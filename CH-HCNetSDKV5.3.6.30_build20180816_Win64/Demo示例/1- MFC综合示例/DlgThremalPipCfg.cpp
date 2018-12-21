// DlgThremalPipCfg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgThremalPipCfg.h"
#include "afxdialogex.h"
#include "DrawFun.h"


// CDlgThremalPipCfg 对话框

IMPLEMENT_DYNAMIC(CDlgThremalPipCfg, CDialogEx)

CDlgThremalPipCfg::CDlgThremalPipCfg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgThremalPipCfg::IDD, pParent)
    , m_bPipRegion(FALSE)
    , m_iColorB(0)
    , m_iColorG(0)
    , m_iColorR(0)
    , m_iTransparency(0)
    , m_bPipEnable(FALSE)
{
    m_bDrawEnd = FALSE;
    m_nDrawPointNum = 0;
    memset(&m_struPolyGon, 0, sizeof(m_struPolyGon));
    memset(&m_struLine, 0, sizeof(m_struLine));
    memset(&m_struThermalPip, 0, sizeof(m_struThermalPip));
    memset(&m_struThermalIntelruleDisplay, 0, sizeof(m_struThermalIntelruleDisplay));
}

CDlgThremalPipCfg::~CDlgThremalPipCfg()
{
    StopRealPlay();
}

void CDlgThremalPipCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHECK_PIP_REGION, m_bPipRegion);
    DDX_Control(pDX, IDC_COMBO_OVERLAP_TYPE, m_comboOverlapType);
    DDX_Control(pDX, IDC_COMBO_PIP_MODE, m_comboPipMode);
    DDX_Control(pDX, IDC_COMBO_RULESLINE_COLOR, m_comboRuleslineColor);
    DDX_Text(pDX, IDC_EDIT_B, m_iColorB);
    DDX_Text(pDX, IDC_EDIT_G, m_iColorG);
    DDX_Text(pDX, IDC_EDIT_R, m_iColorR);
    DDX_Text(pDX, IDC_EDIT_TRANSPARENCY, m_iTransparency);
    DDV_MinMaxInt(pDX, m_iTransparency, 0, 100);
    DDV_MinMaxInt(pDX, m_iColorR, 0, 255);
    DDV_MinMaxInt(pDX, m_iColorG, 0, 255);
    DDV_MinMaxInt(pDX, m_iColorB, 0, 255);
    DDX_Check(pDX, IDC_CHECK_PIP_ENABLE, m_bPipEnable);
    DDX_Control(pDX, IDC_COMBO_FONT_SIZE, m_comboFontSize);
}


BEGIN_MESSAGE_MAP(CDlgThremalPipCfg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_GET, &CDlgThremalPipCfg::OnBnClickedButtonGet)
    ON_BN_CLICKED(IDC_BUTTON_SET, &CDlgThremalPipCfg::OnBnClickedButtonSet)
    ON_BN_CLICKED(IDC_BUTTON_GET_OSD, &CDlgThremalPipCfg::OnBnClickedButtonGetOsd)
    ON_BN_CLICKED(IDC_BUTTON_SET_OSD, &CDlgThremalPipCfg::OnBnClickedButtonSetOsd)
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
//    ON_WM_RBUTTONDOWN()
    ON_CBN_SELCHANGE(IDC_COMBO_RULESLINE_COLOR, &CDlgThremalPipCfg::OnCbnSelchangeComboRuleslineColor)
    ON_BN_CLICKED(IDC_BUTTON_CONFIRM_OSD, &CDlgThremalPipCfg::OnBnClickedButtonConfirmOsd)
    ON_BN_CLICKED(IDC_BUTTON_REMOVE_DRAW_LINE, &CDlgThremalPipCfg::OnBnClickedButtonRemoveDrawLine)
    ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

void CALLBACK g_PipThermDraw(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
    CDlgThremalPipCfg* pDlg = (CDlgThremalPipCfg*)dwUser;

    if (pDlg != NULL)
    {
        pDlg->DrawRgnFun(hDc);
    }
}

// CDlgThremalPipCfg 消息处理程序

BOOL CDlgThremalPipCfg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    GetDlgItem(IDC_STATIC_PREVIEW)->GetWindowRect(&m_rcPlayWnd);
    ScreenToClient(&m_rcPlayWnd);

    StartRealPlay(GetDlgItem(IDC_STATIC_PREVIEW)->GetSafeHwnd(), g_PipThermDraw, this, m_lChannel);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}

