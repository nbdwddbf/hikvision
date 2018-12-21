// DlgMergeDevResource.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMergeDevResource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMergeDevResource dialog


CDlgMergeDevResource::CDlgMergeDevResource(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMergeDevResource::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMergeDevResource)
	m_bAudio = FALSE;
	m_dwSubWinNo = 0;
	m_dwWinNo = 0;
	//}}AFX_DATA_INIT
}


void CDlgMergeDevResource::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMergeDevResource)
	DDX_Control(pDX, IDC_COMBO_OUTPUT_NO, m_comboOutputNo);
	DDX_Control(pDX, IDC_COMBO_CODE_CHAN, m_comboCodeChan);
	DDX_Check(pDX, IDC_CHK_AUDIO, m_bAudio);
	DDX_Text(pDX, IDC_EDIT_SUBWIN_NO, m_dwSubWinNo);
	DDX_Text(pDX, IDC_EDIT_WIN_NO, m_dwWinNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMergeDevResource, CDialog)
	//{{AFX_MSG_MAP(CDlgMergeDevResource)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET_ALL, OnBtnGetAll)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_CBN_SELCHANGE(IDC_COMBO_CODE_CHAN, OnSelchangeComboCodeChan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMergeDevResource message handlers

BOOL CDlgMergeDevResource::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    int i = 0;
    
    for (i = 0; i < 8; i++)
    {
        sprintf(m_szLan, "%d", i + 1);
        m_comboCodeChan.AddString(m_szLan);
    }
    
    NET_DVR_DISPLAYCFG struOutput = {0};
    DWORD dwReturned = 0;
    
    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_VIDEOWALLDISPLAYNO, 0, &struOutput, sizeof(struOutput), &dwReturned))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_VIDEOWALLDISPLAYNO");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_VIDEOWALLDISPLAYNO");
        
        int iBnc = 0;
        int iVga = 0;
        int iHdmi = 0;
        int iDvi = 0;
        int iUnknown = 0;
        
        for (i = 0; i < MAX_DISPLAY_NUM; i++)
        {
            switch (struOutput.struDisplayParam[i].byDispChanType)
            {
            case 1:
                sprintf(m_szLan, "BNC%d", iBnc + 1);                
                iBnc++;
                break;
            case 2:
                sprintf(m_szLan, "VGA%d", iVga + 1);
                iVga++;
                break;
            case 3:
                sprintf(m_szLan, "HDMI%d", iHdmi + 1);
                iHdmi++;
                break;
            case 4:
                sprintf(m_szLan, "DVI%d", iDvi + 1);
                iDvi++;
                break;
            case 0xff:
                break;
            default:
                sprintf(m_szLan, "Unknown%d", iUnknown + 1);
                iUnknown ++; 
                break;                
            }
            
            if (struOutput.struDisplayParam[i].byDispChanType != 0xff || struOutput.struDisplayParam[i].byDispChanType != 0 )
            {
                m_comboOutputNo.AddString(m_szLan);
                m_comboOutputNo.SetItemData(iBnc + iVga + iHdmi + iDvi + iUnknown - 1, struOutput.struDisplayParam[i].dwDisplayNo);
            }
        }
    }

    memset(&m_struChanResource, 0, sizeof(m_struChanResource));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMergeDevResource::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    int iChanSel = m_comboCodeChan.GetCurSel();

    if (iChanSel == CB_ERR)
    {
        return;
    }

    DWORD dwReturned = 0;

    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_CHAN_RELATION, iChanSel + 1, &m_struChanResource[iChanSel], sizeof(m_struChanResource[iChanSel]), &dwReturned))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_CHAN_RELATION");
        MessageBox("Error, NET_DVR_GET_CHAN_RELATION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_CHAN_RELATION");

        int i = 0;
        for (i = 0; i < m_comboOutputNo.GetCount(); i++)
        {
            DWORD dwData = m_comboOutputNo.GetItemData(i) ;
            if (dwData == m_struChanResource[iChanSel].dwDisplayChan)
            {
                m_comboOutputNo.SetCurSel(i);
                break;
            }
        }
        
        if (i == m_comboOutputNo.GetCount())
        {
            m_comboOutputNo.SetCurSel(CB_ERR);
        }
        
        m_bAudio = m_struChanResource[iChanSel].byRelateAudio;
        m_dwWinNo = m_struChanResource[iChanSel].dwSubWinNo & 0xffff;
        m_dwSubWinNo = (m_struChanResource[iChanSel].dwSubWinNo & 0xff0000) >> 16;
        
        UpdateData(FALSE);
    }	
}

