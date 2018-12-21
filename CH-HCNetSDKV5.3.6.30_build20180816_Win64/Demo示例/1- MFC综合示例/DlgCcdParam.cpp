// DlgCcdParam1.cpp : implementation file
/**********************************************************
FileName:    DlgCcdParam.cpp
Description: CCD Parameter Config    
Date:        2009/11/11
Note: 		 <global>struct, refer to GeneralDef.h, global variants and functions refer to ClientDemo.cpp   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/06/10>       <created>
***********************************************************/

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgCcdParam.h"
#include "DlgInfrareCfg.h"
#include "DlgISPParamCfg.h"
#include "DlgSignalLightSync.h"
#include "DlgIOOutCfg.h"
#include "DlgEZVIZAccessCfg.h"
#include "DlgDPCCfg.h"
#include "DlgBuiltinSupplementLight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCcdParam dialog

/*********************************************************
  Function:	CDlgCcdParam
  Desc:		Constructor
  Input:	pParent, parent window pointer
  Output:	none
  Return:	none
**********************************************************/
CDlgCcdParam::CDlgCcdParam(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCcdParam::IDD, pParent)
    , m_byCalibrationAccurateLevel(0)
    , m_byZoomedInDistantViewLevel(0)
    , m_byHorizontalFOV(0)
    , m_byVerticalFOV(0)
    , m_byBrightnessSuddenChangeSuppression(FALSE)
  {
	//{{AFX_DATA_INIT(CDlgCcdParam)
	m_iBrightness = 0;
	m_iContrast = 0;
	m_iGain = 0;
	m_iSaturation = 0;
	m_iSharpness = 0;
	m_iExposureUserSet = 0;
	m_iVedioExposure = 0;
	m_iUserGain = 0;
	m_byNormalLevel = 0;
	m_bySpectralLevel = 0;
	m_byTemporalLevel = 0;
	m_byAutoCompInter = 0;
	m_bChkLightInhibitEn = FALSE;
	m_bChkIlluminationEn = FALSE;
	m_bChkSmartIREn = FALSE;
	m_byBGain = 0;
	m_byRGain = 0;
	m_byEndTimeHour = 0;
	m_byEndTimeMin = 0;
	m_byEndTimeSec = 0;
	m_dwBackLightX1 = 0;
	m_dwBackLightX2 = 0;
	m_dwBackLightY1 = 0;
	m_dwBackLightY2 = 0;
	m_byBeginTimeHour = 0;
	m_byBeginTimeMin = 0;
	m_byBeginTimeSec = 0;
	m_byDehazeLevel = 0;
	m_bChkCorridorMode = FALSE;
	m_byElectLevel = 0;
	m_byIRDistance = 0;
	m_byPIrisAperture = 0;
	m_bChkISPSet = FALSE;
	m_byLaserAngle = 0;
	m_byLaserBrightness = 0;
	m_byLaserSensitivity = 0;
	m_byLaserLimitBrightness = 0;
	m_byShortIRDistance = 0;
	m_byLongIRDistance = 0;
	m_byAGCGainLevel = 0;
	m_byAGCLightLevel = 0;
	m_byDDEExpertLevel = 0;
	m_byDDELevel = 0;
	m_dwFFCTime = 0;
	m_bLensDistortionCorrection = FALSE;
	m_byIllumination = 0;
	m_bChkLaserEnabled = FALSE;
	m_iDeviceIndex = -1;
	m_lChannel = -1;
	m_byLightAngle = 0;
	m_bOpticalDehaze = FALSE;
    m_iHighTemp = 0;
    m_iLowTemp = 0;
	//}}AFX_DATA_INIT
	memset(&m_struDehaze, 0, sizeof(m_struDehaze));
	memset(&m_struCorridorMode, 0, sizeof(m_struCorridorMode));
	memset(&m_struISPCameraParamCfg, 0, sizeof(m_struISPCameraParamCfg));
}

/*********************************************************
  Function:	DoDataExchange
  Desc:		the map between control and variable
  Input:	pDX, CDataExchange,pass the data exchange object to the window CWnd::DoDataExchange
  Output:	none
  Return:	none
**********************************************************/
void CDlgCcdParam::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgCcdParam)
    DDX_Control(pDX, IDC_COMBO_VIDEOFORMAT, m_comVideoFormat);
    DDX_Control(pDX, IDC_COMBO_FOCUSING_POSITION_STATE, m_comboFocusingPositionState);
    DDX_Control(pDX, IDC_COMBO_AGC_TYPE, m_comAGCType);
    DDX_Control(pDX, IDC_COMBO_AGC_TYPE_TEMP, m_comThermometryAGCType);
    DDX_Control(pDX, IDC_COMBO_FFC_MODE, m_comFFCMode);
    DDX_Control(pDX, IDC_COMBO_DDE_MODE, m_comDDEMode);
    DDX_Control(pDX, IDC_COMBO_MIRROR, m_comboMirror);
    DDX_Control(pDX, IDC_COMBO_LASER_TRIGGER_MODE, m_cmLaserTriggerMode);
    DDX_Control(pDX, IDC_COMBO_CONTROL_MODE, m_cmLaserControlMode);
    DDX_Control(pDX, IDC_COMBO_CAPTURE_MODE2, m_comboCaptureMode2);
    DDX_Control(pDX, IDC_COMBO_CAPTURE_MODE, m_comboCaptureMode);
    DDX_Control(pDX, IDC_COMBO_PIRIS_MODE, m_comboPIrisMode);
    DDX_Control(pDX, IDC_COMBO_SMARTIR_MODE, m_comboSmartIRMode);
    DDX_Control(pDX, IDC_COM_ELECTE, m_comElecteSwitch);
    DDX_Control(pDX, IDC_COMBO_DEHAZE_MODE, m_comboDehazeMode);
    DDX_Control(pDX, IDC_COMBO_LOCALOUTPUTCATE, m_comboLocalOutPutGate);
    DDX_Control(pDX, IDC_COMBO_DAYNIGHT_FILTER_TYPE, m_comboDayNightType);
    DDX_Control(pDX, IDC_COMBO_ALARM_TRIG_STATE, m_comboAlarmTrigMode);
    DDX_Control(pDX, IDC_COMBO_BACKLIGHT_MODE, m_comboBackLightMode);
    DDX_Control(pDX, IDC_COMBO_WHITEBALANCE_MODE, m_comboWhiteBalanceMode);
    DDX_Control(pDX, IDC_COMBO_LIGHT_INHIBIT_LEVEL, m_comboLightInhibitLevel);
    DDX_Control(pDX, IDC_COMBO_GRAY_LEVEL, m_comboGrayLevel);
    DDX_Control(pDX, IDC_COMBO_DIGITAL_ZOOM, m_comboDigitalZoom);
    DDX_Control(pDX, IDC_COMBO_PALETTE_MODE, m_comboPaletteMode);
    DDX_Control(pDX, IDC_COMBO_FOCUS_SPEED, m_comboFocusSpeed);
    DDX_Control(pDX, IDC_COMBO_FILTER_SWITCH, m_comboFilterSwitch);
    DDX_Control(pDX, IDC_COMBO_ENHANCE_MODE, m_comboEnhanceMode);
    DDX_Control(pDX, IDC_COMBO_DIMMERMODE, m_comboDimmerMode);
    DDX_Control(pDX, IDC_COMBO_INOUT_DOOR_MODE, m_comboInOutMode);
    DDX_Control(pDX, IDC_COMBO_NOISEMOVEMODE, m_comboNoiseMoveMode);
    DDX_Control(pDX, IDC_COMBO_IRISMODE, m_ctrlIrisMode);
    DDX_Control(pDX, IDC_COMBO_FUSION_MODE, m_comboFusionMode);
    DDX_Text(pDX, IDC_EDIT_BRIGHTNESS, m_iBrightness);
    DDX_Text(pDX, IDC_EDIT_CONTRAST, m_iContrast);
    DDX_Text(pDX, IDC_EDIT_AGC_HIGH_TEMP, m_iHighTemp);
    DDX_Text(pDX, IDC_EDIT_AGC_LOW_TEMP, m_iLowTemp);
    DDX_Text(pDX, IDC_EDIT_GAIN, m_iGain);
    DDX_Text(pDX, IDC_EDIT_SATURATION, m_iSaturation);
    DDX_Text(pDX, IDC_EDIT_SHARPNESS, m_iSharpness);
    DDX_Text(pDX, IDC_EDIT_EXPOSUREUSERSET, m_iExposureUserSet);
    DDX_Text(pDX, IDC_EDIT_VEDIOEXPOSURE, m_iVedioExposure);
    DDX_Text(pDX, IDC_EDIT_USERGAIN, m_iUserGain);
    DDX_Text(pDX, IDC_EDIT_NORMAILEVEL, m_byNormalLevel);
    DDX_Text(pDX, IDC_EDIT_SPECTRALLEVEL, m_bySpectralLevel);
    DDX_Text(pDX, IDC_EDIT_TEMPORALLEVEL, m_byTemporalLevel);
    DDX_Text(pDX, IDC_EDIT_AUTO_COMP_INTERVAL, m_byAutoCompInter);
    DDX_Check(pDX, IDC_CHK_LIGHT_INHIBIT_EN, m_bChkLightInhibitEn);
    DDX_Check(pDX, IDC_CHK_ILLUMINATION_EN, m_bChkIlluminationEn);
    DDX_Check(pDX, IDC_CHK_SMARTIR_ENABLE, m_bChkSmartIREn);
    DDX_Text(pDX, IDC_EDIT_B_GAIN, m_byBGain);
    DDX_Text(pDX, IDC_EDIT_R_GAIN, m_byRGain);
    DDX_Text(pDX, IDC_EDIT_END_TIME_HOUR1, m_byEndTimeHour);
    DDX_Text(pDX, IDC_EDIT_END_TIME_MIN, m_byEndTimeMin);
    DDX_Text(pDX, IDC_EDIT_END_TIME_SEC, m_byEndTimeSec);
    DDX_Text(pDX, IDC_EDIT_BACKLIGHT_X1, m_dwBackLightX1);
    DDX_Text(pDX, IDC_EDIT_BACKLIGHT_X2, m_dwBackLightX2);
    DDX_Text(pDX, IDC_EDIT_BACKLIGHT_Y1, m_dwBackLightY1);
    DDX_Text(pDX, IDC_EDIT_BACKLIGHT_Y2, m_dwBackLightY2);
    DDX_Text(pDX, IDC_EDIT_BEGIN_TIME_HOUR, m_byBeginTimeHour);
    DDX_Text(pDX, IDC_EDIT_BEGIN_TIME_MIN, m_byBeginTimeMin);
    DDX_Text(pDX, IDC_EDIT_BEGIN_TIME_SEC, m_byBeginTimeSec);
    DDX_Text(pDX, IDC_EDIT_DEHAZE_LEVEL, m_byDehazeLevel);
    DDX_Check(pDX, IDC_CHECK_CORRIDOR_MODE, m_bChkCorridorMode);
    DDX_Text(pDX, IDC_EDIT_ELECT_LEVEL, m_byElectLevel);
    DDX_Text(pDX, IDC_EDIT_IRDISTANCE, m_byIRDistance);
    DDX_Text(pDX, IDC_EDIT_PIRIS_APERTURE, m_byPIrisAperture);
    DDX_Check(pDX, IDC_CHK_ISPSET, m_bChkISPSet);
    DDX_Text(pDX, IDC_EDIT_ANGLE, m_byLaserAngle);
    DDX_Text(pDX, IDC_EDIT_LASER_BRIGHTNESS, m_byLaserBrightness);
    DDX_Text(pDX, IDC_EDIT_LASER_SENSITIVITY, m_byLaserSensitivity);
    DDX_Text(pDX, IDC_EDIT_LIMIT_BRIGHTNESS, m_byLaserLimitBrightness);
    DDX_Text(pDX, IDC_EDIT_SHORTIR_DISTANCE, m_byShortIRDistance);
    DDX_Text(pDX, IDC_EDIT_LONGIR_DISTANCE, m_byLongIRDistance);
    DDX_Text(pDX, IDC_EDIT_AGC_GAINLEVEL, m_byAGCGainLevel);
    DDX_Text(pDX, IDC_EDIT_AGC_LIGHTLEVEL, m_byAGCLightLevel);
    DDX_Text(pDX, IDC_EDIT_DDE_EXPERT_LEVEL, m_byDDEExpertLevel);
    DDX_Text(pDX, IDC_EDIT_DDE_LEVEL, m_byDDELevel);
    DDX_Text(pDX, IDC_EDIT_FFC_TIME, m_dwFFCTime);
    DDX_Check(pDX, IDC_CHECK_LENS_DIST_CORR, m_bLensDistortionCorrection);
    DDX_Text(pDX, IDC_EDIT_LIMIT_ILLUMINATION, m_byIllumination);
    DDX_Check(pDX, IDC_CHECK_LASER_ENABLED, m_bChkLaserEnabled);
    DDX_Text(pDX, IDC_EDIT_LIGHT_ANGLE, m_byLightAngle);
    DDX_Check(pDX, IDC_CHECK_OPTICAL_DEHAZE, m_bOpticalDehaze);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMBO_DistCorrectLevel, m_comDistortionCorrectionLevel);
    DDX_Text(pDX, IDC_EDIT4, m_byCalibrationAccurateLevel);
    DDX_Text(pDX, IDC_EDIT5, m_byZoomedInDistantViewLevel);
    DDX_Text(pDX, IDC_EDIT6, m_byHorizontalFOV);
    DDX_Text(pDX, IDC_EDIT8, m_byVerticalFOV);
    DDX_Check(pDX, IDC_CHECK1, m_byBrightnessSuddenChangeSuppression);
  }


