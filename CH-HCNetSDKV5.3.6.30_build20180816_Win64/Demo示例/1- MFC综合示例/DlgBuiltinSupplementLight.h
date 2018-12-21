#if !defined(AFX_DLGBUILTINSUPPLEMENTLIGHT_H__C3088633_04AF_44BD_8D56_7A10EB112842__INCLUDED_)
#define AFX_DLGBUILTINSUPPLEMENTLIGHT_H__C3088633_04AF_44BD_8D56_7A10EB112842__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBuiltinSupplementLight.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgBuiltinSupplementLight dialog

class CDlgBuiltinSupplementLight : public CDialog
{
// Construction
public:
	CDlgBuiltinSupplementLight(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgBuiltinSupplementLight)
	enum { IDD = IDD_DLG_BUILTIN_SUPPLEMENTLIGHT };
	COleDateTime	m_TimeStop;
	CComboBox	m_comboMode;
	int		m_iBLimit;
	COleDateTime	m_TimeStart;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBuiltinSupplementLight)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgBuiltinSupplementLight)
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    NET_DVR_BUILTIN_SUPPLEMENTLIGHT m_struBuiltinSupplementLight;

    LONG m_lServerID;
	int m_iDeviceIndex;
    LONG m_lChannel;
    char m_szStatusBuf[ISAPI_STATUS_LEN];

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBUILTINSUPPLEMENTLIGHT_H__C3088633_04AF_44BD_8D56_7A10EB112842__INCLUDED_)
