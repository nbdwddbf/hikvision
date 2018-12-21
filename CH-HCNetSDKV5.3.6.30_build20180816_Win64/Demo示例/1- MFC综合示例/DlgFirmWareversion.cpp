// DlgFirmWareversion.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgFirmWareversion.h"
#include "afxdialogex.h"


// CDlgFirmWareversion 对话框

IMPLEMENT_DYNAMIC(CDlgFirmWareversion, CDialogEx)

CDlgFirmWareversion::CDlgFirmWareversion(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgFirmWareversion::IDD, pParent)
    , m_FirmwareVersion(_T(""))
{

}

CDlgFirmWareversion::~CDlgFirmWareversion()
{
}

void CDlgFirmWareversion::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_FIRMWARE_VERSION, m_FirmwareVersion);
}


BEGIN_MESSAGE_MAP(CDlgFirmWareversion, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_GET, &CDlgFirmWareversion::OnBnClickedBtnGet)
END_MESSAGE_MAP()


// CDlgFirmWareversion 消息处理程序





void CDlgFirmWareversion::OnBnClickedBtnGet()
{
    NET_DVR_FIRMWARE_VERSION_IFNO struFirmwareVersion = { 0 };
    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &struFirmwareVersion;
    struCfg.dwOutSize = sizeof(struFirmwareVersion);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_FIRMWARE_VERSION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_FIRMWARE_VERSION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_FIRMWARE_VERSION");
    }

    m_FirmwareVersion.Format(_T("%s"), struFirmwareVersion.szFirmwareVersion);
    UpdateData(FALSE);
}
