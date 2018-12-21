#pragma once
#include "afxwin.h"


// CDlgFaceData 对话框

class CDlgFaceData : public CDialog
{
	DECLARE_DYNAMIC(CDlgFaceData)

public:
	CDlgFaceData(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgFaceData();

// 对话框数据
	enum { IDD = IDD_DLG_FACE_DATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnStartUpload();
    afx_msg void OnBnClickedBtnSelectFile();
    HANDLE  m_hFile;
    LONG m_iFileSize;
    BOOL OnInitDialog();
public:
    LONG  m_lChannel;
    LONG  m_lUserID;
    int   m_iDeviceIndex;
    LONG m_lUploadHandle;
    LONG m_lUploadHandleFD;
    HANDLE	m_hUpLoadThread;
    BOOL    m_bUpLoading;
    char  m_szStatusBuf[ISAPI_STATUS_LEN];
    CString m_szPicID;
    CString m_szFDID;
    CString m_strFilePath;
    DWORD m_dwUploadProgress;
    CComboBox m_comUploadState;
    LONG    m_lDownloadHandle;
    NET_DVR_UPLOAD_FACE_DATA_OUT m_struFaceDataRet;
    afx_msg void OnBnClickedBtnUodate();
    CString m_strFDCustomInfo;
    CComboBox m_comFDLibType;
    HANDLE  m_hPicDownloadThread;
    BOOL m_bStopDownloadPic;
    afx_msg void OnBnClickedBtnStopUpload();
    afx_msg void OnBnClickedBtnUploadFacelib();
    afx_msg void OnBnClickedBtnFileBrower();
    afx_msg void OnBnClickedBtnUpload();
    afx_msg void OnBnClickedBtnDwonload();
    CString m_szCheckCode;
    CString m_szPathFD;
    BOOL m_bCover;
    afx_msg void OnBnClickedBtnFacelibSearch();
};
