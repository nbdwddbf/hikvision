// DlgCluster.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgCluster.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"
#include "XMLParamsConvert.h"

// CDlgCluster 对话框

IMPLEMENT_DYNAMIC(CDlgCluster, CDialogEx)

CDlgCluster::CDlgCluster(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCluster::IDD, pParent)
    , m_csClusterIpv6(_T(""))
    , m_csNvrIpv6(_T(""))
    , m_csClusterIPv4(_T(""))
    , m_csNvrIpv4(_T(""))
    , m_csPassword(_T(""))
    , m_csPort(_T(""))
    , m_csUsername(_T(""))
    , m_csLastXml(_T(""))
    , m_bEnableInputXml(FALSE)
    , m_bEnableEncrypt(FALSE)
    , m_csHttpPort(_T(""))
    , m_dwDeviceID(0)
{
    m_pBuffer = NULL;
    m_bEdit = FALSE;
    m_dwUnitNum = 0;
    for (int i = 0; i < 20;i++)
    {
        memset(&m_struLoginInfo, 0, sizeof(m_struLoginInfo));
    }
}

CDlgCluster::~CDlgCluster()
{

    if (m_pBuffer != NULL)
    {
        delete[]m_pBuffer;
        m_pBuffer = NULL;
    }
}

void CDlgCluster::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_IPMODE_CLUSTER, m_comboClusterIpMode);
    DDX_Control(pDX, IDC_COMBO_IPMODE_NVR, m_comboNvrIpMode);
    DDX_Control(pDX, IDC_LIST_DEVICE, m_listDevice);
    DDX_Control(pDX, IDC_COMBO_MODE, m_comboClusterMode);
    DDX_Text(pDX, IDC_EDIT_IPV6_CLUSTER, m_csClusterIpv6);
    DDX_Text(pDX, IDC_EDIT_IPV6_NVR, m_csNvrIpv6);
    DDX_Text(pDX, IDC_EDIT_IPV4_CLUSTER, m_csClusterIPv4);
    DDX_Text(pDX, IDC_EDIT_IPV4_NVR, m_csNvrIpv4);
    DDX_Text(pDX, IDC_EDIT_PASSWORD_NVR, m_csPassword);
    DDX_Text(pDX, IDC_EDIT_PORT_NVR, m_csPort);
    DDX_Text(pDX, IDC_EDIT_USERNAME_NVR, m_csUsername);
    DDX_Text(pDX, IDC_EDIT_PARAM_INPUT, m_csLastXml);
    DDX_Check(pDX, IDC_CHECK_USERINPUT, m_bEnableInputXml);
    DDX_Check(pDX, IDC_CHECK_ENCRYPT, m_bEnableEncrypt);
    DDX_Text(pDX, IDC_EDIT_PORT_HTTP, m_csHttpPort);
    DDX_Text(pDX, IDC_EDIT_DEVICE_NO, m_dwDeviceID);
}


BEGIN_MESSAGE_MAP(CDlgCluster, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_GET, &CDlgCluster::OnBnClickedButtonGet)
    ON_BN_CLICKED(IDC_BUTTON_SET, &CDlgCluster::OnBnClickedButtonSet)
    ON_BN_CLICKED(IDC_BUTTON_ADD, &CDlgCluster::OnBnClickedButtonAdd)
    ON_BN_CLICKED(IDC_BUTTON_DEL, &CDlgCluster::OnBnClickedButtonDel)
    ON_BN_CLICKED(IDC_BUTTON_ADDTOLIST, &CDlgCluster::OnBnClickedButtonAddtolist)
    ON_BN_CLICKED(IDC_BUTTON_DELFROMLIST, &CDlgCluster::OnBnClickedButtonDelfromlist)
    ON_BN_CLICKED(IDC_BUTTON_XML, &CDlgCluster::OnBnClickedButtonXml)
    ON_BN_CLICKED(IDC_BUTTON_ADDALL, &CDlgCluster::OnBnClickedButtonAddall)
    //ON_BN_CLICKED(IDC_BUTTON_DELALL, &CDlgCluster::OnBnClickedButtonDelall)
    ON_BN_CLICKED(IDOK, &CDlgCluster::OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON_CLEAR_LIST, &CDlgCluster::OnBnClickedButtonClearList)
    ON_NOTIFY(NM_CLICK, IDC_LIST_DEVICE, &CDlgCluster::OnNMClickListDevice)
    ON_BN_CLICKED(IDC_BUTTON_MODIFY_LIST, &CDlgCluster::OnBnClickedButtonModifyList)
    ON_BN_CLICKED(IDC_BUTTON_CLUSTER_CREATE, &CDlgCluster::OnBnClickedButtonClusterCreate)
    ON_BN_CLICKED(IDC_BUTTON_GET_DEVICE_INFO, &CDlgCluster::OnBnClickedButtonGetDeviceInfo)
    ON_BN_CLICKED(IDC_BTN_GET_CLUSTER_STATUS, &CDlgCluster::OnBnClickedBtnGetClusterStatus)
END_MESSAGE_MAP()

