#pragma once


// CDlgRecPassBackHistorySchdule 对话框

class CDlgRecPassBackHistorySchdule : public CDialogEx
{
    DECLARE_DYNAMIC(CDlgRecPassBackHistorySchdule)

public:
    CDlgRecPassBackHistorySchdule(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CDlgRecPassBackHistorySchdule();

    // 对话框数据
    enum { IDD = IDD_DLG_RECORD_PASS_BACK_HISTORY_SCHEDULE };
    CComboBox m_comboWeekday;
    BOOL m_bCheckAllDay;
    CComboBox m_comboCopyWeekday;
    int m_iHour11;
    int m_iMin11;
    int m_iHour12;
    int m_iMin12;
    int m_iHour21;
    int m_iMin21;
    int m_iHour22;
    int m_iMin22;
    int m_iHour31;
    int m_iMin31;
    int m_iHour32;
    int m_iMin32;
    int m_iHour41;
    int m_iMin41;
    int m_iHour42;
    int m_iMin42;
    int m_iHour51;
    int m_iMin51;
    int m_iHour52;
    int m_iMin52;
    int m_iHour61;
    int m_iMin61;
    int m_iHour62;
    int m_iMin62;
    int m_iHour71;
    int m_iMin71;
    int m_iHour72;
    int m_iMin72;
    int m_iHour81;
    int m_iMin81;
    int m_iHour82;
    int m_iMin82;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedBtnRemoteRecOk();
    afx_msg void OnBnClickedBtnRemoteRecExit();
    afx_msg void OnBnClickedBtnRemoteRecCopy();
    afx_msg void OnCbnSelchangeComboWeekDay();
    afx_msg void OnBnClickedChkAllDay();

    DECLARE_MESSAGE_MAP()

public:
    int m_nDate;
    int m_nCopyDate;
    void EnableControlAllDay(BOOL bEnable);
    BOOL TimeTest();

    LPNET_DVR_RECORD_PASSBACK_HISTORY_PLAN_CFG m_pStruRecordPassBackHistoryPlanCfg;
};
