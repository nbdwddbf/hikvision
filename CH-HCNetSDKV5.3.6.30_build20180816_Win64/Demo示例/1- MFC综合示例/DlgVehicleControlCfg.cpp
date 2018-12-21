// DlgVehicleCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVehicleControlCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVehicleControlCfg dialog


CDlgVehicleControlCfg::CDlgVehicleControlCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVehicleControlCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVehicleControlCfg)
	m_iHour12 = 0;
	m_iHour11 = 0;
	m_iHour21 = 0;
	m_iHour22 = 0;
	m_Min11 = 0;
	m_Min12 = 0;
	m_Min21 = 0;
	m_Min22 = 0;
	m_iMaxXAcc = 0;
	m_iMaxYAcc = 0;
	m_iMaxZAcc = 0;
	m_bGAlarmout = FALSE;
	m_bGMonitor = FALSE;
	m_bGCenter = FALSE;
	m_bGVoice = FALSE;
	m_bGJpegCapture = FALSE;
	m_bGpsInvokeAlarmout = FALSE;
	m_strDownloadServer = _T("");
	m_bEnableGps = FALSE;
	m_iGpsSpeedLimit = 0;
	m_bGpsAlarmMonitor = FALSE;
	m_bGpsUploadCenter = FALSE;
	m_bGpsVoice = FALSE;
	m_bGpsJpegCapture = FALSE;
	m_iGpsInterval = 0;
	m_bEnableBackup = FALSE;
	m_bNeedBackup = FALSE;
	m_iBackupDays = 0;
	m_iStartMin1 = 0;
	m_iStartMin2 = 0;
	m_iStopMinute1 = 0;
	m_iStopMinute2 = 0;
	m_iStartHour1 = 0;
	m_iStartHour2 = 0;
	m_iStopHour1 = 0;
	m_iStopHour2 = 0;
	m_bEnableUnderProtect = FALSE;
	//}}AFX_DATA_INIT
	memset(&m_struPowerCtrlParam, 0, sizeof(m_struPowerCtrlParam));
	memset(&m_struGsensorPara, 0, sizeof(m_struGsensorPara));
	memset(&m_struAutoBackParam, 0, sizeof(m_struAutoBackParam));
	memset(&m_struGpsParam, 0, sizeof(m_struGpsParam));
	memset(&m_struSensorParam, 0, sizeof(m_struSensorParam));
	memset(&m_struDownloadParam, 0, sizeof(m_struDownloadParam));
	m_lServerID = -1;
	memset(&m_bGpsAlarmOut[0], 0 ,sizeof(BOOL)*MAX_ALARMOUT_V30);
	memset(&m_bGSensorAlarmOut[0], 0 ,sizeof(BOOL)*MAX_ALARMOUT_V30);
	memset(&m_bGpsOsdChan[0], 0 ,sizeof(BOOL)*MAX_CHANNUM_V30);
	memset(&m_bSensorOsdChan[0], 0 ,sizeof(BOOL)*MAX_CHANNUM_V30);
}

void CDlgVehicleControlCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVehicleControlCfg)
	DDX_Control(pDX, IDC_COMBO_UNDER_VOLT_PERCENT, m_UnderVoltPercent);
	DDX_Control(pDX, IDC_GPSADJUSTTIME, m_AdjustTimeCtrl);
	DDX_Control(pDX, IDC_COMBO_CHAN, m_ChanCtrl);
	DDX_Control(pDX, IDC_COMBO_BACKUPFILETYPE, m_BackupFileTypeCtrl);
	DDX_Control(pDX, IDC_GPSSPEEDUNIT, m_GpsSpeedUnitCtrl);
	DDX_Control(pDX, IDC_GPSRETRIEVE, m_GpsRetrieveCtrl);
	DDX_Control(pDX, IDC_GPSCONNECT, m_GpsConnectCtrl);
	DDX_Control(pDX, IDC_GPSADJUST, m_GpsAdjustCtrl);
	DDX_Control(pDX, IDC_SENSOR_TRIGGERCHAN4, m_TriggerChan4Ctrl);
	DDX_Control(pDX, IDC_SENSOR_TRIGGERCHAN3, m_TriggerChan3Ctrl);
	DDX_Control(pDX, IDC_SENSOR_TRIGGERCHAN2, m_TriggerChan2Ctrl);
	DDX_Control(pDX, IDC_SENSOR_TRIGGERCHAN1, m_TriggerChan1Ctrl);
	DDX_Control(pDX, IDC_SENSOR_ELECTRIC4, m_Electric4Ctrl);
	DDX_Control(pDX, IDC_SENSOR_ELECTRIC3, m_Electric3Ctrl);
	DDX_Control(pDX, IDC_SENSOR_ELECTRIC2, m_Electric2Ctrl);
	DDX_Control(pDX, IDC_SENSOR_ELECTRIC1, m_Electric1Ctrl);
	DDX_Control(pDX, IDC_TREE_SENSORIN, m_SensorTree);
	DDX_Control(pDX, IDC_TREE_ADDOSD, m_GpsOsdTree);
	DDX_Control(pDX, IDC_TREE_ALARM_OUT, m_treeGpsAlarmout);
	DDX_Control(pDX, IDC_TREE_ALARM_OUT_G, m_GAlarmTree);
	DDX_Control(pDX, IDC_COMBO_MODULESELECT, m_ModuleSelectCtrl);
	DDX_Control(pDX, IDC_COMBOHALTDELAY, m_HaltDelayCtrl);
	DDX_Control(pDX, IDC_COMBOPOWERCTRLMODE, m_PowerCtrlMode);
	DDX_Control(pDX, IDC_COMBOWEEKDAY, m_WeekdayCtrl);
	DDX_Text(pDX, IDC_EDITHOUR012, m_iHour12);
	DDX_Text(pDX, IDC_EDITHOUR011, m_iHour11);
	DDX_Text(pDX, IDC_EDITHOUR021, m_iHour21);
	DDX_Text(pDX, IDC_EDITHOUR022, m_iHour22);
	DDX_Text(pDX, IDC_EDITMIN011, m_Min11);
	DDX_Text(pDX, IDC_EDITMIN012, m_Min12);
	DDX_Text(pDX, IDC_EDITMIN021, m_Min21);
	DDX_Text(pDX, IDC_EDITMIN022, m_Min22);
	DDX_Text(pDX, IDC_EDIT_MAXXACC, m_iMaxXAcc);
	DDX_Text(pDX, IDC_EDIT_MAXYACC, m_iMaxYAcc);
	DDX_Text(pDX, IDC_EDIT_MAXZACC, m_iMaxZAcc);
	DDX_Check(pDX, IDC_CHK_ALARMIN_INVOKE_ALARMOUT_G, m_bGAlarmout);
	DDX_Check(pDX, IDC_CHK_ALARMIN_MONITOR_G, m_bGMonitor);
	DDX_Check(pDX, IDC_CHK_ALARMIN_UPLOAD_CENTER_G, m_bGCenter);
	DDX_Check(pDX, IDC_CHK_ALARMIN_VOICE_G, m_bGVoice);
	DDX_Check(pDX, IDC_CHK_INVOKE_JPEG_CAPTURE_G, m_bGJpegCapture);
	DDX_Check(pDX, IDC_CHK_ALARMIN_INVOKE_ALARMOUT, m_bGpsInvokeAlarmout);
	DDX_Text(pDX, IDC_EDIT_DOWNLOADSERVER, m_strDownloadServer);
	DDX_Check(pDX, IDC_GPSENABLE, m_bEnableGps);
	DDX_Text(pDX, IDC_GPSSPEEDLIMIT, m_iGpsSpeedLimit);
	DDX_Check(pDX, IDC_CHK_ALARMIN_MONITOR_GPS, m_bGpsAlarmMonitor);
	DDX_Check(pDX, IDC_CHK_ALARMIN_UPLOAD_CENTER_GPS, m_bGpsUploadCenter);
	DDX_Check(pDX, IDC_CHK_ALARMIN_VOICE_GPS, m_bGpsVoice);
	DDX_Check(pDX, IDC_CHK_INVOKE_JPEG_CAPTURE_GPS, m_bGpsJpegCapture);
	DDX_Text(pDX, IDC_EDIT_GPSINTERVAL, m_iGpsInterval);
	DDX_Check(pDX, IDC_CHECK_ENABLEAUTOBACKUP, m_bEnableBackup);
	DDX_Check(pDX, IDC_CHECK_NEEDBACKUP, m_bNeedBackup);
	DDX_Text(pDX, IDC_EDIT_BACKUPDAYS, m_iBackupDays);
	DDX_Text(pDX, IDC_EDIT_STARTMINUTE1, m_iStartMin1);
	DDX_Text(pDX, IDC_EDIT_STARTMINUTE2, m_iStartMin2);
	DDX_Text(pDX, IDC_EDIT_STOPMINUTE1, m_iStopMinute1);
	DDX_Text(pDX, IDC_EDIT_STOPMINUTE2, m_iStopMinute2);
	DDX_Text(pDX, IDC_EDITSTARTHOUR1, m_iStartHour1);
	DDX_Text(pDX, IDC_EDITSTARTHOUR2, m_iStartHour2);
	DDX_Text(pDX, IDC_EDITSTOPHOUR1, m_iStopHour1);
	DDX_Text(pDX, IDC_EDITSTOPHOUR2, m_iStopHour2);
	DDX_Check(pDX, IDC_CHK_ENABLE_UNDER_VOLT_PROTECT, m_bEnableUnderProtect);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVehicleControlCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVehicleControlCfg)
	ON_BN_CLICKED(IDSURE, OnSure)
	ON_BN_CLICKED(IDC_GETAUTOWORK, OnGetautowork)
	ON_BN_CLICKED(IDC_SETAUTOWORK, OnSetautowork)
	ON_CBN_SELCHANGE(IDC_COMBOWEEKDAY, OnSelchangeComboweekday)
	ON_BN_CLICKED(IDC_GETGSENSOR, OnGetgsensor)
	ON_BN_CLICKED(IDC_SETGSENSOR, OnSetgsensor)
	ON_BN_CLICKED(IDC_GETAUTOBACKUP, OnGetautobackup)
	ON_BN_CLICKED(IDC_SETAUTOBACKUP, OnSetautobackup)
	ON_BN_CLICKED(IDC_SETSENSORIN, OnSetsensorin)
	ON_BN_CLICKED(IDC_SETAUTODOWNIP, OnSetautodownip)
	ON_BN_CLICKED(IDC_SETGPSCFG, OnSetgpscfg)
	ON_BN_CLICKED(IDC_GETSENSORIN, OnGetsensorin)
	ON_BN_CLICKED(IDC_GETGPSCFG, OnGetgpscfg)
	ON_BN_CLICKED(IDC_GETAUTODOWNIP, OnGetautodownip)
	ON_BN_CLICKED(IDC_CHK_ALARMIN_INVOKE_ALARMOUT_G, OnChkAlarminInvokeAlarmoutG)
	ON_WM_PAINT()
	ON_NOTIFY(NM_CLICK, IDC_TREE_ALARM_OUT_G, OnClickTreeAlarmOutG)
	ON_BN_CLICKED(IDC_CHK_ALARMIN_INVOKE_ALARMOUT, OnChkAlarminInvokeAlarmout)
	ON_NOTIFY(NM_CLICK, IDC_TREE_ALARM_OUT, OnClickTreeAlarmOut)
	ON_NOTIFY(NM_CLICK, IDC_TREE_ADDOSD, OnClickTreeAddosd)
	ON_NOTIFY(NM_CLICK, IDC_TREE_SENSORIN, OnClickTreeSensorin)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_SURE, OnButtonSure)
	ON_CBN_SELCHANGE(IDC_COMBO_CHAN, OnSelchangeComboChan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVehicleControlCfg message handlers

void CDlgVehicleControlCfg::OnSure() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int sel = m_WeekdayCtrl.GetCurSel();
	m_struPowerCtrlParam.struAutoWorkPara.struWorkTime[sel][0].byStartHour = m_iHour11;
	m_struPowerCtrlParam.struAutoWorkPara.struWorkTime[sel][0].byStopHour = m_iHour12;
	m_struPowerCtrlParam.struAutoWorkPara.struWorkTime[sel][1].byStartHour = m_iHour21;
	m_struPowerCtrlParam.struAutoWorkPara.struWorkTime[sel][1].byStopHour = m_iHour22;

	m_struPowerCtrlParam.struAutoWorkPara.struWorkTime[sel][0].byStartMin = m_Min11;
	m_struPowerCtrlParam.struAutoWorkPara.struWorkTime[sel][0].byStopMin = m_Min12;
	m_struPowerCtrlParam.struAutoWorkPara.struWorkTime[sel][1].byStartMin = m_Min21;
	m_struPowerCtrlParam.struAutoWorkPara.struWorkTime[sel][1].byStopMin = m_Min22;
}

