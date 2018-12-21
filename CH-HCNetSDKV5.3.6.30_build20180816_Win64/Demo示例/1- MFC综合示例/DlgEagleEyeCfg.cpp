// DlgEagleEyeCfg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgEagleEyeCfg.h"
#include "afxdialogex.h"
#include "DrawFun.h"
// CDlgEagleEyeCfg 对话框
IMPLEMENT_DYNAMIC(CDlgEagleEyeCfg, CDialogEx)

CDlgEagleEyeCfg::CDlgEagleEyeCfg(CWnd* pParent /*=NULL*/)
: CDialogEx(CDlgEagleEyeCfg::IDD, pParent)
, m_wTrackTime(0)
, m_Coefficient(0)
{
    m_lChannel = 1;
    m_lPlayHandle = -1;
    memset(&m_struSlaveCameraCalibCfgV51, 0, sizeof(m_struSlaveCameraCalibCfgV51));
    memset(&m_struSlaveCameraCond, 0, sizeof(m_struSlaveCameraCond));
    memset(&m_strGotoSceneCond, 0, sizeof(m_strGotoSceneCond));
    memset(&m_struTrackMode, 0, sizeof(m_struTrackMode));
    memset(&m_struTracking, 0, sizeof(m_struTracking));
    memset(&m_struRegionTemp, 0, sizeof(m_struRegionTemp));
    memset(&m_struTrackPoint, 0, sizeof(m_struTrackPoint));
    memset(&m_struTrackInitPostion, 0, sizeof(m_struTrackInitPostion));

}
CDlgEagleEyeCfg *g_pDlgMasterSlaveTrackingEagle = NULL;

void CALLBACK g_DrawSlaveMasterEagle(LONG lRealHandle, HDC hDc, DWORD dwUser)
{

    g_pDlgMasterSlaveTrackingEagle->F_DrawFrameEagle(hDc);

}

CDlgEagleEyeCfg::~CDlgEagleEyeCfg()
{
    if (m_lPlayHandle >= 0)
    {
        NET_DVR_StopRealPlay(m_lPlayHandle);
        m_lPlayHandle = -1;
    }
}
void CDlgEagleEyeCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_SLAVE_CAMERAID, m_comboSlaveCameraID);
    DDX_Control(pDX, IDC_COMBO_CALIBMODE, m_comboCalibMode);
    DDX_Control(pDX, IDC_COMBO_SCENEID, m_comboSceneID);
    DDX_Control(pDX, IDC_LIST_CALIB, m_lstCalib);
    DDX_Control(pDX, IDC_COB_GOTO_SCENEID, m_comboGotoSceneId);
    DDX_Control(pDX, IDC_BTN_CALIB_DEL, m_btnDel);
    DDX_Control(pDX, IDC_BTN_CALIB, m_btnCalib);
    DDX_Control(pDX, IDC_COMBO_ENABLED, m_combEnabled);
    DDX_Text(pDX, IDC_EDIT_TRACK_TIME, m_wTrackTime);
    DDX_Control(pDX, IDC_FollowCamaID_COMBO, m_SetFollowInitPositionCtrl);
    DDX_Control(pDX, IDC_FCamaID_COMBO, m_FcIDCoefficientCtrl);
    DDX_Text(pDX, IDC_Coefficient_EDIT, m_Coefficient);
    DDV_MinMaxInt(pDX, m_Coefficient, 0, 10);
    DDX_Control(pDX, IDC_COMBO_ResolutionType, m_resolutiontypectrl);
    DDX_Control(pDX, IDC_COMBO_LINKAGE, m_cmbLinkage);
}


