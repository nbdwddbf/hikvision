// DlgVcaPositionRule.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaPositionRule.h"
#include <math.h>
#include "gdiplus/GdiPlus.h"
#include "DlgVcaTrackCfg.h"
#include "DlgPtzCtrl.h"
#include "DlgIPDomeLocalCfg.h"
#include "DlgPositionTrackCfg.h"
#include "DlgLimitAngle.h"
#include "DlgPtzLockCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CDlgVcaPositionRule *g_pDlgVcaPositionRule;  
#define  AlarmLine 1
#define  AlarmArea 2

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaPositionRule dialog
/*********************************************************
Function:	DrawAlertShow
Desc:		Callback of Draw on preview
Input:	nPort that is Player Handle
hDc    : DC handle of player window
dwUser: User data
Output:	none
Return:	none
**********************************************************/
void CALLBACK DrawPositionAlertShow(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
	SetBkMode(hDc, TRANSPARENT);
	SetTextColor(hDc, RGB(255, 255, 255));
	if(g_pDlgVcaPositionRule->m_bRuleActive)
	{
		g_pDlgVcaPositionRule->F_DrawFun(lRealHandle, hDc, dwUser); 
	}
}

CDlgVcaPositionRule::CDlgVcaPositionRule(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaPositionRule::IDD, pParent)
    , m_iParam1(0)
    , m_iParam2(0)
    , m_iParam3(0)
    , m_iParam4(0)
    , m_iParam5(0)
    , m_iParam6(0)
{
	//{{AFX_DATA_INIT(CDlgVcaPositionRule)
	m_bDSPAddRule = FALSE;
	m_bDSPAddTarget = FALSE;
	m_bPicAddRule = FALSE;
	m_bPicAddTarget = FALSE;
	m_bFilterActive = FALSE;
	m_bSetMaxFilter = FALSE;
	m_bSetMiniFilter = FALSE;
	m_bVcaActive = FALSE;
	m_bHandleType1 = FALSE;
	m_bHandleType2 = FALSE;
	m_bHandleType3 = FALSE;
	m_bHandleType4 = FALSE;
	m_bHandleType5 = FALSE;
    m_bHandleType6 = FALSE;
	m_bDrawPolygon = FALSE;
	m_bRuleActive = FALSE;
	m_iBAdvanceChanNum = 0;
	m_iBBaseChanNum = 0;
	m_iBFullChanNum = 0;
	m_iPlateChanNum = 0;
	m_iVcaChanNum = 0;
	m_csRuleName = _T("");
	m_iHour11 = 0;
	m_iHour12 = 0;
	m_iHour21 = 0;
	m_iHour22 = 0;
	m_iMin11 = 0;
	m_iMin12 = 0;
	m_iMin21 = 0;
	m_iMin22 = 0;
	m_iAlarmDelay = 0;
	m_iAlarmPersist = 0;
	m_fMaxDistance = 0.0f;
	m_fDenstityRate = 0.0f;
	m_iReadCardTimePersist = 0;
	m_bDrawLine = FALSE;
	m_iAtmChanNum = 0;
	m_csPtzPositionName = _T("");
	m_bChkTrackEn = FALSE;
	m_dwTrackTime = 0;
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
	m_bChkPositionEn = FALSE;
    m_dwMinInterval = 0;
    m_dwMaxInterval = 0;
    m_byRuleID1 = 0;
    m_byRuleID2 = 0; 
	//}}AFX_DATA_INIT
	m_lServerID = -1;
	m_iStartChannel = -1;
	m_iDevIndex = -1;
	m_iChannelnumber = -1;
	m_dwAlarmOutNum = 0;
	m_iVcaChannel = -1;
    m_iPositionIndex = 0;
	
	memset(&m_struVcaCtrlCfg, 0, sizeof(m_struVcaCtrlCfg));
	memset(&m_struBehaviorAbility, 0, sizeof(m_struBehaviorAbility));
	memset(&m_struRuleCfg, 0, sizeof(m_struRuleCfg));
    memset(&m_struRuleCfgEx, 0, sizeof(m_struRuleCfgEx));
	memset(&m_struOneRule, 0, sizeof(m_struOneRule));
	memset(&m_struVCADrawMode, 0 ,sizeof(m_struVCADrawMode));
	m_dwPosNum = 0;

	memset(&m_struVcaPolygon[0], 0, sizeof(NET_VCA_POLYGON)*MAX_RULE_NUM_V42);
	memset(&m_struVcaLine[0], 0, sizeof(NET_VCA_LINE)*MAX_RULE_NUM_V42);
	memset(&m_bCloseIn[0], 0, sizeof(BOOL)*MAX_RULE_NUM_V42);
	memset(&m_bNeedRedraw[0], 0, sizeof(BOOL)*MAX_RULE_NUM_V42);
	memset(&m_bMouseMove[0], 0, sizeof(BOOL)*MAX_RULE_NUM_V42);
	memset(&m_struAlarmTime[0][0], 0, (MAX_DAYS*MAX_TIMESEGMENT_V30*sizeof(NET_DVR_SCHEDTIME)));
	
	m_iCurRuleID = -1;
	memset(&m_rcWndRect, 0, sizeof(m_rcWndRect));
	m_lPlayHandle = -1;

    memset(&m_struPositionRule, 0, sizeof(m_struPositionRule));
    memset(&m_struPtzPosition, 0, sizeof(m_struPtzPosition));
    memset(&m_struTrackCfg, 0, sizeof(m_struTrackCfg));
    memset(&m_struRuleCfgV42, 0, sizeof(m_struRuleCfgV42));
    memset(&m_struChanGroup, 0, sizeof(m_struChanGroup));
    m_pbChannel = new BOOL[MAX_CHANNUM_V40];
    if(m_pbChannel)
    {
        memset(m_pbChannel,0,sizeof(BOOL)*MAX_CHANNUM_V40);
    }

    m_pbAlarmOut = new BOOL[MAX_ALARMOUT_V40];
    if(m_pbAlarmOut)
    {
        memset(m_pbAlarmOut,0,sizeof(BOOL)*MAX_ALARMOUT_V40);
    }

}



/*********************************************************
Function:	CDlgVcaPositionRule
Desc:		destructor
Input:	
Output:	
Return:	
**********************************************************/
CDlgVcaPositionRule::~CDlgVcaPositionRule()
{
    if (m_pbChannel)
    {
        delete[] m_pbChannel;
        m_pbChannel = NULL;
    }

    if (m_pbAlarmOut)
    {
        delete[] m_pbAlarmOut;
        m_pbAlarmOut = NULL;
    }
}
/*********************************************************
  Function:	DoDataExchange
  Desc:		the map between control and variable
  Input:	none
  Output:	none
  Return:	none
**********************************************************/

void CDlgVcaPositionRule::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgVcaPositionRule)
    DDX_Control(pDX, IDC_TREE_CHANNEL_VCA, m_treeChannel);
    DDX_Control(pDX, IDC_TREE_ALARMOUT, m_treeAlarmout);
    DDX_Control(pDX, IDC_COMBO_DET_TARGET, m_comDetTarget);
    DDX_Control(pDX, IDC_COMBO_EVENT_PRIORITY, m_comEventPriority);
    DDX_Control(pDX, IDC_COMBO_POSITION_GROUPNO, m_cmbVCARuleGroupNo);
    DDX_Control(pDX, IDC_COMBO_POSITION_CHANNEL, m_cmbVCARuleChannel);
    DDX_Control(pDX, IDC_COMBO_ZOOM_MODE, m_comboZoomMode);
    DDX_Control(pDX, IDC_COMBO_TRACKING_MODE, m_comboTrackingMode);
    DDX_Control(pDX, IDC_COMBO_POSITION_INDEX, m_comboPositionIndex);
    DDX_Control(pDX, IDC_COMBO_RULE_SEQ, m_comboRuleSequence);
    DDX_Text(pDX, IDC_EDIT_MIN_INTERVAL, m_dwMinInterval);
    DDX_Text(pDX, IDC_EDIT_MAX_INTERVAL, m_dwMaxInterval);
    DDX_Text(pDX, IDC_EDIT_RULE1, m_byRuleID1);
    DDX_Text(pDX, IDC_EDIT_RULE2, m_byRuleID2);
    DDX_Control(pDX, IDC_STATIC_STICKUP_ALARM_PERSIST, m_staticStickupAlarmPersist);
    DDX_Control(pDX, IDC_COMBO_ATM_MODE2, m_comboAtmMode);
    DDX_Control(pDX, IDC_STATIC_ALARM_DIRECT, m_staticAlarmDirect);
    DDX_Control(pDX, IDC_COMLINEALARMDIRECT, m_comboAlarmDirect);
    DDX_Control(pDX, IDC_STATIC_MAX_DISTANCE_AREA, m_staticMaxDistanceArea);
    DDX_Control(pDX, IDC_STATIC_DENSTITY_RATE_AREA, m_staticDenstityRateArea);
    DDX_Control(pDX, IDC_STATIC_ALARM_PERSIST_AREA, m_staticAlarmPersistArea);
    DDX_Control(pDX, IDC_STATIC_ALARM_DELAY_AREA, m_staticAlarmDelayArea);
    DDX_Control(pDX, IDC_STATIC_READ_CARD_TIME_PERSIST_AREA2, m_staticReadCardTimePersistArea);
    DDX_Control(pDX, IDC_EDIT_ALARM_PERSIST, m_editAlarmPersist);
    DDX_Control(pDX, IDC_EDIT_DENSTITY_RATE, m_editDenstityRate);
    DDX_Control(pDX, IDC_EDIT_READ_CARD_TIME_PERSIST, m_editReadCardTimePersist);
    DDX_Control(pDX, IDC_EDIT_MAX_DISTANCE, m_editMaxDistance);
    DDX_Control(pDX, IDC_EDIT_ALARM_DELAY, m_editAlarmDelay);
    DDX_Control(pDX, IDC_STATIC_READ_CARD_TIME_PERSIST, m_staticReadCardTimePersist);
    DDX_Control(pDX, IDC_STATIC_MAX_DISTANCE, m_staticMaxDistance);
    DDX_Control(pDX, IDC_STATIC_DENSTITY_RATE, m_staticDenstityRate);
    DDX_Control(pDX, IDC_STATIC_ALARM_PERSIST, m_staticAlarmPersist);
    DDX_Control(pDX, IDC_STATIC_ALARM_DELAY, m_staticAlarmDelay);
    DDX_Control(pDX, IDC_COMBOWEEKDAY, m_comboWeekday);
    DDX_Control(pDX, IDC_COMBOCOPYTIME, m_comboCopyTime);
    DDX_Control(pDX, IDC_COMBO_VCA_TYPE, m_comboVcaType);
    DDX_Control(pDX, IDC_COMBO_VCA_CHAN, m_comboVcaChan);
    DDX_Control(pDX, IDC_COMBO_STREAM, m_comboStream);
    DDX_Control(pDX, IDC_COMBO_SENSITIVE, m_comboSensitive);
    DDX_Control(pDX, IDC_COMBO_RULE_TYPE, m_comboRuleType);
    DDX_Control(pDX, IDC_COMBO_RULE_ID, m_comboRuleID);
    DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_comboResolution);
    DDX_Control(pDX, IDC_COMBO_PRO_PIC_TYPE, m_comboProPicType);
    DDX_Control(pDX, IDC_COMBO_PIC_QUALITY, m_comboPicQuality);
    DDX_Check(pDX, IDC_CHECK_DSP_ADD_RULE, m_bDSPAddRule);
    DDX_Check(pDX, IDC_CHECK_DSP_ADD_TARGET, m_bDSPAddTarget);
    DDX_Check(pDX, IDC_CHECK_PIC_ADD_RULE, m_bPicAddRule);
    DDX_Check(pDX, IDC_CHECK_PIC_ADD_TARGET, m_bPicAddTarget);
    DDX_Check(pDX, IDC_CHECK_FILTER_ACTIVE, m_bFilterActive);
    DDX_Check(pDX, IDC_CHECK_SET_MAX_FILTER, m_bSetMaxFilter);
    DDX_Check(pDX, IDC_CHECK_SET_MINI_FILTER, m_bSetMiniFilter);
    DDX_Check(pDX, IDC_CHECK_VCA_ACTIVE, m_bVcaActive);
    DDX_Check(pDX, IDC_CHECKHANDLETYPE1, m_bHandleType1);
    DDX_Check(pDX, IDC_CHECKHANDLETYPE2, m_bHandleType2);
    DDX_Check(pDX, IDC_CHECKHANDLETYPE3, m_bHandleType3);
    DDX_Check(pDX, IDC_CHECKHANDLETYPE4, m_bHandleType4);
    DDX_Check(pDX, IDC_CHECKHANDLETYPE5, m_bHandleType5);
    DDX_Check(pDX, IDC_CHK_PIC_CLOUD, m_bHandleType6);
    DDX_Check(pDX, IDC_CHK_DRAW_POLYGON, m_bDrawPolygon);
    DDX_Check(pDX, IDC_CHK_RULE_ACTIVE, m_bRuleActive);
    DDX_Text(pDX, IDC_EDIT_BADVANCE_CHAN_NUM, m_iBAdvanceChanNum);
    DDX_Text(pDX, IDC_EDIT_BBASE_CHAN_NUM, m_iBBaseChanNum);
    DDX_Text(pDX, IDC_EDIT_BFULL_CHAN_NUM, m_iBFullChanNum);
    DDX_Text(pDX, IDC_EDIT_PLATE_CHAN_NUM1, m_iPlateChanNum);
    DDX_Text(pDX, IDC_EDIT_VCA_CHAN_NUM, m_iVcaChanNum);
    DDX_Text(pDX, IDC_EDIT_RULE_NAME, m_csRuleName);
    DDV_MaxChars(pDX, m_csRuleName, 31);
    DDX_Text(pDX, IDC_EDITHOUR11, m_iHour11);
    DDX_Text(pDX, IDC_EDITHOUR12, m_iHour12);
    DDX_Text(pDX, IDC_EDITHOUR21, m_iHour21);
    DDX_Text(pDX, IDC_EDITHOUR22, m_iHour22);
    DDX_Text(pDX, IDC_EDITMIN11, m_iMin11);
    DDX_Text(pDX, IDC_EDITMIN12, m_iMin12);
    DDX_Text(pDX, IDC_EDITMIN21, m_iMin21);
    DDX_Text(pDX, IDC_EDITMIN22, m_iMin22);
    DDX_Text(pDX, IDC_EDIT_ALARM_DELAY, m_iAlarmDelay);
    DDX_Text(pDX, IDC_EDIT_ALARM_PERSIST, m_iAlarmPersist);
    DDX_Text(pDX, IDC_EDIT_MAX_DISTANCE, m_fMaxDistance);
    DDX_Text(pDX, IDC_EDIT_DENSTITY_RATE, m_fDenstityRate);
    DDX_Text(pDX, IDC_EDIT_READ_CARD_TIME_PERSIST, m_iReadCardTimePersist);
    DDX_Check(pDX, IDC_CHK_DRAW_LINE, m_bDrawLine);
    DDX_Text(pDX, IDC_EDIT_ATM_CHAN_NUM, m_iAtmChanNum);
    DDX_Text(pDX, IDC_EDIT_PTZ_POSITION_NAME, m_csPtzPositionName);
    DDX_Check(pDX, IDC_CHK_TRACK_ENABLE, m_bChkTrackEn);
    DDX_Text(pDX, IDC_EDIT_TRACK_TIME, m_dwTrackTime);
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
    DDX_Check(pDX, IDC_CHK_ENABLE_POSITION, m_bChkPositionEn);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMBO_EVENT_PRIORITY2, m_comboPriority);
    DDX_Text(pDX, IDC_EDIT_PARAM1, m_iParam1);
    DDX_Text(pDX, IDC_EDIT_PARAM2, m_iParam2);
    DDX_Text(pDX, IDC_EDIT_PARAM3, m_iParam3);
    DDX_Text(pDX, IDC_EDIT_PARAM4, m_iParam4);
    DDX_Text(pDX, IDC_EDIT_PARAM5, m_iParam5);
    DDX_Text(pDX, IDC_EDIT_PARAM6, m_iParam6);
}


