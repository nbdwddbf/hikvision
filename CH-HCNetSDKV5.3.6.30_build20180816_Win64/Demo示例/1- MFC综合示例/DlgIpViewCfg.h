#if !defined(AFX_DLGIPVIEWCFG_H__F64D375D_7768_48DC_990E_F2F0EA337A08__INCLUDED_)
#define AFX_DLGIPVIEWCFG_H__F64D375D_7768_48DC_990E_F2F0EA337A08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIpViewCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgIpViewCfg dialog

class CDlgIpViewCfg : public CDialog
{
// Construction
public:
	CDlgIpViewCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgIpViewCfg)
	enum { IDD = IDD_DLG_IP_VIEW_CFG };
	CComboBox	m_comboAudioPacketLength2;
	CComboBox	m_comboAudioPacketLength;
	CComboBox	m_comboAudioEncodePrio2;
	CComboBox	m_comboAudioEncodePrio1;
	BOOL	m_bChkAutoRes;
	BOOL	m_bChkUseAlarm1;
	BOOL	m_bChkUseAlarm2;
	CString	m_strAlarm1;
	CString	m_strAlarm2;
	BYTE	m_byResTime;
	CComboBox	m_comboLoginState;
	BOOL	m_bChkAutoLogin;
	CString	m_strDevName;
	CString	m_strIP;
	CString	m_strLocalNum;
	DWORD	m_dwLocalPort;
	BYTE	m_byLoginCycle;
	DWORD	m_dwPort;
	CString	m_strUserName;
	CString	m_strUserPwd;
	BYTE	m_byRingType;
	BYTE	m_byRingVolume;
	BYTE	m_byRingInVolume;
	BYTE	m_byRingOutVolume;
	short	m_wRtpPort;
	DWORD	m_dwPreviewDelayTime;
	DWORD	m_dwDecibel;
	BOOL	m_bAudioLimitAlarm;
	BOOL	m_bButtonDownAlarm;
    CComboBox m_comboAddrType;
    CString  m_csDomainName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIpViewCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIpViewCfg)
	afx_msg void OnBtnSetIpViewCallCfg();
	afx_msg void OnBtnGetIpViewCallCfg();
	afx_msg void OnBtnGetSipCfg();
	afx_msg void OnBtnSetSipCfg();
	afx_msg void OnBtnSetIpViewDevCfg();
	afx_msg void OnBtnGetIpViewDevCfg();
	afx_msg void OnBtnSetAudioParmCfg();
	afx_msg void OnBtnGetAudioParmCfg();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnAudioLimitCfg();
	afx_msg void OnBtnButtonDownCfg();
	afx_msg void OnBtnSetIpViewAlarmCfg();
	afx_msg void OnBtnGetIpViewAlarmCfg();
	afx_msg void OnChkAudioLimitAlarm();
	afx_msg void OnChkButtonDownAlarm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG m_lServerID;
	DWORD m_dwDevIndex;
	NET_DVR_IP_VIEW_CALL_CFG m_struIpViewCallCfg;
    NET_DVR_SIP_CFG_V50 m_struSipCfg;
	NET_DVR_IP_VIEW_DEVCFG m_struIpViewDevCfg;
	NET_DVR_IP_VIEW_AUDIO_CFG m_struIpViewAudioCfg;
	NET_IPC_BUTTON_DOWN_ALARM_CFG m_struButtonDownAlarmCfg;
	NET_IPC_AUDIO_LIMIT_ALARM_CFG m_struAudioLimitAlarmCfg;
    CString m_csSipProxyDomain;
    CString m_csSipStunDomain;
    CString m_csProxyIP;
    CString m_csStunIP;
    DWORD m_dwProxyPort;
    DWORD m_dwStunPort;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIPVIEWCFG_H__F64D375D_7768_48DC_990E_F2F0EA337A08__INCLUDED_)
