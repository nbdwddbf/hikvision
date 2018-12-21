// DlgRemoteeMMC.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgRemoteeMMC.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"

// CDlgRemoteeMMC 对话框

IMPLEMENT_DYNAMIC(CDlgRemoteeMMC, CDialog)

CDlgRemoteeMMC::CDlgRemoteeMMC(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteeMMC::IDD, pParent)
    , m_bChkeMMC(FALSE)
{
    m_pXmlOutput = new char[ISAPI_DATA_LEN];
    memset(m_pXmlOutput, 0, ISAPI_DATA_LEN);
}

CDlgRemoteeMMC::~CDlgRemoteeMMC()
{
}

void CDlgRemoteeMMC::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHK_eMMC, m_bChkeMMC);
}


BEGIN_MESSAGE_MAP(CDlgRemoteeMMC, CDialog)
    ON_BN_CLICKED(IDOK, &CDlgRemoteeMMC::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &CDlgRemoteeMMC::OnBnClickedCancel)
    ON_BN_CLICKED(IDCANCEL2, &CDlgRemoteeMMC::OnBnClickedCancel2)
END_MESSAGE_MAP()


// CDlgRemoteeMMC 消息处理程序


void CDlgRemoteeMMC::OnBnClickedOk()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    CXmlBase xmlInputParam;
    //CXmlBase xmlOutputParam;

    sprintf(m_sCommand, "PUT /ISAPI/ContentMgmt/Storage/eMMC\r\n");

    CXmlBase struXml;
    struXml.CreateRoot("eMMCConfiguration");
    struXml.SetAttribute("version", "2.0");

    if (m_bChkeMMC == FALSE)
    {
        struXml.AddNode("enabled", "false");
        struXml.OutOfElem();
    }
    else
    {
        struXml.AddNode("enabled", "true");
        struXml.OutOfElem();
    }

    struXml.SetRoot();
    m_csInputXml = struXml.GetChildren().c_str();
    m_csInputXml.Replace("\n", "\r\n");
    m_InPutXmlLen = m_csInputXml.GetLength();

    char *pInputXml = NULL;
    pInputXml = new char[m_InPutXmlLen + 1];
    memset(pInputXml, 0, m_InPutXmlLen + 1);
    memcpy(pInputXml, m_csInputXml.GetBuffer(0), m_InPutXmlLen);

    NET_DVR_XML_CONFIG_INPUT struInput = { 0 };
    struInput.lpRequestUrl = m_sCommand;
    struInput.dwRequestUrlLen = strlen(m_sCommand);
    struInput.lpInBuffer = pInputXml;
    struInput.dwInBufferSize = m_InPutXmlLen;
    struInput.dwSize = sizeof(NET_DVR_XML_CONFIG_INPUT);
    NET_DVR_XML_CONFIG_OUTPUT struOutput = { 0 };
    char sStatusBuf[1024] = { 0 };
    struOutput.lpStatusBuffer = sStatusBuf;
    struOutput.dwStatusSize = sizeof(sStatusBuf);
    //struOutput.lpOutBuffer = m_pXmlOutput;
    //struOutput.dwOutBufferSize = ISAPI_DATA_LEN;
    struOutput.dwSize = sizeof(NET_DVR_XML_CONFIG_OUTPUT);

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOutput))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig  eMMC ");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig  eMMC ");
    }

    UpdateData(FALSE);
}


void CDlgRemoteeMMC::OnBnClickedCancel()
{
    // TODO:  在此添加控件通知处理程序代码
    CDialog::OnCancel();
}


void CDlgRemoteeMMC::OnBnClickedCancel2()
{
    CXmlBase xmlOutputParam;
    sprintf(m_sCommand, "GET /ISAPI/ContentMgmt/Storage/eMMC\r\n");
    string strTemp = "";
    NET_DVR_XML_CONFIG_INPUT struInput = { 0 };
    struInput.lpRequestUrl = m_sCommand;
    struInput.dwRequestUrlLen = strlen(m_sCommand);
    struInput.dwSize = sizeof(NET_DVR_XML_CONFIG_INPUT);
    NET_DVR_XML_CONFIG_OUTPUT struOutput = { 0 };
    char sStatusBuf[1024] = { 0 };
    struOutput.lpStatusBuffer = sStatusBuf;
    struOutput.dwStatusSize = sizeof(sStatusBuf);
    struOutput.lpOutBuffer = m_pXmlOutput;
    struOutput.dwOutBufferSize = ISAPI_DATA_LEN;
    struOutput.dwSize = sizeof(NET_DVR_XML_CONFIG_OUTPUT);

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOutput))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig  eMMC ");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig  eMMC ");
    }

    if (xmlOutputParam.FindElem("eMMCConfiguration") && xmlOutputParam.IntoElem())
    {
        if (xmlOutputParam.FindElem("enabled"))
        {
            strTemp = xmlOutputParam.GetData();
            if (strTemp.compare("false") == 0)
            {
                m_bChkeMMC = FALSE;
            }
            else if (strTemp.compare("true") == 0)
            {
                m_bChkeMMC = TRUE;
            }
        }
    }

    UpdateData(FALSE);
}
