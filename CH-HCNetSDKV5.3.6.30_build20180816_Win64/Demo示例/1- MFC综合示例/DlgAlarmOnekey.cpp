// DlgAlarmOnekey.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgAlarmOnekey.h"
#include "afxdialogex.h"


// CDlgAlarmOnekey 对话框

IMPLEMENT_DYNAMIC(CDlgAlarmOnekey, CDialogEx)
CDlgAlarmOnekey::CDlgAlarmOnekey(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgAlarmOnekey::IDD, pParent)
{
    memset(&m_struCallWaitingCfg, 0, sizeof(NET_DVR_CALL_WAITTING_CFG));
    memset(&m_struAlarmLampCfg, 0, sizeof(NET_DVR_ALARM_LAMP_CFG));
    memset(&m_struVoicePromptionCfg, 0, sizeof(NET_DVR_VOICE_PROMPTION_CFG));
    memset(&m_struEmergenceAlarmRspCtrlCfg, 0, sizeof(NET_DVR_EMERGENCE_ALARM_RSP_CTRL_CFG));
    m_bEnable1 = FALSE;
    m_iWaitTime = 0;
    m_bEnable2 = FALSE;
    m_iFlashDuration = 0;
    m_iFlashIntervalTime = 0;
    m_bEnable3 = FALSE;
    m_csCenterBusyFile = _T("");
    m_csRefusedFile = _T("");
    m_csHangUpFile = _T("");
    m_csCallWaittingFile = _T("");
    m_csConsultWaittingFile = _T("");
}

BOOL CDlgAlarmOnekey::OnInitDialog()
{
    CDialog::OnInitDialog();
    // TODO: Add extra initialization here
    m_cmbCommand.SetCurSel(0);
    m_cmbType.SetCurSel(0);
    return TRUE;
}

CDlgAlarmOnekey::~CDlgAlarmOnekey()
{
}

void CDlgAlarmOnekey::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHK_ENABLE1, m_bEnable1);
    DDX_Text(pDX, IDC_EDIT_WAIT_TIME, m_iWaitTime);
    DDX_Check(pDX, IDC_CHK_ENABLE2, m_bEnable2);
    DDX_Text(pDX, IDC_EDIT_FLASH_DURATION, m_iFlashDuration);
    DDX_Text(pDX, IDC_EDIT_FLASH_INTERVAL_TIME, m_iFlashIntervalTime);
    DDX_Check(pDX, IDC_CHK_ENABLE3, m_bEnable3);
    DDX_Text(pDX, IDC_EDIT_CENTER_BUSY_FILE, m_csCenterBusyFile);
    DDX_Text(pDX, IDC_EDIT_REFUSED_FILE, m_csRefusedFile);
    DDX_Text(pDX, IDC_EDIT_HANG_UP_FILE, m_csHangUpFile);
    DDX_Text(pDX, IDC_EDIT_CALL_WAITTING_FILE, m_csCallWaittingFile);
    DDX_Text(pDX, IDC_EDIT_CONSULT_WAITTING_FILE, m_csConsultWaittingFile);
    DDX_Control(pDX, IDC_CMB_COMMAND, m_cmbCommand);
    DDX_Control(pDX, IDC_CMB_EMERGENCY_TYPE, m_cmbType);
}


BEGIN_MESSAGE_MAP(CDlgAlarmOnekey, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_GET_CALL_WAITING, &CDlgAlarmOnekey::OnBnClickedBtnGetCallWaiting)
    ON_BN_CLICKED(IDC_BTN_SET_CALL_WAITING, &CDlgAlarmOnekey::OnBnClickedBtnSetCallWaiting)
    ON_BN_CLICKED(IDC_BTN_GET_ALARM_LAMP, &CDlgAlarmOnekey::OnBnClickedBtnGetAlarmLamp)
    ON_BN_CLICKED(IDC_BTN_SET_ALARM_LAMP, &CDlgAlarmOnekey::OnBnClickedBtnSetAlarmLamp)
    ON_BN_CLICKED(IDC_BTN_GET_VOICE_PROMPTION, &CDlgAlarmOnekey::OnBnClickedBtnGetVoicePromption)
    ON_BN_CLICKED(IDC_BTN_SET_VOICE_PROMPTION, &CDlgAlarmOnekey::OnBnClickedBtnSetVoicePromption)
    ON_BN_CLICKED(IDC_BTN_CTRL_EMERGENCE_ALARM_RSP, &CDlgAlarmOnekey::OnBnClickedBtnCtrlEmergenceAlarmRsp)
