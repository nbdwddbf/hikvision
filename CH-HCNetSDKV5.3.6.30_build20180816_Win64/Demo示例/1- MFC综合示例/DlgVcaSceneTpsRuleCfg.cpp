// DlgVcaSceneTpsRuleCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaSceneTpsRuleCfg.h"
#include "DrawFun.h"
#include "DlgVcaAlarmTimeCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSceneTpsRuleCfg dialog


#define MAX_RULEPOLYGON_POINT_NUM 10
#define MIN_RULEPOLYGON_POINT_NUM 4
/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSceneTpsRuleCfg dialog
void CALLBACK g_DrawSceneTpsRule(LONG lRealHandle, HDC hDc, DWORD dwUser)
{   
	CDlgVcaSceneTpsRuleCfg* pDlgTpsRuleCfg = (CDlgVcaSceneTpsRuleCfg*)(dwUser);
	if (pDlgTpsRuleCfg != NULL)
	{
		pDlgTpsRuleCfg->DrawTpsRuleFun(hDc);
	}
}


CDlgVcaSceneTpsRuleCfg::CDlgVcaSceneTpsRuleCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaSceneTpsRuleCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaSceneTpsRuleCfg)
	m_bRuleActive = FALSE;
	m_bHandleType_EmailJpg = FALSE;
	m_bHandleType_Monitor = FALSE;
	m_bHandleType_Output = FALSE;
	m_bHandleType_Sound = FALSE;
	m_bHandleType_Upload = FALSE;
	m_bSizeFilterEnable = FALSE;
	m_nMaxRectHeight = 0;
	m_nMaxRectWidth = 0;
	m_nMinRectHeight = 0;
	m_nMinRectWidth = 0;
	//}}AFX_DATA_INIT

	memset(&m_struItsAbility,    0,sizeof(m_struItsAbility));
	memset(&m_struTPSRuleCfg,    0,sizeof(m_struTPSRuleCfg));
	memset(&m_struCurRulePolygon,0,sizeof(m_struCurRulePolygon));
	memset(&m_struMinRect,       0,sizeof(m_struMinRect));
	memset(&m_struMaxRect,       0,sizeof(m_struMaxRect));
	memset(&m_struSceneCfg,      0,sizeof(m_struSceneCfg));
	memset(m_struSceneLaneCfg,   0,sizeof(m_struSceneLaneCfg));
	m_nCurSceneIndex       =     0;
	m_nCurRuleIndex        =     0;
	m_nCurDrawType         =     DRAW_TYPE_NONE;
	m_bFirstDrawMaxRect    =     FALSE;
	m_bFirstDrawMinRect    =     FALSE;
	m_nSizeFilterMode      =     0;
	m_nCurLaneIndex        =     0;
	m_nDrawPointNum        =     0;
	
}


void CDlgVcaSceneTpsRuleCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaSceneTpsRuleCfg)
	DDX_Control(pDX, IDC_LIST_ALARMOUTPUT_CHAN, m_listAlarmOutputChan);
	DDX_Control(pDX, IDC_LIST_AIDTYPE, m_listTPSType);
	DDX_Control(pDX, IDC_COMBO_SIZEFILTER_MODE, m_comboSizeFilterMode);
	DDX_Control(pDX, IDC_COMBO_SCENE, m_comboScene);
	DDX_Control(pDX, IDC_COMBO_RULEINDEX, m_comboRule);
	DDX_Control(pDX, IDC_COMBO_LANE, m_comboLane);
	DDX_Check(pDX, IDC_CHECK_RULEACTIVE, m_bRuleActive);
	DDX_Check(pDX, IDC_CHECK_HANDLETYPE_JPG, m_bHandleType_EmailJpg);
	DDX_Check(pDX, IDC_CHECK_HANDLETYPE_MONITOR, m_bHandleType_Monitor);
	DDX_Check(pDX, IDC_CHECK_HANDLETYPE_OUTPUT, m_bHandleType_Output);
	DDX_Check(pDX, IDC_CHECK_HANDLETYPE_SOUND, m_bHandleType_Sound);
	DDX_Check(pDX, IDC_CHECK_HANDLETYPE_UPLOAD, m_bHandleType_Upload);
	DDX_Check(pDX, IDC_CHECK_SIZEFILTER_ENABLE, m_bSizeFilterEnable);
	DDX_Text(pDX, IDC_EDIT_MAXRECT_HEIGHT, m_nMaxRectHeight);
	DDX_Text(pDX, IDC_EDIT_MAXRECT_WIDTH, m_nMaxRectWidth);
	DDX_Text(pDX, IDC_EDIT_MINRECT_HEIGHT, m_nMinRectHeight);
	DDX_Text(pDX, IDC_EDIT_MINRECT_WIDTH, m_nMinRectWidth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaSceneTpsRuleCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaSceneTpsRuleCfg)
	ON_BN_CLICKED(IDC_BTN_DRAW_MAXRECT, OnBtnDrawMaxrect)
	ON_BN_CLICKED(IDC_BTN_DRAW_MINRECT, OnBtnDrawMinrect)
	ON_BN_CLICKED(IDC_BTN_DRAW_RULE, OnBtnDrawRule)
	ON_BN_CLICKED(IDC_BTN_STOPDRAW, OnBtnStopdraw)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_SET_ALARMTIME, OnBtnSetAlarmtime)
	ON_BN_CLICKED(IDC_CHECK_SIZEFILTER_ENABLE, OnCheckSizefilterEnable)
	ON_CBN_SELCHANGE(IDC_COMBO_LANE, OnSelchangeComboLane)
	ON_CBN_SELCHANGE(IDC_COMBO_RULEINDEX, OnSelchangeComboRuleindex)
	ON_CBN_SELCHANGE(IDC_COMBO_SCENE, OnSelchangeComboScene)
	ON_CBN_SELCHANGE(IDC_COMBO_SIZEFILTER_MODE, OnSelchangeComboSizefilterMode)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSceneTpsRuleCfg message handlers
