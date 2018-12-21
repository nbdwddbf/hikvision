// DlgVcaSceneAidRuleCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaSceneAidRuleCfg.h"
#include "DlgVcaAlarmTimeCfg.h"
#include "DrawFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_RULEPOLYGON_POINT_NUM 10
#define MIN_RULEPOLYGON_POINT_NUM 4
/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSceneAidRuleCfg dialog

void CALLBACK g_DrawSceneAidRule(LONG lRealHandle, HDC hDc, DWORD dwUser)
{   
	CDlgVcaSceneAidRuleCfg* pDlgAidRuleCfg = (CDlgVcaSceneAidRuleCfg*)(dwUser);
	if (pDlgAidRuleCfg != NULL)
	{
		pDlgAidRuleCfg->DrawAidRuleFun(hDc);
	}
}

CDlgVcaSceneAidRuleCfg::CDlgVcaSceneAidRuleCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaSceneAidRuleCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaSceneAidRuleCfg)
	m_bRuleActive          = FALSE;
	m_strRuleName          = _T("");
	m_bHandleType_EmailJpg = FALSE;
	m_bHandleType_Monitor  = FALSE;
	m_bHandleType_Sound    = FALSE;
	m_bHandleType_Output   = FALSE;
	m_bHandleType_Upload   = FALSE;
	m_nPedestrian          = 0;
	m_nParking             = 0;
	m_nMinRectWidth        = 0;
	m_nMinRectHeight       = 0;
	m_nMaxRectWidth        = 0;
	m_nMaxRectHeight       = 0;
	m_nInverseDuration     = 0;
	m_nInverseDistance     = 0;
	m_nInverseAngle        = 0;
	m_nDebris              = 0;
	m_nCongestionDuration  = 0;
	m_nCongestionLength    = 0;
	m_bSizeFilterEnable    = FALSE;
	m_nIllegalParkingTime = 0;
	m_nIllegalParkingPicNum = 0;
	m_bMergePic = FALSE;
	//}}AFX_DATA_INIT
	memset(&m_struItsAbility,    0, sizeof(m_struItsAbility));
	memset(m_struAIDRuleCfg,     0, sizeof(m_struAIDRuleCfg));
	memset(&m_struCurRulePolygon,0, sizeof(m_struCurRulePolygon));
	memset(m_struMinRect,        0, sizeof(m_struMinRect));
	memset(m_struMaxRect,        0, sizeof(m_struMaxRect));
	memset(&m_struSceneCfg,      0, sizeof(m_struSceneCfg));
	memset(m_struSceneLaneCfg,   0, sizeof(m_struSceneLaneCfg));
	m_nCurSceneIndex       = 0;
	m_nCurRuleIndex        = 0;
	m_nCurDrawType         = DRAW_TYPE_NONE;
	m_bFirstDrawMaxRect    = FALSE;
	m_bFirstDrawMinRect    = FALSE;
	m_nSizeFilterMode      = 0;
	m_nDrawPointNum        = 0;

}


void CDlgVcaSceneAidRuleCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaSceneAidRuleCfg)
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_comboPicResolution);
	DDX_Control(pDX, IDC_COMBO_PIC_QUALITY, m_comboPicQuality);
	DDX_Control(pDX, IDC_COMBO_PRO_PIC_TYPE, m_comboProPicType);
	DDX_Control(pDX, IDC_COMBO_SIZEFILTER_MODE, m_comboSizeFilterMode);
	DDX_Control(pDX, IDC_LIST_RECORD_CHAN, m_listRecordChan);
	DDX_Control(pDX, IDC_LIST_ALARMOUTPUT_CHAN, m_listAlarmOutputChan);
	DDX_Control(pDX, IDC_LIST_AIDTYPE, m_listAIDType);
	DDX_Control(pDX, IDC_COMBO_RULEINDEX, m_comboRuleIndex);
	DDX_Control(pDX, IDC_COMBO_SCENE, m_comboScene);
	DDX_Check(pDX, IDC_CHECK_RULEACTIVE, m_bRuleActive);
	DDX_Text(pDX, IDC_EDIT_RULENAME, m_strRuleName);
	DDX_Check(pDX, IDC_CHECK_HANDLETYPE_JPG, m_bHandleType_EmailJpg);
	DDX_Check(pDX, IDC_CHECK_HANDLETYPE_MONITOR, m_bHandleType_Monitor);
	DDX_Check(pDX, IDC_CHECK_HANDLETYPE_SOUND, m_bHandleType_Sound);
	DDX_Check(pDX, IDC_CHECK_HANDLETYPE_OUTPUT, m_bHandleType_Output);
	DDX_Check(pDX, IDC_CHECK_HANDLETYPE_UPLOAD, m_bHandleType_Upload);
	DDX_Text(pDX, IDC_EDIT_PEDESTRIAN, m_nPedestrian);
	DDX_Text(pDX, IDC_EDIT_PARKING, m_nParking);
	DDX_Text(pDX, IDC_EDIT_MINRECT_WIDTH, m_nMinRectWidth);
	DDX_Text(pDX, IDC_EDIT_MINRECT_HEIGHT, m_nMinRectHeight);
	DDX_Text(pDX, IDC_EDIT_MAXRECT_WIDTH, m_nMaxRectWidth);
	DDX_Text(pDX, IDC_EDIT_MAXRECT_HEIGHT, m_nMaxRectHeight);
	DDX_Text(pDX, IDC_EDIT_INVERSE_DURATION, m_nInverseDuration);
	DDX_Text(pDX, IDC_EDIT_INVERSE_DISTANCE, m_nInverseDistance);
	DDX_Text(pDX, IDC_EDIT_INVERSE_ANGLE, m_nInverseAngle);
	DDX_Text(pDX, IDC_EDIT_DEBRIS, m_nDebris);
	DDX_Text(pDX, IDC_EDIT_CONGESTION_DURATION, m_nCongestionDuration);
	DDX_Text(pDX, IDC_EDIT_CONGESTION_LENGTH, m_nCongestionLength);
	DDX_Check(pDX, IDC_CHECK_SIZEFILTER_ENABLE, m_bSizeFilterEnable);
	DDX_Text(pDX, IDC_EDIT_ILLEGAL_PARKINGTIME, m_nIllegalParkingTime);
	DDX_Text(pDX, IDC_EDIT_ILLEGAL_PARKINGPICNUM, m_nIllegalParkingPicNum);
	DDX_Check(pDX, IDC_CHECK_MERGE_PIC, m_bMergePic);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaSceneAidRuleCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaSceneAidRuleCfg)
	ON_CBN_SELCHANGE(IDC_COMBO_SCENE, OnSelchangeComboScene)
	ON_CBN_SELCHANGE(IDC_COMBO_SIZEFILTER_MODE, OnSelchangeComboSizefilterMode)
	ON_CBN_SELCHANGE(IDC_COMBO_RULEINDEX, OnSelchangeComboRuleindex)
	ON_BN_CLICKED(IDC_BTN_DRAW_MAXRECT, OnBtnDrawMaxrect)
	ON_BN_CLICKED(IDC_BTN_DRAW_MINRECT, OnBtnDrawMinrect)
	ON_BN_CLICKED(IDC_BTN_DRAW_RULE, OnBtnDrawRule)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_SET_ALARMTIME, OnBtnSetAlarmtime)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BTN_STOPDRAW, OnBtnStopdraw)
	ON_BN_CLICKED(IDC_CHECK_SIZEFILTER_ENABLE, OnCheckSizefilterEnable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSceneAidRuleCfg message handlers

BOOL CDlgVcaSceneAidRuleCfg::OnInitDialog()
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

	StartRealPlay(GetDlgItem(IDC_PLAYWND)->GetSafeHwnd(),g_DrawSceneAidRule,this);

	LoadWndSceneContent(m_nCurSceneIndex);

	return TRUE;
}

void CDlgVcaSceneAidRuleCfg::OnSelchangeComboScene() 
{
	int nCusrSceneIndex = m_comboScene.GetCurSel();
	if (nCusrSceneIndex != CB_ERR)
	{  
		SaveWndSceneContent(m_nCurSceneIndex);

		m_nCurSceneIndex = nCusrSceneIndex;

		LoadWndSceneContent(nCusrSceneIndex);
	}
	
}

void CDlgVcaSceneAidRuleCfg::OnSelchangeComboSizefilterMode() 
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

void CDlgVcaSceneAidRuleCfg::OnSelchangeComboRuleindex() 
{
	int nSelRuleIndex = m_comboRuleIndex.GetCurSel();
	if (nSelRuleIndex != CB_ERR)
	{
		SaveWndRuleContent(m_nCurSceneIndex,m_nCurRuleIndex);

		m_nCurRuleIndex = nSelRuleIndex;

		LoadWndRuleContent(m_nCurSceneIndex,nSelRuleIndex);
	}
	
}

