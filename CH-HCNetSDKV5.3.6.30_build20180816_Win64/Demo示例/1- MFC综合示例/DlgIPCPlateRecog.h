#include "afxwin.h"
#if !defined(AFX_DLGIPCPLATERECOG_H__24A6E933_8E87_47D6_B2EF_AA31A36C53E1__INCLUDED_)
#define AFX_DLGIPCPLATERECOG_H__24A6E933_8E87_47D6_B2EF_AA31A36C53E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIPCPlateRecog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgIPCPlateRecog dialog

class CDlgIPCPlateRecog : public CDialog
{
// Construction
public:
	CDlgIPCPlateRecog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgIPCPlateRecog();
// Dialog Data
	//{{AFX_DATA(CDlgIPCPlateRecog)
	enum { IDD = IDD_DLG_IPC_PLATE_RECOG };
	CComboBox	m_cmbGroupNo;
	CTreeCtrl	m_treeChan;
	CTreeCtrl	m_treeAlarmOut;
	CComboBox	m_cmbChannel;
	CComboBox	m_comPicRelateType;
	CComboBox	m_comRelateType;
	CComboBox	m_comboCopyTime;
	CComboBox	m_comboWeekday;
	int		m_iHour11;
	int		m_iHour12;
	int		m_iHour21;
	int		m_iHour22;
	int		m_iHour31;
	int		m_iHour32;
	int		m_iHour41;
	int		m_iHour42;
	int		m_iHour51;
	int		m_iHour52;
	int		m_iHour61;
	int		m_iHour62;
	int		m_iHour71;
	int		m_iHour72;
	int		m_iHour81;
	int		m_iHour82;
	int		m_iMin11;
	int		m_iMin12;
	int		m_iMin21;
	int		m_iMin22;
	int		m_iMin31;
	int		m_iMin32;
	int		m_iMin41;
	int		m_iMin42;
	int		m_iMin51;
	int		m_iMin52;
	int		m_iMin61;
	int		m_iMin62;
	int		m_iMin71;
	int		m_iMin72;
	int		m_iMin81;
	int		m_iMin82;
	BOOL	m_bUploadCenter;
	BYTE	m_byPicQuality;
	DWORD	m_dwPicSize;
	int		m_iSceneID1;
	int		m_iSceneID2;
	int		m_iSceneID3;
	int		m_iSceneID4;
	int		m_iSceneID5;
	int		m_iSceneID6;
	int		m_iSceneID7;
	int		m_iSceneID8;
	CComboBox	m_comPicType;
	BOOL	m_bFTP;
    BOOL	m_bCloud;
	BOOL	m_bChkInvokeAlarmOut;
	BOOL	m_bEMap;
	BOOL	m_bFocus;
	BOOL	m_bPTZ;
	BOOL	m_bInvokeAlarmOut;
	BOOL	m_bMonitor;
	BOOL	m_bJepgCap;
	BOOL	m_bFtp;
	BOOL	m_bVoice;
	BOOL	m_bCenter;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIPCPlateRecog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIPCPlateRecog)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimeOk2();
	afx_msg void OnTimeCopy2();
	afx_msg void OnBtnSetGuard();
	afx_msg void OnBtnGetGuard();
	afx_msg void OnSelchangeComboweekday();
	afx_msg void OnSelchangeComPicType();
	afx_msg void OnBtnGetPicInfo();
	afx_msg void OnBtnSetPicInfo();
	afx_msg void OnBtnTriggerexCfg();
	afx_msg void OnBtnOverlapCfg();
	afx_msg void OnBtnIpcChanCfg();
	afx_msg void OnBtnManualSnapPlate();
	afx_msg void OnBtnCloudStorageCfg();
	afx_msg void OnBtnCompleteRestore();
	afx_msg void OnChkInvokeAlarmOut();
	afx_msg void OnClickTreeTriggerAlarmOut(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickTreeRecordchan(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboGroup();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:

	LONG        m_lServerID; // 用户ID
    int         m_iDevIndex; // 设备索引
	LONG        m_lChannel;
	NET_DVR_GUARD_CFG m_struGuardCfg;
	NET_DVR_GUARD_COND m_struGuardCond;

	BOOL *m_pbAlarmOut;
	BOOL *m_pbRecordChan;

	BOOL F_TimeTest(); 
	void SetAlarmTimeToWnd(NET_DVR_TIME_DETECTION const *pAlarmTime, int nDay);
	void GetAlarmTimeFromWnd(NET_DVR_TIME_DETECTION *pAlarmTime, int nDay);
	void SceneIDToDlg(int nDay, BOOL bSceneToDlg);
	void SetGuardCond();
	void CreateTree();
	void UpdateRelateChanInfo();
	void GetRelateChanInfo(DWORD dwGroupNo);
	

    CComboBox m_comEventTriggerDirection;
    afx_msg void OnBnClickedButtonTrigger();
    BOOL m_bLane;
    CString m_strLaneID;
    CString m_strSavePath;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIPCPLATERECOG_H__24A6E933_8E87_47D6_B2EF_AA31A36C53E1__INCLUDED_)
