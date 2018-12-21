#if !defined(AFX_DLGREMOTENETNFS_H__EA12F669_A1B7_48FB_B272_E49B8C170006__INCLUDED_)
#define AFX_DLGREMOTENETNFS_H__EA12F669_A1B7_48FB_B272_E49B8C170006__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRemoteNetNFS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteNetNFS dialog

class CDlgRemoteNetNFS : public CDialog
{
// Construction
public:
	CDlgRemoteNetNFS(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	static DWORD WINAPI GetNasServerTestInfoThread(LPVOID lpArg);
public:


	//{{AFX_DATA(CDlgRemoteNetNFS)
	enum { IDD = IDD_DLG_REMOTE_NET_NFS };
	CComboBox	m_comboDiskType;
	CComboBox	m_comboAddrType;
	CComboBox	m_comboMountType;
	CListCtrl	m_listFindNasDir;
	CListCtrl	m_listDirectory;
	CComboBox m_comboNFSDisk;
	CString m_csNFSIP;
	CString m_csNFSDir;
	short	m_wPort;
	CString	m_csFindNasIP;
	short	m_wFindNasPort;
	CString	m_csPasswd;
	CString	m_csUserName;
	CString	m_csNFSDomain;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CDlgRemoteNetNFS)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteNetNFS)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnNfsSave();
	afx_msg void OnCbnSelchangeComboNfsDisk();
	afx_msg void OnBnClickedBtnExit();
	afx_msg void OnSelchangeComboDiskType();
	afx_msg void OnBtnSearchDirectory();
	afx_msg void OnClickListDirectory(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnFindnasDir();
	afx_msg void OnSelchangeComboMountType();
	afx_msg void OnBtnNasServerTest();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	NET_DVR_NET_DISKCFG_V40 m_struNetDiskCfg;
	int m_iCurDisk;//current nas disk number
	int m_iDiskType;//current nas disk type
	LONG m_lServerID;
    int m_iDevIndex;
    LONG m_lSearchHandle;
    BOOL m_bSearching;
    HANDLE m_hSearchThread;
	HANDLE m_hFindNasThread;
    int  m_iDirectoryNum;
	long m_lFindNasHandle;
	long m_lListNum;
	void SetMountTypeToWnd(int m_iCurDisk);
	NET_DVR_SERVER_TEST_PARA m_struNasServerTestParam;
	LONG m_lNasTestHandle;
	HANDLE	m_hGetInfoThread;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREMOTENETNFS_H__EA12F669_A1B7_48FB_B272_E49B8C170006__INCLUDED_)
