/**********************************************************
FileName:    DlgVcaIvmsCfg.cpp
Description: IVMS config and relate dialog   
Date:        2009/07/10
Note: 		    
    <version> <time>         <desc>
    <1.0    > <2009/07/10>       <created>
***********************************************************/
// DlgVcaIvmsCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaIvmsCfg.h"
#include "DlgVcaIvmsSched.h"
#include "DlgVcaMaskRegion.h"
#include "DlgVcaEnterRegion.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgVcaIvmsCfg *g_pDlgVcaIvmsCfg;
#define  AlarmLine 1
#define  AlarmArea 2
/////////////////////////////////////////////////////////////////////////////
// CDlgVcaIvmsCfg dialog
/*********************************************************
  Function:	DrawIVMSAlertShow
  Desc:		Callback for Draw
  Input:	LONG lRealHandle
			HDC hDc
			DWORD dwUser
  Output:	
  Return:	void
**********************************************************/
void CALLBACK DrawIVMSAlertShow(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
	SetBkMode(hDc, TRANSPARENT);
	SetTextColor(hDc, RGB(255, 255, 255));
	if(g_pDlgVcaIvmsCfg->m_bRuleActive)
	{
		g_pDlgVcaIvmsCfg->F_DrawFun(lRealHandle, hDc, dwUser); 
	}
}