BEGIN_MESSAGE_MAP(CDlgCcdParam, CDialog)
	//{{AFX_MSG_MAP(CDlgCcdParam)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_INFRARE_CFG, OnBtnInfrareCfg)
	ON_BN_CLICKED(IDC_BTN_SET_CORRIDOR_MODE, OnBtnSetCorridorMode)
	ON_BN_CLICKED(IDC_BTN_GET_CORRIDOR_MODE, OnBtnGetCorridorMode)
	ON_BN_CLICKED(IDC_BTN_GET_EX, OnBtnGetEx)
	ON_BN_CLICKED(IDC_BTN_SET_EX, OnBtnSetEx)
	ON_CBN_SELCHANGE(IDC_COMBO_IRISMODE, OnSelchangeComboIrismode)
	ON_CBN_SELCHANGE(IDC_COMBO_PIRIS_MODE, OnSelchangeComboPirisMode)
	ON_CBN_SELCHANGE(IDC_COMBO_SMARTIR_MODE, OnSelchangeComboSmartirMode)
    ON_CBN_SELCHANGE(IDC_COMBO_AGC_TYPE_TEMP, OnSelchangeComboAGCTempMode)
	ON_BN_CLICKED(IDC_BTN_ISP_PARAMSET, OnBtnIspParamset)
	ON_BN_CLICKED(IDC_BTN_SIGNALLIGHTSYNC, OnBtnSignallightsync)
	ON_BN_CLICKED(IDC_BTN_EZVIZ_ACCESSCFG, OnBtnEzvizAccesscfg)
	ON_BN_CLICKED(IDC_BTN_IOOUTCFG, OnBtnIOoutCfg)
	ON_BN_CLICKED(IDC_BTN_DPC, OnBtnDpc)
	ON_BN_CLICKED(IDC_BTN_FFC_MANUAL, OnBtnFfcManual)
	ON_BN_CLICKED(IDC_BTN_FFC_BACKCOMP, OnBtnFfcBackcomp)
	ON_CBN_SELCHANGE(IDC_COMBO_FFC_MODE, OnSelchangeComboFfcMode)
	ON_CBN_SELCHANGE(IDC_COMBO_DDE_MODE, OnSelchangeComboDdeMode)
	ON_CBN_SELCHANGE(IDC_COMBO_AGC_TYPE, OnSelchangeComboAgcType)
	ON_BN_CLICKED(IDC_BTN_FOCUSING_POSITION_STATE, OnBtnFocusingPositionState)
	ON_BN_CLICKED(IDC_BTN_SUPPLEMENTLIGHT, OnBtnSupplementlight)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCcdParam message handlers
