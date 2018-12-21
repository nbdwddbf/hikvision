// DlgIperf.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgIperf.h"
#include "afxdialogex.h"

#define IPERF_URL       "PUT /ISAPI/System/Debug/IperfTest\r\n"
#define IPERF_PARAM_TCP "-s -w 8388608 -p %d -i 5 "
#define IPERF_PARAM_UDP "-s -w 8388608 -u -p %d -i 5 "


//Iperf的报文内容，这里简单实现，用个宏快速解决，不一个个组装了
/*
	<IperfTest version = "2.0" xmlns = "http://www.isapi.org/ver20/XMLSchema">
	<serverIP><!--req, xs:string--></serverIP>
	<serverPort><!--req, xs: integer, default = "5001"--></serverPort >
	<protocolType><!--req, xs:string, "TCP" or "UDP"--></protocolType>
	<testTime><!--req, xs:integer, 单位(s), default = "30", min = "10", max = "3000"--></testTime>
	<UDPParam>
	<bandwidth><!--opt, xs:integer, 利用带宽, 单位（Kbps）, default = "102400"--></bandwidth>
	</UDPParam>
	</IperfTest>
*/

#define IPERF_XML "<IperfTest version=\"2.0\" xmlns=\"http://www.isapi.org/ver20/XMLSchema\">\r\n<serverIP>%s</serverIP>\r\n<serverPort>%d</serverPort>\r\n<protocolType>%s</protocolType>\r\n<testTime>%d</testTime>\r\n<UDPParam><bandwidth>%d</bandwidth>\r\n</UDPParam>\r\n</IperfTest>\r\n"


// CDlgIperf 对话框

IMPLEMENT_DYNAMIC(CDlgIperf, CDialog)

CDlgIperf::CDlgIperf(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIperf::IDD, pParent)
	, m_dwBandWidth(102400)
	, m_wPort(5001)
	, m_strServerIP(_T("0.0.0.0"))
	, m_dwTestTime(30)
	, m_hProcess(NULL)
{
}

CDlgIperf::~CDlgIperf()
{
	if (m_hProcess != NULL)
	{
		int iCode = 0;
		TerminateProcess(m_hProcess, iCode);
		CloseHandle(m_hProcess);
		m_hProcess = NULL;
	}
}

void CDlgIperf::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PRO_TYPE, m_ComboProType);
	DDX_Control(pDX, IDC_EDIT_BANDWIDTH, m_EdtBandWidth);
	DDX_Text(pDX, IDC_EDIT_IP, m_strServerIP);
	DDV_MaxChars(pDX, m_strServerIP, 16);
	DDX_Text(pDX, IDC_EDIT_PORT, m_wPort);
	DDX_Text(pDX, IDC_EDIT_BANDWIDTH, m_dwBandWidth);
	DDX_Text(pDX, IDC_EDIT_TIME, m_dwTestTime);
}


BOOL CDlgIperf::OnInitDialog()
{
	BOOL bRet = CDialog::OnInitDialog();
	//把默认值都填入到控件里
	UpdateData(FALSE);
	m_ComboProType.SetCurSel(0);
	OnCbnSelchangeComboProType();

	return bRet;
}

BEGIN_MESSAGE_MAP(CDlgIperf, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_PRO_TYPE, &CDlgIperf::OnCbnSelchangeComboProType)
	ON_BN_CLICKED(IDC_BTN_TEST, &CDlgIperf::OnBnClickedBtnTest)
END_MESSAGE_MAP()


// CDlgIperf 消息处理程序


void CDlgIperf::OnCbnSelchangeComboProType()
{
	// TODO:  在此添加控件通知处理程序代码
	int iProType = m_ComboProType.GetCurSel();
	if (iProType == 0)
	{
		m_EdtBandWidth.EnableWindow(FALSE);
	}
	else
	{
		m_EdtBandWidth.EnableWindow(TRUE);
	}

	if (m_hProcess != NULL)
	{
		int iCode = 0;
		TerminateProcess(m_hProcess, iCode);
		CloseHandle(m_hProcess);
		m_hProcess = NULL;
	}
}


void CDlgIperf::OnBnClickedBtnTest()
{
	UpdateData(TRUE);

	RunIperf();

	// TODO:  在此添加控件通知处理程序代码
	char szCommand[256] = { 0 };
	sprintf(szCommand, IPERF_URL);
	//组装XML报文
	char szXML[1024] = { 0 };
	char szProtocolType[4] = { 0 };
	if (m_ComboProType.GetCurSel() == 0)
	{
		sprintf(szProtocolType, "TCP");
	}
	else
	{
		sprintf(szProtocolType, "UDP");
	}
	sprintf(szXML, IPERF_XML, m_strServerIP, m_wPort, szProtocolType, m_dwTestTime, m_dwBandWidth);

	DWORD dwDeviceIndex = g_pMainDlg->GetCurDeviceIndex();

	NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
	NET_DVR_XML_CONFIG_OUTPUT   struOutput = { 0 };
	struInput.dwSize = sizeof(struInput);
	struOutput.dwSize = sizeof(struOutput);

	struInput.dwRequestUrlLen = strlen(szCommand);
	struInput.dwInBufferSize = strlen(szXML);
	struInput.lpInBuffer = szXML;
	struInput.lpRequestUrl = szCommand;

	char sStatusBuf[1024] = { 0 };
	struOutput.lpStatusBuffer = sStatusBuf;
	struOutput.dwStatusSize = sizeof(sStatusBuf);

	if (!NET_DVR_STDXMLConfig(g_struDeviceInfo[dwDeviceIndex].lLoginID, &struInput, &struOutput))
	{
		g_pMainDlg->AddLog(dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
	}
	
}

void CDlgIperf::RunIperf()
{
	UpdateData(TRUE);
	if (m_hProcess != NULL)
	{
		//尝试等待一下，看看程序是否仍然存活
		if (WaitForSingleObject(m_hProcess, 0) == WAIT_TIMEOUT)
		{
			return;
		}
		else
		{
			CloseHandle(m_hProcess);
		}
	}

	char szParam[64] = { 0 };
	if (m_ComboProType.GetCurSel() == 0)
	{
		sprintf(szParam, IPERF_PARAM_TCP, m_wPort);
	}
	else
	{
		sprintf(szParam, IPERF_PARAM_UDP, m_wPort);
	}

	SHELLEXECUTEINFO sei;
	ZeroMemory(&sei, sizeof(SHELLEXECUTEINFO));

	sei.cbSize = sizeof(SHELLEXECUTEINFO);
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	sei.hwnd = this->GetSafeHwnd();
	sei.lpVerb = "open";
	//sei.lpFile = "E:/workhome/SDK5.0/baseline/common/HCNetSDK/VS2013/win32/lib/iperf.exe";
	sei.lpFile = "iperf.exe";
	sei.lpParameters = szParam;
	//sei.lpDirectory = pFileName;
	sei.nShow = SW_SHOWNORMAL;
	sei.hInstApp = NULL;

	ShellExecuteEx(&sei);

	m_hProcess = sei.hProcess;


}
