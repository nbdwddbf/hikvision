// DlgProductAlarmHostCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgProductAlarmHostCfg.h"
#include "DlgAlarmHostStatus.h"
#include "DlgAlarmOutCfg.h"
#include "DlgAlarmHostAbility.h"
#include "DlgAlarmHostRs485.h"
#include "DlgAlarmNetUser.h"
#include "DlgAlarmOperatorUser.h"
#include "DlgAlarmHostEnableCfg.h"
#include "DlgGatewayCfg.h"
#include "DlgAlarmHostReportMode.h"
#include "DlgAlarmHostGPRS.h"
#include "DlgAlarmHostNetCfg.h"
#include "DlgAlarmHostAudioAssociateAlarm.h"
#include "DlgAlarmHostLED.h"
#include "DlgSafetyCabin.h"
#include "DlgAlarmhostModuleCfg.h"
#include "DlgAlarmhostPrinter.h"
#include "DlgAlarmHostLogSearch.h"
#include "DlgAlarmOnekey.h"
#include "DlgAlarmChanAblitity.h"
#include "DlgAlarmCenterNetCfg.h"
#include "DlgAlarmTamper.h"
#include "DlgAlarmHostDialParam.h"
#include "DlgAlarmhostSubsystem.h"
#include "DlgAlarmHostZoomAddr.h"
#include "DlgAlarmHostTriggerCode.h"
#include "DlgAlarmHostFaultProcess.h"
#include "DlgAlarmHostEventTrigger.h"
#include "DlgAlarmHostExternalModule.h"
#include "DlgAlarmhostSTDXMLConfig.h"
#include "DlgSubsysNetCfg.h"
#include "DlgAlarmHostZoneCfg.h"
#include "DlgAlarmCenterServerCfg.h"
#include "DlgDelayPreviewCfg.h"
#include "DlgZoneLinkageChanCfg.h"
#include "DlgAlarmPicCfg.h"
#include "DlgWhiteList.h"
#include "DlgSystemTimeAlarm.h"
#include "DlgAlarmHostGetAllModule.h"
#include "DlgWirelessBusinessSearch.h"
#include "DlgRemoteControllerManage.h"
#include "DlgDetectorRegister.h"
#include "DlgScaleOutCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgProductAlarmHostCfg dialog


CDlgProductAlarmHostCfg::CDlgProductAlarmHostCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProductAlarmHostCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgProductAlarmHostCfg)
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
}


void CDlgProductAlarmHostCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgProductAlarmHostCfg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgProductAlarmHostCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgProductAlarmHostCfg)
	ON_BN_CLICKED(IDC_BTN_STATUS_QUERY, OnBtnStatusQuery)
	ON_BN_CLICKED(IDC_BTN_ALARMOUT_CFG, OnBtnAlarmoutCfg)
	ON_BN_CLICKED(IDC_BTN_ALARMHOST_ABILITY, OnBtnAlarmhostAbility)
	ON_BN_CLICKED(IDC_BTN_RS485_CFG, OnBtnRs485Cfg)
	ON_BN_CLICKED(IDC_BTN_NET_USER, OnBtnNetUser)
	ON_BN_CLICKED(IDC_BTN_OPERATOR_USER, OnBtnOperatorUser)
	ON_BN_CLICKED(IDC_BTN_BATTARY_VOLTAGE, OnBtnBattaryVoltage)
	ON_BN_CLICKED(IDC_BTN_ALARMHOST_ENABLECFG, OnBtnAlarmhostEnablecfg)
	ON_BN_CLICKED(IDC_BTN_GATEWAY_CFG, OnBtnGatewayCfg)
	ON_BN_CLICKED(IDC_BUTTON_DIALPARAM, OnButtonDialparam)
	ON_BN_CLICKED(IDC_BTN_BYPASSSETUP, OnBtnBypasssetup)
	ON_BN_CLICKED(IDC_BTN_BYPASS_STOPSETUP, OnBtnBypassStopsetup)
	ON_BN_CLICKED(IDC_BTN_SUBSYSTEM_CFG, OnBtnSubsystemCfg)
	ON_BN_CLICKED(IDC_BTN_REPORTMODE, OnBtnReportmode)
	ON_BN_CLICKED(IDC_BTN_GPRSPARA, OnBtnGprspara)
	ON_BN_CLICKED(IDC_BTN_NETCFG, OnBtnNetcfg)
	ON_BN_CLICKED(IDC_BTN_ZOOM_CODE, OnBtnZoomCode)
	ON_BN_CLICKED(IDC_BTN_TRIGGER_CODE, OnBtnTriggerCode)
	ON_BN_CLICKED(IDC_BTN_FAULT_PROCESS, OnBtnFaultProcess)
	ON_BN_CLICKED(IDC_BTN_EVENT_TRIGGER, OnBtnEventTrigger)
	ON_BN_CLICKED(IDC_BTN_EXTERN_MODULE, OnBtnExternModule)
	ON_BN_CLICKED(IDC_BTN_LED, OnBtnLed)
	ON_BN_CLICKED(IDC_BTN_AUDIO_ASSOCIATE, OnBtnAudioAssociate)
	ON_BN_CLICKED(IDC_BTN_SAFETY_CABIN, OnBtnSafetyCabin)
	ON_BN_CLICKED(IDC_BTN_MODULE_CFG, OnBtnModuleCfg)
	ON_BN_CLICKED(IDC_BUT_NETALARM_ALARM_LOG_SEARCH, OnButAlarmLogSearch)
	ON_BN_CLICKED(IDC_BTN_ALARM_CHAN_ABLITITY, OnBtnAlarmChanAblitity)
	ON_BN_CLICKED(IDC_BTN_ALARM_CENTER, OnBtnAlarmCenter)
	ON_BN_CLICKED(IDC_BTN_TAMPER, OnBtnTamper)
    ON_BN_CLICKED(IDC_BTN_STD_XML_CONFIG, &CDlgProductAlarmHostCfg::OnBnClickedBtnStdXmlConfig)
    ON_BN_CLICKED(IDC_BTN_PRINTER2, OnBtnPrinter)
    ON_BN_CLICKED(IDC_BTN_ALARM_ONE_KEY, &CDlgProductAlarmHostCfg::OnBnClickedBtnAlarmOneKey)
    ON_BN_CLICKED(IDC_BTN_GET_ALL_MODULE, OnBtnGerAllModule)
    ON_BN_CLICKED(IDC_BTN_SUB_SYSTEM_ALARM, OnBtnSubSystemAlarm)
    ON_BN_CLICKED(IDC_BTN_WHITE_LIST_CFG, OnBtnWhiteListCfg)
    ON_BN_CLICKED(IDC_BTN_WIRELESS_BUSINNESS_SEARCH, OnBtnWirelessBusinnessSearch)
    ON_BN_CLICKED(IDC_BTN_GET_ALL_REMOTE_CONTROLLER, OnBtnGetAllRemoteController)
    ON_BN_CLICKED(IDC_BTN_ALARM_CAPTRUE_CFG2, OnBtnAlarmCaptrueCfg)
    ON_BN_CLICKED(IDC_BTN_CENTER_SVR_CFG, OnBtnCenterSvrCfg)
    ON_BN_CLICKED(IDC_BTN_LINKAGE_CHAN, OnBtnLinkageChan)
    ON_BN_CLICKED(IDC_BTN_DELAY_PREVIEW_CFG, OnBnClickedBtnDelayPreviewCfg)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_ZONE_CFG, &CDlgProductAlarmHostCfg::OnBnClickedBtnZoneCfg)
    ON_BN_CLICKED(IDC_BTN_REGISTERDETECTOR, &CDlgProductAlarmHostCfg::OnBnClickedBtnRegisterdetector)
    ON_BN_CLICKED(IDC_BTN_OUT_SCALE, &CDlgProductAlarmHostCfg::OnBnClickedBtnOutScale)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgProductAlarmHostCfg message handlers

BOOL CDlgProductAlarmHostCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
    
//     m_comboAlarmOut.SetCurSel(0);
//     OnSelchangeComboAlarmOut();
    
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgProductAlarmHostCfg::GetAlarmHostAbility(NET_DVR_ALARMHOST_ABILITY& struAlarmHostAbility)
{
    BOOL bRet = FALSE;
    DWORD dwReturn = 0;
    if (NET_DVR_GetDeviceAbility(m_lServerID, ALARMHOST_ABILITY, NULL, 0, (char*)&struAlarmHostAbility, sizeof(struAlarmHostAbility)))
    {
        char szLan[128] = {0};
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



// void CDlgProductAlarmHostCfg::OnBtnSetAlarmoutTime() 
// {
// /*    UpdateData(TRUE);*/
// //     m_struAlarmOutTimeCfg.wAlarmOutTime = m_iAlarmOutTime;
// //     SetAlarmOutTimeCfg(m_struAlarmOutTimeCfg);
// }


// void CDlgProductAlarmHostCfg::OnSelchangeComboAlarmOut() 
// {
// //     GetAlarmOutTimeCfg(m_struAlarmOutTimeCfg);
// //     m_iAlarmOutTime = (int)m_struAlarmOutTimeCfg.wAlarmOutTime;   
// //     UpdateData(FALSE);
// }

// void CDlgProductAlarmHostCfg::OnBtnOpenAlarmout() 
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

// void CDlgProductAlarmHostCfg::OnBtnCloseAlarmout() 
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


void CDlgProductAlarmHostCfg::OnBtnStatusQuery() 
{   
    CDlgAlarmHostStatus dlg;
    memcpy(&dlg.m_struAlarmHostAbility, &m_struAlarmHostAbility, sizeof(m_struAlarmHostAbility));
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lServerID = m_lServerID;
    dlg.m_lStartChan = m_lStartChan;
    dlg.m_lChannel = m_lChannel;
    dlg.DoModal();
}

void CDlgProductAlarmHostCfg::OnBtnAlarmoutCfg() 
{
    CDlgAlarmOutCfg dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    memcpy(&dlg.m_struAbility, &m_struAlarmHostAbility, sizeof(m_struAlarmHostAbility));

    dlg.DoModal();
}

void CDlgProductAlarmHostCfg::OnBtnAlarmhostAbility() 
{
    CDlgAlarmHostAbility dlg;
    memcpy(&dlg.m_struAlarmHostAbility, &m_struAlarmHostAbility, sizeof(m_struAlarmHostAbility));
    dlg.DoModal();
	
}

void CDlgProductAlarmHostCfg::OnBtnRs485Cfg() 
{
	CDlgAlarmHostRs485 dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    memcpy(&dlg.m_struDevAbility, &m_struAlarmHostAbility, sizeof(m_struAlarmHostAbility));
    dlg.DoModal();
}


void CDlgProductAlarmHostCfg::OnBtnNetUser() 
{
    CDlgAlarmNetUser dlg;
    dlg.m_lLoginID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_dwNetUserNum = m_struAlarmHostAbility.wNetUserNum;
    dlg.DoModal();
}


void CDlgProductAlarmHostCfg::OnBtnOperatorUser() 
{
    CDlgAlarmOperatorUser dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_dwOperatorUserNum = m_struAlarmHostAbility.wOperatorUserNum;
    dlg.m_dwAlarmInNum = m_struAlarmHostAbility.wLocalAlarmInNum + m_struAlarmHostAbility.wExpandAlarmInNum;
    dlg.m_iSubSystemNum = m_struAlarmHostAbility.wSubSystemNum;
    dlg.m_dwKeyboardUserNum = m_struAlarmHostAbility.wKeyboardNum;
    dlg.DoModal();
}

void CDlgProductAlarmHostCfg::OnBtnBattaryVoltage() 
{
    char szLan[128] = {0};
    if (GetBatteryVoltage())
    {
        sprintf(szLan, "Battery voltage %0.3f", m_fBatteryVoltage);
        AfxMessageBox(szLan);
    }
}

BOOL CDlgProductAlarmHostCfg::GetBatteryVoltage()
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

void CDlgProductAlarmHostCfg::OnBtnAlarmhostEnablecfg() 
{
    CDlgAlarmHostEnableCfg dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    memcpy(&dlg.m_struAbility, &m_struAlarmHostAbility, sizeof(m_struAlarmHostAbility));
    dlg.DoModal();
}

void CDlgProductAlarmHostCfg::OnBtnGatewayCfg() 
{
	CDlgGatewayCfg dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_dwGatawayNum = m_struAlarmHostAbility.wGatewayNum;
    dlg.DoModal();
}


void CDlgProductAlarmHostCfg::OnButtonDialparam() 
{
    CDlgAlarmHostDialParam dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
	
}

void CDlgProductAlarmHostCfg::OnBtnBypasssetup() 
{
	// TODO: Add your control notification handler code here
	if (!NET_DVR_AlarmHostArrayBypass(g_struDeviceInfo[m_iDevIndex].lLoginID))
	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "组旁路失败" , "NET_DVR_AlarmHostArrayBypass FAILED");
		MessageBox(szLan);
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_AlarmHostArrayBypass FAILED");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_AlarmHostArrayBypass SUCC");
	}
}



