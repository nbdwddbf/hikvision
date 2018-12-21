#if !defined(AFX_DLGCLOUDSTORAGE_H__70CFACB8_C352_4859_9F07_D3C1BE4BE2F4__INCLUDED_)
#define AFX_DLGCLOUDSTORAGE_H__70CFACB8_C352_4859_9F07_D3C1BE4BE2F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCloudStorage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCloudStorage dialog

class CDlgCloudStorage : public CDialog
{
// Construction
public:
	CDlgCloudStorage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCloudStorage)
	enum { IDD = IDD_DLG_CLOUD_STORAGE };
	CComboBox	m_cmbZoomType;
	CComboBox	m_cmbCoverType;
	CComboBox	m_cmbPoolType;
	CComboBox	m_cmbPoolID;
	CComboBox	m_cmbClusterStatus;
	CString	m_strPicCameraID;
	CString	m_strPicPath;
	CString	m_strPicCommenState;
	CString	m_strPicSingleState;
	DWORD	m_dwTotalSpace;
	DWORD	m_dwOnlineSpace;
	DWORD	m_dwFreeSpace;
	DWORD	m_dwAllocatedSpace;
	DWORD	m_dwCoverCycle;
	DWORD	m_dwPoolFreeSize;
	CString	m_strPoolName;
	DWORD	m_dwPoolSize;
	CString	m_strDownloadCmrID;
	CString	m_strStartTime;
	CString	m_strStopTime;
	CString	m_strSavePath;
	int		m_iQualityPer;
	int		m_iScalePer;
	int		m_iHeight;
	int		m_iWidth;
	BOOL	m_bBmp;
	BOOL	m_bJpg;
	BOOL	m_bPng;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCloudStorage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
public:
    LONG m_lUserID;
    int m_iDeviceIndex;
    int m_iStartPoolID;
    int m_iMaxPoolID;
    int m_iPoolCount;
    int m_iPucturePoolID;
    LONG m_lUploadPicHandle;
    HANDLE	m_hPicUpLoadThread;
    HANDLE  m_hPicDownloadThread;
    BOOL m_bStopUploadPic;
    BOOL m_bStopDownloadPic;
    NET_DVR_UPLOAD_FILE_RET m_struPicRet;
    char *m_pPoolList;
    DWORD m_dwPoolListLen;
    LONG m_lDownloadPicHandle;

    BOOL GetCloudStorageAbility();
    BOOL GetPicturePoolID();
    BOOL PicUpload(CString strFileName, CString strFilePath, BYTE byPicType);
    BOOL CreateStoragePool(DWORD dwPoolID, char* pBuf, DWORD dwBufLen, int &dwRet);
    BOOL ShowPoolCfg(DWORD dwPoolID);
    BOOL GetCloudStoragePoolProperty();

    static DWORD WINAPI PicUpLoadThread(LPVOID pParam);
    static DWORD WINAPI PicDownloadThread(LPVOID pParam);
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCloudStorage)
	afx_msg void OnBtnUploadPic();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnUploadPicStop();
	afx_msg void OnBtnGetClusterresource();
	afx_msg void OnBtnCreatePool();
	afx_msg void OnBtnDeletePool();
	afx_msg void OnBtnGetPool();
	afx_msg void OnBtnSetPool();
	afx_msg void OnClose();
	afx_msg void OnSelchangeCmbPoolId();
	afx_msg void OnBtnStopDowloadPic();
	afx_msg void OnBtnDowloadPic();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCLOUDSTORAGE_H__70CFACB8_C352_4859_9F07_D3C1BE4BE2F4__INCLUDED_)
