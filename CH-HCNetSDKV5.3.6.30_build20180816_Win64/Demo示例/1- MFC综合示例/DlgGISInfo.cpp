// DlgGISInfo.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgGISInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGISInfo dialog


CDlgGISInfo::CDlgGISInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGISInfo::IDD, pParent)
    , m_PTZEXPan(0)
    , m_PTZEXTilt(0)
    , m_PTZEXZoom(0)
    , m_MinHorizontalValue(0)
    , MaxHorizontalValue(0)
    , m_MinVerticalValue(0)
    , m_MaxVerticalValue(0)
    , m_PTZPosExEnable(FALSE)
    , m_PTZEXForcus(0)
{
	//{{AFX_DATA_INIT(CDlgGISInfo)
	m_dwLatitude = 0;
	m_dwLongitude = 0;
	m_dwTimeOut = 0;
	m_fAzimuth = 0.0f;
	m_fFold = 0.0f;
	m_fHorizontalValue = 0.0f;
	m_fHorWidth = 0.0f;
	m_dwLatitudeGIS = 0;
	m_dwLongitudeGIS = 0;
	m_fMaxViewRadius = 0.0f;
	m_fVerticalValue = 0.0f;
	m_fVerWidth = 0.0f;
	m_fVisibleRadius = 0.0f;
	m_chkUploadEnabled = FALSE;
	m_chkVoiceWarning = FALSE;
	m_chkSatelliteTimeEnable = FALSE;
	m_byLatitudeDegree = 0;
	m_byLatitudeDegree2 = 0;
	m_byLatitudeMinute = 0;
	m_byLatitudeMinute2 = 0;
	m_fLatitudeSec = 0.0f;
	m_fLatitudeSec2 = 0.0f;
	m_byLongitudeDegree = 0;
	m_byLongitudeDegree2 = 0;
	m_byLongitudeMinute = 0;
	m_byLongitudeMinute2 = 0;
	m_fLongitudeSec = 0.0f;
	m_fLongitudeSec2 = 0.0f;
	m_bChkCentEnable = FALSE;
	m_fPanPos = 0.0f;
	m_fTiltPos = 0.0f;
	m_fZoomPos = 0.0f;
	m_fDegree = 0.0f;
	m_iAzimuth = 0;
	m_iTimeInterval = 0;
	m_bStreamEncryptionEnable = FALSE;
	m_byGPSLatitudeDegree = 0;
	m_byGPSLatitudeMinute = 0;
	m_fGPSLatitudeSec = 0.0f;
	m_byGPSLongitudeDegree = 0;
	m_byGPSLongitudeMinute = 0;
	m_fGPSLongitudeSec = 0.0f;
	m_chkStart = FALSE;
	//}}AFX_DATA_INIT
    m_lChannel = -1;
    m_lUser = -1;
    m_iDeviceIndex = -1;
    m_bySensitivity11 = 0;
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
}


void CDlgGISInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgGISInfo)
    DDX_Control(pDX, IDC_COMBO_POSITION_WORKMODE, m_comPositionWorkMode);
    DDX_Control(pDX, IDC_COMBO_GPS_WORKMODE, m_comGPSWorkMode);
    DDX_Control(pDX, IDC_COMBO_GPS_LONGITUDE_TYPE, m_comGPSLongitudeType);
    DDX_Control(pDX, IDC_COMBO_GPS_LATITUDE_TYPE, m_comGPSLatitudeType);
    DDX_Control(pDX, IDC_COMBO_LONGITUDE_TYPE2, m_comLongitudeType2);
    DDX_Control(pDX, IDC_COMBO_LATITUDE_TYPE2, m_comLatitudeType2);
    DDX_Control(pDX, IDC_COMBO_LONGITUDE_TYPE, m_comLongitudeType);
    DDX_Control(pDX, IDC_COMBO_LATITUDE_TYPE, m_comLatitudeType);
    DDX_Control(pDX, IDC_COMBO_SENSOR_TYPE, m_comSensorType);
    DDX_Control(pDX, IDC_COMBO_CONTROL_TYPE, m_comControlType);
    DDX_Text(pDX, IDC_EDIT_LATITUDE, m_dwLatitude);
    DDX_Text(pDX, IDC_EDIT_LONGITUDE, m_dwLongitude);
    DDX_Text(pDX, IDC_EDIT_TIMEOUT, m_dwTimeOut);
    DDX_Text(pDX, IDC_EDIT_AMZIMUTH, m_fAzimuth);
    DDX_Text(pDX, IDC_EDIT_FOLD, m_fFold);
    DDX_Text(pDX, IDC_EDIT_HORIZONTAL_VALUE, m_fHorizontalValue);
    DDX_Text(pDX, IDC_EDIT_HORWIDTH, m_fHorWidth);
    DDX_Text(pDX, IDC_EDIT_LATITUDE_GIS, m_dwLatitudeGIS);
    DDX_Text(pDX, IDC_EDIT_LONGITUDE_GIS, m_dwLongitudeGIS);
    DDX_Text(pDX, IDC_EDIT_MAX_VIEW_RADIUS, m_fMaxViewRadius);
    DDX_Text(pDX, IDC_EDIT_VERTICAL_VALUE, m_fVerticalValue);
    DDX_Text(pDX, IDC_EDIT_VERWIDTH, m_fVerWidth);
    DDX_Text(pDX, IDC_EDIT_VISIBLE_RADIUS, m_fVisibleRadius);
    DDX_Check(pDX, IDC_CHK_UPLOADENABLED, m_chkUploadEnabled);
    DDX_Check(pDX, IDC_CHK_VOICEWARNING, m_chkVoiceWarning);
    DDX_Check(pDX, IDC_CHK_SATELLITETIME_ENABLE, m_chkSatelliteTimeEnable);
    DDX_Text(pDX, IDC_EDIT_LATITUDE_DEGREE, m_byLatitudeDegree);
    DDX_Text(pDX, IDC_EDIT_LATITUDE_DEGREE2, m_byLatitudeDegree2);
    DDX_Text(pDX, IDC_EDIT_LATITUDE_MINUTE, m_byLatitudeMinute);
    DDX_Text(pDX, IDC_EDIT_LATITUDE_MINUTE2, m_byLatitudeMinute2);
    DDX_Text(pDX, IDC_EDIT_SENSITIVITY1, m_bySensitivity11);
    DDX_Text(pDX, IDC_EDIT_LATITUDE_SEC, m_fLatitudeSec);
    DDX_Text(pDX, IDC_EDIT_LATITUDE_SEC2, m_fLatitudeSec2);
    DDX_Text(pDX, IDC_EDIT_LONGITUDE_DEGREE, m_byLongitudeDegree);
    DDX_Text(pDX, IDC_EDIT_LONGITUDE_DEGREE2, m_byLongitudeDegree2);
    DDX_Text(pDX, IDC_EDIT_LONGITUDE_MINUTE3, m_byLongitudeMinute);
    DDX_Text(pDX, IDC_EDIT_LONGITUDE_MINUTE2, m_byLongitudeMinute2);
    DDX_Text(pDX, IDC_EDIT_LONGITUDE_SEC, m_fLongitudeSec);
    DDX_Text(pDX, IDC_EDIT_LONGITUDE_SEC2, m_fLongitudeSec2);
    DDX_Check(pDX, IDC_CHK_CENTRALIZEDCTRL_ENABLE, m_bChkCentEnable);
    DDX_Text(pDX, IDC_EDIT_PANPOS, m_fPanPos);
    DDX_Text(pDX, IDC_EDIT_TILTPOS, m_fTiltPos);
    DDX_Text(pDX, IDC_EDIT_ZOOMPOS, m_fZoomPos);
    DDX_Text(pDX, IDC_EDIT_DEGREE, m_fDegree);
    DDX_Text(pDX, IDC_EDIT_AZIMUTH, m_iAzimuth);
    DDX_Text(pDX, IDC_EDIT_TIMEINTERVAL, m_iTimeInterval);
    DDX_Check(pDX, IDC_CHK_STREAMENCRYPTION_ENABLE, m_bStreamEncryptionEnable);
    DDX_Text(pDX, IDC_EDIT_GPS_LATITUDE_DEGREE, m_byGPSLatitudeDegree);
    DDX_Text(pDX, IDC_EDIT_GPS_LATITUDE_MINUTE, m_byGPSLatitudeMinute);
    DDX_Text(pDX, IDC_EDIT_GPS_LATITUDE_SEC, m_fGPSLatitudeSec);
    DDX_Text(pDX, IDC_EDIT_GPS_LONGITUDE_DEGREE, m_byGPSLongitudeDegree);
    DDX_Text(pDX, IDC_EDIT_GPS_LONGITUDE_MINUTE, m_byGPSLongitudeMinute);
    DDX_Text(pDX, IDC_EDIT_GPS_LONGITUDE_SEC, m_fGPSLongitudeSec);
    DDX_Check(pDX, IDC_CHK_START, m_chkStart);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_PTZEX_Pan, m_PTZEXPan);
    DDX_Text(pDX, IDC_EDIT_PTZEX_Tilt, m_PTZEXTilt);
    DDX_Text(pDX, IDC_EDIT_PTZEXZoom, m_PTZEXZoom);
    DDX_Text(pDX, IDC_EDIT_MinHorizontalValue, m_MinHorizontalValue);
    DDX_Text(pDX, IDC_EDIT_MaxHorizontalValue, MaxHorizontalValue);
    DDX_Text(pDX, IDC_EDIT_MinVerticalValue, m_MinVerticalValue);
    DDX_Text(pDX, IDC_EDIT_MaxVerticalValue, m_MaxVerticalValue);
    DDX_Check(pDX, IDC_CHECK_PTZPosExEnable, m_PTZPosExEnable);
    DDX_Text(pDX, IDC_EDITPTZEX_Forcus, m_PTZEXForcus);
}


