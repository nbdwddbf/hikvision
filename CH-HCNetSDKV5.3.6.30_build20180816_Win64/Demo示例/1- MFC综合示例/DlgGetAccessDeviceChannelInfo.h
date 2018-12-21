#if !defined(AFX_DLGGETACCESSDEVICECHANNELINFO_H__511D4166_1867_4977_BB6A_41E46C01674E__INCLUDED_)
#define AFX_DLGGETACCESSDEVICECHANNELINFO_H__511D4166_1867_4977_BB6A_41E46C01674E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGetAccessDeviceChannelInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGetAccessDeviceChannelInfo dialog

class CDlgGetAccessDeviceChannelInfo : public CDialog
{
// Construction
public:
	CDlgGetAccessDeviceChannelInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgGetAccessDeviceChannelInfo)
	enum { IDD = IDD_DLG_GET_ACCESS_DEVICE_CHANNEL_INFO };
	CComboBox	m_cmbAccessMode;
	CComboBox	m_comboProType;
	CString	m_strDomain;
	CString	m_strIP;
	CString	m_strPasswd;
	CString	m_strUserName;
	CString	m_strOutput;
	short	m_wPort;
	DWORD	m_dwGroup;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGetAccessDeviceChannelInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGetAccessDeviceChannelInfo)
	afx_msg void OnBtnGet();
	afx_msg void OnButtonUpdateProList();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG m_lUserID;
	DWORD m_dwDevIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGETACCESSDEVICECHANNELINFO_H__511D4166_1867_4977_BB6A_41E46C01674E__INCLUDED_)
