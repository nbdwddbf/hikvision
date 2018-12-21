// DlgPdcRuleCfgEx.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPdcRuleCfgEx.h"
#include <math.h>
#include "DlgPDCSearch.h"
#include "DlgPdcCalibration.h"
#include "DlgPdcResult.h"
#include "DrawFun.h"
#include "DlgVcaResetCounterCfg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPdcRuleCfgEx dialog
CDlgPdcRuleCfgEx *g_pDlgPdcRuleCfg;
void CALLBACK DrawPDCShowEx(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
    SetBkMode(hDc, TRANSPARENT);
    SetTextColor(hDc, RGB(255, 255, 255));
    
    if (g_pDlgPdcRuleCfg != NULL)
    {
        g_pDlgPdcRuleCfg->F_DrawPdcRule(lRealHandle, hDc, dwUser);
    }
    
}

CDlgPdcRuleCfgEx::CDlgPdcRuleCfgEx(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPdcRuleCfgEx::IDD, pParent)
    , m_ShadowEnable(FALSE)
    , m_AroundEnable(FALSE)
    , m_PushCarEnable(FALSE)
    , m_DayReportEnable(FALSE)
    , m_WeekReportEnable(FALSE)
    , m_MonthReportEnable(FALSE)
    , m_YearReportEnable(FALSE)
    , m_fHeightFilter(0)
    , m_fHeight(0)
    , m_fTiltAngle(0)
    , m_fHeelAngle(0)
    , m_bStreamOverlayRuleInfos(FALSE)
    , m_bRS485TransmissionEnabled(FALSE)
    , m_ctResetDate(COleDateTime::GetCurrentTime())
    , m_ctResetTime(COleDateTime::GetCurrentTime())
    , m_byDetectThreshold(0)
    , m_bLightStream(FALSE)
    , m_bCountPolygon(false)
{
	//{{AFX_DATA_INIT(CDlgPdcRuleCfgEx)
	m_bEnableRule = FALSE;
	m_bUploadCenter = FALSE;
	m_byDetSensitivity = 0;
	m_byGeneratieSpeedSpace = 0;
	m_byGeneratieSpeedTime = 0;
	m_byTargetSizeCorrect = 0;
	m_byCountSpeed = 0;
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
	m_bEnableOSD = 0;
	m_fPointX = 0.0;
	m_fPointY = 0.0;
	m_bChkSECUpload = FALSE;
	m_fWidth = 0.0f;
	m_bChkRemovePDC = FALSE;
	//}}AFX_DATA_INIT
	m_lChannel = -1;
	m_lServerID = -1;
	m_lChanNum = -1;
	m_pStruPdcRuleCfg = NULL;
	m_lPlayHandle = -1;
	memset(&m_struPdcRuleCfg, 0, sizeof(m_struPdcRuleCfg));
	m_struPdcRuleCfg.struAlarmHandleType.dwRelAlarmOutChanNum = 0xffffffff;
	memset(&m_struPdcRuleCfg.struAlarmHandleType.dwRelAlarmOut, 0xffffffff, MAX_CHANNUM_V30);
    m_dwPosNum = 0;
    m_dwLineNum = 0;
}


void CDlgPdcRuleCfgEx::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgPdcRuleCfgEx)
    DDX_Control(pDX, IDC_COMBO_UPLOAD_CYCLE, m_comboUploadCycle);
    DDX_Control(pDX, IDC_COMBOCOPYTIME, m_comboCopyTime);
    DDX_Control(pDX, IDC_COMBOWEEKDAY, m_comboWeekday);
    DDX_Control(pDX, IDC_COMBO_DET_TYPE, m_comboDetType);
    DDX_Check(pDX, IDC_CHK_RULE, m_bEnableRule);
    DDX_Check(pDX, IDC_CHK_UPLOAD_CENTER, m_bUploadCenter);
    DDX_Text(pDX, IDC_EDIT_DET_SENSITIVITY, m_byDetSensitivity);
    DDX_Text(pDX, IDC_EDIT_SPEED_SPACE, m_byGeneratieSpeedSpace);
    DDX_Text(pDX, IDC_EDIT_SPEED_TIME, m_byGeneratieSpeedTime);
    DDX_Text(pDX, IDC_EDIT_TARGETSIZECORRECT, m_byTargetSizeCorrect);
    DDX_Text(pDX, IDC_EDIT_COUNT_SPEED, m_byCountSpeed);
    DDX_Text(pDX, IDC_EDITHOUR11, m_iHour11);
    DDX_Text(pDX, IDC_EDITHOUR12, m_iHour12);
    DDX_Text(pDX, IDC_EDITHOUR21, m_iHour21);
    DDX_Text(pDX, IDC_EDITHOUR22, m_iHour22);
    DDX_Text(pDX, IDC_EDITHOUR31, m_iHour31);
    DDX_Text(pDX, IDC_EDITHOUR32, m_iHour32);
    DDX_Text(pDX, IDC_EDITHOUR41, m_iHour41);
    DDX_Text(pDX, IDC_EDITHOUR42, m_iHour42);
    DDX_Text(pDX, IDC_EDITHOUR51, m_iHour51);
    DDX_Text(pDX, IDC_EDITHOUR52, m_iHour52);
    DDX_Text(pDX, IDC_EDITHOUR61, m_iHour61);
    DDX_Text(pDX, IDC_EDITHOUR62, m_iHour62);
    DDX_Text(pDX, IDC_EDITHOUR71, m_iHour71);
    DDX_Text(pDX, IDC_EDITHOUR72, m_iHour72);
    DDX_Text(pDX, IDC_EDITHOUR81, m_iHour81);
    DDX_Text(pDX, IDC_EDITHOUR82, m_iHour82);
    DDX_Text(pDX, IDC_EDITMIN11, m_iMin11);
    DDX_Text(pDX, IDC_EDITMIN12, m_iMin12);
    DDX_Text(pDX, IDC_EDITMIN21, m_iMin21);
    DDX_Text(pDX, IDC_EDITMIN22, m_iMin22);
    DDX_Text(pDX, IDC_EDITMIN31, m_iMin31);
    DDX_Text(pDX, IDC_EDITMIN32, m_iMin32);
    DDX_Text(pDX, IDC_EDITMIN41, m_iMin41);
    DDX_Text(pDX, IDC_EDITMIN42, m_iMin42);
    DDX_Text(pDX, IDC_EDITMIN51, m_iMin51);
    DDX_Text(pDX, IDC_EDITMIN52, m_iMin52);
    DDX_Text(pDX, IDC_EDITMIN61, m_iMin61);
    DDX_Text(pDX, IDC_EDITMIN62, m_iMin62);
    DDX_Text(pDX, IDC_EDITMIN71, m_iMin71);
    DDX_Text(pDX, IDC_EDITMIN72, m_iMin72);
    DDX_Text(pDX, IDC_EDITMIN81, m_iMin81);
    DDX_Text(pDX, IDC_EDITMIN82, m_iMin82);
    DDX_Check(pDX, IDC_CHECK_OSD_ENABLE, m_bEnableOSD);
    DDX_Text(pDX, IDC_EDIT_POINT_X, m_fPointX);
    DDX_Text(pDX, IDC_EDIT_POINT_Y, m_fPointY);
    DDX_Check(pDX, IDC_CHK_SEC_UPLOAD, m_bChkSECUpload);
    DDX_Text(pDX, IDC_EDIT_PDC_WIDTH, m_fWidth);
    DDX_Check(pDX, IDC_CHK_PDCREMOVE, m_bChkRemovePDC);
    DDX_Control(pDX, IDC_COMBO_SQID, m_dwID);
    DDX_Control(pDX, IDC_COMBO_OSDENEW, m_OSDEnable_New);
    DDX_Check(pDX, IDC_CHECK4, m_ShadowEnable);
    DDX_Check(pDX, IDC_CHECK5, m_AroundEnable);
    DDX_Check(pDX, IDC_CHECK6, m_PushCarEnable);
    DDX_Check(pDX, IDC_CHECK7, m_DayReportEnable);
    DDX_Check(pDX, IDC_CHECK8, m_WeekReportEnable);
    DDX_Check(pDX, IDC_CHECK9, m_MonthReportEnable);
    DDX_Check(pDX, IDC_CHECK10, m_YearReportEnable);
    DDX_Control(pDX, IDC_CMB_HEIGHT_FILTER_OSD_ENABLED, m_cmbHeightFilterEnabled);
    DDX_Control(pDX, IDC_CMB_HGIGHT_FILTER_ENABLED, m_cmbHeightFilter);
    DDX_Text(pDX, IDC_EDIT_HEIGHT, m_fHeightFilter);
    DDX_Control(pDX, IDC_CMB_CALIB_TYPE, m_cmbCalibType);
    DDX_Text(pDX, IDC_EDIT_CALIB_HEIGHT, m_fHeight);
    DDX_Text(pDX, IDC_EDIT_TILTANGLE, m_fTiltAngle);
    DDX_Text(pDX, IDC_EDIT_HEELANGLE, m_fHeelAngle);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_CMB_TYPE, m_cmbType);
    DDX_Control(pDX, IDC_CMB_CALIB_TYPE2, m_cmbArgType);
    DDX_Check(pDX, IDC_CHECK_STREAM_OVERLAY_RULE_INFO, m_bStreamOverlayRuleInfos);
    DDX_Check(pDX, IDC_CHECK_RE485_TRANSMISSION, m_bRS485TransmissionEnabled);
    DDX_Control(pDX, IDC_COMBO_COUNTING_TYPE, m_comboCountingType);
    DDX_Control(pDX, IDC_COMBO_SIGNAL_TYPE, m_comboSignalType);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_RESET_DATE, m_ctResetDate);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_RESET_TIME, m_ctResetTime);
    DDX_Text(pDX, IDC_EDIT_DETECT_THRESHOID, m_byDetectThreshold);
    DDX_Check(pDX, IDC_CHK_LIGHTSTREAM, m_bLightStream);
}


