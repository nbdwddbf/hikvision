#if !defined(AFX_DLGPOSCONNECTMODE_H__D785D4A3_3F0C_4395_B765_31CCE9DBFF26__INCLUDED_)
#define AFX_DLGPOSCONNECTMODE_H__D785D4A3_3F0C_4395_B765_31CCE9DBFF26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPosConnectMode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPosConnectMode dialog

typedef enum tagPOS_CONNECT_MODE
{
    MODE_NET_TCP_MONITER = 0,
	MODE_NET_RECEIVE,
	MODE_RS232,
	MODE_NET_UDP_MONITER,
	MODE_SNIFF,
	MODE_MULTICAST,
	MODE_USB_RS232
}POS_CONNECT_MODE;
class CDlgPosConnectMode : public CDialog
{
// Construction
public:
	CDlgPosConnectMode(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPosConnectMode)
	enum { IDD = IDD_DLG_POS_CONNECT_MODE };
	CComboBox	m_cmbFilterID;
	CComboBox	m_comboRS232StopBit;
	CComboBox	m_comboRS232Parity;
	CComboBox	m_comboRS232FlowCtrl;
	CComboBox	m_comboRS232DataBit;
	CComboBox	m_comboRS232BaudRate;
	CComboBox	m_comboRS232WorkMode;
	CComboBox	m_comboConnectMode;
	short	m_wRecvPort;
	short	m_wDstPort;
	CString	m_csSourceAddr;
	short	m_wSourcePort;
	CString	m_csDstAddr;
	BOOL	m_bEnableDstAddr;
	BOOL	m_bEnableDstPort;
	BOOL	m_bEnableSourcePort;
	CString	m_csMultiCastAddr;
	short	m_wMultiCastPort;
	BYTE	m_byUSBToRS232SerialNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPosConnectMode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPosConnectMode)
	afx_msg void OnBtnSet();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGet();
	afx_msg void OnKillfocusEditNetReceivePort();
	afx_msg void OnSelchangeComboConnectMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void ShowConnectInfo(UINT dwType);
	void ShowNetReceiveInfo(BOOL bShow);
	void ShowNetMonitorInfo(BOOL bShow);
	void ShowRS232Info(BOOL bShow);
    void ShowUSBToRS232Info(BOOL bShow);
	void GetNetSeceiveInfo();
	void GetTcpMonitorInfo();
	void GetUdpMonitorInfo();
	void GetRS232Info();
	void GetUSBToRS232Info();
	void GetSniffInfo();
	void GetMultiCastInfo();
	void SetNetSeceiveInfo();
	void SetTcpMonitorInfo();
	void SetUDPMonitorInfo();
	void SetRS232Info();
	void SetUsbToRS232Info();
public:
	int m_iUserID ;
	int m_iDevIndex;
	NET_DVR_CONNECT_POS_CFG m_struConnectPosCfg ;
    CString m_szRestrictRemoteIP;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPOSCONNECTMODE_H__D785D4A3_3F0C_4395_B765_31CCE9DBFF26__INCLUDED_)
