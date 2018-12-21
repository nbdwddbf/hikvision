// DlgMobileTriggerCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMobileTriggerCfg.h"
#include "DrawFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgMobileTriggerCfg *lpMobileDlg = NULL;
/////////////////////////////////////////////////////////////////////////////
// CDlgMobileTriggerCfg dialog


CDlgMobileTriggerCfg::CDlgMobileTriggerCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMobileTriggerCfg::IDD, pParent)
	, m_bChkBackRecog(FALSE)
	, m_bChkForWardRecog(FALSE)
	, m_bBoundaryLine(FALSE)
	, m_bCleanPloygon(FALSE)
	, m_bDriveLine(FALSE)
	, m_bIllegalPark(FALSE)
	, m_bLaneLine1(FALSE)
	, m_bLaneLine2(FALSE)
	, m_bPolygon(FALSE)
	, m_bReverseDrive(FALSE)
	, m_bShowPolygon(TRUE)
	, m_dwInterval1(0)
	, m_dwInterval2(0)
{
	//{{AFX_DATA_INIT(CDlgMobileTriggerCfg)
	m_bChkEnable = FALSE;
	m_bChkHoldSpecialRoad = FALSE;
	m_bChkBigCar = FALSE;
	m_bChkCarPressRoad = FALSE;
	m_bChkPost = FALSE;
	m_bChkPost2 = FALSE;
	m_bChkPressRoad = FALSE;
	m_bChkRecordEnable = FALSE;
	m_dwOverRecordTime = 0;
	m_dwCapNum = 0;
	m_dwPreRecordTime = 0;
	//}}AFX_DATA_INIT
    m_lServerID = -1; // 用户ID
    m_iDevIndex = -1; // 设备索引
	m_lChannel  = -1;	
	m_lPlayHandle = -1;
	m_dwPosNum = -1;
	m_bCloseIn = FALSE;
    m_bPolygonMouseMove = FALSE;
	m_bMouseMove = FALSE;

	memset(&m_struLaneLine1, 0, sizeof(m_struLaneLine1));
	memset(&m_struLaneLine2, 0, sizeof(m_struLaneLine2));
	memset(&m_struPolygon, 0, sizeof(m_struPolygon));
	memset(&m_struLaneBoundaryLine, 0, sizeof(m_struLaneBoundaryLine));
    memset(&m_struTrigger, 0, sizeof(m_struTrigger));

}


void CDlgMobileTriggerCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMobileTriggerCfg)
	DDX_Control(pDX, IDC_COMBO_SCENE_MODE, m_comboSceneMode);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bChkEnable);
	DDX_Check(pDX, IDC_CHK_HOLD_SPECIALROAD, m_bChkHoldSpecialRoad);
	DDX_Check(pDX, IDC_CHK_BIGCAR, m_bChkBigCar);
	DDX_Check(pDX, IDC_CHK_CARPRESS_ROAD, m_bChkCarPressRoad);
	DDX_Check(pDX, IDC_CHK_POST, m_bChkPost);
	DDX_Check(pDX, IDC_CHK_POST2, m_bChkPost2);
	DDX_Check(pDX, IDC_CHK_PRESS_ROAD, m_bChkPressRoad);
	DDX_Check(pDX, IDC_CHK_RECORD_ENABLE, m_bChkRecordEnable);
	DDX_Text(pDX, IDC_EDIT_OVERRECORD_TIME, m_dwOverRecordTime);
	DDX_Text(pDX, IDC_EDIT_CAP_NUM, m_dwCapNum);
	DDX_Text(pDX, IDC_EDIT_PRERECORD_TIME, m_dwPreRecordTime);
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_CHK_BACK_RECOG, m_bChkBackRecog);
	DDX_Check(pDX, IDC_CHK_FORWARD_RECOG, m_bChkForWardRecog);
	DDX_Check(pDX, IDC_CHk_BOUNDARYLINE, m_bBoundaryLine);
	DDX_Check(pDX, IDC_CHK_CLEAN_PLOYGON, m_bCleanPloygon);
	DDX_Check(pDX, IDC_CHK_DRIVE_LINE, m_bDriveLine);
	DDX_Check(pDX, IDC_CHK_ILLEGAL_PARK, m_bIllegalPark);
	DDX_Check(pDX, IDC_CHK_LANELINE1, m_bLaneLine1);
	DDX_Check(pDX, IDC_CHK_LANELINE2, m_bLaneLine2);
	DDX_Check(pDX, IDC_CHK_POLYGON, m_bPolygon);
	DDX_Check(pDX, IDC_CHK_REVERSE_DRIVE, m_bReverseDrive);
	DDX_Check(pDX, IDC_CHK_SHOW_POLYGON, m_bShowPolygon);
	DDX_Control(pDX, IDC_COMBO_LANE_DIR, m_comLaneDir);
	DDX_Control(pDX, IDC_COMBO_INTERVAL_TYPE, m_comboIntervalType);
	DDX_Text(pDX, IDC_EDIT_INTERVAL2, m_dwInterval2);
	DDX_Text(pDX, IDC_EDIT_INTERVAL1, m_dwInterval1);
}


