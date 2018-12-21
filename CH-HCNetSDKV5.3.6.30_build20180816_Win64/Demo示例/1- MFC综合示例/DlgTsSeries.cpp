// DlgTsSeries.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgTsSeries.h"
#include "DlgEctChanStatus.h"
#include "DlgEctWorkState.h"
#include "DlgITCIOinCfg.h"
#include "DlgTmeCfg.h"


// #ifdef _DEBUG
// #define new DEBUG_NEW
// #undef THIS_FILE
// static char THIS_FILE[] = __FILE__;
// #endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTsSeries dialog
#define    INLAY_LAMP_CTRL_MODE        1//
#define    EXTERNAL_LAMP_CTRL_MODE     2//
#define    PARKING_LAMP_CTRL_MODE      3//
#define    MIXLAMP_CTRL_MODE           4//
#define    SINGLELAMP_CTRL_MODE        5//   

#define    NORMAL_PARK_IO_STATE        0//
#define    NORMAL_NO_PARK_IO_STATE     1//
#define    SPECIAL_PARK_IO_STATE       2//
#define    SPECIAL_NO_PARK_IO_STATE    3//

CDlgTsSeries::CDlgTsSeries(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTsSeries::IDD, pParent)
    , m_byUnLock(FALSE)
{
	//{{AFX_DATA_INIT(CDlgTsSeries)
	m_csSendData = _T("");
	m_iCamLaneID = 0;
	m_csGateInfo = _T("");
	m_csGateSiteID = _T("");
	m_iLaneID = 0;
	m_iRelativeIONum = 0;
	m_iRemoteCamlaneID = 0;
	m_iRemoteLaneID = 0;
	m_csLaneName = _T("");
	m_byCtrlChannelIndex = 0;
	m_byGateIndex = 0;
	m_byLedIndex = 0;
	m_byRelatIndex = 0;
	m_csLicense = _T("");
	m_csParkingNo = _T("");
	m_strCardNo = _T("");
	m_byChargeRuleID = 0;
	m_startDate = COleDateTime::GetCurrentTime();
	m_startTime = COleDateTime::GetCurrentTime();
	m_stopDate = COleDateTime::GetCurrentTime();
	m_stopTime = COleDateTime::GetCurrentTime();
	m_csRelateCardNo = _T("");
	m_csVehicleLicense = _T("");
	m_startDate2 = COleDateTime::GetCurrentTime();
	m_startTime2 = COleDateTime::GetCurrentTime();
	m_stopDate2 = COleDateTime::GetCurrentTime();
	m_stopTime2 = COleDateTime::GetCurrentTime();
	m_dwUpdataSerialNum = 0;
	m_dwParkingNum = 0;
	m_csAppSerialNum = _T("");
	//}}AFX_DATA_INIT
	m_lTranHandle = -1;
	m_lCardSendHandle = -1;
    m_lVehicleSendHandle = -1;
	memset(m_strITSGateLaneCfg, 0, sizeof(m_strITSGateLaneCfg));
}

CDlgTsSeries::~CDlgTsSeries()
{
    char szLan[128] = {0};
    if (m_lVehicleSendHandle < 0)
    {
        return;
    }
    
    if ( !NET_DVR_StopRemoteConfig(m_lVehicleSendHandle))
    {
        g_StringLanType(szLan, "车辆数据下发停止失败", "The Vehicle to send the data stop failed");
        sprintf(szLan, "%s 错误码:%d", szLan, NET_DVR_GetLastError());
        AfxMessageBox(szLan);
        return;
    }
    
    m_lVehicleSendHandle = -1;

	if (m_lCardSendHandle < 0)
	{

		return;
	}
	
	if ( !NET_DVR_StopRemoteConfig(m_lCardSendHandle))
    {
        g_StringLanType(szLan, "临时卡数据下发停止失败", "The temporary card to send the data stop failed");
        sprintf(szLan, "%s 错误码:%d", szLan, NET_DVR_GetLastError());
        AfxMessageBox(szLan);
        return;
    }
	m_lCardSendHandle = -1;

}


void CDlgTsSeries::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTsSeries)
	DDX_Control(pDX, IDC_COMBO_VEHICLE_TYPE, m_comVehicleType);
	DDX_Control(pDX, IDC_COMBO_PLATE_COLOR, m_comPlateColor);
	DDX_Control(pDX, IDC_COMBO_CARDSTATUS, m_comCardStatus);
	DDX_Control(pDX, IDC_COMBO_ENTRANCE_NO, m_comEntranceNo);
	DDX_Control(pDX, IDC_COMBO_GATE_CTRL, m_comGateCtrl);
	DDX_Control(pDX, IDC_COMBO_LANE_NO, m_comLaneNo);
	DDX_Control(pDX, IDC_COMBO_CARDTYPE, m_comParkingCardType);
	DDX_Control(pDX, IDC_CHECK_DELETE_CARD, m_checkDelCard);
	DDX_Control(pDX, IDC_CHECK_DELETE_ALL_CARD, m_checkDelAllCard);
	DDX_Control(pDX, IDC_COMBO_CARD_TYPE, m_comCardType);
	DDX_Control(pDX, IDC_COMBO_VEHICLELOGORECOG, m_comVehicleLogoRecog);
	DDX_Control(pDX, IDC_COMBO_CARCOLORDEEP, m_comCarColorDeep);
	DDX_Control(pDX, IDC_COMBO_CARCOLOR, m_comCarColor);
	DDX_Control(pDX, IDC_COMBO_RELATE_LANENO2, m_comRelateLaneNo2);
	DDX_Control(pDX, IDC_COMBO_PARKINGSTATE2, m_comParkingStatus2);
	DDX_Control(pDX, IDC_COMBO_LAMPCOLORSTATE, m_comLampColorStatus);
	DDX_Control(pDX, IDC_COMBO_FLICKER2, m_comFlickerStatus);
	DDX_Control(pDX, IDC_COMBO_RELATE_LANENO, m_comRelateLaneNo);
	DDX_Control(pDX, IDC_COMBO_PARKINGSTATE, m_comParkingStatus);
	DDX_Control(pDX, IDC_COMBO_PARKLAMP, m_comParkingLamp);
	DDX_Control(pDX, IDC_COMBO_RE_PARKINGLAMP, m_comRelateParkingLamp);
	DDX_Control(pDX, IDC_COMBO_LED_DEV, m_comLEDDev);
	DDX_Control(pDX, IDC_COMBO_CHARGE_MODE, m_comChargeMode);
	DDX_Control(pDX, IDC_COMBO_CHARGE, m_comCharge);
	DDX_Control(pDX, IDC_COMBO_PARKINDEX, m_comParkIndex);
	DDX_Control(pDX, IDC_CHECK_IO3, m_checkIO3);
	DDX_Control(pDX, IDC_CHECK_IO2, m_checkIO2);
	DDX_Control(pDX, IDC_CHECK_IO1, m_checkIO1);
	DDX_Control(pDX, IDC_COMBO_LAMP_FLICKER, m_comLampFlicker);
	DDX_Control(pDX, IDC_COMBO_LAMP_ENABLE, m_comLampEnable);
	DDX_Control(pDX, IDC_COMBO_PARK_SPACE_ATTRIBUTE, m_comParkSpaceAttribute);
	DDX_Control(pDX, IDC_COMBO_PARK_SPACE_INFO, m_comParkSpaceInfo);
	DDX_Control(pDX, IDC_COMBO_PARKNUM, m_comParkNum);
	DDX_Control(pDX, IDC_COMBO_PARKSTATUS, m_comParkStatus);
	DDX_Control(pDX, IDC_COMBO_FLICKER, m_comFlicker);
	DDX_Control(pDX, IDC_COMBO_ENABLE, m_comEnable);
	DDX_Control(pDX, IDC_COMBO_PARKINFO, m_comParkInfo);
	DDX_Control(pDX, IDC_COMBO_IOSTATE, m_comIOSTate);
	DDX_Control(pDX, IDC_COMBO_LAMPCOLOR, m_comLampColor);
    DDX_Control(pDX, IDC_COMBO_MIXLAMPMODE, m_comMixLampMode);
	DDX_Control(pDX, IDC_COMBO_LAMPCTRLMODE, m_comLampCtrlMode);
	DDX_Control(pDX, IDC_COMBO_CARD_MODE, m_comCardMode);
	DDX_Control(pDX, IDC_COMBO_LPR_MODE, m_comLprMode);
	DDX_Control(pDX, IDC_COMBO_GATELANE_MODE, m_comGateLaneMode);
	DDX_Control(pDX, IDC_COMBO_CODE, m_cmbCode);
	DDX_Control(pDX, IDC_COMBO_VALID, m_cmbValid);
	DDX_Control(pDX, IDC_COMBO_IPCTYPE, m_cmbIpcType);
	DDX_Control(pDX, IDC_COMBO_GATELANE, m_cmbGateLane);
	DDX_Control(pDX, IDC_COMBO_DIRECTION, m_cmbDirection);
	DDX_Text(pDX, IDC_EDIT_SEND_DATA, m_csSendData);
	DDX_Text(pDX, IDC_EDIT_CAMLANE_ID, m_iCamLaneID);
	DDX_Text(pDX, IDC_EDIT_GATEINFO, m_csGateInfo);
	DDX_Text(pDX, IDC_EDIT_GATESITE_ID, m_csGateSiteID);
	DDX_Text(pDX, IDC_EDIT_LANE_ID, m_iLaneID);
	DDX_Text(pDX, IDC_EDIT_RELATIVE_IONUM, m_iRelativeIONum);
	DDX_Text(pDX, IDC_EDIT_REMOTE_CAMLANE_ID, m_iRemoteCamlaneID);
	DDX_Text(pDX, IDC_EDIT_REMOTE_LANE_ID, m_iRemoteLaneID);
	DDX_Text(pDX, IDC_EDIT_LANENAME, m_csLaneName);
	DDX_Text(pDX, IDC_EDIT_CHANNEL, m_byCtrlChannelIndex);
	DDX_Text(pDX, IDC_EDIT_GATE_INDEX, m_byGateIndex);
	DDX_Text(pDX, IDC_EDIT_LED_INDEX, m_byLedIndex);
	DDX_Text(pDX, IDC_EDIT_RELAT_INDEX, m_byRelatIndex);
	DDX_Text(pDX, IDC_EDIT_LICENSE, m_csLicense);
	DDX_Text(pDX, IDC_EDIT_PARKINGNO, m_csParkingNo);
	DDX_Text(pDX, IDC_EDIT_CARD_NO1, m_strCardNo);
	DDX_Text(pDX, IDC_EDIT_CHARGE_RULE_ID, m_byChargeRuleID);
	DDX_DateTimeCtrl(pDX, IDC_START_DATE, m_startDate);
	DDX_DateTimeCtrl(pDX, IDC_START_TIME, m_startTime);
	DDX_DateTimeCtrl(pDX, IDC_STOP_DATE, m_stopDate);
	DDX_DateTimeCtrl(pDX, IDC_STOP_TIME, m_stopTime);
	DDX_Text(pDX, IDC_EDIT_RELATE_CARDNO, m_csRelateCardNo);
	DDX_Text(pDX, IDC_EDIT_VEHICLE_LICENSE, m_csVehicleLicense);
	DDX_DateTimeCtrl(pDX, IDC_START_DATE2, m_startDate2);
	DDX_DateTimeCtrl(pDX, IDC_START_TIME2, m_startTime2);
	DDX_DateTimeCtrl(pDX, IDC_STOP_DATE2, m_stopDate2);
	DDX_DateTimeCtrl(pDX, IDC_STOP_TIME2, m_stopTime2);
	DDX_Text(pDX, IDC_EDIT_UPDATA_SERIALNUM, m_dwUpdataSerialNum);
	DDX_Text(pDX, IDC_EDIT_PARKING_NUM, m_dwParkingNum);
	DDX_Text(pDX, IDC_EDIT_APP_SERIAL_NUM, m_csAppSerialNum);
	//}}AFX_DATA_MAP
    DDX_Check(pDX, IDC_CHECK_UNLOCK, m_byUnLock);
}


