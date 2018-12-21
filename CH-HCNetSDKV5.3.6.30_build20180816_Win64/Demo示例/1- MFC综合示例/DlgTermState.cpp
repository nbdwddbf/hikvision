// DlgTermState.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgTermState.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgTermState dialog


CDlgTermState::CDlgTermState(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTermState::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgTermState)
	m_csScheduleName = _T("");
	m_dwScheduleNo = 0;
	m_dwTemperature = 0;
	m_csHardVersion = _T("");
	m_SysVersion = _T("");
	m_dwTermID = 0;
	m_dwTermStateCount = 0;
	m_dwCpuIndex = 0;
	m_dwMemIndex = 0;
	m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;
	m_dwXMLResultBufLen = ISAPI_DATA_LEN;
	m_bySwitch = FALSE;
	m_byVolum = FALSE;
	//}}AFX_DATA_INIT
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	m_paTermState = new TERM_STATE[MAX_NUM_TERMINAL];
	memset(m_paTermState, 0, sizeof(TERM_STATE)*MAX_NUM_TERMINAL);
	memset(&m_szRequestURL, '\0' ,sizeof(m_szRequestURL));
	memset(&m_szXMLStatus, '\0', sizeof(m_szXMLStatus));
	m_pXMLResultBuf = new char[ISAPI_DATA_LEN];
	memset(m_pXMLResultBuf, 0, ISAPI_DATA_LEN);
}

void CDlgTermState::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgTermState)
	DDX_Control(pDX, IDC_COM_ADDR_FORMAT_TYPE, m_comAddrFormatType);
	DDX_Control(pDX, IDC_COM_IP_VERSION, m_comIPVersion);
	DDX_Control(pDX, IDC_COM_ONLINE, m_comOnlineState);
	DDX_Control(pDX, IDC_COM_ABNORMAL, m_comAbnormalState);
	DDX_Text(pDX, IDC_EDIT_SCHEDULE_NAME, m_csScheduleName);
	DDX_Text(pDX, IDC_EDIT_SCHEDULE_NO, m_dwScheduleNo);
	DDX_Text(pDX, IDC_EDIT_TEMPERATURE1, m_dwTemperature);
	DDX_Text(pDX, IDC_EDT_HARDVERSION, m_csHardVersion);
	DDX_Text(pDX, IDC_EDT_SYSVERSION, m_SysVersion);
	DDX_Text(pDX, IDC_EDT_TERM_ID, m_dwTermID);
	DDX_Text(pDX, IDC_EDT_TERM_NAME, m_csTermName);
	DDX_Text(pDX, IDC_EDT_VERSION, m_csVersion);
	DDX_Text(pDX, IDC_EDT_COND_CODE, m_CondCode);
	DDX_Text(pDX, IDC_EDT_REG_TIME, m_csRegTime);
	DDX_Text(pDX, IDC_COM_ADDR_FORMAT_TYPE, m_csAddrFormatType);
	DDX_Text(pDX, IDC_EDT_HOST_NAME, m_csHostName);
	DDX_Text(pDX, IDC_COM_IP_VERSION, m_csIPVersion);
	DDX_Text(pDX, IDC_EDT_IP4_ADDR, m_csIPv4);
	DDX_Text(pDX, IDC_EDT_IP6_ADDR, m_csIPv6);
	DDX_Text(pDX, IDC_EDT_MAC_ADDR, m_csMacAddr);
	DDX_Text(pDX, IDC_EDT_DISTRIBUTE_SERVER_URL, m_csServerURL);
	DDX_Text(pDX, IDC_COM_ONLINE, m_csOnlineState);
	DDX_Text(pDX, IDC_COM_ABNORMAL, m_csAbnormalState);
	DDX_Check(pDX, IDC_CHECK_SWITCH, m_bySwitch);
	DDX_Check(pDX, IDC_CHECK_VOLUM, m_byVolum);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgTermState, CDialog)
	//{{AFX_MSG_MAP(DlgTermState)
	ON_BN_CLICKED(IDC_RAD_GET_ONE, OnRadGetOne)
	ON_BN_CLICKED(IDC_RAD_GET_MORE, OnRadGetMore)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_NOTIFY(NM_CLICK, IDC_LIST_TERM_STATUS, OnClickLstTermInfo)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgTermState message handlers


BOOL CDlgTermState::OnInitDialog()
{
    CDialog::OnInitDialog();

	m_pListTerm = (CListCtrl*)GetDlgItem(IDC_LIST_TERM_STATUS);
	m_pListCPU  = (CListCtrl*)GetDlgItem(IDC_LIST_CPU);
	m_pListMem  = (CListCtrl*)GetDlgItem(IDC_LIST_MEM);
	m_pListDisk  = (CListCtrl*)GetDlgItem(IDC_LIST_DISK1);

	m_comAddrFormatType.InsertString(0, _T("ipaddress"));
    m_comAddrFormatType.InsertString(1, _T("hostname"));
	m_comAddrFormatType.SetCurSel(0);

	m_comIPVersion.InsertString(0, _T("v4"));
    m_comIPVersion.InsertString(1, _T("v6"));
	m_comIPVersion.InsertString(2, _T("dual"));
	m_comIPVersion.SetCurSel(0);

	m_comOnlineState.InsertString(0, _T("online"));
    m_comOnlineState.InsertString(1, _T("offline"));
	m_comOnlineState.SetCurSel(0);

	m_comAbnormalState.InsertString(0, _T("normal"));
    m_comAbnormalState.InsertString(1, _T("abnormal"));
	m_comAbnormalState.SetCurSel(0);

	LONG lStyle;
    lStyle = GetWindowLong(m_pListTerm->m_hWnd, GWL_STYLE);//获取当前窗口style
    lStyle &= ~LVS_TYPEMASK; //清除显示方式位
    lStyle |= LVS_REPORT;    //设置style
    SetWindowLong(m_pListTerm->m_hWnd, GWL_STYLE, lStyle);//设置style
	SetWindowLong(m_pListCPU->m_hWnd, GWL_STYLE, lStyle);//设置style
	SetWindowLong(m_pListMem->m_hWnd, GWL_STYLE, lStyle);//设置style
	SetWindowLong(m_pListDisk->m_hWnd, GWL_STYLE, lStyle);//设置style
    
    DWORD dwStyle = m_pListTerm->GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
    dwStyle |= LVS_EX_GRIDLINES;    //网格线（只适用与report风格的listctrl）
    m_pListTerm->SetExtendedStyle(dwStyle); //设置扩展风格
	m_pListCPU->SetExtendedStyle(dwStyle); //设置扩展风格
	m_pListMem->SetExtendedStyle(dwStyle); //设置扩展风格
	m_pListDisk->SetExtendedStyle(dwStyle);
	
	
    m_pListTerm->InsertColumn(0, "Index", LVCFMT_LEFT, 50);//插入列
    m_pListTerm->InsertColumn(1, "ID", LVCFMT_LEFT, 100);
	m_pListTerm->InsertColumn(2, "TermName", LVCFMT_LEFT, 100);

	m_pListCPU->InsertColumn(0, "Index", LVCFMT_LEFT, 50);//插入列
    m_pListCPU->InsertColumn(1, "CPU描述", LVCFMT_LEFT, 100);
    m_pListCPU->InsertColumn(2, "CPU使用率", LVCFMT_LEFT, 100);

	m_pListMem->InsertColumn(0, "Index", LVCFMT_LEFT, 50);//插入列
    m_pListMem->InsertColumn(1, "内存描述", LVCFMT_LEFT, 100);
    m_pListMem->InsertColumn(2, "内存已使用(MB)", LVCFMT_LEFT, 100);
	m_pListMem->InsertColumn(3, "内存可用(MB)", LVCFMT_LEFT, 100);


	m_pListDisk->InsertColumn(0, "Index", LVCFMT_LEFT, 50);//插入列
    m_pListDisk->InsertColumn(1, "Disk描述", LVCFMT_LEFT, 100);
    m_pListDisk->InsertColumn(2, "Disk存已使用(MB)", LVCFMT_LEFT, 100);
	m_pListDisk->InsertColumn(3, "Disk可用(MB)", LVCFMT_LEFT, 100);


	GetDlgItem(IDC_BTN_GET)->EnableWindow(FALSE);
	
	
	UpdateData(FALSE);


	return TRUE;
}

