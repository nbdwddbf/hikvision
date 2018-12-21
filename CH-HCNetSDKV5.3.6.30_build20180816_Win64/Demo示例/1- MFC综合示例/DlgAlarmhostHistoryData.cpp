// DlgAlarmhostHistoryData.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmhostHistoryData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmhostHistoryData dialog
DWORD WINAPI CDlgAlarmhostHistoryData::GetConfigThread(LPVOID lpArg)
{
	CDlgAlarmhostHistoryData* pThis = reinterpret_cast<CDlgAlarmhostHistoryData*>(lpArg);
	int bRet = 0;
	char szLan[128] = {0};
	while(pThis->m_bGetNext)
	{
		bRet = NET_DVR_GetNextRemoteConfig(pThis->m_lHandle, &pThis->m_struHistoryData, sizeof(pThis->m_struHistoryData));
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
				g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_SUCC_T, szLan);
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

void CDlgAlarmhostHistoryData::AddInfoToDlg() 
{
	//时间点
	sprintf(m_sTemp, "%02d-%02d-%02d, %02d:%02d:%02d", m_struHistoryData.struTime.dwYear, m_struHistoryData.struTime.dwMonth, m_struHistoryData.struTime.dwDay, \
		m_struHistoryData.struTime.dwHour, m_struHistoryData.struTime.dwMinute, m_struHistoryData.struTime.dwSecond);
	m_listData.InsertItem(m_iRowCount, m_sTemp);
	//通道号
	if(0xffffffff == m_struHistoryData.dwChanNo)
	{
		sprintf(m_sTemp, "%s", "--");
	}
	else
	{
		sprintf(m_sTemp, "%d", m_struHistoryData.dwChanNo);
	}
	m_listData.SetItemText(m_iRowCount, 1, m_sTemp);

	//槽位号
	if(0xffffffff == m_struHistoryData.dwSubChanNo)
	{
		sprintf(m_sTemp, "%s", "--");
	}
	else
	{
		sprintf(m_sTemp, "%d", m_struHistoryData.dwSubChanNo);
	}
	m_listData.SetItemText(m_iRowCount, 2, m_sTemp);

	//变量号
	if(0xffffffff == m_struHistoryData.dwVariableNo)
	{
		sprintf(m_sTemp, "%s", "--");
	}
	else
	{
		sprintf(m_sTemp, "%d", m_struHistoryData.dwVariableNo);
	}
	m_listData.SetItemText(m_iRowCount, 3, m_sTemp);

	//点号
	if(0xffffffff == m_struHistoryData.dwPointNo)
	{
		sprintf(m_sTemp, "%s", "--");
	}
	else
	{
		sprintf(m_sTemp, "%d", m_struHistoryData.dwPointNo);
	}
	m_listData.SetItemText(m_iRowCount, 4, m_sTemp);

	//历史数据
	sprintf(m_sTemp, "%.3f", (float)m_struHistoryData.iData/1000);
	m_listData.SetItemText(m_iRowCount, 5, m_sTemp);

	if(0 == m_struHistoryData.byDataType)
	{
		sprintf(m_sTemp, "正常数据");
	}
	else if (1 == m_struHistoryData.byDataType)
	{
		sprintf(m_sTemp, "越上限数据");
	}
	else if (2 == m_struHistoryData.byDataType)
	{
		sprintf(m_sTemp, "越下限数据");
	}
	else
	{
		sprintf(m_sTemp, "--");
	}
	m_listData.SetItemText(m_iRowCount, 6, m_sTemp);
	m_iRowCount++;
}


CDlgAlarmhostHistoryData::CDlgAlarmhostHistoryData(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmhostHistoryData::IDD, pParent)
	, m_lUserID(-1)
	, m_iDeviceIndex(-1)
	, m_hGetInfoThread(NULL)
	, m_iRowCount(0)
	, m_lHandle(-1)
{
	//{{AFX_DATA_INIT(CDlgAlarmhostHistoryData)
	m_timeStartDay = COleDateTime::GetCurrentTime();
	m_timeStartTime = COleDateTime::GetCurrentTime();
	m_timeStopDay = COleDateTime::GetCurrentTime();
	m_timeStopTime = COleDateTime::GetCurrentTime();
	m_dwChanNo = 0;
	m_dwPointNo = 0;
	m_dwSlotNo = 0;
	m_dwVarNo = 0;
	//}}AFX_DATA_INIT
}


void CDlgAlarmhostHistoryData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmhostHistoryData)
	DDX_Control(pDX, IDC_COMBO_CHAN_TYPE, m_cmChanType);
	DDX_Control(pDX, IDC_LIST_DATA, m_listData);
	DDX_Control(pDX, IDC_COMBO_MINOR_TYPE, m_cmMinorType);
	DDX_Control(pDX, IDC_COMBO_MAJOR_TYPE, m_cmMajorType);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START_DAY, m_timeStartDay);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START_TIME, m_timeStartTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STOP_DAY, m_timeStopDay);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STOP_TIME, m_timeStopTime);
	DDX_Text(pDX, IDC_EDIT_CHAN_NO, m_dwChanNo);
	DDX_Text(pDX, IDC_EDIT_POINT_NO, m_dwPointNo);
	DDX_Text(pDX, IDC_EDIT_SLOT_NO, m_dwSlotNo);
	DDX_Text(pDX, IDC_EDIT_VAR_NO, m_dwVarNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmhostHistoryData, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmhostHistoryData)
	ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	ON_CBN_SELCHANGE(IDC_COMBO_MAJOR_TYPE, OnSelchangeComboMajorType)
	ON_CBN_SELCHANGE(IDC_COMBO_CHAN_TYPE, OnSelchangeComboChanType)
	ON_CBN_SELCHANGE(IDC_COMBO_MINOR_TYPE, OnSelchangeComboMinorType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmhostHistoryData message handlers

BOOL CDlgAlarmhostHistoryData::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	m_listData.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listData.InsertColumn(0, "time", LVCFMT_LEFT, 150, -1);
	m_listData.InsertColumn(1,"channel", LVCFMT_LEFT, 80, -1);
	m_listData.InsertColumn(2,"slot", LVCFMT_LEFT, 80, -1);
	m_listData.InsertColumn(3,"variable", LVCFMT_LEFT, 80, -1);
	m_listData.InsertColumn(4,"point", LVCFMT_LEFT, 80, -1);
	m_listData.InsertColumn(5,"history data", LVCFMT_LEFT, 100, -1);
	m_listData.InsertColumn(6,"data type", LVCFMT_LEFT, 100, -1);

	InitComboWnd();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlarmhostHistoryData::InitComboWnd()
{
	CString csStr;
	m_cmMajorType.ResetContent();
	g_StringLanType(m_sTemp, "全部", "All");
	csStr.Format("%s", m_sTemp);
	m_cmMajorType.AddString(m_sTemp);

	g_StringLanType(m_sTemp, "按时间", "By Time");
	csStr.Format("%s", m_sTemp);
	m_cmMajorType.AddString(m_sTemp);

	g_StringLanType(m_sTemp, "按类型", "By Type");
	csStr.Format("%s", m_sTemp);
	m_cmMajorType.AddString(m_sTemp);

	g_StringLanType(m_sTemp, "时间+类型", "Time&Type");
	csStr.Format("%s", m_sTemp);
	m_cmMajorType.AddString(m_sTemp);
	
	m_cmMinorType.ResetContent();
	g_StringLanType(m_sTemp, "点号", "Point No");
	csStr.Format("%s", m_sTemp);
	m_cmMinorType.AddString(m_sTemp);

	g_StringLanType(m_sTemp, "变量号", "Var No");
	csStr.Format("%s", m_sTemp);
	m_cmMinorType.AddString(m_sTemp);

	m_cmChanType.ResetContent();
	g_StringLanType(m_sTemp, "本地模拟量", "Sensor");
	csStr.Format("%s", m_sTemp);
	m_cmChanType.AddString(m_sTemp);

	g_StringLanType(m_sTemp, "485通道", "RS_485");
	csStr.Format("%s", m_sTemp);
	m_cmChanType.AddString(m_sTemp);

	UpdateData(FALSE);
}

void CDlgAlarmhostHistoryData::GetSearchConditionFromDlg()
{
	UpdateData(TRUE);
	int iMajorType = m_cmMajorType.GetCurSel() + 1;
	int iMinorType = m_cmMinorType.GetCurSel() + 1;
	///查询方式主类型，1-全部，2-按时间， 3-按类型，4-时间+类型
	//查询次类型 1-点号，2-通道+槽位+变量号，byMajorType为3,或者4的时候该参数有效
	if (1 == iMajorType)
	{
		//全部
		m_struSearch.byMajorType = 1;
	}
	else if(2 == iMajorType)
	{
		//按时间
		m_struSearch.byMajorType = 2;
		m_struSearch.struStartTime.dwYear = m_timeStartDay.GetYear();
		m_struSearch.struStartTime.dwMonth = m_timeStartDay.GetMonth();
		m_struSearch.struStartTime.dwDay = m_timeStartDay.GetDay();
		m_struSearch.struStartTime.dwHour = m_timeStartTime.GetHour();
		m_struSearch.struStartTime.dwMinute = m_timeStartTime.GetMinute();
		m_struSearch.struStartTime.dwSecond = m_timeStartTime.GetSecond();
		
		m_struSearch.struStopTime.dwYear = m_timeStopDay.GetYear();
		m_struSearch.struStopTime.dwMonth = m_timeStopDay.GetMonth();
		m_struSearch.struStopTime.dwDay = m_timeStopDay.GetDay();
		m_struSearch.struStopTime.dwHour = m_timeStopTime.GetHour();
		m_struSearch.struStopTime.dwMinute = m_timeStopTime.GetMinute();
		m_struSearch.struStopTime.dwSecond = m_timeStopTime.GetSecond();
	}
	else if (3 == iMajorType && 1 == iMinorType)
	{
		//按点号
		m_struSearch.byMajorType = 3;
		m_struSearch.byMinorType = 1;
		m_struSearch.dwPointNo = m_dwPointNo;
	}
	else if (3 == iMajorType && 2 == iMinorType)
	{
		//按变量号
		m_struSearch.byMajorType = 3;
		m_struSearch.byMinorType = 2;
		m_struSearch.dwChanNo = m_dwChanNo;
		m_struSearch.dwSubChanNo = m_dwSlotNo;
		m_struSearch.dwVariableNo = m_dwVarNo;
		m_struSearch.byChanType = m_cmChanType.GetCurSel() + 1;
	}
	else if (4 == iMajorType && 1 == iMinorType)
	{
		//时间+点号
		m_struSearch.byMajorType = 4;
		m_struSearch.byMinorType = 1;

		m_struSearch.struStartTime.dwYear = m_timeStartDay.GetYear();
		m_struSearch.struStartTime.dwMonth = m_timeStartDay.GetMonth();
		m_struSearch.struStartTime.dwDay = m_timeStartDay.GetDay();
		m_struSearch.struStartTime.dwHour = m_timeStartTime.GetHour();
		m_struSearch.struStartTime.dwMinute = m_timeStartTime.GetMinute();
		m_struSearch.struStartTime.dwSecond = m_timeStartTime.GetSecond();
		
		m_struSearch.struStopTime.dwYear = m_timeStopDay.GetYear();
		m_struSearch.struStopTime.dwMonth = m_timeStopDay.GetMonth();
		m_struSearch.struStopTime.dwDay = m_timeStopDay.GetDay();
		m_struSearch.struStopTime.dwHour = m_timeStopTime.GetHour();
		m_struSearch.struStopTime.dwMinute = m_timeStopTime.GetMinute();
		m_struSearch.struStopTime.dwSecond = m_timeStopTime.GetSecond();
		
		m_struSearch.dwPointNo = m_dwPointNo;
	}
	else if(4 == iMajorType && 2 == iMinorType)
	{
		//时间+变量号
		m_struSearch.byMajorType = 4;
		m_struSearch.byMinorType = 2;

		m_struSearch.struStartTime.dwYear = m_timeStartDay.GetYear();
		m_struSearch.struStartTime.dwMonth = m_timeStartDay.GetMonth();
		m_struSearch.struStartTime.dwDay = m_timeStartDay.GetDay();
		m_struSearch.struStartTime.dwHour = m_timeStartTime.GetHour();
		m_struSearch.struStartTime.dwMinute = m_timeStartTime.GetMinute();
		m_struSearch.struStartTime.dwSecond = m_timeStartTime.GetSecond();
		
		m_struSearch.struStopTime.dwYear = m_timeStopDay.GetYear();
		m_struSearch.struStopTime.dwMonth = m_timeStopDay.GetMonth();
		m_struSearch.struStopTime.dwDay = m_timeStopDay.GetDay();
		m_struSearch.struStopTime.dwHour = m_timeStopTime.GetHour();
		m_struSearch.struStopTime.dwMinute = m_timeStopTime.GetMinute();
		m_struSearch.struStopTime.dwSecond = m_timeStopTime.GetSecond();

		m_struSearch.dwChanNo = m_dwChanNo;
		m_struSearch.dwSubChanNo = m_dwSlotNo;
		m_struSearch.dwVariableNo = m_dwVarNo;
		m_struSearch.byChanType = m_cmChanType.GetCurSel() + 1;
	}
}

void CDlgAlarmhostHistoryData::OnBtnSearch() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	memset(&m_struSearch, 0, sizeof(m_struSearch));
	GetSearchConditionFromDlg();
	m_struSearch.dwSize = sizeof(m_struSearch);
	m_listData.DeleteAllItems();
	m_iRowCount = 0;
	if (m_lHandle>=0)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "It is getting data, wait for a moment");
	}
	else
	{
		m_lHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_GET_HISTORY_VALUE, &m_struSearch, sizeof(m_struSearch), NULL, this);
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

