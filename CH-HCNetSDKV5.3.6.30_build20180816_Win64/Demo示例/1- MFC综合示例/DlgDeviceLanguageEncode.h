#if !defined(AFX_DLGDEVICELANGUAGEENCODE_H__10538F2C_31FA_4C25_8849_DE3287A08BF1__INCLUDED_)
#define AFX_DLGDEVICELANGUAGEENCODE_H__10538F2C_31FA_4C25_8849_DE3287A08BF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDeviceLanguageEncode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDeviceLanguageEncode dialog

class CDlgDeviceLanguageEncode : public CDialog
{
// Construction
public:
	CDlgDeviceLanguageEncode(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDeviceLanguageEncode)
	enum { IDD = IDD_DLG_DEVICE_LANGUAGE_ENCODE };
	CString	m_strEncodeFormat;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDeviceLanguageEncode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
public:
	LONG	m_lLoginID;
	LONG	m_lChannel;
	LONG	m_iDeviceIndex;
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDeviceLanguageEncode)
	afx_msg void OnBtnGet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDEVICELANGUAGEENCODE_H__10538F2C_31FA_4C25_8849_DE3287A08BF1__INCLUDED_)