BEGIN_MESSAGE_MAP(CDlgVcaPositionRule, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaPositionRule)
	ON_BN_CLICKED(ID_BTN_SET_RULE_CFG, OnBtnSetRuleCfg)
	ON_BN_CLICKED(ID_BTN_SET_VCA_CTRL, OnBtnSetVcaCtrl)
	ON_BN_CLICKED(IDC_BTN_REFESH, OnBtnRefesh)
	ON_BN_CLICKED(IDC_BTN_SET_ONE_RULE, OnBtnSetOneRule)
	ON_BN_CLICKED(IDC_BTN_VCA_RESTART, OnBtnVcaRestart)
	ON_BN_CLICKED(IDC_BTN_SET_VCA_DRAW_MODE, OnBtnSetVcaDrawMode)
	ON_CBN_SELCHANGE(IDC_COMBO_VCA_CHAN, OnSelchangeComboVcaChan)
	ON_BN_CLICKED(IDC_CHECK_VCA_ACTIVE, OnCheckVcaActive)
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
	ON_EN_CHANGE(IDC_EDIT_ALARM_DELAY, OnChangeEditAlarmDelay)
	ON_EN_CHANGE(IDC_EDIT_ALARM_PERSIST, OnChangeEditAlarmPersist)
	ON_EN_CHANGE(IDC_EDIT_DENSTITY_RATE, OnChangeEditDenstityRate)
	ON_EN_CHANGE(IDC_EDIT_MAX_DISTANCE, OnChangeEditMaxDistance)
	ON_EN_CHANGE(IDC_EDIT_READ_CARD_TIME_PERSIST, OnChangeEditReadCardTimePersist)
	ON_BN_CLICKED(IDC_BTN_TRACK_CFG, OnBtnTrackCfg)
	ON_BN_CLICKED(IDC_BTN_GET_PTZ, OnBtnGetPtz)
	ON_BN_CLICKED(IDC_BTN_PTZ_CTRL, OnBtnPtzCtrl)
	ON_BN_CLICKED(IDC_BTN_ENABLE_CALIBRATE, OnBtnEnableCalibrate)
	ON_BN_CLICKED(IDC_BTN_DOME_CONFIG, OnBtnDomeConfig)
	ON_CBN_SELCHANGE(IDC_COMBO_POSITION_INDEX, OnSelchangeComboPositionIndex)
	ON_BN_CLICKED(IDC_BTN_POSITION_TRACK, OnBtnPositionTrack)
	ON_BN_CLICKED(IDC_BTN_POSITION_LIMITANGLE, OnBtnPositionLimitangle)
	ON_BN_CLICKED(ID_BTN_GET_RULE_CFG, OnBtnGetRuleCfg)
	ON_NOTIFY(NM_CLICK, IDC_TREE_CHANNEL_VCA, OnClickTreeChannelVca)
	ON_NOTIFY(NM_CLICK, IDC_TREE_ALARMOUT, OnClickTreeAlarmout)
	ON_BN_CLICKED(IDC_BTN_SET_PTZ, OnBtnSetPtz)
	ON_BN_CLICKED(IDC_BTN_PTZ_LOCKCFG, OnBtnPtzLockcfg)
	//}}AFX_MSG_MAP
    ON_CBN_SELCHANGE(IDC_COMBO_POSITION_CHANNEL, &CDlgVcaPositionRule::OnCbnSelchangeComboPositionChannel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaPositionRule message handlers

BOOL CDlgVcaPositionRule::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	CPoint pt(0,0);
	CRect  rcWnd(0,0,0,0);
	GetDlgItem(IDC_PLAYWND)->GetWindowRect(&rcWnd);
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
				if(PtInRect(&rcWnd,pt))
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
							MessageBox(szLan);
							return TRUE;
						}
						if((float)(pt.x-rcWnd.left)/(float)rcWnd.Width() <= m_struVcaPolygon[m_iCurRuleID].struPos[m_dwPosNum-1].fX+0.01 && (float)(pt.x-rcWnd.left)/(float)rcWnd.Width() >= m_struVcaPolygon[m_iCurRuleID].struPos[m_dwPosNum-1].fX-0.01\
							&& (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() <= m_struVcaPolygon[m_iCurRuleID].struPos[m_dwPosNum-1].fY+0.01 && (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() >= m_struVcaPolygon[m_iCurRuleID].struPos[m_dwPosNum-1].fY-0.01)
						{
							char szLan[128] = {0};
							g_StringLanType(szLan, "不能连续在同一点上画区域", "Can't draw region on the point used");
							MessageBox(szLan);
							return TRUE;
						}
						m_bCloseIn[m_iCurRuleID] = FALSE;
						m_bMouseMove[m_iCurRuleID] = FALSE;
						m_struVcaPolygon[m_iCurRuleID].struPos[m_dwPosNum].fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
						m_struVcaPolygon[m_iCurRuleID].struPos[m_dwPosNum].fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
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
				if(PtInRect(&rcWnd,pt))
				{		
					if(!m_bMouseMove[m_iCurRuleID])
					{
						m_struVcaLine[m_iCurRuleID].struStart.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
						m_struVcaLine[m_iCurRuleID].struStart.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();		
						m_struVcaLine[m_iCurRuleID].struEnd.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
						m_struVcaLine[m_iCurRuleID].struEnd.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();			
						m_bMouseMove[m_iCurRuleID] = TRUE;
					}
					else
					{
						if ((float)(pt.x-rcWnd.left)/(float)rcWnd.Width() <= m_struVcaLine[m_iCurRuleID].struStart.fX+0.01 && (float)(pt.x-rcWnd.left)/(float)rcWnd.Width() >= m_struVcaLine[m_iCurRuleID].struStart.fX-0.01\
							&& (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() <= m_struVcaLine[m_iCurRuleID].struStart.fY+0.01 && (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() >= m_struVcaLine[m_iCurRuleID].struStart.fY-0.01)
						{
							char szLan[128] = {0};
							g_StringLanType(szLan, "不能连续在同一点上画区域", "Can't draw region on the point used");
							MessageBox(szLan);
							return TRUE;
						}
						m_struVcaLine[m_iCurRuleID].struEnd.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
						m_struVcaLine[m_iCurRuleID].struEnd.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();			
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
			if(PtInRect(&rcWnd,pt))
			{
			m_struOneRule.struSizeFilter.struMiniRect.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
			m_struOneRule.struSizeFilter.struMiniRect.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
			}
		}//First coordinate of Maximal Rectangle
		else if(m_bSetMaxFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
		{
			if(PtInRect(&rcWnd,pt))
			{
			m_struOneRule.struSizeFilter.struMaxRect.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
			m_struOneRule.struSizeFilter.struMaxRect.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
		}
		}
		break;
	case WM_MOUSEMOVE:
		if((m_bDrawLine || m_bDrawPolygon)&&(GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
		{
			if (m_bDrawPolygon)
			{
				if(PtInRect(&rcWnd,pt))
				{
					if(m_dwPosNum > 9)
					{
						return TRUE;
					}
					if( m_bNeedRedraw[m_iCurRuleID] && !m_bCloseIn[m_iCurRuleID])
					{
						m_bMouseMove[m_iCurRuleID] = TRUE;
						m_struVcaPolygon[m_iCurRuleID].struPos[m_dwPosNum].fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
						m_struVcaPolygon[m_iCurRuleID].struPos[m_dwPosNum].fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
						m_struVcaPolygon[m_iCurRuleID].dwPointNum = m_dwPosNum+1;				
					}
				}
			}
			
			if(m_bDrawLine)
			{
				if(PtInRect(&rcWnd,pt))
				{
					if(m_bMouseMove)
					{
						m_struVcaLine[m_iCurRuleID].struEnd.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
						m_struVcaLine[m_iCurRuleID].struEnd.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();			
					}
				}
			}
		}
		else if(m_bSetMiniFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)) //尺寸过滤器
		{
			if(PtInRect(&rcWnd,pt))
			{
			m_struOneRule.struSizeFilter.struMiniRect.fWidth = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width() - m_struOneRule.struSizeFilter.struMiniRect.fX;
			m_struOneRule.struSizeFilter.struMiniRect.fHeight = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() - m_struOneRule.struSizeFilter.struMiniRect.fY;
			}
	
		}
		else if(m_bSetMaxFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)) //尺寸过滤器
		{
			if(PtInRect(&rcWnd,pt))
			{	
			m_struOneRule.struSizeFilter.struMaxRect.fWidth = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width() - m_struOneRule.struSizeFilter.struMaxRect.fX;
			m_struOneRule.struSizeFilter.struMaxRect.fHeight = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() - m_struOneRule.struSizeFilter.struMaxRect.fY;
		}
		}
		break;
	case WM_RBUTTONDOWN://Click right mouse to close the rectangle. 
		if(m_bDrawPolygon && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
		{
			if(PtInRect(&rcWnd,pt))
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
					MessageBox(szlan);
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
			if(PtInRect(&rcWnd,pt))
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
					m_struVcaPolygon[m_iCurRuleID].dwPointNum = 0;
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
BOOL CDlgVcaPositionRule::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here

    CRect rect;
	GetDlgItem(IDC_PLAYWND)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	int nWidth = (int)((rect.Height()*352)/288);
	rect.left  += (long)fabs((long double)(rect.right - rect.left - nWidth))/2;
	rect.right = rect.left + nWidth;
	
	GetDlgItem(IDC_PLAYWND)->MoveWindow(rect);

	g_pDlgVcaPositionRule = this; // 
	m_iVcaChannel = m_iStartChannel;	
	m_dwAlarmOutNum = g_struDeviceInfo[m_iDevIndex].iAlarmOutNum;
	GetDevVcaChanPara();//Get channel info
     
	char szLan[128] = {0};
	DWORD dwReturned = 0;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_VCA_CTRLCFG, 0, &m_struVcaCtrlCfg, sizeof(NET_VCA_CTRLCFG), &dwReturned))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VCA_CTRLCFG");
        g_StringLanType(szLan, "获取智能控制信息失败", "Failure to obtain information on VCA Control");
        AfxMessageBox(szLan);
        //	OnButexit();
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_VCA_CTRLCFG ");
    }

	EnableVcaWindow(m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byVCAEnable); 

	NET_VCA_CHAN_IN_PARAM struVcaChanInparam;
	memset(&struVcaChanInparam, 0 ,sizeof(NET_VCA_CHAN_IN_PARAM));
	struVcaChanInparam.byVCAType = m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byVCAType;
	struVcaChanInparam.byMode = m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byMode;
	
	m_iCurRuleID = 0;

	GetVcaPara(m_iVcaChannel, struVcaChanInparam);
	
	RefreshOneRule(m_struOneRule);
 
    GetTrackCfg();
   
     
   if (m_struTrackCfg.byEnable)
    {
        g_StringLanType(szLan, "禁止跟踪", "Disable track");
        GetDlgItem(IDC_BTN_ENABLE_CALIBRATE)->SetWindowText(szLan);
    }
    else
    {
        g_StringLanType(szLan, "启用跟踪", "Enable track");
        GetDlgItem(IDC_BTN_ENABLE_CALIBRATE)->SetWindowText(szLan);
    }
    
    g_AddChanInfoToComBox(m_cmbVCARuleChannel, m_iDevIndex,TRUE);

    m_cmbVCARuleGroupNo.ResetContent();
    DWORD dwGroupNo = 0;
    if (g_struDeviceInfo[m_iDevIndex].iDeviceChanNum % MAX_CHANNUM_V30 != 0)
    {
        dwGroupNo = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum/MAX_CHANNUM_V30 + 1;
    }
    else
    {
       dwGroupNo = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum/MAX_CHANNUM_V30; 
    }

	//数字报警通道号是从33开始，前32个预留给模拟报警，所以第一组是33-64，第二组是65-128，这里加1组
    for (int i=0; i< dwGroupNo+1; i++)
    {
        sprintf(szLan,"The %dth Group", i+1);
        m_cmbVCARuleGroupNo.AddString(szLan);
    }

    m_cmbVCARuleGroupNo.SetCurSel(0);
    m_comboRuleID.SetCurSel(0);

    OnCbnSelchangeComboPositionChannel();

    GetDlgItem(IDC_COMBO_VCA_CHAN)->EnableWindow(FALSE);

	UpdateData(FALSE);
 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgVcaPositionRule::GetTrackCfg()
{
    DWORD dwReturn = 0;
    BOOL bRet = FALSE;
    char szLan[128] = {0};
    // get calibrate config
    bRet = NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_TRACK_CFG, m_iVcaChannel, &m_struTrackCfg, sizeof(m_struTrackCfg), &dwReturn);
    if (!bRet)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_TRACK_CFG");
        g_StringLanType(szLan, "获取标定配置失败", "Fail to get calibrate config");
        MessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_TRACK_CFG");
    }
    return bRet;
}

BOOL CDlgVcaPositionRule::SetTrackCfg()
{
    BOOL bRet = FALSE;
    char szLan[128] = {0};
    bRet = NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_TRACK_CFG, m_iVcaChannel, &m_struTrackCfg, sizeof(m_struTrackCfg));
    if (!bRet)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_TRACK_CFG");
        g_StringLanType(szLan, "设置标定配置失败", "Fail to set calibrate config");
        MessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_TRACK_CFG");
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
void CDlgVcaPositionRule::OnBtnSetRuleCfg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struRuleCfg.byPicProType = (unsigned char)m_comboProPicType.GetCurSel();
	m_struRuleCfg.struPictureParam.wPicSize = (unsigned short)m_comboResolution.GetCurSel();
	m_struRuleCfg.struPictureParam.wPicQuality = (unsigned short)m_comboPicQuality.GetCurSel();

	SetRuleBehaviorCfg();
}

/*********************************************************
  Function:	OnBtnSetVcaCtrl
  Desc:		Set Button function for VCA control
  Input:	
  Output:	
  Return:	void 
**********************************************************/
void CDlgVcaPositionRule::OnBtnSetVcaCtrl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int nChanIndex;
	nChanIndex = m_comboVcaChan.GetCurSel()+1;
	
	m_struVcaCtrlCfg.struCtrlInfo[nChanIndex-1].byVCAEnable = (unsigned char)m_bVcaActive;
	m_struVcaCtrlCfg.struCtrlInfo[nChanIndex-1].byVCAType = (unsigned char)m_comboVcaType.GetItemData(m_comboVcaType.GetCurSel());
	m_struVcaCtrlCfg.struCtrlInfo[nChanIndex-1].byStreamWithVCA = (unsigned char)m_comboStream.GetCurSel();
	
	if (m_struVcaCtrlCfg.struCtrlInfo[nChanIndex-1].byVCAType == VCA_ATM)
	{
		GetDlgItem(IDC_STATIC_ATM_MODE)->ShowWindow(SW_SHOW);
		m_comboAtmMode.ShowWindow(SW_SHOW);
		m_struVcaCtrlCfg.struCtrlInfo[nChanIndex-1].byMode = (BYTE)m_comboAtmMode.GetCurSel();
	}
	else
	{
		GetDlgItem(IDC_STATIC_ATM_MODE)->ShowWindow(SW_HIDE);
		m_comboAtmMode.ShowWindow(SW_HIDE);
	}

	if(!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_VCA_CTRLCFG, nChanIndex , &m_struVcaCtrlCfg, sizeof(NET_VCA_CTRLCFG)))
	{	
		
		char sbuf[128];
		sprintf(sbuf, "NET_DVR_SET_VCA_CTRLCFG ch%d failed", nChanIndex);
		MessageBox(sbuf);
		memcpy(&m_struVcaCtrlCfg, &g_pMainDlg->m_struVcaCtrlCfg,sizeof(NET_VCA_CTRLCFG));
		
		UpdateData(TRUE);
		m_comboVcaType.SetCurSel(m_struVcaCtrlCfg.struCtrlInfo[nChanIndex-1].byVCAType-1);
		m_bVcaActive = m_struVcaCtrlCfg.struCtrlInfo[nChanIndex-1].byVCAEnable;
		m_comboStream.SetCurSel(m_struVcaCtrlCfg.struCtrlInfo[nChanIndex-1].byStreamWithVCA);

		if (m_struVcaCtrlCfg.struCtrlInfo[nChanIndex-1].byVCAType == VCA_ATM)
		{
			GetDlgItem(IDC_STATIC_ATM_MODE)->ShowWindow(SW_SHOW);
			m_comboAtmMode.ShowWindow(SW_SHOW);
			m_comboAtmMode.SetCurSel(m_struVcaCtrlCfg.struCtrlInfo[nChanIndex-1].byMode);
		}
		else
		{
			GetDlgItem(IDC_STATIC_ATM_MODE)->ShowWindow(SW_HIDE);
			m_comboAtmMode.ShowWindow(SW_HIDE);
		}
        
		UpdateData(FALSE);
		
	}
	else
	{
		memcpy(&g_pMainDlg->m_struVcaCtrlCfg, &m_struVcaCtrlCfg,sizeof(NET_VCA_CTRLCFG));//copy as a globe member
		char sbuf[128];
		sprintf(sbuf, "NET_DVR_SET_VCA_CTRLCFG ch%d successfully", nChanIndex);
		MessageBox(sbuf);
		
		NET_VCA_CHAN_IN_PARAM struVcaChanInPara;
		memset(&struVcaChanInPara, 0, sizeof(NET_VCA_CHAN_IN_PARAM));
		struVcaChanInPara.byVCAType = m_struVcaCtrlCfg.struCtrlInfo[nChanIndex-1].byVCAType;
		struVcaChanInPara.byMode = m_struVcaCtrlCfg.struCtrlInfo[nChanIndex-1].byMode;
		GetVcaPara(nChanIndex, struVcaChanInPara);		
	}
}

/*********************************************************
  Function:	OnBtnRefesh
  Desc:		
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaPositionRule::OnBtnRefesh() 
{
	// TODO: Add your control notification handler code here
	OnInitDialog();
}

/*********************************************************
  Function:	OnBtnSetOneRule
  Desc:		
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaPositionRule::OnBtnSetOneRule() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    m_struRuleCfg.byPicProType = (unsigned char)m_comboProPicType.GetCurSel();
    m_struRuleCfg.struPictureParam.wPicSize = (unsigned short)m_comboResolution.GetCurSel();
	m_struRuleCfg.struPictureParam.wPicQuality = (unsigned short)m_comboPicQuality.GetCurSel();

   SaveOneRule(m_struOneRule);
/*	SetOneRule(m_struOneRule);

    GetRuleCfg();
    m_comboRuleID.SetCurSel(0);
    OnSelchangeComboRuleId();

    */
}

/*********************************************************
  Function:	OnBtnVcaRestart
  Desc:		Reboot VCA library 
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaPositionRule::OnBtnVcaRestart() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	if (!NET_VCA_RestartLib(m_lServerID, m_iVcaChannel))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_VCA_RestartLib %d", m_iVcaChannel);
		char sBufCn[128] =  {0};
		char sBufEn[128] = {0};
		sprintf(sBufCn, "智能通道%d智能库重启失败", m_iVcaChannel);
		sprintf(sBufEn, "VcaChannel%d failed to restart VCA library", m_iVcaChannel);
		g_StringLanType(szLan, sBufCn, sBufEn);
		MessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_VCA_RestartLib %d", m_iVcaChannel);
	}
}

/*********************************************************
  Function:	OnBtnSetVcaDrawMode
  Desc:		Set draw mode
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaPositionRule::OnBtnSetVcaDrawMode() 
{
	// TODO: Add your control notification handler code here
	SetVcaDrawMode();
}

/*********************************************************
Function:	GetDevVcaChanPara
Desc:		Get Channel Info from Device VCA Ability
Input:	
Output:	
Return:	void
**********************************************************/
void CDlgVcaPositionRule::GetDevVcaChanPara()
{
	m_iVcaChanNum = g_pMainDlg->m_struVcaDevAbility.byVCAChanNum;
	m_iPlateChanNum = g_pMainDlg->m_struVcaDevAbility.byPlateChanNum;
	m_iAtmChanNum = g_pMainDlg->m_struVcaDevAbility.byATMChanNum;
	m_iBBaseChanNum = g_pMainDlg->m_struVcaDevAbility.byBBaseChanNum;
	m_iBAdvanceChanNum = g_pMainDlg->m_struVcaDevAbility.byBAdvanceChanNum;
	m_iBFullChanNum = g_pMainDlg->m_struVcaDevAbility.byBFullChanNum;

	UpdateData(FALSE);

	memset(&m_struVcaCtrlCfg, 0,sizeof(NET_VCA_CTRLCFG));
	memcpy(&m_struVcaCtrlCfg, &g_pMainDlg->m_struVcaCtrlCfg,sizeof(NET_VCA_CTRLCFG));
	char sbuf[128];
	for (int i = 0; i < m_iVcaChanNum; i++)
	{
		sprintf(sbuf, "VCA Chan%d", i+1);
		m_comboVcaChan.InsertString(i,sbuf);
	}
	
	m_comboVcaChan.SetCurSel(0);
	InsertComboVcaType(); 
	OnSelchangeComboVcaChan();	
}

/*********************************************************
  Function:	OnSelchangeComboVcaChan
  Desc:		Modify combo Control
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaPositionRule::OnSelchangeComboVcaChan() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	//m_iVcaChannel = 1/*m_comboVcaChan.GetCurSel()+1*/; 
	SetComboVcaType();
	m_bVcaActive = m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byVCAEnable;
	EnableVcaWindow(m_bVcaActive);
	m_comboStream.SetCurSel(m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byStreamWithVCA);

	if (m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byVCAType == VCA_ATM)
	{
		GetDlgItem(IDC_STATIC_ATM_MODE)->ShowWindow(SW_SHOW);
		m_comboAtmMode.ShowWindow(SW_SHOW);
		m_comboAtmMode.SetCurSel(m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byMode);
	}
	else
	{
		GetDlgItem(IDC_STATIC_ATM_MODE)->ShowWindow(SW_HIDE);
		m_comboAtmMode.ShowWindow(SW_HIDE);
	}

	UpdateData(FALSE);

	
}

/*********************************************************
    Function: EnableVcaWindow
    Desc:	GUI Responding 
    Input:	BOOL bEnable
    Output:	
    Return:	BOOL 
**********************************************************/
BOOL CDlgVcaPositionRule::EnableVcaWindow(BOOL bEnable)
{
	GetDlgItem(IDC_COMBO_VCA_TYPE)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_STREAM)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_PRO_PIC_TYPE)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_SET_ONE_RULE)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_RULE_TYPE)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_RESOLUTION)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHK_RULE_ACTIVE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_RULE_NAME)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_DSP_ADD_TARGET)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_DSP_ADD_RULE)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_PIC_ADD_TARGET)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_PIC_ADD_RULE)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_SET_VCA_DRAW_MODE)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_PIC_QUALITY)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_VCA_RESTART)->EnableWindow(bEnable);
	GetDlgItem(ID_BTN_SET_RULE_CFG)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_FILTER_ACTIVE)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_SET_MINI_FILTER)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHK_DRAW_POLYGON)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_SET_MAX_FILTER)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_SENSITIVE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_ALARM_DELAY)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_ALARM_PERSIST)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECKHANDLETYPE1)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECKHANDLETYPE2)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECKHANDLETYPE3)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECKHANDLETYPE4)->EnableWindow(bEnable);
    GetDlgItem(IDC_CHK_PIC_CLOUD)->EnableWindow(bEnable);
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
	GetDlgItem(IDC_CHECKHANDLETYPE5)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MAX_DISTANCE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_DENSTITY_RATE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_READ_CARD_TIME_PERSIST)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_RULE_ID)->EnableWindow(bEnable);
	GetDlgItem(IDC_STATIC_ALARM_DIRECT)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMLINEALARMDIRECT)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHK_DRAW_LINE)->EnableWindow(bEnable);
	return TRUE;
}


/*********************************************************
  Function:	OnCheckVcaActive
  Desc:		
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaPositionRule::OnCheckVcaActive() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	EnableVcaWindow(m_bVcaActive);
	EnableRuleWindow(m_bVcaActive&&m_bRuleActive);
	UpdateData(FALSE);
}

/*********************************************************
Function:	GetVcaPara	
Desc:	Get VCA info 
Input:	int iChannel VCA Channel
		NET_VCA_CHAN_IN_PARAM struVcaChanInpara (Input Channel Ability parameter)
Output:	
Return:	BOOL 
**********************************************************/
BOOL CDlgVcaPositionRule::GetVcaPara(int iChannel,NET_VCA_CHAN_IN_PARAM struVcaChanInpara)
{
	UNREFERENCED_PARAMETER(iChannel);

	char szLan[128] = {0};
	if(!NET_DVR_GetDeviceAbility(m_lServerID,  VCA_CHAN_ABILITY, (char*)&struVcaChanInpara, \
		sizeof(NET_VCA_CHAN_IN_PARAM), (char*)&m_struBehaviorAbility, sizeof(NET_VCA_BEHAVIOR_ABILITY)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "VCA_CHAN_ABILITY");
		g_StringLanType(szLan, "获取智能通道能力失败", "Fail to Get Channel Ability");
		MessageBox(szLan);
		//OnCancel();
		//return FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "VCA_CHAN_ABILITY");
	}
	
//m_struBehaviorAbility.byMaxRuleNum = 8;
	if (!InsertRuleID(m_struBehaviorAbility.byMaxRuleNum)) //Insert Rule ID to ComboBox
	{
		return FALSE;
	}
	//set different Behavior according to different VCA Ability
	
//m_struBehaviorAbility.dwAbilityType = 0xffffffff;
	if(!InsertRuleType(m_struBehaviorAbility.dwAbilityType, m_struBehaviorAbility.dwAbilityTypeEx))
	{
		return FALSE;
	}

	//Get VCA info Overlay 
	if(!GetVcaDrawMode())
	{
		return FALSE;
	}
	
    //Get Config info
    m_comboPositionIndex.SetCurSel(0);
    OnSelchangeComboPositionIndex();
//     if(!GetRuleCfg())
//     {
//         return FALSE;
//     }

	UpdateData(FALSE);
	return TRUE;
}

