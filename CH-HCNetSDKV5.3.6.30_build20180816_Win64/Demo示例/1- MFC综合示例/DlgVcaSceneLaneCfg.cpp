// DlgVcaSceneLaneCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaSceneLaneCfg.h"
#include "DrawFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSceneLaneCfg dialog


#define MAX_RULEPOLYGON_POINT_NUM 10
#define MIN_RULEPOLYGON_POINT_NUM 4
/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSceneLaneCfg dialog

void CALLBACK g_DrawSceneLane(LONG lRealHandle, HDC hDc, DWORD dwUser)
{  
	CDlgVcaSceneLaneCfg* pLaneCfg = (CDlgVcaSceneLaneCfg*)(dwUser);
	if (pLaneCfg != NULL)
	{
		pLaneCfg->DrawSceneLaneFun(hDc);
	}
}

CDlgVcaSceneLaneCfg::CDlgVcaSceneLaneCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaSceneLaneCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaSceneLaneCfg)
	m_strLaneName = _T("");
	//}}AFX_DATA_INIT
    
	memset(m_struSceneLaneCfg,    0, sizeof(m_struSceneLaneCfg));
	memset(m_struDrawingLane,     0, sizeof(m_struDrawingLane));
	memset(&m_struSceneCfg,       0, sizeof(m_struSceneCfg));
	m_nCurSceneIndex      = 0;
	m_nCurLaneIndex       = 0;
	m_nCurDrawType        = DRAW_TYPE_NONE;
	m_bCheckLaneEnable    = FALSE;
	m_bFirstDrawDirection = FALSE;
	m_nDrawPointNum       = 0;

	for (int i = 0; i < MAX_LANE_NUM; i++)
	{
		m_struSceneLaneCfg[i].dwSize = sizeof(m_struSceneLaneCfg[i]);
	}
}


void CDlgVcaSceneLaneCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaSceneLaneCfg)
	DDX_Control(pDX, IDC_COMBO_SCENE, m_comboScene);
	DDX_Control(pDX, IDC_COMBO_LANE, m_comboLane);
	DDX_Text(pDX, IDC_EDIT_LANENAME, m_strLaneName);
	DDX_Check(pDX,IDC_CHECK_LANEENABLE,m_bCheckLaneEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaSceneLaneCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaSceneLaneCfg)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_LANE, OnSelchangeComboLane)
	ON_CBN_SELCHANGE(IDC_COMBO_SCENE, OnSelchangeComboScene)
	ON_BN_CLICKED(IDC_BTN_DRAWDIRECTION, OnBtnDrawdirection)
	ON_BN_CLICKED(IDC_BTN_DRAWLANE, OnBtnDrawlane)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSceneLaneCfg message handlers

BOOL CDlgVcaSceneLaneCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
    
	if (!GetSceneCfg(m_struSceneCfg))
	{   
		char szError[64] = "\0";
		g_StringLanType(szError, "获取场景配置信息失败", "Get Scene cfg failed!");
		AfxMessageBox(szError);
	}

	InitCtrlState();
	
	StartRealPlay(GetDlgItem(IDC_PLAYWND)->GetSafeHwnd(),g_DrawSceneLane,this);
	
	GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcPlayWnd);
	ScreenToClient(&m_rcPlayWnd);

	LoadSceneWndContent(m_nCurSceneIndex);

	return TRUE;
}

void CDlgVcaSceneLaneCfg::OnDestroy()
{   
	StopRealPlay();
	CDialog::OnDestroy();
}

void CDlgVcaSceneLaneCfg::OnSelchangeComboLane() 
{
	int nCurSel = m_comboLane.GetCurSel();
	if (nCurSel != CB_ERR)
	{
		SaveLaneWndContent(m_nCurLaneIndex);
		m_nCurLaneIndex = nCurSel;
		LoadLaneWndContent(nCurSel);
	}
	
}

void CDlgVcaSceneLaneCfg::OnSelchangeComboScene() 
{
	int nCurSel = m_comboScene.GetCurSel();
	if (nCurSel != CB_ERR)
	{   
		SaveSceneWndContent(m_nCurSceneIndex);
		m_nCurSceneIndex = nCurSel;
		LoadSceneWndContent(nCurSel);
	}
}

void CDlgVcaSceneLaneCfg::OnBtnDrawdirection() 
{   
	NET_DVR_DIRECTION & struFlowDirection = m_struDrawingLane[m_nCurLaneIndex].struFlowDirection;
	memset(&struFlowDirection,0,sizeof(struFlowDirection));
	m_nCurDrawType = DRAW_TYPE_DIR;
	m_bFirstDrawDirection = TRUE;
	
}

