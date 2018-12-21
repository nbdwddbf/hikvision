#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "EzvizDDNSAPI.h"
#include "DlgEzvizLogin.h"
#include "rapidjson\rapidjson.h"
#include "rapidjson\document.h"
using namespace rapidjson;

#define WM_DDNSAREALIST (WM_USER+200)
#define WM_DDNSGETDEVICELIST (WM_USER+2000)

// CDlgAddDevice dialog

class CDlgAddDevice : public CDialog
{
	DECLARE_DYNAMIC(CDlgAddDevice)

public:
	CDlgAddDevice(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgAddDevice();


// Dialog Data

public:

// 	BOOL OnInitDialog();
	//{{AFX_DATA(CDlgAddDevice)
	enum { IDD = IDD_DLG_ADD_DEVICE };
	CString m_csNodeName;	
	CString m_csUserName;
	CString m_csPwd;
	int m_iDeviceIndex;
	BOOL m_bChkGetIPByIPServer;
	CString m_csDeviceName;
	CString m_csDevSN;	
	int m_iIPServerPort;
	int		m_nLoginPort;
	CString	m_csDevAddr;
	CString	m_csDDNSAddr;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CDlgAddDevice)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CDlgAddDevice)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedAddDeviceOk();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedBtnGetDevIp();
    afx_msg void OnBnClickedChkGetIpByIPServer();	
	afx_msg void OnActivateDevice();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
    CComboBox m_cmbProxyType;
	afx_msg void OnBnClickedRefresh();
	afx_msg void OnBnClickedEzvizlogin();
	afx_msg void OnBnClickedDevconfirm();
	CComboBox m_cmbAreaList;
	CListCtrl m_DeviceList;

    CComboBox m_cmbLoginMode;
    CComboBox m_cmbHttps;

	afx_msg LRESULT GetAreaList(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT GetDeviceList(WPARAM wParam, LPARAM lParam);
	afx_msg void OnNMDblclkEzvizdevicelist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedAutoPolling();
	afx_msg void OnBnClickedUsehcaccount();
	afx_msg void OnBnClickedUsedevaccount();
};
