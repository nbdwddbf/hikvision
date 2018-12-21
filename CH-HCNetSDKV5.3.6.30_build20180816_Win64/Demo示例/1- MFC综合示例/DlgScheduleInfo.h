#pragma once


// CDlgScheduleInfo 对话框

class CDlgScheduleInfo : public CDialog
{
	DECLARE_DYNAMIC(CDlgScheduleInfo)

public:
	CDlgScheduleInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgScheduleInfo();
    BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DLG_SCHEDULE_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
    int m_iDevIndex;
    long m_lServerID;
    afx_msg void OnBnClickedBtnGetScheduleInfo();
    afx_msg void OnBnClickedBtnCleanScheduleInfo();
    afx_msg void OnCbnSelchangeComboCommand();
    CComboBox m_cmbCommand;
    int m_iEmployeeNo;
    CString m_csName;
    CListCtrl m_lstScheduleInfo;
    COleDateTime	m_startDate;
    COleDateTime	m_startTime;
    COleDateTime	m_stopDate;
    COleDateTime	m_stopTime;
    NET_DVR_SEARCH_INFO_COND m_struSearchInfoCond;
    NET_DVR_SCHEDULE_INFO_CFG m_struScheduleInfoCfg;
    LONG m_lHandle;
    BOOL m_bGetNext;
    HANDLE m_hGetInfoThread;
    static DWORD WINAPI GetScheduleInfoThread(LPVOID lpScheduleInfo);
    void AddScheduleInfoCfg(LPNET_DVR_SCHEDULE_INFO_CFG lpInter);
};
