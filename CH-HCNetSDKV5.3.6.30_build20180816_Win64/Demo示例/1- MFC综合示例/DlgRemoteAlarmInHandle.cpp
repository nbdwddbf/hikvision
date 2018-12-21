/**********************************************************
FileName:    DlgRemoteAlarmInHandle.cpp
Description: alarm input handling      
Date:        2008/05/17
Note: 		<global>struct, refer to GeneralDef.h, global variants and functions refer to ClientDemo.cpp   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/
#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgRemoteAlarmInHandle.h"
#include ".\dlgremotealarminhandle.h"


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
	, m_iChanCount(0)
	, m_lStartChannel(0)
	, m_iCopyTime(0)
	, m_dwAlarmInNum(0)
	, m_dwAlarmOutNum(0)
	, m_bChkInvokeAlarmOut(FALSE)
	, m_bChkInvokeJpegCapture(FALSE)
	, m_bChkPicToFtp(FALSE)
    , m_bChkPicToCloud(FALSE)
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
	, m_bChkEmapAlarmOut(FALSE)
	, m_dwDevIndex(0)
	, m_bChkSmsAlarm(FALSE)
{
    m_lServerID = -1;
    m_lAlarmInIndex = -1;
    m_pbRecordChan = NULL;
    m_pbAlarmOut = NULL;
    memset(&m_struHolidayHandle, 0, sizeof(m_struHolidayHandle));
    m_pbRecordChan = new BOOL[MAX_CHANNUM_V40];
    if (m_pbRecordChan != NULL)
    {
        memset(m_pbRecordChan, 0, sizeof(BOOL)*MAX_CHANNUM_V40);   
    }

    m_pbAlarmOut = new BOOL[MAX_ALARMOUT_V40];
    if (m_pbAlarmOut != NULL)
    {
        memset(m_pbAlarmOut,0,sizeof(BOOL)*MAX_ALARMOUT_V40);
    }
     m_bSetHolidayCfg = TRUE;
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
	if (m_pbAlarmOut != NULL)
    {
        delete[] m_pbAlarmOut;
        m_pbAlarmOut = NULL;
    }
	
    if(m_pbRecordChan != NULL)
    {
        delete[] m_pbRecordChan;
        m_pbRecordChan = NULL;
    }
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
	DDX_Check(pDX, IDC_CHK_ALARM_EMAP, m_bChkEmapAlarmOut);
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
	DDX_Check(pDX, IDC_CHK_PIC_FTP, m_bChkPicToFtp);
    DDX_Check(pDX, IDC_CHK_PIC_CLOUD, m_bChkPicToCloud);
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_CHK_ALARMIN_SMS, m_bChkSmsAlarm);
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
	ON_BN_CLICKED(IDC_BTN_RECORDCHAN_ALL, OnBtnRecordchanAll)
	ON_BN_CLICKED(IDC_BTN_ALARMOUT_ALL, OnBtnAlarmoutAll)
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
    if (m_bSetHolidayCfg)
    {
        GetAlarmInHolidayHandle(m_struHolidayHandle);
	}
	GetAlarmInHolidayHandle(m_struHolidayHandle);
    int i = 0;
	m_iCopyTime = -1;
	
	m_bChkMonitorAlarm = m_lpAlarmInV40->struAlarmHandleType.dwHandleType &0x01;
	m_bChkVoiceAlarm = (m_lpAlarmInV40->struAlarmHandleType.dwHandleType>>1)&0x01;
	m_bChkUploadCenter = (m_lpAlarmInV40->struAlarmHandleType.dwHandleType>>2)&0x01;
	m_bChkInvokeAlarmOut = (m_lpAlarmInV40->struAlarmHandleType.dwHandleType>>3)&0x01;
	m_bChkInvokeJpegCapture = (m_lpAlarmInV40->struAlarmHandleType.dwHandleType>>4)&0x01;
	m_bChkEmapAlarmOut = (m_lpAlarmInV40->struAlarmHandleType.dwHandleType>>6)&0x01;
	m_bChkPicToFtp = (m_lpAlarmInV40->struAlarmHandleType.dwHandleType>>9)&0x01;
    m_bChkPicToCloud = (m_lpAlarmInV40->struAlarmHandleType.dwHandleType >> 12) & 0x01;
	m_bChkSmsAlarm = (m_lpAlarmInV40->struAlarmHandleType.dwHandleType >> 13) & 0x01;

	m_treeAlarmOut.EnableWindow(m_bChkInvokeAlarmOut);

	m_pbAlarmOut = new BOOL[MAX_ALARMOUT_V40];
    if (m_pbAlarmOut != NULL)
    {
       memset(m_pbAlarmOut,0,sizeof(BOOL)*MAX_ALARMOUT_V40);
    }

	
	for (i=0;i< MAX_ALARMOUT_V40;i++)
    {
        if (m_lpAlarmInV40->struAlarmHandleType.dwRelAlarmOut[i] != INVALID_VALUE_UINT32)
        {
            if (m_lpAlarmInV40->struAlarmHandleType.dwRelAlarmOut[i] < MAX_ALARMOUT_V40)
            {
                m_pbAlarmOut[m_lpAlarmInV40->struAlarmHandleType.dwRelAlarmOut[i]] = TRUE;
            }
        }
        else
        {
            break;
        }
	}
	
	for (i=0; i< MAX_CHANNUM_V40; i++)
	{
        if (m_lpAlarmInV40->dwRelRecordChan[i] != INVALID_VALUE_UINT32)
        {
            if((m_lpAlarmInV40->dwRelRecordChan[i] > 0 ) && (m_lpAlarmInV40->dwRelRecordChan[i] <= MAX_CHANNUM_V40))
            {
                m_pbRecordChan[m_lpAlarmInV40->dwRelRecordChan[i] - 1] = TRUE;
            }
        }
        else
        {
            break;
        }
	}


	m_comboWeekday.SetCurSel(0);
	m_comboCopyTime.SetCurSel(0);
	m_iHour11 = m_lpAlarmInV40->struAlarmTime[0][0].byStartHour;
	m_iMin11 = m_lpAlarmInV40->struAlarmTime[0][0].byStartMin;
	m_iHour12 = m_lpAlarmInV40->struAlarmTime[0][0].byStopHour;
	m_iMin12 = m_lpAlarmInV40->struAlarmTime[0][0].byStopMin;
	m_iHour21 = m_lpAlarmInV40->struAlarmTime[0][1].byStartHour;
	m_iMin21 = m_lpAlarmInV40->struAlarmTime[0][1].byStartMin;
	m_iHour22 = m_lpAlarmInV40->struAlarmTime[0][1].byStopHour;
	m_iMin22 = m_lpAlarmInV40->struAlarmTime[0][1].byStopMin;
	m_iHour31 = m_lpAlarmInV40->struAlarmTime[0][2].byStartHour;
	m_iMin31 = m_lpAlarmInV40->struAlarmTime[0][2].byStartMin;
	m_iHour32 = m_lpAlarmInV40->struAlarmTime[0][2].byStopHour;
	m_iMin32 = m_lpAlarmInV40->struAlarmTime[0][2].byStopMin;
	m_iHour41 = m_lpAlarmInV40->struAlarmTime[0][3].byStartHour;
	m_iMin41 = m_lpAlarmInV40->struAlarmTime[0][3].byStartMin;
	m_iHour42 = m_lpAlarmInV40->struAlarmTime[0][3].byStopHour;
	m_iMin42 = m_lpAlarmInV40->struAlarmTime[0][3].byStopMin;
	m_iHour51 = m_lpAlarmInV40->struAlarmTime[0][4].byStartHour;
	m_iMin51 = m_lpAlarmInV40->struAlarmTime[0][4].byStartMin;
	m_iHour52 = m_lpAlarmInV40->struAlarmTime[0][4].byStopHour;
	m_iMin52 = m_lpAlarmInV40->struAlarmTime[0][4].byStopMin;
	m_iHour61 = m_lpAlarmInV40->struAlarmTime[0][5].byStartHour;
	m_iMin61 = m_lpAlarmInV40->struAlarmTime[0][5].byStartMin;
	m_iHour62 = m_lpAlarmInV40->struAlarmTime[0][5].byStopHour;
	m_iMin62 = m_lpAlarmInV40->struAlarmTime[0][5].byStopMin;
	m_iHour71 = m_lpAlarmInV40->struAlarmTime[0][6].byStartHour;
	m_iMin71 = m_lpAlarmInV40->struAlarmTime[0][6].byStartMin;
	m_iHour72 = m_lpAlarmInV40->struAlarmTime[0][6].byStopHour;
	m_iMin72 = m_lpAlarmInV40->struAlarmTime[0][6].byStopMin;
	m_iHour81 = m_lpAlarmInV40->struAlarmTime[0][7].byStartHour;
	m_iMin81 = m_lpAlarmInV40->struAlarmTime[0][7].byStartMin;
	m_iHour82 = m_lpAlarmInV40->struAlarmTime[0][7].byStopHour;
	m_iMin82 = m_lpAlarmInV40->struAlarmTime[0][7].byStopMin;
	GetDlgItem(IDC_BTN_ALARMIN_OK)->EnableWindow(TRUE);
	UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/*********************************************************
  Function:	OnBnClickedBtnAlarmInTimeOk
  Desc:		check and update alarm in time
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
    if (7 == i)
    {
        m_struHolidayHandle.struAlarmTime[0].byStartHour = (BYTE)m_iHour11;
        m_struHolidayHandle.struAlarmTime[0].byStartMin = (BYTE)m_iMin11;
        m_struHolidayHandle.struAlarmTime[0].byStopHour = (BYTE)m_iHour12;
        m_struHolidayHandle.struAlarmTime[0].byStopMin = (BYTE)m_iMin12;
        m_struHolidayHandle.struAlarmTime[1].byStartHour = (BYTE)m_iHour21;
        m_struHolidayHandle.struAlarmTime[1].byStartMin = (BYTE)m_iMin21;
        m_struHolidayHandle.struAlarmTime[1].byStopHour = (BYTE)m_iHour22;
        m_struHolidayHandle.struAlarmTime[1].byStopMin = (BYTE)m_iMin22;
        m_struHolidayHandle.struAlarmTime[2].byStartHour = (BYTE)m_iHour31;
        m_struHolidayHandle.struAlarmTime[2].byStartMin = (BYTE)m_iMin31;
        m_struHolidayHandle.struAlarmTime[2].byStopHour = (BYTE)m_iHour32;
        m_struHolidayHandle.struAlarmTime[2].byStopMin = (BYTE)m_iMin32;
        m_struHolidayHandle.struAlarmTime[3].byStartHour = (BYTE)m_iHour41;
        m_struHolidayHandle.struAlarmTime[3].byStartMin = (BYTE)m_iMin41;
        m_struHolidayHandle.struAlarmTime[3].byStopHour = (BYTE)m_iHour42;
        m_struHolidayHandle.struAlarmTime[3].byStopMin = (BYTE)m_iMin42;
        m_struHolidayHandle.struAlarmTime[4].byStartHour = (BYTE)m_iHour51;
        m_struHolidayHandle.struAlarmTime[4].byStartMin = (BYTE)m_iMin51;
        m_struHolidayHandle.struAlarmTime[4].byStopHour = (BYTE)m_iHour52;
        m_struHolidayHandle.struAlarmTime[4].byStopMin = (BYTE)m_iMin52;
        m_struHolidayHandle.struAlarmTime[5].byStartHour = (BYTE)m_iHour61;
        m_struHolidayHandle.struAlarmTime[5].byStartMin = (BYTE)m_iMin61;
        m_struHolidayHandle.struAlarmTime[5].byStopHour = (BYTE)m_iHour62;
        m_struHolidayHandle.struAlarmTime[5].byStopMin = (BYTE)m_iMin62;
        m_struHolidayHandle.struAlarmTime[6].byStartHour = (BYTE)m_iHour71;
        m_struHolidayHandle.struAlarmTime[6].byStartMin = (BYTE)m_iMin71;
        m_struHolidayHandle.struAlarmTime[6].byStopHour = (BYTE)m_iHour72;
        m_struHolidayHandle.struAlarmTime[6].byStopMin = (BYTE)m_iMin72;
        m_struHolidayHandle.struAlarmTime[7].byStartHour = (BYTE)m_iHour81;
        m_struHolidayHandle.struAlarmTime[7].byStartMin = (BYTE)m_iMin81;
        m_struHolidayHandle.struAlarmTime[7].byStopHour = (BYTE)m_iHour82;
        m_struHolidayHandle.struAlarmTime[7].byStopMin = (BYTE)m_iMin82;

        if (m_bSetHolidayCfg)
        {
            if (!SetAlarmInHolidayHandle(m_struHolidayHandle))
            {
                AfxMessageBox("Fail to set holiday handle");
            }
        }
    }
    else
    {
        m_lpAlarmInV40->struAlarmTime[i][0].byStartHour = (BYTE)m_iHour11;
        m_lpAlarmInV40->struAlarmTime[i][0].byStartMin = (BYTE)m_iMin11;
        m_lpAlarmInV40->struAlarmTime[i][0].byStopHour = (BYTE)m_iHour12;
        m_lpAlarmInV40->struAlarmTime[i][0].byStopMin = (BYTE)m_iMin12;
        m_lpAlarmInV40->struAlarmTime[i][1].byStartHour = (BYTE)m_iHour21;
        m_lpAlarmInV40->struAlarmTime[i][1].byStartMin = (BYTE)m_iMin21;
        m_lpAlarmInV40->struAlarmTime[i][1].byStopHour = (BYTE)m_iHour22;
        m_lpAlarmInV40->struAlarmTime[i][1].byStopMin = (BYTE)m_iMin22;
        m_lpAlarmInV40->struAlarmTime[i][2].byStartHour = (BYTE)m_iHour31;
        m_lpAlarmInV40->struAlarmTime[i][2].byStartMin = (BYTE)m_iMin31;
        m_lpAlarmInV40->struAlarmTime[i][2].byStopHour = (BYTE)m_iHour32;
        m_lpAlarmInV40->struAlarmTime[i][2].byStopMin = (BYTE)m_iMin32;
        m_lpAlarmInV40->struAlarmTime[i][3].byStartHour = (BYTE)m_iHour41;
        m_lpAlarmInV40->struAlarmTime[i][3].byStartMin = (BYTE)m_iMin41;
        m_lpAlarmInV40->struAlarmTime[i][3].byStopHour = (BYTE)m_iHour42;
        m_lpAlarmInV40->struAlarmTime[i][3].byStopMin = (BYTE)m_iMin42;
        m_lpAlarmInV40->struAlarmTime[i][4].byStartHour = (BYTE)m_iHour51;
        m_lpAlarmInV40->struAlarmTime[i][4].byStartMin = (BYTE)m_iMin51;
        m_lpAlarmInV40->struAlarmTime[i][4].byStopHour = (BYTE)m_iHour52;
        m_lpAlarmInV40->struAlarmTime[i][4].byStopMin = (BYTE)m_iMin52;
        m_lpAlarmInV40->struAlarmTime[i][5].byStartHour = (BYTE)m_iHour61;
        m_lpAlarmInV40->struAlarmTime[i][5].byStartMin = (BYTE)m_iMin61;
        m_lpAlarmInV40->struAlarmTime[i][5].byStopHour = (BYTE)m_iHour62;
        m_lpAlarmInV40->struAlarmTime[i][5].byStopMin = (BYTE)m_iMin62;
        m_lpAlarmInV40->struAlarmTime[i][6].byStartHour = (BYTE)m_iHour71;
        m_lpAlarmInV40->struAlarmTime[i][6].byStartMin = (BYTE)m_iMin71;
        m_lpAlarmInV40->struAlarmTime[i][6].byStopHour = (BYTE)m_iHour72;
        m_lpAlarmInV40->struAlarmTime[i][6].byStopMin = (BYTE)m_iMin72;
        m_lpAlarmInV40->struAlarmTime[i][7].byStartHour = (BYTE)m_iHour81;
        m_lpAlarmInV40->struAlarmTime[i][7].byStartMin = (BYTE)m_iMin81;
        m_lpAlarmInV40->struAlarmTime[i][7].byStopHour = (BYTE)m_iHour82;
        m_lpAlarmInV40->struAlarmTime[i][7].byStopMin = (BYTE)m_iMin82;
    }

	GetDlgItem(IDC_BTN_ALARMIN_TIME_COPY)->EnableWindow(TRUE);
}

/*********************************************************
  Function:	OnCbnSelchangeComboAlarminWeekday
  Desc:		select a date and update the timetable
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteAlarmInHandle::OnCbnSelchangeComboAlarminWeekday()
{
	UpdateData(TRUE);
	
	int	i = m_comboWeekday.GetCurSel();	
    if (7 == i)
    {
        m_iHour11 = m_struHolidayHandle.struAlarmTime[0].byStartHour;
        m_iMin11 = m_struHolidayHandle.struAlarmTime[0].byStartMin;
        m_iHour12 = m_struHolidayHandle.struAlarmTime[0].byStopHour;
        m_iMin12 = m_struHolidayHandle.struAlarmTime[0].byStopMin;
        m_iHour21 = m_struHolidayHandle.struAlarmTime[1].byStartHour;
        m_iMin21 = m_struHolidayHandle.struAlarmTime[1].byStartMin;
        m_iHour22 = m_struHolidayHandle.struAlarmTime[1].byStopHour;
        m_iMin22 = m_struHolidayHandle.struAlarmTime[1].byStopMin;
        m_iHour31 = m_struHolidayHandle.struAlarmTime[2].byStartHour;
        m_iMin31 = m_struHolidayHandle.struAlarmTime[2].byStartMin;
        m_iHour32 = m_struHolidayHandle.struAlarmTime[2].byStopHour;
        m_iMin32 = m_struHolidayHandle.struAlarmTime[2].byStopMin;
        m_iHour41 = m_struHolidayHandle.struAlarmTime[3].byStartHour;
        m_iMin41 = m_struHolidayHandle.struAlarmTime[3].byStartMin;
        m_iHour42 = m_struHolidayHandle.struAlarmTime[3].byStopHour;
        m_iMin42 = m_struHolidayHandle.struAlarmTime[3].byStopMin;
        m_iHour51 = m_struHolidayHandle.struAlarmTime[4].byStartHour;
        m_iMin51 = m_struHolidayHandle.struAlarmTime[4].byStartMin;
        m_iHour52 = m_struHolidayHandle.struAlarmTime[4].byStopHour;
        m_iMin52 = m_struHolidayHandle.struAlarmTime[4].byStopMin;
        m_iHour61 = m_struHolidayHandle.struAlarmTime[5].byStartHour;
        m_iMin61 = m_struHolidayHandle.struAlarmTime[5].byStartMin;
        m_iHour62 = m_struHolidayHandle.struAlarmTime[5].byStopHour;
        m_iMin62 = m_struHolidayHandle.struAlarmTime[5].byStopMin;
        m_iHour71 = m_struHolidayHandle.struAlarmTime[6].byStartHour;
        m_iMin71 = m_struHolidayHandle.struAlarmTime[6].byStartMin;
        m_iHour72 = m_struHolidayHandle.struAlarmTime[6].byStopHour;
        m_iMin72 = m_struHolidayHandle.struAlarmTime[6].byStopMin;
        m_iHour81 = m_struHolidayHandle.struAlarmTime[7].byStartHour;
        m_iMin81 = m_struHolidayHandle.struAlarmTime[7].byStartMin;
        m_iHour82 = m_struHolidayHandle.struAlarmTime[7].byStopHour;
        m_iMin82 = m_struHolidayHandle.struAlarmTime[7].byStopMin;
     }
    else
    {
	    m_iHour11 = m_lpAlarmInV40->struAlarmTime[i][0].byStartHour;
	    m_iMin11 = m_lpAlarmInV40->struAlarmTime[i][0].byStartMin;
	    m_iHour12 = m_lpAlarmInV40->struAlarmTime[i][0].byStopHour;
	    m_iMin12 = m_lpAlarmInV40->struAlarmTime[i][0].byStopMin;
	    m_iHour21 = m_lpAlarmInV40->struAlarmTime[i][1].byStartHour;
	    m_iMin21 = m_lpAlarmInV40->struAlarmTime[i][1].byStartMin;
	    m_iHour22 = m_lpAlarmInV40->struAlarmTime[i][1].byStopHour;
	    m_iMin22 = m_lpAlarmInV40->struAlarmTime[i][1].byStopMin;
	    m_iHour31 = m_lpAlarmInV40->struAlarmTime[i][2].byStartHour;
	    m_iMin31 = m_lpAlarmInV40->struAlarmTime[i][2].byStartMin;
	    m_iHour32 = m_lpAlarmInV40->struAlarmTime[i][2].byStopHour;
	    m_iMin32 = m_lpAlarmInV40->struAlarmTime[i][2].byStopMin;
	    m_iHour41 = m_lpAlarmInV40->struAlarmTime[i][3].byStartHour;
	    m_iMin41 = m_lpAlarmInV40->struAlarmTime[i][3].byStartMin;
	    m_iHour42 = m_lpAlarmInV40->struAlarmTime[i][3].byStopHour;
	    m_iMin42 = m_lpAlarmInV40->struAlarmTime[i][3].byStopMin;
	    m_iHour51 = m_lpAlarmInV40->struAlarmTime[i][4].byStartHour;
	    m_iMin51 = m_lpAlarmInV40->struAlarmTime[i][4].byStartMin;
	    m_iHour52 = m_lpAlarmInV40->struAlarmTime[i][4].byStopHour;
	    m_iMin52 = m_lpAlarmInV40->struAlarmTime[i][4].byStopMin;
	    m_iHour61 = m_lpAlarmInV40->struAlarmTime[i][5].byStartHour;
	    m_iMin61 = m_lpAlarmInV40->struAlarmTime[i][5].byStartMin;
	    m_iHour62 = m_lpAlarmInV40->struAlarmTime[i][5].byStopHour;
	    m_iMin62 = m_lpAlarmInV40->struAlarmTime[i][5].byStopMin;
	    m_iHour71 = m_lpAlarmInV40->struAlarmTime[i][6].byStartHour;
	    m_iMin71 = m_lpAlarmInV40->struAlarmTime[i][6].byStartMin;
	    m_iHour72 = m_lpAlarmInV40->struAlarmTime[i][6].byStopHour;
	    m_iMin72 = m_lpAlarmInV40->struAlarmTime[i][6].byStopMin;
	    m_iHour81 = m_lpAlarmInV40->struAlarmTime[i][7].byStartHour;
	    m_iMin81 = m_lpAlarmInV40->struAlarmTime[i][7].byStartMin;
	    m_iHour82 = m_lpAlarmInV40->struAlarmTime[i][7].byStopHour;
	    m_iMin82 = m_lpAlarmInV40->struAlarmTime[i][7].byStopMin;
    }
	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnBnClickedBtnAlarminTimeCopy
  Desc:		copy time schedule to certain date
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
				memcpy(&(m_lpAlarmInV40->struAlarmTime[j][k]), &(m_lpAlarmInV40->struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
			}
		}
	}
    else if (7 == m_nCopyTime)
    {
        for (k = 0; k < MAX_TIMESEGMENT_V30; k++)
        {
            memcpy(&m_struHolidayHandle.struAlarmTime[k], &(m_lpAlarmInV40->struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
        }
        if (!SetAlarmInHolidayHandle(m_struHolidayHandle))
        {
            AfxMessageBox("Fail to set holiday handle");
        }
    }
	else
	{
		for (k=0; k<MAX_TIMESEGMENT_V30; k++)
		{
			memcpy(&(m_lpAlarmInV40->struAlarmTime[m_nCopyTime][k]), &(m_lpAlarmInV40->struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
		}
	}
}

/*********************************************************
Function:	OnBnClickedBtnAlarminOk
Desc:		finish time setting and check the status on relative time schedule
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
	m_lpAlarmInV40->struAlarmTime[i][0].byStartHour = (BYTE)m_iHour11;
	m_lpAlarmInV40->struAlarmTime[i][0].byStartMin = (BYTE)m_iMin11;
	m_lpAlarmInV40->struAlarmTime[i][0].byStopHour = (BYTE)m_iHour12;
	m_lpAlarmInV40->struAlarmTime[i][0].byStopMin = (BYTE)m_iMin12;
	m_lpAlarmInV40->struAlarmTime[i][1].byStartHour = (BYTE)m_iHour21;
	m_lpAlarmInV40->struAlarmTime[i][1].byStartMin = (BYTE)m_iMin21;
	m_lpAlarmInV40->struAlarmTime[i][1].byStopHour = (BYTE)m_iHour22;
	m_lpAlarmInV40->struAlarmTime[i][1].byStopMin = (BYTE)m_iMin22;
	m_lpAlarmInV40->struAlarmTime[i][2].byStartHour = (BYTE)m_iHour31;
	m_lpAlarmInV40->struAlarmTime[i][2].byStartMin = (BYTE)m_iMin31;
	m_lpAlarmInV40->struAlarmTime[i][2].byStopHour = (BYTE)m_iHour32;
	m_lpAlarmInV40->struAlarmTime[i][2].byStopMin = (BYTE)m_iMin32;
	m_lpAlarmInV40->struAlarmTime[i][3].byStartHour = (BYTE)m_iHour41;
	m_lpAlarmInV40->struAlarmTime[i][3].byStartMin = (BYTE)m_iMin41;
	m_lpAlarmInV40->struAlarmTime[i][3].byStopHour = (BYTE)m_iHour42;
	m_lpAlarmInV40->struAlarmTime[i][3].byStopMin = (BYTE)m_iMin42;

	m_lpAlarmInV40->struAlarmTime[i][4].byStartHour = (BYTE)m_iHour51;
	m_lpAlarmInV40->struAlarmTime[i][4].byStartMin = (BYTE)m_iMin51;
	m_lpAlarmInV40->struAlarmTime[i][4].byStopHour = (BYTE)m_iHour52;
	m_lpAlarmInV40->struAlarmTime[i][4].byStopMin = (BYTE)m_iMin52;
	m_lpAlarmInV40->struAlarmTime[i][5].byStartHour = (BYTE)m_iHour61;
	m_lpAlarmInV40->struAlarmTime[i][5].byStartMin = (BYTE)m_iMin61;
	m_lpAlarmInV40->struAlarmTime[i][5].byStopHour = (BYTE)m_iHour62;
	m_lpAlarmInV40->struAlarmTime[i][5].byStopMin = (BYTE)m_iMin62;
	m_lpAlarmInV40->struAlarmTime[i][6].byStartHour = (BYTE)m_iHour71;
	m_lpAlarmInV40->struAlarmTime[i][6].byStartMin = (BYTE)m_iMin71;
	m_lpAlarmInV40->struAlarmTime[i][6].byStopHour = (BYTE)m_iHour72;
	m_lpAlarmInV40->struAlarmTime[i][6].byStopMin = (BYTE)m_iMin72;
	m_lpAlarmInV40->struAlarmTime[i][7].byStartHour = (BYTE)m_iHour81;
	m_lpAlarmInV40->struAlarmTime[i][7].byStartMin = (BYTE)m_iMin81;
	m_lpAlarmInV40->struAlarmTime[i][7].byStopHour = (BYTE)m_iHour82;
	m_lpAlarmInV40->struAlarmTime[i][7].byStopMin = (BYTE)m_iMin82;
 
	memset(m_lpAlarmInV40->struAlarmHandleType.dwRelAlarmOut, INVALID_VALUE_UINT32, MAX_ALARMOUT_V40);
	DWORD dwCurSign = 0;
	
	DWORD dwVaildItem = 0;
	DWORD dwItem = 0; 
	HTREEITEM  treeItem = m_treeAlarmOut.GetRootItem(); 
	while (treeItem != NULL)
	{
		BOOL bCheck = m_treeAlarmOut.GetCheck(treeItem);
		if (bCheck)
		{
			m_lpAlarmInV40->struAlarmHandleType.dwRelAlarmOut[dwVaildItem++] = dwItem;
		}
		dwItem ++; 
		treeItem = m_treeAlarmOut.GetNextSiblingItem(treeItem); 
	}
//     for (i=0; i<MAX_ALARMOUT_V40; i++)
//     {
//         if (m_pbAlarmOut[i])
//         {
//             m_lpAlarmInV40->struAlarmHandleType.dwRelAlarmOut[dwCurSign++] = i;
//         }        
//     }

	m_lpAlarmInV40->struAlarmHandleType.dwHandleType = 0;
	m_lpAlarmInV40->struAlarmHandleType.dwHandleType |= (m_bChkMonitorAlarm << 0);
	m_lpAlarmInV40->struAlarmHandleType.dwHandleType |= (m_bChkVoiceAlarm << 1);
	m_lpAlarmInV40->struAlarmHandleType.dwHandleType |= (m_bChkUploadCenter << 2);
	m_lpAlarmInV40->struAlarmHandleType.dwHandleType |= (m_bChkInvokeAlarmOut << 3);
	m_lpAlarmInV40->struAlarmHandleType.dwHandleType |= (m_bChkInvokeJpegCapture << 4);
	m_lpAlarmInV40->struAlarmHandleType.dwHandleType |= (m_bChkEmapAlarmOut<<6);
	m_lpAlarmInV40->struAlarmHandleType.dwHandleType |= (m_bChkPicToFtp << 9);	
    m_lpAlarmInV40->struAlarmHandleType.dwHandleType |= (m_bChkPicToCloud << 12);
	m_lpAlarmInV40->struAlarmHandleType.dwHandleType |= (m_bChkSmsAlarm << 13);

	memset(m_lpAlarmInV40->dwRelRecordChan, INVALID_VALUE_UINT32, MAX_CHANNUM_V40);
    dwCurSign = 0;
    for (i=0; i<MAX_CHANNUM_V40; i++)
    {
        if (m_pbRecordChan[i])
        {
            m_lpAlarmInV40->dwRelRecordChan[dwCurSign++] = i+1;
        }        
    }

	CDialog::OnOK();
}

/*********************************************************
  Function:	OnBnClickedBtnAlarminExit
  Desc:		cancel alarm in settings
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
  Desc:		enable alarm output
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
  Desc:		check time
  Input:	
  Output:	
  Return:	TRUE,correct time schedule;FALSE,incorrect time schedule;
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
  Desc:		establish alarm out - video connection
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

	int iChanShow = 0;

	for (i = 0; i < g_struDeviceInfo[m_dwDevIndex].iDeviceChanNum; i++)
	{
		iChanShow = g_struDeviceInfo[m_dwDevIndex].pStruChanInfo[i].iChannelNO;

		if ((i < m_iAnaChanCount) && g_struDeviceInfo[m_dwDevIndex].pStruChanInfo[i].bEnable)
		{
			strTemp.Format(ANALOG_C_FORMAT, iChanShow);
			hChanItem =  m_treeChan.InsertItem(strTemp, 0, 0, TVI_ROOT);
			m_treeChan.SetItemData(hChanItem, 0*1000 + i);	
			if (m_pbRecordChan[iChanShow -1])
			{
				m_treeChan.SetCheck(hChanItem, TRUE);
			}
		}
		else if (i >= m_iAnaChanCount && g_struDeviceInfo[m_dwDevIndex].pStruChanInfo[i].bEnable)
		{
			strTemp.Format(DIGITAL_C_FORMAT, iChanShow - m_iDStartChannel + 1);
			hChanItem =  m_treeChan.InsertItem(strTemp, 0, 0, TVI_ROOT);
			m_treeChan.SetItemData(hChanItem, 1*1000 + i);	
			if (m_pbRecordChan[iChanShow - 1])
			{
				m_treeChan.SetCheck(hChanItem, TRUE);
			}
		}
	}
	m_treeChan.SelectItem(hChanItem);
	m_treeChan.Expand(m_treeChan.GetRootItem(),TVE_EXPAND);	

	g_CreateAlarmOutTree(m_treeAlarmOut, m_dwDevIndex, m_pbAlarmOut);
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
	m_pbRecordChan[dwIndex] = !bCheck;
	//switch checkbox status on click
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
	m_pbAlarmOut[dwIndex] = !bCheck;
	//switch checkbox status on click
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
	CDialog::OnPaint();
	// Do not call CDialog::OnPaint() for painting messages
}

BOOL CDlgRemoteAlarmInHandle::GetAlarmInHolidayHandle(NET_DVR_HOLIDAY_HANDLE &struHolidayHandle)
{
    DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_ALARMIN_HOLIDAY_HANDLE, m_lAlarmInIndex, &struHolidayHandle, sizeof(struHolidayHandle), &dwReturn))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARMIN_HOLIDAY_HANDLE");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMIN_HOLIDAY_HANDLE");
        return FALSE;
    }
}

BOOL CDlgRemoteAlarmInHandle::SetAlarmInHolidayHandle(NET_DVR_HOLIDAY_HANDLE &struHolidayHandle)
{
    DWORD dwReturn = 0;
    if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_ALARMIN_HOLIDAY_HANDLE, m_lAlarmInIndex, &struHolidayHandle, sizeof(struHolidayHandle)))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_ALARMIN_HOLIDAY_HANDLE");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_ALARMIN_HOLIDAY_HANDLE");
        return FALSE;
    }
}


void CDlgRemoteAlarmInHandle::OnBtnRecordchanAll() 
{
	// TODO: Add your control notification handler code here
    CString struAlarmOutText = "";
    BOOL bSetAll = FALSE;
    int  i = 0;
    GetDlgItem(IDC_BTN_RECORDCHAN_ALL)->GetWindowText(struAlarmOutText);
    if (struAlarmOutText.Find("全选") != -1)
    {
        GetDlgItem(IDC_BTN_RECORDCHAN_ALL)->SetWindowText("全不选");
        
        for (i = 0; i < MAX_CHANNUM_V40; i++)
        {
            if ((i <  g_struDeviceInfo[m_dwDevIndex].iDeviceChanNum) && g_struDeviceInfo[m_dwDevIndex].pStruChanInfo[i].bEnable)
            {
                m_pbRecordChan[i] = 1;
            }
            else if (i >= MAX_ANALOG_CHANNUM && g_struDeviceInfo[m_dwDevIndex].pStruChanInfo[i].bEnable)
            {
                m_pbRecordChan[i] = 1;
            }
        }
        
    }
    else   
    {
        GetDlgItem(IDC_BTN_RECORDCHAN_ALL)->SetWindowText("全选");
        for (i = 0; i < MAX_CHANNUM_V40; i++)
        {
            m_pbRecordChan[i] = 0;
        }
    }
    
    CreateTree();
}

void CDlgRemoteAlarmInHandle::OnBtnAlarmoutAll() 
{
	// TODO: Add your control notification handler code here
    
    CString struAlarmOutText = "";
    DWORD dwID = 0;
    char szLan[1024] = {0};
    char szLanCn[1024] = {0};
    char szLanEn[1024] = {0};

    GetDlgItem(IDC_BTN_ALARMOUT_ALL)->GetWindowText(struAlarmOutText);
    if ((struAlarmOutText.Find("全选") != -1) || (struAlarmOutText.Find("Sel All") != -1))
    {
        memcpy(szLanCn,"全不选",strlen("全不选"));
        memcpy(szLanEn,"Uncheck All",strlen("Uncheck All"));        
        g_StringLanType(szLan, szLanCn, szLanEn);

        for (int i  = 0; i < MAX_ALARMOUT_V40 ; i++ )
        {
            if ((i <  g_struDeviceInfo[m_dwDevIndex].iAlarmOutNum))
            {                
                m_pbAlarmOut[i] = 1;
            }
            else if (i >= MAX_ANALOG_ALARMOUT)
            {
                dwID = g_struDeviceInfo[m_dwDevIndex].pStruIPAlarmOutCfgV40->struIPAlarmOutInfo[i-MAX_ANALOG_ALARMOUT].dwIPID;
                if (dwID != 0)
                {
                    m_pbAlarmOut[i] = 1;
                }
                
            }
            
        }     
    }
    else   
    {
        memcpy(szLanCn,"全选",strlen("全选"));
        memcpy(szLanEn,"Sel All",strlen("Sel All"));        
        g_StringLanType(szLan, szLanCn, szLanEn);

        for (int i  = 0; i < MAX_ALARMOUT_V40 ; i++ )
        {
            m_pbAlarmOut[i] = 0;
        }
    }    
         GetDlgItem(IDC_BTN_ALARMOUT_ALL)->SetWindowText(szLan);
	CreateTree();
}