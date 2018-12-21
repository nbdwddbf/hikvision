#if !defined(AFX_MATDYNAMICTEST_H__7153FB2E_1558_4224_AA30_429CFA570960__INCLUDED_)
#define AFX_MATDYNAMICTEST_H__7153FB2E_1558_4224_AA30_429CFA570960__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MatDynamicTest.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMatDynamicTest dialog

class CMatDynamicTest : public CDialog
{
// Construction
public:
	CMatDynamicTest(CWnd* pParent = NULL);   // standard constructor

	LONG m_lServerID;
	LONG m_lDeviceID;
	int m_iChannelnumber;
	LONG m_lStartChan;
	BOOL m_BUseWinNo; 
    NET_DVR_IPC_PROTO_LIST m_struProtoList;

// Dialog Data
	//{{AFX_DATA(CMatDynamicTest)
	enum { IDD = IDD_DLG_MATDYNAMIC };
	CComboBox	m_comboChannelType;
	CComboBox	m_comboDomainTransPro;
	CComboBox	m_comboDomainTransMode;
	CComboBox	m_comboDomainStreamMediaPro;
	CComboBox	m_comboDomainServerType;
	CComboBox	m_comboDomainFacType;
	CComboBox	m_comboDomainChannelType;
	CComboBox	m_comboStreamMode;
	CComboBox	m_FacTypeCtrl;
	CComboBox	m_ComboStreamMediaPro;
	CComboBox	m_DecChanCombo;
	CComboBox	m_TransModeCombo;
	CComboBox	m_TransProtocolCombo;
	CString	m_RemoteIP;
	int		m_RemoteSurveillace;
	CString	m_RemoteUser;
	CString	m_RemotePass;
	CString	m_strStreamMediaIp;
	DWORD	m_dwStreamMediaPort;
	BOOL	m_bUseStreamMedia;
	DWORD	m_RemotePort;
	CString	m_csUrl;
	CString	m_strDomainRemoteName;
	CString	m_strDomainRemotePass;
	CString	m_strDomainServerIp;
	UINT	m_uiDomainServerPort;
	CString	m_strDomainStreamId;
	CString	m_strDomainStreamMediaIp;
	UINT	m_uiDomainStreamMediaPort;
	CString	m_strDomainName;
	UINT	m_uiDomainChannelNum;
	BOOL	m_bDomainUseStreamMedia;
	CString	m_strStreamId;
	short	m_wRemotePort;
	CString	m_csDecodeChanTitle;
	DWORD	m_dwSubWinNo;
	DWORD	m_dwWallNo;
	DWORD	m_dwWinNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatDynamicTest)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMatDynamicTest)
	afx_msg void OnStartdynamic();
	afx_msg void OnStopdynamic();
	virtual BOOL OnInitDialog();
	afx_msg void OnUsestreammedia();
	afx_msg void OnSelchangeComboStreamMode();
	afx_msg void OnChkDomainUsestreammedia();
	afx_msg void OnSelchangeComboChannelType2();
	afx_msg void OnSelchangeComboDomainChannelType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void EnableIpOrDomainGroup(BOOL IsEnable);
	void EnableURLGroup(BOOL IsEnable);
	void EnableDynamicDDNSGroup(BOOL IsEnable);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATDYNAMICTEST_H__7153FB2E_1558_4224_AA30_429CFA570960__INCLUDED_)