void CDlgVehicleControlCfg::OnGetautowork() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
	m_struPowerCtrlParam.dwSize = sizeof(m_struPowerCtrlParam);
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_MB_POWERCTRLPARA, -1, &m_struPowerCtrlParam, sizeof(m_struPowerCtrlParam), &dwReturn))
	{
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}
	MessageBox("get success!");
	m_PowerCtrlMode.SetCurSel(m_struPowerCtrlParam.struAutoWorkPara.byCurPowerCtrlType -1);
	m_WeekdayCtrl.SetCurSel(0);

	if (m_struPowerCtrlParam.dwHaltDelay % 60 == 0)
	{
		m_HaltDelayCtrl.SetCurSel(11 + m_struPowerCtrlParam.dwHaltDelay / 60);
	}
	else
	{
		m_HaltDelayCtrl.SetCurSel(m_struPowerCtrlParam.dwHaltDelay / 5);
	}
	
	m_bEnableUnderProtect = m_struPowerCtrlParam.byEnableUnderVoltProtect;
	switch (m_struPowerCtrlParam.byUnderVoltPercent)
	{
	case 85:
		m_UnderVoltPercent.SetCurSel(0);
		break;
	case 90:
		m_UnderVoltPercent.SetCurSel(1);
		break;
	case 95:
		m_UnderVoltPercent.SetCurSel(2);
		break;
	default:
		break;
	}
	UpdateData(FALSE);
	OnSelchangeComboweekday();
}

void CDlgVehicleControlCfg::OnSetautowork() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struPowerCtrlParam.struAutoWorkPara.byCurPowerCtrlType = m_PowerCtrlMode.GetCurSel() + 1;
	m_struPowerCtrlParam.dwSize = sizeof(m_struPowerCtrlParam);

	char temp[20] = {0};
	m_HaltDelayCtrl.GetLBText(m_HaltDelayCtrl.GetCurSel(), temp);
	m_struPowerCtrlParam.dwHaltDelay = atoi(temp);
	m_struPowerCtrlParam.byEnableUnderVoltProtect = m_bEnableUnderProtect;
	
	switch (m_UnderVoltPercent.GetCurSel())
	{
	case 0:
		m_struPowerCtrlParam.byUnderVoltPercent = 85;
		break;
	case 1:
		m_struPowerCtrlParam.byUnderVoltPercent = 90;
		break;
	case 2:
		m_struPowerCtrlParam.byUnderVoltPercent = 95;
		break;
	default:
		break;
	}
	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_MB_POWERCTRLPARA, -1, &m_struPowerCtrlParam, sizeof(m_struPowerCtrlParam)))
	{
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}
	else
	{
		MessageBox("set success!");
	}
}

void CDlgVehicleControlCfg::OnSelchangeComboweekday() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int sel = m_WeekdayCtrl.GetCurSel();
	m_iHour11 = m_struPowerCtrlParam.struAutoWorkPara.struWorkTime[sel][0].byStartHour;
	m_iHour12 =	m_struPowerCtrlParam.struAutoWorkPara.struWorkTime[sel][0].byStopHour;
	m_iHour21 =	m_struPowerCtrlParam.struAutoWorkPara.struWorkTime[sel][1].byStartHour;
	m_iHour22 =	m_struPowerCtrlParam.struAutoWorkPara.struWorkTime[sel][1].byStopHour;
	
	m_Min11 = m_struPowerCtrlParam.struAutoWorkPara.struWorkTime[sel][0].byStartMin;
	m_Min12 = m_struPowerCtrlParam.struAutoWorkPara.struWorkTime[sel][0].byStopMin;
	m_Min21 = m_struPowerCtrlParam.struAutoWorkPara.struWorkTime[sel][1].byStartMin;
	m_Min22 = m_struPowerCtrlParam.struAutoWorkPara.struWorkTime[sel][1].byStopMin;
	UpdateData(FALSE);
}

BOOL CDlgVehicleControlCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int i = 0;
	CString tmp;

	for (i = 0; i < m_nChannel; i ++)
	{
		tmp.Format("chan%d", i + m_lStartChan);
		m_TriggerChan1Ctrl.AddString(tmp);
		m_TriggerChan2Ctrl.AddString(tmp);
		m_TriggerChan3Ctrl.AddString(tmp);
		m_TriggerChan4Ctrl.AddString(tmp);
		m_ChanCtrl.AddString(tmp);
	}
	
	//GPSÊ±Çø
	m_AdjustTimeCtrl.AddString("GMT-12:00");
	m_AdjustTimeCtrl.AddString("GMT-11:00");
	m_AdjustTimeCtrl.AddString("GMT-10:00");
	m_AdjustTimeCtrl.AddString("GMT-09:30");
	m_AdjustTimeCtrl.AddString("GMT-09:00");
	m_AdjustTimeCtrl.AddString("GMT-08:00");
	m_AdjustTimeCtrl.AddString("GMT-07:00");
	m_AdjustTimeCtrl.AddString("GMT-06:00");
	m_AdjustTimeCtrl.AddString("GMT-05:00");
	m_AdjustTimeCtrl.AddString("GMT-04:30");
	m_AdjustTimeCtrl.AddString("GMT-04:00");
	m_AdjustTimeCtrl.AddString("GMT-03:30");
	m_AdjustTimeCtrl.AddString("GMT-03:00");
	m_AdjustTimeCtrl.AddString("GMT-02:00");
	m_AdjustTimeCtrl.AddString("GMT-01:00");
	m_AdjustTimeCtrl.AddString("GMT");
	m_AdjustTimeCtrl.AddString("GMT+01:00");
	m_AdjustTimeCtrl.AddString("GMT+02:00");
	m_AdjustTimeCtrl.AddString("GMT+03:00");
	m_AdjustTimeCtrl.AddString("GMT+03:30");
	m_AdjustTimeCtrl.AddString("GMT+04:00");
	m_AdjustTimeCtrl.AddString("GMT+04:30");
	m_AdjustTimeCtrl.AddString("GMT+05:00");
	m_AdjustTimeCtrl.AddString("GMT+05:30");
	m_AdjustTimeCtrl.AddString("GMT+05:45");
	m_AdjustTimeCtrl.AddString("GMT+06:00");
	m_AdjustTimeCtrl.AddString("GMT+06:30");
	m_AdjustTimeCtrl.AddString("GMT+07:00");
	m_AdjustTimeCtrl.AddString("GMT+08:00");
	m_AdjustTimeCtrl.AddString("GMT+09:00");
	m_AdjustTimeCtrl.AddString("GMT+09:30");
	m_AdjustTimeCtrl.AddString("GMT+10:00");
	m_AdjustTimeCtrl.AddString("GMT+10:30");
	m_AdjustTimeCtrl.AddString("GMT+11:00");
	m_AdjustTimeCtrl.AddString("GMT+11:30");
	m_AdjustTimeCtrl.AddString("GMT+12:00");
	m_AdjustTimeCtrl.AddString("GMT+13:00");

	m_GAlarmTree.EnableWindow(m_bGAlarmout);
	m_treeGpsAlarmout.EnableWindow(m_bGpsInvokeAlarmout);
	UpdateData(FALSE);

	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVehicleControlCfg::OnGetgsensor() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
	m_struGsensorPara.dwSize = sizeof(m_struGsensorPara);
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_GSENSORPARA, -1, &m_struGsensorPara, sizeof(m_struGsensorPara), &dwReturn))
	{
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}
	MessageBox("get success!");

	m_GAlarmTree.EnableWindow(m_bGAlarmout);
    memset(&m_bGSensorAlarmOut, 0, sizeof(BOOL) * MAX_ALARMOUT_V30);
    for (int i = 0; i < MAX_ALARMOUT_V30; i++)
    {
        m_bGSensorAlarmOut[i] = (BOOL)m_struGsensorPara.struHandleException.byRelAlarmOut[i];
		TRACE("bGsensor = %d, m_struGsensorPara.balarmout = %d", m_bGSensorAlarmOut[i], m_struGsensorPara.struHandleException.byRelAlarmOut[i]);
    }

	m_ModuleSelectCtrl.SetCurSel(m_struGsensorPara.byModuleSelect);
    m_iMaxXAcc = m_struGsensorPara.struAccelerationCfg.dwMaxXAcc;
    m_iMaxYAcc = m_struGsensorPara.struAccelerationCfg.dwMaxYAcc;
    m_iMaxZAcc = m_struGsensorPara.struAccelerationCfg.dwMaxZAcc;
    m_bGMonitor = m_struGsensorPara.struHandleException.dwHandleType &0x01;
    m_bGVoice = (m_struGsensorPara.struHandleException.dwHandleType>>1)&0x01;
    m_bGCenter = (m_struGsensorPara.struHandleException.dwHandleType>>2)&0x01;
    m_bGAlarmout = (m_struGsensorPara.struHandleException.dwHandleType>>3)&0x01;
    m_bGJpegCapture = (m_struGsensorPara.struHandleException.dwHandleType>>4)&0x01;
	//UpdateData(FALSE);
	m_GAlarmTree.EnableWindow(m_bGAlarmout);
	CreateTree();
}

