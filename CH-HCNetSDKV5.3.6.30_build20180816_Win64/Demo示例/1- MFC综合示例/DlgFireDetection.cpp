// DlgFireDetection.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgFireDetection.h"
#include "DrawFun.h"
#include "DlgShipDetection.h"
#include "DlgManualThermCfg.h"
#include "DlgRegionDetectCfg.h"
#include "DlgThremalPipCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFireDetection dialog

#define WM_MSG_ADD_REALTIMEINFO_TOLIST 1001
#define WM_MSG_GET_REALTIMEINFO_FINISH 1002
#define WM_MSG_ADD_THERMOMETRY_TOLIST  1003
#define WM_MSG_GET_THERMOMETRY_FINISH  1004

// void CALLBACK g_fGetThermometryCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
// {
//     CDlgFireDetection* pDlg = (CDlgFireDetection*)pUserData;
//     if (pDlg == NULL)
//     {
//         return;
//     }
//     pDlg->ProcessGetThermometryCallbackData(dwType,lpBuffer,dwBufLen);
// }

// void CDlgFireDetection::ProcessGetThermometryCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
// {
//     CString strItem = "";
//     if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
//     {
//         LPNET_DVR_THERMOMETRIC_INFO lpThermometryInfo =  new NET_DVR_THERMOMETRIC_INFO; 
//         memcpy(lpThermometryInfo, lpBuffer, sizeof(*lpThermometryInfo)); 
//         PostMessage(WM_MSG_ADD_THERMOMETRY_TOLIST, (WPARAM)lpThermometryInfo,0);
//     }
//     else if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
//     {
//         DWORD dwStatus = *(DWORD*)lpBuffer;
//         if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
//         {
//             PostMessage(WM_MSG_GET_THERMOMETRY_FINISH,0,0);
//         }
//         else if ( dwStatus == NET_SDK_CALLBACK_STATUS_FAILED )
//         {
//             DWORD dwErrCode = *(DWORD*)((char *)lpBuffer + 4); 
//             
//             g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_THERMOMETRIC_INFO, Error code %d", dwErrCode);
//         }
//     }
// }

void CALLBACK g_fGetRealtimeThermometryCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CDlgFireDetection* pDlg = (CDlgFireDetection*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
    pDlg->ProcessGetRealtimeThermometryCallbackData(dwType,lpBuffer,dwBufLen);
}

void CDlgFireDetection::ProcessGetRealtimeThermometryCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{
    CString strItem = "";
    if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        LPNET_DVR_THERMOMETRY_UPLOAD lpThermometryInfo =  new NET_DVR_THERMOMETRY_UPLOAD; 
        memcpy(lpThermometryInfo, lpBuffer, sizeof(*lpThermometryInfo)); 
        PostMessage(WM_MSG_ADD_REALTIMEINFO_TOLIST, (WPARAM)lpThermometryInfo,0);
	}
    else if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
        DWORD dwStatus = *(DWORD*)lpBuffer;
        if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            PostMessage(WM_MSG_GET_REALTIMEINFO_FINISH,0,0);
        }
        else if ( dwStatus == NET_SDK_CALLBACK_STATUS_FAILED )
        {
            DWORD dwErrCode = *(DWORD*)((char *)lpBuffer + 4); 
      
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_REALTIME_THERMOMETRY, Error code %d", dwErrCode);
        }
	}
}

LRESULT CDlgFireDetection::OnMsgAddRealtimeCfgToList(WPARAM wParam,LPARAM lParam)
{
    LPNET_DVR_THERMOMETRY_UPLOAD lpThermometryInfo = (LPNET_DVR_THERMOMETRY_UPLOAD)wParam; 

    int iItemCount = m_lstRealtimeThermometry.GetItemCount();
    
	m_lstRealtimeThermometry.InsertItem(iItemCount, "");

    char szStr[512] = {0};

    sprintf(szStr, "%d", lpThermometryInfo->dwRelativeTime);
	m_lstRealtimeThermometry.SetItemText(iItemCount, 0, szStr);

    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%d", lpThermometryInfo->dwAbsTime);
	m_lstRealtimeThermometry.SetItemText(iItemCount, 1, szStr);

    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%s", lpThermometryInfo->szRuleName);
	m_lstRealtimeThermometry.SetItemText(iItemCount, 2, szStr);

    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%d", lpThermometryInfo->byRuleID);
	m_lstRealtimeThermometry.SetItemText(iItemCount, 3, szStr);

    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%d", lpThermometryInfo->wPresetNo);
	m_lstRealtimeThermometry.SetItemText(iItemCount, 4, szStr);

    memset(szStr, 0, sizeof(szStr));
    if (0 == lpThermometryInfo->byRuleCalibType)
    {
        sprintf(szStr, "点测温");
    } 
    else if (1 == lpThermometryInfo->byRuleCalibType)
    {
        sprintf(szStr, "区域测温");
    }
    else if (2 == lpThermometryInfo->byRuleCalibType)
    {
        sprintf(szStr, "线测温");
    }
	m_lstRealtimeThermometry.SetItemText(iItemCount, 5, szStr);

    if (0 == lpThermometryInfo->byRuleCalibType)
    {
        memset(szStr, 0, sizeof(szStr));
        sprintf(szStr, "%f", lpThermometryInfo->struPointThermCfg.fTemperature);
        m_lstRealtimeThermometry.SetItemText(iItemCount, 6, szStr);
        
        memset(szStr, 0, sizeof(szStr));
        sprintf(szStr, "x:%f,y:%f", lpThermometryInfo->struPointThermCfg.struPoint.fX, lpThermometryInfo->struPointThermCfg.struPoint.fY);
        m_lstRealtimeThermometry.SetItemText(iItemCount, 7, szStr);
    } 
    else if (1 == lpThermometryInfo->byRuleCalibType || 2 == lpThermometryInfo->byRuleCalibType)
    {
        memset(szStr, 0, sizeof(szStr));
        sprintf(szStr, "%f", lpThermometryInfo->struLinePolygonThermCfg.fMaxTemperature);
        m_lstRealtimeThermometry.SetItemText(iItemCount, 8, szStr);

        memset(szStr, 0, sizeof(szStr));
        sprintf(szStr, "%f", lpThermometryInfo->struLinePolygonThermCfg.fMinTemperature);
        m_lstRealtimeThermometry.SetItemText(iItemCount, 9, szStr);

        memset(szStr, 0, sizeof(szStr));
        sprintf(szStr, "%f", lpThermometryInfo->struLinePolygonThermCfg.fAverageTemperature);
        m_lstRealtimeThermometry.SetItemText(iItemCount, 10, szStr);

        memset(szStr, 0, sizeof(szStr));
        sprintf(szStr, "%f", lpThermometryInfo->struLinePolygonThermCfg.fTemperatureDiff);
        m_lstRealtimeThermometry.SetItemText(iItemCount, 11, szStr);

        memset(szStr, 0, sizeof(szStr));
        int iPointNum = lpThermometryInfo->struLinePolygonThermCfg.struRegion.dwPointNum;    
        for (int i = 0; i < iPointNum; i++)
        {
            float fX = lpThermometryInfo->struLinePolygonThermCfg.struRegion.struPos[i].fX;
            float fY = lpThermometryInfo->struLinePolygonThermCfg.struRegion.struPos[i].fY;
            sprintf(szStr, "%sX%d:%f,Y%d:%f;", szStr, i+1, fX, i+1, fY); 
        }
        m_lstRealtimeThermometry.SetItemText(iItemCount, 12, szStr);
    }

    memset(szStr, 0, sizeof(szStr));
    if(0 == lpThermometryInfo->byThermometryUnit)
    {
        sprintf(szStr, "摄氏度");
    }
    else if (1 == lpThermometryInfo->byThermometryUnit)
    {
        sprintf(szStr, "华氏度");
    }
    else if (2 == lpThermometryInfo->byThermometryUnit)
    {
        sprintf(szStr, "开尔文");
    }
    m_lstRealtimeThermometry.SetItemText(iItemCount, 13, szStr);

    memset(szStr, 0, sizeof(szStr));
    if(0 == lpThermometryInfo->byDataType)
    {
        sprintf(szStr, "检测中");
    }
    else if (1 == lpThermometryInfo->byDataType)
    {
        sprintf(szStr, "开始");
    }
    else if (2 == lpThermometryInfo->byDataType)
    {
        sprintf(szStr, "结束");
    }
    m_lstRealtimeThermometry.SetItemText(iItemCount, 14, szStr);

    if ((lpThermometryInfo->bySpecialPointThermType >> 0) & 0x01)
    {
        memset(szStr, 0, sizeof(szStr));
        sprintf(szStr, "%0.1f", lpThermometryInfo->fCenterPointTemperature);
        m_lstRealtimeThermometry.SetItemText(iItemCount, 15, szStr);
    }
    if ((lpThermometryInfo->bySpecialPointThermType >> 1) & 0x01)
    {
        memset(szStr, 0, sizeof(szStr));
        sprintf(szStr, "%0.1f", lpThermometryInfo->fHighestPointTemperature);
        m_lstRealtimeThermometry.SetItemText(iItemCount, 16, szStr);
    }
    if ((lpThermometryInfo->bySpecialPointThermType >> 2) & 0x01)
    {
        memset(szStr, 0, sizeof(szStr));
        sprintf(szStr, "%0.1f", lpThermometryInfo->fLowestPointTemperature);
        m_lstRealtimeThermometry.SetItemText(iItemCount, 17, szStr);
    }
    return 0;
    
}

LRESULT CDlgFireDetection::OnMsgRealtimeCfgFinish(WPARAM wParam,LPARAM lParam)
{
    if (m_lRealTimeInfoHandle>0)
    {
        NET_DVR_StopRemoteConfig(m_lRealTimeInfoHandle);
        m_lRealTimeInfoHandle = -1;
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_REALTIME_THERMOMETRY Get finish");
    }
    return 0;
}

// LRESULT CDlgFireDetection::OnMsgAddThermometryCfgToList(WPARAM wParam,LPARAM lParam)
// {
//     LPNET_DVR_THERMOMETRIC_INFO lpThermometryInfo = (LPNET_DVR_THERMOMETRIC_INFO)wParam; 
//     
//     int iItemCount = m_lstRealtimeThermometry.GetItemCount();
//     
// 	m_lstThermometric.InsertItem(iItemCount, "");
// 
//     char szStr[128] = {0};
//     
//     sprintf(szStr, "%d", lpThermometryInfo->dwGrayValue);
// 	m_lstThermometric.SetItemText(iItemCount, 0, szStr);
// 
//     memset(szStr, 0, sizeof(szStr));
//     sprintf(szStr, "%d", lpThermometryInfo->dwCenterPointGrayValue);
// 	m_lstThermometric.SetItemText(iItemCount, 1, szStr);
// 
//     memset(szStr, 0, sizeof(szStr));
//     sprintf(szStr, "%f", lpThermometryInfo->fCavityTemperature);
// 	m_lstThermometric.SetItemText(iItemCount, 2, szStr);
// 
//     memset(szStr, 0, sizeof(szStr));
//     sprintf(szStr, "%f", lpThermometryInfo->fFPATemperature);
// 	m_lstThermometric.SetItemText(iItemCount, 3, szStr);
// 
//     memset(szStr, 0, sizeof(szStr));
//     sprintf(szStr, "%f", lpThermometryInfo->fCenterPointTemperature);
// 	m_lstThermometric.SetItemText(iItemCount, 4, szStr);
// 
//     memset(szStr, 0, sizeof(szStr));
//     sprintf(szStr, "%f", lpThermometryInfo->fEnvironTemperature);
// 	m_lstThermometric.SetItemText(iItemCount, 5, szStr);
// 
//     memset(szStr, 0, sizeof(szStr));
//     sprintf(szStr, "%d", lpThermometryInfo->byTemperatureLevel);
// 	m_lstThermometric.SetItemText(iItemCount, 6, szStr);
// 
//     return 0;
// }

LRESULT CDlgFireDetection::OnMsgThermometryCfgFinish(WPARAM wParam,LPARAM lParam)
{
    if (m_lThermometricHandle>0)
    {
        NET_DVR_StopRemoteConfig(m_lThermometricHandle);
        m_lThermometricHandle = -1;
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_THERMOMETRIC_INFO Get finish");
    }
    return 0;
}

void CALLBACK g_DrawCalibRgn(LONG lRealHandle, HDC hDc, DWORD dwUser)
{  
    CDlgFireDetection* pDlg = (CDlgFireDetection*)dwUser;
    
    if (pDlg != NULL)
    {
        pDlg->DrawRgnFun(hDc);
    }
}

