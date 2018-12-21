// DlgProductAcs.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgProductAcs.h"
#include "DlgAcsWorkStatus.h"
#include "DlgDoorConfig.h"
#include "DlgWeekPlan.h"
#include "DlgGroupCfg.h"
#include "DlgMultiCardCfg.h"
#include "DlgClearAcsParam.h"
#include "DlgSneakAndLock.h"
#include "DlgGatewayCardCfg.h"
#include "DlgAlarmNetUser.h"
#include "DlgAlarmHost.h"
#include "DlgAcsCaseSensor.h"
#include "DlgAcsCardUserInfoCfg.h"
#include "DlgAcsExternalDevCfg.h"
#include "DlgAcsPersonnelChannelCfg.h"
#include "DlgWiegandCfg.h"
#include "DlgAcsMoudleStatus.h"
#include "DlgAcsLocalControllerStatus.h"
#include "DlgAcsOnlineLocalControllerCfg.h"
#include "DlgAlarmHostAbility.h"
#include "DlgAlarmHostZoomAddr.h"
#include "DlgAlarmHostTriggerCode.h"
#include "DlgAcsLocalControllerCfg.h"
#include "DlgAcsUSBDeviceManage.h"
#include "DlgAlarmHostExternalModule.h"
#include "DlgUploadBlackList.h"
#include "DlgGetRegisterInfo.h"
#include "DlgAcsFaceParamCfg.h"
#include "DlgUploadBlackListPicture.h"
#include "DlgBatchUploadBlackList.h"
#include "DlgAcsCheckFacePicture.h"
#include "DlgAcsFaceAndTemplate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgProductAcs dialog


CDlgProductAcs::CDlgProductAcs(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProductAcs::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgProductAcs)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_lUserID = -1;
    m_iDeviceIndex = -1;
	m_lChannel = -1;
}


