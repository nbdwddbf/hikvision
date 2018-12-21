// DlgTrialDVR.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgTrialDVR.h"
#include "DlgTrialAudioActivation.h"
#include "DlgInfrared.h"
#include "DlgTrialPIPCfg.h"
#include "DlgAccessCameraCfg.h"
#include "DlgMixAudioInCfg.h"
#include "DlgWifiDHCPCfg.h"
#include "DlgGetWifiClientListInfo.h"
#include "DlgAudioDiacriticalCfg.h"
#include "DlgMultilStreamRelChanCfg.h"
#include "DlgVideoOutResolutionCfg.h"
#include "DlgMixAudioOutCfg.h"
#include "DlgRemoteControlPlay.h"
#include "DlgCaseInfo.h"
#include "DlgMicrophoneStatus.h"
#include "DlgTrialHostStatus.h"
#include "DlgLocalInputInfo.h"
#include "DlgLampCfg.h"
#include "DlgLampControl.h"
#include "DlgAudioOutVolumeCfg.h"
#include "DlgAudioInVolumeCfg1.h"
#include "DlgAreaMaskCfg.h"
#include "DlgInChanVideoLostCfg.h"
#include "DLGTrialAudioMix.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTrialDVR dialog


CDlgTrialDVR::CDlgTrialDVR(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTrialDVR::IDD, pParent)
    ,m_lUserID(-1)
    ,m_iDevIndex(-1)

{
	//{{AFX_DATA_INIT(CDlgTrialDVR)
	m_wHDMINum = 0;
	m_wIPNum = 0;
	m_wPIPNum = 0;
	m_wSDINum = 0;
	m_wHDMIStartNo = 0;
	m_wIPStartNo = 0;
	m_wPIPStartNo = 0;
	m_wSDIStartNo = 0;
	m_wVGAStartNo = 0;
	m_wVGANum = 0;
	m_wPOEStartNo = 0;
	m_wYPBPRStartNo = 0;
	m_wPOENum = 0;
	m_wYPBPRNum = 0;
	//}}AFX_DATA_INIT
}


void CDlgTrialDVR::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTrialDVR)
	DDX_Text(pDX, IDC_EDIT_HDMI_NUM, m_wHDMINum);
	DDX_Text(pDX, IDC_EDIT_IP_NUM, m_wIPNum);
	DDX_Text(pDX, IDC_EDIT_PIP_NUM, m_wPIPNum);
	DDX_Text(pDX, IDC_EDIT_SDI_NUM, m_wSDINum);
	DDX_Text(pDX, IDC_EDIT_START_NO_HDMI, m_wHDMIStartNo);
	DDX_Text(pDX, IDC_EDIT_START_NO_IP, m_wIPStartNo);
	DDX_Text(pDX, IDC_EDIT_START_NO_PIP, m_wPIPStartNo);
	DDX_Text(pDX, IDC_EDIT_START_NO_SDI, m_wSDIStartNo);
	DDX_Text(pDX, IDC_EDIT_START_NO_VGA, m_wVGAStartNo);
	DDX_Text(pDX, IDC_EDIT_VGA_NUM, m_wVGANum);
	DDX_Text(pDX, IDC_EDIT_START_NO_POE, m_wPOEStartNo);
	DDX_Text(pDX, IDC_EDIT_START_NO_YPBPR, m_wYPBPRStartNo);
	DDX_Text(pDX, IDC_EDIT_POE_NUM, m_wPOENum);
	DDX_Text(pDX, IDC_EDIT_YPBPR_NUM, m_wYPBPRNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTrialDVR, CDialog)
	//{{AFX_MSG_MAP(CDlgTrialDVR)
	ON_BN_CLICKED(IDC_BTN_AUDIO_ACTIVATION, OnBtnAudioActivation)
	ON_BN_CLICKED(IDC_BTN_INFRARED, OnBtnInfrared)
	ON_BN_CLICKED(IDC_BTN_GET_SYSTEM_INFO, OnBtnGetSystemInfo)
	ON_BN_CLICKED(IDC_BTN_PIP_CFG, OnBtnPipCfg)
	ON_BN_CLICKED(IDC_BTN_REMOTE_PLAY, OnBtnRemotePlay)
	ON_BN_CLICKED(IDC_BTN_CASE_INFO, OnBtnCaseInfo)
	ON_BN_CLICKED(IDC_BTN_MICROPHONE_STATUS, OnBtnMicrophoneStatus)
	ON_BN_CLICKED(IDC_BTN_TRIAL_HOST_STATUS, OnBtnTrialHostStatus)
	ON_BN_CLICKED(IDC_BTN_LOCAL_INPUT, OnBtnLocalInput)
	ON_BN_CLICKED(IDC_BTN_LAMP_INFO, OnBtnLampInfo)
	ON_BN_CLICKED(IDC_BTN_LAMP_CONTROL, OnBtnLampControl)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG_CAMERA_TYPE, OnButtonConfigCameraType)
	ON_BN_CLICKED(IDC_BTN_MIX_AUDIOIN_CFG, OnButtonMixAudioInParamCfg)
 	ON_BN_CLICKED(IDC_BTN_MIX_AUDIOOUT_CFG, OnButtonMixAudioOutParamCfg)
	ON_BN_CLICKED(IDC_BTN_AUDIOIN_VOLUME_CFG, OnButtonAudioInVolumeCfg)
	ON_BN_CLICKED(IDC_BTN_AUDIOOUT_VOLUME_CFG, OnButtonAudioOutVolumeCfg)
	ON_BN_CLICKED(IDC_BTN_AREA_MASK_CFG, OnButtonMaskAreaParamCfg)
	ON_BN_CLICKED(IDC_BTN_AUDIO_DIACRITICAL_CFG, OnButtonAudioDiacriticalCfg)
	ON_BN_CLICKED(IDC_BTN_VIDEO_OUT_RESOLUTION_CFG, OnButtonVideoOutResolutionCfg)
	ON_BN_CLICKED(IDC_BTN_MULTISTREAM_RELATION_CHAN_CFG, OnButtonMultilStreamRelChanCfg)
	ON_BN_CLICKED(IDC_BTN_REMOTECONTROL_POWER_ON, OnButtonRemotePowerOn)
	ON_BN_CLICKED(IDC_BTN_WIFI_DHCP_ADDR_CFG, OnButtonWifiDHCPCfg)
 	ON_BN_CLICKED(IDC_BTN_WIFI_CLIENT_LIST_INFO, OnButtonGetWifiClientListInfo)
    ON_BN_CLICKED(IDC_BTN_INCHANNEL_VIDEO,OnBtnInChannelVideLossCfg)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_AUDIO_MIX, &CDlgTrialDVR::OnBnClickedBtnAudioMix)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTrialDVR message handlers