void CDlgMergeDevResource::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    int iChanSel = m_comboCodeChan.GetCurSel();
    int iOutputSel = m_comboOutputNo.GetCurSel();
    
    if (iChanSel == CB_ERR || iOutputSel == CB_ERR)
    {
        return;
    }

    m_struChanResource[iChanSel].dwSize = sizeof(m_struChanResource[iChanSel]);
    m_struChanResource[iChanSel].dwDisplayChan = m_comboOutputNo.GetItemData(iOutputSel);
    m_struChanResource[iChanSel].byRelateAudio = m_bAudio;
    m_struChanResource[iChanSel].dwSubWinNo = 0x01000000 | ((m_dwSubWinNo & 0xff) << 16) | (m_dwWinNo & 0xffff);

    if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_CHAN_RELATION, iChanSel + 1, &m_struChanResource[iChanSel], sizeof(m_struChanResource[iChanSel])))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_CHAN_RELATION");
        MessageBox("Error, NET_DVR_SET_CHAN_RELATION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_CHAN_RELATION");
    }	
}

void CDlgMergeDevResource::OnBtnGetAll() 
{
	// TODO: Add your control notification handler code here
    DWORD dwReturned = 0;
    char sBuffer[4 + sizeof(m_struChanResource)] = {0};

    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_ALL_CHAN_RELATION, 0, sBuffer, sizeof(sBuffer), &dwReturned))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALL_CHAN_RELATION");
        MessageBox("Error, NET_DVR_GET_ALL_CHAN_RELATION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALL_CHAN_RELATION");
        memcpy(&m_struChanResource, sBuffer+4, sizeof(m_struChanResource)); 
        int iChanSel = m_comboCodeChan.GetCurSel();

        if (iChanSel != CB_ERR)
        {
            int i = 0;
            for (i = 0; i < m_comboOutputNo.GetCount(); i++)
            {
                if (m_comboOutputNo.GetItemData(i) == m_struChanResource[iChanSel].dwDisplayChan)
                {
                    m_comboOutputNo.SetCurSel(i);
                    break;
                }
            }

            if (i == m_comboOutputNo.GetCount())
            {
                m_comboOutputNo.SetCurSel(CB_ERR);
            }

            m_bAudio = m_struChanResource[iChanSel].byRelateAudio;
            m_dwWinNo = m_struChanResource[iChanSel].dwSubWinNo & 0x00001111;
            m_dwSubWinNo = (m_struChanResource[iChanSel].dwSubWinNo & 0x00110000) >> 16;

            UpdateData(FALSE);
        }
    }	
}

void CDlgMergeDevResource::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CDlgMergeDevResource::OnSelchangeComboCodeChan() 
{
	// TODO: Add your control notification handler code here
//	OnBtnGet();
    UpdateData(TRUE); 
    int iChanSel = m_comboCodeChan.GetCurSel();

    int i = 0;
    for (i = 0; i < m_comboOutputNo.GetCount(); i++)
    {
        DWORD dwData = m_comboOutputNo.GetItemData(i) ;
        if (dwData == m_struChanResource[iChanSel].dwDisplayChan)
        {
            m_comboOutputNo.SetCurSel(i);
            break;
        }
    }
    
    if (i == m_comboOutputNo.GetCount())
    {
        m_comboOutputNo.SetCurSel(CB_ERR);
    }
    
    m_bAudio = m_struChanResource[iChanSel].byRelateAudio;
    m_dwWinNo = m_struChanResource[iChanSel].dwSubWinNo & 0xffff;
    m_dwSubWinNo = (m_struChanResource[iChanSel].dwSubWinNo & 0xff0000) >> 16;
    
    UpdateData(FALSE);
}