BEGIN_MESSAGE_MAP(CDlgPdcRuleCfgEx, CDialog)
	//{{AFX_MSG_MAP(CDlgPdcRuleCfgEx)
	ON_BN_CLICKED(IDC_BTN_PDC_RULECFG, OnBtnPdcRulecfg)
	ON_BN_CLICKED(IDC_RADIO_DRAW_POLYGON, OnRadioDrawPolygon)
	ON_BN_CLICKED(IDC_RADIO_DRAW_DIRECTION, OnRadioDrawDirection)
    ON_BN_CLICKED(IDC_RADIO_DETECT_LINE, OnRadioDetectLine)
	ON_BN_CLICKED(IDC_TIME_OK2, OnTimeOk2)
	ON_BN_CLICKED(IDC_TIME_COPY2, OnTimeCopy2)
	ON_BN_CLICKED(IDC_BTN_PDC_QUERY, OnBtnPdcQuery)
	ON_BN_CLICKED(IDC_BTN_CALIBRATION, OnBtnCalibration)
	ON_BN_CLICKED(IDC_BTN_GET_PDC_RULECFG, OnBtnGetPdcRulecfg)
	ON_BN_CLICKED(IDC_BTN_PDC_RESULT, OnBtnPdcResult)
    ON_BN_CLICKED(IDC_BTN_GET_PDC_LINT, OnBtnGetPdcLint)
    ON_BN_CLICKED(IDC_BTN_SET_PDC_LINT, OnBtnSetPdcLint)
	ON_BN_CLICKED(IDC_BTN_ADV_RESET_COUNTE, OnBtnAdvResetCounte)
	ON_BN_CLICKED(IDC_BTN_GETPDCRECOMMEND, OnBtnGetpdcrecommend)
	ON_BN_CLICKED(IDC_BTN_REMOVE_FLASHSTORAGE, OnBtnRemoveFlashstorage)
    ON_BN_CLICKED(IDC_BTN_HEIGHT_SET, &CDlgPdcRuleCfgEx::OnBnClickedBtnHeightSet)
    ON_BN_CLICKED(IDC_BTN_CALIB, &CDlgPdcRuleCfgEx::OnBnClickedBtnCalib)
    ON_BN_CLICKED(IDC_RADIO_CALIB, &CDlgPdcRuleCfgEx::OnBnClickedRadioCalib)
    ON_CBN_SELCHANGE(IDC_CMB_CALIB_TYPE, &CDlgPdcRuleCfgEx::OnCbnSelchangeCmbCalibType)
    ON_BN_CLICKED(IDC_BTN_HEIGHT_GET, &CDlgPdcRuleCfgEx::OnBnClickedBtnHeightGet)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_CALIB_GET, &CDlgPdcRuleCfgEx::OnBnClickedBtnCalibGet)
    ON_BN_CLICKED(IDC_RADIO_POLY_LINE, &CDlgPdcRuleCfgEx::OnBnClickedRadioPolyLine)
    ON_BN_CLICKED(IDC_COUNT_POLYGON, &CDlgPdcRuleCfgEx::OnBnClickedCountPolygon)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPdcRuleCfgEx message handlers



