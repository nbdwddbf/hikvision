#if !defined(AFX_DLGDEVSTORAGEINFO_H__9B135038_536A_496C_8A09_DE2B554AC249__INCLUDED_)
#define AFX_DLGDEVSTORAGEINFO_H__9B135038_536A_496C_8A09_DE2B554AC249__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDevStorageInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDevStorageInfo dialog

class CDlgDevStorageInfo : public CDialog
{
// Construction
public:
	CDlgDevStorageInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDevStorageInfo)
	enum { IDD = IDD_DLG_DEV_STORAGE };
	int		m_nCapacityTotal;
	int		m_nFreeSpaceTotal;
	int		m_nLockedRecordSpace;
	int		m_nUnLockedSpace;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDevStorageInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDevStorageInfo)
	afx_msg void OnBtnGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lUserID;
	int m_iDevIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDEVSTORAGEINFO_H__9B135038_536A_496C_8A09_DE2B554AC249__INCLUDED_)
