#if !defined(AFX_DLGVEDIOIMGDB_H__7C33FE95_22CD_42FB_AC29_1040EAFA5B46__INCLUDED_)
#define AFX_DLGVEDIOIMGDB_H__7C33FE95_22CD_42FB_AC29_1040EAFA5B46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVedioImgDB.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVedioImgDB dialog
#define DOWNLOAD_DB_FILE_TIMER (WM_USER+105)
#define UPLOAD_DB_FILE_TIMER (WM_USER+106)

#define MAX_BUFFER_LEN   (32*1024)

class CDlgVedioImgDB : public CDialog
{
// Construction
public:
	CDlgVedioImgDB(CWnd* pParent = NULL);   // standard constructor
	~CDlgVedioImgDB();

// Dialog Data
	//{{AFX_DATA(CDlgVedioImgDB)
	enum { IDD = IDD_DLG_VEDIO_IMG_DB };
	CString	m_i64Available;
	CString	m_i64Capacity;
	CString	m_strFileID;
	CString	m_i64FileLen;
	CString	m_i64Used;
	CString	m_i64Offset;
	CString	m_strStatus;
	UINT	m_dwSpeed;
	//}}AFX_DATA


	int		m_lUserID;
    int		m_iDevIndex;
	FILE	*m_fp;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVedioImgDB)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVedioImgDB)
	afx_msg void OnButtonGetCap();
	afx_msg void OnButtonSetCap();
	afx_msg void OnButtonQueryFile();
	afx_msg void OnButtonDelFile();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonUploadStart();
	afx_msg void OnButtonUploadClose();
	afx_msg void OnButtonDownloadStart();
	afx_msg void OnButtonDownloadClose();
	afx_msg void OnButtonControlSpeed();
#if (_MSC_VER >= 1500)	//vs2008
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif	afx_msg void OnBtnRefuse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	static DWORD WINAPI UpLoadSendThread(LPVOID pParam);

private:
	NET_DVR_VIDEO_IMG_DB_CFG	m_struVideoImgDBCfg;
	NET_DVR_FILE_INFO_IN		m_struFileInfoIn;
	NET_DVR_FILE_QUERY_INFO		m_struQueryInfo;
	char						m_szStatusBuf[ISAPI_STATUS_LEN];
	char						m_szFileName[MAX_PATH];
	HANDLE						m_hFile;
	

	LONG	m_lUploadHandle;
	HANDLE	m_hUpLoadThread;
    DWORD	m_dwThreadId;
	LONG	m_lDownloadHandle;
	LONG    m_timerHandle;
	BOOL	m_bStop;

	

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVEDIOIMGDB_H__7C33FE95_22CD_42FB_AC29_1040EAFA5B46__INCLUDED_)
