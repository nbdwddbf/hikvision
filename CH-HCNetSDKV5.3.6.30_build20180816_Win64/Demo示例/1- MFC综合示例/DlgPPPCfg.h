#pragma once


// CDlgPPPCfg dialog

class CDlgPPPCfg : public CDialog
{
	DECLARE_DYNAMIC(CDlgPPPCfg)

public:
	CDlgPPPCfg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPPPCfg();

// Dialog Data



public:
	//{{AFX_DATA(CDlgPPPCfg)
	enum { IDD = IDD_DLG_PPP_CFG };
	CComboBox m_comboPPPMode;
	CComboBox m_comboRedialMode;
	CString m_csUserName;
	CString m_csPwd;
	CString m_csRemoteIP;
	CString m_csLocalIP;
	CString m_csVerifyPwd;
	CString m_csIPMask;
	CString m_csTelNum;
	BOOL m_bChkDataEncrypt;
	BOOL m_bChkRedial;
	//}}AFX_DATA
	




	//{{AFX_VIRTUAL(CDlgPPPCfg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgPPPCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnSetup();
	afx_msg void OnBnClickedBtnExit();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	NET_DVR_PPPCFG_V30 m_struPPPConfig;
	
	
};