/*********************************************************
  Function:	OnBtnGet
  Desc:		CCD parameter get
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgCcdParam::OnBtnGet() 
{
    DWORD dwReturn = 0;
    memset(&m_CcdParam, 0, sizeof(m_CcdParam));
    m_CcdParam.dwSize = sizeof(m_CcdParam);
    TRACE("ccdparamstruct size = %d", sizeof(m_CcdParam));
    if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_GET_CCDPARAMCFG, m_lChannel, &m_CcdParam, sizeof(m_CcdParam), &dwReturn))
    {
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_GET_CCDPARAMCFG");
    }
	else
	{
        g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_GET_CCDPARAMCFG");
	}

	if (m_CcdParam.byLocalOutputGate >= 20 && m_CcdParam.byLocalOutputGate <= 28)
	{
		m_comboLocalOutPutGate.SetCurSel(m_CcdParam.byLocalOutputGate - 16);
	}
	
	if (m_CcdParam.byLocalOutputGate >= 40 && m_CcdParam.byLocalOutputGate <= 48)
	{
		m_comboLocalOutPutGate.SetCurSel(m_CcdParam.byLocalOutputGate - 27);
	}
	else
	{
		m_comboLocalOutPutGate.SetCurSel(m_CcdParam.byLocalOutputGate);	
	}

    m_iBrightness = m_CcdParam.struVideoEffect.byBrightnessLevel;
    m_iExposureUserSet = m_CcdParam.struExposure.dwVideoExposureSet;
    m_iVedioExposure = m_CcdParam.struExposure.dwVideoExposureSet;
    m_iContrast = m_CcdParam.struVideoEffect.byContrastLevel;
    m_iGain = m_CcdParam.struGain.byGainLevel;
	m_iUserGain = m_CcdParam.struGain.byGainUserSet;
    m_iSaturation = m_CcdParam.struVideoEffect.bySaturationLevel;
    m_iSharpness = m_CcdParam.struVideoEffect.bySharpnessLevel;
	m_bChkSmartIREn = m_CcdParam.struVideoEffect.byEnableFunc&0x01;
	m_bChkIlluminationEn = (m_CcdParam.struVideoEffect.byEnableFunc>>1)&0x01;
	m_bChkLightInhibitEn = (m_CcdParam.struVideoEffect.byEnableFunc>>2)&0x01;
	m_comboLightInhibitLevel.SetCurSel(m_CcdParam.struVideoEffect.byLightInhibitLevel-1);
	m_comboGrayLevel.SetCurSel(m_CcdParam.struVideoEffect.byGrayLevel);
	m_ctrlIrisMode.SetCurSel(m_CcdParam.byIrisMode);

	m_comboWhiteBalanceMode.SetCurSel(m_CcdParam.struWhiteBalance.byWhiteBalanceMode);
	m_byBGain = m_CcdParam.struWhiteBalance.byWhiteBalanceModeBGain;
	m_byRGain = m_CcdParam.struWhiteBalance.byWhiteBalanceModeRGain;

	m_comboMirror.SetCurSel(m_CcdParam.byMirror);
	m_comboNoiseMoveMode.SetCurSel(m_CcdParam.struNoiseRemove.byDigitalNoiseRemoveEnable);
	m_byNormalLevel = m_CcdParam.struNoiseRemove.byDigitalNoiseRemoveLevel;
	m_bySpectralLevel = m_CcdParam.struNoiseRemove.bySpectralLevel;
	m_byTemporalLevel = m_CcdParam.struNoiseRemove.byTemporalLevel;

	m_comboDigitalZoom.SetCurSel(m_CcdParam.byDigitalZoom);
	m_comboDimmerMode.SetCurSel(m_CcdParam.byDimmerMode);
	m_comboEnhanceMode.SetCurSel(m_CcdParam.byEnhancedMode);
	m_comboPaletteMode.SetCurSel(m_CcdParam.byPaletteMode);
	m_comboFilterSwitch.SetCurSel(m_CcdParam.byFilterSwitch);
	m_comboFocusSpeed.SetCurSel(m_CcdParam.byFocusSpeed);
	m_byAutoCompInter = m_CcdParam.byAutoCompensationInterval;

	m_comboInOutMode.SetCurSel(m_CcdParam.bySceneMode);
	
	m_comboDayNightType.SetCurSel(m_CcdParam.struDayNight.byDayNightFilterType);
	m_byBeginTimeHour = m_CcdParam.struDayNight.byBeginTime;
	m_byBeginTimeMin = m_CcdParam.struDayNight.byBeginTimeMin;
	m_byBeginTimeSec = m_CcdParam.struDayNight.byBeginTimeSec;
	m_byEndTimeHour = m_CcdParam.struDayNight.byEndTime;
	m_byEndTimeMin = m_CcdParam.struDayNight.byEndTimeMin;
	m_byEndTimeSec = m_CcdParam.struDayNight.byEndTimeSec;
	m_comboAlarmTrigMode.SetCurSel(m_CcdParam.struDayNight.byAlarmTrigState);

	m_comboBackLightMode.SetCurSel(m_CcdParam.struBackLight.byBacklightMode);
	m_dwBackLightX1 = m_CcdParam.struBackLight.dwPositionX1;
	m_dwBackLightX2 = m_CcdParam.struBackLight.dwPositionX2;
	m_dwBackLightY1 = m_CcdParam.struBackLight.dwPositionY1;
	m_dwBackLightY2 = m_CcdParam.struBackLight.dwPositionY2;

	if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_GET_CAMERA_DEHAZE_CFG, m_lChannel, &m_struDehaze, sizeof(m_struDehaze), &dwReturn))
    {
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_GET_CAMERA_DEHAZE_CFG");
    }
	else
	{
        g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_GET_CAMERA_DEHAZE_CFG");
	}
	m_comboDehazeMode.SetCurSel(m_struDehaze.byDehazeMode);
	m_byDehazeLevel = m_struDehaze.byLevel;
 
	SetNewInfoToWnd();

    UpdateData(FALSE);
}

/*********************************************************
  Function:	OnBtnSet
  Desc:		CCD parameter set
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgCcdParam::OnBtnSet() 
{
    UpdateData(TRUE);
	if((m_iBrightness < 0) || (m_iBrightness >100) || (m_iContrast < 0) || (m_iContrast >100) ||  \
		(m_iSaturation < 0) || (m_iSaturation >100) || (m_iSharpness < 0) || (m_iSharpness >100) ||  \
		(m_iGain < 0) || (m_iGain >100) || (m_iUserGain < 0) || (m_iUserGain > 100))
	{
		return;
	}
    m_CcdParam.struVideoEffect.byBrightnessLevel = m_iBrightness;
    m_CcdParam.struVideoEffect.byContrastLevel = m_iContrast;
    m_CcdParam.struVideoEffect.bySaturationLevel = m_iSaturation;
    m_CcdParam.struVideoEffect.bySharpnessLevel = m_iSharpness;
	m_CcdParam.struVideoEffect.byEnableFunc = 0;
	m_CcdParam.struVideoEffect.byEnableFunc |= m_bChkSmartIREn;
	m_CcdParam.struVideoEffect.byEnableFunc |= (m_bChkIlluminationEn<<1);
	m_CcdParam.struVideoEffect.byEnableFunc |= (m_bChkLightInhibitEn<<2);
	m_CcdParam.struVideoEffect.byLightInhibitLevel = m_comboLightInhibitLevel.GetCurSel()+1;
	m_CcdParam.struVideoEffect.byGrayLevel = m_comboGrayLevel.GetCurSel();

    m_CcdParam.struExposure.dwExposureUserSet = m_iExposureUserSet;
    m_CcdParam.struExposure.dwVideoExposureSet = m_iVedioExposure;
    m_CcdParam.struGain.byGainLevel = m_iGain;
	m_CcdParam.struGain.byGainUserSet = m_iUserGain;
	m_CcdParam.byIrisMode = m_ctrlIrisMode.GetCurSel();
    m_CcdParam.dwSize = sizeof(m_CcdParam);

	m_CcdParam.struWhiteBalance.byWhiteBalanceMode = m_comboWhiteBalanceMode.GetCurSel();
	m_CcdParam.struWhiteBalance.byWhiteBalanceModeBGain = m_byBGain;
	m_CcdParam.struWhiteBalance.byWhiteBalanceModeRGain = m_byRGain;

	m_CcdParam.byMirror = m_comboMirror.GetCurSel();
	m_CcdParam.struNoiseRemove.byDigitalNoiseRemoveEnable = m_comboNoiseMoveMode.GetCurSel();
	m_CcdParam.struNoiseRemove.byDigitalNoiseRemoveLevel = m_byNormalLevel;
	m_CcdParam.struNoiseRemove.bySpectralLevel = m_bySpectralLevel;
	m_CcdParam.struNoiseRemove.byTemporalLevel = m_byTemporalLevel;

	m_CcdParam.byDigitalZoom = m_comboDigitalZoom.GetCurSel();
	m_CcdParam.byDimmerMode = m_comboDimmerMode.GetCurSel();
	m_CcdParam.byEnhancedMode = m_comboEnhanceMode.GetCurSel();
	m_CcdParam.byPaletteMode = m_comboPaletteMode.GetCurSel();
	m_CcdParam.byFilterSwitch = m_comboFilterSwitch.GetCurSel();
	m_CcdParam.byAutoCompensationInterval = m_byAutoCompInter;
	m_CcdParam.byFocusSpeed = m_comboFocusSpeed.GetCurSel();

	m_CcdParam.bySceneMode = m_comboInOutMode.GetCurSel();
	m_CcdParam.byLocalOutputGate = m_comboLocalOutPutGate.GetItemData(m_comboLocalOutPutGate.GetCurSel());
	m_CcdParam.struDayNight.byDayNightFilterType = m_comboDayNightType.GetCurSel();
	m_CcdParam.struDayNight.byBeginTime = m_byBeginTimeHour;
	m_CcdParam.struDayNight.byBeginTimeMin = m_byBeginTimeMin;
	m_CcdParam.struDayNight.byBeginTimeSec = m_byBeginTimeSec;
	m_CcdParam.struDayNight.byEndTime = m_byEndTimeHour;
	m_CcdParam.struDayNight.byEndTimeMin = m_byEndTimeMin;
	m_CcdParam.struDayNight.byEndTimeSec = m_byEndTimeSec;
	m_CcdParam.struDayNight.byAlarmTrigState = m_comboAlarmTrigMode.GetCurSel();

	m_CcdParam.struBackLight.byBacklightMode = m_comboBackLightMode.GetCurSel();
	m_CcdParam.struBackLight.dwPositionX1 = m_dwBackLightX1;
	m_CcdParam.struBackLight.dwPositionX2 = m_dwBackLightX2;
	m_CcdParam.struBackLight.dwPositionY1 = m_dwBackLightY1;
	m_CcdParam.struBackLight.dwPositionY2 = m_dwBackLightY2;

    if (!NET_DVR_SetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_SET_CCDPARAMCFG, m_lChannel, &m_CcdParam, sizeof(m_CcdParam)))
    {
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_SET_CCDPARAMCFG");
        return;
    }
	else
	{
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_SET_CCDPARAMCFG");
	}

	m_struDehaze.byDehazeMode = m_comboDehazeMode.GetCurSel();
	m_struDehaze.byLevel = m_byDehazeLevel;
	if (!NET_DVR_SetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_SET_CAMERA_DEHAZE_CFG, m_lChannel, &m_struDehaze, sizeof(m_struDehaze)))
    {
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_SET_CAMERA_DEHAZE_CFG");
        return;
    }
	else
	{
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_SET_CAMERA_DEHAZE_CFG");
	}
}

/*********************************************************
  Function:	OnBtnExit
  Desc:		Exit fun
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgCcdParam::OnBtnExit() 
{
    CDialog::OnCancel();	
}

/*********************************************************
  Function:	OnInitDialog
  Desc:		Initialize the dialog
  Input:	
  Output:	
  Return:	
**********************************************************/
BOOL CDlgCcdParam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitLocalOutPutGate();
	GetDlgItem(IDC_COMBO_PIRIS_MODE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_PIRIS_APERTURE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_PIRIS_APERTURE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_PIRIS_MODE)->ShowWindow(SW_HIDE);


	OnBtnGet();
	OnBtnGetEx();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCcdParam::InitLocalOutPutGate()
{
	char szLan[128] = {0};
	m_comboLocalOutPutGate.ResetContent();
	g_StringLanType(szLan, "本地输出关闭", "Local output off");
	m_comboLocalOutPutGate.InsertString(0, szLan);
    m_comboLocalOutPutGate.SetItemData(0, 0);
	
	g_StringLanType(szLan, "本地输出打开", "Local output on");
	m_comboLocalOutPutGate.InsertString(1, szLan);
    m_comboLocalOutPutGate.SetItemData(1, 1);
	
	g_StringLanType(szLan, "缩放输出", "Scaling output");
	m_comboLocalOutPutGate.InsertString(2, szLan);
    m_comboLocalOutPutGate.SetItemData(2, 11);
	
	g_StringLanType(szLan, "裁剪输出", "Cutting output");
	m_comboLocalOutPutGate.InsertString(3, szLan);
    m_comboLocalOutPutGate.SetItemData(3, 12);
	//
	//20-HDMI_720P50输出开
	//21-HDMI_720P60输出开
	//22-HDMI_1080I60输出开
	//23-HDMI_1080I50输出开
	//24-HDMI_1080P24输出开
	//25-HDMI_1080P25输出开
	//26-HDMI_1080P30输出开
	//27-HDMI_1080P50输出开
	//28-HDMI_1080P60输出开
	g_StringLanType(szLan, "HDMI_720P50输出", "HDMI_720P50 output");
	m_comboLocalOutPutGate.InsertString(4, szLan);
    m_comboLocalOutPutGate.SetItemData(4, 20);
	
	g_StringLanType(szLan, "HDMI_720P60输出", "HDMI_720P60 output");
	m_comboLocalOutPutGate.InsertString(5, szLan);
    m_comboLocalOutPutGate.SetItemData(5, 21);
	
	g_StringLanType(szLan, "HDMI_1080I60输出", "SDI_1080I60 output");
	m_comboLocalOutPutGate.InsertString(6, szLan);
    m_comboLocalOutPutGate.SetItemData(6, 22);
	
	g_StringLanType(szLan, "HDMI_1080I50输出", "HDMI_1080I50 output");
	m_comboLocalOutPutGate.InsertString(7, szLan);
    m_comboLocalOutPutGate.SetItemData(7, 23);
	
	g_StringLanType(szLan, "HDMI_1080P24输出", "HDMI_1080P24 output");
	m_comboLocalOutPutGate.InsertString(8, szLan);
    m_comboLocalOutPutGate.SetItemData(8, 24);
	
	g_StringLanType(szLan, "HDMI_1080P25输出", "HDMI_1080P25 output");
	m_comboLocalOutPutGate.InsertString(9, szLan);
    m_comboLocalOutPutGate.SetItemData(9, 25);
	
	g_StringLanType(szLan, "HDMI_1080P30输出", "HDMI_1080P30 output");
	m_comboLocalOutPutGate.InsertString(10, szLan);
    m_comboLocalOutPutGate.SetItemData(10, 26);
	
	g_StringLanType(szLan, "HDMI_1080P50输出", "HDMI_1080P50 output");
	m_comboLocalOutPutGate.InsertString(11, szLan);
    m_comboLocalOutPutGate.SetItemData(11, 27);
	
	g_StringLanType(szLan, "HDMI_1080P60输出", "HDMI_1080P60 output");
	m_comboLocalOutPutGate.InsertString(12, szLan);
    m_comboLocalOutPutGate.SetItemData(12, 28);
	//SDI输出测试40～48
	//40-SDI_720P50,
	//41-SDI_720P60,
	//42-SDI_1080I50,
	//43-SDI_1080I60,
	//44-SDI_1080P24,
	//45-SDI_1080P25,
	//46-SDI_1080P30,
	//47-SDI_1080P50,
	//48-SDI_1080P60
	g_StringLanType(szLan, "SDI_720P50输出", "SDI_720P50 output");
	m_comboLocalOutPutGate.InsertString(13, szLan);
    m_comboLocalOutPutGate.SetItemData(13, 40);
	
	g_StringLanType(szLan, "SDI_720P60输出", "SDI_720P60 output");
	m_comboLocalOutPutGate.InsertString(14, szLan);
    m_comboLocalOutPutGate.SetItemData(14, 41);
	
	g_StringLanType(szLan, "SDI_1080I50输出", "SDI_1080I50 output");
	m_comboLocalOutPutGate.InsertString(15, szLan);
    m_comboLocalOutPutGate.SetItemData(15, 42);
	
	g_StringLanType(szLan, "SDI_1080I60输出", "SDI_1080I60 output");
	m_comboLocalOutPutGate.InsertString(16, szLan);
    m_comboLocalOutPutGate.SetItemData(16, 43);
	
	g_StringLanType(szLan, "SDI_1080P24输出", "SDI_1080P24 output");
	m_comboLocalOutPutGate.InsertString(17, szLan);
    m_comboLocalOutPutGate.SetItemData(17, 44);
	
	g_StringLanType(szLan, "SDI_1080P25输出", "SDI_1080P25 output");
	m_comboLocalOutPutGate.InsertString(18, szLan);
    m_comboLocalOutPutGate.SetItemData(18, 45);
	
	g_StringLanType(szLan, "SDI_1080P30输出", "SDI_1080P30 output");
	m_comboLocalOutPutGate.InsertString(19, szLan);
    m_comboLocalOutPutGate.SetItemData(19, 46);
	
	g_StringLanType(szLan, "SDI_1080P50输出", "SDI_1080P50 output");
	m_comboLocalOutPutGate.InsertString(20, szLan);
    m_comboLocalOutPutGate.SetItemData(20, 47);
	
	g_StringLanType(szLan, "SDI_1080P60输出", "SDI_1080P60 output");
	m_comboLocalOutPutGate.InsertString(21, szLan);
    m_comboLocalOutPutGate.SetItemData(21, 48);

	m_comboWhiteBalanceMode.ResetContent();
	g_StringLanType(szLan, "手动白平衡","MWB");
	m_comboWhiteBalanceMode.InsertString(0, szLan);
	m_comboWhiteBalanceMode.SetItemData(0, 0);
	
	g_StringLanType(szLan, "自动白平衡1", "AWB1");
	m_comboWhiteBalanceMode.InsertString(1, szLan);
	m_comboWhiteBalanceMode.SetItemData(1, 1);
	
	g_StringLanType(szLan, "自动白平衡2", "AWB2");
	m_comboWhiteBalanceMode.InsertString(2, szLan);
	m_comboWhiteBalanceMode.SetItemData(2, 2);
	
	g_StringLanType(szLan, "锁定白平衡", "Locked WB");
	m_comboWhiteBalanceMode.InsertString(3, szLan);
	m_comboWhiteBalanceMode.SetItemData(3, 3);
	
	g_StringLanType(szLan, "室外", "Outdoor");
	m_comboWhiteBalanceMode.InsertString(4, szLan);
	m_comboWhiteBalanceMode.SetItemData(4, 4);
	
	g_StringLanType(szLan, "室内", "Indoor");
	m_comboWhiteBalanceMode.InsertString(5, szLan);
	m_comboWhiteBalanceMode.SetItemData(5, 5);
	
	g_StringLanType(szLan, "日光灯", "Fluorescent Lamp");
	m_comboWhiteBalanceMode.InsertString(6, szLan);
	m_comboWhiteBalanceMode.SetItemData(6, 6);
	
	g_StringLanType(szLan, "钠灯", "Sodium Lamp");
	m_comboWhiteBalanceMode.InsertString(7, szLan);
	m_comboWhiteBalanceMode.SetItemData(7, 7);
	
	g_StringLanType(szLan, "自动跟踪", "Auto-Track");
	m_comboWhiteBalanceMode.InsertString(8, szLan);
	m_comboWhiteBalanceMode.SetItemData(8, 8);
	
	g_StringLanType(szLan, "一次白平衡", "One Push");
	m_comboWhiteBalanceMode.InsertString(9, szLan);
	m_comboWhiteBalanceMode.SetItemData(9, 9);
	
	g_StringLanType(szLan, "室外自动", "Auto-Outdoor");
	m_comboWhiteBalanceMode.InsertString(10, szLan);
	m_comboWhiteBalanceMode.SetItemData(10, 10);
	
	g_StringLanType(szLan, "钠灯自动", "Auto-Sodiumlight");
	m_comboWhiteBalanceMode.InsertString(11, szLan);
	m_comboWhiteBalanceMode.SetItemData(11, 11);
	
	g_StringLanType(szLan, "水银灯", "Mercury Lamp");
	m_comboWhiteBalanceMode.InsertString(12, szLan);
	m_comboWhiteBalanceMode.SetItemData(12, 12);
	
	g_StringLanType(szLan, "自动白平衡", "Auto-WB");
	m_comboWhiteBalanceMode.InsertString(13, szLan);
	m_comboWhiteBalanceMode.SetItemData(13, 13);
	
	g_StringLanType(szLan, "白炽灯", "IncandescentLamp");
	m_comboWhiteBalanceMode.InsertString(14, szLan);
	m_comboWhiteBalanceMode.SetItemData(14, 14);
	
	g_StringLanType(szLan, "暖光灯", "Warm Light Lamp");
	m_comboWhiteBalanceMode.InsertString(15, szLan);
	m_comboWhiteBalanceMode.SetItemData(15, 15);
	
	g_StringLanType(szLan, "自然光", "Natural Light");
	m_comboWhiteBalanceMode.InsertString(16, szLan);
	m_comboWhiteBalanceMode.SetItemData(16, 16);

	
	m_cmLaserControlMode.ResetContent();
	g_StringLanType(szLan, "自动", "Auto");
	m_cmLaserControlMode.AddString(szLan);
	g_StringLanType(szLan, "手动", "manual");
	m_cmLaserControlMode.AddString(szLan);
	
	m_cmLaserTriggerMode.ResetContent();
	g_StringLanType(szLan, "机芯触发", "Camera Module Trigger ");
	m_cmLaserTriggerMode.AddString(szLan);
	g_StringLanType(szLan, "光敏触发", "Photoresistance Trigger");
	m_cmLaserTriggerMode.AddString(szLan);

    m_comFFCMode.SetCurSel(0);
    m_comDDEMode.SetCurSel(0);
	m_comAGCType.SetCurSel(0);
}

