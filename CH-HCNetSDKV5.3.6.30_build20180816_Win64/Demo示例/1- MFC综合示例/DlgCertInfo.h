#if !defined(AFX_DLGCERTINFO_H__00A8DF0A_C1F8_417C_BF0C_FB2B6C1C6E5F__INCLUDED_)
#define AFX_DLGCERTINFO_H__00A8DF0A_C1F8_417C_BF0C_FB2B6C1C6E5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCertInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCertInfo dialog

#define DOWNLOAD_TIMER WM_USER+100
#define UPLOAD_TIMER WM_USER+101


class CDlgCertInfo : public CDialog
{
// Construction
public:
	CDlgCertInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCertInfo)
	enum { IDD = IDD_DLG_CERTIFICATE };
	short	m_wCertFunc;
	UINT	m_dwKeyAlgorithm;
	UINT	m_dwKeyLen;
	CString	m_strCertPassword;
	short	m_wCertType;
	UINT	m_dwValidDays;
	UINT	m_dwCertVersion;
	CString	m_strCountry;
	CString	m_strEmail;
	BYTE	m_byCertFileType;
	CString	m_strLocality;
	CString	m_strState;
	CString	m_strOrganization;
	CString	m_strUnit;
	CString	m_strCommonName;
	CString	m_strCertFilePath;
	CString	m_strStatus;
	CString	m_strUploadStatus;
	CTime	m_tmrBeginDate;
	CTime	m_tmrBeginTime;
	CTime	m_tmrEndDate;
	CTime	m_tmrEndTime;
	UINT	m_dwSelfSignAlgorithm;
	CString	m_strSelfSignCommonName;
	CString	m_strSelfSignCountry;
	CString	m_strSelfSignEmail;
	CString	m_strSelfSignLocality;
	CString	m_strSelfSignOrganization;
	CString	m_strSelfSignSN;
	CString	m_strSelfSignState;
	CString	m_strSelfSignUnit;
	CComboBox	m_comboCertRequest;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCertInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCertInfo)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonCertCreate();
	afx_msg void OnButtonCertDel();
	afx_msg void OnButtonCertGet();
	afx_msg void OnButtonCertUpload();
	afx_msg void OnButtonBrowseCertFile();
	afx_msg void OnButtonCertDownload();
#if (_MSC_VER >= 1500)	//vs2008
    afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
    afx_msg void OnTimer(UINT nIDEvent);
#endif
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG    m_lUserID;
    int     m_iDevIndex;
	LONG	m_lDownloadHandle;
	LONG	m_lUploadHandle;
	LONG    m_timerHandle;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCERTINFO_H__00A8DF0A_C1F8_417C_BF0C_FB2B6C1C6E5F__INCLUDED_)
