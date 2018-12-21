// DlgDeviceManage.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgAcsUSBDeviceManage.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"


// CDlgDeviceManage 对话框

IMPLEMENT_DYNAMIC(CDlgAcsUSBDeviceManage, CDialogEx)

CDlgAcsUSBDeviceManage::CDlgAcsUSBDeviceManage(CWnd* pParent /*=NULL*/)
: CDialogEx(CDlgAcsUSBDeviceManage::IDD, pParent)
	, m_strDeviceName(_T(""))
	, m_iUSBNumber(0)
	, m_lUserID(-1)
	, m_iDeviceIndex(-1)
    , m_iProgress(0)
{

}

CDlgAcsUSBDeviceManage::~CDlgAcsUSBDeviceManage()
{
}

void CDlgAcsUSBDeviceManage::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COM_COMMAND_TYPE, m_comCommandType);
    DDX_Control(pDX, IDC_COMBO_CONNECT_STATUS, m_comConnetStatus);
    DDX_Text(pDX, IDC_EDIT_DEVICE_NAME, m_strDeviceName);
    DDX_Text(pDX, IDC_EDIT_USB_NUMBER, m_iUSBNumber);
    DDX_Text(pDX, IDC_EDIT_PROGRESS, m_iProgress);
}


BEGIN_MESSAGE_MAP(CDlgAcsUSBDeviceManage, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_GET, &CDlgAcsUSBDeviceManage::OnBnClickedButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_CONTROL, &CDlgAcsUSBDeviceManage::OnBnClickedButtonControl)
    ON_WM_TIMER()
END_MESSAGE_MAP()


// CDlgDeviceManage 消息处理程序


BOOL CDlgAcsUSBDeviceManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	char szLan[64] = { 0 };

	g_StringLanType(szLan, "已连接", "connected");
	m_comConnetStatus.InsertString(0, szLan);
	g_StringLanType(szLan, "未连接", "disconnected");
	m_comConnetStatus.InsertString(1, szLan);
	m_comConnetStatus.SetCurSel(0);

	g_StringLanType(szLan, "通用参数输入", "commonParamImport");
	m_comCommandType.InsertString(0, szLan);
	g_StringLanType(szLan, "通用参数输出", "commonParamExport");
	m_comCommandType.InsertString(1, szLan);
	g_StringLanType(szLan, "卡参数输入", "cardParamImport");
	m_comCommandType.InsertString(2, szLan);
	g_StringLanType(szLan, "卡参数输出", "cardParamExport");
	m_comCommandType.InsertString(3, szLan);
	g_StringLanType(szLan, "考勤参数输出", "attendanceParamExport");
	m_comCommandType.InsertString(4, szLan);
	m_comCommandType.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

BOOL CDlgAcsUSBDeviceManage::CreateUSBControlXML(char* pBuf, DWORD dwBufLen, int &dwRet)
{
	CString strParam = _T("");
	CXmlBase xmlBase;
	xmlBase.CreateRoot("USBControl");
	xmlBase.SetAttribute("version", "2.0");
	if (m_comCommandType.GetCurSel() == 0)
	{
		xmlBase.AddNode("commandType", "commonParamImport");
	}
	else if (m_comCommandType.GetCurSel() == 1)
	{
		xmlBase.AddNode("commandType", "commonParamExport");
	}
	else if (m_comCommandType.GetCurSel() == 2)
	{
		xmlBase.AddNode("commandType", "cardParamImport");
	}
	else if (m_comCommandType.GetCurSel() == 3)
	{
		xmlBase.AddNode("commandType", "cardParamExport");
	}
	else if (m_comCommandType.GetCurSel() == 4)
	{
		xmlBase.AddNode("commandType", "attendanceParamExport");
	}
	xmlBase.OutOfElem();

	return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}

