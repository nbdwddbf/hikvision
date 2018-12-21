#if !defined(AFX_DLGPDCSEARCH_H__ACF862DB_CA49_43EC_9D81_9DB288D2B4F8__INCLUDED_)
#define AFX_DLGPDCSEARCH_H__ACF862DB_CA49_43EC_9D81_9DB288D2B4F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPDCSearch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPDCSearch dialog

class CDlgPDCSearch : public CDialog
{
// Construction
public:
	CDlgPDCSearch(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPDCSearch)
	enum { IDD = IDD_DLG_PDC_SEARCH };
	CListCtrl	m_listPDCInfo;
	CTime	m_ctTimeStop;
	CTime   m_ctTimeStart;
	CTime   m_ctDateStart;
	CTime	m_ctDateStop;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPDCSearch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPDCSearch)
	afx_msg void OnBtnSearch();
	afx_msg void OnBtnExit();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    long        m_lFindHandle; 
    long        m_lServerID; 
    long        m_lChannel;  
    int         m_iDevIndex; 
    long        m_lPDCInfoNum;
    HANDLE      m_hPdcFindThread;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPDCSEARCH_H__ACF862DB_CA49_43EC_9D81_9DB288D2B4F8__INCLUDED_)
