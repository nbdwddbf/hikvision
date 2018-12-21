// DlgManualThermCfg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgManualThermCfg.h"
#include "afxdialogex.h"
#include "DrawFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CDlgManualThermCfg 对话框

#define WM_MSG_ADD_MANUALTHERM_INFO_TOLIST 1001
#define WM_MSG_GET_MANUALTHERM_INFO_FINISH 1002

IMPLEMENT_DYNAMIC(CDlgManualThermCfg, CDialogEx)

CDlgManualThermCfg::CDlgManualThermCfg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgManualThermCfg::IDD, pParent)
    , m_ctCurrentDate(0)
    , m_ctCurrentTime(0)
    , m_fHumidity(0)
    , m_iRuleID(0)
    , m_fTemperture(0)
    , m_iDistance(0)
    , m_fEmissivity(0)
{
    m_lManualThremInfoHandle = -1;
    m_bDrawEnd = FALSE;
    m_nDrawPointNum = 0;
    m_bSelectItem = FALSE;
    m_iRowCount = -1;
    m_iItem = -1;
    m_iSubItem = -1;
    m_iLastItem = -1;
    memset(&m_struPolyGon, 0, sizeof(m_struPolyGon));
    memset(&m_struLine, 0, sizeof(m_struLine));
    memset(&m_struManualThermometry, 0, sizeof(m_struManualThermometry));
}

CDlgManualThermCfg::~CDlgManualThermCfg()
{
    StopRealPlay();

    if (m_lManualThremInfoHandle >= 0)
    {
        NET_DVR_StopRemoteConfig(m_lManualThremInfoHandle);
        m_lManualThremInfoHandle = -1;
    }
}

void CDlgManualThermCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_CRUISE_MODE, m_comboCruiseMode);
    DDX_DateTimeCtrl(pDX, IDC_DATETIME_CURRENT_DATE, m_ctCurrentDate);
    DDX_DateTimeCtrl(pDX, IDC_DATETIME_CURRENT_TIME, m_ctCurrentTime);
    DDX_Text(pDX, IDC_EDIT_HUMIDITY, m_fHumidity);
    DDX_Text(pDX, IDC_EDIT_RULE_ID, m_iRuleID);
    DDX_Text(pDX, IDC_EDIT_TEMPERATURE, m_fTemperture);
    DDX_Control(pDX, IDC_LIST_MANUALTHERM_INFO, m_listManualThermInfo);
    DDX_Control(pDX, IDC_COMBO_BOX, m_comboBox);
    DDX_Control(pDX, IDC_EDIT_TEXT_BOX, m_editTextBox);
    DDX_Text(pDX, IDC_EDIT_DISTANCE, m_iDistance);
    DDX_Text(pDX, IDC_EDIT_EMISSIVITY, m_fEmissivity);
}


BEGIN_MESSAGE_MAP(CDlgManualThermCfg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_GET_CRUISE, &CDlgManualThermCfg::OnBnClickedButtonGetCruise)
    ON_BN_CLICKED(IDC_BUTTON_GET_TEMP_HUMI, &CDlgManualThermCfg::OnBnClickedButtonGetTempHumi)
    ON_BN_CLICKED(IDC_BUTTON_GET_MANUALTHERM_INFO, &CDlgManualThermCfg::OnBnClickedButtonGetManualthermInfo)
    ON_BN_CLICKED(IDC_BUTTON_SET_MANUALTHERM_INFO, &CDlgManualThermCfg::OnBnClickedButtonSetManualthermInfo)
    ON_NOTIFY(NM_CLICK, IDC_LIST_MANUALTHERM_INFO, &CDlgManualThermCfg::OnNMClickListManualthermInfo)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST_MANUALTHERM_INFO, &CDlgManualThermCfg::OnNMDblclkListManualthermInfo)
    ON_EN_KILLFOCUS(IDC_EDIT_TEXT_BOX, &CDlgManualThermCfg::OnEnKillfocusEditTextBox)
    ON_CBN_KILLFOCUS(IDC_COMBO_BOX, &CDlgManualThermCfg::OnCbnKillfocusComboBox)
    ON_BN_CLICKED(IDC_BUTTON_ADD, &CDlgManualThermCfg::OnBnClickedButtonAdd)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDlgManualThermCfg::OnBnClickedButtonDelete)
    ON_MESSAGE(WM_MSG_ADD_MANUALTHERM_INFO_TOLIST, OnMsgAddManualThermInfoToList)
    ON_MESSAGE(WM_MSG_GET_MANUALTHERM_INFO_FINISH, OnMsgManualThermInfoFinish)
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONDOWN()
    ON_WM_RBUTTONDOWN()
    ON_BN_CLICKED(IDC_BUTTON_GET_MANUALTHERM_BASIC, &CDlgManualThermCfg::OnBnClickedButtonGetManualthermBasic)
    ON_BN_CLICKED(IDC_BUTTON_SET_MANUALTHERM_BASIC, &CDlgManualThermCfg::OnBnClickedButtonSetManualthermBasic)
    ON_BN_CLICKED(IDC_BUTTON_DELETE_RULE, &CDlgManualThermCfg::OnBnClickedButtonDeleteRule)
END_MESSAGE_MAP()


// CDlgManualThermCfg 消息处理程序

