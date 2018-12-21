#if !defined(AFX_DLGAUDIOUPLOADDOWNLOAD_H__CDC42592_6063_4E59_A417_455EF9E3B5F5__INCLUDED_)
#define AFX_DLGAUDIOUPLOADDOWNLOAD_H__CDC42592_6063_4E59_A417_455EF9E3B5F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAudioUploadDownload.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAudioUploadDownload dialog

class CDlgAudioUploadDownload : public CDialog
{
// Construction
public:
	void FunEnableWindow(BOOL bEnableStart, BYTE byType);
	LONG m_lPos;
	int m_nPackNum;
	LONG m_lUploadHandle;
	LONG m_lDownloadHandle;
	int m_iDeviceIndex;
	LONG m_lUploadTimer;
	LONG m_lDownloadTimer;
	LONG m_lAudioNum;
	CDlgAudioUploadDownload(CWnd* pParent = NULL);   // standard constructor
	~CDlgAudioUploadDownload();
	NET_DVR_ALARMHOST_ABILITY m_struAbility;
	NET_DVR_UPLOAD_PARAM m_struUpload;
	NET_DVR_DOWNLOAD_PARAM m_struDownload;
	char* m_pAudioBuf;
	DWORD m_dwAudioLen;
	CFile m_fileDown;
	char m_szLan[128];
	void InitComboBox();


// Dialog Data
	//{{AFX_DATA(CDlgAudioUploadDownload)
	enum { IDD = IDD_DLG_AUDIOUPDOWN };
	CComboBox	m_cmAudioNum;
	CComboBox	m_cmAudioCtrl;
	CProgressCtrl	m_progressUpload;
	CProgressCtrl	m_progressDownload;
	CString	m_csDownloadPath;
	CString	m_csUploadPath;
	CString	m_csDownload;
	CString	m_csUpload;
	int		m_radioDownload;
	int		m_radioUpload;
	CString	m_strName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAudioUploadDownload)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAudioUploadDownload)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnUploadStart();
	afx_msg void OnBtnUploadpath();
	afx_msg void OnBtnUploadStop();
	afx_msg void OnBtnDownloadStart();
	afx_msg void OnBtnDownloadStop();
	virtual void OnCancel();
#if (_MSC_VER >= 1500)	//vs2008
    afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
    afx_msg void OnTimer(UINT nIDEvent);
#endif
	afx_msg void OnBtnCtrl();
	afx_msg void OnRadioUploadByfile();
	afx_msg void OnRadioUploadBybuffer();
	afx_msg void OnRadioDownloadByfile();
	afx_msg void OnRadioDownloadBybuffer();
	afx_msg void OnBtnSetAudioName();
	afx_msg void OnBtnGetAudioName();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAUDIOUPLOADDOWNLOAD_H__CDC42592_6063_4E59_A417_455EF9E3B5F5__INCLUDED_)