void CDlgAlarmhostHistoryData::OnBtnStop() 
{
	// TODO: Add your control notification handler code here
	if (-1 == m_lHandle)
	{
		return;
	}
	if (!NET_DVR_StopRemoteConfig(m_lHandle))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Stop Remote Config Failed");
		m_bGetNext = FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Stop Remote Config Successful");
		m_bGetNext = FALSE;
		m_lHandle = -1;
	}
}

void CDlgAlarmhostHistoryData::OnSelchangeComboMajorType() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iType = m_cmMajorType.GetCurSel();
	if (0 == iType)
	{
		//全部
		GetDlgItem(IDC_COMBO_MINOR_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_CHAN_NO)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SLOT_NO)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_VAR_NO)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_POINT_NO)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATETIMEPICKER_START_DAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATETIMEPICKER_START_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATETIMEPICKER_STOP_DAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATETIMEPICKER_STOP_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_CHAN_TYPE)->EnableWindow(FALSE);
	}
	else if (1 == iType)
	{
		//按时间
		GetDlgItem(IDC_COMBO_MINOR_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_CHAN_NO)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SLOT_NO)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_VAR_NO)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_POINT_NO)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATETIMEPICKER_START_DAY)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIMEPICKER_START_TIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIMEPICKER_STOP_DAY)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIMEPICKER_STOP_TIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_CHAN_TYPE)->EnableWindow(FALSE);
	}
	else if (2 == iType)
	{
		//按类型
		GetDlgItem(IDC_COMBO_MINOR_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_CHAN_NO)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SLOT_NO)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_VAR_NO)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_POINT_NO)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIMEPICKER_START_DAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATETIMEPICKER_START_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATETIMEPICKER_STOP_DAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATETIMEPICKER_STOP_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_CHAN_TYPE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_COMBO_MINOR_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_CHAN_NO)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_SLOT_NO)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_VAR_NO)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_POINT_NO)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIMEPICKER_START_DAY)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIMEPICKER_START_TIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIMEPICKER_STOP_DAY)->EnableWindow(TRUE);
		GetDlgItem(IDC_DATETIMEPICKER_STOP_TIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_CHAN_TYPE)->EnableWindow(TRUE);
	}
	UpdateData(FALSE);
}

