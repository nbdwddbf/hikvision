#pragma once
#include "afxwin.h"


// CDlgUploadFaceLib 对话框

class CDlgUploadFaceLib : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgUploadFaceLib)

public:
	CDlgUploadFaceLib(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgUploadFaceLib();

// 对话框数据
	enum { IDD = IDD_DLG_UPLOAD_FACELIB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    CString m_csFDID;
    CString m_csPicPath;
    CString m_csXmlPath;
    afx_msg void OnBnClickedBtnXmlImport();
    afx_msg void OnBnClickedBtnPicImport();
    afx_msg void OnBnClickedBtnUpload();
    afx_msg void OnBnClickedBtnStop();


public:
    LONG m_lUserID;
    int m_iDeviceIndex;
    LONG m_lUploadHandle;
    HANDLE	m_hUpLoadThread;
    BOOL m_bStopUpload;
    NET_DVR_SEND_PARAM_IN m_struSendParam;
    BYTE    *pSendAppendData;
    BYTE    *pSendPicData;
    int  m_iNum;
    bool m_bClose;
    static DWORD WINAPI FaceLibUpLoadThread(LPVOID pParam);
    void readFileData();
    void stopUploadData();
    BOOL sendUploadData();
    LONG getUploadState();
    BOOL m_bConcurrent;
    afx_msg void OnClose();
    CComboBox m_comNum;
    afx_msg void OnCbnSelchangeComboNum();
    void timeShow(BOOL bBegin);
    void startControlShow(BOOL bstart);
    CString m_csPID;
    NET_DVR_UPLOAD_FILE_RET m_struPicRet;
    BOOL m_bCover;
    BOOL m_bCustomID;
    BOOL m_bPicURL;
    CString m_strIdentityKey;
};