void CDlgTrialDVR::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlgTrialDVR::OnBtnAudioActivation() 
{
	// TODO: Add your control notification handler code here
    CDlgTrialAudioActivation dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDevIndex = m_iDevIndex;
    memcpy(&(dlg.m_struSystemInfo),&m_struTrialSysInfo,sizeof(m_struTrialSysInfo));
    dlg.DoModal();
}

void CDlgTrialDVR::OnBtnInfrared() 
{
	// TODO: Add your control notification handler code here
    CDlgInfrared dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDevIndex = m_iDevIndex;
 
    dlg.DoModal();
}

void CDlgTrialDVR::OnBtnGetSystemInfo() 
{
	// TODO: Add your control notification handler code here
	memset(&m_struTrialSysInfo,0,sizeof(m_struTrialSysInfo));

    if (m_iDevIndex < 0)
    {
        return;
    }

    DWORD dwRet = 0 ;
    if (!NET_DVR_GetDVRConfig(m_lUserID,NET_DVR_GET_TRIAL_SYSTEM_CFG,NULL,&m_struTrialSysInfo,sizeof(m_struTrialSysInfo),&dwRet))
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_GET_TRIAL_SYSTEM_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_GET_TRIAL_SYSTEM_CFG");
    }

    for (int i = 0; i < m_struTrialSysInfo.byVideoInTypeNum; i++)
    {
        switch (m_struTrialSysInfo.struVideoIn[i].wInType)
        {
        case 0:
            m_wSDINum = m_struTrialSysInfo.struVideoIn[i].wInNum;
            m_wSDIStartNo = m_struTrialSysInfo.struVideoIn[i].wStartNo;
            break;
        case  1:
            m_wVGANum = m_struTrialSysInfo.struVideoIn[i].wInNum;
            m_wVGAStartNo = m_struTrialSysInfo.struVideoIn[i].wStartNo;
            break;
        case 2:
            m_wHDMINum = m_struTrialSysInfo.struVideoIn[i].wInNum;
            m_wHDMIStartNo = m_struTrialSysInfo.struVideoIn[i].wStartNo;
            break;
        case 3:
            m_wIPNum = m_struTrialSysInfo.struVideoIn[i].wInNum;
            m_wIPStartNo = m_struTrialSysInfo.struVideoIn[i].wStartNo;
            break;
        case 4:
            m_wPIPNum = m_struTrialSysInfo.struVideoIn[i].wInNum;
            m_wPIPStartNo = m_struTrialSysInfo.struVideoIn[i].wStartNo;
            break;
        case 5:
            m_wPOENum = m_struTrialSysInfo.struVideoIn[i].wInNum;
            m_wPOEStartNo = m_struTrialSysInfo.struVideoIn[i].wStartNo;
            break;
        case 6:
            m_wYPBPRNum = m_struTrialSysInfo.struVideoIn[i].wInNum;
            m_wYPBPRStartNo = m_struTrialSysInfo.struVideoIn[i].wStartNo;
            break;
        default:
            break;
        }
    }
    
    UpdateData(FALSE);

}