void CDlgVcaSceneAidRuleCfg::OnBtnDrawMaxrect() 
{
	memset(&m_struMaxRect[m_nCurRuleIndex],0,sizeof(m_struMaxRect[m_nCurRuleIndex]));
	m_nCurDrawType = DRAW_TYPE_MAXRECT;
	m_bFirstDrawMaxRect = TRUE;
}

void CDlgVcaSceneAidRuleCfg::OnBtnDrawMinrect() 
{
	memset(&m_struMinRect[m_nCurRuleIndex],0,sizeof(m_struMinRect[m_nCurRuleIndex]));
	m_nCurDrawType = DRAW_TYPE_MINRECT;
	m_bFirstDrawMinRect = TRUE;
}

void CDlgVcaSceneAidRuleCfg::OnBtnDrawRule() 
{   
	memset(&m_struCurRulePolygon,0,sizeof(m_struCurRulePolygon));
	m_nCurDrawType = DRAW_TYPE_RULE;
	m_nDrawPointNum     = 0;
}

void CDlgVcaSceneAidRuleCfg::OnBtnSave() 
{
	SaveWndSceneContent(m_nCurSceneIndex);
    
	char szError[32] = "\0";
	if (SetAIDRuleCfg())
	{
		g_StringLanType(szError, "保存成功","Saved successfully");
	}
	else
	{
		g_StringLanType(szError, "保存失败","Save failed");
	}
	AfxMessageBox(szError);
}

void CDlgVcaSceneAidRuleCfg::OnBtnSetAlarmtime() 
{   
	CDlgVcaAlarmTimeCfg dlg;
	dlg.InitAlarmTimeCfg(m_struAIDRuleCfg[m_nCurSceneIndex].struAIDRule[m_nCurRuleIndex].struAlarmTime);
	if (dlg.DoModal() == IDOK)
	{
		dlg.GetAlarmTimeCfg(m_struAIDRuleCfg[m_nCurSceneIndex].struAIDRule[m_nCurRuleIndex].struAlarmTime);
	}
	
}

void CDlgVcaSceneAidRuleCfg::OnDestroy()
{   
	StopRealPlay();
	CDialog::OnDestroy();
}

void CDlgVcaSceneAidRuleCfg::OnLButtonDown(UINT nFlags, CPoint point)
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

void CDlgVcaSceneAidRuleCfg::OnRButtonDown(UINT nFlags, CPoint point)
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


void CDlgVcaSceneAidRuleCfg::OnMouseMove(UINT nFlags, CPoint point)
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