BOOL CDlgVcaSceneTpsRuleCfg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (!GetSceneCfg(m_struSceneCfg))
	{   
		char szError[64] = "\0";
		g_StringLanType(szError, "获取场景配置信息失败", "Get Scene cfg failed!");
		AfxMessageBox(szError);
	}
     
	GetVcaChanAbility();
	InitCtrlState();

	GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcPlayWnd);
	ScreenToClient(&m_rcPlayWnd);

	StartRealPlay(GetDlgItem(IDC_PLAYWND)->GetSafeHwnd(),g_DrawSceneTpsRule,this);

	LoadWndSceneContent(m_nCurSceneIndex);

	return TRUE;
}

void CDlgVcaSceneTpsRuleCfg::OnDestroy()
{
	StopRealPlay();
	CDialog::OnDestroy();
}

void CDlgVcaSceneTpsRuleCfg::OnBtnDrawMaxrect() 
{
	memset(&m_struMaxRect[m_nCurRuleIndex],0,sizeof(m_struMaxRect[m_nCurRuleIndex]));
	m_nCurDrawType = DRAW_TYPE_MAXRECT;
	m_bFirstDrawMaxRect = TRUE;
}

void CDlgVcaSceneTpsRuleCfg::OnBtnDrawMinrect() 
{
	memset(&m_struMinRect[m_nCurRuleIndex],0,sizeof(m_struMinRect[m_nCurRuleIndex]));
	m_nCurDrawType = DRAW_TYPE_MINRECT;
	m_bFirstDrawMinRect = TRUE;
}

void CDlgVcaSceneTpsRuleCfg::OnBtnDrawRule() 
{
	memset(&m_struCurRulePolygon,0,sizeof(m_struCurRulePolygon));
	m_nCurDrawType  = DRAW_TYPE_RULE;
	m_nDrawPointNum = 0;
}

void CDlgVcaSceneTpsRuleCfg::OnBtnStopdraw() 
{
	m_bFirstDrawMaxRect = FALSE;
	m_bFirstDrawMinRect = FALSE;
	m_nCurDrawType = DRAW_TYPE_NONE;
	EnableSetParams(TRUE);
	m_struCurRulePolygon.dwPointNum = m_nDrawPointNum;
	
}

void CDlgVcaSceneTpsRuleCfg::OnBtnSave() 
{
	SaveWndSceneContent(m_nCurSceneIndex);
    
	char szError[32] = "\0";
	if (SetTPSRuleCfg())
	{   
    	g_StringLanType(szError, "保存成功","Saved successfully");
	}
	else
	{
		g_StringLanType(szError, "保存失败","Save failed");
	}
	AfxMessageBox(szError);
}

void CDlgVcaSceneTpsRuleCfg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDown(nFlags,point);
	
	if (!m_rcPlayWnd.PtInRect(point))
	{
		return;
	}
	if (m_nCurDrawType == DRAW_TYPE_NONE)
	{
		return;
	}
	
	if (m_nCurDrawType == DRAW_TYPE_RULE)
	{
		if (m_nDrawPointNum >= MAX_RULEPOLYGON_POINT_NUM)
		{
			m_nCurDrawType = DRAW_TYPE_NONE;
		}
		else
		{
			m_struCurRulePolygon.struPos[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
			m_struCurRulePolygon.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
			
			m_nDrawPointNum++;
		}
	}
	else if (m_nCurDrawType == DRAW_TYPE_MAXRECT)
	{   
		if (m_bFirstDrawMaxRect)
		{
			m_struMaxRect[m_nCurSceneIndex][m_nCurRuleIndex].fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
            m_struMaxRect[m_nCurSceneIndex][m_nCurRuleIndex].fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
			m_bFirstDrawMaxRect = FALSE;
		}
		else
		{   
			m_struMaxRect[m_nCurSceneIndex][m_nCurRuleIndex].fWidth  = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width() - m_struMaxRect[m_nCurSceneIndex][m_nCurRuleIndex].fX;
            m_struMaxRect[m_nCurSceneIndex][m_nCurRuleIndex].fHeight = (float)(point.y-m_rcPlayWnd.top)/(float)m_rcPlayWnd.Height() - m_struMaxRect[m_nCurSceneIndex][m_nCurRuleIndex].fY;
			m_nCurDrawType = DRAW_TYPE_NONE;
		}
	}
	else if (m_nCurDrawType == DRAW_TYPE_MINRECT)
	{  
		if (m_bFirstDrawMinRect)
		{
			m_struMinRect[m_nCurSceneIndex][m_nCurRuleIndex].fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
            m_struMinRect[m_nCurSceneIndex][m_nCurRuleIndex].fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
			m_bFirstDrawMinRect = FALSE;
		}
		else
		{   
			m_struMinRect[m_nCurSceneIndex][m_nCurRuleIndex].fWidth  = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width() - m_struMinRect[m_nCurSceneIndex][m_nCurRuleIndex].fX;
            m_struMinRect[m_nCurSceneIndex][m_nCurRuleIndex].fHeight = (float)(point.y-m_rcPlayWnd.top)/(float)m_rcPlayWnd.Height() - m_struMinRect[m_nCurSceneIndex][m_nCurRuleIndex].fY;
			m_nCurDrawType = DRAW_TYPE_NONE;
		}
	}
	
	EnableSetParams(m_nCurDrawType == DRAW_TYPE_NONE);
}

