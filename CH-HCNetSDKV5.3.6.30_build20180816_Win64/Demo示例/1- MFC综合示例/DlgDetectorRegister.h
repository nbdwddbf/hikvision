#pragma once


// CDlgDetectorRegister 对话框

class CDlgDetectorRegister : public CDialog
{
	DECLARE_DYNAMIC(CDlgDetectorRegister)

public:
	CDlgDetectorRegister(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDetectorRegister();
    int m_iDevIndex;
    LONG m_lServerID;
    int  m_iRowCount;
    LONG m_lTranHandle;
    BOOL m_bGetNext;
    HANDLE	m_hGetInfoThread;
    void AddInfoToDlg();
    NET_DVR_ALARMHOST_DETECTOR_INFO m_struInfo;
    static DWORD WINAPI GetConfigThread(LPVOID lpArg);
// 对话框数据
	enum { IDD = IDD_DLG_DETECTOR_REGISTER };
    BOOL OnInitDialog();
    CListCtrl	m_listData;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnDetectorRegister();
};



