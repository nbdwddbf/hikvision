#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgSmartCalib.h"
#include "afxdialogex.h"
#include "DrawFun.h"

// CDlgSmartCalib 


void CALLBACK g_DrawSmartCalibRgn(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
    CDlgSmartCalib* pDlg = (CDlgSmartCalib*)dwUser;

    if (pDlg != NULL)
    {
        pDlg->DrawSmartRgn(hDc);
    }
}
void CDlgSmartCalib::DrawSmartRgn(HDC hDc)
{
    DRAW_POLYGON_PARAM_EX struMaxPolygonParam;
    DRAW_POLYGON_PARAM_EX struMinPolygonParam;
    if (m_bMaxTarget)
    {
        memset(&struMaxPolygonParam, 0, sizeof(struMaxPolygonParam));
        struMaxPolygonParam.color = RGB(255, 0, 0);
        memcpy(&struMaxPolygonParam.rcWnd, &m_rcPlayWnd, sizeof(m_rcPlayWnd));
        struMaxPolygonParam.pArryPt = m_strMaxVacRegion.struPos;
        struMaxPolygonParam.dwPtNum = m_strMaxVacRegion.dwPointNum;
        CDrawFun::DrawPolygonEx(hDc, &struMaxPolygonParam);
    }
    
    if (m_bMinTarget)
    {
        memset(&struMinPolygonParam, 0, sizeof(struMinPolygonParam));
        struMinPolygonParam.color = RGB(200, 0, 0);
        memcpy(&struMinPolygonParam.rcWnd, &m_rcPlayWnd, sizeof(m_rcPlayWnd));
        struMinPolygonParam.pArryPt = m_strMinVacRegion.struPos;
        struMinPolygonParam.dwPtNum = m_strMinVacRegion.dwPointNum;
        CDrawFun::DrawPolygonEx(hDc, &struMinPolygonParam);
    }

}
IMPLEMENT_DYNAMIC(CDlgSmartCalib, CDialogEx)

CDlgSmartCalib::CDlgSmartCalib(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSmartCalib::IDD, pParent)
    , m_bMinTarget(FALSE)
    , m_bMaxTarget(FALSE)
{
    memset(&m_strMinVacRegion, 0, sizeof(m_strMinVacRegion));
    memset(&m_strMaxVacRegion, 0, sizeof(m_strMaxVacRegion));
    memset(&m_struSmartCalibCond, 0, sizeof(m_struSmartCalibCond));
    memset(&m_struSmartCalib, 0, sizeof(m_struSmartCalib));
}

CDlgSmartCalib::~CDlgSmartCalib()
{
}

void CDlgSmartCalib::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHK_MIN_TARGET, m_bMinTarget);
    DDX_Check(pDX, IDC_CHK_MAX_TARGET, m_bMaxTarget);
    DDX_Control(pDX, IDC_CMB_RULE_ID, m_cmbRuleID);
    DDX_Control(pDX, IDC_CMB_SMART_TYPE, m_bSmartType);
    DDX_Control(pDX, IDC_CMB_SMART_MODE, m_cmbMode);
    DDX_Control(pDX, IDC_CMB_SMART_STRATEGY, m_cmbStrategy);
    DDX_Control(pDX, IDC_CMB_SMART_PRIORITY, m_cmbPriority);
}


