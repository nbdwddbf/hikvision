// DlgTPSRuleCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgTPSRuleCfg.h"
#include "DrawFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTPSRuleCfg dialog
CDlgTPSRuleCfg *g_pDlgTpsRule = NULL;
void CALLBACK g_DrawTpsRule(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
    g_pDlgTpsRule->F_DrawFun(lRealHandle, hDc, dwUser);
}

CDlgTPSRuleCfg::CDlgTPSRuleCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTPSRuleCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTPSRuleCfg)
	m_bEnable = FALSE;
	m_bFilterActive = FALSE;
	m_bSetMaxFilter = FALSE;
	m_bSetMiniFilter = FALSE;
	m_bHandleType1 = FALSE;
	m_bHandleType2 = FALSE;
	m_bHandleType3 = FALSE;
	m_bHandleType4 = FALSE;
	m_bHandleType5 = FALSE;
	m_bDrawPolygon = FALSE;
	m_fMaxHeight = 0.0f;
	m_fMaxWidth = 0.0f;
	m_fMinHeight = 0.0f;
	m_fMinWidth = 0.0f;
	m_iHour11 = 0;
	m_iMin11 = 0;
	m_iHour12 = 0;
	m_iMin12 = 0;
	m_iHour21 = 0;
	m_iMin21 = 0;
	m_iHour22 = 0;
	m_iMin22 = 0;
	m_iHour31 = 0;
	m_iMin31 = 0;
	m_iHour32 = 0;
	m_iMin32 = 0;
	m_iHour41 = 0;
	m_iMin41 = 0;
	m_iHour42 = 0;
	m_iMin42 = 0;
	m_iHour51 = 0;
	m_iMin51 = 0;
	m_iHour52 = 0;
	m_iMin52 = 0;
	m_iHour61 = 0;
	m_iMin61 = 0;
	m_iHour62 = 0;
	m_iMin62 = 0;
	m_iHour71 = 0;
	m_iMin71 = 0;
	m_iHour72 = 0;
	m_iMin72 = 0;
	m_iHour81 = 0;
	m_iMin81 = 0;
	m_iHour82 = 0;
	m_iMin82 = 0;
	//}}AFX_DATA_INIT
    m_iDevIndex = -1;
    m_lServerID = -1;
    m_lChannel = -1;
    memset(&m_struTPSRuleCfg, 0, sizeof(m_struTPSRuleCfg));
    memset(&m_struLaneCfg, 0, sizeof(m_struLaneCfg));
    m_iTPSIndex = -1;
    m_dwAlarmOutNum = 0;
    m_lPlayHandle = -1;
    memset(&m_struPUStream, 0, sizeof(m_struPUStream));
    m_lPUServerID = -1;
    m_dwPosNum = 0;
    memset(&m_rcWnd, 0, sizeof(m_rcWnd));
    memset(m_bCloseIn, 0, sizeof(m_bCloseIn));
    memset(m_bMouseMove, 0, sizeof(m_bMouseMove));
    memset(m_bNeedRedraw, 0, sizeof(m_bNeedRedraw));
    memset(m_struVcaPolygon, 0, sizeof(m_struVcaPolygon));
    memset(&m_struVcaChanInParam, 0, sizeof(m_struVcaChanInParam));
    memset(&m_struItsAbility, 0, sizeof(m_struItsAbility));
}


void CDlgTPSRuleCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTPSRuleCfg)
	DDX_Control(pDX, IDC_COMBO_FILTER_MODE, m_comboFilterMode);
	DDX_Control(pDX, IDC_LIST_ALARM_OUT, m_listAlarmOut);
	DDX_Control(pDX, IDC_COMBO_LANE_ID, m_comboLaneID);
	DDX_Control(pDX, IDC_COMBO_TPS_INDEX, m_comboTPSIndex);
	DDX_Control(pDX, IDC_COMBOWEEKDAY, m_comboWeekday);
	DDX_Control(pDX, IDC_COMBOCOPYTIME, m_comboCopyTime);
	DDX_Control(pDX, IDC_LIST_TPS_TYPE, m_listTPSType);
	DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
	DDX_Check(pDX, IDC_CHECK_FILTER_ACTIVE, m_bFilterActive);
	DDX_Check(pDX, IDC_CHECK_SET_MAX_FILTER, m_bSetMaxFilter);
	DDX_Check(pDX, IDC_CHECK_SET_MINI_FILTER, m_bSetMiniFilter);
	DDX_Check(pDX, IDC_CHECKHANDLETYPE1, m_bHandleType1);
	DDX_Check(pDX, IDC_CHECKHANDLETYPE2, m_bHandleType2);
	DDX_Check(pDX, IDC_CHECKHANDLETYPE3, m_bHandleType3);
	DDX_Check(pDX, IDC_CHECKHANDLETYPE4, m_bHandleType4);
	DDX_Check(pDX, IDC_CHECKHANDLETYPE5, m_bHandleType5);
	DDX_Check(pDX, IDC_CHECK_DRAW_VIRTUAL_LOOP, m_bDrawPolygon);
	DDX_Text(pDX, IDC_EDIT_MAX_HEIGHT, m_fMaxHeight);
	DDX_Text(pDX, IDC_EDIT_MAX_WIDTH, m_fMaxWidth);
	DDX_Text(pDX, IDC_EDIT_MIN_HEIGHT, m_fMinHeight);
	DDX_Text(pDX, IDC_EDIT_MIN_WIDTH, m_fMinWidth);
	DDX_Text(pDX, IDC_EDIT_TIME1_BEGIN_HOUR, m_iHour11);
	DDX_Text(pDX, IDC_EDIT_TIME1_BEGIN_MIN, m_iMin11);
	DDX_Text(pDX, IDC_EDIT_TIME1_END_HOUR, m_iHour12);
	DDX_Text(pDX, IDC_EDIT_TIME1_END_MIN, m_iMin12);
	DDX_Text(pDX, IDC_EDIT_TIME2_BEGIN_HOUR, m_iHour21);
	DDX_Text(pDX, IDC_EDIT_TIME2_BEGIN_MIN, m_iMin21);
	DDX_Text(pDX, IDC_EDIT_TIME2_END_HOUR, m_iHour22);
	DDX_Text(pDX, IDC_EDIT_TIME2_END_MIN, m_iMin22);
	DDX_Text(pDX, IDC_EDIT_TIME3_BEGIN_HOUR, m_iHour31);
	DDX_Text(pDX, IDC_EDIT_TIME3_BEGIN_MIN, m_iMin31);
	DDX_Text(pDX, IDC_EDIT_TIME3_END_HOUR, m_iHour32);
	DDX_Text(pDX, IDC_EDIT_TIME3_END_MIN, m_iMin32);
	DDX_Text(pDX, IDC_EDIT_TIME4_BEGIN_HOUR, m_iHour41);
	DDX_Text(pDX, IDC_EDIT_TIME4_BEGIN_MIN, m_iMin41);
	DDX_Text(pDX, IDC_EDIT_TIME4_END_HOUR, m_iHour42);
	DDX_Text(pDX, IDC_EDIT_TIME4_END_MIN, m_iMin42);
	DDX_Text(pDX, IDC_EDIT_TIME5_BEGIN_HOUR, m_iHour51);
	DDX_Text(pDX, IDC_EDIT_TIME5_BEGIN_MIN, m_iMin51);
	DDX_Text(pDX, IDC_EDIT_TIME5_END_HOUR, m_iHour52);
	DDX_Text(pDX, IDC_EDIT_TIME5_END_MIN, m_iMin52);
	DDX_Text(pDX, IDC_EDIT_TIME6_BEGIN_HOUR, m_iHour61);
	DDX_Text(pDX, IDC_EDIT_TIME6_BEGIN_MIN, m_iMin61);
	DDX_Text(pDX, IDC_EDIT_TIME6_END_HOUR, m_iHour62);
	DDX_Text(pDX, IDC_EDIT_TIME6_END_MIN, m_iMin62);
	DDX_Text(pDX, IDC_EDIT_TIME7_BEGIN_HOUR, m_iHour71);
	DDX_Text(pDX, IDC_EDIT_TIME7_BEGIN_MIN, m_iMin71);
	DDX_Text(pDX, IDC_EDIT_TIME7_END_HOUR, m_iHour72);
	DDX_Text(pDX, IDC_EDIT_TIME7_END_MIN, m_iMin72);
	DDX_Text(pDX, IDC_EDIT_TIME8_BEGIN_HOUR, m_iHour81);
	DDX_Text(pDX, IDC_EDIT_TIME8_BEGIN_MIN, m_iMin81);
	DDX_Text(pDX, IDC_EDIT_TIME8_END_HOUR, m_iHour82);
	DDX_Text(pDX, IDC_EDIT_TIME8_END_MIN, m_iMin82);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTPSRuleCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgTPSRuleCfg)
	ON_BN_CLICKED(IDC_BTN_SET_TPS_RULECFG, OnBtnSetTpsRulecfg)
	ON_CBN_SELCHANGE(IDC_COMBO_TPS_INDEX, OnSelchangeComboTpsIndex)
	ON_CBN_SELCHANGE(IDC_COMBOWEEKDAY, OnSelchangeComboweekday)
	ON_BN_CLICKED(IDC_TIME_OK, OnTimeOk)
	ON_BN_CLICKED(IDC_TIME_COPY, OnTimeCopy)
	ON_BN_CLICKED(IDC_CHECK_DRAW_VIRTUAL_LOOP, OnCheckDrawVirtualLoop)
	ON_BN_CLICKED(IDC_CHECK_FILTER_ACTIVE, OnCheckFilterActive)
	ON_BN_CLICKED(IDC_CHECK_SET_MINI_FILTER, OnCheckSetMiniFilter)
	ON_BN_CLICKED(IDC_CHECK_SET_MAX_FILTER, OnCheckSetMaxFilter)
	ON_CBN_SELCHANGE(IDC_COMBO_FILTER_MODE, OnSelchangeComboFilterMode)
	ON_BN_CLICKED(IDC_BTN_CONFIRM, OnBtnConfirm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTPSRuleCfg message handlers

BOOL CDlgTPSRuleCfg::PreTranslateMessage(MSG* pMsg) 
{
    GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWnd);
    
    CPoint pt(0,0);
    GetCursorPos(&pt);
    
    if (m_bDrawPolygon)
    {
        PreDrawPolygonMsg(pMsg, pt);
    }
    else if (m_bSetMiniFilter || m_bSetMaxFilter)
    {
        PreDrawSizeFilterMsg(pMsg, pt);
    }

	
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CDlgTPSRuleCfg::PreDrawSizeFilterMsg(MSG* pMsg, CPoint &pt)
{
    switch (pMsg->message)
    {
    case WM_LBUTTONDOWN:
        if(m_bSetMiniFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            if(PtInRect(&m_rcWnd,pt))
            {
                m_struTPSRuleCfg.struOneTpsRule[m_iTPSIndex].struSizeFilter.struMiniRect.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                m_struTPSRuleCfg.struOneTpsRule[m_iTPSIndex].struSizeFilter.struMiniRect.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
            }
        }//First coordinate of Maximal Rectangle
        else if(m_bSetMaxFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            if(PtInRect(&m_rcWnd,pt))
            {
                m_struTPSRuleCfg.struOneTpsRule[m_iTPSIndex].struSizeFilter.struMaxRect.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                m_struTPSRuleCfg.struOneTpsRule[m_iTPSIndex].struSizeFilter.struMaxRect.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
            }
        }
        break;
    case WM_MOUSEMOVE:
        if(m_bSetMiniFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)) //尺寸过滤器
        {
            if(PtInRect(&m_rcWnd,pt))
            {
                m_struTPSRuleCfg.struOneTpsRule[m_iTPSIndex].struSizeFilter.struMiniRect.fWidth = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() - m_struTPSRuleCfg.struOneTpsRule[m_iTPSIndex].struSizeFilter.struMiniRect.fX;
                m_struTPSRuleCfg.struOneTpsRule[m_iTPSIndex].struSizeFilter.struMiniRect.fHeight = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() - m_struTPSRuleCfg.struOneTpsRule[m_iTPSIndex].struSizeFilter.struMiniRect.fY;
            }
            
        }
        else if(m_bSetMaxFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)) //尺寸过滤器
        {
            if(PtInRect(&m_rcWnd,pt))
            {	
                m_struTPSRuleCfg.struOneTpsRule[m_iTPSIndex].struSizeFilter.struMaxRect.fWidth = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() - m_struTPSRuleCfg.struOneTpsRule[m_iTPSIndex].struSizeFilter.struMaxRect.fX;
                m_struTPSRuleCfg.struOneTpsRule[m_iTPSIndex].struSizeFilter.struMaxRect.fHeight = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() - m_struTPSRuleCfg.struOneTpsRule[m_iTPSIndex].struSizeFilter.struMaxRect.fY;
            }
        }
        break;
    }
    
    return TRUE;
}

