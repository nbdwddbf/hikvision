// DlgMCUTerminalManageCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMCUTerminalManageCfg.h"
#include "InfoDiffusionParamsConvert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define CSTRING_TO_CHARS(str,sz) memcpy((sz),str.GetBuffer(str.GetLength()),str.GetLength())

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUTerminalManageCfg dialog


CDlgMCUTerminalManageCfg::CDlgMCUTerminalManageCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMCUTerminalManageCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMCUTerminalManageCfg)
	m_csUser = _T("");
	m_csPwd = _T("");
	m_csOSDName = _T("");
	m_csTerminalName = _T("");
	m_csHostName = _T("");
	m_bEnable = TRUE;
	m_csIP = _T("");
	m_csIPV6 = _T("");
	m_IPortNo = 0;

    m_pXMLParamBuf = NULL;
    m_dwXMLParamBufLen = 0;


    memset(&m_szUUID, '\0', sizeof(m_szUUID));

	//}}AFX_DATA_INIT
}

CDlgMCUTerminalManageCfg::~CDlgMCUTerminalManageCfg()
{
    if (NULL != m_szRequestURL)
    {
        delete[] m_szRequestURL;
        m_szRequestURL = NULL;
    }

    if (NULL != m_szXMLResultBuf)
    {
        delete[] m_szXMLResultBuf;
        m_szXMLResultBuf = NULL;
    }
    
    if (NULL != m_szXMLResultBuf)
    {
        delete[] m_szXMLStatus;
        m_szXMLStatus = NULL;
    }
 }

void CDlgMCUTerminalManageCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgMCUTerminalManageCfg)
    DDX_Text(pDX, IDC_EDIT_TERMINAL_ID, m_csUUID);
    DDX_Text(pDX, IDC_EDIT_ADDRESS_FORMAT_TYPE, m_csAddFormatType);
    DDX_Text(pDX, IDC_COMBO_PROTOCOL_TYPE, m_csProtocolType);
    DDX_Text(pDX, IDC_COM_IP_VERSION, m_csIPVersion);

    DDX_Text(pDX, IDC_EDIT_USERID, m_csUser);
    DDX_Text(pDX, IDC_EDIT_PWD, m_csPwd);
    DDX_Text(pDX, IDC_EDIT_OSD_NAME, m_csOSDName);
    DDX_Text(pDX, IDC_EDIT_TERMINAL_NAME, m_csTerminalName);
    DDX_Text(pDX, IDC_EDIT_HOST_NAME, m_csHostName);
    DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
    DDX_Text(pDX, IDC_EDT_IP, m_csIP);
    DDX_Text(pDX, IDC_EDIT_IPV6_ADDRESS, m_csIPV6);
    DDX_Text(pDX, IDC_EDIT_PORT, m_IPortNo);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_LIST_TERMINAL, m_ctrlTerminal);
}


BEGIN_MESSAGE_MAP(CDlgMCUTerminalManageCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgMCUTerminalManageCfg)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_BN_CLICKED(IDC_BUT_GET, OnButGet)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_GET_ALL, &CDlgMCUTerminalManageCfg::OnBnClickedBtnGetAll)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUTerminalManageCfg message handlers

BOOL CDlgMCUTerminalManageCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();



    m_szRequestURL = new char[REQUEST_URL_LEN];  
    if (m_szRequestURL == NULL)
    {
        return FALSE;
    }

    memset(m_szRequestURL, '\0' , REQUEST_URL_LEN);

    m_szXMLResultBuf = new char[ISAPI_DATA_LEN];
    if (m_szXMLResultBuf == NULL)
    {
        return FALSE;
    }

    memset(m_szXMLResultBuf, '\0', ISAPI_DATA_LEN);
    m_dwXMLResultBufLen = ISAPI_DATA_LEN;
    m_szXMLStatus = new char[ISAPI_STATUS_LEN];

    if (m_szXMLStatus == NULL)
    {
        return FALSE;
    }

	memset(m_szXMLStatus, '\0', ISAPI_STATUS_LEN);

    DWORD dwExStyle = m_ctrlTerminal.GetExtendedStyle();
    dwExStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
    m_ctrlTerminal.SetExtendedStyle(dwExStyle);

    char szLan[512] = { 0 };
    g_StringLanType(szLan, "序号", "Index");
    m_ctrlTerminal.InsertColumn(0, szLan);
    m_ctrlTerminal.SetColumnWidth(0, 60);

    memset(szLan, 0, sizeof(szLan));
    g_StringLanType(szLan, "注册终端名称", "Terminal Name.");
    m_ctrlTerminal.InsertColumn(1, szLan);
    m_ctrlTerminal.SetColumnWidth(1, 100);
    
    UpdateData(FALSE);
	


	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


