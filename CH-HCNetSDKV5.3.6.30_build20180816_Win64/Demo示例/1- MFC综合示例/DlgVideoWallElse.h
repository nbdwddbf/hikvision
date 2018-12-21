#if !defined(AFX_DLGVIDEOWALLELSE_H__A555AA57_6E15_4628_A794_7A1FC2CE0456__INCLUDED_)
#define AFX_DLGVIDEOWALLELSE_H__A555AA57_6E15_4628_A794_7A1FC2CE0456__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVideoWallElse.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoWallElse dialog

class CDlgVideoWallElse : public CDialog
{
// Construction
public:
	CDlgVideoWallElse(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVideoWallElse)
	enum { IDD = IDD_DLG_VIDEOWALL_ELSESET };
	CComboBox	m_CmCutPictureMode;
	DWORD	m_dwSubWinNo;
	DWORD	m_dwWallNo;
	DWORD	m_dwWinNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVideoWallElse)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVideoWallElse)
	virtual BOOL OnInitDialog();
	afx_msg void OnButCPMRefresh();
	afx_msg void OnButCPMSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lUserID;
	int m_iDeviceIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIDEOWALLELSE_H__A555AA57_6E15_4628_A794_7A1FC2CE0456__INCLUDED_)