void CALLBACK g_ManualThermDraw(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
    CDlgManualThermCfg* pDlg = (CDlgManualThermCfg*)dwUser;

    if (pDlg != NULL)
    {
        pDlg->DrawRgnFun(hDc);
    }
}

void CALLBACK g_fGetManualThermInfoCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CDlgManualThermCfg* pDlg = (CDlgManualThermCfg*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
    pDlg->ProcessGetManualThermInfoCallbackData(dwType, lpBuffer, dwBufLen);
}

BOOL CDlgManualThermCfg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    GetDlgItem(IDC_STATIC_PREVIEW)->GetWindowRect(&m_rcPlayWnd);
    ScreenToClient(&m_rcPlayWnd);

    StartRealPlay(GetDlgItem(IDC_STATIC_PREVIEW)->GetSafeHwnd(), g_ManualThermDraw, this, m_lChannel);

    char szLan[64] = { 0 };
    g_StringLanType(szLan, "连续", "continuous");
    m_comboCruiseMode.InsertString(0, szLan);
    g_StringLanType(szLan, "预置点", "preset");
    m_comboCruiseMode.InsertString(1, szLan);

    char szLanTemp[128] = { 0 };
    m_listManualThermInfo.SetExtendedStyle(m_listManualThermInfo.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES);
    g_StringLanType(szLanTemp, "序号", "N0");
    m_listManualThermInfo.InsertColumn(0, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "相对时标", "Relative Time");
    m_listManualThermInfo.InsertColumn(1, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "绝对时标", "Abs Time");
    m_listManualThermInfo.InsertColumn(2, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "测温单位", "Unit");
    m_listManualThermInfo.InsertColumn(3, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "数据状态", "Data Type");
    m_listManualThermInfo.InsertColumn(4, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "规则ID", "Rule ID");
    m_listManualThermInfo.InsertColumn(5, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "使能", "Eanble");
    m_listManualThermInfo.InsertColumn(6, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "规则名称", "Rule Name");
    m_listManualThermInfo.InsertColumn(7, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "标定类型", "Calibration Type");
    m_listManualThermInfo.InsertColumn(8, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "当前温度", "Current Temperature");
    m_listManualThermInfo.InsertColumn(9, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "点测温坐标", "Point");
    m_listManualThermInfo.InsertColumn(10, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "最高温", "Max Temperature");
    m_listManualThermInfo.InsertColumn(11, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "最低温", "Min Temperature");
    m_listManualThermInfo.InsertColumn(12, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "平均温", "Average Temperature");
    m_listManualThermInfo.InsertColumn(13, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "温差", "Temperature difference");
    m_listManualThermInfo.InsertColumn(14, szLanTemp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLanTemp, "测温区域", "Region");
    m_listManualThermInfo.InsertColumn(15, szLanTemp, LVCFMT_LEFT, 60, -1);

    m_iRowCount = m_listManualThermInfo.GetItemCount();  //获取行数

    m_editTextBox.ShowWindow(SW_HIDE);
    m_comboBox.ShowWindow(SW_HIDE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}

void CDlgManualThermCfg::DrawRgnFun(HDC hDc)
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


