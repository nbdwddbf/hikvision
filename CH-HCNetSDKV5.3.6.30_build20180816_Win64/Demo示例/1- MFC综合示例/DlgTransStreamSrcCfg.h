#if !defined(AFX_DLGTRANSSTREAMSRCCFG_H__26B81FF2_A49E_4CB7_8126_6F23389AAB35__INCLUDED_)
#define AFX_DLGTRANSSTREAMSRCCFG_H__26B81FF2_A49E_4CB7_8126_6F23389AAB35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTransStreamSrcCfg.h : header file
//

#define MSG_GET_STREAM_ID	WM_USER+100
#define RECV_BUF_LEN        2 * 1024 * 1024

/////////////////////////////////////////////////////////////////////////////
// CDlgTransStreamSrcCfg dialog

class CDlgTransStreamSrcCfg : public CDialog
{
// Construction
public:
	CDlgTransStreamSrcCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTransStreamSrcCfg)
	enum { IDD = IDD_DLG_TRANS_STREAM_SRC_CFG };
	CComboBox	m_comboMediaProtocol;
	CComboBox	m_comboTransProtocol;
	CListCtrl	m_lstStreamSrc;
	CComboBox	m_cmbSrcType;
	CComboBox	m_cmbStreamtype;
	CComboBox	m_cmbProtocolType;
	BOOL	m_bEnableChannel;
	BOOL	m_bEnableURL;
	CString	m_strChannel;
	CString	m_strDomainName;
	CString	m_strIPAddress;
	CString	m_strPassword;
	CString	m_strPort;
	CString	m_strRelatedChannel;
	CString	m_strStreamID;
	CString	m_strStreamURL;
	CString	m_strUserName;
	CString	m_strStatus;
	BOOL	m_bOnline;
	BOOL	m_bZeroChanel;
	BOOL	m_bChannel;
	CString	m_csMediaServerIp;
	CString	m_csMediaServerPort;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTransStreamSrcCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTransStreamSrcCfg)
		// NOTE: the ClassWizard will add member functions here
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAddStreamID();
	afx_msg void OnButtonDelStreamID();
	afx_msg void OnClickListStreamSrc(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonGetStreamSrc();
	afx_msg void OnButtonSetStreamSrc();
	afx_msg void OnSelchangeComboSrcType();
	afx_msg void OnButtonGetProtoList();
	afx_msg void OnBtnGetAll();
	afx_msg void OnBtnDeleteAll();
	afx_msg void OnBtnExit();
	afx_msg void OnChkChannel();
	afx_msg void OnBtnMod();
	afx_msg void OnBtnCopyToAll();
	afx_msg void OnBtnApplyTransChan();
	afx_msg void OnBtnVideoIntercomStream();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	NET_DVR_IPC_PROTO_LIST m_struProtoList;
	LONG	m_hLongCfgHandle;
	void GetStreamInfoFromList(LPNET_DVR_STREAM_INFO lpStreamInfo, DWORD *pNum);
	int m_iCurSelItem;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRANSSTREAMSRCCFG_H__26B81FF2_A49E_4CB7_8126_6F23389AAB35__INCLUDED_)
