#if !defined(AFX_DLGTHSCREEN_H__A56FBBD0_A4F6_4E18_B6C5_81E8AC94894E__INCLUDED_)
#define AFX_DLGTHSCREEN_H__A56FBBD0_A4F6_4E18_B6C5_81E8AC94894E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgThscreen.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgThscreen dialog

class CDlgThscreen : public CDialog
{
// Construction
public:
	CDlgThscreen(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgThscreen)
	enum { IDD = IDD_DLG_THSCREEN };
	CComboBox	m_comTimingMode;
	BOOL	m_bEnable;
	BOOL	m_bOSDDisplayEnable;
	int		m_iInterval;
	float	m_fX;
	float	m_fY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgThscreen)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgThscreen)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
    afx_msg void OnBtnThScreenTiming();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG m_lLoginID;
    INT  m_iDeviceIndex;
	LONG m_lChannel;
	
    char    m_szStatusBuf[ISAPI_STATUS_LEN];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTHSCREEN_H__A56FBBD0_A4F6_4E18_B6C5_81E8AC94894E__INCLUDED_)
