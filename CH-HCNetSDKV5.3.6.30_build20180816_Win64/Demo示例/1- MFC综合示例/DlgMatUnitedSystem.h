#if !defined(AFX_DLGMATUNITEDSYSTEM_H__A30ACF3E_E0BD_48EE_A5A4_7C9A4885192F__INCLUDED_)
#define AFX_DLGMATUNITEDSYSTEM_H__A30ACF3E_E0BD_48EE_A5A4_7C9A4885192F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMatUnitedSystem.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMatUnitedSystem dialog

class CDlgMatUnitedSystem : public CDialog
{
// Construction
public:
	CDlgMatUnitedSystem(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMatUnitedSystem)
	enum { IDD = IDD_DLG_MAT_UNITED_SYSTEM };
	CComboBox	m_comboSystemNum;
	CString	m_csAdress;
	CString	m_csPassWord;
	DWORD	m_wPort;
	DWORD	m_dwSeq;
	CString	m_csUserName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMatUnitedSystem)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMatUnitedSystem)
	afx_msg void OnBtnGet();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboSystemNum();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lUserID;
	LONG m_iDeviceIndex;
	NET_DVR_UNITEDMATRIXSYSTEMINFO m_struInfo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMATUNITEDSYSTEM_H__A30ACF3E_E0BD_48EE_A5A4_7C9A4885192F__INCLUDED_)
