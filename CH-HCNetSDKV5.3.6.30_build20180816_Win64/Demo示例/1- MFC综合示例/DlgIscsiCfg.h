#if !defined(AFX_DLGISCSICFG_H__2FE95E6F_6273_4929_A58C_1231544CB73C__INCLUDED_)
#define AFX_DLGISCSICFG_H__2FE95E6F_6273_4929_A58C_1231544CB73C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIscsiCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgIscsiCfg dialog

class CDlgIscsiCfg : public CDialog
{
// Construction
public:
	CDlgIscsiCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgIscsiCfg)
	enum { IDD = IDD_DLG_ISCSI_CFG };
	BOOL	m_bEnable;
	CString	m_csNvtIndexCode;
	int		m_iPort;
	CString	m_csIpAddr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIscsiCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIscsiCfg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnChangeEditVrmPort();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    long m_lServerID;
    long m_iDevIndex;
    NET_DVR_ISCSI_CFG m_struIscsiCfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGISCSICFG_H__2FE95E6F_6273_4929_A58C_1231544CB73C__INCLUDED_)