void CDlgVcaSceneTpsRuleCfg::OnMouseMove(UINT nFlags, CPoint point)
{
	CDialog::OnMouseMove(nFlags,point);
	
	if (!m_rcPlayWnd.PtInRect(point))
	{
		return;
	}
	if (m_nCurDrawType == DRAW_TYPE_NONE)
	{
		return;
	}
	
	if (m_nCurDrawType == DRAW_TYPE_RULE)
	{
		if (m_nDrawPointNum >= MAX_RULEPOLYGON_POINT_NUM || m_nDrawPointNum < 1)
		{
			return;
		}
		m_struCurRulePolygon.struPos[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
		m_struCurRulePolygon.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
	    m_struCurRulePolygon.dwPointNum = m_nDrawPointNum + 1;
	}
	else if (m_nCurDrawType == DRAW_TYPE_MAXRECT)
	{   
		if (!m_bFirstDrawMaxRect)
		{
			m_struMaxRect[m_nCurSceneIndex][m_nCurRuleIndex].fWidth  = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width() - m_struMaxRect[m_nCurSceneIndex][m_nCurRuleIndex].fX;
            m_struMaxRect[m_nCurSceneIndex][m_nCurRuleIndex].fHeight = (float)(point.y-m_rcPlayWnd.top)/(float)m_rcPlayWnd.Height() - m_struMaxRect[m_nCurSceneIndex][m_nCurRuleIndex].fY;
            
			if (m_nSizeFilterMode == IMAGE_PIX_MODE)
			{
				SetDlgItemInt(IDC_EDIT_MAXRECT_WIDTH,m_struMaxRect[m_nCurSceneIndex][m_nCurRuleIndex].fWidth * m_rcPlayWnd.Width());
				SetDlgItemInt(IDC_EDIT_MAXRECT_HEIGHT,m_struMaxRect[m_nCurSceneIndex][m_nCurRuleIndex].fHeight * m_rcPlayWnd.Height());
			}
		}
		
	}
	else if (m_nCurDrawType == DRAW_TYPE_MINRECT)
	{   
		if (!m_bFirstDrawMinRect)
		{
			m_struMinRect[m_nCurSceneIndex][m_nCurRuleIndex].fWidth  = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width() - m_struMinRect[m_nCurSceneIndex][m_nCurRuleIndex].fX;
            m_struMinRect[m_nCurSceneIndex][m_nCurRuleIndex].fHeight = (float)(point.y-m_rcPlayWnd.top)/(float)m_rcPlayWnd.Height() - m_struMinRect[m_nCurSceneIndex][m_nCurRuleIndex].fY;
            
			if (m_nSizeFilterMode == IMAGE_PIX_MODE)
			{
				SetDlgItemInt(IDC_EDIT_MINRECT_WIDTH, m_struMinRect[m_nCurSceneIndex][m_nCurRuleIndex].fWidth  * m_rcPlayWnd.Width());
				SetDlgItemInt(IDC_EDIT_MINRECT_HEIGHT,m_struMinRect[m_nCurSceneIndex][m_nCurRuleIndex].fHeight * m_rcPlayWnd.Height());
			}
		}
	}
}

void CDlgVcaSceneTpsRuleCfg::OnRButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnRButtonDown(nFlags,point);
	
	if (!m_rcPlayWnd.PtInRect(point))
	{
		return;
	}
	if (m_nCurDrawType == DRAW_TYPE_NONE)
	{
		return;
	}
	
	if (m_nCurDrawType == DRAW_TYPE_RULE)
	{
		if (m_nDrawPointNum < MIN_RULEPOLYGON_POINT_NUM)
		{
			memset(&m_struCurRulePolygon,0,sizeof(m_struCurRulePolygon));
		}
		else
		{   
			m_struCurRulePolygon.dwPointNum = m_nDrawPointNum;
		}
		
		m_nCurDrawType = DRAW_TYPE_NONE;
	}
	else if (m_nCurDrawType == DRAW_TYPE_MAXRECT)
	{   
		m_bFirstDrawMaxRect = FALSE;
		m_nCurDrawType = DRAW_TYPE_NONE;
	}
	else if (m_nCurDrawType == DRAW_TYPE_MINRECT)
	{   
		m_bFirstDrawMinRect = FALSE;
		m_nCurDrawType = DRAW_TYPE_NONE;
	}
	EnableSetParams(m_nCurDrawType == DRAW_TYPE_NONE);
}


