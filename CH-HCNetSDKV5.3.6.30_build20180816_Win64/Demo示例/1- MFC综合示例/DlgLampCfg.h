#if !defined(AFX_DLGLAMPCFG_H__CCE3BD95_0550_42B2_8D68_B23C2B512608__INCLUDED_)
#define AFX_DLGLAMPCFG_H__CCE3BD95_0550_42B2_8D68_B23C2B512608__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLampCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLampCfg dialog

class CDlgLampCfg : public CDialog
{
// Construction
public:
	CDlgLampCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLampCfg)
	enum { IDD = IDD_DLG_TRIAL_LAMP_INFO };
	CComboBox	m_comboLamp;
	BOOL	m_bEnable;
	CString	m_sLampName;
	CString	m_sLampStatus1;
	CString	m_sLampStatus2;
	CString	m_sLampStatus3;
	//}}AFX_DATA

	int m_iDeviceIndex;
	LONG m_lUserID;
	NET_DVR_LAMP_OUT m_struLampOut;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLampCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLampCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnOk();
	afx_msg void OnSelchangeComboLamp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLAMPCFG_H__CCE3BD95_0550_42B2_8D68_B23C2B512608__INCLUDED_)
