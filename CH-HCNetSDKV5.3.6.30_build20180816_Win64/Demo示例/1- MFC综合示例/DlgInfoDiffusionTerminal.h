#if !defined(AFX_DLGINFODIFFUSIONTERMINAL_H__82D724E9_E57E_4E2B_BB6E_FB30C081400C__INCLUDED_)
#define AFX_DLGINFODIFFUSIONTERMINAL_H__82D724E9_E57E_4E2B_BB6E_FB30C081400C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfoDiffusionTerminal.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionTerminal dialog

class CDlgInfoDiffusionTerminal : public CDialog
{
// Construction
public:
	CDlgInfoDiffusionTerminal(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInfoDiffusionTerminal)
	enum { IDD = IDD_DLG_INFO_DIFFUSION_TERMINAL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInfoDiffusionTerminal)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInfoDiffusionTerminal)
	afx_msg void OnBtnExit();
	afx_msg void OnBtnTerminalConfig();
	afx_msg void OnBtnTerminalControl();
	afx_msg void OnBtnTerminalStatus();
	afx_msg void OnBtnTerminalPlay();
	afx_msg void OnBtnTerminalGroup();
	afx_msg void OnBtnTerminalUpgrade();
	afx_msg void OnBtnTerminalPreview();
	afx_msg void OnBtnTerminalServer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINFODIFFUSIONTERMINAL_H__82D724E9_E57E_4E2B_BB6E_FB30C081400C__INCLUDED_)
