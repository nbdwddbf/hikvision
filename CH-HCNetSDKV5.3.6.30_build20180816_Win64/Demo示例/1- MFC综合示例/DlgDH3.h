#if !defined(AFX_DLGDH3_H__065FBF55_C7B8_4507_8DA9_C3A4E4115322__INCLUDED_)
#define AFX_DLGDH3_H__065FBF55_C7B8_4507_8DA9_C3A4E4115322__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDH3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgDH3 dialog

class DlgDH3 : public CDialog
{
// Construction
public:
	DlgDH3(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgDH3)
	enum { IDD = IDD_DLG_DH };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgDH3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgDH3)
	afx_msg void OnBtnGetAllPoint();
	afx_msg void OnBtnGetAllSensor();
	afx_msg void OnBtnGetAllRs485Cfg();
	afx_msg void OnBtnGetAllRs485SlotCfg();
	afx_msg void OnBtnGetDeviceState();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDH3_H__065FBF55_C7B8_4507_8DA9_C3A4E4115322__INCLUDED_)
