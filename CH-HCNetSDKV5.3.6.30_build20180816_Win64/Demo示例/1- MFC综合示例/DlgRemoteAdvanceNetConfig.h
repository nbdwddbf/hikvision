#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDlgRemoteAdvanceNetConfig dialog

class CDlgRemoteAdvanceNetConfig : public CDialog
{
	DECLARE_DYNAMIC(CDlgRemoteAdvanceNetConfig)

public:
	CDlgRemoteAdvanceNetConfig(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgRemoteAdvanceNetConfig();

	static DWORD WINAPI GetNtpServerTestInfoThread(LPVOID lpArg);
	static DWORD WINAPI GetEmailTestWithParamInfoThread(LPVOID lpArg);
// Dialog Data
	
public:
	//{{AFX_DATA(CDlgRemoteAdvanceNetConfig)
	enum { IDD = IDD_DLG_REMOTE_ADVANCE_NET_CFG };
	CComboBox	m_cmbDDNSStatus;
	CComboBox	m_comboEncryptType;
	CComboBox	m_comboDDNSType;
	CString m_csSenderName;
	CString m_csSenderAddr;
	CString m_csAccountPwd;
	CString m_csAccountPwdConfirm;
	CString m_csAccount;
	BOOL m_bChkAuthen;
	BOOL m_bChkAttach;
	CComboBox m_comboSendInterval;
	CComboBox m_comboServerType;
	BOOL m_bChkNtp;
	CString m_csNtpAddr;
	short m_iNtpInterval;
	short m_iNTPInterHour;
	short m_iNTPInterMin;
	BOOL m_bChkDdns;
	CString m_csDDNSAddr;//domain name
	CString m_csDDNSUserName;
	CString m_csDDNSPwd;
	CString m_csDDNSPwdConfirm;
	CListCtrl m_listEmailReceiver;
	CString m_csPPPoEUserName;
	CString m_csPPPoEPwd;
	CString m_csPPPoEVeriPwd;
	CString m_csPPPoEIP;	
	CString m_csSmtpSvrAddr;
	CString m_csPop3SvrAddr;
	UINT	m_uDDNSPort;
	CString	m_csDevDomain;
	UINT	m_uNtpPort;
	int	m_wSmtpPort;
	BOOL	m_bEnableSSL;
	BOOL	m_bEnableTSL;
	short	m_wCountrtID;
	BOOL	m_bChkStartTLS;
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CDlgRemoteAdvanceNetConfig)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteAdvanceNetConfig)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedChkEnablePppoe();
	afx_msg void OnBnClickedBtnPppoeOk();
	afx_msg void OnBnClickedBtnNtpOk();
	afx_msg void OnBnClickedBtnDdnsOk();
	afx_msg void OnBnClickedBtnEmaileOk();	
	afx_msg void OnBnClickedBtnAddReceiver();
	afx_msg void OnBnClickedBtnDelReceiver();
	afx_msg void OnBnClickedChkUseNtp();
	afx_msg void OnBnClickedChkDdns();
	afx_msg void OnBnClickedBtnHighNetConfigOk();
	afx_msg void OnBtnExit();
	afx_msg void OnSelchangeComboDdnsType();
	afx_msg void OnBtnTest();
	afx_msg void OnBtnSnmpCfg();
	afx_msg void OnBtnNtpServerTest();
	afx_msg void OnBtnEmailServerTestWithParam();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
public:	
	CString m_csDnsIP;
	int m_iDeviceIndex;
	BOOL	m_bEmailGet;
	BOOL	m_bNTPGet;
	BOOL m_bChkEnablePPPoE;
	void EnablePPPOEItem(BOOL bEnable);
	void EnableNTPItem(BOOL bEnable);
	void SwitchDDNSCtrlStat(int iHost);
    void SetEmailTestState(LPCTSTR lpszString);
	void AddStatusList();
	LONG	m_lServerID;	
	LPNET_DVR_PPPOECFG m_pPPPoECfg;
	BOOL	m_bPPPoEGet;
	NET_DVR_DDNSPARA_V30 m_struDDNSPara;
	NET_DVR_DDNSPARA_EX m_struDDNSParaEx;
	BOOL	m_bDDNSGet;
	NET_DVR_NTPPARA     m_struNTPPara;	
	NET_DVR_EMAILCFG_V30	m_struEmailCfg;
    HANDLE  m_hEmailTestThread;
    long m_lEmailTestHandle;

	LONG	m_lNtpTestHandle;
	LONG	m_lEmailTestWithParaHandle;
	HANDLE	m_hGetInfoThread;
	NET_DVR_SERVER_TEST_PARA m_struServerTestPara;
};