void CDlgManualThermCfg::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default

    __super::OnLButtonDown(nFlags, point);

    UpdateData(TRUE);

    //m_bDrawEnd = FALSE;

    if (!m_rcPlayWnd.PtInRect(point))
    {
        return;
    }

    if (m_iSubItem != 8)
    {
        return;
    }

    if (0 == m_comboBox.GetCurSel())
    {
        NET_VCA_POINT&  struPoint = m_struManualThermometry.struRuleInfo.struPointTherm.struPoint;
        struPoint.fX = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
        struPoint.fY = (float)(point.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();
        //return;
    }
    else if (1 == m_comboBox.GetCurSel())
    {
        NET_VCA_POLYGON&  struRegion = m_struManualThermometry.struRuleInfo.struRegionTherm.struRegion;
        if (m_bDrawEnd || m_nDrawPointNum >= VCA_MAX_POLYGON_POINT_NUM)
        {
            m_bDrawEnd = FALSE;
            memset(&struRegion, 0, sizeof(struRegion));
            //  return;
        }
        struRegion.struPos[m_nDrawPointNum].fX = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
        struRegion.struPos[m_nDrawPointNum].fY = (float)(point.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();
        m_nDrawPointNum++;

        memcpy(&m_struPolyGon, &struRegion, sizeof(NET_VCA_POLYGON));
    }
    else if (2 == m_comboBox.GetCurSel())
    {
        NET_VCA_POLYGON&  struRegion = m_struManualThermometry.struRuleInfo.struRegionTherm.struRegion;

        if (m_bDrawEnd || m_nDrawPointNum >= 2)
        {
            m_bDrawEnd = FALSE;
            memset(&struRegion, 0, sizeof(struRegion));
            //  return;
        }
        struRegion.struPos[m_nDrawPointNum].fX = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
        struRegion.struPos[m_nDrawPointNum].fY = (float)(point.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();
        m_nDrawPointNum++;
        memcpy(&m_struPolyGon, &struRegion, sizeof(NET_VCA_POLYGON));

        if (2 == m_nDrawPointNum)
        {
            m_bDrawEnd = TRUE;
            m_nDrawPointNum = 0;
        }
    }

}

void CDlgManualThermCfg::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default

    __super::OnMouseMove(nFlags, point);

    if (m_bDrawEnd)
    {
        return;
    }

    if (m_iSubItem != 8)
    {
        return;
    }

    if (!m_rcPlayWnd.PtInRect(point))
    {
        return;
    }

    if (0 == m_comboBox.GetCurSel())
    {
        return;
    }
    else if (1 == m_comboBox.GetCurSel())
    {

        NET_VCA_POLYGON&  struRegion = m_struManualThermometry.struRuleInfo.struRegionTherm.struRegion;

        struRegion.struPos[m_nDrawPointNum].fX = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
        struRegion.struPos[m_nDrawPointNum].fY = (float)(point.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();
        struRegion.dwPointNum = m_nDrawPointNum + 1;

        memcpy(&m_struPolyGon, &struRegion, sizeof(NET_VCA_POLYGON));
    }
    else if (2 == m_comboBox.GetCurSel())
    {
        NET_VCA_POLYGON&  struRegion = m_struManualThermometry.struRuleInfo.struRegionTherm.struRegion;

        struRegion.struPos[m_nDrawPointNum].fX = (float)(point.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
        struRegion.struPos[m_nDrawPointNum].fY = (float)(point.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();
        struRegion.dwPointNum = m_nDrawPointNum + 1;

        memcpy(&m_struPolyGon, &struRegion, sizeof(NET_VCA_POLYGON));
    }

}

void CDlgManualThermCfg::OnRButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default

    __super::OnRButtonDown(nFlags, point);

    if (!m_rcPlayWnd.PtInRect(point))
    {
        return;
    }

    if (m_iSubItem != 8)
    {
        return;
    }

    //测温
    if (0 == m_comboBox.GetCurSel())
    {
        return;
    }
    else if (1 == m_comboBox.GetCurSel())
    {
        NET_VCA_POLYGON&  struRegion = m_struManualThermometry.struRuleInfo.struRegionTherm.struRegion;
        if (m_nDrawPointNum >= 20 || m_nDrawPointNum < 3)
        {
            memset(&struRegion, 0, sizeof(struRegion));
            return;
        }

        struRegion.dwPointNum = m_nDrawPointNum;

        memcpy(&m_struPolyGon, &struRegion, sizeof(NET_VCA_POLYGON));
    }
    else if (2 == m_comboBox.GetCurSel())
    {
        NET_VCA_POLYGON&  struRegion = m_struManualThermometry.struRuleInfo.struRegionTherm.struRegion;
        if (m_nDrawPointNum > 2)
        {
            memset(&struRegion, 0, sizeof(struRegion));
            return;
        }

        struRegion.dwPointNum = m_nDrawPointNum;

        memcpy(&m_struPolyGon, &struRegion, sizeof(NET_VCA_POLYGON));
    }
    m_nDrawPointNum = 0;

    m_bDrawEnd = TRUE;


}

void CDlgManualThermCfg::ProcessGetManualThermInfoCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{
    CString strItem = "";
    if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        LPNET_SDK_MANUAL_THERMOMETRY lpManualThermometry = new NET_SDK_MANUAL_THERMOMETRY;
        memcpy(lpManualThermometry, lpBuffer, sizeof(*lpManualThermometry));
        PostMessage(WM_MSG_ADD_MANUALTHERM_INFO_TOLIST, (WPARAM)lpManualThermometry, 0);
    }
    else if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
        DWORD dwStatus = *(DWORD*)lpBuffer;
        if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            PostMessage(WM_MSG_GET_MANUALTHERM_INFO_FINISH, 0, 0);
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
        {
            DWORD dwErrCode = *(DWORD*)((char *)lpBuffer + 4);

            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_MANUALTHERM_INFO, Error code %d", dwErrCode);
        }
    }
}

LRESULT CDlgManualThermCfg::OnMsgAddManualThermInfoToList(WPARAM wParam, LPARAM lParam)
{
    LPNET_SDK_MANUAL_THERMOMETRY lpManualThermometry = (LPNET_SDK_MANUAL_THERMOMETRY)wParam;

    int iItemCount = m_listManualThermInfo.GetItemCount();

    m_listManualThermInfo.InsertItem(iItemCount, "");

    char szStr[512] = { 0 };

    sprintf(szStr, "%d", iItemCount);
    m_listManualThermInfo.SetItemText(iItemCount, 0, szStr);

    sprintf(szStr, "%d", lpManualThermometry->dwRelativeTime);
    m_listManualThermInfo.SetItemText(iItemCount, 1, szStr);

    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%d", lpManualThermometry->dwAbsTime);
    m_listManualThermInfo.SetItemText(iItemCount, 2, szStr);

    memset(szStr, 0, sizeof(szStr));
    if (0 == lpManualThermometry->byThermometryUnit)
    {
        g_StringLanType(szStr, "摄氏度", "℃");
    }
    else if (1 == lpManualThermometry->byThermometryUnit)
    {
        g_StringLanType(szStr, "华氏度", "℉");
    }
    else if (2 == lpManualThermometry->byThermometryUnit)
    {
        g_StringLanType(szStr, "开尔文", "K");
    }
    m_listManualThermInfo.SetItemText(iItemCount, 3, szStr);

    memset(szStr, 0, sizeof(szStr));
    if (0 == lpManualThermometry->byDataType)
    {
        g_StringLanType(szStr, "检测中", "testing");
    }
    else if (1 == lpManualThermometry->byDataType)
    {
        g_StringLanType(szStr, "开始", "begin");
    }
    else if (2 == lpManualThermometry->byDataType)
    {
        g_StringLanType(szStr, "结束", "end");
    }
    m_listManualThermInfo.SetItemText(iItemCount, 4, szStr);

    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%d", lpManualThermometry->struRuleInfo.byRuleID);
    m_listManualThermInfo.SetItemText(iItemCount, 5, szStr);

    memset(szStr, 0, sizeof(szStr));
    if (1 == lpManualThermometry->struRuleInfo.byEnable)
    {
        g_StringLanType(szStr, "启用", "enable");
    }
    else if (0 == lpManualThermometry->struRuleInfo.byEnable)
    {
        g_StringLanType(szStr, "不启用", "disable");
    }
    m_listManualThermInfo.SetItemText(iItemCount, 6, szStr);

    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%s", lpManualThermometry->struRuleInfo.szRuleName);
    m_listManualThermInfo.SetItemText(iItemCount, 7, szStr);

    memset(szStr, 0, sizeof(szStr));
    if (0 == lpManualThermometry->struRuleInfo.byRuleCalibType)
    {
        g_StringLanType(szStr, "点", "point");
    }
    else if (1 == lpManualThermometry->struRuleInfo.byRuleCalibType)
    {
        g_StringLanType(szStr, "框", "box");
    }
    else if (2 == lpManualThermometry->struRuleInfo.byRuleCalibType)
    {
        g_StringLanType(szStr, "线", "line");
    }
    m_listManualThermInfo.SetItemText(iItemCount, 8, szStr);

    if (0 == lpManualThermometry->struRuleInfo.byRuleCalibType)
    {
        memset(szStr, 0, sizeof(szStr));
        sprintf(szStr, "%f", lpManualThermometry->struRuleInfo.struPointTherm.fPointTemperature);
        m_listManualThermInfo.SetItemText(iItemCount, 9, szStr);

        memset(szStr, 0, sizeof(szStr));
        sprintf(szStr, "x:%f,y:%f", lpManualThermometry->struRuleInfo.struPointTherm.struPoint.fX, lpManualThermometry->struRuleInfo.struPointTherm.struPoint.fY);
        m_listManualThermInfo.SetItemText(iItemCount, 10, szStr);
    }
    else if (1 == lpManualThermometry->struRuleInfo.byRuleCalibType || 2 == lpManualThermometry->struRuleInfo.byRuleCalibType)
    {
        memset(szStr, 0, sizeof(szStr));
        sprintf(szStr, "%f", lpManualThermometry->struRuleInfo.struRegionTherm.fMaxTemperature);
        m_listManualThermInfo.SetItemText(iItemCount, 11, szStr);

        memset(szStr, 0, sizeof(szStr));
        sprintf(szStr, "%f", lpManualThermometry->struRuleInfo.struRegionTherm.fMinTemperature);
        m_listManualThermInfo.SetItemText(iItemCount, 12, szStr);

        memset(szStr, 0, sizeof(szStr));
        sprintf(szStr, "%f", lpManualThermometry->struRuleInfo.struRegionTherm.fAverageTemperature);
        m_listManualThermInfo.SetItemText(iItemCount, 13, szStr);

        memset(szStr, 0, sizeof(szStr));
        sprintf(szStr, "%f", lpManualThermometry->struRuleInfo.struRegionTherm.fTemperatureDiff);
        m_listManualThermInfo.SetItemText(iItemCount, 14, szStr);

        memset(szStr, 0, sizeof(szStr));
        int iPointNum = lpManualThermometry->struRuleInfo.struRegionTherm.struRegion.dwPointNum;
        for (int i = 0; i < iPointNum; i++)
        {
            float fX = lpManualThermometry->struRuleInfo.struRegionTherm.struRegion.struPos[i].fX;
            float fY = lpManualThermometry->struRuleInfo.struRegionTherm.struRegion.struPos[i].fY;
            sprintf(szStr, "%sX%d:%f,Y%d:%f;", szStr, i + 1, fX, i + 1, fY);
        }
        m_listManualThermInfo.SetItemText(iItemCount, 15, szStr);
    }

    return 0;

}

LRESULT CDlgManualThermCfg::OnMsgManualThermInfoFinish(WPARAM wParam, LPARAM lParam)
{
    if (m_lManualThremInfoHandle > 0)
    {
        NET_DVR_StopRemoteConfig(m_lManualThremInfoHandle);
        m_lManualThremInfoHandle = -1;
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_MANUALTHERM_INFO Get finish");
    }
    return 0;
}

void CDlgManualThermCfg::OnBnClickedButtonGetCruise()
{
    // TODO:  在此添加控件通知处理程序代码

    UpdateData(TRUE);

    char szStatusBuf[ISAPI_STATUS_LEN] = { 0 };

    NET_DVR_CRUISE_PARAM struCruiseParam = { 0 };
    NET_DVR_STD_CONFIG struStdConfig = { 0 };

    struCruiseParam.dwSize = sizeof(struCruiseParam);

    struStdConfig.lpCondBuffer = &m_lChannel;
    struStdConfig.dwCondSize = sizeof(m_lChannel);
    struStdConfig.lpInBuffer = NULL;
    struStdConfig.dwInSize = 0;
    struStdConfig.lpOutBuffer = (LPVOID)&struCruiseParam;
    struStdConfig.dwOutSize = sizeof(struCruiseParam);

    struStdConfig.lpStatusBuffer = szStatusBuf;
    struStdConfig.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_CRUISE_INFO, &struStdConfig))
    {
        OutputDebugString(szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_CRUISE_INFO");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_CRUISE_INFO");
    }
    m_comboCruiseMode.SetCurSel(struCruiseParam.byCruiseMode);

    UpdateData(FALSE);
}


