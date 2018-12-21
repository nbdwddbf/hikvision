// DlgTerminalGkCfg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgTerminalGkCfg.h"
#include "afxdialogex.h"
#include "XMLParamsConvert.h"




// CDlgTerminalGkCfg 对话框

IMPLEMENT_DYNAMIC(CDlgTerminalGkCfg, CDialogEx)

CDlgTerminalGkCfg::CDlgTerminalGkCfg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTerminalGkCfg::IDD, pParent)
    , m_bEnable(FALSE)
    , m_szIPV4(_T(""))
    , m_szIPV6(_T(""))
    , m_wPort(0)
    , m_szName(_T(""))
    , m_bStatus(FALSE)
    , m_byBuildGk(FALSE)
    , m_csPwd(_T(""))
{

}

CDlgTerminalGkCfg::~CDlgTerminalGkCfg()
{
}

void CDlgTerminalGkCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_IPTYPE, m_cmbIpType);
    DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
    DDX_Text(pDX, IDC_EDIT_V4, m_szIPV4);
    DDX_Text(pDX, IDC_EDIT_V6, m_szIPV6);
    DDX_Text(pDX, IDC_EDIT_PORT, m_wPort);
    DDX_Text(pDX, IDC_EDIT6, m_szName);
    DDX_Control(pDX, IDC_COMBO_TYPE, m_cmbType);
    DDX_Check(pDX, IDC_CHECK_STATUS, m_bStatus);
    DDX_Check(pDX, IDC_CHECK_BUILD, m_byBuildGk);
    DDX_Text(pDX, IDC_EDIT_PWD, m_csPwd);
}


BEGIN_MESSAGE_MAP(CDlgTerminalGkCfg, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_GET, &CDlgTerminalGkCfg::OnBnClickedBtnGet)
    ON_BN_CLICKED(IDC_BTN_SET, &CDlgTerminalGkCfg::OnBnClickedBtnSet)
END_MESSAGE_MAP()


// CDlgTerminalGkCfg 消息处理程序


void CDlgTerminalGkCfg::OnBnClickedBtnGet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    int nTypeSel = m_cmbType.GetCurSel();
    if (nTypeSel == CB_ERR)
    {
        return;
    }

    NET_DVR_TERMINAL_GK_CFG struGkCfg = { 0 };
    struGkCfg.dwSize = sizeof(struGkCfg);

    if (nTypeSel == 0)
    {
    
        NET_DVR_STD_CONFIG struConfig = { 0 };
        struConfig.lpOutBuffer = &struGkCfg;
        struConfig.dwOutSize = sizeof(struGkCfg);
        if (!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_TERMINAL_GK_CFG, &struConfig))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_TERMINAL_GK_CFG");
            return;
        }
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_TERMINAL_GK_CFG");
    }
    else if (nTypeSel == 1)
    {
        NET_DVR_XML_CONFIG_INPUT struInputParam = { 0 };
        struInputParam.dwSize = sizeof(struInputParam);
        struInputParam.lpRequestUrl = "GET /ISAPI/VCS/mcu/mcuGkCfg";
        struInputParam.dwRequestUrlLen = strlen("GET /ISAPI/VCS/mcu/mcuGkCfg");

        char szStatusBuff[1024] = { 0 };
        char *szOutputXmlBuffer = new char[MAX_LEN_XML]; 
        memset(szOutputXmlBuffer, 0, MAX_LEN_XML);
        NET_DVR_XML_CONFIG_OUTPUT struOutputParam = { 0 };
        struOutputParam.dwSize = sizeof(struOutputParam);
        struOutputParam.lpOutBuffer = szOutputXmlBuffer;
        struOutputParam.dwOutBufferSize = MAX_LEN_XML;
        struOutputParam.lpStatusBuffer = szStatusBuff;
        struOutputParam.dwStatusSize = sizeof(szStatusBuff);

        if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
            if (szOutputXmlBuffer != NULL)
            {
                delete[] szOutputXmlBuffer;
                szOutputXmlBuffer = NULL;
            }
            return;
        }
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");

        memset(&struGkCfg, 0, sizeof(struGkCfg));
        struGkCfg.dwSize = sizeof(struGkCfg);
        if (!ConvertGkCfgXmlToStru(szOutputXmlBuffer, &struGkCfg))
        {
            if (szOutputXmlBuffer != NULL)
            {
                delete[] szOutputXmlBuffer;
                szOutputXmlBuffer = NULL;
            }
        }
        if (szOutputXmlBuffer != NULL)
        {
            delete[] szOutputXmlBuffer;
            szOutputXmlBuffer = NULL;
        }
    }

    m_bEnable = struGkCfg.byEnable;
    char szIPV6[128] = { 0 };
    memcpy(szIPV6, struGkCfg.struGKIP.byIPv6, sizeof(struGkCfg.struGKIP.byIPv6));
    if (strcmp(struGkCfg.struGKIP.sIpV4, "") != 0 && strcmp(szIPV6, "") != 0)
    {
        m_szIPV4.Format("%s", struGkCfg.struGKIP.sIpV4);
        m_szIPV6.Format("%s", struGkCfg.struGKIP.byIPv6);
        m_cmbIpType.SetCurSel(m_cmbIpType.FindString(-1, "dual"));
    }
    else if(strcmp(struGkCfg.struGKIP.sIpV4, "") != 0)
    {
        m_szIPV4.Format("%s", struGkCfg.struGKIP.sIpV4);
        m_cmbIpType.SetCurSel(m_cmbIpType.FindString(-1, "IPV4"));
    }
    else if (strcmp(szIPV6, "") != 0)
    {
        m_szIPV6.Format("%s", struGkCfg.struGKIP.byIPv6);
        m_cmbIpType.SetCurSel(m_cmbIpType.FindString(-1, "IPV6"));
    }
    m_wPort = struGkCfg.wGKPort;
    m_szName.Format("%s", struGkCfg.byRegisterName);
    m_csPwd.Format("%s", struGkCfg.byPassword);
    m_bStatus = struGkCfg.byRegisterState;
    UpdateData(FALSE);
}


