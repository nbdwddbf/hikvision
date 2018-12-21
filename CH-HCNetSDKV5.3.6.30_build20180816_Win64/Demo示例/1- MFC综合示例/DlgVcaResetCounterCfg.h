#if !defined(AFX_DLGVCARESETCOUNTERCFG_H__0F269373_9C43_43E9_86D3_217173BB5A15__INCLUDED_)
#define AFX_DLGVCARESETCOUNTERCFG_H__0F269373_9C43_43E9_86D3_217173BB5A15__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaResetCounterCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaResetCounterCfg dialog

class CDlgVcaResetCounterCfg : public CDialog
{
// Construction
public:
	CDlgVcaResetCounterCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaResetCounterCfg)
	enum { IDD = IDD_DLG_VCA_RESET_COUNTER_CFG };
	CComboBox	m_comMode;
	CComboBox	m_comboWeekday;
	CComboBox	m_comboCopyTime;
	BOOL	m_bChkResetCounter;
	BYTE	m_byResetTimeHour;
	BYTE	m_byResetTimeMin;
	BYTE	m_byResetTimeSec;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaResetCounterCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaResetCounterCfg)
	afx_msg void OnTimeOk2();
	afx_msg void OnTimeCopy2();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnSelchangeCombocopytime();
	afx_msg void OnSelchangeComboweekday();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	long  m_lServerID; // 用户ID
    int   m_iDevIndex; // 设备索引
	int   m_iVcaChan;     // 当前智能通道 开始默认为0 
    BOOL  m_bHideGetCtrl;
	NET_DVR_RESET_COUNTER_CFG m_struResetCounterCfg;

	BOOL F_TimeTest(); 
	void SetTimeToWnd(NET_DVR_TIME_EX const *pTime);
	void GetTimeFromWnd(NET_DVR_TIME_EX *pTime);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCARESETCOUNTERCFG_H__0F269373_9C43_43E9_86D3_217173BB5A15__INCLUDED_)
