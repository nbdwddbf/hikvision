#if !defined(AFX_DLGCASEINFO_H__9013C2EE_1697_43C6_AA8A_EC4879E68CE1__INCLUDED_)
#define AFX_DLGCASEINFO_H__9013C2EE_1697_43C6_AA8A_EC4879E68CE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCaseInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCaseInfo dialog

class CDlgCaseInfo : public CDialog
{
// Construction
public:
	CDlgCaseInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCaseInfo)
	enum { IDD = IDD_DLG_CASE_INFO };
	CComboBox	m_comboCaseType;
	UINT	m_nCaseShowTime;
	CString	m_sCaseLitigant1;
	CString	m_sCaseLitigant2;
	CString	m_sCaseName;
	CString	m_sCaseNo;
	CString	m_ChiefJudge;
	UINT	m_nCaseRealTimeShowTime;
	//}}AFX_DATA
	LONG m_lUserID;
	int m_iDeviceIndex;
	NET_DVR_CASE_INFO m_struCaseInfo;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCaseInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCaseInfo)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnControl();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    CString m_sCaseTypeCustom;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCASEINFO_H__9013C2EE_1697_43C6_AA8A_EC4879E68CE1__INCLUDED_)