BEGIN_MESSAGE_MAP(CDlgTsSeries, CDialog)
	//{{AFX_MSG_MAP(CDlgTsSeries)
	ON_BN_CLICKED(IDC_BTN_SET_TRANS, OnBtnSetTrans)
	ON_BN_CLICKED(IDC_BTN_OUT_TRANS, OnBtnOutTrans)
	ON_BN_CLICKED(IDC_BTN_SEND_DATA, OnBtnSendDataTrans)
	ON_BN_CLICKED(IDC_BTN_GET_CHAN_LANE, OnBtnGetChanLane)
	ON_BN_CLICKED(IDC_BTN_SET_CHAN_LANE, OnBtnSetChanLane)
	ON_BN_CLICKED(IDC_BTN_SAVE_LANE, OnBtnSaveLane)
	ON_CBN_SELCHANGE(IDC_COMBO_GATELANE, OnSelchangeComboGatelane)
	ON_BN_CLICKED(IDC_BTN_REMOTE_COMMAND, OnBtnRemoteCommand)
	ON_BN_CLICKED(IDC_BTN_GET_ECT_WORK_STATUS2, OnBtnGetEctWorkStatus2)
	ON_BN_CLICKED(IDC_BTN_GET_ECT_DEV_STATUE, OnBtnGetEctDevStatue)
	ON_BN_CLICKED(IDC_BTN_PRE_LAMP_CTRL_INFO, OnBtnPreLampCtrlInfo)
	ON_BN_CLICKED(IDC_BTN_SET_LAMP_CTRL_INFO, OnBtnSetLampCtrlInfo)
	ON_BN_CLICKED(IDC_BTN_GET_LAMP_CTRL_INFO, OnBtnGetLampCtrlInfo)
	ON_CBN_SELCHANGE(IDC_COMBO_LAMPCTRLMODE, OnSelchangeComboLampctrlmode)
	ON_CBN_SELCHANGE(IDC_COMBO_PARKNUM, OnSelchangeComboParknum)
	ON_CBN_SELCHANGE(IDC_COMBO_PARKINFO, OnSelchangeComboParkinfo)
	ON_CBN_SELCHANGE(IDC_COMBO_PARKSTATUS, OnSelchangeComboParkstatus)
	ON_BN_CLICKED(IDC_BTN_SET_PARKSPACE_ATTRIBUTE, OnBtnSetParkspaceAttribute)
	ON_BN_CLICKED(IDC_BTN_GET_PARKSPACE_ATTRIBUTE, OnBtnGetParkspaceAttribute)
	ON_CBN_SELCHANGE(IDC_COMBO_PARK_SPACE_INFO, OnSelchangeComboParkSpaceInfo)
	ON_BN_CLICKED(IDC_BTN_SET_LAMP_EXTERNAL, OnBtnSetLampExternal)
	ON_BN_CLICKED(IDC_BTN_GET_LAMP_EXTERNAL, OnBtnGetLampExternal)
	ON_BN_CLICKED(IDC_BTN_SET_COMPEL_CAPTURE, OnBtnSetCompelCapture)
	ON_BN_CLICKED(IDC_BTN_SET_CUSTOMINFO, OnBtnSetCustominfo)
	ON_BN_CLICKED(IDC_BTN_GET_CUSTOMINFO, OnBtnGetCustominfo)
	ON_BN_CLICKED(IDC_BTN_PRE_PARKSPACE_ATTRIBUTE, OnBtnPreParkspaceAttribute)
	ON_CBN_SELCHANGE(IDC_COMBO_LED_DEV, OnSelchangeComboLedDev)
	ON_CBN_SELCHANGE(IDC_COMBO_PARKLAMP, OnSelchangeComboParklamp)
	ON_CBN_SELCHANGE(IDC_COMBO_PARKINGSTATE, OnSelchangeComboParkingstate)
	ON_BN_CLICKED(IDC_BTN_GETSTATUS, OnBtnGetstatus)
	ON_CBN_SELCHANGE(IDC_COMBO_MIXLAMPMODE, OnSelchangeComboMixlampmode)
	ON_BN_CLICKED(IDC_BTN_DEL_TEMPORARY_CARD, OnBtnDelTemporaryCard)
	ON_BN_CLICKED(IDC_BTN_CREATE_LINK, OnBtnCreateLink)
	ON_BN_CLICKED(IDC_BTN_TEMPORARY_CARD_SEND, OnBtnTemporaryCardSend)
	ON_BN_CLICKED(IDC_BTN_STOP_SEND, OnBtnStopSend)
	ON_BN_CLICKED(IDC_BTN_GATE_CTRL, OnBtnGateCtrl)
	ON_BN_CLICKED(IDC_BTN_VEHICLE_CREATE_LINK_VEHICLE, OnBtnVehicleCreateLinkVehicle)
	ON_BN_CLICKED(IDC_BTN_TEMPORARY_VEHICLE_SEND, OnBtnTemporaryVehicleSend)
	ON_BN_CLICKED(IDC_BTN_VEHICLE_STOP_SEND, OnBtnVehicleStopSend)
	ON_BN_CLICKED(IDC_BTN_ITC_IOIN, OnBtnItcIoin)
	ON_BN_CLICKED(IDC_BTN_TME_CFG, OnBtnTmeCfg)
	ON_BN_CLICKED(IDC_BTN_SET_PARKING_DATASTATE, OnBtnSetParkingDatastate)
	ON_BN_CLICKED(IDC_BTN_GET_PARKING_DATASTATE, OnBtnGetParkingDatastate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTsSeries message handlers

//void CALLBACK g_fTransChanDataCallBack(LONG m_lTranHandle, char *pRecvDataBuffer, DWORD dwBufSize, DWORD dwUser)
void CALLBACK g_fTransChanDataCallBack(DWORD m_lTranHandle, void *pRecvDataBuffer, DWORD dwBufSize, void* pUserData)
{
	char szLan[1024] = {0};
	char szTemp[1204] = {0};
	memcpy(szTemp, pRecvDataBuffer, dwBufSize);
	sprintf(szLan, "Info[%s], Len[%d]", szTemp, dwBufSize);
	AfxMessageBox(szLan);
	return;
}

void CDlgTsSeries::OnBtnSetTrans() 
{
	// TODO: Add your control notification handler code here
	m_lTranHandle = NET_DVR_StartRemoteConfig(m_lLoginID, NET_ITS_TRANSCHAN_START, NULL, 0, g_fTransChanDataCallBack, this);

	//m_lTranHandle = NET_DVR_TransChanStart(m_lLoginID, NET_ITS_TRANSCHAN_START, NULL, 0, g_fTransChanDataCallBack, NULL);
	if (m_lTranHandle  == -1)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartRemoteConfig Failed!");
		AfxMessageBox("Start Direct Transmission Failed");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StartRemoteConfig Success!");
	MessageBox("success to start!");
	OnBtnSendDataTrans();
// 	OnBtnSendDataTrans();
// 	OnBtnSendDataTrans();
// 	OnBtnSendDataTrans();
}

void CDlgTsSeries::OnBtnOutTrans() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	if (m_lTranHandle < 0)
	{
		return;
	}
	//if (!NET_DVR_TransStop(m_lTranHandle))
	if(!NET_DVR_StopRemoteConfig(m_lTranHandle))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopRemoteConfig Failed!");
		g_StringLanType(szLan, "停止通明通道失败", "Stop Direct Transmission Failed");
		AfxMessageBox(szLan);
		return;
	}
}

void CDlgTsSeries::OnBtnSendDataTrans() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	int iBufLen = m_csSendData.GetLength()<1024*1024?m_csSendData.GetLength():1024*1024;
	char *psSendBuf = (LPSTR)(LPCTSTR)m_csSendData;	
	m_csSendData.ReleaseBuffer();

	if (m_lTranHandle < 0)
	{
		return;
	}

	if (!NET_DVR_SendRemoteConfig(m_lTranHandle, 0, psSendBuf, iBufLen))
	//if (!NET_DVR_TransSend(m_lTranHandle, 0, psSendBuf, iBufLen))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SendRemoteConfig Failed!");
		g_StringLanType(szLan, "发送失败", "Send Failed");
		AfxMessageBox(szLan);
		return;
	}
	g_StringLanType(szLan, "发送成功", "Send Succ");
	AfxMessageBox(szLan);
	return;
}

void CDlgTsSeries::OnBtnGetChanLane() 
{
	// TODO: Add your control notification handler code here
	UpdateData(FALSE);
	DWORD dwRet = 0;
	char szLan[128] = {0};
	NET_ITS_IPC_CHAN_LANE_CFG strItsIpcChanLaneCfg;
	memset(&strItsIpcChanLaneCfg, 0, sizeof(strItsIpcChanLaneCfg));

	if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_ITS_GET_GATEIPC_CHAN_CFG, m_lChannel, &strItsIpcChanLaneCfg, sizeof(strItsIpcChanLaneCfg), &dwRet))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_ITS_GET_GATEIPC_CHAN_CFG Failed!");
		g_StringLanType(szLan, "获取出入口参数失败", "Failed to get the entrance parameters");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_ITS_GET_GATEIPC_CHAN_CFG SUCC!");
	}
	
	m_cmbIpcType.SetCurSel(strItsIpcChanLaneCfg.byIpcType -1);
	memcpy(m_strITSGateLaneCfg, &strItsIpcChanLaneCfg.struGateLane[0], sizeof(m_strITSGateLaneCfg));
	m_cmbGateLane.SetCurSel(0);
	OnSelchangeComboGatelane();
	UpdateData(TRUE);
}

void CDlgTsSeries::OnBtnSetChanLane() 
{
	// TODO: Add your control notification handler code here
	UpdateData(FALSE);
	char szLan[128] = {0};
	NET_ITS_IPC_CHAN_LANE_CFG strItsIpcChanLaneCfg;
	memset(&strItsIpcChanLaneCfg, 0, sizeof(strItsIpcChanLaneCfg));
	int i = 0;
	BOOL bRet = 0;
	strItsIpcChanLaneCfg.byIpcType = m_cmbIpcType.GetCurSel()+1;
	strItsIpcChanLaneCfg.dwSize = sizeof(strItsIpcChanLaneCfg);
	
	memcpy(&strItsIpcChanLaneCfg.struGateLane[0], m_strITSGateLaneCfg, sizeof(m_strITSGateLaneCfg));

	if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_ITS_SET_GATEIPC_CHAN_CFG, m_lChannel, &strItsIpcChanLaneCfg, sizeof(strItsIpcChanLaneCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_ITS_SET_GATEIPC_CHAN_CFG Failed!");
		g_StringLanType(szLan, "设置出入口参数失败", "Failed to set the entrance parameters");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_ITS_SET_GATEIPC_CHAN_CFG Succ!");
		g_StringLanType(szLan, "设置出入口参数成功", "Succ to set the entrance parameters");
		AfxMessageBox(szLan);
	}
	return;
}