void CDlgProductAcs::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgProductAcs)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgProductAcs, CDialog)
	//{{AFX_MSG_MAP(CDlgProductAcs)
	ON_BN_CLICKED(IDC_BTN_ACS_WORK_STATUS, OnBtnAcsWorkStatus)
	ON_BN_CLICKED(IDC_BUT_AC_PLANCONFIGURE, OnButPlanConfig)
	ON_BN_CLICKED(IDC_BUT_AC_DOORCONFIG, OnButDoorConfig)
	ON_BN_CLICKED(IDC_BTN_ACS_GROUP_CFG, OnBtnAcsGroupCfg)
	ON_BN_CLICKED(IDC_BTN_ACS_MULTI_CARD, OnBtnAcsMultiCard)
	ON_BN_CLICKED(IDC_BTN_ACS_CLEAR, OnBtnAcsClear)
	ON_BN_CLICKED(IDC_BTN_SNEAK_AND_LOCK, OnBtnSneakAndLock)
	ON_BN_CLICKED(IDC_BUT_AC_ALARMINANDOUT, OnButAlarminAndout)
	ON_BN_CLICKED(IDC_BUT_AC_ALARMUSER, OnButAcAlarmUser)
	ON_BN_CLICKED(IDC_BTN_CARD_CFG, OnBtnCardCfg)
	ON_BN_CLICKED(IDC_BTN_CASE_SENSOR, OnBtnCaseSensor)
	ON_BN_CLICKED(IDC_BUT_AC_REMOTECONTROL, OnButAcRemotecontrol)
	ON_BN_CLICKED(IDC_BUT_AC_RS485, OnButAcRs485)
    ON_BN_CLICKED(IDC_BUT_AC_CARDREADERCFG, OnButAcCardreadercfg)
    ON_BN_CLICKED(IDC_BUT_CMS_CFG, OnButCmsCfg)
    ON_BN_CLICKED(IDC_BUT_ALARMHOST_NETCFG, OnButAlarmHostNetCfg)
    ON_BN_CLICKED(IDC_BUT_ALARMHOST_WIRELESS_NETWORK_CFG, OnButAlarmHostWirelessNetworkCfg)
    ON_BN_CLICKED(IDC_BUT_ALARMHOST_REPORT_CENTER_V40, OnButAlarmHostReportCenterV40)
    ON_BN_CLICKED(IDC_BUT_SMSRELATIVEPARA, OnButSmsRelativePara)
    ON_BN_CLICKED(IDC_BUT_PHONE_DOOR_RIGHT_CFG, OnButPhoneDoorRightCfg)
    ON_BN_CLICKED(IDC_BUT_FINGERPRINT_CFG, OnButFingerPrintCfg)
    ON_BN_CLICKED(IDC_BUTTON_PASSWD_OPEN_DOOR, OnButPasswdOpenDoor)
    ON_BN_CLICKED(IDC_BUT_EVENT_CARD_LINKAGE_CFG, OnButEventCardLinkageCfg)
    ON_BN_CLICKED(IDC_BUT_ANTI_SNEAK_HOST_CFG, OnButAntiSneakHostCfg)
    ON_BN_CLICKED(IDC_BUT_READER_ANTI_SNEAK_HOST_CFG, OnButReaderAntiSneakHostCfg)
    ON_BN_CLICKED(IDC_BUT_ACS_CFG, OnButAcsCfg)
	ON_BN_CLICKED(IDC_BTN_CARD_USER_INFO, OnBtnCardUserInfo)
    ON_BN_CLICKED(IDC_BUTTON_FACEDETECT, OnButFaceDetect)
    ON_BN_CLICKED(IDC_BUTTON_SNAPCFG, OnButSnapCfg)
    ON_BN_CLICKED(IDC_BUTTON_ACS_EXTERNAL_DEV_CFG, OnButAcsExternalDevCfg)
    ON_BN_CLICKED(IDC_BUTTON_PERSONNEL_CHANNEL_CFG, OnButAcsPersonnelChannelCfg)
	ON_BN_CLICKED(IDC_BTN_GATE_TIME_CFG, OnBtnGateTimeCfg)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_WIEGAND_CFG, &CDlgProductAcs::OnBnClickedButtonWiegandCfg)
	ON_BN_CLICKED(IDC_BUTTON_MOUDLE_STATUS, &CDlgProductAcs::OnBnClickedButtonMoudleStatus)
    ON_BN_CLICKED(IDC_BTN_CAPTURE_FINGER_PRINT, &CDlgProductAcs::OnBnClickedBtnCaptureFingerPrint)
    ON_BN_CLICKED(IDC_BTN_ACS_XML_DIFFUSION, &CDlgProductAcs::OnBnClickedBtnAcsXmlDiffusion)
    ON_BN_CLICKED(IDC_BTN_ACS_ATTENDANCE, &CDlgProductAcs::OnBnClickedBtnAcsAttendance)
    ON_BN_CLICKED(IDC_BUTTON_LOCAL_CONTROLLER_STATUS, &CDlgProductAcs::OnBnClickedButtonLocalControllerStatus)
    ON_BN_CLICKED(IDC_BUTTON_ONLINE_LOCAL_CONTROLLER, &CDlgProductAcs::OnBnClickedButtonOnlineLocalController)
    ON_BN_CLICKED(IDC_BTN_ALARMHOST_ABILITY, &CDlgProductAcs::OnBnClickedBtnAlarmhostAbility)
    ON_BN_CLICKED(IDC_BTN_ZOOM_CODE, &CDlgProductAcs::OnBnClickedBtnZoomCode)
    ON_BN_CLICKED(IDC_BTN_TRIGGER_CODE, &CDlgProductAcs::OnBnClickedBtnTriggerCode)
    ON_BN_CLICKED(IDC_BTN_LOCAL_CONTROLLER_CFG, &CDlgProductAcs::OnBnClickedBtnLocalControllerCfg)
    ON_BN_CLICKED(IDC_BTN_USB_DEVICE_MANAGE, &CDlgProductAcs::OnBnClickedBtnUsbDeviceManage)
    ON_BN_CLICKED(IDC_BTN_EXTERN_MODULE, &CDlgProductAcs::OnBnClickedBtnExternModule)
    ON_BN_CLICKED(IDC_BTN_ACS_FACE_PARAM_CFG, &CDlgProductAcs::OnBnClickedBtnAcsFaceParamCfg)
    ON_BN_CLICKED(IDC_BTN_CAPTURE_FACE, &CDlgProductAcs::OnBnClickedBtnCaptureFace)
    ON_BN_CLICKED(IDC_BTN_UPLOAD_CERTIFICATE_BLACK_LIST, &CDlgProductAcs::OnBnClickedBtnUploadCertificateBlackList)
    ON_BN_CLICKED(IDC_BTN_GET_REGISTER_INFO, &CDlgProductAcs::OnBnClickedBtnGetRegisterInfo)
    ON_BN_CLICKED(IDC_BTN_GET_ACS_EVENT, &CDlgProductAcs::OnBnClickedBtnGetAcsEvent)
    ON_BN_CLICKED(IDC_BTN_SET_EXAM_INFO, &CDlgProductAcs::OnBnClickedBtnSetExamInfo)
    ON_BN_CLICKED(IDC_BTN_SET_EXAMINEE_INFO, &CDlgProductAcs::OnBnClickedBtnSetExamineeInfo)
    ON_BN_CLICKED(IDC_BTN_SEARCH_EXAM_COMPARE_RESULT, &CDlgProductAcs::OnBnClickedBtnSearchExamCompareResult)
    ON_BN_CLICKED(IDC_BTN_UPLOAD_BLACK_LIST_PICTURE, &CDlgProductAcs::OnBnClickedBtnUploadBlackListPicture)
    ON_BN_CLICKED(IDC_BTN_UPLOAD_BLACK_LIST, &CDlgProductAcs::OnBnClickedBtnUploadBlackList)
    ON_BN_CLICKED(IDC_BTN_CHECK_FACE_PICTURE, &CDlgProductAcs::OnBnClickedBtnCheckFacePicture)
    ON_BN_CLICKED(IDC_BTN_FACE_TEMPLATE, &CDlgProductAcs::OnBnClickedBtnFaceTemplate)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgProductAcs message handlers

