#if !defined(AFX_DLG67DVSCFG_H__EB4590B6_9396_4369_ABEF_29E1BEC5B154__INCLUDED_)
#define AFX_DLG67DVSCFG_H__EB4590B6_9396_4369_ABEF_29E1BEC5B154__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg67DVSCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg67DVSCfg dialog

class CDlgNetServiceCfg : public CDialog
{
// Construction
public:
	CDlgNetServiceCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg67DVSCfg)
	enum { IDD = IDD_DLG_NETSERVICE_CFG };
	CComboBox	m_cmbFlag;
	BOOL	m_bBonjour;
	BOOL	m_bHttps;
	BOOL	m_bSocks;
	CString	m_strFriendName;
	CString	m_strHostName;
	CString	m_strLocalAddress;
	CString	m_strPassword;
	CString	m_strProxyIP;
	UINT	m_wHttpsPort;
	UINT	m_wProxyPort;
	CString	m_strUserName;
	BYTE	m_byVersion;
	UINT	m_dwManageDscp;
	UINT	m_dwAlarmDscp;
	UINT	m_dwAudioDscp;
	UINT	m_dwVideoDscp;
	BOOL	m_bQosEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg67DVSCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg67DVSCfg)
	afx_msg void OnButtonBonjourGet();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonBonjourSet();
	afx_msg void OnButtonSocksGet();
	afx_msg void OnButtonSocksSet();
	afx_msg void OnButtonQosGet();
	afx_msg void OnButtonQosSet();
	afx_msg void OnButtonHttpsGet();
	afx_msg void OnButtonHttpsSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG    m_lUserID;
    int     m_iDevIndex;

	NET_DVR_BONJOUR_CFG m_struBonjourInfo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG67DVSCFG_H__EB4590B6_9396_4369_ABEF_29E1BEC5B154__INCLUDED_)