void CDlgTsSeries::OnBtnSaveLane() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int iItem = m_cmbGateLane.GetCurSel();
	if (iItem >= 0 && iItem <=3)
	{
		memcpy(m_strITSGateLaneCfg[iItem].byGateSiteID, m_csGateSiteID, 48);
		memcpy(m_strITSGateLaneCfg[iItem].byGateInfo, m_csGateInfo, 48);
		memcpy(m_strITSGateLaneCfg[iItem].byLaneName, m_csLaneName, 32);
		m_strITSGateLaneCfg[iItem].byValid = m_cmbValid.GetCurSel();
		m_strITSGateLaneCfg[iItem].byCamLaneId = m_iCamLaneID;
		m_strITSGateLaneCfg[iItem].wLaneid = m_iLaneID;
		m_strITSGateLaneCfg[iItem].byRelativeIoNum = m_iRelativeIONum;
		m_strITSGateLaneCfg[iItem].byDirection = m_cmbDirection.GetCurSel()+1;
		m_strITSGateLaneCfg[iItem].byLprMode = m_comLprMode.GetCurSel();
		m_strITSGateLaneCfg[iItem].byCardMode = m_comCardMode.GetCurSel();
		m_strITSGateLaneCfg[iItem].byGateLaneMode = m_comGateLaneMode.GetCurSel();
		//新增参数 2013-11-19
	 	m_strITSGateLaneCfg[iItem].byCharge = m_comCharge.GetCurSel();
		m_strITSGateLaneCfg[iItem].byChargeMode = m_comChargeMode.GetCurSel();
		m_strITSGateLaneCfg[iItem].byLedRelativeIndex[m_comLEDDev.GetCurSel()] = m_byLedIndex;
		m_strITSGateLaneCfg[iItem].byGateRelativeIndex = m_byGateIndex;
		m_strITSGateLaneCfg[iItem].byFarRrRelativeIndex = m_byRelatIndex;
	}

}

void CDlgTsSeries::OnSelchangeComboGatelane() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iItem = m_cmbGateLane.GetCurSel();
	m_csGateSiteID.Format("%s", m_strITSGateLaneCfg[iItem].byGateSiteID);
	m_csGateInfo.Format("%s", m_strITSGateLaneCfg[iItem].byGateInfo);
	m_csLaneName.Format("%s", m_strITSGateLaneCfg[iItem].byLaneName);
	m_cmbValid.SetCurSel(m_strITSGateLaneCfg[iItem].byValid);
	m_iCamLaneID = m_strITSGateLaneCfg[iItem].byCamLaneId;
	m_iLaneID = m_strITSGateLaneCfg[iItem].wLaneid;
	m_iRelativeIONum = m_strITSGateLaneCfg[iItem].byRelativeIoNum;
	m_cmbDirection.SetCurSel(m_strITSGateLaneCfg[iItem].byDirection -1);
	//m_cmbIOMode.SetCurSel(m_strITSGateLaneCfg[iItem].byIoMode);
	m_comCardMode.SetCurSel(m_strITSGateLaneCfg[iItem].byCardMode);
	m_comLprMode.SetCurSel(m_strITSGateLaneCfg[iItem].byLprMode);
	m_comGateLaneMode.SetCurSel(m_strITSGateLaneCfg[iItem].byGateLaneMode);

	//新增参数 2013-11-19
	m_comCharge.SetCurSel(m_strITSGateLaneCfg[iItem].byCharge);
	m_comChargeMode.SetCurSel(m_strITSGateLaneCfg[iItem].byChargeMode);
	m_comLEDDev.SetCurSel(0);
	m_byLedIndex = m_strITSGateLaneCfg[iItem].byLedRelativeIndex[0];
	m_byGateIndex = m_strITSGateLaneCfg[iItem].byGateRelativeIndex;
	m_byRelatIndex = m_strITSGateLaneCfg[iItem].byFarRrRelativeIndex;

	UpdateData(FALSE);
}

void CDlgTsSeries::OnBtnRemoteCommand() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	NET_ITS_REMOTE_CONTROL strRemoteControl;
	memset(&strRemoteControl, 0, sizeof(strRemoteControl));

	strRemoteControl.dwSize = sizeof(strRemoteControl);
	strRemoteControl.struRemoteCommand.byCamLaneId = m_iRemoteCamlaneID;
	strRemoteControl.struRemoteCommand.wLaneid = m_iRemoteLaneID;
	strRemoteControl.struRemoteCommand.dwCode = m_cmbCode.GetCurSel();

	if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_ITS_REMOTE_DEVICE_CONTROL, 0, &strRemoteControl, sizeof(strRemoteControl)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_ITS_REMOTE_DEVICE_CONTROL Failed!");
		g_StringLanType(szLan, "设置远程控制参数失败", "Failed to set up a remote control parameters");
		AfxMessageBox(szLan);
		return;
	}
}

void CDlgTsSeries::OnBtnGetEctWorkStatus2() 
{
	// TODO: Add your control notification handler code here
	CDlgEctChanStatus dlg;
	dlg.m_lLoginID = m_lLoginID;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.m_lChannel = m_lChannel;
	dlg.DoModal();
}

BOOL CDlgTsSeries::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	memset(&m_struLampCtrlInfo, 0, sizeof(m_struLampCtrlInfo));
	m_comParkNum.EnableWindow(FALSE);
	m_comParkInfo.EnableWindow(FALSE);
	m_comIOSTate.EnableWindow(FALSE);

	m_comRelateParkingLamp.EnableWindow(FALSE);
	m_comEnable.EnableWindow(FALSE);
	m_comFlicker.EnableWindow(FALSE);

		
	m_comLampCtrlMode.SetCurSel(0);
	m_comParkNum.SetCurSel(0);
	m_comParkInfo.SetCurSel(0);
	m_comParkStatus.SetCurSel(0);
	m_comCardType.SetCurSel(0);
	memset(&m_struParkSpaceAttribute, 0, sizeof(m_struParkSpaceAttribute));
	memset(&m_struLampExternal, 0, sizeof(m_struLampExternal));
	memset(&m_struCompelCapTure, 0, sizeof(m_struCompelCapTure));

    GetDlgItem(IDC_BTN_VEHICLE_CREATE_LINK_VEHICLE)->EnableWindow(TRUE);
    GetDlgItem(IDC_BTN_TEMPORARY_VEHICLE_SEND)->EnableWindow(FALSE);
    GetDlgItem(IDC_BTN_VEHICLE_STOP_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CREATE_LINK)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_TEMPORARY_CARD_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_STOP_SEND)->EnableWindow(FALSE);

    char szLan[128] = { 0 };
    int iIndex = 0;
    m_comGateCtrl.ResetContent();
    g_StringLanType(szLan, "关闭道闸", "close");
    m_comGateCtrl.InsertString(iIndex, szLan);
    m_comGateCtrl.SetItemData(iIndex, 0);
    iIndex++;

    g_StringLanType(szLan, "开启道闸", "open");
    m_comGateCtrl.InsertString(iIndex, szLan);
    m_comGateCtrl.SetItemData(iIndex, 1);
    iIndex++;


    g_StringLanType(szLan, "停止道闸", "stop");
    m_comGateCtrl.InsertString(iIndex, szLan);
    m_comGateCtrl.SetItemData(iIndex, 2);
    iIndex++;


    g_StringLanType(szLan, "锁定道闸", "lock");
    m_comGateCtrl.InsertString(iIndex, szLan);
    m_comGateCtrl.SetItemData(iIndex, 3);
    iIndex++;

    g_StringLanType(szLan, "解锁道闸", "unlock");
    m_comGateCtrl.InsertString(iIndex, szLan);
    m_comGateCtrl.SetItemData(iIndex, 4);
    iIndex++;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTsSeries::OnBtnGetEctDevStatue() 
{
	// TODO: Add your control notification handler code here
	CDlgEctWorkState dlg;
	dlg.m_lLoginID = m_lLoginID;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.DoModal();
}

