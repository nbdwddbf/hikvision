// DlgRegionDetectCfg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgRegionDetectCfg.h"
#include "afxdialogex.h"
#include "DrawFun.h"


// CDlgRegionDetectCfg 对话框

IMPLEMENT_DYNAMIC(CDlgRegionDetectCfg, CDialogEx)

CDlgRegionDetectCfg::CDlgRegionDetectCfg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRegionDetectCfg::IDD, pParent)
    , m_firedisplayShieldAreaEnabled(FALSE)
    , m_smokedisplayShieldAreaEnabled(FALSE)
{
    m_nDrawPointNum = 0;
    m_nDrawSmokePointNum = 0;
    m_bDrawEnd = FALSE;


    memset(&m_struFireShieldMask, 0, sizeof(m_struFireShieldMask));
    memset(&m_struSmokeShieldMask, 0, sizeof(m_struSmokeShieldMask));
}

CDlgRegionDetectCfg::~CDlgRegionDetectCfg()
{

}

void CDlgRegionDetectCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);

    DDX_Text(pDX, IDC_EDIT_MASK_NAME2, m_csMaskName2);
    DDX_Check(pDX, IDC_CHECK_ENABLE_SMOKESHIELDMASK, m_bEnalbeSmokeShieldMask);
    DDX_Check(pDX, IDC_CHECK_ENABLE_ONE_REGION2, m_bEnableOneRegion2);
    DDX_Control(pDX, IDC_COMBO_SMOKE_MASKID, m_comMaskID2);
    DDX_Control(pDX, IDC_COMBO_SHIELD_ZOOM2, m_comShieldZoom2);
    DDX_Control(pDX, IDC_COMBO_REGION_TYPE2, m_comRegionType2);
    DDX_Control(pDX, IDC_COMBO_MASK_TYPE2, m_comMaskType2);

    DDX_Control(pDX, IDC_COMBO_SCAN_STATE, m_comAreScanState);
    DDX_Text(pDX, IDC_EDIT_MASK_NAME, m_csMaskName);
    DDX_Check(pDX, IDC_CHECK_ENABLE_FIRESHIELDMASK, m_bEnalbeFireShieldMask);
    DDX_Check(pDX, IDC_CHECK_ENABLE_ONE_REGION, m_bEnableOneRegion);
    DDX_Control(pDX, IDC_COMBO_MASKID, m_comMaskID);
    DDX_Control(pDX, IDC_COMBO_SHIELD_ZOOM, m_comShieldZoom);
    DDX_Control(pDX, IDC_COMBO_REGION_TYPE, m_comRegionType);
    DDX_Control(pDX, IDC_COMBO_MASK_TYPE, m_comMaskType);

    DDX_Check(pDX, IDC_CHECK_FIRE_SHOW_ENABLE, m_bFireShowEnabled);
    DDX_Check(pDX, IDC_CHECK_SMOKE_SHOW_ENABLE, m_bSmokeShowEnabled);

    DDX_Control(pDX, IDC_COMBO1, m_cShieldAreaTransparency);
    DDX_Control(pDX, IDC_COMBO17, m_csmocktran);
    DDX_Check(pDX, IDC_CHECK1, m_firedisplayShieldAreaEnabled);
    DDX_Check(pDX, IDC_CHECK2, m_smokedisplayShieldAreaEnabled);
}