BOOL CDlgTPSRuleCfg::PreDrawPolygonMsg(MSG* pMsg, CPoint &pt)
{
    int i=0;
    BOOL bOneLine = TRUE,bXOneLine = TRUE,bYOneLine = TRUE;

    switch (pMsg->message)
    {
    case WM_LBUTTONDOWN:
        if ((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) && 
            PtInRect(&m_rcWnd,pt))
        {

                if(m_bNeedRedraw[m_iTPSIndex])
                {			
                    if(m_bCloseIn[m_iTPSIndex])
                    {
                        m_dwPosNum = 0;
                        m_struVcaPolygon[m_iTPSIndex].dwPointNum = m_dwPosNum;		
                    }
                    if(m_dwPosNum>9)
                    {
                        char szLan[128] = {0};
                        g_StringLanType(szLan,"多边形顶点不能超过10个!","Apexes of polygon should less than 11");
                        AfxMessageBox(szLan);
                        return TRUE;
                    }
                    if((float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() <= m_struVcaPolygon[m_iTPSIndex].struPos[m_dwPosNum-1].fX+0.01 && (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() >= m_struVcaPolygon[m_iTPSIndex].struPos[m_dwPosNum-1].fX-0.01\
                        && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() <= m_struVcaPolygon[m_iTPSIndex].struPos[m_dwPosNum-1].fY+0.01 && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() >= m_struVcaPolygon[m_iTPSIndex].struPos[m_dwPosNum-1].fY-0.01)
                    {
                        char szLan[128] = {0};
                        g_StringLanType(szLan, "不能连续在同一点上画区域", "Can't draw region on the point used");
                        AfxMessageBox(szLan);
                        return TRUE;
                    }
                    m_bCloseIn[m_iTPSIndex] = FALSE;
                    m_bMouseMove[m_iTPSIndex] = FALSE;
                    m_struVcaPolygon[m_iTPSIndex].struPos[m_dwPosNum].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                    m_struVcaPolygon[m_iTPSIndex].struPos[m_dwPosNum].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
                    m_dwPosNum++;
                    m_struVcaPolygon[m_iTPSIndex].dwPointNum = m_dwPosNum;	
                    
            }
            
        }
        break;
    case WM_MOUSEMOVE:
        if ((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) && 
            PtInRect(&m_rcWnd,pt))
        {
                if(PtInRect(&m_rcWnd,pt))
                {
                    if(m_dwPosNum > 9)
                    {
                        return TRUE;
                    }
                    if( m_bNeedRedraw[m_iTPSIndex] && !m_bCloseIn[m_iTPSIndex])
                    {
                        m_bMouseMove[m_iTPSIndex] = TRUE;
                        m_struVcaPolygon[m_iTPSIndex].struPos[m_dwPosNum].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                        m_struVcaPolygon[m_iTPSIndex].struPos[m_dwPosNum].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
                        m_struVcaPolygon[m_iTPSIndex].dwPointNum = m_dwPosNum+1;				
                    }
                }
        }

        break;
    case WM_RBUTTONDOWN:
        if((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) 
            && PtInRect(&m_rcWnd,pt))
        {
                if(m_dwPosNum > 9)
                {
                    return TRUE;
                }
                for(i=0; i<m_dwPosNum; i++)
                {
                    if(m_struVcaPolygon[m_iTPSIndex].struPos[i].fX != m_struVcaPolygon[m_iTPSIndex].struPos[i+1].fX)
                    {
                        bXOneLine = FALSE;
                        break;
                    }
                }
                for(i=0; i<m_dwPosNum; i++)
                {
                    if(m_struVcaPolygon[m_iTPSIndex].struPos[i].fY != m_struVcaPolygon[m_iTPSIndex].struPos[i+1].fY)
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
                if( m_bNeedRedraw[m_iTPSIndex] && !m_bCloseIn[m_iTPSIndex])
                {
                    if(m_bMouseMove[m_iTPSIndex])
                    {
                        m_bMouseMove[m_iTPSIndex] = FALSE;
                        m_struVcaPolygon[m_iTPSIndex].dwPointNum--;
                        m_struVcaPolygon[m_iTPSIndex].struPos[m_struVcaPolygon[m_iTPSIndex].dwPointNum].fX = 0;
                        m_struVcaPolygon[m_iTPSIndex].struPos[m_struVcaPolygon[m_iTPSIndex].dwPointNum].fY = 0;
                    }
                    m_bCloseIn[m_iTPSIndex] = TRUE;
                }
		}
        break;
    }
    return TRUE;
}

BOOL CDlgTPSRuleCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
    g_pDlgTpsRule = this;
    GetVcaChanAbility();
    InitWnd();
	StartPlay();
    m_dwAlarmOutNum = g_struDeviceInfo[m_iDevIndex].iAlarmOutNum;
    
    if (!GetTPSRuleCfg())
    {
        return FALSE;
    }
    
    GetLaneCfg();

	SetTPSRuleToWnd(m_struTPSRuleCfg);

    UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgTPSRuleCfg::GetVcaChanAbility()
{
    BOOL bRet = FALSE; 
    DWORD dwSceneMode = 0;
    if (!NET_DVR_GetSceneMode(m_lServerID, m_lChannel, &dwSceneMode))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "VCA_CHAN_ABILITY");
       // return FALSE;
    }
    m_struVcaChanInParam.byMode = (BYTE)dwSceneMode;
    m_struVcaChanInParam.byVCAType = VCA_ITS;
    
    if (!NET_DVR_GetDeviceAbility(m_lServerID, VCA_CHAN_ABILITY, (char*)&m_struVcaChanInParam,\
        sizeof(m_struVcaChanInParam), (char*)&m_struItsAbility, sizeof(m_struItsAbility)))
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

BOOL CDlgTPSRuleCfg::GetLaneCfg()
{
    DWORD dwReturn = 0;
    BOOL bRet = FALSE;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_LANECFG, m_lChannel, &m_struLaneCfg, sizeof(m_struLaneCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_LANECFG Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_LANECFG Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}

BOOL CDlgTPSRuleCfg::InitWnd()
{
    for (int i = 0; i < MAX_AID_RULE; i ++)
    {
        m_bNeedRedraw[i] = FALSE;//Redraw polygon
        m_bCloseIn[i] = TRUE;//Polygon is closed or not
    }

    m_comboLaneID.ResetContent();
    m_comboLaneID.AddString("Lane 1");
    m_comboLaneID.AddString("Lane 2");
    m_comboLaneID.AddString("Lane 3");
    m_comboLaneID.AddString("Lane 4");
    m_comboLaneID.AddString("Lane 5");
    m_comboLaneID.AddString("Lane 6");
    m_comboLaneID.AddString("Lane 7");
    m_comboLaneID.AddString("Lane 8");

    char szLan[128] = {0};
    m_listTPSType.DeleteAllItems();
    m_listTPSType.SetExtendedStyle(LVS_EX_CHECKBOXES);
    int index = 0;

    if ((m_struItsAbility.dwAbilityType & ITS_LANE_VOLUME_ABILITY) != 0)
    {
        g_StringLanType(szLan, "车道流量", "Lane volume");
        m_listTPSType.InsertItem(index, szLan);
        m_listTPSType.SetItemData(index, LANE_VOLUME);
        index++;
    }
    
    if ((m_struItsAbility.dwAbilityType & ITS_LANE_VELOCITY_ABILITY) != 0)
    {
        g_StringLanType(szLan, "车道速度", "Lane velocity");
        m_listTPSType.InsertItem(index, szLan);
        m_listTPSType.SetItemData(index, LANE_VELOCITY);
        index++;
    }
    
    if ((m_struItsAbility.dwAbilityType & ITS_TIME_HEADWAY_ABILITY) != 0)
    {
        g_StringLanType(szLan, "车头时距", "Time Headway");
        m_listTPSType.InsertItem(index, szLan);
        m_listTPSType.SetItemData(index, TIME_HEADWAY);
        index++;
    }
    
    if ((m_struItsAbility.dwAbilityType & ITS_SPACE_HEADWAY_ABILITY) != 0)
    {
        g_StringLanType(szLan, "车头间距", "Space headway");
        m_listTPSType.InsertItem(index, szLan);
        m_listTPSType.SetItemData(index, SPACE_HEADWAY);
        index++;
    }
    
    if ((m_struItsAbility.dwAbilityType & ITS_TIME_OCCUPANCY_RATIO_ABILITY) != 0)
    {
        g_StringLanType(szLan, "时间占有率", "Time occupancy ratio");
        m_listTPSType.InsertItem(index, szLan);
        m_listTPSType.SetItemData(index, TIME_OCCUPANCY_RATIO);
        index++;
    }
    
    if ((m_struItsAbility.dwAbilityType & ITS_SPACE_OCCUPANCY_RATIO_ABILITY) != 0)
    {
        g_StringLanType(szLan, "空间占有率", "Space occupancy ratio");
        m_listTPSType.InsertItem(index, szLan);
        m_listTPSType.SetItemData(index, SPACE_OCCUPANCY_RATIO);
        index++;
    }
    
    if ((m_struItsAbility.dwAbilityType & ITS_LANE_QUEUE_ABILITY) != 0)
    {
        g_StringLanType(szLan, "排队长度", "Queue");
        m_listTPSType.InsertItem(index, szLan);
        m_listTPSType.SetItemData(index, QUEUE);
        index++;
    }

	if ((m_struItsAbility.dwAbilityType & ITS_VEHICLE_TYPE_ABILITY) != 0)
    {
		g_StringLanType(szLan, "车辆类型", "Vehicle type");
		m_listTPSType.InsertItem(index, szLan);
		m_listTPSType.SetItemData(index, VEHICLE_TYPE);
		index++;
    }
	
	if ((m_struItsAbility.dwAbilityType & ITS_TRAFFIC_STATE_ABILITY) != 0)
    {
		g_StringLanType(szLan, "交通状态", "Traffic state");
		m_listTPSType.InsertItem(index, szLan);
		m_listTPSType.SetItemData(index,TRAFFIC_STATE);
		index++;
    }
    
    m_comboTPSIndex.SetCurSel(0);
    OnSelchangeComboTpsIndex();

   return TRUE;
}

BOOL CDlgTPSRuleCfg::SetTPSRuleCfg()
{
    BOOL bRet = FALSE;
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_TPS_RULECFG_V41, m_lChannel, &m_struTPSRuleCfg, sizeof(m_struTPSRuleCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_TPS_RULECFG_V41 Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_TPS_RULECFG_V41 Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}

BOOL CDlgTPSRuleCfg::GetTPSRuleCfg()
{
    DWORD dwReturn = 0;
    BOOL bRet = FALSE;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_TPS_RULECFG_V41, m_lChannel, &m_struTPSRuleCfg, sizeof(m_struTPSRuleCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_TPS_RULECFG_V41 Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_TPS_RULECFG_V41 Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}

BOOL CDlgTPSRuleCfg::SetTPSRuleToWnd(NET_DVR_TPS_RULECFG_V41 const &struTpsRule)
{
    SetOneTpsRuleToWnd(struTpsRule.struOneTpsRule[m_iTPSIndex]);
    return TRUE;
}



BOOL CDlgTPSRuleCfg::GetTPSRuleFromWnd(NET_DVR_TPS_RULECFG_V41  &struTpsRule)
{
    GetOneTpsRuleFromWnd(struTpsRule.struOneTpsRule[m_iTPSIndex]);
    return TRUE;
}

BOOL CDlgTPSRuleCfg::SetOneTpsRuleToWnd(NET_DVR_ONE_TPS_RULE_V41 const &struOneTpsRule)
{
    m_bEnable = struOneTpsRule.byEnable;
    for (int i = 0; i < m_listTPSType.GetItemCount(); i++)
    {
        m_listTPSType.SetCheck(i, FALSE);
        
        if ((struOneTpsRule.dwCalcType & m_listTPSType.GetItemData(i)) != 0)
        {
            m_listTPSType.SetCheck(i, TRUE);
        }
    }
    m_comboLaneID.SetCurSel(struOneTpsRule.byLaneID);
    SetSizeFilterToWnd(struOneTpsRule.struSizeFilter);
    SetHandleExceptionToWnd(struOneTpsRule.struHandleType, m_dwAlarmOutNum);
	int nDay = m_comboWeekday.GetCurSel();
    SetAlarmTimeToWnd(&struOneTpsRule.struAlarmTime[0][0], nDay);
    memcpy(&m_struVcaPolygon[m_iTPSIndex], &struOneTpsRule.struVitrualLoop, sizeof(NET_VCA_POLYGON));
    return TRUE;
}

BOOL CDlgTPSRuleCfg::GetOneTpsRuleFromWnd(NET_DVR_ONE_TPS_RULE_V41 &struOneTpsRule)
{
    struOneTpsRule.byEnable = m_bEnable;
    struOneTpsRule.byLaneID = m_comboLaneID.GetCurSel();
    GetHandleExceptionFromWnd(struOneTpsRule.struHandleType);
    GetSizeFilterFromWnd(struOneTpsRule.struSizeFilter);
    struOneTpsRule.dwCalcType = 0;
    for (int i = 0; i < m_listTPSType.GetItemCount(); i++)
    {
        if (m_listTPSType.GetCheck(i))
        {
            struOneTpsRule.dwCalcType += m_listTPSType.GetItemData(i);
        }
    }

    memcpy(&struOneTpsRule.struVitrualLoop, &m_struVcaPolygon[m_iTPSIndex], sizeof(struOneTpsRule.struVitrualLoop));
	GetAlarmTimeFromWnd(&struOneTpsRule.struAlarmTime[0][0], m_comboWeekday.GetCurSel());
   
    return TRUE;
}


BOOL CDlgTPSRuleCfg::SetHandleExceptionToWnd(NET_DVR_HANDLEEXCEPTION_V30 const &struHandleType,int nAlarmNum)
{
    m_bHandleType1 = (struHandleType.dwHandleType) &0x01;
    m_bHandleType2 = (struHandleType.dwHandleType>>1)&0x01;
    m_bHandleType3 = (struHandleType.dwHandleType>>2)&0x01;
    m_bHandleType4 = (struHandleType.dwHandleType>>3)&0x01;
    m_bHandleType5 = (struHandleType.dwHandleType>>4)&0x01;
    
    //m_listAlarmOut.EnableWindow(m_bHandleType4);
    
    m_listAlarmOut.DeleteAllItems();
    m_listAlarmOut.SetExtendedStyle(LVS_EX_CHECKBOXES);
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
        if (struHandleType.byRelAlarmOut[i])
        {
            m_listAlarmOut.SetCheck(i);
        }
    }
    return TRUE;
}

BOOL CDlgTPSRuleCfg::GetHandleExceptionFromWnd(NET_DVR_HANDLEEXCEPTION_V30 &struHandleType)
{
    
    UpdateData(TRUE);
    struHandleType.dwHandleType = 0;
    struHandleType.dwHandleType |= (m_bHandleType1 << 0);
    struHandleType.dwHandleType |= (m_bHandleType2 << 1);
    struHandleType.dwHandleType |= (m_bHandleType3 << 2);
    struHandleType.dwHandleType |= (m_bHandleType4 << 3);
    struHandleType.dwHandleType |= (m_bHandleType5 << 4);
    
    for (DWORD i = 0; i < m_dwAlarmOutNum; i++)
    {
        struHandleType.byRelAlarmOut[i] = (BYTE)m_listAlarmOut.GetCheck(i);
    }
    UpdateData(FALSE);
    return TRUE;
}


void CDlgTPSRuleCfg::OnBtnSetTpsRulecfg() 
{
    UpdateData(TRUE);
    GetTPSRuleFromWnd(m_struTPSRuleCfg);
	if (!SetTPSRuleCfg())
    {
        AfxMessageBox("Fail to set TPS rule config");
    }
}

void CDlgTPSRuleCfg::OnSelchangeComboTpsIndex() 
{
	m_iTPSIndex = m_comboTPSIndex.GetCurSel();
    m_bNeedRedraw[m_iTPSIndex] = TRUE;
    SetTPSRuleToWnd(m_struTPSRuleCfg);
    
    UpdateData(FALSE);
}

void CDlgTPSRuleCfg::OnSelchangeComboweekday() 
{
	int	i = m_comboWeekday.GetCurSel();	
    SetAlarmTimeToWnd(&m_struTPSRuleCfg.struOneTpsRule[m_iTPSIndex].struAlarmTime[0][0], i);
    UpdateData(FALSE);
}

void CDlgTPSRuleCfg::OnTimeOk() 
{
	UpdateData(TRUE);
    if (!F_TimeTest())
    {
        return;
    }
    int	i = m_comboWeekday.GetCurSel();	
    GetAlarmTimeFromWnd(&m_struTPSRuleCfg.struOneTpsRule[m_iTPSIndex].struAlarmTime[0][0], i);
}	

void CDlgTPSRuleCfg::OnTimeCopy() 
{
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
                memcpy(&(m_struTPSRuleCfg.struOneTpsRule[m_iTPSIndex].struAlarmTime[j][k]), &(m_struTPSRuleCfg.struOneTpsRule[m_iTPSIndex].struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
            }
        }
    }
    else
    {
        for(k=0; k<MAX_TIMESEGMENT_V30; k++)
        {
            memcpy(&(m_struTPSRuleCfg.struOneTpsRule[m_iTPSIndex].struAlarmTime[m_nCopyTime][k]), &(m_struTPSRuleCfg.struOneTpsRule[m_iTPSIndex].struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
        }
    }
}


BOOL CDlgTPSRuleCfg::F_TimeTest()
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


LONG CDlgTPSRuleCfg::StartPlay()
{
    if (GetPuStreamCfg(m_struPUStream))
    {
        NET_DVR_DEVICEINFO_V30 struDeviceInfo = {0};
        
        m_lPUServerID = NET_DVR_Login_V30(m_struPUStream.struDevChanInfo.struIP.sIpV4, m_struPUStream.struDevChanInfo.wDVRPort,
            (char*)m_struPUStream.struDevChanInfo.sUserName, (char*)m_struPUStream.struDevChanInfo.sPassword, &struDeviceInfo);
        if (m_lPUServerID < 0)
        {
            AfxMessageBox("Fail to login front device");
            return m_lPUServerID;
        }
        
        NET_DVR_CLIENTINFO struPlay;
        struPlay.hPlayWnd 	= GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
        struPlay.lChannel 	= m_struPUStream.struDevChanInfo.byChannel; 
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
            bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, g_DrawTpsRule, 0);//DC Draw callback
        }
        return m_lPlayHandle;
    }
    else
    {
    NET_DVR_CLIENTINFO struPlay;
    struPlay.hPlayWnd 	= GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
    struPlay.lChannel 	= m_lChannel; 
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
        bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, g_DrawTpsRule, 0);//DC Draw callback
    }
    return m_lPlayHandle;
}
}

BOOL CDlgTPSRuleCfg::StopPlay()
{
    if (m_lPlayHandle >= 0)
    {
        NET_DVR_StopRealPlay(m_lPlayHandle);
        m_lPlayHandle = -1;
    }
    if (m_lPUServerID)
    {
        NET_DVR_Logout(m_lPUServerID);
    }
    return TRUE;
}

void CDlgTPSRuleCfg::PostNcDestroy() 
{
    StopPlay();
    g_pDlgTpsRule = NULL;
	CDialog::PostNcDestroy();
}

void CDlgTPSRuleCfg::F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser)
{
    DRAW_POLYGON_PARAM struDrawPolygon;
    memset(&struDrawPolygon, 0, sizeof(struDrawPolygon));
    struDrawPolygon.color = RGB(255, 255, 0);
    memcpy(&struDrawPolygon.rcWnd, &m_rcWnd, sizeof(struDrawPolygon.rcWnd));
    memcpy(&struDrawPolygon.struVcaPolygon, &m_struVcaPolygon[m_iTPSIndex], sizeof(struDrawPolygon.struVcaPolygon));
    struDrawPolygon.bCloseIn = m_bCloseIn[m_iTPSIndex];
    struDrawPolygon.bMouseMove = m_bMouseMove[m_iTPSIndex];
    CDrawFun::DrawVcaPolygon(hDc, &struDrawPolygon);

    if (m_bFilterActive)
    {
        DRAW_RECT_PARAM struDrawRect;
        memset(&struDrawRect, 0, sizeof(struDrawRect));
        struDrawRect.color = RGB(0, 255, 125);
        memcpy(&struDrawRect.rcWnd, &m_rcWnd, sizeof(struDrawRect.rcWnd));
        memcpy(&struDrawRect.struVcaRect, &m_struTPSRuleCfg.struOneTpsRule[m_iTPSIndex].struSizeFilter.struMaxRect, sizeof(struDrawRect.struVcaRect));
        CDrawFun::DrawVcaRect(hDc, &struDrawRect);
        
        memset(&struDrawRect, 0, sizeof(struDrawRect));
        struDrawRect.color = RGB(0, 255, 125);
        memcpy(&struDrawRect.rcWnd, &m_rcWnd, sizeof(struDrawRect.rcWnd));
        memcpy(&struDrawRect.struVcaRect, &m_struTPSRuleCfg.struOneTpsRule[m_iTPSIndex].struSizeFilter.struMiniRect, sizeof(struDrawRect.struVcaRect));
        CDrawFun::DrawVcaRect(hDc, &struDrawRect);
    }

    DrawLane(hDc);
}

