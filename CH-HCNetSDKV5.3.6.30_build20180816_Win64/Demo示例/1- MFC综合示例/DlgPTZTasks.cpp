// DlgPTZTasks.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPTZTasks.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPTZTasks dialog


CDlgPTZTasks::CDlgPTZTasks(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPTZTasks::IDD, pParent),
	m_iDevIndex(-1),
	m_lServerID(-1),
	m_iChanNo(0)
	, m_iHour11(0)
	, m_iMin11(0)
	, m_iHour12(0)
	, m_iMin12(0)
	, m_iHour21(0)
	, m_iMin21(0)
	, m_iHour22(0)
	, m_iMin22(0)
	, m_iHour31(0)
	, m_iMin31(0)
	, m_iHour32(0)
	, m_iMin32(0)
	, m_iHour41(0)
	, m_iMin41(0)
	, m_iHour42(0)
	, m_iMin42(0)
	, m_iHour51(0)
	, m_iMin51(0)
	, m_iHour52(0)
	, m_iMin52(0)
	, m_iHour61(0)
	, m_iMin61(0)
	, m_iHour62(0)
	, m_iMin62(0)
	, m_iHour71(0)
	, m_iMin71(0)
	, m_iHour72(0)
	, m_iMin72(0)
	, m_iHour81(0)
	, m_iMin81(0)
	, m_iHour82(0)
	, m_iMin82(0)

{
	//{{AFX_DATA_INIT(CDlgPTZTasks)
	m_iParkTime = 0;
	m_bEnable = FALSE;
	m_iMin91 = 0;
	m_iMin92 = 0;
	m_iMin101 = 0;
	m_iMin102 = 0;
	m_iHour92 = 0;
	m_iHour91 = 0;
	m_iHour102 = 0;
	m_iHour101 = 0;
	m_iChidAction1 = 0;
	m_iChidAction10 = 0;
	m_iChidAction2 = 0;
	m_iChidAction3 = 0;
	m_iChidAction4 = 0;
	m_iChidAction5 = 0;
	m_iChidAction6 = 0;
	m_iChidAction7 = 0;
	m_iChidAction8 = 0;
	m_iChidAction9 = 0;
	//}}AFX_DATA_INIT
}


