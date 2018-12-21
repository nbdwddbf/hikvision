#if !defined(AFX_DLGNETRAHTTPS_H__E304E321_DDAA_457A_B044_B41008DBD28D__INCLUDED_)
#define AFX_DLGNETRAHTTPS_H__E304E321_DDAA_457A_B044_B41008DBD28D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNetraHttps.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNetraHttps dialog

class CDlgNetraHttps : public CDialog
{
// Construction
public:
	CDlgNetraHttps(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNetraHttps)
	enum { IDD = IDD_DLG_NETRAHTTPS };
	short	m_wHttpsPort;
	BOOL	m_bHttps;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNetraHttps)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNetraHttps)
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG m_lUserId;
	int m_iDevIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNETRAHTTPS_H__E304E321_DDAA_457A_B044_B41008DBD28D__INCLUDED_)
