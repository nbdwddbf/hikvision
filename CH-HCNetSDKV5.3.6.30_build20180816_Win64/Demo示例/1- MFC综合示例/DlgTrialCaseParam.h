#if !defined(AFX_DLGTRIALCASEPARAM_H__D2B1F94F_69D2_4366_B98F_7BAEE5B23F64__INCLUDED_)
#define AFX_DLGTRIALCASEPARAM_H__D2B1F94F_69D2_4366_B98F_7BAEE5B23F64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTrialCaseParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTrialCaseParam dialog

class CDlgTrialCaseParam : public CDialog
{
// Construction
public:
	CDlgTrialCaseParam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTrialCaseParam)
	enum { IDD = IDD_DLG_TRIAL_CASE_PARAM };
	CComboBox	m_comboCaseType;
	CString	m_sCaseLitigant1;
	CString	m_sCaseLitigant2;
	CString	m_sCaseName;
	CString	m_sCaseNo;
	CString	m_sChiefJudge;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTrialCaseParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTrialCaseParam)
	afx_msg void OnBtnOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRIALCASEPARAM_H__D2B1F94F_69D2_4366_B98F_7BAEE5B23F64__INCLUDED_)
