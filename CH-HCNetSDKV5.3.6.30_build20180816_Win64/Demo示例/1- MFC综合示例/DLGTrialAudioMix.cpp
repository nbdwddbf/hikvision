// DLGTrialAudioMix.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DLGTrialAudioMix.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"

// CDLGTrialAudioMix 对话框

IMPLEMENT_DYNAMIC(CDLGTrialAudioMix, CDialogEx)

CDLGTrialAudioMix::CDLGTrialAudioMix(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDLGTrialAudioMix::IDD, pParent)
    , m_AudioMixInfo(_T(""))
{

}

CDLGTrialAudioMix::~CDLGTrialAudioMix()
{
}

void CDLGTrialAudioMix::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_AUDIOMIX_ID, m_AudioMixID);
    DDX_Text(pDX, IDC_EDIT_AUDIOMIX_INFO, m_AudioMixInfo);
    DDX_Control(pDX, IDC_COMBO_SERIALPORT_ID, m_SerialPortID);
}


BEGIN_MESSAGE_MAP(CDLGTrialAudioMix, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_GET_SINGLE_AUDIOMIXCFG, &CDLGTrialAudioMix::OnBnClickedBtnGetSingleAudiomixcfg)
    ON_BN_CLICKED(IDC_BTN_SET_SINGLE_AUDIOMIXCFG, &CDLGTrialAudioMix::OnBnClickedBtnSetSingleAudiomixcfg)
    ON_BN_CLICKED(IDC_BTN_GET_AUDIOMIXCFG, &CDLGTrialAudioMix::OnBnClickedBtnGetAudiomixcfg)
    ON_BN_CLICKED(IDC_BTN_SET_AUDIOMIXCFG, &CDLGTrialAudioMix::OnBnClickedBtnSetAudiomixcfg)
    ON_BN_CLICKED(IDC_BTN_GET_SINGLE_SERIALPORT_CFG, &CDLGTrialAudioMix::OnBnClickedBtnGetSingleSerialportCfg)
    ON_BN_CLICKED(IDC_BTN_SET_SINGLE_SERIALPORT_CFG, &CDLGTrialAudioMix::OnBnClickedBtnSetSingleSerialportCfg)
    ON_BN_CLICKED(IDC_BTN_GET_SERIALPORT_CFG, &CDLGTrialAudioMix::OnBnClickedBtnGetSerialportCfg)
    ON_BN_CLICKED(IDC_BTN_SET_SERIALPORT_CFG, &CDLGTrialAudioMix::OnBnClickedBtnSetSerialportCfg)
END_MESSAGE_MAP()


// CDLGTrialAudioMix 消息处理程序


void CDLGTrialAudioMix::OnBnClickedBtnGetSingleAudiomixcfg()
{
    UpdateData(TRUE);
    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);

    char szUrl[256] = { 0 };
    sprintf(szUrl, "GET /ISAPI/System/Audio/Mixing/%d\r\n", m_AudioMixID.GetCurSel() + 1);
    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);

    DWORD dwOutputLen = 1024 * 1024;
    char *pOutBuf = new char[dwOutputLen];
    memset(pOutBuf, 0, dwOutputLen);
    struOuput.lpOutBuffer = pOutBuf;
    struOuput.dwOutBufferSize = dwOutputLen;

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "GET /ISAPI/System/Audio/Mixing/<ID>\r\n");
        delete[]pOutBuf;
        pOutBuf = NULL;
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "GET /ISAPI/System/Audio/Mixing/<ID>\r\n");
        CXmlBase xmlBase;
        xmlBase.Parse(pOutBuf);
        xmlBase.SetRoot();
        m_AudioMixInfo = xmlBase.GetChildren().c_str();
        m_AudioMixInfo.Replace("\n", "\r\n");
    }

    UpdateData(FALSE);

    if (pOutBuf != NULL)
    {
        delete[]pOutBuf;
        pOutBuf = NULL;
    }

    return;
}


void CDLGTrialAudioMix::OnBnClickedBtnSetSingleAudiomixcfg()
{
    UpdateData(TRUE);
    DWORD dwBufLen = 10 * 1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);

    CString temp = m_AudioMixInfo;
    temp.Replace("\r\n", "\n");
    sprintf(pBuf, temp, sizeof(temp));
    char szUrl[256] = { 0 };
    sprintf(szUrl, "PUT /ISAPI/System/Audio/Mixing/%d\r\n", m_AudioMixID.GetCurSel()+1);

    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    struInput.lpInBuffer = pBuf;
    struInput.dwInBufferSize = dwBufLen;
    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, szUrl);
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, szUrl);
    }
    UpdateData(FALSE);
    if (pBuf != NULL)
    {
        delete[]pBuf;
        pBuf = NULL;
    }
}


void CDLGTrialAudioMix::OnBnClickedBtnGetAudiomixcfg()
{
    UpdateData(TRUE);
    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    char szUrl[256] = { 0 };
    sprintf(szUrl, "GET /ISAPI/System/Audio/Mixing\r\n");
    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    DWORD dwOutputLen = 1024 * 1024;
    char *pOutBuf = new char[dwOutputLen];
    memset(pOutBuf, 0, dwOutputLen);
    struOuput.lpOutBuffer = pOutBuf;
    struOuput.dwOutBufferSize = dwOutputLen;

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "GET /ISAPI/System/Audio/Mixing\r\n");
        delete[]pOutBuf;
        pOutBuf = NULL;
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "GET /ISAPI/System/Audio/Mixing\r\n");
        CXmlBase xmlBase;
        xmlBase.Parse(pOutBuf);
        xmlBase.SetRoot();
        m_AudioMixInfo = xmlBase.GetChildren().c_str();
        m_AudioMixInfo.Replace("\n", "\r\n");
    }

    UpdateData(FALSE);

    if (pOutBuf != NULL)
    {
        delete[]pOutBuf;
        pOutBuf = NULL;
    }

    return;
}


