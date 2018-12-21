// DlgIPCSimpIntellCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgIPCSimpIntellCfg.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIPCSimpIntellCfg dialog

void CALLBACK AudioDecibelCB(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
	int i = *((int*)lpBuffer);
	CDlgIPCSimpIntellCfg *pDlg = (CDlgIPCSimpIntellCfg *)pUserData;
	pDlg->SetAudioDecibel(i);
}

void CALLBACK DrawVideoEpoliceAlertShow(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
    SetBkMode(hDc, TRANSPARENT);
    SetTextColor(hDc, RGB(255, 255, 255));

	CDlgIPCSimpIntellCfg *lp = (CDlgIPCSimpIntellCfg *)dwUser;
    lp->F_DrawFun(lRealHandle, hDc, dwUser);     
}

BOOL IsCrossLine( NET_VCA_POLYGON *struRuleRegion )
{
	//如果结构空，则不判断
	if(struRuleRegion == NULL)
	{
		return FALSE;
	}
	
	int i = 0, j = 0;
	DWORD dwPointTotal = 0;
	NET_VCA_POINT *pPointArray = NULL;
	bool    bCrossLine = FALSE;
	
	pPointArray = (NET_VCA_POINT *)struRuleRegion->struPos;
	dwPointTotal = struRuleRegion->dwPointNum;
	
    CString strTemp = "";
    if(dwPointTotal > 10)
    {
        strTemp.Format("dwPonitTotal is[%d]",dwPointTotal);
        ::AfxMessageBox(strTemp);
        return FALSE;
    }

	//如果小于最小个数3，不能构成框
	if (dwPointTotal == MIN_PNT_NUM)
	{
		bCrossLine = FALSE;
	}
	else
	{
		
		for(i=0; i<static_cast<int>(dwPointTotal-3); i++)
		{
			for(j=i+2; j<static_cast<int>(dwPointTotal-1); j++)
			{
				if(F_LineCrossDetect(pPointArray[i], pPointArray[i + 1], pPointArray[j], pPointArray[j + 1]))
				{
					bCrossLine = TRUE;
				}   
			}
		}
	}
	
	return bCrossLine;
}

BOOL F_LineCrossDetect( NET_VCA_POINT p1, NET_VCA_POINT p2, NET_VCA_POINT q1, NET_VCA_POINT q2 )
{
	NET_VCA_POINT p1_q1, q2_q1, p2_q1, q1_p1, p2_p1, q2_p1;       //Difference vector
    float z1, z2, z3, z4;
    BOOL  line_cross = FALSE;
    
    // p1 - q1;
    p1_q1.fX = p1.fX - q1.fX;
    p1_q1.fY = p1.fY - q1.fY;
    
    // q2 - q1;
    q2_q1.fX = q2.fX - q1.fX;
    q2_q1.fY = q2.fY - q1.fY;
    
    // p2 - q1;
    p2_q1.fX = p2.fX - q1.fX;
    p2_q1.fY = p2.fY - q1.fY;
    
    // 1 (p1 - q1) × (q2 - q1)；
    z1 = p1_q1.fX * q2_q1.fY - q2_q1.fX * p1_q1.fY; 
    
    // 2 (q2 - q1) × (p2 - q1)；
    z2 = q2_q1.fX * p2_q1.fY - p2_q1.fX * q2_q1.fY;
    
    // q1 - p1;
    q1_p1.fX = q1.fX - p1.fX;
    q1_p1.fY = q1.fY - p1.fY;
    
    // p2 - p1;
    p2_p1.fX = p2.fX - p1.fX;
    p2_p1.fY = p2.fY - p1.fY;
    
    // q2 - p1;
    q2_p1.fX = q2.fX - p1.fX;
    q2_p1.fY = q2.fY - p1.fY;
    
    // 3 (q1 - p1) × (p2 - p1)；
    z3 = q1_p1.fX * p2_p1.fY - p2_p1.fX * q1_p1.fY;
    
    //4 (p2 - p1) × (q2 - p1);
    z4 = p2_p1.fX * q2_p1.fY - q2_p1.fX * p2_p1.fY;
    
    
    //  check the span of two segment
    if( ((z1 >= 0.0f && z2 >= 0.0f) || (z1 < 0.0f && z2 < 0.0f)) && 
        ((z3 >= 0.0f && z4 >= 0.0f) || (z3 < 0.0f && z4 < 0.0f)))
    {
        line_cross = TRUE;	
    }else
    {
        line_cross = FALSE;
    }
    
    return line_cross;
}

BOOL IsValidArea( LPNET_VCA_POLYGON lpstruPolygon )
{
	if(lpstruPolygon == NULL)
    {
        return FALSE;
    }
    // 判断组成多边形的所有点是否在一条直线上
    if (F_IsStraightLine(lpstruPolygon))
    {
        char szLan[128] = {0};
        g_StringLanType(szLan, "所有点在同一直线上，不能组成多边形!",\
            "All points have been in the same line, not able to form the polygon");
        //AfxMessageBox(szLan);
        return FALSE;
    }
    // 判断组成多边形的终点和起点的连线与已有的直线是否有交叉
    if (F_IsACrossLine(lpstruPolygon))
    {
        char szLan[128] = {0};
        g_StringLanType(szLan,"终点和起点的连线与已有的直线相交，不能组成有效的多边形!", \
            "There are straight-line intersection, can not be composed of an effective polygon");
        //AfxMessageBox(szLan);
        return FALSE;
    }
    return TRUE;
}

BOOL F_IsStraightLine( NET_VCA_POLYGON *lpstruPolygon )
{
	if(lpstruPolygon == NULL)
    {
        return FALSE;
    }
    unsigned int i = 0;
    BOOL         bStraightLine;
    float        fSlope;
    float        fDistance;
    float        fCoefficient;
    float        fOffset;
    DWORD		 nPointTotal;
    NET_VCA_POINT *pPointArray;
    int          nXOffset;
    int          nYOffset;
    
    pPointArray = lpstruPolygon->struPos;
    nPointTotal = lpstruPolygon->dwPointNum;
    
    nXOffset = (int)(pPointArray[0].fX - pPointArray[1].fX);
    nYOffset = (int)(pPointArray[0].fY - pPointArray[1].fY);
    bStraightLine = TRUE;
    
    //Check if all points construct a vertical line.
    if (0 == nXOffset)
    {
        for (i = 2; i < nPointTotal; i++)
        {
            if (pPointArray[0].fX != pPointArray[i].fX)
            {
                bStraightLine = FALSE;
                break;
            }
        }
    }
    
    // Check if all points construct a horizontal line.
    if (0 == nYOffset)
    {
        for (i = 2; i < nPointTotal; i++)
        {
            if (pPointArray[0].fY != pPointArray[i].fY)
            {
                bStraightLine = FALSE;
                break;
            }                 
        }
    }
    
    // Check if all points construct a diagonal.
    if ((0 != nXOffset) && (0 != nYOffset))
    {
        // calculate slope
        fSlope  = 1.0f * nYOffset / nXOffset;
        // intercept 
        fOffset = pPointArray[0].fY - fSlope * pPointArray[1].fX;
        // the coefficient for calculating the distance between point and line. 
        fCoefficient = (float)sqrt(1.0 + fSlope * fSlope);
        
        for (i = 2; i < nPointTotal; i ++)
        {
            // Calculate the distance between other point and the line constructed by point 1 and point 2. 
            fDistance = (float)fabs(fSlope * pPointArray[i].fX - pPointArray[i].fY + fOffset)/fCoefficient;
            
            // if there is one distance of points that is more than 0, the polygon is valid.
            if ((fDistance - 0.0f) > 0.000001f)
            {
                bStraightLine = FALSE;
                break;
            }
        }		
    }
    
    return bStraightLine;	
}

BOOL F_IsACrossLine( NET_VCA_POLYGON *alarm_region )
{
	if(alarm_region == NULL)
    {
        return FALSE;
    }
    unsigned int i;
    DWORD	 nPointTotal;
    NET_VCA_POINT *pPointArray;
    NET_VCA_POINT *pPntArr;
    BOOL    bCrossLine;
    
    pPointArray = alarm_region->struPos;
    nPointTotal = alarm_region->dwPointNum;
    bCrossLine  = FALSE;
    
    
    if (nPointTotal == ITC_MAX_POLYGON_POINT_NUM)
    {
        bCrossLine = FALSE;
    }
    else
    {
        pPntArr = new NET_VCA_POINT[nPointTotal];
        if (pPntArr == NULL)
        {
            char szLan[128] = {0};
            g_StringLanType(szLan, "Allocate memory failed!","Memory allocation failure!");
            //AfxMessageBox(szLan);
            exit(EXIT_FAILURE);
        }
        
        for (i = 0; i < nPointTotal; i++)
        {
            pPntArr[i] = pPointArray[i];
        }
        //      pPntArr[nPointTotal] = pPointArray[0];
        
        for(i = 0; i < nPointTotal - 1; i++)
        {
            
            if (F_LineCrossDetect(pPntArr[0], pPntArr[nPointTotal - 1], pPntArr[i], pPntArr[i + 1]))
            {
                bCrossLine = TRUE;
            }			
        } 
        delete [] pPntArr;
    }
    return bCrossLine;
}

CDlgIPCSimpIntellCfg::CDlgIPCSimpIntellCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIPCSimpIntellCfg::IDD, pParent)
	, m_bChkInvokeAlarmOut(FALSE)
	, m_bChkInvokeJpegCapture(FALSE)
	, m_bChkPicToFtp(FALSE)
    , m_bChkPicToCloud(FALSE)
	, m_iHour11(0)
	, m_iMin11(0)
	, m_iHour12(0)
	, m_iMin12(0)
	, m_iHour21(0)
	, m_iMin21(0)
	, m_iHour22(0)
	, m_iMin22(0)
	, m_iHour31(0)
	, m_iMin31(0)
	, m_iHour32(0)
	, m_iMin32(0)
	, m_iHour41(0)
	, m_iMin41(0)
	, m_iHour42(0)
	, m_iMin42(0)
	, m_iHour51(0)
	, m_iMin51(0)
	, m_iHour52(0)
	, m_iMin52(0)
	, m_iHour61(0)
	, m_iMin61(0)
	, m_iHour62(0)
	, m_iMin62(0)
	, m_iHour71(0)
	, m_iMin71(0)
	, m_iHour72(0)
	, m_iMin72(0)
	, m_iHour81(0)
	, m_iMin81(0)
	, m_iHour82(0)
	, m_iMin82(0)
	, m_bChkUploadCenter(FALSE)
	, m_bChkMonitorAlarm(FALSE)
	, m_bChkVoiceAlarm(FALSE)
	, m_bChkEmapAlarmOut(FALSE)
	, m_bChkFocusAlarm(FALSE),
	m_lLoginID(-1),
	m_iDeviceIndex(-1),
	m_lChannel(-1),
	m_lPlayHandle(-1),
	m_iChanCount(0),
    m_iAnaChanCount(0),
	m_iDStartChannel(-1),
	m_lStartChannel(-1),
	m_bEnable(FALSE),
	m_bAudioAbnormal(FALSE),
	m_iAudioSen("0"),
	m_iAudioThreshold("0"),
	m_iLineSen("0"),
	m_iCross("0"),
	m_iFieldDuration("0"),
	m_iFieldRate("0"),
	m_iFieldSen("0"),
	m_iFieldNo(0),
	m_iLineNo(0),
	m_dwPosNum(0),
	m_bCloseIn(FALSE),
	m_bMouseMove(FALSE),
	m_bMouseMovePolygon(FALSE),
	m_lAudioHandle(-1),
    m_hRegisterDrawThread(NULL),
    m_nMaxWidth(0),
	m_nMaxHeight(0),
	m_bRecordChan(NULL),
	m_pbAlarmOut(NULL)
    , m_dwPreset(0)
    , m_bHumanMisFlineDetect(FALSE)
    , m_bHumanMisFFiledDetect(FALSE)
    , m_bHumanMisFRegionEDetect(FALSE)
    , m_bHumanMisFRegionExitDetect(FALSE)
    , m_strFaceLibID(_T(""))
    , m_bVehicleField(FALSE)
    , m_bVehicleLine(FALSE)
    , m_bVehicleEnter(FALSE)
    , m_bVehicleExit(FALSE)
    , m_bTraverseWhiteLightDurationTime(0)
    , m_bIntrusionWhiteLightDurationTime(0)
    , m_bTraverseDetTargetAll(FALSE)
    , m_bTraverseDetTargetHuman(FALSE)
    , m_bTraverseDetTargetVerhicle(FALSE)
    , m_bIntrusionDetTargetAll(FALSE)
    , m_bIntrusionDetTargetHuman(FALSE)
    , m_bIntrusionDetTargetVerhicle(FALSE)
    , m_iSensitivityLevel(0)
    , m_iDurationTime(0)
    , m_iMinTriggerTime(0)
    , m_iLinkageTime(0)
    , m_iFilterTime(0)
{
	//{{AFX_DATA_INIT(CDlgIPCSimpIntellCfg)
	m_bEnable = FALSE;
	m_bAudioAbnormal = FALSE;
	m_iAudioSen = "0";
	m_iAudioThreshold = "0";
	m_iMaxChan = 0;
	m_iUsedChan = 0;
	m_iLineSen = "0";
	m_iFieldDuration = "0";
	m_iFieldRate = "0";
	m_iFieldSen = "0";
	m_iCross = "0";
	m_iSceneSen = 0;
	m_bTraverseDualVca = FALSE;
	m_bFieldDetectionDualVca = FALSE;
	m_iDefocusSensortiveLevel = 0;
	m_bySensitivity = 0;
	m_bChkPTZAlarm = FALSE;
	m_byRegionEntrSensitivity = 0;
	m_nAttendedSensitivity = 0;
	m_nAttendedTimeThresgold = 0;
	m_nGroupObjectOccup = 0;
	m_nLoiterSensitivity = 0;
	m_nLoiterTimeThreshold = 0;
	m_nParkSensitivity = 0;
	m_nParkTimeThreshold = 0;
	m_nRapidMoveSensitivity = 0;
	m_nRegionExitSensitivity = 0;
	m_nUnattendedSensitivity = 0;
	m_nUnattendedTimeThreshold = 0;
    m_iZoneIndex = 0;
	m_nResolutionWidth = 0;
	m_nResolutionHeight = 0;
	m_bChkUnattendedBaggageTime = FALSE;
	m_bChkAttendedBaggageTime = FALSE;
	//}}AFX_DATA_INIT
	memset(&m_struHolidayHandle, 0, sizeof(m_struHolidayHandle));
	memset(&m_struPtzLockCfg, 0, sizeof(m_struPtzLockCfg));
	memset(&m_struPtzLockInfoCond, 0, sizeof(m_struPtzLockInfoCond));
	memset(&m_struPtzLockInfo, 0, sizeof(m_struPtzLockInfo));
    memset(&m_struRegionEntrDetection, 0, sizeof(m_struRegionEntrDetection));
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);

    memset(&m_struRegionEntrDetection, 0, sizeof(m_struRegionEntrDetection));
    memset(&m_struRegionExitDetection, 0, sizeof(m_struRegionExitDetection));
    memset(&m_struLoiterDetection, 0, sizeof(m_struLoiterDetection));
    memset(&m_struGroupDetection, 0, sizeof(m_struGroupDetection));
    memset(&m_struRapidMove, 0, sizeof(m_struRapidMove));
    memset(&m_struParkDetection, 0, sizeof(m_struParkDetection));
    memset(&m_struUnattended, 0, sizeof(m_struUnattended));
    memset(&m_struAttended, 0, sizeof(m_struAttended));
    memset(&m_struEventTrigger, 0, sizeof(m_struEventTrigger));
    memset(&m_struEventSchedule, 0, sizeof(m_struEventSchedule));
    memset(&m_struClipCfg, 0, sizeof(m_struClipCfg));
    memset(&m_bySceneID, 0, sizeof(BYTE) * MAX_DAYS * MAX_TIMESEGMENT_V30);
    m_pStruAlarmHandleType = NULL;
    m_bTraverseDetTarget = 1;
    m_bIntrusionDetTarget = 1;
}


void CDlgIPCSimpIntellCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgIPCSimpIntellCfg)
    DDX_Control(pDX, IDC_COMBO_TRAVERSE_DETTARGET, m_comTraverseDetTarget);
    DDX_Control(pDX, IDC_COMBO_RUN_DETTARGET, m_comRunDetTarget);
    DDX_Control(pDX, IDC_COMBO_INTRUSION_DETTARGET, m_comIntrusionDetTarget);
    DDX_Control(pDX, IDC_COMBO_EXIT_DETTARGET, m_comboExitDetTarget);
    DDX_Control(pDX, IDC_COMBO_ENTER_DETTARGET, m_comboEnterDetTarget);
    DDX_Control(pDX, IDC_CMB_CLIP_REGION_NO, m_cmbClipRegionNo);
    DDX_Control(pDX, IDC_CMB_STREAM_TYPE, m_cmbStreamType);
    DDX_Control(pDX, IDC_CMB_UNATTENDED_NO, m_cmbUnattendedNo);
    DDX_Control(pDX, IDC_CMB_RAPID_MOVE, m_cmbRapidMove);
    DDX_Control(pDX, IDC_CMB_PARK_NO, m_cmbParkNo);
    DDX_Control(pDX, IDC_CMB_LOITER_NO, m_cmbLoiterNo);
    DDX_Control(pDX, IDC_CMB_GROUP_NO, m_cmbGroupDetectionNo);
    DDX_Control(pDX, IDC_CMB_ATTENDED_NO, m_cmbAttendedNo);
    DDX_Control(pDX, IDC_CMB_REGION_EXIT_NO, m_cmbRegionExitNo);
    DDX_Control(pDX, IDC_CMB_REGION_ENTR_NO, m_cmbRegionEntrNo);
    DDX_Control(pDX, IDC_CMB_GROUPNO, m_cmbGroupNo);
    DDX_Control(pDX, IDC_COMBO_PTZ_LOCKSTATUS, m_comboPtzLockStatus);
    DDX_Control(pDX, IDC_COMBO_ENABLE, m_comEnable);
    DDX_Control(pDX, IDC_COMBO_REGION_ID, m_ComboRegionID);
    DDX_Control(pDX, IDC_COMBO_FIELDNO, m_Comnbo_FieldNo);
    DDX_Control(pDX, IDC_COMBO_LINENO, m_Combo_LineNo);
    DDX_Control(pDX, IDC_COMBO_CFG_TYPE, m_Combo_CfgType);
    DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cmbChannel);
    DDX_Control(pDX, IDC_PLAYWND, m_wndPlay);
    DDX_Control(pDX, IDC_TREE_ALARM_OUT, m_treeAlarmOut);
    DDX_Control(pDX, IDC_TREE_CHAN, m_treeChan);
    DDX_Control(pDX, IDC_COMBO_ALARMIN_WEEKDAY, m_comboWeekday);
    DDX_Control(pDX, IDC_COMBO_ALARMIN_COPY_TIME, m_comboCopyTime);
    DDX_Check(pDX, IDC_CHK_ALARMIN_MONITOR, m_bChkMonitorAlarm);
    DDX_Check(pDX, IDC_CHK_ALARMIN_VOICE, m_bChkVoiceAlarm);
    DDX_Check(pDX, IDC_CHK_ALARMIN_UPLOAD_CENTER, m_bChkUploadCenter);
    DDX_Check(pDX, IDC_CHK_ALARMIN_INVOKE_ALARMOUT, m_bChkInvokeAlarmOut);
    DDX_Check(pDX, IDC_CHK_INVOKE_JPEG_CAPTURE, m_bChkInvokeJpegCapture);
    DDX_Check(pDX, IDC_CHK_ALARM_EMAP, m_bChkEmapAlarmOut);
    DDX_Check(pDX, IDC_CHK_ALARM_FOCUS, m_bChkFocusAlarm);
    DDX_Text(pDX, IDC_EDIT_ZONE_ALARMIN, m_iZoneIndex);
    DDX_Text(pDX, IDC_EDIT_HOUR11, m_iHour11);
    DDX_Text(pDX, IDC_EDIT_MIN11, m_iMin11);
    DDX_Text(pDX, IDC_EDIT_HOUR12, m_iHour12);
    DDX_Text(pDX, IDC_EDIT_MIN12, m_iMin12);
    DDX_Text(pDX, IDC_EDIT_HOUR21, m_iHour21);
    DDX_Text(pDX, IDC_EDIT_MIN21, m_iMin21);
    DDX_Text(pDX, IDC_EDIT_HOUR22, m_iHour22);
    DDX_Text(pDX, IDC_EDIT_MIN22, m_iMin22);
    DDX_Text(pDX, IDC_EDIT_HOUR31, m_iHour31);
    DDX_Text(pDX, IDC_EDIT_MIN31, m_iMin31);
    DDX_Text(pDX, IDC_EDIT_HOUR32, m_iHour32);
    DDX_Text(pDX, IDC_EDIT_MIN32, m_iMin32);
    DDX_Text(pDX, IDC_EDIT_HOUR41, m_iHour41);
    DDX_Text(pDX, IDC_EDIT_MIN41, m_iMin41);
    DDX_Text(pDX, IDC_EDIT_HOUR42, m_iHour42);
    DDX_Text(pDX, IDC_EDIT_MIN42, m_iMin42);
    DDX_Text(pDX, IDC_EDIT_HOUR51, m_iHour51);
    DDX_Text(pDX, IDC_EDIT_MIN51, m_iMin51);
    DDX_Text(pDX, IDC_EDIT_HOUR52, m_iHour52);
    DDX_Text(pDX, IDC_EDIT_MIN52, m_iMin52);
    DDX_Text(pDX, IDC_EDIT_HOUR61, m_iHour61);
    DDX_Text(pDX, IDC_EDIT_MIN61, m_iMin61);
    DDX_Text(pDX, IDC_EDIT_HOUR62, m_iHour62);
    DDX_Text(pDX, IDC_EDIT_MIN62, m_iMin62);
    DDX_Text(pDX, IDC_EDIT_HOUR71, m_iHour71);
    DDX_Text(pDX, IDC_EDIT_MIN71, m_iMin71);
    DDX_Text(pDX, IDC_EDIT_HOUR72, m_iHour72);
    DDX_Text(pDX, IDC_EDIT_MIN72, m_iMin72);
    DDX_Text(pDX, IDC_EDIT_HOUR81, m_iHour81);
    DDX_Text(pDX, IDC_EDIT_MIN81, m_iMin81);
    DDX_Text(pDX, IDC_EDIT_HOUR82, m_iHour82);
    DDX_Text(pDX, IDC_EDIT_MIN82, m_iMin82);
    DDX_Check(pDX, IDC_CHK_PIC_FTP, m_bChkPicToFtp);
    DDX_Check(pDX, IDC_CHK_PIC_CLOUD, m_bChkPicToCloud);
    DDX_Check(pDX, IDC_CHK_LINE_DETECTION, m_bEnable);
    DDX_Check(pDX, IDC_CHK_AUDIOABNORMAL, m_bAudioAbnormal);
    DDX_Text(pDX, IDC_EDT_AUDIOSEN, m_iAudioSen);
    DDX_Text(pDX, IDC_EDT_THRESHOLD, m_iAudioThreshold);
    DDX_Text(pDX, IDC_EDT_LINESEN, m_iLineSen);
    DDX_Text(pDX, IDC_EDT_FIELDDURATION, m_iFieldDuration);
    DDX_Text(pDX, IDC_EDT_FIELDRATE, m_iFieldRate);
    DDX_Text(pDX, IDC_EDT_FIELDSEN, m_iFieldSen);
    DDX_Text(pDX, IDC_EDT_CROSS, m_iCross);
    DDX_Text(pDX, IDC_EDT_SCENESEN, m_iSceneSen);
    DDX_Check(pDX, IDC_CHK_TRAVERSE_DUAL_VCA, m_bTraverseDualVca);
    DDX_Check(pDX, IDC_CHK_FIELD_DETECION_DUAL_VCA, m_bFieldDetectionDualVca);
    DDX_Text(pDX, IDC_EDIT_DEFOCUS_SENSORTIVE, m_iDefocusSensortiveLevel);
    DDX_Text(pDX, IDC_EDT_SENSITIVITY, m_bySensitivity);
    DDX_Check(pDX, IDC_CHK_ALARM_PTZ, m_bChkPTZAlarm);
    DDX_Text(pDX, IDC_EDT_REGION_ENTR_SENSITIVITY, m_byRegionEntrSensitivity);
    DDX_Text(pDX, IDC_EDT_ATTENDED_SENSITIVITY, m_nAttendedSensitivity);
    DDX_Text(pDX, IDC_EDT_ATTENDED_TIME_THRESHOLD, m_nAttendedTimeThresgold);
    DDX_Text(pDX, IDC_EDT_GROUP_OBJECT_OCCUP, m_nGroupObjectOccup);
    DDX_Text(pDX, IDC_EDT_LOITER_SENSITIVITY, m_nLoiterSensitivity);
    DDX_Text(pDX, IDC_EDT_LOITER_TIME_THRESHOLD, m_nLoiterTimeThreshold);
    DDX_Text(pDX, IDC_EDT_PARK_SENSITIVITY, m_nParkSensitivity);
    DDX_Text(pDX, IDC_EDT_PARK_TIME_THRESHOLD, m_nParkTimeThreshold);
    DDX_Text(pDX, IDC_EDT_RAPID_MOVE_SENSITIVITY, m_nRapidMoveSensitivity);
    DDX_Text(pDX, IDC_EDT_REGION_EXIT_SENSITIVITY, m_nRegionExitSensitivity);
    DDX_Text(pDX, IDC_EDT_UNATTENDED_SENSITIVITY, m_nUnattendedSensitivity);
    DDX_Text(pDX, IDC_EDT_UNATTENDED_TIME_THRESHOLD, m_nUnattendedTimeThreshold);
    DDX_Text(pDX, IDC_EDIT_RESOLUTION_WIDTH, m_nResolutionWidth);
    DDX_Text(pDX, IDC_EDIT_RESOLUTION_HEIGHT, m_nResolutionHeight);
    DDX_Check(pDX, IDC_CHK_NEWTIMETHRESHOLDMODE, m_bChkUnattendedBaggageTime);
    DDX_Check(pDX, IDC_CHK_NEWTIMETHRESHOLDMODE2, m_bChkAttendedBaggageTime);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDT_PRESET, m_dwPreset);
    DDX_Control(pDX, IDC_COMBO_DIRECTION, m_combDirection);
    DDX_Check(pDX, IDC_CHECK1, m_bHumanMisFlineDetect);
    DDX_Check(pDX, IDC_CHECK2, m_bHumanMisFFiledDetect);
    DDX_Check(pDX, IDC_CHECK3, m_bHumanMisFRegionEDetect);
    DDX_Check(pDX, IDC_CHECK49, m_bHumanMisFRegionExitDetect);
    DDX_Text(pDX, IDC_EDIT3, m_strFaceLibID);
    DDX_Control(pDX, IDC_COMBO_SCENEID1, m_comSceneID1);
    DDX_Control(pDX, IDC_COMBO_SCENEID2, m_comSceneID2);
    DDX_Control(pDX, IDC_COMBO_SCENEID3, m_comSceneID3);
    DDX_Control(pDX, IDC_COMBO_SCENEID4, m_comSceneID4);
    DDX_Control(pDX, IDC_COMBO_SCENEID5, m_comSceneID5);
    DDX_Control(pDX, IDC_COMBO_SCENEID6, m_comSceneID6);
    DDX_Control(pDX, IDC_COMBO_SCENEID7, m_comSceneID7);
    DDX_Control(pDX, IDC_COMBO_SCENEID8, m_comSceneID8);
    DDX_Check(pDX, IDC_CHECK_VEHICLE_FIELD, m_bVehicleField);
    DDX_Check(pDX, IDC_CHECK_VEHICLE_LINE, m_bVehicleLine);
    DDX_Check(pDX, IDC_CHECK_VEHICLE_ENTER, m_bVehicleEnter);
    DDX_Check(pDX, IDC_CHECK_VEHICLE_EXIT, m_bVehicleExit);
    DDX_Text(pDX, IDC_EDIT_TRAVERSE_LIGHT_TIME, m_bTraverseWhiteLightDurationTime);
    DDX_Text(pDX, IDC_EDIT_INTRUSION_LIGHT_TIME, m_bIntrusionWhiteLightDurationTime);
    DDX_Check(pDX, IDC_CHECK_TRAVERSE_DETTARGET_ALL2, m_bTraverseDetTargetAll);
    DDX_Check(pDX, IDC_CHECK_TRAVERSE_DETTARGET_HUMAN2, m_bTraverseDetTargetHuman);
    DDX_Check(pDX, IDC_CHECK_TRAVERSE_DETTARGET_VEHICLE2, m_bTraverseDetTargetVerhicle);
    DDX_Check(pDX, IDC_CHECK_INTRUSION_DETTARGET_ALL, m_bIntrusionDetTargetAll);
    DDX_Check(pDX, IDC_CHECK_INTRUSION_DETTARGET_HUMAN, m_bIntrusionDetTargetHuman);
    DDX_Check(pDX, IDC_CHECK_INTRUSION_DETTARGET_VEHICLE, m_bIntrusionDetTargetVerhicle);
    DDX_Text(pDX, IDC_EDIT_GROUP_SENSITIVITY, m_iSensitivityLevel);
    DDX_Text(pDX, IDC_EDIT_GROUP_DURATION_TIME, m_iDurationTime);
    DDX_Text(pDX, IDC_EDIT_MINTRIGGER_NUMBER, m_iMinTriggerTime);
    DDX_Text(pDX, IDC_EDIT_GROUP_LINKAGE_TIME, m_iLinkageTime);
    DDX_Text(pDX, IDC_EDIT_GROUP_FILTER_TIME, m_iFilterTime);
}


