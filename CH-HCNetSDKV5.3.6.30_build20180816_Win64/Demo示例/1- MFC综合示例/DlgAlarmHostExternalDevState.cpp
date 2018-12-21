// DlgAlarmHostExternalDevState.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmHostExternalDevState.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostExternalDevState dialog


CDlgAlarmHostExternalDevState::CDlgAlarmHostExternalDevState(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmHostExternalDevState::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAlarmHostExternalDevState)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(&m_struExternalDeviceState, 0 ,sizeof(NET_DVR_ALARMHOST_EXTERNAL_DEVICE_STATE));
}


void CDlgAlarmHostExternalDevState::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmHostExternalDevState)
	DDX_Control(pDX, IDC_COMBO_EXTERNAL_DEVICE_TYPE, m_cmDevType);
	DDX_Control(pDX, IDC_LIST_STATE, m_listState);
	DDX_Control(pDX, IDC_COMBO_SLOT_INDEX, m_cmSlotIndex);
	DDX_Control(pDX, IDC_COMBO_485CHANNEL, m_cm485ChanIndex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmHostExternalDevState, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmHostExternalDevState)
	ON_CBN_SELCHANGE(IDC_COMBO_EXTERNAL_DEVICE_TYPE, OnSelchangeComboExternalDeviceType)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostExternalDevState message handlers

