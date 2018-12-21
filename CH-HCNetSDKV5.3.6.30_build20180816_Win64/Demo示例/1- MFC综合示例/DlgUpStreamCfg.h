#if !defined(AFX_DLGUPSTREAMCFG_H__39E0C27B_3F73_42A1_BFEE_EBBA604883EE__INCLUDED_)
#define AFX_DLGUPSTREAMCFG_H__39E0C27B_3F73_42A1_BFEE_EBBA604883EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgUpStreamCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgUpStreamCfg dialog

class CDlgUpStreamCfg : public CDialog
{
// Construction
public:
	CDlgUpStreamCfg(CWnd* pParent = NULL);   // standard constructor
	~CDlgUpStreamCfg();
// Dialog Data
	//{{AFX_DATA(CDlgUpStreamCfg)
	enum { IDD = IDD_DLG_PU_STREAM_CFG };
    CComboBox	m_comboChannelType;
    CComboBox	m_cmResolution;
    CComboBox	m_combDeviceType;
    CComboBox	m_comboDomainTransPro;
    CComboBox	m_comboDomainTransMode;
    CComboBox	m_comboDomainStreamMediaPro;
    CComboBox	m_comboDomainServerType;
    CComboBox	m_comboDomainFacType;
    CComboBox	m_comboDomainChannelType;
    CComboBox	m_comboStreamMode;
    CComboBox	m_FacTypeCtrl;
    CComboBox	m_ComboStreamMediaPro;
 //   CComboBox	m_DecChanCombo;
    CComboBox	m_TransModeCombo;
    CComboBox	m_TransProtocolCombo;
    CString	    m_RemoteIP;
    int		    m_RemoteSurveillace;
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
    BOOL	m_bDispChan;
    BOOL	m_bSubDispChan;
    DWORD	m_dwInputIndex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgUpStreamCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgUpStreamCfg)
	virtual BOOL OnInitDialog();
    afx_msg void OnSelchangeComboStreamMode();
    afx_msg void OnSelchangeComboChannelType2();
	afx_msg void OnSelchangeComboDomainChannelType();
	afx_msg void OnOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    void EnableIpOrDomainGroup(BOOL IsEnable);
    void EnableURLGroup(BOOL IsEnable);
	void EnableDynamicDDNSGroup(BOOL IsEnable);
    
//    NET_DVR_IPC_PROTO_LIST m_struProtoList;
	NET_DVR_IPC_PROTO_LIST_V41 m_struProtocolListV41;
	LPNET_DVR_PROTO_TYPE m_lpProtoType;

    BOOL UpdateStreamCfg();   //更新界面
	BOOL UpdateStreamCfg(BOOL bUpdateStructure);   //更新结构体 
public:
    LONG m_lServerID;
	LONG m_lDeviceID;
    int  m_iChannelnumber;
	LONG m_lStartChan;
    NET_DVR_PU_STREAM_CFG_V41 m_struStreamCfgV41; 
    NET_DVR_PU_STREAM_CFG_V41& GetStreamCfg();
    void SetStreamCfg(const NET_DVR_PU_STREAM_CFG_V41& Cfg); 

	afx_msg void oncbnChangeStreamMode();
	afx_msg void OnBnClickedUsestreammedia();
	afx_msg void OnBnClickedChkDomainUsestreammedia();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGUPSTREAMCFG_H__39E0C27B_3F73_42A1_BFEE_EBBA604883EE__INCLUDED_)