void CDlgVehicleControlCfg::OnSetgsensor() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	memset(&m_struGsensorPara, 0, sizeof(m_struGsensorPara));
	m_struGsensorPara.dwSize = sizeof(m_struGsensorPara);
	m_struGsensorPara.byModuleSelect = m_ModuleSelectCtrl.GetCurSel();
    m_struGsensorPara.struAccelerationCfg.dwMaxXAcc = m_iMaxXAcc;
    m_struGsensorPara.struAccelerationCfg.dwMaxYAcc = m_iMaxYAcc;
    m_struGsensorPara.struAccelerationCfg.dwMaxZAcc = m_iMaxZAcc;
    m_struGsensorPara.struHandleException.dwHandleType |= (m_bGMonitor << 0);
    m_struGsensorPara.struHandleException.dwHandleType |= (m_bGVoice << 1);
    m_struGsensorPara.struHandleException.dwHandleType |= (m_bGCenter << 2);
    m_struGsensorPara.struHandleException.dwHandleType |= (m_bGAlarmout << 3);
    m_struGsensorPara.struHandleException.dwHandleType |= (m_bGJpegCapture << 4);

	for (int i = 0; i < MAX_ALARMOUT_V30; i++)
    {
        m_struGsensorPara.struHandleException.byRelAlarmOut[i] = (BYTE)m_bGSensorAlarmOut[i];
    }

	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_GSENSORPARA, -1, &m_struGsensorPara, sizeof(m_struGsensorPara)))
	{
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}
	else
	{
		MessageBox("set success!");
	}
}

void CDlgVehicleControlCfg::OnGetautobackup() 
{
	DWORD dwReturn = 0;
	m_struAutoBackParam.dwSize = sizeof(m_struAutoBackParam);
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_AUTOBACKUPPARA, -1, &m_struAutoBackParam, sizeof(m_struAutoBackParam), &dwReturn))
	{
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}
	MessageBox("get success!");
	
	m_bEnableBackup = m_struAutoBackParam.byEnableAutoBackup;
	m_ChanCtrl.SetCurSel(0);
	int sel = 0;
	m_bNeedBackup = m_struAutoBackParam.byBackupChannel[sel];
	m_iBackupDays = m_struAutoBackParam.byBackupDays[sel];
	m_BackupFileTypeCtrl.SetCurSel(m_struAutoBackParam.byBackupFileType[sel]);
	m_iStartHour1 = m_struAutoBackParam.struBackupTime[sel][0].byStartHour;
	m_iStartHour2 = m_struAutoBackParam.struBackupTime[sel][1].byStartHour;
	m_iStopHour1 = m_struAutoBackParam.struBackupTime[sel][0].byStopHour;  
	m_iStopHour2 = m_struAutoBackParam.struBackupTime[sel][1].byStopHour;  
	m_iStartMin1 = m_struAutoBackParam.struBackupTime[sel][0].byStartMin;  
	m_iStartMin2 = m_struAutoBackParam.struBackupTime[sel][1].byStartMin; 
	m_iStopMinute1 = m_struAutoBackParam.struBackupTime[sel][0].byStopMin;   
	m_iStopMinute2 = m_struAutoBackParam.struBackupTime[sel][1].byStopMin;
	UpdateData(FALSE);
	//OnSelchangeComboChan();
}

void CDlgVehicleControlCfg::OnSetautobackup() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	m_struAutoBackParam.dwSize = sizeof(m_struAutoBackParam);
	m_struAutoBackParam.byEnableAutoBackup = m_bEnableBackup;
	
	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_AUTOBACKUPPARA, -1, &m_struAutoBackParam, sizeof(m_struAutoBackParam)))
	{
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}
	else
	{
		MessageBox("set success!");
	}
}

void CDlgVehicleControlCfg::OnSetsensorin() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	memset(&m_struSensorParam, 0, sizeof(m_struSensorParam));

	m_struSensorParam.dwSize = sizeof(m_struSensorParam);

	for (int i = 0; i < MAX_CHANNUM_V30; i++)
	{
		m_struSensorParam.byOsdDisplay[i] = (BYTE)m_bSensorOsdChan[i];
	}
	
	m_struSensorParam.byTriggerChannel[0] = m_TriggerChan1Ctrl.GetCurSel() + m_lStartChan;
	m_struSensorParam.byTriggerChannel[1] = m_TriggerChan2Ctrl.GetCurSel() + m_lStartChan;
	m_struSensorParam.byTriggerChannel[2] = m_TriggerChan3Ctrl.GetCurSel() + m_lStartChan;
	m_struSensorParam.byTriggerChannel[3] = m_TriggerChan4Ctrl.GetCurSel() + m_lStartChan;

	m_struSensorParam.byTriggerType[0] = m_Electric1Ctrl.GetCurSel();
	m_struSensorParam.byTriggerType[1] = m_Electric2Ctrl.GetCurSel();
	m_struSensorParam.byTriggerType[2] = m_Electric3Ctrl.GetCurSel();
	m_struSensorParam.byTriggerType[3] = m_Electric4Ctrl.GetCurSel();

	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_MB_SENSORINPARA, -1, &m_struSensorParam, sizeof(m_struSensorParam)))
	{
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}
	else
	{
		MessageBox("set success!");
	}
}