void CDlgPTZTasks::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPTZTasks)
	DDX_Control(pDX, IDC_COMBO_ACTION9, m_comboAction9);
	DDX_Control(pDX, IDC_COMBO_ACTION8, m_comboAction8);
	DDX_Control(pDX, IDC_COMBO_ACTION7, m_comboAction7);
	DDX_Control(pDX, IDC_COMBO_ACTION6, m_comboAction6);
	DDX_Control(pDX, IDC_COMBO_ACTION5, m_comboAction5);
	DDX_Control(pDX, IDC_COMBO_ACTION4, m_comboAction4);
	DDX_Control(pDX, IDC_COMBO_ACTION3, m_comboAction3);
	DDX_Control(pDX, IDC_COMBO_ACTION2, m_comboAction2);
	DDX_Control(pDX, IDC_COMBO_ACTION10, m_comboAction10);
	DDX_Control(pDX, IDC_COMBO_ACTION1, m_comboAction1);
	DDX_Text(pDX, IDC_EDT_PARKTIME, m_iParkTime);
	DDX_Check(pDX, IDC_CHK_TASK, m_bEnable);
	DDX_Text(pDX, IDC_EDIT_MIN91, m_iMin91);
	DDX_Text(pDX, IDC_EDIT_MIN92, m_iMin92);
	DDX_Text(pDX, IDC_EDIT_MIN102, m_iMin101);
	DDX_Text(pDX, IDC_EDIT_MIN101, m_iMin102);
	DDX_Text(pDX, IDC_EDIT_HOUR92, m_iHour92);
	DDX_Text(pDX, IDC_EDIT_HOUR91, m_iHour91);
	DDX_Text(pDX, IDC_EDIT_HOUR102, m_iHour102);
	DDX_Text(pDX, IDC_EDIT_HOUR101, m_iHour101);
	DDX_Text(pDX, IDC_EDT_ACTION1, m_iChidAction1);
	DDX_Text(pDX, IDC_EDT_ACTION10, m_iChidAction10);
	DDX_Text(pDX, IDC_EDT_ACTION2, m_iChidAction2);
	DDX_Text(pDX, IDC_EDT_ACTION3, m_iChidAction3);
	DDX_Text(pDX, IDC_EDT_ACTION4, m_iChidAction4);
	DDX_Text(pDX, IDC_EDT_ACTION5, m_iChidAction5);
	DDX_Text(pDX, IDC_EDT_ACTION6, m_iChidAction6);
	DDX_Text(pDX, IDC_EDT_ACTION7, m_iChidAction7);
	DDX_Text(pDX, IDC_EDT_ACTION8, m_iChidAction8);
	DDX_Text(pDX, IDC_EDT_ACTION9, m_iChidAction9);
	DDX_Text(pDX, IDC_EDIT_HOUR11, m_iHour11);
	DDX_Text(pDX, IDC_EDIT_MIN11, m_iMin11);
	DDX_Text(pDX, IDC_EDIT_HOUR12, m_iHour12);
	DDX_Text(pDX, IDC_EDIT_MIN12, m_iMin12);
	DDX_Text(pDX, IDC_EDIT_HOUR21, m_iHour21);
	DDX_Text(pDX, IDC_EDIT_MIN21, m_iMin21);
	DDX_Text(pDX, IDC_EDIT_HOUR22, m_iHour22);
	DDX_Text(pDX, IDC_EDIT_MIN22, m_iMin22);
	DDX_Text(pDX, IDC_EDIT_HOUR31, m_iHour31);
	DDX_Text(pDX, IDC_EDIT_MIN31, m_iMin31);
	DDX_Text(pDX, IDC_EDIT_HOUR32, m_iHour32);
	DDX_Text(pDX, IDC_EDIT_MIN32, m_iMin32);
	DDX_Text(pDX, IDC_EDIT_HOUR41, m_iHour41);
	DDX_Text(pDX, IDC_EDIT_MIN41, m_iMin41);
	DDX_Text(pDX, IDC_EDIT_HOUR42, m_iHour42);
	DDX_Text(pDX, IDC_EDIT_MIN42, m_iMin42);
	DDX_Text(pDX, IDC_EDIT_HOUR51, m_iHour51);
	DDX_Text(pDX, IDC_EDIT_MIN51, m_iMin51);
	DDX_Text(pDX, IDC_EDIT_HOUR52, m_iHour52);
	DDX_Text(pDX, IDC_EDIT_MIN52, m_iMin52);
	DDX_Text(pDX, IDC_EDIT_HOUR61, m_iHour61);
	DDX_Text(pDX, IDC_EDIT_MIN61, m_iMin61);
	DDX_Text(pDX, IDC_EDIT_HOUR62, m_iHour62);
	DDX_Text(pDX, IDC_EDIT_MIN62, m_iMin62);
	DDX_Text(pDX, IDC_EDIT_HOUR71, m_iHour71);
	DDX_Text(pDX, IDC_EDIT_MIN71, m_iMin71);
	DDX_Text(pDX, IDC_EDIT_HOUR72, m_iHour72);
	DDX_Text(pDX, IDC_EDIT_MIN72, m_iMin72);
	DDX_Text(pDX, IDC_EDIT_HOUR81, m_iHour81);
	DDX_Text(pDX, IDC_EDIT_MIN81, m_iMin81);
	DDX_Text(pDX, IDC_EDIT_HOUR82, m_iHour82);
	DDX_Text(pDX, IDC_EDIT_MIN82, m_iMin82);	
	DDX_Control(pDX, IDC_COMBO_ALARMIN_WEEKDAY, m_comboWeekday);
	DDX_Control(pDX, IDC_COMBO_ALARMIN_COPY_TIME, m_comboCopyTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPTZTasks, CDialog)
	//{{AFX_MSG_MAP(CDlgPTZTasks)
	ON_BN_CLICKED(IDC_BTN_ALARM_IN_TIME_OK, OnBtnAlarmInTimeOk)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARMIN_WEEKDAY, OnCbnSelchangeComboAlarminWeekday)
	ON_BN_CLICKED(IDC_BTN_ALARMIN_TIME_COPY, OnBtnAlarminTimeCopy)
	ON_BN_CLICKED(IDC_BTN_GETTASKS, OnBtnGettasks)
	ON_BN_CLICKED(IDC_BTN_SETTASK, OnBtnSettask)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPTZTasks message handlers

