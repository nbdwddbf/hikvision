#include "afxwin.h"
#if !defined(AFX_DLGALARMHOSTNETCFG_H__B4CBF589_1EC3_4891_8F95_474757127B3E__INCLUDED_)
#define AFX_DLGALARMHOSTNETCFG_H__B4CBF589_1EC3_4891_8F95_474757127B3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmHostNetCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostNetCfg dialog

class CDlgAlarmHostNetCfg : public CDialog
{
// Construction
public:
	CDlgAlarmHostNetCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlarmHostNetCfg)
	enum { IDD = IDD_DLG_ALARMHOST_NETCFG };
	CComboBox	m_cmbAddrType;
	CIPAddressCtrl	m_ipCenter;
	CComboBox	m_cmProtocolType;
	CComboBox	m_cmCenter;
    CComboBox   m_cmbEnable;
	CString	m_csDeviceID;
	int		m_iPort;
	CString	m_csDomain;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmHostNetCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_iDeviceIndex;
	long m_lUserID;
	NET_DVR_ALARMHOST_NETCFG m_struNetCfg;
	NET_DVR_ALARMHOST_NETCFG_V50 m_struNetCfgV50;
	NET_DVR_ALARMHOST_ABILITY m_struAbility;
	char szLan[1024];
	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmHostNetCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboProtocoltype();
	afx_msg void OnSelchangeComboCenter();
	afx_msg void OnBtnSure();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnSelchangeCmbAddrType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cnbNICType;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMHOSTNETCFG_H__B4CBF589_1EC3_4891_8F95_474757127B3E__INCLUDED_)