void CDlgVehicleControlCfg::OnSetautodownip() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	m_struDownloadParam.dwSize = sizeof(m_struDownloadParam);
	memcpy(m_struDownloadParam.struDownloadSvrIp.sIpV4, m_strDownloadServer, 16);
	
	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_MB_DOWNLOADSVRPARA, -1, &m_struDownloadParam, sizeof(m_struDownloadParam)))
	{
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}
	else
	{
		MessageBox("set success!");
	}
}

void CDlgVehicleControlCfg::OnSetgpscfg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	memset(&m_struGpsParam, 0, sizeof(m_struGpsParam));

	m_struGpsParam.dwSize = sizeof(m_struGpsParam);

	int i = 0;
	for (i = 0; i < MAX_ALARMOUT_V30; i++)
    {
        m_struGpsParam.struGpsAlarm.byRelAlarmOut[i] = (BYTE)m_bGpsAlarmOut[i];
    }

	for (i = 0; i < MAX_CHANNUM_V30; i++)
	{
		m_struGpsParam.byGpsOsdChannel[i] = (BYTE)m_bGpsOsdChan[i];
	}

	m_struGpsParam.byEnableGPS = m_bEnableGps;
	m_struGpsParam.byGpsInterface = m_GpsConnectCtrl.GetCurSel();
	m_struGpsParam.byEnableAdjustTime = m_GpsAdjustCtrl.GetCurSel();
	m_struGpsParam.byEnableRetrieve = m_GpsRetrieveCtrl.GetCurSel();
	m_struGpsParam.bySpeedUnit = m_GpsSpeedUnitCtrl.GetCurSel();
	m_struGpsParam.dwSpeedLimit = m_iGpsSpeedLimit;
	m_struGpsParam.wGpsUploadInterval = m_iGpsInterval;

	m_struGpsParam.struGpsAlarm.dwHandleType |= (m_bGpsAlarmMonitor << 0);
    m_struGpsParam.struGpsAlarm.dwHandleType |= (m_bGpsVoice << 1);
    m_struGpsParam.struGpsAlarm.dwHandleType |= (m_bGpsUploadCenter << 2);
    m_struGpsParam.struGpsAlarm.dwHandleType |= (m_bGpsInvokeAlarmout << 3);
    m_struGpsParam.struGpsAlarm.dwHandleType |= (m_bGpsJpegCapture << 4);
	
	switch (m_AdjustTimeCtrl.GetCurSel())
	{
	case 0:
		m_struGpsParam.iAdjustTime = -12 * 3600;
		break;
	case 1:
		m_struGpsParam.iAdjustTime = -11 * 3600;
		break;
	case 2:
		m_struGpsParam.iAdjustTime = -10 * 3600;
		break;
	case 3:
		m_struGpsParam.iAdjustTime = -9 * 3600 - 1800;
		break;
	case 4:
		m_struGpsParam.iAdjustTime = -9 * 3600;
		break;
	case 5:
		m_struGpsParam.iAdjustTime = -8 * 3600;
		break;
	case 6:
		m_struGpsParam.iAdjustTime = -7 * 3600;
		break;
	case 7:
		m_struGpsParam.iAdjustTime = -6 * 3600;
		break;
	case 8:
		m_struGpsParam.iAdjustTime = -5 * 3600;
		break;
	case 9:
		m_struGpsParam.iAdjustTime = -4 * 3600 - 1800;
		break;
	case 10:
		m_struGpsParam.iAdjustTime = -4 * 3600;
		break;
	case 11:
		m_struGpsParam.iAdjustTime = -3 * 3600 - 1800;
		break;
	case 12:
		m_struGpsParam.iAdjustTime = -3 * 3600;
		break;
	case 13:
		m_struGpsParam.iAdjustTime = -2 * 3600;
		break;
	case 14:
		m_struGpsParam.iAdjustTime = -1 * 3600;
		break;
	case 15:
		m_struGpsParam.iAdjustTime = 0;
		break;
	case 16:
		m_struGpsParam.iAdjustTime = 1 * 3600;
		break;
	case 17:
		m_struGpsParam.iAdjustTime = 2 * 3600;
		break;
	case 18:
		m_struGpsParam.iAdjustTime = 3 * 3600;
		break;
	case 19:
		m_struGpsParam.iAdjustTime = 3 * 3600 + 1800;
		break;
	case 20:
		m_struGpsParam.iAdjustTime = 4 * 3600;
		break;
	case 21:
		m_struGpsParam.iAdjustTime = 4 * 3600 + 1800;
		break;
	case 22:
		m_struGpsParam.iAdjustTime = 5 * 3600;
		break;
	case 23:
		m_struGpsParam.iAdjustTime = 5 * 3600 + 1800;
		break;
	case 24:
		m_struGpsParam.iAdjustTime = 5 * 3600 + 2700;
		break;
	case 25:
		m_struGpsParam.iAdjustTime = 6 * 3600;
		break;
	case 26:
		m_struGpsParam.iAdjustTime = 6 * 3600 + 1800;
		break;
	case 27:
		m_struGpsParam.iAdjustTime = 7 * 3600;
		break;
	case 28:
		m_struGpsParam.iAdjustTime = 8 * 3600;
		break;
	case 29:
		m_struGpsParam.iAdjustTime = 9 * 3600;
		break;
	case 30:
		m_struGpsParam.iAdjustTime = 9 * 3600 + 1800;
		break;
	case 31:
		m_struGpsParam.iAdjustTime = 10 * 3600;
		break;
	case 32:
		m_struGpsParam.iAdjustTime = 10 * 3600 + 1800;
		break;
	case 33:
		m_struGpsParam.iAdjustTime = 11 * 3600;
		break;
	case 34:
		m_struGpsParam.iAdjustTime = 11 * 3600 + 1800;
		break;
	case 35:
		m_struGpsParam.iAdjustTime = 12 * 3600;
		break;
	case 36:
		m_struGpsParam.iAdjustTime = 12 * 3600 + 1800;
		break;
	case 37:
		m_struGpsParam.iAdjustTime = 13 * 3600;
		break;
	default:
		m_struGpsParam.iAdjustTime = -1;
	}
	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_MB_GPSPARA, -1, &m_struGpsParam, sizeof(m_struGpsParam)))
	{
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}
	else
	{
		MessageBox("set success!");
	}
}

