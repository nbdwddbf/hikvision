#if !defined(AFX_DLGEZVIZACCESSCFG_H__9DFBF838_A941_4508_8BB5_9193FA74EF78__INCLUDED_)
#define AFX_DLGEZVIZACCESSCFG_H__9DFBF838_A941_4508_8BB5_9193FA74EF78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEZVIZAccessCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgEZVIZAccessCfg dialog

class CDlgEZVIZAccessCfg : public CDialog
{
// Construction
public:
	long m_lUserID;
	long m_iCurChanNO;
    int m_iDevIndex;
	CDlgEZVIZAccessCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgEZVIZAccessCfg)
	enum { IDD = IDD_DLG_EZVIZ_ACCESSCFG };
	CComboBox	m_cmbRedirect;
	CComboBox	m_cbEnable;
	CComboBox	m_cbDeviceStatus;
	CString	m_csDomainName;
    CComboBox  m_cmbNetMode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEZVIZAccessCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgEZVIZAccessCfg)
	afx_msg void OnBtnGet();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CString m_csVerificationCode;
    CString m_csOperateCode;
    CString m_strOfflineStatus;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEZVIZACCESSCFG_H__9DFBF838_A941_4508_8BB5_9193FA74EF78__INCLUDED_)
