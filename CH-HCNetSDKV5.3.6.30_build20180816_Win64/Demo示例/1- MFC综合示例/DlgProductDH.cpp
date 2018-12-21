// DlgProductDH.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgProductDH.h"
#include "afxdialogex.h"
#include "DlgAlarmhostHistoryData.h"
#include "DlgAlarmhostPointCfg.h"
#include "DlgAlarmhostSensorLinkage.h"
#include "DlgScaleOutCfg.h"
#include "DlgAlarmhostDataUploadMode.h"
#include "DlgAlarmHostRs485.h"
#include "DlgAlarmHostExternalDevState.h"
#include "DlgAlarmHostLogSearch.h"
#include "DlgAlarmhostExternalDevLimitValue.h"
#include "DlgGetAllPointCfg.h"
#include "DlgGetAllSensor.h"
#include "DlgGetAllRs485Cfg.h"
#include "DlgGetAllRs485Slot.h"
#include "DlgDeviceSelfCheckState.h"
#include "DlgRS485ProtocolVersion.h"
#include "DlgAlarmHostZoneCfg.h"
#include "DlgAlarmOutCfg.h"
#include "DlgAlarmHostEnableCfg.h"
#include "DlgAlarmHostAbility.h"
#include "DlgAlarmNetUser.h"
#include "DlgAlarmOperatorUser.h"
#include "DlgAlarmHostStatus.h"
#include "DlgRS485DLLParamCfg.h"
// CDlgProductDH 对话框

IMPLEMENT_DYNAMIC(CDlgProductDH, CDialog)

CDlgProductDH::CDlgProductDH(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProductDH::IDD, pParent)
{
    m_iDevIndex = -1;
    m_lServerID = -1;
    m_lStartChan = -1;
    m_lChannel = -1;
    m_bInit = FALSE;
    memset(&m_struAlarmHostAbility, 0, sizeof(m_struAlarmHostAbility));
}

CDlgProductDH::~CDlgProductDH()
{
  
}

void CDlgProductDH::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgProductDH, CDialog)
    
    ON_BN_CLICKED(IDC_BTN_HISTORY_DATA, &CDlgProductDH::OnBnClickedBtnHistoryData)
    ON_BN_CLICKED(IDC_BTN_POINT_CFG, &CDlgProductDH::OnBnClickedBtnPointCfg)
    ON_BN_CLICKED(IDC_BTN_SENSOR_LINKAGE, &CDlgProductDH::OnBnClickedBtnSensorLinkage)
    ON_BN_CLICKED(IDC_BTN_SCALE_OUT_CFG, &CDlgProductDH::OnBnClickedBtnScaleOutCfg)
    ON_BN_CLICKED(IDC_BTN_UPLOAD_MODE, &CDlgProductDH::OnBnClickedBtnUploadMode)
    ON_BN_CLICKED(IDC_BTN_RS485_CFG, &CDlgProductDH::OnBnClickedBtnRs485Cfg)
    ON_BN_CLICKED(IDC_BTN_EXTERNAL_DEVICE_STATE, &CDlgProductDH::OnBnClickedBtnExternalDeviceState)
    ON_BN_CLICKED(IDC_BUT_NETALARM_ALARM_LOG_SEARCH, &CDlgProductDH::OnBnClickedButNetalarmAlarmLogSearch)
    ON_BN_CLICKED(IDC_BTN_SENSOR_CFG, &CDlgProductDH::OnBnClickedBtnSensorCfg)
    ON_BN_CLICKED(IDC_BTN_EXTERNAL_DEVICE_LIMIT_VALUE, &CDlgProductDH::OnBnClickedBtnExternalDeviceLimitValue)
    ON_BN_CLICKED(IDC_BTN_GET_ALL_POINT, &CDlgProductDH::OnBnClickedBtnGetAllPoint)
    ON_BN_CLICKED(IDC_BTN_GET_ALL_SENSOR, &CDlgProductDH::OnBnClickedBtnGetAllSensor)
    ON_BN_CLICKED(IDC_BTN_GET_ALL_RS485_CFG, &CDlgProductDH::OnBnClickedBtnGetAllRs485Cfg)
    ON_BN_CLICKED(IDC_BTN_GET_ALL_RS485_SLOT_CFG, &CDlgProductDH::OnBnClickedBtnGetAllRs485SlotCfg)
    ON_BN_CLICKED(IDC_BTN_GET_DEVICE_STATE, &CDlgProductDH::OnBnClickedBtnGetDeviceState)
    ON_BN_CLICKED(IDC_BTN_RS485_VERSION, &CDlgProductDH::OnBnClickedBtnRs485Version)
    ON_BN_CLICKED(IDC_BTN_ZONE_CFG, &CDlgProductDH::OnBnClickedBtnZoneCfg)
    ON_BN_CLICKED(IDC_BTN_OUTPUT_CFG, &CDlgProductDH::OnBnClickedBtnOutputCfg)
    ON_BN_CLICKED(IDC_BTN_ENABLE_CFG, &CDlgProductDH::OnBnClickedBtnEnableCfg)
    ON_BN_CLICKED(IDC_BTN_ABILITY_GET, &CDlgProductDH::OnBnClickedBtnAbilityGet)
    ON_BN_CLICKED(IDC_BTN_NETUSER_CFG, &CDlgProductDH::OnBnClickedBtnNetuserCfg)
    ON_BN_CLICKED(IDC_BTN_KEYPADUSER_CFG, &CDlgProductDH::OnBnClickedBtnKeypaduserCfg)
    ON_BN_CLICKED(IDC_BTN_STATUS_CHECK, &CDlgProductDH::OnBnClickedBtnStatusCheck)
    ON_BN_CLICKED(IDC_BTN_VOLTAGE_CHECK, &CDlgProductDH::OnBnClickedBtnVoltageCheck)
    ON_BN_CLICKED(IDC_BTN_RS485_DLL_CFG, &CDlgProductDH::OnBnClickedBtnRs485DllCfg)