void CDlgFireDetection::DrawRgnFun(HDC hDc)
{
    DRAW_POLYGON_PARAM_EX struPolygonParam;
    DRAW_POLYGON_PARAM_EX struITCPolygonParam;
    DRAW_LINE_PARAM  struLaneLineParam;
    if(m_bThermShow)
    {
        memset(&struPolygonParam,0,sizeof(struPolygonParam));
        struPolygonParam.color = RGB(255, 0, 0);
        memcpy(&struPolygonParam.rcWnd, &m_rcPlayWnd, sizeof(m_rcPlayWnd));
        struPolygonParam.pArryPt = m_struPolyGon.struPos;
        struPolygonParam.dwPtNum = m_struPolyGon.dwPointNum;
        CDrawFun::DrawPolygonEx(hDc, &struPolygonParam);
    }
    
    if(m_bShipsShow)
    {
        memset(&struITCPolygonParam,0,sizeof(struITCPolygonParam));
        struITCPolygonParam.color = RGB(0, 255, 0);
        memcpy(&struITCPolygonParam.rcWnd, &m_rcPlayWnd, sizeof(m_rcPlayWnd));
        struITCPolygonParam.pArryPt = m_struITCPolyGon.struPos;
        struITCPolygonParam.dwPtNum = m_struITCPolyGon.dwPointNum;
        CDrawFun::DrawPolygonEx(hDc, &struITCPolygonParam);

        memset(&struLaneLineParam,0,sizeof(struLaneLineParam));
        struLaneLineParam.color = RGB(0, 0, 255);
        memcpy(&struLaneLineParam.rcWnd, &m_rcPlayWnd, sizeof(m_rcPlayWnd));
        struLaneLineParam.struVcaLine = m_struLine;
        CDrawFun::DrawLine(hDc, &struLaneLineParam);
    }

}

CDlgFireDetection::CDlgFireDetection(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFireDetection::IDD, pParent)
    , m_bManualRangEnable(FALSE)
	, m_bManualDeicingEnable(FALSE)
    , m_byFireZoomLevel(0)
    , mSmokeEnabled(FALSE)
    , mSmokeSensitivity(0)
    , m_fAlarmVal(0)
    , m_fAlertVal(0)
    , m_bShowTempStripEnable(FALSE)
    , m_sShipsAlgName(_T(""))
    , m_sThermAlgName(_T(""))
    , m_csFireAlgName(_T(""))
    , m_iRuleIDCond(0)
    , m_fThernomertryEmissivity(0)
    , m_bFireManualWaitEnabled(FALSE)
    , m_ThermalOpticalTransmittance(0)
    , m_externalOpticsWindowCorrection(0)
    , m_CancelRepeatedAlarmEnabled(FALSE)
    , m_InstallationHeight(0)
    , m_PatrolSensitivity(0)
    , m_DoubleCheckSensitivity(0)
{
	//{{AFX_DATA_INIT(CDlgFireDetection)
	m_bEnable = FALSE;
	m_bFireRegionOverlay = FALSE;
	m_byFireComfirmTime = 0;
	m_bySensitivity = 0;
	m_bEnbaleThermometry = FALSE;
	m_bPictureOverlay = FALSE;
	m_bStreamOverlay = FALSE;
	m_bEnableRule = FALSE;
	m_bChkRegion = FALSE;
	m_dwDistance = 0;
	m_fEmissivity = 0.0f;
	m_fReflectiveTemperature = 0.0f;
	m_byRuleID = 0;
	m_csRuleName = _T("");
	m_bChkAlarmRuleEnable = FALSE;
	m_byThermometryRuleID = 0;
	m_csThermometryRuleName = _T("");
	m_fAlarm = 0.0f;
	m_fAlert = 0.0f;
	m_fThreshold = 0.0f;
	m_bChkDiffComparisonEnable = FALSE;
	m_fTemperatureDiff = 0.0f;
	m_byAlarmID1 = 0;
	m_byAlarmID2 = 0;
	m_byDiffRuleID = 0;
	m_fThermPointX = 0.0f;
	m_fThermPointY = 0.0f;
	m_fCenterPointEmissionRate = 0.0f;
	m_csFilePath = _T("");
	m_bReflectiveEnabled = FALSE;
	m_fThresholdTemperature = 0.0f;
	m_bEnableBareDataOverlay = FALSE;
	m_byInterTimeBareDataOverlay = 3;
	m_bShipsEnable = FALSE;
	m_bShipsFrameOverlayEnabled = FALSE;
	m_bShipsRuleEnable = FALSE;
	m_fLookDownUpAngle = 0.0f;
	m_fHorizontalHeight = 0.0f;
	m_byShipsSensitivity = 0;
	m_bShipsShow = FALSE;
	m_bThermShow = TRUE;
	m_byShipRuleID = 0;
	//}}AFX_DATA_INIT
   // m_lChannel = -1;
   // m_lServerID = -1;
   // m_iDeviceIndex = -1;
    m_lPlayHandle = -1;
    m_nDrawPointNum = 0;
    m_lRealTimeInfoHandle = -1;
    m_lThermometricHandle = -1;
    m_hUpLoadThread = NULL;
    m_lUploadHandle = -1; 
    m_bUpLoading = FALSE;
    m_hDownloadThread = NULL;
    m_bDownLoading = FALSE;
	m_lDownloadHandle = -1;
    m_bDrawEnd = FALSE;
    m_nShipsDrawPointNum = 0;
    m_iHighTemperature = 0;
    m_iLowTemperature = 0;
    m_fThernomertryEmissivity = 0.0f;
    m_byEnviroHumidity = 0;
    m_iEnviroTemperature = 0;
    m_iCorrectionVolume = 0;
    m_bySpecialPointThermType = 0;
    m_bChkCenterSpecialPoint = FALSE;
    m_bChkHighestSpecialPoint = FALSE;
    m_bChkLowestSpecialPoint = FALSE;
    m_bChkReflectiveEnabled = FALSE;
    m_dwDistanceMeter = 0;
    m_fReflectiveTemp = 0.0f;
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    memset(&m_struFireDetection, 0, sizeof(m_struFireDetection));
    memset(&m_struThermometryInfo, 0, sizeof(m_struThermometryInfo));
    memset(&m_struThermometryCond, 0, sizeof(m_struThermometryCond));
    memset(&m_struThermometryAlarmInfo, 0, sizeof(m_struThermometryAlarmInfo));
    memset(&m_struThermometryDiffComparison, 0, sizeof(m_struThermometryDiffComparison));
    memset(&m_struPolyGon, 0, sizeof(m_struPolyGon));
    memset(&m_struShipsDet, 0, sizeof(m_struShipsDet));
    memset(&m_struLine, 0, sizeof(m_struLine));
    memset(&m_struITCPolyGon, 0, sizeof(m_struITCPolyGon));
    
    
}

CDlgFireDetection::~CDlgFireDetection()
{
    StopRealPlay();
    
    if(m_lUploadHandle >= 0)
    {
        NET_DVR_UploadClose(m_lUploadHandle);
    }
    
    if(m_lDownloadHandle >= 0)
    {
        NET_DVR_StopDownload(m_lDownloadHandle);
    }

    if(m_lRealTimeInfoHandle >= 0)
    {
         NET_DVR_StopRemoteConfig(m_lRealTimeInfoHandle);
         m_lRealTimeInfoHandle = -1;
    }
}