BOOL CDlgPdcRuleCfgEx::PreTranslateMessage(MSG* pMsg) 
{
    // TODO: Add your specialized code here and/or call the base class
   
    CPoint pt(0,0);
    CRect  rcWnd(0,0,0,0);
    GetDlgItem(IDC_PLAYWND)->GetWindowRect(&rcWnd);
    GetCursorPos(&pt);
    CString strTemp = _T("");
    DWORD i=0;
    BOOL bOneLine = TRUE,bXOneLine = TRUE,bYOneLine = TRUE;
    
    switch(pMsg->message) 
    {
    case WM_LBUTTONDOWN:
        if ((m_iDrawType == 1 || m_iDrawType == 2 || m_iDrawType == 3 || m_iDrawType == 4 || m_iDrawType == 5 || m_iDrawType == 6) && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))//按CTRL键 画图
        {
            if (m_iDrawType == 1)// Draw polygon
            {
                if(PtInRect(&rcWnd,pt))
                {	
                        if(m_bCloseIn)
                        {
                            m_dwPosNum = 0;
                            m_struPdcRuleCfg.struPolygon.dwPointNum = m_dwPosNum;		
                        }
                        if(m_dwPosNum>9)
                        {
                            char szLan[128] = {0};
                            g_StringLanType(szLan,"人数统计规则为4边形","Polygon vertex can not be over 4!");
                            AfxMessageBox(szLan);
                            return TRUE;
                        }
                        if((float)(pt.x-rcWnd.left)/(float)rcWnd.Width() <= m_struPdcRuleCfg.struPolygon.struPos[m_dwPosNum-1].fX+0.01 && (float)(pt.x-rcWnd.left)/(float)rcWnd.Width() >= m_struPdcRuleCfg.struPolygon.struPos[m_dwPosNum-1].fX-0.01\
                            && (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() <= m_struPdcRuleCfg.struPolygon.struPos[m_dwPosNum-1].fY+0.01 && (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() >= m_struPdcRuleCfg.struPolygon.struPos[m_dwPosNum-1].fY-0.01)
                        {
                            char szLan[128] = {0};
                            g_StringLanType(szLan, "不能连续在同一点上画区域", "Region can not be painted in the same point");
                            AfxMessageBox(szLan);
                            return TRUE;
                        }
                        m_bCloseIn = FALSE;
                        m_bMouseMove = FALSE;
                        m_struPdcRuleCfg.struPolygon.struPos[m_dwPosNum].fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struPdcRuleCfg.struPolygon.struPos[m_dwPosNum].fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
                        m_dwPosNum++;
                        m_struPdcRuleCfg.struPolygon.dwPointNum = m_dwPosNum;			
                }
                
            }
            else if (m_iDrawType == 2)
            {
                if(PtInRect(&rcWnd,pt))
                {		
                    if(!m_bMouseMove)
                    {
                        m_struPdcRuleCfg.struEnterDirection.struStartPoint.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struPdcRuleCfg.struEnterDirection.struStartPoint.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();		
                        m_struPdcRuleCfg.struEnterDirection.struEndPoint.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struPdcRuleCfg.struEnterDirection.struEndPoint.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();			
                        m_bMouseMove = TRUE;
                    }
                    else
                    {
                        if ((float)(pt.x-rcWnd.left)/(float)rcWnd.Width() <= m_struPdcRuleCfg.struEnterDirection.struStartPoint.fX+0.01 && (float)(pt.x-rcWnd.left)/(float)rcWnd.Width() >= m_struPdcRuleCfg.struEnterDirection.struStartPoint.fX-0.01\
                            && (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() <= m_struPdcRuleCfg.struEnterDirection.struStartPoint.fY+0.01 && (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() >= m_struPdcRuleCfg.struEnterDirection.struStartPoint.fY-0.01)
                        {
                            char szLan[128] = {0};
                            g_StringLanType(szLan, "不能连续在同一点上画区域", "Region can not be painted in the same point");
                            AfxMessageBox(szLan);
                            return TRUE;
                        }
                        m_struPdcRuleCfg.struEnterDirection.struEndPoint.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struPdcRuleCfg.struEnterDirection.struEndPoint.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();			
                        m_bMouseMove = FALSE;
                    }
                }
            }
            else if (m_iDrawType == 3)
            {
                if(PtInRect(&rcWnd,pt))
                {		
                    if(!m_bMouseMove)
                    {
                        m_struPdcRuleCfg.struLine.struStart.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struPdcRuleCfg.struLine.struStart.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();		
                        m_struPdcRuleCfg.struLine.struEnd.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struPdcRuleCfg.struLine.struEnd.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();			
                        m_bMouseMove = TRUE;
                    }
                    else
                    {
                        if ((float)(pt.x-rcWnd.left)/(float)rcWnd.Width() <= m_struPdcRuleCfg.struLine.struStart.fX+0.01 && (float)(pt.x-rcWnd.left)/(float)rcWnd.Width() >= m_struPdcRuleCfg.struLine.struStart.fX-0.01\
                            && (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() <= m_struPdcRuleCfg.struLine.struStart.fY+0.01 && (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() >= m_struPdcRuleCfg.struLine.struStart.fY-0.01)
                        {
                            char szLan[128] = {0};
                            g_StringLanType(szLan, "不能连续在同一点上画区域", "Region can not be painted in the same point");
                            AfxMessageBox(szLan);
                            return TRUE;
                        }
                        m_struPdcRuleCfg.struLine.struEnd.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struPdcRuleCfg.struLine.struEnd.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();			
                        m_bMouseMove = FALSE;
                    }
                }
            }
            else if (m_iDrawType == 4)
            {

                if (PtInRect(&rcWnd, pt))
                {
                    memset(&m_struPdcRuleCfg.struAutoCalibPolygon, 0, sizeof(m_struPdcRuleCfg.struAutoCalibPolygon));
                    if (!m_bMouseMove)
                    {
                        m_struPdcRuleCfg.struAutoCalibPolygon.struPos[0].fX = (float)(pt.x - rcWnd.left) / (float)rcWnd.Width();
                        m_struPdcRuleCfg.struAutoCalibPolygon.struPos[0].fY = (float)(pt.y - rcWnd.top) / (float)rcWnd.Height();
                        m_struPdcRuleCfg.struAutoCalibPolygon.dwPointNum = 1;
                        m_bMouseMove = TRUE;
                    }
                }
            }
            else if (m_iDrawType == 5)// Draw poly line
            {
                if (PtInRect(&rcWnd, pt))
                {
                    if (m_dwLineNum > 3)
                    {
                        return TRUE;
                    }
                    if ((float)(pt.x - rcWnd.left) / (float)rcWnd.Width() <= m_struPdcRuleCfg.struPolygon.struPos[m_dwLineNum - 1].fX + 0.01 && (float)(pt.x - rcWnd.left) / (float)rcWnd.Width() >= m_struPdcRuleCfg.struPolygon.struPos[m_dwLineNum - 1].fX - 0.01\
                        && (float)(pt.y - rcWnd.top) / (float)rcWnd.Height() <= m_struPdcRuleCfg.struPolygon.struPos[m_dwLineNum - 1].fY + 0.01 && (float)(pt.y - rcWnd.top) / (float)rcWnd.Height() >= m_struPdcRuleCfg.struPolygon.struPos[m_dwLineNum - 1].fY - 0.01)
                    {
                        char szLan[128] = { 0 };
                        g_StringLanType(szLan, "不能连续在同一点上画区域", "Region can not be painted in the same point");
                        AfxMessageBox(szLan);
                        return TRUE;
                    }
                    m_bCloseIn = FALSE;
                    m_bMouseMove = FALSE;
                    m_struPdcRuleCfg.struPolyLine.struPoint[m_dwLineNum].fX = (float)(pt.x - rcWnd.left) / (float)rcWnd.Width();
                    m_struPdcRuleCfg.struPolyLine.struPoint[m_dwLineNum].fY = (float)(pt.y - rcWnd.top) / (float)rcWnd.Height();
                    m_dwLineNum++;
                }

            }
            if (m_iDrawType == 6)// Draw polygon
            {
                if (PtInRect(&rcWnd, pt))
                {
                    if (m_bCloseIn)
                    {
                        m_dwPosNum = 0;
                        m_struPdcRuleCfg.struCountPolygon.dwPointNum = m_dwPosNum;
                    }
                    if (m_dwPosNum > 9)
                    {
                        char szLan[128] = { 0 };
                        g_StringLanType(szLan, "人数统计规则为4边形", "Polygon vertex can not be over 4!");
                        AfxMessageBox(szLan);
                        return TRUE;
                    }
                    if ((float)(pt.x - rcWnd.left) / (float)rcWnd.Width() <= m_struPdcRuleCfg.struCountPolygon.struPos[m_dwPosNum - 1].fX + 0.01 && (float)(pt.x - rcWnd.left) / (float)rcWnd.Width() >= m_struPdcRuleCfg.struCountPolygon.struPos[m_dwPosNum - 1].fX - 0.01\
                        && (float)(pt.y - rcWnd.top) / (float)rcWnd.Height() <= m_struPdcRuleCfg.struCountPolygon.struPos[m_dwPosNum - 1].fY + 0.01 && (float)(pt.y - rcWnd.top) / (float)rcWnd.Height() >= m_struPdcRuleCfg.struCountPolygon.struPos[m_dwPosNum - 1].fY - 0.01)
                    {
                        char szLan[128] = { 0 };
                        g_StringLanType(szLan, "不能连续在同一点上画区域", "Region can not be painted in the same point");
                        AfxMessageBox(szLan);
                        return TRUE;
                    }
                    m_bCloseIn = FALSE;
                    m_bMouseMove = FALSE;
                    m_struPdcRuleCfg.struCountPolygon.struPos[m_dwPosNum].fX = (float)(pt.x - rcWnd.left) / (float)rcWnd.Width();
                    m_struPdcRuleCfg.struCountPolygon.struPos[m_dwPosNum].fY = (float)(pt.y - rcWnd.top) / (float)rcWnd.Height();
                    m_dwPosNum++;
                    m_struPdcRuleCfg.struCountPolygon.dwPointNum = m_dwPosNum;
                }

            }
            break;
        }
    case WM_MOUSEMOVE:
        if ((m_iDrawType == 1 || m_iDrawType == 2 || m_iDrawType == 3 || m_iDrawType == 4 || m_iDrawType == 5 || m_iDrawType == 6) && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            if (m_iDrawType == 1)
            {
                if(PtInRect(&rcWnd,pt))
                {
                    if(m_dwPosNum > 9)
                    {
                        return TRUE;
                    }
                    if( !m_bCloseIn)
                    {
                        m_bMouseMove = TRUE;
                        m_struPdcRuleCfg.struPolygon.struPos[m_dwPosNum].fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struPdcRuleCfg.struPolygon.struPos[m_dwPosNum].fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
                        m_struPdcRuleCfg.struPolygon.dwPointNum = m_dwPosNum+1;				
                    }
                }
            }
            else if (m_iDrawType == 2)
            {
                if(PtInRect(&rcWnd,pt))
                {
                    if(m_bMouseMove)
                    {
                        m_struPdcRuleCfg.struEnterDirection.struEndPoint.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struPdcRuleCfg.struEnterDirection.struEndPoint.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();			
                    }
                }

            }
            else if (m_iDrawType == 3)
            {
                if(PtInRect(&rcWnd,pt))
                {
                    if(m_bMouseMove)
                    {
                        m_struPdcRuleCfg.struLine.struEnd.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struPdcRuleCfg.struLine.struEnd.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();			
                    }
                }
                
            }
            else if (m_iDrawType == 4)
            {
                if (PtInRect(&rcWnd, pt) && m_bMouseMove)
                {
                    m_struPdcRuleCfg.struAutoCalibPolygon.struPos[1].fX = m_struPdcRuleCfg.struAutoCalibPolygon.struPos[0].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
                    m_struPdcRuleCfg.struAutoCalibPolygon.struPos[1].fY = m_struPdcRuleCfg.struAutoCalibPolygon.struPos[2].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;
                    m_struPdcRuleCfg.struAutoCalibPolygon.struPos[3].fX = m_struPdcRuleCfg.struAutoCalibPolygon.struPos[2].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
                    m_struPdcRuleCfg.struAutoCalibPolygon.struPos[3].fY = m_struPdcRuleCfg.struAutoCalibPolygon.struPos[0].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;
                    m_struPdcRuleCfg.struAutoCalibPolygon.struPos[2].fX = (float)(pt.x - rcWnd.left) / (float)rcWnd.Width();
                    m_struPdcRuleCfg.struAutoCalibPolygon.struPos[2].fY = (float)(pt.y - rcWnd.top) / (float)rcWnd.Height();
                    m_struPdcRuleCfg.struAutoCalibPolygon.dwPointNum = 4;
                }
            }
            else if (m_iDrawType == 5)
            {
                if (PtInRect(&rcWnd, pt))
                {
                    if (m_dwLineNum > 3)
                    {
                        return TRUE;
                    }
                    if (!m_bCloseIn)
                    {
                        m_bMouseMove = TRUE;
                        m_struPdcRuleCfg.struPolyLine.struPoint[m_dwLineNum].fX = (float)(pt.x - rcWnd.left) / (float)rcWnd.Width();
                        m_struPdcRuleCfg.struPolyLine.struPoint[m_dwLineNum].fY = (float)(pt.y - rcWnd.top) / (float)rcWnd.Height();
                    }
                }
            }
            if (m_iDrawType == 6)
            {
                if (PtInRect(&rcWnd, pt))
                {
                    if (m_dwPosNum > 9)
                    {
                        return TRUE;
                    }
                    if (!m_bCloseIn)
                    {
                        m_bMouseMove = TRUE;
                        m_struPdcRuleCfg.struCountPolygon.struPos[m_dwPosNum].fX = (float)(pt.x - rcWnd.left) / (float)rcWnd.Width();
                        m_struPdcRuleCfg.struCountPolygon.struPos[m_dwPosNum].fY = (float)(pt.y - rcWnd.top) / (float)rcWnd.Height();
                        m_struPdcRuleCfg.struCountPolygon.dwPointNum = m_dwPosNum + 1;
                    }
                }
            }
        }
        break;
    case WM_LBUTTONUP:
        if ((m_iDrawType == 1 || m_iDrawType == 4 || m_iDrawType == 5 || m_iDrawType == 6) && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            if (m_iDrawType == 4)
            {
                m_struPdcRuleCfg.struAutoCalibPolygon.struPos[1].fX = m_struPdcRuleCfg.struAutoCalibPolygon.struPos[0].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
                m_struPdcRuleCfg.struAutoCalibPolygon.struPos[1].fY = m_struPdcRuleCfg.struAutoCalibPolygon.struPos[2].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;
                m_struPdcRuleCfg.struAutoCalibPolygon.struPos[3].fX = m_struPdcRuleCfg.struAutoCalibPolygon.struPos[2].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
                m_struPdcRuleCfg.struAutoCalibPolygon.struPos[3].fY = m_struPdcRuleCfg.struAutoCalibPolygon.struPos[0].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;
                m_struPdcRuleCfg.struAutoCalibPolygon.struPos[2].fX = (float)(pt.x - rcWnd.left) / (float)rcWnd.Width();
                m_struPdcRuleCfg.struAutoCalibPolygon.struPos[2].fY = (float)(pt.y - rcWnd.top) / (float)rcWnd.Height();
            }
            m_bMouseMove = FALSE;
        }
        break;

    case WM_RBUTTONDOWN:
        if ((m_iDrawType == 1) && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            if(PtInRect(&rcWnd,pt))
            {
                if(m_dwPosNum > 9)
                {
                    return TRUE;
                }
                for(i=0; i<m_dwPosNum; i++)
                {
                    if(m_struPdcRuleCfg.struPolygon.struPos[i].fX != m_struPdcRuleCfg.struPolygon.struPos[i+1].fX)
                    {
                        bXOneLine = FALSE;
                        break;
                    }
                }
                for(i=0; i<m_dwPosNum; i++)
                {
                    if(m_struPdcRuleCfg.struPolygon.struPos[i].fY != m_struPdcRuleCfg.struPolygon.struPos[i+1].fY)
                    {
                        bYOneLine = FALSE;
                        break;
                    }
                }
                bOneLine = bXOneLine||bYOneLine;
                if(bOneLine)
                {
                    char szlan[128] = {0};
                    g_StringLanType(szlan, "所画点成一线，无法构成区域!","Can not constitute a regional");
                    AfxMessageBox(szlan);
                    return TRUE;
                }
                if( !m_bCloseIn)
                {
                    if(m_bMouseMove)
                    {
                        m_bMouseMove = FALSE;
                        m_struPdcRuleCfg.struPolygon.dwPointNum--;
                        m_struPdcRuleCfg.struPolygon.struPos[m_struPdcRuleCfg.struPolygon.dwPointNum].fX = 0;
                        m_struPdcRuleCfg.struPolygon.struPos[m_struPdcRuleCfg.struPolygon.dwPointNum].fY = 0;
                    }
                    m_bCloseIn = TRUE;
                }
            }
        }
        else if(m_iDrawType == 1)
        {
            if(PtInRect(&rcWnd,pt))
            {
                if(m_dwPosNum == 0)
                {
                    return TRUE;
                }
                if( !m_bCloseIn)
                {
                    m_struPdcRuleCfg.struPolygon.dwPointNum--;
                    m_dwPosNum--;
                    m_struPdcRuleCfg.struPolygon.struPos[m_struPdcRuleCfg.struPolygon.dwPointNum].fX = 0;
                    m_struPdcRuleCfg.struPolygon.struPos[m_struPdcRuleCfg.struPolygon.dwPointNum].fY = 0;
                }
                else if( m_bCloseIn)
                {
                    m_struPdcRuleCfg.struPolygon.dwPointNum = 0;
                    m_dwPosNum = 0;
                    m_bCloseIn = FALSE;
                }
            }
        }
        else if ((m_iDrawType == 5) && (GetAsyncKeyState(VK_LCONTROL) < 0 || GetAsyncKeyState(VK_RCONTROL) < 0))
        {
            if (PtInRect(&rcWnd, pt))
            {
                if (m_dwLineNum > 3)
                {
                    return TRUE;
                }
                for (i = 0; i < m_dwLineNum; i++)
                {
                    if (m_struPdcRuleCfg.struPolyLine.struPoint[i].fX != m_struPdcRuleCfg.struPolyLine.struPoint[i + 1].fX)
                    {
                        bXOneLine = FALSE;
                        break;
                    }
                }
                for (i = 0; i < m_dwLineNum; i++)
                {
                    if (m_struPdcRuleCfg.struPolyLine.struPoint[i].fY != m_struPdcRuleCfg.struPolyLine.struPoint[i + 1].fY)
                    {
                        bYOneLine = FALSE;
                        break;
                    }
                }
                bOneLine = bXOneLine || bYOneLine;
                if (bOneLine)
                {
                    char szlan[128] = { 0 };
                    g_StringLanType(szlan, "所画点成一线，无法构成区域!", "Can not constitute a regional");
                    AfxMessageBox(szlan);
                    return TRUE;
                }
                if (!m_bCloseIn)
                {
                    if (m_bMouseMove)
                    {
                        m_bMouseMove = FALSE;
                        m_struPdcRuleCfg.struPolyLine.struPoint[m_dwLineNum - 1].fX = 0;
                        m_struPdcRuleCfg.struPolyLine.struPoint[m_dwLineNum - 1].fY = 0;
                    }
                    m_bCloseIn = TRUE;
                }
            }
        }
        else if (m_iDrawType == 5)
        {
            if (PtInRect(&rcWnd, pt))
            {
                if (m_dwLineNum == 0)
                {
                    return TRUE;
                }
                m_dwLineNum--;
                m_struPdcRuleCfg.struPolyLine.struPoint[m_dwLineNum].fX = 0;
                m_struPdcRuleCfg.struPolyLine.struPoint[m_dwLineNum].fY = 0;
            }
        }
        if ((m_iDrawType == 6) && (GetAsyncKeyState(VK_LCONTROL) < 0 || GetAsyncKeyState(VK_RCONTROL) < 0))
        {
            if (PtInRect(&rcWnd, pt))
            {
                if (m_dwPosNum > 9)
                {
                    return TRUE;
                }
                for (i = 0; i < m_dwPosNum; i++)
                {
                    if (m_struPdcRuleCfg.struCountPolygon.struPos[i].fX != m_struPdcRuleCfg.struCountPolygon.struPos[i + 1].fX)
                    {
                        bXOneLine = FALSE;
                        break;
                    }
                }
                for (i = 0; i < m_dwPosNum; i++)
                {
                    if (m_struPdcRuleCfg.struCountPolygon.struPos[i].fY != m_struPdcRuleCfg.struCountPolygon.struPos[i + 1].fY)
                    {
                        bYOneLine = FALSE;
                        break;
                    }
                }
                bOneLine = bXOneLine || bYOneLine;
                if (bOneLine)
                {
                    char szlan[128] = { 0 };
                    g_StringLanType(szlan, "所画点成一线，无法构成区域!", "Can not constitute a regional");
                    AfxMessageBox(szlan);
                    return TRUE;
                }
                if (!m_bCloseIn)
                {
                    if (m_bMouseMove)
                    {
                        m_bMouseMove = FALSE;
                        m_struPdcRuleCfg.struCountPolygon.dwPointNum--;
                        m_struPdcRuleCfg.struCountPolygon.struPos[m_struPdcRuleCfg.struCountPolygon.dwPointNum].fX = 0;
                        m_struPdcRuleCfg.struCountPolygon.struPos[m_struPdcRuleCfg.struCountPolygon.dwPointNum].fY = 0;
                    }
                    m_bCloseIn = TRUE;
                }
            }
        }
        else if (m_iDrawType == 6)
        {
            if (PtInRect(&rcWnd, pt))
            {
                if (m_dwPosNum == 0)
                {
                    return TRUE;
                }
                if (!m_bCloseIn)
                {
                    m_struPdcRuleCfg.struCountPolygon.dwPointNum--;
                    m_dwPosNum--;
                    m_struPdcRuleCfg.struCountPolygon.struPos[m_struPdcRuleCfg.struCountPolygon.dwPointNum].fX = 0;
                    m_struPdcRuleCfg.struCountPolygon.struPos[m_struPdcRuleCfg.struCountPolygon.dwPointNum].fY = 0;
                }
                else if (m_bCloseIn)
                {
                    m_struPdcRuleCfg.struCountPolygon.dwPointNum = 0;
                    m_dwPosNum = 0;
                    m_bCloseIn = FALSE;
                }
            }
        }
        break;
    default:
        break;
    }
    return CDialog::PreTranslateMessage(pMsg);
}

void CDlgPdcRuleCfgEx::PDCDetectLine(HDC hDc, NET_VCA_LINE struLine)
{
    DRAW_LINE_PARAM  struLaneLineParam;
    struLaneLineParam.color = RGB(0,255,0);
    NET_ITC_LINE struLaneLine = {0};
    memcpy(&struLaneLine.struLine, &struLine, sizeof(NET_VCA_LINE));
    struLaneLine.struLine = m_struPdcRuleCfg.struLine;
    memcpy(&struLaneLineParam.rcWnd, &m_rcWndRect, sizeof(m_rcWndRect));
	struLaneLineParam.struVcaLine = struLaneLine.struLine;

    CDrawFun::DrawLine(hDc, &struLaneLineParam);
}

void CDlgPdcRuleCfgEx::PDCDrawDirection(HDC hDc, DWORD dwUser)
{
    CPen cpDrawPen;
    
    int x1 = (int)(m_struPdcRuleCfg.struEnterDirection.struStartPoint.fX*m_rcWndRect.Width());
    int y1 = (int)(m_struPdcRuleCfg.struEnterDirection.struStartPoint.fY*m_rcWndRect.Height());
    
    int x2 = (int)(m_struPdcRuleCfg.struEnterDirection.struEndPoint.fX*m_rcWndRect.Width());
    int y2 = (int)(m_struPdcRuleCfg.struEnterDirection.struEndPoint.fY*m_rcWndRect.Height());
    
    if ((x1 == x2) && (y1 == y2))
    {
        return;
    }
    
    using namespace Gdiplus;
    Graphics graphics(hDc);
    
    Color color(80, 0, 0, 0);
    
    Pen pen(color, 7);
    
    pen.SetStartCap(LineCapFlat);
    
    Point pt1 = Point(0, -1);
    Point pt2 = Point(2, -1);
    Point pt3 = Point(0, 4);
    Point pt4 = Point(-2, -1);
    GraphicsPath fillPath;
    fillPath.AddLine(pt1, pt2);
    fillPath.AddLine(pt2, pt3);
    fillPath.AddLine(pt3, pt4);
    CustomLineCap custCap(&fillPath, NULL);
    pen.SetCustomEndCap(&custCap);
    cpDrawPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
    color.SetValue(color.MakeARGB(100, 0, 255, 255));
    SetTextColor(hDc,RGB(225, 225, 225));
    
    int k = 0;
    
    if(x2 != x1)
        k = (y2 - y1) / (x2 - x1);
    
    pen.SetColor(color);
    
    if(k < 0)
        graphics.DrawLine(&pen, x1-2, y1-1, x2-2, y2-1);
    else
        graphics.DrawLine(&pen, x1+2, y1-1, x2+2, y2-1);
    
    HGDIOBJ cpOldPen = SelectObject(hDc, cpDrawPen);
    
    cpDrawPen.DeleteObject();
    SelectObject(hDc, cpOldPen);
    
    graphics.ReleaseHDC(hDc);
}

void CDlgPdcRuleCfgEx::PDCDrawCalib(HDC hDc, DWORD dwUser)
{
    DRAW_POLYGON_PARAM_EX struMaxPolygonParam;
    DRAW_POLYGON_PARAM_EX struMinPolygonParam;
    memset(&struMaxPolygonParam, 0, sizeof(struMaxPolygonParam));
    struMaxPolygonParam.color = RGB(0, 255, 0);
    memcpy(&struMaxPolygonParam.rcWnd, &m_rcWndRect, sizeof(m_rcWndRect));
    struMaxPolygonParam.pArryPt = m_struPdcRuleCfg.struAutoCalibPolygon.struPos;
    struMaxPolygonParam.dwPtNum = m_struPdcRuleCfg.struAutoCalibPolygon.dwPointNum;
    CDrawFun::DrawPolygonEx(hDc, &struMaxPolygonParam);
}

void CDlgPdcRuleCfgEx::PDCDrawCalibResult(HDC hDc, DWORD dwUser)
{
    DRAW_POLYGON_PARAM_EX struMaxPolygonParam;
    DRAW_POLYGON_PARAM_EX struMinPolygonParam;
    memset(&struMaxPolygonParam, 0, sizeof(struMaxPolygonParam));
    struMaxPolygonParam.color = RGB(0, 0, 255);
    memcpy(&struMaxPolygonParam.rcWnd, &m_rcWndRect, sizeof(m_rcWndRect));
    struMaxPolygonParam.pArryPt = m_struPdcRuleCfg.struCountPolygon.struPos;
    struMaxPolygonParam.dwPtNum = m_struPdcRuleCfg.struCountPolygon.dwPointNum;
    CDrawFun::DrawPolygonEx(hDc, &struMaxPolygonParam);
}

long CDlgPdcRuleCfgEx::StartRealPlay()
{
    NET_DVR_CLIENTINFO struClientInfo;
    memset(&struClientInfo, 0, sizeof(NET_DVR_CLIENTINFO));
    struClientInfo.lChannel = m_lChannel;
    struClientInfo.hPlayWnd = GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
    m_lPlayHandle = NET_DVR_RealPlay_V30(m_lServerID, &struClientInfo, NULL, NULL, TRUE); 
    if (m_lPlayHandle == -1) 
    {
        AfxMessageBox("Fail to Preview");
        return m_lPlayHandle;
    }
    else
    {
        if (!NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawPDCShowEx, 0)) 
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RigisterDrawFun Fail");
            AfxMessageBox("Fail to set DrawFun callback");
        }
        
    }
    return m_lPlayHandle;
}

BOOL CDlgPdcRuleCfgEx::StopRealPlay()
{
    BOOL bRet;
    if (m_lPlayHandle >= 0)
    {
        bRet = NET_DVR_StopRealPlay(m_lPlayHandle);
        if (!bRet)
        {
            AfxMessageBox("Fail to stop preview");
        }
    }
    return bRet;
}

void CDlgPdcRuleCfgEx::F_DrawPdcRule(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
    F_DrawFrame(lRealHandle, hDc, dwUser,  RGB(255, 255, 0));
    PDCDrawDirection(hDc, dwUser);
    PDCDetectLine(hDc, m_struPdcRuleCfg.struLine);
    PDCDrawCalib(hDc, dwUser);
    PDCDrawCalibResult(hDc, dwUser);
    F_DrawPolyLine(lRealHandle, hDc, dwUser, RGB(255, 255, 0));
}

void CDlgPdcRuleCfgEx::GetPdcRuleWnd()
{
	BOOL bStatus = FALSE;
	m_struPdcRuleCond.dwSize = sizeof(NET_DVR_PDC_RULE_COND);
	m_struPdcRuleCond.dwChannel = m_lChannel;
    m_struPdcRuleCond.dwID = m_dwID.GetCurSel();
    char szLan[128] = {0};
	DWORD *pStatus = new DWORD[1];
    memset(pStatus, 0, sizeof(DWORD)*1);

    if (NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_PDC_RULECFG_V42, 1, &m_struPdcRuleCond, sizeof(NET_DVR_PDC_RULE_COND), \
		pStatus, &m_struPdcRuleCfg, sizeof(m_struPdcRuleCfg)))
	{
		DWORD *pStatusTmp = pStatus;
		for (int i = 0; i < 1; i++)
		{
			if (*pStatusTmp != 0)
			{
				bStatus = TRUE;
				g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PDC_RULECFG_V42");
				delete [] pStatus;
				return;
			}
			pStatusTmp++;
		}
		
		if (!bStatus)
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PDC_RULECFG_V42");
		} 
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PDC_RULECFG_V42");
		delete [] pStatus;
		return;
	}
	delete [] pStatus;
   
    m_OSDEnable_New.SetCurSel(m_struPdcRuleCfg.byOSDEnable);
	m_fPointX = m_struPdcRuleCfg.struOSDPoint.fX;
	m_fPointY = m_struPdcRuleCfg.struOSDPoint.fY;
    m_bEnableRule = m_struPdcRuleCfg.byEnable;
	m_byDetSensitivity = m_struPdcRuleCfg.byDetecteSensitivity;
	m_byGeneratieSpeedSpace = m_struPdcRuleCfg.byGenerateSpeedSpace;
	m_byGeneratieSpeedTime = m_struPdcRuleCfg.byGenerateSpeedTime;
	m_byCountSpeed = m_struPdcRuleCfg.byCountSpeed;
	m_comboDetType.SetCurSel(m_struPdcRuleCfg.byDetecteType);
	m_byTargetSizeCorrect = m_struPdcRuleCfg.byTargetSizeCorrect;
    m_bStreamOverlayRuleInfos = m_struPdcRuleCfg.byStreamOverlayRuleInfos;
    m_comboCountingType.SetCurSel(m_struPdcRuleCfg.byCountingType);
    m_comboSignalType.SetCurSel(m_struPdcRuleCfg.byCountingType);
    m_bRS485TransmissionEnabled = m_struPdcRuleCfg.byRS485TransmissionEnabled;
    m_ctResetDate.SetDate(m_struPdcRuleCfg.struDailyResetTime.wYear, m_struPdcRuleCfg.struDailyResetTime.byMonth, m_struPdcRuleCfg.struDailyResetTime.byDay);
    m_ctResetDate.SetTime(0, 0, 0);
    m_ctResetTime.SetTime(m_struPdcRuleCfg.struDailyResetTime.byHour, m_struPdcRuleCfg.struDailyResetTime.byMinute, m_struPdcRuleCfg.struDailyResetTime.bySecond);

    m_comboUploadCycle.SetCurSel(m_struPdcRuleCfg.byDataUploadCycle);
    m_bChkSECUpload = m_struPdcRuleCfg.bySECUploadEnable;   

    m_ShadowEnable = m_struPdcRuleCfg.byInterferenceSuppression & 0x01;
    m_AroundEnable = (m_struPdcRuleCfg.byInterferenceSuppression >> 1) & 0x01;
    m_PushCarEnable = (m_struPdcRuleCfg.byInterferenceSuppression >> 2) & 0x01;

    m_DayReportEnable = m_struPdcRuleCfg.byEmailDayReport;
    m_WeekReportEnable = m_struPdcRuleCfg.byEmailWeekReport;
    m_MonthReportEnable = m_struPdcRuleCfg.byEmailMonthReport;
    m_YearReportEnable = m_struPdcRuleCfg.byEmailYearReport;
    m_cmbCalibType.SetCurSel(m_struPdcRuleCfg.byCalibrateType);
    m_cmbHeightFilter.SetCurSel(m_struPdcRuleCfg.byHeightFilterEnable);
    m_fHeightFilter = m_struPdcRuleCfg.fHeightFilter;
    m_fTiltAngle = m_struPdcRuleCfg.fTiltAngle;
    m_fHeelAngle = m_struPdcRuleCfg.fHeelAngle;
    m_fHeight = m_struPdcRuleCfg.fHeight;
    m_byDetectThreshold = m_struPdcRuleCfg.byDetectThreshold;
    m_bLightStream = m_struPdcRuleCfg.byAidedTrackEnabled;

    if (0 < m_struPdcRuleCfg.struCountPolygon.dwPointNum)
    {
        ((CButton *)GetDlgItem(IDC_COUNT_POLYGON))->SetCheck(TRUE);
    }
    else
    {
        ((CButton *)GetDlgItem(IDC_COUNT_POLYGON))->SetCheck(FALSE);
    }

    if(0 == m_struPdcRuleCfg.byCurDetectType)
    {
        ((CButton *)GetDlgItem(IDC_RADIO_DRAW_POLYGON))->SetCheck(TRUE);
        ((CButton *)GetDlgItem(IDC_RADIO_DETECT_LINE))->SetCheck(FALSE);
        ((CButton *)GetDlgItem(IDC_RADIO_POLY_LINE))->SetCheck(FALSE);
        m_iDrawType = 1;
    }
    else if (1 == m_struPdcRuleCfg.byCurDetectType)
    {
        ((CButton *)GetDlgItem(IDC_RADIO_DRAW_POLYGON))->SetCheck(FALSE);
        ((CButton *)GetDlgItem(IDC_RADIO_DETECT_LINE))->SetCheck(TRUE);
        ((CButton *)GetDlgItem(IDC_RADIO_POLY_LINE))->SetCheck(FALSE);
        m_iDrawType = 3;
    }
    else if (2 == m_struPdcRuleCfg.byCurDetectType)
    {
        ((CButton *)GetDlgItem(IDC_RADIO_DRAW_POLYGON))->SetCheck(FALSE);
        ((CButton *)GetDlgItem(IDC_RADIO_DETECT_LINE))->SetCheck(FALSE);
        ((CButton *)GetDlgItem(IDC_RADIO_POLY_LINE))->SetCheck(TRUE);
        m_iDrawType = 5;

        m_dwLineNum = 0;
        for (int n = 0; n < 4; n++)
        {
            if (m_struPdcRuleCfg.struPolyLine.struPoint[n].fX != 0 || m_struPdcRuleCfg.struPolyLine.struPoint[n].fY != 0)
            {
                m_dwLineNum++;
            }
        }
    }

	if (m_struPdcRuleCfg.struAlarmHandleType.dwHandleType == 0x04)
	{
		m_bUploadCenter = TRUE;
	}
	else
	{
		m_bUploadCenter = FALSE;
	}

	int nDay = 0;
	m_comboWeekday.SetCurSel(0);
	SetAlarmTimeToWnd(&m_struPdcRuleCfg.struAlarmTime[0][0], nDay);
    
    UpdateData(FALSE);	
}

void CDlgPdcRuleCfgEx::OnBtnPdcRulecfg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	BOOL bStatus = FALSE;
	DWORD *pStatus = new DWORD[1];
    memset(pStatus, 0, sizeof(DWORD)*1);

	m_struPdcRuleCond.dwSize = sizeof(NET_DVR_PDC_RULE_COND);
	m_struPdcRuleCond.dwChannel = m_lChannel;
    m_struPdcRuleCond.dwID = m_dwID.GetCurSel();
	m_struPdcRuleCfg.dwSize = sizeof(m_struPdcRuleCfg);

    m_struPdcRuleCfg.byOSDEnable = m_OSDEnable_New.GetCurSel();;
	m_struPdcRuleCfg.struOSDPoint.fX = m_fPointX;
	m_struPdcRuleCfg.struOSDPoint.fY = m_fPointY;

    m_struPdcRuleCfg.byEnable = m_bEnableRule;
	m_struPdcRuleCfg.byDetecteSensitivity = m_byDetSensitivity;
	m_struPdcRuleCfg.byGenerateSpeedSpace = m_byGeneratieSpeedSpace;
	m_struPdcRuleCfg.byGenerateSpeedTime = m_byGeneratieSpeedTime;
	m_struPdcRuleCfg.byCountSpeed = m_byCountSpeed;
	m_struPdcRuleCfg.byDetecteType = m_comboDetType.GetCurSel();
	m_struPdcRuleCfg.byTargetSizeCorrect = m_byTargetSizeCorrect;
    m_struPdcRuleCfg.byStreamOverlayRuleInfos = m_bStreamOverlayRuleInfos;
    m_struPdcRuleCfg.byCountingType = m_comboCountingType.GetCurSel();
    m_struPdcRuleCfg.bySignalType = m_comboSignalType.GetCurSel();
    m_struPdcRuleCfg.byRS485TransmissionEnabled = m_bRS485TransmissionEnabled;
    m_struPdcRuleCfg.struDailyResetTime.wYear = m_ctResetDate.GetYear();
    m_struPdcRuleCfg.struDailyResetTime.byMonth = m_ctResetDate.GetMonth();
    m_struPdcRuleCfg.struDailyResetTime.byDay = m_ctResetDate.GetDay();
    m_struPdcRuleCfg.struDailyResetTime.byHour = m_ctResetTime.GetHour();
    m_struPdcRuleCfg.struDailyResetTime.byMinute = m_ctResetTime.GetMinute();
    m_struPdcRuleCfg.struDailyResetTime.bySecond = m_ctResetTime.GetSecond();

    m_struPdcRuleCfg.byDataUploadCycle = m_comboUploadCycle.GetCurSel();
    m_struPdcRuleCfg.bySECUploadEnable = m_bChkSECUpload;
    m_struPdcRuleCfg.byInterferenceSuppression = 0;
    m_struPdcRuleCfg.byInterferenceSuppression |= (m_ShadowEnable << 0);
    m_struPdcRuleCfg.byInterferenceSuppression |= (m_AroundEnable << 1);
    m_struPdcRuleCfg.byInterferenceSuppression |= (m_PushCarEnable << 2);
    m_struPdcRuleCfg.byEmailDayReport = m_DayReportEnable;
    m_struPdcRuleCfg.byEmailWeekReport = m_WeekReportEnable;
    m_struPdcRuleCfg.byEmailMonthReport = m_MonthReportEnable;
    m_struPdcRuleCfg.byEmailYearReport = m_YearReportEnable;
    m_struPdcRuleCfg.byHeightFilterEnable = m_cmbHeightFilter.GetCurSel();
    m_struPdcRuleCfg.fHeightFilter = m_fHeightFilter;

    m_struPdcRuleCfg.byDetectThreshold = m_byDetectThreshold;
    m_struPdcRuleCfg.byAidedTrackEnabled = m_bLightStream;

	if (m_bUploadCenter)
	{
		m_struPdcRuleCfg.struAlarmHandleType.dwHandleType = 0x04;
	}
	else
	{
		m_struPdcRuleCfg.struAlarmHandleType.dwHandleType = 0x00;
	}
	
    char szLan[128] = {0};
    if (!NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_PDC_RULECFG_V42, 1, &m_struPdcRuleCond, sizeof(NET_DVR_PDC_RULE_COND), \
		pStatus, &m_struPdcRuleCfg, sizeof(m_struPdcRuleCfg)))
 	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_PDC_RULECFG_V42");
		delete [] pStatus;
		return;
	}
	else
	{
		DWORD *pStatusTmp = pStatus;
		for (int i = 0; i < 1; i++)
		{	
			if (*pStatusTmp != 0)
			{
				bStatus = TRUE;
				g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_PDC_RULECFG_V42");
				delete [] pStatus;
				return;
			}
			pStatusTmp++;
		}
		
		if (!bStatus)
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_PDC_RULECFG_V42");
		}
	}
	delete [] pStatus;
}

