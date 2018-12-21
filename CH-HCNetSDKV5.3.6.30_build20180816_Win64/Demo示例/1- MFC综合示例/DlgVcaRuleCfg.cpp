/**********************************************************
FileName:    DlgVcaRuleCfg.cpp
Description: VCA Rule config and relate config      
Date:        2009/07/10
Note: 		
<version> <time>         <desc>
<1.0    > <2009/07/10>       <created>
***********************************************************/
// DlgVcaRuleCfg.cpp : implementation file
//
#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaRuleCfg.h"
#include "DlgVcaEnterRegion.h"
#include "DlgVcaMaskRegion.h"
#include <math.h>
#include "gdiplus/GdiPlus.h"
#include "DlgVcaLF.h"
#include "DrawFun.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CDlgVcaRuleCfg *g_pDlgVcaRuleCfg;  
#define  AlarmLine 1
#define  AlarmArea 2
/////////////////////////////////////////////////////////////////////////////
// CDlgVcaRuleCfg dialog

/*********************************************************
Function:	DrawAlertShow
Desc:		Callback of Draw on preview
Input:	nPort that is Player Handle
hDc    : DC handle of player window
dwUser: User data
Output:	none
Return:	none
**********************************************************/
void CALLBACK DrawAlertShow(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
    SetBkMode(hDc, TRANSPARENT);
    SetTextColor(hDc, RGB(255, 255, 255));
    if(g_pDlgVcaRuleCfg->m_bRuleActive)
    {
        g_pDlgVcaRuleCfg->F_DrawFun(lRealHandle, hDc, dwUser); 
    }
    
}

/*********************************************************
Function:	CDlgVcaRuleCfg
Desc:		Constructor
Input:	
Output:	
Return:	
**********************************************************/
CDlgVcaRuleCfg::CDlgVcaRuleCfg(CWnd* pParent /*=NULL*/)
: CDialog(CDlgVcaRuleCfg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgVcaRuleCfg)
    m_bFilterActive = FALSE;
    m_bSetMaxFilter = FALSE;
    m_bSetMiniFilter = FALSE;
    m_bHandleType1 = FALSE;
    m_bHandleType2 = FALSE;
    m_bHandleType3 = FALSE;
    m_bHandleType4 = FALSE;
    m_bHandleType5 = FALSE;
    m_bDrawPolygon = FALSE;
    m_bRuleActive = FALSE;
    m_csRuleName = _T("");
    m_iHour11 = 0;
    m_iHour12 = 0;
    m_iHour21 = 0;
    m_iHour22 = 0;
    m_iMin11 = 0;
    m_iMin12 = 0;
    m_iMin21 = 0;
    m_iMin22 = 0;
    m_iAlarmPersist = 0;
    m_bDrawLine = FALSE;
	m_fAlarmRate = 0.0f;
	m_fMinHeight = 0.0f;
	m_fMinWidth = 0.0f;
	m_fMaxHeight = 0.0f;
	m_fMaxWidth = 0.0f;
	m_dwLeaveDelay = 0;
	m_dwStaticDelay = 0;
	m_bChkPicRecordEn = FALSE;
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
	m_dwEventDelayTime = 0;
	m_fTriggerArea = 0;
	m_byHeightThreshold = 0;
	m_bNoneStateEffective = FALSE;
	m_byPeopleNumThreshold = 0;
	m_fSpacingThreshold = 0.0f;
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    m_iVcaChannel = -1;
    memset(&m_struRuleCfg, 0, sizeof(m_struRuleCfg));
    memset(&m_struBehaviorAbility, 0, sizeof(m_struBehaviorAbility)) ;
    memset(&m_struVcaChanInParam, 0, sizeof(m_struVcaChanInParam));
    memset(&m_struVcaCtrlCfg, 0, sizeof(m_struVcaCtrlCfg));
    memset(&m_struSizeFilter, 0, sizeof(m_struSizeFilter));
    memset(&m_rcWnd, 0, sizeof(m_rcWnd));
    m_lPlayHandle = -1;
    m_dwPosNum = 0;
    memset(&m_struVcaPolygon[0], 0, sizeof(NET_VCA_POLYGON)*MAX_RULE_NUM);
    memset(&m_struVcaLine[0], 0, sizeof(NET_VCA_LINE)*MAX_RULE_NUM);
    memset(&m_bCloseIn[0], 0, sizeof(BOOL)*MAX_RULE_NUM);
    memset(&m_bNeedRedraw[0], 0, sizeof(BOOL)*MAX_RULE_NUM);
    memset(&m_bMouseMove[0], 0, sizeof(BOOL)*MAX_RULE_NUM);
    m_iCurRuleID = -1;
    m_lPUServerID = -1;
	memset(&m_bAlarmOut[0], 0, sizeof(BOOL)*MAX_ALARMOUT_V30);
	m_dwEventType = 0xffffffff;

}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	none
Output:	none
Return:	none
**********************************************************/
void CDlgVcaRuleCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgVcaRuleCfg)
	DDX_Control(pDX, IDC_COMBO_DETECT_MODE, m_comDetectMode);
	DDX_Control(pDX, IDC_COMBO_RELSNAPCHAN3, m_comboRelSnapChan3);
	DDX_Control(pDX, IDC_COMBO_RELSNAPCHAN2, m_comboRelSnapChan2);
	DDX_Control(pDX, IDC_COMBO_RELSNAPCHAN1, m_comboRelSnapChan1);
	DDX_Control(pDX, IDC_COMBO_PERSONTYPE, m_comboPersonType);
	DDX_Control(pDX, IDC_COMBO_FILTER_STRATEGY, m_comboFilterStrategy);
	DDX_Control(pDX, IDC_COMBO_TRIGGERPOINT, m_comboTriggerPoint);
	DDX_Control(pDX, IDC_COMBO_TRIGGERMODE, m_comboTriggerMode);
	DDX_Control(pDX, IDC_TREE_ALARM_OUT_RELATE, m_treeAlarmOut);
	DDX_Control(pDX, IDC_COMBO_EVENT_PARAM_MODE, m_comboEventParamMode);
	DDX_Control(pDX, IDC_STATIC_DELAY_TIME, m_staticDelayTime);
	DDX_Control(pDX, IDC_COMBO_AUDIO_MODE, m_comboAudioMode);
	DDX_Control(pDX, IDC_COMBO_ALARM_DELAY, m_comboAlarmDelay);
	DDX_Control(pDX, IDC_COMBO_UP_LASTALARM, m_cmUpLastAlarm);
	DDX_Control(pDX, IDC_COMBO_RUN_MODE, m_comboRunMode);
	DDX_Control(pDX, IDC_COMBO_FILTER_MODE, m_comboFilterMode);
 	DDX_Control(pDX, IDC_STATIC_ALRAM_AREA, m_staticAlarmArea);
	DDX_Control(pDX, IDC_STATIC_ALARM_TEXT, m_staticAlarmText);
    DDX_Control(pDX, IDC_COMLINEALARMDIRECT, m_comboAlarmDirect);
    DDX_Control(pDX, IDC_LIST_RECORD_CHAN, m_listRecordChan);
    DDX_Control(pDX, IDC_COMBOWEEKDAY, m_comboWeekday);
    DDX_Control(pDX, IDC_COMBOCOPYTIME, m_comboCopyTime);
    DDX_Control(pDX, IDC_COMBO_SENSITIVE, m_comboSensitive);
    DDX_Control(pDX, IDC_COMBO_RULE_TYPE, m_comboRuleType);
    DDX_Control(pDX, IDC_COMBO_RULE_ID, m_comboRuleID);
    DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_comboResolution);
    DDX_Control(pDX, IDC_COMBO_PRO_PIC_TYPE, m_comboProPicType);
    DDX_Control(pDX, IDC_COMBO_PIC_QUALITY, m_comboPicQuality);
    DDX_Check(pDX, IDC_CHECK_FILTER_ACTIVE, m_bFilterActive);
    DDX_Check(pDX, IDC_CHECK_SET_MAX_FILTER, m_bSetMaxFilter);
    DDX_Check(pDX, IDC_CHECK_SET_MINI_FILTER, m_bSetMiniFilter);
    DDX_Check(pDX, IDC_CHECKHANDLETYPE1, m_bHandleType1);
    DDX_Check(pDX, IDC_CHECKHANDLETYPE2, m_bHandleType2);
    DDX_Check(pDX, IDC_CHECKHANDLETYPE3, m_bHandleType3);
    DDX_Check(pDX, IDC_CHECKHANDLETYPE4, m_bHandleType4);
    DDX_Check(pDX, IDC_CHECKHANDLETYPE5, m_bHandleType5);
    DDX_Check(pDX, IDC_CHK_DRAW_POLYGON, m_bDrawPolygon);
    DDX_Check(pDX, IDC_CHK_RULE_ACTIVE, m_bRuleActive);
    DDX_Text(pDX, IDC_EDIT_RULE_NAME, m_csRuleName);
    DDX_Text(pDX, IDC_EDITHOUR11, m_iHour11);
    DDX_Text(pDX, IDC_EDITHOUR12, m_iHour12);
    DDX_Text(pDX, IDC_EDITHOUR21, m_iHour21);
    DDX_Text(pDX, IDC_EDITHOUR22, m_iHour22);
    DDX_Text(pDX, IDC_EDITMIN11, m_iMin11);
    DDX_Text(pDX, IDC_EDITMIN12, m_iMin12);
    DDX_Text(pDX, IDC_EDITMIN21, m_iMin21);
    DDX_Text(pDX, IDC_EDITMIN22, m_iMin22);
    DDX_Text(pDX, IDC_EDIT_ALARM_PERSIST, m_iAlarmPersist);
    DDX_Check(pDX, IDC_CHK_DRAW_LINE, m_bDrawLine);
	DDX_Text(pDX, IDC_EDIT_ALARM_RATE, m_fAlarmRate);
	DDX_Text(pDX, IDC_EDIT_MIN_HEIGHT, m_fMinHeight);
	DDX_Text(pDX, IDC_EDIT_MIN_WIDTH, m_fMinWidth);
	DDX_Text(pDX, IDC_EDIT_MAX_HEIGHT, m_fMaxHeight);
	DDX_Text(pDX, IDC_EDIT_MAX_WIDTH, m_fMaxWidth);
	DDX_Text(pDX, IDC_EDIT_LEAVE_DELAY, m_dwLeaveDelay);
	DDX_Text(pDX, IDC_EDIT_STATIC_DELAY, m_dwStaticDelay);
	DDX_Check(pDX, IDC_CHK_PIC_RECORD_EN, m_bChkPicRecordEn);
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
	DDX_Text(pDX, IDC_EDIT_EVENT_DELAY_TIME, m_dwEventDelayTime);
	DDX_Text(pDX, IDC_EDIT_TRIGGERAREA, m_fTriggerArea);
	DDX_Text(pDX, IDC_EDIT_HEIGHT_THRESHOLD, m_byHeightThreshold);
	DDX_Check(pDX, IDC_CHECK_NONESTATE, m_bNoneStateEffective);
	DDX_Text(pDX, IDC_EDIT_PEOPLENUM_THRESHOLD, m_byPeopleNumThreshold);
	DDX_Text(pDX, IDC_EDIT_SPACING_THRESHOLD, m_fSpacingThreshold);
	//}}AFX_DATA_MAP
}

/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgVcaRuleCfg, CDialog)
//{{AFX_MSG_MAP(CDlgVcaRuleCfg)
    ON_BN_CLICKED(ID_BTN_SET_RULE_CFG, OnBtnSetRuleCfg)
    ON_BN_CLICKED(IDC_BTN_SET_ONE_RULE, OnBtnSetOneRule)
    ON_CBN_SELCHANGE(IDC_COMBO_RULE_ID, OnSelchangeComboRuleId)
    ON_BN_CLICKED(IDC_CHK_RULE_ACTIVE, OnChkRuleActive)
    ON_CBN_SELCHANGE(IDC_COMBO_RULE_TYPE, OnSelchangeComboRuleType)
    ON_BN_CLICKED(IDC_CHK_DRAW_POLYGON, OnChkDrawPolygon)
    ON_BN_CLICKED(IDC_CHECK_FILTER_ACTIVE, OnCheckFilterActive)
    ON_BN_CLICKED(IDC_CHECK_SET_MINI_FILTER, OnCheckSetMiniFilter)
    ON_BN_CLICKED(IDC_CHECK_SET_MAX_FILTER, OnCheckSetMaxFilter)
    ON_BN_CLICKED(IDC_CHK_DRAW_LINE, OnChkDrawLine)
    ON_CBN_SELCHANGE(IDC_COMLINEALARMDIRECT, OnSelchangeComlinealarmdirect)
    ON_BN_CLICKED(IDC_TIME_OK, OnTimeOk)
    ON_BN_CLICKED(IDC_TIME_COPY, OnTimeCopy)
    ON_CBN_SELCHANGE(IDC_COMBOWEEKDAY, OnSelchangeComboweekday)
    ON_BN_CLICKED(IDC_CHECKHANDLETYPE4, OnCheckhandletype4)
    ON_EN_CHANGE(IDC_EDIT_RULE_NAME, OnChangeEditRuleName)
	ON_CBN_SELCHANGE(IDC_COMBO_FILTER_MODE, OnSelchangeComboFilterMode)
	ON_NOTIFY(NM_CLICK, IDC_TREE_ALARM_OUT_RELATE, OnClickTreeAlarmOutRelate)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMBO_TRIGGERMODE, OnSelchangeComboTriggermode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaRuleCfg message handlers

