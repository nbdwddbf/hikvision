#if !defined(AFX_DLGVIDEOINTERCOMAUTHCFG_H__5B3DB213_5E03_4597_BD51_DB7699F7D41E__INCLUDED_)
#define AFX_DLGVIDEOINTERCOMAUTHCFG_H__5B3DB213_5E03_4597_BD51_DB7699F7D41E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVideoIntercomAuthCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomAuthCfg dialog

class CDlgVideoIntercomAuthCfg : public CDialog
{
// Construction
public:
	CDlgVideoIntercomAuthCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVideoIntercomAuthCfg)
	enum { IDD = IDD_DLG_VIDEO_INTERCOM_AUTH_CFG };
	CString	m_csPassWord;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVideoIntercomAuthCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVideoIntercomAuthCfg)
	afx_msg void OnBtnTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lUserID;
    LONG m_iDevIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIDEOINTERCOMAUTHCFG_H__5B3DB213_5E03_4597_BD51_DB7699F7D41E__INCLUDED_)
