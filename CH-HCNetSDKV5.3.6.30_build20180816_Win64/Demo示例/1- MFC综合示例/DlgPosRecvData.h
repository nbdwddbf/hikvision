#if !defined(AFX_DLGPOSRECVDATA_H__A58D0DA9_DBD7_4570_9723_62462BF70786__INCLUDED_)
#define AFX_DLGPOSRECVDATA_H__A58D0DA9_DBD7_4570_9723_62462BF70786__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPosRecvData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPosRecvData dialog

#define  MSG_PULL_CHANGE_RECEIVEDATA_SHOW WM_USER + 1005 
class CDlgPosRecvData : public CDialog
{
// Construction
public:
	CDlgPosRecvData(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPosRecvData)
	enum { IDD = IDD_DLG_POS_RECV_DATA };
	CComboBox	m_comboConnectMode;
	CComboBox	m_comboChanNum;
	CString	m_csStatusInfo;
	short	m_wPort;
	CString	m_csReceivedData;
	CString	m_csPosName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPosRecvData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPosRecvData)
	afx_msg void OnBtnUpload();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnStartListen();
	afx_msg void OnBtnSaveData();
	afx_msg void OnSelchangeCombochannelnum();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	LRESULT OnChangeDataShow(WPARAM wParam, LPARAM lParam);
public:
	
	void StartNetNakedDataListen();
	void StopNetNakedDataListen();
	void AddChanInfo();
    void GetChanAndRuleInfo(DWORD dwChanNum);
public:
	NET_DVR_POS_INFO m_struPosInfo;
	int m_iUserID;
	int m_iDevIndex;
	LONG m_lUploadHandle;
	HANDLE	m_hUpLoadThread;
	BOOL m_bUpLoading;

	NET_DVR_NAKED_DATA_PARAM m_struNakedDataParam;
	NET_DVR_CHAN_FILTER_CFG m_struChanFilterCfg;
	NET_DVR_POS_FILTER_CFG m_struPosFilterCfg;
	NET_DVR_CONNECT_POS_CFG m_struConnPosCfg; 
	NET_DVR_IPPARACFG_V40 m_struIPParaCfgV40; 
	int m_iStartListenHandle;
	BOOL m_bStartListen;
	char m_szPosIp[128];
	WORD m_wSocketPort;
	DWORD  m_dwChanNum;
	DWORD  m_dwTheFilterNum;
	DWORD  m_dwTheGroupNum;
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPOSRECVDATA_H__A58D0DA9_DBD7_4570_9723_62462BF70786__INCLUDED_)
