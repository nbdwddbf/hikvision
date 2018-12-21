#if !defined(AFX_DLGWIRELESSBUSINESSSEARCH_H__25ECA076_2154_4F6C_98EC_AC5BED8CEAE2__INCLUDED_)
#define AFX_DLGWIRELESSBUSINESSSEARCH_H__25ECA076_2154_4F6C_98EC_AC5BED8CEAE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWirelessBusinessSearch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgWirelessBusinessSearch dialog

class CDlgWirelessBusinessSearch : public CDialog
{
// Construction
public:
	CDlgWirelessBusinessSearch(CWnd* pParent = NULL);   // standard constructor

    int     m_iDevIndex;
    LONG    m_lUserID;

// Dialog Data
	//{{AFX_DATA(CDlgWirelessBusinessSearch)
	enum { IDD = IDD_DLG_WIRELESS_BUSINNESS_SEARCH };
	CComboBox	m_cmbType;
	CString	m_csCommOperatorNum;
	CString	m_cs3GBusiness;
	CString	m_csSearchCode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWirelessBusinessSearch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWirelessBusinessSearch)
	afx_msg void OnBtnSearch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWIRELESSBUSINESSSEARCH_H__25ECA076_2154_4F6C_98EC_AC5BED8CEAE2__INCLUDED_)
