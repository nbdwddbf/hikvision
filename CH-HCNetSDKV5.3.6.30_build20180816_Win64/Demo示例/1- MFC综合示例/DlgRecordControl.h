#if !defined(AFX_DLGRECORDCONTROL_H__ED30BFD5_53C2_4595_9A15_EE48361E19D1__INCLUDED_)
#define AFX_DLGRECORDCONTROL_H__ED30BFD5_53C2_4595_9A15_EE48361E19D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRecordControl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgRecordControl dialog

class DlgRecordControl : public CDialog
{
// Construction
public:
	DlgRecordControl(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgRecordControl)
	enum { IDD = IDD_DLG_RECORD_HOST_CONTROL };
	CComboBox	m_byCmdType;
	CComboBox	m_comCmdType;
	UINT	m_nDelayTime;
	UINT	m_nCourseIndex;
	BOOL	m_bStartDefine;
	BOOL	m_bDelayDefine;
	CString	m_byCourseName;
	CString	m_byCourseDescription;
	CString	m_byInstructorName;
	CString	m_byRecUUID;
	//}}AFX_DATA

	LONG m_lUserID;
	int m_iDeviceIndex;
	int m_iMirrorNum;
	int m_iStartChannel;

	NET_DVR_RECORDING_CONTROL_CFG m_struRecordControlCfg;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgRecordControl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	BOOL OnInitDialog();
	// Generated message map functions
	//{{AFX_MSG(DlgRecordControl)
	afx_msg void OnBtnSet();
	afx_msg void OnSelchangeComCmdType();
	afx_msg void OnBtnOk();
	afx_msg void OnButtonManualControl();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRECORDCONTROL_H__ED30BFD5_53C2_4595_9A15_EE48361E19D1__INCLUDED_)