/** @fn         BOOL ConvertModeXmlNodeToShow(const char* pXmlBuf)
*  @brief      获取xml节点在控件上显示
*  @param (in)	const char* pXmlBuf
*  @param (in)	void*       pStruct
*  @return     BOOL
*/
BOOL CDlgCluster::ConvertModeXmlNodeToShow(const char* pXmlBuf)
{
    CXmlBase struXml;
    if (struXml.Parse(pXmlBuf) == NULL)
    {
        return FALSE;
    }

    if (struXml.FindElem("ClusterMode") && struXml.IntoElem())
    {
        if (struXml.FindElem("ipVersion"))
        {
            CString csIpVersion = struXml.GetData().c_str();
            if (csIpVersion == _T("v4"))
            {
                m_comboClusterIpMode.SetCurSel(0);
            }
            else if (csIpVersion == _T("v6"))
            {
                m_comboClusterIpMode.SetCurSel(1);
            }
            else if (csIpVersion == _T("dual"))
            {
                m_comboClusterIpMode.SetCurSel(2);
            }
            else
            {
                AfxMessageBox("xml node error");
            }
        }

        if (struXml.FindElem("mode"))
        {
            CString csMode = struXml.GetData().c_str();
            if (csMode == _T("single"))
            {
                m_comboClusterMode.SetCurSel(0);
            }
            else if (csMode == _T("cluster"))
            {
                m_comboClusterMode.SetCurSel(1);
            }
            else
            {
                AfxMessageBox("xml node error");
            }
        }

        if (struXml.FindElem("clusterIPv4"))
        {
            m_csClusterIPv4 = struXml.GetData().c_str();
        }

        if (struXml.FindElem("clusterIPv6"))
        {
            m_csClusterIpv6 = struXml.GetData().c_str();
        }

        struXml.OutOfElem();
    }

    return TRUE;
}

/** @fn        BOOL PackageModeXml( char* *pXmlBuf, DWORD &dwXmlLen)
*  @brief      组装设备工作模式的xml报文
*  @param (in)	char** pXmlBuf
*  @param (in)	DWORD& dwXmlLen
*  @return     BOOL
*/
BOOL CDlgCluster::PackageModeXml(char* *pXmlBuf, DWORD &dwXmlLen)
{
    if (pXmlBuf == NULL)
    {
        return FALSE;
    }

    CXmlBase struXml;
    struXml.CreateRoot("ClusterMode");
    struXml.SetAttribute("version", "2.0");
    struXml.SetAttribute("xmlns", "http://www.isapi.org/ver20/XMLSchema");

    if (m_comboClusterMode.GetCurSel() == 0)
    {
        if (struXml.AddNode("mode", "single"))
        {
            struXml.OutOfElem();
        }
    }
    else
    {
        if (struXml.AddNode("mode", "cluster"))
        {
            struXml.OutOfElem();
        }
    }

    if(m_comboClusterIpMode.GetCurSel() == 0)
    {
        if (struXml.AddNode("ipVersion", "v4"))
        {
            struXml.OutOfElem();
        }
    }
    else if (m_comboClusterIpMode.GetCurSel() == 1)
    {
        if (struXml.AddNode("ipVersion", "v6"))
        {
            struXml.OutOfElem();
        }
    }
    else
    {
        if (struXml.AddNode("ipVersion", "dual"))
        {
            struXml.OutOfElem();
        }
    }

    if (struXml.AddNode("clusterIPv4", m_csClusterIPv4.GetBuffer(0)))
    {
        struXml.OutOfElem();
    }

    if (struXml.AddNode("clusterIPv6", m_csClusterIpv6.GetBuffer(0)))
    {
        struXml.OutOfElem();
    }

    if (!PrintXmlToNewBuffer(pXmlBuf, dwXmlLen, struXml))
    {
        return FALSE;
    }

    return TRUE;
}

/** @fn        BOOL PackageDeviceInfoXml(char* *pXmlBuf, DWORD &dwXmlLen)
*  @brief      组装设备信息的xml报文
*  @param (in)	char** pXmlBuf
*  @param (in)	DWORD& dwXmlLen
*  @return     BOOL
*/
BOOL CDlgCluster::PackageDeviceInfoXml(char* *pXmlBuf, DWORD &dwXmlLen)
{
    if (pXmlBuf == NULL)
    {
        return FALSE;
    }

    CXmlBase struXml;
    struXml.CreateRoot("DevAccessInfoList");
    struXml.SetAttribute("version", "2.0");
    struXml.SetAttribute("xmlns", "http://www.isapi.org/ver20/XMLSchema");

    if (struXml.AddNode("DevAccessInfo"))
    {
        if (m_comboClusterIpMode.GetCurSel() == 0)
        {
            if (struXml.AddNode("ipVersion", "v4"))
            {
                struXml.OutOfElem();
            }
        }
        else if (m_comboClusterIpMode.GetCurSel() == 1)
        {
            if (struXml.AddNode("ipVersion", "v6"))
            {
                struXml.OutOfElem();
            }
        }
        else
        {
            if (struXml.AddNode("ipVersion", "dual"))
            {
                struXml.OutOfElem();
            }
        }

        if (struXml.AddNode("ipAddress", m_csNvrIpv4.GetBuffer(0)))
        {
            struXml.OutOfElem();
        }

        if (struXml.AddNode("ipv6Address", m_csNvrIpv6.GetBuffer(0)))
        {
            struXml.OutOfElem();
        }

        if (struXml.AddNode("port", m_csPort.GetBuffer(0)))
        {
            struXml.OutOfElem();
        }

        if (struXml.AddNode("loginName", m_csUsername.GetBuffer(0)))
        {
            struXml.OutOfElem();
        }

        if (struXml.AddNode("passwd", m_csPassword.GetBuffer(0)))
        {
            struXml.OutOfElem();
        }

        if (struXml.AddNode("httpPort", m_csHttpPort.GetBuffer(0)))
        {
            struXml.OutOfElem();
        }

        struXml.OutOfElem();
    }
    if (!PrintXmlToNewBuffer(pXmlBuf, dwXmlLen, struXml))
    {
        return FALSE;
    }

    return TRUE;
}


