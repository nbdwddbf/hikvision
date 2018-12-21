/**********************************************************
FileName:    DlgLocalRecordSchedule.cpp
Description: local record schedule      
Date:        2008/05/17
Note: 		 <global>struct, define refer to GeneralDef.h, global variables and functions refer to ClientDemo.cpp   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/



#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgLocalRecordSchedule.h"
#include ".\dlglocalrecordschedule.h"


// CDlgLocalRecordSchedule dialog
/*********************************************************
  Function:	CDlgLocalRecordSchedule
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgLocalRecordSchedule, CDialog)
CDlgLocalRecordSchedule::CDlgLocalRecordSchedule(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLocalRecordSchedule::IDD, pParent)
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
}

/*********************************************************
  Function:	~CDlgLocalRecordSchedule
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgLocalRecordSchedule::~CDlgLocalRecordSchedule()
{
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgLocalRecordSchedule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLocalRecordSchedule)
	DDX_Control(pDX, IDC_COMBO_LOCAL_WEEK_DAY, m_comboScheduleWeekday);
	DDX_Control(pDX, IDC_COMBO_LOCAL_COPY_WEEK_DAY, m_comboCopyWeekday);
	DDX_Text(pDX, IDC_EDIT_LOCAL_HOUR11, m_iHour11);
	DDX_Text(pDX, IDC_EDIT_LOCAL_MINI11, m_iMin11);
	DDX_Text(pDX, IDC_EDIT_LOCAL_HOUR12, m_iHour12);
	DDX_Text(pDX, IDC_EDIT_LOCAL_MINI12, m_iMin12);
	DDX_Text(pDX, IDC_EDIT_LOCAL_HOUR21, m_iHour21);
	DDX_Text(pDX, IDC_EDIT_LOCAL_MINI21, m_iMin21);
	DDX_Text(pDX, IDC_EDIT_LOCAL_HOUR22, m_iHour22);
	DDX_Text(pDX, IDC_EDIT_LOCAL_MINI22, m_iMin22);
	DDX_Text(pDX, IDC_EDIT_LOCAL_HOUR31, m_iHour31);
	DDX_Text(pDX, IDC_EDIT_LOCAL_MINI31, m_iMin31);
	DDX_Text(pDX, IDC_EDIT_LOCAL_HOUR32, m_iHour32);
	DDX_Text(pDX, IDC_EDIT_LOCAL_MINI32, m_iMin32);
	DDX_Text(pDX, IDC_EDIT_LOCAL_HOUR41, m_iHour41);
	DDX_Text(pDX, IDC_EDIT_LOCAL_MINI41, m_iMin41);
	DDX_Text(pDX, IDC_EDIT_LOCAL_HOUR42, m_iHour42);
	DDX_Text(pDX, IDC_EDIT_LOCAL_MINI42, m_iMin42);
    //}}AFX_DATA_MAP
}

/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgLocalRecordSchedule, CDialog)
	//{{AFX_MSG_MAP(CDlgLocalRecordSchedule)	
	ON_BN_CLICKED(ID_LOCAL_REC_OK, OnBnClickedLocalRecOk)
	ON_BN_CLICKED(ID_LOCAL_REC_EXIT, OnBnClickedLocalRecExit)
	ON_BN_CLICKED(IDC_BTN_LOCAL_REC_COPY, OnBnClickedBtnRecCopy)
	ON_CBN_SELCHANGE(IDC_COMBO_LOCAL_WEEK_DAY, OnCbnSelchangeComboWeekday)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CDlgLocalRecordSchedule message handlers
// CSetClientRecordPlan message handlers
/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgLocalRecordSchedule::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	m_comboScheduleWeekday.SetCurSel(0);
	m_comboCopyWeekday.SetCurSel(7);
	m_iHour11 = g_struLocalParam.struLocalRecordTime[0][0].iStartHour;
	m_iMin11 = g_struLocalParam.struLocalRecordTime[0][0].iStartMinute;
	m_iHour12 = g_struLocalParam.struLocalRecordTime[0][0].iStopHour;
	m_iMin12 = g_struLocalParam.struLocalRecordTime[0][0].iStopMinute;

	m_iHour21 = g_struLocalParam.struLocalRecordTime[0][1].iStartHour;
	m_iMin21 = g_struLocalParam.struLocalRecordTime[0][1].iStartMinute;
	m_iHour22 = g_struLocalParam.struLocalRecordTime[0][1].iStopHour;
	m_iMin22 = g_struLocalParam.struLocalRecordTime[0][1].iStopMinute;

	m_iHour31 = g_struLocalParam.struLocalRecordTime[0][2].iStartHour;
	m_iMin31 = g_struLocalParam.struLocalRecordTime[0][2].iStartMinute;
	m_iHour32 = g_struLocalParam.struLocalRecordTime[0][2].iStopHour;
	m_iMin32 = g_struLocalParam.struLocalRecordTime[0][2].iStopMinute;

	m_iHour41 = g_struLocalParam.struLocalRecordTime[0][3].iStartHour;
	m_iMin41 = g_struLocalParam.struLocalRecordTime[0][3].iStartMinute;
	m_iHour42 = g_struLocalParam.struLocalRecordTime[0][3].iStopHour;
	m_iMin42 = g_struLocalParam.struLocalRecordTime[0][3].iStopMinute;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/*********************************************************
  Function:	OnBnClickedLocalRecOk
  Desc:		set the day local record
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgLocalRecordSchedule::OnBnClickedLocalRecOk()
{
	int i, j;
	char szLan[1024] = {0};
	UpdateData(TRUE);	
	i = m_comboScheduleWeekday.GetCurSel();
	if ((i < 0) || (i > 6))
	{
		return;
	}

	if ((m_iHour11 < 0) || (m_iHour12 < 0) || (m_iHour21 < 0) || (m_iHour22 < 0) ||		\
		(m_iHour31 < 0) || (m_iHour32 < 0) || (m_iHour41 < 0) || (m_iHour42 < 0))
	{
		g_StringLanType(szLan, "小时范围在0 -- 24之间", "Hour between 0 - 24 ");
		AfxMessageBox(szLan);
		return;
	}
	if ((m_iMin11 < 0) || (m_iMin11 > 60) || (m_iMin12 < 0) || (m_iMin12 > 60) ||		\
		(m_iMin21 < 0) || (m_iMin21 > 60) || (m_iMin22 < 0) || (m_iMin22 > 60) ||		\
		(m_iMin31 < 0) || (m_iMin31 > 60) || (m_iMin32 < 0) || (m_iMin32 > 60) ||		\
		(m_iMin41 < 0) || (m_iMin41 > 60) || (m_iMin42 < 0) || (m_iMin42 > 60))
	{
		g_StringLanType(szLan, "分钟范围在0 -- 60之间", "Minute between 0 - 60 ");
		AfxMessageBox(szLan);
		return;
	}
	g_struLocalParam.struLocalRecordTime[i][0].iStartHour = (WORD)m_iHour11;
	g_struLocalParam.struLocalRecordTime[i][0].iStartMinute = (WORD)m_iMin11;
	g_struLocalParam.struLocalRecordTime[i][0].iStopHour = (WORD)m_iHour12;
	g_struLocalParam.struLocalRecordTime[i][0].iStopMinute = (WORD)m_iMin12;
	g_struLocalParam.struLocalRecordTime[i][0].iStartTime = (WORD)(m_iHour11 * 100 + m_iMin11);
	g_struLocalParam.struLocalRecordTime[i][0].iStopTime = (WORD)(m_iHour12 * 100 + m_iMin12);

	g_struLocalParam.struLocalRecordTime[i][1].iStartHour = (WORD)m_iHour21;
	g_struLocalParam.struLocalRecordTime[i][1].iStartMinute = (WORD)m_iMin21;
	g_struLocalParam.struLocalRecordTime[i][1].iStopHour = (WORD)m_iHour22;
	g_struLocalParam.struLocalRecordTime[i][1].iStopMinute = (WORD)m_iMin22;
	g_struLocalParam.struLocalRecordTime[i][1].iStartTime = (WORD)(m_iHour21 * 100 + m_iMin21);
	g_struLocalParam.struLocalRecordTime[i][1].iStopTime = (WORD)(m_iHour22 * 100 + m_iMin22);

	g_struLocalParam.struLocalRecordTime[i][2].iStartHour = (WORD)m_iHour31;
	g_struLocalParam.struLocalRecordTime[i][2].iStartMinute = (WORD)m_iMin31;
	g_struLocalParam.struLocalRecordTime[i][2].iStopHour = (WORD)m_iHour32;
	g_struLocalParam.struLocalRecordTime[i][2].iStopMinute = (WORD)m_iMin32;
	g_struLocalParam.struLocalRecordTime[i][2].iStartTime = (WORD)(m_iHour31 * 100 + m_iMin31);
	g_struLocalParam.struLocalRecordTime[i][2].iStopTime = (WORD)(m_iHour32 * 100 + m_iMin32);

	g_struLocalParam.struLocalRecordTime[i][3].iStartHour = (WORD)m_iHour41;
	g_struLocalParam.struLocalRecordTime[i][3].iStartMinute = (WORD)m_iMin41;
	g_struLocalParam.struLocalRecordTime[i][3].iStopHour = (WORD)m_iHour42;
	g_struLocalParam.struLocalRecordTime[i][3].iStopMinute = (WORD)m_iMin42;
	g_struLocalParam.struLocalRecordTime[i][3].iStartTime = (WORD)(m_iHour41 * 100 + m_iMin41);
	g_struLocalParam.struLocalRecordTime[i][3].iStopTime = (WORD)(m_iHour41 * 100 + m_iMin42);
	for (j = 0; j < 4; j++)
	{
		if ((g_struLocalParam.struLocalRecordTime[i][j].iStartTime >= 2400) || (g_struLocalParam.struLocalRecordTime[i][j].iStopTime > 2400))
		{
			g_StringLanType(szLan, "录像时间不能超过24:00", "record time can not be more than 24:00");
			AfxMessageBox(szLan);
			return;
		}
		if (g_struLocalParam.struLocalRecordTime[i][j].iStartTime > g_struLocalParam.struLocalRecordTime[i][j].iStopTime)
		{
			g_StringLanType(szLan, "录像起始时间不能大于录像停止时间", "record start time can not be larger than the record to stop time");
			AfxMessageBox(szLan);
			return;
		}
		for (int k=j+1; k<4; k++)
		{
			if (	((g_struLocalParam.struLocalRecordTime[i][j].iStartTime > g_struLocalParam.struLocalRecordTime[i][k].iStartTime) &&
				(g_struLocalParam.struLocalRecordTime[i][j].iStartTime < g_struLocalParam.struLocalRecordTime[i][k].iStopTime))
				||	((g_struLocalParam.struLocalRecordTime[i][j].iStopTime > g_struLocalParam.struLocalRecordTime[i][k].iStartTime) &&
				(g_struLocalParam.struLocalRecordTime[i][j].iStopTime < g_struLocalParam.struLocalRecordTime[i][k].iStopTime))	)
			{
				g_StringLanType(szLan, "录像时间不能重复", "time can not be repeated");
				AfxMessageBox(szLan);
				return;
			}
		}

	}
	//m_bChanged = TRUE;
	GetDlgItem(IDC_BTN_LOCAL_REC_COPY)->EnableWindow(TRUE);	
}

/*********************************************************
  Function:	OnBnClickedLocalRecExit
  Desc:		exit record schedule configuration
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgLocalRecordSchedule::OnBnClickedLocalRecExit()
{
	CDialog::OnCancel();
}

/*********************************************************
  Function:	OnBnClickedBtnRecCopy
  Desc:		copy this day record schedule to corresponding date
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgLocalRecordSchedule::OnBnClickedBtnRecCopy()
{
	int iCurDate, iCopyDate, i, j;

	UpdateData(TRUE);
	iCurDate = m_comboScheduleWeekday.GetCurSel();
	iCopyDate = m_comboCopyWeekday.GetCurSel();

	if ((iCurDate < 0) || (iCopyDate >= m_comboCopyWeekday.GetCount()))
	{
		return;
	}
	if (iCopyDate == iCurDate)
	{
		return;
	}
	if (iCopyDate == 7)
	{
		for (i = 0; i < 7; i++)
		{
			if (i == iCurDate)
			{
				continue;
			}
			for (j = 0; j < 4; j++)
			{
				g_struLocalParam.struLocalRecordTime[i][j].iStartHour = g_struLocalParam.struLocalRecordTime[iCurDate][j].iStartHour;
				g_struLocalParam.struLocalRecordTime[i][j].iStartMinute = g_struLocalParam.struLocalRecordTime[iCurDate][j].iStartMinute;
				g_struLocalParam.struLocalRecordTime[i][j].iStartTime = g_struLocalParam.struLocalRecordTime[iCurDate][j].iStartTime;
				g_struLocalParam.struLocalRecordTime[i][j].iStopHour = g_struLocalParam.struLocalRecordTime[iCurDate][j].iStopHour;
				g_struLocalParam.struLocalRecordTime[i][j].iStopMinute = g_struLocalParam.struLocalRecordTime[iCurDate][j].iStopMinute;
				g_struLocalParam.struLocalRecordTime[i][j].iStopTime = g_struLocalParam.struLocalRecordTime[iCurDate][j].iStopTime;
			}
		}
	}
	else
	{
		for (j = 0; j < 4; j++)
		{
			g_struLocalParam.struLocalRecordTime[iCopyDate][j].iStartHour = g_struLocalParam.struLocalRecordTime[iCurDate][j].iStartHour;
			g_struLocalParam.struLocalRecordTime[iCopyDate][j].iStartMinute = g_struLocalParam.struLocalRecordTime[iCurDate][j].iStartMinute;
			g_struLocalParam.struLocalRecordTime[iCopyDate][j].iStartTime = g_struLocalParam.struLocalRecordTime[iCurDate][j].iStartTime;
			g_struLocalParam.struLocalRecordTime[iCopyDate][j].iStopHour = g_struLocalParam.struLocalRecordTime[iCurDate][j].iStopHour;
			g_struLocalParam.struLocalRecordTime[iCopyDate][j].iStopMinute = g_struLocalParam.struLocalRecordTime[iCurDate][j].iStopMinute;
			g_struLocalParam.struLocalRecordTime[iCopyDate][j].iStopTime = g_struLocalParam.struLocalRecordTime[iCurDate][j].iStopTime;
		}
	}
}

/*********************************************************
  Function:	OnCbnSelchangeComboWeekday
  Desc:		select corresponding date that need to configure
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgLocalRecordSchedule::OnCbnSelchangeComboWeekday()
{
	int i;

	i = m_comboScheduleWeekday.GetCurSel();
	if ((i < 0) || (i >= m_comboScheduleWeekday.GetCount()))
	{
		return;
	}
	m_iHour11 = g_struLocalParam.struLocalRecordTime[i][0].iStartHour;
	m_iMin11 = g_struLocalParam.struLocalRecordTime[i][0].iStartMinute;
	m_iHour12 = g_struLocalParam.struLocalRecordTime[i][0].iStopHour;
	m_iMin12 = g_struLocalParam.struLocalRecordTime[i][0].iStopMinute;

	m_iHour21 = g_struLocalParam.struLocalRecordTime[i][1].iStartHour;
	m_iMin21 = g_struLocalParam.struLocalRecordTime[i][1].iStartMinute;
	m_iHour22 = g_struLocalParam.struLocalRecordTime[i][1].iStopHour;
	m_iMin22 = g_struLocalParam.struLocalRecordTime[i][1].iStopMinute;

	m_iHour31 = g_struLocalParam.struLocalRecordTime[i][2].iStartHour;
	m_iMin31 = g_struLocalParam.struLocalRecordTime[i][2].iStartMinute;
	m_iHour32 = g_struLocalParam.struLocalRecordTime[i][2].iStopHour;
	m_iMin32 = g_struLocalParam.struLocalRecordTime[i][2].iStopMinute;

	m_iHour41 = g_struLocalParam.struLocalRecordTime[i][3].iStartHour;
	m_iMin41 = g_struLocalParam.struLocalRecordTime[i][3].iStartMinute;
	m_iHour42 = g_struLocalParam.struLocalRecordTime[i][3].iStopHour;
	m_iMin42 = g_struLocalParam.struLocalRecordTime[i][3].iStopMinute;
	UpdateData(FALSE);
}