BEGIN_MESSAGE_MAP(CDlgRegionDetectCfg, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_SET_FIRE_SHIELD_MASK_CFG, &CDlgRegionDetectCfg::OnBnClickedBtnSetFireShieldMaskCfg)
    ON_BN_CLICKED(IDC_BTN_SAVE_FIRE_SHIELD_MASK_CFG, &CDlgRegionDetectCfg::OnBnClickedBtnSaveFireShieldMaskCfg)
    ON_BN_CLICKED(IDC_BTN_GET_FIRE_SHIELD_MASK_CFG, &CDlgRegionDetectCfg::OnBnClickedBtnGetFireShieldMaskCfg)
    ON_BN_CLICKED(IDC_BTN_SAVE_SMOKE_SHIELD_MASK_CFG, &CDlgRegionDetectCfg::OnBnClickedBtnSaveSmokeShieldMaskCfg)
    ON_BN_CLICKED(IDC_BTN_SET_SMOKE_SHIELD_MASK_CFG, &CDlgRegionDetectCfg::OnBnClickedBtnSetSmokeShieldMaskCfg)
    ON_BN_CLICKED(IDC_BTN_GET_SMOKE_SHIELD_MASK_CFG, &CDlgRegionDetectCfg::OnBnClickedBtnGetSmokeShieldMaskCfg)
    ON_BN_CLICKED(IDC_BTN_GET_AREASCAN, &CDlgRegionDetectCfg::OnBnClickedBtnGetAreascan)
    ON_BN_CLICKED(IDC_BTN_DEL_AREASCAN, &CDlgRegionDetectCfg::OnBnClickedBtnDelAreascan)
    ON_BN_CLICKED(IDC_BTN_ARESACN_IN, &CDlgRegionDetectCfg::OnBnClickedBtnAresacnIn)
    ON_BN_CLICKED(IDC_BTN_ARESACN_CONFIRM, &CDlgRegionDetectCfg::OnBnClickedBtnAresacnConfirm)
    ON_BN_CLICKED(IDC_BTN_ARESACN_STOP, &CDlgRegionDetectCfg::OnBnClickedBtnAresacnStop)
    ON_BN_CLICKED(IDC_BTN_SAVE_SCANZOOM, &CDlgRegionDetectCfg::OnBnClickedBtnSaveScanzoom)
    ON_BN_CLICKED(IDC_BTN_GET_SCANZOOM, &CDlgRegionDetectCfg::OnBnClickedBtnGetScanzoom)
    ON_WM_MOUSELEAVE()
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONDOWN()
    ON_WM_RBUTTONDOWN()
    ON_BN_CLICKED(IDC_BTN_FIRE_REGION_DEL, &CDlgRegionDetectCfg::OnBnClickedBtnFireRegionDel)
    ON_BN_CLICKED(IDC_BTN_SMOKE_REGION_DEL, &CDlgRegionDetectCfg::OnBnClickedBtnSmokeRegionDel)
END_MESSAGE_MAP()


// CDlgRegionDetectCfg 消息处理程序

void CALLBACK g_RegionDetectCfgDraw(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
    CDlgRegionDetectCfg* pDlg = (CDlgRegionDetectCfg*)dwUser;

    if (pDlg != NULL)
    {
        pDlg->DrawRgnFun(hDc);
    }
}


BOOL CDlgRegionDetectCfg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    GetDlgItem(IDC_STATIC_PREVIEW)->GetWindowRect(&m_rcPlayWnd);
    ScreenToClient(&m_rcPlayWnd);
    m_comMaskID.SetCurSel(0);
    m_comMaskID2.SetCurSel(0);

    StartRealPlay(GetDlgItem(IDC_STATIC_PREVIEW)->GetSafeHwnd(), g_RegionDetectCfgDraw, this, m_lChannel);

    return TRUE;
}

void CDlgRegionDetectCfg::DrawRgnFun(HDC hDc)
{
    DRAW_POLYGON_PARAM_EX struPolygonParam;

    memset(&struPolygonParam, 0, sizeof(struPolygonParam));
    struPolygonParam.color = RGB(255, 0, 0);
    memcpy(&struPolygonParam.rcWnd, &m_rcPlayWnd, sizeof(m_rcPlayWnd));
    struPolygonParam.pArryPt = m_struPolyGon.struPos;
    struPolygonParam.dwPtNum = m_struPolyGon.dwPointNum;
    CDrawFun::DrawPolygonEx(hDc, &struPolygonParam);
}

