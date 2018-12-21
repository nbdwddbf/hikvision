// DlgIPCSpecial.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgIPCSpecial.h"
#include "DlgIPAddrFilterCfg.h"
#include "DlgUploadLogo.h"
#include "DlgPTZTasks.h"
#include "DlgVcaForensicsModeCfg.h"
#include "DrawFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIPCSpecial dialog
void CALLBACK fFishEyeRemoteConfigCallback(
										   DWORD  dwType,
										   void   *lpBuffer,
										   DWORD  dwBufLen,
										   void   *pUserData
);

void CALLBACK g_DrawManualtRace(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
 	CDlgIPCSpecial* pDlg = (CDlgIPCSpecial*)dwUser;

 	if (pDlg != NULL)
 	{
 		pDlg->DrawVcaRect(hDc);
 	}
	
};



CDlgIPCSpecial::CDlgIPCSpecial(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIPCSpecial::IDD, pParent)
    , m_fX(0)
    , m_fY(0)
    , m_fZ(0)
{
	//{{AFX_DATA_INIT(CDlgIPCSpecial)
	m_dwDeadPixelX = 0;
	m_dwDeadPixelY = 0;
	m_dwDelayTime = 0;
	m_byWirelessIndex = 0;
	m_bChkMonitorAlarm = FALSE;
	m_bChkAudioAlarm = FALSE;
	m_bChkReportCenter = FALSE;
	m_bChkInvokeAlarmOut = FALSE;
	m_bChkInvokeJpegCapture = FALSE;
	m_bChkPicFtp = FALSE;
	m_bChkHanleAlarm = FALSE;
	m_bChkRecordEn = FALSE;
	m_csAlarmName = _T("");
	m_bChkWirelessLight = FALSE;
	m_bChkWpsEn = FALSE;
	m_csAPPin = _T("");
	m_csDevPin = _T("");
	m_csWpsEssid = _T("");
	m_dwFEChannelNum = 0;
	m_dwCruiseChannelNum = 0;
	m_iPresetNum = 0;
	m_iPtzCruiseNum = 0;
	m_iPresetGroupNum = 0;
	m_iPreCruiseGroupNum = 0;
	m_iPresetGetGroupNum = 0;
	m_iPreGetCruiseGroupNum = 0;
	m_byWirelessID = 0;
	m_iHour11 = 0;
	m_iHour12 = 0;
	m_iHour21 = 0;
	m_iHour22 = 0;
	m_iHour31 = 0;
	m_iHour32 = 0;
	m_iHour41 = 0;
	m_iHour42 = 0;
	m_iHour51 = 0;
	m_iHour52 = 0;
	m_iHour61 = 0;
	m_iHour62 = 0;
	m_iHour71 = 0;
	m_iHour72 = 0;
	m_iHour81 = 0;
	m_iHour82 = 0;
	m_iMin11 = 0;
	m_iMin12 = 0;
	m_iMin21 = 0;
	m_iMin22 = 0;
	m_iMin31 = 0;
	m_iMin32 = 0;
	m_iMin41 = 0;
	m_iMin42 = 0;
	m_iMin51 = 0;
	m_iMin52 = 0;
	m_iMin61 = 0;
	m_iMin62 = 0;
	m_iMin71 = 0;
	m_iMin72 = 0;
	m_iMin81 = 0;
	m_iMin82 = 0;
	m_strPresetName = _T("");
	m_fPtzPosX = 0.0f;
	m_fPtzPosY = 0.0f;
	m_bRealTimeOutput = FALSE;
	m_bMobileDev = FALSE;
	m_dwSerialNo = 0;
	//}}AFX_DATA_INIT
	m_lServerID = -1;
    m_iDevIndex = -1;
	m_lChannel = -1;
	m_lPlayHandle = -1;
	m_iPtzPresetNum = 0;
	dwChoosePtzindexNum = 0;
	m_bMouseMove = FALSE;
	memset(&m_rcWnd, 0, sizeof(m_rcWnd));
	memset(&m_bAlarmOut[0], 0, sizeof(BOOL)*MAX_ALARMOUT_V30);
	memset(&m_struAuxAlarm, 0, sizeof(m_struAuxAlarm));
	memset(&m_struPoint,0,sizeof(m_struPoint));

	memset(m_struPresetName,0,sizeof(NET_DVR_PRESET_NAME)*MAX_PRESET_NUM);
	memset(&m_struVcaRect, 0, sizeof(NET_VCA_RECT));
	
	m_strPresetName = "";

	m_bDragFishEyePTZ   = FALSE;
	m_lFishEyeCfgHandle = -1;
}