BEGIN_MESSAGE_MAP(CDlgIPCSimpIntellCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgIPCSimpIntellCfg)
	ON_NOTIFY(NM_CLICK, IDC_TREE_CHAN, OnClickTreeChan)
	ON_BN_CLICKED(IDC_BTN_ALARM_IN_TIME_OK, OnBnClickedBtnAlarmInTimeOk)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARMIN_WEEKDAY, OnCbnSelchangeComboAlarminWeekday)
	ON_BN_CLICKED(IDC_BTN_ALARMIN_TIME_COPY, OnBnClickedBtnAlarminTimeCopy)
	ON_BN_CLICKED(IDC_CHK_ALARMIN_INVOKE_ALARMOUT, OnBnClickedChkAlarminInvokeAlarmout)
	ON_NOTIFY(NM_CLICK, IDC_TREE_ALARM_OUT, OnClickTreeAlarmOut)
	ON_CBN_SELCHANGE(IDC_COMBO_CFG_TYPE, OnCfgTypeChanged)
    ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL, OnChannelChanged)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_SAVECFG, OnBtnSavecfg)
    ON_BN_CLICKED(IDC_BTN_CANCELANDEXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_REFRESH,OnBtnRefresh)
    ON_CBN_SELCHANGE(IDC_COMBO_LINENO, OnLineNoChanged)
	ON_CBN_SELCHANGE(IDC_COMBO_FIELDNO, OnFieldNoChanged)
	ON_BN_CLICKED(IDC_BTN_CLEARPIC, OnBtnClearpic)
	ON_BN_CLICKED(IDC_BTN_PTZ_LOCKSTATUS_SET, OnBtnPtzLockstatusSet)
	ON_BN_CLICKED(IDC_BTN_REGION_ENTR_REFRESH, OnBtnRegionEntrRefresh)
	ON_BN_CLICKED(IDC_BTN_REGION_ENTR_SAVE, OnBtnRegionEntrSave)
	ON_BN_CLICKED(IDC_BTN_REGION_EXIT_REFRESH, OnBtnRegionExitRefresh)
	ON_BN_CLICKED(IDC_BTN_REGION_EXIT_SAVE, OnBtnRegionExitSave)
	ON_BN_CLICKED(IDC_BTN_LOITER_REFRESH, OnBtnLoiterRefresh)
	ON_BN_CLICKED(IDC_BTN_LOITER_SAVE, OnBtnLoiterSave)
	ON_BN_CLICKED(IDC_BTN_GROUP_REFRESH, OnBtnGroupRefresh)
	ON_BN_CLICKED(IDC_BTN_GROUP_SAVE, OnBtnGroupSave)
	ON_BN_CLICKED(IDC_BTN_RAPID_MOVE_REFRESH, OnBtnRapidMoveRefresh)
	ON_BN_CLICKED(IDC_BTN_RAPID_MOVE_SAVE, OnBtnRapidMoveSave)
	ON_BN_CLICKED(IDC_BTN_PARK_REFRESH, OnBtnParkRefresh)
	ON_BN_CLICKED(IDC_BTN_PARK_SAVE, OnBtnParkSave)
	ON_BN_CLICKED(IDC_BTN_UNATTENDED_REFRESH, OnBtnUnattendedRefresh)
	ON_BN_CLICKED(IDC_BTN_UNATTENDED_SAVE, OnBtnUnattendedSave)
	ON_BN_CLICKED(IDC_BTN_ATTENDED_REFRESH, OnBtnAttendedRefresh)
	ON_BN_CLICKED(IDC_BTN_ATTENDED_SAVE, OnBtnAttendedSave)
	ON_CBN_SELCHANGE(IDC_CMB_ATTENDED_NO, OnSelchangeCmbAttendedNo)
	ON_CBN_SELCHANGE(IDC_CMB_GROUP_NO, OnSelchangeCmbGroupNo)
	ON_CBN_SELCHANGE(IDC_CMB_LOITER_NO, OnSelchangeCmbLoiterNo)
	ON_CBN_SELCHANGE(IDC_CMB_PARK_NO, OnSelchangeCmbParkNo)
	ON_CBN_SELCHANGE(IDC_CMB_RAPID_MOVE, OnSelchangeCmbRapidMove)
	ON_CBN_SELCHANGE(IDC_CMB_REGION_ENTR_NO, OnSelchangeCmbRegionEntrNo)
	ON_CBN_SELCHANGE(IDC_CMB_REGION_EXIT_NO, OnSelchangeCmbRegionExitNo)
	ON_CBN_SELCHANGE(IDC_CMB_UNATTENDED_NO, OnSelchangeCmbUnattendedNo)
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY(NM_CLICK, IDC_TREE_CHAN, OnClickTreeChan)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

DWORD  fRegisterDrawFun(LPVOID pParam)
{
    CDlgIPCSimpIntellCfg *pIPCSimpInterllCfg = (CDlgIPCSimpIntellCfg *)pParam;
    while (1)
    {
        if (!NET_DVR_RigisterDrawFun(pIPCSimpInterllCfg->m_lPlayHandle,  DrawVideoEpoliceAlertShow , (DWORD)pParam)) 
        {
            Sleep(1000);            
            continue;       
        }
        else
        {
            int nPlayerIndex = NET_DVR_GetRealPlayerIndex(pIPCSimpInterllCfg->m_lPlayHandle);
            PlayM4_GetPictureSize(nPlayerIndex, &pIPCSimpInterllCfg->m_nMaxWidth, &pIPCSimpInterllCfg->m_nMaxHeight);
            break;
        }
    }
    return FALSE;
}

//************************************
// Method:    Play
// FullName:  CDlgIPCSimpIntellCfg::Play
// Access:    protected 
// Returns:   void
// Qualifier:
//************************************
void CDlgIPCSimpIntellCfg::Play()
{
	char szLan[128] = {0};
	char szTemp[256] = {0};
    NET_DVR_PREVIEWINFO struPreviewInfo = {0};
	
    struPreviewInfo.hPlayWnd = GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
    struPreviewInfo.lChannel = m_lChannel;

// 	if (m_Combo_CfgType.GetCurSel() == 13)
// 	{
//         struPreviewInfo.dwStreamType = m_cmbStreamType.GetCurSel();
// 	}
    if (struPreviewInfo.lChannel < 1)
    {
        struPreviewInfo.lChannel = 1;
	}

	if (m_lPlayHandle >= 0)
	{
        NET_DVR_RigisterDrawFun(m_lPlayHandle,  NULL ,0);        
		NET_DVR_StopRealPlay(m_lPlayHandle);
		m_lPlayHandle = -1;
	}
	
	m_lPlayHandle =  NET_DVR_RealPlay_V40(m_lLoginID, &struPreviewInfo, NULL, NULL); 

	if (m_lPlayHandle < 0)
	{
		g_StringLanType(szLan, "预览失败", "Realplay failed");
		sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
       // AfxMessageBox(szTemp);
		return ;
	}

//     while (1)
//     {
//         if (!NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawVideoEpoliceAlertShow, (DWORD)this)) 
//         {
//             continue;
//         }
//         else
//         {
//             break;
//         }
//     }

    DWORD dwThreadId = 0;
    if (m_hRegisterDrawThread != NULL)
    {
        TerminateThread(m_hRegisterDrawThread, 0);
        CloseHandle(m_hRegisterDrawThread);
        m_hRegisterDrawThread = NULL;
    }
    
    if (m_hRegisterDrawThread == NULL)
    {
        m_hRegisterDrawThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(fRegisterDrawFun),this,0,&dwThreadId);
    }

   
	
// 	NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawRoiDetectShow, 0);
	
}

BOOL CDlgIPCSimpIntellCfg::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWnd);

	m_Combo_CfgType.SetCurSel(0);
	m_Combo_LineNo.SetCurSel(0);
	m_Comnbo_FieldNo.SetCurSel(0);
    m_cmbRegionEntrNo.SetCurSel(0);
    m_cmbRegionExitNo.SetCurSel(0);
    m_cmbLoiterNo.SetCurSel(0);
    m_cmbGroupDetectionNo.SetCurSel(0);
    m_cmbParkNo.SetCurSel(0);
    m_cmbRapidMove.SetCurSel(0);
    m_cmbAttendedNo.SetCurSel(0);
    m_cmbUnattendedNo.SetCurSel(0);
    m_cmbClipRegionNo.SetCurSel(0);
    m_cmbStreamType.SetCurSel(2);
	m_bRecordChan = new BOOL[MAX_CHANNUM_V40];
	if(m_bRecordChan != NULL)
	{
		memset(m_bRecordChan,0,sizeof(BOOL) * MAX_CHANNUM_V40);
	}

	m_pStruAlarmHandleType = new NET_DVR_HANDLEEXCEPTION_V41;
	if (m_pStruAlarmHandleType != NULL)
	{
		memset(m_pStruAlarmHandleType,0,sizeof(NET_DVR_HANDLEEXCEPTION_V41));
		memset(m_pStruAlarmHandleType->dwRelAlarmOut,0xff,sizeof(DWORD)*MAX_ALARMOUT_V40);
	}

	m_pbAlarmOut = new BOOL[MAX_ALARMOUT_V40];

	if(m_pbAlarmOut != NULL)
	{
		memset(m_pbAlarmOut,0,sizeof(BOOL) * MAX_ALARMOUT_V40);
	}
    //Add Channel Info 
    AddChanInfo();
    //m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    AddGroupNoInfo();
	m_bCloseIn = TRUE;//Polygon is closed or not

	m_bMouseMove = FALSE;

	OnCfgTypeChanged();

//	Play();
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDlgIPCSimpIntellCfg message handlers

void CDlgIPCSimpIntellCfg::OnClickTreeChan(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);
	CPoint pt(0,0);
	CRect rc(0,0,0,0);
	GetCursorPos(&pt);
	GetDlgItem(IDC_TREE_CHAN)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	ScreenToClient(&pt);
	pt.x = pt.x - rc.left;
	pt.y = pt.y - rc.top;
	
	UINT uFlag = 0;
	HTREEITEM hSelect = m_treeChan.HitTest(pt, &uFlag);
	
	if (NULL == hSelect) 
	{
		return;
	}
	m_treeChan.SelectItem(hSelect);
	DWORD dwIndex = m_treeChan.GetItemData(hSelect)%1000;
	BOOL bCheck = m_treeChan.GetCheck(hSelect);
	m_bRecordChan[dwIndex - 1] = !bCheck;
	//switch checkbox status on click
	if (uFlag != LVHT_TOLEFT)
	{
		m_treeChan.SetCheck(hSelect, !bCheck);
	}
	else
	{
		m_treeChan.SetCheck(hSelect, bCheck);
	}
	
	*pResult = 0;
}

void CDlgIPCSimpIntellCfg::OnBnClickedBtnAlarmInTimeOk()
{
    UpdateData(TRUE);
    if (!TimeTest())
    {
        return;
    }
    int	i = m_comboWeekday.GetCurSel();	
    if (i == 7)
    {
        m_struHolidayHandle.struAlarmTime[0].byStartHour = (BYTE)m_iHour11;
        m_struHolidayHandle.struAlarmTime[0].byStartMin = (BYTE)m_iMin11;
        m_struHolidayHandle.struAlarmTime[0].byStopHour = (BYTE)m_iHour12;
        m_struHolidayHandle.struAlarmTime[0].byStopMin = (BYTE)m_iMin12;
        m_struHolidayHandle.struAlarmTime[1].byStartHour = (BYTE)m_iHour21;
        m_struHolidayHandle.struAlarmTime[1].byStartMin = (BYTE)m_iMin21;
        m_struHolidayHandle.struAlarmTime[1].byStopHour = (BYTE)m_iHour22;
        m_struHolidayHandle.struAlarmTime[1].byStopMin = (BYTE)m_iMin22;
        m_struHolidayHandle.struAlarmTime[2].byStartHour = (BYTE)m_iHour31;
        m_struHolidayHandle.struAlarmTime[2].byStartMin = (BYTE)m_iMin31;
        m_struHolidayHandle.struAlarmTime[2].byStopHour = (BYTE)m_iHour32;
        m_struHolidayHandle.struAlarmTime[2].byStopMin = (BYTE)m_iMin32;
        m_struHolidayHandle.struAlarmTime[3].byStartHour = (BYTE)m_iHour41;
        m_struHolidayHandle.struAlarmTime[3].byStartMin = (BYTE)m_iMin41;
        m_struHolidayHandle.struAlarmTime[3].byStopHour = (BYTE)m_iHour42;
        m_struHolidayHandle.struAlarmTime[3].byStopMin = (BYTE)m_iMin42;
        
        m_struHolidayHandle.struAlarmTime[4].byStartHour = (BYTE)m_iHour51;
        m_struHolidayHandle.struAlarmTime[4].byStartMin = (BYTE)m_iMin51;
        m_struHolidayHandle.struAlarmTime[4].byStopHour = (BYTE)m_iHour52;
        m_struHolidayHandle.struAlarmTime[4].byStopMin = (BYTE)m_iMin52;
        m_struHolidayHandle.struAlarmTime[5].byStartHour = (BYTE)m_iHour61;
        m_struHolidayHandle.struAlarmTime[5].byStartMin = (BYTE)m_iMin61;
        m_struHolidayHandle.struAlarmTime[5].byStopHour = (BYTE)m_iHour62;
        m_struHolidayHandle.struAlarmTime[5].byStopMin = (BYTE)m_iMin62;
        m_struHolidayHandle.struAlarmTime[6].byStartHour = (BYTE)m_iHour71;
        m_struHolidayHandle.struAlarmTime[6].byStartMin = (BYTE)m_iMin71;
        m_struHolidayHandle.struAlarmTime[6].byStopHour = (BYTE)m_iHour72;
        m_struHolidayHandle.struAlarmTime[6].byStopMin = (BYTE)m_iMin72;
        m_struHolidayHandle.struAlarmTime[7].byStartHour = (BYTE)m_iHour81;
        m_struHolidayHandle.struAlarmTime[7].byStartMin = (BYTE)m_iMin81;
        m_struHolidayHandle.struAlarmTime[7].byStopHour = (BYTE)m_iHour82;
        m_struHolidayHandle.struAlarmTime[7].byStopMin = (BYTE)m_iMin82;
        
    }
    else
    {
        m_struAlarmTime[i][0].byStartHour = (BYTE)m_iHour11;
        m_struAlarmTime[i][0].byStartMin = (BYTE)m_iMin11;
        m_struAlarmTime[i][0].byStopHour = (BYTE)m_iHour12;
        m_struAlarmTime[i][0].byStopMin = (BYTE)m_iMin12;
        m_struAlarmTime[i][1].byStartHour = (BYTE)m_iHour21;
        m_struAlarmTime[i][1].byStartMin = (BYTE)m_iMin21;
        m_struAlarmTime[i][1].byStopHour = (BYTE)m_iHour22;
        m_struAlarmTime[i][1].byStopMin = (BYTE)m_iMin22;
        m_struAlarmTime[i][2].byStartHour = (BYTE)m_iHour31;
        m_struAlarmTime[i][2].byStartMin = (BYTE)m_iMin31;
        m_struAlarmTime[i][2].byStopHour = (BYTE)m_iHour32;
        m_struAlarmTime[i][2].byStopMin = (BYTE)m_iMin32;
        m_struAlarmTime[i][3].byStartHour = (BYTE)m_iHour41;
        m_struAlarmTime[i][3].byStartMin = (BYTE)m_iMin41;
        m_struAlarmTime[i][3].byStopHour = (BYTE)m_iHour42;
        m_struAlarmTime[i][3].byStopMin = (BYTE)m_iMin42;
        m_struAlarmTime[i][4].byStartHour = (BYTE)m_iHour51;
        m_struAlarmTime[i][4].byStartMin = (BYTE)m_iMin51;
        m_struAlarmTime[i][4].byStopHour = (BYTE)m_iHour52;
        m_struAlarmTime[i][4].byStopMin = (BYTE)m_iMin52;
        m_struAlarmTime[i][5].byStartHour = (BYTE)m_iHour61;
        m_struAlarmTime[i][5].byStartMin = (BYTE)m_iMin61;
        m_struAlarmTime[i][5].byStopHour = (BYTE)m_iHour62;
        m_struAlarmTime[i][5].byStopMin = (BYTE)m_iMin62;
        m_struAlarmTime[i][6].byStartHour = (BYTE)m_iHour71;
        m_struAlarmTime[i][6].byStartMin = (BYTE)m_iMin71;
        m_struAlarmTime[i][6].byStopHour = (BYTE)m_iHour72;
        m_struAlarmTime[i][6].byStopMin = (BYTE)m_iMin72;
        m_struAlarmTime[i][7].byStartHour = (BYTE)m_iHour81;
        m_struAlarmTime[i][7].byStartMin = (BYTE)m_iMin81;
        m_struAlarmTime[i][7].byStopHour = (BYTE)m_iHour82;
        m_struAlarmTime[i][7].byStopMin = (BYTE)m_iMin82;

        m_bySceneID[i][0] = (BYTE)m_comSceneID1.GetCurSel();
        m_bySceneID[i][1] = (BYTE)m_comSceneID2.GetCurSel();
        m_bySceneID[i][2] = (BYTE)m_comSceneID3.GetCurSel();
        m_bySceneID[i][3] = (BYTE)m_comSceneID4.GetCurSel();
        m_bySceneID[i][4] = (BYTE)m_comSceneID5.GetCurSel();
        m_bySceneID[i][5] = (BYTE)m_comSceneID6.GetCurSel();
        m_bySceneID[i][6] = (BYTE)m_comSceneID7.GetCurSel();
        m_bySceneID[i][7] = (BYTE)m_comSceneID8.GetCurSel();

    }
	GetDlgItem(IDC_BTN_ALARMIN_TIME_COPY)->EnableWindow(TRUE);
}

BOOL CDlgIPCSimpIntellCfg::TimeTest()
{
	int i = 0;
	int j = 0;
	WORD wStartTime[MAX_TIMESEGMENT_V30], wStopTime[MAX_TIMESEGMENT_V30];
	char szLan[1024] = {0};
	UpdateData(TRUE);
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
		return FALSE;
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
		return FALSE;
	}
	wStartTime[0] = (WORD)(m_iHour11 * 100 + m_iMin11);
	wStartTime[1] = (WORD)(m_iHour21 * 100 + m_iMin21);
	wStartTime[2] = (WORD)(m_iHour31 * 100 + m_iMin31);
	wStartTime[3] = (WORD)(m_iHour41 * 100 + m_iMin41);
	wStopTime[0] = (WORD)(m_iHour12 * 100 + m_iMin12);
	wStopTime[1] = (WORD)(m_iHour22 * 100 + m_iMin22);
	wStopTime[2] = (WORD)(m_iHour32 * 100 + m_iMin32);
	wStopTime[3] = (WORD)(m_iHour42 * 100 + m_iMin42);
	wStartTime[4] = (WORD)(m_iHour51 * 100 + m_iMin51);
	wStartTime[5] = (WORD)(m_iHour61 * 100 + m_iMin61);
	wStartTime[6] = (WORD)(m_iHour71 * 100 + m_iMin71);
	wStartTime[7] = (WORD)(m_iHour81 * 100 + m_iMin81);
	wStopTime[4] = (WORD)(m_iHour52 * 100 + m_iMin52);
	wStopTime[5] = (WORD)(m_iHour62 * 100 + m_iMin62);
	wStopTime[6] = (WORD)(m_iHour72 * 100 + m_iMin72);
	wStopTime[7] = (WORD)(m_iHour82 * 100 + m_iMin82);
	for (i = 0; i < MAX_TIMESEGMENT_V30; i++)
	{
		if ((wStartTime[i] > 2400) || (wStopTime[i] > 2400))
		{
			g_StringLanType(szLan, "布防时间不能超过24:00", "Fortify time can not be more than 24:00");
			AfxMessageBox(szLan);
			return FALSE;
		}
		if (wStartTime[i] > wStopTime[i])
		{
			g_StringLanType(szLan, "布防起始时间不能大于停止时间", "Fortify start time can not be larger than the record to stop time");
			AfxMessageBox(szLan);
			return FALSE;
		}
		for (j = 0; j < MAX_TIMESEGMENT_V30; j++)
		{
			if (i == j)
			{
				continue;
			}
			if ((wStartTime[i] > wStartTime[j]) && (wStartTime[i] < wStopTime[j]) ||	\
				(wStopTime[i] > wStartTime[j]) && (wStopTime[i] < wStopTime[j]))
            {
				g_StringLanType(szLan, "时间段不能重复", "time can not be repeated");
				AfxMessageBox(szLan);
				return FALSE;
			}
		}
	}

	return TRUE;
}

