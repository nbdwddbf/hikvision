// DlgAlarmHostAbility.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmHostAbility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostAbility dialog


CDlgAlarmHostAbility::CDlgAlarmHostAbility(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmHostAbility::IDD, pParent)
    , m_bAlarminType10(FALSE)
    , m_bAlarminType11(FALSE)
    , m_bAlarminType12(FALSE)
    , m_bAlarminType13(FALSE)
{
	//{{AFX_DATA_INIT(CDlgAlarmHostAbility)
	m_iAudioOutNum = 0;
	m_iElectrolLockNum = 0;
	m_iExpandAlarmInNum = 0;
	m_iExpandAlarmOutNum = 0;
	m_iExpandRs485Num = 0;
	m_iExpandSensorNum = 0;
	m_iFullDuplexRs485Num = 0;
	m_iLocalAlarmInNum = 0;
	m_iLocalAlarmOutNum = 0;
	m_iLocalRs485Num = 0;
	m_iLocalSensorNum = 0;
	m_iMobileGateNum = 0;
	m_iSirenNum = 0;
    m_byAlarmLampNum = 0;
	m_iSubSystemNum = 0;
	m_iTotalAlarmOutNum = 0;
	m_iTotalRs485Num = 0;
	m_iTotalSensorNum = 0;
	m_iTotalAlarmInNum = 0;
	m_bAlarminType1 = FALSE;
	m_bAlarminType2 = FALSE;
	m_bAlarminType3 = FALSE;
	m_bAlarminType4 = FALSE;
	m_bAlarminType5 = FALSE;
	m_bSupportAlarmDelay = FALSE;
	m_bSupportArrayBypass = FALSE;
	m_bSupportDetector = FALSE;
	m_bSupportSens = FALSE;
	m_iBoardUserNums = 0;
	m_iNetUserNums = 0;
	m_iOperateUserNums = 0;
	m_bAlarminType6 = FALSE;
	m_bAlarminType7 = FALSE;
	m_bAlarminType8 = FALSE;
	m_bAlarminType9 = FALSE;
	m_dw3GCenter = 0;
	m_dwAudioNum = 0;
	m_dwCenterNum = 0;
	m_dwGPRSCenter = 0;
	m_dwNetCenterNum = 0;
	m_dwTelCenterNum = 0;
	m_byAnalogChan = 0;
	m_byDigitalChan = 0;
	m_byPublicSystemNum = 0;
	m_bSubsystemEnable = FALSE;
	m_bSubSystemTime = FALSE;
	m_bTriggerOffAlarmout = FALSE;
	m_bTriggerOnAlarmout = FALSE;
	m_bArmZoom = FALSE;
	m_iPublicSubsystemAsssociateSubsystem = 0;
	m_bSubsystemAutoArm = FALSE;
	m_bKeyzoomOperateSubsystem = FALSE;
	m_bReportSoundOnKeyboard = FALSE;
	m_bFaultAssociateSound = FALSE;
	m_bSearchStatus = FALSE;
	m_bExternalSubsystemCfg = FALSE;
	m_iOverallKeyboard = 0;
	m_bConfigFile = FALSE;
	m_bFaultLinakgeLed = FALSE;
	m_by485SlotNum = 0;
	//}}AFX_DATA_INIT
    memset(&m_struAlarmHostAbility, 0, sizeof(m_struAlarmHostAbility));
}


