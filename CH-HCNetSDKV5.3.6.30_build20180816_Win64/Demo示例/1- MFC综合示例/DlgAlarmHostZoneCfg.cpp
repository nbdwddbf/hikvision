// DlgAlarmHostZoneCfg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgAlarmHostZoneCfg.h"
#include "afxdialogex.h"


// CDlgAlarmHostZoneCfg 对话框

IMPLEMENT_DYNAMIC(CDlgAlarmHostZoneCfg, CDialog)

CDlgAlarmHostZoneCfg::CDlgAlarmHostZoneCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmHostZoneCfg::IDD, pParent)
    , m_csDetectorSerialNo(_T(""))
    , m_bChkEnableDetetorTypeCfg(FALSE)
{
    m_csAlarmInName = _T("");
    m_csVoiceFileName = _T("");
    m_iDelayTime = 0;
    m_iHour11 = 0;
    m_iHour12 = 0;
    m_iHour21 = 0;
    m_iHour22 = 0;
    m_iMin11 = 0;
    m_iMin12 = 0;
    m_iMin21 = 0;
    m_iMin22 = 0;
    m_iMin31 = 0;
    m_iMin32 = 0;
    m_iMin41 = 0;
    m_iMin42 = 0;
    m_iHour31 = 0;
    m_iHour32 = 0;
    m_iHour41 = 0;
    m_iHour42 = 0;
    m_bGroupBypass = FALSE;
    m_chUploadReport = FALSE;
    m_iInDelay = 0;
    m_iOutDelay = 0;
    m_iTimeOut = 0;
    m_fZoneResistorManual = 0.0f;
    m_iDetectorSignalIntensity = 0;
    //}}AFX_DATA_INIT
    m_iDevIndex = -1;
    m_lServerID = -1;
    m_lStartChan = -1;
    m_lChannel = -1;
    memset(&m_struAlarmHostAbility, 0, sizeof(m_struAlarmHostAbility));
    memset(&m_struAlarmInParam, 0, sizeof(m_struAlarmInParam));
    memset(&m_struAlarmInSetup, 0, sizeof(m_struAlarmInSetup));
    m_fBatteryVoltage = 0;
    m_bInit = FALSE;
    for (int i = 0; i < 8; i++)
    {
        m_bLampOut[i] = FALSE;
    }
}

CDlgAlarmHostZoneCfg::~CDlgAlarmHostZoneCfg()
{
}

void CDlgAlarmHostZoneCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_ALARM_SENSITIVITY, m_cmSensitivity);
    DDX_Control(pDX, IDC_COMBOCOPYTIME, m_comboCopyTime);
    DDX_Control(pDX, IDC_COMBOWEEKDAY, m_comboWeekday);
    DDX_Control(pDX, IDC_LIST_SIREN_OUT, m_listSirenOut);
    DDX_Control(pDX, IDC_COMBO_DETECTOR, m_comboDetector);
    DDX_Control(pDX, IDC_COMBO_DEFENSE_TYPE, m_comboDefenseType);
    DDX_Control(pDX, IDC_LIST_ALARM_IN, m_listAlarmIn);
    DDX_Control(pDX, IDC_LIST_ALARM_OUT, m_listAlarmOut);
    DDX_Control(pDX, IDC_COMBO_ALARM_IN, m_comboAlarmIn);
    DDX_Text(pDX, IDC_EDIT_ALARMIN_NAME, m_csAlarmInName);
    DDV_MaxChars(pDX, m_csAlarmInName, 32);
    DDX_Text(pDX, IDC_EDIT_VOICE_FILE_NAME, m_csVoiceFileName);
    DDV_MaxChars(pDX, m_csVoiceFileName, 32);
    DDX_Text(pDX, IDC_EDIT_TIME_OUT, m_iTimeOut);
    DDX_Text(pDX, IDC_EDIT_DELAY_TIME, m_iDelayTime);
    DDX_Text(pDX, IDC_EDITHOUR11, m_iHour11);
    DDX_Text(pDX, IDC_EDITHOUR12, m_iHour12);
    DDX_Text(pDX, IDC_EDITHOUR21, m_iHour21);
    DDX_Text(pDX, IDC_EDITHOUR22, m_iHour22);
    DDX_Text(pDX, IDC_EDITMIN11, m_iMin11);
    DDX_Text(pDX, IDC_EDITMIN12, m_iMin12);
    DDX_Text(pDX, IDC_EDITMIN21, m_iMin21);
    DDX_Text(pDX, IDC_EDITMIN22, m_iMin22);
    DDX_Text(pDX, IDC_EDITMIN31, m_iMin31);
    DDX_Text(pDX, IDC_EDITMIN32, m_iMin32);
    DDX_Text(pDX, IDC_EDITMIN41, m_iMin41);
    DDX_Text(pDX, IDC_EDITMIN42, m_iMin42);
    DDX_Text(pDX, IDC_EDITHOUR31, m_iHour31);
    DDX_Text(pDX, IDC_EDITHOUR32, m_iHour32);
    DDX_Text(pDX, IDC_EDITHOUR41, m_iHour41);
    DDX_Text(pDX, IDC_EDITHOUR42, m_iHour42);
    DDX_Check(pDX, IDC_CHECK_GROUPBYPASS, m_bGroupBypass);
    DDX_Check(pDX, IDC_CHECK_UPLOAD_ALARM_RECOVERY_REPORT, m_chUploadReport);
    DDX_Check(pDX, IDC_CHECK_LAMP1, m_bLampOut[0]);
    DDX_Check(pDX, IDC_CHECK_LAMP2, m_bLampOut[1]);
    DDX_Check(pDX, IDC_CHECK_LAMP3, m_bLampOut[2]);
    DDX_Check(pDX, IDC_CHECK_LAMP4, m_bLampOut[3]);
    DDX_Check(pDX, IDC_CHECK_LAMP5, m_bLampOut[4]);
    DDX_Check(pDX, IDC_CHECK_LAMP6, m_bLampOut[5]);
    DDX_Check(pDX, IDC_CHECK_LAMP7, m_bLampOut[6]);
    DDX_Check(pDX, IDC_CHECK_LAMP8, m_bLampOut[7]);
    DDX_Text(pDX, IDC_EDIT_IN_DELAY, m_iInDelay);
    DDX_Text(pDX, IDC_EDIT_OUT_DELAY, m_iOutDelay);
    DDX_Control(pDX, IDC_CMB_ZONE_RESISTOR, m_cmbZoneResistor);
    DDX_Text(pDX, IDC_EDIT_ZONE_RESISTOR_MANUAL, m_fZoneResistorManual);
    DDX_Text(pDX, IDC_EDIT_ASSOCIATED_DETECTOR, m_csDetectorSerialNo);
    DDX_Control(pDX, IDC_CMB_ZONE_SIGNAL_TYPE, m_cmbZoneSignalType);
    DDX_Check(pDX, IDC_CHK_ENABLE_CFG_DETECTOR_TYPE, m_bChkEnableDetetorTypeCfg);
    DDX_Control(pDX, IDC_COMBO_TIMEOUT_RANGE, m_cmbTimeOutRange);
    DDX_Control(pDX, IDC_CMB_ALARM_TYPE, m_cmbAlarmType);
    DDX_Text(pDX, IDC_EDIT_SIGNAL_INTESITY, m_iDetectorSignalIntensity);
    DDX_Control(pDX, IDC_CMB_ALARM_TYPE2, m_cmbTimeOutMethod);
}


