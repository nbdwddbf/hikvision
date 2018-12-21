// DlgVcaSceneITSCalibrate.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaSceneITSCalibrate.h"
#include "DrawFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSceneITSCalibrate dialog


#define MAX_POLYGON_POINTNUM CALIB_PT_NUM
#define MIN_POLYGON_POINTNUM 4
/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSceneITSCalibrate dialog
void CALLBACK g_DrawSceneItsCalibrate(LONG lRealHandle, HDC hDc, DWORD dwUser)
{   
	CDlgVcaSceneITSCalibrate* pDlgCalibrate = (CDlgVcaSceneITSCalibrate*)dwUser;
	if (pDlgCalibrate != NULL)
	{
		pDlgCalibrate->DrawRegionFun(hDc);
	}
}

CDlgVcaSceneITSCalibrate::CDlgVcaSceneITSCalibrate(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaSceneITSCalibrate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaSceneITSCalibrate)
	m_bEnable = FALSE;
	m_fLength = 0;
	m_fWidth = 0;
	//}}AFX_DATA_INIT
	m_nCurSceneIndex  = 0;
	m_bDrawingCaliRgn = FALSE;
	m_nDrawPointNum   = 0;
	memset(m_struSceneCaliCfg,0,sizeof(m_struSceneCaliCfg));
	memset(&m_struSceneCfg,   0,sizeof(m_struSceneCfg));
}


void CDlgVcaSceneITSCalibrate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaSceneITSCalibrate)
	DDX_Control(pDX, IDC_COMBO_SCENE, m_comboScene);
	DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
	DDX_Text(pDX, IDC_EDIT_LENGTH, m_fLength);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_fWidth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaSceneITSCalibrate, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaSceneITSCalibrate)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_CBN_SELCHANGE(IDC_COMBO_SCENE, OnSelchangeComboScene)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_DRAWRGN, OnBtnDrawRgn)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSceneITSCalibrate message handlers
BOOL CDlgVcaSceneITSCalibrate::OnInitDialog()
{
	CDialog::OnInitDialog();
    
	if (!GetSceneCfg(m_struSceneCfg))
	{   
		char szError[64] = "\0";
		g_StringLanType(szError, "获取场景配置信息失败", "Get Scene cfg failed!");
		AfxMessageBox(szError);
	}
	
	InitCtrlState();
	
	StartRealPlay(GetDlgItem(IDC_PLAYWND)->GetSafeHwnd(),g_DrawSceneItsCalibrate,this);
	
	GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcPlayWnd);
	ScreenToClient(&m_rcPlayWnd);

	LoadSceneWndContent(m_nCurSceneIndex);

	return TRUE;
}
void CDlgVcaSceneITSCalibrate::OnBtnSave() 
{
	SaveSceneWndContent(m_nCurSceneIndex);
    
	char szError[32] = "\0";
	if (SetCalibrateCfg())
	{   
		g_StringLanType(szError, "保存成功","Saved successfully");
	}
	else
	{
		g_StringLanType(szError, "保存失败","Save failed");
	}
	AfxMessageBox(szError);
}

void CDlgVcaSceneITSCalibrate::OnSelchangeComboScene() 
{
	int nCurSelIndex = m_comboScene.GetCurSel();

	if (nCurSelIndex != CB_ERR)
	{
		SaveSceneWndContent(m_nCurSceneIndex);
		m_nCurSceneIndex = nCurSelIndex;
		LoadSceneWndContent(nCurSelIndex);
	}
}

void CDlgVcaSceneITSCalibrate::OnDestroy()
{
	StopRealPlay();
	CDialog::OnDestroy();
}

void CDlgVcaSceneITSCalibrate::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDown(nFlags,point);

	if (!m_bDrawingCaliRgn)
	{
		return;
	}
	if (!m_rcPlayWnd.PtInRect(point))
	{
		return;
	}
	
	NET_DVR_ITS_CALIBRATION& struITSCali = m_struSceneCaliCfg[m_nCurSceneIndex].uCalibrateParam.struITSCalibration;
	

	if (m_nDrawPointNum >= MAX_POLYGON_POINTNUM)
	{
		m_bDrawingCaliRgn = FALSE;
	}
	else
	{
		struITSCali.struPoint[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
		struITSCali.struPoint[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
		m_nDrawPointNum++;
	}

	if (m_nDrawPointNum == MAX_POLYGON_POINTNUM)
	{
		m_bDrawingCaliRgn = FALSE;
		struITSCali.dwPointNum = m_nDrawPointNum;
	}
}

void CDlgVcaSceneITSCalibrate::OnRButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnRButtonDown(nFlags,point);

	if (!m_bDrawingCaliRgn)
	{
		return;
	}
	if (!m_rcPlayWnd.PtInRect(point))
	{
		return;
	}
	
	NET_DVR_ITS_CALIBRATION& struITSCali = m_struSceneCaliCfg[m_nCurSceneIndex].uCalibrateParam.struITSCalibration;
	
	if (m_nDrawPointNum < MIN_POLYGON_POINTNUM)
	{
		memset(&struITSCali ,0,sizeof(struITSCali));
	}
	else
	{   
		struITSCali.dwPointNum = m_nDrawPointNum;
	}
	
	m_bDrawingCaliRgn = FALSE;
}