void CDlgProductAcs::CurCfgUpadate()
{
    int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    if (iDeviceIndex < 0)
    {
        EnableWindow(FALSE);
        return;
    }
   
    EnableWindow(TRUE);
    
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
    if (iChanIndex < 0)
    {
        iChanIndex = 0;//default to config channel one
    }

    m_iDeviceIndex = iDeviceIndex;
    m_lUserID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	m_lChannel= iChanIndex+g_struDeviceInfo[iDeviceIndex].iStartChan;
}

void CDlgProductAcs::OnBtnAcsWorkStatus() 
{
	// TODO: Add your control notification handler code here
    CDlgAcsWorkStatus dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();	
}

void CDlgProductAcs::OnButPlanConfig() 
{
	// TODO: Add your control notification handler code here
	CDlgWeekPlan dlg; 
    dlg.DoModal(); 
}

void CDlgProductAcs::OnButDoorConfig() 
{
	// TODO: Add your control notification handler code here
	CDlgDoorConfig dlg; 
    dlg.DoModal(); 
}

void CDlgProductAcs::OnBtnAcsGroupCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgGroupCfg dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDevIndex = m_iDeviceIndex;
	dlg.m_lChannel = m_lChannel;
	dlg.DoModal(); 
}

void CDlgProductAcs::OnBtnAcsMultiCard() 
{
	// TODO: Add your control notification handler code here
	CDlgMultiCardCfg dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDevIndex = m_iDeviceIndex;
	dlg.m_lChannel = m_lChannel;
	dlg.DoModal(); 
}

void CDlgProductAcs::OnBtnAcsClear() 
{
	// TODO: Add your control notification handler code here
	CDlgClearAcsParam dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDevIndex = m_iDeviceIndex;
	dlg.m_lChannel = m_lChannel;
	dlg.DoModal(); 
}

void CDlgProductAcs::OnBtnSneakAndLock() 
{
	// TODO: Add your control notification handler code here
	CDlgSneakAndLock dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDevIndex = m_iDeviceIndex;
	dlg.m_lChannel = m_lChannel;
	dlg.DoModal(); 
}