void CDlgVcaSceneLaneCfg::OnBtnDrawlane() 
{   
	NET_VCA_POLYGON & struPolygon = m_struDrawingLane[m_nCurLaneIndex].struPolygon;
	memset(&struPolygon,0,sizeof(struPolygon));
	m_nCurDrawType = DRAW_TYPE_LANE;
	m_nDrawPointNum = 0;
}

void CDlgVcaSceneLaneCfg::OnBtnSave() 
{
	SaveSceneWndContent(m_nCurSceneIndex);
    
	char szError[32] = "\0";
	if (SetLaneCfg())
	{
		g_StringLanType(szError, "保存成功","Saved successfully");
	}
	else
	{
		g_StringLanType(szError, "保存失败","Save failed");
	}
	AfxMessageBox(szError);
}

void CDlgVcaSceneLaneCfg::OnLButtonDown(UINT nFlags, CPoint point)
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
	
	if (m_nCurDrawType == DRAW_TYPE_LANE)
	{   
		NET_VCA_POLYGON& struPolygon = m_struDrawingLane[m_nCurLaneIndex].struPolygon;
		
		if (m_nDrawPointNum >= MAX_RULEPOLYGON_POINT_NUM)
		{
			m_nCurDrawType = DRAW_TYPE_NONE;
		}
		else
		{
			struPolygon.struPos[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
			struPolygon.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
			m_nDrawPointNum++;
		}
	}
	else if (m_nCurDrawType == DRAW_TYPE_DIR)
	{   
		NET_DVR_DIRECTION& struDirection = m_struDrawingLane[m_nCurLaneIndex].struFlowDirection;

		if (m_bFirstDrawDirection)
		{
			struDirection.struStartPoint.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
            struDirection.struStartPoint.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
			struDirection.struEndPoint.fX   = struDirection.struStartPoint.fX;
            struDirection.struEndPoint.fY   = struDirection.struStartPoint.fY;
			m_bFirstDrawDirection = FALSE;
		}
		else
		{   
			struDirection.struEndPoint.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
            struDirection.struEndPoint.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
			m_nCurDrawType = DRAW_TYPE_NONE;
		}
	}
}

void CDlgVcaSceneLaneCfg::OnRButtonDown(UINT nFlags, CPoint point)
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
	
	if (m_nCurDrawType == DRAW_TYPE_LANE)
	{   
		NET_VCA_POLYGON& struPolygon = m_struDrawingLane[m_nCurLaneIndex].struPolygon;

		if (m_nDrawPointNum < MIN_RULEPOLYGON_POINT_NUM)
		{
			memset(&struPolygon,0,sizeof(struPolygon));
		}
		else
		{   
			struPolygon.dwPointNum = m_nDrawPointNum;
		}
	}
	else if (m_nCurDrawType == DRAW_TYPE_DIR)
	{   
		m_bFirstDrawDirection = FALSE;
	}
	m_nCurDrawType = DRAW_TYPE_NONE;	
}

void CDlgVcaSceneLaneCfg::OnMouseMove(UINT nFlags, CPoint point)
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
	
	if (m_nCurDrawType == DRAW_TYPE_LANE)
	{
		NET_VCA_POLYGON& struPolygon = m_struDrawingLane[m_nCurLaneIndex].struPolygon;
		
		if (m_nDrawPointNum >= MAX_RULEPOLYGON_POINT_NUM || m_nDrawPointNum < 1)
		{
			return;
		}
		struPolygon.struPos[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
		struPolygon.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
	    struPolygon.dwPointNum = m_nDrawPointNum + 1;
	}
	else if (m_nCurDrawType == DRAW_TYPE_DIR)
	{   
		NET_DVR_DIRECTION& struDirection = m_struDrawingLane[m_nCurLaneIndex].struFlowDirection;

		if (!m_bFirstDrawDirection)
		{
			struDirection.struEndPoint.fX = (float)(point.x-m_rcPlayWnd.left)/(float)m_rcPlayWnd.Width();
            struDirection.struEndPoint.fY = (float)(point.y-m_rcPlayWnd.top) /(float)m_rcPlayWnd.Height();
		}
	}
}


void CDlgVcaSceneLaneCfg::InitCtrlState()
{   
	int i               = 0;
	int nIndex          = 0;
	CString strItemText = _T("");
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
		strItemText.Format(_T("%d"),i + 1);
		m_comboLane.InsertString(i,strItemText);
	}
}