void CDlgTermState::OnRadGetOne()
{
	m_bGetOne = TRUE;
	
	GetDlgItem(IDC_LIST_TERM_STATUS)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_GET)->EnableWindow(TRUE);
}

void CDlgTermState::OnRadGetMore()
{
	m_bGetOne = FALSE;
	GetDlgItem(IDC_LIST_TERM_STATUS)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_GET)->EnableWindow(TRUE);
}

void CDlgTermState::OnBtnGet()
{
	UpdateData(TRUE);
	
	m_dwTermStateCount = 0;
	m_dwCpuIndex = 0;
	m_dwMemIndex = 0;
	memset(m_paTermState, 0, sizeof(TERM_STATE)*MAX_NUM_TERMINAL);
	
	memset(&m_szRequestURL, '\0' ,sizeof(m_szRequestURL));
	m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;
	memset(m_pXMLResultBuf, 0, ISAPI_DATA_LEN);
	m_dwXMLResultBufLen = ISAPI_DATA_LEN;
	memset(&m_szXMLStatus, '\0', sizeof(m_szXMLStatus));

	//调用接口
	NET_DVR_XML_CONFIG_INPUT struXMLCfgInput = {0};
	struXMLCfgInput.dwSize = sizeof(struXMLCfgInput);
	if (m_bGetOne)
	{
		sprintf((char*)m_szRequestURL, "GET /ISAPI/Publish/TerminalMgr/terminals/state/%d\r\n", m_dwTermID);
	}
	else
	{
		sprintf((char*)m_szRequestURL, "GET /ISAPI/Publish/TerminalMgr/terminals/state\r\n");
	}
	
	struXMLCfgInput.lpRequestUrl = (char*)m_szRequestURL;
	struXMLCfgInput.dwRequestUrlLen = strlen(m_szRequestURL);
	struXMLCfgInput.lpInBuffer      = NULL;
	struXMLCfgInput.dwInBufferSize  = 0;
	
	NET_DVR_XML_CONFIG_OUTPUT struXMLCfgOutput = {0};
	struXMLCfgOutput.dwSize = sizeof(struXMLCfgOutput);
	struXMLCfgOutput.lpOutBuffer = (char*)m_pXMLResultBuf;
	struXMLCfgOutput.dwOutBufferSize = ISAPI_DATA_LEN;
	struXMLCfgOutput.lpStatusBuffer = (char*)m_szXMLStatus;
	struXMLCfgOutput.dwStatusSize = sizeof(m_szXMLStatus);
	
	LPNET_DVR_XML_CONFIG_OUTPUT lpXMLCfgOutput = &struXMLCfgOutput;
	
	if (NET_DVR_STDXMLConfig(m_lUserID, &struXMLCfgInput, lpXMLCfgOutput))
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");			
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		return;
    }

	//解析获取数据
	CXmlBase struXmlResult;
	
	if (struXmlResult.Parse((char*)m_pXMLResultBuf))
	{
		m_pListTerm->DeleteAllItems();
		m_pListCPU->DeleteAllItems();
		m_pListMem->DeleteAllItems();
        m_pListDisk->DeleteAllItems();

		if (m_bGetOne)
		{
			//获取一个
			if(struXmlResult.FindElem("TerminalState") && struXmlResult.IntoElem())
			{
				if (struXmlResult.FindElem("id"))
				{
					ConvertSingleNodeData(&m_paTermState[0].dwID, struXmlResult, "id", NODE_STRING_TO_INT);
				}
				
				if (struXmlResult.FindElem("terminalName"))
				{
					ConvertSingleNodeData((char*)&m_paTermState[0].szTermName, struXmlResult, "terminalName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
				}

				if (struXmlResult.FindElem("PlayerState") && struXmlResult.IntoElem())
				{
					if (struXmlResult.FindElem("BasicInfo") && struXmlResult.IntoElem())
					{
						if (struXmlResult.FindElem("version"))
						{
							ConvertSingleNodeData((char*)&m_paTermState[0].szVersion, struXmlResult, "version", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						}

						if (struXmlResult.FindElem("hardwareVersion"))
						{
							ConvertSingleNodeData((char*)&m_paTermState[0].szHardwareVersion, struXmlResult, "hardwareVersion", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						}

						if (struXmlResult.FindElem("systemVersion"))
						{
							ConvertSingleNodeData((char*)&m_paTermState[0].szSystemVersion, struXmlResult, "systemVersion", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						}

						if (struXmlResult.FindElem("characteristicCode"))
						{
							ConvertSingleNodeData((char*)&m_paTermState[0].szCondCode, struXmlResult, "characteristicCode", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						}

						if (struXmlResult.FindElem("registerTime"))
						{
							ConvertSingleNodeData((char*)&m_paTermState[0].szRegTime, struXmlResult, "registerTime", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						}
						struXmlResult.OutOfElem();
					}//BasicInfo

					if (struXmlResult.FindElem("WorkState") && struXmlResult.IntoElem())
					{
						if (struXmlResult.FindElem("TerminalAddress") && struXmlResult.IntoElem())
						{
							if (struXmlResult.FindElem("addressingFormatType"))
							{
								ConvertSingleNodeData((char*)&m_paTermState[0].szAddrFormatType, struXmlResult, "addressingFormatType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							}
							
							if (struXmlResult.FindElem("hostName"))
							{
								ConvertSingleNodeData((char*)&m_paTermState[0].szHostName, struXmlResult, "hostName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							}
							
							if (struXmlResult.FindElem("IpAddress") && struXmlResult.IntoElem())
							{
								if (struXmlResult.FindElem("ipVersion"))
								{
									ConvertSingleNodeData((char*)&m_paTermState[0].szIPVersion, struXmlResult, "ipVersion", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								if (struXmlResult.FindElem("ipAddress"))
								{
									ConvertSingleNodeData((char*)&m_paTermState[0].szIPv4, struXmlResult, "ipAddress", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								if (struXmlResult.FindElem("ipv6Address"))
								{
									ConvertSingleNodeData((char*)&m_paTermState[0].szIPv6, struXmlResult, "ipv6Address", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								
								struXmlResult.OutOfElem();
							}//IpAddress
							
							struXmlResult.OutOfElem();

						}//ipAddress

						if (struXmlResult.FindElem("macAddress"))
						{
							ConvertSingleNodeData((char*)&m_paTermState[0].szMacAddr, struXmlResult, "macAddress", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						}
						if (struXmlResult.FindElem("distributeServerUrl"))
						{
							ConvertSingleNodeData((char*)&m_paTermState[0].szServerURL, struXmlResult, "distributeServerUrl", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						}
						if (struXmlResult.FindElem("onlineState"))
						{
							ConvertSingleNodeData((char*)&m_paTermState[0].szOnlineState, struXmlResult, "onlineState", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						}
						if (struXmlResult.FindElem("abnormalState"))
						{
							ConvertSingleNodeData((char*)&m_paTermState[0].szAbnormalState, struXmlResult, "abnormalState", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						}

						if (struXmlResult.FindElem("CPUList") && struXmlResult.IntoElem())
						{
							if (struXmlResult.FindElem("CPU") && struXmlResult.IntoElem())
							{
								if (struXmlResult.FindElem("cpuDescription"))
								{
									ConvertSingleNodeData((char*)&m_paTermState[0].aCpuInfo[m_paTermState[0].dwCpuInfoCount].szCpuDesc, struXmlResult, "cpuDescription", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}

								if (struXmlResult.FindElem("cpuUtilization"))
								{
									ConvertSingleNodeData(&m_paTermState[0].aCpuInfo[m_paTermState[0].dwCpuInfoCount].dwCpuUtil, struXmlResult, "cpuUtilization", NODE_STRING_TO_INT);
								}

								m_csCpuDesc = m_paTermState[0].aCpuInfo[m_paTermState[0].dwCpuInfoCount].szCpuDesc;
								m_csCpuUsage.Format("%d", m_paTermState[0].aCpuInfo[m_paTermState[0].dwCpuInfoCount].dwCpuUtil);

								CString csInfo;
								csInfo.Format("%d", m_paTermState[0].dwCpuInfoCount+1);

								int nRow = m_pListCPU->InsertItem(m_paTermState[0].dwCpuInfoCount, csInfo);//插入行 
								m_pListCPU->SetItemText(nRow, 1, m_csCpuDesc);//设置数据
								m_pListCPU->SetItemText(nRow, 2, m_csCpuUsage);//设置数据

								m_paTermState[0].dwCpuInfoCount++;
								struXmlResult.OutOfElem();

								while (struXmlResult.NextSibElem() && struXmlResult.IntoElem())
								{
									if (struXmlResult.FindElem("cpuDescription"))
									{
										ConvertSingleNodeData((char*)&m_paTermState[0].aCpuInfo[m_paTermState[0].dwCpuInfoCount].szCpuDesc, struXmlResult, "cpuDescription", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
									}
									
									if (struXmlResult.FindElem("cpuUtilization"))
									{
										ConvertSingleNodeData(&m_paTermState[0].aCpuInfo[m_paTermState[0].dwCpuInfoCount].dwCpuUtil, struXmlResult, "cpuUtilization", NODE_STRING_TO_INT);
									}
									
									m_csCpuDesc = m_paTermState[0].aCpuInfo[m_paTermState[0].dwCpuInfoCount].szCpuDesc;
									m_csCpuUsage.Format("%d", m_paTermState[0].aCpuInfo[m_paTermState[0].dwCpuInfoCount].dwCpuUtil);
									
									CString csInfo;
									csInfo.Format("%d", m_paTermState[0].dwCpuInfoCount+1);
									
									int nRow = m_pListCPU->InsertItem(m_paTermState[0].dwCpuInfoCount, csInfo);//插入行 
									m_pListCPU->SetItemText(nRow, 1, m_csCpuDesc);//设置数据
									m_pListCPU->SetItemText(nRow, 2, m_csCpuUsage);//设置数据
									
									m_paTermState[0].dwCpuInfoCount++;
									struXmlResult.OutOfElem();
								}

							}//CPU

							struXmlResult.OutOfElem();
						}//CPUList

						if (struXmlResult.FindElem("MemoryList") && struXmlResult.IntoElem())
						{
							if (struXmlResult.FindElem("Memory") && struXmlResult.IntoElem())
							{
								if (struXmlResult.FindElem("memoryDescription"))
								{
									ConvertSingleNodeData((char*)&m_paTermState[0].aMemInfo[m_paTermState[0].dwMemInfoCount].szMemDesc, struXmlResult, "memoryDescription", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								
								if (struXmlResult.FindElem("memoryUsage"))
								{
									ConvertSingleNodeData(&m_paTermState[0].aMemInfo[m_paTermState[0].dwMemInfoCount].fMemUsage, struXmlResult, "memoryUsage", NODE_STRING_TO_FLOAT);
								}

								if (struXmlResult.FindElem("memoryAvailable"))
								{
									ConvertSingleNodeData(&m_paTermState[0].aMemInfo[m_paTermState[0].dwMemInfoCount].fMemAvailable, struXmlResult, "memoryAvailable", NODE_STRING_TO_FLOAT);
								}

								m_csMemDesc = m_paTermState[0].aMemInfo[m_paTermState[0].dwMemInfoCount].szMemDesc;
								m_csMemUsage.Format("%f", m_paTermState[0].aMemInfo[m_paTermState[0].dwMemInfoCount].fMemUsage);
								m_csMemAvailable.Format("%f", m_paTermState[0].aMemInfo[m_paTermState[0].dwMemInfoCount].fMemAvailable);
								
								CString csInfo;
								csInfo.Format("%d", m_paTermState[0].dwMemInfoCount+1);
								
								int nRow = m_pListMem->InsertItem(m_paTermState[0].dwMemInfoCount, csInfo);//插入行 
								m_pListMem->SetItemText(nRow, 1, m_csMemDesc);//设置数据
								m_pListMem->SetItemText(nRow, 2, m_csMemUsage);//设置数据
								m_pListMem->SetItemText(nRow, 3, m_csMemAvailable);//设置数据
								
								m_paTermState[0].dwMemInfoCount++;
								struXmlResult.OutOfElem();

								while (struXmlResult.NextSibElem() && struXmlResult.IntoElem())
								{
									if (struXmlResult.FindElem("memoryDescription"))
									{
										ConvertSingleNodeData((char*)&m_paTermState[0].aMemInfo[m_paTermState[0].dwMemInfoCount].szMemDesc, struXmlResult, "memoryDescription", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
									}
									
									if (struXmlResult.FindElem("memoryUsage"))
									{
										ConvertSingleNodeData(&m_paTermState[0].aMemInfo[m_paTermState[0].dwMemInfoCount].fMemUsage, struXmlResult, "memoryUsage", NODE_STRING_TO_FLOAT);
									}
									
									if (struXmlResult.FindElem("memoryAvailable"))
									{
										ConvertSingleNodeData(&m_paTermState[0].aMemInfo[m_paTermState[0].dwMemInfoCount].fMemAvailable, struXmlResult, "memoryAvailable", NODE_STRING_TO_FLOAT);
									}
									
									m_csMemDesc = m_paTermState[0].aMemInfo[m_paTermState[0].dwMemInfoCount].szMemDesc;
									m_csMemUsage.Format("%f", m_paTermState[0].aMemInfo[m_paTermState[0].dwMemInfoCount].fMemUsage);
									m_csMemAvailable.Format("%f", m_paTermState[0].aMemInfo[m_paTermState[0].dwMemInfoCount].fMemAvailable);
									
									CString csInfo;
									csInfo.Format("%d", m_paTermState[0].dwMemInfoCount+1);
									
									int nRow = m_pListMem->InsertItem(m_paTermState[0].dwMemInfoCount, csInfo);//插入行 
									m_pListMem->SetItemText(nRow, 1, m_csMemDesc);//设置数据
									m_pListMem->SetItemText(nRow, 2, m_csMemUsage);//设置数据
									m_pListMem->SetItemText(nRow, 3, m_csMemAvailable);//设置数据
									
									m_paTermState[0].dwMemInfoCount++;
									struXmlResult.OutOfElem();
								}
								
							}//Memory
							
							struXmlResult.OutOfElem();
						}//MemoryList
						if(struXmlResult.FindElem("DiskList") && struXmlResult.IntoElem())
						{
							if (struXmlResult.FindElem("Disk") && struXmlResult.IntoElem())
							{
								if (struXmlResult.FindElem("diskDescription"))
								{
									ConvertSingleNodeData((char*)&m_paTermState[0].aDiskInfo[m_paTermState[0].dwDiskInfoCount].szDiskDesc, struXmlResult, "diskDescription", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								
								if (struXmlResult.FindElem("diskUsage"))
								{
									ConvertSingleNodeData(&m_paTermState[0].aDiskInfo[m_paTermState[0].dwDiskInfoCount].fDiskUsage, struXmlResult, "diskUsage", NODE_STRING_TO_FLOAT);
								}
								
								if (struXmlResult.FindElem("diskAvailable"))
								{
									ConvertSingleNodeData(&m_paTermState[0].aDiskInfo[m_paTermState[0].dwDiskInfoCount].fDiskAvailable, struXmlResult, "diskAvailable", NODE_STRING_TO_FLOAT);
								}
								
								m_csDiskDesc = m_paTermState[0].aDiskInfo[m_paTermState[0].dwDiskInfoCount].szDiskDesc;
								m_csDiskUsage.Format("%f", m_paTermState[0].aDiskInfo[m_paTermState[0].dwDiskInfoCount].fDiskUsage);
								m_csDiskAvailable.Format("%f", m_paTermState[0].aDiskInfo[m_paTermState[0].dwDiskInfoCount].fDiskAvailable);
								
								CString csInfo;
								csInfo.Format("%d", m_paTermState[0].dwDiskInfoCount+1);
								
								int nRow = m_pListDisk->InsertItem(m_paTermState[0].dwDiskInfoCount, csInfo);//插入行 
								m_pListDisk->SetItemText(nRow, 1, m_csDiskDesc);//设置数据
								m_pListDisk->SetItemText(nRow, 2, m_csDiskUsage);//设置数据
								m_pListDisk->SetItemText(nRow, 3, m_csDiskAvailable);//设置数据
								m_paTermState[0].dwDiskInfoCount++;
								struXmlResult.OutOfElem();
								
								while (struXmlResult.NextSibElem() && struXmlResult.IntoElem())
								{
									if (struXmlResult.FindElem("diskDescription"))
									{
										ConvertSingleNodeData((char*)&m_paTermState[0].aDiskInfo[m_paTermState[0].dwDiskInfoCount].szDiskDesc, struXmlResult, "diskDescription", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
									}
									
									if (struXmlResult.FindElem("diskUsage"))
									{
										ConvertSingleNodeData(&m_paTermState[0].aDiskInfo[m_paTermState[0].dwDiskInfoCount].fDiskUsage, struXmlResult, "diskUsage", NODE_STRING_TO_FLOAT);
									}
									
									if (struXmlResult.FindElem("diskAvailable"))
									{
										ConvertSingleNodeData(&m_paTermState[0].aDiskInfo[m_paTermState[0].dwDiskInfoCount].fDiskAvailable, struXmlResult, "diskAvailable", NODE_STRING_TO_FLOAT);
									}
									m_csDiskDesc = m_paTermState[0].aDiskInfo[m_paTermState[0].dwDiskInfoCount].szDiskDesc;
									m_csDiskUsage.Format("%f", m_paTermState[0].aDiskInfo[m_paTermState[0].dwDiskInfoCount].fDiskUsage);
									m_csDiskAvailable.Format("%f", m_paTermState[0].aDiskInfo[m_paTermState[0].dwDiskInfoCount].fDiskAvailable);
									
									CString csInfo;
									csInfo.Format("%d", m_paTermState[0].dwDiskInfoCount+1);
									
									int nRow = m_pListDisk->InsertItem(m_paTermState[0].dwDiskInfoCount, csInfo);//插入行 
									m_pListDisk->SetItemText(nRow, 1, m_csDiskDesc);//设置数据
									m_pListDisk->SetItemText(nRow, 2, m_csDiskUsage);//设置数据
									m_pListDisk->SetItemText(nRow, 3, m_csDiskAvailable);//设置数据
									m_paTermState[0].dwDiskInfoCount++;
									struXmlResult.OutOfElem();
								}
								
							}//Disk
							
							struXmlResult.OutOfElem();
						}//DiskList
						
						if (struXmlResult.FindElem("temperature"))
						{
							ConvertSingleNodeData(&m_paTermState[0].dwTemperature, struXmlResult, "temperature", NODE_STRING_TO_INT);
						}
						m_dwTemperature = m_paTermState[0].dwTemperature;

						struXmlResult.OutOfElem();
					}//WorkState

					if (struXmlResult.FindElem("PlayInfo") && struXmlResult.IntoElem())
					{
						ConvertSingleNodeData(&m_paTermState[0].struPlayInfo.dwScheduleNo, struXmlResult, "scheduleNo", NODE_STRING_TO_INT);
						ConvertSingleNodeData(m_paTermState[0].struPlayInfo.szScheduleName, struXmlResult, "scheduleName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						struXmlResult.OutOfElem();
					}

                    if(struXmlResult.FindElem("TimingPlan")&& struXmlResult.IntoElem())
                    {
                        if(struXmlResult.FindElem("SwitchPlan")&& struXmlResult.IntoElem())
                        {
                            ConvertSingleNodeData(&m_paTermState[0].struTimingPlan.bySwitchEnabled, struXmlResult, "enabled", NODE_STRING_TO_BOOL);
                            struXmlResult.OutOfElem();
                        }
                        if(struXmlResult.FindElem("VolumePlan")&& struXmlResult.IntoElem())
                        {
                            ConvertSingleNodeData(&m_paTermState[0].struTimingPlan.byVolumeEnabled, struXmlResult, "enabled", NODE_STRING_TO_BOOL);
                            struXmlResult.OutOfElem();
                        }
                        struXmlResult.OutOfElem();

                    }

					struXmlResult.OutOfElem();
				}//PlayerState

				struXmlResult.OutOfElem();
			}	
			m_csTermName = m_paTermState[0].szTermName;
			
			m_csVersion = m_paTermState[0].szVersion;
			m_CondCode  = m_paTermState[0].szCondCode;
			m_csRegTime = m_paTermState[0].szRegTime;
			m_csHardVersion = m_paTermState[0].szHardwareVersion;
			m_SysVersion = m_paTermState[0].szSystemVersion;
			
			m_csAddrFormatType = m_paTermState[0].szAddrFormatType;
			m_csHostName = m_paTermState[0].szHostName;
			m_csIPVersion = m_paTermState[0].szIPVersion;
			m_csIPv4 = m_paTermState[0].szIPv4;
			m_csIPv6 = m_paTermState[0].szIPv6;
			
			m_csMacAddr = m_paTermState[0].szMacAddr;
			m_csServerURL = m_paTermState[0].szServerURL;
			m_csOnlineState = m_paTermState[0].szOnlineState;
			m_csAbnormalState = m_paTermState[0].szAbnormalState;

			m_dwScheduleNo = m_paTermState[0].struPlayInfo.dwScheduleNo;
			m_csScheduleName = m_paTermState[0].struPlayInfo.szScheduleName;
			m_bySwitch = m_paTermState[0].struTimingPlan.bySwitchEnabled;
			m_byVolum = m_paTermState[0].struTimingPlan.byVolumeEnabled;
		}
		else
		{
			//获取多个
			if(struXmlResult.FindElem("TerminalStateList") && struXmlResult.IntoElem())
			{
				if (struXmlResult.FindElem("TerminalState") && struXmlResult.IntoElem())
				{
					if (struXmlResult.FindElem("id"))
					{
						ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].dwID, struXmlResult, "id", NODE_STRING_TO_INT);
					}
					
					if (struXmlResult.FindElem("terminalName"))
					{
						ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szTermName, struXmlResult, "terminalName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
					}

					if (struXmlResult.FindElem("PlayerState") && struXmlResult.IntoElem())
					{
						if (struXmlResult.FindElem("BasicInfo") && struXmlResult.IntoElem())
						{
							if (struXmlResult.FindElem("version"))
							{
								ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szVersion, struXmlResult, "version", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							}

							if (struXmlResult.FindElem("hardwareVersion"))
							{
								ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szHardwareVersion, struXmlResult, "hardwareVersion", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							}
							
							if (struXmlResult.FindElem("systemVersion"))
							{
								ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szSystemVersion, struXmlResult, "systemVersion", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						}

							if (struXmlResult.FindElem("characteristicCode"))
							{
								ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szCondCode, struXmlResult, "characteristicCode", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							}

							if (struXmlResult.FindElem("registerTime"))
							{
								ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szRegTime, struXmlResult, "registerTime", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							}
							struXmlResult.OutOfElem();
						}//BasicInfo

						if (struXmlResult.FindElem("WorkState") && struXmlResult.IntoElem())
						{
							if (struXmlResult.FindElem("TerminalAddress") && struXmlResult.IntoElem())
							{
								if (struXmlResult.FindElem("addressingFormatType"))
								{
									ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szAddrFormatType, struXmlResult, "addressingFormatType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								
								if (struXmlResult.FindElem("hostName"))
								{
									ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szHostName, struXmlResult, "hostName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								
								if (struXmlResult.FindElem("IpAddress") && struXmlResult.IntoElem())
								{
									if (struXmlResult.FindElem("ipVersion"))
									{
										ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szIPVersion, struXmlResult, "ipVersion", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
									}
									if (struXmlResult.FindElem("ipAddress"))
									{
										ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szIPv4, struXmlResult, "ipAddress", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
									}
									if (struXmlResult.FindElem("ipv6Address"))
									{
										ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szIPv6, struXmlResult, "ipv6Address", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
									}
									
									struXmlResult.OutOfElem();
								}//IpAddress
								
								struXmlResult.OutOfElem();

							}//ipAddress

							if (struXmlResult.FindElem("macAddress"))
							{
								ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szMacAddr, struXmlResult, "macAddress", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							}
							if (struXmlResult.FindElem("distributeServerUrl"))
							{
								ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szServerURL, struXmlResult, "distributeServerUrl", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							}
							if (struXmlResult.FindElem("onlineState"))
							{
								ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szOnlineState, struXmlResult, "onlineState", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							}
							if (struXmlResult.FindElem("abnormalState"))
							{
								ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szAbnormalState, struXmlResult, "abnormalState", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							}

							if (struXmlResult.FindElem("CPUList") && struXmlResult.IntoElem())
							{
								if (struXmlResult.FindElem("CPU") && struXmlResult.IntoElem())
								{
									if (struXmlResult.FindElem("cpuDescription"))
									{
										ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].aCpuInfo[m_paTermState[m_dwTermStateCount].dwCpuInfoCount].szCpuDesc, struXmlResult, "cpuDescription", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
									}

									if (struXmlResult.FindElem("cpuUtilization"))
									{
										ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].aCpuInfo[m_paTermState[m_dwTermStateCount].dwCpuInfoCount].dwCpuUtil, struXmlResult, "cpuUtilization", NODE_STRING_TO_INT);
									}

									m_paTermState[m_dwTermStateCount].dwCpuInfoCount++;
									struXmlResult.OutOfElem();

									while (struXmlResult.NextSibElem() && struXmlResult.IntoElem())
									{
										if (struXmlResult.FindElem("cpuDescription"))
										{
											ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].aCpuInfo[m_paTermState[m_dwTermStateCount].dwCpuInfoCount].szCpuDesc, struXmlResult, "cpuDescription", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
										}
										
										if (struXmlResult.FindElem("cpuUtilization"))
										{
											ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].aCpuInfo[m_paTermState[m_dwTermStateCount].dwCpuInfoCount].dwCpuUtil, struXmlResult, "cpuUtilization", NODE_STRING_TO_INT);
										}
										
										m_paTermState[m_dwTermStateCount].dwCpuInfoCount++;
										struXmlResult.OutOfElem();
									}

								}//CPU

								struXmlResult.OutOfElem();
							}//CPUList

							if (struXmlResult.FindElem("MemoryList") && struXmlResult.IntoElem())
							{
								if (struXmlResult.FindElem("Memory") && struXmlResult.IntoElem())
								{
									if (struXmlResult.FindElem("memoryDescription"))
									{
										ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].aMemInfo[m_paTermState[m_dwTermStateCount].dwMemInfoCount].szMemDesc, struXmlResult, "memoryDescription", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
									}
									
									if (struXmlResult.FindElem("memoryUsage"))
									{
										ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].aMemInfo[m_paTermState[m_dwTermStateCount].dwMemInfoCount].fMemUsage, struXmlResult, "memoryUsage", NODE_STRING_TO_FLOAT);
									}

									if (struXmlResult.FindElem("memoryAvailable"))
									{
										ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].aMemInfo[m_paTermState[m_dwTermStateCount].dwMemInfoCount].fMemAvailable, struXmlResult, "memoryAvailable", NODE_STRING_TO_FLOAT);
									}

									m_paTermState[m_dwTermStateCount].dwMemInfoCount++;
									struXmlResult.OutOfElem();

									while (struXmlResult.NextSibElem() && struXmlResult.IntoElem())
									{
										if (struXmlResult.FindElem("memoryDescription"))
										{
											ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].aMemInfo[m_paTermState[m_dwTermStateCount].dwMemInfoCount].szMemDesc, struXmlResult, "memoryDescription", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
										}
										
										if (struXmlResult.FindElem("memoryUsage"))
										{
											ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].aMemInfo[m_paTermState[m_dwTermStateCount].dwMemInfoCount].fMemUsage, struXmlResult, "memoryUsage", NODE_STRING_TO_FLOAT);
										}
										
										if (struXmlResult.FindElem("memoryAvailable"))
										{
											ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].aMemInfo[m_paTermState[m_dwTermStateCount].dwMemInfoCount].fMemAvailable, struXmlResult, "memoryAvailable", NODE_STRING_TO_FLOAT);
										}

										m_paTermState[m_dwTermStateCount].dwMemInfoCount++;
										struXmlResult.OutOfElem();
									}
									
								}//Memory
								
								struXmlResult.OutOfElem();
							}//MemoryList
							if(struXmlResult.FindElem("DiskList") && struXmlResult.IntoElem())
							{
								if (struXmlResult.FindElem("Disk") && struXmlResult.IntoElem())
								{
									if (struXmlResult.FindElem("diskDescription"))
									{
										ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].aDiskInfo[m_paTermState[m_dwTermStateCount].dwDiskInfoCount].szDiskDesc, struXmlResult, "diskDescription", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
									}
									
									if (struXmlResult.FindElem("diskUsage"))
									{
										ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].aDiskInfo[m_paTermState[m_dwTermStateCount].dwDiskInfoCount].fDiskUsage, struXmlResult, "diskUsage", NODE_STRING_TO_FLOAT);
									}
									
									if (struXmlResult.FindElem("diskAvailable"))
									{
										ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].aDiskInfo[m_paTermState[m_dwTermStateCount].dwDiskInfoCount].fDiskAvailable, struXmlResult, "diskAvailable", NODE_STRING_TO_FLOAT);
									}
									
									m_paTermState[m_dwTermStateCount].dwDiskInfoCount++;
									struXmlResult.OutOfElem();
									
									while (struXmlResult.NextSibElem() && struXmlResult.IntoElem())
									{
										if (struXmlResult.FindElem("diskDescription"))
										{
											ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].aDiskInfo[m_paTermState[m_dwTermStateCount].dwDiskInfoCount].szDiskDesc, struXmlResult, "diskDescription", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
										}
										
										if (struXmlResult.FindElem("diskUsage"))
										{
											ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].aDiskInfo[m_paTermState[m_dwTermStateCount].dwDiskInfoCount].fDiskUsage, struXmlResult, "diskUsage", NODE_STRING_TO_FLOAT);
										}
										
										if (struXmlResult.FindElem("diskAvailable"))
										{
											ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].aDiskInfo[m_paTermState[m_dwTermStateCount].dwDiskInfoCount].fDiskAvailable, struXmlResult, "diskAvailable", NODE_STRING_TO_FLOAT);
										}
										
										m_paTermState[m_dwTermStateCount].dwDiskInfoCount++;
										struXmlResult.OutOfElem();
									}
									
								}//Disk
								
								struXmlResult.OutOfElem();
							}//DiskList
							
							if (struXmlResult.FindElem("temperature"))
							{
								ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].dwTemperature, struXmlResult, "temperature", NODE_STRING_TO_INT);
							}

							struXmlResult.OutOfElem();
						}//WorkState

						if (struXmlResult.FindElem("PlayInfo") && struXmlResult.IntoElem())
						{
							ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].struPlayInfo.dwScheduleNo, struXmlResult, "scheduleNo", NODE_STRING_TO_INT);
							ConvertSingleNodeData(m_paTermState[m_dwTermStateCount].struPlayInfo.szScheduleName, struXmlResult, "scheduleName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							struXmlResult.OutOfElem();
						}

                        if(struXmlResult.FindElem("TimingPlan")&& struXmlResult.IntoElem())
                        {
                            if(struXmlResult.FindElem("SwitchPlan")&& struXmlResult.IntoElem())
                            {
                                ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].struTimingPlan.bySwitchEnabled, struXmlResult, "enabled", NODE_STRING_TO_BOOL);
                                struXmlResult.OutOfElem();
                            }
                            if(struXmlResult.FindElem("VolumePlan")&& struXmlResult.IntoElem())
                            {
                                ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].struTimingPlan.byVolumeEnabled, struXmlResult, "enabled", NODE_STRING_TO_BOOL);
                                struXmlResult.OutOfElem();
                            }
                            struXmlResult.OutOfElem();
                            
                        }

						struXmlResult.OutOfElem();
					}//PlayerState

					struXmlResult.OutOfElem();

					//Term添加
					CString csInfo;
					csInfo.Format("%d", m_dwTermStateCount+1);
					
					int nRow = m_pListTerm->InsertItem(m_dwTermStateCount, csInfo);//插入行
					csInfo.Format("%d", m_paTermState[m_dwTermStateCount].dwID);
					m_pListTerm->SetItemText(nRow, 1, csInfo);//设置数据
					csInfo = m_paTermState[m_dwTermStateCount].szTermName;
					m_pListTerm->SetItemText(nRow, 2, csInfo);//设置数据
					
					m_dwTermStateCount++;

					while (struXmlResult.NextSibElem() && struXmlResult.IntoElem())
					{
						if (struXmlResult.FindElem("id"))
						{
							ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].dwID, struXmlResult, "id", NODE_STRING_TO_INT);
						}
						
						if (struXmlResult.FindElem("terminalName"))
						{
							ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szTermName, struXmlResult, "terminalName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						}
						
						if (struXmlResult.FindElem("PlayerState") && struXmlResult.IntoElem())
						{
							if (struXmlResult.FindElem("BasicInfo") && struXmlResult.IntoElem())
							{
								if (struXmlResult.FindElem("version"))
								{
									ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szVersion, struXmlResult, "version", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}

								if (struXmlResult.FindElem("hardwareVersion"))
								{
									ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szHardwareVersion, struXmlResult, "hardwareVersion", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}

								if (struXmlResult.FindElem("systemVersion"))
								{
									ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szSystemVersion, struXmlResult, "systemVersion", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								
								if (struXmlResult.FindElem("characteristicCode"))
								{
									ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szCondCode, struXmlResult, "characteristicCode", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								
								if (struXmlResult.FindElem("registerTime"))
								{
									ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szRegTime, struXmlResult, "registerTime", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								struXmlResult.OutOfElem();
							}//BasicInfo
							
							if (struXmlResult.FindElem("WorkState") && struXmlResult.IntoElem())
							{
								if (struXmlResult.FindElem("TerminalAddress") && struXmlResult.IntoElem())
								{
									if (struXmlResult.FindElem("addressingFormatType"))
									{
										ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szAddrFormatType, struXmlResult, "addressingFormatType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
									}
									
									if (struXmlResult.FindElem("hostName"))
									{
										ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szHostName, struXmlResult, "hostName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
									}
									
									if (struXmlResult.FindElem("IpAddress") && struXmlResult.IntoElem())
									{
										if (struXmlResult.FindElem("ipVersion"))
										{
											ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szIPVersion, struXmlResult, "ipVersion", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
										}
										if (struXmlResult.FindElem("ipAddress"))
										{
											ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szIPv4, struXmlResult, "ipAddress", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
										}
										if (struXmlResult.FindElem("ipv6Address"))
										{
											ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szIPv6, struXmlResult, "ipv6Address", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
										}
										
										struXmlResult.OutOfElem();
									}//IpAddress
									
									struXmlResult.OutOfElem();
									
								}//ipAddress
								
								if (struXmlResult.FindElem("macAddress"))
								{
									ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szMacAddr, struXmlResult, "macAddress", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								if (struXmlResult.FindElem("distributeServerUrl"))
								{
									ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szServerURL, struXmlResult, "distributeServerUrl", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								if (struXmlResult.FindElem("onlineState"))
								{
									ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szOnlineState, struXmlResult, "onlineState", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								if (struXmlResult.FindElem("abnormalState"))
								{
									ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].szAbnormalState, struXmlResult, "abnormalState", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								
								if (struXmlResult.FindElem("CPUList") && struXmlResult.IntoElem())
								{
									if (struXmlResult.FindElem("CPU") && struXmlResult.IntoElem())
									{
										if (struXmlResult.FindElem("cpuDescription"))
										{
											ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].aCpuInfo[m_paTermState[m_dwTermStateCount].dwCpuInfoCount].szCpuDesc, struXmlResult, "cpuDescription", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
										}
										
										if (struXmlResult.FindElem("cpuUtilization"))
										{
											ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].aCpuInfo[m_paTermState[m_dwTermStateCount].dwCpuInfoCount].dwCpuUtil, struXmlResult, "cpuUtilization", NODE_STRING_TO_INT);
										}
										
										m_paTermState[m_dwTermStateCount].dwCpuInfoCount++;
										struXmlResult.OutOfElem();
										
										while (struXmlResult.NextSibElem() && struXmlResult.IntoElem())
										{
											if (struXmlResult.FindElem("cpuDescription"))
											{
												ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].aCpuInfo[m_paTermState[m_dwTermStateCount].dwCpuInfoCount].szCpuDesc, struXmlResult, "cpuDescription", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
											}
											
											if (struXmlResult.FindElem("cpuUtilization"))
											{
												ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].aCpuInfo[m_paTermState[m_dwTermStateCount].dwCpuInfoCount].dwCpuUtil, struXmlResult, "cpuUtilization", NODE_STRING_TO_INT);
											}
											
											m_paTermState[m_dwTermStateCount].dwCpuInfoCount++;
											struXmlResult.OutOfElem();
										}
										
									}//CPU
									
									struXmlResult.OutOfElem();
								}//CPUList
								
								if (struXmlResult.FindElem("MemoryList") && struXmlResult.IntoElem())
								{
									if (struXmlResult.FindElem("Memory") && struXmlResult.IntoElem())
									{
										if (struXmlResult.FindElem("memoryDescription"))
										{
											ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].aMemInfo[m_paTermState[m_dwTermStateCount].dwMemInfoCount].szMemDesc, struXmlResult, "memoryDescription", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
										}
										
										if (struXmlResult.FindElem("memoryUsage"))
										{
											ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].aMemInfo[m_paTermState[m_dwTermStateCount].dwMemInfoCount].fMemUsage, struXmlResult, "memoryUsage", NODE_STRING_TO_FLOAT);
										}
										
										if (struXmlResult.FindElem("memoryAvailable"))
										{
											ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].aMemInfo[m_paTermState[m_dwTermStateCount].dwMemInfoCount].fMemAvailable, struXmlResult, "memoryAvailable", NODE_STRING_TO_FLOAT);
										}
										
										m_paTermState[m_dwTermStateCount].dwMemInfoCount++;
										struXmlResult.OutOfElem();
										
										while (struXmlResult.NextSibElem() && struXmlResult.IntoElem())
										{
											if (struXmlResult.FindElem("memoryDescription"))
											{
												ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].aMemInfo[m_paTermState[m_dwTermStateCount].dwMemInfoCount].szMemDesc, struXmlResult, "memoryDescription", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
											}
											
											if (struXmlResult.FindElem("memoryUsage"))
											{
												ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].aMemInfo[m_paTermState[m_dwTermStateCount].dwMemInfoCount].fMemUsage, struXmlResult, "memoryUsage", NODE_STRING_TO_FLOAT);
											}
											
											if (struXmlResult.FindElem("memoryAvailable"))
											{
												ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].aMemInfo[m_paTermState[m_dwTermStateCount].dwMemInfoCount].fMemAvailable, struXmlResult, "memoryAvailable", NODE_STRING_TO_FLOAT);
											}
											
											m_paTermState[m_dwTermStateCount].dwMemInfoCount++;
											struXmlResult.OutOfElem();
										}
										
									}//Memory
									
									struXmlResult.OutOfElem();
								}//MemoryList

								if(struXmlResult.FindElem("DiskList") && struXmlResult.IntoElem())
								{
									if (struXmlResult.FindElem("Disk") && struXmlResult.IntoElem())
                                    {
                                        if (struXmlResult.FindElem("diskDescription"))
                                        {
                                            ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].aDiskInfo[m_paTermState[m_dwTermStateCount].dwDiskInfoCount].szDiskDesc, struXmlResult, "diskDescription", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
                                        }
                                        
                                        if (struXmlResult.FindElem("diskUsage"))
                                        {
                                            ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].aDiskInfo[m_paTermState[m_dwTermStateCount].dwDiskInfoCount].fDiskUsage, struXmlResult, "diskUsage", NODE_STRING_TO_FLOAT);
                                        }
                                        
                                        if (struXmlResult.FindElem("diskAvailable"))
                                        {
                                            ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].aDiskInfo[m_paTermState[m_dwTermStateCount].dwDiskInfoCount].fDiskAvailable, struXmlResult, "diskAvailable", NODE_STRING_TO_FLOAT);
                                        }
                                        
                                        m_paTermState[m_dwTermStateCount].dwDiskInfoCount++;
                                        struXmlResult.OutOfElem();
                                        
                                        while (struXmlResult.NextSibElem() && struXmlResult.IntoElem())
                                        {
                                            if (struXmlResult.FindElem("diskDescription"))
											{
												ConvertSingleNodeData((char*)&m_paTermState[m_dwTermStateCount].aDiskInfo[m_paTermState[m_dwTermStateCount].dwDiskInfoCount].szDiskDesc, struXmlResult, "diskDescription", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
											}
											
											if (struXmlResult.FindElem("diskUsage"))
											{
												ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].aDiskInfo[m_paTermState[m_dwTermStateCount].dwDiskInfoCount].fDiskUsage, struXmlResult, "diskUsage", NODE_STRING_TO_FLOAT);
											}
											
											if (struXmlResult.FindElem("diskAvailable"))
											{
												ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].aDiskInfo[m_paTermState[m_dwTermStateCount].dwDiskInfoCount].fDiskAvailable, struXmlResult, "diskAvailable", NODE_STRING_TO_FLOAT);
											}
                                            
                                            m_paTermState[m_dwTermStateCount].dwDiskInfoCount++;
                                            struXmlResult.OutOfElem();
                                        }
                                        
                                    }//Disk

									struXmlResult.OutOfElem();
								}//DiskList
								
								if (struXmlResult.FindElem("temperature"))
								{
									ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].dwTemperature, struXmlResult, "temperature", NODE_STRING_TO_INT);
								}
								m_dwTemperature = m_paTermState[m_dwTermStateCount].dwTemperature;
								struXmlResult.OutOfElem();
							}//WorkState
							
							if (struXmlResult.FindElem("PlayInfo") && struXmlResult.IntoElem())
							{
								ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].struPlayInfo.dwScheduleNo, struXmlResult, "scheduleNo", NODE_STRING_TO_INT);
								ConvertSingleNodeData(m_paTermState[m_dwTermStateCount].struPlayInfo.szScheduleName, struXmlResult, "scheduleName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								struXmlResult.OutOfElem();
							}

							if (struXmlResult.FindElem("TimingPlan") && struXmlResult.IntoElem())
							{
								if (struXmlResult.FindElem("SwitchPlan") && struXmlResult.IntoElem())
								{
									ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].struTimingPlan.bySwitchEnabled, struXmlResult, "enabled", NODE_STRING_TO_BOOL);
								
									struXmlResult.OutOfElem();
								}
								if (struXmlResult.FindElem("VolumePlan") && struXmlResult.IntoElem())
								{
									ConvertSingleNodeData(&m_paTermState[m_dwTermStateCount].struTimingPlan.byVolumeEnabled, struXmlResult, "enabled", NODE_STRING_TO_BOOL);
									
									struXmlResult.OutOfElem();
								}
								struXmlResult.OutOfElem();
							}
							
							struXmlResult.OutOfElem();
						}//PlayerState
					
						struXmlResult.OutOfElem();
					
						//Term添加
						csInfo.Format("%d", m_dwTermStateCount+1);
					
						nRow = m_pListTerm->InsertItem(m_dwTermStateCount, csInfo);//插入行
						csInfo.Format("%d", m_paTermState[m_dwTermStateCount].dwID);
						m_pListTerm->SetItemText(nRow, 1, csInfo);//设置数据
						csInfo = m_paTermState[m_dwTermStateCount].szTermName;
						m_pListTerm->SetItemText(nRow, 2, csInfo);//设置数据
					
						m_dwTermStateCount++;
					
					}
				}//Terminal

				struXmlResult.OutOfElem();

			}//TerminalStateList
			
		}//else 

	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Parse XML data failed");
	}

	UpdateData(FALSE);
}