void CDlgVcaSceneITSCalibrate::OnMouseMove(UINT nFlags, CPoint point)
{
	CDialog::OnMouseMove(nFlags,point);

	if (!m_bDrawingCaliRgn)
	{
		return;
	}
	if (!m_rcPlayWnd.PtInRect(point))
	{
		return;
	}

	NET_DVR_ITS_CALIBRATION& struITSCali = m_struSceneCaliCfg[m_nCurSceneIndex].uCalibrateParam.struITSCalibration;

	if (m_nDrawPointNum >= MAX_POLYGON_POINTNUM || m_nDrawPointNum < 1)
	{
		return;
	}
	
	struITSCali.struPoint[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
	struITSCali.struPoint[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
	struITSCali.dwPointNum = m_nDrawPointNum + 1;
}

void CDlgVcaSceneITSCalibrate::OnBtnDrawRgn() 
{
	m_bDrawingCaliRgn = TRUE;
	m_nDrawPointNum   = 0;
	NET_DVR_ITS_CALIBRATION& struITSCali = m_struSceneCaliCfg[m_nCurSceneIndex].uCalibrateParam.struITSCalibration;
	memset(&struITSCali,0,sizeof(struITSCali));
}

void CDlgVcaSceneITSCalibrate::DrawRegionFun(HDC hdc)
{
    DRAW_POLYGON_PARAM struPolygonParam;
    memset(&struPolygonParam, 0, sizeof(struPolygonParam));
    
	NET_VCA_POLYGON strCaliPolygon = {0};
	NET_DVR_ITS_CALIBRATION& struItsCali = m_struSceneCaliCfg[m_nCurSceneIndex].uCalibrateParam.struITSCalibration;
	strCaliPolygon.dwPointNum = struItsCali.dwPointNum;
    memcpy(strCaliPolygon.struPos, struItsCali.struPoint, CALIB_PT_NUM*sizeof(NET_VCA_POINT));
    
    struPolygonParam.bCloseIn   = !m_bDrawingCaliRgn;
    struPolygonParam.bMouseMove = m_bDrawingCaliRgn;
    struPolygonParam.color      =  RGB(255, 255, 0);
    memcpy(&struPolygonParam.rcWnd, &m_rcPlayWnd, sizeof(m_rcPlayWnd));
    memcpy(&struPolygonParam.struVcaPolygon, &strCaliPolygon, sizeof(struPolygonParam.struVcaPolygon));
    CDrawFun::DrawVcaPolygon(hdc, &struPolygonParam);
}

void CDlgVcaSceneITSCalibrate::InitCtrlState()
{   
	int nIndex          = 0;
	CString strItemText = _T("");
	for (int i = 0; i < MAX_ITS_SCENE_NUM; i++)
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


BOOL CDlgVcaSceneITSCalibrate::GetCalibrateCfg()
{
	NET_DVR_SCENE_COND struSceneCond = {0};
	GetSceneCond(struSceneCond);
	
	DWORD dwStatus = 0;
	BOOL bRet      = FALSE;
	
    if (!NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_SCENE_CALIBRATION, 1,(LPVOID)&struSceneCond, sizeof(struSceneCond),
		&dwStatus,&m_struSceneCaliCfg[m_nCurSceneIndex], sizeof(m_struSceneCaliCfg[m_nCurSceneIndex])))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SCENE_CALIBRATION Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SCENE_CALIBRATION Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
	return bRet;
}

BOOL CDlgVcaSceneITSCalibrate::SetCalibrateCfg()
{
	NET_DVR_SCENE_COND struSceneCond = {0};
	GetSceneCond(struSceneCond);
	
    DWORD dwStatus = 0;
	BOOL bRet      = FALSE;
	
    if (!NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_SCENE_CALIBRATION,1,(LPVOID)&struSceneCond, sizeof(struSceneCond),
		&dwStatus,&m_struSceneCaliCfg[m_nCurSceneIndex], sizeof(m_struSceneCaliCfg[m_nCurSceneIndex])))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SCENE_CALIBRATION Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SCENE_CALIBRATION Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}


BOOL CDlgVcaSceneITSCalibrate::GetSceneCond(NET_DVR_SCENE_COND& struSceneCond)
{
	struSceneCond.dwSize    = sizeof(struSceneCond);
	struSceneCond.dwSceneID = m_comboScene.GetItemData(m_nCurSceneIndex);
	struSceneCond.lChannel  = m_lChannel;
	
	return TRUE;
}


void CDlgVcaSceneITSCalibrate::LoadSceneWndContent(int nSceneIndex)
{   
	if (!GetCalibrateCfg())
	{
		char szError[32] = "\0";
		g_StringLanType(szError, "获取标定参数失败", "Get calibration param failed!");
		AfxMessageBox(szError);
	}
    m_comboScene.SetCurSel(nSceneIndex);

	NET_DVR_ITS_CALIBRATION& struITSCali = m_struSceneCaliCfg[m_nCurSceneIndex].uCalibrateParam.struITSCalibration;
	m_bEnable = m_struSceneCaliCfg[m_nCurSceneIndex].byEnable;
	m_fLength = struITSCali.fHeight;
	m_fWidth  = struITSCali.fWidth;
	UpdateData(FALSE);

	//Change to current scene ptz pos
	ChangeScene(m_struSceneCfg.struSceneCfg[m_nCurSceneIndex].struPtzPos);
}

void CDlgVcaSceneITSCalibrate::SaveSceneWndContent(int nSceneIndex)
{
	UpdateData(TRUE);
    
	NET_DVR_ITS_CALIBRATION& struITSCali = m_struSceneCaliCfg[m_nCurSceneIndex].uCalibrateParam.struITSCalibration;
	m_struSceneCaliCfg[m_nCurSceneIndex].byEnable          = m_bEnable;
	m_struSceneCaliCfg[m_nCurSceneIndex].byCalibrationType = ITS_CALBIRETE;
	struITSCali.fHeight  = m_fLength;
	struITSCali.fWidth   = m_fWidth;
}
