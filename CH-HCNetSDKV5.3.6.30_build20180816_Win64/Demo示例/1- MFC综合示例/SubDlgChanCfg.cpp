/**********************************************************
FileName:    SubDlgChanCfg.cpp
Description: Channel Configuration      
Date:        2008/05/17
Note: 		<Global>struct, macro refer to GeneralDef.h, global variants and API refer to ClientDemo.cpp  
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/
#include "stdafx.h"
#include "ClientDemo.h"
#include "SubDlgChanCfg.h"
#include "DlgRemoteRecordSchedule.h"
#include "DlgRemoteHideArea.h"
#include "DlgRemoteMotionDetect.h"
#include "DlgRemoteHideAlarm.h"
#include "DlgRemoteVideoInLost.h"
#include "DlgRemoteShowString.h"
#include ".\subdlgchancfg.h"
#include "DlgJpegCaptureCfg.h"
#include "DlgDiskQuota.h"
#include "DlgRemoteVideoInput.h"
#include "DlgAccessCameraCfg.h"
#include "DialogRecordTimeSpan.h"
#include "DlgVideoOut.h"
#include "DlgWD1Enable.h"
#include "DlgNetraRecordPackage.h"
#include "DlgDeviceLanguageEncode.h"

LPNET_DVR_MOTION_V30 g_lpMotionDetect = NULL;
LPNET_DVR_MOTION_V40 g_lpMotionDetectV40 = NULL;
LPNET_DVR_HIDEALARM_V30 g_lpHideAlarm = NULL;
LPNET_DVR_HIDEALARM_V40 g_lpHideAlarmV40 = NULL;
LPNET_DVR_VILOST_V30 g_lpVILost = NULL;
LPNET_DVR_VILOST_V40 g_lpVILostV40 = NULL;
LPNET_DVR_VILOST_V40 g_lpAULostV40 = NULL;
// CSubDlgChanCfg dialog

/*********************************************************
  Function:	CSubDlgChanCfg
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CSubDlgChanCfg, CDialog)
CSubDlgChanCfg::CSubDlgChanCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubDlgChanCfg::IDD, pParent)
	, m_csChanName(_T(""))
	, m_iBitRate(0)
    , m_iAvBitRate(0)
	, m_iFrameIInterval(0)
	, m_bCheckRecord(FALSE)
	, m_bCheckHideArea(FALSE)
	, m_bCheckMotion(FALSE)
	, m_bCheckHideAlarm(FALSE)
	, m_bCheckVILost(FALSE)
	, m_bCheckAULost(FALSE)
	, m_bCheckOsd(FALSE)
	, m_iOsdX(0)
	, m_iOsdY(0)
	, m_bChkDispWeek(FALSE)
	, m_bCheckChanName(FALSE)
	, m_iChanNameX(0)
	, m_iChanNameY(0)
	, m_iDeviceIndex(-1)
	, m_lLoginID(-1)
	, m_iCompressionTypeSel(NORM_HIGH_STREAM_COMPRESSION)
	, m_iCurChanIndex(-1)
	, m_iChanShowNum(0)
	, m_iCopyChanIndex(0)
	, m_iChanCount(0)
	, m_lStartChannel(0)
	, m_dwAlarmOutNum(0)
	, m_dwDurationTime(0)
	, m_bOSDColor(FALSE)
    , m_iCurGroupNo(0)
    , m_dwBoundary(0)
    , m_bDepthMapEnable(FALSE)
    , m_bKeyEnable(FALSE)
    , m_bSelfBackColor(FALSE)
    , m_bySelfRed(0)
    , m_bySelfGreen(0)
    , m_bySelfBlue(0)
    , m_bYStreamEnable(FALSE)
{
	int i = 0; 
	for (i=0; i<MAX_CHANNUM_V40; i++)
	{	
		memset(&m_struMSCompressionCfg[i], 0, 5*sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG));
//		memset(&m_struPicCfg[i], 0, sizeof(NET_DVR_PICCFG_V30));
//		memset(&m_struCompressionCfg[i], 0, sizeof(NET_DVR_COMPRESSIONCFG_V30));      

	}

    m_pStruPicCfgV40 = new NET_DVR_PICCFG_V40[MAX_CHANNUM_V40];
    if (m_pStruPicCfgV40 != NULL)
    {
        memset(m_pStruPicCfgV40, 0, sizeof(NET_DVR_PICCFG_V40)*MAX_CHANNUM_V40);
    }

    for (i = 0; i< MAX_CHANNUM_V40; i++)
    {
        	m_bRemoteRecord[i] = FALSE;
    }
	for (i=0; i<5; i++)
	{
		memset(&m_struMSCond[i], 0, sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG_COND));
	}
    m_pCompresscfgAbility = new NET_DVR_COMPRESSIONCFG_ABILITY;
    if (m_pCompresscfgAbility != NULL)
    {
        memset(m_pCompresscfgAbility,0, sizeof(NET_DVR_COMPRESSIONCFG_ABILITY));
    }

	m_pbSetChannelPara = new BOOL[MAX_CHANNUM_V40];
	if(m_pbSetChannelPara != NULL)
	{
		memset(m_pbSetChannelPara, 0, sizeof(BOOL)*MAX_CHANNUM_V40);
	}
	
	m_pbGetChannelPara = new BOOL[MAX_CHANNUM_V40];
	if(m_pbGetChannelPara != NULL)
	{
		memset(m_pbGetChannelPara, 0, sizeof(BOOL)*MAX_CHANNUM_V40);
	}

	m_pStruRemoteRecCfg = new NET_DVR_RECORD_V30[MAX_CHANNUM_V40];
	
	if(m_pStruRemoteRecCfg != NULL)
	{	
		memset(m_pStruRemoteRecCfg,0, sizeof(NET_DVR_RECORD_V30) * MAX_CHANNUM_V40);
	}

	m_pStruRemoteRecCfgV40 = new NET_DVR_RECORD_V40[MAX_CHANNUM_V40];
	
	if (m_pStruRemoteRecCfgV40 != NULL)
	{
		memset(m_pStruRemoteRecCfgV40,0, sizeof(NET_DVR_RECORD_V40) * MAX_CHANNUM_V40);
	}

	m_pStruAudioIn = new NET_DVR_AUDIO_INPUT_PARAM[MAX_CHANNUM_V40];
	if(m_pStruAudioIn != NULL)
	{
		memset(m_pStruAudioIn,0, sizeof(NET_DVR_AUDIO_INPUT_PARAM));
	}

	m_pStruPOEAdapterType =  new NET_DVR_POE_CHANNEL_ADD_MODE[MAX_CHANNUM_V40];
	if (m_pStruPOEAdapterType != NULL)
	{
		memset(m_pStruPOEAdapterType,0, sizeof(NET_DVR_POE_CHANNEL_ADD_MODE));
	}

	m_pStruCabac = new NET_DVR_STREAM_CABAC[MAX_CHANNUM_V40];
	if (m_pStruCabac != NULL)
	{
		memset(m_pStruCabac,0, sizeof(NET_DVR_STREAM_CABAC));
	}
		
}

/*********************************************************
  Function:	~CSubDlgChanCfg
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CSubDlgChanCfg::~CSubDlgChanCfg()
{
    
    if (m_pStruPicCfgV40 != NULL)
    {
        delete [] m_pStruPicCfgV40;
        m_pStruPicCfgV40 = NULL;
    }

    if (m_pCompresscfgAbility != NULL)
    {
        delete m_pCompresscfgAbility;
        m_pCompresscfgAbility = NULL;
    }

	if(m_pbSetChannelPara != NULL)
	{
		delete[] m_pbSetChannelPara;
		m_pbSetChannelPara = NULL;
	}

	if(m_pbGetChannelPara != NULL)
	{
		delete[] m_pbGetChannelPara;
		m_pbGetChannelPara = NULL;
	}
	
	if(m_pbGetChannelPara != NULL)
	{
		delete[] m_pbGetChannelPara;
		m_pbGetChannelPara = NULL;
	}
 
	
	if(m_pStruRemoteRecCfg != NULL)
	{	
		delete[] m_pStruRemoteRecCfg;
		m_pStruRemoteRecCfg = NULL;
	}

    if (m_pStruRemoteRecCfgV40 != NULL)
    {
        delete[] m_pStruRemoteRecCfgV40;
        m_pStruRemoteRecCfgV40 = NULL;
    }
 
	if(m_pStruAudioIn != NULL)
	{
		delete[] m_pStruAudioIn;
		m_pStruAudioIn = NULL;
	}
	
 
	if (m_pStruPOEAdapterType != NULL)
	{
		delete[] m_pStruPOEAdapterType;
		m_pStruPOEAdapterType = NULL;
	}
	
	if (m_pStruCabac != NULL)
	{
		delete[] m_pStruCabac;
		m_pStruCabac = NULL;
	}
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgChanCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CSubDlgChanCfg)
    DDX_Control(pDX, IDC_COMBO_SVC, m_comSVC);
    DDX_Control(pDX, IDC_COMBO_VIDEOFORMAT, m_cmbVideoFormat);
    DDX_Control(pDX, IDC_COMBO_AUDIO_SAMPLING_RATE, m_comboSamplingRate);
    DDX_Control(pDX, IDC_COMBO_AUDIOBITARTE, m_comboAudioBitRate);
    DDX_Control(pDX, IDC_COMBO_POE_ADAPTER_TYPE, m_cmbPoeAdapterType);
    DDX_Control(pDX, IDC_COMBO_AUDIOIN_TYPE, m_comboAudioInType);
    DDX_Control(pDX, IDC_COMBO_VIDEO_ENC_COMPLEXITY, m_comboVideoEncComplexity);
    DDX_Control(pDX, IDC_COMBO_OSD_FONT, m_cmbOsdFont);
    DDX_Control(pDX, IDC_COMBO_HOUR_TYPE, m_comboHourType);
    DDX_Control(pDX, IDC_COMBO_VIDEO_TYPE, m_comboVideoType);
    DDX_Control(pDX, IDC_COMBO_AUDIO_TYPE, m_comboAudioType);
    DDX_Control(pDX, IDC_COMBO_COMPRESSION_TYPE, m_comboCompressionType);
    DDX_Check(pDX, IDC_CHK_HIDE_ALARM, m_bCheckHideAlarm);
    DDX_Check(pDX, IDC_CHK_VILOST, m_bCheckVILost);
    DDX_Check(pDX, IDC_CHK_AULOST2, m_bCheckAULost);
    DDX_Check(pDX, IDC_CHK_MOTION, m_bCheckMotion);
    DDX_Control(pDX, IDC_EDIT_REC_DELAY, m_comboRecDelay);
    DDX_Control(pDX, IDC_EDIT_PRERECORD_TIME, m_comboPreRecordTime);
    DDX_Check(pDX, IDC_CHK_HIDE_AREA, m_bCheckHideArea);
    DDX_Control(pDX, IDC_COMBO_CHAN, m_comboChanNum);
    DDX_Text(pDX, IDC_EDIT_CHANNEL_NAME, m_csChanName);
    DDX_Control(pDX, IDC_COMBO_IMAGE_QUALITY, m_comboImageQuality);
    DDX_Control(pDX, IDC_COMBO_STREAM_TYPE, m_comboStreamType);
    DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_comboResolution);
    DDX_Control(pDX, IDC_COMBO_BIT_RATE_TYPE, m_comboBitRateType);
    DDX_Control(pDX, IDC_COMBO_FRAME_RATE, m_comboFrameRate);
    DDX_Control(pDX, IDC_COMBO_MAX_BIT_RATE, m_comboBitRate);
    DDX_Control(pDX, IDC_COMBO_AVERAGE_VIDEO_BITRATE, m_comboAverageBitRate);
    DDX_Text(pDX, IDC_EDIT_BIT_RATE, m_iBitRate);
    DDX_Text(pDX, IDC_EDIT_AV_BIT_RATE, m_iAvBitRate);
    DDX_Text(pDX, IDC_EDIT_FRAME_I_INTERVAL, m_iFrameIInterval);
    DDX_Control(pDX, IDC_COMBO_FRAME_BP_INTERVAL, m_comboFrameBPInterval);
    DDX_Check(pDX, IDC_CHK_RECORD, m_bCheckRecord);
    DDX_Check(pDX, IDC_CHK_OSD, m_bCheckOsd);
    DDX_Text(pDX, IDC_EDIT_OSD_X, m_iOsdX);
    DDX_Text(pDX, IDC_EDIT_OSD_Y, m_iOsdY);
    DDX_Check(pDX, IDC_CHK_DISPLAY_WEEK, m_bChkDispWeek);
    DDX_Control(pDX, IDC_COMBO_OSD_ATTRIB, m_comboOsdAttrib);
    DDX_Control(pDX, IDC_COMBO_OSD_TYPE, m_comboOsdType);
    DDX_Control(pDX, IDC_COMBO_ALIGNMENT, m_comboAlignment);
    DDX_Check(pDX, IDC_CHK_CHAN_NAME, m_bCheckChanName);
    DDX_Text(pDX, IDC_EDIT_CHAN_NAME_X, m_iChanNameX);
    DDX_Text(pDX, IDC_EDIT_CHAN_NAME_Y, m_iChanNameY);
    DDX_Control(pDX, IDC_COMBO_COPY_CHAN, m_comboCopyChan);
    DDX_Text(pDX, IDC_EDIT_DURATION_TIME, m_dwDurationTime);
    DDX_Check(pDX, IDC_CHK_REDUNDANCY_REC, m_bChkRedundancyRec);
    DDX_Check(pDX, IDC_CHK_AUDIO_REC, m_bChkAudioRec);
    DDX_Check(pDX, IDC_CHK_EVENT_COMPRESS, m_bEventCompress);
    DDX_Check(pDX, IDC_CHECK_CABAC, m_bCabacCheck);
    DDX_Text(pDX, IDC_EDIT_VOLUME, m_byVolume);
    DDX_Check(pDX, IDC_CHECK_CALLBACK_CHANNEL, m_bCallback);
    DDX_Check(pDX, IDC_CHECK_BACKUP, m_bBackup);
    DDX_Text(pDX, IDC_EDIT_LOCK_DURATION, m_wLockDuration);
    DDX_Control(pDX, IDC_CMB_STREAM_TYPE, m_cmbStreamType);
    DDX_Check(pDX, IDC_CHK_ENABLE_SVC, m_bChkEnableSvc);
    DDX_Check(pDX, IDC_CHK_NOSIE_FILITER, m_bEnableNoiseFilter);
    DDX_Check(pDX, IDC_CHK_COLOR, m_bOSDColor);
    DDX_Text(pDX, IDC_EDIT_OSD_COLOR_B, m_byOsdColorB);
    DDX_Text(pDX, IDC_EDIT_OSD_COLOR_G, m_byOsdColorG);
    DDX_Text(pDX, IDC_EDIT_OSD_COLOR_R, m_byOsdColorR);
    DDX_Text(pDX, IDC_EDIT_STREAMSMOOTH, m_byStreamSmooth);
    DDX_Check(pDX, IDC_CHK_AUDIO_EXTRA, m_bChkAudioExtra);
    DDX_Check(pDX, IDC_CHK_SMARTCODEC, m_bChkSmartCodec);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_BOUNDARY, m_dwBoundary);
    DDX_Check(pDX, IDC_CHK_ENABLE_DEPTH_MAP, m_bDepthMapEnable);
    DDX_Check(pDX, IDC_CHECK_KEY_ENABLE, m_bKeyEnable);
    DDX_Check(pDX, IDC_SELF_BACK, m_bSelfBackColor);
    DDX_Text(pDX, IDC_EDIT_OSD_COLOR_RF, m_bySelfRed);
    DDX_Text(pDX, IDC_EDIT_OSD_COLOR_GF, m_bySelfGreen);
    DDX_Text(pDX, IDC_EDIT_OSD_COLOR_BF, m_bySelfBlue);
    DDX_Check(pDX, IDC_CHECK_YSTREAM, m_bYStreamEnable);
}

/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CSubDlgChanCfg, CDialog)
	//{{AFX_MSG_MAP(CSubDlgChanCfg)	
	ON_CBN_SELCHANGE(IDC_COMBO_MAX_BIT_RATE, OnCbnSelchangeComboMaxBitRate)
    ON_CBN_SELCHANGE(IDC_COMBO_AVERAGE_VIDEO_BITRATE, OnCbnSelchangeComboAvcBitRate)
	ON_CBN_SELCHANGE(IDC_COMBO_COMPRESSION_TYPE, OnCbnSelchangeComboCompressionType)
	ON_BN_CLICKED(IDC_BTN_CMP_OK, OnBnClickedBtnCmpOk)
	ON_BN_CLICKED(IDC_BTN_REMOTE_RECORD_SETUP, OnBnClickedBtnRemoteRecordSetup)
	ON_BN_CLICKED(IDC_BTN_HIDE_SETUP, OnBnClickedBtnHideSetup)
	ON_BN_CLICKED(IDC_BTN_MOTION_SETUP, OnBnClickedBtnMotionSetup)
	ON_BN_CLICKED(IDC_BTN_HIDE_ALARM_SETUP, OnBnClickedBtnHideAlarmSetup)
	ON_BN_CLICKED(IDC_BTN_VILOST_SETUP, OnBnClickedBtnVilostSetup)
	ON_BN_CLICKED(IDC_BTN_AULOST_SETUP2, OnBnClickedBtnAUlostSetup)
	ON_BN_CLICKED(IDC_BTN_STRING, OnBnClickedBtnString)
	ON_BN_CLICKED(IDC_BTN_CHAN_COPY, OnBnClickedBtnChanCopy)
	ON_BN_CLICKED(ID_BTN_CHAN_CFG_OK, OnBnClickedBtnChanCfgOk)
	ON_BN_CLICKED(ID_BTN_CHAN_CFG_EXIT, OnBnClickedBtnChanCfgExit)
	ON_BN_CLICKED(IDC_CHK_RECORD, OnBnClickedChkRecord)
	ON_BN_CLICKED(IDC_CHK_HIDE_AREA, OnBnClickedChkHideArea)
	ON_BN_CLICKED(IDC_CHK_OSD, OnBnClickedChkOsd)
	ON_BN_CLICKED(IDC_CHK_CHAN_NAME, OnBnClickedChkChanNamePos)
	ON_CBN_SELCHANGE(IDC_COMBO_CHAN, OnCbnSelchangeComboChan)
	ON_CBN_SELCHANGE(IDC_COMBO_COPY_CHAN, OnCbnSelchangeComboCopyChan)
	ON_BN_CLICKED(IDC_CHK_MOTION, OnBnClickedChkMotion)
	ON_BN_CLICKED(IDC_CHK_HIDE_ALARM, OnBnClickedChkHideAlarm)
	ON_BN_CLICKED(IDC_CHK_VILOST, OnBnClickedChkVilost)
	ON_BN_CLICKED(IDC_CHK_AULOST2, OnBnClickedChkAUlost)
	ON_CBN_SELCHANGE(IDC_COMBO_FRAME_RATE, OnCbnSelchangeComboFrameRate)
	ON_BN_CLICKED(IDC_BTN_JPEG_CAPTURE, OnBtnJpegCapture)
	ON_BN_CLICKED(IDC_BTN_DISK_QUOTA, OnBtnDiskQuota)
	ON_BN_CLICKED(IDC_BUTTON_LIMIT_FRAME_UPDATE, OnButtonLimitFrameUpdate)
	ON_BN_CLICKED(IDC_BUTTON_VIDEO_IN_EFFECT, OnButtonVideoInEffect)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG_CAMERA_TYPE, OnButtonConfigCameraType)
	ON_BN_CLICKED(IDC_BUTTON_INQUIRY_TIME_SPAN, OnButtonInquiryTimeSpan)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_INDEX, OnButtonUpdateIndex)
	ON_BN_CLICKED(IDC_BTN_VIDEO_OUTPUT, OnBtnVideoOutput)
	ON_BN_CLICKED(IDC_BTN_WD_ENABLE, OnBtnWdEnable)
	ON_BN_CLICKED(IDC_BTN_VEDIOPACKAGE, OnBtnVediopackage)
	ON_BN_CLICKED(IDC_BTN_DEVICE_LANGUAGE_ENCODE, OnBtnDeviceLanguageEncode)
	ON_BN_CLICKED(IDC_CHK_COLOR, OnChkOSDColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// CSubDlgChanCfg message handlers

/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CSubDlgChanCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
    AddStreamType();
	AddResolution();
	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);
	
	OnChkOSDColor(); 
	return TRUE; 
}

/*********************************************************
Function:	CheckInitParam
Desc:		Check and update init paramerters
Input:	
Output:	
Return:	TRUE,device parameters correct, init device;FALSE,do not init
**********************************************************/
BOOL CSubDlgChanCfg::CheckInitParam()
{
	UpdateData(TRUE);
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();

	if (iDeviceIndex == -1)
	{
		return FALSE;
	}
	
// 	if (g_pMainDlg->IsCurDevMatDec(iDeviceIndex))
// 	{
// 		return FALSE;
// 	}

    if (m_iDeviceIndex == iDeviceIndex && m_iCurChanIndex != -1 && m_iCurGroupNo == g_struDeviceInfo[m_iDeviceIndex].iGroupNO)
	{
		return TRUE;
	}
	else
	{
		m_iDeviceIndex = iDeviceIndex;
		m_lLoginID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
        m_iCurGroupNo = g_struDeviceInfo[m_iDeviceIndex].iGroupNO;
        m_lStartChannel = g_struDeviceInfo[m_iDeviceIndex].iStartChan + g_struDeviceInfo[m_iDeviceIndex].iGroupNO * 64;//起始通道号加上组号
		m_iChanCount = g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum;
		m_dwAlarmOutNum = g_struDeviceInfo[m_iDeviceIndex].iAlarmOutNum;
	}


	m_bCheckHideAlarm = FALSE;
	m_bCheckVILost = FALSE;
	m_bCheckAULost = FALSE;
	m_bCheckMotion = FALSE;

	m_bCheckHideArea = FALSE;
	m_csChanName = _T("");

	m_iBitRate = 0;
    m_iAvBitRate = 0;
	m_iFrameIInterval = 0;
	m_comboRecDelay.SetCurSel(-1);
	m_comboPreRecordTime.SetCurSel(-1);
	m_comboChanNum.SetCurSel(-1);
	m_comboImageQuality.SetCurSel(-1);
	m_comboStreamType.SetCurSel(-1);
	m_comboResolution.SetCurSel(-1);
	m_comboBitRateType.SetCurSel(-1);
	m_comboFrameRate.SetCurSel(-1);
	m_comboBitRate.SetCurSel(-1);
    m_comboAverageBitRate.SetCurSel(-1);
	m_comboFrameBPInterval.SetCurSel(-1);
	m_comboStreamType.SetCurSel(-1);
	m_comboOsdAttrib.SetCurSel(-1);
	m_comboOsdType.SetCurSel(-1);
	m_comboHourType.SetCurSel(-1);
	m_bCheckRecord = FALSE;
	m_bCheckOsd = FALSE;
	m_iOsdX = 0;
	m_iOsdY = 0;
	m_bChkDispWeek = FALSE;
	m_bCheckChanName = FALSE;
	m_iChanNameX = 0;
	m_iChanNameY = 0;
	m_iCompressionTypeSel = 0;
	m_comboCopyChan.ResetContent();
	m_comboChanNum.ResetContent();

	if (m_lLoginID < 0)
	{
		return FALSE;
	}


	m_iCopyChanIndex = -1;
	
    //GetStreamTypeAbility();
    int i=0;
    CString sTemp;
    DWORD dwChanShow = 0;//display channel number
    DWORD iCopyIndex = 0;
	char szLan[128] = {0};
 
	
	//2008-9-6 12:54	
	m_comboCompressionType.SetCurSel(0);
	g_StringLanType(szLan, "全部通道", "All Channels");
	m_comboCopyChan.AddString(szLan);
    int iCount = 0;
    for (i=0; i < MAX_CHANNUM_V30; i++)
    {
        STRU_CHANNEL_INFO *pChannelInfo = &(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i]);
        if (pChannelInfo->iChanIndex < 0)
        {
            break;
        }
        
        dwChanShow = pChannelInfo->iChannelNO;
        
        
        m_pbSetChannelPara[i] = FALSE;
        m_pbGetChannelPara[i] = FALSE;
        m_bRemoteRecord[i] = FALSE;
        if (pChannelInfo->iChanType  == DEMO_CHANNEL_TYPE_ANALOG)
        {
            if (g_struDeviceInfo[iDeviceIndex].iDeviceType == DS_B20_MSU_NP || \
                g_struDeviceInfo[iDeviceIndex].iDeviceType == DS_MMC_B20_CLASS || \
                g_struDeviceInfo[iDeviceIndex].iDeviceType == DS_B21_MCU_NP_CLASS || \
                g_struDeviceInfo[iDeviceIndex].iDeviceType == DS_C20N_VWMS || \
                g_struDeviceInfo[iDeviceIndex].iDeviceType == DS_Y10_MCU) //B20/B21主控
			{
				sTemp.Format("Camera_%d_%d_%d", dwChanShow>>24, (dwChanShow>>16)&0x000000ff, dwChanShow&0x000000ff);
			}
			else
			{
				sTemp.Format(ANALOG_C_FORMAT, dwChanShow);
			}
        }
        else if (pChannelInfo->iChanType  == DEMO_CHANNEL_TYPE_IP)
        {
            //sTemp.Format(DIGITAL_C_FORMAT, dwChanShow - g_struDeviceInfo[iDeviceIndex].pStruIPParaCfgV40[0].dwStartDChan + 1);
            sTemp.Format("%s",pChannelInfo->chChanName);
        }
        else
        {
            sTemp.Format("NO_Type%d", dwChanShow);
        }
		m_comboChanNum.AddString(sTemp);
        m_comboChanNum.SetItemData(iCount++, pChannelInfo->iChanIndex);
    }
	for (i = 0; i < g_struDeviceInfo[iDeviceIndex].byMirrorChanNum&&i < 16; i++)
	{
		STRU_CHANNEL_INFO *pChannelInfo = &(g_struDeviceInfo[iDeviceIndex].struMirrorChan[i]);
		if (pChannelInfo->iChanIndex < 0)
        {
            break;
        }
        
        dwChanShow = pChannelInfo->iChannelNO;
		sTemp.Format("%s", pChannelInfo->chChanName);
		m_comboChanNum.AddString(sTemp);
        m_comboChanNum.SetItemData(iCount++, pChannelInfo->iChanIndex);
		
	}
    if (m_iCurChanIndex < 0)
    {
        m_iCurChanIndex = 0;
    }
    GetCurChanInfo(m_iCurChanIndex);
	return TRUE;
}