BEGIN_MESSAGE_MAP(CDlgAlarmHostZoneCfg, CDialog)
    ON_BN_CLICKED(IDC_BTN_SET_ALARMIN_PARAM, OnBtnSetAlarmInParam)
    ON_CBN_SELCHANGE(IDC_COMBO_ALARM_IN, OnSelchangeComboAlarmIn)
    ON_BN_CLICKED(IDC_BTN_SET_ALARM_CHAN, OnBtnSetAlarmChan)
    ON_BN_CLICKED(IDC_BTN_CLOSE_ALARM_CHAN, OnBtnCloseAlarmChan)
    ON_BN_CLICKED(IDC_BTN_BYPASS, OnBtnBypass)
    ON_BN_CLICKED(IDC_BTN_UN_BYPASS, OnBtnUnBypass)
    ON_NOTIFY(NM_RCLICK, IDC_LIST_ALARM_OUT, OnRclickListAlarmOut)
    ON_COMMAND(ID_MENU_SELECT_ALL, OnMenuSelectAll)
    ON_COMMAND(ID_MENU_CANCEL_ALL, OnMenuCancelAll)
    ON_BN_CLICKED(IDC_TIME_OK, OnTimeOk)
    ON_BN_CLICKED(IDC_TIME_COPY, OnTimeCopy)
    ON_CBN_SELCHANGE(IDC_COMBOWEEKDAY, OnSelchangeComboweekday)
    ON_CBN_SELCHANGE(IDC_COMBOCOPYTIME, OnSelchangeCombocopytime)
    ON_CBN_SELCHANGE(IDC_COMBO_DEFENSE_TYPE, OnSelchangeComboDefenseType)
    ON_CBN_SELCHANGE(IDC_CMB_ZONE_RESISTOR, OnSelchangeCmbZoneResistor)
END_MESSAGE_MAP()


// CDlgAlarmHostZoneCfg 消息处理程序
// DlgProductAlarmHostCfg.cpp : implementation file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostZoneCfg message handlers

