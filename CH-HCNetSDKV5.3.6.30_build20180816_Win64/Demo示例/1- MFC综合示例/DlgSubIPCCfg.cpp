// DlgSubIPCCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgSubIPCCfg.h"
#include "DlgCcdParam.h"
#include "DlgIPCSpecial.h"
#include "DlgIPCSpeclalEx.h"
#include "DlgUpgradeIPC.h"
#include "DlgImExportIPCCfgFile.h"
#include "DlgRoiCfg.h"
#include "DlgPtzScope.h"
#include "DlgIPCSimpIntellCfg.h"
#include "DlgDevServer.h"
#include "DlgGBT28181ProtocolAccess.h"
#include "DlgRemoteAlarmDetectFace.h"
#include "DlgCameraSetupCfg.h"
#include "DlgFishEye.h"
#include "DlgStreamAttachInfoCfg.h"
#include "DlgPtzCfgCtrl.h"
#include "DlgIPCPlateRecog.h"
#include "DlgWirelessDial.h"
#include "DlgCloudStoragePhoneTest.h"
#include "DlgRemoteControlStatus.h"
#include "DlgThirdGenerationCfg.h"
#include "DlgMonitorLocation.h"
#include "DlgLiteStorage.h"
#include "DlgMasterSlaveTracking.h"
#include "DlgVehicleRecogCFG.h"
#include "DlgFireDetection.h"
#include "DlgGISInfo.h"
#include "DlgFrameCtrl.h"
#include "DlgPersonnelStatis.h"
#include "DlgConnectList.h"
#include "DlgTimeCorrect.h"
#include "DlgWirelessServer.h"
#include "DlgExternalDev.h"
#include "DlgThermalDoubleSpectrum.h"
#include "DlgThscreen.h"
#include "DlgBatteryPower.h"
#include "DlgPanoramaImage.h"
#include "DlgOnlineUserList.h"
#include "DlgThreeDimensionaPtz.h"
#include "DlgSmartStoragedDetection.h"
#include "DlgPrivateProtocolCfg.h"
#include "DlgFTPUpload.h"
#include "DlgOISCfg.h"
#include "DlgMacFilter.h"
#include "DlgSmartCalib.h"
#include "DlgEagleCfg.h"
#include "DlgTest.h"
#include "DlgVehicleInfo.h"
#include "DlgFirmWareversion.h"
#include "DLGFIREPTZEXCFG.h"
#include "DlgSoftwareService.h"
#include "DlgFaceData.h"
#include "DlgUploadHd.h"
#include "DlgVcaVersionList.h"
#include "DlgPosInfoctrl.h"
#include "DLGCfgSecuFile.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSubIPCCfg dialog


CDlgSubIPCCfg::CDlgSubIPCCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSubIPCCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSubIPCCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lDeviceIndex = -1;
	m_lUserID = -1;
	m_lChannel = -1;
	m_lChanCount = -1;
	m_lAnaChanCount = -1;
	m_lDStartChannel = -1;
	m_lAlarmOutNum = -1;
	m_lStartChan = -1;
	m_lAlarmInNum = -1;
}


void CDlgSubIPCCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSubIPCCfg)
	DDX_Control(pDX, IDC_COMBO_ALARM_IN, m_comboAlarmIn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSubIPCCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgSubIPCCfg)
	ON_BN_CLICKED(IDC_BTN_CCDCONFIG, OnBtnCcdconfig)
	ON_BN_CLICKED(IDC_BTN_DETECT_FACE, OnBtnDetectFace)
	ON_BN_CLICKED(IDC_BTN_IPC_SPECIAL, OnBtnIpcSpecial)
	ON_BN_CLICKED(IDC_BTN_IPC_SPECIALEX, OnBtnIpcSpecialex)
	ON_BN_CLICKED(IDC_BTN_UPGRADE_IPC, OnBtnUpgradeIpc)
	ON_BN_CLICKED(IDC_BTN_IM_EXPORT_IPC_CFG_FILE, OnBtnImExportIpcCfgFile)
	ON_BN_CLICKED(IDC_BTN_ROI, OnBtnRoi)
	ON_BN_CLICKED(IDC_BTN_PTZ_SCOPE, OnBtnPtzScope)
	ON_BN_CLICKED(IDC_BTN_IPCINTELL, OnBtnIpcintell)
	ON_BN_CLICKED(IDC_BTN_DEVSERVER, OnBtnDevserver)
	ON_BN_CLICKED(IDC_BTN_GBT28181_PROTOCOL, OnBtnGbt28181Protocol)
	ON_BN_CLICKED(IDC_BTN_CAMERA_SETUPCFG, OnBtnCameraSetupcfg)
	ON_BN_CLICKED(IDC_BTN_FISHEYE, OnBtnFisheye)
	ON_BN_CLICKED(IDC_BTN_STREAM_ATTACHINFO_CFG, OnBtnStreamAttachinfoCfg)
	ON_BN_CLICKED(IDC_BTN_PTZCFGCTRL, OnBtnPtzcfgctrl)
	ON_BN_CLICKED(IDC_BTN_IPC_PLATE_RECOG, OnBtnIpcPlateRecog)
	ON_BN_CLICKED(IDC_BTN_WIRELESS, OnBtnWireless)
	ON_BN_CLICKED(IDC_BTN_REMOTECONTROL_STATUS, OnBtnRemotecontrolStatus)
	ON_BN_CLICKED(IDC_BTN_3G_CONFIG, OnBtn3gConfig)
	ON_BN_CLICKED(IDC_BTN_CLOUDSTORAGE_TEST_CFG, OnBtnCloudstorageTestCfg)
	ON_BN_CLICKED(IDC_BTN_MONITOR_LOCATION, OnBtnMonitorLocation)
	ON_BN_CLICKED(IDC_BTN_LITESTORAGE11, OnBtnLitestorage11)
	ON_BN_CLICKED(IDC_BTN_MASTRESLAVE_TRACKING, OnBtnMastreslaveTracking)
	ON_BN_CLICKED(IDC_BTN_VEH_RECOG, OnBtnVehRecog)
	ON_BN_CLICKED(IDC_BTN_FIRE_DETECTION, OnBtnFireDetection)
	ON_BN_CLICKED(IDC_BTN_GIS_INFO, OnBtnGisInfo)
	ON_BN_CLICKED(IDC_BTN_STREAM_FRAME, OnBtnStreamFrame)
	ON_BN_CLICKED(IDC_BTN_PERSONNEL_STATISTICS, OnBtnPersonnelStatistics)
	ON_BN_CLICKED(IDC_BTN_WIRELESS_SERVER, OnBtnWirelessServer)
	ON_BN_CLICKED(IDC_BTN_TIME_CORRECT, OnBtnTimeCorrect)
	ON_BN_CLICKED(IDC_BTN_CONNECT_LIST, OnBtnConnectList)
    ON_BN_CLICKED(IDC_BUTTON_EXTERNAL_DEV, OnBtnExternalDev)
	ON_BN_CLICKED(IDC_BUTTON_THERMAL_DOUBLE_SPECTRUM, OnButtonThermalDoubleSpectrum)
	ON_BN_CLICKED(IDC_BTN_THSCREEN, OnBtnThscreen)
    ON_BN_CLICKED(IDC_BUTTON_BATTERY_POWER, OnBtnBatteryPower)
	ON_BN_CLICKED(IDC_BTN_PANORAMAIMAGE, OnBtnPanoramaimage)
    ON_BN_CLICKED(IDC_BUTTON_ONLINE_USER, OnBtnOnlineUserList)
	ON_BN_CLICKED(IDC_BUTTON_SMART_STORAGEDETECTION, OnButtonSmartStoragedetection)
	ON_BN_CLICKED(IDC_BTN_PRIVATE_PROTOCL, OnBtnPrivateProtocl)
	ON_BN_CLICKED(IDC_BTN_FTPUPLOAD, OnBtnFtpupload)
	ON_BN_CLICKED(IDC_BTN_THREE_DIM_SPEED_PTZ, OnBtnThreeDimSpeedPtz)
    ON_BN_CLICKED(IDC_BTN_ANR_ARMING_HOST, &CDlgSubIPCCfg::OnBnClickedBtnAnrArmingHost)
    ON_BN_CLICKED(IDC_BUTTON_OISPARA, &CDlgSubIPCCfg::OnBnClickedButtonOispara)
    ON_BN_CLICKED(IDC_BUTTON_MAC, &CDlgSubIPCCfg::OnBnClickedButtonMac)
    ON_BN_CLICKED(IDC_BUTTON_EAGLECFG, &CDlgSubIPCCfg::OnBnClickedButtonEaglecfg)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_SMART_CALIBRATION, &CDlgSubIPCCfg::OnBnClickedBtnSmartCalibration)
    ON_BN_CLICKED(IDC_BTN_TEST, &CDlgSubIPCCfg::OnBnClickedBtnTest)
    ON_BN_CLICKED(IDC_BTN_EAGLEEYE_CFG, &CDlgSubIPCCfg::OnBnClickedBtnEagleeyeCfg)
    ON_BN_CLICKED(IDC_BTN_CALIB, &CDlgSubIPCCfg::OnBnClickedBtnCalib)
    ON_BN_CLICKED(IDC_BTN_UPLPANORAMIC, &CDlgSubIPCCfg::OnBnClickedBtnUplpanoramic)
    ON_BN_CLICKED(IDC_BTN_GET_VECHICLE_INFO, &CDlgSubIPCCfg::OnBnClickedBtnGetVechicleInfo)
    ON_BN_CLICKED(IDC_BTN_FIRMWARE_VERSION, &CDlgSubIPCCfg::OnBnClickedBtnFirmwareVersion)
    ON_BN_CLICKED(IDC_FIREPTZEXCFG, &CDlgSubIPCCfg::OnBnClickedFireptzexcfg)
    ON_BN_CLICKED(IDC_BTN_SOFTWARE_SERVICE, &CDlgSubIPCCfg::OnBnClickedBtnSoftwareService)
    ON_BN_CLICKED(IDC_BTN_FACE_DATA, &CDlgSubIPCCfg::OnBnClickedBtnFaceData)
    ON_BN_CLICKED(IDC_BTN_UPLOAD_HD, &CDlgSubIPCCfg::OnBnClickedBtnUploadHd)
    ON_BN_CLICKED(IDC_BTN_POSINFO, &CDlgSubIPCCfg::OnBnClickedBtnPosinfo)
    ON_BN_CLICKED(IDC_BTN_GET_VCA_VERSION_LIST, &CDlgSubIPCCfg::OnBnClickedBtnGetVcaVersionList)
    ON_BN_CLICKED(IDC_BTN_SECU_CFG, &CDlgSubIPCCfg::OnBnClickedBtnSecuCfg)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSubIPCCfg message handlers
