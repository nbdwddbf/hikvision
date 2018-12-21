// DlgVcaAuxAreaList.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaAuxAreaList.h"
#include "DrawFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaAuxAreaList dialog

void CALLBACK g_DrawAuxAreaList(LONG lRealHandle, HDC hDc, DWORD dwUser)
{  
	CDlgVcaAuxAreaList* pDlgAreaList = (CDlgVcaAuxAreaList*)dwUser;
	if (pDlgAreaList != NULL)
	{
		pDlgAreaList->DrawAreaFun(hDc);
	}
}

#define MAX_POLYGON_POINTNUM 10
#define MIN_POLYGON_POINTNUM 3


CDlgVcaAuxAreaList::CDlgVcaAuxAreaList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaAuxAreaList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaAuxAreaList)
	m_bEnable = FALSE;
	//}}AFX_DATA_INIT

    m_bDrawingRegion   = FALSE;
    m_nCurRegionIndex  = 0;
	m_nDrawPointNum    = 0;
	memset(&m_struAuxAreaList,0,sizeof(m_struAuxAreaList));
}


void CDlgVcaAuxAreaList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaAuxAreaList)
	DDX_Control(pDX, IDC_COMBO_RGNINDEX, m_comboAreaIndex);
	DDX_Control(pDX, IDC_COMBO_AREATYPE, m_comboAreaType);
	DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaAuxAreaList, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaAuxAreaList)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_RGNINDEX, OnSelchangeComboAreaIndex)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BTN_DRAWREGION, OnBtnDrawRegion)
	ON_BN_CLICKED(IDC_BTN_STOPDRAW, OnBtnStopDraw)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaAuxAreaList message handlers

BOOL CDlgVcaAuxAreaList::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcPlayWnd);
	ScreenToClient(&m_rcPlayWnd);
	StartRealPlay(GetDlgItem(IDC_PLAYWND)->GetSafeHwnd(),g_DrawAuxAreaList,this);
	
	InitCtrlState();
	GetAuxAreaList();
	LoadWndContent(m_nCurRegionIndex);

	return TRUE;
}

void CDlgVcaAuxAreaList::OnDestroy()
{   
	StopRealPlay();
	CDialog::OnDestroy();
}

void CDlgVcaAuxAreaList::OnBtnSave() 
{
	SaveWndContent(m_nCurRegionIndex);
	char szError[32] = "\0";
	if (SetAuxAreaList())
	{
        g_StringLanType(szError, "保存成功","Saved successfully");
	}
	else
	{
		g_StringLanType(szError, "保存失败","Save failed");
	}
	AfxMessageBox(szError);
}


void CDlgVcaAuxAreaList::OnSelchangeComboAreaIndex() 
{
	int nCurSel = m_comboAreaIndex.GetCurSel();
	if (nCurSel != CB_ERR)
	{   
		SaveWndContent(m_nCurRegionIndex);
		m_nCurRegionIndex = nCurSel;
		LoadWndContent(m_nCurRegionIndex);
	}
}


void CDlgVcaAuxAreaList::OnLButtonDown(UINT nFlags, CPoint point)
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
	
	NET_VCA_POLYGON& struPolygon = m_struAuxAreaList.struArea[m_nCurRegionIndex].struPolygon;
	
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


void CDlgVcaAuxAreaList::OnRButtonDown(UINT nFlags, CPoint point)
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
	
	NET_VCA_POLYGON& struPolygon =  m_struAuxAreaList.struArea[m_nCurRegionIndex].struPolygon;
	
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

void CDlgVcaAuxAreaList::OnMouseMove(UINT nFlags, CPoint point)
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
	
	NET_VCA_POLYGON& struPolygon = m_struAuxAreaList.struArea[m_nCurRegionIndex].struPolygon;
	
	if (m_nDrawPointNum >= MAX_POLYGON_POINTNUM || m_nDrawPointNum < 1)
	{
		return;
	}
	
	struPolygon.struPos[m_nDrawPointNum].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
	struPolygon.struPos[m_nDrawPointNum].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
	struPolygon.dwPointNum = m_nDrawPointNum + 1;
}

