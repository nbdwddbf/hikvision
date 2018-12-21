#if !defined(AFX_DLGKEYBOARDCFG_H__D5FDA124_B15D_4595_BB8B_74A3D10B4970__INCLUDED_)
#define AFX_DLGKEYBOARDCFG_H__D5FDA124_B15D_4595_BB8B_74A3D10B4970__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgKeyboardCfg.h : header file
//
 
/////////////////////////////////////////////////////////////////////////////
// CDlgKeyboardCfg dialog

class CDlgKeyboardCfg : public CDialog
{
// Construction
public:
	CDlgKeyboardCfg(CWnd* pParent = NULL);   // standard constructor

	int m_iDeviceIndex;
	LONG m_lUserID;

// Dialog Data
	//{{AFX_DATA(CDlgKeyboardCfg)
	enum { IDD = IDD_DLG_KEYBOARD_CFG };
	CComboBox	m_cmbKeyboardID;
	BOOL	m_bKeyBoardLock;
	UINT	m_nLockTime;
	UINT	m_nErrortimes;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgKeyboardCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgKeyboardCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGKEYBOARDALARMCFG_H__D5FDA124_B15D_4595_BB8B_74A3D10B4970__INCLUDED_)