void CDlgPTZTasks::OnBtnAlarmInTimeOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (!TimeTest())
	{
		return;
	}
	int	i = m_comboWeekday.GetCurSel();	
	
	m_struAlarmTime[i][0].byStartHour = (BYTE)m_iHour11;
	m_struAlarmTime[i][0].byStartMin = (BYTE)m_iMin11;
	m_struAlarmTime[i][0].byStopHour = (BYTE)m_iHour12;
	m_struAlarmTime[i][0].byStopMin = (BYTE)m_iMin12;
	m_struAlarmTime[i][1].byStartHour = (BYTE)m_iHour21;
	m_struAlarmTime[i][1].byStartMin = (BYTE)m_iMin21;
	m_struAlarmTime[i][1].byStopHour = (BYTE)m_iHour22;
	m_struAlarmTime[i][1].byStopMin = (BYTE)m_iMin22;
	m_struAlarmTime[i][2].byStartHour = (BYTE)m_iHour31;
	m_struAlarmTime[i][2].byStartMin = (BYTE)m_iMin31;
	m_struAlarmTime[i][2].byStopHour = (BYTE)m_iHour32;
	m_struAlarmTime[i][2].byStopMin = (BYTE)m_iMin32;
	m_struAlarmTime[i][3].byStartHour = (BYTE)m_iHour41;
	m_struAlarmTime[i][3].byStartMin = (BYTE)m_iMin41;
	m_struAlarmTime[i][3].byStopHour = (BYTE)m_iHour42;
	m_struAlarmTime[i][3].byStopMin = (BYTE)m_iMin42;
	m_struAlarmTime[i][4].byStartHour = (BYTE)m_iHour51;
	m_struAlarmTime[i][4].byStartMin = (BYTE)m_iMin51;
	m_struAlarmTime[i][4].byStopHour = (BYTE)m_iHour52;
	m_struAlarmTime[i][4].byStopMin = (BYTE)m_iMin52;
	m_struAlarmTime[i][5].byStartHour = (BYTE)m_iHour61;
	m_struAlarmTime[i][5].byStartMin = (BYTE)m_iMin61;
	m_struAlarmTime[i][5].byStopHour = (BYTE)m_iHour62;
	m_struAlarmTime[i][5].byStopMin = (BYTE)m_iMin62;
	m_struAlarmTime[i][6].byStartHour = (BYTE)m_iHour71;
	m_struAlarmTime[i][6].byStartMin = (BYTE)m_iMin71;
	m_struAlarmTime[i][6].byStopHour = (BYTE)m_iHour72;
	m_struAlarmTime[i][6].byStopMin = (BYTE)m_iMin72;
	m_struAlarmTime[i][7].byStartHour = (BYTE)m_iHour81;
	m_struAlarmTime[i][7].byStartMin = (BYTE)m_iMin81;
	m_struAlarmTime[i][7].byStopHour = (BYTE)m_iHour82;
    m_struAlarmTime[i][7].byStopMin = (BYTE)m_iMin82;
	m_struAlarmTime[i][8].byStartHour = (BYTE)m_iHour91;
	m_struAlarmTime[i][8].byStartMin = (BYTE)m_iMin91;
	m_struAlarmTime[i][8].byStopHour = (BYTE)m_iHour92;
    m_struAlarmTime[i][8].byStopMin = (BYTE)m_iMin92;
	m_struAlarmTime[i][9].byStartHour = (BYTE)m_iHour101;
	m_struAlarmTime[i][9].byStartMin = (BYTE)m_iMin101;
	m_struAlarmTime[i][9].byStopHour = (BYTE)m_iHour102;
    m_struAlarmTime[i][9].byStopMin = (BYTE)m_iMin102;
	
	m_struTimeTask.struTask[i][0].wAction = m_comboAction1.GetCurSel();
	m_struTimeTask.struTask[i][1].wAction = m_comboAction2.GetCurSel();
	m_struTimeTask.struTask[i][2].wAction = m_comboAction3.GetCurSel();
	m_struTimeTask.struTask[i][3].wAction = m_comboAction4.GetCurSel();
	m_struTimeTask.struTask[i][4].wAction = m_comboAction5.GetCurSel();
	m_struTimeTask.struTask[i][5].wAction = m_comboAction6.GetCurSel();
	m_struTimeTask.struTask[i][6].wAction = m_comboAction7.GetCurSel();
	m_struTimeTask.struTask[i][7].wAction = m_comboAction8.GetCurSel();
	m_struTimeTask.struTask[i][8].wAction = m_comboAction9.GetCurSel();
	m_struTimeTask.struTask[i][9].wAction = m_comboAction10.GetCurSel();

	m_struTimeTask.struTask[i][0].wActionNum = m_iChidAction1;
	m_struTimeTask.struTask[i][1].wActionNum = m_iChidAction2;
	m_struTimeTask.struTask[i][2].wActionNum = m_iChidAction3;
	m_struTimeTask.struTask[i][3].wActionNum = m_iChidAction4;
	m_struTimeTask.struTask[i][4].wActionNum = m_iChidAction5;
	m_struTimeTask.struTask[i][5].wActionNum = m_iChidAction6;
	m_struTimeTask.struTask[i][6].wActionNum = m_iChidAction7;
	m_struTimeTask.struTask[i][7].wActionNum = m_iChidAction8;
	m_struTimeTask.struTask[i][8].wActionNum = m_iChidAction9;
	m_struTimeTask.struTask[i][9].wActionNum = m_iChidAction10;

	GetDlgItem(IDC_BTN_ALARMIN_TIME_COPY)->EnableWindow(TRUE);
}