BEGIN_MESSAGE_MAP(CDlgGISInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgGISInfo)
	ON_BN_CLICKED(IDC_BTN_SET_CENTRALIZEDCTRL, OnBtnSetCentralizedctrl)
	ON_BN_CLICKED(IDC_BTN_GET_CENTRALIZEDCTRL, OnBtnGetCentralizedctrl)
	ON_BN_CLICKED(IDC_BTN_GET_GISINFO, OnBtnGetGisinfo)
	ON_BN_CLICKED(IDC_BTN_SET_VANDALPROOFALARM, OnBtnSetVandalproofalarm)
	ON_BN_CLICKED(IDC_BTN_GET_VANDALPROOFALARM, OnBtnGetVandalproofalarm)
	ON_BN_CLICKED(IDC_BTN_COMPASS_CALIBRATE_CTRL, OnBtnCompassCalibrateCtrl)
	ON_BN_CLICKED(IDC_BTN_COMPASS_NORTH_CTRL, OnBtnCompassNorthCtrl)
	ON_BN_CLICKED(IDC_BTN_SET_SATELLITETIME, OnBtnSetSatellitetime)
	ON_BN_CLICKED(IDC_BTN_GET_SATELLITETIME, OnBtnGetSatellitetime)
	ON_BN_CLICKED(IDC_BTN_GETAZIMUTH, OnBtnGetazimuth)
	ON_BN_CLICKED(IDC_BTN_SET_STREAMENCRYPTION, OnBtnSetStreamencryption)
	ON_BN_CLICKED(IDC_BTN_GET_STREAMENCRYPTION, OnBtnGetStreamencryption)
	ON_BN_CLICKED(IDC_BTN_GET_GPS, OnBtnGetGps)
	ON_BN_CLICKED(IDC_BTN_SET_GPS, OnBtnSetGps)
	ON_CBN_SELCHANGE(IDC_COMBO_POSITION_WORKMODE, OnSelchangeComboPositionWorkmode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGISInfo message handlers

void CDlgGISInfo::OnBtnSetCentralizedctrl() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char szLan[512] = {0};
    NET_DVR_CENTRALIZEDCTRL_CFG struCentCtrl = {0};
    
    struCentCtrl.byEnable = m_bChkCentEnable;

    struCentCtrl.byLatitudeType = m_comLatitudeType.GetCurSel();
    struCentCtrl.byLongitudeType = m_comLongitudeType.GetCurSel();

    struCentCtrl.struLatitude.fSec = m_fLatitudeSec;
    struCentCtrl.struLatitude.byDegree = m_byLatitudeDegree;
    struCentCtrl.struLatitude.byMinute = m_byLatitudeMinute;

    struCentCtrl.struLongitude.fSec = m_fLongitudeSec;
    struCentCtrl.struLongitude.byDegree = m_byLongitudeDegree;
    struCentCtrl.struLongitude.byMinute = m_byLongitudeMinute;

    //struCentCtrl.dwLongitude = m_dwLongitude;
    //struCentCtrl.dwLatitude = m_dwLatitude;
    struCentCtrl.dwTimeOut = m_dwTimeOut;
    struCentCtrl.byControlType = m_comControlType.GetCurSel();
    struCentCtrl.dwSize = sizeof(struCentCtrl);
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struCentCtrl;
    struCfg.dwInSize = sizeof(struCentCtrl);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lUser, NET_DVR_SET_CENTRALIZEDCTRL, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_CENTRALIZEDCTRL");
        sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_CENTRALIZEDCTRL");
    }
}

