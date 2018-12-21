#if !defined(AFX_DLGITSWORKSTATE_H__2DE9C5CB_8154_45C7_B61C_FB1CC0F21E9B__INCLUDED_)
#define AFX_DLGITSWORKSTATE_H__2DE9C5CB_8154_45C7_B61C_FB1CC0F21E9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgITSWorkState.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgITSWorkState dialog

class CDlgITSWorkState : public CDialog
{
// Construction
public:
	CDlgITSWorkState(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgITSWorkState)
	enum { IDD = IDD_DLG_ITS_WORKSTATE };
	CComboBox	m_comboDevChan;
	CListCtrl	m_listAlarmOutState;
	CListCtrl	m_listAlarmInState;
	CComboBox	m_comboLocalDisplay;
	CComboBox	m_comboHostIndex;
	CListCtrl	m_listDiskState;
	CListCtrl	m_listChanState;
	CString	m_csHostIP;
	DWORD	m_dwCpuUsage;
	DWORD	m_dwDataTotal;
	DWORD	m_dwDevTemp;
	CString	m_csDeviceName;
	DWORD	m_dwEndDay;
	DWORD	m_dwEndHour;
	DWORD	m_dwEndMilliSec;
	DWORD	m_dwEndMinute;
	DWORD	m_dwEndMonth;
	DWORD	m_dwEndSec;
	DWORD	m_dwEndYear;
	DWORD	m_dwMemoryUsage;
	DWORD	m_dwNeedSendData;
	DWORD	m_dwRunTime;
	DWORD	m_dwStartDay;
	DWORD	m_dwStartHour;
	DWORD	m_dwStartMilliSec;
	DWORD	m_dwStartMinute;
	DWORD	m_dwStartMonth;
	DWORD	m_dwStartSec;
	DWORD	m_dwStartYear;
	CString	m_csDeviceState;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgITSWorkState)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgITSWorkState)
	afx_msg void OnBtnGet();
	afx_msg void OnSelchangeComboHost();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int m_iDeviceIndex;
	CString m_csRecState;
	CString m_csSignalState;
	CString m_csHardWareState;
	CString m_csLinkCount;
	CString m_csBitrate;
	CString m_csDiskVolume;
	CString m_csDiskFreeSpace;
	CString m_csDiskState;
	BOOL CheckInitParam(void);
	LONG m_lLoginID;
	int m_iHostSel;

	NET_ITS_WORKSTATE m_struWorkState;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGITSWORKSTATE_H__2DE9C5CB_8154_45C7_B61C_FB1CC0F21E9B__INCLUDED_)
