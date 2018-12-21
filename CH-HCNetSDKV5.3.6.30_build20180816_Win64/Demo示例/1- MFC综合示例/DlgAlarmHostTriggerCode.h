#if !defined(AFX_DLGALARMHOSTTRIGGERCODE_H__11D272CD_E39E_4E53_A5CF_13DD87BD8208__INCLUDED_)
#define AFX_DLGALARMHOSTTRIGGERCODE_H__11D272CD_E39E_4E53_A5CF_13DD87BD8208__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmHostTriggerCode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostTriggerCode dialog

class CDlgAlarmHostTriggerCode : public CDialog
{
// Construction
public:
	CDlgAlarmHostTriggerCode(CWnd* pParent = NULL);   // standard constructor
	~CDlgAlarmHostTriggerCode();
	LPNET_DVR_ALARMOUT_PARAM m_lpStruAlarmOut;
	void AddTriggerInfoToDlg(LPNET_DVR_ALARMOUT_PARAM lpInter);
	void SaveTriggerInfo();
	int m_iDeviceIndex;
	LONG m_lUserID;
	LONG m_lHandle;
	int m_iStruCount;
	BOOL m_struChangeState[MAX_ALARMHOST_ALARMOUT_NUM];
// Dialog Data
	//{{AFX_DATA(CDlgAlarmHostTriggerCode)
	enum { IDD = IDD_DLG_ALARMHOST_TRIGGER_ADDR };
	CButton	m_btnGet;
	CListCtrl	m_listTrigger;
	CEdit	m_Edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmHostTriggerCode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmHostTriggerCode)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListTrigger(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEditText();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
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
	static DWORD WINAPI GetTriggerListThread (LPVOID lpArg);
	BOOL	m_bGetNext;
	void OnCancel();
	HANDLE	m_hGetInfoThread;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMHOSTTRIGGERCODE_H__11D272CD_E39E_4E53_A5CF_13DD87BD8208__INCLUDED_)
