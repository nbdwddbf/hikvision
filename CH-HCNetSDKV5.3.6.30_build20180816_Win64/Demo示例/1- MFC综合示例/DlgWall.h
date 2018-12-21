#if !defined(AFX_DLGWALL_H__C5D092A7_03BC_40BB_8233_2DCEBD9E6AC9__INCLUDED_)
#define AFX_DLGWALL_H__C5D092A7_03BC_40BB_8233_2DCEBD9E6AC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWall.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgWall dialog

class CDlgWall : public CDialog
{
// Construction
public:
	CDlgWall(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgWall)
	enum { IDD = IDD_DLG_WALL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWall)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWall)
	afx_msg void OnBtnWallCfg();
	afx_msg void OnBtnWincfg();
	afx_msg void OnBtnPic();
	afx_msg void OnBtnSence();
	afx_msg void OnBtnWallWinStatus();
	afx_msg void OnBtnPicPreview();
	afx_msg void OnBtnUnitedSystem();
	afx_msg void OnBtnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG m_lServerID;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWALL_H__C5D092A7_03BC_40BB_8233_2DCEBD9E6AC9__INCLUDED_)