/*********************************************************
  Function:	CDlgVcaIvmsCfg
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgVcaIvmsCfg::CDlgVcaIvmsCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaIvmsCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaIvmsCfg)
	m_bDspAddRule = FALSE;
	m_bDspAddTarget = FALSE;
	m_bFilterActive = FALSE;
	m_bPicAddRule = FALSE;
	m_bPicAddTarget = FALSE;
	m_bSetMaxFilter = FALSE;
	m_bSetMiniFilter = FALSE;
	m_bVcaActive = FALSE;
	m_bDrawLine = FALSE;
	m_bDrawPolygon = FALSE;
	m_bPicPro = FALSE;
	m_bRuleActive = FALSE;
	m_iAlarmDelay = 0;
	m_iAlarmPersist = 0;
	m_iBAdvanceChanNum = 0;
	m_iBBaseChanNum = 0;
	m_iBFullChanNum = 0;
	m_fDenstityRate = 0.0f;
	m_fMaxDistance = 0.0f;
	m_iPlateChanNum = 0;
	m_iReadCardTimePersist = 0;
	m_csRuleName = _T("");
	m_iVcaChanNum = 0;
	m_iAtmChanNum = 0;
	m_csDevIP = _T("");
	m_csTimePeriod = _T("");
	m_bPicWithVca = FALSE;
	//}}AFX_DATA_INIT
	m_lServerID = -1;
	m_iStartChannel = -1;
	m_iDevIndex = -1;
	m_iChannelnumber = -1;
	m_dwAlarmOutNum = 0;
	m_iVcaChannel = -1;
	
	memset(&m_struVcaCtrlCfg, 0, sizeof(NET_VCA_CTRLCFG));
	memset(&m_struBehaviorAbility, 0, sizeof(NET_VCA_BEHAVIOR_ABILITY));
	memset(&m_struIvmsRuleCfg, 0, sizeof(NET_IVMS_RULECFG));
	memset(&m_struVCADrawMode, 0 ,sizeof(NET_VCA_DRAW_MODE));
	
	memset(&m_struIVMSStreamCfg, 0, sizeof(NET_IVMS_STREAMCFG));
	memset(&m_struIvmsBehaviorCfg, 0, sizeof(NET_IVMS_BEHAVIORCFG));
	memset(&m_struVcaPolygon[0], 0, sizeof(NET_VCA_POLYGON)*MAX_RULE_NUM);
	memset(&m_struVcaLine[0], 0, sizeof(NET_VCA_LINE)*MAX_RULE_NUM);
	memset(&m_bCloseIn[0], 0, sizeof(BOOL)*MAX_RULE_NUM);
	memset(&m_bNeedRedraw[0], 0, sizeof(BOOL)*MAX_RULE_NUM);
	memset(&m_bMouseMove[0], 0, sizeof(BOOL)*MAX_RULE_NUM);
	memset(&m_struIVMSMaskList, 0, sizeof(NET_IVMS_MASK_REGION_LIST));
	memset(&m_struIVMSEnterRegion, 0, sizeof(NET_IVMS_ENTER_REGION));
	memset(&m_rcWndRect, 0, sizeof(CRect));
	m_iCurRuleID = -1;
	m_dwPosNum = 0;
	m_lPlayHandle = -1;
	m_iWeekday = 0;
	m_iTimePeriod = 0;
	m_lUserID = -1;
}

/*********************************************************
  Function:	DoDataExchange
  Desc:		the map between control and variable
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgVcaIvmsCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaIvmsCfg)
	DDX_Control(pDX, IDC_STATIC_ALARM_PERSIST_STICK_UP_AREA, m_staticAlarmPersistStickUpArea);
	DDX_Control(pDX, IDC_COMBO_WEEKDAY_COPY, m_comboWeekdayCopy);
	DDX_Control(pDX, IDC_COMBO_ATM_MODE, m_comboAtmMode);
	DDX_Control(pDX, IDC_EDIT_READ_CARD_TIME_PERSIST, m_editReadCardTimePersist);
	DDX_Control(pDX, IDC_EDIT_MAX_DISTANCE, m_editMaxDistance);
	DDX_Control(pDX, IDC_EDIT_DENSTITY_RATE, m_editDenstityRate);
	DDX_Control(pDX, IDC_EDIT_ALARM_PERSIST, m_editAlarmPersist);
	DDX_Control(pDX, IDC_EDIT_ALARM_DELAY, m_editAlarmDelay);
	DDX_Control(pDX, IDC_COMBO_TIME_PERIOD, m_comboTimePeriod);
	DDX_Control(pDX, IDC_COMBO_WEEKDAY, m_comboWeekday);
	DDX_Control(pDX, IDC_COMBO_LINE_ALARM_DIRECT, m_comboAlarmDirect);
	DDX_Control(pDX, IDC_STATIC_READ_CARD_TIME_PERSIST_AREA, m_staticReadCardTimePersistArea);
	DDX_Control(pDX, IDC_STATIC_READ_CARD_TIME_PERSIST, m_staticReadCardTimePersist);
	DDX_Control(pDX, IDC_STATIC_MAX_DISTANCE_AREA, m_staticMaxDistanceArea);
	DDX_Control(pDX, IDC_STATIC_MAX_DISTANCE, m_staticMaxDistance);
	DDX_Control(pDX, IDC_STATIC_DENSTITY_RATE_AREA, m_staticDenstityRateArea);
	DDX_Control(pDX, IDC_STATIC_DENSTITY_RATE, m_staticDenstityRate);
	DDX_Control(pDX, IDC_STATIC_ALARM_PERSIST_AREA, m_staticAlarmPersistArea);
	DDX_Control(pDX, IDC_STATIC_ALARM_PERSIST, m_staticAlarmPersist);
	DDX_Control(pDX, IDC_STATIC_ALARM_DIRECT, m_staticAlarmDirect);
	DDX_Control(pDX, IDC_STATIC_ALARM_DELAY_AREA, m_staticAlarmDelayArea);
	DDX_Control(pDX, IDC_STATIC_ALARM_DELAY, m_staticAlarmDelay);
	DDX_Control(pDX, IDC_COMBO_VCA_TYPE, m_comboVcaType);
	DDX_Control(pDX, IDC_COMBO_VCA_CHAN, m_comboVcaChan);
	DDX_Control(pDX, IDC_COMBO_STREAM, m_comboStream);
	DDX_Control(pDX, IDC_COMBO_SENSITIVE, m_comboSensitive);
	DDX_Control(pDX, IDC_COMBO_RULE_TYPE, m_comboRuleType);
	DDX_Control(pDX, IDC_COMBO_RULE_ID, m_comboRuleId);
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_comboResolution);
	DDX_Control(pDX, IDC_COMBO_PIC_QUALITY, m_comboPicQuality);
	DDX_Check(pDX, IDC_CHECK_DSP_ADD_RULE, m_bDspAddRule);
	DDX_Check(pDX, IDC_CHECK_DSP_ADD_TARGET, m_bDspAddTarget);
	DDX_Check(pDX, IDC_CHECK_FILTER_ACTIVE, m_bFilterActive);
	DDX_Check(pDX, IDC_CHECK_PIC_ADD_RULE, m_bPicAddRule);
	DDX_Check(pDX, IDC_CHECK_PIC_ADD_TARGET, m_bPicAddTarget);
	DDX_Check(pDX, IDC_CHECK_SET_MAX_FILTER, m_bSetMaxFilter);
	DDX_Check(pDX, IDC_CHECK_SET_MINI_FILTER, m_bSetMiniFilter);
	DDX_Check(pDX, IDC_CHECK_VCA_ACTIVE, m_bVcaActive);
	DDX_Check(pDX, IDC_CHK_DRAW_LINE, m_bDrawLine);
	DDX_Check(pDX, IDC_CHK_DRAW_POLYGON, m_bDrawPolygon);
	DDX_Check(pDX, IDC_CHK_PIC_PRO, m_bPicPro);
	DDX_Check(pDX, IDC_CHK_RULE_ACTIVE, m_bRuleActive);
	DDX_Text(pDX, IDC_EDIT_ALARM_DELAY, m_iAlarmDelay);
	DDX_Text(pDX, IDC_EDIT_ALARM_PERSIST, m_iAlarmPersist);
	DDX_Text(pDX, IDC_EDIT_BADVANCE_CHAN_NUM, m_iBAdvanceChanNum);
	DDX_Text(pDX, IDC_EDIT_BBASE_CHAN_NUM, m_iBBaseChanNum);
	DDX_Text(pDX, IDC_EDIT_BFULL_CHAN_NUM, m_iBFullChanNum);
	DDX_Text(pDX, IDC_EDIT_DENSTITY_RATE, m_fDenstityRate);
	DDX_Text(pDX, IDC_EDIT_MAX_DISTANCE, m_fMaxDistance);
	DDX_Text(pDX, IDC_EDIT_PLATE_CHAN_NUM, m_iPlateChanNum);
	DDX_Text(pDX, IDC_EDIT_READ_CARD_TIME_PERSIST, m_iReadCardTimePersist);
	DDX_Text(pDX, IDC_EDIT_RULE_NAME, m_csRuleName);
	DDX_Text(pDX, IDC_EDIT_VCA_CHAN_NUM, m_iVcaChanNum);
	DDX_Text(pDX, IDC_EDIT_ATM_CHAN_NUM, m_iAtmChanNum);
	DDX_Text(pDX, IDC_STATIC_DEV_IP, m_csDevIP);
	DDX_Text(pDX, IDC_STATIC_TIME_PERIOD, m_csTimePeriod);
	DDX_Check(pDX, IDC_CHK_PICWITHVCA, m_bPicWithVca);
	//}}AFX_DATA_MAP
}

/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgVcaIvmsCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaIvmsCfg)
	ON_WM_DESTROY()
	ON_BN_CLICKED(ID_BTN_SET_VCA_CTRL, OnBtnSetVcaCtrl)
	ON_BN_CLICKED(IDC_BTN_VCA_RESTART, OnBtnVcaRestart)
	ON_BN_CLICKED(IDC_BTN_SET_VCA_DRAW_MODE, OnBtnSetVcaDrawMode)
	ON_BN_CLICKED(IDC_BTN_IVMS_SCHED, OnBtnIvmsSched)
	ON_BN_CLICKED(ID_BTN_SET_IVMS_CFG, OnBtnSetIvmsCfg)
	ON_BN_CLICKED(IDC_CHK_DRAW_LINE, OnChkDrawLine)
	ON_BN_CLICKED(IDC_CHK_DRAW_POLYGON, OnChkDrawPolygon)
	ON_BN_CLICKED(IDC_CHK_PIC_PRO, OnChkPicPro)
	ON_BN_CLICKED(IDC_CHK_RULE_ACTIVE, OnChkRuleActive)
	ON_BN_CLICKED(IDC_CHECK_VCA_ACTIVE, OnCheckVcaActive)
	ON_BN_CLICKED(IDC_CHECK_FILTER_ACTIVE, OnCheckFilterActive)
	ON_BN_CLICKED(IDC_CHECK_SET_MINI_FILTER, OnCheckSetMiniFilter)
	ON_BN_CLICKED(IDC_CHECK_SET_MAX_FILTER, OnCheckSetMaxFilter)
	ON_CBN_SELCHANGE(IDC_COMBO_VCA_CHAN, OnSelchangeComboVcaChan)
	ON_CBN_SELCHANGE(IDC_COMBO_WEEKDAY, OnSelchangeComboWeekday)
	ON_CBN_SELCHANGE(IDC_COMBO_TIME_PERIOD, OnSelchangeComboTimePeriod)
	ON_CBN_SELCHANGE(IDC_COMBO_LINE_ALARM_DIRECT, OnSelchangeComboLineAlarmDirect)
	ON_CBN_SELCHANGE(IDC_COMBO_RULE_TYPE, OnSelchangeComboRuleType)
	ON_CBN_SELCHANGE(IDC_COMBO_RULE_ID, OnSelchangeComboRuleId)
	ON_BN_CLICKED(IDC_BTN_RULE_OK, OnBtnRuleOk)
	ON_CBN_SELCHANGE(IDC_COMBO_PIC_QUALITY, OnSelchangeComboPicQuality)
	ON_CBN_SELCHANGE(IDC_COMBO_RESOLUTION, OnSelchangeComboResolution)
	ON_BN_CLICKED(IDC_BTN_PIC_OK, OnBtnPicOk)
	ON_CBN_SELCHANGE(IDC_COMBO_VCA_TYPE, OnSelchangeComboVcaType)
	ON_BN_CLICKED(IDC_BTN_MASK_REGION, OnBtnMaskRegion)
	ON_BN_CLICKED(IDC_BTN_ENTER_REGION, OnBtnEnterRegion)
	ON_BN_CLICKED(ID_BTN_COPY_DAY, OnBtnCopyDay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaIvmsCfg message handlers
/*********************************************************
  Function:	PreTranslateMessage
  Desc:		the get the enter and escape key message
  Input:	pMsg, the message of key
  Output:	none
  Return:	TRUE, means successful; FALSE, means failed;
**********************************************************/
BOOL CDlgVcaIvmsCfg::PreTranslateMessage(MSG* pMsg) 
{
		CPoint pt(0,0);
	CRect  rcWnd(0,0,0,0);
	GetDlgItem(IDC_PLAYWND)->GetWindowRect(&rcWnd);
	GetCursorPos(&pt);
	CString strTemp = _T("");
	int i=0;
	BOOL bOneLine = TRUE,bXOneLine = TRUE,bYOneLine = TRUE;

	switch(pMsg->message) 
	{
	case WM_LBUTTONDOWN:
		if( (m_bDrawLine || m_bDrawPolygon)&&
			(GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
		{
			if (m_bDrawPolygon)
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
							g_StringLanType(szLan,"多边形顶点不能超过10个!","Polygon vertex can not be over 10!");
							AfxMessageBox(szLan);
							return TRUE;
						}
						if((float)(pt.x-rcWnd.left)/(float)rcWnd.Width() <= m_struVcaPolygon[m_iCurRuleID].struPos[m_dwPosNum-1].fX+0.01 && (float)(pt.x-rcWnd.left)/(float)rcWnd.Width() >= m_struVcaPolygon[m_iCurRuleID].struPos[m_dwPosNum-1].fX-0.01\
							&& (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() <= m_struVcaPolygon[m_iCurRuleID].struPos[m_dwPosNum-1].fY+0.01 && (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() >= m_struVcaPolygon[m_iCurRuleID].struPos[m_dwPosNum-1].fY-0.01)
						{
							char szLan[128] = {0};
							g_StringLanType(szLan, "不能连续在同一点上画区域", "Region can not be painted in the same point");
							AfxMessageBox(szLan);
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
							g_StringLanType(szLan, "不能连续在同一点上画区域", "Region can not be painted in the same point");
							AfxMessageBox(szLan);
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
			
		}//Draw the first coordinate of minimum rectangle
		else if(m_bSetMiniFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
		{
			if(PtInRect(&rcWnd,pt))
			{
			m_struIvmsRuleCfg.struRule[m_iCurRuleID].struSizeFilter.struMiniRect.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
			m_struIvmsRuleCfg.struRule[m_iCurRuleID].struSizeFilter.struMiniRect.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
			}
			
		}//Draw the first coordinate of maximum rectangle
		else if(m_bSetMaxFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
		{
			if(PtInRect(&rcWnd,pt))
			{
			m_struIvmsRuleCfg.struRule[m_iCurRuleID].struSizeFilter.struMaxRect.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
			m_struIvmsRuleCfg.struRule[m_iCurRuleID].struSizeFilter.struMaxRect.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
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
		else if(m_bSetMiniFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
		{
			if(PtInRect(&rcWnd,pt))
			{
			m_struIvmsRuleCfg.struRule[m_iCurRuleID].struSizeFilter.struMiniRect.fWidth = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width() - m_struIvmsRuleCfg.struRule[m_iCurRuleID].struSizeFilter.struMiniRect.fX;
			m_struIvmsRuleCfg.struRule[m_iCurRuleID].struSizeFilter.struMiniRect.fHeight = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() - m_struIvmsRuleCfg.struRule[m_iCurRuleID].struSizeFilter.struMiniRect.fY;
			}
		}
		else if(m_bSetMaxFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
		{
			if(PtInRect(&rcWnd,pt))
			{
			m_struIvmsRuleCfg.struRule[m_iCurRuleID].struSizeFilter.struMaxRect.fWidth = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width() - m_struIvmsRuleCfg.struRule[m_iCurRuleID].struSizeFilter.struMaxRect.fX;
			m_struIvmsRuleCfg.struRule[m_iCurRuleID].struSizeFilter.struMaxRect.fHeight = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() - m_struIvmsRuleCfg.struRule[m_iCurRuleID].struSizeFilter.struMaxRect.fY;
		}
		}
		break;
	case WM_RBUTTONDOWN://right click to close the rectangle 
		if(m_bDrawPolygon && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
		{
			if(PtInRect(&rcWnd,pt))
			{
				if(m_dwPosNum > 9)
				{
					return TRUE;
				}
				for(i = 0; i < (int)m_dwPosNum; i++)
				{
					if(m_struVcaPolygon[m_iCurRuleID].struPos[i].fX != m_struVcaPolygon[m_iCurRuleID].struPos[i+1].fX)
					{
						bXOneLine = FALSE;
						break;
					}
				}
				for(i=0; i < (int)m_dwPosNum; i++)
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
					g_StringLanType(szlan, "所画点成一线，无法构成区域!","Can not constitute a regional");
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
  Desc:		Initialize Dialog
  Input:	
  Output:	
  Return:	BOOL
**********************************************************/
BOOL CDlgVcaIvmsCfg::OnInitDialog() 
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

	g_pDlgVcaIvmsCfg = this;
	
	m_iVcaChannel = m_iStartChannel;
	m_dwAlarmOutNum = g_struDeviceInfo[m_iDevIndex].iAlarmOutNum;
	m_iCurRuleID = 0;
	
	if(!GetVcaDrawMode())
	{
		return FALSE;
	}

	GetDevVcaChanPara();//Get device channel info

	m_comboVcaChan.SetCurSel(0);
	UpdateData(FALSE);
	OnSelchangeComboVcaChan(); 
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
	
/*********************************************************
  Function:	GetMaskRegion
  Desc:		Get mask region parameters
  Input:	
  Output:	
  Return:	BOOL
**********************************************************/
BOOL CDlgVcaIvmsCfg::GetMaskRegion()
{
	DWORD dwReturned = 0;
	if(!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_IVMS_MASK_REGION, m_iVcaChannel, &m_struIVMSMaskList, sizeof(NET_IVMS_MASK_REGION_LIST), &dwReturned))	
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_IVMS_MASK_REGION %d", m_iVcaChannel);
		char szLan[128] = {0};
		g_StringLanType(szLan,"获取IVMS屏蔽参数失败", "Fail to get ivms mask region");
		AfxMessageBox(szLan);
		//OnCancel();
		return FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_IVMS_MASK_REGION %d", m_iVcaChannel);
	}
	return TRUE;
	
}
	
/*********************************************************
  Function:	GetEnterRegion
  Desc:		Get config of enter region
  Input:	
  Output:	
  Return:	BOOL
**********************************************************/
BOOL CDlgVcaIvmsCfg::GetEnterRegion()
{
	DWORD dwReturned = 0 ;
	if(!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_IVMS_ENTER_REGION, m_iVcaChannel, &m_struIVMSEnterRegion, sizeof(NET_IVMS_ENTER_REGION), &dwReturned))	
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_IVMS_ENTER_REGION %d", m_iVcaChannel);
		char szLan[128] = {0};
		g_StringLanType(szLan, "获取IVMS进入区域参数失败", "Fail to get IVMS enter region");
		AfxMessageBox(szLan);
		//OnCancel();
		return FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_IVMS_ENTER_REGION %d", m_iVcaChannel);
}
	return TRUE;	
}

/*********************************************************
  Function:	RefreshVcaCtrl
  Desc:		refresh control
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::RefreshVcaCtrl()
{

	NET_VCA_CHAN_IN_PARAM struVcaChanInparam;
	memset(&struVcaChanInparam, 0 ,sizeof(NET_VCA_CHAN_IN_PARAM));
	struVcaChanInparam.byVCAType = g_pMainDlg->m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byVCAType;
	struVcaChanInparam.byMode = g_pMainDlg->m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byMode;
	if (!GetIVMSChanAbility(m_iVcaChannel, struVcaChanInparam))//get channel ability
	{
	}


	if (!GetIvmsStreamPara()) //get IVMS parameter
	{
		
	}
	
	if (!GetIvmsBehaviorCfg())
	{
	}
	
	//config upload alarm image info
	m_bPicPro = m_struIvmsBehaviorCfg.byPicProType; //get actions for alarm
	m_comboResolution.SetCurSel(m_struIvmsBehaviorCfg.struPicParam.wPicSize);//image resolution, 4cif etc.
	m_comboPicQuality.SetCurSel(m_struIvmsBehaviorCfg.struPicParam.wPicQuality);//image quality, 0 best, 1 better 2 normal

	//get config info
	m_iWeekday = 0;
	m_iTimePeriod = 0;
	m_comboWeekday.SetCurSel(m_iWeekday);
	m_comboTimePeriod.SetCurSel(m_iTimePeriod);
	UpdateData(FALSE);
	OnSelchangeComboWeekday();
}

/*********************************************************
  Function:	OnDestroy
  Desc:		destroy dialog and its corresponding resource while exit
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgVcaIvmsCfg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}


/*********************************************************
  Function:	OnBtnSetVcaCtrl
  Desc:		Set intelligent control
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::OnBtnSetVcaCtrl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byVCAEnable = (unsigned char)m_bVcaActive;
	m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byVCAType = (unsigned char)m_comboVcaType.GetItemData(m_comboVcaType.GetCurSel());
	if (m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byVCAType == VCA_ATM)
	{
		if (m_comboAtmMode.GetCurSel() ==CB_ERR)
		{
			TRACE("ATM MODE ERROR");
		}
		m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byMode = (unsigned char)m_comboAtmMode.GetCurSel();
	}
	m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byStreamWithVCA = (unsigned char)m_comboStream.GetCurSel();
	m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byPicWithVCA = m_bPicWithVca;
	
	if(!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_VCA_CTRLCFG, m_iVcaChannel , &m_struVcaCtrlCfg, sizeof(NET_VCA_CTRLCFG)))
	{	
		char szLan[128] = {0};
		char sBufEn[128] = {0};
		char sBufCn[128] = {0};
		sprintf(sBufCn, "设置智能通道%d失败", m_iVcaChannel);
		sprintf(sBufEn, "fail to set VCA channel[%d]", m_iVcaChannel);
		g_StringLanType(szLan, sBufCn, sBufEn);
		AfxMessageBox(szLan);
		memcpy(&m_struVcaCtrlCfg, &g_pMainDlg->m_struVcaCtrlCfg,sizeof(NET_VCA_CTRLCFG));
		
//		UpdateData(TRUE);
		SetComboVcaType(m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byVCAType);
				m_bVcaActive = m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byVCAEnable;
		m_comboStream.SetCurSel(m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byStreamWithVCA);
		UpdateData(FALSE);
		
	}
	else
	{
		memcpy(&g_pMainDlg->m_struVcaCtrlCfg, &m_struVcaCtrlCfg,sizeof(NET_VCA_CTRLCFG));//copy as a global member
		
		if(m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel -1].byVCAType == VCA_ATM)
		{
			if (m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel -1].byMode == 0)
			{
				GetDlgItem(IDC_BTN_ENTER_REGION)->ShowWindow(SW_SHOW);	
				GetEnterRegion();
			}
			else
			{
				GetDlgItem(IDC_BTN_ENTER_REGION)->ShowWindow(SW_HIDE);
			}

			GetDlgItem(IDC_BTN_MASK_REGION)->ShowWindow(SW_SHOW);
			GetMaskRegion();
		}
		else
		{
			GetDlgItem(IDC_BTN_ENTER_REGION)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_MASK_REGION)->ShowWindow(SW_HIDE);
		}
		
		char szLan[128] = {0};
		char sBufEn[128] = {0};
		char sBufCn[128] = {0};
		sprintf(sBufCn, "设置智能通道%d成功", m_iVcaChannel);
		sprintf(sBufEn, "Success to set VCA channel[%d]", m_iVcaChannel);
		g_StringLanType(szLan, sBufCn, sBufEn);
		AfxMessageBox(szLan);
		
		RefreshVcaCtrl();
	}
}

/*********************************************************
  Function:	OnBtnVcaRestart
  Desc:		function for reboot intelligent library  
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::OnBtnVcaRestart() 
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
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_VCA_RestartLib %d", m_iVcaChannel);
	}
	
}

/*********************************************************
  Function:	OnBtnSetVcaDrawMode
  Desc:		function for olver target
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::OnBtnSetVcaDrawMode() 
{
	// TODO: Add your control notification handler code here
		SetVcaDrawMode();
}

/*********************************************************
  Function:	OnBtnIvmsSched
  Desc:		function for getting stream schedule 
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::OnBtnIvmsSched() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaIvmsSched dlg;
	dlg.DoModal();

	char chTimePeriod[128] = {0};

	int nIndex = m_comboTimePeriod.GetCurSel()+1;
	sprintf(chTimePeriod, "Time%d: %dH%dM--%dH%dM", nIndex,
		m_struIVMSStreamCfg.struDevSched[m_iWeekday][m_iTimePeriod].struTime.byStartHour,
		m_struIVMSStreamCfg.struDevSched[m_iWeekday][m_iTimePeriod].struTime.byStartMin,
		m_struIVMSStreamCfg.struDevSched[m_iWeekday][m_iTimePeriod].struTime.byStopHour,
		m_struIVMSStreamCfg.struDevSched[m_iWeekday][m_iTimePeriod].struTime.byStopMin);
	m_csTimePeriod = chTimePeriod;	
	
// 	if(m_struIVMSStreamCfg.struDevSched[m_iWeekday][m_iTimePeriod].struPUStream.struStreamMediaSvrCfg.dwValid == TRUE)
// 	{
// 		m_csDevIP = "取流IP: ";
// 		m_csDevIP = m_struIVMSStreamCfg.struDevSched[m_iWeekday][m_iTimePeriod].struPUStream.struStreamMediaSvrCfg.struDevIP.sIpV4;
// 	}
// 	else
	{
		m_csDevIP = "Device IP: ";
		m_csDevIP += m_struIVMSStreamCfg.struDevSched[m_iWeekday][m_iTimePeriod].struPUStream.struDevChanInfo.struIP.sIpV4;
	}
//
	OnSelchangeComboWeekday();
	UpdateData(FALSE);
	
}

/*********************************************************
  Function:	OnBtnSetIvmsCfg
  Desc:		IVMS config
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::OnBtnSetIvmsCfg() 
{
	// TODO: Add your control notification handler code here
	BOOL bFlag = TRUE;
	if (m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byVCAType == VCA_ATM)
	{
		if (m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byMode == 0)
		{
			if (!SetEnterRegion())
			{
				bFlag = FALSE;
		}
	}
		if (!SetMaskRegion())
		{
			bFlag = FALSE;
		}		
	}
	if (!SetIvmsStreamCfg())
	{
		bFlag = FALSE;
	}
	if (!SetIvmsBehaviorCfg())
	{
		bFlag = FALSE;
	}
	if (bFlag == TRUE)
	{
		AfxMessageBox("Success to set IDS");
	}
}

/*********************************************************
  Function:	SetMaskRegion
  Desc:		set maks region
  Input:	
  Output:	
  Return:	void
**********************************************************/
BOOL CDlgVcaIvmsCfg::SetMaskRegion()
{
	BOOL bFlag = FALSE;
	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_IVMS_MASK_REGION, m_iVcaChannel, &m_struIVMSMaskList, sizeof(NET_IVMS_MASK_REGION_LIST)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_IVMS_MASK_REGION %d", m_iVcaChannel);
		AfxMessageBox("fail to set mask region");
		bFlag = FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_IVMS_MASK_REGION %d", m_iVcaChannel);
		bFlag = TRUE;
	}	
	return bFlag;
}

/*********************************************************
  Function:	SetEnterRegion
  Desc:		set enter area
  Input:	
  Output:	
  Return:	void
**********************************************************/
BOOL CDlgVcaIvmsCfg::SetEnterRegion()
{
	BOOL bFlag = FALSE;
	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_IVMS_ENTER_REGION, m_iVcaChannel, &m_struIVMSEnterRegion, sizeof(NET_IVMS_ENTER_REGION)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_IVMS_ENTER_REGION %d", m_iVcaChannel);
		AfxMessageBox("fail to set enter region");
		bFlag = FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_IVMS_ENTER_REGION %d", m_iVcaChannel);
		bFlag = TRUE;
	}		
	return bFlag;
}

/*********************************************************
  Function:	SetIvmsStreamCfg
  Desc:		Set fetching stream of iVMS
  Input:	
  Output:	
  Return:	
**********************************************************/
BOOL CDlgVcaIvmsCfg::SetIvmsStreamCfg()
{
	BOOL bFlag = FALSE;
    
	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_IVMS_STREAMCFG, m_iVcaChannel, &m_struIVMSStreamCfg, sizeof(NET_IVMS_STREAMCFG)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_IVMS_STREAMCFG %d", m_iVcaChannel);
		AfxMessageBox("Fail to set IVMS para");
		bFlag = FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_IVMS_STREAMCFG %d", m_iVcaChannel);
		bFlag = TRUE;
	}
	return bFlag;
}

/*********************************************************
  Function:	SetIvmsBehaviorCfg
  Desc:		Set IVMS behavior analysis rule
  Input:	
  Output:	
  Return:	void
**********************************************************/
BOOL CDlgVcaIvmsCfg::SetIvmsBehaviorCfg()
{
	BOOL bFlag = FALSE;
	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_IVMS_BEHAVIORCFG, m_iVcaChannel, &m_struIvmsBehaviorCfg, sizeof(NET_IVMS_BEHAVIORCFG)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_IVMS_BEHAVIORCFG %d", m_iVcaChannel);
		AfxMessageBox("Fail to set IVMS behavior");
		bFlag = FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_IVMS_BEHAVIORCFG %d", m_iVcaChannel);
		bFlag = TRUE;
	}
	return bFlag;
}

/*********************************************************
  Function:	OnChkDrawLine
  Desc:		draw line
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::OnChkDrawLine() 
{
	UpdateData(TRUE);
	if(m_bDrawLine)//when setting
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
  Function:	OnChkDrawPolygon
  Desc:		Draw polygon
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::OnChkDrawPolygon() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_bDrawPolygon)
	{
		m_bNeedRedraw[m_iCurRuleID] = TRUE;//redraw the polygon
		m_bSetMaxFilter = FALSE;//while drawing polygon, can't draw filter rectangle
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
  Function:	OnChkPicPro
  Desc:		upload image to host
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::OnChkPicPro() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struIvmsBehaviorCfg.byPicProType = (unsigned char)m_bPicPro;
}

/*********************************************************
  Function:	OnChkRuleActive
  Desc:		varify rule 
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::OnChkRuleActive() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	EnableRuleWindow(m_bRuleActive);
	m_struIvmsRuleCfg.struRule[m_iCurRuleID].byActive = (unsigned char)m_bRuleActive;
// 	
// 	OnSelchangeComboRuleType();
// 	
	UpdateData(FALSE);	
}

/*********************************************************
  Function:	OnCheckVcaActive
  Desc:		enable intellignet function 
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::OnCheckVcaActive() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_comboVcaType.GetCurSel() == CB_ERR )
	{
		m_comboVcaType.EnableWindow(m_bVcaActive);
	}
	else
	{
	EnableVcaWindow(m_bVcaActive); 
	}
	EnableRuleWindow(m_bVcaActive&&m_bRuleActive); 
	UpdateData(FALSE);
}

/*********************************************************
Function:	SetVcaDrawMode
Desc:		set target overlay
Input:	
Output:	
Return:	 void
**********************************************************/
void CDlgVcaIvmsCfg::SetVcaDrawMode()
{
	UpdateData(TRUE);
	m_struVCADrawMode.byDspAddRule = (unsigned char)m_bDspAddRule;
	m_struVCADrawMode.byDspAddTarget = (unsigned char)m_bDspAddTarget;
	m_struVCADrawMode.byDspPicAddRule = (unsigned char)m_bPicAddRule;
	m_struVCADrawMode.byDspPicAddTarget = (unsigned char)m_bPicAddTarget;
	char szLan[128] = {0};
	if (!NET_DVR_SetVCADrawMode(m_lServerID,  m_iVcaChannel, &m_struVCADrawMode))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_VCA_DRAW_MODE %d", m_iVcaChannel);
		char sbufCn[128] = {0};
		char sbufEn[128] = {0};
		sprintf(sbufCn,"设置通道%d目标叠加失败", m_iVcaChannel);
		sprintf(sbufEn, "Fail to set Channel%d: VCA draw mode");
		g_StringLanType(szLan, sbufCn, sbufEn);
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_VCA_DRAW_MODE %d", m_iVcaChannel);
		char sbufCn[128] = {0};
		char sbufEn[128] = {0};
		sprintf(sbufCn,"设置通道%d目标叠加成功", m_iVcaChannel);
		sprintf(sbufEn, "Success to set Channel%d: VCA draw mode");
		g_StringLanType(szLan, sbufCn, sbufEn);
		AfxMessageBox(szLan);
	}
}


/*********************************************************
Function:	EnableRuleWindow
Desc:	
Input:	
Output:	
Return:	 BOOL
**********************************************************/
BOOL CDlgVcaIvmsCfg::EnableRuleWindow(BOOL bEnable)
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

	GetDlgItem(IDC_EDIT_MAX_DISTANCE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_DENSTITY_RATE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_READ_CARD_TIME_PERSIST)->EnableWindow(bEnable);

	GetDlgItem(IDC_STATIC_ALARM_DIRECT)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_LINE_ALARM_DIRECT)->EnableWindow(bEnable);

	GetDlgItem(IDC_CHK_DRAW_LINE)->EnableWindow(bEnable);
 	
	GetDlgItem(IDC_CHECK_SET_MAX_FILTER)->EnableWindow(m_bFilterActive&m_bRuleActive);
	GetDlgItem(IDC_CHECK_SET_MINI_FILTER)->EnableWindow(m_bFilterActive&m_bRuleActive);
	return TRUE;
}

/*********************************************************
Function:	GetEventType
Desc:	
Input:	int num
Output:	
Return:	VCA_EVENT_TYPE
**********************************************************/
VCA_EVENT_TYPE CDlgVcaIvmsCfg::GetEventType(int num)
{
	return (VCA_EVENT_TYPE)m_comboRuleType.GetItemData(num);
}

/*********************************************************
Function:	F_DrawFun
Desc:	 draw
Input:	long lPlayHandle
		HDC hDc
		DWORD dwUser
Output:	
Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser)
{
	COLORREF color;
	color = RGB(255, 255, 0);//yellow
	if(	m_struIvmsRuleCfg.struRule[m_iCurRuleID].dwEventType == VCA_ENTER_AREA
		|| m_struIvmsRuleCfg.struRule[m_iCurRuleID].dwEventType == VCA_EXIT_AREA
		|| m_struIvmsRuleCfg.struRule[m_iCurRuleID].dwEventType == VCA_INTRUSION
		|| m_struIvmsRuleCfg.struRule[m_iCurRuleID].dwEventType == VCA_LOITER
		|| m_struIvmsRuleCfg.struRule[m_iCurRuleID].dwEventType == VCA_LEFT_TAKE
		|| m_struIvmsRuleCfg.struRule[m_iCurRuleID].dwEventType == VCA_PARKING
		|| m_struIvmsRuleCfg.struRule[m_iCurRuleID].dwEventType == VCA_RUN
		|| m_struIvmsRuleCfg.struRule[m_iCurRuleID].dwEventType == VCA_HIGH_DENSITY
		|| m_struIvmsRuleCfg.struRule[m_iCurRuleID].dwEventType == VCA_STICK_UP
		|| m_struIvmsRuleCfg.struRule[m_iCurRuleID].dwEventType == VCA_INSTALL_SCANNER
		)
	{
		F_DrawFrame(lPlayHandle, hDc, dwUser, m_iCurRuleID, color);
	}
	else if (m_struIvmsRuleCfg.struRule[m_iCurRuleID].dwEventType == VCA_TRAVERSE_PLANE)
	{
		F_DrawLine(lPlayHandle, hDc, dwUser, m_iCurRuleID, color);
	}
	else
	{
		TRACE("INVALID EVENT TYPE");
	}
	F_DrawFilter(lPlayHandle, hDc, dwUser, m_iCurRuleID, RGB(0, 255, 125));
}


/*********************************************************
Function:	F_DrawFrame
Desc:	draw polygon
Input:	long lRealHandle
		HDC hDc
		DWORD dwUser
		DWORD dwRuleID current rule ID
		COLORREF color 
Output:	
Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::F_DrawFrame(long lRealHandle, HDC hDc, DWORD dwUser, DWORD dwRuleID, COLORREF color)
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
		//if the new line is crossed with existing line, redraw. 
		if(i>=MIN_PNT_NUM && !m_bMouseMove[m_iCurRuleID] && IsCrossLine(&m_struVcaPolygon[dwRuleID]))
		{
			char szLan[128] = {0};
			g_StringLanType(szLan,"多边形不相邻的边有相交情况存在,请重新输入!","Polygon edges are not adjacent is intersect");
			AfxMessageBox(szLan);
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
	//close the polygon automatically if the 10th points is drawn. 
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
		//check if it's a valid region
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
Desc:	drwa size filter
Input:	long lRealHandle
		HDC hDc
		DWORD dwUser
		DWORD dwRuleID
		COLORREF color
Output:	
Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::F_DrawFilter(long lRealHandle, HDC hDc, DWORD dwUser, DWORD dwRuleID, COLORREF color)
{
//	if (m_bSetMiniFilter || m_bSetMaxFilter)
	if (m_bFilterActive)
	{
		CPen DrawPen;
		
		DrawPen.CreatePen(PS_SOLID, 1, color);
		CBrush brTmp;
		brTmp.CreateSolidBrush(color);
		
		HGDIOBJ pOldPen = SelectObject(hDc, DrawPen);
		CRect rectMini, rectMax;
		rectMini.left = (int)(m_struIvmsRuleCfg.struRule[dwRuleID].struSizeFilter.struMiniRect.fX*m_rcWndRect.Width());
		rectMini.top = (int)(m_struIvmsRuleCfg.struRule[dwRuleID].struSizeFilter.struMiniRect.fY*m_rcWndRect.Height());
		rectMini.right = (int)((m_struIvmsRuleCfg.struRule[dwRuleID].struSizeFilter.struMiniRect.fX+m_struIvmsRuleCfg.struRule[dwRuleID].struSizeFilter.struMiniRect.fWidth)*m_rcWndRect.Width());
		rectMini.bottom = (int)((m_struIvmsRuleCfg.struRule[dwRuleID].struSizeFilter.struMiniRect.fY+m_struIvmsRuleCfg.struRule[dwRuleID].struSizeFilter.struMiniRect.fHeight)*m_rcWndRect.Height());
		FrameRect(hDc, rectMini, brTmp);
		
		rectMax.left = (int)(m_struIvmsRuleCfg.struRule[dwRuleID].struSizeFilter.struMaxRect.fX*m_rcWndRect.Width());
		rectMax.top = (int)(m_struIvmsRuleCfg.struRule[dwRuleID].struSizeFilter.struMaxRect.fY*m_rcWndRect.Height());
		rectMax.right = (int)((m_struIvmsRuleCfg.struRule[dwRuleID].struSizeFilter.struMaxRect.fX+m_struIvmsRuleCfg.struRule[dwRuleID].struSizeFilter.struMaxRect.fWidth)*m_rcWndRect.Width());
		rectMax.bottom = (int)((m_struIvmsRuleCfg.struRule[dwRuleID].struSizeFilter.struMaxRect.fY+m_struIvmsRuleCfg.struRule[dwRuleID].struSizeFilter.struMaxRect.fHeight)*m_rcWndRect.Height());
		FrameRect(hDc, rectMax, brTmp);
		
		SelectObject(hDc, pOldPen);
		DeleteObject(DrawPen);
	}
}

/*********************************************************
Function:	F_AddLabel
Desc:	add label
Input:	HDC hDc
		int iAlarmType
		DWORD dwRuleID
Output:	
Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::F_AddLabel(HDC hDc, int iAlarmType, DWORD dwRuleID)
{
	if (AlarmArea == iAlarmType)
	{
		CString szTemp(_T(""));
		CRect rect;
		UINT uFormat = DT_LEFT;
		int iTxtWidth = 0;//label width
		int iTxtHeight = 20;//	
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
		CRect rect;
		UINT uFormat = DT_LEFT;
		int iTxtWidth = 0;//lable width
		int iTxtHeight = 20;//lable height
		iTxtWidth = iTxtHeight;
		szTemp.Format("(%d)", dwRuleID);
		
		if (m_struVcaLine[dwRuleID].struStart.fX >= 0.5 && m_struVcaLine[dwRuleID].struStart.fY >= 0.5)
		{//line at right bottom
			uFormat = DT_RIGHT;
			rect.left = (int)(m_struVcaLine[dwRuleID].struStart.fX*m_rcWndRect.Width()) - iTxtWidth;
			rect.top = (int)(m_struVcaLine[dwRuleID].struStart.fY*m_rcWndRect.Height()) - iTxtHeight;
			rect.bottom = (int)(m_struVcaLine[dwRuleID].struStart.fY*m_rcWndRect.Height());
			rect.right = (int)(m_struVcaLine[dwRuleID].struStart.fX*m_rcWndRect.Width());
		}
		else if (m_struVcaLine[dwRuleID].struStart.fX < 0.5 && m_struVcaLine[dwRuleID].struStart.fY < 0.5)
		{//line at top left
			uFormat = DT_LEFT;
			rect.left = (int)(m_struVcaLine[dwRuleID].struStart.fX*m_rcWndRect.Width());
			rect.top = (int)(m_struVcaLine[dwRuleID].struStart.fY*m_rcWndRect.Height());
			rect.bottom = (int)(m_struVcaLine[dwRuleID].struStart.fY*m_rcWndRect.Height()) + iTxtHeight;
			rect.right = (int)(m_struVcaLine[dwRuleID].struStart.fX*m_rcWndRect.Width()) + iTxtWidth;
		}
		else if (m_struVcaLine[dwRuleID].struStart.fX < 0.5 && m_struVcaLine[dwRuleID].struStart.fY >= 0.5)
		{//line at left bottom
			uFormat = DT_LEFT;
			rect.left = (int)(m_struVcaLine[dwRuleID].struStart.fX*m_rcWndRect.Width());
			rect.top = (int)(m_struVcaLine[dwRuleID].struStart.fY*m_rcWndRect.Height()) - iTxtHeight;
			rect.bottom = (int)(m_struVcaLine[dwRuleID].struStart.fY*m_rcWndRect.Height());
			rect.right = (int)(m_struVcaLine[dwRuleID].struStart.fX*m_rcWndRect.Width()) + iTxtWidth;
		}
		else if (m_struVcaLine[dwRuleID].struStart.fX >= 0.5 && m_struVcaLine[dwRuleID].struStart.fY < 0.5)
		{
			//line at right top
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
Desc:	varify if it's a valid region
Input:	NET_VCA_POLYGON *alarm_region
Output:	
Return:	BOOL
**********************************************************/
BOOL CDlgVcaIvmsCfg::IsValidArea(NET_VCA_POLYGON *alarm_region)
{
	if(alarm_region == NULL)
	{
		return FALSE;
	}
	// check if all points are in same line
	if (F_IsStraightLine(alarm_region))
	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "所有点在同一直线上，不能组成多边形!",\
			"All points have been in the same line, not able to form the polygon");
		MessageBox(szLan);
		return FALSE;
	}
	// check if the line of start point and end point is crossed by existing line.
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
Function:	IsCrossLine
Desc:	
Input:	NET_VCA_POLYGON *alarm_region
Output:	
Return:	BOOL
**********************************************************/
BOOL CDlgVcaIvmsCfg::IsCrossLine(NET_VCA_POLYGON *alarm_region)
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
	
	// polygon should have 3 vertexes at least
	if (nPointTotal >= 3)
	{
		bCrossLine = FALSE;
	}
	// more than 3 vertexes
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
		
		// copy vertexes to an array, which length is 1 more than vertexes
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
Desc:	
Input:	NET_VCA_POLYGON *alarm_region
Output:	
Return:	BOOL
**********************************************************/
BOOL CDlgVcaIvmsCfg::F_IsACrossLine(NET_VCA_POLYGON *alarm_region)
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
	
	// polygon has 3 vertexes
	if (nPointTotal == VCA_MAX_POLYGON_POINT_NUM)
	{
		bCrossLine = FALSE;
	}
	// more than 3
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
		
		// copy vertexes to an array, which length is 1 more than vertexes
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
BOOL CDlgVcaIvmsCfg::F_IsStraightLine(NET_VCA_POLYGON *alarm_region)
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
	
	//check all points compose one line
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
	
	// check all points compose a line
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
	
	// check all points compose bias
	if ((0 != nXOffset) && (0 != nYOffset))
	{
		// slope
		fSlope  = 1.0f * nYOffset / nXOffset;
		// intercept of calculating  slope intercept form Equation
		fOffset = pPointArray[0].fY - fSlope * pPointArray[1].fX;
		// Coefficient for calculating distance between point to line. 
		fCoefficient = (float)sqrt(1.0 + fSlope * fSlope);
		
		for (i = 2; i < nPointTotal; i ++)
		{
			// calculating the distance to the line consist of point 0 and point 1. 
			fDistance = (float)fabs(fSlope * pPointArray[i].fX - pPointArray[i].fY + fOffset)/fCoefficient;
			
			// if one distance is larger than 0, the polygon is valid. 
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
		NET_VCA_POINT q2
Output:	
Return:	BOOL
**********************************************************/
BOOL CDlgVcaIvmsCfg::F_LineCrossDetect(NET_VCA_POINT p1, NET_VCA_POINT p2, NET_VCA_POINT q1, NET_VCA_POINT q2)
{
	NET_VCA_POINT p1_q1, q2_q1, p2_q1, q1_p1, p2_p1, q2_p1;    // vectorial difference；
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
	
	// cross product1 (p1 - q1) × (q2 - q1)；
	z1 = p1_q1.fX * q2_q1.fY - q2_q1.fX * p1_q1.fY; 
	
	// cross product2 (q2 - q1) × (p2 - q1)；
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
	
	// cross product3 (q1 - p1) × (p2 - p1)；
	z3 = q1_p1.fX * p2_p1.fY - p2_p1.fX * q1_p1.fY;
	
	// cross product4 (p2 - p1) × (q2 - p1);
	z4 = p2_p1.fX * q2_p1.fY - q2_p1.fX * p2_p1.fY;
	
	
	//  check if two lines are crossed；
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
Desc:	draw alert surface
Input:	long lPlayHandle
		HDC hDc
		DWORD dwUser
		DWORD dwRuleID
		COLORREF color
Output:	
Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::F_DrawLine(long lPlayHandle, HDC hDc, DWORD dwUser, DWORD dwRuleID, COLORREF color)
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
		
        //if absolute slope is larger than 2, draw rectange directly 
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
        //draw parallelogram, vertical height is 8
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
    
		//draw arrow
    F_DrawArrowhead(hDc, dwRuleID, m_struIvmsRuleCfg.struRule[dwRuleID].uEventParam.struTraversePlane.dwCrossDirection);
		//draw label
		F_AddLabel(hDc, AlarmLine, dwRuleID);
    
	SelectObject(hDc, pOldPen);
	DeleteObject(DrawPen);
}

/*********************************************************
Function:	F_DrawArrowhead
Desc:	draw arrow  
Input:	HDC hDc
		DWORD dwRuleID
		int direction 
Output:	
Return:	
**********************************************************/
void CDlgVcaIvmsCfg::F_DrawArrowhead(HDC hDc, DWORD dwRuleID, int direction)
{
    POINT ptArrow_start0;/*, ptArrow_start1, ptArrow_start2;*/
    POINT ptArrow_end;
    float fLine_k = 0.0, fArrow_k = 0.0, fArrow_k1 = 0.0;
    int   iTheta = 0;
    int   iDirection = -1;
    //check current directoin 
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

    //draw arrow
    //coordinate of middle point
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
    //if abs(slope) is larger than 2, the width is 4
    if(abs(fLine_k) >= 2)
		{
        pen.SetWidth(4);
    }
    else
    {
        //widht of arrow is 8*cos(alpha)
        float fWidth = 8.0 / sqrt(1.0 + fLine_k * fLine_k);
        pen.SetWidth(fWidth);
    }

    pen.SetStartCap(LineCapFlat);
    pen.SetEndCap(LineCapArrowAnchor);

    if (fLine_k != 0.0)
    {
        //slope of the segment perpendicular to alert line
        fArrow_k =  -1.0 / fLine_k;

        iTheta = (int)(atan(fArrow_k ) / PI * 180);

        if (0 == iDirection || 2 == iDirection)
        {
            //to prevent arrow departur segment, width subtract 1, 
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
        //arrow is in vertical direction
        if (0 == iDirection || 2 == iDirection)
		{
			// x increase direction；
            ptStart0.x = ptArrow_start0.x;
            ptStart0.y = ptArrow_start0.y;// + 4;

            ptArrow_end.x = ptStart0.x ;
            ptArrow_end.y = ptStart0.y + 20;

            graphics.DrawLine(&pen, ptStart0.x, ptStart0.y, ptArrow_end.x, ptArrow_end.y);
		}
        if (1 == iDirection || 2 == iDirection)
		{
			// x reduce direction
            ptStart0.x = ptArrow_start0.x;
            ptStart0.y = ptArrow_start0.y - 8;

            ptArrow_end.x = ptStart0.x ;
            ptArrow_end.y = ptStart0.y - 20;

            graphics.DrawLine(&pen, ptStart0.x, ptStart0.y, ptArrow_end.x, ptArrow_end.y);
		}		
	}
}

/*********************************************************
  Function:	OnCheckFilterActive
  Desc:		check if the size filter is valid  
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::OnCheckFilterActive() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_CHECK_SET_MAX_FILTER)->EnableWindow(m_bFilterActive);
	GetDlgItem(IDC_CHECK_SET_MINI_FILTER)->EnableWindow(m_bFilterActive);
}

/*********************************************************
  Function:	OnCheckSetMiniFilter
  Desc:		Set minimum rectangle of size fitler
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::OnCheckSetMiniFilter() 
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
  Desc:		Set maximum rectangle of size fitler
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::OnCheckSetMaxFilter() 
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
Function:	SetVcaEventPara
Desc:	Set Intelligent Behavior Event Parameter
Input:	NET_VCA_EVENT_UNION &uEventparam
		VCA_EVENT_TYPE struEventType
Output:	NET_VCA_EVENT_UNION &uEventparam
Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::SetVcaEventPara(NET_VCA_EVENT_UNION &uEventparam, VCA_EVENT_TYPE struEventType)
{
	switch (struEventType)
	{
	case VCA_TRAVERSE_PLANE:
		memcpy(&uEventparam.struTraversePlane.struPlaneBottom, &m_struVcaLine[m_iCurRuleID], sizeof(NET_VCA_LINE));
//		uEventparam.struTraversePlane.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
		uEventparam.struTraversePlane.dwCrossDirection = (VCA_CROSS_DIRECTION)m_comboAlarmDirect.GetCurSel();
		break;
	case VCA_ENTER_AREA:
		memcpy(&uEventparam.struArea.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
//		uEventparam.struArea.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
		break;
	case VCA_EXIT_AREA:
		memcpy(&uEventparam.struArea.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
//		uEventparam.struArea.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
		break;
	case VCA_INTRUSION:
		uEventparam.struIntrusion.wDuration = (WORD)m_iAlarmDelay;
		memcpy(&uEventparam.struIntrusion.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
//		uEventparam.struIntrusion.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
		break;
	case VCA_LOITER:
		uEventparam.struLoiter.wDuration = (WORD)m_iAlarmPersist;
		memcpy(&uEventparam.struLoiter.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
//		uEventparam.struLoiter.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
		break;
	case VCA_LEFT_TAKE:
		uEventparam.struTakeTeft.wDuration = (WORD)m_iAlarmPersist;
		memcpy(&uEventparam.struTakeTeft.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
//		uEventparam.struTakeTeft.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
		break;
	case VCA_PARKING:
		uEventparam.struParking.wDuration = (WORD)m_iAlarmPersist;
		memcpy(&uEventparam.struParking.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
//		uEventparam.struParking.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
		break;
	case VCA_RUN:
		uEventparam.struRun.fRunDistance = m_fMaxDistance;
		memcpy(&uEventparam.struRun.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
//		uEventparam.struRun.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
		break;
	case VCA_HIGH_DENSITY:
		uEventparam.struHighDensity.fDensity = m_fDenstityRate;
		memcpy(&uEventparam.struHighDensity.struRegion, &m_struVcaPolygon[m_iCurRuleID], sizeof(NET_VCA_POLYGON));
///		uEventparam.struHighDensity.bySensitivity = (BYTE)(m_comboSensitive.GetCurSel()+1);
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
	default:
		break;
	}
}


/*********************************************************
  Function:	InsertComboVcaType
  Desc:		Add correlative Intelligent type in ComboBox
  Input:	
  Output:	
  Return:	BOOL
**********************************************************/
BOOL CDlgVcaIvmsCfg::InsertComboVcaType()
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
	if (m_iPlateChanNum> 0)
	{
        char szLan[128] = {0};
        g_StringLanType(szLan, "车牌识别", "Plate Recognition");
        m_comboVcaType.InsertString(index, szLan);
        m_comboVcaType.SetItemData(index, VCA_PLATE);
        index++;
	}
	if (m_iAtmChanNum > 0)
	{
		m_comboVcaType.InsertString(index, "Intelligent ATM");
		m_comboVcaType.SetItemData(index, VCA_ATM);
		index++;
	}
	return TRUE;
}

/*********************************************************
  Function:	SetComboVcaType
  Desc:		
  Input:	BYTE byVcaType
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::SetComboVcaType(BYTE byVcaType)
{
	if (byVcaType == 0)
	{
		m_comboVcaType.SetCurSel(-1);
	}
	int nIndex = 0;
	

	for (int i = 0; i < m_comboVcaType.GetCount(); i++)
	{
		if (m_comboVcaType.GetItemData(i) == (DWORD)byVcaType)
		{
			m_comboVcaType.SetCurSel(i);
			return;
		}
		
	}
	
	
}

/*********************************************************
  Function:	InsertRuleID
  Desc:		
  Input:	int RuleNum
  Output:	
  Return:	BOOL
**********************************************************/
BOOL CDlgVcaIvmsCfg::InsertRuleID(int RuleNum)
{
	m_comboRuleId.ResetContent();
	char sbuf[128] = {0};
	for (int i= 0; i < RuleNum; i++)
	{	
		sprintf(sbuf, "Rule%d", i);
		m_comboRuleId.InsertString(i,sbuf);
	}
	return TRUE;
}

/*********************************************************
Function:	InsertRuleType
Desc:	Add rule type in ComboBox
Input:	int iBehaviorAbilityType
Output:	
Return:	BOOL
**********************************************************/
BOOL CDlgVcaIvmsCfg::InsertRuleType(int iBehaviorAbilityType)
{
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
		g_StringLanType(szLan, "物品遗留捡包", "Left and Take");
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
// 	if((iBehaviorAbilityType&STICK_UP_ABILITY) != 0)
// 	{
// 		m_comboRuleType.InsertString(index, "贴纸条");
// 		m_comboRuleType.SetItemData(index, VCA_STICK_UP);
// 		index++;
// 	}
// 	if ((iBehaviorAbilityType&INSTALL_SCANNER_ABILITY) != 0)
// 	{
// 		m_comboRuleType.InsertString(index, "安装读卡器");
// 		m_comboRuleType.SetItemData(index, (DWORD)VCA_INSTALL_SCANNER);
// 		index++;
// 	}
	return TRUE;
}

/*********************************************************
Function:	GetVcaDrawMode
Desc:		Get Overlay Target config
Input:	
Output:	
Return:		BOOL
**********************************************************/
BOOL CDlgVcaIvmsCfg::GetVcaDrawMode()
{
	memset(&m_struVCADrawMode, 0, sizeof(NET_VCA_DRAW_MODE));
	char szLan[128] = {0};
	if(!NET_DVR_GetVCADrawMode(m_lServerID,  m_iVcaChannel, &m_struVCADrawMode))	
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_VCA_DRAW_MODE %d", m_iVcaChannel);
		char sbufCn[128] = {0};
		char sbufEn[128] = {0};
		sprintf(sbufCn,"获取通道%d目标叠加失败", m_iVcaChannel);
		sprintf(sbufEn, "Fail to get Channel%d: VCA draw mode");
		g_StringLanType(szLan, sbufCn, sbufEn);
		OnCancel();
		return FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_VCA_DRAW_MODE %d", m_iVcaChannel);
	}
	m_bDspAddRule = m_struVCADrawMode.byDspAddRule;
	m_bDspAddTarget = m_struVCADrawMode.byDspAddTarget;
	m_bPicAddRule = m_struVCADrawMode.byDspPicAddRule;
	m_bPicAddTarget = m_struVCADrawMode.byDspPicAddTarget;
	return TRUE;
}

/*********************************************************
Function:	GetIVMSBehaviorCfg
Desc:	Get behavior rule config
Input:	NET_IVMS_RULECFG struIvmsRuleCfg
		int iRuleID
Output:	
Return:	BOOL
**********************************************************/
BOOL CDlgVcaIvmsCfg::GetIVMSRuleCfg(NET_IVMS_RULECFG struIvmsRuleCfg, int iRuleID)
{
	for(int i = 0;i<MAX_RULE_NUM; i++)
	{
		m_bNeedRedraw[i] = FALSE;//redraw polygon
		m_bCloseIn[i] = TRUE;// polygon is closed
	}
	
	m_comboRuleId.SetCurSel(iRuleID);
	UpdateData(FALSE);
	OnSelchangeComboRuleId();

	return TRUE;
}

/*********************************************************
Function:	GetDevVcaChanPara
Desc:		Get VCA channel ability
Input:	
Output:	
Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::GetDevVcaChanPara()
{
	m_iVcaChanNum = g_pMainDlg->m_struVcaDevAbility.byVCAChanNum;
	m_iPlateChanNum	 = g_pMainDlg->m_struVcaDevAbility.byPlateChanNum;
	m_iBBaseChanNum = g_pMainDlg->m_struVcaDevAbility.byBBaseChanNum;
	m_iBAdvanceChanNum = g_pMainDlg->m_struVcaDevAbility.byBAdvanceChanNum;
	m_iBFullChanNum = g_pMainDlg->m_struVcaDevAbility.byBFullChanNum;
	m_iAtmChanNum = g_pMainDlg->m_struVcaDevAbility.byATMChanNum;
	
	UpdateData(FALSE);
	
	memset(&m_struVcaCtrlCfg, 0,sizeof(NET_VCA_CTRLCFG));
	memcpy(&m_struVcaCtrlCfg, &g_pMainDlg->m_struVcaCtrlCfg,sizeof(NET_VCA_CTRLCFG));
	char sbuf[128];
	for (int i = 0; i < m_iVcaChanNum; i++)
	{
		sprintf(sbuf, "VCA channel%d", i+1);
		m_comboVcaChan.InsertString(i,sbuf);
	}
	
	InsertComboVcaType(); 
}

/*********************************************************
  Function:	OnSelchangeComboVcaChan
  Desc:		
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::OnSelchangeComboVcaChan() 
{
	// TODO: Add your control notification handler code here
	
 	UpdateData(TRUE);
 	m_iVcaChannel = m_comboVcaChan.GetCurSel()+1;
 	SetComboVcaType(m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byVCAType); //set VCA type
 	m_bVcaActive = m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byVCAEnable;
	
	EnableVcaWindow(m_bVcaActive); //if enable the intelligent function
	EnableRuleWindow(m_bVcaActive&&m_bRuleActive); 

	m_comboStream.SetCurSel(m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byStreamWithVCA);
	m_comboAtmMode.SetCurSel(m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byMode);
	m_bPicWithVca = m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byPicWithVCA;
	//If it's ATM mode，join into mask area. If it's ATM panel，join into enter area
	if(m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel -1].byVCAType == VCA_ATM)
	{
		if (m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel -1].byMode == 0)
		{
			GetDlgItem(IDC_BTN_ENTER_REGION)->ShowWindow(SW_SHOW);	
			GetEnterRegion();
	}
	else 
	{
			GetDlgItem(IDC_BTN_ENTER_REGION)->ShowWindow(SW_HIDE);
	}
		GetDlgItem(IDC_STATIC_ATM_MODE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_ATM_MODE)->ShowWindow(SW_SHOW);	
		GetDlgItem(IDC_BTN_MASK_REGION)->ShowWindow(SW_SHOW);
		GetMaskRegion();
	}
	else
	{
		GetDlgItem(IDC_COMBO_ATM_MODE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_ENTER_REGION)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_MASK_REGION)->ShowWindow(SW_HIDE);
	}

	RefreshVcaCtrl();
	UpdateData(FALSE);
}

/*********************************************************
Function:	GetIvmsStreamPara
Desc:	    Get IVMS parameter of fetching stream 
Input:	
Output:	
Return:	BOOL 
**********************************************************/
BOOL CDlgVcaIvmsCfg::GetIvmsStreamPara()
{
	DWORD dwReturned;
	memset(&m_struIVMSStreamCfg, 0, sizeof(NET_IVMS_STREAMCFG));
	if(!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_IVMS_STREAMCFG, m_iVcaChannel, &m_struIVMSStreamCfg, sizeof(NET_IVMS_STREAMCFG), &dwReturned))	
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_IVMS_STREAMCFG %d", m_iVcaChannel);
		AfxMessageBox("Fail to get IVMS Cfg");
//		OnCancel();
		return FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_IVMS_STREAMCFG %d", m_iVcaChannel);
	}
	return TRUE;
}

/*********************************************************
Function:	GetIvmsBehaviorCfg
Desc:	    Get IVMS behavior config
Input:	
Output:	
Return:	BOOL 
**********************************************************/
BOOL CDlgVcaIvmsCfg::GetIvmsBehaviorCfg()
{
	DWORD dwReturned;
	memset(&m_struIvmsBehaviorCfg, 0, sizeof(NET_IVMS_BEHAVIORCFG));
	if(!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_IVMS_BEHAVIORCFG, m_iVcaChannel, &m_struIvmsBehaviorCfg, sizeof(NET_IVMS_BEHAVIORCFG), &dwReturned))	
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_IVMS_BEHAVIORCFG %d", m_iVcaChannel);

		return FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_IVMS_BEHAVIORCFG %d", m_iVcaChannel);
	}
	return TRUE;

}

