#pragma once


// CDlgJPEGPicDownloadMedical 对话框

class CDlgJPEGPicDownloadMedical : public CDialog
{
	DECLARE_DYNAMIC(CDlgJPEGPicDownloadMedical)

public:
	CDlgJPEGPicDownloadMedical(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgJPEGPicDownloadMedical();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持


public:
    BOOL m_bDown;
    BOOL m_bSearchDown;
    BOOL m_bBackuping;
    HANDLE m_hBackupThread;

    int m_iChannel;
    HWND m_hPareTabWnd;
    HWND m_hPareDlgWnd;
    LONG  m_lFileHandle;
    HANDLE m_hFileThread;
    HANDLE m_hGetThread;
    int iFileType;
    int m_iFileNum;
    int iSelServer;
    LONG m_lStartChan;
    LONG m_lServerID;
    LONG m_lServerType;
    int m_iIPChanNum;
    int m_iChanNum;
    BOOL m_bFindFile;
    char filenamedownload[256];
    int m_iDeviceIndex;
    CString m_csPatientID;
    POSITION  pos;
    int nSelPics;
    int nDownPics;
    //NET_DVR_FIND_PICTURE_PARAM m_struFindPictureParam;
    NET_DVR_FIND_PICTURE_MEDICAL_PARAM m_struFindPictureParam;
    NET_DVR_DISKABILITY_LIST  m_struDiskList;

    LONG    m_lBackupHandle;
    NET_DVR_FIND_PICTURE *m_pFindPicture;

public:

    void F_Close();
    BOOL CheckInitParam();
    void SetParentWnd(HWND *hhWnd, int iParentNum);
    void GetFindPictureParamFromWnd();
    void GetFindPictureParamFromWnd(NET_DVR_FIND_PICTURE_PARAM &struPictureParam);
    BOOL GetBackupPictureParamFromWnd_FILE(NET_DVR_BACKUP_PICTURE_PARAM &struBackPicturParam);
    BOOL GetDiskList(NET_DVR_DISKABILITY_LIST &struDiskList);
    DWORD ProcessFileSize(CString csFileSize);

    /*NET_DVR_FIND_PICTURE_PARAM*/


    // Dialog Data
    //{{AFX_DATA(CJPEGPicDownload)
    enum { IDD = IDD_DLG_MEDICAL_PATIENT };
    CComboBox	m_comCountry;
    CComboBox	m_comRegion;
    CComboBox	m_comHvtType;
    CComboBox	m_comProvince;
    CComboBox	m_comboBackupType;
    CComboBox	m_comboDiskList;
    CStatic	m_ShowJpegCtrl;
    CProgressCtrl	m_downProgress;
    CListCtrl	m_PicList;
    CComboBox	m_PicTypeCtrl;
    CComboBox	m_ChannelCtrl;
    CString	m_sCardNum;
    BOOL	m_bChkCard;
    CTime	m_ctDateStart;
    CTime	m_ctDateStop;
    CTime	m_ctTimeStart;
    CTime	m_ctTimeStop;
    BOOL	m_bContinue;
    CString	m_sLicense;
    BOOL	m_bRetWithFaceRect;
    //}}AFX_DATA


    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CJPEGPicDownload)
protected:
    virtual void PostNcDestroy();
    //}}AFX_VIRTUAL

    // Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CJPEGPicDownload)
    /*virtual void OnOK();
    virtual void OnCancel();*/
    virtual BOOL OnInitDialog();
    afx_msg void OnSearchlist();
    afx_msg void OnDownload();
    afx_msg void OnCheckcard();
    afx_msg void OnClickRemotepiclist(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDestroyResource();
    afx_msg void OnBtnBackup();
    afx_msg void OnSelchangeComboDiskList();
    afx_msg void OnUpload();
    DECLARE_MESSAGE_MAP()
    //}}AFX_MSG
public:
    CString m_strStreamID;
    DWORD m_dwPicIntervalTime;
    afx_msg void OnBnClickedButtonDownloadPictureByTime();
    LONG m_lDownPicByTimeHandle;
    afx_msg LRESULT OnMsgDownloacPicByTimeFinish(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnMsgAddStaticBoxFileSum(WPARAM wParam, LPARAM lParam);
    void ProcessDownloadPicByTimeCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
    int m_iDownloadPicByTimeSum;
    afx_msg void OnBnClickedButtonStopDownload();
    CComboBox m_comboFileType;

    LONG m_lPort;
    afx_msg void OnBnClickedBtnMedical();
    afx_msg void OnClose();
};
