// DlgSystemTimeAlarm.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgSystemTimeAlarm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgSystemTimeAlarm dialog


DlgSystemTimeAlarm::DlgSystemTimeAlarm(CWnd* pParent /*=NULL*/)
	: CDialog(DlgSystemTimeAlarm::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgSystemTimeAlarm)
	m_bMandatoryAlarm = FALSE;
	m_hour11 = 0;
	m_hour12 = 0;
	m_hour14 = 0;
	m_hour15 = 0;
	m_hour21 = 0;
	m_hour22 = 0;
	m_hour24 = 0;
	m_hour25 = 0;
	m_hour31 = 0;
	m_hour32 = 0;
	m_hour33 = 0;
	m_hour34 = 0;
	m_hour41 = 0;
	m_hour42 = 0;
	m_hour44 = 0;
	m_hour43 = 0;
	m_hour51 = 0;
	m_hour52 = 0;
	m_hour53 = 0;
	m_hour54 = 0;
	m_hour61 = 0;
	m_hour62 = 0;
	m_hour64 = 0;
	m_hour65 = 0;
	m_hour71 = 0;
	m_hour73 = 0;
	m_hour72 = 0;
	m_hour74 = 0;
	m_hour81 = 0;
	m_hour82 = 0;
	m_hour83 = 0;
	m_hour84 = 0;
	m_min11 = 0;
	m_min12 = 0;
	m_min13 = 0;
	m_min14 = 0;
	m_min21 = 0;
	m_min22 = 0;
	m_min23 = 0;
	m_min24 = 0;
	m_min31 = 0;
	m_min32 = 0;
	m_min34 = 0;
	m_min41 = 0;
	m_min33 = 0;
	m_min42 = 0;
	m_min43 = 0;
	m_min44 = 0;
	m_min51 = 0;
	m_min52 = 0;
	m_min53 = 0;
	m_min54 = 0;
	m_min61 = 0;
	m_min62 = 0;
	m_min63 = 0;
	m_min64 = 0;
	m_min71 = 0;
	m_min72 = 0;
	m_min73 = 0;
	m_min74 = 0;
	m_min81 = 0;
	m_min82 = 0;
	m_min83 = 0;
	m_min84 = 0;
	m_startDay = 0;
	m_startMonth = 0;
	m_endMonth = 0;
	m_endDay = 0;
	m_bPriorScheduleOn = FALSE;
	m_bNormalSchedule = FALSE;
	m_bPriorMandatoryAlarm = FALSE;
	m_subSystem = 1;
	//}}AFX_DATA_INIT
	memset(&m_sturSubsystemAlarm,0,sizeof(m_sturSubsystemAlarm));
	memset(&m_struPriorSchedAlarm,0,sizeof(m_struPriorSchedAlarm));
	m_iDevIndex = 0;
	m_lServerID = 0;
}