BOOL CDlgVcaRuleCfg::PreTranslateMessage(MSG* pMsg) 
{
    // TODO: Add your specialized code here and/or call the base class
    CPoint pt(0,0);
    GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWnd);
    GetCursorPos(&pt);
    CString strTemp = _T("");
    DWORD i=0;
    BOOL bOneLine = TRUE,bXOneLine = TRUE,bYOneLine = TRUE;
    
    switch(pMsg->message)  // Message of Draw
    {
    case WM_LBUTTONDOWN:
        if( (m_bDrawLine || m_bDrawPolygon)&&
            (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))//Press CTRL to draw
        {
            if (m_bDrawPolygon)// Draw polygon
            {
                if(PtInRect(&m_rcWnd,pt))
                {	
                    if(m_bNeedRedraw[m_iCurRuleID])
                    {			
                        if(m_bCloseIn[m_iCurRuleID])
                        {
                            m_dwPosNum = 0;
                            m_struVcaPolygon[m_iCurRuleID].dwPointNum = m_dwPosNum;		
                        }
                        if(m_dwPosNum>9)
                        {
                            char szLan[128] = {0};
                            g_StringLanType(szLan,"多边形顶点不能超过10个!","Apexes of polygon should less than 11");
                            AfxMessageBox(szLan);
                            return TRUE;
                        }
                        if((float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() <= m_struVcaPolygon[m_iCurRuleID].struPos[m_dwPosNum-1].fX+0.01 && (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() >= m_struVcaPolygon[m_iCurRuleID].struPos[m_dwPosNum-1].fX-0.01\
                            && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() <= m_struVcaPolygon[m_iCurRuleID].struPos[m_dwPosNum-1].fY+0.01 && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() >= m_struVcaPolygon[m_iCurRuleID].struPos[m_dwPosNum-1].fY-0.01)
                        {
                            char szLan[128] = {0};
                            g_StringLanType(szLan, "不能连续在同一点上画区域", "Can't draw region on the point used");
                            AfxMessageBox(szLan);
                            return TRUE;
                        }
                        m_bCloseIn[m_iCurRuleID] = FALSE;
                        m_bMouseMove[m_iCurRuleID] = FALSE;
                        m_struVcaPolygon[m_iCurRuleID].struPos[m_dwPosNum].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                        m_struVcaPolygon[m_iCurRuleID].struPos[m_dwPosNum].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
                        m_dwPosNum++;
                        m_struVcaPolygon[m_iCurRuleID].dwPointNum = m_dwPosNum;			
                    }
                    else
                    {
                        return TRUE;
                    }
                }
            }
            if (m_bDrawLine) 
            {
                if(PtInRect(&m_rcWnd,pt))
                {		
                    if(!m_bMouseMove[m_iCurRuleID])
                    {
                        m_struVcaLine[m_iCurRuleID].struStart.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                        m_struVcaLine[m_iCurRuleID].struStart.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();		
                        m_struVcaLine[m_iCurRuleID].struEnd.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                        m_struVcaLine[m_iCurRuleID].struEnd.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();			
                        m_bMouseMove[m_iCurRuleID] = TRUE;
                    }
                    else
                    {
                        if ((float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() <= m_struVcaLine[m_iCurRuleID].struStart.fX+0.01 && (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() >= m_struVcaLine[m_iCurRuleID].struStart.fX-0.01\
                            && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() <= m_struVcaLine[m_iCurRuleID].struStart.fY+0.01 && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() >= m_struVcaLine[m_iCurRuleID].struStart.fY-0.01)
                        {
                            char szLan[128] = {0};
                            g_StringLanType(szLan, "不能连续在同一点上画区域", "Can't draw region on the point used");
                            AfxMessageBox(szLan);
                            return TRUE;
                        }
                        m_struVcaLine[m_iCurRuleID].struEnd.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                        m_struVcaLine[m_iCurRuleID].struEnd.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();			
                        m_bMouseMove[m_iCurRuleID] = FALSE;
                    }
                    
                }
                else
                {
                    return TRUE;
                }
            }
            
        }//First coordinate of Minimal Rectangle
        else if(m_bSetMiniFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            if(PtInRect(&m_rcWnd,pt))
            {
                m_struSizeFilter.struMiniRect.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                m_struSizeFilter.struMiniRect.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
            }
        }//First coordinate of Maximal Rectangle
        else if(m_bSetMaxFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            if(PtInRect(&m_rcWnd,pt))
            {
                m_struSizeFilter.struMaxRect.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                m_struSizeFilter.struMaxRect.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
            }
        }
        break;
    case WM_MOUSEMOVE:
        if((m_bDrawLine || m_bDrawPolygon)&&(GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            if (m_bDrawPolygon)
            {
                if(PtInRect(&m_rcWnd,pt))
                {
                    if(m_dwPosNum > 9)
                    {
                        return TRUE;
                    }
                    if( m_bNeedRedraw[m_iCurRuleID] && !m_bCloseIn[m_iCurRuleID])
                    {
                        m_bMouseMove[m_iCurRuleID] = TRUE;
                        m_struVcaPolygon[m_iCurRuleID].struPos[m_dwPosNum].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                        m_struVcaPolygon[m_iCurRuleID].struPos[m_dwPosNum].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
                        m_struVcaPolygon[m_iCurRuleID].dwPointNum = m_dwPosNum+1;				
                    }
                }
            }
            
            if(m_bDrawLine)
            {
                if(PtInRect(&m_rcWnd,pt))
                {
                    if(m_bMouseMove)
                    {
                        m_struVcaLine[m_iCurRuleID].struEnd.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                        m_struVcaLine[m_iCurRuleID].struEnd.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();			
                    }
                }
            }
        }
        else if(m_bSetMiniFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)) //尺寸过滤器
        {
            if(PtInRect(&m_rcWnd,pt))
            {
                m_struSizeFilter.struMiniRect.fWidth = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() - m_struSizeFilter.struMiniRect.fX;
                m_struSizeFilter.struMiniRect.fHeight = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() - m_struSizeFilter.struMiniRect.fY;
            }
            
        }
        else if(m_bSetMaxFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)) //尺寸过滤器
        {
            if(PtInRect(&m_rcWnd,pt))
            {	
                m_struSizeFilter.struMaxRect.fWidth = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() - m_struSizeFilter.struMaxRect.fX;
                m_struSizeFilter.struMaxRect.fHeight = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() - m_struSizeFilter.struMaxRect.fY;
            }
        }
        break;
    case WM_RBUTTONDOWN://Click right mouse to close the rectangle. 
        if(m_bDrawPolygon && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            if(PtInRect(&m_rcWnd,pt))
            {
                if(m_dwPosNum > 9)
                {
                    return TRUE;
                }
                for(i=0; i<m_dwPosNum; i++)
                {
                    if(m_struVcaPolygon[m_iCurRuleID].struPos[i].fX != m_struVcaPolygon[m_iCurRuleID].struPos[i+1].fX)
                    {
                        bXOneLine = FALSE;
                        break;
                    }
                }
                for(i=0; i<m_dwPosNum; i++)
                {
                    if(m_struVcaPolygon[m_iCurRuleID].struPos[i].fY != m_struVcaPolygon[m_iCurRuleID].struPos[i+1].fY)
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
                if( m_bNeedRedraw[m_iCurRuleID] && !m_bCloseIn[m_iCurRuleID])
                {
                    if(m_bMouseMove[m_iCurRuleID])
                    {
                        m_bMouseMove[m_iCurRuleID] = FALSE;
                        m_struVcaPolygon[m_iCurRuleID].dwPointNum--;
                        m_struVcaPolygon[m_iCurRuleID].struPos[m_struVcaPolygon[m_iCurRuleID].dwPointNum].fX = 0;
                        m_struVcaPolygon[m_iCurRuleID].struPos[m_struVcaPolygon[m_iCurRuleID].dwPointNum].fY = 0;
                    }
                    m_bCloseIn[m_iCurRuleID] = TRUE;
                }
            }
        }
        else if(m_bDrawPolygon)
        {
            if(PtInRect(&m_rcWnd,pt))
            {
                if(m_dwPosNum == 0)
                {
                    return TRUE;
                }
                if( m_bNeedRedraw[m_iCurRuleID] && !m_bCloseIn[m_iCurRuleID])
                {
                    m_struVcaPolygon[m_iCurRuleID].dwPointNum--;
                    m_dwPosNum--;
                    m_struVcaPolygon[m_iCurRuleID].struPos[m_struVcaPolygon[m_iCurRuleID].dwPointNum].fX = 0;
                    m_struVcaPolygon[m_iCurRuleID].struPos[m_struVcaPolygon[m_iCurRuleID].dwPointNum].fY = 0;
                }
                else if( m_bNeedRedraw[m_iCurRuleID] && m_bCloseIn[m_iCurRuleID])
                {
                    memset(&m_struVcaPolygon[m_iCurRuleID], 0, sizeof(m_struVcaPolygon[m_iCurRuleID]));
                    m_dwPosNum = 0;
                    m_bCloseIn[m_iCurRuleID] = FALSE;
                }
            }
        }
        break;
    default:
        break;
    }
    return CDialog::PreTranslateMessage(pMsg);
}

/*********************************************************
Function:	OnInitDialog
Desc:		 
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgVcaRuleCfg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    // TODO: Add extra initialization here

	m_comboSensitive.ResetContent();
	CString strSensitivity= "";
	for (int i = 0; i < 100; i++)
	{
		strSensitivity.Format("%d",i + 1);
        m_comboSensitive.InsertString(i,strSensitivity);
	}
    
    CRect rect;
    GetDlgItem(IDC_PLAYWND)->GetWindowRect(&rect);
    ScreenToClient(&rect);
    int nWidth = (int)((rect.Height()*352)/288);
    rect.left  += (long)fabs((long double)(rect.right - rect.left - nWidth))/2;
    rect.right = rect.left + nWidth;
    GetDlgItem(IDC_PLAYWND)->MoveWindow(rect);
    
    g_pDlgVcaRuleCfg = this; // 

    StartPlay();

    if (!GetVcaParam())
    {
	//	CDialog::OnCancel();
        //return FALSE;
    }
    
    InitWnd();
   
    m_comboRuleID.SetCurSel(0);
    OnSelchangeComboRuleId();
    m_comboWeekday.SetCurSel(0);


    SetVcaRuleToWnd(m_struRuleCfg);

	OnSelchangeComboTriggermode();
//
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVcaRuleCfg::InitWnd()
{   
	int i = 0;
    char szLan[128] = {0};
    for(i = 0;i<MAX_RULE_NUM; i++)
    {
        m_bNeedRedraw[i] = FALSE;//Redraw polygon
        m_bCloseIn[i] = TRUE;//Polygon is closed or not
    }
    
	m_comboRelSnapChan1.ResetContent();
	m_comboRelSnapChan2.ResetContent();
	m_comboRelSnapChan3.ResetContent();

	int nIndex = 0;
	for (i = g_struDeviceInfo[m_iDevIndex].iStartChan; i  <= g_struDeviceInfo[m_iDevIndex].iAnalogChanNum ; i++)
	{
		sprintf(szLan, "Analog Chan%d", i);
		m_comboRelSnapChan1.InsertString(nIndex,szLan);
		m_comboRelSnapChan2.InsertString(nIndex,szLan);
		m_comboRelSnapChan3.InsertString(nIndex,szLan);
		m_comboRelSnapChan1.SetItemData(nIndex, i);
		m_comboRelSnapChan2.SetItemData(nIndex, i);
		m_comboRelSnapChan3.SetItemData(nIndex, i);
		nIndex++;
	}
    
    for (i = 0; i  < g_struDeviceInfo[m_iDevIndex].pStruIPParaCfgV40->dwDChanNum ; i++)
	{
		sprintf(szLan, "IP Chan%d", i + 1);
		m_comboRelSnapChan1.InsertString(nIndex,szLan);
		m_comboRelSnapChan2.InsertString(nIndex,szLan);
		m_comboRelSnapChan3.InsertString(nIndex,szLan);
		m_comboRelSnapChan1.SetItemData(nIndex, i + g_struDeviceInfo[m_iDevIndex].pStruIPParaCfgV40->dwStartDChan);
		m_comboRelSnapChan2.SetItemData(nIndex, i + g_struDeviceInfo[m_iDevIndex].pStruIPParaCfgV40->dwStartDChan);
		m_comboRelSnapChan3.SetItemData(nIndex, i + g_struDeviceInfo[m_iDevIndex].pStruIPParaCfgV40->dwStartDChan);
		nIndex++;
	}


	g_StringLanType(szLan,"不使用","None");
	m_comboRelSnapChan1.InsertString(0,szLan);
	m_comboRelSnapChan2.InsertString(0,szLan);
	m_comboRelSnapChan3.InsertString(0,szLan);
	m_comboRelSnapChan1.SetItemData(0,0);
	m_comboRelSnapChan2.SetItemData(0,0);
	m_comboRelSnapChan3.SetItemData(0,0);
	m_comboRelSnapChan1.SetCurSel(0);
	m_comboRelSnapChan2.SetCurSel(0);
	m_comboRelSnapChan3.SetCurSel(0);

    InitRuleType(m_struBehaviorAbility.dwAbilityType, m_struBehaviorAbility.dwAbilityTypeEx);
    InitRuleID(m_struBehaviorAbility.byMaxRuleNum);

    nIndex = 0;
    m_comboFilterMode.ResetContent();
    g_StringLanType(szLan, "像素模式","Pix Mode");
    m_comboFilterMode.InsertString(nIndex, szLan);
    m_comboFilterMode.SetItemData(nIndex, IMAGE_PIX_MODE);
    nIndex++;

    g_StringLanType(szLan, "实际大小模式","Real Mode");
    m_comboFilterMode.InsertString(nIndex, szLan);
    m_comboFilterMode.SetItemData(nIndex, REAL_WORLD_MODE);
    nIndex++;

    g_StringLanType(szLan, "默认模式","Default Mode");
    m_comboFilterMode.InsertString(nIndex, szLan);
    m_comboFilterMode.SetItemData(nIndex, DEFAULT_MODE);
    nIndex++;


    m_comboRunMode.ResetContent();
    g_StringLanType(szLan, "像素模式","Pix Mode");
    m_comboRunMode.AddString(szLan);
    g_StringLanType(szLan, "实际大小模式","Real Mode");
    m_comboRunMode.AddString(szLan);

    g_StringLanType(szLan, "不启用","Disable");
	m_comboTriggerMode.InsertString(0,szLan);
	m_comboTriggerMode.SetItemData(0,TRIGGER_MODE_NONE);
	
    g_StringLanType(szLan, "轨迹点","Track point");
	m_comboTriggerMode.InsertString(1,szLan);
	m_comboTriggerMode.SetItemData(1,TRIGGER_MODE_TRACKPOINT);
	
	g_StringLanType(szLan, "目标面积","Target area");
	m_comboTriggerMode.InsertString(2,szLan);
	m_comboTriggerMode.SetItemData(2,TRIGGER_MODE_TARGETAREA);

	g_StringLanType(szLan, "中","Center");
	m_comboTriggerPoint.InsertString(0,szLan);
	m_comboTriggerPoint.SetItemData(0,TRIGGER_POINT_CENTER);

	g_StringLanType(szLan, "上","Up");
	m_comboTriggerPoint.InsertString(1,szLan);
	m_comboTriggerPoint.SetItemData(1,TRIGGER_POINT_UP);

	g_StringLanType(szLan, "下","Down");
	m_comboTriggerPoint.InsertString(2,szLan);
	m_comboTriggerPoint.SetItemData(2,TRIGGER_POINT_DOWN);

	g_StringLanType(szLan, "不启用","Disable");
	m_comboFilterStrategy.InsertString(0,szLan);
	m_comboFilterStrategy.SetItemData(0,FILTER_STRATEGY_NONE);


	g_StringLanType(szLan, "宽度和高度","Width and height");
	m_comboFilterStrategy.InsertString(1,szLan);
	m_comboFilterStrategy.SetItemData(1,FILTER_STRATEGY_WIDTH_AND_HEIGHT);

	g_StringLanType(szLan, "面积过滤","Area");
	m_comboFilterStrategy.InsertString(2,szLan);
	m_comboFilterStrategy.SetItemData(2,FILTER_STRATEGY_AERA);
    
	m_comboTriggerMode.SetCurSel(0);
	m_comboTriggerPoint.SetCurSel(0);
	m_comboFilterStrategy.SetCurSel(0);
}


BOOL CDlgVcaRuleCfg::GetVcaParam()
{
//     if (!GetVcaCtrlCfg())
//     {
//         AfxMessageBox("Fail to get vca ctrl");
//         return FALSE;
//     }
   
//     m_struVcaChanInParam.byVCAType = m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel -1].byVCAType;
//     if (m_struVcaChanInParam.byVCAType == VCA_ATM)
//     {
//         m_struVcaChanInParam.byMode = m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel -1].byMode;
//     }

	m_struVcaChanInParam.byVCAType = m_byVCAType;
	if (m_byVCAType == VCA_ATM)
	{
		m_struVcaChanInParam.byMode = m_byMode;
	}
    
    if (!GetVcaChanAbility())
    {
        AfxMessageBox("Fail to get vca chan ability");
        return FALSE;
    }

    if (!GetVcaRuleCfg())
    {
        AfxMessageBox("Fail to get vca rule config");
        return FALSE;
    }
    return TRUE;
}

BOOL CDlgVcaRuleCfg::GetVcaCtrlCfg()
{
    BOOL bRet = FALSE;
    DWORD dwReturn = 0;
    if(!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_VCA_CTRLCFG, -1, &m_struVcaCtrlCfg, sizeof(m_struVcaCtrlCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VCA_CTRLCFG");
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_VCA_CTRLCFG");
        bRet = TRUE;
    }
    return bRet;
}

BOOL CDlgVcaRuleCfg::GetVcaChanAbility()
{
    BOOL bRet = FALSE; 
    if (!NET_DVR_GetDeviceAbility(m_lServerID, VCA_CHAN_ABILITY, (char*)&m_struVcaChanInParam,\
        sizeof(m_struVcaChanInParam), (char*)&m_struBehaviorAbility, sizeof(m_struBehaviorAbility)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "VCA_CHAN_ABILITY");
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "VCA_CHAN_ABILITY");
        bRet = TRUE;
    }

    return bRet;
}


BOOL CDlgVcaRuleCfg::GetVcaRuleCfg()
{
    BOOL bRet = FALSE;
    DWORD dwReturn = 0;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_VCA_GET_RULECFG_V41, m_iVcaChannel, &m_struRuleCfg, sizeof(m_struRuleCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_VCA_GET_RULECFG_V41 Chan[%d]", m_iVcaChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_VCA_GET_RULECFG_V41 Chan[%d]", m_iVcaChannel);
        bRet = TRUE;
    }
    return bRet;
}

BOOL CDlgVcaRuleCfg::SetVcaRuleCfg()
{
    BOOL bRet= FALSE;
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_VCA_SET_RULECFG_V41, m_iVcaChannel, &m_struRuleCfg, sizeof(m_struRuleCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_VCA_SET_RULECFG_V41 Chan[%d]", m_iVcaChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_VCA_SET_RULECFG_V41 Chan[%d]", m_iVcaChannel);
        bRet = TRUE;
    }
    return bRet;
}

/*********************************************************
Function:	OnBtnSetRuleCfg
Desc:		
Input:	
Output:	
Return:	void
**********************************************************/
void CDlgVcaRuleCfg::OnBtnSetRuleCfg() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
	m_struRuleCfg.byPicProType = (unsigned char)m_comboProPicType.GetCurSel();
    m_struRuleCfg.byUpLastAlarm = (unsigned char)m_cmUpLastAlarm.GetCurSel();
	m_struRuleCfg.byPicRecordEnable = m_bChkPicRecordEn;
    m_struRuleCfg.struPictureParam.wPicSize = (unsigned short)m_comboResolution.GetCurSel();
    m_struRuleCfg.struPictureParam.wPicQuality = (unsigned short)m_comboPicQuality.GetCurSel();
	m_struRuleCfg.wRelSnapChan[0] = m_comboRelSnapChan1.GetItemData(m_comboRelSnapChan1.GetCurSel());
	m_struRuleCfg.wRelSnapChan[1] = m_comboRelSnapChan2.GetItemData(m_comboRelSnapChan2.GetCurSel());
	m_struRuleCfg.wRelSnapChan[2] = m_comboRelSnapChan3.GetItemData(m_comboRelSnapChan3.GetCurSel());
    char szLan[128] = {0};
    if (!SetVcaRuleCfg())
    {
        sprintf(szLan, "Fail to Set Channal%d VCA behavior rule", m_iVcaChannel);
        AfxMessageBox(szLan);
    }
    else
    {
        sprintf(szLan, "Success to Set Channal%d VCA behavior rule", m_iVcaChannel);
        AfxMessageBox(szLan);
    }
}



/*********************************************************
Function:	OnBtnSetOneRule
Desc:		
Input:	
Output:	
Return:	void
**********************************************************/
void CDlgVcaRuleCfg::OnBtnSetOneRule() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    GetOneVcaRuleFromWnd(m_struRuleCfg.struRule[m_iCurRuleID]);
	for (int i = 0; i<MAX_RULE_NUM; i++)
	{
		if(1 == m_struRuleCfg.struRule[i].byActive)
		{
			m_struRuleCfg.struRule[i].byEventTypeFlag = 1;
		}
	}
	m_struRuleCfg.wRelSnapChan[0] = m_comboRelSnapChan1.GetItemData(m_comboRelSnapChan1.GetCurSel());
	m_struRuleCfg.wRelSnapChan[1] = m_comboRelSnapChan2.GetItemData(m_comboRelSnapChan2.GetCurSel());
	m_struRuleCfg.wRelSnapChan[2] = m_comboRelSnapChan3.GetItemData(m_comboRelSnapChan3.GetCurSel());
    char szLan[128] = {0};
    if (!SetVcaRuleCfg())
    {
        sprintf(szLan, "Fail to Set Channal%d VCA behavior rule", m_iVcaChannel);
        AfxMessageBox(szLan);
    }
    else
    {
        sprintf(szLan, "Success to Set Channal%d VCA behavior rule", m_iVcaChannel);
        AfxMessageBox(szLan);
    }
}




/*********************************************************
Function:	InsertRuleType
Desc:	Insert Ability type in m_comboRuleType and m_comboRuleTypeEx. 
Input:	int iBehaviorAbilityType
Output:	
Return:	BOOL 
**********************************************************/
BOOL CDlgVcaRuleCfg::InitRuleType(int iBehaviorAbilityType, int iBehaviorAbilityTypeEx)
{
    m_comboRuleType.ResetContent();
    char szLan[128] = {0};
    int index = 0;
    if((iBehaviorAbilityType&TRAVERSE_PLANE_ABILITY) != 0)
    {
        g_StringLanType(szLan, "穿越警戒面", "Traverse Plane");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_TRAVERSE_PLANE);
        index++;
    }
    if((iBehaviorAbilityType&ENTER_AREA_ABILITY) != 0)
    {
        g_StringLanType(szLan, "进入区域", "Enter Area");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_ENTER_AREA);
        index++;
    }
    if((iBehaviorAbilityType&EXIT_AREA_ABILITY) != 0)
    {
        g_StringLanType(szLan, "离开区域", "Exit Area");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_EXIT_AREA);
        index++;
    }
    if((iBehaviorAbilityType&INTRUSION_ABILITY) != 0)
    {
        g_StringLanType(szLan, "入侵", "Intrusion");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_INTRUSION);
        index++;
    }
    if((iBehaviorAbilityType&LOITER_ABILITY) != 0)
    {
        g_StringLanType(szLan, "徘徊", "Loiter");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_LOITER);
        index++;
    }
    if((iBehaviorAbilityType&LEFT_TAKE_ABILITY) != 0)
    {
        g_StringLanType(szLan, "物品遗留拿取", "Left and Take");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_LEFT_TAKE);
        index++;
    }
    if((iBehaviorAbilityType&PARKING_ABILITY) != 0)
    {
        g_StringLanType(szLan, "停车", "Parking");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_PARKING);
        index++;
    }
    if((iBehaviorAbilityType&RUN_ABILITY) != 0)
    {
        g_StringLanType(szLan, "快速移动", "Running");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_RUN);
        index++;
    }
    if((iBehaviorAbilityType&HIGH_DENSITY_ABILITY) != 0)
    {
        g_StringLanType(szLan, "人员聚集", "Staff Density");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_HIGH_DENSITY);
        index++;
    }
    if ((iBehaviorAbilityType & VIOLENT_MOTION_ABILITY) != 0)
    {
        g_StringLanType(szLan, "剧烈运动", "Violent motion");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_VIOLENT_MOTION);
        index++;
    }
    
    if ((iBehaviorAbilityType & REACH_HIGHT_ABILITY) != 0)
    {
        g_StringLanType(szLan, "攀高检测", "Reach hight");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_REACH_HIGHT);
        index++;
    }

    if ((iBehaviorAbilityType & GET_UP_ABILITY) != 0)
    {
        g_StringLanType(szLan, "起身检测", "Get up");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_GET_UP);
        index++;
    }
    
	if ((iBehaviorAbilityType & KEY_PERSON_GET_UP_ABILITY) != 0)
    {
        g_StringLanType(szLan, "重点人员起身检测", "Get up");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_KEY_PERSON_GET_UP);
        index++;
    }

    if (iBehaviorAbilityType & LEFT_ABILITY)
    {
        g_StringLanType(szLan, "物品遗留", "Left");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_LEFT);
        index++;
    }

    if (iBehaviorAbilityType & TAKE_ABILITY)
    {
        g_StringLanType(szLan, "物品拿取", "Take");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_TAKE);
        index++;
    }

	if (iBehaviorAbilityType & LEAVE_POSITION)
	{
		g_StringLanType(szLan, "离岗", "Leave Position");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_LEAVE_POSITION);
        index++;
	}

	if (iBehaviorAbilityType & TRAIL_ABILITY)
    {
        g_StringLanType(szLan, "尾随", "Trail");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_TRAIL);
        index++;
    }
	
	if (iBehaviorAbilityType & STANDUP_ABILITY)
    {
        g_StringLanType(szLan, "起立", "Stand Up");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_STANDUP);
        index++;
    }
	
	if (iBehaviorAbilityType & FALL_DOWN_ABILITY)
    {
        g_StringLanType(szLan, "倒地", "Fall Down");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_FALL_DOWN);
        index++;
    }
	
	if (iBehaviorAbilityType & AUDIO_ABNORMAL_ABILITY)
    {
        g_StringLanType(szLan, "声强突变", "Audio abnormal");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_AUDIO_ABNORMAL);
        index++;
    }

	if (iBehaviorAbilityType & ADV_REACH_HEIGHT_ABILITY)
    {
        g_StringLanType(szLan, "折线攀高", "ADV Reach height");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_ADV_REACH_HEIGHT);
        index++;
    }
    
	if (iBehaviorAbilityType & TOILET_TARRY_ABILITY)
    {
        g_StringLanType(szLan, "如厕超时", "Toilet tarry");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_TOILET_TARRY);
        index++;
    }

	if (iBehaviorAbilityType & YARD_TARRY_ABILITY)
    {
        g_StringLanType(szLan, "放风场滞留", "Yard tarry");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_YARD_TARRY);
        index++;
    }

	if (iBehaviorAbilityType & ADV_TRAVERSE_PLANE_ABILITY)
	{
		g_StringLanType(szLan, "折线警戒面", "ADV Traverse plane");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_ADV_TRAVERSE_PLANE);
        index++;
	}

    if (iBehaviorAbilityType & OVER_TIME_ABILITY)
    {
        g_StringLanType(szLan, "操作超时", "over time");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_OVER_TIME);
        index++;
    }

    if (iBehaviorAbilityType & HUMAN_ENTER_ABILITY)
    {
        g_StringLanType(szLan, "人员进入", "Human enter");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_HUMAN_ENTER);
        index++;
    }

    if((iBehaviorAbilityType&STICK_UP_ABILITY) != 0)
    {
        g_StringLanType(szLan, "贴纸条", "Stick up");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_STICK_UP);
        index++;
    }
    if ((iBehaviorAbilityType&INSTALL_SCANNER_ABILITY) != 0)
    {
        g_StringLanType(szLan, "安装读卡器", "Install Scanner");
        m_comboRuleType.InsertString(index, szLan);
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_INSTALL_SCANNER);
        index++;
    }

   if((iBehaviorAbilityTypeEx&PEOPLENUM_CHANGE_ABILITY) != 0)
   {
	   g_StringLanType(szLan, "人数变化事件", "People Num Changep");
	   m_comboRuleType.InsertString(index, szLan);
	   m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_PEOPLENUM_CHANGE);
	   index++;
   }

   if ((iBehaviorAbilityTypeEx&SPACING_CHANGE_ABILITY) != 0)
   {
	   g_StringLanType(szLan, "间距变化事件", "Spacing Change");
	   m_comboRuleType.InsertString(index, szLan);
	   m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_SPACING_CHANGE);
	   index++;
    }
    return TRUE;
    
}


