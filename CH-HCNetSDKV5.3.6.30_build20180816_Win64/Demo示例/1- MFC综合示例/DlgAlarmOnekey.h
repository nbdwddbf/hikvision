#pragma once


// CDlgAlarmOnekey 对话框

class CDlgAlarmOnekey : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAlarmOnekey)

public:
	CDlgAlarmOnekey(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAlarmOnekey();

// 对话框数据
	enum { IDD = IDD_DLG_ALARM_ONE_KEY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
    NET_DVR_CALL_WAITTING_CFG m_struCallWaitingCfg;
    NET_DVR_ALARM_LAMP_CFG m_struAlarmLampCfg;
    NET_DVR_VOICE_PROMPTION_CFG m_struVoicePromptionCfg;
    NET_DVR_EMERGENCE_ALARM_RSP_CTRL_CFG m_struEmergenceAlarmRspCtrlCfg;
    LONG    m_lServerID;
    int     m_iDevIndex;
    BOOL    m_bEnable1;
    int     m_iWaitTime;
    BOOL    m_bEnable2;
    int     m_iFlashDuration;
    int     m_iFlashIntervalTime;
    BOOL    m_bEnable3;
    CString m_csCenterBusyFile;
    CString m_csRefusedFile;
    CString m_csHangUpFile;
    CString m_csCallWaittingFile;
    CString m_csConsultWaittingFile;
    CComboBox   m_cmbCommand;
    CComboBox   m_cmbType;
    afx_msg void OnBnClickedBtnGetCallWaiting();
    afx_msg void OnBnClickedBtnSetCallWaiting();
    afx_msg void OnBnClickedBtnGetAlarmLamp();
    afx_msg void OnBnClickedBtnSetAlarmLamp();
    afx_msg void OnBnClickedBtnGetVoicePromption();
    afx_msg void OnBnClickedBtnSetVoicePromption();
    afx_msg void OnBnClickedBtnCtrlEmergenceAlarmRsp();
};
#pragma once


// CDlgAlarmOneKey 对话框

class CDlgAlarmOneKey : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAlarmOneKey)

public:
	CDlgAlarmOneKey(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAlarmOneKey();

// 对话框数据
	enum { IDD = IDD_DLG_ALARM_ONE_KEY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
