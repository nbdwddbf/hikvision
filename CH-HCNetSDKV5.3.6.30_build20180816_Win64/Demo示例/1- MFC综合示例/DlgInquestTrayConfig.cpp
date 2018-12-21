// DlgInquestTrayConfig.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgInquestTrayConfig.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"

// CDlgInquestTrayConfig 对话框

IMPLEMENT_DYNAMIC(CDlgInquestTrayConfig, CDialogEx)

CDlgInquestTrayConfig::CDlgInquestTrayConfig(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgInquestTrayConfig::IDD, pParent)
    , m_lUserID(-1)
    , m_iDeviceIndex(-1)
    , m_strTrayNo(_T(""))
    , m_bIsAbnormal(FALSE)
{

}

CDlgInquestTrayConfig::~CDlgInquestTrayConfig()
{
}

void CDlgInquestTrayConfig::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_TRAY_NO, m_strTrayNo);
    DDX_Check(pDX, IDC_CHK_IS_ABNORMAL, m_bIsAbnormal);
    DDX_Control(pDX, IDC_COMBO_TRAY_STATUS, m_comboTrayStatus);
}


BEGIN_MESSAGE_MAP(CDlgInquestTrayConfig, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_GET, &CDlgInquestTrayConfig::OnBnClickedButtonGet)
    ON_BN_CLICKED(IDC_BUTTON_SET, &CDlgInquestTrayConfig::OnBnClickedButtonSet)
END_MESSAGE_MAP()


// CDlgInquestTrayConfig 消息处理程序

BOOL CDlgInquestTrayConfig::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    GetDlgItem(IDC_CHK_IS_ABNORMAL)->EnableWindow(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}

BOOL CDlgInquestTrayConfig::CreateTrayConfigXML(char* pBuf, DWORD dwBufLen, int &dwRet)
{
    CString strParam = _T("");
    CXmlBase xmlBase;
    xmlBase.CreateRoot("TrayConfiguration");
    xmlBase.SetAttribute("version", "2.0");
    if (m_bIsAbnormal)
    {
        xmlBase.AddNode("isAbnormal", "true");
    }
    else
    {
        xmlBase.AddNode("isAbnormal", "false");
    }
    xmlBase.OutOfElem();
    if (m_comboTrayStatus.GetCurSel() == 0)
    {
        xmlBase.AddNode("trayStatus", "open");
    }
    else if (m_comboTrayStatus.GetCurSel() == 1)
    {
        xmlBase.AddNode("trayStatus", "close");
    }
    xmlBase.OutOfElem();

    return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}

void CDlgInquestTrayConfig::OnBnClickedButtonGet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    char szUrl[256] = { 0 };
    sprintf(szUrl, "GET /ISAPI/ContentMgmt/Trial/TrayConfiguration/%s\r\n", m_strTrayNo);

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
        delete[]pOutBuf;
        pOutBuf = NULL;
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);
    }

    BOOL bRet = FALSE;
    CXmlBase xmlBase;
    xmlBase.Parse(pOutBuf);
    if (xmlBase.FindElem("TrayConfiguration") && xmlBase.IntoElem())
    {
        if (xmlBase.FindElem("isAbnormal"))
        {
            if (xmlBase.GetData().compare("true") == 0)
            {
                m_bIsAbnormal = TRUE;
            }
            else if (xmlBase.GetData().compare("false") == 0)
            {
                m_bIsAbnormal = FALSE;
            }
        }

        if (xmlBase.FindElem("trayStatus"))
        {
            if (xmlBase.GetData().compare("open") == 0)
            {
                m_comboTrayStatus.SetCurSel(0);
            }
            else if (xmlBase.GetData().compare("close") == 0)
            {
                m_comboTrayStatus.SetCurSel(1);
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


void CDlgInquestTrayConfig::OnBnClickedButtonSet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    DWORD dwBufLen = 10 * 1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);
    int dwXmlLen = 0;
    if (!CreateTrayConfigXML(pBuf, dwBufLen, dwXmlLen))
    {
        delete[]pBuf;
        pBuf = NULL;
        return;
    }

    char szUrl[256] = { 0 };
    sprintf(szUrl, "PUT /ISAPI/ContentMgmt/Trial/TrayConfiguration/%s\r\n", m_strTrayNo);
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
