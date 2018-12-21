#pragma once
#include "afxwin.h"
#include "config.h"


// CDlgRemoteHideAlarm dialog

class CDlgRemoteHideAlarm : public CDialog
{
	DECLARE_DYNAMIC(CDlgRemoteHideAlarm)

public:
	CDlgRemoteHideAlarm(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgRemoteHideAlarm();

// Dialog Data

public:

	//{{AFX_DATA(CDlgRemoteHideAlarm)
	enum { IDD = IDD_DLG_REMOTE_HIDE_ALARM };
	CTreeCtrl	m_treeAlarmOut;
	CComboBox m_comboHideAlarmSensitive;
	CStatic m_picHideAlarm;
	BOOL m_bChkMonitorAlarm;
	BOOL m_bChkAudioAlarm;
	BOOL m_bChkReportCenter;
	BOOL m_bChkInvokeAlarmOut;
	BOOL m_bChkInvokeJpegCapture;
	CComboBox m_comboWeekday;
	CComboBox m_comboDayCopy;
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
	BOOL m_bChkHideAlarmShow;
	BOOL m_bChkHideAlarmSet;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CDlgRemoteHideAlarm)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteHideAlarm)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);	
	afx_msg void OnBnClickedBtnHaDayOk();
	afx_msg void OnBnClickedChkHideAlarmShow();
	afx_msg void OnBnClickedChkHideAlarmSet();
	afx_msg void OnBnClickedBtnHideAlarmOk();
	afx_msg void OnBnClickedBtnHideAlarmExit();
	afx_msg void OnBnClickedChkHaInvokeAlarmOut();
	afx_msg void OnBnClickedBtnHaDayCopy();
	afx_msg void OnCbnSelchangeComboHaWeekday();
	afx_msg void OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
public:

	int		m_iChanShowNum;
	LONG	m_lLoginID;
	BOOL	m_bDrawdetect;
	LONG	m_lPlayHandle;
	DWORD	m_dwDevIndex;
	DWORD	m_dwAlarmOutNum;
	BOOL	m_bAlarmOut[MAX_ALARMOUT_V30];
	BOOL	TimeTest();
	void	CreateTree(void);
};
