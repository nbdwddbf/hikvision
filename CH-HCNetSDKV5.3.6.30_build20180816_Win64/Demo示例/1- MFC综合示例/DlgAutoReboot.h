#if !defined(AFX_DLGAUTOREBOOT_H__D8C7A660_9B76_4726_97B0_E01E27E574D9__INCLUDED_)
#define AFX_DLGAUTOREBOOT_H__D8C7A660_9B76_4726_97B0_E01E27E574D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAutoReboot.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAutoReboot dialog

class CDlgAutoReboot : public CDialog
{
// Construction
public:
	CDlgAutoReboot(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAutoReboot)
	enum { IDD = IDD_DLG_AUTO_REBOOT };
	CComboBox	m_comboDate;
	BYTE	m_byHour;
	BYTE	m_byMin;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAutoReboot)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAutoReboot)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lUserID;
	int  m_iDeviceIndex;
	NET_DVR_AUTO_REBOOT_CFG m_struRebootTime;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAUTOREBOOT_H__D8C7A660_9B76_4726_97B0_E01E27E574D9__INCLUDED_)
