// DlgEagleCfg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgEagleCfg.h"
#include "afxdialogex.h"
#include "DrawFun.h"
#include "VcaCommonOperations.h"
// CDlgEagleCfg 对话框

IMPLEMENT_DYNAMIC(CDlgEagleCfg, CDialogEx)

void CALLBACK g_DrawCalRgn(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
    CDlgEagleCfg* pDlg = (CDlgEagleCfg*)dwUser;

    if (pDlg != NULL)
    {
        pDlg->DrawRgn(hDc);
    }
}

void CDlgEagleCfg::DrawRgn(HDC hDc)
{
    DRAW_POLYGON_PARAM_EX struPolygonParam;
    DRAW_POLYGON_PARAM_EX struITCPolygonParam;
    DRAW_LINE_PARAM  struLaneLineParam;

    memset(&struPolygonParam, 0, sizeof(struPolygonParam));
    struPolygonParam.color = RGB(255, 0, 0);
    memcpy(&struPolygonParam.rcWnd, &m_rcPlayWnd, sizeof(m_rcPlayWnd));
    struPolygonParam.pArryPt = m_strVacRegion.struPos;
    struPolygonParam.dwPtNum = m_strVacRegion.dwPointNum;
    CDrawFun::DrawPolygonEx(hDc, &struPolygonParam);


}
CDlgEagleCfg::CDlgEagleCfg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CDlgEagleCfg::IDD, pParent)
    , m_wRate(0)
    , m_bySpotNum(0)
{
    m_nDrawPointNum = 0;
    memset(&m_struBuiltin_EAGLEFOCUSING_CALCFG, 0, sizeof(m_struBuiltin_EAGLEFOCUSING_CALCFG));

}

CDlgEagleCfg::~CDlgEagleCfg()
{
}

void CDlgEagleCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_EAGLEABLITY, m_eagleability);
    DDX_Control(pDX, IDC_COMBO_EAGLE_CAL_ABLIT, m_eagle_cal_ablity);
    DDX_Control(pDX, IDC_COMBO_RULE, m_eagle_rule);
    DDX_Control(pDX, IDC_CMB_SCENE, m_cmbScene);

    DDX_Text(pDX, IDC_EDIT_RATE, m_wRate);
    DDX_Text(pDX, IDC_EDIT_SPOT_NUM, m_bySpotNum);
}


BEGIN_MESSAGE_MAP(CDlgEagleCfg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_EASET, &CDlgEagleCfg::OnBnClickedButtonEaset)
    ON_BN_CLICKED(IDC_BUTTON_CAL_SET, &CDlgEagleCfg::OnBnClickedButtonCalSet)
    ON_BN_CLICKED(IDC_BUTTON_CAL_GET, &CDlgEagleCfg::OnBnClickedButtonCalGet)
    ON_BN_CLICKED(IDC_BUTTON_EAGET, &CDlgEagleCfg::OnBnClickedButtonEaget)
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_RBUTTONDOWN()
    ON_CBN_SELCHANGE(IDC_CMB_SCENE, &CDlgEagleCfg::OnCbnSelchangeCmbScene)
    ON_BN_CLICKED(IDC_BTN_DEL, &CDlgEagleCfg::OnBnClickedBtnDel)
    ON_BN_CLICKED(IDC_BTN_GOTO_SCEN, &CDlgEagleCfg::OnBnClickedBtnGotoScen)
END_MESSAGE_MAP()


// CDlgEagleCfg 消息处理程序


BOOL CDlgEagleCfg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    GetDlgItem(IDC_STATIC_PLAY)->GetWindowRect(&m_rcPlayWnd);
    ScreenToClient(&m_rcPlayWnd);

    StartRealPlay(GetDlgItem(IDC_STATIC_PLAY)->GetSafeHwnd(), g_DrawCalRgn, this);


    m_eagle_cal_ablity.ResetContent();
    m_eagle_cal_ablity.InsertString(0, "StopCalib");
    m_eagle_cal_ablity.InsertString(1, "StartCalib");
    m_eagle_cal_ablity.SetCurSel(0);

    m_eagle_rule.ResetContent();
    m_eagle_rule.InsertString(0, "line");
    m_eagle_rule.SetCurSel(0);


    m_cmbScene.SetCurSel(0);

    m_eagleability.ResetContent();
    m_eagleability.InsertString(0, "Close");
    m_eagleability.InsertString(1, "Start");
    m_eagleability.SetCurSel(0);

    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control

}
void CDlgEagleCfg::OnBnClickedButtonEaset()
{
    UpdateData(TRUE);
    m_struBuiltin_EAGLEFOCUSING_CTRL.dwSize = sizeof(m_struBuiltin_EAGLEFOCUSING_CTRL);
    m_struBuiltin_EAGLEFOCUSING_CTRL.byEnable = m_eagleability.GetCurSel();

    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &m_struBuiltin_EAGLEFOCUSING_CTRL;
    struCfg.dwInSize = sizeof(m_struBuiltin_EAGLEFOCUSING_CTRL);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_EAGLEFOCUSING_CTRL, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_EAGLEFOCUSING_CTRL");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_EAGLEFOCUSING_CTRL");
        OutputDebugString(m_szStatusBuf);
    }
}