/** @fn        BOOL PackageDeviceInfoXml(char* *pXmlBuf, DWORD &dwXmlLen)
*  @brief      组装所有的设备信息xml报文
*  @param (in)	char** pXmlBuf
*  @param (in)	DWORD& dwXmlLen
*  @return     BOOL
*/
BOOL CDlgCluster::PackageAllDeviceInfoXml(char* *pXmlBuf, DWORD &dwXmlLen)
{
    if (pXmlBuf == NULL)
    {
        return FALSE;
    }

    CXmlBase struXml;
    struXml.CreateRoot("DevAccessInfoList");
    struXml.SetAttribute("version", "2.0");
    struXml.SetAttribute("xmlns", "http://www.isapi.org/ver20/XMLSchema");

    int nItemCount = m_listDevice.GetItemCount();
    if (nItemCount < 0)
    {
        return FALSE;
    }

    for (int i = 0; i < nItemCount; i++)
    {
        string csValue[7] = { "" };
        for (int j = 0; j < 7; j++)
        {
            csValue[j] = m_listDevice.GetItemText(i, j+1);
        }

        if (struXml.AddNode("DevAccessInfo"))
        {
            if (struXml.AddNode("ipVersion", csValue[0]))
            {
                struXml.OutOfElem();
            }

            if (struXml.AddNode("ipAddress", csValue[1]))
            {
                struXml.OutOfElem();
            }

            if (struXml.AddNode("ipv6Address", csValue[2]))
            {
                struXml.OutOfElem();
            }

            if (struXml.AddNode("port", csValue[3]))
            {
                struXml.OutOfElem();
            }

            if (struXml.AddNode("httpPort", csValue[4]))
            {
                struXml.OutOfElem();
            }

            if (struXml.AddNode("loginName", csValue[5]))
            {
                struXml.OutOfElem();
            }

            if (struXml.AddNode("passwd", csValue[6]))
            {
                struXml.OutOfElem();
            }

            struXml.OutOfElem();
        }
    }
    if (!PrintXmlToNewBuffer(pXmlBuf, dwXmlLen, struXml))
    {
        return FALSE;
    }

    return TRUE;
}

/** @fn        BOOL PackageClusterInfoXml(char* *pXmlBuf, DWORD &dwXmlLen)
*  @brief      组装集群组网的xml报文
*  @param (in)	char** pXmlBuf
*  @param (in)	DWORD& dwXmlLen
*  @return     BOOL
*/
BOOL CDlgCluster::PackageClusterInfoXml(char* *pXmlBuf, DWORD &dwXmlLen)
{
    if (pXmlBuf == NULL)
    {
        return FALSE;
    }

    CXmlBase struXml;
    struXml.CreateRoot("ClusterCreation");
    struXml.SetAttribute("version", "2.0");
    struXml.SetAttribute("xmlns", "http://www.isapi.org/ver20/XMLSchema");

    int nItemCount = m_listDevice.GetItemCount();
    if (nItemCount >= 0)
    {
        if (struXml.AddNode("DevAccessInfoList"))
        {
            for (int i = 0; i < nItemCount; i++)
            {
                string csValue[7] = { "" };
                for (int j = 0; j < 7; j++)
                {
                    csValue[j] = m_listDevice.GetItemText(i, j + 1);
                }

                if (struXml.AddNode("DevAccessInfo"))
                {
                    if (struXml.AddNode("ipVersion", csValue[0]))
                    {
                        struXml.OutOfElem();
                    }

                    if (struXml.AddNode("ipAddress", csValue[1]))
                    {
                        struXml.OutOfElem();
                    }

                    if (struXml.AddNode("ipv6Address", csValue[2]))
                    {
                        struXml.OutOfElem();
                    }

                    if (struXml.AddNode("port", csValue[3]))
                    {
                        struXml.OutOfElem();
                    }

                    if (struXml.AddNode("httpPort", csValue[4]))
                    {
                        struXml.OutOfElem();
                    }

                    if (struXml.AddNode("loginName", csValue[5]))
                    {
                        struXml.OutOfElem();
                    }

                    if (struXml.AddNode("passwd", csValue[6]))
                    {
                        struXml.OutOfElem();
                    }
                    struXml.OutOfElem();
                }
            }
            struXml.OutOfElem();
        }
    }

    if (struXml.AddNode("ClusterInfo"))
    {
        if (m_comboClusterIpMode.GetCurSel() == 0)
        {
            if (struXml.AddNode("ipVersion", "v4"))
            {
                struXml.OutOfElem();
            }
        }
        else if (m_comboClusterIpMode.GetCurSel() == 1)
        {
            if (struXml.AddNode("ipVersion", "v6"))
            {
                struXml.OutOfElem();
            }
        }
        else
        {
            if (struXml.AddNode("ipVersion", "dual"))
            {
                struXml.OutOfElem();
            }
        }

        if (struXml.AddNode("ipAddress", m_csNvrIpv4.GetBuffer(0)))
        {
            struXml.OutOfElem();
        }

        if (struXml.AddNode("ipv6Address", m_csNvrIpv6.GetBuffer(0)))
        {
            struXml.OutOfElem();
        }

        if (struXml.AddNode("port", m_csPort.GetBuffer(0)))
        {
            struXml.OutOfElem();
        }

        if (struXml.AddNode("loginName", m_csUsername.GetBuffer(0)))
        {
            struXml.OutOfElem();
        }

        if (struXml.AddNode("passwd", m_csPassword.GetBuffer(0)))
        {
            struXml.OutOfElem();
        }

        if (struXml.AddNode("httpPort", m_csHttpPort.GetBuffer(0)))
        {
            struXml.OutOfElem();
        }

        struXml.OutOfElem();

    }
    if (!PrintXmlToNewBuffer(pXmlBuf, dwXmlLen, struXml))
    {
        return FALSE;
    }

    return TRUE;
}

