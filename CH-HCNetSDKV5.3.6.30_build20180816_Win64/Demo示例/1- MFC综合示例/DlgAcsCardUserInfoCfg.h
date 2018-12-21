#if !defined(AFX_DLGACSCARDUSERINFOCFG_H__50381B92_41F6_4661_A3F9_A2931ECAA1BE__INCLUDED_)
#define AFX_DLGACSCARDUSERINFOCFG_H__50381B92_41F6_4661_A3F9_A2931ECAA1BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAcsCardUserInfoCfg1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAcsCardUserInfoCfg dialog

class CDlgAcsCardUserInfoCfg : public CDialog
{
// Construction
public:
	CDlgAcsCardUserInfoCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAcsCardUserInfoCfg)
	enum { IDD = IDD_DLG_ACS_CARD_USERINFO };
	CString	m_csCardNo;
	CString	m_csUserName;
    CComboBox	m_Index;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAcsCardUserInfoCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAcsCardUserInfoCfg)
	afx_msg void OnButtonGet();
	afx_msg void OnButtonSet();
    afx_msg void OnBtnSure();
    afx_msg void OnSelchangeIndex();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG m_lUserID;
	int m_iDevIndex;

	NET_DVR_CARD_CFG_SEND_DATA m_struCond;
	NET_DVR_CARD_USER_INFO_CFG m_struUserInfo;
	BYTE m_csUserNum;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGACSCARDUSERINFOCFG_H__50381B92_41F6_4661_A3F9_A2931ECAA1BE__INCLUDED_)