/*********************************************************
Function:	GetTimeSchedPara
Desc:	
Input:	int nWeekday
		int nTimePeriod
Output:	
Return:	BOOL
**********************************************************/
BOOL CDlgVcaIvmsCfg::GetTimeSchedPara(int nWeekday, int nTimePeriod)
{
	// time segment
	char chTimePeriod[128] = {0};
	int nIndex = m_comboTimePeriod.GetCurSel()+1;
	sprintf(chTimePeriod, "time%d: %dH%dM--%dH%dM", nIndex,
		m_struIVMSStreamCfg.struDevSched[nWeekday][nTimePeriod].struTime.byStartHour,
		m_struIVMSStreamCfg.struDevSched[nWeekday][nTimePeriod].struTime.byStartMin,
		m_struIVMSStreamCfg.struDevSched[nWeekday][nTimePeriod].struTime.byStopHour,
		m_struIVMSStreamCfg.struDevSched[nWeekday][nTimePeriod].struTime.byStopMin);
	m_csTimePeriod = chTimePeriod;	

// 	if(m_struIVMSStreamCfg.struDevSched[nWeekday][nTimePeriod].struPUStream.struStreamMediaSvrCfg.dwValid == TRUE)
// 	{
// 		m_csDevIP = "取流IP: ";
// 		m_csDevIP = m_struIVMSStreamCfg.struDevSched[nWeekday][nTimePeriod].struPUStream.struStreamMediaSvrCfg.struDevIP.sIpV4;
// 	}
// 	else
	{
		m_csDevIP = "device IP: ";
		m_csDevIP += m_struIVMSStreamCfg.struDevSched[nWeekday][nTimePeriod].struPUStream.struDevChanInfo.struIP.sIpV4;
	}

	UpdateData(FALSE);
	GetIVMSRuleCfg(m_struIvmsBehaviorCfg.struRuleCfg[m_iWeekday][m_iTimePeriod], 0);
	
	return TRUE;
}