void CDlgVcaSceneTpsRuleCfg::OnBtnSetAlarmtime() 
{
	CDlgVcaAlarmTimeCfg dlg;
	dlg.InitAlarmTimeCfg(m_struTPSRuleCfg[m_nCurSceneIndex].struOneTpsRule[m_nCurRuleIndex].struAlarmTime);
	if (dlg.DoModal() == IDOK)
	{
		dlg.GetAlarmTimeCfg(m_struTPSRuleCfg[m_nCurSceneIndex].struOneTpsRule[m_nCurRuleIndex].struAlarmTime);
	}
	
}

void CDlgVcaSceneTpsRuleCfg::OnCheckSizefilterEnable() 
{
	UpdateData(TRUE);
	
	m_comboSizeFilterMode.EnableWindow(m_bSizeFilterEnable);
	GetDlgItem(IDC_EDIT_MAXRECT_WIDTH)->EnableWindow(m_bSizeFilterEnable  && m_nSizeFilterMode == REAL_WORLD_MODE);
	GetDlgItem(IDC_EDIT_MAXRECT_HEIGHT)->EnableWindow(m_bSizeFilterEnable && m_nSizeFilterMode == REAL_WORLD_MODE);
	GetDlgItem(IDC_EDIT_MINRECT_WIDTH)->EnableWindow(m_bSizeFilterEnable  && m_nSizeFilterMode == REAL_WORLD_MODE);
	GetDlgItem(IDC_EDIT_MINRECT_HEIGHT)->EnableWindow(m_bSizeFilterEnable && m_nSizeFilterMode == REAL_WORLD_MODE);
	GetDlgItem(IDC_BTN_DRAW_MAXRECT)->EnableWindow(m_bSizeFilterEnable && m_nSizeFilterMode == IMAGE_PIX_MODE);
	GetDlgItem(IDC_BTN_DRAW_MINRECT)->EnableWindow(m_bSizeFilterEnable && m_nSizeFilterMode == IMAGE_PIX_MODE);
	
}

void CDlgVcaSceneTpsRuleCfg::OnSelchangeComboLane() 
{
	int nCurSelIndex = m_comboLane.GetCurSel();
	if (nCurSelIndex != CB_ERR)
	{
		m_nCurLaneIndex = nCurSelIndex;
	}
}

void CDlgVcaSceneTpsRuleCfg::OnSelchangeComboRuleindex() 
{
	int nSelRuleIndex = m_comboRule.GetCurSel();
	if (nSelRuleIndex != CB_ERR)
	{
		SaveWndRuleContent(m_nCurSceneIndex,m_nCurRuleIndex);
		
		m_nCurRuleIndex = nSelRuleIndex;
		
		LoadWndRuleContent(m_nCurSceneIndex,nSelRuleIndex);
	}
	
}

void CDlgVcaSceneTpsRuleCfg::OnSelchangeComboScene() 
{
	int nCusrSceneIndex = m_comboScene.GetCurSel();
	if (nCusrSceneIndex != CB_ERR)
	{  
		SaveWndSceneContent(m_nCurSceneIndex);

		m_nCurSceneIndex = nCusrSceneIndex;
		
		LoadWndSceneContent(nCusrSceneIndex);
	}
}

void CDlgVcaSceneTpsRuleCfg::OnSelchangeComboSizefilterMode() 
{
	int nCurSel = m_comboSizeFilterMode.GetCurSel();
	if (nCurSel != CB_ERR)
	{   
		m_nSizeFilterMode = m_comboSizeFilterMode.GetItemData(nCurSel);
		
		GetDlgItem(IDC_EDIT_MAXRECT_WIDTH)->EnableWindow(m_nSizeFilterMode == REAL_WORLD_MODE);
		GetDlgItem(IDC_EDIT_MAXRECT_HEIGHT)->EnableWindow(m_nSizeFilterMode == REAL_WORLD_MODE);
		GetDlgItem(IDC_EDIT_MINRECT_WIDTH)->EnableWindow(m_nSizeFilterMode == REAL_WORLD_MODE);
		GetDlgItem(IDC_EDIT_MINRECT_HEIGHT)->EnableWindow(m_nSizeFilterMode == REAL_WORLD_MODE);
		GetDlgItem(IDC_BTN_DRAW_MINRECT)->EnableWindow(m_nSizeFilterMode == IMAGE_PIX_MODE);
		GetDlgItem(IDC_BTN_DRAW_MAXRECT)->EnableWindow(m_nSizeFilterMode == IMAGE_PIX_MODE);
	}
}