void CDlgPdcRuleCfgEx::OnRadioDrawPolygon() 
{
	// TODO: Add your control notification handler code here
	m_iDrawType = 1;
    m_struPdcRuleCfg.byCurDetectType = 0;
    ((CButton *)GetDlgItem(IDC_RADIO_DRAW_POLYGON))->SetCheck(TRUE);
    ((CButton *)GetDlgItem(IDC_RADIO_DETECT_LINE))->SetCheck(FALSE);
    ((CButton *)GetDlgItem(IDC_RADIO_DRAW_DIRECTION))->SetCheck(FALSE);
    ((CButton *)GetDlgItem(IDC_RADIO_POLY_LINE))->SetCheck(FALSE);
    ((CButton *)GetDlgItem(IDC_COUNT_POLYGON))->SetCheck(FALSE);
}

void CDlgPdcRuleCfgEx::OnRadioDrawDirection() 
{
	// TODO: Add your control notification handler code here
	m_iDrawType = 2; 
    ((CButton *)GetDlgItem(IDC_RADIO_DRAW_POLYGON))->SetCheck(FALSE);
    ((CButton *)GetDlgItem(IDC_RADIO_DETECT_LINE))->SetCheck(FALSE);
    ((CButton *)GetDlgItem(IDC_RADIO_DRAW_DIRECTION))->SetCheck(TRUE);
    ((CButton *)GetDlgItem(IDC_RADIO_POLY_LINE))->SetCheck(FALSE);
    ((CButton *)GetDlgItem(IDC_COUNT_POLYGON))->SetCheck(FALSE);
}