/*********************************************************
Function:	InsertRuleType
Desc:	Insert Ability type in m_comboRuleType. 
Input:	int iBehaviorAbilityType
Output:	
Return:	BOOL 
**********************************************************/
BOOL CDlgVcaPositionRule::InsertRuleType(int iBehaviorAbilityType, int iBehaviorAbilityTypeEx)
{
    //iBehaviorAbilityType = 0xffffffff;
	m_comboRuleType.ResetContent();
	char szLan[128] = {0};
	int index = 0;
	if((iBehaviorAbilityType&TRAVERSE_PLANE_ABILITY) != 0)
	{
		g_StringLanType(szLan, "穿越警戒面", "Traverse Plane");
		m_comboRuleType.InsertString(index, szLan);
		m_comboRuleType.SetItemData(index, VCA_TRAVERSE_PLANE);
		index++;
	}
	if((iBehaviorAbilityType&ENTER_AREA_ABILITY) != 0)
	{
		g_StringLanType(szLan, "进入区域", "Enter Area");
		m_comboRuleType.InsertString(index, szLan);
		m_comboRuleType.SetItemData(index, VCA_ENTER_AREA);
		index++;
	}
	if((iBehaviorAbilityType&EXIT_AREA_ABILITY) != 0)
	{
		g_StringLanType(szLan, "离开区域", "Exit Area");
		m_comboRuleType.InsertString(index, szLan);
		m_comboRuleType.SetItemData(index, VCA_EXIT_AREA);
		index++;
	}
	if((iBehaviorAbilityType&INTRUSION_ABILITY) != 0)
	{
		g_StringLanType(szLan, "入侵", "Intrusion");
		m_comboRuleType.InsertString(index, szLan);
		m_comboRuleType.SetItemData(index, VCA_INTRUSION);
		index++;
	}
	if((iBehaviorAbilityType&LOITER_ABILITY) != 0)
	{
		g_StringLanType(szLan, "徘徊", "Loiter");
		m_comboRuleType.InsertString(index, szLan);
		m_comboRuleType.SetItemData(index, VCA_LOITER);
		index++;
	}
	if((iBehaviorAbilityType&LEFT_TAKE_ABILITY) != 0)
	{
		g_StringLanType(szLan, "物品遗留拿取", "Left and Take");
		m_comboRuleType.InsertString(index, szLan);
		m_comboRuleType.SetItemData(index, VCA_LEFT_TAKE);
		index++;
	}
	if((iBehaviorAbilityType&PARKING_ABILITY) != 0)
	{
		g_StringLanType(szLan, "停车", "Parking");
		m_comboRuleType.InsertString(index, szLan);
		m_comboRuleType.SetItemData(index, VCA_PARKING);
		index++;
	}
	if((iBehaviorAbilityType&RUN_ABILITY) != 0)
	{
		g_StringLanType(szLan, "快速移动", "Running");
		m_comboRuleType.InsertString(index, szLan);
		m_comboRuleType.SetItemData(index, VCA_RUN);
		index++;
	}
	if((iBehaviorAbilityType&HIGH_DENSITY_ABILITY) != 0)
	{
		g_StringLanType(szLan, "人员聚集", "Staff Density");
		m_comboRuleType.InsertString(index, szLan);
		m_comboRuleType.SetItemData(index, VCA_HIGH_DENSITY);
		index++;
	}
	if((iBehaviorAbilityType&STICK_UP_ABILITY) != 0)
	{
		m_comboRuleType.InsertString(index, "贴纸条");
		m_comboRuleType.SetItemData(index, VCA_STICK_UP);
		index++;
	}
	if ((iBehaviorAbilityType&INSTALL_SCANNER_ABILITY) != 0)
	{
		m_comboRuleType.InsertString(index, "安装读卡器");
		m_comboRuleType.SetItemData(index, (unsigned long)VCA_INSTALL_SCANNER);
		index++;
	}

	if((iBehaviorAbilityType&LECTURE_ABILITY) != 0)
	{
		m_comboRuleType.InsertString(index, "授课");
		m_comboRuleType.SetItemData(index,VCA_LECTURE);
		index++;
	}
	if ((iBehaviorAbilityType&ANSWER_ABILITY) != 0)
	{
		m_comboRuleType.InsertString(index, "回答问题");
		m_comboRuleType.SetItemData(index, VCA_ANSWER);
		index++;
	}
    if ((iBehaviorAbilityTypeEx&EVENT_COMBINED_ABILITY) != 0)
    {
        m_comboRuleType.InsertString(index, "组合规则事件");
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_COMBINED_RULE);
        index++;
	}

    if ((iBehaviorAbilityType&LEFT_ABILITY) != 0)
    {
        m_comboRuleType.InsertString(index, "物品遗留");
        m_comboRuleType.SetItemData(index, VCA_LEFT);
        index++;
    }

    if ((iBehaviorAbilityType&TAKE_ABILITY) != 0)
    {
        m_comboRuleType.InsertString(index, "物品拿取");
        m_comboRuleType.SetItemData(index, VCA_TAKE);
        index++;
    }

    if ((iBehaviorAbilityTypeEx&EVENT_TEACHER_WRITING) != 0)
    {
        m_comboRuleType.InsertString(index, "板书");
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_BLACKBOARD_WRITE);
        index++;
    }

    if ((iBehaviorAbilityType&VIOLENT_MOTION_ABILITY) != 0)
    {
        m_comboRuleType.InsertString(index, "剧烈运动");
        m_comboRuleType.SetItemData(index, VCA_VIOLENT_MOTION);
        index++;
    }

    if ((iBehaviorAbilityType&ADV_REACH_HEIGHT_ABILITY) != 0)
    {
        m_comboRuleType.InsertString(index, "折线攀高");
        m_comboRuleType.SetItemData(index, VCA_ADV_REACH_HEIGHT);
        index++;
    }

    if ((iBehaviorAbilityType&GET_UP_ABILITY) != 0)
    {
        m_comboRuleType.InsertString(index, "起身");
        m_comboRuleType.SetItemData(index, VCA_GET_UP);
        index++;
    }

    if ((iBehaviorAbilityType&LEAVE_POSITION) != 0)
    {
        m_comboRuleType.InsertString(index, "离岗");
        m_comboRuleType.SetItemData(index, VCA_LEAVE_POSITION);
        index++;
    }

    if ((iBehaviorAbilityType&STANDUP_ABILITY) != 0)
    {
        m_comboRuleType.InsertString(index, "起立");
        m_comboRuleType.SetItemData(index, VCA_STANDUP);
        index++;
    }

    if ((iBehaviorAbilityTypeEx&PEOPLENUM_CHANGE_ABILITY) != 0)
    {
        m_comboRuleType.InsertString(index, "人数变化");
        m_comboRuleType.SetItemData(index, ENUM_VCA_EVENT_PEOPLENUM_CHANGE);
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
BOOL CDlgVcaPositionRule::InsertRuleID(int RuleNum)
{
    m_comboRuleID.ResetContent();
	char sbuf[128] = {0};
    if (RuleNum <= 8)
    {
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
    } 
    else if (RuleNum > 8)
    {
        for (int i= 0; i < 16; i++)
        {	
            char szLan[128] = {0};
            char sBufCn[128] = {0};
            char sBufEn[128] = {0};
            sprintf(sBufCn, "规则%d", i);
            sprintf(sBufEn, "Rule%d", i);
            g_StringLanType(szLan,sBufCn,sBufEn);
            m_comboRuleID.InsertString(i,szLan);
    	}
    }

	return TRUE;
}

/*********************************************************
Function:	GetRuleCfg
Desc:	get rule parameter
Input:	
Output:	
Return:	BOOL 
**********************************************************/
BOOL CDlgVcaPositionRule::GetRuleCfg()
{
    int i = 0, j = 0;
	for(i = 0;i<MAX_RULE_NUM; i++)
	{
		m_bNeedRedraw[i] = FALSE;//Redraw polygon
		m_bCloseIn[i] = TRUE;//Polygon is closed or not
	}
	
	memset(&m_struRuleCfg, 0,sizeof(m_struRuleCfg));
	char szLan[128] = {0};

   /* if (!NET_DVR_GetPositionRule_V41(m_lServerID, m_iVcaChannel, m_iPositionIndex, &m_struPositionRule))
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetPositionRule_V41 Channel[%d]Position[%d]", m_iVcaChannel, m_iPositionIndex);
		char sbufCn[128] = {0};
		char sbufEn[128] = {0};
		sprintf(sbufCn, "获取通道%d行为规则信息失败",  m_iVcaChannel);
		sprintf(sbufEn, "Fail to get Channel%d VCA behavior rule", m_iVcaChannel);
		g_StringLanType(szLan, sbufCn, sbufEn);
		MessageBox(szLan);
        //OnCancel();
		return FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetPositionRule_V41 Channel[%d] Position[%d]",m_iVcaChannel, m_iPositionIndex);
        memcpy(&m_struRuleCfg, &m_struPositionRule.struVcaRuleCfg, sizeof(m_struRuleCfg));
        memcpy(&m_struPtzPosition, &m_struPositionRule.struPtzPosition, sizeof(m_struPtzPosition));

	}
    */
    memset(&m_struChanGroup, 0, sizeof(m_struChanGroup));
    m_struChanGroup.dwSize = sizeof(m_struChanGroup);
    m_struChanGroup.dwChannel = m_cmbVCARuleChannel.GetItemData(m_cmbVCARuleChannel.GetCurSel());
    m_struChanGroup.dwGroup = m_cmbVCARuleGroupNo.GetCurSel();
    m_struChanGroup.byID = m_comboPositionIndex.GetCurSel() + 1;
    //m_struChanGroup.dwPositionNo = 1;
    memset(&m_struRuleCfgV42, 0, sizeof(m_struRuleCfgV42));

    DWORD dwRetList = NET_DVR_NOERROR;
    BOOL bRet = NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_RULECFG_V42,1,&m_struChanGroup, sizeof(m_struChanGroup),&dwRetList,&m_struRuleCfgV42, sizeof(m_struRuleCfgV42));
    
    if (bRet)
    {
        if (dwRetList == NET_DVR_NOERROR)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_RULECFG_V42 Channel[%d] Position[%d]",m_struChanGroup.dwChannel,  m_struChanGroup.byID);
            memcpy(&m_struRuleCfg, &m_struPositionRule.struVcaRuleCfg, sizeof(m_struRuleCfg));
            m_struRuleCfg.dwSize = sizeof(m_struRuleCfg);
            m_struRuleCfg.byPicProType = m_struRuleCfgV42.byPicProType;
            m_struRuleCfg.byUpLastAlarm = m_struRuleCfgV42.byUpLastAlarm;
            m_struRuleCfg.byPicRecordEnable = m_struRuleCfgV42.byPicRecordEnable;
            memcpy(&m_struRuleCfg.struPictureParam, &m_struRuleCfgV42.struPicParam, sizeof(NET_DVR_JPEGPARA));
			m_comEventPriority.SetCurSel(m_struRuleCfgV42.struRule[m_iCurRuleID].byEventPriority);

           for (i = 0; i< MAX_REL_SNAPCHAN_NUM; i++)
           {
               m_struRuleCfg.wRelSnapChan[i] = m_struRuleCfgV42.wRelSnapChan[i];
           }
            
           for (i = 0; i< MAX_RULE_NUM_V42; i++)
           {
               if (i < 8)
               {
                   OneRuleV41ToOneRuleV42(&m_struRuleCfg.struRule[i], &m_struRuleCfgV42.struRule[i], FALSE);
               } 
               else
               {
                   OneRuleV41ToOneRuleV42(&m_struRuleCfgEx.struRule[i-8], &m_struRuleCfgV42.struRule[i], FALSE);
               }
               m_struRuleCfg.struRule[i].wAlarmDelay = m_struRuleCfgV42.struRule[i].wAlarmDelay;
           }
           
           memcpy(&m_struPtzPosition, &m_struRuleCfgV42.struPTZPosition, sizeof(m_struPtzPosition)); 
        } 
        else
        {
            sprintf(szLan,"NET_DVR_GET_RULECFG_V42 Error[%s][%d]",NET_DVR_GetErrorMsg(), NET_DVR_GetLastError());
            AfxMessageBox(szLan);
            return FALSE;
        }
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_RULECFG_V42 Channel[%d]Position[%d]", m_struChanGroup.dwChannel,  m_struChanGroup.byID);
        return FALSE;
    }

   

	m_bChkTrackEn = m_struPositionRule.byTrackEnable;
	m_dwTrackTime = m_struPositionRule.wTrackDuration;

    m_csPtzPositionName = m_struPtzPosition.byPtzPositionName;
	m_bChkPositionEn = m_struPtzPosition.byEnable;
 
    
    m_comboProPicType.SetCurSel(m_struRuleCfg.byPicProType); //get Action for alarm
	m_comboResolution.SetCurSel(m_struRuleCfg.struPictureParam.wPicSize);//Image resolution
	m_comboPicQuality.SetCurSel(m_struRuleCfg.struPictureParam.wPicQuality);//Image quality 0-best 1-better 2-normal
	
	m_comboRuleID.SetCurSel(0);
	m_iCurRuleID = 0;
	memcpy(&m_struOneRule, &m_struRuleCfg.struRule[m_iCurRuleID], sizeof(NET_VCA_ONE_RULE_V41));
	m_comEventPriority.SetCurSel(m_struRuleCfgV42.struRule[m_iCurRuleID].byEventPriority);

	m_bRuleActive = m_struOneRule.byActive;
	EnableRuleWindow(m_bRuleActive);
 	SetRuleActiveAble(m_bRuleActive);
 	//Config rule name
 	m_csRuleName = m_struOneRule.byRuleName;

	GetEventTypeSet(m_struOneRule.dwEventType, m_struOneRule.wEventTypeEx);

	memcpy(&m_struAlarmTime[0][0],&m_struOneRule.struAlarmTime[0][0], MAX_DAYS*MAX_TIMESEGMENT_V30*sizeof(NET_DVR_SCHEDTIME));
	return TRUE;
}

/*********************************************************
Function:	GetEventTypeSet
Desc:	Get Event type
Input:	VCA_EVENT_TYPE struEventType 
Output:	
Return:	BOOL 
**********************************************************/
BOOL CDlgVcaPositionRule::GetEventTypeSet(VCA_EVENT_TYPE struEventType, WORD wEventType)
{
    if (wEventType != 0)
	{
        for (int i = 0; i < m_comboRuleType.GetCount(); i++) //loop and compare m_comboRuleType
        {
            if (m_comboRuleType.GetItemData(i) == wEventType)
            {
                m_comboRuleType.SetCurSel(i);
                return TRUE;
            }
        }
        EventTypeExToEventType(struEventType, wEventType);
        for (int i = 0; i < 128; i++) //loop and compare m_comboRuleType
        {
            if ((VCA_EVENT_TYPE)m_comboRuleType.GetItemData(i) == struEventType)
            {
                m_comboRuleType.SetCurSel(i);
                return TRUE;
            }
        }
	}
    else
    {
        for (int i = 0; i < 128; i++) //loop and compare m_comboRuleType
        {
            if ((VCA_EVENT_TYPE)m_comboRuleType.GetItemData(i) == struEventType)
            {
                m_comboRuleType.SetCurSel(i);
                return TRUE;
            }
        }
    }

	return FALSE;
}
/*********************************************************
Function:	SetRuleActiveAble
Desc:	
Input:	bEnable
Output:	
Return:	BOOL 
**********************************************************/
BOOL CDlgVcaPositionRule::SetRuleActiveAble(BOOL bEnable)
{
	m_comboRuleType.EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_RULE_NAME)->EnableWindow(bEnable);
	return TRUE;
}

/*********************************************************
Function:	GetVcaDrawMode
Desc:		Get target added info
Input:	
Output:	
Return:	BOOL 
**********************************************************/
BOOL CDlgVcaPositionRule::GetVcaDrawMode()
{
	memset(&m_struVCADrawMode, 0, sizeof(NET_VCA_DRAW_MODE));
	char szLan[128] = {0};
	if(!NET_DVR_GetVCADrawMode(m_lServerID,  m_iVcaChannel, &m_struVCADrawMode))	
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_VCA_DRAW_MODE %d", m_iVcaChannel);
		char sbufCn[128] = {0};
		char sbufEn[128] = {0};
		sprintf(sbufCn,"Get Target added info of channel %d failed", m_iVcaChannel);
		sprintf(sbufEn, "Get Target added info of channel %d failed");
		g_StringLanType(szLan, sbufCn, sbufEn);
		OnCancel();
		return FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_VCA_DRAW_MODE %d", m_iVcaChannel);
	}
	m_bDSPAddRule = m_struVCADrawMode.byDspAddRule;
	m_bDSPAddTarget = m_struVCADrawMode.byDspAddTarget;
	m_bPicAddRule = m_struVCADrawMode.byDspPicAddRule;
	m_bPicAddTarget = m_struVCADrawMode.byDspPicAddTarget;
	return TRUE;
}

/*********************************************************
  Function:	OnSelchangeComboRuleId
  Desc:		Modify combo for rule ID
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaPositionRule::OnSelchangeComboRuleId() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    //SaveOneRule(m_struOneRule);

	m_iCurRuleID = m_comboRuleID.GetCurSel();
	m_comEventPriority.SetCurSel(m_struRuleCfgV42.struRule[m_iCurRuleID].byEventPriority);
    if (m_iCurRuleID<8)
    {
        memcpy(&m_struOneRule, &m_struRuleCfg.struRule[m_iCurRuleID], sizeof(m_struOneRule));
    } 
    else
    {
        memcpy(&m_struOneRule, &m_struRuleCfgEx.struRule[m_iCurRuleID - 8], sizeof(m_struOneRule));
    }

	m_bRuleActive = m_struOneRule.byActive;
	EnableRuleWindow(m_bRuleActive);
	SetRuleActiveAble(m_bRuleActive);
	//config rule name
	m_csRuleName = m_struOneRule.byRuleName;
    if (0 != m_struOneRule.wEventTypeEx)
    {   
        //VCA_EVENT_TYPE dwEventType;
        if (!EventTypeExToEventType(m_struOneRule.dwEventType, m_struOneRule.wEventTypeEx))
        {
            m_struOneRule.dwEventType = (VCA_EVENT_TYPE)0;
            for (int i = 0;  i < 128; i++) //loop and compare m_comboRuleType
            {
                if((VCA_EVENT_TYPE)m_comboRuleType.GetItemData(i) == m_struOneRule.wEventTypeEx)
                {
                    m_comboRuleType.SetCurSel(i);
                    break;
                }
        	}
        }
        else
        {
            GetEventTypeSet(m_struOneRule.dwEventType);
        }
        
    }
    else
    {
	    GetEventTypeSet(m_struOneRule.dwEventType);
    }

	RefreshOneRule(m_struOneRule);
	UpdateData(FALSE);
}

/*********************************************************
Function:	RefreshOneRule
Desc:	refresh a rule
Input:	NET_VCA_ONE_RULE_V41 struVcaOneRule
Output:	
Return:	BOOL 
**********************************************************/
BOOL CDlgVcaPositionRule::RefreshOneRule(NET_VCA_ONE_RULE_V41 struVcaOneRule)
{
	ShowRuleTypeWnd(struVcaOneRule.dwEventType, struVcaOneRule.wEventTypeEx); //setup display for different rules
	
	m_bHandleType1 = (struVcaOneRule.struHandleType.dwHandleType) &0x01;
	m_bHandleType2 = (struVcaOneRule.struHandleType.dwHandleType>>1)&0x01;
	m_bHandleType3 = (struVcaOneRule.struHandleType.dwHandleType>>2)&0x01;
	m_bHandleType4 = (struVcaOneRule.struHandleType.dwHandleType>>3)&0x01;
	m_bHandleType5 = (struVcaOneRule.struHandleType.dwHandleType>>4)&0x01;
    m_bHandleType6 = (struVcaOneRule.struHandleType.dwHandleType >> 12) & 0x01;
	ShowAlarmNum(struVcaOneRule, MAX_ALARMOUT_V30);
	//m_listAlarmOut.EnableWindow(m_bHandleType4);
	
	m_comboWeekday.SetCurSel(0);
	m_comboCopyTime.SetCurSel(0);

	memcpy(&m_struAlarmTime[0][0],&struVcaOneRule.struAlarmTime[0][0],
		MAX_DAYS*MAX_TIMESEGMENT_V30*sizeof(NET_DVR_SCHEDTIME));
	m_iHour11 = m_struAlarmTime[0][0].byStartHour;
	m_iMin11 = m_struAlarmTime[0][0].byStartMin;
	m_iHour12 = m_struAlarmTime[0][0].byStopHour;
	m_iMin12 = m_struAlarmTime[0][0].byStopMin;
	m_iHour21 = m_struAlarmTime[0][1].byStartHour;
	m_iMin21 = m_struAlarmTime[0][1].byStartMin;
	m_iHour22 = m_struAlarmTime[0][1].byStopHour;
	m_iMin22 = m_struAlarmTime[0][1].byStopMin;

	m_iHour31 = m_struAlarmTime[0][2].byStartHour;
	m_iMin31 = m_struAlarmTime[0][2].byStartMin;
	m_iHour32 = m_struAlarmTime[0][2].byStopHour;
	m_iMin32 = m_struAlarmTime[0][2].byStopMin;
	m_iHour41 = m_struAlarmTime[0][3].byStartHour;
	m_iMin41 = m_struAlarmTime[0][3].byStartMin;
	m_iHour42 = m_struAlarmTime[0][3].byStopHour;
	m_iMin42 = m_struAlarmTime[0][3].byStopMin;

	m_iHour51 = m_struAlarmTime[0][4].byStartHour;
	m_iMin51 = m_struAlarmTime[0][4].byStartMin;
	m_iHour52 = m_struAlarmTime[0][4].byStopHour;
	m_iMin52 = m_struAlarmTime[0][4].byStopMin;
	m_iHour61 = m_struAlarmTime[0][5].byStartHour;
	m_iMin61 = m_struAlarmTime[0][5].byStartMin;
	m_iHour62 = m_struAlarmTime[0][5].byStopHour;
	m_iMin62 = m_struAlarmTime[0][5].byStopMin;

	m_iHour71 = m_struAlarmTime[0][6].byStartHour;
	m_iMin71 = m_struAlarmTime[0][6].byStartMin;
	m_iHour72 = m_struAlarmTime[0][6].byStopHour;
	m_iMin72 = m_struAlarmTime[0][6].byStopMin;
	m_iHour81 = m_struAlarmTime[0][7].byStartHour;
	m_iMin81 = m_struAlarmTime[0][7].byStartMin;
	m_iHour82 = m_struAlarmTime[0][7].byStopHour;
	m_iMin82 = m_struAlarmTime[0][7].byStopMin;
	
	
	//Setup Filter
	m_bFilterActive = struVcaOneRule.struSizeFilter.byActive;
	GetDlgItem(IDC_CHECK_SET_MAX_FILTER)->EnableWindow(m_bFilterActive);
	GetDlgItem(IDC_CHECK_SET_MINI_FILTER)->EnableWindow(m_bFilterActive);
	
	GetEventParaSet(struVcaOneRule.dwEventType, struVcaOneRule.uEventParam, struVcaOneRule.wEventTypeEx);
	
    int i = 0;
	//Setup record channel
    for ( i = 0; i< MAX_CHANNUM_V30;i++)
    {
        m_pbChannel[i] = struVcaOneRule.byRelRecordChan[i];
    }
	g_CreateChannelTree(m_treeChannel,m_iDevIndex,m_pbChannel);
	

    for ( i = 0; i< MAX_ALARMOUT_V30;i++)
    {
        m_pbAlarmOut[i] = struVcaOneRule.struHandleType.byRelAlarmOut[i];
    }
	g_CreateAlarmOutTree(m_treeAlarmout,m_iDevIndex,m_pbAlarmOut);
	
	UpdateData(FALSE);
	return TRUE;
}

/*********************************************************
Function:	F_ShowRecordChan
Desc:		show recording channel
Input:	NET_VCA_ONE_RULE_V41 struVcaOneRule
		int nChanNum
Output:	
Return:	BOOL 
**********************************************************/
BOOL CDlgVcaPositionRule::F_ShowRecordChan(NET_VCA_ONE_RULE_V41 struVcaOneRule, int nChanNum)
{
    //
/*	m_listRecordChan.SetExtendedStyle(LVS_EX_CHECKBOXES);
	char szLan[128] = {0};
	char sbufCn[128] = {0};
	char sbufEn[128] = {0};

	m_listRecordChan.DeleteAllItems();
	for (i = 0; i < nChanNum; i++)
	{
		sprintf(sbufCn, "通道%d", (i+1));
		sprintf(sbufEn, "Channel%d", (i+1));
		g_StringLanType(szLan, sbufCn, sbufEn);
		m_listRecordChan.InsertItem(i, szLan);
	}

	for (i = 0; i < nChanNum; i++ )
	{
		if (struVcaOneRule.byRelRecordChan[i])
		{
			m_listRecordChan.SetCheck(i);
		}
		
	}
   	*/

	return TRUE;
}

