#if !defined(AFX_DLGWIRELESSSERVER_H__7259F314_4744_4FE2_8CC1_F6A9967665AD__INCLUDED_)
#define AFX_DLGWIRELESSSERVER_H__7259F314_4744_4FE2_8CC1_F6A9967665AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWirelessServer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgWirelessServer dialog

class DlgWirelessServer : public CDialog
{
// Construction
public:
	DlgWirelessServer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgWirelessServer)
	enum { IDD = IDD_DLG_WIRELESS_SERVER };
    BOOL	m_byDefaultPassword;
	CComboBox	m_comBroadcastEnable;
	CComboBox	m_comHotSpotEnable;
	CComboBox	m_comEncryptionMode;
	CComboBox	m_comSafeMode;
	CComboBox	m_comChannel;
    CString	m_szSsidInformation;
	CString	m_szPassWd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgWirelessServer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgWirelessServer)
    virtual BOOL OnInitDialog();
	afx_msg void OnSet();
	afx_msg void OnGet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG  m_lChannel;
    LONG m_lUserID;
    int m_iDeviceIndex;

    char m_szStatusBuf[ISAPI_STATUS_LEN];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWIRELESSSERVER_H__7259F314_4744_4FE2_8CC1_F6A9967665AD__INCLUDED_)
