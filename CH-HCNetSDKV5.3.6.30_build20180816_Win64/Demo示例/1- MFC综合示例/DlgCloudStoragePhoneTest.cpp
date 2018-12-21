// DlgCloudStoragePhoneTest.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgCloudStoragePhoneTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCloudStoragePhoneTest dialog


CDlgCloudStoragePhoneTest::CDlgCloudStoragePhoneTest(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCloudStoragePhoneTest::IDD, pParent)
    , m_strAccessKey(_T(""))
    , m_strSecretKey(_T(""))
{
	//{{AFX_DATA_INIT(CDlgCloudStoragePhoneTest)
	m_csIP = _T("");
	m_csPassword = _T("");
	m_csPhoneNum = _T("");
	m_dwPoolID = 0;
	m_csUser = _T("");
	m_dwPort = 0;
	//}}AFX_DATA_INIT

    m_lUserID = -1;
    m_dwDevIndex = -1;
    m_lCloudServerTest = -1;
    m_lPhoneTest = -1;
    memset(&m_struServerTestPara, 0, sizeof(m_struServerTestPara));
    memset(&m_struPhoneTestPara, 0, sizeof(m_struPhoneTestPara));
}


void CDlgCloudStoragePhoneTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCloudStoragePhoneTest)
	DDX_Control(pDX, IDC_COMBO_POOLPARAM, m_comPoolParam);
	DDX_Text(pDX, IDC_EDIT_IP, m_csIP);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csPassword);
	DDX_Text(pDX, IDC_EDIT_PHONE_NUM, m_csPhoneNum);
	DDX_Text(pDX, IDC_EDIT_POOL_ID, m_dwPoolID);
	DDX_Text(pDX, IDC_EDIT_USER, m_csUser);
	DDX_Text(pDX, IDC_EDIT_PORT, m_dwPort);
	//}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMBO_PROTOCOL_TYPE, m_comboProtocolType);
    DDX_Text(pDX, IDC_EDIT_ACCESS_KEY, m_strAccessKey);
    DDX_Text(pDX, IDC_EDIT_SECRET_KEY, m_strSecretKey);
}


BEGIN_MESSAGE_MAP(CDlgCloudStoragePhoneTest, CDialog)
	//{{AFX_MSG_MAP(CDlgCloudStoragePhoneTest)
	ON_BN_CLICKED(IDC_BTN_CLOUD_TEST, OnBtnCloudTest)
	ON_BN_CLICKED(IDC_BTN_PHONE_TEST, OnBtnPhoneTest)
	ON_CBN_SELCHANGE(IDC_COMBO_POOLPARAM, OnSelchangeComboPoolparam)
	ON_BN_CLICKED(IDC_BTN_CLOUD_SAVE, OnBtnCloudSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCloudStoragePhoneTest message handlers

DWORD WINAPI CDlgCloudStoragePhoneTest::GetCloudServerTestInfoThread(LPVOID lpArg)
{
    CDlgCloudStoragePhoneTest* pThis = reinterpret_cast<CDlgCloudStoragePhoneTest*>(lpArg);
    DWORD dwState = 0;
    CString csErrInfo;
    while (1)
    {
        
        if (!NET_DVR_GetRemoteConfigState(pThis->m_lCloudServerTest, &dwState))
        {
            g_pMainDlg->AddLog(pThis->m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GetRemoteConfigState NET_DVR_FIND_NAS_DIRECTORY ");
            pThis->GetDlgItem(IDC_STATIC_FTP_SERVER_TEST)->SetWindowText("Get state Fail!");
            NET_DVR_StopRemoteConfig(pThis->m_lCloudServerTest);
            return -1;
        }
        else
        {
            if (dwState == PROCESSING)
            {
                pThis->GetDlgItem(IDC_STATIC_FTP_SERVER_TEST)->SetWindowText("Testing...");
                Sleep(1000);
            }
            else if (dwState == PROCESS_SUCCESS)
            {
                pThis->GetDlgItem(IDC_STATIC_FTP_SERVER_TEST)->SetWindowText("Test Success!");
                break;
            }
            else if (dwState == PROCESS_EXCEPTION)
            {
                pThis->GetDlgItem(IDC_STATIC_FTP_SERVER_TEST)->SetWindowText("Test Exception!!");
                break;
            }
            else
            {
                csErrInfo.Format("Test Fail %d", dwState);
                pThis->GetDlgItem(IDC_STATIC_FTP_SERVER_TEST)->SetWindowText(csErrInfo);
                break;
            }
        }
        
    }
    if (-1 != pThis->m_lCloudServerTest)
    {
        if (!NET_DVR_StopRemoteConfig(pThis->m_lCloudServerTest))
        {
            g_pMainDlg->AddLog(pThis->m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_CLOUDSTORAGE_SERVER_TEST Stop Remote Config Failed");
        }
        else
        {
            g_pMainDlg->AddLog(pThis->m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_CLOUDSTORAGE_SERVER_TEST Stop Remote Config Successful");
            pThis->m_lCloudServerTest = -1;
        }
    }
    return 0 ;
}

void CDlgCloudStoragePhoneTest::OnBtnCloudTest() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

	m_struServerTestPara.dwSize = sizeof(m_struServerTestPara);
    memcpy(m_struServerTestPara.unionServerPara.struCloudStoragePara.struIPAdder.sIpV4, m_csIP, 16);
    m_struServerTestPara.unionServerPara.struCloudStoragePara.wPort = m_dwPort;
    memcpy(m_struServerTestPara.unionServerPara.struCloudStoragePara.szUser, m_csUser, CLOUD_NAME_LEN);
    memcpy(m_struServerTestPara.unionServerPara.struCloudStoragePara.szPassword, m_csPassword, CLOUD_PASSWD_LEN);

    m_struServerTestPara.unionServerPara.struCloudStoragePara.byProtocolType = m_comboProtocolType.GetCurSel();
    memcpy(m_struServerTestPara.unionServerPara.struCloudStoragePara.szAccessKey, m_strAccessKey, NET_SDK_ACCESS_KEY_LEN);
    memcpy(m_struServerTestPara.unionServerPara.struCloudStoragePara.szSecretKey, m_strSecretKey, NET_SDK_SECRET_KEY_LEN);

    m_lCloudServerTest = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_CLOUDSTORAGE_SERVER_TEST, &m_struServerTestPara, sizeof(m_struServerTestPara), NULL, this);
    if (m_lCloudServerTest >= 0)
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_CLOUDSTORAGE_SERVER_TEST Start Remote Config successfully");
        DWORD dwThreadId;
        CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetCloudServerTestInfoThread), this, 0, &dwThreadId);
    } 
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_CLOUDSTORAGE_SERVER_TEST Start Remote Config failed");
        return;
	}
}

