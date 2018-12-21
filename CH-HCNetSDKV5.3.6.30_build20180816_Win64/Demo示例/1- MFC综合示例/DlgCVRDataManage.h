#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#define MAX_BUFFER_LEN   (32*1024)

// CDlgCVRDataManage 对话框

class CDlgCVRDataManage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCVRDataManage)

public:
	CDlgCVRDataManage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCVRDataManage();

// 对话框数据
	enum { IDD = IDD_DLG_CVR_DATA_MANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    CComboBox m_comboFileType;
    CString m_strDownloadUrl;
    CString m_strFileName;
    CString m_strFilePath;
    DWORD m_dwFileSize;
    int m_iFileVolumeID;
    CString m_strUploadUrl;
    afx_msg void OnBnClickedButtonBrowse();
    afx_msg void OnBnClickedButtonUpload();
    afx_msg void OnBnClickedButtonDownload();

    LONG m_lServerID;
    LONG m_lDeviceIndex;

    LONG m_lUploadHandle;
    BOOL m_bUpLoading;
    HANDLE m_hUpLoadThread;
    DWORD m_dwThreadId;
    HANDLE m_hUpLoadSendThread;
    DWORD m_dwSendThreadId;
    CFile m_cSendFile;
    CFile m_cRecvFile;

    NET_DVR_UPLOAD_FILEVOLUME_PRARAM m_struFileVolumeDataInfo;
    static DWORD WINAPI GetUpLoadDataThread(LPVOID pParam);
    static DWORD WINAPI GetUpLoadSendDataThread(LPVOID pParam);
    CString m_strSavePath;

    BOOL m_bDownLoading;
    LONG m_lDownloadHandle;
    HANDLE m_hDownloadThread;
    NET_DVR_DOWNLOAD_FILEVOLUME_PARAM m_struFileVolumeDataParam;
    afx_msg void OnBnClickedButtonSavePathBrowse();
    BOOL m_bUploadSubpackage;
    BOOL m_bDownloadDataCallback;
    afx_msg void OnBnClickedButtonSearch();
    afx_msg void OnBnClickedButtonGet();
    afx_msg void OnBnClickedButtonSet();
    afx_msg void OnBnClickedButtonAdd();
    afx_msg void OnBnClickedButtonAddLock();
    afx_msg void OnBnClickedButtonFileLock();
    CListCtrl m_listFileSearch;
    CListCtrl m_listFileLock;
    CString m_strFileSearchUrl;
    CString m_strFileLockUrl;
    int m_iUploadSpeed;
    int m_iDownloadSpeed;

    int m_iRowCount;
    BOOL m_bSelectItem;
    int m_iSubItem;
    int m_iLastItem;

    int m_iRowCountLock;
    BOOL m_bSelectItemLock;
    int m_iSubItemLock;
    int m_iLastItemLock;

    BOOL CreateTransferSpeedCfg(char* pBuf, DWORD dwBufLen, int &dwRet);
    BOOL CreateSearchFileCondition(char* pBuf, DWORD dwBufLen, int &dwRet);
    BOOL CreateLockConfiguration(char* pBuf, DWORD dwBufLen, int &dwRet);
    CComboBox m_comboLockType;
    int m_iLockTime;
    afx_msg void OnBnClickedButtonDeleteSearch();
    afx_msg void OnBnClickedButtonDeleteLock();
    afx_msg void OnNMClickListFileSearch(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMClickListFileLock(NMHDR *pNMHDR, LRESULT *pResult);
    BOOL m_bArchive;
};
