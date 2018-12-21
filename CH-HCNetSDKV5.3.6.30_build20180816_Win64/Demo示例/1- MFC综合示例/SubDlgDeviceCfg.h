#pragma once
#include "afxwin.h"


// CSubDlgDeviceCfg dialog

class CSubDlgDeviceCfg : public CDialog
{
	DECLARE_DYNAMIC(CSubDlgDeviceCfg)

public:
	CSubDlgDeviceCfg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubDlgDeviceCfg();

// Dialog Data
public:
	//{{AFX_DATA(CSubDlgDeviceCfg)
	enum { IDD = IDD_SUB_DLG_DEVICE_CFG };
	CComboBox	m_cmbMenuOutputMode;
	CComboBox	m_comboStorageMode;
	CComboBox	m_comboPlug;
	CComboBox	m_comboEsata;
	CComboBox	m_comboDevSupport;
	CComboBox	m_comboSubProtocol;
	CComboBox	m_comboMainProtocol;
	CComboBox	m_comboMinor;
	CString m_csDeviceName;
	int m_iHdNum;
	UINT m_iYKQID;
	CComboBox m_comboUseZoom;
	CString m_csDeviceSerialNo;
	CString m_csSoftwareVersion;
	CString m_csHardwareVersion;
	CString m_csDspVersion;
	int m_iAlarmInNum;
	int m_iAlarmOutNum;
	int m_iChanNum;
	CComboBox m_comboCycleRec;
	CString	m_csPanelVersion;
	int		m_iZeroChanNum;
	CString	m_csDevTypeName;
	CString	m_csLanguageType;
	DWORD	m_dwDevType;
    int		m_iIPChanNum;
    BOOL	m_bEnableRemotePowerOn;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CSubDlgDeviceCfg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CSubDlgDeviceCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnRemoteNetOk();
	afx_msg void OnBnClickedBtnJpegFtp();
	afx_msg void OnBtnZone();
	afx_msg void OnBtnRtsp();
	afx_msg void OnBtnAudiotalkcodetConfig();
	afx_msg void OnButtonJpegFtp();
	afx_msg void OnButtonAes();
	afx_msg void OnBtnAutoReboot();
	afx_msg void OnCmsParma();
	afx_msg void OnBtnDevAbility();
	afx_msg void OnDlgHoliday();
	afx_msg void OnBtnSecurity();
	afx_msg void OnBtnOnlineUpgrade();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	BOOL CfgSetup();
	BOOL CheckInitParam();
	void CurCfgUpdate();
	inline BOOL ValidIPv6(BYTE *ip);

	DWORD m_dwUseZoom;
	NET_DVR_SCALECFG m_struScale;
	int	m_iChanCount;//preview channel number
	LONG	m_lStartChannel;	
	NET_DVR_DEVICECFG_V40 m_struDeviceCfg;
	NET_DVR_MENU_OUTPUT_MODE m_struMenuOutputMode;
	BOOL	m_bSetDeviceCfg;
	BOOL	m_bSupScale;
	int		m_iSelType;
	int m_iTypeNum;

	BOOL m_bDeviceCfgSet;
	
	int m_iDeviceIndex;
	LONG m_lLoginID;
    LONG m_lChannel;
	NET_DVR_SERVER_TEST_PARA m_struIpTest;
	LONG	m_lIpTest;
	HANDLE	m_hIpTest;
    NET_DVR_DEVICECFG_V50 m_struDeviceCfgV50;
};