/*********************************************************
Function:	ShowRuleTypeWnd
Desc:	According to event type, show or Hide correlative control
Input:	VCA_EVENT_TYPE struEventType
Output:	
Return:	 BOOL 
**********************************************************/
BOOL CDlgVcaPositionRule::ShowRuleTypeWnd(VCA_EVENT_TYPE struEventType, WORD wEventTypeEx)
{
	// Show correlative control and hide others.

	m_staticAlarmDelay.ShowWindow(SW_HIDE);
	m_staticAlarmPersist.ShowWindow(SW_HIDE);
	m_staticMaxDistance.ShowWindow(SW_HIDE);
	m_staticDenstityRate.ShowWindow(SW_HIDE);
	m_staticReadCardTimePersist.ShowWindow(SW_HIDE);

	m_editReadCardTimePersist.ShowWindow(SW_HIDE);
	m_editAlarmDelay.ShowWindow(SW_HIDE);
	m_editDenstityRate.ShowWindow(SW_HIDE);
	m_editMaxDistance.ShowWindow(SW_HIDE);
	m_editAlarmPersist.ShowWindow(SW_HIDE);

	m_staticAlarmDelayArea.ShowWindow(SW_HIDE);
	m_staticAlarmPersistArea.ShowWindow(SW_HIDE);
	m_staticMaxDistanceArea.ShowWindow(SW_HIDE);
	m_staticDenstityRateArea.ShowWindow(SW_HIDE);
	m_staticReadCardTimePersistArea.ShowWindow(SW_HIDE);
	m_staticStickupAlarmPersist.ShowWindow(SW_HIDE);
		
	GetDlgItem(IDC_CHK_DRAW_LINE)->ShowWindow(SW_HIDE);
	m_staticAlarmDirect.ShowWindow(SW_HIDE);
	m_comboAlarmDirect.ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHK_DRAW_POLYGON)->ShowWindow(SW_HIDE);

    GetDlgItem(IDC_STATIC_RULE_SEQ)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO_RULE_SEQ)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_MIN_INTERVAL)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_EDIT_MIN_INTERVAL)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_MAX_INTERVAL)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_EDIT_MAX_INTERVAL)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_RULE1)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_EDIT_RULE1)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_STATIC_RULE2)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_EDIT_RULE2)->ShowWindow(SW_HIDE);

    GetDlgItem(IDC_EDIT_PARAM1)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_EDIT_PARAM2)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_EDIT_PARAM3)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_EDIT_PARAM4)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_EDIT_PARAM5)->ShowWindow(SW_HIDE);

	m_comboTrackingMode.EnableWindow(FALSE);
	m_comboZoomMode.EnableWindow(FALSE);

	if (struEventType == VCA_TRAVERSE_PLANE)
	{
		GetDlgItem(IDC_CHK_DRAW_LINE)->ShowWindow(SW_SHOW);
		m_staticAlarmDirect.ShowWindow(SW_SHOW);
		m_comboAlarmDirect.ShowWindow(SW_SHOW);
		m_bDrawLine = FALSE;
		m_bDrawPolygon = FALSE;
		memset(&m_struVcaPolygon[m_iCurRuleID], 0, sizeof(NET_VCA_LINE));

	}
	else
	{
		GetDlgItem(IDC_CHK_DRAW_POLYGON)->ShowWindow(SW_SHOW);
		m_bDrawLine = FALSE;
		m_bDrawPolygon = FALSE;
		memset(&m_struVcaLine[m_iCurRuleID], 0, sizeof(NET_VCA_LINE));

        GetDlgItem(IDC_COMBO_SENSITIVE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_SENSITIVITY)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_DURATION)->ShowWindow(SW_SHOW);

		if (struEventType == VCA_ENTER_AREA)
		{
		}
		else if (struEventType == VCA_EXIT_AREA)
		{
		}
		else if (struEventType == VCA_INTRUSION || struEventType == VCA_LECTURE)
		{
			m_staticAlarmDelay.ShowWindow(SW_SHOW);
			m_staticAlarmDelayArea.ShowWindow(SW_SHOW);
			m_editAlarmDelay.ShowWindow(SW_SHOW);

			m_comboTrackingMode.EnableWindow(TRUE);
			m_comboZoomMode.EnableWindow(TRUE);

		}
		else if (struEventType == VCA_LOITER)
		{
			m_staticAlarmPersist.ShowWindow(SW_SHOW);
			m_staticAlarmPersistArea.ShowWindow(SW_SHOW);

			m_editAlarmPersist.ShowWindow(SW_SHOW);

		}
		else if (struEventType == VCA_LEFT_TAKE)
		{
			m_staticAlarmPersist.ShowWindow(SW_SHOW);
			m_staticAlarmPersistArea.ShowWindow(SW_SHOW);
			m_editAlarmPersist.ShowWindow(SW_SHOW);
		}
		else if (struEventType == VCA_PARKING)
		{
			m_staticAlarmPersist.ShowWindow(SW_SHOW);
			m_staticAlarmPersistArea.ShowWindow(SW_SHOW);
			m_editAlarmPersist.ShowWindow(SW_SHOW);
		}
		else if (struEventType == VCA_RUN)
		{
			m_staticMaxDistance.ShowWindow(SW_SHOW);
			m_staticMaxDistanceArea.ShowWindow(SW_SHOW);
			m_editMaxDistance.ShowWindow(SW_SHOW);
		}
		else if (struEventType == VCA_HIGH_DENSITY)
		{
			m_staticDenstityRate.ShowWindow(SW_SHOW);
			m_staticDenstityRateArea.ShowWindow(SW_SHOW);
			m_editDenstityRate.ShowWindow(SW_SHOW);
		}
		else if (struEventType == VCA_STICK_UP)
		{
			m_staticStickupAlarmPersist.ShowWindow(SW_SHOW);
			m_staticAlarmPersist.ShowWindow(SW_SHOW);
			m_editAlarmPersist.ShowWindow(SW_SHOW);
		}
		else if (struEventType == VCA_INSTALL_SCANNER)
		{
			m_staticReadCardTimePersist.ShowWindow(SW_SHOW);
			m_staticReadCardTimePersistArea.ShowWindow(SW_SHOW);
			m_editReadCardTimePersist.ShowWindow(SW_SHOW);
		}
        else if (struEventType == VCA_LEFT)
        {
                m_staticAlarmPersist.ShowWindow(SW_SHOW);
                m_staticAlarmPersistArea.ShowWindow(SW_SHOW);
                m_editAlarmPersist.ShowWindow(SW_SHOW);
        }
        else if (struEventType == VCA_TAKE)
        {
            m_staticAlarmPersist.ShowWindow(SW_SHOW);
            m_staticAlarmPersistArea.ShowWindow(SW_SHOW);
            m_editAlarmPersist.ShowWindow(SW_SHOW);
        }
        else if (wEventTypeEx == ENUM_VCA_EVENT_COMBINED_RULE)
        {
            GetDlgItem(IDC_STATIC_RULE_SEQ)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_COMBO_RULE_SEQ)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_STATIC_MIN_INTERVAL)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_MIN_INTERVAL)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_STATIC_MAX_INTERVAL)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_MAX_INTERVAL)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_STATIC_RULE1)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_RULE1)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_STATIC_RULE2)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_RULE2)->ShowWindow(SW_SHOW);
		}
        else if (struEventType == VCA_VIOLENT_MOTION || struEventType == VCA_GET_UP || struEventType == VCA_LEAVE_POSITION || struEventType == VCA_STANDUP
            || struEventType == VCA_ADV_REACH_HEIGHT || wEventTypeEx == ENUM_VCA_EVENT_PEOPLENUM_CHANGE)
        {
            GetDlgItem(IDC_COMBO_SENSITIVE)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_STATIC_SENSITIVITY)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_STATIC_DURATION)->ShowWindow(SW_HIDE);

            GetDlgItem(IDC_EDIT_PARAM1)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_PARAM2)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_PARAM3)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_PARAM4)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_PARAM5)->ShowWindow(SW_SHOW);
        }
		else
		{
			return FALSE;
		}
	}
	return TRUE;	
}

/*********************************************************
Function:	ShowAlarmNum
Desc:	shwo alarm output channel
Input:	NET_VCA_ONE_RULE_V41 struVcaOneRule
		int nAlarmNum
Output:	
Return:	void 
**********************************************************/
void CDlgVcaPositionRule::ShowAlarmNum(NET_VCA_ONE_RULE_V41 struVcaOneRule,int nAlarmNum)
{
	/*m_treeChannel.DeleteAllItems();
	m_treeChannel.SetExtendedStyle(LVS_EX_CHECKBOXES);
	char szLan[128] = {0};
	char sbufCn[128] = {0};
	char sbufEn[128] = {0};
	int i;
	for (i = 0; i < nAlarmNum; i++)
	{
		sprintf(sbufCn, "输出%d", (i+1));
		sprintf(sbufEn, "Channel%d", (i+1));
		g_StringLanType(szLan, sbufCn, sbufEn);
		m_listAlarmOut.InsertItem(i, szLan);
	}
	for (i = 0; i < nAlarmNum; i++ )
	{
		if (struVcaOneRule.struHandleType.byRelAlarmOut[i])
		{
			m_listAlarmOut.SetCheck(i);
		}
	}
    */
	
//    g_CreateAlarmOutTree(m_treeAlarmout,m_iDevIndex,&struVcaOneRule.struHandleType.byRelAlarmOut);
}

/*********************************************************
Function:	GetEventParaSet
Desc:	Get and display Event Parameters
Input:	VCA_EVENT_TYPE struEventType
		NET_VCA_EVENT_UNION uEventParam
Output:	
Return:	void 
**********************************************************/
void CDlgVcaPositionRule::GetEventParaSet(VCA_EVENT_TYPE struEventType,NET_VCA_EVENT_UNION uEventParam, WORD wEventTypeEx)
{
    char szLan[120] = { 0 };
	BYTE bySensitivity = 0;
	switch (struEventType)
	{
	case VCA_TRAVERSE_PLANE:
        m_comboAlarmDirect.SetCurSel(uEventParam.struTraversePlane.dwCrossDirection);
        m_comDetTarget.SetCurSel(uEventParam.struTraversePlane.byDetectionTarget);
        m_comboPriority.SetCurSel(uEventParam.struTraversePlane.byPriority);
          bySensitivity = uEventParam.struTraversePlane.bySensitivity;
		OnSelchangeComlinealarmdirect();
		memcpy(&m_struVcaLine[m_iCurRuleID], &uEventParam.struTraversePlane.struPlaneBottom, sizeof(NET_VCA_LINE));
		break;
	case VCA_ENTER_AREA:
        m_comDetTarget.SetCurSel(uEventParam.struArea.byDetectionTarget);
        m_comboPriority.SetCurSel(uEventParam.struArea.byPriority);
        bySensitivity = uEventParam.struArea.bySensitivity;
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struArea.struRegion, sizeof(NET_VCA_POLYGON));
		break;
	case VCA_EXIT_AREA:
		m_comDetTarget.SetCurSel(uEventParam.struArea.byDetectionTarget);
        m_comboPriority.SetCurSel(uEventParam.struArea.byPriority);
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struArea.struRegion, sizeof(NET_VCA_POLYGON));
        bySensitivity = uEventParam.struArea.bySensitivity;
		break;
	case VCA_INTRUSION:
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struIntrusion.struRegion, sizeof(NET_VCA_POLYGON));
		m_iAlarmDelay = uEventParam.struIntrusion.wDuration;
		m_comDetTarget.SetCurSel(uEventParam.struIntrusion.byDetectionTarget);
        m_comboPriority.SetCurSel(uEventParam.struIntrusion.byPriority);
        bySensitivity = uEventParam.struIntrusion.bySensitivity;
		m_staticAlarmDelay.ShowWindow(SW_SHOW);
		m_staticAlarmDelayArea.ShowWindow(SW_SHOW);
		m_editAlarmDelay.ShowWindow(SW_SHOW);
		break;
	case VCA_LOITER:
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struLoiter.struRegion, sizeof(NET_VCA_POLYGON));
		m_iAlarmPersist	= uEventParam.struLoiter.wDuration;
        bySensitivity = uEventParam.struLoiter.bySensitivity;
		m_staticAlarmPersist.ShowWindow(SW_SHOW);
		m_staticAlarmPersistArea.ShowWindow(SW_SHOW);
		m_editAlarmPersist.ShowWindow(SW_SHOW);
		break;
	case VCA_LEFT_TAKE:
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struTakeTeft.struRegion, sizeof(NET_VCA_POLYGON));
		m_iAlarmPersist	= uEventParam.struTakeTeft.wDuration;
		m_staticAlarmPersist.ShowWindow(SW_SHOW);
		m_staticAlarmPersistArea.ShowWindow(SW_SHOW);
		m_editAlarmPersist.ShowWindow(SW_SHOW);
		break;
	case VCA_PARKING:
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struParking.struRegion, sizeof(NET_VCA_POLYGON));
		m_iAlarmPersist	= uEventParam.struParking.wDuration;
        bySensitivity = uEventParam.struParking.bySensitivity;
		m_staticAlarmPersist.ShowWindow(SW_SHOW);
		m_staticAlarmPersistArea.ShowWindow(SW_SHOW);
		m_editAlarmPersist.ShowWindow(SW_SHOW);
		break;
	case VCA_RUN:
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struRun.struRegion, sizeof(NET_VCA_POLYGON));
		m_fMaxDistance = uEventParam.struRun.fRunDistance;
		m_comDetTarget.SetCurSel(uEventParam.struRun.byDetectionTarget);
        bySensitivity = uEventParam.struRun.bySensitivity;
		m_staticMaxDistance.ShowWindow(SW_SHOW);
		m_staticMaxDistanceArea.ShowWindow(SW_SHOW);
		m_editMaxDistance.ShowWindow(SW_SHOW);
		break;
	case VCA_HIGH_DENSITY:
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struHighDensity.struRegion, sizeof(NET_VCA_POLYGON));
		m_fDenstityRate = uEventParam.struHighDensity.fDensity;
		m_staticDenstityRate.ShowWindow(SW_SHOW);
		m_staticDenstityRateArea.ShowWindow(SW_SHOW);
		m_editDenstityRate.ShowWindow(SW_SHOW);
		break;
	case VCA_STICK_UP:
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struStickUp.struRegion, sizeof(NET_VCA_POLYGON));
		m_iAlarmPersist = uEventParam.struStickUp.wDuration;
		m_staticAlarmPersist.ShowWindow(SW_SHOW);
		m_staticStickupAlarmPersist.ShowWindow(SW_SHOW);
		m_editAlarmPersist.ShowWindow(SW_SHOW);
		break;
	case VCA_INSTALL_SCANNER:
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struScanner.struRegion, sizeof(NET_VCA_POLYGON));
		m_iReadCardTimePersist	 = uEventParam.struScanner.wDuration;
		m_staticReadCardTimePersist.ShowWindow(SW_SHOW);
		m_staticReadCardTimePersistArea.ShowWindow(SW_SHOW);
		m_editReadCardTimePersist.ShowWindow(SW_SHOW);
		break;
	case VCA_LECTURE:
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struLecture.struRegion, sizeof(NET_VCA_POLYGON));
		m_iAlarmDelay = uEventParam.struLecture.wDuration;
		bySensitivity = uEventParam.struLecture.bySensitivity;
		m_comboTrackingMode.SetCurSel(uEventParam.struLecture.byTrackingMode);
		m_comboZoomMode.SetCurSel(uEventParam.struLecture.byZoomMode);
		m_staticAlarmDelay.ShowWindow(SW_SHOW);
		m_staticAlarmDelayArea.ShowWindow(SW_SHOW);
		m_editAlarmDelay.ShowWindow(SW_SHOW);
		break;
	case VCA_ANSWER:
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struAnswer.struRegion, sizeof(NET_VCA_POLYGON));
		bySensitivity = uEventParam.struAnswer.bySensitivity;
		break;
    case VCA_LEFT:
        memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struLeft.struRegion, sizeof(NET_VCA_POLYGON));
        m_iAlarmPersist	= uEventParam.struLeft.wDuration;
        bySensitivity = uEventParam.struAnswer.bySensitivity;
        m_staticAlarmPersist.ShowWindow(SW_SHOW);
        m_staticAlarmPersistArea.ShowWindow(SW_SHOW);
        m_editAlarmPersist.ShowWindow(SW_SHOW);
		break;
    case VCA_TAKE:
        memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struTake.struRegion, sizeof(NET_VCA_POLYGON));
        m_iAlarmPersist	= uEventParam.struTake.wDuration;
         bySensitivity = uEventParam.struTake.bySensitivity;
        m_staticAlarmPersist.ShowWindow(SW_SHOW);
        m_staticAlarmPersistArea.ShowWindow(SW_SHOW);
        m_editAlarmPersist.ShowWindow(SW_SHOW);
		break;

    case VCA_VIOLENT_MOTION:
        memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struViolentMotion.struRegion, sizeof(NET_VCA_POLYGON));

        sprintf(szLan, "m_struVcaPolygon[m_iCurRuleID].dwPointNum == %d\n", m_struVcaPolygon[m_iCurRuleID].dwPointNum);
        OutputDebugString(szLan);
        m_iParam1 = uEventParam.struViolentMotion.wDuration;
        m_iParam2 = uEventParam.struViolentMotion.bySensitivity;
        m_iParam3 = uEventParam.struViolentMotion.byMode;
        break;

    case VCA_GET_UP:
        memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struGetUp.struRegion, sizeof(NET_VCA_POLYGON));
        m_iParam1 = uEventParam.struGetUp.wDuration;
        m_iParam2 = uEventParam.struGetUp.bySensitivity;
        m_iParam3 = uEventParam.struGetUp.byMode;
        break;

    case VCA_LEAVE_POSITION:
        memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struLeavePos.struRegion, sizeof(NET_VCA_POLYGON));
        m_iParam1 = uEventParam.struLeavePos.wLeaveDelay;
        m_iParam2 = uEventParam.struLeavePos.wStaticDelay;
        m_iParam3 = uEventParam.struLeavePos.byMode;
        m_iParam4 = uEventParam.struLeavePos.byPersonType;
        m_iParam5 = uEventParam.struLeavePos.byOnPosition;
        m_iParam6 = uEventParam.struLeavePos.bySensitivity;
        break;

    case VCA_ADV_REACH_HEIGHT:
        memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struReachHeight.struRegion, sizeof(NET_VCA_POLYGON));
        m_iParam1 = uEventParam.struReachHeight.dwCrossDirection;
        break;

    case VCA_STANDUP:
        memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struStandUp.struRegion, sizeof(NET_VCA_POLYGON));
        m_iParam1 = uEventParam.struStandUp.bySensitivity;
        m_iParam2 = uEventParam.struStandUp.byHeightThreshold;
        m_iParam3 = uEventParam.struStandUp.wDuration;
        break;

	default:
		break;
	}

    switch (wEventTypeEx)
	{
    case ENUM_VCA_EVENT_COMBINED_RULE:
        m_comboRuleSequence.SetCurSel(uEventParam.struCombinedRule.byRuleSequence);
        m_dwMinInterval = uEventParam.struCombinedRule.dwMinInterval;
        m_dwMaxInterval = uEventParam.struCombinedRule.dwMaxInterval;
        m_byRuleID1 = uEventParam.struCombinedRule.struRule1Raram.byRuleID;
        m_byRuleID2 = uEventParam.struCombinedRule.struRule2Raram.byRuleID;
        break;
    case ENUM_VCA_EVENT_BLACKBOARD_WRITE:
        memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struBlackboardWrite.struRegion, sizeof(NET_VCA_POLYGON));
        break;
    case ENUM_VCA_EVENT_PEOPLENUM_CHANGE:
        memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struPeopleNumChange.struRegion, sizeof(NET_VCA_POLYGON));
        m_iParam1 = uEventParam.struPeopleNumChange.bySensitivity;
        m_iParam2 = uEventParam.struPeopleNumChange.byPeopleNumThreshold;
        m_iParam3 = uEventParam.struPeopleNumChange.byDetectMode;
        m_iParam4 = uEventParam.struPeopleNumChange.byNoneStateEffective;
        m_iParam5 = uEventParam.struPeopleNumChange.wDuration;
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

/*********************************************************
  Function:	OnCancel
  Desc:		
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaPositionRule::OnCancel() 
{
	// TODO: Add extra cleanup here
	if (m_lPlayHandle >= 0)
	{
		NET_DVR_StopRealPlay(m_lPlayHandle);
		m_lPlayHandle = -1;
	}
	else 
	{
	
	}
    g_pDlgVcaPositionRule = NULL;
    CDialog::OnCancel();
}

/*********************************************************
Function:	SetVcaDrawMode
Desc:		Add Target
Input:	
Output:	
Return: void 	
**********************************************************/
void CDlgVcaPositionRule::SetVcaDrawMode()
{
	UpdateData(TRUE);
	m_struVCADrawMode.byDspAddRule = (unsigned char)m_bDSPAddRule;
	m_struVCADrawMode.byDspAddTarget = (unsigned char)m_bDSPAddTarget;
	m_struVCADrawMode.byDspPicAddRule = (unsigned char)m_bPicAddRule;
	m_struVCADrawMode.byDspPicAddTarget = (unsigned char)m_bPicAddTarget;
	char szLan[128] = {0};
	if (!NET_DVR_SetVCADrawMode(m_lServerID,  m_iVcaChannel, &m_struVCADrawMode))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_VCA_DRAW_MODE %d", m_iVcaChannel);
		char sbufCn[128] = {0};
		char sbufEn[128] = {0};
		sprintf(sbufCn,"设置通道%d目标叠加失败", m_iVcaChannel);
		sprintf(sbufEn, "Set target added for channel%d failed");
		g_StringLanType(szLan, sbufCn, sbufEn);
		MessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_VCA_DRAW_MODE %d", m_iVcaChannel);
		char sbufCn[128] = {0};
		char sbufEn[128] = {0};
		sprintf(sbufCn,"设置通道%d目标叠加成功", m_iVcaChannel);
		sprintf(sbufEn, "Set target added for channel%d successfully");
		g_StringLanType(szLan, sbufCn, sbufEn);
		MessageBox(szLan);
	}
}

/*********************************************************
  Function:	OnChkRuleActive
  Desc:		Invalid or not
  Input:	
  Output:	
  Return:	void
**********************************************************/ 
void CDlgVcaPositionRule::OnChkRuleActive() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	EnableRuleWindow(m_bRuleActive);
	m_struOneRule.byActive = (unsigned char)m_bRuleActive;
	UpdateData(FALSE);
	OnSelchangeComboRuleType();
}

/*********************************************************
Function:	EnableRuleWindow
Desc:	    
Input:	BOOL bEnable
Output:	
Return:	BOOL
**********************************************************/
BOOL CDlgVcaPositionRule::EnableRuleWindow(BOOL bEnable)
{
	GetDlgItem(IDC_COMBO_RULE_TYPE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_RULE_NAME)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_FILTER_ACTIVE)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_SET_MINI_FILTER)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHK_DRAW_POLYGON)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_SET_MAX_FILTER)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_SENSITIVE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_ALARM_DELAY)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_ALARM_PERSIST)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECKHANDLETYPE1)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECKHANDLETYPE2)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECKHANDLETYPE3)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECKHANDLETYPE4)->EnableWindow(bEnable);
    GetDlgItem(IDC_CHK_PIC_CLOUD)->EnableWindow(bEnable);
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
	GetDlgItem(IDC_CHECKHANDLETYPE5)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MAX_DISTANCE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_DENSTITY_RATE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_READ_CARD_TIME_PERSIST)->EnableWindow(bEnable);
	GetDlgItem(IDC_STATIC_ALARM_DIRECT)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMLINEALARMDIRECT)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHK_DRAW_LINE)->EnableWindow(bEnable);

	return TRUE;
}

/*********************************************************
  Function:	OnSelchangeComboRuleType
  Desc:		Modify Rule Type 
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaPositionRule::OnSelchangeComboRuleType() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

// 	if (m_comboRuleType.GetCurSel() == 8)
// 	{
// 		m_struOneRule.wEventTypeEx = ENUM_VCA_EVENT_LECTURE;
// 		memcpy(&m_struVcaPolygon[m_iCurRuleID], &m_struRuleCfg.struRule[m_iCurRuleID].uEventParam.struLecture.struRegion, sizeof(NET_VCA_POLYGON));
// 	} 
// 	else if(m_comboRuleType.GetCurSel() == 9)
// 	{
// 		m_struOneRule.wEventTypeEx = ENUM_VCA_EVENT_ANSWER;
// 		memcpy(&m_struVcaPolygon[m_iCurRuleID], &m_struRuleCfg.struRule[m_iCurRuleID].uEventParam.struAnswer.struRegion, sizeof(NET_VCA_POLYGON));
// 	}
// 	else
// 	{
		VCA_EVENT_TYPE struEventType;
		
		struEventType = GetEventType(m_comboRuleType.GetCurSel());
        WORD wEventTypeEx = m_comboRuleType.GetItemData(m_comboRuleType.GetCurSel());
		ShowRuleTypeWnd(struEventType, wEventTypeEx);
        if (m_iCurRuleID<8)
        {
            if (struEventType == m_struRuleCfg.struRule[m_iCurRuleID].dwEventType)
            {
                
                GetEventParaSet(struEventType, m_struRuleCfg.struRule[m_iCurRuleID].uEventParam, wEventTypeEx);
            }
            else
            {
                NET_VCA_EVENT_UNION uEventParam;
                memset(&uEventParam, 0, sizeof(NET_VCA_EVENT_UNION));
                GetEventParaSet(struEventType, uEventParam, wEventTypeEx);
		    }
        } 
        else
        {
            if (struEventType == m_struRuleCfgEx.struRule[m_iCurRuleID-8].dwEventType)
            {
                
                GetEventParaSet(struEventType, m_struRuleCfgEx.struRule[m_iCurRuleID-8].uEventParam, wEventTypeEx);
            }
            else
            {
                NET_VCA_EVENT_UNION uEventParam;
                memset(&uEventParam, 0, sizeof(NET_VCA_EVENT_UNION));
                GetEventParaSet(struEventType, uEventParam, wEventTypeEx);
		    }
        }

		m_struOneRule.dwEventType = struEventType; 	

        if (!EventTypeToEventTypeEx(struEventType, m_struOneRule.wEventTypeEx))
        {
            if (ENUM_VCA_EVENT_COMBINED_RULE == wEventTypeEx || ENUM_VCA_EVENT_BLACKBOARD_WRITE == wEventTypeEx || ENUM_VCA_EVENT_PEOPLENUM_CHANGE == wEventTypeEx)
            {
                m_struOneRule.wEventTypeEx = wEventTypeEx;
            } 
            else
            {
                m_struOneRule.wEventTypeEx = 0; 
            }
            	
        }

        m_comEventPriority.SetCurSel(m_struRuleCfgV42.struRule[m_iCurRuleID].byEventPriority);

	//}

	UpdateData(FALSE);
}


/*********************************************************
Function:	GetEventType
Desc:	
Input:	int num
Output:	
Return:	VCA_EVENT_TYPE
**********************************************************/
VCA_EVENT_TYPE CDlgVcaPositionRule::GetEventType(int num)
{
	return (VCA_EVENT_TYPE)m_comboRuleType.GetItemData(num);
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
void CDlgVcaPositionRule::F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser)
{
	COLORREF color;
	color = RGB(255, 255, 0);//Yellow
	if(	m_struOneRule.dwEventType == VCA_ENTER_AREA
		|| m_struOneRule.dwEventType == VCA_EXIT_AREA
		|| m_struOneRule.dwEventType == VCA_INTRUSION
		|| m_struOneRule.dwEventType == VCA_LOITER
		|| m_struOneRule.dwEventType == VCA_LEFT_TAKE
		|| m_struOneRule.dwEventType == VCA_PARKING
		|| m_struOneRule.dwEventType == VCA_RUN
		|| m_struOneRule.dwEventType == VCA_HIGH_DENSITY
		|| m_struOneRule.dwEventType == VCA_STICK_UP
		|| m_struOneRule.dwEventType == VCA_INSTALL_SCANNER
        || m_struOneRule.dwEventType == VCA_LECTURE
        || m_struOneRule.dwEventType == VCA_ANSWER
        || m_struOneRule.dwEventType == VCA_LEFT
        || m_struOneRule.dwEventType == VCA_TAKE
        || m_struOneRule.dwEventType == VCA_VIOLENT_MOTION
        || m_struOneRule.dwEventType == VCA_GET_UP
        || m_struOneRule.dwEventType == VCA_LEAVE_POSITION
        || m_struOneRule.dwEventType == VCA_STANDUP
        || m_struOneRule.dwEventType == VCA_ADV_REACH_HEIGHT
        || m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_BLACKBOARD_WRITE
        || m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_PEOPLENUM_CHANGE
/*        || m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_COMBINED_RULE*/
		)
	{
		F_DrawFrame(lPlayHandle, hDc, dwUser, m_iCurRuleID, color);
	}
	else if (m_struOneRule.dwEventType == VCA_TRAVERSE_PLANE)
	{
		F_DrawLine(lPlayHandle, hDc, dwUser, m_iCurRuleID, color);
	}
	
	F_DrawFilter(lPlayHandle, hDc, dwUser, m_iCurRuleID, RGB(0, 255, 125));
}

