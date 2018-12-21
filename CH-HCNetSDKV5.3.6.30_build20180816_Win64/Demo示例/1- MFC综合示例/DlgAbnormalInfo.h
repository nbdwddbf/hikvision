#pragma once


// CDlgAbnormalInfo 对话框

class CDlgAbnormalInfo : public CDialog
{
	DECLARE_DYNAMIC(CDlgAbnormalInfo)

public:
	CDlgAbnormalInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAbnormalInfo();
    BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DLG_ABNORMAL_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    int m_iDevIndex;
    long m_lServerID;
    afx_msg void OnBnClickedBtnGetAbnormalInfo();
    afx_msg void OnBnClickedBtnCleanAbnormalInfo();
    CComboBox m_cmbCommand;
    int m_iEmployeeNo;
    CString m_csName;
    CListCtrl m_lstAbnormalInfo;
    COleDateTime	m_startDate;
    COleDateTime	m_startTime;
    COleDateTime	m_stopDate;
    COleDateTime	m_stopTime;
    NET_DVR_SEARCH_INFO_COND m_struSearchInfoCond;
    NET_DVR_ABNORMAL_CFG m_struAbnormalCfg;
    LONG m_lHandle;
    BOOL m_bGetNext;
    HANDLE m_hGetInfoThread;
    static DWORD WINAPI GetAbnormalInfoThread(LPVOID lpAbnormalInfo);
    void AddAbnormalInfoCfg(LPNET_DVR_ABNORMAL_CFG lpInter);
    afx_msg void OnCbnSelchangeComboCommand();
};