void CDlgManualThermCfg::OnBnClickedButtonGetTempHumi()
{
    // TODO:  在此添加控件通知处理程序代码

    UpdateData(TRUE);

    char szStatusBuf[ISAPI_STATUS_LEN] = { 0 };

    NET_DVR_TEMP_HUMI_INFO struTempHumiInfo = { 0 };
    NET_DVR_STD_CONFIG struStdConfig = { 0 };

    struTempHumiInfo.dwSize = sizeof(struTempHumiInfo);

    struStdConfig.lpCondBuffer = &m_lChannel;
    struStdConfig.dwCondSize = sizeof(m_lChannel);
    struStdConfig.lpInBuffer = NULL;
    struStdConfig.dwInSize = 0;
    struStdConfig.lpOutBuffer = (LPVOID)&struTempHumiInfo;
    struStdConfig.dwOutSize = sizeof(struTempHumiInfo);

    struStdConfig.lpStatusBuffer = szStatusBuf;
    struStdConfig.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_TEMP_HUMI_INFO, &struStdConfig))
    {
        OutputDebugString(szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_TEMP_HUMI_INFO");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_TEMP_HUMI_INFO");
    }
    if (struTempHumiInfo.struCurrentTime.wYear != 0)
    {
        CTime ctimeTemp(struTempHumiInfo.struCurrentTime.wYear, struTempHumiInfo.struCurrentTime.byMonth, struTempHumiInfo.struCurrentTime.byDay,
            struTempHumiInfo.struCurrentTime.byHour, struTempHumiInfo.struCurrentTime.byMinute, struTempHumiInfo.struCurrentTime.bySecond);
        m_ctCurrentDate = ctimeTemp;
        m_ctCurrentTime = ctimeTemp;
    }

    m_fTemperture = struTempHumiInfo.fTemperature;
    m_fHumidity = struTempHumiInfo.fHumidity;

    UpdateData(FALSE);
}