void CDlgCluster::Initbuff()
{
    memset(m_pBuffer, 0, m_dwBufferLen);
    memset(&m_struInput, 0, sizeof(m_struInput));
    memset(&m_struOuput, 0, sizeof(m_struOuput));
    m_struInput.dwSize = sizeof(m_struInput);
    m_struOuput.dwSize = sizeof(m_struOuput);
}

void CDlgCluster::OnBnClickedButtonGet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    Initbuff();
    char szUrl[256] = { 0 };
    char szLan[64] = { 0 };

    sprintf(szUrl,"GET /ISAPI/ContentMgmt/Cluster/ClusterMode\r\n");
    m_struInput.lpRequestUrl = szUrl;
    m_struInput.dwRequestUrlLen = strlen(szUrl);
    m_struOuput.lpOutBuffer = m_pBuffer;
    m_struOuput.dwOutBufferSize = m_dwBufferLen;

    if (!NET_DVR_STDXMLConfig(m_lUserID, &m_struInput, &m_struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szUrl);
        //CString csPrompt;
        //g_StringLanType(szLan, "获取设备工作模式", "Get device work mode fail");
        //csPrompt.Format("%s[%d]", szLan, NET_DVR_GetLastError());
        //AfxMessageBox(csPrompt);
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);

    ConvertModeXmlNodeToShow((char *)m_struOuput.lpOutBuffer);
  /*CXmlBase xmlOutput;
    xmlOutput.Parse((char *)m_struOuput.lpOutBuffer);
    xmlOutput.SetRoot();
    m_csOutputParam = xmlOutput.GetChildren().c_str();
    m_csOutputParam.Replace("\n", "\r\n")*/;
    UpdateData(FALSE);
}


void CDlgCluster::OnBnClickedButtonSet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    char szUrl[256] = { 0 };
    Initbuff();
    char szLan[64] = { 0 };

    sprintf(szUrl, "PUT /ISAPI/ContentMgmt/Cluster/ClusterMode\r\n");
    m_struInput.lpRequestUrl = szUrl;
    m_struInput.dwRequestUrlLen = strlen(szUrl);

    if (m_bEnableInputXml)
    {
        char *pInBuffer = new char[m_dwBufferLen];
        memset(pInBuffer, 0, m_dwBufferLen);
        memcpy(pInBuffer, m_csLastXml.GetBuffer(), m_csLastXml.GetLength()); 
        m_struInput.lpInBuffer = pInBuffer;
        m_struInput.dwInBufferSize = m_csLastXml.GetLength();
        int iLength = 0;
        for (int i = 0; i < m_struInput.dwInBufferSize; i++)
        {
            //此处是为了避免传递空格和换行符
            if (*((char*)m_struInput.lpInBuffer + i) != 10 && *((char*)m_struInput.lpInBuffer + i) != 32)
            {
                *((char*)m_struInput.lpInBuffer + iLength) = *((char*)m_struInput.lpInBuffer + i);
                iLength += 1;
            }
        }
        m_struInput.dwInBufferSize = iLength;
    }
    else
    {
        PackageModeXml((char* *)&m_struInput.lpInBuffer, m_struInput.dwInBufferSize);
    }

    m_struOuput.lpStatusBuffer = m_pBuffer;
    m_struOuput.dwStatusSize = m_dwBufferLen;

    if (!NET_DVR_STDXMLConfig(m_lUserID, &m_struInput, &m_struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szUrl);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);
    }

    CXmlBase xmlOutput;
    xmlOutput.Parse((char *)m_struOuput.lpStatusBuffer);
    xmlOutput.SetRoot();
    m_csLastXml = xmlOutput.GetChildren().c_str();
    m_csLastXml.Replace("\n", "\r\n");

    if (m_struInput.lpInBuffer != NULL)
    {
        delete (char*)m_struInput.lpInBuffer;
        m_struInput.lpInBuffer = NULL;
    }
    UpdateData(FALSE);
}


void CDlgCluster::OnBnClickedButtonAdd()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    char szUrl[256] = { 0 };
    Initbuff();
    char szLan[64] = { 0 };

    sprintf(szUrl, "POST /ISAPI/ContentMgmt/Cluster/device\r\n");
    m_struInput.lpRequestUrl = szUrl;
    m_struInput.dwRequestUrlLen = strlen(szUrl);
    if (m_bEnableEncrypt)
    {
        m_struInput.byForceEncrpt = 1;
    }

    if (m_bEnableInputXml)
    {
        char *pInBuffer = new char[m_dwBufferLen];
        memset(pInBuffer, 0, m_dwBufferLen);
        memcpy(pInBuffer, m_csLastXml.GetBuffer(), m_csLastXml.GetLength());
        m_struInput.lpInBuffer = pInBuffer;
        m_struInput.dwInBufferSize = m_csLastXml.GetLength();
        int iLength = 0;
        for (int i = 0; i < m_struInput.dwInBufferSize; i++)
        {
            //此处是为了避免传递空格和换行符
            if (*((char*)m_struInput.lpInBuffer + i) != 10 && *((char*)m_struInput.lpInBuffer + i) != 32)
            {
                *((char*)m_struInput.lpInBuffer + iLength) = *((char*)m_struInput.lpInBuffer + i);
                iLength += 1;
            }
        }
        m_struInput.dwInBufferSize = iLength;
    }
    else
    {
        PackageDeviceInfoXml((char* *)&m_struInput.lpInBuffer, m_struInput.dwInBufferSize);
    }

    m_struOuput.lpStatusBuffer = m_pBuffer;
    m_struOuput.dwStatusSize = m_dwBufferLen;

    if (!NET_DVR_STDXMLConfig(m_lUserID, &m_struInput, &m_struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szUrl);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);
    }

    CXmlBase xmlOutput;
    xmlOutput.Parse((char *)m_struOuput.lpStatusBuffer);
    xmlOutput.SetRoot();
    m_csLastXml = xmlOutput.GetChildren().c_str();
    m_csLastXml.Replace("\n", "\r\n");

    if (m_struInput.lpInBuffer != NULL)
    {
        delete[] (char*)m_struInput.lpInBuffer;
        m_struInput.lpInBuffer = NULL;
    }

    UpdateData(FALSE);
}