void CDlgTPSRuleCfg::DrawLane(HDC hDc)
{
    DRAW_POLYGON_PARAM struPolygonParam;
    memset(&struPolygonParam, 0, sizeof(struPolygonParam));
    
    DRAW_DIRECTION_PARAM struDirectionParam;
    memset(&struPolygonParam, 0, sizeof(struPolygonParam));

    for (int i = 0; i < MAX_LANE_NUM; i++)
    {
        struPolygonParam.color = RGB(255,255,0);
        struDirectionParam.color = RGB(255,255,0);

        struPolygonParam.bCloseIn = TRUE;
        struPolygonParam.bMouseMove = FALSE;
        memcpy(&struPolygonParam.rcWnd, &m_rcWnd, sizeof(m_rcWnd));
        memcpy(&struPolygonParam.struVcaPolygon, &m_struLaneCfg.struLane[i].struPolygon, sizeof(struPolygonParam.struVcaPolygon));
        strncpy(struPolygonParam.chName, (char*)m_struLaneCfg.struLane[i].byLaneName, sizeof(struPolygonParam.chName));
        CDrawFun::DrawVcaPolygon(hDc, &struPolygonParam);
        
        memcpy(&struDirectionParam.rcWnd, &m_rcWnd, sizeof(struDirectionParam.rcWnd));
        memcpy(&struDirectionParam.struDirection, &m_struLaneCfg.struLane[i].struFlowDirection, sizeof(struDirectionParam.struDirection));
        CDrawFun::DrawDirection(hDc, &struDirectionParam);
    }
}

