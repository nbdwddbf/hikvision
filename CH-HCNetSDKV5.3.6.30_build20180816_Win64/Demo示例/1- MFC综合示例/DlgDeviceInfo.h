#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CDlgDeviceInfo dialog

class CDlgDeviceInfo : public CDialog
{
	DECLARE_DYNAMIC(CDlgDeviceInfo)

public:
	CDlgDeviceInfo(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgDeviceInfo();

// Dialog Data

public:
	//{{AFX_DATA(CDlgDeviceInfo)
	enum { IDD = IDD_DLG_DEVICE_INFO };
	CString m_csLocalNodeName;
	CString m_csUserName;
	CIPAddressCtrl m_ctrlIPAddr;
	CString m_csPwd;
	int m_iPort;
	CString m_csMultiIP;
	int m_iChanNum;
	//CComboBox m_comboDeviceType;
	CString m_csSerialNo;
	CString	m_csDeviceTypeName;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CDlgDeviceInfo)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgDeviceInfo)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedDevinfoOk();
	afx_msg void OnBnClickedDevinfoCancel();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	int m_iDeviceIndex;
	int m_iSelType;
	int m_iTypeNum;
    CString m_csDeviceClassName;
    CString m_csClassName;

    CComboBox m_cmbLoginMode;
    CComboBox m_cmbHttps;
};
