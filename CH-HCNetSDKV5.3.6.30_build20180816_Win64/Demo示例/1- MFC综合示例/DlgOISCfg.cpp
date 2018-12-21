// DlgOISCfg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgOISCfg.h"
#include "afxdialogex.h"


// CDlgOISCfg 对话框

IMPLEMENT_DYNAMIC(CDlgOISCfg, CDialogEx)

CDlgOISCfg::CDlgOISCfg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgOISCfg::IDD, pParent)
{

}

CDlgOISCfg::~CDlgOISCfg()
{
}

void CDlgOISCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_ENABLE, m_enable);
    DDX_Control(pDX, IDC_COMBO_LEVEL, m_level);
    DDX_Control(pDX, IDC_CMB_OIS_SENSITIVITY, m_OISSensitivity);
}


BEGIN_MESSAGE_MAP(CDlgOISCfg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_GET, &CDlgOISCfg::OnBnClickedButtonGet)
    ON_BN_CLICKED(IDC_BUTTON_SET, &CDlgOISCfg::OnBnClickedButtonSet)
END_MESSAGE_MAP()


// CDlgOISCfg 消息处理程序


void CDlgOISCfg::OnBnClickedButtonGet()
{
    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &m_struBuiltinOIS;
    struCfg.dwOutSize = sizeof(m_struBuiltinOIS);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_OIS_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_OIS_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_OIS_CFG");

    }

    m_enable.SetCurSel(m_struBuiltinOIS.byMode);
    m_level.SetCurSel(m_struBuiltinOIS.byOISLevel);
    m_OISSensitivity.SetCurSel(m_struBuiltinOIS.byOISSensitivity);
    UpdateData(FALSE);
}


void CDlgOISCfg::OnBnClickedButtonSet()
{
    m_struBuiltinOIS.dwSize = sizeof(m_struBuiltinOIS);
    m_struBuiltinOIS.byMode = m_enable.GetCurSel();
    m_struBuiltinOIS.byOISLevel = m_level.GetCurSel();
    m_struBuiltinOIS.byOISSensitivity = m_OISSensitivity.GetCurSel();

    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &m_struBuiltinOIS;
    struCfg.dwInSize = sizeof(m_struBuiltinOIS);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_OIS_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_OIS_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_OIS_CFG");
        OutputDebugString(m_szStatusBuf);
    }
}
