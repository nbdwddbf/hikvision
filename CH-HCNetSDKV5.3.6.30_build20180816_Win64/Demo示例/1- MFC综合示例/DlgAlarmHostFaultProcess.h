#if !defined(AFX_DLGALARMHOSTFAULTPROCESS_H__C2EC4718_1ACD_4321_8C5C_67643C220116__INCLUDED_)
#define AFX_DLGALARMHOSTFAULTPROCESS_H__C2EC4718_1ACD_4321_8C5C_67643C220116__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmHostFaultProcess.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostFaultProcess dialog

class CDlgAlarmHostFaultProcess : public CDialog
{
// Construction
public:
	CDlgAlarmHostFaultProcess(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlarmHostFaultProcess)
	enum { IDD = IDD_DLG_ALARMHOST_FAULT_PROCESS };
	CListCtrl	m_listFaultLedLinkage;
	CListCtrl	m_listOverallFaultJointSound;
	CListCtrl	m_listOverallFaultJointLED;
	CComboBox	m_cmSubsystem;
	CListCtrl	m_listSubsystemFaultJointSound;
	CListCtrl	m_listSubsystemFaultJointLED;
	CListCtrl	m_listCheckFault;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmHostFaultProcess)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmHostFaultProcess)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnSelchangeComboSubsystem();
	afx_msg void OnBtnCloseOverallFaultSound();
	afx_msg void OnBtnCloseSubsystemFaultSound();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_iDeviceIndex;
	long m_lUserID;
	NET_DVR_ALARMHOST_ABILITY m_struAlarmHostAbility;
	void InitListWnd();
	void InitComboBox() ;
	NET_DVR_ALARMHOST_FAULT_CFG m_struFaultCfg;
	void GetFaultInfoFromDlg();
	void SetFaultInfoToDlg();
	int m_iCurSubSystemIndex;
	char m_szLan[128];
	NET_DVR_CONTROL_PARAM m_struCtrlParam;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMHOSTFAULTPROCESS_H__C2EC4718_1ACD_4321_8C5C_67643C220116__INCLUDED_)