void CDlgIPCSpecial::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIPCSpecial)
	DDX_Control(pDX, IDC_COMBO_REALTIME_OUTPUT, m_comboRealTimeOutput);
	DDX_Control(pDX, IDC_LIST_FISHEYE_CALLBACK, m_listFishEyeCallback);
	DDX_Control(pDX, IDC_COMBO_PTZCHANNEL, m_comboPtzChannel);
	DDX_Control(pDX, IDC_COMBO_STREAMMODE, m_comboStreamMode);
	DDX_Control(pDX, IDC_COMBO_TRACKTYPE, m_comboTrackType);
	DDX_Control(pDX, IDC_COMBO_PTZPRESETNO, m_comboPresetNo);
	DDX_Control(pDX, IDC_STATIC_NOTE, m_staNote);
	DDX_Control(pDX, IDC_COMBO_ALARMIN_WEEKDAY, m_comboWeekday);
	DDX_Control(pDX, IDC_COMBO_MOTION_TRACK_GET, m_comboMotionTrackGet);
	DDX_Control(pDX, IDC_COMBO_MOTION_TRACK_SET, m_comboMotionTrackSet);
	DDX_Control(pDX, IDC_LIST_PRECRUISE_INFO, m_listGetPreCruiseiInfo);
	DDX_Control(pDX, IDC_LIST_PRESET_INFO2, m_listGetPresetInfo);
	DDX_Control(pDX, IDC_COMBO_FISH_EYE_MOUNT_TYPE, m_comboFishEyeMountType);
	DDX_Control(pDX, IDC_COMBO_FISH_EYE_CONNECT_MODE, m_comboFishEyeConnectMode);
	DDX_Control(pDX, IDC_COMBO_WPS_CONNECT_TYPE, m_comboWpsConType);
	DDX_Control(pDX, IDC_COMBO_WIRELESS_ALARM_ID, m_comboWirelessId);
	DDX_Control(pDX, IDC_COMBO_AUXALARM_TYPE, m_comboAuxAlarmType);
	DDX_Control(pDX, IDC_COMBO_AUX_ALARM_ID, m_comboAuxAlarmId);
	DDX_Control(pDX, IDC_TREE_ALARM_OUT, m_treeAlarmOut);
	DDX_Control(pDX, IDC_COMBO_COMMAND, m_comboCmd);
	DDX_Text(pDX, IDC_EDIT_DEADPIXEL_X, m_dwDeadPixelX);
	DDX_Text(pDX, IDC_EDIT_DEADPIXEL_Y, m_dwDeadPixelY);
	DDX_Text(pDX, IDC_EDIT_DELAY_TIME, m_dwDelayTime);
	DDX_Text(pDX, IDC_EDIT_WIRELESS_INDEX, m_byWirelessIndex);
	DDX_Check(pDX, IDC_CHK_MONITOR_ALARM, m_bChkMonitorAlarm);
	DDX_Check(pDX, IDC_CHK_AUDIO_ALARM, m_bChkAudioAlarm);
	DDX_Check(pDX, IDC_CHK_REPORT_CENTER, m_bChkReportCenter);
	DDX_Check(pDX, IDC_CHK_INVOKE_ALARM_OUT, m_bChkInvokeAlarmOut);
	DDX_Check(pDX, IDC_CHK_INVOKE_JPEG_CAPTURE, m_bChkInvokeJpegCapture);
	DDX_Check(pDX, IDC_CHK_PIC_FTP, m_bChkPicFtp);
	DDX_Check(pDX, IDC_CHK_HANLE_ALARM, m_bChkHanleAlarm);
	DDX_Check(pDX, IDC_CHK_RECORD_EN, m_bChkRecordEn);
	DDX_Text(pDX, IDC_EDIT_ALARM_NAME, m_csAlarmName);
	DDX_Check(pDX, IDC_CHK_WIRELESS_LIGHT, m_bChkWirelessLight);
	DDX_Check(pDX, IDC_CHK_WPS_EN, m_bChkWpsEn);
	DDX_Text(pDX, IDC_EDIT_AP_PIN, m_csAPPin);
	DDX_Text(pDX, IDC_EDIT_DEV_PIN, m_csDevPin);
	DDX_Text(pDX, IDC_EDIT_WPS_ESSID, m_csWpsEssid);
	DDX_Text(pDX, IDC_EDIT_PRESET_NUM, m_iPresetNum);
	DDX_Text(pDX, IDC_EDIT_PTZCRUISE_NUM, m_iPtzCruiseNum);
	DDX_Text(pDX, IDC_EDIT_PRESET_GROUPNUM, m_iPresetGroupNum);
	DDX_Text(pDX, IDC_EDIT_PRECRUISE_GROUPNUM, m_iPreCruiseGroupNum);
	DDX_Text(pDX, IDC_EDIT_PREGET_GROUPNUM, m_iPresetGetGroupNum);
	DDX_Text(pDX, IDC_EDIT_PRECRUISEGET_GROUPNUM, m_iPreGetCruiseGroupNum);
	DDX_Text(pDX, IDC_EDIT_WIRELESS_ID, m_byWirelessID);
	DDX_Text(pDX, IDC_EDIT_HOUR11, m_iHour11);
	DDX_Text(pDX, IDC_EDIT_HOUR12, m_iHour12);
	DDX_Text(pDX, IDC_EDIT_HOUR21, m_iHour21);
	DDX_Text(pDX, IDC_EDIT_HOUR22, m_iHour22);
	DDX_Text(pDX, IDC_EDIT_HOUR31, m_iHour31);
	DDX_Text(pDX, IDC_EDIT_HOUR32, m_iHour32);
	DDX_Text(pDX, IDC_EDIT_HOUR41, m_iHour41);
	DDX_Text(pDX, IDC_EDIT_HOUR42, m_iHour42);
	DDX_Text(pDX, IDC_EDIT_HOUR51, m_iHour51);
	DDX_Text(pDX, IDC_EDIT_HOUR52, m_iHour52);
	DDX_Text(pDX, IDC_EDIT_HOUR61, m_iHour61);
	DDX_Text(pDX, IDC_EDIT_HOUR62, m_iHour62);
	DDX_Text(pDX, IDC_EDIT_HOUR71, m_iHour71);
	DDX_Text(pDX, IDC_EDIT_HOUR72, m_iHour72);
	DDX_Text(pDX, IDC_EDIT_HOUR81, m_iHour81);
	DDX_Text(pDX, IDC_EDIT_HOUR82, m_iHour82);
	DDX_Text(pDX, IDC_EDIT_MIN11, m_iMin11);
	DDX_Text(pDX, IDC_EDIT_MIN12, m_iMin12);
	DDX_Text(pDX, IDC_EDIT_MIN21, m_iMin21);
	DDX_Text(pDX, IDC_EDIT_MIN22, m_iMin22);
	DDX_Text(pDX, IDC_EDIT_MIN31, m_iMin31);
	DDX_Text(pDX, IDC_EDIT_MIN32, m_iMin32);
	DDX_Text(pDX, IDC_EDIT_MIN41, m_iMin41);
	DDX_Text(pDX, IDC_EDIT_MIN42, m_iMin42);
	DDX_Text(pDX, IDC_EDIT_MIN51, m_iMin51);
	DDX_Text(pDX, IDC_EDIT_MIN52, m_iMin52);
	DDX_Text(pDX, IDC_EDIT_MIN61, m_iMin61);
	DDX_Text(pDX, IDC_EDIT_MIN62, m_iMin62);
	DDX_Text(pDX, IDC_EDIT_MIN71, m_iMin71);
	DDX_Text(pDX, IDC_EDIT_MIN72, m_iMin72);
	DDX_Text(pDX, IDC_EDIT_MIN81, m_iMin81);
	DDX_Text(pDX, IDC_EDIT_MIN82, m_iMin82);
	DDX_Text(pDX, IDC_EDT_PRESETNAME, m_strPresetName);
	DDX_Text(pDX, IDC_EDIT_XPTZPOS, m_fPtzPosX);
	DDV_MinMaxFloat(pDX, m_fPtzPosX, 0.f, 1.f);
	DDX_Text(pDX, IDC_EDIT_YPTZPOS, m_fPtzPosY);
	DDV_MinMaxFloat(pDX, m_fPtzPosY, 0.f, 1.f);
	DDX_Check(pDX, IDC_CHECK_REALTIME_OUTPUT, m_bRealTimeOutput);
	DDX_Check(pDX, IDC_CHECK_MOBILEDEV, m_bMobileDev);
	DDX_Text(pDX, IDC_EDIT_SERIAL_NUM, m_dwSerialNo);
    DDX_Text(pDX, IDC_EDIT_X, m_fX);
    DDX_Text(pDX, IDC_EDIT_Y, m_fY);
    DDX_Text(pDX, IDC_EDIT_Z, m_fZ);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIPCSpecial, CDialog)
	//{{AFX_MSG_MAP(CDlgIPCSpecial)
	ON_BN_CLICKED(IDC_BTN_SHUTTER_COMP, OnBtnShutterComp)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_IPC_ONEPUSH_FOCUS, OnBtnIpcOnepushFocus)
	ON_BN_CLICKED(IDC_BTN_IPC_RESET_LENS, OnBtnIpcResetLens)
	ON_BN_CLICKED(IDC_BTN_REMOTECONTROL_ALARM, OnBtnRemotecontrolAlarm)
	ON_BN_CLICKED(IDC_BTN_REMOTECONTROL_DISALARM, OnBtnRemotecontrolDisalarm)
	ON_BN_CLICKED(IDC_BTN_REMOTECONTROL_STUDY, OnBtnRemotecontrolStudy)
	ON_BN_CLICKED(IDC_BTN_WIRELESS_STUDY, OnBtnWirelessStudy)
	ON_BN_CLICKED(IDC_BTN_GET_AUXALARM, OnBtnGetAuxalarm)
	ON_BN_CLICKED(IDC_BTN_SET_AUXALARM, OnBtnSetAuxalarm)
	ON_NOTIFY(NM_CLICK, IDC_TREE_ALARM_OUT, OnClickTreeAlarmOut)
	ON_BN_CLICKED(IDC_BTN_SAVE_AUX_ALARM, OnBtnSaveAuxAlarm)
	ON_CBN_SELCHANGE(IDC_COMBO_AUX_ALARM_ID, OnSelchangeComboAuxAlarmId)
	ON_CBN_SELCHANGE(IDC_COMBO_AUXALARM_TYPE, OnSelchangeComboAuxalarmType)
	ON_CBN_SELCHANGE(IDC_COMBO_WIRELESS_ALARM_ID, OnSelchangeComboWirelessAlarmId)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHK_WPS_EN, OnChkWpsEn)
	ON_BN_CLICKED(IDC_BTN_REFRESH, OnBtnRefresh)
	ON_BN_CLICKED(IDC_BTN_WPS_CONNECT, OnBtnWpsConnect)
	ON_BN_CLICKED(IDC_BTN_UPDATE_PIN, OnBtnUpdatePin)
	ON_BN_CLICKED(IDC_BTN_GET_DEV_PIN, OnBtnGetDevPin)
	ON_BN_CLICKED(IDC_BTN_FISH_EYE_SET, OnBtnFishEyeSet)
	ON_BN_CLICKED(IDC_BTN_FISH_EYE_GET, OnBtnFishEyeGet)
	ON_BN_CLICKED(IDC_BTN_GET_PRESET_NUM, OnBtnGetPresetNum)
	ON_BN_CLICKED(IDC_BTN_GET_PTZCRUISE_NUM, OnBtnGetPtzcruiseNum)
	ON_BN_CLICKED(IDC_BTN_GETPRESET_INFO, OnBtnGetpresetInfo)
	ON_BN_CLICKED(IDC_BTN_GETCRUISE_INFO, OnBtnGetcruiseInfo)
	ON_BN_CLICKED(IDC_BTN_MOTION_TRACK_SET, OnBtnMotionTrackSet)
	ON_BN_CLICKED(IDC_BTN_MOTION_TRACK_GET, OnBtnMotionTrackGet)
	ON_BN_CLICKED(IDC_BTN_IPADDR_FILTER, OnBtnIpaddrFilter)
	ON_BN_CLICKED(IDC_BTN_UPLOAD_LOGO, OnBtnUploadLogo)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARMIN_WEEKDAY, OnSelchangeComboAlarminWeekday)
	ON_BN_CLICKED(IDC_BTN_GETPRESETNAME, OnBtnGetpresetname)
	ON_CBN_SELCHANGE(IDC_COMBO_PTZPRESETNO, OnEditchangeComboPtzpresetno)
	ON_BN_CLICKED(IDC_BTN_SETPRESETNAME, OnBtnSetpresetname)
	ON_BN_CLICKED(IDC_BTN_PTZTASK, OnBtnPtztask)
	ON_BN_CLICKED(IDC_BTN_GETTRACKTYPE, OnBtnGettracktype)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
	ON_BN_CLICKED(IDC_BTN_CREATELINK, OnBtnCreatelink)
	ON_BN_CLICKED(IDC_BTN_CLOSELINK, OnBtnCloselink)
	ON_BN_CLICKED(IDC_BTN_GETSTREAMMODE, OnBtnGetStreamMode)
	ON_BN_CLICKED(IDC_BNT_GET_PTZPOS, OnBntGetPtzPos)
	ON_BN_CLICKED(IDC_BNT_SET_PTZPOS, OnBntSetPtzPos)
	ON_BN_CLICKED(IDC_BTN_SET_DEVPARAM, OnBtnSetDevparam)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_FORENSICS_MODE, OnBtnForensicsMode)
	ON_BN_CLICKED(IDC_BTN_FORCESTOP_FORENSICS, OnBtnForcestopForensics)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CDlgIPCSpecial::DrawVcaRect(HDC hdc)
{
   	DRAW_RECT_PARAM struRectParam;
	memset(&struRectParam,0,sizeof(struRectParam));
	memcpy(&struRectParam.rcWnd, &m_rcWnd, sizeof(m_rcWnd));
	struRectParam.color = RGB(255,0,0);

	NET_VCA_RECT& struVcaRect = m_struVcaRect;
	memcpy(&struRectParam.struVcaRect, &m_struVcaRect, sizeof(NET_VCA_RECT));
	
	CDrawFun::DrawVcaRect(hdc,&struRectParam);
}

/////////////////////////////////////////////////////////////////////////////
// CDlgIPCSpecial message handlers
BOOL CDlgIPCSpecial::OnInitDialog()
{
	CDialog::OnInitDialog();
	OnBtnGetAuxalarm();

	CString strTemp;

	m_comboWeekday.SetCurSel(0);

	char szLan[128] = {0};
	m_listGetPresetInfo.InsertColumn(0, "",LVCFMT_LEFT, 0, -1);
	g_StringLanType(szLan, "预置点序号", "Preset point number");
	m_listGetPresetInfo.InsertColumn(1, szLan, LVCFMT_LEFT, 90);
	g_StringLanType(szLan, "预置点x轴", "preset point x axis");
	m_listGetPresetInfo.InsertColumn(2, szLan, LVCFMT_LEFT, 90);
	g_StringLanType(szLan, "预置点y轴", "preset point y axis");
	m_listGetPresetInfo.InsertColumn(3, szLan, LVCFMT_LEFT, 100);
	m_listGetPresetInfo.SetExtendedStyle(m_listGetPresetInfo.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);

	m_listGetPreCruiseiInfo.InsertColumn(0, "",LVCFMT_LEFT, 0, -1);
	g_StringLanType(szLan, "巡航路径序号", "Cruise path serial number");
	m_listGetPreCruiseiInfo.InsertColumn(1, szLan, LVCFMT_LEFT, 50);
	g_StringLanType(szLan, "巡航点号", "Cruise Point");
	m_listGetPreCruiseiInfo.InsertColumn(2, szLan, LVCFMT_LEFT, 50);
	g_StringLanType(szLan, "预置点序号", "Preset Point");
	m_listGetPreCruiseiInfo.InsertColumn(3, szLan, LVCFMT_LEFT, 80);
	g_StringLanType(szLan, "预置点x轴", "Preset Point x axis");
	m_listGetPreCruiseiInfo.InsertColumn(4, szLan, LVCFMT_LEFT, 80);
	g_StringLanType(szLan, "预置点y轴", "Preset Point y axis");
	m_listGetPreCruiseiInfo.InsertColumn(5, szLan, LVCFMT_LEFT, 80);
	g_StringLanType(szLan, "停留时间", "Stop time");
	m_listGetPreCruiseiInfo.InsertColumn(6, szLan, LVCFMT_LEFT, 80);
	g_StringLanType(szLan, "速度", "Speed");
	m_listGetPreCruiseiInfo.InsertColumn(7, szLan, LVCFMT_LEFT, 40);

	m_listGetPreCruiseiInfo.SetExtendedStyle(m_listGetPresetInfo.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
	GetDlgItem(IDC_PLAYWND_PTZ)->GetWindowRect(&m_rcWnd);
	ScreenToClient(&m_rcWnd);
	//预览接口调用
	NET_DVR_CLIENTINFO struPlay;
	struPlay.hPlayWnd 	= GetDlgItem(IDC_PLAYWND_PTZ)->GetSafeHwnd();
	struPlay.lChannel 	= m_lChannel; 
	struPlay.lLinkMode 	= 0;
	struPlay.sMultiCastIP = "";	
	m_lPlayHandle = NET_DVR_RealPlay_V30(m_lServerID, &struPlay, NULL, NULL, TRUE);
	BOOL bRet = FALSE;
// 	if (m_lPlayHandle>=0)
// 	{
	   if (m_lPlayHandle < 0)
	   {
		   g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_RealPlay_V30");
		   AfxMessageBox("NET_DVR_RealPlay_V30 FAIL");		
	   }
	   else
	   {
		   g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_RealPlay_V30");
		   bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, g_DrawManualtRace, (DWORD)this);
	   }
 //   }	

	m_iPresetNum = 0;
	m_iPresetGroupNum = 0;
	m_dwFEChannelNum = 1;

	m_iPresetGetGroupNum = 1;
	
	m_iPreGetCruiseGroupNum = 1;

	for (int j = 0; j < MAX_PRESET_NUM/*256*/; j++)
	{
		CString str;
		str.Format("%d", j+1);
		m_comboPresetNo.AddString(str);
		m_comboPresetNo.SetItemData(j, j+1);

// 		if (j != 255)
// 		{
// 			m_comboPresetNo.SetItemData(j, j+1);
// 		}
// 		else
// 		{
// 			m_comboPresetNo.SetItemData(j, 0); //0表示第256个预置位
// 		}
	}

	m_comboPresetNo.SetCurSel(0);
    

	int iAnalogChanNum   = g_struDeviceInfo[m_iDevIndex].iAnalogChanNum;
	int iIpChanNum       = g_struDeviceInfo[m_iDevIndex].iIPChanNum;
	CString strChannelNo = "";
	int iIndex           = 0;
	int iStartChannel    = g_struDeviceInfo[m_iDevIndex].iStartChan;
	m_comboPtzChannel.ResetContent();

	for (int i = 0; i < MAX_CHANNUM_V30; i++)
	{
		
		int iChannelNO = g_struDeviceInfo[m_iDevIndex].pStruChanInfo[i].iChannelNO;
	
		
		if ((i < iAnalogChanNum) && g_struDeviceInfo[m_iDevIndex].pStruChanInfo[i].bEnable)
		{
			strChannelNo.Format(ANALOG_C_FORMAT, iChannelNO);
			m_comboPtzChannel.InsertString(iIndex,strChannelNo);
			m_comboPtzChannel.SetItemData(iIndex,iChannelNO);
			iIndex++;
		}
		else if (i >= iAnalogChanNum && g_struDeviceInfo[m_iDevIndex].pStruChanInfo[i].bEnable)
		{
			strChannelNo.Format(DIGITAL_C_FORMAT, iChannelNO - iStartChannel + 1);
			m_comboPtzChannel.InsertString(iIndex,strChannelNo);
			m_comboPtzChannel.SetItemData(iIndex,iChannelNO);
			iIndex++;
		}
	}

	UpdateData(FALSE);
	return TRUE;
}