void CDlgVcaSceneTpsRuleCfg::DrawTpsRuleFun(HDC hdc)
{
	DRAW_POLYGON_PARAM struDrawPolygon;
    memset(&struDrawPolygon, 0, sizeof(struDrawPolygon));
    struDrawPolygon.color = RGB(255, 0, 0);
    memcpy(&struDrawPolygon.rcWnd, &m_rcPlayWnd, sizeof(struDrawPolygon.rcWnd));
    memcpy(&struDrawPolygon.struVcaPolygon, &m_struCurRulePolygon, sizeof(struDrawPolygon.struVcaPolygon));
    struDrawPolygon.bCloseIn = m_nCurDrawType != DRAW_TYPE_RULE;
    struDrawPolygon.bMouseMove = FALSE;
    CDrawFun::DrawVcaPolygon(hdc, &struDrawPolygon);
	
	if (m_bSizeFilterEnable && m_nSizeFilterMode == IMAGE_PIX_MODE)
	{
		DRAW_RECT_PARAM struDrawRect;
		if (!m_bFirstDrawMaxRect)
		{
			memset(&struDrawRect, 0, sizeof(struDrawRect));
			struDrawRect.color = RGB(0, 255, 125);
			memcpy(&struDrawRect.rcWnd, &m_rcPlayWnd, sizeof(struDrawRect.rcWnd));
			memcpy(&struDrawRect.struVcaRect, &m_struMaxRect[m_nCurSceneIndex][m_nCurRuleIndex], sizeof(struDrawRect.struVcaRect));
			CDrawFun::DrawVcaRect(hdc, &struDrawRect);
		}
		
		if (!m_bFirstDrawMinRect)
		{
			memset(&struDrawRect, 0, sizeof(struDrawRect));
			struDrawRect.color = RGB(0, 255, 125);
			memcpy(&struDrawRect.rcWnd, &m_rcPlayWnd, sizeof(struDrawRect.rcWnd));
			memcpy(&struDrawRect.struVcaRect, &m_struMinRect[m_nCurSceneIndex][m_nCurRuleIndex], sizeof(struDrawRect.struVcaRect));
			CDrawFun::DrawVcaRect(hdc, &struDrawRect);
	}
	}
    
	DRAW_POLYGON_PARAM struLanePolygon;
	memset(&struLanePolygon, 0, sizeof(struLanePolygon));
	
	DRAW_DIRECTION_PARAM struDirectionParam;
	memset(&struDirectionParam, 0, sizeof(struDirectionParam));
	
	for (int i = 0; i < MAX_LANE_NUM; i++)
	{   
		struLanePolygon.bCloseIn = TRUE;
		struLanePolygon.color = RGB(255, 255, 0);
		struDirectionParam.color = RGB(255,255,0);
		struLanePolygon.bMouseMove = FALSE;
		memcpy(&struLanePolygon.rcWnd, &m_rcPlayWnd, sizeof(m_rcPlayWnd));
		memcpy(&struLanePolygon.struVcaPolygon, &m_struSceneLaneCfg[m_nCurSceneIndex].struLane[i].struPolygon, sizeof(struLanePolygon.struVcaPolygon));
		strncpy(struLanePolygon.chName, (char*)m_struSceneLaneCfg[m_nCurSceneIndex].struLane[i].byLaneName, sizeof(struLanePolygon.chName));
		CDrawFun::DrawVcaPolygon(hdc, &struLanePolygon);
		
		memcpy(&struDirectionParam.rcWnd, &m_rcPlayWnd, sizeof(struDirectionParam.rcWnd));
		memcpy(&struDirectionParam.struDirection, &m_struSceneLaneCfg[m_nCurSceneIndex].struLane[i].struFlowDirection, sizeof(struDirectionParam.struDirection));
		CDrawFun::DrawDirection(hdc, &struDirectionParam);
	}
}

