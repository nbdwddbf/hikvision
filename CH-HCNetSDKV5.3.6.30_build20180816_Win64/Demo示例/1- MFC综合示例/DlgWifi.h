#if !defined(AFX_DLGWIFI_H__19581CB9_A2E3_45B7_88CE_D53AC9C9FD8A__INCLUDED_)
#define AFX_DLGWIFI_H__19581CB9_A2E3_45B7_88CE_D53AC9C9FD8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWifi.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgWifi dialog

class CDlgWifi : public CDialog
{
// Construction
public:
	CDlgWifi(CWnd* pParent = NULL);   // standard constructor
	int m_iDeviceIndex;
	BOOL GetParam();

// Dialog Data
	//{{AFX_DATA(CDlgWifi)
	enum { IDD = IDD_DLG_WIFI };
	CComboBox	m_cmbErrorCode;
	CComboBox	m_cmbConnectStatus;
	CComboBox	m_comboPeapVer;
	CComboBox	m_comboPeapInterAuth;
	CComboBox	m_comboPeapLabel;
	CComboBox	m_comboAuthType;
	CComboBox	m_comboCertType;
	CComboBox	m_comboFileType;
	CComboBox	m_comboInterAuthType;
	CComboBox	m_comboEapolVer;
	CComboBox	m_comboWPAEnterEncry;
	CComboBox	m_comboWpaEncType;
	CComboBox	m_ActiveKey;
    CComboBox   m_comboKeyType;
	BOOL	m_Active1;
	CString	m_csPassword;
	CString	m_csPrivateKeyPwd;
	CString	m_csUserName;
	CString	m_csUploadState;
	CString	m_csAnonyIdentity;
	CString	m_csIdentity;
	CString	m_csCertPath;
	//}}AFX_DATA
	CComboBox	m_AuthCtrl;
	CComboBox	m_KeyLenCtrl;
	CComboBox	m_KeyTypeCtrl;
	CComboBox	m_WorkModeCtrl;
	CComboBox	m_EncryptTypeCtrl;
	CComboBox	m_EthernetWorkMode;
	CListCtrl	m_WifiList;
	CString	m_strDns1;
	CString	m_strDns2;
	CString	m_strGatewayAddr;
	CString	m_strHideCode;
	CString	m_strHostAddr;
	CString	m_strIpAddress;
	CString	m_strSsid;
	BOOL	m_bAutoDns;
	BOOL	m_bStartDhcp;
    BOOL	m_byCloseWifi;
	CString	m_strKey1;
	CString	m_strKey2;
	CString	m_strKey3;
	CString	m_strKey4;
	CString	m_strEncKey;
	UINT	m_uKeyLen;
	UINT	m_uApNum;

	NET_DVR_WIFI_WORKMODE m_WifiWorkMode;
	NET_DVR_AP_INFO_LIST  m_ApInfo;
	NET_DVR_WIFI_CFG      m_WifiCfg;
	NET_DVR_WIFI_CONNECT_STATUS	m_struWifiStatus;

	char    m_chFilename[256];//Ö¤ÊéÂ·¾¶
	LONG    m_lUploadHandle;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWifi)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWifi)
	afx_msg void OnRefurbish();
	afx_msg void OnSavewifiparam();
	afx_msg void OnSelchangeEncrypttype();
	afx_msg void OnStartdhcp();
	afx_msg void OnAutodns();
	afx_msg void OnDblclkWifiList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnExit();
	afx_msg void OnBtnScanCert();
	afx_msg void OnBtnUploadCert();
#if (_MSC_VER >= 1500)	//vs2008
    afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
    afx_msg void OnTimer(UINT nIDEvent);
#endif
	afx_msg void OnSelchangeComboAuthType();
	afx_msg void OnBtnGetConnectStatus();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWIFI_H__19581CB9_A2E3_45B7_88CE_D53AC9C9FD8A__INCLUDED_)
