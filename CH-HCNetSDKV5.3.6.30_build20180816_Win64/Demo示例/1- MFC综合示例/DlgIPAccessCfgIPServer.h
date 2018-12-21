#if !defined(AFX_DLGIPACCESSCFGIPSERVER_H__119C1432_91F7_4744_AB7A_368D37BE1274__INCLUDED_)
#define AFX_DLGIPACCESSCFGIPSERVER_H__119C1432_91F7_4744_AB7A_368D37BE1274__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIPAccessCfgIPServer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgIPAccessCfgIPServer dialog

class CDlgIPAccessCfgIPServer : public CDialog
{
// Construction
public:
	CDlgIPAccessCfgIPServer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgIPAccessCfgIPServer)
	enum { IDD = IDD_DLG_REMOTE_IP_ACCESS_CFG_IPSERVER };
	BOOL	m_bEnable;
	DWORD	m_dwDVRChannelNO;
	DWORD	m_dwDVRPort;
	CString	m_csDVRSerial;
	CString	m_csIPServerIP;
	DWORD	m_dwIPServerPort;
	CString	m_csPasswd;
	CString	m_csUsername;
	CString	m_csDVRName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIPAccessCfgIPServer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIPAccessCfgIPServer)
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void UpdateParams();
	void SetParams();
	
public:
	int m_iChannelIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIPACCESSCFGIPSERVER_H__119C1432_91F7_4744_AB7A_368D37BE1274__INCLUDED_)