void CDlgManualThermCfg::OnBnClickedButtonGetManualthermInfo()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    char szLan[128] = { 0 };

    NET_DVR_REALTIME_THERMOMETRY_COND struCond = { 0 };
    struCond.dwSize = sizeof(NET_DVR_REALTIME_THERMOMETRY_COND);
    struCond.dwChan = m_lChannel;
    struCond.byRuleID = m_iRuleID;

    if (m_lManualThremInfoHandle >= 0)
    {
        if (!NET_DVR_StopRemoteConfig(m_lManualThremInfoHandle))
        {
            g_StringLanType(szLan, "手动测温实时获取失败", "Stop Manual measuring temperature real time acquisition Failed");
            AfxMessageBox(szLan);
        }
        else
        {
            m_lManualThremInfoHandle = -1;
            g_StringLanType(szLan, "获取", "Get");
            GetDlgItem(IDC_BUTTON_GET_MANUALTHERM_INFO)->SetWindowText(szLan);
            return;
        }
    }

    m_lManualThremInfoHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_GET_MANUALTHERM_INFO, &struCond, sizeof(struCond), g_fGetManualThermInfoCallback, this);
    if (m_lManualThremInfoHandle >= 0)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_MANUALTHERM_INFO Chan[%d]", m_lChannel);
        g_StringLanType(szLan, "停止获取", "Stop get");
        GetDlgItem(IDC_BUTTON_GET_MANUALTHERM_INFO)->SetWindowText(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_MANUALTHERM_INFO Chan[%d]", m_lChannel);
        g_StringLanType(szLan, "手动测温实时获取失败", "Get Manual measuring temperature real time acquisition  Failed");
        AfxMessageBox(szLan);
        return;
    }
}


void CDlgManualThermCfg::OnBnClickedButtonSetManualthermInfo()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    if (!m_bSelectItem)
    {
        MessageBox("Please select item!");
        return;
    }

    char szStatusBuf[ISAPI_STATUS_LEN] = { 0 };

    m_struManualThermometry.dwChannel = m_lChannel;

    NET_DVR_STD_CONFIG struStdConfig = { 0 };

    m_struManualThermometry.dwSize = sizeof(m_struManualThermometry);

    struStdConfig.lpCondBuffer = (LPVOID)&m_lChannel;
    struStdConfig.dwCondSize = sizeof(m_lChannel);
    struStdConfig.lpInBuffer = (LPVOID)&m_struManualThermometry;
    struStdConfig.dwInSize = sizeof(m_struManualThermometry);

    struStdConfig.lpStatusBuffer = szStatusBuf;
    struStdConfig.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_MANUALTHERM, &struStdConfig))
    {
        OutputDebugString(szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_MANUALTHERM");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_MANUALTHERM");
    }

    UpdateData(FALSE);
}