/*********************************************************
Function:	InsertRuleID
Desc:	display rule ID in m_comboRuleID
Input:	
Output:	
Return:	BOOL 
**********************************************************/
BOOL CDlgVcaRuleCfg::InitRuleID(int RuleNum)
{
    m_comboRuleID.ResetContent();
    char sbuf[128] = {0};
    for (int i= 0; i < RuleNum; i++)
    {	
        char szLan[128] = {0};
        char sBufCn[128] = {0};
        char sBufEn[128] = {0};
        sprintf(sBufCn, "规则%d", i);
        sprintf(sBufEn, "Rule%d", i);
        g_StringLanType(szLan,sBufCn,sBufEn);
        m_comboRuleID.InsertString(i,szLan);
    }
    return TRUE;
}




/*********************************************************
Function:	OnSelchangeComboRuleId
Desc:		Modify combo for rule ID
Input:	
Output:	
Return:	void
**********************************************************/
void CDlgVcaRuleCfg::OnSelchangeComboRuleId() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_iCurRuleID = m_comboRuleID.GetCurSel();
    memcpy(&m_struOneRule, &m_struRuleCfg.struRule[m_iCurRuleID], sizeof(NET_VCA_ONE_RULE_V41));
    
    SetOneVcaRuleToWnd(m_struOneRule);

    UpdateData(FALSE);
    OnChkRuleActive();

}