void CDlgPdcRuleCfgEx::OnRadioDetectLine()
{
    m_iDrawType = 3;
    m_struPdcRuleCfg.byCurDetectType = 1;
    ((CButton *)GetDlgItem(IDC_RADIO_DRAW_POLYGON))->SetCheck(FALSE);
    ((CButton *)GetDlgItem(IDC_RADIO_DETECT_LINE))->SetCheck(TRUE);
    ((CButton *)GetDlgItem(IDC_RADIO_DRAW_DIRECTION))->SetCheck(FALSE);
    ((CButton *)GetDlgItem(IDC_RADIO_POLY_LINE))->SetCheck(FALSE);
    ((CButton *)GetDlgItem(IDC_COUNT_POLYGON))->SetCheck(FALSE);
}

/*********************************************************
Function:	F_TimeTest
Desc:		Check Fortify time
Input:	
Output:	
Return:	BOOL
**********************************************************/
BOOL CDlgPdcRuleCfgEx::F_TimeTest()
{
	int i = 0;
	int j = 0;
	WORD wStartTime[MAX_TIMESEGMENT_V30], wStopTime[MAX_TIMESEGMENT_V30];
	char szLan[128] = {0};
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

void CDlgPdcRuleCfgEx::SetAlarmTimeToWnd(NET_DVR_SCHEDTIME const *pAlarmTime, int nDay)
{
    m_iHour11 = pAlarmTime[nDay*8+0].byStartHour;
    m_iMin11 = pAlarmTime[nDay*8+0].byStartMin;
    m_iHour12 = pAlarmTime[nDay*8+0].byStopHour;
    m_iMin12 = pAlarmTime[nDay*8+0].byStopMin;
    m_iHour21 = pAlarmTime[nDay*8+1].byStartHour;
    m_iMin21 = pAlarmTime[nDay*8+1].byStartMin;
    m_iHour22 = pAlarmTime[nDay*8+1].byStopHour;
    m_iMin22 = pAlarmTime[nDay*8+1].byStopMin;
	
	m_iHour31 = pAlarmTime[nDay*8+2].byStartHour;
	m_iMin31 = pAlarmTime[nDay*8+2].byStartMin;
	m_iHour32 = pAlarmTime[nDay*8+2].byStopHour;
	m_iMin32 = pAlarmTime[nDay*8+2].byStopMin;
	m_iHour41 = pAlarmTime[nDay*8+3].byStartHour;
	m_iMin41 = pAlarmTime[nDay*8+3].byStartMin;
	m_iHour42 = pAlarmTime[nDay*8+3].byStopHour;
	m_iMin42 = pAlarmTime[nDay*8+3].byStopMin;
	
	m_iHour51 = pAlarmTime[nDay*8+4].byStartHour;
	m_iMin51 = pAlarmTime[nDay*8+4].byStartMin;
	m_iHour52 = pAlarmTime[nDay*8+4].byStopHour;
	m_iMin52 = pAlarmTime[nDay*8+4].byStopMin;
	m_iHour61 = pAlarmTime[nDay*8+5].byStartHour;
	m_iMin61 = pAlarmTime[nDay*8+5].byStartMin;
	m_iHour62 = pAlarmTime[nDay*8+5].byStopHour;
	m_iMin62 = pAlarmTime[nDay*8+5].byStopMin;
	
	m_iHour71 = pAlarmTime[nDay*8+6].byStartHour;
	m_iMin71 = pAlarmTime[nDay*8+6].byStartMin;
	m_iHour72 = pAlarmTime[nDay*8+6].byStopHour;
	m_iMin72 = pAlarmTime[nDay*8+6].byStopMin;
	m_iHour81 = pAlarmTime[nDay*8+7].byStartHour;
	m_iMin81 = pAlarmTime[nDay*8+7].byStartMin;
	m_iHour82 = pAlarmTime[nDay*8+7].byStopHour;
	m_iMin82 = pAlarmTime[nDay*8+7].byStopMin;
}

void CDlgPdcRuleCfgEx::GetAlarmTimeFromWnd(NET_DVR_SCHEDTIME *pAlarmTime, int nDay)
{
    pAlarmTime[nDay*8+0].byStartHour = (BYTE)m_iHour11;
    pAlarmTime[nDay*8+0].byStartMin = (BYTE)m_iMin11;
    pAlarmTime[nDay*8+0].byStopHour = (BYTE)m_iHour12;
    pAlarmTime[nDay*8+0].byStopMin = (BYTE)m_iMin12;
    pAlarmTime[nDay*8+1].byStartHour = (BYTE)m_iHour21;
    pAlarmTime[nDay*8+1].byStartMin = (BYTE)m_iMin21;
    pAlarmTime[nDay*8+1].byStopHour = (BYTE)m_iHour22;
    pAlarmTime[nDay*8+1].byStopMin = (BYTE)m_iMin22;
	
	pAlarmTime[nDay*8+2].byStartHour = (BYTE)m_iHour31;
    pAlarmTime[nDay*8+2].byStartMin = (BYTE)m_iMin31;
    pAlarmTime[nDay*8+2].byStopHour = (BYTE)m_iHour32;
    pAlarmTime[nDay*8+2].byStopMin = (BYTE)m_iMin32;
    pAlarmTime[nDay*8+3].byStartHour = (BYTE)m_iHour41;
    pAlarmTime[nDay*8+3].byStartMin = (BYTE)m_iMin41;
    pAlarmTime[nDay*8+3].byStopHour = (BYTE)m_iHour42;
    pAlarmTime[nDay*8+3].byStopMin = (BYTE)m_iMin42;
	
	pAlarmTime[nDay*8+4].byStartHour = (BYTE)m_iHour51;
    pAlarmTime[nDay*8+4].byStartMin = (BYTE)m_iMin51;
    pAlarmTime[nDay*8+4].byStopHour = (BYTE)m_iHour52;
    pAlarmTime[nDay*8+4].byStopMin = (BYTE)m_iMin52;
    pAlarmTime[nDay*8+5].byStartHour = (BYTE)m_iHour61;
    pAlarmTime[nDay*8+5].byStartMin = (BYTE)m_iMin61;
    pAlarmTime[nDay*8+5].byStopHour = (BYTE)m_iHour62;
    pAlarmTime[nDay*8+5].byStopMin = (BYTE)m_iMin62;
	
	pAlarmTime[nDay*8+6].byStartHour = (BYTE)m_iHour71;
    pAlarmTime[nDay*8+6].byStartMin = (BYTE)m_iMin71;
    pAlarmTime[nDay*8+6].byStopHour = (BYTE)m_iHour72;
    pAlarmTime[nDay*8+6].byStopMin = (BYTE)m_iMin72;
    pAlarmTime[nDay*8+7].byStartHour = (BYTE)m_iHour81;
    pAlarmTime[nDay*8+7].byStartMin = (BYTE)m_iMin81;
    pAlarmTime[nDay*8+7].byStopHour = (BYTE)m_iHour82;
    pAlarmTime[nDay*8+7].byStopMin = (BYTE)m_iMin82;
}

void CDlgPdcRuleCfgEx::OnTimeOk2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    if (!F_TimeTest())
    {
        return;
    }
    int	i = m_comboWeekday.GetCurSel();	
    GetAlarmTimeFromWnd(&m_struPdcRuleCfg.struAlarmTime[0][0], i);
}

