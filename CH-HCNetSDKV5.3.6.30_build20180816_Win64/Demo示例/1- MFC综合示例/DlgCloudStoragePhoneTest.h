#include "afxwin.h"
#if !defined(AFX_DLGCLOUDSTORAGEPHONETEST_H__26C49E00_3C3B_409B_B3D5_20611C8081F1__INCLUDED_)
#define AFX_DLGCLOUDSTORAGEPHONETEST_H__26C49E00_3C3B_409B_B3D5_20611C8081F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCloudStoragePhoneTest.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCloudStoragePhoneTest dialog

class CDlgCloudStoragePhoneTest : public CDialog
{
// Construction
public:
	CDlgCloudStoragePhoneTest(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCloudStoragePhoneTest)
	enum { IDD = IDD_DLG_CLOUDSTORAGE_TEST };
	CComboBox	m_comPoolParam;
	CString	m_csIP;
	CString	m_csPassword;
	CString	m_csPhoneNum;
	DWORD	m_dwPoolID;
	CString	m_csUser;
	DWORD	m_dwPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCloudStoragePhoneTest)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCloudStoragePhoneTest)
	afx_msg void OnBtnCloudTest();
	afx_msg void OnBtnPhoneTest();
	afx_msg void OnSelchangeComboPoolparam();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnCloudSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG  m_lUserID;
    DWORD m_dwDevIndex;
    LONG  m_lCloudServerTest;
    LONG  m_lPhoneTest;

    NET_DVR_SERVER_TEST_PARA m_struServerTestPara;
    NET_DVR_SERVER_TEST_PARA m_struPhoneTestPara;
public:
    static DWORD WINAPI GetCloudServerTestInfoThread(LPVOID lpArg);
    static DWORD WINAPI GetPhoneTestInfoThread(LPVOID lpArg);
    CComboBox m_comboProtocolType;
    CString m_strAccessKey;
    CString m_strSecretKey;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCLOUDSTORAGEPHONETEST_H__26C49E00_3C3B_409B_B3D5_20611C8081F1__INCLUDED_)
