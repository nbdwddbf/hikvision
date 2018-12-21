#if !defined(AFX_DLGACSSNAPCFG_H__8A52AD30_9C3F_4C67_8B5A_D3277B044D2A__INCLUDED_)
#define AFX_DLGACSSNAPCFG_H__8A52AD30_9C3F_4C67_8B5A_D3277B044D2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAcsSnapCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgAcsSnapCfg dialog

class DlgAcsSnapCfg : public CDialog
{
// Construction
public:
	DlgAcsSnapCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgAcsSnapCfg)
	enum { IDD = IDD_DLG_ACS_SNAP_CFG };
	DWORD   m_dwSnapTimes;
    DWORD   m_IntervalTime1;
    DWORD   m_IntervalTime2;
    DWORD   m_IntervalTime3;
    DWORD   m_IntervalTime4;
	//}}AFX_DATA

    NET_DVR_SNAPCFG m_struSnapCfg;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgAcsSnapCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgAcsSnapCfg)
    virtual BOOL OnInitDialog();
    afx_msg void OnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int m_iSnapWaitTime;
	CComboBox m_comboJpegResolution;
	CComboBox m_comboJpegQuality;
	afx_msg void OnBnClickedButtonGet();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGACSSNAPCFG_H__8A52AD30_9C3F_4C67_8B5A_D3277B044D2A__INCLUDED_)
