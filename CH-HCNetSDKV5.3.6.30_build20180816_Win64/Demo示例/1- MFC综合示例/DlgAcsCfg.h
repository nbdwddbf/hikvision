#if !defined(AFX_DLGACSCFG_H__C86842FE_9540_4ECC_A184_58A1A2B756C0__INCLUDED_)
#define AFX_DLGACSCFG_H__C86842FE_9540_4ECC_A184_58A1A2B756C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAcsCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgAcsCfg dialog

class DlgAcsCfg : public CDialog
{
// Construction
public:
	DlgAcsCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgAcsCfg)
	enum { IDD = IDD_DIA_ACS_CFG };
	BOOL	m_byRS485Backup;
    BOOL	m_byInputCardNo;
	BOOL	m_bOverlayUserInfo;
	BOOL	m_bShowCapPic;
	BOOL	m_bShowCardNo;
	BOOL	m_bShowUserInfo;
	BOOL	m_bVoicePrompt;
    BOOL	m_bLinkCapPic;
	BOOL	m_bSaveCapPic;
    BOOL    m_byEnableWifiDetect;
    BOOL    m_byEnable3G4G;
	//}}AFX_DATA

    NET_DVR_ACS_CFG m_struAcsCfg;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgAcsCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgAcsCfg)
    virtual BOOL OnInitDialog();
    afx_msg void OnSet();
	afx_msg void OnGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGACSCFG_H__C86842FE_9540_4ECC_A184_58A1A2B756C0__INCLUDED_)