void CDlgProductAlarmHostCfg::OnBtnBypassStopsetup() 
{
	// TODO: Add your control notification handler code here
	char szLan[1024] = {0};
	if (!NET_DVR_AlarmHostArrayBypassResume(g_struDeviceInfo[m_iDevIndex].lLoginID))
	{
		g_StringLanType(szLan, "撤销组旁路失败" , "NET_DVR_AlarmHostArrayBypassResume FAILED");
		MessageBox(szLan);
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_AlarmHostArrayBypassResume FAILED");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_AlarmHostArrayBypassResume SUCC");
	}
}

void CDlgProductAlarmHostCfg::OnBtnSubsystemCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgAlarmhostSubsystem dlg;
	dlg.DoModal();
}



void CDlgProductAlarmHostCfg::OnBtnReportmode() 
{
	// TODO: Add your control notification handler code here
	CDlgAlarmHostReportMode dlg;
	dlg.DoModal();
}

void CDlgProductAlarmHostCfg::OnBtnGprspara() 
{
	// TODO: Add your control notification handler code here
	CDlgAlarmHostGPRS dlg;
	dlg.DoModal();
}


void CDlgProductAlarmHostCfg::OnBtnNetcfg() 
{
	// TODO: Add your control notification handler code here
	CDlgAlarmHostNetCfg dlg;
	dlg.DoModal();
}


void CDlgProductAlarmHostCfg::OnBtnZoomCode() 
{
	// TODO: Add your control notification handler code here
	CDlgAlarmHostZoneAddr dlg;
	dlg.DoModal();
}

void CDlgProductAlarmHostCfg::OnBtnTriggerCode() 
{
	// TODO: Add your control notification handler code here
	CDlgAlarmHostTriggerCode dlg;
	dlg.DoModal();
}


void CDlgProductAlarmHostCfg::OnBtnFaultProcess() 
{
	// TODO: Add your control notification handler code here
	CDlgAlarmHostFaultProcess dlg;
	dlg.DoModal();
}


void CDlgProductAlarmHostCfg::OnBtnEventTrigger() 
{
	// TODO: Add your control notification handler code here
	CDlgAlarmHostEventTrigger dlg;
	dlg.DoModal();
}


