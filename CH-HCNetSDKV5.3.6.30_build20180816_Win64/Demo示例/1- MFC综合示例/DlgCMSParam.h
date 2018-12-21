#include "afxwin.h"
#if !defined(AFX_DLGCMSPARAM_H__D5DE62DD_AEE9_473D_9F9A_180B61725756__INCLUDED_)
#define AFX_DLGCMSPARAM_H__D5DE62DD_AEE9_473D_9F9A_180B61725756__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCMSParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgCMSParam dialog

class DlgCMSParam : public CDialog
{
// Construction
public:
	DlgCMSParam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgCMSParam)
	enum { IDD = IDD_DLG_CMS_PARAM };
	CComboBox	m_cmbAddrType;
	CComboBox	m_ProtocolType;
	CComboBox	m_index;
	CComboBox   m_networkType;
	BOOL	m_bRegister;
	CString	m_sDeviceID;
	CString	m_sIP;
	UINT	m_Port;
	CString	m_sVersion;
	CString	m_csDomain;
    BOOL m_bEnable;
	//}}AFX_DATA

	NET_DVR_CMS_PARAM m_struCmsParam;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgCMSParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgCMSParam)
	virtual BOOL OnInitDialog();
	afx_msg void OnSet();
	afx_msg void OnGet();
	afx_msg void OnChangeDeviceid();
	afx_msg void OnSelchangeIndex();
	afx_msg void OnSelchangeCmbAddrType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    CComboBox m_comboProtocolVersion;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCMSPARAM_H__D5DE62DD_AEE9_473D_9F9A_180B61725756__INCLUDED_)