void CDlgAlarmHostAbility::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmHostAbility)
	DDX_Control(pDX, IDC_LIST_SUBSYSTEM_EVENT, m_listSubsystemEvent);
	DDX_Control(pDX, IDC_LIST_SUBSYSTEM_ARM_TYPE, m_listSubsystemArmType);
	DDX_Control(pDX, IDC_LIST_FAULT_TYPE, m_listFaultType);
	DDX_Control(pDX, IDC_LIST_OVERALL_EVENT, m_listOverallEvent);
	DDX_Text(pDX, IDC_EDIT_AUDIO_OUT_NUM, m_iAudioOutNum);
	DDX_Text(pDX, IDC_EDIT_ELECTROL_LOCK_NUM, m_iElectrolLockNum);
	DDX_Text(pDX, IDC_EDIT_EXPAND_ALARMIN_NUM, m_iExpandAlarmInNum);
	DDX_Text(pDX, IDC_EDIT_EXPAND_ALARMOUT_NUM, m_iExpandAlarmOutNum);
	DDX_Text(pDX, IDC_EDIT_EXPAND_RS485_NUM, m_iExpandRs485Num);
	DDX_Text(pDX, IDC_EDIT_EXPAND_SENSOR_NUM, m_iExpandSensorNum);
	DDX_Text(pDX, IDC_EDIT_FULL_DUPLEX_RS485_NUM, m_iFullDuplexRs485Num);
	DDX_Text(pDX, IDC_EDIT_LOCAL_ALARMIN_NUM, m_iLocalAlarmInNum);
	DDX_Text(pDX, IDC_EDIT_LOCAL_ALARMOUT_NUM, m_iLocalAlarmOutNum);
	DDX_Text(pDX, IDC_EDIT_LOCAL_RS485_NUM, m_iLocalRs485Num);
	DDX_Text(pDX, IDC_EDIT_LOCAL_SENSOR_NUM, m_iLocalSensorNum);
	DDX_Text(pDX, IDC_EDIT_MOBILE_GATE_NUM, m_iMobileGateNum);
	DDX_Text(pDX, IDC_EDIT_SIREN_NUM, m_iSirenNum);
    DDX_Text(pDX, IDC_EDIT_ALARMLAMP_NUM, m_byAlarmLampNum);
	DDX_Text(pDX, IDC_EDIT_SUB_SYSTEM_NUM, m_iSubSystemNum);
	DDX_Text(pDX, IDC_EDIT_TOTAL_ALARMOUT_NUM, m_iTotalAlarmOutNum);
	DDX_Text(pDX, IDC_EDIT_TOTAL_RS485_NUM, m_iTotalRs485Num);
	DDX_Text(pDX, IDC_EDIT_TOTAL_SENSOR_NUM, m_iTotalSensorNum);
	DDX_Text(pDX, IDC_EDIT_TOTOAL_ALARMIN_NUM, m_iTotalAlarmInNum);
	DDX_Check(pDX, IDC_CHECK_ALARMINTYPE1, m_bAlarminType1);
	DDX_Check(pDX, IDC_CHECK_ALARMINTYPE2, m_bAlarminType2);
	DDX_Check(pDX, IDC_CHECK_ALARMINTYPE3, m_bAlarminType3);
	DDX_Check(pDX, IDC_CHECK_ALARMINTYPE4, m_bAlarminType4);
	DDX_Check(pDX, IDC_CHECK_ALARMINTYPE5, m_bAlarminType5);
	DDX_Check(pDX, IDC_CHECK_SUPPORTALARMDELAY, m_bSupportAlarmDelay);
	DDX_Check(pDX, IDC_CHECK_SUPPORTARRAYBYPASS, m_bSupportArrayBypass);
	DDX_Check(pDX, IDC_CHECK_SUPPORTDETECTOR, m_bSupportDetector);
	DDX_Check(pDX, IDC_CHECK_SUPPORTSENS, m_bSupportSens);
	DDX_Text(pDX, IDC_EDIT_BOARDUSERNUMS, m_iBoardUserNums);
	DDX_Text(pDX, IDC_EDIT_NETUSERNUMS, m_iNetUserNums);
	DDX_Text(pDX, IDC_EDIT_OPERATEUSERNUMS, m_iOperateUserNums);
	DDX_Check(pDX, IDC_CHECK_ALARMINTYPE6, m_bAlarminType6);
	DDX_Check(pDX, IDC_CHECK_ALARMINTYPE7, m_bAlarminType7);
	DDX_Check(pDX, IDC_CHECK_ALARMINTYPE8, m_bAlarminType8);
	DDX_Check(pDX, IDC_CHECK_ALARMINTYPE9, m_bAlarminType9);
	DDX_Text(pDX, IDC_EDIT_3G_CENTER_NUM, m_dw3GCenter);
	DDX_Text(pDX, IDC_EDIT_AUDIONUMS, m_dwAudioNum);
	DDX_Text(pDX, IDC_EDIT_CENTERNUM, m_dwCenterNum);
	DDX_Text(pDX, IDC_EDIT_GPRS_CENTER_NUM, m_dwGPRSCenter);
	DDX_Text(pDX, IDC_EDIT_NET_CENTER_NUM, m_dwNetCenterNum);
	DDX_Text(pDX, IDC_EDIT_TEL_CENTER_NUM, m_dwTelCenterNum);
	DDX_Text(pDX, IDC_EDIT_ANALOG_VIDEO_CHAN, m_byAnalogChan);
	DDX_Text(pDX, IDC_EDIT_DIGITAL_VIDEO_CHAN, m_byDigitalChan);
	DDX_Text(pDX, IDC_EDIT_PUBLIC_SYSTEM_NUM, m_byPublicSystemNum);
	DDX_Check(pDX, IDC_CHECK_SUPPORT_SUBSYSTEM_ENABLE, m_bSubsystemEnable);
	DDX_Check(pDX, IDC_CHECK_SUPPORT_SUBSYSTEM_TIME, m_bSubSystemTime);
	DDX_Check(pDX, IDC_CHECK_SUPPORT_TRIGGER_OFF_ALARMOUT, m_bTriggerOffAlarmout);
	DDX_Check(pDX, IDC_CHECK_SUPPORT_TRIGGER_ON_ALARMOUT, m_bTriggerOnAlarmout);
	DDX_Check(pDX, IDC_CHECK_SUPPORT_ARM_ZOOM, m_bArmZoom);
	DDX_Text(pDX, IDC_EDIT_PUBLIC_SUBSYSTEM_ASSOCIATE_SUBSYSTEM, m_iPublicSubsystemAsssociateSubsystem);
	DDX_Check(pDX, IDC_CHECK_SUPPORT_SUBSYSTEM_AUTO_ARM, m_bSubsystemAutoArm);
	DDX_Check(pDX, IDC_CHECK_KEYZOOM_OPERATE_SUBSYSTEM, m_bKeyzoomOperateSubsystem);
	DDX_Check(pDX, IDC_CHECK_REPORT_SOUND_ON_KEYBOARD, m_bReportSoundOnKeyboard);
	DDX_Check(pDX, IDC_CHECK_SUPPORT_FAULT_ASSOCITATE_SOUND, m_bFaultAssociateSound);
	DDX_Check(pDX, IDC_CHECK_SUPPORT_SEARCH_STATUS, m_bSearchStatus);
	DDX_Check(pDX, IDC_CHECK_SUPPORT_SUBSYSTEM_EXTERNAL_CFG, m_bExternalSubsystemCfg);
	DDX_Text(pDX, IDC_EDIT_OVERALL_KEYBOARD, m_iOverallKeyboard);
	DDX_Check(pDX, IDC_CHECK_CONFIG_FILE, m_bConfigFile);
	DDX_Check(pDX, IDC_CHECK_FAULT_LINKAGE_LED, m_bFaultLinakgeLed);
	DDX_Text(pDX, IDC_EDIT_485SLOT_NUM, m_by485SlotNum);
	//}}AFX_DATA_MAP
    DDX_Check(pDX, IDC_CHECK_ALARMINTYPE10, m_bAlarminType10);
    DDX_Check(pDX, IDC_CHECK_ALARMINTYPE11, m_bAlarminType11);
    DDX_Check(pDX, IDC_CHECK_ALARMINTYPE12, m_bAlarminType12);
    DDX_Check(pDX, IDC_CHECK_ALARMINTYPE13, m_bAlarminType13);
}


