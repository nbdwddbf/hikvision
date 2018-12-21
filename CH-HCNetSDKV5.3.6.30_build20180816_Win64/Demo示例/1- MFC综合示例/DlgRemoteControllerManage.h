#if !defined(AFX_DLGREMOTECONTROLLERMANAGE_H__6B2E0A97_CA9D_454F_8938_D26A51AA2DF6__INCLUDED_)
#define AFX_DLGREMOTECONTROLLERMANAGE_H__6B2E0A97_CA9D_454F_8938_D26A51AA2DF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRemoteControllerManage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteControllerManage dialog

class CDlgRemoteControllerManage : public CDialog
{
// Construction
public:
	CDlgRemoteControllerManage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRemoteControllerManage)
	enum { IDD = IDD_DLG_REMOTE_CONTROLLER_MANEGE };
	CListCtrl	m_listctrlRemoteController;
	//}}AFX_DATA

	NET_DVR_REMOTECONTROLLER_PERMISSION_CFG m_struRemoteControllerCfg;
	DWORD m_iDeviceIndex;
	LONG m_lUserID;
	long m_lHandle;
	BOOL m_bGetNext;
	HANDLE	m_hGetInfoThread;
	DWORD m_iRowCount;
	char m_sTemp[256];
	void AddInfoToDlg();
	static DWORD WINAPI GetConfigThread (LPVOID lpArg);
	BOOL OnInitDialog();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRemoteControllerManage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteControllerManage)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnDelete();
	afx_msg void OnBtnAdd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREMOTECONTROLLERMANAGE_H__6B2E0A97_CA9D_454F_8938_D26A51AA2DF6__INCLUDED_)
