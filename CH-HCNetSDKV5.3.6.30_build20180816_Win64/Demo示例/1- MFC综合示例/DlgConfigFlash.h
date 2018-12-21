#if !defined(AFX_DLGCONFIGFLASH_H__2BF00773_B484_4D4C_9A44_5082147C0EF5__INCLUDED_)
#define AFX_DLGCONFIGFLASH_H__2BF00773_B484_4D4C_9A44_5082147C0EF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgConfigFlash.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgConfigFlash dialog

class CDlgConfigFlash : public CDialog
{
// Construction
public:
	CDlgConfigFlash(CWnd* pParent = NULL);   // standard constructor
	void LoadTreeImage();
	void CreateTree();
	void CheckAllDevState(HTREEITEM hRoot, BOOL bCheck, int uFlag);
	CImageList m_TreeImage;
	int m_iDeviceIndex;
// Dialog Data
	//{{AFX_DATA(CDlgConfigFlash)
	enum { IDD = IDD_DLG_CONFIG_FLASH };
	CTreeCtrl	m_treeAll;
	CString	m_csDevice;
	CString	m_csFileName;
	CString	m_csUpgrade;
	CString	m_csCopyFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgConfigFlash)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgConfigFlash)
	afx_msg void OnClickTreeall(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnExit();
	afx_msg void OnBtnBrowseFile();
	afx_msg void OnBtnGetFlash();
	afx_msg void OnBtnCopyFlash();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCONFIGFLASH_H__2BF00773_B484_4D4C_9A44_5082147C0EF5__INCLUDED_)