BOOL CDlgAlarmHostExternalDevState::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	m_listState.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listState.InsertColumn(0, "variable", LVCFMT_LEFT, 200, -1);
	m_listState.InsertColumn(1,"value", LVCFMT_LEFT, 200, -1);

	m_cmDevType.AddString("UPS");
	g_StringLanType(m_sTemp, "开关电源", "Switch Power");
	m_cmDevType.AddString(m_sTemp);
	g_StringLanType(m_sTemp, "气体检测系统", "Gas detect system");
	m_cmDevType.AddString(m_sTemp);
	g_StringLanType(m_sTemp, "温湿度传感器", "Temperature Humidity sensor");
	m_cmDevType.AddString(m_sTemp);
	g_StringLanType(m_sTemp, "空调", "Air condition");
	m_cmDevType.AddString(m_sTemp);
	g_StringLanType(m_sTemp, "电量表", "Electricity");
	m_cmDevType.AddString(m_sTemp);
	g_StringLanType(m_sTemp, "变压器温显表", "Transformer temperature");
	m_cmDevType.AddString(m_sTemp);

	g_StringLanType(m_sTemp, "水位传感器", "water level sensor");
	m_cmDevType.AddString(m_sTemp);
	g_StringLanType(m_sTemp, "扬尘噪声传感器", "dust and noise sensor");
	m_cmDevType.AddString(m_sTemp);
	g_StringLanType(m_sTemp, "环境采集仪", "environmental logger");
	m_cmDevType.AddString(m_sTemp);

	m_struAbility.dwSize = sizeof(m_struAbility);
	if(!NET_DVR_GetDeviceAbility(m_lUserID, ALARMHOST_ABILITY, NULL, 0, (char*)&m_struAbility, sizeof(m_struAbility)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Get Alarmhost ability failed");
		return FALSE;
	}
	CString csStr;
	m_cm485ChanIndex.ResetContent();
	int i=0; 
	for (i=0; i<(m_struAbility.wLocalRs485Num +  m_struAbility.wExpandRs485Num); i++)
	{
		csStr.Format("Chan%d", i+1);
		m_cm485ChanIndex.AddString(csStr);
	}

	m_cmSlotIndex.ResetContent();
	for (i=0; i<m_struAbility.by485SlotNum; i++)
	{
		csStr.Format("Slot%d", i+1);
		m_cmSlotIndex.AddString(csStr);
	}
	m_cm485ChanIndex.SetCurSel(0);
	m_cmSlotIndex.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgAlarmHostExternalDevState::OnSelchangeComboExternalDeviceType() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_listState.DeleteAllItems();
	int iIndex = m_cmDevType.GetCurSel() + 1;
	if (1 == iIndex)
	{
		memcpy(&m_struUpsState, &m_struExternalDeviceState.struDevState.struUpsState, sizeof(NET_DVR_ALARMHOST_UPS_STATE));
		SetUpsState();
	}
	else if (2 == iIndex)
	{
		memcpy(&m_struSwitchPowerState, &m_struExternalDeviceState.struDevState.struSwitchPowerState, sizeof(NET_DVR_ALARMHOST_SWITCH_POWER_SUPPLY_STATE));
		SetSwitchPowerState() ;
	}
	else if (3 == iIndex)
	{
		memcpy(&m_struGasDetectorState, &m_struExternalDeviceState.struDevState.struGasDetectorState, sizeof(NET_DVR_ALARMHOST_GAS_DETECTOR_STATE));
		SetGasDetectSystemState() ;
	}
	else if (4 == iIndex)
	{
		memcpy(&m_struTempHumiSensorState, &m_struExternalDeviceState.struDevState.struTempHumiSensorState, sizeof(NET_DVR_ALARMHOST_TEMP_HUMI_SENSOR_STATE));
		SetTempHumiSensorState() ;
	}
	else if (5 == iIndex)
	{
		memcpy(&m_struAirConditionState, &m_struExternalDeviceState.struDevState.struAirConditionState, sizeof(NET_DVR_ALARMHOST_AIRCONDITION_STATE));
		SetAirConditionState() ;
	}
	else if (6 == iIndex)
	{
		memcpy(&m_struElectricityState, &m_struExternalDeviceState.struDevState.struElectricityState, sizeof(NET_DVR_ALARMHOST_ELECTRICITY_STATE));
		SetElectricityState();
	}
	else if (7 == iIndex)
	{
		memcpy(&m_struTransformaterTempState, &m_struExternalDeviceState.struDevState.struTransformerTempState, sizeof(NET_DVR_ALARMHOST_TRANSFORMER_TEMP_STATE));
		SetTransformaterState();
	}
	else if (8 == iIndex)
	{
		memcpy(&m_struWaterLevelSensor, &m_struExternalDeviceState.struDevState.struWaterLevelSensor, sizeof(NET_DVR_ALARMHOST_WATERLEVEL_SENSOR));
		SetWaterLevelSensorParam();
	}
	else if (9 == iIndex)
	{
		memcpy(&m_struDustNoiseSensor, &m_struExternalDeviceState.struDevState.struDustNoiseSensor, sizeof(NET_DVR_ALARMHOST_DUSTNOISE_SENSOR));
		SetDustNoiseSensorParam();
	}
	else if (10 == iIndex)
	{
		memcpy(&m_struEnvironmentLogger, &m_struExternalDeviceState.struDevState.struEnvironmentLogger, sizeof(NET_DVR_ALARMHOST_ENVIRONMENTAL_LOGGER));
		SetEnvironmentLoggerParam();
	}
	UpdateData(FALSE);
}

void CDlgAlarmHostExternalDevState::SetGasDetectSystemState() 
{
	m_listState.DeleteAllItems();
	int index = 0;
	
	m_listState.InsertItem(index, "SF6", 0);
	sprintf(m_sTemp, "%d", m_struGasDetectorState.iSF6);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "流量", 0);
	sprintf(m_sTemp, "%d", m_struGasDetectorState.iFlow);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "温度", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struGasDetectorState.iTemperature/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "氧气", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struGasDetectorState.iO2/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "湿度", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struGasDetectorState.iHumidity/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	UpdateData(FALSE);
	
}

