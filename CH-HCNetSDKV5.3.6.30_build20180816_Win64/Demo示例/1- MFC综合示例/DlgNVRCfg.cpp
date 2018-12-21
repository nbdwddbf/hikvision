// DlgNVRCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgNVRCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNVRCfg dialog


CDlgNVRCfg::CDlgNVRCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNVRCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNVRCfg)
	m_strIPCIP = _T("");
	m_wPort = 0;
	m_strNewPasswd = _T("");
	m_strIPCNetFlow = _T("");
	m_strRWNetFlow = _T("");
	m_strPlaybackNetFlow = _T("");
	m_strPreviewNetFlow = _T("");
	m_strOldPasswd = _T("");
	m_bSynIPC = FALSE;
	m_bRaid = FALSE;
	m_dwRaidID = 0;
	m_lPullDiskHandle = -1;
	m_lScanRaidHandle = -1;
	m_strPullDiskState = _T("");
	m_strScanRaidState = _T("");
	m_bSleep = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgNVRCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNVRCfg)
	DDX_Text(pDX, IDC_DLG_NVR_CFG_EDIT_IP, m_strIPCIP);
	DDX_Text(pDX, IDC_DLG_NVR_CFG_EDIT_PORT, m_wPort);
	DDX_Text(pDX, IDC_DLG_NVR_CFG_EDIT_NEW_PASSWD, m_strNewPasswd);
	DDX_Text(pDX, IDC_DLG_NVR_CFG_STATIC_IPC, m_strIPCNetFlow);
	DDX_Text(pDX, IDC_DLG_NVR_CFG_STATIC_NET_RW, m_strRWNetFlow);
	DDX_Text(pDX, IDC_DLG_NVR_CFG_STATIC_PLAYBACK, m_strPlaybackNetFlow);
	DDX_Text(pDX, IDC_DLG_NVR_CFG_STATIC_PREVIEW, m_strPreviewNetFlow);
	DDX_Text(pDX, IDC_EDIT_OLD_PASSWD, m_strOldPasswd);
	DDX_Check(pDX, IDC_CHECK_SYN, m_bSynIPC);
	DDX_Check(pDX, IDC_CHECK_RAID, m_bRaid);
	DDX_Text(pDX, IDC_EDIT_RAID_ID, m_dwRaidID);
	DDV_MinMaxDWord(pDX, m_dwRaidID, 0, 65535);
	DDX_Text(pDX, IDC_STATIC_PULL_DISK_STATE, m_strPullDiskState);
	DDX_Text(pDX, IDC_STATIC_SCAN_RAID_STATE, m_strScanRaidState);
	DDX_Check(pDX, IDC_CHECK_SLEEP, m_bSleep);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNVRCfg, CDialog)
	ON_MESSAGE(MSG_PULL_DISK_STATE, OnPullDiskState)
	ON_MESSAGE(MSG_SCAN_RAID_STATE, OnScanRaidState)
	//{{AFX_MSG_MAP(CDlgNVRCfg)
	ON_BN_CLICKED(IDC_BTN_UPDATE, OnBtnUpdate)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_SET_RAID, OnBtnSetRaid)
	ON_BN_CLICKED(IDC_BTN_SECURE_PULL_DISK, OnBtnSecurePullDisk)
	ON_BN_CLICKED(IDC_BTN_SCAN_RAID, OnBtnScanRaid)
	ON_BN_CLICKED(IDC_BUTTON_STOP_PULL_DISK, OnButtonStopPullDisk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNVRCfg message handlers

BOOL CDlgNVRCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitWnd();

// 	pPullDiskState = (CStatic*)GetDlgItem(IDC_STATIC_PULL_DISK_STATE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//Init window.
void CDlgNVRCfg::InitWnd()
{
    UpdateData(FALSE);
	int iRet = -1;
    DWORD uiReturnLen = 0;
	char szLan[128] = {0};

	//get whether synchronous.
    NET_DVR_SYNCHRONOUS_IPC struParams = {0};
    struParams.dwSize = sizeof(struParams);
    iRet = NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_DVR_SYNCHRONOUS_IPC, m_lChannel, \
        &struParams, sizeof(NET_DVR_SYNCHRONOUS_IPC), &uiReturnLen);
    if (!iRet)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_DVR_SYNCHRONOUS_IPC m_lChannel[%d]", m_lChannel);	
		g_StringLanType(szLan, "获取同步参数失败", "Get asychronous parameter failed.");
		AfxMessageBox(szLan);
		return;
    }
	m_bSynIPC = struParams.byEnable;


	NET_DVR_DISK_RAID_INFO struRaidParams = {0};
    struRaidParams.dwSize = sizeof(struRaidParams);
    iRet = NET_DVR_GetDVRConfig(m_lUserID,  NET_DVR_GET_DISK_RAID_INFO, 0, \
        &struRaidParams, sizeof(NET_DVR_DISK_RAID_INFO), &uiReturnLen);
    if (!iRet)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_DISK_RAID_INFO m_lChannel[%d]", m_lChannel);	
		g_StringLanType(szLan, "获取Raid参数失败", "Get raid parameter failed.");
		AfxMessageBox(szLan);
    }
	m_bRaid = struRaidParams.byEnable;
	m_bSleep  = struRaidParams.bySleepStatus;
	//Net using
    OnBtnUpdate();
}