void CDlgVcaSceneTpsRuleCfg::InitCtrlState()
{   
	char szLan[128]  = {0};
	char sbufCn[128] = {0};
    char sbufEn[128] = {0};
    int i = 0;
	
	CString strItemText = _T("");
	for (i = 0; i < MAX_RULE_NUM; i++)
	{
		strItemText.Format(_T("Rule %d"), i + 1);
		m_comboRule.InsertString(i,strItemText);
	}
	
    m_listTPSType.ResetContent();
	
    int index = 0;
    if ((m_struItsAbility.dwAbilityType & ITS_LANE_VOLUME_ABILITY) != 0)
    {
		g_StringLanType(szLan, "车道流量", "Lane volume");
		m_listTPSType.InsertString(index, szLan);
		m_listTPSType.SetItemData(index, LANE_VOLUME);
		index++;
    }
    
    if ((m_struItsAbility.dwAbilityType & ITS_LANE_VELOCITY_ABILITY) != 0)
    {
		g_StringLanType(szLan, "车道速度", "Lane velocity");
		m_listTPSType.InsertString(index, szLan);
		m_listTPSType.SetItemData(index, LANE_VELOCITY);
		index++;
    }
    
    if ((m_struItsAbility.dwAbilityType & ITS_TIME_HEADWAY_ABILITY) != 0)
    {
		g_StringLanType(szLan, "车头时距", "Time Headway");
		m_listTPSType.InsertString(index, szLan);
		m_listTPSType.SetItemData(index, TIME_HEADWAY);
		index++;
    }
    
    if ((m_struItsAbility.dwAbilityType & ITS_SPACE_HEADWAY_ABILITY) != 0)
    {
		g_StringLanType(szLan, "车头间距", "Space headway");
		m_listTPSType.InsertString(index, szLan);
		m_listTPSType.SetItemData(index, SPACE_HEADWAY);
		index++;
    }
    
    if ((m_struItsAbility.dwAbilityType & ITS_TIME_OCCUPANCY_RATIO_ABILITY) != 0)
    {
		g_StringLanType(szLan, "车道时间占有率", "Time occupancy ratio");
		m_listTPSType.InsertString(index, szLan);
		m_listTPSType.SetItemData(index, TIME_OCCUPANCY_RATIO);
		index++;
    }
    
    if ((m_struItsAbility.dwAbilityType & ITS_SPACE_OCCUPANCY_RATIO_ABILITY) != 0)
    {
		g_StringLanType(szLan, "车道空间占有率", "Space occupancy ratio");
		m_listTPSType.InsertString(index, szLan);
		m_listTPSType.SetItemData(index, SPACE_OCCUPANCY_RATIO);
		index++;
    }
    
    if ((m_struItsAbility.dwAbilityType & ITS_LANE_QUEUE_ABILITY) != 0)
    {
		g_StringLanType(szLan, "排队长度", "Queue");
		m_listTPSType.InsertString(index, szLan);
		m_listTPSType.SetItemData(index, QUEUE);
		index++;
    }

	if ((m_struItsAbility.dwAbilityType & ITS_VEHICLE_TYPE_ABILITY) != 0)
    {
		g_StringLanType(szLan, "车辆类型", "Vehicle type");
		m_listTPSType.InsertString(index, szLan);
		m_listTPSType.SetItemData(index, VEHICLE_TYPE);
		index++;
    }

	if ((m_struItsAbility.dwAbilityType & ITS_TRAFFIC_STATE_ABILITY) != 0)
    {
		g_StringLanType(szLan, "交通状态", "Traffic state");
		m_listTPSType.InsertString(index, szLan);
		m_listTPSType.SetItemData(index,TRAFFIC_STATE);
		index++;
    }
	
    for (i = 0; i < MAX_IP_ALARMOUT_V40; i++)
	{
		DWORD dwID       = g_struDeviceInfo[m_iDevIndex].struAlarmOutCfg.struIPAlarmOutInfo[i].byIPID;
		DWORD dwAlarmOut = g_struDeviceInfo[m_iDevIndex].struAlarmOutCfg.struIPAlarmOutInfo[i].byAlarmOut;
		if (dwID != 0)
		{   
			sprintf(sbufCn, "IP输出 %d", (i+1));
			sprintf(sbufEn, "IPAlarmOut %d", (i+1));
            g_StringLanType(szLan, sbufCn, sbufEn);
			m_listAlarmOutputChan.InsertString(i,szLan);
			m_listAlarmOutputChan.SetItemData(i,dwAlarmOut);
		}
	}
	
    
	m_comboSizeFilterMode.ResetContent();
	char szSizeBuff[50] = {0};
	 g_StringLanType(szSizeBuff, "像素大小", "Image pixel mode");
	m_comboSizeFilterMode.InsertString(0,szSizeBuff);
	m_comboSizeFilterMode.SetItemData(0,IMAGE_PIX_MODE);

	g_StringLanType(szSizeBuff, "实际尺寸", "Real world mode");
	m_comboSizeFilterMode.InsertString(1,szSizeBuff);
	m_comboSizeFilterMode.SetItemData(1,REAL_WORLD_MODE);
    
	int nIndex = 0;
	for (i = 0; i < MAX_ITS_SCENE_NUM; i++)
	{   
		NET_DVR_ONE_SCENE_CFG& struOneSceneCfg = m_struSceneCfg.struSceneCfg[i];
		if (struOneSceneCfg.dwSceneID > 0 && struOneSceneCfg.byEnable)
		{   
			strItemText.Format(_T("%s"), struOneSceneCfg.bySceneName);
			m_comboScene.InsertString(nIndex,strItemText);
			m_comboScene.SetItemData(nIndex,struOneSceneCfg.dwSceneID);
			nIndex++;
		}
	}

	for (i = 0; i < MAX_LANE_NUM; i++)
	{
		strItemText.Format(_T("%d"), i + 1);
		m_comboLane.InsertString(i,strItemText);
	}
    
	m_comboRule.SetCurSel(0);
	m_comboLane.SetCurSel(0);
}

