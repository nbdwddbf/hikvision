#if !defined(AFX_DLGDIAGNOSTICSERVER_H__0BBFD987_F964_4B6F_B957_8FF0F9BAA5C9__INCLUDED_)
#define AFX_DLGDIAGNOSTICSERVER_H__0BBFD987_F964_4B6F_B957_8FF0F9BAA5C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDiagnosticServer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDiagnosticServer dialog

class CDlgDiagnosticServer : public CDialog
{
// Construction
public:
	CDlgDiagnosticServer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDiagnosticServer)
	enum { IDD = IDD_DLG_DIAGNOSTIC_SERVER };
	CStatic	m_VqdPic;
	CComboBox	m_comboStatus;
	short	m_sTotalPlanNum;
	short	m_sRemainAbility;
	short	m_sAbility;
	BYTE	m_byCPULoad;
	BYTE	m_byMEMLoad;
	BYTE	m_minuteBegin;
	BYTE	m_mintueEnd;
	DWORD	m_dwPlanNum;
	short	m_sWperiod;
	BOOL	m_bBlur;
	BOOL	m_bCheckFlag;
	BOOL	m_bChroma;
	BOOL	m_bFreeze;
	BOOL	m_bLuma;
	BOOL	m_bPtz;
	BOOL	m_bSignal;
	BOOL	m_bSnow;
	BOOL	m_bStreak;
	BYTE	m_hourBegin;
	BYTE	m_hourEnd;
	CString	m_csVqdStreamID;
	CString	m_csVqdUrl;
	DWORD	m_dwPicLength;
	int		m_iCurPlanNum;
	CString	m_csIP;
	DWORD	m_dwPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDiagnosticServer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDiagnosticServer)
	afx_msg void OnBtnStatusGet();
	afx_msg void OnBtnDataserverManagment();
 	afx_msg void OnBtnVqdResultGet();
	afx_msg void OnBtnVqdPlan();
	afx_msg void OnBtnMonitorInfo();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnSceneChangeUpdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG    m_lServerID;
    int     m_iDevIndex;
	LONG    m_lChannel;
	LONG    m_lPlanCount;

	NET_DVR_QUERY_STATUS m_struQueryStatus;
	NET_DVR_NETCFG_V30 m_struNetCfgV30;
	//NET_DVR_STREAMID_PLAN_CFG g_struStreamIDPlanCfg[64];

	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDIAGNOSTICSERVER_H__0BBFD987_F964_4B6F_B957_8FF0F9BAA5C9__INCLUDED_)
