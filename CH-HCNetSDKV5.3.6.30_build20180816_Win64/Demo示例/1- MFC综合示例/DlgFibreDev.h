#include "afxwin.h"
#if !defined(AFX_DLGFIBREDEV_H__71A4537E_47BE_4506_95ED_60BCCAEC5D40__INCLUDED_)
#define AFX_DLGFIBREDEV_H__71A4537E_47BE_4506_95ED_60BCCAEC5D40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFibreDev.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFibreDev dialog

class CDlgFibreDev : public CDialog
{
// Construction
public:
	CDlgFibreDev(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFibreDev)
	enum { IDD = IDD_DLG_FIBRE_DEV };
	CComboBox	m_cmbPortTypeNet;
	CComboBox	m_cmbWorkMod;
	CComboBox	m_cmbPeerWorkMod;
	CComboBox	m_cmbPortType;
	CComboBox	m_cmbPeerBandWidth;
	CComboBox	m_cmbBandWidth;
	CComboBox	m_cmbCardType;
	CComboBox	m_comboStruType;
	CComboBox	m_comboFuncStruType;
	CComboBox	m_comboFuncCardIndex;
	CComboBox	m_comboFuncWorkMode;
	CComboBox	m_comboFuncPortIndex;
	CComboBox	m_comboFuncIndex;
	CComboBox	m_comboFuncBandWidth;
	CComboBox	m_comboCardIndex;
	CComboBox	m_comboStatusPortTye;
	CComboBox	m_comboPowerType;
	CComboBox	m_comboPortType;
	CComboBox	m_comboLinkState;
	CComboBox	m_comboNetPortWidth;
	CComboBox	m_comboWorkMode;
	CComboBox	m_comboNetPortIndex;
	CComboBox	m_comboIndex;
	CComboBox	m_comboPortID;
	CComboBox	m_comboCardID;
	CString	m_strPeerDevName;
	CString	m_strPortMacAddr;
	CString	m_strPortRemarks;
	CString	m_strPeerPortID;
	CString	m_strPeerPortMacAddr;
	CString	m_strPeerPortRemarks;
	BOOL	m_bEnableSetlldp;
	BOOL	m_bEnableGetlldp;
	BOOL	m_bEnablellpd;
	DWORD	m_dwHoldTime;
	DWORD	m_dwPacketTime;
	DWORD	m_dwReiniTime;
	BYTE	m_bySlotNo;
	BYTE	m_byPortNo;
	DWORD	m_dwFuncCardNum;
	DWORD	m_dwStatusCardNum;
	DWORD	m_dwCRCPacket;
	DWORD	m_dwFragement;
	DWORD	m_dwFuncPortNum;
	CString	m_szSerialNo;
	CString	m_szIPAddr;
	DWORD	m_dwLostPacker;
	DWORD	m_dwNetPortNum;
	CString	m_szPortName;
	DWORD	m_dwRecvByte;
	DWORD	m_dwSendByte;
	CString	m_szSeralNo;
	CString	m_szTypeName;
	DWORD	m_dwMainSlotNo;
	DWORD	m_dwSlotNum;
	BOOL	m_bPortEnable;
	BOOL	m_bEnable;
	BOOL	m_bCardEnable;
	CString	m_strPortNameNet;
	DWORD	m_dwSlotUsedNum;
	CString	m_szSoftwareVer;
	CString	m_szFuncSoftwareVer;
	DWORD	m_dwFuncSlotNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFibreDev)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFibreDev)
	afx_msg void OnBtnFibrePortRemarksGet();
	afx_msg void OnBtnFibrePortRemarksSet();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboFibreCardId();
	afx_msg void OnSelchangeComboFibrePortId();
	afx_msg void OnDestroy();
	afx_msg void OnBtnGetLldp();
	afx_msg void OnBtnSetLldp();
	afx_msg void OnBtnSetLldpcfg();
	afx_msg void OnSelchangeComboIndex();
	afx_msg void OnBtnGetNetinfo();
	afx_msg void OnBtnConvertGet();
	afx_msg void OnSelchangeComboNetportIndex();
	afx_msg void OnSelchangeComboFuncPortindex();
	afx_msg void OnSelchangeComboFunccardindex();
	afx_msg void OnSelchangeComboCaedstatIndex();
	afx_msg void OnSelchangeComboFuncIndex();
	afx_msg void OnSelchangeComboPort();
	afx_msg void OnSelchangeComboCardType();
	afx_msg void OnButtonGet();
	afx_msg void OnButtonExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	LONG m_lUserID;
	LPNET_DVR_STD_CONFIG m_lpConfigParam;
	LPNET_DVR_FIBER_CONVERT_TOPOLOGY m_lpFibreTopoInfo;
	LPNET_DVR_FC_CARD_TOPOLOGY m_lpCardTopoInfo;
	LPNET_DVR_FC_PORT_TOPOLOGY m_lpPortTopoInfo;
    NET_DVR_LLDP_CFG m_strulldpCfg;
    NET_DVR_FIBER_CONVERT_BASIC_V50 m_struFiberConvertBasic;
    NET_DVR_FIBER_CONVERT_STATE_V50 m_struFiberConbertState;


public:
	void SetUserID(LONG lUserID){m_lUserID = lUserID;};
    DWORD m_dwSlots;
    CString m_sMacAddr;
    CString m_sGateWay;
    CString m_sMask;
    CString m_sNewestSoftWareVer;
    CString m_sHardVer;
    DWORD m_dwFuncSlots;
    CString m_sHardwareVer;
    CComboBox m_cmbType;
    void SelchangeComboRecvCardIndex(int iIndex);
    void SelchangeComboRecvCardPortIndex(int iIndex, int iPindex);
    void SelchangeComboRemoteSendCardIndex(int iIndex);
    void SelchangeComboRemoteSendCardPortIndex(int iIndex, int iPindex);
    CString m_sModelName;
    CComboBox m_cmbDuplexMode;
    CComboBox m_cmbPortSpeed;
    CString m_sPortName;
    DWORD m_dwRecvByteSpeed;
    DWORD m_dwRecvPackets;
    DWORD m_dwRecvPacketSpeed;
    DWORD m_dwSendByteSpeed;
    DWORD m_dwSendPackets;
    DWORD m_dwSendPacketSpeed;
    afx_msg void OnCbnSelchangeComboCardtype();
    DWORD m_dwStatePortNo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFIBREDEV_H__71A4537E_47BE_4506_95ED_60BCCAEC5D40__INCLUDED_)