BOOL CSubDlgChanCfg::GetCurChanInfo(int iChanIndex)
{
    UpdateData(TRUE);
    int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    
    int i = 0;
    CString sTemp;
    DWORD dwReturned = 0;
    DWORD dwChanShow = 0;//display channel number
    DWORD iCopyIndex = 0;
    char szLan[128] = {0};
    
    i = iChanIndex;
    if (iChanIndex < 0)
    {
        i = 0;
        m_iCurChanIndex = 0;
    }
    
    STRU_CHANNEL_INFO *pChannelInfo;
    if ((g_struDeviceInfo[iDeviceIndex].byMirrorChanNum > 0) && (iChanIndex >= MIRROR_CHAN_INDEX))
    {
        pChannelInfo = &(g_struDeviceInfo[iDeviceIndex].struMirrorChan[i - MIRROR_CHAN_INDEX]);
	//	m_iCurChanIndex = m_iCurChanIndex - g_struDeviceInfo[iDeviceIndex].struMirrorChan[i + 1 -g_struDeviceInfo[iDeviceIndex].wStartMirrorChanNo]
    }
	else
	{
		pChannelInfo = &(g_struDeviceInfo[iDeviceIndex].pStruChanInfo[i]);
	}

    if (pChannelInfo->iChanIndex < 0)
    {
        
        return FALSE;
    }
    
    dwChanShow = pChannelInfo->iChannelNO;
    
    int k = 0;
    for (k = 0; k < m_comboChanNum.GetCount(); k++)
    {
        if (m_comboChanNum.GetItemData(k) == m_iCurChanIndex)
        {
            break;
        }
    }

    if (k == m_comboChanNum.GetCount())
    {
        m_comboChanNum.SetCurSel(-1);
    }
    else
    {
        m_comboChanNum.SetCurSel(k);
    }
    
    
    m_pbSetChannelPara[i] = FALSE;
    m_pbGetChannelPara[i] = FALSE;
    m_bRemoteRecord[i] = FALSE;
    
    DWORD dwStatus[5] = {0};
    
    if (pChannelInfo->bEnable)
    {
        memset(&m_struMSCompressionCfg[i][0], 0, 5*sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG));
        
        for(int j=0; j<5; j++)
        {			
            m_struMSCond[j].dwSize = sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG_COND);
            m_struMSCond[j].struStreamInfo.dwChannel = dwChanShow;
            m_struMSCond[j].struStreamInfo.dwSize = sizeof(NET_DVR_STREAM_INFO);
            m_struMSCond[j].dwStreamType = j; 
            
        }
        
        
        if (!NET_DVR_GetDeviceConfig(m_lLoginID, NET_DVR_GET_MULTI_STREAM_COMPRESSIONCFG, 5,\
            &m_struMSCond[0], 5*sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG_COND), &dwStatus[0], &m_struMSCompressionCfg[i][0], 5*sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG)))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_GET_MULTI_STREAM_COMPRESSIONCFG", dwChanShow);
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_MULTI_STREAM_COMPRESSIONCFG chan[%d]", dwChanShow);	
        }
        
        
        memset(&m_pStruPicCfgV40[i], 0, sizeof(m_pStruPicCfgV40[i]));
        
        if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_PICCFG_V40,dwChanShow, &m_pStruPicCfgV40[i], sizeof(m_pStruPicCfgV40[i]), &dwReturned))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_GET_PICCFG_V40 , Status[%d]", dwChanShow, dwReturned);
            //return FALSE;
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_PICCFG_V40 chan[%d], Status[%d]", dwChanShow, dwReturned);	
        }
        
		memset(&m_pStruRemoteRecCfg[i], 0, sizeof(m_pStruRemoteRecCfg[i]));
		memset(&m_pStruRemoteRecCfgV40[i], 0, sizeof(m_pStruRemoteRecCfgV40[i]));
		//         if (!NET_DVR_GetDVRConfig(m_lLoginID,NET_DVR_GET_RECORDCFG_V30, dwChanShow, &m_pStruRemoteRecCfg[i], sizeof(NET_DVR_RECORD_V30), &dwReturned))	
		//         {
		//             g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_GET_RECORDCFG_V30", dwChanShow);	
		//             //return FALSE;
		//         }
		//         else
		//         {
		//             g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_RECORDCFG_V30 chan[%d]", dwChanShow);	
		//         }
		
		if (!NET_DVR_GetDVRConfig(m_lLoginID,NET_DVR_GET_RECORDCFG_V40, dwChanShow, &m_pStruRemoteRecCfgV40[i], sizeof(NET_DVR_RECORD_V40), &dwReturned))	
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_GET_RECORDCFG_V40", dwChanShow);			
            //return FALSE;
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_RECORDCFG_V40 chan[%d]", dwChanShow);	
			
			
			m_pStruRemoteRecCfg[i].byAudioRec = m_pStruRemoteRecCfgV40[i].byAudioRec;
			m_pStruRemoteRecCfg[i].byPassbackRecord = m_pStruRemoteRecCfgV40[i].byPassbackRecord;
			m_pStruRemoteRecCfg[i].byRecordBackup = m_pStruRemoteRecCfgV40[i].byRecordBackup;
			
			m_pStruRemoteRecCfg[i].byRedundancyRec = m_pStruRemoteRecCfgV40[i].byRedundancyRec;
			m_pStruRemoteRecCfg[i].byStreamType = m_pStruRemoteRecCfgV40[i].byStreamType;
			m_pStruRemoteRecCfg[i].bySVCLevel = m_pStruRemoteRecCfgV40[i].bySVCLevel;
			m_pStruRemoteRecCfg[i].byExtraSaveAudio = m_pStruRemoteRecCfgV40[i].byExtraSaveAudio;

			
			m_pStruRemoteRecCfg[i].dwPreRecordTime = m_pStruRemoteRecCfgV40[i].dwPreRecordTime;
			m_pStruRemoteRecCfg[i].dwRecord = m_pStruRemoteRecCfgV40[i].dwRecord;
			m_pStruRemoteRecCfg[i].dwRecorderDuration = m_pStruRemoteRecCfgV40[i].dwRecorderDuration;
			
			m_pStruRemoteRecCfg[i].dwRecordTime = m_pStruRemoteRecCfgV40[i].dwRecordTime;
			m_pStruRemoteRecCfg[i].wLockDuration = m_pStruRemoteRecCfgV40[i].wLockDuration;
			for (int j = 0; j < MAX_DAYS; j++)
			{
				m_pStruRemoteRecCfg[i].struRecAllDay[j].byRecordType = m_pStruRemoteRecCfgV40[i].struRecAllDay[j].byRecordType;
			    m_pStruRemoteRecCfg[i].struRecAllDay[j].wAllDayRecord = m_pStruRemoteRecCfgV40[i].struRecAllDay[j].byAllDayRecord;
				for(int k = 0; k < MAX_TIMESEGMENT_V30; k++)
				{
					m_pStruRemoteRecCfg[i].struRecordSched[j][k].byRecordType = m_pStruRemoteRecCfgV40[i].struRecordSched[j][k].byRecordType;
					m_pStruRemoteRecCfg[i].struRecordSched[j][k].struRecordTime = m_pStruRemoteRecCfgV40[i].struRecordSched[j][k].struRecordTime;
				}	
			}
			
        }
        
        memset(&m_pStruAudioIn[i], 0, sizeof(m_pStruAudioIn[i]));
        if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_AUDIO_INPUT, dwChanShow, &m_pStruAudioIn[i], sizeof(NET_DVR_AUDIO_INPUT_PARAM), &dwReturned))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_GET_AUDIO_INPUT", dwChanShow);
            //return FALSE;
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_AUDIO_INPUT chan[%d]", dwChanShow);	
        }
        
        m_comboCopyChan.AddString(sTemp);
        m_comboCopyChan.SetItemData(iCopyIndex, i);	
        iCopyIndex++;//0 map to all channels
        m_pbGetChannelPara[i] = TRUE;
        
        memset(&m_pStruCabac[i], 0, sizeof(m_pStruCabac[i]));
        if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_STREAM_CABAC, dwChanShow, &m_pStruCabac[i], sizeof(NET_DVR_STREAM_CABAC), &dwReturned))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_GET_STREAM_CABAC", dwChanShow);
            //return FALSE;
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_STREAM_CABAC chan[%d]", dwChanShow);	
        }
        
        memset(&m_pStruPOEAdapterType[i], 0, sizeof(m_pStruPOEAdapterType[i]));
        if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_POE_CHANNEL_ADD_MODE, dwChanShow, &m_pStruPOEAdapterType[i], sizeof(NET_DVR_POE_CHANNEL_ADD_MODE), &dwReturned))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_GET_POE_CHANNEL_ADD_MODE", dwChanShow);
            return FALSE;
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_POE_CHANNEL_ADD_MODE chan[%d]", dwChanShow);	
        }
    }
    
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_CFG");
    return TRUE;
}
/*********************************************************
Function:	CurCfgUpdate
Desc:		Update device parameters and refreshthecontrols
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgChanCfg::CurCfgUpdate(int iChanIndex)
{ 
	char cTemp[100] = {0};
	int i = 0;
	char szLan[128] = {0};
    BOOL bFind = FALSE;
	if (iChanIndex == -1)
	{//channel index may be -1 and select a node on the device list, the default value is set as the first valid index value
		for (i=0; i<MAX_CHANNUM_V40; i++)
		{
			if (g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].bEnable)
			{
                m_iCurChanIndex = i;
                bFind = TRUE;
				break;
			}
		}
        if (!bFind)
        {
            return;
        }
	}
	else
	{
		m_iCurChanIndex = iChanIndex;
	}

    GetCurChanInfo(m_iCurChanIndex);
    // As the zero chan do  noting
    if (m_iCurChanIndex >= ZERO_CHAN_INDEX)
    {
        AfxMessageBox("Not support zero chan in the page");
        return;
    }

	//*** 0<=m_iCurChanIndex<= 64*2***//
	DEMO_CHANNEL_TYPE iChannelType = g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[m_iCurChanIndex].iChanType;

    m_lLoginID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	if (iChannelType ==  DEMO_CHANNEL_TYPE_ANALOG)
	{
		GetDlgItem(IDC_BTN_STRING)->EnableWindow(TRUE);	
	}
	else
	{
		GetDlgItem(IDC_BTN_STRING)->EnableWindow(TRUE);
	}


	m_comboCopyChan.SetCurSel(0);
	if ((g_struDeviceInfo[m_iDeviceIndex].byMirrorChanNum > 0)&&(iChanIndex >= g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum))
    {
		m_iChanShowNum = g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[m_iCurChanIndex - MIRROR_CHAN_INDEX].iChannelNO;
    }
	else
	{
		m_iChanShowNum = g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[m_iCurChanIndex].iChannelNO;
	}

	//compression parameters
    if (GetCompressCfgAbility(m_iChanShowNum))
    {
        //GetStreamTypeAbility();
        m_comboCompressionType.SetCurSel(0);
     //   GetResolutionAbility();
        GetBitrateAbility();
        GetBitrateTypeAbility();
        GetFrameAbility();
    }
    else
    {
        AfxMessageBox("Get compression ability failed");
    }

    UpdateCompressionInfo();
	
	//recording paramerters
	m_bCheckRecord = m_pStruRemoteRecCfg[m_iCurChanIndex].dwRecord;
	GetDlgItem(IDC_BTN_REMOTE_RECORD_SETUP)->EnableWindow(m_bCheckRecord);
	m_comboRecDelay.SetCurSel(m_pStruRemoteRecCfg[m_iCurChanIndex].dwRecordTime);
	m_comboPreRecordTime.SetCurSel(m_pStruRemoteRecCfg[m_iCurChanIndex].dwPreRecordTime);
	m_cmbStreamType.SetCurSel(m_pStruRemoteRecCfg[m_iCurChanIndex].byStreamType);
	m_bBackup = m_pStruRemoteRecCfg[m_iCurChanIndex].byRecordBackup;
	m_bChkAudioExtra = m_pStruRemoteRecCfg[m_iCurChanIndex].byExtraSaveAudio;
	m_wLockDuration = m_pStruRemoteRecCfg[m_iCurChanIndex].wLockDuration;
	m_bCallback = m_pStruRemoteRecCfg[m_iCurChanIndex].byPassbackRecord;
// 	if (0xffffffff == m_struRemoteRecCfg[m_iCurChanIndex].dwRecorderDuration)
// 	{
// 		GetDlgItem(IDC_EDIT_DURATION_TIME)->EnableWindow(FALSE);
// 	}
// 	else
// 	{
// 		GetDlgItem(IDC_EDIT_DURATION_TIME)->EnableWindow(TRUE);
// 		m_dwDurationTime = m_struRemoteRecCfg[m_iCurChanIndex].dwRecorderDuration;
// 	}
	//录像保存时间
	m_dwDurationTime = m_pStruRemoteRecCfg[m_iCurChanIndex].dwRecorderDuration;

	if (0xff == m_pStruRemoteRecCfg[m_iCurChanIndex].byRedundancyRec)
	{
		GetDlgItem(IDC_CHK_REDUNDANCY_REC)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_CHK_REDUNDANCY_REC)->EnableWindow(TRUE);
		m_bChkRedundancyRec = m_pStruRemoteRecCfg[m_iCurChanIndex].byRedundancyRec;
	}

	if (0xff == m_pStruRemoteRecCfg[m_iCurChanIndex].byAudioRec)
	{
		GetDlgItem(IDC_CHK_AUDIO_REC)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_CHK_AUDIO_REC)->EnableWindow(TRUE);
		m_bChkAudioRec = m_pStruRemoteRecCfg[m_iCurChanIndex].byAudioRec;
	}

   
    //image parameters with V40
 	ZeroMemory(cTemp, 100);
    memcpy(cTemp, m_pStruPicCfgV40[m_iCurChanIndex].sChanName, NAME_LEN);
    m_csChanName.Format("%s",cTemp);
    m_bCheckHideArea = m_pStruPicCfgV40[m_iCurChanIndex].dwEnableHide;
    GetDlgItem(IDC_BTN_HIDE_SETUP)->EnableWindow(m_bCheckHideArea);
    m_bCheckMotion = m_pStruPicCfgV40[m_iCurChanIndex].struMotion.byEnableHandleMotion;
    m_bKeyEnable = m_pStruPicCfgV40[m_iCurChanIndex].struMotion.byKeyingEnable;
    GetDlgItem(IDC_BTN_MOTION_SETUP)->EnableWindow(m_bCheckMotion);
    if (m_pStruPicCfgV40[m_iCurChanIndex].struHideAlarm.dwEnableHideAlarm > 0)
    {
        m_bCheckHideAlarm = TRUE;
    }
    else
    {
        m_bCheckHideAlarm = FALSE;
    }
    GetDlgItem(IDC_BTN_HIDE_ALARM_SETUP)->EnableWindow(m_bCheckHideAlarm);
    
    m_bCheckChanName = m_pStruPicCfgV40[m_iCurChanIndex].dwShowChanName;
    EnableChanname(m_bCheckChanName);
    m_iChanNameX = m_pStruPicCfgV40[m_iCurChanIndex].wShowNameTopLeftX;
    m_iChanNameY = m_pStruPicCfgV40[m_iCurChanIndex].wShowNameTopLeftY;
    m_bCheckOsd = m_pStruPicCfgV40[m_iCurChanIndex].dwShowOsd;
    EnableOsd(m_bCheckOsd);
    m_iOsdX = m_pStruPicCfgV40[m_iCurChanIndex].wOSDTopLeftX;
    m_iOsdY = m_pStruPicCfgV40[m_iCurChanIndex].wOSDTopLeftY;
    m_bChkDispWeek = m_pStruPicCfgV40[m_iCurChanIndex].byDispWeek;
    //2011-07-18 osd不显示时，显示方式默认为第一种
    if (!m_bCheckOsd && m_pStruPicCfgV40[m_iCurChanIndex].byOSDAttrib == 0)
    {
        m_pStruPicCfgV40[m_iCurChanIndex].byOSDAttrib = 1;
    }
    m_comboOsdAttrib.SetCurSel(m_pStruPicCfgV40[m_iCurChanIndex].byOSDAttrib-1);
    m_comboOsdType.SetCurSel(m_pStruPicCfgV40[m_iCurChanIndex].byOSDType);

	if (m_pStruPicCfgV40[m_iCurChanIndex].byFontSize == 8)
	{
		g_StringLanType(szLan, "字体大小返回不支持的索引8,请更改字体大小配置!", \
			"The font size is not supported by the index returned 8, please change the font size configuration!");
		AfxMessageBox(szLan);
	}

    m_bOSDColor = m_pStruPicCfgV40[m_iCurChanIndex].byOSDColorType;
    m_comboAlignment.SetCurSel(m_pStruPicCfgV40[m_iCurChanIndex].byAlignment);
	UpdateData(FALSE);
	OnChkOSDColor(); 

	m_byOsdColorR = m_pStruPicCfgV40[m_iCurChanIndex].struOsdColor.byRed;
	m_byOsdColorG = m_pStruPicCfgV40[m_iCurChanIndex].struOsdColor.byGreen;
	m_byOsdColorB = m_pStruPicCfgV40[m_iCurChanIndex].struOsdColor.byBlue;
    m_dwBoundary = m_pStruPicCfgV40[m_iCurChanIndex].dwBoundary;

    m_bSelfBackColor = m_pStruPicCfgV40[m_iCurChanIndex].byOSDBkColorMode;
    m_bySelfBlue = m_pStruPicCfgV40[m_iCurChanIndex].struOsdBkColor.byBlue;
    m_bySelfGreen = m_pStruPicCfgV40[m_iCurChanIndex].struOsdBkColor.byGreen;
    m_bySelfRed = m_pStruPicCfgV40[m_iCurChanIndex].struOsdBkColor.byRed;
	
    m_cmbVideoFormat.SetCurSel(m_pStruPicCfgV40[m_iCurChanIndex].dwVideoFormat);
    if (m_pStruPicCfgV40[m_iCurChanIndex].byFontSize == 0xff)
    {
        m_cmbOsdFont.SetCurSel(7);
    }
    else
    {
        m_cmbOsdFont.SetCurSel(m_pStruPicCfgV40[m_iCurChanIndex].byFontSize);
    }
    m_comboHourType.SetCurSel(m_pStruPicCfgV40[m_iCurChanIndex].byHourOSDType);
	m_bCheckVILost = (BOOL)m_pStruPicCfgV40[m_iCurChanIndex].struVILost.dwEnableVILostAlarm;
	m_bCheckAULost = (BOOL)m_pStruPicCfgV40[m_iCurChanIndex].struAULost.dwEnableVILostAlarm;
	GetDlgItem(IDC_BTN_AULOST_SETUP2)->EnableWindow(m_bCheckAULost);

	GetDlgItem(IDC_BTN_VILOST_SETUP)->EnableWindow(m_bCheckVILost);
// 	m_bChkAuLost = m_struPicCfg[m_iCurChanIndex].struAULost.byEnableHandleVILost;
// 	GetDlgItem(IDC_BTN_AULOST_SETUP)->EnableWindow(m_bChkAuLost);
	GetDlgItem(ID_BTN_CHAN_CFG_OK)->EnableWindow(TRUE);

	m_comboAudioInType.SetCurSel(m_pStruAudioIn[m_iCurChanIndex].byAudioInputType);
	m_byVolume = m_pStruAudioIn[m_iCurChanIndex].byVolume;
	m_bEnableNoiseFilter = m_pStruAudioIn[m_iCurChanIndex].byEnableNoiseFilter;
	

	m_bCabacCheck = m_pStruCabac[m_iCurChanIndex].byCabacEnable;
	m_cmbPoeAdapterType.SetCurSel(m_pStruPOEAdapterType[m_iCurChanIndex].byAddMode);
    UpdateData(FALSE);
}