BOOL CDlgPTZTasks::TimeTest()
{
	int i = 0;
	int j = 0;
	WORD wStartTime[MAX_SCH_TASKS_NUM], wStopTime[MAX_SCH_TASKS_NUM];
	char szLan[1024] = {0};
	UpdateData(TRUE);
	if ((m_iHour11 < 0) || (m_iHour11 > 24) || (m_iHour12 < 0) || (m_iHour12 > 24) ||	\
		(m_iHour21 < 0) || (m_iHour21 > 24) || (m_iHour22 < 0) || (m_iHour22 > 24) ||	\
		(m_iHour31 < 0) || (m_iHour31 > 24) || (m_iHour32 < 0) || (m_iHour32 > 24) ||	\
		(m_iHour41 < 0) || (m_iHour41 > 24) || (m_iHour42 < 0) || (m_iHour42 > 24) ||   \
		(m_iHour51 < 0) || (m_iHour51 > 24) || (m_iHour52 < 0) || (m_iHour52 > 24) ||	\
		(m_iHour61 < 0) || (m_iHour61 > 24) || (m_iHour62 < 0) || (m_iHour62 > 24) ||	\
		(m_iHour71 < 0) || (m_iHour71 > 24) || (m_iHour72 < 0) || (m_iHour72 > 24) ||	\
		(m_iHour81 < 0) || (m_iHour81 > 24) || (m_iHour82 < 0) || (m_iHour82 > 24) ||	\
		(m_iHour91 < 0) || (m_iHour91 > 24) || (m_iHour92 < 0) || (m_iHour92 > 24) ||	\
		(m_iHour101 < 0) || (m_iHour101 > 24) || (m_iHour102 < 0) || (m_iHour102 > 24))
	{
		g_StringLanType(szLan, "小时范围在0 -- 24之间", "Hour between 0 - 24 ");
		AfxMessageBox(szLan);
		return FALSE;
	}
	if ((m_iMin11 < 0) || (m_iMin11 > 60) || (m_iMin12 < 0) || (m_iMin12 > 60) ||	\
		(m_iMin21 < 0) || (m_iMin21 > 60) || (m_iMin22 < 0) || (m_iMin22 > 60) ||	\
		(m_iMin31 < 0) || (m_iMin31 > 60) || (m_iMin32 < 0) || (m_iMin32 > 60) ||	\
		(m_iMin41 < 0) || (m_iMin41 > 60) || (m_iMin42 < 0) || (m_iMin42 > 60) ||   \
		(m_iMin51 < 0) || (m_iMin51 > 60) || (m_iMin52 < 0) || (m_iMin52 > 60) ||	\
		(m_iMin61 < 0) || (m_iMin61 > 60) || (m_iMin62 < 0) || (m_iMin62 > 60) ||	\
		(m_iMin71 < 0) || (m_iMin71 > 60) || (m_iMin72 < 0) || (m_iMin72 > 60) ||	\
		(m_iMin81 < 0) || (m_iMin81 > 60) || (m_iMin82 < 0) || (m_iMin82 > 60) ||	\
		(m_iMin91 < 0) || (m_iMin91 > 60) || (m_iMin92 < 0) || (m_iMin92 > 60) ||	\
		(m_iMin101 < 0) || (m_iMin101 > 60) || (m_iMin102 < 0) || (m_iMin102 > 60))
	{
		g_StringLanType(szLan, "分钟范围在0 -- 60之间", "Minute between 0 - 60 ");
		AfxMessageBox(szLan);
		return FALSE;
	}
	wStartTime[0] = (WORD)(m_iHour11 * 100 + m_iMin11);
	wStartTime[1] = (WORD)(m_iHour21 * 100 + m_iMin21);
	wStartTime[2] = (WORD)(m_iHour31 * 100 + m_iMin31);
	wStartTime[3] = (WORD)(m_iHour41 * 100 + m_iMin41);
	wStopTime[0] = (WORD)(m_iHour12 * 100 + m_iMin12);
	wStopTime[1] = (WORD)(m_iHour22 * 100 + m_iMin22);
	wStopTime[2] = (WORD)(m_iHour32 * 100 + m_iMin32);
	wStopTime[3] = (WORD)(m_iHour42 * 100 + m_iMin42);
	wStartTime[4] = (WORD)(m_iHour51 * 100 + m_iMin51);
	wStartTime[5] = (WORD)(m_iHour61 * 100 + m_iMin61);
	wStartTime[6] = (WORD)(m_iHour71 * 100 + m_iMin71);
	wStartTime[7] = (WORD)(m_iHour81 * 100 + m_iMin81);
	wStopTime[4] = (WORD)(m_iHour52 * 100 + m_iMin52);
	wStopTime[5] = (WORD)(m_iHour62 * 100 + m_iMin62);
	wStopTime[6] = (WORD)(m_iHour72 * 100 + m_iMin72);
	wStopTime[7] = (WORD)(m_iHour82 * 100 + m_iMin82);

	wStartTime[8] = (WORD)(m_iHour91 * 100 + m_iMin91);
	wStartTime[9] = (WORD)(m_iHour101 * 100 + m_iMin101);
	wStopTime[8] = (WORD)(m_iHour92 * 100 + m_iMin92);
	wStopTime[9] = (WORD)(m_iHour102 * 100 + m_iMin102);

	for (i = 0; i < MAX_SCH_TASKS_NUM; i++)
	{
		if ((wStartTime[i] > 2400) || (wStopTime[i] > 2400))
		{
			g_StringLanType(szLan, "布防时间不能超过24:00", "Fortify time can not be more than 24:00");
			AfxMessageBox(szLan);
			return FALSE;
		}
		if (wStartTime[i] > wStopTime[i])
		{
			g_StringLanType(szLan, "布防起始时间不能大于停止时间", "Fortify start time can not be larger than the record to stop time");
			AfxMessageBox(szLan);
			return FALSE;
		}
		for (j = 0; j < MAX_SCH_TASKS_NUM; j++)
		{
			if (i == j)
			{
				continue;
			}
			if ((wStartTime[i] > wStartTime[j]) && (wStartTime[i] < wStopTime[j]) ||	\
				(wStopTime[i] > wStartTime[j]) && (wStopTime[i] < wStopTime[j]))
			{
				g_StringLanType(szLan, "时间段不能重复", "time can not be repeated");
				AfxMessageBox(szLan);
				return FALSE;
			}
		}
	}
	return TRUE;
}

