#if !defined(AFX_DLGACSSMSCFG_H__5DD439E4_5E24_442C_8A6F_1BB7F7581E4C__INCLUDED_)
#define AFX_DLGACSSMSCFG_H__5DD439E4_5E24_442C_8A6F_1BB7F7581E4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAcsSmsCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgAcsSmsCfg dialog

class DlgAcsSmsCfg : public CDialog
{
// Construction
public:
	DlgAcsSmsCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgAcsSmsCfg)
	enum { IDD = IDD_DLG_ACS_SMS_CFG };
    CComboBox	m_comboWhiteList;
    BOOL	m_byPhonePerssion;
    CString	m_sPhoneNo;
    CString	m_sAcsPassword;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgAcsSmsCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    int m_iDeviceIndex;
    long m_lUserID;
	NET_DVR_SMSRELATIVEPARAM_V50 m_struSmsCfg;
	// Generated message map functions
	//{{AFX_MSG(DlgAcsSmsCfg)
    virtual BOOL OnInitDialog();
    afx_msg void OnSelchangeWhiteList();
    afx_msg void OnBtnSure();
    afx_msg void OnBtnGet();
    afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGACSSMSCFG_H__5DD439E4_5E24_442C_8A6F_1BB7F7581E4C__INCLUDED_)
