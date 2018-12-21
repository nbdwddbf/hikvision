#if !defined(AFX_DLGALARMCENTERSERVERCFG_H__56DB1ADD_FEE5_4C47_B2E4_8DE3A59A8771__INCLUDED_)
#define AFX_DLGALARMCENTERSERVERCFG_H__56DB1ADD_FEE5_4C47_B2E4_8DE3A59A8771__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmCenterServerCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmCenterServerCfg dialog

class CDlgAlarmCenterServerCfg : public CDialog
{
// Construction
public:
	CDlgAlarmCenterServerCfg(CWnd* pParent = NULL);   // standard constructor

	LONG m_lUserID;
	int m_iDeviceIndex;

// Dialog Data
	//{{AFX_DATA(CDlgAlarmCenterServerCfg)
	enum { IDD = IDD_DLG_ALARM_CENTER_SVR_CFG };
	CComboBox	m_cmbServerType;
	UINT	m_nIntervalTime;
	CString	m_csIP;
	UINT	m_nPort;
	CString	m_csIPV6;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmCenterServerCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmCenterServerCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnSelchangeComboServertype();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMCENTERSERVERCFG_H__56DB1ADD_FEE5_4C47_B2E4_8DE3A59A8771__INCLUDED_)
