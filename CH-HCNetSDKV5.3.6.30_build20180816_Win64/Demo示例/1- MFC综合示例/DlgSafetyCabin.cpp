// DlgSafetyCabin.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgSafetyCabin.h"
#include "DlgOutputScheduleRuleCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSafetyCabin dialog


CDlgSafetyCabin::CDlgSafetyCabin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSafetyCabin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSafetyCabin)
	m_wCurtainDelay = 0;
	m_wCurtainResponse = 0;
	m_byDevUseTimeOut = 0;
	m_bySensitivity = 0;
	m_wFaintToEmergencyTime = 0;
	m_byFollowDetectorSensitivity = 0;
	m_byManyPersonSensitivity = 0;
	//}}AFX_DATA_INIT
}


void CDlgSafetyCabin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSafetyCabin)
	DDX_Control(pDX, IDC_COMBO_WORK_MODE, m_comboWorkMode);
	DDX_Control(pDX, IDC_COMBO_SENSOR_TYPE, m_comboSensorType);
	DDX_Control(pDX, IDC_COMBO_FAINT_LOCK_ON, m_comboFaintToUnlock);
	DDX_Control(pDX, IDC_COMBO_OVERTIME_LOCK_ON, m_comboOverTimeToUnlock);
	DDX_Text(pDX, IDC_EDIT_CURTAIN_DELAY, m_wCurtainDelay);
	DDX_Text(pDX, IDC_EDIT_CURTAIN_RESPONSE, m_wCurtainResponse);
	DDV_MinMaxInt(pDX, m_wCurtainResponse, 0, 300);
	DDX_Text(pDX, IDC_EDIT_DEVUSE_TIMEOUT, m_byDevUseTimeOut);
	DDV_MinMaxByte(pDX, m_byDevUseTimeOut, 5, 30);
	DDX_Text(pDX, IDC_EDIT_SENSITIVITY, m_bySensitivity);
	DDV_MinMaxByte(pDX, m_bySensitivity, 0, 100);
	DDX_Text(pDX, IDC_EDIT_FAINT_TO_ALARM, m_wFaintToEmergencyTime);
	DDV_MinMaxInt(pDX, m_wFaintToEmergencyTime, 10, 300);
	DDX_Text(pDX, IDC_EDIT_FOLLOW_SENSITIVITY, m_byFollowDetectorSensitivity);
	DDV_MinMaxByte(pDX, m_byFollowDetectorSensitivity, 0, 100);
	DDX_Text(pDX, IDC_EDIT_MANYPERSON_SENSITIVITY, m_byManyPersonSensitivity);
	DDV_MinMaxByte(pDX, m_byManyPersonSensitivity, 0, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSafetyCabin, CDialog)
	//{{AFX_MSG_MAP(CDlgSafetyCabin)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_OUTPUT_SCHEDULE_CFG, OnBtnOutputScheduleCfg)
	ON_BN_CLICKED(IDC_BTN_ONE_OUTPUT_SCHEDULE_CFG, OnBtnOneOutputScheduleCfg)
	ON_BN_CLICKED(IDC_BTN_SAFECABIN_STATE, OnBtnSafecabinState)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSafetyCabin message handlers