/*********************************************************
Function:	F_DrawFrame
Desc:	
Input:	lPlayHandle, Player handle
		hDc : DC handle
		dwUser: User data to distinguish different channels
		DWORD dwRuleID :current rule ID
		COLORREF color:color of line
Output:	
Return:	 void
**********************************************************/
void CDlgVcaPositionRule::F_DrawFrame(long lRealHandle, HDC hDc, DWORD dwUser, DWORD dwRuleID, COLORREF color)
{
	UNREFERENCED_PARAMETER(dwUser);
	UNREFERENCED_PARAMETER(lRealHandle);

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
	MoveToEx(hDc, (int)(m_struVcaPolygon[dwRuleID].struPos[0].fX*m_rcWndRect.Width()), \
		(int)(m_struVcaPolygon[dwRuleID].struPos[0].fY*m_rcWndRect.Height()), NULL);
	
	for(i=1; i<m_struVcaPolygon[dwRuleID].dwPointNum; i++)
	{
        
		LineTo(hDc, (int)(m_struVcaPolygon[dwRuleID].struPos[i].fX*m_rcWndRect.Width()),\
			(int)(m_struVcaPolygon[dwRuleID].struPos[i].fY*m_rcWndRect.Height()));
		//Redraw the polygon if the lines are intersectant.
		if(i>=MIN_PNT_NUM && !m_bMouseMove[m_iCurRuleID] && IsCrossLine(&m_struVcaPolygon[dwRuleID]))
		{
			char szLan[128] = {0};
			g_StringLanType(szLan,"多边形不相邻的边有相交情况存在,请重新输入!","Edges of Polygon can be intersectant, please redraw.!");
			MessageBox(szLan);
			m_dwPosNum--;
			m_struVcaPolygon[dwRuleID].dwPointNum--;
			break;
		}
		if(!m_bCloseIn[dwRuleID])
		{
			m_bDrawPolygon = TRUE;
		}
	}
    
    for (i=0; i<(int)m_struVcaPolygon[dwRuleID].dwPointNum ; i++)
    {
        if (i == VCA_MAX_POLYGON_POINT_NUM)
        {
            break;
        }
        
        point[i].x = (int)(m_struVcaPolygon[dwRuleID].struPos[i].fX*m_rcWndRect.Width());
        point[i].y = (int)(m_struVcaPolygon[dwRuleID].struPos[i].fY*m_rcWndRect.Height());
    }
	//After drawing the 10th point, connect it with the 1st point.
	if(VCA_MAX_POLYGON_POINT_NUM == i && !m_bMouseMove[m_iCurRuleID])
	{
		if (IsValidArea(&m_struVcaPolygon[dwRuleID]))
		{
            graphics.FillPolygon(&brush, (Point *)point, m_struVcaPolygon[dwRuleID].dwPointNum);
            
			LineTo(hDc, (int)(m_struVcaPolygon[dwRuleID].struPos[0].fX*m_rcWndRect.Width()), (int)(m_struVcaPolygon[dwRuleID].struPos[0].fY*m_rcWndRect.Height()));	
			F_AddLabel(hDc, AlarmArea, dwRuleID);//
			m_bCloseIn[dwRuleID] = TRUE;
		}else//redraw
		{
			m_bCloseIn[dwRuleID] = FALSE;
			m_bNeedRedraw[dwRuleID] = TRUE;
			m_struVcaPolygon[dwRuleID].dwPointNum--;
			m_dwPosNum--;
		}
		//check if the alarm region is intact
	}
	else if(m_struVcaPolygon[dwRuleID].dwPointNum>2 && m_bCloseIn[dwRuleID])
	{
		if (IsValidArea(&m_struVcaPolygon[dwRuleID]))
		{
            graphics.FillPolygon(&brush, (Point *)point, m_struVcaPolygon[dwRuleID].dwPointNum);
            
			LineTo(hDc, (int)(m_struVcaPolygon[dwRuleID].struPos[0].fX*m_rcWndRect.Width()),(int)(m_struVcaPolygon[dwRuleID].struPos[0].fY*m_rcWndRect.Height()));
			F_AddLabel(hDc, AlarmArea, dwRuleID);
		}else
		{
			m_bNeedRedraw[dwRuleID] = TRUE;
			m_bCloseIn[dwRuleID] = FALSE;
		}
	}
	
	SelectObject(hDc, pOldPen);
	DeleteObject(DrawPen);
}

/*********************************************************
Function:	F_DrawFilter
Desc:	Rule filter
Input:	lPlayHandle, Player handle
		hDc :DC handle
		dwUser: User data
		DWORD dwRuleID Current rule ID
		COLORREF color 
Output:	
Return:	 void
**********************************************************/
void CDlgVcaPositionRule::F_DrawFilter(long lRealHandle, HDC hDc, DWORD dwUser, DWORD dwRuleID, COLORREF color)
{
	UNREFERENCED_PARAMETER(dwRuleID);
	UNREFERENCED_PARAMETER(dwUser);
	UNREFERENCED_PARAMETER(lRealHandle);
//	if (m_bSetMiniFilter || m_bSetMaxFilter)
	if (m_bFilterActive)
	{
		CPen DrawPen;
		
		DrawPen.CreatePen(PS_SOLID, 1, color);
		CBrush brTmp;
		brTmp.CreateSolidBrush(color);
		
		HGDIOBJ pOldPen = SelectObject(hDc, DrawPen);
		CRect rectMini, rectMax;
		rectMini.left = (int)(m_struOneRule.struSizeFilter.struMiniRect.fX*m_rcWndRect.Width());
		rectMini.top = (int)(m_struOneRule.struSizeFilter.struMiniRect.fY*m_rcWndRect.Height());
		rectMini.right = (int)((m_struOneRule.struSizeFilter.struMiniRect.fX+m_struOneRule.struSizeFilter.struMiniRect.fWidth)*m_rcWndRect.Width());
		rectMini.bottom = (int)((m_struOneRule.struSizeFilter.struMiniRect.fY+m_struOneRule.struSizeFilter.struMiniRect.fHeight)*m_rcWndRect.Height());
		FrameRect(hDc, rectMini, brTmp);
		
		rectMax.left = (int)(m_struOneRule.struSizeFilter.struMaxRect.fX*m_rcWndRect.Width());
		rectMax.top = (int)(m_struOneRule.struSizeFilter.struMaxRect.fY*m_rcWndRect.Height());
		rectMax.right = (int)((m_struOneRule.struSizeFilter.struMaxRect.fX+m_struOneRule.struSizeFilter.struMaxRect.fWidth)*m_rcWndRect.Width());
		rectMax.bottom = (int)((m_struOneRule.struSizeFilter.struMaxRect.fY+m_struOneRule.struSizeFilter.struMaxRect.fHeight)*m_rcWndRect.Height());
		FrameRect(hDc, rectMax, brTmp);
		
		SelectObject(hDc, pOldPen);
		DeleteObject(DrawPen);
	}
}

/*********************************************************
Function:	F_AddLabel
Desc:		Add Label on player window
Input:	hDc : DC handle
		iAlarmType: Alarm Type
		dwRuleID: Current rule ID
Output:	
Return:	void 
**********************************************************/
void CDlgVcaPositionRule::F_AddLabel(HDC hDc, int iAlarmType, DWORD dwRuleID)
{
	if (AlarmArea == iAlarmType)
	{
		CString szTemp(_T(""));
		DWORD dwID;
		dwID = 0;
		CRect rect;
		UINT uFormat = DT_LEFT;
		int iTxtWidth = 0;// width of label
		int iTxtHeight = 20;//height of label	
		iTxtWidth = iTxtHeight;
		szTemp.Format("(%d)", dwRuleID);
		
		if (m_struVcaPolygon[dwRuleID].struPos[0].fX >= 0.5 && m_struVcaPolygon[dwRuleID].struPos[0].fY >= 0.5)
		{
			uFormat = DT_RIGHT;
			rect.left = (int)(m_struVcaPolygon[dwRuleID].struPos[0].fX*m_rcWndRect.Width()) - iTxtWidth;
			rect.top = (int)(m_struVcaPolygon[dwRuleID].struPos[0].fY*m_rcWndRect.Height()) - iTxtHeight;
			rect.bottom = (int)(m_struVcaPolygon[dwRuleID].struPos[0].fY*m_rcWndRect.Height());
			rect.right = (int)(m_struVcaPolygon[dwRuleID].struPos[0].fX*m_rcWndRect.Width());
		}else if (m_struVcaPolygon[dwRuleID].struPos[0].fX < 0.5 && m_struVcaPolygon[dwRuleID].struPos[0].fY < 0.5)
		{
			uFormat = DT_LEFT;
			rect.left = (int)(m_struVcaPolygon[dwRuleID].struPos[0].fX*m_rcWndRect.Width());
			rect.top = (int)(m_struVcaPolygon[dwRuleID].struPos[0].fY*m_rcWndRect.Height());
			rect.bottom = (int)(m_struVcaPolygon[dwRuleID].struPos[0].fY*m_rcWndRect.Height()) + iTxtHeight;
			rect.right = (int)(m_struVcaPolygon[dwRuleID].struPos[0].fX*m_rcWndRect.Width()) + iTxtWidth;
		}else if (m_struVcaPolygon[dwRuleID].struPos[0].fX < 0.5 && m_struVcaPolygon[dwRuleID].struPos[0].fY >= 0.5)
		{
			uFormat = DT_LEFT;
			rect.left = (int)(m_struVcaPolygon[dwRuleID].struPos[0].fX*m_rcWndRect.Width());
			rect.top = (int)(m_struVcaPolygon[dwRuleID].struPos[0].fY*m_rcWndRect.Height()) - iTxtHeight;
			rect.bottom = (int)(m_struVcaPolygon[dwRuleID].struPos[0].fY*m_rcWndRect.Height());
			rect.right = (int)(m_struVcaPolygon[dwRuleID].struPos[0].fX*m_rcWndRect.Width()) + iTxtWidth;
			
		}else if (m_struVcaPolygon[dwRuleID].struPos[0].fX >= 0.5 && m_struVcaPolygon[dwRuleID].struPos[0].fY < 0.5)
		{
			uFormat = DT_RIGHT;
			rect.left = (int)(m_struVcaPolygon[dwRuleID].struPos[0].fX*m_rcWndRect.Width()) - iTxtWidth;
			rect.top = (int)(m_struVcaPolygon[dwRuleID].struPos[0].fY*m_rcWndRect.Height());
			rect.bottom = (int)(m_struVcaPolygon[dwRuleID].struPos[0].fY*m_rcWndRect.Height()) + iTxtHeight;
			rect.right = (int)(m_struVcaPolygon[dwRuleID].struPos[0].fX*m_rcWndRect.Width());
		}
		DrawText(hDc, szTemp, strlen(szTemp), &rect, uFormat);

	}
	if (iAlarmType == AlarmLine)
	{
		CString szTemp(_T(""));
		DWORD dwID;
		dwID = 0;
		CRect rect;
		UINT uFormat = DT_LEFT;
		int iTxtWidth = 0;
		int iTxtHeight = 20;
		iTxtWidth = iTxtHeight;
		szTemp.Format("(%d)", dwRuleID);
		
		if (m_struVcaLine[dwRuleID].struStart.fX >= 0.5 && m_struVcaLine[dwRuleID].struStart.fY >= 0.5)
		{//Alarm Plane at right bottom
			uFormat = DT_RIGHT;
			rect.left = (int)(m_struVcaLine[dwRuleID].struStart.fX*m_rcWndRect.Width()) - iTxtWidth;
			rect.top = (int)(m_struVcaLine[dwRuleID].struStart.fY*m_rcWndRect.Height()) - iTxtHeight;
			rect.bottom = (int)(m_struVcaLine[dwRuleID].struStart.fY*m_rcWndRect.Height());
			rect.right = (int)(m_struVcaLine[dwRuleID].struStart.fX*m_rcWndRect.Width());
		}
		else if (m_struVcaLine[dwRuleID].struStart.fX < 0.5 && m_struVcaLine[dwRuleID].struStart.fY < 0.5)
		{//Alarm Plane at left top
			uFormat = DT_LEFT;
			rect.left = (int)(m_struVcaLine[dwRuleID].struStart.fX*m_rcWndRect.Width());
			rect.top = (int)(m_struVcaLine[dwRuleID].struStart.fY*m_rcWndRect.Height());
			rect.bottom = (int)(m_struVcaLine[dwRuleID].struStart.fY*m_rcWndRect.Height()) + iTxtHeight;
			rect.right = (int)(m_struVcaLine[dwRuleID].struStart.fX*m_rcWndRect.Width()) + iTxtWidth;
		}
		else if (m_struVcaLine[dwRuleID].struStart.fX < 0.5 && m_struVcaLine[dwRuleID].struStart.fY >= 0.5)
		{//Alarm Plane at left bottom
			uFormat = DT_LEFT;
			rect.left = (int)(m_struVcaLine[dwRuleID].struStart.fX*m_rcWndRect.Width());
			rect.top = (int)(m_struVcaLine[dwRuleID].struStart.fY*m_rcWndRect.Height()) - iTxtHeight;
			rect.bottom = (int)(m_struVcaLine[dwRuleID].struStart.fY*m_rcWndRect.Height());
			rect.right = (int)(m_struVcaLine[dwRuleID].struStart.fX*m_rcWndRect.Width()) + iTxtWidth;
		}
		else if (m_struVcaLine[dwRuleID].struStart.fX >= 0.5 && m_struVcaLine[dwRuleID].struStart.fY < 0.5)
		{
			//Alarm Plane at right bottom
			uFormat = DT_RIGHT;
			rect.left = (int)(m_struVcaLine[dwRuleID].struStart.fX*m_rcWndRect.Width()) - iTxtWidth;
			rect.top = (int)(m_struVcaLine[dwRuleID].struStart.fY*m_rcWndRect.Height());
			rect.bottom = (int)(m_struVcaLine[dwRuleID].struStart.fY*m_rcWndRect.Height()) + iTxtHeight;
			rect.right = (int)(m_struVcaLine[dwRuleID].struStart.fX*m_rcWndRect.Width());
		}
		DrawText(hDc, szTemp, strlen(szTemp), &rect, uFormat);
	}
}

/*********************************************************
Function:	IsValidArea
Desc:		Check if the area is valid
Input:	alarm_region: 
Output:	
Return:	BOOL
**********************************************************/
BOOL CDlgVcaPositionRule::IsValidArea(NET_VCA_POLYGON *alarm_region)
{
	if(alarm_region == NULL)
	{
		return FALSE;
	}
	// Check if all points of polygon is in one line.
	if (F_IsStraightLine(alarm_region))
	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "所有点在同一直线上，不能组成多边形!",\
			"All points have been in the same line, not able to form the polygon");
		MessageBox(szLan);
		return FALSE;
	}
	// check if all the lines have cross
	if (F_IsACrossLine(alarm_region))
	{
		char szLan[128] = {0};
		g_StringLanType(szLan,"终点和起点的连线与已有的直线相交，不能组成有效的多边形!", \
			"The edges of polygon can't be intersectant, please draw again");
		MessageBox(szLan);
		return FALSE;
	}
	return TRUE;
}

/*********************************************************
Function:	IsCrossLine
Desc:	IsCrossLine
Input:	
Output:	
Return:	BOOL 
**********************************************************/
BOOL CDlgVcaPositionRule::IsCrossLine(NET_VCA_POLYGON *alarm_region)
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
	
	// The apexes of polygon should be more than 3
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
			g_StringLanType(szLan, "内存分配失败!","Allocate memory failed!");
			MessageBox(szLan);
			exit(EXIT_FAILURE);
		}
		
		//Copy the apex to a array
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

/*********************************************************
Function:	F_IsACrossLine
Desc:		Check if cross the alarm plane
Input:	NET_VCA_POLYGON *alarm_region
Output:	
Return:	BOOL 
**********************************************************/
BOOL CDlgVcaPositionRule::F_IsACrossLine(NET_VCA_POLYGON *alarm_region)
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
			g_StringLanType(szLan, "Allocate memory failed!","Memory allocation failure!");
			MessageBox(szLan);
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

/*********************************************************
Function:	F_IsStraightLine
Desc:	
Input:	NET_VCA_POLYGON *alarm_region
Output:	
Return:	BOOL 
**********************************************************/
BOOL CDlgVcaPositionRule::F_IsStraightLine(NET_VCA_POLYGON *alarm_region)
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


/*********************************************************
Function:	F_LineCrossDetect
Desc:	
Input:	NET_VCA_POINT p1
		NET_VCA_POINT p2
		NET_VCA_POINT q1
		NET_VCA_POINT q1
Output:	
Return:	BOOL 
**********************************************************/
BOOL CDlgVcaPositionRule::F_LineCrossDetect(NET_VCA_POINT p1, NET_VCA_POINT p2, NET_VCA_POINT q1, NET_VCA_POINT q2)
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

/*********************************************************
Function:	F_DrawLine
Desc:	
Input:	long lPlayHandle
		HDC hDc
		DWORD dwUser
		DWORD dwRuleID
		COLORREF color
Output:	
Return:	void 
**********************************************************/
void CDlgVcaPositionRule::F_DrawLine(long lPlayHandle, HDC hDc, DWORD dwUser, DWORD dwRuleID, COLORREF color)
{
	UNREFERENCED_PARAMETER(dwUser);
	UNREFERENCED_PARAMETER(lPlayHandle);
    
	int iDirect = -1;
    int x1 = (int)(m_struVcaLine[dwRuleID].struStart.fX*m_rcWndRect.Width());
    int y1 = (int)(m_struVcaLine[dwRuleID].struStart.fY*m_rcWndRect.Height());
    int x2 = (int)(m_struVcaLine[dwRuleID].struEnd.fX*m_rcWndRect.Width());
    int y2 = (int)(m_struVcaLine[dwRuleID].struEnd.fY*m_rcWndRect.Height());
	
	SetTextColor(hDc,color);
	
    using namespace Gdiplus;
    Graphics graphics(hDc);
    Color DrawColor;
    DrawColor.SetValue(DrawColor.MakeARGB(50,GetRValue(color) ,GetGValue(color),GetBValue(color)));
    
    Pen pen(color, 4);
    pen.SetStartCap(LineCapFlat);
    pen.SetEndCap(LineCapFlat);
    
    CPen DrawPen;
    DrawPen.CreatePen(PS_SOLID, 1, color);
    
    bool bRect = false;
    int k = 0;
    //calculate slope
    if(x2 != x1)
	{
        k = (y2 - y1) / (x2 - x1);
		
        //if the absolute value of slope is more than 2, draw rectangle directly
        if(abs(k) >= 2)
        {
            bRect = true;
        }
    }
    else
    {
        bRect = true;
    }
		
    if(bRect)
		{
        //TRACE("Line\n");
        
        pen.SetColor(DrawColor);
        if(k < 0)
        {
            graphics.DrawLine(&pen, x1-2, y1-1, x2-2, y2-1);
        }
        else
        {
            graphics.DrawLine(&pen, x1+2, y1-1, x2+2, y2-1);
        }
    }
    else
    {
        //Draw parallelogram, the vertical height is 8
        SolidBrush  brush(DrawColor);
        POINT point[4];
        point[0].x = x1;
        point[0].y = y1;
        point[1].x = x2;
        point[1].y = y2;
        point[2].x = x2;
        point[2].y = y2-8;
        point[3].x = x1;
        point[3].y = y1-8;
        graphics.FillPolygon(&brush, (Point *)point, 4);
		}
		
    
    HGDIOBJ pOldPen = SelectObject(hDc, DrawPen);
    MoveToEx(hDc, x1, y1, NULL);
    LineTo(hDc, x2, y2);
    
		//Draw arrow
    F_DrawArrowhead(hDc, dwRuleID, m_struOneRule.uEventParam.struTraversePlane.dwCrossDirection);
		//Draw label
		F_AddLabel(hDc, AlarmLine, dwRuleID);
    
	SelectObject(hDc, pOldPen);
	DeleteObject(DrawPen);
}