void CDlgManualThermCfg::OnNMClickListManualthermInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // TODO:  在此添加控件通知处理程序代码

    m_iLastItem = pNMItemActivate->iItem;
    m_iSubItem = pNMItemActivate->iSubItem;
    m_bSelectItem = TRUE;

    *pResult = 0;
}


void CDlgManualThermCfg::OnNMDblclkListManualthermInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // TODO:  在此添加控件通知处理程序代码

    char szStr[128] = { 0 };

    CRect  EditRect;
    m_iItem = pNMItemActivate->iItem;
    m_iSubItem = pNMItemActivate->iSubItem;

    if (m_iItem == -1)
    {
        return;
    }
    switch (m_iSubItem)
    {
    case 0:
    case 1:
    case 2:
    case 4:
    case 10://点测温坐标
    case 15://区域、线
        break;
    case 3://测温单位
        if (m_iItem < m_iRowCount)
        {
            m_comboBox.ResetContent();
            g_StringLanType(szStr, "摄氏度", "℃");
            m_comboBox.InsertString(0, szStr);
            g_StringLanType(szStr, "华氏度", "℉");
            m_comboBox.InsertString(1, szStr);
            g_StringLanType(szStr, "开尔文", "K");
            m_comboBox.InsertString(2, szStr);
            m_comboBox.SetCurSel(0);

            m_listManualThermInfo.GetSubItemRect(m_iItem, m_iSubItem, LVIR_LABEL, EditRect);
            m_comboBox.SetParent(&m_listManualThermInfo); //将list control设置为父窗口,生成的ComboBox才能正确定位

            EditRect.SetRect(EditRect.left, EditRect.top, EditRect.left + m_listManualThermInfo.GetColumnWidth(m_iSubItem), EditRect.bottom);

            //将选中的list控件中的内容copy到edit控件中
            CString strItem = m_listManualThermInfo.GetItemText(m_iItem, m_iSubItem);
            m_comboBox.MoveWindow(&EditRect);
            m_comboBox.ShowWindow(SW_SHOW);
            m_comboBox.SetWindowText(strItem);
            m_comboBox.SetFocus();//设置为焦点
        }
        else
        {
            m_comboBox.ShowWindow(SW_HIDE);
        }
        break;
    case 6://使能
        if (m_iItem < m_iRowCount)
        {
            m_comboBox.ResetContent();
            g_StringLanType(szStr, "不启用", "disable");
            m_comboBox.InsertString(0, szStr);
            g_StringLanType(szStr, "启用", "enable");
            m_comboBox.InsertString(1, szStr);
            m_comboBox.SetCurSel(0);

            m_listManualThermInfo.GetSubItemRect(m_iItem, m_iSubItem, LVIR_LABEL, EditRect);
            m_comboBox.SetParent(&m_listManualThermInfo); //将list control设置为父窗口,生成的ComboBox才能正确定位

            EditRect.SetRect(EditRect.left, EditRect.top, EditRect.left + m_listManualThermInfo.GetColumnWidth(m_iSubItem), EditRect.bottom);

            //将选中的list控件中的内容copy到edit控件中
            CString strItem = m_listManualThermInfo.GetItemText(m_iItem, m_iSubItem);
            m_comboBox.MoveWindow(&EditRect);
            m_comboBox.ShowWindow(SW_SHOW);
            m_comboBox.SetWindowText(strItem);
            m_comboBox.SetFocus();//设置为焦点
        }
        else
        {
            m_comboBox.ShowWindow(SW_HIDE);
        }
        break;
    case 8://规则标定类型
        if (m_iItem < m_iRowCount)
        {
            m_comboBox.ResetContent();
            g_StringLanType(szStr, "点", "point");
            m_comboBox.InsertString(0, szStr);
            g_StringLanType(szStr, "框", "box");
            m_comboBox.InsertString(1, szStr);
            g_StringLanType(szStr, "线", "line");
            m_comboBox.InsertString(2, szStr);
            m_comboBox.SetCurSel(0);

            m_listManualThermInfo.GetSubItemRect(m_iItem, m_iSubItem, LVIR_LABEL, EditRect);
            m_comboBox.SetParent(&m_listManualThermInfo); //将list control设置为父窗口,生成的ComboBox才能正确定位

            EditRect.SetRect(EditRect.left, EditRect.top, EditRect.left + m_listManualThermInfo.GetColumnWidth(m_iSubItem), EditRect.bottom);

            //将选中的list控件中的内容copy到edit控件中
            CString strItem = m_listManualThermInfo.GetItemText(m_iItem, m_iSubItem);
            m_comboBox.MoveWindow(&EditRect);
            m_comboBox.ShowWindow(SW_SHOW);
            m_comboBox.SetWindowText(strItem);
            m_comboBox.SetFocus();//设置为焦点
        }
        else
        {
            m_comboBox.ShowWindow(SW_HIDE);
        }
        break;
    case 5:
    case 7:
    case 9:
    case 11:
    case 12:
    case 13:
    case 14:
        if (m_iItem < m_iRowCount)
        {
            m_listManualThermInfo.GetSubItemRect(m_iItem, m_iSubItem, LVIR_LABEL, EditRect);
            m_editTextBox.SetParent(&m_listManualThermInfo); //将list control设置为父窗口,生成的Edit才能正确定位

            EditRect.SetRect(EditRect.left, EditRect.top, EditRect.left + m_listManualThermInfo.GetColumnWidth(m_iSubItem), EditRect.bottom);

            //将选中的list控件中的内容copy到edit控件中
            CString strItem = m_listManualThermInfo.GetItemText(m_iItem, m_iSubItem);
            m_editTextBox.MoveWindow(&EditRect);
            m_editTextBox.ShowWindow(SW_SHOW);
            m_editTextBox.SetWindowText(strItem);
            m_editTextBox.SetFocus();//设置为焦点
            m_editTextBox.SetSel(0, -1);  //0,-1表示单元格内容全选中
        }
        else
        {
            m_editTextBox.ShowWindow(SW_HIDE);
        }
        break;
    default:
        break;
    }

    *pResult = 0;
}