void CDlgThremalPipCfg::DrawRgnFun(HDC hDc)
{
    DRAW_POLYGON_PARAM_EX struPolygonParam;
    DRAW_LINE_PARAM  struLaneLineParam;

    memset(&struPolygonParam, 0, sizeof(struPolygonParam));
    struPolygonParam.color = RGB(255, 0, 0);
    memcpy(&struPolygonParam.rcWnd, &m_rcPlayWnd, sizeof(m_rcPlayWnd));
    struPolygonParam.pArryPt = m_struPolyGon.struPos;
    struPolygonParam.dwPtNum = m_struPolyGon.dwPointNum;
    CDrawFun::DrawPolygonEx(hDc, &struPolygonParam);

    memset(&struLaneLineParam, 0, sizeof(struLaneLineParam));
    struLaneLineParam.color = RGB(0, 0, 255);
    memcpy(&struLaneLineParam.rcWnd, &m_rcPlayWnd, sizeof(m_rcPlayWnd));
    struLaneLineParam.struVcaLine = m_struLine;
    CDrawFun::DrawLine(hDc, &struLaneLineParam);

}

void CDlgThremalPipCfg::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO:  在此添加消息处理程序代码和/或调用默认值

    CDialogEx::OnLButtonDown(nFlags, point);

    UpdateData(TRUE);

    //m_bDrawEnd = FALSE;

    if (!m_rcPlayWnd.PtInRect(point))
    {
        return;
    }

    if (!m_bPipRegion)
    {
        return;
    }

    NET_VCA_POLYGON&  struRegion = m_struThermalPip.struPipRegion;
    if (m_bDrawEnd || m_nDrawPointNum >= VCA_MAX_POLYGON_POINT_NUM)
    {
        m_bDrawEnd = FALSE;
        memset(&struRegion, 0, sizeof(struRegion));
        //  return;
    }
    struRegion.struPos[0].fX = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
    struRegion.struPos[0].fY = (float)(point.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();

    memcpy(&m_struPolyGon, &struRegion, sizeof(NET_VCA_POLYGON));
}


void CDlgThremalPipCfg::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO:  在此添加消息处理程序代码和/或调用默认值

    CDialogEx::OnMouseMove(nFlags, point);

    if (m_bDrawEnd)
    {
        return;
    }

    if (!m_bPipRegion)
    {
        return;
    }

    if (!m_rcPlayWnd.PtInRect(point))
    {
        return;
    }

    NET_VCA_POLYGON&  struRegion = m_struThermalPip.struPipRegion;

    struRegion.struPos[1].fX = struRegion.struPos[0].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
    struRegion.struPos[1].fY = struRegion.struPos[2].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;
    struRegion.struPos[3].fX = struRegion.struPos[2].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
    struRegion.struPos[3].fY = struRegion.struPos[0].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;
    struRegion.struPos[2].fX = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
    struRegion.struPos[2].fY = (float)(point.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();
    struRegion.dwPointNum = 4;

    memcpy(&m_struPolyGon, &struRegion, sizeof(NET_VCA_POLYGON));
}

void CDlgThremalPipCfg::OnLButtonUp(UINT nFlags, CPoint point)
{
    // TODO:  在此添加消息处理程序代码和/或调用默认值

    __super::OnLButtonUp(nFlags, point);

    if (!m_rcPlayWnd.PtInRect(point))
    {
        return;
    }

    if (!m_bPipRegion)
    {
        return;
    }

    NET_VCA_POLYGON&  struRegion = m_struThermalPip.struPipRegion;

    struRegion.struPos[1].fX = struRegion.struPos[0].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
    struRegion.struPos[1].fY = struRegion.struPos[2].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;
    struRegion.struPos[3].fX = struRegion.struPos[2].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
    struRegion.struPos[3].fY = struRegion.struPos[0].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;
    struRegion.struPos[2].fX = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
    struRegion.struPos[2].fY = (float)(point.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();

    memcpy(&m_struPolyGon, &struRegion, sizeof(NET_VCA_POLYGON));

    m_nDrawPointNum = 0;

    m_bDrawEnd = TRUE;
}


void CDlgThremalPipCfg::OnBnClickedButtonGet()
{
    // TODO:  在此添加控件通知处理程序代码

    UpdateData(TRUE);

    char szStatusBuf[ISAPI_STATUS_LEN] = { 0 };

    NET_DVR_STD_CONFIG struStdConfig = { 0 };

    m_struThermalPip.dwSize = sizeof(m_struThermalPip);

    struStdConfig.lpCondBuffer = &m_lChannel;
    struStdConfig.dwCondSize = sizeof(m_lChannel);
    struStdConfig.lpInBuffer = NULL;
    struStdConfig.dwInSize = 0;
    struStdConfig.lpOutBuffer = (LPVOID)&m_struThermalPip;
    struStdConfig.dwOutSize = sizeof(m_struThermalPip);

    struStdConfig.lpStatusBuffer = szStatusBuf;
    struStdConfig.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_THERMAL_PIP, &struStdConfig))
    {
        OutputDebugString(szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_THERMAL_PIP");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_THERMAL_PIP");
    }
    m_bPipEnable = m_struThermalPip.byEnable;
    m_comboPipMode.SetCurSel(m_struThermalPip.byPipMode);
    m_comboOverlapType.SetCurSel(m_struThermalPip.byOverlapType);
    m_iTransparency = m_struThermalPip.byTransparency;
    m_struPolyGon = m_struThermalPip.struPipRegion;

    UpdateData(FALSE);
}


