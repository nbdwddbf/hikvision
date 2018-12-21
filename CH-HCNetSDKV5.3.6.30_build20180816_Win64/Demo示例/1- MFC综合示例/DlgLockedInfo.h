#if !defined(AFX_DLGALARMHOSTTRIGGERCODE_H__11D272CD_E39E_4E53_A5CF_13DD87BD8208__INCLUDED_)
#define AFX_DLGALARMHOSTTRIGGERCODE_H__11D272CD_E39E_4E53_A5CF_13DD87BD8208__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmHostTriggerCode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLockedInfo dialog
#define  MAX_LOCKED_NUM 1024
class CDlgLockedInfo : public CDialog
{
// Construction
public:
	CDlgLockedInfo(CWnd* pParent = NULL);   // standard constructor
	~CDlgLockedInfo();
	LPNET_DVR_LOCKED_INFO m_lpStruLockedInfo;
	void AddInfoToDlg(LPNET_DVR_LOCKED_INFO lpInter);
	void SaveInfo();
	int m_iDeviceIndex;
	LONG m_lUserID;
	LONG m_lHandle;
    int m_iStruCount;
// Dialog Data
	//{{AFX_DATA(CDlgLockedInfo)
	enum { IDD = IDD_DLG_LOCKED_INFO };
	CButton	m_btnGet;
	CListCtrl	m_listLockedInfo;
	CEdit	m_Edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLockedInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLockedInfo)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListTrigger(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEditText();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	afx_msg void OnClickListTrigger(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnUnlockAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	BOOL m_bNeedSave;
	int m_iRowCount;
	//CEdit m_Edit;
	int m_iItem;
	int m_iSubItem;
	int m_iLastItem;
	static DWORD WINAPI GetLockedListThread (LPVOID lpArg);
	BOOL	m_bGetNext;
	void OnCancel();
	HANDLE	m_hGetInfoThread;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMHOSTTRIGGERCODE_H__11D272CD_E39E_4E53_A5CF_13DD87BD8208__INCLUDED_)