/*********************************************************
  Function:	OnCbnSelchangeComboChan
  Desc:		get channel paramerets and refresh the control
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnCbnSelchangeComboChan()
{
	UpdateData(TRUE);
	int iChanIndex  = m_comboChanNum.GetCurSel();
	CurCfgUpdate(iChanIndex);
}

/*********************************************************
  Function:	OnBnClickedBtnRemoteRecordSetup
  Desc:		remote recording schedule
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedBtnRemoteRecordSetup()
{
	CDlgRemoteRecordSchedule dlg;
    dlg.m_lServerID = m_lLoginID;
    dlg.m_lChannel = g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[m_iCurChanIndex].iChannelNO;     
    dlg.m_iDevIndex = m_iDeviceIndex;

	dlg.m_struRemoteRecSchedule = &(m_pStruRemoteRecCfg[m_iCurChanIndex]);
	if (dlg.DoModal() == IDOK)
	{
		m_pbSetChannelPara[m_iCurChanIndex] = TRUE;
		g_bMustReboot = g_pMainDlg->IsNeedRebootDevType();
	}
}


/*********************************************************
  Function:	OnBnClickedBtnHideSetup
  Desc:		privacy mask setting
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedBtnHideSetup()
{
	CDlgRemoteHideArea dlg;
	int i = 0;

	for (i=0; i<MAX_SHELTERNUM; i++)
	{
		memcpy(&(dlg.m_struShelter[i]), &(m_pStruPicCfgV40[m_iCurChanIndex].struShelter[i]),sizeof(NET_DVR_SHELTER));
	}
	dlg.m_iChanShowNum = m_iChanShowNum;
	dlg.m_lLoginID = m_lLoginID;
	if (dlg.DoModal() == IDOK)
	{
		for (i=0; i<MAX_SHELTERNUM; i++)
		{
			memcpy(&(m_pStruPicCfgV40[m_iCurChanIndex].struShelter[i]), &(dlg.m_struShelter[i]),sizeof(NET_DVR_SHELTER));
		}
		m_pbSetChannelPara[m_iCurChanIndex] = TRUE;
	}
}

/*********************************************************
  Function:	OnBnClickedBtnMotionSetup
  Desc:		motion detect schedule, zone, etc
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedBtnMotionSetup()
{
	CDlgRemoteMotionDetect dlgRemoteMotionDetect;

//	g_lpMotionDetect = &(m_struPicCfg[m_iCurChanIndex].struMotion);
    g_lpMotionDetectV40 = &(m_pStruPicCfgV40[m_iCurChanIndex].struMotion);
	dlgRemoteMotionDetect.m_iChanShowNum = m_iChanShowNum;
	dlgRemoteMotionDetect.m_lLoginID = m_lLoginID;
	dlgRemoteMotionDetect.m_dwAlarmOutNum = m_dwAlarmOutNum;
	dlgRemoteMotionDetect.m_iChanCount = m_iChanCount;
	dlgRemoteMotionDetect.m_dwDevIndex = m_iDeviceIndex;
	if (dlgRemoteMotionDetect.DoModal() == IDOK)
	{
		m_pbSetChannelPara[m_iCurChanIndex] = TRUE;
	}
}

/*********************************************************
  Function:	OnBnClickedBtnHideAlarmSetup
  Desc:		view tamper settings 
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedBtnHideAlarmSetup()
{
	CDlgRemoteHideAlarm dlgRemoteHideAlarm;

	//g_lpHideAlarm = &(m_struPicCfg[m_iCurChanIndex].struHideAlarm);
    g_lpHideAlarmV40 = &(m_pStruPicCfgV40[m_iCurChanIndex].struHideAlarm);
	dlgRemoteHideAlarm.m_iChanShowNum = m_iChanShowNum;
	dlgRemoteHideAlarm.m_lLoginID = m_lLoginID;
	dlgRemoteHideAlarm.m_dwAlarmOutNum = m_dwAlarmOutNum;
	dlgRemoteHideAlarm.m_dwDevIndex = m_iDeviceIndex;
	if (dlgRemoteHideAlarm.DoModal() == IDOK)
	{
		m_pbSetChannelPara[m_iCurChanIndex] = TRUE;
	}
}

/*********************************************************
  Function:	OnBnClickedBtnVilostSetup
  Desc:		video loss settings
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedBtnVilostSetup()
{
	CDlgRemoteVideoInLost dlgRemoteVideoInLost;

	//g_lpVILost = &(m_struPicCfg[m_iCurChanIndex].struVILost);
    g_lpVILostV40 = &(m_pStruPicCfgV40[m_iCurChanIndex].struVILost);
	dlgRemoteVideoInLost.m_iChanShowNum = m_iChanShowNum;
	dlgRemoteVideoInLost.m_lLoginID = m_lLoginID;
	dlgRemoteVideoInLost.m_dwAlarmOutNum = m_dwAlarmOutNum;
	dlgRemoteVideoInLost.m_dwDevIndex = m_iDeviceIndex;
	dlgRemoteVideoInLost.m_bIsVILost = FALSE;
	if (dlgRemoteVideoInLost.DoModal() == IDOK)
	{
		m_pbSetChannelPara[m_iCurChanIndex] = TRUE;
	}
}


/*********************************************************
  Function:	OnBnClickedBtnAUlostSetup
  Desc:		video loss settings
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedBtnAUlostSetup()
{
	CDlgRemoteVideoInLost dlgRemoteVideoInLost;

	//g_lpVILost = &(m_struPicCfg[m_iCurChanIndex].struVILost);
    g_lpVILostV40 = &(m_pStruPicCfgV40[m_iCurChanIndex].struAULost);
	dlgRemoteVideoInLost.m_iChanShowNum = m_iChanShowNum;
	dlgRemoteVideoInLost.m_lLoginID = m_lLoginID;
	dlgRemoteVideoInLost.m_dwAlarmOutNum = m_dwAlarmOutNum;
	dlgRemoteVideoInLost.m_dwDevIndex = m_iDeviceIndex;
	dlgRemoteVideoInLost.m_bIsVILost = TRUE;
	if (dlgRemoteVideoInLost.DoModal() == IDOK)
	{
		m_pbSetChannelPara[m_iCurChanIndex] = TRUE;
	}
}


/*********************************************************
  Function:	OnBnClickedBtnString	
  Desc:		string overlay settings
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedBtnString()
{
	CDlgRemoteShowString dlgRemoteShowString;

	dlgRemoteShowString.m_lLoginID = m_lLoginID;
	dlgRemoteShowString.m_iChanShowNum = m_iChanShowNum;
	dlgRemoteShowString.DoModal();
}

/*********************************************************
  Function:	OnBnClickedBtnChanCopy
  Desc:		copy channel configuration
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedBtnChanCopy()
{
	UpdateData(TRUE);
	int i = 0, j = 0, k = 0;
	m_iCopyChanIndex = m_comboCopyChan.GetItemData(m_comboCopyChan.GetCurSel()) - 1;
// 	if (m_iCopyChanIndex == m_iCurChanIndex)
// 	{
// 		return;
// 	}

	if (m_iCopyChanIndex == -1)
	{
		for (i=0; i<MAX_CHANNUM_V40; i++)
		{
			if (i == m_iCurChanIndex|| !g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].bEnable)//去掉没有获取设备通道参数的通道，既处于关闭状态的通道
			{
				continue;// || !m_bGetChannelPara[i] 
			}
			//copy comrpession parameters
				//main stream
			CheckRebootParam( &(m_struMSCompressionCfg[i][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byStreamType),\
				m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byStreamType, FALSE);				 
			m_struMSCompressionCfg[i][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byPicQuality = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byPicQuality;
			m_struMSCompressionCfg[i][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate;
			CheckRebootParam( &(m_struMSCompressionCfg[i][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byResolution),\
				m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byResolution, TRUE);
			m_struMSCompressionCfg[i][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate;
			m_struMSCompressionCfg[i][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byBitrateType = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byBitrateType;
			m_struMSCompressionCfg[i][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame;	
			m_struMSCompressionCfg[i][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI;
			m_struMSCompressionCfg[i][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncType = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncType;	
			m_struMSCompressionCfg[i][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byAudioEncType = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byAudioEncType;
			m_struMSCompressionCfg[i][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity;
			m_struMSCompressionCfg[i][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byStreamSmooth = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byStreamSmooth;		
			//sub stream
			m_struMSCompressionCfg[i][SUB_STREAM_COMPRESSION].struStreamPara.byStreamType = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byStreamType;
			m_struMSCompressionCfg[i][SUB_STREAM_COMPRESSION].struStreamPara.byPicQuality = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byPicQuality;
			m_struMSCompressionCfg[i][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate;
			m_struMSCompressionCfg[i][SUB_STREAM_COMPRESSION].struStreamPara.byResolution = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byResolution;
			m_struMSCompressionCfg[i][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate= m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate;
			m_struMSCompressionCfg[i][SUB_STREAM_COMPRESSION].struStreamPara.byBitrateType = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byBitrateType;
			m_struMSCompressionCfg[i][SUB_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame;	
			m_struMSCompressionCfg[i][SUB_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI;
			m_struMSCompressionCfg[i][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncType = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncType;	
			m_struMSCompressionCfg[i][SUB_STREAM_COMPRESSION].struStreamPara.byAudioEncType = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byAudioEncType;
			m_struMSCompressionCfg[i][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity;
			m_struMSCompressionCfg[i][SUB_STREAM_COMPRESSION].struStreamPara.byStreamSmooth = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byStreamSmooth;					
			//event
			m_struMSCompressionCfg[i][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamType = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamType;
			m_struMSCompressionCfg[i][EVENT_INVOKE_COMPRESSION].struStreamPara.byPicQuality = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byPicQuality;
			m_struMSCompressionCfg[i][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoBitrate = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoBitrate;
			m_struMSCompressionCfg[i][EVENT_INVOKE_COMPRESSION].struStreamPara.byResolution = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byResolution;
			m_struMSCompressionCfg[i][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoFrameRate = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoFrameRate;
			m_struMSCompressionCfg[i][EVENT_INVOKE_COMPRESSION].struStreamPara.byBitrateType = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byBitrateType;
			m_struMSCompressionCfg[i][EVENT_INVOKE_COMPRESSION].struStreamPara.byIntervalBPFrame = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byIntervalBPFrame;	
			m_struMSCompressionCfg[i][EVENT_INVOKE_COMPRESSION].struStreamPara.wIntervalFrameI = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.wIntervalFrameI;
			m_struMSCompressionCfg[i][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncType = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncType;	
			m_struMSCompressionCfg[i][EVENT_INVOKE_COMPRESSION].struStreamPara.byAudioEncType = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byAudioEncType;
			m_struMSCompressionCfg[i][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncComplexity = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncComplexity;
			m_struMSCompressionCfg[i][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamSmooth = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamSmooth;	
// 			m_struCompressionCfg[i].struNormLowRecordPara.byStreamType = m_struCompressionCfg[m_iCurChanIndex].struNormLowRecordPara.byStreamType;
// 			m_struCompressionCfg[i].struNormLowRecordPara.byPicQuality = m_struCompressionCfg[m_iCurChanIndex].struNormLowRecordPara.byPicQuality;
// 			m_struCompressionCfg[i].struNormLowRecordPara.dwVideoBitrate = m_struCompressionCfg[m_iCurChanIndex].struNormLowRecordPara.dwVideoBitrate;
// 			m_struCompressionCfg[i].struNormLowRecordPara.byResolution = m_struCompressionCfg[m_iCurChanIndex].struNormLowRecordPara.byResolution;
// 			m_struCompressionCfg[i].struNormLowRecordPara.dwVideoFrameRate = m_struCompressionCfg[m_iCurChanIndex].struNormLowRecordPara.dwVideoFrameRate;
// 			m_struCompressionCfg[i].struNormLowRecordPara.byBitrateType = m_struCompressionCfg[m_iCurChanIndex].struNormLowRecordPara.byBitrateType;
// 			m_struCompressionCfg[i].struNormLowRecordPara.byIntervalBPFrame = m_struCompressionCfg[m_iCurChanIndex].struNormLowRecordPara.byIntervalBPFrame;	
// 			m_struCompressionCfg[i].struNormLowRecordPara.wIntervalFrameI = m_struCompressionCfg[m_iCurChanIndex].struNormLowRecordPara.wIntervalFrameI;

			//recording paramerters
			m_pStruRemoteRecCfg[i].dwSize = sizeof(NET_DVR_RECORD_V30);
			m_pStruRemoteRecCfg[i].dwRecord = m_pStruRemoteRecCfg[m_iCurChanIndex].dwRecord;
			m_pStruRemoteRecCfg[i].dwRecordTime = m_pStruRemoteRecCfg[m_iCurChanIndex].dwRecordTime;
			m_pStruRemoteRecCfg[i].dwPreRecordTime = m_pStruRemoteRecCfg[m_iCurChanIndex].dwPreRecordTime;
			m_pStruRemoteRecCfg[i].dwRecorderDuration = m_pStruRemoteRecCfg[m_iCurChanIndex].dwRecorderDuration;
			m_pStruRemoteRecCfg[i].byStreamType = m_pStruRemoteRecCfg[m_iCurChanIndex].byStreamType;
			m_pStruRemoteRecCfg[i].byPassbackRecord = m_pStruRemoteRecCfg[m_iCurChanIndex].byPassbackRecord;
			m_pStruRemoteRecCfg[i].wLockDuration = m_pStruRemoteRecCfg[m_iCurChanIndex].wLockDuration;
			m_pStruRemoteRecCfg[i].byRecordBackup = m_pStruRemoteRecCfg[m_iCurChanIndex].byRecordBackup;

			//copy time schedule
			for (k=0; k<MAX_DAYS; k++)
			{
				memcpy(&(m_pStruRemoteRecCfg[i].struRecAllDay[k]), &(m_pStruRemoteRecCfg[m_iCurChanIndex].struRecAllDay[k]), sizeof(NET_DVR_RECORDDAY));
				for (j=0; j<MAX_TIMESEGMENT_V30; j++)
				{
					memcpy(&m_pStruRemoteRecCfg[i].struRecordSched[k][j],&m_pStruRemoteRecCfg[m_iCurChanIndex].struRecordSched[k][j],sizeof(NET_DVR_RECORDSCHED));				
				}
			}

			//image parameters
		/*	m_struPicCfg[i].dwEnableHide = m_bCheckHideArea;
			m_struPicCfg[i].struMotion.byEnableHandleMotion = (BYTE)m_bCheckMotion;			
			if (!m_bCheckHideAlarm)
			{
				m_struPicCfg[i].struHideAlarm.dwEnableHideAlarm = m_bCheckHideAlarm;
			}
			m_struPicCfg[i].dwShowChanName = m_bCheckChanName;
			m_struPicCfg[i].wShowNameTopLeftX = (WORD)m_iChanNameX;
			m_struPicCfg[i].wShowNameTopLeftY = (WORD)m_iChanNameY;
			m_struPicCfg[i].dwShowOsd = m_bCheckOsd;
			m_struPicCfg[i].wOSDTopLeftX = (WORD)m_iOsdX;
			m_struPicCfg[i].wOSDTopLeftY = (WORD)m_iOsdY;
			m_struPicCfg[i].byDispWeek = (BYTE)m_bChkDispWeek;
			m_struPicCfg[i].byOSDAttrib = (BYTE)(m_comboOsdAttrib.GetCurSel()+1);
			m_struPicCfg[i].byOSDType = (BYTE)m_comboOsdType.GetCurSel();
			if (4 == (BYTE)(m_cmbOsdFont.GetCurSel()))
			{
				m_struPicCfg[i].byFontSize = 0xff;
			}
			else
			{
				m_struPicCfg[i].byFontSize = (BYTE)(m_cmbOsdFont.GetCurSel());
			}
			m_struPicCfg[i].byHourOSDType = (BYTE)m_comboHourType.GetCurSel();
			m_struPicCfg[i].struVILost.byEnableHandleVILost = (BYTE)m_bCheckVILost;
            */

            m_pStruPicCfgV40[i].dwEnableHide = m_bCheckHideArea;
            m_pStruPicCfgV40[i].struMotion.byEnableHandleMotion = (BYTE)m_bCheckMotion;			
            m_pStruPicCfgV40[i].struMotion.byKeyingEnable = (BYTE)m_bKeyEnable;
            if (!m_bCheckHideAlarm)
            {
			    m_pStruPicCfgV40[i].struHideAlarm.dwEnableHideAlarm = m_bCheckHideAlarm;
            }
            m_pStruPicCfgV40[i].dwShowChanName = m_bCheckChanName;
            m_pStruPicCfgV40[i].wShowNameTopLeftX = (WORD)m_iChanNameX;
            m_pStruPicCfgV40[i].wShowNameTopLeftY = (WORD)m_iChanNameY;
            m_pStruPicCfgV40[i].dwShowOsd = m_bCheckOsd;
            m_pStruPicCfgV40[i].wOSDTopLeftX = (WORD)m_iOsdX;
            m_pStruPicCfgV40[i].wOSDTopLeftY = (WORD)m_iOsdY;
            m_pStruPicCfgV40[i].byDispWeek = (BYTE)m_bChkDispWeek;
            m_pStruPicCfgV40[i].byOSDAttrib = (BYTE)(m_comboOsdAttrib.GetCurSel()+1);
            m_pStruPicCfgV40[i].byOSDType = (BYTE)m_comboOsdType.GetCurSel();
			m_pStruPicCfgV40[i].byOSDColorType = (BYTE)m_bOSDColor;
            m_pStruPicCfgV40[m_iCurChanIndex].byAlignment = m_comboAlignment.GetCurSel();
			m_pStruPicCfgV40[i].struOsdColor.byRed = m_byOsdColorR;
			m_pStruPicCfgV40[i].struOsdColor.byGreen = m_byOsdColorG;
			m_pStruPicCfgV40[i].struOsdColor.byBlue = m_byOsdColorB;
            m_pStruPicCfgV40[i].dwBoundary = m_dwBoundary;
            m_pStruPicCfgV40[i].byOSDBkColorMode = m_bSelfBackColor;
            m_pStruPicCfgV40[i].struOsdBkColor.byBlue = m_bySelfBlue;
            m_pStruPicCfgV40[i].struOsdBkColor.byGreen = m_bySelfGreen;
            m_pStruPicCfgV40[i].struOsdBkColor.byRed = m_bySelfRed;
            m_pStruPicCfgV40[i].dwVideoFormat = m_cmbVideoFormat.GetCurSel();
			memcpy(&m_pStruPicCfgV40[i].struViColor,&m_pStruPicCfgV40[m_iCurChanIndex].struViColor,sizeof(NET_DVR_VICOLOR));
			
            if (7 == (BYTE)(m_cmbOsdFont.GetCurSel()))
            {
                m_pStruPicCfgV40[i].byFontSize = 0xff;
            }
            else
            {
                m_pStruPicCfgV40[i].byFontSize = (BYTE)(m_cmbOsdFont.GetCurSel());
            }
            m_pStruPicCfgV40[i].byHourOSDType = (BYTE)m_comboHourType.GetCurSel();
			m_pStruPicCfgV40[i].struVILost.dwEnableVILostAlarm = (BYTE)m_bCheckVILost;
			m_pStruPicCfgV40[i].struAULost.dwEnableVILostAlarm = m_bCheckAULost;
//			m_struPicCfg[i].struAULost.byEnableHandleVILost = m_bChkAuLost;
				//copy image parameters
