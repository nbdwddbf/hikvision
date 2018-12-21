#if !defined(AFX_DLGVQDPLAN_H__F8098539_DD57_441F_A5EE_8C21E00AD0B0__INCLUDED_)
#define AFX_DLGVQDPLAN_H__F8098539_DD57_441F_A5EE_8C21E00AD0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVqdPlan.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVqdPlan dialog

class CDlgVqdPlan : public CDialog
{
// Construction
public:
	CDlgVqdPlan(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVqdPlan)
	enum { IDD = IDD_DLG_VQD_PLAN };
	CComboBox	m_comboPlanMode;
	CComboBox	m_comboWeekday;
	CListCtrl	m_lstVqdPlan;
	CListCtrl	m_lstMonitorInfo;
	int		m_iWperiod;
	DWORD	m_dwStreamIDNum;
	CString	m_csStreamID;
	CString	m_csPlanID;
	BYTE	m_byMintueEnd;
	BYTE	m_byMintueBegin;
	BYTE	m_byHourEnd;
	BYTE	m_byHourBegin;
	BOOL	m_bStreak;
	BOOL	m_bSnow;
	BOOL	m_bSignal;
	BOOL	m_bPtz;
	BOOL	m_bLuma;
	BOOL	m_bFreeze;
	BOOL	m_bChroma;
	BOOL	m_bCheckFlag;
	BOOL	m_bBlur;
	CString	m_csStreamID1;
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
	BOOL	m_bCycleCheck;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVqdPlan)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVqdPlan)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDel();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	afx_msg void OnCheckPtz();
	afx_msg void OnCheckSignal();
	afx_msg void OnCheckBlur();
	afx_msg void OnCheckFreeze();
	afx_msg void OnCheckLuma();
	afx_msg void OnCheckSnow();
	afx_msg void OnCheckStreak();
	afx_msg void OnCheckChroma();
	afx_msg void OnClickListVqdPlan(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnMoitorDel();
	afx_msg void OnBtnMoitorSet();
	afx_msg void OnBtnMoitorAdd();
	afx_msg void OnBtnDelPlan();
	afx_msg void OnSelchangeComboAlarmOutWeekday();
	afx_msg void OnBtnSure();
	afx_msg void OnSelchangeComboPlanmode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG    m_lServerID;
    LONG    m_lChannel;
    int     m_iDevIndex;
	void    ChangSelect();
	NET_DVR_PLAN_VQD_CFG m_struPlanVqdCfg;
	LPNET_DVR_PLAN_VQD_CFG m_pStruPlanVqdCfg;
	LONG	m_lHandle;
	int		m_iStruCount;
	static DWORD WINAPI GetVqdPlanThread(LPVOID lpArg);
	BOOL	m_bGetNext;
	HANDLE	m_hGetInfoThread;
	
	NET_DVR_STREAM_INFO m_struStreamInfo;
	LPNET_DVR_STREAM_INFO m_pStruStreamInfo;
	int		m_iMonitorStruCount;
	void	AddVqdPlanInfoToDlg(LPNET_DVR_PLAN_VQD_CFG lpInter);
	int		m_iRowCount;
	int     m_iMonitorInfoCount;
	LONG    m_lMonitorHandle;
	void    AddMonitorInfoToList(LPNET_DVR_STREAM_INFO lpInter);
	static DWORD WINAPI GetMonitorInfoThread(LPVOID lpArg);
	BOOL	m_bGetMonitorNext;
	void    GetMonitorIDInfo(LPNET_DVR_PLAN_VQD_CFG lpInter);
	BOOL    m_bGetMonitorInfo;
	BOOL    m_bSetMonitorInfo;
	NET_DVR_PLAN_VQD_CFG m_struPlanVqdCfgTemp[64];
	CString m_csListPlanID;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVQDPLAN_H__F8098539_DD57_441F_A5EE_8C21E00AD0B0__INCLUDED_)
