#if !defined(AFX_DLGINTERACTIVESCREENCONFIG_H__E25D9ED1_4704_4C5C_BB23_BF9EA7BCBE83__INCLUDED_)
#define AFX_DLGINTERACTIVESCREENCONFIG_H__E25D9ED1_4704_4C5C_BB23_BF9EA7BCBE83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInteractiveScreenConfig.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInteractiveScreenConfig dialog

class CDlgInteractiveScreenConfig : public CDialog
{
// Construction
public:
	CDlgInteractiveScreenConfig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInteractiveScreenConfig)
	enum { IDD = IDD_DLG_INTERACTIVE_SCREEN_CONFIG };
	CComboBox	m_comScreenShow;
	CComboBox	m_comScreenLock;
	CComboBox	m_comBlackScreen;
	DWORD	m_dwBrightness;
	DWORD	m_dwContrast;
	DWORD	m_dwVolume;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInteractiveScreenConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInteractiveScreenConfig)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG    m_lServerID;
	int     m_iDevIndex;
	LONG    m_lChannel;
	NET_DVR_SCREEN_CONFIG m_struScreenCfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINTERACTIVESCREENCONFIG_H__E25D9ED1_4704_4C5C_BB23_BF9EA7BCBE83__INCLUDED_)
