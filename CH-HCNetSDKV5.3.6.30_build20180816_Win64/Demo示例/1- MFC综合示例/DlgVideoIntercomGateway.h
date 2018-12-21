#if !defined(AFX_DLGVIDEOINTERCOMGATEWAY_H__F9E9E9F6_CA2B_4BED_9F5A_CFB8D16F7583__INCLUDED_)
#define AFX_DLGVIDEOINTERCOMGATEWAY_H__F9E9E9F6_CA2B_4BED_9F5A_CFB8D16F7583__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVideoIntercomGateway.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomGateway dialog

class CDlgVideoIntercomGateway : public CDialog
{
// Construction
public:
	CDlgVideoIntercomGateway(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVideoIntercomGateway)
	enum { IDD = IDD_DLG_VIDEO_INTERCOM_GATEWAY };
	CComboBox	m_comboOpenLockType;
	CComboBox	m_comboLockType;
	CComboBox	m_comboCommand;
	CString	m_strControlSrcInfo;
	DWORD	m_dwGatewayIndex;
	CString	m_strLockPassword;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVideoIntercomGateway)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVideoIntercomGateway)
	afx_msg void OnBtnSet();
	afx_msg void OnSelchangeComboLocktype();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	BOOL ControlGateway();
public:
	LONG m_lServerID;
	int  m_iDevIndex;
    int m_iLockID;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIDEOINTERCOMGATEWAY_H__F9E9E9F6_CA2B_4BED_9F5A_CFB8D16F7583__INCLUDED_)
