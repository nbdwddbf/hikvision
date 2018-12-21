#if !defined(AFX_DLGUPDATE_H__7A9C3240_0A63_448C_A085_187AFF3B7434__INCLUDED_)
#define AFX_DLGUPDATE_H__7A9C3240_0A63_448C_A085_187AFF3B7434__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgUpdate.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgUpdate dialog

class CDlgUpdate : public CDialog
{
// Construction
public:
	CDlgUpdate(CWnd* pParent = NULL);   // standard constructor
public:
	LONG m_lUpgradeHandle;
	
	LONG	m_lServerID;
	UINT	m_lpUpgradeTimer;
	BOOL	m_bUpgrade;
// Dialog Data
	//{{AFX_DATA(CDlgUpdate)
	enum { IDD = IDD_DIALOG_UPDATE };
	CComboBox	m_comboEnvironment;
	CProgressCtrl	m_progressUpgrade;
	CString m_csUpgradeFile;
	CString m_csUpgradeStat;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgUpdate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgUpdate)
	afx_msg void OnBtnSetEnviro();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnBrowseFile();
	afx_msg void OnBtnUpgradeExit();
	afx_msg void OnBtnUpgrade();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGUPDATE_H__7A9C3240_0A63_448C_A085_187AFF3B7434__INCLUDED_)
