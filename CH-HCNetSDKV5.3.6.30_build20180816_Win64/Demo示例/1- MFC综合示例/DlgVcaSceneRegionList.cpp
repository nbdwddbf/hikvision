// DlgVcaSceneRegionList.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaSceneRegionList.h"
#include "DrawFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSceneRegionList dialog


void CALLBACK g_DrawSceneRegionList(LONG lRealHandle, HDC hDc, DWORD dwUser)
{  
	CDlgVcaSceneRegionList* pDlgRegionList = (CDlgVcaSceneRegionList*)dwUser;
	if (pDlgRegionList != NULL)
	{
		pDlgRegionList->DrawRegionFun(hDc);
	}
}

#define MAX_POLYGON_POINTNUM 10
#define MIN_POLYGON_POINTNUM 3

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSceneRegionList dialog


CDlgVcaSceneRegionList::CDlgVcaSceneRegionList(int nRegionListType,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaSceneRegionList::IDD, pParent)
	, m_nRegionListType(nRegionListType)
{
	//{{AFX_DATA_INIT(CDlgVcaSceneRegionList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(&m_struSceneRegionList,    0,  sizeof(m_struSceneRegionList));
	memset(&m_struDrawingRgnList,     0,  sizeof(m_struDrawingRgnList));
	memset(&m_struSceneCfg,           0,  sizeof(m_struSceneCfg));
	m_bDrawingRegion  = FALSE;
	m_nCurSceneIndex  = 0;
	m_nCurRegionIndex = 0;
	m_nDrawPointNum   = 0;
}


void CDlgVcaSceneRegionList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaSceneRegionList)
	DDX_Control(pDX, IDC_COMBO_SCENE,       m_comboScene);
	DDX_Control(pDX, IDC_COMBO_REGIONINDEX, m_comboRegionIndex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaSceneRegionList, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaSceneRegionList)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_DRAWREGION,OnBtnDrawRegion)
	ON_BN_CLICKED(IDC_BTN_STOPDRAW,OnBtnStopDraw)
	ON_CBN_SELCHANGE(IDC_COMBO_SCENE,       OnSelchangeComboScene)
	ON_CBN_SELCHANGE(IDC_COMBO_REGIONINDEX, OnSelchangeComboRegionindex)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSceneRegionList message handlers


BOOL CDlgVcaSceneRegionList::OnInitDialog()
{
	CDialog::OnInitDialog();
    
	if (!GetSceneCfg(m_struSceneCfg))
	{   
		char szError[64] = "\0";
		g_StringLanType(szError, "获取场景配置信息失败", "Get Scene cfg failed!");
		AfxMessageBox(szError);
	}

    InitCtrlState();

	StartRealPlay(GetDlgItem(IDC_PLAYWND)->GetSafeHwnd(),g_DrawSceneRegionList,this);

	GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcPlayWnd);
	ScreenToClient(&m_rcPlayWnd);

	LoadSceneRgnWndContent(m_nCurSceneIndex);

	return TRUE;
}

void CDlgVcaSceneRegionList::OnBtnSave() 
{  
	SaveSceneRgnWndContent(m_nCurSceneIndex);
    
	m_struSceneRegionList[m_nCurSceneIndex].byNum = 0;
	for (int i = 0; i < MAX_REGION_NUM; i++)
	{
		if (m_struSceneRegionList[m_nCurSceneIndex].struPolygon[i].dwPointNum > MIN_POLYGON_POINTNUM)
		{
			m_struSceneRegionList[m_nCurSceneIndex].byNum++;
		}
	}

	BOOL bRet = FALSE;
	if (m_nRegionListType == REGIONLIST_TYPE_MASK)
	{
		bRet = SetMaskRegion();
	}
	else if (m_nRegionListType == REGIONLIST_TYPE_REFERENCE)
	{
		bRet = SetReferenceRegion();
	}
    
	char szInfo[32] = "\0";
	if (bRet)
	{
		g_StringLanType(szInfo, "保存成功","Saved successfully");
	}
	else
	{
		g_StringLanType(szInfo, "保存失败","Save failed");
	}
	AfxMessageBox(szInfo);
}


void CDlgVcaSceneRegionList::OnSelchangeComboScene() 
{
	int nCurSel = m_comboScene.GetCurSel();
	if (nCurSel != CB_ERR)
	{   
		SaveSceneRgnWndContent(m_nCurSceneIndex);
		m_nCurSceneIndex = nCurSel;
		LoadSceneRgnWndContent(nCurSel);
	}
}

void CDlgVcaSceneRegionList::OnSelchangeComboRegionindex() 
{
	int nCurSel = m_comboRegionIndex.GetCurSel();
	if (nCurSel != CB_ERR)
	{
		m_nCurRegionIndex = nCurSel;
	}
}

void CDlgVcaSceneRegionList::OnDestroy()
{
	StopRealPlay();
	CDialog::OnDestroy();
}

