#pragma once


// CDlgRemoteMatDecDnsCfg dialog

class CDlgRemoteMatDecDnsCfg : public CDialog
{
	DECLARE_DYNAMIC(CDlgRemoteMatDecDnsCfg)

public:
	CDlgRemoteMatDecDnsCfg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgRemoteMatDecDnsCfg();

// Dialog Data



public:


	//{{AFX_DATA(CDlgRemoteMatDecDnsCfg)
	enum { IDD = IDD_DLG_MAT_DEC_DNS_CFG };
	CString m_FirstDns;
	CString m_SecondDns;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CDlgRemoteMatDecDnsCfg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteMatDecDnsCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnMatDecOk();	
	afx_msg void OnBnClickedBtnMatDecExit();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	
	int m_lLoginID;
	NET_DVR_NETCFG_OTHER m_NetCFGOther;
	
};