void CDlgRegionDetectCfg::OnBnClickedBtnSetFireShieldMaskCfg()
{
    UpdateData(TRUE);

    m_struFireShieldMask.dwSize = sizeof(m_struFireShieldMask);

    OnBnClickedBtnSaveFireShieldMaskCfg();


    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &m_struFireShieldMask;
    struCfg.dwInSize = sizeof(m_struFireShieldMask);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_FIRESHIELDMASK_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_FIRESHIELDMASK_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_FIRESHIELDMASK_CFG");
    }
}


void CDlgRegionDetectCfg::OnBnClickedBtnSaveFireShieldMaskCfg()
{
    UpdateData(TRUE);
    int iMask = m_comMaskID.GetCurSel();


    m_struFireShieldMask.byEnabled = m_bEnalbeFireShieldMask;
    m_struFireShieldMask.struMaskRegion[iMask].byMaskID = m_comMaskID.GetCurSel() + 1;
    m_struFireShieldMask.struMaskRegion[iMask].byEnabled = m_bEnableOneRegion;
    m_struFireShieldMask.struMaskRegion[iMask].byMaskType = m_comMaskType.GetCurSel();
    m_struFireShieldMask.struMaskRegion[iMask].byRegionType = m_comRegionType.GetCurSel();

    m_struFireShieldMask.struMaskRegion[iMask].byShieldZoom = m_comShieldZoom.GetCurSel();
    strncpy(m_struFireShieldMask.struMaskRegion[iMask].szMaskName, m_csMaskName.GetBuffer(0), (NAME_LEN - 1));
    m_struFireShieldMask.struMaskRegion[iMask].byShowEnabled = m_bFireShowEnabled;
    m_struFireShieldMask.byShieldAreaTransparency = m_cShieldAreaTransparency.GetCurSel();
    m_struFireShieldMask.byDisplayShieldAreaEnabled = m_firedisplayShieldAreaEnabled;
    UpdateData(FALSE);
}


void CDlgRegionDetectCfg::OnBnClickedBtnGetFireShieldMaskCfg()
{
    UpdateData(TRUE);
    memset(&m_struFireShieldMask, 0, sizeof(m_struFireShieldMask));

    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &m_struFireShieldMask;
    struCfg.dwOutSize = sizeof(m_struFireShieldMask);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_FIRESHIELDMASK_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_FIRESHIELDMASK_CFG, err = %d", NET_DVR_GetLastError());
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_FIRESHIELDMASK_CFG");
    }

    m_comMaskID.SetCurSel(0);

    int iMask = m_comMaskID.GetCurSel();
    m_bFireShowEnabled = m_struFireShieldMask.struMaskRegion[iMask].byShowEnabled;

    if (m_bFireShowEnabled)
    {       
        m_bEnalbeFireShieldMask = m_struFireShieldMask.byEnabled;
        m_comMaskID.SetCurSel(m_struFireShieldMask.struMaskRegion[iMask].byMaskID - 1);
        m_bEnableOneRegion = m_struFireShieldMask.struMaskRegion[iMask].byEnabled;
        m_comMaskType.SetCurSel(m_struFireShieldMask.struMaskRegion[iMask].byMaskType);
        m_comRegionType.SetCurSel(m_struFireShieldMask.struMaskRegion[iMask].byRegionType);
        m_comShieldZoom.SetCurSel(m_struFireShieldMask.struMaskRegion[iMask].byShieldZoom);
        m_csMaskName.Format(_T("%s"), m_struFireShieldMask.struMaskRegion[iMask].szMaskName);
    }
    
    m_cShieldAreaTransparency.SetCurSel(m_struFireShieldMask.byShieldAreaTransparency);
    m_firedisplayShieldAreaEnabled = m_struFireShieldMask.byDisplayShieldAreaEnabled;

    UpdateData(FALSE);
}


