// DlgScheduleAutoTrack.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgScheduleAutoTrack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgScheduleAutoTrack dialog


CDlgScheduleAutoTrack::CDlgScheduleAutoTrack(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgScheduleAutoTrack::IDD, pParent)
	, m_lUserID(-1)
	, m_iDeviceIndex(-1)
	, m_iCurWeekIndex(0)
{
	//{{AFX_DATA_INIT(CDlgScheduleAutoTrack)
	m_chEnable = FALSE;
	m_timeStart1 = COleDateTime::GetCurrentTime();
	m_timeStart2 = COleDateTime::GetCurrentTime();
	m_timeStart4 = COleDateTime::GetCurrentTime();
	m_timeStart5 = COleDateTime::GetCurrentTime();
	m_timeStart6 = COleDateTime::GetCurrentTime();
	m_timeStart7 = COleDateTime::GetCurrentTime();
	m_timeStart8 = COleDateTime::GetCurrentTime();
	m_timeStart3 = COleDateTime::GetCurrentTime();
	m_timeStop1 = COleDateTime::GetCurrentTime();
	m_timeStop2 = COleDateTime::GetCurrentTime();
	m_timeStop3 = COleDateTime::GetCurrentTime();
	m_timeStop4 = COleDateTime::GetCurrentTime();
	m_timeStop5 = COleDateTime::GetCurrentTime();
	m_timeStop6 = COleDateTime::GetCurrentTime();
	m_timeStop7 = COleDateTime::GetCurrentTime();
	m_timeStop8 = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}


void CDlgScheduleAutoTrack::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgScheduleAutoTrack)
	DDX_Control(pDX, IDC_COMBO_WORKMODE, m_cmWorkMode);
	DDX_Control(pDX, IDC_COMBO_WEEK, m_cmWeek);
	DDX_Check(pDX, IDC_CHECK_ENABLE, m_chEnable);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START1, m_timeStart1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START2, m_timeStart2);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START4, m_timeStart4);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START5, m_timeStart5);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START6, m_timeStart6);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START7, m_timeStart7);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START8, m_timeStart8);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START9, m_timeStart3);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STOT1, m_timeStop1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STOT2, m_timeStop2);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STOT3, m_timeStop3);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STOT4, m_timeStop4);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STOT5, m_timeStop5);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STOT6, m_timeStop6);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STOT7, m_timeStop7);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_STOT8, m_timeStop8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgScheduleAutoTrack, CDialog)
	//{{AFX_MSG_MAP(CDlgScheduleAutoTrack)
	ON_CBN_SELCHANGE(IDC_COMBO_WEEK, OnSelchangeComboWeek)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgScheduleAutoTrack message handlers

CDlgScheduleAutoTrack::~CDlgScheduleAutoTrack() 
{
	return;
}