void CDlgCluster::OnBnClickedButtonDel()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    Initbuff();
    char szUrl[256] = { 0 };
    char szLan[64] = { 0 };

    sprintf(szUrl, "DELETE /ISAPI/ContentMgmt/Cluster/device/%d\r\n", m_dwDeviceID);
    m_struInput.lpRequestUrl = szUrl;
    m_struInput.dwRequestUrlLen = strlen(szUrl);
    if (m_bEnableEncrypt)
    {
        m_struInput.byForceEncrpt = 1;
    }

    if (m_bEnableInputXml)
    {
        char *pInBuffer = new char[m_dwBufferLen];
        memset(pInBuffer, 0, m_dwBufferLen);
        memcpy(pInBuffer, m_csLastXml.GetBuffer(), m_csLastXml.GetLength());
        m_struInput.lpInBuffer = pInBuffer;
        m_struInput.dwInBufferSize = m_csLastXml.GetLength();
        int iLength = 0;
        for (int i = 0; i < m_struInput.dwInBufferSize; i++)
        {
            //此处是为了避免传递空格和换行符
            if (*((char*)m_struInput.lpInBuffer + i) != 10 && *((char*)m_struInput.lpInBuffer + i) != 32)
            {
                *((char*)m_struInput.lpInBuffer + iLength) = *((char*)m_struInput.lpInBuffer + i);
                iLength += 1;
            }
        }
        m_struInput.dwInBufferSize = iLength;
    }
    //else
    //{
    //    PackageDeviceInfoXml((char* *)&m_struInput.lpInBuffer, m_struInput.dwInBufferSize);
    //}
    m_struOuput.lpStatusBuffer = m_pBuffer;
    m_struOuput.dwStatusSize = m_dwBufferLen;

    if (!NET_DVR_STDXMLConfig(m_lUserID, &m_struInput, &m_struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szUrl);
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);

    CXmlBase xmlOutput;
    xmlOutput.Parse((char *)m_struOuput.lpStatusBuffer);
    xmlOutput.SetRoot();
    m_csLastXml = xmlOutput.GetChildren().c_str();
    m_csLastXml.Replace("\n", "\r\n");

    if (m_struInput.lpInBuffer != NULL)
    {
        delete[] (char*)m_struInput.lpInBuffer;
        m_struInput.lpInBuffer = NULL;
    }

    UpdateData(FALSE);
}


void CDlgCluster::OnBnClickedButtonAddtolist()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    char szLan[1024] = { 0 };

    int nItemCount = m_listDevice.GetItemCount();
    CString strItem = "";
    strItem.Format("%d", nItemCount + 1);
    int iInsertIndex = m_listDevice.InsertItem(nItemCount, strItem);

    if (m_comboNvrIpMode.GetCurSel() == 0)
    {
        sprintf(szLan, "%s", "v4");
    }
    else if (m_comboNvrIpMode.GetCurSel() == 1)
    {
        sprintf(szLan, "%s", "v6");
    }
    else
    {
        sprintf(szLan, "%s", "dual");
    }
    m_listDevice.SetItemText(iInsertIndex, 1, szLan);

    sprintf(szLan, "%s", m_csNvrIpv4);
    m_listDevice.SetItemText(iInsertIndex, 2, szLan);
    sprintf(szLan, "%s", m_csNvrIpv6);
    m_listDevice.SetItemText(iInsertIndex, 3, szLan);
    sprintf(szLan, "%s", m_csPort);
    m_listDevice.SetItemText(iInsertIndex, 4, szLan);
    sprintf(szLan, "%s", m_csHttpPort);
    m_listDevice.SetItemText(iInsertIndex, 5, szLan);
    sprintf(szLan, "%s", m_csUsername);
    m_listDevice.SetItemText(iInsertIndex, 6, szLan);
    sprintf(szLan, "%s", m_csPassword);
    m_listDevice.SetItemText(iInsertIndex, 7, szLan);

    strncpy(m_struLoginInfo[nItemCount].sDeviceAddress, m_csNvrIpv4, m_csNvrIpv4.GetLength());
    strncpy(m_struLoginInfo[nItemCount].sPassword, m_csPassword, m_csPassword.GetLength());
    strncpy(m_struLoginInfo[nItemCount].sUserName, m_csUsername, m_csUsername.GetLength());
    m_struLoginInfo[nItemCount].wPort = atoi(m_csPort);
    m_dwUnitNum = nItemCount + 1;

    UpdateData(FALSE);
}


void CDlgCluster::OnBnClickedButtonDelfromlist()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    if (m_iSelectItem>=0)
    {    
        m_listDevice.DeleteItem(m_iSelectItem);
        m_iSelectItem = -1;
    }
    UpdateData(FALSE);
}


