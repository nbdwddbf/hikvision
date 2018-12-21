#if !defined(AFX_DLGETHERNETIPV6CFG_H__C35AF3B0_8F9F_4537_853A_C66408CD7D03__INCLUDED_)
#define AFX_DLGETHERNETIPV6CFG_H__C35AF3B0_8F9F_4537_853A_C66408CD7D03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEthernetIpv6Cfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgEthernetIpv6Cfg dialog

class CDlgEthernetIpv6Cfg : public CDialog
{
// Construction
public:
	CDlgEthernetIpv6Cfg(CWnd* pParent = NULL);   // standard constructor
	~CDlgEthernetIpv6Cfg();
// Dialog Data
	//{{AFX_DATA(CDlgEthernetIpv6Cfg)
	enum { IDD = IDD_DLG_ETHERNET_IPV6_CFG };
	CListCtrl	m_EthernetIpv6Cfglist;
	CString	m_csMacAddr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEthernetIpv6Cfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgEthernetIpv6Cfg)
	afx_msg void OnBtnGetEthernetIpv6();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG m_lUserID;
	int  m_iDeviceIndex;
	long m_lFindHandle;
	BOOL m_bGetNext;
	HANDLE	m_hGetInfoThread;
	int  m_iEthernetCount;
	
	NET_DVR_ETHERNET_IPV6_COND m_struEthernetIpv6Cond;
	LPNET_DVR_ETHERNET_IPV6_CFG m_lpStruEthernetIpv6Cfg;
	static DWORD WINAPI GetEthernetIPV6ListThread(LPVOID lpArg);
	void AddEthernetIPV6InfoToDlg(LPNET_DVR_ETHERNET_IPV6_CFG lpInter);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGETHERNETIPV6CFG_H__C35AF3B0_8F9F_4537_853A_C66408CD7D03__INCLUDED_)