void DlgSystemTimeAlarm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgSystemTimeAlarm)
	DDX_Control(pDX, IDC_LIST_SYSTEM, m_listSystem);
	DDX_Control(pDX, IDC_COMBO_PRIOR_ALARM_TYPE8, m_comPriorAlarmType8);
	DDX_Control(pDX, IDC_COMBO_PRIOR_ALARM_TYPE7, m_comPriorAlarmType7);
	DDX_Control(pDX, IDC_COMBO_PRIOR_ALARM_TYPE6, m_comPriorAlarmType6);
	DDX_Control(pDX, IDC_COMBO_PRIOR_ALARM_TYPE5, m_comPriorAlarmType5);
	DDX_Control(pDX, IDC_COMBO_PRIOR_ALARM_TYPE3, m_comPriorAlarmType3);
	DDX_Control(pDX, IDC_COMBO_PRIOR_ALARM_TYPE2, m_comPriorAlarmType2);
	DDX_Control(pDX, IDC_COMBO_PRIOR_ALARM_TYPE4, m_comPriorAlarmType4);
	DDX_Control(pDX, IDC_COMBO_PRIOR_ALARM_TYPE1, m_comPriorAlarmType1);
	DDX_Control(pDX, IDC_COMBO_NORMAL_ALARM_TYPE8, m_comNormalAlarmType8);
	DDX_Control(pDX, IDC_COMBO_NORMAL_ALARM_TYPE7, m_comNormalAlarmType7);
	DDX_Control(pDX, IDC_COMBO_NORMAL_ALARM_TYPE6, m_comNormalAlarmType6);
	DDX_Control(pDX, IDC_COMBO_NORMAL_ALARM_TYPE5, m_comNormalAlarmType5);
	DDX_Control(pDX, IDC_COMBO_NORMAL_ALARM_TYPE4, m_comNormalAlarmType4);
	DDX_Control(pDX, IDC_COMBO_NORMAL_ALARM_TYPE3, m_comNormalAlarmType3);
	DDX_Control(pDX, IDC_COMBO_NORMAL_ALARM_TYPE2, m_comNormalAlarmType2);
	DDX_Control(pDX, IDC_COMBO_NORMAL_ALARM_TYPE1, m_comNormalAlarmType1);
	DDX_Control(pDX, IDC_COMBO_PRIOR_TIME, m_comPriorTime);
	DDX_Control(pDX, IDC_COMBO_NORAML_TIME, m_comNormalTime);
	DDX_Check(pDX, IDC_CHK_MANDATORY_ALARM, m_bMandatoryAlarm);
	DDX_Text(pDX, IDC_EDIT_HOUR11, m_hour11);
	DDX_Text(pDX, IDC_EDIT_HOUR12, m_hour12);
	DDX_Text(pDX, IDC_EDIT_HOUR14, m_hour14);
	DDX_Text(pDX, IDC_EDIT_HOUR15, m_hour15);
	DDX_Text(pDX, IDC_EDIT_HOUR21, m_hour21);
	DDX_Text(pDX, IDC_EDIT_HOUR22, m_hour22);
	DDX_Text(pDX, IDC_EDIT_HOUR24, m_hour24);
	DDX_Text(pDX, IDC_EDIT_HOUR25, m_hour25);
	DDX_Text(pDX, IDC_EDIT_HOUR31, m_hour31);
	DDX_Text(pDX, IDC_EDIT_HOUR32, m_hour32);
	DDX_Text(pDX, IDC_EDIT_HOUR33, m_hour33);
	DDX_Text(pDX, IDC_EDIT_HOUR34, m_hour34);
	DDX_Text(pDX, IDC_EDIT_HOUR41, m_hour41);
	DDX_Text(pDX, IDC_EDIT_HOUR42, m_hour42);
	DDX_Text(pDX, IDC_EDIT_HOUR44, m_hour44);
	DDX_Text(pDX, IDC_EDIT_HOUR43, m_hour43);
	DDX_Text(pDX, IDC_EDIT_HOUR51, m_hour51);
	DDX_Text(pDX, IDC_EDIT_HOUR52, m_hour52);
	DDX_Text(pDX, IDC_EDIT_HOUR53, m_hour53);
	DDX_Text(pDX, IDC_EDIT_HOUR54, m_hour54);
	DDX_Text(pDX, IDC_EDIT_HOUR61, m_hour61);
	DDX_Text(pDX, IDC_EDIT_HOUR62, m_hour62);
	DDX_Text(pDX, IDC_EDIT_HOUR64, m_hour64);
	DDX_Text(pDX, IDC_EDIT_HOUR65, m_hour65);
	DDX_Text(pDX, IDC_EDIT_HOUR71, m_hour71);
	DDX_Text(pDX, IDC_EDIT_HOUR73, m_hour73);
	DDX_Text(pDX, IDC_EDIT_HOUR72, m_hour72);
	DDX_Text(pDX, IDC_EDIT_HOUR74, m_hour74);
	DDX_Text(pDX, IDC_EDIT_HOUR81, m_hour81);
	DDX_Text(pDX, IDC_EDIT_HOUR82, m_hour82);
	DDX_Text(pDX, IDC_EDIT_HOUR83, m_hour83);
	DDX_Text(pDX, IDC_EDIT_HOUR84, m_hour84);
	DDX_Text(pDX, IDC_EDIT_MIN11, m_min11);
	DDX_Text(pDX, IDC_EDIT_MIN12, m_min12);
	DDX_Text(pDX, IDC_EDIT_MIN13, m_min13);
	DDX_Text(pDX, IDC_EDIT_MIN14, m_min14);
	DDX_Text(pDX, IDC_EDIT_MIN21, m_min21);
	DDX_Text(pDX, IDC_EDIT_MIN22, m_min22);
	DDX_Text(pDX, IDC_EDIT_MIN23, m_min23);
	DDX_Text(pDX, IDC_EDIT_MIN24, m_min24);
	DDX_Text(pDX, IDC_EDIT_MIN31, m_min31);
	DDX_Text(pDX, IDC_EDIT_MIN32, m_min32);
	DDX_Text(pDX, IDC_EDIT_MIN34, m_min34);
	DDX_Text(pDX, IDC_EDIT_MIN41, m_min41);
	DDX_Text(pDX, IDC_EDIT_MIN33, m_min33);
	DDX_Text(pDX, IDC_EDIT_MIN42, m_min42);
	DDX_Text(pDX, IDC_EDIT_MIN43, m_min43);
	DDX_Text(pDX, IDC_EDIT_MIN44, m_min44);
	DDX_Text(pDX, IDC_EDIT_MIN51, m_min51);
	DDX_Text(pDX, IDC_EDIT_MIN52, m_min52);
	DDX_Text(pDX, IDC_EDIT_MIN53, m_min53);
	DDX_Text(pDX, IDC_EDIT_MIN54, m_min54);
	DDX_Text(pDX, IDC_EDIT_MIN61, m_min61);
	DDX_Text(pDX, IDC_EDIT_MIN62, m_min62);
	DDX_Text(pDX, IDC_EDIT_MIN63, m_min63);
	DDX_Text(pDX, IDC_EDIT_MIN64, m_min64);
	DDX_Text(pDX, IDC_EDIT_MIN71, m_min71);
	DDX_Text(pDX, IDC_EDIT_MIN72, m_min72);
	DDX_Text(pDX, IDC_EDIT_MIN73, m_min73);
	DDX_Text(pDX, IDC_EDIT_MIN74, m_min74);
	DDX_Text(pDX, IDC_EDIT_MIN81, m_min81);
	DDX_Text(pDX, IDC_EDIT_MIN82, m_min82);
	DDX_Text(pDX, IDC_EDIT_MIN83, m_min83);
	DDX_Text(pDX, IDC_EDIT_MIN84, m_min84);
	DDX_Text(pDX, IDC_START_DAY, m_startDay);
	DDX_Text(pDX, IDC_START_MONTH, m_startMonth);
	DDX_Text(pDX, IDC_END_MONTH, m_endMonth);
	DDX_Text(pDX, IDC_END_DAY, m_endDay);
	DDX_Check(pDX, IDC_CHK_PRIOR_SCHEDULE_ON, m_bPriorScheduleOn);
	DDX_Check(pDX, IDC_CHK_NORMAL_SCHEDULE_ON, m_bNormalSchedule);
	DDX_Check(pDX, IDC_CHK_PRIOR_MANDATORY_ALARM, m_bPriorMandatoryAlarm);
	DDX_Text(pDX, IDC_SUBSYSTEM, m_subSystem);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgSystemTimeAlarm, CDialog)
	//{{AFX_MSG_MAP(DlgSystemTimeAlarm)
	ON_BN_CLICKED(IDC_NORMAL_GET, OnGet)
	ON_BN_CLICKED(IDC_NORMAL_SET, OnSet)
	ON_BN_CLICKED(IDC_BTN_NORMAL_OK, OnBtnNormalOk)
	ON_BN_CLICKED(IDC_BTN_PRIOR_OK, OnBtnPriorOk)
	ON_CBN_SELENDCANCEL(IDC_COMBO_PRIOR_TIME, OnSelendcancelComboPriorTime)
	ON_CBN_SELCHANGE(IDC_COMBO_NORAML_TIME, OnSelchangeComboNoramlTime)
	ON_BN_CLICKED(IDC_CHK_PRIOR_SCHEDULE_ON, OnChkPriorScheduleOn)
	ON_BN_CLICKED(IDC_CHK_NORMAL_SCHEDULE_ON, OnChkNormalScheduleOn)
	ON_BN_CLICKED(IDC_PRIOR_GET, OnPriorGet)
	ON_BN_CLICKED(IDC_PRIOR_SET, OnPriorSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgSystemTimeAlarm message handlers

BOOL DlgSystemTimeAlarm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	OnGet();
	OnChkNormalScheduleOn();
	OnChkPriorScheduleOn();
	CString csStr;
	m_listSystem.SetExtendedStyle(LVS_EX_CHECKBOXES);
	for (int i=0; i<32; i++)
	{
		csStr.Format("system%d", i+1);
		m_listSystem.InsertItem(i, csStr);
	}
    return TRUE;
}

