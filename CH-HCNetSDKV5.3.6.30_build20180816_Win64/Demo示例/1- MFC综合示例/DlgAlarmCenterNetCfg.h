#if !defined(AFX_DLGALARMCENTERNETCFG_H__896698C9_0E6B_4A5F_AC94_492A8C398951__INCLUDED_)
#define AFX_DLGALARMCENTERNETCFG_H__896698C9_0E6B_4A5F_AC94_492A8C398951__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmCenterNetCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmCenterNetCfg dialog

class CDlgAlarmCenterNetCfg : public CDialog
{
// Construction
public:
	CDlgAlarmCenterNetCfg(CWnd* pParent = NULL);   // standard constructor

	int m_iDeviceIndex;
	LONG m_lUserID;

// Dialog Data
	//{{AFX_DATA(CDlgAlarmCenterNetCfg)
	enum { IDD = IDD_DLG_ALARM_CENTER_NETCFG };
	CString	m_csAuxiliaryAddr;
	int		m_iAuxiliaryPort;
	CString	m_csHostAddr1;
	short	m_wHostPort1;
	CString	m_csHostAddr2;
	short	m_wHostPort2;
	CString	m_csHostAddr3;
	short	m_wHostPort3;
	CString	m_csHostAddr4;
	short	m_wHostPort4;
	CString	m_csHostAddr5;
	short	m_wHostPort5;
	CString	m_csHostAddr6;
	short	m_wHostPort6;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmCenterNetCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmCenterNetCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMCENTERNETCFG_H__896698C9_0E6B_4A5F_AC94_492A8C398951__INCLUDED_)