void CDlgCcdParam::OnBtnInfrareCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgInfrareCfg dlg;
	dlg.m_iDevIndex = m_iDeviceIndex;
    dlg.m_lChannel = m_lChannel;
	dlg.DoModal();
}

void CDlgCcdParam::OnBtnSetCorridorMode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struCorridorMode.dwSize = sizeof(m_struCorridorMode);
	m_struCorridorMode.byEnableCorridorMode = m_bChkCorridorMode;
	
    if (!NET_DVR_SetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_SET_CORRIDOR_MODE, m_lChannel, &m_struCorridorMode, sizeof(m_struCorridorMode)))
    {
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_SET_CORRIDOR_MODE");
        return;
    }
	else
	{
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_SET_CORRIDOR_MODE");
	}
	
}

void CDlgCcdParam::OnBtnGetCorridorMode() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
	memset(&m_struCorridorMode, 0, sizeof(m_struCorridorMode));
	
	if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_GET_CORRIDOR_MODE, m_lChannel, &m_struCorridorMode, sizeof(m_struCorridorMode), &dwReturn))
    {
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_GET_CCDPARAMCFG");
		return;
    }
	else
	{
        g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_GET_CCDPARAMCFG");
	}
	m_bChkCorridorMode = m_struCorridorMode.byEnableCorridorMode;
	UpdateData(FALSE);
}


