#pragma once


// CDlgAttendanceRecordInfo 对话框

class CDlgAttendanceRecordInfo : public CDialog
{
	DECLARE_DYNAMIC(CDlgAttendanceRecordInfo)

public:
	CDlgAttendanceRecordInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAttendanceRecordInfo();
    BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DLG_ATTENDANCE_RECORD_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnCleanAttendanceRecordInfo();
    afx_msg void OnBnClickedBtnGetAttendanceRecordInfo();
    int m_iDevIndex;
    long m_lServerID;
    CComboBox m_cmbCommand;
    int m_iEmployeeNo;
    CString m_csName;
    CListCtrl m_lstAttendanceRecordInfo;
    COleDateTime	m_startDate;
    COleDateTime	m_startTime;
    COleDateTime	m_stopDate;
    COleDateTime	m_stopTime;
    NET_DVR_SEARCH_INFO_COND m_struSearchInfoCond;
    NET_DVR_ATTENDANCE_RECORD_CFG m_struAttendanceRecordCfg;
    LONG m_lHandle;
    BOOL m_bGetNext;
    HANDLE m_hGetInfoThread;
    static DWORD WINAPI GetAttendanceRecordThread(LPVOID lpAttendanceRecord);
    void AddAttendanceRecordCfg(LPNET_DVR_ATTENDANCE_RECORD_CFG lpInter);
    afx_msg void OnCbnSelchangeComboCommand();
};