/*********************************************************
Function:	ShowRuleTypeWnd
Desc:	According to event type, show or Hide correlative control
Input:	VCA_RULE_EVENT_TYPE_EX struEventType
Output:	
Return:	 BOOL 
**********************************************************/
BOOL CDlgVcaRuleCfg::ShowRuleTypeWnd(VCA_RULE_EVENT_TYPE_EX struEventType)
{
    m_staticAlarmText.SetWindowText("");
    m_staticAlarmArea.SetWindowText("");
    GetDlgItem(IDC_EDIT_ALARM_PERSIST)->SetWindowText("");
    GetDlgItem(IDC_EDIT_ALARM_RATE)->SetWindowText("");
    char szLan[128] = {0};
    GetDlgItem(IDC_EDIT_ALARM_PERSIST)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_EDIT_ALARM_RATE)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_CHK_DRAW_LINE)->ShowWindow(SW_HIDE);
    m_comboAlarmDirect.ShowWindow(SW_HIDE);
    GetDlgItem(IDC_CHK_DRAW_POLYGON)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_SENSITIVE)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_SENSITIVE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_LEAVE_DELAY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_STATIC_DELAY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_LEAVE_DELAY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_STATIC_DELAY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_AUDIO_MODE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO_AUDIO_MODE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_DELAY_TIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_EVENT_DELAY_TIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO_EVENT_PARAM_MODE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_EVENT_PARAM_MODE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_RUN_MODE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO_RUN_MODE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_PERSON_TYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO_PERSONTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_HEIGHT_THRESHOLD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_HEIGHT_THRESHOLD)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATIC_PEOPLENUM_THRESHOLD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_PEOPLENUM_THRESHOLD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_SPACING_THRESHOLD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_SPACING_THRESHOLD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_DETECT_MODE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO_DETECT_MODE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHECK_NONESTATE)->ShowWindow(SW_HIDE);


    if (struEventType == ENUM_VCA_EVENT_TRAVERSE_PLANE || struEventType == ENUM_VCA_EVENT_REACH_HIGHT)
    {
        if (struEventType ==ENUM_VCA_EVENT_TRAVERSE_PLANE )
        {
            g_StringLanType(szLan, "报警方向", "Alarm Direct");
            m_staticAlarmText.SetWindowText(szLan);
            GetDlgItem(IDC_CHK_DRAW_LINE)->ShowWindow(SW_SHOW);
            m_comboAlarmDirect.ShowWindow(SW_SHOW);
        }
        else if (struEventType == ENUM_VCA_EVENT_REACH_HIGHT)
        {
            GetDlgItem(IDC_CHK_DRAW_LINE)->ShowWindow(SW_SHOW);
            g_StringLanType(szLan, "触发时间阈值:", "Trigger time:");
            m_staticAlarmText.SetWindowText(szLan);
//            m_staticAlarmArea.SetWindowText("1-100s");
            GetDlgItem(IDC_EDIT_ALARM_PERSIST)->ShowWindow(SW_SHOW);
        }
		GetDlgItem(IDC_EDIT_LEAVE_DELAY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_STATIC_DELAY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_LEAVE_DELAY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_STATIC_DELAY)->ShowWindow(SW_HIDE);
        m_bDrawLine = FALSE;
        m_bDrawPolygon = FALSE;
        memset(&m_struVcaPolygon[m_iCurRuleID], 0, sizeof(NET_VCA_LINE));
        
		if (struEventType == ENUM_VCA_EVENT_TRAVERSE_PLANE)
		{   
			GetDlgItem(IDC_STATIC_SENSITIVE)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_COMBO_SENSITIVE)->ShowWindow(SW_SHOW);
		}
    }
    else
    {
        GetDlgItem(IDC_CHK_DRAW_POLYGON)->ShowWindow(SW_SHOW);
        m_bDrawLine = FALSE;
        m_bDrawPolygon = FALSE;
        memset(&m_struVcaLine[m_iCurRuleID], 0, sizeof(NET_VCA_LINE));

        if (struEventType == ENUM_VCA_EVENT_ENTER_AREA)
        {
			GetDlgItem(IDC_EDIT_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_STATIC_DELAY)->ShowWindow(SW_HIDE);
        }
        else if (struEventType == ENUM_VCA_EVENT_EXIT_AREA)
        {
			GetDlgItem(IDC_EDIT_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_STATIC_DELAY)->ShowWindow(SW_HIDE);
        }
        else if (struEventType == ENUM_VCA_EVENT_INTRUSION)
        {
            g_StringLanType(szLan, "触发时间阈值:", "Trigger time:");
            m_staticAlarmText.SetWindowText(szLan);
            if (g_struDeviceInfo[m_iDevIndex].iDeviceType == IDS6101_HF_A)
            {
//                m_staticAlarmArea.SetWindowText("1-1200s");
            }
            else
            {
//                m_staticAlarmArea.SetWindowText("1-120s");
            }
            GetDlgItem(IDC_EDIT_ALARM_PERSIST)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_SENSITIVE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_SENSITIVE)->ShowWindow(SW_SHOW);
        }
        else if (struEventType == ENUM_VCA_EVENT_LOITER)
        {
            g_StringLanType(szLan, "触发时间阈值:", "Trigger time:");
            m_staticAlarmText.SetWindowText(szLan);
//            m_staticAlarmArea.SetWindowText("1-120s");
            GetDlgItem(IDC_EDIT_ALARM_PERSIST)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_STATIC_DELAY)->ShowWindow(SW_HIDE);
        }
        else if (struEventType == ENUM_VCA_EVENT_LEFT_TAKE)
        {
            g_StringLanType(szLan, "触发时间阈值:", "Trigger time");
            m_staticAlarmText.SetWindowText(szLan);
//            m_staticAlarmArea.SetWindowText("1-120s");
            GetDlgItem(IDC_EDIT_ALARM_PERSIST)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_STATIC_DELAY)->ShowWindow(SW_HIDE);
        }
        else if (struEventType == ENUM_VCA_EVENT_PARKING)
        {
            g_StringLanType(szLan, "触发时间阈值:", "Trigger time:");
            m_staticAlarmText.SetWindowText(szLan);
//            m_staticAlarmArea.SetWindowText("1-120s");
            GetDlgItem(IDC_EDIT_ALARM_PERSIST)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_STATIC_DELAY)->ShowWindow(SW_HIDE);
        }
        else if (struEventType == ENUM_VCA_EVENT_RUN)
        {
            g_StringLanType(szLan, "快速移动距离:","Run Distance:");
            m_staticAlarmText.SetWindowText(szLan);
            if (0 == m_comboRunMode.GetCurSel())
            {
            //m_staticAlarmArea.SetWindowText("[0.1,1]");
            }
            else if (1 == m_comboRunMode.GetCurSel())
            {
//                m_staticAlarmArea.SetWindowText("[1-20]m/s");
            }
            
            GetDlgItem(IDC_EDIT_ALARM_RATE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_RUN_MODE)->ShowWindow(SW_SHOW);
	        GetDlgItem(IDC_COMBO_RUN_MODE)->ShowWindow(SW_SHOW);
        }
        else if (struEventType == ENUM_VCA_EVENT_HIGH_DENSITY)
        {
            g_StringLanType(szLan, "人员聚集:", "Person density:");
            m_staticAlarmText.SetWindowText(szLan);
//            m_staticAlarmArea.SetWindowText("[0.1,1]");
            GetDlgItem(IDC_EDIT_ALARM_RATE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_STATIC_DELAY)->ShowWindow(SW_HIDE);
        }
        else if (struEventType == ENUM_VCA_EVENT_VIOLENT_MOTION)
        {
            g_StringLanType(szLan, "触发时间阈值:", "Trigger time:");
            m_staticAlarmText.SetWindowText(szLan);
//            m_staticAlarmArea.SetWindowText("1-50s");
            GetDlgItem(IDC_STATIC_SENSITIVE)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_COMBO_SENSITIVE)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_ALARM_PERSIST)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO_EVENT_PARAM_MODE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_EVENT_PARAM_MODE)->ShowWindow(SW_SHOW);

			int nIndex = 0;
			m_comboEventParamMode.ResetContent();
			
			g_StringLanType(szLan, "纯视频","Video");
			m_comboEventParamMode.InsertString(nIndex, szLan);
			m_comboEventParamMode.SetItemData(nIndex, 0);
            nIndex++;
			
			g_StringLanType(szLan, "音视频","Video & Audio");
			m_comboEventParamMode.InsertString(nIndex, szLan);
			m_comboEventParamMode.SetItemData(nIndex, 1);
            nIndex++;

			g_StringLanType(szLan, "纯音频","Audio");
			m_comboEventParamMode.InsertString(nIndex, szLan);
			m_comboEventParamMode.SetItemData(nIndex, 1);
            nIndex++;
        }
        else if (struEventType == ENUM_VCA_EVENT_GET_UP || 
			     struEventType == ENUM_VCA_EVENT_KEY_PERSON_GET_UP)
        {
            g_StringLanType(szLan, "触发时间阈值:", "Trigger time:");
            m_staticAlarmText.SetWindowText(szLan);
//            m_staticAlarmArea.SetWindowText("1-100s");
            GetDlgItem(IDC_EDIT_ALARM_PERSIST)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_COMBO_EVENT_PARAM_MODE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_EVENT_PARAM_MODE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_SENSITIVE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_SENSITIVE)->ShowWindow(SW_SHOW);
			int nIndex = 0;
			m_comboEventParamMode.ResetContent();
			
			g_StringLanType(szLan, "大床通铺模式","Over Bed Mode");
			m_comboEventParamMode.InsertString(nIndex, szLan);
			m_comboEventParamMode.SetItemData(nIndex, 0);
            nIndex++;
			
			g_StringLanType(szLan, "高低铺模式","Area Move Mode");
			m_comboEventParamMode.InsertString(nIndex, szLan);
			m_comboEventParamMode.SetItemData(nIndex, 1);
            nIndex++;

			g_StringLanType(szLan, "坐立起身模式","Sitting Mode");
			m_comboEventParamMode.InsertString(nIndex, szLan);
			m_comboEventParamMode.SetItemData(nIndex, 2);
            nIndex++;
        }
        else if (struEventType == ENUM_VCA_EVENT_LEFT)
        {
            g_StringLanType(szLan, "触发时间阈值:", "Trigger time:");
            m_staticAlarmText.SetWindowText(szLan);
//            m_staticAlarmArea.SetWindowText("4-60s");
            GetDlgItem(IDC_EDIT_ALARM_PERSIST)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_SENSITIVE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_SENSITIVE)->ShowWindow(SW_SHOW);
        }
        else if (struEventType == ENUM_VCA_EVENT_TAKE)
        {
            g_StringLanType(szLan, "触发时间阈值:", "Trigger time:");
            m_staticAlarmText.SetWindowText(szLan);
//            m_staticAlarmArea.SetWindowText("4-60s");
            GetDlgItem(IDC_EDIT_ALARM_PERSIST)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_SENSITIVE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_SENSITIVE)->ShowWindow(SW_SHOW);
        }
		else if (struEventType == ENUM_VCA_EVENT_TRAIL)
        {
            GetDlgItem(IDC_STATIC_SENSITIVE)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_COMBO_SENSITIVE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_ALARM_PERSIST)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_STATIC_DELAY)->ShowWindow(SW_HIDE);
        }
		else if (struEventType == ENUM_VCA_EVENT_STANDUP)
        {
			g_StringLanType(szLan, "触发时间阈值:", "Trigger time:");
            m_staticAlarmText.SetWindowText(szLan);
			//            m_staticAlarmArea.SetWindowText("1-60s");
			GetDlgItem(IDC_EDIT_ALARM_PERSIST)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_STATIC_SENSITIVE)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_COMBO_SENSITIVE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_HEIGHT_THRESHOLD)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_HEIGHT_THRESHOLD)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_STATIC_DELAY)->ShowWindow(SW_HIDE);
        }
		else if (struEventType == ENUM_VCA_EVENT_FALL_DOWN)
        {
			g_StringLanType(szLan, "触发时间阈值:", "Trigger time:");
            m_staticAlarmText.SetWindowText(szLan);
//            m_staticAlarmArea.SetWindowText("1-60s");
			GetDlgItem(IDC_EDIT_ALARM_PERSIST)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_STATIC_SENSITIVE)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_COMBO_SENSITIVE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_HEIGHT_THRESHOLD)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_HEIGHT_THRESHOLD)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_STATIC_DELAY)->ShowWindow(SW_HIDE);
        }
		else if (struEventType == ENUM_VCA_EVENT_PEOPLENUM_CHANGE)
		{
			g_StringLanType(szLan, "触发时间阈值:", "Trigger time:");
			m_staticAlarmText.SetWindowText(szLan);
			//            m_staticAlarmArea.SetWindowText("1-60s");
			m_comDetectMode.ResetContent();
			int nIndex = 0;
			g_StringLanType(szLan, "大于","More than");
			m_comDetectMode.InsertString(nIndex, szLan);
			nIndex++;

			g_StringLanType(szLan, "小于","Less than");
			m_comDetectMode.InsertString(nIndex, szLan);
			nIndex++;

			g_StringLanType(szLan, "等于","equal to");
			m_comDetectMode.InsertString(nIndex, szLan);
			nIndex++;

			g_StringLanType(szLan, "不等于","Not equal to");
			m_comDetectMode.InsertString(nIndex, szLan);
			nIndex++;

			GetDlgItem(IDC_STATIC_PEOPLENUM_THRESHOLD)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_PEOPLENUM_THRESHOLD)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_DETECT_MODE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_DETECT_MODE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_CHECK_NONESTATE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_SENSITIVE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_SENSITIVE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_ALARM_PERSIST)->ShowWindow(SW_SHOW);
        }
		else if (struEventType == ENUM_VCA_EVENT_SPACING_CHANGE)
		{
			g_StringLanType(szLan, "触发时间阈值:", "Trigger time:");
			m_staticAlarmText.SetWindowText(szLan);
			//            m_staticAlarmArea.SetWindowText("1-60s");
			m_comDetectMode.ResetContent();
			int nIndex = 0;
			g_StringLanType(szLan, "大于","More than");
			m_comDetectMode.InsertString(nIndex, szLan);
			nIndex++;
			
			g_StringLanType(szLan, "小于","Less than");
			m_comDetectMode.InsertString(nIndex, szLan);
			nIndex++;
			
			GetDlgItem(IDC_STATIC_SPACING_THRESHOLD)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_SPACING_THRESHOLD)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_DETECT_MODE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_DETECT_MODE)->ShowWindow(SW_SHOW);
	
			GetDlgItem(IDC_STATIC_SENSITIVE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_SENSITIVE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_ALARM_PERSIST)->ShowWindow(SW_SHOW);
        }
		else if (struEventType == ENUM_VCA_EVENT_AUDIO_ABNORMAL)
        {
			g_StringLanType(szLan, "声音强度:", "Decibel:");
            m_staticAlarmText.SetWindowText(szLan);
			//            m_staticAlarmArea.SetWindowText("1-60s");
			GetDlgItem(IDC_EDIT_ALARM_PERSIST)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_STATIC_SENSITIVE)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_COMBO_SENSITIVE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_AUDIO_MODE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_AUDIO_MODE)->ShowWindow(SW_SHOW);
        }
		else if (struEventType == ENUM_VCA_EVENT_ADV_REACH_HEIGHT)
		{
			m_comboAlarmDirect.ShowWindow(SW_SHOW);
		}
		else if (struEventType == ENUM_VCA_EVENT_ADV_TRAVERSE_PLANE)
		{
			m_comboAlarmDirect.ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_SENSITIVE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_SENSITIVE)->ShowWindow(SW_SHOW);
		}
		else if (struEventType == ENUM_VCA_EVENT_TOILET_TARRY)
		{
			GetDlgItem(IDC_STATIC_DELAY_TIME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_EVENT_DELAY_TIME)->ShowWindow(SW_SHOW);
			g_StringLanType(szLan, "如厕超时时间(s)", "Toilet tarry delay time");
			m_staticDelayTime.SetWindowText(szLan);
		}
		else if (struEventType == ENUM_VCA_EVENT_YARD_TARRY)
		{
			GetDlgItem(IDC_STATIC_DELAY_TIME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_EVENT_DELAY_TIME)->ShowWindow(SW_SHOW);
			g_StringLanType(szLan, "放风场滞留时间(s)", "Yard tarry delay time");
			m_staticDelayTime.SetWindowText(szLan);
		}
        else if (struEventType == ENUM_VCA_EVENT_STICK_UP)
        {
            g_StringLanType(szLan, "触发时间阈值:", "Trigger time:");
            m_staticAlarmText.SetWindowText(szLan);
//            m_staticAlarmArea.SetWindowText("4-60s");
            GetDlgItem(IDC_EDIT_ALARM_PERSIST)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_STATIC_SENSITIVE)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_COMBO_SENSITIVE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_STATIC_DELAY)->ShowWindow(SW_HIDE);
        }
        else if (struEventType == ENUM_VCA_EVENT_INSTALL_SCANNER)
        {
            g_StringLanType(szLan, "触发时间阈值:", "Trigger time:");
            m_staticAlarmText.SetWindowText(szLan);
//            m_staticAlarmArea.SetWindowText("4-60s");
            GetDlgItem(IDC_EDIT_ALARM_PERSIST)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_STATIC_SENSITIVE)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_COMBO_SENSITIVE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_STATIC_DELAY)->ShowWindow(SW_HIDE);

        }
        else if (struEventType == ENUM_VCA_EVENT_OVER_TIME)
        {
            g_StringLanType(szLan, "触发时间阈值:", "Trigger time:");
            m_staticAlarmText.SetWindowText(szLan);
//            m_staticAlarmArea.SetWindowText("");
            GetDlgItem(IDC_EDIT_ALARM_PERSIST)->ShowWindow(SW_SHOW);   
			GetDlgItem(IDC_EDIT_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_STATIC_DELAY)->ShowWindow(SW_HIDE);
        }
        else if (struEventType == ENUM_VCA_EVENT_HUMAN_ENTER)
        {
            GetDlgItem(IDC_EDIT_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_STATIC_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_LEAVE_DELAY)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_STATIC_STATIC_DELAY)->ShowWindow(SW_HIDE);
        }
		else if (struEventType == ENUM_VCA_EVENT_LEAVE_POSITION)
		{
			GetDlgItem(IDC_EDIT_ALARM_PERSIST)->ShowWindow(SW_HIDE); 
            GetDlgItem(IDC_STATIC_SENSITIVE)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_COMBO_SENSITIVE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_LEAVE_DELAY)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_STATIC_DELAY)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_LEAVE_DELAY)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_STATIC_DELAY)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_EVENT_PARAM_MODE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_EVENT_PARAM_MODE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_COMBO_PERSONTYPE)->ShowWindow(SW_SHOW);
	    	GetDlgItem(IDC_STATIC_PERSON_TYPE)->ShowWindow(SW_SHOW);
			int nIndex = 0;
			m_comboEventParamMode.ResetContent();
						
			g_StringLanType(szLan, "离岗事件","Leave position event");
			m_comboEventParamMode.InsertString(nIndex, szLan);
			m_comboEventParamMode.SetItemData(nIndex, 0);
            nIndex++;

			g_StringLanType(szLan, "睡岗事件","Sleep position event");
			m_comboEventParamMode.InsertString(nIndex, szLan);
			m_comboEventParamMode.SetItemData(nIndex, 1);
            nIndex++;

			g_StringLanType(szLan, "离岗睡岗事件","Leave&Sleep position event");
			m_comboEventParamMode.InsertString(nIndex, szLan);
			m_comboEventParamMode.SetItemData(nIndex, 2);
            nIndex++;
            
			m_comboPersonType.ResetContent();
			g_StringLanType(szLan, "单人值岗","Single");
			m_comboPersonType.InsertString(0,szLan);
			m_comboPersonType.SetItemData(0,0);

			g_StringLanType(szLan, "双人值岗","Double");
			m_comboPersonType.InsertString(1,szLan);
			m_comboPersonType.SetItemData(1,1);
	    }
        else
        {
            return FALSE;
        }
    }
    return TRUE;	
}