//			memcpy(&(m_struPicCfg[i].struViColor), &(m_struPicCfg[m_iCurChanIndex].struViColor), sizeof(NET_DVR_VICOLOR));
			m_pStruAudioIn[i].byAudioInputType = (BYTE)(m_comboAudioInType.GetCurSel());
			m_pStruAudioIn[i].byVolume = m_byVolume;
			m_pbSetChannelPara[i] = TRUE;
			m_pStruAudioIn[i].byEnableNoiseFilter = m_bEnableNoiseFilter;
        }		
	}
	else
	{//main stream
// 		CheckRebootParam( &(m_struCompressionCfg[m_iCopyChanIndex].struNormHighRecordPara.byStreamType),\
// 			m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byStreamType, FALSE);
		CheckRebootParam( &(m_struMSCompressionCfg[m_iCopyChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byStreamType),\
			m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byStreamType, FALSE);				 
		m_struMSCompressionCfg[m_iCopyChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byPicQuality = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byPicQuality;
		m_struMSCompressionCfg[m_iCopyChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate;
		CheckRebootParam( &(m_struMSCompressionCfg[m_iCopyChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byResolution),\
			m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byResolution, TRUE);
		m_struMSCompressionCfg[m_iCopyChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate;
		m_struMSCompressionCfg[m_iCopyChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byBitrateType = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byBitrateType;
		m_struMSCompressionCfg[m_iCopyChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame;	
		m_struMSCompressionCfg[m_iCopyChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI;
		m_struMSCompressionCfg[m_iCopyChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncType = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncType;	
		m_struMSCompressionCfg[m_iCopyChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byAudioEncType = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byAudioEncType;
		m_struMSCompressionCfg[m_iCopyChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity;
		m_struMSCompressionCfg[m_iCopyChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byStreamSmooth = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byStreamSmooth;
		//sub stream
		m_struMSCompressionCfg[m_iCopyChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byStreamType = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byStreamType;
		m_struMSCompressionCfg[m_iCopyChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byPicQuality = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byPicQuality;
		m_struMSCompressionCfg[m_iCopyChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate;
		m_struMSCompressionCfg[m_iCopyChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byResolution = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byResolution;
		m_struMSCompressionCfg[m_iCopyChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate= m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate;
		m_struMSCompressionCfg[m_iCopyChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byBitrateType = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byBitrateType;
		m_struMSCompressionCfg[m_iCopyChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame;	
		m_struMSCompressionCfg[m_iCopyChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI;
		m_struMSCompressionCfg[m_iCopyChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncType = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncType;	
		m_struMSCompressionCfg[m_iCopyChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byAudioEncType = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byAudioEncType;
		m_struMSCompressionCfg[m_iCopyChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity;
		m_struMSCompressionCfg[m_iCopyChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byStreamSmooth = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byStreamSmooth;		
		//event
		m_struMSCompressionCfg[m_iCopyChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamType = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamType;
		m_struMSCompressionCfg[m_iCopyChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byPicQuality = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byPicQuality;
		m_struMSCompressionCfg[m_iCopyChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoBitrate = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoBitrate;
		m_struMSCompressionCfg[m_iCopyChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byResolution = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byResolution;
		m_struMSCompressionCfg[m_iCopyChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoFrameRate = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoFrameRate;
		m_struMSCompressionCfg[m_iCopyChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byBitrateType = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byBitrateType;
		m_struMSCompressionCfg[m_iCopyChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byIntervalBPFrame = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byIntervalBPFrame;	
		m_struMSCompressionCfg[m_iCopyChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.wIntervalFrameI = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.wIntervalFrameI;
		m_struMSCompressionCfg[m_iCopyChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncType = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncType;	
		m_struMSCompressionCfg[m_iCopyChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byAudioEncType = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byAudioEncType;
		m_struMSCompressionCfg[m_iCopyChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncComplexity = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncComplexity;
		m_struMSCompressionCfg[m_iCopyChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamSmooth = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamSmooth;	
		//remote record parameters
		m_pStruRemoteRecCfg[m_iCopyChanIndex].dwSize = sizeof(NET_DVR_RECORD_V30);
		m_pStruRemoteRecCfg[m_iCopyChanIndex].dwRecord = m_bCheckRecord;
		m_pStruRemoteRecCfg[m_iCopyChanIndex].dwRecordTime = m_comboRecDelay.GetCurSel();
		m_pStruRemoteRecCfg[m_iCopyChanIndex].dwPreRecordTime = m_comboPreRecordTime.GetCurSel();
		m_pStruRemoteRecCfg[m_iCopyChanIndex].dwRecorderDuration = m_dwDurationTime;
		m_pStruRemoteRecCfg[m_iCopyChanIndex].byStreamType = m_pStruRemoteRecCfg[m_iCurChanIndex].byStreamType;
		m_pStruRemoteRecCfg[m_iCopyChanIndex].byPassbackRecord = m_pStruRemoteRecCfg[m_iCurChanIndex].byPassbackRecord;
		m_pStruRemoteRecCfg[m_iCopyChanIndex].wLockDuration = m_pStruRemoteRecCfg[m_iCurChanIndex].wLockDuration;
		m_pStruRemoteRecCfg[m_iCopyChanIndex].byRecordBackup = m_pStruRemoteRecCfg[m_iCurChanIndex].byRecordBackup;

		for (k=0; k<MAX_DAYS; k++)
		{
			memcpy(&(m_pStruRemoteRecCfg[m_iCopyChanIndex].struRecAllDay[k]), &(m_pStruRemoteRecCfg[m_iCurChanIndex].struRecAllDay[k]), sizeof(NET_DVR_RECORDDAY));
			for (j=0; j<MAX_TIMESEGMENT_V30; j++)
			{
				memcpy(&m_pStruRemoteRecCfg[m_iCopyChanIndex].struRecordSched[k][j],&m_pStruRemoteRecCfg[m_iCurChanIndex].struRecordSched[k][j],sizeof(NET_DVR_RECORDSCHED));				
			}
		}
		
/*		m_struPicCfg[m_iCopyChanIndex].dwEnableHide = m_bCheckHideArea;
		m_struPicCfg[m_iCopyChanIndex].struMotion.byEnableHandleMotion = (BYTE)m_bCheckMotion;
		if (!m_bCheckHideAlarm)
		{
			m_struPicCfg[m_iCopyChanIndex].struHideAlarm.dwEnableHideAlarm = m_bCheckHideAlarm;
		}
		m_struPicCfg[m_iCopyChanIndex].dwShowChanName = m_bCheckChanName;
		m_struPicCfg[m_iCopyChanIndex].wShowNameTopLeftX = (WORD)m_iChanNameX;
		m_struPicCfg[m_iCopyChanIndex].wShowNameTopLeftY = (WORD)m_iChanNameY;
		m_struPicCfg[m_iCopyChanIndex].dwShowOsd = m_bCheckOsd;
		m_struPicCfg[m_iCopyChanIndex].wOSDTopLeftX = (WORD)m_iOsdX;
		m_struPicCfg[m_iCopyChanIndex].wOSDTopLeftY = (WORD)m_iOsdY;
		m_struPicCfg[m_iCopyChanIndex].byDispWeek = (BYTE)m_bChkDispWeek;
		m_struPicCfg[m_iCopyChanIndex].byOSDAttrib = (BYTE)(m_comboOsdAttrib.GetCurSel()+1);
		m_struPicCfg[m_iCopyChanIndex].byOSDType = (BYTE)m_comboOsdType.GetCurSel();
		if (4 == (BYTE)(m_cmbOsdFont.GetCurSel()))
		{
			m_struPicCfg[m_iCopyChanIndex].byFontSize = 0xff;
		}
		else
		{
			m_struPicCfg[m_iCopyChanIndex].byFontSize = (BYTE)(m_cmbOsdFont.GetCurSel());
		}
		m_struPicCfg[m_iCopyChanIndex].struVILost.byEnableHandleVILost = (BYTE)m_bCheckVILost;
        */
        // Channel Pic Cfg 
        m_pStruPicCfgV40[m_iCopyChanIndex].dwEnableHide = m_bCheckHideArea;
        m_pStruPicCfgV40[m_iCopyChanIndex].struMotion.byEnableHandleMotion = (BYTE)m_bCheckMotion;
        m_pStruPicCfgV40[m_iCopyChanIndex].struMotion.byKeyingEnable = (BYTE)m_bKeyEnable;
        if (!m_bCheckHideAlarm)
        {
		    m_pStruPicCfgV40[m_iCopyChanIndex].struHideAlarm.dwEnableHideAlarm = m_bCheckHideAlarm;
        }
        m_pStruPicCfgV40[m_iCopyChanIndex].dwShowChanName = m_bCheckChanName;
        m_pStruPicCfgV40[m_iCopyChanIndex].wShowNameTopLeftX = (WORD)m_iChanNameX;
        m_pStruPicCfgV40[m_iCopyChanIndex].wShowNameTopLeftY = (WORD)m_iChanNameY;
        m_pStruPicCfgV40[m_iCopyChanIndex].dwShowOsd = m_bCheckOsd;
        m_pStruPicCfgV40[m_iCopyChanIndex].wOSDTopLeftX = (WORD)m_iOsdX;
        m_pStruPicCfgV40[m_iCopyChanIndex].wOSDTopLeftY = (WORD)m_iOsdY;
        m_pStruPicCfgV40[m_iCopyChanIndex].byDispWeek = (BYTE)m_bChkDispWeek;
        m_pStruPicCfgV40[m_iCopyChanIndex].byOSDAttrib = (BYTE)(m_comboOsdAttrib.GetCurSel()+1);
        m_pStruPicCfgV40[m_iCopyChanIndex].byOSDType = (BYTE)m_comboOsdType.GetCurSel();
		m_pStruPicCfgV40[m_iCopyChanIndex].byOSDColorType = (BYTE)m_bOSDColor;
        m_pStruPicCfgV40[m_iCurChanIndex].byAlignment = m_comboAlignment.GetCurSel();
		m_pStruPicCfgV40[m_iCopyChanIndex].struOsdColor.byRed = m_byOsdColorR;
		m_pStruPicCfgV40[m_iCopyChanIndex].struOsdColor.byGreen = m_byOsdColorG;
		m_pStruPicCfgV40[m_iCopyChanIndex].struOsdColor.byBlue = m_byOsdColorB;
        m_pStruPicCfgV40[m_iCopyChanIndex].dwBoundary = m_dwBoundary;
        m_pStruPicCfgV40[m_iCopyChanIndex].byOSDBkColorMode = m_bSelfBackColor;
        m_pStruPicCfgV40[m_iCopyChanIndex].struOsdBkColor.byBlue = m_bySelfBlue;
        m_pStruPicCfgV40[m_iCopyChanIndex].struOsdBkColor.byGreen = m_bySelfGreen;
        m_pStruPicCfgV40[m_iCopyChanIndex].struOsdBkColor.byRed = m_bySelfRed;
        m_pStruPicCfgV40[m_iCopyChanIndex].dwVideoFormat = m_cmbVideoFormat.GetCurSel();
        if (7 == (BYTE)(m_cmbOsdFont.GetCurSel()))
        {
            m_pStruPicCfgV40[m_iCopyChanIndex].byFontSize = 0xff;
        }
        else
        {
            m_pStruPicCfgV40[m_iCopyChanIndex].byFontSize = (BYTE)(m_cmbOsdFont.GetCurSel());
        }
		m_pStruPicCfgV40[m_iCopyChanIndex].struVILost.dwEnableVILostAlarm = (DWORD)m_bCheckVILost;
		m_pStruPicCfgV40[m_iCopyChanIndex].struAULost.dwEnableVILostAlarm = (DWORD)m_bCheckAULost;

		m_pStruAudioIn[m_iCopyChanIndex].byAudioInputType = (BYTE)(m_comboAudioInType.GetCurSel());
		m_pStruAudioIn[m_iCopyChanIndex].byEnableNoiseFilter = m_bEnableNoiseFilter;
		m_pbSetChannelPara[m_iCopyChanIndex] = TRUE;
	}
}

/*********************************************************
  Function:	OnBnClickedBtnChanCfgOk
  Desc:		Confirm current channel configuration
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedBtnChanCfgOk()
{
	SaveLastCompressTypePara();
	
	UpdateData(TRUE);	
	OnBnClickedBtnCmpOk();
	//record paramerters
	m_pStruRemoteRecCfg[m_iCurChanIndex].dwRecord = m_bCheckRecord;
	m_pStruRemoteRecCfg[m_iCurChanIndex].dwRecordTime = m_comboRecDelay.GetCurSel();
	m_pStruRemoteRecCfg[m_iCurChanIndex].dwPreRecordTime = m_comboPreRecordTime.GetCurSel();
	m_pStruRemoteRecCfg[m_iCurChanIndex].dwRecorderDuration = m_dwDurationTime;
	m_pStruRemoteRecCfg[m_iCurChanIndex].byRedundancyRec = (BYTE)m_bChkRedundancyRec;
	m_pStruRemoteRecCfg[m_iCurChanIndex].byAudioRec = (BYTE)m_bChkAudioRec;
	switch (m_cmbStreamType.GetCurSel())
	{
	case 0:
	case 1:
		m_pStruRemoteRecCfg[m_iCurChanIndex].byStreamType = m_cmbStreamType.GetCurSel();
		break;
    case 2:
        m_pStruRemoteRecCfg[m_iCurChanIndex].byStreamType = m_cmbStreamType.GetCurSel();
        break;
	case 3:
		m_pStruRemoteRecCfg[m_iCurChanIndex].byStreamType = m_cmbStreamType.GetCurSel();
		break;
	default:
		break;
	}
	m_pStruRemoteRecCfg[m_iCurChanIndex].byRecordBackup = m_bBackup;
	m_pStruRemoteRecCfg[m_iCurChanIndex].wLockDuration = m_wLockDuration;
	m_pStruRemoteRecCfg[m_iCurChanIndex].byPassbackRecord = (BYTE)m_bCallback;
    m_pStruRemoteRecCfg[m_iCurChanIndex].byExtraSaveAudio = m_bChkAudioExtra;
	//channel image paramerters
/*	memcpy(m_struPicCfg[m_iCurChanIndex].sChanName,m_csChanName,NAME_LEN);
	m_struPicCfg[m_iCurChanIndex].dwEnableHide = m_bCheckHideArea;
	m_struPicCfg[m_iCurChanIndex].struMotion.byEnableHandleMotion = (BYTE)m_bCheckMotion;
	
	//delete this condition judgement
	if (!m_bCheckHideAlarm)
	{
		m_struPicCfg[m_iCurChanIndex].struHideAlarm.dwEnableHideAlarm = m_bCheckHideAlarm;
	}

	m_struPicCfg[m_iCurChanIndex].dwShowChanName = m_bCheckChanName;
	m_struPicCfg[m_iCurChanIndex].wShowNameTopLeftX = (WORD)m_iChanNameX;
	m_struPicCfg[m_iCurChanIndex].wShowNameTopLeftY = (WORD)m_iChanNameY;
	m_struPicCfg[m_iCurChanIndex].dwShowOsd = m_bCheckOsd;
	m_struPicCfg[m_iCurChanIndex].wOSDTopLeftX = (WORD)m_iOsdX;
	m_struPicCfg[m_iCurChanIndex].wOSDTopLeftY = (WORD)m_iOsdY;
	m_struPicCfg[m_iCurChanIndex].byDispWeek = (BYTE)m_bChkDispWeek;
	m_struPicCfg[m_iCurChanIndex].byOSDAttrib = (BYTE)(m_comboOsdAttrib.GetCurSel()+1);
	m_struPicCfg[m_iCurChanIndex].byOSDType = (BYTE)(m_comboOsdType.GetCurSel());
	if (4 == (BYTE)(m_cmbOsdFont.GetCurSel()))
	{
		m_struPicCfg[m_iCurChanIndex].byFontSize = 0xff;
	}
	else
	{
		m_struPicCfg[m_iCurChanIndex].byFontSize = (BYTE)(m_cmbOsdFont.GetCurSel());
	}
	m_struPicCfg[m_iCurChanIndex].byHourOSDType = (BYTE)m_comboHourType.GetCurSel();
	m_struPicCfg[m_iCurChanIndex].struVILost.byEnableHandleVILost = (BYTE)m_bCheckVILost;	
*/
    strncpy((char*)m_pStruPicCfgV40[m_iCurChanIndex].sChanName, m_csChanName, NAME_LEN);
    m_pStruPicCfgV40[m_iCurChanIndex].dwEnableHide = m_bCheckHideArea;
    m_pStruPicCfgV40[m_iCurChanIndex].struMotion.byEnableHandleMotion = (BYTE)m_bCheckMotion;
    m_pStruPicCfgV40[m_iCurChanIndex].struMotion.byKeyingEnable = (BYTE)m_bKeyEnable;
    
    //delete this condition judgement

	m_pStruPicCfgV40[m_iCurChanIndex].struHideAlarm.dwEnableHideAlarm = m_bCheckHideAlarm;

    
    m_pStruPicCfgV40[m_iCurChanIndex].dwShowChanName = m_bCheckChanName;
    m_pStruPicCfgV40[m_iCurChanIndex].wShowNameTopLeftX = (WORD)m_iChanNameX;
    m_pStruPicCfgV40[m_iCurChanIndex].wShowNameTopLeftY = (WORD)m_iChanNameY;
    m_pStruPicCfgV40[m_iCurChanIndex].dwShowOsd = m_bCheckOsd;
    m_pStruPicCfgV40[m_iCurChanIndex].wOSDTopLeftX = (WORD)m_iOsdX;
    m_pStruPicCfgV40[m_iCurChanIndex].wOSDTopLeftY = (WORD)m_iOsdY;
    m_pStruPicCfgV40[m_iCurChanIndex].byDispWeek = (BYTE)m_bChkDispWeek;
    m_pStruPicCfgV40[m_iCurChanIndex].byOSDAttrib = (BYTE)(m_comboOsdAttrib.GetCurSel()+1);
    m_pStruPicCfgV40[m_iCurChanIndex].byOSDType = (BYTE)(m_comboOsdType.GetCurSel());
	m_pStruPicCfgV40[m_iCurChanIndex].byOSDColorType = (BYTE)m_bOSDColor;
    m_pStruPicCfgV40[m_iCurChanIndex].byAlignment = m_comboAlignment.GetCurSel();
	m_pStruPicCfgV40[m_iCurChanIndex].struOsdColor.byRed = m_byOsdColorR;
	m_pStruPicCfgV40[m_iCurChanIndex].struOsdColor.byGreen = m_byOsdColorG;
	m_pStruPicCfgV40[m_iCurChanIndex].struOsdColor.byBlue = m_byOsdColorB;
    m_pStruPicCfgV40[m_iCurChanIndex].dwBoundary = m_dwBoundary;
    m_pStruPicCfgV40[m_iCurChanIndex].byOSDBkColorMode = m_bSelfBackColor;
    m_pStruPicCfgV40[m_iCurChanIndex].struOsdBkColor.byBlue = m_bySelfBlue;
    m_pStruPicCfgV40[m_iCurChanIndex].struOsdBkColor.byGreen = m_bySelfGreen;
    m_pStruPicCfgV40[m_iCurChanIndex].struOsdBkColor.byRed = m_bySelfRed;
    m_pStruPicCfgV40[m_iCurChanIndex].dwVideoFormat = m_cmbVideoFormat.GetCurSel();

    if (7 == (BYTE)(m_cmbOsdFont.GetCurSel()))
    {
        m_pStruPicCfgV40[m_iCurChanIndex].byFontSize = 0xff;
    }
    else
    {
        m_pStruPicCfgV40[m_iCurChanIndex].byFontSize = (BYTE)(m_cmbOsdFont.GetCurSel());
    }
    m_pStruPicCfgV40[m_iCurChanIndex].byHourOSDType = (BYTE)m_comboHourType.GetCurSel();
	m_pStruPicCfgV40[m_iCurChanIndex].struVILost.dwEnableVILostAlarm = (DWORD)m_bCheckVILost;
	m_pStruPicCfgV40[m_iCurChanIndex].struAULost.dwEnableVILostAlarm = (DWORD)m_bCheckAULost;
//	m_struPicCfg[m_iCurChanIndex].struAULost.byEnableHandleVILost = m_bChkAuLost;
	
	m_pbSetChannelPara[m_iCurChanIndex] = TRUE;
	GetDlgItem(IDC_BTN_CHAN_COPY)->EnableWindow(TRUE);

	m_pStruCabac[m_iCurChanIndex].dwSize = sizeof(NET_DVR_STREAM_CABAC);
	m_pStruCabac[m_iCurChanIndex].byCabacEnable = m_bCabacCheck;

	m_pStruPOEAdapterType[m_iCurChanIndex].dwSize = sizeof(NET_DVR_POE_CHANNEL_ADD_MODE);
	m_pStruPOEAdapterType[m_iCurChanIndex].byAddMode = (BYTE)m_cmbPoeAdapterType.GetCurSel();

}

/*********************************************************
Function:	CfgSetup
Desc:		Set image paramerters
Input:	
Output:	
Return:	TRUE,setting succeeds;FALSE,settings fails;
**********************************************************/
BOOL CSubDlgChanCfg::CfgSetup()
{
	CString sTemp;
	int i = 0;
	int iChanShow = 0;//display channel number
	char szLan[128] = {0};
	DWORD dwStatus[5] = {0};


// 	NET_DVR_MULTI_STREAM_COMPRESSIONCFG_COND struCond = {0};
// 	NET_DVR_MULTI_STREAM_COMPRESSIONCFG struCompress = {0};
// 
// 	struCond.dwSize = sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG_COND);
// 	struCond.dwStreamType = 4;
// 	struCond.struStreamInfo.dwChannel = 33;
// 
// 	memcpy(&struCompress, &m_struMSCompressionCfg[0][4], sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG));
// 	struCompress.struStreamPara.byResolution = 3;
// 	struCompress.struStreamPara.dwVideoBitrate = 23;
// 
// 	NET_DVR_SetDeviceConfig(m_lLoginID, NET_DVR_SET_MULTI_STREAM_COMPRESSIONCFG, 1, &struCond, sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG_COND), NULL, &struCompress, sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG));


	//the confirm button on channel setting is only valid for the selected channel, users need to copy the settings to other channels
	for (i = 0; i < MAX_CHANNUM_V40; i++)
	{
	//	STRU_CHANNEL_INFO *pChannelInfo = &(g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i]);
		STRU_CHANNEL_INFO *pChannelInfo;
		if ((g_struDeviceInfo[m_iDeviceIndex].byMirrorChanNum > 0)&&(m_iCurChanIndex >= g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum))
		{
            pChannelInfo = &(g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[m_iCurChanIndex - MIRROR_CHAN_INDEX]);
		}
		else
		{
			pChannelInfo = &(g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i]);
		}
		iChanShow = pChannelInfo->iChannelNO;
		if (m_pbSetChannelPara[i] && pChannelInfo->bEnable)
		{
			// 			if (!NET_DVR_SetDVRConfig(m_lLoginID,NET_DVR_SET_COMPRESSCFG_V30, iChanShow,&(m_struCompressionCfg[i]), sizeof(NET_DVR_COMPRESSIONCFG_V30)))
			// 			{
			// 				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_COMPRESSCFG_V30 %s", g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i].chChanName);
			// 				g_StringLanType(szLan, "参数保存失败", "Save failed");
			// 				AfxMessageBox(szLan);
			// 				//return FALSE;
			// 			}
			// 			else
			// 			{
			// 				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_COMPRESSCFG_V30  %s", g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i].chChanName);	
			// 			}
			
			for(int j=0; j<5; j++)
			{			
				m_struMSCond[j].dwSize = sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG_COND);
				m_struMSCond[j].struStreamInfo.dwChannel = iChanShow;
				m_struMSCond[j].struStreamInfo.dwSize = sizeof(NET_DVR_STREAM_INFO);
				m_struMSCond[j].dwStreamType = j; 
				m_struMSCompressionCfg[i][j].dwSize = sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG);				
				
			}
			
			if (!NET_DVR_SetDeviceConfig(m_lLoginID, NET_DVR_SET_MULTI_STREAM_COMPRESSIONCFG, 5,
				&m_struMSCond, 5*sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG_COND), &dwStatus, &m_struMSCompressionCfg[i][0], 5*sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG)))	
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_MULTI_STREAM_COMPRESSIONCFG,  %s", g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].chChanName);
				g_StringLanType(szLan, "多码流参数保存失败", "Save multi stream param failed");
				AfxMessageBox(szLan);
				//return FALSE;
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_MULTI_STREAM_COMPRESSIONCFG %s", g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].chChanName);
			}
			
// 			if (!NET_DVR_SetDVRConfig(m_lLoginID,NET_DVR_SET_RECORDCFG_V30, iChanShow,&(m_pStruRemoteRecCfg[i]), sizeof(NET_DVR_RECORD_V30)))	
// 			{
// 				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_RECORDCFG_V30 %s", g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].chChanName);
// 				g_StringLanType(szLan, "录像参数保存失败", "Save record param failed");
// 				AfxMessageBox(szLan);
// 				//return FALSE;
// 			}
// 			else
// 			{
// 				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_RECORDCFG_V30 %s", g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].chChanName);
// 			}
			m_pStruRemoteRecCfgV40[i].dwSize = sizeof(NET_DVR_RECORD_V40);
			m_pStruRemoteRecCfgV40[i].byAudioRec = m_pStruRemoteRecCfg[i].byAudioRec;
			m_pStruRemoteRecCfgV40[i].byPassbackRecord = m_pStruRemoteRecCfg[i].byPassbackRecord;
			m_pStruRemoteRecCfgV40[i].byRecordBackup = m_pStruRemoteRecCfg[i].byRecordBackup;
			
			m_pStruRemoteRecCfgV40[i].byRedundancyRec = m_pStruRemoteRecCfg[i].byRedundancyRec;
			m_pStruRemoteRecCfgV40[i].byStreamType = m_pStruRemoteRecCfg[i].byStreamType;
			m_pStruRemoteRecCfgV40[i].bySVCLevel = m_pStruRemoteRecCfg[i].bySVCLevel;
			m_pStruRemoteRecCfgV40[i].byExtraSaveAudio = m_pStruRemoteRecCfg[i].byExtraSaveAudio;
			
			m_pStruRemoteRecCfgV40[i].dwPreRecordTime = m_pStruRemoteRecCfg[i].dwPreRecordTime;
			m_pStruRemoteRecCfgV40[i].dwRecord = m_pStruRemoteRecCfg[i].dwRecord;
			m_pStruRemoteRecCfgV40[i].dwRecorderDuration = m_pStruRemoteRecCfg[i].dwRecorderDuration;
			
			m_pStruRemoteRecCfgV40[i].dwRecordTime = m_pStruRemoteRecCfg[i].dwRecordTime;
			m_pStruRemoteRecCfgV40[i].wLockDuration = m_pStruRemoteRecCfg[i].wLockDuration;
			for (int g = 0; g< MAX_DAYS; g++)
			{
				m_pStruRemoteRecCfgV40[i].struRecAllDay[g].byRecordType = m_pStruRemoteRecCfg[i].struRecAllDay[g].byRecordType;
				m_pStruRemoteRecCfgV40[i].struRecAllDay[g].byAllDayRecord = m_pStruRemoteRecCfg[i].struRecAllDay[g].wAllDayRecord;
				for(int k = 0; k < MAX_TIMESEGMENT_V30; k++)
				{
					m_pStruRemoteRecCfgV40[i].struRecordSched[g][k].byRecordType = m_pStruRemoteRecCfg[i].struRecordSched[g][k].byRecordType;
					m_pStruRemoteRecCfgV40[i].struRecordSched[g][k].struRecordTime = m_pStruRemoteRecCfg[i].struRecordSched[g][k].struRecordTime;
				}	
			}

			if (!NET_DVR_SetDVRConfig(m_lLoginID,NET_DVR_SET_RECORDCFG_V40, iChanShow,&(m_pStruRemoteRecCfgV40[i]), sizeof(NET_DVR_RECORD_V40)))	
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_RECORDCFG_V40 %s", g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].chChanName);
				g_StringLanType(szLan, "录像参数保存失败", "Save record param failed");
				AfxMessageBox(szLan);
				//return FALSE;
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_RECORDCFG_V40 %s", g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].chChanName);
			}

            /*         if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_PICCFG_V30, iChanShow, &(m_struPicCfg[i]), sizeof(NET_DVR_PICCFG_V30)))
            {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "chan[%d]: NET_DVR_SET_PICCFG_V30", iChanShow);
            g_StringLanType(szLan, "参数保存失败", "Save failed");
            AfxMessageBox(szLan);
            //return FALSE;
            }
            else
            {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PICCFG_V30 %s", g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i].chChanName);
            }
            */	
			
            //channel picture param

            m_pStruPicCfgV40[i].dwSize = sizeof(NET_DVR_PICCFG_V40);

			if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_PICCFG_V40, iChanShow, &m_pStruPicCfgV40[i], sizeof(NET_DVR_PICCFG_V40)))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "chan[%d]: NET_DVR_SET_PICCFG_V40", iChanShow);
				g_StringLanType(szLan, "图像参数保存失败", "Save picture param failed");
				AfxMessageBox(szLan);
				//return FALSE;
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PICCFG_V40 %s", g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].chChanName);
			}
		
			if (!NET_DVR_SetDVRConfig(m_lLoginID,NET_DVR_SET_AUDIO_INPUT, iChanShow,&(m_pStruAudioIn[i]), sizeof(NET_DVR_AUDIO_INPUT_PARAM)))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_AUDIO_INPUT %s", g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].chChanName);
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_AUDIO_INPUT  %s", g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].chChanName);	
			}
			
			if (!NET_DVR_SetDVRConfig(m_lLoginID,NET_DVR_SET_STREAM_CABAC, iChanShow, &(m_pStruCabac[i]), sizeof(NET_DVR_STREAM_CABAC)))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_STREAM_CABAC %s", g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].chChanName);
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_STREAM_CABAC  %s", g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].chChanName);	
			}
            
            m_pStruPOEAdapterType[i].dwSize = sizeof(NET_DVR_POE_CHANNEL_ADD_MODE);
			if (!NET_DVR_SetDVRConfig(m_lLoginID,NET_DVR_SET_POE_CHANNEL_ADD_MODE, iChanShow, &(m_pStruPOEAdapterType[i]), sizeof(NET_DVR_POE_CHANNEL_ADD_MODE)))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_POE_CHANNEL_ADD_MODE %s", g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].chChanName);
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_POE_CHANNEL_ADD_MODE  %s", g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].chChanName);	
			}
			
			m_pbSetChannelPara[i] = FALSE;
		}
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "chan parameter set successfully!"); 
	return TRUE;
}

/*********************************************************
  Function:	OnBnClickedBtnChanCfgExit
  Desc:		cancel current channel settings
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedBtnChanCfgExit()
{
	for (int i=0; i<m_iChanCount; i++)
	{
		m_pbSetChannelPara[i] = FALSE;
	}
}

/*********************************************************
  Function:	OnBnClickedChkRecord
  Desc:		set remote record schedule or not
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedChkRecord()
{
	UpdateData(TRUE);
	if (m_bCheckRecord)
	{
		GetDlgItem(IDC_BTN_REMOTE_RECORD_SETUP)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_REMOTE_RECORD_SETUP)->EnableWindow(FALSE);
	}
}

/*********************************************************
  Function:	OnBnClickedChkHideArea
  Desc:		set privacy mask or not
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedChkHideArea()
{
	UpdateData(TRUE);
	if (m_bCheckHideArea)
	{
		GetDlgItem(IDC_BTN_HIDE_SETUP)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_HIDE_SETUP)->EnableWindow(FALSE);
	}
}

/*********************************************************
  Function:	OnBnClickedChkOsd
  Desc:		set osd or not
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedChkOsd()
{
	UpdateData(TRUE);
	EnableOsd(m_bCheckOsd);
	UpdateData(FALSE);
}

/*********************************************************
  Function:	EnableOsd
  Desc:		 status of osd parameters in the control
  Input:	bEnable,TRUE,enable;FALSE,disable;
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::EnableOsd(BOOL bEnable) 
{
	GetDlgItem(IDC_EDIT_OSD_X)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_OSD_Y)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_OSD_ATTRIB)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_OSD_TYPE)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHK_DISPLAY_WEEK)->EnableWindow(bEnable);
}

/*********************************************************
  Function:	OnBnClickedChkChanNamePos
  Desc:		set channel name position or not
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedChkChanNamePos()
{
	UpdateData(TRUE);
	EnableChanname(m_bCheckChanName);
	UpdateData(FALSE);
}

/*********************************************************
Function:	EnableChanname
Desc:		channel name position parameters status on the control
Input:	bEnable,TRUE,enable;FALSE,disable;
Output:	
Return:	
**********************************************************/
void CSubDlgChanCfg::EnableChanname(BOOL bEnable) 
{
	GetDlgItem(IDC_EDIT_CHAN_NAME_X)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_CHAN_NAME_Y)->EnableWindow(bEnable);
}

/*********************************************************
  Function:	OnCbnSelchangeComboCopyChan
  Desc:		select the channel number to be copied to
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnCbnSelchangeComboCopyChan()
{
	UpdateData(TRUE);
	DWORD dwSel = m_comboCopyChan.GetCurSel();
	CString csChan = _T("");
	if (dwSel == 0)
	{
		m_iCopyChanIndex =  - 1;
	}
	else
	{
		m_comboCopyChan.SetItemData(1, 1);
		dwSel = m_comboCopyChan.GetItemData(1);
		m_comboCopyChan.GetDlgItemText(dwSel, csChan);
		m_iCopyChanIndex = atoi(csChan.GetBuffer(0));
	}	
}

/*********************************************************
  Function:	OnBnClickedChkMotion
  Desc:		setmotion detect or not
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedChkMotion()
{
	UpdateData(TRUE);
	GetDlgItem(IDC_BTN_MOTION_SETUP)->EnableWindow(m_bCheckMotion);
}

/*********************************************************
  Function:	OnBnClickedChkHideAlarm
  Desc:		set view tamper detect or not
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedChkHideAlarm()
{
	UpdateData(TRUE);
	GetDlgItem(IDC_BTN_HIDE_ALARM_SETUP)->EnableWindow(m_bCheckHideAlarm);
}

/*********************************************************
  Function:	OnBnClickedChkVilost
  Desc:		set video loss detect or not
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedChkVilost()
{
	UpdateData(TRUE);
	GetDlgItem(IDC_BTN_VILOST_SETUP)->EnableWindow(m_bCheckVILost);
}


/*********************************************************
  Function:	OnBnClickedChkAUlost
  Desc:		set video loss detect or not
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedChkAUlost()
{
	UpdateData(TRUE);
	GetDlgItem(IDC_BTN_AULOST_SETUP2)->EnableWindow(m_bCheckAULost);
}


/*********************************************************
  Function:	FrameIIntervalMap
  Desc:		frame interval
  Input:	
  Output:	
  Return:	
**********************************************************/
WORD CSubDlgChanCfg::FrameIIntervalMap(DWORD nSelFrameRate)
{
	WORD nRet = 0;
	switch (nSelFrameRate)
	{
	case 0:
		nRet = 25;
		break;
	case 6:
		nRet = 2;
		break;
	case 7:
		nRet = 4;
		break;
	case 8:
		nRet = 6;
		break;
	case 9:
		nRet = 8;
		break;
	case 10:
		nRet = 10;
		break;
	case 11:
		nRet = 12;
		break;
	case 12:
		nRet = 16;
		break;
	case 13:
		nRet = 20;
		break;
	case 14:
		nRet = 15;
		break;
	case 15:
		nRet = 18;
		break;
	case 16:
		nRet = 22;
		break;
	default:
		nRet = 1;
	}
	nRet *= 4;
	return nRet;
}

/*********************************************************
  Function:	OnCbnSelchangeComboFrameRate
  Desc:		main stream settings
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnCbnSelchangeComboFrameRate()
{
	UpdateData(TRUE);
	WORD nSel = (WORD)m_comboFrameRate.GetCurSel();
	m_iFrameIInterval = FrameIIntervalMap(nSel);	
	UpdateData(FALSE);
}

/*********************************************************
Function:	UpdateCompressionInfo
Desc:		update compression paraemeters and control display
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgChanCfg::UpdateCompressionInfo()
{
    UpdateData(TRUE);
	GetDlgItem(IDC_CHK_EVENT_COMPRESS)->ShowWindow(SW_HIDE);
    int nCount = 0;
    int iCompressionType = m_comboCompressionType.GetCurSel();
	switch (m_comboCompressionType.GetCurSel())
	{
	case NORM_HIGH_STREAM_COMPRESSION:
   //     GetResolutionAbility();
		GetDlgItem(IDC_COMBO_STREAM_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_RESOLUTION)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FRAME_I_INTERVAL)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_FRAME_BP_INTERVAL)->EnableWindow(TRUE);

		//码率类型，定码率 or 变码率
        SetBitrateTypeCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byBitrateType);
       
		//码率上限
		if ((m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate >> 31) & 0x01) // 自定义
		{
			GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(TRUE);
			m_comboBitRate.SetCurSel(m_comboBitRate.GetCount()-1);		//adjust bit rate settings
			m_iBitRate = (m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate & 0x7fffffff)/1024;
		}
		else
		{
            SetBitrateCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate);
            m_iBitRate = 0;
			GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(FALSE);
		}	

        SetResolutionCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byResolution);
        m_comboStreamType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byStreamType);
		m_comboImageQuality.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byPicQuality);

		//m_comboBitRateType.SetCurSel(m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byBitrateType);
        SetFrameCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate);
		//m_comboFrameRate.SetCurSel(m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.dwVideoFrameRate);
		m_comboFrameBPInterval.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame);	
		m_iFrameIInterval = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI;

//		m_comboVideoType.EnableWindow(FALSE);
//		m_comboAudioType.EnableWindow(FALSE);
		//2011-05-01
		if (m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncType == 0xff)
		{
			//not support this parameter, disable the Combo
			m_comboVideoType.EnableWindow(FALSE);
			m_comboVideoType.SetCurSel(0);
		}
// 		else
// 		{
//             m_comboVideoType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncType);
// 		}

		else if (m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncType > 2)
		{
			m_comboVideoType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncType - 4);
		}
		else
		{
            m_comboVideoType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncType);
		}

		if (m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byAudioEncType == 0xff)
		{
			//not support this parameter, disable the Combo
			m_comboAudioType.EnableWindow(FALSE);
			m_comboAudioType.SetCurSel(0);
		}
		else
		{
			m_comboAudioType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byAudioEncType);
		}
		m_comboVideoEncComplexity.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity);
		//m_bChkEnableSvc = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byEnableSvc;
		m_comSVC.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byEnableSvc);
		m_comboAudioBitRate.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byAudioBitRate);
		m_byStreamSmooth = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byStreamSmooth;
		m_comboSamplingRate.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byAudioSamplingRate);
        m_bChkSmartCodec = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.bySmartCodec;
        m_bDepthMapEnable = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byDepthMapEnable & 0x01;
        m_bYStreamEnable = (m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byDepthMapEnable & 0x02) >> 1;
        //m_comboAverageBitRate.SetCurSel(m_comboAverageBitRate.GetCount()-1);

        //平均码率
        if ((m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.wAverageVideoBitrate >> 15) & 0x01) // 自定义
        {
            GetDlgItem(IDC_EDIT_AV_BIT_RATE)->EnableWindow(TRUE);
            m_comboAverageBitRate.SetCurSel(m_comboAverageBitRate.GetCount()-1);		//adjust bit rate settings
            m_iAvBitRate = (m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.wAverageVideoBitrate & 0x7fff)/*/1024*/;
        }
        else
        {
            SetAvBitrateCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.wAverageVideoBitrate);
            m_iAvBitRate = 0;
            GetDlgItem(IDC_EDIT_AV_BIT_RATE)->EnableWindow(FALSE);
		}	
        
		break;
	case SUB_STREAM_COMPRESSION:	
//         GetSubResolutionAbility();
		GetDlgItem(IDC_COMBO_STREAM_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_RESOLUTION)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FRAME_I_INTERVAL)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_FRAME_BP_INTERVAL)->EnableWindow(TRUE);
		if ((m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate >> 31) & 0x01)
		{
			GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(TRUE);
			m_comboBitRate.SetCurSel(m_comboBitRate.GetCount()-1);		//adjust bit rate settings
			m_iBitRate = (m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate & 0x7fffffff)/1024;
		}
		else
		{
            SetBitrateCurSel(m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate);
            m_iBitRate = 0;
			GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(FALSE);
		}


        SetResolutionCurSel(m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byResolution);
		m_comboStreamType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byStreamType);
		m_comboImageQuality.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byPicQuality);
        SetBitrateTypeCurSel(m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byBitrateType);
		SetFrameCurSel(m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate);
        //m_comboFrameRate.SetCurSel(m_struCompressionCfg[m_iCurChanIndex].struNetPara.dwVideoFrameRate);	
		m_comboFrameBPInterval.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame);	
		m_iFrameIInterval = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI;

		if (m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncType > 2)
		{
			m_comboVideoType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncType - 4);
		}
		else
		{
            m_comboVideoType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncType);
		}
		m_comboAudioType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byAudioEncType);
		m_comboVideoEncComplexity.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity);
//		m_bChkEnableSvc = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byEnableSvc;
        m_comSVC.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byEnableSvc);
		m_byStreamSmooth = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byStreamSmooth;		
		m_comboAudioBitRate.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byAudioBitRate);
		m_comboSamplingRate.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byAudioSamplingRate);
        m_bChkSmartCodec = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.bySmartCodec;
        m_bDepthMapEnable = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byDepthMapEnable & 0x01;
        m_bYStreamEnable = (m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byDepthMapEnable & 0x02) >> 1;
        m_comboAverageBitRate.SetCurSel(m_comboAverageBitRate.GetCount()-1);
		break;
	case EVENT_INVOKE_COMPRESSION:
  //      GetEventResolutionAbility();
		GetDlgItem(IDC_CHK_EVENT_COMPRESS)->ShowWindow(SW_SHOW);
		if (m_iCurChanIndex < MAX_ANALOG_CHANNUM)
		{
			EnableEventCtrl(TRUE);
		}
		else
		{
			EnableEventCtrl(FALSE);
		}
		
		
		if ((m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoBitrate >> 31) & 0x01)
		{
			GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(TRUE);
			m_comboBitRate.SetCurSel(m_comboBitRate.GetCount()-1);		//adjust bit rate settings
			m_iBitRate = (m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoBitrate & 0x7fffffff)/1024;
		}
		else
		{
            SetBitrateCurSel(m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoBitrate);
            m_iBitRate = 0;
			GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(FALSE);
		}
		// 		dwResoltion = m_struCompressionCfg[m_iCurChanIndex].struEventRecordPara.byResolution;
		// 		if (dwResoltion >=15)
		// 		{
		// 			dwResoltion = dwResoltion - 11;
		// 		}
		// 		m_comboResolution.SetCurSel(dwResoltion);
		if (m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamType & 0x80)
		{
			m_bEventCompress = TRUE;
			m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamType &= 0x7f;
		}
		else
		{
			m_bEventCompress = FALSE;
			//m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamType &= 0x0;

		}
        SetResolutionCurSel(m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byResolution);
		m_comboStreamType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamType);
		m_comboImageQuality.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byPicQuality);
        SetBitrateTypeCurSel(m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byBitrateType);
        SetFrameCurSel(m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoFrameRate);

		m_comboFrameBPInterval.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byIntervalBPFrame);	
		m_iFrameIInterval = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.wIntervalFrameI;
		//2011-05-01
		if (m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncType == 0xff)
		{
			//not support this parameter, disable the Combo
			m_comboVideoType.EnableWindow(FALSE);
			m_comboVideoType.SetCurSel(0);
		}
// 		else
// 		{
//             m_comboVideoType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncType);
// 		}
		else if (m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncType > 2)
		{
			m_comboVideoType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncType - 4);
		}
		else
		{
            m_comboVideoType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncType);
		}
		
		if (m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byAudioEncType == 0xff)
		{
			//not support this parameter, disable the Combo
			m_comboAudioType.EnableWindow(FALSE);
			m_comboAudioType.SetCurSel(0);
		}
		else
		{
			m_comboAudioType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byAudioEncType);
		}
		m_comboVideoEncComplexity.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncComplexity);
