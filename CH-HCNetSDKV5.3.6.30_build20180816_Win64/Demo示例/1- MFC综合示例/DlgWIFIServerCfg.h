#if !defined(AFX_DLGWIFISERVERCFG_H__CE76CE98_3981_4DD2_ACD7_01699256E2A4__INCLUDED_)
#define AFX_DLGWIFISERVERCFG_H__CE76CE98_3981_4DD2_ACD7_01699256E2A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWIFIServerCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgWIFIServerCfg dialog

class CDlgWIFIServerCfg : public CDialog
{
// Construction
public:
	CDlgWIFIServerCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgWIFIServerCfg)
	enum { IDD = IDD_DLG_WIFI_SERVER_CFG };
	CComboBox	m_comKeyType;
	CComboBox	m_comAlgorithmType;
	CComboBox	m_comWepKeyLenType;
	CComboBox	m_comDefaultTransmitKeyIndex;
	CComboBox	m_comSecurityMode;
	CComboBox	m_comAuthenticationType;
	CComboBox	m_comboIPType;
	BOOL	m_bChkWifiAP;
	BOOL	m_bChkBroadcast;
	BOOL	m_bChkDHCP;
	BOOL	m_bChkWlanShare;
	CString	m_csDNS1;
	CString	m_csDNS2;
	CString	m_csSSID;
	CString	m_csEndIP;
	CString	m_csGateway;
	CString	m_csIP;
	CString	m_csIPMask;
	CString	m_csStartIP;
	CString	m_csEncryptionKey1;
	CString	m_csEncryptionKey2;
	CString	m_csEncryptionKey3;
	CString	m_csEncryptionKey4;
	CString	m_csSharedKey;
	BOOL	m_bCHKDefaultPass;
	BYTE	m_byWPAKeyLen;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWIFIServerCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWIFIServerCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnSelchangeComboSecurityMode();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboTransmitkeyIndex();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG  m_lChannel;
    long  m_lServerID; // 用户ID
    int   m_iDevIndex; // 设备索引
    int   m_nNetworkCardNo;
    char m_szStatusBuf[ISAPI_STATUS_LEN];
    NET_DVR_WIRELESSSERVER_FULLVERSION_CFG m_struWifiServerCfg;

    BOOL ValidIPv6(BYTE *ip);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWIFISERVERCFG_H__CE76CE98_3981_4DD2_ACD7_01699256E2A4__INCLUDED_)