BEGIN_MESSAGE_MAP(CDlgMobileTriggerCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgMobileTriggerCfg)
	ON_BN_CLICKED(IDC_BRN_GET, OnBrnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_CBN_SELCHANGE(IDC_COMBO_SCENE_MODE, OnSelchangeComboSceneMode)
	ON_BN_CLICKED(IDC_CHK_CARPRESS_ROAD, OnChkCarpressRoad)
	ON_BN_CLICKED(IDC_CHK_HOLD_SPECIALROAD, OnChkHoldSpecialroad)
	ON_BN_CLICKED(IDC_CHK_POST2, OnChkPost2)
	ON_BN_CLICKED(IDC_CHK_POST, OnChkPost)
	ON_BN_CLICKED(IDC_CHK_BIGCAR, OnChkBigcar)
	ON_BN_CLICKED(IDC_CHK_PRESS_ROAD, OnChkPressRoad)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHK_FORWARD_RECOG, &CDlgMobileTriggerCfg::OnBnClickedChkForwardRecog)
	ON_BN_CLICKED(IDC_CHK_BACK_RECOG, &CDlgMobileTriggerCfg::OnBnClickedChkBackRecog)
	ON_BN_CLICKED(IDC_CHK_SHOW_POLYGON, &CDlgMobileTriggerCfg::OnBnClickedChkShowPolygon)
	ON_BN_CLICKED(IDC_CHK_CLEAN_PLOYGON, &CDlgMobileTriggerCfg::OnBnClickedChkCleanPloygon)
	ON_BN_CLICKED(IDC_CHK_LANELINE1, &CDlgMobileTriggerCfg::OnBnClickedChkLaneline1)
	ON_BN_CLICKED(IDC_CHK_LANELINE2, &CDlgMobileTriggerCfg::OnBnClickedChkLaneline2)
	ON_BN_CLICKED(IDC_CHk_BOUNDARYLINE, &CDlgMobileTriggerCfg::OnBnClickedChkBoundaryline)
	ON_BN_CLICKED(IDC_CHK_POLYGON, &CDlgMobileTriggerCfg::OnBnClickedChkPolygon)
	ON_CBN_SELCHANGE(IDC_COMBO_INTERVAL_TYPE, &CDlgMobileTriggerCfg::OnCbnSelchangeComboIntervalType)
	ON_BN_CLICKED(IDC_CHK_DRIVE_LINE, &CDlgMobileTriggerCfg::OnBnClickedChkDriveLine)
	ON_BN_CLICKED(IDC_CHK_REVERSE_DRIVE, &CDlgMobileTriggerCfg::OnBnClickedChkReverseDrive)
	ON_BN_CLICKED(IDC_CHK_ILLEGAL_PARK, &CDlgMobileTriggerCfg::OnBnClickedChkIllegalPark)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMobileTriggerCfg message handlers

void CALLBACK DrawMobileAlertShow(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
	SetBkMode(hDc, TRANSPARENT);
	SetTextColor(hDc, RGB(255, 255, 255));

	lpMobileDlg->F_DrawFun(lRealHandle, hDc, dwUser);
}