// SET
void CDlgMCUTerminalManageCfg::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);

	memset(m_szRequestURL, '\0' ,REQUEST_URL_LEN);
	memset(m_szXMLResultBuf, '\0', ISAPI_DATA_LEN);
	m_dwXMLResultBufLen = ISAPI_DATA_LEN;
    memset(m_szXMLStatus, '\0', sizeof(ISAPI_STATUS_LEN));
    
	char szTerminalName[MAX_XML_ELEM_LEN] = {0};
	char szOSDName[MAX_XML_ELEM_LEN] = {0};
	char szProtocolType[MAX_XML_ELEM_LEN] = {0};
	char szAddFormatType[MAX_XML_ELEM_LEN] = {0};
	char szHostName[MAX_XML_ELEM_LEN] = {0};
	char szIPVersion[MAX_XML_ELEM_LEN] = {0};
	char szIP[MAX_XML_ELEM_LEN] = {0};
	char szIPV6[MAX_XML_ELEM_LEN] = {0};
	char szUser[MAX_XML_ELEM_LEN] = {0};
	char szPwd[MAX_XML_ELEM_LEN] = {0};
    char szTermID[MAX_XML_ELEM_LEN] = {0};
	
    CSTRING_TO_CHARS(m_csUUID, szTermID);
	CSTRING_TO_CHARS(m_csOSDName, szOSDName);
	CSTRING_TO_CHARS(m_csTerminalName, szTerminalName);
	CSTRING_TO_CHARS(m_csProtocolType, szProtocolType);
	CSTRING_TO_CHARS(m_csAddFormatType, szAddFormatType);
	CSTRING_TO_CHARS(m_csHostName, szHostName);
	CSTRING_TO_CHARS(m_csIPVersion, szIPVersion);
	CSTRING_TO_CHARS(m_csIP, szIP);
	CSTRING_TO_CHARS(m_csIPV6, szIPV6);
	CSTRING_TO_CHARS(m_csUser, szUser);
	CSTRING_TO_CHARS(m_csPwd, szPwd);

	m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;
    ////////////////////////////////////////////////////////////////////////////
	//填充并转化信息
	CXmlBase struXmlParam;
	struXmlParam.CreateRoot("Terminal");
	struXmlParam.SetAttribute("version", "2.0");
	struXmlParam.SetAttribute("xmlns", "http://www.isapi.org/ver20/XMLSchema");
	
	
	ConvertSingleNodeData((char*)&szTermID, struXmlParam, "id", NODE_ARRAY_TO_STRING);
	ConvertSingleNodeData(&m_bEnable, struXmlParam, "enabled", NODE_BOOL_TO_STRING);	
	ConvertSingleNodeData((char*)&szTerminalName, struXmlParam, "terminalName", NODE_ARRAY_TO_STRING);
	ConvertSingleNodeData((char*)&szOSDName, struXmlParam, "OSDName", NODE_ARRAY_TO_STRING);
	ConvertSingleNodeData((char*)&szProtocolType, struXmlParam, "protocolType", NODE_ARRAY_TO_STRING);
    
	//终端地址
	if (struXmlParam.AddNode("TerminalAddress"))
	{		
		ConvertSingleNodeData((char*)&szAddFormatType, struXmlParam, "addressingFormatType", NODE_ARRAY_TO_STRING);	  
		ConvertSingleNodeData((char*)&szHostName, struXmlParam, "hostName", NODE_ARRAY_TO_STRING);        
		if (struXmlParam.AddNode("IpAddress"))
		{			
			ConvertSingleNodeData((char*)&szIPVersion, struXmlParam, "ipVersion", NODE_ARRAY_TO_STRING);			
            ConvertSingleNodeData((char*)&szIP, struXmlParam, "ipAddress", NODE_ARRAY_TO_STRING);			
	        ConvertSingleNodeData((char*)&szIPV6, struXmlParam, "ipv6Address", NODE_ARRAY_TO_STRING);
			struXmlParam.OutOfElem();
		}
		ConvertSingleNodeData(&m_IPortNo, struXmlParam, "portNo",NODE_INT_TO_STRING); 
		struXmlParam.OutOfElem();
	}
	ConvertSingleNodeData((char*)&szUser, struXmlParam, "userName", NODE_ARRAY_TO_STRING);
	ConvertSingleNodeData((char*)&szPwd, struXmlParam, "password", NODE_ARRAY_TO_STRING);
	////////////////////////////////////////////////////////////////////////////
	//将XML转存到buffer中
	m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;

	if (!PrintXmlToNewBuffer(&m_pXMLParamBuf, m_dwXMLParamBufLen, struXmlParam))
	{
		 g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "PrintXmlToNewBuffer");
		 return;
	}
	//Debug
	//CString strMsg = m_pXMLParamBuf;
	//MessageBox(strMsg);

	//获取终端管理配置
	//lpInputParam->lpRequestUrl为：PUT /ISAPI/VCS/terminals/<ID>；
	//lpInputParam->lpInBuffer为Terminal；
	//lpOutputParam->lpOutBuffer为NULL；
	//lpOutputParam->lpStatusBuffer为ResponseStatus。

    CSTRING_TO_CHARS(m_csUUID, m_szUUID);

	//调用SDK接口
	NET_DVR_XML_CONFIG_INPUT struXMLCfgInput = {0};
	struXMLCfgInput.dwSize = sizeof(struXMLCfgInput);
	sprintf((char*)m_szRequestURL, "PUT /ISAPI/VCS/terminals/%s", m_szUUID);
	struXMLCfgInput.lpRequestUrl = (char*)m_szRequestURL;
	struXMLCfgInput.dwRequestUrlLen = strlen(m_szRequestURL);
	struXMLCfgInput.lpInBuffer      = m_pXMLParamBuf;
	struXMLCfgInput.dwInBufferSize  = m_dwXMLParamBufLen;

	NET_DVR_XML_CONFIG_OUTPUT struXMLCfgOutput = {0};
	struXMLCfgOutput.dwSize = sizeof(struXMLCfgOutput);
	struXMLCfgOutput.lpOutBuffer = NULL;
	struXMLCfgOutput.dwOutBufferSize = 0;
	struXMLCfgOutput.lpStatusBuffer = m_szXMLStatus;
	struXMLCfgOutput.dwStatusSize = ISAPI_STATUS_LEN;

	LPNET_DVR_XML_CONFIG_OUTPUT lpXMLCfgOutput = &struXMLCfgOutput;

	if (NET_DVR_STDXMLConfig(m_lUserID, &struXMLCfgInput, lpXMLCfgOutput))
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");			
    }
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
	}

	ProcessXMLStatus(m_iDeviceIndex, (char*)struXMLCfgOutput.lpStatusBuffer);
    
	delete[] m_pXMLParamBuf;
	m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;
	
	UpdateData(FALSE);

}