void CDlgAlarmhostHistoryData::OnSelchangeComboChanType() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	BYTE byType = m_cmChanType.GetCurSel() + 1;
	
	if (1==m_cmMinorType.GetCurSel())   //次类型为变量
	{
		if (1 == byType)
		{
			//本地模拟量
			//GetDlgItem(IDC_EDIT_CHAN_NO)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_SLOT_NO)->EnableWindow(FALSE);
			//GetDlgItem(IDC_EDIT_VAR_NO)->EnableWindow(FALSE);
		}
		else if (2 == byType)
		{
			//485
			//GetDlgItem(IDC_EDIT_VAR_NO)->EnableWindow(TRUE);
			//GetDlgItem(IDC_EDIT_POINT_NO)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_SLOT_NO)->EnableWindow(TRUE);
			//GetDlgItem(IDC_EDIT_VAR_NO)->EnableWindow(TRUE);
		}
		m_dwVarNo = 1;
	}
	UpdateData(FALSE);
}


void CDlgAlarmhostHistoryData::OnSelchangeComboMinorType() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (2==m_cmMajorType.GetCurSel() || 3==m_cmMinorType.GetCurSel())
	{
		if (0==m_cmMinorType.GetCurSel())
		{
			//按点号
			GetDlgItem(IDC_EDIT_CHAN_NO)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_SLOT_NO)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_VAR_NO)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_POINT_NO)->EnableWindow(TRUE);
		}
		else if (1==m_cmMinorType.GetCurSel())
		{
			//按变量号
			GetDlgItem(IDC_EDIT_CHAN_NO)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_SLOT_NO)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_VAR_NO)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_POINT_NO)->EnableWindow(FALSE);
		}
	}
	UpdateData(FALSE);
}
