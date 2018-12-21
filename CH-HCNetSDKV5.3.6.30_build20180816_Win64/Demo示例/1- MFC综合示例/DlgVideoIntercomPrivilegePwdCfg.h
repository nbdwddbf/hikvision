#if !defined(AFX_DLGVIDEOINTERCOMPRIVILEGEPWDCFG_H__F60E3516_66F0_4BE1_B5A7_7F1FA8C9089E__INCLUDED_)
#define AFX_DLGVIDEOINTERCOMPRIVILEGEPWDCFG_H__F60E3516_66F0_4BE1_B5A7_7F1FA8C9089E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVideoIntercomPrivilegePwdCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomPrivilegePwdCfg dialog

class CDlgVideoIntercomPrivilegePwdCfg : public CDialog
{
// Construction
public:
	CDlgVideoIntercomPrivilegePwdCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVideoIntercomPrivilegePwdCfg)
	enum { IDD = IDD_DLG_VIDEO_INTERCOM_PRIVILEGE_PWD_CFG };
	CComboBox	m_comboPwdType;
	CString	m_strNewPwd;
	CString	m_strOldPwd;
	CString	m_strConfirmNewPwd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVideoIntercomPrivilegePwdCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVideoIntercomPrivilegePwdCfg)
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	void InitCtrlState();
	BOOL SetPrivilegePwdCfg();
public:
	LONG m_lServerID;
	LONG m_iDevIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVIDEOINTERCOMPRIVILEGEPWDCFG_H__F60E3516_66F0_4BE1_B5A7_7F1FA8C9089E__INCLUDED_)