void CDlgVcaSceneAidRuleCfg::DrawAidRuleFun(HDC hdc)
{
	DRAW_POLYGON_PARAM struDrawPolygon;
    memset(&struDrawPolygon, 0, sizeof(struDrawPolygon));
    struDrawPolygon.color = RGB(255, 0, 0);
    memcpy(&struDrawPolygon.rcWnd, &m_rcPlayWnd, sizeof(struDrawPolygon.rcWnd));
    memcpy(&struDrawPolygon.struVcaPolygon, &m_struCurRulePolygon, sizeof(struDrawPolygon.struVcaPolygon));
    struDrawPolygon.bCloseIn   = m_nCurDrawType != DRAW_TYPE_RULE;
    struDrawPolygon.bMouseMove = FALSE;
    strncpy(struDrawPolygon.chName, (char*)m_struAIDRuleCfg[m_nCurSceneIndex].struAIDRule[m_nCurRuleIndex].byRuleName, sizeof(struDrawPolygon.chName));
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

void CDlgVcaSceneAidRuleCfg::InitCtrlState()
{
	char szLan[128] = {0};
    char sbufCn[128] = {0};
    char sbufEn[128] = {0};
    int i = 0;
	
	CString strItemText = _T("");
	for (i = 0; i < MAX_RULE_NUM; i++)
	{
		strItemText.Format(_T("Rule %d"), i + 1);
		m_comboRuleIndex.InsertString(i,strItemText);
	}
	
    m_listAIDType.ResetContent();
	
    int index = 0;
	
    if ((m_struItsAbility.dwAbilityType & ITS_CONGESTION_ABILITY) != 0)
    {
		g_StringLanType(szLan, "拥堵", "Congestion");
		m_listAIDType.InsertString(index, szLan);
		m_listAIDType.SetItemData(index, CONGESTION);
		index++;
    }
	
    if ((m_struItsAbility.dwAbilityType & ITS_PARKING_ABILITY) != 0)
    {
		g_StringLanType(szLan, "停车", "Parking");
		m_listAIDType.InsertString(index, szLan);
		m_listAIDType.SetItemData(index, PARKING);
		index++;
    }
	
    if ((m_struItsAbility.dwAbilityType & ITS_INVERSE_ABILITY) != 0)
    {
		g_StringLanType(szLan, "逆行", "Inverse");
		m_listAIDType.InsertString(index, szLan);
		m_listAIDType.SetItemData(index, INVERSE);
		index++;
    }
	
    if ((m_struItsAbility.dwAbilityType & ITS_PEDESTRIAN_ABILITY) != 0)
    {
		g_StringLanType(szLan, "行人", "Pedestrian");
		m_listAIDType.InsertString(index, szLan);
		m_listAIDType.SetItemData(index, PEDESTRIAN);
		index++;
    }
	
    if ((m_struItsAbility.dwAbilityType & ITS_DEBRIS_ABILITY) != 0)
    {
		g_StringLanType(szLan, "抛洒物", "Debris");
		m_listAIDType.InsertString(index, szLan);
		m_listAIDType.SetItemData(index, DEBRIS);
		index++;
    }
	
    if ((m_struItsAbility.dwAbilityType & ITS_SMOKE_ABILITY) != 0)
    {
        g_StringLanType(szLan, "烟雾", "Smoke");
       	m_listAIDType.InsertString(index, szLan);
        m_listAIDType.SetItemData(index, SMOKE);
        index++;
    }
    
	for (i = 0; i < MAX_IP_ALARMOUT_V40; i++)
	{
		DWORD dwID       = g_struDeviceInfo[m_iDevIndex].pStruIPAlarmOutCfgV40->struIPAlarmOutInfo[i].dwIPID;
		DWORD dwAlarmOut = g_struDeviceInfo[m_iDevIndex].pStruIPAlarmOutCfgV40->struIPAlarmOutInfo[i].dwAlarmOut;
		if (dwID != 0)
		{   
			sprintf(sbufCn, "IP输出 %d", (i+1));
			sprintf(sbufEn, "IPAlarmOut %d", (i+1));
            g_StringLanType(szLan, sbufCn, sbufEn);
		    m_listAlarmOutputChan.InsertString(i,szLan);
			m_listAlarmOutputChan.SetItemData(i,dwAlarmOut);
		}
	}
	
    int nChannelnumber = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;
    m_listRecordChan.ResetContent();
    for (i = 0; i < nChannelnumber; i++)
    {
        sprintf(sbufCn, "通道%d", (i+1));
        sprintf(sbufEn, "Channel%d", (i+1));
        g_StringLanType(szLan, sbufCn, sbufEn);
        m_listRecordChan.InsertString(i, szLan);
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
}


BOOL CDlgVcaSceneAidRuleCfg::GetVcaChanAbility()
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


BOOL CDlgVcaSceneAidRuleCfg::SetAIDRuleCfg()
{   
    NET_DVR_SCENE_COND struSceneCond = {0};
	GetSceneCond(struSceneCond);
	
    DWORD dwStatus = 0;
	BOOL bRet      = FALSE;
	
	m_struAIDRuleCfg[m_nCurSceneIndex].dwSize = sizeof(m_struAIDRuleCfg[m_nCurSceneIndex]);
    if (!NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_SCENE_AID_RULECFG,1,(LPVOID)&struSceneCond, sizeof(struSceneCond),
		&dwStatus,&m_struAIDRuleCfg[m_nCurSceneIndex], sizeof(m_struAIDRuleCfg[m_nCurSceneIndex])))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SCENE_AID_RULECFG Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SCENE_AID_RULECFG Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}


BOOL CDlgVcaSceneAidRuleCfg::GetAIDRuleCfg()
{
	NET_DVR_SCENE_COND struSceneCond = {0};
	GetSceneCond(struSceneCond);
	
	DWORD dwStatus = 0;
	BOOL bRet      = FALSE;
	
	m_struAIDRuleCfg[m_nCurSceneIndex].dwSize = sizeof(m_struAIDRuleCfg[m_nCurSceneIndex]);
    if (!NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_SCENE_AID_RULECFG, 1,(LPVOID)&struSceneCond, sizeof(struSceneCond),
		&dwStatus,&m_struAIDRuleCfg[m_nCurSceneIndex], sizeof(m_struAIDRuleCfg[m_nCurSceneIndex])))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SCENE_AID_RULECFG Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SCENE_AID_RULECFG Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
	return bRet;
}

