#if !defined(AFX_DLGIPACCESSCFGDDNS_H__633E8E34_9A15_4276_BC0B_3B0000CC41A1__INCLUDED_)
#define AFX_DLGIPACCESSCFGDDNS_H__633E8E34_9A15_4276_BC0B_3B0000CC41A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIPAccessCfgDDNS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgIPAccessCfgDDNS dialog

class CDlgIPAccessCfgDDNS : public CDialog
{
// Construction
public:
	CDlgIPAccessCfgDDNS(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgIPAccessCfgDDNS)
	enum { IDD = IDD_DLG_REMOTE_IP_ACCESS_CFG_DDNS };
	CComboBox	m_comboStreamTransType;
	CComboBox	m_comboDVRTransType;
	CComboBox	m_comboDVRTransProtocol;
	BOOL	m_bEnable;
	DWORD	m_dwChannel;
	CString	m_csDVRName;
	DWORD	m_dwDVRPort;
	CString	m_csDVRSerial;
	CString	m_csIPServerIP;
	CString	m_csDVRPasswd;
	CString	m_csStreamIP;
	DWORD	m_dwStreamPort;
	CString	m_csUserName;
	DWORD	m_dwIPServerPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIPAccessCfgDDNS)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIPAccessCfgDDNS)
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

#endif // !defined(AFX_DLGIPACCESSCFGDDNS_H__633E8E34_9A15_4276_BC0B_3B0000CC41A1__INCLUDED_)