BOOL CDlgTrialDVR::OnInitDialog() 
{
	CDialog::OnInitDialog();
	memset(&m_struTrialSysInfo,0,sizeof(m_struTrialSysInfo));
	// TODO: Add extra initialization here
	OnBtnGetSystemInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTrialDVR::OnBtnPipCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgTrialPIPCfg dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDevIndex = m_iDevIndex;
       memcpy(&(dlg.m_struSystemInfo),&m_struTrialSysInfo,sizeof(m_struTrialSysInfo));
    dlg.DoModal();
}


void CDlgTrialDVR::OnBtnRemotePlay() 
{
	// TODO: Add your control notification handler code here
	CDlgRemoteControlPlay dlg;
	dlg.DoModal();
}

void CDlgTrialDVR::OnBtnCaseInfo() 
{
	// TODO: Add your control notification handler code here
	CDlgCaseInfo dlg;
	dlg.DoModal();
}

void CDlgTrialDVR::OnBtnMicrophoneStatus() 
{
	// TODO: Add your control notification handler code here
	CDlgMicrophoneStatus dlg;
	dlg.DoModal();
}

void CDlgTrialDVR::OnBtnTrialHostStatus() 
{
	// TODO: Add your control notification handler code here
	CDlgTrialHostStatus dlg;
	dlg.DoModal();
}

void CDlgTrialDVR::OnBtnLocalInput() 
{
	// TODO: Add your control notification handler code here
	CDlgLocalInputInfo dlg;
	dlg.setParam(m_struTrialSysInfo);
	dlg.DoModal();
}


void CDlgTrialDVR::OnBtnLampInfo() 
{
	// TODO: Add your control notification handler code here
	CDlgLampCfg dlg;
	dlg.DoModal();
}


void CDlgTrialDVR::OnBtnLampControl() 
{
	// TODO: Add your control notification handler code here
	CDlgLampControl dlg;
	dlg.DoModal();
}


void CDlgTrialDVR::OnButtonConfigCameraType() 
{
	// TODO: Add your control notification handler code here
	CDlgAccessCameraCfg dlg;
	dlg.m_lUserID = m_lUserID;
    dlg.m_dwDevIndex = m_iDevIndex;

	int iChanIndex = g_pMainDlg->GetCurChanIndex();
    if (iChanIndex < 0)
    {
        iChanIndex = 0;//default to config channel one
    }
	m_lChannel= iChanIndex+g_struDeviceInfo[m_iDevIndex].iStartChan;
    dlg.m_bTrialChannelFlag = 1;
    dlg.DoModal();
}

void CDlgTrialDVR::OnButtonMixAudioInParamCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgMixAudioInCfg dlg;
	dlg.m_lUserID = m_lUserID;
    dlg.m_dwDevIndex = m_iDevIndex;
	
    dlg.DoModal();
}

void CDlgTrialDVR::OnButtonMixAudioOutParamCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgMixAudioOutCfg dlg;
	dlg.m_lUserID = m_lUserID;
    dlg.m_dwDevIndex = m_iDevIndex;
	
    dlg.DoModal();
}


void CDlgTrialDVR::OnButtonVideoOutResolutionCfg()
{
	// TODO: Add your control notification handler code here
	CDlgVideoOutResolutionCfg dlg;
	dlg.m_lUserID = m_lUserID;
    dlg.m_dwDevIndex = m_iDevIndex;
	
    dlg.DoModal();
}


void CDlgTrialDVR::OnButtonMultilStreamRelChanCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgMultilStreamRelChanCfg dlg;
	dlg.m_lUserID = m_lUserID;
    dlg.m_dwDevIndex = m_iDevIndex;
	
    dlg.DoModal();
}

void CDlgTrialDVR::OnButtonWifiDHCPCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgWifiDHCPCfg dlg;
	dlg.m_lUserID = m_lUserID;
    dlg.m_dwDevIndex = m_iDevIndex;
	
    dlg.DoModal();
}


void CDlgTrialDVR::OnButtonGetWifiClientListInfo()
{
	// TODO: Add your control notification handler code here
	CDlgGetWifiClientListInfo dlg;
	dlg.m_lUserID = m_lUserID;
    dlg.m_dwDevIndex = m_iDevIndex;
	
    dlg.DoModal();
}


void CDlgTrialDVR::OnButtonAudioDiacriticalCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgAudioDiacriticalCfg dlg;
	dlg.m_lUserID = m_lUserID;
    dlg.m_dwDevIndex = m_iDevIndex;
	
    dlg.DoModal();
}

