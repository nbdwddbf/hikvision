#if !defined(AFX_DLGQUICKADDIPC_H__D624469C_74E2_4D30_8E58_3562BBE580D4__INCLUDED_)
#define AFX_DLGQUICKADDIPC_H__D624469C_74E2_4D30_8E58_3562BBE580D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQuickAddIpc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQuickAddIpc dialog

class CDlgQuickAddIpc : public CDialog
{
// Construction
public:
	CDlgQuickAddIpc(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgQuickAddIpc)
	enum { IDD = IDD_DLG_QUICK_ADD_IPC };
	CListCtrl	m_listIPChan;
	CListCtrl	m_listSadpInfo;
	CString	m_csDevIP;
	int		m_iDevPort;
	CString	m_csPassword;
	CString	m_csSubnetMask;
	BYTE	m_ProtocolType;
	CString	m_strActivatePwd;
	CString	m_csGB28181DevID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQuickAddIpc)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQuickAddIpc)
	afx_msg void OnBtnGetSadpinfo();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnQuickAdd();
	afx_msg void OnBtnRefresh();
	afx_msg void OnBtnQuickSet();
	afx_msg void OnClickListSadpInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnSaveSadpinfo();
	afx_msg void OnBtnActivate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    long m_lServerID;
    int m_iDevIndex;
    BYTE m_byMacAddr[MACADDR_LEN];
    NET_DVR_SADPINFO_LIST m_struSadpInfoList;
    NET_DVR_IPC_PROTO_LIST m_struIpcProtoList;
    NET_DVR_IPPARACFG_V40 m_struIpParaCfgV40;
    char* GetFactoryStr(int nFactoryType);
    void CheckInitparam();
    BOOL SetIPParamConfig();
    BOOL GetIPParamConfig();
    BOOL m_bIPCActivatePassword;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQUICKADDIPC_H__D624469C_74E2_4D30_8E58_3562BBE580D4__INCLUDED_)
