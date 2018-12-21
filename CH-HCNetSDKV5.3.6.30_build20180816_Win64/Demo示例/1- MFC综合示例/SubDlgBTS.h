#if !defined(AFX_SUBDLGBTS_H__D8B409A2_7A09_4DBD_B7B2_FFF277F06FE3__INCLUDED_)
#define AFX_SUBDLGBTS_H__D8B409A2_7A09_4DBD_B7B2_FFF277F06FE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubDlgBTS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSubDlgBTS dialog

class CSubDlgBTS : public CDialog
{
// Construction
public:
	CSubDlgBTS(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSubDlgBTS)
	enum { IDD = IDD_SUB_DLG_BTS };
	CComboBox	m_cmbBTS;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubDlgBTS)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSubDlgBTS)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSetBTS();
	afx_msg void OnBtnGetBTS();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG    m_lServerID;
    int     m_iDevIndex;

	BOOL CheckInitParam();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBDLGBTS_H__D8B409A2_7A09_4DBD_B7B2_FFF277F06FE3__INCLUDED_)