void CDlgFireDetection::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgFireDetection)
    DDX_Control(pDX, IDC_COMBO_SHIPS_RULE, m_comShipsRule);
    DDX_Control(pDX, IDC_COMBO_SHIPS_DRAW, m_comShipsDraw);
    DDX_Control(pDX, IDC_COMBO_RULE_CALIB_TYPE, m_comRuleCalibType);
    DDX_Control(pDX, IDC_COMBO_TEMPERATURE_RANGE, m_comTemperatureRange);
    DDX_Control(pDX, IDC_LIST_THERMOMETRIC, m_lstThermometric);
    DDX_Control(pDX, IDC_LIST_REALTIME_THERMOMETRY, m_lstRealtimeThermometry);
    DDX_Control(pDX, IDC_COMBO_DIFFCOMPARISON_TYPE, m_comDiffComparisonType);
    DDX_Control(pDX, IDC_COMBO_DIFFCOMPARISON_ALARMTYPE, m_comDiffComparisonAlarmType);
    DDX_Control(pDX, IDC_COMBO_DIFFCOMPARISON_ALARMRULE, m_comDiffComparisonAlarmRule);
    DDX_Control(pDX, IDC_COMBO_THERMOMETRY_ALARMTYPE, m_comThermometryAlarmType);
    DDX_Control(pDX, IDC_COMBO_THERMOMETRY_ALARMRULE, m_comThermometryAlarmRule);
    DDX_Control(pDX, IDC_COMBO_RULE, m_comRule);
    DDX_Control(pDX, IDC_COMBO_PRESET_NO, m_comPresetNo);
    DDX_Control(pDX, IDC_COMBO_THERMOMETRY_UNIT, m_comThermometryUnit);
    DDX_Control(pDX, IDC_COMBO_THERMOMETRY_RANGE, m_comThermometryRange);
    DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
    DDX_Check(pDX, IDC_CHK_FIREREG_OVERLAY, m_bFireRegionOverlay);
    DDX_Text(pDX, IDC_EDIT_FIRE_COMFIRM_TIME, m_byFireComfirmTime);
    DDX_Text(pDX, IDC_EDIT_SENSITIVITY, m_bySensitivity);
    DDX_Check(pDX, IDC_CHK_ENABLE_THERMOMETRY, m_bEnbaleThermometry);
    DDX_Check(pDX, IDC_CHK_PICTURE_OVERLAY, m_bPictureOverlay);
    DDX_Check(pDX, IDC_CHK_STREAM_OVERLAY, m_bStreamOverlay);
    DDX_Check(pDX, IDC_CHECK_ENABLE_RULE, m_bEnableRule);
    DDX_Check(pDX, IDC_CHECK_REGION, m_bChkRegion);
    DDX_Text(pDX, IDC_EDIT_DISTANCE, m_dwDistance);
    DDX_Text(pDX, IDC_EDIT_EMISSIVITY, m_fEmissivity);
    DDX_Text(pDX, IDC_EDIT_REFLECTIVE_TEMPERATURE, m_fReflectiveTemperature);
    DDX_Text(pDX, IDC_EDIT_RULE_ID, m_byRuleID);
    DDX_Text(pDX, IDC_EDIT_RULE_NAME, m_csRuleName);
    DDX_Check(pDX, IDC_CHECK_ALARMRULE_ENABLE, m_bChkAlarmRuleEnable);
    DDX_Text(pDX, IDC_EDIT_THERMOMETRY_ALARMRULE_ID, m_byThermometryRuleID);
    DDX_Text(pDX, IDC_EDIT_THERMOMETRY_ALARMRULE_NAME, m_csThermometryRuleName);
    DDX_Text(pDX, IDC_EDIT_THERMOMETRY_ALARM, m_fAlarm);
    DDX_Text(pDX, IDC_EDIT_THERMOMETRY_ALERT, m_fAlert);
    DDX_Text(pDX, IDC_EDIT_THERMOMETRY_THRESHOLD, m_fThreshold);
    DDX_Check(pDX, IDC_CHECK_DIFFCOMPARISON_ENABLE, m_bChkDiffComparisonEnable);
    DDX_Text(pDX, IDC_EDIT_DIFFCOMPARISON, m_fTemperatureDiff);
    DDX_Text(pDX, IDC_EDIT_DIFFCOMPARISON_ALARMID1, m_byAlarmID1);
    DDX_Text(pDX, IDC_EDIT_DIFFCOMPARISON_ALARMID2, m_byAlarmID2);
    DDX_Text(pDX, IDC_EDIT_DIFFCOMPARISON_RULEID, m_byDiffRuleID);
    DDX_Text(pDX, IDC_EDIT_THERMOMETRIC_POINT_X, m_fThermPointX);
    DDX_Text(pDX, IDC_EDIT_THERMOMETRIC_POINT_Y, m_fThermPointY);
    DDX_Text(pDX, IDC_EDIT_EMISSION_RATE, m_fCenterPointEmissionRate);
    DDX_Text(pDX, IDC_EDIT_FILE_PATH, m_csFilePath);
    DDX_Check(pDX, IDC_CHECK_REFLECTIVE_ENABLE, m_bReflectiveEnabled);
    DDX_Text(pDX, IDC_EDIT_THRESHOLD_TEMPERATURE, m_fThresholdTemperature);
    DDX_Check(pDX, IDC_CHK_ENABLE_BAREDATAOVERLAY, m_bEnableBareDataOverlay);
    DDX_Text(pDX, IDC_EDIT_INTERVALTIME_BAREDATAOVERLAY, m_byInterTimeBareDataOverlay);
    DDX_Check(pDX, IDC_CHECK_SHIPS_ENABLE, m_bShipsEnable);
    DDX_Check(pDX, IDC_CHECK_SHIPS_FRAMEOVERLAY_ENABLED, m_bShipsFrameOverlayEnabled);
    DDX_Check(pDX, IDC_CHECK_SHIPS_RULE_ENABLE, m_bShipsRuleEnable);
    DDX_Text(pDX, IDC_EDIT_LOOKDOWNUPANAGLE, m_fLookDownUpAngle);
    DDX_Text(pDX, IDC_EDIT_SHIPS_HORIZONTALHEIGHT, m_fHorizontalHeight);
    DDX_Text(pDX, IDC_EDIT_SHIPS_RULE_SENSITIVITY, m_byShipsSensitivity);
    DDX_Check(pDX, IDC_CHK_SHIPS_SHOW, m_bShipsShow);
    DDX_Check(pDX, IDC_CHK_THERMOMETRY_SHOW, m_bThermShow);
    DDX_Text(pDX, IDC_EDIT_SHIPS_RULE_ID, m_byShipRuleID);
    //}}AFX_DATA_MAP
    DDX_Check(pDX, IDC_CHK_MANUALRANGING_ENABLE, m_bManualRangEnable);
    DDX_Check(pDX, IDC_CHK_MANUALDEICING_ENABLE, m_bManualDeicingEnable);
    DDX_Control(pDX, IDC_COMBO_INTELLTYPE, m_comIntellType);
    DDX_Control(pDX, IDC_COMBO_DetectionMode, mDetectionMode);
    DDX_Control(pDX, IDC_COMBO_FireFocusMode, mFireFocusMode);
    DDX_Control(pDX, IDC_COMBO_StrategyType, mStrategyType);
    DDX_Control(pDX, IDC_COMBO_FIRE_ZOOMMODE, m_comFireZoomMode);
    DDX_Control(pDX, IDC_COMBO_SMOKE_FIRE_ENABLED, m_comSmokeFireEnabled);
    DDX_Text(pDX, IDC_EDIT_FIRE_ZOOMLEVEL, m_byFireZoomLevel);
    DDX_Check(pDX, IDC_CHECK_SMOCKENABLE, mSmokeEnabled);
    DDX_Text(pDX, IDC_EDIT_SMOKE_SENSITIVITY, mSmokeSensitivity);
    DDX_Control(pDX, IDC_COMBO_THERMOMETRY_COLOR_TYPE, m_comTemperatureColor);
    DDX_Control(pDX, IDC_COMBO_DISTANCE_TYPE, m_comDistanceUnit);
    DDX_Control(pDX, IDC_COMBO_THERMOMETRY_CURVE, m_cmbThermometryCurve);
    DDX_Control(pDX, IDC_COMBO_FIRE_MODE, m_cmbFireImageModea);
    DDX_Text(pDX, IDC_EDIT_HIGH_TEMP, m_iHighTemperature);
    DDX_Text(pDX, IDC_EDIT_LOW_TEMP, m_iLowTemperature);
    DDX_Text(pDX, IDC_EDIT_THERMOMERY_EMISSIVITY, m_fThernomertryEmissivity);
    DDX_Text(pDX, IDC_EDIT_ENVIROHUMIDITY, m_byEnviroHumidity);
    DDX_Text(pDX, IDC_EDIT_ENVIRTEMP, m_iEnviroTemperature);
    DDX_Text(pDX, IDC_EDIT_CORRECTION_VOLUME, m_iCorrectionVolume);
    DDX_Text(pDX, IDC_EDIT_DISTEANCE_METER, m_dwDistanceMeter);
    DDX_Text(pDX, IDC_EDIT_REFLECTIVETEMP, m_fReflectiveTemp);
    DDX_Check(pDX, IDC_CHECK_SPECIAL_CENTER, m_bChkCenterSpecialPoint);
    DDX_Check(pDX, IDC_CHECK_SPECIAL_HIGHEST, m_bChkHighestSpecialPoint);
    DDX_Check(pDX, IDC_CHECK_SPECIAL_LOWEST, m_bChkLowestSpecialPoint);
    DDX_Check(pDX, IDC_CHECK_REFLECTIVE_ENABLED, m_bChkReflectiveEnabled);
    DDX_Text(pDX, IDC_EDIT_ALARM, m_fAlarmVal);
    DDX_Text(pDX, IDC_EDIT_ALERT, m_fAlertVal);
    DDX_Check(pDX, IDC_CHECK_SHOW_TEMPSTRIP, m_bShowTempStripEnable);
    DDX_Control(pDX, IDC_COMBO_THERMOMETRY_MODE, m_cmbThermometryMode);
    DDX_Text(pDX, IDC_EDIT_SHIPSALGNAME, m_sShipsAlgName);
    DDX_Text(pDX, IDC_EDIT_THERMOMETRYALGNAME, m_sThermAlgName);
    DDX_Text(pDX, IDC_EDIT_FIREALGNAME, m_csFireAlgName);
    DDX_Control(pDX, IDC_COMBO_MODE_COND, m_comModeCond);
    DDX_Text(pDX, IDC_EDIT_RULEID_COND, m_iRuleIDCond);
    DDX_Check(pDX, IDC_CHK_FIREMANUALWAIT, m_bFireManualWaitEnabled);
    DDX_Text(pDX, IDC_EDIT2, m_ThermalOpticalTransmittance);
    DDX_Text(pDX, IDC_EDIT9, m_externalOpticsWindowCorrection);
    DDX_Check(pDX, IDC_CHECK1, m_CancelRepeatedAlarmEnabled);
    DDX_Control(pDX, IDC_COMBO1, m_ApplicationSceneMode);
    DDX_Text(pDX, IDC_EDIT3, m_InstallationHeight);
    DDX_Text(pDX, IDC_EDIT_SMOKE_SENSITIVITY2, m_PatrolSensitivity);
    DDX_Text(pDX, IDC_EDIT_SMOKE_SENSITIVITY3, m_DoubleCheckSensitivity);
}


BEGIN_MESSAGE_MAP(CDlgFireDetection, CDialog)
	//{{AFX_MSG_MAP(CDlgFireDetection)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_SET_THERMOMETRY, OnBtnSetThermometry)
	ON_BN_CLICKED(IDC_BTN_GET_THERMOMETRY, OnBtnGetThermometry)
	ON_BN_CLICKED(IDC_BTN_GET_THERMOMETRY_PRESETINFO, OnBtnGetThermometryPresetinfo)
	ON_BN_CLICKED(IDC_BTN_SET_THERMOMETRY_PRESETINFO, OnBtnSetThermometryPresetinfo)
	ON_BN_CLICKED(IDC_BTN_SAVE_THERMOMETRY_PRESETINFO, OnBtnSaveThermometryPresetinfo)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_CBN_SELCHANGE(IDC_COMBO_RULE, OnSelchangeComboRule)
	ON_BN_CLICKED(IDC_BTN_SAVE_THERMOMETRY_ALARMRULE, OnBtnSaveThermometryAlarmrule)
	ON_CBN_SELCHANGE(IDC_COMBO_THERMOMETRY_ALARMRULE, OnSelchangeComboThermometryAlarmrule)
	ON_BN_CLICKED(IDC_BTN_SET_THERMOMETRY_ALARMRULE, OnBtnSetThermometryAlarmrule)
	ON_BN_CLICKED(IDC_BTN_GET_THERMOMETRY_ALARMRULE, OnBtnGetThermometryAlarmrule)
	ON_CBN_SELCHANGE(IDC_COMBO_DIFFCOMPARISON_ALARMRULE, OnSelchangeComboDiffcomparisonAlarmrule)
	ON_BN_CLICKED(IDC_BTN_SAVE_DIFFCOMPARISON, OnBtnSaveDiffcomparison)
	ON_BN_CLICKED(IDC_BTN_SET_DIFFCOMPARISON, OnBtnSetDiffcomparison)
	ON_BN_CLICKED(IDC_BTN_GET_DIFFCOMPARISON, OnBtnGetDiffcomparison)
	ON_BN_CLICKED(IDC_BTN_GET_REALTIME_THERMOMETRY, OnBtnGetRealtimeThermometry)
    ON_MESSAGE(WM_MSG_ADD_REALTIMEINFO_TOLIST,OnMsgAddRealtimeCfgToList)
    ON_MESSAGE(WM_MSG_GET_REALTIMEINFO_FINISH,OnMsgRealtimeCfgFinish)
	ON_BN_CLICKED(IDC_BTN_GET_THERMOMETRIC, OnBtnGetThermometric)
    ON_MESSAGE(WM_MSG_GET_THERMOMETRY_FINISH,OnMsgThermometryCfgFinish)
	ON_BN_CLICKED(IDC_BTN_FILE_PATH, OnBtnFilePath)
	ON_BN_CLICKED(IDC_BTN_FILE_DOWNLOAD, OnBtnFileDownload)
	ON_BN_CLICKED(IDC_BTN_FILE_UPLOAD, OnBtnFileUpload)
	ON_CBN_SELCHANGE(IDC_COMBO_RULE_CALIB_TYPE, OnSelchangeComboRuleCalibType)
	ON_BN_CLICKED(IDC_BTN_SET_BAREDATAOVERLAY, OnBtnSetBaredataoverlay)
	ON_BN_CLICKED(IDC_BTN_GET_BAREDATAOVERLAY, OnBtnGetBaredataoverlay)
	ON_BN_CLICKED(IDC_BTN_SHIPS_RULE_SAVE, OnBtnShipsRuleSave)
	ON_CBN_SELCHANGE(IDC_COMBO_SHIPS_RULE, OnSelchangeComboShipsRule)
	ON_BN_CLICKED(IDC_BTN_SHIPS_GET, OnBtnShipsGet)
	ON_BN_CLICKED(IDC_BTN_SHIPS_SET, OnBtnShipsSet)
	ON_CBN_SELCHANGE(IDC_COMBO_SHIPS_DRAW, OnSelchangeComboShipsDraw)
	ON_BN_CLICKED(IDC_CHK_THERMOMETRY_SHOW, OnChkThermometryShow)
	ON_BN_CLICKED(IDC_CHK_SHIPS_SHOW, OnChkShipsShow)
	ON_BN_CLICKED(IDC_BTN_SHIPSCOUNT, OnBtnShipscount)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_FOCUSZOOM, &CDlgFireDetection::OnBnClickedBtnFocuszoom)
    ON_BN_CLICKED(IDC_BTN_SET_MANUALRANGING, &CDlgFireDetection::OnBnClickedBtnSetManualranging)
	ON_BN_CLICKED(IDC_BTN_SET_MANUALDEICING, &CDlgFireDetection::OnBnClickedBtnSetManualdeicing)
	ON_BN_CLICKED(IDC_BTN_GET_MANUALDEICING, &CDlgFireDetection::OnBnClickedBtnGetManualdeicing)
    ON_BN_CLICKED(IDC_BTN_GET_MANUALTHERM_INFO, &CDlgFireDetection::OnBnClickedBtnGetManualthermInfo)
    ON_BN_CLICKED(IDC_BTN_SET_THERMINTELL, &CDlgFireDetection::OnBnClickedBtnSetThermintell)
    ON_BN_CLICKED(IDC_BTN_GET_THERMINTELL, &CDlgFireDetection::OnBnClickedBtnGetThermintell)
    ON_BN_CLICKED(IDC_BTN_REGION_CFG, &CDlgFireDetection::OnBnClickedBtnRegionCfg)
    ON_BN_CLICKED(IDC_BTN_THERMAL_PIP_CFG, &CDlgFireDetection::OnBnClickedBtnThermalPipCfg)
    ON_BN_CLICKED(IDC_BTN_SET_THERMOMETRY_MODE, &CDlgFireDetection::OnBnClickedBtnSetThermometryMode)
    ON_BN_CLICKED(IDC_BTN_GET_THERMOMETRY_MODE, &CDlgFireDetection::OnBnClickedBtnGetThermometryMode)
    ON_BN_CLICKED(IDC_BTN_GET_ALGINFO, &CDlgFireDetection::OnBnClickedBtnGetAlginfo)
    ON_BN_CLICKED(IDC_BTN_FIRESCAN_START, &CDlgFireDetection::OnBnClickedBtnFirescanStart)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFireDetection message handlers

