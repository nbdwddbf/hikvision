// DlgCVRResourceIPCfg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgCVRResourceIPCfg.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"


// CDlgCVRResourceIPCfg 对话框

IMPLEMENT_DYNAMIC(CDlgCVRResourceIPCfg, CDialogEx)

CDlgCVRResourceIPCfg::CDlgCVRResourceIPCfg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCVRResourceIPCfg::IDD, pParent)
    , m_strIPv4Address(_T(""))
    , m_strIPv6Address(_T(""))
    , m_strIPv4SubnetMask(_T(""))
    , m_strIPv6SubnetMask(_T(""))
{

}

CDlgCVRResourceIPCfg::~CDlgCVRResourceIPCfg()
{
}

void CDlgCVRResourceIPCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_ADDRESS_TYPE, m_comboAddressType);
    DDX_Control(pDX, IDC_COMBO_IP_VERSION, m_comboIPVersion);
    DDX_Text(pDX, IDC_EDIT_IPV4_ADDRESS, m_strIPv4Address);
    DDX_Text(pDX, IDC_EDIT_IPV6_ADDRESS, m_strIPv6Address);
    DDX_Text(pDX, IDC_EDIT_IPV4_SUBNETMASK, m_strIPv4SubnetMask);
    DDX_Text(pDX, IDC_EDIT_IPV6_SUBNETMASK, m_strIPv6SubnetMask);
}


BEGIN_MESSAGE_MAP(CDlgCVRResourceIPCfg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_GET, &CDlgCVRResourceIPCfg::OnBnClickedButtonGet)
    ON_BN_CLICKED(IDC_BUTTON_SET, &CDlgCVRResourceIPCfg::OnBnClickedButtonSet)
END_MESSAGE_MAP()


// CDlgCVRResourceIPCfg 消息处理程序

BOOL CDlgCVRResourceIPCfg::CreateResourceIPCfg(char* pBuf, DWORD dwBufLen, int &dwRet)
{
    CXmlBase xmlBase;
    CString strParam = _T("");
    xmlBase.CreateRoot("ResourceIPConfiguration");
    xmlBase.SetAttribute("version", "2.0");
    if (m_comboIPVersion.GetCurSel() == 0)
    {
        xmlBase.AddNode("ipVersion", "v4");
        xmlBase.OutOfElem();

        xmlBase.AddNode("ipAddress", m_strIPv4Address.GetBuffer(0));
        xmlBase.OutOfElem();

        xmlBase.AddNode("subnetMask", m_strIPv4SubnetMask.GetBuffer(0));
        xmlBase.OutOfElem();
    }
    else if (m_comboIPVersion.GetCurSel() == 1)
    {
        xmlBase.AddNode("ipVersion", "v6");
        xmlBase.OutOfElem();

        xmlBase.AddNode("ipv6Address", m_strIPv6Address.GetBuffer(0));
        xmlBase.OutOfElem();

        xmlBase.AddNode("bitMask", m_strIPv6SubnetMask.GetBuffer(0));
        xmlBase.OutOfElem();
    }
    else if (m_comboIPVersion.GetCurSel() == 2)
    {
        xmlBase.AddNode("ipVersion", "dual");
        xmlBase.OutOfElem();

        xmlBase.AddNode("ipAddress", m_strIPv4Address.GetBuffer(0));
        xmlBase.OutOfElem();

        xmlBase.AddNode("subnetMask", m_strIPv4SubnetMask.GetBuffer(0));
        xmlBase.OutOfElem();

        xmlBase.AddNode("ipv6Address", m_strIPv6Address.GetBuffer(0));
        xmlBase.OutOfElem();

        xmlBase.AddNode("bitMask", m_strIPv6SubnetMask.GetBuffer(0));
        xmlBase.OutOfElem();
    }

    if (m_comboAddressType.GetCurSel() == 0)
    {
        xmlBase.AddNode("addressingType", "static");
        xmlBase.OutOfElem();
    }
    else if (m_comboAddressType.GetCurSel() == 1)
    {
        xmlBase.AddNode("addressingType", "dynamic");
        xmlBase.OutOfElem();
    }
    else if (m_comboAddressType.GetCurSel() == 2)
    {
        xmlBase.AddNode("addressingType", "apipa");
        xmlBase.OutOfElem();
    }

    return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}


