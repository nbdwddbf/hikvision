// DlgAcsLocalControllerCfg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgAcsLocalControllerCfg.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"


// CDlgAcsLocalControllerCfg 对话框

IMPLEMENT_DYNAMIC(CDlgAcsLocalControllerCfg, CDialogEx)

CDlgAcsLocalControllerCfg::CDlgAcsLocalControllerCfg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgAcsLocalControllerCfg::IDD, pParent)
	, m_iLocalControllerID(0)
	, m_strDeviceName(_T(""))
	, m_strIPAddress(_T(""))
	, m_iPortNo(0)
	, m_strDefaultGateway(_T(""))
	, m_strSubnetMask(_T(""))
	, m_bNetworkEnable(FALSE)
	, m_lUserID(-1)
	, m_iDeviceIndex(-1)
{

}

CDlgAcsLocalControllerCfg::~CDlgAcsLocalControllerCfg()
{
}

void CDlgAcsLocalControllerCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LOCAL_CONTROLLER_ID, m_iLocalControllerID);
	DDX_Text(pDX, IDC_EDIT_DEVICE_NAME, m_strDeviceName);
	DDX_Text(pDX, IDC_EDIT_IP_ADDRESS, m_strIPAddress);
	DDX_Text(pDX, IDC_EDIT_PORT_NO, m_iPortNo);
	DDX_Text(pDX, IDC_EDIT_DEFAULT_GATEWAY, m_strDefaultGateway);
	DDX_Text(pDX, IDC_EDIT_SUBNET_MASK, m_strSubnetMask);
	DDX_Check(pDX, IDC_CHECK_NETWORK_ENABLE, m_bNetworkEnable);
	DDX_Control(pDX, IDC_COMBO_DEVICE_TYPE, m_cmbDeviceType);
	DDX_Control(pDX, IDC_COMBO_OFFLINE_WORK_MODE, m_cmbOfflineWorkMode);
	DDX_Control(pDX, IDC_COMBO_COMMAND_TYPE, m_cmbCommandType);
}


BEGIN_MESSAGE_MAP(CDlgAcsLocalControllerCfg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDlgAcsLocalControllerCfg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_GET, &CDlgAcsLocalControllerCfg::OnBnClickedButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CDlgAcsLocalControllerCfg::OnBnClickedButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDlgAcsLocalControllerCfg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_ALL, &CDlgAcsLocalControllerCfg::OnBnClickedButtonDeleteAll)
	ON_BN_CLICKED(IDC_BUTTON_CONTROL, &CDlgAcsLocalControllerCfg::OnBnClickedButtonControl)
END_MESSAGE_MAP()


// CDlgAcsLocalControllerCfg 消息处理程序


BOOL CDlgAcsLocalControllerCfg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	char szLan[64] = { 0 };

	g_StringLanType(szLan, "1门", "1door");
	m_cmbDeviceType.InsertString(0, szLan);
	g_StringLanType(szLan, "2门", "2door");
	m_cmbDeviceType.InsertString(1, szLan);
	g_StringLanType(szLan, "4门", "4door");
	m_cmbDeviceType.InsertString(2, szLan);
	m_cmbDeviceType.SetCurSel(0);

	g_StringLanType(szLan, "不支持", "notSupport");
	m_cmbOfflineWorkMode.InsertString(0, szLan);
	g_StringLanType(szLan, "配置模式", "configuration");
	m_cmbOfflineWorkMode.InsertString(1, szLan);
	g_StringLanType(szLan, "自学习模式", "autoLearn");
	m_cmbOfflineWorkMode.InsertString(2, szLan);
	m_cmbOfflineWorkMode.SetCurSel(0);

	g_StringLanType(szLan, "恢复", "restore");
	m_cmbCommandType.InsertString(0, szLan);
	g_StringLanType(szLan, "重启", "reboot");
	m_cmbCommandType.InsertString(1, szLan);
	m_cmbCommandType.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

