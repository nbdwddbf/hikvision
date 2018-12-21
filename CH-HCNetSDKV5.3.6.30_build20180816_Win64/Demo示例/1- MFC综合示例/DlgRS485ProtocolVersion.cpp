// DlgRS485ProtocolVersion.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgRS485ProtocolVersion.h"
#include "afxdialogex.h"


// CDlgRS485ProtocolVersion 对话框

IMPLEMENT_DYNAMIC(CDlgRS485ProtocolVersion, CDialog)

CDlgRS485ProtocolVersion::CDlgRS485ProtocolVersion(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRS485ProtocolVersion::IDD, pParent)
    , m_lUserID(-1)
{
    m_csVersion = _T("");
}

CDlgRS485ProtocolVersion::~CDlgRS485ProtocolVersion()
{
}

void CDlgRS485ProtocolVersion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_VERSION_485, m_csVersion);
}


BEGIN_MESSAGE_MAP(CDlgRS485ProtocolVersion, CDialog)
    ON_BN_CLICKED(IDC_BTN_GET, &CDlgRS485ProtocolVersion::OnBnClickedBtnGet)
END_MESSAGE_MAP()


// CDlgRS485ProtocolVersion 消息处理程序
void CDlgRS485ProtocolVersion::OnBnClickedBtnGet()
{
    // TODO:  在此添加控件通知处理程序代码
    NET_DVR_RS485_PROTOCOL_VERSION struVersion = { 0 };
    struVersion.dwSize = sizeof(NET_DVR_RS485_PROTOCOL_VERSION);
    DWORD dwRet = 0;
    if (NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_RS485_PROTOCOL_VERSION, 0, &struVersion, sizeof(struVersion), &dwRet))
    {
        g_pMainDlg->AddLog(m_lUserID, OPERATION_SUCC_T, "NET_DVR_RS485_PROTOCOL_VERSION");
    }
    else
    {
        g_pMainDlg->AddLog(m_lUserID, OPERATION_FAIL_T, "NET_DVR_RS485_PROTOCOL_VERSION");
        return;
    }
    char szLan[40] = { 0 };
    strncpy(szLan, (char*)struVersion.byProtocleVersion, sizeof(struVersion.byProtocleVersion));
    m_csVersion.Format("%s", szLan);
    UpdateData(FALSE);
}