void CDlgTermState::OnClickLstTermInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	if(pNMListView->iItem != -1)
    {
		//判断Item状态，是否为选中状态
		if(m_pListTerm->GetItemState(pNMListView->iItem, LVIS_SELECTED) == LVIS_SELECTED)
		{
			if (pNMListView->iItem < m_dwTermStateCount)
			{
				m_dwTermIndex = pNMListView->iItem;		

				m_dwTermID = m_paTermState[m_dwTermIndex].dwID;
				m_csTermName = m_paTermState[m_dwTermIndex].szTermName;
				
				m_csVersion = m_paTermState[m_dwTermIndex].szVersion;
				m_CondCode  = m_paTermState[m_dwTermIndex].szCondCode;
				m_csRegTime = m_paTermState[m_dwTermIndex].szRegTime;
				m_csHardVersion = m_paTermState[m_dwTermIndex].szHardwareVersion;
				m_SysVersion = m_paTermState[m_dwTermIndex].szSystemVersion;

				
				m_csAddrFormatType = m_paTermState[m_dwTermIndex].szAddrFormatType;
				m_csHostName = m_paTermState[m_dwTermIndex].szHostName;
				m_csIPVersion = m_paTermState[m_dwTermIndex].szIPVersion;
				m_csIPv4 = m_paTermState[m_dwTermIndex].szIPv4;
				m_csIPv6 = m_paTermState[m_dwTermIndex].szIPv6;
				
				m_csMacAddr = m_paTermState[m_dwTermIndex].szMacAddr;
				m_csServerURL = m_paTermState[m_dwTermIndex].szServerURL;
				m_csOnlineState = m_paTermState[m_dwTermIndex].szOnlineState;
				m_csAbnormalState = m_paTermState[m_dwTermIndex].szAbnormalState;

				m_dwScheduleNo = m_paTermState[m_dwTermIndex].struPlayInfo.dwScheduleNo;
				m_csScheduleName = m_paTermState[m_dwTermIndex].struPlayInfo.szScheduleName;
				m_bySwitch = m_paTermState[m_dwTermIndex].struTimingPlan.bySwitchEnabled;
				m_byVolum = m_paTermState[m_dwTermIndex].struTimingPlan.byVolumeEnabled;

				int i = 0;
				CString csInfo;

				m_pListCPU->DeleteAllItems();
				for (i = 0; i < m_paTermState[m_dwTermIndex].dwCpuInfoCount; i++)
				{
					csInfo.Format("%d", i+1);		
					int nRow = m_pListCPU->InsertItem(i, csInfo);//插入行
					csInfo = m_paTermState[m_dwTermIndex].aCpuInfo[i].szCpuDesc;
					m_pListCPU->SetItemText(nRow, 1, csInfo);//设置数据
					csInfo.Format("%d", m_paTermState[m_dwTermIndex].aCpuInfo[i].dwCpuUtil);
					m_pListCPU->SetItemText(nRow, 2, csInfo);//设置数据
				}

				m_pListMem->DeleteAllItems();
				for (i = 0; i < m_paTermState[m_dwTermIndex].dwMemInfoCount; i++)
				{
					csInfo.Format("%d", i+1);		
					int nRow = m_pListMem->InsertItem(i, csInfo);//插入行
					csInfo = m_paTermState[m_dwTermIndex].aMemInfo[i].szMemDesc;
					m_pListMem->SetItemText(nRow, 1, csInfo);//设置数据
					csInfo.Format("%f", m_paTermState[m_dwTermIndex].aMemInfo[i].fMemUsage);
					m_pListMem->SetItemText(nRow, 2, csInfo);//设置数据
					csInfo.Format("%f", m_paTermState[m_dwTermIndex].aMemInfo[i].fMemAvailable);
					m_pListMem->SetItemText(nRow, 3, csInfo);//设置数据
				}

                m_pListDisk->DeleteAllItems();
                for (i = 0; i < m_paTermState[m_dwTermIndex].dwDiskInfoCount; i++)
                {
                    csInfo.Format("%d", i+1);		
                    int nRow = m_pListDisk->InsertItem(i, csInfo);//插入行
                    csInfo = m_paTermState[m_dwTermIndex].aDiskInfo[i].szDiskDesc;
                    m_pListDisk->SetItemText(nRow, 1, csInfo);//设置数据
                    csInfo.Format("%f", m_paTermState[m_dwTermIndex].aDiskInfo[i].fDiskUsage);
                    m_pListDisk->SetItemText(nRow, 2, csInfo);//设置数据
                    csInfo.Format("%f", m_paTermState[m_dwTermIndex].aDiskInfo[i].fDiskAvailable);
                    m_pListDisk->SetItemText(nRow, 3, csInfo);//设置数据
				}

				m_dwScheduleNo = m_paTermState[m_dwTermIndex].struPlayInfo.dwScheduleNo;
				m_csScheduleName = m_paTermState[m_dwTermIndex].struPlayInfo.szScheduleName;
                m_dwTemperature = m_paTermState[m_dwTermIndex].dwTemperature;
                m_byVolum = m_paTermState[m_dwTermIndex].struTimingPlan.byVolumeEnabled;
                m_bySwitch = m_paTermState[m_dwTermIndex].struTimingPlan.bySwitchEnabled;
		
				UpdateData(FALSE);
			}
		}
	}
	
	*pResult = 0;
}

void CDlgTermState::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	delete[] m_paTermState;
	m_paTermState = NULL;
	delete[] m_pXMLResultBuf;
	m_pXMLResultBuf = NULL;
}