BOOL CDlgAcsLocalControllerCfg::CreateLocalControllerXML(char* pBuf, DWORD dwBufLen, int &dwRet)
{
	CString strParam = _T("");
	CXmlBase xmlBase;
	xmlBase.CreateRoot("LocalController");
	xmlBase.SetAttribute("version", "2.0");
	strParam.Format("%d", m_iLocalControllerID);
	xmlBase.AddNode("localControllerID", strParam.GetBuffer(0));
	xmlBase.OutOfElem();
	xmlBase.AddNode("devName", m_strDeviceName.GetBuffer(0));
	xmlBase.OutOfElem();
	if (m_cmbDeviceType.GetCurSel() == 0)
	{
		xmlBase.AddNode("devType", "1door");
	}
	else if (m_cmbDeviceType.GetCurSel() == 1)
	{
		xmlBase.AddNode("devType", "2doors");
	}
	else if (m_cmbDeviceType.GetCurSel() == 2)
	{
		xmlBase.AddNode("devType", "4doors");
	}
	xmlBase.OutOfElem();
	if (m_cmbOfflineWorkMode.GetCurSel() == 0)
	{
		xmlBase.AddNode("offlineWorkMode", "notSupport");
	}
	else if(m_cmbOfflineWorkMode.GetCurSel() == 1)
	{
		xmlBase.AddNode("offlineWorkMode", "configuration");
	}
	else if(m_cmbOfflineWorkMode.GetCurSel() == 2)
	{
		xmlBase.AddNode("offlineWorkMode", "autoLearn");
	}
	xmlBase.OutOfElem();
	if (m_bNetworkEnable)
	{
		xmlBase.AddNode("networkEnable", "true");
	}
	else
	{
		xmlBase.AddNode("networkEnable", "false");
	}
	xmlBase.OutOfElem();
	if (m_strIPAddress.Find(':') != -1)
	{
		xmlBase.AddNode("ipv6Address", m_strIPAddress.GetBuffer(0));
		xmlBase.OutOfElem();
		xmlBase.AddNode("bitMask", m_strSubnetMask.GetBuffer(0));
		xmlBase.OutOfElem();
		xmlBase.AddNode("DefaultGateway");
		xmlBase.AddNode("ipv6Address", m_strDefaultGateway.GetBuffer(0));
		xmlBase.OutOfElem();
		xmlBase.OutOfElem();
	}
	else
	{
		xmlBase.AddNode("ipAddress", m_strIPAddress.GetBuffer(0));
		xmlBase.OutOfElem();
		xmlBase.AddNode("subnetMask", m_strSubnetMask.GetBuffer(0));
		xmlBase.OutOfElem();
		xmlBase.AddNode("DefaultGateway");
		xmlBase.AddNode("ipAddress", m_strDefaultGateway.GetBuffer(0));
		xmlBase.OutOfElem();
		xmlBase.OutOfElem();
	}

	strParam.Format("%d", m_iPortNo);
	xmlBase.AddNode("portNo", strParam.GetBuffer(0));
	xmlBase.OutOfElem();

	return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}

void CDlgAcsLocalControllerCfg::OnBnClickedButtonAdd()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	DWORD dwBufLen = 10 * 1024;
	char *pBuf = new char[dwBufLen];
	memset(pBuf, 0, dwBufLen);
	int dwXmlLen = 0;
	if (!CreateLocalControllerXML(pBuf, dwBufLen, dwXmlLen))
	{
		delete[]pBuf;
		pBuf = NULL;
		return;
	}

	char szUrl[256] = { 0 };
	sprintf(szUrl, "PUT /ISAPI/AccessControl/localController/addDevice\r\n");
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