void CDlgRegionDetectCfg::OnBnClickedBtnSaveSmokeShieldMaskCfg()
{
    UpdateData(TRUE);
    int iMask = m_comMaskID2.GetCurSel();

    m_struSmokeShieldMask.byEnabled = m_bEnalbeSmokeShieldMask;
    m_struSmokeShieldMask.struMaskRegion[iMask].byMaskID = m_comMaskID2.GetCurSel() + 1;
    m_struSmokeShieldMask.struMaskRegion[iMask].byEnabled = m_bEnableOneRegion2;
    m_struSmokeShieldMask.struMaskRegion[iMask].byMaskType = m_comMaskType2.GetCurSel();
    m_struSmokeShieldMask.struMaskRegion[iMask].byRegionType = m_comRegionType2.GetCurSel();

    m_struSmokeShieldMask.struMaskRegion[iMask].byShieldZoom = m_comShieldZoom2.GetCurSel();
    strncpy(m_struSmokeShieldMask.struMaskRegion[iMask].szMaskName, m_csMaskName2.GetBuffer(0), (NAME_LEN - 1));
    m_struSmokeShieldMask.struMaskRegion[iMask].byShowEnabled = m_bSmokeShowEnabled;
    m_struSmokeShieldMask.byShieldAreaTransparency = m_csmocktran.GetCurSel();
    m_struSmokeShieldMask.byDisplayShieldAreaEnabled = m_smokedisplayShieldAreaEnabled;
    UpdateData(FALSE);
}


void CDlgRegionDetectCfg::OnBnClickedBtnSetSmokeShieldMaskCfg()
{
    UpdateData(TRUE);

    m_struSmokeShieldMask.dwSize = sizeof(m_struSmokeShieldMask);

    OnBnClickedBtnSaveSmokeShieldMaskCfg();

    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &m_struSmokeShieldMask;
    struCfg.dwInSize = sizeof(m_struSmokeShieldMask);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_SMOKESHIELDMASK_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SMOKESHIELDMASK_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SMOKESHIELDMASK_CFG");
    }
}


void CDlgRegionDetectCfg::OnBnClickedBtnGetSmokeShieldMaskCfg()
{
    UpdateData(TRUE);
    memset(&m_struSmokeShieldMask, 0, sizeof(m_struSmokeShieldMask));

    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &m_struSmokeShieldMask;
    struCfg.dwOutSize = sizeof(m_struSmokeShieldMask);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_SMOKESHIELDMASK_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SMOKESHIELDMASK_CFG, err = %d", NET_DVR_GetLastError());
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SMOKESHIELDMASK_CFG");
    }

    m_comMaskID2.SetCurSel(0);
    int iMask = m_comMaskID2.GetCurSel();
    m_bSmokeShowEnabled = m_struSmokeShieldMask.struMaskRegion[iMask].byShowEnabled;

    if (m_bSmokeShowEnabled)
    {
        m_bEnalbeSmokeShieldMask = m_struSmokeShieldMask.byEnabled;
        m_comMaskID2.SetCurSel(m_struSmokeShieldMask.struMaskRegion[iMask].byMaskID - 1);
        m_bEnableOneRegion2 = m_struSmokeShieldMask.struMaskRegion[iMask].byEnabled;
        m_comMaskType2.SetCurSel(m_struSmokeShieldMask.struMaskRegion[iMask].byMaskType);
        m_comRegionType2.SetCurSel(m_struSmokeShieldMask.struMaskRegion[iMask].byRegionType);
        m_comShieldZoom2.SetCurSel(m_struSmokeShieldMask.struMaskRegion[iMask].byShieldZoom);
        m_csMaskName2.Format(_T("%s"), m_struSmokeShieldMask.struMaskRegion[iMask].szMaskName);
    }
    m_csmocktran.SetCurSel(m_struSmokeShieldMask.byShieldAreaTransparency);
    m_smokedisplayShieldAreaEnabled = m_struSmokeShieldMask.byDisplayShieldAreaEnabled;
    UpdateData(FALSE);
}


void CDlgRegionDetectCfg::OnBnClickedBtnSetAreascan()
{
    UpdateData(TRUE);
}


