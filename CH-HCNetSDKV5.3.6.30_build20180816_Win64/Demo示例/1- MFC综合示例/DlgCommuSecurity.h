#if !defined(AFX_DLGCOMMUSECURITY_H__17DC414C_3703_4FC4_9564_29D36A527C44__INCLUDED_)
#define AFX_DLGCOMMUSECURITY_H__17DC414C_3703_4FC4_9564_29D36A527C44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCommuSecurity.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgCommuSecurity dialog

class DlgCommuSecurity : public CDialog
{
// Construction
public:
	DlgCommuSecurity(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgCommuSecurity)
	enum { IDD = IDD_DLG_COMMU_SECURITY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgCommuSecurity)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgCommuSecurity)
	afx_msg void OnBtnSecrityCfg();
	afx_msg void OnBtnPwManageCfg();
	afx_msg void OnBnClickedBtnEncryptCert();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lUSerID;
    LONG    m_lChannel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCOMMUSECURITY_H__17DC414C_3703_4FC4_9564_29D36A527C44__INCLUDED_)