void CDlgMobileTriggerCfg::F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser)
{
	DRAW_POLYGON_PARAM struPolygonParam = {0};
		
	if (m_bPolygon || m_bShowPolygon) //牌识区域
	{
		DRAW_POLYGON_PARAM struPolygonParam;
		memset(&struPolygonParam, 0, sizeof(struPolygonParam));
		struPolygonParam.color = RGB(255, 255, 0);
		memcpy(&struPolygonParam.rcWnd, &m_rcWnd, sizeof(m_rcWnd));
		memcpy(&struPolygonParam.struVcaPolygon, &m_struPolygon, sizeof(struPolygonParam.struVcaPolygon));
		struPolygonParam.bCloseIn = m_bCloseIn;
		struPolygonParam.bMouseMove = m_bPolygonMouseMove;

		CDrawFun::DrawVcaPolygon(hDc, &struPolygonParam);
	}

	DRAW_LINE_PARAM  struLaneBoundaryParam = {0};
	if (m_bBoundaryLine || m_bShowPolygon)//车道右边界线
	{
		if ((m_struLaneBoundaryLine.struLine.struStart.fX != 0 \
			|| m_struLaneBoundaryLine.struLine.struStart.fY != 0 || m_struLaneBoundaryLine.struLine.struEnd.fX != 0 \
			|| m_struLaneBoundaryLine.struLine.struEnd.fY != 0))
		{
			struLaneBoundaryParam.color = RGB(255, 0, 255);
			memcpy(&struLaneBoundaryParam.rcWnd, m_rcWnd, sizeof(struLaneBoundaryParam.rcWnd));
			memcpy(&struLaneBoundaryParam.struVcaLine, &m_struLaneBoundaryLine.struLine, sizeof(struLaneBoundaryParam.struVcaLine));
			CDrawFun::DrawLine(hDc, &struLaneBoundaryParam);
		}
	}

	memset(&struLaneBoundaryParam, 0, sizeof(struLaneBoundaryParam));
	if (m_bLaneLine1 || m_bShowPolygon)//车道线1
	{
		if ((m_struLaneLine1.struLine.struStart.fX != 0 \
			|| m_struLaneLine1.struLine.struStart.fY != 0 \
			|| m_struLaneLine1.struLine.struEnd.fX != 0 \
			|| m_struLaneLine1.struLine.struEnd.fY != 0))
		{
			struLaneBoundaryParam.color = RGB(255, 255, 0);
			memcpy(&struLaneBoundaryParam.rcWnd, m_rcWnd, sizeof(struLaneBoundaryParam.rcWnd));
			memcpy(&struLaneBoundaryParam.struVcaLine, &m_struLaneLine1.struLine, sizeof(struLaneBoundaryParam.struVcaLine));
			CDrawFun::DrawLine(hDc, &struLaneBoundaryParam);
		}
	}

	memset(&struLaneBoundaryParam, 0, sizeof(struLaneBoundaryParam));
	if (m_bLaneLine2 || m_bShowPolygon)//车道线2
	{
		if ((m_struLaneLine2.struLine.struStart.fX != 0 \
			|| m_struLaneLine2.struLine.struStart.fY != 0 \
			|| m_struLaneLine2.struLine.struEnd.fX != 0 \
			|| m_struLaneLine2.struLine.struEnd.fY != 0))
		{
			struLaneBoundaryParam.color = RGB(255, 0, 0);
			memcpy(&struLaneBoundaryParam.rcWnd, m_rcWnd, sizeof(struLaneBoundaryParam.rcWnd));
			memcpy(&struLaneBoundaryParam.struVcaLine, &m_struLaneLine2.struLine, sizeof(struLaneBoundaryParam.struVcaLine));
			CDrawFun::DrawLine(hDc, &struLaneBoundaryParam);
		}
	}

}

BOOL CDlgMobileTriggerCfg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	CPoint pt(0, 0);
	GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWnd);
	GetCursorPos(&pt);
	ScreenToClient(&m_rcWnd);
	ScreenToClient(&pt);

	if (m_bPolygon)//牌识区域 
	{
		PreDrawPolygonMsg(pMsg, pt, &m_struPolygon);
	}

	if (m_bBoundaryLine)//车道右边界线
	{
		PreDrawLineMsg(pMsg, pt, &m_struLaneBoundaryLine.struLine);
	}

	if (m_bLaneLine1) //车道线1
	{
		PreDrawLineMsg(pMsg, pt, &m_struLaneLine1.struLine);
	}

	if (m_bLaneLine2)//车道线2
	{
		PreDrawLineMsg(pMsg, pt, &m_struLaneLine2.struLine);
	}

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CDlgMobileTriggerCfg::PreDrawLineMsg(MSG* pMsg, CPoint &pt, LPNET_VCA_LINE pStruLine)
{
	CString strTemp = _T("");
	DWORD i = 0;
	BOOL bOneLine = TRUE, bXOneLine = TRUE, bYOneLine = TRUE;

	switch (pMsg->message)  // Message of Draw
	{
	case WM_LBUTTONDOWN:
		if ((GetAsyncKeyState(VK_LCONTROL) < 0 || GetAsyncKeyState(VK_RCONTROL) < 0))
		{
			if (PtInRect(&m_rcWnd, pt))
			{

				if (!m_bMouseMove)
				{
					pStruLine->struStart.fX = (float)(pt.x - m_rcWnd.left) / (float)m_rcWnd.Width();
					pStruLine->struStart.fY = (float)(pt.y - m_rcWnd.top) / (float)m_rcWnd.Height();
					pStruLine->struEnd.fX = (float)(pt.x - m_rcWnd.left) / (float)m_rcWnd.Width();
					pStruLine->struEnd.fY = (float)(pt.y - m_rcWnd.top) / (float)m_rcWnd.Height();
					m_bMouseMove = TRUE;
				}
				else
				{
					if ((float)(pt.x - m_rcWnd.left) / (float)m_rcWnd.Width() <= pStruLine->struStart.fX + 0.01 && (float)(pt.x - m_rcWnd.left) / (float)m_rcWnd.Width() >= pStruLine->struStart.fX - 0.01\
						&& (float)(pt.y - m_rcWnd.top) / (float)m_rcWnd.Height() <= pStruLine->struStart.fY + 0.01 && (float)(pt.y - m_rcWnd.top) / (float)m_rcWnd.Height() >= pStruLine->struStart.fY - 0.01)
					{
						char szLan[128] = { 0 };
						g_StringLanType(szLan, "不能连续在同一点上画区域", "Can't draw region on the point used");
						AfxMessageBox(szLan);
						return TRUE;
					}
					pStruLine->struEnd.fX = (float)(pt.x - m_rcWnd.left) / (float)m_rcWnd.Width();
					pStruLine->struEnd.fY = (float)(pt.y - m_rcWnd.top) / (float)m_rcWnd.Height();
					m_bMouseMove = FALSE;
				}

			}
			else
			{
				return TRUE;
			}
		}
		break;
	case WM_MOUSEMOVE:
		if ((GetAsyncKeyState(VK_LCONTROL) < 0 || GetAsyncKeyState(VK_RCONTROL) < 0))
		{
			if (PtInRect(&m_rcWnd, pt))
			{

				if (m_bMouseMove)
				{
					pStruLine->struEnd.fX = (float)(pt.x - m_rcWnd.left) / (float)m_rcWnd.Width();
					pStruLine->struEnd.fY = (float)(pt.y - m_rcWnd.top) / (float)m_rcWnd.Height();
				}

			}
		}
		break;
	case WM_RBUTTONDOWN://Click right mouse to close the rectangle. 
		break;
	default:
		break;
	}
	return TRUE;
}


