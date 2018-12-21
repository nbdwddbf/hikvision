#if !defined(AFX_DLGIPACCESSCFGSTREAMSERVER_H__5B5FD811_6198_439E_868D_376BFF737681__INCLUDED_)
#define AFX_DLGIPACCESSCFGSTREAMSERVER_H__5B5FD811_6198_439E_868D_376BFF737681__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIPAccessCfgStreamServer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgIPAccessCfgStreamServer dialog

class CDlgIPAccessCfgStreamServer : public CDialog
{
// Construction
public:
	CDlgIPAccessCfgStreamServer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgIPAccessCfgStreamServer)
	enum { IDD = IDD_DLG_REMOTE_IP_ACCESS_CFG_STREAM_SERVER };
	CComboBox	m_comboStreamTransType;
	CComboBox	m_comboDVRTransType;
	CComboBox	m_comboDVRTransProtocol;
	BOOL	m_bEnable;
	DWORD	m_dwChannelNO;
	CString	m_csDVRIP;
	DWORD	m_dwDVRPort;
	CString	m_csPasswd;
	CString	m_csStreamServerIP;
	CString	m_csUserName;
	DWORD	m_dwStreamPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIPAccessCfgStreamServer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIPAccessCfgStreamServer)
	afx_msg void OnBtnSet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void UpdateParams(int iMode);
	void SetParams();

	int m_iMode;  //取流模式

public:
	int m_iChannelIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIPACCESSCFGSTREAMSERVER_H__5B5FD811_6198_439E_868D_376BFF737681__INCLUDED_)