/*********************************************************
  Function:	OnSelchangeComboWeekday
  Desc:		
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::OnSelchangeComboWeekday() 
{
	StopPlay();
	m_iWeekday = m_comboWeekday.GetCurSel();
	m_iTimePeriod = m_comboTimePeriod.GetCurSel();
	StartPlay(m_iWeekday, m_iTimePeriod);

	memcpy(&m_struIvmsRuleCfg, &m_struIvmsBehaviorCfg.struRuleCfg[m_iWeekday][m_iTimePeriod], sizeof(NET_IVMS_RULECFG));

	memset(&m_struVcaPolygon[0], 0, sizeof(NET_VCA_POLYGON)*MAX_RULE_NUM);
	memset(&m_struVcaLine[0], 0, sizeof(NET_VCA_LINE)*MAX_RULE_NUM);
	memset(&m_bCloseIn[0], 0, sizeof(BOOL)*MAX_RULE_NUM);
	memset(&m_bNeedRedraw[0], 0, sizeof(BOOL)*MAX_RULE_NUM);
	memset(&m_bMouseMove[0], 0, sizeof(BOOL)*MAX_RULE_NUM);

	GetTimeSchedPara(m_iWeekday, m_iTimePeriod);
}

/*********************************************************
  Function:	OnSelchangeComboTimePeriod
  Desc:		
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::OnSelchangeComboTimePeriod() 
{
	StopPlay();
	m_iWeekday = m_comboWeekday.GetCurSel();
	m_iTimePeriod = m_comboTimePeriod.GetCurSel();
	StartPlay(m_iWeekday, m_iTimePeriod);
	memcpy(&m_struIvmsRuleCfg, &m_struIvmsBehaviorCfg.struRuleCfg[m_iWeekday][m_iTimePeriod], sizeof(NET_IVMS_RULECFG));	

	memset(&m_struVcaPolygon[0], 0, sizeof(NET_VCA_POLYGON)*MAX_RULE_NUM);
	memset(&m_struVcaLine[0], 0, sizeof(NET_VCA_LINE)*MAX_RULE_NUM);
	memset(&m_bCloseIn[0], 0, sizeof(BOOL)*MAX_RULE_NUM);
	memset(&m_bNeedRedraw[0], 0, sizeof(BOOL)*MAX_RULE_NUM);
	memset(&m_bMouseMove[0], 0, sizeof(BOOL)*MAX_RULE_NUM);


	GetTimeSchedPara(m_iWeekday, m_iTimePeriod);
}

/*********************************************************
Function:	GetIvmsOneRuleSet
Desc:	
Input:	NET_IVMS_ONE_RULE struIvmsRule
Output:	
Return:	
**********************************************************/
BOOL CDlgVcaIvmsCfg::GetIvmsOneRuleSet(NET_IVMS_ONE_RULE struIvmsRule)
{
	m_bRuleActive = struIvmsRule.byActive; //valid rule
	EnableRuleWindow(m_bRuleActive);
	m_csRuleName = struIvmsRule.byRuleName; 
	
	m_bFilterActive = struIvmsRule.struSizeFilter.byActive;
	GetDlgItem(IDC_CHECK_SET_MAX_FILTER)->EnableWindow(m_bFilterActive&m_bRuleActive);
	GetDlgItem(IDC_CHECK_SET_MINI_FILTER)->EnableWindow(m_bFilterActive&m_bRuleActive);
	UpdateData(FALSE);
	
	GetEventTypeSet(struIvmsRule.dwEventType);	
	GetEventParaSet(struIvmsRule.dwEventType, struIvmsRule.uEventParam);
	return TRUE;
}

