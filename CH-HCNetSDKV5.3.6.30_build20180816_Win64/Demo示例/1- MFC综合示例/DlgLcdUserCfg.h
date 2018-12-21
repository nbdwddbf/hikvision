#if !defined(AFX_DLGLCDUSERCFG_H__1720A71A_EE58_43D7_AD11_6606138320A8__INCLUDED_)
#define AFX_DLGLCDUSERCFG_H__1720A71A_EE58_43D7_AD11_6606138320A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLcdUserCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLcdUserCfg dialog

class CDlgLcdUserCfg : public CDialog
{
// Construction
public:
	CDlgLcdUserCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLcdUserCfg)
	enum { IDD = IDD_DLG_LCD_USER_CFG };
	CIPAddressCtrl	m_cIp;
	CComboBox	m_comboUserIndex;
	CComboBox	m_comboPriority;
	CString	m_csMacAddr;
	CString	m_csPassword;
	CString	m_csPasswordSure;
	CString	m_csUserName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLcdUserCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLcdUserCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG m_lUserId;
    int m_iDeviceIndex;
    NET_DVR_VCS_USER_INFO m_struUserCfg;
    char m_szLan[64];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLCDUSERCFG_H__1720A71A_EE58_43D7_AD11_6606138320A8__INCLUDED_)
