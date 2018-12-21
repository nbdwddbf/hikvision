// DLGGetChannelInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DLGGetChannelInfo.h"
#include "afxdialogex.h"
#include "./xml/XmlBase.h"

// CDLGGetChannelInfo 对话框

IMPLEMENT_DYNAMIC(CDLGGetChannelInfo, CDialogEx)

CDLGGetChannelInfo::CDLGGetChannelInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDLGGetChannelInfo::IDD, pParent)
    , m_channelInfo(_T(""))
{

}

CDLGGetChannelInfo::~CDLGGetChannelInfo()
{
}

void CDLGGetChannelInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_CHANNNEL_INFO, m_channelInfo);
}


BEGIN_MESSAGE_MAP(CDLGGetChannelInfo, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_GET_SINGLE_CHANINFO, &CDLGGetChannelInfo::OnBnClickedBtnGetSingleChaninfo)
    ON_BN_CLICKED(IDC_BTN_GET_CHANINFO, &CDLGGetChannelInfo::OnBnClickedBtnGetChaninfo)
    ON_BN_CLICKED(IDC_BTN_GET_ONLINE_USERLIST, &CDLGGetChannelInfo::OnBnClickedBtnGetOnlineUserlist)
    ON_BN_CLICKED(IDC_BTN_GET_MUTEX_FUNCTION, &CDLGGetChannelInfo::OnBnClickedBtnGetMutexFunction)
END_MESSAGE_MAP()


// CDLGGetChannelInfo 消息处理程序


void CDLGGetChannelInfo::OnBnClickedBtnGetSingleChaninfo()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    NET_DVR_STD_CONFIG struCfg = { 0 };
    char *pszOutputBuffer = new (nothrow) char[4 * 1024];
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.byDataType = 1;
    struCfg.lpXmlBuffer = pszOutputBuffer;
    struCfg.dwXmlSize = 4 * 1024;
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;


    if (!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_SINGLE_CHANNELINFO, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SINGLE_CHANNELINFO");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SINGLE_CHANNELINFO");
        CXmlBase xmlBase;
        xmlBase.Parse(pszOutputBuffer);
        xmlBase.SetRoot();
        m_channelInfo = xmlBase.GetChildren().c_str();
        //	m_strDevAbility = m_pOutBuf;
        m_channelInfo.Replace("\n", "\r\n");
    }
    delete[] pszOutputBuffer;
    UpdateData(FALSE);
}


void CDLGGetChannelInfo::OnBnClickedBtnGetChaninfo()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    NET_DVR_STD_CONFIG struCfg = { 0 };
    char *pszOutputBuffer = new (nothrow) char[1024 * 1024];
    struCfg.lpCondBuffer = NULL;
    struCfg.dwCondSize = 0;
    struCfg.byDataType = 1;
    struCfg.lpXmlBuffer = pszOutputBuffer;
    struCfg.dwXmlSize = 1024 * 1024;
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if (!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_CHANNELINFO, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_CHANNELINFO");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_CHANNELINFO");
        CXmlBase xmlBase;
        xmlBase.Parse(pszOutputBuffer);
        xmlBase.SetRoot();
        m_channelInfo = xmlBase.GetChildren().c_str();
        //	m_strDevAbility = m_pOutBuf;
        m_channelInfo.Replace("\n", "\r\n");
    }

    delete[] pszOutputBuffer;
    UpdateData(FALSE);
}


void CDLGGetChannelInfo::OnBnClickedBtnGetOnlineUserlist()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    NET_DVR_STD_CONFIG struCfg = { 0 };

    char *pszOutputBuffer = new (nothrow) char[4 * 1024];

    struCfg.lpCondBuffer = NULL;
    struCfg.dwCondSize = 0;
    struCfg.byDataType = 1;
    struCfg.lpXmlBuffer = pszOutputBuffer;
    struCfg.dwXmlSize = 4 * 1024;
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if (!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_ONLINEUSERLIST_SC, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ONLINEUSERLIST_SC");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ONLINEUSERLIST_SC");
        CXmlBase xmlBase;
        xmlBase.Parse(pszOutputBuffer);
        xmlBase.SetRoot();
        m_channelInfo = xmlBase.GetChildren().c_str();
        //	m_strDevAbility = m_pOutBuf;
        m_channelInfo.Replace("\n", "\r\n");
    }

    delete[] pszOutputBuffer;
    UpdateData(FALSE);
}


void CDLGGetChannelInfo::OnBnClickedBtnGetMutexFunction()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    NET_DVR_STD_CONFIG struCfg = { 0 };
    char *pszOutputBuffer = new (nothrow) char[4 * 1024];
    struCfg.lpCondBuffer = NULL;
    struCfg.dwCondSize = 0;
    struCfg.byDataType = 1;
    struCfg.lpXmlBuffer = pszOutputBuffer;
    struCfg.dwXmlSize = 4 * 1024;
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if (!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_MUTEX_FUNCTION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_MUTEX_FUNCTION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_MUTEX_FUNCTION");
        CXmlBase xmlBase;
        xmlBase.Parse(pszOutputBuffer);
        xmlBase.SetRoot();
        m_channelInfo = xmlBase.GetChildren().c_str();
        //	m_strDevAbility = m_pOutBuf;
        m_channelInfo.Replace("\n", "\r\n");
    }
    delete[] pszOutputBuffer;
    UpdateData(FALSE);
}