void CDlgGISInfo::OnBtnGetCentralizedctrl() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_CENTRALIZEDCTRL_CFG struCentCtrl = {0};

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &struCentCtrl;
    struCfg.dwOutSize = sizeof(struCentCtrl);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lUser, NET_DVR_GET_CENTRALIZEDCTRL, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_CENTRALIZEDCTRL");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_CENTRALIZEDCTRL");
    }
    
    m_bChkCentEnable = struCentCtrl.byEnable;

    m_comLatitudeType.SetCurSel(struCentCtrl.byLatitudeType);
    m_comLongitudeType.SetCurSel(struCentCtrl.byLongitudeType);
    
    m_fLatitudeSec = struCentCtrl.struLatitude.fSec;
    m_byLatitudeDegree = struCentCtrl.struLatitude.byDegree;
    m_byLatitudeMinute = struCentCtrl.struLatitude.byMinute;
    
    m_fLongitudeSec = struCentCtrl.struLongitude.fSec;
    m_byLongitudeDegree = struCentCtrl.struLongitude.byDegree;
    m_byLongitudeMinute = struCentCtrl.struLongitude.byMinute;

 //   m_dwLongitude = struCentCtrl.dwLongitude;
 //   m_dwLatitude = struCentCtrl.dwLatitude;
    m_dwTimeOut = struCentCtrl.dwTimeOut;
    m_comControlType.SetCurSel(struCentCtrl.byControlType);
    
    UpdateData(FALSE);
}

void CDlgGISInfo::OnBtnGetGisinfo() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_GIS_INFO struGISInfo = {0};
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &struGISInfo;
    struCfg.dwOutSize = sizeof(struGISInfo);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lUser, NET_DVR_GET_GISINFO, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_GISINFO");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_GISINFO");
    }
    
    m_fAzimuth = struGISInfo.fAzimuth;
    m_comLatitudeType2.SetCurSel(struGISInfo.byLatitudeType);
    m_comLongitudeType2.SetCurSel(struGISInfo.byLongitudeType);
    
    m_fLatitudeSec2 = struGISInfo.struLatitude.fSec;
    m_byLatitudeDegree2 = struGISInfo.struLatitude.byDegree;
    m_byLatitudeMinute2 = struGISInfo.struLatitude.byMinute;
    
    m_fLongitudeSec2 = struGISInfo.struLongitude.fSec;
    m_byLongitudeDegree2 = struGISInfo.struLongitude.byDegree;
    m_byLongitudeMinute2 = struGISInfo.struLongitude.byMinute;
   // m_dwLongitudeGIS = struGISInfo.dwLongitude;
   // m_dwLatitudeGIS = struGISInfo.dwLatitude;
    m_fHorizontalValue = struGISInfo.fHorizontalValue;
    m_fVerticalValue = struGISInfo.fVerticalValue;
    m_fVisibleRadius = struGISInfo.fVisibleRadius;
    m_fMaxViewRadius = struGISInfo.fMaxViewRadius;
    m_fPanPos = struGISInfo.struPtzPos.fPanPos;
    m_fTiltPos = struGISInfo.struPtzPos.fTiltPos;
    m_fZoomPos = struGISInfo.struPtzPos.fZoomPos;

    m_comSensorType.SetCurSel(struGISInfo.struSensorParam.bySensorType);
    m_fHorWidth = struGISInfo.struSensorParam.fHorWidth;
    m_fVerWidth = struGISInfo.struSensorParam.fVerWidth;
    m_fFold = struGISInfo.struSensorParam.fFold;
    
    m_PTZPosExEnable = struGISInfo.byPTZPosExEnable;

    m_PTZEXPan = struGISInfo.struPtzPosEx.fPan;
    m_PTZEXTilt = struGISInfo.struPtzPosEx.fTilt;
    m_PTZEXZoom = struGISInfo.struPtzPosEx.fZoom;
    m_PTZEXForcus = struGISInfo.struPtzPosEx.dwFocus;
    m_MinHorizontalValue = struGISInfo.fMinHorizontalValue;
    MaxHorizontalValue = struGISInfo.fMaxHorizontalValue;

    m_MinVerticalValue = struGISInfo.fMinVerticalValue;
    m_MaxVerticalValue = struGISInfo.fMaxVerticalValue;

    UpdateData(FALSE);
}

