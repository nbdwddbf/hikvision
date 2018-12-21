#if !defined(AFX_DLGINFODIFFUSIONXMLUPDOWNLOAD_H__ADB421E0_998F_4C5E_AC23_D24A04CED28B__INCLUDED_)
#define AFX_DLGINFODIFFUSIONXMLUPDOWNLOAD_H__ADB421E0_998F_4C5E_AC23_D24A04CED28B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfoDiffusionXmlUpdownload.h : header file
//

#define TIMER_UPDOWNLOAD_MATERIAL_PROGRESS 1 //上传下载进度

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionXmlUpdownload dialog

class CDlgInfoDiffusionXmlUpdownload : public CDialog
{
// Construction
public:
	CDlgInfoDiffusionXmlUpdownload(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInfoDiffusionXmlUpdownload)
	enum { IDD = IDD_DLG_INFO_DIFFUSION_XML_UPDOWNLOAD };
	CStatic	m_statProgress;
	CProgressCtrl	m_ctrlProgress;
	CString	m_szOutputParam;
	CString	m_szInputParam;
	DWORD	m_dwMaterialIndex;
	CString	m_szSavePath;
	CString	m_szFilePath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInfoDiffusionXmlUpdownload)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInfoDiffusionXmlUpdownload)
	afx_msg void OnBtnUpload();
	afx_msg void OnBtnExit();
	afx_msg void OnBtnDownload();
	afx_msg void OnBtnChoseSavepath();
	afx_msg void OnBtnChoseFile();
	//afx_msg void OnTimer(UINT nIDEvent);
#if (_MSC_VER >= 1500)	//vs2008
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	LONG m_lUserID;
	int m_iDeviceIndex;

	LONG m_lUpdownloadHandle;
	BOOL m_bUploading;
	BOOL m_bDownloading;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINFODIFFUSIONXMLUPDOWNLOAD_H__ADB421E0_998F_4C5E_AC23_D24A04CED28B__INCLUDED_)
