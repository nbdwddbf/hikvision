#if !defined(AFX_DLGREMOTEALARMDETECTFACE_H__16F05015_6B54_4BB6_9D91_88B8B4A8200C__INCLUDED_)
#define AFX_DLGREMOTEALARMDETECTFACE_H__16F05015_6B54_4BB6_9D91_88B8B4A8200C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRemoteAlarmDetectFace.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteAlarmDetectFace dialog

class CDlgRemoteAlarmDetectFace : public CDialog
{
// Construction
public:
	CDlgRemoteAlarmDetectFace(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRemoteAlarmDetectFace)
	enum { IDD = IDD_DLG_REMOTE_ALARM_DETECT_FACE };
	CComboBox	m_comboChannel;
	CComboBox	m_comDetectSensitive;
	CTreeCtrl	m_treeAlarmOut;
	CTreeCtrl	m_treeChan;
	BOOL	m_bChkEmapAlarmOut;
	BOOL	m_bChkInvokeAlarmOut;
	BOOL	m_bChkMonitorAlarm;
	BOOL	m_bChkUploadCenter;
	BOOL	m_bChkVoiceAlarm;
	BOOL	m_bChkInvokeJpegCapture;
	BOOL	m_bChkPicToFtp;
    BOOL	m_bChkPicToCloud;
	BOOL	m_bChkFaceDetect;
	BOOL	m_bChkEnableDisPlay;
	CComboBox	m_comboWeekday;
	CComboBox	m_comboCopyTime;
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
	UINT	m_nDuration;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRemoteAlarmDetectFace)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteAlarmDetectFace)
	afx_msg void OnBtnAlarmInTimeOk();
	afx_msg void OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnAlarminOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnClickTreeChan(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnAlarminTimeCopy();
	afx_msg void OnSelchangeComboAlarminWeekday();
	afx_msg void OnChkAlarminInvokeAlarmout();
	afx_msg void OnBtnAlarminUpload();
	afx_msg void OnBtnAlarminExit();
	afx_msg void OnPaint();
	afx_msg void OnSelchangeComboChannel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int		m_iChanCount;
	int		m_iAnaChanCount;
	int     m_iDStartChannel;
	LONG	m_lStartChannel;
	int     m_iCopyTime;
	DWORD   m_dwAlarmInNum;
	DWORD   m_dwAlarmOutNum;
	BOOL TimeTest();
	void CreateTree();
    BOOL	m_bAlarmOut[MAX_ALARMOUT_V40];
	BOOL	m_bRecordChan[MAX_CHANNUM_V30];
	DWORD   m_dwDevIndex;
    LONG    m_lServerID;
    LONG    m_lAlarmInIndex; 
	void ShowData();
	NET_DVR_DETECT_FACE  m_struDetectFaceCfg;
	NET_DVR_CHANNEL_GROUP m_struChannelGroup;

	NET_DVR_SCHEDTIME m_struAlarmTime[MAX_DAYS][MAX_TIMESEGMENT_V30]; 
	NET_DVR_SCHEDTIME m_struHolidayTime[MAX_TIMESEGMENT_V30];
	DWORD m_dwMaxRelAlarmOutNum;
	DWORD m_dwMaxRelRecordChanNum;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREMOTEALARMDETECTFACE_H__16F05015_6B54_4BB6_9D91_88B8B4A8200C__INCLUDED_)
