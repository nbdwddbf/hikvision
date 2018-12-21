#if !defined(AFX_DLGALARMHOSTSUBSYSTEM_H__49E3EC22_7896_44F3_B077_2EAD9D73620E__INCLUDED_)
#define AFX_DLGALARMHOSTSUBSYSTEM_H__49E3EC22_7896_44F3_B077_2EAD9D73620E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmhostSubsystem.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmhostSubsystem dialog

class CDlgAlarmhostSubsystem : public CDialog
{
// Construction
public:
	CDlgAlarmhostSubsystem(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlarmhostSubsystem)
	enum { IDD = IDD_DLG_ALARMHOST_SUBSYSTEM };
	CComboBox	m_cmbRemindID;
	CComboBox	m_cmArmWeekdayCopy;
	CComboBox	m_cmArmWeekday;
	CListCtrl	m_listKeyBoardUser;
	CListCtrl	m_listSupportKeyBoardUser;
	CListCtrl	m_listJointSubsystem;
	CListCtrl	m_listBeJoinedSubSystem;
	CListCtrl	m_listSupportKeyboard;
	CListCtrl	m_listSupportKeyboardAddr;
	CListCtrl	m_listAssociateAlarmIn;
	CComboBox	m_cmSubSystem;
	short	m_wEnterDelay;
	short	m_wExitDelay;
	BOOL	m_chHostageReport;
	BOOL	m_chPublicSubSystem;
	BOOL	m_chSubSystem;
	BOOL	m_chToneOfArm;
	BOOL	m_chToneOfSendReport;
	COleDateTime	m_timeStart1;
	COleDateTime	m_timeStart2;
	COleDateTime	m_timeStart3;
	COleDateTime	m_timeStart4;
	COleDateTime	m_timeStop1;
	COleDateTime	m_timeStop2;
	COleDateTime	m_timeStop3;
	COleDateTime	m_timeStop4;
	COleDateTime	m_timeAlarmIn;
	BYTE	m_byAlarmInAdvance;
	DWORD	m_dwDelayTime;
	BOOL	m_chKeyZoneArm;
	BOOL	m_chKeyZoneDisarm;
	BOOL	m_chSendArmReport;
	BOOL	m_chSendDisarmReport;
	BOOL	m_bFri;
	BOOL	m_bMon;
	BOOL	m_bSta;
	BOOL	m_bSun;
	BOOL	m_bWen;
	BOOL	m_bEnableRemind;
	BOOL	m_bTus;
	BOOL	m_bThu;
	BOOL	m_bEnableAlarmInDelay;
	CString	m_csSubSystemID;
    CString m_csOperatorCode;
    DWORD   m_dwZoneIndex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmhostSubsystem)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_iDeviceIndex;
	LONG m_lUserID;
	NET_DVR_ALARMHOST_ABILITY m_struAlarmHostAbility;
	NET_DVR_ALARMSUBSYSTEMPARAM m_struSubSystem;
	NET_DVR_CONTROL_PARAM m_struCtrlParam;
	void InitListCtrl();
	void InitComboBox();
	NET_DVR_SUBSYSTEM_PARAM_EX m_struSubSystemEx;
	int m_iCurWeekdayIndex;
	void SetArmTimeToDlg();
	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmhostSubsystem)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnSubsystemSetup();
	afx_msg void OnBtnStopsetup();
	afx_msg void OnBtnClearalarm();
	afx_msg void OnBtnBypass();
	afx_msg void OnBtnResumeBypass();
	afx_msg void OnCheckPublicSubsystem();
	afx_msg void OnSelchangeComboArmWeek();
	afx_msg void OnButtonCopy();
	afx_msg void OnBtnSubsystemInmmediateArm();
	afx_msg void OnBtnSubsystemStayArm();
	afx_msg void OnSelchangeCmbRemindId();
	afx_msg void OnBtnSaveRemind();
    afx_msg void OnBnClickedBtnNetcardCfg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL m_chKeyZoneAlarmEnable;
	BOOL m_chKeyZoneReportEnable;
	BOOL m_chOneKeyAlarmEnable;
	BOOL m_chSingleZoneArmEnable;
	BOOL m_chMandatoryAlarm;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMHOSTSUBSYSTEM_H__49E3EC22_7896_44F3_B077_2EAD9D73620E__INCLUDED_)