void CDlgNVRCfg::OnBtnUpdate() 
{
	// TODO: Add your control notification handler code here
	
	DWORD uiReturnLen = 0;
	char szLan[128] = {0};

	NET_DVR_DEVICE_NET_USING_INFO struParams = {0};
    struParams.dwSize = sizeof(NET_DVR_DEVICE_NET_USING_INFO);
	int iRet = NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_DEVICE_NET_USING_INFO, 0, \
        &struParams, sizeof(NET_DVR_DEVICE_NET_USING_INFO), &uiReturnLen);
    if (!iRet)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_DEVICE_NET_USING_INFO ");	
		g_StringLanType(szLan, "获取设备网络使用状况", "Get net information of the device failed.");
		AfxMessageBox(szLan);
		return;
    }

	m_strPreviewNetFlow.Format("%d", struParams.dwPreview);
    m_strPlaybackNetFlow.Format("%d", struParams.dwPlayback);
	m_strRWNetFlow.Format("%d", struParams.dwNetDiskRW);
	m_strIPCNetFlow.Format("%d", struParams.dwIPCModule);

	UpdateData(FALSE);
}

void CDlgNVRCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
	//Set synchronous
	int iRet = -1;
    DWORD uiReturnLen = 0;
	char szLan[128] = {0};
	
    NET_DVR_SYNCHRONOUS_IPC struSynParams = {0};
    struSynParams.dwSize = sizeof(struSynParams);
    struSynParams.byEnable = m_bSynIPC;
    iRet = NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_DVR_SYNCHRONOUS_IPC, m_lChannel, \
        &struSynParams, sizeof(NET_DVR_SYNCHRONOUS_IPC));
    if (!iRet)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_DVR_SYNCHRONOUS_IPC");	
		g_StringLanType(szLan, "设置同步参数失败", "Set net information of the device failed.");
		AfxMessageBox(szLan);
		return;
    }

	//Set user name
	NET_DVR_IPC_PASSWD struPasswdParams = {0};
    struPasswdParams.dwSize = sizeof(NET_DVR_IPC_PASSWD);
	strncpy(struPasswdParams.sOldPasswd, m_strOldPasswd.GetBuffer(0), sizeof(struPasswdParams.sOldPasswd));
    strncpy(struPasswdParams.sNewPasswd, m_strNewPasswd.GetBuffer(0), sizeof(struPasswdParams.sNewPasswd));
    iRet = NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_DVR_IPC_PASSWD, m_lChannel, &struPasswdParams, sizeof(NET_DVR_IPC_PASSWD));
    if (!iRet)
    {
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_DVR_IPC_PASSWD");	
		g_StringLanType(szLan, "设置用户名密码错误", "Set passwd failed.");
		AfxMessageBox(szLan);
		return;
    }

	//Set IPC
	NET_DVR_IPC_NETCFG struNetParams = {0};
    struNetParams.dwSize = sizeof(NET_DVR_IPC_NETCFG);
    strncpy(struNetParams.struIP.sIpV4,  m_strIPCIP.GetBuffer(0), sizeof(struNetParams.struIP.sIpV4));
    struNetParams.wPort = m_wPort;

    iRet = NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_DVR_IPC_NET, m_lChannel, &struNetParams, sizeof(NET_DVR_IPC_NETCFG));
    if (!iRet)
    {
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_DVR_IPC_NET");	
		g_StringLanType(szLan, "设置网络参数错误", "Set net parameter failed.");
		AfxMessageBox(szLan);
		return;
    }
}

void CDlgNVRCfg::OnBtnSetRaid() 
{
	 UpdateData(TRUE);

	// TODO: Add your control notification handler code here
	NET_DVR_DISK_RAID_INFO struParams = {0};
    struParams.dwSize = sizeof(struParams);
	char szLan[128] = {0};
	
	struParams.byEnable = m_bRaid;
	struParams.bySleepStatus = m_bSleep;
    //get
    BOOL bRet = NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_DISK_RAID_INFO, 0, \
        &struParams, sizeof(NET_DVR_DISK_RAID_INFO));
    if (!bRet)
    {
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_DISK_RAID_INFO");	
		g_StringLanType(szLan, "设置磁盘raid错误", "Set disk raid failed.");
		AfxMessageBox(szLan);
    }

}