BOOL CDlgSafetyCabin::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	char szLan[128] = {0};
	// TODO: Add extra initialization here
	if (!NET_DVR_GetDeviceAbility(m_lUserID, ALARMHOST_ABILITY, NULL, 0, (char*)&m_struAblity, sizeof(m_struAblity)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "ALARMHOST_ABILITY");
		g_StringLanType(szLan, "获取能力集失败", "Get ability fail");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "ALARMHOST_ABILITY");
	}

    OnBtnGet() ;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSafetyCabin::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	m_struWorkMode.dwSize = sizeof(NET_DVR_SAFETYCABIN_WORK_MODE);
	m_struWorkMode.byWorkMode = m_comboWorkMode.GetCurSel();
	m_struWorkMode.byFaintToUnlock = m_comboFaintToUnlock.GetCurSel();
	m_struWorkMode.byOvertimeToUnlock = m_comboOverTimeToUnlock.GetCurSel();

	m_struPersonSignalCfg.dwSize = sizeof(NET_DVR_SAFETYCABIN_PERSON_SIGNAL_CFG);
	m_struPersonSignalCfg.bySensorType = m_comboSensorType.GetCurSel();
	m_struPersonSignalCfg.bySensitivity = m_bySensitivity;
	m_struPersonSignalCfg.byDevUseTimeout = m_byDevUseTimeOut;
	m_struPersonSignalCfg.wCurtainDelayTime = m_wCurtainDelay;
	m_struPersonSignalCfg.wCurtainResponseTime = m_wCurtainResponse;
	m_struPersonSignalCfg.wFaintToEmergencyTime = m_wFaintToEmergencyTime;
	m_struPersonSignalCfg.byFollowDetectorSensitivity = m_byFollowDetectorSensitivity;
	m_struPersonSignalCfg.byManyPersonSensitivity = m_byManyPersonSensitivity;

	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_SAFETYCABIN_WORK_MODE, 0, &m_struWorkMode, sizeof(m_struWorkMode)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SAFETYCABIN_WORK_MODE");
		g_StringLanType(szLan, "设置防护舱工作模式失败", "Set safety cabin work mode fail");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_SAFETYCABIN_WORK_MODE");
	}

	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_SAFETYCABIN_PERSON_SIGNAL_CFG, 0, &m_struPersonSignalCfg, sizeof(m_struPersonSignalCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SAFETYCABIN_PERSON_SIGNAL_CFG");
		g_StringLanType(szLan, "设置人信号探测参数失败", "Set person signal config fail");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_SAFETYCABIN_PERSON_SIGNAL_CFG");
	}
}

void CDlgSafetyCabin::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	DWORD dwReturned = 0;
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_SAFETYCABIN_WORK_MODE, 0, &m_struWorkMode, sizeof(m_struWorkMode), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SAFETYCABIN_WORK_MODE");
		g_StringLanType(szLan, "获取防护舱工作模式失败", "Get safety cabin work mode fail");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SAFETYCABIN_WORK_MODE");
	}
	
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_SAFETYCABIN_PERSON_SIGNAL_CFG, 0, &m_struPersonSignalCfg, sizeof(m_struPersonSignalCfg), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SAFETYCABIN_PERSON_SIGNAL_CFG");
		g_StringLanType(szLan, "获取人信号探测参数失败", "Get person signal config fail");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SAFETYCABIN_PERSON_SIGNAL_CFG");
	}

	m_comboWorkMode.SetCurSel(m_struWorkMode.byWorkMode);
	m_comboFaintToUnlock.SetCurSel(m_struWorkMode.byFaintToUnlock);
	m_comboOverTimeToUnlock.SetCurSel(m_struWorkMode.byOvertimeToUnlock);

	m_comboSensorType.SetCurSel(m_struPersonSignalCfg.bySensorType);
	
	m_bySensitivity = m_struPersonSignalCfg.bySensitivity;
	m_byDevUseTimeOut = m_struPersonSignalCfg.byDevUseTimeout;
	m_wCurtainDelay = m_struPersonSignalCfg.wCurtainDelayTime;
	m_wCurtainResponse = m_struPersonSignalCfg.wCurtainResponseTime;
	m_wFaintToEmergencyTime = m_struPersonSignalCfg.wFaintToEmergencyTime;
	m_byFollowDetectorSensitivity = m_struPersonSignalCfg.byFollowDetectorSensitivity;
	m_byManyPersonSensitivity = m_struPersonSignalCfg.byManyPersonSensitivity;

	UpdateData(FALSE);
}

void CDlgSafetyCabin::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CDlgSafetyCabin::OnBtnOutputScheduleCfg() 
{
	CDlgOutputScheduleRuleCfg dlg;
	dlg.m_lUserID      = m_lUserID;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.DoModal();
}


#include "DlgOneOutputScheduleRuleCfg.h"
void CDlgSafetyCabin::OnBtnOneOutputScheduleCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgOneOutputScheduleRuleCfg dlg;
	dlg.m_lUserID      = m_lUserID;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.DoModal();
}

#include "DlgSafeCabinState.h"
void CDlgSafetyCabin::OnBtnSafecabinState() 
{
	// TODO: Add your control notification handler code here
	CDlgSafeCabinState dlg;
	dlg.m_lUserID      = m_lUserID;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.DoModal();
}