//		m_bChkEnableSvc = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byEnableSvc;
        m_comSVC.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byEnableSvc);
		m_comboAudioBitRate.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byAudioBitRate);
		m_byStreamSmooth = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamSmooth;	
		m_comboSamplingRate.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byAudioSamplingRate);
        m_bChkSmartCodec = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.bySmartCodec;
        m_bDepthMapEnable = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byDepthMapEnable & 0x01;
        m_bYStreamEnable = (m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byDepthMapEnable & 0x02) >> 1;
        m_comboAverageBitRate.SetCurSel(m_comboAverageBitRate.GetCount()-1);
		break;
	case THIRD_STREAM_COMPRESSION:
  //      GetThirdResolutionAbility();
		GetDlgItem(IDC_COMBO_STREAM_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_RESOLUTION)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FRAME_I_INTERVAL)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_FRAME_BP_INTERVAL)->EnableWindow(TRUE);
		if ((m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate >> 31) & 0x01)
		{
			GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(TRUE);
			m_comboBitRate.SetCurSel(m_comboBitRate.GetCount()-1);		//adjust bit rate settings
			m_iBitRate = (m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate & 0x7fffffff)/1024;
		}
		else
		{
            SetBitrateCurSel(m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate);
            m_iBitRate = 0;
			GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(FALSE);
		}
		
		// 		dwResoltion = m_struCompressionCfg[m_iCurChanIndex].struNetPara.byResolution;
		// // 		if (dwResoltion >=16)
		// // 		{
		// // 			dwResoltion = dwResoltion - 11;
		// // 		}
		// 		m_comboResolution.SetCurSel(dwResoltion-1);
        SetResolutionCurSel(m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byResolution);
		m_comboStreamType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byStreamType);
		m_comboImageQuality.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byPicQuality);
        SetBitrateTypeCurSel(m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byBitrateType);
		SetFrameCurSel(m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate);
        //m_comboFrameRate.SetCurSel(m_struCompressionCfg[m_iCurChanIndex].struNetPara.dwVideoFrameRate);	
		m_comboFrameBPInterval.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame);	
		m_iFrameIInterval = m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI;
		
		if (m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byVideoEncType > 2)
		{
			m_comboVideoType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byVideoEncType - 4);
		}
		else
		{
            m_comboVideoType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byVideoEncType);
		}
		m_comboAudioType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byAudioEncType);
		m_comboVideoEncComplexity.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity);
//		m_bChkEnableSvc = m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byEnableSvc;
        m_comSVC.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byEnableSvc);
		m_comboAudioBitRate.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byAudioBitRate);
		m_byStreamSmooth = m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byStreamSmooth;	
		m_comboSamplingRate.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byAudioSamplingRate);
        m_bChkSmartCodec = m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.bySmartCodec;
        m_bDepthMapEnable = m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byDepthMapEnable & 0x01;
        m_bYStreamEnable = (m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byDepthMapEnable & 0x02) >> 1;
        m_comboAverageBitRate.SetCurSel(m_comboAverageBitRate.GetCount()-1);
		break;
	case TRANS_STREAM_COMPRESSION:
        GetTranscodeResolutionAbility();
		GetDlgItem(IDC_COMBO_STREAM_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_RESOLUTION)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FRAME_I_INTERVAL)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_FRAME_BP_INTERVAL)->EnableWindow(TRUE);
		if ((m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate >> 31) & 0x01)
		{
			GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(TRUE);
			m_comboBitRate.SetCurSel(m_comboBitRate.GetCount()-1);		//adjust bit rate settings
			m_iBitRate = (m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate & 0x7fffffff)/1024;
		}
		else
		{
            SetBitrateCurSel(m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate);
            m_iBitRate = 0;
			GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(FALSE);
		}
		
		// 		dwResoltion = m_struCompressionCfg[m_iCurChanIndex].struNetPara.byResolution;
		// // 		if (dwResoltion >=16)
		// // 		{
		// // 			dwResoltion = dwResoltion - 11;
		// // 		}
		// 		m_comboResolution.SetCurSel(dwResoltion-1);
        SetResolutionCurSel(m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byResolution);
		m_comboStreamType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byStreamType);
		m_comboImageQuality.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byPicQuality);
        SetBitrateTypeCurSel(m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byBitrateType);
		SetFrameCurSel(m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate);
        //m_comboFrameRate.SetCurSel(m_struCompressionCfg[m_iCurChanIndex].struNetPara.dwVideoFrameRate);	
		m_comboFrameBPInterval.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame);	
		m_iFrameIInterval = m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI;
		
		if (m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byVideoEncType > 2)
		{
			m_comboVideoType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byVideoEncType - 4);
		}
		else
		{
            m_comboVideoType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byVideoEncType);
		}
		m_comboAudioType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byAudioEncType);
		m_comboVideoEncComplexity.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity);
//		m_bChkEnableSvc = m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byEnableSvc;
        m_comSVC.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byEnableSvc);
		m_comboAudioBitRate.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byAudioBitRate);	
		m_byStreamSmooth = m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byStreamSmooth;
		m_comboSamplingRate.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byAudioSamplingRate);
        m_bChkSmartCodec = m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.bySmartCodec;
        m_bDepthMapEnable = m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byDepthMapEnable & 0x01;
        m_bYStreamEnable = (m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byDepthMapEnable & 0x02) >> 1;
        m_comboAverageBitRate.SetCurSel(m_comboAverageBitRate.GetCount()-1);
		break;
	default:
        if (iCompressionType > TRANS_STREAM_COMPRESSION && iCompressionType < 11)
        {
            GetDlgItem(IDC_COMBO_STREAM_TYPE)->EnableWindow(TRUE);
            GetDlgItem(IDC_COMBO_RESOLUTION)->EnableWindow(TRUE);
            GetDlgItem(IDC_EDIT_FRAME_I_INTERVAL)->EnableWindow(TRUE);
            GetDlgItem(IDC_COMBO_FRAME_BP_INTERVAL)->EnableWindow(TRUE);

            //码率类型，定码率 or 变码率
            SetBitrateTypeCurSel(m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byBitrateType);

            //码率上限
            if ((m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.dwVideoBitrate >> 31) & 0x01) // 自定义
            {
                GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(TRUE);
                m_comboBitRate.SetCurSel(m_comboBitRate.GetCount() - 1);		//adjust bit rate settings
                m_iBitRate = (m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.dwVideoBitrate & 0x7fffffff) / 1024;
            }
            else
            {
                SetBitrateCurSel(m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.dwVideoBitrate);
                m_iBitRate = 0;
                GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(FALSE);
            }

            SetResolutionCurSel(m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byResolution);
            m_comboStreamType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byStreamType);
            m_comboImageQuality.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byPicQuality);

            //m_comboBitRateType.SetCurSel(m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byBitrateType);
            SetFrameCurSel(m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.dwVideoFrameRate);
            //m_comboFrameRate.SetCurSel(m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.dwVideoFrameRate);
            m_comboFrameBPInterval.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byIntervalBPFrame);
            m_iFrameIInterval = m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.wIntervalFrameI;

            //		m_comboVideoType.EnableWindow(FALSE);
            //		m_comboAudioType.EnableWindow(FALSE);
            //2011-05-01
            if (m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byVideoEncType == 0xff)
            {
                //not support this parameter, disable the Combo
                m_comboVideoType.EnableWindow(FALSE);
                m_comboVideoType.SetCurSel(0);
            }
            // 		else
            // 		{
            //             m_comboVideoType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncType);
            // 		}

            else if (m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byVideoEncType > 2)
            {
                m_comboVideoType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byVideoEncType - 4);
            }
            else
            {
                m_comboVideoType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byVideoEncType);
            }

            if (m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byAudioEncType == 0xff)
            {
                //not support this parameter, disable the Combo
                m_comboAudioType.EnableWindow(FALSE);
                m_comboAudioType.SetCurSel(0);
            }
            else
            {
                m_comboAudioType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byAudioEncType);
            }
            m_comboVideoEncComplexity.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byVideoEncComplexity);
            //m_bChkEnableSvc = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byEnableSvc;
            m_comSVC.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byEnableSvc);
            m_comboAudioBitRate.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byAudioBitRate);
            m_byStreamSmooth = m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byStreamSmooth;
            m_comboSamplingRate.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byAudioSamplingRate);
            m_bChkSmartCodec = m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.bySmartCodec;
            m_bDepthMapEnable = m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byDepthMapEnable & 0x01;
            m_bYStreamEnable = (m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byDepthMapEnable & 0x02) >> 1;
            //m_comboAverageBitRate.SetCurSel(m_comboAverageBitRate.GetCount()-1);

            //平均码率
            if ((m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.wAverageVideoBitrate >> 15) & 0x01) // 自定义
            {
                GetDlgItem(IDC_EDIT_AV_BIT_RATE)->EnableWindow(TRUE);
                m_comboAverageBitRate.SetCurSel(m_comboAverageBitRate.GetCount() - 1);		//adjust bit rate settings
                m_iAvBitRate = (m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.wAverageVideoBitrate & 0x7fff)/*/1024*/;
            }
            else
            {
                SetAvBitrateCurSel(m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.wAverageVideoBitrate);
                m_iAvBitRate = 0;
                GetDlgItem(IDC_EDIT_AV_BIT_RATE)->EnableWindow(FALSE);
            }
        }
		break;
	}
	UpdateData(FALSE);
}