BOOL CDlgAlarmHostZoneCfg::OnInitDialog()
{
    CDialog::OnInitDialog();

    //     m_comboAlarmOut.SetCurSel(0);
    //     OnSelchangeComboAlarmOut();
    UpdatePapam();
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlarmHostZoneCfg::InitWnd()
{
    InitAlarmInCombo();
    InitAlarmOutList();
    InitAlarmInList();
    InitSirenOutList();
    //    InitAlarmOutCombo();
    InitAlarmInDetectorCombo();
    IninAlarmInDefenseTypeCombo();
    InitWeekdayCombo();
    InitSensitivityCombo();
    InitZoneSignalTypeCombo();
}

void CDlgAlarmHostZoneCfg::InitAlarmInCombo()
{
    char szLan[128] = { 0 };
    m_comboAlarmIn.ResetContent();
    int i = 0;
    for (i = 0; i < (m_struAlarmHostAbility.wTotalAlarmInNum); i++)
    {
        sprintf(szLan, "Alarm In %d", i + 1);
        m_comboAlarmIn.InsertString(i, szLan);
        m_comboAlarmIn.SetItemData(i, i);
    }

    if (i > 0)
    {
        m_comboAlarmIn.SetCurSel(0);
    }
}

void CDlgAlarmHostZoneCfg::InitWeekdayCombo()
{
    char szLan[128] = { 0 };
    g_StringLanType(szLan, "整个星期", "Whole Week");
    m_comboCopyTime.AddString(szLan);

    g_StringLanType(szLan, "星期一", "Monday");
    m_comboWeekday.AddString(szLan);
    m_comboCopyTime.AddString(szLan);
    g_StringLanType(szLan, "星期二", "Tuesday");
    m_comboWeekday.AddString(szLan);
    m_comboCopyTime.AddString(szLan);
    g_StringLanType(szLan, "星期三", "Wednesday");
    m_comboWeekday.AddString(szLan);
    m_comboCopyTime.AddString(szLan);
    g_StringLanType(szLan, "星期四", "Thursday");
    m_comboWeekday.AddString(szLan);
    m_comboCopyTime.AddString(szLan);
    g_StringLanType(szLan, "星期五", "Friday");
    m_comboWeekday.AddString(szLan);
    m_comboCopyTime.AddString(szLan);
    g_StringLanType(szLan, "星期六", "Saturday");
    m_comboWeekday.AddString(szLan);
    m_comboCopyTime.AddString(szLan);
    g_StringLanType(szLan, "星期天", "Sunday");
    m_comboWeekday.AddString(szLan);
    m_comboCopyTime.AddString(szLan);
}

void CDlgAlarmHostZoneCfg::InitZoneSignalTypeCombo()
{
    char szLan[128] = { 0 };
    g_StringLanType(szLan, "有线防区", "Cable Zone");
    m_cmbZoneSignalType.AddString(szLan);

    g_StringLanType(szLan, "无线防区", "Wireless Zone");
    m_cmbZoneSignalType.AddString(szLan);
}

void CDlgAlarmHostZoneCfg::InitSensitivityCombo()
{
    m_cmSensitivity.ResetContent();
    m_cmSensitivity.AddString("10ms");
    m_cmSensitivity.AddString("250ms");
    m_cmSensitivity.AddString("500ms");
    m_cmSensitivity.AddString("750ms");
}

void CDlgAlarmHostZoneCfg::InitAlarmOutList()
{
    char szLan[128] = { 0 };

    m_listAlarmOut.SetExtendedStyle(LVS_EX_CHECKBOXES);
    for (int i = 0; i < (m_struAlarmHostAbility.wLocalAlarmOutNum + m_struAlarmHostAbility.wExpandAlarmOutNum); i++)
    {
        sprintf(szLan, "Alarm Out %d", (i + 1));
        m_listAlarmOut.InsertItem(i, szLan);
    }
}

void CDlgAlarmHostZoneCfg::InitAlarmInList()
{
    char szLan[128] = { 0 };

    m_listAlarmIn.SetExtendedStyle(LVS_EX_CHECKBOXES);
    for (int i = 0; i < (m_struAlarmHostAbility.wLocalAlarmInNum + m_struAlarmHostAbility.wExpandAlarmInNum); i++)
    {
        sprintf(szLan, "Alarm In %d", (i + 1));
        m_listAlarmIn.InsertItem(i, szLan);
    }
}

void CDlgAlarmHostZoneCfg::InitSirenOutList()
{
    char szLan[128] = { 0 };
    m_listSirenOut.SetExtendedStyle(LVS_EX_CHECKBOXES);
    for (int i = 0; i < m_struAlarmHostAbility.wSirenNum; i++)
    {
        sprintf(szLan, "Siren %d", (i + 1));
        m_listSirenOut.InsertItem(i, szLan);
    }
}

void CDlgAlarmHostZoneCfg::InitAlarmInDetectorCombo()
{
    char szLan[128] = { 0 };
    m_comboDetector.ResetContent();
    int nIndex = 0;

    g_StringLanType(szLan, "紧急开关", "Panic Button");
    m_comboDetector.InsertString(nIndex, szLan);
    m_comboDetector.SetItemData(nIndex, PANIC_BUTTON);
    nIndex++;

    g_StringLanType(szLan, "门磁开关", "Magnetic Contact");
    m_comboDetector.InsertString(nIndex, szLan);
    m_comboDetector.SetItemData(nIndex, MAGNETIC_CONTACT);
    nIndex++;

    g_StringLanType(szLan, "烟感探测器", "Smoke Detector");
    m_comboDetector.InsertString(nIndex, szLan);
    m_comboDetector.SetItemData(nIndex, SMOKE_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "主动红外探测器", "Active Infrared Detector");
    m_comboDetector.InsertString(nIndex, szLan);
    m_comboDetector.SetItemData(nIndex, ACTIVE_INFRARED_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "被动红外探测器", "Passive Infrared Detector");
    m_comboDetector.InsertString(nIndex, szLan);
    m_comboDetector.SetItemData(nIndex, PASSIVE_INFRARED_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "玻璃破碎探测器", "Glass Break Detector");
    m_comboDetector.InsertString(nIndex, szLan);
    m_comboDetector.SetItemData(nIndex, GLASS_BREAK_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "震动探测器", "Vibration detector");
    m_comboDetector.InsertString(nIndex, szLan);
    m_comboDetector.SetItemData(nIndex, VIBRATION_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "双鉴移动探测器", "Dual Technology PIR detector");
    m_comboDetector.InsertString(nIndex, szLan);
    m_comboDetector.SetItemData(nIndex, DUAL_TECHNOLOGY_PIR_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "三技术探测器", "Triple Technology PIR detector");
    m_comboDetector.InsertString(nIndex, szLan);
    m_comboDetector.SetItemData(nIndex, TRIPLE_TECHNOLOGY_PIR_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "湿度探测器", "Humidity Dectector");
    m_comboDetector.InsertString(nIndex, szLan);
    m_comboDetector.SetItemData(nIndex, HUMIDITY_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "温感探测器", "Temperature Dectector");
    m_comboDetector.InsertString(nIndex, szLan);
    m_comboDetector.SetItemData(nIndex, TEMPERATURE_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "可燃气体探测器", "Combustible Gas Detector");
    m_comboDetector.InsertString(nIndex, szLan);
    m_comboDetector.SetItemData(nIndex, COMBUSTIBLE_GAS_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "随动开关", "dynamic switch");
    m_comboDetector.InsertString(nIndex, szLan);
    m_comboDetector.SetItemData(nIndex, DYNAMIC_SWITCH);
    nIndex++;

    g_StringLanType(szLan, "控制开关", "control switch");
    m_comboDetector.InsertString(nIndex, szLan);
    m_comboDetector.SetItemData(nIndex, CONTROL_SWITCH);
    nIndex++;

    g_StringLanType(szLan, "智能锁", "smart lock");
    m_comboDetector.InsertString(nIndex, szLan);
    m_comboDetector.SetItemData(nIndex, SMART_LOCK);
    nIndex++;

    g_StringLanType(szLan, "水感探测器", "water detector");
    m_comboDetector.InsertString(nIndex, szLan);
    m_comboDetector.SetItemData(nIndex, WATER_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "位移探测器", "displacement detector");
    m_comboDetector.InsertString(nIndex, szLan);
    m_comboDetector.SetItemData(nIndex, DISPLACEMENT_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "单体门磁探测器", "single infrared detector");
    m_comboDetector.InsertString(nIndex, szLan);
    m_comboDetector.SetItemData(nIndex, SINGLE_INFRARED_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "无线单防区模块", "wireless single zone module");
    m_comboDetector.InsertString(nIndex, szLan);
    m_comboDetector.SetItemData(nIndex, SINGLE_ZONE_MODULE);
    nIndex++;

    g_StringLanType(szLan, "幕帘红外人体探测器", "curtain infrared detector");
    m_comboDetector.InsertString(nIndex, szLan);
    m_comboDetector.SetItemData(nIndex, CURTAIN_INFRARED_DETECTOR);
    nIndex++;

    g_StringLanType(szLan, "门铃开关", "bell switch");
    m_comboDetector.InsertString(nIndex, szLan);
    m_comboDetector.SetItemData(nIndex, DOORBELL_SWITCH);
    nIndex++;

    g_StringLanType(szLan, "医疗求助按钮", "medical help");
    m_comboDetector.InsertString(nIndex, szLan);
    m_comboDetector.SetItemData(nIndex, MEDICAL_HELP_BUTTON);
    nIndex++;

    g_StringLanType(szLan, "室外双鉴传感器", "outdoor dual detector");
    m_comboDetector.InsertString(nIndex, szLan);
    m_comboDetector.SetItemData(nIndex, OUTDOOR_DUAL_TECH);
    nIndex++;

    g_StringLanType(szLan, "其他探测器", "Other Detector");
    m_comboDetector.InsertString(nIndex, szLan);
    m_comboDetector.SetItemData(nIndex, OTHER_DETECTOR);
    nIndex++;

}

void CDlgAlarmHostZoneCfg::IninAlarmInDefenseTypeCombo()
{
    char szLan[128] = { 0 };
    m_comboDefenseType.ResetContent();
    g_StringLanType(szLan, "即时防区", "Instant zone");
    m_comboDefenseType.AddString(szLan);
    g_StringLanType(szLan, "24小时有声防区", "24-hour zone");
    m_comboDefenseType.AddString(szLan);
    g_StringLanType(szLan, "延时防区", "Delay zone");
    m_comboDefenseType.AddString(szLan);
    g_StringLanType(szLan, "内部防区", "Inter zone");
    m_comboDefenseType.AddString(szLan);
    g_StringLanType(szLan, "钥匙布撤防防区", "Key zone");
    m_comboDefenseType.AddString(szLan);

    g_StringLanType(szLan, "火警防区", "Fire zone");
    m_comboDefenseType.AddString(szLan);
    g_StringLanType(szLan, "周界防区", "perimeter zone");
    m_comboDefenseType.AddString(szLan);
    g_StringLanType(szLan, "24小时无声防区", "24-hour silent zone");
    m_comboDefenseType.AddString(szLan);
    g_StringLanType(szLan, "24小时辅助防区", "24-hour auxiliary zone");
    m_comboDefenseType.AddString(szLan);
    g_StringLanType(szLan, "24小时震动防区", "24-hour vibration zone");
    m_comboDefenseType.AddString(szLan);
    g_StringLanType(szLan, "门禁紧急开门防区", "door emergency open protection zones");
    m_comboDefenseType.AddString(szLan);
    g_StringLanType(szLan, "门禁紧急关门防区", "door emergency shutdown protection zones");
    m_comboDefenseType.AddString(szLan);
    g_StringLanType(szLan, "超时防区", "time-out zone");
    m_comboDefenseType.AddString(szLan);
    g_StringLanType(szLan, "紧急防区", "emergency zone");
    m_comboDefenseType.AddString(szLan);
    g_StringLanType(szLan, "屏蔽防区", "shield zone");
    m_comboDefenseType.AddString(szLan);
}

BOOL CDlgAlarmHostZoneCfg::GetAlarmHostAbility(NET_DVR_ALARMHOST_ABILITY& struAlarmHostAbility)
{
    BOOL bRet = FALSE;
    DWORD dwReturn = 0;
    if (NET_DVR_GetDeviceAbility(m_lServerID, ALARMHOST_ABILITY, NULL, 0, (char*)&struAlarmHostAbility, sizeof(struAlarmHostAbility)))
    {
        char szLan[128] = { 0 };
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "ALARMHOST_ABILITY");
        bRet = TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "ALARMHOST_ABILITY");
        bRet = FALSE;
    }
    return bRet;
}

