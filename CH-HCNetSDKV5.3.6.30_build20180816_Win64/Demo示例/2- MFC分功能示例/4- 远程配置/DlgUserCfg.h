#if !defined(AFX_DLGUSERCFG_H__0CC254E4_7A9B_4195_A714_07158DFFF87D__INCLUDED_)
#define AFX_DLGUSERCFG_H__0CC254E4_7A9B_4195_A714_07158DFFF87D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgUserCfg.h : header file
//
#include "config.h"
#include "GeneralDef.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgUserCfg dialog

class CDlgUserCfg : public CDialog
{
// Construction
public:
	CDlgUserCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgUserCfg)
	enum { IDD = IDD_DIALOG_USER_CFG };
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
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgUserCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgUserCfg)
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	
	int		m_iChanCount;//该设备的预览通道数
	LONG	m_lLoginID;
	LONG	m_lStartChannel;
	int		m_iUserIndex;
	CString m_loginname;
	NET_DVR_USER_V30 m_struUserCfg;
	BOOL m_bSuperUserLogin;
	BOOL m_bSetUserParams;
	int m_iDeviceIndex;
	
	int m_iSelLocalRightType;
	int m_iSelNetRightType;
	BOOL m_bLocalChan[MAX_CHANNUM_V30];
	BOOL m_bRemoteChan[MAX_CHANNUM_V30];
	BOOL ShowLocalChanRight(int nChan, BOOL bFlag, BYTE *pRight);
	BOOL ShowNetChanRight(int nChan, BOOL bFlag, BYTE *pRight);
	BOOL CheckInitParam();
	void CurCfgUpdate();
	void CreateLocalTree();
	void CreateRemoteTree();
	BOOL m_bLocalEnable;//是否使本地权限树不响应节点单击
	BOOL m_bRemoteEnable;
	BOOL m_bGetUserParams;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGUSERCFG_H__0CC254E4_7A9B_4195_A714_07158DFFF87D__INCLUDED_)
