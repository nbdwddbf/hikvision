#if !defined(AFX_DLGNVRCFG_H__38486C3E_835D_409D_8521_E5E152CC9ECB__INCLUDED_)
#define AFX_DLGNVRCFG_H__38486C3E_835D_409D_8521_E5E152CC9ECB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNVRCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////


#define MSG_PULL_DISK_STATE WM_USER+100 
#define MSG_SCAN_RAID_STATE WM_USER+101

class CDlgNVRCfg : public CDialog
{
// Construction
public:
	CDlgNVRCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNVRCfg)
	enum { IDD = IDD_DLG_NVR_CFG };
	CString	m_strIPCIP;
	short	m_wPort;
	CString	m_strNewPasswd;
	CString	m_strIPCNetFlow;
	CString	m_strRWNetFlow;
	CString	m_strPlaybackNetFlow;
	CString	m_strPreviewNetFlow;
	CString	m_strOldPasswd;
	BOOL	m_bSynIPC;
	BOOL	m_bRaid;
	DWORD	m_dwRaidID;
	CString	m_strPullDiskState;
	CString	m_strScanRaidState;
	BOOL	m_bSleep;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNVRCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNVRCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnUpdate();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnSetRaid();
	afx_msg void OnBtnSecurePullDisk();
	afx_msg void OnBtnScanRaid();
	afx_msg void OnButtonStopPullDisk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void InitWnd();

	LRESULT OnPullDiskState(WPARAM wParam, LPARAM lParam);
	LRESULT OnScanRaidState(WPARAM wParam, LPARAM lParam);

// 	static void __stdcall PullDiskStateCallBack(LONG lUserId, LONG dwState, LPVOID pUser);
// 	static void __stdcall ScanRaidStateCallBack(LONG lUserId, LONG dwState, LPVOID pUser);



public:
	LONG    m_lUserID;
    int     m_iDevIndex;
	LONG    m_lChannel;

private:
	LONG m_lPullDiskHandle;
	LONG m_lScanRaidHandle;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNVRCFG_H__38486C3E_835D_409D_8521_E5E152CC9ECB__INCLUDED_)