void CDlgIPCSpecial::OnBtnShutterComp() 
{
	// TODO: Add your control notification handler code here
	if (!NET_DVR_ShutterCompensation(m_lServerID))
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_ShutterCompensation");
		return;
	}
	else
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_ShutterCompensation");
	}
}

void CDlgIPCSpecial::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_CORRECT_DEADPIXEL_PARAM struDeadPixel;
	memset(&struDeadPixel, 0, sizeof(struDeadPixel));
    struDeadPixel.dwCommand = m_comboCmd.GetCurSel();
    struDeadPixel.dwDeadPixelX = m_dwDeadPixelX;
	struDeadPixel.dwDeadPixelY = m_dwDeadPixelY;
	struDeadPixel.dwSize = sizeof(struDeadPixel);
	
	if (!NET_DVR_CorrectDeadPixel(m_lServerID, m_lChannel, &struDeadPixel))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_CorrectDeadPixel");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_CorrectDeadPixel");
	}
}

// void CDlgIPCSpecial::OnBtnFocusOnepush() 
// {
// 	// TODO: Add your control notification handler code here
// 	if (!NET_DVR_FocusOnePush(m_lServerID, m_lChannel))
// 	{
// 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_FocusOnePush");
// 		return;
// 	}
// 	else
// 	{
// 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_FocusOnePush");
// 	}
// }

// void CDlgIPCSpecial::OnBtnResetLens() 
// {
// 	// TODO: Add your control notification handler code here
// 	if (!NET_DVR_ResetLens(m_lServerID, m_lChannel))
// 	{
// 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_ResetLens");
// 		return;
// 	}
// 	else
// 	{
// 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_ResetLens");
// 	}
// }

void CDlgIPCSpecial::OnBtnIpcOnepushFocus() 
{
	// TODO: Add your control notification handler code here
 	if (!NET_DVR_FocusOnePush(m_lServerID, m_lChannel))
 	{
 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_FocusOnePush");
 		return;
 	}
 	else
 	{
 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_FocusOnePush");
 	}
}

void CDlgIPCSpecial::OnBtnIpcResetLens() 
{
	// TODO: Add your control notification handler code here
	if (!NET_DVR_ResetLens(m_lServerID, m_lChannel))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_ResetLens");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_ResetLens");
	}
}

void CDlgIPCSpecial::OnBtnRemotecontrolAlarm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_REMOTECONTROL_ALARM_PARAM struInBuf = {0};
	struInBuf.dwSize = sizeof(NET_DVR_REMOTECONTROL_ALARM_PARAM);
	struInBuf.dwChannel = 1;
	struInBuf.wDealyTime = m_dwDelayTime;
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_ALARM, &struInBuf, sizeof(struInBuf)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_ALARM");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_ALARM");
	}
}

void CDlgIPCSpecial::OnBtnRemotecontrolDisalarm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_REMOTECONTROL_ALARM_PARAM struInBuf = {0};
	struInBuf.dwSize = sizeof(NET_DVR_REMOTECONTROL_ALARM_PARAM);
	struInBuf.dwChannel = 1;
	struInBuf.wDealyTime = m_dwDelayTime;
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_DISALARM, &struInBuf, sizeof(struInBuf)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_DISALARM");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_DISALARM");
	}
}

void CDlgIPCSpecial::OnBtnRemotecontrolStudy() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_REMOTECONTROL_STUDY_PARAM struInBuf = {0};
	struInBuf.dwSize = sizeof(NET_DVR_REMOTECONTROL_STUDY_PARAM);
	struInBuf.dwChannel = 1;
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_STUDY, &struInBuf, sizeof(struInBuf)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_STUDY");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_STUDY");
	}
}

void CDlgIPCSpecial::OnBtnWirelessStudy() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_WIRELESS_ALARM_STUDY_PARAM struInBuf = {0};
	struInBuf.dwSize = sizeof(NET_DVR_WIRELESS_ALARM_STUDY_PARAM);
	struInBuf.dwChannel = 1;
	struInBuf.byIndex = m_byWirelessIndex;
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_WIRELESS_ALARM_STUDY, &struInBuf, sizeof(struInBuf)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_WIRELESS_ALARM_STUDY");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_WIRELESS_ALARM_STUDY");
	}
}

void CDlgIPCSpecial::OnBtnGetAuxalarm() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
	int i;
    m_staNote.ShowWindow(SW_SHOW);
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_IPC_GET_AUX_ALARMCFG, 1, &m_struAuxAlarm, sizeof(m_struAuxAlarm), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_IPC_GET_AUX_ALARMCFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_IPC_GET_AUX_ALARMCFG");
//        return;
    }
	m_comboAuxAlarmId.SetCurSel(0);
	m_comboWirelessId.SetCurSel(0);
	m_lWirelessID = 0;
	m_lAuxAlarmID = 0;
	m_comboAuxAlarmType.SetCurSel(m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType-1);
	if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_PIR)
	{
		m_csAlarmName.Format("%s", m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byAlarmName);
		m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byAlarmHandle;
		for (i=0; i<MAX_ALARMOUT_V30; i++)
		{
			m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.byRelAlarmOut[i];
		}
		m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byRelRecordChan[0];
		m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType &0x01;
		m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>1)&0x01;
		m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>2)&0x01;
		m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>3)&0x01;
		m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>4)&0x01;
	    m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>9)&0x01;
		m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>5)&0x01;

		m_staNote.ShowWindow(SW_HIDE);
		m_comboWeekday.SetCurSel(0);
		GetComboAlarminWeekdayData(0);
	}
	else if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_WIRELESS)
	{
		m_csAlarmName.Format("%s", m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byAlarmName);
		m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byAlarmHandle;
		m_byWirelessID = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byID;
		for (i=0; i<MAX_ALARMOUT_V30; i++)
		{
			m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.byRelAlarmOut[i];
		}
		m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byRelRecordChan[0];
		m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType &0x01;
		m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>1)&0x01;
		m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>2)&0x01;
		m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>3)&0x01;
		m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>4)&0x01;
		m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>9)&0x01;
		m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>5)&0x01;
	}
	else if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_CALLHELP)
	{
		m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.byAlarmHandle;
		for (i=0; i<MAX_ALARMOUT_V30; i++)
		{
			m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.byRelAlarmOut[i];
		}
		m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.byRelRecordChan[0];
		m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType &0x01;
		m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>1)&0x01;
		m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>2)&0x01;
		m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>3)&0x01;
		m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>4)&0x01;
		m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>9)&0x01;
		m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>5)&0x01;
	}
// 	else if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_PIR)
// 	{
// 		m_csAlarmName.Format("%s", m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.byAlarmName);
// 		m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.byAlarmHandle;
// 		for (i=0; i<MAX_ALARMOUT_V30; i++)
// 		{
// 			m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.byRelAlarmOut[i];
// 		}
// 		m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.byRelRecordChan[0];
// 		m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType &0x01;
// 		m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType>>1)&0x01;
// 		m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType>>2)&0x01;
// 		m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType>>3)&0x01;
// 		m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType>>4)&0x01;
// 		m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType>>9)&0x01;
// 		m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType>>5)&0x01;
// 
// 		m_staNote.ShowWindow(SW_HIDE);
// 		m_comboWeekday.SetCurSel(0);
// 		GetComboAlarminWeekdayData(0);
// 	}
	CreateTree();
	UpdateData(FALSE);
}

void CDlgIPCSpecial::OnBtnSetAuxalarm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (NET_DVR_SetDVRConfig(m_lServerID, NET_IPC_SET_AUX_ALARMCFG, 1, &m_struAuxAlarm, sizeof(m_struAuxAlarm)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_IPC_SET_AUX_ALARMCFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_IPC_SET_AUX_ALARMCFG");
        return;
    }
}

/*********************************************************
Function:	CreateTree
Desc:		Create alarm output-video channel connection
Input:	
Output:	
Return:	
**********************************************************/
void CDlgIPCSpecial::CreateTree(void)
{
	//m_treeAlarmOut.DeleteAllItems();
	g_CreateAlarmOutTree(m_treeAlarmOut, m_iDevIndex, m_bAlarmOut);
}

void CDlgIPCSpecial::OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult) 
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
	HTREEITEM hSelect = m_treeAlarmOut.HitTest(pt, &uFlag);
	
	if (NULL == hSelect) 
	{
		return;
	}
	m_treeAlarmOut.SelectItem(hSelect);
	DWORD dwIndex = m_treeAlarmOut.GetItemData(hSelect)%1000;
	BOOL bCheck = m_treeAlarmOut.GetCheck(hSelect);
	m_bAlarmOut[dwIndex] = !bCheck;
	
	if (uFlag != LVHT_TOLEFT)
	{
		m_treeAlarmOut.SetCheck(hSelect, !bCheck);
	}
	else
	{
		m_treeAlarmOut.SetCheck(hSelect, bCheck);
	}
	*pResult = 0;
}