BEGIN_MESSAGE_MAP(CDlgEagleEyeCfg, CDialogEx)
    ON_BN_CLICKED(IDCANCEL, &CDlgEagleEyeCfg::OnBnClickedCancel)
    ON_BN_CLICKED(IDC_BTN_CALIB_GET, &CDlgEagleEyeCfg::OnBnClickedBtnCalibGet)
    ON_BN_CLICKED(IDC_BTN_CALIB_SET, &CDlgEagleEyeCfg::OnBnClickedBtnCalibSet)
    ON_BN_CLICKED(IDC_BTN_SET_GOTOSCENE, &CDlgEagleEyeCfg::OnBnClickedBtnSetGotoscene)
    ON_BN_CLICKED(IDC_BTN_CALIB, &CDlgEagleEyeCfg::OnBnClickedBtnCalib)
    ON_BN_CLICKED(IDC_BTN_CALIB_DEL, &CDlgEagleEyeCfg::OnBnClickedBtnCalibDel)
    ON_CBN_SELCHANGE(IDC_COMBO_CALIBMODE, &CDlgEagleEyeCfg::OnCbnSelchangeComboCalibmode)
    ON_BN_CLICKED(_SET_TRACKRATIO, &CDlgEagleEyeCfg::OnBnClickedSetTrackratio)
    ON_BN_CLICKED(IDC_BTN_TRACK_GET, &CDlgEagleEyeCfg::OnBnClickedBtnTrackGet)
    ON_BN_CLICKED(IDC_BTN_TRACK_SET, &CDlgEagleEyeCfg::OnBnClickedBtnTrackSet)
    ON_BN_CLICKED(IDC_SetInitPosition_BUTTON, &CDlgEagleEyeCfg::OnBnClickedSetinitpositionButton)
    ON_BN_CLICKED(IDC_BTN_Coefficient_GET, &CDlgEagleEyeCfg::OnBnClickedBtnCoefficientGet)
    ON_BN_CLICKED(IDC_BTN_Coefficient_SET, &CDlgEagleEyeCfg::OnBnClickedBtnCoefficientSet)
    ON_BN_CLICKED(IDC_GET_ResolutionType_BUTTON, &CDlgEagleEyeCfg::OnBnClickedGetResolutiontypeButton)
    ON_BN_CLICKED(IDC_SET_ResolutionType_BUTTON, &CDlgEagleEyeCfg::OnBnClickedSetResolutiontypeButton)
    ON_BN_CLICKED(IDC_GET_LINKAGE_BUTTON, &CDlgEagleEyeCfg::OnBnClickedGetLinkageButton)
    ON_BN_CLICKED(IDC_SET_LINKAGE_BUTTON, &CDlgEagleEyeCfg::OnBnClickedSetLinkageButton)
END_MESSAGE_MAP()


// CDlgEagleEyeCfg 消息处理程序


void CDlgEagleEyeCfg::OnBnClickedCancel()
{
    // TODO:  在此添加控件通知处理程序代码
    CDialogEx::OnCancel();
}
BOOL CDlgEagleEyeCfg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化

    // TODO: Add extra initialization here
    g_pDlgMasterSlaveTrackingEagle = this;
    GetDlgItem(IDC_MASTER_PLAYWND_EAGLE)->GetWindowRect(&m_rcEagleWnd);

    m_lstCalib.SetExtendedStyle(m_lstCalib.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    m_lstCalib.InsertColumn(0, "Index", LVCFMT_LEFT, 50, -1);
    m_lstCalib.InsertColumn(1, "Coordinates(x,y)", LVCFMT_LEFT, 100, -1);
    m_lstCalib.InsertColumn(2, "PTZ(p,t,z)", LVCFMT_LEFT, 150, -1);

    CString  strTemp;
    for (int i = 0; i < 6; i++)
    {
        strTemp.Format("%02d", i + 1);
        m_lstCalib.InsertItem(i, strTemp);
    }
    m_comboSlaveCameraID.SetCurSel(0);
    m_comboCalibMode.SetCurSel(0);
    m_comboSceneID.SetCurSel(0);
    m_comboGotoSceneId.SetCurSel(0);
    m_combEnabled.SetCurSel(0);


    NET_DVR_CLIENTINFO struPlayInfo;
    memset(&struPlayInfo, 0, sizeof(NET_DVR_CLIENTINFO));

    struPlayInfo.hPlayWnd = GetDlgItem(IDC_MASTER_PLAYWND_EAGLE)->GetSafeHwnd();
    struPlayInfo.lChannel = m_lChannel;
    struPlayInfo.lLinkMode = 0;
    Play(&struPlayInfo, m_lServerID, 0);
    BOOL bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, g_DrawSlaveMasterEagle, 0);
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}