BOOL CDlgMobileTriggerCfg::PreDrawPolygonMsg(MSG* pMsg, CPoint &pt, LPNET_ITC_POLYGON pStruPolygon)
{
	int i = 0;
	BOOL bOneLine = TRUE, bXOneLine = TRUE, bYOneLine = TRUE;

	switch (pMsg->message)
	{
	case WM_LBUTTONDOWN:
		if ((GetAsyncKeyState(VK_LCONTROL) < 0 || GetAsyncKeyState(VK_RCONTROL)<0) &&
			PtInRect(&m_rcWnd, pt))
		{

			if (m_dwPosNum > 19)
			{
				m_bCloseIn = TRUE;
			}
			if (m_bCloseIn)
			{
				m_dwPosNum = 0;
				pStruPolygon->dwPointNum = m_dwPosNum;
				memset(pStruPolygon, 0, sizeof(NET_ITC_POLYGON));
			}
			if (m_dwPosNum > 19)
			{
				char szLan[128] = { 0 };
				g_StringLanType(szLan, "多边形顶点不能超过20个!", "Apexes of polygon should less than 20");
				AfxMessageBox(szLan);
				return TRUE;
			}
			if ((float)(pt.x - m_rcWnd.left) / (float)m_rcWnd.Width() <= pStruPolygon->struPos[m_dwPosNum - 1].fX + 0.01 && (float)(pt.x - m_rcWnd.left) / (float)m_rcWnd.Width() >= pStruPolygon->struPos[m_dwPosNum - 1].fX - 0.01\
				&& (float)(pt.y - m_rcWnd.top) / (float)m_rcWnd.Height() <= pStruPolygon->struPos[m_dwPosNum - 1].fY + 0.01 && (float)(pt.y - m_rcWnd.top) / (float)m_rcWnd.Height() >= pStruPolygon->struPos[m_dwPosNum - 1].fY - 0.01)
			{
				char szLan[128] = { 0 };
				g_StringLanType(szLan, "不能连续在同一点上画区域", "Can't draw region on the point used");
				AfxMessageBox(szLan);
				return TRUE;
			}
			m_bCloseIn = FALSE;
			m_bPolygonMouseMove = FALSE;
			pStruPolygon->struPos[m_dwPosNum].fX = (float)(pt.x - m_rcWnd.left) / (float)m_rcWnd.Width();
			pStruPolygon->struPos[m_dwPosNum].fY = (float)(pt.y - m_rcWnd.top) / (float)m_rcWnd.Height();
			m_dwPosNum++;
			pStruPolygon->dwPointNum = m_dwPosNum;

		}
		break;
	case WM_MOUSEMOVE:
		if ((GetAsyncKeyState(VK_LCONTROL) < 0 || GetAsyncKeyState(VK_RCONTROL)<0) &&
			PtInRect(&m_rcWnd, pt))
		{

			if (PtInRect(&m_rcWnd, pt))
			{
				if (m_dwPosNum > 19)
				{
					return TRUE;
				}
				if (!m_bCloseIn)
				{
					m_bPolygonMouseMove = TRUE;
					pStruPolygon->struPos[m_dwPosNum].fX = (float)(pt.x - m_rcWnd.left) / (float)m_rcWnd.Width();
					pStruPolygon->struPos[m_dwPosNum].fY = (float)(pt.y - m_rcWnd.top) / (float)m_rcWnd.Height();
					pStruPolygon->dwPointNum = m_dwPosNum + 1;
				}
			}

		}
		break;
	case WM_RBUTTONDOWN:
		if ((GetAsyncKeyState(VK_LCONTROL) < 0 || GetAsyncKeyState(VK_RCONTROL)<0)
			&& PtInRect(&m_rcWnd, pt))
		{
			if (m_dwPosNum > 19)
			{
				return TRUE;
			}
			for (i = 0; i < m_dwPosNum; i++)
			{
				if (pStruPolygon->struPos[i].fX != pStruPolygon->struPos[i + 1].fX)
				{
					bXOneLine = FALSE;
					break;
				}
			}
			for (i = 0; i < m_dwPosNum; i++)
			{
				if (pStruPolygon->struPos[i].fY != pStruPolygon->struPos[i + 1].fY)
				{
					bYOneLine = FALSE;
					break;
				}
			}
			bOneLine = bXOneLine || bYOneLine;
			if (bOneLine)
			{
				char szlan[128] = { 0 };
				g_StringLanType(szlan, "所画点成一线，无法构成区域!", "The points is on a line and can't create a rectangle!");
				AfxMessageBox(szlan);
				return TRUE;
			}

			if (!m_bCloseIn)
			{
				if (m_bPolygonMouseMove)
				{
					m_bPolygonMouseMove = FALSE;
					pStruPolygon->dwPointNum--;
					pStruPolygon->struPos[pStruPolygon->dwPointNum].fX = 0;
					pStruPolygon->struPos[pStruPolygon->dwPointNum].fY = 0;
				}
				m_bCloseIn = TRUE;
			}

		}
		break;
	}
	return TRUE;
}


