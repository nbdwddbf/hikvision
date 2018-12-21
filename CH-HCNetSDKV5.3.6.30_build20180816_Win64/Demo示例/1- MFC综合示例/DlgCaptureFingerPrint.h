#pragma once


// CDlgCaptureFingerPrint 对话框

class CDlgCaptureFingerPrint : public CDialog
{
	DECLARE_DYNAMIC(CDlgCaptureFingerPrint)

public:
	CDlgCaptureFingerPrint(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCaptureFingerPrint();
    BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DLG_CAPTURE_FINGER_PRINT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    int m_iDevIndex;
    long m_lServerID;
    afx_msg void OnBnClickedBtnGetFingerPrint();
    afx_msg LRESULT OnMsgCaptureFingerPrintFinish(WPARAM wParam, LPARAM lParam);
    LONG m_lRemoteHandle;
    CComboBox m_cmbFingerPrintPicType;
    int m_iFingerNo;
    int m_iFingerPrintQuality;
    int m_iFingerNoReturn;
};