void CDlgCcdParam::OnBtnGetEx() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReturn = 0;
	memset(&m_CcdParamEx, 0, sizeof(m_CcdParamEx));
	if (m_bChkISPSet)
	{
		memset(&m_struISPCameraParamCfg, 0, sizeof(m_struISPCameraParamCfg));
		if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_GET_ISP_CAMERAPARAMCFG, m_lChannel, \
			&m_struISPCameraParamCfg, sizeof(m_struISPCameraParamCfg), &dwReturn))
		{
			g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_FAIL_T, "Error Code = %d ;NET_DVR_GET_ISP_CAMERAPARAMCFG", NET_DVR_GetLastError());
		}
		else
		{
			g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_SUCC_T, "Error Code = %d ;NET_DVR_GET_ISP_CAMERAPARAMCFG", NET_DVR_GetLastError());

			memcpy(&m_CcdParamEx, &m_struISPCameraParamCfg.struSelfAdaptiveParam, sizeof(m_CcdParamEx));
		}
	} 
	else
	{
		
		m_CcdParamEx.dwSize = sizeof(m_CcdParamEx);
		TRACE("ccdparamstruct size = %d", sizeof(m_CcdParamEx));
		if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_GET_CCDPARAMCFG_EX, m_lChannel, &m_CcdParamEx, sizeof(m_CcdParamEx), &dwReturn))
		{
			g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_FAIL_T, "Error Code = %d ;NET_DVR_GET_CCDPARAMCFG_EX", NET_DVR_GetLastError());
		}
		else
		{
			g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_SUCC_T, "Error Code = %d ;NET_DVR_GET_CCDPARAMCFG_EX", NET_DVR_GetLastError());
		}
	}

	//m_comboLocalOutPutGate.SetCurSel(m_CcdParamEx.byLocalOutputGate);
	if (m_CcdParamEx.byLocalOutputGate >= 20 && m_CcdParamEx.byLocalOutputGate <= 28)
	{
		m_comboLocalOutPutGate.SetCurSel(m_CcdParamEx.byLocalOutputGate - 16);
	}
	
	if (m_CcdParamEx.byLocalOutputGate >= 40 && m_CcdParamEx.byLocalOutputGate <= 48)
	{
		m_comboLocalOutPutGate.SetCurSel(m_CcdParamEx.byLocalOutputGate - 27);
	}
	else
	{
		m_comboLocalOutPutGate.SetCurSel(m_CcdParamEx.byLocalOutputGate);
	}
	
    m_iBrightness = m_CcdParamEx.struVideoEffect.byBrightnessLevel;
    m_iExposureUserSet = m_CcdParamEx.struExposure.dwVideoExposureSet;
    m_iVedioExposure = m_CcdParamEx.struExposure.dwVideoExposureSet;
    m_iContrast = m_CcdParamEx.struVideoEffect.byContrastLevel;
    m_iGain = m_CcdParamEx.struGain.byGainLevel;
	m_iUserGain = m_CcdParamEx.struGain.byGainUserSet;
    m_iSaturation = m_CcdParamEx.struVideoEffect.bySaturationLevel;
    m_iSharpness = m_CcdParamEx.struVideoEffect.bySharpnessLevel;
	m_bChkSmartIREn = m_CcdParamEx.struVideoEffect.byEnableFunc&0x01;
	m_bChkIlluminationEn = (m_CcdParamEx.struVideoEffect.byEnableFunc>>1)&0x01;
	m_bChkLightInhibitEn = (m_CcdParamEx.struVideoEffect.byEnableFunc>>2)&0x01;
	m_comboLightInhibitLevel.SetCurSel(m_CcdParamEx.struVideoEffect.byLightInhibitLevel-1);
	m_comboGrayLevel.SetCurSel(m_CcdParamEx.struVideoEffect.byGrayLevel);
	m_ctrlIrisMode.SetCurSel(m_CcdParamEx.byIrisMode);
	
	m_comboWhiteBalanceMode.SetCurSel(m_CcdParamEx.struWhiteBalance.byWhiteBalanceMode);
	m_byBGain = m_CcdParamEx.struWhiteBalance.byWhiteBalanceModeBGain;
	m_byRGain = m_CcdParamEx.struWhiteBalance.byWhiteBalanceModeRGain;

	m_comVideoFormat.SetCurSel(m_CcdParamEx.byPowerLineFrequencyMode);
	m_comboMirror.SetCurSel(m_CcdParamEx.byMirror);
	m_comboNoiseMoveMode.SetCurSel(m_CcdParamEx.struNoiseRemove.byDigitalNoiseRemoveEnable);
	m_byNormalLevel = m_CcdParamEx.struNoiseRemove.byDigitalNoiseRemoveLevel;
	m_bySpectralLevel = m_CcdParamEx.struNoiseRemove.bySpectralLevel;
	m_byTemporalLevel = m_CcdParamEx.struNoiseRemove.byTemporalLevel;
	
	m_comboDigitalZoom.SetCurSel(m_CcdParamEx.byDigitalZoom);
	m_comboDimmerMode.SetCurSel(m_CcdParamEx.byDimmerMode);
	m_comboEnhanceMode.SetCurSel(m_CcdParamEx.byEnhancedMode);
	m_comboPaletteMode.SetCurSel(m_CcdParamEx.byPaletteMode);
	m_comboFilterSwitch.SetCurSel(m_CcdParamEx.byFilterSwitch);
	m_comboFocusSpeed.SetCurSel(m_CcdParamEx.byFocusSpeed);
	m_byAutoCompInter = m_CcdParamEx.byAutoCompensationInterval;
	
	m_comboInOutMode.SetCurSel(m_CcdParamEx.bySceneMode);
	
	m_comboDayNightType.SetCurSel(m_CcdParamEx.struDayNight.byDayNightFilterType);
	m_byBeginTimeHour = m_CcdParamEx.struDayNight.byBeginTime;
	m_byBeginTimeMin = m_CcdParamEx.struDayNight.byBeginTimeMin;
	m_byBeginTimeSec = m_CcdParamEx.struDayNight.byBeginTimeSec;
	m_byEndTimeHour = m_CcdParamEx.struDayNight.byEndTime;
	m_byEndTimeMin = m_CcdParamEx.struDayNight.byEndTimeMin;
	m_byEndTimeSec = m_CcdParamEx.struDayNight.byEndTimeSec;
	m_comboAlarmTrigMode.SetCurSel(m_CcdParamEx.struDayNight.byAlarmTrigState);
	
	m_comboBackLightMode.SetCurSel(m_CcdParamEx.struBackLight.byBacklightMode);
	m_dwBackLightX1 = m_CcdParamEx.struBackLight.dwPositionX1;
	m_dwBackLightX2 = m_CcdParamEx.struBackLight.dwPositionX2;
	m_dwBackLightY1 = m_CcdParamEx.struBackLight.dwPositionY1;
	m_dwBackLightY2 = m_CcdParamEx.struBackLight.dwPositionY2;
	
	//透雾
	m_comboDehazeMode.SetCurSel(m_CcdParamEx.struDefogCfg.byMode);
	m_byDehazeLevel = m_CcdParamEx.struDefogCfg.byLevel;
	
	//电子防抖
	m_comElecteSwitch.SetCurSel(m_CcdParamEx.struElectronicStabilization.byEnable);
	m_byElectLevel = m_CcdParamEx.struElectronicStabilization.byLevel;
	
	m_bChkCorridorMode = m_CcdParamEx.struCorridorMode.byEnableCorridorMode;
	
	m_comboSmartIRMode.SetCurSel(m_CcdParamEx.struSmartIRParam.byMode);
	m_byIRDistance = m_CcdParamEx.struSmartIRParam.byIRDistance;
	
	m_byShortIRDistance =m_CcdParamEx.struSmartIRParam.byShortIRDistance;
	m_byLongIRDistance = m_CcdParamEx.struSmartIRParam.byLongIRDistance;

	m_comboPIrisMode.SetCurSel(m_CcdParamEx.struPIrisParam.byMode);
	m_byPIrisAperture = m_CcdParamEx.struPIrisParam.byPIrisAperture;

	m_comboCaptureMode.SetCurSel(m_CcdParamEx.byCaptureModeN);
	m_comboCaptureMode2.SetCurSel(m_CcdParamEx.byCaptureModeP);

	
	//激光参数
	m_cmLaserControlMode.SetCurSel(m_CcdParamEx.struLaserParam.byControlMode - 1);
	m_cmLaserTriggerMode.SetCurSel(m_CcdParamEx.struLaserParam.byTriggerMode - 1);
	m_byLaserAngle = m_CcdParamEx.struLaserParam.byAngle;
	m_byLaserBrightness = m_CcdParamEx.struLaserParam.byBrightness;
	m_byLaserSensitivity = m_CcdParamEx.struLaserParam.bySensitivity;
	m_byLaserLimitBrightness = m_CcdParamEx.struLaserParam.byLimitBrightness;//2014-01-26
	m_bChkLaserEnabled = m_CcdParamEx.struLaserParam.byEnabled;
	m_byIllumination = m_CcdParamEx.struLaserParam.byIllumination;
	m_byLightAngle = m_CcdParamEx.struLaserParam.byLightAngle;
	
    m_comFFCMode.SetCurSel(m_CcdParamEx.struFFCParam.byMode - 1);
    m_dwFFCTime = m_CcdParamEx.struFFCParam.wCompensateTime;
    
    m_comDDEMode.SetCurSel(m_CcdParamEx.struDDEParam.byMode - 1);
    m_byDDELevel = m_CcdParamEx.struDDEParam.byNormalLevel;
    m_byDDEExpertLevel = m_CcdParamEx.struDDEParam.byExpertLevel;
    
    m_comThermometryAGCType.SetCurSel(m_CcdParamEx.struThermAGC.byMode);
    m_iHighTemp = m_CcdParamEx.struThermAGC.iHighTemperature;
    m_iLowTemp = m_CcdParamEx.struThermAGC.iLowTemperature;

    m_comAGCType.SetCurSel(m_CcdParamEx.struAGCParam.bySceneType - 1);
    m_byAGCLightLevel = m_CcdParamEx.struAGCParam.byLightLevel;
    m_byAGCGainLevel = m_CcdParamEx.struAGCParam.byGainLevel;
    
	m_bLensDistortionCorrection = m_CcdParamEx.byLensDistortionCorrection;

    if (m_CcdParamEx.byDistortionCorrectionLevel==255)
    {
        m_comDistortionCorrectionLevel.SetCurSel(4);
    } 
    else
    {
        m_comDistortionCorrectionLevel.SetCurSel(m_CcdParamEx.byDistortionCorrectionLevel);
    }
    m_byCalibrationAccurateLevel = m_CcdParamEx.byCalibrationAccurateLevel;
    m_byZoomedInDistantViewLevel = m_CcdParamEx.byZoomedInDistantViewLevel;
    m_byHorizontalFOV = m_CcdParamEx.byHorizontalFOV;
    m_byVerticalFOV = m_CcdParamEx.byVerticalFOV;

	m_bOpticalDehaze = m_CcdParamEx.struOpticalDehaze.byEnable;

    m_comboFusionMode.SetCurSel(m_CcdParamEx.byFusionMode);

    m_byBrightnessSuddenChangeSuppression = m_CcdParamEx.byBrightnessSuddenChangeSuppression;

	SetNewInfoToWnd();

    UpdateData(FALSE);
	
}