void CDlgEagleCfg::OnBnClickedButtonCalSet()
{
    UpdateData(TRUE);
    memset(&m_struBuiltin_EAGLEFOCUSING_CALCFG, 0, sizeof(m_struBuiltin_EAGLEFOCUSING_CALCFG));
    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &m_struBuiltin_EAGLEFOCUSING_CALCFG;
    struCfg.dwInSize = sizeof(m_struBuiltin_EAGLEFOCUSING_CALCFG);
    m_struBuiltin_EAGLEFOCUSING_CALCFG.dwSize = sizeof(m_struBuiltin_EAGLEFOCUSING_CALCFG);
    m_struBuiltin_EAGLEFOCUSING_CALCFG.byEnabled = m_eagle_cal_ablity.GetCurSel();
    m_struBuiltin_EAGLEFOCUSING_CALCFG.struEagleFoucsing[0].byRuleType = m_eagle_rule.GetCurSel();

    m_struBuiltin_EAGLEFOCUSING_CALCFG.struEagleFoucsing[0].bySceneID = m_cmbScene.GetCurSel();
    m_struBuiltin_EAGLEFOCUSING_CALCFG.struEagleFoucsing[0].bySpotNum = m_bySpotNum;
    m_struBuiltin_EAGLEFOCUSING_CALCFG.struEagleFoucsing[0].wRate = m_wRate;
    memcpy(&m_struBuiltin_EAGLEFOCUSING_CALCFG.struEagleFoucsing[0].struRegion, &m_strVacRegion, sizeof(NET_VCA_POLYGON));

    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_EAGLEFOCUSING_CALCFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_EAGLEFOCUSING_CALCFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_EAGLEFOCUSING_CALCFG");

    }
    UpdateData(FALSE);
}

void CDlgEagleCfg::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    CDialog::OnLButtonDown(nFlags, point);
    UpdateData(TRUE);
    if (!m_rcPlayWnd.PtInRect(point))
    {
        return;
    }
    if (0 == m_eagle_rule.GetCurSel())
    {
        NET_VCA_POLYGON&  struRegion = m_struBuiltin_EAGLEFOCUSING_CALCFG.struEagleFoucsing[m_cmbScene.GetCurSel()].struRegion;
        if (m_bDrawEnd || m_nDrawPointNum >= 2)
        {
            m_bDrawEnd = FALSE;
            memset(&struRegion, 0, sizeof(struRegion));
            //  return;
        }
        struRegion.struPos[m_nDrawPointNum].fX = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
        struRegion.struPos[m_nDrawPointNum].fY = (float)(point.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();
        m_nDrawPointNum++;

        memcpy(&m_strVacRegion, &m_strVacRegion, sizeof(NET_VCA_POLYGON));
        //return;
        if (2 == m_nDrawPointNum)
        {
            m_bDrawEnd = TRUE;
            m_nDrawPointNum = 0;
        }
    }
    else if (1 == m_eagle_rule.GetCurSel())
    {
    }
    else if (2 == m_eagle_rule.GetCurSel())
    {
    }
}

void CDlgEagleCfg::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    CDialogEx::OnMouseMove(nFlags, point);
    if (m_bDrawEnd)
    {
        return;
    }

    if (!m_rcPlayWnd.PtInRect(point))
    {
        return;
    }


    if (0 == m_eagle_rule.GetCurSel())
    {
        NET_VCA_POLYGON& struRegion = m_struBuiltin_EAGLEFOCUSING_CALCFG.struEagleFoucsing[m_cmbScene.GetCurSel()].struRegion;

        struRegion.struPos[m_nDrawPointNum].fX = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
        struRegion.struPos[m_nDrawPointNum].fY = (float)(point.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();
        struRegion.dwPointNum = m_nDrawPointNum + 1;

        memcpy(&m_strVacRegion, &struRegion, sizeof(NET_VCA_POLYGON));
    }
    else if (1 == m_eagle_rule.GetCurSel())
    {

    }

}

void CDlgEagleCfg::OnRButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default

    CDialog::OnRButtonDown(nFlags, point);

    if (!m_rcPlayWnd.PtInRect(point))
    {
        return;
    }

    if (/*!m_bChkRegion*/0 == m_eagle_rule.GetCurSel())
    {
        NET_VCA_POLYGON&  struRegion = m_struBuiltin_EAGLEFOCUSING_CALCFG.struEagleFoucsing[m_cmbScene.GetCurSel()].struRegion;
        if (m_nDrawPointNum > 2)
        {
            memset(&struRegion, 0, sizeof(struRegion));
            return;
        }

        struRegion.dwPointNum = m_nDrawPointNum;

        memcpy(&m_strVacRegion, &struRegion, sizeof(NET_VCA_POLYGON));
    }
    else if (1 == m_eagle_rule.GetCurSel())
    {
    }
    else if (2 == m_eagle_rule.GetCurSel())
    {

    }
    m_nDrawPointNum = 0;
    m_bDrawEnd = TRUE;

}

