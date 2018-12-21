// DlgTrialPIPCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgTrialPIPCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTrialPIPCfg dialog


CDlgTrialPIPCfg::CDlgTrialPIPCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTrialPIPCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTrialPIPCfg)
	m_dwX = 0;
	m_dwY = 0;
	m_dwHeight = 0;
	m_dwWidth = 0;
	//}}AFX_DATA_INIT
}


void CDlgTrialPIPCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTrialPIPCfg)
	DDX_Control(pDX, IDC_CMB_SHOW_MODE, m_cmbShowMode);
	DDX_Control(pDX, IDC_CMB_SHOWCHAN, m_cmbShowChan);
	DDX_Control(pDX, IDC_CMB_SHOW_POS, m_cmbShowPosition);
	DDX_Control(pDX, IDC_CMB_PIP_CHAN_NUM, m_cmbPipChanNum);
	DDX_Text(pDX, IDC_EDIT_X, m_dwX);
	DDX_Text(pDX, IDC_EDIT_Y, m_dwY);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_dwHeight);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_dwWidth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTrialPIPCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgTrialPIPCfg)
	ON_BN_CLICKED(IDC_GET, OnGet)
	ON_CBN_SELCHANGE(IDC_CMB_SHOW_POS, OnSelchangeCmbShowPos)
	ON_BN_CLICKED(IDC_SET, OnSet)
	ON_BN_CLICKED(IDC_MODE, OnMode)
	ON_CBN_SELCHANGE(IDC_CMB_PIP_CHAN_NUM, OnSelchangeCmbPipChanNum)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTrialPIPCfg message handlers

void CDlgTrialPIPCfg::OnGet() 
{
	// TODO: Add your control notification handler code here
	
    memset(&m_struInquestPIPStatus,0,sizeof(m_struInquestPIPStatus));

    NET_DVR_INQUEST_ROOM struInquestRoom = {0};
   struInquestRoom.byRoomIndex = 1;
    if (!NET_DVR_InquestGetPIPStatus_V40(m_lUserID,&struInquestRoom,&m_struInquestPIPStatus))
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_InquestGetPIPStatus_V40");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T, "NET_DVR_InquestGetPIPStatus_V40");
    }
    
    ShowCurPIPInfo();
}

