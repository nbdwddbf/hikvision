#if !defined(AFX_DLGCHECKTIME_H__76DE0C8C_7441_4322_86E8_E4CAF0DBE19A__INCLUDED_)
#define AFX_DLGCHECKTIME_H__76DE0C8C_7441_4322_86E8_E4CAF0DBE19A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCheckTime.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCheckTime dialog

class CDlgCheckTime : public CDialog
{
// Construction
public:
	CDlgCheckTime(CWnd* pParent = NULL);   // standard constructor
	void LoadTreeImage();
	void CreateTree();
	CImageList m_TreeImage;
	BOOL m_bFortify;
	
	// select/ do not select all thedevice on certain area
	void CheckAllDevState(HTREEITEM hRoot, BOOL bCheck, int uFlag);

	// add/ delete device in a broadcast group
	BOOL AddDVR(HTREEITEM hDevice, int iDeviceIndex , BOOL bCheck);
// Dialog Data
	//{{AFX_DATA(CDlgCheckTime)
	enum { IDD = IDD_DLG_CHECK_TIME };
	CTreeCtrl	m_treeAll;
	COleDateTime	m_checkDate;
	COleDateTime	m_checkTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCheckTime)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCheckTime)
	afx_msg void OnBtnCheckTime();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnExit();
	afx_msg void OnClickTreeall(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCHECKTIME_H__76DE0C8C_7441_4322_86E8_E4CAF0DBE19A__INCLUDED_)