void CDlgVcaSceneTpsRuleCfg::LoadWndRuleContent(int nSceneIndex,int nRuleIndex)
{
	int i = 0;
	
	const NET_DVR_ONE_TPS_RULE_V41& struOneTpsRule = m_struTPSRuleCfg[nSceneIndex].struOneTpsRule[nRuleIndex];
	
	m_bRuleActive    =  struOneTpsRule.byEnable;
	m_nCurLaneIndex  =  struOneTpsRule.byLaneID;

	m_comboLane.SetCurSel(m_nCurLaneIndex);
    
	int nTpsTypeCount = m_listTPSType.GetCount();
	for (i = 0; i < nTpsTypeCount; i++)
	{
		if (struOneTpsRule.dwCalcType & m_listTPSType.GetItemData(i))
		{
			m_listTPSType.SetCheck(i,TRUE);
		}
		else
		{
			m_listTPSType.SetCheck(i,FALSE);
		}
	}
	
	memcpy(&m_struCurRulePolygon,&struOneTpsRule.struVitrualLoop, sizeof(m_struCurRulePolygon));
	
	
    m_bHandleType_Monitor  = struOneTpsRule.struHandleType.dwHandleType & 0x01 ? TRUE : FALSE;
    m_bHandleType_Sound    = struOneTpsRule.struHandleType.dwHandleType & 0x02 ? TRUE : FALSE;
    m_bHandleType_Upload   = struOneTpsRule.struHandleType.dwHandleType & 0x04 ? TRUE : FALSE;
    m_bHandleType_Output   = struOneTpsRule.struHandleType.dwHandleType & 0x08 ? TRUE : FALSE;
    m_bHandleType_EmailJpg = struOneTpsRule.struHandleType.dwHandleType & 0x10 ? TRUE : FALSE;
    
    for (i = 0; i < MAX_ALARMOUT_V30 ;i++)
    {   
		if (i >= m_listAlarmOutputChan.GetCount())
		{
			break;
		}
        if (struOneTpsRule.struHandleType.byRelAlarmOut[i])
		{
			m_listAlarmOutputChan.SetCheck(i,TRUE);
		}
		else
		{
			m_listAlarmOutputChan.SetCheck(i,FALSE);
		}
    }
	
	
	m_bSizeFilterEnable = struOneTpsRule.struSizeFilter.byActive ;
	m_nSizeFilterMode = struOneTpsRule.struSizeFilter.byMode;
    
	int nFilterModeCount = m_comboSizeFilterMode.GetCount();
	for (i = 0; i < nFilterModeCount; i++)
	{
		if (m_comboSizeFilterMode.GetItemData(i) == struOneTpsRule.struSizeFilter.byMode)
		{
			m_comboSizeFilterMode.SetCurSel(i);
			break;
		}
	}
	
	int nMultiWndWidth  = 1;
	int nMultiWndHeight = 1;
	if (struOneTpsRule.struSizeFilter.byMode == IMAGE_PIX_MODE)
	{
		nMultiWndWidth  = m_rcPlayWnd.Width();
		nMultiWndHeight = m_rcPlayWnd.Height();
	}
	
    m_nMinRectHeight = struOneTpsRule.struSizeFilter.struMiniRect.fHeight * nMultiWndHeight;
	m_nMinRectWidth  = struOneTpsRule.struSizeFilter.struMiniRect.fWidth  * nMultiWndWidth;
	m_nMaxRectHeight = struOneTpsRule.struSizeFilter.struMaxRect.fHeight  * nMultiWndHeight;
    m_nMaxRectWidth  = struOneTpsRule.struSizeFilter.struMaxRect.fWidth   * nMultiWndWidth;
    
	m_struMinRect[m_nCurSceneIndex][m_nCurRuleIndex] = struOneTpsRule.struSizeFilter.struMiniRect;
	m_struMaxRect[m_nCurSceneIndex][m_nCurRuleIndex] = struOneTpsRule.struSizeFilter.struMaxRect;
	
	UpdateData(FALSE);
    
	OnSelchangeComboSizefilterMode();
	OnCheckSizefilterEnable();
}

void CDlgVcaSceneTpsRuleCfg::SaveWndRuleContent(int nSceneIndex,int nRuleIndex)
{
	UpdateData(TRUE);
	
    int i = 0;
	
	NET_DVR_ONE_TPS_RULE_V41& struOneTpsRule = m_struTPSRuleCfg[nSceneIndex].struOneTpsRule[nRuleIndex];

	struOneTpsRule.byEnable = m_bRuleActive;
	struOneTpsRule.byLaneID = m_nCurLaneIndex;
    
	struOneTpsRule.dwCalcType = 0;
	int nAidTypeCount = m_listTPSType.GetCount();
	for (i = 0; i < nAidTypeCount; i++)
	{
		if (m_listTPSType.GetCheck(i))
		{
			struOneTpsRule.dwCalcType |= m_listTPSType.GetItemData(i);
		}
	}
	
    memcpy(&struOneTpsRule.struVitrualLoop, &m_struCurRulePolygon, sizeof(struOneTpsRule.struVitrualLoop));
	

	struOneTpsRule.struHandleType.dwHandleType = 0;
	if (m_bHandleType_Monitor)
	{
		struOneTpsRule.struHandleType.dwHandleType |= 0x01;
	}
	if (m_bHandleType_Sound)
	{
		struOneTpsRule.struHandleType.dwHandleType |= 0x02;
	}
	
	if (m_bHandleType_Upload)
	{
		struOneTpsRule.struHandleType.dwHandleType |= 0x04;
	}
	
	if (m_bHandleType_Output)
	{
		struOneTpsRule.struHandleType.dwHandleType |= 0x08;
	}
	
	if (m_bHandleType_EmailJpg)
	{
		struOneTpsRule.struHandleType.dwHandleType |= 0x10;
	}
    
	for (i = 0; i < MAX_ALARMOUT_V30; i++)
    {   
		if (i >= m_listAlarmOutputChan.GetCount())
		{
			break;
		}
        struOneTpsRule.struHandleType.byRelAlarmOut[i] = m_listAlarmOutputChan.GetCheck(i);
    }
    
	int nFilterModeIndex = m_comboSizeFilterMode.GetCurSel();
	
	struOneTpsRule.struSizeFilter.byActive = m_bSizeFilterEnable;
    struOneTpsRule.struSizeFilter.byMode   = m_comboSizeFilterMode.GetItemData(nFilterModeIndex);
    
	struOneTpsRule.struSizeFilter.struMaxRect  = m_struMaxRect[m_nCurSceneIndex][m_nCurRuleIndex];
    struOneTpsRule.struSizeFilter.struMiniRect = m_struMinRect[m_nCurSceneIndex][m_nCurRuleIndex];
	if (struOneTpsRule.struSizeFilter.byMode == REAL_WORLD_MODE)
	{
		struOneTpsRule.struSizeFilter.struMiniRect.fHeight = m_nMinRectHeight;
		struOneTpsRule.struSizeFilter.struMiniRect.fWidth  = m_nMinRectWidth;
		struOneTpsRule.struSizeFilter.struMaxRect.fHeight  = m_nMaxRectHeight;
        struOneTpsRule.struSizeFilter.struMaxRect.fWidth   = m_nMaxRectWidth;
	}
}

