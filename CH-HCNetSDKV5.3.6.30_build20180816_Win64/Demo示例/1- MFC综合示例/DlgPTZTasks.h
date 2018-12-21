#if !defined(AFX_DLGPTZTASKS_H__984E849A_C298_4ECA_85C9_6B54301456C4__INCLUDED_)
#define AFX_DLGPTZTASKS_H__984E849A_C298_4ECA_85C9_6B54301456C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPTZTasks.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPTZTasks dialog

class CDlgPTZTasks : public CDialog
{
// Construction
public:
	CDlgPTZTasks(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPTZTasks)
	enum { IDD = IDD_DLG_PTZTASKS };
	CComboBox	m_comboAction9;
	CComboBox	m_comboAction8;
	CComboBox	m_comboAction7;
	CComboBox	m_comboAction6;
	CComboBox	m_comboAction5;
	CComboBox	m_comboAction4;
	CComboBox	m_comboAction3;
	CComboBox	m_comboAction2;
	CComboBox	m_comboAction10;
	CComboBox	m_comboAction1;
	int		m_iParkTime;
	BOOL	m_bEnable;
	int		m_iMin91;
	int		m_iMin92;
	int		m_iMin101;
	int		m_iMin102;
	int		m_iHour92;
	int		m_iHour91;
	int		m_iHour102;
	int		m_iHour101;
	int		m_iChidAction1;
	int		m_iChidAction10;
	int		m_iChidAction2;
	int		m_iChidAction3;
	int		m_iChidAction4;
	int		m_iChidAction5;
	int		m_iChidAction6;
	int		m_iChidAction7;
	int		m_iChidAction8;
	int		m_iChidAction9;
	int		m_iHour11;
	int		m_iMin11;
	int		m_iHour12;
	int		m_iMin12;
	int		m_iHour21;
	int		m_iMin21;
	int		m_iHour22;
	int		m_iMin22;
	int		m_iHour31;
	int		m_iMin31;
	int		m_iHour32;
	int		m_iMin32;
	int		m_iHour41;
	int		m_iMin41;
	int		m_iHour42;
	int		m_iMin42;
	int		m_iHour51;
	int		m_iMin51;
	int		m_iHour52;
	int		m_iMin52;
	int		m_iHour61;
	int		m_iMin61;
	int		m_iHour62;
	int		m_iMin62;
	int		m_iHour71;
	int		m_iMin71;
	int		m_iHour72;
	int		m_iMin72;
	int		m_iHour81;
	int		m_iMin81;
	int		m_iHour82;
	int		m_iMin82;
	CComboBox	m_comboWeekday;
	CComboBox	m_comboCopyTime;
	//}}AFX_DATA

public:
	LONG m_lServerID;
	int  m_iDevIndex;
	int  m_iChanNo;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPTZTasks)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPTZTasks)
	afx_msg void OnBtnAlarmInTimeOk();
	afx_msg void OnCbnSelchangeComboAlarminWeekday();
	afx_msg void OnBtnAlarminTimeCopy();
	afx_msg void OnBtnGettasks();
	afx_msg void OnBtnSettask();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:

	NET_DVR_SCHEDTIME m_struAlarmTime[MAX_DAYS][MAX_SCH_TASKS_NUM]; 

	NET_DVR_TIME_TASK m_struTimeTask;

protected:
	BOOL TimeTest();
	void ShowOtherData();
	void SaveOtherData();
	virtual BOOL OnInitDialog();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPTZTASKS_H__984E849A_C298_4ECA_85C9_6B54301456C4__INCLUDED_)