BOOL CDlgVcaSceneAidRuleCfg::GetLaneCfg()
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


BOOL CDlgVcaSceneAidRuleCfg::GetSceneCond(NET_DVR_SCENE_COND& struSceneCond)
{
	struSceneCond.dwSize    = sizeof(struSceneCond);
	struSceneCond.dwSceneID = m_comboScene.GetItemData(m_nCurSceneIndex);
	struSceneCond.lChannel  = m_lChannel;

	return TRUE;
}


void CDlgVcaSceneAidRuleCfg::OnBtnStopdraw() 
{   
	m_bFirstDrawMaxRect = FALSE;
	m_bFirstDrawMinRect = FALSE;
	m_nCurDrawType = DRAW_TYPE_NONE;
	m_struCurRulePolygon.dwPointNum = m_nDrawPointNum;
	EnableSetParams(TRUE);
}

void CDlgVcaSceneAidRuleCfg::EnableSetParams(BOOL bEnable)
{
	GetDlgItem(IDC_BTN_SAVE)->EnableWindow(bEnable);
}


void CDlgVcaSceneAidRuleCfg::OnCheckSizefilterEnable() 
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



void CDlgVcaSceneAidRuleCfg::LoadWndRuleContent(int nSceneIndex,int nRuleIndex)
{   
	int i = 0;

	const NET_DVR_ONE_AID_RULE_V41& struOneAidRule = m_struAIDRuleCfg[nSceneIndex].struAIDRule[nRuleIndex];

	m_bRuleActive = struOneAidRule.byEnable;
	m_strRuleName = struOneAidRule.byRuleName;
    
	int nAidTypeCount = m_listAIDType.GetCount();
	for (i = 0; i < nAidTypeCount; i++)
	{
		if (struOneAidRule.dwEventType & m_listAIDType.GetItemData(i))
		{
			m_listAIDType.SetCheck(i,TRUE);
		}
		else
		{
			m_listAIDType.SetCheck(i,FALSE);
		}
	}

	memcpy(&m_struCurRulePolygon,&struOneAidRule.struPolygon, sizeof(m_struCurRulePolygon));

    m_nParking              = struOneAidRule.struAIDParam.wParkingDuration;
    m_nPedestrian           = struOneAidRule.struAIDParam.wPedestrianDuration;
    m_nDebris               = struOneAidRule.struAIDParam.wDebrisDuration;
    m_nCongestionLength     = struOneAidRule.struAIDParam.wCongestionLength;
    m_nCongestionDuration   = struOneAidRule.struAIDParam.wCongestionDuration;
    m_nInverseDuration      = struOneAidRule.struAIDParam.wInverseDuration;
    m_nInverseDistance      = struOneAidRule.struAIDParam.wInverseDistance;
    m_nInverseAngle         = struOneAidRule.struAIDParam.wInverseAngleTolerance;
	m_nIllegalParkingTime   = struOneAidRule.struAIDParam.wIllegalParkingTime;
	m_nIllegalParkingPicNum = struOneAidRule.struAIDParam.wIllegalParkingPicNum;
	m_bMergePic             = struOneAidRule.struAIDParam.byMergePic;

    m_bHandleType_Monitor  = struOneAidRule.struHandleType.dwHandleType & 0x01 ? TRUE : FALSE;
    m_bHandleType_Sound    = struOneAidRule.struHandleType.dwHandleType & 0x02 ? TRUE : FALSE;
    m_bHandleType_Upload   = struOneAidRule.struHandleType.dwHandleType & 0x04 ? TRUE : FALSE;
    m_bHandleType_Output   = struOneAidRule.struHandleType.dwHandleType & 0x08 ? TRUE : FALSE;
    m_bHandleType_EmailJpg = struOneAidRule.struHandleType.dwHandleType & 0x10 ? TRUE : FALSE;

    for (i = 0; i < MAX_ALARMOUT_V30; i++)
    {   
		if (i >= m_listAlarmOutputChan.GetCount())
		{
			break;
		}

        if (struOneAidRule.struHandleType.byRelAlarmOut[i])
		{   
			m_listAlarmOutputChan.SetCheck(i,TRUE);
		}
		else
		{
			m_listAlarmOutputChan.SetCheck(i,FALSE);
		}
    }

	int nChannelnumber = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;
	for (i = 0; i < nChannelnumber; i++)
    {
        if (struOneAidRule.byRelRecordChan[i])
		{
			m_listRecordChan.SetCheck(i,TRUE);
		}
		else
		{
			m_listRecordChan.SetCheck(i,FALSE);
		}
    }

	m_bSizeFilterEnable = struOneAidRule.struSizeFilter.byActive ;
	m_nSizeFilterMode = struOneAidRule.struSizeFilter.byMode;
    
	int nFilterModeCount = m_comboSizeFilterMode.GetCount();
	for (i = 0; i < nFilterModeCount; i++)
	{
		if (m_comboSizeFilterMode.GetItemData(i) == struOneAidRule.struSizeFilter.byMode)
		{
			m_comboSizeFilterMode.SetCurSel(i);
			break;
		}
	}
	
	int nMultiWndWidth  = 1;
	int nMultiWndHeight = 1;
	if (struOneAidRule.struSizeFilter.byMode == IMAGE_PIX_MODE)
	{
		nMultiWndWidth  = m_rcPlayWnd.Width();
		nMultiWndHeight = m_rcPlayWnd.Height();
	}

    m_nMinRectHeight = struOneAidRule.struSizeFilter.struMiniRect.fHeight * nMultiWndHeight;
	m_nMinRectWidth  = struOneAidRule.struSizeFilter.struMiniRect.fWidth  * nMultiWndWidth;
	m_nMaxRectHeight = struOneAidRule.struSizeFilter.struMaxRect.fHeight  * nMultiWndHeight;
    m_nMaxRectWidth  = struOneAidRule.struSizeFilter.struMaxRect.fWidth   * nMultiWndWidth;
    
	m_struMinRect[m_nCurSceneIndex][m_nCurRuleIndex] = struOneAidRule.struSizeFilter.struMiniRect;
	m_struMaxRect[m_nCurSceneIndex][m_nCurRuleIndex] = struOneAidRule.struSizeFilter.struMaxRect;
   
	UpdateData(FALSE);
    
	OnSelchangeComboSizefilterMode();
	OnCheckSizefilterEnable();
}

