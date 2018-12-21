#pragma once


// CDlgHardDiskStorageTest 对话框

class CDlgHardDiskStorageTest : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgHardDiskStorageTest)

public:
	CDlgHardDiskStorageTest(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgHardDiskStorageTest();

// 对话框数据
	enum { IDD = IDD_DLG_HARD_DISK_STORAGE_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonGet();
    CString m_strCardNo;
    int m_iRssi;

    LONG m_lUserID;
    int m_iDeviceIndex;
    afx_msg void OnTimer(UINT_PTR nIDEvent);

    BOOL m_bStart;
    void GetHardDiskStorageTest();
    afx_msg void OnClose();
};