void CDlgAlarmHostExternalDevState::SetTempHumiSensorState() 
{
	m_listState.DeleteAllItems();
	int index = 0;

	m_listState.InsertItem(index, "温度", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struTempHumiSensorState.iTemperature/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "湿度", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struTempHumiSensorState.iHumidity/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	UpdateData(FALSE);
}

void CDlgAlarmHostExternalDevState::SetAirConditionState() 
{
	m_listState.DeleteAllItems();
	int index = 0;

	m_listState.InsertItem(index, "温度", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struAirConditionState.iTemperature/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "湿度", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struAirConditionState.iHumidity/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "运行状态", 0);
	if (1 == m_struAirConditionState.byRunState)
	{
		sprintf(m_sTemp, "正常");
	}
	else if(2 == m_struAirConditionState.byRunState)
	{
		sprintf(m_sTemp, "停机");
	}
	else
	{
		sprintf(m_sTemp, "未知状态");
	}
	m_listState.SetItemText(index++, 1, m_sTemp);
	UpdateData(FALSE);
}

void CDlgAlarmHostExternalDevState::SetSwitchPowerState() 
{
	m_listState.DeleteAllItems();
	int index = 0;

	m_listState.InsertItem(index, "A相交流电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struSwitchPowerState.struACVoltage.iPhaseAVol/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "B相交流电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struSwitchPowerState.struACVoltage.iPhaseBVol/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "C相交流电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struSwitchPowerState.struACVoltage.iPhaseCVol/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "相平均电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struSwitchPowerState.struACVoltage.iAveragePhaseVol/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "DC转换器电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struSwitchPowerState.iDCConvertVoltage/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "A相交流电流", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struSwitchPowerState.struACCurrent.iPhaseACurrent/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "B相交流电流", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struSwitchPowerState.struACCurrent.iPhaseBCurrent/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "C相交流电流", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struSwitchPowerState.struACCurrent.iPhaseCCurrent/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "负载总电流", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struSwitchPowerState.iTotalCurrent/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "电池1温度", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struSwitchPowerState.iBattery1Temperature/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "电池2温度", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struSwitchPowerState.iBattery2Temperature/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "电池1电流", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struSwitchPowerState.iBattery1Current/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "电池2电流", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struSwitchPowerState.iBattery2Current/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "电池3电流", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struSwitchPowerState.iBattery3Current/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "电池4电流", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struSwitchPowerState.iBattery4Current/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "电池测试电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struSwitchPowerState.iBatteryTestVoltage/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "整流模块输出电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struSwitchPowerState.iRectifierOutputVoltage/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "整流模块输出电流", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struSwitchPowerState.iRectifierOutputCurrent/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "直流输出电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struSwitchPowerState.iDCOutputVoltage/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	UpdateData(FALSE);
}

void CDlgAlarmHostExternalDevState::SetUpsState() 
{
	m_listState.DeleteAllItems();
	int index = 0;

	m_listState.InsertItem(index, "A相输入电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struInputVoltage.iPhaseAVol/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "B相输入电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struInputVoltage.iPhaseBVol/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "C相输入电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struInputVoltage.iPhaseCVol/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "平均输入电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struInputVoltage.iAveragePhaseVol/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "A相旁路电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struBypassVoltage.iPhaseAVol/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "B相旁路电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struBypassVoltage.iPhaseBVol/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "C相旁路电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struBypassVoltage.iPhaseCVol/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "平均旁路电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struBypassVoltage.iAveragePhaseVol/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "A相输出电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struOutputVoltage.iPhaseAVol/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "B相输出电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struOutputVoltage.iPhaseBVol/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "C相输出电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struOutputVoltage.iPhaseCVol/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "平均输出电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struOutputVoltage.iAveragePhaseVol/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "整流器电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.iRectifierVol/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "逆变器电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.iInverterVol/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "A相输入电流", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struInputCurrent.iPhaseACurrent/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "B相输入电流", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struInputCurrent.iPhaseBCurrent/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "C相输入电流", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struInputCurrent.iPhaseCCurrent/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "A相旁路电流", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struBypassCurrent.iPhaseACurrent/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "B相旁路电流", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struBypassCurrent.iPhaseBCurrent/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "C相旁路电流", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struBypassCurrent.iPhaseCCurrent/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "A相输出电流", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struOutputCurrent.iPhaseACurrent/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "B相输出电流", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struOutputCurrent.iPhaseBCurrent/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "C相输出电流", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struOutputCurrent.iPhaseCCurrent/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "逆变器电流", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.iInverterCurrent/10);
	m_listState.SetItemText(index++, 1, m_sTemp);




	m_listState.InsertItem(index, "A相输入频率", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struInputFrequency.iPhaseAFrequency/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "B相输入频率", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struInputFrequency.iPhaseBFrequency/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "C相输入频率", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struInputFrequency.iPhaseCFrequency/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "A相旁路频率", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struBypassFrequency.iPhaseAFrequency/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "B相旁路频率", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struBypassFrequency.iPhaseBFrequency/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "C相旁路频率", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struBypassFrequency.iPhaseCFrequency/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "A相输出频率", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struOutputFrequency.iPhaseAFrequency/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "B相输出频率", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struOutputFrequency.iPhaseBFrequency/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "C相输出频率", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.struOutputFrequency.iPhaseCFrequency/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "逆变器频率", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.iInverterFre/10);
	m_listState.SetItemText(index++, 1, m_sTemp);




	m_listState.InsertItem(index, "A相输入功率", 0);
	sprintf(m_sTemp, "%d", m_struUpsState.struInputPower.iPhaseAPower);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "B相输入功率", 0);
	sprintf(m_sTemp, "%d", m_struUpsState.struInputPower.iPhaseBPower);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "C相输入功率", 0);
	sprintf(m_sTemp, "%d", m_struUpsState.struInputPower.iPhaseCPower);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "A相旁路功率", 0);
	sprintf(m_sTemp, "%d", m_struUpsState.struBypassPower.iPhaseAPower);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "B相旁路功率", 0);
	sprintf(m_sTemp, "%d", m_struUpsState.struBypassPower.iPhaseBPower);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "C相旁路功率", 0);
	sprintf(m_sTemp, "%d", m_struUpsState.struBypassPower.iPhaseCPower);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "A相输出功率", 0);
	sprintf(m_sTemp, "%d", m_struUpsState.struOutputPower.iPhaseAPower);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "B相输出功率", 0);
	sprintf(m_sTemp, "%d", m_struUpsState.struOutputPower.iPhaseBPower);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "C相输出功率", 0);
	sprintf(m_sTemp, "%d", m_struUpsState.struOutputPower.iPhaseCPower);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "A相复功率", 0);
	sprintf(m_sTemp, "%d", m_struUpsState.struComplexPower.iPhaseAPower);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "B相复功率", 0);
	sprintf(m_sTemp, "%d", m_struUpsState.struComplexPower.iPhaseBPower);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "C相复功率", 0);
	sprintf(m_sTemp, "%d", m_struUpsState.struComplexPower.iPhaseCPower);
	m_listState.SetItemText(index++, 1, m_sTemp);


	m_listState.InsertItem(index, "标称功率", 0);
	sprintf(m_sTemp, "%d", m_struUpsState.iNormalPower);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "功率因数", 0);
	sprintf(m_sTemp, "%.2f", (float)m_struUpsState.iPowerFacter/100);
	m_listState.SetItemText(index++, 1, m_sTemp);


	m_listState.InsertItem(index, "电池备份时间", 0);
	sprintf(m_sTemp, "%d", m_struUpsState.iBatteryEstimated);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "A相负载率", 0);
	sprintf(m_sTemp, "%.2f", (float)m_struUpsState.struBatteryLoadFactor.iPhaseALoadFactor/100);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "B相负载率", 0);
	sprintf(m_sTemp, "%.2f", (float)m_struUpsState.struBatteryLoadFactor.iPhaseBLoadFactor/100);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "C相负载率", 0);
	sprintf(m_sTemp, "%.2f", (float)m_struUpsState.struBatteryLoadFactor.iPhaseCLoadFactor/100);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "电池温度", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.iBatteryTemperature/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "电池电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struUpsState.iBatteryVoltage/10);
	m_listState.SetItemText(index++, 1, m_sTemp);


	m_listState.InsertItem(index, "整流器运行状态", 0);
	if (1 == m_struUpsState.byRectifierState)
	{
		g_StringLanType(m_sTemp, "正常", "Normal");
		sprintf(m_sTemp, "%s", m_sTemp);
	}
	else if(2 == m_struUpsState.byRectifierState)
	{
		g_StringLanType(m_sTemp, "异常", "Abnormal");
		sprintf(m_sTemp, "%s", m_sTemp);
	}
	else
	{
		g_StringLanType(m_sTemp, "未知状态", "Unknown");
		sprintf(m_sTemp, "%s", m_sTemp);
	}
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	m_listState.InsertItem(index, "逆变器运行状态", 0);
	if (1 == m_struUpsState.byInverterState)
	{
		g_StringLanType(m_sTemp, "正常", "Normal");
		sprintf(m_sTemp, "%s", m_sTemp);
	}
	else if(2 == m_struUpsState.byInverterState)
	{
		g_StringLanType(m_sTemp, "异常", "Abnormal");
		sprintf(m_sTemp, "%s", m_sTemp);
	}
	else
	{
		g_StringLanType(m_sTemp, "未知状态", "Unknown");
		sprintf(m_sTemp, "%s", m_sTemp);
	}
	m_listState.SetItemText(index++, 1, m_sTemp);


	m_listState.InsertItem(index, "充电器运行状态", 0);
	if (1 == m_struUpsState.byChargeState)
	{
		g_StringLanType(m_sTemp, "正常", "Normal");
		sprintf(m_sTemp, "%s", m_sTemp);
	}
	else if(2 == m_struUpsState.byChargeState)
	{
		g_StringLanType(m_sTemp, "异常", "Abnormal");
		sprintf(m_sTemp, "%s", m_sTemp);
	}
	else
	{
		g_StringLanType(m_sTemp, "未知状态", "Unknown");
		sprintf(m_sTemp, "%s", m_sTemp);
	}
	m_listState.SetItemText(index++, 1, m_sTemp);


	m_listState.InsertItem(index, "电池运行状态", 0);
	if (1 == m_struUpsState.byBatteryState)
	{
		g_StringLanType(m_sTemp, "正常", "Normal");
		sprintf(m_sTemp, "%s", m_sTemp);
	}
	else if(2 == m_struUpsState.byBatteryState)
	{
		g_StringLanType(m_sTemp, "异常", "Abnormal");
		sprintf(m_sTemp, "%s", m_sTemp);
	}
	else
	{
		g_StringLanType(m_sTemp, "未知状态", "Unknown");
		sprintf(m_sTemp, "%s", m_sTemp);
	}
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "自动旁路状态", 0);
	if (1 == m_struUpsState.byAutoBypassState)
	{
		g_StringLanType(m_sTemp, "正常", "Normal");
		sprintf(m_sTemp, "%s", m_sTemp);
	}
	else if(2 == m_struUpsState.byAutoBypassState)
	{
		g_StringLanType(m_sTemp, "异常", "Abnormal");
		sprintf(m_sTemp, "%s", m_sTemp);
	}
	else
	{
		g_StringLanType(m_sTemp, "未知状态", "Unknown");
		sprintf(m_sTemp, "%s", m_sTemp);
	}
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "整流器运行状态", 0);

	if (1 == m_struUpsState.byRectifierState)
	{
		g_StringLanType(m_sTemp, "正常", "Normal");
		sprintf(m_sTemp, "%s", m_sTemp);
	}
	else if(2 == m_struUpsState.byRectifierState)
	{
		g_StringLanType(m_sTemp, "异常", "Abnormal");
		sprintf(m_sTemp, "%s", m_sTemp);
	}
	else
	{
		g_StringLanType(m_sTemp, "未知状态", "Unknown");
		sprintf(m_sTemp, "%s", m_sTemp);
	}
	m_listState.SetItemText(index++, 1, m_sTemp);

	UpdateData(FALSE);
}