void CDlgVcaSceneAidRuleCfg::SaveWndRuleContent(int nSceneIndex,int nRuleIndex)
{
	UpdateData(TRUE);
	
    int i = 0;
	
	NET_DVR_ONE_AID_RULE_V41& struOneAidRule = m_struAIDRuleCfg[nSceneIndex].struAIDRule[nRuleIndex];
	struOneAidRule.byEnable = m_bRuleActive;
	strncpy((char*)struOneAidRule.byRuleName, m_strRuleName.GetBuffer(0), sizeof(struOneAidRule.byRuleName));
    
	struOneAidRule.dwEventType = 0;
	int nAidTypeCount = m_listAIDType.GetCount();
	for (i = 0; i < nAidTypeCount; i++)
	{
		if (m_listAIDType.GetCheck(i))
		{
			struOneAidRule.dwEventType |= m_listAIDType.GetItemData(i);
		}
	}

    memcpy(&struOneAidRule.struPolygon, &m_struCurRulePolygon, sizeof(struOneAidRule.struPolygon));
	
	struOneAidRule.struAIDParam.wParkingDuration       = m_nParking;
    struOneAidRule.struAIDParam.wPedestrianDuration    = m_nPedestrian;
    struOneAidRule.struAIDParam.wDebrisDuration        = m_nDebris;
    struOneAidRule.struAIDParam.wCongestionLength      = m_nCongestionLength;
    struOneAidRule.struAIDParam.wCongestionDuration    = m_nCongestionDuration;
    struOneAidRule.struAIDParam.wInverseDuration       = m_nInverseDuration;
    struOneAidRule.struAIDParam.wInverseDistance       = m_nInverseDistance;
    struOneAidRule.struAIDParam.wInverseAngleTolerance = m_nInverseAngle;
	struOneAidRule.struAIDParam.wIllegalParkingTime    = m_nIllegalParkingTime;
	struOneAidRule.struAIDParam.wIllegalParkingPicNum  = m_nIllegalParkingPicNum;
	struOneAidRule.struAIDParam.byMergePic             = m_bMergePic;
	
	struOneAidRule.struHandleType.dwHandleType = 0;

	
	if (m_bHandleType_Monitor)
	{
		struOneAidRule.struHandleType.dwHandleType |= 0x01;
	}
	if (m_bHandleType_Sound)
	{
		struOneAidRule.struHandleType.dwHandleType |= 0x02;
	}

	if (m_bHandleType_Upload)
	{
		struOneAidRule.struHandleType.dwHandleType |= 0x04;
	}

	if (m_bHandleType_Output)
	{
		struOneAidRule.struHandleType.dwHandleType |= 0x08;
	}

	if (m_bHandleType_EmailJpg)
	{
		struOneAidRule.struHandleType.dwHandleType |= 0x10;
	}
    

    for (i = 0; i < MAX_ALARMOUT_V30; i++)
    {   
		if (i >= m_listAlarmOutputChan.GetCount())
		{
			break;
		}
        struOneAidRule.struHandleType.byRelAlarmOut[i] = m_listAlarmOutputChan.GetCheck(i);
    }
    
	int nChannelnumber = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;
	for (i = 0; i < nChannelnumber; i++)
    {
        struOneAidRule.byRelRecordChan[i] = m_listRecordChan.GetCheck(i);
    }
	 
	int nFilterModeIndex = m_comboSizeFilterMode.GetCurSel();

	struOneAidRule.struSizeFilter.byActive = m_bSizeFilterEnable;
    struOneAidRule.struSizeFilter.byMode   = m_comboSizeFilterMode.GetItemData(nFilterModeIndex);
    
	struOneAidRule.struSizeFilter.struMaxRect  = m_struMaxRect[m_nCurSceneIndex][m_nCurRuleIndex];
    struOneAidRule.struSizeFilter.struMiniRect = m_struMinRect[m_nCurSceneIndex][m_nCurRuleIndex];
	if (struOneAidRule.struSizeFilter.byMode == REAL_WORLD_MODE)
	{
		struOneAidRule.struSizeFilter.struMiniRect.fHeight = m_nMinRectHeight;
		struOneAidRule.struSizeFilter.struMiniRect.fWidth  = m_nMinRectWidth;
		struOneAidRule.struSizeFilter.struMaxRect.fHeight  = m_nMaxRectHeight;
        struOneAidRule.struSizeFilter.struMaxRect.fWidth   = m_nMaxRectWidth;
	}
}