void CDlgIPCSpecial::OnBtnSaveAuxAlarm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int i;
	m_lAuxAlarmID = m_comboAuxAlarmId.GetCurSel();
	m_lWirelessID = m_comboWirelessId.GetCurSel();
	m_struAuxAlarm.dwSize = sizeof(NET_IPC_AUX_ALARMCFG);
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType = m_comboAuxAlarmType.GetCurSel()+1;
	if (m_comboAuxAlarmType.GetCurSel()+1 == IPC_AUXALARM_PIR)
	{
		int j = 0;
		char szLan[1024] = {0};
		j = m_comboWeekday.GetCurSel();
		
		if ((j < 0) || (j > 6))
		{
			return;
		}
		
		if ((m_iHour11 < 0) || (m_iHour11 > 24) || (m_iHour12 < 0) || (m_iHour12 > 24) ||	\
			(m_iHour21 < 0) || (m_iHour21 > 24) || (m_iHour22 < 0) || (m_iHour22 > 24) ||	\
			(m_iHour31 < 0) || (m_iHour31 > 24) || (m_iHour32 < 0) || (m_iHour32 > 24) ||	\
			(m_iHour41 < 0) || (m_iHour41 > 24) || (m_iHour42 < 0) || (m_iHour42 > 24) ||   \
			(m_iHour51 < 0) || (m_iHour51 > 24) || (m_iHour52 < 0) || (m_iHour52 > 24) ||	\
			(m_iHour61 < 0) || (m_iHour61 > 24) || (m_iHour62 < 0) || (m_iHour62 > 24) ||	\
			(m_iHour71 < 0) || (m_iHour71 > 24) || (m_iHour72 < 0) || (m_iHour72 > 24) ||	\
			(m_iHour81 < 0) || (m_iHour81 > 24) || (m_iHour82 < 0) || (m_iHour82 > 24))
		{
			g_StringLanType(szLan, "小时范围在0 -- 24之间", "Hour between 0 - 24 ");
			AfxMessageBox(szLan);
			return;
		}
		
		if ((m_iMin11 < 0) || (m_iMin11 > 60) || (m_iMin12 < 0) || (m_iMin12 > 60) ||	\
			(m_iMin21 < 0) || (m_iMin21 > 60) || (m_iMin22 < 0) || (m_iMin22 > 60) ||	\
			(m_iMin31 < 0) || (m_iMin31 > 60) || (m_iMin32 < 0) || (m_iMin32 > 60) ||	\
			(m_iMin41 < 0) || (m_iMin41 > 60) || (m_iMin42 < 0) || (m_iMin42 > 60) ||   \
			(m_iMin51 < 0) || (m_iMin51 > 60) || (m_iMin52 < 0) || (m_iMin52 > 60) ||	\
			(m_iMin61 < 0) || (m_iMin61 > 60) || (m_iMin62 < 0) || (m_iMin62 > 60) ||	\
			(m_iMin71 < 0) || (m_iMin71 > 60) || (m_iMin72 < 0) || (m_iMin72 > 60) ||	\
			(m_iMin81 < 0) || (m_iMin81 > 60) || (m_iMin82 < 0) || (m_iMin82 > 60))
		{
			g_StringLanType(szLan, "分钟范围在0 -- 60之间", "Minute between 0 - 60 ");
			AfxMessageBox(szLan);
			return;
		}

		memcpy(m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byAlarmName, m_csAlarmName,NAME_LEN);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byAlarmHandle = m_bChkHanleAlarm;
		for (i=0; i<MAX_ALARMOUT_V30; i++)
		{
			m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.byRelAlarmOut[i] = (BYTE)m_bAlarmOut[i];
		}
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byRelRecordChan[0] = m_bChkRecordEn;
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType = 0;
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType |= (m_bChkMonitorAlarm << 0);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType |= (m_bChkAudioAlarm << 1);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType |= (m_bChkReportCenter << 2);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType |= (m_bChkInvokeAlarmOut << 3);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType |= (m_bChkInvokeJpegCapture << 4);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType |= (m_bChkWirelessLight << 5);
	    m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType |= (m_bChkPicFtp << 9);

	
		SetComboAlarminWeekdayData(j);
		
	}
	else if (m_comboAuxAlarmType.GetCurSel()+1 == IPC_AUXALARM_WIRELESS)
	{
		memcpy(m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byAlarmName, m_csAlarmName,NAME_LEN);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byAlarmHandle = m_bChkHanleAlarm;
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byID = m_byWirelessID;
		for (i=0; i<MAX_ALARMOUT_V30; i++)
		{
			m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.byRelAlarmOut[i] = (BYTE)m_bAlarmOut[i];
		}
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byRelRecordChan[0] = m_bChkRecordEn;
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType = 0;
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType |= (m_bChkMonitorAlarm << 0);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType |= (m_bChkAudioAlarm << 1);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType |= (m_bChkReportCenter << 2);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType |= (m_bChkInvokeAlarmOut << 3);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType |= (m_bChkInvokeJpegCapture << 4);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType |= (m_bChkWirelessLight << 5);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType |= (m_bChkPicFtp << 9);
	}
	else if (m_comboAuxAlarmType.GetCurSel()+1 == IPC_AUXALARM_CALLHELP)
	{
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.byAlarmHandle = m_bChkHanleAlarm;
		for (i=0; i<MAX_ALARMOUT_V30; i++)
		{
			m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.byRelAlarmOut[i] = (BYTE)m_bAlarmOut[i];
		}
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.byRelRecordChan[0] = m_bChkRecordEn;
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType = 0;
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType |= (m_bChkMonitorAlarm << 0);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType |= (m_bChkAudioAlarm << 1);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType |= (m_bChkReportCenter << 2);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType |= (m_bChkInvokeAlarmOut << 3);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType |= (m_bChkInvokeJpegCapture << 4);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType |= (m_bChkWirelessLight << 5);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType |= (m_bChkPicFtp << 9);
	}
// 	if (m_comboAuxAlarmType.GetCurSel()+1 == IPC_AUXALARM_PIR_EX)
// 	{
// 		int j = 0;
// 		char szLan[1024] = {0};
// 		j = m_comboWeekday.GetCurSel();
// 
// 		if ((j < 0) || (j > 6))
// 		{
// 			return;
// 		}
// 		
// 		if ((m_iHour11 < 0) || (m_iHour11 > 24) || (m_iHour12 < 0) || (m_iHour12 > 24) ||	\
// 			(m_iHour21 < 0) || (m_iHour21 > 24) || (m_iHour22 < 0) || (m_iHour22 > 24) ||	\
// 			(m_iHour31 < 0) || (m_iHour31 > 24) || (m_iHour32 < 0) || (m_iHour32 > 24) ||	\
// 			(m_iHour41 < 0) || (m_iHour41 > 24) || (m_iHour42 < 0) || (m_iHour42 > 24) ||   \
// 			(m_iHour51 < 0) || (m_iHour51 > 24) || (m_iHour52 < 0) || (m_iHour52 > 24) ||	\
// 			(m_iHour61 < 0) || (m_iHour61 > 24) || (m_iHour62 < 0) || (m_iHour62 > 24) ||	\
// 			(m_iHour71 < 0) || (m_iHour71 > 24) || (m_iHour72 < 0) || (m_iHour72 > 24) ||	\
// 			(m_iHour81 < 0) || (m_iHour81 > 24) || (m_iHour82 < 0) || (m_iHour82 > 24))
// 		{
// 			g_StringLanType(szLan, "小时范围在0 -- 24之间", "Hour between 0 - 24 ");
// 			AfxMessageBox(szLan);
// 			return;
// 		}
// 
// 		if ((m_iMin11 < 0) || (m_iMin11 > 60) || (m_iMin12 < 0) || (m_iMin12 > 60) ||	\
// 			(m_iMin21 < 0) || (m_iMin21 > 60) || (m_iMin22 < 0) || (m_iMin22 > 60) ||	\
// 			(m_iMin31 < 0) || (m_iMin31 > 60) || (m_iMin32 < 0) || (m_iMin32 > 60) ||	\
// 			(m_iMin41 < 0) || (m_iMin41 > 60) || (m_iMin42 < 0) || (m_iMin42 > 60) ||   \
// 			(m_iMin51 < 0) || (m_iMin51 > 60) || (m_iMin52 < 0) || (m_iMin52 > 60) ||	\
// 			(m_iMin61 < 0) || (m_iMin61 > 60) || (m_iMin62 < 0) || (m_iMin62 > 60) ||	\
// 			(m_iMin71 < 0) || (m_iMin71 > 60) || (m_iMin72 < 0) || (m_iMin72 > 60) ||	\
// 			(m_iMin81 < 0) || (m_iMin81 > 60) || (m_iMin82 < 0) || (m_iMin82 > 60))
// 		{
// 			g_StringLanType(szLan, "分钟范围在0 -- 60之间", "Minute between 0 - 60 ");
// 			AfxMessageBox(szLan);
// 			return;
// 		}
// 
// 		memcpy(m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.byAlarmName, m_csAlarmName,NAME_LEN);
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.byAlarmHandle = m_bChkHanleAlarm;
// 		for (i=0; i<MAX_ALARMOUT_V30; i++)
// 		{
// 			m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.byRelAlarmOut[i] = (BYTE)m_bAlarmOut[i];
// 		}
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.byRelRecordChan[0] = m_bChkRecordEn;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType = 0;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType |= (m_bChkMonitorAlarm << 0);
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType |= (m_bChkAudioAlarm << 1);
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType |= (m_bChkReportCenter << 2);
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType |= (m_bChkInvokeAlarmOut << 3);
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType |= (m_bChkInvokeJpegCapture << 4);
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType |= (m_bChkWirelessLight << 5);
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType |= (m_bChkPicFtp << 9);
// 		
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][0].byStartHour = (BYTE)m_iHour11;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][0].byStartMin = (BYTE)m_iMin11;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][0].byStopHour = (BYTE)m_iHour12;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][0].byStopMin = (BYTE)m_iMin12;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][1].byStartHour = (BYTE)m_iHour21;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][1].byStartMin = (BYTE)m_iMin21;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][1].byStopHour = (BYTE)m_iHour22;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][1].byStopMin = (BYTE)m_iMin22;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][2].byStartHour = (BYTE)m_iHour31;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][2].byStartMin = (BYTE)m_iMin31;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][2].byStopHour = (BYTE)m_iHour32;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][2].byStopMin = (BYTE)m_iMin32;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][3].byStartHour = (BYTE)m_iHour41;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][3].byStartMin = (BYTE)m_iMin41;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][3].byStopHour = (BYTE)m_iHour42;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][3].byStopMin = (BYTE)m_iMin42;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][4].byStartHour = (BYTE)m_iHour51;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][4].byStartMin = (BYTE)m_iMin51;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][4].byStopHour = (BYTE)m_iHour52;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][4].byStopMin = (BYTE)m_iMin52;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][5].byStartHour = (BYTE)m_iHour61;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][5].byStartMin = (BYTE)m_iMin61;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][5].byStopHour = (BYTE)m_iHour62;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][5].byStopMin = (BYTE)m_iMin62;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][6].byStartHour = (BYTE)m_iHour71;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][6].byStartMin = (BYTE)m_iMin71;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][6].byStopHour = (BYTE)m_iHour72;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][6].byStopMin = (BYTE)m_iMin72;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][7].byStartHour = (BYTE)m_iHour81;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][7].byStartMin = (BYTE)m_iMin81;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][7].byStopHour = (BYTE)m_iHour82;
// 		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmTime[j][7].byStopMin = (BYTE)m_iMin82;
// 	}
}

