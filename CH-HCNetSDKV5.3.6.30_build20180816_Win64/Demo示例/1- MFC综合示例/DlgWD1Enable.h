#if !defined(AFX_DLGWD1ENABLE_H__0A35133E_4262_4858_81BE_94CBA78EA561__INCLUDED_)
#define AFX_DLGWD1ENABLE_H__0A35133E_4262_4858_81BE_94CBA78EA561__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWD1Enable.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgWD1Enable dialog

class CDlgWD1Enable : public CDialog
{
// Construction
public:
	CDlgWD1Enable(CWnd* pParent = NULL);   // standard constructor
	LONG m_lServerID;
    LONG m_iDevIndex;
    int  m_lChannel;

// Dialog Data
	//{{AFX_DATA(CDlgWD1Enable)
	enum { IDD = IDD_DLG_WD1ENABLE };
	BOOL	m_chkWd1Enable;
	UINT	m_dwHighVersion;
	UINT 	m_dwLowerVersion;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWD1Enable)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWD1Enable)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWD1ENABLE_H__0A35133E_4262_4858_81BE_94CBA78EA561__INCLUDED_)