BOOL CDlgAlarmHostZoneCfg::SetAlarmInParam(NET_DVR_ALARMIN_PARAM_V50& struAlarmInParam)
{
    //     if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_AlarmInParamCFG, i + m_lStartChan + sel * 64, &m_struAlarmInParamCfg, sizeof(m_struAlarmInParamCfg)))
    BOOL bRet = FALSE;
    LONG lAlarmIn = m_comboAlarmIn.GetItemData(m_comboAlarmIn.GetCurSel());
    if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_ALARMIN_PARAM_V50, lAlarmIn, &struAlarmInParam, sizeof(struAlarmInParam)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_ALARMIN_PARAM_V50");
        bRet = TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_ALARMIN_PARAM_V50");
        bRet = FALSE;
    }

    return bRet;
}

BOOL CDlgAlarmHostZoneCfg::GetAlarmInParam(NET_DVR_ALARMIN_PARAM_V50& struAlarmInParam)
{
    BOOL bRet = FALSE;
    LONG lAlarmIn = m_comboAlarmIn.GetItemData(m_comboAlarmIn.GetCurSel());
    DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_ALARMIN_PARAM_V50, lAlarmIn, &struAlarmInParam, sizeof(struAlarmInParam), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARMIN_PARAM_V50");
        bRet = TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMIN_PARAM_V50");
        bRet = FALSE;
    }
    return bRet;
}

BOOL CDlgAlarmHostZoneCfg::AlarmHostSetAlarmChan(NET_DVR_ALARMIN_SETUP &struAlarmInSetup)
{
    BOOL bRet = FALSE;

    if (!NET_DVR_AlarmHostSetupAlarmChan(m_lServerID, &struAlarmInSetup))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_AlarmHostSetupAlarmChan");
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_AlarmHostSetupAlarmChan");
        bRet = TRUE;
    }
    return bRet;
}

BOOL CDlgAlarmHostZoneCfg::AlarmHostCloseAlarmChan(NET_DVR_ALARMIN_SETUP &struAlarmInSetup)
{
    BOOL bRet = FALSE;
    if (!NET_DVR_AlarmHostCloseAlarmChan(m_lServerID, &struAlarmInSetup))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_AlarmHostCloseAlarmChan");
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_AlarmHostCloseAlarmChan");
        bRet = TRUE;
    }
    return bRet;
}