END_MESSAGE_MAP()


// CDlgProductDH 消息处理程序

void CDlgProductDH::UpdataParam()
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
        }
    }
    UpdateData(FALSE);
}

BOOL CDlgProductDH::GetAlarmHostAbility(NET_DVR_ALARMHOST_ABILITY& struAlarmHostAbility)
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


void CDlgProductDH::OnBnClickedBtnHistoryData()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAlarmhostHistoryData dlg;
    dlg.DoModal();
}


void CDlgProductDH::OnBnClickedBtnPointCfg()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAlarmhostPointCfg dlg;
    dlg.DoModal();
}

void CDlgProductDH::OnBnClickedBtnSensorLinkage()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAlarmhostSensorLinkage dlg;
    dlg.DoModal();
}




void CDlgProductDH::OnBnClickedBtnScaleOutCfg()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgScaleOutCfg dlg;
    dlg.DoModal();
}


void CDlgProductDH::OnBnClickedBtnUploadMode()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAlarmhostDataUploadMode dlg;
    dlg.DoModal();
}




void CDlgProductDH::OnBnClickedBtnRs485Cfg()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAlarmHostRs485 dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    memcpy(&dlg.m_struDevAbility, &m_struAlarmHostAbility, sizeof(m_struAlarmHostAbility));
    dlg.DoModal();
}


void CDlgProductDH::OnBnClickedBtnExternalDeviceState()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAlarmHostExternalDevState dlg;
    dlg.DoModal();
}


void CDlgProductDH::OnBnClickedButNetalarmAlarmLogSearch()
{
    // TODO:  在此添加控件通知处理程序代码
    int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    if (iDeviceIndex == -1)
    {
        return;
    }
    CDlgAlarmHostLogSearch dlg;
    dlg.m_lServerID = g_struDeviceInfo[iDeviceIndex].lLoginID;
    dlg.m_iDevIndex = iDeviceIndex;
    dlg.DoModal();
}


void CDlgProductDH::OnBnClickedBtnSensorCfg()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgSensorCfg dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChanNum = g_struDeviceInfo[m_iDevIndex].iAnalogChanNum;
    memcpy(&dlg.m_struDevAbility, &m_struAlarmHostAbility, sizeof(m_struAlarmHostAbility));
    dlg.DoModal();
}


void CDlgProductDH::OnBnClickedBtnExternalDeviceLimitValue()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAlarmhostExternalDevLimitValue dlg;
    dlg.DoModal();
}


void CDlgProductDH::OnBnClickedBtnGetAllPoint()
{
    // TODO:  在此添加控件通知处理程序代码
    DlgGetAllPointCfg dlg;
    dlg.DoModal();
}


