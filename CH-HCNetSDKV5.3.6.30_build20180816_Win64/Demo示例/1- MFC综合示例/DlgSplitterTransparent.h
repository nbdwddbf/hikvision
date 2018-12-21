#if !defined(AFX_DLGSPLITTERTRANSPARENT_H__BF09EDDB_2F8B_4B82_828B_3502F25BC26A__INCLUDED_)
#define AFX_DLGSPLITTERTRANSPARENT_H__BF09EDDB_2F8B_4B82_828B_3502F25BC26A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSplitterTransparent.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSplitterTransparent dialog

class CDlgSplitterTransparent : public CDialog
{
// Construction
public:
	CDlgSplitterTransparent(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSplitterTransparent)
	enum { IDD = IDD_DLG_SPLITTER_TRANSPARENT };
	CComboBox	m_comboSerialType;
	CComboBox	m_comboTransparentMode;
	CComboBox	m_comboTransparentNum;
	CComboBox	m_comboRs485Num;
	BOOL	m_bEnable;
	CString	m_csRemoteIp;
	DWORD	m_wPort;
	DWORD	m_wLocalPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSplitterTransparent)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSplitterTransparent)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSavePara();
	afx_msg void OnSelchangeComboTransparentMode();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnCopyAll();
	afx_msg void OnSelchangeComboTransparentNum();
	afx_msg void OnSelchangeComboRs485Num();
	afx_msg void OnBtnStartTransparent();
	afx_msg void OnSelchangeComboSerialType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lServerID;
	int m_iDeviceIndex;
	NET_DVR_TRANSPARENT_CHAN_CFG m_struTransChanCfgClinet[9]; //客户端模式参数
	NET_DVR_TRANSPARENT_CHAN_CFG m_struTransChanCfgServer[9]; //服务器模式参数
	//BOOL m_bParamSaved[4];

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSPLITTERTRANSPARENT_H__BF09EDDB_2F8B_4B82_828B_3502F25BC26A__INCLUDED_)
