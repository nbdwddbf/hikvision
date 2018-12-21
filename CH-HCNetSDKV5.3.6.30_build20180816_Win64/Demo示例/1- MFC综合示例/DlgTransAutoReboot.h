#if !defined(AFX_DLGTRANSAUTOREBOOT_H__DC3815E8_4925_402F_8EF5_BFDC08F283DE__INCLUDED_)
#define AFX_DLGTRANSAUTOREBOOT_H__DC3815E8_4925_402F_8EF5_BFDC08F283DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTransAutoReboot.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTransAutoReboot dialog

class CDlgTransAutoReboot : public CDialog
{
// Construction
public:
	CDlgTransAutoReboot(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTransAutoReboot)
	enum { IDD = IDD_DLG_TRANS_AUTO_REBOOT };
	CComboBox	m_comboDisplayMode;
	CComboBox	m_comboWorkMode;
	CComboBox	m_comboRebootDate;
	CComboBox	m_comboAutoRebootMode;
	BYTE	m_byHour;
	BYTE	m_byMinute;
	BOOL	m_BEnableVCADec;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTransAutoReboot)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTransAutoReboot)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lUserID;
	int  m_iDeviceIndex;
	NET_DVR_DEV_WORK_MODE m_struDevWorkMode;
	NET_DVR_AUTO_REBOOT_CFG m_struAutoReboot;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRANSAUTOREBOOT_H__DC3815E8_4925_402F_8EF5_BFDC08F283DE__INCLUDED_)
