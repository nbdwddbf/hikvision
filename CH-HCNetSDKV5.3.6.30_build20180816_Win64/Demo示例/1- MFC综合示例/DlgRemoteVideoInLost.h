#pragma once
#include "afxwin.h"


// CDlgRemoteVideoInLost dialog

class CDlgRemoteVideoInLost : public CDialog
{
	DECLARE_DYNAMIC(CDlgRemoteVideoInLost)

public:
	CDlgRemoteVideoInLost(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgRemoteVideoInLost();

// Dialog Data
	


public:


	//{{AFX_DATA(CDlgRemoteVideoInLost)
	enum { IDD = IDD_DLG_REOMTE_VILOST };
	CTreeCtrl	m_treeAlarmOut;
	BOOL m_bChkMonitorAlarm;
	BOOL m_bChkAudioAlarm;
	BOOL m_bChkReportCenter;
	BOOL m_bChkInvokeAlarmOut;
	BOOL m_bChkEmapAlarmOut;
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
	int m_iInputLostShreshold;
	BOOL	m_bChkPicToFtp;
    BOOL    m_bChkPicToCloud;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CDlgRemoteVideoInLost)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteVideoInLost)
	virtual BOOL OnInitDialog();	
	afx_msg void OnBnClickedChkVilostInvokeAlarmOut();
	afx_msg void OnBnClickedBtnVilostDayOk();
	afx_msg void OnBnClickedBtnVilostDayCopy();
	afx_msg void OnCbnSelchangeComboVilostWeekday();
	afx_msg void OnBnClickedBtnVilostOk();
	afx_msg void OnBnClickedBtnVilostExit();
	afx_msg void OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg void OnBtnAlarmoutSelectall();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	
	BOOL m_bIsVILost;
	int	m_iChanShowNum;
	LONG	m_lLoginID;	
	DWORD	m_dwAlarmOutNum;
	DWORD	m_dwDevIndex;
	BOOL TimeTest();
	//	BOOL m_bAlarmOut[MAX_ALARMOUT_V30];
   	BOOL   *m_pbAlarmOut;
	void CreateTree();
    NET_DVR_HOLIDAY_HANDLE m_struVLHolidayHandle;
    BOOL GetVLHolidayHandle(NET_DVR_HOLIDAY_HANDLE &struHolidayHandle);
    BOOL SetVLHolidayHandle(NET_DVR_HOLIDAY_HANDLE &struHolidayHandle);
};
