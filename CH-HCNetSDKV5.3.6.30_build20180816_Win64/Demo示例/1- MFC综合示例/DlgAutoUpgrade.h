#if !defined(AFX_DLGAUTOUPGRADE_H__5C5158E8_2561_4949_850E_6CE68FDA734A__INCLUDED_)
#define AFX_DLGAUTOUPGRADE_H__5C5158E8_2561_4949_850E_6CE68FDA734A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAutoUpgrade.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAutoUpgrade dialog

class CDlgAutoUpgrade : public CDialog
{
// Construction
public:
	CDlgAutoUpgrade(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAutoUpgrade)
	enum { IDD = IDD_DLG_AUTOUPGRADE };
	CComboBox	m_cmbIDCodeIndex;
	CString	m_strIDCode;
	CString	m_strIDCodeVersion;
	BOOL	m_bConnectStatus;
	BOOL	m_bNewVersionAvailable;
	CString	m_strNewVersion;
	CString	m_strChangeLog;
	CString	m_strIDCodeCheck;
	CString	m_strIDCodeVersionCheck;
	BOOL	m_bRecommenVersion;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAutoUpgrade)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
public:
    LONG    m_lLoginID;
    int     m_iDeviceIndex;
    HANDLE	m_hGetProgress;
    BOOL    m_bExitGetProgress;
    NET_DVR_FIRMWARECODE_LIST m_struIDCodeList;
    static DWORD WINAPI GetProgressThread (LPVOID lpArg);
    void    GetSvrStatus();
    void    GetNewVersion(BOOL bManualCheck = FALSE);
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAutoUpgrade)
	afx_msg void OnBtnAllowAutoupgrade();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnBtnGetIdcode();
	afx_msg void OnSelchangeCmbIdcodeIndex();
	afx_msg void OnBtnManualCheck();
	afx_msg void OnBtnGetCheckVersion();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAUTOUPGRADE_H__5C5158E8_2561_4949_850E_6CE68FDA734A__INCLUDED_)
