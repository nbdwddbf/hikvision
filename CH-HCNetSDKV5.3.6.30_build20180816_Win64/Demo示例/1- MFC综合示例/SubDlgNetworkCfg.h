#if !defined(AFX_SUBDLGNETWORKCFG_H__CC942E5C_F5A7_44E2_B470_20514CA609A4__INCLUDED_)
#define AFX_SUBDLGNETWORKCFG_H__CC942E5C_F5A7_44E2_B470_20514CA609A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubDlgNetworkCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSubDlgNetworkCfg dialog

class CSubDlgNetworkCfg : public CDialog
{
// Construction
public:
	CSubDlgNetworkCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSubDlgNetworkCfg)
	enum { IDD = IDD_SUB_DLG_NETWORK_CFG };
	CComboBox	m_comboNetFace;
	BOOL	m_bChkDhcp;
	CString m_csDeviceIP;
	CString m_csIPMask;
	CString m_csGatewayIP;
	CString m_csDNSIP1;
	CString m_csDNSIP2;
	CString m_csMacAddr;
	CString m_csIPResolver;
	int m_iMainPort;
	int m_iMainPort2;
	int m_iHttpPort;
	CString m_csMultiIP;
	CString m_csAlarmHostIP;
	int m_iAlarmHostPort;
	short m_wMTU;
	CComboBox m_comboIPv6Mode;
    BOOL m_bEnablePrivateMulticastDiscovery;
    BOOL m_bEnableOnvifMulticastDiscovery;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubDlgNetworkCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSubDlgNetworkCfg)
	afx_msg void OnBtnIpTest();
	afx_msg void OnBtnAdvanceNetSetup();
	afx_msg void OnBtnBondingCfg();
	afx_msg void OnBtnGetEthernetIpv6Cfg();
	afx_msg void OnBtnHighNetCfg();
	afx_msg void OnBtnMatDecDns();
	afx_msg void OnBtnNetworkFlowtest();
	afx_msg void OnBtnWifiConfig();
	afx_msg void OnButtonMultNetcard();
	afx_msg void OnButtonUpnp();
	afx_msg void OnChkDhcp();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	void EnableDhcp();
    void EnableDns();
	BOOL ValidIPv6(BYTE *ip);
public:
	BOOL CfgSetup();
	BOOL CheckInitParam();
	void CurCfgUpdate();
	static DWORD WINAPI GetServerTestInfoThread1(LPVOID lpArg);
protected:
	LONG	m_lIpTest;
	HANDLE	m_hIpTest;
public:
    int m_iDeviceIndex;
	LONG m_lLoginID;
    NET_DVR_NETCFG_V50 m_struNetCfg;
    CString m_csAlarmHostIP2;
    int m_iAlarmHostPort2;
    BOOL m_bDNS;
    afx_msg void OnBnClickedCheckDnsEnable();
    CString m_strEthernetPort;
private:
    // iShowMode:0表示显示ipv4,1表示显示ipv6
    void ShowNetworkCfg(int iShowMode);
    CComboBox m_comboShowMode;
    afx_msg void OnCbnSelchangeComboShowMode();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBDLGNETWORKCFG_H__CC942E5C_F5A7_44E2_B470_20514CA609A4__INCLUDED_)
