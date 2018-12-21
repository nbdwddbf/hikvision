#if !defined(AFX_DLGUPNPCFG_H__03B28E40_91A1_4844_A41D_76E45ED552A9__INCLUDED_)
#define AFX_DLGUPNPCFG_H__03B28E40_91A1_4844_A41D_76E45ED552A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgUpnpCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgUpnpCfg dialog

class CDlgUpnpCfg : public CDialog
{
// Construction
public:
	CDlgUpnpCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgUpnpCfg)
	enum { IDD = IDD_DLG_UPNP };
	CComboBox	m_comboNatType;
	CListCtrl	m_listState;
	int		m_iServerPort;
	int		m_iRtspPort;
	CString	m_csNatIp;
	int		m_iAdminPort;
	int     m_iHttpsPort;
	BOOL	m_bEnableNat;
	BOOL	m_bEnableWeb;
	BOOL	m_bEnableUpnp;
	BOOL	m_bEnableRtsp;
	BOOL	m_bEnableAdmin;
	BOOL    m_bEnableHttps;
	CString m_csPoeIP;
	CString	m_csFriendName;
	BOOL	m_bEnableHppts;
	//}}AFX_DATA

	NET_DVR_NAT_CFG m_strNatCfg;
	NET_DVR_POE_CFG m_strPoeCfg;
	LONG m_lUserID;
	DWORD m_dwDeviceIndex;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgUpnpCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgUpnpCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonUpdate();
	afx_msg void OnButtonSetup();
	afx_msg void OnButtonUpdateState();
	afx_msg void OnButtonExit();
	afx_msg void OnButtonGetPoe();
	afx_msg void OnButtonSetPoe();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    int m_iSdkOverTlsPort;
    BOOL m_bSdkOverTlsEnable;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGUPNPCFG_H__03B28E40_91A1_4844_A41D_76E45ED552A9__INCLUDED_)
