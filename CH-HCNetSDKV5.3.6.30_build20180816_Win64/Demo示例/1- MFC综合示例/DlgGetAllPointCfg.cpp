// DlgGetAllPointCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgGetAllPointCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgGetAllPointCfg dialog
DWORD WINAPI DlgGetAllPointCfg::GetConfigThread(LPVOID lpArg)
{
	DlgGetAllPointCfg* pThis = reinterpret_cast<DlgGetAllPointCfg*>(lpArg);
	int bRet = 0;
	char szLan[128] = {0};
	while(pThis->m_bGetNext)
	{
		bRet = NET_DVR_GetNextRemoteConfig(pThis->m_lHandle, &pThis->m_struAlarmPointCfg, sizeof(pThis->m_struAlarmPointCfg));
		if (bRet == NET_SDK_GET_NEXT_STATUS_SUCCESS)
		{
			//Sleep(300);
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
				g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_SUCC_T, szLan);
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
			g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_FAIL_T, "Stop Remote Config Failed");
			pThis->m_bGetNext = FALSE;
		}
		else
		{
			g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_SUCC_T, "Stop Remote Config Successful");
			pThis->m_bGetNext = FALSE;
			pThis->m_lHandle = -1;
		}
	}
	return 0 ;
}

void DlgGetAllPointCfg::AddInfoToDlg() 
{
	//点号
	if(0xffffffff == m_struAlarmPointCfg.dwPointNo)
	{
		sprintf(m_sTemp, "%s", "--");
	}
	else
	{
		sprintf(m_sTemp, "%d", m_struAlarmPointCfg.dwPointNo);
	}
	m_listPointCfg.InsertItem(m_iRowCount,m_sTemp);
	
	//点号描述
	sprintf(m_sTemp, "%s", (char*)m_struAlarmPointCfg.sPointDescribe, NAME_LEN);
	m_listPointCfg.SetItemText(m_iRowCount, 1, m_sTemp);
	
	//通道号
	if(0xffffffff == m_struAlarmPointCfg.dwChanNo)
	{
		sprintf(m_sTemp, "%s", "--");
	}
	else
	{
		sprintf(m_sTemp, "%d", m_struAlarmPointCfg.dwChanNo);
	}
	m_listPointCfg.SetItemText(m_iRowCount, 2, m_sTemp);
	
	//槽位号
	if(0xffffffff == m_struAlarmPointCfg.dwSubChanNo)
	{
		sprintf(m_sTemp, "%s", "--");
	}
	else
	{
		sprintf(m_sTemp, "%d", m_struAlarmPointCfg.dwSubChanNo);
	}
	m_listPointCfg.SetItemText(m_iRowCount, 3, m_sTemp);
	
	//槽位号
	if(0xffffffff == m_struAlarmPointCfg.dwVariableNo)
	{
		sprintf(m_sTemp, "%s", "--");
	}
	else
	{
		sprintf(m_sTemp, "%d", m_struAlarmPointCfg.dwVariableNo);
	}
	m_listPointCfg.SetItemText(m_iRowCount, 4, m_sTemp);

	if(1 == m_struAlarmPointCfg.byPointType)
	{
		sprintf(m_sTemp, "模拟量");
	}
	else if (2 == m_struAlarmPointCfg.byPointType)
	{
		sprintf(m_sTemp, "开关量");
	}
	else
	{
		sprintf(m_sTemp, "无意义");
	}
	m_listPointCfg.SetItemText(m_iRowCount, 5, m_sTemp);
	
	if(1 == m_struAlarmPointCfg.byChanType)
	{
		sprintf(m_sTemp, "本地模拟量通道");
	}
	else if (2 == m_struAlarmPointCfg.byChanType)
	{
		sprintf(m_sTemp, "本地开关量通道");
	}
	else if (3 == m_struAlarmPointCfg.byChanType)
	{
		sprintf(m_sTemp, "485通道");
	}
	else if (4 == m_struAlarmPointCfg.byChanType)
	{
		sprintf(m_sTemp, "网络通道");
	}
	else
	{
		sprintf(m_sTemp, "无意义");
	}
	m_listPointCfg.SetItemText(m_iRowCount, 6, m_sTemp);
	
	m_iRowCount++;
}

DlgGetAllPointCfg::DlgGetAllPointCfg(CWnd* pParent /*=NULL*/)
	: CDialog(DlgGetAllPointCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgGetAllPointCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(&m_struAlarmPointCfg,0,sizeof(m_struAlarmPointCfg));
	m_lHandle = -1;
}


void DlgGetAllPointCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgGetAllPointCfg)
	DDX_Control(pDX, IDC_LIST_POINT_CFG, m_listPointCfg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgGetAllPointCfg, CDialog)
	//{{AFX_MSG_MAP(DlgGetAllPointCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgGetAllPointCfg message handlers
BOOL DlgGetAllPointCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	m_listPointCfg.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listPointCfg.InsertColumn(0, "点号", LVCFMT_LEFT, 80, -1);
	m_listPointCfg.InsertColumn(1,"点号描述", LVCFMT_LEFT, 150, -1);
	m_listPointCfg.InsertColumn(2,"通道号", LVCFMT_LEFT, 80, -1);
	m_listPointCfg.InsertColumn(3,"槽位号", LVCFMT_LEFT, 80, -1);
	m_listPointCfg.InsertColumn(4,"变量编号", LVCFMT_LEFT, 80, -1);
	m_listPointCfg.InsertColumn(5,"点号类型", LVCFMT_LEFT, 80, -1);
	m_listPointCfg.InsertColumn(6,"接入类型", LVCFMT_LEFT, 100, -1);

	return TRUE;
}

void DlgGetAllPointCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	m_listPointCfg.DeleteAllItems();
	m_iRowCount = 0;
	if (m_lHandle>=0)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "It is getting data, wait for a moment");
	}
	else
	{
		m_lHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_GET_ALL_ALARM_POINT_CFG, NULL, 0, NULL, this);
		if (m_lHandle>=0)
		{
			m_bGetNext = TRUE;
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Start Remote Config successfully");
			DWORD dwThreadId;
			m_hGetInfoThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetConfigThread), this, 0, &dwThreadId);
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Start Remote Config failed");
			return;
		}
	}
}