void CDlgCluster::OnBnClickedButtonModifyList()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    char szLan[1024] = { 0 };
    if (m_iSelectItem >= 0)
    {
        if (m_comboNvrIpMode.GetCurSel() == 0)
        {
            sprintf(szLan, "%s", "v4");
        }
        else if (m_comboNvrIpMode.GetCurSel() == 1)
        {
            sprintf(szLan, "%s", "v6");
        }
        else
        {
            sprintf(szLan, "%s", "dual");
        }
        m_listDevice.SetItemText(m_iSelectItem, 1, szLan);

        sprintf(szLan, "%s", m_csNvrIpv4);
        m_listDevice.SetItemText(m_iSelectItem, 2, szLan);
        sprintf(szLan, "%s", m_csNvrIpv6);
        m_listDevice.SetItemText(m_iSelectItem, 3, szLan);
        sprintf(szLan, "%s", m_csPort);
        m_listDevice.SetItemText(m_iSelectItem, 4, szLan);
        sprintf(szLan, "%s", m_csHttpPort);
        m_listDevice.SetItemText(m_iSelectItem, 5, szLan);
    }

    UpdateData(FALSE);
}

void CDlgCluster::OnBnClickedButtonClearList()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    m_listDevice.DeleteAllItems();
    UpdateData(FALSE);
}


void CDlgCluster::OnBnClickedButtonXml()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    char szLan[128] = { 0 };
    if (m_bShowList)
    {
        GetDlgItem(IDC_EDIT_PARAM_INPUT)->ShowWindow(TRUE);
        GetDlgItem(IDC_LIST_DEVICE)->ShowWindow(FALSE);
        g_StringLanType(szLan, "设备列表", "device list");
        GetDlgItem(IDC_BUTTON_XML)->SetWindowTextA(szLan);
    }
    else
    {
        GetDlgItem(IDC_EDIT_PARAM_INPUT)->ShowWindow(FALSE);
        GetDlgItem(IDC_LIST_DEVICE)->ShowWindow(TRUE);
        g_StringLanType(szLan, "查看/编辑XML", "look/edit XML");
        GetDlgItem(IDC_BUTTON_XML)->SetWindowTextA(szLan);
    }
    m_bShowList = !m_bShowList;
    UpdateData(FALSE);
}


void CDlgCluster::OnBnClickedButtonAddall()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    char szUrl[256] = { 0 };
    Initbuff();
    char szLan[64] = { 0 };

    sprintf(szUrl, "POST /ISAPI/ContentMgmt/Cluster/device\r\n");
    m_struInput.lpRequestUrl = szUrl;
    m_struInput.dwRequestUrlLen = strlen(szUrl);
    if (m_bEnableEncrypt)
    {
        m_struInput.byForceEncrpt = 1;
    }
    if (m_bEnableInputXml)
    {
        char *pInBuffer = new char[m_dwBufferLen];
        memset(pInBuffer, 0, m_dwBufferLen);
        memcpy(pInBuffer, m_csLastXml.GetBuffer(), m_csLastXml.GetLength());
        m_struInput.lpInBuffer = pInBuffer;
        m_struInput.dwInBufferSize = m_csLastXml.GetLength();
        int iLength = 0;
        for (int i = 0; i < m_struInput.dwInBufferSize; i++)
        {
            //此处是为了避免传递空格和换行符
            if (*((char*)m_struInput.lpInBuffer + i) != 10 && *((char*)m_struInput.lpInBuffer + i) != 32)
            {
                *((char*)m_struInput.lpInBuffer + iLength) = *((char*)m_struInput.lpInBuffer + i);
                iLength += 1;
            }
        }
        m_struInput.dwInBufferSize = iLength;
    }
    else
    {
        if (PackageAllDeviceInfoXml((char* *)&m_struInput.lpInBuffer, m_struInput.dwInBufferSize))
        {
            AfxMessageBox("Please add some info to list!");
            return;
        }
    }

    m_struOuput.lpStatusBuffer = m_pBuffer;
    m_struOuput.dwStatusSize = m_dwBufferLen;

    if (!NET_DVR_STDXMLConfig(m_lUserID, &m_struInput, &m_struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szUrl);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);
    }

    CXmlBase xmlOutput;
    xmlOutput.Parse((char *)m_struOuput.lpStatusBuffer);
    xmlOutput.SetRoot();
    m_csLastXml = xmlOutput.GetChildren().c_str();
    m_csLastXml.Replace("\n", "\r\n");

    if (m_struInput.lpInBuffer != NULL)
    {
        delete[] (char*)m_struInput.lpInBuffer;
        m_struInput.lpInBuffer = NULL;
    }

    UpdateData(FALSE);
}


//void CDlgCluster::OnBnClickedButtonDelall()
//{
    //UpdateData(TRUE);
    //Initbuff();
    //char szUrl[256] = { 0 };
    //char szLan[64] = { 0 };

    //sprintf(szUrl, "GET /ISAPI/ContentMgmt/Cluster/device\r\n");
    //m_struInput.lpRequestUrl = szUrl;
    //m_struInput.dwRequestUrlLen = strlen(szUrl);
    //if (m_bEnableEncrypt)
    //{
    //    m_struInput.byForceEncrpt = 1;
    //}
    //if (m_bEnableInputXml)
    //{
    //    char *pInBuffer = new char[m_dwBufferLen];
    //    memset(pInBuffer, 0, m_dwBufferLen);
    //    memcpy(pInBuffer, m_csLastXml.GetBuffer(), m_csLastXml.GetLength());
    //    m_struInput.lpInBuffer = pInBuffer;
    //    m_struInput.dwInBufferSize = m_csLastXml.GetLength();
    //    int iLength = 0;
    //    for (int i = 0; i < m_struInput.dwInBufferSize; i++)
    //    {
    //        //此处是为了避免传递空格和换行符
    //        if (*((char*)m_struInput.lpInBuffer + i) != 10 && *((char*)m_struInput.lpInBuffer + i) != 32)
    //        {
    //            *((char*)m_struInput.lpInBuffer + iLength) = *((char*)m_struInput.lpInBuffer + i);
    //            iLength += 1;
    //        }
    //    }
    //    m_struInput.dwInBufferSize = iLength;
    //}
    //else
    //{
    //    if (PackageAllDeviceInfoXml((char* *)&m_struInput.lpInBuffer, m_struInput.dwInBufferSize))
    //    {
    //        AfxMessageBox("Please add some info to list!");
    //        return;
    //    }
    //}
    //m_struOuput.lpStatusBuffer = m_pBuffer;
    //m_struOuput.dwStatusSize = m_dwBufferLen;

    //if (!NET_DVR_STDXMLConfig(m_lUserID, &m_struInput, &m_struOuput))
    //{
    //    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szUrl);
    //    return;
    //}
    //g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);

    //CXmlBase xmlOutput;
    //xmlOutput.Parse((char *)m_struOuput.lpStatusBuffer);
    //xmlOutput.SetRoot();
    //m_csLastXml = xmlOutput.GetChildren().c_str();
    //m_csLastXml.Replace("\n", "\r\n");

    //if (m_struInput.lpInBuffer != NULL)
    //{
    //    delete[](char*)m_struInput.lpInBuffer;
    //    m_struInput.lpInBuffer = NULL;
    //}
    //UpdateData(FALSE);
