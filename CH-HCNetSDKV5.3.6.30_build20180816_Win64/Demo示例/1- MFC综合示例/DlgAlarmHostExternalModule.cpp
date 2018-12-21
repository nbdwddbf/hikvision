// DlgAlarmHostExternalModule.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmHostExternalModule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostExternalModule dialog


CDlgAlarmHostExternalModule::CDlgAlarmHostExternalModule(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmHostExternalModule::IDD, pParent)
, m_iDeviceIndex(-1)
, m_lUserID(-1)
, m_lHandle(-1)
{
	//{{AFX_DATA_INIT(CDlgAlarmHostExternalModule)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgAlarmHostExternalModule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmHostExternalModule)
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmHostExternalModule, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmHostExternalModule)
	ON_BN_CLICKED(IDC_BTN_AUTO_SEARCH, OnBtnAutoSearch)
	ON_BN_CLICKED(IDC_BTN_REGISTER, OnBtnRegister)
	ON_MESSAGE(WM_PROC_ALARMHOST_EXTERNAL_MODULE, OnGetProgress)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostExternalModule message handlers

void CALLBACK g_ExternModuleCallback(DWORD dwDataType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
	DWORD	dwStatus = 0;
	DWORD	dwProgress = 0;
	CDlgAlarmHostExternalModule *pThis = static_cast<CDlgAlarmHostExternalModule*>(pUserData);
	HWND hWnd = pThis->GetSafeHwnd();
	if (NULL == hWnd)
	{
		return;
	}
	
	switch (dwDataType)
	{
	case NET_SDK_CALLBACK_TYPE_PROGRESS:
		dwProgress = *((DWORD*)lpBuffer);
		::PostMessage(hWnd, WM_PROC_ALARMHOST_EXTERNAL_MODULE, (DWORD)NET_SDK_CALLBACK_TYPE_PROGRESS, dwProgress);
		break;
	case NET_SDK_CALLBACK_TYPE_STATUS:
		dwStatus = *(DWORD*)lpBuffer;
		//dwProgress = *(((DWORD*)lpBuffer) + 1);
		if (dwStatus==NET_SDK_CALLBACK_STATUS_SUCCESS)
		{
			::PostMessage(hWnd, WM_PROC_ALARMHOST_EXTERNAL_MODULE, (DWORD)NET_SDK_CALLBACK_TYPE_STATUS, (DWORD)NET_SDK_CALLBACK_STATUS_SUCCESS);
		}
		else
		{
			::PostMessage(hWnd, WM_PROC_ALARMHOST_EXTERNAL_MODULE, (DWORD)NET_SDK_CALLBACK_TYPE_STATUS, (DWORD)NET_SDK_CALLBACK_STATUS_FAILED);
		}	
		break;
	default:
		g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_FAIL_T, "Unknown Status");
		break;
	}
}

BOOL CDlgAlarmHostExternalModule::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlarmHostExternalModule::OnBtnAutoSearch() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	if (m_lHandle>=0)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "It is searching, wait for a moment");
	}
	else
	{
		m_progress.SetPos(0);
		g_StringLanType(szLan, "进度", "progress");
		sprintf(szLan, "%s %%%d", szLan, 0);
		SetDlgItemText(IDC_STATIC_PROGRESS, szLan);
		m_lHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_SEARCH_ARMHOST_EXTERNAL_MODULE, NULL, 0, g_ExternModuleCallback, this);
		if (m_lHandle>=0)
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Start Remote Config successfully");
			GetDlgItem(IDC_BTN_AUTO_SEARCH)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_REGISTER)->EnableWindow(FALSE);
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Start Remote Config failed");
			return;
		}
	}
}

void CDlgAlarmHostExternalModule::OnBtnRegister() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	if (m_lHandle>=0)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "It is searching, wait for a moment");
	}
	else
	{
		m_progress.SetPos(0);
		g_StringLanType(szLan, "进度", "progress");
		sprintf(szLan, "%s %%%d", szLan, 0);
		SetDlgItemText(IDC_STATIC_PROGRESS, szLan);
		m_lHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_REGISTER_ALARMHOST_EXTERNAL_MODULE, NULL, 0, g_ExternModuleCallback, this);
		if (m_lHandle>=0)
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Start Remote Config successfully");
			GetDlgItem(IDC_BTN_AUTO_SEARCH)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_REGISTER)->EnableWindow(FALSE);
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Start Remote Config failed");
			return;
		}
	}
}

LRESULT CDlgAlarmHostExternalModule::OnGetProgress(WPARAM wParam, LPARAM lParam)
{
	//CDlgMatrixDispRoute* pDispRoute = reinterpret_cast<CDlgMatrixDispRoute*>(wParam);
	char szLan[128] = {0};
	DWORD dwDataType = (DWORD)wParam;
	DWORD dwProgress = 0;
	DWORD dwStatus = 0;
	
	switch (dwDataType)
	{
	case NET_SDK_CALLBACK_TYPE_PROGRESS:
		dwProgress = (DWORD)lParam;
		g_StringLanType(szLan, "进度", "progress");
		sprintf(szLan, "%s %%%d", szLan, dwProgress);
		SetDlgItemText(IDC_STATIC_PROGRESS, szLan);
		m_progress.SetPos(dwProgress);
		break;
	case NET_SDK_CALLBACK_TYPE_STATUS:
		dwStatus = (DWORD)lParam;
		if (NET_SDK_CALLBACK_STATUS_SUCCESS == dwStatus)
		{
			g_StringLanType(szLan, "搜索/注册成功", "search or register successful");
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szLan);
		}
		else 
		{
			g_StringLanType(szLan, "搜索/注册失败", "search or register failed");
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "operate failed");
		}
		if (!NET_DVR_StopRemoteConfig(m_lHandle))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Stop Remote Config Failed");
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Stop Remote Config Successful");
			GetDlgItem(IDC_BTN_AUTO_SEARCH)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_REGISTER)->EnableWindow(TRUE);
			m_lHandle = -1;
		}
		break;
	default:
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Unknown Status");
		break;
	}
	return NULL;
}

void CDlgAlarmHostExternalModule::OnBtnStop() 
{
	// TODO: Add your control notification handler code here

	char szLan[128] = {0};
	if (!NET_DVR_StopRemoteConfig(m_lHandle))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Stop Remote Config Failed");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Stop Remote Config Successful");
		GetDlgItem(IDC_BTN_AUTO_SEARCH)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_REGISTER)->EnableWindow(TRUE);
		g_StringLanType(szLan, "进度", "progress");
		sprintf(szLan, "%s %%%d", szLan, 0);
		SetDlgItemText(IDC_STATIC_PROGRESS, szLan);
		m_progress.SetPos(0);
		m_lHandle = -1;
	}
}
