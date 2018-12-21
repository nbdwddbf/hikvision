#pragma once


// CDlgUHFRFIDReaderCfg 对话框

class CDlgUHFRFIDReaderCfg : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgUHFRFIDReaderCfg)

public:
	CDlgUHFRFIDReaderCfg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgUHFRFIDReaderCfg();

// 对话框数据
	enum { IDD = IDD_DLG_UHF_RFID_READER_CFG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonBasicCfg();
    afx_msg void OnBnClickedButtonHardDiskStorageTest();

    LONG m_lUserID;
    int m_iDeviceIndex;
};