void CDlgManualThermCfg::SaveParam()
{
    // TODO:  在此添加控件通知处理程序代码
    char  szListStr[128] = { 0 };

    m_listManualThermInfo.GetItemText(m_iLastItem, 3, szListStr, 128);
    if (0 == strcmp(szListStr, "摄氏度") || 0 == strcmp(szListStr, "℃"))
    {
        m_struManualThermometry.byThermometryUnit = 0;
    }
    else if (0 == strcmp(szListStr, "华氏度") || 0 == strcmp(szListStr, "℉"))
    {
        m_struManualThermometry.byThermometryUnit = 1;
    }
    else if (0 == strcmp(szListStr, "开尔文") || 0 == strcmp(szListStr, "K"))
    {
        m_struManualThermometry.byThermometryUnit = 2;
    }

    m_listManualThermInfo.GetItemText(m_iLastItem, 5, szListStr, 128);
    m_struManualThermometry.struRuleInfo.byRuleID = atoi(szListStr);

    m_listManualThermInfo.GetItemText(m_iLastItem, 6, szListStr, 128);
    if (0 == strcmp(szListStr, "不启用") || 0 == strcmp(szListStr, "disable"))
    {
        m_struManualThermometry.struRuleInfo.byEnable = 0;
    }
    else if (0 == strcmp(szListStr, "启用") || 0 == strcmp(szListStr, "enable"))
    {
        m_struManualThermometry.struRuleInfo.byEnable = 1;
    }

    m_listManualThermInfo.GetItemText(m_iLastItem, 7, szListStr, 128);
    memcpy(m_struManualThermometry.struRuleInfo.szRuleName, szListStr, NAME_LEN);

    m_listManualThermInfo.GetItemText(m_iLastItem, 8, szListStr, 128);
    if (0 == strcmp(szListStr, "点") || 0 == strcmp(szListStr, "point"))
    {
        m_struManualThermometry.struRuleInfo.byRuleCalibType = 0;
    }
    else if (0 == strcmp(szListStr, "框") || 0 == strcmp(szListStr, "box"))
    {
        m_struManualThermometry.struRuleInfo.byRuleCalibType = 1;
    }
    else if (0 == strcmp(szListStr, "线") || 0 == strcmp(szListStr, "line"))
    {
        m_struManualThermometry.struRuleInfo.byRuleCalibType = 2;
    }

    m_listManualThermInfo.GetItemText(m_iLastItem, 9, szListStr, 128);
    m_struManualThermometry.struRuleInfo.struPointTherm.fPointTemperature = atof(szListStr);

    m_listManualThermInfo.GetItemText(m_iLastItem, 11, szListStr, 128);
    m_struManualThermometry.struRuleInfo.struRegionTherm.fMaxTemperature = atof(szListStr);

    m_listManualThermInfo.GetItemText(m_iLastItem, 12, szListStr, 128);
    m_struManualThermometry.struRuleInfo.struRegionTherm.fMinTemperature = atof(szListStr);

    m_listManualThermInfo.GetItemText(m_iLastItem, 13, szListStr, 128);
    m_struManualThermometry.struRuleInfo.struRegionTherm.fAverageTemperature = atof(szListStr);

    m_listManualThermInfo.GetItemText(m_iLastItem, 14, szListStr, 128);
    m_struManualThermometry.struRuleInfo.struRegionTherm.fTemperatureDiff = atof(szListStr);
}

void CDlgManualThermCfg::OnEnKillfocusEditTextBox()
{
    // TODO:  在此添加控件通知处理程序代码
    CString  csEditStr;
    char  szListStr[128] = { 0 };
    m_listManualThermInfo.GetItemText(m_iItem, m_iSubItem, szListStr, 128);
    m_editTextBox.GetWindowText(csEditStr);
    if (csEditStr.Compare(szListStr))
    {
        m_listManualThermInfo.SetItemText(m_iItem, m_iSubItem, csEditStr);
        m_iLastItem = m_iItem;
        SaveParam();
    }
    m_editTextBox.ShowWindow(SW_HIDE);
}


