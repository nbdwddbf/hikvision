#if !defined(AFX_DLGIMEXPORTIPCCFGFILE_H__2BF00773_B484_4D4C_9A44_5082147C0EF5__INCLUDED_)
#define AFX_DLGIMEXPORTIPCCFGFILE_H__2BF00773_B484_4D4C_9A44_5082147C0EF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgImExportIPCCfgFile.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// DlgImexporIPCCfgFile dialog

#define MSG_IMPORT_IPC_CFG_FILE_STATUS  WM_USER+104
#define DOWNLOAD_IPC_CFG_FILE_TIMER		WM_USER+105

class DlgImexporIPCCfgFile : public CDialog
{
// Construction
public:
	DlgImexporIPCCfgFile(CWnd* pParent = NULL);   // standard constructor
	void LoadTreeImage();
	void CreateTree();
	void CheckAllDevState(HTREEITEM hRoot, BOOL bCheck, int uFlag);
	CImageList m_TreeImage;
	int m_iDeviceIndex;
	int m_iRecvFailedNum;
    BOOL m_bProcessing;
// Dialog Data
	//{{AFX_DATA(DlgImexporIPCCfgFile)
	enum { IDD = IDD_DLG_IM_EXPORT_IPC_CFG_FILE };
	CTreeCtrl	m_treeAll;
	CString	m_csDevice;
	CString	m_csFileName;
	CString	m_csCopyFile;
	CString	m_strOutput;
	CString	m_strStatus;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgImexporIPCCfgFile)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgImexporIPCCfgFile)
	afx_msg void OnClickTreeall(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnExit();
	afx_msg void OnBtnBrowseFile();
	afx_msg void OnBtnGetFile();
	afx_msg void OnBtnImport();
	afx_msg void OnClose();
#if (_MSC_VER >= 1500)	//vs2008
    afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
    afx_msg void OnTimer(UINT nIDEvent);
#endif
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	LRESULT OnImportIPCCfgFileMessage(WPARAM wParam, LPARAM lParam);

public:
	LONG	m_lHandle;
	LONG 	m_lDownloadHandle;
	LONG    m_timerHandle;
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIMEXPORTIPCCFGFILE_H__2BF00773_B484_4D4C_9A44_5082147C0EF5__INCLUDED_)
