#if !defined(AFX_DLGUPLOADLOGO_H__E2FC2B3B_2813_4B5A_BCD2_FDC241E6BBE0__INCLUDED_)
#define AFX_DLGUPLOADLOGO_H__E2FC2B3B_2813_4B5A_BCD2_FDC241E6BBE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgUploadLogo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgUploadLogo dialog

class CDlgUploadLogo : public CDialog
{
// Construction
public:
	CDlgUploadLogo(CWnd* pParent = NULL);   // standard constructor

    LONG m_lServerID;
	int  m_iDevIndex;
    int m_iCurChanIndex;
    LONG m_lStartChan;
    int  m_iChannelNumber;
    int m_iChannel;
	NET_DVR_LOGO_OVERLAYCFG m_struLogoOverlay;

// Dialog Data
	//{{AFX_DATA(DlgUploadLogo)
	enum { IDD = IDD_DLG_MATUPLOADLOGO };
	CComboBox	m_DecChanCtrl;
	CString	m_strLogodir;
	DWORD	m_dwXcoordinate;
	DWORD	m_dwYcoordinate;
	BOOL	m_bFlush;
	BOOL	m_bTranslucent;
	DWORD	m_dwHeight;
	DWORD	m_dwWidth;
	BOOL	m_bChkEnableOverlay;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgUploadLogo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgUploadLogo)
    virtual BOOL OnInitDialog();
	afx_msg void OnBrowse();
	afx_msg void OnUploadlogobtn();
	afx_msg void OnExit();
	afx_msg void OnShowlogo();
	afx_msg void OnHidelogo();
	afx_msg void OnBtnGetLogoOverlaycfg();
	afx_msg void OnBtnSetLogoOverlaycfg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGUPLOADLOGO_H__E2FC2B3B_2813_4B5A_BCD2_FDC241E6BBE0__INCLUDED_)