BOOL CDlgFireDetection::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    InitComboBoxCtrl();
    InitListCtrl();
    GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcPlayWnd);
    ScreenToClient(&m_rcPlayWnd);

   StartRealPlay(GetDlgItem(IDC_PLAYWND)->GetSafeHwnd(),g_DrawCalibRgn,this);
    
   m_comIntellType.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgFireDetection::InitListCtrl()
{
    char szLanTemp[128] = {0};
	m_lstRealtimeThermometry.SetExtendedStyle(m_lstRealtimeThermometry.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
    g_StringLanType(szLanTemp, "相对时标", "Relative Time");
    m_lstRealtimeThermometry.InsertColumn(0, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "绝对时标", "Abs Time");
    m_lstRealtimeThermometry.InsertColumn(1, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "规则名称", "Rule Name");
    m_lstRealtimeThermometry.InsertColumn(2, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "规则ID", "Rule ID");
    m_lstRealtimeThermometry.InsertColumn(3, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "预置点号", "Preset No");
    m_lstRealtimeThermometry.InsertColumn(4, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "标定类型", "Calibration Type");
    m_lstRealtimeThermometry.InsertColumn(5, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "当前温度", "Current Temperature");
    m_lstRealtimeThermometry.InsertColumn(6, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "点测温坐标", "Point");
    m_lstRealtimeThermometry.InsertColumn(7, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "最高温", "Max Temperature");
    m_lstRealtimeThermometry.InsertColumn(8, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "最低温", "Min Temperature");
    m_lstRealtimeThermometry.InsertColumn(9, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "平均温", "Average Temperature");
    m_lstRealtimeThermometry.InsertColumn(10, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "温差", "Temperature difference");
    m_lstRealtimeThermometry.InsertColumn(11, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "测温区域", "Region");
    m_lstRealtimeThermometry.InsertColumn(12, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "测温单位", "Unit");
    m_lstRealtimeThermometry.InsertColumn(13, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "数据状态", "Data Type");
    m_lstRealtimeThermometry.InsertColumn(14, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "中心点测温", "Center Point");
    m_lstRealtimeThermometry.InsertColumn(15, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "最高点测温", "Highest Point");
    m_lstRealtimeThermometry.InsertColumn(16, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "最低点测温", "Lowest Point");
    m_lstRealtimeThermometry.InsertColumn(17, szLanTemp, LVCFMT_LEFT, 60, -1);


    m_lstThermometric.SetExtendedStyle(m_lstThermometric.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
    g_StringLanType(szLanTemp, "本地灰度值", "Gray Value");
    m_lstThermometric.InsertColumn(0, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "中心点灰度值", "Center Point Gray Value");
    m_lstThermometric.InsertColumn(1, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "空腔温度", "Cavity Temperature");
    m_lstThermometric.InsertColumn(2, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "FPA温度", "FPA Temperature");
    m_lstThermometric.InsertColumn(3, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "中心点温度", "Center Point Temperature");
    m_lstThermometric.InsertColumn(4, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "环境温度", "Environ Temperature");
    m_lstThermometric.InsertColumn(5, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "温控等级", "Temperature Level");
    m_lstThermometric.InsertColumn(6, szLanTemp, LVCFMT_LEFT, 60, -1);
}

void CDlgFireDetection::InitComboBoxCtrl()
{
    char sbuf[128] = {0};
    int i = 0;
    for (i = 0; i < 40; i++)
    {
        sprintf(sbuf, "Rule%d", i+1);
        m_comRule.InsertString(i,sbuf);
    }
    m_comRule.SetCurSel(0);
    
    for (i = 0; i < 100; i++)
    {
        sprintf(sbuf, "%d", i+1);
        m_comPresetNo.InsertString(i,sbuf);
    }
    m_comPresetNo.SetCurSel(0);

    for (i = 0; i < 40; i++)
    {
        sprintf(sbuf, "Rule%d", i+1);
        m_comThermometryAlarmRule.InsertString(i,sbuf);
    }
    m_comThermometryAlarmRule.SetCurSel(0);

    m_comThermometryAlarmType.ResetContent();    
    g_StringLanType(sbuf, "高温大于", "highestGreater");
    m_comThermometryAlarmType.AddString(sbuf);
    g_StringLanType(sbuf, "高温小于", "highestLess");
    m_comThermometryAlarmType.AddString(sbuf);
    g_StringLanType(sbuf, "低温大于", "lowestGreater");
    m_comThermometryAlarmType.AddString(sbuf);
    g_StringLanType(sbuf, "低温小于", "lowestLess");
    m_comThermometryAlarmType.AddString(sbuf);
    g_StringLanType(sbuf, "平均温大于", "averageGreater");
    m_comThermometryAlarmType.AddString(sbuf);
    g_StringLanType(sbuf, "平均温小于", "averageLess");
    m_comThermometryAlarmType.AddString(sbuf);
    g_StringLanType(sbuf, "温差大于", "diffTempGreater");
    m_comThermometryAlarmType.AddString(sbuf);
    g_StringLanType(sbuf, "温差小于", "diffTempLess");
    m_comThermometryAlarmType.AddString(sbuf);
    m_comThermometryAlarmType.SetCurSel(0);

    for (i = 0; i < 40; i++)
    {
        sprintf(sbuf, "Rule%d", i+1);
        m_comDiffComparisonAlarmRule.InsertString(i,sbuf);
    }
    m_comDiffComparisonAlarmRule.SetCurSel(0);

//     m_comDiffComparisonAlarmType.ResetContent();    
//     g_StringLanType(sbuf, "高温", "highest");
//     m_comDiffComparisonAlarmType.AddString(sbuf);
//     g_StringLanType(sbuf, "低温", "lowest");
//     m_comDiffComparisonAlarmType.AddString(sbuf);
//     g_StringLanType(sbuf, "平均温", "average");
//     m_comDiffComparisonAlarmType.AddString(sbuf);
//     g_StringLanType(sbuf, "温差", "diffTemp");
//     m_comDiffComparisonAlarmType.AddString(sbuf);
//     m_comDiffComparisonAlarmType.SetCurSel(0);
	m_comDiffComparisonAlarmType.ResetContent();
	g_StringLanType(sbuf, "高温大于", "highestGreater");
	m_comDiffComparisonAlarmType.AddString(sbuf);
	g_StringLanType(sbuf, "高温小于", "highestLess");
	m_comDiffComparisonAlarmType.AddString(sbuf);
	g_StringLanType(sbuf, "低温大于", "lowestGreater");
	m_comDiffComparisonAlarmType.AddString(sbuf);
	g_StringLanType(sbuf, "低温小于", "lowestLess");
	m_comDiffComparisonAlarmType.AddString(sbuf);
	g_StringLanType(sbuf, "平均温大于", "averageGreater");
	m_comDiffComparisonAlarmType.AddString(sbuf);
	g_StringLanType(sbuf, "平均温小于", "averageLess");
	m_comDiffComparisonAlarmType.AddString(sbuf);
	g_StringLanType(sbuf, "温差大于", "diffTempGreater");
	m_comDiffComparisonAlarmType.AddString(sbuf);
	g_StringLanType(sbuf, "温差小于", "diffTempLess");
	m_comDiffComparisonAlarmType.AddString(sbuf);
	m_comDiffComparisonAlarmType.SetCurSel(0);

    m_comDiffComparisonType.ResetContent();    
    g_StringLanType(sbuf, "小于", "Less");
    m_comDiffComparisonType.AddString(sbuf);
    g_StringLanType(sbuf, "大于", "Greater");
    m_comDiffComparisonType.AddString(sbuf);
    m_comDiffComparisonType.SetCurSel(0);

    m_comRuleCalibType.SetCurSel(0);

    for (i = 0; i < 8; i++)
    {
        sprintf(sbuf, "Rule%d", i+1);
        m_comShipsRule.InsertString(i,sbuf);
    }
    m_comShipsRule.SetCurSel(0);

    m_comShipsDraw.SetCurSel(0);
}

void CDlgFireDetection::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    memset(&m_struFireDetection, 0, sizeof(m_struFireDetection));

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &m_struFireDetection;
    struCfg.dwOutSize = sizeof(m_struFireDetection);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_FIREDETECTION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_FIREDETECTION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_FIREDETECTION");
    }

    m_bEnable = m_struFireDetection.byEnabled;
    m_bySensitivity = m_struFireDetection.bySensitivity;
    m_byFireComfirmTime = m_struFireDetection.byFireComfirmTime;
    m_bFireRegionOverlay = m_struFireDetection.byFireRegionOverlay;

    mDetectionMode.SetCurSel(m_struFireDetection.byDetectionMode);
    mFireFocusMode.SetCurSel(m_struFireDetection.byFireFocusMode);

    mStrategyType.SetCurSel(m_struFireDetection.struAlarmStrategy.byStrategyType);

    mSmokeEnabled = m_struFireDetection.struSmokeCfg.byEnable;
    mSmokeSensitivity = m_struFireDetection.struSmokeCfg.bySensitivity;
    m_PatrolSensitivity = m_struFireDetection.struSmokeCfg.byPatrolSensitivity;
    m_DoubleCheckSensitivity = m_struFireDetection.struSmokeCfg.byDoubleCheckSensitivity;

    m_comFireZoomMode.SetCurSel(m_struFireDetection.byFireZoomMode);
    m_byFireZoomLevel = m_struFireDetection.byFirezoomLevel;

    m_comSmokeFireEnabled.SetCurSel(m_struFireDetection.bySmokeFireEnabled);
    m_bFireManualWaitEnabled = m_struFireDetection.byFireManualWaitEnabled;

    m_CancelRepeatedAlarmEnabled = m_struFireDetection.byCancelRepeatedAlarmEnabled;
    m_ApplicationSceneMode.SetCurSel(m_struFireDetection.byApplicationSceneMode);
    m_InstallationHeight = m_struFireDetection.dwInstallationHeight;

    UpdateData(FALSE);
}

void CDlgFireDetection::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    memset(&m_struFireDetection, 0, sizeof(m_struFireDetection));

    m_struFireDetection.byEnabled = m_bEnable;
    m_struFireDetection.bySensitivity = m_bySensitivity;
    m_struFireDetection.byFireComfirmTime = m_byFireComfirmTime;
    m_struFireDetection.byFireRegionOverlay = m_bFireRegionOverlay;
    m_struFireDetection.dwSize = sizeof(m_struFireDetection);
    
    m_struFireDetection.byDetectionMode = mDetectionMode.GetCurSel();
    m_struFireDetection.byFireFocusMode = mFireFocusMode.GetCurSel();

    m_struFireDetection.struAlarmStrategy.byStrategyType = mStrategyType.GetCurSel();

    m_struFireDetection.struSmokeCfg.byEnable = mSmokeEnabled;
    m_struFireDetection.struSmokeCfg.bySensitivity = mSmokeSensitivity;
    m_struFireDetection.struSmokeCfg.byPatrolSensitivity = m_PatrolSensitivity;
    m_struFireDetection.struSmokeCfg.byDoubleCheckSensitivity = m_DoubleCheckSensitivity;

    m_struFireDetection.byFireZoomMode = m_comFireZoomMode.GetCurSel();
    m_struFireDetection.byFirezoomLevel = m_byFireZoomLevel;

    m_struFireDetection.bySmokeFireEnabled = m_comSmokeFireEnabled.GetCurSel();
    m_struFireDetection.byFireManualWaitEnabled = m_bFireManualWaitEnabled;

    m_struFireDetection.byCancelRepeatedAlarmEnabled = m_CancelRepeatedAlarmEnabled;
    m_struFireDetection.byApplicationSceneMode = m_ApplicationSceneMode.GetCurSel();
    m_struFireDetection.dwInstallationHeight = m_InstallationHeight;

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &m_struFireDetection;
    struCfg.dwInSize = sizeof(m_struFireDetection);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_FIREDETECTION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_FIREDETECTION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_FIREDETECTION");
    }
}

