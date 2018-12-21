// DlgImageDiffDetectionCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgImageDiffDetectionCfg.h"
#include "VcaCommonOperations.h"
#include "DrawFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgImageDiffDetectionCfg dialog

void CALLBACK g_DrawThermometricCfgRgn(LONG lRealHandle, HDC hDc, DWORD dwUser)
{  
    CDlgImageDiffDetectionCfg* pDlg = (CDlgImageDiffDetectionCfg*)dwUser;
    if (pDlg != NULL)
    {
        pDlg->DrawRgnFun(hDc);
    }
}

CDlgImageDiffDetectionCfg::CDlgImageDiffDetectionCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgImageDiffDetectionCfg::IDD, pParent)
    , m_iChannel(0)
{
	//{{AFX_DATA_INIT(CDlgImageDiffDetectionCfg)
    m_bCheckEnabled = FALSE;
    m_byThreshold = 0;
    m_bySensitivity = 0;
    m_nCurDrawType = TRUE;
    m_bStart = FALSE;
    memset(&m_struVacPloygon, 0, sizeof(m_struVacPloygon));
	//}}AFX_DATA_INIT
}

CDlgImageDiffDetectionCfg::~CDlgImageDiffDetectionCfg()
{
    CVcaCommonOperations::~CVcaCommonOperations();
    StopRealPlay();
}

void CDlgImageDiffDetectionCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgImageDiffDetectionCfg)

    DDX_Check(pDX, IDC_CHECK_ENABLED, m_bCheckEnabled);

    DDX_Text(pDX, IDC_EDIT_THRESHOLD, m_byThreshold);
    DDX_Text(pDX, IDC_EDIT_SENSITIVITY, m_bySensitivity);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMBO_VIDEO_INPUT_TYPE, m_comboVideoInputType);
}

BOOL CDlgImageDiffDetectionCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
    GetDlgItem(IDC_STATIC_REAL_PLAY)->GetWindowRect(&m_rcPlayWnd);
    ScreenToClient(&m_rcPlayWnd);
    StartRealPlay(GetDlgItem(IDC_STATIC_REAL_PLAY)->GetSafeHwnd(), g_DrawThermometricCfgRgn, this, m_iChannel);
    
    return TRUE;
}


BEGIN_MESSAGE_MAP(CDlgImageDiffDetectionCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgImageDiffDetectionCfg)
	ON_BN_CLICKED(IDC_BUTTON_GET_IMAGE_DIFF_DETECTION_CFG, OnBtnGetImageDiffDetectionCfg)
    ON_BN_CLICKED(IDC_BUTTON_SET_IMAGE_DIFF_DETECTION_CFG, OnBtnSetImageDiffDetectionCfg)
    ON_BN_CLICKED(IDC_BUTTON_CLEAR_FRAME, OnBtnClearFrame)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgImageDiffDetectionCfg message handlers

void CDlgImageDiffDetectionCfg::OnBtnGetImageDiffDetectionCfg()
{
    UpdateData(TRUE);
    NET_DVR_IMAGE_DIFF_DETECTION_CFG struImageDiffDecection = {0};
    struImageDiffDecection.dwSize = sizeof(struImageDiffDecection);
    NET_DVR_STD_CONFIG struCfg = {0};
    DWORD dwChannel = m_iChannel;
    struCfg.lpCondBuffer = &dwChannel;
    struCfg.dwCondSize = sizeof(dwChannel);
    struCfg.lpOutBuffer = &struImageDiffDecection;
    struCfg.dwOutSize = sizeof(struImageDiffDecection);

    if(!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_IMAGE_DIFF_DETECTION_CFG, &struCfg))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_IMAGE_DIFF_DETECTION_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_IMAGE_DIFF_DETECTION_CFG");
    }
    m_bCheckEnabled = struImageDiffDecection.byEnabled;
    m_byThreshold = struImageDiffDecection.byThreshold;
    m_bySensitivity = struImageDiffDecection.bySensitivity;
    memcpy(&m_struVacPloygon, &struImageDiffDecection.struRegion, sizeof(m_struVacPloygon));
    m_comboVideoInputType.SetCurSel(struImageDiffDecection.byVideoInputType);
    UpdateData(FALSE);
}

