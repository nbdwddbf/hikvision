// DlgGetWifiClientListInfo.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgGetWifiClientListInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGetWifiClientListInfo dialog


DWORD WINAPI CDlgGetWifiClientListInfo::GetConfigThread(LPVOID lpArg)
{
	CDlgGetWifiClientListInfo* pThis = reinterpret_cast<CDlgGetWifiClientListInfo*>(lpArg);
	int bRet = 0;
	char szLan[128] = {0};
	while(pThis->m_bGetNext)
	{
		bRet = NET_DVR_GetNextRemoteConfig(pThis->m_lHandle, &pThis->m_struWifiClientInfo, sizeof(pThis->m_struWifiClientInfo));
		if (bRet == NET_SDK_GET_NEXT_STATUS_SUCCESS)
		{
			pThis->AddInfoToDlg();  
		}
		else
		{
			if (bRet == NET_SDK_GET_NETX_STATUS_NEED_WAIT)
			{
				Sleep(5);
				continue;
			}
			if (bRet == NET_SDK_GET_NEXT_STATUS_FINISH)
			{
				g_StringLanType(szLan, "获取配置结束!", "Get route info Ending");
				g_pMainDlg->AddLog(pThis->m_dwDevIndex, OPERATION_SUCC_T, szLan);
				//AfxMessageBox(szLan);
				break;
			}
			else if(bRet == NET_SDK_GET_NEXT_STATUS_FAILED)
			{
				g_StringLanType(szLan, "获取配置失败!", "Get route info failed");
				AfxMessageBox(szLan);
				break;
			}
			else
			{
				g_StringLanType(szLan, "未知状态", "Unknown status");
				AfxMessageBox(szLan);
				break;
			}
		}
	}
	if (-1 != pThis->m_lHandle)
	{
		if (!NET_DVR_StopRemoteConfig(pThis->m_lHandle))
		{
			g_pMainDlg->AddLog(pThis->m_dwDevIndex, OPERATION_FAIL_T, "Stop Remote Config Failed");
			pThis->m_bGetNext = FALSE;
		}
		else
		{
			g_pMainDlg->AddLog(pThis->m_dwDevIndex, OPERATION_SUCC_T, "Stop Remote Config Successful");
			pThis->m_bGetNext = FALSE;
			pThis->m_lHandle = -1;
		}
	}
	return 0 ;
}

void CDlgGetWifiClientListInfo::AddInfoToDlg() 
{
	//IP地址
	sprintf(m_sTemp, "%s", (char*)m_struWifiClientInfo.struAddress.sIpV4, 16);
	m_listClientInfo.InsertItem(m_iRowCount,m_sTemp);
	
	//MAC地址
	sprintf(m_sTemp, "%02x:%02x:%02x:%02x:%02x:%02x", m_struWifiClientInfo.byMACAddr[0], m_struWifiClientInfo.byMACAddr[1]\
        , m_struWifiClientInfo.byMACAddr[2], m_struWifiClientInfo.byMACAddr[3]\
        , m_struWifiClientInfo.byMACAddr[4], m_struWifiClientInfo.byMACAddr[5]);
	m_listClientInfo.SetItemText(m_iRowCount, 1, m_sTemp);
	
	//连接速度
	if(0xffff == m_struWifiClientInfo.wConnSpeed)
	{
		sprintf(m_sTemp, "%s", "--");
	}
	else
	{
		sprintf(m_sTemp, "%d", m_struWifiClientInfo.wConnSpeed);
	}
	m_listClientInfo.SetItemText(m_iRowCount, 2, m_sTemp);
	
	//信号强度
	if(0xff == m_struWifiClientInfo.byRSSIValue)
	{
		sprintf(m_sTemp, "%s", "--");
	}
	else
	{
		sprintf(m_sTemp, "%d", m_struWifiClientInfo.byRSSIValue * -1);
	}
	m_listClientInfo.SetItemText(m_iRowCount, 3, m_sTemp);
	
	//网络带宽
	if(0xffff == m_struWifiClientInfo.wBandwidth)
	{
		sprintf(m_sTemp, "%s", "--");
	}
	else
	{
		sprintf(m_sTemp, "%d", m_struWifiClientInfo.wBandwidth);
	}
	m_listClientInfo.SetItemText(m_iRowCount, 4, m_sTemp);
	
	m_iRowCount++;
}


CDlgGetWifiClientListInfo::CDlgGetWifiClientListInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGetWifiClientListInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGetWifiClientListInfo)
	//}}AFX_DATA_INIT
	memset(&m_struWifiClientInfo,0,sizeof(m_struWifiClientInfo));
	m_lHandle = -1;
}


void CDlgGetWifiClientListInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGetWifiClientListInfo)
	DDX_Control(pDX, IDC_LIST_CLIENT_INFO, m_listClientInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGetWifiClientListInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgGetWifiClientListInfo)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGetWifiClientListInfo message handlers

void CDlgGetWifiClientListInfo::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	 
	m_listClientInfo.DeleteAllItems();
	m_iRowCount = 0;
	if (m_lHandle>=0)
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "It is getting data, wait for a moment");
	}
	else
	{
		m_lHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_GET_WIFI_CLIENT_LIST_INFO, NULL, 0, NULL, this);
		if (m_lHandle>=0)
		{
			m_bGetNext = TRUE;
			g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "Start Remote Config successfully");
			DWORD dwThreadId;
			m_hGetInfoThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetConfigThread), this, 0, &dwThreadId);
		}
		else
		{
			g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "Start Remote Config failed");
			return;
		}
	}
}

BOOL CDlgGetWifiClientListInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_listClientInfo.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listClientInfo.InsertColumn(0, "IP地址", LVCFMT_LEFT, 120, -1);
	m_listClientInfo.InsertColumn(1,"MAC地址", LVCFMT_LEFT, 150, -1);
	m_listClientInfo.InsertColumn(2,"连接速度(Mb/s)", LVCFMT_LEFT, 100, -1);
	m_listClientInfo.InsertColumn(3,"信号强度(dbm)", LVCFMT_LEFT, 100, -1);
	m_listClientInfo.InsertColumn(4,"网络带宽(Mb)", LVCFMT_LEFT, 100, -1);
	
	return TRUE;
}
