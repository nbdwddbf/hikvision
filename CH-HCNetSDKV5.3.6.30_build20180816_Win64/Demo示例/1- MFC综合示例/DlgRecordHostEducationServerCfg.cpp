// DlgRecordHostEducationServerCfg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgRecordHostEducationServerCfg.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"


// CDlgRecordHostEducationServerCfg 对话框

IMPLEMENT_DYNAMIC(CDlgRecordHostEducationServerCfg, CDialogEx)

CDlgRecordHostEducationServerCfg::CDlgRecordHostEducationServerCfg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRecordHostEducationServerCfg::IDD, pParent)
	, m_bConnetServer(FALSE)
	, m_strDomain(_T(""))
	, m_iHeartBeatTime(0)
	, m_strIPAddress(_T(""))
	, m_iPort(0)
	, m_lUserID(-1)
	, m_iDeviceIndex(-1)
{

}

CDlgRecordHostEducationServerCfg::~CDlgRecordHostEducationServerCfg()
{
}

void CDlgRecordHostEducationServerCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_CONNECT_SERVER, m_bConnetServer);
	DDX_Control(pDX, IDC_COMBO_CONNET_STATUS, m_cmbConnetStatus);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cmbType);
	DDX_Text(pDX, IDC_EDIT_DOMAIN, m_strDomain);
	DDX_Text(pDX, IDC_EDIT_HEART_BEAT_TIME, m_iHeartBeatTime);
	DDX_Text(pDX, IDC_EDIT_IP_ADDRESS, m_strIPAddress);
	DDX_Text(pDX, IDC_EDIT_PORT, m_iPort);
}


BEGIN_MESSAGE_MAP(CDlgRecordHostEducationServerCfg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_GET, &CDlgRecordHostEducationServerCfg::OnBnClickedButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CDlgRecordHostEducationServerCfg::OnBnClickedButtonSet)
END_MESSAGE_MAP()


// CDlgRecordHostEducationServerCfg 消息处理程序


BOOL CDlgRecordHostEducationServerCfg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	char szLan[64] = { 0 };

	g_StringLanType(szLan, "IP地址", "IPAddress");
	m_cmbType.InsertString(0, szLan);
	g_StringLanType(szLan, "域名", "Domain");
	m_cmbType.InsertString(1, szLan);
	m_cmbType.SetCurSel(0);

	g_StringLanType(szLan, "已连接", "connected");
	m_cmbConnetStatus.InsertString(0, szLan);
	g_StringLanType(szLan, "正在连接", "connecting");
	m_cmbConnetStatus.InsertString(1, szLan);
	g_StringLanType(szLan, "未连接", "disconnect");
	m_cmbConnetStatus.InsertString(2, szLan);
	m_cmbConnetStatus.SetCurSel(2);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

BOOL CDlgRecordHostEducationServerCfg::CreateEducationServerCfgXML(char* pBuf, DWORD dwBufLen, int &dwRet)
{
	CString strParam = _T("");
	CXmlBase xmlBase;
	xmlBase.CreateRoot("EducationServerConfiguration");
	xmlBase.SetAttribute("version", "2.0");

    if (m_cmbType.GetCurSel() == 0)
    {
        xmlBase.AddNode("addressType", "IPAddress");
    }
    else if (m_cmbType.GetCurSel() == 1)
    {
        xmlBase.AddNode("addressType", "domain");
    }
    xmlBase.OutOfElem();
	if (m_strIPAddress.Find(':') != -1)
	{
		xmlBase.AddNode("ipv6Address", m_strIPAddress.GetBuffer(0));
		xmlBase.OutOfElem();
	}
	else
	{
		xmlBase.AddNode("ipAddress", m_strIPAddress.GetBuffer(0));
		xmlBase.OutOfElem();
	}
	xmlBase.AddNode("domain", m_strDomain.GetBuffer(0));
	xmlBase.OutOfElem();
	strParam.Format("%d", m_iPort);
	xmlBase.AddNode("portNo", strParam.GetBuffer(0));
	xmlBase.OutOfElem();
	strParam.Format("%d", m_iHeartBeatTime);
	xmlBase.AddNode("heartbeatTime", strParam.GetBuffer(0));
	xmlBase.OutOfElem();
	if (m_bConnetServer)
	{
		xmlBase.AddNode("connectServer", "true");
		xmlBase.OutOfElem();
		if (m_cmbConnetStatus.GetCurSel() == 0)
		{
			xmlBase.AddNode("connectStatus", "connected");
		}
		else if (m_cmbConnetStatus.GetCurSel() == 1)
		{
			xmlBase.AddNode("connectStatus", "connecting");
		}
		else if (m_cmbConnetStatus.GetCurSel() == 2)
		{
			xmlBase.AddNode("connectStatus", "disconnect");
		}
		xmlBase.OutOfElem();
	}
	else
	{
		xmlBase.AddNode("connectServer", "false");
		xmlBase.OutOfElem();
	}

	return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}

