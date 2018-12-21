// DlgHardDiskStorageTest.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgHardDiskStorageTest.h"
#include "afxdialogex.h"


// CDlgHardDiskStorageTest 对话框

IMPLEMENT_DYNAMIC(CDlgHardDiskStorageTest, CDialogEx)

CDlgHardDiskStorageTest::CDlgHardDiskStorageTest(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgHardDiskStorageTest::IDD, pParent)
    , m_strCardNo(_T(""))
    , m_iRssi(0)
    , m_lUserID(-1)
    , m_iDeviceIndex(-1)
    , m_bStart(FALSE)
{
}

CDlgHardDiskStorageTest::~CDlgHardDiskStorageTest()
{
}

void CDlgHardDiskStorageTest::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_CARD_NO, m_strCardNo);
    DDX_Text(pDX, IDC_EDIT_RSSI, m_iRssi);
}


BEGIN_MESSAGE_MAP(CDlgHardDiskStorageTest, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_GET, &CDlgHardDiskStorageTest::OnBnClickedButtonGet)
    ON_WM_TIMER()
    ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgHardDiskStorageTest 消息处理程序


void CDlgHardDiskStorageTest::OnBnClickedButtonGet()
{
    // TODO:  在此添加控件通知处理程序代码
    char szLan[128] = { 0 };
    if (!m_bStart)
    {
        g_StringLanType(szLan, "停止", "Stop");
        GetDlgItem(IDC_BUTTON_GET)->SetWindowText(szLan);
        m_bStart = TRUE;
        SetTimer(8, 500, NULL);
    }
    else
    {
        g_StringLanType(szLan, "获取", "Get");
        GetDlgItem(IDC_BUTTON_GET)->SetWindowText(szLan);
        m_bStart = FALSE;
        KillTimer(8);
    }
}

void CDlgHardDiskStorageTest::GetHardDiskStorageTest()
{
    UpdateData(TRUE);
    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    char szUrl[256] = { 0 };
    sprintf(szUrl, "GET /ISAPI/Traffic/UHFRFIDReader/hardDiskStorageTest\r\n");

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
    if (xmlBase.FindElem("HardDiskStorageTest") && xmlBase.IntoElem())
    {
        if (xmlBase.FindElem("cardNo"))
        {
            m_strCardNo = xmlBase.GetData().c_str();
        }
        if (xmlBase.FindElem("rssi"))
        {
            m_iRssi = atoi(xmlBase.GetData().c_str());
        }
        xmlBase.OutOfElem();
    }

    delete[]pOutBuf;
    pOutBuf = NULL;

    UpdateData(FALSE);
    return;
}

void CDlgHardDiskStorageTest::OnTimer(UINT_PTR nIDEvent)
{
    // TODO:  在此添加消息处理程序代码和/或调用默认值

    switch (nIDEvent)
    {
    case 8:
        GetHardDiskStorageTest();
        break;
    default:
        break;
    }

    CDialogEx::OnTimer(nIDEvent);
}


void CDlgHardDiskStorageTest::OnClose()
{
    // TODO:  在此添加消息处理程序代码和/或调用默认值

    if (m_bStart)
    {
        KillTimer(8);
    }

    CDialogEx::OnClose();
}
