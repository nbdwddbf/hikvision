#if !defined(AFX_DLGSDIMATRIX_H__32F87273_A7A2_41DB_85AF_997ACFF49530__INCLUDED_)
#define AFX_DLGSDIMATRIX_H__32F87273_A7A2_41DB_85AF_997ACFF49530__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSDIMatrix.h : header file
//
extern CClientDemoDlg *g_pMainDlg;
/////////////////////////////////////////////////////////////////////////////
// CDlgSDIMatrix dialog

class CDlgSDIMatrix : public CDialog
{
// Construction
public:
	CDlgSDIMatrix(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSDIMatrix)
	enum { IDD = IDD_DLG_SDI_MATRIX };
	CButton	m_btnChangePassword;
	CButton	m_btnOneSwitchAll;
	CListBox	m_ctrRelationDisplay;
	DWORD	m_dwInputNum;
	DWORD	m_dwOutputNum;
	DWORD	m_dwOutputChannel;
	DWORD	m_dwInputChannel;
	CString	m_csUserPassword;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSDIMatrix)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSDIMatrix)
	afx_msg void OnBtnSdiRefresh();
	afx_msg void OnBtnSdiDelallrelation();
	afx_msg void OnBtnSdiBasecfgRefresh();
	afx_msg void OnBtnSdiBasecfgSet();
	afx_msg void OnBtnSdiSwitch();
	virtual BOOL OnInitDialog();
	afx_msg void OnChkSdiOneswitchall();
	afx_msg void OnBtnSdiChangepassword();
	afx_msg void OnChkSdiChangepassword();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
    bool SwitchIO(DWORD input, DWORD output);
public:
    LONG    m_lUserID;
    LONG    m_iDevIndex;
    DWORD   m_dwChannel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSDIMATRIX_H__32F87273_A7A2_41DB_85AF_997ACFF49530__INCLUDED_)
