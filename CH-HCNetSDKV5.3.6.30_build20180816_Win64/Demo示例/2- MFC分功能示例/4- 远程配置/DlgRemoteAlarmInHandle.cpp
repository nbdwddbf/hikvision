/**********************************************************
FileName:    DlgRemoteAlarmInHandle.cpp
Description: 告警输入处理      
Date:       
Note: 		 
Modification History:      
<version> <time>         <desc>
    
***********************************************************/
#include "stdafx.h"
#include "config.h"
#include "DlgRemoteAlarmInHandle.h"


// CDlgRemoteAlarmInHandle dialog
/*********************************************************
  Function:	CDlgRemoteAlarmInHandle
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgRemoteAlarmInHandle, CDialog)
CDlgRemoteAlarmInHandle::CDlgRemoteAlarmInHandle(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteAlarmInHandle::IDD, pParent)
	, m_lpAlarmIn(NULL)
	, m_iChanCount(0)
	, m_lStartChannel(0)
	, m_iCopyTime(0)
	, m_dwAlarmInNum(0)
	, m_dwAlarmOutNum(0)
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
	, m_bChkUploadCenter(FALSE)
	, m_bChkMonitorAlarm(FALSE)
	, m_bChkVoiceAlarm(FALSE)
	, m_dwDevIndex(0)
{
}

/*********************************************************
  Function:	~CDlgRemoteAlarmInHandle
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgRemoteAlarmInHandle::~CDlgRemoteAlarmInHandle()
{
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteAlarmInHandle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteAlarmInHandle)
	DDX_Control(pDX, IDC_TREE_ALARM_OUT, m_treeAlarmOut);
	DDX_Control(pDX, IDC_TREE_CHAN, m_treeChan);
	DDX_Control(pDX, IDC_COMBO_ALARMIN_WEEKDAY, m_comboWeekday);
	DDX_Control(pDX, IDC_COMBO_ALARMIN_COPY_TIME, m_comboCopyTime);
	DDX_Check(pDX, IDC_CHK_ALARMIN_MONITOR, m_bChkMonitorAlarm);
	DDX_Check(pDX, IDC_CHK_ALARMIN_VOICE, m_bChkVoiceAlarm);
	DDX_Check(pDX, IDC_CHK_ALARMIN_UPLOAD_CENTER, m_bChkUploadCenter);
	DDX_Check(pDX, IDC_CHK_ALARMIN_INVOKE_ALARMOUT, m_bChkInvokeAlarmOut);
	DDX_Check(pDX, IDC_CHK_INVOKE_JPEG_CAPTURE, m_bChkInvokeJpegCapture);
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
	//}}AFX_DATA_MAP
}


/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgRemoteAlarmInHandle, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteAlarmInHandle)	
	ON_BN_CLICKED(IDC_BTN_ALARM_IN_TIME_OK, OnBnClickedBtnAlarmInTimeOk)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARMIN_WEEKDAY, OnCbnSelchangeComboAlarminWeekday)
	ON_BN_CLICKED(IDC_BTN_ALARMIN_TIME_COPY, OnBnClickedBtnAlarminTimeCopy)
	ON_BN_CLICKED(IDC_BTN_ALARMIN_OK, OnBnClickedBtnAlarminOk)
	ON_BN_CLICKED(IDC_BTN_ALARMIN_EXIT, OnBnClickedBtnAlarminExit)
	ON_BN_CLICKED(IDC_CHK_ALARMIN_INVOKE_ALARMOUT, OnBnClickedChkAlarminInvokeAlarmout)
	ON_NOTIFY(NM_CLICK, IDC_TREE_CHAN, OnClickTreeChan)
	ON_NOTIFY(NM_CLICK, IDC_TREE_ALARM_OUT, OnClickTreeAlarmOut)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CDlgRemoteAlarmInHandle message handlers

/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgRemoteAlarmInHandle::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int i = 0;
	m_iCopyTime = -1;
	m_bChkMonitorAlarm = m_lpAlarmIn->struAlarmHandleType.dwHandleType &0x01;
	m_bChkVoiceAlarm = (m_lpAlarmIn->struAlarmHandleType.dwHandleType>>1)&0x01;
	m_bChkUploadCenter = (m_lpAlarmIn->struAlarmHandleType.dwHandleType>>2)&0x01;
	m_bChkInvokeAlarmOut = (m_lpAlarmIn->struAlarmHandleType.dwHandleType>>3)&0x01;
	m_bChkInvokeJpegCapture = (m_lpAlarmIn->struAlarmHandleType.dwHandleType>>4)&0x01;

	m_treeAlarmOut.EnableWindow(m_bChkInvokeAlarmOut);
	for (i=0;i<MAX_ALARMOUT_V30;i++)
	{
		m_bAlarmOut[i] = m_lpAlarmIn->struAlarmHandleType.byRelAlarmOut[i];
	}
	for (i=0; i< MAX_CHANNUM_V30; i++)
	{
		m_bRecordChan[i] = m_lpAlarmIn->byRelRecordChan[i];
	}

	m_comboWeekday.SetCurSel(0);
	m_comboCopyTime.SetCurSel(0);
	m_iHour11 = m_lpAlarmIn->struAlarmTime[0][0].byStartHour;
	m_iMin11 = m_lpAlarmIn->struAlarmTime[0][0].byStartMin;
	m_iHour12 = m_lpAlarmIn->struAlarmTime[0][0].byStopHour;
	m_iMin12 = m_lpAlarmIn->struAlarmTime[0][0].byStopMin;
	m_iHour21 = m_lpAlarmIn->struAlarmTime[0][1].byStartHour;
	m_iMin21 = m_lpAlarmIn->struAlarmTime[0][1].byStartMin;
	m_iHour22 = m_lpAlarmIn->struAlarmTime[0][1].byStopHour;
	m_iMin22 = m_lpAlarmIn->struAlarmTime[0][1].byStopMin;
	m_iHour31 = m_lpAlarmIn->struAlarmTime[0][2].byStartHour;
	m_iMin31 = m_lpAlarmIn->struAlarmTime[0][2].byStartMin;
	m_iHour32 = m_lpAlarmIn->struAlarmTime[0][2].byStopHour;
	m_iMin32 = m_lpAlarmIn->struAlarmTime[0][2].byStopMin;
	m_iHour41 = m_lpAlarmIn->struAlarmTime[0][3].byStartHour;
	m_iMin41 = m_lpAlarmIn->struAlarmTime[0][3].byStartMin;
	m_iHour42 = m_lpAlarmIn->struAlarmTime[0][3].byStopHour;
	m_iMin42 = m_lpAlarmIn->struAlarmTime[0][3].byStopMin;
	m_iHour51 = m_lpAlarmIn->struAlarmTime[0][4].byStartHour;
	m_iMin51 = m_lpAlarmIn->struAlarmTime[0][4].byStartMin;
	m_iHour52 = m_lpAlarmIn->struAlarmTime[0][4].byStopHour;
	m_iMin52 = m_lpAlarmIn->struAlarmTime[0][4].byStopMin;
	m_iHour61 = m_lpAlarmIn->struAlarmTime[0][5].byStartHour;
	m_iMin61 = m_lpAlarmIn->struAlarmTime[0][5].byStartMin;
	m_iHour62 = m_lpAlarmIn->struAlarmTime[0][5].byStopHour;
	m_iMin62 = m_lpAlarmIn->struAlarmTime[0][5].byStopMin;
	m_iHour71 = m_lpAlarmIn->struAlarmTime[0][6].byStartHour;
	m_iMin71 = m_lpAlarmIn->struAlarmTime[0][6].byStartMin;
	m_iHour72 = m_lpAlarmIn->struAlarmTime[0][6].byStopHour;
	m_iMin72 = m_lpAlarmIn->struAlarmTime[0][6].byStopMin;
	m_iHour81 = m_lpAlarmIn->struAlarmTime[0][7].byStartHour;
	m_iMin81 = m_lpAlarmIn->struAlarmTime[0][7].byStartMin;
	m_iHour82 = m_lpAlarmIn->struAlarmTime[0][7].byStopHour;
	m_iMin82 = m_lpAlarmIn->struAlarmTime[0][7].byStopMin;
	GetDlgItem(IDC_BTN_ALARMIN_OK)->EnableWindow(TRUE);
	UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/*********************************************************
  Function:	OnBnClickedBtnAlarmInTimeOk
  Desc:		完称时间表设置,检验并更新对应结构中的时间表
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteAlarmInHandle::OnBnClickedBtnAlarmInTimeOk()
{
	UpdateData(TRUE);
	if (!TimeTest())
	{
		return;
	}
	int	i = m_comboWeekday.GetCurSel();	
	m_lpAlarmIn->struAlarmTime[i][0].byStartHour = m_iHour11;
	m_lpAlarmIn->struAlarmTime[i][0].byStartMin = m_iMin11;
	m_lpAlarmIn->struAlarmTime[i][0].byStopHour = m_iHour12;
	m_lpAlarmIn->struAlarmTime[i][0].byStopMin = m_iMin12;
	m_lpAlarmIn->struAlarmTime[i][1].byStartHour = m_iHour21;
	m_lpAlarmIn->struAlarmTime[i][1].byStartMin = m_iMin21;
	m_lpAlarmIn->struAlarmTime[i][1].byStopHour = m_iHour22;
	m_lpAlarmIn->struAlarmTime[i][1].byStopMin = m_iMin22;
	m_lpAlarmIn->struAlarmTime[i][2].byStartHour = m_iHour31;
	m_lpAlarmIn->struAlarmTime[i][2].byStartMin = m_iMin31;
	m_lpAlarmIn->struAlarmTime[i][2].byStopHour = m_iHour32;
	m_lpAlarmIn->struAlarmTime[i][2].byStopMin = m_iMin32;
	m_lpAlarmIn->struAlarmTime[i][3].byStartHour = m_iHour41;
	m_lpAlarmIn->struAlarmTime[i][3].byStartMin = m_iMin41;
	m_lpAlarmIn->struAlarmTime[i][3].byStopHour = m_iHour42;
	m_lpAlarmIn->struAlarmTime[i][3].byStopMin = m_iMin42;
	m_lpAlarmIn->struAlarmTime[i][4].byStartHour = m_iHour51;
	m_lpAlarmIn->struAlarmTime[i][4].byStartMin = m_iMin51;
	m_lpAlarmIn->struAlarmTime[i][4].byStopHour = m_iHour52;
	m_lpAlarmIn->struAlarmTime[i][4].byStopMin = m_iMin52;
	m_lpAlarmIn->struAlarmTime[i][5].byStartHour = m_iHour61;
	m_lpAlarmIn->struAlarmTime[i][5].byStartMin = m_iMin61;
	m_lpAlarmIn->struAlarmTime[i][5].byStopHour = m_iHour62;
	m_lpAlarmIn->struAlarmTime[i][5].byStopMin = m_iMin62;
	m_lpAlarmIn->struAlarmTime[i][6].byStartHour = m_iHour71;
	m_lpAlarmIn->struAlarmTime[i][6].byStartMin = m_iMin71;
	m_lpAlarmIn->struAlarmTime[i][6].byStopHour = m_iHour72;
	m_lpAlarmIn->struAlarmTime[i][6].byStopMin = m_iMin72;
	m_lpAlarmIn->struAlarmTime[i][7].byStartHour = m_iHour81;
	m_lpAlarmIn->struAlarmTime[i][7].byStartMin = m_iMin81;
	m_lpAlarmIn->struAlarmTime[i][7].byStopHour = m_iHour82;
	m_lpAlarmIn->struAlarmTime[i][7].byStopMin = m_iMin82;

	GetDlgItem(IDC_BTN_ALARMIN_TIME_COPY)->EnableWindow(TRUE);
}

/*********************************************************
  Function:	OnCbnSelchangeComboAlarminWeekday
  Desc:		选择一天,并更新对应的时间表
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteAlarmInHandle::OnCbnSelchangeComboAlarminWeekday()
{
	UpdateData(TRUE);
	int	i = m_comboWeekday.GetCurSel();	
	m_iHour11 = m_lpAlarmIn->struAlarmTime[i][0].byStartHour;
	m_iMin11 = m_lpAlarmIn->struAlarmTime[i][0].byStartMin;
	m_iHour12 = m_lpAlarmIn->struAlarmTime[i][0].byStopHour;
	m_iMin12 = m_lpAlarmIn->struAlarmTime[i][0].byStopMin;
	m_iHour21 = m_lpAlarmIn->struAlarmTime[i][1].byStartHour;
	m_iMin21 = m_lpAlarmIn->struAlarmTime[i][1].byStartMin;
	m_iHour22 = m_lpAlarmIn->struAlarmTime[i][1].byStopHour;
	m_iMin22 = m_lpAlarmIn->struAlarmTime[i][1].byStopMin;
	m_iHour31 = m_lpAlarmIn->struAlarmTime[i][2].byStartHour;
	m_iMin31 = m_lpAlarmIn->struAlarmTime[i][2].byStartMin;
	m_iHour32 = m_lpAlarmIn->struAlarmTime[i][2].byStopHour;
	m_iMin32 = m_lpAlarmIn->struAlarmTime[i][2].byStopMin;
	m_iHour41 = m_lpAlarmIn->struAlarmTime[i][3].byStartHour;
	m_iMin41 = m_lpAlarmIn->struAlarmTime[i][3].byStartMin;
	m_iHour42 = m_lpAlarmIn->struAlarmTime[i][3].byStopHour;
	m_iMin42 = m_lpAlarmIn->struAlarmTime[i][3].byStopMin;
	m_iHour51 = m_lpAlarmIn->struAlarmTime[i][4].byStartHour;
	m_iMin51 = m_lpAlarmIn->struAlarmTime[i][4].byStartMin;
	m_iHour52 = m_lpAlarmIn->struAlarmTime[i][4].byStopHour;
	m_iMin52 = m_lpAlarmIn->struAlarmTime[i][4].byStopMin;
	m_iHour61 = m_lpAlarmIn->struAlarmTime[i][5].byStartHour;
	m_iMin61 = m_lpAlarmIn->struAlarmTime[i][5].byStartMin;
	m_iHour62 = m_lpAlarmIn->struAlarmTime[i][5].byStopHour;
	m_iMin62 = m_lpAlarmIn->struAlarmTime[i][5].byStopMin;
	m_iHour71 = m_lpAlarmIn->struAlarmTime[i][6].byStartHour;
	m_iMin71 = m_lpAlarmIn->struAlarmTime[i][6].byStartMin;
	m_iHour72 = m_lpAlarmIn->struAlarmTime[i][6].byStopHour;
	m_iMin72 = m_lpAlarmIn->struAlarmTime[i][6].byStopMin;
	m_iHour81 = m_lpAlarmIn->struAlarmTime[i][7].byStartHour;
	m_iMin81 = m_lpAlarmIn->struAlarmTime[i][7].byStartMin;
	m_iHour82 = m_lpAlarmIn->struAlarmTime[i][7].byStopHour;
	m_iMin82 = m_lpAlarmIn->struAlarmTime[i][7].byStopMin;
	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnBnClickedBtnAlarminTimeCopy
  Desc:		复制时间表到对应的日期
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteAlarmInHandle::OnBnClickedBtnAlarminTimeCopy()
{
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
			for (k=0; k<MAX_TIMESEGMENT_V30; k++)
			{
				memcpy(&(m_lpAlarmIn->struAlarmTime[j][k]), &(m_lpAlarmIn->struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
			}
		}
	}
	else
	{
		for (k=0; k<MAX_TIMESEGMENT_V30; k++)
		{
			memcpy(&(m_lpAlarmIn->struAlarmTime[m_nCopyTime][k]), &(m_lpAlarmIn->struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
		}
	}
}

/*********************************************************
Function:	OnBnClickedBtnAlarminOk
Desc:		完称时间表设置,检验并更新对应结构中的时间表,相关告警的状态
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteAlarmInHandle::OnBnClickedBtnAlarminOk()
{
	UpdateData(TRUE);
	if (!TimeTest())
	{
		return;
	}
	int	i = m_comboWeekday.GetCurSel();	
	m_lpAlarmIn->struAlarmTime[i][0].byStartHour = m_iHour11;
	m_lpAlarmIn->struAlarmTime[i][0].byStartMin = m_iMin11;
	m_lpAlarmIn->struAlarmTime[i][0].byStopHour = m_iHour12;
	m_lpAlarmIn->struAlarmTime[i][0].byStopMin = m_iMin12;
	m_lpAlarmIn->struAlarmTime[i][1].byStartHour = m_iHour21;
	m_lpAlarmIn->struAlarmTime[i][1].byStartMin = m_iMin21;
	m_lpAlarmIn->struAlarmTime[i][1].byStopHour = m_iHour22;
	m_lpAlarmIn->struAlarmTime[i][1].byStopMin = m_iMin22;
	m_lpAlarmIn->struAlarmTime[i][2].byStartHour = m_iHour31;
	m_lpAlarmIn->struAlarmTime[i][2].byStartMin = m_iMin31;
	m_lpAlarmIn->struAlarmTime[i][2].byStopHour = m_iHour32;
	m_lpAlarmIn->struAlarmTime[i][2].byStopMin = m_iMin32;
	m_lpAlarmIn->struAlarmTime[i][3].byStartHour = m_iHour41;
	m_lpAlarmIn->struAlarmTime[i][3].byStartMin = m_iMin41;
	m_lpAlarmIn->struAlarmTime[i][3].byStopHour = m_iHour42;
	m_lpAlarmIn->struAlarmTime[i][3].byStopMin = m_iMin42;

	m_lpAlarmIn->struAlarmTime[i][4].byStartHour = m_iHour51;
	m_lpAlarmIn->struAlarmTime[i][4].byStartMin = m_iMin51;
	m_lpAlarmIn->struAlarmTime[i][4].byStopHour = m_iHour52;
	m_lpAlarmIn->struAlarmTime[i][4].byStopMin = m_iMin52;
	m_lpAlarmIn->struAlarmTime[i][5].byStartHour = m_iHour61;
	m_lpAlarmIn->struAlarmTime[i][5].byStartMin = m_iMin61;
	m_lpAlarmIn->struAlarmTime[i][5].byStopHour = m_iHour62;
	m_lpAlarmIn->struAlarmTime[i][5].byStopMin = m_iMin62;
	m_lpAlarmIn->struAlarmTime[i][6].byStartHour = m_iHour71;
	m_lpAlarmIn->struAlarmTime[i][6].byStartMin = m_iMin71;
	m_lpAlarmIn->struAlarmTime[i][6].byStopHour = m_iHour72;
	m_lpAlarmIn->struAlarmTime[i][6].byStopMin = m_iMin72;
	m_lpAlarmIn->struAlarmTime[i][7].byStartHour = m_iHour81;
	m_lpAlarmIn->struAlarmTime[i][7].byStartMin = m_iMin81;
	m_lpAlarmIn->struAlarmTime[i][7].byStopHour = m_iHour82;
	m_lpAlarmIn->struAlarmTime[i][7].byStopMin = m_iMin82;

	for (i=0; i<MAX_CHANNUM_V30; i++)
	{
		m_lpAlarmIn->byRelRecordChan[i] = m_bRecordChan[i];
	}

	m_lpAlarmIn->struAlarmHandleType.dwHandleType = 0;
	m_lpAlarmIn->struAlarmHandleType.dwHandleType |= (m_bChkMonitorAlarm << 0);
	m_lpAlarmIn->struAlarmHandleType.dwHandleType |= (m_bChkVoiceAlarm << 1);
	m_lpAlarmIn->struAlarmHandleType.dwHandleType |= (m_bChkUploadCenter << 2);
	m_lpAlarmIn->struAlarmHandleType.dwHandleType |= (m_bChkInvokeAlarmOut << 3);
	m_lpAlarmIn->struAlarmHandleType.dwHandleType |= (m_bChkInvokeJpegCapture << 4);
	for (i=0; i<MAX_ALARMOUT_V30; i++)
	{
		m_lpAlarmIn->struAlarmHandleType.byRelAlarmOut[i] = m_bAlarmOut[i];
	}

	CDialog::OnOK();
}

/*********************************************************
  Function:	OnBnClickedBtnAlarminExit
  Desc:		取消告警输入的配置
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteAlarmInHandle::OnBnClickedBtnAlarminExit()
{
	CDialog::OnCancel();
}

/*********************************************************
  Function:	OnBnClickedChkAlarminInvokeAlarmout
  Desc:		是否触发告警输出,改变对应的告警输出口的状态
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteAlarmInHandle::OnBnClickedChkAlarminInvokeAlarmout()
{
	UpdateData(TRUE);
	m_treeAlarmOut.EnableWindow(m_bChkInvokeAlarmOut);
}

/*********************************************************
  Function:	TimeTest
  Desc:		校验时间正确性
  Input:	
  Output:	
  Return:	TRUE,正确的时间表;FALSE,错误的时间表;
**********************************************************/
BOOL CDlgRemoteAlarmInHandle::TimeTest()
{
	int i = 0;
	int j = 0;
	WORD wStartTime[MAX_TIMESEGMENT_V30], wStopTime[MAX_TIMESEGMENT_V30];
	char szLan[1024] = {0};
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
  Function:	CreateTree
  Desc:		创建告警输出和视频通道树
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteAlarmInHandle::CreateTree(void)
{
	m_treeChan.DeleteAllItems();
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0;
	HTREEITEM hChanItem = NULL;
	if (m_iChanCount <= 0)
	{
		m_treeAlarmOut.EnableWindow(FALSE);
		m_treeChan.EnableWindow(FALSE);
	}

	for (i = 0; i < MAX_CHANNUM_V30; i++)
	{
		if ((i < m_iChanCount) && g_struDeviceInfo[m_dwDevIndex].struChanInfo[i].bEnable)
		{
			strTemp.Format(ANALOG_C_FORMAT, i+g_struDeviceInfo[m_dwDevIndex].iStartChan);
			hChanItem =  m_treeChan.InsertItem(strTemp, 0, 0, TVI_ROOT);
			m_treeChan.SetItemData(hChanItem, 0*1000 + i);	
			if (m_bRecordChan[i])
			{
				m_treeChan.SetCheck(hChanItem, TRUE);
			}
		}
		else if (i >= MAX_ANALOG_CHANNUM && g_struDeviceInfo[m_dwDevIndex].struChanInfo[i].bEnable)
		{
			strTemp.Format(DIGITAL_C_FORMAT, i+g_struDeviceInfo[m_dwDevIndex].iStartChan-MAX_ANALOG_CHANNUM);
			hChanItem =  m_treeChan.InsertItem(strTemp, 0, 0, TVI_ROOT);
			m_treeChan.SetItemData(hChanItem, 1*1000 + i);	
			if (m_bRecordChan[i])
			{
				m_treeChan.SetCheck(hChanItem, TRUE);
			}
		}
	}
	m_treeChan.SelectItem(hChanItem);
	m_treeChan.Expand(m_treeChan.GetRootItem(),TVE_EXPAND);	

	g_CreateAlarmOutTree(m_treeAlarmOut, m_dwDevIndex, m_bAlarmOut);
}


void CDlgRemoteAlarmInHandle::OnClickTreeChan(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	CPoint pt(0,0);
	CRect rc(0,0,0,0);
	GetCursorPos(&pt);
	GetDlgItem(IDC_TREE_CHAN)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	ScreenToClient(&pt);
	pt.x = pt.x - rc.left;
	pt.y = pt.y - rc.top;

	UINT uFlag = 0;
	HTREEITEM hSelect = m_treeChan.HitTest(pt, &uFlag);

	if (NULL == hSelect) 
	{
		return;
	}
	m_treeChan.SelectItem(hSelect);
	DWORD dwIndex = m_treeChan.GetItemData(hSelect)%1000;
	BOOL bCheck = m_treeChan.GetCheck(hSelect);
	m_bRecordChan[dwIndex] = !bCheck;
	//单击的时候改变checkbox的选中状态
	if (uFlag != LVHT_TOLEFT)
	{
		m_treeChan.SetCheck(hSelect, !bCheck);
	}
	else
	{
		m_treeChan.SetCheck(hSelect, bCheck);
	}

	*pResult = 0;
}

void CDlgRemoteAlarmInHandle::OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult) 
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

void CDlgRemoteAlarmInHandle::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CreateTree();
	// Do not call CDialog::OnPaint() for painting messages
}
