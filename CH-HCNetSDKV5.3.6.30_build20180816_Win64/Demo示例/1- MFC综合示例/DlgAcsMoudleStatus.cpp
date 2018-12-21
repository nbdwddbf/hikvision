// DlgAcsMoudleStatus.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgAcsMoudleStatus.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"


// CDlgAcsMoudleStatus 对话框

IMPLEMENT_DYNAMIC(CDlgAcsMoudleStatus, CDialogEx)

CDlgAcsMoudleStatus::CDlgAcsMoudleStatus(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgAcsMoudleStatus::IDD, pParent)
	, m_lUserID(0)
	, m_iDeviceIndex(0)
{

}

CDlgAcsMoudleStatus::~CDlgAcsMoudleStatus()
{
}

void CDlgAcsMoudleStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ONLINE_STATUS, m_listOnlineStatus);
	DDX_Control(pDX, IDC_LIST_DESMANTEL_STATUS, m_listDesmantelStatus);
}


BEGIN_MESSAGE_MAP(CDlgAcsMoudleStatus, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_GET, &CDlgAcsMoudleStatus::OnBnClickedButtonGet)
END_MESSAGE_MAP()


BOOL CDlgAcsMoudleStatus::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here	
	int i = 0;
	CString tmp;

	m_listOnlineStatus.SetExtendedStyle(LVS_EX_CHECKBOXES);
	for (i = 0; i < 256; i++)
	{
		tmp.Format("Online Status %d", (i + 1));
		m_listOnlineStatus.InsertItem(i, tmp);
	}

	m_listDesmantelStatus.SetExtendedStyle(LVS_EX_CHECKBOXES);
	for (i = 0; i < 256; i++)
	{
		tmp.Format("Desmantel Status %d", (i + 1));
		m_listDesmantelStatus.InsertItem(i, tmp);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAcsMoudleStatus::OnBnClickedButtonGet()
{
	// TODO: Add extra initialization here	
	UpdateData(TRUE);
	char szDoorNo[300] = { 0 };
	char szOnlineStatus[300] = { 0 };
	string strOnlineStatus = _T("");
	string strDesmantelStatus = _T("");
	NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
	NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
	struInput.dwSize = sizeof(struInput);
	struOuput.dwSize = sizeof(struOuput);
	char szUrl[256] = { 0 };
	sprintf(szUrl, "GET /ISAPI/AccessControl/DoorSecurityModule/moduleStatus\r\n");
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
		if (pOutBuf != NULL)
		{
			delete[]pOutBuf;
			pOutBuf = NULL;
		}
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);
	}

	CXmlBase xmlBase;
	xmlBase.Parse(pOutBuf);
	if (xmlBase.FindElem("ModuleStatus") && xmlBase.IntoElem())
	{
		if (xmlBase.FindElem("onlineStatus"))
		{
			strOnlineStatus = xmlBase.GetData();
			if (strOnlineStatus.length() > 256)
			{
				MessageBox("The param you get from device is illegal ");
				return;
			}
		}
		if (xmlBase.FindElem("desmantelStatus"))
		{
			strDesmantelStatus = xmlBase.GetData();
			if (strDesmantelStatus.length() > 256)
			{
				MessageBox("The param you get from device is illegal ");
				return;
			}
		}
		xmlBase.OutOfElem();
	}
	if (pOutBuf != NULL)
	{
		delete[]pOutBuf;
		pOutBuf = NULL;
	}

	for (int i = 0; i < 256; i++)
	{
		if (strOnlineStatus.empty() || strOnlineStatus[i] == '\0')
		{
			break;
		}
		if (strOnlineStatus[i] == '0')
		{
			m_listOnlineStatus.SetCheck(i, FALSE);
		}
		else if (strOnlineStatus[i] == '1')
		{
			m_listOnlineStatus.SetCheck(i, TRUE);
		}
	}

	for (int i = 0; i < 256; i++)
	{
		if (strDesmantelStatus.empty() || strDesmantelStatus[i] == '\0')
		{
			break;
		}
		if (strDesmantelStatus[i] == '0')
		{
			m_listDesmantelStatus.SetCheck(i, FALSE);
		}
		else if (strDesmantelStatus[i] == '1')
		{
			m_listDesmantelStatus.SetCheck(i, TRUE);
		}
	}

	UpdateData(FALSE);
	return;
}