void CDlgPdcRuleCfgEx::OnTimeCopy2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    int j,k;
    int i = m_comboWeekday.GetCurSel();
    int m_nCopyTime = m_comboCopyTime.GetCurSel() - 1;
    
    if(m_nCopyTime == -1)
    {
        for(j=0; j<MAX_DAYS; j++)
        {
            if(j == i)
                continue;
            for(k=0; k<MAX_TIMESEGMENT_V30/*MAX_TIMESEGMENT_2*/; k++)
            {
                memcpy(&(m_struPdcRuleCfg.struAlarmTime[j][k]), &(m_struPdcRuleCfg.struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
            }
        }
    }
    else
    {
        for(k=0; k<MAX_TIMESEGMENT_V30/*MAX_TIMESEGMENT_2*/; k++)
        {
            memcpy(&(m_struPdcRuleCfg.struAlarmTime[m_nCopyTime][k]), &(m_struPdcRuleCfg.struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
        }
    }
}

BOOL CDlgPdcRuleCfgEx::IsCrossLine(NET_VCA_POLYGON *alarm_region)
{
    if(alarm_region == NULL)
    {
        return FALSE;
    }
    unsigned int i, j;
    DWORD nPointTotal = 0;
    NET_VCA_POINT *pPointArray = NULL;
    NET_VCA_POINT *pPntArr = NULL;
    BOOL    bCrossLine;
    
    pPointArray = alarm_region->struPos;
    nPointTotal = alarm_region->dwPointNum;
    bCrossLine  = FALSE;
    
    if (nPointTotal >= 3)
    {
        bCrossLine = FALSE;
    }
    else
    {
        pPntArr = new NET_VCA_POINT[nPointTotal];
        if (pPntArr == NULL)
        {
            char szLan[128] = {0};
            g_StringLanType(szLan, "内存分配失败!","Memory allocation failure!");
            AfxMessageBox(szLan);
            exit(EXIT_FAILURE);
        }
        
        for (i = 0; i < nPointTotal; i++)
        {
            pPntArr[i] = pPointArray[i];
        }
        
        for(i = 0; i < nPointTotal - 3; i++)
        {
            for (j = i + 2; j < nPointTotal-1; j++)
            {
                
                if (F_LineCrossDetect(pPntArr[i], pPntArr[i + 1], pPntArr[j], pPntArr[j + 1]))
                {
                    bCrossLine = TRUE;
                }			
            }
        }
        if (pPntArr != NULL)
        {
            delete [] pPntArr;
        }
    }
    return bCrossLine;
}

BOOL CDlgPdcRuleCfgEx::F_LineCrossDetect(NET_VCA_POINT p1, NET_VCA_POINT p2, NET_VCA_POINT q1, NET_VCA_POINT q2)
{
    NET_VCA_POINT p1_q1, q2_q1, p2_q1, q1_p1, p2_p1, q2_p1;    
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
    
    // 叉积1 (p1 - q1) × (q2 - q1)；
    z1 = p1_q1.fX * q2_q1.fY - q2_q1.fX * p1_q1.fY; 
    
    // 叉积2 (q2 - q1) × (p2 - q1)；
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
    
    // 叉积3 (q1 - p1) × (p2 - p1)；
    z3 = q1_p1.fX * p2_p1.fY - p2_p1.fX * q1_p1.fY;
    
    // 叉积4 (p2 - p1) × (q2 - p1);
    z4 = p2_p1.fX * q2_p1.fY - q2_p1.fX * p2_p1.fY;
    
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

BOOL CDlgPdcRuleCfgEx::IsValidArea(NET_VCA_POLYGON *alarm_region)
{
    if(alarm_region == NULL)
    {
        return FALSE;
    }
	
    if (F_IsStraightLine(alarm_region))
    {
        char szLan[128] = {0};
        g_StringLanType(szLan, "所有点在同一直线上，不能组成多边形!",\
            "All points have been in the same line, not able to form the polygon");
        MessageBox(szLan);
        return FALSE;
    }
	
    if (F_IsACrossLine(alarm_region))
    {
        char szLan[128] = {0};
        g_StringLanType(szLan,"终点和起点的连线与已有的直线相交，不能组成有效的多边形!", \
            "There are straight-line intersection, can not be composed of an effective polygon");
        MessageBox(szLan);
        return FALSE;
    }
    return TRUE;
}

/*********************************************************
Function:	F_DrawFrame
Desc:	
Input:	lPlayHandle, 播放窗口的播放句柄
hDc : 播放窗口的设备控制器句柄
dwUser: 用户数据，用于区分多路预览时都设置该回调函数
DWORD dwRuleID 当前规则ID
COLORREF color 划线颜色
Output:	
Return:	 void
**********************************************************/
/*********************************************************
  Function:	F_DrawFrame
  Desc:		Draw frame
  Input:	lRealHandle, player port;
            hDc,handle;
			dwUser, user data;
			color
  Output:	
  Return:	
**********************************************************/
void CDlgPdcRuleCfgEx::F_DrawFrame(long lRealHandle, HDC hDc, DWORD dwUser,  COLORREF color)
{
    using namespace Gdiplus;
    Graphics graphics(hDc);
    SolidBrush  brush(Color(50, 0, 0, 0));
    brush.SetColor(Color(50, GetRValue(color), GetGValue(color), GetBValue(color)));
    
    POINT point[VCA_MAX_POLYGON_POINT_NUM] = {0};
    
    CPen DrawPen;
    unsigned int i;
    
    DrawPen.CreatePen(PS_SOLID, 1, color);
    SetTextColor(hDc,color);
    
    HGDIOBJ pOldPen = SelectObject(hDc, DrawPen);
    MoveToEx(hDc, (int)(m_struPdcRuleCfg.struPolygon.struPos[0].fX*m_rcWndRect.Width()), \
        (int)(m_struPdcRuleCfg.struPolygon.struPos[0].fY*m_rcWndRect.Height()), NULL);
    
    for(i=1; i<m_struPdcRuleCfg.struPolygon.dwPointNum; i++)
    {
        
        LineTo(hDc, (int)(m_struPdcRuleCfg.struPolygon.struPos[i].fX*m_rcWndRect.Width()),\
            (int)(m_struPdcRuleCfg.struPolygon.struPos[i].fY*m_rcWndRect.Height()));
        //if cross, redraw
        if(i>=MIN_PNT_NUM && !m_bMouseMove && IsCrossLine(&m_struPdcRuleCfg.struPolygon))
        {
            char szLan[128] = {0};
            g_StringLanType(szLan,"多边形不相邻的边有相交情况存在,请重新输入!","Polygon edges are not adjacent is intersect");
            AfxMessageBox(szLan);
            m_dwPosNum--;
            m_struPdcRuleCfg.struPolygon.dwPointNum--;
            break;
        }

    }
    
    for (i=0; i<(int)m_struPdcRuleCfg.struPolygon.dwPointNum ; i++)
    {
        if (i == VCA_MAX_POLYGON_POINT_NUM)
        {
            break;
        }
        
        point[i].x = (int)(m_struPdcRuleCfg.struPolygon.struPos[i].fX*m_rcWndRect.Width());
        point[i].y = (int)(m_struPdcRuleCfg.struPolygon.struPos[i].fY*m_rcWndRect.Height());
    }
    
    if(VCA_MAX_POLYGON_POINT_NUM == i && !m_bMouseMove)
    {
        if (IsValidArea(&m_struPdcRuleCfg.struPolygon))
        {
            graphics.FillPolygon(&brush, (Point *)point, m_struPdcRuleCfg.struPolygon.dwPointNum);
            
            LineTo(hDc, (int)(m_struPdcRuleCfg.struPolygon.struPos[0].fX*m_rcWndRect.Width()), (int)(m_struPdcRuleCfg.struPolygon.struPos[0].fY*m_rcWndRect.Height()));	
            m_bCloseIn = TRUE;
        }else
        {
            m_bCloseIn = FALSE;
            m_struPdcRuleCfg.struPolygon.dwPointNum--;
            m_dwPosNum--;
        }
    }
    else if(m_struPdcRuleCfg.struPolygon.dwPointNum>2 && m_bCloseIn)
    {
        if (IsValidArea(&m_struPdcRuleCfg.struPolygon))
        {
            graphics.FillPolygon(&brush, (Point *)point, m_struPdcRuleCfg.struPolygon.dwPointNum);
            
            LineTo(hDc, (int)(m_struPdcRuleCfg.struPolygon.struPos[0].fX*m_rcWndRect.Width()),(int)(m_struPdcRuleCfg.struPolygon.struPos[0].fY*m_rcWndRect.Height()));
        }else
        {
            m_bCloseIn = FALSE;
        }
    }
    
    SelectObject(hDc, pOldPen);
    DeleteObject(DrawPen);
}

void CDlgPdcRuleCfgEx::F_DrawPolyLine(long lRealHandle, HDC hDc, DWORD dwUser, COLORREF color)
{
    using namespace Gdiplus;
    Graphics graphics(hDc);
    SolidBrush  brush(Color(50, 0, 0, 0));
    brush.SetColor(Color(50, GetRValue(color), GetGValue(color), GetBValue(color)));

    POINT point[4] = { 0 };
    NET_VCA_POLYGON   struPolyLine = { 0 };
    for (int x = 0; x < m_dwLineNum; x++)
    {
        struPolyLine.struPos[x].fX = m_struPdcRuleCfg.struPolyLine.struPoint[x].fX;
        struPolyLine.struPos[x].fY = m_struPdcRuleCfg.struPolyLine.struPoint[x].fY;
    }
    struPolyLine.dwPointNum = m_dwLineNum;

    CPen DrawPen;
    int i;

    DrawPen.CreatePen(PS_SOLID, 1, color);
    SetTextColor(hDc, color);

    HGDIOBJ pOldPen = SelectObject(hDc, DrawPen);
    MoveToEx(hDc, (int)(struPolyLine.struPos[0].fX*m_rcWndRect.Width()), \
        (int)(struPolyLine.struPos[0].fY*m_rcWndRect.Height()), NULL);

    for (i = 1; i < struPolyLine.dwPointNum; i++)
    {

        LineTo(hDc, (int)(struPolyLine.struPos[i].fX*m_rcWndRect.Width()), \
            (int)(struPolyLine.struPos[i].fY*m_rcWndRect.Height()));
        //if cross, redraw
        if (i >= MIN_PNT_NUM && !m_bMouseMove && IsCrossLine(&struPolyLine))
        {
            char szLan[128] = { 0 };
            g_StringLanType(szLan, "多边形不相邻的边有相交情况存在,请重新输入!", "Polygon edges are not adjacent is intersect");
            AfxMessageBox(szLan);
            m_dwLineNum--;
            struPolyLine.dwPointNum--;
            break;
        }

    }

    for (i = 0; i < (int)struPolyLine.dwPointNum; i++)
    {
        if (i == 4)
        {
            break;
        }

        point[i].x = (int)(struPolyLine.struPos[i].fX*m_rcWndRect.Width());
        point[i].y = (int)(struPolyLine.struPos[i].fY*m_rcWndRect.Height());
    }

    if (4 == i && !m_bMouseMove)
    {
        if (struPolyLine.struPos[0].fX == struPolyLine.struPos[3].fX && struPolyLine.struPos[0].fY == struPolyLine.struPos[3].fY)
        {
            char szLan[128] = { 0 };
            g_StringLanType(szLan, "不允许构成三角形,请重新输入!", "Triangle is not allowed");
            AfxMessageBox(szLan);

            m_bCloseIn = FALSE;
            struPolyLine.dwPointNum--;
            m_dwLineNum--;
        }
        else
        {
            m_bCloseIn = TRUE;
        }
    }

    SelectObject(hDc, pOldPen);
    DeleteObject(DrawPen);

    //DRAW_POLYGON_PARAM_EX struMaxPolygonParam;
    //DRAW_POLYGON_PARAM_EX struMinPolygonParam;
    //memset(&struMaxPolygonParam, 0, sizeof(struMaxPolygonParam));
    //struMaxPolygonParam.color = RGB(0, 255, 0);
    //memcpy(&struMaxPolygonParam.rcWnd, &m_rcWndRect, sizeof(m_rcWndRect));
    //struMaxPolygonParam.pArryPt = m_struPdcRuleCfg.struPolyLine.struPoint;
    //struMaxPolygonParam.dwPtNum = 4;
    //CDrawFun::DrawPolygonEx(hDc, &struMaxPolygonParam);
}

BOOL CDlgPdcRuleCfgEx::F_IsACrossLine(NET_VCA_POLYGON *alarm_region) // 
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
    
    if (nPointTotal == VCA_MAX_POLYGON_POINT_NUM)
    {
        bCrossLine = FALSE;
    }
    else
    {
        pPntArr = new NET_VCA_POINT[nPointTotal];
        if (pPntArr == NULL)
        {
            char szLan[128] = {0};
            g_StringLanType(szLan, "内存分配失败!","Memory allocation failure!");
            AfxMessageBox(szLan);
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

BOOL CDlgPdcRuleCfgEx::F_IsStraightLine(NET_VCA_POLYGON *alarm_region)  
{
    if(alarm_region == NULL)
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
    
    pPointArray = alarm_region->struPos;
    nPointTotal = alarm_region->dwPointNum;
    
    nXOffset = (int)(pPointArray[0].fX - pPointArray[1].fX);
    nYOffset = (int)(pPointArray[0].fY - pPointArray[1].fY);
    bStraightLine = TRUE;
    
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
    
    if ((0 != nXOffset) && (0 != nYOffset))
    {
        fSlope  = 1.0f * nYOffset / nXOffset;
        
        fOffset = pPointArray[0].fY - fSlope * pPointArray[1].fX;
        
        fCoefficient = (float)sqrt(1.0 + fSlope * fSlope);
        
        for (i = 2; i < nPointTotal; i ++)
        {
            fDistance = (float)fabs(fSlope * pPointArray[i].fX - pPointArray[i].fY + fOffset)/fCoefficient;
            
            if ((fDistance - 0.0f) > 0.000001f)
            {
                bStraightLine = FALSE;
                break;
            }
        }		
    }
    
    return bStraightLine;	
}

BOOL CDlgPdcRuleCfgEx::OnInitDialog() 
{
	CDialog::OnInitDialog();

	memset(&m_struPdcRuleCond, 0, sizeof(NET_DVR_PDC_RULE_COND));
// 	if (m_pStruPdcRuleCfg != NULL)
// 	{
// 		delete [] m_pStruPdcRuleCfg;
// 		m_pStruPdcRuleCfg = NULL;
// 	}
// 	m_pStruPdcRuleCfg = new NET_DVR_PDC_RULE_CFG_V42[1];
// 	memset(m_pStruPdcRuleCfg, 0, 1*sizeof(NET_DVR_PDC_RULE_CFG_V42));

	g_pDlgPdcRuleCfg = this;
    GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWndRect);
    m_bCloseIn = TRUE;
	// TODO: Add extra initialization here

    if (m_lPlayHandle >= 0)
    {
        StopRealPlay();
    }
    StartRealPlay();

	GetPdcRuleWnd();
    if (m_struPdcRuleCfg.byCalibrateType == 1)
    {
        GetDlgItem(IDC_EDIT_CALIB_HEIGHT)->EnableWindow(FALSE);
    }
    if (m_struPdcRuleCfg.byCalibrateType != 1)
    {
        GetDlgItem(IDC_RADIO_CALIB)->ShowWindow(FALSE);
    }
    memset(&m_strSetupResult, 0, sizeof(m_strSetupResult));
    m_cmbHeightFilterEnabled.SetCurSel(0);
    m_comboCountingType.SetCurSel(0);
    m_comboSignalType.SetCurSel(0);
    m_cmbType.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPdcRuleCfgEx::OnBtnPdcQuery() 
{
	// TODO: Add your control notification handler code here
	CDlgPDCSearch dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_lChannel = m_lChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgPdcRuleCfgEx::OnBtnCalibration() 
{
	// TODO: Add your control notification handler code here
	CDlgPdcCalibration dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel = m_lChannel;
    dlg.m_lPlayHandle = m_lPlayHandle;
    dlg.DoModal();
}

void CDlgPdcRuleCfgEx::OnBtnGetPdcRulecfg() 
{
	// TODO: Add your control notification handler code here
	GetPdcRuleWnd();
}

CDlgPdcRuleCfgEx::~CDlgPdcRuleCfgEx()
{
	if (m_lPlayHandle >= 0)
	{
		NET_DVR_StopRealPlay(m_lPlayHandle);
		m_lPlayHandle = -1;
	}
}

void CDlgPdcRuleCfgEx::OnBtnPdcResult() 
{
	// TODO: Add your control notification handler code here
	CDlgPdcResult dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel = m_lChannel;
    dlg.DoModal();
}

void CDlgPdcRuleCfgEx::OnBtnGetPdcLint()
{

}

void CDlgPdcRuleCfgEx::OnBtnSetPdcLint()
{

}
void CDlgPdcRuleCfgEx::OnBtnAdvResetCounte() 
{
	// TODO: Add your control notification handler code here
    CDlgVcaResetCounterCfg dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_iVcaChan = m_lChannel;
    dlg.m_bHideGetCtrl = TRUE;
    dlg.DoModal();
}

void CDlgPdcRuleCfgEx::OnBtnGetpdcrecommend() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    NET_DVR_PDC_RECOMMEND strPDCRecommend = {0};
    strPDCRecommend.dwSize = sizeof(strPDCRecommend);

    struCfg.lpOutBuffer = &strPDCRecommend;
    struCfg.dwOutSize = sizeof(strPDCRecommend);

    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_PDC_RECOMMEND, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PDC_RECOMMEND");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PDC_RECOMMEND");
    }
    
    m_fWidth = strPDCRecommend.wWidth;

    UpdateData(FALSE);
}

void CDlgPdcRuleCfgEx::OnBtnRemoveFlashstorage() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    
    NET_DVR_FLASHSTORAGE_REMOVE struFlashStorage = {0};
    struFlashStorage.dwSize = sizeof(struFlashStorage);
    struFlashStorage.dwChannel = m_lChannel;
    struFlashStorage.byPDCRemoveEnable = 0;
    struFlashStorage.byPDCRemoveEnable |= m_bChkRemovePDC;
    
    NET_DVR_STD_CONTROL struControl = {0};
    struControl.lpCondBuffer = &struFlashStorage;
    struControl.dwCondSize = sizeof(struFlashStorage);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struControl.lpStatusBuffer = m_szStatusBuf;
    struControl.dwStatusSize = ISAPI_STATUS_LEN;
    
    if (!NET_DVR_STDControl(m_lServerID, NET_DVR_REMOVE_FLASHSTORAGE, &struControl))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_REMOVE_FLASHSTORAGE");
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_REMOVE_FLASHSTORAGE");
    }
}


void CDlgPdcRuleCfgEx::OnCbnSelchangeCmbCalibType()
{
    UpdateData(TRUE);
    if (m_cmbCalibType.GetCurSel() == 1)
    {
        GetDlgItem(IDC_RADIO_CALIB)->ShowWindow(TRUE);
        GetDlgItem(IDC_EDIT_CALIB_HEIGHT)->EnableWindow(FALSE);
    }
    else
    {
        GetDlgItem(IDC_RADIO_CALIB)->ShowWindow(FALSE);
        GetDlgItem(IDC_EDIT_CALIB_HEIGHT)->EnableWindow(TRUE);
    }
    UpdateData(FALSE);
}


void CDlgPdcRuleCfgEx::OnBnClickedBtnHeightSet()
{
    UpdateData(TRUE);
    char szLan[512] = { 0 };
    NET_DVR_POS_INFO_OVERLAY m_struPosInfoOverlay = { 0 };
    m_struPosInfoOverlay.dwSize = sizeof(NET_DVR_POS_INFO_OVERLAY);;
    m_struPosInfoOverlay.byPosInfoOverlayEnable = m_cmbHeightFilterEnabled.GetCurSel();
    m_struPosInfoOverlay.byOverlayType = m_cmbType.GetCurSel();


    NET_DVR_STD_CONFIG m_struStdConfig = { 0 };
    m_struStdConfig.lpCondBuffer = &m_lChannel;
    m_struStdConfig.dwCondSize = sizeof(m_lChannel);



    m_struStdConfig.lpInBuffer = (LPVOID)&m_struPosInfoOverlay;
    m_struStdConfig.dwInSize = sizeof(m_struPosInfoOverlay);

    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    m_struStdConfig.lpStatusBuffer = m_szStatusBuf;
    m_struStdConfig.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_POS_INFO_OVERLAY, &m_struStdConfig))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_POS_INFO_OVERLAY ");
        sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_POS_INFO_OVERLAY ");
    }
}

