// configDlg.h : header file
//

#if !defined(AFX_CONFIGDLG_H__89F891D5_7548_4598_96A5_61F3FB4E6D4B__INCLUDED_)
#define AFX_CONFIGDLG_H__89F891D5_7548_4598_96A5_61F3FB4E6D4B__INCLUDED_

#include "config.h"
#include "DlgExceptionCfg.h"	// Added by ClassView
#include "DlgUserCfg.h"	// Added by ClassView
#include "DlgDeviceCfg.h"	// Added by myself,因为是我自己在下面添加 CDlgDeviceCfg m_DlgDeviceCfg;语句，所以得在这里包含头文件。
#include "DlgChanCfg.h"	
#include "DlgSerialCfg.h"
#include "DlgAlarmCfg.h"	// Added by ClassView


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog

class CConfigDlg : public CDialog
{
// Construction
public:	
	
	BOOL DoLogin();
	void OnCancel();
	BOOL m_bIsLogin;
	NET_DVR_DEVICEINFO_V30 DeviceInfoTmp;//定义几个结构体
	NET_DVR_DEVICECFG m_struDeviceCfg;
	NET_DVR_NETCFG_V30 m_struNetCfg;
	NET_DVR_COMPRESSIONCFG_V30 m_struCompressionCfg;
	NET_DVR_RECORD_V30 m_struRecordCfg;
	NET_DVR_PICCFG_V30 m_struPicCfg;
	
	
	CDlgDeviceCfg m_DlgDeviceCfg;//定义几个对话框类的对象，要在configdlg.h中包含这些类的头文件。
	CDlgChanCfg m_DlgChanCfg;
	CDlgSerialCfg m_DlgSerialCfg;
	CDlgAlarmCfg m_DlgAlarmCfg;	
	CDlgExceptionCfg m_DlgExceptionCfg;
	CDlgUserCfg m_DlgUserCfg;
	
	 

	CConfigDlg(CWnd* pParent = NULL);	// standard constructor
	
// Dialog Data
	//{{AFX_DATA(CConfigDlg)
	enum { IDD = IDD_CONFIG_DIALOG };
	CIPAddressCtrl	m_ipctrlDevIP;
	CTabCtrl	m_tabConfigDlg;
	UINT	m_iDevPort;
	CString	m_csPassword;
	CString	m_csUserName;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CConfigDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeTabConfigDlg(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonLogin();
	afx_msg void OnButtonShutdown();
	afx_msg void OnButtonReboot();
	afx_msg void OnButtonRefreshCfg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGDLG_H__89F891D5_7548_4598_96A5_61F3FB4E6D4B__INCLUDED_)
