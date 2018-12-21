#if !defined(AFX_DLGVCAREMOTECHANNEL_H__1EA72F92_72A5_4411_B513_6ED71341EDFD__INCLUDED_)
#define AFX_DLGVCAREMOTECHANNEL_H__1EA72F92_72A5_4411_B513_6ED71341EDFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaRemoteChannel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaRemoteChannel dialog

class CDlgVcaRemoteChannel : public CDialog
{
// Construction
public:
	CDlgVcaRemoteChannel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaRemoteChannel)
	enum { IDD = IDD_DLG_VCA_REMOTE_CHANNEL };
	CString	m_strAddress;
	DWORD	m_nChannelNo;
	CString	m_strPassword;
	DWORD	m_nPort;
	CString	m_strUserName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaRemoteChannel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaRemoteChannel)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void SetRemoteChannelParam(CString strAddress,DWORD dwPort,CString strUserName,CString strPwd,DWORD dwChannel);
	void GetRemoteChannelParam(CString& strAddress,DWORD& dwPort,CString& strUserName,CString& strPwd,DWORD& dwChannel);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCAREMOTECHANNEL_H__1EA72F92_72A5_4411_B513_6ED71341EDFD__INCLUDED_)