void CDlgFireDetection::OnBtnSetThermometry() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_THERMOMETRY_BASICPARAM struThermometryBasic = {0};
    
    struThermometryBasic.byEnabled = m_bEnbaleThermometry;
    struThermometryBasic.byStreamOverlay = m_bStreamOverlay;
    struThermometryBasic.byPictureOverlay = m_bPictureOverlay;
    //默认值;-20~150℃;0~550℃;0-650℃;-20-650℃;-20~1500℃;automatic;
    if (m_comThermometryRange.GetCurSel() == 6)
    {
        struThermometryBasic.byThermometryRange = 0xff;
    }
    else
    {
        struThermometryBasic.byThermometryRange = m_comThermometryRange.GetCurSel();
    }
    struThermometryBasic.byThermometryUnit = m_comThermometryUnit.GetCurSel();
    struThermometryBasic.struTempColor.byType = m_comTemperatureColor.GetCurSel();
    struThermometryBasic.struTempColor.iHighTemperature = m_iHighTemperature;
    struThermometryBasic.struTempColor.iLowTemperature = m_iLowTemperature;
    struThermometryBasic.byDistanceUnit = m_comDistanceUnit.GetCurSel();
    struThermometryBasic.byFireImageModea = m_cmbFireImageModea.GetCurSel();
    struThermometryBasic.byThermometryCurve = m_cmbThermometryCurve.GetCurSel();
    struThermometryBasic.fEmissivity = m_fThernomertryEmissivity;
    struThermometryBasic.byEnviroHumidity = m_byEnviroHumidity;
    struThermometryBasic.iEnviroTemperature = m_iEnviroTemperature;
    struThermometryBasic.iCorrectionVolume = m_iCorrectionVolume;
    struThermometryBasic.bySpecialPointThermType = 0;
    struThermometryBasic.bySpecialPointThermType |= (m_bChkCenterSpecialPoint << 0);
    struThermometryBasic.bySpecialPointThermType |= (m_bChkHighestSpecialPoint << 1);
    struThermometryBasic.bySpecialPointThermType |= (m_bChkLowestSpecialPoint << 2);
    struThermometryBasic.byReflectiveEnabled = m_bChkReflectiveEnabled;
    struThermometryBasic.wDistance = m_dwDistanceMeter;
    struThermometryBasic.fReflectiveTemperature = m_fReflectiveTemp;
    struThermometryBasic.byShowTempStripEnable = m_bShowTempStripEnable;
    struThermometryBasic.fAlert = m_fAlertVal;
    struThermometryBasic.fAlarm = m_fAlarmVal;
    struThermometryBasic.fThermalOpticalTransmittance = m_ThermalOpticalTransmittance;
    struThermometryBasic.fExternalOpticsWindowCorrection = m_externalOpticsWindowCorrection;
    struThermometryBasic.dwSize = sizeof(struThermometryBasic);
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struThermometryBasic;
    struCfg.dwInSize = sizeof(struThermometryBasic);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_THERMOMETRY_BASICPARAM, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_THERMOMETRY_BASICPARAM");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_THERMOMETRY_BASICPARAM");
    }
}

void CDlgFireDetection::OnBtnGetThermometry() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_THERMOMETRY_BASICPARAM struThermometryBasic = {0};
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &struThermometryBasic;
    struCfg.dwOutSize = sizeof(struThermometryBasic);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_THERMOMETRY_BASICPARAM, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_THERMOMETRY_BASICPARAM");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_THERMOMETRY_BASICPARAM");
    }
    
    m_bEnbaleThermometry = struThermometryBasic.byEnabled;
    m_bStreamOverlay = struThermometryBasic.byStreamOverlay;
    m_bPictureOverlay = struThermometryBasic.byPictureOverlay;
    //默认值;-20~150℃;0~550℃;0-650℃;-20-650℃;-20~1500℃;automatic;
    if (struThermometryBasic.byThermometryRange == 0xff)
    {
        m_comThermometryRange.SetCurSel(6);
    }
    else
    {
        m_comThermometryRange.SetCurSel(struThermometryBasic.byThermometryRange);
    }
    m_comThermometryUnit.SetCurSel(struThermometryBasic.byThermometryUnit);
    m_comDistanceUnit.SetCurSel(struThermometryBasic.byDistanceUnit);
    m_cmbFireImageModea.SetCurSel(struThermometryBasic.byFireImageModea);
    m_cmbThermometryCurve.SetCurSel(struThermometryBasic.byThermometryCurve);
    m_fThernomertryEmissivity = struThermometryBasic.fEmissivity;
    m_byEnviroHumidity = struThermometryBasic.byEnviroHumidity;
    m_iEnviroTemperature = struThermometryBasic.iEnviroTemperature;
    m_iCorrectionVolume = struThermometryBasic.iCorrectionVolume;
    m_comTemperatureColor.SetCurSel(struThermometryBasic.struTempColor.byType);
    m_iHighTemperature = struThermometryBasic.struTempColor.iHighTemperature;
    m_iLowTemperature = struThermometryBasic.struTempColor.iLowTemperature;
    m_bChkCenterSpecialPoint = (struThermometryBasic.bySpecialPointThermType >> 0) & 0x01;
    m_bChkHighestSpecialPoint = (struThermometryBasic.bySpecialPointThermType >> 1) & 0x01;
    m_bChkLowestSpecialPoint = (struThermometryBasic.bySpecialPointThermType >> 2) & 0x01;
    m_bChkReflectiveEnabled = struThermometryBasic.byReflectiveEnabled;
    m_dwDistanceMeter = struThermometryBasic.wDistance;
    m_fReflectiveTemp = struThermometryBasic.fReflectiveTemperature;
    m_bShowTempStripEnable = struThermometryBasic.byShowTempStripEnable;
    m_fAlertVal = struThermometryBasic.fAlert;
    m_fAlarmVal = struThermometryBasic.fAlarm;
    m_ThermalOpticalTransmittance = struThermometryBasic.fThermalOpticalTransmittance;
    m_externalOpticsWindowCorrection = struThermometryBasic.fExternalOpticsWindowCorrection;
    UpdateData(FALSE);
}

void CDlgFireDetection::SaveThermometryCond()
{
    UpdateData(TRUE);
    memset(&m_struThermometryCond, 0, sizeof(m_struThermometryCond));
    m_struThermometryCond.dwSize = sizeof(m_struThermometryCond);
    m_struThermometryCond.dwChannel = m_lChannel;
    m_struThermometryCond.wPresetNo = m_comPresetNo.GetCurSel() + 1;
}

void CDlgFireDetection::OnBtnGetThermometryPresetinfo() 
{
	// TODO: Add your control notification handler code here
    SaveThermometryCond();

    memset(&m_struThermometryInfo, 0, sizeof(m_struThermometryInfo));

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_struThermometryCond;
    struCfg.dwCondSize = sizeof(m_struThermometryCond);
    struCfg.lpOutBuffer = &m_struThermometryInfo;
    struCfg.dwOutSize = sizeof(m_struThermometryInfo);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_THERMOMETRY_PRESETINFO, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_THERMOMETRY_PRESETINFO");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_THERMOMETRY_PRESETINFO");
    }

    m_comRule.SetCurSel(0);
    OnSelchangeComboRule();

}

void CDlgFireDetection::OnBtnSetThermometryPresetinfo() 
{
	// TODO: Add your control notification handler code here
    SaveThermometryCond();
    
    m_struThermometryInfo.dwSize = sizeof(m_struThermometryInfo);
    m_struThermometryInfo.wPresetNo = m_comPresetNo.GetCurSel() + 1;
    OnBtnSaveThermometryPresetinfo();

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_struThermometryCond;
    struCfg.dwCondSize = sizeof(m_struThermometryCond);
    struCfg.lpInBuffer = &m_struThermometryInfo;
    struCfg.dwInSize = sizeof(m_struThermometryInfo);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_THERMOMETRY_PRESETINFO, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_THERMOMETRY_PRESETINFO");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_THERMOMETRY_PRESETINFO");
    }

}

void CDlgFireDetection::OnBtnSaveThermometryPresetinfo() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int iRule = m_comRule.GetCurSel();
    m_struThermometryInfo.struPresetInfo[iRule].byEnabled = m_bEnableRule;
    m_struThermometryInfo.struPresetInfo[iRule].byRuleID = m_byRuleID;
    m_struThermometryInfo.struPresetInfo[iRule].wDistance = m_dwDistance;
    m_struThermometryInfo.struPresetInfo[iRule].fEmissivity = m_fEmissivity;
    m_struThermometryInfo.struPresetInfo[iRule].byReflectiveEnabled = m_bReflectiveEnabled;
    m_struThermometryInfo.struPresetInfo[iRule].fReflectiveTemperature = m_fReflectiveTemperature;
    m_struThermometryInfo.struPresetInfo[iRule].byRuleCalibType = m_comRuleCalibType.GetCurSel();
    strncpy(m_struThermometryInfo.struPresetInfo[iRule].szRuleName, m_csRuleName.GetBuffer(0), (NAME_LEN - 1));
    //m_struThermometryInfo.struPresetInfo[iRule].fThresholdTemperature = m_fThresholdTemperature;

}

