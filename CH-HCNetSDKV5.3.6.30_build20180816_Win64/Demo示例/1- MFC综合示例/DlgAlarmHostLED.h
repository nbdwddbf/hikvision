#if !defined(AFX_DLGALARMHOSTLED_H__2FA2FFFD_CB4F_495C_B944_426CEE769770__INCLUDED_)
#define AFX_DLGALARMHOSTLED_H__2FA2FFFD_CB4F_495C_B944_426CEE769770__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmHostLED.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostLED dialog

class CDlgAlarmHostLED : public CDialog
{
// Construction
public:
	CDlgAlarmHostLED(CWnd* pParent = NULL);   // standard constructor
	char	m_szTemp[128];
	int		m_iDeviceIndex;
	long	m_lUserID;
	NET_DVR_LED_SCREEN_CFG m_struLEDCfg;
	NET_DVR_LED_CONTENT_CFG m_struLEDContent;
	NET_DVR_TIME_EX m_struCheckTime;
	NET_DVR_LED_STATUS m_struLEDStatus;
	NET_DVR_CONTROL_PARAM m_struCtrlParam;
	BOOL CheckAndGetTime();
	void GetTime(INT iTimeIndex);
// Dialog Data
	//{{AFX_DATA(CDlgAlarmHostLED)
	enum { IDD = IDD_DLG_ALARMHOST_LED };
	CComboBox	m_cmOEPolarity;
	CComboBox	m_cmLEDWidth;
	CComboBox	m_cmTranseMode;
	CComboBox	m_cmScanType;
	CComboBox	m_cmProtocolType;
	CComboBox	m_cmLEDHeight;
	CComboBox	m_cmLEDColor;
	CComboBox	m_cmDataPolarity;
	CComboBox	m_cmContentStayTime;
	CComboBox	m_cmContentSpeed;
	CComboBox	m_cmContentAct;
	CString	m_csLEDContent;
	CString	m_csLEDName;
	COleDateTime	m_checkTimeDay;
	COleDateTime	m_checkTimeTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmHostLED)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmHostLED)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGetLedparam();
	afx_msg void OnBtnSetLedparam();
	afx_msg void OnBtnGetLedcontent();
	afx_msg void OnBtnSetLedcontent();
	afx_msg void OnBtnLedTurnon();
	afx_msg void OnBtnLedTurnoff();
	afx_msg void OnBtnChecktime();
	afx_msg void OnBtnLedBrightness();
	afx_msg void OnBtnTimerSwitch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMHOSTLED_H__2FA2FFFD_CB4F_495C_B944_426CEE769770__INCLUDED_)