void DlgSystemTimeAlarm::OnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	OnBtnNormalOk();
//	OnBtnPriorOk();
	m_sturSubsystemAlarm.byMandatoryAlarm = m_bMandatoryAlarm;
	m_sturSubsystemAlarm.byNormalSchedTimeOn = m_bNormalSchedule;
	m_sturSubsystemAlarm.dwSize = sizeof(m_sturSubsystemAlarm);
//	m_sturSubsystemAlarm.byPriorSchedTimeOn = m_bPriorScheduleOn;
	DWORD returned = 0;
	char szLan[128] = {0};
	if (!NET_DVR_SetDVRConfig(m_lServerID,NET_DVR_SET_SUBSYSTEM_ALARM,m_subSystem,&m_sturSubsystemAlarm,sizeof(m_sturSubsystemAlarm)))
	{
		g_StringLanType(szLan, "设置子系统定时布撤防失败" , "NET_DVR_SET_SUBSYSTEM_ALARM FAILED");
		MessageBox(szLan);
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SUBSYSTEM_ALARM FAILED");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SUBSYSTEM_ALARM SUCC");
	}
}

void DlgSystemTimeAlarm::OnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD returned = 0;
	char szLan[128] = {0};
	if (!NET_DVR_GetDVRConfig(m_lServerID,NET_DVR_GET_SUBSYSTEM_ALARM,m_subSystem,&m_sturSubsystemAlarm,sizeof(m_sturSubsystemAlarm),&returned))
	{
		g_StringLanType(szLan, "获取子系统定时布撤防失败" , "NET_DVR_GET_SUBSYSTEM_ALARM FAILED");
		MessageBox(szLan);
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SUBSYSTEM_ALARM FAILED");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SUBSYSTEM_ALARM SUCC");
	}
	m_comNormalTime.SetCurSel(0);
	m_comPriorTime.SetCurSel(0);
	m_bMandatoryAlarm = m_sturSubsystemAlarm.byMandatoryAlarm;
	m_bNormalSchedule = m_sturSubsystemAlarm.byNormalSchedTimeOn;
//	m_bPriorScheduleOn = m_sturSubsystemAlarm.byPriorSchedTimeOn;
	UpdateData(FALSE);
//	OnSelendcancelComboPriorTime();
	OnSelchangeComboNoramlTime();
}