void CDlgRecordHostEducationServerCfg::OnBnClickedButtonGet()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
	NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
	struInput.dwSize = sizeof(struInput);
	struOuput.dwSize = sizeof(struOuput);
	char szUrl[256] = { 0 };
	sprintf(szUrl, "GET /ISAPI/ContentMgmt/RecordingHost/EducationServerConfiguration\r\n");

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
	if (xmlBase.FindElem("EducationServerConfiguration") && xmlBase.IntoElem())
	{
        if (xmlBase.FindElem("addressType"))
        {
            if (xmlBase.GetData().compare("IPAddress") == 0)
            {
                m_cmbType.SetCurSel(0);
            }
            else if (xmlBase.GetData().compare("domain") == 0)
            {
                m_cmbType.SetCurSel(1);
            }
        }
		if (xmlBase.FindElem("ipAddress"))
		{
			m_strIPAddress = xmlBase.GetData().c_str();
		}
		else if (xmlBase.FindElem("ipv6Address"))
		{
			m_strIPAddress = xmlBase.GetData().c_str();
		}
		if (xmlBase.FindElem("domain"))
		{
			m_strDomain = xmlBase.GetData().c_str();
		}
		if (xmlBase.FindElem("portNo"))
		{
			m_iPort = atoi(xmlBase.GetData().c_str());
		}
		if (xmlBase.FindElem("heartbeatTime"))
		{
			m_iHeartBeatTime = atoi(xmlBase.GetData().c_str());
		}
		if (xmlBase.FindElem("connectServer"))
		{
			if (xmlBase.GetData().compare("true") == 0)
			{
				m_bConnetServer = TRUE;
				if (xmlBase.FindElem("connectStatus"))
				{
					if (xmlBase.GetData().compare("connected") == 0)
					{
						m_cmbConnetStatus.SetCurSel(0);
					}
					else if (xmlBase.GetData().compare("connecting") == 0)
					{
						m_cmbConnetStatus.SetCurSel(1);
					}
					else if (xmlBase.GetData().compare("disconnect") == 0)
					{
						m_cmbConnetStatus.SetCurSel(2);
					}
				}
			}
			else if (xmlBase.GetData().compare("false") == 0)
			{
				m_bConnetServer = FALSE;
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


void CDlgRecordHostEducationServerCfg::OnBnClickedButtonSet()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	DWORD dwBufLen = 10 * 1024;
	char *pBuf = new char[dwBufLen];
	memset(pBuf, 0, dwBufLen);
	int dwXmlLen = 0;
	if (!CreateEducationServerCfgXML(pBuf, dwBufLen, dwXmlLen))
	{
		delete[]pBuf;
		pBuf = NULL;
		return;
	}

	char szUrl[256] = { 0 };
	sprintf(szUrl, "PUT /ISAPI/ContentMgmt/RecordingHost/EducationServerConfiguration\r\n");
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