void CDlgGISInfo::OnBtnSetVandalproofalarm() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char szLan[512] = {0};
    NET_DVR_VANDALPROOFALARM_CFG struVandalproof = {0};
    
    struVandalproof.byUploadEnabled = m_chkUploadEnabled;
    struVandalproof.byVoiceWarningEnabled = m_chkVoiceWarning;
    struVandalproof.bySensitivity = m_bySensitivity11;
    struVandalproof.byEnable = m_chkStart;
    struVandalproof.dwSize = sizeof(struVandalproof);
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struVandalproof;
    struCfg.dwInSize = sizeof(struVandalproof);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lUser, NET_DVR_SET_VANDALPROOFALARM, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_VANDALPROOFALARM");
        sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_VANDALPROOFALARM");
    }
}

void CDlgGISInfo::OnBtnGetVandalproofalarm() 
{
	// TODO: Add your control notification handler code here
    char szLan[512] = {0};
    NET_DVR_VANDALPROOFALARM_CFG struVandalproof = {0};
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &struVandalproof;
    struCfg.dwOutSize = sizeof(struVandalproof);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lUser, NET_DVR_GET_VANDALPROOFALARM, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_VANDALPROOFALARM");
        sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_VANDALPROOFALARM");
    }
    
    m_chkUploadEnabled = struVandalproof.byUploadEnabled;
    m_chkVoiceWarning = struVandalproof.byVoiceWarningEnabled;
    m_bySensitivity11 = struVandalproof.bySensitivity;
    m_chkStart = struVandalproof.byEnable;

    UpdateData(FALSE);
}

void CDlgGISInfo::OnBtnCompassCalibrateCtrl() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char szLan[512] = {0};
    NET_DVR_COMPASS_COND m_struComassCond = {0};
    m_struComassCond.dwSize = sizeof(NET_DVR_COMPASS_COND);
    m_struComassCond.dwChannel = m_lChannel;
        
    NET_DVR_STD_CONTROL struControl = {0};
    struControl.lpCondBuffer = &m_struComassCond;
    struControl.dwCondSize = sizeof(m_struComassCond);
    
    memset(m_szStatusBuf, 0, 1024);
    struControl.lpStatusBuffer = m_szStatusBuf;
    struControl.dwStatusSize = 1024;
    
    if(!NET_DVR_STDControl(m_lUser, NET_DVR_COMPASS_CALIBRATE_CTRL, &struControl))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_COMPASS_CALIBRATE_CTRL");
        sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_COMPASS_CALIBRATE_CTRL");
    }
}

void CDlgGISInfo::OnBtnCompassNorthCtrl() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char szLan[512] = {0};
    NET_DVR_COMPASS_COND m_struComassCond = {0};
    m_struComassCond.dwSize = sizeof(NET_DVR_COMPASS_COND);
    m_struComassCond.dwChannel = m_lChannel;
    
    NET_DVR_STD_CONTROL struControl = {0};
    struControl.lpCondBuffer = &m_struComassCond;
    struControl.dwCondSize = sizeof(m_struComassCond);
    
    memset(m_szStatusBuf, 0, 1024);
    struControl.lpStatusBuffer = m_szStatusBuf;
    struControl.dwStatusSize = 1024;
    
    if(!NET_DVR_STDControl(m_lUser, NET_DVR_COMPASS_NORTH_CTRL, &struControl))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_COMPASS_NORTH_CTRL");
        sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_COMPASS_NORTH_CTRL");
    }
	
}

