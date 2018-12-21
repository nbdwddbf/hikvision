#if !defined(AFX_DLGWIRELESSDIAL_H__5A69C382_5614_4695_91A1_00DBE42A5DD9__INCLUDED_)
#define AFX_DLGWIRELESSDIAL_H__5A69C382_5614_4695_91A1_00DBE42A5DD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWirelessDial1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgWirelessDial dialog

class CDlgWirelessDial : public CDialog
{
// Construction
public:
	CDlgWirelessDial(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgWirelessDial)
	enum { IDD = IDD_DLG_WIRELESS_DIAL };
	CComboBox	m_comboCopyTime;
	CComboBox	m_comboWeekday;
	CComboBox	m_cmbVerifProtocol;
	CComboBox	m_cmbUIMStatus;
	CComboBox	m_cmbRealtimeMode;
	CComboBox	m_cmbNetworkMode;
	CComboBox	m_cmbDialMode;
	BOOL	m_bEnableWirelessDial;
	CString	m_strAPNName;
	CString	m_strDialStatus;
	CString	m_strDialNum;
	CString	m_strDNSAddr;
	CString	m_strGatewayAddr;
	CString	m_strIPAddr;
	CString	m_strIPMask;
	int		m_nMTU;
	int		m_nNetworkCardNo;
	int		m_nOffTime;
	CString	m_strPassword;
	int		m_nSignalQuality;
	CString	m_strUIMCardNum;
	CString	m_strUserName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWirelessDial)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
public:
    int m_iHour11;
    int m_iMin11;
    int m_iHour12;
    int m_iMin12;
    int m_iHour21;
    int m_iMin21;
    int m_iHour22;
    int m_iMin22;
    int m_iHour31;
    int m_iMin31;
    int m_iHour32;
    int m_iMin32;
    int m_iHour41;
    int m_iMin41;
    int m_iHour42;
    int m_iMin42;
    int m_iHour51;
    int m_iMin51;
    int m_iHour52;
    int m_iMin52;
    int m_iHour61;
    int m_iMin61;
    int m_iHour62;
    int m_iMin62;
    int m_iHour71;
    int m_iMin71;
    int m_iHour72;
    int m_iMin72;
    int m_iHour81;
    int m_iMin81;
    int m_iHour82;
    int m_iMin82;
    
    NET_DVR_WIRELESSDIAL_CFG    m_struWirelessDialCfg;
    NET_DVR_WIRELESSDIAL_STATUS m_struWirelessDialStatus;
    NET_DVR_WIRELESSDIAL_SCHEDULE   m_struWirelessDialSchedule;
    char m_szStatusBuf[ISAPI_STATUS_LEN];
    LONG m_lLoginID;
    int  m_iDeviceIndex;

    void SetItemData(CComboBox &combo, char* szData);
    BOOL ValidIPv6(BYTE *ip);
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWirelessDial)
	afx_msg void OnBtnWirelessDialRefresh();
	afx_msg void OnBtnWirelessDialSave();
	afx_msg void OnBtnStatusRefresh();
	afx_msg void OnBtnConnect();
	afx_msg void OnBtnDisconnect();
	afx_msg void OnBtnDialSchedule();
	afx_msg void OnBtnDialScheduleRefresh();
	afx_msg void OnBtnAlarmInTimeOk();
	afx_msg void OnBtnAlarminTimeCopy();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboAlarminWeekday();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    CString m_strNetAPN;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWIRELESSDIAL_H__5A69C382_5614_4695_91A1_00DBE42A5DD9__INCLUDED_)
