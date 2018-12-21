#pragma once
#include "afxwin.h"
#include "time.h"
#include "afxdtctl.h"


// CDlgLocalConfig dialog

class CDlgLocalConfig : public CDialog
{
	DECLARE_DYNAMIC(CDlgLocalConfig)

public:
	CDlgLocalConfig(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgLocalConfig();
	
// Dialog Data

public:	
	//{{AFX_DATA(CDlgLocalConfig)
	enum { IDD = IDD_DLG_LOCAL_CONFIG };
	CComboBox	m_comIPType;
	CComboBox	m_cmLevel;
	CComboBox	m_cmTalkMode;
	CComboBox	m_AllAddressCtrl;
	CComboBox	m_comboSDKLog;
	CComboBox	m_comboBFrame;
	CComboBox	m_comboSoundMode;
	CButton m_chkCyclePlay;
	CButton m_chkUseCard;
	int m_iCycleTime;
	CButton m_chkAutoRecord;
	CButton m_chkCycleRecord;
	CComboBox m_comboRecFirstDisk;
	CComboBox m_comboRecLastDisk;
	int m_iFileInterval;
	CString m_csDownLoadPath;
	CString m_csPicSnatchPath;
	CString m_csLogPath;
	CButton m_chkSysTime;
	CTime m_ctimeCheckDeviceTime;
	BOOL m_bCyclePlay;
	BOOL m_bAutoRecord;
	BOOL m_bCycleRecord;
	BOOL m_bUseCard;
	BOOL m_bChkDeviceTime;
	CDateTimeCtrl m_ctCheckTime;
	CComboBox m_comboVideoFormat;
	BOOL	m_bChkNoDecode;
	BOOL	m_bBlock;
	int		m_iTimeOut;
	CString	m_strSdklog;
	BOOL	m_bWriteSdkLog;
	BOOL	m_bReconnect;
	int		m_iListenPort;
	UINT	m_wMaxTcpPort;
	UINT	m_wMinTcpPort;
	UINT	m_wMaxUdpPort;
	UINT	m_wMinUdpPort;
	UINT	m_dwMaxMemBlocks;
	UINT	m_dwReleaseInterval;
	UINT	m_dwPreviewTimeout;
	UINT	m_dwVodTimeout;
	UINT	m_dwAlarmTimeout;
	UINT	m_dwOtherModuleTimeout;
	BOOL	m_bUseAbilityParse;
	BOOL	m_bRtpSort;
	UINT	m_dwMaxBuffNum;
	int		m_iConnectTimeout;
	UINT	m_dwNetFailNum;
	UINT	m_dwHeartCheckTime;
	CString	m_csIPV6;
	//}}AFX_DATA

	LONG m_lListenHandle;



	//{{AFX_VIRTUAL(CDlgLocalConfig)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgLocalConfig)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnSelectDownLoadPath();
	afx_msg void OnBnClickedLocalOk();
	afx_msg void OnBnClickedChkCyclePlay();
	afx_msg void OnBnClickedChkAutoRecord();
	afx_msg void OnBnClickedBtnSetTime();
	afx_msg void OnBnClickedBtnSelectPicPath();
	afx_msg void OnBnClickedBtnSelectLogPath();
	afx_msg void OnBnClickedChkSystime();
	afx_msg void OnBnClickedChkUseCard();
	afx_msg void OnSelchangeComboSoundMode();
	afx_msg void OnButtonStartListen();
	afx_msg void OnButtonStopListen();
	afx_msg void OnButtonRefrush();
	afx_msg void OnBtnSelectSdklogPath();
	afx_msg void OnBtnBindIp();
	afx_msg void OnButtonSetSdkCfg();
	afx_msg void OnButtonGetSdkCfg();
	afx_msg void OnBtnSetModuleTimeout();
	afx_msg void OnBtnGetModuleTimeout();
	afx_msg void OnCheckUseAbilityParse();
	afx_msg void OnSelchangeComboTalkMode();
	afx_msg void OnSelchangeComboIptype();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	
	CString GetDirectoryPath();
	NET_DVR_LOCAL_CHECK_DEV m_struLoaclCheckDev;
	NET_DVR_LOCAL_STREAM_CALLBACK_CFG struStreamCallBackCfg;
	int m_dwObjectRelease;
	int m_dwSDKLogNum;
	afx_msg void OnBnClickedBtnReleaseSdkMempool();
	CComboBox m_comboPlayBackEndFlag;
	afx_msg void OnBnClickedBtnCallback();
    CString m_sPTProxyIP;
    DWORD m_dwPTProxyPort;
    afx_msg void OnBnClickedBtnSetProxy();
    CComboBox m_cmbExceptionCBType;
    BOOL m_bChkResumeEnable;
    int m_iReusmeTimeout;
    afx_msg void OnBnClickedCheckOldJsonCallback();
    BOOL m_bOldJsonCallback;
    BOOL m_bJsonAlarmPictureSeparate;
    afx_msg void OnBnClickedCheckJsonAlarmPictureSeparate();
};