void CDlgManualThermCfg::OnCbnKillfocusComboBox()
{
    // TODO:  在此添加控件通知处理程序代码
    CString  csComboBoxStr;
    char  szListStr[128] = { 0 };
    m_listManualThermInfo.GetItemText(m_iItem, m_iSubItem, szListStr, 128);
    m_comboBox.GetWindowText(csComboBoxStr);
    if (csComboBoxStr.Compare(szListStr))
    {
        m_comboBox.SetCurSel(m_comboBox.FindString(0, szListStr));
        m_listManualThermInfo.SetItemText(m_iItem, m_iSubItem, csComboBoxStr);
        m_iLastItem = m_iItem;
        SaveParam();
    }
    m_comboBox.ShowWindow(SW_HIDE);
}


void CDlgManualThermCfg::OnBnClickedButtonAdd()
{
    // TODO:  在此添加控件通知处理程序代码
    m_iRowCount = m_listManualThermInfo.GetItemCount();
    CString strTemp = _T("");
    strTemp.Format("%d", m_iRowCount);
    m_listManualThermInfo.InsertItem(m_iRowCount, strTemp);
    m_iRowCount++;
}


void CDlgManualThermCfg::OnBnClickedButtonDelete()
{
    // TODO:  在此添加控件通知处理程序代码
    if (m_iLastItem >= 0 && m_iLastItem < m_iRowCount)
    {
        m_listManualThermInfo.DeleteItem(m_iLastItem);
    }
}



void CDlgManualThermCfg::OnBnClickedButtonGetManualthermBasic()
{
    // TODO:  在此添加控件通知处理程序代码

    UpdateData(TRUE);

    char szStatusBuf[ISAPI_STATUS_LEN] = { 0 };

    NET_SDK_MANUALTHERM_BASICPARAM struManualThermBasicParam = { 0 };
    NET_DVR_STD_CONFIG struStdConfig = { 0 };

    struManualThermBasicParam.dwSize = sizeof(struManualThermBasicParam);

    struStdConfig.lpCondBuffer = &m_lChannel;
    struStdConfig.dwCondSize = sizeof(m_lChannel);
    struStdConfig.lpInBuffer = NULL;
    struStdConfig.dwInSize = 0;
    struStdConfig.lpOutBuffer = (LPVOID)&struManualThermBasicParam;
    struStdConfig.dwOutSize = sizeof(struManualThermBasicParam);

    struStdConfig.lpStatusBuffer = szStatusBuf;
    struStdConfig.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_MANUALTHERM_BASICPARAM, &struStdConfig))
    {
        OutputDebugString(szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_MANUALTHERM_BASICPARAM");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_MANUALTHERM_BASICPARAM");
    }
    m_iDistance = struManualThermBasicParam.wDistance;
    m_fEmissivity = struManualThermBasicParam.fEmissivity;

    UpdateData(FALSE);
}


void CDlgManualThermCfg::OnBnClickedButtonSetManualthermBasic()
{
    // TODO:  在此添加控件通知处理程序代码

    UpdateData(TRUE);

    char szStatusBuf[ISAPI_STATUS_LEN] = { 0 };

    NET_SDK_MANUALTHERM_BASICPARAM struManualThermBasicParam = { 0 };
    NET_DVR_STD_CONFIG struStdConfig = { 0 };

    struManualThermBasicParam.dwSize = sizeof(struManualThermBasicParam);
    struManualThermBasicParam.wDistance = m_iDistance;
    struManualThermBasicParam.fEmissivity = m_fEmissivity;

    struStdConfig.lpCondBuffer = (LPVOID)&m_lChannel;
    struStdConfig.dwCondSize = sizeof(m_lChannel);
    struStdConfig.lpInBuffer = (LPVOID)&struManualThermBasicParam;
    struStdConfig.dwInSize = sizeof(struManualThermBasicParam);

    struStdConfig.lpStatusBuffer = szStatusBuf;
    struStdConfig.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_MANUALTHERM_BASICPARAM, &struStdConfig))
    {
        OutputDebugString(szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_MANUALTHERM_BASICPARAM");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_MANUALTHERM_BASICPARAM");
    }

    UpdateData(FALSE);
}


void CDlgManualThermCfg::OnBnClickedButtonDeleteRule()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    char szStatusBuf[ISAPI_STATUS_LEN] = { 0 };

    NET_DVR_REALTIME_THERMOMETRY_COND struCond = { 0 };
    struCond.dwSize = sizeof(NET_DVR_REALTIME_THERMOMETRY_COND);
    struCond.dwChan = m_lChannel;
    struCond.byRuleID = m_iRuleID;

    NET_DVR_STD_CONFIG struStdConfig = { 0 };


    NET_DVR_STD_CONTROL struStdControl = { 0 };
    struStdControl.lpCondBuffer = &struCond;
    struStdControl.dwCondSize = sizeof(struCond);

    struStdControl.lpStatusBuffer = szStatusBuf;
    struStdControl.dwStatusSize = ISAPI_STATUS_LEN;


    if (!NET_DVR_STDControl(m_lServerID, NET_DVR_DEL_MANUALTHERM_RULE, &struStdControl))
    {
        OutputDebugString(szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_DEL_MANUALTHERM_RULE");
    }
    else
    {
        OutputDebugString(szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DEL_MANUALTHERM_RULE");
    }

    UpdateData(FALSE);
}