void CDlgMobileTriggerCfg::OnBrnGet() 
{
	// TODO: Add your control notification handler code here
//    DWORD dwStatus = 0;
	DWORD dwReturn = 0;
//     int iChannel = 1;
//     NET_DVR_TRIGGER_COND struTriggerCond = {0};
//     struTriggerCond.dwSize = sizeof(struTriggerCond);
//     struTriggerCond.dwChannel = 1;
//     struTriggerCond.dwTriggerMode = ITC_POST_MOBILE_TYPE;
    
//     if (!NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_TRIGGEREX_CFG, 1,(LPVOID)&struTriggerCond, sizeof(struTriggerCond),
//         &dwStatus,&m_struTrigger, sizeof(m_struTrigger)))
//     {
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_TRIGGEREX_CFG Chan[%d]", iChannel);
//         return;
//     }
//     else
//     {
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_TRIGGEREX_CFG Chan[%d]", m_lChannel);
//     }

	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_ITC_GET_TRIGGERCFG, ITC_POST_MOBILE_TYPE, &m_struTrigger, sizeof(m_struTrigger), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_ITC_GET_TRIGGERCFG TYPE[%d]", ITC_POST_MOBILE_TYPE);
        return;
    }
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_ITC_GET_TRIGGERCFG TYPE[%d]", ITC_POST_MOBILE_TYPE);
	}

    m_bChkEnable = m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.byEnable;
    m_bChkRecordEnable = m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.byRecordEnable;
    m_dwCapNum = m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.byCapNum;
    m_dwPreRecordTime = m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.dwPreRecordTime;
    m_dwOverRecordTime = m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.dwOverRecordTime;
    m_comboSceneMode.SetCurSel(m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.bySceneMode);
    m_bChkPost = m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.wExpressWayCapType & 0x0001;
    m_bChkBigCar = (m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.wExpressWayCapType >> 1) &0x0001;
    m_bChkPressRoad = (m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.wExpressWayCapType >> 2) &0x0001;

    m_bChkPost2 = (m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.wUrbanRoadCapType >> 0) &0x0001;
    m_bChkCarPressRoad = (m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.wUrbanRoadCapType >> 1) &0x0001;
    m_bChkHoldSpecialRoad = (m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.wUrbanRoadCapType >> 2) &0x0001;
	m_bDriveLine = (m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.wUrbanRoadCapType >> 3) & 0x0001;
	m_bReverseDrive = (m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.wUrbanRoadCapType >> 4) & 0x0001;
	m_bIllegalPark = (m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.wUrbanRoadCapType >> 5) & 0x0001;

	m_comLaneDir.SetCurSel(m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.struLane.byCarDriveDirect - 1);

	m_bChkBackRecog = m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.struPlateRecog.dwRecogMode & 0x0001;
	if (m_bChkBackRecog)
	{
		m_bChkForWardRecog = FALSE;
	}
	else
	{
		m_bChkForWardRecog = TRUE;
	}

	memcpy(&m_struLaneLine1, &m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.struLine[0].struLaneLine, sizeof(m_struLaneLine1));
	memcpy(&m_struLaneLine2, &m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.struLine[1].struLaneLine, sizeof(m_struLaneLine2));
	memcpy(&m_struPolygon, &m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.struPolygon[0], sizeof(m_struPolygon));
	memcpy(&m_struLaneBoundaryLine, &m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.struLaneBoundaryLine, sizeof(m_struLaneBoundaryLine));

	m_comboIntervalType.SetCurSel(m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.struInterval.byIntervalType);
	m_dwInterval1 = m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.struInterval.wInterval[0];
	m_dwInterval2 = m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.struInterval.wInterval[1];
	
    UpdateData(FALSE);

	OnSelchangeComboSceneMode();

    return;
}

void CDlgMobileTriggerCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

//     int iChannel = 1;
//     NET_DVR_TRIGGER_COND struTriggerCond = {0};
//     struTriggerCond.dwSize = sizeof(struTriggerCond);
//     struTriggerCond.dwChannel = 1;
//     struTriggerCond.dwTriggerMode = ITC_POST_MOBILE_TYPE;

    m_struTrigger.dwSize = sizeof(m_struTrigger);
    m_struTrigger.struTriggerParam.dwTriggerType = ITC_POST_MOBILE_TYPE;
    m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.byEnable = m_bChkEnable;
    m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.bySceneMode = m_comboSceneMode.GetCurSel();
    m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.byCapNum = m_dwCapNum;
    m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.byRecordEnable = m_bChkRecordEnable;
    m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.dwPreRecordTime = m_dwPreRecordTime;
    m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.dwOverRecordTime = m_dwOverRecordTime;

	m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.wExpressWayCapType = 0;
    m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.wExpressWayCapType |= m_bChkPost;
    m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.wExpressWayCapType |= (m_bChkBigCar<<1);
    m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.wExpressWayCapType |= (m_bChkPressRoad<<2);

	m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.wUrbanRoadCapType = 0;
    m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.wUrbanRoadCapType |= m_bChkPost2;
    m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.wUrbanRoadCapType |= (m_bChkCarPressRoad<<1);
    m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.wUrbanRoadCapType |= (m_bChkHoldSpecialRoad<<2);
	m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.wUrbanRoadCapType |= (m_bDriveLine << 3);
	m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.wUrbanRoadCapType |= (m_bReverseDrive << 4);
	m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.wUrbanRoadCapType |= (m_bIllegalPark << 5);

	m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.struLane.byCarDriveDirect = m_comLaneDir.GetCurSel() + 1;

	m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.struPlateRecog.dwRecogMode = 0;
	m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.struPlateRecog.dwRecogMode |= (m_bChkBackRecog << 0);


	memcpy(&m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.struLine[0].struLaneLine, &m_struLaneLine1, sizeof(m_struLaneLine1));
	memcpy(&m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.struLine[1].struLaneLine, &m_struLaneLine2, sizeof(m_struLaneLine2));
	memcpy(&m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.struPolygon[0], &m_struPolygon, sizeof(m_struPolygon));
	memcpy(&m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.struLaneBoundaryLine, &m_struLaneBoundaryLine, sizeof(m_struLaneBoundaryLine));

	m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.struInterval.byIntervalType = m_comboIntervalType.GetCurSel();

	m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.struInterval.wInterval[0] = m_dwInterval1;
	m_struTrigger.struTriggerParam.uTriggerParam.struPostMobile.struInterval.wInterval[1] = m_dwInterval2;


    DWORD dwStatus = 0;

	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_ITC_SET_TRIGGERCFG, ITC_POST_MOBILE_TYPE, &m_struTrigger, sizeof(m_struTrigger)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_ITC_SET_TRIGGERCFG TYPE[%d]", ITC_POST_MOBILE_TYPE);
        return;
    }
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_ITC_SET_TRIGGERCFG TYPE[%d]", ITC_POST_MOBILE_TYPE);
	}
    