void CDlgIPCSimpIntellCfg::OnCbnSelchangeComboAlarminWeekday()
{
	UpdateData(TRUE);
	int	i = m_comboWeekday.GetCurSel();	
    if (i == 7)
    {
        m_iHour11 = m_struHolidayHandle.struAlarmTime[0].byStartHour;
        m_iMin11 = m_struHolidayHandle.struAlarmTime[0].byStartMin;
        m_iHour12 = m_struHolidayHandle.struAlarmTime[0].byStopHour;
        m_iMin12 = m_struHolidayHandle.struAlarmTime[0].byStopMin;
        m_iHour21 = m_struHolidayHandle.struAlarmTime[1].byStartHour;
        m_iMin21 = m_struHolidayHandle.struAlarmTime[1].byStartMin;
        m_iHour22 = m_struHolidayHandle.struAlarmTime[1].byStopHour;
        m_iMin22 = m_struHolidayHandle.struAlarmTime[1].byStopMin;
        m_iHour31 = m_struHolidayHandle.struAlarmTime[2].byStartHour;
        m_iMin31 = m_struHolidayHandle.struAlarmTime[2].byStartMin;
        m_iHour32 = m_struHolidayHandle.struAlarmTime[2].byStopHour;
        m_iMin32 = m_struHolidayHandle.struAlarmTime[2].byStopMin;
        m_iHour41 = m_struHolidayHandle.struAlarmTime[3].byStartHour;
        m_iMin41 = m_struHolidayHandle.struAlarmTime[3].byStartMin;
        m_iHour42 = m_struHolidayHandle.struAlarmTime[3].byStopHour;
        m_iMin42 = m_struHolidayHandle.struAlarmTime[3].byStopMin;
        m_iHour51 = m_struHolidayHandle.struAlarmTime[4].byStartHour;
        m_iMin51 = m_struHolidayHandle.struAlarmTime[4].byStartMin;
        m_iHour52 = m_struHolidayHandle.struAlarmTime[4].byStopHour;
        m_iMin52 = m_struHolidayHandle.struAlarmTime[4].byStopMin;
        m_iHour61 = m_struHolidayHandle.struAlarmTime[5].byStartHour;
        m_iMin61 = m_struHolidayHandle.struAlarmTime[5].byStartMin;
        m_iHour62 = m_struHolidayHandle.struAlarmTime[5].byStopHour;
        m_iMin62 = m_struHolidayHandle.struAlarmTime[5].byStopMin;
        m_iHour71 = m_struHolidayHandle.struAlarmTime[6].byStartHour;
        m_iMin71 = m_struHolidayHandle.struAlarmTime[6].byStartMin;
        m_iHour72 = m_struHolidayHandle.struAlarmTime[6].byStopHour;
        m_iMin72 = m_struHolidayHandle.struAlarmTime[6].byStopMin;
        m_iHour81 = m_struHolidayHandle.struAlarmTime[7].byStartHour;
        m_iMin81 = m_struHolidayHandle.struAlarmTime[7].byStartMin;
        m_iHour82 = m_struHolidayHandle.struAlarmTime[7].byStopHour;
        m_iMin82 = m_struHolidayHandle.struAlarmTime[7].byStopMin;
    }
    else
    {
        m_iHour11 = m_struAlarmTime[i][0].byStartHour;
        m_iMin11 = m_struAlarmTime[i][0].byStartMin;
        m_iHour12 =m_struAlarmTime[i][0].byStopHour;
        m_iMin12 = m_struAlarmTime[i][0].byStopMin;
        m_iHour21 = m_struAlarmTime[i][1].byStartHour;
        m_iMin21 = m_struAlarmTime[i][1].byStartMin;
        m_iHour22 = m_struAlarmTime[i][1].byStopHour;
        m_iMin22 = m_struAlarmTime[i][1].byStopMin;
        m_iHour31 = m_struAlarmTime[i][2].byStartHour;
        m_iMin31 = m_struAlarmTime[i][2].byStartMin;
        m_iHour32 = m_struAlarmTime[i][2].byStopHour;
        m_iMin32 = m_struAlarmTime[i][2].byStopMin;
        m_iHour41 = m_struAlarmTime[i][3].byStartHour;
        m_iMin41 = m_struAlarmTime[i][3].byStartMin;
        m_iHour42 = m_struAlarmTime[i][3].byStopHour;
        m_iMin42 = m_struAlarmTime[i][3].byStopMin;
        m_iHour51 = m_struAlarmTime[i][4].byStartHour;
        m_iMin51 = m_struAlarmTime[i][4].byStartMin;
        m_iHour52 = m_struAlarmTime[i][4].byStopHour;
        m_iMin52 = m_struAlarmTime[i][4].byStopMin;
        m_iHour61 = m_struAlarmTime[i][5].byStartHour;
        m_iMin61 = m_struAlarmTime[i][5].byStartMin;
        m_iHour62 = m_struAlarmTime[i][5].byStopHour;
        m_iMin62 = m_struAlarmTime[i][5].byStopMin;
        m_iHour71 = m_struAlarmTime[i][6].byStartHour;
        m_iMin71 = m_struAlarmTime[i][6].byStartMin;
        m_iHour72 = m_struAlarmTime[i][6].byStopHour;
        m_iMin72 = m_struAlarmTime[i][6].byStopMin;
        m_iHour81 = m_struAlarmTime[i][7].byStartHour;
        m_iMin81 = m_struAlarmTime[i][7].byStartMin;
        m_iHour82 = m_struAlarmTime[i][7].byStopHour;
    	m_iMin82 = m_struAlarmTime[i][7].byStopMin;

        m_comSceneID1.SetCurSel(m_bySceneID[i][0]);
        m_comSceneID2.SetCurSel(m_bySceneID[i][1]);
        m_comSceneID3.SetCurSel(m_bySceneID[i][2]);
        m_comSceneID4.SetCurSel(m_bySceneID[i][3]);
        m_comSceneID5.SetCurSel(m_bySceneID[i][4]);
        m_comSceneID6.SetCurSel(m_bySceneID[i][5]);
        m_comSceneID7.SetCurSel(m_bySceneID[i][6]);
        m_comSceneID8.SetCurSel(m_bySceneID[i][7]);

    }
	
	UpdateData(FALSE);
}

void CDlgIPCSimpIntellCfg::ShowData()
{
	UpdateData(TRUE);
	int i = 0;
	m_bChkMonitorAlarm = m_pStruAlarmHandleType->dwHandleType &0x01;
	m_bChkVoiceAlarm = (m_pStruAlarmHandleType->dwHandleType>>1)&0x01;
	m_bChkUploadCenter = (m_pStruAlarmHandleType->dwHandleType>>2)&0x01;
	m_bChkInvokeAlarmOut = (m_pStruAlarmHandleType->dwHandleType>>3)&0x01;
	m_bChkInvokeJpegCapture = (m_pStruAlarmHandleType->dwHandleType>>4)&0x01;
	m_bChkEmapAlarmOut = (m_pStruAlarmHandleType->dwHandleType>>6)&0x01;
	m_bChkPicToFtp = (m_pStruAlarmHandleType->dwHandleType>>9)&0x01;
    m_bChkPicToCloud = (m_pStruAlarmHandleType->dwHandleType >> 12) & 0x01;
	m_bChkFocusAlarm = (m_pStruAlarmHandleType->dwHandleType>>10)&0x01;
	m_bChkPTZAlarm = (m_pStruAlarmHandleType->dwHandleType>>11)&0x01;

	m_treeAlarmOut.EnableWindow(m_bChkInvokeAlarmOut);
	memset(m_pbAlarmOut, FALSE, MAX_ALARMOUT_V40);

	for (i = 0; i < MAX_ALARMOUT_V40; i++)
	{
		if (m_pStruAlarmHandleType->dwRelAlarmOut[i] != 0xffffffff)
		{
			m_pbAlarmOut[m_pStruAlarmHandleType->dwRelAlarmOut[i]] = 1;
		}        
	}
 
	//以下是音频异常专有
	m_bAudioAbnormal = m_struAudioException.struAudioAbnormal.byEnable;
	m_iAudioSen.Format("%d", m_struAudioException.struAudioAbnormal.bySensitivity);
	m_iAudioThreshold.Format("%d", m_struAudioException.struAudioAbnormal.byThreshold);
//	m_iAudioSen = m_struAudioException.struAudioAbnormal.bySensitivity;
	//m_iAudioThreshold = m_struAudioException.struAudioAbnormal.byThreshold;

	m_iLineSen.Format("%d", m_struLineDetection.struAlertParam[m_Combo_LineNo.GetCurSel()].bySensitivity);
//	m_iLineSen = m_struLineDetection.struAlertParam[m_Combo_LineNo.GetCurSel()].bySensitivity;
	m_iCross.Format("%d", m_struLineDetection.struAlertParam[m_Combo_LineNo.GetCurSel()].dwCrossDirection);
//	m_iCross = m_struLineDetection.struAlertParam[m_Combo_LineNo.GetCurSel()].dwCrossDirection;
    m_bTraverseWhiteLightDurationTime = m_struLineDetection.struHandleException.byWhiteLightDurationTime;
	//区域入侵
	m_iFieldSen.Format("%d", m_struFieldDetection.struIntrusion[m_Comnbo_FieldNo.GetCurSel()].bySensitivity);
//	m_iFieldSen = m_struFieldDetection.struIntrusion[m_Comnbo_FieldNo.GetCurSel()].bySensitivity;
	m_iFieldRate.Format("%d", m_struFieldDetection.struIntrusion[m_Comnbo_FieldNo.GetCurSel()].byRate);
//	m_iFieldRate = m_struFieldDetection.struIntrusion[m_Comnbo_FieldNo.GetCurSel()].byRate;
	m_iFieldDuration.Format("%d", m_struFieldDetection.struIntrusion[m_Comnbo_FieldNo.GetCurSel()].wDuration);
//	m_iFieldDuration = m_struFieldDetection.struIntrusion[m_Comnbo_FieldNo.GetCurSel()].wDuration;
    m_bIntrusionWhiteLightDurationTime = m_struFieldDetection.struHandleException.byWhiteLightDurationTime;

    m_bIntrusionDetTargetAll = FALSE;
    m_bIntrusionDetTargetHuman = FALSE;
    m_bIntrusionDetTargetVerhicle = FALSE;
    if (!m_struFieldDetection.struIntrusion[m_Comnbo_FieldNo.GetCurSel()].byDetectionTarget)
    {
        m_bIntrusionDetTargetAll = true;
    }
    else
    {
        m_bIntrusionDetTargetHuman = m_struFieldDetection.struIntrusion[m_Comnbo_FieldNo.GetCurSel()].byDetectionTarget & 1;
        m_bIntrusionDetTargetVerhicle = (m_struFieldDetection.struIntrusion[m_Comnbo_FieldNo.GetCurSel()].byDetectionTarget >> 1) & 1;
    }
    m_bTraverseDetTargetAll = FALSE;
    m_bTraverseDetTargetHuman = FALSE;
    m_bTraverseDetTargetVerhicle = FALSE;
	//m_comIntrusionDetTarget.SetCurSel(m_struFieldDetection.struIntrusion[m_Comnbo_FieldNo.GetCurSel()].byDetectionTarget);
    if (!m_struLineDetection.struAlertParam[m_Combo_LineNo.GetCurSel()].byDetectionTarget)
    {
        m_bTraverseDetTargetAll = true;
    }
    else
    {
        m_bTraverseDetTargetHuman = m_struLineDetection.struAlertParam[m_Combo_LineNo.GetCurSel()].byDetectionTarget & 1;
        m_bTraverseDetTargetVerhicle = (m_struLineDetection.struAlertParam[m_Combo_LineNo.GetCurSel()].byDetectionTarget >> 1) & 1;
    }
	//m_comTraverseDetTarget.SetCurSel(m_struLineDetection.struAlertParam[m_Combo_LineNo.GetCurSel()].byDetectionTarget);

	//2013-07-17 场景更变侦测
	m_iSceneSen = m_struSceneDetection.bySensitiveLevel;

	CreateTree();
	UpdateData(FALSE);
	m_comboWeekday.SetCurSel(0);
	m_comboCopyTime.SetCurSel(0);
	OnCbnSelchangeComboAlarminWeekday();
//	GetDlgItem(IDC_BTN_ALARMIN_OK)->EnableWindow(TRUE);	

	if (m_lPlayHandle  < 0)
	{
	//	Play();
	}

    if (m_Combo_CfgType.GetCurSel() == 3)
    {
        if (m_lAudioHandle < 0)
        {
            NET_DVR_INPUTVOLUME struInputVolume = {0};
            struInputVolume.dwSize = sizeof(NET_DVR_INPUTVOLUME);
            struInputVolume.byAudioInputChan = m_lChannel;
            m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
            m_lAudioHandle = NET_DVR_StartRemoteConfig(m_lLoginID, NET_DVR_START_GET_INPUTVOLUME, &struInputVolume, sizeof(struInputVolume), AudioDecibelCB, this);
	    }
    }
	

	return;
}