void CDlgTrialDVR::OnButtonAudioInVolumeCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgAudioInVolumeCfg dlg;
	dlg.m_lUserID = m_lUserID;
    dlg.m_dwDevIndex = m_iDevIndex;
	
    dlg.DoModal();
}


void CDlgTrialDVR::OnButtonAudioOutVolumeCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgAudioOutVolumeCfg dlg;
	dlg.m_lUserID = m_lUserID;
    dlg.m_dwDevIndex = m_iDevIndex;
	
    dlg.DoModal();
}


void CDlgTrialDVR::OnButtonMaskAreaParamCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgAreaMaskCfg dlg;
	dlg.m_lUserID = m_lUserID;
    dlg.m_dwDevIndex = m_iDevIndex;

	int iChanIndex = g_pMainDlg->GetCurChanIndex();
    if (iChanIndex < 0)
    {
        iChanIndex = 0;//default to config channel one
    }
	m_lChannel= iChanIndex+g_struDeviceInfo[m_iDevIndex].iStartChan;
	dlg.m_lChannel = m_lChannel;
	
    dlg.DoModal();
}


void CDlgTrialDVR::OnButtonRemotePowerOn() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	
	/*if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_REMOTECONTROL_POWER_ON, NULL, 0))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_POWER_ON ");
		g_StringLanType(szLan, "²Ù×÷Ê§°Ü", "control failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_POWER_ON");
	}
    */
}

void CDlgTrialDVR::OnBtnInChannelVideLossCfg()
{
    CDlgInChanVideoLostCfg dlg;
    dlg.m_lLoginID = m_lUserID;
   // dlg.m_dwAlarmOutNum = m_dwAlarmOutNum;
    dlg.m_iDevIndex = m_iDevIndex;
    memcpy(&(dlg.m_struSystemInfo),&m_struTrialSysInfo,sizeof(m_struTrialSysInfo));
    dlg.DoModal();

//ConvertVilostV40T0V30();
    /*g_lpVILostV40 = &(m_pStruPicCfgV40[m_iCurChanIndex].struVILost);
    dlg.m_iChanShowNum = m_iChanShowNum;

    if (dlg.DoModal() == IDOK)
    {
        
	}  
    */
}

void  CDlgTrialDVR::ConvertVilostV40T0V30(NET_DVR_VILOST_V40 *pViLostV40, NET_DVR_VILOST_V30 *pViLostV30,BOOL bV40ToV30)
{
    if (pViLostV30== NULL || pViLostV40==NULL)
    {
        return;
    }

    int i =0 ;
    DWORD dwIndex = 0;

    if(bV40ToV30)
    {
        memset(pViLostV30,0,sizeof(NET_DVR_VILOST_V30));
        pViLostV30->byEnableHandleVILost = pViLostV40->dwEnableVILostAlarm;
        pViLostV30->strVILostHandleType.dwHandleType = pViLostV40->dwHandleType;
        for (i =0; i< MAX_ALARMOUT_V40;i++)
        {
            if(pViLostV40->dwRelAlarmOut[i] != 0xffffffff && i < MAX_ALARMOUT_V30)
            {
                pViLostV30->strVILostHandleType.byRelAlarmOut[i] = pViLostV40->dwRelAlarmOut[i];
            }
            else
            {
                break;
            }
        }

        memcpy(&pViLostV30->struAlarmTime[0],&pViLostV40->struAlarmTime[0],sizeof(pViLostV30->struAlarmTime));

    }
    else
    {
        memset(pViLostV40,0,sizeof(NET_DVR_VILOST_V40));
        memset(pViLostV40->dwRelAlarmOut,0xff,sizeof(DWORD)*MAX_ALARMOUT_V40);
        pViLostV40->dwEnableVILostAlarm = pViLostV30->byEnableHandleVILost;
        pViLostV40->dwHandleType = pViLostV30->strVILostHandleType.dwHandleType;
        for (i = 0; i< MAX_ALARMOUT_V30; i++)
        {
            if (pViLostV30->strVILostHandleType.byRelAlarmOut[i] == 1)
            {
                pViLostV40->dwRelAlarmOut[dwIndex] = i;
                dwIndex++;
            }
        }
        memcpy(&pViLostV40->struAlarmTime[0],&pViLostV30->struAlarmTime[0],sizeof(pViLostV30->struAlarmTime));
    }
}

void CDlgTrialDVR::OnBnClickedBtnAudioMix()
{
    CDLGTrialAudioMix dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_dwDevIndex = m_iDevIndex;

    int iChanIndex = g_pMainDlg->GetCurChanIndex();
    if (iChanIndex < 0)
    {
        iChanIndex = 0;//default to config channel one
    }
    m_lChannel = iChanIndex + g_struDeviceInfo[m_iDevIndex].iStartChan;

    dlg.DoModal();
}