/*********************************************************
  Function:	GetEventTypeSet
  Desc:		
  Input:	VCA_EVENT_TYPE struEventType
  Output:	
  Return:	
**********************************************************/
BOOL CDlgVcaIvmsCfg::GetEventTypeSet(VCA_EVENT_TYPE struEventType)
{
	if (struEventType == 0)
	{
		m_comboRuleType.SetCurSel(-1);
		return FALSE;
	}
	for (int i = 0; i < 32; i++)
	{
		if((VCA_EVENT_TYPE)m_comboRuleType.GetItemData(i) == struEventType)
		{
			m_comboRuleType.SetCurSel(i);
			UpdateData(FALSE);
			OnSelchangeComboRuleType();
			return TRUE;
		}
	}
	return FALSE;
}

/*********************************************************
  Function:	GetEventParaSet
  Desc:		
  Input:	VCA_EVENT_TYPE struEventType
			NET_VCA_EVENT_UNION uEventParam
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::GetEventParaSet(VCA_EVENT_TYPE struEventType,NET_VCA_EVENT_UNION uEventParam)
{
	BYTE bySensitivity = 0;
	switch (struEventType)
	{
	case VCA_TRAVERSE_PLANE:
//		bySensitivity = uEventParam.struTraversePlane.bySensitivity;
		m_comboAlarmDirect.SetCurSel(uEventParam.struTraversePlane.dwCrossDirection);
		OnSelchangeComboLineAlarmDirect();
		memcpy(&m_struVcaLine[m_iCurRuleID], &uEventParam.struTraversePlane.struPlaneBottom, sizeof(NET_VCA_LINE));
		break;
	case VCA_ENTER_AREA:
//		bySensitivity = uEventParam.struArea.bySensitivity;		
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struArea.struRegion, sizeof(NET_VCA_POLYGON));
		break;
	case VCA_EXIT_AREA:
//		bySensitivity = uEventParam.struArea.bySensitivity;		
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struArea.struRegion, sizeof(NET_VCA_POLYGON));
		break;
	case VCA_INTRUSION:
//		bySensitivity = uEventParam.struIntrusion.bySensitivity;		
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struIntrusion.struRegion, sizeof(NET_VCA_POLYGON));
		m_iAlarmDelay = uEventParam.struIntrusion.wDuration;
		m_staticAlarmDelay.ShowWindow(SW_SHOW);
		m_staticAlarmDelayArea.ShowWindow(SW_SHOW);
		m_editAlarmDelay.ShowWindow(SW_SHOW);
		break;
	case VCA_LOITER:
//		bySensitivity = uEventParam.struLoiter.bySensitivity;	
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struLoiter.struRegion, sizeof(NET_VCA_POLYGON));
		m_iAlarmPersist	= uEventParam.struLoiter.wDuration;
		m_staticAlarmPersist.ShowWindow(SW_SHOW);
		m_staticAlarmPersistArea.ShowWindow(SW_SHOW);
		m_editAlarmPersist.ShowWindow(SW_SHOW);
		break;
	case VCA_LEFT_TAKE:
//		bySensitivity = uEventParam.struTakeTeft.bySensitivity;		
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struTakeTeft.struRegion, sizeof(NET_VCA_POLYGON));
		m_iAlarmPersist	= uEventParam.struTakeTeft.wDuration;
		m_staticAlarmPersist.ShowWindow(SW_SHOW);
		m_staticAlarmPersistArea.ShowWindow(SW_SHOW);
		m_editAlarmPersist.ShowWindow(SW_SHOW);
		break;
	case VCA_PARKING:
//		bySensitivity = uEventParam.struParking.bySensitivity;
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struParking.struRegion, sizeof(NET_VCA_POLYGON));
		m_iAlarmPersist	= uEventParam.struParking.wDuration;
		m_staticAlarmPersist.ShowWindow(SW_SHOW);
		m_staticAlarmPersistArea.ShowWindow(SW_SHOW);
		m_editAlarmPersist.ShowWindow(SW_SHOW);
		break;
	case VCA_RUN:
//		bySensitivity = uEventParam.struRun.bySensitivity;		
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struRun.struRegion, sizeof(NET_VCA_POLYGON));
		m_fMaxDistance = uEventParam.struRun.fRunDistance;
		m_staticMaxDistance.ShowWindow(SW_SHOW);
		m_staticMaxDistanceArea.ShowWindow(SW_SHOW);
		m_editMaxDistance.ShowWindow(SW_SHOW);
		break;
	case VCA_HIGH_DENSITY:
//		bySensitivity = uEventParam.struHighDensity.bySensitivity;		
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struHighDensity.struRegion, sizeof(NET_VCA_POLYGON));
		m_fDenstityRate = uEventParam.struHighDensity.fDensity;
		m_staticDenstityRate.ShowWindow(SW_SHOW);
		m_staticDenstityRateArea.ShowWindow(SW_SHOW);
		m_editDenstityRate.ShowWindow(SW_SHOW);
		break;
	case VCA_STICK_UP:
		bySensitivity = uEventParam.struStickUp.bySensitivity;		
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struStickUp.struRegion, sizeof(NET_VCA_POLYGON));
		m_iAlarmPersist = uEventParam.struStickUp.wDuration;
		m_staticAlarmPersist.ShowWindow(SW_SHOW);
		m_staticAlarmPersistStickUpArea.ShowWindow(SW_SHOW);
		m_editAlarmPersist.ShowWindow(SW_SHOW);
		
		break;
	case VCA_INSTALL_SCANNER:
		bySensitivity = uEventParam.struScanner.bySensitivity;		
		memcpy(&m_struVcaPolygon[m_iCurRuleID], &uEventParam.struScanner.struRegion, sizeof(NET_VCA_POLYGON));
		m_iReadCardTimePersist	 = uEventParam.struScanner.wDuration;
		m_staticReadCardTimePersist.ShowWindow(SW_SHOW);
		m_staticReadCardTimePersistArea.ShowWindow(SW_SHOW);
		m_editReadCardTimePersist.ShowWindow(SW_SHOW);
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
  Function:	OnSelchangeComboLineAlarmDirect
  Desc:		
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::OnSelchangeComboLineAlarmDirect() 
{
	// TODO: Add your control notification handler code here
	VCA_CROSS_DIRECTION iDirect;
	iDirect = (VCA_CROSS_DIRECTION)m_comboAlarmDirect.GetCurSel();
	m_struIvmsRuleCfg.struRule[m_iCurRuleID].uEventParam.struTraversePlane.dwCrossDirection = iDirect;
}

/*********************************************************
  Function:	OnSelchangeComboRuleType
  Desc:		
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::OnSelchangeComboRuleType() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	VCA_EVENT_TYPE struEventType;
	struEventType = GetEventType(m_comboRuleType.GetCurSel());
	ShowRuleTypeWnd(struEventType);
	
	if (struEventType == m_struIvmsBehaviorCfg.struRuleCfg[m_iWeekday][m_iTimePeriod].struRule[m_iCurRuleID].dwEventType)
	{
		GetEventParaSet(struEventType, m_struIvmsBehaviorCfg.struRuleCfg[m_iWeekday][m_iTimePeriod].struRule[m_iCurRuleID].uEventParam);
	}
	else
	{
		NET_VCA_EVENT_UNION uEventParam;
		memset(&uEventParam, 0, sizeof(NET_VCA_EVENT_UNION));
		GetEventParaSet(struEventType, uEventParam);
	}
	m_struIvmsRuleCfg.struRule[m_iCurRuleID].dwEventType = struEventType;

	UpdateData(FALSE);
}

/*********************************************************
Function:	ShowRuleTypeWnd
Desc:	
Input:	VCA_EVENT_TYPE struEventType
Output:	
Return:	
**********************************************************/
BOOL CDlgVcaIvmsCfg::ShowRuleTypeWnd(VCA_EVENT_TYPE struEventType)
{
	//Hide and show control 

	m_staticAlarmDelay.ShowWindow(SW_HIDE);
	m_staticAlarmPersist.ShowWindow(SW_HIDE);
	m_staticMaxDistance.ShowWindow(SW_HIDE);
	m_staticDenstityRate.ShowWindow(SW_HIDE);
	m_staticReadCardTimePersist.ShowWindow(SW_HIDE);
	m_staticAlarmPersistStickUpArea.ShowWindow(SW_HIDE);

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
		
	GetDlgItem(IDC_CHK_DRAW_LINE)->ShowWindow(SW_HIDE);
	m_staticAlarmDirect.ShowWindow(SW_HIDE);
	m_comboAlarmDirect.ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CHK_DRAW_POLYGON)->ShowWindow(SW_HIDE);

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

		if (struEventType == VCA_ENTER_AREA)
		{
		}
		else if (struEventType == VCA_EXIT_AREA)
		{
		}
		else if (struEventType == VCA_INTRUSION)
		{
			m_staticAlarmDelay.ShowWindow(SW_SHOW);
			m_staticAlarmDelayArea.ShowWindow(SW_SHOW);
			m_editAlarmDelay.ShowWindow(SW_SHOW);
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
			m_staticAlarmPersistStickUpArea.ShowWindow(SW_SHOW);
			m_staticAlarmPersist.ShowWindow(SW_SHOW);
			m_editAlarmPersist.ShowWindow(SW_SHOW);
		}
		else if (struEventType == VCA_INSTALL_SCANNER)
		{
			m_staticReadCardTimePersist.ShowWindow(SW_SHOW);
			m_staticReadCardTimePersistArea.ShowWindow(SW_SHOW);
			m_editReadCardTimePersist.ShowWindow(SW_SHOW);
		}
		else
		{
			return FALSE;
		}
	}
	return TRUE;	
}

