// ManageDlg.h : header file
//

#if !defined(AFX_MANAGEDLG_H__BC349B3C_4830_4849_BDDC_BEC89ECB493E__INCLUDED_)
#define AFX_MANAGEDLG_H__BC349B3C_4830_4849_BDDC_BEC89ECB493E__INCLUDED_

#include "DlgDeviceState.h"	// Added by ClassView
#include "DlgLogSearch.h"	// Added by ClassView
#include "GeneralDef.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CManageDlg dialog

class CManageDlg : public CDialog
{
// Construction
public:
	CDlgDeviceState m_DlgDeviceState;
	CDlgLogSearch m_DlgLogSearch;
	CManageDlg(CWnd* pParent = NULL);	// standard constructor
public:
	void DoGetDeviceResoureCfg();
	BOOL DoLogin();
	BOOL m_bIsLogin;
	LOCAL_DEVICE_INFO m_struDeviceInfo;

// Dialog Data
	//{{AFX_DATA(CManageDlg)
	enum { IDD = IDD_MANAGE_DIALOG };
	CTabCtrl	m_ctrlTab;
	CIPAddressCtrl	m_ctrlDevIp;
	UINT	m_nDevPort;
	CString	m_csUser;
	CString	m_csPWD;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CManageDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonCheckTime();
	afx_msg void OnButtonDefaultCfg();
	afx_msg void OnButtonHdFormat();
	afx_msg void OnButtonLogin();
	afx_msg void OnButtonReboot();
	afx_msg void OnButtonShutdown();
	afx_msg void OnButtonUpdate();
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANAGEDLG_H__BC349B3C_4830_4849_BDDC_BEC89ECB493E__INCLUDED_)