void CDlgThremalPipCfg::OnBnClickedButtonSet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    char szStatusBuf[ISAPI_STATUS_LEN] = { 0 };

    NET_DVR_STD_CONFIG struStdConfig = { 0 };

    m_struThermalPip.dwSize = sizeof(m_struThermalPip);
    m_struThermalPip.byEnable = m_bPipEnable;
    m_struThermalPip.byPipMode = m_comboPipMode.GetCurSel();
    m_struThermalPip.byOverlapType = m_comboOverlapType.GetCurSel();
    m_struThermalPip.byTransparency = m_iTransparency;

    struStdConfig.lpCondBuffer = (LPVOID)&m_lChannel;
    struStdConfig.dwCondSize = sizeof(m_lChannel);
    struStdConfig.lpInBuffer = (LPVOID)&m_struThermalPip;
    struStdConfig.dwInSize = sizeof(m_struThermalPip);

    struStdConfig.lpStatusBuffer = szStatusBuf;
    struStdConfig.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_THERMAL_PIP, &struStdConfig))
    {
        OutputDebugString(szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_THERMAL_PIP");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_THERMAL_PIP");
    }

    UpdateData(FALSE);
}


void CDlgThremalPipCfg::OnBnClickedButtonGetOsd()
{
    // TODO:  在此添加控件通知处理程序代码

    UpdateData(TRUE);

    char szStatusBuf[ISAPI_STATUS_LEN] = { 0 };

    NET_DVR_STD_CONFIG struStdConfig = { 0 };

    m_struThermalIntelruleDisplay.dwSize = sizeof(m_struThermalIntelruleDisplay);

    struStdConfig.lpCondBuffer = &m_lChannel;
    struStdConfig.dwCondSize = sizeof(m_lChannel);
    struStdConfig.lpInBuffer = NULL;
    struStdConfig.dwInSize = 0;
    struStdConfig.lpOutBuffer = (LPVOID)&m_struThermalIntelruleDisplay;
    struStdConfig.dwOutSize = sizeof(m_struThermalIntelruleDisplay);

    struStdConfig.lpStatusBuffer = szStatusBuf;
    struStdConfig.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_THERMAL_INTELRULE_DISPLAY, &struStdConfig))
    {
        OutputDebugString(szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_THERMAL_INTELRULE_DISPLAY");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_THERMAL_INTELRULE_DISPLAY");
    }

    m_comboFontSize.SetCurSel(m_struThermalIntelruleDisplay.byFontSizeType);
    m_comboRuleslineColor.SetCurSel(0);
    m_iColorR = m_struThermalIntelruleDisplay.struNormalRulesLineCfg.struRGB.byRed;
    m_iColorG = m_struThermalIntelruleDisplay.struNormalRulesLineCfg.struRGB.byGreen;
    m_iColorB = m_struThermalIntelruleDisplay.struNormalRulesLineCfg.struRGB.byBlue;

    UpdateData(FALSE);
}