BOOL CDlgTrialPIPCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
   
	m_dwLastShowChanIndex = 0;
	// TODO: Add extra initialization here
    AddChanItemInfo(&m_cmbShowChan);

    AddPIPShowModeInfo();

  

    char szTemp[128] = {0};
    DWORD dwIndex = 0;
    m_cmbPipChanNum.ResetContent();
    
    for (int i = 0; i < 9; i++)
    {
        sprintf(szTemp,"%d",i); 
        m_cmbPipChanNum.AddString(szTemp);
        m_cmbPipChanNum.SetItemData(dwIndex++,i);
    }
     m_cmbPipChanNum.SetCurSel(0);

    OnGet();
    UpdateData(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTrialPIPCfg::AddChanItemInfo(CComboBox* cmbBox)
{
    //cmbBox.ResetContent();
    BOOL bBreak = FALSE;
    DWORD dwIndex = 0;
    char szLan[128] = {0};
    char szTemp[128] = {0};

    cmbBox->ResetContent();

    for (int i = 0; i< m_struSystemInfo.byVideoInTypeNum; i++)
    { 
        if (!bBreak)
        {
            switch (m_struSystemInfo.struVideoIn[i].wInType)
            {
            case 0:
                memcpy(szTemp,"SDI",sizeof("SDI"));
                break;
            case  1:
                memcpy(szTemp,"VGA",sizeof("VGA"));
                break;
            case 2:
                memcpy(szTemp,"HDMI",sizeof("HDMI"));
                break;
            case 3:
                memcpy(szTemp,"IP",sizeof("IP"));
                break; 
            case 4:
                memcpy(szTemp,"PIP",sizeof("PIP"));
                break;
            case 5:              
                memcpy(szTemp,"POE",sizeof("POE"));
                break;
            case 6:
                memcpy(szTemp,"YPBPR",sizeof("YPBPR"));
                break;
            default:
                memcpy(szTemp,"UnKown",sizeof("UnKown"));
                break;
            }
            for (int j = 0; j < m_struSystemInfo.struVideoIn[i].wInNum; j++)
            {
                
                sprintf(szLan,"%s%02d",szTemp,j+1);                    
                cmbBox->AddString(szLan);
                cmbBox->SetItemData(dwIndex,m_struSystemInfo.struVideoIn[i].wStartNo + j);
                dwIndex++;
            }
            
              //bBreak = TRUE;
        }
    }
    cmbBox->AddString("NULL");
    cmbBox->SetItemData(dwIndex,0xff);
    cmbBox->SetCurSel(0);
    UpdateData(FALSE);
    return;
}


void CDlgTrialPIPCfg::AddPIPShowModeInfo()
{
    char szMode[128]   = {0};
    char szModeCn[128] = {0};
    char szModeEn[128] = {0};
    DWORD  dwIndex = 0;
    m_cmbShowMode.ResetContent();

 
    memcpy(szModeCn,"画中画",sizeof("画中画"));
    memcpy(szModeEn,"PIP",sizeof("PIP"));
    g_StringLanType(szMode,szModeCn,szModeEn);
    m_cmbShowMode.AddString(szMode);
    m_cmbShowMode.SetItemData(dwIndex,0);
    dwIndex++;

    memcpy(szModeCn,"均分",sizeof("均分"));
    memcpy(szModeEn,"Average",sizeof("Average"));
    g_StringLanType(szMode,szModeCn,szModeEn);
    m_cmbShowMode.AddString(szMode);
    m_cmbShowMode.SetItemData(dwIndex,1);
    dwIndex++;

    memcpy(szModeCn,"拼接",sizeof("拼接"));
    memcpy(szModeEn,"Split",sizeof("Split"));
    g_StringLanType(szMode,szModeCn,szModeEn);
    m_cmbShowMode.AddString(szMode);
    m_cmbShowMode.SetItemData(dwIndex,2);
    

    m_cmbShowMode.SetCurSel(0);
    UpdateData(FALSE);
}


void CDlgTrialPIPCfg::ShowCurPIPInfo()
{
    UpdateData(FALSE);

    if (m_struInquestPIPStatus.struStructHead.wLength != sizeof(m_struInquestPIPStatus))
    {
        return;
    }

    //show Back Chan
    SelectCmbBoxByData(&m_cmbPipChanNum, m_struInquestPIPStatus.byPIPMode);
    SelectCmbBoxByData(&m_cmbShowMode, m_struInquestPIPStatus.byPicShowMode);
    OnSelchangeCmbPipChanNum();
    
    m_cmbShowPosition.SetCurSel(0);
    OnSelchangeCmbShowPos();

    UpdateData(FALSE);
}

void CDlgTrialPIPCfg::SelectCmbBoxByData(CComboBox* cmbBox, DWORD dwFindData)
{
    if (cmbBox == NULL)
    {
        return;
    }


    for(int i = 0; i< cmbBox->GetCount(); i++)
    {
        if (dwFindData == cmbBox->GetItemData(i))
        {
            cmbBox->SetCurSel(i);
            break;
        }
    }

    UpdateData(FALSE);

}

void CDlgTrialPIPCfg::OnSelchangeCmbShowPos() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if (m_cmbShowPosition.GetCurSel() < 0)
    {
        return;
    }


    DWORD dwIndex = m_cmbShowPosition.GetCurSel();
    m_dwLastShowChanIndex = dwIndex; 
    if (dwIndex == 0)
    {
        SelectCmbBoxByData(&m_cmbShowChan,m_struInquestPIPStatus.byBackChan);
        m_dwX  = 0;
        m_dwY  = 0;
        m_dwHeight = 0;
        m_dwWidth =0;
    }
    else
    {
        dwIndex -= 1;
        SelectCmbBoxByData(&m_cmbShowChan,m_struInquestPIPStatus.strPipPara[dwIndex].byPipChan);
        m_dwX  = m_struInquestPIPStatus.strPipPara[dwIndex].wTopLeftX;
        m_dwY  = m_struInquestPIPStatus.strPipPara[dwIndex].wTopLeftY;
        m_dwHeight = m_struInquestPIPStatus.strPipPara[dwIndex].wHeight;
        m_dwWidth = m_struInquestPIPStatus.strPipPara[dwIndex].wWidth;
    }


   

    UpdateData(FALSE);
}

