#if !defined(AFX_DLGVCADEVACCESSCFG_H__D5B92B87_9AC1_417A_B2B6_BE18A5FA274D__INCLUDED_)
#define AFX_DLGVCADEVACCESSCFG_H__D5B92B87_9AC1_417A_B2B6_BE18A5FA274D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaDevAccessCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaDevAccessCfg dialog

class CDlgVcaDevAccessCfg : public CDialog
{
// Construction
public:
	CDlgVcaDevAccessCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaDevAccessCfg)
	enum { IDD = IDD_DLG_DEV_ACCESS_CFG };
	BOOL	m_bChkAccessEn;
	CString	m_csIP;
	DWORD	m_dwPort;
	CString	m_csPassword;
	CString	m_csUserName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaDevAccessCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaDevAccessCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG    m_lServerID;
    LONG    m_lChannel;
    int     m_iDevIndex;
	NET_DVR_DEV_ACCESS_CFG m_struDevAccessCfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCADEVACCESSCFG_H__D5B92B87_9AC1_417A_B2B6_BE18A5FA274D__INCLUDED_)
