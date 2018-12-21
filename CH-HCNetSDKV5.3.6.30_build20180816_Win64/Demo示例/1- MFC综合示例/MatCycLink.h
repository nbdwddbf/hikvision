#if !defined(AFX_MATCYCLINK_H__C81B5763_F98C_42C4_A5FE_223E644FFB9D__INCLUDED_)
#define AFX_MATCYCLINK_H__C81B5763_F98C_42C4_A5FE_223E644FFB9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MatCycLink.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMatCycLink dialog

class CMatCycLink : public CDialog
{
// Construction
public:
	CMatCycLink(CWnd* pParent = NULL);   // standard constructor

	LONG m_lServerID;
	LONG m_lDeviceID;
	int m_iChannelnumber;
	LONG m_lStartChan;
	BOOL m_BUseWinNo; 
    NET_DVR_IPC_PROTO_LIST m_struProtoList;

// Dialog Data
	//{{AFX_DATA(CMatCycLink)
	enum { IDD = IDD_DLG_MATCYCLINK };
	CComboBox	m_comboChannelType;
	CComboBox	m_comboSwitch;
	CComboBox	m_comboDomainTransMode;
	CComboBox	m_comboDomainStreamMediaPro;
	CComboBox	m_comboDomainTransPro;
	CComboBox	m_comboDomainServerType;
	CComboBox	m_comboDomainFacType;
	CComboBox	m_comboDomainChanneType;
	CComboBox	m_comboStreamMode;
	CComboBox	m_FacTypeCtrl;
	CComboBox	m_ComboStreamMediaPro;
	CComboBox	m_TransModesCombo;
	CComboBox	m_TransProtocolCombo;
	CComboBox	m_DecChanCombo2;
	CComboBox	m_DecChanCombo;
	CComboBox	m_ConnectChanCombo;
	CString	m_DVRIP;
	CString	m_DVRPasswd;
	short	m_DVRPort;
	CString	m_DVRUser;
	int		m_PoolTime;
	BOOL	m_bCheckConnectChan;
	BOOL	m_bUseStreamMedia;
	CString	m_strStreamMediaIp;
	DWORD	m_dwStreamMediaPort;
	BOOL	m_bUseUrl;
	CString	m_csUrl;
	BOOL	m_bDomainUseStreamMedia;
	UINT	m_dwDomainChannelNum;
	CString	m_strDomainIp;
	CString	m_strDomainRemoteName;
	CString	m_strDomainRemotePass;
	CString	m_strDomainServerIp;
	short	m_wDomainServerPort;
	CString	m_strDomainStreamId;
	CString	m_strDomainStreamIdIP;
	short	m_wDomainStreamMediaPort;
	CString	m_strStreamID;
	BYTE	m_byChannelNum;
	short	m_wDomainDevPort;
	CString	m_csDecodeChanTitle;
	DWORD	m_dwSubWinNo;
	DWORD	m_dwWallNo;
	DWORD	m_dwWinNo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatCycLink)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	NET_DVR_MATRIX_LOOP_DECINFO_V41 m_MatLoopDec;
	int m_iChanSel;
	BOOL m_CycLink[64];     //轮巡开关

	// Generated message map functions
	//{{AFX_MSG(CMatCycLink)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombodecchan();
	afx_msg void OnSelchangeComboconchan();
	afx_msg void OnSingleget();
	afx_msg void OnWholeget();
	afx_msg void OnSingleset();
	afx_msg void OnUsestreammedia();
	afx_msg void OnSelchangeComboStreamMode();
	afx_msg void OnChkDomainUsestreammedia();
	afx_msg void OnUrlSavepara();
	afx_msg void OnDomainSavepara();
	afx_msg void OnIpSavepara();
	afx_msg void OnBtnSetDecCycleParm();
	afx_msg void OnSelchangeComboIpChannelType();
	afx_msg void OnSelchangeComboDomainChannelType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void EnableIpOrDomainGroup(BOOL IsEnable);
	void EnableURLGroup(BOOL IsEnable);
	void EnableDynamicDDNSGroup(BOOL IsEnable);
	int  WinInIndex(DWORD dwWinNo);
	int  m_iWin[MAX_CYCLE_CHAN_V30]; //窗口号的对应的下标为
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATCYCLINK_H__C81B5763_F98C_42C4_A5FE_223E644FFB9D__INCLUDED_)