//}


void CDlgCluster::OnBnClickedOk()
{
    // TODO:  在此添加控件通知处理程序代码
    CDialogEx::OnOK();
}


BOOL CDlgCluster::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    char szLan[128] = { 0 };
    UpdateData(TRUE);
    memset(&m_struInput, 0, sizeof(m_struInput));
    memset(&m_struOuput, 0, sizeof(m_struOuput));
    m_struInput.dwSize = sizeof(m_struInput);
    m_struOuput.dwSize = sizeof(m_struOuput);

    m_iSelectItem = -1;

    m_comboClusterIpMode.SetCurSel(0);
    m_comboClusterMode.SetCurSel(1);
    m_comboNvrIpMode.SetCurSel(0);

    m_csUsername = _T("admin");
    m_csPort = _T("8000");

    m_listDevice.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    g_StringLanType(szLan, "编号", "No");
    m_listDevice.InsertColumn(0, szLan, LVCFMT_LEFT, 90, -1);
    g_StringLanType(szLan, "IP类型", "IP Version");
    m_listDevice.InsertColumn(1, szLan, LVCFMT_LEFT, 90, -1);
    g_StringLanType(szLan, "IPv4", "IPv4");
    m_listDevice.InsertColumn(2, szLan, LVCFMT_LEFT, 150, -1);
    g_StringLanType(szLan, "IPv6", "IPv6");
    m_listDevice.InsertColumn(3, szLan, LVCFMT_LEFT, 150, -1);
    g_StringLanType(szLan, "端口", "Port");
    m_listDevice.InsertColumn(4, szLan, LVCFMT_LEFT, 90, -1);
    g_StringLanType(szLan, "HTTP端口", "Http Port");
    m_listDevice.InsertColumn(5, szLan, LVCFMT_LEFT, 80, -1);
    g_StringLanType(szLan, "用户名", "Username");
    m_listDevice.InsertColumn(6, szLan, LVCFMT_LEFT, 80, -1);
    g_StringLanType(szLan, "密码", "Password");
    m_listDevice.InsertColumn(7, szLan, LVCFMT_LEFT, 80, -1);


    m_dwBufferLen = 1024 * 1024;
    m_pBuffer = new char[m_dwBufferLen];
    memset(m_pBuffer, 0, m_dwBufferLen);
    m_bEnableEncrypt = FALSE;
    m_bEnableInputXml = FALSE;
    m_bShowList = TRUE;
    GetDlgItem(IDC_EDIT_PARAM_INPUT)->ShowWindow(FALSE);
    GetDlgItem(IDC_LIST_DEVICE)->ShowWindow(TRUE);
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}



void CDlgCluster::OnNMClickListDevice(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    UpdateData(TRUE);

    int nItem = pNMItemActivate->iItem;
    m_iSelectItem = nItem;

    if (nItem >= 0 && nItem < m_listDevice.GetItemCount())//判断单击击位置是否在有数据的列表项上面
    {
        CString csTmp;
        csTmp = m_listDevice.GetItemText(nItem, 1);
        if (!strcmp(csTmp,"v4"))
        {
            m_comboNvrIpMode.SetCurSel(0);
        }
        else if (!strcmp(csTmp, "v6"))
        {
            m_comboNvrIpMode.SetCurSel(1);
        }
        else
        {
            m_comboNvrIpMode.SetCurSel(2);
        }

        m_csNvrIpv4 = m_listDevice.GetItemText(nItem, 2);
        m_csNvrIpv6 = m_listDevice.GetItemText(nItem, 3);
        m_csPort = m_listDevice.GetItemText(nItem, 4);
        m_csHttpPort = m_listDevice.GetItemText(nItem, 5);
        m_csUsername = m_listDevice.GetItemText(nItem, 6);
        m_csPassword = m_listDevice.GetItemText(nItem, 7);
    }
    UpdateData(FALSE);
    *pResult = 0;
}