END_MESSAGE_MAP()


// CDlgAlarmOnekey 消息处理程序


void CDlgAlarmOnekey::OnBnClickedBtnGetCallWaiting()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    NET_DVR_STD_CONFIG struStdConfig = { 0 };
    struStdConfig.lpOutBuffer = (LPVOID)&m_struCallWaitingCfg;
    struStdConfig.dwOutSize = sizeof(m_struCallWaitingCfg);
    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_CALL_WAITTING_CFG, &struStdConfig))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_CALL_WAITTING_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_CALL_WAITTING_CFG");
    }
    m_bEnable1 = m_struCallWaitingCfg.byEnable;
    m_iWaitTime = m_struCallWaitingCfg.wWaitTime;
    UpdateData(FALSE);
}


void CDlgAlarmOnekey::OnBnClickedBtnSetCallWaiting()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    m_struCallWaitingCfg.dwSize = sizeof(m_struCallWaitingCfg);
    m_struCallWaitingCfg.byEnable = m_bEnable1;
    m_struCallWaitingCfg.wWaitTime = (WORD)m_iWaitTime;
    NET_DVR_STD_CONFIG struStdConfig = { 0 };
    struStdConfig.lpInBuffer = (LPVOID)&m_struCallWaitingCfg;
    struStdConfig.dwInSize = sizeof(m_struCallWaitingCfg);
    if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_CALL_WAITTING_CFG, &struStdConfig))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_CALL_WAITTING_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_CALL_WAITTING_CFG");
    }
    UpdateData(FALSE);
}


void CDlgAlarmOnekey::OnBnClickedBtnGetAlarmLamp()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    NET_DVR_STD_CONFIG struStdConfig = { 0 };
    struStdConfig.lpOutBuffer = (LPVOID)&m_struAlarmLampCfg;
    struStdConfig.dwOutSize = sizeof(m_struAlarmLampCfg);
    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_ALARM_LAMP_CFG, &struStdConfig))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARM_LAMP_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARM_LAMP_CFG");
    }
    m_bEnable2 = m_struAlarmLampCfg.byEnable;
    m_iFlashDuration = m_struAlarmLampCfg.wFlashDuration;
    m_iFlashIntervalTime = m_struAlarmLampCfg.wFlashIntervalTime;
    UpdateData(FALSE);
}


void CDlgAlarmOnekey::OnBnClickedBtnSetAlarmLamp()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    m_struAlarmLampCfg.dwSize = sizeof(m_struAlarmLampCfg);
    m_struAlarmLampCfg.byEnable = m_bEnable2;
    m_struAlarmLampCfg.wFlashDuration = (WORD)m_iFlashDuration;
    m_struAlarmLampCfg.wFlashIntervalTime = (WORD)m_iFlashIntervalTime;
    NET_DVR_STD_CONFIG struStdConfig = { 0 };
    struStdConfig.lpInBuffer = (LPVOID)&m_struAlarmLampCfg;
    struStdConfig.dwInSize = sizeof(m_struAlarmLampCfg);
    if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_ALARM_LAMP_CFG, &struStdConfig))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_ALARM_LAMP_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_ALARM_LAMP_CFG");
    }
    UpdateData(FALSE);
}


