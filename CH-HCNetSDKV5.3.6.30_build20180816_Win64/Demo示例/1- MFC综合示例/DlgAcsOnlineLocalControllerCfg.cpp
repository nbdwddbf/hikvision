// DlgAcsOnlineLocalControllerCfg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgAcsOnlineLocalControllerCfg.h"
#include "afxdialogex.h"


// CDlgAcsOnlineLocalControllerCfg 对话框

IMPLEMENT_DYNAMIC(CDlgAcsOnlineLocalControllerCfg, CDialogEx)

void CALLBACK g_fGetLocalControlLerCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData);
#define WM_MSG_GET_LOCALCONTROLLER_FINISH 1003
#define WM_MSG_ADD_LOCALCONTROLLER_TOLIST 1004
#define WM_MSG_UPDATEDATA_INTERFACE   1005

CDlgAcsOnlineLocalControllerCfg::CDlgAcsOnlineLocalControllerCfg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgAcsOnlineLocalControllerCfg::IDD, pParent)
{
	m_lServerID = -1;
	m_iDevIndex = -1;
	m_lGetLocalControllerHandle = -1;
	m_iListIndex = -1;
}

CDlgAcsOnlineLocalControllerCfg::~CDlgAcsOnlineLocalControllerCfg()
{
}

void CDlgAcsOnlineLocalControllerCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ONLINE_LOCAL_CONTROLLER, m_listOnlineLocalController);
}


BEGIN_MESSAGE_MAP(CDlgAcsOnlineLocalControllerCfg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CDlgAcsOnlineLocalControllerCfg::OnBnClickedButtonSearch)
	ON_MESSAGE(WM_MSG_GET_LOCALCONTROLLER_FINISH, OnMsgGetLocalControllerFinish)
	ON_MESSAGE(WM_MSG_ADD_LOCALCONTROLLER_TOLIST, OnMsgAddLocalControllerToList)
	ON_MESSAGE(WM_MSG_UPDATEDATA_INTERFACE, OnMsgUpdateData)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgAcsOnlineLocalControllerCfg 消息处理程序

BOOL CDlgAcsOnlineLocalControllerCfg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	char szLan[64] = { 0 };

	m_listOnlineLocalController.DeleteAllItems();
	g_StringLanType(szLan, "序号", "No");
	m_listOnlineLocalController.InsertColumn(0, szLan, LVCFMT_LEFT, 40);
	g_StringLanType(szLan, "就地控制器名称", "LocalControllerName");
	m_listOnlineLocalController.InsertColumn(1, szLan, LVCFMT_LEFT, 120);
	g_StringLanType(szLan, "就地控制器序号", "LocalControllerNo");
	m_listOnlineLocalController.InsertColumn(2, szLan, LVCFMT_LEFT, 60);
	g_StringLanType(szLan, "设备端口号", "DevPort");
	m_listOnlineLocalController.InsertColumn(3, szLan, LVCFMT_LEFT, 60);
	g_StringLanType(szLan, "设备IP地址", "DevIP");
	m_listOnlineLocalController.InsertColumn(4, szLan, LVCFMT_LEFT, 100);
	g_StringLanType(szLan, "设备子网掩码", "SubnetMask");
	m_listOnlineLocalController.InsertColumn(5, szLan, LVCFMT_LEFT, 80);
	g_StringLanType(szLan, "设备网关", "Gateway");
	m_listOnlineLocalController.InsertColumn(6, szLan, LVCFMT_LEFT, 120);
	g_StringLanType(szLan, "搜索进度", "SearchProgress");
	m_listOnlineLocalController.InsertColumn(7, szLan, LVCFMT_LEFT, 80);
	m_listOnlineLocalController.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CALLBACK g_fGetLocalControlLerCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
	CDlgAcsOnlineLocalControllerCfg* pDlg = (CDlgAcsOnlineLocalControllerCfg*)pUserData;
	if (pDlg == NULL)
	{
		return;
	}
	pDlg->ProcessGetLocalControllerCallbackData(dwType, lpBuffer, dwBufLen);
}

LRESULT CDlgAcsOnlineLocalControllerCfg::OnMsgGetLocalControllerFinish(WPARAM wParam, LPARAM lParam)
{
	NET_DVR_StopRemoteConfig(m_lGetLocalControllerHandle);
	m_lGetLocalControllerHandle = -1;
	g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ONLINE_LOCAL_CONTROLLER Get finish");
	return 0;
}

LRESULT CDlgAcsOnlineLocalControllerCfg::OnMsgAddLocalControllerToList(WPARAM wParam, LPARAM lParam)
{
	LPNET_DVR_ONLINE_LOCAL_CONTROLLER_CFG lpLocalControllerCfg = (LPNET_DVR_ONLINE_LOCAL_CONTROLLER_CFG)wParam;
	if (lpLocalControllerCfg->dwSize == 0)
	{
		return 0;
	}
	AddToLocalControllerList(*lpLocalControllerCfg, lpLocalControllerCfg->wLocalControllerID);
	delete lpLocalControllerCfg;
	return 0;
}

LRESULT CDlgAcsOnlineLocalControllerCfg::OnMsgUpdateData(WPARAM wParam, LPARAM lParam)
{
	DWORD dwTrue = (DWORD)wParam;
	UpdateData(dwTrue);
	return 0;
}