void DlgSystemTimeAlarm::OnBtnNormalOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (!m_bNormalSchedule)
	{
		return;
	}
	DWORD sel = m_comNormalTime.GetCurSel();
	m_sturSubsystemAlarm.struNormalSchedtime[sel][0].byAlarmType = m_comNormalAlarmType1.GetCurSel();
	m_sturSubsystemAlarm.struNormalSchedtime[sel][1].byAlarmType = m_comNormalAlarmType2.GetCurSel();
	m_sturSubsystemAlarm.struNormalSchedtime[sel][2].byAlarmType = m_comNormalAlarmType3.GetCurSel();
	m_sturSubsystemAlarm.struNormalSchedtime[sel][3].byAlarmType = m_comNormalAlarmType4.GetCurSel();
	m_sturSubsystemAlarm.struNormalSchedtime[sel][4].byAlarmType = m_comNormalAlarmType5.GetCurSel();
	m_sturSubsystemAlarm.struNormalSchedtime[sel][5].byAlarmType = m_comNormalAlarmType6.GetCurSel();
	m_sturSubsystemAlarm.struNormalSchedtime[sel][6].byAlarmType = m_comNormalAlarmType7.GetCurSel();
	m_sturSubsystemAlarm.struNormalSchedtime[sel][7].byAlarmType = m_comNormalAlarmType8.GetCurSel();

	
	m_sturSubsystemAlarm.struNormalSchedtime[sel][0].struTime.byStartHour = m_hour11;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][1].struTime.byStartHour = m_hour21;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][2].struTime.byStartHour = m_hour31;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][3].struTime.byStartHour = m_hour41;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][4].struTime.byStartHour = m_hour51;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][5].struTime.byStartHour = m_hour61;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][6].struTime.byStartHour = m_hour71;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][7].struTime.byStartHour = m_hour81;
	
	m_sturSubsystemAlarm.struNormalSchedtime[sel][0].struTime.byStopHour = m_hour12;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][1].struTime.byStopHour = m_hour22;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][2].struTime.byStopHour = m_hour32;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][3].struTime.byStopHour = m_hour42;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][4].struTime.byStopHour = m_hour52;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][5].struTime.byStopHour = m_hour62;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][6].struTime.byStopHour = m_hour72;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][7].struTime.byStopHour = m_hour82;
	
	m_sturSubsystemAlarm.struNormalSchedtime[sel][0].struTime.byStartMin = m_min11;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][1].struTime.byStartMin = m_min21;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][2].struTime.byStartMin = m_min31;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][3].struTime.byStartMin = m_min41;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][4].struTime.byStartMin = m_min51;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][5].struTime.byStartMin = m_min61;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][6].struTime.byStartMin = m_min71;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][7].struTime.byStartMin = m_min81;
	
	m_sturSubsystemAlarm.struNormalSchedtime[sel][0].struTime.byStopMin = m_min12;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][1].struTime.byStopMin = m_min22;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][2].struTime.byStopMin = m_min32;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][3].struTime.byStopMin = m_min42;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][4].struTime.byStopMin = m_min52;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][5].struTime.byStopMin = m_min62;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][6].struTime.byStopMin = m_min72;
	m_sturSubsystemAlarm.struNormalSchedtime[sel][7].struTime.byStopMin = m_min82;
}

