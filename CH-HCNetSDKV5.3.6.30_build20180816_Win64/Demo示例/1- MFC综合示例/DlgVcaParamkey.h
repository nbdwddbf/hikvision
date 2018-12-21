#if !defined(AFX_DLGVCAPARAMKEY_H__951BE587_E3DD_4B94_A647_0B0E389EE2EA__INCLUDED_)
#define AFX_DLGVCAPARAMKEY_H__951BE587_E3DD_4B94_A647_0B0E389EE2EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaParamkey.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaParamkey dialog

class CDlgVcaParamkey : public CDialog
{
// Construction
public:
	CDlgVcaParamkey(CWnd* pParent = NULL);   // standard constructor
	
	int GetParamIndex();
	long	m_lServerID;
	int		m_iDevIndex;
	LONG    m_lChannel;
	DWORD	m_dwParameterKey;

// Dialog Data
	//{{AFX_DATA(CDlgVcaParamkey)
	enum { IDD = IDD_DLG_VCA_PARAMKEY };
	CComboBox	m_ComboParamkey;
	int		m_iKey;
	UINT	m_nParamKey;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaParamkey)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaParamkey)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonGetParamkey();
	virtual void OnOK();
	afx_msg void OnSelchangeComboParamkey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCAPARAMKEY_H__951BE587_E3DD_4B94_A647_0B0E389EE2EA__INCLUDED_)