void CDlgEagleEyeCfg::F_DrawFrameEagle(HDC hDc)
{
    DRAW_POLYGON_PARAM_EX struPolygonParam;
    memset(&struPolygonParam, 0, sizeof(struPolygonParam));
    struPolygonParam.color = RGB(255, 0, 0);
    memcpy(&struPolygonParam.rcWnd, &m_rcEagleWnd, sizeof(m_rcEagleWnd));
    struPolygonParam.pArryPt = m_struTracking.struRegion.struPos;
    struPolygonParam.dwPtNum = m_struTracking.struRegion.dwPointNum;
    CDrawFun::DrawPolygonEx(hDc, &struPolygonParam);
}
BOOL CDlgEagleEyeCfg::PreTranslateMessage(MSG* pMsg)
{
    UpdateData(TRUE);
    int index = m_comboSlaveCameraID.GetCurSel();
    CPoint pt(0, 0);
    GetDlgItem(IDC_MASTER_PLAYWND_EAGLE)->GetWindowRect(&m_rcEagleWnd);
    GetCursorPos(&pt);
    ScreenToClient(&m_rcEagleWnd);
    ScreenToClient(&pt);
    CString strTemp = _T("");
    DWORD i = 0;
    BOOL bOneLine = TRUE, bXOneLine = TRUE, bYOneLine = TRUE;
    switch (pMsg->message)  // Message of Draw
    {
    case WM_LBUTTONDOWN:
        if ((GetAsyncKeyState(VK_LCONTROL) < 0 || GetAsyncKeyState(VK_RCONTROL) < 0))//Press CTRL to draw
        {
            if (PtInRect(&m_rcEagleWnd, pt))
            {
                m_struTrackPoint.fX = (float)(pt.x - m_rcEagleWnd.left) / (float)m_rcEagleWnd.Width();
                m_struTrackPoint.fY = (float)(pt.y - m_rcEagleWnd.top) / (float)m_rcEagleWnd.Height();
                memset(&m_struTracking.struRegion, 0, sizeof(m_struTracking.struRegion));
                int nItem = m_lstCalib.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
                m_struSlaveCameraCalibCfgV51.struCalibParam[nItem].struCalibCoordinates.fX = (float)(pt.x - m_rcEagleWnd.left) / (float)m_rcEagleWnd.Width();
                m_struSlaveCameraCalibCfgV51.struCalibParam[nItem].struCalibCoordinates.fY = (float)(pt.y - m_rcEagleWnd.top) / (float)m_rcEagleWnd.Height();
            }
        }
        break;
    case WM_MOUSEMOVE:
        if ((GetAsyncKeyState(VK_LCONTROL) < 0 || GetAsyncKeyState(VK_RCONTROL) < 0))
        {
            if (PtInRect(&m_rcEagleWnd, pt) && m_bMouseMove)
            {

                m_struTracking.struRegion.struPos[1].fX = m_struTracking.struRegion.struPos[0].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
                m_struTracking.struRegion.struPos[1].fY = m_struTracking.struRegion.struPos[2].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;
                m_struTracking.struRegion.struPos[3].fX = m_struTracking.struRegion.struPos[2].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
                m_struTracking.struRegion.struPos[3].fY = m_struTracking.struRegion.struPos[0].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;
                m_struTracking.struRegion.struPos[2].fX = (float)(pt.x - m_rcEagleWnd.left) / (float)m_rcEagleWnd.Width();
                m_struTracking.struRegion.struPos[2].fY = (float)(pt.y - m_rcEagleWnd.top) / (float)m_rcEagleWnd.Height();
                m_struTracking.struRegion.dwPointNum = 4;
                memcpy(&m_struRegionTemp, &m_struTracking.struRegion, sizeof(NET_VCA_POLYGON));
            }
        }
        break;
    case WM_LBUTTONUP:
        if ((GetAsyncKeyState(VK_LCONTROL) < 0 || GetAsyncKeyState(VK_RCONTROL) < 0))//Press CTRL to draw
        {
            m_struTracking.struRegion.struPos[1].fX = m_struTracking.struRegion.struPos[0].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
            m_struTracking.struRegion.struPos[1].fY = m_struTracking.struRegion.struPos[2].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;
            m_struTracking.struRegion.struPos[3].fX = m_struTracking.struRegion.struPos[2].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
            m_struTracking.struRegion.struPos[3].fY = m_struTracking.struRegion.struPos[0].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;
            m_struTracking.struRegion.struPos[2].fX = (float)(pt.x - m_rcEagleWnd.left) / (float)m_rcEagleWnd.Width();
            m_struTracking.struRegion.struPos[2].fY = (float)(pt.y - m_rcEagleWnd.top) / (float)m_rcEagleWnd.Height();
            memcpy(&m_struRegionTemp, &m_struTracking.struRegion, sizeof(NET_VCA_POLYGON));
        }
        m_bMouseMove = FALSE;
        break;
    default:
        break;
    }
    return CDialog::PreTranslateMessage(pMsg);
}
BOOL CDlgEagleEyeCfg::Play(NET_DVR_CLIENTINFO* struClientInfo, LONG loginID, int index)
{
    char szLan[128] = { 0 };
    char szTemp[256] = { 0 };
    if (m_lPlayHandle >= 0)
    {
        NET_DVR_StopRealPlay(m_lPlayHandle);
        m_lPlayHandle = -1;
    }

    m_lPlayHandle = NET_DVR_RealPlay_V30(loginID, struClientInfo, NULL, NULL, TRUE);
    BOOL bRet = FALSE;
    if (m_lPlayHandle < 0)
    {
        g_StringLanType(szLan, "预览失败", "Realplay failed");
        sprintf(szTemp, "%s %s ErrCode:%d", szLan, NET_DVR_GetErrorMsg(), NET_DVR_GetLastError());
        AfxMessageBox(szTemp);
        return FALSE;
    }
    //bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawRoiDetectShow, 0);
    UpdateData(FALSE);
    return TRUE;
}

