#if !defined(AFX_DLGITCABLITY_H__38B035CC_9BBE_45A0_871A_483E25B6E2C4__INCLUDED_)
#define AFX_DLGITCABLITY_H__38B035CC_9BBE_45A0_871A_483E25B6E2C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgITCAblity.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgITCAblity dialog

class CDlgITCAblity : public CDialog
{
// Construction
public:
	CDlgITCAblity(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgITCAblity)
	enum { IDD = IDD_DIG_ITCABLITY };
	CString	m_csITCAblity;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgITCAblity)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgITCAblity)
	afx_msg void OnBtnGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG m_lServerID;
	int m_iDeviceIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGITCABLITY_H__38B035CC_9BBE_45A0_871A_483E25B6E2C4__INCLUDED_)
