// DlgVcaAlarmTimeCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaAlarmTimeCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaAlarmTimeCfg dialog


CDlgVcaAlarmTimeCfg::CDlgVcaAlarmTimeCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaAlarmTimeCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaAlarmTimeCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(m_ArryTimeSegBeginHour,0,sizeof(m_ArryTimeSegBeginHour));
	memset(m_ArryTimeSegBeginMin, 0,sizeof(m_ArryTimeSegBeginMin));
	memset(m_ArryTimeSegEndHour,  0,sizeof(m_ArryTimeSegEndHour));
	memset(m_ArryTimeSegEndMin,   0,sizeof(m_ArryTimeSegEndMin));
	memset(&m_strArryAlatmTime,   0,sizeof(m_strArryAlatmTime));
	m_nPreSelDayIndex = 0;
}


void CDlgVcaAlarmTimeCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaAlarmTimeCfg)
	DDX_Control(pDX, IDC_COMBO_COPYWEEK, m_comboCopyWeek);
	DDX_Control(pDX, IDC_COMBO_WEEK, m_comboWeek);

	DDX_Text(pDX,IDC_EDIT_SEG1_BEGIN_HOUR,m_ArryTimeSegBeginHour[0]);
	DDX_Text(pDX,IDC_EDIT_SEG2_BEGIN_HOUR,m_ArryTimeSegBeginHour[1]);
	DDX_Text(pDX,IDC_EDIT_SEG3_BEGIN_HOUR,m_ArryTimeSegBeginHour[2]);
	DDX_Text(pDX,IDC_EDIT_SEG4_BEGIN_HOUR,m_ArryTimeSegBeginHour[3]);
	DDX_Text(pDX,IDC_EDIT_SEG5_BEGIN_HOUR,m_ArryTimeSegBeginHour[4]);
	DDX_Text(pDX,IDC_EDIT_SEG6_BEGIN_HOUR,m_ArryTimeSegBeginHour[5]);
	DDX_Text(pDX,IDC_EDIT_SEG7_BEGIN_HOUR,m_ArryTimeSegBeginHour[6]);
	DDX_Text(pDX,IDC_EDIT_SEG8_BEGIN_HOUR,m_ArryTimeSegBeginHour[7]);

    DDX_Text(pDX,IDC_EDIT_SEG1_BEGIN_MIN,m_ArryTimeSegBeginMin[0]);
	DDX_Text(pDX,IDC_EDIT_SEG2_BEGIN_MIN,m_ArryTimeSegBeginMin[1]);
	DDX_Text(pDX,IDC_EDIT_SEG3_BEGIN_MIN,m_ArryTimeSegBeginMin[2]);
	DDX_Text(pDX,IDC_EDIT_SEG4_BEGIN_MIN,m_ArryTimeSegBeginMin[3]);
	DDX_Text(pDX,IDC_EDIT_SEG5_BEGIN_MIN,m_ArryTimeSegBeginMin[4]);
	DDX_Text(pDX,IDC_EDIT_SEG6_BEGIN_MIN,m_ArryTimeSegBeginMin[5]);
	DDX_Text(pDX,IDC_EDIT_SEG7_BEGIN_MIN,m_ArryTimeSegBeginMin[6]);
	DDX_Text(pDX,IDC_EDIT_SEG8_BEGIN_MIN,m_ArryTimeSegBeginMin[7]);

	DDX_Text(pDX,IDC_EDIT_SEG1_END_HOUR,m_ArryTimeSegEndHour[0]);
	DDX_Text(pDX,IDC_EDIT_SEG2_END_HOUR,m_ArryTimeSegEndHour[1]);
	DDX_Text(pDX,IDC_EDIT_SEG3_END_HOUR,m_ArryTimeSegEndHour[2]);
	DDX_Text(pDX,IDC_EDIT_SEG4_END_HOUR,m_ArryTimeSegEndHour[3]);
	DDX_Text(pDX,IDC_EDIT_SEG5_END_HOUR,m_ArryTimeSegEndHour[4]);
	DDX_Text(pDX,IDC_EDIT_SEG6_END_HOUR,m_ArryTimeSegEndHour[5]);
	DDX_Text(pDX,IDC_EDIT_SEG7_END_HOUR,m_ArryTimeSegEndHour[6]);
	DDX_Text(pDX,IDC_EDIT_SEG8_END_HOUR,m_ArryTimeSegEndHour[7]);

	DDX_Text(pDX,IDC_EDIT_SEG1_END_MIN,m_ArryTimeSegEndMin[0]);
	DDX_Text(pDX,IDC_EDIT_SEG2_END_MIN,m_ArryTimeSegEndMin[1]);
	DDX_Text(pDX,IDC_EDIT_SEG3_END_MIN,m_ArryTimeSegEndMin[2]);
	DDX_Text(pDX,IDC_EDIT_SEG4_END_MIN,m_ArryTimeSegEndMin[3]);
	DDX_Text(pDX,IDC_EDIT_SEG5_END_MIN,m_ArryTimeSegEndMin[4]);
	DDX_Text(pDX,IDC_EDIT_SEG6_END_MIN,m_ArryTimeSegEndMin[5]);
	DDX_Text(pDX,IDC_EDIT_SEG7_END_MIN,m_ArryTimeSegEndMin[6]);
	DDX_Text(pDX,IDC_EDIT_SEG8_END_MIN,m_ArryTimeSegEndMin[7]);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaAlarmTimeCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaAlarmTimeCfg)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_CBN_SELCHANGE(IDC_COMBO_WEEK, OnSelchangeComboWeek)
	ON_BN_CLICKED(IDC_BTN_COPY, OnBtnCopy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaAlarmTimeCfg message handlers

BOOL CDlgVcaAlarmTimeCfg::OnInitDialog()
{   
	CDialog::OnInitDialog();
	InitCtrlState();
	LoadDayAlarmTime(m_nPreSelDayIndex);
	return TRUE;
}

void CDlgVcaAlarmTimeCfg::OnBtnSave() 
{   
	SaveDayAlarmTime(m_nPreSelDayIndex);

	if (!ValidateData())
	{
		return;
	}
	OnOK();
}

void CDlgVcaAlarmTimeCfg::OnSelchangeComboWeek() 
{   
	int nCurSelDay = m_comboWeek.GetCurSel();
	if (nCurSelDay != CB_ERR)
	{   
		SaveDayAlarmTime(m_nPreSelDayIndex);
		LoadDayAlarmTime(nCurSelDay);
		m_nPreSelDayIndex = nCurSelDay;
	}
}

void CDlgVcaAlarmTimeCfg::OnBtnCopy() 
{   
	int nCurSelDay     = m_comboWeek.GetCurSel();
	int nCurSelCopyDay = m_comboCopyWeek.GetCurSel();
	
	if (nCurSelDay == CB_ERR || nCurSelCopyDay == CB_ERR)
	{
		return;
	}

	SaveDayAlarmTime(nCurSelDay);

	if (!ValidateOneDayAlarmTime(nCurSelDay))
	{
		return;
	}

	if (nCurSelCopyDay == m_comboCopyWeek.GetCount() - 1)
	{
		for (int i = 0; i < MAX_DAYS; i++)
		{
			for (int j = 0; j < MAX_TIMESEGMENT_V30; j++)
			{
				m_strArryAlatmTime[i][j] = m_strArryAlatmTime[nCurSelDay][j];
			}
		}
	}
	else
	{
		for (int i = 0; i < MAX_TIMESEGMENT_V30; i++)
		{
			m_strArryAlatmTime[nCurSelCopyDay][i] = m_strArryAlatmTime[nCurSelDay][i];
		}
	}

	char szWeekDay[50] = {0};
	g_StringLanType(szWeekDay,"复制成功","Copy successfully");
	AfxMessageBox(szWeekDay);
}


void CDlgVcaAlarmTimeCfg::InitCtrlState()
{   
	char szWeekDay[50] = {0};
	g_StringLanType(szWeekDay,"星期一","Monday");
	m_comboWeek.InsertString(0,szWeekDay);
    m_comboCopyWeek.InsertString(0,szWeekDay);

	g_StringLanType(szWeekDay,"星期二","Tuesday");
	m_comboWeek.InsertString(1,szWeekDay);
	m_comboCopyWeek.InsertString(1,szWeekDay);

	g_StringLanType(szWeekDay,"星期三","Wednesday");
	m_comboWeek.InsertString(2,szWeekDay);
	m_comboCopyWeek.InsertString(2,szWeekDay);

	g_StringLanType(szWeekDay,"星期四","Thursday");
	m_comboWeek.InsertString(3,szWeekDay);
	m_comboCopyWeek.InsertString(3,szWeekDay);

	g_StringLanType(szWeekDay,"星期五","Friday");
	m_comboWeek.InsertString(4,szWeekDay);
	m_comboCopyWeek.InsertString(4,szWeekDay);

	g_StringLanType(szWeekDay,"星期六","Saturday");
	m_comboWeek.InsertString(5,szWeekDay);
	m_comboCopyWeek.InsertString(5,szWeekDay);

	g_StringLanType(szWeekDay,"星期日","Sunday");
	m_comboWeek.InsertString(6,szWeekDay);
	m_comboCopyWeek.InsertString(6,szWeekDay);

	g_StringLanType(szWeekDay,"整个星期","Whole week");
	m_comboCopyWeek.InsertString(7,szWeekDay);
    
	m_comboWeek.SetCurSel(0);
	m_comboCopyWeek.SetCurSel(0);
}


void CDlgVcaAlarmTimeCfg::LoadDayAlarmTime(int nDayIndex)
{  
	for (int i = 0; i < MAX_TIMESEGMENT_V30; i++)
	{
		m_ArryTimeSegBeginHour[i]  =  m_strArryAlatmTime[nDayIndex][i].byStartHour;
		m_ArryTimeSegBeginMin[i]   =  m_strArryAlatmTime[nDayIndex][i].byStartMin;
		m_ArryTimeSegEndHour[i]    =  m_strArryAlatmTime[nDayIndex][i].byStopHour;
		m_ArryTimeSegEndMin[i]     =  m_strArryAlatmTime[nDayIndex][i].byStopMin;
	}
	UpdateData(FALSE);
}

void CDlgVcaAlarmTimeCfg::SaveDayAlarmTime(int nDayIndex)
{
	UpdateData(TRUE);
	
	for (int i = 0; i < MAX_TIMESEGMENT_V30; i++)
	{
		m_strArryAlatmTime[nDayIndex][i].byStartHour = m_ArryTimeSegBeginHour[i];
		m_strArryAlatmTime[nDayIndex][i].byStartMin  = m_ArryTimeSegBeginMin[i];
		m_strArryAlatmTime[nDayIndex][i].byStopHour  = m_ArryTimeSegEndHour[i];
		m_strArryAlatmTime[nDayIndex][i].byStopMin   = m_ArryTimeSegEndMin[i];
	}
}

void CDlgVcaAlarmTimeCfg::InitAlarmTimeCfg(NET_DVR_SCHEDTIME strArryAlarmTime[MAX_DAYS][MAX_TIMESEGMENT_V30])
{
	for (int i = 0; i < MAX_DAYS; i++)
	{
		for (int j = 0; j < MAX_TIMESEGMENT_V30; j++)
		{
			m_strArryAlatmTime[i][j]  = strArryAlarmTime[i][j];
		}
	}
}

void CDlgVcaAlarmTimeCfg::GetAlarmTimeCfg(NET_DVR_SCHEDTIME struArryAlarmTime[MAX_DAYS][MAX_TIMESEGMENT_V30])
{
	for (int i = 0; i < MAX_DAYS; i++)
	{
		for (int j = 0; j < MAX_TIMESEGMENT_V30; j++)
		{
			struArryAlarmTime[i][j] = m_strArryAlatmTime[i][j];
		}
	}
}

BOOL CDlgVcaAlarmTimeCfg::ValidateData()
{
	for (int i = 0; i < MAX_DAYS; i++)
	{
		if (!ValidateOneDayAlarmTime(i))
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CDlgVcaAlarmTimeCfg::ValidateOneDayAlarmTime(int nDayIndex)
{   
	char     szErrInfo[64]     = "\0";
	char     szTimeSegment[16] = "\0";
	CString  szDayOfWeek       = "";
	BOOL     bValid            = TRUE;
	m_comboWeek.GetLBText(nDayIndex,szDayOfWeek);

    for (int i = 0; i < MAX_TIMESEGMENT_V30; i++)
	{   
	    
        if (bValid)
		{
			if ((m_strArryAlatmTime[nDayIndex][i].byStartHour < 0    || m_strArryAlatmTime[nDayIndex][i].byStartHour > 24)  ||
				(m_strArryAlatmTime[nDayIndex][i].byStartMin < 0     || m_strArryAlatmTime[nDayIndex][i].byStartMin  >= 60) ||
				(m_strArryAlatmTime[nDayIndex][i].byStartHour == 24  && m_strArryAlatmTime[nDayIndex][i].byStartMin  != 0))
			{       
				bValid = FALSE;
				g_StringLanType(szErrInfo,"开始时间不合理","begin time is not correct");
			}
		}
		
		if (bValid)
		{
			if ((m_strArryAlatmTime[nDayIndex][i].byStopHour < 0    || m_strArryAlatmTime[nDayIndex][i].byStopHour > 24)  ||
				(m_strArryAlatmTime[nDayIndex][i].byStopMin < 0     || m_strArryAlatmTime[nDayIndex][i].byStopMin  >= 60) ||
				(m_strArryAlatmTime[nDayIndex][i].byStopHour == 24  && m_strArryAlatmTime[nDayIndex][i].byStopMin  != 0))
			{       
				bValid = FALSE;
				g_StringLanType(szErrInfo,"结束时间不合理","end time is not correct");
			}
		}

		if (bValid)
		{
			int nStartMinOffset = m_strArryAlatmTime[nDayIndex][i].byStartHour * 60 + m_strArryAlatmTime[nDayIndex][i].byStartMin;
			int nStopMinOffset  = m_strArryAlatmTime[nDayIndex][i].byStopHour  * 60 + m_strArryAlatmTime[nDayIndex][i].byStopMin;
			
			if (nStartMinOffset > nStopMinOffset)
			{   
				bValid = FALSE;
				g_StringLanType(szErrInfo,"开始时间不能大于结束时间","begin time must less than end time");
			}
		}
        
		if (!bValid)
		{   
			g_StringLanType(szTimeSegment,"时间段","time segment");

			CString strErr = "";
			strErr.Format(_T("%s: %s[%d] %s"),szDayOfWeek,szTimeSegment,i + 1,szErrInfo);
			AfxMessageBox(strErr);
			break;
		}
	}
	return bValid;
}