void CDlgPTZTasks::OnCbnSelchangeComboAlarminWeekday()
{
	UpdateData(TRUE);
	int	i = m_comboWeekday.GetCurSel();	
	m_iHour11 = m_struAlarmTime[i][0].byStartHour;
	m_iMin11 = m_struAlarmTime[i][0].byStartMin;
	m_iHour12 =m_struAlarmTime[i][0].byStopHour;
	m_iMin12 = m_struAlarmTime[i][0].byStopMin;
	m_iHour21 = m_struAlarmTime[i][1].byStartHour;
	m_iMin21 = m_struAlarmTime[i][1].byStartMin;
	m_iHour22 = m_struAlarmTime[i][1].byStopHour;
	m_iMin22 = m_struAlarmTime[i][1].byStopMin;
	m_iHour31 = m_struAlarmTime[i][2].byStartHour;
	m_iMin31 = m_struAlarmTime[i][2].byStartMin;
	m_iHour32 = m_struAlarmTime[i][2].byStopHour;
	m_iMin32 = m_struAlarmTime[i][2].byStopMin;
	m_iHour41 = m_struAlarmTime[i][3].byStartHour;
	m_iMin41 = m_struAlarmTime[i][3].byStartMin;
	m_iHour42 = m_struAlarmTime[i][3].byStopHour;
	m_iMin42 = m_struAlarmTime[i][3].byStopMin;
	m_iHour51 = m_struAlarmTime[i][4].byStartHour;
	m_iMin51 = m_struAlarmTime[i][4].byStartMin;
	m_iHour52 = m_struAlarmTime[i][4].byStopHour;
	m_iMin52 = m_struAlarmTime[i][4].byStopMin;
	m_iHour61 = m_struAlarmTime[i][5].byStartHour;
	m_iMin61 = m_struAlarmTime[i][5].byStartMin;
	m_iHour62 = m_struAlarmTime[i][5].byStopHour;
	m_iMin62 = m_struAlarmTime[i][5].byStopMin;
	m_iHour71 = m_struAlarmTime[i][6].byStartHour;
	m_iMin71 = m_struAlarmTime[i][6].byStartMin;
	m_iHour72 = m_struAlarmTime[i][6].byStopHour;
	m_iMin72 = m_struAlarmTime[i][6].byStopMin;
	m_iHour81 = m_struAlarmTime[i][7].byStartHour;
	m_iMin81 = m_struAlarmTime[i][7].byStartMin;
	m_iHour82 = m_struAlarmTime[i][7].byStopHour;
	m_iMin82 = m_struAlarmTime[i][8].byStopMin;
	m_iHour91 = m_struAlarmTime[i][8].byStartHour;
	m_iMin91 = m_struAlarmTime[i][8].byStartMin;
	m_iHour92 = m_struAlarmTime[i][8].byStopHour;
	m_iMin92 = m_struAlarmTime[i][8].byStopMin;
	m_iHour101 = m_struAlarmTime[i][9].byStartHour;
	m_iMin101 = m_struAlarmTime[i][9].byStartMin;
	m_iHour102 = m_struAlarmTime[i][9].byStopHour;
	m_iMin102 = m_struAlarmTime[i][9].byStopMin;
	m_comboAction1.SetCurSel(m_struTimeTask.struTask[i][0].wAction);
	m_comboAction2.SetCurSel(m_struTimeTask.struTask[i][1].wAction);
	m_comboAction3.SetCurSel(m_struTimeTask.struTask[i][2].wAction);
	m_comboAction4.SetCurSel(m_struTimeTask.struTask[i][3].wAction);
	m_comboAction5.SetCurSel(m_struTimeTask.struTask[i][4].wAction);
	m_comboAction6.SetCurSel(m_struTimeTask.struTask[i][5].wAction);
	m_comboAction7.SetCurSel(m_struTimeTask.struTask[i][6].wAction);
	m_comboAction8.SetCurSel(m_struTimeTask.struTask[i][7].wAction);
	m_comboAction9.SetCurSel(m_struTimeTask.struTask[i][8].wAction);
	m_comboAction10.SetCurSel(m_struTimeTask.struTask[i][9].wAction);

	m_iChidAction1 = m_struTimeTask.struTask[i][0].wActionNum;
	m_iChidAction2 = m_struTimeTask.struTask[i][1].wActionNum;
	m_iChidAction3 = m_struTimeTask.struTask[i][2].wActionNum;
	m_iChidAction4 = m_struTimeTask.struTask[i][3].wActionNum;
	m_iChidAction5 = m_struTimeTask.struTask[i][4].wActionNum;
	m_iChidAction6 = m_struTimeTask.struTask[i][5].wActionNum;
	m_iChidAction7 = m_struTimeTask.struTask[i][6].wActionNum;
	m_iChidAction8 = m_struTimeTask.struTask[i][7].wActionNum;
	m_iChidAction9 = m_struTimeTask.struTask[i][8].wActionNum;
	m_iChidAction10 = m_struTimeTask.struTask[i][9].wActionNum;
	UpdateData(FALSE);
}