void CDlgFireDetection::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonDown(nFlags, point);

    UpdateData(TRUE);

    //m_bDrawEnd = FALSE;

    if (!m_rcPlayWnd.PtInRect(point))
    {
        return;
	}

    if (m_bThermShow)
    {
        if (/*!m_bChkRegion*/0 == m_comRuleCalibType.GetCurSel())
        {
            NET_VCA_POINT&  struPoint = m_struThermometryInfo.struPresetInfo[m_comRule.GetCurSel()].struPoint;
            struPoint.fX = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
            struPoint.fY = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
            //return;
        }
        else if (1 == m_comRuleCalibType.GetCurSel())
        {
            int i = m_comRule.GetCurSel();

            NET_VCA_POLYGON&  struRegion = m_struThermometryInfo.struPresetInfo[m_comRule.GetCurSel()].struRegion;
            if (m_bDrawEnd || m_nDrawPointNum >= 20)
            {
                m_bDrawEnd = FALSE;
                memset(&struRegion,0,sizeof(struRegion));
                //  return;
            }
            struRegion.struPos[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
            struRegion.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
            m_nDrawPointNum++;
            
            memcpy(&m_struPolyGon, &struRegion, sizeof(NET_VCA_POLYGON));
        }
        else if (2 == m_comRuleCalibType.GetCurSel())
        {
            NET_VCA_POLYGON&  struRegion = m_struThermometryInfo.struPresetInfo[m_comRule.GetCurSel()].struRegion;
            
            if (m_bDrawEnd || m_nDrawPointNum >= 2)
            {
                m_bDrawEnd = FALSE;
                memset(&struRegion,0,sizeof(struRegion));
                //  return;
            }
            struRegion.struPos[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
            struRegion.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
            m_nDrawPointNum++;
            memcpy(&m_struPolyGon, &struRegion, sizeof(NET_VCA_POLYGON));
            
            if (2 == m_nDrawPointNum)
            {
                m_bDrawEnd = TRUE;
                m_nDrawPointNum = 0;
            }
        }
    }


    if (m_bShipsShow)
    {
        if (0 == m_comShipsDraw.GetCurSel())
        {
            NET_ITC_POLYGON&  struITCRegion = m_struShipsDet.struShipsDetectionRegion[m_comShipsRule.GetCurSel()].struPolygon;
            if (m_bDrawEnd || m_nShipsDrawPointNum >= 20)
            {
                m_bDrawEnd = FALSE;
                memset(&struITCRegion,0,sizeof(struITCRegion));
                //  return;
            }
            struITCRegion.struPos[m_nShipsDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
            struITCRegion.struPos[m_nShipsDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
            m_nShipsDrawPointNum++;
            
            memcpy(&m_struITCPolyGon, &struITCRegion, sizeof(NET_ITC_POLYGON));
        }
        else if (1 == m_comShipsDraw.GetCurSel())
        {
            NET_VCA_LINE& struTriggerLine = m_struShipsDet.struShipsDetectionRegion[m_comShipsRule.GetCurSel()].struTriggerLine;
            
            if (m_bDrawEnd || m_nShipsDrawPointNum >= 2)
            {
                m_bDrawEnd = FALSE;
                memset(&struTriggerLine,0,sizeof(struTriggerLine));
                //  return;
            }
            
            if (0 == m_nShipsDrawPointNum)
            {
                struTriggerLine.struStart.fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
                struTriggerLine.struStart.fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
                struTriggerLine.struEnd.fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
                struTriggerLine.struEnd.fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
                m_nShipsDrawPointNum++;
            } 
            else if (1 == m_nShipsDrawPointNum)
            {
                struTriggerLine.struEnd.fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
                struTriggerLine.struEnd.fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
                m_bDrawEnd = TRUE;
                m_nShipsDrawPointNum = 0;
            }
            
            memcpy(&m_struLine, &struTriggerLine, sizeof(NET_VCA_LINE));
            
        }
    }
    
}

void CDlgFireDetection::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnMouseMove(nFlags, point);

    if (m_bDrawEnd)
    {
        return;
    }

    if (!m_rcPlayWnd.PtInRect(point))
    {
        return;
	}

    if (m_bThermShow)
    {
        if (/*!m_bChkRegion*/0 == m_comRuleCalibType.GetCurSel())
        {
            return;
        }
        else if (1 == m_comRuleCalibType.GetCurSel())
        {
            
            NET_VCA_POLYGON&  struRegion = m_struThermometryInfo.struPresetInfo[m_comRule.GetCurSel()].struRegion;
            
            //         if (m_nDrawPointNum >= 20 || m_nDrawPointNum < 3)
            //         {
            //             memset(&struRegion,0,sizeof(struRegion));
            //             return;
            // 	    }
            
            struRegion.struPos[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
            struRegion.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
            struRegion.dwPointNum = m_nDrawPointNum + 1;
            
            memcpy(&m_struPolyGon, &struRegion, sizeof(NET_VCA_POLYGON));
        }
        else if (2 == m_comRuleCalibType.GetCurSel())
        {
            NET_VCA_POLYGON&  struRegion = m_struThermometryInfo.struPresetInfo[m_comRule.GetCurSel()].struRegion;
            
            //         if (m_nDrawPointNum > 2)
            //         {
            //             memset(&struRegion,0,sizeof(struRegion));
            //             return;
            //         }
            
            struRegion.struPos[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
            struRegion.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
            struRegion.dwPointNum = m_nDrawPointNum + 1;
            
            memcpy(&m_struPolyGon, &struRegion, sizeof(NET_VCA_POLYGON));
        }

    }


    if (m_bShipsShow)
    {
        if (0 == m_comShipsDraw.GetCurSel())
        {
            
            NET_ITC_POLYGON&  struITCRegion = m_struShipsDet.struShipsDetectionRegion[m_comShipsRule.GetCurSel()].struPolygon;
            
            struITCRegion.struPos[m_nShipsDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
            struITCRegion.struPos[m_nShipsDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
            struITCRegion.dwPointNum = m_nShipsDrawPointNum + 1;
            
            memcpy(&m_struITCPolyGon, &struITCRegion, sizeof(NET_ITC_POLYGON));
        }
        else if (1 == m_comShipsDraw.GetCurSel())
        {
            
            NET_VCA_LINE& struTriggerLine = m_struShipsDet.struShipsDetectionRegion[m_comShipsRule.GetCurSel()].struTriggerLine;
            
            struTriggerLine.struEnd.fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
            struTriggerLine.struEnd.fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
            
            
            memcpy(&m_struLine, &struTriggerLine, sizeof(NET_VCA_LINE));
        }
    }
   
}

void CDlgFireDetection::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnRButtonDown(nFlags, point);

    if (!m_rcPlayWnd.PtInRect(point))
    {
        return;
    }

    if (m_bThermShow)
    {
        //测温
        if (/*!m_bChkRegion*/0 == m_comRuleCalibType.GetCurSel())
        {
            return;
        }
        else if (1 == m_comRuleCalibType.GetCurSel())
        {    
            NET_VCA_POLYGON&  struRegion = m_struThermometryInfo.struPresetInfo[m_comRule.GetCurSel()].struRegion;
            if (m_nDrawPointNum >= 20 || m_nDrawPointNum < 3)
            {
                memset(&struRegion,0,sizeof(struRegion));
                return;
            }
            
            struRegion.dwPointNum = m_nDrawPointNum;
            
            memcpy(&m_struPolyGon, &struRegion, sizeof(NET_VCA_POLYGON));
        }
        else if (2 == m_comRuleCalibType.GetCurSel())
        {
            NET_VCA_POLYGON&  struRegion = m_struThermometryInfo.struPresetInfo[m_comRule.GetCurSel()].struRegion;
            if (m_nDrawPointNum > 2)
            {
                memset(&struRegion,0,sizeof(struRegion));
                return;
            }
            
            struRegion.dwPointNum = m_nDrawPointNum;
            
            memcpy(&m_struPolyGon, &struRegion, sizeof(NET_VCA_POLYGON));
        }
        m_nDrawPointNum = 0;
    }
    

    if (m_bShipsShow)
    {
        //船只检测
        if (0 == m_comShipsDraw.GetCurSel())
        {
        
            NET_ITC_POLYGON&  struITCRegion = m_struShipsDet.struShipsDetectionRegion[m_comShipsRule.GetCurSel()].struPolygon;
        
            if (m_nShipsDrawPointNum >= 20 || m_nShipsDrawPointNum < 3)
            {
                memset(&m_struITCPolyGon,0,sizeof(m_struITCPolyGon));
                return;
            }
        
            m_struITCPolyGon.dwPointNum = m_nShipsDrawPointNum;
        
            memcpy(&m_struITCPolyGon, &struITCRegion, sizeof(NET_ITC_POLYGON));
        }
        m_nShipsDrawPointNum = 0;
    }
    m_bDrawEnd = TRUE;
    
    
}

void CDlgFireDetection::OnSelchangeComboRule() 
{
	// TODO: Add your control notification handler code here
    int iRule = m_comRule.GetCurSel();
    m_bEnableRule = m_struThermometryInfo.struPresetInfo[iRule].byEnabled;
    m_byRuleID = m_struThermometryInfo.struPresetInfo[iRule].byRuleID;
    m_dwDistance = m_struThermometryInfo.struPresetInfo[iRule].wDistance;
    m_fEmissivity = m_struThermometryInfo.struPresetInfo[iRule].fEmissivity;
    m_bReflectiveEnabled = m_struThermometryInfo.struPresetInfo[iRule].byReflectiveEnabled;
    m_fReflectiveTemperature = m_struThermometryInfo.struPresetInfo[iRule].fReflectiveTemperature;
    m_comRuleCalibType.SetCurSel(m_struThermometryInfo.struPresetInfo[iRule].byRuleCalibType);
    m_csRuleName.Format(_T("%s"), m_struThermometryInfo.struPresetInfo[iRule].szRuleName);
    //m_fThresholdTemperature = m_struThermometryInfo.struPresetInfo[iRule].fThresholdTemperature;
    memcpy(&m_struPolyGon, &m_struThermometryInfo.struPresetInfo[iRule].struRegion, sizeof(NET_VCA_POLYGON));
    UpdateData(FALSE);
}

void CDlgFireDetection::OnBtnSaveThermometryAlarmrule() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    int iRule = m_comThermometryAlarmRule.GetCurSel();
    m_struThermometryAlarmInfo.struThermometryAlarmRuleParam[iRule].byEnable = m_bChkAlarmRuleEnable;
    m_struThermometryAlarmInfo.struThermometryAlarmRuleParam[iRule].byRuleID = m_byThermometryRuleID;
    m_struThermometryAlarmInfo.struThermometryAlarmRuleParam[iRule].byRule = m_comThermometryAlarmType.GetCurSel();
    strncpy(m_struThermometryAlarmInfo.struThermometryAlarmRuleParam[iRule].szRuleName, m_csThermometryRuleName.GetBuffer(0), (NAME_LEN - 1));
    m_struThermometryAlarmInfo.struThermometryAlarmRuleParam[iRule].fAlert = m_fAlert;
    m_struThermometryAlarmInfo.struThermometryAlarmRuleParam[iRule].fAlarm = m_fAlarm;
    m_struThermometryAlarmInfo.struThermometryAlarmRuleParam[iRule].fThreshold = m_fThreshold;
}

void CDlgFireDetection::OnSelchangeComboThermometryAlarmrule() 
{
	// TODO: Add your control notification handler code here
	int iRule = m_comThermometryAlarmRule.GetCurSel();
    m_bChkAlarmRuleEnable = m_struThermometryAlarmInfo.struThermometryAlarmRuleParam[iRule].byEnable;
    m_byThermometryRuleID = m_struThermometryAlarmInfo.struThermometryAlarmRuleParam[iRule].byRuleID;
    m_comThermometryAlarmType.SetCurSel(m_struThermometryAlarmInfo.struThermometryAlarmRuleParam[iRule].byRule);
    m_csThermometryRuleName.Format(_T("%s"), m_struThermometryAlarmInfo.struThermometryAlarmRuleParam[iRule].szRuleName);
    m_fAlert = m_struThermometryAlarmInfo.struThermometryAlarmRuleParam[iRule].fAlert;
    m_fAlarm = m_struThermometryAlarmInfo.struThermometryAlarmRuleParam[iRule].fAlarm;
    m_fThreshold = m_struThermometryAlarmInfo.struThermometryAlarmRuleParam[iRule].fThreshold;

    UpdateData(FALSE);
}

void CDlgFireDetection::OnBtnSetThermometryAlarmrule() 
{
	// TODO: Add your control notification handler code here
    SaveThermometryCond();
    
    m_struThermometryAlarmInfo.dwSize = sizeof(m_struThermometryAlarmInfo);
    OnBtnSaveThermometryAlarmrule();
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_struThermometryCond;
    struCfg.dwCondSize = sizeof(m_struThermometryCond);
    struCfg.lpInBuffer = &m_struThermometryAlarmInfo;
    struCfg.dwInSize = sizeof(m_struThermometryAlarmInfo);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_THERMOMETRY_ALARMRULE, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_THERMOMETRY_ALARMRULE");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_THERMOMETRY_ALARMRULE");
    }
}

void CDlgFireDetection::OnBtnGetThermometryAlarmrule() 
{
	// TODO: Add your control notification handler code here
    SaveThermometryCond();
    
    memset(&m_struThermometryAlarmInfo, 0, sizeof(m_struThermometryAlarmInfo));

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_struThermometryCond;
    struCfg.dwCondSize = sizeof(m_struThermometryCond);
    struCfg.lpOutBuffer = &m_struThermometryAlarmInfo;
    struCfg.dwOutSize = sizeof(m_struThermometryAlarmInfo);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_THERMOMETRY_ALARMRULE, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_THERMOMETRY_ALARMRULE");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_THERMOMETRY_ALARMRULE");
    }
    
    m_comRule.SetCurSel(0);
    OnSelchangeComboThermometryAlarmrule();
}

void CDlgFireDetection::OnSelchangeComboDiffcomparisonAlarmrule() 
{
	// TODO: Add your control notification handler code here
    int iRule = m_comDiffComparisonAlarmRule.GetCurSel();
    m_byDiffRuleID = m_struThermometryDiffComparison.struDiffComparison[iRule].byRuleID;
    m_bChkAlarmRuleEnable = m_struThermometryDiffComparison.struDiffComparison[iRule].byEnable;
    m_byAlarmID1 = m_struThermometryDiffComparison.struDiffComparison[iRule].byAlarmID1;
    m_byAlarmID2 = m_struThermometryDiffComparison.struDiffComparison[iRule].byAlarmID2;
    m_comDiffComparisonAlarmType.SetCurSel(m_struThermometryDiffComparison.struDiffComparison[iRule].byRule);
   // m_comDiffComparisonType.SetCurSel(m_struThermometryDiffComparison.struDiffComparison[iRule].byDifferenceType);
    m_fTemperatureDiff = m_struThermometryDiffComparison.struDiffComparison[iRule].fTemperatureDiff;
    UpdateData(FALSE);
}

void CDlgFireDetection::OnBtnSaveDiffcomparison() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
	int iRule = m_comDiffComparisonAlarmRule.GetCurSel();
    m_struThermometryDiffComparison.struDiffComparison[iRule].byRuleID = m_byDiffRuleID;
    m_struThermometryDiffComparison.struDiffComparison[iRule].byEnable = m_bChkAlarmRuleEnable;
    m_struThermometryDiffComparison.struDiffComparison[iRule].byAlarmID1 = m_byAlarmID1;
    m_struThermometryDiffComparison.struDiffComparison[iRule].byAlarmID2 = m_byAlarmID2;
    m_struThermometryDiffComparison.struDiffComparison[iRule].byRule = m_comDiffComparisonAlarmType.GetCurSel();
   // m_struThermometryDiffComparison.struDiffComparison[iRule].byDifferenceType = m_comDiffComparisonType.GetCurSel();
    m_struThermometryDiffComparison.struDiffComparison[iRule].fTemperatureDiff = m_fTemperatureDiff;
}

void CDlgFireDetection::OnBtnSetDiffcomparison() 
{
	// TODO: Add your control notification handler code here
    SaveThermometryCond();
    
    m_struThermometryDiffComparison.dwSize = sizeof(m_struThermometryDiffComparison);
    OnBtnSaveDiffcomparison();
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_struThermometryCond;
    struCfg.dwCondSize = sizeof(m_struThermometryCond);
    struCfg.lpInBuffer = &m_struThermometryDiffComparison;
    struCfg.dwInSize = sizeof(m_struThermometryDiffComparison);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_THERMOMETRY_DIFFCOMPARISON, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_THERMOMETRY_DIFFCOMPARISON");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_THERMOMETRY_DIFFCOMPARISON");
    }
}

void CDlgFireDetection::OnBtnGetDiffcomparison() 
{
	// TODO: Add your control notification handler code here
    SaveThermometryCond();
    
    memset(&m_struThermometryDiffComparison, 0, sizeof(m_struThermometryDiffComparison));
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_struThermometryCond;
    struCfg.dwCondSize = sizeof(m_struThermometryCond);
    struCfg.lpOutBuffer = &m_struThermometryDiffComparison;
    struCfg.dwOutSize = sizeof(m_struThermometryDiffComparison);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_THERMOMETRY_DIFFCOMPARISON, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_THERMOMETRY_DIFFCOMPARISON");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_THERMOMETRY_DIFFCOMPARISON");
    }
    
    m_comRule.SetCurSel(0);
    OnSelchangeComboDiffcomparisonAlarmrule();
}