void CDlgAlarmHostExternalDevState::SetElectricityState()
{
	m_listState.DeleteAllItems();
	int index = 0;
	//直流电压
	m_listState.InsertItem(index, "直流电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struElectricityState.iDCVoltage/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	//直流电流
	m_listState.InsertItem(index, "直流电流", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struElectricityState.iDCCurrent/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	//电压
	m_listState.InsertItem(index, "A相电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struElectricityState.struPhaseVoltage.iPhaseAVol/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "B相电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struElectricityState.struPhaseVoltage.iPhaseBVol/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "C相电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struElectricityState.struPhaseVoltage.iPhaseCVol/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "相电压平均值", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struElectricityState.struPhaseVoltage.iAveragePhaseVol/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "AB线电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struElectricityState.struLineVoltage.iLineVolAB/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "BC线电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struElectricityState.struLineVoltage.iLineVolBC/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "CA线电压", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struElectricityState.struLineVoltage.iLineVolCA/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "线电压平均值", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struElectricityState.struLineVoltage.iAverageLineVol/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	//电流
	int i=0; 
	for (i=0; i<4; i++)
	{
		sprintf(m_sTemp, "第%d路A相电流", i+1);
		m_listState.InsertItem(index, m_sTemp, 0);
		sprintf(m_sTemp, "%.1f", (float)m_struElectricityState.struCurrent[i].iPhaseACurrent/10);
		m_listState.SetItemText(index++, 1, m_sTemp);

		sprintf(m_sTemp, "第%d路B相电流", i+1);
		m_listState.InsertItem(index, m_sTemp, 0);
		sprintf(m_sTemp, "%.1f", (float)m_struElectricityState.struCurrent[i].iPhaseBCurrent/10);
		m_listState.SetItemText(index++, 1, m_sTemp);

		sprintf(m_sTemp, "第%d路C相电流", i+1);
		m_listState.InsertItem(index, m_sTemp, 0);
		sprintf(m_sTemp, "%.1f", (float)m_struElectricityState.struCurrent[i].iPhaseCCurrent/10);
		m_listState.SetItemText(index++, 1, m_sTemp);
	}
	m_listState.InsertItem(index, "平均电流", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struElectricityState.iAverageCurrent/10);
	m_listState.SetItemText(index++, 1, m_sTemp);

	m_listState.InsertItem(index, "中线电流", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struElectricityState.iNeutralCurrent/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	//有功功率
	for (i=0; i<4; i++)
	{
		sprintf(m_sTemp, "第%d路A相有功功率", i+1);
		m_listState.InsertItem(index, m_sTemp, 0);
		sprintf(m_sTemp, "%d", m_struElectricityState.struActivePower[i].iPhaseAPower);
		m_listState.SetItemText(index++, 1, m_sTemp);

		sprintf(m_sTemp, "第%d路B相有功功率", i+1);
		m_listState.InsertItem(index, m_sTemp, 0);
		sprintf(m_sTemp, "%d", m_struElectricityState.struActivePower[i].iPhaseBPower);
		m_listState.SetItemText(index++, 1, m_sTemp);

		sprintf(m_sTemp, "第%d路C相有功功率", i+1);
		m_listState.InsertItem(index, m_sTemp, 0);
		sprintf(m_sTemp, "%d", m_struElectricityState.struActivePower[i].iPhaseCPower);
		m_listState.SetItemText(index++, 1, m_sTemp);

		sprintf(m_sTemp, "第%d路系统合相有功功率", i+1);
		m_listState.InsertItem(index, m_sTemp, 0);
		sprintf(m_sTemp, "%d", m_struElectricityState.struActivePower[i].iSysTotalPower);
		m_listState.SetItemText(index++, 1, m_sTemp);
	}
	//无功功率
	for (i=0; i<4; i++)
	{
		sprintf(m_sTemp, "第%d路A相无功功率", i+1);
		m_listState.InsertItem(index, m_sTemp, 0);
		sprintf(m_sTemp, "%d", m_struElectricityState.struReactivePower[i].iPhaseAPower);
		m_listState.SetItemText(index++, 1, m_sTemp);
		sprintf(m_sTemp, "第%d路B相无功功率", i+1);
		m_listState.InsertItem(index, m_sTemp, 0);
		sprintf(m_sTemp, "%d", m_struElectricityState.struReactivePower[i].iPhaseBPower);
		m_listState.SetItemText(index++, 1, m_sTemp);
		sprintf(m_sTemp, "第%d路C相无功功率", i+1);
		m_listState.InsertItem(index, m_sTemp, 0);
		sprintf(m_sTemp, "%d", m_struElectricityState.struReactivePower[i].iPhaseCPower);
		m_listState.SetItemText(index++, 1, m_sTemp);
		sprintf(m_sTemp, "第%d路系统合相无功功率", i+1);
		m_listState.InsertItem(index, m_sTemp, 0);
		sprintf(m_sTemp, "%d", m_struElectricityState.struReactivePower[i].iSysTotalPower);
		m_listState.SetItemText(index++, 1, m_sTemp);
	}
	//视在功率
	for (i=0; i<4; i++)
	{
		sprintf(m_sTemp, "第%d路A相视在功率", i+1);
		m_listState.InsertItem(index, m_sTemp, 0);
		sprintf(m_sTemp, "%d", m_struElectricityState.struApparentPower[i].iPhaseAPower);
		m_listState.SetItemText(index++, 1, m_sTemp);

		sprintf(m_sTemp, "第%d路B相视在功率", i+1);
		m_listState.InsertItem(index, m_sTemp, 0);
		sprintf(m_sTemp, "%d", m_struElectricityState.struApparentPower[i].iPhaseBPower);
		m_listState.SetItemText(index++, 1, m_sTemp);

		sprintf(m_sTemp, "第%d路C相视在功率", i+1);
		m_listState.InsertItem(index, m_sTemp, 0);
		sprintf(m_sTemp, "%d", m_struElectricityState.struApparentPower[i].iPhaseCPower);
		m_listState.SetItemText(index++, 1, m_sTemp);

		sprintf(m_sTemp, "第%d路系统合相视在功率", i+1);
		m_listState.InsertItem(index, m_sTemp, 0);
		sprintf(m_sTemp, "%d", m_struElectricityState.struApparentPower[i].iSysTotalPower);
		m_listState.SetItemText(index++, 1, m_sTemp);
	}
	//功率因数
	for (i=0; i<4; i++)
	{
		sprintf(m_sTemp, "第%d路A相功率因数", i+1);
		m_listState.InsertItem(index, m_sTemp, 0);
		sprintf(m_sTemp, "%.2f", (float)m_struElectricityState.struPowerFactor[i].iPhaseAPowerFactor/100);
		m_listState.SetItemText(index++, 1, m_sTemp);

		sprintf(m_sTemp, "第%d路B相功率因数", i+1);
		m_listState.InsertItem(index, m_sTemp, 0);
		sprintf(m_sTemp, "%.2f", (float)m_struElectricityState.struPowerFactor[i].iPhaseBPowerFactor/100);
		m_listState.SetItemText(index++, 1, m_sTemp);

		sprintf(m_sTemp, "第%d路C相功率因数", i+1);
		m_listState.InsertItem(index, m_sTemp, 0);
		sprintf(m_sTemp, "%.2f", (float)m_struElectricityState.struPowerFactor[i].iPhaseCPowerFactor/100);
		m_listState.SetItemText(index++, 1, m_sTemp);

		sprintf(m_sTemp, "第%d路系统合相功率因数", i+1);
		m_listState.InsertItem(index, m_sTemp, 0);
		sprintf(m_sTemp, "%.2f", (float)m_struElectricityState.struPowerFactor[i].iTotalPowerFactor/100);
		m_listState.SetItemText(index++, 1, m_sTemp);
	}

	//频率
	m_listState.InsertItem(index, "A相频率", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struElectricityState.struFrequency.iPhaseAFrequency/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	m_listState.InsertItem(index, "B相频率", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struElectricityState.struFrequency.iPhaseBFrequency/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	m_listState.InsertItem(index, "C相频率", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struElectricityState.struFrequency.iPhaseCFrequency/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	UpdateData(FALSE);
}

void CDlgAlarmHostExternalDevState::SetTransformaterState()
{
	m_listState.DeleteAllItems();
	int index = 0;
	//A相温度
	m_listState.InsertItem(index, "A相温度", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struTransformaterTempState.iPhaseATemperature/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	//B相温度
	m_listState.InsertItem(index, "B相温度", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struTransformaterTempState.iPhaseBTemperature/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	//C相温度
	m_listState.InsertItem(index, "C相温度", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struTransformaterTempState.iPhaseCTemperature/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	//D相温度
	m_listState.InsertItem(index, "D相温度", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struTransformaterTempState.iPhaseDTemperature/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	UpdateData(FALSE);
}


void CDlgAlarmHostExternalDevState::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwStatus = 0;
	DWORD dwChanIndex = 0;
	DWORD dwSlotIndex = 0;
	DWORD dwInput = 0; 
	dwChanIndex = m_cm485ChanIndex.GetCurSel() + 1;
	//dwChanIndex = 0;
	dwChanIndex = dwChanIndex << 16;
	dwSlotIndex = m_cmSlotIndex.GetCurSel() + 1;
	dwInput = dwChanIndex | dwSlotIndex;

	if (!NET_DVR_GetDeviceStatus(m_lUserID, NET_DVR_GET_ALARMHOST_EXTERNAL_DEVICE_STATE, 1, &dwInput, 4, NULL, &m_struExternalDeviceState, sizeof(m_struExternalDeviceState)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Get Device status failed");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Get device status successful");
	}
	m_cmDevType.SetCurSel(m_struExternalDeviceState.byDevType - 1);
	UpdateData(FALSE);	
	OnSelchangeComboExternalDeviceType();
}

void CDlgAlarmHostExternalDevState::SetWaterLevelSensorParam()
{
	m_listState.DeleteAllItems();
	int index = 0;
	//水位
	m_listState.InsertItem(index, "水位", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struWaterLevelSensor.iWaterLevel/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	UpdateData(FALSE);
}

void CDlgAlarmHostExternalDevState::SetDustNoiseSensorParam()
{
	m_listState.DeleteAllItems();
	int index = 0;
	//扬尘
	m_listState.InsertItem(index, "扬尘", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struDustNoiseSensor.iDust/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	//噪声
	m_listState.InsertItem(index, "噪声", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struDustNoiseSensor.iNoise/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	UpdateData(FALSE);
}

void CDlgAlarmHostExternalDevState::SetEnvironmentLoggerParam()
{
	m_listState.DeleteAllItems();
	int index = 0;
	//氨氮
	m_listState.InsertItem(index, "氨氮", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struEnvironmentLogger.iAmmoniaNitrogen/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	//COD
	m_listState.InsertItem(index, "COD", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struEnvironmentLogger.iCOD/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	//PH
	m_listState.InsertItem(index, "PH", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struEnvironmentLogger.iPH/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	//氧气
	m_listState.InsertItem(index, "氧气", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struEnvironmentLogger.iOxygen/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	//二氧化硫
	m_listState.InsertItem(index, "二氧化硫", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struEnvironmentLogger.iSulfurDioxide/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	//烟尘
	m_listState.InsertItem(index, "烟尘", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struEnvironmentLogger.iSoot/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	//氟化物
	m_listState.InsertItem(index, "氟化物", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struEnvironmentLogger.iFluoride/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	//污水
	m_listState.InsertItem(index, "污水", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struEnvironmentLogger.iPollutedWater/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	//总磷
	m_listState.InsertItem(index, "总磷", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struEnvironmentLogger.iTotalPhosphorus/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	//废气
	m_listState.InsertItem(index, "废气", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struEnvironmentLogger.iExhaust/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	//氮氧化物
	m_listState.InsertItem(index, "氮氧化物", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struEnvironmentLogger.iNitrogenOxides/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	//烟气温度
	m_listState.InsertItem(index, "烟气温度", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struEnvironmentLogger.iFlueGasTemperature/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	//烟气压力
	m_listState.InsertItem(index, "烟气压力", 0);
	sprintf(m_sTemp, "%.1f", (float)m_struEnvironmentLogger.iFlueGasPressure/10);
	m_listState.SetItemText(index++, 1, m_sTemp);
	
	UpdateData(FALSE);
}