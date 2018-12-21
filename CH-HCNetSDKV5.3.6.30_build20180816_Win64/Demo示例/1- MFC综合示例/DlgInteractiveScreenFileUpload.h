#include "afxwin.h"
#if !defined(AFX_DLGINTERACTIVESCREENFILEUPLOAD_H__4A78FB47_75FD_4E53_B8E2_D6E5ED804D99__INCLUDED_)
#define AFX_DLGINTERACTIVESCREENFILEUPLOAD_H__4A78FB47_75FD_4E53_B8E2_D6E5ED804D99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInteractiveScreenFileUpload.h : header file
//

#define TIMER_UPDOWNLOAD_MATERIAL_PROGRESS 888

/////////////////////////////////////////////////////////////////////////////
// CDlgInteractiveScreenFileUpload dialog

class CDlgInteractiveScreenFileUpload : public CDialog
{
// Construction
public:
	CDlgInteractiveScreenFileUpload(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInteractiveScreenFileUpload)
	enum { IDD = IDD_DLG_INTERACTIVE_SCREENFILE_UPLOAD };
	CStatic	m_statProgress;
	CProgressCtrl	m_ctrlProgress;
	CComboBox	m_comVideoFormat;
	CComboBox	m_comPicFormat;
	CComboBox	m_comFileType;
	CString	m_csFileName;
	DWORD	m_dwPPTPage;
	DWORD	m_dwFileIndex;
	CString	m_szSavePath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInteractiveScreenFileUpload)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInteractiveScreenFileUpload)
	afx_msg void OnBtnDownload();
	afx_msg void OnBtnUpload();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnChoose();
	afx_msg void OnBtnSaveFile();
	afx_msg void OnSelchangeComFiletype();
//	afx_msg void OnTimer(UINT nIDEvent);
#if (_MSC_VER >= 1500)	//vs2008
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	LONG m_lUserID;
	int m_iDeviceIndex;
	
	LONG m_lUpdownloadHandle;
	BOOL m_bUploading;
	BOOL m_bDownloading;

	NET_DVR_SCREEM_FILE_UPLOAD_PARAM m_struUpload;
	NET_DVR_SCREEM_FILE_DOWNLOAD_PARAM m_struDownload;

	CString m_sFileName;

	LONG m_lDownloadHandle;
public:
    CComboBox m_cmbDocFormat;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINTERACTIVESCREENFILEUPLOAD_H__4A78FB47_75FD_4E53_B8E2_D6E5ED804D99__INCLUDED_)