// BOOL CDlgAlarmHostZoneCfg::SetAlarmOutTimeCfg(NET_DVR_ALARMOUTTIMECFG &struAlarmOutTime)
// {
// // #define NET_DVR_GET_ALARMOUTTIMECFG		1122 //获取报警输出/警号时间参数
// // #define NET_DVR_SET_ALARMOUTTIMECFG		1123//设置报警输出/警号时间参数
//     BOOL bRet = FALSE;
//     int lAlarmOut = m_comboAlarmOut.GetItemData(m_comboAlarmOut.GetCurSel());
//     if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_ALARMOUTTIMECFG, lAlarmOut, &struAlarmOutTime, sizeof(struAlarmOutTime)))
//     {
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_ALARMOUTTIMECFG");
//         bRet = FALSE;
//     }
//     else
//     {
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_ALARMOUTTIMECFG");
//         bRet = TRUE;
//     }   
//     return bRet;
// }
// 
// BOOL CDlgAlarmHostZoneCfg::GetAlarmOutTimeCfg(NET_DVR_ALARMOUTTIMECFG &struAlarmOutTime)
// {
//     BOOL bRet = FALSE;
//     int lAlarmOut = m_comboAlarmOut.GetItemData(m_comboAlarmOut.GetCurSel());
//     DWORD dwReturn = 0;
//     if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_ALARMOUTTIMECFG, lAlarmOut, &struAlarmOutTime, sizeof(struAlarmOutTime), &dwReturn))
//     {
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMOUTTIMECFG");
//         bRet = FALSE;
//     }
//     else
//     {
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARMOUTTIMECFG");
//         bRet = TRUE;
//     }   
//     return bRet;
// }
// 
void CDlgAlarmHostZoneCfg::SetAlarmInParamToWnd(NET_DVR_ALARMIN_PARAM_V50& struAlarmInParam)
{
    int i = 0;
    for (i = 0; i < m_listAlarmOut.GetItemCount(); i++)
    {
        if (1 == struAlarmInParam.byAssociateAlarmOut[i])
        {
            m_listAlarmOut.SetCheck(i, TRUE);
        }
        else
        {
            m_listAlarmOut.SetCheck(i, FALSE);
        }
    }

    for (i = 0; i < m_listSirenOut.GetItemCount(); i++)
    {
        if (1 == struAlarmInParam.byAssociateSirenOut[i])
        {
            m_listSirenOut.SetCheck(i, TRUE);
        }
        else
        {
            m_listSirenOut.SetCheck(i, FALSE);
        }
    }
    char szLan[40] = { 0 };
    strncpy(szLan, (char*)struAlarmInParam.byName, sizeof(struAlarmInParam.byName));
    m_csAlarmInName.Format("%s", szLan);
    for (i = 0; i < m_comboDetector.GetCount(); i++)
    {
        if (m_comboDetector.GetItemData(i) == struAlarmInParam.wDetectorType)
        {
            m_comboDetector.SetCurSel(i);
            break;
        }
    }
    if (struAlarmInParam.byType == 0xff)
    {
        m_comboDefenseType.SetCurSel(m_comboDefenseType.GetCount() - 1);
    }
    else
    {
        m_comboDefenseType.SetCurSel(struAlarmInParam.byType);
    }
    m_comboDefenseType.SetCurSel(struAlarmInParam.byType);
    OnSelchangeComboDefenseType();
    m_iDelayTime = struAlarmInParam.dwParam;
    m_comboWeekday.SetCurSel(0);
    OnSelchangeComboweekday();
    m_cmSensitivity.SetCurSel(struAlarmInParam.bySensitivityParam);
    m_bGroupBypass = struAlarmInParam.byArrayBypass;
    m_chUploadReport = struAlarmInParam.byUploadAlarmRecoveryReport;
    m_iInDelay = (int)struAlarmInParam.wInDelay;
    m_iOutDelay = (int)struAlarmInParam.wOutDelay;
    m_iTimeOut = (int)struAlarmInParam.wTimeOut;
    m_cmbAlarmType.SetCurSel(struAlarmInParam.byAlarmType);
    if (struAlarmInParam.byZoneResistor == 0xff)
    {
        m_fZoneResistorManual = struAlarmInParam.fZoneResistorManual;
        m_cmbZoneResistor.SetCurSel(6);
    }
    else
    {
        m_cmbZoneResistor.SetCurSel(struAlarmInParam.byZoneResistor);
    }
    OnSelchangeCmbZoneResistor();

    char szTemp[20] = { 0 };
    strncpy(szTemp, (char*)struAlarmInParam.byDetectorSerialNo, sizeof(struAlarmInParam.byDetectorSerialNo));
    m_csDetectorSerialNo.Format("%s", szTemp);

    m_cmbZoneSignalType.SetCurSel(struAlarmInParam.byZoneSignalType);

    m_bChkEnableDetetorTypeCfg = struAlarmInParam.byDisableDetectorTypeCfg;
    for (int i = 0; i < 8; i++)
    {
        if (struAlarmInParam.byAssociateLampOut[i] == 1)
        {
            m_bLampOut[i] = TRUE;
        }
        else
        {
            m_bLampOut[i] = FALSE;
        }
    }
    char szTempLan[40] = { 0 };
    strncpy(szTempLan, (char*)struAlarmInParam.byVoiceFileName, sizeof(struAlarmInParam.byVoiceFileName));
    m_csVoiceFileName.Format("%s", szTempLan);
    m_cmbTimeOutRange.SetCurSel(struAlarmInParam.byTimeOutRange);
    m_iDetectorSignalIntensity = struAlarmInParam.byDetectorSignalIntensity;
    m_cmbTimeOutMethod.SetCurSel(struAlarmInParam.byTimeOutMethod);
    UpdateData(FALSE);
}

