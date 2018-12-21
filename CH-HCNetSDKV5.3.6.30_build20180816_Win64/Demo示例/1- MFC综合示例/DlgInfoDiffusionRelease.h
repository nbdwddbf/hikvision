#if !defined(AFX_DLGINFODIFFUSIONRELEASE_H__D746CB79_1AE0_473E_BAD7_9E13CB646BFD__INCLUDED_)
#define AFX_DLGINFODIFFUSIONRELEASE_H__D746CB79_1AE0_473E_BAD7_9E13CB646BFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfoDiffusionRelease.h : header file
//

#include "InfoDiffusionParamsConvert.h"
#include "afxdtctl.h"
#include "ATLComTime.h"

#define MAX_LEN_XML 10*1024*1024 //xml最大长度

//结束长连接消息
const int WM_STOP_REMOTE_CONFIG = WM_USER + 1;

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionRelease dialog

class CDlgInfoDiffusionRelease : public CDialog
{
// Construction
public:
	CDlgInfoDiffusionRelease(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInfoDiffusionRelease)
	enum { IDD = IDD_DLG_INFO_DIFFUSION_SCHEDULE_RELEASE };
	CProgressCtrl	m_progressRelease;
	CListCtrl	m_listTerminal;
	CComboBox	m_cmbReleaseType;
	DWORD	m_dwScheduleID;
	DWORD	m_dwTerminalID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInfoDiffusionRelease)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInfoDiffusionRelease)
	afx_msg void OnBtnExit();
	afx_msg void OnBtnRelease();
	afx_msg void OnBtnTerminalAdd();
	afx_msg void OnBtnTerminalDel();
	afx_msg void OnBtnTerminalMod();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboReleaseType();
	afx_msg void OnDestroy();
	afx_msg void OnClickListTerminal(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	LRESULT OnStopRemoteConfig(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	LONG m_lUserID;
	int m_iDeviceIndex;
	
	int m_nCurSelTerminal;
	
	LPNET_DVR_SCHEDULE_RELEASE m_lpRelease;
	char* m_pOutputXmlBuffer;

	LONG m_lConfigHandle;

public:
	void InitTerminalCtrlList();
	void RefreshTernimalList(CString strReleaseType);
	DWORD GetRemoteConfigState();
	void StopRemoteConfig();
	void ShowReleaseProgress(DWORD dwProgress, CString strTips);
    CDateTimeCtrl m_date;
    COleDateTime m_time;
    COleDateTime m_dateDate;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINFODIFFUSIONRELEASE_H__D746CB79_1AE0_473E_BAD7_9E13CB646BFD__INCLUDED_)
