/**********************************************************
FileName:    DlgRemoteHideAlarm.cpp
Description: 远程遮挡告警处理      
Date:        
Note: 		
Modification History:      
<version> <time>         <desc>
    
***********************************************************/


#include "stdafx.h"
#include "DlgRemoteHideAlarm.h"
#include "config.h"


// CDlgRemoteHideAlarm dialog
extern LPNET_DVR_HIDEALARM_V30 g_lpHideAlarm;//告警遮挡区域
RECT g_rectHideAlarmShow;
RECT g_rectHideAlarmSetArea;

/*********************************************************
  Function:	HideAlarmGetCallBack
  Desc:		
  Input:	
  Output:	
  Return:	
**********************************************************/
void CALLBACK HideAlarmGetCallBack(LONG nPort,HDC hDc,DWORD nUser)
{
	CRect rect;
	int i = 0,j = 0;
	CPoint point;
	rect.left = g_rectHideAlarmSetArea.left;
	rect.top = g_rectHideAlarmSetArea.top;
	rect.right = g_rectHideAlarmSetArea.right;
	rect.bottom = g_rectHideAlarmSetArea.bottom;
	::DrawEdge(hDc,&rect,BDR_SUNKENOUTER,BF_RECT);
	SetBkMode(hDc,TRANSPARENT);
}