void CDlgAlarmHostZoneCfg::GetAlarmInParamFromWnd(NET_DVR_ALARMIN_PARAM_V50& struAlarmInParam)
{
    int i = 0;
    for (i = 0; i < m_listAlarmOut.GetItemCount(); i++)
    {
        if (TRUE == m_listAlarmOut.GetCheck(i))
        {
            struAlarmInParam.byAssociateAlarmOut[i] = 1;
        }
        else
        {
            struAlarmInParam.byAssociateAlarmOut[i] = 0;
        }
    }

    for (i = 0; i < m_listSirenOut.GetItemCount(); i++)
    {
        if (TRUE == m_listSirenOut.GetCheck(i))
        {
            struAlarmInParam.byAssociateSirenOut[i] = 1;
        }
        else
        {
            struAlarmInParam.byAssociateSirenOut[i] = 0;
        }
    }
    strncpy((char*)struAlarmInParam.byName, m_csAlarmInName.GetBuffer(0), sizeof(struAlarmInParam.byName));
    struAlarmInParam.wDetectorType = m_comboDetector.GetItemData(m_comboDetector.GetCurSel());
    struAlarmInParam.byType = (m_comboDefenseType.GetCurSel()>13) ? 0xff : m_comboDefenseType.GetCurSel();
    struAlarmInParam.dwParam = m_iDelayTime;
    GetAlarmTimeFromWnd(&struAlarmInParam.struAlarmTime[0][0], m_comboWeekday.GetCurSel());

    struAlarmInParam.byArrayBypass = m_bGroupBypass;
    struAlarmInParam.bySensitivityParam = m_cmSensitivity.GetCurSel();
    struAlarmInParam.byUploadAlarmRecoveryReport = m_chUploadReport;
    struAlarmInParam.byAlarmType = m_cmbAlarmType.GetCurSel();
    struAlarmInParam.wInDelay = (WORD)m_iInDelay;
    struAlarmInParam.wOutDelay = (WORD)m_iOutDelay;
    struAlarmInParam.wTimeOut = (WORD)m_iTimeOut;
    struAlarmInParam.byDetectorSignalIntensity = m_iDetectorSignalIntensity;
    struAlarmInParam.byTimeOutMethod = m_cmbTimeOutMethod.GetCurSel();
    if (m_cmbZoneResistor.GetCurSel() == 6)
    {
        struAlarmInParam.fZoneResistorManual = m_fZoneResistorManual;
        struAlarmInParam.byZoneResistor = 0xff;
    }
    else
    {
        struAlarmInParam.byZoneResistor = m_cmbZoneResistor.GetCurSel();
    }

    strncpy((char*)struAlarmInParam.byDetectorSerialNo, m_csDetectorSerialNo.GetBuffer(0), sizeof(struAlarmInParam.byDetectorSerialNo));

    struAlarmInParam.byZoneSignalType = m_cmbZoneSignalType.GetCurSel();

    struAlarmInParam.byDisableDetectorTypeCfg = m_bChkEnableDetetorTypeCfg;
    for (int i = 0; i < 8; i++)
    {
        if (m_bLampOut[i] == TRUE)
        {
            struAlarmInParam.byAssociateLampOut[i] = 1;
        }
        else
        {
            struAlarmInParam.byAssociateLampOut[i] = 0;
        }
    }
    strncpy((char*)struAlarmInParam.byVoiceFileName, m_csVoiceFileName.GetBuffer(0), sizeof(struAlarmInParam.byVoiceFileName));
    struAlarmInParam.byTimeOutRange = m_cmbTimeOutRange.GetCurSel();
}

void CDlgAlarmHostZoneCfg::GetAlarmInSetupFromWnd(NET_DVR_ALARMIN_SETUP &struAlarmInSetup)
{
    for (int i = 0; i < m_listAlarmIn.GetItemCount(); i++)
    {
        if (TRUE == m_listAlarmIn.GetCheck(i))
        {
            struAlarmInSetup.byAssiciateAlarmIn[i] = 1;
        }
        else
        {
            struAlarmInSetup.byAssiciateAlarmIn[i] = 0;
        }
    }
}

void CDlgAlarmHostZoneCfg::OnBtnSetAlarmInParam()
{
    UpdateData(TRUE);
    GetAlarmInParamFromWnd(m_struAlarmInParam);
    if (!SetAlarmInParam(m_struAlarmInParam))
    {
        AfxMessageBox("Fail to set Alarm in associate");
    }
}

void CDlgAlarmHostZoneCfg::OnSelchangeComboAlarmIn()
{
    GetAlarmInParam(m_struAlarmInParam);
    SetAlarmInParamToWnd(m_struAlarmInParam);
    UpdateData(FALSE);
}


void CDlgAlarmHostZoneCfg::OnBtnSetAlarmChan()
{
    GetAlarmInSetupFromWnd(m_struAlarmInSetup);
    if (!AlarmHostSetAlarmChan(m_struAlarmInSetup))
    {
        AfxMessageBox("Fail to set alarm chan");
    }
}

void CDlgAlarmHostZoneCfg::OnBtnCloseAlarmChan()
{
    GetAlarmInSetupFromWnd(m_struAlarmInSetup);
    if (!AlarmHostCloseAlarmChan(m_struAlarmInSetup))
    {
        AfxMessageBox("Fail to clost alarm chan");
    }
}

// void CDlgAlarmHostZoneCfg::OnBtnSetAlarmoutTime() 
// {
// /*    UpdateData(TRUE);*/
// //     m_struAlarmOutTimeCfg.wAlarmOutTime = m_iAlarmOutTime;
// //     SetAlarmOutTimeCfg(m_struAlarmOutTimeCfg);
// }


// void CDlgAlarmHostZoneCfg::OnSelchangeComboAlarmOut() 
// {
// //     GetAlarmOutTimeCfg(m_struAlarmOutTimeCfg);
// //     m_iAlarmOutTime = (int)m_struAlarmOutTimeCfg.wAlarmOutTime;   
// //     UpdateData(FALSE);
// }

// void CDlgAlarmHostZoneCfg::OnBtnOpenAlarmout() 
// {   
//     LONG lAlarmOutPort = m_comboAlarmOut.GetItemData(m_comboAlarmOut.GetCurSel());
//     if (!NET_DVR_SetAlarmOut(m_lServerID, lAlarmOutPort, 1))
//     {
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SetAlarmOut");
//         AfxMessageBox("Fail to set alarm out");
//     }
//     else
//     {
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SetAlarmOut");
//     }
// }

