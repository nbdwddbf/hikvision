#if !defined(AFX_DLGALARMEXCEPTIONHANDLE_H__CBF9FED7_F89D_404E_AA2E_2D241A8CAF12__INCLUDED_)
#define AFX_DLGALARMEXCEPTIONHANDLE_H__CBF9FED7_F89D_404E_AA2E_2D241A8CAF12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmExceptionHandle.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmExceptionHandle dialog

class CDlgAlarmExceptionHandle : public CDialog
{
// Construction
public:
	CDlgAlarmExceptionHandle(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlarmExceptionHandle)
	enum { IDD = IDD_DLG_ALARM_EXCEPTION_HANDLE };
	CTreeCtrl	m_treeAlarmOut;
	BOOL	m_bChkMonitorAlarm;
	BOOL	m_bChkAudioAlarm;
	BOOL	m_bChkReportCenter;
	BOOL	m_bChkInvokeAlarmOut;
	BOOL	m_bChkInvokeJpegCapture;
	BOOL	m_bChkPicFtp;
	BOOL	m_bChkEmapAlarmOut;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmExceptionHandle)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmExceptionHandle)
	afx_msg void OnBtnSetAlarmExceptionHandle();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChkTriggerAlarmOutput();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	NET_DVR_HANDLEEXCEPTION_V30 *m_struHandleException;
	BOOL m_bAlarmOut[MAX_ALARMOUT_V30];
	DWORD m_dwDevIndex; 
	BOOL m_bChkSmsAlarm;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMEXCEPTIONHANDLE_H__CBF9FED7_F89D_404E_AA2E_2D241A8CAF12__INCLUDED_)