void CDlgVcaSceneRegionList::InitCtrlState()
{   
	char szTitle[128] = {0};
                   
	if (m_nRegionListType == REGIONLIST_TYPE_MASK)
	{
		 g_StringLanType(szTitle, "屏蔽区域","Mask region");
	}
	else if (m_nRegionListType == REGIONLIST_TYPE_REFERENCE)
	{
		 g_StringLanType(szTitle, "参考区域","Reference region");
	}
	else
	{
		g_StringLanType(szTitle, "多边形区域","Polygon region");
	}
	SetWindowText(szTitle);

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

	for (i = 0; i < MAX_REGION_NUM; i++)
	{
		strItemText.Format(_T("%d"),i + 1);
		m_comboRegionIndex.InsertString(i,strItemText);
	}
}

void CDlgVcaSceneRegionList::OnLButtonDown(UINT nFlags, CPoint point)
{   
	CDialog::OnLButtonDown(nFlags,point);
     
	if (!m_bDrawingRegion)
	{
		return;
	}
	if (!m_rcPlayWnd.PtInRect(point))
	{
		return;
	}

	NET_VCA_POLYGON& struPolygon = m_struDrawingRgnList.struPolygon[m_nCurRegionIndex];

	if (m_nDrawPointNum >= MAX_POLYGON_POINTNUM)
	{
		m_bDrawingRegion = FALSE;
	}
	else
	{
		struPolygon.struPos[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
		struPolygon.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
		m_nDrawPointNum++;
	}
}


void CDlgVcaSceneRegionList::OnRButtonDown(UINT nFlags, CPoint point)
{   
	CDialog::OnRButtonDown(nFlags,point);
	
	if (!m_bDrawingRegion)
	{
		return;
	}
	if (!m_rcPlayWnd.PtInRect(point))
	{
		return;
	}

	NET_VCA_POLYGON& struPolygon = m_struDrawingRgnList.struPolygon[m_nCurRegionIndex];

	if (m_nDrawPointNum < MIN_POLYGON_POINTNUM)
	{
		memset(&struPolygon,0,sizeof(struPolygon));
	}
	else
	{   
		struPolygon.dwPointNum = m_nDrawPointNum;
	}

	m_bDrawingRegion = FALSE;
}

void CDlgVcaSceneRegionList::OnMouseMove(UINT nFlags, CPoint point)
{
	CDialog::OnMouseMove(nFlags,point);
	
	if (!m_bDrawingRegion)
	{
		return;
	}
	if (!m_rcPlayWnd.PtInRect(point))
	{
		return;
	}
	
	NET_VCA_POLYGON& struPolygon = m_struDrawingRgnList.struPolygon[m_nCurRegionIndex];
	
	if (m_nDrawPointNum >= MAX_POLYGON_POINTNUM || m_nDrawPointNum < 1)
	{
		return;
	}
	
	struPolygon.struPos[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
	struPolygon.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
	struPolygon.dwPointNum = m_nDrawPointNum + 1;
}

void CDlgVcaSceneRegionList::DrawRegionFun(HDC hdc)
{
	DRAW_POLYGON_PARAM struPolygonParam;
    memset(&struPolygonParam, 0, sizeof(struPolygonParam));
    char szLan[32];
    for (int i = 0; i < MAX_REGION_NUM; i++)
    {   
		const NET_VCA_POLYGON& struPolygon = m_struDrawingRgnList.struPolygon[i];

		struPolygonParam.rcWnd = m_rcPlayWnd;
        sprintf(szLan, "%d", i + 1);
        memcpy(struPolygonParam.chName, szLan, sizeof(struPolygonParam.chName));

        if (i == m_nCurRegionIndex)
        {   
			struPolygonParam.bCloseIn   = !m_bDrawingRegion;
            struPolygonParam.color = RGB(255, 0, 0);
        }
        else
        {   
			struPolygonParam.bCloseIn   = TRUE;
			struPolygonParam.color = RGB(255, 255, 0);
        }
		struPolygonParam.bMouseMove = FALSE;
        memcpy(&struPolygonParam.struVcaPolygon, &struPolygon, sizeof(struPolygonParam.struVcaPolygon));
        CDrawFun::DrawVcaPolygon(hdc, &struPolygonParam);
    }
}

void CDlgVcaSceneRegionList::OnBtnDrawRegion()
{
	m_bDrawingRegion = TRUE;
	m_nDrawPointNum   = 0;
	memset(&m_struDrawingRgnList.struPolygon[m_nCurRegionIndex],0,sizeof(m_struDrawingRgnList.struPolygon[m_nCurRegionIndex]));
}

void CDlgVcaSceneRegionList::OnBtnStopDraw()
{
	m_bDrawingRegion = FALSE;
	m_struDrawingRgnList.struPolygon[m_nCurRegionIndex].dwPointNum = m_nDrawPointNum;
}


void CDlgVcaSceneRegionList::LoadSceneRgnWndContent(int nSceneIndex)
{
	m_comboRegionIndex.SetCurSel(0);
	m_comboScene.SetCurSel(nSceneIndex);
	m_nCurRegionIndex = 0;
     
	BOOL bRet = FALSE;
	if (m_nRegionListType == REGIONLIST_TYPE_MASK)
	{
		bRet = GetMaskRegion();
	}
	else if (m_nRegionListType == REGIONLIST_TYPE_REFERENCE)
	{
		bRet = GetReferenceRegion();
	}
    
	if (!bRet)
	{   
		char szError[32] = "\0";
		g_StringLanType(szError, "获取区域参数失败", "Get region cfg failed!");
		AfxMessageBox(szError);
	}
	memcpy(&m_struDrawingRgnList,&m_struSceneRegionList[nSceneIndex],sizeof(m_struDrawingRgnList));
    
	//Change to current scene ptz pos
	ChangeScene(m_struSceneCfg.struSceneCfg[m_nCurSceneIndex].struPtzPos);
}

void CDlgVcaSceneRegionList::SaveSceneRgnWndContent(int nSceneIndex)
{
	memcpy(&m_struSceneRegionList[nSceneIndex],&m_struDrawingRgnList,sizeof(m_struSceneRegionList[nSceneIndex]));
}


BOOL CDlgVcaSceneRegionList::SetMaskRegion()
{   
	NET_DVR_SCENE_COND struSceneCond = {0};
	GetSceneCond(struSceneCond);
	
    DWORD dwStatus = 0;
	BOOL bRet      = FALSE;
	
	m_struSceneRegionList[m_nCurSceneIndex].dwSize = sizeof(m_struSceneRegionList[m_nCurSceneIndex]);
    if (!NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_SCENE_MASK_REGION,1,(LPVOID)&struSceneCond, sizeof(struSceneCond),
		&dwStatus,&m_struSceneRegionList[m_nCurSceneIndex], sizeof(m_struSceneRegionList[m_nCurSceneIndex])))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SCENE_MASK_REGION Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SCENE_MASK_REGION Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}


BOOL CDlgVcaSceneRegionList::GetMaskRegion()
{  
	NET_DVR_SCENE_COND struSceneCond = {0};
	GetSceneCond(struSceneCond);
	
	DWORD dwStatus = 0;
	BOOL bRet      = FALSE;

    m_struSceneRegionList[m_nCurSceneIndex].dwSize = sizeof(m_struSceneRegionList[m_nCurSceneIndex]);
    if (!NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_SCENE_MASK_REGION, 1,(LPVOID)&struSceneCond, sizeof(struSceneCond),
		&dwStatus,&m_struSceneRegionList[m_nCurSceneIndex], sizeof(m_struSceneRegionList[m_nCurSceneIndex])))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SCENE_MASK_REGION Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SCENE_MASK_REGION Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
	return bRet;
}

