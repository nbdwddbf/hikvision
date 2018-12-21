// DlgSoftwareService.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgSoftwareService.h"
#include "afxdialogex.h"


// CDlgSoftwareService 对话框

IMPLEMENT_DYNAMIC(CDlgSoftwareService, CDialog)

CDlgSoftwareService::CDlgSoftwareService(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSoftwareService::IDD, pParent)
{
    memset(&m_strSoftwareService, 0, sizeof(m_strSoftwareService));
}

CDlgSoftwareService::~CDlgSoftwareService()
{
}

void CDlgSoftwareService::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CMB_ENABLED, m_cmbThirdStreamEnabled);
    DDX_Control(pDX, IDC_CMB_SUBSTREAM_ENABLED, m_cmbSubStream);
}


BEGIN_MESSAGE_MAP(CDlgSoftwareService, CDialog)
    ON_BN_CLICKED(IDC_BTN_GET, &CDlgSoftwareService::OnBnClickedBtnGet)
    ON_BN_CLICKED(IDC_BTN_SET, &CDlgSoftwareService::OnBnClickedBtnSet)
END_MESSAGE_MAP()


// CDlgSoftwareService 消息处理程序


void CDlgSoftwareService::OnBnClickedBtnGet()
{
    UpdateData(TRUE);
    NET_DVR_STD_CONFIG struCfg = { 0 };

    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &m_strSoftwareService;
    struCfg.dwOutSize = sizeof(m_strSoftwareService);

    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_SOFTWARE_SERVICE, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SOFTWARE_SERVICE");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SOFTWARE_SERVICE");
        m_cmbThirdStreamEnabled.SetCurSel(m_strSoftwareService.byThirdStreamEnabled);
        m_cmbSubStream.SetCurSel(m_strSoftwareService.bySubStreamEnabled);
    }
    UpdateData(FALSE);
}


void CDlgSoftwareService::OnBnClickedBtnSet()
{
    UpdateData(TRUE);
    m_strSoftwareService.dwSize = sizeof(m_strSoftwareService);
    m_strSoftwareService.byThirdStreamEnabled = m_cmbThirdStreamEnabled.GetCurSel();
    m_strSoftwareService.bySubStreamEnabled = m_cmbSubStream.GetCurSel();
    NET_DVR_STD_CONFIG struStdConfig = { 0 };
    struStdConfig.lpCondBuffer = &m_lChannel;
    struStdConfig.dwCondSize = sizeof(m_lChannel);

    struStdConfig.lpInBuffer = (LPVOID)&m_strSoftwareService;
    struStdConfig.dwInSize = sizeof(m_strSoftwareService);

    if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_SOFTWARE_SERVICE, &struStdConfig))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SOFTWARE_SERVICE");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SOFTWARE_SERVICE");
    }
    UpdateData(FALSE);
}