void CDlgEagleEyeCfg::OnBnClickedBtnCalibGet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    m_struSlaveCameraCond.byID = m_comboSlaveCameraID.GetCurSel() + 2;
    m_struSlaveCameraCond.dwChannel = m_lChannel;
    m_struSlaveCameraCond.dwSize = sizeof(m_struSlaveCameraCond);
    m_struSlaveCameraCond.dwSceneID = m_comboSceneID.GetCurSel() + 1;
    memset(&m_struSlaveCameraCalibCfgV51, 0, sizeof(m_struSlaveCameraCalibCfgV51));
    m_struSlaveCameraCalibCfgV51.dwSize = sizeof(m_struSlaveCameraCalibCfgV51);

    NET_DVR_STD_CONFIG struCfg = { 0 };

    struCfg.lpCondBuffer = &m_struSlaveCameraCond;
    struCfg.dwCondSize = sizeof(m_struSlaveCameraCond);
    struCfg.lpOutBuffer = &m_struSlaveCameraCalibCfgV51;
    struCfg.dwOutSize = sizeof(m_struSlaveCameraCalibCfgV51);

    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_SLAVECAMERA_CALIB_V51, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SLAVECAMERA_CALIB_V51");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SLAVECAMERA_CALIB_V51");
    }

    m_comboCalibMode.SetCurSel(m_struSlaveCameraCalibCfgV51.byCalibMode);
    SetDataToCalibList(&m_struSlaveCameraCalibCfgV51);
    OnCbnSelchangeComboCalibmode();
    UpdateData(FALSE);
}

BOOL CDlgEagleEyeCfg::SetDataToCalibList(NET_DVR_SLAVECAMERA_CALIB_V51* m_struSlaveCameraCalibCfgV51)
{
    CString strTemp;
    m_lstCalib.DeleteAllItems();
    for (int i = 0; i < MAX_CALIB_NUM_EX; i++)
    {
        strTemp.Format("%02d", i + 1);
        m_lstCalib.InsertItem(i, strTemp);

        strTemp.Format("(%.3f,%.3f)", m_struSlaveCameraCalibCfgV51->struCalibParam[i].struCalibCoordinates.fX, \
            m_struSlaveCameraCalibCfgV51->struCalibParam[i].struCalibCoordinates.fY);
        m_lstCalib.SetItemText(i, 1, strTemp);

        strTemp.Format("(%.1f,%.1f,%.1f)", m_struSlaveCameraCalibCfgV51->struCalibParam[i].struPtzInfo.fPan, \
            m_struSlaveCameraCalibCfgV51->struCalibParam[i].struPtzInfo.fTilt, \
            m_struSlaveCameraCalibCfgV51->struCalibParam[i].struPtzInfo.fZoom);
        m_lstCalib.SetItemText(i, 2, strTemp);
    }
    return TRUE;
}