void CDlgTrialPIPCfg::OnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    m_struInquestPIPStatus.struStructHead.wLength = sizeof(m_struInquestPIPStatus);
    NET_DVR_INQUEST_ROOM struInquestRoom = {0};
    struInquestRoom.byRoomIndex = 1;

    for (int i = 0; i< MAX_INQUEST_PIP_NUM_EX;i++)
    {
        if (m_struInquestPIPStatus.strPipPara[i].byPipChan == 0)
        {
            m_struInquestPIPStatus.strPipPara[i].byPipChan = 0xff;
        }
    }
    
    m_struInquestPIPStatus.byPicShowMode = m_cmbShowMode.GetItemData(m_cmbShowMode.GetCurSel());
    m_struInquestPIPStatus.byPIPMode = m_cmbPipChanNum.GetItemData(m_cmbPipChanNum.GetCurSel());
    if (!NET_DVR_InquestSetPIPStatus_V40(m_lUserID,&struInquestRoom,&m_struInquestPIPStatus))
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_InquestSetPIPStatus_V40");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T, "NET_DVR_InquestSetPIPStatus_V40");
    }
    
    return;

}

void CDlgTrialPIPCfg::SaveLastSmallChanInfo(DWORD dwChaIndex)
{
    UpdateData(TRUE);
    if (dwChaIndex == 0)
    {
        m_struInquestPIPStatus.byBaseChan = m_cmbShowChan.GetItemData(m_cmbShowChan.GetCurSel());
        m_struInquestPIPStatus.byBackChan = m_cmbShowChan.GetItemData(m_cmbShowChan.GetCurSel());
    }
    else
    {
        m_struInquestPIPStatus.strPipPara[dwChaIndex - 1].byPipChan = m_cmbShowChan.GetItemData(m_cmbShowChan.GetCurSel());
        m_struInquestPIPStatus.strPipPara[dwChaIndex - 1].wTopLeftX = m_dwX;
        m_struInquestPIPStatus.strPipPara[dwChaIndex - 1].wTopLeftY = m_dwY;
        m_struInquestPIPStatus.strPipPara[dwChaIndex - 1].wHeight   = m_dwHeight;
        m_struInquestPIPStatus.strPipPara[dwChaIndex - 1].wWidth    = m_dwWidth;
        
    }  
}

void CDlgTrialPIPCfg::OnMode() 
{
	// TODO: Add your control notification handler code here
    DWORD dwIndex = m_cmbShowPosition.GetCurSel();
    SaveLastSmallChanInfo(dwIndex);
}

void CDlgTrialPIPCfg::OnSelchangeCmbPipChanNum() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    char szLan[128] = {0};

    DWORD dwPipNum = m_cmbPipChanNum.GetItemData(m_cmbPipChanNum.GetCurSel());
    if (dwPipNum == 0xFF)
    {
        dwPipNum = 1;  //only background picture
    }
    else
    {
        dwPipNum +=1;   //Contains background picture
    }
    DWORD dwIndex = 0;
    m_cmbShowPosition.ResetContent();
    for (int i = 0; i< dwPipNum; i++)
    {
        sprintf(szLan,"%d",i+1);
        m_cmbShowPosition.AddString(szLan);
        m_cmbShowPosition.SetItemData(dwIndex++,i);
    }

    m_cmbShowPosition.SetCurSel(0);
}
