#if !defined(AFX_DLGALARMHOSTEXTERNALMODULE_H__C27DD24D_04DA_4E80_B95F_2DFA88F80265__INCLUDED_)
#define AFX_DLGALARMHOSTEXTERNALMODULE_H__C27DD24D_04DA_4E80_B95F_2DFA88F80265__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmHostExternalModule.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostExternalModule dialog

class CDlgAlarmHostExternalModule : public CDialog
{
// Construction
public:
	CDlgAlarmHostExternalModule(CWnd* pParent = NULL);   // standard constructor
	int m_iDeviceIndex;
// Dialog Data
	//{{AFX_DATA(CDlgAlarmHostExternalModule)
	enum { IDD = IDD_DLG_ALARMHOST_EXTERN_MODULE };
	CProgressCtrl	m_progress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmHostExternalModule)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmHostExternalModule)
	afx_msg void OnBtnAutoSearch();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnRegister();
	afx_msg void OnBtnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	long m_lUserID;
	long m_lHandle;
	LRESULT OnGetProgress(WPARAM wParam, LPARAM lParam);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMHOSTEXTERNALMODULE_H__C27DD24D_04DA_4E80_B95F_2DFA88F80265__INCLUDED_)