void CDlgTPSRuleCfg::OnCheckDrawVirtualLoop() 
{
    UpdateData(TRUE);	
}

void CDlgTPSRuleCfg::OnCheckFilterActive() 
{
    
    UpdateData(TRUE);
    GetDlgItem(IDC_CHECK_SET_MAX_FILTER)->EnableWindow(m_bFilterActive);
    GetDlgItem(IDC_CHECK_SET_MINI_FILTER)->EnableWindow(m_bFilterActive);
	
}

void CDlgTPSRuleCfg::OnCheckSetMiniFilter() 
{
    UpdateData(TRUE);
    if (m_bSetMiniFilter)
    {
        m_bSetMaxFilter = FALSE;
        m_bDrawPolygon = FALSE;
        UpdateData(FALSE);
    }
}

void CDlgTPSRuleCfg::OnCheckSetMaxFilter() 
{
    UpdateData(TRUE);
    if (m_bSetMaxFilter)
    {
        m_bSetMiniFilter = FALSE;
        m_bDrawPolygon = FALSE;
        UpdateData(FALSE);
	}
}

void CDlgTPSRuleCfg::OnSelchangeComboFilterMode() 
{
    BYTE byMode = m_comboFilterMode.GetCurSel();
    EnableFilterModeWnd(byMode);
    UpdateData(FALSE);

}