void CDlgCcdParam::SetNewInfoToWnd()
{
    OnSelchangeComboAGCTempMode();

	if (m_comboPIrisMode.GetCurSel() != 0)
	{
		GetDlgItem(IDC_STATIC_PIRIS_APERTURE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PIRIS_APERTURE)->EnableWindow(TRUE);
	} 
	else
	{
		GetDlgItem(IDC_STATIC_PIRIS_APERTURE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PIRIS_APERTURE)->EnableWindow(FALSE);		
	}
	
	if (m_comboSmartIRMode.GetCurSel() != 0)
	{
		GetDlgItem(IDC_STATIC_IR_DISTANCE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_IRDISTANCE)->EnableWindow(TRUE);
	} 
	else
	{
		GetDlgItem(IDC_STATIC_IR_DISTANCE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_IRDISTANCE)->EnableWindow(FALSE);		
	}
	
	if (m_ctrlIrisMode.GetCurSel() == 2  || m_ctrlIrisMode.GetCurSel() == 3 || m_ctrlIrisMode.GetCurSel() == 4 || m_ctrlIrisMode.GetCurSel() == 5)
	{
		GetDlgItem(IDC_COMBO_PIRIS_MODE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PIRIS_APERTURE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PIRIS_APERTURE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PIRIS_MODE)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_COMBO_PIRIS_MODE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PIRIS_APERTURE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PIRIS_APERTURE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PIRIS_MODE)->ShowWindow(SW_HIDE);
	}	
}