void CDlgTerminalGkCfg::OnBnClickedBtnSet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    int nTypeSel = m_cmbType.GetCurSel();
    if (nTypeSel == CB_ERR)
    {
        return;
    }  

    char szIP[128] = { 0 };
    char szName[64] = { 0 };
    NET_DVR_TERMINAL_GK_CFG struGkCfg = { 0 };
    struGkCfg.dwSize = sizeof(struGkCfg);
    int nSel = m_cmbIpType.GetCurSel();
    if (nSel == CB_ERR)
    {
        return;
    }
    CString strIPType;
    m_cmbIpType.GetLBText(nSel, strIPType);
    if (strcmp(strIPType, "IPV4") == 0)
    {
        memcpy(struGkCfg.struGKIP.sIpV4, m_szIPV4, sizeof(struGkCfg.struGKIP.sIpV4));
    }
    else if (strcmp(strIPType, "IPV6") == 0)
    {
        memcpy(struGkCfg.struGKIP.byIPv6, m_szIPV6, sizeof(struGkCfg.struGKIP.byIPv6));
    }
    else if (strcmp(strIPType, "dual") == 0)
    {
        memcpy(struGkCfg.struGKIP.sIpV4, m_szIPV4, sizeof(struGkCfg.struGKIP.sIpV4));
        memcpy(struGkCfg.struGKIP.byIPv6, m_szIPV6, sizeof(struGkCfg.struGKIP.byIPv6));
    }
    struGkCfg.byEnable = m_bEnable;
    struGkCfg.wGKPort = m_wPort;
    memcpy(struGkCfg.byRegisterName, m_szName, strlen(m_szName));
    memcpy(struGkCfg.byPassword, m_csPwd, strlen(m_csPwd));
    if (nTypeSel == 0)
    {
        NET_DVR_STD_CONFIG struConfig = { 0 };
        struConfig.lpInBuffer = &struGkCfg;
        struConfig.dwInSize = sizeof(struGkCfg);
        if (!NET_DVR_SetSTDConfig(m_lUserID, NET_DVR_SET_TERMINAL_GK_CFG, &struConfig))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_TERMINAL_GK_CFG");
            return;
        }
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_TERMINAL_GK_CFG");
    }
    else if (nTypeSel == 1)
    {
        char *pInputBuff = NULL;
        DWORD dwInputSize = 0;
        if (!ConvertGkCfgStruToXml(&struGkCfg, &pInputBuff, dwInputSize))
        {
            return;
        }

        NET_DVR_XML_CONFIG_INPUT struInputParam = { 0 };
        struInputParam.dwSize = sizeof(struInputParam);
        struInputParam.lpRequestUrl = "PUT /ISAPI/VCS/mcu/mcuGkCfg";
        struInputParam.dwRequestUrlLen = strlen("PUT /ISAPI/VCS/mcu/mcuGkCfg");
        struInputParam.lpInBuffer = pInputBuff;
        struInputParam.dwInBufferSize = dwInputSize;

        char szStatusBuff[1024] = { 0 };
        NET_DVR_XML_CONFIG_OUTPUT struOutputParam = { 0 };
        struOutputParam.dwSize = sizeof(struOutputParam);
        struOutputParam.lpStatusBuffer = szStatusBuff;
        struOutputParam.dwStatusSize = sizeof(szStatusBuff);

        if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
            return;
        }
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");   
    }
    
}


