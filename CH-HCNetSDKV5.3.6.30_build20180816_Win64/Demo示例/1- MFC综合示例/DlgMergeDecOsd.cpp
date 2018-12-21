// DlgMergeDecOsd.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMergeDecOsd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMergeDecOsd dialog


CDlgMergeDecOsd::CDlgMergeDecOsd(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMergeDecOsd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMergeDecOsd)
	m_bShow = FALSE;
	m_csOsdContent = _T("");
	m_dwX = 0;
	m_dwY = 0;
	m_dwOSDRed = 0;
	m_dwOSDGreen = 0;
	m_dwOSDBlue = 0;
	m_dwHeight = 0;
	m_dwWidth = 0;
	//}}AFX_DATA_INIT
    memset(m_struOutputOsdCfg, 0, sizeof(m_struOutputOsdCfg)); 
}


void CDlgMergeDecOsd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMergeDecOsd)
	DDX_Control(pDX, IDC_COMBO_OSD_COLOR, m_cmbOSDColor);
	DDX_Control(pDX, IDC_COMBO_OUTPUT_NO, m_comboOutputNo);
	DDX_Control(pDX, IDC_COMBO_OSD_NO, m_comboOsdNo);
	DDX_Control(pDX, IDC_COMBO_FONT_SIZE, m_comboFontSize);
	DDX_Check(pDX, IDC_CHK_SHOW, m_bShow);
	DDX_Text(pDX, IDC_EDIT_OSD_CONTENT, m_csOsdContent);
	DDX_Text(pDX, IDC_EDIT_X, m_dwX);
	DDX_Text(pDX, IDC_EDIT_Y, m_dwY);
	DDX_Text(pDX, IDC_EDIT_OSD_RED, m_dwOSDRed);
	DDX_Text(pDX, IDC_EDIT_OSD_GREEN, m_dwOSDGreen);
	DDX_Text(pDX, IDC_EDIT_OSD_BLUE, m_dwOSDBlue);
	DDX_Text(pDX, IDC_EDIT_OSD_HEIGHT, m_dwHeight);
	DDX_Text(pDX, IDC_EDIT_OSD_WIDTH, m_dwWidth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMergeDecOsd, CDialog)
	//{{AFX_MSG_MAP(CDlgMergeDecOsd)
	ON_CBN_SELCHANGE(IDC_COMBO_OUTPUT_NO, OnSelchangeComboOutputNo)
	ON_CBN_SELCHANGE(IDC_COMBO_OSD_NO, OnSelchangeComboOsdNo)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET_ALL, OnBtnGetAll)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMergeDecOsd message handlers

BOOL CDlgMergeDecOsd::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    int i = 0;
    
    for (i = 0; i < 16; i++)
    {
        sprintf(m_szLan, "%d", i + 1);
        m_comboOsdNo.AddString(m_szLan);
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
                break;                
            }
            
            if (struOutput.struDisplayParam[i].byDispChanType != 0xff)
            {
                int iIndex = m_comboOutputNo.AddString(m_szLan);
                m_comboOutputNo.SetItemData(iIndex, struOutput.struDisplayParam[i].dwDisplayNo);
            }
        }
    }
    m_cmbOSDColor.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMergeDecOsd::OnSelchangeComboOutputNo() 
{
	// TODO: Add your control notification handler code here
    OnBtnGetAll();	
}

void CDlgMergeDecOsd::OnSelchangeComboOsdNo() 
{
	// TODO: Add your control notification handler code here
     UpdateData(TRUE); 
    int iOutputSel = m_comboOutputNo.GetCurSel();
    int iOsdSel = m_comboOsdNo.GetCurSel();
    
    if (iOutputSel == CB_ERR || iOsdSel == CB_ERR)
    {
        return;
    }

    m_bShow = m_struOutputOsdCfg[iOsdSel].byEnable;
    m_comboFontSize.SetCurSel(m_struOutputOsdCfg[iOsdSel].byFontSize - 1);
    m_csOsdContent = (char *)m_struOutputOsdCfg[iOsdSel].byOsdContent;
    m_dwX = m_struOutputOsdCfg[iOsdSel].struRect.dwXCoordinate;
    m_dwY = m_struOutputOsdCfg[iOsdSel].struRect.dwYCoordinate;
    m_dwWidth = m_struOutputOsdCfg[iOsdSel].struRect.dwWidth;
    m_dwHeight = m_struOutputOsdCfg[iOsdSel].struRect.dwHeight;
    
    m_cmbOSDColor.SetCurSel(m_struOutputOsdCfg[iOsdSel].byOSDColor); 
//     m_dwOSDRed = m_struOutputOsdCfg[iOsdSel].struOsdColor.byRed; 
//     m_dwOSDGreen = m_struOutputOsdCfg[iOsdSel].struOsdColor.byGreen;
//     m_dwOSDBlue = m_struOutputOsdCfg[iOsdSel].struOsdColor.byBlue; 
    UpdateData(FALSE);
}