void CALLBACK HideAlarmSetCallBack(LONG nPort,HDC hDc,DWORD nUser)
{
	::DrawEdge(hDc,&g_rectHideAlarmShow,BDR_SUNKENOUTER,BF_RECT);
	SetBkMode(hDc,TRANSPARENT);
}
/*********************************************************
  Function:	CDlgRemoteHideAlarm
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgRemoteHideAlarm, CDialog)
CDlgRemoteHideAlarm::CDlgRemoteHideAlarm(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteHideAlarm::IDD, pParent)
	, m_bChkMonitorAlarm(FALSE)
	, m_bChkAudioAlarm(FALSE)
	, m_bChkReportCenter(FALSE)
	, m_bChkInvokeAlarmOut(FALSE)
	, m_bChkInvokeJpegCapture(FALSE)
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
	, m_bChkHideAlarmShow(FALSE)
	, m_bChkHideAlarmSet(FALSE)
	, m_iChanShowNum(0)
	, m_lLoginID(-1)
	, m_bDrawdetect(FALSE)
	, m_lPlayHandle(NULL)
	, m_dwAlarmOutNum(0)
	, m_dwDevIndex(0)
{
}

/*********************************************************
  Function:	~CDlgRemoteHideAlarm
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgRemoteHideAlarm::~CDlgRemoteHideAlarm()
{
}
/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteHideAlarm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteHideAlarm)
	DDX_Control(pDX, IDC_TREE_ALARM_OUT, m_treeAlarmOut);
	DDX_Control(pDX, IDC_COMBO_HIDE_ALARM_SENSITIVE, m_comboHideAlarmSensitive);
	DDX_Control(pDX, IDC_PIC_HIDE_ALARM, m_picHideAlarm);
	DDX_Check(pDX, IDC_CHK_HA_MONITOR_ALARM, m_bChkMonitorAlarm);
	DDX_Check(pDX, IDC_CHK_HA_AUDIO_ALARM, m_bChkAudioAlarm);
	DDX_Check(pDX, IDC_CHK_HA_REPORT_CENTER, m_bChkReportCenter);
	DDX_Check(pDX, IDC_CHK_HA_INVOKE_ALARM_OUT, m_bChkInvokeAlarmOut);
	DDX_Check(pDX, IDC_CHK_INVOKE_JPEG_CAPTURE, m_bChkInvokeJpegCapture);
	DDX_Control(pDX, IDC_COMBO_HA_WEEKDAY, m_comboWeekday);
	DDX_Control(pDX, IDC_COMBO_HIDE_ALARM_DAY_COPY, m_comboDayCopy);
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
	DDX_Check(pDX, IDC_CHK_HIDE_ALARM_SHOW, m_bChkHideAlarmShow);
	DDX_Check(pDX, IDC_CHK_HIDE_ALARM_SET, m_bChkHideAlarmSet);
	//}}AFX_DATA_MAP

}


/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgRemoteHideAlarm, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteHideAlarm)	
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BTN_HIDE_ALARM_DAY_OK, OnBnClickedBtnHaDayOk)
	ON_BN_CLICKED(IDC_CHK_HIDE_ALARM_SHOW, OnBnClickedChkHideAlarmShow)
	ON_BN_CLICKED(IDC_CHK_HIDE_ALARM_SET, OnBnClickedChkHideAlarmSet)
	ON_BN_CLICKED(ID_BTN_HIDE_ALARM_OK, OnBnClickedBtnHideAlarmOk)
	ON_BN_CLICKED(ID_BTN_HIDE_ALARM_EXIT, OnBnClickedBtnHideAlarmExit)
	ON_BN_CLICKED(IDC_CHK_HA_INVOKE_ALARM_OUT, OnBnClickedChkHaInvokeAlarmOut)
	ON_BN_CLICKED(IDC_BTN_HA_DAY_COPY, OnBnClickedBtnHaDayCopy)
	ON_CBN_SELCHANGE(IDC_COMBO_HA_WEEKDAY, OnCbnSelchangeComboHaWeekday)
	ON_NOTIFY(NM_CLICK, IDC_TREE_ALARM_OUT, OnClickTreeAlarmOut)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CDlgRemoteHideAlarm message handlers
/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgRemoteHideAlarm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_picHideAlarm.MoveWindow(DETECT_AREA_LEFT,DETECT_AREA_TOP, 352, 288);

	g_rectHideAlarmSetArea.left = g_lpHideAlarm->wHideAlarmAreaTopLeftX/2;
	g_rectHideAlarmSetArea.top = g_lpHideAlarm->wHideAlarmAreaTopLeftY/2;
	g_rectHideAlarmSetArea.bottom = (g_lpHideAlarm->wHideAlarmAreaTopLeftY + g_lpHideAlarm->wHideAlarmAreaHeight)/2;
	g_rectHideAlarmSetArea.right = (g_lpHideAlarm->wHideAlarmAreaTopLeftX + g_lpHideAlarm->wHideAlarmAreaWidth)/2;

	NET_DVR_CLIENTINFO struPlayInfo;
	struPlayInfo.hPlayWnd = m_picHideAlarm.GetSafeHwnd();
	struPlayInfo.lChannel = m_iChanShowNum;
	struPlayInfo.lLinkMode = 0;
	struPlayInfo.sMultiCastIP = "";	 

	m_lPlayHandle = NET_DVR_RealPlay(m_lLoginID, &struPlayInfo);	
	if (m_lPlayHandle == -1)
	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "网络连接失败", "Network connection failure");
		AfxMessageBox(szLan);
	}	
	m_bDrawdetect = FALSE;
	m_bChkMonitorAlarm = g_lpHideAlarm->strHideAlarmHandleType.dwHandleType &0x01;
	m_bChkAudioAlarm = (g_lpHideAlarm->strHideAlarmHandleType.dwHandleType>>1)&0x01;
	m_bChkReportCenter = (g_lpHideAlarm->strHideAlarmHandleType.dwHandleType>>2)&0x01;
	m_bChkInvokeAlarmOut = (g_lpHideAlarm->strHideAlarmHandleType.dwHandleType>>3)&0x01;
	m_bChkInvokeJpegCapture = (g_lpHideAlarm->strHideAlarmHandleType.dwHandleType>>4)&0x01;
	int i=0;
	for (i=0; i<MAX_ALARMOUT_V30; i++)
	{
		m_bAlarmOut[i] = g_lpHideAlarm->strHideAlarmHandleType.byRelAlarmOut[i];
	}
	m_treeAlarmOut.EnableWindow(m_bChkInvokeAlarmOut);

	m_comboWeekday.SetCurSel(0);
	m_comboDayCopy.SetCurSel(0);
	m_iHour11 = g_lpHideAlarm->struAlarmTime[0][0].byStartHour;
	m_iMin11 = g_lpHideAlarm->struAlarmTime[0][0].byStartMin;
	m_iHour12 = g_lpHideAlarm->struAlarmTime[0][0].byStopHour;
	m_iMin12 = g_lpHideAlarm->struAlarmTime[0][0].byStopMin;
	m_iHour21 = g_lpHideAlarm->struAlarmTime[0][1].byStartHour;
	m_iMin21 = g_lpHideAlarm->struAlarmTime[0][1].byStartMin;
	m_iHour22 = g_lpHideAlarm->struAlarmTime[0][1].byStopHour;
	m_iMin22 = g_lpHideAlarm->struAlarmTime[0][1].byStopMin;
	m_iHour31 = g_lpHideAlarm->struAlarmTime[0][2].byStartHour;
	m_iMin31 = g_lpHideAlarm->struAlarmTime[0][2].byStartMin;
	m_iHour32 = g_lpHideAlarm->struAlarmTime[0][2].byStopHour;
	m_iMin32 = g_lpHideAlarm->struAlarmTime[0][2].byStopMin;
	m_iHour41 = g_lpHideAlarm->struAlarmTime[0][3].byStartHour;
	m_iMin41 = g_lpHideAlarm->struAlarmTime[0][3].byStartMin;
	m_iHour42 = g_lpHideAlarm->struAlarmTime[0][3].byStopHour;
	m_iMin42 = g_lpHideAlarm->struAlarmTime[0][3].byStopMin;
	m_iHour51 = g_lpHideAlarm->struAlarmTime[0][4].byStartHour;
	m_iMin51 = g_lpHideAlarm->struAlarmTime[0][4].byStartMin;
	m_iHour52 = g_lpHideAlarm->struAlarmTime[0][4].byStopHour;
	m_iMin52 = g_lpHideAlarm->struAlarmTime[0][4].byStopMin;
	m_iHour61 = g_lpHideAlarm->struAlarmTime[0][5].byStartHour;
	m_iMin61 = g_lpHideAlarm->struAlarmTime[0][5].byStartMin;
	m_iHour62 = g_lpHideAlarm->struAlarmTime[0][5].byStopHour;
	m_iMin62 = g_lpHideAlarm->struAlarmTime[0][5].byStopMin;
	m_iHour71 = g_lpHideAlarm->struAlarmTime[0][6].byStartHour;
	m_iMin71 = g_lpHideAlarm->struAlarmTime[0][6].byStartMin;
	m_iHour72 = g_lpHideAlarm->struAlarmTime[0][6].byStopHour;
	m_iMin72 = g_lpHideAlarm->struAlarmTime[0][6].byStopMin;
	m_iHour81 = g_lpHideAlarm->struAlarmTime[0][7].byStartHour;
	m_iMin81 = g_lpHideAlarm->struAlarmTime[0][7].byStartMin;
	m_iHour82 = g_lpHideAlarm->struAlarmTime[0][7].byStopHour;
	m_iMin82 = g_lpHideAlarm->struAlarmTime[0][7].byStopMin;
	GetDlgItem(IDC_CHK_HIDE_ALARM_SHOW)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHK_HIDE_ALARM_SET)->EnableWindow(TRUE);
	if (g_lpHideAlarm->dwEnableHideAlarm > 0)
	{
		m_comboHideAlarmSensitive.SetCurSel(g_lpHideAlarm->dwEnableHideAlarm -1);
	}
	else
	{
		m_comboHideAlarmSensitive.SetCurSel(0);
	}
	UpdateData(FALSE);
	return TRUE; 
}

/*********************************************************
Function:	TimeTest
Desc:		校验时间正确性
Input:	
Output:	
Return:		TRUE,正确的时间表;FALSE,错误的时间表;
**********************************************************/
BOOL CDlgRemoteHideAlarm::TimeTest()
{
	int i = 0;
	int j = 0;
	WORD wStartTime[MAX_TIMESEGMENT_V30], wStopTime[MAX_TIMESEGMENT_V30];
	char szLan[128] = {0};
	UpdateData(TRUE);
	if ((m_iHour11 < 0) || (m_iHour11 > 24) || (m_iHour12 < 0) || (m_iHour12 > 24) ||	\
		(m_iHour21 < 0) || (m_iHour21 > 24) || (m_iHour22 < 0) || (m_iHour22 > 24) ||	\
		(m_iHour31 < 0) || (m_iHour31 > 24) || (m_iHour32 < 0) || (m_iHour32 > 24) ||	\
		(m_iHour41 < 0) || (m_iHour41 > 24) || (m_iHour42 < 0) || (m_iHour42 > 24) ||   \
		(m_iHour51 < 0) || (m_iHour51 > 24) || (m_iHour52 < 0) || (m_iHour52 > 24) ||	\
		(m_iHour61 < 0) || (m_iHour61 > 24) || (m_iHour62 < 0) || (m_iHour62 > 24) ||	\
		(m_iHour71 < 0) || (m_iHour71 > 24) || (m_iHour72 < 0) || (m_iHour72 > 24) ||	\
		(m_iHour81 < 0) || (m_iHour81 > 24) || (m_iHour82 < 0) || (m_iHour82 > 24))
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
		(m_iMin81 < 0) || (m_iMin81 > 60) || (m_iMin82 < 0) || (m_iMin82 > 60))
	{
		g_StringLanType(szLan, "分钟范围在0 -- 60之间", "Minute between 0 - 60 ");
		AfxMessageBox(szLan);
		return FALSE;
	}
	wStartTime[0] = m_iHour11 * 100 + m_iMin11;
	wStartTime[1] = m_iHour21 * 100 + m_iMin21;
	wStartTime[2] = m_iHour31 * 100 + m_iMin31;
	wStartTime[3] = m_iHour41 * 100 + m_iMin41;
	wStopTime[0] = m_iHour12 * 100 + m_iMin12;
	wStopTime[1] = m_iHour22 * 100 + m_iMin22;
	wStopTime[2] = m_iHour32 * 100 + m_iMin32;
	wStopTime[3] = m_iHour42 * 100 + m_iMin42;
	wStartTime[4] = m_iHour51 * 100 + m_iMin51;
	wStartTime[5] = m_iHour61 * 100 + m_iMin61;
	wStartTime[6] = m_iHour71 * 100 + m_iMin71;
	wStartTime[7] = m_iHour81 * 100 + m_iMin81;
	wStopTime[4] = m_iHour52 * 100 + m_iMin52;
	wStopTime[5] = m_iHour62 * 100 + m_iMin62;
	wStopTime[6] = m_iHour72 * 100 + m_iMin72;
	wStopTime[7] = m_iHour82 * 100 + m_iMin82;
	for (i = 0; i < MAX_TIMESEGMENT_V30; i++)
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
		for (j = 0; j < MAX_TIMESEGMENT_V30; j++)
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