void CDlgTPSRuleCfg::SetSizeFilterToWnd(const NET_VCA_SIZE_FILTER &struSizeFilter)
{
    m_bFilterActive = struSizeFilter.byActive;
    
    m_comboFilterMode.SetCurSel(struSizeFilter.byMode);
    EnableFilterModeWnd(struSizeFilter.byMode);
    m_fMinHeight = struSizeFilter.struMiniRect.fHeight;
    m_fMinWidth = struSizeFilter.struMiniRect.fWidth;
    m_fMaxHeight = struSizeFilter.struMaxRect.fHeight;
    m_fMaxWidth = struSizeFilter.struMaxRect.fWidth;
}

void CDlgTPSRuleCfg::EnableFilterModeWnd(BYTE byMode)
{
    BOOL bEnable = FALSE;
    if (IMAGE_PIX_MODE == byMode)
    {
        bEnable = FALSE;
    }
    else if (REAL_WORLD_MODE == byMode)
    {
        bEnable = TRUE;
    }
    
    GetDlgItem(IDC_EDIT_MIN_WIDTH)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_MIN_HEIGHT)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_MAX_WIDTH)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_MAX_HEIGHT)->EnableWindow(bEnable);
}


void CDlgTPSRuleCfg::GetSizeFilterFromWnd(NET_VCA_SIZE_FILTER &struSizeFilter)
{
    struSizeFilter.byActive = m_bFilterActive;
    struSizeFilter.byMode = m_comboFilterMode.GetCurSel();
    if (REAL_WORLD_MODE == struSizeFilter.byMode)
    {
        struSizeFilter.struMiniRect.fHeight = m_fMinHeight;
        struSizeFilter.struMiniRect.fWidth = m_fMinWidth;
        struSizeFilter.struMaxRect.fHeight = m_fMaxHeight;
        struSizeFilter.struMaxRect.fWidth = m_fMaxWidth;
    }
}


void CDlgTPSRuleCfg::OnBtnConfirm() 
{
	
}

BOOL CDlgTPSRuleCfg::GetPuStreamCfg(NET_DVR_PU_STREAM_CFG &struPUStream)
{
    DWORD dwReturn = 0; 
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_PU_STREAMCFG, m_lChannel, &struPUStream, sizeof(struPUStream), &dwReturn))
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



void CDlgTPSRuleCfg::SetAlarmTimeToWnd(NET_DVR_SCHEDTIME const *pAlarmTime, int nDay)
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

void CDlgTPSRuleCfg::GetAlarmTimeFromWnd(NET_DVR_SCHEDTIME *pAlarmTime, int nDay)
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