#if !defined(AFX_DLGDEVICECFG_H__936FDD35_B34F_4817_B3BE_B05F0E05ADB1__INCLUDED_)
#define AFX_DLGDEVICECFG_H__936FDD35_B34F_4817_B3BE_B05F0E05ADB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDeviceCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDeviceCfg dialog

class CDlgDeviceCfg : public CDialog
{
// Construction
public:
	void GetNetCfg();
	void GetDeviceCfg();
	void EnableDhcp();
	CDlgDeviceCfg(CWnd* pParent = NULL);   // standard constructor
    NET_DVR_DEVICECFG m_struDeviceCfg;//设备参数配置结构体
	NET_DVR_NETCFG_V30 m_struNetCfg;//网络参数配置结构体
	NET_DVR_SCALECFG m_struScaleCfg;//缩放参数配置结构体
	
// Dialog Data
	//{{AFX_DATA(CDlgDeviceCfg)
	enum { IDD = IDD_DIALOG_DEVICE_CFG };
	CComboBox	m_comboMinorScale;
	CComboBox	m_comboMajorScale;
	CComboBox	m_comboNetFace;
	CComboBox	m_comboDeviceType;
	CComboBox	m_comboCycleRec;
	int		m_iHdNum;
	int		m_iAlarmInNum;
	int		m_iAlarmOutNum;
	int		m_iChanNum;
	int		m_iYKQID;
	CString	m_csDeviceName;
	CString	m_csDeviceSerialNo;
	CString	m_csSoftwareVersion;
	CString	m_csHardwareVersion;
	CString	m_csDspVersion;
	CString	m_csPanelVersion;
	int		m_iMtuPort;
	int		m_iHttpPort;
	int		m_iMtu;
	CString	m_csDeviceIP;
	CString	m_csGatewayIP;
	CString	m_csIPMask;
	CString	m_csMacAddr;
	int		m_iMainPort;
	CString	m_csDNSIP1;
	CString	m_csAlarmHostIP;
	int		m_iAlarmHostPort;
	CString	m_csDNSIP2;
	BOOL	m_bChkDhcp;
	CString	m_csMultiIP;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDeviceCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDeviceCfg)
	afx_msg void OnButtonSetNetCfg();
	afx_msg void OnButtonSetDeviceCfg();
	afx_msg void OnChkDhcp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDEVICECFG_H__936FDD35_B34F_4817_B3BE_B05F0E05ADB1__INCLUDED_)
