// DlgAutoUpgrade.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAutoUpgrade.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAutoUpgrade dialog


CDlgAutoUpgrade::CDlgAutoUpgrade(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAutoUpgrade::IDD, pParent)
    , m_lLoginID(-1)
    , m_iDeviceIndex(-1)
    , m_hGetProgress(NULL)
    , m_bExitGetProgress(FALSE)
{
    memset(&m_struIDCodeList, 0, sizeof(m_struIDCodeList));
	//{{AFX_DATA_INIT(CDlgAutoUpgrade)
	m_strIDCode = _T("");
	m_strIDCodeVersion = _T("");
	m_bConnectStatus = FALSE;
	m_bNewVersionAvailable = FALSE;
	m_strNewVersion = _T("");
	m_strChangeLog = _T("");
	m_strIDCodeCheck = _T("");
	m_strIDCodeVersionCheck = _T("");
	m_bRecommenVersion = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgAutoUpgrade::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAutoUpgrade)
	DDX_Control(pDX, IDC_CMB_IDCODE_INDEX, m_cmbIDCodeIndex);
	DDX_Text(pDX, IDC_EDIT_IDCODE, m_strIDCode);
	DDX_Text(pDX, IDC_EDIT_IDCODE_VERSION, m_strIDCodeVersion);
	DDX_Check(pDX, IDC_CK_CONNECTSTATUS, m_bConnectStatus);
	DDX_Check(pDX, IDC_CK_NEWVERSION_AVAILABLE, m_bNewVersionAvailable);
	DDX_Text(pDX, IDC_EDIT_NEWVERSION, m_strNewVersion);
	DDX_Text(pDX, IDC_EDIT_CHANGELOG, m_strChangeLog);
	DDX_Text(pDX, IDC_EDIT_IDCODE_CHECK, m_strIDCodeCheck);
	DDV_MaxChars(pDX, m_strIDCodeCheck, 128);
	DDX_Text(pDX, IDC_EDIT_IDCODE_VERSION_CHECK, m_strIDCodeVersionCheck);
	DDV_MaxChars(pDX, m_strIDCodeVersionCheck, 64);
	DDX_Check(pDX, IDC_CK_RECOMMEN_VERSION, m_bRecommenVersion);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAutoUpgrade, CDialog)
	//{{AFX_MSG_MAP(CDlgAutoUpgrade)
	ON_BN_CLICKED(IDC_BTN_ALLOW_AUTOUPGRADE, OnBtnAllowAutoupgrade)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_GET_IDCODE, OnBtnGetIdcode)
	ON_CBN_SELCHANGE(IDC_CMB_IDCODE_INDEX, OnSelchangeCmbIdcodeIndex)
	ON_BN_CLICKED(IDC_BTN_MANUAL_CHECK, OnBtnManualCheck)
	ON_BN_CLICKED(IDC_BTN_GET_CHECK_VERSION, OnBtnGetCheckVersion)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAutoUpgrade message handlers

void CDlgAutoUpgrade::OnBtnAllowAutoupgrade() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_STD_CONTROL struSTDCtrl = {0};
	if(!NET_DVR_STDControl(m_lLoginID, NET_DVR_SET_ONLINE_UPGRADE, &struSTDCtrl))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_ONLINE_UPGRADE");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_ONLINE_UPGRADE");
        DWORD dwThreadId;
        m_bExitGetProgress = FALSE;
        m_hGetProgress = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetProgressThread), this, 0, &dwThreadId);
    }
}

BOOL CDlgAutoUpgrade::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetSvrStatus();
    GetNewVersion();
    OnBtnGetIdcode();
    m_strIDCodeCheck = m_struIDCodeList.struCode[0].byCode;
    m_strIDCodeVersionCheck = m_struIDCodeList.struCode[0].byVersion;
    UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

DWORD WINAPI CDlgAutoUpgrade::GetProgressThread(LPVOID lpArg)
{
    CDlgAutoUpgrade *pDlg = (CDlgAutoUpgrade*)lpArg;

    NET_DVR_ONLINEUPGRADE_STATUS struUpgradeStatus = {0};
    NET_DVR_STD_CONFIG   struSTDConfig = {0};
    struSTDConfig.lpOutBuffer = &struUpgradeStatus;
    struSTDConfig.dwOutSize = sizeof(struUpgradeStatus);
    char szBuf[128] = {0};
    while(!pDlg->m_bExitGetProgress)
    {
        if (!NET_DVR_GetSTDConfig(pDlg->m_lLoginID, NET_DVR_GET_ONLINEUPGRADE_PROGRESS, &struSTDConfig))
        {
            g_pMainDlg->AddLog(pDlg->m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ONLINEUPGRADE_PROGRESS");
            break;
        }
        else
        {
            sprintf(szBuf, "NET_DVR_GET_ONLINEUPGRADE_PROGRESS[%d][%d]", struUpgradeStatus.byProgress, struUpgradeStatus.byUpgradeStatus);
            g_pMainDlg->AddLog(pDlg->m_iDeviceIndex, OPERATION_SUCC_T, szBuf);
            if (struUpgradeStatus.byProgress == 100 || struUpgradeStatus.byUpgradeStatus != 1)
            {    
                ::Sleep(1000);
                break;
            }
        }
        ::Sleep(1000);
    }
    return 0;
}

void CDlgAutoUpgrade::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	m_bExitGetProgress = TRUE;
    WaitForSingleObject(m_hGetProgress, INFINITE);
    m_hGetProgress = NULL;
}