void CDlgVcaSceneTpsRuleCfg::LoadWndSceneContent(int nSceneIndex)
{   
	if (!GetTPSRuleCfg())
	{   
		char szError[32] = "\0";
		g_StringLanType(szError, "获取统计规则失败", "Get TPS rule cfg failed!");
		AfxMessageBox(szError);
	}

	if (!GetLaneCfg())
	{
		char szError[32] = "\0";
		g_StringLanType(szError, "获取车道信息失败", "Get lane cfg failed!");
		AfxMessageBox(szError);
	}
    
	m_comboScene.SetCurSel(nSceneIndex);
	m_comboRule.SetCurSel(0);
	m_nCurRuleIndex = 0;
	LoadWndRuleContent(nSceneIndex,m_nCurRuleIndex);

	UpdateData(FALSE);

	//Change to current scene ptz pos
	ChangeScene(m_struSceneCfg.struSceneCfg[m_nCurSceneIndex].struPtzPos);
}

void CDlgVcaSceneTpsRuleCfg::SaveWndSceneContent(int nSceneIndex)
{
	UpdateData(TRUE);
	
	SaveWndRuleContent(nSceneIndex,m_nCurRuleIndex);
}

BOOL CDlgVcaSceneTpsRuleCfg::GetVcaChanAbility()
{
	BOOL bRet = FALSE; 
	
	NET_VCA_CTRLCFG struVcaCtrlCfg = {0};
    memcpy(&struVcaCtrlCfg, &g_pMainDlg->m_struVcaCtrlCfg,sizeof(NET_VCA_CTRLCFG));
	
    NET_VCA_CHAN_IN_PARAM struVcaChanInParam = {0};
    struVcaChanInParam.byMode    = struVcaCtrlCfg.struCtrlInfo[m_lChannel - 1].byMode;
    struVcaChanInParam.byVCAType = struVcaCtrlCfg.struCtrlInfo[m_lChannel - 1].byVCAType;
    
    if (!NET_DVR_GetDeviceAbility(m_lServerID, VCA_CHAN_ABILITY, (char*)&struVcaChanInParam,
        sizeof(struVcaChanInParam), (char*)&m_struItsAbility, sizeof(m_struItsAbility)))
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

BOOL CDlgVcaSceneTpsRuleCfg::GetTPSRuleCfg()
{
	NET_DVR_SCENE_COND struSceneCond = {0};
	GetSceneCond(struSceneCond);
	
	DWORD dwStatus = 0;
	BOOL bRet      = FALSE;
	
    if (!NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_SCENE_TPS_RULECFG, 1,(LPVOID)&struSceneCond, sizeof(struSceneCond),
		&dwStatus,&m_struTPSRuleCfg[m_nCurSceneIndex], sizeof(m_struTPSRuleCfg[m_nCurSceneIndex])))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SCENE_TPS_RULECFG Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SCENE_TPS_RULECFG Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
	return bRet;
}



BOOL CDlgVcaSceneTpsRuleCfg::SetTPSRuleCfg()
{
	NET_DVR_SCENE_COND struSceneCond = {0};
	GetSceneCond(struSceneCond);
	
    DWORD dwStatus = 0;
	BOOL bRet      = FALSE;
	
    if (!NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_SCENE_TPS_RULECFG,1,(LPVOID)&struSceneCond, sizeof(struSceneCond),
		&dwStatus,&m_struTPSRuleCfg[m_nCurSceneIndex], sizeof(m_struTPSRuleCfg[m_nCurSceneIndex])))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SCENE_TPS_RULECFG Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SCENE_TPS_RULECFG Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}

BOOL CDlgVcaSceneTpsRuleCfg::GetLaneCfg()
{
	NET_DVR_SCENE_COND struSceneCond = {0};
	GetSceneCond(struSceneCond);
	
	DWORD dwStatus = 0;
	BOOL bRet      = FALSE;
	
	memset(&m_struSceneLaneCfg[m_nCurSceneIndex],0,sizeof(m_struSceneLaneCfg[m_nCurSceneIndex]));
    m_struSceneLaneCfg[m_nCurSceneIndex].dwSize = sizeof(m_struSceneLaneCfg[m_nCurSceneIndex]);
    if (!NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_SCENE_LANECFG, 1,(LPVOID)&struSceneCond, sizeof(struSceneCond),
		&dwStatus,&m_struSceneLaneCfg[m_nCurSceneIndex], sizeof(m_struSceneLaneCfg[m_nCurSceneIndex])))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SCENE_LANECFG Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SCENE_LANECFG Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
	return bRet;
}

BOOL CDlgVcaSceneTpsRuleCfg::GetSceneCond(NET_DVR_SCENE_COND& struSceneCond)
{
	struSceneCond.dwSize    = sizeof(struSceneCond);
	struSceneCond.dwSceneID = m_comboScene.GetItemData(m_nCurSceneIndex);
	struSceneCond.lChannel  = m_lChannel;
	
	return TRUE;
}

void CDlgVcaSceneTpsRuleCfg::EnableSetParams(BOOL bEnable)
{
	GetDlgItem(IDC_BTN_SAVE)->EnableWindow(bEnable);
}