//终端管理获取
void CDlgMCUTerminalManageCfg::OnButGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	memset(m_szRequestURL, '\0' ,REQUEST_URL_LEN);
	memset(m_szXMLResultBuf, '\0', ISAPI_DATA_LEN);
	m_dwXMLResultBufLen = ISAPI_DATA_LEN;
    memset(m_szXMLStatus, '\0', sizeof(ISAPI_STATUS_LEN));
    
    char szTermID[MAX_XML_ELEM_LEN] = {0};
	char szTerminalName[MAX_XML_ELEM_LEN] = {0};
	char szOSDName[MAX_XML_ELEM_LEN] = {0};
	char szProtocolType[MAX_XML_ELEM_LEN] = {0};
	char szAddFormatType[MAX_XML_ELEM_LEN] = {0};
	char szHostName[MAX_XML_ELEM_LEN] = {0};
	char szIPVersion[MAX_XML_ELEM_LEN] = {0};
	char szIP[MAX_XML_ELEM_LEN] = {0};
	char szIPV6[MAX_XML_ELEM_LEN] = {0};
	char szUser[MAX_XML_ELEM_LEN] = {0};
	char szPwd[MAX_XML_ELEM_LEN] = {0};
	
	
	//lpInputParam->lpRequestUrl为：GET /ISAPI/VCS/terminals/<ID>；
	//lpInputParam->lpInBuffer为NULL；
	//lpOutputParam->lpOutBuffer为Terminal；
	//lpOutputParam->lpStatusBuffer为ResponseStatus，获取成功时不返回。


	CSTRING_TO_CHARS(m_csUUID, szTermID);
	//调用接口
	NET_DVR_XML_CONFIG_INPUT struXMLCfgInput = {0};
	struXMLCfgInput.dwSize = sizeof(struXMLCfgInput);
	sprintf((char*)m_szRequestURL, "GET /ISAPI/VCS/terminals/%s", szTermID);
	struXMLCfgInput.lpRequestUrl = (char*)m_szRequestURL;
	struXMLCfgInput.dwRequestUrlLen = strlen(m_szRequestURL);
	struXMLCfgInput.lpInBuffer      = NULL;
	struXMLCfgInput.dwInBufferSize  = 0;
	
	NET_DVR_XML_CONFIG_OUTPUT struXMLCfgOutput = {0};
	struXMLCfgOutput.dwSize = sizeof(struXMLCfgOutput);
	struXMLCfgOutput.lpOutBuffer = (char*)m_szXMLResultBuf;
	struXMLCfgOutput.dwOutBufferSize = ISAPI_DATA_LEN;
	struXMLCfgOutput.lpStatusBuffer = (char*)m_szXMLStatus;
	struXMLCfgOutput.dwStatusSize = ISAPI_STATUS_LEN;
	
	LPNET_DVR_XML_CONFIG_OUTPUT lpXMLCfgOutput = &struXMLCfgOutput;
	
	if (NET_DVR_STDXMLConfig(m_lUserID, &struXMLCfgInput, lpXMLCfgOutput))
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig Success");			
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig Error");
		ProcessXMLStatus(m_iDeviceIndex, (char*)struXMLCfgOutput.lpOutBuffer);
		return;
    }
	
	ProcessXMLStatus(m_iDeviceIndex, (char*)struXMLCfgOutput.lpOutBuffer);

	//解析获取数据
	CXmlBase struXmlResult;

    //int back = strlen((char*)struXMLCfgOutput.lpOutBuffer);
    //((char*)struXMLCfgOutput.lpOutBuffer)[back] = '\n';
	
	if (struXmlResult.Parse((char*)struXMLCfgOutput.lpOutBuffer))
	{
		TermGroupInfo struTermGroupInfo = {0};
		if (struXmlResult.FindElem("Terminal") && struXmlResult.IntoElem())
		{	
			if (struXmlResult.FindElem("id"))
			{
				ConvertSingleNodeData((char*)&szTermID, struXmlResult, "id", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
			}
			
			if (struXmlResult.FindElem("enabled"))
			{
				ConvertSingleNodeData(&m_bEnable, struXmlResult, "enabled", NODE_STRING_TO_BOOL);
			}
			
			if (struXmlResult.FindElem("terminalName"))
			{
				ConvertSingleNodeData((char*)&szTerminalName, struXmlResult, "terminalName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
				m_csTerminalName = szTerminalName;
			}
			
			if (struXmlResult.FindElem("OSDName"))
			{
				ConvertSingleNodeData((char*)&szOSDName, struXmlResult, "OSDName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
				m_csOSDName = szOSDName;
			}
			if (struXmlResult.FindElem("protocolType"))
			{
				ConvertSingleNodeData((char*)&szProtocolType, struXmlResult, "protocolType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
				m_csProtocolType = szProtocolType;
			}
			
			if (struXmlResult.FindElem("TerminalAddress") && struXmlResult.IntoElem())
			{	
				//addressingFormatType
				if (struXmlResult.FindElem("addressingFormatType"))
				{
					ConvertSingleNodeData((char*)&szAddFormatType, struXmlResult, "addressingFormatType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
					m_csAddFormatType = szAddFormatType;
				}
				
				//hostName
				if (struXmlResult.FindElem("hostName"))
				{
					ConvertSingleNodeData((char*)&szHostName, struXmlResult, "hostName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
					m_csHostName = szHostName;
				}

				//IpAddress
				if (struXmlResult.FindElem("IpAddress") && struXmlResult.IntoElem())
				{
					//ipVersion
					if (struXmlResult.FindElem("ipVersion"))
					{
						ConvertSingleNodeData((char*)&szIPVersion, struXmlResult, "ipVersion", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						m_csIPVersion = szIPVersion;
					}
					
					//ipAddress
					if (struXmlResult.FindElem("ipAddress"))
					{
						ConvertSingleNodeData((char*)&szIP, struXmlResult, "ipAddress", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						m_csIP = szIP;
					}
				
					//ipv6Address
					if (struXmlResult.FindElem("ipv6Address"))
					{
						ConvertSingleNodeData((char*)&szIPV6, struXmlResult, "ipv6Address", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						m_csIPV6 = szIPV6;
					}
					struXmlResult.OutOfElem();
				}

				//PortNo
				if (struXmlResult.FindElem("portNo"))
				{
					ConvertSingleNodeData(&m_IPortNo, struXmlResult, "portNo", NODE_STRING_TO_INT);
				}

		    	struXmlResult.OutOfElem();
			}// end if (struXmlResult.FindElem("TerminalAddress") && struXmlResult.IntoElem())

			if (struXmlResult.FindElem("userName"))
			{
				ConvertSingleNodeData((char*)&szUser, struXmlResult, "userName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
				m_csUser = szUser;
			}
			
			if (struXmlResult.FindElem("password"))
			{
				ConvertSingleNodeData((char*)&szPwd, struXmlResult, "password", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
				m_csPwd = szPwd;
			}
			
			struXmlResult.OutOfElem();

            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "获取成功");

		}//if (struXmlResult.FindElem("Terminal") && struXmlResult.IntoElem())		
	}

    m_csUUID = szTermID;
    m_csAddFormatType = szAddFormatType;
    m_csProtocolType = szProtocolType;
    m_csIPVersion = szIPVersion;
    m_csUser = szUser;
    m_csPwd = szPwd;
    m_csOSDName = szOSDName;
    m_csTerminalName = szTerminalName;
    
    m_csHostName = szHostName;
    m_csIP = szIP;
    m_csIPV6 = szIPV6;
	
	UpdateData(FALSE);
}


//终端管理增加
void CDlgMCUTerminalManageCfg::OnBtnAdd() 
{
	UpdateData(TRUE);

	memset(m_szRequestURL, '\0' ,REQUEST_URL_LEN);
	memset(m_szXMLResultBuf, '\0', ISAPI_DATA_LEN);
	m_dwXMLResultBufLen = ISAPI_DATA_LEN;
    memset(m_szXMLStatus, '\0', sizeof(ISAPI_STATUS_LEN));
    
	char szTerminalName[MAX_XML_ELEM_LEN] = {0};
	char szOSDName[MAX_XML_ELEM_LEN] = {0};
	char szProtocolType[MAX_XML_ELEM_LEN] = {0};
	char szAddFormatType[MAX_XML_ELEM_LEN] = {0};
	char szHostName[MAX_XML_ELEM_LEN] = {0};
	char szIPVersion[MAX_XML_ELEM_LEN] = {0};
	char szIP[MAX_XML_ELEM_LEN] = {0};
	char szIPV6[MAX_XML_ELEM_LEN] = {0};
	char szUser[MAX_XML_ELEM_LEN] = {0};
	char szPwd[MAX_XML_ELEM_LEN] = {0};
	
	CSTRING_TO_CHARS(m_csOSDName, szOSDName);
	CSTRING_TO_CHARS(m_csTerminalName, szTerminalName);
	CSTRING_TO_CHARS(m_csProtocolType, szProtocolType);
	CSTRING_TO_CHARS(m_csAddFormatType, szAddFormatType);
	CSTRING_TO_CHARS(m_csHostName, szHostName);
	CSTRING_TO_CHARS(m_csIPVersion, szIPVersion);
	CSTRING_TO_CHARS(m_csIP, szIP);
	CSTRING_TO_CHARS(m_csIPV6, szIPV6);
	CSTRING_TO_CHARS(m_csUser, szUser);
	CSTRING_TO_CHARS(m_csPwd, szPwd);

	m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;

	//填充并转化信息
	CXmlBase struXmlParam;
	struXmlParam.CreateRoot("Terminal");
	struXmlParam.SetAttribute("version", "2.0");
	struXmlParam.SetAttribute("xmlns", "http://www.isapi.org/ver20/XMLSchema");
	
	//ConvertSingleNodeData(&m_dwTerminalID, struXmlParam, "id", NODE_INT_TO_STRING);
	ConvertSingleNodeData(&m_bEnable, struXmlParam, "enabled", NODE_BOOL_TO_STRING);
	ConvertSingleNodeData((char*)&szTerminalName, struXmlParam, "terminalName", NODE_ARRAY_TO_STRING);
	ConvertSingleNodeData((char*)&szOSDName, struXmlParam, "OSDName", NODE_ARRAY_TO_STRING);
	ConvertSingleNodeData((char*)&szProtocolType, struXmlParam, "protocolType", NODE_ARRAY_TO_STRING);
    
	//终端地址
	if (struXmlParam.AddNode("TerminalAddress"))
	{
		ConvertSingleNodeData((char*)&szAddFormatType, struXmlParam, "addressingFormatType", NODE_ARRAY_TO_STRING);
		ConvertSingleNodeData((char*)&szHostName, struXmlParam, "hostName", NODE_ARRAY_TO_STRING);
        
		if (struXmlParam.AddNode("IpAddress"))
		{
			ConvertSingleNodeData((char*)&szIPVersion, struXmlParam, "ipVersion", NODE_ARRAY_TO_STRING);
            ConvertSingleNodeData((char*)&szIP, struXmlParam, "ipAddress", NODE_ARRAY_TO_STRING);
			ConvertSingleNodeData((char*)&szIPV6, struXmlParam, "ipv6Address", NODE_ARRAY_TO_STRING);
			struXmlParam.OutOfElem();
		}
		
		ConvertSingleNodeData(&m_IPortNo, struXmlParam, "portNo",NODE_INT_TO_STRING); 
		
		struXmlParam.OutOfElem();
	}
	ConvertSingleNodeData((char*)&szUser, struXmlParam, "userName", NODE_ARRAY_TO_STRING);
	ConvertSingleNodeData((char*)&szPwd, struXmlParam, "password", NODE_ARRAY_TO_STRING);

	//将XML转存到buffer中
	m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;
	
	if (!PrintXmlToNewBuffer(&m_pXMLParamBuf, m_dwXMLParamBufLen, struXmlParam))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "PrintXmlToNewBuffer");
		return;
	}
	//Debug
	CString strMsg = m_pXMLParamBuf;
	MessageBox(strMsg);
	
	//lpInputParam->lpRequestUrl为：POST /ISAPI/VCS/terminals；
	//lpInputParam->lpInBuffer为Terminal；
	//lpOutputParam->lpOutBuffer为NULL；
	//lpOutputParam->lpStatusBuffer为ResponseStatus。

	
	NET_DVR_XML_CONFIG_INPUT struXMLCfgInput = {0};
	struXMLCfgInput.dwSize = sizeof(struXMLCfgInput);
	sprintf((char*)m_szRequestURL, "POST /ISAPI/VCS/terminals");
	struXMLCfgInput.lpRequestUrl = (char*)m_szRequestURL;
	struXMLCfgInput.dwRequestUrlLen = strlen(m_szRequestURL);
	struXMLCfgInput.lpInBuffer      = m_pXMLParamBuf;
	struXMLCfgInput.dwInBufferSize  = m_dwXMLParamBufLen;
	
	NET_DVR_XML_CONFIG_OUTPUT struXMLCfgOutput = {0};
	struXMLCfgOutput.dwSize = sizeof(struXMLCfgOutput);
	struXMLCfgOutput.lpOutBuffer = NULL;
	struXMLCfgOutput.dwOutBufferSize = 0;
	struXMLCfgOutput.lpStatusBuffer = (char*)m_szXMLStatus;
	struXMLCfgOutput.dwStatusSize = ISAPI_STATUS_LEN;
	
	LPNET_DVR_XML_CONFIG_OUTPUT lpXMLCfgOutput = &struXMLCfgOutput;
	
	if (NET_DVR_STDXMLConfig(m_lUserID, &struXMLCfgInput, lpXMLCfgOutput))
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");			
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
    }
	
	m_csUUID = ProcessXMLStatus(m_iDeviceIndex, (char*)struXMLCfgOutput.lpStatusBuffer);


	delete[] m_pXMLParamBuf;
	m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;
	
	UpdateData(FALSE);	
}

//终端管理删除
void CDlgMCUTerminalManageCfg::OnBtnDel() 
{
	UpdateData(TRUE);

	memset(m_szRequestURL, '\0' ,REQUEST_URL_LEN);
	memset(m_szXMLResultBuf, '\0', ISAPI_DATA_LEN);
	m_dwXMLResultBufLen = ISAPI_DATA_LEN;
    memset(m_szXMLStatus, '\0', sizeof(ISAPI_STATUS_LEN));
    
	//lpInputParam->lpRequestUrl为：DELETE /ISAPI/VCS/terminals/<ID>；
	//lpInputParam->lpInBuffer为NULL；
	//lpOutputParam->lpOutBuffer为NULL；
	//lpOutputParam->lpStatusBuffer为ResponseStatus。

    CSTRING_TO_CHARS(m_csUUID, m_szUUID);

	NET_DVR_XML_CONFIG_INPUT struXMLCfgInput = {0};
	struXMLCfgInput.dwSize = sizeof(struXMLCfgInput);
	sprintf((char*)m_szRequestURL, "DELETE /ISAPI/VCS/terminals/%s", m_szUUID);
	struXMLCfgInput.lpRequestUrl = (char*)m_szRequestURL;
	struXMLCfgInput.dwRequestUrlLen = strlen(m_szRequestURL);
	struXMLCfgInput.lpInBuffer      = NULL;
	struXMLCfgInput.dwInBufferSize  = 0;
	
	NET_DVR_XML_CONFIG_OUTPUT struXMLCfgOutput = {0};
	struXMLCfgOutput.dwSize = sizeof(struXMLCfgOutput);
	struXMLCfgOutput.lpOutBuffer = NULL;
	struXMLCfgOutput.dwOutBufferSize = 0;
	struXMLCfgOutput.lpStatusBuffer = (char*)m_szXMLStatus;
	struXMLCfgOutput.dwStatusSize = ISAPI_STATUS_LEN;
	
	LPNET_DVR_XML_CONFIG_OUTPUT lpXMLCfgOutput = &struXMLCfgOutput;
	
	if (NET_DVR_STDXMLConfig(m_lUserID, &struXMLCfgInput, lpXMLCfgOutput))
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");			
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
    }

	//状态处理
	ProcessXMLStatus(m_iDeviceIndex, (char*)struXMLCfgOutput.lpStatusBuffer);
	
	UpdateData(FALSE);
}

CString CDlgMCUTerminalManageCfg::ProcessXMLStatus(int iDeviceIndex, char* lpStatusBuf)
{
    DWORD dwStatusCode = 0;
    char  szStatusInfo  [256] = {0};
    char  szStatusString[128] = {0};
	char  szID          [256] = {0};
	
	CString csRet;
	
    CXmlBase struXmlStatus;
    if (struXmlStatus.Parse(lpStatusBuf))
    {
        if (struXmlStatus.FindElem("ResponseStatus") && struXmlStatus.IntoElem())
        {
            if (struXmlStatus.FindElem("statusCode"))
            {
                ConvertSingleNodeData(&dwStatusCode, struXmlStatus, "statusCode", NODE_STRING_TO_INT);
				
                sprintf((char*)szStatusInfo, "%s", GetStatusCodeInfo(dwStatusCode));
                if (dwStatusCode == 0 || dwStatusCode == 1)
                {
                    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szStatusInfo);
                }
                else
                {
                    if (struXmlStatus.FindElem("statusString"))
                    {
                        ConvertSingleNodeData((char*)&szStatusString, struXmlStatus, "statusString", NODE_STRING_TO_ARRAY, 128);
                        sprintf((char*)szStatusInfo, "StatusString: %s", szStatusString);
                        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szStatusInfo);
                        struXmlStatus.OutOfElem();
                    }	
                }
				if (struXmlStatus.FindElem("ID"))
				{
					ConvertSingleNodeData(&szID, struXmlStatus, "ID", NODE_STRING_TO_ARRAY, 256);
					csRet = szID;
				}
            }
        }
    }
    else
    {
        //g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Status XML Parse Error");
    }
	return csRet;
}


void CDlgMCUTerminalManageCfg::OnBnClickedBtnGetAll()
{
    // TODO:  在此添加控件通知处理程序代码
    CString strCommand;
    strCommand.Format("GET /ISAPI/VCS/mcu/gkServer/regGkTerminal\r\n");
    NET_DVR_XML_CONFIG_INPUT struInputParam = { 0 };
    struInputParam.dwSize = sizeof(struInputParam);
    struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
    struInputParam.dwRequestUrlLen = strCommand.GetLength();

    char szStatusBuff[1024] = { 0 };
    char szOutputBuffer[1024] = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT struOutputParam = { 0 };
    struOutputParam.dwSize = sizeof(struOutputParam);
    struOutputParam.lpOutBuffer = szOutputBuffer;
    struOutputParam.dwOutBufferSize = 1024;
    struOutputParam.lpStatusBuffer = szStatusBuff;
    struOutputParam.dwStatusSize = sizeof(szStatusBuff);

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");

    memset(m_szName, 0, sizeof(m_szName));
    m_nIdCount = 0;
    ConvertTermNameXmlToStruList(szOutputBuffer);
    RefreshList();

    UpdateData(FALSE);
}

BOOL CDlgMCUTerminalManageCfg::ConvertTermNameXmlToStruList(const char* pXmlBuf)
{
    if (pXmlBuf == NULL)
    {
        return FALSE;
    }
    CXmlBase struXml;
    if (struXml.Parse(pXmlBuf) == NULL)
    {
        return FALSE;
    }

    if (struXml.FindElem("RegGkTerminalList") && struXml.IntoElem())
    {
        if (struXml.FindElem("RegGkTerminal") && struXml.IntoElem())
        {
            ConvertSingleNodeData(m_szName[m_nIdCount], struXml, "registerName", NODE_STRING_TO_ARRAY, 64);
            m_nIdCount++;
            struXml.OutOfElem();
        }
        while (struXml.NextSibElem())
        {
            if (struXml.FindElem("RegGkTerminal") && struXml.IntoElem())
            {
                ConvertSingleNodeData(m_szName[m_nIdCount], struXml, "registerName", NODE_STRING_TO_ARRAY, 64);
                m_nIdCount++;
                if (m_nIdCount > 64)
                {
                    break;
                }
                struXml.OutOfElem();
            }
        }
        struXml.OutOfElem();
        return TRUE;
    }

    return FALSE;
}

void CDlgMCUTerminalManageCfg::RefreshList()
{
   
    m_ctrlTerminal.DeleteAllItems();
    CString str;
    for (int nCnt = 0; nCnt < m_nIdCount; nCnt++)
    {
        
        str.Format("%d", nCnt + 1);
        m_ctrlTerminal.InsertItem(nCnt, str);
        str.Format("%s", m_szName[nCnt]);
        m_ctrlTerminal.SetItemText(nCnt, 1, str);
    }
}