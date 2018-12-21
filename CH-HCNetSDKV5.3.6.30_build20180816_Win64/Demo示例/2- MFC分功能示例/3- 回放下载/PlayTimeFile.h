#if !defined(AFX_PLAYTIMEFILE_H__593AD1EC_120F_42C4_A468_0495DCBC46E4__INCLUDED_)
#define AFX_PLAYTIMEFILE_H__593AD1EC_120F_42C4_A468_0495DCBC46E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlayTimeFile.h : header file
//
#include "HCNetSDK.h"
/////////////////////////////////////////////////////////////////////////////
// CPlayTimeFile dialog
#define PLAY_STOP   0
#define PLAY_NORMAL 1
#define PLAY_PAUSE  2
#define PLAY_FAST   3
#define PLAY_SLOW   4

class CPlayTimeFile : public CPropertyPage
{
	DECLARE_DYNCREATE(CPlayTimeFile)

// Construction
public:
	CPlayTimeFile();
	~CPlayTimeFile();
public:
	void SetPlayState(int iState);
	void InitUI();
	void GetStartStopTime(NET_DVR_TIME &StartDayTime, NET_DVR_TIME &StopDayTime);
	NET_DVR_TIME m_StartTime;
	NET_DVR_TIME m_StopTime;
	
	BOOL m_IsDownloading;
	LONG m_lDownloadHandle;
	BOOL m_IsPlaying;
	BOOL m_IsPause;
	BOOL m_bChangeSpeed;
	LONG m_hPlayHandle;
	BOOL m_bIsSaving;

	HICON m_hPlayEnableIcon;
	HICON m_hPlayDisableIcon;
	
	HICON m_hPauseEnableIcon;
	HICON m_hPauseDisableIcon;
	
	HICON m_hStopEnableIcon;
	HICON m_hStopDisableIcon;
	
	
	HICON m_hFastDisableIcon;
	HICON m_hFastEnableIcon;
	
	HICON m_hSlowDisableIcon;
	HICON m_hSlowEnableIcon;
// Dialog Data
	//{{AFX_DATA(CPlayTimeFile)
	enum { IDD = IDD_PAGE_TIME };
	CDateTimeCtrl	m_ctrlTimeStart;
	CDateTimeCtrl	m_ctrlTimeStop;
	CDateTimeCtrl	m_ctrlDateStop;
	CDateTimeCtrl	m_ctrlDateStart;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPlayTimeFile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPlayTimeFile)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnPlayBytime();
	afx_msg void OnBtnDownloadByTime();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnStopTime();
	afx_msg void OnBtnFast();
	afx_msg void OnBtnSlow();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYTIMEFILE_H__593AD1EC_120F_42C4_A468_0495DCBC46E4__INCLUDED_)
