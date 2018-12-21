// DlgAlarmHostGetAllModule.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmHostGetAllModule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgAlarmHostGetAllModule dialog

DWORD WINAPI DlgAlarmHostGetAllModule::GetConfigThread(LPVOID lpArg)
{
	DlgAlarmHostGetAllModule* pThis = reinterpret_cast<DlgAlarmHostGetAllModule*>(lpArg);
	int bRet = 0;
	char szLan[128] = {0};
	while(pThis->m_bGetNext)
	{
		bRet = NET_DVR_GetNextRemoteConfig(pThis->m_lTranHandle, &pThis->m_struModuleInfo, sizeof(pThis->m_struModuleInfo));
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
				g_StringLanType(szLan, "查询数据结束!", "Get route info Ending");
				g_pMainDlg->AddLog(pThis->m_iDevIndex, OPERATION_SUCC_T, szLan);
				//AfxMessageBox(szLan);
				break;
			}
			else if(bRet == NET_SDK_GET_NEXT_STATUS_FAILED)
			{
				g_StringLanType(szLan, "查询数据失败!", "Get route info failed");
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
	if (-1 != pThis->m_lTranHandle)
	{
		if (!NET_DVR_StopRemoteConfig(pThis->m_lTranHandle))
		{
			g_pMainDlg->AddLog(pThis->m_iDevIndex, OPERATION_FAIL_T, "Stop Remote Config Failed");
			pThis->m_bGetNext = FALSE;
		}
		else
		{
			g_pMainDlg->AddLog(pThis->m_iDevIndex, OPERATION_SUCC_T, "Stop Remote Config Successful");
			pThis->m_bGetNext = FALSE;
			pThis->m_lTranHandle = -1;
		}
	}
	return 0 ;
}

void DlgAlarmHostGetAllModule::AddInfoToDlg() 
{ 
	//时间点
	char sTemp[256];
	BOOL isVailed = FALSE;
	if (m_struModuleInfo.byModuleType == 1)
	{
		g_StringLanType(sTemp, "键盘", "Keyboard");
		m_listData.InsertItem(m_iRowCount, sTemp);

		if (m_struModuleInfo.byKeyBoardType == 1)
		{
			sprintf(sTemp, "LCD");
			m_listData.SetItemText(m_iRowCount, 1, sTemp);
		}
		else if (m_struModuleInfo.byKeyBoardType == 2)
		{
			sprintf(sTemp, "LED");
			m_listData.SetItemText(m_iRowCount, 1, sTemp);
		}
		else
		{
			g_StringLanType(sTemp, "无效类型", "invalid type");
			m_listData.SetItemText(m_iRowCount, 1, sTemp);
		}
	}
	else if (m_struModuleInfo.byModuleType == 2)
	{
		g_StringLanType(sTemp, "触发器", "trigger");
		m_listData.InsertItem(m_iRowCount, sTemp);
		//UpdateData(FALSE);
		//m_listData.SetItemText(0, 1, sTemp);
		if (m_struModuleInfo.byTriggerType == 1)
		{
			g_StringLanType(sTemp, "本地触发器", "local trigger");
			m_listData.SetItemText(m_iRowCount, 1, sTemp);
		}
		else if (m_struModuleInfo.byTriggerType == 2)
		{
			g_StringLanType(sTemp, "4路触发器", "4 zone trigger");
			m_listData.SetItemText(m_iRowCount, 1, sTemp);
		}
		else if (m_struModuleInfo.byTriggerType == 3)
		{
			g_StringLanType(sTemp, "8路触发器", "8 zone trigger");
			m_listData.SetItemText(m_iRowCount, 1, sTemp);
		}
		else if (m_struModuleInfo.byTriggerType == 4)
		{
			g_StringLanType(sTemp, "单防区触发器", "single zone trigger");
			m_listData.SetItemText(m_iRowCount, 1, sTemp);
		}
		else if (m_struModuleInfo.byTriggerType == 5)
		{
			g_StringLanType(sTemp, "32路触发器", "32 zone trigger");
			m_listData.SetItemText(m_iRowCount, 1, sTemp);
		}
		else
		{
			g_StringLanType(sTemp, "无效类型", "invalid type");
			m_listData.SetItemText(m_iRowCount, 1, sTemp);
		}
	}
	else if (m_struModuleInfo.byModuleType == 3)
	{
		g_StringLanType(sTemp, "防区", "zone");
		m_listData.InsertItem(m_iRowCount, sTemp);

		if (m_struModuleInfo.byZoneType == 1)
		{
			g_StringLanType(sTemp, "本地防区", "local trigger");
			m_listData.SetItemText(m_iRowCount, 1, sTemp);
		}
		else if (m_struModuleInfo.byZoneType == 2)
		{
			g_StringLanType(sTemp, "单防区", "single zone");
			m_listData.SetItemText(m_iRowCount, 1, sTemp);
		}
		else if (m_struModuleInfo.byZoneType == 3)
		{
			g_StringLanType(sTemp, "双防区", "double zone");
			m_listData.SetItemText(m_iRowCount, 1, sTemp);
		}
		else if (m_struModuleInfo.byZoneType == 4)
		{
			g_StringLanType(sTemp, "8防区", "8 zone");
			m_listData.SetItemText(m_iRowCount, 1, sTemp);
		}
		else if (m_struModuleInfo.byZoneType == 5)
		{
			g_StringLanType(sTemp, "8路模拟量防区", "8 sensor zone");
			m_listData.SetItemText(m_iRowCount, 1, sTemp);
		}
		else if (m_struModuleInfo.byZoneType == 6)
		{
			g_StringLanType(sTemp, "单防区触发器", "single zone trigger");
			m_listData.SetItemText(m_iRowCount, 1, sTemp);
		}
		else
		{
			g_StringLanType(sTemp, "无效类型", "invalid type");
			m_listData.SetItemText(m_iRowCount, 1, sTemp);
		}
	}
    else if (m_struModuleInfo.byModuleType == 4)
    {
        g_StringLanType(sTemp, "网络模块", "networkModule");
        m_listData.InsertItem(m_iRowCount, sTemp);
    }
	else
	{
		g_StringLanType(sTemp, "无效类型", "invalid type");
		m_listData.InsertItem(m_iRowCount, sTemp);
	//	m_listData.SetItemText(m_iRowCount, 1, sTemp);
		isVailed = TRUE;
	}
	if (!isVailed)
	{
		sprintf(sTemp, "%d", m_struModuleInfo.wModuleAddress);
		m_listData.SetItemText(m_iRowCount, 2, sTemp);

		//sprintf(sTemp, "%s", (char*)m_struModuleInfo.sModelInfo);
		memcpy(sTemp,m_struModuleInfo.sModelInfo,32);
		m_listData.SetItemText(m_iRowCount, 3, sTemp);
		
		//sprintf(sTemp, "%s", (char*)m_struModuleInfo.sDeviceVersionInfo);
		memcpy(sTemp,m_struModuleInfo.sDeviceVersionInfo,32);
		m_listData.SetItemText(m_iRowCount, 4, sTemp);
	}
	m_iRowCount++;
	//UpdateData(FALSE);
}

DlgAlarmHostGetAllModule::DlgAlarmHostGetAllModule(CWnd* pParent /*=NULL*/)
	: CDialog(DlgAlarmHostGetAllModule::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgAlarmHostGetAllModule)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_iDevIndex = 0;
	m_lServerID = 0;
	m_iRowCount = 0;
	m_lTranHandle = -1;
}


