#if !defined(AFX_DLGINFODIFFUSIONTERMINALUPGRADE_H__6975656A_BDE6_4F27_8BA2_DE0A38A9C17F__INCLUDED_)
#define AFX_DLGINFODIFFUSIONTERMINALUPGRADE_H__6975656A_BDE6_4F27_8BA2_DE0A38A9C17F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfoDiffusionTerminalUpgrade.h : header file
//

//结束长连接消息
const int WM_STOP_REMOTE_CONFIG = WM_USER + 1;

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionTerminalUpgrade dialog

class CDlgInfoDiffusionTerminalUpgrade : public CDialog
{
// Construction
public:
	CDlgInfoDiffusionTerminalUpgrade(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInfoDiffusionTerminalUpgrade)
	enum { IDD = IDD_DLG_INFO_DIFFUSION_TERMINAL_UPGRADE };
	CComboBox	m_cmbUpgradeType;
	CListCtrl	m_listTerminal;
	CProgressCtrl	m_progressUpgrade;
	DWORD	m_dwTerminalNo;
	DWORD	m_dwGroupNo;
	CString	m_sFilePath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInfoDiffusionTerminalUpgrade)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInfoDiffusionTerminalUpgrade)
	afx_msg void OnBtnUpgradeMod();
	afx_msg void OnBtnUpgradeDel();
	afx_msg void OnBtnUpgradeAdd();
	afx_msg void OnBtnUpgrade();
	afx_msg void OnBtnExit();
	afx_msg void OnBtnChoose();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnClickListTerminal(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboUpgradeType();
//	afx_msg void OnTimer(UINT nIDEvent);
#if (_MSC_VER >= 1500)	//vs2008
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif
	//}}AFX_MSG
	LRESULT OnStopRemoteConfig(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	LONG m_lUserID;
	int m_iDeviceIndex;
	
	DWORD m_dwaTerminal[1024];
	int m_nCurSelTerminal;
	
	LONG m_lConfigHandle;
	
public:
	void  InitTerminalCtrlList();
	DWORD GetRemoteConfigState();
	void  StopRemoteConfig();
	void  ShowUpgradeProgress(DWORD dwProgress, CString strTips);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINFODIFFUSIONTERMINALUPGRADE_H__6975656A_BDE6_4F27_8BA2_DE0A38A9C17F__INCLUDED_)