void DlgSystemTimeAlarm::OnBtnPriorOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (!m_bPriorScheduleOn)
	{
		return;
	}
	
	
	m_struPriorSchedAlarm.struOneDayTime[0].byAlarmType = m_comPriorAlarmType1.GetCurSel();
	m_struPriorSchedAlarm.struOneDayTime[1].byAlarmType = m_comPriorAlarmType2.GetCurSel();
	m_struPriorSchedAlarm.struOneDayTime[2].byAlarmType = m_comPriorAlarmType3.GetCurSel();
	m_struPriorSchedAlarm.struOneDayTime[3].byAlarmType = m_comPriorAlarmType4.GetCurSel();
	m_struPriorSchedAlarm.struOneDayTime[4].byAlarmType = m_comPriorAlarmType5.GetCurSel();
	m_struPriorSchedAlarm.struOneDayTime[5].byAlarmType = m_comPriorAlarmType6.GetCurSel();
	m_struPriorSchedAlarm.struOneDayTime[6].byAlarmType = m_comPriorAlarmType7.GetCurSel();
	m_struPriorSchedAlarm.struOneDayTime[7].byAlarmType = m_comPriorAlarmType8.GetCurSel();

	m_struPriorSchedAlarm.struOneDayTime[0].struTime.byStartHour = m_hour14;
	m_struPriorSchedAlarm.struOneDayTime[1].struTime.byStartHour = m_hour24;
	m_struPriorSchedAlarm.struOneDayTime[2].struTime.byStartHour = m_hour33;
	m_struPriorSchedAlarm.struOneDayTime[3].struTime.byStartHour = m_hour43;
	m_struPriorSchedAlarm.struOneDayTime[4].struTime.byStartHour = m_hour53;
	m_struPriorSchedAlarm.struOneDayTime[5].struTime.byStartHour = m_hour64;
	m_struPriorSchedAlarm.struOneDayTime[6].struTime.byStartHour = m_hour73;
	m_struPriorSchedAlarm.struOneDayTime[7].struTime.byStartHour = m_hour83;

	m_struPriorSchedAlarm.struOneDayTime[0].struTime.byStopHour = m_hour15;
	m_struPriorSchedAlarm.struOneDayTime[1].struTime.byStopHour = m_hour25;
	m_struPriorSchedAlarm.struOneDayTime[2].struTime.byStopHour = m_hour34;
	m_struPriorSchedAlarm.struOneDayTime[3].struTime.byStopHour = m_hour44;
	m_struPriorSchedAlarm.struOneDayTime[4].struTime.byStopHour = m_hour54;
	m_struPriorSchedAlarm.struOneDayTime[5].struTime.byStopHour = m_hour65;
	m_struPriorSchedAlarm.struOneDayTime[6].struTime.byStopHour = m_hour74;
	m_struPriorSchedAlarm.struOneDayTime[7].struTime.byStopHour = m_hour84;

	m_struPriorSchedAlarm.struOneDayTime[0].struTime.byStartMin = m_min13;
	m_struPriorSchedAlarm.struOneDayTime[1].struTime.byStartMin = m_min23;
	m_struPriorSchedAlarm.struOneDayTime[2].struTime.byStartMin = m_min33;
	m_struPriorSchedAlarm.struOneDayTime[3].struTime.byStartMin = m_min43;
	m_struPriorSchedAlarm.struOneDayTime[4].struTime.byStartMin = m_min53;
	m_struPriorSchedAlarm.struOneDayTime[5].struTime.byStartMin = m_min63;
	m_struPriorSchedAlarm.struOneDayTime[6].struTime.byStartMin = m_min73;
	m_struPriorSchedAlarm.struOneDayTime[7].struTime.byStartMin = m_min83;

	m_struPriorSchedAlarm.struOneDayTime[0].struTime.byStopMin = m_min14;
	m_struPriorSchedAlarm.struOneDayTime[1].struTime.byStopMin = m_min24;
	m_struPriorSchedAlarm.struOneDayTime[2].struTime.byStopMin = m_min34;
	m_struPriorSchedAlarm.struOneDayTime[3].struTime.byStopMin = m_min44;
	m_struPriorSchedAlarm.struOneDayTime[4].struTime.byStopMin = m_min54;
	m_struPriorSchedAlarm.struOneDayTime[5].struTime.byStopMin = m_min64;
	m_struPriorSchedAlarm.struOneDayTime[6].struTime.byStopMin = m_min74;
	m_struPriorSchedAlarm.struOneDayTime[7].struTime.byStopMin = m_min84;

	m_struPriorSchedAlarm.struData.byStartDay = m_startDay;
	m_struPriorSchedAlarm.struData.byStartMonth = m_startMonth;
	m_struPriorSchedAlarm.struData.byStopDay = m_endDay;
	m_struPriorSchedAlarm.struData.byStopMonth = m_endMonth;

	for(int i = 0;i < 32; i++)
	{
		m_struPriorSchedAlarm.bySubSystem[i] = m_listSystem.GetCheck(i);
	}
}