void CDlgEagleEyeCfg::OnBnClickedBtnCalibSet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    m_struSlaveCameraCond.byID = m_comboSlaveCameraID.GetCurSel() + 2;
    m_struSlaveCameraCond.dwChannel = m_lChannel;
    m_struSlaveCameraCond.dwSize = sizeof(m_struSlaveCameraCond);
    m_struSlaveCameraCond.dwSceneID = m_comboSceneID.GetCurSel() + 1;

    m_struSlaveCameraCalibCfgV51.dwSize = sizeof(m_struSlaveCameraCalibCfgV51);
    m_struSlaveCameraCalibCfgV51.byCalibMode = m_comboCalibMode.GetCurSel();


    NET_DVR_STD_CONFIG struCfg = { 0 };

    struCfg.lpCondBuffer = &m_struSlaveCameraCond;
    struCfg.dwCondSize = sizeof(m_struSlaveCameraCond);
    struCfg.lpInBuffer = &m_struSlaveCameraCalibCfgV51;
    struCfg.dwInSize = sizeof(m_struSlaveCameraCalibCfgV51);

    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_SLAVECAMERA_CALIB_V51, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SLAVECAMERA_CALIB_V51");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SLAVECAMERA_CALIB_V51");
    }
}

void CDlgEagleEyeCfg::OnBnClickedBtnSetGotoscene()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    m_strGotoSceneCond.dwSceneID = m_comboGotoSceneId.GetCurSel() + 1;
    m_strGotoSceneCond.dwChannel = m_lChannel;
    m_strGotoSceneCond.dwSize = sizeof(m_strGotoSceneCond);

    NET_DVR_STD_CONTROL struCfg = { 0 };
    struCfg.lpCondBuffer = &m_strGotoSceneCond;
    struCfg.dwCondSize = sizeof(m_strGotoSceneCond);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_STDControl(m_lServerID, NET_DVR_SET_GOTOSCENE, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_GOTOSCENE");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_GOTOSCENE");
    }
}

DWORD HexToDecMa1(DWORD wHex)
{
    return (wHex / 4096) * 1000 + ((wHex % 4096) / 256) * 100 + ((wHex % 256) / 16) * 10 + (wHex % 16);
}

void CDlgEagleEyeCfg::OnBnClickedBtnCalib()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    int nItem = 0;
    CString strTemp;

    NET_DVR_PTZPOS m_ptzPos = { 0 };
    DWORD dwReturned;
    BOOL bRet = NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_PTZPOS, 0, &m_ptzPos, sizeof(NET_DVR_PTZPOS), &dwReturned);
    if (!bRet)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PTZPOS");
        return;
    }

    int m_iPara1 = HexToDecMa1(m_ptzPos.wPanPos);
    int m_iPara2 = HexToDecMa1(m_ptzPos.wTiltPos);
    int m_iPara3 = HexToDecMa1(m_ptzPos.wZoomPos);

    nItem = m_lstCalib.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
    strTemp.Format("(%.3f,%.3f)", m_struSlaveCameraCalibCfgV51.struCalibParam[nItem].struCalibCoordinates.fX, \
        m_struSlaveCameraCalibCfgV51.struCalibParam[nItem].struCalibCoordinates.fY);
    m_lstCalib.SetItemText(nItem, 1, strTemp);

    float fP = (float)((float)m_iPara1 / 10);
    float fT = (float)((float)m_iPara2 / 10);
    float fZ = (float)((float)m_iPara3 / 10);

    strTemp.Format("(%.1f,%.1f,%.1f)", fP, fT, fZ);
    m_lstCalib.SetItemText(nItem, 2, strTemp);

    m_struSlaveCameraCalibCfgV51.struCalibParam[nItem].struPtzInfo.fPan = fP;
    m_struSlaveCameraCalibCfgV51.struCalibParam[nItem].struPtzInfo.fTilt = fT;
    m_struSlaveCameraCalibCfgV51.struCalibParam[nItem].struPtzInfo.fZoom = fZ;

}


void CDlgEagleEyeCfg::OnBnClickedBtnCalibDel()
{
    // TODO: Add your control notification handler code here
    int nItem = 0;
    CString strTemp;
    while (m_lstCalib.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED) != -1)
    {
        nItem = m_lstCalib.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
        m_lstCalib.DeleteItem(nItem);

        strTemp.Format("%02d", nItem + 1);
        m_lstCalib.InsertItem(nItem, strTemp);
    }
    memset(&m_struSlaveCameraCalibCfgV51.struCalibParam[nItem], 0, sizeof(NET_DVR_CALIB_PARAM));
}

