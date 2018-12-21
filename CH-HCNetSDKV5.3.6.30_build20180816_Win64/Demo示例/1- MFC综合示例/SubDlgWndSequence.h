#if !defined(AFX_SUBDLGWNDSEQUENCE_H__E0BAC6EE_F261_43B5_95AA_4DB29F8AB221__INCLUDED_)
#define AFX_SUBDLGWNDSEQUENCE_H__E0BAC6EE_F261_43B5_95AA_4DB29F8AB221__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubDlgWndSequence.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSubDlgWndSequence dialog

class CSubDlgWndSequence : public CDialog
{
// Construction
public:
	CSubDlgWndSequence(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubDlgWndSequence();

// Dialog Data
	//{{AFX_DATA(CSubDlgWndSequence)
	enum { IDD = IDD_SUBDLG_WND_SEQUENCE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubDlgWndSequence)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSubDlgWndSequence)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CComboBox *m_pComboBox;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	void OnSetCurSel(int nIndex);
	int OnGetCurSel(void);
	void OnInitialize(int nChanNum, int nIPChanNum, int nStartNum);
    
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBDLGWNDSEQUENCE_H__E0BAC6EE_F261_43B5_95AA_4DB29F8AB221__INCLUDED_)
