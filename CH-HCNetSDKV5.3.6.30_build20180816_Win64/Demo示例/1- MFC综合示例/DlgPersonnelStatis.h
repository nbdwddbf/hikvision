#if !defined(AFX_DLGPERSONNELSTATIS_H__9644D285_65B4_469A_ACC6_9C185F966606__INCLUDED_)
#define AFX_DLGPERSONNELSTATIS_H__9644D285_65B4_469A_ACC6_9C185F966606__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPersonnelStatis.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPersonnelStatis dialog

class CDlgPersonnelStatis : public CDialog
{
// Construction
public:
	CDlgPersonnelStatis(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPersonnelStatis)
	enum { IDD = IDD_DLG_PERSONNEL_STATIS };
	CComboBox	m_comPerortType;
	CListCtrl	m_lPerStatistics;
	COleDateTime	m_startDate;
	COleDateTime	m_startTime;
	BOOL	m_bAgeUserful;
	BOOL	m_bPersonNumUseful;
	BOOL	m_bSexUseful;
	DWORD	m_dwTerminalNo;
	BOOL	m_bEnableProgram;
	DWORD	m_dwScheduleNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPersonnelStatis)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPersonnelStatis)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGetPersonnelStatisitcs();
	afx_msg void OnBtnCleanHeatmapInfo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	NET_DVR_FACECAPTURE_STATISTICS_COND m_struStatisticsCond;
	NET_DVR_FACECAPTURE_STATISTICS_RESULT m_struStatisticsResult;
	NET_DVR_AGEGROUP_PARAM m_struAgegroupParam;
	NET_DVR_SEXGROUP_PARAM m_struSexgroupParam;
	LONG  m_lChannel;
	LONG m_lHandle;
	long  m_lServerID; // 用户ID
    int   m_iDevIndex; // 设备索引
	BOOL m_bGetNext;

	HANDLE m_hGetInfoThread;

	static DWORD WINAPI GetPersonnelStatisticsThread(LPVOID lpPersonnelStatistics);
	void AddPersonnelStatisticsLst(LPNET_DVR_FACECAPTURE_STATISTICS_RESULT lpInter);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPERSONNELSTATIS_H__9644D285_65B4_469A_ACC6_9C185F966606__INCLUDED_)