//     if (!NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_TRIGGEREX_CFG,1,(LPVOID)&struTriggerCond, sizeof(struTriggerCond),
//         &dwStatus,&m_struTrigger, sizeof(m_struTrigger)))
//     {
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_TRIGGEREX_CFG Chan[%d]", iChannel);
//         return;
//     }
//     else
//     {
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_TRIGGEREX_CFG Chan[%d]", iChannel);
//     }

    return;
}

void CDlgMobileTriggerCfg::OnSelchangeComboSceneMode() 
{
	// TODO: Add your control notification handler code here
	if (0 == m_comboSceneMode.GetCurSel())
	{
		GetDlgItem(IDC_CHK_POST)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_BIGCAR)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_PRESS_ROAD)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_POST2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_CARPRESS_ROAD)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_HOLD_SPECIALROAD)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_DRIVE_LINE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_REVERSE_DRIVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_ILLEGAL_PARK)->EnableWindow(FALSE);
	} 
	else
	{
		GetDlgItem(IDC_CHK_POST)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_BIGCAR)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_PRESS_ROAD)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_POST2)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_CARPRESS_ROAD)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_HOLD_SPECIALROAD)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_DRIVE_LINE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_REVERSE_DRIVE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_ILLEGAL_PARK)->EnableWindow(TRUE);
	}
}

void CDlgMobileTriggerCfg::OnChkCarpressRoad() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	if (1 == m_bChkCarPressRoad)
	{
		m_bChkPost2 = 0;
		m_bDriveLine = 0;
		m_bReverseDrive = 0;
		m_bIllegalPark = 0;
		m_bChkHoldSpecialRoad = 0;
	}
	UpdateData(FALSE);

}

void CDlgMobileTriggerCfg::OnChkHoldSpecialroad() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	if (1 == m_bChkHoldSpecialRoad)
	{
		m_bChkPost2 = 0;
		m_bDriveLine = 0;
		m_bReverseDrive = 0;
		m_bIllegalPark = 0;
		m_bChkCarPressRoad = 0;
	}
	UpdateData(FALSE);
}


void CDlgMobileTriggerCfg::OnChkPost2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (1 == m_bChkPost2)
	{
		m_bChkCarPressRoad = 0;
		m_bChkHoldSpecialRoad = 0;
		m_bIllegalPark = 0;
	}
	UpdateData(FALSE);
}

BOOL CDlgMobileTriggerCfg::Play()
{
	char szLan[128] = { 0 };
	char szTemp[256] = { 0 };
	NET_DVR_CLIENTINFO struPlayInfo;
	memset(&struPlayInfo, 0, sizeof(NET_DVR_CLIENTINFO));

	struPlayInfo.hPlayWnd = GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
	struPlayInfo.lChannel = 1;
	struPlayInfo.lLinkMode = 0;

	if (m_lPlayHandle >= 0)
	{
		NET_DVR_StopRealPlay(m_lPlayHandle);
		m_lPlayHandle = -1;
	}

	m_lPlayHandle = NET_DVR_RealPlay_V30(m_lServerID, &struPlayInfo, NULL, NULL, TRUE);
	BOOL bRet = FALSE;
	if (m_lPlayHandle < 0)
	{
		g_StringLanType(szLan, "预览失败", "Realplay failed");
		sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
		AfxMessageBox(szTemp);
		return FALSE;
	}

	bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawMobileAlertShow, 0);

	return TRUE;
}


BOOL CDlgMobileTriggerCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
// 	CRect rc(0, 0, 0, 0);
// 	GetParent()->GetClientRect(&rc);
// 	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
// 	MoveWindow(&rc);
	lpMobileDlg = this;
	GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWnd);
	m_bCloseIn = TRUE;

	Play();

	m_comboIntervalType.SetCurSel(0);
	OnCbnSelchangeComboIntervalType();
	m_comboSceneMode.SetCurSel(0);
	m_comLaneDir.SetCurSel(0);
	OnBrnGet();
	OnBnClickedChkShowPolygon();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMobileTriggerCfg::OnChkPost() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (1 == m_bChkPost)
	{
		m_bChkBigCar = 0;
		m_bChkPressRoad = 0;
	}
	UpdateData(FALSE);
}

void CDlgMobileTriggerCfg::OnChkBigcar() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (1 == m_bChkBigCar)
	{
		m_bChkPost = 0;
	}
	UpdateData(FALSE);
}

void CDlgMobileTriggerCfg::OnChkPressRoad() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (1 == m_bChkPressRoad)
	{
		m_bChkPost = 0;
	}
	UpdateData(FALSE);
}


void CDlgMobileTriggerCfg::OnBnClickedChkForwardRecog()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_bChkForWardRecog)
	{
		m_bChkBackRecog = FALSE;
	}
	else
	{
		m_bChkBackRecog = TRUE;
	}
	UpdateData(FALSE);
}