void CDlgSubIPCCfg::CurCfgUpdate()
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
    m_lDeviceIndex = iDeviceIndex;
    m_lUserID = g_struDeviceInfo[iDeviceIndex].lLoginID;
    m_lChannel= g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].iChannelNO;
	m_lChanCount = g_struDeviceInfo[iDeviceIndex].iDeviceChanNum;
	m_lAnaChanCount = g_struDeviceInfo[iDeviceIndex].iAnalogChanNum;
	if (m_lDStartChannel = g_struDeviceInfo[iDeviceIndex].pStruIPParaCfgV40 != NULL)
	{
		m_lDStartChannel = g_struDeviceInfo[iDeviceIndex].pStruIPParaCfgV40[0].dwStartDChan;
	}
	m_lAlarmOutNum = g_struDeviceInfo[iDeviceIndex].iAlarmOutNum;
	m_lStartChan = g_struDeviceInfo[iDeviceIndex].iStartChan;
	m_lAlarmInNum = g_struDeviceInfo[iDeviceIndex].iAlarmInNum;

	if (!CheckInitParam())
	{
		return;
	}
}

BOOL CDlgSubIPCCfg::CheckInitParam()
{	
	int iAlarmInSel = 0;
	CString sTemp;
	char szLan[128] = {0};
	DWORD dwReturned = 0;
	m_comboAlarmIn.ResetContent();
	NET_DVR_ALARMINCFG_V40 struAlarmInCfgV40 = {0};
	NET_DVR_DEVICECFG_V40 struDeviceCfg = {0};

	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_DEVICECFG_V40, 0, &struDeviceCfg, sizeof(struDeviceCfg), &dwReturned))
	{
		g_pMainDlg->AddLog(m_lDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_DEVICECFG_V40");
		g_StringLanType(szLan, "获取设备参数失败", "Get Device Configure failed");
		AfxMessageBox(szLan);
		//	return FALSE;
	}
	else
	{

		g_pMainDlg->AddLog(m_lDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_DEVICECFG_V40");
	}


	sTemp.Format(_T("All AlarmIn"));

	NET_DVR_IPALARMINCFG_V40 struIPAlarmInCfgV40 = {0};
	if (g_struDeviceInfo[m_lDeviceIndex].iIPChanNum > 0)// == DS90XX_HF_S
	{
		//Get the Group number of alarm in and alarm out.
		//         if (bInit)
		//         {
		//             GetAlarmInOutGroupNum();
		//         }

		if (g_pMainDlg->DoGetIPAlarmInCfg(m_lDeviceIndex, FALSE, 0))
		{
			memcpy(&struIPAlarmInCfgV40, g_struDeviceInfo[m_lDeviceIndex].pStruIPAlarmInCfgV40, sizeof(NET_DVR_IPALARMINCFG_V40));
		}

	}



// 	for (int i=0; i<m_lAlarmInNum; i++)
// 	{	
// 		int iIPAlarmIndex = i;
//             
//         if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_ALARMINCFG_V40, iIPAlarmIndex, &struAlarmInCfgV40, sizeof(NET_DVR_ALARMINCFG_V40), &dwReturned))
//         {
//             g_pMainDlg->AddLog(m_lDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMINCFG_V40 chanindex[%d]", iIPAlarmIndex);	
//             g_StringLanType(szLan, "获取报警输入参数失败", "Alarm input parameters to get the failure");
// //            AfxMessageBox(szLan);
// 			return FALSE;
//         }
//         else
//         {
//             g_pMainDlg->AddLog(m_lDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARMINCFG_V40 chanindex[%d]", iIPAlarmIndex);	
//             
//         }
//      			
// 		sTemp.Format(ALARM_IN_NAME, (1+i));
// 
//         m_comboAlarmIn.AddString(sTemp);
//         m_comboAlarmIn.SetItemData(iAlarmInSel, iIPAlarmIndex);
//         iAlarmInSel++;
//     }

	int iIPAlarmIndex = 0;
	DWORD iAlarmChan = 0;
	for (int i=0; i< (g_struDeviceInfo[m_lDeviceIndex].iAlarmInNum + struIPAlarmInCfgV40.dwCurIPAlarmInNum); i++)//m_dwAlarmInNum
	{	        
		if (i< g_struDeviceInfo[m_lDeviceIndex].iAlarmInNum)
		{

			if (i >= g_struDeviceInfo[m_lDeviceIndex].iAlarmInNum)
			{
				iIPAlarmIndex = i ;
				iAlarmChan = i - g_struDeviceInfo[m_lDeviceIndex].iAlarmInNum + struDeviceCfg.byStartIPAlarmInNo;
			}
			else
			{
				iIPAlarmIndex = i;
				iAlarmChan= i; 
			}

			if (i<(int)g_struDeviceInfo[m_lDeviceIndex].iAlarmInNum)
			{			
				sTemp.Format(ALARM_IN_NAME, (1+i));
			}
			else
			{
				sTemp.Format(IP_ALARM_IN_NAME, (1 + iIPAlarmIndex-g_struDeviceInfo[m_lDeviceIndex].iAlarmInNum));
			}  

			m_comboAlarmIn.AddString(sTemp);
			m_comboAlarmIn.SetItemData(iAlarmInSel, iAlarmChan);

			iAlarmInSel++;
		}
	}
	m_comboAlarmIn.SetCurSel(0);

	return TRUE;
}

void CDlgSubIPCCfg::OnBtnCcdconfig() 
{
	// TODO: Add your control notification handler code here
	CDlgCcdParam dlg;
	dlg.m_iDeviceIndex = m_lDeviceIndex;
	dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
	dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnDetectFace() 
{
	// TODO: Add your control notification handler code here
	CDlgRemoteAlarmDetectFace dlg;
	//	dlg.m_lpAlarmIn = &m_struAlarmInCfg[m_iAlarmInIndex];
	dlg.m_iChanCount = m_lChanCount;
	dlg.m_iAnaChanCount = m_lAnaChanCount;
	dlg.m_iDStartChannel = m_lDStartChannel;
	dlg.m_dwDevIndex = m_lDeviceIndex;
	dlg.m_lStartChannel = m_lStartChan;
	dlg.m_dwAlarmOutNum = m_lAlarmOutNum;
	dlg.m_dwAlarmInNum = m_lAlarmInNum;
    dlg.m_lAlarmInIndex = m_comboAlarmIn.GetItemData(m_comboAlarmIn.GetCurSel());
    dlg.m_lServerID = m_lUserID;
	
	dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnIpcSpecial() 
{
	// TODO: Add your control notification handler code here

	CDlgIPCSpecial dlg;
	dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_lDeviceIndex;
	dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
	dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnIpcSpecialex() 
{
	// TODO: Add your control notification handler code here
	
	CDlgIPCSpeclalEx dlg;
	dlg.m_lLoginID = m_lUserID;	
	dlg.m_iDeviceIndex = m_lDeviceIndex;			
	dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
	dlg.m_iChanCount = m_lChanCount;
	dlg.m_iAnaChanCount = m_lAnaChanCount;
	dlg.m_iDStartChannel = m_lDStartChannel;
	dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnUpgradeIpc() 
{
	// TODO: Add your control notification handler code here
	CDlgUpgradeIPC dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_dwDevIndex = m_lDeviceIndex;
    dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnImExportIpcCfgFile() 
{
	// TODO: Add your control notification handler code here
	DlgImexporIPCCfgFile dlg;
	dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnRoi() 
{
	// TODO: Add your control notification handler code here
	CDlgRoiCfg dlg;
	dlg.m_lLoginID = m_lUserID;	
	dlg.m_iDeviceIndex = m_lDeviceIndex;			
	dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
	dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnPtzScope() 
{
	// TODO: Add your control notification handler code here
	CDlgPtzScope dlg;
    dlg.m_iDevIndex = m_lDeviceIndex;
    dlg.m_lServerID = m_lUserID;
    dlg.m_lChannel= g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;;
    dlg.DoModal();	
}

void CDlgSubIPCCfg::OnBtnIpcintell() 
{
	// TODO: Add your control notification handler code here
	CDlgIPCSimpIntellCfg dlg;
	dlg.m_lLoginID = m_lUserID;	
	dlg.m_iDeviceIndex = m_lDeviceIndex;			
    dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
	dlg.m_iChanCount = m_lChanCount;
	dlg.m_iAnaChanCount = m_lAnaChanCount;
	dlg.m_iDStartChannel = m_lDStartChannel;
	dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnDevserver() 
{
	// TODO: Add your control notification handler code here
	CDlgDevServer dlg;
	dlg.m_lServerID = m_lUserID;
	dlg.m_dwAlarmOutNum = m_lAlarmOutNum;
	dlg.m_dwDevIndex = m_lDeviceIndex;
	dlg.m_nChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;;
	dlg.m_lStartChan = m_lStartChan;
	dlg.m_dwAlarmInNum = m_lAlarmInNum;
	dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnGbt28181Protocol() 
{
	// TODO: Add your control notification handler code here
	CDlgGBT28181ProtocolAccess dlg;
	dlg.m_lServerID = m_lUserID;
	dlg.m_dwAlarmOutNum = m_lAlarmOutNum;
	dlg.m_dwDevIndex = m_lDeviceIndex;
	dlg.m_nChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;;
	dlg.m_lStartChan = m_lStartChan;
	dlg.m_dwAlarmInNum = m_lAlarmInNum;
	dlg.DoModal();
}

BOOL CDlgSubIPCCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgSubIPCCfg::OnBtnCameraSetupcfg() 
{
	// TODO: Add your control notification handler code here
	CDlgCameraSetupCfg dlg ;
	dlg.m_lLoginID = m_lUserID;
	dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
	dlg.m_iDeviceIndex = m_lDeviceIndex ;
	dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnFisheye() 
{
	CDlgFishEye dlg;
	dlg.m_lServerID = m_lUserID;
	dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
	dlg.m_iDevIndex = m_lDeviceIndex;
	dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnStreamAttachinfoCfg() 
{
	CDlgStreamAttachInfoCfg dlg;
	dlg.m_lServerID = m_lUserID;
	dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
	dlg.m_iDeviceIndex = m_lDeviceIndex;
	dlg.DoModal();
	
}

void CDlgSubIPCCfg::OnBtnPtzcfgctrl() 
{
	// TODO: Add your control notification handler code here
	CDlgPtzCfgCtrl dlg;
	dlg.m_lLoginID = m_lUserID;
	dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
	dlg.m_iDeviceIndex = m_lDeviceIndex;
	dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnIpcPlateRecog() 
{
	// TODO: Add your control notification handler code here
	CDlgIPCPlateRecog dlg;
	dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_lDeviceIndex;
    dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
    dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnWireless() 
{
	// TODO: Add your control notification handler code here
    CDlgWirelessDial dlg;
    dlg.m_lLoginID = m_lUserID;
    dlg.m_iDeviceIndex = m_lDeviceIndex;
    dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnRemotecontrolStatus() 
{
    // TODO: Add your control notification handler code here
    CDlgRemoteControlStatus dlg;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_lDeviceIndex;
    dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
    dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtn3gConfig() 
{
    // TODO: Add your control notification handler code here
    CDlgThirdGenerationCfg dlg;
    dlg.m_lServerID = m_lUserID;
    dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnCloudstorageTestCfg() 
{
	// TODO: Add your control notification handler code here
    CDlgCloudStoragePhoneTest dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_dwDevIndex = m_lDeviceIndex;
    dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnMonitorLocation() 
{
	// TODO: Add your control notification handler code here
    CDlgMonitorLocation dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_dwDevIndex = m_lDeviceIndex;
    dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
    dlg.DoModal();
}

// void CDlgSubIPCCfg::OnBtnLitestorage() 
// {
// 	// TODO: Add your control notification handler code here
// 	CDlgLiteStorage dlg;
//     dlg.m_lLoginID = m_lUserID;
//     dlg.DoModal();
// }


void CDlgSubIPCCfg::OnBtnLitestorage11() 
{
	// TODO: Add your control notification handler code here
	CDlgLiteStorage dlg;
    dlg.m_lLoginID = m_lUserID;
    dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnMastreslaveTracking() 
{
	// TODO: Add your control notification handler code here
	CDlgMasterSlaveTracking dlg;
    dlg.m_lLoginID = m_lUserID;
    dlg.m_iDeviceIndex = m_lDeviceIndex;
    dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnVehRecog() 
{
	// TODO: Add your control notification handler code here
	CDlgVehicleRecogCFG dlg;
	dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
	dlg.m_lUserID = m_lUserID;
	dlg.m_lDevIndex = m_lDeviceIndex;
	dlg.DoModal();
}


void CDlgSubIPCCfg::OnBtnFireDetection() 
{
	// TODO: Add your control notification handler code here
	CDlgFireDetection dlg;
    dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_lDeviceIndex;
	dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnGisInfo() 
{
	// TODO: Add your control notification handler code here
    CDlgGISInfo dlg;
    dlg.m_lChannel = m_lChannel;
    dlg.m_lUser = m_lUserID;
    dlg.m_iDeviceIndex = m_lDeviceIndex;
	dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnStreamFrame() 
{
	// TODO: Add your control notification handler code here
    CDlgFrameCtrl dlg;
    dlg.m_iChannel = m_lChannel;
    dlg.m_lUser = m_lUserID;
    dlg.m_iDeviceIndex = m_lDeviceIndex;
	dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnPersonnelStatistics() 
{
	CDlgPersonnelStatis dlg;
    dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_lDeviceIndex;
	dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnWirelessServer()
{
	DlgWirelessServer dlg;
    dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_lDeviceIndex;
	dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnTimeCorrect()
{
	// TODO: Add your control notification handler code here
	DlgTimeCorrect dlg;
    dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_lDeviceIndex;
	dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnConnectList()
{
	// TODO: Add your control notification handler code here
	DlgConnectList dlg;
    dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_lDeviceIndex;
	dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnExternalDev()
{
    // TODO: Add your control notification handler code here
    DlgExternalDev dlg;
    dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_lDeviceIndex;
    dlg.DoModal();
}

void CDlgSubIPCCfg::OnButtonThermalDoubleSpectrum() 
{
	// TODO: Add your control notification handler code here
	CDlgThermalDoubleSpectrum dlg;
    dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_lDeviceIndex;
    dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnThscreen() 
{
	// TODO: Add your control notification handler code here
	CDlgThscreen dlg;
	dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
    dlg.m_lLoginID = m_lUserID;
    dlg.m_iDeviceIndex = m_lDeviceIndex;
    dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnBatteryPower()
{
    // TODO: Add your control notification handler code here
    DlgBatteryPower dlg;
    dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_lDeviceIndex;
    dlg.DoModal();
}

void CDlgSubIPCCfg::OnBtnPanoramaimage() 
{
	// TODO: Add your control notification handler code here
    CDlgPanoramaImage dlg;
    dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_lDeviceIndex;
    dlg.DoModal();	
}

void CDlgSubIPCCfg::OnBtnOnlineUserList()
{
    // TODO: Add your control notification handler code here
    DlgOnlineUserList dlg;
    dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_lDeviceIndex;
    dlg.DoModal();
}

void CDlgSubIPCCfg::OnButtonSmartStoragedetection() 
{
	// TODO: Add your control notification handler code here
	CDlgSmartStoragedDetection dlg;
    dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
    dlg.m_lLoginID = m_lUserID;
    dlg.m_iDeviceIndex = m_lDeviceIndex;
    dlg.DoModal();	
}

void CDlgSubIPCCfg::OnBtnPrivateProtocl() 
{
	// TODO: Add your control notification handler code here
    CDlgPrivateProtocolCfg dlg;
    dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_lDeviceIndex;
    dlg.DoModal();
}



void CDlgSubIPCCfg::OnBtnFtpupload() 
{
	// TODO: Add your control notification handler code here
    CDlgFTPUpload dlg;
    //dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_lDeviceIndex;
    dlg.DoModal();
}





void CDlgSubIPCCfg::OnBtnThreeDimSpeedPtz() 
{
	// TODO: Add your control notification handler code here
    CDlgThreeDimensionaPtz dlg;
    dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_lDeviceIndex;
    dlg.DoModal();	
}


#include "DlgArmingHost.h"
void CDlgSubIPCCfg::OnBnClickedBtnAnrArmingHost()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgArmingHost dlg;
    dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_lDeviceIndex;
    dlg.DoModal();
}

void CDlgSubIPCCfg::OnBnClickedButtonOispara()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgOISCfg dlg;
    dlg.m_lServerID = g_struDeviceInfo[m_lDeviceIndex].lLoginID;
    dlg.m_iDeviceIndex = m_lDeviceIndex;
    dlg.m_lChannel = m_lChannel;
    dlg.DoModal();
}

void CDlgSubIPCCfg::OnBnClickedButtonMac()
{

    CDlgMacFilter dlg;
    dlg.m_lServerID = g_struDeviceInfo[m_lDeviceIndex].lLoginID;
    dlg.m_iDeviceIndex = m_lDeviceIndex;
    dlg.m_lChannel = m_lChannel;
    dlg.DoModal();
}

void CDlgSubIPCCfg::OnBnClickedButtonEaglecfg()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgEagleCfg dlg;
    dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_lDeviceIndex;
    dlg.DoModal();
}

void CDlgSubIPCCfg::OnBnClickedBtnSmartCalibration()
{
    CDlgSmartCalib dlg;
    dlg.m_lChannel = m_lChannel;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_lDeviceIndex;
    dlg.DoModal();
}


void CDlgSubIPCCfg::OnBnClickedBtnTest()
{
    CDlgTest dlg;
    dlg.m_lServerID = g_struDeviceInfo[m_lDeviceIndex].lLoginID;
    dlg.m_iDeviceIndex = m_lDeviceIndex;
    dlg.m_lChannel = m_lChannel;
    dlg.DoModal();
}

#include "DlgEagleEyeCfg.h"
void CDlgSubIPCCfg::OnBnClickedBtnEagleeyeCfg()
{
    CDlgEagleEyeCfg dlg;
    dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_lDeviceIndex;
    dlg.DoModal();
}

#include "DlgCapturePictureV50.h"
void CDlgSubIPCCfg::OnBnClickedBtnCalib()
{
    int iDeviceIndex = m_lDeviceIndex;
    if (iDeviceIndex == -1)
    {
        return;
    }
    int iChanIndex = g_pMainDlg->GetCurChanIndex();
    if (iChanIndex == -1)
    {
        char szLan[128] = { 0 };
        g_StringLanType(szLan, "通道号错误！", "Channel Error");
        AfxMessageBox(szLan);
        return;
    }
    if (iChanIndex >= ZERO_CHAN_INDEX)
    {
        AfxMessageBox("Zero not support  NET_DVR_CaptureJPEGPicture");
    }
    CDlgCapturePictureV50 dlg;
    if (g_struDeviceInfo[iDeviceIndex].byMirrorChanNum > 0 && iChanIndex >= g_struDeviceInfo[iDeviceIndex].wStartMirrorChanNo)
    {
        dlg.m_pChanInfo = &g_struDeviceInfo[iDeviceIndex].struMirrorChan[iChanIndex - g_struDeviceInfo[iDeviceIndex].wStartMirrorChanNo];
    }
    else
    {
        dlg.m_pChanInfo = &g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex];
    }
    dlg.DoModal();
}

#include "UPLOAD_PANORAMIC_STITCH.h"
void CDlgSubIPCCfg::OnBnClickedBtnUplpanoramic()
{
    CUPLOAD_PANORAMIC_STITCH dlg;
    dlg.m_lServerID = g_struDeviceInfo[m_lDeviceIndex].lLoginID;
    dlg.m_iDeviceIndex = m_lDeviceIndex;
    dlg.m_lChannel = m_lChannel;
    dlg.DoModal();
}


void CDlgSubIPCCfg::OnBnClickedBtnGetVechicleInfo()
{
    CDlgVehicleInfo dlg;
    dlg.m_lChannel = m_lChannel;
    dlg.DoModal();
}



void CDlgSubIPCCfg::OnBnClickedBtnFirmwareVersion()
{
    CDlgFirmWareversion dlg;
    dlg.m_lChannel = m_lChannel;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_lDeviceIndex;
    dlg.DoModal();
}




void CDlgSubIPCCfg::OnBnClickedFireptzexcfg()
{
    CDLGFIREPTZEXCFG dlg;
    dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_lDeviceIndex;
    dlg.DoModal();
}


void CDlgSubIPCCfg::OnBnClickedBtnSoftwareService()
{
    CDlgSoftwareService dlg;
    dlg.m_lChannel = g_struDeviceInfo[m_lDeviceIndex].pStruChanInfo[g_pMainDlg->GetCurChanIndex()].iChannelNO;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_lDeviceIndex;
    dlg.DoModal();
}

void CDlgSubIPCCfg::OnBnClickedBtnFaceData()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgFaceData dlg;
    dlg.m_lChannel = m_lChannel;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_lDeviceIndex;
    dlg.DoModal();
}


void CDlgSubIPCCfg::OnBnClickedBtnUploadHd()
{
    CDlgUploadHd dlg;
    dlg.m_lServerID = g_struDeviceInfo[m_lDeviceIndex].lLoginID;
    dlg.m_iDevIndex = m_lDeviceIndex;
    dlg.m_lChannel = m_lChannel;
    dlg.DoModal();
}


void CDlgSubIPCCfg::OnBnClickedBtnPosinfo()
{
    CDlgPosInfoctrl dlg;
    dlg.m_lChannel = m_lChannel;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_lDeviceIndex;
    dlg.DoModal();
}


void CDlgSubIPCCfg::OnBnClickedBtnGetVcaVersionList()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgVcaVersionList dlg;
    dlg.m_lChannel = m_lChannel;
    dlg.m_lUserID = m_lUserID;
    dlg.m_lDeviceIndex = m_lDeviceIndex;
    dlg.DoModal();
}


void CDlgSubIPCCfg::OnBnClickedBtnSecuCfg()
{
    CDLGCfgSecuFile dlg;
    dlg.m_lChannel = m_lChannel;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_lDeviceIndex;
    dlg.DoModal();
}