#include "DlgACAlarmInOutCfg.h"
void CDlgProductAcs::OnButAlarminAndout() 
{
	// TODO: Add your control notification handler code here
// 	CDlgAlarmHost dlg; 
//     dlg.m_lServerID = m_lUserID;
//     dlg.m_iDevIndex = m_iDeviceIndex;
//     dlg.m_lChannel = m_lChannel;
// 	dlg.DoModal(); 
    CDlgACAlarmInOutCfg dlg; 
    dlg.DoModal(); 
}

void CDlgProductAcs::OnButAcAlarmUser() 
{
	// TODO: Add your control notification handler code here
	CDlgAlarmNetUser dlg; 
    dlg.m_lLoginID = m_lUserID;
    dlg.m_iDevIndex = m_iDeviceIndex;
    dlg.m_dwNetUserNum = 1;
    dlg.DoModal();
}

BOOL CDlgProductAcs::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//GetAlarmHostAbility(m_struAlarmHostAbility); 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgProductAcs::OnBtnCardCfg() 
{
	// TODO: Add your control notification handler code here
    CDlgGatewayCardCfg dlg;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_iDeviceIndex;
	dlg.DoModal();
}

void CDlgProductAcs::OnBtnCaseSensor() 
{
	// TODO: Add your control notification handler code here
	CDlgAcsCaseSensor dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
}

#include "DlgGatewayCfg.h"
void CDlgProductAcs::OnButAcRemotecontrol() 
{
	// TODO: Add your control notification handler code here
    CDlgGatewayCfg dlg;
    dlg.m_lServerID = m_lUserID;
    dlg.m_dwGatawayNum = 128;
    dlg.DoModal();
}

#include "DlgAlarmHostRs485.h"
void CDlgProductAcs::OnButAcRs485() 
{
	// TODO: Add your control notification handler code here
    CDlgAlarmHostRs485 dlg;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_iDeviceIndex;
    memset(&dlg.m_struDevAbility, 0, sizeof(dlg.m_struDevAbility)); 
//    memcpy(&dlg.m_struDevAbility, &m_struAlarmHostAbility, sizeof(m_struAlarmHostAbility));
    dlg.m_i485SlotNum = 1; 
    dlg.m_iRS485Num = 8;
    dlg.DoModal();
}

#include "DlgCardReaderCfg.h"
void CDlgProductAcs::OnButAcCardreadercfg() 
{
	// TODO: Add your control notification handler code here
	CDlgCardReaderCfg dlg; 
    dlg.DoModal(); 
}

#include "DlgCMSParam.h"
void CDlgProductAcs::OnButCmsCfg() 
{
    // TODO: Add your control notification handler code here
    DlgCMSParam dlg; 
    dlg.DoModal(); 
}

#include "DlgAlarmHostNetCfg.h"
void CDlgProductAcs::OnButAlarmHostNetCfg() 
{
    // TODO: Add your control notification handler code here
    CDlgAlarmHostNetCfg dlg; 
    dlg.DoModal(); 
}

#include "DlgAlarmHostGPRS.h"
void CDlgProductAcs::OnButAlarmHostWirelessNetworkCfg() 
{
    // TODO: Add your control notification handler code here
    CDlgAlarmHostGPRS dlg; 
    dlg.DoModal(); 
}

#include "DlgAlarmHostReportMode.h"
void CDlgProductAcs::OnButAlarmHostReportCenterV40() 
{
    // TODO: Add your control notification handler code here
    CDlgAlarmHostReportMode dlg; 
    dlg.DoModal(); 
}

#include "DlgAcsSmsCfg.h"
void CDlgProductAcs::OnButSmsRelativePara() 
{
    // TODO: Add your control notification handler code here
    DlgAcsSmsCfg dlg; 
    dlg.DoModal(); 
}

#include "DlgAcsPhoneDoorRightCfg.h"
void CDlgProductAcs::OnButPhoneDoorRightCfg() 
{
    // TODO: Add your control notification handler code here
    DlgAcsPhoneDoorRightCfg dlg; 
    dlg.DoModal(); 
}