void CDlgEagleEyeCfg::OnCbnSelchangeComboCalibmode()
{
    // TODO:  在此添加控件通知处理程序代码
    if (m_comboCalibMode.GetCurSel() == 2)
    {
        GetDlgItem(IDC_BTN_CALIB_DEL)->EnableWindow(TRUE);
        GetDlgItem(IDC_BTN_CALIB)->EnableWindow(TRUE);
        GetDlgItem(IDC_LIST_CALIB)->EnableWindow(TRUE);
    }
    else
    {
        GetDlgItem(IDC_BTN_CALIB_DEL)->EnableWindow(FALSE);
        GetDlgItem(IDC_BTN_CALIB)->EnableWindow(FALSE);
        GetDlgItem(IDC_LIST_CALIB)->EnableWindow(FALSE);
    }
}


void CDlgEagleEyeCfg::OnBnClickedSetTrackratio()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    m_struSlaveCameraCond.byID = m_comboSlaveCameraID.GetCurSel() + 2;
    m_struSlaveCameraCond.dwChannel = m_lChannel;
    m_struSlaveCameraCond.dwSize = sizeof(m_struSlaveCameraCond);

    NET_DVR_STD_CONTROL struCfg = { 0 };
    struCfg.lpCondBuffer = &m_struSlaveCameraCond;
    struCfg.dwCondSize = sizeof(m_struSlaveCameraCond);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if (!NET_DVR_STDControl(m_lServerID, NET_DVR_SET_TRACKINGRATIO, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_TRACKINGRATIO");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_TRACKINGRATIO");
    }
}

void CDlgEagleEyeCfg::OnBnClickedBtnTrackGet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    m_struSlaveCameraCond.byID = m_comboSlaveCameraID.GetCurSel() + 2;
    m_struSlaveCameraCond.dwChannel = m_lChannel;
    m_struSlaveCameraCond.dwSize = sizeof(m_struSlaveCameraCond);

    memset(&m_struTracking, 0, sizeof(m_struTracking));
    m_struTracking.dwSize = sizeof(m_struTracking);

    NET_DVR_STD_CONFIG struCfg = { 0 };

    struCfg.lpCondBuffer = &m_struSlaveCameraCond;
    struCfg.dwCondSize = sizeof(m_struSlaveCameraCond);
    struCfg.lpOutBuffer = &m_struTracking;
    struCfg.dwOutSize = sizeof(m_struTracking);

    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_TRACKING, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_TRACKING");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_TRACKING");
    }
    m_combEnabled.SetCurSel(m_struTracking.byEnable);
    m_wTrackTime = m_struTracking.wTrackingTime;
    UpdateData(FALSE);
}


void CDlgEagleEyeCfg::OnBnClickedBtnTrackSet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    m_struSlaveCameraCond.byID = m_comboSlaveCameraID.GetCurSel() + 2;
    m_struSlaveCameraCond.dwChannel = m_lChannel;
    m_struSlaveCameraCond.dwSize = sizeof(m_struSlaveCameraCond);

    m_struTracking.dwSize = sizeof(m_struTracking);
    m_struTracking.byEnable = m_combEnabled.GetCurSel();
    m_struTracking.wTrackingTime = (WORD)m_wTrackTime;
    m_struTracking.byMode = 2;
    NET_DVR_STD_CONFIG struCfg = { 0 };

    struCfg.lpCondBuffer = &m_struSlaveCameraCond;
    struCfg.dwCondSize = sizeof(m_struSlaveCameraCond);
    struCfg.lpInBuffer = &m_struTracking;
    struCfg.dwInSize = sizeof(m_struTracking);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_TRACKING, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_TRACKING");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_TRACKING");
    }

}



void CDlgEagleEyeCfg::OnBnClickedSetinitpositionButton()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    m_struTrackInitPosition.dwSize = sizeof(m_struTrackInitPosition);
    m_struTrackInitPosition.dwChannel = m_lChannel;
    m_struTrackInitPosition.byID = m_SetFollowInitPositionCtrl.GetCurSel() + 1;

    NET_DVR_STD_CONTROL struCfg = { 0 };
    struCfg.lpCondBuffer = &m_struTrackInitPosition;
    struCfg.dwCondSize = sizeof(m_struTrackInitPosition);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_STDControl(m_lServerID, NET_DVR_SET_TRACK_INITPOSTION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_TRACK_INITPOSTION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_TRACK_INITPOSTION");
    }
}