/*********************************************************
Function:	OnCbnSelchangeComboCompressionType
Desc:		update compression parameters and control display
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgChanCfg::OnCbnSelchangeComboCompressionType()
{
//	SaveLastCompressTypePara();
	UpdateData(TRUE);
	int iCmpType = NORM_HIGH_STREAM_COMPRESSION;
	switch(m_comboCompressionType.GetCurSel())
	{
	case 0:
		iCmpType = NORM_HIGH_STREAM_COMPRESSION;
		break;
	case 1:
		iCmpType = SUB_STREAM_COMPRESSION;
		break;
	case 2:
		iCmpType = EVENT_INVOKE_COMPRESSION;
		break;
	case 3:
		iCmpType = THIRD_STREAM_COMPRESSION;
		break;
	case 4:
		iCmpType = TRANS_STREAM_COMPRESSION;
		break;
	default:
        iCmpType = m_comboCompressionType.GetCurSel();
		break;
	}
// 	if (m_iCompressionTypeSel == iCmpType)
// 	{
// 		return;
// 	}
	m_iCompressionTypeSel = iCmpType;
	UpdateCompressionInfo();
	DoUpdateFrame();
	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnBnClickedBtnCmpOk
  Desc:		finish compression paramertes modification
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedBtnCmpOk()
{
	UpdateData(TRUE);
	DWORD dwDefBitRate = 0;
	BYTE byEventResolution = 0;
    int iCompressionType = m_comboCompressionType.GetCurSel();

	m_pStruAudioIn[m_iCurChanIndex].byAudioInputType = m_comboAudioInType.GetCurSel();
	m_pStruAudioIn[m_iCurChanIndex].byVolume = m_byVolume;
	m_pStruAudioIn[m_iCurChanIndex].byEnableNoiseFilter = m_bEnableNoiseFilter;
	switch (m_comboCompressionType.GetCurSel())
	{
	case NORM_HIGH_STREAM_COMPRESSION:
		CheckRebootParam( &(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byStreamType),\
			m_comboStreamType.GetCurSel(), FALSE);

		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byPicQuality = (BYTE)m_comboImageQuality.GetCurSel();
		if (m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel()) == -1)	//adjust bit rate settings
		{
			dwDefBitRate = m_iBitRate*1024;		
			if (dwDefBitRate < 32*1024)
			{
				dwDefBitRate = 32*1024;
			}
//2010-6-9 删除下面对码率上限的限制
// 			if (dwDefBitRate > 8192*1024)
// 			{
// 				dwDefBitRate =  8192*1024;
// 			}
			dwDefBitRate |= 0x80000000;
			m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = dwDefBitRate;
		}
		else
		{
			m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel());
		}
// 		CheckRebootParam( &(m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byResolution),\
// 			m_comboResolution.GetCurSel(), TRUE);
        m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byResolution = m_comboResolution.GetItemData(m_comboResolution.GetCurSel());
		//	m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byResolution = m_comboResolution.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate = m_comboFrameRate.GetItemData(m_comboFrameRate.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byBitrateType = (BYTE)m_comboBitRateType.GetItemData(m_comboBitRateType.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame = (BYTE)m_comboFrameBPInterval.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI = (WORD)m_iFrameIInterval;
		
		if (m_comboVideoType.GetCurSel() == 3 ||m_comboVideoType.GetCurSel() == 4 || m_comboVideoType.GetCurSel() == 5 || m_comboVideoType.GetCurSel() == 6)
		{
			m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel() + 4;
		}
		else
		{
            m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel();
		}
		
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byAudioEncType = (BYTE)m_comboAudioType.GetCurSel();		
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity = (BYTE)m_comboVideoEncComplexity.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byAudioBitRate = (BYTE)m_comboAudioBitRate.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byStreamSmooth = m_byStreamSmooth;	
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byAudioSamplingRate = (BYTE)m_comboSamplingRate.GetCurSel();
		break;
	case SUB_STREAM_COMPRESSION:
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byStreamType = (BYTE)m_comboStreamType.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byPicQuality = (BYTE)m_comboImageQuality.GetCurSel();
		if (m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel()) == -1)	//adjust bit rate settings
		{
			dwDefBitRate = m_iBitRate*1024;		
			if (dwDefBitRate < 32*1024)
			{
				dwDefBitRate = 32*1024;
			}
//2010-6-9 删除下面对码率上限的限制
// 			if (dwDefBitRate > 8192*1024)
// 			{
// 				dwDefBitRate =  8192*1024;
// 			}
			dwDefBitRate |= 0x80000000;
			m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = dwDefBitRate;
		}
		else
		{
			m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel());
		}
		
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byResolution = (BYTE)(m_comboResolution.GetItemData(m_comboResolution.GetCurSel()));
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate = m_comboFrameRate.GetItemData(m_comboFrameRate.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byBitrateType = (BYTE)m_comboBitRateType.GetItemData(m_comboBitRateType.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame = (BYTE)m_comboFrameBPInterval.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI = (WORD)m_iFrameIInterval;
		if (m_comboVideoType.GetCurSel() == 3 ||m_comboVideoType.GetCurSel() == 4 || m_comboVideoType.GetCurSel() == 5 || m_comboVideoType.GetCurSel() == 6)
		{
			m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel() + 4;
		}
		else
		{
            m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel();
		}
		
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byAudioEncType = (BYTE)m_comboAudioType.GetCurSel();		
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity = (BYTE)m_comboVideoEncComplexity.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byAudioBitRate = (BYTE)m_comboAudioBitRate.GetCurSel();	
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byStreamSmooth = m_byStreamSmooth;	
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byAudioSamplingRate = (BYTE)m_comboSamplingRate.GetCurSel();
		break;
	case EVENT_INVOKE_COMPRESSION:
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamType = (BYTE)m_comboStreamType.GetCurSel();
		if (m_bEventCompress)
		{
			m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamType |= 0x80;
		}
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byPicQuality = (BYTE)m_comboImageQuality.GetCurSel();
		if (m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel()) == -1)	//adjust bit rate settings
		{
			dwDefBitRate = m_iBitRate*1024;		
			if (dwDefBitRate < 32*1024)
			{
				dwDefBitRate = 32*1024;
			}
//2010-6-9 删除下面对码率上限的限制
// 			if (dwDefBitRate > 8192*1024)
// 			{
// 				dwDefBitRate =  8192*1024;
// 			}
			dwDefBitRate |= 0x80000000;
			m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoBitrate = dwDefBitRate;
		}
		else
		{
			m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoBitrate = m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel());
		}
		
		byEventResolution = (BYTE)m_comboResolution.GetItemData(m_comboResolution.GetCurSel());
		
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byResolution = byEventResolution;
		
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoFrameRate = m_comboFrameRate.GetItemData(m_comboFrameRate.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byBitrateType = (BYTE)m_comboBitRateType.GetItemData(m_comboBitRateType.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byIntervalBPFrame = (BYTE)m_comboFrameBPInterval.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.wIntervalFrameI = (WORD)m_iFrameIInterval;
	
		//		m_struCompressionCfg[m_iCurChanIndex].struEventRecordPara.byIntervalBPFrame = m_comboFrameBPInterval.GetCurSel();//same with main stream
		//m_struCompressionCfg[m_iCurChanIndex].struEventRecordPara.wIntervalFrameI = m_iFrameIInterval;//same with main stream


		
		if (m_comboVideoType.GetCurSel() == 3 ||m_comboVideoType.GetCurSel() == 4 || m_comboVideoType.GetCurSel() == 5 || m_comboVideoType.GetCurSel() == 6)
		{
			m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel() + 4;
		}
		else
		{
            m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel();
		}
		
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byAudioEncType = (BYTE)m_comboAudioType.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncComplexity = (BYTE)m_comboVideoEncComplexity.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byAudioBitRate = (BYTE)m_comboAudioBitRate.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamSmooth = m_byStreamSmooth;
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byAudioSamplingRate = (BYTE)m_comboSamplingRate.GetCurSel();
		break;
	case THIRD_STREAM_COMPRESSION:
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].dwStreamType = THIRD_STREAM_COMPRESSION;
        m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byStreamType = (BYTE)m_comboStreamType.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byPicQuality = (BYTE)m_comboImageQuality.GetCurSel();
		if (m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel()) == -1)	//adjust bit rate settings
		{
			dwDefBitRate = m_iBitRate*1024;		
			if (dwDefBitRate < 32*1024)
			{
				dwDefBitRate = 32*1024;
			}
			//2010-6-9 删除下面对码率上限的限制
			// 			if (dwDefBitRate > 8192*1024)
			// 			{
			// 				dwDefBitRate =  8192*1024;
			// 			}
			dwDefBitRate |= 0x80000000;
			m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = dwDefBitRate;
		}
		else
		{
			m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel());
		}
		
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byResolution = (BYTE)(m_comboResolution.GetItemData(m_comboResolution.GetCurSel()));
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate = m_comboFrameRate.GetItemData(m_comboFrameRate.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byBitrateType = (BYTE)m_comboBitRateType.GetItemData(m_comboBitRateType.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame = (BYTE)m_comboFrameBPInterval.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI = (WORD)m_iFrameIInterval;
		if (m_comboVideoType.GetCurSel() == 3 ||m_comboVideoType.GetCurSel() == 4 || m_comboVideoType.GetCurSel() == 5 || m_comboVideoType.GetCurSel() == 6)
		{
			m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel() + 4;
		}
		else
		{
            m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel();
		}
		
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byAudioEncType = (BYTE)m_comboAudioType.GetCurSel();		
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity = (BYTE)m_comboVideoEncComplexity.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byAudioBitRate = (BYTE)m_comboAudioBitRate.GetCurSel();	
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byStreamSmooth = m_byStreamSmooth;
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byAudioSamplingRate = (BYTE)m_comboSamplingRate.GetCurSel();
		break;
	case TRANS_STREAM_COMPRESSION:
		m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].dwStreamType = TRANS_STREAM_COMPRESSION;
        m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byStreamType = (BYTE)m_comboStreamType.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byPicQuality = (BYTE)m_comboImageQuality.GetCurSel();
		if (m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel()) == -1)	//adjust bit rate settings
		{
			dwDefBitRate = m_iBitRate*1024;		
			if (dwDefBitRate < 32*1024)
			{
				dwDefBitRate = 32*1024;
			}
			//2010-6-9 删除下面对码率上限的限制
			// 			if (dwDefBitRate > 8192*1024)
			// 			{
			// 				dwDefBitRate =  8192*1024;
			// 			}
			dwDefBitRate |= 0x80000000;
			m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = dwDefBitRate;
		}
		else
		{
			m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel());
		}
		
		m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byResolution = (BYTE)(m_comboResolution.GetItemData(m_comboResolution.GetCurSel()));
		m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate = m_comboFrameRate.GetItemData(m_comboFrameRate.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byBitrateType = (BYTE)m_comboBitRateType.GetItemData(m_comboBitRateType.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame = (BYTE)m_comboFrameBPInterval.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI = (WORD)m_iFrameIInterval;
		if (m_comboVideoType.GetCurSel() == 3 ||m_comboVideoType.GetCurSel() == 4 || m_comboVideoType.GetCurSel() == 5 || m_comboVideoType.GetCurSel() == 6)
		{
			m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel() + 4;
		}
		else
		{
            m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel();
		}
		
		m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byAudioEncType = (BYTE)m_comboAudioType.GetCurSel();		
		m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity = (BYTE)m_comboVideoEncComplexity.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byAudioBitRate = (BYTE)m_comboBitRate.GetCurSel();		
		m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byStreamSmooth = m_byStreamSmooth;	
		m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byAudioSamplingRate = (BYTE)m_comboSamplingRate.GetCurSel();
		break;
	default:
        if (iCompressionType > TRANS_STREAM_COMPRESSION && iCompressionType < 11)
        {
            CheckRebootParam(&(m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byStreamType), \
                m_comboStreamType.GetCurSel(), FALSE);

            m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byPicQuality = (BYTE)m_comboImageQuality.GetCurSel();
            if (m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel()) == -1)	//adjust bit rate settings
            {
                dwDefBitRate = m_iBitRate * 1024;
                if (dwDefBitRate < 32 * 1024)
                {
                    dwDefBitRate = 32 * 1024;
                }
                //2010-6-9 删除下面对码率上限的限制
                // 			if (dwDefBitRate > 8192*1024)
                // 			{
                // 				dwDefBitRate =  8192*1024;
                // 			}
                dwDefBitRate |= 0x80000000;
                m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.dwVideoBitrate = dwDefBitRate;
            }
            else
            {
                m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.dwVideoBitrate = m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel());
            }
            // 		CheckRebootParam( &(m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byResolution),\
                                                // 			m_comboResolution.GetCurSel(), TRUE);
            m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byResolution = m_comboResolution.GetItemData(m_comboResolution.GetCurSel());
            //	m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byResolution = m_comboResolution.GetCurSel();
            m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.dwVideoFrameRate = m_comboFrameRate.GetItemData(m_comboFrameRate.GetCurSel());
            m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byBitrateType = (BYTE)m_comboBitRateType.GetItemData(m_comboBitRateType.GetCurSel());
            m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byIntervalBPFrame = (BYTE)m_comboFrameBPInterval.GetCurSel();
            m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.wIntervalFrameI = (WORD)m_iFrameIInterval;

            if (m_comboVideoType.GetCurSel() == 3 || m_comboVideoType.GetCurSel() == 4 || m_comboVideoType.GetCurSel() == 5 || m_comboVideoType.GetCurSel() == 6)
            {
                m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel() + 4;
            }
            else
            {
                m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel();
            }

            m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byAudioEncType = (BYTE)m_comboAudioType.GetCurSel();
            m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byVideoEncComplexity = (BYTE)m_comboVideoEncComplexity.GetCurSel();
            m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byAudioBitRate = (BYTE)m_comboAudioBitRate.GetCurSel();
            m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byStreamSmooth = m_byStreamSmooth;
            m_struMSCompressionCfg[m_iCurChanIndex][iCompressionType].struStreamPara.byAudioSamplingRate = (BYTE)m_comboSamplingRate.GetCurSel();
        }
		break;
	}
}


/*********************************************************
  Function:	SaveLastCompressTypePara
  Desc:		Save parameter when Compress Type changed
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::SaveLastCompressTypePara()
{
    UpdateData(TRUE);
	DWORD dwDefBitRate = 0;
	BYTE byEventResolution = 0;
	switch (m_iCompressionTypeSel)
	{
	case NORM_HIGH_STREAM_COMPRESSION:
		CheckRebootParam( &(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byStreamType),\
			m_comboStreamType.GetCurSel(), FALSE);
		
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byPicQuality = (BYTE)m_comboImageQuality.GetCurSel();
		if (m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel()) == -1)	//adjust bit rate settings
		{
			dwDefBitRate = m_iBitRate*1024;		
			if (dwDefBitRate < 32*1024)
			{
				dwDefBitRate = 32*1024;
			}
//2010-6-9 删除下面对码率上限的限制
// 			if (dwDefBitRate > 8192*1024)
// 			{
// 				dwDefBitRate =  8192*1024;
// 			}
			dwDefBitRate |= 0x80000000;
			m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = dwDefBitRate;
		}
		else
		{
			m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel());
		}
// 		CheckRebootParam( &(m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byResolution),\
// 			m_comboResolution.GetCurSel(), TRUE);
        m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byResolution = m_comboResolution.GetItemData(m_comboResolution.GetCurSel());
	//	m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byResolution = m_comboResolution.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate = m_comboFrameRate.GetItemData(m_comboFrameRate.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byBitrateType = (BYTE)m_comboBitRateType.GetItemData(m_comboBitRateType.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame = (BYTE)m_comboFrameBPInterval.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI = (WORD)m_iFrameIInterval;

		if (m_comboVideoType.GetCurSel() == 3 ||m_comboVideoType.GetCurSel() == 4 || m_comboVideoType.GetCurSel() == 5 || m_comboVideoType.GetCurSel() == 6)
		{
			m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel() + 4;
		}
		else
		{
            m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel();
		}
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byAudioEncType = (BYTE)m_comboAudioType.GetCurSel();		
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity = (BYTE)m_comboVideoEncComplexity.GetCurSel();
//		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byEnableSvc = m_bChkEnableSvc;
        m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byEnableSvc = m_comSVC.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byAudioBitRate = (BYTE)m_comboAudioBitRate.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byStreamSmooth = m_byStreamSmooth;	
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byAudioSamplingRate = (BYTE)m_comboSamplingRate.GetCurSel();
        m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.bySmartCodec = m_bChkSmartCodec;
        if (m_bDepthMapEnable)
        {
            m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byDepthMapEnable |= 0x01;
        }
        else
        {
            m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byDepthMapEnable &= 0xfe;
        }
        if (m_bYStreamEnable)
        {
            m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byDepthMapEnable |= 0x02;
        }
        else
        {
            m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byDepthMapEnable &= 0xfd;
        }
        //m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byDepthMapEnable = m_bDepthMapEnable;

        if (m_comboAverageBitRate.GetItemData(m_comboAverageBitRate.GetCurSel()) == -1)	//adjust bit rate settings
        {
            dwDefBitRate = m_iAvBitRate/**1024*/;
            dwDefBitRate |= 0x8000;
            m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.wAverageVideoBitrate = dwDefBitRate;
        }
        else
        {
            m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.wAverageVideoBitrate = m_comboAverageBitRate.GetItemData(m_comboAverageBitRate.GetCurSel());
		}

		break;
	case SUB_STREAM_COMPRESSION:
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byStreamType = (BYTE)m_comboStreamType.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byPicQuality = (BYTE)m_comboImageQuality.GetCurSel();
		if (m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel()) == -1)	//adjust bit rate settings
		{
			dwDefBitRate = m_iBitRate*1024;		
			if (dwDefBitRate < 32*1024)
			{
				dwDefBitRate = 32*1024;
			}
//2010-6-9 删除下面对码率上限的限制
// 			if (dwDefBitRate > 8192*1024)
// 			{
// 				dwDefBitRate =  8192*1024;
// 			}
			dwDefBitRate |= 0x80000000;
			m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = dwDefBitRate;
		}
		else
		{
			m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel());
		}
		
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byResolution = (BYTE)(m_comboResolution.GetItemData(m_comboResolution.GetCurSel()));
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate = m_comboFrameRate.GetItemData(m_comboFrameRate.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byBitrateType = (BYTE)m_comboBitRateType.GetItemData(m_comboBitRateType.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame = (BYTE)m_comboFrameBPInterval.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI = (WORD)m_iFrameIInterval;
		if (m_comboVideoType.GetCurSel() == 3||m_comboVideoType.GetCurSel() == 4 || m_comboVideoType.GetCurSel() == 5 || m_comboVideoType.GetCurSel() == 6)
		{
			m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel() + 4;
		}
		else
		{
            m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel();
		}
		
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byAudioEncType = (BYTE)m_comboAudioType.GetCurSel();		
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity = (BYTE)m_comboVideoEncComplexity.GetCurSel();
//		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byEnableSvc = m_bChkEnableSvc;
        m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byEnableSvc = m_comSVC.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byAudioBitRate = (BYTE)m_comboAudioBitRate.GetCurSel();	
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byStreamSmooth = m_byStreamSmooth;
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byAudioSamplingRate = (BYTE)m_comboSamplingRate.GetCurSel();
        m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.bySmartCodec = m_bChkSmartCodec;
        if (m_bDepthMapEnable)
        {
            m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byDepthMapEnable |= 0x01;
        }
        else
        {
            m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byDepthMapEnable &= 0xfe;
        }
        if (m_bYStreamEnable)
        {
            m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byDepthMapEnable |= 0x02;
        }
        else
        {
            m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byDepthMapEnable &= 0xfd;
        }
		break;
	case EVENT_INVOKE_COMPRESSION:
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamType = (BYTE)m_comboStreamType.GetCurSel();
		if (m_bEventCompress)
		{
			m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamType |= 0x80;
		//	m_bEventCompress = FALSE;
		}
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byPicQuality = (BYTE)m_comboImageQuality.GetCurSel();
		if (m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel()) == -1)	//adjust bit rate settings
		{
			dwDefBitRate = m_iBitRate*1024;		
			if (dwDefBitRate < 32*1024)
			{
				dwDefBitRate = 32*1024;
			}
//2010-6-9 删除下面对码率上限的限制
// 			if (dwDefBitRate > 8192*1024)
// 			{
// 				dwDefBitRate =  8192*1024;
// 			}
			dwDefBitRate |= 0x80000000;
			m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoBitrate = dwDefBitRate;
		}
		else
		{
			m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoBitrate = m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel());
		}

		byEventResolution = (BYTE)m_comboResolution.GetItemData(m_comboResolution.GetCurSel());

		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byResolution = byEventResolution;

		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoFrameRate = m_comboFrameRate.GetItemData(m_comboFrameRate.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byBitrateType = (BYTE)m_comboBitRateType.GetItemData(m_comboBitRateType.GetCurSel());
//		m_struCompressionCfg[m_iCurChanIndex].struEventRecordPara.byIntervalBPFrame = m_comboFrameBPInterval.GetCurSel();//same with main stream
		//m_struCompressionCfg[m_iCurChanIndex].struEventRecordPara.wIntervalFrameI = m_iFrameIInterval;//same with main stream

		if (m_comboVideoType.GetCurSel() == 3||m_comboVideoType.GetCurSel() == 4 || m_comboVideoType.GetCurSel() == 5 || m_comboVideoType.GetCurSel() == 6)
		{
			m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel() + 4;
		}
		else
		{
            m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel();
		}
		
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byAudioEncType = (BYTE)m_comboAudioType.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncComplexity = (BYTE)m_comboVideoEncComplexity.GetCurSel();
//		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byEnableSvc = m_bChkEnableSvc;
        m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byEnableSvc = m_comSVC.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byAudioBitRate = (BYTE)m_comboAudioBitRate.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamSmooth = m_byStreamSmooth;	
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byAudioSamplingRate = (BYTE)m_comboSamplingRate.GetCurSel();
        m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.bySmartCodec = m_bChkSmartCodec;
        if (m_bDepthMapEnable)
        {
            m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byDepthMapEnable |= 0x01;
        }
        else
        {
            m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byDepthMapEnable &= 0xfe;
        }
        if (m_bYStreamEnable)
        {
            m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byDepthMapEnable |= 0x02;
        }
        else
        {
            m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byDepthMapEnable &= 0xfd;
        }
		break;
	case THIRD_STREAM_COMPRESSION:
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].dwStreamType = THIRD_STREAM_COMPRESSION;
        m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byStreamType = (BYTE)m_comboStreamType.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byPicQuality = (BYTE)m_comboImageQuality.GetCurSel();
		if (m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel()) == -1)	//adjust bit rate settings
		{
			dwDefBitRate = m_iBitRate*1024;		
			if (dwDefBitRate < 32*1024)
			{
				dwDefBitRate = 32*1024;
			}
			//2010-6-9 删除下面对码率上限的限制
			// 			if (dwDefBitRate > 8192*1024)
			// 			{
			// 				dwDefBitRate =  8192*1024;
			// 			}
			dwDefBitRate |= 0x80000000;
			m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = dwDefBitRate;
		}
		else
		{
			m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel());
		}
		
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byResolution = (BYTE)(m_comboResolution.GetItemData(m_comboResolution.GetCurSel()));
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate = m_comboFrameRate.GetItemData(m_comboFrameRate.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byBitrateType = (BYTE)m_comboBitRateType.GetItemData(m_comboBitRateType.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame = (BYTE)m_comboFrameBPInterval.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI = (WORD)m_iFrameIInterval;
		if (m_comboVideoType.GetCurSel() == 3||m_comboVideoType.GetCurSel() == 4 || m_comboVideoType.GetCurSel() == 5 || m_comboVideoType.GetCurSel() == 6)
		{
			m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel() + 4;
		}
		else
		{
            m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel();
		}
		
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byAudioEncType = (BYTE)m_comboAudioType.GetCurSel();		
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity = (BYTE)m_comboVideoEncComplexity.GetCurSel();
//		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byEnableSvc = m_bChkEnableSvc;
        m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byEnableSvc = m_comSVC.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byAudioBitRate = (BYTE)m_comboAudioBitRate.GetCurSel();	
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byStreamSmooth = m_byStreamSmooth;		
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byAudioSamplingRate = (BYTE)m_comboSamplingRate.GetCurSel();
        m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.bySmartCodec = m_bChkSmartCodec;
        if (m_bDepthMapEnable)
        {
            m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byDepthMapEnable |= 0x01;
        }
        else
        {
            m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byDepthMapEnable &= 0xfe;
        }
        if (m_bYStreamEnable)
        {
            m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byDepthMapEnable |= 0x02;
        }
        else
        {
            m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byDepthMapEnable &= 0xfd;
        }
		break;
	case TRANS_STREAM_COMPRESSION:
		m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].dwStreamType = TRANS_STREAM_COMPRESSION;
        m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byStreamType = (BYTE)m_comboStreamType.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byPicQuality = (BYTE)m_comboImageQuality.GetCurSel();
		if (m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel()) == -1)	//adjust bit rate settings
		{
			dwDefBitRate = m_iBitRate*1024;		
			if (dwDefBitRate < 32*1024)
			{
				dwDefBitRate = 32*1024;
			}
			//2010-6-9 删除下面对码率上限的限制
			// 			if (dwDefBitRate > 8192*1024)
			// 			{
			// 				dwDefBitRate =  8192*1024;
			// 			}
			dwDefBitRate |= 0x80000000;
			m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = dwDefBitRate;
		}
		else
		{
			m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel());
		}
		
		m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byResolution = (BYTE)(m_comboResolution.GetItemData(m_comboResolution.GetCurSel()));
		m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate = m_comboFrameRate.GetItemData(m_comboFrameRate.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byBitrateType = (BYTE)m_comboBitRateType.GetItemData(m_comboBitRateType.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame = (BYTE)m_comboFrameBPInterval.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI = (WORD)m_iFrameIInterval;
		if (m_comboVideoType.GetCurSel() == 3||m_comboVideoType.GetCurSel() == 4 || m_comboVideoType.GetCurSel() == 5 || m_comboVideoType.GetCurSel() == 6)
		{
			m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel() + 4;
		}
		else
		{
            m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel();
		}
		
		m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byAudioEncType = (BYTE)m_comboAudioType.GetCurSel();		
		m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity = (BYTE)m_comboVideoEncComplexity.GetCurSel();
//		m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byEnableSvc = m_bChkEnableSvc;
        m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byEnableSvc = m_comSVC.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byAudioBitRate = (BYTE)m_comboAudioBitRate.GetCurSel();	
		m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byStreamSmooth = m_byStreamSmooth;	
		m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byAudioSamplingRate = (BYTE)m_comboSamplingRate.GetCurSel();
        m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.bySmartCodec = m_bChkSmartCodec;
        if (m_bDepthMapEnable)
        {
            m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byDepthMapEnable |= 0x01;
        }
        else
        {
            m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byDepthMapEnable &= 0xfe;
        }
        if (m_bYStreamEnable)
        {
            m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byDepthMapEnable |= 0x02;
        }
        else
        {
            m_struMSCompressionCfg[m_iCurChanIndex][TRANS_STREAM_COMPRESSION].struStreamPara.byDepthMapEnable &= 0xfd;
        }
		break;
	default:
        if (m_iCompressionTypeSel > TRANS_STREAM_COMPRESSION && m_iCompressionTypeSel < 11)
        {
            CheckRebootParam(&(m_struMSCompressionCfg[m_iCurChanIndex][m_iCompressionTypeSel].struStreamPara.byStreamType), \
                m_comboStreamType.GetCurSel(), FALSE);

            m_struMSCompressionCfg[m_iCurChanIndex][m_iCompressionTypeSel].struStreamPara.byPicQuality = (BYTE)m_comboImageQuality.GetCurSel();
            if (m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel()) == -1)	//adjust bit rate settings
            {
                dwDefBitRate = m_iBitRate * 1024;
                if (dwDefBitRate < 32 * 1024)
                {
                    dwDefBitRate = 32 * 1024;
                }
                //2010-6-9 删除下面对码率上限的限制
                // 			if (dwDefBitRate > 8192*1024)
                // 			{
                // 				dwDefBitRate =  8192*1024;
                // 			}
                dwDefBitRate |= 0x80000000;
                m_struMSCompressionCfg[m_iCurChanIndex][m_iCompressionTypeSel].struStreamPara.dwVideoBitrate = dwDefBitRate;
            }
            else
            {
                m_struMSCompressionCfg[m_iCurChanIndex][m_iCompressionTypeSel].struStreamPara.dwVideoBitrate = m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel());
            }
            // 		CheckRebootParam( &(m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byResolution),\
                                                // 			m_comboResolution.GetCurSel(), TRUE);
            m_struMSCompressionCfg[m_iCurChanIndex][m_iCompressionTypeSel].struStreamPara.byResolution = m_comboResolution.GetItemData(m_comboResolution.GetCurSel());
            //	m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byResolution = m_comboResolution.GetCurSel();
            m_struMSCompressionCfg[m_iCurChanIndex][m_iCompressionTypeSel].struStreamPara.dwVideoFrameRate = m_comboFrameRate.GetItemData(m_comboFrameRate.GetCurSel());
            m_struMSCompressionCfg[m_iCurChanIndex][m_iCompressionTypeSel].struStreamPara.byBitrateType = (BYTE)m_comboBitRateType.GetItemData(m_comboBitRateType.GetCurSel());
            m_struMSCompressionCfg[m_iCurChanIndex][m_iCompressionTypeSel].struStreamPara.byIntervalBPFrame = (BYTE)m_comboFrameBPInterval.GetCurSel();
            m_struMSCompressionCfg[m_iCurChanIndex][m_iCompressionTypeSel].struStreamPara.wIntervalFrameI = (WORD)m_iFrameIInterval;

            if (m_comboVideoType.GetCurSel() == 3 || m_comboVideoType.GetCurSel() == 4 || m_comboVideoType.GetCurSel() == 5 || m_comboVideoType.GetCurSel() == 6)
            {
                m_struMSCompressionCfg[m_iCurChanIndex][m_iCompressionTypeSel].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel() + 4;
            }
            else
            {
                m_struMSCompressionCfg[m_iCurChanIndex][m_iCompressionTypeSel].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel();
            }
            m_struMSCompressionCfg[m_iCurChanIndex][m_iCompressionTypeSel].struStreamPara.byAudioEncType = (BYTE)m_comboAudioType.GetCurSel();
            m_struMSCompressionCfg[m_iCurChanIndex][m_iCompressionTypeSel].struStreamPara.byVideoEncComplexity = (BYTE)m_comboVideoEncComplexity.GetCurSel();
            //		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byEnableSvc = m_bChkEnableSvc;
            m_struMSCompressionCfg[m_iCurChanIndex][m_iCompressionTypeSel].struStreamPara.byEnableSvc = m_comSVC.GetCurSel();
            m_struMSCompressionCfg[m_iCurChanIndex][m_iCompressionTypeSel].struStreamPara.byAudioBitRate = (BYTE)m_comboAudioBitRate.GetCurSel();
            m_struMSCompressionCfg[m_iCurChanIndex][m_iCompressionTypeSel].struStreamPara.byStreamSmooth = m_byStreamSmooth;
            m_struMSCompressionCfg[m_iCurChanIndex][m_iCompressionTypeSel].struStreamPara.byAudioSamplingRate = (BYTE)m_comboSamplingRate.GetCurSel();
            m_struMSCompressionCfg[m_iCurChanIndex][m_iCompressionTypeSel].struStreamPara.bySmartCodec = m_bChkSmartCodec;
            if (m_bDepthMapEnable)
            {
                m_struMSCompressionCfg[m_iCurChanIndex][m_iCompressionTypeSel].struStreamPara.byDepthMapEnable |= 0x01;
            }
            else
            {
                m_struMSCompressionCfg[m_iCurChanIndex][m_iCompressionTypeSel].struStreamPara.byDepthMapEnable &= 0xfe;
            }
            if (m_bYStreamEnable)
            {
                m_struMSCompressionCfg[m_iCurChanIndex][m_iCompressionTypeSel].struStreamPara.byDepthMapEnable |= 0x02;
            }
            else
            {
                m_struMSCompressionCfg[m_iCurChanIndex][m_iCompressionTypeSel].struStreamPara.byDepthMapEnable &= 0xfd;
            }

            if (m_comboAverageBitRate.GetItemData(m_comboAverageBitRate.GetCurSel()) == -1)	//adjust bit rate settings
            {
                dwDefBitRate = m_iAvBitRate/**1024*/;
                dwDefBitRate |= 0x8000;
                m_struMSCompressionCfg[m_iCurChanIndex][m_iCompressionTypeSel].struStreamPara.wAverageVideoBitrate = dwDefBitRate;
            }
            else
            {
                m_struMSCompressionCfg[m_iCurChanIndex][m_iCompressionTypeSel].struStreamPara.wAverageVideoBitrate = m_comboAverageBitRate.GetItemData(m_comboAverageBitRate.GetCurSel());
            }

        }
		break;
	}
}