void CDlgCcdParam::OnBtnSetEx() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if((m_iBrightness < 0) || (m_iBrightness >100) || (m_iContrast < 0) || (m_iContrast >100) ||  \
		(m_iSaturation < 0) || (m_iSaturation >100) || (m_iSharpness < 0) || (m_iSharpness >100) ||  \
		(m_iGain < 0) || (m_iGain >100) || (m_iUserGain < 0) || (m_iUserGain > 100))
	{
		return;
	}
	//memset(&m_CcdParamEx, 0, sizeof(m_CcdParamEx));
    m_CcdParamEx.struVideoEffect.byBrightnessLevel = m_iBrightness;
    m_CcdParamEx.struVideoEffect.byContrastLevel = m_iContrast;
    m_CcdParamEx.struVideoEffect.bySaturationLevel = m_iSaturation;
    m_CcdParamEx.struVideoEffect.bySharpnessLevel = m_iSharpness;
	m_CcdParamEx.struVideoEffect.byEnableFunc = 0;
	m_CcdParamEx.struVideoEffect.byEnableFunc |= m_bChkSmartIREn;
	m_CcdParamEx.struVideoEffect.byEnableFunc |= (m_bChkIlluminationEn<<1);
	m_CcdParamEx.struVideoEffect.byEnableFunc |= (m_bChkLightInhibitEn<<2);
	m_CcdParamEx.struVideoEffect.byLightInhibitLevel = m_comboLightInhibitLevel.GetCurSel()+1;
	m_CcdParamEx.struVideoEffect.byGrayLevel = m_comboGrayLevel.GetCurSel();
	
	m_CcdParamEx.struExposure.byExposureMode = 1;
    m_CcdParamEx.struExposure.dwExposureUserSet = m_iExposureUserSet;
    m_CcdParamEx.struExposure.dwVideoExposureSet = m_iVedioExposure;
    m_CcdParamEx.struGain.byGainLevel = m_iGain;
	m_CcdParamEx.struGain.byGainUserSet = m_iUserGain;
	m_CcdParamEx.byIrisMode = m_ctrlIrisMode.GetCurSel();
    m_CcdParamEx.dwSize = sizeof(m_CcdParamEx);
	
	m_CcdParamEx.struWhiteBalance.byWhiteBalanceMode = m_comboWhiteBalanceMode.GetCurSel();
	m_CcdParamEx.struWhiteBalance.byWhiteBalanceModeBGain = m_byBGain;
	m_CcdParamEx.struWhiteBalance.byWhiteBalanceModeRGain = m_byRGain;
	
	m_CcdParamEx.byPowerLineFrequencyMode = m_comVideoFormat.GetCurSel();
	m_CcdParamEx.byMirror = m_comboMirror.GetCurSel();
	m_CcdParamEx.struNoiseRemove.byDigitalNoiseRemoveEnable = m_comboNoiseMoveMode.GetCurSel();
	m_CcdParamEx.struNoiseRemove.byDigitalNoiseRemoveLevel = m_byNormalLevel;
	m_CcdParamEx.struNoiseRemove.bySpectralLevel = m_bySpectralLevel;
	m_CcdParamEx.struNoiseRemove.byTemporalLevel = m_byTemporalLevel;
	
	m_CcdParamEx.byDigitalZoom = m_comboDigitalZoom.GetCurSel();
	m_CcdParamEx.byDimmerMode = m_comboDimmerMode.GetCurSel();
	m_CcdParamEx.byEnhancedMode = m_comboEnhanceMode.GetCurSel();
	m_CcdParamEx.byPaletteMode = m_comboPaletteMode.GetCurSel();
	m_CcdParamEx.byFilterSwitch = m_comboFilterSwitch.GetCurSel();
	m_CcdParamEx.byAutoCompensationInterval = m_byAutoCompInter;
	m_CcdParamEx.byFocusSpeed = m_comboFocusSpeed.GetCurSel();
	
	m_CcdParamEx.bySceneMode = m_comboInOutMode.GetCurSel();
	m_CcdParamEx.byLocalOutputGate = m_comboLocalOutPutGate.GetItemData(m_comboLocalOutPutGate.GetCurSel());
	m_CcdParamEx.struDayNight.byDayNightFilterType = m_comboDayNightType.GetCurSel();
	m_CcdParamEx.struDayNight.byBeginTime = m_byBeginTimeHour;
	m_CcdParamEx.struDayNight.byBeginTimeMin = m_byBeginTimeMin;
	m_CcdParamEx.struDayNight.byBeginTimeSec = m_byBeginTimeSec;
	m_CcdParamEx.struDayNight.byEndTime = m_byEndTimeHour;
	m_CcdParamEx.struDayNight.byEndTimeMin = m_byEndTimeMin;
	m_CcdParamEx.struDayNight.byEndTimeSec = m_byEndTimeSec;
	m_CcdParamEx.struDayNight.byAlarmTrigState = m_comboAlarmTrigMode.GetCurSel();
	
	m_CcdParamEx.struBackLight.byBacklightMode = m_comboBackLightMode.GetCurSel();
	m_CcdParamEx.struBackLight.dwPositionX1 = m_dwBackLightX1;
	m_CcdParamEx.struBackLight.dwPositionX2 = m_dwBackLightX2;
	m_CcdParamEx.struBackLight.dwPositionY1 = m_dwBackLightY1;
	m_CcdParamEx.struBackLight.dwPositionY2 = m_dwBackLightY2;
	
	m_CcdParamEx.struDefogCfg.byMode = m_comboDehazeMode.GetCurSel();
	m_CcdParamEx.struDefogCfg.byLevel = m_byDehazeLevel;
	
	m_CcdParamEx.struElectronicStabilization.byEnable = m_comElecteSwitch.GetCurSel();
	m_CcdParamEx.struElectronicStabilization.byLevel = m_byElectLevel;
	
	m_CcdParamEx.struCorridorMode.byEnableCorridorMode = m_bChkCorridorMode;
	
	m_CcdParamEx.struSmartIRParam.byMode = m_comboSmartIRMode.GetCurSel();
	m_CcdParamEx.struSmartIRParam.byIRDistance = m_byIRDistance;
	
	m_CcdParamEx.struSmartIRParam.byShortIRDistance = m_byShortIRDistance;
	m_CcdParamEx.struSmartIRParam.byLongIRDistance = m_byLongIRDistance;

	m_CcdParamEx.struPIrisParam.byMode = m_comboPIrisMode.GetCurSel();
	m_CcdParamEx.struPIrisParam.byPIrisAperture = m_byPIrisAperture;

	m_CcdParamEx.byCaptureModeN = m_comboCaptureMode.GetCurSel();
	m_CcdParamEx.byCaptureModeP = m_comboCaptureMode2.GetCurSel();

	
	m_CcdParamEx.struLaserParam.byControlMode = m_cmLaserControlMode.GetCurSel() + 1;
	m_CcdParamEx.struLaserParam.byTriggerMode = m_cmLaserTriggerMode.GetCurSel() + 1;
	m_CcdParamEx.struLaserParam.bySensitivity = m_byLaserSensitivity;
	m_CcdParamEx.struLaserParam.byBrightness = m_byLaserBrightness;
	m_CcdParamEx.struLaserParam.byAngle = m_byLaserAngle;
	m_CcdParamEx.struLaserParam.byLimitBrightness = m_byLaserLimitBrightness;//2014-01-26
	m_CcdParamEx.struLaserParam.byEnabled = m_bChkLaserEnabled;
	m_CcdParamEx.struLaserParam.byIllumination = m_byIllumination;
	m_CcdParamEx.struLaserParam.byLightAngle = m_byLightAngle;

    m_CcdParamEx.struFFCParam.byMode = m_comFFCMode.GetCurSel() + 1;
    m_CcdParamEx.struFFCParam.wCompensateTime = m_dwFFCTime;
    
    m_CcdParamEx.struDDEParam.byMode = m_comDDEMode.GetCurSel() + 1;
    m_CcdParamEx.struDDEParam.byNormalLevel = m_byDDELevel;
    m_CcdParamEx.struDDEParam.byExpertLevel = m_byDDEExpertLevel;
    
    m_CcdParamEx.struAGCParam.bySceneType = m_comAGCType.GetCurSel() + 1;
    m_CcdParamEx.struAGCParam.byLightLevel = m_byAGCLightLevel;
    m_CcdParamEx.struAGCParam.byGainLevel = m_byAGCGainLevel;
    
    m_CcdParamEx.byLensDistortionCorrection = m_bLensDistortionCorrection;

    if (m_comDistortionCorrectionLevel.GetCurSel()==4)
    {
        m_CcdParamEx.byDistortionCorrectionLevel =255;
    } 
    else
    {
        m_CcdParamEx.byDistortionCorrectionLevel = m_comDistortionCorrectionLevel.GetCurSel();
    }
    
    m_CcdParamEx.byCalibrationAccurateLevel = m_byCalibrationAccurateLevel;
    m_CcdParamEx.byZoomedInDistantViewLevel = m_byZoomedInDistantViewLevel;
    m_CcdParamEx.byHorizontalFOV = m_byHorizontalFOV;
    m_CcdParamEx.byVerticalFOV = m_byVerticalFOV;
    

	m_CcdParamEx.struOpticalDehaze.byEnable = m_bOpticalDehaze;

    m_CcdParamEx.struThermAGC.byMode = m_comThermometryAGCType.GetCurSel();
    m_CcdParamEx.struThermAGC.iHighTemperature = m_iHighTemp;
    m_CcdParamEx.struThermAGC.iLowTemperature = m_iLowTemp;

    m_CcdParamEx.byFusionMode = m_comboFusionMode.GetCurSel();

    m_CcdParamEx.byBrightnessSuddenChangeSuppression = m_byBrightnessSuddenChangeSuppression;

	if (m_bChkISPSet)
	{
		m_struISPCameraParamCfg.dwSize = sizeof(m_struISPCameraParamCfg);
		memcpy(&m_struISPCameraParamCfg.struSelfAdaptiveParam, &m_CcdParamEx, sizeof(m_CcdParamEx));
		if (!NET_DVR_SetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_SET_ISP_CAMERAPARAMCFG, m_lChannel, \
			&m_struISPCameraParamCfg, sizeof(m_struISPCameraParamCfg)))
		{
			g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_FAIL_T, "Error Code = %d ;NET_DVR_SET_ISP_CAMERAPARAMCFG", NET_DVR_GetLastError());
		}
		else
		{
			g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_SUCC_T, "Error Code = %d ;NET_DVR_SET_ISP_CAMERAPARAMCFG", NET_DVR_GetLastError());
		}
	} 
	else
	{
		if (!NET_DVR_SetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_SET_CCDPARAMCFG_EX, m_lChannel, &m_CcdParamEx, sizeof(m_CcdParamEx)))
		{
			g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_FAIL_T, "Error Code = %d ;NET_DVR_SET_CCDPARAMCFG_EX", NET_DVR_GetLastError());
		}
		else
		{
			g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_SUCC_T, "Error Code = %d ;NET_DVR_SET_CCDPARAMCFG_EX", NET_DVR_GetLastError());
		}
	}
	return;
}