BOOL CDlgScheduleAutoTrack::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	//m_struStartTime = {m_timeStart1, m_timeStart2, m_timeStart3, m_timeStart4, m_timeStart5, m_timeStart6, m_timeStart7, m_timeStart8};
	//m_struStopTime = {m_timeStop1, m_timeStop2, m_timeStop3, m_timeStop4, m_timeStop5, m_timeStop6, m_timeStop7, m_timeStop8};

	m_struStartTime[0] = m_timeStart1;
	m_struStartTime[1] = m_timeStart2;
	m_struStartTime[2] = m_timeStart3;
	m_struStartTime[3] = m_timeStart4;
	m_struStartTime[4] = m_timeStart5;
	m_struStartTime[5] = m_timeStart6;
	m_struStartTime[6] = m_timeStart7;
	m_struStartTime[7] = m_timeStart8;

	m_struStopTime[0] = m_timeStop1;
	m_struStopTime[1] = m_timeStop2;
	m_struStopTime[2] = m_timeStop3;
	m_struStopTime[3] = m_timeStop4;
	m_struStopTime[4] = m_timeStop5;
	m_struStopTime[5] = m_timeStop6;
	m_struStopTime[6] = m_timeStop7;
	m_struStopTime[7] = m_timeStop8;

	memset(&m_struScheduleAutoTrack, 0, sizeof(m_struScheduleAutoTrack));
	InitWindow();
	OnBtnGet();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgScheduleAutoTrack::InitWindow() 
{
	m_cmWeek.ResetContent();
	g_StringLanType(m_szLan, "星期一", "Monday");
	m_cmWeek.AddString(m_szLan);
	g_StringLanType(m_szLan, "星期二", "Tuesday");
	m_cmWeek.AddString(m_szLan);
	g_StringLanType(m_szLan, "星期三", "Wednesday");
	m_cmWeek.AddString(m_szLan);
	g_StringLanType(m_szLan, "星期四", "Thursday");
	m_cmWeek.AddString(m_szLan);
	g_StringLanType(m_szLan, "星期五", "Friday");
	m_cmWeek.AddString(m_szLan);
	g_StringLanType(m_szLan, "星期六", "Saturday");
	m_cmWeek.AddString(m_szLan);
	g_StringLanType(m_szLan, "星期天", "Sunday");
	m_cmWeek.AddString(m_szLan);


	m_cmWorkMode.ResetContent();
	g_StringLanType(m_szLan, "全天开", "open all day");
	m_cmWorkMode.AddString(m_szLan);
	g_StringLanType(m_szLan, "全天关", "close all day");
	m_cmWorkMode.AddString(m_szLan);
	g_StringLanType(m_szLan, "定时", "time");
	m_cmWorkMode.AddString(m_szLan);


	m_cmWeek.SetCurSel(0);
	m_cmWorkMode.SetCurSel(0);
	m_timeStart1.SetTime(0, 0, 0);
	m_timeStop1.SetTime(0, 0, 0);
	m_timeStart2.SetTime(0, 0, 0);
	m_timeStop2.SetTime(0, 0, 0);
	m_timeStart3.SetTime(0, 0, 0);
	m_timeStop3.SetTime(0, 0, 0);
	m_timeStart4.SetTime(0, 0, 0);
	m_timeStop4.SetTime(0, 0, 0);
	m_timeStart5.SetTime(0, 0, 0);
	m_timeStop5.SetTime(0, 0, 0);
	m_timeStart6.SetTime(0, 0, 0);
	m_timeStop6.SetTime(0, 0, 0);
	m_timeStart7.SetTime(0, 0, 0);
	m_timeStop7.SetTime(0, 0, 0);
	m_timeStart8.SetTime(0, 0, 0);
	m_timeStop8.SetTime(0, 0, 0);


	UpdateData(FALSE);
}


void CDlgScheduleAutoTrack::OnSelchangeComboWeek() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int i = 0;

	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].byWorkMode = m_cmWorkMode.GetCurSel();
// 	for (i = 0; i < MAX_TIMESEGMENT_V30; i++)
// 	{
// 		m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartHour = m_struStartTime[i].GetHour();
// 		m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartMin = m_struStartTime[i].GetMinute();
// 		m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopHour = m_struStopTime[i].GetHour();
// 		m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopMin = m_struStopTime[i].GetMinute();
// 	}