void CDlgPdcRuleCfgEx::OnBnClickedBtnHeightGet()
{
    UpdateData(TRUE);
    char szLan[512] = { 0 };
    NET_DVR_POS_INFO_OVERLAY m_struPosInfoOverlay = { 0 };
    m_struPosInfoOverlay.dwSize = sizeof(NET_DVR_POS_INFO_OVERLAY);;



    NET_DVR_STD_CONFIG m_struStdConfig = { 0 };
    m_struStdConfig.lpCondBuffer = &m_lChannel;
    m_struStdConfig.dwCondSize = sizeof(m_lChannel);



    m_struStdConfig.lpOutBuffer = (LPVOID)&m_struPosInfoOverlay;
    m_struStdConfig.dwOutSize = sizeof(m_struPosInfoOverlay);

    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    m_struStdConfig.lpStatusBuffer = m_szStatusBuf;
    m_struStdConfig.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_POS_INFO_OVERLAY, &m_struStdConfig))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_POS_INFO_OVERLAY ");
        sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_POS_INFO_OVERLAY ");
        m_cmbHeightFilterEnabled.SetCurSel(m_struPosInfoOverlay.byPosInfoOverlayEnable);
        m_cmbType.SetCurSel(m_struPosInfoOverlay.byOverlayType);
    }
    UpdateData(FALSE);
}

