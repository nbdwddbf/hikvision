// DlgRecordHostDirectedAdvanceCfg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgRecordHostDirectedAdvanceCfg.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"


// CDlgRecordHostDirectedAdvanceCfg 对话框

IMPLEMENT_DYNAMIC(CDlgRecordHostDirectedAdvanceCfg, CDialogEx)

CDlgRecordHostDirectedAdvanceCfg::CDlgRecordHostDirectedAdvanceCfg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRecordHostDirectedAdvanceCfg::IDD, pParent)
	, m_iValue(0)
	, m_lUserID(-1)
	, m_iDeviceIndex(-1)
	, m_iTypeTarget(0)
{

}

CDlgRecordHostDirectedAdvanceCfg::~CDlgRecordHostDirectedAdvanceCfg()
{
}

void CDlgRecordHostDirectedAdvanceCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_VALUE, m_iTypeTarget);
	DDV_MinMaxInt(pDX, m_iTypeTarget, 0, 100);
	DDX_Text(pDX, IDC_EDIT_TYPE_TARGET, m_iValue);
	DDV_MinMaxInt(pDX, m_iValue, 0, 100);
}


BEGIN_MESSAGE_MAP(CDlgRecordHostDirectedAdvanceCfg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_GET, &CDlgRecordHostDirectedAdvanceCfg::OnBnClickedButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CDlgRecordHostDirectedAdvanceCfg::OnBnClickedButtonSet)
END_MESSAGE_MAP()


// CDlgRecordHostDirectedAdvanceCfg 消息处理程序


BOOL CDlgRecordHostDirectedAdvanceCfg::CreateDirectedAdvanceCfg(char* pBuf, DWORD dwBufLen, int &dwRet)
{
	CString strParam = _T("");
	CXmlBase xmlBase;
	xmlBase.CreateRoot("DirectedAdvanceCfg");
	xmlBase.SetAttribute("version", "2.0");
	strParam.Format("%d", m_iTypeTarget);
	xmlBase.AddNode("commandID", strParam.GetBuffer(0));
	xmlBase.OutOfElem();
	strParam.Format("%d", m_iValue);
	xmlBase.AddNode("value", strParam.GetBuffer(0));
	xmlBase.OutOfElem();

	return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}

void CDlgRecordHostDirectedAdvanceCfg::OnBnClickedButtonGet()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
	NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
	struInput.dwSize = sizeof(struInput);
	struOuput.dwSize = sizeof(struOuput);
	char szUrl[256] = { 0 };
	sprintf(szUrl, "GET /ISAPI/ContentMgmt/RecordingHost/DirectedAdvanceCfg/commandID/%d\r\n", m_iTypeTarget);

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
	if (xmlBase.FindElem("DirectedAdvanceCfg") && xmlBase.IntoElem())
	{
		if (xmlBase.FindElem("commandID"))
		{
			m_iTypeTarget = atoi(xmlBase.GetData().c_str());
		}
		if (xmlBase.FindElem("value"))
		{
			m_iValue = atoi(xmlBase.GetData().c_str());
		}
		xmlBase.OutOfElem();
	}

	delete[]pOutBuf;
	pOutBuf = NULL;

	UpdateData(FALSE);
	return;
}


void CDlgRecordHostDirectedAdvanceCfg::OnBnClickedButtonSet()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	DWORD dwBufLen = 10 * 1024;
	char *pBuf = new char[dwBufLen];
	memset(pBuf, 0, dwBufLen);
	int dwXmlLen = 0;
	if (!CreateDirectedAdvanceCfg(pBuf, dwBufLen, dwXmlLen))
	{
		delete[]pBuf;
		pBuf = NULL;
		return;
	}

	char szUrl[256] = { 0 };
	sprintf(szUrl, "PUT /ISAPI/ContentMgmt/RecordingHost/DirectedAdvanceCfg/commandID/%d\r\n", m_iTypeTarget);
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

	delete[]pBuf;
	pBuf = NULL;

	UpdateData(FALSE);
}