/*********************************************************
Function:	F_DrawArrowhead
Desc:		Draw Arrow. 
Input:	HDC hDc
		DWORD dwRuleID
		int direction
Output:	
Return:	void 
**********************************************************/
void CDlgVcaPositionRule::F_DrawArrowhead(HDC hDc, DWORD dwRuleID, int direction)
{
    POINT ptArrow_start0;/*, ptArrow_start1, ptArrow_start2;*/
    POINT ptArrow_end;
    float fLine_k = 0.0, fArrow_k = 0.0, fArrow_k1 = 0.0;
    int   iTheta = 0;
    int   iDirection = -1;
    //check the direction of flyover line
    switch(direction)
    {
    case VCA_LEFT_GO_RIGHT:
        iDirection = 0;
        break;
    case VCA_RIGHT_GO_LEFT:
        iDirection = 1;
        break;
    case VCA_BOTH_DIRECTION:
        iDirection = 2;
        break;
    }

    //Draw arrow
    //coordinate of arrow's end
    ptArrow_start0.x = (long)(m_rcWndRect.Width()*(m_struVcaLine[dwRuleID].struStart.fX+m_struVcaLine[dwRuleID].struEnd.fX) / 2);
    ptArrow_start0.y = (long)(m_rcWndRect.Height()*(m_struVcaLine[dwRuleID].struStart.fY + m_struVcaLine[dwRuleID].struEnd.fY) / 2);

    //slope
    fLine_k = (m_struVcaLine[dwRuleID].struEnd.fY*m_rcWndRect.Height() - m_struVcaLine[dwRuleID].struStart.fY*m_rcWndRect.Height()) / 
        (m_struVcaLine[dwRuleID].struEnd.fX*m_rcWndRect.Width() - m_struVcaLine[dwRuleID].struStart.fX*m_rcWndRect.Width());

    POINT ptStart0;

    using namespace Gdiplus;
    Graphics graphics(hDc);

    Color color(80, 0, 0, 0);
    color.SetValue(color.MakeARGB(80,255,255,0));

    Pen pen(color, 5);
    //if the absolute value of slope is more than 2, the width of arrow is 4
    if(abs(fLine_k) >= 2)
		{
        pen.SetWidth(4);
    }
    else
    {
        //otherwise the width of arrow is 8*cos(alpha)
        float fWidth = 8.0 / sqrt(1.0 + fLine_k * fLine_k);
        pen.SetWidth(fWidth);
    }

    pen.SetStartCap(LineCapFlat);
    pen.SetEndCap(LineCapArrowAnchor);

    if (fLine_k != 0.0)
    {
        //perpendicular segment on the line
        fArrow_k =  -1.0 / fLine_k;

        iTheta = (int)(atan(fArrow_k ) / PI * 180);

        if (0 == iDirection || 2 == iDirection)
        {
            //reduce 1 of width to prevent the arrow deviate from the segment
            if(fLine_k > 0)
            {
                ptStart0.x = ptArrow_start0.x - (8-1) * sin(iTheta / 180.0 * PI) * cos(iTheta / 180.0 * PI);
                ptStart0.y = ptArrow_start0.y - (8-1) * sin(iTheta / 180.0 * PI) * sin(iTheta / 180.0 * PI);
		}
            else
		{
                ptStart0.x = ptArrow_start0.x;
                ptStart0.y = ptArrow_start0.y;
            }

            ptArrow_end.x = ptStart0.x + 20 * cos(iTheta / 180.0 * PI);
            ptArrow_end.y = 20 * sin(iTheta / 180.0 * PI) + ptStart0.y;

            graphics.DrawLine(&pen, ptStart0.x, ptStart0.y, ptArrow_end.x, ptArrow_end.y);
        }

        if (1 == iDirection || 2 == iDirection)
        {
            if(fLine_k > 0)
            {
                ptStart0.x = ptArrow_start0.x;
                ptStart0.y = ptArrow_start0.y;
            }
            else
            {
                ptStart0.x = ptArrow_start0.x - (8-1) * sin(iTheta / 180.0 * PI) * cos(iTheta / 180.0 * PI);
                ptStart0.y = ptArrow_start0.y - (8-1) * sin(iTheta / 180.0 * PI) * sin(iTheta / 180.0 * PI);
            }

            ptArrow_end.x = ptStart0.x - 20 * cos(iTheta / 180.0 * PI);
            ptArrow_end.y = (-20) * sin(iTheta / 180.0 * PI) + ptStart0.y ;

            graphics.DrawLine(&pen, ptStart0.x, ptStart0.y, ptArrow_end.x, ptArrow_end.y);
		}
	}else
	{
        //The arrow is vertical
        if (0 == iDirection || 2 == iDirection)
		{
			//
            ptStart0.x = ptArrow_start0.x;
            ptStart0.y = ptArrow_start0.y;// + 4;

            ptArrow_end.x = ptStart0.x ;
            ptArrow_end.y = ptStart0.y + 20;

            graphics.DrawLine(&pen, ptStart0.x, ptStart0.y, ptArrow_end.x, ptArrow_end.y);
		}
        if (1 == iDirection || 2 == iDirection)
		{
			// 
            ptStart0.x = ptArrow_start0.x;
            ptStart0.y = ptArrow_start0.y - 8;

            ptArrow_end.x = ptStart0.x ;
            ptArrow_end.y = ptStart0.y - 20;

            graphics.DrawLine(&pen, ptStart0.x, ptStart0.y, ptArrow_end.x, ptArrow_end.y);
		}		
	}

}

/*********************************************************
  Function:	OnChkDrawPolygon
  Desc:		Draw Polygon or not. 
  Input:	
  Output:	
  Return:	void 
**********************************************************/
void CDlgVcaPositionRule::OnChkDrawPolygon() 
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
void CDlgVcaPositionRule::OnCheckFilterActive() 
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
void CDlgVcaPositionRule::OnCheckSetMiniFilter() 
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
void CDlgVcaPositionRule::OnCheckSetMaxFilter() 
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
void CDlgVcaPositionRule::OnChkDrawLine() 
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
void CDlgVcaPositionRule::OnSelchangeComlinealarmdirect() 
{
	VCA_CROSS_DIRECTION iDirect;
	iDirect = (VCA_CROSS_DIRECTION)m_comboAlarmDirect.GetCurSel();
	m_struOneRule.uEventParam.struTraversePlane.dwCrossDirection = iDirect;
}

/*********************************************************
Function:	SetOneRule
Desc:		Set one rule
Input:	struVcaOneRule
Output:	
Return:	void 	
**********************************************************/
BOOL CDlgVcaPositionRule::SetOneRule(NET_VCA_ONE_RULE_V41 &struVcaOneRule)
{

	UpdateData(TRUE);
	
	//Parameter of Behavior analysis
	SetVcaEventPara(struVcaOneRule.uEventParam,struVcaOneRule.dwEventType, struVcaOneRule.wEventTypeEx);
	
	// Size filter 
	struVcaOneRule.struSizeFilter.byActive = (BYTE)m_bFilterActive;

	SetTimePara();//Fortify time 
	memcpy(&m_struOneRule.struAlarmTime[0][0], 
		&m_struAlarmTime[0][0], (MAX_DAYS*MAX_TIMESEGMENT_V30*sizeof(NET_DVR_SCHEDTIME)));
	
	// Alarm linkage (Action after getting alarm)
	SetAlarmPara(struVcaOneRule.struHandleType);//Set alarm info
	/*Camera triggered to record. Set 1 to trigger this channel*/
	SetRelRecordChan(struVcaOneRule, m_iChannelnumber);

	SetRuleBehaviorCfg();
   // SaveTempRuleBehaviorCfg();


	return TRUE;
}


