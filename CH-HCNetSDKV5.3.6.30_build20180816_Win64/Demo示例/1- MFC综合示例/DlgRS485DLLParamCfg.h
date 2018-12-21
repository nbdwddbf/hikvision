#pragma once


// CDlgRS485DLLParamCfg 对话框

#define TIME_RS485_DLL_FILE_PROGRESS  1

class CDlgRS485DLLParamCfg : public CDialog
{
	DECLARE_DYNAMIC(CDlgRS485DLLParamCfg)

public:
	CDlgRS485DLLParamCfg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgRS485DLLParamCfg();

// 对话框数据
	enum { IDD = IDD_DLG_RS485_DLL_PARAM_CFG };

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
    DWORD m_dwUpLoadFileSize;

public:
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnBnClickedBtnChooseDllFile();
    afx_msg void OnBnClickedBtnSaveDllFile();
    afx_msg void OnBnClickedBtnImportDll();
    afx_msg void OnBnClickedBtnExportDll();
    CString m_sFilePath;
    CString m_sSaveFilePath;
};
