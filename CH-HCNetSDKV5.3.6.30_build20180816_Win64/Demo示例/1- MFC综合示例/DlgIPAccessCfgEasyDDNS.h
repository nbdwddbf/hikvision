#if !defined(AFX_DLGIPACCESSCFGEASYDDNS_H__FECB02D8_DF5B_499E_921C_2F912BE88322__INCLUDED_)
#define AFX_DLGIPACCESSCFGEASYDDNS_H__FECB02D8_DF5B_499E_921C_2F912BE88322__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIPAccessCfgEasyDDNS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgIPAccessCfgEasyDDNS dialog

class DlgIPAccessCfgEasyDDNS : public CDialog
{
// Construction
public:
	DlgIPAccessCfgEasyDDNS(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgIPAccessCfgEasyDDNS)
	enum { IDD = IDD_DLG_REMOTE_IP_ACCESS_CFG_EASYDDNS };
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
	//{{AFX_VIRTUAL(DlgIPAccessCfgEasyDDNS)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgIPAccessCfgEasyDDNS)
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

#endif // !defined(AFX_DLGIPACCESSCFGEASYDDNS_H__FECB02D8_DF5B_499E_921C_2F912BE88322__INCLUDED_)