/*********************************************************
Function:	SaveOneRule
Desc:		Save one rule
Input:	struVcaOneRule
Output:	
Return:	void 	
**********************************************************/
BOOL CDlgVcaPositionRule::SaveOneRule(NET_VCA_ONE_RULE_V41 &struVcaOneRule)
{
    
    UpdateData(TRUE);
    
    //Parameter of Behavior analysis
    SetVcaEventPara(struVcaOneRule.uEventParam,struVcaOneRule.dwEventType, struVcaOneRule.wEventTypeEx);
    
    // Size filter 
    struVcaOneRule.struSizeFilter.byActive = (BYTE)m_bFilterActive;
    
    SetTimePara();//Fortify time 
    memcpy(&m_struOneRule.struAlarmTime[0][0], 
        &m_struAlarmTime[0][0], (MAX_DAYS*MAX_TIMESEGMENT_V30*sizeof(NET_DVR_SCHEDTIME)));
    
    // Alarm linkage (Action after getting alarm)
    SetAlarmPara(struVcaOneRule.struHandleType);//Set alarm info
    /*Camera triggered to record. Set 1 to trigger this channel*/
    SetRelRecordChan(struVcaOneRule, m_iChannelnumber);
    
    SaveTempRuleBehaviorCfg();
    
    
    return TRUE;
}
/*********************************************************
  Function:	OnTimeOk
  Desc:		
  Input:	
  Output:	
  Return:	void 
**********************************************************/
void CDlgVcaPositionRule::OnTimeOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (!F_TimeTest())
	{
		return;
	}
	int	i = m_comboWeekday.GetCurSel();	
	m_struAlarmTime[i][0].byStartHour = (BYTE)m_iHour11;
	m_struAlarmTime[i][0].byStartMin = (BYTE)m_iMin11;
	m_struAlarmTime[i][0].byStopHour =(BYTE) m_iHour12;
	m_struAlarmTime[i][0].byStopMin = (BYTE)m_iMin12;
	m_struAlarmTime[i][1].byStartHour = (BYTE)m_iHour21;
	m_struAlarmTime[i][1].byStartMin = (BYTE)m_iMin21;
	m_struAlarmTime[i][1].byStopHour = (BYTE)m_iHour22;
	m_struAlarmTime[i][1].byStopMin = (BYTE)m_iMin22;

	m_struAlarmTime[i][2].byStartHour = (BYTE)m_iHour31;
	m_struAlarmTime[i][2].byStartMin = (BYTE)m_iMin31;
	m_struAlarmTime[i][2].byStopHour =(BYTE) m_iHour32;
	m_struAlarmTime[i][2].byStopMin = (BYTE)m_iMin32;
	m_struAlarmTime[i][3].byStartHour = (BYTE)m_iHour41;
	m_struAlarmTime[i][3].byStartMin = (BYTE)m_iMin41;
	m_struAlarmTime[i][3].byStopHour = (BYTE)m_iHour42;
	m_struAlarmTime[i][3].byStopMin = (BYTE)m_iMin42;

	m_struAlarmTime[i][4].byStartHour = (BYTE)m_iHour51;
	m_struAlarmTime[i][4].byStartMin = (BYTE)m_iMin51;
	m_struAlarmTime[i][4].byStopHour =(BYTE) m_iHour52;
	m_struAlarmTime[i][4].byStopMin = (BYTE)m_iMin52;
	m_struAlarmTime[i][5].byStartHour = (BYTE)m_iHour61;
	m_struAlarmTime[i][5].byStartMin = (BYTE)m_iMin61;
	m_struAlarmTime[i][5].byStopHour = (BYTE)m_iHour62;
	m_struAlarmTime[i][5].byStopMin = (BYTE)m_iMin62;

	m_struAlarmTime[i][6].byStartHour = (BYTE)m_iHour71;
	m_struAlarmTime[i][6].byStartMin = (BYTE)m_iMin71;
	m_struAlarmTime[i][6].byStopHour =(BYTE) m_iHour72;
	m_struAlarmTime[i][6].byStopMin = (BYTE)m_iMin72;
	m_struAlarmTime[i][7].byStartHour = (BYTE)m_iHour81;
	m_struAlarmTime[i][7].byStartMin = (BYTE)m_iMin81;
	m_struAlarmTime[i][7].byStopHour = (BYTE)m_iHour82;
	m_struAlarmTime[i][7].byStopMin = (BYTE)m_iMin82;

	GetDlgItem(IDC_TIME_COPY)->EnableWindow(TRUE);
}
/*********************************************************
  Function:	OnTimeCopy
  Desc:		
  Input:	
  Output:	
  Return:	void 
**********************************************************/
void CDlgVcaPositionRule::OnTimeCopy() 
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
			for(k=0; k<MAX_TIMESEGMENT_V30; k++)
			{
				memcpy(&(m_struAlarmTime[j][k]), &(m_struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
			}
		}
	}
	else
	{
		for(k=0; k<MAX_TIMESEGMENT_V30; k++)
		{
			memcpy(&(m_struAlarmTime[m_nCopyTime][k]), &(m_struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
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
BOOL CDlgVcaPositionRule::F_TimeTest()
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
void CDlgVcaPositionRule::OnSelchangeComboweekday() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int	i = m_comboWeekday.GetCurSel();	
	m_iHour11 = m_struAlarmTime[i][0].byStartHour;
	m_iMin11 = m_struAlarmTime[i][0].byStartMin;
	m_iHour12 = m_struAlarmTime[i][0].byStopHour;
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
	UpdateData(FALSE);
}

/*********************************************************
Function:	SetTimePara
Desc:	    set alarm time parameter
Input:	
Output:	
Return:	void 
**********************************************************/
void CDlgVcaPositionRule::SetTimePara()
{
	int i;
	i = m_comboWeekday.GetCurSel();	
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
	m_struAlarmTime[i][2].byStopHour =(BYTE) m_iHour32;
	m_struAlarmTime[i][2].byStopMin = (BYTE)m_iMin32;
	m_struAlarmTime[i][3].byStartHour = (BYTE)m_iHour41;
	m_struAlarmTime[i][3].byStartMin = (BYTE)m_iMin41;
	m_struAlarmTime[i][3].byStopHour = (BYTE)m_iHour42;
	m_struAlarmTime[i][3].byStopMin = (BYTE)m_iMin42;
	
	m_struAlarmTime[i][4].byStartHour = (BYTE)m_iHour51;
	m_struAlarmTime[i][4].byStartMin = (BYTE)m_iMin51;
	m_struAlarmTime[i][4].byStopHour =(BYTE) m_iHour52;
	m_struAlarmTime[i][4].byStopMin = (BYTE)m_iMin52;
	m_struAlarmTime[i][5].byStartHour = (BYTE)m_iHour61;
	m_struAlarmTime[i][5].byStartMin = (BYTE)m_iMin61;
	m_struAlarmTime[i][5].byStopHour = (BYTE)m_iHour62;
	m_struAlarmTime[i][5].byStopMin = (BYTE)m_iMin62;
	
	m_struAlarmTime[i][6].byStartHour = (BYTE)m_iHour71;
	m_struAlarmTime[i][6].byStartMin = (BYTE)m_iMin71;
	m_struAlarmTime[i][6].byStopHour =(BYTE) m_iHour72;
	m_struAlarmTime[i][6].byStopMin = (BYTE)m_iMin72;
	m_struAlarmTime[i][7].byStartHour = (BYTE)m_iHour81;
	m_struAlarmTime[i][7].byStartMin = (BYTE)m_iMin81;
	m_struAlarmTime[i][7].byStopHour = (BYTE)m_iHour82;
	m_struAlarmTime[i][7].byStopMin = (BYTE)m_iMin82;
}

/*********************************************************
Function:	SetAlarmPara	
Desc:	    set alarm parameter
Input:	
Output:	
Return:	void 
**********************************************************/
void CDlgVcaPositionRule::SetAlarmPara(NET_DVR_HANDLEEXCEPTION_V30 &struHandleType)
{

	UpdateData(TRUE);
	struHandleType.dwHandleType = 0;
	struHandleType.dwHandleType |= (m_bHandleType1 << 0);
	struHandleType.dwHandleType |= (m_bHandleType2 << 1);
	struHandleType.dwHandleType |= (m_bHandleType3 << 2);
	struHandleType.dwHandleType |= (m_bHandleType4 << 3);
	struHandleType.dwHandleType |= (m_bHandleType5 << 4);
    struHandleType.dwHandleType |= (m_bHandleType6 << 12);
	
	for (DWORD i = 0; i < MAX_ALARMOUT_V30; i++)
	{
		struHandleType.byRelAlarmOut[i] = (BYTE)m_pbAlarmOut[i];
	}
	
	
}

/*********************************************************
Function:	SetRelRecordChan
Desc:	    set record chan parameter 
Input:	
Output:	
Return:	void 
**********************************************************/
void CDlgVcaPositionRule::SetRelRecordChan(NET_VCA_ONE_RULE_V41 &struVcaOneRule, int nChanNum)
{
	for (int i = 0; i < nChanNum; i++)
	{   
	struVcaOneRule.byRelRecordChan[i] = (BYTE)m_pbChannel[i];
	}
}

/*********************************************************
Function:	SetVcaEventPara
Desc:	    set vca event parameter 
Input:  	VCA_EVENT_TYPE struEventType NET_VCA_EVENT_UNION &uEventparam
Output:	    NET_VCA_EVENT_UNION &uEventparam
Return:	    void 
**********************************************************/
void CDlgVcaPositionRule::SetVcaEventPara(NET_VCA_EVENT_UNION &uEventparam, VCA_EVENT_TYPE struEventType, WORD struEventTypeEx)
{
	switch (struEventType)
	{
	case VCA_TRAVERSE_PLANE:
		memcpy(&uEventparam.struTraversePlane.struPlaneBottom, &m_struVcaLine[m_iCurRuleID], sizeof(NET_VCA_LINE));
		uEventparam.struTraversePlane.dwCrossDirection = (VCA_CROSS_DIRECTION)m_comboAlarmDirect.GetCurSel();
		uEventparam.struTraversePlane.byDetectionTarget = m_comDetTarget.GetCurSel();
        uEventparam.struTraversePlane.byPriority = m_comboPriority.GetCurSel();
        uEventparam.struTraversePlane.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
		break;
	case VCA_ENTER_AREA:
		uEventparam.struArea.byDetectionTarget = m_comDetTarget.GetCurSel();
        uEventparam.struArea.byPriority = m_comboPriority.GetCurSel();
		memcpy(&uEventparam.struArea.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        uEventparam.struArea.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);

		break;
	case VCA_EXIT_AREA:
		uEventparam.struArea.byDetectionTarget = m_comDetTarget.GetCurSel();
        uEventparam.struArea.byPriority = m_comboPriority.GetCurSel();
		memcpy(&uEventparam.struArea.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        uEventparam.struArea.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
		break;
	case VCA_INTRUSION:
		uEventparam.struIntrusion.byDetectionTarget = m_comDetTarget.GetCurSel();
        uEventparam.struIntrusion.byPriority = m_comboPriority.GetCurSel();
		uEventparam.struIntrusion.wDuration = (WORD)m_iAlarmDelay;
		memcpy(&uEventparam.struIntrusion.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        uEventparam.struIntrusion.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
		break;
	case VCA_LOITER:
		uEventparam.struLoiter.wDuration = (WORD)m_iAlarmPersist;
		memcpy(&uEventparam.struLoiter.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        uEventparam.struLoiter.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
		break;
	case VCA_LEFT_TAKE:
		uEventparam.struTakeTeft.wDuration = (WORD)m_iAlarmPersist;
        uEventparam.struTakeTeft.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
		memcpy(&uEventparam.struTakeTeft.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
		break;
	case VCA_PARKING:
		uEventparam.struParking.wDuration = (WORD)m_iAlarmPersist;
		memcpy(&uEventparam.struParking.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        uEventparam.struParking.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
		break;
	case VCA_RUN:
		uEventparam.struRun.byDetectionTarget = m_comDetTarget.GetCurSel();
		uEventparam.struRun.fRunDistance = m_fMaxDistance;
		memcpy(&uEventparam.struRun.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        uEventparam.struRun.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
		break;
	case VCA_HIGH_DENSITY:
		uEventparam.struHighDensity.fDensity = m_fDenstityRate;
		memcpy(&uEventparam.struHighDensity.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        uEventparam.struHighDensity.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
		break;
	case VCA_STICK_UP:
		memcpy(&uEventparam.struStickUp.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
		uEventparam.struStickUp.wDuration = (WORD)m_iAlarmPersist;
		uEventparam.struStickUp.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
		break;
	case VCA_INSTALL_SCANNER:
		memcpy(&uEventparam.struScanner.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
		uEventparam.struScanner.wDuration = (WORD)m_iReadCardTimePersist;
		uEventparam.struScanner.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
		break;

	case VCA_LECTURE:
		uEventparam.struLecture.wDuration = (WORD)m_iAlarmDelay;
		memcpy(&uEventparam.struLecture.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
		uEventparam.struLecture.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
		uEventparam.struLecture.byTrackingMode = (BYTE)(m_comboTrackingMode.GetCurSel());
		uEventparam.struLecture.byZoomMode = (BYTE)(m_comboZoomMode.GetCurSel());
		break;
	case VCA_ANSWER:
		memcpy(&uEventparam.struAnswer.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
		uEventparam.struAnswer.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
		break;
    case VCA_LEFT:
        uEventparam.struLeft.wDuration = (WORD)m_iAlarmPersist;
        uEventparam.struLeft.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
        memcpy(&uEventparam.struLeft.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
		break;
    case VCA_TAKE:
        uEventparam.struTake.wDuration = (WORD)m_iAlarmPersist;
        uEventparam.struTake.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
        memcpy(&uEventparam.struTake.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
		break;

    case VCA_VIOLENT_MOTION:
        uEventparam.struViolentMotion.wDuration = m_iParam1;
        uEventparam.struViolentMotion.bySensitivity = m_iParam2;
        uEventparam.struViolentMotion.byMode = m_iParam3;
        memcpy(&uEventparam.struViolentMotion.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        break;

    case VCA_GET_UP:
        uEventparam.struGetUp.wDuration = m_iParam1;
        uEventparam.struGetUp.bySensitivity = m_iParam2;
        uEventparam.struGetUp.byMode = m_iParam3;
        memcpy(&uEventparam.struGetUp.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        break;

    case VCA_LEAVE_POSITION:
        uEventparam.struLeavePos.wLeaveDelay = m_iParam1;
        uEventparam.struLeavePos.wStaticDelay = m_iParam2;
        uEventparam.struLeavePos.byMode = m_iParam3;
        uEventparam.struLeavePos.byPersonType = m_iParam4;
        uEventparam.struLeavePos.byOnPosition = m_iParam5;
        uEventparam.struLeavePos.bySensitivity = m_iParam6;
        memcpy(&uEventparam.struLeavePos.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        break;

    case VCA_ADV_REACH_HEIGHT:
        uEventparam.struReachHeight.dwCrossDirection = m_iParam1;
        memcpy(&uEventparam.struReachHeight.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        break;

    case VCA_STANDUP:
        uEventparam.struStandUp.bySensitivity = m_iParam1;
        uEventparam.struStandUp.byHeightThreshold = m_iParam2;
        uEventparam.struStandUp.wDuration = m_iParam3;
        memcpy(&uEventparam.struReachHeight.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        break;

	default:
		break;
	}

    switch (struEventTypeEx)
	{
    case ENUM_VCA_EVENT_COMBINED_RULE:
        uEventparam.struCombinedRule.byRuleSequence = m_comboRuleSequence.GetCurSel();
        uEventparam.struCombinedRule.dwMinInterval = m_dwMinInterval;
        uEventparam.struCombinedRule.dwMaxInterval = m_dwMaxInterval;
        uEventparam.struCombinedRule.struRule1Raram.byRuleID = m_byRuleID1;
        uEventparam.struCombinedRule.struRule2Raram.byRuleID = m_byRuleID2;
        break;
    case ENUM_VCA_EVENT_BLACKBOARD_WRITE:
        memcpy(&uEventparam.struBlackboardWrite.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        break;
    case ENUM_VCA_EVENT_PEOPLENUM_CHANGE:
        uEventparam.struPeopleNumChange.bySensitivity = m_iParam1;
        uEventparam.struPeopleNumChange.byPeopleNumThreshold = m_iParam2;
        uEventparam.struPeopleNumChange.byDetectMode = m_iParam3;
        uEventparam.struPeopleNumChange.byNoneStateEffective = m_iParam4;
        uEventparam.struPeopleNumChange.wDuration = m_iParam5;
        memcpy(&uEventparam.struPeopleNumChange.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        break;
    default:
		break;
    }
}

void CDlgVcaPositionRule::SetVcaEventParaV42(NET_VCA_EVENT_UNION &uEventparam, WORD wEventType)
{
    switch (wEventType)
    {
    case ENUM_VCA_EVENT_TRAVERSE_PLANE:
        memcpy(&uEventparam.struTraversePlane.struPlaneBottom, &m_struVcaLine[m_iCurRuleID], sizeof(NET_VCA_LINE));
        uEventparam.struTraversePlane.dwCrossDirection = (VCA_CROSS_DIRECTION)m_comboAlarmDirect.GetCurSel();
        uEventparam.struTraversePlane.byDetectionTarget = m_comDetTarget.GetCurSel();
        uEventparam.struTraversePlane.byPriority = m_comboPriority.GetCurSel();
        uEventparam.struTraversePlane.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
        break;
    case ENUM_VCA_EVENT_ENTER_AREA:
        uEventparam.struArea.byDetectionTarget = m_comDetTarget.GetCurSel();
        uEventparam.struArea.byPriority = m_comboPriority.GetCurSel();
        memcpy(&uEventparam.struArea.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        uEventparam.struArea.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
        
        break;
    case ENUM_VCA_EVENT_EXIT_AREA:
        uEventparam.struArea.byDetectionTarget = m_comDetTarget.GetCurSel();
        uEventparam.struArea.byPriority = m_comboPriority.GetCurSel();
        memcpy(&uEventparam.struArea.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        uEventparam.struArea.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
        break;
    case ENUM_VCA_EVENT_INTRUSION:
        uEventparam.struIntrusion.byDetectionTarget = m_comDetTarget.GetCurSel();
        uEventparam.struIntrusion.byPriority = m_comboPriority.GetCurSel();
        uEventparam.struIntrusion.wDuration = (WORD)m_iAlarmDelay;
        memcpy(&uEventparam.struIntrusion.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        uEventparam.struIntrusion.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
        break;
    case ENUM_VCA_EVENT_LOITER:
        uEventparam.struLoiter.wDuration = (WORD)m_iAlarmPersist;
        memcpy(&uEventparam.struLoiter.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        uEventparam.struLoiter.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
        break;
    case ENUM_VCA_EVENT_LEFT_TAKE:
        uEventparam.struTakeTeft.wDuration = (WORD)m_iAlarmPersist;
        uEventparam.struTakeTeft.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
        memcpy(&uEventparam.struTakeTeft.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        break;
    case ENUM_VCA_EVENT_PARKING:
        uEventparam.struParking.wDuration = (WORD)m_iAlarmPersist;
        memcpy(&uEventparam.struParking.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        uEventparam.struParking.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
        break;
    case ENUM_VCA_EVENT_RUN:
        uEventparam.struRun.byDetectionTarget = m_comDetTarget.GetCurSel();
        uEventparam.struRun.fRunDistance = m_fMaxDistance;
        memcpy(&uEventparam.struRun.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        uEventparam.struRun.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
        break;
    case ENUM_VCA_EVENT_HIGH_DENSITY:
        uEventparam.struHighDensity.fDensity = m_fDenstityRate;
        memcpy(&uEventparam.struHighDensity.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        uEventparam.struHighDensity.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
        break;
    case ENUM_VCA_EVENT_STICK_UP:
        memcpy(&uEventparam.struStickUp.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        uEventparam.struStickUp.wDuration = (WORD)m_iAlarmPersist;
        uEventparam.struStickUp.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
        break;
    case ENUM_VCA_EVENT_INSTALL_SCANNER:
        memcpy(&uEventparam.struScanner.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        uEventparam.struScanner.wDuration = (WORD)m_iReadCardTimePersist;
        uEventparam.struScanner.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
        break;
        
    case ENUM_VCA_EVENT_LECTURE:
        uEventparam.struLecture.wDuration = (WORD)m_iAlarmDelay;
        memcpy(&uEventparam.struLecture.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        uEventparam.struLecture.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
        uEventparam.struLecture.byTrackingMode = (BYTE)(m_comboTrackingMode.GetCurSel());
        uEventparam.struLecture.byZoomMode = (BYTE)(m_comboZoomMode.GetCurSel());
        break;
    case ENUM_VCA_EVENT_ANSWER:
        memcpy(&uEventparam.struAnswer.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        uEventparam.struAnswer.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
        break;
    case ENUM_VCA_EVENT_LEFT:
        uEventparam.struLeft.wDuration = (WORD)m_iAlarmPersist;
        uEventparam.struLeft.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
        memcpy(&uEventparam.struLeft.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        break;
    case ENUM_VCA_EVENT_TAKE:
        uEventparam.struTake.wDuration = (WORD)m_iAlarmPersist;
        uEventparam.struTake.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
        memcpy(&uEventparam.struTake.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
        break;
    default:
        break;
	}   
}
/*********************************************************
  Function:	OnCheckhandletype4
  Desc:		
  Input:	
  Output:	
  Return:	void 
**********************************************************/
void CDlgVcaPositionRule::OnCheckhandletype4() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
//	m_listAlarmOut.EnableWindow(m_bHandleType4);
}

/*********************************************************
  Function:	SetRuleBehaviorCfg
  Desc:		Setup Behavior Analysis Rule
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgVcaPositionRule::SetRuleBehaviorCfg()
{
	char szLan[128] = {0};
	char sbufCn[128] = {0};
	char sbufEn[128] = {0};
    int i,j = 0;
    DWORD  dwRelIndex = 0;
    if (/*(g_struDeviceInfo[m_iDevIndex].bySupport7 & 0x01) != 0x01*/true)
    {
        strncpy((char*)m_struPtzPosition.byPtzPositionName, m_csPtzPositionName.GetBuffer(0), (sizeof(m_struPtzPosition.byPtzPositionName) - 1));
	    m_struPtzPosition.byEnable = m_bChkPositionEn;
        DWORD dwReturn = 0;

        NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_PTZPOS, m_iVcaChannel, &m_struPtzPosition.struPtzPos, sizeof(m_struPtzPosition.struPtzPos), &dwReturn);

        memcpy(&m_struPositionRule.struVcaRuleCfg, &m_struRuleCfg, sizeof(m_struRuleCfg));
        memcpy(&m_struPositionRule.struPtzPosition, &m_struPtzPosition, sizeof(m_struPtzPosition));
    
	    m_struPositionRule.byTrackEnable = m_bChkTrackEn;
	    m_struPositionRule.wTrackDuration = m_dwTrackTime;

//         if (!NET_DVR_SetPositionRule_V41(m_lServerID, m_iVcaChannel, m_iPositionIndex, &m_struPositionRule))
//         {
//             g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SetPositionRule_V41 %d", m_iVcaChannel);
//             sprintf(sbufCn, "Set Behavior Rule of channel %d failed", m_iVcaChannel);
//             sprintf(sbufEn, "Fail to Set Channal%d VCA behavior rule", m_iVcaChannel);
//             g_StringLanType(szLan, sbufCn, sbufEn);
//             MessageBox(szLan);
//             RefreshBehavior(m_iPositionIndex,m_iCurRuleID); 
//         }
//         else//save config
//         {
//             g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SetPositionRule_V41 %d", m_iVcaChannel);
//             sprintf(sbufCn, "Set Behavior Rule of channel %d Successfully", m_iVcaChannel);
//             sprintf(sbufEn, "Success to Set Channal%d VCA behavior rule", m_iVcaChannel);
//             g_StringLanType(szLan, sbufCn, sbufEn);
//             MessageBox(szLan);
//     	}
    }
   

    memset(&m_struChanGroup, 0, sizeof(m_struChanGroup));
    m_struChanGroup.dwSize = sizeof(m_struChanGroup);
    m_struChanGroup.dwChannel = m_cmbVCARuleChannel.GetItemData(m_cmbVCARuleChannel.GetCurSel());
    m_struChanGroup.dwGroup = m_cmbVCARuleGroupNo.GetCurSel();
    m_struChanGroup.byID = m_comboPositionIndex.GetCurSel() + 1;
    m_struChanGroup.dwPositionNo = m_comboPositionIndex.GetCurSel() + 1;
    
    if (m_iCurRuleID<8)
    {
        memcpy(&m_struRuleCfg.struRule[m_iCurRuleID], &m_struOneRule, sizeof(NET_VCA_ONE_RULE_V41));
    } 
    else
    {
        memcpy(&m_struRuleCfgEx.struRule[m_iCurRuleID-8], &m_struOneRule, sizeof(NET_VCA_ONE_RULE_V41));
    }
    

    memset(&m_struRuleCfgV42, 0, sizeof(m_struRuleCfgV42));
    // data copy
    m_struRuleCfgV42.dwSize = sizeof(m_struRuleCfgV42);
    m_struRuleCfgV42.byPicProType = m_struRuleCfg.byPicProType;
    m_struRuleCfgV42.byUpLastAlarm = m_struRuleCfg.byUpLastAlarm;
    m_struRuleCfgV42.byPicRecordEnable = m_struRuleCfg.byPicRecordEnable;
    
    memcpy(&m_struRuleCfgV42.struPicParam, &m_struRuleCfg.struPictureParam, sizeof(NET_DVR_JPEGPARA));
    for (i = 0; i< MAX_REL_SNAPCHAN_NUM; i++)
    {
        m_struRuleCfgV42.wRelSnapChan[i] = m_struRuleCfg.wRelSnapChan[i];
    }
    
    for (i = 0; i< MAX_RULE_NUM_V42; i++)
    {
        if (i < 8)
        {
            OneRuleV41ToOneRuleV42(&m_struRuleCfg.struRule[i], &m_struRuleCfgV42.struRule[i], TRUE);
        } 
        else
        {
            OneRuleV41ToOneRuleV42(&m_struRuleCfgEx.struRule[i-8], &m_struRuleCfgV42.struRule[i], TRUE);
        }
        
        m_struRuleCfgV42.struRule[i].byActive = m_struRuleCfg.struRule[i].byActive;
        if (0 != m_struRuleCfg.struRule[i].wEventTypeEx)
        {
            m_struRuleCfgV42.struRule[i].wEventType = m_struRuleCfg.struRule[i].wEventTypeEx;
        }
        else
        {
            EventTypeToEventTypeEx((VCA_EVENT_TYPE)m_struRuleCfg.struRule[i].dwEventType, m_struRuleCfgV42.struRule[i].wEventType);
        }

        m_struRuleCfgV42.struRule[i].wAlarmDelay = m_struRuleCfg.struRule[i].wAlarmDelay;
    }
    
    memcpy(&m_struRuleCfgV42.struPTZPosition, &m_struPtzPosition,sizeof(m_struPtzPosition)); 
    m_struRuleCfgV42.byTrackEnable = m_bChkTrackEn;
	m_struRuleCfgV42.wTrackDuration = m_dwTrackTime;
	m_struRuleCfgV42.struRule[m_iCurRuleID].byEventPriority = m_comEventPriority.GetCurSel();
    SetVcaEventParaV42(m_struRuleCfgV42.struRule[m_iCurRuleID].uEventParam, m_struRuleCfgV42.struRule[m_iCurRuleID].wEventType);
    
    
    DWORD dwRetList = NET_DVR_NOERROR;
    BOOL bRet = NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_RULECFG_V42,1,&m_struChanGroup, sizeof(m_struChanGroup),&dwRetList,&m_struRuleCfgV42, sizeof(m_struRuleCfgV42));
    
    if (bRet)
    {
        if (dwRetList == NET_DVR_NOERROR)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_RULECFG_V42 Channel[%d] Position[%d]",m_struChanGroup.dwChannel,  m_struChanGroup.byID);
            memcpy(&m_struRuleCfg, &m_struPositionRule.struVcaRuleCfg, sizeof(m_struRuleCfg));
          
        } 
        else
        {
            sprintf(szLan,"NET_DVR_SET_RULECFG_V42 Error[%d]", dwRetList);
            AfxMessageBox(szLan);
            return ;
        }
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_RULECFG_V42 Channel[%d]Position[%d]", m_struChanGroup.dwChannel,  m_struChanGroup.byID);
        return ;
    }
}


/*********************************************************
  Function:	SaveTempRuleBehaviorCfg
  Desc:		Setup Behavior Analysis Rule
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgVcaPositionRule::SaveTempRuleBehaviorCfg()
{
	char szLan[128] = {0};
	char sbufCn[128] = {0};
	char sbufEn[128] = {0};
    int i,j = 0;
    DWORD  dwRelIndex = 0;
    if (/*(g_struDeviceInfo[m_iDevIndex].bySupport7 & 0x01) != 0x01*/true)
    {
        strncpy((char*)m_struPtzPosition.byPtzPositionName, m_csPtzPositionName.GetBuffer(0), (sizeof(m_struPtzPosition.byPtzPositionName) - 1));
	    m_struPtzPosition.byEnable = m_bChkPositionEn;
        DWORD dwReturn = 0;

        NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_PTZPOS, m_iVcaChannel, &m_struPtzPosition.struPtzPos, sizeof(m_struPtzPosition.struPtzPos), &dwReturn);
    

        memcpy(&m_struPositionRule.struVcaRuleCfg, &m_struRuleCfg, sizeof(m_struRuleCfg));
        memcpy(&m_struPositionRule.struPtzPosition, &m_struPtzPosition, sizeof(m_struPtzPosition));
    
	    m_struPositionRule.byTrackEnable = m_bChkTrackEn;
	    m_struPositionRule.wTrackDuration = m_dwTrackTime;

    }
   

    memset(&m_struChanGroup, 0, sizeof(m_struChanGroup));
    m_struChanGroup.dwSize = sizeof(m_struChanGroup);
    m_struChanGroup.dwChannel = m_cmbVCARuleChannel.GetItemData(m_cmbVCARuleChannel.GetCurSel());
    m_struChanGroup.dwGroup = m_cmbVCARuleGroupNo.GetCurSel();
    m_struChanGroup.byID = m_comboPositionIndex.GetCurSel() + 1;
    m_struChanGroup.dwPositionNo = m_comboPositionIndex.GetCurSel() + 1;
    
    if (m_iCurRuleID<8)
    {
        memcpy(&m_struRuleCfg.struRule[m_iCurRuleID], &m_struOneRule, sizeof(NET_VCA_ONE_RULE_V41));
    } 
    else
    {
        memcpy(&m_struRuleCfgEx.struRule[m_iCurRuleID-8], &m_struOneRule, sizeof(NET_VCA_ONE_RULE_V41));
    }
    

    memset(&m_struRuleCfgV42, 0, sizeof(m_struRuleCfgV42));
    // data copy
    m_struRuleCfgV42.dwSize = sizeof(m_struRuleCfgV42);
    m_struRuleCfgV42.byPicProType = m_struRuleCfg.byPicProType;
    m_struRuleCfgV42.byUpLastAlarm = m_struRuleCfg.byUpLastAlarm;
    m_struRuleCfgV42.byPicRecordEnable = m_struRuleCfg.byPicRecordEnable;
    memcpy(&m_struRuleCfgV42.struPicParam, &m_struRuleCfg.struPictureParam, sizeof(NET_DVR_JPEGPARA));
    for (i = 0; i< MAX_REL_SNAPCHAN_NUM; i++)
    {
        m_struRuleCfgV42.wRelSnapChan[i] = m_struRuleCfg.wRelSnapChan[i];
    }
    
    for (i = 0; i< MAX_RULE_NUM_V42; i++)
    {
        if (i < 8)
        {
            OneRuleV41ToOneRuleV42(&m_struRuleCfg.struRule[i], &m_struRuleCfgV42.struRule[i], TRUE);
        } 
        else
        {
            OneRuleV41ToOneRuleV42(&m_struRuleCfgEx.struRule[i-8], &m_struRuleCfgV42.struRule[i], TRUE);
        }
    }
    
    memcpy(&m_struRuleCfgV42.struPTZPosition, &m_struPtzPosition,sizeof(m_struPtzPosition)); 
    m_struRuleCfgV42.byTrackEnable = m_bChkTrackEn;
	m_struRuleCfgV42.wTrackDuration = m_dwTrackTime;
	
    
}

/*********************************************************
  Function:	OnChangeEditRuleName
  Desc:		Modify rule name
  Input:	
  Output:	
  Return:	void 
**********************************************************/
void CDlgVcaPositionRule::OnChangeEditRuleName() 
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

/*********************************************************
  Function:	OnChangeEditAlarmDelay
  Desc:		
  Input:	
  Output:	
  Return:	void 
**********************************************************/
void CDlgVcaPositionRule::OnChangeEditAlarmDelay() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
//	UpdateData(TRUE);
	
}

/*********************************************************
  Function:	OnChangeEditAlarmPersist
  Desc:		
  Input:	
  Output:	
  Return:	void 
**********************************************************/
void CDlgVcaPositionRule::OnChangeEditAlarmPersist() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
//	UpdateData(TRUE);
}

/*********************************************************
  Function:	OnChangeEditDenstityRate
  Desc:		
  Input:	
  Output:	
  Return:	void 
**********************************************************/
void CDlgVcaPositionRule::OnChangeEditDenstityRate() 
{
}

/*********************************************************
  Function:	OnChangeEditMaxDistance
  Desc:		
  Input:	
  Output:	
  Return:	void 
**********************************************************/
void CDlgVcaPositionRule::OnChangeEditMaxDistance() 
{

}

/*********************************************************
  Function:	OnChangeEditReadCardTimePersist
  Desc:		
  Input:	
  Output:	
  Return:	void 
**********************************************************/
void CDlgVcaPositionRule::OnChangeEditReadCardTimePersist() 
{
}

/*********************************************************
Function:InsertComboVcaType
Desc: According to device's ability type, insert type to m_comboVcaType
Input:	
Output:	
Return:	void 
**********************************************************/
BOOL CDlgVcaPositionRule::InsertComboVcaType()
{
	m_comboVcaType.ResetContent();
	int index = 0;
	if (m_iBBaseChanNum > 0)
	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "行为分析基本版", "Behavior of basic");
		m_comboVcaType.InsertString(index, szLan);
		m_comboVcaType.SetItemData(index, VCA_BEHAVIOR_BASE);
		index++;
	}
	if (m_iBAdvanceChanNum > 0)
	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "行为分析高级版", "Behavior of advanced");
		m_comboVcaType.InsertString(index, szLan);
		m_comboVcaType.SetItemData(index, VCA_BEHAVIOR_ADVANCE);
		index++;
	}
	if (m_iBFullChanNum > 0)
	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "行为分析完整版", "Behavior of full");
		m_comboVcaType.InsertString(index, szLan);
		m_comboVcaType.SetItemData(index, VCA_BEHAVIOR_FULL);
		index++;
	}
	if (m_iPlateChanNum > 0)
	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "车牌识别", "Plate Recognition");
		m_comboVcaType.InsertString(index, szLan);
		m_comboVcaType.SetItemData(index, VCA_PLATE);
		index++;
	}
	if (m_iAtmChanNum > 0)
	{
		m_comboVcaType.InsertString(index, "ATM");
		m_comboVcaType.SetItemData(index, VCA_ATM);
	}
	return TRUE;
}

/*********************************************************
Function:SetComboVcaType
Desc:   
Input:	
Output:	
Return:	void 
**********************************************************/
void CDlgVcaPositionRule::SetComboVcaType()
{
	
	for (int i = 0; i < m_comboVcaType.GetCount(); i++)
	{
		if (m_comboVcaType.GetItemData(i) == m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byVCAType )
		{
			m_comboVcaType.SetCurSel(i);
			return;
		}
		
	}
}
/*********************************************************
  Function:	RefreshBehavior
  Desc:		refresh Behavior control
  Input:	int iRuleID
  Output:	
  Return:	void 
**********************************************************/
void CDlgVcaPositionRule::RefreshBehavior(int iPosition, int iRuleID)
{
	memset(&m_struRuleCfg, 0,sizeof(NET_VCA_RULECFG));
	
	char szLan[128] = {0};
    int i,j = 0;
    
   /* if (!NET_DVR_GetPositionRule_V41(m_lServerID, m_iVcaChannel, iPosition, &m_struPositionRule))
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetPositionRule_V41 %d", m_iVcaChannel);
        char sbufCn[128] = {0};
        char sbufEn[128] = {0};
        sprintf(sbufCn, "获取通道%d行为规则信息失败",  m_iVcaChannel);
		sprintf(sbufEn, "Fail to get Channel%d VCA behavior rule", m_iVcaChannel);
		g_StringLanType(szLan, sbufCn, sbufEn);
		MessageBox(szLan);
        //OnCancel();
        return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetPositionRule_V41 %d", m_iVcaChannel);
        memcpy(&m_struRuleCfg, &m_struPositionRule.struVcaRuleCfg, sizeof(m_struRuleCfg));
        memcpy(&m_struPtzPosition, &m_struPositionRule.struPtzPosition, sizeof(m_struPtzPosition));
	}
*/

    memset(&m_struChanGroup, 0, sizeof(m_struChanGroup));
    m_struChanGroup.dwSize = sizeof(m_struChanGroup);
    m_struChanGroup.dwChannel = m_cmbVCARuleChannel.GetItemData(m_cmbVCARuleChannel.GetCurSel());
    m_struChanGroup.dwGroup = m_cmbVCARuleGroupNo.GetCurSel();
    m_struChanGroup.byID = m_comboPositionIndex.GetCurSel() + 1;
    
    memset(&m_struRuleCfgV42, 0, sizeof(m_struRuleCfgV42));
    
    DWORD dwRetList = NET_DVR_NOERROR;
    BOOL bRet = NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_RULECFG_V42,1,&m_struChanGroup, sizeof(m_struChanGroup),&dwRetList,&m_struRuleCfgV42, sizeof(m_struRuleCfgV42));
    
    if (bRet)
    {
        if (dwRetList == NET_DVR_NOERROR)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_RULECFG_V42 Channel[%d] Position[%d]",m_struChanGroup.dwChannel,  m_struChanGroup.byID);
            memcpy(&m_struRuleCfg, &m_struPositionRule.struVcaRuleCfg, sizeof(m_struRuleCfg));
            m_struRuleCfg.dwSize = sizeof(m_struRuleCfg);
            m_struRuleCfg.byPicProType = m_struRuleCfgV42.byPicProType;
            m_struRuleCfg.byUpLastAlarm = m_struRuleCfgV42.byUpLastAlarm;
            m_struRuleCfg.byPicRecordEnable = m_struRuleCfgV42.byPicRecordEnable;
            memcpy(&m_struRuleCfg.struPictureParam, &m_struRuleCfgV42.struPicParam, sizeof(NET_DVR_JPEGPARA));
            for (i = 0; i< MAX_REL_SNAPCHAN_NUM; i++)
            {
                m_struRuleCfg.wRelSnapChan[i] = m_struRuleCfgV42.wRelSnapChan[i];
            }
            
            for (i = 0; i< MAX_RULE_NUM_V42; i++)
            {
                if (i < 8)
                {
                    OneRuleV41ToOneRuleV42(&m_struRuleCfg.struRule[i], &m_struRuleCfgV42.struRule[i], FALSE);
                } 
                else
                {
                    OneRuleV41ToOneRuleV42(&m_struRuleCfgEx.struRule[i-8], &m_struRuleCfgV42.struRule[i], FALSE);
                }
//                 m_struRuleCfg.struRule[i].byActive = m_struRuleCfgV42.struRule[i].byActive;
//                 m_struRuleCfg.struRule[i].wEventTypeEx = m_struRuleCfgV42.struRule[i].wEventType;
//                 m_struRuleCfg.struRule[i].wAlarmDelay = m_struRuleCfgV42.struRule[i].wAlarmDelay;
//                 
//                 memcpy(m_struRuleCfg.struRule[i].byRuleName,m_struRuleCfgV42.struRule[i].byRuleName, NAME_LEN);
//                 memcpy(&m_struRuleCfg.struRule[i].uEventParam,&m_struRuleCfgV42.struRule[i].uEventParam, sizeof(NET_VCA_EVENT_UNION));
//                 memcpy(&m_struRuleCfg.struRule[i].struSizeFilter,&m_struRuleCfgV42.struRule[i].struSizeFilter, sizeof(NET_VCA_SIZE_FILTER));
//                 memcpy(&m_struRuleCfg.struRule[i].struFilterStrategy,&m_struRuleCfgV42.struRule[i].struFilterStrategy, sizeof(NET_VCA_EVENT_UNION));
//                 memcpy(&m_struRuleCfg.struRule[i].struTriggerParam,&m_struRuleCfgV42.struRule[i].struTriggerParam, sizeof(NET_VCA_EVENT_UNION));
//                 memcpy(&m_struRuleCfg.struRule[i].struAlarmTime,&m_struRuleCfgV42.struRule[i].struAlarmTime, sizeof(NET_DVR_SCHEDTIME) * MAX_DAYS *MAX_TIMESEGMENT_V30);
//                 
//                 m_struRuleCfg.struRule[i].struHandleType.dwHandleType = m_struRuleCfgV42.struRule[i].struAlarmHandleType.dwHandleType;
//                 for (j = 0; j< MAX_CHANNUM_V30 &&m_struRuleCfgV42.struRule[i].struAlarmHandleType.dwRelAlarmOutChanNum ; j++)
//                 {
//                     if (m_struRuleCfgV42.struRule[i].struAlarmHandleType.dwRelAlarmOut[j] != 0xffffffff)
//                     {
//                         if (m_struRuleCfgV42.struRule[i].struAlarmHandleType.dwRelAlarmOut[j] < MAX_ALARMOUT_V30)
//                         {
//                             m_struRuleCfg.struRule[i].struHandleType.byRelAlarmOut[m_struRuleCfgV42.struRule[i].struAlarmHandleType.dwRelAlarmOut[j] -1] = 1;
//                         }
//                     }
//                     else
//                     {
//                         break;
//                     }
//                 }
//                 
//                 
//                 for (j = 0; j< MAX_CHANNUM_V30  ; j++)
//                 {
//                     if (m_struRuleCfgV42.struRule[i].dwRelRecordChan[j] != 0xffffffff)
//                     {
//                         if (m_struRuleCfgV42.struRule[i].dwRelRecordChan[j] < MAX_CHANNUM_V30)
//                         {
//                             m_struRuleCfg.struRule[i].byRelRecordChan[m_struRuleCfgV42.struRule[i].dwRelRecordChan[j] -1 ] = 1;
//                         }
//                     }
//                     else
//                     {
//                         break;
//                     }
//                 }
            }
            
            //memcpy(&m_struPtzPosition, &m_struRuleCfgV42.struPTZPosition, sizeof(m_struPtzPosition)); 
        } 
        else
        {
            sprintf(szLan,"NET_DVR_GET_RULECFG_V42 Error[%s][%d]",NET_DVR_GetErrorMsg(), NET_DVR_GetLastError());
            AfxMessageBox(szLan);
            return ;
        }
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_RULECFG_V42 Channel[%d]Position[%d]", m_struChanGroup.dwChannel,  m_struChanGroup.byID);
        return ;
    }

	m_bChkTrackEn = m_struPositionRule.byTrackEnable;
	m_dwTrackTime = m_struPositionRule.wTrackDuration;
	m_comboProPicType.SetCurSel(m_struRuleCfg.byPicProType); //Get actions for alarm
	m_comboResolution.SetCurSel(m_struRuleCfg.struPictureParam.wPicSize);//image resolution
	m_comboPicQuality.SetCurSel(m_struRuleCfg.struPictureParam.wPicQuality);//image quality
	
	m_comboRuleID.SetCurSel(iRuleID);
    if (iRuleID<8)
    {
        memcpy(&m_struOneRule, &m_struRuleCfg.struRule[iRuleID], sizeof(NET_VCA_ONE_RULE_V41));
    } 
    else
    {
        memcpy(&m_struOneRule, &m_struRuleCfgEx.struRule[iRuleID-8], sizeof(NET_VCA_ONE_RULE_V41));
    }
	
	
// 	if (m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_LECTURE)
// 	{
// 		m_comboRuleType.SetCurSel(8);
// 	}
// 	else if (m_struOneRule.wEventTypeEx == ENUM_VCA_EVENT_ANSWER)
// 	{
// 		m_comboRuleType.SetCurSel(9);
// 	}
// 	else
// 	{
		GetEventTypeSet(m_struOneRule.dwEventType);
//	}
	
	m_bRuleActive = m_struOneRule.byActive;
	EnableRuleWindow(m_bRuleActive);
	SetRuleActiveAble(m_bRuleActive);
	//rule name
	m_csRuleName = m_struRuleCfg.struRule[iRuleID].byRuleName;
	
	memcpy(&m_struAlarmTime[0][0],&m_struOneRule.struAlarmTime[0][0], MAX_DAYS*MAX_TIMESEGMENT_V30*sizeof(NET_DVR_SCHEDTIME));
	
	RefreshOneRule(m_struOneRule);
}

void CDlgVcaPositionRule::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	CDialog::PostNcDestroy();
}

void CDlgVcaPositionRule::OnBtnTrackCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaTrackCfg dlg(this);
    
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_iChannel = m_iVcaChannel;
    
    dlg.DoModal();
}

void CDlgVcaPositionRule::OnBtnGetPtz() 
{
	// TODO: Add your control notification handler code here
    DWORD dwReturn = 0;

    m_iVcaChannel = m_cmbVCARuleChannel.GetItemData(m_cmbVCARuleChannel.GetCurSel());
    BOOL bRet = NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_PTZPOS, m_iVcaChannel, &(m_struPtzPosition.struPtzPos), sizeof(m_struPtzPosition.struPtzPos), &dwReturn);
    if (!bRet)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PTZPOS");
        MessageBox("设置PTZ坐标失败");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PTZPOS");
    }


}

void CDlgVcaPositionRule::OnBtnPtzCtrl() 
{
	// TODO: Add your control notification handler code here
	 CDlgPtzCtrl dlg;
     dlg.m_lPlayHandle = m_lPlayHandle;
     dlg.DoModal();
}

void CDlgVcaPositionRule::OnBtnEnableCalibrate() 
{
	// TODO: Add your control notification handler code here
    
    if (m_struTrackCfg.byEnable)
    {
        m_struTrackCfg.byEnable = FALSE;
    }
    else
    {
        m_struTrackCfg.byEnable = TRUE;
    }
    if (SetTrackCfg())
    {
        if (m_struTrackCfg.byEnable)
        {
            GetDlgItem(IDC_BTN_ENABLE_CALIBRATE)->SetWindowText("禁止跟踪");

        }
        else
        {
            GetDlgItem(IDC_BTN_ENABLE_CALIBRATE)->SetWindowText("启用跟踪");
        }
        GetDlgItem(IDC_BTN_DOME_CONFIG)->EnableWindow(!m_struTrackCfg.byEnable);
  //      GetDlgItem(IDC_BTN_TRACK_CFG)->EnableWindow(!m_struTrackCfg.byEnable);
    }
    }

void CDlgVcaPositionRule::OnBtnDomeConfig() 
{
    CDlgIPDomeLocalCfg dlg;
    
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_iChannel = m_iVcaChannel;	
    dlg.DoModal();
}

void CDlgVcaPositionRule::OnSelchangeComboPositionIndex() 
{
	m_iPositionIndex = m_comboPositionIndex.GetCurSel() + 1;
    UpdateData(FALSE);
    OnSelchangeComboRuleId();
}

void CDlgVcaPositionRule::OnBtnPositionTrack() 
{
    CDlgPositionTrackCfg dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();	
}

void CDlgVcaPositionRule::OnBtnPositionLimitangle() 
{
    OnBtnGetPtz(); // get position ptz 
    CDlgLimitAngle dlg;
    dlg.m_lPlayHandle = m_lPlayHandle;
    dlg.m_iPositionIndex = m_iPositionIndex;
    dlg.m_iLimitAngleType = POSITION_LIMIT_ANGLE;
    dlg.m_lServerID = m_lServerID;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVcaPositionRule::OnBtnGetRuleCfg() 
{
    // TODO: Add your control notification handler code here
    GetRuleCfg();
    m_comboRuleID.SetCurSel(0);
    OnSelchangeComboRuleId(); 
}

BOOL CDlgVcaPositionRule::EventTypeToEventTypeEx(VCA_EVENT_TYPE struEventType, WORD& wEventTypeEx)
{
    BOOL iRet = TRUE;
    switch (struEventType)
    {
	case VCA_TRAVERSE_PLANE:
        wEventTypeEx = ENUM_VCA_EVENT_TRAVERSE_PLANE;
        break;
    case VCA_ENTER_AREA:
        wEventTypeEx = ENUM_VCA_EVENT_ENTER_AREA;
        break;
    case VCA_EXIT_AREA:
        wEventTypeEx = ENUM_VCA_EVENT_EXIT_AREA;
        break;
    case VCA_INTRUSION:
        wEventTypeEx = ENUM_VCA_EVENT_INTRUSION;
        break;
    case VCA_LOITER:
        wEventTypeEx = ENUM_VCA_EVENT_LOITER;
        break;
    case VCA_LEFT_TAKE:
        wEventTypeEx = ENUM_VCA_EVENT_LEFT_TAKE;
        break;
    case VCA_PARKING:
        wEventTypeEx = ENUM_VCA_EVENT_PARKING;
        break;
    case VCA_RUN:
        wEventTypeEx = ENUM_VCA_EVENT_RUN;
        break;
    case VCA_HIGH_DENSITY:
        wEventTypeEx = ENUM_VCA_EVENT_HIGH_DENSITY;
        break;
    case VCA_VIOLENT_MOTION:
        wEventTypeEx = ENUM_VCA_EVENT_VIOLENT_MOTION;
        break;
    case VCA_REACH_HIGHT:
        wEventTypeEx = ENUM_VCA_EVENT_REACH_HIGHT;
        break;
    case VCA_GET_UP:
        wEventTypeEx = ENUM_VCA_EVENT_GET_UP;
        break;
    case VCA_LEFT:
        wEventTypeEx = ENUM_VCA_EVENT_LEFT;
        break;
    case VCA_TAKE:
        wEventTypeEx = ENUM_VCA_EVENT_TAKE;
        break;
    case VCA_LEAVE_POSITION:
        wEventTypeEx = ENUM_VCA_EVENT_LEAVE_POSITION;
        break;
    case VCA_TRAIL:
        wEventTypeEx = ENUM_VCA_EVENT_TRAIL;
        break;
    case VCA_KEY_PERSON_GET_UP:
        wEventTypeEx = ENUM_VCA_EVENT_KEY_PERSON_GET_UP;
        break;
    case VCA_STANDUP:
        wEventTypeEx = ENUM_VCA_EVENT_STANDUP;
        break;
    case VCA_FALL_DOWN:
        wEventTypeEx = ENUM_VCA_EVENT_FALL_DOWN;
        break;
    case VCA_AUDIO_ABNORMAL:
        wEventTypeEx = ENUM_VCA_EVENT_AUDIO_ABNORMAL;
        break;
    case VCA_ADV_REACH_HEIGHT:
        wEventTypeEx = ENUM_VCA_EVENT_ADV_REACH_HEIGHT;
        break;
    case VCA_LECTURE:
        wEventTypeEx = ENUM_VCA_EVENT_LECTURE;
        break;
    case VCA_ANSWER:
        wEventTypeEx = ENUM_VCA_EVENT_ANSWER;
        break;
    case VCA_HUMAN_ENTER:
        wEventTypeEx = ENUM_VCA_EVENT_HUMAN_ENTER;
        break;
    case VCA_OVER_TIME:
        wEventTypeEx = ENUM_VCA_EVENT_OVER_TIME;
        break;
    case VCA_STICK_UP:
        wEventTypeEx = ENUM_VCA_EVENT_STICK_UP;
        break;
    case VCA_INSTALL_SCANNER:
        wEventTypeEx = ENUM_VCA_EVENT_INSTALL_SCANNER;
        break;
    default:
         iRet = FALSE;
		break;
    }

    return iRet;
}

BOOL CDlgVcaPositionRule::EventTypeExToEventType(VCA_EVENT_TYPE& struEventType, WORD wEventTypeEx)
{
    BOOL iRet = TRUE;
    switch (wEventTypeEx)
    {
    case ENUM_VCA_EVENT_TRAVERSE_PLANE:
        struEventType = VCA_TRAVERSE_PLANE;
        break;
    case ENUM_VCA_EVENT_ENTER_AREA:
        struEventType = VCA_ENTER_AREA;
        break;
    case ENUM_VCA_EVENT_EXIT_AREA:
        struEventType = VCA_EXIT_AREA;
        break;
    case ENUM_VCA_EVENT_INTRUSION:
        struEventType = VCA_INTRUSION;
        break;
    case ENUM_VCA_EVENT_LOITER:
        struEventType = VCA_LOITER;
        break;
    case ENUM_VCA_EVENT_LEFT_TAKE:
        struEventType = VCA_LEFT_TAKE;
        break;
    case ENUM_VCA_EVENT_PARKING:
        struEventType = VCA_PARKING;
        break;
    case ENUM_VCA_EVENT_RUN:
        struEventType = VCA_RUN;
        break;
    case ENUM_VCA_EVENT_HIGH_DENSITY:
        struEventType = VCA_HIGH_DENSITY;
        break;
    case ENUM_VCA_EVENT_VIOLENT_MOTION:
        struEventType = VCA_VIOLENT_MOTION;
        break;
    case ENUM_VCA_EVENT_REACH_HIGHT:
        struEventType = VCA_REACH_HIGHT;
        break;
    case ENUM_VCA_EVENT_GET_UP:
        struEventType = VCA_GET_UP;
        break;
    case ENUM_VCA_EVENT_LEFT:
        struEventType = VCA_LEFT;
        break;
    case ENUM_VCA_EVENT_TAKE:
        struEventType = VCA_TAKE;
        break;
    case ENUM_VCA_EVENT_LEAVE_POSITION:
        struEventType = VCA_LEAVE_POSITION;
        break;
    case ENUM_VCA_EVENT_TRAIL:
        struEventType = VCA_TRAIL;
        break;
    case ENUM_VCA_EVENT_KEY_PERSON_GET_UP:
        struEventType = VCA_KEY_PERSON_GET_UP;
        break;
    case ENUM_VCA_EVENT_STANDUP:
        struEventType = VCA_STANDUP;
        break;
    case ENUM_VCA_EVENT_FALL_DOWN:
        struEventType = VCA_FALL_DOWN;
        break;
    case ENUM_VCA_EVENT_AUDIO_ABNORMAL:
        struEventType = VCA_AUDIO_ABNORMAL;
        break;
    case ENUM_VCA_EVENT_ADV_REACH_HEIGHT:
        struEventType = VCA_ADV_REACH_HEIGHT;
        break;
    case ENUM_VCA_EVENT_LECTURE:
        struEventType = VCA_LECTURE;
        break;
    case ENUM_VCA_EVENT_ANSWER:
        struEventType = VCA_ANSWER;
        break;
    case ENUM_VCA_EVENT_HUMAN_ENTER:
        struEventType = VCA_HUMAN_ENTER;
        break;
    case ENUM_VCA_EVENT_OVER_TIME:
        struEventType = VCA_OVER_TIME;
        break;
    case ENUM_VCA_EVENT_STICK_UP:
        struEventType = VCA_STICK_UP;
        break;
    case ENUM_VCA_EVENT_INSTALL_SCANNER:
        struEventType = VCA_INSTALL_SCANNER;
        break;
    default:
        iRet = FALSE;
        break;
    }
    
    return iRet;
}

void CDlgVcaPositionRule::OneRuleV41ToOneRuleV42(NET_VCA_ONE_RULE_V41* lpOld, NET_VCA_ONE_RULE_V42* lpV42, BOOL bV41ToV42)
{
    int j = 0;
	int k = 0;

    if (bV41ToV42)
    {
        lpV42->byActive = lpOld->byActive;
        if (0 != lpOld->wEventTypeEx)
        {
            lpV42->wEventType = lpOld->wEventTypeEx;
        } 
        else
        {
            EventTypeToEventTypeEx((VCA_EVENT_TYPE)lpOld->dwEventType, lpV42->wEventType);
        }
        memcpy(lpV42->byRuleName, lpOld->byRuleName, NAME_LEN);
        memcpy(&lpV42->struSizeFilter, &lpOld->struSizeFilter, sizeof(NET_VCA_SIZE_FILTER));
        memcpy(&lpV42->uEventParam, &lpOld->uEventParam, sizeof(NET_VCA_EVENT_UNION));

        for (j=0; j<MAX_DAYS; j++)
        {
            for (k=0; k<MAX_TIMESEGMENT_V30; k++)
            {
                lpV42->struAlarmTime[j][k] = lpOld->struAlarmTime[j][k];
            }
        }
        
        lpV42->struAlarmHandleType.dwHandleType = lpOld->struHandleType.dwHandleType;
        
        DWORD dwRelAlarmOutChanNum = 0;
        memset(lpV42->struAlarmHandleType.dwRelAlarmOut, 0xffffffff, sizeof(lpV42->struAlarmHandleType.dwRelAlarmOut));
        for (j=0; j<MAX_ALARMOUT_V30; j++)
        {
            if (lpOld->struHandleType.byRelAlarmOut[j] && dwRelAlarmOutChanNum <MAX_CHANNUM_V30)
            {
                
                lpV42->struAlarmHandleType.dwRelAlarmOut[dwRelAlarmOutChanNum] = j+1;
                dwRelAlarmOutChanNum ++;
            }
            
        }
        lpV42->struAlarmHandleType.dwRelAlarmOutChanNum = dwRelAlarmOutChanNum;
        
        DWORD dwRelRecordChanNum  = 0;
        memset(lpV42->dwRelRecordChan, 0xffffffff, sizeof(lpV42->dwRelRecordChan));
        for (j=0; j<MAX_CHANNUM_V30; j++)
        {
            if (lpOld->byRelRecordChan[j] && dwRelRecordChanNum <MAX_CHANNUM_V30)
            {
                lpV42->dwRelRecordChan[dwRelRecordChanNum] = j+1;
                dwRelRecordChanNum ++;
            }
        }
        
        memcpy(&lpV42->struFilterStrategy, &lpOld->struFilterStrategy, sizeof(NET_VCA_FILTER_STRATEGY));
        memcpy(&lpV42->struTriggerParam, &lpOld->struTriggerParam, sizeof(NET_VCA_RULE_TRIGGER_PARAM));
    }
    else
    {
        memset(lpOld,0,sizeof(NET_VCA_ONE_RULE_V41));
        lpOld->byActive = lpV42->byActive;
        lpOld->wEventTypeEx = lpV42->wEventType;
        memcpy(lpOld->byRuleName, lpV42->byRuleName, NAME_LEN);
        memcpy(&lpOld->struSizeFilter, &lpV42->struSizeFilter, sizeof(NET_VCA_SIZE_FILTER));
        memcpy(&lpOld->uEventParam, &lpV42->uEventParam, sizeof(NET_VCA_EVENT_UNION));
        for (j=0; j<MAX_DAYS; j++)
        {
            for (k=0; k<MAX_TIMESEGMENT_V30; k++)
            {
                lpOld->struAlarmTime[j][k] = lpV42->struAlarmTime[j][k];
            }
        }
        
        lpOld->struHandleType.dwHandleType = lpV42->struAlarmHandleType.dwHandleType; 
        for (j = 0; j< MAX_CHANNUM_V30 && lpV42->struAlarmHandleType.dwRelAlarmOutChanNum ; j++)
        {
            if (lpV42->struAlarmHandleType.dwRelAlarmOut[j] != 0xffffffff)
            {
                if (lpV42->struAlarmHandleType.dwRelAlarmOut[j] < MAX_ALARMOUT_V30)
                {
                    lpOld->struHandleType.byRelAlarmOut[lpV42->struAlarmHandleType.dwRelAlarmOut[j] -1] = 1;
                }
            }
            else
            {
                break;
            }
        }

         
        for (j = 0; j< MAX_CHANNUM_V30 && lpV42->dwRelRecordChan ; j++)
        {
            if (lpV42->dwRelRecordChan[j] != 0xffffffff)
            {
                if (lpV42->dwRelRecordChan[j] < MAX_ALARMOUT_V30)
                {
                    lpOld->byRelRecordChan[lpV42->dwRelRecordChan[j] -1] = 1;
                }
            }
            else
            {
                break;
            }
        }
        
        memcpy(&lpOld->struFilterStrategy, &lpV42->struFilterStrategy, sizeof(NET_VCA_FILTER_STRATEGY));
        memcpy(&lpOld->struTriggerParam, &lpV42->struTriggerParam, sizeof(NET_VCA_RULE_TRIGGER_PARAM));
    }
}

void CDlgVcaPositionRule::OnClickTreeChannelVca(NMHDR* pNMHDR, LRESULT* pResult) 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    CPoint pt(0,0);
    CRect rc(0,0,0,0);
    GetCursorPos(&pt);
    GetDlgItem(IDC_TREE_CHANNEL_VCA)->GetWindowRect(&rc);
    ScreenToClient(&rc);
    ScreenToClient(&pt);
    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;
    
    UINT uFlag = 0;
    HTREEITEM hSelect = m_treeChannel.HitTest(pt, &uFlag);
    
    if (NULL == hSelect) 
    {
        return;
    }
    m_treeChannel.SelectItem(hSelect);
    DWORD dwIndex = m_treeChannel.GetItemData(hSelect)%1000;
    BOOL bCheck = m_treeChannel.GetCheck(hSelect);
    m_pbChannel[dwIndex - 1] = !bCheck;
    //
    if (uFlag != LVHT_TOLEFT)
    {
        m_treeChannel.SetCheck(hSelect, !bCheck);
    }
    else
    {
        m_treeChannel.SetCheck(hSelect, bCheck);
    }
    
    *pResult = 0;
}

void CDlgVcaPositionRule::OnClickTreeAlarmout(NMHDR* pNMHDR, LRESULT* pResult) 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    CPoint pt(0,0);
    CRect rc(0,0,0,0);
    GetCursorPos(&pt);
    GetDlgItem(IDC_TREE_ALARMOUT)->GetWindowRect(&rc);
    ScreenToClient(&rc);
    ScreenToClient(&pt);
    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;
    
    UINT uFlag = 0;
    HTREEITEM hSelect = m_treeAlarmout.HitTest(pt, &uFlag);
    
    if (NULL == hSelect) 
    {
        return;
    }
    m_treeAlarmout.SelectItem(hSelect);
    DWORD dwIndex = m_treeAlarmout.GetItemData(hSelect)%1000;
    BOOL bCheck = m_treeAlarmout.GetCheck(hSelect);
    m_pbAlarmOut[dwIndex] = !bCheck;
    //switch checkbox status on click
    if (uFlag != LVHT_TOLEFT)
    {
        m_treeAlarmout.SetCheck(hSelect, !bCheck);
    }
    else
    {
        m_treeAlarmout.SetCheck(hSelect, bCheck);
    }
    
    *pResult = 0;
}


void CDlgVcaPositionRule::OnBtnSetPtz() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_struPtzPosition.struPtzPos.wAction = 1;
    m_iVcaChannel = m_cmbVCARuleChannel.GetItemData(m_cmbVCARuleChannel.GetCurSel());
    if(!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_PTZPOS, m_iVcaChannel, &m_struPtzPosition.struPtzPos, sizeof(m_struPtzPosition.struPtzPos)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_PTZPOS");
        MessageBox("设置PTZ坐标失败");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_PTZPOS");
    }
}

void CDlgVcaPositionRule::OnBtnPtzLockcfg() 
{
	// TODO: Add your control notification handler code here
	CDlgPtzLockCfg dlg;
    dlg.m_lUserID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel = m_cmbVCARuleChannel.GetItemData(m_cmbVCARuleChannel.GetCurSel());
    dlg.DoModal();
}


void CDlgVcaPositionRule::OnCbnSelchangeComboPositionChannel()
{
    // TODO:  在此添加控件通知处理程序代码
    NET_DVR_CLIENTINFO struPlay;
    GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWndRect);
    struPlay.hPlayWnd = GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
    struPlay.lChannel = m_cmbVCARuleChannel.GetItemData(m_cmbVCARuleChannel.GetCurSel());
    struPlay.lLinkMode = 0;
    struPlay.sMultiCastIP = "";
    EnableVcaWindow(true);

    if (m_lPlayHandle >= 0)
    {
        NET_DVR_StopRealPlay(m_lPlayHandle);
        m_lPlayHandle = -1;
    }
    else
    {

    }

    m_lPlayHandle = NET_DVR_RealPlay_V30(m_lServerID, &struPlay, NULL, NULL, TRUE);
    BOOL bRet = FALSE;
    if (m_lPlayHandle < 0)
    {
        g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_RealPlay_V30");
        MessageBox("NET_DVR_RealPlay_V30 FAIL");
    }
    else
    {
        bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawPositionAlertShow, 0);//DC Draw callback
    }
}