void CDlgTsSeries::OnBtnPreLampCtrlInfo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struLampCtrlInfo.dwSize = sizeof(NET_DVR_LAMP_CTRL_INFO);
	m_struLampCtrlInfo.byLampCtrlMode = m_comLampCtrlMode.GetCurSel() + 1;//
	m_struLampCtrlInfo.byCtrlChannelIndex = m_byCtrlChannelIndex;         //

	if(INLAY_LAMP_CTRL_MODE == m_comLampCtrlMode.GetCurSel() + 1)//
	{
		m_struLampCtrlInfo.uLampCtrlMode.struInlayLampCtrlMode.struLampStateCtrl[m_comParkStatus.GetCurSel()].byEnable = m_comEnable.GetCurSel();
		m_struLampCtrlInfo.uLampCtrlMode.struInlayLampCtrlMode.struLampStateCtrl[m_comParkStatus.GetCurSel()].byFlicker = m_comFlicker.GetCurSel();
		m_struLampCtrlInfo.uLampCtrlMode.struInlayLampCtrlMode.struLampStateCtrl[m_comParkStatus.GetCurSel()].byLampColor = m_comLampColor.GetCurSel();
	}
	else if (EXTERNAL_LAMP_CTRL_MODE == m_comLampCtrlMode.GetCurSel() + 1)//
	{
		if (NORMAL_PARK_IO_STATE == m_comParkInfo.GetCurSel())
		{
			m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[m_comParkNum.GetCurSel()].struNormalParkIOState.byEnable = m_comEnable.GetCurSel();
			m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[m_comParkNum.GetCurSel()].struNormalParkIOState.byFlicker = m_comFlicker.GetCurSel();
			m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[m_comParkNum.GetCurSel()].struNormalParkIOState.byIOState = m_comIOSTate.GetCurSel();
		}
		else if(NORMAL_NO_PARK_IO_STATE == m_comParkInfo.GetCurSel())
		{
			m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[m_comParkNum.GetCurSel()].struNormalNoParkIOState.byEnable = m_comEnable.GetCurSel();
			m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[m_comParkNum.GetCurSel()].struNormalNoParkIOState.byFlicker = m_comFlicker.GetCurSel();
			m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[m_comParkNum.GetCurSel()].struNormalNoParkIOState.byIOState = m_comIOSTate.GetCurSel();
		}
		else if(SPECIAL_PARK_IO_STATE == m_comParkInfo.GetCurSel())
		{
			m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[m_comParkNum.GetCurSel()].struSpecialParkIOState.byEnable = m_comEnable.GetCurSel();
			m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[m_comParkNum.GetCurSel()].struSpecialParkIOState.byFlicker = m_comFlicker.GetCurSel();
			m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[m_comParkNum.GetCurSel()].struSpecialParkIOState.byIOState = m_comIOSTate.GetCurSel();
		}
		else
		{
			m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[m_comParkNum.GetCurSel()].struSpecialNoParkIOState.byEnable = m_comEnable.GetCurSel();
			m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[m_comParkNum.GetCurSel()].struSpecialNoParkIOState.byFlicker = m_comFlicker.GetCurSel();
			m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[m_comParkNum.GetCurSel()].struSpecialNoParkIOState.byIOState = m_comIOSTate.GetCurSel();
		}
	}
	else if(PARKING_LAMP_CTRL_MODE == m_comLampCtrlMode.GetCurSel() + 1)//
	{
		int itest = m_comParkingLamp.GetCurSel();
		int iy = m_comParkStatus.GetCurSel();
		m_struLampCtrlInfo.uLampCtrlMode.struParkLampCtrlMode[m_comParkingLamp.GetCurSel()].byLampType = m_comRelateParkingLamp.GetCurSel();
		m_struLampCtrlInfo.uLampCtrlMode.struParkLampCtrlMode[m_comParkingLamp.GetCurSel()].struLampInfo[m_comParkingStatus.GetCurSel()].byEnable = m_comEnable.GetCurSel();
		m_struLampCtrlInfo.uLampCtrlMode.struParkLampCtrlMode[m_comParkingLamp.GetCurSel()].struLampInfo[m_comParkingStatus.GetCurSel()].byFlicker = m_comFlicker.GetCurSel();
		m_struLampCtrlInfo.uLampCtrlMode.struParkLampCtrlMode[m_comParkingLamp.GetCurSel()].struLampInfo[m_comParkingStatus.GetCurSel()].byLampColor = m_comLampColor.GetCurSel();
	}
    else if (MIXLAMP_CTRL_MODE == m_comLampCtrlMode.GetCurSel() + 1)
    {
        if (m_comMixLampMode.GetCurSel() == 0)
        {
            m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struExternalParkLamp[m_comParkNum.GetCurSel()].byLampType = m_comRelateParkingLamp.GetCurSel();
            m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struExternalParkLamp[m_comParkNum.GetCurSel()].struLampParam[m_comParkStatus.GetCurSel()].byEnable = \
                m_comEnable.GetCurSel();
            m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struExternalParkLamp[m_comParkNum.GetCurSel()].struLampParam[m_comParkStatus.GetCurSel()].byFlicker = \
                m_comFlicker.GetCurSel();
            m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struExternalParkLamp[m_comParkNum.GetCurSel()].struLampParam[m_comParkStatus.GetCurSel()].byLampColor = \
            m_comLampColor.GetCurSel();
        }
        else if(m_comMixLampMode.GetCurSel() == 1)
        {
            m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struBuiltInParkLamp[m_comParkStatus.GetCurSel()].byEnable = \
                m_comEnable.GetCurSel();
            m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struBuiltInParkLamp[m_comParkStatus.GetCurSel()].byFlicker = \
                m_comFlicker.GetCurSel();
            m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struBuiltInParkLamp[m_comParkStatus.GetCurSel()].byLampColor = \
                m_comLampColor.GetCurSel();
        }
    }
    else if (SINGLELAMP_CTRL_MODE == m_comLampCtrlMode.GetCurSel() + 1)
    {
        m_struLampCtrlInfo.uLampCtrlMode.struSingleExternalLampCtrlMode.byLampType = m_comRelateParkingLamp.GetCurSel();
        m_struLampCtrlInfo.uLampCtrlMode.struSingleExternalLampCtrlMode.struExternLampStateCtrl[m_comParkNum.GetCurSel()].byEnable = m_comEnable.GetCurSel();
        m_struLampCtrlInfo.uLampCtrlMode.struSingleExternalLampCtrlMode.struExternLampStateCtrl[m_comParkNum.GetCurSel()].byFlicker = m_comFlicker.GetCurSel();
        m_struLampCtrlInfo.uLampCtrlMode.struSingleExternalLampCtrlMode.struExternLampStateCtrl[m_comParkNum.GetCurSel()].byLampColor = m_comLampColor.GetCurSel();
        m_struLampCtrlInfo.uLampCtrlMode.struSingleExternalLampCtrlMode.struExternLampStateCtrl[m_comParkNum.GetCurSel()].byIOState = m_comIOSTate.GetCurSel();
    }
}

void CDlgTsSeries::OnBtnSetLampCtrlInfo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	m_struLampCtrlInfo.dwSize = sizeof(m_struLampCtrlInfo);
	if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_ITS_SET_LAMP_CTRLCFG, m_lChannel, &m_struLampCtrlInfo, sizeof(m_struLampCtrlInfo)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_ITS_SET_LAMP_CTRLCFG Failed!");
		g_StringLanType(szLan, "设置内外置灯参数失败", "Failed to set the entrance parameters");
		AfxMessageBox(szLan);
		//return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_ITS_SET_LAMP_CTRLCFG Succ!");
		g_StringLanType(szLan, "设置内外置灯参数成功", "Succ to set the entrance parameters");
		AfxMessageBox(szLan);
	}
	return;

}

void CDlgTsSeries::OnBtnGetLampCtrlInfo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwRet = 0;
	char szLan[128] = {0};
	memset(&m_struLampCtrlInfo, 0, sizeof(m_struLampCtrlInfo));
	
	if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_ITS_GET_LAMP_CTRLCFG, m_lChannel, &m_struLampCtrlInfo, sizeof(m_struLampCtrlInfo), &dwRet))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_ITS_GET_LAMP_CTRLCFG Failed!");
		g_StringLanType(szLan, "获取内外置灯参数失败", "Failed to get the entrance parameters");
		AfxMessageBox(szLan);
		//return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_ITS_GET_LAMP_CTRLCFG Succ!");
		g_StringLanType(szLan, "获取内外置灯参数成功", "Succ to set the entrance parameters");
		AfxMessageBox(szLan);
	}
	
	m_comParkNum.EnableWindow(TRUE);
	m_comParkInfo.EnableWindow(TRUE);
	m_comIOSTate.EnableWindow(TRUE);
	m_comParkStatus.EnableWindow(TRUE);
	m_comLampColor.EnableWindow(TRUE);
	m_comRelateParkingLamp.EnableWindow(TRUE);
	m_comEnable.EnableWindow(TRUE);
	m_comFlicker.EnableWindow(TRUE);

	m_comLampCtrlMode.SetCurSel(0);
	m_comParkNum.SetCurSel(0);
	m_comParkInfo.SetCurSel(0);
	m_comParkStatus.SetCurSel(0);
	if (m_struLampCtrlInfo.byLampCtrlMode > 0)
	{
		m_comLampCtrlMode.SetCurSel(m_struLampCtrlInfo.byLampCtrlMode-1);
	}
	m_byCtrlChannelIndex = m_struLampCtrlInfo.byCtrlChannelIndex;//
	if(INLAY_LAMP_CTRL_MODE == m_comLampCtrlMode.GetCurSel() + 1)//
	{
		m_comParkNum.EnableWindow(FALSE);
		m_comParkInfo.EnableWindow(FALSE);
		m_comIOSTate.EnableWindow(FALSE);
		
		m_comEnable.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struInlayLampCtrlMode.struLampStateCtrl[0].byEnable);
		m_comFlicker.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struInlayLampCtrlMode.struLampStateCtrl[0].byFlicker);
		m_comLampColor.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struInlayLampCtrlMode.struLampStateCtrl[0].byLampColor);
	}
	else if (EXTERNAL_LAMP_CTRL_MODE == m_comLampCtrlMode.GetCurSel() + 1)//
	{
		m_comParkStatus.EnableWindow(FALSE);
		m_comLampColor.EnableWindow(FALSE);
		
		m_comEnable.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[0].struNormalParkIOState.byEnable);
		m_comFlicker.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[0].struNormalParkIOState.byFlicker);
		m_comIOSTate.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[0].struNormalParkIOState.byIOState);
	}
	else if(PARKING_LAMP_CTRL_MODE == m_comLampCtrlMode.GetCurSel() + 1)//
	{
		m_comIOSTate.EnableWindow(FALSE);
		m_comParkNum.EnableWindow(FALSE);
		m_comParkInfo.EnableWindow(FALSE);
		m_comParkStatus.EnableWindow(FALSE);
		//m_comParkingLamp.EnableWindow(FALSE);

		m_comParkingLamp.SetCurSel(0);//
		m_comRelateParkingLamp.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struParkLampCtrlMode[0].byLampType);//
		m_comParkingStatus.SetCurSel(0);//
		m_comEnable.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struParkLampCtrlMode[0].struLampInfo[0].byEnable);
		m_comFlicker.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struParkLampCtrlMode[0].struLampInfo[0].byFlicker);
		m_comLampColor.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struParkLampCtrlMode[0].struLampInfo[0].byLampColor);	
	}
    else if (MIXLAMP_CTRL_MODE == m_comLampCtrlMode.GetCurSel() + 1)
    {
        m_comMixLampMode.SetCurSel(0);
        
        MixlampModeStatusAndValue(0);      
    }
    else if (SINGLELAMP_CTRL_MODE == m_comLampCtrlMode.GetCurSel() + 1)
    {
        SinglelampModeStatus();
        m_comRelateParkingLamp.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struSingleExternalLampCtrlMode.byLampType);
        m_comParkNum.SetCurSel(0);
        m_comEnable.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struSingleExternalLampCtrlMode.struExternLampStateCtrl[0].byEnable);
        m_comFlicker.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struSingleExternalLampCtrlMode.struExternLampStateCtrl[0].byFlicker);
        m_comLampColor.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struSingleExternalLampCtrlMode.struExternLampStateCtrl[0].byLampColor);
        m_comIOSTate.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struSingleExternalLampCtrlMode.struExternLampStateCtrl[0].byIOState);
    }
	UpdateData(FALSE);
}

