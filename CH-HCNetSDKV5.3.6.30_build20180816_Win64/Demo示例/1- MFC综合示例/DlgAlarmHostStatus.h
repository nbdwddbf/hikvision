#include "afxcmn.h"
#if !defined(AFX_DLGALARMHOSTSTATUS_H__77CB60CE_ED7C_48C0_9BB7_5E3B3A4E2B6A__INCLUDED_)
#define AFX_DLGALARMHOSTSTATUS_H__77CB60CE_ED7C_48C0_9BB7_5E3B3A4E2B6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmHostStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostStatus dialog

class CDlgAlarmHostStatus : public CDialog
{
// Construction
public:
	CDlgAlarmHostStatus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlarmHostStatus)
	enum { IDD = IDD_DLG_ALARM_HOST_STATUS };
	CListCtrl	m_listMemoryStatus;
	CListCtrl	m_listFaultStatus;
	CListCtrl	m_listSubSystem;
	CListCtrl	m_listBypassStatus;
	CListCtrl	m_listSetupAlarmInStatus;
	CListCtrl	m_listAlarmOutStatus;
	CListCtrl	m_listAlarmInStaus;
	BOOL	m_bSirenStaus;
    BOOL	m_bSirenStaus1;
    BOOL	m_bSirenStaus2;
//     CListCtrl m_listDetectorConnectionStatus;
//     CListCtrl m_listDetectorPowerStatus;
    CListCtrl m_listDetectorStatus;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmHostStatus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmHostStatus)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnRefresh();
	afx_msg void OnBtnBypassAlarmchan();
	afx_msg void OnBtnCloseAlarmchan();
	afx_msg void OnBtnSetupAlarmchan();
	afx_msg void OnBtnUnBypassAlarmchan();
	afx_msg void OnRclickListSetupAlarminStatus(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickListBypassStatus(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuSelectAll();
	afx_msg void OnMenuCancelAll();
#if (_MSC_VER >= 1500)	//vs2008
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
    afx_msg void OnTimer(UINT nIDEvent);
#endif
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    NET_DVR_ALARMHOST_ABILITY m_struAlarmHostAbility;
    int     m_iDevIndex;
    LONG    m_lServerID;
    LONG    m_lStartChan;
    LONG    m_lChannel;
    int     m_iPopMenuType;

    NET_DVR_ALARMHOST_MAIN_STATUS_V51   m_struAlarmMainStatus;
    NET_DVR_ALARMHOST_OTHER_STATUS_V51  m_struAlarmOtherStatus;

    NET_DVR_ALARMIN_SETUP m_struAlarmInSetup;
public :
    void InitWnd();

    BOOL GetAlarmHostMainStatus(NET_DVR_ALARMHOST_MAIN_STATUS_V51& struAlarmMainStatus);
    BOOL GetAlarmHostOtherStatus(NET_DVR_ALARMHOST_OTHER_STATUS_V51& struAlarmOtherStatus);

    void SetAlarmHostMainStatusToWnd(NET_DVR_ALARMHOST_MAIN_STATUS_V51& struAlarmMainStatus);
    void SetAlarmHostOtherStatusToWnd(NET_DVR_ALARMHOST_OTHER_STATUS_V51& struAlarmOtherStatus);
    
    void GetSetupAlarmChanFromWnd(NET_DVR_ALARMIN_SETUP &struAlarmInSetup);
    void GetBypassAlarmChanFromWnd(NET_DVR_ALARMIN_SETUP &struAlarmInSetup);

    BOOL AlarmHostSetAlarmChan(NET_DVR_ALARMIN_SETUP &struAlarmInSetup);
    BOOL AlarmHostCloseAlarmChan(NET_DVR_ALARMIN_SETUP &struAlarmInSetup);
    BOOL BypassAlarmChan(NET_DVR_ALARMIN_SETUP &struAlarmInSetup);
    BOOL UnBypassAlarmChan(NET_DVR_ALARMIN_SETUP &struAlarmInSetup);

    
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMHOSTSTATUS_H__77CB60CE_ED7C_48C0_9BB7_5E3B3A4E2B6A__INCLUDED_)
