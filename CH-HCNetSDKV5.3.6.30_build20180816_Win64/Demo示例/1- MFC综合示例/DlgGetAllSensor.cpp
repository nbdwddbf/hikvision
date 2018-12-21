// DlgGetAllSensor.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgGetAllSensor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgGetAllSensor dialog
DWORD WINAPI DlgGetAllSensor::GetConfigThread(LPVOID lpArg)
{
	DlgGetAllSensor* pThis = reinterpret_cast<DlgGetAllSensor*>(lpArg);
	int bRet = 0;
	char szLan[128] = {0};
	while(pThis->m_bGetNext)
	{
		bRet = NET_DVR_GetNextRemoteConfig(pThis->m_lHandle, &pThis->m_struSensorInfo, sizeof(pThis->m_struSensorInfo));
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

void DlgGetAllSensor::AddInfoToDlg() 
{
	//通道
	sprintf(m_sTemp, "%d", m_struSensorInfo.byChan);
	m_listSensor.InsertItem(m_iRowCount, m_sTemp);
	
	//传感器名称
	sprintf(m_sTemp, "%s", (char*)m_struSensorInfo.byName, NAME_LEN);
	m_listSensor.SetItemText(m_iRowCount, 1, m_sTemp);
	
	//是否启用
	if(1 == m_struSensorInfo.byEnable)
	{
		sprintf(m_sTemp, "%s", "启用");
	}
	else
	{
		sprintf(m_sTemp, "%s", "不启用");
	}
	m_listSensor.SetItemText(m_iRowCount, 2, m_sTemp);
	
	//是否有效
	if(1 == m_struSensorInfo.byValid)
	{
		sprintf(m_sTemp, "%s", "有效");
	}
	else
	{
		sprintf(m_sTemp, "%s", "无效");
	}
	m_listSensor.SetItemText(m_iRowCount, 3, m_sTemp);
	
	//槽位号
	if(15 == m_struSensorInfo.byAlarmMode)
	{
		sprintf(m_sTemp, "%s", "HHHH");
	}
	else if (14 == m_struSensorInfo.byAlarmMode)
	{
		sprintf(m_sTemp, "%s", "HHHL");
	}
	else if (14 == m_struSensorInfo.byAlarmMode)
	{
		sprintf(m_sTemp, "%s", "HHHL");
	}
	else if (12 == m_struSensorInfo.byAlarmMode)
	{
		sprintf(m_sTemp, "%s", "HHLL");
	}
	else if (8 == m_struSensorInfo.byAlarmMode)
	{
		sprintf(m_sTemp, "%s", "HLLL");
	}
	else if (0 == m_struSensorInfo.byAlarmMode)
	{
		sprintf(m_sTemp, "%s", "LLLL");
	}
	else
	{
		sprintf(m_sTemp, "%s", "--");
	}
	m_listSensor.SetItemText(m_iRowCount, 4, m_sTemp);

	sprintf(m_sTemp, "%.3f", m_struSensorInfo.fMeasureHigh);
	m_listSensor.SetItemText(m_iRowCount, 5, m_sTemp);
	
	sprintf(m_sTemp, "%.3f", m_struSensorInfo.fAlarm1);
	m_listSensor.SetItemText(m_iRowCount, 6, m_sTemp);

	sprintf(m_sTemp, "%.3f", m_struSensorInfo.fAlarm2);
	m_listSensor.SetItemText(m_iRowCount, 7, m_sTemp);

	sprintf(m_sTemp, "%.3f", m_struSensorInfo.fAlarm3);
	m_listSensor.SetItemText(m_iRowCount, 8, m_sTemp);

	sprintf(m_sTemp, "%.3f", m_struSensorInfo.fAlarm4);
	m_listSensor.SetItemText(m_iRowCount, 9, m_sTemp);

	sprintf(m_sTemp, "%d", m_struSensorInfo.dwOsdCfg);
	m_listSensor.SetItemText(m_iRowCount, 10, m_sTemp);

	sprintf(m_sTemp, "%.3f", m_struSensorInfo.fSensitive);
	m_listSensor.SetItemText(m_iRowCount, 11, m_sTemp);

	if(0 == m_struSensorInfo.bySensorStandard)
	{
		sprintf(m_sTemp, "4~20mA");
	}
	else if (1 == m_struSensorInfo.bySensorStandard)
	{
		sprintf(m_sTemp, "0~5V");
	}
	else
	{
		sprintf(m_sTemp, "--");
	}
	m_listSensor.SetItemText(m_iRowCount, 12, m_sTemp);
	
	m_iRowCount++;
}

DlgGetAllSensor::DlgGetAllSensor(CWnd* pParent /*=NULL*/)
	: CDialog(DlgGetAllSensor::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgGetAllSensor)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(&m_struSensorInfo,0,sizeof(m_struSensorInfo));
	m_lHandle = -1;
}


void DlgGetAllSensor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgGetAllSensor)
	DDX_Control(pDX, IDC_LIST_SENSOR, m_listSensor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgGetAllSensor, CDialog)
	//{{AFX_MSG_MAP(DlgGetAllSensor)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgGetAllSensor message handlers
BOOL DlgGetAllSensor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	m_listSensor.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listSensor.InsertColumn(0, "通道号", LVCFMT_LEFT, 80, -1);
	m_listSensor.InsertColumn(1,"传感器名称", LVCFMT_LEFT, 150, -1);
	m_listSensor.InsertColumn(2,"是否启用", LVCFMT_LEFT, 80, -1);
	m_listSensor.InsertColumn(3,"是否有效", LVCFMT_LEFT, 80, -1);
	m_listSensor.InsertColumn(4,"报警模式", LVCFMT_LEFT, 80, -1);
	m_listSensor.InsertColumn(5,"量程上限", LVCFMT_LEFT, 80, -1);
	m_listSensor.InsertColumn(6,"报警限1", LVCFMT_LEFT, 100, -1);
	m_listSensor.InsertColumn(7,"报警限2", LVCFMT_LEFT, 80, -1);
	m_listSensor.InsertColumn(8,"报警限3", LVCFMT_LEFT, 80, -1);
	m_listSensor.InsertColumn(9,"报警限4", LVCFMT_LEFT, 80, -1);
	m_listSensor.InsertColumn(10,"字符叠加", LVCFMT_LEFT, 80, -1);
	m_listSensor.InsertColumn(11,"灵敏度", LVCFMT_LEFT, 80, -1);
	m_listSensor.InsertColumn(12,"传感器规格", LVCFMT_LEFT, 80, -1);

	UpdateData(FALSE);
	return TRUE;
}

void DlgGetAllSensor::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_listSensor.DeleteAllItems();
	m_iRowCount = 0;
	if (m_lHandle>=0)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "It is getting data, wait for a moment");
	}
	else
	{
		m_lHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_GET_ALL_ALARM_SENSOR_CFG, NULL, 0, NULL, this);
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
