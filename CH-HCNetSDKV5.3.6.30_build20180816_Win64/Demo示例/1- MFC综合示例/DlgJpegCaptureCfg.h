#include "afxwin.h"
#if !defined(AFX_DLGJPEGCAPTURECFG_H__E61CBC05_9E36_4216_85C8_29C78DB66C46__INCLUDED_)
#define AFX_DLGJPEGCAPTURECFG_H__E61CBC05_9E36_4216_85C8_29C78DB66C46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgJpegCaptureCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgJpegCaptureCfg dialog

class CDlgJpegCaptureCfg : public CDialog
{
// Construction
public:
	CDlgJpegCaptureCfg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgJpegCaptureCfg();
// Dialog Data
	//{{AFX_DATA(CDlgJpegCaptureCfg)
	enum { IDD = IDD_DLG_JPEG_CAPTURE_CFG };
	CComboBox	m_comPicRuleType2;
	CComboBox	m_comPicRuleType;
	CComboBox	m_comStreamType;
	CComboBox	m_NameItemCtrl2;
	CComboBox	m_NameItemCtrl;
	CComboBox	m_NameElementCtrl2;
	CComboBox	m_NameElementCtrl;
	CComboBox	m_comboProtocalType2;
	CComboBox	m_comboServerType2;
	CComboBox	m_comboServerType;
	CComboBox	m_comboProtocalType;
	CComboBox	m_UseFTPUpCtrl2;
	CComboBox	m_comboSubSecordDirModeCtrl;
	CComboBox	m_comboSubFirstDirModeCtr;
	CComboBox	m_comboMainSecordDirModeCtrl;
	CComboBox	m_comboMainFirstDirModeCtr;
	CComboBox	m_DirLevelCtrl2;
	CComboBox	m_DirLevelCtrl;
	CComboBox	m_UseFTPUpCtrl;
	CTreeCtrl	m_treeEvent;
	CTreeCtrl	m_treeAlarmin;
	CComboBox	m_comboAlarmIn;
	CComboBox	m_comboEvent;
	CComboBox	m_comboTimePicResolution;
	CComboBox	m_comboTimePicQuality;
	CComboBox	m_comboIntervalEvent;
	CComboBox	m_comboIntervalTime;
	CComboBox	m_comboEventPicResolution;
	CComboBox	m_comboEventPicQuality;
	DWORD	m_dwIntervalEvent;
	DWORD	m_dwIntrvalTime;
	CComboBox m_comboWeekday;
	BOOL m_bCheckAllDay;
	CComboBox m_comboAllDayType;
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
	CComboBox m_comboTimeRecType1;
	CComboBox m_comboTimeRecType2;
	CComboBox m_comboTimeRecType3;
	CComboBox m_comboTimeRecType4;
	CComboBox m_comboCopyWeekday;
	CComboBox m_comboTimeRecType5;
	CComboBox m_comboTimeRecType6;
	CComboBox m_comboTimeRecType7;
	CComboBox m_comboTimeRecType8;
	BOOL	m_bEnableCapture;
	DWORD	m_dwPicSaveDays;
	CString	m_csIP;
	DWORD	m_dwPort;
	CString	m_csPassword;
	CString	m_csUserName;
	CString	m_csIP2;
	DWORD	m_dwPort2;
	CString	m_csPassword2;
	CString	m_csUserName2;
	BYTE	m_byEventCapTimes;
	BOOL	m_bChkAnony;
	CString	m_csMainFirstUserDir;
	CString	m_csMainSecordUserDir;
	CString	m_csSubUserDir;
	BOOL	m_bChkAnony2;
	CString	m_csSubFirstUserDir;
	CString	m_csSubSecordUserDir;
	CString	m_csIPv6;
	CString	m_csIP2v6;
	BOOL	m_bFTPPicType;
	BOOL	m_bFTPPicType2;
	CString	m_Delimiter;
	CString	m_Delimiter2;
	BYTE	m_byPicArchivingInterval;
	BYTE	m_byPicArchivingInterval2;
	CString	m_csPicNamePrefix;
	CString	m_csPicNamePrefix2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgJpegCaptureCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgJpegCaptureCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonUpdate();
	afx_msg void OnSelchangeComboAlarmIn();
	afx_msg void OnSelchangeComboOtherEvent();
	afx_msg void OnClickTreeAlarmin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickTreeEvent(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnSetJpegCapture();
	afx_msg void OnButtonExit();
	afx_msg void OnCaptureDayOk();
	afx_msg void OnSelchangeComboWeekday();
	afx_msg void OnButtonUpdateSched();
	afx_msg void OnBtnSetJpegCaptureSched();
	afx_msg void OnButtonUpdateFtp();
	afx_msg void OnSelchangeComboDirLevel();
	afx_msg void OnSelchangeComboSubDirLevel();
	afx_msg void OnSelchangeComboDirModeOne();
	afx_msg void OnSelchangeComboDirModeTwo();	
	afx_msg void OnSelchangeSubComboDirModeOne();
	afx_msg void OnSelchangeSubComboDirModeTwo();
	afx_msg void OnBtnSetFtp();
	afx_msg void OnBtnDayCopy();
	afx_msg void OnChkAllDay();
	afx_msg void OnButtonAlarminAll();
	afx_msg void OnButtonAlarminClean();
	afx_msg void OnButtonEventAll();
	afx_msg void OnButtonEventClean();
	afx_msg void OnButtonUpdateFtp2();
	afx_msg void OnBtnSetFtp2();
	afx_msg void OnEditchangeComboServertype2();
	afx_msg void OnEditchangeComboServertype();
	afx_msg void OnSelchangeComboServertype();
	afx_msg void OnSelchangeComboServertype2();
	afx_msg void OnButjpegname();
	afx_msg void OnButjpegname2();
	afx_msg void OnSelchangeCombonameitemFtp();
	afx_msg void OnSelchangeCombonameitemFtp2();
	afx_msg void OnPaint();
	afx_msg void OnBtnFtpServerTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lUserID;
    LONG    m_lChannelNum;
	LONG    m_iChanShowNO;
    LONG    m_lChannel;
	int     m_iChanCount;
	DWORD   m_dwDevIndex;
	BOOL GetCompressCfgAbility(DWORD dwIPChanIndex);
	void GetResolutionAbility();
	NET_DVR_COMPRESSIONCFG_ABILITY *m_pCompresscfgAbility;
	void SetTimeResolutionCurSel(DWORD dwData);
	void SetEventResolutionCurSel(DWORD dwData);
    NET_DVR_JPEG_CAPTURE_CFG_V40* m_pStruJpegCapture;
	NET_DVR_SCHED_CAPTURECFG m_struCaptureSched;
	NET_DVR_FTPCFG m_strFtpCfg;
	NET_DVR_FTPCFG m_strFtpCfg2;
	NET_DVR_FTPCFG_V40 m_struFtpCfgV40[2];
	NET_DVR_SERVER_TEST_PARA m_struFtpServerTest;
	LONG	m_lFtpServerTest;
	HANDLE	m_hFtpServerTest;	//FTP服务器测试状态获取线程句柄
	DWORD  m_dwCurAlarmInChanNum;
    DWORD  m_dwCurEventChanNum;
    BOOL   *m_pbAlarmInChan;
    BOOL   *m_pbEventChan;
public:
	void EnableControl(BOOL bEnable);
	void CreateChanTreeAlarmIn(int iIndex, BOOL bSetAll = FALSE, BOOL bClearAll = FALSE);
	void CreateChanTreeEvent(int iIndex, BOOL bSetAll = FALSE, BOOL bClearAll = FALSE);
	void SetFtpV40Info();
	void GetFtpV40Info();
	void SetMainFtpSelDirShow(BOOL bShow = FALSE);
	void SetMainFtpSelSecondDirShow(BOOL bShow = FALSE);
	void SetSubFtpSelDirShow(BOOL bShow = FALSE);
	void SetSubFtpSelSecondDirShow(BOOL bShow = FALSE);
	BOOL CheckInitParam();
	BOOL TimeTest();
	static DWORD WINAPI GetFtpServerTestInfoThread(LPVOID lpArg);
    void setComboTimeRecType(int nComboType, BYTE byCaptureType);
    CComboBox m_comboDelayTime;
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGJPEGCAPTURECFG_H__E61CBC05_9E36_4216_85C8_29C78DB66C46__INCLUDED_)