void CDlgAcsLocalControllerCfg::OnBnClickedButtonGet()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
	NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
	struInput.dwSize = sizeof(struInput);
	struOuput.dwSize = sizeof(struOuput);
	char szUrl[256] = { 0 };
	sprintf(szUrl, "GET /ISAPI/AccessControl/localController/localControllerID/%d\r\n", m_iLocalControllerID);

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
	if (xmlBase.FindElem("LocalController") && xmlBase.IntoElem())
	{
		if (xmlBase.FindElem("localControllerID"))
		{
			m_iLocalControllerID = atoi(xmlBase.GetData().c_str());
		}
		if (xmlBase.FindElem("devName"))
		{
			m_strDeviceName = xmlBase.GetData().c_str();
		}
		if (xmlBase.FindElem("devType"))
		{
			if (xmlBase.GetData().compare("1door") == 0)
			{
				m_cmbDeviceType.SetCurSel(0);
			}
			else if (xmlBase.GetData().compare("2doors") == 0)
			{
				m_cmbDeviceType.SetCurSel(1);
			}
			else if (xmlBase.GetData().compare("4doors") == 0)
			{
				m_cmbDeviceType.SetCurSel(2);
			}
		}
		if (xmlBase.FindElem("offlineWorkMode"))
		{
			if (xmlBase.GetData().compare("notSupport") == 0)
			{
				m_cmbOfflineWorkMode.SetCurSel(0);
			}
			else if (xmlBase.GetData().compare("configuration") == 0)
			{
				m_cmbOfflineWorkMode.SetCurSel(1);
			}
			else if (xmlBase.GetData().compare("autoLearn") == 0)
			{
				m_cmbOfflineWorkMode.SetCurSel(2);
			}
		}
		if (xmlBase.FindElem("networkEnable"))
		{
			if (xmlBase.GetData().compare("true") == 0)
			{
				m_bNetworkEnable = TRUE;
			}
			else if (xmlBase.GetData().compare("false") == 0)
			{
				m_bNetworkEnable = FALSE;
			}
		}

		if (xmlBase.FindElem("ipAddress"))
		{
			m_strIPAddress = xmlBase.GetData().c_str();
			if (xmlBase.FindElem("subnetMask"))
			{
				m_strSubnetMask = xmlBase.GetData().c_str();
			}
			if (xmlBase.FindElem("DefaultGateway") && xmlBase.IntoElem())
			{
				if (xmlBase.FindElem("ipAddress"))
				{
					m_strDefaultGateway = xmlBase.GetData().c_str();
				}
				xmlBase.OutOfElem();
			}
		}
		else if (xmlBase.FindElem("ipv6Address"))
		{
			m_strIPAddress = xmlBase.GetData().c_str();
			if (xmlBase.FindElem("bitMask"))
			{
				m_strSubnetMask = xmlBase.GetData().c_str();
			}
			if (xmlBase.FindElem("DefaultGateway") && xmlBase.IntoElem())
			{
				if (xmlBase.FindElem("ipv6Address"))
				{
					m_strDefaultGateway = xmlBase.GetData().c_str();
				}
				xmlBase.OutOfElem();
			}
		}
		
		if (xmlBase.FindElem("portNo"))
		{
			m_iPortNo = atoi(xmlBase.GetData().c_str());
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


void CDlgAcsLocalControllerCfg::OnBnClickedButtonSet()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	DWORD dwBufLen = 10 * 1024;
	char *pBuf = new char[dwBufLen];
	memset(pBuf, 0, dwBufLen);
	int dwXmlLen = 0;
	if (!CreateLocalControllerXML(pBuf, dwBufLen, dwXmlLen))
	{
		delete[]pBuf;
		pBuf = NULL;
		return;
	}

	char szUrl[256] = { 0 };
	sprintf(szUrl, "PUT /ISAPI/AccessControl/localController/localControllerID/%d\r\n", m_iLocalControllerID);
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


void CDlgAcsLocalControllerCfg::OnBnClickedButtonDelete()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	DWORD dwBufLen = 10 * 1024;
	char *pBuf = new char[dwBufLen];
	memset(pBuf, 0, dwBufLen);
	int dwXmlLen = 0;

	char szUrl[256] = { 0 };
	sprintf(szUrl, "DELETE /ISAPI/AccessControl/localController/localControllerID/%d\r\n", m_iLocalControllerID);
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


void CDlgAcsLocalControllerCfg::OnBnClickedButtonDeleteAll()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	DWORD dwBufLen = 10 * 1024;
	char *pBuf = new char[dwBufLen];
	memset(pBuf, 0, dwBufLen);
	int dwXmlLen = 0;

	char szUrl[256] = { 0 };
	sprintf(szUrl, "DELETE /ISAPI/AccessControl/localController\r\n");
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

BOOL CDlgAcsLocalControllerCfg::CreateLocalControllerControlXML(char* pBuf, DWORD dwBufLen, int &dwRet)
{
	CString strParam = _T("");
	CXmlBase xmlBase;
	xmlBase.CreateRoot("LocalControllerControl");
	xmlBase.SetAttribute("version", "2.0");
	if (m_cmbCommandType.GetCurSel() == 0)
	{
		xmlBase.AddNode("commandType", "restore");
	}
	else if (m_cmbCommandType.GetCurSel() == 1)
	{
		xmlBase.AddNode("commandType", "reboot");
	}
	xmlBase.OutOfElem();

	return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}

void CDlgAcsLocalControllerCfg::OnBnClickedButtonControl()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	DWORD dwBufLen = 10 * 1024;
	char *pBuf = new char[dwBufLen];
	memset(pBuf, 0, dwBufLen);
	int dwXmlLen = 0;
	if (!CreateLocalControllerControlXML(pBuf, dwBufLen, dwXmlLen))
	{
		delete[]pBuf;
		pBuf = NULL;
		return;
	}

	char szUrl[256] = { 0 };
	sprintf(szUrl, "PUT /ISAPI/AccessControl/localController/control/localControllerID/%d\r\n", m_iLocalControllerID);
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