BEGIN_MESSAGE_MAP(CDlgAlarmHostAbility, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmHostAbility)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostAbility message handlers

BOOL CDlgAlarmHostAbility::OnInitDialog() 
{
	CDialog::OnInitDialog();
    
	InitListWnd();

    SetAlarmHostAbilityToWnd(m_struAlarmHostAbility);
    UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlarmHostAbility::InitListWnd() 
{
	InitOverallEventList();
	InitSubsystemEventList();
	InitFaultTypeList();
	InitAlarmTypeList();
}

void CDlgAlarmHostAbility::InitOverallEventList() 
{
	//bit0-交流电掉电，bit1-电池电压低，bit2-电话线掉线，bit3-有线网络异常，bit4-无线网络异常
	char szLan[128] = {0};
    //全局事件
	int iIndex = 0;
    m_listOverallEvent.SetExtendedStyle(LVS_EX_CHECKBOXES);
	g_StringLanType(szLan, "交流电断电", "AC outage");
	m_listOverallEvent.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "电池电压低", "low voltage of battery");
	m_listOverallEvent.InsertItem(iIndex++, szLan);	
	g_StringLanType(szLan, "电话线掉线", "telephone off_line");
	m_listOverallEvent.InsertItem(iIndex++, szLan);	
	g_StringLanType(szLan, "有线网络异常", "network abnormal");
	m_listOverallEvent.InsertItem(iIndex++, szLan);	
	g_StringLanType(szLan, "无线网络", "Wireless network abnormal");
	m_listOverallEvent.InsertItem(iIndex++, szLan);	
    g_StringLanType(szLan, "硬盘故障", "harddiskException");
    m_listOverallEvent.InsertItem(iIndex++, szLan);
    g_StringLanType(szLan, "3G/4G信号异常", "3G4GSignalAbnormal");
    m_listOverallEvent.InsertItem(iIndex++, szLan);
    g_StringLanType(szLan, "第三方主机掉线", "thirdHostOffline");
    m_listOverallEvent.InsertItem(iIndex++, szLan);
    g_StringLanType(szLan, "WIFI通信故障", "WifiFault");
    m_listOverallEvent.InsertItem(iIndex++, szLan);
    g_StringLanType(szLan, "RF信号干扰故障", "RFSignalFault");
    m_listOverallEvent.InsertItem(iIndex++, szLan);
}

