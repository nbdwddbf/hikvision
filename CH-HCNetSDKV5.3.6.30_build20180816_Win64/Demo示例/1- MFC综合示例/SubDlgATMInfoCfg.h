#pragma once
#include "afxwin.h"


// CSubDlgATMInfoCfg dialog

class CSubDlgATMInfoCfg : public CDialog
{
	DECLARE_DYNAMIC(CSubDlgATMInfoCfg)

public:
	CSubDlgATMInfoCfg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubDlgATMInfoCfg();

// Dialog Data
	


public:



	//{{AFX_DATA(CSubDlgATMInfoCfg)
	enum { IDD = IDD_SUB_DLG_ATMINFO_CFG };
	CComboBox m_comboInputType;
	
	CString m_csATMIP;
	CComboBox m_comboATMType2;
	CComboBox m_comboATMType;
	int m_iATMPort;
	
	
	DWORD m_dwMsgStartPos;
	CComboBox m_comboAcceptFrameType;
	CString m_csAcceptBusTypeCode;
	DWORD m_dwMsgLen;
	CString m_csMsgInfo;
	DWORD m_dwCardLenInfoStart;

	// size of card info
	DWORD m_dwCardLenInfoLen;
	DWORD m_dwCardNumInfoStart;
	DWORD m_dwCardNumInfoLen;
	DWORD m_dwBusinessStart;
	DWORD m_dwBusinessLen;
	CComboBox m_comboListenFrameType;
	CString m_csListenBusTypeCode;
	short m_wCardAtmPort;
	// protocol type
	CComboBox m_comboProtoType;
	//}}AFX_DATA

	
	//{{AFX_VIRTUAL(CSubDlgATMInfoCfg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CSubDlgATMInfoCfg)
	virtual BOOL OnInitDialog();	
	afx_msg void OnBnClickedBtnAtmOk();
	afx_msg void OnCbnSelchangeComboInputType();
	
	afx_msg void OnCbnSelchangeComboListenFrameType();
	afx_msg void OnCbnSelchangeComboAcceptFrameType();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	
	int m_iDeviceIndex;
	LONG m_lLoginID;
	NET_DVR_FRAMEFORMAT m_struATMInfo;
	BOOL m_bSetPara;
	int m_iInputMode;
	int	 m_iFrameType;
	WORD m_nATMPort;//new port number
	BOOL m_bNewPort;//use new port number
	void EnableControl(int iInputMode, BOOL bNewPort);
	BOOL CheckInitParam();
	void CurCfgUpdate();
	BOOL CfgSetup();
	
	BOOL TimeTest();
};
