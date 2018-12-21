#if !defined(AFX_DLGPICTURESWITCHCTRL_H__F7264F15_85E1_478B_9354_9F7A0CA3EE5A__INCLUDED_)
#define AFX_DLGPICTURESWITCHCTRL_H__F7264F15_85E1_478B_9354_9F7A0CA3EE5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPictureSwitchCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPictureSwitchCtrl dialog

class CDlgPictureSwitchCtrl : public CDialog
{
// Construction
public:
	CDlgPictureSwitchCtrl(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPictureSwitchCtrl)
	enum { IDD = IDD_DLG_PICTURE_SWITCH_CTRL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPictureSwitchCtrl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPictureSwitchCtrl)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSwitch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG    m_lUserID;
    LONG    m_iDevIndex;
    DWORD   m_dwChannel;
	NET_DVR_SCREEN_SWITCH m_struScreenSwitch;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPICTURESWITCHCTRL_H__F7264F15_85E1_478B_9354_9F7A0CA3EE5A__INCLUDED_)
