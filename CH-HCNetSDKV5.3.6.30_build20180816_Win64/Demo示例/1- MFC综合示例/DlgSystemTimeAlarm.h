#if !defined(AFX_DLGSYSTEMTIMEALARM_H__DF95E055_C236_448A_8FF3_ED55EDCA171E__INCLUDED_)
#define AFX_DLGSYSTEMTIMEALARM_H__DF95E055_C236_448A_8FF3_ED55EDCA171E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSystemTimeAlarm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgSystemTimeAlarm dialog

class DlgSystemTimeAlarm : public CDialog
{
// Construction
public:
	DlgSystemTimeAlarm(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgSystemTimeAlarm)
	enum { IDD = IDD_DLG_SUB_SYSTEM_ALARM };
	CListCtrl	m_listSystem;
	CComboBox	m_comPriorAlarmType8;
	CComboBox	m_comPriorAlarmType7;
	CComboBox	m_comPriorAlarmType6;
	CComboBox	m_comPriorAlarmType5;
	CComboBox	m_comPriorAlarmType3;
	CComboBox	m_comPriorAlarmType2;
	CComboBox	m_comPriorAlarmType4;
	CComboBox	m_comPriorAlarmType1;
	CComboBox	m_comNormalAlarmType8;
	CComboBox	m_comNormalAlarmType7;
	CComboBox	m_comNormalAlarmType6;
	CComboBox	m_comNormalAlarmType5;
	CComboBox	m_comNormalAlarmType4;
	CComboBox	m_comNormalAlarmType3;
	CComboBox	m_comNormalAlarmType2;
	CComboBox	m_comNormalAlarmType1;
	CComboBox	m_comPriorTime;
	CComboBox	m_comNormalTime;
	BOOL	m_bMandatoryAlarm;
	UINT	m_hour11;
	UINT	m_hour12;
	UINT	m_hour14;
	UINT	m_hour15;
	UINT	m_hour21;
	UINT	m_hour22;
	UINT	m_hour24;
	UINT	m_hour25;
	UINT	m_hour31;
	UINT	m_hour32;
	UINT	m_hour33;
	UINT	m_hour34;
	UINT	m_hour41;
	UINT	m_hour42;
	UINT	m_hour44;
	UINT	m_hour43;
	UINT	m_hour51;
	UINT	m_hour52;
	UINT	m_hour53;
	UINT	m_hour54;
	UINT	m_hour61;
	UINT	m_hour62;
	UINT	m_hour64;
	UINT	m_hour65;
	UINT	m_hour71;
	UINT	m_hour73;
	UINT	m_hour72;
	UINT	m_hour74;
	UINT	m_hour81;
	UINT	m_hour82;
	UINT	m_hour83;
	UINT	m_hour84;
	UINT	m_min11;
	UINT	m_min12;
	UINT	m_min13;
	UINT	m_min14;
	UINT	m_min21;
	UINT	m_min22;
	UINT	m_min23;
	UINT	m_min24;
	UINT	m_min31;
	UINT	m_min32;
	UINT	m_min34;
	UINT	m_min41;
	UINT	m_min33;
	UINT	m_min42;
	UINT	m_min43;
	UINT	m_min44;
	UINT	m_min51;
	UINT	m_min52;
	UINT	m_min53;
	UINT	m_min54;
	UINT	m_min61;
	UINT	m_min62;
	UINT	m_min63;
	UINT	m_min64;
	UINT	m_min71;
	UINT	m_min72;
	UINT	m_min73;
	UINT	m_min74;
	UINT	m_min81;
	UINT	m_min82;
	UINT	m_min83;
	UINT	m_min84;
	UINT	m_startDay;
	UINT	m_startMonth;
	UINT	m_endMonth;
	UINT	m_endDay;
	BOOL	m_bPriorScheduleOn;
	BOOL	m_bNormalSchedule;
	BOOL	m_bPriorMandatoryAlarm;
	UINT	m_subSystem;
	//}}AFX_DATA

	int m_iDevIndex;
	LONG m_lServerID;
	NET_DVR_SUBSYSTEM_ALARM m_sturSubsystemAlarm;
	NET_DVR_PRIOR_SCHEDTIME m_struPriorSchedAlarm;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgSystemTimeAlarm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	BOOL OnInitDialog();
	// Generated message map functions
	//{{AFX_MSG(DlgSystemTimeAlarm)
	afx_msg void OnSet();
	afx_msg void OnGet();
	afx_msg void OnBtnNormalOk();
	afx_msg void OnBtnPriorOk();
	afx_msg void OnSelendcancelComboPriorTime();
	afx_msg void OnSelchangeComboNoramlTime();
	afx_msg void OnChkPriorScheduleOn();
	afx_msg void OnChkNormalScheduleOn();
	afx_msg void OnPriorGet();
	afx_msg void OnPriorSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSYSTEMTIMEALARM_H__DF95E055_C236_448A_8FF3_ED55EDCA171E__INCLUDED_)