void CDlgVehicleControlCfg::OnGetsensorin() 
{
	DWORD dwReturn = 0;
	m_struSensorParam.dwSize = sizeof(m_struSensorParam);
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_MB_SENSORINPARA, -1, &m_struSensorParam, sizeof(m_struSensorParam), &dwReturn))
	{
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}
	MessageBox("get success!");
	
	int i = 0;
	for (i = 0; i < MAX_CHANNUM_V30; i++)
	{
		m_bSensorOsdChan[i] = (BOOL)m_struSensorParam.byOsdDisplay[i];
	}

	m_Electric1Ctrl.SetCurSel(m_struSensorParam.byTriggerType[0]);
	m_Electric2Ctrl.SetCurSel(m_struSensorParam.byTriggerType[1]);
	m_Electric3Ctrl.SetCurSel(m_struSensorParam.byTriggerType[2]);
	m_Electric4Ctrl.SetCurSel(m_struSensorParam.byTriggerType[3]);

	m_TriggerChan1Ctrl.SetCurSel(m_struSensorParam.byTriggerChannel[0] - m_lStartChan);
	m_TriggerChan2Ctrl.SetCurSel(m_struSensorParam.byTriggerChannel[1] - m_lStartChan);
	m_TriggerChan3Ctrl.SetCurSel(m_struSensorParam.byTriggerChannel[2] - m_lStartChan);
	m_TriggerChan4Ctrl.SetCurSel(m_struSensorParam.byTriggerChannel[3] - m_lStartChan);
	CreateTree();
	//UpdateData(FALSE);
}

void CDlgVehicleControlCfg::OnGetgpscfg() 
{
	DWORD dwReturn = 0;
	m_struGpsParam.dwSize = sizeof(m_struGpsParam);
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_MB_GPSPARA, -1, &m_struGpsParam, sizeof(m_struGpsParam), &dwReturn))
	{
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}
	MessageBox("get success!");
	
	m_treeGpsAlarmout.EnableWindow(m_bGpsInvokeAlarmout);
    memset(&m_bGpsAlarmOut, 0, sizeof(BOOL) * MAX_ALARMOUT_V30);
	int i = 0;
    for (i = 0; i < MAX_ALARMOUT_V30; i++)
    {
        m_bGpsAlarmOut[i] = (BOOL)m_struGpsParam.struGpsAlarm.byRelAlarmOut[i];
	}

	for (i = 0; i < MAX_CHANNUM_V30; i++)
	{
		m_bGpsOsdChan[i] = (BOOL)m_struGpsParam.byGpsOsdChannel[i];
	}

	m_bEnableGps = m_struGpsParam.byEnableGPS;
	m_GpsConnectCtrl.SetCurSel(m_struGpsParam.byGpsInterface);
	m_GpsAdjustCtrl.SetCurSel(m_struGpsParam.byEnableAdjustTime);
	m_GpsSpeedUnitCtrl.SetCurSel(m_struGpsParam.bySpeedUnit);
	m_GpsRetrieveCtrl.SetCurSel(m_struGpsParam.byEnableRetrieve);
	m_iGpsInterval = m_struGpsParam.wGpsUploadInterval;
	m_iGpsSpeedLimit = m_struGpsParam.dwSpeedLimit;

	m_bGpsAlarmMonitor = m_struGpsParam.struGpsAlarm.dwHandleType&0x01;
    m_bGpsVoice = (m_struGpsParam.struGpsAlarm.dwHandleType>>1)&0x01;
    m_bGpsUploadCenter = (m_struGpsParam.struGpsAlarm.dwHandleType>>2)&0x01;
    m_bGpsInvokeAlarmout = (m_struGpsParam.struGpsAlarm.dwHandleType>>3)&0x01;
    m_bGpsJpegCapture = (m_struGpsParam.struGpsAlarm.dwHandleType>>4)&0x01;
	switch (m_struGpsParam.iAdjustTime)
	{
	case -12 * 3600:
		m_AdjustTimeCtrl.SetCurSel(0);
		break;
	case -11 * 3600:
		m_AdjustTimeCtrl.SetCurSel(1);
		break;
	case -10 * 3600:
		m_AdjustTimeCtrl.SetCurSel(2);
		break;
	case -9 * 3600 - 1800:
		m_AdjustTimeCtrl.SetCurSel(3);
		break;
	case -9 * 3600:
		m_AdjustTimeCtrl.SetCurSel(4);
		break;
	case -8 * 3600:
		m_AdjustTimeCtrl.SetCurSel(5);
		break;
	case -7 * 3600:
		m_AdjustTimeCtrl.SetCurSel(6);
		break;
	case -6 * 3600:
		m_AdjustTimeCtrl.SetCurSel(7);
		break;
	case -5 * 3600:
		m_AdjustTimeCtrl.SetCurSel(8);
		break;
	case -4 * 3600 - 1800:
		m_AdjustTimeCtrl.SetCurSel(9);
		break;
	case -4 * 3600:
		m_AdjustTimeCtrl.SetCurSel(10);
		break;
	case -3 * 3600 - 1800:
		m_AdjustTimeCtrl.SetCurSel(11);
		break;
	case -3 * 3600:
		m_AdjustTimeCtrl.SetCurSel(12);
		break;
	case -2 * 3600:
		m_AdjustTimeCtrl.SetCurSel(13);
		break;
	case -1 * 3600:
		m_AdjustTimeCtrl.SetCurSel(14);
		break;
	case 0:
		m_AdjustTimeCtrl.SetCurSel(15);
		break;
	case 1 * 3600:
		m_AdjustTimeCtrl.SetCurSel(16);
		break;
	case 2 * 3600:
		m_AdjustTimeCtrl.SetCurSel(17);
		break;
	case 3 * 3600:
		m_AdjustTimeCtrl.SetCurSel(18);
		break;
	case 3 * 3600 + 1800:
		m_AdjustTimeCtrl.SetCurSel(19);
		break;
	case 4 * 3600:
		m_AdjustTimeCtrl.SetCurSel(20);
		break;
	case 4 * 3600 + 1800:
		m_AdjustTimeCtrl.SetCurSel(21);
		break;
	case 5 * 3600:
		m_AdjustTimeCtrl.SetCurSel(22);
		break;
	case 5 * 3600 + 1800:
		m_AdjustTimeCtrl.SetCurSel(23);
		break;
	case 5 * 3600 + 2700:
		m_AdjustTimeCtrl.SetCurSel(24);
		break;
	case 6 * 3600:
		m_AdjustTimeCtrl.SetCurSel(25);
		break;
	case 6 * 3600 + 1800:
		m_AdjustTimeCtrl.SetCurSel(26);
		break;
	case 7 * 3600:
		m_AdjustTimeCtrl.SetCurSel(27);
		break;
	case 8 * 3600:
		m_AdjustTimeCtrl.SetCurSel(28);
		break;
	case 9 * 3600:
		m_AdjustTimeCtrl.SetCurSel(29);
		break;
	case 9 * 3600 + 1800:
		m_AdjustTimeCtrl.SetCurSel(30);
		break;
	case 10 * 3600:
		m_AdjustTimeCtrl.SetCurSel(31);
		break;
	case 10 * 3600 + 1800:
		m_AdjustTimeCtrl.SetCurSel(32);
		break;
	case 11 * 3600:
		m_AdjustTimeCtrl.SetCurSel(33);
		break;
	case 11 * 3600 + 1800:
		m_AdjustTimeCtrl.SetCurSel(34);
		break;
	case 12 * 3600:
		m_AdjustTimeCtrl.SetCurSel(35);
		break;
	case 12 * 3600 + 1800:
		m_AdjustTimeCtrl.SetCurSel(36);
		break;
	case 13 * 3600:
		m_AdjustTimeCtrl.SetCurSel(37);
		break;
	default:
		m_AdjustTimeCtrl.SetCurSel(-1);
	}
	//UpdateData(FALSE);
	m_treeGpsAlarmout.EnableWindow(m_bGpsInvokeAlarmout);
	CreateTree();
}

