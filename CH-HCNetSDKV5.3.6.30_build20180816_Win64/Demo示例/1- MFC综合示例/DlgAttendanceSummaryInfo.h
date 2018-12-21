#pragma once


// CDlgAttendanceSummaryInfo 对话框

class CDlgAttendanceSummaryInfo : public CDialog
{
	DECLARE_DYNAMIC(CDlgAttendanceSummaryInfo)

public:
	CDlgAttendanceSummaryInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAttendanceSummaryInfo();
    BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DLG_ATTENDANCE_SUMMARY_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnGetAttendanceSummaryInfo();
    afx_msg void OnBnClickedBtnCleanAttendanceSummaryInfo();
    afx_msg void OnCbnSelchangeComboCommand();
    int m_iDevIndex;
    long m_lServerID;
    CComboBox m_cmbCommand;
    int m_iEmployeeNo;
    CString m_csName;
    CListCtrl m_lstAttendanceSummaryInfo;
    COleDateTime	m_startDate;
    COleDateTime	m_startTime;
    COleDateTime	m_stopDate;
    COleDateTime	m_stopTime;
    NET_DVR_SEARCH_INFO_COND m_struSearchInfoCond;
    NET_DVR_ATTENDANCE_SUMMARY_CFG m_struAttendanceSummaryCfg;
    LONG m_lHandle;
    BOOL m_bGetNext;
    HANDLE m_hGetInfoThread;
    static DWORD WINAPI GetAttendanceSummaryThread(LPVOID lpAttendanceSummaryInfo);
    void AddAttendanceSummaryCfg(LPNET_DVR_ATTENDANCE_SUMMARY_CFG lpInter);
};
