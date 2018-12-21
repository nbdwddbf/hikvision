#if !defined(AFX_DLGCUNTOMPROTOCAL_H__C3625A14_11D2_4AA2_9E22_DF52EE164F74__INCLUDED_)
#define AFX_DLGCUNTOMPROTOCAL_H__C3625A14_11D2_4AA2_9E22_DF52EE164F74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCuntomProtocal.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCuntomProtocal dialog

class CDlgCuntomProtocal : public CDialog
{
// Construction
public:
	CDlgCuntomProtocal(CWnd* pParent = NULL);   // standard constructor
	
	NET_DVR_CUSTOM_PROTOCAL m_strProtocal;
	
	LONG m_lUserID;
	DWORD m_dwDevIndex;


// Dialog Data
	//{{AFX_DATA(CDlgCuntomProtocal)
	enum { IDD = IDD_DLG_CUSTOM_PROTOCAL };
	CComboBox	m_cmbSubTransType;
	CComboBox	m_cmbMainTransType;
	CComboBox	m_comboIndex;
	CComboBox	m_comboMainType;
	CComboBox	m_comboSubType;
	DWORD	m_dwSubPort;
	DWORD	m_dwMainPort;
	CString	m_csSubPath;
	CString	m_csProName;
	CString	m_csMainPath;
	BOOL	m_bEnableSub;
	BOOL	m_bEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCuntomProtocal)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCuntomProtocal)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonExit();
	afx_msg void OnButtonUpdate();
	afx_msg void OnSelchangeComboProIndex();
	afx_msg void OnButtonSetup();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCUNTOMPROTOCAL_H__C3625A14_11D2_4AA2_9E22_DF52EE164F74__INCLUDED_)