/*********************************************************
Function:	OnChkRuleActive
Desc:		Invalid or not
Input:	
Output:	
Return:	void
**********************************************************/ 
void CDlgVcaRuleCfg::OnChkRuleActive() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    OnSelchangeComboRuleType();
    EnableRuleWindow(m_bRuleActive);
    m_struOneRule.byActive = (unsigned char)m_bRuleActive;
	m_struOneRule.wAlarmDelay = m_comboAlarmDelay.GetCurSel();
}

/*********************************************************
Function:	EnableRuleWindow
Desc:	    
Input:	BOOL bEnable
Output:	
Return:	BOOL
**********************************************************/
BOOL CDlgVcaRuleCfg::EnableRuleWindow(BOOL bEnable)
{
    GetDlgItem(IDC_COMBO_RULE_TYPE)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_RULE_NAME)->EnableWindow(bEnable);
    GetDlgItem(IDC_CHK_DRAW_POLYGON)->EnableWindow(bEnable);
    GetDlgItem(IDC_COMBO_SENSITIVE)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_ALARM_RATE)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_RULE_NAME)->EnableWindow(bEnable);
    GetDlgItem(IDC_COMLINEALARMDIRECT)->EnableWindow(bEnable);
    GetDlgItem(IDC_CHK_DRAW_LINE)->EnableWindow(bEnable);
    
    EnablAlarmTime(bEnable);
    EnableSizeFilter(bEnable);
    EnableHandleException(bEnable);
    return TRUE;
}

BOOL CDlgVcaRuleCfg::EnablAlarmTime(BOOL bEnable)
{
    GetDlgItem(IDC_EDITHOUR11)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITMIN11)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITHOUR12)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITMIN12)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITHOUR21)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITMIN21)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITHOUR22)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITMIN22)->EnableWindow(bEnable);

	GetDlgItem(IDC_EDITHOUR31)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITMIN31)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITHOUR32)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITMIN32)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITHOUR41)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITMIN41)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITHOUR42)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITMIN42)->EnableWindow(bEnable);

	GetDlgItem(IDC_EDITHOUR51)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITMIN51)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITHOUR52)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITMIN52)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITHOUR61)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITMIN61)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITHOUR62)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITMIN62)->EnableWindow(bEnable);

	GetDlgItem(IDC_EDITHOUR71)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITMIN71)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITHOUR72)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITMIN72)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITHOUR81)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITMIN81)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITHOUR82)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDITMIN82)->EnableWindow(bEnable);

    GetDlgItem(IDC_COMBOWEEKDAY)->EnableWindow(bEnable);
    GetDlgItem(IDC_COMBOCOPYTIME)->EnableWindow(bEnable);
    GetDlgItem(IDC_TIME_COPY)->EnableWindow(bEnable);
    GetDlgItem(IDC_TIME_OK)->EnableWindow(bEnable);
    return TRUE;
}

BOOL CDlgVcaRuleCfg::EnableHandleException(BOOL bEnable)
{
    GetDlgItem(IDC_CHECKHANDLETYPE1)->EnableWindow(bEnable);
    GetDlgItem(IDC_CHECKHANDLETYPE2)->EnableWindow(bEnable);
    GetDlgItem(IDC_CHECKHANDLETYPE3)->EnableWindow(bEnable);
    GetDlgItem(IDC_CHECKHANDLETYPE4)->EnableWindow(bEnable);
    GetDlgItem(IDC_CHECKHANDLETYPE5)->EnableWindow(bEnable);
//    GetDlgItem(IDC_LIST_ALARM_OUT)->EnableWindow(bEnable & m_bHandleType4);
	GetDlgItem(IDC_TREE_ALARM_OUT_RELATE)->EnableWindow(bEnable & m_bHandleType4);
    GetDlgItem(IDC_LIST_RECORD_CHAN)->EnableWindow(bEnable);
    return TRUE;
}

BOOL CDlgVcaRuleCfg::EnableSizeFilter(BOOL bEnable)
{
    GetDlgItem(IDC_CHECK_FILTER_ACTIVE)->EnableWindow(bEnable);
    GetDlgItem(IDC_CHECK_SET_MINI_FILTER)->EnableWindow(bEnable & m_bFilterActive);
    GetDlgItem(IDC_CHECK_SET_MAX_FILTER)->EnableWindow(bEnable & m_bFilterActive);
    return TRUE;
}

/*********************************************************
Function:	OnSelchangeComboRuleType
Desc:		Modify Rule Type 
Input:	
Output:	
Return:	void
**********************************************************/
void CDlgVcaRuleCfg::OnSelchangeComboRuleType() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    VCA_RULE_EVENT_TYPE_EX eEventType;
    
    eEventType = (VCA_RULE_EVENT_TYPE_EX)GetEventTypeFromWnd();
	m_dwEventType = eEventType;
    ShowRuleTypeWnd(eEventType);
    if (eEventType == m_struRuleCfg.struRule[m_iCurRuleID].wEventTypeEx)
    {
        SetEventUnionToWnd(m_struRuleCfg.struRule[m_iCurRuleID].uEventParam, eEventType);
    }
    else
    {
        NET_VCA_EVENT_UNION uEventParam;
        memset(&uEventParam, 0, sizeof(NET_VCA_EVENT_UNION));
        SetEventUnionToWnd(uEventParam, eEventType);
    }
    m_struOneRule.wEventTypeEx = eEventType; 
    UpdateData(FALSE);
}



/*********************************************************
Function:	F_DrawFun
Desc:		Draw
Input:	lPlayHandle, player handle
hDc : DC handle
dwUser: User data to distinguish different channels
Output:	
Return:	void
**********************************************************/
void CDlgVcaRuleCfg::F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser)
{
    COLORREF color;
    color = RGB(255, 255, 0);//Yellow
    if(	m_struOneRule.wEventTypeEx== ENUM_VCA_EVENT_ENTER_AREA
        || m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_EXIT_AREA
        || m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_INTRUSION
        || m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_LOITER
        || m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_LEFT_TAKE
        || m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_PARKING
        || m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_RUN
        || m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_HIGH_DENSITY
        || m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_VIOLENT_MOTION
        /*|| m_struVcaRuleCfg.struRule[m_iCurRuleID].dwEventType == VCA_REACH_HIGHT*/
        || m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_GET_UP
		|| m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_KEY_PERSON_GET_UP
        || m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_LEFT
        || m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_TAKE
        || m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_OVER_TIME
        || m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_STICK_UP
        || m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_INSTALL_SCANNER
		|| m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_LEAVE_POSITION
		|| m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_TRAIL
		|| m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_FALL_DOWN
		|| m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_ADV_REACH_HEIGHT
		|| m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_TOILET_TARRY
		|| m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_YARD_TARRY
		|| m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_ADV_TRAVERSE_PLANE
		|| m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_STANDUP
		|| m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_PEOPLENUM_CHANGE
		|| m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_SPACING_CHANGE
        )
    {
        F_DrawFrame(hDc);
    }
    else if (m_struOneRule.wEventTypeEx == VCA_TRAVERSE_PLANE
        || m_struOneRule.wEventTypeEx == VCA_REACH_HIGHT)
    {
        F_DrawLine(hDc);
    }
    
    F_DrawFilter(hDc);
}

/*********************************************************
Function:	F_DrawFrame
Desc:	
Input:	
hDc : DC handle
Output:	
Return:	 void
**********************************************************/
void CDlgVcaRuleCfg::F_DrawFrame(HDC hDc)
{
    DRAW_POLYGON_PARAM struPolygonParam;
    memset(&struPolygonParam, 0, sizeof(struPolygonParam));
    struPolygonParam.color = RGB(255, 255, 0);
    memcpy(&struPolygonParam.rcWnd, &m_rcWnd, sizeof(m_rcWnd));
    memcpy(&struPolygonParam.struVcaPolygon, &m_struVcaPolygon[m_iCurRuleID], sizeof(struPolygonParam.struVcaPolygon));
    struPolygonParam.bCloseIn = m_bCloseIn[m_iCurRuleID];
    struPolygonParam.bMouseMove = m_bMouseMove[m_iCurRuleID];
    
    CDrawFun::DrawVcaPolygon(hDc, &struPolygonParam);
}

/*********************************************************
Function:	F_DrawFilter
Desc:	Rule filter
Input:
hDc :DC handle
Output:	
Return:	 void
**********************************************************/
void CDlgVcaRuleCfg::F_DrawFilter(HDC hDc)
{
    if (m_bFilterActive)
    {
        DRAW_RECT_PARAM struDrawRect;
        memset(&struDrawRect, 0, sizeof(struDrawRect));
        struDrawRect.color = RGB(0, 255, 125);
        memcpy(&struDrawRect.rcWnd, &m_rcWnd, sizeof(struDrawRect.rcWnd));
        memcpy(&struDrawRect.struVcaRect, &m_struSizeFilter.struMaxRect, sizeof(struDrawRect.struVcaRect));
        CDrawFun::DrawVcaRect(hDc, &struDrawRect);
        
        memset(&struDrawRect, 0, sizeof(struDrawRect));
        struDrawRect.color = RGB(0, 255, 125);
        memcpy(&struDrawRect.rcWnd, &m_rcWnd, sizeof(struDrawRect.rcWnd));
        memcpy(&struDrawRect.struVcaRect, &m_struSizeFilter.struMiniRect, sizeof(struDrawRect.struVcaRect));
        CDrawFun::DrawVcaRect(hDc, &struDrawRect);
    }
}


/*********************************************************
Function:	F_DrawLine
Desc:	
Input:	
HDC hDc

  Output:	
  Return:	void 
**********************************************************/
void CDlgVcaRuleCfg::F_DrawLine(HDC hDc)
{
    DRAW_TRAVERSE_PLANE_PARAM struTraversePlane;
    memset(&struTraversePlane, 0, sizeof(struTraversePlane));
    struTraversePlane.color = RGB(255, 255, 0);
    memcpy(&struTraversePlane.rcWnd, m_rcWnd, sizeof(struTraversePlane.rcWnd));
    memcpy(&struTraversePlane.struVcaLine, &m_struVcaLine[m_iCurRuleID], sizeof(struTraversePlane.struVcaLine));
    struTraversePlane.dwCrossDirection = m_struOneRule.uEventParam.struTraversePlane.dwCrossDirection;
    CDrawFun::DrawTraversePlane(hDc, &struTraversePlane);
}

/*********************************************************
Function:	OnChkDrawPolygon
Desc:		Draw Polygon or not. 
Input:	
Output:	
Return:	void 
**********************************************************/
void CDlgVcaRuleCfg::OnChkDrawPolygon() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if(m_bDrawPolygon)
    {
        m_bNeedRedraw[m_iCurRuleID] = TRUE;//Draw polygon
        m_bSetMaxFilter = FALSE;//While drawing polygon, can't draw filter
        m_bSetMiniFilter = FALSE;
        
    }
    else
    {
        if (m_bNeedRedraw[m_iCurRuleID] && !m_bCloseIn[m_iCurRuleID])
        {
            if (m_bMouseMove[m_iCurRuleID])
            {
                m_bMouseMove[m_iCurRuleID] = FALSE;
                m_struVcaPolygon[m_iCurRuleID].dwPointNum--;
            }
            m_bCloseIn[m_iCurRuleID] = TRUE;
        }		
    }	
    UpdateData(FALSE);
    
}

/*********************************************************
Function:	OnCheckFilterActive
Desc:		Check if the size filter is valid
Input:	
Output:	
Return:	void 
**********************************************************/
void CDlgVcaRuleCfg::OnCheckFilterActive() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    GetDlgItem(IDC_CHECK_SET_MAX_FILTER)->EnableWindow(m_bFilterActive);
    GetDlgItem(IDC_CHECK_SET_MINI_FILTER)->EnableWindow(m_bFilterActive);
}

/*********************************************************
Function:	OnCheckSetMiniFilter
Desc:		Set the minimal filter area
Input:	
Output:	
Return:	void 
**********************************************************/
void CDlgVcaRuleCfg::OnCheckSetMiniFilter() 
{
    // TODO: Add your control notification handler code here
    if (m_lPlayHandle < 0)
    {
        return;
    }
    UpdateData(TRUE);
    if (m_bSetMiniFilter)
    {
        m_bSetMaxFilter = FALSE;
        m_bDrawPolygon = FALSE;
        m_bDrawLine	= FALSE;
        UpdateData(FALSE);
    }
}

/*********************************************************
Function:	OnCheckSetMaxFilter
Desc:		Set the maximal filter area.
Input:	
Output:	
Return:	void 
**********************************************************/
void CDlgVcaRuleCfg::OnCheckSetMaxFilter() 
{
    // TODO: Add your control notification handler code here
    if (m_lPlayHandle < 0)
    {
        return;
    }
    UpdateData(TRUE);
    if (m_bSetMaxFilter)
    {
        m_bSetMiniFilter = FALSE;
        m_bDrawPolygon = FALSE;
        m_bDrawLine = FALSE;
        UpdateData(FALSE);
    }
}

/*********************************************************
Function:	OnChkDrawLine
Desc:		Check control for Drawing line
Input:	
Output:	
Return: void 	
**********************************************************/
void CDlgVcaRuleCfg::OnChkDrawLine() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if(m_bDrawLine)//drawing
    {
        if (m_bMouseMove[m_iCurRuleID])
        {
            m_bMouseMove[m_iCurRuleID] = FALSE;
        }
        m_bSetMaxFilter = FALSE;
        m_bSetMiniFilter = FALSE;
        UpdateData(FALSE);
    }
    else
    {
        m_bMouseMove[m_iCurRuleID] = TRUE;
    }	
    
}

/*********************************************************
Function:	OnSelchangeComlinealarmdirect
Desc:		Modify the way to cross the alarm plane
Input:	
Output:	
Return:	void 	
**********************************************************/
void CDlgVcaRuleCfg::OnSelchangeComlinealarmdirect() 
{
    VCA_CROSS_DIRECTION iDirect;
    iDirect = (VCA_CROSS_DIRECTION)m_comboAlarmDirect.GetCurSel();
	if (m_dwEventType == ENUM_VCA_EVENT_TRAVERSE_PLANE)
	{
		m_struOneRule.uEventParam.struTraversePlane.dwCrossDirection = iDirect;
	}
    else if (m_dwEventType == ENUM_VCA_EVENT_ADV_REACH_HEIGHT)
    {
		m_struOneRule.uEventParam.struReachHeight.dwCrossDirection = iDirect;
    }
	else if (m_dwEventType == ENUM_VCA_EVENT_ADV_TRAVERSE_PLANE)
	{
		m_struOneRule.uEventParam.struAdvTraversePlane.dwCrossDirection = iDirect;
	}
}


