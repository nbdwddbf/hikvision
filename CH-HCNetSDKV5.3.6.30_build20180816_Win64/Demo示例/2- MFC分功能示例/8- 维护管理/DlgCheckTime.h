#if !defined(AFX_DLGCHECKTIME_H__43813512_53F0_4E3E_BDF2_F537A15528FD__INCLUDED_)
#define AFX_DLGCHECKTIME_H__43813512_53F0_4E3E_BDF2_F537A15528FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCheckTime.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCheckTime dialog

class CDlgCheckTime : public CDialog
{
// Construction
public:
	CDlgCheckTime(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCheckTime)
	enum { IDD = IDD_DIALOG_CHECK_TIME };
	CTime	m_checkTime;
	CTime	m_checkDate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCheckTime)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCheckTime)
	afx_msg void OnButtonCheckTime();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCHECKTIME_H__43813512_53F0_4E3E_BDF2_F537A15528FD__INCLUDED_)
