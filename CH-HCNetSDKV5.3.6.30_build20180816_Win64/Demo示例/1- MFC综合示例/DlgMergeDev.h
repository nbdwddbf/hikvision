#if !defined(AFX_DLGMERGEDEV_H__C62DB8CD_AC09_48CA_8919_152A4E275D3B__INCLUDED_)
#define AFX_DLGMERGEDEV_H__C62DB8CD_AC09_48CA_8919_152A4E275D3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMergeDev.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMergeDev dialog

class CDlgMergeDev : public CDialog
{
// Construction
public:
	CDlgMergeDev(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMergeDev)
	enum { IDD = IDD_DLG_MERGE_DEV };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMergeDev)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMergeDev)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnOutputCfg();
	afx_msg void OnBtnWinCfg();
	afx_msg void OnBtnOutputPic();
	afx_msg void OnBtnOutputOsd();
	afx_msg void OnBtnChanResource();
	afx_msg void OnBtnScene();
	afx_msg void OnBtnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lUserID;
    int m_iDeviceIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMERGEDEV_H__C62DB8CD_AC09_48CA_8919_152A4E275D3B__INCLUDED_)