void CDlgGISInfo::OnBtnSetSatellitetime() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char szLan[512] = {0};
    DWORD dwReturned = 0;
    NET_DVR_SATELLITETIME_CFG struSatellitetimeTime = {0};
    struSatellitetimeTime.dwSize = sizeof(NET_DVR_SATELLITETIME_CFG);
    struSatellitetimeTime.byEnable = m_chkSatelliteTimeEnable;
    struSatellitetimeTime.wTimeInterval = m_iTimeInterval;
    if (!NET_DVR_SetDVRConfig(m_lUser, NET_DVR_SET_SATELLITETIME, m_lChannel, &struSatellitetimeTime, sizeof(NET_DVR_SATELLITETIME_CFG)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SATELLITETIME");
        sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_SATELLITETIME");
    }

}

void CDlgGISInfo::OnBtnGetSatellitetime() 
{
	// TODO: Add your control notification handler code here
    char szLan[512] = {0};
    DWORD dwReturned = 0;
    NET_DVR_SATELLITETIME_CFG struSatellitetimeTime = {0};
    if (!NET_DVR_GetDVRConfig(m_lUser, NET_DVR_GET_SATELLITETIME, m_lChannel, &struSatellitetimeTime, sizeof(NET_DVR_SATELLITETIME_CFG), &dwReturned))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SATELLITETIME");
        sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SATELLITETIME");
    }
    
    m_chkSatelliteTimeEnable = struSatellitetimeTime.byEnable;
    m_iTimeInterval = struSatellitetimeTime.wTimeInterval;
	UpdateData(FALSE);
}

void CDlgGISInfo::OnBtnGetazimuth() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_AZIMUTHINFO struAzimuthInfo = {0};

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &struAzimuthInfo;
    struCfg.dwOutSize = sizeof(struAzimuthInfo);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if(!NET_DVR_GetSTDConfig(m_lUser, NET_DVR_GET_AZIMUTHINFO, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_AZIMUTHINFO");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_AZIMUTHINFO");

        m_fDegree = struAzimuthInfo.fDegree;
        m_iAzimuth = struAzimuthInfo.byAzimuth;
    }
    UpdateData(FALSE);
}

void CDlgGISInfo::OnBtnSetStreamencryption() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	char szLan[512] = {0};
    NET_DVR_STREAMENCRYPTION_COND struStreamEncryptionCond = {0};
	struStreamEncryptionCond.dwSize = sizeof(NET_DVR_STREAMENCRYPTION_COND);
	struStreamEncryptionCond.dwChan = m_lChannel;
	
	NET_DVR_STREAMENCRYPTION_CFG struStreamEncryption = {0};

    struStreamEncryption.dwSize = sizeof(NET_DVR_STREAMENCRYPTION_CFG);
    struStreamEncryption.byEnable = m_bStreamEncryptionEnable;

 
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &struStreamEncryptionCond;
    struCfg.dwCondSize = sizeof(NET_DVR_STREAMENCRYPTION_COND);
    struCfg.lpInBuffer = &struStreamEncryption;
    struCfg.dwInSize = sizeof(struStreamEncryption);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lUser, NET_DVR_SET_STREAMENCRYPTION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_STREAMENCRYPTION");
        sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_STREAMENCRYPTION");
    }
}

void CDlgGISInfo::OnBtnGetStreamencryption() 
{
	// TODO: Add your control notification handler code here

	char szLan[512] = {0};
    NET_DVR_STREAMENCRYPTION_COND struStreamEncryptionCond = {0};
	struStreamEncryptionCond.dwSize = sizeof(NET_DVR_STREAMENCRYPTION_COND);
	struStreamEncryptionCond.dwChan = m_lChannel;

	NET_DVR_STREAMENCRYPTION_CFG struStreamEncryption = {0};
	

	
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &struStreamEncryptionCond;
    struCfg.dwCondSize = sizeof(struStreamEncryptionCond);
    struCfg.lpOutBuffer = &struStreamEncryption;
    struCfg.dwOutSize = sizeof(struStreamEncryption);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
	
    if(!NET_DVR_GetSTDConfig(m_lUser, NET_DVR_GET_STREAMENCRYPTION, &struCfg))
    {
		OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_STREAMENCRYPTION");
        sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_STREAMENCRYPTION");
		
        m_bStreamEncryptionEnable = struStreamEncryption.byEnable;

    }
    UpdateData(FALSE);
}


