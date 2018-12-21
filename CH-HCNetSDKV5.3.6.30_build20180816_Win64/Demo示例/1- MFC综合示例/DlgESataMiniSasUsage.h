#if !defined(AFX_DLGESATAMINISASUSAGE_H__E2858CD3_039F_446F_9AEE_BC4463D2E363__INCLUDED_)
#define AFX_DLGESATAMINISASUSAGE_H__E2858CD3_039F_446F_9AEE_BC4463D2E363__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgESataMiniSasUsage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgESataMiniSasUsage dialog

class CDlgESataMiniSasUsage : public CDialog
{
// Construction
public:
	CDlgESataMiniSasUsage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgESataMiniSasUsage)
	enum { IDD = IDD_DIALOG_ESATA_MINISAS_USAGE };
	CComboBox	m_cmbESata;
	CComboBox	m_cmbESataUsage;
	CComboBox	m_cmbMiniSas;
	CComboBox	m_cmbMiniSasUsage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgESataMiniSasUsage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgESataMiniSasUsage)
	afx_msg void OnSelchangeComboMinisas();
	afx_msg void OnSelchangeComboEsata();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonGet();
	afx_msg void OnButtonEsataSave();
	afx_msg void OnButtonMinisasSave();
	afx_msg void OnButtonSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lUserID;
	DWORD m_dwDevIndex;
	NET_DVR_ESATA_MINISAS_USAGE m_struESataMiniSasUsage;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGESATAMINISASUSAGE_H__E2858CD3_039F_446F_9AEE_BC4463D2E363__INCLUDED_)