BEGIN_MESSAGE_MAP(CDlgSmartCalib, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_SET, &CDlgSmartCalib::OnBnClickedBtnSet)
    ON_BN_CLICKED(IDC_BTN_GET, &CDlgSmartCalib::OnBnClickedBtnGet)
    ON_CBN_SELCHANGE(IDC_CMB_RULE_ID, &CDlgSmartCalib::OnCbnSelchangeCmbRuleId)
    ON_BN_CLICKED(IDC_BTN_SAVE, &CDlgSmartCalib::OnBnClickedBtnSave)
    ON_BN_CLICKED(IDC_CHK_MAX_TARGET, &CDlgSmartCalib::OnBnClickedChkMaxTarget)
    ON_BN_CLICKED(IDC_CHK_MIN_TARGET, &CDlgSmartCalib::OnBnClickedChkMinTarget)
    ON_BN_CLICKED(IDCANCEL, &CDlgSmartCalib::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgSmartCalib 

BOOL CDlgSmartCalib::PreTranslateMessage(MSG* pMsg)
{
    UpdateData(TRUE);
    CPoint pt(0, 0);
    GetDlgItem(IDC_PLAY)->GetWindowRect(&m_rcPlayWnd);
    GetCursorPos(&pt);
    ScreenToClient(&m_rcPlayWnd);
    ScreenToClient(&pt);
    CString strTemp = _T("");
    DWORD i = 0;
    BOOL bOneLine = TRUE, bXOneLine = TRUE, bYOneLine = TRUE;

    switch (pMsg->message)  // Message of Draw
    {
    case WM_LBUTTONDOWN:
        if ((GetAsyncKeyState(VK_LCONTROL) < 0 || GetAsyncKeyState(VK_RCONTROL) < 0))//Press CTRL to draw
        {
            if (PtInRect(&m_rcPlayWnd, pt))
            {
//                m_struMAxPoint.fX = (float)(pt.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
 //               m_struMAxPoint.fY = (float)(pt.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();
                memset(&m_strMaxVacRegion, 0, sizeof(m_strMaxVacRegion));
                if (!m_bMouseMove)
                {
                    if (m_bMaxTarget)
                    {
                        m_strMaxVacRegion.struPos[0].fX = (float)(pt.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
                        m_strMaxVacRegion.struPos[0].fY = (float)(pt.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();
                        m_strMaxVacRegion.dwPointNum = 1;
                    }
                    if (m_bMinTarget)
                    {
                        m_strMinVacRegion.struPos[0].fX = (float)(pt.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
                        m_strMinVacRegion.struPos[0].fY = (float)(pt.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();
                        m_strMinVacRegion.dwPointNum = 1;
                    }
                    m_bMouseMove = TRUE;
                }

            }
        }
        break;
    case WM_MOUSEMOVE:
        if ((GetAsyncKeyState(VK_LCONTROL) < 0 || GetAsyncKeyState(VK_RCONTROL) < 0) /*&& m_comboTrackMode.GetCurSel() == 1*/)
        {
            if (PtInRect(&m_rcPlayWnd, pt) && m_bMouseMove)
            {
                if (m_bMaxTarget)
                {
                    m_strMaxVacRegion.struPos[1].fX = m_strMaxVacRegion.struPos[0].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
                    m_strMaxVacRegion.struPos[1].fY = m_strMaxVacRegion.struPos[2].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;
                    m_strMaxVacRegion.struPos[3].fX = m_strMaxVacRegion.struPos[2].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
                    m_strMaxVacRegion.struPos[3].fY = m_strMaxVacRegion.struPos[0].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;
                    m_strMaxVacRegion.struPos[2].fX = (float)(pt.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
                    m_strMaxVacRegion.struPos[2].fY = (float)(pt.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();
                    m_strMaxVacRegion.dwPointNum = 4;
                }
                if (m_bMinTarget)
                {
                    m_strMinVacRegion.struPos[1].fX = m_strMinVacRegion.struPos[0].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
                    m_strMinVacRegion.struPos[1].fY = m_strMinVacRegion.struPos[2].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;
                    m_strMinVacRegion.struPos[3].fX = m_strMinVacRegion.struPos[2].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
                    m_strMinVacRegion.struPos[3].fY = m_strMinVacRegion.struPos[0].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;
                    m_strMinVacRegion.struPos[2].fX = (float)(pt.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
                    m_strMinVacRegion.struPos[2].fY = (float)(pt.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();
                    m_strMinVacRegion.dwPointNum = 4;
                }

            }
        }

        break;

    case WM_LBUTTONUP:
        if ((GetAsyncKeyState(VK_LCONTROL) < 0 || GetAsyncKeyState(VK_RCONTROL) < 0) /*&& m_comboTrackMode.GetCurSel() == 1*/)//Press CTRL to draw
        {
            if (m_bMaxTarget)
            {
                m_strMaxVacRegion.struPos[1].fX = m_strMaxVacRegion.struPos[0].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
                m_strMaxVacRegion.struPos[1].fY = m_strMaxVacRegion.struPos[2].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;
                m_strMaxVacRegion.struPos[3].fX = m_strMaxVacRegion.struPos[2].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
                m_strMaxVacRegion.struPos[3].fY = m_strMaxVacRegion.struPos[0].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;
                m_strMaxVacRegion.struPos[2].fX = (float)(pt.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
                m_strMaxVacRegion.struPos[2].fY = (float)(pt.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();

            }
            if (m_bMinTarget)
            {
                m_strMinVacRegion.struPos[1].fX = m_strMinVacRegion.struPos[0].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
                m_strMinVacRegion.struPos[1].fY = m_strMinVacRegion.struPos[2].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;
                m_strMinVacRegion.struPos[3].fX = m_strMinVacRegion.struPos[2].fX /*(float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width()*/;
                m_strMinVacRegion.struPos[3].fY = m_strMinVacRegion.struPos[0].fY /*(float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height()*/;
                m_strMinVacRegion.struPos[2].fX = (float)(pt.x - m_rcPlayWnd.left) / (float)m_rcPlayWnd.Width();
                m_strMinVacRegion.struPos[2].fY = (float)(pt.y - m_rcPlayWnd.top) / (float)m_rcPlayWnd.Height();
            }
           // memcpy(&m_struRegionTemp, &m_struTracking.struRegion, sizeof(NET_VCA_POLYGON));
        }
        m_bMouseMove = FALSE;
        break;
    default:
        break;
    }
    return CDialog::PreTranslateMessage(pMsg);
}

BOOL CDlgSmartCalib::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    m_cmbRuleID.SetCurSel(0);
    m_bSmartType.SetCurSel(0);
    GetDlgItem(IDC_PLAY)->GetWindowRect(&m_rcPlayWnd);
    ScreenToClient(&m_rcPlayWnd);
    StartRealPlay(GetDlgItem(IDC_PLAY)->GetSafeHwnd(), g_DrawSmartCalibRgn, this);
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control

}


void CDlgSmartCalib::OnBnClickedBtnSet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    NET_DVR_STD_CONFIG struCfg = { 0 };
    //struCfg.lpCondBuffer = &m_lChannel;
    //struCfg.dwCondSize = sizeof(m_lChannel);

    struCfg.lpCondBuffer = &m_struSmartCalibCond;
    struCfg.dwCondSize = sizeof(m_struSmartCalibCond);

    struCfg.lpInBuffer = &m_struSmartCalib;
    struCfg.dwInSize = sizeof(m_struSmartCalib);
    m_struSmartCalib.dwSize = sizeof(m_struSmartCalib);
    //m_struSmartCalib.bySmartType = m_bSmartType.GetCurSel();

    m_struSmartCalibCond.dwSize = sizeof(m_struSmartCalibCond);
    m_struSmartCalibCond.bySmartType = m_bSmartType.GetCurSel();
    m_struSmartCalibCond.dwChannel = m_lChannel;

    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_SMARTCALIBRATION_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SMARTCALIBRATION_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SMARTCALIBRATION_CFG");

    }
    UpdateData(FALSE);
}


void CDlgSmartCalib::OnBnClickedBtnGet()
{
    UpdateData(TRUE);
    memset(&m_struSmartCalib, 0, sizeof(m_struSmartCalib));
    //m_struSmartCalib.bySmartType = m_bSmartType.GetCurSel();
    m_struSmartCalib.dwSize = sizeof(m_struSmartCalib);

    NET_DVR_STD_CONFIG struCfg = { 0 };
    //struCfg.lpCondBuffer = &m_lChannel;
    //struCfg.dwCondSize = sizeof(m_lChannel);

    struCfg.lpCondBuffer = &m_struSmartCalibCond;
    struCfg.dwCondSize = sizeof(m_struSmartCalibCond);

    struCfg.lpOutBuffer = &m_struSmartCalib;
    struCfg.dwOutSize = sizeof(m_struSmartCalib);

    m_struSmartCalibCond.dwSize = sizeof(m_struSmartCalibCond);
    m_struSmartCalibCond.bySmartType = m_bSmartType.GetCurSel();
    m_struSmartCalibCond.dwChannel = m_lChannel;

    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;



    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_SMARTCALIBRATION_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SMARTCALIBRATION_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SMARTCALIBRATION_CFG");

    }

    memcpy(&m_strMaxVacRegion, &m_struSmartCalib.strRegion[0].struMaxTargetSize, sizeof(NET_VCA_POLYGON));
    memcpy(&m_strMinVacRegion, &m_struSmartCalib.strRegion[0].struMinTargetSize, sizeof(NET_VCA_POLYGON));
    UpdateData(FALSE);
}


void CDlgSmartCalib::OnCbnSelchangeCmbRuleId()
{
    UpdateData(TRUE);
    int i = m_cmbRuleID.GetCurSel();
    m_struSmartCalib.strRegion[i].byRuleID = i + 1;

    //m_struSmartCalib.strRegion[i].byMode = m_cmbMode.GetCurSel() + 1;
    //m_struSmartCalib.strRegion[i].byStrategy = m_cmbStrategy.GetCurSel();
    //m_struSmartCalib.strRegion[i].byPriority = m_cmbPriority.GetCurSel() + 1;

    if (m_bMinTarget)
    {
        memcpy(&m_strMinVacRegion, &m_struSmartCalib.strRegion[i].struMinTargetSize, sizeof(NET_VCA_POLYGON));
    }
   
    if (m_bMaxTarget)
    {
        memcpy(&m_strMaxVacRegion, &m_struSmartCalib.strRegion[i].struMaxTargetSize, sizeof(NET_VCA_POLYGON));
    }

    m_cmbMode.SetCurSel(m_struSmartCalib.strRegion[i].byMode - 1);
    m_cmbStrategy.SetCurSel(m_struSmartCalib.strRegion[i].byStrategy);
    m_cmbPriority.SetCurSel(m_struSmartCalib.strRegion[i].byPriority - 1);

    UpdateData(FALSE);
}


void CDlgSmartCalib::OnBnClickedBtnSave()
{
    UpdateData(TRUE);
    int i = m_cmbRuleID.GetCurSel();
    m_struSmartCalib.strRegion[i].byRuleID = m_cmbRuleID.GetCurSel() + 1;

    m_struSmartCalib.strRegion[i].byMode = m_cmbMode.GetCurSel() + 1;
    m_struSmartCalib.strRegion[i].byStrategy = m_cmbStrategy.GetCurSel();
    m_struSmartCalib.strRegion[i].byPriority = m_cmbPriority.GetCurSel() + 1;

    if (m_bMinTarget)
    {
        memcpy(&m_struSmartCalib.strRegion[i].struMinTargetSize, &m_strMinVacRegion, sizeof(NET_VCA_POLYGON));
    }

    if (m_bMaxTarget)
    {
        memcpy(&m_struSmartCalib.strRegion[i].struMaxTargetSize, &m_strMaxVacRegion, sizeof(NET_VCA_POLYGON));
    }
    UpdateData(FALSE);
}


void CDlgSmartCalib::OnBnClickedChkMaxTarget()
{
    UpdateData(TRUE);
    if (m_bMaxTarget)
    {
        m_bMinTarget = FALSE;
    }
    else
    {
        m_bMinTarget = TRUE;
    }
    UpdateData(FALSE);
}
void CDlgSmartCalib::OnBnClickedChkMinTarget()
{
    UpdateData(TRUE);
    if (m_bMinTarget)
    {
        m_bMaxTarget = FALSE;
    }
    else
    {
        m_bMaxTarget = TRUE;
    }
    UpdateData(FALSE);
}


void CDlgSmartCalib::OnBnClickedCancel()
{
    OnCancel();
}