void CDlgProductDH::OnBnClickedBtnGetAllSensor()
{
    // TODO:  在此添加控件通知处理程序代码
    DlgGetAllSensor dlg;
    dlg.DoModal();
}


void CDlgProductDH::OnBnClickedBtnGetAllRs485Cfg()
{
    // TODO:  在此添加控件通知处理程序代码
    DlgGetAllRs485Cfg dlg;
    dlg.DoModal();
}


void CDlgProductDH::OnBnClickedBtnGetAllRs485SlotCfg()
{
    // TODO:  在此添加控件通知处理程序代码
    DlgGetAllRs485Slot dlg;
    dlg.DoModal();
}


void CDlgProductDH::OnBnClickedBtnGetDeviceState()
{
    // TODO:  在此添加控件通知处理程序代码
    DlgDeviceSelfCheckState dlg;
    dlg.DoModal();
}

void CDlgProductDH::OnBnClickedBtnRs485Version()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgRS485ProtocolVersion dlg;
    dlg.m_lUserID = m_lServerID;
    dlg.DoModal();
}


void CDlgProductDH::OnBnClickedBtnZoneCfg()
{
    // TODO:  在此添加控件通知处理程序代码
    // TODO:  在此添加控件通知处理程序代码
    CDlgAlarmHostZoneCfg dlg;
    dlg.DoModal();
}


void CDlgProductDH::OnBnClickedBtnOutputCfg()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAlarmOutCfg dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    memcpy(&dlg.m_struAbility, &m_struAlarmHostAbility, sizeof(m_struAlarmHostAbility));

    dlg.DoModal();
}


void CDlgProductDH::OnBnClickedBtnEnableCfg()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAlarmHostEnableCfg dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    memcpy(&dlg.m_struAbility, &m_struAlarmHostAbility, sizeof(m_struAlarmHostAbility));
    dlg.DoModal();
}


void CDlgProductDH::OnBnClickedBtnAbilityGet()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAlarmHostAbility dlg;
    memcpy(&dlg.m_struAlarmHostAbility, &m_struAlarmHostAbility, sizeof(m_struAlarmHostAbility));
    dlg.DoModal();
}


void CDlgProductDH::OnBnClickedBtnNetuserCfg()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAlarmNetUser dlg;
    dlg.m_lLoginID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_dwNetUserNum = m_struAlarmHostAbility.wNetUserNum;
    dlg.DoModal();
}


void CDlgProductDH::OnBnClickedBtnKeypaduserCfg()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAlarmOperatorUser dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_dwOperatorUserNum = m_struAlarmHostAbility.wOperatorUserNum;
    dlg.m_dwAlarmInNum = m_struAlarmHostAbility.wLocalAlarmInNum + m_struAlarmHostAbility.wExpandAlarmInNum;
    dlg.m_iSubSystemNum = m_struAlarmHostAbility.wSubSystemNum;
    dlg.m_dwKeyboardUserNum = m_struAlarmHostAbility.wKeyboardNum;
    dlg.DoModal();
}


void CDlgProductDH::OnBnClickedBtnStatusCheck()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAlarmHostStatus dlg;
    memcpy(&dlg.m_struAlarmHostAbility, &m_struAlarmHostAbility, sizeof(m_struAlarmHostAbility));
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lServerID = m_lServerID;
    dlg.m_lStartChan = m_lStartChan;
    dlg.m_lChannel = m_lChannel;
    dlg.DoModal();
}

BOOL CDlgProductDH::GetBatteryVoltage()
{
    if (NET_DVR_GetBatteryVoltage(m_lServerID, &m_fBatteryVoltage))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetBatteryVoltage");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetBatteryVoltage");
        return FALSE;
    }
}

void CDlgProductDH::OnBnClickedBtnVoltageCheck()
{
    // TODO:  在此添加控件通知处理程序代码
    char szLan[128] = { 0 };
    if (GetBatteryVoltage())
    {
        sprintf(szLan, "Battery voltage %0.3f", m_fBatteryVoltage);
        AfxMessageBox(szLan);
    }
}


void CDlgProductDH::OnBnClickedBtnRs485DllCfg()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgRS485DLLParamCfg dlg;
    dlg.m_iUserID = m_lServerID;
    dlg.m_iDeviceIndex = m_iDevIndex;
    dlg.DoModal();
}