void CDlgVehicleControlCfg::OnGetautodownip() 
{
	DWORD dwReturn = 0;
	m_struDownloadParam.dwSize = sizeof(m_struDownloadParam);
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_MB_DOWNLOADSVRPARA, -1, &m_struDownloadParam, sizeof(m_struDownloadParam), &dwReturn))
	{
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}
	MessageBox("get success!");
	
	m_strDownloadServer = m_struDownloadParam.struDownloadSvrIp.sIpV4;
	UpdateData(FALSE);
}

void CDlgVehicleControlCfg::OnChkAlarminInvokeAlarmoutG() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    m_GAlarmTree.EnableWindow(m_bGAlarmout);
	UpdateData(FALSE);
}

void CDlgVehicleControlCfg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CreateTree();
	CDialog::OnPaint();
	// Do not call CDialog::OnPaint() for painting messages
}
/*********************************************************
Function:	CreateTree
Desc:		Create connection between alarm output-channel 
Input:	
Output:	
Return:	
**********************************************************/
void CDlgVehicleControlCfg::CreateTree(void)
{
	g_CreateAlarmOutTree(m_treeGpsAlarmout, m_dwDevIndex, m_bGpsAlarmOut);
    g_CreateAlarmOutTree(m_GAlarmTree, m_dwDevIndex, m_bGSensorAlarmOut);
	
	//GPS OSD
	m_GpsOsdTree.DeleteAllItems();
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0;
	HTREEITEM hChanItem = NULL;
	
	for (i = 0; i < MAX_CHANNUM_V30; i++)
	{
		if (g_struDeviceInfo[m_dwDevIndex].pStruChanInfo[i].bEnable)
		{
			if (i < m_nChannel)
			{
				strTemp.Format(ANALOG_C_FORMAT, i+g_struDeviceInfo[m_dwDevIndex].iStartChan);
				hChanItem =  m_GpsOsdTree.InsertItem(strTemp, TVI_ROOT);
				m_GpsOsdTree.SetItemData(hChanItem, 1*1000 + i);	
				if (m_bGpsOsdChan[i])
				{
					m_GpsOsdTree.SetCheck(hChanItem, TRUE);
				}
			}
			else if (i >= MAX_ANALOG_CHANNUM)
			{
				strTemp.Format(DIGITAL_C_FORMAT, i + g_struDeviceInfo[m_dwDevIndex].iStartChan - MAX_ANALOG_CHANNUM);
				hChanItem =  m_GpsOsdTree.InsertItem(strTemp, TVI_ROOT);
				m_GpsOsdTree.SetItemData(hChanItem, 2*1000 + i);	
				if (m_bGpsOsdChan[i])
				{
					m_GpsOsdTree.SetCheck(hChanItem, TRUE);
				}
			}
		}
	}
	m_GpsOsdTree.Expand(m_GpsOsdTree.GetRootItem(),TVE_EXPAND);	

	//SENSORIN¡¡OSD
	m_SensorTree.DeleteAllItems();
	//CString strTemp =_T("");
	//CString strChanTmp = _T("");
	//int i = 0;
	//HTREEITEM hChanItem = NULL;
	
	for (i = 0; i < MAX_CHANNUM_V30; i++)
	{
		if (g_struDeviceInfo[m_dwDevIndex].pStruChanInfo[i].bEnable)
		{
			if (i < m_nChannel)
			{
				strTemp.Format(ANALOG_C_FORMAT, i+g_struDeviceInfo[m_dwDevIndex].iStartChan);
				hChanItem =  m_SensorTree.InsertItem(strTemp, TVI_ROOT);
				m_SensorTree.SetItemData(hChanItem, 1*1000 + i);	
				if (m_bSensorOsdChan[i])
				{
					m_SensorTree.SetCheck(hChanItem, TRUE);
				}
			}
			else if (i >= MAX_ANALOG_CHANNUM)
			{
				strTemp.Format(DIGITAL_C_FORMAT, i + g_struDeviceInfo[m_dwDevIndex].iStartChan - MAX_ANALOG_CHANNUM);
				hChanItem =  m_SensorTree.InsertItem(strTemp, TVI_ROOT);
				m_SensorTree.SetItemData(hChanItem, 2*1000 + i);	
				if (m_bSensorOsdChan[i])
				{
					m_SensorTree.SetCheck(hChanItem, TRUE);
				}
			}
		}
	}
	m_SensorTree.Expand(m_SensorTree.GetRootItem(),TVE_EXPAND);	
	UpdateData(FALSE);
}

void CDlgVehicleControlCfg::OnClickTreeAlarmOutG(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    CPoint pt(0,0);
    CRect rc(0,0,0,0);
    GetCursorPos(&pt);
    GetDlgItem(IDC_TREE_ALARM_OUT_G)->GetWindowRect(&rc);
    ScreenToClient(&rc);
    ScreenToClient(&pt);
    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;
    
    UINT uFlag = 0;
    HTREEITEM hSelect = m_GAlarmTree.HitTest(pt, &uFlag);
    
    if (NULL == hSelect) 
    {
        return;
    }
    m_GAlarmTree.SelectItem(hSelect);
    DWORD dwIndex = m_GAlarmTree.GetItemData(hSelect)%1000;
    BOOL bCheck = m_GAlarmTree.GetCheck(hSelect);
    m_bGSensorAlarmOut[dwIndex] = !bCheck;
    
    if (uFlag != LVHT_TOLEFT)
    {
        m_GAlarmTree.SetCheck(hSelect, !bCheck);
    }
    else
    {
        m_GAlarmTree.SetCheck(hSelect, bCheck);
    }
    
	*pResult = 0;
}

