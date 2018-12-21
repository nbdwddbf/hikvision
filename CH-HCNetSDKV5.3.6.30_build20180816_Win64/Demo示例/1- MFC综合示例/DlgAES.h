#if !defined(AFX_DLGAES_H__BD7F5970_76EF_41B6_9AC0_64E13AC172B4__INCLUDED_)
#define AFX_DLGAES_H__BD7F5970_76EF_41B6_9AC0_64E13AC172B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAES.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAES dialog

class CDlgAES : public CDialog
{
// Construction
public:
	CDlgAES(CWnd* pParent = NULL);   // standard constructor

	LONG m_lUSerID;
	DWORD m_dwDeviceIndex;

// Dialog Data
	//{{AFX_DATA(CDlgAES)
	enum { IDD = IDD_DLG_AES };
	CComboBox	m_comboState;
	CString	m_csKey;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAES)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAES)
	afx_msg void OnButtonUpdateKey();
	afx_msg void OnButtonSetSdkKey();
	afx_msg void OnButtonSetState();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonGetState();
	afx_msg void OnButtonExit();
	afx_msg void OnBtnSetCodeKey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAES_H__BD7F5970_76EF_41B6_9AC0_64E13AC172B4__INCLUDED_)
