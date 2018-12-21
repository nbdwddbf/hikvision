#pragma once


// CDlgAlarmHostDong 对话框

#define TIME_MODBUS_CFG_FILE_PROGRESS 1

class CDlgAlarmHostDong : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAlarmHostDong)

public:
	CDlgAlarmHostDong(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAlarmHostDong();

// 对话框数据
	enum { IDD = IDD_DLG_ALARMHOST_DONG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
    LONG m_iUserID;
    LONG m_iDeviceIndex;

private:
    LONG m_lUpdownloadHandle; //上传/下载句柄
    BOOL m_bUploading;        //正在上传
    BOOL m_bDownloading;      //正在下载

public:
    CString m_sFilePath;
    afx_msg void OnBnClickedBtnChooseFile();
    afx_msg void OnBnClickedBtnSaveFile();
    afx_msg void OnBnClickedBtnImport();
    afx_msg void OnBnClickedBtnExport();
    CString m_sSaveFilePath;
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    DWORD m_dwChanNo;
    DWORD m_dwSlotNo;
    CString m_sOutput1;
    CString m_sOutput2;
    CString m_sOutput3;
    CString m_sOutput4;
    CString m_sOutput5;
    CString m_sOutput6;
    afx_msg void OnBnClickedBtnControl();
    BOOL m_bSwitch;
};