void CDlgTsSeries::OnSelchangeComboLampctrlmode() 
{
	// TODO: Add your control notification handler code here
	m_comParkNum.EnableWindow(TRUE);
	m_comParkInfo.EnableWindow(TRUE);
	m_comIOSTate.EnableWindow(TRUE);
	m_comParkStatus.EnableWindow(TRUE);
	m_comLampColor.EnableWindow(TRUE);
	m_comParkNum.SetCurSel(0);
	m_comParkInfo.SetCurSel(0);
	m_comParkStatus.SetCurSel(0);
	if(INLAY_LAMP_CTRL_MODE == m_comLampCtrlMode.GetCurSel() + 1)//
	{
		m_comParkNum.EnableWindow(FALSE);
		m_comParkInfo.EnableWindow(FALSE);
		m_comIOSTate.EnableWindow(FALSE);
        m_comMixLampMode.EnableWindow(FALSE);

		m_comEnable.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struInlayLampCtrlMode.struLampStateCtrl[0].byEnable);
		m_comFlicker.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struInlayLampCtrlMode.struLampStateCtrl[0].byFlicker);
		m_comLampColor.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struInlayLampCtrlMode.struLampStateCtrl[0].byLampColor);
	}
	else if (EXTERNAL_LAMP_CTRL_MODE == m_comLampCtrlMode.GetCurSel() + 1)//
	{
		m_comParkStatus.EnableWindow(FALSE);
		m_comLampColor.EnableWindow(FALSE);
        m_comMixLampMode.EnableWindow(FALSE);

		m_comEnable.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[0].struNormalParkIOState.byEnable);
		m_comFlicker.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[0].struNormalParkIOState.byFlicker);
		m_comIOSTate.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[0].struNormalParkIOState.byIOState);
	}
	else if(PARKING_LAMP_CTRL_MODE == m_comLampCtrlMode.GetCurSel() + 1)//
	{
		m_comIOSTate.EnableWindow(FALSE);
		m_comParkNum.EnableWindow(FALSE);
		m_comParkInfo.EnableWindow(FALSE);
		m_comParkStatus.EnableWindow(FALSE);
		//m_comParkingLamp.EnableWindow(FALSE);
        m_comMixLampMode.EnableWindow(FALSE);

		m_comParkingLamp.SetCurSel(0);//
		m_comRelateParkingLamp.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struParkLampCtrlMode[0].byLampType);//关联车位灯信息
		m_comParkingStatus.SetCurSel(0);//
		m_comEnable.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struParkLampCtrlMode[0].struLampInfo[0].byEnable);
		m_comFlicker.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struParkLampCtrlMode[0].struLampInfo[0].byFlicker);
		m_comLampColor.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struParkLampCtrlMode[0].struLampInfo[0].byLampColor);
	}
    else if (MIXLAMP_CTRL_MODE == m_comLampCtrlMode.GetCurSel() + 1)
    {
        m_comMixLampMode.EnableWindow(TRUE);
        m_comMixLampMode.SetCurSel(0);
        OnSelchangeComboMixlampmode();

        UpdateData(FALSE);

    }
    else if (SINGLELAMP_CTRL_MODE == m_comLampCtrlMode.GetCurSel() + 1)
    {
        m_comMixLampMode.EnableWindow(FALSE);
        SinglelampModeStatus();
    }
    UpdateData(FALSE);
}

void CDlgTsSeries::OnSelchangeComboParknum() 
{
	// TODO: Add your control notification handler code here
    if (SINGLELAMP_CTRL_MODE == m_comLampCtrlMode.GetCurSel() + 1)
    {
        m_comMixLampMode.EnableWindow(FALSE);
        SinglelampModeStatus();

        m_comRelateParkingLamp.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struSingleExternalLampCtrlMode.byLampType);
        m_comParkingStatus.SetCurSel(0);

        m_comEnable.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struSingleExternalLampCtrlMode.struExternLampStateCtrl[m_comParkNum.GetCurSel()].byEnable);
        m_comFlicker.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struSingleExternalLampCtrlMode.struExternLampStateCtrl[m_comParkNum.GetCurSel()].byFlicker);
        m_comLampColor.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struSingleExternalLampCtrlMode.struExternLampStateCtrl[m_comParkNum.GetCurSel()].byLampColor);
        m_comIOSTate.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struSingleExternalLampCtrlMode.struExternLampStateCtrl[m_comParkNum.GetCurSel()].byIOState);
    } 
    else if (MIXLAMP_CTRL_MODE == m_comLampCtrlMode.GetCurSel() + 1)
    {
        if (m_comMixLampMode.GetCurSel() == 0)
        {
            m_comRelateParkingLamp.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struExternalParkLamp[m_comParkNum.GetCurSel()].byLampType);
            m_comEnable.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struExternalParkLamp[m_comParkNum.GetCurSel()].struLampParam[0].byEnable);
            m_comFlicker.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struExternalParkLamp[m_comParkNum.GetCurSel()].struLampParam[0].byFlicker);
            m_comLampColor.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struExternalParkLamp[m_comParkNum.GetCurSel()].struLampParam[0].byLampColor);   
        } 
//         else if(m_comMixLampMode.GetCurSel() == 1)
//         {
//             m_comEnable.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struBuiltInParkLamp[m_comParkNum.GetCurSel()].byEnable);
//             m_comFlicker.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struBuiltInParkLamp[m_comParkNum.GetCurSel()].byFlicker);
//             m_comLampColor.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struBuiltInParkLamp[m_comParkNum.GetCurSel()].byLampColor);
//         }
    }
    else
    {
        m_comParkInfo.SetCurSel(0);
        m_comEnable.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[m_comParkNum.GetCurSel()].struNormalParkIOState.byEnable);
        m_comFlicker.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[m_comParkNum.GetCurSel()].struNormalParkIOState.byFlicker);
        m_comIOSTate.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[m_comParkNum.GetCurSel()].struNormalParkIOState.byIOState);
    }
    UpdateData(FALSE);
}

void CDlgTsSeries::OnSelchangeComboParkinfo() 
{
	// TODO: Add your control notification handler code here
	if (NORMAL_PARK_IO_STATE == m_comParkInfo.GetCurSel())
	{
		m_comEnable.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[m_comParkNum.GetCurSel()].struNormalParkIOState.byEnable);
		m_comFlicker.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[m_comParkNum.GetCurSel()].struNormalParkIOState.byFlicker);
		m_comIOSTate.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[m_comParkNum.GetCurSel()].struNormalParkIOState.byIOState);
	}
	else if(NORMAL_NO_PARK_IO_STATE == m_comParkInfo.GetCurSel())
	{
		m_comEnable.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[m_comParkNum.GetCurSel()].struNormalNoParkIOState.byEnable);
		m_comFlicker.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[m_comParkNum.GetCurSel()].struNormalNoParkIOState.byFlicker);
		m_comIOSTate.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[m_comParkNum.GetCurSel()].struNormalNoParkIOState.byIOState);
	}
	else if(SPECIAL_PARK_IO_STATE == m_comParkInfo.GetCurSel())
	{
		m_comEnable.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[m_comParkNum.GetCurSel()].struSpecialParkIOState.byEnable);
		m_comFlicker.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[m_comParkNum.GetCurSel()].struSpecialParkIOState.byFlicker);
		m_comIOSTate.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[m_comParkNum.GetCurSel()].struSpecialParkIOState.byIOState);
	}
	else
	{
		m_comEnable.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[m_comParkNum.GetCurSel()].struSpecialNoParkIOState.byEnable);
		m_comFlicker.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[m_comParkNum.GetCurSel()].struSpecialNoParkIOState.byFlicker);
		m_comIOSTate.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struExternalLampCtrlMode.struParkInfo[m_comParkNum.GetCurSel()].struSpecialNoParkIOState.byIOState);
	}
}

void CDlgTsSeries::OnSelchangeComboParkstatus() 
{
	// TODO: Add your control notification handler code here
//     if (MIXLAMP_CTRL_MODE == m_comLampCtrlMode.GetCurSel() + 1)
//     {
//         if (m_comMixLampMode.GetCurSel() == 0)
//         {
//             m_comRelateParkingLamp.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struExternalParkLamp[m_comParkNum.GetCurSel()].byLampType);
//             m_comEnable.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struExternalParkLamp[m_comParkNum.GetCurSel()].struLampParam[m_comParkStatus.GetCurSel()].byEnable);
//             m_comFlicker.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struExternalParkLamp[m_comParkNum.GetCurSel()].struLampParam[m_comParkStatus.GetCurSel()].byFlicker);
//             m_comLampColor.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struExternalParkLamp[m_comParkNum.GetCurSel()].struLampParam[m_comParkStatus.GetCurSel()].byLampColor);   
//         } 
//         else if(m_comMixLampMode.GetCurSel() == 1)
//         {
//             m_comEnable.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struBuiltInParkLamp[m_comParkStatus.GetCurSel()].byEnable);
//             m_comFlicker.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struBuiltInParkLamp[m_comParkStatus.GetCurSel()].byFlicker);
//             m_comLampColor.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struBuiltInParkLamp[m_comParkStatus.GetCurSel()].byLampColor);
//         }
//     } 
//     else
    {
        
        m_comEnable.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struInlayLampCtrlMode.struLampStateCtrl[m_comParkStatus.GetCurSel()].byEnable);
        m_comFlicker.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struInlayLampCtrlMode.struLampStateCtrl[m_comParkStatus.GetCurSel()].byFlicker);
	    m_comLampColor.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struInlayLampCtrlMode.struLampStateCtrl[m_comParkStatus.GetCurSel()].byLampColor);
    }
    UpdateData(FALSE);
}

void CDlgTsSeries::OnBtnPreParkspaceAttribute() 
{
	// TODO: Add your control notification handler code here
	m_struParkSpaceAttribute.dwSize = sizeof(NET_DVR_PARKSPACE_ATTRIBUTE);
	m_struParkSpaceAttribute.struParkSpaceInfo[m_comParkSpaceInfo.GetCurSel()].byParkSpaceAttribute = m_comParkSpaceAttribute.GetCurSel();
}


void CDlgTsSeries::OnBtnSetParkspaceAttribute() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_ITS_SET_PARKSPACE_ATTRIBUTE_CFG, m_lChannel, &m_struParkSpaceAttribute, sizeof(m_struParkSpaceAttribute)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_ITS_SET_PARKSPACE_ATTRIBUTE_CFG Failed!");
		g_StringLanType(szLan, "设置特殊车位参数失败", "Failed to set the entrance parameters");
		AfxMessageBox(szLan);
		//return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_ITS_SET_PARKSPACE_ATTRIBUTE_CFG Succ!");
		g_StringLanType(szLan, "设置特殊车位参数成功", "Succ to set the entrance parameters");
		AfxMessageBox(szLan);
	}
	return;

}

void CDlgTsSeries::OnBtnGetParkspaceAttribute() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwRet = 0;
	char szLan[128] = {0};
	memset(&m_struParkSpaceAttribute, 0, sizeof(m_struParkSpaceAttribute));
	
	if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_ITS_GET_PARKSPACE_ATTRIBUTE_CFG, m_lChannel, &m_struParkSpaceAttribute, sizeof(m_struParkSpaceAttribute), &dwRet))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_ITS_GET_PARKSPACE_ATTRIBUTE_CFG Failed!");
		g_StringLanType(szLan, "获取特殊车位参数失败", "Failed to get the entrance parameters");
		AfxMessageBox(szLan);
		//return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_ITS_GET_PARKSPACE_ATTRIBUTE_CFG Succ!");
		g_StringLanType(szLan, "获取特殊车位参数成功", "Succ to set the entrance parameters");
		AfxMessageBox(szLan);
	}

	m_comParkSpaceInfo.SetCurSel(0);
	m_comParkSpaceAttribute.SetCurSel(m_struParkSpaceAttribute.struParkSpaceInfo[0].byParkSpaceAttribute);
}

void CDlgTsSeries::OnSelchangeComboParkSpaceInfo() 
{
	m_comParkSpaceAttribute.SetCurSel(m_struParkSpaceAttribute.struParkSpaceInfo[m_comParkSpaceInfo.GetCurSel()].byParkSpaceAttribute);
}