void CDlgAcsUSBDeviceManage::OnBnClickedButtonGet()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
	NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
	struInput.dwSize = sizeof(struInput);
	struOuput.dwSize = sizeof(struOuput);
	char szUrl[256] = { 0 };
	sprintf(szUrl, "GET /ISAPI/AccessControl/USBStatus/USBNumber/%d\r\n", m_iUSBNumber);

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
	if (xmlBase.FindElem("USBStatus") && xmlBase.IntoElem())
	{
		if (xmlBase.FindElem("connectStatus"))
		{
			if (xmlBase.GetData().compare("connected") == 0)
			{
				m_comConnetStatus.SetCurSel(0);
			}
			else if (xmlBase.GetData().compare("disconnected") == 0)
			{
				m_comConnetStatus.SetCurSel(1);
			}
		}

		if (xmlBase.FindElem("DeviceInfo") && xmlBase.IntoElem())
		{
			if (xmlBase.FindElem("deviceName"))
			{
				m_strDeviceName = xmlBase.GetData().c_str();
			}
			xmlBase.OutOfElem();
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


void CDlgAcsUSBDeviceManage::OnBnClickedButtonControl()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
    m_iProgress = 0;
	DWORD dwBufLen = 10 * 1024;
	char *pBuf = new char[dwBufLen];
	memset(pBuf, 0, dwBufLen);
	int dwXmlLen = 0;
	if (!CreateUSBControlXML(pBuf, dwBufLen, dwXmlLen))
	{
		delete[]pBuf;
		pBuf = NULL;
		return;
	}

	char szUrl[256] = { 0 };
	sprintf(szUrl, "PUT /ISAPI/AccessControl/USBControl/USBNumber/%d\r\n", m_iUSBNumber);
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
        GetDlgItem(IDC_BUTTON_CONTROL)->EnableWindow(FALSE);
        SetTimer(8, 3000, NULL);
	}

	if (pBuf != NULL)
	{
		delete[]pBuf;
		pBuf = NULL;
	}

	UpdateData(FALSE);
}

#if (_MSC_VER >= 1500)	//vs2008
void CDlgAcsUSBDeviceManage::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgAcsUSBDeviceManage::OnTimer(UINT nIDEvent)
#endif
{
    // TODO: Add your message handler code here and/or call default
    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    char szUrl[256] = { 0 };
    DWORD dwOutputLen = 1024 * 1024;
    char *pOutBuf = NULL;
    BOOL bRet = FALSE;
    CXmlBase xmlBase;
    switch (nIDEvent)
    {
    case 8:
        UpdateData(TRUE);
        pOutBuf = new char[dwOutputLen];
        memset(pOutBuf, 0, dwOutputLen);
        struInput.dwSize = sizeof(struInput);
        struOuput.dwSize = sizeof(struOuput);

        sprintf(szUrl, "GET /ISAPI/AccessControl/USBControlProgress/USBNumber/%d\r\n", m_iUSBNumber);

        struInput.lpRequestUrl = szUrl;
        struInput.dwRequestUrlLen = strlen(szUrl);

        struOuput.lpOutBuffer = pOutBuf;
        struOuput.dwOutBufferSize = dwOutputLen;

        if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szUrl);
            delete[]pOutBuf;
            pOutBuf = NULL;
            GetDlgItem(IDC_BUTTON_CONTROL)->EnableWindow(TRUE);
            KillTimer(8);
            break;
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);
        }

        xmlBase.Parse(pOutBuf);
        if (xmlBase.FindElem("USBControlProgress") && xmlBase.IntoElem())
        {
            if (xmlBase.FindElem("operationProgress"))
            {
                m_iProgress = atoi(xmlBase.GetData().c_str());
            }
            xmlBase.OutOfElem();
        }

        if (pOutBuf != NULL)
        {
            delete[]pOutBuf;
            pOutBuf = NULL;
        }

        UpdateData(FALSE);

        if (m_iProgress < 0 || m_iProgress >= 100)
        {
            GetDlgItem(IDC_BUTTON_CONTROL)->EnableWindow(TRUE);
            KillTimer(8);
        }

        break;
    default:
        break;
    }
    CDialog::OnTimer(nIDEvent);
}