LRESULT CDlgNVRCfg::OnPullDiskState(WPARAM wParam, LPARAM lParam)
{
	DWORD dwState = *(DWORD *)wParam;
	switch (dwState)
	{
	case PULL_DISK_SUCCESS:
		m_strPullDiskState = "安全拔盘成功";
		break;
	case PULL_DISK_FAIL:
		m_strPullDiskState = "安全拔盘失败";
		break;
	case PULL_DISK_PROCESSING:
		m_strPullDiskState = "安全拔盘正在处理...";
		break;
	case PULL_DISK_NO_ARRAY:
		m_strPullDiskState = "安全拔盘阵列不存在";
		break;
	case PULL_DISK_NOT_SUPPORT:
		m_strPullDiskState = "安全拔盘不支持";
		break;
	default:
		m_strPullDiskState = "安全拔盘不支持";
		break;
	}

	UpdateData(FALSE);
	return NULL;
}

LRESULT CDlgNVRCfg::OnScanRaidState(WPARAM wParam, LPARAM lParam)
{
	DWORD dwState = *(DWORD *)wParam;
	switch (dwState)
	{
	case SCAN_RAID_SUC:
	 	m_strScanRaidState = "扫描阵列成功";
	 	break;
	case SCAN_RAID_FAIL:
	 	m_strScanRaidState = "扫描阵列失败";
	 	break;
	case SCAN_RAID_PROCESSING:
	 	m_strScanRaidState = "扫描阵列正在处理...";
	 	break;
	case SCAN_RAID_NOT_SUPPORT:
	 	m_strScanRaidState = "扫描阵列不支持";
	 	break;
	default:
	 	m_strScanRaidState = "扫描阵列不支持";
	 	break;
 
	}
	
	UpdateData(FALSE);
	return NULL;
}

void __stdcall PullDiskStateCallBack(LONG iHandle, DWORD dwState, LPVOID pUser)
{
	CDlgNVRCfg *pThis = (CDlgNVRCfg*)pUser;
	HWND hWnd = pThis->GetSafeHwnd();
	if (NULL == hWnd)
	{
		return;
	}

	::SendMessage(hWnd, MSG_PULL_DISK_STATE, (WPARAM)&dwState, NULL);

	
}

void __stdcall ScanRaidStateCallBack(LONG iHandle, DWORD dwState, LPVOID pUser)
{
	CDlgNVRCfg *pThis = (CDlgNVRCfg*)pUser;
	HWND hWnd = pThis->GetSafeHwnd();
	if (NULL == hWnd)
	{
		return;
	}

	::SendMessage(hWnd, MSG_SCAN_RAID_STATE, (WPARAM)&dwState, NULL);
}

/*********************************************************
Function:	OnBtnSecurePullDisk
Desc:		start secure pull disk.
Input:	
Output:	
Return:	
**********************************************************/
void CDlgNVRCfg::OnBtnSecurePullDisk() 
{
	UpdateData(TRUE);
	
	char szLan[128] = {0};

	m_lPullDiskHandle = NET_DVR_RaidPullDiskStart(m_lUserID, m_dwRaidID, PullDiskStateCallBack, this);
	if (-1 == m_lPullDiskHandle)
	{
	 	g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RaidPullDiskStart");	
	 	g_StringLanType(szLan, "安全拔盘失败", "Secure pull disk failed.");
	 	AfxMessageBox(szLan);
 	}

	m_strPullDiskState = "";
	UpdateData(FALSE);
}

void CDlgNVRCfg::OnBtnScanRaid() 
{
	char szLan[128] = {0};
	m_lScanRaidHandle = NET_DVR_ScanRaidStart(m_lUserID, ScanRaidStateCallBack, this);
	if (-1 == m_lScanRaidHandle)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_ScanRaidStart");	
		g_StringLanType(szLan, "扫描阵列失败", "Scan raid failed.");
		AfxMessageBox(szLan);
	}
	m_strScanRaidState = "";
	UpdateData(FALSE);
}

void CDlgNVRCfg::OnButtonStopPullDisk() 
{
	// TODO: Add your control notification handler code here
// 	if (m_lPullDiskHandle != -1)
// 	{
// 		NET_DVR_ScanRaidDiskStop(m_lScanRaidHandle);
// 	}
}
