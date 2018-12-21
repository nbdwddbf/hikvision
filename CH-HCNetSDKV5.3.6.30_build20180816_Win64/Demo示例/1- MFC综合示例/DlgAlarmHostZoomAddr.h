#if !defined(AFX_DLGALARMHOSTZOOMADDR_H__CDAA56DD_9962_4F62_942D_59FDDF4618FB__INCLUDED_)
#define AFX_DLGALARMHOSTZOOMADDR_H__CDAA56DD_9962_4F62_942D_59FDDF4618FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmHostZoomAddr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostZoneAddr dialog

class CDlgAlarmHostZoneAddr : public CDialog
{
// Construction
public:
	CDlgAlarmHostZoneAddr(CWnd* pParent = NULL);   // standard constructor
	~CDlgAlarmHostZoneAddr();
	LPNET_DVR_ALARMIN_PARAM m_lpStruAlarmIn;
	void AddZoomInfoToDlg(LPNET_DVR_ALARMIN_PARAM lpInter);
	void SaveZoomInfo();
	int m_iDeviceIndex;
	LONG m_lUserID;
	LONG m_lHandle;
	int m_iStruCount;
// Dialog Data
	//{{AFX_DATA(CDlgAlarmHostZoneAddr)
	enum { IDD = IDD_DLG_ALARMHOST_ZONE_ADDR };
	CButton	m_btnGet;
	CComboBox	m_cmSubsystem;
	CEdit	m_Edit;
	CListCtrl	m_listZoom;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmHostZoneAddr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmHostZoneAddr)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListZoom(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEditText();
	afx_msg void OnSelchangeComboSubsystemIndex();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	BOOL m_bNeedSave;
	int m_iRowCount;
	//CEdit m_Edit;
	int m_iItem;
	int m_iSubItem;
	int m_iLastItem;
	NET_DVR_LIST_INFO m_struListInfo;
	NET_DVR_ALARMHOST_ABILITY m_struAlarmHostAbility;
	static DWORD WINAPI GetZoomListThread (LPVOID lpArg);
	BOOL m_bGetNext;
	int m_iZoomCount;
	HANDLE	m_hGetInfoThread;
	void OnCancel();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMHOSTZOOMADDR_H__CDAA56DD_9962_4F62_942D_59FDDF4618FB__INCLUDED_)