#include "DlgAcsFingerPrintCfg.h"
void CDlgProductAcs::OnButFingerPrintCfg() 
{
    // TODO: Add your control notification handler code here
    DlgAcsFingerPrintCfg dlg; 
    dlg.DoModal(); 
}

#include "DlgAcsCardPasswdCfg.h"
void CDlgProductAcs::OnButPasswdOpenDoor() 
{
    // TODO: Add your control notification handler code here
    DlgAcsCardPasswdCfg dlg; 
    dlg.m_lServerID = m_lUserID;
    dlg.DoModal(); 
}

#include "DlgEventCardLinkageCfg.h"
void CDlgProductAcs::OnButEventCardLinkageCfg() 
{
    // TODO: Add your control notification handler code here
    DlgEventCardLinkageCfg dlg; 
    dlg.DoModal(); 
}

#include "DlgAntiSneakHostCfg.h"
void CDlgProductAcs::OnButAntiSneakHostCfg() 
{
    // TODO: Add your control notification handler code here
    DlgAntiSneakHostCfg dlg; 
    dlg.DoModal(); 
}

#include "DlgReaderAntiSneakHostCfg.h"
void CDlgProductAcs::OnButReaderAntiSneakHostCfg() 
{
    // TODO: Add your control notification handler code here
    DlgReaderAntiSneakHostCfg dlg;
    dlg.DoModal(); 
}

#include "DlgAcsCfg.h"
void CDlgProductAcs::OnButAcsCfg() 
{
    // TODO: Add your control notification handler code here
    DlgAcsCfg dlg; 
    dlg.DoModal(); 
}

void CDlgProductAcs::OnBtnCardUserInfo() 
{
	// TODO: Add your control notification handler code here
	CDlgAcsCardUserInfoCfg dlg;
	dlg.m_lUserID = m_lUserID;
	dlg.m_iDevIndex = m_iDeviceIndex;
	dlg.DoModal();

}

#include "DlgVcaFaceDetect.h"
void CDlgProductAcs::OnButFaceDetect() 
{
    // TODO: Add your control notification handler code here
    CDlgVcaFaceDetect dlg; 
    dlg.m_lServerID = m_lUserID;
    dlg.m_lChannel = m_lChannel;
    dlg.m_iDevIndex = m_iDeviceIndex;
	dlg.m_iChannelNum = 0;
    dlg.m_bACS = TRUE;
    dlg.DoModal(); 
}

#include "DlgAcsSnapCfg.h"
void CDlgProductAcs::OnButSnapCfg() 
{
    // TODO: Add your control notification handler code here
    DlgAcsSnapCfg dlg;
    dlg.DoModal(); 
}

void CDlgProductAcs::OnButAcsExternalDevCfg() 
{
    // TODO: Add your control notification handler code here
    DlgAcsExternalDevCfg dlg;
    dlg.DoModal(); 
}

void CDlgProductAcs::OnButAcsPersonnelChannelCfg() 
{
    // TODO: Add your control notification handler code here
    DlgAcsPersonnelChannelCfg dlg;
    dlg.DoModal(); 
}

#include "DlgACSGateTimeCFG.h"
void CDlgProductAcs::OnBtnGateTimeCfg() 
{
	// TODO: Add your control notification handler code here
    CDlgACSGateTimeCFG dlg;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_iDeviceIndex;
    dlg.DoModal(); 
}


void CDlgProductAcs::OnBnClickedButtonWiegandCfg()
{
	// TODO:  在此添加控件通知处理程序代码
	CDlgWiegandCfg dlg;
	dlg.m_lUserID = m_lUserID;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.DoModal();
}


void CDlgProductAcs::OnBnClickedButtonMoudleStatus()
{
	// TODO:  在此添加控件通知处理程序代码
	CDlgAcsMoudleStatus dlg;
	dlg.m_lUserID = m_lUserID;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.DoModal();
}

#include "DlgCaptureFingerPrint.h"
void CDlgProductAcs::OnBnClickedBtnCaptureFingerPrint()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgCaptureFingerPrint dlg;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_iDeviceIndex;
    dlg.DoModal();
}

