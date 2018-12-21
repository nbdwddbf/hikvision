// SubDlgDVRNVRCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "SubDlgDVRNVRCfg.h"
#include "DlgNetServiceCfg.h"
#include "DlgCertInfo.h"
#include "DlgNetraEventVedio.h"
#include "DlgVedioAudioInCfg.h"
#include "DlgVCADetionCfg.h"
#include "DlgIPCSimpIntellCfg.h"
#include "DlgImExportIPCCfgFile.h"
#include "DlgVQDCfg.h"
#include "DlgNVRCfg.h"
#include "DlgGetDigitalChannelStatus.h"
#include "DlgUpgradeIPC.h"
#include "DlgAtmFrameFormatV30.h"
#include "DlgInquestDvr.h"
#include "DlgVehicleCfg.h"
#include "DlgDevWorkMode.h"
#include "DlgGopInfo.h"
#include "DlgRecordHost.h"
#include "DlgRemoteAlarmDetectFace.h"
#include "DlgIPCPlateRecog.h"
#include "DlgNVRIPCCfg.h"
#include "DlgVcaDetectionCfg.h"
#include "DlgHeatMapCfg.h"
#include "DlgPdcRuleCfgEx.h"
#include "DlgvcaMaskRegion.h"
#include "DlgVcaDrawMode.h"
#include "DlgVcaFaceSnapCfg.h"
#include "DlgFishEye.h"
#include "DlgLimitAngle.h"
#include "DlgVcaTrackCfg.h"
#include "DlgVcaChanCtrlCfg.h"
#include "DlgPositionTrackCfg.h"
#include "DlgVcaPositionRule.h"
#include "DlgPicModelCfg.h"
#include "DlgMouseEvent.h"
#include "DlgGB28181ServerCfg.h"
#include "DlgPosManage.h"
#include "DlgVedioImgDB.h"
#include "DlgRecordHostV120.h"
#include "DlgAreaMonitorCfg.h"
#include "DlgCloudManage.h"
#include "DlgPicBatchUpload.h"
#include "DlgPtzNotification.h"
#include "DLGGetChannelInfo.h"
#include "DLGResetLoginPassWord.h"
#include "DlgSuperBrainFunctionTest.h"
#include "DlgCluster.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubDlgDVRNVRCfg dialog


CSubDlgDVRNVRCfg::CSubDlgDVRNVRCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubDlgDVRNVRCfg::IDD, pParent)
    ,m_lUserID(-1)
    ,m_lChanNo(-1)
    ,m_iDevIndex(-1)
{
	//{{AFX_DATA_INIT(CSubDlgDVRNVRCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSubDlgDVRNVRCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubDlgDVRNVRCfg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubDlgDVRNVRCfg, CDialog)
	//{{AFX_MSG_MAP(CSubDlgDVRNVRCfg)
	ON_BN_CLICKED(IDC_BTN_NET_SERVICE, OnBtnNetService)
	ON_BN_CLICKED(IDC_BTN_CERT, OnBtnCert)
	ON_BN_CLICKED(IDC_BTN_EVENT_RECORD, OnBtnEventRecord)
	ON_BN_CLICKED(IDC_BTN_AUDIOINPUT, OnBtnAudioinput)
	ON_BN_CLICKED(IDC_BTN_VCA_DETECTION, OnBtnVcaDetection)
	ON_BN_CLICKED(IDC_BTM_SMD, OnBtmSmd)
	ON_BN_CLICKED(IDC_BTN_IM_EXPORT_IPC_CFG_FILE, OnBtnImExportIpcCfgFile)
	ON_BN_CLICKED(IDC_BTN_VQD_CFG, OnBtnVqdCfg)
	ON_BN_CLICKED(IDC_BTN_NVRCFG, OnBtnNvrcfg)
	ON_BN_CLICKED(IDC_BTN_GET_IPCSTATIUS, OnBtnGetIPCStatus)
	ON_BN_CLICKED(IDC_BTN_UPGRADE_IPC, OnBtnUpgradeIpc)
	ON_BN_CLICKED(IDC_BTN_ATM, OnBtnAtm)
	ON_BN_CLICKED(IDC_BTN_INQUEST, OnBtnInquest)
    ON_BN_CLICKED(IDC_BTN_VEHICLECFG, OnBtnVehicleCfg)
	ON_BN_CLICKED(IDC_BTN_WORKMODE, OnBtnWorkmode)
    ON_BN_CLICKED(IDC_BTN_GOP_INFO, OnBtnGetGopInfo)
	ON_BN_CLICKED(IDC_BTN_RECORD_HOST, OnBtnRecordHost)
	ON_BN_CLICKED(IDC_BTN_TRIAL, OnBtnTrial)
	ON_BN_CLICKED(IDC_BTN_FACEDETECTION, OnBtnFacedetection)
	ON_BN_CLICKED(IDC_BTN_IPC_PLATE_RECOG, OnBtnIpcPlateRecog)
	ON_BN_CLICKED(IDC_BTN_IPC_CFG, OnBtnIpcCfg)
	ON_BN_CLICKED(IDC_BTN_HEATMAP, OnBtnHeatmap)
	ON_BN_CLICKED(IDC_BTN_PDC_RULE, OnBtnPdcRule)
	ON_BN_CLICKED(IDC_BTN_MASK_REGION, OnBtnMaskRegion)
	ON_BN_CLICKED(IDC_BTN_VCA_DRAW_MODE, OnBtnVcaDrawMode)
	ON_BN_CLICKED(IDC_BTN_VCA_FACESNAPCFG, OnBtnVcaFacesnapcfg)
	ON_BN_CLICKED(IDC_BTN_PREVIEW_DISPLAYCFG, OnBtnPreviewDisplaycfg)
	ON_BN_CLICKED(IDC_BTN_POSITION_LIMIT_ANGLE, OnBtnPositionLimitAngle)
	ON_BN_CLICKED(IDC_BTN_TRACK_CFG, OnBtnTrackCfg)
	ON_BN_CLICKED(IDC_BTN_VCA_CTRL, OnBtnVcaCtrl)
	ON_BN_CLICKED(IDC_BTN_VCA_VERSION, OnBtnVcaVersion)
	ON_BN_CLICKED(IDC_BTN_POSITION_TRACKCFG, OnBtnPositionTrackcfg)
	ON_BN_CLICKED(IDC_BTN_VCARULE_CFG, OnBtnVcaruleCfg)
	ON_BN_CLICKED(IDC_BTN_PIC_MODEL_CFG, OnBtnPicModelCfg)
	ON_BN_CLICKED(IDC_BTN_MOUSE_EVENT, OnBtnMouseEvent)
	ON_BN_CLICKED(IDC_BTN_GB28181_SERVER, OnBtnGb28181Server)
    ON_BN_CLICKED(IDC_BUTTON_POS, OnBtnPos)
	ON_BN_CLICKED(IDC_BUTTON_VEDIO_IMG_DB, OnButtonVedioImgDb)
	ON_BN_CLICKED(IDC_BTN_RECORD_HOST_CFG, OnBtnRecordHostCfg)
	ON_BN_CLICKED(IDC_BTN_VCA, OnBtnVca)
	ON_BN_CLICKED(IDC_BTN_CLOUD, &CSubDlgDVRNVRCfg::OnBnClickedBtnCloud)

    ON_BN_CLICKED(IDC_BTN_ACCESSSORY_CARD_INFO_GET, &CSubDlgDVRNVRCfg::OnBnClickedBtnAccesssoryCardInfoGet)
    ON_BN_CLICKED(IDC_BTN_PIC_BATCH_UPLOAD, &CSubDlgDVRNVRCfg::OnBnClickedBtnPicBatchUpload)
	//}}AFX_MSG_MAP	
    ON_BN_CLICKED(IDC_BTN_ACCESSSORY_CARD_INFO_GET, &CSubDlgDVRNVRCfg::OnBnClickedBtnAccesssoryCardInfoGet)
    ON_BN_CLICKED(IDC_BTN_PTZ_NOTIFICATION, &CSubDlgDVRNVRCfg::OnBnClickedBtnPtzNotification)
    ON_BN_CLICKED(IDC_BTN_CHANNEL_INFO, &CSubDlgDVRNVRCfg::OnBnClickedBtnChannelInfo)
    ON_BN_CLICKED(IDC_BTN_RESET_PASSWORD, &CSubDlgDVRNVRCfg::OnBnClickedBtnResetPassword)
    ON_BN_CLICKED(IDC_BUTTON_SUPER_BRAIN_FUNCTION_TEST, &CSubDlgDVRNVRCfg::OnBnClickedButtonSuperBrainFunctionTest)
    ON_BN_CLICKED(IDC_BUTTON_CLUSTER, &CSubDlgDVRNVRCfg::OnBnClickedButtonCluster)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubDlgDVRNVRCfg message handlers

BOOL CSubDlgDVRNVRCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSubDlgDVRNVRCfg::OnBtnNetService() 
{
	// TODO: Add your control notification handler code here
    CDlgNetServiceCfg dlg;
    if (m_iDevIndex < 0)
    {
        AfxMessageBox("Login First!");
        return;
    }
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnCert() 
{
	// TODO: Add your control notification handler code here
	CDlgCertInfo dlg;
    if (m_iDevIndex < 0)
    {
        AfxMessageBox("Login First!");
        return;
    }
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();

}

void CSubDlgDVRNVRCfg::OnBtnEventRecord()
{
    CDlgNetraEventVedio dlg;
    if (m_iDevIndex < 0)
    {
        AfxMessageBox("Login First!");
        return;
    }
    dlg.m_lLoginID = m_lUserID;
    dlg.m_lChannel = m_lChanNo;
    dlg.m_iDeviceIndex = m_iDevIndex;
    dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnAudioinput() 
{
	// TODO: Add your control notification handler code here
   	DlgVedioAudioInCfg dlg; 
    if (m_iDevIndex < 0)
    {
        AfxMessageBox("Login First!");
        return;
    }
    dlg.m_VedioChannel  = m_lChanNo;
    dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnVcaDetection() 
{
	// TODO: Add your control notification handler code here
/*	DlgVCADetionCfg dlg;
    dlg.m_ChannelNo  = m_lChanNo;
    dlg.DoModal();
    */
    CDlgVcaDetectionCfg dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtmSmd() 
{
	// TODO: Add your control notification handler code here
    CDlgIPCSimpIntellCfg dlg;
    dlg.m_lLoginID = m_lUserID;	
    dlg.m_iDeviceIndex = m_iDevIndex;			
    dlg.m_lChannel = m_lChanNo;
    dlg.m_iChanCount = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;
    dlg.m_iAnaChanCount = g_struDeviceInfo[m_iDevIndex].iAnalogChanNum;
    dlg.m_iDStartChannel = g_struDeviceInfo[m_iDevIndex].pStruIPParaCfgV40[0].dwStartDChan;
    if (m_iDevIndex < 0)
    {
        AfxMessageBox("Login First!");
        return;
    }
	dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnImExportIpcCfgFile() 
{
	// TODO: Add your control notification handler code here
    DlgImexporIPCCfgFile dlg;
    if (m_iDevIndex < 0)
    {
        AfxMessageBox("Login First!");
        return;
    }
	dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnVqdCfg() 
{
	// TODO: Add your control notification handler code here
    CDlgVQDCfg dlg;
    if (m_iDevIndex < 0)
    {
        AfxMessageBox("Login First!");
        return;
    }
    dlg.m_lUserID = m_lUserID;	
    dlg.m_iDevIndex = m_iDevIndex;			
    //	dlg.m_lChannel = iChanIndex + g_struDeviceInfo[iDeviceIndex].iStartChan;
	dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnNvrcfg() 
{
	// TODO: Add your control notification handler code here
     
    CDlgNVRCfg dlg;
	int iChanIndex = g_pMainDlg->GetCurChanIndex();

    if (m_iDevIndex < 0)
    {
        AfxMessageBox("Login First!");
        return;
    }

    dlg.m_lUserID = g_struDeviceInfo[m_iDevIndex].lLoginID;
    dlg.m_iDevIndex = m_iDevIndex;
	dlg.m_lChannel = g_struDeviceInfo[m_iDevIndex].pStruChanInfo[iChanIndex].iChannelNO;
	dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnGetIPCStatus() 
{
	// TODO: Add your control notification handler code here
    // TODO: Add your command handler code here
   
    if (m_iDevIndex < 0)
    {
        AfxMessageBox("Login First!");
        return;
    }
    
    CDlgGetDigitalChannelStatus dlg;
    dlg.m_lUserID = g_struDeviceInfo[m_iDevIndex].lLoginID;
    dlg.m_dwDevIndex = m_iDevIndex;
    
	dlg.DoModal();
}
void CSubDlgDVRNVRCfg::CurCfgUpdate()
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
    m_iDevIndex = iDeviceIndex;
    m_lUserID = g_struDeviceInfo[iDeviceIndex].lLoginID;
    m_lChanNo= g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].iChannelNO;
   // m_lChanCount = g_struDeviceInfo[iDeviceIndex].iDeviceChanNum;
}
void CSubDlgDVRNVRCfg::OnBtnUpgradeIpc() 
{
	// TODO: Add your control notification handler code here
    CDlgUpgradeIPC dlg;
    if (m_iDevIndex < 0)
    {
        AfxMessageBox("Login First!");
        return;
    }
    dlg.m_lUserID = m_lUserID;
    dlg.m_dwDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnAtm() 
{
	// TODO: Add your control notification handler code here
    
    CDlgAtmFrameFormatV30 dlg;
    if (m_iDevIndex < 0)
    {
        AfxMessageBox("Login First!");
        return;
    }
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_iChannelNum = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;
    dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnInquest() 
{
	// TODO: Add your control notification handler code here
    CDlgInquestDvr dlg;
    if (m_iDevIndex < 0)
    {
        AfxMessageBox("Login First!");
        return;
    }
    dlg.m_dwDeviceIndex = m_iDevIndex;
    dlg.m_lLoginID = m_lUserID;
	dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnVehicleCfg()
{
       if (m_iDevIndex < 0)
    {
        AfxMessageBox("Login First!");
        return;
    }
    if (m_lChanNo < 0)
    {
        m_lChanNo = 0;//default to config channel one
    }
    
    CDlgVehicleCfg dlg;
    dlg.m_lServerID = m_lUserID;
    dlg.m_dwAlarmOutNum = g_struDeviceInfo[m_iDevIndex].iAlarmOutNum;
    dlg.m_dwDevIndex = m_iDevIndex;
    dlg.m_nChannel = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;
    dlg.m_lStartChan = g_struDeviceInfo[m_iDevIndex].iStartChan;
    dlg.m_iChannelIndex = m_iDevIndex + g_struDeviceInfo[m_iDevIndex].iStartChan;
 	dlg.DoModal();
}
void CSubDlgDVRNVRCfg::OnBtnWorkmode() 
{
	// TODO: Add your control notification handler code here
    CDlgDevWorkMode dlg;
    if (m_iDevIndex < 0)
    {
        AfxMessageBox("Login First!");
        return;
    }
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel = m_lChanNo;
    dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnGetGopInfo()
{
    CDlgGopInfo dlg;
    if (m_iDevIndex < 0)
    {
        AfxMessageBox("Login First!");
        return;
    }

    dlg.m_lUserID = m_lUserID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnRecordHost()
{
	DlgRecordHost dlg;
	dlg.m_lServerID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDevIndex;
	dlg.m_iMirrorNum = g_struDeviceInfo[m_iDevIndex].byMirrorChanNum;
	dlg.m_iStartChannel = g_struDeviceInfo[m_iDevIndex].wStartMirrorChanNo;
	dlg.DoModal();
}

#include "DlgTrialDVR.h"
void CSubDlgDVRNVRCfg::OnBtnTrial() 
{
	// TODO: Add your control notification handler code here
    if (m_iDevIndex < 0)
    {
        return;
    }
    if (m_lChanNo < 0)
    {
        m_lChanNo = 0;//default to config channel one
    }
    
    CDlgTrialDVR dlg;
    dlg.m_lUserID = m_lUserID;
	
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnFacedetection() 
{
	// TODO: Add your control notification handler code here
	CDlgRemoteAlarmDetectFace dlg;
	dlg.m_dwDevIndex = m_iDevIndex;    
	dlg.m_lServerID = m_lUserID;    
	dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnIpcPlateRecog() 
{
	// TODO: Add your control notification handler code here
	CDlgIPCPlateRecog dlg;
	dlg.m_lServerID = m_lUserID;
	dlg.m_iDevIndex = m_iDevIndex;

	dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnIpcCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgNVRIPCCfg dlg;
	dlg.m_lUserID = m_lUserID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnHeatmap() 
{
	// TODO: Add your control notification handler code here
	CDlgHeatMapCfg dlg;
	dlg.m_lServerID = m_lUserID;
	dlg.m_lChannel = m_lChanNo;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnPdcRule() 
{
	// TODO: Add your control notification handler code here
	CDlgPdcRuleCfgEx dlg;
	dlg.m_lServerID = m_lUserID;
	dlg.m_lChannel = m_lChanNo;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.m_lChanNum = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;
	dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnMaskRegion() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaMaskRegion dlg;
	dlg.m_lServerID = m_lUserID;
	dlg.m_iChannel = m_lChanNo;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnVcaDrawMode() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaDrawMode dlg;
	dlg.m_lChannel = m_lChanNo;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.m_lServerID = m_lUserID;
	dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnVcaFacesnapcfg() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaFaceSnapCfg dlg;
	dlg.m_lServerID = m_lUserID;
	dlg.m_lChannel = m_lChanNo;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnPreviewDisplaycfg() 
{
	// TODO: Add your control notification handler code here
	CDlgFishEye dlg;
	dlg.m_lServerID = m_lUserID;
	dlg.m_lChannel = m_lChanNo;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnPositionLimitAngle() 
{
	// TODO: Add your control notification handler code here
	CDlgLimitAngle dlg;
	dlg.m_lPlayHandle = -1;
	dlg.m_iPatrolIndex = 0;
	dlg.m_iLimitAngleType = POSITION_LIMIT_ANGLE;
	dlg.m_lServerID = m_lUserID;
	dlg.m_lChannel = m_lChanNo;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnTrackCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaTrackCfg dlg;

	dlg.m_lServerID = m_lUserID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.m_iChannel = m_lChanNo;

	dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnVcaCtrl() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaChanCtrlCfg dlg;
	dlg.m_lServerID = m_lUserID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.m_iVcaChannel = m_lChanNo;
	dlg.m_iChannelNum = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;
	dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnVcaVersion() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_VCA_VERSION struVcaVersion = {0};
	if (!NET_DVR_GetVCAVersion(m_lUserID, m_lChanNo, &struVcaVersion))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetVCAVersion");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetVCAVersion");
		char szLan[128] = {0};
		sprintf(szLan, "VCA Version: %d.%d.%d build%d%0.2d%0.2d", struVcaVersion.wMajorVersion, struVcaVersion.wMinorVersion,
			struVcaVersion.wRevisionNumber, struVcaVersion.wVersionYear,
			struVcaVersion.byVersionMonth, struVcaVersion.byVersionDay);
		MessageBox(szLan, "About");
	}
}

void CSubDlgDVRNVRCfg::OnBtnPositionTrackcfg() 
{
	// TODO: Add your control notification handler code here
	CDlgPositionTrackCfg dlg;
	dlg.m_lServerID = m_lUserID;
	dlg.m_lChannel = m_lChanNo;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnVcaruleCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaPositionRule dlg;

	dlg.m_lServerID = m_lUserID;
	dlg.m_iDevIndex = m_iDevIndex;

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

	dlg.m_iStartChannel = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].iChannelNO;
    dlg.m_iChannelnumber = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum + g_struDeviceInfo[m_iDevIndex].pStruIPParaCfgV40->dwStartDChan;

	dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnPicModelCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgPicModelCfg dlg;
	dlg.m_lUserID = m_lUserID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnMouseEvent() 
{
	// TODO: Add your control notification handler code here
	CDlgMouseEvent dlg;
	dlg.m_lUserID = m_lUserID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnGb28181Server() 
{
	// TODO: Add your control notification handler code here
	CDlgGB28181ServerCfg dlg;
	dlg.m_lUserID = m_lUserID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}


void CSubDlgDVRNVRCfg::OnBtnPos() 
{    
    CDlgPosManage dlg;
    dlg.m_iUserID = m_lUserID;
    dlg.m_lChanNo = m_lChanNo;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}
void CSubDlgDVRNVRCfg::OnButtonVedioImgDb() 
{
	// TODO: Add your control notification handler code here
	if (m_iDevIndex < 0)
    {
        return;
    }
	
    
    CDlgVedioImgDB dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnRecordHostCfg() 
{
	// TODO: Add your control notification handler code here
    int iDevIndex = g_pMainDlg->GetCurDeviceIndex();
    int iChanIndex = g_pMainDlg->GetCurChanIndex();
    if (iChanIndex < 0)
    {
        iChanIndex = 0;//default to config channel one
    }
    
    CDlgRecordHostV120 dlg;
    dlg.m_lLoginID = m_lUserID;
    if (iChanIndex >= MIRROR_CHAN_INDEX && g_struDeviceInfo[iDevIndex].byMirrorChanNum > 0)//支持导播通道
    {
        dlg.m_lChannel = g_struDeviceInfo[iDevIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].iChannelNO;
    }
    else
    {
        dlg.m_lChannel = g_struDeviceInfo[iDevIndex].pStruChanInfo[iChanIndex].iChannelNO;
    }
    dlg.m_iDeviceIndex = m_iDevIndex;
    dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBtnVca() 
{
	// TODO: Add your control notification handler code here
	CDlgAreaMonitorCfg dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}


void CSubDlgDVRNVRCfg::OnBnClickedBtnCloud()
{
    // TODO: Add your control notification handler code here
    CDlgCloudManage dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_lChanNo = m_lChanNo;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

#include "DlgAccessoryCardInfo.h"
void CSubDlgDVRNVRCfg::OnBnClickedBtnAccesssoryCardInfoGet()
{
        CDlgAccessoryCardInfo dlg;
        dlg.m_lUserID = m_lUserID;
        dlg.m_lChanNo = m_lChanNo;
        dlg.m_iDevIndex = m_iDevIndex;
        dlg.DoModal();

}

void CSubDlgDVRNVRCfg::OnBnClickedBtnPicBatchUpload()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgPicBatchUpload dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDevIndex;
    dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBnClickedBtnPtzNotification()
{
    CDlgPtzNotification dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_lChannel = m_lChanNo;
    dlg.m_iDeviceIndex = m_iDevIndex;
    dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBnClickedBtnChannelInfo()
{
    // TODO:  在此添加控件通知处理程序代码
    CDLGGetChannelInfo dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_lChannel = m_lChanNo;
    dlg.m_iDeviceIndex = m_iDevIndex;
    dlg.DoModal();
}


void CSubDlgDVRNVRCfg::OnBnClickedBtnResetPassword()
{
    // TODO:  在此添加控件通知处理程序代码
    CDLGResetLoginPassWord dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_lChannel = m_lChanNo;
    dlg.m_iDeviceIndex = m_iDevIndex;
    dlg.DoModal();
}


void CSubDlgDVRNVRCfg::OnBnClickedButtonSuperBrainFunctionTest()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgSuperBrainFunctionTest dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_lChannel = m_lChanNo;
    dlg.m_iDeviceIndex = m_iDevIndex;
    dlg.DoModal();
}

void CSubDlgDVRNVRCfg::OnBnClickedButtonCluster()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgCluster dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_lChannel = m_lChanNo;
    dlg.m_iDeviceIndex = m_iDevIndex;
    dlg.DoModal();
}
