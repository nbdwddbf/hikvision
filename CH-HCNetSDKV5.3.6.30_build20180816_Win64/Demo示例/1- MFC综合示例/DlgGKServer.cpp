// DlgGKServer.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgGKServer.h"
#include "afxdialogex.h"
#include "XMLParamsConvert.h"


// CDlgGKServer 对话框

IMPLEMENT_DYNAMIC(CDlgGKServer, CDialogEx)

CDlgGKServer::CDlgGKServer(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgGKServer::IDD, pParent)
    , m_bEnable(FALSE)
    , m_wPort(0)
{

}

CDlgGKServer::~CDlgGKServer()
{
}

void CDlgGKServer::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
    DDX_Text(pDX, IDC_EDIT_PORT, m_wPort);
}


BEGIN_MESSAGE_MAP(CDlgGKServer, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_GET, &CDlgGKServer::OnBnClickedBtnGet)
    ON_BN_CLICKED(IDC_BTN_SET, &CDlgGKServer::OnBnClickedBtnSet)
END_MESSAGE_MAP()


// CDlgGKServer 消息处理程序


void CDlgGKServer::OnBnClickedBtnGet()
{
    // TODO:  在此添加控件通知处理程序代码
    NET_DVR_XML_CONFIG_INPUT struInputParam = { 0 };
    struInputParam.dwSize = sizeof(struInputParam);
    struInputParam.lpRequestUrl = "GET /ISAPI/VCS/mcu/gkServer";
    struInputParam.dwRequestUrlLen = strlen("GET /ISAPI/VCS/mcu/gkServer");

    char szStatusBuff[1024] = { 0 };
    char szOutputXml[1024] = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT struOutputParam = { 0 };
    struOutputParam.dwSize = sizeof(struOutputParam);
    struOutputParam.lpOutBuffer = szOutputXml;
    struOutputParam.dwOutBufferSize = 1024;
    struOutputParam.lpStatusBuffer = szStatusBuff;
    struOutputParam.dwStatusSize = sizeof(szStatusBuff);

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");

    CXmlBase struXmlResult;

    if (struXmlResult.Parse((char*)struOutputParam.lpOutBuffer))
    {
        if (struXmlResult.FindElem("GkServer") && struXmlResult.IntoElem())
        {
            if (struXmlResult.FindElem("enabled"))
            {
                ConvertSingleNodeData(&m_bEnable, struXmlResult, "enabled", NODE_STRING_TO_BOOL);
            }

            if (struXmlResult.FindElem("serverPort"))
            {
                ConvertSingleNodeData(&m_wPort, struXmlResult, "serverPort", NODE_STRING_TO_WORD);
            }
            struXmlResult.OutOfElem();
        }
    }
    UpdateData(FALSE);
}


void CDlgGKServer::OnBnClickedBtnSet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    CXmlBase struXmlParam;
    struXmlParam.CreateRoot("GkServer");
    struXmlParam.SetAttribute("version", "2.0");
    struXmlParam.SetAttribute("xmlns", "http://www.isapi.org/ver20/XMLSchema");

    ConvertSingleNodeData(&m_bEnable, struXmlParam, "enabled", NODE_BOOL_TO_STRING);
    ConvertSingleNodeData(&m_wPort, struXmlParam, "serverPort", NODE_WORD_TO_STRING);
    char *szXMLParamBuf = new char[1024];
    memset(szXMLParamBuf, 0, 1024);
    DWORD dwXMLParamBufLen = 0;

    if (!PrintXmlToNewBuffer(&szXMLParamBuf, dwXMLParamBufLen, struXmlParam))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "PrintXmlToNewBuffer");
        return;
    }

    NET_DVR_XML_CONFIG_INPUT struXMLCfgInput = { 0 };
    struXMLCfgInput.dwSize = sizeof(struXMLCfgInput);
    struXMLCfgInput.lpRequestUrl = "PUT /ISAPI/VCS/mcu/gkServer";
    struXMLCfgInput.dwRequestUrlLen = strlen("PUT /ISAPI/VCS/mcu/gkServer");
    struXMLCfgInput.lpInBuffer = szXMLParamBuf;
    struXMLCfgInput.dwInBufferSize = dwXMLParamBufLen;

    NET_DVR_XML_CONFIG_OUTPUT struXMLCfgOutput = { 0 };
    char szXMLStatus[1024] = { 0 };
    memset(szXMLStatus, 0, 1024);
    struXMLCfgOutput.dwSize = sizeof(struXMLCfgOutput);
    struXMLCfgOutput.lpOutBuffer = NULL;
    struXMLCfgOutput.dwOutBufferSize = 0;
    struXMLCfgOutput.lpStatusBuffer = szXMLStatus;
    struXMLCfgOutput.dwStatusSize = 1024;

    
    if (NET_DVR_STDXMLConfig(m_lUserID, &struXMLCfgInput, &struXMLCfgOutput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
    }
    if (szXMLParamBuf != NULL)
    {
        delete[] szXMLParamBuf;
        szXMLParamBuf = NULL;
    }
}


BOOL CDlgGKServer::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}
