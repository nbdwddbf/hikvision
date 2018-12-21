#pragma once


// CDlgProductDH 对话框

class CDlgProductDH : public CDialog
{
	DECLARE_DYNAMIC(CDlgProductDH)

public:
	CDlgProductDH(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgProductDH();

// 对话框数据
	enum { IDD = IDD_SUBDIG_PRODUCT_DH };
    void UpdataParam();
    int     m_iDevIndex;
    LONG    m_lServerID;
    LONG    m_lStartChan;
    LONG    m_lChannel;
    BOOL	m_bInit;
    float m_fBatteryVoltage;
    NET_DVR_ALARMHOST_ABILITY   m_struAlarmHostAbility;
    BOOL GetAlarmHostAbility(NET_DVR_ALARMHOST_ABILITY& struAlarmHostAbility);
    BOOL GetBatteryVoltage();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
 
    afx_msg void OnBnClickedBtnHistoryData();
    afx_msg void OnBnClickedBtnPointCfg();
    afx_msg void OnBnClickedBtnSensorLinkage();
    afx_msg void OnBnClickedBtnScaleOutCfg();
    afx_msg void OnBnClickedBtnUploadMode();
    afx_msg void OnBnClickedBtnRs485Cfg();
    afx_msg void OnBnClickedBtnExternalDeviceState();
    afx_msg void OnBnClickedButNetalarmAlarmLogSearch();
    afx_msg void OnBnClickedBtnSensorCfg();
    afx_msg void OnBnClickedBtnExternalDeviceLimitValue();
    afx_msg void OnBtnGetAllPoint();
    afx_msg void OnBtnGetAllSensor();
    afx_msg void OnBtnGetAllRs485Cfg();
    afx_msg void OnBtnGetAllRs485SlotCfg();
    afx_msg void OnBtnGetDeviceState();
    afx_msg void OnBnClickedBtnGetAllPoint();
    afx_msg void OnBnClickedBtnGetAllSensor();
    afx_msg void OnBnClickedBtnGetAllRs485Cfg();
    afx_msg void OnBnClickedBtnGetAllRs485SlotCfg();
    afx_msg void OnBnClickedBtnGetDeviceState();
    afx_msg void OnBnClickedBtnRs485Version();
    afx_msg void OnBnClickedBtnZoneCfg();
    afx_msg void OnBnClickedBtnOutputCfg();
    afx_msg void OnBnClickedBtnEnableCfg();
    afx_msg void OnBnClickedBtnAbilityGet();
    afx_msg void OnBnClickedBtnNetuserCfg();
    afx_msg void OnBnClickedBtnKeypaduserCfg();
    afx_msg void OnBnClickedBtnStatusCheck();
    afx_msg void OnBnClickedBtnVoltageCheck();
    afx_msg void OnBnClickedBtnRs485DllCfg();
};