#include "DlgAcsXmlDiffusion.h"
void CDlgProductAcs::OnBnClickedBtnAcsXmlDiffusion()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAcsXmlDiffusion dlg;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_iDeviceIndex;
    dlg.DoModal();
}

#include "DlgAcsAttendance.h"
void CDlgProductAcs::OnBnClickedBtnAcsAttendance()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAcsAttendance dlg;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_iDeviceIndex;
    dlg.DoModal();
}



void CDlgProductAcs::OnBnClickedButtonLocalControllerStatus()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAcsLocalControllerStatus dlg;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_iDeviceIndex;
    dlg.DoModal();
}


void CDlgProductAcs::OnBnClickedButtonOnlineLocalController()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAcsOnlineLocalControllerCfg dlg;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_iDeviceIndex;
    dlg.DoModal();
}


void CDlgProductAcs::OnBnClickedBtnAlarmhostAbility()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAlarmHostAbility dlg;
    DWORD dwReturn = 0;
    if (NET_DVR_GetDeviceAbility(m_lUserID, ALARMHOST_ABILITY, NULL, 0, (char*)&(dlg.m_struAlarmHostAbility), sizeof(dlg.m_struAlarmHostAbility)))
    {
        char szLan[128] = { 0 };
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "ALARMHOST_ABILITY");
        dlg.DoModal();
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "ALARMHOST_ABILITY");
    }
}


void CDlgProductAcs::OnBnClickedBtnZoomCode()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAlarmHostZoneAddr dlg;
    dlg.DoModal();
}


void CDlgProductAcs::OnBnClickedBtnTriggerCode()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAlarmHostTriggerCode dlg;
    dlg.DoModal();
}

void CDlgProductAcs::OnBnClickedBtnLocalControllerCfg()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAcsLocalControllerCfg dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
}


void CDlgProductAcs::OnBnClickedBtnUsbDeviceManage()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAcsUSBDeviceManage dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
}


void CDlgProductAcs::OnBnClickedBtnExternModule()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAlarmHostExternalModule dlg;
    dlg.DoModal();
}


void CDlgProductAcs::OnBnClickedBtnAcsFaceParamCfg()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAcsFaceParamCfg dlg;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_iDeviceIndex;
    dlg.DoModal();
}

#include "DlgCaptureFace.h"
void CDlgProductAcs::OnBnClickedBtnCaptureFace()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgCaptureFace dlg;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_iDeviceIndex;
    dlg.DoModal();
}

void CDlgProductAcs::OnBnClickedBtnUploadCertificateBlackList()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgUploadBlackList dlg;
    dlg.m_lServerID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.m_lChannel = m_lChannel;
    dlg.DoModal();
}

void CDlgProductAcs::OnBnClickedBtnGetRegisterInfo()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgGetRegisterInfo dlg;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_iDeviceIndex;
    dlg.DoModal();
}

#include "DlgAcsLogSearch.h"
void CDlgProductAcs::OnBnClickedBtnGetAcsEvent()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAcsLogSearch dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
}

#include "DlgAcsSetExamInfo.h"
void CDlgProductAcs::OnBnClickedBtnSetExamInfo()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAcsSetExamInfo dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
}

#include "DlgAcsSetExamineeInfo.h"
void CDlgProductAcs::OnBnClickedBtnSetExamineeInfo()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAcsSetExamineeInfo dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
}

#include "DlgAcsSearchExamCompareResult.h"
void CDlgProductAcs::OnBnClickedBtnSearchExamCompareResult()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAcsSearchExamCompareResult dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
}

void CDlgProductAcs::OnBnClickedBtnUploadBlackListPicture()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgUploadBlackListPicture dlg;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
}


void CDlgProductAcs::OnBnClickedBtnUploadBlackList()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgBatchUploadBlackList dlg;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
}


void CDlgProductAcs::OnBnClickedBtnCheckFacePicture()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAcsCheckFacePicture dlg;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
}


void CDlgProductAcs::OnBnClickedBtnFaceTemplate()
{
    DlgAcsFaceAndTemplate dlg;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
}