/*********************************************************
  Function:	EnableVcaWindow
  Desc:		
  Input:	BOOL bEnable
  Output:	
  Return:	BOOL
**********************************************************/
BOOL CDlgVcaIvmsCfg::EnableVcaWindow(BOOL bEnable)
{
	GetDlgItem(IDC_COMBO_VCA_TYPE)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_STREAM)->EnableWindow(bEnable);

	GetDlgItem(IDC_BTN_VCA_RESTART)->EnableWindow(bEnable);
	
	GetDlgItem(IDC_CHK_PIC_PRO)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_PIC_QUALITY)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_RESOLUTION)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_PIC_OK)->EnableWindow(bEnable);

	GetDlgItem(IDC_BTN_IVMS_SCHED)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBOWEEKDAY)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_TIME_PERIOD)->EnableWindow(bEnable);

	GetDlgItem(IDC_CHECK_DSP_ADD_TARGET)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_DSP_ADD_RULE)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_PIC_ADD_TARGET)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_PIC_ADD_RULE)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_SET_VCA_DRAW_MODE)->EnableWindow(bEnable);

	GetDlgItem(IDC_COMBO_RULE_ID)->EnableWindow(bEnable);

	GetDlgItem(IDC_CHK_RULE_ACTIVE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_RULE_NAME)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_RULE_TYPE)->EnableWindow(bEnable);

	GetDlgItem(IDC_CHECK_FILTER_ACTIVE)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_SET_MINI_FILTER)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_SET_MAX_FILTER)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_SENSITIVE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_ALARM_DELAY)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_ALARM_PERSIST)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MAX_DISTANCE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_DENSTITY_RATE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_READ_CARD_TIME_PERSIST)->EnableWindow(bEnable);
	GetDlgItem(IDC_STATIC_ALARM_DIRECT)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_LINE_ALARM_DIRECT)->EnableWindow(bEnable);

	GetDlgItem(IDC_CHK_DRAW_POLYGON)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHK_DRAW_LINE)->EnableWindow(bEnable);
	return TRUE;
}