void CDlgIPCSpecial::OnSelchangeComboAuxAlarmId() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int i;
	m_lAuxAlarmID = m_comboAuxAlarmId.GetCurSel();
	m_lWirelessID = m_comboWirelessId.GetCurSel();

	m_comboAuxAlarmType.SetCurSel(m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType-1);
	if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_PIR)
	{
		m_csAlarmName.Format("%s", m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byAlarmName);
		m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byAlarmHandle;
		for (i=0; i<MAX_ALARMOUT_V30; i++)
		{
			m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.byRelAlarmOut[i];
		}
		m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byRelRecordChan[0];
		m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType &0x01;
		m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>1)&0x01;
		m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>2)&0x01;
		m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>3)&0x01;
		m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>4)&0x01;
		m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>9)&0x01;
		m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>5)&0x01;

		m_comboWeekday.SetCurSel(0);
		GetComboAlarminWeekdayData(0);
	}
	else if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_WIRELESS)
	{
		m_csAlarmName.Format("%s", m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byAlarmName);
		m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byAlarmHandle;
		m_byWirelessID = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byID;
		for (i=0; i<MAX_ALARMOUT_V30; i++)
		{
			m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.byRelAlarmOut[i];
		}
		m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byRelRecordChan[0];
		m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType &0x01;
		m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>1)&0x01;
		m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>2)&0x01;
		m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>3)&0x01;
		m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>4)&0x01;
		m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>9)&0x01;
		m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>5)&0x01;
	}
	else if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_CALLHELP)
	{
		m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.byAlarmHandle;
		for (i=0; i<MAX_ALARMOUT_V30; i++)
		{
			m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.byRelAlarmOut[i];
		}
		m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.byRelRecordChan[0];
		m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType &0x01;
		m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>1)&0x01;
		m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>2)&0x01;
		m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>3)&0x01;
		m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>4)&0x01;
		m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>9)&0x01;
		m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>5)&0x01;
	}
// 	else if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_PIR_EX)
// 	{
// 		m_csAlarmName.Format("%s", m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.byAlarmName);
// 		m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.byAlarmHandle;
// 		for (i=0; i<MAX_ALARMOUT_V30; i++)
// 		{
// 			m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.byRelAlarmOut[i];
// 		}
// 		m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.byRelRecordChan[0];
// 		m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType &0x01;
// 		m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType>>1)&0x01;
// 		m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType>>2)&0x01;
// 		m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType>>3)&0x01;
// 		m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType>>4)&0x01;
// 		m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType>>9)&0x01;
// 		m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType>>5)&0x01;
// 		
// 		m_comboWeekday.SetCurSel(0);
// 		GetComboAlarminWeekdayData(0);
// 	}
	CreateTree();
	UpdateData(FALSE);
}

void CDlgIPCSpecial::OnSelchangeComboAuxalarmType() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char sAlarmName[33] = {0};
	int i;
	m_lAuxAlarmID = m_comboAuxAlarmId.GetCurSel();
	m_lWirelessID = m_comboWirelessId.GetCurSel();
	m_staNote.ShowWindow(SW_SHOW);
	
	if (m_comboAuxAlarmType.GetCurSel()+1 == IPC_AUXALARM_PIR)
	{
		m_staNote.ShowWindow(SW_HIDE);
	}
	
	if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == m_comboAuxAlarmType.GetCurSel()+1)
	{
		if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_PIR)
		{
			m_csAlarmName.Format("%s", m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byAlarmName);
			m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byAlarmHandle;
			for (i=0; i<MAX_ALARMOUT_V30; i++)
			{
				m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.byRelAlarmOut[i];
			}
			m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byRelRecordChan[0];
			m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType &0x01;
			m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>1)&0x01;
			m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>2)&0x01;
			m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>3)&0x01;
			m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>4)&0x01;
			m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>9)&0x01;
			m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>5)&0x01;

			m_comboWeekday.SetCurSel(0);
			GetComboAlarminWeekdayData(0);
		}
		else if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_WIRELESS)
		{
			m_csAlarmName.Format("%s", m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byAlarmName);
			m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byAlarmHandle;
			m_byWirelessID = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byID;
			for (i=0; i<MAX_ALARMOUT_V30; i++)
			{
				m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.byRelAlarmOut[i];
			}
			m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byRelRecordChan[0];
			m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType &0x01;
			m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>1)&0x01;
			m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>2)&0x01;
			m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>3)&0x01;
			m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>4)&0x01;
			m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>9)&0x01;
			m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>5)&0x01;
		}
		else if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_CALLHELP)
		{
			m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.byAlarmHandle;
			for (i=0; i<MAX_ALARMOUT_V30; i++)
			{
				m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.byRelAlarmOut[i];
			}
			m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.byRelRecordChan[0];
			m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType &0x01;
			m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>1)&0x01;
			m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>2)&0x01;
			m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>3)&0x01;
			m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>4)&0x01;
			m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>9)&0x01;
			m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>5)&0x01;
		}
// 		else if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_PIR_EX)
// 		{
// 			m_csAlarmName.Format("%s", m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.byAlarmName);
// 			m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.byAlarmHandle;
// 			for (i=0; i<MAX_ALARMOUT_V30; i++)
// 			{
// 				m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.byRelAlarmOut[i];
// 			}
// 			m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.byRelRecordChan[0];
// 			m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType &0x01;
// 			m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType>>1)&0x01;
// 			m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType>>2)&0x01;
// 			m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType>>3)&0x01;
// 			m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType>>4)&0x01;
// 			m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType>>9)&0x01;
// 			m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType>>5)&0x01;
// 			
// 			m_comboWeekday.SetCurSel(0);
// 			GetComboAlarminWeekdayData(0);
// 		}
	}
	else
	{
		m_comboWirelessId.SetCurSel(0);
		
		m_csAlarmName.Format("%s", sAlarmName);
		m_bChkHanleAlarm = 0;
		for (i=0; i<MAX_ALARMOUT_V30; i++)
		{
			m_bAlarmOut[i] = 0;
		}
		m_bChkRecordEn = 0;
		m_bChkMonitorAlarm = 0;
		m_bChkAudioAlarm = 0;
		m_bChkReportCenter = 0;
		m_bChkInvokeAlarmOut = 0;
		m_bChkInvokeJpegCapture = 0;
		m_bChkPicFtp = 0;
		m_bChkWirelessLight = 0;
	}
	CreateTree();
	UpdateData(FALSE);
}

void CDlgIPCSpecial::OnSelchangeComboWirelessAlarmId() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int i;
	m_lAuxAlarmID = m_comboAuxAlarmId.GetCurSel();
	m_lWirelessID = m_comboWirelessId.GetCurSel();
	
	m_comboAuxAlarmType.SetCurSel(m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType-1);
	if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_PIR)
	{
		m_csAlarmName.Format("%s", m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byAlarmName);
		m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byAlarmHandle;
		for (i=0; i<MAX_ALARMOUT_V30; i++)
		{
			m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.byRelAlarmOut[i];
		}
		m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byRelRecordChan[0];
		m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType &0x01;
		m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>1)&0x01;
		m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>2)&0x01;
		m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>3)&0x01;
		m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>4)&0x01;
		m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>9)&0x01;
		m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>5)&0x01;

		m_comboWeekday.SetCurSel(0);
		GetComboAlarminWeekdayData(0);
	}
	else if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_WIRELESS)
	{
		m_csAlarmName.Format("%s", m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byAlarmName);
		m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byAlarmHandle;
		m_byWirelessID = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byID;
		for (i=0; i<MAX_ALARMOUT_V30; i++)
		{
			m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.byRelAlarmOut[i];
		}
		m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byRelRecordChan[0];
		m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType &0x01;
		m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>1)&0x01;
		m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>2)&0x01;
		m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>3)&0x01;
		m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>4)&0x01;
		m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>9)&0x01;
		m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>5)&0x01;
	}
	else if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_CALLHELP)
	{
		m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.byAlarmHandle;
		for (i=0; i<MAX_ALARMOUT_V30; i++)
		{
			m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.byRelAlarmOut[i];
		}
		m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.byRelRecordChan[0];
		m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType &0x01;
		m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>1)&0x01;
		m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>2)&0x01;
		m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>3)&0x01;
		m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>4)&0x01;
		m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>9)&0x01;
		m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>5)&0x01;
	}
// 	else if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_PIR_EX)
// 	{
// 		m_csAlarmName.Format("%s", m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.byAlarmName);
// 		m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.byAlarmHandle;
// 		for (i=0; i<MAX_ALARMOUT_V30; i++)
// 		{
// 			m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.byRelAlarmOut[i];
// 		}
// 		m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.byRelRecordChan[0];
// 		m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType &0x01;
// 		m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType>>1)&0x01;
// 		m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType>>2)&0x01;
// 		m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType>>3)&0x01;
// 		m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType>>4)&0x01;
// 		m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType>>9)&0x01;
// 		m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarmEx.struAlarmHandleType.dwHandleType>>5)&0x01;
// 		
// 		m_comboWeekday.SetCurSel(0);
// 		GetComboAlarminWeekdayData(0);
// 	}
	CreateTree();
	UpdateData(FALSE);
}

void CDlgIPCSpecial::OnPaint() 
{
	CreateTree();
	CDialog::OnPaint();
}

void CDlgIPCSpecial::OnChkWpsEn() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_WPS_PARAM struWps = {0};
	struWps.dwSize = sizeof(struWps);
	struWps.byEnableWps = m_bChkWpsEn;

	char szLan[128] = {0};

	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_WPSCFG, 1, &struWps, sizeof(struWps)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_WPSCFG fail");
        AfxMessageBox("Fail to set PU stream config");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_WPSCFG Succ");
    }
}

void CDlgIPCSpecial::OnBtnRefresh() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn;

	char szLan[128] = {0};
	NET_DVR_WPS_PARAM struWps = {0};
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_WPSCFG, 1, &struWps, sizeof(struWps), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_WPSCFG Fail");
        g_StringLanType(szLan, "获取WPS配置失败", "Fail to get WPS config");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_WPSCFG Success");
    }

	m_bChkWpsEn = struWps.byEnableWps;
	UpdateData(FALSE);
}

void CDlgIPCSpecial::OnBtnWpsConnect() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szTmp[33] = {0};
	NET_DVR_WPS_CONNECT_PARAM struWps = {0};
	struWps.dwSize = sizeof(struWps);
	struWps.byConnectType = m_comboWpsConType.GetCurSel();
    memcpy(struWps.byPIN, m_csAPPin, m_csAPPin.GetLength());
	memcpy(struWps.byEssid, m_csWpsEssid, m_csWpsEssid.GetLength());
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_WPS_CONNECT, &struWps, sizeof(struWps)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_WPS_CONNECT");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_WPS_CONNECT");
	}
}

void CDlgIPCSpecial::OnBtnUpdatePin() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_UPDATE_PIN, NULL, 0))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_UPDATE_PIN");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_UPDATE_PIN");
	}
}

void CDlgIPCSpecial::OnBtnGetDevPin() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn;
	
	char szLan[128] = {0};
	NET_DVR_PIN_PARAM struPin = {0};
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_DEVICE_PIN, 1, &struPin, sizeof(struPin), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_DEVICE_PIN Fail");
        g_StringLanType(szLan, "获取设备PIN码失败", "Fail to get device PIN");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_DEVICE_PIN Success");
    }
	
	char szTmp[9] = {0};
	memcpy(szTmp, struPin.byPIN, 8);
	m_csDevPin.Format("%s", szTmp);
	UpdateData(FALSE);
}

void CDlgIPCSpecial::OnBtnFishEyeSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_PREVIEW_DISPLAYCFG struFishEye;
	memset(&struFishEye, 0, sizeof(struFishEye));
	struFishEye.dwSize =  sizeof(struFishEye);
	struFishEye.byMountType = m_comboFishEyeMountType.GetCurSel();
	struFishEye.byCorrectMode = m_comboFishEyeConnectMode.GetCurSel();
	struFishEye.byRealTimeOutput = m_comboRealTimeOutput.GetCurSel()/*m_bRealTimeOutput*/;

	if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_PREVIEW_DISPLAYCFG, 1, &struFishEye, sizeof(struFishEye)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_PREVIEW_DISPLAYCFG");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_PREVIEW_DISPLAYCFG");
		return;
	}
}

