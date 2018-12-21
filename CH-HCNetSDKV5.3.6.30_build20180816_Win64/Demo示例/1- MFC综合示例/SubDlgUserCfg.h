#pragma once
#include "afxwin.h"


// CSubDlgUserCfg dialog

class CSubDlgUserCfg : public CDialog
{
	DECLARE_DYNAMIC(CSubDlgUserCfg)

public:
	CSubDlgUserCfg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubDlgUserCfg();

// Dialog Data
public:
	//{{AFX_DATA(CSubDlgUserCfg)
	enum { IDD = IDD_SUB_DLG_USER_CFG };
	CComboBox	m_comboPriority;
	CTreeCtrl	m_treeRemoteChan;
	CTreeCtrl	m_treeLocalChan;
	CComboBox m_comboUserSel;
	CString m_csUserName;
	CString m_csUserPwd;
	CString m_csVerifyPwd;
	CString m_csUserIP;
	CString m_csMacAddr1;
	CString m_csMacAddr2;
	CString m_csMacAddr3;
	CString m_csMacAddr4;
	CString m_csMacAddr5;
	CString m_csMacAddr6;
	BOOL m_bChkLocalPTZCtrl;
	BOOL m_bChkLocalRecManul;
	BOOL m_bChkLocalSetParam;
	BOOL m_bChkLocalShowStat;
	BOOL m_bChkLocalHighOperation;
	BOOL m_bChkLocalPlayBack;
	BOOL m_bChkRemotePTZCtrl;
	BOOL m_bChkRemoteRecManul;
	BOOL m_bChkRemoteSetParam;
	BOOL m_bChkRemoteShowStat;
	BOOL m_bChkRemoteHighOperation;
	BOOL m_bChkRemotePlayBack;
	BOOL m_bChkRemoteVoiceTalk;
	BOOL m_bChkRemoteAlarm;
	BOOL m_bChkRemoteLocalOut;
	BOOL m_bChkRemoteRecRight;
	BOOL m_bChkRemoteUserPtz;
	BOOL m_bChkRemotePreview;
	BOOL m_bChkRemoteSerialCtrl;
	BOOL m_bChkLocalBackup;
	CComboBox m_comboNetRightType;
	CComboBox m_comboLocalRightType;
	BOOL	m_bChkLocalCameraManage;
	BOOL	m_bChkLocalReboot;
	BOOL	m_bChkNetCameraManage;
	BOOL	m_bChkNetReboot;
	BOOL	m_bAlarmOn;
	BOOL	m_bBypass;
	BOOL	m_bAlarmOff;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CSubDlgUserCfg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CSubDlgUserCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboUserSel();
	afx_msg void OnBnClickedBtnUserOk();
	afx_msg void OnCbnSelchangeComboLocalRightType();
	afx_msg void OnBnClickedChkLocalRecManual();
	afx_msg void OnBnClickedChkLocalPtzCtrl();
	afx_msg void OnBnClickedChkLocalBackup();
	afx_msg void OnBnClickedBtnLocalChanOk();
	afx_msg void OnBnClickedBtnRemoteChanOk();
	afx_msg void OnBnClickedChkRemoteRecManual();
	afx_msg void OnBnClickedChkRemotePtzCtrl();
	afx_msg void OnBnClickedChkLocalPlayBack();
	afx_msg void OnBnClickedChkNetPreview();
	afx_msg void OnBnClickedChkRemotePlayBack();
	afx_msg void OnCbnSelchangeComboRemoteRightType();
	afx_msg void OnClickTreeLocalChan(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickTreeRemoteChan(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg void OnButtonSyncIpcPasswd();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	
	int		m_iChanCount;//device preview channel number
	LONG	m_lLoginID;
	LONG	m_lStartChannel;
	int		m_iUserIndex;
	CString m_loginname;
    NET_DVR_USER_V51* m_pStruUserCfg_V51;
    NET_DVR_USER_V51 m_StruUserCfg_V51;
	BOOL m_bSuperUserLogin;
	BOOL m_bSetUserParams;
	int m_iDeviceIndex;

	int m_iSelLocalRightType;
	int m_iSelNetRightType;
	BOOL* m_pbLocalChan;
	BOOL* m_pbRemoteChan;

	BOOL ShowLocalChanRight(int nChan, BOOL bFlag, BYTE *pRight);
	BOOL ShowNetChanRight(int nChan, BOOL bFlag, BYTE *pRight);
	BOOL CheckInitParam();
	BOOL CfgSetup();
	void CurCfgUpdate();
	void CreateLocalTree();
	void CreateRemoteTree();
	void SaveLastLocalChan();  
	void SaveLastRemoteChan(); 
	BOOL m_bLocalEnable;//local user right list not invoke by click on node
	BOOL m_bRemoteEnable;
	BOOL m_bGetUserParams;
    BOOL m_bMaterial;
    BOOL m_bSchedule;
    BOOL m_bProgramAdd;
    BOOL m_bPlay;
    BOOL m_bShop;
    BOOL m_bTerminal;
    BOOL m_bScheduleAdd;
    BOOL m_bMaterialUpload;
    BOOL m_bProgram;
    CString m_sloginPassword;
    BOOL m_bChkLocalPreview;
    afx_msg void OnBnClickedChkLocalPreview();
};