void CDlgTsSeries::OnBtnSetLampExternal() 
{
	// TODO: Add your control notification handler code here
	DWORD dwIONo = 0;
	DWORD dwIONo1 = 0;
	DWORD dwIONo2 = 0;
	DWORD dwIONo3 = 0;
	if(1 == m_checkIO1.GetCheck())
	{
		dwIONo1 = 0x1;
	}
	if(1 == m_checkIO2.GetCheck())
	{
		dwIONo2 = 0x2;
	}
	if(1 == m_checkIO3.GetCheck())
	{
		dwIONo3 = 0x4;
	}
	
	dwIONo = dwIONo1 | dwIONo2 | dwIONo3;
	m_struLampExternal.dwSize = sizeof(NET_DVR_LAMP_EXTERNAL_CFG);
	m_struLampExternal.byEnable = m_comLampEnable.GetCurSel();
	m_struLampExternal.struLampStateCtrl.byFlicker = m_comLampFlicker.GetCurSel();
	m_struLampExternal.struLampStateCtrl.dwIONo = dwIONo;
	m_struLampExternal.struLampStateCtrl.byParkingIndex = m_comRelateLaneNo2.GetCurSel()+1;
	
	char szLan[128] = {0};
	if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_ITS_SET_LAMP_EXTERNAL_CFG, m_lChannel, &m_struLampExternal, sizeof(m_struLampExternal)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_ITS_SET_LAMP_EXTERNAL_CFG Failed!");
		g_StringLanType(szLan, "设置外控配置参数失败", "Failed to set the entrance parameters");
		AfxMessageBox(szLan);
		//return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_ITS_SET_LAMP_EXTERNAL_CFG Succ!");
		g_StringLanType(szLan, "设置外控配置参数成功", "Succ to set the entrance parameters");
		AfxMessageBox(szLan);
	}
	return;

}

void CDlgTsSeries::OnBtnGetLampExternal() 
{
	// TODO: Add your control notification handler code here
// 	UpdateData(TRUE);
// 	DWORD dwRet = 0;
// 	char szLan[128] = {0};
// 	memset(&m_struLampExternal, 0, sizeof(m_struLampExternal));
// 	
// 	if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_ITS_GET_LAMP_EXTERNAL_CFG, m_lChannel, &m_struLampExternal, sizeof(m_struLampExternal), &dwRet))
// 	{
// 		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_ITS_GET_LAMP_EXTERNAL_CFG Failed!");
// 		g_StringLanType(szLan, "获取外控配置参数失败", "Failed to get the entrance parameters");
// 		AfxMessageBox(szLan);
// 		//return;
// 	}
// 	else
// 	{
// 		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_ITS_GET_LAMP_EXTERNAL_CFG Succ!");
// 		g_StringLanType(szLan, "获取外控配置参数成功", "Succ to set the entrance parameters");
// 		AfxMessageBox(szLan);
// 	}
// 
// 
// 	DWORD dwIONo1 = 0x1;
// 	DWORD dwIONo2 = 0x2;
// 	DWORD dwIONo3 = 0x4;
// 	m_checkIO1.SetCheck(0);
// 	m_checkIO2.SetCheck(0);
// 	m_checkIO3.SetCheck(0);
// 
// 	m_comLampEnable.SetCurSel(m_struLampExternal.byEnable);
// 	m_comLampFlicker.SetCurSel(m_struLampExternal.struLampStateCtrl.byFlicker);
// 	if(m_struLampExternal.struLampStateCtrl.dwIONo == dwIONo1)
// 	{
// 		m_checkIO1.SetCheck(1);
// 	}
// 	else if(m_struLampExternal.struLampStateCtrl.dwIONo == dwIONo2)
// 	{
// 		m_checkIO2.SetCheck(1);
// 	}
// 	else if(m_struLampExternal.struLampStateCtrl.dwIONo == dwIONo3)
// 	{
// 		m_checkIO3.SetCheck(1);
// 	}
// 	else if(m_struLampExternal.struLampStateCtrl.dwIONo == (dwIONo1 | dwIONo2))
// 	{
// 		m_checkIO1.SetCheck(1);
// 		m_checkIO2.SetCheck(1);
// 	}
// 	else if(m_struLampExternal.struLampStateCtrl.dwIONo == (dwIONo2 | dwIONo3))
// 	{
// 		m_checkIO2.SetCheck(1);
// 		m_checkIO3.SetCheck(1);
// 	}
// 	else if(m_struLampExternal.struLampStateCtrl.dwIONo == (dwIONo1 | dwIONo2 | dwIONo3))
// 	{
// 		m_checkIO1.SetCheck(1);
// 		m_checkIO2.SetCheck(1);
// 		m_checkIO3.SetCheck(1);
// 	}
}

void CDlgTsSeries::OnBtnSetCompelCapture() 
{
	// TODO: Add your control notification handler code here
	m_struCompelCapTure.dwSize = sizeof(NET_DVR_COMPEL_CAPTURE);
	m_struCompelCapTure.byParkIndex = m_comParkIndex.GetCurSel();

	char szLan[128] = {0};
	if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_ITS_SET_COMPEL_CAPTURE, m_lChannel, &m_struCompelCapTure, sizeof(m_struCompelCapTure)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_ITS_SET_COMPEL_CAPTURE Failed!");
		g_StringLanType(szLan, "设置车位强制抓图失败", "Failed to set the entrance parameters");
		AfxMessageBox(szLan);
		//return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_ITS_SET_COMPEL_CAPTURE Succ!");
		g_StringLanType(szLan, "设置车位强制抓图成功", "Succ to set the entrance parameters");
		AfxMessageBox(szLan);
	}
}

void CDlgTsSeries::OnBtnSetCustominfo() 
{
	// TODO: Add your control notification handler code here
// 	CString strInfo;
// 	m_struCustomInfo.dwSize = sizeof(NET_DVR_CUSTOMINFO_CFG);
// 	GetDlgItem(IDC_EDIT_CUSTOMINFO)->GetWindowText(strInfo);
// 	memset(m_struCustomInfo.byCustomInfo, 0, sizeof(m_struCustomInfo.byCustomInfo));
// 	memcpy(m_struCustomInfo.byCustomInfo, strInfo, strInfo.GetLength());
// 	char szLan[128] = {0};
// 	if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_ITS_SET_CUSTOMINFO_CFG, m_lChannel, &m_struCustomInfo, sizeof(m_struCustomInfo)))
// 	{
// 		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_ITS_SET_CUSTOMINFO_CFG Failed!");
// 		g_StringLanType(szLan, "设置自定义信息失败", "Failed to set the entrance parameters");
// 		AfxMessageBox(szLan);
// 		//return;
// 	}
// 	else
// 	{
// 		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_ITS_SET_CUSTOMINFO_CFG Succ!");
// 		g_StringLanType(szLan, "设置自定义信息成功", "Succ to set the entrance parameters");
// 		AfxMessageBox(szLan);
// 	}
}

void CDlgTsSeries::OnBtnGetCustominfo() 
{
	// TODO: Add your control notification handler code here
// 	UpdateData(TRUE);
// 	CString strInfo;
// 	DWORD dwRet = 0;
// 	char szLan[128] = {0};
// 	memset(&m_struCustomInfo, 0, sizeof(m_struCustomInfo));
// 	
// 	if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_ITS_GET_CUSTOMINFO_CFG, m_lChannel, &m_struCustomInfo, sizeof(m_struCustomInfo), &dwRet))
// 	{
// 		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_ITS_GET_CUSTOMINFO_CFG Failed!");
// 		g_StringLanType(szLan, "获取自定义信息失败", "Failed to get the entrance parameters");
// 		AfxMessageBox(szLan);
// 		//return;
// 	}
// 	else
// 	{
// 		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_ITS_GET_CUSTOMINFO_CFG Succ!");
// 		g_StringLanType(szLan, "获取自定义信息成功", "Succ to set the entrance parameters");
// 		AfxMessageBox(szLan);
// 	}
// 
// 	strInfo = _T("");
// 	strInfo.Format(_T("%s"), m_struCustomInfo.byCustomInfo);
// 	GetDlgItem(IDC_EDIT_CUSTOMINFO)->SetWindowText(strInfo);
}

void CDlgTsSeries::OnSelchangeComboLedDev() //2013-11-19
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iItem = m_cmbGateLane.GetCurSel();
	m_byLedIndex = m_strITSGateLaneCfg[iItem].byLedRelativeIndex[m_comLEDDev.GetCurSel()];
	UpdateData(FALSE);
}

void CDlgTsSeries::OnSelchangeComboParklamp() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iItem = m_comParkingLamp.GetCurSel();
	m_comRelateParkingLamp.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struParkLampCtrlMode[iItem].byLampType);
	m_comParkStatus.SetCurSel(0);//
	
	m_comEnable.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struParkLampCtrlMode[iItem].struLampInfo[0].byEnable);
	m_comFlicker.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struParkLampCtrlMode[iItem].struLampInfo[0].byFlicker);
	m_comLampColor.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struParkLampCtrlMode[iItem].struLampInfo[0].byLampColor);

	UpdateData(FALSE);
}

void CDlgTsSeries::OnSelchangeComboParkingstate() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    if (MIXLAMP_CTRL_MODE == m_comLampCtrlMode.GetCurSel() + 1)
    {
        if (m_comMixLampMode.GetCurSel() == 0)
        {
            m_comRelateParkingLamp.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struExternalParkLamp[m_comParkNum.GetCurSel()].byLampType);
            m_comEnable.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struExternalParkLamp[m_comParkNum.GetCurSel()].struLampParam[m_comParkStatus.GetCurSel()].byEnable);
            m_comFlicker.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struExternalParkLamp[m_comParkNum.GetCurSel()].struLampParam[m_comParkStatus.GetCurSel()].byFlicker);
            m_comLampColor.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struExternalParkLamp[m_comParkNum.GetCurSel()].struLampParam[m_comParkStatus.GetCurSel()].byLampColor);   
        } 
        else if(m_comMixLampMode.GetCurSel() == 1)
        {
            m_comEnable.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struBuiltInParkLamp[m_comParkStatus.GetCurSel()].byEnable);
            m_comFlicker.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struBuiltInParkLamp[m_comParkStatus.GetCurSel()].byFlicker);
            m_comLampColor.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struBuiltInParkLamp[m_comParkStatus.GetCurSel()].byLampColor);
        }
    } 
    else
    {

	    int iParkingLampItem = m_comParkingLamp.GetCurSel();
	    int iParkStatusItem = m_comParkingStatus.GetCurSel();

	    m_comEnable.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struParkLampCtrlMode[iParkingLampItem].struLampInfo[iParkStatusItem].byEnable);
	    m_comFlicker.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struParkLampCtrlMode[iParkingLampItem].struLampInfo[iParkStatusItem].byFlicker);
	    m_comLampColor.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struParkLampCtrlMode[iParkingLampItem].struLampInfo[iParkStatusItem].byLampColor);
    }
	UpdateData(FALSE);
}

