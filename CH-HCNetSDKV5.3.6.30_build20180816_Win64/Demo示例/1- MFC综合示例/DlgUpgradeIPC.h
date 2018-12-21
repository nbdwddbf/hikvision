#if !defined(AFX_DLGUPGRADEIPC_H__52384358_7E24_49C3_A889_B79A70905390__INCLUDED_)
#define AFX_DLGUPGRADEIPC_H__52384358_7E24_49C3_A889_B79A70905390__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgUpgradeIPC.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgUpgradeIPC dialog

#define MSG_UPGRADE_IPC_STATUS  WM_USER+103

class CDlgUpgradeIPC : public CDialog
{
// Construction
public:
	CDlgUpgradeIPC(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgUpgradeIPC();
// Dialog Data
	//{{AFX_DATA(CDlgUpgradeIPC)
	enum { IDD = IDD_DLG_UPGRADE_IPC };
	BOOL	m_bCheckD1;
	BOOL	m_bCheckD2;
	BOOL	m_bCheckD3;
	BOOL	m_bCheckD4;
	BOOL	m_bCheckD5;
	BOOL	m_bCheckD6;
	BOOL	m_bCheckD7;
	BOOL	m_bCheckD8;
	BOOL	m_bCheckD9;
	BOOL	m_bCheckD10;
	BOOL	m_bCheckD11;
	BOOL	m_bCheckD12;
	BOOL	m_bCheckD13;
	BOOL	m_bCheckD14;
	BOOL	m_bCheckD15;
	BOOL	m_bCheckD16;
	BOOL	m_bCheckD17;
	BOOL	m_bCheckD18;
	BOOL	m_bCheckD19;
	BOOL	m_bCheckD20;
	BOOL	m_bCheckD21;
	BOOL	m_bCheckD22;
	BOOL	m_bCheckD23;
	BOOL	m_bCheckD24;
	BOOL	m_bCheckD25;
	BOOL	m_bCheckD26;
	BOOL	m_bCheckD27;
	BOOL	m_bCheckD28;
	BOOL	m_bCheckD29;
	BOOL	m_bCheckD30;
	BOOL	m_bCheckD31;
	BOOL	m_bCheckD32;
	BOOL	m_bCheckD33;
	BOOL	m_bCheckD34;
	BOOL	m_bCheckD35;
	BOOL	m_bCheckD36;
	BOOL	m_bCheckD37;
	BOOL	m_bCheckD38;
	BOOL	m_bCheckD39;
	BOOL	m_bCheckD40;
	BOOL	m_bCheckD41;
	BOOL	m_bCheckD42;
	BOOL	m_bCheckD43;
	BOOL	m_bCheckD44;
	BOOL	m_bCheckD45;
	BOOL	m_bCheckD46;
	BOOL	m_bCheckD47;
	BOOL	m_bCheckD48;
	BOOL	m_bCheckD49;
	BOOL	m_bCheckD50;
	BOOL	m_bCheckD51;
	BOOL	m_bCheckD52;
	BOOL	m_bCheckD53;
	BOOL	m_bCheckD54;
	BOOL	m_bCheckD55;
	BOOL	m_bCheckD56;
	BOOL	m_bCheckD57;
	BOOL	m_bCheckD58;
	BOOL	m_bCheckD59;
	BOOL	m_bCheckD60;
	BOOL	m_bCheckD61;
	BOOL	m_bCheckD62;
	BOOL	m_bCheckD63;
	BOOL	m_bCheckD64;
	CString	m_strUpgradeFile;
	CString	m_strOutput;

	BOOL    m_bInProcessing;
    CTreeCtrl	m_treeChan;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgUpgradeIPC)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgUpgradeIPC)
	afx_msg void OnBtnBrowseFile();
	afx_msg void OnBtnUpgradeExit();
	afx_msg void OnBtnUpgrade();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnBtnUpgradeStop();

	afx_msg void OnClickTreeChan(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnBtnSelectAll();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	LRESULT OnUpgradIPCStatusMessage(WPARAM wParam, LPARAM lParam);
    void CreateChannelTree(CTreeCtrl &m_treeChannel, int iDeviceIndex, BOOL *bChannelChecked);
public:
	LONG    m_lUserID;
	LONG   m_dwDevIndex;
	LONG	m_lHandle;
	NET_DVR_IPPARACFG_V40 m_struIPParamCfgV40;

	BOOL    *m_pbUpdateChan;
    DWORD   m_dwSelectNum;
	
    void CreateTree();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGUPGRADEIPC_H__52384358_7E24_49C3_A889_B79A70905390__INCLUDED_)
