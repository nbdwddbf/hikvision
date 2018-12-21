// DlgRecordHostVedioSwitchConfig.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgRecordHostVedioSwitchConfig.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"

// CDlgRecordHostVedioSwitchConfig 对话框

IMPLEMENT_DYNAMIC(CDlgRecordHostVedioSwitchConfig, CDialogEx)

CDlgRecordHostVedioSwitchConfig::CDlgRecordHostVedioSwitchConfig(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRecordHostVedioSwitchConfig::IDD, pParent)
    , m_enable(FALSE)
{

}

CDlgRecordHostVedioSwitchConfig::~CDlgRecordHostVedioSwitchConfig()
{
}

void CDlgRecordHostVedioSwitchConfig::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHECK_ENABLE, m_enable);
    DDX_Control(pDX, IDC_COMBO_EFFECTMODE, m_EffectModeCtrl);
}


BEGIN_MESSAGE_MAP(CDlgRecordHostVedioSwitchConfig, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_GET, &CDlgRecordHostVedioSwitchConfig::OnBnClickedBtnGet)
    ON_BN_CLICKED(IDC_BTN_SET, &CDlgRecordHostVedioSwitchConfig::OnBnClickedBtnSet)
END_MESSAGE_MAP()


// CDlgRecordHostVedioSwitchConfig 消息处理程序

BOOL CDlgRecordHostVedioSwitchConfig::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO: Add extra initialization here

    char szLan[64] = { 0 };
    g_StringLanType(szLan, "左上放大", "upperLeftZoomIn");
    m_EffectModeCtrl.InsertString(0, szLan);
    g_StringLanType(szLan, "右上放大", "upperRightZoomIn");
    m_EffectModeCtrl.InsertString(1, szLan);
    g_StringLanType(szLan, "左下放大", "lowerLeftZoomIn");
    m_EffectModeCtrl.InsertString(2, szLan);
    g_StringLanType(szLan, "右下放大", "lowerRightZoomIn");
    m_EffectModeCtrl.InsertString(3, szLan);
    g_StringLanType(szLan, "左边放大", "leftZoomIn");
    m_EffectModeCtrl.InsertString(4, szLan);
    g_StringLanType(szLan, "右边放大", "rightZoomIn");
    m_EffectModeCtrl.InsertString(5, szLan);
    g_StringLanType(szLan, "上边放大", "upperZoomIn");
    m_EffectModeCtrl.InsertString(6, szLan);
    g_StringLanType(szLan, "下边放大", "lowerZoomIn");
    m_EffectModeCtrl.InsertString(7, szLan);
    g_StringLanType(szLan, "中心放大", "centerZoomIn");
    m_EffectModeCtrl.InsertString(8, szLan);
    g_StringLanType(szLan, "左边中心放大", "leftCenterZoomIn");
    m_EffectModeCtrl.InsertString(9, szLan);
    g_StringLanType(szLan, "右边中心放大", "rightCenterZoomIn");
    m_EffectModeCtrl.InsertString(10, szLan);
    g_StringLanType(szLan, "上边中心放大", "upperCenterZoomIn");
    m_EffectModeCtrl.InsertString(11, szLan);
    g_StringLanType(szLan, "下边中心放大", "lowerCenterZoomIn");
    m_EffectModeCtrl.InsertString(12, szLan);
    m_EffectModeCtrl.SetCurSel(0);

    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRecordHostVedioSwitchConfig::OnBnClickedBtnGet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    struInput.lpRequestUrl = "GET /ISAPI/ContentMgmt/RecordingHost/VideoSwitchConfiguration\r\n";
    struInput.dwRequestUrlLen = strlen("GET /ISAPI/ContentMgmt/RecordingHost/VideoSwitchConfiguration\r\n");
    DWORD dwOutputLen = 1024 * 1024;
    char *pOutBuf = new char[dwOutputLen];
    memset(pOutBuf, 0, dwOutputLen);
    struOuput.lpOutBuffer = pOutBuf;
    struOuput.dwOutBufferSize = dwOutputLen;

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "GET /ISAPI/ContentMgmt/RecordingHost/VideoSwitchConfiguration\r\n");
        delete[]pOutBuf;
        pOutBuf = NULL;
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "GET /ISAPI/ContentMgmt/RecordingHost/VideoSwitchConfiguration\r\n");
    }

    CXmlBase xmlBase;
    xmlBase.Parse(pOutBuf);
    if (xmlBase.FindElem("VideoSwitchConfiguration") && xmlBase.IntoElem())
    {
        if (xmlBase.FindElem("enable"))
        {
            if (xmlBase.GetData().compare("true") == 0)
            {
                m_enable = TRUE;
            }
            else if (xmlBase.GetData().compare("false") == 0)
            {
                m_enable = FALSE;
            }
        }
        if (xmlBase.FindElem("effectMode"))
        {
            string sztemp = xmlBase.GetData();
            m_EffectModeCtrl.SetCurSel(atoi(sztemp.c_str()));
        }
    }
    UpdateData(FALSE);

    if (pOutBuf!=NULL)
    {
        delete[]pOutBuf;
        pOutBuf = NULL;
    }
    return;
}

BOOL CDlgRecordHostVedioSwitchConfig::CreateVideoSwitchConfiguration(char* pBuf, DWORD dwBufLen, int &dwRet)
{
    CXmlBase xmlBase;
    xmlBase.CreateRoot("VideoSwitchConfiguration");
    xmlBase.SetAttribute("version", "2.0");
    if (m_enable)
    {
        xmlBase.AddNode("enable", "true");
    }
    else
    {
        xmlBase.AddNode("enable", "false");
    }
    xmlBase.OutOfElem();
    char sztemp[10] = { 0 };
    sprintf(sztemp, "%d", m_EffectModeCtrl.GetCurSel());
    xmlBase.AddNode("effectMode", sztemp);

    xmlBase.OutOfElem();

    return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}

void CDlgRecordHostVedioSwitchConfig::OnBnClickedBtnSet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    DWORD dwBufLen = 10 * 1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);
    int dwXmlLen = 0;
    if (!CreateVideoSwitchConfiguration(pBuf, dwBufLen, dwXmlLen))
    {
        delete[]pBuf;
        pBuf = NULL;
        return;
    }

    char szUrl[256] = { 0 };
    sprintf(szUrl, "PUT /ISAPI/ContentMgmt/RecordingHost/VideoSwitchConfiguration\r\n");
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