/*********************************************************
  Function:	CheckRebootParam
  Desc:		detect parameter modification and judge if reboot is needed
  Input:	iCurVal,current value;iModVal,modified value;bJudge,judge device type or not，FALSE:need reboot for all the devices;
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::CheckRebootParam(BYTE *byCurVal, int iModVal, BOOL bJudge)
{
	if ((*byCurVal) != iModVal)
	{
		*byCurVal = (BYTE)iModVal;
		if (!bJudge && g_pMainDlg->IsNeedRebootDevType())
		{
			g_bMustReboot = TRUE;
		}
		else
		{
			g_bMustReboot = FALSE;
		}
	}
}

/*********************************************************
  Function:	OnCbnSelchangeComboMaxBitRate
  Desc:		select user-defined bit rate
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnCbnSelchangeComboMaxBitRate()
{
	UpdateData(TRUE);
//2010-6-9 需要根据能力获取结果的个数
	if (m_comboBitRate.GetCurSel() == m_comboBitRate.GetCount() - 1/*22*/)	//self-define bitrate
	{
		GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(FALSE);
	}
}

void CSubDlgChanCfg::OnCbnSelchangeComboAvcBitRate()
{
    UpdateData(TRUE);
    if (m_comboAverageBitRate.GetCurSel() == m_comboAverageBitRate.GetCount() - 1)
    {
        GetDlgItem(IDC_EDIT_AV_BIT_RATE)->EnableWindow(TRUE);
    }
    else
    {
        GetDlgItem(IDC_EDIT_AV_BIT_RATE)->EnableWindow(FALSE);
	} 
}

/*********************************************************
  Function:	EnableEventCtrl
  Desc:		enable  control or not, when the compression is event type
  Input:	bEnable, TRUE/FALSE
  Output:	none
  Return:	none
**********************************************************/
void CSubDlgChanCfg::EnableEventCtrl(BOOL bEnable)
{
	GetDlgItem(IDC_COMBO_STREAM_TYPE)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_RESOLUTION)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_FRAME_I_INTERVAL)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_FRAME_BP_INTERVAL)->EnableWindow(bEnable);
}
    
void CSubDlgChanCfg::GetResolutionAbility()
{
    for (int nAbilityCount = 0; nAbilityCount < m_pCompresscfgAbility->dwAbilityNum; nAbilityCount++)
    {
        if (MAIN_RESOLUTION_ABILITY == m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwAbilityType)
        {
            m_comboResolution.ResetContent();
            for (int i = 0; i < m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum; i++)
            {
                m_comboResolution.AddString((char*)m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_comboResolution.SetItemData(i, m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].iValue);
            }
        }
    }
}

void CSubDlgChanCfg::GetSubResolutionAbility()
{
    for (int nAbilityCount = 0; nAbilityCount < m_pCompresscfgAbility->dwAbilityNum; nAbilityCount++)
    {
        if (SUB_RESOLUTION_ABILITY == m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwAbilityType)
        {
            m_comboResolution.ResetContent();
            for (int i = 0; i < m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum; i++)
            {
                m_comboResolution.AddString((char*)m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_comboResolution.SetItemData(i, m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].iValue);
            }
        }
    }
}

void CSubDlgChanCfg::GetEventResolutionAbility()
{
    for (int nAbilityCount = 0; nAbilityCount < m_pCompresscfgAbility->dwAbilityNum; nAbilityCount++)
    {
        if (EVENT_RESOLUTION_ABILITY == m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwAbilityType)
        {
            m_comboResolution.ResetContent();
            for (int i = 0; i < m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum; i++)
            {
                m_comboResolution.AddString((char*)m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_comboResolution.SetItemData(i, m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].iValue);
            }
        }
    }
}


void CSubDlgChanCfg::GetThirdResolutionAbility()
{
    for (int nAbilityCount = 0; nAbilityCount < m_pCompresscfgAbility->dwAbilityNum; nAbilityCount++)
    {
        if (THIRD_RESOLUTION_ABILITY == m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwAbilityType)
        {
            m_comboResolution.ResetContent();
            for (int i = 0; i < m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum; i++)
            {
                m_comboResolution.AddString((char*)m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_comboResolution.SetItemData(i, m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].iValue);
            }
        }
    }
}


void CSubDlgChanCfg::GetTranscodeResolutionAbility()
{
	int i = 0;
//     for (int nAbilityCount = 0; nAbilityCount < m_pCompresscfgAbility->dwAbilityNum; nAbilityCount++)
//     {
//         if (MAIN_RESOLUTION_ABILITY == m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwAbilityType)
//         {
//             m_comboResolution.ResetContent();
//             for (i = 0; i < m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum; i++)
//             {
//                 m_comboResolution.AddString((char*)m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
//                 m_comboResolution.SetItemData(i, m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].iValue);
//             }
//         }
//     }

	//转码码流写死1-CIF(352*288/352*240)，2-QCIF(176*144/176*120)，3-4CIF(704*576/704*480)或D1(720*576/720*486)， 0xff-auto
	m_comboResolution.ResetContent();

	m_comboResolution.AddString("QCIF");
	m_comboResolution.SetItemData(0, 2);

	m_comboResolution.AddString("CIF");
	m_comboResolution.SetItemData(1, 1);

	m_comboResolution.AddString("4CIF");
	m_comboResolution.SetItemData(2, 3);

	m_comboResolution.AddString("Auto");
	m_comboResolution.SetItemData(3, 0xff);
}

void CSubDlgChanCfg::GetBitrateTypeAbility()
{
    for (int nAbilityCount = 0; nAbilityCount < m_pCompresscfgAbility->dwAbilityNum; nAbilityCount++)
    {
        if (BITRATE_TYPE_ABILITY == m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwAbilityType)
        {
            m_comboBitRateType.ResetContent();
            for (int i = 0; i < m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum; i++)
            {
                m_comboBitRateType.AddString((char*)m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_comboBitRateType.SetItemData(i, m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].iValue);
            }
        }
    }
}

void CSubDlgChanCfg::GetBitrateAbility()
{
    for (int nAbilityCount = 0; nAbilityCount < m_pCompresscfgAbility->dwAbilityNum; nAbilityCount++)
    {
        if (BITRATE_ABILITY == m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwAbilityType)
        {
            m_comboBitRate.ResetContent();
            m_comboAverageBitRate.ResetContent();
            for (int i = 0; i < m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum; i++)
            {
                m_comboBitRate.AddString((char*)m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_comboBitRate.SetItemData(i, m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].iValue);

                m_comboAverageBitRate.AddString((char*)m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_comboAverageBitRate.SetItemData(i, m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].iValue);
            }
        }
    }
}

void CSubDlgChanCfg::GetFrameAbility()
{
    for (int nAbilityCount = 0; nAbilityCount < m_pCompresscfgAbility->dwAbilityNum; nAbilityCount++)
    {
        if (FRAME_ABILITY == m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwAbilityType)
        {
            m_comboFrameRate.ResetContent();
            for (int i = 0; i < m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum; i++)
            {
                m_comboFrameRate.AddString((char*)m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_comboFrameRate.SetItemData(i, m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].iValue);
            }
        }
    }
}

BOOL CSubDlgChanCfg::GetCompressCfgAbility(DWORD dwIPChanIndex)
{
    if (!NET_DVR_GetDeviceAbility(m_lLoginID, COMPRESSIONCFG_ABILITY, (char*)&dwIPChanIndex, sizeof(dwIPChanIndex), (char*)m_pCompresscfgAbility, sizeof(NET_DVR_COMPRESSIONCFG_ABILITY)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "COMPRESSIONCFG_ABILITY");
        return FALSE;    
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "COMPRESSIONCFG_ABILITY");
        return TRUE;
    }
}

void CSubDlgChanCfg::GetStreamTypeAbility()
{
    for (int nAbilityCount = 0; nAbilityCount < m_pCompresscfgAbility->dwAbilityNum; nAbilityCount++)
    {
        if (COMPRESSION_STREAM_ABILITY == m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwAbilityType)
        {
            m_comboCompressionType.ResetContent();
            for (int i = 0; i < m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum; i++)
            {
                m_comboCompressionType.AddString((char*)m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_comboCompressionType.SetItemData(i, m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].iValue);
            }
        }
    }
}


void CSubDlgChanCfg::SetResolutionCurSel(DWORD dwData)
{
    for (int i = 0; i < m_comboResolution.GetCount(); i++)
    {
        if (m_comboResolution.GetItemData(i) == dwData)
        {
            m_comboResolution.SetCurSel(i);
            return;
        }
    }
}

void CSubDlgChanCfg::SetBitrateCurSel(DWORD dwData)
{
    for (int i = 0; i < m_comboBitRate.GetCount(); i++)
    {
        if (m_comboBitRate.GetItemData(i) == dwData)
        {
            m_comboBitRate.SetCurSel(i);
            return;
        }
    }
}

void CSubDlgChanCfg::SetAvBitrateCurSel(DWORD dwData)
{
    for (int i = 0; i < m_comboAverageBitRate.GetCount(); i++)
    {
        if (m_comboAverageBitRate.GetItemData(i) == dwData)
        {
            m_comboAverageBitRate.SetCurSel(i);
            return;
        }
    }
}
void CSubDlgChanCfg::SetBitrateTypeCurSel(DWORD dwData)
{
    for (int i = 0; i < m_comboBitRateType.GetCount(); i++)
    {
        if (m_comboBitRateType.GetItemData(i) == dwData)
        {
            m_comboBitRateType.SetCurSel(i);
            return;
        }
    }
}

BOOL CSubDlgChanCfg::SetFrameCurSel(DWORD dwData)
{
    for (int i = 0; i < m_comboFrameRate.GetCount(); i++)
    {
        if (m_comboFrameRate.GetItemData(i) == dwData)
        {
            m_comboFrameRate.SetCurSel(i);
            return TRUE;
        }
    }
	return FALSE;
}

void CSubDlgChanCfg::SetStreamTypeCurSel(DWORD dwData)
{
    for (int i = 0; i < m_comboCompressionType.GetCount(); i++)
    {
        if (m_comboCompressionType.GetItemData(i) == dwData)
        {
            m_comboCompressionType.SetCurSel(i);
            return;
        }
    }
}

void CSubDlgChanCfg::OnBtnJpegCapture() 
{
	CDlgJpegCaptureCfg dlg;
    dlg.m_lUserID = m_lLoginID;
    dlg.m_lChannelNum = m_iChanCount;
	dlg.m_iChanShowNO = m_iChanShowNum;
    dlg.m_lChannel = m_iChanShowNum;
	dlg.m_iChanCount = m_iChanCount;
	dlg.m_dwDevIndex = m_iDeviceIndex;
    dlg.DoModal();
    
}

void CSubDlgChanCfg::OnBtnDiskQuota() 
{
    CDlgDiskQuota dlg;
    dlg.m_lServerID = m_lLoginID;
    dlg.m_iDevIndex = m_iDeviceIndex;
    dlg.m_lChannelNum = m_iChanCount;
    dlg. m_lChannel = m_iChanShowNum;
    dlg.DoModal();
    
}

void CSubDlgChanCfg::DoUpdateFrame()
{
	char szLan[128] = {0};
	BOOL bGetFirstFrame = FALSE;
	int iFirstFrame = 0;
	NET_DVR_COMPRESSION_LIMIT struCompressionLimit = {0};
	struCompressionLimit.dwSize = sizeof(struCompressionLimit);
	struCompressionLimit.dwChannel = m_iChanShowNum;
	struCompressionLimit.byCompressType = m_comboCompressionType.GetCurSel();

	//第三,四码流，不发送压缩限制命令
	if (struCompressionLimit.byCompressType == THIRD_STREAM_COMPRESSION || struCompressionLimit.byCompressType == TRANS_STREAM_COMPRESSION)
	{
		return;
	}
	//Only if the channel is IPC, COMPRESSION_LIMIT is usable.
	if (m_iChanShowNum > MAX_ANALOG_CHANNUM)
	{
		return;
	}

//	memcpy(&(struCompressionLimit.struCurrentCfg), &(m_struCompressionCfg[m_iCurChanIndex]), sizeof(NET_DVR_COMPRESSIONCFG_V30));
	NET_DVR_COMPRESSIONCFG_ABILITY struCompresscfgAbility = {0};
	if(!NET_DVR_GetDeviceAbility(m_lLoginID, COMPRESSION_LIMIT, (char*)&struCompressionLimit, sizeof(struCompressionLimit), (char*)(&struCompresscfgAbility), sizeof(struCompresscfgAbility)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "COMPRESSION_LIMIT");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "COMPRESSION_LIMIT");
		
		//update the framerate ability
		
		for (int nAbilityCount = 0; nAbilityCount < struCompresscfgAbility.dwAbilityNum; nAbilityCount++)
		{
			if (FRAME_ABILITY == struCompresscfgAbility.struAbilityNode[nAbilityCount].dwAbilityType)
			{
				m_comboFrameRate.ResetContent();
				for (int i = 0; i < struCompresscfgAbility.struAbilityNode[nAbilityCount].dwNodeNum; i++)
				{
					if (!bGetFirstFrame)
					{
						bGetFirstFrame = TRUE;
						iFirstFrame = struCompresscfgAbility.struAbilityNode[nAbilityCount].struDescNode[i].iValue;
					}
					m_comboFrameRate.AddString((char*)struCompresscfgAbility.struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
					m_comboFrameRate.SetItemData(i, struCompresscfgAbility.struAbilityNode[nAbilityCount].struDescNode[i].iValue);
				}
			}
		}
		SetFrameCurSel(iFirstFrame);
	}	
	UpdateData(FALSE);
}

void CSubDlgChanCfg::OnButtonLimitFrameUpdate() 
{
	OnBnClickedBtnCmpOk();
	DoUpdateFrame();
}

void CSubDlgChanCfg::OnButtonVideoInEffect() 
{
	CDlgRemoteVideoInput dlg;
    dlg.m_lUserID = m_lLoginID;
    dlg.m_dwDevIndex = m_iDeviceIndex;
    dlg. m_lChannel = m_iChanShowNum;
    if (dlg.DoModal() == IDOK)
    {
         CheckInitParam();
    }
     
   
}

void CSubDlgChanCfg::OnButtonConfigCameraType() 
{
	// TODO: Add your control notification handler code here
	CDlgAccessCameraCfg dlg;
    dlg.m_lUserID = m_lLoginID;
    dlg.m_dwDevIndex = m_iDeviceIndex;
    dlg.m_lChannel = m_iChanShowNum;
    dlg.DoModal();
}

void CSubDlgChanCfg::OnButtonInquiryTimeSpan() 
{
	CDialogRecordTimeSpan dlg;
    dlg.m_lServerID = m_lLoginID;
    dlg.m_iDevIndex = m_iDeviceIndex;
    dlg. m_lChannel = m_iChanShowNum;
    dlg.DoModal();	
}

void CSubDlgChanCfg::OnButtonUpdateIndex() 
{
	if(NET_DVR_UpdateRecordIndex(m_lLoginID, m_iChanShowNum))
	{
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UpdateRecordIndex");
		AfxMessageBox("NET_DVR_UpdateRecordIndex succeed");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UpdateRecordIndex");
		CString cs;
		cs.Format("NET_DVR_UpdateRecordIndex failed!Error[%d]", NET_DVR_GetLastError());
		AfxMessageBox(cs);
	}	
}

void CSubDlgChanCfg::OnBtnVideoOutput() 
{
	// TODO: Add your control notification handler code here
	CDlgVideoOut dlg;
	dlg.DoModal();
}
void CSubDlgChanCfg::OnBtnWdEnable() 
{
	// TODO: Add your control notification handler code here
	
	CDlgWD1Enable dlg;
	dlg.m_lServerID = m_lLoginID;
    dlg.m_iDevIndex = m_iDeviceIndex;
    dlg. m_lChannel = m_iChanShowNum;
    dlg.DoModal();
	
}

void CSubDlgChanCfg::OnBtnVeidopackage() 
{
	// TODO: Add your control notification handler code here
	CDlgNetraRecordPackage  dlg ;
	dlg.m_lLoginID = m_lLoginID;
	dlg.m_lChannel = m_iChanShowNum;
	dlg.m_iDevIndex = m_iDeviceIndex ;
	dlg.DoModal();

	
}

void CSubDlgChanCfg::OnBtnVediopackage() 
{
	// TODO: Add your control notification handler code here
	CDlgNetraRecordPackage  dlg ;
	dlg.m_lLoginID = m_lLoginID;
	dlg.m_lChannel = m_iChanShowNum;
	dlg.m_iDevIndex = m_iDeviceIndex ;
	dlg.DoModal();

}

void CSubDlgChanCfg::OnBtnDeviceLanguageEncode() 
{
	// TODO: Add your control notification handler code here
	CDlgDeviceLanguageEncode  dlg ;
	dlg.m_lLoginID = m_lLoginID;
	dlg.m_lChannel = m_iChanShowNum;
	dlg.m_iDeviceIndex = m_iDeviceIndex ;
	dlg.DoModal();
}

void CSubDlgChanCfg::OnChkOSDColor() 
{
	UpdateData(TRUE);

	GetDlgItem(IDC_EDIT_OSD_COLOR_R)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_OSD_COLOR_G)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_OSD_COLOR_B)->EnableWindow(FALSE);
	
	if (m_bOSDColor)
	{
		GetDlgItem(IDC_EDIT_OSD_COLOR_R)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_OSD_COLOR_G)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_OSD_COLOR_B)->EnableWindow(TRUE);
	}

}

void CSubDlgChanCfg::AddStreamType()
{
    char szLan[128] = { 0 };
    int index = 0;

    m_comboCompressionType.ResetContent();
    g_StringLanType(szLan, "主码流", "MainCode");
    m_comboCompressionType.AddString(szLan);
    m_comboCompressionType.SetItemData(index, 0);
    index++;

    g_StringLanType(szLan, "子码流", "SubCode");
    m_comboCompressionType.AddString(szLan);
    m_comboCompressionType.SetItemData(index, 1);
    index++;

    g_StringLanType(szLan, "事件码流", "EventCode");
    m_comboCompressionType.AddString(szLan);
    m_comboCompressionType.SetItemData(index, 2);
    index++;

    g_StringLanType(szLan, "码流3", "ThirdCode");
    m_comboCompressionType.AddString(szLan);
    m_comboCompressionType.SetItemData(index, 3);
    index++;

    g_StringLanType(szLan, "码流4", "TransCode");
    m_comboCompressionType.AddString(szLan);
    m_comboCompressionType.SetItemData(index, 4);
    index++;

    g_StringLanType(szLan, "码流5", "FifthCode");
    m_comboCompressionType.AddString(szLan);
    m_comboCompressionType.SetItemData(index, 5);
    index++;

    g_StringLanType(szLan, "码流6(自定义)", "SixthCode(Custom)");
    m_comboCompressionType.AddString(szLan);
    m_comboCompressionType.SetItemData(index, 6);
    index++;

    g_StringLanType(szLan, "码流7(自定义)", "SeventhCode(Custom)");
    m_comboCompressionType.AddString(szLan);
    m_comboCompressionType.SetItemData(index, 7);
    index++;

    g_StringLanType(szLan, "码流8(自定义)", "EighthCode(Custom)");
    m_comboCompressionType.AddString(szLan);
    m_comboCompressionType.SetItemData(index, 8);
    index++;

    g_StringLanType(szLan, "码流9(自定义)", "NinthCode(Custom)");
    m_comboCompressionType.AddString(szLan);
    m_comboCompressionType.SetItemData(index, 9);
    index++;

    g_StringLanType(szLan, "码流10(自定义)", "TenthCode(Custom)");
    m_comboCompressionType.AddString(szLan);
    m_comboCompressionType.SetItemData(index, 10);
    index++;
}

