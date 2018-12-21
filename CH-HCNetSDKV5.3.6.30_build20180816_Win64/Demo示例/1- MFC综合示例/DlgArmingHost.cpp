// DlgArmingHost.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgArmingHost.h"
#include "afxdialogex.h"


// CDlgArmingHost 对话框

IMPLEMENT_DYNAMIC(CDlgArmingHost, CDialog)

CDlgArmingHost::CDlgArmingHost(CWnd* pParent /*=NULL*/)
: CDialog(CDlgArmingHost::IDD, pParent)
, m_dwPort(0)
, m_strIpv4(_T(""))
, m_strIpv6(_T(""))
{

}

CDlgArmingHost::~CDlgArmingHost()
{
}

void CDlgArmingHost::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_ARING_HOST_PORT, m_dwPort);
    DDX_Text(pDX, IDC_EDIT_ARING_HOST_IPV4, m_strIpv4);
    DDX_Text(pDX, IDC_EDIT_ARING_HOST_IPV6, m_strIpv6);
    DDX_Control(pDX, IDC_CMB_ANR_TYPE, m_cmbANRType);
    DDX_Control(pDX, IDC_CMB_CONFIRM_MECHANISM, m_cmbConfirmMechanismEnabled);
}


BEGIN_MESSAGE_MAP(CDlgArmingHost, CDialog)
    ON_BN_CLICKED(IDC_BTN_GET, &CDlgArmingHost::OnClickedBtnGet)
    ON_BN_CLICKED(IDCANCEL, &CDlgArmingHost::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgArmingHost 消息处理程序



BOOL CDlgArmingHost::OnInitDialog()
{
    CDialog::OnInitDialog();

    UpdateData(TRUE);
    // TODO: Add extra initialization here
    char szLan[128] = { 0 };
    
    m_cmbANRType.ResetContent();
    g_StringLanType(szLan, "SDK", "SDK");
    m_cmbANRType.InsertString(0, szLan);
    g_StringLanType(szLan, "Ehome", "Ehome");
    m_cmbANRType.InsertString(1, szLan);
    m_cmbANRType.SetCurSel(0);
    m_cmbConfirmMechanismEnabled.SetCurSel(0);
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgArmingHost::OnClickedBtnGet()
{
    // TODO:  在此添加控件通知处理程序代码
    NET_DVR_STD_CONFIG  struConfig = { 0 };
    NET_DVR_ANR_ARMING_HOST struAringHost = { 0 };
    struConfig.lpOutBuffer = &struAringHost;
    struConfig.dwOutSize = sizeof(struAringHost);
    
    struAringHost.dwSize = sizeof(struAringHost);
    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_ANR_ARMING_HOST, &struConfig))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ANR_ARMING_HOST Failed");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ANR_ARMING_HOST SUCC");
        m_dwPort = struAringHost.wANRAlarmHostPort;
        m_strIpv4 = struAringHost.struANRArmingHostIpAddr.sIpV4;
        m_strIpv6.Format("%s", struAringHost.struANRArmingHostIpAddr.byIPv6);
        m_cmbANRType.SetCurSel(struAringHost.byANRAlarmType);
        m_cmbConfirmMechanismEnabled.SetCurSel(struAringHost.byConfirmMechanismEnabled);
        UpdateData(FALSE);
    }
}


void CDlgArmingHost::OnBnClickedCancel()
{
    // TODO:  在此添加控件通知处理程序代码
    CDialog::OnCancel();
}