DWORD WINAPI CDlgCloudStoragePhoneTest::GetPhoneTestInfoThread(LPVOID lpArg)
{
    CDlgCloudStoragePhoneTest* pThis = reinterpret_cast<CDlgCloudStoragePhoneTest*>(lpArg);
    DWORD dwState = 0;
    CString csErrInfo;
    while (1)
    {
        
        if (!NET_DVR_GetRemoteConfigState(pThis->m_lPhoneTest, &dwState))
        {
            g_pMainDlg->AddLog(pThis->m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GetRemoteConfigState NET_DVR_FIND_NAS_DIRECTORY ");
            pThis->GetDlgItem(IDC_STATIC_FTP_SERVER_TEST)->SetWindowText("Get state Fail!");
            NET_DVR_StopRemoteConfig(pThis->m_lPhoneTest);
            return -1;
        }
        else
        {
            if (dwState == PROCESSING)
            {
                pThis->GetDlgItem(IDC_STATIC_FTP_SERVER_TEST)->SetWindowText("Testing...");
                Sleep(1000);
            }
            else if (dwState == PROCESS_SUCCESS)
            {
                pThis->GetDlgItem(IDC_STATIC_FTP_SERVER_TEST)->SetWindowText("Test Success!");
                break;
            }
            else if (dwState == PROCESS_EXCEPTION)
            {
                pThis->GetDlgItem(IDC_STATIC_FTP_SERVER_TEST)->SetWindowText("Test Exception!!");
                break;
            }
            else
            {
                csErrInfo.Format("Test Fail %d", dwState);
                pThis->GetDlgItem(IDC_STATIC_FTP_SERVER_TEST)->SetWindowText(csErrInfo);
                break;
            }
        }
        
    }
    if (-1 != pThis->m_lPhoneTest)
    {
        if (!NET_DVR_StopRemoteConfig(pThis->m_lPhoneTest))
        {
            g_pMainDlg->AddLog(pThis->m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_PHONE_NUM_TEST Stop Remote Config Failed");
        }
        else
        {
            g_pMainDlg->AddLog(pThis->m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_PHONE_NUM_TEST Stop Remote Config Successful");
            pThis->m_lPhoneTest = -1;
        }
    }
    return 0 ;
}

void CDlgCloudStoragePhoneTest::OnBtnPhoneTest() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

	m_struPhoneTestPara.dwSize = sizeof(m_struPhoneTestPara);
    memcpy(m_struPhoneTestPara.unionServerPara.struPhoneNumPara.byPhoneNum, m_csPhoneNum, MAX_PHONE_NUM);

    m_lPhoneTest = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_PHONE_NUM_TEST, &m_struPhoneTestPara, sizeof(m_struPhoneTestPara), NULL, this);
    if (m_lPhoneTest >= 0)
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_PHONE_NUM_TEST Start Remote Config successfully");
        DWORD dwThreadId;
        CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetPhoneTestInfoThread), this, 0, &dwThreadId);
    } 
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_PHONE_NUM_TEST Start Remote Config failed");
        return;
	}
}

void CDlgCloudStoragePhoneTest::OnSelchangeComboPoolparam() 
{
	// TODO: Add your control notification handler code here
    m_dwPoolID = m_struServerTestPara.unionServerPara.struCloudStoragePara.struPoolInfo[m_comPoolParam.GetCurSel()].dwPoolID;
	UpdateData(FALSE);
}

BOOL CDlgCloudStoragePhoneTest::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_comPoolParam.SetCurSel(0);
    m_comboProtocolType.SetCurSel(0);
    OnSelchangeComboPoolparam();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCloudStoragePhoneTest::OnBtnCloudSave() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
	m_struServerTestPara.unionServerPara.struCloudStoragePara.struPoolInfo[m_comPoolParam.GetCurSel()].dwPoolID = m_dwPoolID;
}