void DlgSystemTimeAlarm::OnSelendcancelComboPriorTime() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD sel = m_comPriorTime.GetCurSel();
	m_startMonth = m_struPriorSchedAlarm.struData.byStartMonth;
	m_startDay = m_struPriorSchedAlarm.struData.byStartDay;
	m_endMonth = m_struPriorSchedAlarm.struData.byStopMonth;
	m_endDay = m_struPriorSchedAlarm.struData.byStopDay;

	m_comPriorAlarmType1.SetCurSel((int)m_struPriorSchedAlarm.struOneDayTime[0].byAlarmType);
	m_comPriorAlarmType2.SetCurSel((int)m_struPriorSchedAlarm.struOneDayTime[1].byAlarmType);
	m_comPriorAlarmType3.SetCurSel((int)m_struPriorSchedAlarm.struOneDayTime[2].byAlarmType);
	m_comPriorAlarmType4.SetCurSel((int)m_struPriorSchedAlarm.struOneDayTime[3].byAlarmType);
	m_comPriorAlarmType5.SetCurSel((int)m_struPriorSchedAlarm.struOneDayTime[4].byAlarmType);
	m_comPriorAlarmType6.SetCurSel((int)m_struPriorSchedAlarm.struOneDayTime[5].byAlarmType);
	m_comPriorAlarmType7.SetCurSel((int)m_struPriorSchedAlarm.struOneDayTime[6].byAlarmType);
	m_comPriorAlarmType8.SetCurSel((int)m_struPriorSchedAlarm.struOneDayTime[7].byAlarmType);

	m_hour14 = m_struPriorSchedAlarm.struOneDayTime[0].struTime.byStartHour;
	m_hour24 = m_struPriorSchedAlarm.struOneDayTime[1].struTime.byStartHour;
	m_hour33 = m_struPriorSchedAlarm.struOneDayTime[2].struTime.byStartHour;
	m_hour43 = m_struPriorSchedAlarm.struOneDayTime[3].struTime.byStartHour;
	m_hour53 = m_struPriorSchedAlarm.struOneDayTime[4].struTime.byStartHour;
	m_hour64 = m_struPriorSchedAlarm.struOneDayTime[5].struTime.byStartHour;
	m_hour73 = m_struPriorSchedAlarm.struOneDayTime[6].struTime.byStartHour;
	m_hour83 = m_struPriorSchedAlarm.struOneDayTime[7].struTime.byStartHour;

	m_hour15 = m_struPriorSchedAlarm.struOneDayTime[0].struTime.byStopHour;
	m_hour25 = m_struPriorSchedAlarm.struOneDayTime[1].struTime.byStopHour;
	m_hour34 = m_struPriorSchedAlarm.struOneDayTime[2].struTime.byStopHour;
	m_hour44 = m_struPriorSchedAlarm.struOneDayTime[3].struTime.byStopHour;
	m_hour54 = m_struPriorSchedAlarm.struOneDayTime[4].struTime.byStopHour;
	m_hour65 = m_struPriorSchedAlarm.struOneDayTime[5].struTime.byStopHour;
	m_hour74 = m_struPriorSchedAlarm.struOneDayTime[6].struTime.byStopHour;
	m_hour84 = m_struPriorSchedAlarm.struOneDayTime[7].struTime.byStopHour;
	
	m_min13 = m_struPriorSchedAlarm.struOneDayTime[0].struTime.byStartMin;
	m_min23 = m_struPriorSchedAlarm.struOneDayTime[1].struTime.byStartMin;
	m_min33 = m_struPriorSchedAlarm.struOneDayTime[2].struTime.byStartMin;
	m_min43 = m_struPriorSchedAlarm.struOneDayTime[3].struTime.byStartMin;
	m_min53 = m_struPriorSchedAlarm.struOneDayTime[4].struTime.byStartMin;
	m_min63 = m_struPriorSchedAlarm.struOneDayTime[5].struTime.byStartMin;
	m_min73 = m_struPriorSchedAlarm.struOneDayTime[6].struTime.byStartMin;
	m_min83 = m_struPriorSchedAlarm.struOneDayTime[7].struTime.byStartMin;
	
	m_min14 = m_struPriorSchedAlarm.struOneDayTime[0].struTime.byStopMin;
	m_min24 = m_struPriorSchedAlarm.struOneDayTime[1].struTime.byStopMin;
	m_min34 = m_struPriorSchedAlarm.struOneDayTime[2].struTime.byStopMin;
	m_min44 = m_struPriorSchedAlarm.struOneDayTime[3].struTime.byStopMin;
	m_min54 = m_struPriorSchedAlarm.struOneDayTime[4].struTime.byStopMin;
	m_min64 = m_struPriorSchedAlarm.struOneDayTime[5].struTime.byStopMin;
	m_min74 = m_struPriorSchedAlarm.struOneDayTime[6].struTime.byStopMin;
	m_min84 = m_struPriorSchedAlarm.struOneDayTime[7].struTime.byStopMin;
	for (int i=0; i<32; i++)
	{
		m_listSystem.SetCheck(i, (BOOL)(m_struPriorSchedAlarm.bySubSystem[i]));
	}
	UpdateData(FALSE);
}

