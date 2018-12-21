#include "afxwin.h"
#if !defined(AFX_DIALOGMULTINETCARD_H__8E848466_8643_4D0E_9172_12E3994EE5FA__INCLUDED_)
#define AFX_DIALOGMULTINETCARD_H__8E848466_8643_4D0E_9172_12E3994EE5FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogMultiNetCard.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogMultiNetCard dialog

class CDialogMultiNetCard : public CDialog
{
// Construction
public:
	CDialogMultiNetCard(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogMultiNetCard)
	enum { IDD = IDD_DLG_NETCFG_MULTI };
	CComboBox	m_card4Type;
	CComboBox	m_card3Type;
	CComboBox	m_routerCard;
	CComboBox	m_card2Type;
	CComboBox	m_card1Type;
	CString	m_csAlarmIp;
	int		m_iAlarmPort;
	int		m_iHttpPort;
	CString	m_csManage1IP;
	int		m_iManage2Port;
	CString	m_csManage2IP;
	int		m_iManage1Port;
	int		m_iResolverPort;
	CString	m_csRelolverIP;
	CString	m_csMultIP;
	BOOL	m_bCard2;
	BOOL	m_bCard1;
	BOOL	m_bCard1Dhcp;
	BOOL	m_bCard2Dhcp;
	CString	m_csCard1DNS1;
	CString	m_csCard2DNS1;
	CString	m_csCard1DNS2;
	CString	m_csCard2DNS2;
	CString	m_csCard2GateWay;
	CString	m_csCard1GateWay;
	CString	m_csCard1Ip;
	CString	m_csCard2Ip;
	CString	m_csCard2Mac;
	CString	m_csCard1Mac;
	CString	m_csCard1Mask;
	CString	m_csCard2Mask;
	short	m_wCard2MTU;
	short	m_wCard1MTU;
	BOOL	m_bEnablePPPoE;
	CString	m_csPPPoEIP;
	CString	m_csPPPoEPassword;
	CString	m_csPPPoEUserName;
	int		m_iDVRPort;
	int		m_iDVRPort2;
	BOOL	m_bCard3Dhcp;
	BOOL	m_bCard4Dhcp;
	CString	m_csCard3DNS1;
	CString	m_csCard3DNS2;
	CString	m_csCard3GateWay;
	CString	m_csCard3Ip;
	CString	m_csCard3Mac;
	CString	m_csCard3Mask;
	short	m_wCard3MTU;
	CString	m_csCard4DNS1;
	CString	m_csCard4DNS2;
	CString	m_csCard4GateWay;
	CString	m_csCard4Ip;
	CString	m_csCard4Mac;
	CString	m_csCard4Mask;
	short	m_wCard4MTU;

	BOOL	m_bShowIpv6;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogMultiNetCard)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogMultiNetCard)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSetCard2();
	afx_msg void OnButtonSetCard1();
	afx_msg void OnButtonNetcfg();
	afx_msg void OnButtonUpdate();
	afx_msg void OnExit();
	afx_msg void OnButtonSetCard3();
	afx_msg void OnButtonSetCard4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	inline BOOL ValidIPv6(BYTE *ip);
public :
    int m_iDeviceIndex;
	LONG m_lLoginID;
    NET_DVR_NETCFG_MULTI m_struNetCfg;
    BOOL m_bDNS;
    BOOL m_bDNS2;
    BOOL m_bDNS3;
    BOOL m_bDNS4;
    afx_msg void OnBnClickedCheckCard1Dhcp();
    afx_msg void OnBnClickedCheckDnsEnable();
    afx_msg void OnBnClickedCheckCard2Dhcp();
    afx_msg void OnBnClickedCheckDnsEnable2();
    CComboBox m_comboNetcardGroup;
    CString m_strCard1EthernetPort;
    CString m_strCard2EthernetPort;
    CString m_strCard3EthernetPort;
    CString m_strCard4EthernetPort;
private:
    CComboBox m_comboShowMode;
public:
    // iShowMode:0表示显示v4,1表示显示v6
    void ShowNetcardInfo(int iShowMode);
    afx_msg void OnCbnSelchangeComboShowMode();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGMULTINETCARD_H__8E848466_8643_4D0E_9172_12E3994EE5FA__INCLUDED_)