void CDlgPTZTasks::OnBtnAlarminTimeCopy() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int j,k;
	int i = m_comboWeekday.GetCurSel();
	int m_nCopyTime = m_comboCopyTime.GetCurSel() - 1;
	
	if (m_nCopyTime == -1)
	{
		for (j=0; j<MAX_DAYS; j++)
		{
			if (j == i)
			{
				continue;
			}
			for (k=0; k<MAX_SCH_TASKS_NUM; k++)
			{
				memcpy(&(m_struAlarmTime[j][k]), &(m_struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
			}
			m_struTimeTask.struTask[j][0].wAction = m_comboAction1.GetCurSel();
			m_struTimeTask.struTask[j][1].wAction = m_comboAction2.GetCurSel();
			m_struTimeTask.struTask[j][2].wAction = m_comboAction3.GetCurSel();
			m_struTimeTask.struTask[j][3].wAction = m_comboAction4.GetCurSel();
			m_struTimeTask.struTask[j][4].wAction = m_comboAction5.GetCurSel();
			m_struTimeTask.struTask[j][5].wAction = m_comboAction6.GetCurSel();
			m_struTimeTask.struTask[j][6].wAction = m_comboAction7.GetCurSel();
			m_struTimeTask.struTask[j][7].wAction = m_comboAction8.GetCurSel();
			m_struTimeTask.struTask[j][8].wAction = m_comboAction9.GetCurSel();
			m_struTimeTask.struTask[j][9].wAction = m_comboAction10.GetCurSel();

			m_struTimeTask.struTask[j][0].wActionNum = m_iChidAction1;
			m_struTimeTask.struTask[j][1].wActionNum = m_iChidAction2;
			m_struTimeTask.struTask[j][2].wActionNum = m_iChidAction3;
			m_struTimeTask.struTask[j][3].wActionNum = m_iChidAction4;
			m_struTimeTask.struTask[j][4].wActionNum = m_iChidAction5;
			m_struTimeTask.struTask[j][5].wActionNum = m_iChidAction6;
			m_struTimeTask.struTask[j][6].wActionNum = m_iChidAction7;
			m_struTimeTask.struTask[j][7].wActionNum = m_iChidAction8;
			m_struTimeTask.struTask[j][8].wActionNum = m_iChidAction9;
			m_struTimeTask.struTask[j][9].wActionNum = m_iChidAction10;
		}
	}
	else
	{
		for (k=0; k<MAX_SCH_TASKS_NUM; k++)
		{
			memcpy(&(m_struAlarmTime[m_nCopyTime][k]), &(m_struAlarmTime[m_nCopyTime][k]), sizeof(NET_DVR_SCHEDTIME));
		}
		m_struTimeTask.struTask[m_nCopyTime][0].wAction = m_comboAction1.GetCurSel();
		m_struTimeTask.struTask[m_nCopyTime][1].wAction = m_comboAction2.GetCurSel();
		m_struTimeTask.struTask[m_nCopyTime][2].wAction = m_comboAction3.GetCurSel();
		m_struTimeTask.struTask[m_nCopyTime][3].wAction = m_comboAction4.GetCurSel();
		m_struTimeTask.struTask[m_nCopyTime][4].wAction = m_comboAction5.GetCurSel();
		m_struTimeTask.struTask[m_nCopyTime][5].wAction = m_comboAction6.GetCurSel();
		m_struTimeTask.struTask[m_nCopyTime][6].wAction = m_comboAction7.GetCurSel();
		m_struTimeTask.struTask[m_nCopyTime][7].wAction = m_comboAction8.GetCurSel();
		m_struTimeTask.struTask[m_nCopyTime][8].wAction = m_comboAction9.GetCurSel();
		m_struTimeTask.struTask[m_nCopyTime][9].wAction = m_comboAction10.GetCurSel();

		m_struTimeTask.struTask[m_nCopyTime][0].wActionNum = m_iChidAction1;
		m_struTimeTask.struTask[m_nCopyTime][1].wActionNum = m_iChidAction2;
		m_struTimeTask.struTask[m_nCopyTime][2].wActionNum = m_iChidAction3;
		m_struTimeTask.struTask[m_nCopyTime][3].wActionNum = m_iChidAction4;
		m_struTimeTask.struTask[m_nCopyTime][4].wActionNum = m_iChidAction5;
		m_struTimeTask.struTask[m_nCopyTime][5].wActionNum = m_iChidAction6;
		m_struTimeTask.struTask[m_nCopyTime][6].wActionNum = m_iChidAction7;
		m_struTimeTask.struTask[m_nCopyTime][7].wActionNum = m_iChidAction8;
		m_struTimeTask.struTask[m_nCopyTime][8].wActionNum = m_iChidAction9;
		m_struTimeTask.struTask[m_nCopyTime][9].wActionNum = m_iChidAction10;
	}
}

BOOL CDlgPTZTasks::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_comboWeekday.SetCurSel(0);
	m_comboCopyTime.SetCurSel(0);
	OnBtnGettasks();

	return TRUE; 
}