void DlgSystemTimeAlarm::OnSelchangeComboNoramlTime() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD sel = m_comNormalTime.GetCurSel();
	m_comNormalAlarmType1.SetCurSel((int)m_sturSubsystemAlarm.struNormalSchedtime[sel][0].byAlarmType);
	m_comNormalAlarmType2.SetCurSel((int)m_sturSubsystemAlarm.struNormalSchedtime[sel][1].byAlarmType);
	m_comNormalAlarmType3.SetCurSel((int)m_sturSubsystemAlarm.struNormalSchedtime[sel][2].byAlarmType);
	m_comNormalAlarmType4.SetCurSel((int)m_sturSubsystemAlarm.struNormalSchedtime[sel][3].byAlarmType);
	m_comNormalAlarmType5.SetCurSel((int)m_sturSubsystemAlarm.struNormalSchedtime[sel][4].byAlarmType);
	m_comNormalAlarmType6.SetCurSel((int)m_sturSubsystemAlarm.struNormalSchedtime[sel][5].byAlarmType);
	m_comNormalAlarmType7.SetCurSel((int)m_sturSubsystemAlarm.struNormalSchedtime[sel][6].byAlarmType);
	m_comNormalAlarmType8.SetCurSel((int)m_sturSubsystemAlarm.struNormalSchedtime[sel][7].byAlarmType);
	
	m_hour11 = m_sturSubsystemAlarm.struNormalSchedtime[sel][0].struTime.byStartHour;
	m_hour21 = m_sturSubsystemAlarm.struNormalSchedtime[sel][1].struTime.byStartHour;
	m_hour31 = m_sturSubsystemAlarm.struNormalSchedtime[sel][2].struTime.byStartHour;
	m_hour41 = m_sturSubsystemAlarm.struNormalSchedtime[sel][3].struTime.byStartHour;
	m_hour51 = m_sturSubsystemAlarm.struNormalSchedtime[sel][4].struTime.byStartHour;
	m_hour61 = m_sturSubsystemAlarm.struNormalSchedtime[sel][5].struTime.byStartHour;
	m_hour71 = m_sturSubsystemAlarm.struNormalSchedtime[sel][6].struTime.byStartHour;
	m_hour81 = m_sturSubsystemAlarm.struNormalSchedtime[sel][7].struTime.byStartHour;
	
	m_hour12 = m_sturSubsystemAlarm.struNormalSchedtime[sel][0].struTime.byStopHour;
	m_hour22 = m_sturSubsystemAlarm.struNormalSchedtime[sel][1].struTime.byStopHour;
	m_hour32 = m_sturSubsystemAlarm.struNormalSchedtime[sel][2].struTime.byStopHour;
	m_hour42 = m_sturSubsystemAlarm.struNormalSchedtime[sel][3].struTime.byStopHour;
	m_hour52 = m_sturSubsystemAlarm.struNormalSchedtime[sel][4].struTime.byStopHour;
	m_hour62 = m_sturSubsystemAlarm.struNormalSchedtime[sel][5].struTime.byStopHour;
	m_hour72 = m_sturSubsystemAlarm.struNormalSchedtime[sel][6].struTime.byStopHour;
	m_hour82 = m_sturSubsystemAlarm.struNormalSchedtime[sel][7].struTime.byStopHour;
	
	m_min11 = m_sturSubsystemAlarm.struNormalSchedtime[sel][0].struTime.byStartMin;
	m_min21 = m_sturSubsystemAlarm.struNormalSchedtime[sel][1].struTime.byStartMin;
	m_min31 = m_sturSubsystemAlarm.struNormalSchedtime[sel][2].struTime.byStartMin;
	m_min41 = m_sturSubsystemAlarm.struNormalSchedtime[sel][3].struTime.byStartMin;
	m_min51 = m_sturSubsystemAlarm.struNormalSchedtime[sel][4].struTime.byStartMin;
	m_min61 = m_sturSubsystemAlarm.struNormalSchedtime[sel][5].struTime.byStartMin;
	m_min71 = m_sturSubsystemAlarm.struNormalSchedtime[sel][6].struTime.byStartMin;
	m_min81 = m_sturSubsystemAlarm.struNormalSchedtime[sel][7].struTime.byStartMin;
	
	m_min12 = m_sturSubsystemAlarm.struNormalSchedtime[sel][0].struTime.byStopMin;
	m_min22 = m_sturSubsystemAlarm.struNormalSchedtime[sel][1].struTime.byStopMin;
	m_min32 = m_sturSubsystemAlarm.struNormalSchedtime[sel][2].struTime.byStopMin;
	m_min42 = m_sturSubsystemAlarm.struNormalSchedtime[sel][3].struTime.byStopMin;
	m_min52 = m_sturSubsystemAlarm.struNormalSchedtime[sel][4].struTime.byStopMin;
	m_min62 = m_sturSubsystemAlarm.struNormalSchedtime[sel][5].struTime.byStopMin;
	m_min72 = m_sturSubsystemAlarm.struNormalSchedtime[sel][6].struTime.byStopMin;
	m_min82 = m_sturSubsystemAlarm.struNormalSchedtime[sel][7].struTime.byStopMin;
	
	UpdateData(FALSE);
}

void DlgSystemTimeAlarm::OnChkPriorScheduleOn() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_bPriorScheduleOn)
	{
		GetDlgItem(IDC_COMBO_PRIOR_ALARM_TYPE1)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_PRIOR_ALARM_TYPE2)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_PRIOR_ALARM_TYPE3)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_PRIOR_ALARM_TYPE4)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_PRIOR_ALARM_TYPE5)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_PRIOR_ALARM_TYPE6)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_PRIOR_ALARM_TYPE7)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_PRIOR_ALARM_TYPE8)->EnableWindow(TRUE);

		GetDlgItem(IDC_EDIT_HOUR14)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR15)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR24)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR25)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR34)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR33)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR44)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR43)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR54)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR53)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR65)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR64)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR74)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR73)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR84)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR83)->EnableWindow(TRUE);

		GetDlgItem(IDC_EDIT_MIN13)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN14)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN23)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN24)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN33)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN34)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN43)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN44)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN53)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN54)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN63)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN64)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN73)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN74)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN83)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN84)->EnableWindow(TRUE);
		GetDlgItem(IDC_START_DAY)->EnableWindow(TRUE);
		GetDlgItem(IDC_START_MONTH)->EnableWindow(TRUE);
		GetDlgItem(IDC_END_DAY)->EnableWindow(TRUE);
		GetDlgItem(IDC_END_MONTH)->EnableWindow(TRUE);

		GetDlgItem(IDC_COMBO_PRIOR_TIME)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_COMBO_PRIOR_ALARM_TYPE1)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_PRIOR_ALARM_TYPE2)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_PRIOR_ALARM_TYPE3)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_PRIOR_ALARM_TYPE4)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_PRIOR_ALARM_TYPE5)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_PRIOR_ALARM_TYPE6)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_PRIOR_ALARM_TYPE7)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_PRIOR_ALARM_TYPE8)->EnableWindow(FALSE);
		
		GetDlgItem(IDC_EDIT_HOUR14)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR15)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR24)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR25)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR34)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR33)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR44)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR43)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR54)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR53)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR65)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR64)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR74)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR73)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR84)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR83)->EnableWindow(FALSE);
		
		GetDlgItem(IDC_EDIT_MIN13)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN14)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN23)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN24)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN33)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN34)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN43)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN44)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN53)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN54)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN63)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN64)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN73)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN74)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN83)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN84)->EnableWindow(FALSE);
		GetDlgItem(IDC_START_DAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_START_MONTH)->EnableWindow(FALSE);
		GetDlgItem(IDC_END_DAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_END_MONTH)->EnableWindow(FALSE);

		GetDlgItem(IDC_COMBO_PRIOR_TIME)->EnableWindow(FALSE);
	}
	UpdateData(FALSE);
}