BOOL CDlgVcaSceneRegionList::SetReferenceRegion()
{   
	NET_DVR_SCENE_COND struSceneCond = {0};
	GetSceneCond(struSceneCond);

    DWORD dwStatus = 0;
	BOOL bRet      = FALSE;

	m_struSceneRegionList[m_nCurSceneIndex].dwSize = sizeof(m_struSceneRegionList[m_nCurSceneIndex]);
    if (!NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_SCENE_REFERENCE_REGION,1,(LPVOID)&struSceneCond, sizeof(struSceneCond),
		&dwStatus,&m_struSceneRegionList[m_nCurSceneIndex], sizeof(m_struSceneRegionList[m_nCurSceneIndex])))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SCENE_REFERENCE_REGION Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SCENE_REFERENCE_REGION Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}

BOOL CDlgVcaSceneRegionList::GetReferenceRegion()
{   
	NET_DVR_SCENE_COND struSceneCond = {0};
	GetSceneCond(struSceneCond);

	DWORD dwStatus = 0;
	BOOL bRet      = FALSE;
	
	m_struSceneRegionList[m_nCurSceneIndex].dwSize = sizeof(m_struSceneRegionList[m_nCurSceneIndex]);
    if (!NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_SCENE_REFERENCE_REGION, 1,(LPVOID)&struSceneCond, sizeof(struSceneCond),
		&dwStatus,&m_struSceneRegionList[m_nCurSceneIndex], sizeof(m_struSceneRegionList[m_nCurSceneIndex])))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SCENE_REFERENCE_REGION Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SCENE_REFERENCE_REGION Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
	return bRet;
}


BOOL CDlgVcaSceneRegionList::GetSceneCond(NET_DVR_SCENE_COND& struSceneCond)
{
	struSceneCond.dwSize    = sizeof(struSceneCond);
	struSceneCond.dwSceneID = m_comboScene.GetItemData(m_nCurSceneIndex);
	struSceneCond.lChannel  = m_lChannel;

	return TRUE;
}