void CDlgProductAlarmHostCfg::OnBtnExternModule() 
{
	// TODO: Add your control notification handler code here
	CDlgAlarmHostExternalModule dlg;
	dlg.DoModal();
}

void CDlgProductAlarmHostCfg::OnBtnLed() 
{
	// TODO: Add your control notification handler code here
	CDlgAlarmHostLED dlg;
	dlg.DoModal();
}



void CDlgProductAlarmHostCfg::OnBtnAudioAssociate() 
{
	// TODO: Add your control notification handler code here
	CDlgAlarmHostAudioAssociateAlarm dlg;
	dlg.DoModal();
}

void CDlgProductAlarmHostCfg::OnBtnSafetyCabin() 
{
	// TODO: Add your control notification handler code here
	CDlgSafetyCabin dlg;
	dlg.m_lUserID = m_lServerID;
	dlg.DoModal();
}

void CDlgProductAlarmHostCfg::OnBtnModuleCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgAlarmhostModuleCfg dlg;
	dlg.DoModal();
}

void CDlgProductAlarmHostCfg::OnBtnPrinter() 
{
	// TODO: Add your control notification handler code here
	CDlgAlarmHostPrinter dlg;
	dlg.DoModal();
}

void CDlgProductAlarmHostCfg::UpdatePapam()
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
    m_lChannel= iChanIndex+g_struDeviceInfo[iDeviceIndex].iStartChan;
	
	if (!m_bInit)
	{
		if(TRUE == GetAlarmHostAbility(m_struAlarmHostAbility))
		{
			m_bInit = TRUE;
			if (m_struAlarmHostAbility.by3GNum > 0)
			{
				g_StringLanType(m_szLan, "3G参数配置", "3G Config");
				SetDlgItemText(IDC_BTN_GPRSPARA, m_szLan);
			}
			else
			{
				g_StringLanType(m_szLan, "GPRS参数配置", "GPRS Config");
				SetDlgItemText(IDC_BTN_GPRSPARA, m_szLan);
			}
		}
	}
    UpdateData(FALSE);
}

void CDlgProductAlarmHostCfg::OnButAlarmLogSearch() 
{
	// TODO: Add your control notification handler code here
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

void CDlgProductAlarmHostCfg::OnBtnAlarmChanAblitity() 
{
	// TODO: Add your control notification handler code here
	CDlgAlarmChanAblitity dlg;
	dlg.DoModal();
}


void CDlgProductAlarmHostCfg::OnBtnAlarmCenter() 
{
	// TODO: Add your control notification handler code here
	CDlgAlarmCenterNetCfg dlg;
	dlg.DoModal();
}

void CDlgProductAlarmHostCfg::OnBtnTamper() 
{
	// TODO: Add your control notification handler code here
	CDlgAlarmTamper dlg;
	dlg.DoModal();
}

void CDlgProductAlarmHostCfg::OnBnClickedBtnAlarmOneKey()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAlarmOnekey dlg;
    int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    if (iDeviceIndex == -1)
    {
        return;
    }
    dlg.m_lServerID = g_struDeviceInfo[iDeviceIndex].lLoginID;
    dlg.m_iDevIndex = iDeviceIndex;
    dlg.DoModal();
}

void CDlgProductAlarmHostCfg::OnBnClickedBtnStdXmlConfig()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAlarmhostSTDXMLConfig dlg;
    int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    if (iDeviceIndex < 0)
    {
        return;
    }
    int iChanIndex = g_pMainDlg->GetCurChanIndex();
    if (iChanIndex < 0)
    {
        iChanIndex = 0;
    }

    dlg.m_lUserID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;

    dlg.m_iStartChan = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].iChannelNO;

    dlg.DoModal();
}


void CDlgProductAlarmHostCfg::OnBnClickedBtnZoneCfg()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAlarmHostZoneCfg dlg;
    dlg.DoModal();
   // dlg.UpdatePapam();
}

