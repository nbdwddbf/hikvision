#if !defined(AFX_DLGSECURITYCFG_H__CC210827_D541_4BCD_B8AB_845C2468DC40__INCLUDED_)
#define AFX_DLGSECURITYCFG_H__CC210827_D541_4BCD_B8AB_845C2468DC40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSecurityCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSecurityCfg dialog

#define IPADDRESSLEN 15
class CDlgSecurityCfg : public CDialog
{
// Construction
public:
	CDlgSecurityCfg(CWnd* pParent = NULL);   // standard constructor
	int m_iDeviceIndex;
	long m_lUserId;
	NET_DVR_SECURITY_CFG m_struSecurityCfg;
// Dialog Data
	//{{AFX_DATA(CDlgSecurityCfg)
	enum { IDD = IDD_DLG_SECURITY_CFG };
	CComboBox	m_cmLoginLevel;
	BOOL		m_bchkTelnet;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSecurityCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSecurityCfg)
	afx_msg void OnBtnGet();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtinSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSECURITYCFG_H__CC210827_D541_4BCD_B8AB_845C2468DC40__INCLUDED_)