void CDlgAlarmHostAbility::InitSubsystemEventList() 
{
	char szLan[128] = {0};
    //子系统事件 bit0-进入延时，bit1-退出延时，bit2-布防，bit3-撤防，bit4-报警，bit5-消除报警记忆
	int iIndex = 0;
    m_listSubsystemEvent.SetExtendedStyle(LVS_EX_CHECKBOXES);
	g_StringLanType(szLan, "进入延时", "enter delay time");
	m_listSubsystemEvent.InsertItem(iIndex++, szLan);	
	g_StringLanType(szLan, "退出延时", "exit delay time");
	m_listSubsystemEvent.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "布防", "arm");
	m_listSubsystemEvent.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "撤防", "disarm");
	m_listSubsystemEvent.InsertItem(iIndex++, szLan);	
	g_StringLanType(szLan, "报警", "alarm");
	m_listSubsystemEvent.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "消除报警记忆", "clear alarm");
	m_listSubsystemEvent.InsertItem(iIndex++, szLan);		
}

void CDlgAlarmHostAbility::InitFaultTypeList() 
{
	//bit0-交流电断电，bit1-蓄电池欠压，bit2-主机防拆开，bit3-电话线掉线，bit4-主键盘掉线，bit5-网络故障，bit6-GPRS异常，bit7-MBUS异常，bit8-硬盘异常
	char szLan[128] = {0};
	int iIndex = 0;
    m_listFaultType.SetExtendedStyle(LVS_EX_CHECKBOXES);
	g_StringLanType(szLan, "交流电断电", "AC outage");
	m_listFaultType.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "蓄电池欠压", "low voltage of battery");
	m_listFaultType.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "主机防拆开", "device prevent disassemble");
	m_listFaultType.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "电话线掉线", "telephone off_line");
	m_listFaultType.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "主键盘掉线", "main keyboard off_line");
	m_listFaultType.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "网络故障", "network abnormal");
	m_listFaultType.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "GPRS异常", "GPRS abnormal");
	m_listFaultType.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "MBUS", "MBUS abnormal");
	m_listFaultType.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "硬盘异常", "hard disk abnormal");
	m_listFaultType.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "FPGA故障", "hard disk abnormal");
	m_listFaultType.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "模拟量故障", "hard disk abnormal");
	m_listFaultType.InsertItem(iIndex++, szLan);
}