void CDlgThremalPipCfg::OnBnClickedButtonSetOsd()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    char szStatusBuf[ISAPI_STATUS_LEN] = { 0 };

    NET_DVR_STD_CONFIG struStdConfig = { 0 };

    m_struThermalIntelruleDisplay.dwSize = sizeof(m_struThermalIntelruleDisplay);

    m_struThermalIntelruleDisplay.byFontSizeType = m_comboFontSize.GetCurSel();

    struStdConfig.lpCondBuffer = (LPVOID)&m_lChannel;
    struStdConfig.dwCondSize = sizeof(m_lChannel);
    struStdConfig.lpInBuffer = (LPVOID)&m_struThermalIntelruleDisplay;
    struStdConfig.dwInSize = sizeof(m_struThermalIntelruleDisplay);

    struStdConfig.lpStatusBuffer = szStatusBuf;
    struStdConfig.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_THERMAL_INTELRULE_DISPLAY, &struStdConfig))
    {
        OutputDebugString(szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_THERMAL_INTELRULE_DISPLAY");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_THERMAL_INTELRULE_DISPLAY");
    }

    UpdateData(FALSE);
}



void CDlgThremalPipCfg::OnCbnSelchangeComboRuleslineColor()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    int iSel = m_comboRuleslineColor.GetCurSel();
    if (iSel < 0)
    {
        return;
    }

    switch (iSel)
    {
    case 0:
        m_iColorR = m_struThermalIntelruleDisplay.struNormalRulesLineCfg.struRGB.byRed;
        m_iColorG = m_struThermalIntelruleDisplay.struNormalRulesLineCfg.struRGB.byGreen;
        m_iColorB = m_struThermalIntelruleDisplay.struNormalRulesLineCfg.struRGB.byBlue;
        break;
    case 1:
        m_iColorR = m_struThermalIntelruleDisplay.struAlertRulesLineCfg.struRGB.byRed;
        m_iColorG = m_struThermalIntelruleDisplay.struAlertRulesLineCfg.struRGB.byGreen;
        m_iColorB = m_struThermalIntelruleDisplay.struAlertRulesLineCfg.struRGB.byBlue;
        break;
    case 2:
        m_iColorR = m_struThermalIntelruleDisplay.struAlarmRulesLineCfg.struRGB.byRed;
        m_iColorG = m_struThermalIntelruleDisplay.struAlarmRulesLineCfg.struRGB.byGreen;
        m_iColorB = m_struThermalIntelruleDisplay.struAlarmRulesLineCfg.struRGB.byBlue;
        break;
    default:
        break;
    }

    UpdateData(FALSE);
}


void CDlgThremalPipCfg::OnBnClickedButtonConfirmOsd()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    int iSel = m_comboRuleslineColor.GetCurSel();
    if (iSel < 0)
    {
        return;
    }

    switch (iSel)
    {
    case 0:
        m_struThermalIntelruleDisplay.struNormalRulesLineCfg.struRGB.byRed = m_iColorR;
        m_struThermalIntelruleDisplay.struNormalRulesLineCfg.struRGB.byGreen = m_iColorG;
        m_struThermalIntelruleDisplay.struNormalRulesLineCfg.struRGB.byBlue = m_iColorB;
        break;
    case 1:
        m_struThermalIntelruleDisplay.struAlertRulesLineCfg.struRGB.byRed = m_iColorR;
        m_struThermalIntelruleDisplay.struAlertRulesLineCfg.struRGB.byGreen = m_iColorG;
        m_struThermalIntelruleDisplay.struAlertRulesLineCfg.struRGB.byBlue = m_iColorB;
        break;
    case 2:
        m_struThermalIntelruleDisplay.struAlarmRulesLineCfg.struRGB.byRed = m_iColorR;
        m_struThermalIntelruleDisplay.struAlarmRulesLineCfg.struRGB.byGreen = m_iColorG;
        m_struThermalIntelruleDisplay.struAlarmRulesLineCfg.struRGB.byBlue = m_iColorB;
        break;
    default:
        break;
    }

    UpdateData(FALSE);
}


void CDlgThremalPipCfg::OnBnClickedButtonRemoveDrawLine()
{
    // TODO:  在此添加控件通知处理程序代码
    memset(&m_struPolyGon, 0, sizeof(m_struPolyGon));
    memset(&m_struThermalIntelruleDisplay.struNormalRulesLineCfg, 0, sizeof(m_struThermalIntelruleDisplay.struNormalRulesLineCfg));
    memset(&m_struThermalIntelruleDisplay.struNormalRulesLineCfg, 0, sizeof(m_struThermalIntelruleDisplay.struAlertRulesLineCfg));
    memset(&m_struThermalIntelruleDisplay.struNormalRulesLineCfg, 0, sizeof(m_struThermalIntelruleDisplay.struAlarmRulesLineCfg));
    m_bDrawEnd = TRUE;
    m_nDrawPointNum = 0;

    UpdateData(FALSE);
}

