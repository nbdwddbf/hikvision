#if !defined(AFX_DLGINTERACTIVE_H__B4DD022E_E3AE_423D_BDD1_9D03AB85AD4A__INCLUDED_)
#define AFX_DLGINTERACTIVE_H__B4DD022E_E3AE_423D_BDD1_9D03AB85AD4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInteractive.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInteractive dialog

class CDlgInteractive : public CDialog
{
// Construction
public:
	CDlgInteractive(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInteractive)
	enum { IDD = IDD_DLG_INTERACTIVE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInteractive)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInteractive)
	afx_msg void OnBtnFileConfig();
	afx_msg void OnBtnScreenCtrl();
	afx_msg void OnBtnScreenParam();
	afx_msg void OnBtnUpdownload();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINTERACTIVE_H__B4DD022E_E3AE_423D_BDD1_9D03AB85AD4A__INCLUDED_)
