// DlgDevWordMode.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgDevWorkMode.h"
#include "DlgStorageServerSwitch.h"
#include "DlgCloudStorage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDevWordMode dialog


CDlgDevWorkMode::CDlgDevWorkMode(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDevWorkMode::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDevWordMode)
	m_bEnableCS = FALSE;
	//}}AFX_DATA_INIT
    m_lUserID = -1;
    m_iDevIndex = -1;
    m_lChannel = -1;
    memset(&m_struCSCfg,0,sizeof(m_struCSCfg));
}


void CDlgDevWorkMode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDevWordMode)
	DDX_Check(pDX, IDC_CHK_ENABLE_CS, m_bEnableCS);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDevWorkMode, CDialog)
	//{{AFX_MSG_MAP(CDlgDevWordMode)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
    ON_BN_CLICKED(IDC_BTN_STORAGE_SERVER_SWITCH, OnBtnStorageServerSwitch)
	ON_BN_CLICKED(IDC_BTN_STORAGE_SERVER_FILE, OnBtnStorageServerFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDevWordMode message handlers

void CDlgDevWorkMode::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	
    DWORD dwReturned = 0;
    char szLan[1024] = {0};
    
    if (!NET_DVR_GetDVRConfig(m_lUserID,NET_DVR_GET_CLOUD_STORAGE_CFG,0,&m_struCSCfg,sizeof(m_struCSCfg),&dwReturned))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_CLOUD_STORAGE_CFG");
        g_StringLanType(szLan, "»ñÈ¡ÔÆ´æ´¢ÅäÖÃÐÅÏ¢Ê§°Ü", "Get Cloud Storage failed!");
		AfxMessageBox(szLan);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_CLOUD_STORAGE_CFG");

    }
    
    m_bEnableCS = m_struCSCfg.byEnableCS;

    UpdateData(FALSE);
}

BOOL CDlgDevWorkMode::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	OnBtnGet();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgDevWorkMode::OnBtnSet() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char szLan[1024] = {0};
    
    m_struCSCfg.dwSize = sizeof(m_struCSCfg);
   m_struCSCfg.byEnableCS = m_bEnableCS;

    
    if (!NET_DVR_SetDVRConfig(m_lUserID,NET_DVR_SET_CLOUD_STORAGE_CFG,0,&m_struCSCfg,sizeof(m_struCSCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_CLOUD_STORAGE_CFG");
        g_StringLanType(szLan, "ÉèÖÃÔÆ´æ´¢ÅäÖÃÐÅÏ¢Ê§°Ü", "Set Cloud Storage failed");
        AfxMessageBox(szLan);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_CLOUD_STORAGE_CFG");
        
    }
    
    UpdateData(FALSE);
}

void CDlgDevWorkMode::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
    CDialog::OnCancel();
}


void CDlgDevWorkMode::OnBtnStorageServerSwitch()
{
    CDlgStorageServerSwitch dlg;
    dlg.m_lServerID = m_lUserID;
    dlg.m_lChannel = m_lChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}
void CDlgDevWorkMode::OnBtnStorageServerFile() 
{
	// TODO: Add your control notification handler code here
    CDlgCloudStorage dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDevIndex;
    dlg.DoModal();
}