void CDlgCluster::OnBnClickedButtonClusterCreate()
{
    // TODO:  在此添加控件通知处理程序代码

    UpdateData(TRUE);
    char szUrl[256] = { 0 };
    Initbuff();
    char szLan[64] = { 0 };

    sprintf(szUrl, "PUT /ISAPI/ContentMgmt/Cluster/Creation\r\n");
    m_struInput.lpRequestUrl = szUrl;
    m_struInput.dwRequestUrlLen = strlen(szUrl);
    if (m_bEnableEncrypt)
    {
        m_struInput.byForceEncrpt = 1;
    }
    if (m_bEnableInputXml)
    {
        char *pInBuffer = new char[m_dwBufferLen];
        memset(pInBuffer, 0, m_dwBufferLen);
        memcpy(pInBuffer, m_csLastXml.GetBuffer(), m_csLastXml.GetLength());
        m_struInput.lpInBuffer = pInBuffer;
        m_struInput.dwInBufferSize = m_csLastXml.GetLength();
        int iLength = 0;
        for (int i = 0; i < m_struInput.dwInBufferSize; i++)
        {
            //此处是为了避免传递空格和换行符
            if (*((char*)m_struInput.lpInBuffer + i) != 10 && *((char*)m_struInput.lpInBuffer + i) != 32)
            {
                *((char*)m_struInput.lpInBuffer + iLength) = *((char*)m_struInput.lpInBuffer + i);
                iLength += 1;
            }
        }
        m_struInput.dwInBufferSize = iLength;
    }
    else
    {
        PackageClusterInfoXml((char* *)&m_struInput.lpInBuffer, m_struInput.dwInBufferSize);
    }

    m_struOuput.lpStatusBuffer = m_pBuffer;
    m_struOuput.dwStatusSize = m_dwBufferLen;


    strncpy(m_struLoginInfo[m_dwUnitNum].sDeviceAddress, m_csNvrIpv4, m_csNvrIpv4.GetLength());
    strncpy(m_struLoginInfo[m_dwUnitNum].sPassword, m_csPassword, m_csPassword.GetLength());
    strncpy(m_struLoginInfo[m_dwUnitNum].sUserName, m_csUsername, m_csUsername.GetLength());
    m_struLoginInfo[m_dwUnitNum].wPort = atoi(m_csPort);
    m_dwUnitNum++;

    CXmlBase xmlOutput;

    for (int i = 0; i < m_dwUnitNum;i++)
    {
        LONG lUserId = GetUserID(i);
        if (lUserId >= 0)
        {
            if (!NET_DVR_STDXMLConfig(lUserId, &m_struInput, &m_struOuput))
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szUrl);
            }
            else
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);
            }
            CString strTmp;
            xmlOutput.Parse((char *)m_struOuput.lpStatusBuffer);
            xmlOutput.SetRoot();

            char szLan[64] = { 0 };
            sprintf(szLan, "\r\nDevice[%d:%s]\r\n", i, m_struLoginInfo[i].sDeviceAddress);

            strTmp = xmlOutput.GetChildren().c_str();
            strTmp.Replace("\n", "\r\n");

            m_csLastXml.Append(szLan);
            m_csLastXml.Append(strTmp);
        }
        else
        {
            char szLan[64] = { 0 };
            sprintf(szLan, "\r\nDevice[%d:%s]\r\nlogin failed", i, m_struLoginInfo[i].sDeviceAddress);
            m_csLastXml.Append(szLan);
        }
    }

    if (m_struInput.lpInBuffer != NULL)
    {
        delete[] (char*)m_struInput.lpInBuffer;
        m_struInput.lpInBuffer = NULL;
    }

    UpdateData(FALSE);
}


LONG CDlgCluster::GetUserID(int i)
{
    NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = { 0 };
    m_struLoginInfo[i].bUseAsynLogin = false;
    LONG lUserID = NET_DVR_Login_V40(&m_struLoginInfo[i], &struDeviceInfoV40);
    if (lUserID < 0)
    {
        char szLan[1024] = { 0 };
        sprintf(szLan, "%s[%d]", "NET_DVR_Login_V30", i);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_Login_V30");
        return -1;
    }

    return lUserID;
}

void CDlgCluster::OnBnClickedButtonGetDeviceInfo()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    Initbuff();
    char szUrl[256] = { 0 };
    char szLan[64] = { 0 };

    sprintf(szUrl, "GET /ISAPI/ContentMgmt/Cluster/device\r\n");
    m_struInput.lpRequestUrl = szUrl;
    m_struInput.dwRequestUrlLen = strlen(szUrl);
    if (m_bEnableEncrypt)
    {
        m_struInput.byForceEncrpt = 1;
    }
    
    m_struOuput.lpOutBuffer = m_pBuffer;
    m_struOuput.dwOutBufferSize = m_dwBufferLen;

    if (!NET_DVR_STDXMLConfig(m_lUserID, &m_struInput, &m_struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szUrl);
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);

    CXmlBase xmlOutput;
    xmlOutput.Parse((char *)m_struOuput.lpOutBuffer);
    xmlOutput.SetRoot();
    m_csLastXml = xmlOutput.GetChildren().c_str();
    m_csLastXml.Replace("\n", "\r\n");
    UpdateData(FALSE);
}


void CDlgCluster::OnBnClickedBtnGetClusterStatus()
{
    UpdateData(TRUE);
    Initbuff();
    char szUrl[256] = { 0 };
    char szLan[64] = { 0 };

    sprintf(szUrl, "GET /ISAPI/ContentMgmt/Cluster/Status\r\n");
    m_struInput.lpRequestUrl = szUrl;
    m_struInput.dwRequestUrlLen = strlen(szUrl);
    if (m_bEnableEncrypt)
    {
        m_struInput.byForceEncrpt = 1;
    }

    m_struOuput.lpOutBuffer = m_pBuffer;
    m_struOuput.dwOutBufferSize = m_dwBufferLen;

    if (!NET_DVR_STDXMLConfig(m_lUserID, &m_struInput, &m_struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szUrl);
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);

    CXmlBase xmlOutput;
    xmlOutput.Parse((char *)m_struOuput.lpOutBuffer);
    xmlOutput.SetRoot();
    m_csLastXml = xmlOutput.GetChildren().c_str();
    m_csLastXml.Replace("\n", "\r\n");
    UpdateData(FALSE);
}