/*********************************************************
  Function:	OnSelchangeComboRuleId
  Desc:		
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::OnSelchangeComboRuleId() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_iCurRuleID = m_comboRuleId.GetCurSel();

	GetIvmsOneRuleSet(m_struIvmsRuleCfg.struRule[m_iCurRuleID]); 
}

/*********************************************************
  Function:	SetRuleActiveAble
  Desc:		
  Input:	BOOL bEnable
  Output:	
  Return:	BOOL
**********************************************************/
BOOL CDlgVcaIvmsCfg::SetRuleActiveAble(BOOL bEnable)
{
	m_comboRuleType.EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_RULE_NAME)->EnableWindow(bEnable);
	return TRUE;
}

/*********************************************************
  Function:	OnBtnRuleOk
  Desc:		function for OK button
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::OnBtnRuleOk() 
{ 
	// TODO: Add your control notification handler code here
	SetOneIvmsRule(m_struIvmsRuleCfg.struRule[m_iCurRuleID]);
	memcpy(&m_struIvmsBehaviorCfg.struRuleCfg[m_iWeekday][m_iTimePeriod], 
		&m_struIvmsRuleCfg, sizeof(NET_IVMS_RULECFG));
}

/*********************************************************
  Function:	SetOneIvmsRule
  Desc:		
  Input:	NET_IVMS_ONE_RULE &struIvmsRule
  Output:	
  Return:	BOOL
**********************************************************/
BOOL CDlgVcaIvmsCfg::SetOneIvmsRule(NET_IVMS_ONE_RULE &struIvmsRule)
{
	UpdateData(TRUE);
	struIvmsRule.byActive = (BYTE)m_bRuleActive;//valid or not
	//ruleName
	memset(&struIvmsRule.byRuleName[0], 0, sizeof(BYTE)*NAME_LEN);
	strncpy((char*)struIvmsRule.byRuleName, (char*)m_csRuleName.GetBuffer(0), NAME_LEN-1);
	//dweventtype
	struIvmsRule.dwEventType = GetEventType(m_comboRuleType.GetCurSel());
	//size filter
	struIvmsRule.struSizeFilter.byActive = (BYTE)m_bFilterActive;
	
	SetVcaEventPara(struIvmsRule.uEventParam, struIvmsRule.dwEventType);
	return TRUE;
}