void CDlgPTZTasks::OnBtnGettasks() 
{
	// TODO: Add your control notification handler code here
	DWORD iRet = 0;
	memset(&m_struTimeTask, 0, sizeof(m_struTimeTask));
	memset(m_struAlarmTime, 0, sizeof(NET_DVR_SCHEDTIME) * MAX_DAYS * MAX_SCH_TASKS_NUM);
	m_struTimeTask.dwSize = sizeof(m_struTimeTask);
	if (NET_DVR_GetDVRConfig(m_lServerID,  NET_DVR_GET_SCH_TASK, m_iChanNo, &m_struTimeTask, sizeof(m_struTimeTask), &iRet))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SCH_TASK");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SCH_TASK");
	}
	for (int i = 0; i < MAX_DAYS; i++)
	{
		for (int j = 0; j < MAX_SCH_TASKS_NUM; j++)
		{
			memcpy(&(m_struAlarmTime[i][j]), &(m_struTimeTask.struTask[i][j].struSchedTime), sizeof(NET_DVR_SCHEDTIME));
		}	
	}
	OnCbnSelchangeComboAlarminWeekday();
	ShowOtherData();
}

void CDlgPTZTasks::ShowOtherData()
{
	UpdateData(TRUE);
	m_bEnable = m_struTimeTask.byTaskEnable;
	m_iParkTime = m_struTimeTask.dwParkTime;
	UpdateData(FALSE);
}

void CDlgPTZTasks::OnBtnSettask() 
{
	// TODO: Add your control notification handler code here
	SaveOtherData();
	for (int i = 0; i < MAX_DAYS; i++)
	{
		for (int j = 0; j < MAX_SCH_TASKS_NUM; j++)
		{
			memcpy(&(m_struTimeTask.struTask[i][j].struSchedTime), &(m_struAlarmTime[i][j]), sizeof(NET_DVR_SCHEDTIME));
		}	
	}
	if (NET_DVR_SetDVRConfig(m_lServerID,  NET_DVR_SET_SCH_TASK, m_iChanNo, &m_struTimeTask, sizeof(m_struTimeTask)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SCH_TASK");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SCH_TASK");
	}
}

void CDlgPTZTasks::SaveOtherData()
{
	UpdateData(TRUE);
	m_struTimeTask.byTaskEnable = m_bEnable;
	m_struTimeTask.dwParkTime = m_iParkTime;
	UpdateData(FALSE);
}