void CDlgTsSeries::OnBtnGetstatus() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	DWORD dwStatus = 0;
	char szLicense[32] = {0};
	char szParkingNo[32] = {0};
	NET_DVR_PARKLAMP_COND strParkingLampCond = {0};
	strParkingLampCond.dwSize = sizeof(strParkingLampCond);
	strParkingLampCond.dwChannel = m_lChannel;
	strParkingLampCond.byParkingIndex = m_comRelateLaneNo.GetCurSel()+1;

	NET_DVR_PARKLAMP_INFOCFG strParkingLampInfoCfg = {0};
	strParkingLampInfoCfg.dwSize = sizeof(strParkingLampInfoCfg);

	if (!NET_DVR_GetDeviceStatus(m_lLoginID, NET_DVR_GET_PARKLAMP_STATE, 1, &strParkingLampCond, \
		sizeof(strParkingLampCond), &dwStatus, &strParkingLampInfoCfg, sizeof(strParkingLampInfoCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetDeviceStatus NET_DVR_GET_PARKLAMP_STATE");
		g_StringLanType(szLan, "获取停车场信号灯状态失败!", "Get Parking Lamp Status Err!");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetDeviceStatus NET_DVR_GET_PARKLAMP_STATE");
		g_StringLanType(szLan, "获取停车场信号灯状态成功!", "Get Parking Lamp Status Succ!");
		AfxMessageBox(szLan);
	}

	m_comFlickerStatus.SetCurSel(strParkingLampInfoCfg.byLampFlicker);
	m_comLampColorStatus.SetCurSel(strParkingLampInfoCfg.byLampColor);
	//m_comParkStatus.SetCurSel(strParkingLampInfoCfg.byStatus);
	m_comParkingStatus2.SetCurSel(strParkingLampInfoCfg.byStatus);
	m_comCarColor.SetCurSel(strParkingLampInfoCfg.byColor);
	m_comCarColorDeep.SetCurSel(strParkingLampInfoCfg.byColorDepth);
	m_comVehicleLogoRecog.SetCurSel(strParkingLampInfoCfg.byVehicleLogoRecog);

	strncpy(szLicense, (char*)strParkingLampInfoCfg.sLicense, sizeof(strParkingLampInfoCfg.sLicense));
	strncpy(szParkingNo, (char*)strParkingLampInfoCfg.sParkingNo, sizeof(strParkingLampInfoCfg.sParkingNo));

	m_csLicense = szLicense;
	m_csParkingNo = szParkingNo;

	UpdateData(FALSE);
}

void CDlgTsSeries::MixlampModeStatusAndValue(int LampType)
{
    m_comMixLampMode.EnableWindow(TRUE);
    if (0 == LampType)//外置灯
    {     
        m_comMixLampMode.SetCurSel(0);
        m_comParkNum.SetCurSel(0);
        //m_comParkStatus.SetCurSel(0);
        m_comParkingStatus.SetCurSel(0);
        m_comRelateParkingLamp.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struExternalParkLamp[0].byLampType);
        m_comEnable.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struExternalParkLamp[0].struLampParam[0].byEnable);
        m_comFlicker.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struExternalParkLamp[0].struLampParam[0].byFlicker);
        m_comLampColor.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struExternalParkLamp[0].struLampParam[0].byLampColor);       
    } 
    else if(1 == LampType)//内置灯
    {
        m_comMixLampMode.SetCurSel(1);
        //m_comParkStatus.SetCurSel(0);
        m_comParkingStatus.SetCurSel(0);
        m_comEnable.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struBuiltInParkLamp[0].byEnable);
        m_comFlicker.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struBuiltInParkLamp[0].byFlicker);
        m_comLampColor.SetCurSel(m_struLampCtrlInfo.uLampCtrlMode.struMixLampCtrlMode.struBuiltInParkLamp[0].byLampColor);
    }

    OnSelchangeComboMixlampmode();
    UpdateData(FALSE);
}

void CDlgTsSeries::SinglelampModeStatus()
{
    m_comParkNum.EnableWindow(FALSE);
    m_comParkInfo.EnableWindow(FALSE);
    m_comIOSTate.EnableWindow(FALSE);
    m_comParkStatus.EnableWindow(FALSE);
    m_comParkingLamp.EnableWindow(FALSE);
    m_comRelateParkingLamp.EnableWindow(FALSE);
    m_comEnable.EnableWindow(FALSE);
    m_comFlicker.EnableWindow(FALSE);
    m_comParkingStatus.EnableWindow(FALSE);
    m_comMixLampMode.EnableWindow(FALSE);
    
    m_comEnable.EnableWindow(TRUE);
    m_comFlicker.EnableWindow(TRUE);
    m_comLampColor.EnableWindow(TRUE);
    m_comParkNum.EnableWindow(TRUE);
    m_comRelateParkingLamp.EnableWindow(TRUE);
    //m_comParkingStatus.EnableWindow(TRUE);
}
    
void CDlgTsSeries::OnSelchangeComboMixlampmode() 
{
	// TODO: Add your control notification handler code here
	if (m_comMixLampMode.GetCurSel() == 0)
	{
        m_comParkNum.EnableWindow(FALSE);
        m_comParkInfo.EnableWindow(FALSE);
        m_comIOSTate.EnableWindow(FALSE);
        m_comParkStatus.EnableWindow(FALSE);
        m_comParkingLamp.EnableWindow(FALSE);
        m_comRelateParkingLamp.EnableWindow(FALSE);
        m_comEnable.EnableWindow(FALSE);
        m_comFlicker.EnableWindow(FALSE);
        m_comParkingStatus.EnableWindow(FALSE);
        
        m_comEnable.EnableWindow(TRUE);
        m_comFlicker.EnableWindow(TRUE);
        m_comLampColor.EnableWindow(TRUE);
        m_comParkNum.EnableWindow(TRUE);
        m_comRelateParkingLamp.EnableWindow(TRUE);
        m_comParkingStatus.EnableWindow(TRUE); 

	} 
	else if(m_comMixLampMode.GetCurSel() == 1)
	{
        m_comParkNum.EnableWindow(FALSE);
        m_comParkInfo.EnableWindow(FALSE);
        m_comIOSTate.EnableWindow(FALSE);
        m_comParkStatus.EnableWindow(FALSE);
        m_comParkingLamp.EnableWindow(FALSE);
        m_comRelateParkingLamp.EnableWindow(FALSE);
        m_comEnable.EnableWindow(FALSE);
        m_comFlicker.EnableWindow(FALSE);
        m_comParkingStatus.EnableWindow(FALSE);

        m_comEnable.EnableWindow(TRUE);
        m_comFlicker.EnableWindow(TRUE);
        m_comLampColor.EnableWindow(TRUE);
        m_comParkStatus.EnableWindow(TRUE);
	}

    UpdateData(FALSE);
}




//清除临时卡
void CDlgTsSeries::OnBtnDelTemporaryCard() 
{
	// TODO: Add your control notification handler code here
	//将控件内容保存到变量中
	UpdateData(TRUE);
	NET_DVR_PARKING_CARD_CTRL_PARAM struCardCtrlParam = {0};
	struCardCtrlParam.dwSize = sizeof(NET_DVR_PARKING_CARD_CTRL_PARAM);
	struCardCtrlParam.dwChannel = m_lChannel;
	struCardCtrlParam.byCardType = m_comCardType.GetCurSel();
	if (1 == m_checkDelAllCard.GetCheck())
	{
		struCardCtrlParam.byDeleteALL = 1;
	}
	
	//
	NET_DVR_STD_CONTROL struStdControl = {0};
	struStdControl.lpCondBuffer = &struCardCtrlParam;
	struStdControl.dwCondSize = sizeof(NET_DVR_PARKING_CARD_CTRL_PARAM);
	memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
	struStdControl.lpStatusBuffer = m_szStatusBuf;
	struStdControl.dwStatusSize = ISAPI_STATUS_LEN;
	if (!NET_DVR_STDControl(m_lLoginID, NET_DVR_PARKING_CARD_CTRL, &struStdControl))
	{
		OutputDebugString(m_szStatusBuf);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_PARKING_CARD_CTRL");
	}
	else
	{
		OutputDebugString(m_szStatusBuf);
		g_pMainDlg->AddLog(m_iDeviceIndex,  OPERATION_SUCC_T, "NET_DVR_PARKING_CARD_CTRL");
	}
}

void CALLBACK CardSendCB(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
	char szLan[128] = {0};
	
	if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
	{
		DWORD dwStatus = *(DWORD *)lpBuffer;
		if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
		{
			AfxMessageBox("设备发送信息成功");
		}
		else if(dwStatus == NET_SDK_CALLBACK_STATUS_PROCESSING)
		{
			AfxMessageBox("设备发送信息处理中");	
		}
		else if(dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
		{
			char* pBuf = new char[dwBufLen]; 
			memcpy(pBuf, /*(char*)*/lpBuffer, dwBufLen);
			char* pBufTemp = pBuf;
			pBufTemp += 4;
			for (int i = 0; i < (dwBufLen-4)/4; i++)
			{
				if (*(DWORD*)(pBufTemp) != 0)
				{
					sprintf(szLan, "第 %d 组数据的错误码是: %d", i+1, *(DWORD*)(pBufTemp));
					AfxMessageBox(szLan);
				}
				pBufTemp += 4;
			}
		}
		else if(dwStatus == NET_SDK_CALLBACK_STATUS_EXCEPTION)
		{
			AfxMessageBox("设备返回异常");	
		}
	}
	return;
}
void CDlgTsSeries::OnBtnCreateLink() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	if (m_lCardSendHandle >= 0)
	{
		g_StringLanType(szLan, "已经建立连接", "Has already been created Link");
		AfxMessageBox(szLan);
		return;
	}
	
	m_lCardSendHandle = NET_DVR_StartRemoteConfig(m_lLoginID, NET_DVR_PARKING_CARD_SEND, NULL, 0, CardSendCB, this);
	if (m_lCardSendHandle < 0)
	{
		g_StringLanType(szLan, "临时卡数据下发连接失败", "The temporary card to send the data connection failed");
		sprintf(szLan, "%s 错误码:%d", szLan, NET_DVR_GetLastError());
		AfxMessageBox(szLan);
		return;
	}

	GetDlgItem(IDC_BTN_CREATE_LINK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_TEMPORARY_CARD_SEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_STOP_SEND)->EnableWindow(TRUE);
}

void CDlgTsSeries::OnBtnTemporaryCardSend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	if (m_lCardSendHandle < 0)
	{
		g_StringLanType(szLan, "建立连接失败", " Create Link Failed");
		AfxMessageBox(szLan);
		return;
	}
	//为结构体赋值
	NET_DVR_PARKING_CARD struParkingCard = {0};
	struParkingCard.dwSize = sizeof(NET_DVR_PARKING_CARD);
    struParkingCard.dwChannel = m_lChannel;
	memcpy(struParkingCard.szCardNo, m_strCardNo, MAX_CARDNO_LEN);
	struParkingCard.byCardType = m_comParkingCardType.GetCurSel();
    struParkingCard.byCardStatus = m_comCardStatus.GetCurSel();
    struParkingCard.byChargeRuleID = m_byChargeRuleID;
	if (m_checkDelCard.GetCheck() == 1)
	{
		struParkingCard.byDelete = 1;
	}
    struParkingCard.struStartTime.wYear = m_startDate.GetYear();
    struParkingCard.struStartTime.byMonth = m_startDate.GetMonth();
    struParkingCard.struStartTime.byDay = m_startDate.GetDay();
    struParkingCard.struStartTime.byHour = m_startTime.GetHour();
    struParkingCard.struStartTime.byMinute = m_startTime.GetMinute();
    struParkingCard.struStartTime.bySecond = m_startTime.GetSecond();
    
    struParkingCard.struEndTime.wYear = m_stopDate.GetYear();
    struParkingCard.struEndTime.byMonth = m_stopDate.GetMonth();
    struParkingCard.struEndTime.byDay = m_stopDate.GetDay();
    struParkingCard.struEndTime.byHour = m_stopTime.GetHour();
    struParkingCard.struEndTime.byMinute = m_stopTime.GetMinute();
	struParkingCard.struEndTime.bySecond = m_stopTime.GetSecond();

	//调用发送接口
	if (!NET_DVR_SendRemoteConfig(m_lCardSendHandle, ENUM_TME_CARD_SEND_DATA, (char*)&struParkingCard, sizeof(NET_DVR_PARKING_CARD)))
	{
		g_StringLanType(szLan, "临时卡数据下发失败", "The temporary card to send the data  failed");
		sprintf(szLan, "%s 错误码:%d", szLan, NET_DVR_GetLastError());
		AfxMessageBox(szLan);
		return;
	}
	
	GetDlgItem(IDC_BTN_CREATE_LINK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_TEMPORARY_CARD_SEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_STOP_SEND)->EnableWindow(TRUE);

	UpdateData(FALSE);
}

