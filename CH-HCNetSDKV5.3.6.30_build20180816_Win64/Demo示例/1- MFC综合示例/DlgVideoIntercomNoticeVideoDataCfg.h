#pragma once


// CDlgVideoIntercomNoticeVideoDataCfg 对话框
#define TIMER_UPDOWNLOAD_CONFIG_PROGRESS 1 //上传下载进度定时器

class CDlgVideoIntercomNoticeVideoDataCfg : public CDialog
{
	DECLARE_DYNAMIC(CDlgVideoIntercomNoticeVideoDataCfg)

public:
	CDlgVideoIntercomNoticeVideoDataCfg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgVideoIntercomNoticeVideoDataCfg();

// 对话框数据
	enum { IDD = IDD_DLG_VIDEO_INTERCOM_NOTICE_VIDEO_DATA_CFG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg LRESULT OnMsgGetVideoDataFinish(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnScan();
    afx_msg void OnBnClickedBtnUpload();
    void ProcessGetNoticeVideoDataCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen);
    LONG m_lServerID;
    LONG m_iDevIndex;

    CString	m_szUpload;
    DWORD m_dwFileLength;
    NET_DVR_NOTICE_VIDEO_DATA m_struNoticeVideoData;
    BOOL m_bUploading;        //正在上传
    LONG m_lUpdownloadHandle; //上传/下载句柄
    CProgressCtrl	m_ctrlProgress;
    CStatic	m_statProgress;
    afx_msg void OnBnClickedBtnStart();
    afx_msg void OnBnClickedBtnStop();
    LONG m_lGetHandle;
    DWORD m_dwVideoDataLen;
    HANDLE m_hVideoDataFile;
    DWORD m_dwVideoDataReturn;
    CString	m_strNoticeNumber;
};
