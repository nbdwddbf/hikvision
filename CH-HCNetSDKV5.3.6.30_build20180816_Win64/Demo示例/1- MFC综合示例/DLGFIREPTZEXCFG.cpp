// DLGFIREPTZEXCFG.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DLGFIREPTZEXCFG.h"
#include "afxdialogex.h"


// CDLGFIREPTZEXCFG 对话框

IMPLEMENT_DYNAMIC(CDLGFIREPTZEXCFG, CDialogEx)

CDLGFIREPTZEXCFG::CDLGFIREPTZEXCFG(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDLGFIREPTZEXCFG::IDD, pParent)
    , m_PTZEXPan(0)
    , m_PTZEXTilt(0)
    , m_PTZEXZoom(0)
    , m_PTZEXdwFocus(0)
    , m_PTZEXdwFocalLen(0)
    , m_SpeedEX_HorizontalSpeed(0)
    , m_SpeedEX_VerticalSpeed(0)
{

}

CDLGFIREPTZEXCFG::~CDLGFIREPTZEXCFG()
{
}

void CDLGFIREPTZEXCFG::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_Pan, m_PTZEXPan);
    DDX_Text(pDX, IDC_EDIT_Tilt, m_PTZEXTilt);
    DDX_Text(pDX, IDC_EDIT_Zoom, m_PTZEXZoom);
    DDX_Text(pDX, IDC_EDIT_ptzdwFocus, m_PTZEXdwFocus);
    DDX_Text(pDX, IDC_EDIT_dwFocalLen, m_PTZEXdwFocalLen);
    DDX_Text(pDX, IDC_EDIT_SPEEDEX_HorizontalSpeed, m_SpeedEX_HorizontalSpeed);
    DDX_Control(pDX, IDC_COMBO_ZOOMTYPE, m_comZoomType);
    DDX_Text(pDX, IDC_EDIT_SPEEDEX_VerticalSpeed, m_SpeedEX_VerticalSpeed);
}


BEGIN_MESSAGE_MAP(CDLGFIREPTZEXCFG, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_PTZEX_GTE, &CDLGFIREPTZEXCFG::OnBnClickedButtonPtzexGte)
    ON_BN_CLICKED(IDC_BUTTON_PTZEX_SET, &CDLGFIREPTZEXCFG::OnBnClickedButtonPtzexSet)
END_MESSAGE_MAP()


// CDLGFIREPTZEXCFG 消息处理程序


void CDLGFIREPTZEXCFG::OnBnClickedButtonPtzexGte()
{
    NET_DVR_STD_CONFIG struCfg = { 0 };
    memset(&m_struBuiltinPTZABSOLUTEEX, 0, sizeof(m_struBuiltinPTZABSOLUTEEX));
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &m_struBuiltinPTZABSOLUTEEX;
    struCfg.dwOutSize = sizeof(m_struBuiltinPTZABSOLUTEEX);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_PTZABSOLUTEEX, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PTZABSOLUTEEX");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PTZABSOLUTEEX");

    }

    m_PTZEXPan = m_struBuiltinPTZABSOLUTEEX.struPTZCtrl.fPan;
    m_PTZEXTilt = m_struBuiltinPTZABSOLUTEEX.struPTZCtrl.fTilt;
    m_PTZEXZoom = m_struBuiltinPTZABSOLUTEEX.struPTZCtrl.fZoom;
    m_PTZEXdwFocus = m_struBuiltinPTZABSOLUTEEX.struPTZCtrl.dwFocus;
    m_PTZEXdwFocalLen = m_struBuiltinPTZABSOLUTEEX.dwFocalLen;

    m_SpeedEX_HorizontalSpeed = m_struBuiltinPTZABSOLUTEEX.fHorizontalSpeed;
    m_SpeedEX_VerticalSpeed = m_struBuiltinPTZABSOLUTEEX.fVerticalSpeed;
    m_comZoomType.SetCurSel(m_struBuiltinPTZABSOLUTEEX.byZoomType);

    UpdateData(FALSE);
}


void CDLGFIREPTZEXCFG::OnBnClickedButtonPtzexSet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    memset(&m_struBuiltinPTZABSOLUTEEX, 0, sizeof(m_struBuiltinPTZABSOLUTEEX));
    m_struBuiltinPTZABSOLUTEEX.dwSize = sizeof(m_struBuiltinPTZABSOLUTEEX);
    m_struBuiltinPTZABSOLUTEEX.struPTZCtrl.fPan = m_PTZEXPan;
    m_struBuiltinPTZABSOLUTEEX.struPTZCtrl.fTilt = m_PTZEXTilt;
    m_struBuiltinPTZABSOLUTEEX.struPTZCtrl.fZoom = m_PTZEXZoom;
    m_struBuiltinPTZABSOLUTEEX.struPTZCtrl.dwFocus = m_PTZEXdwFocus;
    m_struBuiltinPTZABSOLUTEEX.dwFocalLen = m_PTZEXdwFocalLen;
    m_struBuiltinPTZABSOLUTEEX.fHorizontalSpeed = m_SpeedEX_HorizontalSpeed;
    m_struBuiltinPTZABSOLUTEEX.fVerticalSpeed = m_SpeedEX_VerticalSpeed;
    m_struBuiltinPTZABSOLUTEEX.byZoomType = m_comZoomType.GetCurSel();
    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &m_struBuiltinPTZABSOLUTEEX;
    struCfg.dwInSize = sizeof(m_struBuiltinPTZABSOLUTEEX);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_PTZABSOLUTEEX, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_PTZABSOLUTEEX");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_PTZABSOLUTEEX");
        OutputDebugString(m_szStatusBuf);
    }
}
