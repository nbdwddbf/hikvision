#if !defined(AFX_DLGALARMHOSTHISTORYDATA_H__2A02CCB0_EF20_454D_9EEC_3EEE594F8468__INCLUDED_)
#define AFX_DLGALARMHOSTHISTORYDATA_H__2A02CCB0_EF20_454D_9EEC_3EEE594F8468__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmhostHistoryData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmhostHistoryData dialog

class CDlgAlarmhostHistoryData : public CDialog
{
// Construction
public:
	CDlgAlarmhostHistoryData(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlarmhostHistoryData)
	enum { IDD = IDD_DLG_ALARMHOST_HISTORY_DATA };
	CComboBox	m_cmChanType;
	CListCtrl	m_listData;
	CComboBox	m_cmMinorType;
	CComboBox	m_cmMajorType;
	COleDateTime	m_timeStartDay;
	COleDateTime	m_timeStartTime;
	COleDateTime	m_timeStopDay;
	COleDateTime	m_timeStopTime;
	DWORD	m_dwChanNo;
	DWORD	m_dwPointNo;
	DWORD	m_dwSlotNo;
	DWORD	m_dwVarNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmhostHistoryData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmhostHistoryData)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSearch();
	afx_msg void OnBtnStop();
	afx_msg void OnSelchangeComboMajorType();
	afx_msg void OnSelchangeComboChanType();
	afx_msg void OnSelchangeComboMinorType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	LONG m_lUserID;
	int m_iDeviceIndex;
	char m_sTemp[256];
	NET_DVR_ALARMHOST_ABILITY m_struAbility;
	int m_iItem;
	int m_iSubItem;
	int m_iRowCount;
	long m_lHandle;
	BOOL m_bGetNext;
	HANDLE	m_hGetInfoThread;
	NET_DVR_SEARCH_CONDITION m_struSearch;
	NET_DVR_HISTORY_DATA	 m_struHistoryData;
	static DWORD WINAPI GetConfigThread (LPVOID lpArg);
	void AddInfoToDlg();
	void GetSearchConditionFromDlg();
	void InitComboWnd();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMHOSTHISTORYDATA_H__2A02CCB0_EF20_454D_9EEC_3EEE594F8468__INCLUDED_)