void CDlgVcaSceneAidRuleCfg::LoadWndSceneContent(int nSceneIndex)
{   
	if (!GetAIDRuleCfg())
	{   
		char szError[32] = "\0";
		g_StringLanType(szError, "获取事件规则失败", "Get AID rule cfg failed!");
		AfxMessageBox(szError);
	}

	if (!GetLaneCfg())
	{
		char szError[32] = "\0";
		g_StringLanType(szError, "获取车道信息失败", "Get lane cfg failed!");
		AfxMessageBox(szError);
	}

	m_comboProPicType.SetCurSel(m_struAIDRuleCfg[nSceneIndex].byPicProType);
	m_comboPicResolution.SetCurSel(m_struAIDRuleCfg[nSceneIndex].struPictureParam.wPicSize);
	m_comboPicQuality.SetCurSel(m_struAIDRuleCfg[nSceneIndex].struPictureParam.wPicQuality);
    
	m_comboRuleIndex.SetCurSel(0);
	m_comboScene.SetCurSel(nSceneIndex);
	m_nCurRuleIndex = 0;
	LoadWndRuleContent(nSceneIndex,m_nCurRuleIndex);

	UpdateData(FALSE);

	//Change to current scene ptz pos
	ChangeScene(m_struSceneCfg.struSceneCfg[m_nCurSceneIndex].struPtzPos);
}

void CDlgVcaSceneAidRuleCfg::SaveWndSceneContent(int nSceneIndex)
{   
	UpdateData(TRUE);

	m_struAIDRuleCfg[nSceneIndex].byPicProType                 = m_comboProPicType.GetCurSel(); 
    m_struAIDRuleCfg[nSceneIndex].struPictureParam.wPicSize    = m_comboPicResolution.GetCurSel();
    m_struAIDRuleCfg[nSceneIndex].struPictureParam.wPicQuality = m_comboPicQuality.GetCurSel();


	SaveWndRuleContent(nSceneIndex,m_nCurRuleIndex);
}