void CDlgVcaAuxAreaList::OnBtnDrawRegion() 
{
	m_bDrawingRegion = TRUE;
	m_nDrawPointNum   = 0;

	NET_VCA_POLYGON& struPolygon =  m_struAuxAreaList.struArea[m_nCurRegionIndex].struPolygon;
	memset(&struPolygon,0,sizeof(struPolygon));
}

void CDlgVcaAuxAreaList::OnBtnStopDraw() 
{
	m_bDrawingRegion = FALSE;
    
	NET_VCA_POLYGON& struPolygon =  m_struAuxAreaList.struArea[m_nCurRegionIndex].struPolygon;
	if (m_nDrawPointNum >= MIN_POLYGON_POINTNUM)
	{
		struPolygon.dwPointNum = m_nDrawPointNum;
	}
	else
	{
	
     	memset(&struPolygon,0,sizeof(struPolygon));
	}
}

void CDlgVcaAuxAreaList::InitCtrlState()
{
	m_comboAreaIndex.ResetContent();
	m_comboAreaType.ResetContent();
    
	CString strText = "";
	for (int i = 0; i < MAX_AUXAREA_NUM; i++)
	{
		strText.Format("%d",i + 1);
		m_comboAreaIndex.InsertString(i,strText);
		m_comboAreaIndex.SetItemData(i,i);
	}
	
	char szText[64] = "\0";
	g_StringLanType(szText, "共同区域", "Overlap Region");
	m_comboAreaType.InsertString(0,szText);
	m_comboAreaType.SetItemData(0,ENUM_OVERLAP_REGION);
	
	g_StringLanType(szText, "床铺位置", "Bed Location");
	m_comboAreaType.InsertString(1,szText);
	m_comboAreaType.SetItemData(1,ENUM_BED_LOCATION );
	
	m_comboAreaIndex.SetCurSel(0);
	m_comboAreaType.SetCurSel(0);
}

void CDlgVcaAuxAreaList::DrawAreaFun(HDC hdc)
{
	DRAW_POLYGON_PARAM struPolygonParam;
    memset(&struPolygonParam, 0, sizeof(struPolygonParam));
    char szLan[32];
    for (int i = 0; i < MAX_AUXAREA_NUM; i++)
    {   
		const NET_VCA_POLYGON& struPolygon = m_struAuxAreaList.struArea[i].struPolygon;
		
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

void CDlgVcaAuxAreaList::LoadWndContent(int nAreaIndex)
{
	m_bEnable = m_struAuxAreaList.struArea[nAreaIndex].byEnable;
	int nAreaType = m_struAuxAreaList.struArea[nAreaIndex].dwAreaType;

	int nCount = m_comboAreaType.GetCount();
	for (int i = 0; i < nCount; i++)
	{
		if (m_comboAreaType.GetItemData(i) == nAreaType)
		{
			m_comboAreaType.SetCurSel(i);
			break;
		}
	}
	UpdateData(FALSE);
}

void CDlgVcaAuxAreaList::SaveWndContent(int nAreaIndex)
{   
	UpdateData(TRUE);

	m_struAuxAreaList.struArea[nAreaIndex].byEnable = m_bEnable;

	int nAreaTypeIndex = m_comboAreaType.GetCurSel();
	if (nAreaTypeIndex != CB_ERR)
	{
		m_struAuxAreaList.struArea[nAreaIndex].dwAreaType = m_comboAreaType.GetItemData(nAreaTypeIndex);
	}
}

BOOL CDlgVcaAuxAreaList::GetAuxAreaList()
{
	BOOL bRet      = FALSE;
	DWORD dwReturn = 0;
	
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_AUX_AREA,m_lChannel,&m_struAuxAreaList,
		sizeof(m_struAuxAreaList),&dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_AUX_AREA Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_AUX_AREA Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
	return bRet;
}

BOOL CDlgVcaAuxAreaList::SetAuxAreaList()
{
	BOOL bRet      = FALSE;
	
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_AUX_AREA,m_lChannel,&m_struAuxAreaList,
		sizeof(m_struAuxAreaList)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_AUX_AREA Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_AUX_AREA Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
	return bRet;
}