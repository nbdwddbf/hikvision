#pragma once


// CDlgRemoteAlarmInHandle dialog

class CDlgRemoteAlarmInHandle : public CDialog
{
	DECLARE_DYNAMIC(CDlgRemoteAlarmInHandle)

public:
	CDlgRemoteAlarmInHandle(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgRemoteAlarmInHandle();

// Dialog Data



public:
	//{{AFX_DATA(CDlgRemoteAlarmInHandle)
	enum { IDD = IDD_DLG_REMOTE_ALARM_IN_HANDLE };
	CTreeCtrl	m_treeAlarmOut;
	CTreeCtrl	m_treeChan;
	CComboBox	m_comboWeekday;
	CComboBox	m_comboCopyTime;
	BOOL	m_bChkMonitorAlarm;
	BOOL	m_bChkVoiceAlarm;
	BOOL	m_bChkUploadCenter;
	BOOL	m_bChkInvokeAlarmOut;
	BOOL	m_bChkInvokeJpegCapture;
	BOOL	m_bChkEmapAlarmOut;
	int m_iHour11;
	int m_iMin11;
	int m_iHour12;
	int m_iMin12;
	int m_iHour21;
	int m_iMin21;
	int m_iHour22;
	int m_iMin22;
	int m_iHour31;
	int m_iMin31;
	int m_iHour32;
	int m_iMin32;
	int m_iHour41;
	int m_iMin41;
	int m_iHour42;
	int m_iMin42;
	int m_iHour51;
	int m_iMin51;
	int m_iHour52;
	int m_iMin52;
	int m_iHour61;
	int m_iMin61;
	int m_iHour62;
	int m_iMin62;
	int m_iHour71;
	int m_iMin71;
	int m_iHour72;
	int m_iMin72;
	int m_iHour81;
	int m_iMin81;
	int m_iHour82;
	int m_iMin82;
	BOOL	m_bChkPicToFtp;
    BOOL	m_bChkPicToCloud;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CDlgRemoteAlarmInHandle)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteAlarmInHandle)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnAlarmInTimeOk();
	afx_msg void OnCbnSelchangeComboAlarminWeekday();
	afx_msg void OnBnClickedBtnAlarminTimeCopy();
	afx_msg void OnBnClickedBtnAlarminOk();
	afx_msg void OnBnClickedBtnAlarminExit();
	afx_msg void OnBnClickedChkAlarminInvokeAlarmout();
	afx_msg void OnClickTreeChan(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg void OnBtnRecordchanAll();
	afx_msg void OnBtnAlarmoutAll();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	//LPNET_DVR_ALARMINCFG_V30 m_lpAlarmIn;
	LOCAL_ALARMIN_HANDLE *m_lpAlarmInV40;
	//LPNET_DVR_ALARMINCFG_V40 m_lpAlarmInV40;
	//LPNET_DVR_ANALOG_ALARMINCFG m_lpAnalogAlarmIn;
	int		m_iChanCount;
	int		m_iAnaChanCount;
	int     m_iDStartChannel;
	LONG	m_lStartChannel;
	int m_iCopyTime;
	DWORD m_dwAlarmInNum;
	DWORD m_dwAnalogAlarmInNum;
	DWORD m_dwAlarmOutNum;
	BOOL TimeTest();
	void CreateTree();
	BOOL *m_pbAlarmOut;
	BOOL *m_pbRecordChan;

	DWORD m_dwDevIndex;
    LONG m_lServerID;
    LONG    m_lAlarmInIndex; 
	LONG	m_lAnalogAlarmInIndex;
    NET_DVR_HOLIDAY_HANDLE m_struHolidayHandle;
    BOOL   m_bSetHolidayCfg;
    int m_iPresetDurationTime;
    BOOL  GetAlarmInHolidayHandle(NET_DVR_HOLIDAY_HANDLE &struHolidayHandle);
    BOOL  SetAlarmInHolidayHandle(NET_DVR_HOLIDAY_HANDLE &struHolidayHandle);
    BOOL m_bChkSmsAlarm;
};