/*********************************************************
  Function:	OnLButtonDown
  Desc:		左键与鼠标托动区域的记录,并更新对应的告警区域
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteHideAlarm::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (m_bDrawdetect)
	{
		if (MK_CONTROL&nFlags)
		{
			NET_DVR_RigisterDrawFun(m_lPlayHandle, HideAlarmSetCallBack, 0);
			point.x -= DETECT_AREA_LEFT;
			point.y -= DETECT_AREA_TOP;
			if (point.x < 0)
			{
				point.x = 0;
			}
			g_rectHideAlarmSetArea.left=point.x/16*16;
			if (point.y < 0)
			{
				point.y = 0;
			}
			g_rectHideAlarmSetArea.top=point.y/16*16;
			g_rectHideAlarmSetArea.right=g_rectHideAlarmSetArea.left;
			g_rectHideAlarmSetArea.bottom=g_rectHideAlarmSetArea.top;
			POINT tPoint=point;
			g_rectHideAlarmShow.left=tPoint.x/16*16;
			g_rectHideAlarmShow.top=tPoint.y/16*16;
			g_rectHideAlarmShow.right=tPoint.x/16*16+1;
			g_rectHideAlarmShow.bottom=tPoint.y/16*16+1;
		}
	}	
	CDialog::OnLButtonDown(nFlags, point);
}

/*********************************************************
  Function:	OnMouseMove
  Desc:		左键与鼠标托动区域的记录,并更新对应的告警区域
  Input:	nFlags,功能键状态;point,鼠标位置
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteHideAlarm::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_bDrawdetect)
	{
		if (MK_CONTROL&nFlags&&MK_LBUTTON&nFlags)
		{
			point.x -= DETECT_AREA_LEFT;
			point.y -= DETECT_AREA_TOP;
			if (point.x > 352)
			{
				point.x = 352;
			}
			g_rectHideAlarmSetArea.right=point.x/16*16;
			if (point.y > 288)
			{
				point.y = 288;
			}
			g_rectHideAlarmSetArea.bottom=point.y/16*16;
			POINT tPoint=point;
			g_rectHideAlarmShow.right=tPoint.x/16*16;
			g_rectHideAlarmShow.bottom=tPoint.y/16*16;
		}
	}	
	CDialog::OnMouseMove(nFlags, point);
}

/*********************************************************
Function:	OnBnClickedBtnAlarmInTimeOk
Desc:		完称时间表设置,检验并更新对应结构中的时间表
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteHideAlarm::OnBnClickedBtnHaDayOk()
{
	UpdateData(TRUE);
	if (!TimeTest())
	{
		return;
	}
	int	i = m_comboWeekday.GetCurSel();	
	g_lpHideAlarm->struAlarmTime[i][0].byStartHour = m_iHour11;
	g_lpHideAlarm->struAlarmTime[i][0].byStartMin = m_iMin11;
	g_lpHideAlarm->struAlarmTime[i][0].byStopHour = m_iHour12;
	g_lpHideAlarm->struAlarmTime[i][0].byStopMin = m_iMin12;
	g_lpHideAlarm->struAlarmTime[i][1].byStartHour = m_iHour21;
	g_lpHideAlarm->struAlarmTime[i][1].byStartMin = m_iMin21;
	g_lpHideAlarm->struAlarmTime[i][1].byStopHour = m_iHour22;
	g_lpHideAlarm->struAlarmTime[i][1].byStopMin = m_iMin22;
	g_lpHideAlarm->struAlarmTime[i][2].byStartHour = m_iHour31;
	g_lpHideAlarm->struAlarmTime[i][2].byStartMin = m_iMin31;
	g_lpHideAlarm->struAlarmTime[i][2].byStopHour = m_iHour32;
	g_lpHideAlarm->struAlarmTime[i][2].byStopMin = m_iMin32;
	g_lpHideAlarm->struAlarmTime[i][3].byStartHour = m_iHour41;
	g_lpHideAlarm->struAlarmTime[i][3].byStartMin = m_iMin41;
	g_lpHideAlarm->struAlarmTime[i][3].byStopHour = m_iHour42;
	g_lpHideAlarm->struAlarmTime[i][3].byStopMin = m_iMin42;
	g_lpHideAlarm->struAlarmTime[i][4].byStartHour = m_iHour51;
	g_lpHideAlarm->struAlarmTime[i][4].byStartMin = m_iMin51;
	g_lpHideAlarm->struAlarmTime[i][4].byStopHour = m_iHour52;
	g_lpHideAlarm->struAlarmTime[i][4].byStopMin = m_iMin52;
	g_lpHideAlarm->struAlarmTime[i][5].byStartHour = m_iHour61;
	g_lpHideAlarm->struAlarmTime[i][5].byStartMin = m_iMin61;
	g_lpHideAlarm->struAlarmTime[i][5].byStopHour = m_iHour62;
	g_lpHideAlarm->struAlarmTime[i][5].byStopMin = m_iMin62;
	g_lpHideAlarm->struAlarmTime[i][6].byStartHour = m_iHour71;
	g_lpHideAlarm->struAlarmTime[i][6].byStartMin = m_iMin71;
	g_lpHideAlarm->struAlarmTime[i][6].byStopHour = m_iHour72;
	g_lpHideAlarm->struAlarmTime[i][6].byStopMin = m_iMin72;
	g_lpHideAlarm->struAlarmTime[i][7].byStartHour = m_iHour81;
	g_lpHideAlarm->struAlarmTime[i][7].byStartMin = m_iMin81;
	g_lpHideAlarm->struAlarmTime[i][7].byStopHour = m_iHour82;
	g_lpHideAlarm->struAlarmTime[i][7].byStopMin = m_iMin82;
	GetDlgItem(IDC_COMBO_HIDE_ALARM_DAY_COPY)->EnableWindow(TRUE);
}

/*********************************************************
  Function:	OnBnClickedChkHideAlarmShow
  Desc:		遮挡告警区域的显示
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteHideAlarm::OnBnClickedChkHideAlarmShow()
{
	if (m_lPlayHandle < 0)
	{
		return;
	}
	UpdateData(TRUE);
	if (m_bChkHideAlarmSet)
	{
		m_bChkHideAlarmSet = FALSE;
		m_bDrawdetect = FALSE;
		UpdateData(FALSE);
		GetDlgItem(ID_BTN_HIDE_ALARM_OK)->EnableWindow(FALSE);
	}
	if (m_bChkHideAlarmShow)
	{
		NET_DVR_RigisterDrawFun(m_lPlayHandle,NULL, 0);
		Sleep(200);
		NET_DVR_RigisterDrawFun(m_lPlayHandle,HideAlarmGetCallBack, 0);
	}
	else
	{
		NET_DVR_RigisterDrawFun(m_lPlayHandle,NULL, 0);
	}
}

/*********************************************************
  Function:	OnBnClickedChkHideAlarmSet
  Desc:		遮挡告警的设置
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteHideAlarm::OnBnClickedChkHideAlarmSet()
{
	if (m_lPlayHandle < 0)
	{
		return;
	}
	UpdateData(TRUE);
	if (m_bChkHideAlarmShow)
	{
		m_bChkHideAlarmShow = FALSE;
		UpdateData(FALSE);
	}
	if (m_bChkHideAlarmSet)
	{
		NET_DVR_RigisterDrawFun(m_lPlayHandle,NULL,0);
		m_bDrawdetect = TRUE;
		GetDlgItem(ID_BTN_HIDE_ALARM_OK)->EnableWindow(TRUE);
	}
	else
	{
		m_bDrawdetect = FALSE;
		NET_DVR_RigisterDrawFun(m_lPlayHandle,NULL,0);
		GetDlgItem(ID_BTN_HIDE_ALARM_OK)->EnableWindow(FALSE);
	}
}

/*********************************************************
Function:	OnBnClickedBtnHideAlarmOk
Desc:		完成时间表设置,检验并更新对应结构中的时间表
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteHideAlarm::OnBnClickedBtnHideAlarmOk()
{
	UpdateData(TRUE);
	if (!TimeTest())
	{
		return;
	}
	int	i = m_comboWeekday.GetCurSel();	
	g_lpHideAlarm->struAlarmTime[i][0].byStartHour = m_iHour11;
	g_lpHideAlarm->struAlarmTime[i][0].byStartMin = m_iMin11;
	g_lpHideAlarm->struAlarmTime[i][0].byStopHour = m_iHour12;
	g_lpHideAlarm->struAlarmTime[i][0].byStopMin = m_iMin12;
	g_lpHideAlarm->struAlarmTime[i][1].byStartHour = m_iHour21;
	g_lpHideAlarm->struAlarmTime[i][1].byStartMin = m_iMin21;
	g_lpHideAlarm->struAlarmTime[i][1].byStopHour = m_iHour22;
	g_lpHideAlarm->struAlarmTime[i][1].byStopMin = m_iMin22;
	g_lpHideAlarm->struAlarmTime[i][2].byStartHour = m_iHour31;
	g_lpHideAlarm->struAlarmTime[i][2].byStartMin = m_iMin31;
	g_lpHideAlarm->struAlarmTime[i][2].byStopHour = m_iHour32;
	g_lpHideAlarm->struAlarmTime[i][2].byStopMin = m_iMin32;
	g_lpHideAlarm->struAlarmTime[i][3].byStartHour = m_iHour41;
	g_lpHideAlarm->struAlarmTime[i][3].byStartMin = m_iMin41;
	g_lpHideAlarm->struAlarmTime[i][3].byStopHour = m_iHour42;
	g_lpHideAlarm->struAlarmTime[i][3].byStopMin = m_iMin42;

	g_lpHideAlarm->struAlarmTime[i][4].byStartHour = m_iHour51;
	g_lpHideAlarm->struAlarmTime[i][4].byStartMin = m_iMin51;
	g_lpHideAlarm->struAlarmTime[i][4].byStopHour = m_iHour52;
	g_lpHideAlarm->struAlarmTime[i][4].byStopMin = m_iMin52;
	g_lpHideAlarm->struAlarmTime[i][5].byStartHour = m_iHour61;
	g_lpHideAlarm->struAlarmTime[i][5].byStartMin = m_iMin61;
	g_lpHideAlarm->struAlarmTime[i][5].byStopHour = m_iHour62;
	g_lpHideAlarm->struAlarmTime[i][5].byStopMin = m_iMin62;
	g_lpHideAlarm->struAlarmTime[i][6].byStartHour = m_iHour71;
	g_lpHideAlarm->struAlarmTime[i][6].byStartMin = m_iMin71;
	g_lpHideAlarm->struAlarmTime[i][6].byStopHour = m_iHour72;
	g_lpHideAlarm->struAlarmTime[i][6].byStopMin = m_iMin72;
	g_lpHideAlarm->struAlarmTime[i][7].byStartHour = m_iHour81;
	g_lpHideAlarm->struAlarmTime[i][7].byStartMin = m_iMin81;
	g_lpHideAlarm->struAlarmTime[i][7].byStopHour = m_iHour82;
	g_lpHideAlarm->struAlarmTime[i][7].byStopMin = m_iMin82;
	if (g_rectHideAlarmSetArea.top <= g_rectHideAlarmSetArea.bottom)
	{
		if (g_rectHideAlarmSetArea.left <= g_rectHideAlarmSetArea.right)
		{
			g_lpHideAlarm->wHideAlarmAreaHeight = (WORD)((g_rectHideAlarmSetArea.bottom-g_rectHideAlarmSetArea.top)*2);
			g_lpHideAlarm->wHideAlarmAreaWidth = (WORD)((g_rectHideAlarmSetArea.right-g_rectHideAlarmSetArea.left)*2);
			g_lpHideAlarm->wHideAlarmAreaTopLeftX = (WORD)(g_rectHideAlarmSetArea.left*2);
			g_lpHideAlarm->wHideAlarmAreaTopLeftY = (WORD)(g_rectHideAlarmSetArea.top*2);
		}
		else
		{
			g_lpHideAlarm->wHideAlarmAreaHeight = (WORD)((g_rectHideAlarmSetArea.bottom-g_rectHideAlarmSetArea.top)*2);
			g_lpHideAlarm->wHideAlarmAreaWidth = (WORD)((g_rectHideAlarmSetArea.left-g_rectHideAlarmSetArea.right)*2);
			g_lpHideAlarm->wHideAlarmAreaTopLeftX = (WORD)(g_rectHideAlarmSetArea.right*2);
			g_lpHideAlarm->wHideAlarmAreaTopLeftY = (WORD)(g_rectHideAlarmSetArea.top*2);
		}	
	}
	else
	{
		if (g_rectHideAlarmSetArea.left <= g_rectHideAlarmSetArea.right)
		{
			g_lpHideAlarm->wHideAlarmAreaHeight = (WORD)((g_rectHideAlarmSetArea.top-g_rectHideAlarmSetArea.bottom)*2);
			g_lpHideAlarm->wHideAlarmAreaWidth = (WORD)((g_rectHideAlarmSetArea.right-g_rectHideAlarmSetArea.left)*2);
			g_lpHideAlarm->wHideAlarmAreaTopLeftX = (WORD)(g_rectHideAlarmSetArea.left*2);
			g_lpHideAlarm->wHideAlarmAreaTopLeftY = (WORD)(g_rectHideAlarmSetArea.bottom*2);
		}
		else
		{
			g_lpHideAlarm->wHideAlarmAreaHeight = (WORD)((g_rectHideAlarmSetArea.top-g_rectHideAlarmSetArea.bottom)*2);
			g_lpHideAlarm->wHideAlarmAreaWidth = (WORD)((g_rectHideAlarmSetArea.left-g_rectHideAlarmSetArea.right)*2);
			g_lpHideAlarm->wHideAlarmAreaTopLeftX = (WORD)(g_rectHideAlarmSetArea.right*2);
			g_lpHideAlarm->wHideAlarmAreaTopLeftY = (WORD)(g_rectHideAlarmSetArea.bottom*2);
		}
	}
	g_lpHideAlarm->dwEnableHideAlarm = m_comboHideAlarmSensitive.GetCurSel()+1;	

	g_lpHideAlarm->strHideAlarmHandleType.dwHandleType = 0;
	g_lpHideAlarm->strHideAlarmHandleType.dwHandleType |= (m_bChkMonitorAlarm << 0);
	g_lpHideAlarm->strHideAlarmHandleType.dwHandleType |= (m_bChkAudioAlarm << 1);
	g_lpHideAlarm->strHideAlarmHandleType.dwHandleType |= (m_bChkReportCenter << 2);
	g_lpHideAlarm->strHideAlarmHandleType.dwHandleType |= (m_bChkInvokeAlarmOut << 3);
	g_lpHideAlarm->strHideAlarmHandleType.dwHandleType |= (m_bChkInvokeJpegCapture <<4);
	for (i=0; i<MAX_ALARMOUT_V30; i++)
	{
		g_lpHideAlarm->strHideAlarmHandleType.byRelAlarmOut[i] = m_bAlarmOut[i];
	}
}

/*********************************************************
  Function:	OnBnClickedBtnHideAlarmExit
  Desc:		取消遮挡告警区域的设置
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteHideAlarm::OnBnClickedBtnHideAlarmExit()
{
	if (m_lPlayHandle >= 0)
	{
		NET_DVR_RigisterDrawFun(m_lPlayHandle,NULL, 0);
		NET_DVR_StopRealPlay(m_lPlayHandle);
		m_lPlayHandle = -1;
	}
	CDialog::OnOK();
}

/*********************************************************
  Function:	OnBnClickedChkHaInvokeAlarmOut
  Desc:		遮挡告警触发的告警输出
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteHideAlarm::OnBnClickedChkHaInvokeAlarmOut()
{
	UpdateData(TRUE);
	m_treeAlarmOut.EnableWindow(m_bChkInvokeAlarmOut);
}

/*********************************************************
  Function:	OnBnClickedBtnHaDayCopy
  Desc:		复制时间到对应的日期
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteHideAlarm::OnBnClickedBtnHaDayCopy()
{
	UpdateData(TRUE);
	int j,k;
	int i = m_comboWeekday.GetCurSel();
	int m_nCopyTime = m_comboDayCopy.GetCurSel() - 1;

	if (m_nCopyTime == -1)
	{
		for (j=0; j<MAX_DAYS; j++)
		{
			if (j == i)
			{
				continue;
			}
			for (k=0; k<MAX_TIMESEGMENT_V30; k++)
			{
				memcpy(&(g_lpHideAlarm->struAlarmTime[j][k]), &(g_lpHideAlarm->struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
			}
		}
	}
	else
	{
		for (k=0; k<MAX_TIMESEGMENT_V30; k++)
		{
			memcpy(&(g_lpHideAlarm->struAlarmTime[m_nCopyTime][k]), &(g_lpHideAlarm->struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
		}
	}
}

/*********************************************************
  Function:	OnCbnSelchangeComboHaWeekday
  Desc:		选择对应日期,并更新时间表的显示
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteHideAlarm::OnCbnSelchangeComboHaWeekday()
{
	UpdateData(TRUE);
	int	i = m_comboWeekday.GetCurSel();	
	m_iHour11 = g_lpHideAlarm->struAlarmTime[i][0].byStartHour;
	m_iMin11 = g_lpHideAlarm->struAlarmTime[i][0].byStartMin;
	m_iHour12 = g_lpHideAlarm->struAlarmTime[i][0].byStopHour;
	m_iMin12 = g_lpHideAlarm->struAlarmTime[i][0].byStopMin;
	m_iHour21 = g_lpHideAlarm->struAlarmTime[i][1].byStartHour;
	m_iMin21 = g_lpHideAlarm->struAlarmTime[i][1].byStartMin;
	m_iHour22 = g_lpHideAlarm->struAlarmTime[i][1].byStopHour;
	m_iMin22 = g_lpHideAlarm->struAlarmTime[i][1].byStopMin;
	m_iHour31 = g_lpHideAlarm->struAlarmTime[i][2].byStartHour;
	m_iMin31 = g_lpHideAlarm->struAlarmTime[i][2].byStartMin;
	m_iHour32 = g_lpHideAlarm->struAlarmTime[i][2].byStopHour;
	m_iMin32 = g_lpHideAlarm->struAlarmTime[i][2].byStopMin;
	m_iHour41 = g_lpHideAlarm->struAlarmTime[i][3].byStartHour;
	m_iMin41 = g_lpHideAlarm->struAlarmTime[i][3].byStartMin;
	m_iHour42 = g_lpHideAlarm->struAlarmTime[i][3].byStopHour;
	m_iMin42 = g_lpHideAlarm->struAlarmTime[i][3].byStopMin;
	m_iHour51 = g_lpHideAlarm->struAlarmTime[i][4].byStartHour;
	m_iMin51 = g_lpHideAlarm->struAlarmTime[i][4].byStartMin;
	m_iHour52 = g_lpHideAlarm->struAlarmTime[i][4].byStopHour;
	m_iMin52 = g_lpHideAlarm->struAlarmTime[i][4].byStopMin;
	m_iHour61 = g_lpHideAlarm->struAlarmTime[i][5].byStartHour;
	m_iMin61 = g_lpHideAlarm->struAlarmTime[i][5].byStartMin;
	m_iHour62 = g_lpHideAlarm->struAlarmTime[i][5].byStopHour;
	m_iMin62 = g_lpHideAlarm->struAlarmTime[i][5].byStopMin;
	m_iHour71 = g_lpHideAlarm->struAlarmTime[i][6].byStartHour;
	m_iMin71 = g_lpHideAlarm->struAlarmTime[i][6].byStartMin;
	m_iHour72 = g_lpHideAlarm->struAlarmTime[i][6].byStopHour;
	m_iMin72 = g_lpHideAlarm->struAlarmTime[i][6].byStopMin;
	m_iHour81 = g_lpHideAlarm->struAlarmTime[i][7].byStartHour;
	m_iMin81 = g_lpHideAlarm->struAlarmTime[i][7].byStartMin;
	m_iHour82 = g_lpHideAlarm->struAlarmTime[i][7].byStopHour;
	m_iMin82 = g_lpHideAlarm->struAlarmTime[i][7].byStopMin;
	UpdateData(FALSE);
}


/*********************************************************
  Function:	CreateTree
  Desc:		创建告警输出通道树
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteHideAlarm::CreateTree(void)
{
	g_CreateAlarmOutTree(m_treeAlarmOut, m_dwDevIndex, m_bAlarmOut);
}

/*********************************************************
  Function:	OnClickTreeAlarmOut
  Desc:		select the alarm out channel
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteHideAlarm::OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	CPoint pt(0,0);
	CRect rc(0,0,0,0);
	GetCursorPos(&pt);
	GetDlgItem(IDC_TREE_ALARM_OUT)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	ScreenToClient(&pt);
	pt.x = pt.x - rc.left;
	pt.y = pt.y - rc.top;

	UINT uFlag = 0;
	HTREEITEM hSelect = m_treeAlarmOut.HitTest(pt, &uFlag);

	if (NULL == hSelect) 
	{
		return;
	}
	m_treeAlarmOut.SelectItem(hSelect);
	DWORD dwIndex = m_treeAlarmOut.GetItemData(hSelect)%1000;
	BOOL bCheck = m_treeAlarmOut.GetCheck(hSelect);
	m_bAlarmOut[dwIndex] = !bCheck;
	//单击的时候改变checkbox的选中状态
	if (uFlag != LVHT_TOLEFT)
	{
		m_treeAlarmOut.SetCheck(hSelect, !bCheck);
	}
	else
	{
		m_treeAlarmOut.SetCheck(hSelect, bCheck);
	}

	*pResult = 0;
}

/*********************************************************
  Function:	OnPaint
  Desc:		need to draw the alarm out channel when paint
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteHideAlarm::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CreateTree();
	// Do not call CDialog::OnPaint() for painting messages
}

/*********************************************************
Function:	OnCancel
Desc:		按ESC退出窗口，释放播放资源。
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteHideAlarm::OnCancel() 
{
	NET_DVR_StopRealPlay(m_lPlayHandle);
	CDialog::OnCancel();
}