void DlgSystemTimeAlarm::OnChkNormalScheduleOn() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_bNormalSchedule)
	{
		GetDlgItem(IDC_COMBO_NORMAL_ALARM_TYPE1)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_NORMAL_ALARM_TYPE2)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_NORMAL_ALARM_TYPE3)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_NORMAL_ALARM_TYPE4)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_NORMAL_ALARM_TYPE5)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_NORMAL_ALARM_TYPE6)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_NORMAL_ALARM_TYPE7)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_NORMAL_ALARM_TYPE8)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR11)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR12)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR21)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR22)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR31)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR32)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR41)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR42)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR51)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR52)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR61)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR62)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR71)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR72)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR81)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_HOUR82)->EnableWindow(TRUE);
		
		GetDlgItem(IDC_EDIT_MIN11)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN12)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN21)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN22)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN31)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN32)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN41)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN42)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN51)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN52)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN61)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN62)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN71)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN72)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN81)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIN82)->EnableWindow(TRUE);

		GetDlgItem(IDC_COMBO_NORAML_TIME)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_COMBO_NORMAL_ALARM_TYPE1)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_NORMAL_ALARM_TYPE2)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_NORMAL_ALARM_TYPE3)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_NORMAL_ALARM_TYPE4)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_NORMAL_ALARM_TYPE5)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_NORMAL_ALARM_TYPE6)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_NORMAL_ALARM_TYPE7)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_NORMAL_ALARM_TYPE8)->EnableWindow(FALSE);

		GetDlgItem(IDC_EDIT_HOUR11)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR12)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR21)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR22)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR31)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR32)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR41)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR42)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR51)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR52)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR61)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR62)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR71)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR72)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR81)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_HOUR82)->EnableWindow(FALSE);
		
		GetDlgItem(IDC_EDIT_MIN11)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN12)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN21)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN22)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN31)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN32)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN41)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN42)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN51)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN52)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN61)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN62)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN71)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN72)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN81)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIN82)->EnableWindow(FALSE);

		GetDlgItem(IDC_COMBO_NORAML_TIME)->EnableWindow(FALSE);
	}
	UpdateData(FALSE);
}

void DlgSystemTimeAlarm::OnPriorGet() 
{
	// TODO: Add your control notification handler code here
	m_struPriorSchedAlarm.dwSize = sizeof(NET_DVR_PRIOR_SCHEDTIME);
	char szLan[128] = {0};
	DWORD dwReturned = 0;
	DWORD sel = m_comPriorTime.GetCurSel() + 1;
	if (!NET_DVR_GetDVRConfig(m_lServerID,NET_DVR_GET_PRIOR_ALARM,sel,&m_struPriorSchedAlarm,sizeof(m_struPriorSchedAlarm),&dwReturned))
	{
		g_StringLanType(szLan, "获取优先计划子系统定时布撤防失败" , "NET_DVR_GET_PRIOR_ALARM FAILED");
		MessageBox(szLan);
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PRIOR_ALARM FAILED");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PRIOR_ALARM SUCC");
	}
	m_bPriorMandatoryAlarm = m_struPriorSchedAlarm.byMandatoryAlarm;
	m_bPriorScheduleOn = m_struPriorSchedAlarm.byEnable;
	UpdateData(FALSE);
	OnChkPriorScheduleOn();
	OnSelendcancelComboPriorTime();
}

void DlgSystemTimeAlarm::OnPriorSet() 
{
	// TODO: Add your control notification handler code here
	OnBtnPriorOk();
	UpdateData(TRUE);
	int sel = m_comPriorTime.GetCurSel() + 1;
	m_struPriorSchedAlarm.byMandatoryAlarm = m_bPriorMandatoryAlarm;
	m_struPriorSchedAlarm.byEnable = m_bPriorScheduleOn;
	OnChkPriorScheduleOn();
	m_struPriorSchedAlarm.dwSize = sizeof(NET_DVR_PRIOR_SCHEDTIME);
	char szLan[128] = {0};
	if (!NET_DVR_SetDVRConfig(m_lServerID,NET_DVR_SET_PRIOR_ALARM,sel,&m_struPriorSchedAlarm,sizeof(m_struPriorSchedAlarm)))
	{
		g_StringLanType(szLan, "设置优先计划子系统定时布撤防失败" , "NET_DVR_SET_PRIOR_ALARM FAILED");
		MessageBox(szLan);
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_PRIOR_ALARM FAILED");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_PRIOR_ALARM SUCC");
	}
}