void CDlgIPCSpecial::OnBtnFishEyeGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReturn;
	
	NET_DVR_PREVIEW_DISPLAYCFG struFishEye = {0};
    if (!NET_DVR_GetDVRConfig(m_lServerID,  NET_DVR_GET_PREVIEW_DISPLAYCFG, 1, &struFishEye, sizeof(struFishEye), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, " NET_DVR_GET_PREVIEW_DISPLAYCFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, " NET_DVR_GET_PREVIEW_DISPLAYCFG");

		m_comboFishEyeConnectMode.SetCurSel(struFishEye.byCorrectMode);
		m_comboFishEyeMountType.SetCurSel(struFishEye.byMountType);
		//m_bRealTimeOutput = struFishEye.byRealTimeOutput;
		m_comboRealTimeOutput.SetCurSel(struFishEye.byRealTimeOutput);
    	UpdateData(FALSE);
    }
}

/*************************************************
函数名:    	~CDlgIPCSpecial
函数描述:	析构函数
输入参数:   
无
输出参数: 无  			
返回值:		
无
*************************************************/
CDlgIPCSpecial::~CDlgIPCSpecial()
{
	if (m_lPlayHandle >= 0)
	{
		NET_DVR_RigisterDrawFun(m_lPlayHandle,NULL, 0);
		NET_DVR_StopRealPlay(m_lPlayHandle);
		m_lPlayHandle = -1;
	}
}


BOOL CDlgIPCSpecial::PreTranslateMessage(MSG* pMsg) 
{
	CPoint pt(0,0);
	GetDlgItem(IDC_PLAYWND_PTZ)->GetWindowRect(&m_rcWnd);
    GetCursorPos(&pt);
	ScreenToClient(&m_rcWnd);
	ScreenToClient(&pt);
    CString strTemp = _T("");
    DWORD i=0;
    BOOL bOneLine = TRUE,bXOneLine = TRUE,bYOneLine = TRUE;
    
    switch(pMsg->message)  // Message of Draw
    {
    case WM_LBUTTONDOWN:
        if(GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)//Press CTRL to draw
        {
			if(PtInRect(&m_rcWnd,pt))
			{
				m_struPoint.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
				m_struPoint.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
				if (!m_bMouseMove)
				{
					m_struVcaRect.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
					m_struVcaRect.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
					m_struVcaRect.fWidth = 0;
					m_struVcaRect.fHeight = 0;
					m_bMouseMove = TRUE;
				}

			}
		}
		break;
	case WM_MOUSEMOVE:
		 if(GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)//Press CTRL to draw
		 {
			if(PtInRect(&m_rcWnd,pt))
			{
				if (m_bMouseMove)
				{
					m_struVcaRect.fWidth = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() - m_struVcaRect.fX;
					m_struVcaRect.fHeight = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() - m_struVcaRect.fY;
				}
			}
		 }
		 break;
 case WM_LBUTTONUP:
        if (PtInRect(&m_rcWnd, pt) && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            m_bMouseMove = FALSE;

        }
        break;
	default:
		break;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgIPCSpecial::OnDestroy()
{
	OnBtnCloselink();
	CDialog::OnDestroy();
}

void CDlgIPCSpecial::OnBtnGetPresetNum() 
{
	UpdateData(TRUE);
	DWORD dwReturn;
	char szLan[128] = {0};
	NET_DVR_PRESET_INFO strPrsetinfo = {0};
	if (!NET_DVR_GetDVRConfig(m_lServerID,  NET_DVR_GET_PRESET_NUM, m_lChannel, &strPrsetinfo, sizeof(strPrsetinfo), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, " NET_DVR_GET_PRESET_NUM");
        g_StringLanType(szLan, "获取预置点个数失败", "Fail to get Preset Num");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, " NET_DVR_GET_PRESET_NUM");
    }
	m_iPresetNum = strPrsetinfo.dwPresetNum;
	m_iPresetGroupNum = strPrsetinfo.dwGroupNum;

	m_iPtzPresetNum = strPrsetinfo.dwPresetNum;

	UpdateData(FALSE);	
}

void CDlgIPCSpecial::OnBtnGetPtzcruiseNum() 
{
	UpdateData(TRUE);
	DWORD dwReturn;
	char szLan[128] = {0};
	NET_DVR_PTZCRUISE_INFO strPtzCruiseinfo = {0};
	if (!NET_DVR_GetDVRConfig(m_lServerID,  NET_DVR_GET_PTZCRUISE_NUM, m_lChannel, &strPtzCruiseinfo, sizeof(strPtzCruiseinfo), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, " NET_DVR_GET_PTZCRUISE_NUM");
        g_StringLanType(szLan, "获取巡航路径个数失败", "Fail to get PTZCRUISE Num");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, " NET_DVR_GET_PTZCRUISE_NUM");
    }
	m_iPtzCruiseNum = strPtzCruiseinfo.dwPtzCruiseNum;
	m_iPreCruiseGroupNum = strPtzCruiseinfo.dwGroupNum;
	
	UpdateData(FALSE);
}

void CDlgIPCSpecial::OnBtnGetpresetInfo() 
{ 
	UpdateData(TRUE);
    
	char szLan[128] = {0};
	char szTemp[256] = {0};

	if (0 == m_iPtzPresetNum)
	{
		m_listGetPresetInfo.DeleteAllItems();
		g_StringLanType(szLan, "没有预置点可以获取!", "No preset points available");
		AfxMessageBox(szLan);
		return;
	}

	NET_DVR_PRESET_COND struPresetCond = {0};
	struPresetCond.dwSize              = sizeof(struPresetCond);
	struPresetCond.dwChannel           = m_lChannel;
	struPresetCond.dwGroupNO           = m_iPresetGetGroupNum;
   
	DWORD dwCount = 0;
	if (m_iPresetGetGroupNum <= 1)
	{
		dwCount = m_iPtzPresetNum;
	}
	else
	{   
		int nGourpNum = max(m_iPresetGetGroupNum,1);
		dwCount       = m_iPtzPresetNum - (nGourpNum - 1) * 64;
	}

	if (dwCount > m_iPresetNum)
	{   
		g_StringLanType(szLan, "分组号不合理", "Group number is not correct");
		AfxMessageBox(szLan);
		return;
	}

	NET_DVR_PRESETCFG*pPresetcfg = new NET_DVR_PRESETCFG[dwCount];
	DWORD            *pStatus    = new DWORD[dwCount];

    BOOL bRet = NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_PRESETCFG, dwCount, &struPresetCond, sizeof(NET_DVR_PRESET_COND), pStatus, pPresetcfg, dwCount*sizeof(NET_DVR_PRESETCFG));
	if (!bRet)
	{   
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PRESETCFG");
		g_StringLanType(szLan, "获取预置点信息失败", "Get preset points param failed");
		sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
		AfxMessageBox(szTemp);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PRESETCFG");

		CString   strTextPresetIndex = ""; 
		CString   strTextPresetfx    = ""; 
		CString   strTextPresetfy    = ""; 
		m_listGetPresetInfo.DeleteAllItems();	
		for(int i = 0; i < dwCount; i++)
		{
			m_listGetPresetInfo.InsertItem(i, "", -1);	
			strTextPresetIndex.Format("%d", (pPresetcfg[i].dwPresetIndex + 1));
			strTextPresetfx.Format("%f", pPresetcfg[i].struVcaPoint.fX);
			strTextPresetfy.Format("%f", pPresetcfg[i].struVcaPoint.fY);
				
			m_listGetPresetInfo.SetItemText(i, 1, strTextPresetIndex);
			m_listGetPresetInfo.SetItemText(i, 2, strTextPresetfx);
			m_listGetPresetInfo.SetItemText(i, 3, strTextPresetfy);				
		}
	}

	delete [] pStatus;
	delete [] pPresetcfg;
}

void CDlgIPCSpecial::OnBtnGetcruiseInfo() 
{
	UpdateData(TRUE);
    
	char szLan[128] = {0};
	char szTemp[256] = {0};
	if (0 == m_iPtzCruiseNum)
	{
		m_listGetPreCruiseiInfo.DeleteAllItems();
        g_StringLanType(szLan, "没有巡航路径可以获取!", "No cruise path available");
        AfxMessageBox(szLan);
		return;
	}
	
	NET_DVR_PTZCRUISE_COND strPtzCruiseCond = {0};                  
	strPtzCruiseCond.dwChannel = m_lChannel; 
	strPtzCruiseCond.dwGroupNO = m_iPreGetCruiseGroupNum;
	strPtzCruiseCond.dwSize    = sizeof(strPtzCruiseCond);

	DWORD dwCount = 0;
	
	if (m_iPreGetCruiseGroupNum <= 1)
	{
		dwCount = m_iPtzCruiseNum;
	}
	else
	{   
		int nGourpNum = max(m_iPresetGetGroupNum,1);
		dwCount = m_iPtzCruiseNum - (m_iPreGetCruiseGroupNum - 1) * 64;  
	}
    
	if (dwCount > m_iPtzCruiseNum)
	{   
		g_StringLanType(szLan, "分组号不合理", "Group number is not correct");
		AfxMessageBox(szLan);
		return;
	}

	LPNET_DVR_PTZCRUISECFG pPtzCuisePointCfg = new NET_DVR_PTZCRUISECFG[dwCount];  
	DWORD *pStatus                           = new DWORD[dwCount];
	
	memset(pPtzCuisePointCfg, 0, m_iPtzCruiseNum*sizeof(NET_DVR_PTZCRUISECFG));
	memset(pStatus,           0, m_iPtzCruiseNum*sizeof(DWORD));

	BOOL bRet = NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_PTZCRUISECFG, dwCount, &strPtzCruiseCond, sizeof(NET_DVR_PTZCRUISE_COND), pStatus, pPtzCuisePointCfg, dwCount*sizeof(NET_DVR_PTZCRUISECFG));
	if (!bRet)
	{   
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PTZCRUISECFG");
		g_StringLanType(szLan, "获取巡航路径信息失败", "Get Video PtzCruise Info Configuration failed");
		sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
		AfxMessageBox(szTemp);
	}
	else
	{  
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PTZCRUISECFG");
		m_listGetPreCruiseiInfo.DeleteAllItems();
		
		CString   strTextPtzCruiseIndex  = "";
		CString   strTextPtzCruisepoint  = "";
		CString   strTextPresetIndex     = ""; 
		CString   strTextPresetfx        = ""; 
		CString   strTextPresetfy        = ""; 
		CString   strTextDwell           = "";		
		CString   strTextSpeed           = "";

		NET_DVR_PTZCRUISECFG* pPtzCuisePointCfgTemp = pPtzCuisePointCfg;
		for(int j = 0; j < dwCount; j++)
		{
			for (int i = 0;i < MAX_PTZCRUISE_POINT_NUM;i++)
			{
				m_listGetPreCruiseiInfo.InsertItem(i, "", -1);
				strTextPtzCruiseIndex.Format("%d", (pPtzCuisePointCfgTemp->dwCruiseRoute + 1));
				strTextPtzCruisepoint.Format("%d", i + 1);
				strTextPresetIndex.Format("%d",(pPtzCuisePointCfgTemp->struCruisePoint[i].dwPresetIndex + 1));
				strTextPresetfx.Format("%f", pPtzCuisePointCfgTemp->struCruisePoint[i].struVcaPoint.fX);
				strTextPresetfy.Format("%f", pPtzCuisePointCfgTemp->struCruisePoint[i].struVcaPoint.fY);
				strTextDwell.Format("%d", pPtzCuisePointCfgTemp->struCruisePoint[i].byDwell);
				strTextSpeed.Format("%d", pPtzCuisePointCfgTemp->struCruisePoint[i].bySpeed);
				
				m_listGetPreCruiseiInfo.SetItemText(i, 1, strTextPtzCruiseIndex);
				m_listGetPreCruiseiInfo.SetItemText(i, 2, strTextPtzCruisepoint);
				m_listGetPreCruiseiInfo.SetItemText(i, 3, strTextPresetIndex);
				m_listGetPreCruiseiInfo.SetItemText(i, 4, strTextPresetfx);
				m_listGetPreCruiseiInfo.SetItemText(i, 5, strTextPresetfy);
				m_listGetPreCruiseiInfo.SetItemText(i, 6, strTextDwell);
				m_listGetPreCruiseiInfo.SetItemText(i, 7, strTextSpeed);
			}
			pPtzCuisePointCfgTemp++;
		}
	}
	
	delete [] pPtzCuisePointCfg;
	delete [] pStatus;
}