void CDlgTsSeries::OnBtnStopSend() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	if (m_lCardSendHandle < 0)
	{
		return;
	}
	
	if ( !NET_DVR_StopRemoteConfig(m_lCardSendHandle))
	{
		g_StringLanType(szLan, "卡数据下发停止失败", "The card to send the data stop failed");
		sprintf(szLan, "%s 错误码:%d", szLan, NET_DVR_GetLastError());
		AfxMessageBox(szLan);
		return;
	}
	
	m_lCardSendHandle = -1;
	GetDlgItem(IDC_BTN_CREATE_LINK)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_TEMPORARY_CARD_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_STOP_SEND)->EnableWindow(FALSE);
	
}

void CDlgTsSeries::OnBtnGateCtrl() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char szLan[128] = {0};
    NET_DVR_BARRIERGATE_CFG struGateCFG = {0};
    struGateCFG.dwSize = sizeof(NET_DVR_BARRIERGATE_CFG);
    struGateCFG.dwChannel = 1;
    struGateCFG.byLaneNo = m_comLaneNo.GetCurSel() + 1;
    struGateCFG.byBarrierGateCtrl = m_comGateCtrl.GetCurSel();
    struGateCFG.byEntranceNo = m_comEntranceNo.GetCurSel() + 1;
    struGateCFG.byUnlock = m_byUnLock;

    if (!NET_DVR_RemoteControl(m_lLoginID, NET_DVR_BARRIERGATE_CTRL, &struGateCFG, sizeof(NET_DVR_BARRIERGATE_CFG)))
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_BARRIERGATE_CTRL"); 
		return;
    }
	else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_BARRIERGATE_CTRL"); 
        return;
    }
    
    
	UpdateData(FALSE);
}

void CALLBACK VehicleSendCB(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    char szLan[128] = {0};
    
    if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
        DWORD dwStatus = *(DWORD *)lpBuffer;
        if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            AfxMessageBox("设备发送信息成功");
        }
        else if(dwStatus == NET_SDK_CALLBACK_STATUS_PROCESSING)
        {
            AfxMessageBox("设备发送信息处理中");	
        }
        else if(dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
        {
            char* pBuf = new char[dwBufLen]; 
            memcpy(pBuf, /*(char*)*/lpBuffer, dwBufLen);
            char* pBufTemp = pBuf;
            pBufTemp += 4;
            for (int i = 0; i < (dwBufLen-4)/4; i++)
            {
                if (*(DWORD*)(pBufTemp) != 0)
                {
                    sprintf(szLan, "第 %d 组数据的错误码是: %d", i+1, *(DWORD*)(pBufTemp));
                    AfxMessageBox(szLan);
                }
                pBufTemp += 4;
            }
        }
        else if(dwStatus == NET_SDK_CALLBACK_STATUS_EXCEPTION)
        {
            AfxMessageBox("设备返回异常");	
        }
    }
    return;
}

void CDlgTsSeries::OnBtnVehicleCreateLinkVehicle() 
{
	// TODO: Add your control notification handler code here
    char szLan[128] = {0};
    if (m_lVehicleSendHandle >= 0)
    {
        g_StringLanType(szLan, "已经建立连接", "Has already been created Link");
        AfxMessageBox(szLan);
        return;
    }
    
    m_lVehicleSendHandle = NET_DVR_StartRemoteConfig(m_lLoginID, NET_DVR_PARKING_VEHICLE_SEND, NULL, 0, VehicleSendCB, this);
    if (m_lVehicleSendHandle < 0)
    {
        g_StringLanType(szLan, "车辆数据下发连接失败", "The vehicle info to send the data connection failed");
        sprintf(szLan, "%s 错误码:%d", szLan, NET_DVR_GetLastError());
        AfxMessageBox(szLan);
        return;
    }
    
    GetDlgItem(IDC_BTN_VEHICLE_CREATE_LINK_VEHICLE)->EnableWindow(FALSE);
    GetDlgItem(IDC_BTN_TEMPORARY_VEHICLE_SEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_VEHICLE_STOP_SEND)->EnableWindow(TRUE);
}

void CDlgTsSeries::OnBtnTemporaryVehicleSend() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char szLan[128] = {0};
    if (m_lVehicleSendHandle < 0)
    {
        g_StringLanType(szLan, "建立连接失败", " Create Link Failed");
        AfxMessageBox(szLan);
        return;
    }
    //为结构体赋值
    NET_DVR_PARKING_VEHICLE struParkingVehicle = {0};
    struParkingVehicle.dwSize = sizeof(NET_DVR_PARKING_VEHICLE);
    struParkingVehicle.dwChannel = m_lChannel;
    memcpy(struParkingVehicle.szLicense, m_csVehicleLicense, MAX_LICENSE_LEN);
    memcpy(struParkingVehicle.szRelateCardNo, m_csRelateCardNo, MAX_CARDNO_LEN);
    struParkingVehicle.byVehicleType = m_comVehicleType.GetCurSel();
    if(6 == m_comPlateColor.GetCurSel())
    {
        struParkingVehicle.byPlateColor = 0xff;
    }
    else
    {
        struParkingVehicle.byPlateColor = m_comPlateColor.GetCurSel();
    }
    

    struParkingVehicle.struStartTime.wYear = m_startDate2.GetYear();
    struParkingVehicle.struStartTime.byMonth = m_startDate2.GetMonth();
    struParkingVehicle.struStartTime.byDay = m_startDate2.GetDay();
    struParkingVehicle.struStartTime.byHour = m_startTime2.GetHour();
    struParkingVehicle.struStartTime.byMinute = m_startTime2.GetMinute();
    struParkingVehicle.struStartTime.bySecond = m_startTime2.GetSecond();
    
    struParkingVehicle.struEndTime.wYear = m_stopDate2.GetYear();
    struParkingVehicle.struEndTime.byMonth = m_stopDate2.GetMonth();
    struParkingVehicle.struEndTime.byDay = m_stopDate2.GetDay();
    struParkingVehicle.struEndTime.byHour = m_stopTime2.GetHour();
    struParkingVehicle.struEndTime.byMinute = m_stopTime2.GetMinute();
	struParkingVehicle.struEndTime.bySecond = m_stopTime2.GetSecond();
    
    //调用发送接口
    if (!NET_DVR_SendRemoteConfig(m_lVehicleSendHandle, ENUM_TME_VEHICLE_SEND_DATA, (char*)&struParkingVehicle, sizeof(NET_DVR_PARKING_VEHICLE)))
    {
        g_StringLanType(szLan, "车辆数据下发失败", "Vehicle to send the data  failed");
        sprintf(szLan, "%s 错误码:%d", szLan, NET_DVR_GetLastError());
        AfxMessageBox(szLan);
        return;
    }
    
    GetDlgItem(IDC_BTN_VEHICLE_CREATE_LINK_VEHICLE)->EnableWindow(FALSE);
    GetDlgItem(IDC_BTN_TEMPORARY_VEHICLE_SEND)->EnableWindow(TRUE);
    GetDlgItem(IDC_BTN_VEHICLE_STOP_SEND)->EnableWindow(TRUE);
    
	UpdateData(FALSE);
}

void CDlgTsSeries::OnBtnVehicleStopSend() 
{
	// TODO: Add your control notification handler code here
    char szLan[128] = {0};
    if (m_lVehicleSendHandle < 0)
    {
        return;
    }
    
    if ( !NET_DVR_StopRemoteConfig(m_lVehicleSendHandle))
    {
        g_StringLanType(szLan, "车辆数据下发停止失败", "The Vehicle to send the data stop failed");
        sprintf(szLan, "%s 错误码:%d", szLan, NET_DVR_GetLastError());
        AfxMessageBox(szLan);
        return;
    }
    
    m_lVehicleSendHandle = -1;
    GetDlgItem(IDC_BTN_VEHICLE_CREATE_LINK_VEHICLE)->EnableWindow(TRUE);
    GetDlgItem(IDC_BTN_TEMPORARY_VEHICLE_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_VEHICLE_STOP_SEND)->EnableWindow(FALSE);
}

void CDlgTsSeries::OnBtnItcIoin() 
{
	// TODO: Add your control notification handler code here
	CDlgITCIOinCfg dlg;
    dlg.m_lServerID = m_lLoginID;
    dlg.DoModal();
}

void CDlgTsSeries::OnBtnTmeCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgTmeCfg dlg;
    dlg.m_lLoginID = m_lLoginID;
    dlg.m_lChannel = m_lChannel;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
}

void CDlgTsSeries::OnBtnSetParkingDatastate() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_PARKING_DATASTATE_INFO struParkingDataState = {0};
    struParkingDataState.dwSize = sizeof(NET_DVR_PARKING_DATASTATE_INFO);
    memcpy(struParkingDataState.szAppSerialNum,  m_csAppSerialNum.GetBuffer(0), m_csAppSerialNum.GetLength());
    struParkingDataState.dwParkingNum = m_dwParkingNum;
    struParkingDataState.dwUpdataSerialNum = m_dwUpdataSerialNum;
    
    if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_PARKING_DATASTATE, m_lChannel, &struParkingDataState, sizeof(struParkingDataState)))
    {
     	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_PARKING_DATASTATE Failed!");

     	//return;
    }
    else
    {
     	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PARKING_DATASTATE Succ!");
 	}
}

void CDlgTsSeries::OnBtnGetParkingDatastate() 
{
	// TODO: Add your control notification handler code here
    DWORD dwReturned = 0;
    NET_DVR_PARKING_DATASTATE_INFO struParkingDataState = {0};
    struParkingDataState.dwSize = sizeof(NET_DVR_PARKING_DATASTATE_INFO);

    
    if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_PARKING_DATASTATE, m_lChannel, &struParkingDataState, sizeof(struParkingDataState), &dwReturned))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PARKING_DATASTATE Failed!");
        
        //return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_PARKING_DATASTATE Succ!");
 	}

    m_csAppSerialNum.Format(_T("%s"), struParkingDataState.szAppSerialNum);
    m_dwParkingNum = struParkingDataState.dwParkingNum;
    m_dwUpdataSerialNum = struParkingDataState.dwUpdataSerialNum ;
    UpdateData(FALSE);
}
