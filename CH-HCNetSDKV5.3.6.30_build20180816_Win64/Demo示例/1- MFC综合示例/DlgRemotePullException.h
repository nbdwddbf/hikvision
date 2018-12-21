#pragma once
#include "afxwin.h"


// CDlgRemotePullException dialog

class CDlgRemotePullException : public CDialog
{
	DECLARE_DYNAMIC(CDlgRemotePullException)

public:
	CDlgRemotePullException(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgRemotePullException();

// Dialog Data
	


public:


	//{{AFX_DATA(CDlgRemotePullException)
	enum { IDD = IDD_DLG_REOMTE_PULLEXCEPTION };
	CTreeCtrl	m_treeAlarmOut;
	BOOL m_bChkMonitorAlarm;
	BOOL m_bChkAudioAlarm;
	BOOL m_bChkReportCenter;
	BOOL m_bChkInvokeAlarmOut;
	CComboBox m_comboWeekday;
	CComboBox m_comboCopyDay;
	BOOL m_bChkInvokeJpegCapture;
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
	BOOL	m_bCheckPull;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CDlgRemotePullException)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgRemotePullException)
	virtual BOOL OnInitDialog();	
	afx_msg void OnBnClickedChkVilostInvokeAlarmOut();
	afx_msg void OnBnClickedBtnVilostDayOk();
	afx_msg void OnBnClickedBtnVilostDayCopy();
	afx_msg void OnCbnSelchangeComboVilostWeekday();
	afx_msg void OnBnClickedBtnVilostOk();
	afx_msg void OnBnClickedBtnVilostExit();
	afx_msg void OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	
	int	m_iChanShowNum;
	LONG	m_lLoginID;	
	DWORD	m_dwAlarmOutNum;
	DWORD	m_dwDevIndex;
	BOOL TimeTest();
	BOOL m_bAlarmOut[MAX_ALARMOUT_V30];
	void CreateTree();
};





