// void CDlgAlarmHostZoneCfg::OnBtnCloseAlarmout() 
// {
//     LONG lAlarmOutPort = m_comboAlarmOut.GetItemData(m_comboAlarmOut.GetCurSel());
//     if (!NET_DVR_SetAlarmOut(m_lServerID, lAlarmOutPort, 0))
//     {
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SetAlarmOut");
//         AfxMessageBox("Fail to set alarm out");
//     }
//     else
//     {
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SetAlarmOut");
//     }
// }

BOOL CDlgAlarmHostZoneCfg::BypassAlarmChan(NET_DVR_ALARMIN_SETUP &struAlarmInSetup)
{
    if (NET_DVR_BypassAlarmChan(m_lServerID, &struAlarmInSetup))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_BypassAlarmChan");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_BypassAlarmChan");
        return FALSE;
    }
}

BOOL CDlgAlarmHostZoneCfg::UnBypassAlarmChan(NET_DVR_ALARMIN_SETUP &struAlarmInSetup)
{
    if (NET_DVR_UnBypassAlarmChan(m_lServerID, &struAlarmInSetup))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_UnBypassAlarmChan");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_UnBypassAlarmChan");
        return FALSE;
    }
}

void CDlgAlarmHostZoneCfg::OnBtnBypass()
{
    GetAlarmInSetupFromWnd(m_struAlarmInSetup);
    if (!BypassAlarmChan(m_struAlarmInSetup))
    {
        AfxMessageBox("Fail to bypass alarm chan");
    }

}

void CDlgAlarmHostZoneCfg::OnBtnUnBypass()
{
    GetAlarmInSetupFromWnd(m_struAlarmInSetup);
    if (!UnBypassAlarmChan(m_struAlarmInSetup))
    {
        AfxMessageBox("Fail to  Unbypass alarm chan");
    }
}

void CDlgAlarmHostZoneCfg::OnRclickListAlarmOut(NMHDR* pNMHDR, LRESULT* pResult)
{
    CMenu pMenu;

    if (!pMenu.LoadMenu(IDR_MENU_SELECT_MODE))
    {
        return;
    }
    CPoint point;
    GetCursorPos(&point);
    pMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
    *pResult = 0;
}

void CDlgAlarmHostZoneCfg::OnMenuSelectAll()
{
    for (int i = 0; i < m_listAlarmOut.GetItemCount(); i++)
    {
        m_listAlarmOut.SetCheck(i, TRUE);
    }
}

void CDlgAlarmHostZoneCfg::OnMenuCancelAll()
{
    for (int i = 0; i < m_listAlarmOut.GetItemCount(); i++)
    {
        m_listAlarmOut.SetCheck(i, FALSE);
    }

}

void CDlgAlarmHostZoneCfg::OnTimeOk()
{
    UpdateData(TRUE);
    //     if (!F_TimeTest())
    //     {
    //         return;
    //     }
    int	i = m_comboWeekday.GetCurSel();
    GetAlarmTimeFromWnd(&m_struAlarmInParam.struAlarmTime[0][0], i);
}

