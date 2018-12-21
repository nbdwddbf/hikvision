#pragma once
#include "afxwin.h"


// CDlgChannelInfo dialog

class CDlgChannelInfo : public CDialog
{
	DECLARE_DYNAMIC(CDlgChannelInfo)

public:
	CDlgChannelInfo(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgChannelInfo();

// Dialog Data
	

public:
	//{{AFX_DATA(CDlgChannelInfo)
	enum { IDD = IDD_DLG_CHANNEL_INFO };
	CComboBox	m_cmPreviewProtocolType;
	CComboBox	m_comboPassbackRecord;
	CString m_csChanName;
	int m_iChanNo;
	CComboBox	m_cmPreviewMode;
	CString m_csLocalNodeName;
	CString m_csDeviceIP;
	CComboBox m_comboProtocol;
	CComboBox m_comboTransportType;
	BOOL m_bChanged;
	PCHANNEL_INFO m_pChanInfo;
	//}}AFX_DATA


	//{{AFX_VIRTUAL(CDlgChannelInfo)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgChannelInfo)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnUpdateMenuChannelInfo(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    void AddStreamType();
    CComboBox m_comVideoCodingType;
};