void CDlgCcdParam::OnSelchangeComboAGCTempMode()
{
    if (m_comThermometryAGCType.GetCurSel() == 0)
    {
        m_comAGCType.EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_AGC_LIGHTLEVEL)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_AGC_GAINLEVEL)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_AGC_HIGH_TEMP)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_AGC_LOW_TEMP)->EnableWindow(FALSE);
    }
    else if (m_comThermometryAGCType.GetCurSel() == 1)
    {
        m_comAGCType.EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_AGC_LIGHTLEVEL)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_AGC_GAINLEVEL)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_AGC_HIGH_TEMP)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_AGC_LOW_TEMP)->EnableWindow(FALSE);
    }
    else if (m_comThermometryAGCType.GetCurSel() == 2)
    {
        m_comAGCType.EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_AGC_LIGHTLEVEL)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_AGC_GAINLEVEL)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_AGC_HIGH_TEMP)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_AGC_LOW_TEMP)->EnableWindow(TRUE);
    }
}

void CDlgCcdParam::OnSelchangeComboIrismode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_ctrlIrisMode.GetCurSel() == 2 || m_ctrlIrisMode.GetCurSel() == 3 || m_ctrlIrisMode.GetCurSel() == 4 || m_ctrlIrisMode.GetCurSel() == 5)
	{
		GetDlgItem(IDC_COMBO_PIRIS_MODE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PIRIS_APERTURE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PIRIS_APERTURE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PIRIS_MODE)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_COMBO_PIRIS_MODE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PIRIS_APERTURE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PIRIS_APERTURE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PIRIS_MODE)->ShowWindow(SW_HIDE);
	}
	UpdateData(FALSE);
}

void CDlgCcdParam::OnSelchangeComboPirisMode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_comboPIrisMode.GetCurSel() != 0)
	{
		GetDlgItem(IDC_STATIC_PIRIS_APERTURE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PIRIS_APERTURE)->EnableWindow(TRUE);
	} 
	else
	{
		GetDlgItem(IDC_STATIC_PIRIS_APERTURE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PIRIS_APERTURE)->EnableWindow(FALSE);		
	}
	UpdateData(FALSE);
}

void CDlgCcdParam::OnSelchangeComboSmartirMode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_comboSmartIRMode.GetCurSel() != 0)
	{
		GetDlgItem(IDC_STATIC_IR_DISTANCE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_IRDISTANCE)->EnableWindow(TRUE);
	} 
	else
	{
		GetDlgItem(IDC_STATIC_IR_DISTANCE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_IRDISTANCE)->EnableWindow(FALSE);		
	}
	UpdateData(FALSE);
}

void CDlgCcdParam::OnBtnIspParamset() 
{
	// TODO: Add your control notification handler code here
	CDlgISPParamCfg dlg;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.m_lServerID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	dlg.m_pstruISPCameraParamcfg = &m_struISPCameraParamCfg;
	dlg.DoModal();
}

void CDlgCcdParam::OnBtnSignallightsync() 
{
	// TODO: Add your control notification handler code here
	CDlgSignalLightSync dlg;
	dlg.m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	
	dlg.DoModal();
}


void CDlgCcdParam::OnBtnEzvizAccesscfg() 
{
	// TODO: Add your control notification handler code here
	CDlgEZVIZAccessCfg dlg;
	dlg.m_lUserID = dlg.m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	dlg.m_iDevIndex = m_iDeviceIndex;
	dlg.DoModal();
}

void CDlgCcdParam::OnBtnIOoutCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgIOOutCfg dlg;
	dlg.m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.DoModal();
}

void CDlgCcdParam::OnBtnDpc() 
{
	// TODO: Add your control notification handler code here
    CDlgDPCCfg dlg;
    dlg.m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
    dlg.m_iDevIndex = m_iDeviceIndex;
	dlg.m_lChannel = m_lChannel;
	dlg.DoModal();
}

void CDlgCcdParam::OnBtnFfcManual() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_FFC_MANUAL_INFO struFFCManualInfo = {0};
    struFFCManualInfo.dwSize = sizeof(NET_DVR_FFC_MANUAL_INFO);
    struFFCManualInfo.dwChannel = m_lChannel;
    // TODO: Add your control notification handler code here
    if (NET_DVR_RemoteControl(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_FFC_MANUAL_CTRL, &struFFCManualInfo, sizeof(NET_DVR_FFC_MANUAL_INFO)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_FFC_MANUAL_CTRL");
        return; 
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_FFC_MANUAL_CTRL");
        return; 
	} 
}

void CDlgCcdParam::OnBtnFfcBackcomp() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_FFC_BACKCOMP_INFO struFFCBackCompInfo = {0};
    struFFCBackCompInfo.dwSize = sizeof(NET_DVR_FFC_BACKCOMP_INFO);
    struFFCBackCompInfo.dwChannel = m_lChannel;
    // TODO: Add your control notification handler code here
    if (NET_DVR_RemoteControl(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_FFC_BACKCOMP_CTRL, &struFFCBackCompInfo, sizeof(NET_DVR_FFC_BACKCOMP_INFO)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_FFC_BACKCOMP_CTRL");
        return; 
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_FFC_BACKCOMP_CTRL");
        return; 
    } 
}

void CDlgCcdParam::OnSelchangeComboFfcMode() 
{
	// TODO: Add your control notification handler code here
    if (0 == m_comFFCMode.GetCurSel())
    {
        GetDlgItem(IDC_EDIT_FFC_TIME)->EnableWindow(TRUE);
    }
    else
    {
        GetDlgItem(IDC_EDIT_FFC_TIME)->EnableWindow(FALSE);
	}
}

void CDlgCcdParam::OnSelchangeComboDdeMode() 
{
	// TODO: Add your control notification handler code here
    if (1 == m_comDDEMode.GetCurSel())
    {
        GetDlgItem(IDC_EDIT_DDE_LEVEL)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_DDE_EXPERT_LEVEL)->EnableWindow(FALSE);
    }
    else if (2 == m_comDDEMode.GetCurSel())
    {
        GetDlgItem(IDC_EDIT_DDE_LEVEL)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_DDE_EXPERT_LEVEL)->EnableWindow(TRUE);
    }
    else
    {
        GetDlgItem(IDC_EDIT_DDE_LEVEL)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_DDE_EXPERT_LEVEL)->EnableWindow(FALSE);
    }
}

void CDlgCcdParam::OnSelchangeComboAgcType() 
{
	// TODO: Add your control notification handler code here
    if (2 == m_comAGCType.GetCurSel())
    {
        GetDlgItem(IDC_EDIT_AGC_LIGHTLEVEL)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_AGC_GAINLEVEL)->EnableWindow(TRUE);
    }
    else
    {
        GetDlgItem(IDC_EDIT_AGC_LIGHTLEVEL)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_AGC_GAINLEVEL)->EnableWindow(FALSE);
	}
}

void CDlgCcdParam::OnBtnFocusingPositionState() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
	NET_DVR_FOCUSING_POSITION_STATE struFocusingPositionState = {0};
    struFocusingPositionState.dwSize = sizeof(struFocusingPositionState);
    if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_GET_FOCUSING_POSITION_STATE, m_lChannel, \
		&struFocusingPositionState, sizeof(struFocusingPositionState), &dwReturn))
    {
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_GET_FOCUSING_POSITION_STATE");
    }
	else
	{
        g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_GET_FOCUSING_POSITION_STATE");
	}
	m_comboFocusingPositionState.SetCurSel(struFocusingPositionState.byState);
	UpdateData(FALSE);
}

void CDlgCcdParam::OnBtnSupplementlight() 
{
	// TODO: Add your control notification handler code here
    CDlgBuiltinSupplementLight dlg;
    dlg.m_lServerID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.m_lChannel = m_lChannel;
	dlg.DoModal();
}