void CDlgAlarmHostZoneCfg::OnTimeCopy()
{
    UpdateData(TRUE);
    int j, k;
    int i = m_comboWeekday.GetCurSel();
    int nCopyTime = m_comboCopyTime.GetCurSel() - 1;

    if (nCopyTime == -1)
    {
        for (j = 0; j < MAX_DAYS; j++)
        {
            if (j == i)
                continue;
            for (k = 0; k < MAX_TIMESEGMENT; k++)
            {
                memcpy(&(m_struAlarmInParam.struAlarmTime[j][k]), &(m_struAlarmInParam.struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
            }
        }
    }
    else
    {
        for (k = 0; k < MAX_TIMESEGMENT; k++)
        {
            memcpy(&(m_struAlarmInParam.struAlarmTime[nCopyTime][k]), &(m_struAlarmInParam.struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
        }
    }
}

BOOL CDlgAlarmHostZoneCfg::F_TimeTest()
{
    int i, j;
    WORD wStartTime[4], wStopTime[4];

    UpdateData(TRUE);
    if ((m_iHour11 < 0) || (m_iHour11 > 24) || (m_iHour12 < 0) || (m_iHour12 > 24) || \
        (m_iHour21 < 0) || (m_iHour21 > 24) || (m_iHour22 < 0) || (m_iHour22 > 24))
    {
        AfxMessageBox("Hours range 0 - 24 !");
        return FALSE;
    }
    if ((m_iMin11 < 0) || (m_iMin11 > 60) || (m_iMin12 < 0) || (m_iMin12 > 60) || \
        (m_iMin21 < 0) || (m_iMin21 > 60) || (m_iMin22 < 0) || (m_iMin22 > 60))
    {
        AfxMessageBox("Minute range 0 - 60!");
        return FALSE;
    }
    wStartTime[0] = (WORD)(m_iHour11 * 100 + m_iMin11);
    wStartTime[1] = (WORD)(m_iHour21 * 100 + m_iMin21);
    wStopTime[0] = (WORD)(m_iHour12 * 100 + m_iMin12);
    wStopTime[1] = (WORD)(m_iHour22 * 100 + m_iMin22);
    for (i = 0; i < MAX_TIMESEGMENT; i++)
    {
        if ((wStartTime[i] > 2400) || (wStopTime[i] > 2400))
        {
            char szLan[128] = { 0 };
            g_StringLanType(szLan, "布防时间不能超过24:00", "Fortify time can not be more than 24:00");
            AfxMessageBox(szLan);
            return FALSE;
        }
        if (wStartTime[i] > wStopTime[i])
        {
            char szLan[128] = { 0 };
            g_StringLanType(szLan, "布防起始时间不能大于停止时间", "Fortify start time can not be larger than the record to stop time");
            AfxMessageBox(szLan);
            return FALSE;
        }
        for (j = 0; j < MAX_TIMESEGMENT; j++)
        {
            if (i == j)
                continue;
            if ((wStartTime[i] > wStartTime[j]) && (wStartTime[i] < wStopTime[j]) || \
                (wStopTime[i] > wStartTime[j]) && (wStopTime[i] < wStopTime[j]))
            {
                char szLan[128] = { 0 };
                g_StringLanType(szLan, "布防时间段不能重复!", "Fortify time period can not be repeated!");
                AfxMessageBox(szLan);
                return FALSE;
            }
        }
    }
    return TRUE;
}

void CDlgAlarmHostZoneCfg::SetAlarmTimeToWnd(NET_DVR_SCHEDTIME const *pAlarmTime, int nDay)
{
    m_iHour11 = pAlarmTime[nDay * 4 + 0].byStartHour;
    m_iMin11 = pAlarmTime[nDay * 4 + 0].byStartMin;
    m_iHour12 = pAlarmTime[nDay * 4 + 0].byStopHour;
    m_iMin12 = pAlarmTime[nDay * 4 + 0].byStopMin;
    m_iHour21 = pAlarmTime[nDay * 4 + 1].byStartHour;
    m_iMin21 = pAlarmTime[nDay * 4 + 1].byStartMin;
    m_iHour22 = pAlarmTime[nDay * 4 + 1].byStopHour;
    m_iMin22 = pAlarmTime[nDay * 4 + 1].byStopMin;
    m_iHour31 = pAlarmTime[nDay * 4 + 2].byStartHour;
    m_iMin31 = pAlarmTime[nDay * 4 + 2].byStartMin;
    m_iHour32 = pAlarmTime[nDay * 4 + 2].byStopHour;
    m_iMin32 = pAlarmTime[nDay * 4 + 2].byStopMin;
    m_iHour41 = pAlarmTime[nDay * 4 + 3].byStartHour;
    m_iMin41 = pAlarmTime[nDay * 4 + 3].byStartMin;
    m_iHour42 = pAlarmTime[nDay * 4 + 3].byStopHour;
    m_iMin42 = pAlarmTime[nDay * 4 + 3].byStopMin;

}

void CDlgAlarmHostZoneCfg::GetAlarmTimeFromWnd(NET_DVR_SCHEDTIME *pAlarmTime, int nDay)
{
    pAlarmTime[nDay * 4 + 0].byStartHour = (BYTE)m_iHour11;
    pAlarmTime[nDay * 4 + 0].byStartMin = (BYTE)m_iMin11;
    pAlarmTime[nDay * 4 + 0].byStopHour = (BYTE)m_iHour12;
    pAlarmTime[nDay * 4 + 0].byStopMin = (BYTE)m_iMin12;

    pAlarmTime[nDay * 4 + 1].byStartHour = (BYTE)m_iHour21;
    pAlarmTime[nDay * 4 + 1].byStartMin = (BYTE)m_iMin21;
    pAlarmTime[nDay * 4 + 1].byStopHour = (BYTE)m_iHour22;
    pAlarmTime[nDay * 4 + 1].byStopMin = (BYTE)m_iMin22;

    pAlarmTime[nDay * 4 + 2].byStartHour = (BYTE)m_iHour31;
    pAlarmTime[nDay * 4 + 2].byStartMin = (BYTE)m_iMin31;
    pAlarmTime[nDay * 4 + 2].byStopHour = (BYTE)m_iHour32;
    pAlarmTime[nDay * 4 + 2].byStopMin = (BYTE)m_iMin32;

    pAlarmTime[nDay * 4 + 3].byStartHour = (BYTE)m_iHour41;
    pAlarmTime[nDay * 4 + 3].byStartMin = (BYTE)m_iMin41;
    pAlarmTime[nDay * 4 + 3].byStopHour = (BYTE)m_iHour42;
    pAlarmTime[nDay * 4 + 3].byStopMin = (BYTE)m_iMin42;
}


void CDlgAlarmHostZoneCfg::OnSelchangeComboweekday()
{
    int	i = m_comboWeekday.GetCurSel();
    SetAlarmTimeToWnd(&m_struAlarmInParam.struAlarmTime[0][0], i);
    UpdateData(FALSE);

}

void CDlgAlarmHostZoneCfg::OnSelchangeCombocopytime()
{

}

void CDlgAlarmHostZoneCfg::OnSelchangeComboDefenseType()
{
    if (m_comboDefenseType.GetCurSel() == 2)
    {
        GetDlgItem(IDC_EDIT_DELAY_TIME)->EnableWindow(TRUE);
    }
    else
    {
        GetDlgItem(IDC_EDIT_DELAY_TIME)->EnableWindow(FALSE);
    }
}

void CDlgAlarmHostZoneCfg::UpdatePapam()
{
    int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    if (iDeviceIndex < 0)
    {
        return;
    }

    int iChanIndex = g_pMainDlg->GetCurChanIndex();
    if (iChanIndex < 0)
    {
        iChanIndex = 0;//default to config channel one
    }
    m_iDevIndex = iDeviceIndex;
    m_lServerID = g_struDeviceInfo[iDeviceIndex].lLoginID;
    m_lStartChan = g_struDeviceInfo[iDeviceIndex].iStartChan;
    m_lChannel = iChanIndex + g_struDeviceInfo[iDeviceIndex].iStartChan;

    if (!m_bInit)
    {
        if (TRUE == GetAlarmHostAbility(m_struAlarmHostAbility))
        {
            m_bInit = TRUE;
            InitWnd();
            GetAlarmInParam(m_struAlarmInParam);
            SetAlarmInParamToWnd(m_struAlarmInParam);
        }
    }
    UpdateData(FALSE);
}


void CDlgAlarmHostZoneCfg::OnSelchangeCmbZoneResistor()
{
    // TODO: Add your control notification handler code here
    if (m_cmbZoneResistor.GetCurSel() == 6)
    {
        GetDlgItem(IDC_EDIT_ZONE_RESISTOR_MANUAL)->EnableWindow(TRUE);
    }
    else
    {
        GetDlgItem(IDC_EDIT_ZONE_RESISTOR_MANUAL)->EnableWindow(FALSE);
    }
}