void CDlgVcaSceneLaneCfg::DrawSceneLaneFun(HDC hdc)
{
    DRAW_POLYGON_PARAM struPolygonParam;
    memset(&struPolygonParam, 0, sizeof(struPolygonParam));
	
    DRAW_DIRECTION_PARAM struDirectionParam;
    memset(&struDirectionParam, 0, sizeof(struDirectionParam));
    
    for (int i = 0; i < MAX_LANE_NUM; i++)
    {
        if (i == m_nCurLaneIndex)
        {
            struPolygonParam.color = RGB(244,62,0);
            struDirectionParam.color = RGB(244,62,0);
			struPolygonParam.bCloseIn = m_nCurDrawType != DRAW_TYPE_LANE;
        }
        else
        {   
			struPolygonParam.bCloseIn = TRUE;
			struPolygonParam.color = RGB(255, 255, 0);
            struDirectionParam.color = RGB(255,255,0);
        }
        
        struPolygonParam.bMouseMove = FALSE;
		memcpy(&struPolygonParam.rcWnd, &m_rcPlayWnd, sizeof(m_rcPlayWnd));
        memcpy(&struPolygonParam.struVcaPolygon, &m_struDrawingLane[i].struPolygon, sizeof(struPolygonParam.struVcaPolygon));
        strncpy(struPolygonParam.chName, (char*)m_struDrawingLane[i].byLaneName, sizeof(struPolygonParam.chName));
		CDrawFun::DrawVcaPolygon(hdc, &struPolygonParam);
		
		memcpy(&struDirectionParam.rcWnd, &m_rcPlayWnd, sizeof(struDirectionParam.rcWnd));
		memcpy(&struDirectionParam.struDirection, &m_struDrawingLane[i].struFlowDirection, sizeof(struDirectionParam.struDirection));
        CDrawFun::DrawDirection(hdc, &struDirectionParam);
	}
}

void CDlgVcaSceneLaneCfg::LoadSceneWndContent(int nSceneIndex)
{  
	m_comboScene.SetCurSel(nSceneIndex);
	m_comboLane.SetCurSel(0);
	m_nCurLaneIndex = 0;

	if (!GetLaneCfg())
	{   
		char szError[32] = "\0";
		g_StringLanType(szError, "获取车道信息失败", "Get lane cfg failed!");
		AfxMessageBox(szError);
	}

    memcpy(m_struDrawingLane,m_struSceneLaneCfg[nSceneIndex].struLane,sizeof(m_struDrawingLane));
	LoadLaneWndContent(m_nCurLaneIndex);

	//Change to current scene ptz pos
	ChangeScene(m_struSceneCfg.struSceneCfg[m_nCurSceneIndex].struPtzPos);
}

void CDlgVcaSceneLaneCfg::SaveSceneWndContent(int nSceneIndex)
{   
	SaveLaneWndContent(m_nCurLaneIndex);

	memcpy(m_struSceneLaneCfg[nSceneIndex].struLane,m_struDrawingLane,sizeof(m_struSceneLaneCfg[nSceneIndex].struLane));
}

void CDlgVcaSceneLaneCfg::LoadLaneWndContent(int nLaneIndex)
{
	m_bCheckLaneEnable = m_struDrawingLane[nLaneIndex].byEnable;
	m_strLaneName      = m_struDrawingLane[nLaneIndex].byLaneName;

	UpdateData(FALSE);
}

void CDlgVcaSceneLaneCfg::SaveLaneWndContent(int nLaneIndex)
{   
	UpdateData(TRUE);

	strncpy((char*)m_struDrawingLane[nLaneIndex].byLaneName, m_strLaneName.GetBuffer(0), sizeof(m_struDrawingLane[nLaneIndex].byLaneName));
	m_struDrawingLane[nLaneIndex].byEnable = m_bCheckLaneEnable;
}

BOOL CDlgVcaSceneLaneCfg::GetLaneCfg()
{
	NET_DVR_SCENE_COND struSceneCond = {0};
	GetSceneCond(struSceneCond);
	
	DWORD dwStatus = 0;
	BOOL bRet      = FALSE;
	
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


BOOL CDlgVcaSceneLaneCfg::SetLaneCfg()
{
	NET_DVR_SCENE_COND struSceneCond = {0};
	GetSceneCond(struSceneCond);
	
    DWORD dwStatus = 0;
	BOOL bRet      = FALSE;
	
    if (!NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_SCENE_LANECFG,1,(LPVOID)&struSceneCond, sizeof(struSceneCond),
		&dwStatus,&m_struSceneLaneCfg[m_nCurSceneIndex], sizeof(m_struSceneLaneCfg[m_nCurSceneIndex])))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SCENE_LANECFG Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SCENE_LANECFG Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}

BOOL CDlgVcaSceneLaneCfg::GetSceneCond(NET_DVR_SCENE_COND& struSceneCond)
{
	struSceneCond.dwSize    = sizeof(struSceneCond);
	struSceneCond.dwSceneID = m_comboScene.GetItemData(m_nCurSceneIndex);
	struSceneCond.lChannel  = m_lChannel;
	
	return TRUE;
}