void CDlgPdcRuleCfgEx::OnBnClickedBtnCalib()
{
    UpdateData(TRUE);
    char szLan[512] = { 0 };
    NET_DVR_SETUP_CALIB_COND m_struSetupCalib = { 0 };
    m_struSetupCalib.dwSize = sizeof(NET_DVR_SETUP_CALIB_COND);
    m_struSetupCalib.fHeight = m_fHeight;
    memcpy(&m_struSetupCalib.struAutoCalibPolygon, &m_struPdcRuleCfg.struAutoCalibPolygon, sizeof(m_struSetupCalib.struAutoCalibPolygon));
    m_struSetupCalib.byCalibrateType = m_cmbCalibType.GetCurSel();
    m_struSetupCalib.byIntelligentType = m_cmbArgType.GetCurSel();
    NET_DVR_STD_CONFIG m_struStdConfig = { 0 };




    m_struStdConfig.lpCondBuffer = (LPVOID)&m_struSetupCalib;
    m_struStdConfig.dwCondSize = sizeof(m_struSetupCalib);

    m_struStdConfig.lpOutBuffer = (LPVOID)&m_strSetupResult;
    m_struStdConfig.dwOutSize = sizeof(m_strSetupResult);

    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    m_struStdConfig.lpStatusBuffer = m_szStatusBuf;
    m_struStdConfig.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_POST_SETUP_CALIB, &m_struStdConfig))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_POST_SETUP_CALIB ");
        sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_POST_SETUP_CALIB");

        m_fHeight = m_strSetupResult.fHeight;
        m_struPdcRuleCfg.fHeight = m_strSetupResult.fHeight;
        m_struPdcRuleCfg.byCalibrateType = m_strSetupResult.byCalibrateType;
        m_fTiltAngle = m_strSetupResult.fTiltAngle;
        m_fHeelAngle = m_strSetupResult.fHeelAngle;
        m_struPdcRuleCfg.fTiltAngle = m_strSetupResult.fTiltAngle;
        m_struPdcRuleCfg.fHeelAngle = m_strSetupResult.fHeelAngle;
        memcpy(&m_struPdcRuleCfg.struEnterDirection, &m_strSetupResult.struEnterDirection, sizeof(m_strSetupResult.struEnterDirection));
        memcpy(&m_struPdcRuleCfg.struLine, &m_strSetupResult.struLine, sizeof(m_strSetupResult.struLine));
        memcpy(&m_struPdcRuleCfg.struCountPolygon, &m_strSetupResult.struCountPolygon, sizeof(m_strSetupResult.struCountPolygon));
    }
    UpdateData(FALSE);
}
void CDlgPdcRuleCfgEx::OnBnClickedRadioCalib()
{
    m_iDrawType = 4;
    return;
}



void CDlgPdcRuleCfgEx::OnBnClickedBtnCalibGet()
{
    UpdateData(TRUE);
    char szLan[512] = { 0 };
    NET_DVR_STD_CONFIG m_struStdConfig = { 0 };
    m_struStdConfig.lpInBuffer = NULL;
    m_struStdConfig.dwInSize = 0;
    memset(&m_strSetupResult, 0, sizeof(m_strSetupResult));
    m_struStdConfig.lpOutBuffer = (LPVOID)&m_strSetupResult;
    m_struStdConfig.dwOutSize = sizeof(m_strSetupResult);

    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    m_struStdConfig.lpStatusBuffer = m_szStatusBuf;
    m_struStdConfig.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_SETUP_CALIB, &m_struStdConfig))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SETUP_CALIB ");
        sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SETUP_CALIB");
        m_cmbCalibType.SetCurSel(m_strSetupResult.byCalibrateType);
        m_fHeight = m_strSetupResult.fHeight;
        m_struPdcRuleCfg.fHeight = m_strSetupResult.fHeight;
        m_struPdcRuleCfg.byCalibrateType = m_strSetupResult.byCalibrateType;
        m_fTiltAngle = m_strSetupResult.fTiltAngle;
        m_fHeelAngle = m_strSetupResult.fHeelAngle;
        m_struPdcRuleCfg.fTiltAngle = m_strSetupResult.fTiltAngle;
        m_struPdcRuleCfg.fHeelAngle = m_strSetupResult.fHeelAngle;
        memcpy(&m_struPdcRuleCfg.struEnterDirection, &m_strSetupResult.struEnterDirection, sizeof(m_strSetupResult.struEnterDirection));
        memcpy(&m_struPdcRuleCfg.struLine, &m_strSetupResult.struLine, sizeof(m_strSetupResult.struLine));
        memcpy(&m_struPdcRuleCfg.struCountPolygon, &m_strSetupResult.struCountPolygon, sizeof(m_strSetupResult.struCountPolygon));
    }
    UpdateData(FALSE);
}



void CDlgPdcRuleCfgEx::OnBnClickedRadioPolyLine()
{
    // TODO:  在此添加控件通知处理程序代码
    m_iDrawType = 5;
    m_struPdcRuleCfg.byCurDetectType = 2;
    ((CButton *)GetDlgItem(IDC_RADIO_DRAW_POLYGON))->SetCheck(FALSE);
    ((CButton *)GetDlgItem(IDC_RADIO_DETECT_LINE))->SetCheck(FALSE);
    ((CButton *)GetDlgItem(IDC_RADIO_DRAW_DIRECTION))->SetCheck(FALSE);
    ((CButton *)GetDlgItem(IDC_RADIO_POLY_LINE))->SetCheck(TRUE);
    ((CButton *)GetDlgItem(IDC_COUNT_POLYGON))->SetCheck(FALSE);
}

void CDlgPdcRuleCfgEx::OnBnClickedCountPolygon()
{
    // TODO:  在此添加控件通知处理程序代码

    m_iDrawType = 6;
    m_struPdcRuleCfg.byCurDetectType = 0;
    ((CButton *)GetDlgItem(IDC_RADIO_DRAW_POLYGON))->SetCheck(FALSE);
    ((CButton *)GetDlgItem(IDC_RADIO_DETECT_LINE))->SetCheck(FALSE);
    ((CButton *)GetDlgItem(IDC_RADIO_DRAW_DIRECTION))->SetCheck(FALSE);
    ((CButton *)GetDlgItem(IDC_RADIO_POLY_LINE))->SetCheck(FALSE);
    ((CButton *)GetDlgItem(IDC_COUNT_POLYGON))->SetCheck(TRUE);
    
}