void CDlgMergeDecOsd::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    int iOutputSel = m_comboOutputNo.GetCurSel();
    int iOsdSel = m_comboOsdNo.GetCurSel();

    if (iOutputSel == CB_ERR || iOsdSel == CB_ERR)
    {
        return;
    }

    DWORD dwReturned = 0;
    DWORD dwOutPutNo = m_comboOutputNo.GetItemData(iOutputSel);
    DWORD dwOsdWinNo = 0x01000000 | (dwOutPutNo << 16) | (iOsdSel + 1);

    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_OUTPUT_OSD_CFG, dwOsdWinNo, &m_struOutputOsdCfg[iOsdSel], sizeof(m_struOutputOsdCfg[iOsdSel]), &dwReturned))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_OUTPUT_OSD_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_OUTPUT_OSD_CFG");
        OnSelchangeComboOsdNo();
    }     

    UpdateData(FALSE);
}

void CDlgMergeDecOsd::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    int iOutputSel = m_comboOutputNo.GetCurSel();
    int iOsdSel = m_comboOsdNo.GetCurSel();
    
    if (iOutputSel == CB_ERR || iOsdSel == CB_ERR)
    {
        return;
    }
    
    DWORD dwOutPutNo = m_comboOutputNo.GetItemData(iOutputSel);
    DWORD dwOsdWinNo = 0x01000000 | (dwOutPutNo << 16) | (iOsdSel + 1);

    m_struOutputOsdCfg[iOsdSel].dwSize = sizeof(m_struOutputOsdCfg[iOsdSel]);
    m_struOutputOsdCfg[iOsdSel].byEnable = m_bShow; 
    m_struOutputOsdCfg[iOsdSel].byFontSize = m_comboFontSize.GetCurSel() + 1;
//    memcpy(m_struOutputOsdCfg[iOsdSel].byOsdContent, m_csOsdContent.GetBuffer(0), min(MAX_OSD_LEN, m_csOsdContent.GetLength()));
    strncpy((char *)m_struOutputOsdCfg[iOsdSel].byOsdContent, (LPCTSTR)m_csOsdContent, MAX_OSD_LEN);
    m_struOutputOsdCfg[iOsdSel].struRect.dwXCoordinate = m_dwX;
    m_struOutputOsdCfg[iOsdSel].struRect.dwYCoordinate = m_dwY;
    m_struOutputOsdCfg[iOsdSel].struRect.dwWidth = m_dwWidth;
    m_struOutputOsdCfg[iOsdSel].struRect.dwHeight = m_dwHeight;

     m_struOutputOsdCfg[iOsdSel].byOSDColor =  m_cmbOSDColor.GetCurSel(); 
//     m_struOutputOsdCfg[iOsdSel].struOsdColor.byRed = (BYTE)m_dwOSDRed; 
//     m_struOutputOsdCfg[iOsdSel].struOsdColor.byGreen = (BYTE)m_dwOSDGreen; 
//     m_struOutputOsdCfg[iOsdSel].struOsdColor.byBlue = (BYTE)m_dwOSDBlue; 
    if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_OUTPUT_OSD_CFG, dwOsdWinNo, &m_struOutputOsdCfg[iOsdSel], sizeof(m_struOutputOsdCfg[iOsdSel])))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_OUTPUT_OSD_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_OUTPUT_OSD_CFG");
    }	
}

void CDlgMergeDecOsd::OnBtnGetAll() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    int iOutputSel = m_comboOutputNo.GetCurSel();

    if (iOutputSel == CB_ERR)
    {
        return;
    }

    DWORD dwReturned = 0;
    DWORD dwOutputNo = m_comboOutputNo.GetItemData(iOutputSel);
    char sBuffer[4 + sizeof(m_struOutputOsdCfg)] = {0};

    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_OUTPUT_ALL_OSD_CFG, dwOutputNo, sBuffer, sizeof(sBuffer), &dwReturned))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_OUTPUT_ALL_OSD_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_OUTPUT_ALL_OSD_CFG");
        memcpy(&m_struOutputOsdCfg, sBuffer+4, sizeof(m_struOutputOsdCfg)); 
//        m_comboOutputNo.SetCurSel(0);
        m_comboOsdNo.SetCurSel(0);
        UpdateData(FALSE);
        OnSelchangeComboOsdNo();
    }
    
}

void CDlgMergeDecOsd::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
