// DlgWiegandCfg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgWiegandCfg.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"


// CDlgWiegandCfg 对话框

IMPLEMENT_DYNAMIC(CDlgWiegandCfg, CDialogEx)

CDlgWiegandCfg::CDlgWiegandCfg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgWiegandCfg::IDD, pParent)
	, m_iWiegandNo(0)
	, m_lUserID(0)
	, m_iDeviceIndex(0)
{

}

CDlgWiegandCfg::~CDlgWiegandCfg()
{
}

void CDlgWiegandCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_WIEGAND_NO, m_iWiegandNo);
	DDV_MinMaxInt(pDX, m_iWiegandNo, 0, 100);
	DDX_Control(pDX, IDC_COMBO_COMMUNICATION_DIRECTION, m_cmbCommunicationDirection);
	DDX_Control(pDX, IDC_COMBO_WIEGAND_MODE, m_cmbWiegandMode);
}


BEGIN_MESSAGE_MAP(CDlgWiegandCfg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_GET, &CDlgWiegandCfg::OnBnClickedButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CDlgWiegandCfg::OnBnClickedButtonSet)
	ON_CBN_SELCHANGE(IDC_COMBO_COMMUNICATION_DIRECTION, &CDlgWiegandCfg::OnCbnSelchangeComboCommunicationDirection)
END_MESSAGE_MAP()


// CDlgWiegandCfg 消息处理程序

BOOL CDlgWiegandCfg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	char szLan[64] = { 0 };

	m_cmbCommunicationDirection.ResetContent();
	g_StringLanType(szLan, "接收", "receive");
	m_cmbCommunicationDirection.InsertString(0, szLan);
	g_StringLanType(szLan, "发送", "send");
	m_cmbCommunicationDirection.InsertString(1, szLan);
	m_cmbCommunicationDirection.SetCurSel(0);

	m_cmbWiegandMode.ResetContent();
	g_StringLanType(szLan, "韦根26", "wiegand26");
	m_cmbWiegandMode.InsertString(0, szLan);
	g_StringLanType(szLan, "韦根34", "wiegand34");
	m_cmbWiegandMode.InsertString(1, szLan);
    g_StringLanType(szLan, "韦根27", "wiegand27");
    m_cmbWiegandMode.InsertString(2, szLan);
    g_StringLanType(szLan, "韦根35", "wiegand35");
    m_cmbWiegandMode.InsertString(3, szLan);
	m_cmbWiegandMode.SetCurSel(0);
	GetDlgItem(IDC_STATIC_WIEGAND_MODE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO_WIEGAND_MODE)->ShowWindow(SW_HIDE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgWiegandCfg::CreateWiegandCfg(char* pBuf, DWORD dwBufLen, int &dwRet)
{
	CXmlBase xmlBase;
	CString strParam = _T("");
	xmlBase.CreateRoot("WiegandCfg");
	xmlBase.SetAttribute("version", "2.0");
	if (m_cmbCommunicationDirection.GetCurSel() == 0)
	{
		xmlBase.AddNode("communicateDirection", "receive");
		xmlBase.OutOfElem();
	}
	else if (m_cmbCommunicationDirection.GetCurSel() == 1)
	{
		xmlBase.AddNode("communicateDirection", "send");
		xmlBase.OutOfElem();
		if (m_cmbWiegandMode.GetCurSel() == 0)
		{
			xmlBase.AddNode("wiegandMode", "wiegand26");
		}
		else if (m_cmbWiegandMode.GetCurSel() == 1)
		{
			xmlBase.AddNode("wiegandMode", "wiegand34");
		}
        else if (m_cmbWiegandMode.GetCurSel() == 2)
        {
            xmlBase.AddNode("wiegandMode", "wiegand27");
        }
        else if (m_cmbWiegandMode.GetCurSel() == 3)
        {
            xmlBase.AddNode("wiegandMode", "wiegand35");
        }
		xmlBase.OutOfElem();
	}

	return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}


void CDlgWiegandCfg::OnBnClickedButtonGet()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
	NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
	struInput.dwSize = sizeof(struInput);
	struOuput.dwSize = sizeof(struOuput);
	char szUrl[256] = { 0 };
	sprintf(szUrl, "GET /ISAPI/AccessControl/WiegandCfg/wiegandNo/%d\r\n", m_iWiegandNo);
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
	if (xmlBase.FindElem("WiegandCfg") && xmlBase.IntoElem())
	{
		if (xmlBase.FindElem("communicateDirection"))
		{
			if (xmlBase.GetData().compare("receive") == 0)
			{
				m_cmbCommunicationDirection.SetCurSel(0);
			}
			else if (xmlBase.GetData().compare("send") == 0)
			{
				m_cmbCommunicationDirection.SetCurSel(1);
			}
		}
		if (xmlBase.FindElem("wiegandMode"))
		{
			if (xmlBase.GetData().compare("wiegand26") == 0)
			{
				m_cmbWiegandMode.SetCurSel(0);
			}
			else if (xmlBase.GetData().compare("wiegand34") == 0)
			{
				m_cmbWiegandMode.SetCurSel(1);
			}
            else if (xmlBase.GetData().compare("wiegand27") == 0)
            {
                m_cmbWiegandMode.SetCurSel(3);
            }
            else if (xmlBase.GetData().compare("wiegand35") == 0)
            {
                m_cmbWiegandMode.SetCurSel(4);
            }
		}
		xmlBase.OutOfElem();
	}
	OnCbnSelchangeComboCommunicationDirection();

	if (pOutBuf != NULL)
	{
		delete[]pOutBuf;
		pOutBuf = NULL;
	}
	UpdateData(FALSE);

	return;
}


void CDlgWiegandCfg::OnBnClickedButtonSet()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	DWORD dwBufLen = 10 * 1024;
	char *pBuf = new char[dwBufLen];
	memset(pBuf, 0, dwBufLen);
	int dwXmlLen = 0;
	if (!CreateWiegandCfg(pBuf, dwBufLen, dwXmlLen))
	{
		delete[]pBuf;
		pBuf = NULL;
		return;
	}

	char szUrl[256] = { 0 };
	sprintf(szUrl, "PUT /ISAPI/AccessControl/WiegandCfg/wiegandNo/%d\r\n", m_iWiegandNo);
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


void CDlgWiegandCfg::OnCbnSelchangeComboCommunicationDirection()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_cmbCommunicationDirection.GetCurSel() == 0)
	{
		GetDlgItem(IDC_STATIC_WIEGAND_MODE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_WIEGAND_MODE)->ShowWindow(SW_HIDE);
	}
	else if(m_cmbCommunicationDirection.GetCurSel() == 1)
	{
		GetDlgItem(IDC_STATIC_WIEGAND_MODE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_WIEGAND_MODE)->ShowWindow(SW_SHOW);
	}
}
