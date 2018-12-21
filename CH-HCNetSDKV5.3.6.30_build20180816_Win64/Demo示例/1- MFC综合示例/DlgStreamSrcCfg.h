#if !defined(AFX_DLGSTREAMSRCCFG_H__C592D9A9_CC0E_49B2_9E60_ED274833F997__INCLUDED_)
#define AFX_DLGSTREAMSRCCFG_H__C592D9A9_CC0E_49B2_9E60_ED274833F997__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgStreamSrcCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgStreamSrcCfg dialog

class CDlgStreamSrcCfg : public CDialog
{
// Construction
public:
	CDlgStreamSrcCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgStreamSrcCfg)
	enum { IDD = IDD_DLG_STREAM_SRC_CFG };
	CComboBox	m_cmbVideoType;
	CListCtrl	m_lstStreamSrc;
	CComboBox	m_cmbSrcType;
	CComboBox	m_cmbStreamType;
	CComboBox	m_cmbProtocolType;
	BOOL	m_bEnableChannel;
	BOOL	m_bEnableURL;
	CString	m_strChannel;
	CString	m_strDomainName;
	CString	m_strPassword;
	CString	m_strPort;
	CString	m_strRelatedChannel;
	CString	m_strStreamID;
	CString	m_strStreamURL;
	CString	m_strUserName;
	CString	m_strStatus;
	BOOL	m_bEnableRTSPPro;
	BOOL	m_bLocalBackUp;
	CString	m_strDeviceName;
	CString	m_strRtspPasswd;
	CString	m_strRtspUrl;
	CString	m_strRtspUserName;
	CString	m_strRtspStreamID;
	BOOL	m_bChanStatus;
	BOOL	m_bEnableUrlMore;
	BOOL	m_bBackupUrlMore;
	short	m_wPortUrlMore;
	CString	m_sPasswdUrlMore;
	CString	m_strStreamUrlMore;
	CString	m_strNameUrlMore;
	CString	m_strChanNameUrlMore;
	BOOL	m_bRtspBackUp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgStreamSrcCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgStreamSrcCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAddStreamID();
	afx_msg void OnButtonDelStreamID();
	afx_msg void OnClickListStreamSrc(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonGetStreamSrc();
	afx_msg void OnButtonSetStreamSrc();
	afx_msg void OnSelchangeComboSrcType();
	afx_msg void OnBtnMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    void ClearDirectChanInfo();
    void ClearUrlInfo();
    void ClearRtspInfo(); 
    void ShowUnionInfo(int iCurIndex);
    void ClearUrlMoreInfo();
    BOOL ReadStreamCfgV40(int dwItem);
    BOOL AssignmentStreamCfgV40(int iSelectItem);
    void AddStreamInfoToList(int iItem);
    void AddProtocalList();
    BOOL CheckInitParam();
    int FindDataIndexInCombo(byte byProtocalType);
    int FindDataIndexInComboByStr(CString strFind);
protected:
    NET_DVR_STREAM_SRC_INFO_V40 m_struStreamSrcInfo;
    NET_DVR_IPC_PROTO_LIST   m_struProList;
    NET_DVR_STREAM_INFO m_struStreamID;
    int  m_iCurSelectItem;
public:
    CString m_strMonitorName;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSTREAMSRCCFG_H__C592D9A9_CC0E_49B2_9E60_ED274833F997__INCLUDED_)