void CDlgAutoUpgrade::OnBtnGetIdcode() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_FIRMWARECODE_COND struIDCodeCond = {0};
    struIDCodeCond.dwSize = sizeof(struIDCodeCond);
    struIDCodeCond.dwStartIndex = 1;
    struIDCodeCond.dwMaxNum = MAX_IDCODE_NUM;
    
    NET_DVR_STD_CONFIG  struConfig = {0};
    struConfig.lpCondBuffer = &struIDCodeCond;
    struConfig.dwCondSize = sizeof(struIDCodeCond);
    struConfig.lpOutBuffer = &m_struIDCodeList;
    struConfig.dwOutSize = sizeof(m_struIDCodeList);
    if (!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_FIRMWARECODE, &struConfig))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_FIRMWARECODE");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_FIRMWARECODE");
        int i = 0;
        m_cmbIDCodeIndex.ResetContent();
        char szBuf[4] = {0};
        for (i = 0; i < m_struIDCodeList.dwValidCodeNum; i++)
        {
            sprintf(szBuf, "%d", i + 1);
            m_cmbIDCodeIndex.AddString(szBuf);
        }
        m_cmbIDCodeIndex.SetCurSel(0);
        m_strIDCode = m_struIDCodeList.struCode[0].byCode;
        m_strIDCodeVersion = m_struIDCodeList.struCode[0].byVersion;
    }
    UpdateData(FALSE);
}

void CDlgAutoUpgrade::OnSelchangeCmbIdcodeIndex() 
{
	// TODO: Add your control notification handler code here
	int nCurSel = m_cmbIDCodeIndex.GetCurSel();
    m_strIDCode = m_struIDCodeList.struCode[nCurSel].byCode;
    m_strIDCodeVersion = m_struIDCodeList.struCode[0].byVersion;
    UpdateData(FALSE);
}

void CDlgAutoUpgrade::GetSvrStatus()
{
    NET_DVR_ONLINEUPGRADE_SERVER  struSvr = {0};
    NET_DVR_STD_CONFIG  struConfig = {0};
    struConfig.lpOutBuffer = &struSvr;
    struConfig.dwOutSize = sizeof(struSvr);
    if (!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_ONLINEUPGRADE_SERVER, &struConfig))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ONLINEUPGRADE_SERVER");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ONLINEUPGRADE_SERVER");
        m_bConnectStatus = struSvr.byConnectStatus;
        UpdateData(FALSE);
    }
}

void CDlgAutoUpgrade::GetNewVersion(BOOL bManualCheck)
{
    NET_DVR_ONLINEUPGRADE_VERSION_COND    struVersionCond = {0};
    struVersionCond.dwSize = sizeof(struVersionCond);
    struVersionCond.byCheckFromSvr = bManualCheck;
    NET_DVR_ONLINEUPGRADE_VERSION_RET struVersionRet = {0};
    NET_DVR_STD_CONFIG  struConfig = {0};
    struConfig.lpCondBuffer = &struVersionCond;
    struConfig.dwCondSize = sizeof(struVersionCond);
    struConfig.lpOutBuffer = &struVersionRet;
    struConfig.dwOutSize = sizeof(struVersionRet);
    if (!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_ONLINEUPGRADE_VERSION, &struConfig))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ONLINEUPGRADE_VERSION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ONLINEUPGRADE_VERSION");
        m_bNewVersionAvailable = struVersionRet.byNewVersionAvailable;
        m_strNewVersion = struVersionRet.byNewVersion;
        m_strChangeLog = struVersionRet.byChangeLog;
        UpdateData(FALSE);
    }
}

void CDlgAutoUpgrade::OnBtnManualCheck() 
{
	// TODO: Add your control notification handler code here
	GetNewVersion(TRUE);
}

void CDlgAutoUpgrade::OnBtnGetCheckVersion() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    NET_DVR_RECOMMEN_VERSION_COND   struCond = {0};
    struCond.dwSize = sizeof(struCond);
    memcpy(struCond.byFirmwareCode, m_strIDCodeCheck.GetBuffer(0), m_strIDCodeCheck.GetLength());
    memcpy(struCond.byFirmwareVersion, m_strIDCodeVersionCheck.GetBuffer(0), m_strIDCodeVersionCheck.GetLength());
    NET_DVR_RECOMMEN_VERSION_RET    struRet = {0};
    NET_DVR_STD_CONFIG struConfig = {0};
    struConfig.lpCondBuffer = &struCond;
    struConfig.dwCondSize = sizeof(struCond);
    struConfig.lpOutBuffer = &struRet;
    struConfig.dwOutSize = sizeof(struRet);
    if (!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_RECOMMEN_VERSION, &struConfig))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_RECOMMEN_VERSION");
        return ;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_RECOMMEN_VERSION");
    }
    m_bRecommenVersion = struRet.byRecommenUpgrade;
    UpdateData(FALSE);
}