BOOL CDlgTerminalGkCfg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
    m_cmbIpType.SetCurSel(0);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}

BOOL CDlgTerminalGkCfg::ConvertGkCfgXmlToStru(char *pXmlBuffer, NET_DVR_TERMINAL_GK_CFG *pStruct)
{
    if (pXmlBuffer == NULL || pStruct == NULL)
    {
        return FALSE;
    }
    if (pStruct->dwSize != sizeof(*pStruct))
    {
        return FALSE;
    }
    CXmlBase struXml;
    if (struXml.Parse(pXmlBuffer) == NULL)
    {
        return FALSE;
    }
    if (struXml.FindElem("GkConfig") && struXml.IntoElem())
    {
        if (!ConvertSingleNodeData(&pStruct->byEnable, struXml, "enabled", NODE_STRING_TO_BOOL))
        {
            return FALSE;
        }
        bool byBuild = false;
        if (!ConvertSingleNodeData(&byBuild, struXml, "buildInGk", NODE_STRING_TO_BOOL))
        {
            return FALSE;
        }
        m_byBuildGk = byBuild;
        if (struXml.FindElem("IpAddress") && struXml.IntoElem())
        {
            BYTE byIPVersion[8] = { 0 };
            if (!ConvertSingleNodeData( byIPVersion, struXml, "ipVersion", NODE_STRING_TO_ARRAY, sizeof(byIPVersion)))
            {
                return FALSE;
            }
            if (0 == strcmp((char*)byIPVersion, "v4"))
            {
                if (!ConvertSingleNodeData(pStruct->struGKIP.sIpV4, struXml, "ipAddress", NODE_STRING_TO_ARRAY, sizeof(pStruct->struGKIP.sIpV4)))
                {
                    return FALSE;
                }
            }
            else if (0 == strcmp((char*)byIPVersion, "v6"))
            {
                if (!ConvertSingleNodeData(pStruct->struGKIP.byIPv6, struXml, "ipv6Address", NODE_STRING_TO_ARRAY, sizeof(pStruct->struGKIP.byIPv6)))
                {
                    return FALSE;
                }
            }
            else if (0 == strcmp((char*)byIPVersion, "dual"))
            {
                if (!ConvertSingleNodeData( pStruct->struGKIP.sIpV4, struXml, "ipAddress", NODE_STRING_TO_ARRAY, sizeof(pStruct->struGKIP.sIpV4)))
                {
                    return FALSE;
                }
                if (!ConvertSingleNodeData(pStruct->struGKIP.byIPv6, struXml, "ipv6Address", NODE_STRING_TO_ARRAY, sizeof(pStruct->struGKIP.byIPv6)))
                {
                    return FALSE;
                }

            }
            struXml.OutOfElem();
        }
        if (!ConvertSingleNodeData( &pStruct->wGKPort, struXml, "gkPort", NODE_STRING_TO_WORD))
        {
            return FALSE;
        }
        if (!ConvertSingleNodeData( pStruct->byRegisterName, struXml, "registerName", NODE_STRING_TO_ARRAY, sizeof(pStruct->byRegisterName)))
        {
            return FALSE;
        }
        if (!ConvertSingleNodeData(&pStruct->byRegisterState, struXml, "registerState", NODE_STRING_TO_BOOL))
        {
            return FALSE;
        }
        
        struXml.OutOfElem();
    }
    return TRUE;

}
BOOL CDlgTerminalGkCfg::ConvertGkCfgStruToXml(NET_DVR_TERMINAL_GK_CFG*pStruct, char* *pXmlBuf, DWORD &dwInputSize)
{
    if (pStruct == NULL || pXmlBuf == NULL)
    {
        return FALSE;
    }
    if (pStruct->dwSize != sizeof(*pStruct))
    {
        return FALSE;
    }
    CXmlBase struXml;
    struXml.CreateRoot("GkConfig");
    struXml.SetAttribute("version", "2.0");
    if (!ConvertSingleNodeData(&pStruct->byEnable, struXml, "enabled", NODE_BOOL_TO_STRING))
    {
        return FALSE;
    }
    if (m_byBuildGk == TRUE)
    {
        if (!ConvertSingleNodeData(&m_byBuildGk, struXml, "buildInGk", NODE_BOOL_TO_STRING))
        {
            return FALSE;
        }
    }
    else
    {
        if (struXml.AddNode("IpAddress"))
        {
            char szIPV6[128] = { 0 };
            memcpy(szIPV6, pStruct->struGKIP.byIPv6, sizeof(pStruct->struGKIP.byIPv6));
            if (strcmp(pStruct->struGKIP.sIpV4, "") != 0 && strcmp(szIPV6, "") != 0)
            {
                if (!ConvertSingleNodeData((void*)"dual", struXml, "ipVersion", NODE_ARRAY_TO_STRING))
                {
                    return FALSE;
                }
                if (!ConvertSingleNodeData(&pStruct->struGKIP.sIpV4, struXml, "ipAddress", NODE_ARRAY_TO_STRING))
                {
                    return FALSE;
                }
                if (!ConvertSingleNodeData(&pStruct->struGKIP.byIPv6, struXml, "ipv6Address", NODE_ARRAY_TO_STRING))
                {
                    return FALSE;
                }
            }
            else if (strcmp(pStruct->struGKIP.sIpV4, "") != 0)
            {
                if (!ConvertSingleNodeData((void*)"v4", struXml, "ipVersion", NODE_ARRAY_TO_STRING))
                {
                    return FALSE;
                }
                if (!ConvertSingleNodeData(&pStruct->struGKIP.sIpV4, struXml, "ipAddress", NODE_ARRAY_TO_STRING))
                {
                    return FALSE;
                }
            }
            else if (strcmp(szIPV6, "") != 0)
            {
                if (!ConvertSingleNodeData((void*)"v6", struXml, "ipVersion", NODE_ARRAY_TO_STRING))
                {
                    return FALSE;
                }
                if (!ConvertSingleNodeData(&pStruct->struGKIP.byIPv6, struXml, "ipv6Address", NODE_ARRAY_TO_STRING))
                {
                    return FALSE;
                }
            }
            struXml.OutOfElem();
        }
        if (!ConvertSingleNodeData(&pStruct->wGKPort, struXml, "gkPort", NODE_WORD_TO_STRING))
        {
            return FALSE;
        }
    }
    if (!ConvertSingleNodeData( pStruct->byRegisterName, struXml, "registerName", NODE_ARRAY_TO_STRING, sizeof(pStruct->byRegisterName)))
    {
        return FALSE;
    }
//     if (!ConvertSingleNodeData(&pStruct->byRegisterState, struXml, "registerState", NODE_BOOL_TO_STRING))
//     {
//         return FALSE;
//     }
    
    if (!PrintXmlToNewBuffer(pXmlBuf, dwInputSize, struXml))
    {
        return FALSE;
    }
    return TRUE;
}