void CSubDlgChanCfg::AddResolution()
{
	
	int index = 0;
	m_comboResolution.InsertString(index, "DCIF");
	m_comboResolution.SetItemData(index, 0);
	index++;
	
	m_comboResolution.InsertString(index, "CIF");
	m_comboResolution.SetItemData(index, 1);
	index++;
	
	m_comboResolution.InsertString(index, "QCIF");
	m_comboResolution.SetItemData(index, 2);
	index++;
	
	m_comboResolution.InsertString(index, "4CIF");
	m_comboResolution.SetItemData(index, 3);
	index++;
	
	m_comboResolution.InsertString(index, "2CIF");
	m_comboResolution.SetItemData(index, 4);
	index++;
	
	m_comboResolution.InsertString(index, "reserve");
	m_comboResolution.SetItemData(index, 5);
	index++;
	
	m_comboResolution.InsertString(index, "QVGA(320*240)");
	m_comboResolution.SetItemData(index, 6);
	index++;
	
	m_comboResolution.InsertString(index, "QQVGA(160*120)");
	m_comboResolution.SetItemData(index, 7);
	index++;
	
	m_comboResolution.InsertString(index, "384*288");
	m_comboResolution.SetItemData(index, 12);
	index++;
	m_comboResolution.InsertString(index, "576*576");
	m_comboResolution.SetItemData(index, 13);
	index++;
	
	m_comboResolution.InsertString(index, "VGA(640*480)");
	m_comboResolution.SetItemData(index, 16);
	index++;	
	
	m_comboResolution.InsertString(index, "UXGA (1600*1200)");
	m_comboResolution.SetItemData(index, 17);
	index++;
	
	m_comboResolution.InsertString(index, "SVGA(800*600)");
	m_comboResolution.SetItemData(index, 18);
	index++;
	m_comboResolution.InsertString(index, "HD720p(1280*720)");
	m_comboResolution.SetItemData(index, 19);
	index++;
	
	m_comboResolution.InsertString(index, "XVGA");
	m_comboResolution.SetItemData(index, 20);
	index++;

	m_comboResolution.InsertString(index, "HD900p");
	m_comboResolution.SetItemData(index, 21);
	index++;
	m_comboResolution.InsertString(index, "1536*1536");
	m_comboResolution.SetItemData(index, 23);
	index++;
	
	m_comboResolution.InsertString(index, "1920*1920");
	m_comboResolution.SetItemData(index, 24);
	index++;	
	
	m_comboResolution.InsertString(index, "HD1080i");
	m_comboResolution.SetItemData(index, 27);
	index++;
	
	m_comboResolution.InsertString(index, "2560*1920");
	m_comboResolution.SetItemData(index, 28);
	index++;
	m_comboResolution.InsertString(index, "1600*304");
	m_comboResolution.SetItemData(index, 29);
	index++;
	
	m_comboResolution.InsertString(index, "2048*1536");
	m_comboResolution.SetItemData(index, 30);
	index++;

	m_comboResolution.InsertString(index, "2448*2048");
	m_comboResolution.SetItemData(index, 31);
	index++;
	m_comboResolution.InsertString(index, "2448*1200");
	m_comboResolution.SetItemData(index, 32);
	index++;
	
	m_comboResolution.InsertString(index, "2448*800");
	m_comboResolution.SetItemData(index, 33);
	index++;	
	
	m_comboResolution.InsertString(index, "XGA(1024*768)");
	m_comboResolution.SetItemData(index, 34);
	index++;
	
	m_comboResolution.InsertString(index, "SXGA（1280*1024）");
	m_comboResolution.SetItemData(index, 35);
	index++;
	m_comboResolution.InsertString(index, "WD1(960*576/960*480)");
	m_comboResolution.SetItemData(index, 36);
	index++;
	
	m_comboResolution.InsertString(index, "1080i");
	m_comboResolution.SetItemData(index, 37);
	index++;

	m_comboResolution.InsertString(index, "WSXGA(1440*900)");
	m_comboResolution.SetItemData(index, 38);
	index++;	
	
	m_comboResolution.InsertString(index, "HD_F(1920*1080/1280*720)");
	m_comboResolution.SetItemData(index, 39);
	index++;
	
	m_comboResolution.InsertString(index, "HD_H(1920*540/1280*360)");
	m_comboResolution.SetItemData(index, 40);
	index++;
	m_comboResolution.InsertString(index, "HD_Q(960*540/630*360)");
	m_comboResolution.SetItemData(index, 41);
	index++;
	
	m_comboResolution.InsertString(index, "2336*1744");
	m_comboResolution.SetItemData(index, 42);
	index++;

	m_comboResolution.InsertString(index, "1920*1456");
	m_comboResolution.SetItemData(index, 43);
	index++;	
	m_comboResolution.InsertString(index, "2592*2048");
	m_comboResolution.SetItemData(index, 44);
	index++;	
	m_comboResolution.InsertString(index, "3296*2472");
	m_comboResolution.SetItemData(index, 45);
	index++;	
	m_comboResolution.InsertString(index, "1376*768");
	m_comboResolution.SetItemData(index, 46);
	index++;	
	m_comboResolution.InsertString(index, "1366*768");
	m_comboResolution.SetItemData(index, 47);
	index++;	
	m_comboResolution.InsertString(index, "1360*768");
	m_comboResolution.SetItemData(index, 48);
	index++;	
	m_comboResolution.InsertString(index, "WSXGA+");
	m_comboResolution.SetItemData(index, 49);
	index++;	
	m_comboResolution.InsertString(index, "720*720");
	m_comboResolution.SetItemData(index, 50);
	index++;	

	m_comboResolution.InsertString(index, "1280*1280");
	m_comboResolution.SetItemData(index, 51);
	index++;	

	m_comboResolution.InsertString(index, "2048*768");
	m_comboResolution.SetItemData(index, 52);
	index++;

	m_comboResolution.InsertString(index, "2048*2048");
	m_comboResolution.SetItemData(index, 53);
	index++;

	m_comboResolution.InsertString(index, "2560*2048");
	m_comboResolution.SetItemData(index, 54);
	index++;

	m_comboResolution.InsertString(index, "3072*2048");
	m_comboResolution.SetItemData(index, 55);
	index++;

	m_comboResolution.InsertString(index, "2304*1296");
	m_comboResolution.SetItemData(index, 56);
	index++;

	m_comboResolution.InsertString(index, "WXGA(1280*800)");
	m_comboResolution.SetItemData(index, 57);
	index++;

	m_comboResolution.InsertString(index, "1600*600");
	m_comboResolution.SetItemData(index, 58);
	index++;

	m_comboResolution.InsertString(index, "1600*9000");
	m_comboResolution.SetItemData(index, 59);
	index++;

	m_comboResolution.InsertString(index, "2752*2208");
	m_comboResolution.SetItemData(index, 60);
	index++;
 
	m_comboResolution.InsertString(index, "384*288");
	m_comboResolution.SetItemData(index, 61);
	index++;
	
	m_comboResolution.InsertString(index, "4000*3000");
	m_comboResolution.SetItemData(index, 62);
	index++;
	
	m_comboResolution.InsertString(index, "4096*2160");
	m_comboResolution.SetItemData(index, 63);
	index++;
	
	m_comboResolution.InsertString(index, "3840*2160");
	m_comboResolution.SetItemData(index, 64);
	index++;
	
	m_comboResolution.InsertString(index, "4000*2250");
	m_comboResolution.SetItemData(index, 65);
	index++;
	
	m_comboResolution.InsertString(index, "3072*1728");
	m_comboResolution.SetItemData(index, 66);
	index++;

	m_comboResolution.InsertString(index, "2592*1944");
	m_comboResolution.SetItemData(index, 67);
	index++;
	
	m_comboResolution.InsertString(index, "2464*1520");
	m_comboResolution.SetItemData(index, 68);
	index++;
	
	m_comboResolution.InsertString(index, "1280*1920");
	m_comboResolution.SetItemData(index, 69);
	index++;
	
	m_comboResolution.InsertString(index, "2560*1440");
	m_comboResolution.SetItemData(index, 70);
	index++;

    m_comboResolution.InsertString(index, "1024*1024");
    m_comboResolution.SetItemData(index, 71);
	index++;

    m_comboResolution.InsertString(index, "160*128");
    m_comboResolution.SetItemData(index, 72);
    index++;
    
    m_comboResolution.InsertString(index, "324*240");
    m_comboResolution.SetItemData(index, 73);
    index++;
    
    m_comboResolution.InsertString(index, "324*256");
    m_comboResolution.SetItemData(index, 74);
    index++;
    
    m_comboResolution.InsertString(index, "336*256");
    m_comboResolution.SetItemData(index, 75);
    index++;
    
    m_comboResolution.InsertString(index, "640*512");
    m_comboResolution.SetItemData(index, 76);
	index++;

	m_comboResolution.InsertString(index, "2720*2048");
    m_comboResolution.SetItemData(index, 77);
	index++;
	
	m_comboResolution.InsertString(index, "384*256");
    m_comboResolution.SetItemData(index, 78);
	index++;
	
	m_comboResolution.InsertString(index, "384*216");
    m_comboResolution.SetItemData(index, 79);
	index++;

	m_comboResolution.InsertString(index, "320*256");
    m_comboResolution.SetItemData(index, 80);
	index++;

	m_comboResolution.InsertString(index, "320*180");
    m_comboResolution.SetItemData(index, 81);
	index++;

	m_comboResolution.InsertString(index, "320*192");
    m_comboResolution.SetItemData(index, 82);
	index++;

	m_comboResolution.InsertString(index, "512*384");
    m_comboResolution.SetItemData(index, 83);
	index++;

	m_comboResolution.InsertString(index, "325*256");
    m_comboResolution.SetItemData(index, 84);
	index++;

	m_comboResolution.InsertString(index, "256*192");
    m_comboResolution.SetItemData(index, 85);
	index++;

	m_comboResolution.InsertString(index, "640*360");
    m_comboResolution.SetItemData(index, 86);
	index++;

    m_comboResolution.InsertString(index, "1776x1340");
    m_comboResolution.SetItemData(index, 87);
	index++;

    m_comboResolution.InsertString(index, "1936x1092");
    m_comboResolution.SetItemData(index, 88);
	index++;
    
    m_comboResolution.InsertString(index, "2080x784");
    m_comboResolution.SetItemData(index, 89);
	index++;

    m_comboResolution.InsertString(index, "2144x604");
    m_comboResolution.SetItemData(index, 90);
	index++;
    
    m_comboResolution.InsertString(index, "1920*1200");
    m_comboResolution.SetItemData(index, 91);
	index++;

    m_comboResolution.InsertString(index, "4064*3040");
    m_comboResolution.SetItemData(index, 92);
    index++;
    
    m_comboResolution.InsertString(index, "3040*3040");
    m_comboResolution.SetItemData(index, 93);
	index++;

    m_comboResolution.InsertString(index, "3072*2304");
    m_comboResolution.SetItemData(index, 94);
    index++;
    
    m_comboResolution.InsertString(index, "3072*1152");
    m_comboResolution.SetItemData(index, 95);
	index++;

    m_comboResolution.InsertString(index, "2560*2560");
    m_comboResolution.SetItemData(index, 96);
    index++;
    
    m_comboResolution.InsertString(index, "2688*1536");
    m_comboResolution.SetItemData(index, 97);
	index++;

    m_comboResolution.InsertString(index, "2688*1520");
    m_comboResolution.SetItemData(index, 98);
    index++;
    
    m_comboResolution.InsertString(index, "3072*3072");
    m_comboResolution.SetItemData(index, 99);
	index++;

    m_comboResolution.InsertString(index, "3392*2008");
    m_comboResolution.SetItemData(index,100);
    index++;
    
    m_comboResolution.InsertString(index, "4000*3080");
    m_comboResolution.SetItemData(index, 101);
    index++;
    
    m_comboResolution.InsertString(index, "960*720");
    m_comboResolution.SetItemData(index, 102);
    index++;
    
    m_comboResolution.InsertString(index, "1024*1536");
    m_comboResolution.SetItemData(index, 103);
    index++;
    
    m_comboResolution.InsertString(index, "704*1056");
    m_comboResolution.SetItemData(index, 104);
    index++;
    
    m_comboResolution.InsertString(index, "352*528");
    m_comboResolution.SetItemData(index, 105);
    index++;
    
    m_comboResolution.InsertString(index, "2048*1530");
    m_comboResolution.SetItemData(index, 106);
    index++;
    
    m_comboResolution.InsertString(index, "2560*1600");
    m_comboResolution.SetItemData(index, 107);
    index++;
    
    m_comboResolution.InsertString(index, "2800*2100");
    m_comboResolution.SetItemData(index, 108);
    index++;
    
    m_comboResolution.InsertString(index, "4088*4088");
    m_comboResolution.SetItemData(index, 109);
    index++;
    
    m_comboResolution.InsertString(index, "4000*3072");
    m_comboResolution.SetItemData(index, 110);
    index++;

    m_comboResolution.InsertString(index, "960*1080(half 1080p)");
    m_comboResolution.SetItemData(index, 111);
    index++;

    m_comboResolution.InsertString(index, "640*720(half 720p)");
    m_comboResolution.SetItemData(index, 112);
    index++;

	m_comboResolution.InsertString(index, "640*960");
	m_comboResolution.SetItemData(index, 113);
	index++;

	m_comboResolution.InsertString(index, "320*480");
	m_comboResolution.SetItemData(index, 114);
	index++;

	m_comboResolution.InsertString(index, "3840*2400");
	m_comboResolution.SetItemData(index, 115);
	index++;

	m_comboResolution.InsertString(index, "3840*1680");
	m_comboResolution.SetItemData(index, 116);
	index++;
	m_comboResolution.InsertString(index, "2560*1120");
	m_comboResolution.SetItemData(index, 117);
	index++;

	m_comboResolution.InsertString(index, "704*320");
	m_comboResolution.SetItemData(index, 118);
	index++;

	m_comboResolution.InsertString(index, "1200*1920");
	m_comboResolution.SetItemData(index, 119);
	index++;

	m_comboResolution.InsertString(index, "480*768");
	m_comboResolution.SetItemData(index, 120);
	index++;
	m_comboResolution.InsertString(index, "768*480");
	m_comboResolution.SetItemData(index, 121);
	index++;

	m_comboResolution.InsertString(index, "320*512");
	m_comboResolution.SetItemData(index, 122);
	index++;

	m_comboResolution.InsertString(index, "512*320");
	m_comboResolution.SetItemData(index, 123);
	index++;

	m_comboResolution.InsertString(index, "4096*1800");
	m_comboResolution.SetItemData(index, 124);
	index++;

	m_comboResolution.InsertString(index, "1280*560");
	m_comboResolution.SetItemData(index, 125);
	index++;
	m_comboResolution.InsertString(index, "2400*3840");
	m_comboResolution.SetItemData(index, 126);
	index++;

	m_comboResolution.InsertString(index, "480*272");
	m_comboResolution.SetItemData(index, 127);
	index++;

	m_comboResolution.InsertString(index, "512*272");
	m_comboResolution.SetItemData(index, 128);
	index++;

	m_comboResolution.InsertString(index, "2592*2592");
	m_comboResolution.SetItemData(index, 129);
	index++;

    m_comboResolution.InsertString(index, "1792*2880");
    m_comboResolution.SetItemData(index, 130);
    index++;

    m_comboResolution.InsertString(index, "1600*2560");
    m_comboResolution.SetItemData(index, 131);
    index++;

    m_comboResolution.InsertString(index, "2720*1192");
    m_comboResolution.SetItemData(index, 132);
    index++;

    m_comboResolution.InsertString(index, "2560*960");
    m_comboResolution.SetItemData(index, 135);
    index++;

    m_comboResolution.InsertString(index, "2064*1544");
    m_comboResolution.SetItemData(index, 136);
    index++;

    m_comboResolution.InsertString(index, "4096*1200");
    m_comboResolution.SetItemData(index, 137);
    index++;

    m_comboResolution.InsertString(index, "3840*1080");
    m_comboResolution.SetItemData(index, 138);
    index++;

    m_comboResolution.InsertString(index, "2720*800");
    m_comboResolution.SetItemData(index, 139);
    index++;

    m_comboResolution.InsertString(index, "512*232");
    m_comboResolution.SetItemData(index, 140);
    index++;

    m_comboResolution.InsertString(index, "704*200");
    m_comboResolution.SetItemData(index, 141);
    index++;

    m_comboResolution.InsertString(index, "512*152");
    m_comboResolution.SetItemData(index, 142);
    index++;

    m_comboResolution.InsertString(index, "2048*896");
    m_comboResolution.SetItemData(index, 143);
    index++;

    m_comboResolution.InsertString(index, "2048*600");
    m_comboResolution.SetItemData(index, 144);
    index++;

    m_comboResolution.InsertString(index, "1280*376");
    m_comboResolution.SetItemData(index, 145);
    index++;

    m_comboResolution.InsertString(index, "2592*1520");
    m_comboResolution.SetItemData(index, 146);
    index++;

    m_comboResolution.InsertString(index, "2592*1536");
    m_comboResolution.SetItemData(index, 147);
    index++;

    m_comboResolution.InsertString(index, "3072*8192");
    m_comboResolution.SetItemData(index, 148);
    index++;

    m_comboResolution.InsertString(index, "768*2048");
    m_comboResolution.SetItemData(index, 149);
    index++;

    m_comboResolution.InsertString(index, "8208*3072");
    m_comboResolution.SetItemData(index, 150);
    index++;

    m_comboResolution.InsertString(index, "4096*1536");
    m_comboResolution.SetItemData(index, 151);
    index++;

    m_comboResolution.InsertString(index, "6912*2800");
    m_comboResolution.SetItemData(index, 152);
    index++;

    m_comboResolution.InsertString(index, "3456*1400");
    m_comboResolution.SetItemData(index, 153);
    index++;

    m_comboResolution.InsertString(index, "480*720");
    m_comboResolution.SetItemData(index, 154);
    index++;

    m_comboResolution.InsertString(index, "800*450");
    m_comboResolution.SetItemData(index, 155);
    index++;

    m_comboResolution.InsertString(index, "480*270");
    m_comboResolution.SetItemData(index, 156);
    index++;

    m_comboResolution.InsertString(index, "2560*1536");
    m_comboResolution.SetItemData(index, 157);
    index++;

    m_comboResolution.InsertString(index, "1456*1456");
    m_comboResolution.SetItemData(index, 158);
    index++;

    m_comboResolution.InsertString(index, "3026*3026");
    m_comboResolution.SetItemData(index, 159);
    index++;

    m_comboResolution.InsertString(index, "3264*2448");
    m_comboResolution.SetItemData(index, 160);
    index++;

    m_comboResolution.InsertString(index, "288*320");
    m_comboResolution.SetItemData(index, 161);
    index++;

    m_comboResolution.InsertString(index, "144*176");
    m_comboResolution.SetItemData(index, 162);
    index++;

    m_comboResolution.InsertString(index, "480*640");
    m_comboResolution.SetItemData(index, 163);
    index++;

    m_comboResolution.InsertString(index, "240*320");
    m_comboResolution.SetItemData(index, 164);
    index++;

    m_comboResolution.InsertString(index, "120*160");
    m_comboResolution.SetItemData(index, 165);
    index++;

    m_comboResolution.InsertString(index, "576*720");
    m_comboResolution.SetItemData(index, 166);
    index++;

    m_comboResolution.InsertString(index, "720*1280");
    m_comboResolution.SetItemData(index, 167);
    index++;

    m_comboResolution.InsertString(index, "576*960");
    m_comboResolution.SetItemData(index, 168);
    index++;
    
    m_comboResolution.InsertString(index, "2944*1656");
    m_comboResolution.SetItemData(index, 169);
    index++;

    m_comboResolution.InsertString(index, "432*240");
    m_comboResolution.SetItemData(index, 170);
    index++;

    m_comboResolution.InsertString(index, "2160*3840");
    m_comboResolution.SetItemData(index, 171);
    index++;

    m_comboResolution.InsertString(index, "1080*1920");
    m_comboResolution.SetItemData(index, 172);
    index++;

    m_comboResolution.InsertString(index, "7008*1080");
    m_comboResolution.SetItemData(index, 173);
    index++;

    m_comboResolution.InsertString(index, "3504*540");
    m_comboResolution.SetItemData(index, 174);
    index++;

    m_comboResolution.InsertString(index, "1752*270");
    m_comboResolution.SetItemData(index, 175);
    index++;

    m_comboResolution.InsertString(index, "876*135");
    m_comboResolution.SetItemData(index, 176);
    index++;

    m_comboResolution.InsertString(index, "4096*1440");
    m_comboResolution.SetItemData(index, 177);
    index++;

    m_comboResolution.InsertString(index, "4096*1080");
    m_comboResolution.SetItemData(index, 178);
    index++;

    m_comboResolution.InsertString(index, "1536*864");
    m_comboResolution.SetItemData(index, 179);
    index++;

    m_comboResolution.InsertString(index, "3200*1800");
    m_comboResolution.SetItemData(index, 186);
    index++;

    m_comboResolution.InsertString(index, "1752*272");
    m_comboResolution.SetItemData(index, 187);
    index++;

    m_comboResolution.InsertString(index, "872*136");
    m_comboResolution.SetItemData(index, 188);
    index++;

    m_comboResolution.InsertString(index, "1280*1440");
    m_comboResolution.SetItemData(index, 189);
    index++;

    m_comboResolution.InsertString(index, "3520*544");
    m_comboResolution.SetItemData(index, 190);
    index++;
    
    m_comboResolution.InsertString(index, "1728*256");
    m_comboResolution.SetItemData(index, 191);
    index++;
    
    m_comboResolution.InsertString(index, "864*128");
    m_comboResolution.SetItemData(index, 192);
    index++;
    
    m_comboResolution.InsertString(index, "5470*3684");
    m_comboResolution.SetItemData(index, 193);
    index++;
    
    m_comboResolution.InsertString(index, "2560*750");
    m_comboResolution.SetItemData(index, 194);
    index++;
    
    m_comboResolution.InsertString(index, "1600*480");
    m_comboResolution.SetItemData(index, 195);
    index++;

    m_comboResolution.InsertString(index, "1024*300");
    m_comboResolution.SetItemData(index, 196);
    index++;

    m_comboResolution.InsertString(index, "848*480");
    m_comboResolution.SetItemData(index, 197);
    index++;

    m_comboResolution.InsertString(index, "8160*3616");
    m_comboResolution.SetItemData(index, 198);
    index++;

    m_comboResolution.InsertString(index, "8160*2304");
    m_comboResolution.SetItemData(index, 199);
    index++;

    m_comboResolution.InsertString(index, "4064*2560");
    m_comboResolution.SetItemData(index, 200);
    index++;

    m_comboResolution.InsertString(index, "1400*1050");
    m_comboResolution.SetItemData(index, 201);
    index++;

    m_comboResolution.InsertString(index, "2688*1512");
    m_comboResolution.SetItemData(index, 202);
    index++;

    m_comboResolution.InsertString(index, "704*288");
    m_comboResolution.SetItemData(index, 203);
    index++;

    m_comboResolution.InsertString(index, "1560*656");
    m_comboResolution.SetItemData(index, 204);
    index++;

    m_comboResolution.InsertString(index, "3072*1280");
    m_comboResolution.SetItemData(index, 205);
    index++;

    m_comboResolution.InsertString(index, "4320*1808");
    m_comboResolution.SetItemData(index, 206);
    index++;

    m_comboResolution.InsertString(index, "6120*2560");
    m_comboResolution.SetItemData(index, 207);
    index++;

    m_comboResolution.InsertString(index, "1280*960");
    m_comboResolution.SetItemData(index, 208);
    index++;

    m_comboResolution.InsertString(index, "3000*3000");
    m_comboResolution.SetItemData(index, 209);
    index++;

    m_comboResolution.InsertString(index, "2032*3616");
    m_comboResolution.SetItemData(index, 210);
    index++;

    m_comboResolution.InsertString(index, "Auto");
    m_comboResolution.SetItemData(index, 0xff);
    index++;
}