/*********************************************************
Function:	OnTimeOk
Desc:		
Input:	
Output:	
Return:	void 
**********************************************************/
void CDlgVcaRuleCfg::OnTimeOk() 
{
    UpdateData(TRUE);
    if (!F_TimeTest())
    {
        return;
    }
    int	i = m_comboWeekday.GetCurSel();	
    GetAlarmTimeFromWnd(&m_struRuleCfg.struRule[m_iCurRuleID].struAlarmTime[0][0], i);

}
/*********************************************************
Function:	OnTimeCopy
Desc:		
Input:	
Output:	
Return:	void 
**********************************************************/
void CDlgVcaRuleCfg::OnTimeCopy() 
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
                memcpy(&(m_struRuleCfg.struRule[m_iCurRuleID].struAlarmTime[j][k]), &(m_struRuleCfg.struRule[m_iCurRuleID].struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
            }
        }
    }
    else
    {
        for(k=0; k<MAX_TIMESEGMENT_V30/*MAX_TIMESEGMENT_2*/; k++)
        {
            memcpy(&(m_struRuleCfg.struRule[m_iCurRuleID].struAlarmTime[m_nCopyTime][k]), &(m_struRuleCfg.struRule[m_iCurRuleID].struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
        }
    }
    
}

/*********************************************************
Function:	F_TimeTest
Desc:		Check Fortify time
Input:	
Output:	
Return:	BOOL
**********************************************************/
BOOL CDlgVcaRuleCfg::F_TimeTest()
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

/*********************************************************
Function:	OnSelchangeComboweekday
Desc:		
Input:	
Output:	
Return:	void 
**********************************************************/
void CDlgVcaRuleCfg::OnSelchangeComboweekday() 
{
    // TODO: Add your control notification handler code here
    int	i = m_comboWeekday.GetCurSel();	
    SetAlarmTimeToWnd(&m_struRuleCfg.struRule[m_iCurRuleID].struAlarmTime[0][0], i);
    UpdateData(FALSE);
}

/*********************************************************
Function:	OnCheckhandletype4
Desc:		
Input:	
Output:	
Return:	void 
**********************************************************/
void CDlgVcaRuleCfg::OnCheckhandletype4() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_treeAlarmOut.EnableWindow(m_bHandleType4);
}

/*********************************************************
Function:	OnChangeEditRuleName
Desc:		Modify rule name
Input:	
Output:	
Return:	void 
**********************************************************/
void CDlgVcaRuleCfg::OnChangeEditRuleName() 
{
    // TODO: If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.
    
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    memset(&m_struOneRule.byRuleName[0], 0, sizeof(BYTE)*NAME_LEN);
    strncpy((char*)&m_struOneRule.byRuleName[0], m_csRuleName.GetBuffer(0), (NAME_LEN - 1));
}

void CDlgVcaRuleCfg::SetVcaRuleToWnd(NET_VCA_RULECFG_V41 const &struVcaRuleCfg)
{
    m_comboProPicType.SetCurSel(struVcaRuleCfg.byPicProType);
	m_cmUpLastAlarm.SetCurSel(struVcaRuleCfg.byUpLastAlarm);
	m_bChkPicRecordEn = struVcaRuleCfg.byPicRecordEnable;
    m_comboResolution.SetCurSel(struVcaRuleCfg.struPictureParam.wPicSize);
    m_comboPicQuality.SetCurSel(struVcaRuleCfg.struPictureParam.wPicQuality);

	for (int i = 0; i < g_struDeviceInfo[m_iDevIndex].iDeviceChanNum; i++)
	{
		if (m_comboRelSnapChan1.GetItemData(i) == struVcaRuleCfg.wRelSnapChan[0])
		{
			m_comboRelSnapChan1.SetCurSel(i);
		}
		if (m_comboRelSnapChan2.GetItemData(i) == struVcaRuleCfg.wRelSnapChan[1])
		{
			m_comboRelSnapChan2.SetCurSel(i);
		}
		if (m_comboRelSnapChan3.GetItemData(i) == struVcaRuleCfg.wRelSnapChan[2])
		{
			m_comboRelSnapChan3.SetCurSel(i);
		}
	}
    
    SetOneVcaRuleToWnd(struVcaRuleCfg.struRule[m_comboRuleID.GetCurSel()]);
}

void CDlgVcaRuleCfg::GetVcaRuleFromWnd(NET_VCA_RULECFG_V41 &struVcaRuleCfg)
{

}

void CDlgVcaRuleCfg::SetOneVcaRuleToWnd(NET_VCA_ONE_RULE_V41 const &struVcaOneRule)
{
    m_bRuleActive = struVcaOneRule.byActive;
    m_csRuleName = struVcaOneRule.byRuleName;
	m_comboAlarmDelay.SetCurSel(struVcaOneRule.wAlarmDelay);
    SetEventTypeToWnd(struVcaOneRule.wEventTypeEx);
    SetEventUnionToWnd(struVcaOneRule.uEventParam, struVcaOneRule.wEventTypeEx);
    SetSizeFilterToWnd(struVcaOneRule.struSizeFilter);
    int nDay = m_comboWeekday.GetCurSel();
    SetAlarmTimeToWnd(&struVcaOneRule.struAlarmTime[0][0], nDay);
    SetHandleExceptionToWnd(struVcaOneRule.struHandleType);
    SetRelRecordChanToWnd(struVcaOneRule.byRelRecordChan, g_struDeviceInfo[m_iDevIndex].iDeviceChanNum);
    m_treeAlarmOut.EnableWindow((struVcaOneRule.struHandleType.dwHandleType>>3)&0x01);
	SetFilterStrategyToWnd(struVcaOneRule.struFilterStrategy);
	SetRuleTriggerParamToWnd(struVcaOneRule.struTriggerParam);
}

void CDlgVcaRuleCfg::GetOneVcaRuleFromWnd(NET_VCA_ONE_RULE_V41 &struOneRule)
{   
    struOneRule.byActive = m_bRuleActive;
	struOneRule.wAlarmDelay = m_comboAlarmDelay.GetCurSel();
    strncpy((char*)struOneRule.byRuleName, m_csRuleName.GetBuffer(0), sizeof(struOneRule.byRuleName));
    struOneRule.wEventTypeEx = GetEventTypeFromWnd();
    GetEventUnionFromWnd(struOneRule.uEventParam, struOneRule.wEventTypeEx);
    GetSizeFilterFromWnd(struOneRule.struSizeFilter);
    GetAlarmTimeFromWnd(&struOneRule.struAlarmTime[0][0], m_comboWeekday.GetCurSel());
    GetHandleExceptionFromWnd(struOneRule.struHandleType);
    GetRelRecordChanFromWnd(struOneRule.byRelRecordChan, g_struDeviceInfo[m_iDevIndex].iDeviceChanNum);
	GetFilterStrategyFromWnd(&struOneRule.struFilterStrategy);
	GetRuleTriggerParamFromWnd(&struOneRule.struTriggerParam);
	struOneRule.byEventTypeFlag = 1;
}

void CDlgVcaRuleCfg::SetEventTypeToWnd(DWORD dwEventType)
{
    for (int i = 0; i < m_comboRuleType.GetCount(); i++)
    {
        if (dwEventType == m_comboRuleType.GetItemData(i))
        {
            m_comboRuleType.SetCurSel(i);
            break;
        }
    }
}

DWORD CDlgVcaRuleCfg::GetEventTypeFromWnd()
{
    return m_comboRuleType.GetItemData(m_comboRuleType.GetCurSel());
}

void CDlgVcaRuleCfg::SetEventUnionToWnd(NET_VCA_EVENT_UNION const & uEventParam, DWORD dwEventType)
{
    BYTE bySensitivity = 0;
	int i;
    switch (dwEventType)
    {
    case ENUM_VCA_EVENT_TRAVERSE_PLANE:
        m_comboAlarmDirect.SetCurSel(uEventParam.struTraversePlane.dwCrossDirection);
        OnSelchangeComlinealarmdirect();
        memcpy(&m_struVcaLine[m_iCurRuleID], &uEventParam.struTraversePlane.struPlaneBottom, sizeof(NET_VCA_LINE));
		bySensitivity = uEventParam.struTraversePlane.bySensitivity;
        break;
    case ENUM_VCA_EVENT_ENTER_AREA:
        memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struArea.struRegion, sizeof(NET_VCA_POLYGON));
        break;
    case ENUM_VCA_EVENT_EXIT_AREA:
        memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struArea.struRegion, sizeof(NET_VCA_POLYGON));
        break;
    case ENUM_VCA_EVENT_INTRUSION:
        memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struIntrusion.struRegion, sizeof(NET_VCA_POLYGON));
        m_iAlarmPersist = uEventParam.struIntrusion.wDuration;
	    bySensitivity = uEventParam.struIntrusion.bySensitivity;
        break;
    case ENUM_VCA_EVENT_LOITER:
        memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struLoiter.struRegion, sizeof(NET_VCA_POLYGON));
        m_iAlarmPersist	= uEventParam.struLoiter.wDuration;
        break;
    case ENUM_VCA_EVENT_LEFT_TAKE:
        memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struTakeTeft.struRegion, sizeof(NET_VCA_POLYGON));
        m_iAlarmPersist	= uEventParam.struTakeTeft.wDuration;
        break;
    case ENUM_VCA_EVENT_PARKING:
        memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struParking.struRegion, sizeof(NET_VCA_POLYGON));
        m_iAlarmPersist	= uEventParam.struParking.wDuration;
        break;
    case ENUM_VCA_EVENT_RUN:
        memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struRun.struRegion, sizeof(NET_VCA_POLYGON));
        m_fAlarmRate = uEventParam.struRun.fRunDistance;
        m_comboRunMode.SetCurSel(uEventParam.struRun.byMode);
        break;
    case ENUM_VCA_EVENT_HIGH_DENSITY:
        memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struHighDensity.struRegion, sizeof(NET_VCA_POLYGON));
        m_fAlarmRate = uEventParam.struHighDensity.fDensity;
        break;
    case ENUM_VCA_EVENT_GET_UP:
	case ENUM_VCA_EVENT_KEY_PERSON_GET_UP:
        //emcpy(&m_struVcaLine[m_iCurRuleID], &)
        memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struGetUp.struRegion, sizeof(NET_VCA_POLYGON));
        m_iAlarmPersist = uEventParam.struGetUp.wDuration;
		for (i =0; i < m_comboEventParamMode.GetCount(); i++)
		{
			if (uEventParam.struGetUp.byMode == m_comboEventParamMode.GetItemData(i))
			{
				m_comboEventParamMode.SetCurSel(i);
				break;
			}
		}
		bySensitivity = uEventParam.struGetUp.bySensitivity;
        break;
    case ENUM_VCA_EVENT_VIOLENT_MOTION:
        memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struViolentMotion.struRegion, sizeof(NET_VCA_POLYGON));
        m_iAlarmPersist = uEventParam.struViolentMotion.wDuration;
        bySensitivity = uEventParam.struViolentMotion.bySensitivity;

		for (i =0; i < m_comboEventParamMode.GetCount(); i++)
		{
			if (uEventParam.struViolentMotion.byMode == m_comboEventParamMode.GetItemData(i))
			{
				m_comboEventParamMode.SetCurSel(i);
				break;
			}
		}
        break;
    case ENUM_VCA_EVENT_REACH_HIGHT:
        memcpy(&m_struVcaLine[m_iCurRuleID], &uEventParam.struReachHight.struVcaLine, sizeof(NET_VCA_LINE));
        m_iAlarmPersist = uEventParam.struReachHight.wDuration;
        break;
    case ENUM_VCA_EVENT_LEFT:
        memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struLeft.struRegion, sizeof(NET_VCA_POLYGON));
        m_iAlarmPersist = uEventParam.struLeft.wDuration;
		bySensitivity = uEventParam.struLeft.bySensitivity;
        break;
    case ENUM_VCA_EVENT_TAKE:
        memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struTake.struRegion, sizeof(NET_VCA_POLYGON));
        m_iAlarmPersist = uEventParam.struTake.wDuration;
		bySensitivity = uEventParam.struTake.bySensitivity;
        break;

    case ENUM_VCA_EVENT_OVER_TIME:
//         NET_VCA_POLYGON     struRegion;    // 区域范围
//         HPR_UINT16  wDuration;  // 操作报警时间阈值
//         HPR_UINT8   byRes[6];   // 保留字节
//     }NET_VCA_OVER_TIME, *LPNET_VCA_OVER_TIME;
        memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struOvertime.struRegion, sizeof(NET_VCA_POLYGON));
        m_iAlarmPersist = uEventParam.struOvertime.wDuration;
        break;
    case ENUM_VCA_EVENT_STICK_UP:
        memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struStickUp.struRegion, sizeof(NET_VCA_POLYGON));
        m_iAlarmPersist = uEventParam.struStickUp.wDuration;
        bySensitivity = uEventParam.struStickUp.bySensitivity;
        break;
    case ENUM_VCA_EVENT_INSTALL_SCANNER:
        memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struScanner.struRegion, sizeof(NET_VCA_POLYGON));
        m_iAlarmPersist	 = uEventParam.struScanner.wDuration;
        bySensitivity = uEventParam.struScanner.bySensitivity;
        break;
	case ENUM_VCA_EVENT_LEAVE_POSITION:
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struLeavePos.struRegion, sizeof(NET_VCA_POLYGON));
		m_dwLeaveDelay = uEventParam.struLeavePos.wLeaveDelay;
		m_dwStaticDelay = uEventParam.struLeavePos.wStaticDelay;
		for (i =0; i < m_comboEventParamMode.GetCount(); i++)
		{
			if (uEventParam.struLeavePos.byMode == m_comboEventParamMode.GetItemData(i))
			{
				m_comboEventParamMode.SetCurSel(i);
				break;
			}
		}
		for (i = 0; i < m_comboPersonType.GetCount(); i++)
		{
			if (uEventParam.struLeavePos.byPersonType == m_comboPersonType.GetItemData(i))
			{
				m_comboPersonType.SetCurSel(i);
				break;
			}
		}
        bySensitivity = uEventParam.struLeavePos.bySensitivity;
		break;
	case ENUM_VCA_EVENT_TRAIL:
        memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struTrail.struRegion, sizeof(NET_VCA_POLYGON));
		bySensitivity = uEventParam.struTrail.bySensitivity;
		break;
	case ENUM_VCA_EVENT_FALL_DOWN:
        memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struFallDown.struRegion, sizeof(NET_VCA_POLYGON));
		bySensitivity = uEventParam.struFallDown.bySensitivity;
		m_iAlarmPersist = uEventParam.struFallDown.wDuration;
		m_byHeightThreshold = uEventParam.struFallDown.byHeightThreshold;
		break;
	case ENUM_VCA_EVENT_STANDUP:
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struStandUp.struRegion, sizeof(NET_VCA_POLYGON));
		bySensitivity = uEventParam.struStandUp.bySensitivity;
		m_iAlarmPersist = uEventParam.struStandUp.wDuration;
		m_byHeightThreshold = uEventParam.struStandUp.byHeightThreshold;
		break;
	case ENUM_VCA_EVENT_PEOPLENUM_CHANGE:
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struPeopleNumChange.struRegion, sizeof(NET_VCA_POLYGON));
		bySensitivity = uEventParam.struPeopleNumChange.bySensitivity;
		m_byPeopleNumThreshold = uEventParam.struPeopleNumChange.byPeopleNumThreshold;
		m_comDetectMode.SetCurSel(uEventParam.struPeopleNumChange.byDetectMode - 1);
		m_bNoneStateEffective = uEventParam.struPeopleNumChange.byNoneStateEffective;
		m_iAlarmPersist = uEventParam.struPeopleNumChange.wDuration;
		break;
	case ENUM_VCA_EVENT_SPACING_CHANGE:
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struSpacingChange.struRegion, sizeof(NET_VCA_POLYGON));
		bySensitivity = uEventParam.struSpacingChange.bySensitivity;
		m_comDetectMode.SetCurSel(uEventParam.struSpacingChange.byDetectMode - 1);
		m_fSpacingThreshold = uEventParam.struSpacingChange.fSpacingThreshold;
		m_iAlarmPersist = uEventParam.struSpacingChange.wDuration;
		break;
	case ENUM_VCA_EVENT_AUDIO_ABNORMAL:
		bySensitivity = uEventParam.struAudioAbnormal.bySensitivity;
		m_iAlarmPersist = uEventParam.struAudioAbnormal.wDecibel;
		m_comboAudioMode.SetCurSel(uEventParam.struAudioAbnormal.byAudioMode);
        break;
	case ENUM_VCA_EVENT_ADV_REACH_HEIGHT:
		m_comboAlarmDirect.SetCurSel(uEventParam.struReachHeight.dwCrossDirection);
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struReachHeight.struRegion, sizeof(NET_VCA_POLYGON));
		break;
	case ENUM_VCA_EVENT_TOILET_TARRY:
		m_dwEventDelayTime = uEventParam.struToiletTarry.wDelay;
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struToiletTarry.struRegion, sizeof(NET_VCA_POLYGON));
		break;
	case ENUM_VCA_EVENT_YARD_TARRY:
		m_dwEventDelayTime = uEventParam.struYardTarry.wDelay;
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struYardTarry.struRegion, sizeof(NET_VCA_POLYGON));
		break;
	case ENUM_VCA_EVENT_ADV_TRAVERSE_PLANE:
		m_comboAlarmDirect.SetCurSel(uEventParam.struAdvTraversePlane.dwCrossDirection);
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struAdvTraversePlane.struRegion, sizeof(NET_VCA_POLYGON));
		bySensitivity = uEventParam.struAdvTraversePlane.bySensitivity;
		break;
    default:
        break;
    }
    if (bySensitivity < 1)
    {
        bySensitivity = 0;
    }
    else
    {
        bySensitivity = (unsigned char)(bySensitivity - 1);
    }
    m_comboSensitive.SetCurSel(bySensitivity);
    m_dwPosNum = m_struVcaPolygon[m_iCurRuleID].dwPointNum;

}

