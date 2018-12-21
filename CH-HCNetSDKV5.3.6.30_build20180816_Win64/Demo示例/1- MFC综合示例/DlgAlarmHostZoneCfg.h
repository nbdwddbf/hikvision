#pragma once


// CDlgAlarmHostZoneCfg 对话框

class CDlgAlarmHostZoneCfg : public CDialog
{
	DECLARE_DYNAMIC(CDlgAlarmHostZoneCfg)

public:
	CDlgAlarmHostZoneCfg(CWnd* pParent = NULL);   // 标准构造函数
    CComboBox	m_cmbZoneResistor;
    CComboBox	m_cmSensitivity;
    CComboBox	m_comboCopyTime;
    CComboBox	m_comboWeekday;
    CListCtrl	m_listSirenOut;
    CComboBox	m_comboDetector;
    CComboBox	m_comboDefenseType;
    CListCtrl	m_listAlarmIn;
    CListCtrl	m_listAlarmOut;
    CComboBox	m_comboAlarmIn;
    CString	m_csAlarmInName;
    CString m_csVoiceFileName;
    int		m_iDelayTime;
    int     m_iTimeOut;
    int		m_iHour11;
    int		m_iHour12;
    int		m_iHour21;
    int		m_iHour22;
    int		m_iMin11;
    int		m_iMin12;
    int		m_iMin21;
    int		m_iMin22;
    int		m_iMin31;
    int		m_iMin32;
    int		m_iMin41;
    int		m_iMin42;
    int		m_iHour31;
    int		m_iHour32;
    int		m_iHour41;
    int		m_iHour42;
    BOOL	m_bGroupBypass;
    BOOL	m_chUploadReport;
    int		m_iInDelay;
    int		m_iOutDelay;
    float	m_fZoneResistorManual;
    BOOL    m_bLampOut[8];
	virtual ~CDlgAlarmHostZoneCfg();

// 对话框数据
	enum { IDD = IDD_DIG_ALARMHOST_ZONE_CFG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();
    afx_msg void OnBtnSetAlarmInParam();
    afx_msg void OnSelchangeComboAlarmIn();
    afx_msg void OnBtnSetAlarmChan();
    afx_msg void OnBtnCloseAlarmChan();
    afx_msg void OnBtnBypass();
    afx_msg void OnBtnUnBypass();
    afx_msg void OnRclickListAlarmOut(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnMenuSelectAll();
    afx_msg void OnMenuCancelAll();
    afx_msg void OnTimeOk();
    afx_msg void OnTimeCopy();
    afx_msg void OnSelchangeComboweekday();
    afx_msg void OnSelchangeCombocopytime();
    afx_msg void OnSelchangeComboDefenseType();
    afx_msg void OnSelchangeCmbZoneResistor();

	DECLARE_MESSAGE_MAP()
public:
    int     m_iDevIndex;
    LONG    m_lServerID;
    LONG    m_lStartChan;
    LONG    m_lChannel;
    char    m_szLan[128];
    BOOL	m_bInit;

    NET_DVR_ALARMHOST_ABILITY   m_struAlarmHostAbility;
    NET_DVR_ALARMIN_PARAM_V50       m_struAlarmInParam;
    NET_DVR_ALARMIN_SETUP       m_struAlarmInSetup;

    float m_fBatteryVoltage;
public:
    void InitWnd();
    void InitAlarmInCombo();
    void InitAlarmOutList();
    void InitAlarmInList();
    void InitSirenOutList();
    //    void InitAlarmOutCombo();
    void InitAlarmInDetectorCombo();
    void IninAlarmInDefenseTypeCombo();
    void InitWeekdayCombo();
    void InitSensitivityCombo();
    void InitZoneSignalTypeCombo();

    BOOL GetAlarmHostAbility(NET_DVR_ALARMHOST_ABILITY& struAlarmHostAbility);
    BOOL SetAlarmInParam(NET_DVR_ALARMIN_PARAM_V50& struAlarmInParam);
    BOOL GetAlarmInParam(NET_DVR_ALARMIN_PARAM_V50& struAlarmInParam);
    BOOL AlarmHostSetAlarmChan(NET_DVR_ALARMIN_SETUP &struAlarmInSetup);
    BOOL AlarmHostCloseAlarmChan(NET_DVR_ALARMIN_SETUP &struAlarmInSetup);
    BOOL BypassAlarmChan(NET_DVR_ALARMIN_SETUP &struAlarmInSetup);
    BOOL UnBypassAlarmChan(NET_DVR_ALARMIN_SETUP &struAlarmInSetup);

    void SetAlarmInParamToWnd(NET_DVR_ALARMIN_PARAM_V50& struAlarmInParam);
    void GetAlarmInParamFromWnd(NET_DVR_ALARMIN_PARAM_V50& struAlarmInParam);
    void GetAlarmInSetupFromWnd(NET_DVR_ALARMIN_SETUP &struAlarmInSetup);
    BOOL F_TimeTest();
    void SetAlarmTimeToWnd(NET_DVR_SCHEDTIME const *pAlarmTime, int nDay);
    void GetAlarmTimeFromWnd(NET_DVR_SCHEDTIME *pAlarmTime, int nDay);
    void UpdatePapam(); 

    CString m_csDetectorSerialNo;
    CComboBox m_cmbZoneSignalType;
    BOOL m_bChkEnableDetetorTypeCfg;
    CComboBox m_cmbTimeOutRange;
    CComboBox	m_cmbAlarmType;
    int  m_iDetectorSignalIntensity;
    CComboBox m_cmbTimeOutMethod;
};