void CDlgVehicleControlCfg::OnChkAlarminInvokeAlarmout() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    m_treeGpsAlarmout.EnableWindow(m_bGpsInvokeAlarmout);
	UpdateData(FALSE);
}

void CDlgVehicleControlCfg::OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    CPoint pt(0,0);
    CRect rc(0,0,0,0);
    GetCursorPos(&pt);
    GetDlgItem(IDC_TREE_ALARM_OUT)->GetWindowRect(&rc);
    ScreenToClient(&rc);
    ScreenToClient(&pt);
    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;
    
    UINT uFlag = 0;
    HTREEITEM hSelect = m_treeGpsAlarmout.HitTest(pt, &uFlag);
    
    if (NULL == hSelect) 
    {
        return;
    }
    m_treeGpsAlarmout.SelectItem(hSelect);
    DWORD dwIndex = m_treeGpsAlarmout.GetItemData(hSelect)%1000;
    BOOL bCheck = m_treeGpsAlarmout.GetCheck(hSelect);
    m_bGpsAlarmOut[dwIndex] = !bCheck;
    
    if (uFlag != LVHT_TOLEFT)
    {
        m_treeGpsAlarmout.SetCheck(hSelect, !bCheck);
    }
    else
    {
        m_treeGpsAlarmout.SetCheck(hSelect, bCheck);
    }
    
	*pResult = 0;
}

void CDlgVehicleControlCfg::OnClickTreeAddosd(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	CPoint pt(0,0);
	CRect rc(0,0,0,0);
	GetCursorPos(&pt);
	GetDlgItem(IDC_TREE_ADDOSD)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	ScreenToClient(&pt);
	pt.x = pt.x - rc.left;
	pt.y = pt.y - rc.top;
	
	UINT uFlag = 0;
	HTREEITEM hSelect = m_GpsOsdTree.HitTest(pt, &uFlag);
	
	if (NULL == hSelect) 
	{
		return;
	}
	m_GpsOsdTree.SelectItem(hSelect);
	DWORD dwIndex = m_GpsOsdTree.GetItemData(hSelect)%1000;
	BOOL bCheck = m_GpsOsdTree.GetCheck(hSelect);
	m_bGpsOsdChan[dwIndex] = !bCheck;
	//
	if (uFlag != LVHT_TOLEFT)
	{
		m_GpsOsdTree.SetCheck(hSelect, !bCheck);
	}
	else
	{
		m_GpsOsdTree.SetCheck(hSelect, bCheck);
	}
	
	*pResult = 0;
}

void CDlgVehicleControlCfg::OnClickTreeSensorin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	CPoint pt(0,0);
	CRect rc(0,0,0,0);
	GetCursorPos(&pt);
	GetDlgItem(IDC_TREE_SENSORIN)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	ScreenToClient(&pt);
	pt.x = pt.x - rc.left;
	pt.y = pt.y - rc.top;
	
	UINT uFlag = 0;
	HTREEITEM hSelect = m_SensorTree.HitTest(pt, &uFlag);
	
	if (NULL == hSelect) 
	{
		return;
	}
	m_SensorTree.SelectItem(hSelect);
	DWORD dwIndex = m_SensorTree.GetItemData(hSelect)%1000;
	BOOL bCheck = m_SensorTree.GetCheck(hSelect);
	m_bSensorOsdChan[dwIndex] = !bCheck;
	//
	if (uFlag != LVHT_TOLEFT)
	{
		m_SensorTree.SetCheck(hSelect, !bCheck);
	}
	else
	{
		m_SensorTree.SetCheck(hSelect, bCheck);
	}
	
	*pResult = 0;
}

void CDlgVehicleControlCfg::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CDlgVehicleControlCfg::OnButtonSure() 
{
	// TODO: OnButtonSure() Add your control notification handler code here
	UpdateData(TRUE);
	int sel = m_ChanCtrl.GetCurSel();
	m_struAutoBackParam.byBackupChannel[sel] = m_bNeedBackup;
	m_struAutoBackParam.byBackupDays[sel] = m_iBackupDays;
	m_struAutoBackParam.byBackupFileType[sel] = m_BackupFileTypeCtrl.GetCurSel();
	m_struAutoBackParam.struBackupTime[sel][0].byStartHour = m_iStartHour1;
	m_struAutoBackParam.struBackupTime[sel][1].byStartHour = m_iStartHour2;
	m_struAutoBackParam.struBackupTime[sel][0].byStopHour = m_iStopHour1;
	m_struAutoBackParam.struBackupTime[sel][1].byStopHour = m_iStopHour2;
	m_struAutoBackParam.struBackupTime[sel][0].byStartMin = m_iStartMin1;
	m_struAutoBackParam.struBackupTime[sel][1].byStartMin = m_iStartMin2;
	m_struAutoBackParam.struBackupTime[sel][0].byStopMin = m_iStopMinute1;
	m_struAutoBackParam.struBackupTime[sel][1].byStopMin = m_iStopMinute2;
}

void CDlgVehicleControlCfg::OnSelchangeComboChan() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int sel = m_ChanCtrl.GetCurSel();
	m_bNeedBackup = m_struAutoBackParam.byBackupChannel[sel];
	m_iBackupDays = m_struAutoBackParam.byBackupDays[sel];
	m_BackupFileTypeCtrl.SetCurSel(m_struAutoBackParam.byBackupFileType[sel]);
	m_iStartHour1 = m_struAutoBackParam.struBackupTime[sel][0].byStartHour;
	m_iStartHour2 = m_struAutoBackParam.struBackupTime[sel][1].byStartHour;
	m_iStopHour1 = m_struAutoBackParam.struBackupTime[sel][0].byStopHour;  
	m_iStopHour2 = m_struAutoBackParam.struBackupTime[sel][1].byStopHour;  
	m_iStartMin1 = m_struAutoBackParam.struBackupTime[sel][0].byStartMin;  
	m_iStartMin2 = m_struAutoBackParam.struBackupTime[sel][1].byStartMin; 
	m_iStopMinute1 = m_struAutoBackParam.struBackupTime[sel][0].byStopMin;   
	m_iStopMinute2 = m_struAutoBackParam.struBackupTime[sel][1].byStopMin;
	UpdateData(FALSE);
}