void CDlgImageDiffDetectionCfg::OnBtnSetImageDiffDetectionCfg()
{
    UpdateData(TRUE);
    NET_DVR_IMAGE_DIFF_DETECTION_CFG struImageDiffDecection = {0};
    struImageDiffDecection.dwSize = sizeof(struImageDiffDecection);
    struImageDiffDecection.byEnabled = m_bCheckEnabled;
    struImageDiffDecection.byThreshold = m_byThreshold;
    struImageDiffDecection.bySensitivity = m_bySensitivity;
    memcpy(&struImageDiffDecection.struRegion, &m_struVacPloygon, sizeof(m_struVacPloygon));
    struImageDiffDecection.byVideoInputType = m_comboVideoInputType.GetCurSel();
    NET_DVR_STD_CONFIG struCfg = {0};
    DWORD dwChannel = m_iChannel;
    struCfg.lpCondBuffer = &dwChannel;
    struCfg.dwCondSize = sizeof(dwChannel);
    struCfg.lpInBuffer = &struImageDiffDecection;
    struCfg.dwInSize = sizeof(struImageDiffDecection);

    if(!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_IMAGE_DIFF_DETECTION_CFG, &struCfg))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_IMAGE_DIFF_DETECTION_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_IMAGE_DIFF_DETECTION_CFG");
    }
    UpdateData(FALSE);
}

void CDlgImageDiffDetectionCfg::OnBtnClearFrame()
{
    memset(&m_struVacPloygon, 0, sizeof(m_struVacPloygon));
}

void CDlgImageDiffDetectionCfg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    if (!m_rcPlayWnd.PtInRect(point) || !m_bStart || m_nCurDrawType == DRAW_TYPE_NONE)
    {
        return;
	}
    m_struVacPloygon.dwPointNum = 4;
    m_struVacPloygon.struPos[2].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
    m_struVacPloygon.struPos[2].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
    m_struVacPloygon.struPos[1].fX = m_struVacPloygon.struPos[2].fX;
    m_struVacPloygon.struPos[1].fY = m_struVacPloygon.struPos[0].fY;
    m_struVacPloygon.struPos[3].fX = m_struVacPloygon.struPos[0].fX;
    m_struVacPloygon.struPos[3].fY = m_struVacPloygon.struPos[2].fY;
 
	CDialog::OnMouseMove(nFlags, point);
}

void CDlgImageDiffDetectionCfg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    if (!m_rcPlayWnd.PtInRect(point) || m_nCurDrawType == DRAW_TYPE_NONE)
    {
        return;
	}
    memset(&m_struVacPloygon, 0, sizeof(m_struVacPloygon));
    m_struVacPloygon.dwPointNum = 0;
    m_struVacPloygon.struPos[0].fX  = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
	m_struVacPloygon.struPos[0].fY  = (float)(point.y - m_rcPlayWnd.top)  / (float)m_rcPlayWnd.Height();
    m_bStart = TRUE;

	CDialog::OnLButtonDown(nFlags, point);
}

void CDlgImageDiffDetectionCfg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    if (!m_rcPlayWnd.PtInRect(point) || m_nCurDrawType == DRAW_TYPE_NONE)
    {
        return;
    }
    m_bStart = FALSE;
	CDialog::OnRButtonDown(nFlags, point);
}

void CDlgImageDiffDetectionCfg::DrawRgnFun(HDC hdc)
{
    if (m_nCurDrawType == DRAW_TYPE_RECTANGLE)
    {
        DRAW_POLYGON_PARAM struPolygonParam;
        memset(&struPolygonParam,0,sizeof(struPolygonParam));
        memcpy(&struPolygonParam.rcWnd, &m_rcPlayWnd, sizeof(m_rcPlayWnd));
        struPolygonParam.color = RGB(255, 0, 0);
        memcpy(&struPolygonParam.struVcaPolygon, &m_struVacPloygon, sizeof(m_struVacPloygon));
        struPolygonParam.struVcaPolygon.struPos[struPolygonParam.struVcaPolygon.dwPointNum].fX = struPolygonParam.struVcaPolygon.struPos[0].fX;
        struPolygonParam.struVcaPolygon.struPos[struPolygonParam.struVcaPolygon.dwPointNum].fY = struPolygonParam.struVcaPolygon.struPos[0].fY;
        struPolygonParam.struVcaPolygon.dwPointNum += 1;
        CDrawFun::DrawVcaPolygon(hdc, &struPolygonParam);
    }
}
