#pragma once
#include "afxwin.h"


// CUPLOAD_PANORAMIC_STITCH 对话框
#define MAX_BUFFER_LEN   (32*1024)
class CUPLOAD_PANORAMIC_STITCH : public CDialogEx
{
	DECLARE_DYNAMIC(CUPLOAD_PANORAMIC_STITCH)

public:
	CUPLOAD_PANORAMIC_STITCH(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUPLOAD_PANORAMIC_STITCH();

// 对话框数据
	enum { IDD = IDD_DLG_UPLOAD_PANORAMIC_STITCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

    static DWORD WINAPI UpLoadSendThread(LPVOID pParam);
public:
    afx_msg void OnBnClickedBtnGetFilepath();
    CString m_uploadfilepath;
    virtual BOOL OnInitDialog();
    LONG m_lServerID;
    int m_iDeviceIndex;
    LONG m_lChannel;
    LONG m_lGetPANORAMICHandle;
    LONG m_lSetPANORAMICHandle;
    afx_msg void OnBnClickedBtnUplaod();
    afx_msg void OnClose();
    CString strFilePath;
    HANDLE	m_hUpLoadThread;
    DWORD	m_dwThreadId;
    HANDLE  m_hFile;
    LONG m_iFileSize;
};