void CDlgEagleEyeCfg::OnBnClickedBtnCoefficientGet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    m_struSlaveCameraCond.byID = m_FcIDCoefficientCtrl.GetCurSel() + 1;
    m_struSlaveCameraCond.dwChannel = m_lChannel;
    m_struSlaveCameraCond.dwSize = sizeof(m_struSlaveCameraCond);

    memset(&m_struTrackingInfo, 0, sizeof(m_struTrackingInfo));
    m_struTrackingInfo.dwSize = sizeof(m_struTrackingInfo);

    NET_DVR_STD_CONFIG struCfg = { 0 };

    struCfg.lpCondBuffer = &m_struSlaveCameraCond;
    struCfg.dwCondSize = sizeof(m_struSlaveCameraCond);
    struCfg.lpOutBuffer = &m_struTrackingInfo;
    struCfg.dwOutSize = sizeof(m_struTrackingInfo);

    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_TRACKINGRATIO_MANUAL, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_TRACKINGRATIO_MANUAL");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_TRACKINGRATIO_MANUAL");
    }

    m_Coefficient = m_struTrackingInfo.byCoefficient;

    UpdateData(FALSE);
}


void CDlgEagleEyeCfg::OnBnClickedBtnCoefficientSet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    m_struSlaveCameraCond.byID = m_FcIDCoefficientCtrl.GetCurSel() + 1;
    m_struSlaveCameraCond.dwChannel = m_lChannel;
    m_struSlaveCameraCond.dwSize = sizeof(m_struSlaveCameraCond);

    m_struTrackingInfo.dwSize = sizeof(m_struTrackingInfo);
    m_struTrackingInfo.byCoefficient = m_Coefficient;

    NET_DVR_STD_CONFIG struCfg = { 0 };

    struCfg.lpCondBuffer = &m_struSlaveCameraCond;
    struCfg.dwCondSize = sizeof(m_struSlaveCameraCond);
    struCfg.lpInBuffer = &m_struTrackingInfo;
    struCfg.dwInSize = sizeof(m_struTrackingInfo);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_TRACKINGRATIO_MANUAL, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_TRACKINGRATIO_MANUAL");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_TRACKINGRATIO_MANUAL");
    }
}


void CDlgEagleEyeCfg::OnBnClickedGetResolutiontypeButton()
{
    // TODO:  在此添加控件通知处理程序代码
    memset(&m_struResolutionSwitch, 0, sizeof(m_struResolutionSwitch));

    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &m_struResolutionSwitch;
    struCfg.dwOutSize = sizeof(m_struResolutionSwitch);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_RESOLUTION_SWITCH, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_RESOLUTION_SWITCH");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_RESOLUTION_SWITCH");
    }

    m_resolutiontypectrl.SetCurSel(m_struResolutionSwitch.byResolutionType);
    //   m_byFocusZoom = m_struFireDetection.byFocusZoom;
    UpdateData(FALSE);
}


void CDlgEagleEyeCfg::OnBnClickedSetResolutiontypeButton()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    memset(&m_struResolutionSwitch, 0, sizeof(m_struResolutionSwitch));

    m_struResolutionSwitch.byResolutionType = m_resolutiontypectrl.GetCurSel();
    m_struResolutionSwitch.dwSize = sizeof(m_struResolutionSwitch);

    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &m_struResolutionSwitch;
    struCfg.dwInSize = sizeof(m_struResolutionSwitch);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_RESOLUTION_SWITCH, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_RESOLUTION_SWITCH");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_RESOLUTION_SWITCH");
    }
}


void CDlgEagleEyeCfg::OnBnClickedGetLinkageButton()
{
    memset(&m_struLinkage, 0, sizeof(m_struLinkage));

    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &m_struLinkage;
    struCfg.dwOutSize = sizeof(m_struLinkage);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_PANORAMA_LINKAGE, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PANORAMA_LINKAGE");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PANORAMA_LINKAGE");
    }

    m_cmbLinkage.SetCurSel(m_struLinkage.byEnable);

}


void CDlgEagleEyeCfg::OnBnClickedSetLinkageButton()
{
    memset(&m_struLinkage, 0, sizeof(m_struLinkage));

    m_struLinkage.byEnable = m_cmbLinkage.GetCurSel();
    m_struLinkage.dwSize = sizeof(m_struLinkage);

    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &m_struLinkage;
    struCfg.dwInSize = sizeof(m_struLinkage);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_PANORAMA_LINKAGE, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_PANORAMA_LINKAGE");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_PANORAMA_LINKAGE");
    }
}