void CDlgGISInfo::OnBtnGetGps() 
{
	// TODO: Add your control notification handler code here
	char szLan[512] = {0};
	
	NET_DVR_REVISE_GPS_CFG struGpsCfg = {0};
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &struGpsCfg;
    struCfg.dwOutSize = sizeof(struGpsCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
	
    if(!NET_DVR_GetSTDConfig(m_lUser, NET_DVR_GET_REVISE_GPS, &struCfg))
    {
		OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_REVISE_GPS");
        sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_REVISE_GPS");
		
		m_comGPSLatitudeType.SetCurSel(struGpsCfg.byLatitudeType);
		m_comGPSLongitudeType.SetCurSel(struGpsCfg.byLongitudeType);
		
		m_fGPSLatitudeSec = struGpsCfg.struLatitude.fSec;
		m_byGPSLatitudeDegree = struGpsCfg.struLatitude.byDegree;
		m_byGPSLatitudeMinute = struGpsCfg.struLatitude.byMinute;
		
		m_fGPSLongitudeSec = struGpsCfg.struLongitude.fSec;
		m_byGPSLongitudeDegree = struGpsCfg.struLongitude.byDegree;
        m_byGPSLongitudeMinute = struGpsCfg.struLongitude.byMinute;

        m_comGPSWorkMode.SetCurSel(struGpsCfg.byMode);
		
    }
    UpdateData(FALSE);
}

void CDlgGISInfo::OnBtnSetGps() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	char szLan[512] = {0};
	
	NET_DVR_REVISE_GPS_CFG struGpsCfg = {0};
	
    struGpsCfg.dwSize = sizeof(NET_DVR_REVISE_GPS_CFG);
	struGpsCfg.byLatitudeType = m_comGPSLatitudeType.GetCurSel();
    struGpsCfg.byLongitudeType = m_comGPSLongitudeType.GetCurSel();
	
    struGpsCfg.struLatitude.fSec = m_fGPSLatitudeSec;
    struGpsCfg.struLatitude.byDegree = m_byGPSLatitudeDegree;
    struGpsCfg.struLatitude.byMinute = m_byGPSLatitudeMinute;
	
    struGpsCfg.struLongitude.fSec = m_fGPSLongitudeSec;
    struGpsCfg.struLongitude.byDegree = m_byGPSLongitudeDegree;
    struGpsCfg.struLongitude.byMinute = m_byGPSLongitudeMinute;
	
	struGpsCfg.byMode = m_comGPSWorkMode.GetCurSel();

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struGpsCfg;
    struCfg.dwInSize = sizeof(struGpsCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lUser, NET_DVR_SET_REVISE_GPS, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_REVISE_GPS");
        sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_REVISE_GPS");
    }
}

void CDlgGISInfo::OnSelchangeComboPositionWorkmode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    char szLan[512] = {0};

    NET_DVR_POSITION_CFG struPosition = {0};
    struPosition.dwSize = sizeof(struPosition);
    struPosition.bySoftWorkMode = m_comPositionWorkMode.GetCurSel();

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struPosition;
    struCfg.dwInSize = sizeof(struPosition);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lUser, NET_DVR_SET_POSITION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_POSITION");
        sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_POSITION");
    } 

}

void CDlgGISInfo::GetPosition() 
{
    // TODO: Add your control notification handler code here
    NET_DVR_POSITION_CFG struPosition = {0};

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &struPosition;
    struCfg.dwOutSize = sizeof(struPosition);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lUser, NET_DVR_GET_POSITION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_POSITION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_POSITION");
    }
    
    m_comPositionWorkMode.SetCurSel(struPosition.bySoftWorkMode);   
    UpdateData(FALSE);
}

BOOL CDlgGISInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetPosition();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
