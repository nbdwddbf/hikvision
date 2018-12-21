#if !defined(AFX_DLGALARMHOSTEVENTTRIGGER_H__CB9A97D7_4BEE_40A9_936C_15D3ED39B8AD__INCLUDED_)
#define AFX_DLGALARMHOSTEVENTTRIGGER_H__CB9A97D7_4BEE_40A9_936C_15D3ED39B8AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmHostEventTrigger.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostEventTrigger dialog

class CDlgAlarmHostEventTrigger : public CDialog
{
// Construction
public:
	CDlgAlarmHostEventTrigger(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlarmHostEventTrigger)
	enum { IDD = IDD_DLG_ALARMHOST_EVENT_TRIGGER };
	CListCtrl	m_listSubsystemTriggerOn;
	CListCtrl	m_listSubsystemTriggerOff;
	CListCtrl	m_listOverallTriggerOff;
	CListCtrl	m_listOverallTriggerOn;
	CComboBox	m_cmSubsystem;
	CComboBox	m_cmAlarmout;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmHostEventTrigger)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmHostEventTrigger)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboSubsystem();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		int m_iDeviceIndex;
	long m_lUserID;
	NET_DVR_ALARMHOST_ABILITY m_struAlarmHostAbility;
	void InitSubSystemList();
	void InitOverallList();
	void InitComboBox() ;
	NET_DVR_TRIGGER_EVENT m_struEventTrigger;
	void GetEventInfoFromDlg();
	void SetEventInfoToDlg();
	int m_iCurSubSystemIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMHOSTEVENTTRIGGER_H__CB9A97D7_4BEE_40A9_936C_15D3ED39B8AD__INCLUDED_)
