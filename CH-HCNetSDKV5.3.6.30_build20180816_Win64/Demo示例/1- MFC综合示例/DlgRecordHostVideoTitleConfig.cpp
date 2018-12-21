// DlgRecordHostVideoTitleConfig.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgRecordHostVideoTitleConfig.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"

// CDlgRecordHostVideoTitleConfig 对话框

IMPLEMENT_DYNAMIC(CDlgRecordHostVideoTitleConfig, CDialogEx)

CDlgRecordHostVideoTitleConfig::CDlgRecordHostVideoTitleConfig(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRecordHostVideoTitleConfig::IDD, pParent)
    , m_bEnable(FALSE)
    , m_ibackgroundImageIndex(0)
    , m_idisplayTimeLength(0)
    , m_bEnableTrailer(FALSE)
    , m_iImageIndexTrailer(0)
    , m_iTimeLengthTrailer(0)
{

}

CDlgRecordHostVideoTitleConfig::~CDlgRecordHostVideoTitleConfig()
{
}

void CDlgRecordHostVideoTitleConfig::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
    DDX_Text(pDX, IDC_EDIT_IMAGEINDEX, m_ibackgroundImageIndex);
    DDX_Text(pDX, IDC_EDIT_TIMELENGTH, m_idisplayTimeLength);
    DDX_Check(pDX, IDC_CHECK_ENABLE_TRAILER, m_bEnableTrailer);
    DDX_Text(pDX, IDC_EDIT_IMAGEINDEX_TRAILER, m_iImageIndexTrailer);
    DDX_Text(pDX, IDC_EDIT_TIMELENGTH_TRAILER, m_iTimeLengthTrailer);
}


BEGIN_MESSAGE_MAP(CDlgRecordHostVideoTitleConfig, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_GET, &CDlgRecordHostVideoTitleConfig::OnBnClickedBtnGet)
    ON_BN_CLICKED(IDC_BTN_SET, &CDlgRecordHostVideoTitleConfig::OnBnClickedBtnSet)
    ON_BN_CLICKED(IDC_BTN_GET_TRAILER, &CDlgRecordHostVideoTitleConfig::OnBnClickedBtnGetTrailer)
    ON_BN_CLICKED(IDC_BTN_SET_TRAILER, &CDlgRecordHostVideoTitleConfig::OnBnClickedBtnSetTrailer)
END_MESSAGE_MAP()


// CDlgRecordHostVideoTitleConfig 消息处理程序


void CDlgRecordHostVideoTitleConfig::OnBnClickedBtnGet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    struInput.lpRequestUrl = "GET /ISAPI/ContentMgmt/RecordingHost/VideoTitleConfiguration\r\n";
    struInput.dwRequestUrlLen = strlen("GET /ISAPI/ContentMgmt/RecordingHost/VideoTitleConfiguration\r\n");
    DWORD dwOutputLen = 1024 * 1024;
    char *pOutBuf = new char[dwOutputLen];
    memset(pOutBuf, 0, dwOutputLen);
    struOuput.lpOutBuffer = pOutBuf;
    struOuput.dwOutBufferSize = dwOutputLen;

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "GET /ISAPI/ContentMgmt/RecordingHost/VideoTitleConfiguration\r\n");
        delete[]pOutBuf;
        pOutBuf = NULL;
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "GET /ISAPI/ContentMgmt/RecordingHost/VideoTitleConfiguration\r\n");
    }

    CXmlBase xmlBase;
    xmlBase.Parse(pOutBuf);
    if (xmlBase.FindElem("VideoTitleConfiguration") && xmlBase.IntoElem())
    {
        if (xmlBase.FindElem("enable"))
        {
            if (xmlBase.GetData().compare("true") == 0)
            {
                m_bEnable = TRUE;
            }
            else if (xmlBase.GetData().compare("false") == 0)
            {
                m_bEnable = FALSE;
            }
        }
        if (xmlBase.FindElem("backgroundImageIndex"))
        {
            string sztemp = xmlBase.GetData();
            m_ibackgroundImageIndex = atoi(sztemp.c_str());
        }
        if (xmlBase.FindElem("displayTimeLength"))
        {
            string sztemp = xmlBase.GetData();
            m_idisplayTimeLength = atoi(sztemp.c_str());
        }
    }
    UpdateData(FALSE);

    if (pOutBuf != NULL)
    {
        delete[]pOutBuf;
        pOutBuf = NULL;
    }

    return;
}