void CDlgFireDetection::OnBtnGetRealtimeThermometry() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    char szLan[128] = {0};

    NET_DVR_REALTIME_THERMOMETRY_COND m_struCond = {0};
    m_struCond.dwSize = sizeof(NET_DVR_REALTIME_THERMOMETRY_COND);
    m_struCond.dwChan = m_lChannel;
    m_struCond.byMode = m_comModeCond.GetCurSel() + 1;
    m_struCond.byRuleID = m_iRuleIDCond;

    if (m_lRealTimeInfoHandle >= 0)
    {
        if (!NET_DVR_StopRemoteConfig(m_lRealTimeInfoHandle))
        {
            g_StringLanType(szLan, "实时测温停止失败", "Stop Realtime Thermometry Info Failed");
            AfxMessageBox(szLan);
            return;
        }
	}

    m_lRealTimeInfoHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_GET_REALTIME_THERMOMETRY, &m_struCond, sizeof(m_struCond), g_fGetRealtimeThermometryCallback, this);
    if (m_lRealTimeInfoHandle >= 0)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_REALTIME_THERMOMETRY Chan[%d]", m_lChannel);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_REALTIME_THERMOMETRY Chan[%d]", m_lChannel);
        g_StringLanType(szLan, "实时测温获取失败", "Get Realtime Thermometry Info Failed");
        AfxMessageBox(szLan);
        return;
	}

}

void CDlgFireDetection::OnBtnGetThermometric() 
{
	// TODO: Add your control notification handler code here
//     UpdateData(TRUE);
//     char szLan[128] = {0};
// 
//     NET_DVR_THERMOMETRIC_COND m_struCond = {0};
//     m_struCond.dwSize = sizeof(NET_DVR_THERMOMETRIC_COND);
//     m_struCond.fCenterPointEmissionRate = m_fCenterPointEmissionRate;
//     m_struCond.struPoint.fX = m_fThermPointX;
//     m_struCond.struPoint.fX = m_fThermPointY;
//     m_struCond.byTemperatureRange = m_comTemperatureRange.GetCurSel()+1;
// 
//     if (m_lThermometricHandle >= 0)
//     {
//         if (!NET_DVR_StopRemoteConfig(m_lThermometricHandle))
//         {
//             g_StringLanType(szLan, "测温停止失败", "Stop Thermometry Info Failed");
//             AfxMessageBox(szLan);
//             return;
//         }
//     }
//     
//     m_lThermometricHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_GET_THERMOMETRIC_INFO, &m_struCond, sizeof(m_struCond), g_fGetThermometryCallback, this);
//     if (m_lThermometricHandle >= 0)
//     {
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_THERMOMETRIC_INFO Chan[%d]", m_lChannel);
//     }
//     else
//     {
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_THERMOMETRIC_INFO Chan[%d]", m_lChannel);
//         g_StringLanType(szLan, "测温获取失败", "Get Thermometry Info Failed");
//         AfxMessageBox(szLan);
//         return;
// 	}
}   

void CDlgFireDetection::OnBtnFilePath() 
{
	// TODO: Add your control notification handler code here
    static char szFilter[] = "All File(*.*)|*.*||";
    CFileDialog dlg(TRUE,"*.*", NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter);
    if (dlg.DoModal() == IDOK)
    {
        m_csFilePath = dlg.GetPathName();
        UpdateData(FALSE);
	}
}

DWORD  GetDownloadTherFileThread(LPVOID pParam)
{
    CDlgFireDetection *pThis = ( CDlgFireDetection*)pParam;
    
    DWORD dwState = 0;
    DWORD dwProgress = 0;
    char szLan[256] = {0};
    
    
    while (TRUE)
    {
        dwState = NET_DVR_GetDownloadState(pThis->m_lDownloadHandle,&dwProgress);
        if (dwState == 1)
        {
            g_StringLanType(szLan, "下载成功", "Download successfully");
            pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
            pThis->m_bDownLoading = FALSE;
            g_StringLanType(szLan,"下载","Download");
            pThis->GetDlgItem(IDC_BTN_FILE_DOWNLOAD)->SetWindowText(szLan);
            pThis->m_bDownLoading = FALSE;
            break;
        }
        else if (dwState == 2)
        {
            g_StringLanType(szLan, "正在下载,已下载:", "Is Downloading,progress:");
            sprintf(szLan, "%s%d", szLan, dwProgress);
            pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        }
        else if (dwState == 3)
        {
            g_StringLanType(szLan, "下载失败", "Download failed");
            pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
            break;
        }
        else if (dwState == 4)
        {
            if (dwProgress == 100)
            {
                g_StringLanType(szLan, "下载成功", "Download successfully");
                pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
                g_StringLanType(szLan,"下载","DownLoad");
                pThis->GetDlgItem(IDC_BTN_FILE_DOWNLOAD)->SetWindowText(szLan);
                pThis->m_bDownLoading = FALSE;
                break; 
            }
            else
            {
                g_StringLanType(szLan, "网络断开，状态未知", "Network disconnect, status unknown");
                pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
                break;
            }
            
        }
        
        if (dwState != 2 && dwState != 5)
        {        
            NET_DVR_StopDownload(pThis->m_lDownloadHandle);
            pThis->m_bDownLoading = FALSE;
            g_StringLanType(szLan,"下载","Download");
            pThis->GetDlgItem(IDC_BTN_FILE_DOWNLOAD)->SetWindowText(szLan);
        }
    }
    
    return FALSE;
}

void CDlgFireDetection::OnBtnFileDownload() 
{
	// TODO: Add your control notification handler code here
    char szLan[128] = {0};
    if (m_bDownLoading == FALSE)
    {
        UpdateData(TRUE);
        GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        char szFileName[MAX_PATH];
        char szInfoBuf[128] = {0};
        if (m_csFilePath.IsEmpty())
        {
            MessageBox("保存文件路径不能为空"); 
            return ; 
        }
        strcpy(szFileName, m_csFilePath);
        
        m_lDownloadHandle = NET_DVR_StartDownload(m_lServerID, NET_SDK_DOWNLOAD_THERMOMETRIC_FILE, NULL, NULL, szFileName);
        if (m_lDownloadHandle<0)
        {
            NET_DVR_StopDownloadFile(m_lDownloadHandle);
            AfxMessageBox("NET_SDK_DOWNLOAD_THERMOMETRIC_FILE Download Failed");
            return;	
        }

        DWORD dwThreadId = 0;
        m_hDownloadThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetDownloadTherFileThread),this,0,&dwThreadId);
        if (m_hDownloadThread  == NULL)
        {
            char szLan[256] = {0};
            g_StringLanType(szLan, "打开下载文件线程失败!", "open DownLoad thread Fail!");
            AfxMessageBox(szLan);
            return;
        }
        g_StringLanType(szLan, "停止下载", "Stop DownLoad");
        GetDlgItem(IDC_BTN_FILE_DOWNLOAD)->SetWindowText(szLan);
        m_bDownLoading = TRUE;
    }
    else
    {
        NET_DVR_StopDownload(m_lDownloadHandle);
        m_bDownLoading = FALSE;
        g_StringLanType(szLan, "下载", "DownLoad");
        GetDlgItem(IDC_BTN_FILE_DOWNLOAD)->SetWindowText(szLan);
    }
    UpdateData(FALSE);
}

DWORD  GetUpLoadTherFileThread(LPVOID pParam)
{
    CDlgFireDetection *pThis = (CDlgFireDetection*)pParam;
    
    DWORD dwState = 0;
    DWORD dwProgress = 0;
    char szLan[256] = {0};
    
    
    while (TRUE)
    {
        dwState = NET_DVR_GetUploadState(pThis->m_lUploadHandle,&dwProgress);
        if (dwState == 1)
        {
            g_StringLanType(szLan, "上传成功", "Upload successfully");
            pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
            pThis->m_bUpLoading = FALSE;
            g_StringLanType(szLan,"上传","Upload");
            pThis->GetDlgItem(IDC_BTN_FILE_UPLOAD)->SetWindowText(szLan);
            pThis->m_bUpLoading = FALSE;
            break;
        }
        else if (dwState == 2)
        {
            g_StringLanType(szLan, "正在上传,已上传:", "Is uploading,progress:");
            sprintf(szLan, "%s%d", szLan, dwProgress);
            pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        }
        else if (dwState == 3)
        {
            g_StringLanType(szLan, "上传失败", "Upload failed");
            pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
            break;
        }
        else if (dwState == 4)
        {
            if (dwProgress == 100)
            {
                g_StringLanType(szLan, "上传成功", "Upload successfully");
                pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
                g_StringLanType(szLan,"上传","UpLoad");
                pThis->GetDlgItem(IDC_BTN_FILE_UPLOAD)->SetWindowText(szLan);
                pThis->m_bUpLoading = FALSE;
                break; 
            }
            else
            {
                g_StringLanType(szLan, "网络断开，状态未知", "Network disconnect, status unknown");
                pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
                break;
            }
            
        }
        
        if (dwState != 2 && dwState != 5)
        {        
            NET_DVR_UploadClose(pThis->m_lUploadHandle);
            pThis->m_bUpLoading = FALSE;
            g_StringLanType(szLan,"上传","UpLoad");
            pThis->GetDlgItem(IDC_BTN_FILE_UPLOAD)->SetWindowText(szLan);
        }
    }
    
    return FALSE;
}

void CDlgFireDetection::OnBtnFileUpload() 
{
	// TODO: Add your control notification handler code here
    char szLan[128] = {0};
    if (m_bUpLoading == FALSE)
    {
        UpdateData(TRUE);
        char szFileName[MAX_PATH];
        strcpy(szFileName, m_csFilePath);
        CFile cFile;
        GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        if (!cFile.Open(szFileName, NULL))
        {
            g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
            AfxMessageBox(szLan);
            return;
        }
        DWORD dwFileSize = (DWORD)cFile.GetLength();
        if (dwFileSize == 0)
        {
            g_StringLanType(szLan, "配置文件为空", "Configure file is empty");
            AfxMessageBox(szLan);
        }
        cFile.Close();
        
        
        m_lUploadHandle = NET_DVR_UploadFile(m_lServerID, UPLOAD_THERMOMETRIC_FILE, NULL, NULL, szFileName);
        if (m_lUploadHandle < 0)
        {
            NET_DVR_StopUploadFile(m_lUploadHandle);
            AfxMessageBox("UPLOAD_THERMOMETRIC_FILE Upload Failed");
            return;	
        }

        DWORD dwThreadId = 0;
        m_hUpLoadThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetUpLoadTherFileThread),this,0,&dwThreadId);
        if (m_hUpLoadThread  == NULL)
        {
            char szLan[256] = {0};
            g_StringLanType(szLan, "打开长传文件线程失败!", "open UpLoad thread Fail!");
            AfxMessageBox(szLan);
            return;
        }
        g_StringLanType(szLan, "停止上传", "Stop UpLoad");
        GetDlgItem(IDC_BTN_FILE_UPLOAD)->SetWindowText(szLan);
        m_bUpLoading = TRUE;
    }
    else
    {
        NET_DVR_UploadClose(m_lUploadHandle);
        m_bUpLoading = FALSE;
        g_StringLanType(szLan,"上传","UpLoad");
        GetDlgItem(IDC_BTN_FILE_UPLOAD)->SetWindowText(szLan);
    }
	UpdateData(FALSE);
}

void CDlgFireDetection::OnSelchangeComboRuleCalibType() 
{
	// TODO: Add your control notification handler code here
    NET_VCA_POINT&  struPoint = m_struThermometryInfo.struPresetInfo[m_comRule.GetCurSel()].struPoint;
    NET_VCA_POLYGON&  struRegion = m_struThermometryInfo.struPresetInfo[m_comRule.GetCurSel()].struRegion;
  

    memset(&struRegion,0,sizeof(struRegion));
    memset(&struPoint,0,sizeof(struPoint));

	memcpy(&m_struPolyGon, &struRegion, sizeof(NET_VCA_POLYGON));
}

void CDlgFireDetection::OnBtnSetBaredataoverlay() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_BAREDATAOVERLAY_CFG struBareDataOverlay = {0};
    struBareDataOverlay.dwSize = sizeof(struBareDataOverlay);
    struBareDataOverlay.byEnable = m_bEnableBareDataOverlay;
	struBareDataOverlay.byIntervalTime = m_byInterTimeBareDataOverlay;

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struBareDataOverlay;
    struCfg.dwInSize = sizeof(struBareDataOverlay);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if(!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_BAREDATAOVERLAY_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_BAREDATAOVERLAY_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_BAREDATAOVERLAY_CFG");
    }
}

