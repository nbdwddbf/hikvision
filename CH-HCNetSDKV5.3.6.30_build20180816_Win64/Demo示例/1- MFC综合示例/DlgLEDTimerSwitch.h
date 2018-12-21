#if !defined(AFX_DLGLEDTIMERSWITCH_H__5EE6C49F_DF91_464B_84FB_EA75368D4205__INCLUDED_)
#define AFX_DLGLEDTIMERSWITCH_H__5EE6C49F_DF91_464B_84FB_EA75368D4205__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLEDTimerSwitch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLEDTimerSwitch dialog
typedef enum
{
	LED_TIME1 = 0,		//定时时间1
	LED_TIME2	,		//定时时间2
	LED_TIME3	,		//定时时间3
}LED_CTRL_TIME_TYPE;

class CDlgLEDTimerSwitch : public CDialog
{
// Construction
public:
	CDlgLEDTimerSwitch(CWnd* pParent = NULL);   // standard constructor

	int		m_iDeviceIndex;
	long	m_lUserID;
	NET_DVR_LED_SWITCH_TIME m_struSwitchTime;
	void GetTime(INT iTimeIndex);
	BOOL CheckAndGetTime();
// Dialog Data
	//{{AFX_DATA(CDlgLEDTimerSwitch)
	enum { IDD = IDD_DLG_ALARMHOST_LED_TIMER_SWITCH };
		// NOTE: the ClassWizard will add data members here
	BOOL	m_chTime1;
	BOOL	m_chTime2;
	BOOL	m_chTime3;
	COleDateTime	m_time1Off;
	COleDateTime	m_time1On;
	COleDateTime	m_time2Off;
	COleDateTime	m_time2On;
	COleDateTime	m_time3Off;
	COleDateTime	m_time3On;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLEDTimerSwitch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLEDTimerSwitch)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckTime1();
	afx_msg void OnCheckTime2();
	afx_msg void OnCheckTime3();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLEDTIMERSWITCH_H__5EE6C49F_DF91_464B_84FB_EA75368D4205__INCLUDED_)