void CDlgAlarmHostAbility::InitAlarmTypeList() 
{
	//bit0-外出布防，bit1-即时布防，bit2-留守布防。
	char szLan[128] = {0};
	int iIndex = 0;
	m_listSubsystemArmType.SetExtendedStyle(LVS_EX_CHECKBOXES);
	g_StringLanType(szLan, "外出布防", "ordinary arm");
	m_listSubsystemArmType.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "即时布防", "immediate arm");
	m_listSubsystemArmType.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "留守布防", "stay arm");
	m_listSubsystemArmType.InsertItem(iIndex++, szLan);
}

void CDlgAlarmHostAbility::SetAlarmHostAbilityToWnd(NET_DVR_ALARMHOST_ABILITY& struAlarmHostAlility)
{
    m_iAudioOutNum = struAlarmHostAlility.wAudioOutNum;
    m_iElectrolLockNum = struAlarmHostAlility.wElectroLockNum;
    m_iExpandAlarmInNum = struAlarmHostAlility.wExpandAlarmInNum;
    m_iExpandAlarmOutNum = struAlarmHostAlility.wExpandAlarmOutNum;
    m_iExpandRs485Num = struAlarmHostAlility.wExpandRs485Num;
    m_iExpandSensorNum = struAlarmHostAlility.wExpandSensorNum;
    m_iFullDuplexRs485Num = struAlarmHostAlility.wFullDuplexRs485Num;
    m_iLocalAlarmInNum = struAlarmHostAlility.wLocalAlarmInNum;
    m_iLocalAlarmOutNum = struAlarmHostAlility.wLocalAlarmOutNum;
    m_iLocalRs485Num = struAlarmHostAlility.wLocalRs485Num;
    m_iLocalSensorNum = struAlarmHostAlility.wLocalSensorNum;
    m_iMobileGateNum = struAlarmHostAlility.wGatewayNum;
    m_iSirenNum = struAlarmHostAlility.wSirenNum;
    m_iSubSystemNum = struAlarmHostAlility.wSubSystemNum;
    m_iTotalAlarmOutNum = struAlarmHostAlility.wTotalAlarmOutNum;
    m_iTotalRs485Num = struAlarmHostAlility.wTotalRs485Num;
    m_iTotalSensorNum = struAlarmHostAlility.wTotalSensorNum;
	m_iTotalAlarmInNum = struAlarmHostAlility.wTotalAlarmInNum;

    m_iNetUserNums = struAlarmHostAlility.wNetUserNum;
    m_iOperateUserNums = struAlarmHostAlility.wOperatorUserNum;
    m_iBoardUserNums = struAlarmHostAlility.wKeyboardNum;

	m_dwCenterNum = struAlarmHostAlility.byCenterGroupNum;
	m_dwTelCenterNum = struAlarmHostAlility.byTelNum;
	m_dwNetCenterNum = struAlarmHostAlility.byNetNum;
	m_dwGPRSCenter = struAlarmHostAlility.byGPRSNum;
	m_dw3GCenter = struAlarmHostAlility.by3GNum;
	m_dwAudioNum = struAlarmHostAlility.byAudioNum;

    m_bAlarminType1 = struAlarmHostAlility.bySupportAlarmInType[0];
    m_bAlarminType2 = struAlarmHostAlility.bySupportAlarmInType[1];
    m_bAlarminType3 = struAlarmHostAlility.bySupportAlarmInType[2];
    m_bAlarminType4 = struAlarmHostAlility.bySupportAlarmInType[3];
    m_bAlarminType5 = struAlarmHostAlility.bySupportAlarmInType[4];
    m_bAlarminType6 = struAlarmHostAlility.bySupportAlarmInType[5];
    m_bAlarminType7 = struAlarmHostAlility.bySupportAlarmInType[6];
    m_bAlarminType8 = struAlarmHostAlility.bySupportAlarmInType[7];
	m_bAlarminType9 = struAlarmHostAlility.bySupportAlarmInType[15];
    m_bAlarminType10 = struAlarmHostAlility.bySupportAlarmInType[8];
    m_bAlarminType11 = struAlarmHostAlility.bySupportAlarmInType[9];
    m_bAlarminType12 = struAlarmHostAlility.bySupportAlarmInType[10];
    m_bAlarminType13 = struAlarmHostAlility.bySupportAlarmInType[11];

    m_bSupportAlarmDelay = struAlarmHostAlility.bySupportAlarmInDelay;
    m_bSupportArrayBypass = struAlarmHostAlility.bySupportArrayBypass;
    m_bSupportDetector = struAlarmHostAlility.bySupportDetector;
    m_bSupportSens = struAlarmHostAlility.bySupportSensitivity;
	m_byAnalogChan = struAlarmHostAlility.byAnalogVideoChanNum;
	m_byDigitalChan = struAlarmHostAlility.byDigitalVideoChanNum;
	m_byPublicSystemNum = struAlarmHostAlility.byPublicSubSystemNum;
	m_iPublicSubsystemAsssociateSubsystem = struAlarmHostAlility.byPublicSubsystemAssociateSubsystemNum;
	m_iOverallKeyboard = struAlarmHostAlility.byOverallKeyboard;
	m_by485SlotNum = struAlarmHostAlility.by485SlotNum;
    m_byAlarmLampNum = struAlarmHostAlility.byAlarmLampNum;
	m_bSubSystemTime = (BOOL)(m_struAlarmHostAbility.dwSupport1 & 0x01);
	m_bTriggerOnAlarmout = (m_struAlarmHostAbility.dwSupport1 & 0x02) ? 1 : 0;
	m_bTriggerOffAlarmout = (m_struAlarmHostAbility.dwSupport1 & 0x04) ? 1 : 0;
	m_bSubsystemEnable = (m_struAlarmHostAbility.dwSupport1 & 0x08) ? 1 : 0;
	m_bArmZoom = (m_struAlarmHostAbility.dwSupport1 & 0x10) ? 1 : 0;
	m_bSubsystemAutoArm = (m_struAlarmHostAbility.dwSupport1 & 0x20) ? 1 : 0;
	m_bFaultAssociateSound = (m_struAlarmHostAbility.dwSupport1 & 0x40) ? 1 : 0;
	m_bSearchStatus = (m_struAlarmHostAbility.dwSupport1 & 0x80) ? 1 : 0;
	m_bExternalSubsystemCfg = (m_struAlarmHostAbility.dwSupport1 & 0x100) ? 1 : 0;
	m_bKeyzoomOperateSubsystem = (m_struAlarmHostAbility.dwSupport1 & 0x200) ? 1 : 0;
	m_bReportSoundOnKeyboard = (m_struAlarmHostAbility.dwSupport1 & 0x400) ? 1 : 0;
	m_bConfigFile = (m_struAlarmHostAbility.dwSupport1 & 0x800) ? 1 : 0;
	m_bFaultLinakgeLed = (m_struAlarmHostAbility.dwSupport1 & 0x2000) ? 1 : 0;

	BOOL bState = 0;
	int i=0;
	for (i=0; i<m_listOverallEvent.GetItemCount(); i++)
	{
		bState = (m_struAlarmHostAbility.dwOverallEvent>>i) & 0x01;
		m_listOverallEvent.SetCheck(i, bState);
	}
	for (i=0; i<m_listSubsystemEvent.GetItemCount(); i++)
	{
		bState = (m_struAlarmHostAbility.dwSubSystemEvent>>i) & 0x01;
		m_listSubsystemEvent.SetCheck(i, bState);
	}
	for (i=0; i<m_listFaultType.GetItemCount(); i++)
	{
		bState = (m_struAlarmHostAbility.dwFaultType>>i) & 0x01;
		m_listFaultType.SetCheck(i, bState);
	}
	for (i=0; i<m_listSubsystemArmType.GetItemCount(); i++)
	{
		bState = (m_struAlarmHostAbility.bySubSystemArmType>>i) & 0x01;
		m_listSubsystemArmType.SetCheck(i, bState);
	}
	UpdateData(FALSE);
}