/*********************************************************
  Function:	OnSelchangeComboPicQuality
  Desc:		
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgVcaIvmsCfg::OnSelchangeComboPicQuality() 
{
	// TODO: Add your control notification handler code here
	m_struIvmsBehaviorCfg.struPicParam.wPicQuality = (WORD)m_comboPicQuality.GetCurSel();
}

/*********************************************************
  Function:	OnSelchangeComboResolution
  Desc:		
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgVcaIvmsCfg::OnSelchangeComboResolution() 
{
	// TODO: Add your control notification handler code here
	m_struIvmsBehaviorCfg.struPicParam.wPicSize = (WORD)m_comboResolution.GetCurSel();
}


/*********************************************************
  Function:	GetIVMSChanAbility
  Desc:		
  Input:	
  Output:	
  Return:	BOOL
**********************************************************/
BOOL CDlgVcaIvmsCfg::GetIVMSChanAbility(int iChannel, NET_VCA_CHAN_IN_PARAM struVcaChanInpara)
{
	char szLan[128] = {0};
	char sbufCn[128] = {0};
	char sbufEn[128] = {0};
	
	if(!NET_DVR_GetDeviceAbility(m_lServerID,  VCA_CHAN_ABILITY, (char*)&struVcaChanInpara, \
		sizeof(NET_VCA_CHAN_IN_PARAM), (char*)&m_struBehaviorAbility, sizeof(NET_VCA_BEHAVIOR_ABILITY)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "VCA_CHAN_ABILITY");
		g_StringLanType(szLan, "获取智能通道能力失败", "Fail to Get Channel Ability");
		AfxMessageBox(szLan);
		OnCancel();
		return FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "VCA_CHAN_ABILITY");
	}
	
	
	if (!InsertRuleID(m_struBehaviorAbility.byMaxRuleNum))
	{
		return FALSE;
	}
	//get different behaviors according to behavior ability
	
	if(!InsertRuleType(m_struBehaviorAbility.dwAbilityType))
	{
		return FALSE;
	}
	UpdateData(FALSE);
	return TRUE;
}

/*********************************************************
  Function:	OnBtnPicOk
  Desc:		
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::OnBtnPicOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struIvmsBehaviorCfg.byPicProType = (BYTE)m_bPicPro;
	m_struIvmsBehaviorCfg.struPicParam.wPicQuality = (WORD)m_comboPicQuality.GetCurSel();
	m_struIvmsBehaviorCfg.struPicParam.wPicSize = (WORD)m_comboResolution.GetCurSel();
	
	memcpy(&m_struIvmsBehaviorCfg.struRuleCfg[m_iWeekday][m_iTimePeriod], &m_struIvmsRuleCfg, sizeof(NET_IVMS_RULECFG));

}

/*********************************************************
  Function:	OnSelchangeComboVcaType
  Desc:		
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::OnSelchangeComboVcaType() 
{
	// TODO: Add your control notification handler code here
	if ((m_comboVcaType.GetCurSel() != CB_ERR) && m_bVcaActive)
	{
		EnableVcaWindow(m_bVcaActive); 
		EnableRuleWindow(m_bVcaActive&&m_bRuleActive); 
	}
	if(m_comboVcaType.GetItemData(m_comboVcaType.GetCurSel()) == VCA_ATM)
	{
		GetDlgItem(IDC_STATIC_ATM_MODE)->ShowWindow(SW_SHOW);
		m_comboAtmMode.ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_STATIC_ATM_MODE)->ShowWindow(SW_HIDE);
		m_comboAtmMode.ShowWindow(SW_HIDE);
	}
}

/*********************************************************
  Function:	OnCancel
  Desc:		
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::OnCancel() 
{
	// TODO: Add extra cleanup here
	CDialog::OnCancel();
}

/*********************************************************
  Function:	PostNcDestroy
  Desc:		destroy diaglog
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgVcaIvmsCfg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (m_lPlayHandle >= 0)
	{
		NET_DVR_StopRealPlay(m_lPlayHandle);
	}
	if (m_lUserID >= 0)
	{
		if (!NET_DVR_Logout_V30(m_lUserID))
		{
			AfxMessageBox("Fail to logout");
		}
	}
	CDialog::PostNcDestroy();
}

/*********************************************************
  Function:	OnBtnMaskRegion
  Desc:		
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgVcaIvmsCfg::OnBtnMaskRegion() 
{
	// TODO: Add your control notification handler code here
    CDlgVcaMaskRegion dlg;
	dlg.m_lServerID = m_lUserID;
	dlg.m_iChannel = m_struIVMSStreamCfg.struDevSched[m_iWeekday][m_iTimePeriod].struPUStream.struDevChanInfo.byChannel;
    dlg.m_iDevIndex = m_iDevIndex;
   memcpy(&(dlg.m_struMaskRegionList), &(m_struIVMSMaskList.struList[m_iWeekday][m_iTimePeriod]), sizeof(NET_VCA_MASK_REGION_LIST));
	if (dlg.DoModal()==IDOK)
	{
		memcpy(&(m_struIVMSMaskList.struList[m_iWeekday][m_iTimePeriod]), \
            &(dlg.m_struMaskRegionList), sizeof(NET_VCA_MASK_REGION_LIST));
	}	
}

/*********************************************************
  Function:	OnBtnEnterRegion
  Desc:		
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::OnBtnEnterRegion() 
{
	// TODO: Add your control notification handler code here
    CDlgVcaEnterRegion dlg;
	dlg.m_lServerID = m_lUserID;
	dlg.m_iChannel = m_struIVMSStreamCfg.struDevSched[m_iWeekday][m_iTimePeriod].struPUStream.struDevChanInfo.byChannel;
    dlg.m_iDevIndex = m_iDevIndex;
	memcpy(&(dlg.m_struVCAEnterRegion), &(m_struIVMSEnterRegion.struEnter[m_iWeekday][m_iTimePeriod]), sizeof(NET_VCA_ENTER_REGION));
	if (dlg.DoModal()==IDOK)
	{
		memcpy(&(m_struIVMSEnterRegion.struEnter[m_iWeekday][m_iTimePeriod]), \
			&(dlg.m_struVCAEnterRegion), sizeof(NET_VCA_ENTER_REGION));
	}	
}

/*********************************************************
  Function:	OnBtnCopyDay
  Desc:		copy time segment parameter
  Input:	
  Output:	
  Return:	void
**********************************************************/
void CDlgVcaIvmsCfg::OnBtnCopyDay() 
{
	// TODO: Add your control notification handler code here
	if ((m_comboWeekdayCopy.GetCurSel() == CB_ERR))
	{
		AfxMessageBox("Please Select the day");
		return;
	}
	else
	{
		if (m_comboWeekdayCopy.GetCurSel() == 0)
		{
			for (int i = 0; i < MAX_DAYS; i++)
			{
				memcpy(&m_struIVMSStreamCfg.struDevSched[i], &m_struIVMSStreamCfg.struDevSched[m_iWeekday], sizeof(NET_IVMS_DEVSCHED)*MAX_TIMESEGMENT);
				memcpy(&m_struIvmsBehaviorCfg.struRuleCfg[i], &m_struIvmsBehaviorCfg.struRuleCfg[m_iWeekday], sizeof(NET_IVMS_RULECFG)*MAX_TIMESEGMENT);
				if(m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel -1].byVCAType == VCA_ATM)
				{
					memcpy(&m_struIVMSMaskList.struList[i], &m_struIVMSMaskList.struList[m_iWeekday], \
						sizeof(NET_VCA_MASK_REGION_LIST)*MAX_TIMESEGMENT);
					if (m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel -1].byMode == 0)
					{
						memcpy(&m_struIVMSEnterRegion.struEnter[i], &m_struIVMSEnterRegion.struEnter[m_iWeekday], \
							sizeof(NET_VCA_ENTER_REGION)*MAX_TIMESEGMENT);
					}
				}
			}
		}
		else
		{
			memcpy(&m_struIVMSStreamCfg.struDevSched[m_comboWeekdayCopy.GetCurSel()-1], &m_struIVMSStreamCfg.struDevSched[m_iWeekday], sizeof(NET_IVMS_DEVSCHED)*MAX_TIMESEGMENT);
			memcpy(&m_struIvmsBehaviorCfg.struRuleCfg[m_comboWeekdayCopy.GetCurSel()-1], &m_struIvmsBehaviorCfg.struRuleCfg[m_iWeekday], sizeof(NET_IVMS_RULECFG)*MAX_TIMESEGMENT);
			if(m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel -1].byVCAType == VCA_ATM)
			{
				memcpy(&m_struIVMSMaskList.struList[m_comboWeekdayCopy.GetCurSel()-1], &m_struIVMSMaskList.struList[m_iWeekday], \
					sizeof(NET_VCA_MASK_REGION_LIST)*MAX_TIMESEGMENT);
				if (m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel -1].byMode == 0)
				{
					memcpy(&m_struIVMSEnterRegion.struEnter[m_comboWeekdayCopy.GetCurSel()-1], &m_struIVMSEnterRegion.struEnter[m_iWeekday], \
						sizeof(NET_VCA_ENTER_REGION)*MAX_TIMESEGMENT);					
				}
			}

		}
		AfxMessageBox("Copy Success!");
	}
	
}


/*********************************************************
Function:StartPlay
Desc: play one channel
Input:	
Output:	
Return:	
**********************************************************/
void CDlgVcaIvmsCfg::StartPlay(int iTimeWeekday, int iTimePeriod)
{
// 	if (m_struIVMSStreamCfg.struDevSched[iTimeWeekday][iTimePeriod].struPUStream.struStreamMediaSvrCfg.dwValid == 0)//使用设备
	{
		NET_DVR_DEVICEINFO_V30 struDeviceInfo;
		m_lUserID = NET_DVR_Login_V30(m_struIVMSStreamCfg.struDevSched[iTimeWeekday][iTimePeriod].struPUStream.struDevChanInfo.struIP.sIpV4, 
			m_struIVMSStreamCfg.struDevSched[iTimeWeekday][iTimePeriod].struPUStream.struDevChanInfo.wDVRPort,
			(char*)m_struIVMSStreamCfg.struDevSched[iTimeWeekday][iTimePeriod].struPUStream.struDevChanInfo.sUserName,
			(char*)m_struIVMSStreamCfg.struDevSched[iTimeWeekday][iTimePeriod].struPUStream.struDevChanInfo.sPassword,&struDeviceInfo);
		
	
		NET_DVR_CLIENTINFO struPlay;
		GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWndRect);
		struPlay.hPlayWnd 	= GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
		struPlay.lChannel 	= m_struIVMSStreamCfg.struDevSched[iTimeWeekday][iTimePeriod].struPUStream.struDevChanInfo.byChannel; 
		struPlay.lLinkMode 	= 0;
		struPlay.sMultiCastIP = "";	
		
		
		m_lPlayHandle = NET_DVR_RealPlay_V30(m_lUserID, &struPlay, NULL, NULL, TRUE); 
		BOOL bRet = FALSE;
		if (m_lPlayHandle < 0)
		{
			g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_RealPlay_V30");
//			AfxMessageBox("NET_DVR_RealPlay_V30 FAIL");		
		}
		else
		{
			bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawIVMSAlertShow, 0);//set dc draw callback
		}
		
	}
// 	else//enble streaming media server
// 	{
// 		
// 	}
	
}


/*********************************************************
Function:StopPlay
Desc:   stop play one channel
Input:	
Output:	
Return:	
**********************************************************/
void CDlgVcaIvmsCfg::StopPlay()
{
	if (m_lPlayHandle >= 0)
	{
		NET_DVR_StopRealPlay(m_lPlayHandle);
	}
	if (m_lUserID >= 0)
	{
		if (!NET_DVR_Logout_V30(m_lUserID))
		{
			AfxMessageBox("Fail to logout"); 
		}
	}

	CWnd   *pWnd = GetDlgItem(IDC_PLAYWND);  
	RECT   rect;
	if (pWnd != NULL)
	{
		pWnd->GetWindowRect(&rect);
	}
	
	ScreenToClient(&rect);
	InvalidateRect(&rect);
}