void CDlgRegionDetectCfg::OnBnClickedBtnGetAreascan()
{
    NET_SDK_AREASCAN_CFG struAreaScan = { 0 };

    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &struAreaScan;
    struCfg.dwOutSize = sizeof(struAreaScan);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_AREASCAN_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_AREASCAN_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_AREASCAN_CFG");
    }

    m_comAreScanState.SetCurSel(struAreaScan.byScanState);

    UpdateData(FALSE);
}


void CDlgRegionDetectCfg::OnBnClickedBtnDelAreascan()
{
    UpdateData(TRUE);

    NET_DVR_STD_CONTROL struStdControl = { 0 };
    struStdControl.lpCondBuffer = &m_lChannel;
    struStdControl.dwCondSize = sizeof(m_lChannel);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struStdControl.lpStatusBuffer = m_szStatusBuf;
    struStdControl.dwStatusSize = ISAPI_STATUS_LEN;
    if (!NET_DVR_STDControl(m_lServerID, NET_DVR_DEL_AREASCAN_CFG, &struStdControl))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_DEL_AREASCAN_CFG");
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DEL_AREASCAN_CFG");
    }
}


void CDlgRegionDetectCfg::OnBnClickedBtnAresacnIn()
{
    UpdateData(TRUE);

    NET_DVR_STD_CONTROL struStdControl = { 0 };
    struStdControl.lpCondBuffer = &m_lChannel;
    struStdControl.dwCondSize = sizeof(m_lChannel);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struStdControl.lpStatusBuffer = m_szStatusBuf;
    struStdControl.dwStatusSize = ISAPI_STATUS_LEN;
    if (!NET_DVR_STDControl(m_lServerID, NET_DVR_AREASCAN_INIT_CTRL, &struStdControl))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_AREASCAN_INIT_CTRL");
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_AREASCAN_INIT_CTRL");
    }
}


void CDlgRegionDetectCfg::OnBnClickedBtnAresacnConfirm()
{
    UpdateData(TRUE);

    NET_DVR_STD_CONTROL struStdControl = { 0 };
    struStdControl.lpCondBuffer = &m_lChannel;
    struStdControl.dwCondSize = sizeof(m_lChannel);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struStdControl.lpStatusBuffer = m_szStatusBuf;
    struStdControl.dwStatusSize = ISAPI_STATUS_LEN;
    if (!NET_DVR_STDControl(m_lServerID, NET_DVR_AREASCAN_CONFIRM_CTRL, &struStdControl))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_AREASCAN_CONFIRM_CTRL");
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_AREASCAN_CONFIRM_CTRL");
    }
}


void CDlgRegionDetectCfg::OnBnClickedBtnAresacnStop()
{
    UpdateData(TRUE);

    NET_DVR_STD_CONTROL struStdControl = { 0 };
    struStdControl.lpCondBuffer = &m_lChannel;
    struStdControl.dwCondSize = sizeof(m_lChannel);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struStdControl.lpStatusBuffer = m_szStatusBuf;
    struStdControl.dwStatusSize = ISAPI_STATUS_LEN;
    if (!NET_DVR_STDControl(m_lServerID, NET_DVR_AREASCAN_STOP_CTRL, &struStdControl))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_AREASCAN_STOP_CTRL");
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_AREASCAN_STOP_CTRL");
    }
}


void CDlgRegionDetectCfg::OnBnClickedBtnSaveScanzoom()
{
    UpdateData(TRUE);

    NET_DVR_STD_CONTROL struStdControl = { 0 };
    struStdControl.lpCondBuffer = &m_lChannel;
    struStdControl.dwCondSize = sizeof(m_lChannel);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struStdControl.lpStatusBuffer = m_szStatusBuf;
    struStdControl.dwStatusSize = ISAPI_STATUS_LEN;
    if (!NET_DVR_STDControl(m_lServerID, NET_DVR_SAVE_SCANZOOM_CTRL, &struStdControl))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SAVE_SCANZOOM_CTRL");
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SAVE_SCANZOOM_CTRL");
    }
}