void CDlgFireDetection::OnBtnGetBaredataoverlay() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_BAREDATAOVERLAY_CFG struBareDataOverlay = {0};
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &struBareDataOverlay;
    struCfg.dwOutSize = sizeof(struBareDataOverlay);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_BAREDATAOVERLAY_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_BAREDATAOVERLAY_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_BAREDATAOVERLAY_CFG");
    }

    m_bEnableBareDataOverlay = struBareDataOverlay.byEnable;
    m_byInterTimeBareDataOverlay = struBareDataOverlay.byIntervalTime;
    UpdateData(FALSE);
}

void CDlgFireDetection::OnBtnShipsRuleSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    int iRule = m_comShipsRule.GetCurSel();
	m_struShipsDet.struShipsDetectionRegion[iRule].byEnable = m_bShipsRuleEnable;
	m_struShipsDet.struShipsDetectionRegion[iRule].byRuleID = m_byShipRuleID;
    m_struShipsDet.struShipsDetectionRegion[iRule].bySensitivity = m_byShipsSensitivity;
    m_struShipsDet.struShipsDetectionRegion[iRule].byFrameOverlayEnabled = m_bShipsFrameOverlayEnabled;
}

void CDlgFireDetection::OnSelchangeComboShipsRule() 
{
	// TODO: Add your control notification handler code here
	int iRule = m_comShipsRule.GetCurSel();
	m_byShipRuleID = m_struShipsDet.struShipsDetectionRegion[iRule].byRuleID;
    m_byShipsSensitivity = m_struShipsDet.struShipsDetectionRegion[iRule].bySensitivity;
    m_bShipsFrameOverlayEnabled = m_struShipsDet.struShipsDetectionRegion[iRule].byFrameOverlayEnabled;
	m_bShipsRuleEnable = m_struShipsDet.struShipsDetectionRegion[iRule].byEnable;
    memcpy(&m_struITCPolyGon, &m_struShipsDet.struShipsDetectionRegion[iRule].struPolygon, sizeof(NET_ITC_POLYGON));
    memcpy(&m_struLine, &m_struShipsDet.struShipsDetectionRegion[iRule].struTriggerLine, sizeof(NET_VCA_LINE));

    UpdateData(FALSE);
}

void CDlgFireDetection::OnBtnShipsGet() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &m_struShipsDet;
    struCfg.dwOutSize = sizeof(m_struShipsDet);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if(!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_SHIPSDETECTION_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SHIPSDETECTION_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SHIPSDETECTION_CFG");
    }
    m_fLookDownUpAngle = m_struShipsDet.fLookDownUpAngle;
    m_fHorizontalHeight = m_struShipsDet.fHorizontalHeight;
	m_bShipsEnable = m_struShipsDet.byEnable;
    m_comShipsRule.SetCurSel(0);
    UpdateData(FALSE);

    OnSelchangeComboShipsRule();
    
}

void CDlgFireDetection::OnBtnShipsSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);


	m_struShipsDet.dwSize = sizeof(m_struShipsDet);
    m_struShipsDet.byEnable = m_bShipsEnable;
    m_struShipsDet.fLookDownUpAngle = m_fLookDownUpAngle;
    m_struShipsDet.fHorizontalHeight = m_fHorizontalHeight;

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &m_struShipsDet;
    struCfg.dwInSize = sizeof(m_struShipsDet);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if(!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_SHIPSDETECTION_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SHIPSDETECTION_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SHIPSDETECTION_CFG");
    }
}


void CDlgFireDetection::OnSelchangeComboShipsDraw() 
{
	// TODO: Add your control notification handler code here
    NET_VCA_LINE& struTriggerLine = m_struShipsDet.struShipsDetectionRegion[m_comShipsRule.GetCurSel()].struTriggerLine;
    NET_ITC_POLYGON&  struITCRegion = m_struShipsDet.struShipsDetectionRegion[m_comShipsRule.GetCurSel()].struPolygon;
    
    
 //   memset(&struTriggerLine,0,sizeof(struTriggerLine));
 //   memset(&struITCRegion,0,sizeof(struITCRegion));
    
	memcpy(&m_struITCPolyGon, &struITCRegion, sizeof(NET_ITC_POLYGON));
    memcpy(&m_struLine, &struTriggerLine, sizeof(NET_VCA_LINE));
}

void CDlgFireDetection::OnChkThermometryShow() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    if (m_bThermShow)
    {
        m_bShipsShow = FALSE;
        OnSelchangeComboShipsDraw();
    }
    else
    {
        m_bShipsShow = TRUE;
    }
    UpdateData(FALSE);
}

void CDlgFireDetection::OnChkShipsShow() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if (m_bShipsShow)
    {
        m_bThermShow = FALSE;
        OnSelchangeComboRuleCalibType();
    }
    else
    {
        m_bThermShow = TRUE;
    }
    UpdateData(FALSE);
}

void CDlgFireDetection::OnBtnShipscount() 
{
	// TODO: Add your control notification handler code here
    CDlgShipDetection dlg;
    dlg.m_lChannel = m_lChannel;
    dlg.m_lUserID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}


void CDlgFireDetection::OnBnClickedBtnFocuszoom()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    NET_DVR_STD_CONTROL struStdControl = { 0 };
    struStdControl.lpCondBuffer = &m_lChannel;
    struStdControl.dwCondSize = sizeof(m_lChannel);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struStdControl.lpStatusBuffer = m_szStatusBuf;
    struStdControl.dwStatusSize = ISAPI_STATUS_LEN;
    if (!NET_DVR_STDControl(m_lServerID, NET_DVR_FIRE_FOCUSZOOM_CTRL, &struStdControl))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_FIRE_FOCUSZOOM_CTRL");
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_FIRE_FOCUSZOOM_CTRL");
    }
}


void CDlgFireDetection::OnBnClickedBtnSetManualranging()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

	NET_DVR_MANUALRANGING_CFG struManualRangCfg = { 0 };
	struManualRangCfg.byEnabled = m_bManualRangEnable;
	struManualRangCfg.dwSize = sizeof(struManualRangCfg);

    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
	struCfg.lpInBuffer = &struManualRangCfg;
	struCfg.dwInSize = sizeof(struManualRangCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

	if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_MANUALRANGING, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_MANUALRANGING");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_MANUALRANGING");
    }
}


void CDlgFireDetection::OnBnClickedBtnSetManualdeicing()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	char szLan[256] = { 0 };
	NET_DVR_MANUALDEICING_CFG struManualDeicingCfg = { 0 };
	struManualDeicingCfg.byEnabled = m_bManualDeicingEnable;

	struManualDeicingCfg.dwSize = sizeof(struManualDeicingCfg);

	NET_DVR_STD_CONFIG struCfg = { 0 };
	struCfg.lpCondBuffer = &m_lChannel;
	struCfg.dwCondSize = sizeof(m_lChannel);
	struCfg.lpInBuffer = &struManualDeicingCfg;
	struCfg.dwInSize = sizeof(struManualDeicingCfg);
	memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
	struCfg.lpStatusBuffer = m_szStatusBuf;
	struCfg.dwStatusSize = ISAPI_STATUS_LEN;

	if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_MANUALDEICING, &struCfg))
	{
		OutputDebugString(m_szStatusBuf);
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_MANUALDEICING");
		sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_MANUALDEICING");
	}
}


void CDlgFireDetection::OnBnClickedBtnGetManualdeicing()
{
	// TODO:  在此添加控件通知处理程序代码
	NET_DVR_MANUALDEICING_CFG struManualDeicingCfg = { 0 };
	NET_DVR_STD_CONFIG struCfg = { 0 };
	struCfg.lpCondBuffer = &m_lChannel;
	struCfg.dwCondSize = sizeof(m_lChannel);
	struCfg.lpOutBuffer = &struManualDeicingCfg;
	struCfg.dwOutSize = sizeof(struManualDeicingCfg);
	memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
	struCfg.lpStatusBuffer = m_szStatusBuf;
	struCfg.dwStatusSize = ISAPI_STATUS_LEN;

	if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_MANUALDEICING, &struCfg))
	{
		OutputDebugString(m_szStatusBuf);
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_MANUALDEICING");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_MANUALDEICING");
	}
	m_bManualDeicingEnable = struManualDeicingCfg.byEnabled;
	UpdateData(FALSE);

}

void CDlgFireDetection::OnBnClickedBtnGetManualthermInfo()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgManualThermCfg dlg;
    dlg.m_lChannel = m_lChannel;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgFireDetection::OnBnClickedBtnSetThermintell()
{
    // TODO:  在此添加控件通知处理程序代码

    char szLan[256] = { 0 };
    NET_DVR_THERMINTELL_PARAM struThermIntellCfg = { 0 };
    struThermIntellCfg.byIntellType = m_comIntellType.GetCurSel();

    struThermIntellCfg.dwSize = sizeof(struThermIntellCfg);

    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struThermIntellCfg;
    struCfg.dwInSize = sizeof(struThermIntellCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_THERMINTELL, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_THERMINTELL");
        sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_THERMINTELL");
    }
}


void CDlgFireDetection::OnBnClickedBtnGetThermintell()
{
    // TODO:  在此添加控件通知处理程序代码
    NET_DVR_THERMINTELL_PARAM struThermIntellCfg = { 0 };
    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &struThermIntellCfg;
    struCfg.dwOutSize = sizeof(struThermIntellCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_THERMINTELL, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_THERMINTELL");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_THERMINTELL");
    }
    m_comIntellType.SetCurSel(struThermIntellCfg.byIntellType);
}

void CDlgFireDetection::OnBnClickedBtnRegionCfg()
{
    CDlgRegionDetectCfg dlg;
    dlg.m_lChannel = m_lChannel;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}



void CDlgFireDetection::OnBnClickedBtnThermalPipCfg()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgThremalPipCfg dlg;
    dlg.m_lChannel = m_lChannel;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}


void CDlgFireDetection::OnBnClickedBtnSetThermometryMode()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    char szLan[256] = { 0 };
    NET_DVR_THERMOMETRY_MODE struThermModeCfg = { 0 };
    struThermModeCfg.byMode = m_cmbThermometryMode.GetCurSel();

    struThermModeCfg.dwSize = sizeof(struThermModeCfg);

    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struThermModeCfg;
    struCfg.dwInSize = sizeof(struThermModeCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_THERMOMETRY_MODE, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_THERMOMETRY_MODE");
        sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_THERMOMETRY_MODE");
    }
}


void CDlgFireDetection::OnBnClickedBtnGetThermometryMode()
{
    // TODO:  在此添加控件通知处理程序代码
    NET_DVR_THERMOMETRY_MODE struThermModeCfg = { 0 };
    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &struThermModeCfg;
    struCfg.dwOutSize = sizeof(struThermModeCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_THERMOMETRY_MODE, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_THERMOMETRY_MODE");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_THERMOMETRY_MODE");
    }
    m_cmbThermometryMode.SetCurSel(struThermModeCfg.byMode);
    UpdateData(FALSE);
}


void CDlgFireDetection::OnBnClickedBtnGetAlginfo()
{
    // TODO:  在此添加控件通知处理程序代码
    NET_DVR_THERMAL_ALGINFO struAlgInfo = { 0 };
    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &struAlgInfo;
    struCfg.dwOutSize = sizeof(struAlgInfo);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_THERMAL_ALGVERSION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_THERMAL_ALGVERSION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_THERMAL_ALGVERSION");
    }

    m_sThermAlgName.Format("%s", struAlgInfo.sThermometryAlgName);
    m_sShipsAlgName.Format("%s", struAlgInfo.sShipsAlgName);
    m_csFireAlgName.Format("%s", struAlgInfo.sFireAlgName);


    UpdateData(FALSE);
}


void CDlgFireDetection::OnBnClickedBtnFirescanStart()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    char szUrl[256] = { 0 };
    sprintf(szUrl, "GET /ISAPI/Thermal/channels/%d/fireScanStart", m_lChannel);
    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    

    char* lpOutputXml = NULL;
    lpOutputXml = new char[10 * 1024 * 1024];
    memset(lpOutputXml, 0, 10 * 1024 * 1024);
    struOuput.lpOutBuffer = lpOutputXml;
    struOuput.dwOutBufferSize = 10 * 1024 * 1024;



    if (!NET_DVR_STDXMLConfig(m_lServerID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, szUrl);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, szUrl);
    }

    if (NULL != lpOutputXml)
    {
        delete[]lpOutputXml;
        lpOutputXml = NULL;
    }

    UpdateData(FALSE);
}