// 	for (i = 0; i < MAX_TIMESEGMENT_V30; i++)
// 	{
// 		m_struStartTime[i].SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartMin, 0);
// 		m_struStopTime[i].SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopMin, 0);
// 	}
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartHour = m_timeStart1.GetHour();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartMin = m_timeStart1.GetMinute();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopHour = m_timeStop1.GetHour();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i++].byStopMin = m_timeStop1.GetMinute();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartHour = m_timeStart2.GetHour();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartMin = m_timeStart2.GetMinute();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopHour = m_timeStop2.GetHour();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i++].byStopMin = m_timeStop2.GetMinute();

	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartHour = m_timeStart3.GetHour();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartMin = m_timeStart3.GetMinute();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopHour = m_timeStop3.GetHour();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i++].byStopMin = m_timeStop3.GetMinute();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartHour = m_timeStart4.GetHour();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartMin = m_timeStart4.GetMinute();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopHour = m_timeStop4.GetHour();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i++].byStopMin = m_timeStop4.GetMinute();

	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartHour = m_timeStart5.GetHour();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartMin = m_timeStart5.GetMinute();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopHour = m_timeStop5.GetHour();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i++].byStopMin = m_timeStop5.GetMinute();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartHour = m_timeStart6.GetHour();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartMin = m_timeStart6.GetMinute();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopHour = m_timeStop6.GetHour();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i++].byStopMin = m_timeStop6.GetMinute();

	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartHour = m_timeStart7.GetHour();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartMin = m_timeStart7.GetMinute();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopHour = m_timeStop7.GetHour();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i++].byStopMin = m_timeStop7.GetMinute();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartHour = m_timeStart8.GetHour();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartMin = m_timeStart8.GetMinute();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopHour = m_timeStop8.GetHour();
	m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i++].byStopMin = m_timeStop8.GetMinute();

	m_iCurWeekIndex = m_cmWeek.GetCurSel();
	m_cmWorkMode.SetCurSel(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].byWorkMode);

	i=0;
	m_timeStart1.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartMin, 0);
	m_timeStop1.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i++].byStopMin, 0);
	m_timeStart2.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartMin, 0);
	m_timeStop2.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i++].byStopMin, 0);
	m_timeStart3.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartMin, 0);
	m_timeStop3.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i++].byStopMin, 0);
	m_timeStart4.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartMin, 0);
	m_timeStop4.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i++].byStopMin, 0);
	m_timeStart5.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartMin, 0);
	m_timeStop5.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i++].byStopMin, 0);
	m_timeStart6.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartMin, 0);
	m_timeStop6.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i++].byStopMin, 0);
	m_timeStart7.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartMin, 0);
	m_timeStop7.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i++].byStopMin, 0);
	m_timeStart8.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartMin, 0);
	m_timeStop8.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopMin, 0);

	UpdateData(FALSE);
}

void CDlgScheduleAutoTrack::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturnLen = 0;
	memset(&m_struScheduleAutoTrack, 0, sizeof(m_struScheduleAutoTrack));
	//m_struScheduleAutoTrack.dwSize = sizeof(m_struScheduleAutoTrack);
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_SCHEDULE_AUTO_TRACK_CFG, 1, &m_struScheduleAutoTrack, sizeof(m_struScheduleAutoTrack), &dwReturnLen))
	{
		CString csStr;
		csStr.Format("err = %d", NET_DVR_GetLastError());
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "get auto track config failed");
		return ;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "get auto track config successful");
	}
	m_chEnable = m_struScheduleAutoTrack.byEnableTrack;
	m_cmWeek.SetCurSel(0);
	m_iCurWeekIndex = 0;
	m_cmWorkMode.SetCurSel(m_struScheduleAutoTrack.struSchedule[0].byWorkMode);

	int i = 0;
	m_timeStart1.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartMin, 0);
	m_timeStop1.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i++].byStopMin, 0);
	m_timeStart2.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartMin, 0);
	m_timeStop2.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i++].byStopMin, 0);
	m_timeStart3.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartMin, 0);
	m_timeStop3.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i++].byStopMin, 0);
	m_timeStart4.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartMin, 0);
	m_timeStop4.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i++].byStopMin, 0);
	m_timeStart5.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartMin, 0);
	m_timeStop5.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i++].byStopMin, 0);
	m_timeStart6.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartMin, 0);
	m_timeStop6.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i++].byStopMin, 0);
	m_timeStart7.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartMin, 0);
	m_timeStop7.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i++].byStopMin, 0);
	m_timeStart8.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStartMin, 0);
	m_timeStop8.SetTime(m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopHour,m_struScheduleAutoTrack.struSchedule[m_iCurWeekIndex].struTime[i].byStopMin, 0);

	UpdateData(FALSE);
	OnSelchangeComboWeek();
}

void CDlgScheduleAutoTrack::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struScheduleAutoTrack.byEnableTrack = m_chEnable;
	OnSelchangeComboWeek();
	m_struScheduleAutoTrack.dwSize = sizeof(m_struScheduleAutoTrack);
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_SCHEDULE_AUTO_TRACK_CFG, 1, &m_struScheduleAutoTrack, sizeof(m_struScheduleAutoTrack)))
	{
		CString csStr;
		csStr.Format("err = %d", NET_DVR_GetLastError());
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Set auto track config failed");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Set auto track config successful");
	}
}
