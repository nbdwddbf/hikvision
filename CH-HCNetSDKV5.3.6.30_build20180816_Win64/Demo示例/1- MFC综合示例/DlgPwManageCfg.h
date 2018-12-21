#if !defined(AFX_DLGPWMANAGECFG_H__B5ABBFC2_DE1B_4E71_91C9_9DB476216811__INCLUDED_)
#define AFX_DLGPWMANAGECFG_H__B5ABBFC2_DE1B_4E71_91C9_9DB476216811__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPwManageCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPwManageCfg dialog

class CDlgPwManageCfg : public CDialog
{
// Construction
public:
	CDlgPwManageCfg(CWnd* pParent = NULL);   // standard constructor
	long m_lUserId;
	int m_iDeviceIndex;
	char m_szLan[128];
	NET_DVR_PASSWORD_MANAGE_CFG m_struPwManageCfg;
// Dialog Data
	//{{AFX_DATA(CDlgPwManageCfg)
	enum { IDD = IDD_DLG_PW_MANAGE_CFG };
	BYTE	m_byLockCount;
	DWORD	m_dwLockTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPwManageCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPwManageCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnLockInfo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPWMANAGECFG_H__B5ABBFC2_DE1B_4E71_91C9_9DB476216811__INCLUDED_)
