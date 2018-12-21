#include "afxwin.h"
#if !defined(AFX_DLGNETWORKBONDING_H__F5AADF4F_CE94_48AC_B7C4_19FA3D625A5B__INCLUDED_)
#define AFX_DLGNETWORKBONDING_H__F5AADF4F_CE94_48AC_B7C4_19FA3D625A5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNetworkBonding.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNetworkBonding dialog

class CDlgNetworkBonding : public CDialog
{
// Construction
public:
	CDlgNetworkBonding(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNetworkBonding)
	enum { IDD = IDD_DLG_NETWORK_BONDING };
	CComboBox	m_comboBondType;
	CListCtrl	m_listBondCard;
	CComboBox	m_comboMasterCard;
	CComboBox	m_comboWorkMode;
	BOOL	m_bEnable;
	BOOL	m_bStatus;
	BOOL	m_bDhcp;
	CString	m_csBondIP;
	CString	m_csBondMac;
	CString	m_csBondMask;
	CString	m_csGatewayIP;
	int		m_iBondMtu;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNetworkBonding)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNetworkBonding)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSetUp();
	afx_msg void OnButtonExit();
	afx_msg void OnButtonUpdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    DWORD   m_dwNetworkNum;     // Íø¿¨ÊýÄ¿
    NET_DVR_NETWORK_BONDING m_struNetworkBonding;    
public:
    void InitWnd();
    void InitWorkModeCombo();
    void InitMasterCardCombo();
    void InitBondCardList();
    BOOL GetNetworkBonding(NET_DVR_NETWORK_BONDING &struNetworkBonding);
    BOOL SetNetworkBonding(NET_DVR_NETWORK_BONDING &struNetworkBonding);
    void GetNetworkBondingFromWnd(NET_DVR_NETWORK_BONDING &struNetworkBonding);
    void SetNetworkBondingToWnd(NET_DVR_NETWORK_BONDING &struNetworkBonding);
    void GetOneBondingFromWnd(NET_DVR_ONE_BONDING &struOneBonding);
    void SetOneBondingToWnd(NET_DVR_ONE_BONDING &struOneBonding);
    void SetEthernetV30ToWnd(NET_DVR_ETHERNET_V30 &struEthernet);
    void GetEthernetV30FromWnd(NET_DVR_ETHERNET_V30 &struEthernet);
    //NET_DVR_ETHERNET_V30
    CComboBox m_comboBondMode;
    CString m_strEthernetPort;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNETWORKBONDING_H__F5AADF4F_CE94_48AC_B7C4_19FA3D625A5B__INCLUDED_)