void CDlgRegionDetectCfg::OnBnClickedBtnGetScanzoom()
{
    UpdateData(TRUE);

    NET_DVR_STD_CONTROL struStdControl = { 0 };
    struStdControl.lpCondBuffer = &m_lChannel;
    struStdControl.dwCondSize = sizeof(m_lChannel);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struStdControl.lpStatusBuffer = m_szStatusBuf;
    struStdControl.dwStatusSize = ISAPI_STATUS_LEN;
    if (!NET_DVR_STDControl(m_lServerID, NET_DVR_GET_SCANZOOM_CTRL, &struStdControl))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SCANZOOM_CTRL");
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SCANZOOM_CTRL");
    }
}



void CDlgRegionDetectCfg::OnMouseMove(UINT nFlags, CPoint point)
{
    __super::OnMouseMove(nFlags, point);

    if (m_bDrawEnd)
    {
    return;
    }

    if (!m_rcPlayWnd.PtInRect(point))
    {
    return;
    }

    if (m_bEnalbeFireShieldMask)
    {
        NET_VCA_POLYGON&  struRegion = m_struFireShieldMask.struMaskRegion[m_comMaskID.GetCurSel()].struRegion;

        struRegion.struPos[m_nDrawPointNum].fX = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
        struRegion.struPos[m_nDrawPointNum].fY = (float)(point.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();
        struRegion.dwPointNum = m_nDrawPointNum + 1;

        memcpy(&m_struPolyGon, &struRegion, sizeof(NET_VCA_POLYGON));
    }

    if (m_bEnalbeSmokeShieldMask)
    {
        NET_VCA_POLYGON&  struRegion = m_struSmokeShieldMask.struMaskRegion[m_comMaskID2.GetCurSel()].struRegion;

        struRegion.struPos[m_nDrawSmokePointNum].fX = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
        struRegion.struPos[m_nDrawSmokePointNum].fY = (float)(point.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();
        struRegion.dwPointNum = m_nDrawSmokePointNum + 1;

        memcpy(&m_struPolyGon, &struRegion, sizeof(NET_VCA_POLYGON));
    }
}


void CDlgRegionDetectCfg::OnLButtonDown(UINT nFlags, CPoint point)
{
    __super::OnLButtonDown(nFlags, point);

    UpdateData(TRUE);

    //m_bDrawEnd = FALSE;

    if (!m_rcPlayWnd.PtInRect(point))
    {
        return;
    }

    if (m_bEnalbeFireShieldMask)
    {
        if (m_comMaskID.GetCurSel() < 0)
        {
            AfxMessageBox("请选择区域ID值");
        }
        NET_VCA_POLYGON&  struRegion = m_struFireShieldMask.struMaskRegion[m_comMaskID.GetCurSel()].struRegion;
        if (m_bDrawEnd || m_nDrawPointNum >= VCA_MAX_POLYGON_POINT_NUM)
        {
            m_bDrawEnd = FALSE;
            memset(&struRegion, 0, sizeof(struRegion));
//            return;
        }
        struRegion.struPos[m_nDrawPointNum].fX = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
        struRegion.struPos[m_nDrawPointNum].fY = (float)(point.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();
        m_nDrawPointNum++;

        memcpy(&m_struPolyGon, &struRegion, sizeof(NET_VCA_POLYGON));
    }

    if (m_bEnalbeSmokeShieldMask)
    {
        if (m_comMaskID2.GetCurSel() < 0)
        {
            AfxMessageBox("请选择区域ID值");
        }

        NET_VCA_POLYGON&  struRegion = m_struSmokeShieldMask.struMaskRegion[m_comMaskID2.GetCurSel()].struRegion;
        if (m_bDrawEnd || m_nDrawSmokePointNum >= VCA_MAX_POLYGON_POINT_NUM)
        {
            m_bDrawEnd = FALSE;
            memset(&struRegion, 0, sizeof(struRegion));
//            return;
        }
        struRegion.struPos[m_nDrawSmokePointNum].fX = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
        struRegion.struPos[m_nDrawSmokePointNum].fY = (float)(point.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();
        m_nDrawSmokePointNum++;

        memcpy(&m_struPolyGon, &struRegion, sizeof(NET_VCA_POLYGON));
    }
}


void CDlgRegionDetectCfg::OnRButtonDown(UINT nFlags, CPoint point)
{
    __super::OnRButtonDown(nFlags, point);

    if (!m_rcPlayWnd.PtInRect(point))
    {
        return;
    }

    if (m_bEnalbeFireShieldMask)
    {
        NET_VCA_POLYGON&  struRegion = m_struFireShieldMask.struMaskRegion[m_comMaskID.GetCurSel()].struRegion;
        if (m_nDrawPointNum >= 20 || m_nDrawPointNum < 3)
        {
            memset(&struRegion, 0, sizeof(struRegion));
            return;
        }

        struRegion.dwPointNum = m_nDrawPointNum;

        memcpy(&m_struPolyGon, &struRegion, sizeof(NET_VCA_POLYGON));
        m_nDrawPointNum = 0;
    }

    if (m_bEnalbeSmokeShieldMask)
    {
        NET_VCA_POLYGON&  struRegion = m_struSmokeShieldMask.struMaskRegion[m_comMaskID2.GetCurSel()].struRegion;
        if (m_nDrawSmokePointNum >= 20 || m_nDrawSmokePointNum < 3)
        {
            memset(&struRegion, 0, sizeof(struRegion));
            return; 
        }

        struRegion.dwPointNum = m_nDrawSmokePointNum;
        memcpy(&m_struPolyGon, &struRegion, sizeof(NET_VCA_POLYGON));
        m_nDrawSmokePointNum = 0;
    }
    
    m_bDrawEnd = TRUE;
}

void CDlgRegionDetectCfg::OnBnClickedBtnFireRegionDel()
{
    UpdateData(TRUE);

    m_FireShieldMaskCond.dwSize = sizeof(m_FireShieldMaskCond);

    m_FireShieldMaskCond.dwChannel = m_lChannel;
    m_FireShieldMaskCond.byRegionID = m_comMaskID.GetCurSel() + 1;

    NET_DVR_STD_CONTROL struStdControl = { 0 };
    struStdControl.lpCondBuffer = &m_FireShieldMaskCond;
    struStdControl.dwCondSize = sizeof(m_FireShieldMaskCond);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struStdControl.lpStatusBuffer = m_szStatusBuf;
    struStdControl.dwStatusSize = ISAPI_STATUS_LEN;


    if (!NET_DVR_STDControl(m_lServerID, NET_DVR_DEL_FIRESHIELDMASK_CTRL, &struStdControl))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_DEL_AREASCAN_CFG");
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DEL_AREASCAN_CFG");
    }
}


void CDlgRegionDetectCfg::OnBnClickedBtnSmokeRegionDel()
{
    UpdateData(TRUE);

    m_SmokeShieldMaskCond.dwSize = sizeof(m_SmokeShieldMaskCond);

    m_SmokeShieldMaskCond.dwChannel = m_lChannel;
    m_SmokeShieldMaskCond.byRegionID = m_comMaskID2.GetCurSel() + 1;

    NET_DVR_STD_CONTROL struStdControl = { 0 };
    struStdControl.lpCondBuffer = &m_SmokeShieldMaskCond;
    struStdControl.dwCondSize = sizeof(m_SmokeShieldMaskCond);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struStdControl.lpStatusBuffer = m_szStatusBuf;
    struStdControl.dwStatusSize = ISAPI_STATUS_LEN;
    if (!NET_DVR_STDControl(m_lServerID, NET_DVR_DEL_SMOKESHIELDMASK_CTRL, &struStdControl))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_DEL_AREASCAN_CFG");
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DEL_AREASCAN_CFG");
    }
}