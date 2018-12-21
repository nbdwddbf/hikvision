#if !defined(AFX_DLGWIFIDHCPCFG_H__1A0BCC08_B28F_4F35_827A_F79301C3D630__INCLUDED_)
#define AFX_DLGWIFIDHCPCFG_H__1A0BCC08_B28F_4F35_827A_F79301C3D630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWifiDHCPCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgWifiDHCPCfg dialog

class CDlgWifiDHCPCfg : public CDialog
{
// Construction
public:
	CDlgWifiDHCPCfg(CWnd* pParent = NULL);   // standard constructor

	LONG    m_lUserID;
    LONG    m_lChannel;
	DWORD   m_dwDevIndex;

// Dialog Data
	//{{AFX_DATA(CDlgWifiDHCPCfg)
	enum { IDD = IDD_DLG_WIFI_DHCP_ADDR_CFG };
	CString	m_strEndIPAddr;
	CString	m_strStartIPAddr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWifiDHCPCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWifiDHCPCfg)
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWIFIDHCPCFG_H__1A0BCC08_B28F_4F35_827A_F79301C3D630__INCLUDED_)