void CDlgCVRResourceIPCfg::OnBnClickedButtonGet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    char szUrl[256] = { 0 };
    sprintf(szUrl, "GET /ISAPI/System/Network/ResourceIPConfiguration\r\n");
    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    DWORD dwOutputLen = 1024 * 1024;
    char *pOutBuf = new char[dwOutputLen];
    memset(pOutBuf, 0, dwOutputLen);
    struOuput.lpOutBuffer = pOutBuf;
    struOuput.dwOutBufferSize = dwOutputLen;

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szUrl);
        if (pOutBuf != NULL)
        {
            delete[]pOutBuf;
            pOutBuf = NULL;
        }
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);
    }

    CXmlBase xmlBase;
    xmlBase.Parse(pOutBuf);
    if (xmlBase.FindElem("ResourceIPConfiguration") && xmlBase.IntoElem())
    {
        if (xmlBase.FindElem("ipVersion"))
        {
            if (xmlBase.GetData().compare("v4") == 0)
            {
                m_comboIPVersion.SetCurSel(0);

                if (xmlBase.FindElem("addressingType"))
                {
                    if (xmlBase.GetData().compare("static") == 0)
                    {
                        m_comboAddressType.SetCurSel(0);
                    }
                    else if (xmlBase.GetData().compare("dynamic") == 0)
                    {
                        m_comboAddressType.SetCurSel(1);
                    }
                    else if (xmlBase.GetData().compare("apipa") == 0)
                    {
                        m_comboAddressType.SetCurSel(2);
                    }
                }

                if (xmlBase.FindElem("ipAddress"))
                {
                    m_strIPv4Address = xmlBase.GetData().c_str();
                }
                if (xmlBase.FindElem("subnetMask"))
                {
                    m_strIPv4SubnetMask = xmlBase.GetData().c_str();
                }
            }
            else if (xmlBase.GetData().compare("v6") == 0)
            {
                m_comboIPVersion.SetCurSel(1);

                if (xmlBase.FindElem("addressingType"))
                {
                    if (xmlBase.GetData().compare("static") == 0)
                    {
                        m_comboAddressType.SetCurSel(0);
                    }
                    else if (xmlBase.GetData().compare("dynamic") == 0)
                    {
                        m_comboAddressType.SetCurSel(1);
                    }
                    else if (xmlBase.GetData().compare("apipa") == 0)
                    {
                        m_comboAddressType.SetCurSel(2);
                    }
                }

                if (xmlBase.FindElem("ipv6Address"))
                {
                    m_strIPv6Address = xmlBase.GetData().c_str();
                }
                if (xmlBase.FindElem("bitMask"))
                {
                    m_strIPv6SubnetMask = xmlBase.GetData().c_str();
                }
            }
            else if (xmlBase.GetData().compare("dual") == 0)
            {
                m_comboIPVersion.SetCurSel(2);

                if (xmlBase.FindElem("addressingType"))
                {
                    if (xmlBase.GetData().compare("static") == 0)
                    {
                        m_comboAddressType.SetCurSel(0);
                    }
                    else if (xmlBase.GetData().compare("dynamic") == 0)
                    {
                        m_comboAddressType.SetCurSel(1);
                    }
                    else if (xmlBase.GetData().compare("apipa") == 0)
                    {
                        m_comboAddressType.SetCurSel(2);
                    }
                }

                if (xmlBase.FindElem("ipAddress"))
                {
                    m_strIPv4Address = xmlBase.GetData().c_str();
                }
                if (xmlBase.FindElem("subnetMask"))
                {
                    m_strIPv4SubnetMask = xmlBase.GetData().c_str();
                }

                if (xmlBase.FindElem("ipv6Address"))
                {
                    m_strIPv6Address = xmlBase.GetData().c_str();
                }
                if (xmlBase.FindElem("bitMask"))
                {
                    m_strIPv6SubnetMask = xmlBase.GetData().c_str();
                }
            }
        }
        xmlBase.OutOfElem();
    }

    if (pOutBuf != NULL)
    {
        delete[]pOutBuf;
        pOutBuf = NULL;
    }
    UpdateData(FALSE);

    return;
}


void CDlgCVRResourceIPCfg::OnBnClickedButtonSet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    DWORD dwBufLen = 10 * 1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);
    int dwXmlLen = 0;
    if (!CreateResourceIPCfg(pBuf, dwBufLen, dwXmlLen))
    {
        delete[]pBuf;
        pBuf = NULL;
        return;
    }

    char szUrl[256] = { 0 };
    sprintf(szUrl, "PUT /ISAPI/System/Network/ResourceIPConfiguration\r\n");
    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    struInput.lpInBuffer = pBuf;
    struInput.dwInBufferSize = dwXmlLen;
    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szUrl);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);
    }

    if (pBuf != NULL)
    {
        delete[]pBuf;
        pBuf = NULL;
    }

    UpdateData(FALSE);
}
