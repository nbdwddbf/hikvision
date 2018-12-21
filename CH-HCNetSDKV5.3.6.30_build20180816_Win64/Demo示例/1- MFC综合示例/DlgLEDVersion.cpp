// DlgLEDVersion.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgLEDVersion.h"
#include "afxdialogex.h"
#include "ParseXMLHelper.h"

using namespace InformationReleaseSystem;


// CDlgLEDVersion 对话框

IMPLEMENT_DYNAMIC(CDlgLEDVersion, CDialogEx)

CDlgLEDVersion::CDlgLEDVersion(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgLEDVersion::IDD, pParent)
    , m_dwNo(0)
    , m_dwStartLine(0)
    , m_dwStartColumn(0)
    , m_dwEndLine(0)
    , m_dwEndColumn(0)
    , m_szBordType(_T(""))
    , m_szSoftType(_T(""))
    , m_szSoftVersion(_T(""))
{

}

CDlgLEDVersion::~CDlgLEDVersion()
{
}

void CDlgLEDVersion::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_NO, m_dwNo);
    DDX_Text(pDX, IDC_EDIT_SLINE, m_dwStartLine);
    DDX_Text(pDX, IDC_EDIT_SCOLUMN, m_dwStartColumn);
    DDX_Text(pDX, IDC_EDIT_ELINE, m_dwEndLine);
    DDX_Text(pDX, IDC_EDIT_ECOLUMN, m_dwEndColumn);
    DDX_Text(pDX, IDC_EDIT_BORT_TYPE, m_szBordType);
    DDX_Text(pDX, IDC_EDIT_SOFT_TYPE, m_szSoftType);
    DDX_Text(pDX, IDC_EDIT_SOFT_VERSION, m_szSoftVersion);
}


BEGIN_MESSAGE_MAP(CDlgLEDVersion, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_GET, &CDlgLEDVersion::OnBnClickedBtnGet)
    ON_BN_CLICKED(IDC_BTN_RESTORE, &CDlgLEDVersion::OnBnClickedBtnRestore)
END_MESSAGE_MAP()


// CDlgLEDVersion 消息处理程序



void CDlgLEDVersion::OnBnClickedBtnGet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    m_struArea.iOutputNo = m_dwNo;
    m_struArea.struArea.iStartLine = m_dwStartLine;
    m_struArea.struArea.iStartColumn = m_dwStartColumn;
    m_struArea.struArea.iEndLine = m_dwEndLine;
    m_struArea.struArea.iEndColumn = m_dwEndColumn;
    string stringArea;
    stringArea = TGenXmlDoc<RecvCardArea>(m_struArea, "V2.0");

    NET_DVR_XML_CONFIG_INPUT struInputParam = { 0 };
    struInputParam.dwSize = sizeof(struInputParam);
    struInputParam.lpRequestUrl = "GET /ISAPI/LED/RecvCard/System/version\r\n";
    struInputParam.dwRequestUrlLen = strlen("GET /ISAPI/LED/RecvCard/System/version\r\n");
    struInputParam.lpInBuffer = (void*)stringArea.c_str();
    struInputParam.dwInBufferSize = stringArea.length();
    char szOutBuffer[1024] = { 0 };
    char szStatusBuffer[1024] = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT struOutpurParam = { 0 };
    struOutpurParam.dwSize = sizeof(struOutpurParam);
    struOutpurParam.lpOutBuffer = szOutBuffer;
    struOutpurParam.dwOutBufferSize = sizeof(szOutBuffer);
    struOutpurParam.lpStatusBuffer = szStatusBuffer;
    struOutpurParam.dwStatusSize = sizeof(szStatusBuffer);

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutpurParam))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");

    string stringVersion = (char*)struOutpurParam.lpOutBuffer;
    TParseXmlDoc<RecvCardVersion>(m_struVersion, stringVersion.c_str(), "RecvCardVersion");

    m_szBordType = m_struVersion.strBoardType.c_str();
    m_szSoftType = m_struVersion.strSoftwareType.c_str();
    m_szSoftVersion = m_struVersion.strSoftwareVersion.c_str();
    UpdateData(FALSE);   
}


void CDlgLEDVersion::OnBnClickedBtnRestore()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    m_struArea.iOutputNo = m_dwNo;
    m_struArea.struArea.iStartLine = m_dwStartLine;
    m_struArea.struArea.iStartColumn = m_dwStartColumn;
    m_struArea.struArea.iEndLine = m_dwEndLine;
    m_struArea.struArea.iEndColumn = m_dwEndColumn;

    string stringArea;
    stringArea = TGenXmlDoc<RecvCardArea>(m_struArea, "V2.0");

    NET_DVR_XML_CONFIG_INPUT struInputParam = { 0 };
    struInputParam.dwSize = sizeof(struInputParam);
    struInputParam.lpRequestUrl = "PUT /ISAPI/LED/RecvCard/System/restore\r\n";
    struInputParam.dwRequestUrlLen = strlen("PUT /ISAPI/LED/RecvCard/System/restore\r\n");
    struInputParam.lpInBuffer = (void*)stringArea.c_str();
    struInputParam.dwInBufferSize = stringArea.length();

    char szStatusBuffer[1024] = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT struOutpurParam = { 0 };
    struOutpurParam.dwSize = sizeof(struOutpurParam);
    struOutpurParam.lpOutBuffer = NULL;
    struOutpurParam.dwOutBufferSize = 0;
    struOutpurParam.lpStatusBuffer = szStatusBuffer;
    struOutpurParam.dwStatusSize = sizeof(szStatusBuffer);

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutpurParam))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
}


BOOL CDlgLEDVersion::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}