void CDlgVcaRuleCfg::GetEventUnionFromWnd(NET_VCA_EVENT_UNION &uEventParam, DWORD dwEventType)
{
	UpdateData(TRUE);
    BYTE bySensity = 0;
    switch (dwEventType)
    {
    case ENUM_VCA_EVENT_TRAVERSE_PLANE:
        memcpy(&uEventParam.struTraversePlane.struPlaneBottom, &m_struVcaLine[m_iCurRuleID], sizeof(NET_VCA_LINE));
        uEventParam.struTraversePlane.dwCrossDirection = (VCA_CROSS_DIRECTION)m_comboAlarmDirect.GetCurSel();
		uEventParam.struTraversePlane.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
        break;
    case ENUM_VCA_EVENT_ENTER_AREA:
        memcpy(&uEventParam.struArea.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        break;
    case ENUM_VCA_EVENT_EXIT_AREA:
        memcpy(&uEventParam.struArea.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        break;
    case ENUM_VCA_EVENT_INTRUSION:
        uEventParam.struIntrusion.wDuration = (WORD)m_iAlarmPersist;
        memcpy(&uEventParam.struIntrusion.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
		uEventParam.struIntrusion.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
        break;
    case ENUM_VCA_EVENT_LOITER:
        uEventParam.struLoiter.wDuration = (WORD)m_iAlarmPersist;
        memcpy(&uEventParam.struLoiter.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        break;
    case ENUM_VCA_EVENT_LEFT_TAKE:
        uEventParam.struTakeTeft.wDuration = (WORD)m_iAlarmPersist;
        memcpy(&uEventParam.struTakeTeft.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        break;
    case ENUM_VCA_EVENT_PARKING:
        uEventParam.struParking.wDuration = (WORD)m_iAlarmPersist;
        memcpy(&uEventParam.struParking.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        break;
    case ENUM_VCA_EVENT_RUN:
        uEventParam.struRun.fRunDistance = m_fAlarmRate;
        memcpy(&uEventParam.struRun.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        uEventParam.struRun.byMode = m_comboRunMode.GetCurSel();
        break;
    case ENUM_VCA_EVENT_HIGH_DENSITY:
        uEventParam.struHighDensity.fDensity = m_fAlarmRate;
        memcpy(&uEventParam.struHighDensity.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        break;
    case ENUM_VCA_EVENT_VIOLENT_MOTION:
        uEventParam.struViolentMotion.wDuration = m_iAlarmPersist;
        memcpy(&uEventParam.struViolentMotion.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        uEventParam.struViolentMotion.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel() +1);
		uEventParam.struViolentMotion.byMode = m_comboEventParamMode.GetItemData(m_comboEventParamMode.GetCurSel());
        break;
    case ENUM_VCA_EVENT_REACH_HIGHT:
        uEventParam.struReachHight.wDuration = m_iAlarmPersist;
        memcpy(&uEventParam.struReachHight.struVcaLine, &m_struVcaLine[m_iCurRuleID], sizeof(NET_VCA_LINE));
        break;
    case ENUM_VCA_EVENT_GET_UP:
	case ENUM_VCA_EVENT_KEY_PERSON_GET_UP:
        uEventParam.struGetUp.wDuration = m_iAlarmPersist;
        memcpy(&uEventParam.struGetUp.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
		uEventParam.struGetUp.byMode = m_comboEventParamMode.GetItemData(m_comboEventParamMode.GetCurSel());
		uEventParam.struGetUp.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
        break;
    case ENUM_VCA_EVENT_LEFT:
        uEventParam.struLeft.wDuration = m_iAlarmPersist;
        memcpy(&uEventParam.struLeft.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
		uEventParam.struLeft.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
        break;
    case ENUM_VCA_EVENT_TAKE:
        uEventParam.struTake.wDuration = m_iAlarmPersist;
        memcpy(&uEventParam.struTake.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
		uEventParam.struTake.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
        break;
    case ENUM_VCA_EVENT_OVER_TIME:
        memcpy(&uEventParam.struOvertime.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        uEventParam.struOvertime.wDuration = (WORD)m_iAlarmPersist;
        break;
    case ENUM_VCA_EVENT_STICK_UP:
        memcpy(&uEventParam.struStickUp.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        uEventParam.struStickUp.wDuration = (WORD)m_iAlarmPersist;
        uEventParam.struStickUp.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
        break;
    case ENUM_VCA_EVENT_INSTALL_SCANNER:
        memcpy(&uEventParam.struScanner.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        uEventParam.struScanner.wDuration = (WORD)m_iAlarmPersist;
        uEventParam.struScanner.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
        break;
	case ENUM_VCA_EVENT_LEAVE_POSITION:
        memcpy(&uEventParam.struLeavePos.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
		uEventParam.struLeavePos.wLeaveDelay = m_dwLeaveDelay;
		uEventParam.struLeavePos.wStaticDelay = m_dwStaticDelay;
		uEventParam.struLeavePos.byMode = m_comboEventParamMode.GetItemData(m_comboEventParamMode.GetCurSel());
		uEventParam.struLeavePos.byPersonType = m_comboPersonType.GetItemData(m_comboPersonType.GetCurSel());
        bySensity = (BYTE)(m_comboSensitive.GetCurSel() + 1);
        if (bySensity >= 5)
        {
            bySensity = 5;
        }
        uEventParam.struLeavePos.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel() + 1);
		break;
	case ENUM_VCA_EVENT_TRAIL:
		uEventParam.struTrail.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
		memcpy(&uEventParam.struTrail.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
		break;
	case ENUM_VCA_EVENT_FALL_DOWN:
		uEventParam.struFallDown.byHeightThreshold = m_byHeightThreshold;
		uEventParam.struFallDown.wDuration = m_iAlarmPersist;
		uEventParam.struFallDown.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
		memcpy(&uEventParam.struFallDown.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
		break;
	case ENUM_VCA_EVENT_STANDUP:
		memcpy(&uEventParam.struStandUp.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
		uEventParam.struStandUp.bySensitivity= (BYTE)(m_comboSensitive.GetCurSel()+1);
		uEventParam.struStandUp.wDuration = m_iAlarmPersist;
		uEventParam.struStandUp.byHeightThreshold = m_byHeightThreshold;
		break;
	case ENUM_VCA_EVENT_PEOPLENUM_CHANGE:
		memcpy(&uEventParam.struPeopleNumChange.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
		uEventParam.struPeopleNumChange.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
		uEventParam.struPeopleNumChange.byPeopleNumThreshold = m_byPeopleNumThreshold;
		uEventParam.struPeopleNumChange.byDetectMode = (BYTE)(m_comDetectMode.GetCurSel()+1);
		uEventParam.struPeopleNumChange.byNoneStateEffective = m_bNoneStateEffective;
		uEventParam.struPeopleNumChange.wDuration = m_iAlarmPersist;
		break;
	case ENUM_VCA_EVENT_SPACING_CHANGE:
		memcpy(&uEventParam.struSpacingChange.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
		uEventParam.struSpacingChange.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
		uEventParam.struSpacingChange.byDetectMode = (BYTE)(m_comDetectMode.GetCurSel()+1);
		uEventParam.struSpacingChange.fSpacingThreshold = m_fSpacingThreshold;
		uEventParam.struSpacingChange.wDuration = m_iAlarmPersist;
		break;
	case ENUM_VCA_EVENT_AUDIO_ABNORMAL:
		uEventParam.struAudioAbnormal.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel() +1);
		uEventParam.struAudioAbnormal.wDecibel = m_iAlarmPersist;
		uEventParam.struAudioAbnormal.byAudioMode = m_comboAudioMode.GetCurSel();
		break;
	case ENUM_VCA_EVENT_ADV_REACH_HEIGHT:
		uEventParam.struReachHeight.dwCrossDirection = (VCA_CROSS_DIRECTION)m_comboAlarmDirect.GetCurSel();
		memcpy(&uEventParam.struReachHeight.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
		break;
	case ENUM_VCA_EVENT_TOILET_TARRY:
		uEventParam.struToiletTarry.wDelay = m_dwEventDelayTime;
		memcpy(&uEventParam.struToiletTarry.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
		break;
	case ENUM_VCA_EVENT_YARD_TARRY:
		uEventParam.struYardTarry.wDelay = m_dwEventDelayTime;
		memcpy(&uEventParam.struYardTarry.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
		break;
	case ENUM_VCA_EVENT_ADV_TRAVERSE_PLANE:
		uEventParam.struAdvTraversePlane.dwCrossDirection = (VCA_CROSS_DIRECTION)m_comboAlarmDirect.GetCurSel();
		memcpy(&uEventParam.struAdvTraversePlane.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
		uEventParam.struAdvTraversePlane.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
		break;
    default:
        break;
    }

}

void CDlgVcaRuleCfg::SetSizeFilterToWnd(NET_VCA_SIZE_FILTER const &struSizeFilter)
{
    m_bFilterActive = struSizeFilter.byActive;
    m_comboFilterMode.SetCurSel(struSizeFilter.byMode);
    OnSelchangeComboFilterMode();
    if (IMAGE_PIX_MODE == struSizeFilter.byMode)
    {
        memcpy(&m_struSizeFilter.struMaxRect, &struSizeFilter.struMaxRect, sizeof(m_struSizeFilter.struMaxRect));
        memcpy(&m_struSizeFilter.struMiniRect, &struSizeFilter.struMiniRect, sizeof(m_struSizeFilter.struMiniRect));
    }
    else if (REAL_WORLD_MODE == struSizeFilter.byMode)
    {
        m_fMinHeight = struSizeFilter.struMiniRect.fHeight;
        m_fMinWidth = struSizeFilter.struMiniRect.fWidth;
        m_fMaxHeight = struSizeFilter.struMaxRect.fHeight;
        m_fMaxWidth = struSizeFilter.struMaxRect.fWidth;
    }
    else if (DEFAULT_MODE == struSizeFilter.byMode)
    {

    }

//     m_comboFilterMode.SetCurSel(struSizeFilter.byMode);
//     m_comboFilterMode.SetCurSel(struSizeFilter.byMode);
//     EnableFilterModeWnd(struSizeFilter.byMode);
//     m_fMinHeight = struSizeFilter.struMiniRect.fHeight;
//     m_fMinWidth = struSizeFilter.struMiniRect.fWidth;
//     m_fMaxHeight = struSizeFilter.struMaxRect.fHeight;
//     m_fMaxWidth = struSizeFilter.struMaxRect.fWidth;
}

void CDlgVcaRuleCfg::GetSizeFilterFromWnd(NET_VCA_SIZE_FILTER &struSizeFilter)
{
    struSizeFilter.byActive = m_bFilterActive;
    struSizeFilter.byMode = m_comboFilterMode.GetItemData(m_comboFilterMode.GetCurSel());
    if (IMAGE_PIX_MODE == struSizeFilter.byMode)
    {
        memcpy(&struSizeFilter.struMaxRect, &m_struSizeFilter.struMaxRect, sizeof(struSizeFilter.struMaxRect));
        memcpy(&struSizeFilter.struMiniRect, &m_struSizeFilter.struMiniRect, sizeof(struSizeFilter.struMiniRect));
    }
    else if (REAL_WORLD_MODE == struSizeFilter.byMode)
    {
        struSizeFilter.struMaxRect.fHeight = m_fMaxHeight;
        struSizeFilter.struMaxRect.fWidth = m_fMaxWidth;
        struSizeFilter.struMiniRect.fHeight = m_fMinHeight;
        struSizeFilter.struMiniRect.fWidth = m_fMinWidth;
    }

//     struSizeFilter.byMode = m_comboFilterMode.GetCurSel();
//     if (REAL_WORLD_MODE == struSizeFilter.byMode)
//     {
//         struSizeFilter.struMiniRect.fHeight = m_fMinHeight;
//         struSizeFilter.struMiniRect.fWidth = m_fMinWidth;
//         struSizeFilter.struMaxRect.fHeight = m_fMaxHeight;
//         struSizeFilter.struMaxRect.fWidth = m_fMaxWidth;
//     }

}

void CDlgVcaRuleCfg::SetHandleExceptionToWnd(NET_DVR_HANDLEEXCEPTION_V30 const &struHandleException)
{
    m_bHandleType1 = (struHandleException.dwHandleType) &0x01;
    m_bHandleType2 = (struHandleException.dwHandleType>>1)&0x01;
    m_bHandleType3 = (struHandleException.dwHandleType>>2)&0x01;
    m_bHandleType4 = (struHandleException.dwHandleType>>3)&0x01;
    m_bHandleType5 = (struHandleException.dwHandleType>>4)&0x01;
    
    char szLan[128] = {0};
    char sbufCn[128] = {0};
    char sbufEn[128] = {0};
    int i;
//     for (i = 0; i < g_struDeviceInfo[m_iDevIndex].iAlarmOutNum; i++)
//     {
//         sprintf(sbufCn, "输出%d", (i+1));
//         sprintf(sbufEn, "Channel%d", (i+1));
//         g_StringLanType(szLan, sbufCn, sbufEn);
//         m_listAlarmOut.InsertItem(i, szLan);
//     }
//     for (i = 0; i < g_struDeviceInfo[m_iDevIndex].iAlarmOutNum; i++ )
//     {
//         if (struHandleException.byRelAlarmOut[i])
//         {
//             m_listAlarmOut.SetCheck(i);
//         }
//     }
	for (i=0; i<MAX_ALARMOUT_V30; i++)
	{
		m_bAlarmOut[i] = struHandleException.byRelAlarmOut[i];
	}
}

void CDlgVcaRuleCfg::GetHandleExceptionFromWnd(NET_DVR_HANDLEEXCEPTION_V30 &struHandleException)
{

    UpdateData(TRUE);
    struHandleException.dwHandleType = 0;
    struHandleException.dwHandleType |= (m_bHandleType1 << 0);
    struHandleException.dwHandleType |= (m_bHandleType2 << 1);
    struHandleException.dwHandleType |= (m_bHandleType3 << 2);
    struHandleException.dwHandleType |= (m_bHandleType4 << 3);
    struHandleException.dwHandleType |= (m_bHandleType5 << 4);
    
//     for (DWORD i = 0; i < g_struDeviceInfo[m_iDevIndex].iAlarmOutNum; i++)
//     {
//         struHandleException.byRelAlarmOut[i] = (BYTE)m_listAlarmOut.GetCheck(i);
//     }
	for (int i=0; i<MAX_ALARMOUT_V30; i++)
	{
		struHandleException.byRelAlarmOut[i] = (BYTE)m_bAlarmOut[i];
	}
    UpdateData(FALSE);
}

void CDlgVcaRuleCfg::SetRelRecordChanToWnd(BYTE const *byRelRecordChan, int nChanNum)
{
    m_listRecordChan.SetExtendedStyle(LVS_EX_CHECKBOXES);
    char szLan[128] = {0};
    int i;
    m_listRecordChan.DeleteAllItems();
    
	int nIndex = 0;
	for (i = g_struDeviceInfo[m_iDevIndex].iStartChan; i  <= g_struDeviceInfo[m_iDevIndex].iAnalogChanNum ; i++)
	{
		sprintf(szLan, "Analog Chan%d", i);
		m_listRecordChan.InsertItem(nIndex,szLan);
		m_listRecordChan.SetItemData(nIndex, i);
		nIndex++;
	}
    
    for (i = 0; i  < g_struDeviceInfo[m_iDevIndex].pStruIPParaCfgV40->dwDChanNum ; i++)
	{
		sprintf(szLan, "IP Chan%d", i + 1);
		m_listRecordChan.InsertItem(nIndex,szLan);
		m_listRecordChan.SetItemData(nIndex, i + g_struDeviceInfo[m_iDevIndex].pStruIPParaCfgV40->dwStartDChan);
		nIndex++;
	}

	for (i = 0; i < m_listRecordChan.GetItemCount(); i++)
	{   
		int nChanNumber = m_listRecordChan.GetItemData(i);
		int nAnalogChan = nChanNumber - g_struDeviceInfo[m_iDevIndex].iStartChan;
		if (nAnalogChan>=0 && byRelRecordChan[nAnalogChan])
        {
            m_listRecordChan.SetCheck(i);
        }
		else 
		{   
			int nIPChan = nChanNumber - g_struDeviceInfo[m_iDevIndex].pStruIPParaCfgV40->dwStartDChan;
			if (nIPChan >= 0 && byRelRecordChan[nIPChan])
			{
				m_listRecordChan.SetCheck(i);
			}
		}
	}
}
void CDlgVcaRuleCfg::GetRelRecordChanFromWnd(BYTE  *byRelRecordChan, int nChanNum)
{   
	memset(byRelRecordChan,0,MAX_CHANNUM_V30);

    for (int i = 0; i < m_listRecordChan.GetItemCount(); i++)
    {   
		if (m_listRecordChan.GetCheck(i))
		{
			int nChanNumber = m_listRecordChan.GetItemData(i);
			byRelRecordChan[nChanNumber - 1] = TRUE;
		}
    }
}

void CDlgVcaRuleCfg::SetAlarmTimeToWnd(NET_DVR_SCHEDTIME const *pAlarmTime, int nDay)
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

void CDlgVcaRuleCfg::GetAlarmTimeFromWnd(NET_DVR_SCHEDTIME *pAlarmTime, int nDay)
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

void CDlgVcaRuleCfg::SetFilterStrategyToWnd(NET_VCA_FILTER_STRATEGY const& struFilterStrategy)
{
	int nCount = m_comboFilterStrategy.GetCount();
	for (int i = 0; i < nCount; i++)
	{
		if (m_comboFilterStrategy.GetItemData(i) == struFilterStrategy.byStrategy)
		{
			m_comboFilterStrategy.SetCurSel(i);
			break;
		}
	}
}

void CDlgVcaRuleCfg::GetFilterStrategyFromWnd(NET_VCA_FILTER_STRATEGY* pFilterStrategy)
{
	int nCurSel = m_comboFilterStrategy.GetCurSel();
	if (nCurSel != CB_ERR)
	{
		pFilterStrategy->byStrategy = m_comboFilterStrategy.GetItemData(nCurSel);
	}
}

void CDlgVcaRuleCfg::SetRuleTriggerParamToWnd(NET_VCA_RULE_TRIGGER_PARAM const& struRuleTriggerParam)
{   
	int i = 0;
	DWORD dwTriggerMode = struRuleTriggerParam.byTriggerMode;

	int nTriggerModeCount = m_comboTriggerMode.GetCount();
	for (i = 0; i < nTriggerModeCount; i++)
	{
		if (m_comboTriggerMode.GetItemData(i) == struRuleTriggerParam.byTriggerMode)
		{
			m_comboTriggerMode.SetCurSel(i);
			break;
		}
	}

	if (dwTriggerMode == TRIGGER_MODE_TRACKPOINT)
	{
		int nTriggerPtCount = m_comboTriggerPoint.GetCount();
		for (i = 0; i < nTriggerPtCount; i++)
		{
			if (m_comboTriggerPoint.GetItemData(i) == struRuleTriggerParam.byTriggerPoint)
			{
				m_comboTriggerPoint.SetCurSel(i);
				break;
			}
		}
	}
	else if (dwTriggerMode == TRIGGER_MODE_TARGETAREA)
	{
		m_fTriggerArea = struRuleTriggerParam.fTriggerArea;
	}
}

void CDlgVcaRuleCfg::GetRuleTriggerParamFromWnd(NET_VCA_RULE_TRIGGER_PARAM* pRuleTriggerParam)
{   
	DWORD dwTriggerMode    = TRIGGER_MODE_NONE;
	int nTriggerModeIndex = m_comboTriggerMode.GetCurSel();
	if (nTriggerModeIndex != CB_ERR)
	{   
		dwTriggerMode = m_comboTriggerMode.GetItemData(nTriggerModeIndex);
		pRuleTriggerParam->byTriggerMode = dwTriggerMode;
	}

	if (dwTriggerMode == TRIGGER_MODE_TRACKPOINT)
	{
		int nTrackPtIndex = m_comboTriggerPoint.GetCurSel();
		if (nTrackPtIndex != CB_ERR)
		{
			pRuleTriggerParam->byTriggerPoint = m_comboTriggerPoint.GetItemData(nTrackPtIndex);
		}
	}
	else if (dwTriggerMode == TRIGGER_MODE_TARGETAREA)
	{
		pRuleTriggerParam->fTriggerArea = m_fTriggerArea;
	}
}

LONG CDlgVcaRuleCfg::StartPlay()
{
    //  如果能去前端流设备
	/*
    if (GetPuStreamCfg(m_struPuStream))
    {
        NET_DVR_DEVICEINFO_V30 struDeviceInfo = {0};
        
        m_lPUServerID = NET_DVR_Login_V30(m_struPuStream.struDevChanInfo.struIP.sIpV4, m_struPuStream.struDevChanInfo.wDVRPort,
            (char*)m_struPuStream.struDevChanInfo.sUserName, (char*)m_struPuStream.struDevChanInfo.sPassword, &struDeviceInfo);
        if (m_lPUServerID < 0)
        {
            AfxMessageBox("Fail to login front device");
            return m_lPUServerID;
        }
        
        NET_DVR_CLIENTINFO struPlay;
        struPlay.hPlayWnd 	= GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
        struPlay.lChannel 	= m_struPuStream.struDevChanInfo.byChannel; 
        struPlay.lLinkMode 	= 0;
        struPlay.sMultiCastIP = "";	
        
        m_lPlayHandle = NET_DVR_RealPlay_V30(m_lPUServerID, &struPlay, NULL, NULL, TRUE); 
        
        BOOL bRet = FALSE;
        if (m_lPlayHandle < 0)
        {
            g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_RealPlay_V30");
            AfxMessageBox("NET_DVR_RealPlay_V30 FAIL");		
        }
        else
        {
            g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_RealPlay_V30");
            bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawAlertShow, 0);//DC Draw callback
        }
        return m_lPlayHandle;
    }
	*/
//   else // 到设备去取流预览
    {
    NET_DVR_CLIENTINFO struPlay;
    struPlay.hPlayWnd 	= GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
    struPlay.lChannel 	= m_iVcaChannel; 
    struPlay.lLinkMode 	= 0;
    struPlay.sMultiCastIP = "";	
    
    m_lPlayHandle = NET_DVR_RealPlay_V30(m_lServerID, &struPlay, NULL, NULL, TRUE); 
    BOOL bRet = FALSE;
    if (m_lPlayHandle < 0)
    {
        g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_RealPlay_V30");
        AfxMessageBox("NET_DVR_RealPlay_V30 FAIL");		
    }
    else
    {
        g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_RealPlay_V30");
        bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawAlertShow, 0);//DC Draw callback
    }

    return m_lPlayHandle;
}

}


BOOL CDlgVcaRuleCfg::StopPlay()
{
    if (m_lPlayHandle >= 0)
    {
        NET_DVR_StopRealPlay(m_lPlayHandle);
        m_lPlayHandle = -1;
    }

    if (m_lPUServerID >= 0)
    {
        NET_DVR_Logout_V30(m_lPUServerID);
        m_lPUServerID = -1;
    }
    return TRUE;
}

void CDlgVcaRuleCfg::PostNcDestroy() 
{
    if (m_lPlayHandle >= 0)
    {
        NET_DVR_StopRealPlay(m_lPlayHandle);
        m_lPlayHandle = -1;
    }
    g_pDlgVcaRuleCfg = NULL;
	
	CDialog::PostNcDestroy();
}

void CDlgVcaRuleCfg::OnSelchangeComboFilterMode() 
{
    DWORD dwFilterMode = m_comboFilterMode.GetItemData(m_comboFilterMode.GetCurSel());
    ShowDefaultMode(SW_HIDE);
    if (IMAGE_PIX_MODE == dwFilterMode)
    {
        ShowPixMode(SW_SHOW);
    }
    else if (REAL_WORLD_MODE == dwFilterMode)
    {
        ShowRealMode(SW_SHOW);
    }
    else if (DEFAULT_MODE == dwFilterMode)
    {
        
    }
}

void CDlgVcaRuleCfg::ShowPixMode(int nCmdShow)
{
    GetDlgItem(IDC_CHECK_SET_MINI_FILTER)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_CHECK_SET_MAX_FILTER)->ShowWindow(nCmdShow);
}
void CDlgVcaRuleCfg::ShowRealMode(int nCmdShow)
{
    GetDlgItem(IDC_STATIC_MIN)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_STATIC_MIN_H)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_STATIC_MIN_W)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_STATIC_MAX)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_STATIC_MAX_W)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_STATIC_MAX_H)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_EDIT_MIN_HEIGHT)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_EDIT_MIN_WIDTH)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_EDIT_MAX_HEIGHT)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_EDIT_MAX_WIDTH)->ShowWindow(nCmdShow);
}

void CDlgVcaRuleCfg::ShowDefaultMode(int nCmdShow)
{
    ShowRealMode(nCmdShow);
    ShowPixMode(nCmdShow);
}

BOOL CDlgVcaRuleCfg::GetPuStreamCfg(NET_DVR_PU_STREAM_CFG &struPUStream)
{
    DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_PU_STREAMCFG,m_iVcaChannel, &struPUStream, sizeof(struPUStream), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PU_STREAMCFG");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PU_STREAMCFG");
        return FALSE;
    }
}

void CDlgVcaRuleCfg::OnClickTreeAlarmOutRelate(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CPoint pt(0,0);
	CRect rc(0,0,0,0);
	GetCursorPos(&pt);
	GetDlgItem(IDC_TREE_ALARM_OUT_RELATE)->GetWindowRect(&rc);
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

void CDlgVcaRuleCfg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CreateTree();
	CDialog::OnPaint();
	// Do not call CDialog::OnPaint() for painting messages
}

void CDlgVcaRuleCfg::CreateAlarmOutTree(CTreeCtrl &m_treeAlarmOut, int iDeviceIndex, BOOL *bAlarmOut)
{
	if (iDeviceIndex == -1)
	{
		return;
	}
	m_treeAlarmOut.DeleteAllItems();
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0;
	HTREEITEM hChanItem = NULL;
	HTREEITEM hFirstItem = NULL;
	BOOL m_bAlarmOut[MAX_IP_ALARMOUT];
	DWORD dwID = 0;
	for (i = 0; i < MAX_IP_ALARMOUT; i++)
	{
		m_bAlarmOut[i] = BOOL(*(bAlarmOut+i));
// 		if ((i <  g_struDeviceInfo[iDeviceIndex].iAlarmOutNum))
// 		{
// 			strTemp.Format(ALARM_OUT_FORMAT, i+1);
// 			hChanItem =  m_treeAlarmOut.InsertItem(strTemp, 0, 0, TVI_ROOT);
// 			if (hFirstItem == NULL)
// 			{
// 				hFirstItem = hChanItem;
// 			}
// 			m_treeAlarmOut.SetItemData(hChanItem, 0*1000 + i);	
// 			if (m_bAlarmOut[i])
// 			{
// 				m_treeAlarmOut.SetCheck(hChanItem, TRUE);
// 			}
// 		}
// 		else if (i >= MAX_ANALOG_ALARMOUT)
// 		{
			dwID = g_struDeviceInfo[iDeviceIndex].struAlarmOutCfg.struIPAlarmOutInfo[i/*-MAX_ANALOG_ALARMOUT*/].byIPID;
			if (dwID != 0)
			{
				strTemp.Format(IP_ALARM_OUT_NAME, i+1/*-MAX_ANALOG_ALARMOUT*/);
				hChanItem =  m_treeAlarmOut.InsertItem(strTemp, 0, 0, TVI_ROOT);
				m_treeAlarmOut.SetItemData(hChanItem, 1*1000 + i);	
				if (m_bAlarmOut[i])
				{
					m_treeAlarmOut.SetCheck(hChanItem, TRUE);
				}
			}
		// }
	}
	m_treeAlarmOut.SelectItem(hFirstItem);//avoid keeping clearing screen
	m_treeAlarmOut.Expand(m_treeAlarmOut.GetRootItem(),TVE_EXPAND);
}

/*********************************************************
Function:	CreateTree
Desc:		Create alarm output-video channel connection
Input:	
Output:	
Return:	
**********************************************************/
void CDlgVcaRuleCfg::CreateTree(void)
{
	//m_treeAlarmOut.DeleteAllItems();
	CreateAlarmOutTree(m_treeAlarmOut, m_iDevIndex, m_bAlarmOut);
//	m_treeChan.DeleteAllItems();
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0;
	HTREEITEM hChanItem = NULL;
	
// 	for (i = 0; i < MAX_CHANNUM_V30; i++)
// 	{
// 		if (g_struDeviceInfo[m_dwDevIndex].struChanInfo[i].bEnable)
// 		{
// 			if (i < m_iChanCount)
// 			{
// 				strTemp.Format(ANALOG_C_FORMAT, i+g_struDeviceInfo[m_dwDevIndex].iStartChan);
// 				hChanItem =  m_treeChan.InsertItem(strTemp, TVI_ROOT);
// 				m_treeChan.SetItemData(hChanItem, 1*1000 + i);	
// 				if (g_lpMotionDetect->byRelRecordChan[i])
// 				{
// 					m_treeChan.SetCheck(hChanItem, TRUE);
// 				}
// 			}
// 			else if (i >= MAX_ANALOG_CHANNUM)
// 			{
// 				strTemp.Format(DIGITAL_C_FORMAT, i+g_struDeviceInfo[m_dwDevIndex].iStartChan-MAX_ANALOG_CHANNUM);
// 				hChanItem =  m_treeChan.InsertItem(strTemp, TVI_ROOT);
// 				m_treeChan.SetItemData(hChanItem, 2*1000 + i);	
// 				if (m_bRecordChan[i])
// 				{
// 					m_treeChan.SetCheck(hChanItem, TRUE);
// 				}
// 			}
// 		}
// 	}
// 	m_treeChan.Expand(m_treeChan.GetRootItem(),TVE_EXPAND);	
	UpdateData(FALSE);
}

void CDlgVcaRuleCfg::OnSelchangeComboTriggermode() 
{
	int nCurSel = m_comboTriggerMode.GetCurSel();
	if (nCurSel != CB_ERR)
	{
		DWORD dwTriggerMode = m_comboTriggerMode.GetItemData(nCurSel);

		m_comboTriggerPoint.EnableWindow(dwTriggerMode == TRIGGER_MODE_TRACKPOINT);
		GetDlgItem(IDC_EDIT_TRIGGERAREA)->EnableWindow(dwTriggerMode == TRIGGER_MODE_TARGETAREA);
	}
}