void CDLGTrialAudioMix::OnBnClickedBtnSetAudiomixcfg()
{
    UpdateData(TRUE);
    DWORD dwBufLen = 10 * 1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);

    CString temp = m_AudioMixInfo;
    temp.Replace("\r\n", "\n");
    sprintf(pBuf, temp, sizeof(temp));

    char szUrl[256] = { 0 };
    sprintf(szUrl, "PUT /ISAPI/System/Audio/Mixing\r\n");

    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    struInput.lpInBuffer = pBuf;
    struInput.dwInBufferSize = dwBufLen;
    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, szUrl);
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, szUrl);
    }
    UpdateData(FALSE);
    if (pBuf != NULL)
    {
        delete[]pBuf;
        pBuf = NULL;
    }
}


void CDLGTrialAudioMix::OnBnClickedBtnGetSingleSerialportCfg()
{
    UpdateData(TRUE);
    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);

    char szUrl[256] = { 0 };
    sprintf(szUrl, "GET /ISAPI/System/Serial/ports/%d\r\n", m_SerialPortID.GetCurSel() + 1);
    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);

    DWORD dwOutputLen = 1024 * 1024;
    char *pOutBuf = new char[dwOutputLen];
    memset(pOutBuf, 0, dwOutputLen);
    struOuput.lpOutBuffer = pOutBuf;
    struOuput.dwOutBufferSize = dwOutputLen;

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "GET /ISAPI/System/Serial/ports/<ID>\r\n");
        delete[]pOutBuf;
        pOutBuf = NULL;
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "GET /ISAPI/System/Serial/ports/<ID>\r\n");
        CXmlBase xmlBase;
        xmlBase.Parse(pOutBuf);
        xmlBase.SetRoot();
        m_AudioMixInfo = xmlBase.GetChildren().c_str();
        m_AudioMixInfo.Replace("\n", "\r\n");
    }

    UpdateData(FALSE);

    if (pOutBuf != NULL)
    {
        delete[]pOutBuf;
        pOutBuf = NULL;
    }

    return;
}


void CDLGTrialAudioMix::OnBnClickedBtnSetSingleSerialportCfg()
{
    UpdateData(TRUE);
    DWORD dwBufLen = 10 * 1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);

    CString temp = m_AudioMixInfo;
    temp.Replace("\r\n", "\n");
    sprintf(pBuf, temp, sizeof(temp));

    char szUrl[256] = { 0 };
    sprintf(szUrl, "PUT /ISAPI/System/Serial/ports/%d\r\n", m_SerialPortID.GetCurSel() + 1);

    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    struInput.lpInBuffer = pBuf;
    struInput.dwInBufferSize = dwBufLen;
    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, szUrl);
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, szUrl);
    }
    UpdateData(FALSE);
    if (pBuf != NULL)
    {
        delete[]pBuf;
        pBuf = NULL;
    }
}


void CDLGTrialAudioMix::OnBnClickedBtnGetSerialportCfg()
{
    UpdateData(TRUE);
    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);

    char szUrl[256] = { 0 };
    sprintf(szUrl, "GET /ISAPI/System/Serial/ports\r\n");
    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);

    DWORD dwOutputLen = 1024 * 1024;
    char *pOutBuf = new char[dwOutputLen];
    memset(pOutBuf, 0, dwOutputLen);
    struOuput.lpOutBuffer = pOutBuf;
    struOuput.dwOutBufferSize = dwOutputLen;

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "GET /ISAPI/System/Serial/ports\r\n");
        delete[]pOutBuf;
        pOutBuf = NULL;
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "GET /ISAPI/System/Serial/ports\r\n");
        CXmlBase xmlBase;
        xmlBase.Parse(pOutBuf);
        xmlBase.SetRoot();
        m_AudioMixInfo = xmlBase.GetChildren().c_str();
        m_AudioMixInfo.Replace("\n", "\r\n");
    }

    UpdateData(FALSE);

    if (pOutBuf != NULL)
    {
        delete[]pOutBuf;
        pOutBuf = NULL;
    }

    return;
}


void CDLGTrialAudioMix::OnBnClickedBtnSetSerialportCfg()
{
    UpdateData(TRUE);
    DWORD dwBufLen = 10 * 1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);

    CString temp = m_AudioMixInfo;
    temp.Replace("\r\n", "\n");
    sprintf(pBuf, temp, sizeof(temp));

    char szUrl[256] = { 0 };
    sprintf(szUrl, "PUT /ISAPI/System/Serial/ports\r\n");

    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    struInput.lpInBuffer = pBuf;
    struInput.dwInBufferSize = dwBufLen;
    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, szUrl);
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, szUrl);
    }
    UpdateData(FALSE);
    if (pBuf != NULL)
    {
        delete[]pBuf;
        pBuf = NULL;
    }
}