BOOL CDlgRecordHostVideoTitleConfig::CreateVideoTitleConfiguration(char* pBuf, DWORD dwBufLen, int &dwRet)
{
    CXmlBase xmlBase;
    xmlBase.CreateRoot("VideoTitleConfiguration");
    xmlBase.SetAttribute("version", "2.0");
    if (m_bEnable)
    {
        xmlBase.AddNode("enable", "true");
    }
    else
    {
        xmlBase.AddNode("enable", "false");
    }
    xmlBase.OutOfElem();
    char sztemp[10] = { 0 };
    sprintf(sztemp, "%d", m_ibackgroundImageIndex);
    xmlBase.AddNode("backgroundImageIndex", sztemp);
    xmlBase.OutOfElem();
    sprintf(sztemp, "%d", m_idisplayTimeLength);
    xmlBase.AddNode("displayTimeLength", sztemp);
    
    xmlBase.OutOfElem();

    return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}
void CDlgRecordHostVideoTitleConfig::OnBnClickedBtnSet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    DWORD dwBufLen = 10 * 1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);
    int dwXmlLen = 0;
    if (!CreateVideoTitleConfiguration(pBuf, dwBufLen, dwXmlLen))
    {
        delete[]pBuf;
        pBuf = NULL;
        return;
    }

    char szUrl[256] = { 0 };
    sprintf(szUrl, "PUT /ISAPI/ContentMgmt/RecordingHost/VideoTitleConfiguration\r\n");
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
    UpdateData(FALSE);
    if (pBuf != NULL)
    {
        delete[]pBuf;
        pBuf = NULL;
    }
}


void CDlgRecordHostVideoTitleConfig::OnBnClickedBtnGetTrailer()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    struInput.lpRequestUrl = "GET /ISAPI/ContentMgmt/RecordingHost/VideoTrailerConfiguration\r\n";
    struInput.dwRequestUrlLen = strlen("GET /ISAPI/ContentMgmt/RecordingHost/VideoTrailerConfiguration\r\n");
    DWORD dwOutputLen = 1024 * 1024;
    char *pOutBuf = new char[dwOutputLen];
    memset(pOutBuf, 0, dwOutputLen);
    struOuput.lpOutBuffer = pOutBuf;
    struOuput.dwOutBufferSize = dwOutputLen;

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "GET /ISAPI/ContentMgmt/RecordingHost/VideoTrailerConfiguration\r\n");
        delete[]pOutBuf;
        pOutBuf = NULL;
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "GET /ISAPI/ContentMgmt/RecordingHost/VideoTrailerConfiguration\r\n");
    }

    CXmlBase xmlBase;
    xmlBase.Parse(pOutBuf);
    if (xmlBase.FindElem("VideoTrailerConfiguration") && xmlBase.IntoElem())
    {
        if (xmlBase.FindElem("enable"))
        {
            if (xmlBase.GetData().compare("true") == 0)
            {
                m_bEnableTrailer = TRUE;
            }
            else if (xmlBase.GetData().compare("false") == 0)
            {
                m_bEnableTrailer = FALSE;
            }
        }
        if (xmlBase.FindElem("backgroundImageIndex"))
        {
            string sztemp = xmlBase.GetData();
            m_iImageIndexTrailer = atoi(sztemp.c_str());
        }
        if (xmlBase.FindElem("displayTimeLength"))
        {
            string sztemp = xmlBase.GetData();
            m_iTimeLengthTrailer = atoi(sztemp.c_str());
        }
    }
    UpdateData(FALSE);

    if (pOutBuf != NULL)
    {
        delete[]pOutBuf;
        pOutBuf = NULL;
    }

    return;
}

BOOL CDlgRecordHostVideoTitleConfig::CreateVideoTrailerConfiguration(char* pBuf, DWORD dwBufLen, int &dwRet)
{
    CXmlBase xmlBase;
    xmlBase.CreateRoot("VideoTrailerConfiguration");
    xmlBase.SetAttribute("version", "2.0");
    if (m_bEnableTrailer)
    {
        xmlBase.AddNode("enable", "true");
    }
    else
    {
        xmlBase.AddNode("enable", "false");
    }
    xmlBase.OutOfElem();
    char sztemp[10] = { 0 };
    sprintf(sztemp, "%d", m_iImageIndexTrailer);
    xmlBase.AddNode("backgroundImageIndex", sztemp);
    xmlBase.OutOfElem();
    sprintf(sztemp, "%d", m_iTimeLengthTrailer);
    xmlBase.AddNode("displayTimeLength", sztemp);

    xmlBase.OutOfElem();

    return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}
void CDlgRecordHostVideoTitleConfig::OnBnClickedBtnSetTrailer()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    DWORD dwBufLen = 10 * 1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);
    int dwXmlLen = 0;
    if (!CreateVideoTrailerConfiguration(pBuf, dwBufLen, dwXmlLen))
    {
        delete[]pBuf;
        pBuf = NULL;
        return;
    }

    char szUrl[256] = { 0 };
    sprintf(szUrl, "PUT /ISAPI/ContentMgmt/RecordingHost/VideoTrailerConfiguration\r\n");
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
    UpdateData(FALSE);
    if (pBuf != NULL)
    {
        delete[]pBuf;
        pBuf = NULL;
    }
}
