#if !defined(AFX_DLGLOGSEARCH_H__E3BCD2C5_B011_49EE_8A57_03975B590083__INCLUDED_)
#define AFX_DLGLOGSEARCH_H__E3BCD2C5_B011_49EE_8A57_03975B590083__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLogSearch.h : header file
//

#include "GeneralDef.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgLogSearch dialog

class CDlgLogSearch : public CDialog
{
// Construction
public:
	CDlgLogSearch(CWnd* pParent = NULL);   // standard constructor

public:
	LONG m_lLoginID;
	int m_iMode;
	int m_iMajType;
	int m_iMinType;
	
	BOOL m_bSearch;
	LONG m_lLogHandle;
	HANDLE m_hFileThread;
	LONG m_lLogNum;
public:
	void AddMinorString();
	
// Dialog Data
	//{{AFX_DATA(CDlgLogSearch)
	enum { IDD = IDD_DIALOG_LOG_SEARCH };
	CComboBox m_comboMode;
	CComboBox m_comboMajorType;
	CComboBox m_comboMinorType;
	CTime m_ctTimeStart;
	CTime m_ctDateStart;
	CTime m_ctDateStop;
	CTime m_ctTimeStop;
	CListCtrl m_listDeviceLog;
	BOOL m_bChkSmart;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLogSearch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLogSearch)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSearchLog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLOGSEARCH_H__E3BCD2C5_B011_49EE_8A57_03975B590083__INCLUDED_)
