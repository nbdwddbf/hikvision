#if !defined(AFX_USERDLG_H__D4EF2A8F_0B74_422A_9401_5439AECEAFD6__INCLUDED_)
#define AFX_USERDLG_H__D4EF2A8F_0B74_422A_9401_5439AECEAFD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserDlg dialog

class CUserDlg : public CDialog
{
// Construction
public:
	CUserDlg(CWnd* pParent = NULL);   // standard constructor
    LONG m_lServerID;
	int  m_iDeviceIndex;
    NET_DVR_ALARM_DEVICE_USER m_User;
    BOOL GetUserCfg();

// Dialog Data
	//{{AFX_DATA(CUserDlg)
	enum { IDD = IDD_DLG_SPLITTER_USER_CFG };
	CComboBox	m_UserCtrl;
	CString	m_strVerifyPwd;
	CString	m_strPwd;
	CString	m_strUser;
	BOOL	m_bRemoteParam;
	BOOL	m_bRemotePtz;
	BOOL	m_bRemoteOperation;
	BOOL	m_bRemoteReboot;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserDlg)
	afx_msg void OnBtnUserOk();
	afx_msg void OnSelchangeComboUserSel();		
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERDLG_H__D4EF2A8F_0B74_422A_9401_5439AECEAFD6__INCLUDED_)
