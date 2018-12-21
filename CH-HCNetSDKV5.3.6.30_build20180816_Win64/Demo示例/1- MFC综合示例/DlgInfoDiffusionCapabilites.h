#if !defined(AFX_DLGINFODIFFUSIONCAPABILITES_H__D7E5FBE1_57E1_4F71_9191_784E3896FB1F__INCLUDED_)
#define AFX_DLGINFODIFFUSIONCAPABILITES_H__D7E5FBE1_57E1_4F71_9191_784E3896FB1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInfoDiffusionCapabilites.h : header file
//

#define MAX_LEN_XML 10*1024*1024 //xml最大长度

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionCapabilites dialog

class CDlgInfoDiffusionCapabilites : public CDialog
{
// Construction
public:
	CDlgInfoDiffusionCapabilites(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInfoDiffusionCapabilites)
	enum { IDD = IDD_DLG_INFO_DIFFUSION_CAPABILITES };
	CComboBox	m_cmbCapablitesType;
	CString	m_szCapabilites;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInfoDiffusionCapabilites)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInfoDiffusionCapabilites)
	afx_msg void OnBtnExit();
	afx_msg void OnBtnGetCapabilites();
	afx_msg void OnSelchangeComboCapabilitesType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	LONG m_lUserID;
	int m_iDeviceIndex;

	CString m_szCommand;

	char* m_pOutputXmlBuffer;
	
public:
    virtual BOOL OnInitDialog();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINFODIFFUSIONCAPABILITES_H__D7E5FBE1_57E1_4F71_9191_784E3896FB1F__INCLUDED_)
