#if !defined(AFX_DLGMONITORINFO_H__7B6E983D_83A0_4854_A8E4_8AADB36F5356__INCLUDED_)
#define AFX_DLGMONITORINFO_H__7B6E983D_83A0_4854_A8E4_8AADB36F5356__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMonitorInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMonitorInfo dialog

class CDlgMonitorInfo : public CDialog
{
// Construction
public:
	CDlgMonitorInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMonitorInfo)
	enum { IDD = IDD_DLG_MONITOR_INFO };
	CComboBox	m_cmbDevProtorl;
	CComboBox	m_csCmbllProtorl;
	CComboBox	m_cmbDevType;
	CListCtrl	m_lstStreamSrc;
	CComboBox	m_cmbStreamtype;
	CComboBox	m_cmbSrcType;
	CComboBox	m_cmbProtocolType;
	BOOL	m_bEnableChannel;
	BOOL	m_bEnableURL;
	CString	m_strChannel;
	CString	m_strDomainName;
	CString	m_strIPAddress;
	CString	m_strPassword;
	CString	m_strPort;
	CString	m_strRelatedChannel;
	CString	m_strStatus;
	CString	m_strStreamID;
	CString	m_strStreamURL;
	CString	m_strUserName;
	BOOL	m_bEnableCheck;
	BYTE	m_byBlurPoint;
	BYTE	m_byChromaPoint;
	BYTE	m_byFreezePoint;
	BYTE	m_byLumaPoint;
	BYTE	m_byPtzPoint;
	BYTE	m_bySignalPoint;
	BYTE	m_bySnowPoint;
	BYTE	m_byStreakPoint;
	int		m_iCount;
	CString	m_csStreamIP;
	int		m_iStreamPort;
	CString	m_csDevIP;
	int		m_iDevPort;
	BOOL	m_bMonitorDel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMonitorInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMonitorInfo)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAddStreamID();
	afx_msg void OnButtonDelStreamID();
	afx_msg void OnButtonGetStreamSrc();
	afx_msg void OnButtonSetStreamSrc();
	afx_msg void OnClickListStreamSrc(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboSrcType();
	afx_msg void OnBtnMonitorInfoAdd();
	afx_msg void OnBtnMonitorInfoDel();
	afx_msg void OnBtnMonitorInfoSet();
	afx_msg void OnBtnMonitorInfoGet();
	afx_msg void OnBtnGetinfo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	BOOL	m_bGetNext;
	LONG    m_lHandle;
	LONG    m_hLongCfgHandle;
	HANDLE	m_hGetInfoThread;
	LONG    m_lServerID;
    LONG    m_lChannel;
    int     m_iDevIndex;
	int     m_iListNum;
	NET_DVR_STREAM_INFO struStreamInfo;
	LPNET_DVR_STREAM_INFO m_pStruStreamInfo;
	static DWORD WINAPI GetStreamInfoThread (LPVOID lpArg);
	void	AddStreamInfoToDlg(LPNET_DVR_STREAM_INFO lpInter);
	void    ShowVQDList(int iNum,LONG lCount, DWORD *pStatus, LPNET_DVR_STREAM_INFO pstruStreamID,LPNET_DVR_STREAM_SRC_INFO pInputStreamSrcInfo, LPNET_DVR_MONITOR_VQDCFG pInputMonitorInfo);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMONITORINFO_H__7B6E983D_83A0_4854_A8E4_8AADB36F5356__INCLUDED_)