void CDlgIPCSpecial::OnBtnMotionTrackSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_MOTION_TRACK_CFG strMotionTtackCfg = {0};
	memset(&strMotionTtackCfg, 0, sizeof(strMotionTtackCfg));
	strMotionTtackCfg.dwSize = sizeof(strMotionTtackCfg);
	strMotionTtackCfg.byEnableTrack = m_comboMotionTrackSet.GetCurSel();


//	if (NET_DVR_RemoteControl(m_lServerID, NET_DVR_SET_MOTION_TRACK_CFG, &strMotionTtackCfg, sizeof(strMotionTtackCfg)))
	if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_MOTION_TRACK_CFG, 1, &strMotionTtackCfg, sizeof(strMotionTtackCfg)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_MOTION_TRACK_CFG");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_MOTION_TRACK_CFG");
		return;
	}
	UpdateData(FALSE);
}

void CDlgIPCSpecial::OnBtnMotionTrackGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReturn;
	char szLan[128] = {0};
	NET_DVR_MOTION_TRACK_CFG strMotionTtackCfg = {0};
	if (!NET_DVR_GetDVRConfig(m_lServerID,  NET_DVR_GET_MOTION_TRACK_CFG, 1, &strMotionTtackCfg, sizeof(strMotionTtackCfg), &dwReturn))

//	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_GET_MOTION_TRACK_CFG, &strMotionTtackCfg, sizeof(strMotionTtackCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, " NET_DVR_GET_MOTION_TRACK_CFG Fail");
        g_StringLanType(szLan, "获取跟踪模式状态失败", "Fail to get motion track");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, " NET_DVR_GET_MOTION_TRACK_CFG Success");
    }
	m_comboMotionTrackGet.SetCurSel(strMotionTtackCfg.byEnableTrack);
	
	UpdateData(FALSE);
	
}

void CDlgIPCSpecial::OnBtnIpaddrFilter() 
{
	// TODO: Add your control notification handler code here
	CDlgIPAddrFilterCfg dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.DoModal();
}

void CDlgIPCSpecial::OnBtnUploadLogo() 
{
	// TODO: Add your control notification handler code here
	CDlgUploadLogo dlg;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.m_lServerID = m_lServerID;
	dlg.DoModal();
}

void CDlgIPCSpecial::OnSelchangeComboAlarminWeekday() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int	j = m_comboWeekday.GetCurSel();	
	GetComboAlarminWeekdayData(j);
	UpdateData(FALSE);
}

void CDlgIPCSpecial::GetComboAlarminWeekdayData(int j) 
{
	m_iHour11 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][0].byStartHour;
	m_iMin11 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][0].byStartMin;
	m_iHour12 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][0].byStopHour;
	m_iMin12 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][0].byStopMin;
	m_iHour21 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][1].byStartHour;
	m_iMin21 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][1].byStartMin;
	m_iHour22 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][1].byStopHour;
	m_iMin22 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][1].byStopMin;
	m_iHour31 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][2].byStartHour;
	m_iMin31 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][2].byStartMin;
	m_iHour32 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][2].byStopHour;
	m_iMin32 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][2].byStopMin;
	m_iHour41 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][3].byStartHour;
	m_iMin41 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][3].byStartMin;
	m_iHour42 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][3].byStopHour;
	m_iMin42 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][3].byStopMin;
	m_iHour51 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][4].byStartHour;
	m_iMin51 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][4].byStartMin;
	m_iHour52 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][4].byStopHour;
	m_iMin52 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][4].byStopMin;
	m_iHour61 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][5].byStartHour;
	m_iMin61 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][5].byStartMin;
	m_iHour62 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][5].byStopHour;
	m_iMin62 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][5].byStopMin;
	m_iHour71 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][6].byStartHour;
	m_iMin71 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][6].byStartMin;
	m_iHour72 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][6].byStopHour;
	m_iMin72 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][6].byStopMin;
	m_iHour81 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][7].byStartHour;
	m_iMin81 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][7].byStartMin;
	m_iHour82 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][7].byStopHour;
	m_iMin82 = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][7].byStopMin;
}

void CDlgIPCSpecial::SetComboAlarminWeekdayData(int j) 
{
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][0].byStartHour = (BYTE)m_iHour11;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][0].byStartMin = (BYTE)m_iMin11;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][0].byStopHour = (BYTE)m_iHour12;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][0].byStopMin = (BYTE)m_iMin12;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][1].byStartHour = (BYTE)m_iHour21;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][1].byStartMin = (BYTE)m_iMin21;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][1].byStopHour = (BYTE)m_iHour22;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][1].byStopMin = (BYTE)m_iMin22;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][2].byStartHour = (BYTE)m_iHour31;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][2].byStartMin = (BYTE)m_iMin31;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][2].byStopHour = (BYTE)m_iHour32;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][2].byStopMin = (BYTE)m_iMin32;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][3].byStartHour = (BYTE)m_iHour41;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][3].byStartMin = (BYTE)m_iMin41;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][3].byStopHour = (BYTE)m_iHour42;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][3].byStopMin = (BYTE)m_iMin42;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][4].byStartHour = (BYTE)m_iHour51;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][4].byStartMin = (BYTE)m_iMin51;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][4].byStopHour = (BYTE)m_iHour52;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][4].byStopMin = (BYTE)m_iMin52;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][5].byStartHour = (BYTE)m_iHour61;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][5].byStartMin = (BYTE)m_iMin61;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][5].byStopHour = (BYTE)m_iHour62;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][5].byStopMin = (BYTE)m_iMin62;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][6].byStartHour = (BYTE)m_iHour71;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][6].byStartMin = (BYTE)m_iMin71;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][6].byStopHour = (BYTE)m_iHour72;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][6].byStopMin = (BYTE)m_iMin72;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][7].byStartHour = (BYTE)m_iHour81;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][7].byStartMin = (BYTE)m_iMin81;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][7].byStopHour = (BYTE)m_iHour82;
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmTime[j][7].byStopMin = (BYTE)m_iMin82;
}

void CDlgIPCSpecial::OnBtnGetpresetname() 
{
	// TODO: Add your control notification handler code here
	memset(m_struPresetName, 0, sizeof(NET_DVR_PRESET_NAME) * MAX_PRESET_NUM/*256*/);
	
	DWORD iRet = 0;
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_PRESET_NAME, m_lChannel, m_struPresetName, sizeof(NET_DVR_PRESET_NAME) * MAX_PRESET_NUM/*256*/, &iRet))
	{
		char szLan[128] = {0};
		char szTemp[256] = {0};	
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, " NET_DVR_GET_PRESET_NAME Fail");
		g_StringLanType(szLan, "获取预置点名称失败!", "Fail to get the name of presets!");
		sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
        AfxMessageBox(szTemp);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, " NET_DVR_GET_PRESET_NAME SUCESS");
	}
	
	OnEditchangeComboPtzpresetno();
}

void CDlgIPCSpecial::OnEditchangeComboPtzpresetno() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int i = m_comboPresetNo.GetCurSel();
	m_strPresetName.Format("%s", m_struPresetName[i].byName);
    m_fX = m_struPresetName[i].wPanPos;
    m_fY = m_struPresetName[i].wTiltPos;
    m_fZ = m_struPresetName[i].wZoomPos;
	UpdateData(FALSE);
}

void CDlgIPCSpecial::OnBtnSetpresetname() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int i = m_comboPresetNo.GetCurSel();
	strncpy(m_struPresetName[i].byName,(LPCTSTR)m_strPresetName,NAME_LEN);
	m_struPresetName[i].dwSize = sizeof(NET_DVR_PRESET_NAME);
    m_struPresetName[i].wPanPos = m_fX;
    m_struPresetName[i].wTiltPos = m_fY;
    m_struPresetName[i].wZoomPos = m_fZ;
	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_PRESET_NAME, m_lChannel, &(m_struPresetName[i]), sizeof(NET_DVR_PRESET_NAME)))
	{
		char szLan[128] = {0};
		char szTemp[256] = {0};	
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, " NET_DVR_SET_PRESET_NAME Fail");
		g_StringLanType(szLan, "设置预置点名称失败!", "Fail to get the name of presets!");
		sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
        AfxMessageBox(szTemp);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, " NET_DVR_SET_PRESET_NAME SUCESS");
	}
	UpdateData(FALSE);
}

void CDlgIPCSpecial::OnBtnPtztask() 
{
	// TODO: Add your control notification handler code here
	CDlgPTZTasks dlg;
	dlg.m_iChanNo = m_lChannel;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.m_lServerID = m_lServerID;
	
	dlg.DoModal();
}

void CDlgIPCSpecial::OnBtnGettracktype() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

	NET_DVR_PTZ_MANUALTRACE struTrack = {0};
	struTrack.dwSize = sizeof(NET_DVR_PTZ_MANUALTRACE);
	struTrack.byTrackType = m_comboTrackType.GetCurSel();
    struTrack.dwSerialNo = m_dwSerialNo;
    SYSTEMTIME t;
    GetLocalTime(&t);

    struTrack.struTime.wYear = t.wYear;
    struTrack.struTime.byMonth = t.wMonth;
    struTrack.struTime.byDay = t.wDay;
    struTrack.struTime.byHour = t.wHour;
    struTrack.struTime.byMinute = t.wMinute;
    struTrack.struTime.bySecond = t.wSecond;
    struTrack.struTime.wMilliSec = t.wMilliseconds;

	struTrack.struPoint.fX = m_struVcaRect.fX;
	struTrack.struPoint.fY = m_struVcaRect.fY;

	struTrack.struPointEnd.fX = m_struVcaRect.fX + m_struVcaRect.fWidth;
	struTrack.struPointEnd.fY = m_struVcaRect.fY + m_struVcaRect.fHeight;
 	struTrack.dwChannel = 1;
	DWORD iRet = 0;
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_CONTROL_PTZ_MANUALTRACE, &struTrack, sizeof(struTrack)))
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_CONTROL_PTZ_MANUALTRACE");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_CONTROL_PTZ_MANUALTRACE");
	}
}

void CDlgIPCSpecial::OnMouseMove(UINT nFlags, CPoint point)
{   
	CDialog::OnMouseMove(nFlags,point);

	if (!m_rcWnd.PtInRect(point))
	{   
		m_bDragFishEyePTZ = FALSE;
        PostMessage(WM_SETCURSOR,0,0);
		return;
	}
	PostMessage(WM_SETCURSOR,0,0);
	SendDragPtzPos(point);
}