void DlgAlarmHostGetAllModule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgAlarmHostGetAllModule)
	DDX_Control(pDX, IDC_LIST_ALL_MODULE, m_listData);
	DDX_Control(pDX, IDC_COM_MODULE_TYPE, m_comModuleType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgAlarmHostGetAllModule, CDialog)
	//{{AFX_MSG_MAP(DlgAlarmHostGetAllModule)
	ON_BN_CLICKED(IDC_GET, OnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgAlarmHostGetAllModule message handlers
BOOL DlgAlarmHostGetAllModule::OnInitDialog() 
{
	CDialog::OnInitDialog();
	char szLan[128] = {0};
	m_listData.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	g_StringLanType(szLan, "模块类型", "Module type");
	m_listData.InsertColumn(0, szLan, LVCFMT_LEFT, 150, -1);
	g_StringLanType(szLan, "键盘/触发器/防区类型/网络模块", "Keyboard/Trigger type/zone type/network module");
	m_listData.InsertColumn(1, szLan, LVCFMT_LEFT, 300, -1);
	g_StringLanType(szLan, "外接模块地址", "Module addr");
	m_listData.InsertColumn(2, szLan, LVCFMT_LEFT, 250, -1);
	g_StringLanType(szLan, "模块信息", "Module info");
	m_listData.InsertColumn(3, szLan, LVCFMT_LEFT, 300, -1);
	g_StringLanType(szLan, "版本信息", "Version info");
	m_listData.InsertColumn(4, szLan, LVCFMT_LEFT, 300, -1);
	UpdateData(FALSE);
	return TRUE;
}

void DlgAlarmHostGetAllModule::OnGet() 
{
	// TODO: Add your control notification handler code here
	int type = 0;
	type = m_comModuleType.GetCurSel() + 1;
	m_listData.DeleteAllItems();
	m_iRowCount = 0;
	if (m_lTranHandle>=0)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "It is getting data, wait for a moment");
	}
	else
	{
		m_lTranHandle = NET_DVR_StartRemoteConfig(m_lServerID,NET_DVR_GET_ALARMHOST_MODULE_LIST,(void*)(&type),sizeof(DWORD),NULL,this);
		if (m_lTranHandle>=0)
		{
			m_bGetNext = TRUE;
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Start Remote Config successfully");
			DWORD dwThreadId;
			m_hGetInfoThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetConfigThread), this, 0, &dwThreadId);
		}
		else
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Start Remote Config failed");
			return;
		}
	}
}