void CDlgProductAlarmHostCfg::OnBtnWirelessBusinnessSearch()
{
    // TODO: Add your control notification handler code here
    CDlgWirelessBusinessSearch dlg;

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
    dlg.m_iDevIndex = iDeviceIndex;
    dlg.m_lUserID = g_struDeviceInfo[iDeviceIndex].lLoginID;

    dlg.DoModal();
}


void CDlgProductAlarmHostCfg::OnBtnGetAllRemoteController()
{
    // TODO: Add your control notification handler code here
    CDlgRemoteControllerManage dlg;
    dlg.DoModal();
}

void CDlgProductAlarmHostCfg::OnBtnGerAllModule()
{
    DlgAlarmHostGetAllModule dlg;

    int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    if (iDeviceIndex < 0)
    {
        return;
    }
    dlg.m_iDevIndex = iDeviceIndex;
    dlg.m_lServerID = g_struDeviceInfo[iDeviceIndex].lLoginID;

    dlg.DoModal();
}


void CDlgProductAlarmHostCfg::OnBtnSubSystemAlarm()
{
    DlgSystemTimeAlarm dlg;

    int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    if (iDeviceIndex < 0)
    {
        return;
    }
    dlg.m_iDevIndex = iDeviceIndex;
    dlg.m_lServerID = g_struDeviceInfo[iDeviceIndex].lLoginID;

    dlg.DoModal();
}


void CDlgProductAlarmHostCfg::OnBtnWhiteListCfg()
{
    DlgWhiteList dlg;

    dlg.DoModal();
}


void CDlgProductAlarmHostCfg::OnBtnAlarmCaptrueCfg()
{
    // TODO: Add your control notification handler code here
    CDlgAlarmPicCfg dlg;
    dlg.DoModal();
}


void CDlgProductAlarmHostCfg::OnBtnLinkageChan()
{
    // TODO: Add your control notification handler code here
    CDlgZoneLinkageChanCfg dlg;
    int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    if (iDeviceIndex < 0)
    {
        return;
    }
    dlg.m_lUserID = g_struDeviceInfo[iDeviceIndex].lLoginID;
    dlg.m_iDeviceIndex = iDeviceIndex;
    dlg.DoModal();
}


void CDlgProductAlarmHostCfg::OnBtnCenterSvrCfg()
{
    // TODO: Add your control notification handler code here
    CDlgAlarmCenterServerCfg dlg;
    int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    if (iDeviceIndex < 0)
    {
        return;
    }
    dlg.m_lUserID = g_struDeviceInfo[iDeviceIndex].lLoginID;
    dlg.m_iDeviceIndex = iDeviceIndex;
    dlg.DoModal();

}



void CDlgProductAlarmHostCfg::OnBnClickedBtnDelayPreviewCfg()
{
    int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    if (iDeviceIndex < 0)
    {
        return;
    }
    int iChanIndex = g_pMainDlg->GetCurChanIndex();
    if (iChanIndex < 0)
    {
        iChanIndex = 0;
    }

    CDlgDelayPreviewCfg dlg;
    dlg.m_lUserID = g_struDeviceInfo[iDeviceIndex].lLoginID;
    dlg.m_lChannel = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].iChannelNO;//iChanIndex + g_struDeviceInfo[iDeviceIndex].iStartChan;
    dlg.m_iDeviceIndex = iDeviceIndex;

    dlg.DoModal();
}

void CDlgProductAlarmHostCfg::OnBnClickedBtnRegisterdetector()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgDetectorRegister dlg;
    int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    if (iDeviceIndex < 0)
    {
        return;
    }
    dlg.m_iDevIndex = iDeviceIndex;
    dlg.m_lServerID = g_struDeviceInfo[iDeviceIndex].lLoginID;

    dlg.DoModal();
}

void CDlgProductAlarmHostCfg::OnBnClickedBtnOutScale()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgScaleOutCfg dlg;
    dlg.DoModal();
}