void CDlgIPCSpecial::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDown(nFlags,point);

	if (!m_rcWnd.PtInRect(point))
	{   
		return;
	}

	if (m_lFishEyeCfgHandle != -1)
	{   
		int nPtzChannelIndex = m_comboPtzChannel.GetCurSel();
        if (nPtzChannelIndex != CB_ERR)
		{
			 m_dwPtzChannel = m_comboPtzChannel.GetItemData(nPtzChannelIndex);
		}
		m_bDragFishEyePTZ = TRUE;
		m_ptOriDrag = point;
    	PostMessage(WM_SETCURSOR,0,0);
	}
}

void CDlgIPCSpecial::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonUp(nFlags,point);

	m_bDragFishEyePTZ = FALSE;
	PostMessage(WM_SETCURSOR,0,0);
}

BOOL CDlgIPCSpecial::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (m_bDragFishEyePTZ)
	{
		SetCursor(LoadCursor(NULL,IDC_SIZEALL));
		return TRUE;
	}
	else
	{
		SetCursor(LoadCursor(NULL,IDC_ARROW));
	}
	return CDialog::OnSetCursor(pWnd,nHitTest,message);
}

void CDlgIPCSpecial::OnBtnCreatelink() 
{
	m_lFishEyeCfgHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_FISHEYE_CFG,NULL,0,fFishEyeRemoteConfigCallback,this);
	if (m_lFishEyeCfgHandle == -1)
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_FAIL_T, "NET_DVR_StartRemoteConfig NET_DVR_FISHEYE_CFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_SUCC_T, "NET_DVR_StartRemoteConfig NET_DVR_FISHEYE_CFG");
		GetDlgItem(IDC_BTN_CREATELINK)->EnableWindow(FALSE);
	}
	
}

void CDlgIPCSpecial::OnBtnCloselink() 
{
	if (m_lFishEyeCfgHandle == -1)
	{
		return;
	}

	if (!NET_DVR_StopRemoteConfig(m_lFishEyeCfgHandle))
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_FAIL_T, "NET_DVR_StopRemoteConfig NET_DVR_FISHEYE_CFG");
	}
	else
	{  
		g_pMainDlg->AddLog(m_lServerID, OPERATION_SUCC_T, "NET_DVR_StopRemoteConfig NET_DVR_FISHEYE_CFG");
		GetDlgItem(IDC_BTN_CREATELINK)->EnableWindow(TRUE);
	}
	m_lFishEyeCfgHandle = -1;
}

void CDlgIPCSpecial::SendDragPtzPos(CPoint pt)
{   
	if (!m_bDragFishEyePTZ    || 
		!m_rcWnd.PtInRect(pt) || 
		m_lFishEyeCfgHandle == -1)
	{
		return;
	}
    
	static DWORD s_LastSendTime = 0;

	DWORD dwCurSendTime = GetTickCount();
    DWORD dwInterval    = dwCurSendTime - s_LastSendTime;
	if (dwInterval < 60)
	{
		return;
	}



	NET_VCA_POINT ptTargetPtz;
	ptTargetPtz.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
	ptTargetPtz.fY = (float)(pt.y-m_rcWnd.top) /(float)m_rcWnd.Height();

	NET_VCA_POINT ptOriPtz;
    ptOriPtz.fX = (float)(m_ptOriDrag.x-m_rcWnd.left)/(float)m_rcWnd.Width();
	ptOriPtz.fY = (float)(m_ptOriDrag.y-m_rcWnd.top) /(float)m_rcWnd.Height();


	NET_DVR_DRAG_POS_PARAM     struDragPtzParam;
	struDragPtzParam.dwChannel    = m_lChannel;
	struDragPtzParam.dwPtzChannel = m_dwPtzChannel; // Only effecvice under fisheye mode
	struDragPtzParam.struToPoint  = ptTargetPtz;
	struDragPtzParam.struOriPoint = ptOriPtz;

	if (!NET_DVR_SendRemoteConfig(m_lFishEyeCfgHandle,DRAG_PTZ,(char*)&struDragPtzParam,sizeof(struDragPtzParam)))
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_FAIL_T, "NET_DVR_SendRemoteConfig DRAG_PTZ");
	}
	else
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_SUCC_T, "NET_DVR_SendRemoteConfig DRAG_PTZ");
	}

	s_LastSendTime = GetTickCount();
}

void CALLBACK fFishEyeRemoteConfigCallback(DWORD dwType, void *lpBuffer, DWORD dwBufLen, void *pUserData)
{  
	CDlgIPCSpecial* pIPCSpecial = (CDlgIPCSpecial*)pUserData;
	if (pIPCSpecial == NULL)
	{
		return;
	}
    
	CString strItem = "";

	switch (dwType)
	{
	case NET_SDK_CALLBACK_TYPE_STATUS:
		{
			if (lpBuffer != NULL)
			{
				DWORD dwStatus = *(DWORD*)lpBuffer;
				if (dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
				{
					
				    strItem = "Fisheye remote config link maybe closed";
					pIPCSpecial->AddFishEyeCallbackData(strItem);
				}
			}
		}
		break;
	case NET_SDK_CALLBACK_TYPE_DATA:
		{
			if (lpBuffer != NULL)
			{
				NET_DVR_CALLBACK_TYPE_DATA* pCallbackData = (NET_DVR_CALLBACK_TYPE_DATA*)lpBuffer;
				if (pCallbackData->dwDataType == ENUM_FISHEYE_STREAM_STATUS)
				{   
					NET_DVR_FISHEYE_STREAM_STATUS* pStreamStatus = (NET_DVR_FISHEYE_STREAM_STATUS*)pCallbackData->pData;
					DWORD dwStreamMode = pStreamStatus->byStreamMode;
					DWORD dwChannel    = pCallbackData->dwChannel;
				    
					CString strStatus = "Unknown";
					if (dwStreamMode == FISHEYE_STREAM_MODE_FISHEYE)
					{
						strStatus = "FishEye";
					}
					else if (dwStreamMode == FISHEYE_STREAM_MODE_PANORAMA)
					{
						strStatus = "PANORAMA";
					}
					else if (dwStreamMode == FISHEYE_STREAM_MODE_PTZ)
					{
						strStatus = "PTZ";
					}
					strItem.Format("Channel[%d] stream mode: %s",pCallbackData->dwChannel,strStatus);
					pIPCSpecial->AddFishEyeCallbackData(strItem);
				}
				else if (pCallbackData->dwDataType == ENUM_FISHEYE_PTZPOS)
				{   
					NET_VCA_POINT* pPoint = (NET_VCA_POINT*)pCallbackData->pData;
					strItem.Format("Channel[%d] ptz pos: [%.3f,%.3f]",pCallbackData->dwChannel,pPoint->fX,pPoint->fY);
					pIPCSpecial->AddFishEyeCallbackData(strItem);
				}
				else if (pCallbackData->dwDataType == ENUM_FISHEYE_REALTIME_OUTPUT)
				{
					DWORD dwOutputMode = *(DWORD*)pCallbackData->pData;
					strItem.Format("Channel[%d] realtime output: %s",pCallbackData->dwChannel,dwOutputMode == 0 ? "Off" : "On");
					pIPCSpecial->AddFishEyeCallbackData(strItem);
				}
			}
		}
		break;
	default:
		break;
	}
}

void CDlgIPCSpecial::OnBtnGetStreamMode() 
{
	NET_DVR_FISHEYE_STREAM_STATUS struStreamStatus = {0};
	DWORD dwStatus = 0;
	BOOL  bResult  = FALSE;

	if (!NET_DVR_GetDeviceStatus(m_lServerID,NET_DVR_GET_FISHEYE_STREAM_STATUS,1,&m_lChannel,sizeof(m_lChannel),
		&dwStatus,&struStreamStatus,sizeof(struStreamStatus)))
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_FAIL_T, "NET_DVR_GetDeviceStatus NET_DVR_GET_FISHEYE_STREAM_STATUS");
	}
	else
	{   
		bResult = TRUE;
		g_pMainDlg->AddLog(m_lServerID, OPERATION_SUCC_T, "NET_DVR_GetDeviceStatus NET_DVR_GET_FISHEYE_STREAM_STATUS");
	}
	
	if (bResult)
	{
		m_comboStreamMode.SetCurSel(struStreamStatus.byStreamMode);
	}
}

void CDlgIPCSpecial::OnBntGetPtzPos() 
{
	NET_VCA_POINT struPtzPoint = {0};
	DWORD dwReturn = 0;

	if (!NET_DVR_GetDVRConfig(m_lServerID,NET_DVR_GET_PTZ_POINT,m_lChannel,&struPtzPoint,sizeof(struPtzPoint),&dwReturn))
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_FAIL_T, "NET_DVR_GET_PTZ_POINT");
	}
	else
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_SUCC_T, "NET_DVR_GET_PTZ_POINT");
	}

	m_fPtzPosX = struPtzPoint.fX;
	m_fPtzPosY = struPtzPoint.fY;
	UpdateData(FALSE);
}

void CDlgIPCSpecial::OnBntSetPtzPos() 
{
	UpdateData(TRUE);
     
	NET_VCA_POINT struPtzPoint = {0};
	struPtzPoint.fX  = m_fPtzPosX;
	struPtzPoint.fY  = m_fPtzPosY;

	if (!NET_DVR_SetDVRConfig(m_lServerID,NET_DVR_SET_PTZ_POINT,m_lChannel,&struPtzPoint,sizeof(struPtzPoint)))
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_FAIL_T, "NET_DVR_SET_PTZ_POINT");
	}
	else
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_SUCC_T, "NET_DVR_SET_PTZ_POINT");
	}
}

void CDlgIPCSpecial::OnBtnSetDevparam() 
{
	UpdateData(TRUE);

	NET_DVR_LOGIN_DEVICE_PARAM struLoginDevParam = {0};
	struLoginDevParam.dwSize      = sizeof(struLoginDevParam);
	struLoginDevParam.byMobileDev = m_bMobileDev;

	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_DEV_PARAM,&struLoginDevParam,sizeof(struLoginDevParam)))
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_FAIL_T, "NET_DVR_REMOTECONTROL_DEV_PARAM");
	}
	else
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_SUCC_T, "NET_DVR_REMOTECONTROL_DEV_PARAM");
	}
}


void CDlgIPCSpecial::AddFishEyeCallbackData(CString strData)
{   
	int nItemCount = m_listFishEyeCallback.GetCount();
	if (nItemCount > 100)
	{
		m_listFishEyeCallback.DeleteString(nItemCount - 1);
	}
	m_listFishEyeCallback.InsertString(0,strData);
}

void CDlgIPCSpecial::OnBtnForensicsMode() 
{
	// TODO: Add your control notification handler code here
    CDlgVcaForensicsModeCfg dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel = m_lChannel;
    dlg.DoModal();
}

void CDlgIPCSpecial::OnBtnForcestopForensics() 
{
	// TODO: Add your control notification handler code here
    
    NET_DVR_FORCESTOP_FORENSICS_CFG struForcrStopForensicsCfg = {0};
    struForcrStopForensicsCfg.dwSize   = sizeof(struForcrStopForensicsCfg);
    struForcrStopForensicsCfg.dwChannel = m_lChannel;
    
    if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_FORCESTOP_FORENSICS_CTRL,&struForcrStopForensicsCfg,sizeof(struForcrStopForensicsCfg)))
    {
        g_pMainDlg->AddLog(m_lServerID, OPERATION_FAIL_T, "NET_DVR_FORCESTOP_FORENSICS_CTRL");
    }
    else
    {
        g_pMainDlg->AddLog(m_lServerID, OPERATION_SUCC_T, "NET_DVR_FORCESTOP_FORENSICS_CTRL");
	}
}
