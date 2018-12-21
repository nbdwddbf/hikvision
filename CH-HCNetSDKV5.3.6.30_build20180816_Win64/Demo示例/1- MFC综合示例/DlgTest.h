#pragma once
#include "afxwin.h"


// CDlgTest 对话框

class CDlgTest : public CDialogEx
{
    DECLARE_DYNAMIC(CDlgTest)

public:
    CDlgTest(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CDlgTest();

    // 对话框数据
    enum { IDD = IDD_DLG_TEST };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()
public:
    DWORD m_dwChan;
    DWORD m_dwIn;
    DWORD m_dwOut;
    DWORD m_dwST;
    DWORD m_dwEt;
    DWORD m_dwEh;
    DWORD m_dwAlarm;
    LONG m_lServerID;
    int m_iDeviceIndex;
    LONG m_lChannel;
    DWORD m_dwFileType;
    afx_msg void OnBnClickedBtnSet();
    CComboBox m_cmbWorkMode;
    CComboBox m_cmbPreviewImageMode;

    afx_msg void OnBnClickedBtnSetCounting();
    afx_msg void OnBnClickedBtnGetCounting();
    NET_DVR_CAMERA_WORK_MODE struCameraWorkMode;
    afx_msg void OnBnClickedBtnFilePath();
    CString m_csFilePath;
    afx_msg void OnBnClickedBtnFileUpload();
    LONG    m_lUploadHandle;
    BOOL    m_bUpLoading;
    HANDLE	m_hUpLoadThread;
    afx_msg void OnBnClickedBtnFileUploadDeepeyesBinocular();
    afx_msg void OnBnClickedBtnFilePathDeepeyesBinocular();

    LONG    m_lUploadHandleTX1;
    BOOL    m_bUpLoadingTX1;
    HANDLE	m_hUpLoadThreadTX1;
    CString m_csDeepeyesFilePath;
    CComboBox m_comFileType;
    afx_msg void OnCbnSelchangeComboFiletype();
    virtual BOOL OnInitDialog();
};