void CDlgIPCSimpIntellCfg::OnBnClickedBtnAlarminTimeCopy()
{
	UpdateData(TRUE);
	int j,k;
	int i = m_comboWeekday.GetCurSel();
	int m_nCopyTime = m_comboCopyTime.GetCurSel() - 1;
	m_struLineDetection.dwSize = sizeof(m_struLineDetection);

	if (m_nCopyTime == -1)
	{
		for (j=0; j<MAX_DAYS; j++)
		{
			if (j == i)
			{
				continue;
			}
			for (k=0; k<MAX_TIMESEGMENT_V30; k++)
			{
				memcpy(&(m_struAlarmTime[j][k]), &(m_struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
                memcpy(&(m_bySceneID[j][k]), &(m_bySceneID[i][k]), sizeof(BYTE));
			}
		}
	}
    else if (m_nCopyTime == 7) // 假日情况
    {
        for (k = 0; k < MAX_TIMESEGMENT_V30; k++)
        {
            memcpy(&m_struHolidayHandle.struAlarmTime[k], &(m_struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
        }
//         if (!SetMotionHolidayHandle(m_struHolidayHandle))
//         {
//             AfxMessageBox("Fail to set motion holiday handle");
//         }
    }
	else
	{
		for (k=0; k<MAX_TIMESEGMENT_V30; k++)
		{
			memcpy(&(m_struAlarmTime[m_nCopyTime][k]), &(m_struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
            memcpy(&(m_bySceneID[m_nCopyTime][k]), &(m_bySceneID[i][k]), sizeof(BYTE));
		}
	}
}

void CDlgIPCSimpIntellCfg::OnBnClickedChkAlarminInvokeAlarmout()
{
	UpdateData(TRUE);
	m_treeAlarmOut.EnableWindow(m_bChkInvokeAlarmOut);
}

void CDlgIPCSimpIntellCfg::OnClickTreeAlarmOut( NMHDR* pNMHDR, LRESULT* pResult )
{
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
	m_pbAlarmOut[dwIndex] = !bCheck;
	//switch checkbox status on click
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

void CDlgIPCSimpIntellCfg::CreateTree()
{
	m_treeChan.DeleteAllItems();
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0;
	HTREEITEM hChanItem = NULL;
	if (m_iChanCount <= 0)
	{
		m_treeAlarmOut.EnableWindow(FALSE);
		m_treeChan.EnableWindow(FALSE);
	}
	
	int iChanShow = 0;
	
    for (i = 0; i < g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum; i++)
    {

        hChanItem =  m_treeChan.InsertItem(g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].chChanName, 0, 0, TVI_ROOT);
        m_treeChan.SetItemData(hChanItem, 0*1000 + g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChannelNO);	
        if (m_bRecordChan[g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChannelNO -1])
        {
            m_treeChan.SetCheck(hChanItem, TRUE);
        }
	}

/*	for (i = 0; i < g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum; i++)
	{
		iChanShow = g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChannelNO;
		
		if ((i < m_iAnaChanCount) && g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].bEnable)
		{
			strTemp.Format(ANALOG_C_FORMAT, iChanShow);
			hChanItem =  m_treeChan.InsertItem(strTemp, 0, 0, TVI_ROOT);
			m_treeChan.SetItemData(hChanItem, 0*1000 + i);	
			if (m_bRecordChan[iChanShow -1])
			{
				m_treeChan.SetCheck(hChanItem, TRUE);
			}
		}
		else if (i >= m_iAnaChanCount && g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].bEnable)
		{
			strTemp.Format(DIGITAL_C_FORMAT, iChanShow - m_iDStartChannel + 1);
			hChanItem =  m_treeChan.InsertItem(strTemp, 0, 0, TVI_ROOT);
			m_treeChan.SetItemData(hChanItem, 1*1000 + i);	
			if (m_bRecordChan[iChanShow - 1])
			{
				m_treeChan.SetCheck(hChanItem, TRUE);
			}
		}
	}
*/
    m_treeChan.SelectItem(hChanItem);
	m_treeChan.Expand(m_treeChan.GetRootItem(),TVE_EXPAND);	

	UpdateWindow();
	
	
	g_CreateAlarmOutTree(m_treeAlarmOut, m_iDeviceIndex, m_pbAlarmOut);
}

void CDlgIPCSimpIntellCfg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CreateTree();
	// Do not call CDialog::OnPaint() for painting messages
}

void CDlgIPCSimpIntellCfg::OnCfgTypeChanged()
{
    memset(&m_struLineDetection, 0, sizeof(m_struLineDetection));
    memset(&m_struFieldDetection, 0, sizeof(m_struFieldDetection));
    memset(&m_struDefousDetection, 0, sizeof(m_struDefousDetection));
    memset(&m_struAudioException, 0, sizeof(m_struAudioException));
    memset(&m_struSceneDetection, 0, sizeof(m_struSceneDetection));//场景变更侦测2013-07-17
	memset(m_bRecordChan, 0,sizeof(BOOL)*MAX_CHANNUM_V40);
	memset(m_pbAlarmOut, 0 , sizeof(BOOL)*MAX_ALARMOUT_V40);
	memset(m_struHolidayHandle.struAlarmTime, 0, sizeof(NET_DVR_SCHEDTIME)*MAX_TIMESEGMENT_V30);
	memset(&m_pStruAlarmHandleType->dwRelAlarmOut, 0, MAX_CHANNUM_V30);
	int i = m_Combo_CfgType.GetCurSel();
	//m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    if (i == 0)  
	{
		GetLineDetection();
		//
// 		for (int k = 0; k < MAX_CHANNUM_V30; k++)
// 		{
// 			m_bRecordChan[k] = m_struLineDetection.byRelRecordChan[k];
// 		}
        for (int k = 0; k < m_struLineDetection.dwRelRecordChanNum; k++)
        {
            if (m_struLineDetection.byRelRecordChan[k] != 0xffffffff)
            {
                m_bRecordChan[m_struLineDetection.byRelRecordChan[k]-1] = 1;
            }
        }
		memcpy(m_struAlarmTime, m_struLineDetection.struAlarmSched, sizeof(NET_DVR_SCHEDTIME) * MAX_DAYS * MAX_TIMESEGMENT_V30);
        memcpy(m_struHolidayHandle.struAlarmTime, m_struLineDetection.struHolidayTime, sizeof(NET_DVR_SCHEDTIME)*MAX_TIMESEGMENT_V30);
		ConvertHandleExceptionV40ToV41(&m_struLineDetection.struHandleException,m_pStruAlarmHandleType,TRUE);

		m_bEnable = m_struLineDetection.byEnable;
		m_bTraverseDualVca = m_struLineDetection.byEnableDualVca;
        m_bHumanMisFlineDetect = m_struLineDetection.byEnableHumanMisinfoFilter;
        m_bVehicleLine = m_struLineDetection.byEnableVehicleMisinfoFilter;
	}
	else if(i == 1) //当前配置区域入侵侦测
	{
		GetFieldDetection();
		//
		for (int k = 0; k < m_struFieldDetection.dwRelRecordChanNum; k++)
		{
            if(m_struFieldDetection.byRelRecordChan[k] != 0xffffffff)
            {
                m_bRecordChan[m_struFieldDetection.byRelRecordChan[k]-1] = 1;
            }
			
		}
 

		memcpy(m_struAlarmTime, m_struFieldDetection.struAlarmSched, sizeof(NET_DVR_SCHEDTIME) * MAX_DAYS * MAX_TIMESEGMENT_V30);
        memcpy(m_struHolidayHandle.struAlarmTime, m_struFieldDetection.struHolidayTime, sizeof(NET_DVR_SCHEDTIME)*MAX_TIMESEGMENT_V30);
		ConvertHandleExceptionV40ToV41(&m_struFieldDetection.struHandleException,m_pStruAlarmHandleType,TRUE);
		m_bEnable = m_struFieldDetection.byEnable;
		m_bFieldDetectionDualVca = m_struFieldDetection.byEnableDualVca;
        m_bHumanMisFFiledDetect = m_struFieldDetection.byEnableHumanMisinfoFilter;
        m_bVehicleField = m_struFieldDetection.byEnableVehicleMisinfoFilter;
	}
	else if(i == 2) //当前配置虚焦侦测
	{
		GetDefousDetection();
         
		ConvertHandleExceptionV40ToV41(&m_struDefousDetection.struHandleException,m_pStruAlarmHandleType,TRUE);
		m_bEnable = m_struDefousDetection.byEnable;
		m_iDefocusSensortiveLevel = m_struDefousDetection.bySensitiveLevel;
	}
	else if (i == 3)
	{
		GetAudioException();
		m_bEnable = m_struAudioException.byEnableAudioInException;
		memcpy(m_struAlarmTime, m_struAudioException.struAlarmSched, sizeof(NET_DVR_SCHEDTIME) * MAX_DAYS * MAX_TIMESEGMENT_V30);
		ConvertHandleExceptionV40ToV41(&m_struAudioException.struHandleException,m_pStruAlarmHandleType,TRUE);
		//2014-03-21
		m_bySensitivity = m_struAudioException.struAudioSteepDrop.bySensitivity; 
		m_comEnable.SetCurSel(m_struAudioException.struAudioSteepDrop.byEnable); 
		for (int k = 0; k < m_struAudioException.dwRelRecordChanNum; k++)
		{
            if (m_struAudioException.byRelRecordChan[k] != 0xff)
            {
                m_bRecordChan[m_struAudioException.byRelRecordChan[k]-1]  =1;
            }
		}

	}
	else if (i == 4)//场景变更侦测2013-07-17
	{
		GetSceneDetection();
		m_bEnable = m_struSceneDetection.byEnable;
		memcpy(m_struAlarmTime, m_struSceneDetection.struAlarmSched, sizeof(NET_DVR_SCHEDTIME) * MAX_DAYS * MAX_TIMESEGMENT_V30);
		ConvertHandleExceptionV40ToV41(&m_struSceneDetection.struHandleException,m_pStruAlarmHandleType,TRUE);
		for (int k = 0; k < m_struSceneDetection.dwRelRecordChanNum; k++)
		{
            if ( m_struSceneDetection.dwRelRecordChan[k] != 0xffffffff)
            {
                m_bRecordChan[m_struSceneDetection.dwRelRecordChan[k]-1] = 1;
            }			
		}
	}
    else if (i == 5)
    {
        GetRegionEntrDetection();
        m_bEnable = m_struRegionEntrDetection.byEnabled;
        m_bHumanMisFRegionEDetect = m_struRegionEntrDetection.byEnableHumanMisinfoFilter;
        m_bVehicleEnter = m_struRegionEntrDetection.byEnableVehicleMisinfoFilter;
        int j = m_cmbRegionEntrNo.GetCurSel();
        m_byRegionEntrSensitivity = m_struRegionEntrDetection.struRegion[j].bySensitivity;
        UpdateData(FALSE);
        if(GetEventTrigger(NET_DVR_GET_REGION_ENTR_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_REGION_ENTR_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_REGION_ENTR_TRIGGER");
        }
        if(GetEventSchedule(NET_DVR_GET_REGION_ENTR_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_REGION_ENTR_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_REGION_ENTR_SCHEDULE");
        }
    }
    else if (i == 6)
    {
        GetRegionExitDetection();
        m_bEnable = m_struRegionExitDetection.byEnabled;
        m_bHumanMisFRegionExitDetect = m_struRegionExitDetection.byEnableHumanMisinfoFilter;
        m_bVehicleExit = m_struRegionExitDetection.byEnableVehicleMisinfoFilter;
        int j = m_cmbRegionExitNo.GetCurSel();
        m_nRegionExitSensitivity = m_struRegionExitDetection.struRegion[j].bySensitivity;
        UpdateData(FALSE);
        if(GetEventTrigger(NET_DVR_GET_REGION_EXIT_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_REGION_EXIT_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_REGION_EXIT_TRIGGER");
        }
        if(GetEventSchedule(NET_DVR_GET_REGION_EXIT_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_REGION_EXIT_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_REGION_EXIT_SCHEDULE");
        }
    }
    else if (i == 7)
    {
        GetLoiterDetection();
        m_bEnable = m_struLoiterDetection.byEnabled;
        int j = m_cmbLoiterNo.GetCurSel();
        m_nLoiterSensitivity = m_struLoiterDetection.struRegion[j].bySensitivity;
        m_nLoiterTimeThreshold = m_struLoiterDetection.struRegion[j].byTimeThreshold;
        UpdateData(FALSE);
        if(GetEventTrigger(NET_DVR_GET_LOITERING_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_LOITERING_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_LOITERING_TRIGGER");
        }
        if(GetEventSchedule(NET_DVR_GET_LOITERING_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_LOITERING_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_LOITERING_SCHEDULE");
        }
    }
    else if (i == 8)
    {
        GetGroupDetection();
        m_bEnable = m_struGroupDetection.byEnabled;
        int j = m_cmbGroupDetectionNo.GetCurSel();
        m_nGroupObjectOccup = m_struGroupDetection.struRegion[j].byObjectOccup;
        m_iSensitivityLevel = m_struGroupDetection.struRegion[j].bySensitivityLevel;
        m_iDurationTime = m_struGroupDetection.struRegion[j].byDurationTime;
        m_iFilterTime = m_struGroupDetection.struRegion[j].byFilterTime;
        m_iMinTriggerTime = m_struGroupDetection.struRegion[j].byMinTriggerNumber;
        m_iLinkageTime = m_struGroupDetection.struRegion[j].byLinkageTime;

        UpdateData(FALSE);
        if(GetEventTrigger(NET_DVR_GET_GROUPDETECTION_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_GROUPDETECTION_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_GROUPDETECTION_TRIGGER");
        }
        if(GetEventSchedule(NET_DVR_GET_GROUPDETECTION_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_GROUPDETECTION_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_GROUPDETECTION_SCHEDULE");
        }
    }
    else if (i == 9)
    {
        GetRapidMoveDetection();
        m_bEnable = m_struRapidMove.byEnabled;
        int j = m_cmbRapidMove.GetCurSel();
        m_nRapidMoveSensitivity = m_struRapidMove.struRegion[j].bySensitivity;
        UpdateData(FALSE);
        if(GetEventTrigger(NET_DVR_GET_RAPIDMOVE_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_RAPIDMOVE_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_RAPIDMOVE_TRIGGER");
        }
        if(GetEventSchedule(NET_DVR_GET_RAPIDMOVE_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_RAPIDMOVE_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_RAPIDMOVE_SCHEDULE");
        }
    }
    else if (i == 10)
    {
        GetParkDetection();
        m_bEnable = m_struParkDetection.byEnabled;
        int j = m_cmbParkNo.GetCurSel();
        m_nParkSensitivity = m_struParkDetection.struRegion[j].bySensitivity;
        m_nParkTimeThreshold = m_struParkDetection.struRegion[j].byTimeThreshold;
        UpdateData(FALSE);
        if(GetEventTrigger(NET_DVR_GET_PARKING_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_PARKING_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PARKING_TRIGGER");
        }
        if(GetEventSchedule(NET_DVR_GET_PARKING_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_PARKING_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PARKING_SCHEDULE");
        }
    }
    else if (i == 11)
    {
        GetUnattendedDetection();
        m_bEnable = m_struUnattended.byEnabled;
        int j = m_cmbUnattendedNo.GetCurSel();
        m_nUnattendedSensitivity = m_struUnattended.struRegion[j].bySensitivity;
        m_nUnattendedTimeThreshold = m_struUnattended.struRegion[j].wTimeThreshold;
        UpdateData(FALSE);
        if(GetEventTrigger(NET_DVR_GET_UNATTENDED_BAGGAGE_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_UNATTENDED_BAGGAGE_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_UNATTENDED_BAGGAGE_TRIGGER");
        }
        if(GetEventSchedule(NET_DVR_GET_UNATTENDED_BAGGAGE_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_UNATTENDED_BAGGAGE_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_UNATTENDED_BAGGAGE_SCHEDULE");
        }
    }
    else if (i == 12)
    {
        GetAttendedDetection();
        m_bEnable = m_struAttended.byEnabled;
        int j = m_cmbAttendedNo.GetCurSel();
        m_nAttendedSensitivity = m_struAttended.struRegion[j].bySensitivity;
        m_nAttendedTimeThresgold = m_struAttended.struRegion[j].wTimeThreshold;
        UpdateData(FALSE);
        if(GetEventTrigger(NET_DVR_GET_ATTENDEDBAGGAGE_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ATTENDEDBAGGAGE_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ATTENDEDBAGGAGE_TRIGGER");
        }
        if(GetEventSchedule(NET_DVR_GET_ATTENDEDBAGGAGE_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ATTENDEDBAGGAGE_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ATTENDEDBAGGAGE_SCHEDULE");
        }
    }
    else if (i == 13)
    {
        GetClipCfg();
        m_bEnable = m_struClipCfg.byEnabled;
        m_nResolutionWidth = m_struClipCfg.wResolutionWidth;
        m_nResolutionHeight = m_struClipCfg.wResolutionHeight;
    }
    else if (i == 14)
    {
        if(GetEventTrigger(NET_DVR_GET_FIREDETECTION_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_FIREDETECTION_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_FIREDETECTION_TRIGGER");
        }
        if (GetEventSchedule(NET_DVR_GET_FIREDETECTION_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_FIREDETECTION_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_FIREDETECTION_SCHEDULE");
        }
    }
    else if (i == 15) //防破坏报警联动配置
    {
        if(GetEventTrigger(NET_DVR_GET_VANDALPROOFALARM_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_VANDALPROOFALARM_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_VANDALPROOFALARM_TRIGGER");
        }
    }
    else if (i == 16)
    {
        if(GetEventTrigger(NET_DVR_GET_VEHICLE_BLACKLIST_EVENT_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_BLACKLST_EVENT_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_BLACKLST_EVENT_TRIGGER");
        }
        if(GetEventSchedule(NET_DVR_GET_VEHICLE_BLACKLST_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_BLACKLST_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_BLACKLST_SCHEDULE");
        }
    }    
    else if (i == 17)
    {
        if(GetEventTrigger(NET_DVR_GET_VEHICLE_WHITELIST_EVENT_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_WHITELST_EVENT_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_WHITELST_EVENT_TRIGGER");
        }
        if(GetEventSchedule(NET_DVR_GET_VEHICLE_WHITELST_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_WHITELST_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_WHITELST_SCHEDULE");
        }
    }
    else if (i == 18)
    {
        if(GetEventTrigger(NET_DVR_GET_VEHICLE_OTHERLIST_EVENT_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_VEHICLE_OTHERLIST_EVENT_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_VEHICLE_OTHERLIST_EVENT_TRIGGER");
        }
    }    
    else if (i == 19)
    {
        if(GetEventTrigger(NET_DVR_GET_VEHICLE_ALLLIST_EVENT_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_VEHICLE_ALLLIST_EVENT_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_VEHICLE_ALLLIST_EVENT_TRIGGER");
        }
    }
    else if (i == 20)
    {
//         if(GetEventTrigger(NET_DVR_GET_FACECAPTURE_EVENT_TRIGGER))
//         {
//             g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_FACECAPTURE_EVENT_TRIGGER");
//         }
//         else
//         {
//             g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_FACECAPTURE_EVENT_TRIGGER");
//         }
// 
//         if(GetEventSchedule(NET_DVR_GET_FACECAPTURE_SCHEDULE))
//         {
//             g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_FACECAPTURE_SCHEDULE");
//         }
//         else
//         {
//             g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_FACECAPTURE_SCHEDULE");
//         }
    }
    else if (i == 21)
    {
        if(GetEventTrigger(NET_DVR_GET_STORAGEDETECTION_EVENT_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_STORAGEDETECTION_EVENT_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_STORAGEDETECTION_EVENT_TRIGGER");
        }

        if(GetEventSchedule(NET_DVR_GET_STORAGEDETECTION_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_STORAGEDETECTION_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_STORAGEDETECTION_SCHEDULE");
        }
    }
    else if (i == 22)
    {
        if (GetEventTrigger(NET_DVR_GET_SHIPSDETECTION_EVENT_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SHIPSDETECTION_EVENT_TRIGGER");
        }
        else
        {

            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SHIPSDETECTION_EVENT_TRIGGER");
        }

        if (GetEventSchedule(NET_DVR_GET_SHIPSDETECTION_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SHIPSDETECTION_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SHIPSDETECTION_SCHEDULE");
        }

    }
    else if (i == 23)
    {
        if (GetEventTrigger(NET_DVR_GET_THERMOMETRY_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_THERMOMETRY_TRIGGER");
        }
        else
        {

            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_THERMOMETRY_TRIGGER");
        }
        if (GetEventSchedule(NET_DVR_GET_THERMOMETRY_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_THERMOMETRY_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_THERMOMETRY_SCHEDULE");
        }
    }
    else if (i == 24)
    {
        if (GetEventTrigger(NET_DVR_GET_TEMPERATURE_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_TEMPERATURE_TRIGGER");
        }
        else
        {

            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_TEMPERATURE_TRIGGER");
        }
        if (GetEventSchedule(NET_DVR_GET_TEMPERTURE_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_TEMPERTURE_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_TEMPERTURE_SCHEDULE");
        }
    }
    else if (i == 25)
    {
        if (GetEventTrigger(NET_DVR_GET_ALARMIN_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARMIN_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMIN_TRIGGER");
        }
    }
    else if (i == 26)
    {
        if (GetEventTrigger(NET_DVR_GET_EMERGENCY_CALL_HELP_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_EMERGENCY_CALL_HELP_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_EMERGENCY_CALL_HELP_TRIGGER");
        }
    }
    else if (i == 27)
    {
        if (GetEventTrigger(NET_DVR_GET_CONSULT_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_CONSULT_TRIGGER ");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_CONSULT_TRIGGER ");
        }
    }
    else if (i == 28)
    {
        //黑名单人脸比对
        if (GetEventTrigger(NET_DVR_GET_BLACKLIST_FACECONTRAST_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_BLACKLIST_FACECONTRAST_TRIGGER");
        }
        else
        {

            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_BLACKLIST_FACECONTRAST_TRIGGER");
        }
        if (GetEventSchedule(NET_DVR_GET_BLACKLIST_FACECONTRAST_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_BLACKLIST_FACECONTRAST_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_BLACKLIST_FACECONTRAST_SCHEDULE");
        }
    }
    else if (i == 29)
    {
        //白名单人脸比对
        if (GetEventTrigger(NET_DVR_GET_WHITELIST_FACECONTRAST_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_WHITELIST_FACECONTRAST_TRIGGER");
        }
        else
        {

            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_WHITELIST_FACECONTRAST_TRIGGER");
        }
        if (GetEventSchedule(NET_DVR_GET_WHITELIST_FACECONTRAST_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_WHITELIST_FACECONTRAST_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_WHITELIST_FACECONTRAST_SCHEDULE");
        }
    }
    else if (i == 30)
    {
        //人体识别
        if (GetEventTrigger(NET_DVR_GET_HUMAN_RECOGNITION_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_HUMAN_RECOGNITION_TRIGGER");
        }
        else
        {

            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_HUMAN_RECOGNITION_TRIGGER");
        }
        if (GetEventSchedule(NET_DVR_GET_HUMAN_RECOGNITION_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_HUMAN_RECOGNITION_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_HUMAN_RECOGNITION_SCHEDULE");
        }
    }
    else if (i == 31)
    {
        if (GetEventTrigger(NET_DVR_GET_FACECONTRAST_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_FACECONTRAST_TRIGGER");
        }
        else
        {

            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_FACECONTRAST_TRIGGER");
        }
        if (GetEventSchedule(NET_DVR_GET_FACECONTRAST_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_FACECONTRAST_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_FACECONTRAST_SCHEDULE");
        }
    }
    else if (i == 32)
    {
        if (GetEventTrigger(NET_DVR_GET_FRAMES_PEOPLE_COUNTING_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_FRAMES_PEOPLE_COUNTING_TRIGGER");
        }
        else
        {

            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_FRAMES_PEOPLE_COUNTING_TRIGGER");
        }
        if (GetEventSchedule(NET_DVR_GET_FRAMES_PEOPLE_COUNTING_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_FRAMES_PEOPLE_COUNTING_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_FRAMES_PEOPLE_COUNTING_SCHEDULE");
        }
    }
    else if (i == 33)
    {
        if (GetEventTrigger(NET_DVR_GET_STUDENTS_STOODUP_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_STUDENTS_STOODUP_TRIGGER");
        }
        else
        {

            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_STUDENTS_STOODUP_TRIGGER");
        }
        if (GetEventSchedule(NET_DVR_GET_STUDENTS_STOODUP_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_STUDENTS_STOODUP_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_STUDENTS_STOODUP_SCHEDULE");
        }
    }
    else if (i == 34)
    {
        if (GetEventTrigger(NET_DVR_GET_PERSONDENSITY_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_PERSONDENSITY_TRIGGER");
        }
        else
        {

            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PERSONDENSITY_TRIGGER");
        }
        if (GetEventSchedule(NET_DVR_GET_PERSONDENSITY_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_PERSONDENSITY_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PERSONDENSITY_SCHEDULE");
        }
    }
    else if (i == 35)
    {
        if (GetEventTrigger(NET_DVR_GET_FACELIB_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_FACELIB_TRIGGER");
        }
        else
        {

            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_FACELIB_TRIGGER");
        }
        if (GetEventSchedule(NET_DVR_GET_FACELIB_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_FACELIB_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_FACELIB_SCHEDULE");
        }
    }
    else if (i == 36)
    {
        if (GetEventTrigger(NET_DVR_GET_FACESNAP_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_FACESNAP_TRIGGER");
        }
        else
        {

            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_FACESNAP_TRIGGER");
        }
        if (GetEventSchedule(NET_DVR_GET_FACESNAP_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_FACESNAP_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_FACESNAP_SCHEDULE");
        }
    }
    else if (i == 37)
    {
        if (GetEventTrigger(NET_DVR_GET_SAFETY_HELMET_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SAFETY_HELMET_TRIGGER");
        }
        else
        {

            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SAFETY_HELMET_TRIGGER");
        }
        if (GetEventSchedule(NET_DVR_GET_SAFETY_HELMET_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SAFETY_HELMET_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SAFETY_HELMET_SCHEDULE");
        }
    }
    else if (i == 38)
    {
        if (GetEventTrigger(NET_DVR_GET_FACE_THERMOMETRY_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_FACE_THERMOMETRY_TRIGGER");
        }
        else
        {

            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_FACE_THERMOMETRY_TRIGGER");
        }
        if (GetEventSchedule(NET_DVR_GET_FACE_THERMOMETRY_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_FACE_THERMOMETRY_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_FACE_THERMOMETRY_SCHEDULE");
        }
    }
    else if (i == 39)
    {
        if (GetEventTrigger(NET_DVR_GET_SIGN_ABNORMAL_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SIGN_ABNORMAL_TRIGGER");
        }
        else
        {

            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SIGN_ABNORMAL_TRIGGER");
        }
    }
    else if (i == 40)
    {
        if (GetEventTrigger(NET_DVR_GET_SOFTIO_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SOFTIO_TRIGGER");
        }
        else
        {

            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SOFTIO_TRIGGER");
        }
        if (GetEventSchedule(NET_DVR_GET_SOFTIO_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SOFTIO_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SOFTIO_SCHEDULE");
        }
    }
    else if (i == 41)
    {
        if (SetEventTrigger(NET_DVR_GET_PERSONQUEUE_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_PERSONQUEUE_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PERSONQUEUE_TRIGGER");
        }
        if (SetEventSchedule(NET_DVR_GET_PERSONQUEUE_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_PERSONQUEUE_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PERSONQUEUE_SCHEDULE");
        }
    }
    else if (i == 42)
    {
        if (GetEventTrigger(NET_DVR_GET_HFPD_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_HFPD_TRIGGER");
        }
        else
        {

            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_HFPD_TRIGGER");
        }
        if (GetEventSchedule(NET_DVR_GET_HFPD_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_HFPD_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_HFPD_SCHEDULE");
        }
    }
  
	//GetDlgItem(IDC_CHK_LINE_DETECTION)->UpdateData(FALSE);
	UpdateData(FALSE);
	ShowData();
}

void CDlgIPCSimpIntellCfg::GetLineDetection()
{
	UpdateData(TRUE);
	int iCount = 1;
	NET_DVR_CHANNEL_GROUP struLineDetectionCond = {0};
	struLineDetectionCond.dwChannel = m_lChannel;//m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
	struLineDetectionCond.dwGroup = m_cmbGroupNo.GetItemData(m_cmbGroupNo.GetCurSel());
	struLineDetectionCond.byID = m_Combo_LineNo.GetCurSel()+1/*m_ComboRegionID.GetCurSel()+1*/;
	struLineDetectionCond.dwSize = sizeof(struLineDetectionCond);
	int pStatus = 0;
    char szLan[128] = {0};
	BOOL bRet = NET_DVR_GetDeviceConfig(m_lLoginID, NET_DVR_GET_TRAVERSE_PLANE_DETECTION, iCount, &struLineDetectionCond, \
		sizeof(NET_DVR_CHANNEL_GROUP), &pStatus, &m_struLineDetection, sizeof(m_struLineDetection));
	if (bRet && pStatus == NET_DVR_NOERROR)
	{
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_TRAVERSE_PLANE_DETECTION");
    }
    else if (!bRet)
    {
        DWORD dwErrCode = NET_DVR_GetLastError();
        sprintf(szLan, "err %d", dwErrCode);
        AfxMessageBox(szLan);

        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_TRAVERSE_PLANE_DETECTION");
        return;
    }
}

void CDlgIPCSimpIntellCfg::SaveLineDetection()
{
	UpdateData(TRUE);
	int iCount = 0;
    char szLan[128] = {0};
	NET_DVR_CHANNEL_GROUP struLineDetectionCond = {0};

	struLineDetectionCond.dwChannel = m_lChannel;//m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
	struLineDetectionCond.dwGroup = m_cmbGroupNo.GetItemData(m_cmbGroupNo.GetCurSel());
	struLineDetectionCond.byID = m_Combo_LineNo.GetCurSel()+1/*m_ComboRegionID.GetCurSel()+1*/;
	struLineDetectionCond.dwSize = sizeof(struLineDetectionCond);
	int pStatus = 0;
	m_struLineDetection.dwSize = sizeof(NET_VCA_TRAVERSE_PLANE_DETECTION);
	BOOL bRet = NET_DVR_SetDeviceConfig(m_lLoginID, NET_DVR_SET_TRAVERSE_PLANE_DETECTION, iCount, &struLineDetectionCond, \
		sizeof(NET_DVR_CHANNEL_GROUP), &pStatus, &m_struLineDetection, sizeof(m_struLineDetection));
	if (bRet && pStatus == NET_DVR_NOERROR)
	{
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_TRAVERSE_PLANE_DETECTION");
    }
    else
    {
        sprintf(szLan,"err %d",pStatus);
        AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_TRAVERSE_PLANE_DETECTION");
    }
}

void CDlgIPCSimpIntellCfg::GetFieldDetection()
{
	UpdateData(TRUE);
	int iCount = 1;
	NET_DVR_CHANNEL_GROUP struFielDetectionCond = {0};
    struFielDetectionCond.dwChannel = m_lChannel;//m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
	struFielDetectionCond.dwGroup = m_cmbGroupNo.GetItemData(m_cmbGroupNo.GetCurSel());
	struFielDetectionCond.byID = m_Comnbo_FieldNo.GetCurSel() + 1/*m_ComboRegionID.GetCurSel()+1*/;
	struFielDetectionCond.dwSize = sizeof(struFielDetectionCond);
	int pStatus = 0;
    char szLan[128] = {0};
	BOOL bRet = NET_DVR_GetDeviceConfig(m_lLoginID, NET_DVR_GET_FIELD_DETECTION, iCount, &struFielDetectionCond, \
		sizeof(NET_DVR_CHANNEL_GROUP), &pStatus, &m_struFieldDetection, sizeof(m_struFieldDetection));
	if (bRet && pStatus == NET_DVR_NOERROR)
	{
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_FIELD_DETECTION");
    }
    else
    {
        sprintf(szLan,"err %d",pStatus);
        AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_FIELD_DETECTION");
    }
}


void CDlgIPCSimpIntellCfg::SaveFieldDetection()
{
	UpdateData(TRUE);
	int iCount = 1;
	NET_DVR_CHANNEL_GROUP struFieldDetectionCond = {0};
    struFieldDetectionCond.dwChannel = m_lChannel; //m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
	struFieldDetectionCond.dwGroup = m_cmbGroupNo.GetItemData(m_cmbGroupNo.GetCurSel());
	struFieldDetectionCond.byID = m_Comnbo_FieldNo.GetCurSel() + 1/*m_ComboRegionID.GetCurSel()+1*/;
	struFieldDetectionCond.dwSize = sizeof(struFieldDetectionCond);
	int pStatus = 0;
	m_struFieldDetection.dwSize = sizeof(m_struFieldDetection);
    char szLan[128] = {0};
    BOOL bRet = NET_DVR_SetDeviceConfig(m_lLoginID, NET_DVR_SET_FIELD_DETECTION, iCount, &struFieldDetectionCond, \
		sizeof(NET_DVR_CHANNEL_GROUP), &pStatus, &m_struFieldDetection, sizeof(m_struFieldDetection));
	if (bRet && pStatus == NET_DVR_NOERROR)
	{
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_FIELD_DETECTION");
    }
    else
    {
        sprintf(szLan,"err %d",pStatus);
        AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_FIELD_DETECTION");
    }
}

void CDlgIPCSimpIntellCfg::GetDefousDetection()
{
	int iCount = 1;
	NET_DVR_CHANNEL_GROUP struDefousCond = {0};
	struDefousCond.dwChannel = m_lChannel;//m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
	struDefousCond.dwGroup = 1;
	struDefousCond.dwSize = sizeof(struDefousCond);
	int pStatus = 0;
    char szLan[128] = {0};
	m_struDefousDetection.dwSize = sizeof(NET_VCA_DEFOCUSPARAM);
	BOOL bRet = NET_DVR_GetDeviceConfig(m_lLoginID, NET_DVR_GET_DEFOCUSPARAM, iCount, &struDefousCond, \
		sizeof(NET_DVR_CHANNEL_GROUP), &pStatus, &m_struDefousDetection, sizeof(m_struDefousDetection));
	if (bRet && pStatus == 0)
	{
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_DEFOCUSPARAM");
    }
    else
    {
        sprintf(szLan,"err %d",pStatus);
        AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_DEFOCUSPARAM");
    }
}

void CDlgIPCSimpIntellCfg::SaveDefousDetection()
{
	int iCount = 1;
	NET_DVR_CHANNEL_GROUP struDefousCond = {0};
	struDefousCond.dwChannel = m_lChannel;//m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
	struDefousCond.dwGroup = 0;
	struDefousCond.dwSize = sizeof(struDefousCond);
	m_struDefousDetection.dwSize = sizeof(m_struDefousDetection);
	int pStatus = 0;
    char szLan[128] = {0};
	BOOL bRet = NET_DVR_SetDeviceConfig(m_lLoginID, NET_DVR_SET_DEFOCUSPARAM, iCount, &struDefousCond, \
		sizeof(NET_DVR_CHANNEL_GROUP), &pStatus, &m_struDefousDetection, sizeof(m_struDefousDetection));
	if (bRet && pStatus == 0)
	{
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_DEFOCUSPARAM");
    }
    else
    {
       sprintf(szLan,"err %d",pStatus);
        AfxMessageBox(szLan);;
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_DEFOCUSPARAM");
    }
}

void CDlgIPCSimpIntellCfg::OnBtnSavecfg() 
{
	SaveUIData();
	int i = m_Combo_CfgType.GetCurSel();
	// TODO: Add your control notification handler code here
	if (i == 0)
	{
		m_struLineDetection.byEnable = m_bEnable;
		m_struLineDetection.byEnableDualVca = m_bTraverseDualVca;
        m_struLineDetection.byEnableHumanMisinfoFilter = m_bHumanMisFlineDetect;
        m_struLineDetection.byEnableVehicleMisinfoFilter = m_bVehicleLine;
		memcpy(m_struLineDetection.struAlarmSched, m_struAlarmTime, sizeof(NET_DVR_SCHEDTIME) * MAX_DAYS * MAX_TIMESEGMENT_V30);
        memcpy(m_struLineDetection.struHolidayTime, m_struHolidayHandle.struAlarmTime, sizeof(NET_DVR_SCHEDTIME)*MAX_TIMESEGMENT_V30);
		m_struLineDetection.dwRelRecordChanNum = 0;
        memset(m_struLineDetection.byRelRecordChan, 0xffffffff, sizeof(m_struLineDetection.byRelRecordChan));
        for (int k = 0; k < MAX_CHANNUM_V30*8; k++)
		{
            if(m_bRecordChan[k])
            {
                m_struLineDetection.byRelRecordChan[m_struLineDetection.dwRelRecordChanNum++] = k +1;
            }
		}

		ConvertHandleExceptionV40ToV41(&m_struLineDetection.struHandleException,m_pStruAlarmHandleType,FALSE);
		
		SaveLineDetection();
	}
	else if (i == 1)
	{
        m_struFieldDetection.dwRelRecordChanNum = 0;
        memset(m_struFieldDetection.byRelRecordChan, 0xffffffff, sizeof(m_struFieldDetection.byRelRecordChan));
        for (int k = 0; k < MAX_CHANNUM_V30*8; k++)
        {
            if(m_bRecordChan[k])
            {
                m_struFieldDetection.byRelRecordChan[m_struFieldDetection.dwRelRecordChanNum++] = k +1;
            }
        }


		memcpy(m_struFieldDetection.struAlarmSched, m_struAlarmTime, sizeof(NET_DVR_SCHEDTIME) * MAX_DAYS * MAX_TIMESEGMENT_V30);
        memcpy(m_struFieldDetection.struHolidayTime, m_struHolidayHandle.struAlarmTime, sizeof(NET_DVR_SCHEDTIME)*MAX_TIMESEGMENT_V30);

        ConvertHandleExceptionV40ToV41(&m_struFieldDetection.struHandleException, m_pStruAlarmHandleType, FALSE);
		m_struFieldDetection.byEnable = m_bEnable;

		m_struFieldDetection.byEnableDualVca = m_bFieldDetectionDualVca;
        m_struFieldDetection.byEnableHumanMisinfoFilter = m_bHumanMisFFiledDetect;
        m_struFieldDetection.byEnableVehicleMisinfoFilter = m_bVehicleField;
		SaveFieldDetection();
	}
	else if (i == 2)
	{
		m_struDefousDetection.byEnable = m_bEnable;
		ConvertHandleExceptionV40ToV41(&m_struDefousDetection.struHandleException,m_pStruAlarmHandleType,FALSE);
		m_struDefousDetection.bySensitiveLevel = m_iDefocusSensortiveLevel;
		SaveDefousDetection();
	}
	else if (i == 3)
	{
		m_struAudioException.byEnableAudioInException = m_bEnable;
		memcpy(m_struAudioException.struAlarmSched, m_struAlarmTime, sizeof(NET_DVR_SCHEDTIME) * MAX_DAYS * MAX_TIMESEGMENT_V30);

        m_struAudioException.dwRelRecordChanNum = 0;
        memset(m_struAudioException.byRelRecordChan, 0xffffffff, sizeof(m_struAudioException.byRelRecordChan));
        for (int k = 0; k < MAX_CHANNUM_V30*8; k++)
        {
            if(m_bRecordChan[k])
            {
                m_struAudioException.byRelRecordChan[m_struAudioException.dwRelRecordChanNum++] = k +1;
            }
        }

		ConvertHandleExceptionV40ToV41(&m_struAudioException.struHandleException,m_pStruAlarmHandleType,FALSE);
		
		//2014-03-21
		m_struAudioException.struAudioSteepDrop.bySensitivity = m_bySensitivity; 
		m_struAudioException.struAudioSteepDrop.byEnable = m_comEnable.GetCurSel(); 
		
		SaveAudioException();
	}
	else if (i == 4)//场景变更侦测2013-07-17
	{
		m_struSceneDetection.byEnable = m_bEnable;
		memcpy(m_struSceneDetection.struAlarmSched, m_struAlarmTime, sizeof(NET_DVR_SCHEDTIME) * MAX_DAYS * MAX_TIMESEGMENT_V30);
        m_struSceneDetection.dwRelRecordChanNum = 0;
        memset(m_struSceneDetection.dwRelRecordChan, 0xffffffff, sizeof(m_struSceneDetection.dwRelRecordChan));
		for (int k = 0; k < MAX_CHANNUM_V30; k++)
		{
			//m_struSceneDetection.dwRelRecordChan[k] = m_bRecordChan[k] +1;
            if (m_bRecordChan[k])
            {
                m_struSceneDetection.dwRelRecordChan[m_struSceneDetection.dwRelRecordChanNum++] = k + 1;
            }
		}
		ConvertHandleExceptionV40ToV41(&m_struSceneDetection.struHandleException,m_pStruAlarmHandleType,FALSE);
		SaveSceneDetection();
	}
    else if (i == 5)
    {
        m_struRegionEntrDetection.byEnabled = m_bEnable;
        m_struRegionEntrDetection.byEnableHumanMisinfoFilter = m_bHumanMisFRegionEDetect;
        m_struRegionEntrDetection.byEnableVehicleMisinfoFilter = m_bVehicleEnter;
        SaveRegionEntrDetection();
        if(SetEventTrigger(NET_DVR_SET_REGION_ENTR_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_REGION_ENTR_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_REGION_ENTR_TRIGGER");
        }
        if(SetEventSchedule(NET_DVR_SET_REGION_ENTR_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_REGION_ENTR_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_REGION_ENTR_SCHEDULE");
        }
    }
    else if (i == 6)
    {
        m_struRegionExitDetection.byEnabled = m_bEnable;
        m_struRegionExitDetection.byEnableHumanMisinfoFilter = m_bHumanMisFRegionExitDetect;
        m_struRegionExitDetection.byEnableVehicleMisinfoFilter = m_bVehicleExit;
        SaveRegionExitDetection();
        if(SetEventTrigger(NET_DVR_SET_REGION_EXIT_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_REGION_EXIT_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_REGION_EXIT_TRIGGER");
        }
        if(SetEventSchedule(NET_DVR_SET_REGION_EXIT_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_REGION_EXIT_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_REGION_EXIT_SCHEDULE");
        }
    }
    else if (i == 7)
    {
        m_struLoiterDetection.byEnabled = m_bEnable;
        SaveLoiterDetection();
        if(SetEventTrigger(NET_DVR_SET_LOITERING_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_LOITERING_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_LOITERING_TRIGGER");
        }
        if(SetEventSchedule(NET_DVR_SET_LOITERING_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_LOITERING_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_LOITERING_SCHEDULE");
        }
    }
    else if (i == 8)
    {
        m_struGroupDetection.byEnabled = m_bEnable;
        SaveGroupDetection();
        if(SetEventTrigger(NET_DVR_SET_GROUPDETECTION_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_GROUPDETECTION_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_GROUPDETECTION_TRIGGER");
        }
        if(SetEventSchedule(NET_DVR_SET_GROUPDETECTION_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_GROUPDETECTION_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_GROUPDETECTION_SCHEDULE");
        }
    }
    else if (i == 9)
    {
        m_struRapidMove.byEnabled = m_bEnable;
        SaveRapidMoveDetection();
        if(SetEventTrigger(NET_DVR_SET_RAPIDMOVE_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_RAPIDMOVE_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_RAPIDMOVE_TRIGGER");
        }
        if(SetEventSchedule(NET_DVR_SET_RAPIDMOVE_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_RAPIDMOVE_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_RAPIDMOVE_SCHEDULE");
        }
    }
    else if (i == 10)
    {
        m_struParkDetection.byEnabled = m_bEnable;
        SaveParkDetection();
        if(SetEventTrigger(NET_DVR_SET_PARKING_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PARKING_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_PARKING_TRIGGER");
        }
        if(SetEventSchedule(NET_DVR_SET_PARKING_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PARKING_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_PARKING_SCHEDULE");
        }
    }
    else if (i == 11)
    {
        m_struUnattended.byEnabled = m_bEnable;
        SaveUnattendedDetection();
        if(SetEventTrigger(NET_DVR_SET_UNATTENDED_BAGGAGE_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_UNATTENDED_BAGGAGE_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_UNATTENDED_BAGGAGE_TRIGGER");
        }
        if(SetEventSchedule(NET_DVR_SET_UNATTENDED_BAGGAGE_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_UNATTENDED_BAGGAGE_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_UNATTENDED_BAGGAGE_SCHEDULE");
        }
    }
    else if (i == 12)
    {
        m_struAttended.byEnabled = m_bEnable;
        SaveAttendedDetection();
        if(SetEventTrigger(NET_DVR_SET_ATTENDEDBAGGAGE_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_ATTENDEDBAGGAGE_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_ATTENDEDBAGGAGE_TRIGGER");
        }
        if(SetEventSchedule(NET_DVR_SET_ATTENDEDBAGGAGE_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_ATTENDEDBAGGAGE_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_ATTENDEDBAGGAGE_SCHEDULE");
        }
    }
    else if (i == 13)
    {
        m_struClipCfg.byEnabled = m_bEnable;
        m_struClipCfg.wResolutionWidth = m_nResolutionWidth;
        m_struClipCfg.wResolutionHeight = m_nResolutionHeight;
        SaveClipCfg();
    }
    else if (i == 14)
    {
        if(SetEventTrigger(NET_DVR_SET_FIREDETECTION_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_FIREDETECTION_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_FIREDETECTION_TRIGGER");
        }
        if (SetEventSchedule(NET_DVR_SET_FIREDETECTION_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_FIREDETECTION_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_FIREDETECTION_SCHEDULE");
        }
    }
    else if (i == 15)//防破坏报警
    {
        if(SetEventTrigger(NET_DVR_SET_VANDALPROOFALARM_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_VANDALPROOFALARM_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_VANDALPROOFALARM_TRIGGER");
        }
    }
    else if (i == 16)
    {
        if(SetEventTrigger(NET_DVR_SET_VEHICLE_BLACKLIST_EVENT_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_BLACKLST_EVENT_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_BLACKLST_EVENT_TRIGGER");
        }
        if(SetEventSchedule(NET_DVR_SET_VEHICLE_BLACKLST_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_BLACKLST_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_BLACKLST_SCHEDULE");
        }
    }
    else if (i == 17)
    {
        if(SetEventTrigger(NET_DVR_SET_VEHICLE_WHITELIST_EVENT_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_WHITELST_EVENT_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_WHITELST_EVENT_TRIGGER");
        }
        if(SetEventSchedule(NET_DVR_SET_VEHICLE_WHITELST_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_WHITELST_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_WHITELST_SCHEDULE");
        }
    }
    else if (i == 18)
    {
        if(SetEventTrigger(NET_DVR_SET_VEHICLE_OTHERLIST_EVENT_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_VEHICLE_OTHERLIST_EVENT_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_VEHICLE_OTHERLIST_EVENT_TRIGGER");
        }
    }
    else if (i == 19)
    {
        if(SetEventTrigger(NET_DVR_SET_VEHICLE_ALLLIST_EVENT_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_VEHICLE_ALLLIST_EVENT_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_VEHICLE_ALLLIST_EVENT_TRIGGER");
        }
    }
    else if (i == 20)
    {
//         if(SetEventTrigger(NET_DVR_SET_FACECAPTURE_EVENT_TRIGGER))
//         {
//             g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_FACECAPTURE_EVENT_TRIGGER");
//         }
//         else
//         {
//             g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_FACECAPTURE_EVENT_TRIGGER");
//         }
//         
//         if(SetEventSchedule(NET_DVR_SET_FACECAPTURE_SCHEDULE))
//         {
//             g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_FACECAPTURE_SCHEDULE");
//         }
//         else
//         {
//             g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_FACECAPTURE_SCHEDULE");
//         }
    }
    else if (i == 21)
    {
        if(SetEventTrigger(NET_DVR_SET_STORAGEDETECTION_EVENT_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_STORAGEDETECTION_EVENT_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_STORAGEDETECTION_EVENT_TRIGGER");
        }
        
        if(SetEventSchedule(NET_DVR_SET_STORAGEDETECTION_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_STORAGEDETECTION_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_STORAGEDETECTION_SCHEDULE");
        }
    }
    else if (i == 22)
    {
        if (SetEventTrigger(NET_DVR_SET_SHIPSDETECTION_EVENT_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_SHIPSDETECTION_EVENT_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SHIPSDETECTION_EVENT_TRIGGER");
        }

        if (SetEventSchedule(NET_DVR_SET_SHIPSDETECTION_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_SHIPSDETECTION_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SHIPSDETECTION_SCHEDULE");
        }

    }
    else if (i == 23)
    {
        if (SetEventTrigger(NET_DVR_SET_THERMOMETRY_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_THERMOMETRY_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_THERMOMETRY_TRIGGER");
        }
        if (SetEventSchedule(NET_DVR_SET_THERMOMETRY_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_THERMOMETRY_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_THERMOMETRY_SCHEDULE");
        }
    }
    else if (i == 24)
    {
        if (SetEventTrigger(NET_DVR_SET_TEMPERATURE_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_TEMPERATURE_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_TEMPERATURE_TRIGGER");
        }
        if (SetEventSchedule(NET_DVR_SET_TEMPERTURE_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_TEMPERTURE_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_TEMPERTURE_SCHEDULE");
        }
    }
    else if (i == 25)
    {
        if (SetEventTrigger(NET_DVR_SET_ALARMIN_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_ALARMIN_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_ALARMIN_TRIGGER");
        }
    }
    else if (i == 26)
    {
        if (SetEventTrigger(NET_DVR_SET_EMERGENCY_CALL_HELP_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_EMERGENCY_CALL_HELP_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_EMERGENCY_CALL_HELP_TRIGGER");
        }
    }
    else if (i == 27)
    {
        if (SetEventTrigger(NET_DVR_SET_CONSULT_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_CONSULT_TRIGGER ");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_CONSULT_TRIGGER ");
        }
    }
    else if (i == 28)
    {
        //黑名单人脸比对
        if (SetEventTrigger(NET_DVR_SET_BLACKLIST_FACECONTRAST_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_BLACKLIST_FACECONTRAST_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_BLACKLIST_FACECONTRAST_TRIGGER");
        }
        if (SetEventSchedule(NET_DVR_SET_BLACKLIST_FACECONTRAST_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_BLACKLIST_FACECONTRAST_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_BLACKLIST_FACECONTRAST_SCHEDULE");
        }
    }
    else if (i == 29)
    {
        //白名单人脸比对
        if (SetEventTrigger(NET_DVR_SET_WHITELIST_FACECONTRAST_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_WHITELIST_FACECONTRAST_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_WHITELIST_FACECONTRAST_TRIGGER");
        }
        if (SetEventSchedule(NET_DVR_SET_WHITELIST_FACECONTRAST_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_WHITELIST_FACECONTRAST_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_WHITELIST_FACECONTRAST_SCHEDULE");
        }
    }
    else if (i == 30)
    {
        if (SetEventTrigger(NET_DVR_SET_HUMAN_RECOGNITION_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_HUMAN_RECOGNITION_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_HUMAN_RECOGNITION_TRIGGER");
        }
        if (SetEventSchedule(NET_DVR_SET_HUMAN_RECOGNITION_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_HUMAN_RECOGNITION_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_HUMAN_RECOGNITION_SCHEDULE");
        }
    }
    else if (i == 31)
    {
        if (SetEventTrigger(NET_DVR_SET_FACECONTRAST_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_FACECONTRAST_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_FACECONTRAST_TRIGGER");
        }
        if (SetEventSchedule(NET_DVR_SET_FACECONTRAST_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_FACECONTRAST_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_FACECONTRAST_SCHEDULE");
        }
    }
    else if (i == 32)
    {
        if (SetEventTrigger(NET_DVR_SET_FRAMES_PEOPLE_COUNTING_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_FRAMES_PEOPLE_COUNTING_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_FRAMES_PEOPLE_COUNTING_TRIGGER");
        }
        if (SetEventSchedule(NET_DVR_SET_FRAMES_PEOPLE_COUNTING_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_FRAMES_PEOPLE_COUNTING_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_FRAMES_PEOPLE_COUNTING_SCHEDULE");
        }
    }
    else if (i == 33)
    {
        if (SetEventTrigger(NET_DVR_SET_STUDENTS_STOODUP_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_STUDENTS_STOODUP_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_STUDENTS_STOODUP_TRIGGER");
        }
        if (SetEventSchedule(NET_DVR_SET_STUDENTS_STOODUP_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_STUDENTS_STOODUP_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_STUDENTS_STOODUP_SCHEDULE");
        }
    }
    else if (i == 34)
    {
        if (SetEventTrigger(NET_DVR_SET_PERSONDENSITY_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PERSONDENSITY_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_PERSONDENSITY_TRIGGER");
        }
        if (SetEventSchedule(NET_DVR_SET_PERSONDENSITY_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PERSONDENSITY_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_PERSONDENSITY_SCHEDULE");
        }
    }
    else if (i == 35)
    {
        if (SetEventTrigger(NET_DVR_SET_FACELIB_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_FACELIB_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_FACELIB_TRIGGER");
        }
        if (SetEventSchedule(NET_DVR_SET_FACELIB_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_FACELIB_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_FACELIB_SCHEDULE");
        }
    }
    else if (i == 36)
    {
        if (SetEventTrigger(NET_DVR_SET_FACESNAP_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_FACESNAP_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_FACESNAP_TRIGGER");
        }
        if (SetEventSchedule(NET_DVR_SET_FACESNAP_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_FACESNAP_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_FACESNAP_SCHEDULE");
        }
    }
    else if (i == 37)
    {
        if (SetEventTrigger(NET_DVR_SET_SAFETY_HELMET_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_SAFETY_HELMET_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SAFETY_HELMET_TRIGGER");
        }
        if (SetEventSchedule(NET_DVR_SET_SAFETY_HELMET_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_SAFETY_HELMET_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SAFETY_HELMET_SCHEDULE");
        }
    }
    else if (i == 38)
    {
        if (SetEventTrigger(NET_DVR_SET_FACE_THERMOMETRY_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_FACE_THERMOMETRY_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_FACE_THERMOMETRY_TRIGGER");
        }
        if (SetEventSchedule(NET_DVR_SET_FACE_THERMOMETRY_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_FACE_THERMOMETRY_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_FACE_THERMOMETRY_SCHEDULE");
        }
    }
    else if (i == 39)
    {
        if (SetEventTrigger(NET_DVR_SET_SIGN_ABNORMAL_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_SIGN_ABNORMAL_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SIGN_ABNORMAL_TRIGGER");
        }
    }
    else if (i == 40)
    {
        if (SetEventTrigger(NET_DVR_SET_SOFTIO_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_SOFTIO_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SOFTIO_TRIGGER");
        }
        if (SetEventSchedule(NET_DVR_SET_SOFTIO_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_SOFTIO_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SOFTIO_SCHEDULE");
        }
    }
    else if (i == 41)
    {
        if (SetEventTrigger(NET_DVR_SET_PERSONQUEUE_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PERSONQUEUE_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_PERSONQUEUE_TRIGGER");
        }
        if (SetEventSchedule(NET_DVR_SET_PERSONQUEUE_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PERSONQUEUE_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_PERSONQUEUE_SCHEDULE");
        }
    }
    else if (i == 42)
    {
        if (SetEventTrigger(NET_DVR_SET_HFPD_TRIGGER))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_HFPD_TRIGGER");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_HFPD_TRIGGER");
        }
        if (SetEventSchedule(NET_DVR_SET_HFPD_SCHEDULE))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_HFPD_SCHEDULE");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_HFPD_SCHEDULE");
        }
    }
}

void CDlgIPCSimpIntellCfg::SaveUIData()
{
	UpdateData(TRUE);
	if (!TimeTest())
	{
		return;
	}
	int	i = m_comboWeekday.GetCurSel();	
    if (i == 7)
    {
        m_struHolidayHandle.struAlarmTime[0].byStartHour = (BYTE)m_iHour11;
        m_struHolidayHandle.struAlarmTime[0].byStartMin = (BYTE)m_iMin11;
        m_struHolidayHandle.struAlarmTime[0].byStopHour = (BYTE)m_iHour12;
        m_struHolidayHandle.struAlarmTime[0].byStopMin = (BYTE)m_iMin12;
        m_struHolidayHandle.struAlarmTime[1].byStartHour = (BYTE)m_iHour21;
        m_struHolidayHandle.struAlarmTime[1].byStartMin = (BYTE)m_iMin21;
        m_struHolidayHandle.struAlarmTime[1].byStopHour = (BYTE)m_iHour22;
        m_struHolidayHandle.struAlarmTime[1].byStopMin = (BYTE)m_iMin22;
        m_struHolidayHandle.struAlarmTime[2].byStartHour = (BYTE)m_iHour31;
        m_struHolidayHandle.struAlarmTime[2].byStartMin = (BYTE)m_iMin31;
        m_struHolidayHandle.struAlarmTime[2].byStopHour = (BYTE)m_iHour32;
        m_struHolidayHandle.struAlarmTime[2].byStopMin = (BYTE)m_iMin32;
        m_struHolidayHandle.struAlarmTime[3].byStartHour = (BYTE)m_iHour41;
        m_struHolidayHandle.struAlarmTime[3].byStartMin = (BYTE)m_iMin41;
        m_struHolidayHandle.struAlarmTime[3].byStopHour = (BYTE)m_iHour42;
        m_struHolidayHandle.struAlarmTime[3].byStopMin = (BYTE)m_iMin42;
        
        m_struHolidayHandle.struAlarmTime[4].byStartHour = (BYTE)m_iHour51;
        m_struHolidayHandle.struAlarmTime[4].byStartMin = (BYTE)m_iMin51;
        m_struHolidayHandle.struAlarmTime[4].byStopHour = (BYTE)m_iHour52;
        m_struHolidayHandle.struAlarmTime[4].byStopMin = (BYTE)m_iMin52;
        m_struHolidayHandle.struAlarmTime[5].byStartHour = (BYTE)m_iHour61;
        m_struHolidayHandle.struAlarmTime[5].byStartMin = (BYTE)m_iMin61;
        m_struHolidayHandle.struAlarmTime[5].byStopHour = (BYTE)m_iHour62;
        m_struHolidayHandle.struAlarmTime[5].byStopMin = (BYTE)m_iMin62;
        m_struHolidayHandle.struAlarmTime[6].byStartHour = (BYTE)m_iHour71;
        m_struHolidayHandle.struAlarmTime[6].byStartMin = (BYTE)m_iMin71;
        m_struHolidayHandle.struAlarmTime[6].byStopHour = (BYTE)m_iHour72;
        m_struHolidayHandle.struAlarmTime[6].byStopMin = (BYTE)m_iMin72;
        m_struHolidayHandle.struAlarmTime[7].byStartHour = (BYTE)m_iHour81;
        m_struHolidayHandle.struAlarmTime[7].byStartMin = (BYTE)m_iMin81;
        m_struHolidayHandle.struAlarmTime[7].byStopHour = (BYTE)m_iHour82;
        m_struHolidayHandle.struAlarmTime[7].byStopMin = (BYTE)m_iMin82;
    }
    else
    {
        m_struAlarmTime[i][0].byStartHour = (BYTE)m_iHour11;
        m_struAlarmTime[i][0].byStartMin = (BYTE)m_iMin11;
        m_struAlarmTime[i][0].byStopHour = (BYTE)m_iHour12;
        m_struAlarmTime[i][0].byStopMin = (BYTE)m_iMin12;
        m_struAlarmTime[i][1].byStartHour = (BYTE)m_iHour21;
        m_struAlarmTime[i][1].byStartMin = (BYTE)m_iMin21;
        m_struAlarmTime[i][1].byStopHour = (BYTE)m_iHour22;
        m_struAlarmTime[i][1].byStopMin = (BYTE)m_iMin22;
        m_struAlarmTime[i][2].byStartHour = (BYTE)m_iHour31;
        m_struAlarmTime[i][2].byStartMin = (BYTE)m_iMin31;
        m_struAlarmTime[i][2].byStopHour = (BYTE)m_iHour32;
        m_struAlarmTime[i][2].byStopMin = (BYTE)m_iMin32;
        m_struAlarmTime[i][3].byStartHour = (BYTE)m_iHour41;
        m_struAlarmTime[i][3].byStartMin = (BYTE)m_iMin41;
        m_struAlarmTime[i][3].byStopHour = (BYTE)m_iHour42;
        m_struAlarmTime[i][3].byStopMin = (BYTE)m_iMin42;
        
        m_struAlarmTime[i][4].byStartHour = (BYTE)m_iHour51;
        m_struAlarmTime[i][4].byStartMin = (BYTE)m_iMin51;
        m_struAlarmTime[i][4].byStopHour = (BYTE)m_iHour52;
        m_struAlarmTime[i][4].byStopMin = (BYTE)m_iMin52;
        m_struAlarmTime[i][5].byStartHour = (BYTE)m_iHour61;
        m_struAlarmTime[i][5].byStartMin = (BYTE)m_iMin61;
        m_struAlarmTime[i][5].byStopHour = (BYTE)m_iHour62;
        m_struAlarmTime[i][5].byStopMin = (BYTE)m_iMin62;
        m_struAlarmTime[i][6].byStartHour = (BYTE)m_iHour71;
        m_struAlarmTime[i][6].byStartMin = (BYTE)m_iMin71;
        m_struAlarmTime[i][6].byStopHour = (BYTE)m_iHour72;
        m_struAlarmTime[i][6].byStopMin = (BYTE)m_iMin72;
        m_struAlarmTime[i][7].byStartHour = (BYTE)m_iHour81;
        m_struAlarmTime[i][7].byStartMin = (BYTE)m_iMin81;
        m_struAlarmTime[i][7].byStopHour = (BYTE)m_iHour82;
    	m_struAlarmTime[i][7].byStopMin = (BYTE)m_iMin82;

        m_bySceneID[i][0] = (BYTE)m_comSceneID1.GetCurSel();
        m_bySceneID[i][1] = (BYTE)m_comSceneID2.GetCurSel();
        m_bySceneID[i][2] = (BYTE)m_comSceneID3.GetCurSel();
        m_bySceneID[i][3] = (BYTE)m_comSceneID4.GetCurSel();
        m_bySceneID[i][4] = (BYTE)m_comSceneID5.GetCurSel();
        m_bySceneID[i][5] = (BYTE)m_comSceneID6.GetCurSel();
        m_bySceneID[i][6] = (BYTE)m_comSceneID7.GetCurSel();
        m_bySceneID[i][7] = (BYTE)m_comSceneID8.GetCurSel();

    }

	
// 	for (i=0; i<MAX_CHANNUM_V30; i++)
// 	{
// 		m_lpAlarmIn->byRelRecordChan[i] = (BYTE)m_bRecordChan[i];
// 	}
	
	m_pStruAlarmHandleType->dwHandleType = 0;
	m_pStruAlarmHandleType->dwHandleType |= (m_bChkMonitorAlarm << 0);
	m_pStruAlarmHandleType->dwHandleType |= (m_bChkVoiceAlarm << 1);
	m_pStruAlarmHandleType->dwHandleType |= (m_bChkUploadCenter << 2);
	m_pStruAlarmHandleType->dwHandleType |= (m_bChkInvokeAlarmOut << 3);
	m_pStruAlarmHandleType->dwHandleType |= (m_bChkInvokeJpegCapture << 4);
	m_pStruAlarmHandleType->dwHandleType |= (m_bChkEmapAlarmOut<<6);
	m_pStruAlarmHandleType->dwHandleType |= (m_bChkPicToFtp << 9);
    m_pStruAlarmHandleType->dwHandleType |= (m_bChkPicToCloud << 12);
	m_pStruAlarmHandleType->dwHandleType |= (m_bChkFocusAlarm << 10);
	m_pStruAlarmHandleType->dwHandleType |= (m_bChkPTZAlarm << 11);
	int iAlarmOutCount = 0;
	DWORD dwRelAlarmOutChanNum = 0;
	memset(m_pStruAlarmHandleType->dwRelAlarmOut, 0xffffffff, sizeof(m_pStruAlarmHandleType->dwRelAlarmOut));
	for (i=0; i < MAX_ALARMOUT_V40; i++)
	{

		if (m_pbAlarmOut[i])
		{
			m_pStruAlarmHandleType->dwRelAlarmOut[dwRelAlarmOutChanNum++] = i;
		}
	}
	 


// 	int iRecordCount = 0;
// 	for (int k = 0; k < MAX_CHANNUM_V30; k++)
// 	{
// 		if (m_bRecordChan[k])
// 		{
// 			iRecordCount++;
// 		}
// 		else
// 		{
// 			break; //是紧凑排列的只要找到空的
// 		}
// 	}

	//以下是音频异常专有
	m_struAudioException.struAudioAbnormal.byEnable = m_bAudioAbnormal;
	m_struAudioException.struAudioAbnormal.bySensitivity = atoi(m_iAudioSen);
	m_struAudioException.struAudioAbnormal.byThreshold = atoi(m_iAudioThreshold);
	//m_struAudioException.dwRelRecordChanNum = iRecordCount;

	m_struLineDetection.struAlertParam[m_Combo_LineNo.GetCurSel()].bySensitivity = atoi(m_iLineSen);
	m_struLineDetection.struAlertParam[m_Combo_LineNo.GetCurSel()].dwCrossDirection = (VCA_CROSS_DIRECTION)atoi(m_iCross);

    m_bTraverseDetTarget = 1;
    if (!m_bTraverseDetTargetHuman)
    {
        m_bTraverseDetTarget &= 0;
    }
    if (m_bTraverseDetTargetVerhicle)
    {
        m_bTraverseDetTarget |= (1 << 1);
    }
    if (m_bTraverseDetTargetAll)
    {
        m_bTraverseDetTarget = 0;
    }
    m_struLineDetection.struAlertParam[m_Combo_LineNo.GetCurSel()].byDetectionTarget = m_bTraverseDetTarget;
	//m_struLineDetection.struAlertParam[m_Combo_LineNo.GetCurSel()].byDetectionTarget = m_comTraverseDetTarget.GetCurSel();
	//m_struLineDetection.dwRelRecordChanNum = iRecordCount;
    m_struLineDetection.struHandleException.byWhiteLightDurationTime = m_bTraverseWhiteLightDurationTime;
	
	//区域入侵
	m_struFieldDetection.struIntrusion[m_Comnbo_FieldNo.GetCurSel()].bySensitivity = atoi(m_iFieldSen);
	m_struFieldDetection.struIntrusion[m_Comnbo_FieldNo.GetCurSel()].byRate = atoi(m_iFieldRate);
	m_struFieldDetection.struIntrusion[m_Comnbo_FieldNo.GetCurSel()].wDuration = atoi(m_iFieldDuration);

    m_bIntrusionDetTarget = 1;
    if (!m_bIntrusionDetTargetHuman)
    {
        m_bIntrusionDetTarget &= 0;
    }
    if (m_bIntrusionDetTargetVerhicle)
    {
        m_bIntrusionDetTarget |= (1 << 1);
    }
    if (m_bIntrusionDetTargetAll)
    {
        m_bIntrusionDetTarget = 0;
    }

    m_struFieldDetection.struIntrusion[m_Comnbo_FieldNo.GetCurSel()].byDetectionTarget = m_bIntrusionDetTarget;
	//m_struFieldDetection.struIntrusion[m_Comnbo_FieldNo.GetCurSel()].byDetectionTarget = m_comIntrusionDetTarget.GetCurSel();
    m_struFieldDetection.struHandleException.byWhiteLightDurationTime = m_bIntrusionWhiteLightDurationTime;
	//m_struFieldDetection.dwRelRecordChanNum = iRecordCount;

	//场景变更侦测2013-07-17
	m_struSceneDetection.bySensitiveLevel = m_iSceneSen;
	//m_struSceneDetection.dwRelRecordChanNum = iRecordCount;
}

//************************************
// Method:    GetAudioException
// FullName:  CDlgIPCSimpIntellCfg::GetAudioException
// Access:    protected 
// Returns:   void
// Qualifier:
//************************************
void CDlgIPCSimpIntellCfg::GetAudioException()
{
	int iCount = 1;
	NET_DVR_CHANNEL_GROUP struAudioDetectionCond = {0};
	struAudioDetectionCond.dwChannel = m_lChannel;//m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    struAudioDetectionCond.dwGroup = m_cmbGroupNo.GetItemData(m_cmbGroupNo.GetCurSel());
	struAudioDetectionCond.dwSize = sizeof(struAudioDetectionCond);
	int pStatus = 0;
    char szLan[128] = {0};
	BOOL bRet = NET_DVR_GetDeviceConfig(m_lLoginID, NET_DVR_GET_AUDIOEXCEPTIONPARAM, iCount, &struAudioDetectionCond, \
		sizeof(NET_DVR_CHANNEL_GROUP), &pStatus, &m_struAudioException, sizeof(m_struAudioException));
	if (bRet && pStatus==0)
	{
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_AUDIOEXCEPTIONPARAM");
    }
    else
    {
        sprintf(szLan,"err %d",pStatus);
        AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_AUDIOEXCEPTIONPARAM");
    }
}

void CDlgIPCSimpIntellCfg::SaveAudioException()
{
	int iCount = 1;
	NET_DVR_CHANNEL_GROUP struAudioExceptionCond = {0};
	struAudioExceptionCond.dwChannel = m_lChannel;//m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    struAudioExceptionCond.dwGroup = m_cmbGroupNo.GetItemData(m_cmbGroupNo.GetCurSel());
	struAudioExceptionCond.dwSize = sizeof(struAudioExceptionCond);
	int pStatus = 0;
    char szLan[128] = {0};
	m_struAudioException.dwSize = sizeof(m_struAudioException);
	BOOL bRet = NET_DVR_SetDeviceConfig(m_lLoginID, NET_DVR_SET_AUDIOEXCEPTIONPARAM, iCount, &struAudioExceptionCond, \
		sizeof(NET_DVR_CHANNEL_GROUP), &pStatus, &m_struAudioException, sizeof(m_struAudioException));
	if (bRet && pStatus == 0)
	{
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_AUDIOEXCEPTIONPARAM");
    }
    else
    {
        sprintf(szLan,"err %d",pStatus);
        AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_AUDIOEXCEPTIONPARAM");
    }
}

void CDlgIPCSimpIntellCfg::GetSceneDetection()//场景变更侦测2013-07-17
{
	int iCount = 1;
	NET_DVR_CHANNEL_GROUP struSceneDetectionCond = {0};
	struSceneDetectionCond.dwChannel = m_lChannel;//m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    struSceneDetectionCond.dwGroup = m_cmbGroupNo.GetItemData(m_cmbGroupNo.GetCurSel());
	struSceneDetectionCond.dwSize = sizeof(struSceneDetectionCond);
	int pStatus = 0;
    char szLan[128] = {0};
	BOOL bRet = NET_DVR_GetDeviceConfig(m_lLoginID, NET_DVR_GET_SCENECHANGE_DETECTIONCFG, iCount, &struSceneDetectionCond, \
		sizeof(NET_DVR_CHANNEL_GROUP), &pStatus, &m_struSceneDetection, sizeof(m_struSceneDetection));
	if (bRet && pStatus == 0)
	{
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SCENECHANGE_DETECTIONCFG");
    }
    else
    {
        sprintf(szLan,"err %d",pStatus);
        AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SCENECHANGE_DETECTIONCFG");
    }
}

void CDlgIPCSimpIntellCfg::SaveSceneDetection()//场景变更侦测2013-07-17
{
	int iCount = 1;
	NET_DVR_CHANNEL_GROUP struSceneDetectionCond = {0};
	struSceneDetectionCond.dwChannel = m_lChannel;//m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    struSceneDetectionCond.dwGroup = m_cmbGroupNo.GetItemData(m_cmbGroupNo.GetCurSel());
	struSceneDetectionCond.dwSize = sizeof(struSceneDetectionCond);
	int pStatus = 0;
    char szLan[128] = {0};
	m_struSceneDetection.dwSize = sizeof(m_struSceneDetection);
	BOOL bRet = NET_DVR_SetDeviceConfig(m_lLoginID, NET_DVR_SET_SCENECHANGE_DETECTIONCFG, iCount, &struSceneDetectionCond, \
		sizeof(NET_DVR_CHANNEL_GROUP), &pStatus, &m_struSceneDetection, sizeof(m_struSceneDetection));
	if (bRet && pStatus == 0)
	{
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_SCENECHANGE_DETECTIONCFG");
    }
    else
    {
        sprintf(szLan,"err %d",pStatus);
        AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SCENECHANGE_DETECTIONCFG");
    }
}

void CDlgIPCSimpIntellCfg::GetRegionEntrDetection()
{    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &m_struRegionEntrDetection;
    struCfg.dwOutSize = sizeof(m_struRegionEntrDetection);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_REGION_ENTR_DETECTION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_REGION_ENTR_DETECTION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_REGION_ENTR_DETECTION");
    }
}

void CDlgIPCSimpIntellCfg::SaveRegionEntrDetection()
{    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &m_struRegionEntrDetection;
    struCfg.dwInSize = sizeof(m_struRegionEntrDetection);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    m_struRegionEntrDetection.dwSize = sizeof(m_struRegionEntrDetection);    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_REGION_ENTR_DETECTION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_REGION_ENTR_DETECTION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_REGION_ENTR_DETECTION");
    }
}

void CDlgIPCSimpIntellCfg::GetRegionExitDetection()
{    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &m_struRegionExitDetection;
    struCfg.dwOutSize = sizeof(m_struRegionExitDetection);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_REGION_EXITING_DETECTION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_REGION_EXITING_DETECTION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_REGION_EXITING_DETECTION");
    }
}

void CDlgIPCSimpIntellCfg::SaveRegionExitDetection()
{    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &m_struRegionExitDetection;
    struCfg.dwInSize = sizeof(m_struRegionExitDetection);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    m_struRegionExitDetection.dwSize = sizeof(m_struRegionExitDetection);
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_REGION_EXITING_DETECTION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_REGION_EXITING_DETECTION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_REGION_EXITING_DETECTION");
    }
}

void CDlgIPCSimpIntellCfg::GetLoiterDetection()
{    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &m_struLoiterDetection;
    struCfg.dwOutSize = sizeof(m_struLoiterDetection);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_LOITERING_DETECTION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_LOITERING_DETECTION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_LOITERING_DETECTION");
    }
}

void CDlgIPCSimpIntellCfg::SaveLoiterDetection()
{    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &m_struLoiterDetection;
    struCfg.dwInSize = sizeof(m_struLoiterDetection);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    m_struLoiterDetection.dwSize = sizeof(m_struLoiterDetection);
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_LOITERING_DETECTION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_LOITERING_DETECTION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_LOITERING_DETECTION");
    }
}

void CDlgIPCSimpIntellCfg::GetGroupDetection()
{    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &m_struGroupDetection;
    struCfg.dwOutSize = sizeof(m_struGroupDetection);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_GROUP_DETECTION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_GROUP_DETECTION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_GROUP_DETECTION");
    }
}

void CDlgIPCSimpIntellCfg::SaveGroupDetection()
{    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &m_struGroupDetection;
    struCfg.dwInSize = sizeof(m_struGroupDetection);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    m_struGroupDetection.dwSize = sizeof(m_struGroupDetection);
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_GROUP_DETECTION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_GROUP_DETECTION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_GROUP_DETECTION");
    }
}

void CDlgIPCSimpIntellCfg::GetRapidMoveDetection()
{    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &m_struRapidMove;
    struCfg.dwOutSize = sizeof(m_struRapidMove);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_RAPIDMOVE_DETECTION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_RAPIDMOVE_DETECTION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_RAPIDMOVE_DETECTION");
    }
}

void CDlgIPCSimpIntellCfg::SaveRapidMoveDetection()
{    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &m_struRapidMove;
    struCfg.dwInSize = sizeof(m_struRapidMove);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    m_struRapidMove.dwSize = sizeof(m_struRapidMove);
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_RAPIDMOVE_DETECTION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_RAPIDMOVE_DETECTION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_RAPIDMOVE_DETECTION");
    }
}

void CDlgIPCSimpIntellCfg::GetParkDetection()
{    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &m_struParkDetection;
    struCfg.dwOutSize = sizeof(m_struParkDetection);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_PARKING_DETECTION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PARKING_DETECTION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_PARKING_DETECTION");
    }
}

void CDlgIPCSimpIntellCfg::SaveParkDetection()
{    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &m_struParkDetection;
    struCfg.dwInSize = sizeof(m_struParkDetection);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    m_struParkDetection.dwSize = sizeof(m_struParkDetection);
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_PARKING_DETECTION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_PARKING_DETECTION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PARKING_DETECTION");
    }
}

void CDlgIPCSimpIntellCfg::GetUnattendedDetection()
{    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &m_struUnattended;
    struCfg.dwOutSize = sizeof(m_struUnattended);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_UNATTENDED_BAGGAGE_DETECTION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_UNATTENDED_BAGGAGE_DETECTION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_UNATTENDED_BAGGAGE_DETECTION");
    }
}

void CDlgIPCSimpIntellCfg::SaveUnattendedDetection()
{    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &m_struUnattended;
    struCfg.dwInSize = sizeof(m_struUnattended);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    m_struUnattended.dwSize = sizeof(m_struUnattended);
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_UNATTENDED_BAGGAGE_DETECTION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_UNATTENDED_BAGGAGE_DETECTION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_UNATTENDED_BAGGAGE_DETECTION");
    }
}

void CDlgIPCSimpIntellCfg::GetAttendedDetection()
{    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &m_struAttended;
    struCfg.dwOutSize = sizeof(m_struAttended);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_ATTENDEDBAGGAGE_DETECTION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ATTENDEDBAGGAGE_DETECTION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ATTENDEDBAGGAGE_DETECTION");
    }
}

void CDlgIPCSimpIntellCfg::SaveAttendedDetection()
{    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &m_struAttended;
    struCfg.dwInSize = sizeof(m_struAttended);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    m_struAttended.dwSize = sizeof(m_struAttended);
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_ATTENDEDBAGGAGE_DETECTION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_ATTENDEDBAGGAGE_DETECTION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_ATTENDEDBAGGAGE_DETECTION");
    }
}

void CDlgIPCSimpIntellCfg::GetClipCfg()
{
    NET_DVR_REGION_CLIP_COND struCond = {0};
    struCond.dwSize = sizeof(struCond);
    struCond.dwChannel = m_lChannel;
    struCond.dwStreamType = m_cmbStreamType.GetCurSel();
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &struCond;
    struCfg.dwCondSize = sizeof(struCond);
    struCfg.lpOutBuffer = &m_struClipCfg;
    struCfg.dwOutSize = sizeof(m_struClipCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_REGION_CLIP, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_REGION_CLIP");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_REGION_CLIP");
    }
}

void CDlgIPCSimpIntellCfg::SaveClipCfg()
{
    NET_DVR_REGION_CLIP_COND struCond = {0};
    struCond.dwSize = sizeof(struCond);
    struCond.dwChannel = m_lChannel;
    struCond.dwStreamType = m_cmbStreamType.GetCurSel();
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &struCond;
    struCfg.dwCondSize = sizeof(struCond);
    struCfg.lpInBuffer = &m_struClipCfg;
    struCfg.dwInSize = sizeof(m_struClipCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_REGION_CLIP, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_REGION_CLIP");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_REGION_CLIP");
    }
}

BOOL CDlgIPCSimpIntellCfg::PreDrawRectMsg(MSG* pMsg, CPoint &pt, NET_VCA_POLYGON &struRegion)
{
    int i=0;
    BOOL bOneLine = TRUE,bXOneLine = TRUE,bYOneLine = TRUE;
    UpdateData(TRUE);
    switch (pMsg->message)
    {
    case WM_LBUTTONDOWN:
        if ((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) && 
            PtInRect(&m_rcWnd,pt))
        {
       //     if(m_bNeedRedraw)
            {
				
                struRegion.struPos[0].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                struRegion.struPos[0].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();

                struRegion.struPos[1].fX = struRegion.struPos[0].fX + (float)m_nResolutionWidth/(float)m_nMaxWidth;
                struRegion.struPos[1].fY = struRegion.struPos[0].fY;
                
                struRegion.struPos[2].fX = struRegion.struPos[0].fX + (float)m_nResolutionWidth/(float)m_nMaxWidth;
                struRegion.struPos[2].fY = struRegion.struPos[0].fY + (float)m_nResolutionHeight/(float)m_nMaxHeight;

                struRegion.struPos[3].fX = struRegion.struPos[0].fX;
                struRegion.struPos[3].fY = struRegion.struPos[0].fY + (float)m_nResolutionHeight/(float)m_nMaxHeight;
                struRegion.dwPointNum = 4;	
            }
            
        }
        break;
    }
    return TRUE;
}

BOOL CDlgIPCSimpIntellCfg::PreDrawPolygonMsg( MSG* pMsg, CPoint &pt, NET_VCA_POLYGON &struRegion)
{
	int i=0;
    BOOL bOneLine = TRUE,bXOneLine = TRUE,bYOneLine = TRUE;

    switch (pMsg->message)
    {
    case WM_LBUTTONDOWN:
        if ((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) && 
            PtInRect(&m_rcWnd,pt))
        {
       //     if(m_bNeedRedraw)
            {
				if (m_dwPosNum > 19)
				{
					m_bCloseIn = TRUE;
				}
                if(m_bCloseIn)
                {
                    m_dwPosNum = 0;
                    struRegion.dwPointNum = m_dwPosNum;
					memset(&struRegion, 0, sizeof(NET_VCA_POLYGON));
                }
                if(m_dwPosNum > 19)
                {
                    char szLan[128] = {0};
                    g_StringLanType(szLan,"多边形顶点不能超过20个!","Apexes of polygon should less than 20");
                    AfxMessageBox(szLan);
                    return TRUE;
                }
				if((float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() <= struRegion.struPos[m_dwPosNum-1].fX+0.01 && (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() >= struRegion.struPos[m_dwPosNum-1].fX-0.01\
                    && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() <= struRegion.struPos[m_dwPosNum-1].fY+0.01 && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() >= struRegion.struPos[m_dwPosNum-1].fY-0.01)
                {
                    char szLan[128] = {0};
                    g_StringLanType(szLan, "不能连续在同一点上画区域", "Can't draw region on the point used");
                    AfxMessageBox(szLan);
                    return TRUE;
                }
                m_bCloseIn = FALSE;
                m_bMouseMovePolygon = FALSE;
                struRegion.struPos[m_dwPosNum].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                struRegion.struPos[m_dwPosNum].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
                m_dwPosNum++;
                struRegion.dwPointNum = m_dwPosNum;	
            }
            
        }
        break;
    case WM_MOUSEMOVE:
        if ((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) && 
            PtInRect(&m_rcWnd,pt))
        {
                if(PtInRect(&m_rcWnd,pt))
                {
                    if(m_dwPosNum > 19)
                    {
                        return TRUE;
                    }
                    if( !m_bCloseIn)
                    {
                        m_bMouseMovePolygon = TRUE;
                        struRegion.struPos[m_dwPosNum].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                        struRegion.struPos[m_dwPosNum].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
                        struRegion.dwPointNum = m_dwPosNum+1;				
                    }
                }
        }

        break;
    case WM_RBUTTONDOWN:
        if((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) 
            && PtInRect(&m_rcWnd,pt))
        {
                if(m_dwPosNum > 19)
                {
                    return TRUE;
                }
                for(i=0; i<m_dwPosNum; i++)
                {
                    if(struRegion.struPos[i].fX != struRegion.struPos[i+1].fX)
                    {
                        bXOneLine = FALSE;
                        break;
                    }
                }
                for(i=0; i<m_dwPosNum; i++)
                {
                    if(struRegion.struPos[i].fY != struRegion.struPos[i+1].fY)
                    {
                        bYOneLine = FALSE;
                        break;
                    }
                }
                bOneLine = bXOneLine||bYOneLine;
                if(bOneLine)
                {
                    char szlan[128] = {0};
                    g_StringLanType(szlan, "所画点成一线，无法构成区域!","The points is on a line and can't create a rectangle!");
                    AfxMessageBox(szlan);
                    return TRUE;
                }
                if( !m_bCloseIn)
                {
                    if(m_bMouseMovePolygon)
                    {
                        m_bMouseMovePolygon = FALSE;
                        struRegion.dwPointNum--;
                        struRegion.struPos[struRegion.dwPointNum].fX = 0;
                        struRegion.struPos[struRegion.dwPointNum].fY = 0;
                    }
                    m_bCloseIn = TRUE;
                }
		}
        break;
    }
     return TRUE;
}

void CDlgIPCSimpIntellCfg::OnLineNoChanged()
{
//	if (m_Combo_CfgType.GetCurSel() == 0)
	{
		UpdateData(TRUE);
		
		m_struLineDetection.struAlertParam[m_iLineNo].bySensitivity = atoi(m_iLineSen);
		m_struLineDetection.struAlertParam[m_iLineNo].dwCrossDirection = (VCA_CROSS_DIRECTION)atoi(m_iCross);
        m_bTraverseDetTarget = 1;
        if (m_bTraverseDetTargetHuman)
        {
            m_bTraverseDetTarget |= 1;
        }
        if (m_bTraverseDetTargetVerhicle)
        {
            m_bTraverseDetTarget |= (1 << 1);
        }
        if (m_bTraverseDetTargetAll)
        {
            m_bTraverseDetTarget = 0;
        }
        m_struLineDetection.struAlertParam[m_Combo_LineNo.GetCurSel()].byDetectionTarget = m_bTraverseDetTarget;
		//m_struLineDetection.struAlertParam[m_iLineNo].byDetectionTarget = m_comTraverseDetTarget.GetCurSel();
				
		//然后把当前值拷贝到页面
		m_iLineNo = m_Combo_LineNo.GetCurSel();
		m_iLineSen.Format("%d", m_struLineDetection.struAlertParam[m_iLineNo].bySensitivity);
	//	m_iLineSen = m_struLineDetection.struAlertParam[m_iLineNo].bySensitivity;
		m_iCross.Format("%d", m_struLineDetection.struAlertParam[m_Combo_LineNo.GetCurSel()].dwCrossDirection);
	//	m_iCross = m_struLineDetection.struAlertParam[m_Combo_LineNo.GetCurSel()].dwCrossDirection;

        m_bTraverseDetTarget = 1;
        if (m_bTraverseDetTargetHuman)
        {
            m_bTraverseDetTarget |= 1;
        }
        if (m_bTraverseDetTargetVerhicle)
        {
            m_bTraverseDetTarget |= (1 << 1);
        }
        if (m_bTraverseDetTargetAll)
        {
            m_bTraverseDetTarget = 0;
        }
        m_struLineDetection.struAlertParam[m_Combo_LineNo.GetCurSel()].byDetectionTarget = m_bTraverseDetTarget;
		//m_comTraverseDetTarget.SetCurSel(m_struLineDetection.struAlertParam[m_Combo_LineNo.GetCurSel()].byDetectionTarget);
		UpdateData(FALSE);
	}
}

void CDlgIPCSimpIntellCfg::OnFieldNoChanged()
{
	//if (m_Combo_CfgType.GetCurSel() == 1)
	{
		UpdateData(TRUE);

		m_dwPosNum = 0;
		//区域入侵
		m_struFieldDetection.struIntrusion[m_iFieldNo].bySensitivity = atoi(m_iFieldSen);
		m_struFieldDetection.struIntrusion[m_iFieldNo].byRate = atoi(m_iFieldRate);
		m_struFieldDetection.struIntrusion[m_iFieldNo].wDuration = atoi(m_iFieldDuration);

        m_bIntrusionDetTarget = 1;
        if (m_bIntrusionDetTargetHuman)
        {
            m_bIntrusionDetTarget |= 1;
        }
        if (m_bIntrusionDetTargetVerhicle)
        {
            m_bIntrusionDetTarget |= (1 << 1);
        }
        if (m_bIntrusionDetTargetAll)
        {
            m_bIntrusionDetTarget = 0;
        }

        m_struFieldDetection.struIntrusion[m_Comnbo_FieldNo.GetCurSel()].byDetectionTarget = m_bIntrusionDetTarget;
		//m_struFieldDetection.struIntrusion[m_iFieldNo].byDetectionTarget = m_comIntrusionDetTarget.GetCurSel();

		//然后把当前值拷贝到页面
		m_iFieldNo = m_Comnbo_FieldNo.GetCurSel();

		m_iFieldSen.Format("%d", m_struFieldDetection.struIntrusion[m_iFieldNo].bySensitivity);
	//	m_iFieldSen = m_struFieldDetection.struIntrusion[m_iFieldNo].bySensitivity;
		m_iFieldRate.Format("%d", m_struFieldDetection.struIntrusion[m_iFieldNo].byRate);
	//	m_iFieldRate = m_struFieldDetection.struIntrusion[m_iFieldNo].byRate;
		m_iFieldDuration.Format("%d", m_struFieldDetection.struIntrusion[m_iFieldNo].wDuration);
	//	m_iFieldDuration = m_struFieldDetection.struIntrusion[m_iFieldNo].wDuration;

		UpdateData(FALSE);
	}
}

BOOL CDlgIPCSimpIntellCfg::PreDrawLineMsg( MSG* pMsg, CPoint &pt )
{
  //  UpdateData(TRUE);
	CString strTemp = _T("");
    DWORD i=0;
    BOOL bOneLine = TRUE,bXOneLine = TRUE,bYOneLine = TRUE;
 
    switch(pMsg->message)  // Message of Draw
    {
    case WM_LBUTTONDOWN:
 
        if( (m_Combo_CfgType.GetCurSel() == 0) &&
            ((GetAsyncKeyState(VK_LCONTROL)< 0) || (GetAsyncKeyState(VK_RCONTROL) < 0)))//Press CTRL to draw
		{
			if(!m_bMouseMove) 
			{
				m_struLineDetection.struAlertParam[m_iLineNo].struPlaneBottom.struStart.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
				m_struLineDetection.struAlertParam[m_iLineNo].struPlaneBottom.struStart.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();		
				m_struLineDetection.struAlertParam[m_iLineNo].struPlaneBottom.struEnd.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
				m_struLineDetection.struAlertParam[m_iLineNo].struPlaneBottom.struEnd.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();			
				m_bMouseMove = TRUE;
			}
			else
			{
				if ((float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() <= m_struLineDetection.struAlertParam[m_iLineNo].struPlaneBottom.struStart.fX+0.01 && (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() >= m_struLineDetection.struAlertParam[m_iLineNo].struPlaneBottom.struStart.fX-0.01\
					&& (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() <= m_struLineDetection.struAlertParam[m_iLineNo].struPlaneBottom.struStart.fY+0.01 && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() >= m_struLineDetection.struAlertParam[m_iLineNo].struPlaneBottom.struStart.fY-0.01)
				{
					char szLan[128] = {0};
					g_StringLanType(szLan, "不能连续在同一点上画区域", "Can't draw region on the point used");
					AfxMessageBox(szLan);
					return TRUE;
				}
				m_struLineDetection.struAlertParam[m_iLineNo].struPlaneBottom.struEnd.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
				m_struLineDetection.struAlertParam[m_iLineNo].struPlaneBottom.struEnd.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();			
				m_bMouseMove = FALSE;
             }
		}
        break;
    case WM_MOUSEMOVE:
        if( (m_Combo_CfgType.GetCurSel() == 0)  && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
			if(PtInRect(&m_rcWnd,pt))
            {
				if(m_bMouseMove)
				{
					m_struLineDetection.struAlertParam[m_iLineNo].struPlaneBottom.struEnd.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
					m_struLineDetection.struAlertParam[m_iLineNo].struPlaneBottom.struEnd.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();			
                }
			}
        }
        break;
    case WM_RBUTTONDOWN://Click right mouse to close the rectangle. 
        break;
    default:
        break;
    }
	return TRUE;
}

BOOL CDlgIPCSimpIntellCfg::PreTranslateMessage( MSG* pMsg )
{
	CPoint pt(0, 0);
	GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWnd);
	GetCursorPos(&pt);
	ScreenToClient(&m_rcWnd);
	ScreenToClient(&pt);
	
// 	if (m_bChkDrawPlate)
// 	{
// 		PreDrawPolygonMsg(pMsg, pt);
// 	}
	if (m_Combo_CfgType.GetCurSel() == 0)
	{
		PreDrawLineMsg(pMsg, pt);
	}
	else if(m_Combo_CfgType.GetCurSel() == 1)
	{
		PreDrawPolygonMsg(pMsg, pt, m_struFieldDetection.struIntrusion[m_iFieldNo].struRegion);
	}
    else if(m_Combo_CfgType.GetCurSel() == 5)
    {
        PreDrawPolygonMsg(pMsg, pt, m_struRegionEntrDetection.struRegion[m_cmbRegionEntrNo.GetCurSel()].struRegion);
	}
    else if(m_Combo_CfgType.GetCurSel() == 6)
    {
        PreDrawPolygonMsg(pMsg, pt, m_struRegionExitDetection.struRegion[m_cmbRegionExitNo.GetCurSel()].struRegion);
	}
    else if(m_Combo_CfgType.GetCurSel() == 7)
    {
        PreDrawPolygonMsg(pMsg, pt, m_struLoiterDetection.struRegion[m_cmbLoiterNo.GetCurSel()].struRegion);
	}
    else if(m_Combo_CfgType.GetCurSel() == 8)
    {
        PreDrawPolygonMsg(pMsg, pt, m_struGroupDetection.struRegion[m_cmbGroupDetectionNo.GetCurSel()].struRegion);
	}
    else if(m_Combo_CfgType.GetCurSel() == 9)
    {
        PreDrawPolygonMsg(pMsg, pt, m_struRapidMove.struRegion[m_cmbRapidMove.GetCurSel()].struRegion);
	}
    else if(m_Combo_CfgType.GetCurSel() == 10)
    {
        PreDrawPolygonMsg(pMsg, pt, m_struParkDetection.struRegion[m_cmbParkNo.GetCurSel()].struRegion);
	}
    else if(m_Combo_CfgType.GetCurSel() == 11)
    {
        PreDrawPolygonMsg(pMsg, pt, m_struUnattended.struRegion[m_cmbUnattendedNo.GetCurSel()].struRegion);
	}
    else if(m_Combo_CfgType.GetCurSel() == 12)
    {
        PreDrawPolygonMsg(pMsg, pt, m_struAttended.struRegion[m_cmbAttendedNo.GetCurSel()].struRegion);
	}	
	else if (m_Combo_CfgType.GetCurSel() == 13)
	{
        PreDrawRectMsg(pMsg, pt, m_struClipCfg.struRegion[m_cmbClipRegionNo.GetCurSel()]);
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgIPCSimpIntellCfg::F_DrawLine( HDC hDc )
{
	int iDirect = -1;
	int i = m_struLineDetection.struAlertParam[m_iLineNo].struPlaneBottom.struStart.fX;
    int x1 = (int)(m_struLineDetection.struAlertParam[m_iLineNo].struPlaneBottom.struStart.fX*m_rcWnd.Width());
    int y1 = (int)(m_struLineDetection.struAlertParam[m_iLineNo].struPlaneBottom.struStart.fY*m_rcWnd.Height());
    int x2 = (int)(m_struLineDetection.struAlertParam[m_iLineNo].struPlaneBottom.struEnd.fX*m_rcWnd.Width());
    int y2 = (int)(m_struLineDetection.struAlertParam[m_iLineNo].struPlaneBottom.struEnd.fY*m_rcWnd.Height());
	
	COLORREF color = RGB(0,255,0); 
    SetTextColor(hDc,color);
    
    using namespace Gdiplus;
    Graphics graphics(hDc);
    Color DrawColor;
    DrawColor.SetValue(DrawColor.MakeARGB(50,GetRValue(color) ,GetGValue(color),GetBValue(color)));
    
    Pen pen(color, 4);
    pen.SetStartCap(LineCapFlat);
    pen.SetEndCap(LineCapFlat);
    
    CPen DrawPen;
    DrawPen.CreatePen(PS_SOLID, 2, color);
    
	//     bool bRect = false;
	//     int k = 0;
	//     //calculate slope
	//     if(x2 != x1)
	//     {
	//         k = (y2 - y1) / (x2 - x1);
	//         
	//         //if the absolute value of slope is more than 2, draw rectangle directly
	//         if(abs(k) >= 2)
	//         {
	//             bRect = true;
	//         }
	//     }
	//     else
	//     {
	//         bRect = true;
	//     }
	//     
	//     if(bRect)
	//     {
	//         pen.SetColor(DrawColor);
	//         if(k < 0)
	//         {
	//             graphics.DrawLine(&pen, x1-2, y1-1, x2-2, y2-1);
	//         }
	//         else
	//         {
	//             graphics.DrawLine(&pen, x1+2, y1-1, x2+2, y2-1);
	//         }
	//     }
	//     else
	//     {
	//         //Draw parallelogram, the vertical height is 8
	//         SolidBrush  brush(DrawColor);
	//         POINT point[4];
	//         point[0].x = x1;
	//         point[0].y = y1;
	//         point[1].x = x2;
	//         point[1].y = y2;
	//         point[2].x = x2;
	//         point[2].y = y2-8;
	//         point[3].x = x1;
	//         point[3].y = y1-8;
	//         graphics.FillPolygon(&brush, (Point *)point, 4);
	//     }
    
    
    HGDIOBJ pOldPen = SelectObject(hDc, DrawPen);
    MoveToEx(hDc, x1, y1, NULL);
    LineTo(hDc, x2, y2);
    
    //Draw arrow
	//    F_DrawArrowhead(hDc, lpDrawTaversePlane);
    //Draw label
    
    SelectObject(hDc, pOldPen);
	DeleteObject(DrawPen);
}

void CDlgIPCSimpIntellCfg::F_DrawFun( long lPlayHandle, HDC hDc, DWORD dwUser )
{
	if (m_Combo_CfgType.GetCurSel() == 0)
	{
		F_DrawLine(hDc);
	}
	else if (m_Combo_CfgType.GetCurSel() == 1)
	{
		F_DrawPolygon(hDc, m_struFieldDetection.struIntrusion[m_iFieldNo].struRegion);
	}
    else if(m_Combo_CfgType.GetCurSel() == 5)
    {
        F_DrawPolygon(hDc, m_struRegionEntrDetection.struRegion[m_cmbRegionEntrNo.GetCurSel()].struRegion);
    }
    else if(m_Combo_CfgType.GetCurSel() == 6)
    {
        F_DrawPolygon(hDc, m_struRegionExitDetection.struRegion[m_cmbRegionExitNo.GetCurSel()].struRegion);
    }
    else if(m_Combo_CfgType.GetCurSel() == 7)
    {
        F_DrawPolygon(hDc, m_struLoiterDetection.struRegion[m_cmbLoiterNo.GetCurSel()].struRegion);
    }
    else if(m_Combo_CfgType.GetCurSel() == 8)
    {
        F_DrawPolygon(hDc, m_struGroupDetection.struRegion[m_cmbGroupDetectionNo.GetCurSel()].struRegion);
    }
    else if(m_Combo_CfgType.GetCurSel() == 9)
    {
        F_DrawPolygon(hDc, m_struRapidMove.struRegion[m_cmbRapidMove.GetCurSel()].struRegion);
    }
    else if(m_Combo_CfgType.GetCurSel() == 10)
    {
        F_DrawPolygon(hDc, m_struParkDetection.struRegion[m_cmbParkNo.GetCurSel()].struRegion);
    }
    else if(m_Combo_CfgType.GetCurSel() == 11)
    {
        F_DrawPolygon(hDc, m_struUnattended.struRegion[m_cmbUnattendedNo.GetCurSel()].struRegion);
    }
    else if(m_Combo_CfgType.GetCurSel() == 12)
    {
        F_DrawPolygon(hDc, m_struAttended.struRegion[m_cmbAttendedNo.GetCurSel()].struRegion);
	}
    else if (m_Combo_CfgType.GetCurSel() == 13)
    {
        F_DrawPolygon(hDc, m_struClipCfg.struRegion[m_cmbClipRegionNo.GetCurSel()]);
    }
}

void CDlgIPCSimpIntellCfg::F_DrawPolygon( HDC hDc, NET_VCA_POLYGON &struRegion)
{
	using namespace Gdiplus;
    Graphics graphics(hDc);
    SolidBrush  brush(Color(50, 0, 0, 0));
	COLORREF color = RGB(0,255,0); 
    brush.SetColor(Color(50, GetRValue(color), GetGValue(color), GetBValue(color)));
    
    POINT point[ITC_MAX_POLYGON_POINT_NUM] = {0};
    
    CPen DrawPen;
    unsigned int i;
    
    DrawPen.CreatePen(PS_SOLID, 2, color);
    SetTextColor(hDc,color);
    SetBkMode(hDc, TRANSPARENT);
    
    HGDIOBJ pOldPen = SelectObject(hDc, DrawPen);
    MoveToEx(hDc, (int)(struRegion.struPos[0].fX*m_rcWnd.Width()), \
        (int)(struRegion.struPos[0].fY*m_rcWnd.Height()), NULL);
    
    for(i=1; i<struRegion.dwPointNum && i < VCA_MAX_POLYGON_POINT_NUM + 1; i++)
    {
        
        LineTo(hDc, (int)(struRegion.struPos[i].fX*m_rcWnd.Width()),\
            (int)(struRegion.struPos[i].fY*m_rcWnd.Height()));
        //Redraw the polygon if the lines are intersectant.
		
		if (i>=MIN_PNT_NUM)
		{
			if (!m_bMouseMove)
			{
				if (IsCrossLine(&(struRegion)))
				{
					{
						char szLan[128] = {0};
						g_StringLanType(szLan,"多边形不相邻的边有相交情况存在,请重新输入!","Edges of Polygon can be intersectant, please redraw.!");
						//		AfxMessageBox(szLan);
						struRegion.dwPointNum--;
						m_dwPosNum = struRegion.dwPointNum;
						memset(&struRegion.struPos[struRegion.dwPointNum], 0, sizeof(NET_VCA_POINT));
						break;
					}
				}
			}
		}
		//        if(i>=MIN_PNT_NUM && !lpDrawPolygon->bMouseMove && IsCrossLine(&lpDrawPolygon->struVcaPolygon))
		//         {
		//             char szLan[128] = {0};
		//             g_StringLanType(szLan,"多边形不相邻的边有相交情况存在,请重新输入!","Edges of Polygon can be intersectant, please redraw.!");
		//             //AfxMessageBox(szLan);
		//             lpDrawPolygon->struVcaPolygon.dwPointNum--;
		//             break;
		//         }
    }
    
    for (i=0; i<(int)struRegion.dwPointNum ; i++)
    {
        if (i == ITC_MAX_POLYGON_POINT_NUM)
        {
            break;
        }
        
        point[i].x = (int)(struRegion.struPos[i].fX*m_rcWnd.Width());
        point[i].y = (int)(struRegion.struPos[i].fY*m_rcWnd.Height());
    }
    //After drawing the 10th point, connect it with the 1st point.
    if(ITC_MAX_POLYGON_POINT_NUM == i && !m_bMouseMove)
    {
        if (IsValidArea(&struRegion))
        {
            graphics.FillPolygon(&brush, (Point *)point, struRegion.dwPointNum);
            
            LineTo(hDc, point[0].x, point[0].y);
           // TextOut(hDc, point[0].x, point[0].y, lpDrawPolygon->chName, strlen(lpDrawPolygon->chName));
			
            m_bCloseIn = TRUE;
        }else//redraw
        {
			
        }
        //check if the alarm region is intact
    }
    else if(struRegion.dwPointNum>2 && m_bCloseIn)
    {
        if (IsValidArea(&struRegion))
        {
            graphics.FillPolygon(&brush, (Point *)point, struRegion.dwPointNum);
            
            LineTo(hDc, point[0].x, point[0].y);
			
         //   TextOut(hDc, point[0].x, point[0].y, lpDrawPolygon->chName, strlen(lpDrawPolygon->chName));
			//            F_AddLabel(hDc, AlarmArea, dwRuleID);
        }else
        {
			//             m_bNeedRedraw[dwRuleID] = TRUE;
			//             m_bCloseIn[dwRuleID] = FALSE;
        }
    }
    
    SelectObject(hDc, pOldPen);
    DeleteObject(DrawPen);
}

void CDlgIPCSimpIntellCfg::SetAudioDecibel( const int &i )
{
	CString str;
	str.Format("%d", i);
	GetDlgItem(IDC_STATIC_AUDIODECIBEL)->SetWindowText(str);
}

CDlgIPCSimpIntellCfg::~CDlgIPCSimpIntellCfg()
{
	if (m_bRecordChan != NULL)
	{
		delete[] m_bRecordChan;
		m_bRecordChan = NULL;
	}

	if (m_pStruAlarmHandleType != NULL)
	{
		delete m_pStruAlarmHandleType;
		m_pStruAlarmHandleType = NULL;
	}
	if(m_pbAlarmOut != NULL)
	{
		delete[] m_pbAlarmOut;
		m_pbAlarmOut = NULL;
	}
}

void CDlgIPCSimpIntellCfg::OnBtnClearpic() 
{
	// TODO: Add your control notification handler code here
	if (m_Combo_CfgType.GetCurSel() == 0)
	{
		memset(&(m_struLineDetection.struAlertParam[m_iLineNo]), 0, sizeof(NET_VCA_TRAVERSE_PLANE));
	}
	else if (m_Combo_CfgType.GetCurSel() == 1)
	{
		memset(&(m_struFieldDetection.struIntrusion[m_iFieldNo]), 0, sizeof(NET_VCA_INTRUSION));
	}
    else if (m_Combo_CfgType.GetCurSel() == 5)
    {
        memset(&m_struRegionEntrDetection.struRegion[m_cmbRegionEntrNo.GetCurSel()].struRegion, 0, sizeof(NET_VCA_POLYGON));
    }
    else if (m_Combo_CfgType.GetCurSel() == 6)
    {
        memset(&m_struRegionExitDetection.struRegion[m_cmbRegionExitNo.GetCurSel()].struRegion, 0, sizeof(NET_VCA_POLYGON));
    }
    else if (m_Combo_CfgType.GetCurSel() == 7)
    {
        memset(&m_struLoiterDetection.struRegion[m_cmbLoiterNo.GetCurSel()].struRegion, 0, sizeof(NET_VCA_POLYGON));
    }
    else if (m_Combo_CfgType.GetCurSel() == 8)
    {
        memset(&m_struGroupDetection.struRegion[m_cmbGroupDetectionNo.GetCurSel()].struRegion, 0, sizeof(NET_VCA_POLYGON));
    }
    else if (m_Combo_CfgType.GetCurSel() == 9)
    {
        memset(&m_struRapidMove.struRegion[m_cmbRapidMove.GetCurSel()].struRegion, 0, sizeof(NET_VCA_POLYGON));
    }
    else if (m_Combo_CfgType.GetCurSel() == 10)
    {
        memset(&m_struParkDetection.struRegion[m_cmbParkNo.GetCurSel()].struRegion, 0, sizeof(NET_VCA_POLYGON));
    }
    else if (m_Combo_CfgType.GetCurSel() == 11)
    {
        memset(&m_struUnattended.struRegion[m_cmbUnattendedNo.GetCurSel()].struRegion, 0, sizeof(NET_VCA_POLYGON));
    }
    else if (m_Combo_CfgType.GetCurSel() == 12)
    {
        memset(&m_struAttended.struRegion[m_cmbAttendedNo.GetCurSel()].struRegion, 0, sizeof(NET_VCA_POLYGON));   
    }
    else if (m_Combo_CfgType.GetCurSel() == 13)
    {
        memset(&m_struClipCfg.struRegion[m_cmbClipRegionNo.GetCurSel()], 0, sizeof(NET_VCA_POLYGON));
    }
}

void CDlgIPCSimpIntellCfg::OnChannelChanged()
{
    Play();
    OnCfgTypeChanged();
    return;
}

void CDlgIPCSimpIntellCfg::AddChanInfo()
{
	g_AddChanInfoToComBox(m_cmbChannel, m_iDeviceIndex);

}

void CDlgIPCSimpIntellCfg::AddGroupNoInfo()
{
    m_cmbGroupNo.ResetContent();
    char szLan[128] = {0};
    CString csStr;
    int iIndex = 0;
    int i;
    int iMaxChanNo = 1;
    int iMaxIPAlarmOutNo = 0;  
    if (g_struDeviceInfo[m_iDeviceIndex].iIPChanNum == 0)
    {
        iMaxChanNo = g_struDeviceInfo[m_iDeviceIndex].iStartChan + g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum ;
    }
    else
    {
         iMaxChanNo = g_struDeviceInfo[m_iDeviceIndex].iIPChanNum + g_struDeviceInfo[m_iDeviceIndex].pStruIPParaCfgV40[0].dwStartDChan -1 ;
    }

    if (g_struDeviceInfo[m_iDeviceIndex].pStruIPAlarmOutCfgV40 == NULL)
    {
        iMaxIPAlarmOutNo = g_struDeviceInfo[m_iDeviceIndex].iAlarmOutNum;
    }
    else
    {
        if (g_struDeviceInfo[m_iDeviceIndex].byStartIPAlarmOutNo == 0)
        {
            iMaxIPAlarmOutNo = g_struDeviceInfo[m_iDeviceIndex].pStruIPAlarmOutCfgV40[0].dwCurIPAlarmOutNum +32;
        }
        else
        {
            iMaxIPAlarmOutNo = g_struDeviceInfo[m_iDeviceIndex].pStruIPAlarmOutCfgV40[0].dwCurIPAlarmOutNum +g_struDeviceInfo[m_iDeviceIndex].byStartIPAlarmOutNo;
        }
    }

    DWORD dwMaxGroupNo = (iMaxChanNo > iMaxIPAlarmOutNo)?  (iMaxChanNo/64 + 1):(iMaxIPAlarmOutNo/64 + 1);
    for(i=0; i< dwMaxGroupNo; i++)
    {
        csStr.Format("Group%d", i +1);
        m_cmbGroupNo.AddString(csStr);
        m_cmbGroupNo.SetItemData(iIndex++, i);
    }
    
   
	m_cmbGroupNo.SetCurSel(0);   
}
void CDlgIPCSimpIntellCfg::OnBtnExit()
{
    if (m_hRegisterDrawThread != NULL)
    {
        TerminateThread(m_hRegisterDrawThread, 0);
        CloseHandle(m_hRegisterDrawThread);
        m_hRegisterDrawThread = NULL;
    }
    CDialog::OnCancel();
}
 
void CDlgIPCSimpIntellCfg::OnBtnRefresh()
{
     OnChannelChanged();
}

void CDlgIPCSimpIntellCfg::OnBtnPtzLockstatusSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	
	m_struPtzLockCfg.dwSize = sizeof(m_struPtzLockCfg);
	m_struPtzLockCfg.byWorkMode = m_comboPtzLockStatus.GetCurSel();
	
	if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_PTZLOCKCFG, m_lChannel,&m_struPtzLockCfg, sizeof(m_struPtzLockCfg)))	
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_PTZLOCKCFG %d",NET_DVR_GetLastError());
	}
	else
	{
		if (m_struPtzLockCfg.byWorkMode == 1)
		{
			OnGetPtzLockInfo();
		} 		
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PTZLOCKCFG Success!");
	}
	return;
}


void CALLBACK fPtzLockInfoCallback(DWORD dwType, void *lpBuffer, DWORD dwBufLen, void *pUserData)
{
	CDlgIPCSimpIntellCfg* pPtzLockInfo = (CDlgIPCSimpIntellCfg*)pUserData;
	if (pPtzLockInfo == NULL)
	{
		return;
	}
    
	CString strItem = "";
	
	switch (dwType)
	{
	case NET_SDK_CALLBACK_TYPE_DATA:
		if (lpBuffer != NULL)
		{
			NET_DVR_PTZLOCKINFO* pCallbackData = (NET_DVR_PTZLOCKINFO*)lpBuffer;
			pPtzLockInfo->SetPtzLockTime(pCallbackData->dwRemainingSec);
		}
		break;
	case NET_SDK_CALLBACK_TYPE_STATUS:
		{
			if (lpBuffer != NULL)
			{
				DWORD dwStatus = *(DWORD*)lpBuffer;
				if (dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
				{	
					strItem = "Fail";
					pPtzLockInfo->GetDlgItem(IDC_STATIC_PTZLOCKTIME)->SetWindowText(strItem);
				}
				else if(dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
				{
					strItem = "Succ";
					pPtzLockInfo->GetDlgItem(IDC_STATIC_PTZLOCKTIME)->SetWindowText(strItem);	
				}
			}
		}
		break;
	}
}

void CDlgIPCSimpIntellCfg::OnGetPtzLockInfo()
{
	char szLan[128] = {0};
	
	if (m_lHandle >= 0)
	{
		if (!NET_DVR_StopRemoteConfig(m_lHandle))
		{
			g_StringLanType(szLan, "云台锁定时间获取失败", "Get PTZ Lock Info Failed");
			AfxMessageBox(szLan);
			return;
		}
	} 
	m_struPtzLockInfoCond.dwSize = sizeof(m_struPtzLockInfoCond);
	m_struPtzLockInfoCond.dwChannel = m_lChannel;
	m_lHandle = NET_DVR_StartRemoteConfig(m_lLoginID, NET_DVR_GET_PTZLOCKINFO, &m_struPtzLockInfoCond, sizeof(m_struPtzLockInfoCond), fPtzLockInfoCallback, this);
	if (m_lHandle >= 0)
	{
		g_pMainDlg->AddLog(m_lLoginID, OPERATION_SUCC_T, "NET_DVR_StartRemoteConfig NET_DVR_GET_PTZLOCKINFO");
		// 		m_bGetNext = TRUE;
		// 		DWORD dwThreadId;
		// 		//m_lstPdcResult.DeleteAllItems();
		// 		m_hGetInfoThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetPtzLockInfoThread), this, 0, &dwThreadId);
	}
	else
	{
		g_pMainDlg->AddLog(m_lLoginID, OPERATION_FAIL_T, "NET_DVR_StartRemoteConfig NET_DVR_GET_PTZLOCKINFO");
		//m_bGetNext = FALSE;
		// 		g_StringLanType(szLan, "云台锁定时间获取失败", "Get PTZ Lock Info Failed");
		// 		AfxMessageBox(szLan);
		// 		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PTZLOCKINFO");	
	}
	return;
}

void CDlgIPCSimpIntellCfg::SetPtzLockTime(const int i)
{
	CString str;
	str.Format("%d", i);
	GetDlgItem(IDC_STATIC_PTZLOCKTIME)->SetWindowText(str);
}

void CDlgIPCSimpIntellCfg::OnBtnRegionEntrRefresh() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int i = m_cmbRegionEntrNo.GetCurSel();
    //m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    NET_DVR_SMART_REGION_COND struCond = {0};
    struCond.dwSize = sizeof(struCond);
    struCond.dwChannel = m_lChannel;
    struCond.dwRegion = i + 1;

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &struCond;
    struCfg.dwCondSize = sizeof(struCond);
    struCfg.lpOutBuffer = &m_struRegionEntrDetection.struRegion[i];
    struCfg.dwOutSize = sizeof(m_struRegionEntrDetection.struRegion[i]);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_REGION_ENTR_REGION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_REGION_ENTR_REGION");
        return ;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_REGION_ENTR_REGION");
    }
    m_byRegionEntrSensitivity = m_struRegionEntrDetection.struRegion[i].bySensitivity;
    m_comboEnterDetTarget.SetCurSel(m_struRegionEntrDetection.struRegion[i].byDetectionTarget);

	UpdateData(FALSE);
}

void CDlgIPCSimpIntellCfg::OnBtnRegionEntrSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    int i = m_cmbRegionEntrNo.GetCurSel();
    //m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    NET_DVR_SMART_REGION_COND struCond = {0};
    struCond.dwSize = sizeof(struCond);
    struCond.dwChannel = m_lChannel;
    struCond.dwRegion = i + 1;
    
    m_struRegionEntrDetection.struRegion[i].bySensitivity = m_byRegionEntrSensitivity;
	m_struRegionEntrDetection.struRegion[i].byDetectionTarget = m_comboEnterDetTarget.GetCurSel();

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &struCond;
    struCfg.dwCondSize = sizeof(struCond);
    struCfg.lpInBuffer = &m_struRegionEntrDetection.struRegion[i];
    struCfg.dwInSize = sizeof(m_struRegionEntrDetection.struRegion[i]);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_REGION_ENTR_REGION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_REGION_ENTR_REGION");
        return;
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_REGION_ENTR_REGION");
    }
}

void CDlgIPCSimpIntellCfg::OnBtnRegionExitRefresh() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int i = m_cmbRegionExitNo.GetCurSel();
   // m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    NET_DVR_SMART_REGION_COND struCond = {0};
    struCond.dwSize = sizeof(struCond);
    struCond.dwChannel = m_lChannel;
    struCond.dwRegion = i + 1;
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &struCond;
    struCfg.dwCondSize = sizeof(struCond);
    struCfg.lpOutBuffer = &m_struRegionExitDetection.struRegion[i];
    struCfg.dwOutSize = sizeof(m_struRegionExitDetection.struRegion[i]);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_REGION_EXITING_REGION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_REGION_EXITING_REGION");
        return ;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_REGION_EXITING_REGION");
    }
    m_nRegionExitSensitivity = m_struRegionExitDetection.struRegion[i].bySensitivity;
	m_comboExitDetTarget.SetCurSel(m_struRegionExitDetection.struRegion[i].byDetectionTarget);

    UpdateData(FALSE);
}

void CDlgIPCSimpIntellCfg::OnBtnRegionExitSave() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int i = m_cmbRegionExitNo.GetCurSel();
   // m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    NET_DVR_SMART_REGION_COND struCond = {0};
    struCond.dwSize = sizeof(struCond);
    struCond.dwChannel = m_lChannel;
    struCond.dwRegion = i + 1;
    
    m_struRegionExitDetection.struRegion[i].bySensitivity = m_nRegionExitSensitivity;
	m_struRegionExitDetection.struRegion[i].byDetectionTarget = m_comboExitDetTarget.GetCurSel();

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &struCond;
    struCfg.dwCondSize = sizeof(struCond);
    struCfg.lpInBuffer = &m_struRegionExitDetection.struRegion[i];
    struCfg.dwInSize = sizeof(m_struRegionExitDetection.struRegion[i]);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_REGION_EXITING_REGION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_REGION_EXITING_REGION");
        return;
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_REGION_EXITING_REGION");
    }
}

void CDlgIPCSimpIntellCfg::OnBtnLoiterRefresh() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int i = m_cmbLoiterNo.GetCurSel();
 //   m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    NET_DVR_SMART_REGION_COND struCond = {0};
    struCond.dwSize = sizeof(struCond);
    struCond.dwChannel = m_lChannel;
    struCond.dwRegion = i + 1;
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &struCond;
    struCfg.dwCondSize = sizeof(struCond);
    struCfg.lpOutBuffer = &m_struLoiterDetection.struRegion[i];
    struCfg.dwOutSize = sizeof(m_struLoiterDetection.struRegion[i]);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_LOITERING_REGION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_LOITERING_REGION");
        return ;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_LOITERING_REGION");
    }
    m_nLoiterSensitivity = m_struLoiterDetection.struRegion[i].bySensitivity;
    m_nLoiterTimeThreshold = m_struLoiterDetection.struRegion[i].byTimeThreshold;
    UpdateData(FALSE);
}

void CDlgIPCSimpIntellCfg::OnBtnLoiterSave() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int i = m_cmbLoiterNo.GetCurSel();
 //   m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    NET_DVR_SMART_REGION_COND struCond = {0};
    struCond.dwSize = sizeof(struCond);
    struCond.dwChannel = m_lChannel;
    struCond.dwRegion = i + 1;
    
    m_struLoiterDetection.struRegion[i].bySensitivity = m_nLoiterSensitivity;
    m_struLoiterDetection.struRegion[i].byTimeThreshold = m_nLoiterTimeThreshold;
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &struCond;
    struCfg.dwCondSize = sizeof(struCond);
    struCfg.lpInBuffer = &m_struLoiterDetection.struRegion[i];
    struCfg.dwInSize = sizeof(m_struLoiterDetection.struRegion[i]);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_LOITERING_REGION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_LOITERING_REGION");
        return;
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_LOITERING_REGION");
    }
}

void CDlgIPCSimpIntellCfg::OnBtnGroupRefresh() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int i = m_cmbGroupDetectionNo.GetCurSel();
  //  m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    NET_DVR_SMART_REGION_COND struCond = {0};
    struCond.dwSize = sizeof(struCond);
    struCond.dwChannel = m_lChannel;
    struCond.dwRegion = i + 1;
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &struCond;
    struCfg.dwCondSize = sizeof(struCond);
    struCfg.lpOutBuffer = &m_struGroupDetection.struRegion[i];
    struCfg.dwOutSize = sizeof(m_struGroupDetection.struRegion[i]);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_GROUPDETECTION_REGION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_GROUPDETECTION_REGION");
        return ;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_GROUPDETECTION_REGION");
    }
    m_nGroupObjectOccup = m_struGroupDetection.struRegion[i].byObjectOccup;
    m_iSensitivityLevel = m_struGroupDetection.struRegion[i].bySensitivityLevel;
    m_iDurationTime = m_struGroupDetection.struRegion[i].byDurationTime;
    m_iFilterTime = m_struGroupDetection.struRegion[i].byFilterTime;
    m_iMinTriggerTime = m_struGroupDetection.struRegion[i].byMinTriggerNumber;
    m_iLinkageTime = m_struGroupDetection.struRegion[i].byLinkageTime;
    
    UpdateData(FALSE);
}

void CDlgIPCSimpIntellCfg::OnBtnGroupSave() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int i = m_cmbGroupDetectionNo.GetCurSel();
  //  m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    NET_DVR_SMART_REGION_COND struCond = {0};
    struCond.dwSize = sizeof(struCond);
    struCond.dwChannel = m_lChannel;
    struCond.dwRegion = i + 1;
    
    m_struGroupDetection.struRegion[i].byObjectOccup = m_nGroupObjectOccup;
    m_struGroupDetection.struRegion[i].bySensitivityLevel = m_iSensitivityLevel;
    m_struGroupDetection.struRegion[i].byDurationTime = m_iDurationTime;
    m_struGroupDetection.struRegion[i].byFilterTime = m_iFilterTime;
    m_struGroupDetection.struRegion[i].byMinTriggerNumber = m_iMinTriggerTime;
    m_struGroupDetection.struRegion[i].byLinkageTime = m_iLinkageTime;

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &struCond;
    struCfg.dwCondSize = sizeof(struCond);
    struCfg.lpInBuffer = &m_struGroupDetection.struRegion[i];
    struCfg.dwInSize = sizeof(m_struGroupDetection.struRegion[i]);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_GROUPDETECTION_REGION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_GROUPDETECTION_REGION");
        return;
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_GROUPDETECTION_REGION");
    }
}

void CDlgIPCSimpIntellCfg::OnBtnRapidMoveRefresh() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int i = m_cmbRapidMove.GetCurSel();
 //   m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    NET_DVR_SMART_REGION_COND struCond = {0};
    struCond.dwSize = sizeof(struCond);
    struCond.dwChannel = m_lChannel;
    struCond.dwRegion = i + 1;
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &struCond;
    struCfg.dwCondSize = sizeof(struCond);
    struCfg.lpOutBuffer = &m_struRapidMove.struRegion[i];
    struCfg.dwOutSize = sizeof(m_struRapidMove.struRegion[i]);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_RAPIDMOVE_REGION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_RAPIDMOVE_REGION");
        return ;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_RAPIDMOVE_REGION");
    }
    m_nRapidMoveSensitivity = m_struRapidMove.struRegion[i].bySensitivity;
	m_comRunDetTarget.SetCurSel(m_struRapidMove.struRegion[i].byDetectionTarget);

    UpdateData(FALSE);
}

void CDlgIPCSimpIntellCfg::OnBtnRapidMoveSave() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int i = m_cmbRapidMove.GetCurSel();
  //  m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    NET_DVR_SMART_REGION_COND struCond = {0};
    struCond.dwSize = sizeof(struCond);
    struCond.dwChannel = m_lChannel;
    struCond.dwRegion = i + 1;
    
    m_struRapidMove.struRegion[i].bySensitivity = m_nRapidMoveSensitivity;
	m_struRapidMove.struRegion[i].byDetectionTarget = m_comRunDetTarget.GetCurSel();

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &struCond;
    struCfg.dwCondSize = sizeof(struCond);
    struCfg.lpInBuffer = &m_struRapidMove.struRegion[i];
    struCfg.dwInSize = sizeof(m_struRapidMove.struRegion[i]);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_RAPIDMOVE_REGION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_RAPIDMOVE_REGION");
        return;
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_RAPIDMOVE_REGION");
    }
}

void CDlgIPCSimpIntellCfg::OnBtnParkRefresh() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int i = m_cmbParkNo.GetCurSel();
  //  m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    NET_DVR_SMART_REGION_COND struCond = {0};
    struCond.dwSize = sizeof(struCond);
    struCond.dwChannel = m_lChannel;
    struCond.dwRegion = i + 1;
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &struCond;
    struCfg.dwCondSize = sizeof(struCond);
    struCfg.lpOutBuffer = &m_struParkDetection.struRegion[i];
    struCfg.dwOutSize = sizeof(m_struParkDetection.struRegion[i]);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_PARKING_REGION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PARKING_REGION");
        return ;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_PARKING_REGION");
    }
    m_nParkSensitivity = m_struParkDetection.struRegion[i].bySensitivity;
    m_nParkTimeThreshold = m_struParkDetection.struRegion[i].byTimeThreshold;
    UpdateData(FALSE);
}

void CDlgIPCSimpIntellCfg::OnBtnParkSave() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int i = m_cmbParkNo.GetCurSel();
  //  m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    NET_DVR_SMART_REGION_COND struCond = {0};
    struCond.dwSize = sizeof(struCond);
    struCond.dwChannel = m_lChannel;
    struCond.dwRegion = i + 1;
    
    m_struParkDetection.struRegion[i].bySensitivity = m_nParkSensitivity;
    m_struParkDetection.struRegion[i].byTimeThreshold = m_nParkTimeThreshold;
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &struCond;
    struCfg.dwCondSize = sizeof(struCond);
    struCfg.lpInBuffer = &m_struParkDetection.struRegion[i];
    struCfg.dwInSize = sizeof(m_struParkDetection.struRegion[i]);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_PARKING_REGION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_PARKING_REGION");
        return;
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PARKING_REGION");
    }
}

void CDlgIPCSimpIntellCfg::OnBtnUnattendedRefresh() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int i = m_cmbUnattendedNo.GetCurSel();
  //  m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    NET_DVR_SMART_REGION_COND struCond = {0};
    struCond.dwSize = sizeof(struCond);
    struCond.dwChannel = m_lChannel;
    struCond.dwRegion = i + 1;
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &struCond;
    struCfg.dwCondSize = sizeof(struCond);
    struCfg.lpOutBuffer = &m_struUnattended.struRegion[i];
    struCfg.dwOutSize = sizeof(m_struUnattended.struRegion[i]);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_UNATTENDED_BAGGAGE_REGION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_UNATTENDED_BAGGAGE_REGION");
        return ;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_UNATTENDED_BAGGAGE_REGION");
    }
    m_nUnattendedSensitivity = m_struUnattended.struRegion[i].bySensitivity;
    m_nUnattendedTimeThreshold = m_struUnattended.struRegion[i].wTimeThreshold;
    UpdateData(FALSE);
}

void CDlgIPCSimpIntellCfg::OnBtnUnattendedSave() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int i = m_cmbUnattendedNo.GetCurSel();
   // m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    NET_DVR_SMART_REGION_COND struCond = {0};
    struCond.dwSize = sizeof(struCond);
    struCond.dwChannel = m_lChannel;
    struCond.dwRegion = i + 1;
    
    m_struUnattended.struRegion[i].bySensitivity = m_nUnattendedSensitivity;

    if (m_bChkUnattendedBaggageTime)
    {
        m_struUnattended.struRegion[i].wTimeThreshold = m_nUnattendedTimeThreshold;
        m_struUnattended.struRegion[i].byTimeThresholdMode = 1;
    } 
    else
    {
        m_struUnattended.struRegion[i].byTimeThreshold = m_nUnattendedTimeThreshold;
    }

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &struCond;
    struCfg.dwCondSize = sizeof(struCond);
    struCfg.lpInBuffer = &m_struUnattended.struRegion[i];
    struCfg.dwInSize = sizeof(m_struUnattended.struRegion[i]);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_UNATTENDED_BAGGAGE_REGION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_UNATTENDED_BAGGAGE_REGION");
        return;
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_UNATTENDED_BAGGAGE_REGION");
    }
}

void CDlgIPCSimpIntellCfg::OnBtnAttendedRefresh() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int i = m_cmbAttendedNo.GetCurSel();
  //  m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    NET_DVR_SMART_REGION_COND struCond = {0};
    struCond.dwSize = sizeof(struCond);
    struCond.dwChannel = m_lChannel;
    struCond.dwRegion = i + 1;
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &struCond;
    struCfg.dwCondSize = sizeof(struCond);
    struCfg.lpOutBuffer = &m_struAttended.struRegion[i];
    struCfg.dwOutSize = sizeof(m_struAttended.struRegion[i]);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_ATTENDEDBAGGAGE_REGION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ATTENDEDBAGGAGE_REGION");
        return ;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ATTENDEDBAGGAGE_REGION");
    }
    m_nAttendedSensitivity = m_struAttended.struRegion[i].bySensitivity;
    m_nAttendedTimeThresgold = m_struAttended.struRegion[i].wTimeThreshold;
    UpdateData(FALSE);
}

void CDlgIPCSimpIntellCfg::OnBtnAttendedSave() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int i = m_cmbAttendedNo.GetCurSel();
   // m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    NET_DVR_SMART_REGION_COND struCond = {0};
    struCond.dwSize = sizeof(struCond);
    struCond.dwChannel = m_lChannel;
    struCond.dwRegion = i + 1;
    
    m_struAttended.struRegion[i].bySensitivity = m_nAttendedSensitivity;

    if (m_bChkUnattendedBaggageTime)
    {
        m_struAttended.struRegion[i].wTimeThreshold = m_nAttendedTimeThresgold;
        m_struAttended.struRegion[i].byTimeThresholdMode = 1;
    } 
    else
    {
        m_struAttended.struRegion[i].byTimeThreshold = m_nAttendedTimeThresgold;
    }

    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &struCond;
    struCfg.dwCondSize = sizeof(struCond);
    struCfg.lpInBuffer = &m_struAttended.struRegion[i];
    struCfg.dwInSize = sizeof(m_struAttended.struRegion[i]);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_ATTENDEDBAGGAGE_REGION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_ATTENDEDBAGGAGE_REGION");
        return;
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_ATTENDEDBAGGAGE_REGION");
    }
}

void CDlgIPCSimpIntellCfg::OnSelchangeCmbAttendedNo() 
{
	// TODO: Add your control notification handler code here
    m_dwPosNum = 0;
    int i = m_cmbAttendedNo.GetCurSel();
    m_nAttendedSensitivity = m_struAttended.struRegion[i].bySensitivity;
    m_nAttendedTimeThresgold = m_struAttended.struRegion[i].wTimeThreshold;
    UpdateData(FALSE);
}

void CDlgIPCSimpIntellCfg::OnSelchangeCmbGroupNo() 
{
	// TODO: Add your control notification handler code here
    m_dwPosNum = 0;
    int i = m_cmbGroupDetectionNo.GetCurSel();
    m_nGroupObjectOccup = m_struGroupDetection.struRegion[i].byObjectOccup;
    m_iSensitivityLevel = m_struGroupDetection.struRegion[i].bySensitivityLevel;
    m_iDurationTime = m_struGroupDetection.struRegion[i].byDurationTime;
    m_iFilterTime = m_struGroupDetection.struRegion[i].byFilterTime;
    m_iMinTriggerTime = m_struGroupDetection.struRegion[i].byMinTriggerNumber;
    m_iLinkageTime = m_struGroupDetection.struRegion[i].byLinkageTime;
    UpdateData(FALSE);
}

void CDlgIPCSimpIntellCfg::OnSelchangeCmbLoiterNo() 
{
	// TODO: Add your control notification handler code here
    m_dwPosNum = 0;
    int i = m_cmbLoiterNo.GetCurSel();
    m_nLoiterSensitivity = m_struLoiterDetection.struRegion[i].bySensitivity;
    m_nLoiterTimeThreshold = m_struLoiterDetection.struRegion[i].byTimeThreshold;
    UpdateData(FALSE);
}

void CDlgIPCSimpIntellCfg::OnSelchangeCmbParkNo() 
{
	// TODO: Add your control notification handler code here
    m_dwPosNum = 0;
    int i = m_cmbParkNo.GetCurSel();
    m_nParkSensitivity = m_struParkDetection.struRegion[i].bySensitivity;
    m_nParkTimeThreshold = m_struParkDetection.struRegion[i].byTimeThreshold;
    UpdateData(FALSE);
}

void CDlgIPCSimpIntellCfg::OnSelchangeCmbRapidMove() 
{
	// TODO: Add your control notification handler code here
    m_dwPosNum = 0;
    int i = m_cmbRapidMove.GetCurSel();
	m_nRapidMoveSensitivity = m_struRapidMove.struRegion[i].bySensitivity;
	m_comRunDetTarget.SetCurSel(m_struRapidMove.struRegion[i].byDetectionTarget);
 
    UpdateData(FALSE);
}

void CDlgIPCSimpIntellCfg::OnSelchangeCmbRegionEntrNo() 
{
	// TODO: Add your control notification handler code here
    m_dwPosNum = 0;
    int i = m_cmbRegionEntrNo.GetCurSel();
    m_byRegionEntrSensitivity = m_struRegionEntrDetection.struRegion[i].bySensitivity;
    UpdateData(FALSE);
}

void CDlgIPCSimpIntellCfg::OnSelchangeCmbRegionExitNo() 
{
	// TODO: Add your control notification handler code here
    m_dwPosNum = 0;
	int i = m_cmbRegionExitNo.GetCurSel();
    m_nRegionExitSensitivity = m_struRegionExitDetection.struRegion[i].bySensitivity;
   	m_comboExitDetTarget.SetCurSel(m_struRegionExitDetection.struRegion[i].byDetectionTarget);

	UpdateData(FALSE);
}

void CDlgIPCSimpIntellCfg::OnSelchangeCmbUnattendedNo() 
{
	// TODO: Add your control notification handler code here
    m_dwPosNum = 0;
    int i = m_cmbUnattendedNo.GetCurSel();
    m_nUnattendedSensitivity = m_struUnattended.struRegion[i].bySensitivity;
    m_nUnattendedTimeThreshold = m_struUnattended.struRegion[i].wTimeThreshold;
    UpdateData(FALSE);
}

BOOL CDlgIPCSimpIntellCfg::GetEventTrigger(DWORD dwCommand)
{
   // m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    UpdateData(TRUE);
    NET_DVR_STD_CONFIG struCfg = { 0 };

    NET_DVR_THERMOMETRY_TRIGGER_COND struThermometry = { 0 };
    NET_DVR_TEMPERATURE_TRIGGER_COND struTemperature = { 0 };
    NET_DVR_ALARMIN_TRIGGER_COND strAlarmIn = { 0 };
    NET_DVR_FACELIB_GUARD_COND strFaceLibGuard = { 0 };
    if (dwCommand == NET_DVR_GET_THERMOMETRY_TRIGGER)
    {
        struThermometry.dwSize = sizeof(struThermometry);
        struThermometry.dwChan = m_lChannel;
        struThermometry.dwPreset = m_dwPreset;
        struCfg.lpCondBuffer = &struThermometry;
        struCfg.dwCondSize = sizeof(struThermometry);
    }
    else if (dwCommand == NET_DVR_GET_TEMPERATURE_TRIGGER)
    {

        struTemperature.dwSize = sizeof(struThermometry);
        struTemperature.dwChan = m_lChannel;
        struTemperature.dwPreset = m_dwPreset;
        struCfg.lpCondBuffer = &struTemperature;
        struCfg.dwCondSize = sizeof(struTemperature);
    }
    else if (dwCommand == NET_DVR_GET_ALARMIN_TRIGGER || dwCommand == NET_DVR_GET_EMERGENCY_CALL_HELP_TRIGGER || dwCommand == NET_DVR_GET_CONSULT_TRIGGER)
    {
        strAlarmIn.dwSize = sizeof(strAlarmIn);
        strAlarmIn.dwChannel = m_lChannel;
        strAlarmIn.dwAlarmInNo = m_iZoneIndex;
        struCfg.lpCondBuffer = &strAlarmIn;
        struCfg.dwCondSize = sizeof(strAlarmIn);
    }
    else if (dwCommand == NET_DVR_GET_FACELIB_TRIGGER)
    {
        strFaceLibGuard.dwSize = sizeof(strFaceLibGuard);
        strFaceLibGuard.dwChannel = m_lChannel;
        strncpy(strFaceLibGuard.szFDID, m_strFaceLibID.GetBuffer(m_strFaceLibID.GetLength()), 68);

        struCfg.lpCondBuffer = &strFaceLibGuard;
        struCfg.dwCondSize = sizeof(strFaceLibGuard);
    }
    else
    {
        struCfg.lpCondBuffer = &m_lChannel;
        struCfg.dwCondSize = sizeof(m_lChannel);
    }

    ;
    struCfg.lpOutBuffer = &m_struEventTrigger;
    struCfg.dwOutSize = sizeof(m_struEventTrigger);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, dwCommand, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        return FALSE;
    }
    else
    {
		m_pStruAlarmHandleType->dwHandleType = m_struEventTrigger.struHandleException.dwHandleType;
		memcpy(m_pStruAlarmHandleType->dwRelAlarmOut, m_struEventTrigger.struHandleException.dwRelAlarmOut,sizeof(DWORD)*MAX_ALARMOUT_V40);
		for (int i =0; i < MAX_CHANNUM_V30*8; i++)
		{
			if (m_struEventTrigger.dwRelRecordChan[i] == 0xffffffff)
			{
				break;
			}
			m_bRecordChan[m_struEventTrigger.dwRelRecordChan[i] - 1] = 1;
		}
        m_combDirection.SetCurSel(m_struEventTrigger.byDirection);
        return TRUE;
    }

	return TRUE;
}
BOOL CDlgIPCSimpIntellCfg::SetEventTrigger(DWORD dwCommand)
{
    UpdateData(TRUE);
	m_struEventTrigger.dwSize = sizeof(m_struEventTrigger);
	m_struEventTrigger.struHandleException.dwHandleType = m_pStruAlarmHandleType->dwHandleType;
    m_struEventTrigger.byDirection = m_combDirection.GetCurSel();

	memcpy(m_struEventTrigger.struHandleException.dwRelAlarmOut,m_pStruAlarmHandleType->dwRelAlarmOut,MAX_ALARMOUT_V40);


    int nCount = 0;
    memset(m_struEventTrigger.dwRelRecordChan, 0, sizeof(DWORD) * MAX_CHANNUM_V40);
    for (int k = 0; k < MAX_CHANNUM_V30*8; k++)
    {
        if(m_bRecordChan[k])
        {
            m_struEventTrigger.dwRelRecordChan[nCount] = k+1;
            nCount++;
        }
	}
    //m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    NET_DVR_THERMOMETRY_TRIGGER_COND struThermometry = { 0 };
    NET_DVR_STD_CONFIG struCfg = { 0 };
    NET_DVR_TEMPERATURE_TRIGGER_COND struTemperature = { 0 };
    NET_DVR_ALARMIN_TRIGGER_COND strAlarmIn = { 0 };
    NET_DVR_FACELIB_GUARD_COND strFaceLibGuard = { 0 };
    if (dwCommand == NET_DVR_SET_THERMOMETRY_TRIGGER)
    {
        struThermometry.dwSize = sizeof(struThermometry);
        struThermometry.dwChan = m_lChannel;
        struThermometry.dwPreset = m_dwPreset;
        struCfg.lpCondBuffer = &struThermometry;
        struCfg.dwCondSize = sizeof(struThermometry);
    }
    else if (dwCommand == NET_DVR_SET_TEMPERATURE_TRIGGER)
    {
        struTemperature.dwSize = sizeof(struThermometry);
        struTemperature.dwChan = m_lChannel;
        struTemperature.dwPreset = m_dwPreset;
        struCfg.lpCondBuffer = &struTemperature;
        struCfg.dwCondSize = sizeof(struTemperature);
    }
    else if (dwCommand == NET_DVR_SET_ALARMIN_TRIGGER || dwCommand == NET_DVR_SET_EMERGENCY_CALL_HELP_TRIGGER || dwCommand == NET_DVR_SET_CONSULT_TRIGGER)
    {
        strAlarmIn.dwSize = sizeof(strAlarmIn);
        strAlarmIn.dwChannel = m_lChannel;
        strAlarmIn.dwAlarmInNo = m_iZoneIndex;
        struCfg.lpCondBuffer = &strAlarmIn;
        struCfg.dwCondSize = sizeof(strAlarmIn);
    }
    else if (dwCommand == NET_DVR_SET_FACELIB_TRIGGER)
    {
        strFaceLibGuard.dwSize = sizeof(strFaceLibGuard);
        strFaceLibGuard.dwChannel = m_lChannel;
        strncpy(strFaceLibGuard.szFDID, m_strFaceLibID.GetBuffer(m_strFaceLibID.GetLength()), 68);

        struCfg.lpCondBuffer = &strFaceLibGuard;
        struCfg.dwCondSize = sizeof(strFaceLibGuard);
    }
    else
    {
        struCfg.lpCondBuffer = &m_lChannel;
        struCfg.dwCondSize = sizeof(m_lChannel);
    }

//     struCfg.lpCondBuffer = &m_lChannel;
//     struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &m_struEventTrigger;
    struCfg.dwInSize = sizeof(m_struEventTrigger);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_SetSTDConfig(m_lLoginID, dwCommand, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        return FALSE;
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        return TRUE;
    }
}

BOOL CDlgIPCSimpIntellCfg::GetEventSchedule(DWORD dwCommand)
{
  //  m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    NET_DVR_STD_CONFIG struCfg = {0};

    NET_DVR_FACELIB_GUARD_COND strFaceLibGuard = { 0 };
    if (dwCommand == NET_DVR_GET_FACELIB_SCHEDULE)
    {
        strFaceLibGuard.dwSize = sizeof(strFaceLibGuard);
        strFaceLibGuard.dwChannel = m_lChannel;
        strncpy(strFaceLibGuard.szFDID, m_strFaceLibID.GetBuffer(m_strFaceLibID.GetLength()), 68);

        struCfg.lpCondBuffer = &strFaceLibGuard;
        struCfg.dwCondSize = sizeof(strFaceLibGuard);
    }
    else
    {
        struCfg.lpCondBuffer = &m_lChannel;
        struCfg.dwCondSize = sizeof(m_lChannel);
    }

    struCfg.lpOutBuffer = &m_struEventSchedule;
    struCfg.dwOutSize = sizeof(m_struEventSchedule);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, dwCommand, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        return FALSE;
    }
    else
    {
        memcpy(m_struAlarmTime, m_struEventSchedule.struAlarmTime, sizeof(m_struAlarmTime));
        memcpy(m_bySceneID, m_struEventSchedule.bySceneID, sizeof(m_bySceneID));
        memcpy(m_struHolidayHandle.struAlarmTime, m_struEventSchedule.struHolidayAlarmTime, sizeof(m_struEventSchedule.struHolidayAlarmTime));
        m_comboWeekday.SetCurSel(0);
        m_comboCopyTime.SetCurSel(0);
	    OnCbnSelchangeComboAlarminWeekday();
        return TRUE;
    }
}
BOOL CDlgIPCSimpIntellCfg::SetEventSchedule(DWORD dwCommand)
{
    m_struEventSchedule.dwSize = sizeof(m_struEventSchedule);
    memcpy(m_struEventSchedule.struAlarmTime, m_struAlarmTime, sizeof(m_struAlarmTime));
    memcpy(m_struEventSchedule.bySceneID, m_bySceneID, sizeof(m_bySceneID));
    memcpy(m_struEventSchedule.struHolidayAlarmTime, m_struHolidayHandle.struAlarmTime, sizeof(m_struEventSchedule.struHolidayAlarmTime));

   // m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    NET_DVR_STD_CONFIG struCfg = {0};

    NET_DVR_FACELIB_GUARD_COND strFaceLibGuard = { 0 };
    if (dwCommand == NET_DVR_SET_FACELIB_SCHEDULE)
    {
        strFaceLibGuard.dwSize = sizeof(strFaceLibGuard);
        strFaceLibGuard.dwChannel = m_lChannel;
        strncpy(strFaceLibGuard.szFDID, m_strFaceLibID.GetBuffer(m_strFaceLibID.GetLength()), 68);

        struCfg.lpCondBuffer = &strFaceLibGuard;
        struCfg.dwCondSize = sizeof(strFaceLibGuard);
    }
    else
    {
        struCfg.lpCondBuffer = &m_lChannel;
        struCfg.dwCondSize = sizeof(m_lChannel);
    }

    struCfg.lpInBuffer = &m_struEventSchedule;
    struCfg.dwInSize = sizeof(m_struEventSchedule);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_SetSTDConfig(m_lLoginID, dwCommand, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        return FALSE;
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        return TRUE;
    }
}

BOOL CDlgIPCSimpIntellCfg::SetSMDHolidayCfg()
{
	UpdateData(TRUE);
	DWORD dwRetList = NET_DVR_NOERROR;
	BOOL bRet = FALSE;
	char szLan[128] = {0};
	memset(&m_struHolidayCond,0, sizeof(m_struHolidayCond));
	m_struHolidayCond.dwSize = sizeof(m_struHolidayCond);
    m_struHolidayCond.dwChannel = m_lChannel;
	if (m_Combo_CfgType.GetCurSel() == 2)  //虚焦侦测
	{
		m_struHolidayCond.dwSMDHandleType = 1;
	}
	else if(m_Combo_CfgType.GetCurSel() == 3)//声音异常
	{
		m_struHolidayCond.dwSMDHandleType = 0;
	}
	else if(m_Combo_CfgType.GetCurSel() == 4)//场景变更侦测
	{
		m_struHolidayCond.dwSMDHandleType = 2;
	}
	else
	{
		return TRUE;
	}

	bRet = NET_DVR_SetDeviceConfig(m_lLoginID, NET_DVR_SET_SMD_HOLIDAY_HANDLE,1,&m_struHolidayCond,sizeof(m_struHolidayCond),&dwRetList,&m_struHolidayHandle,sizeof(m_struHolidayHandle));

	if (bRet)
	{
		if (NET_DVR_NOERROR == dwRetList)
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_SMD_HOLIDAY_HANDLE");
		}
		else
		{
			sprintf(szLan,"NET_DVR_SET_AUDIOEXCEPTIONPARAM Failed, Error Info[%s],[%d]",NET_DVR_GetErrorMsg(), NET_DVR_GetLastError());
			AfxMessageBox(szLan);
			return FALSE;
		}
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SMD_HOLIDAY_HANDLE");
		return FALSE;
	}

	return TRUE;
}

void CDlgIPCSimpIntellCfg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default    
    
    if (m_lPlayHandle > -1)
    {
        NET_DVR_StopRealPlay(m_lPlayHandle);
    }
    
    if (m_lAudioHandle > -1)
    {
        NET_DVR_StopRemoteConfig(m_lAudioHandle);
    }

    if (m_hRegisterDrawThread != NULL)
    {
        TerminateThread(m_hRegisterDrawThread, 0);
        CloseHandle(m_hRegisterDrawThread);
        m_hRegisterDrawThread = NULL;
    }
	CDialog::OnClose();
}

BOOL CDlgIPCSimpIntellCfg::ConvertHandleExceptionV40ToV41(NET_DVR_HANDLEEXCEPTION_V40 *pStruExpV40, NET_DVR_HANDLEEXCEPTION_V41 *pStruExpV41, BOOL bV40ToV41)
{
	if (pStruExpV41 == NULL || pStruExpV40 == NULL)
	{
		return FALSE;
	}

	if (bV40ToV41)
	{
		memset(pStruExpV41,0,sizeof(NET_DVR_HANDLEEXCEPTION_V41));
		memset(pStruExpV41->dwRelAlarmOut,0xff,sizeof(DWORD)*MAX_ALARMOUT_V40);
		pStruExpV41->dwHandleType = pStruExpV40->dwHandleType;
		for (int i = 0; i< pStruExpV40->dwRelAlarmOutChanNum;i++)
		{
			pStruExpV41->dwRelAlarmOut[i] = pStruExpV40->dwRelAlarmOut[i] -1;
		}
	}
	else
	{
		pStruExpV40->dwHandleType = pStruExpV41->dwHandleType;
		memset(pStruExpV40->dwRelAlarmOut,0xff,sizeof(DWORD)*MAX_CHANNUM_V30);
		pStruExpV40->dwRelAlarmOutChanNum = 0;
		for(int i =0; i< MAX_ALARMOUT_V40;i++)
		{
			if (pStruExpV40->dwRelAlarmOutChanNum < MAX_CHANNUM_V30 && pStruExpV41->dwRelAlarmOut[i] != 0xffffffff)
			{
				pStruExpV40->dwRelAlarmOut[pStruExpV40->dwRelAlarmOutChanNum++] = pStruExpV41->dwRelAlarmOut[i] +1;
			}

		}
	}

	return TRUE;

}
