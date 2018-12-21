#if !defined(AFX_DLGVCADRAWMODE_H__07FC826E_4E6C_4458_B869_C9B80E647E52__INCLUDED_)
#define AFX_DLGVCADRAWMODE_H__07FC826E_4E6C_4458_B869_C9B80E647E52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaDrawMode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaDrawMode dialog

class CDlgVcaDrawMode : public CDialog
{
// Construction
public:
	CDlgVcaDrawMode(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaDrawMode)
	enum { IDD = IDD_DLG_VCA_DRAW_MODE };
	CComboBox	m_cmbChannel;	
	BOOL	m_bDSPAddRule;
    BOOL	m_bDSPAddTarget;
    BOOL	m_bPicAddRule;
    BOOL	m_bPicAddTarget;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaDrawMode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaDrawMode)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSetDrawMode();
	afx_msg void OnBtnGetDrawMode();
	afx_msg void OnSelchangeComboChannel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG m_lChannel; 
    int  m_iDevIndex;
    LONG m_lServerID;
    NET_VCA_DRAW_MODE   m_struVCADrawMode;
public:
    BOOL SetVcaDrawMode();
    BOOL GetVcaDrawMode();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCADRAWMODE_H__07FC826E_4E6C_4458_B869_C9B80E647E52__INCLUDED_)