void CDlgAcsOnlineLocalControllerCfg::AddToLocalControllerList(const NET_DVR_ONLINE_LOCAL_CONTROLLER_CFG& struLocalControllerInfo, const WORD wLocalControllerNo)
{
	LPNET_DVR_ONLINE_LOCAL_CONTROLLER_CFG pLocalControllerCfg = NULL;
	CString strItem = "";
	char szLan[64] = { 0 };
	if (m_listOnlineLocalController.GetItemCount() > m_iListIndex + 1)
	{
		m_iListIndex = m_listOnlineLocalController.GetItemCount();
		pLocalControllerCfg = (LPNET_DVR_ONLINE_LOCAL_CONTROLLER_CFG)m_listOnlineLocalController.GetItemData(m_iListIndex);
	}
	else
	{
		pLocalControllerCfg = new NET_DVR_ONLINE_LOCAL_CONTROLLER_CFG;
		m_iListIndex = m_listOnlineLocalController.GetItemCount();
		strItem.Format("%d", m_iListIndex + 1);
		m_listOnlineLocalController.InsertItem(m_iListIndex, strItem);
	}
	if (m_iListIndex < 0)
	{
		return;
	}
	memcpy(pLocalControllerCfg, &struLocalControllerInfo, sizeof(struLocalControllerInfo));
	if (0 == struLocalControllerInfo.byEffectData)
	{
		m_listOnlineLocalController.SetItemData(m_iListIndex, (DWORD)pLocalControllerCfg);
        strncpy(szLan, (char*)struLocalControllerInfo.byLocalControllerName, LOCAL_CONTROLLER_NAME_LEN);
        m_listOnlineLocalController.SetItemText(m_iListIndex, 1, szLan);
		strItem.Format("%d", struLocalControllerInfo.wLocalControllerID);
		m_listOnlineLocalController.SetItemText(m_iListIndex, 2, strItem);
		strItem.Format("%d", struLocalControllerInfo.wDevPort);
		m_listOnlineLocalController.SetItemText(m_iListIndex, 3, strItem);
		m_listOnlineLocalController.SetItemText(m_iListIndex, 4, (char*)struLocalControllerInfo.struDevIP.sIpV4);
		m_listOnlineLocalController.SetItemText(m_iListIndex, 5, (char*)struLocalControllerInfo.struSubnetMask.sIpV4);
		m_listOnlineLocalController.SetItemText(m_iListIndex, 6, (char*)struLocalControllerInfo.struGateway.sIpV4);
		strItem.Format("%d", struLocalControllerInfo.bySearchProgress);
		m_listOnlineLocalController.SetItemText(m_iListIndex, 7, strItem);

		m_iListIndex++;
	}
	else if (1 == struLocalControllerInfo.byEffectData)
	{
		m_listOnlineLocalController.SetItemData(m_iListIndex, (DWORD)pLocalControllerCfg);
		g_StringLanType(szLan, "搜索中", "Searching");
		m_listOnlineLocalController.SetItemText(m_iListIndex, 1, szLan);
		strItem.Format("%d", struLocalControllerInfo.bySearchProgress);
		m_listOnlineLocalController.SetItemText(m_iListIndex, 7, strItem);
	}

	UpdateData(FALSE);
}

void CDlgAcsOnlineLocalControllerCfg::ProcessGetLocalControllerCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{
	if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
	{
		LPNET_DVR_ONLINE_LOCAL_CONTROLLER_CFG lpLocalControllerCfg = new NET_DVR_ONLINE_LOCAL_CONTROLLER_CFG;
		memcpy(lpLocalControllerCfg, lpBuffer, sizeof(*lpLocalControllerCfg));
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "GetOnlineLocalController PROCESSING");
		PostMessage(WM_MSG_ADD_LOCALCONTROLLER_TOLIST, (WPARAM)lpLocalControllerCfg, 0);
	}
	else if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
	{
		DWORD dwStatus = *(DWORD*)lpBuffer;
		if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
		{
			PostMessage(WM_MSG_GET_LOCALCONTROLLER_FINISH, 0, 0);
		}
		else if (dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "GetOnlineLocalController STATUS_FAILED");
		}
	}
}

void CDlgAcsOnlineLocalControllerCfg::OnBnClickedButtonSearch()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_lGetLocalControllerHandle != -1)
	{
		NET_DVR_StopRemoteConfig(m_lGetLocalControllerHandle);
	}
	m_listOnlineLocalController.DeleteAllItems();
	UpdateData(TRUE);

	m_lGetLocalControllerHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_GET_ONLINE_LOCAL_CONTROLLER, NULL, 0, g_fGetLocalControlLerCallback, this);
	if (m_lGetLocalControllerHandle == -1)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ONLINE_LOCAL_CONTROLLER");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ONLINE_LOCAL_CONTROLLER");
	}
}


void CDlgAcsOnlineLocalControllerCfg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (m_lGetLocalControllerHandle != -1)
	{
		NET_DVR_StopRemoteConfig(m_lGetLocalControllerHandle);
		m_lGetLocalControllerHandle = -1;
	}
	CDialogEx::OnClose();
}
