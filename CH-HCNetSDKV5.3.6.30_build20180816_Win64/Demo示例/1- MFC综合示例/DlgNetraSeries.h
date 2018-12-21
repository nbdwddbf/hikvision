#if !defined(AFX_DLGNETRASERIES_H__545C4C8F_4BC8_4478_91A3_A5B3F27837EB__INCLUDED_)
#define AFX_DLGNETRASERIES_H__545C4C8F_4BC8_4478_91A3_A5B3F27837EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNetraSeries.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNetraSeries dialog

class CDlgNetraSeries : public CDialog
{
// Construction
public:
	CDlgNetraSeries(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNetraSeries)
	enum { IDD = IDD_DLG_NETRASERIES };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNetraSeries)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNetraSeries)
	afx_msg void OnBtnEventTrigerVedio();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnRecordPackage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
public:
	LONG    m_lLoginID;
    int     m_iDevIndex;
	LONG    m_lChannel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNETRASERIES_H__545C4C8F_4BC8_4478_91A3_A5B3F27837EB__INCLUDED_)
