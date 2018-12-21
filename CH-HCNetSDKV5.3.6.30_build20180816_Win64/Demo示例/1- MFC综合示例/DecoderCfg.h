#if !defined(AFX_DECODERCFG_H__91F75BEB_2ED7_43E6_98F2_3B9A2C3E6815__INCLUDED_)
#define AFX_DECODERCFG_H__91F75BEB_2ED7_43E6_98F2_3B9A2C3E6815__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DecoderCfg.h : header file
//
 
/////////////////////////////////////////////////////////////////////////////
// CDecoderCfg dialog

class CDecoderCfg : public CDialog
{
// Construction
public:
	void SaveData();
	BOOL CheckInit();
	CDecoderCfg(CWnd* pParent = NULL);   // standard constructor

	LONG m_lServerID;
	int  m_iDeviceIndex;
	NET_DVR_DECODERCFG m_struDecoderCfg;
	NET_DVR_RS232CFG m_struRs232Cfg;
	NET_DVR_RS485_WORK_MODE m_struWorkMode;

	NET_DVR_CODESPLITTERASSOCIATE m_struCodeSplitterAssociate;
	BOOL m_bSelOtherCombo;
// Dialog Data
	//{{AFX_DATA(CDecoderCfg)
	enum { IDD = IDD_DLG_SPLITTER_DECODERCFG };
	CComboBox	m_comboSerialType;
	CComboBox	m_comboWorkMode;
	CComboBox	m_SlotCtrl;
	CComboBox	m_DecoderChannelCtrl;
	CComboBox	m_485BaudCtrl;
	CComboBox	m_SlotNumCtrl;
	CComboBox	m_485StopBitCtrl;
	CComboBox	m_485FlowCtrl;
	CComboBox	m_485DataBitCtrl;
	CComboBox	m_485CheckBitCtrl;
	CComboBox	m_485ChannelCtrl;
	CComboBox	m_combo485DecodeType;
	int		m_iDecodeAddress;
	CString	m_strIp;
	int		m_iPort;
	CString	m_strPsw;
	CString	m_strUser;
	int		m_iCodeChannel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDecoderCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDecoderCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnSaveall();
	afx_msg void OnBtnSave2();
	afx_msg void OnSelchangeComboSlotnum();
	afx_msg void OnSelchangeCombo485Channel();
	afx_msg void OnSelchangeComboDecoderchannel();
	afx_msg void OnSelchangeComboSlot();
	afx_msg void OnBtnSaveassociate();
	afx_msg void OnBtnSet();
	afx_msg void OnSelchangeComboWorkMode();
	afx_msg void OnSelchangeComboSerialType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DECODERCFG_H__91F75BEB_2ED7_43E6_98F2_3B9A2C3E6815__INCLUDED_)