void CDlgEagleCfg::OnBnClickedButtonCalGet()
{
    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &m_struBuiltin_EAGLEFOCUSING_CALCFG;
    struCfg.dwOutSize = sizeof(m_struBuiltin_EAGLEFOCUSING_CALCFG);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_EAGLEFOCUSING_CALCFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_EAGLEFOCUSING_CALCFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_EAGLEFOCUSING_CALCFG");

    }

    m_eagle_cal_ablity.SetCurSel(m_struBuiltin_EAGLEFOCUSING_CALCFG.byEnabled);
    m_eagle_rule.SetCurSel(m_struBuiltin_EAGLEFOCUSING_CALCFG.struEagleFoucsing[0].byRuleType);
    m_cmbScene.SetCurSel(m_struBuiltin_EAGLEFOCUSING_CALCFG.struEagleFoucsing[0].bySceneID);
    m_bySpotNum = m_struBuiltin_EAGLEFOCUSING_CALCFG.struEagleFoucsing[0].bySpotNum;
    m_wRate = m_struBuiltin_EAGLEFOCUSING_CALCFG.struEagleFoucsing[0].wRate;
    memcpy(&m_strVacRegion, &m_struBuiltin_EAGLEFOCUSING_CALCFG.struEagleFoucsing[0].struRegion, sizeof(NET_VCA_POLYGON));
    UpdateData(FALSE);
}


void CDlgEagleCfg::OnBnClickedButtonEaget()
{
    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &m_struBuiltin_EAGLEFOCUSING_CTRL;
    struCfg.dwOutSize = sizeof(m_struBuiltin_EAGLEFOCUSING_CTRL);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_EAGLEFOCUSING_CTRL, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_EAGLEFOCUSING_CTRL");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_EAGLEFOCUSING_CTRL");

    }
    m_eagleability.SetCurSel(m_struBuiltin_EAGLEFOCUSING_CTRL.byEnable);
    UpdateData(FALSE);
}





void CDlgEagleCfg::OnCbnSelchangeCmbScene()
{
    UpdateData(TRUE);
    if (m_cmbScene.GetCurSel() != 0)
    {
        m_bySpotNum = m_struBuiltin_EAGLEFOCUSING_CALCFG.struEagleFoucsing[m_cmbScene.GetCurSel() - 1].bySpotNum;
        m_wRate = m_struBuiltin_EAGLEFOCUSING_CALCFG.struEagleFoucsing[m_cmbScene.GetCurSel() - 1].wRate;
        memcpy(&m_strVacRegion, &m_struBuiltin_EAGLEFOCUSING_CALCFG.struEagleFoucsing[m_cmbScene.GetCurSel() - 1].struRegion, sizeof(NET_VCA_POLYGON));
    }
    UpdateData(FALSE);
}


void CDlgEagleCfg::OnBnClickedBtnDel()
{
    UpdateData(TRUE);
    NET_DVR_SCENE_COND strSceneCond = { 0 };
    strSceneCond.dwSceneID = m_cmbScene.GetCurSel();
    strSceneCond.lChannel = m_lChannel;
    strSceneCond.dwSize = sizeof(strSceneCond);

    NET_DVR_STD_CONTROL struCfg = { 0 };
    struCfg.lpCondBuffer = &strSceneCond;
    struCfg.dwCondSize = sizeof(strSceneCond);

    if (!NET_DVR_STDControl(m_lServerID, NET_DVR_EAGLE_FOCUS_SCENE_DEL, &struCfg))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_EAGLE_FOCUS_SCENE_DEL");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_EAGLE_FOCUS_SCENE_DEL");
    }
}


void CDlgEagleCfg::OnBnClickedBtnGotoScen()
{
    UpdateData(TRUE);
    NET_DVR_GOTOSCENE_COND strGotoSceneCond = { 0 };
    strGotoSceneCond.dwSceneID = m_cmbScene.GetCurSel();
    strGotoSceneCond.dwChannel = m_lChannel;
    strGotoSceneCond.dwSize = sizeof(strGotoSceneCond);
    NET_DVR_STD_CONTROL struCfg = { 0 };
    struCfg.lpCondBuffer = &strGotoSceneCond;
    struCfg.dwCondSize = sizeof(strGotoSceneCond);

    if (!NET_DVR_STDControl(m_lServerID, NET_DVR_SET_EAGLE_FOCUS_GOTOSCENE, &struCfg))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_EAGLE_FOCUS_GOTOSCENE");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_EAGLE_FOCUS_GOTOSCENE");
    }
}