void CDlgAlarmOnekey::OnBnClickedBtnGetVoicePromption()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    NET_DVR_STD_CONFIG struStdConfig = { 0 };
    struStdConfig.lpOutBuffer = (LPVOID)&m_struVoicePromptionCfg;
    struStdConfig.dwOutSize = sizeof(m_struVoicePromptionCfg);
    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_VOICE_PROMPTION_CFG, &struStdConfig))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VOICE_PROMPTION_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_VOICE_PROMPTION_CFG");
    }
    m_bEnable3 = m_struVoicePromptionCfg.byEnable;
    m_csCenterBusyFile = m_struVoicePromptionCfg.byCenterBusyFile;
    m_csRefusedFile = m_struVoicePromptionCfg.byRefusedFile;
    m_csHangUpFile = m_struVoicePromptionCfg.byHangUpFile;
    m_csCallWaittingFile = m_struVoicePromptionCfg.byCallWaittingFile;
    m_csConsultWaittingFile = m_struVoicePromptionCfg.byConsultWaittingFile;
    UpdateData(FALSE);
}


void CDlgAlarmOnekey::OnBnClickedBtnSetVoicePromption()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    m_struVoicePromptionCfg.dwSize = sizeof(m_struVoicePromptionCfg);
    m_struVoicePromptionCfg.byEnable = m_bEnable3;
    memcpy(m_struVoicePromptionCfg.byCenterBusyFile, (LPCSTR)m_csCenterBusyFile, m_csCenterBusyFile.GetAllocLength());
    memcpy(m_struVoicePromptionCfg.byRefusedFile, (LPCSTR)m_csRefusedFile, m_csRefusedFile.GetAllocLength());
    memcpy(m_struVoicePromptionCfg.byHangUpFile, (LPCSTR)m_csHangUpFile, m_csHangUpFile.GetAllocLength());
    memcpy(m_struVoicePromptionCfg.byCallWaittingFile, (LPCSTR)m_csCallWaittingFile, m_csCallWaittingFile.GetAllocLength());
    memcpy(m_struVoicePromptionCfg.byConsultWaittingFile, (LPCSTR)m_csConsultWaittingFile, m_csConsultWaittingFile.GetAllocLength());
    NET_DVR_STD_CONFIG struStdConfig = { 0 };
    struStdConfig.lpInBuffer = (LPVOID)&m_struVoicePromptionCfg;
    struStdConfig.dwInSize = sizeof(m_struVoicePromptionCfg);
    if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_VOICE_PROMPTION_CFG, &struStdConfig))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VOICE_PROMPTION_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VOICE_PROMPTION_CFG");
    }
    UpdateData(FALSE);
}


void CDlgAlarmOnekey::OnBnClickedBtnCtrlEmergenceAlarmRsp()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    m_struEmergenceAlarmRspCtrlCfg.dwSize = sizeof(m_struEmergenceAlarmRspCtrlCfg);
    m_struEmergenceAlarmRspCtrlCfg.byCommand = m_cmbCommand.GetCurSel();
     m_struEmergenceAlarmRspCtrlCfg.byType = m_cmbType.GetCurSel();
    NET_DVR_STD_CONTROL struStdControl = {0};
    struStdControl.lpCondBuffer = (LPVOID)&m_struEmergenceAlarmRspCtrlCfg;
    struStdControl.dwCondSize = sizeof(m_struEmergenceAlarmRspCtrlCfg);
    if (!NET_DVR_STDControl(m_lServerID, NET_DVR_EMERGENCE_ALARM_RESPONSE_CTRL, &struStdControl))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_EMERGENCE_ALARM_RESPONSE_CTRL");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_EMERGENCE_ALARM_RESPONSE_CTRL");
    }
    UpdateData(FALSE);
}
// DlgAlarmOneKey.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgAlarmOneKey.h"
#include "afxdialogex.h"


// CDlgAlarmOneKey 对话框

IMPLEMENT_DYNAMIC(CDlgAlarmOneKey, CDialogEx)

CDlgAlarmOneKey::CDlgAlarmOneKey(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgAlarmOneKey::IDD, pParent)
{

}

CDlgAlarmOneKey::~CDlgAlarmOneKey()
{
}

void CDlgAlarmOneKey::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgAlarmOneKey, CDialogEx)
END_MESSAGE_MAP()


// CDlgAlarmOneKey 消息处理程序
