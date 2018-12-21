#if !defined(AFX_DLGPASSIVEWIN_H__A3CA3DAA_C4D9_4D9F_8B59_C321C1D56E65__INCLUDED_)
#define AFX_DLGPASSIVEWIN_H__A3CA3DAA_C4D9_4D9F_8B59_C321C1D56E65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPassiveWin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPassiveWin dialog


class CDlgPassiveWin : public CDialog
{
// Construction
public:
	CDlgPassiveWin(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPassiveWin)
	enum { IDD = IDD_DLG_PASSIVE_WIN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPassiveWin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPassiveWin)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void MoveWindow();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPASSIVEWIN_H__A3CA3DAA_C4D9_4D9F_8B59_C321C1D56E65__INCLUDED_)
