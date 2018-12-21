#if !defined(AFX_DLGSCHEDULEAUTOTRACK_H__4B024257_F5E2_454D_B722_7E3F9F1872FD__INCLUDED_)
#define AFX_DLGSCHEDULEAUTOTRACK_H__4B024257_F5E2_454D_B722_7E3F9F1872FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgScheduleAutoTrack.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgScheduleAutoTrack dialog


class CDlgScheduleAutoTrack : public CDialog
{
// Construction
public:
	CDlgScheduleAutoTrack(CWnd* pParent = NULL);   // standard constructor
	~CDlgScheduleAutoTrack();
// Dialog Data
	//{{AFX_DATA(CDlgScheduleAutoTrack)
	enum { IDD = IDD_DLG_IPC_SCHEDULE_AUTO_TRACK };
	CComboBox	m_cmWorkMode;
	CComboBox	m_cmWeek;
	BOOL	m_chEnable;
	COleDateTime	m_timeStart1;
	COleDateTime	m_timeStart2;
	COleDateTime	m_timeStart4;
	COleDateTime	m_timeStart5;
	COleDateTime	m_timeStart6;
	COleDateTime	m_timeStart7;
	COleDateTime	m_timeStart8;
	COleDateTime	m_timeStart3;
	COleDateTime	m_timeStop1;
	COleDateTime	m_timeStop2;
	COleDateTime	m_timeStop3;
	COleDateTime	m_timeStop4;
	COleDateTime	m_timeStop5;
	COleDateTime	m_timeStop6;
	COleDateTime	m_timeStop7;
	COleDateTime	m_timeStop8;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgScheduleAutoTrack)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgScheduleAutoTrack)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboWeek();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	long m_lUserID;
	int m_iDeviceIndex;
    char m_szLan[128];
	void InitWindow();
	int m_iCurWeekIndex;
	NET_DVR_SCHEDULE_AUTO_TRACK_CFG m_struScheduleAutoTrack;
	COleDateTime m_struStartTime[MAX_TIMESEGMENT_V30];
	COleDateTime m_struStopTime[MAX_TIMESEGMENT_V30];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSCHEDULEAUTOTRACK_H__4B024257_F5E2_454D_B722_7E3F9F1872FD__INCLUDED_)
