#if !defined(AFX_DLGPOSSERIALPORTRECVDATA_H__6DFBFC93_7811_4093_B1DD_2F62D59CBB31__INCLUDED_)
#define AFX_DLGPOSSERIALPORTRECVDATA_H__6DFBFC93_7811_4093_B1DD_2F62D59CBB31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPosSerialPortRecvData.h : header file
//

#define MSG_PULL_CHANGE_COM_RECEIVEDATA_SHOW WM_USER + 1006 
/////////////////////////////////////////////////////////////////////////////
// CDlgPosSerialPortRecvData dialog

class CDlgPosSerialPortRecvData : public CDialog
{
// Construction
public:
	CDlgPosSerialPortRecvData(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPosSerialPortRecvData)
	enum { IDD = IDD_DLG_POS_SERIAL_PORT_RECEIVEDATA };
	CComboBox	m_comboConnectMode;
	CComboBox	m_comboChanNum;
	CComboBox	m_comboSerialPortCom;
	CString	m_csRecvData;
	CString	m_csPosName;
	CString	m_csStatusInfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPosSerialPortRecvData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgPosSerialPortRecvData)
	afx_msg void OnBtnStart();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnOpencom();
	afx_msg void OnSelchangeCombochannelnum();
	afx_msg void OnBtnSaveData();
	afx_msg void OnBtnUpload();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	LRESULT OnChangeDataShow(WPARAM wParam, LPARAM lParam);
public:
	void InitSerialPortWnd();
	BOOL OpenComm();
	void AddChanInfo();
    void GetChanAndRuleInfo(DWORD dwChanNum);
	
public:
	 int m_iUserID ;
	 int m_iDevIndex;
	 BOOL m_bOpenComm;
	 BOOL m_bStartRecv;
	 BOOL m_bUpLoading;
	 int m_iComHandle;

	 LONG m_lUploadHandle;
	HANDLE	m_hUpLoadThread;


	 NET_DVR_NAKED_DATA_PARAM m_struNakedDataParam;
	 NET_DVR_CHAN_FILTER_CFG m_struChanFilterCfg;
	 NET_DVR_POS_FILTER_CFG m_struPosFilterCfg;
	 NET_DVR_CONNECT_POS_CFG m_struConnPosCfg; 
	 NET_DVR_IPPARACFG_V40 m_struIPParaCfgV40; 
	 NET_DVR_POS_INFO   m_struPosInfo;

	 DWORD  m_dwChanNum;
	 DWORD  m_dwTheFilterNum;
     DWORD  m_dwTheGroupNum;


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPOSSERIALPORTRECVDATA_H__6DFBFC93_7811_4093_B1DD_2F62D59CBB31__INCLUDED_)
