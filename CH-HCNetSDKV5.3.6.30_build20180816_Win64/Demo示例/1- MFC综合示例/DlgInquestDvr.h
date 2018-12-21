#if !defined(AFX_DLGINQUESTDVR_H__D18907B0_9EDC_4926_9E10_CF31C91B5B37__INCLUDED_)
#define AFX_DLGINQUESTDVR_H__D18907B0_9EDC_4926_9E10_CF31C91B5B37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInquestDvr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInquestDvr dialog


class CDlgInquestDvr : public CDialog
{
// Construction
public:
	CDlgInquestDvr(CWnd* pParent = NULL);   // standard constructor

	DWORD   m_dwDeviceIndex; //Current device index
	LONG	m_lLoginID;      //User login ID
	LONG	m_lStartChannel; //start channel number, usually 1
	DWORD	m_bEnc[MAX_CHANNUM_V30];  //Is the stream of the channel be encrypted
	BOOL	m_bKeyState;              //Is the stream encrypt key be setted
	NET_DVR_INQUEST_CDRW_CFG    m_strCdrwCfg;   //Cdrw config
	NET_DVR_INQUEST_PIP_STATUS_V40  m_strPIPStatus; //PIP config
	NET_DVR_INQUEST_CDRW_STATUS m_strCdrwStatus;//cdrw status
	NET_DVR_BACKUP_TIME_PARAM m_struBackupTimeParam;//backup time parameters
	NET_DVR_INQUEST_ROOM m_strInquestRoom;//Inquest room command
	NET_DVR_INQUEST_SYSTEM_INFO m_strSystemInfo;//Inquest System Info
	NET_DVR_INQUEST_DEVICE_VERSION m_strDeviceVersion;//Inquest Device Version
	BOOL m_bBackuping;//be backuping or not
    LONG m_lBackupHandle;//backup handle
	HANDLE m_hBackupThread;//backup thread handle

// Dialog Data
	//{{AFX_DATA(CDlgInquestDvr)
	enum { IDD = IDD_DLG_INQUEST_DVR };
	CComboBox	m_cmbInitCD;
	CComboBox	m_cmbHashCheckCD;
	CComboBox	m_comboShowMode;
	CComboBox	m_cmbInquestChannelResolution;
	CComboBox	m_cmbCalcMode;
	CComboBox	m_cmbInquestTime;
	CComboBox	m_cmbInquestRoomSys;
	CComboBox	m_comboResolution;
	CComboBox	m_comboInquestRoom;
	CComboBox	m_comboReocrdMode;
	CComboBox	m_comboSensorNum;
	CComboBox	m_comboSensorType;
	CComboBox	m_comboWorkMode;
	CComboBox	m_comboPIPMode;
	CComboBox	m_comboChanTime;
	CComboBox	m_comboPIPNum;
	CComboBox	m_comboChanSecret;
	CComboBox	m_comboChanCdrw;
	CComboBox	m_comboCdrwType;
	CComboBox	m_comboCdrwState;
	CComboBox	m_comboCdrwNumber;
	CComboBox	m_comboCdrwMode;
	CComboBox	m_comboCdrwInterval;
	BOOL	m_bCancelWrite;
	BOOL	m_bEncrypt;
	BOOL	m_bPause;
	BOOL	m_bCheckCD1;
	BOOL	m_bCheckCD2;
	BOOL	m_bCheckCD3;
	BOOL	m_bCheckCD4;
	BOOL	m_bCDStateEnable;
	BOOL	m_bKeySet;
	CTime	m_cdDateStart;
	CTime	m_ctDateStop;
	CTime	m_ctTimeStart;
	CTime	m_cTimeStop;
	CString	m_csCDName;
	CString	m_csEncKey;
	int		m_iBackChan;
	int		m_iShowChan;
	int		m_iPIPX;
	int		m_iPIPY;
	BOOL	m_bHDException;
	BOOL	m_bCdrwStart;
	int		m_iChanPIP;
	int		m_iCdrwNum;
	CString	m_csMessage;
	short	m_wSensorAddr;
	BOOL	m_bChkYouli;
	BOOL	m_bChkMile;
	BOOL	m_bChkLeicai;
	DWORD	m_dwFreeSpace;
	DWORD	m_dwVolumn;
	CString	m_csDeviceVersion;
	BYTE	m_byAudioThreshold;
	CString	m_strDiskName;
	short	m_wPipHeight;
	short	m_wWidth;
	BOOL	m_bAudoDelRecord;
	UINT	m_dwTimeLeft;
	BYTE	m_byCDType;
	CTime	m_ctInquestDateStart;
	CTime	m_ctInquestTimeStart;
	UINT	m_iPipCount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInquestDvr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:


	// Generated message map functions
	//{{AFX_MSG(CDlgInquestDvr)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonExit();
	afx_msg void OnSelchangeComboChanSecret();
	afx_msg void OnSelchangeComboChanCdrw();
	afx_msg void OnButtonCdrwOk();
	afx_msg void OnButtonCdrwSet();
	afx_msg void OnButtonSetSecretKey();
	afx_msg void OnButtonSetEncState();
	afx_msg void OnButtonStartCdrw();
	afx_msg void OnButtonStopCdrw();
	afx_msg void OnButtonCdrwTime();
	afx_msg void OnButtonUpdate();
	afx_msg void OnButtonUpdateState();
	afx_msg void OnSelchangeComboCdrwNumber();
	afx_msg void OnButtonFile();
	afx_msg void OnSelchangeComboPipNum();
	afx_msg void OnButtonPipOk();
	afx_msg void OnButtonPipSet();
	afx_msg void OnSelchangeComboInquestRoom();
	afx_msg void OnButtonSendMessage();
	afx_msg void OnSelchangeComboSensor();
	afx_msg void OnButtonSensorOk();
	afx_msg void OnButtonSetupSystem();
	afx_msg void OnButtonInquestEvent();
	afx_msg void OnButtonSetSdkSecret();
	afx_msg void OnButtonInquestRoomSysOk();
	afx_msg void OnSelchangeComboInquestRoomSys();
	afx_msg void OnSelchangeComboCalcMode();
    afx_msg void OnButtonPauseCdrw();
	afx_msg void OnButtonResumeeCdrw();
	afx_msg void OnBtnInqUserRight();
	afx_msg void OnBtnMixAudioin();
	afx_msg void OnBtnInquestCaseInfo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
	void initDialog(); 	
	void CheckInitPara(); 

public:
	LONG m_hRemoteConfig;
	HANDLE m_hThread;
	BOOL m_bStatusGeting;
    BOOL m_bAutoOpenTray;
    afx_msg void OnBnClickedButtonTrayConfig();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINQUESTDVR_H__D18907B0_9EDC_4926_9E10_CF31C91B5B37__INCLUDED_)