void CDlgMobileTriggerCfg::OnBnClickedChkBackRecog()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_bChkBackRecog)
	{
		m_bChkForWardRecog = FALSE;
	}
	else
	{
		m_bChkForWardRecog = TRUE;
	}
	UpdateData(FALSE);
}


void CDlgMobileTriggerCfg::OnBnClickedChkShowPolygon()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_bShowPolygon)
	{
		m_dwPosNum = 0;
		m_bCleanPloygon = FALSE;
		m_bLaneLine1 = FALSE;
		m_bLaneLine2 = FALSE;
		m_bBoundaryLine = FALSE;
		m_bPolygon = FALSE;
	}
	UpdateData(FALSE);
}


void CDlgMobileTriggerCfg::OnBnClickedChkCleanPloygon()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_bCleanPloygon)
	{
		m_dwPosNum = 0;
		m_bShowPolygon = FALSE;
		m_bLaneLine1 = FALSE;
		m_bLaneLine2 = FALSE;
		m_bBoundaryLine = FALSE;
		m_bPolygon = FALSE;

		memset(&m_struLaneLine1, 0, sizeof(m_struLaneLine1));
		memset(&m_struLaneLine2, 0, sizeof(m_struLaneLine2));
		memset(&m_struPolygon, 0, sizeof(m_struPolygon));
		memset(&m_struLaneBoundaryLine, 0, sizeof(m_struLaneBoundaryLine));
	}
	UpdateData(FALSE);
}


void CDlgMobileTriggerCfg::OnBnClickedChkLaneline1()
{
	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);
	if (m_bLaneLine1)
	{
		m_dwPosNum = 0;
		m_bShowPolygon = FALSE;
		m_bCleanPloygon = FALSE;
		m_bLaneLine2 = FALSE;
		m_bBoundaryLine = FALSE;
		m_bPolygon = FALSE;
	}
	UpdateData(FALSE);
}


void CDlgMobileTriggerCfg::OnBnClickedChkLaneline2()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_bLaneLine2)
	{
		m_dwPosNum = 0;
		m_bShowPolygon = FALSE;
		m_bCleanPloygon = FALSE;
		m_bLaneLine1 = FALSE;
		m_bBoundaryLine = FALSE;
		m_bPolygon = FALSE;
	}
	UpdateData(FALSE);
}


void CDlgMobileTriggerCfg::OnBnClickedChkBoundaryline()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_bBoundaryLine)
	{
		m_dwPosNum = 0;
		m_bShowPolygon = FALSE;
		m_bCleanPloygon = FALSE;
		m_bLaneLine1 = FALSE;
		m_bLaneLine2 = FALSE;
		m_bPolygon = FALSE;
	}
	UpdateData(FALSE);
}


void CDlgMobileTriggerCfg::OnBnClickedChkPolygon()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_bPolygon)
	{
		m_dwPosNum = 0;
		m_bShowPolygon = FALSE;
		m_bCleanPloygon = FALSE;
		m_bLaneLine1 = FALSE;
		m_bLaneLine2 = FALSE;
		m_bBoundaryLine = FALSE;
	}
	UpdateData(FALSE);
}




void CDlgMobileTriggerCfg::OnCbnSelchangeComboIntervalType()
{
	// TODO:  在此添加控件通知处理程序代码
	int i = m_comboIntervalType.GetCurSel();
	if (0 == i)
	{
		GetDlgItem(IDC_STATIC_INTERVAL_TIME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_INTERVAL_DISTANCE2)->ShowWindow(SW_HIDE);
	}
	else if (1 == i)
	{
		GetDlgItem(IDC_STATIC_INTERVAL_TIME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_INTERVAL_DISTANCE2)->ShowWindow(SW_SHOW);
	}
}


void CDlgMobileTriggerCfg::OnBnClickedChkDriveLine()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (1 == m_bDriveLine)
	{
		m_bChkCarPressRoad = 0;
		m_bChkHoldSpecialRoad = 0;
		m_bIllegalPark = 0;
	}
	UpdateData(FALSE);
}



void CDlgMobileTriggerCfg::OnBnClickedChkReverseDrive()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (1 == m_bReverseDrive)
	{
		m_bChkCarPressRoad = 0;
		m_bChkHoldSpecialRoad = 0;
		m_bIllegalPark = 0;
	}
	UpdateData(FALSE);
}

void CDlgMobileTriggerCfg::OnBnClickedChkIllegalPark()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (1 == m_bIllegalPark)
	{
		m_bChkPost2 = 0;
		m_bDriveLine = 0;
		m_bReverseDrive = 0;
		m_bChkCarPressRoad = 0;
		m_bChkHoldSpecialRoad = 0;
	}
	UpdateData(FALSE);
}
