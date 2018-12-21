#if !defined(AFX_DLGREMOTECONTROLLERCFG_H__8E3003AF_EBC1_4493_89B4_E304930D5AEC__INCLUDED_)
#define AFX_DLGREMOTECONTROLLERCFG_H__8E3003AF_EBC1_4493_89B4_E304930D5AEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRemoteControllerPermissionCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteControllerCfg dialog

class CDlgRemoteControllerCfg : public CDialog
{
// Construction
public:
	CDlgRemoteControllerCfg(CWnd* pParent = NULL);   // standard constructor

	int m_iDeviceIndex;
	LONG m_lUserID;

// Dialog Data
	//{{AFX_DATA(CDlgRemoteControllerCfg)
	enum { IDD = IDD_DLG_REMOTECONTROLLER_CFG };
	CComboBox	m_cmb_SubSysNo;
	CComboBox	m_cmb_RemoteControllerNo;
	BOOL	m_bArmReportRight;
	BOOL	m_bArmRight;
	BOOL	m_bClearArmRight;
	BOOL	m_bDisArmRight;
	BOOL	m_bDisArmReportRight;
	BOOL	m_bEnable;
    BOOL    m_bEnableDel;
	CString	m_strSerialNo;
	UINT	m_iKeyBoradAddr;
    CComboBox	m_cmbAlwaysOpenRight;
    CComboBox	m_cmbOpeningDirection;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRemoteControllerCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteControllerCfg)
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREMOTECONTROLLERCFG_H__8E3003AF_EBC1_4493_89B4_E304930D5AEC__INCLUDED_)
