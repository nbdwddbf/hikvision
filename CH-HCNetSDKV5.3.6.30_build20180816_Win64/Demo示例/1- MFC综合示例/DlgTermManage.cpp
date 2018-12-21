// DlgTermManage.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgTermManage.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CSTRING_TO_CHARS(str,sz) memcpy((sz),str.GetBuffer(str.GetLength()),str.GetLength())

/////////////////////////////////////////////////////////////////////////////
// CDlgTermManage dialog


CDlgTermManage::CDlgTermManage(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTermManage::IDD, pParent)
    , m_dwOrgNo(0)
{
	//{{AFX_DATA_INIT(CDlgTermManage)
	m_csIpcAddrFormatType = _T("");
	m_nOperateType = -1;
	m_dwBelongGroup = 0;
	m_dwTermID = 0;
	m_dwPullPort = 0;
	m_dwIpcID = 0;
	m_dwIpcPort = 8000;
	m_dwIpcInfoCount = 0;
	m_dwIpcInfoIndex = 0;
	m_dwTermInfoCount = 0;
	m_dwTermInfoIndex = 0;
	m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;
	m_dwXMLResultBufLen = ISAPI_DATA_LEN;
	m_dwTerminalChannel = 0;
	//}}AFX_DATA_INIT
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	memset(m_aIPCInfo, 0, sizeof(m_aIPCInfo));
	m_paTermInfo = new TERM_INFO[MAX_NUM_TERMINAL];
	memset(m_paTermInfo, 0, sizeof(TERM_INFO)*MAX_NUM_TERMINAL);
	memset(m_szRequestURL, '\0' ,sizeof(m_szRequestURL));
	memset(m_szXMLStatus, '\0', sizeof(m_szXMLStatus));
	m_bGetOne = FALSE;
	m_pXMLResultBuf = new char[ISAPI_DATA_LEN];
	memset(m_pXMLResultBuf, 0, ISAPI_DATA_LEN);
	memset(&m_struTermInfo, 0, sizeof(m_struTermInfo));
}


void CDlgTermManage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgTermManage)
    DDX_Control(pDX, IDC_COMBO_ADDR_TYPE, m_cmbAddrType);
    DDX_Control(pDX, IDC_COM_REG_TYPE, m_comRegType);
    DDX_Control(pDX, IDC_COM_ADDR_FORMAT_TYPE, m_comPullAddrFormatType);
    DDX_Control(pDX, IDC_COM_PULL_IP_VERSION, m_comPullIPVersion);
    DDX_Control(pDX, IDC_COM_IPC_TYPE, m_comIpcType);
    DDX_Control(pDX, IDC_COM_IPC_IP_VERSION, m_comIpcIPVersion);
    DDX_CBString(pDX, IDC_COMBO_ADDR_TYPE, m_csIpcAddrFormatType);
    DDX_Radio(pDX, IDC_RAD_GET_ONE, m_nOperateType);
    DDX_Text(pDX, IDC_EDIT_BELONG_GROUP, m_dwBelongGroup);
    DDX_Text(pDX, IDC_EDT_TERM_ID, m_dwTermID);
    DDX_Text(pDX, IDC_EDT_TERM_NAME, m_csTermName);
    DDX_Text(pDX, IDC_COM_REG_TYPE, m_csRegType);
    DDX_Text(pDX, IDC_EDT_COND_CODE, m_CondCode);
    DDX_Text(pDX, IDC_COM_ADDR_FORMAT_TYPE, m_csPullAddrFormatType);
    DDX_Text(pDX, IDC_EDT_HOST_NAME, m_csPullHostName);
    DDX_Text(pDX, IDC_COM_PULL_IP_VERSION, m_csPullIPVersion);
    DDX_Text(pDX, IDC_EDT_PULL_IP4_ADDR, m_csPullIPv4);
    DDX_Text(pDX, IDC_EDT_PULL_IP6_ADDR, m_csPullIPv6);
    DDX_Text(pDX, IDC_EDT_PULL_PORT, m_dwPullPort);
    DDX_Text(pDX, IDC_EDT_PULL_USER_NAME, m_csPullUserName);
    DDX_Text(pDX, IDC_EDT_PULL_PWD, m_csPullPwd);
    DDX_Text(pDX, IDC_EDT_IPC_ID, m_dwIpcID);
    DDX_Text(pDX, IDC_COM_IPC_TYPE, m_csIpcType);
    DDX_Text(pDX, IDC_EDT_IPC_HOST_NAME, m_csIpcHostName);
    DDX_Text(pDX, IDC_COM_IPC_IP_VERSION, m_csIpcIPVersion);
    DDX_Text(pDX, IDC_EDT_IPC_IP4_ADDR, m_csIpcIPv4);
    DDX_Text(pDX, IDC_EDT_IPC_IP6_ADDR, m_csIpcIPv6);
    DDX_Text(pDX, IDC_EDT_IPC_PORT, m_dwIpcPort);
    DDX_Text(pDX, IDC_EDT_IPC_USER_NAME, m_csIpcUserName);
    DDX_Text(pDX, IDC_EDT_IPC_PWD, m_csIpcPwd);
    DDX_Text(pDX, IDC_EDIT_TERMINAL_CHANNEL, m_dwTerminalChannel);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_LIST_TERM, m_listTermianl);
    DDX_Text(pDX, IDC_EDIT_BELONG_ORG, m_dwOrgNo);
}


BEGIN_MESSAGE_MAP(CDlgTermManage, CDialog)
	//{{AFX_MSG_MAP(CDlgTermManage)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_BN_CLICKED(IDC_BTN_ADD_IPC, OnBtnAddIpc)
	ON_BN_CLICKED(IDC_RAD_GET_ONE, OnRadGetOne)
	ON_BN_CLICKED(IDC_RAD_GET_MORE, OnRadGetMore)
	ON_BN_CLICKED(IDC_RAD_SET_ONE, OnRadSet)
	ON_BN_CLICKED(IDC_RAD_ADD_ONE, OnRadAdd)
	ON_BN_CLICKED(IDC_RAD_DEL_ONE, OnRadDel)
	ON_NOTIFY(NM_CLICK, IDC_LIST_TERM, OnClickLstTermInfo)
	ON_NOTIFY(NM_CLICK, IDC_LIST_IPC, OnClickLstIpcInfo)
	ON_CBN_SELCHANGE(IDC_COM_ADDR_FORMAT_TYPE, OnSelchangeComAddrFormatType)
	ON_CBN_SELCHANGE(IDC_COM_IPC_IP_VERSION, OnSelchangeComIpcIpVersion)
	ON_CBN_SELCHANGE(IDC_COM_REG_TYPE, OnSelchangeComRegType)
	ON_CBN_SELCHANGE(IDC_COMBO_ADDR_TYPE, OnSelchangeComboAddrType)
	ON_CBN_SELCHANGE(IDC_COM_PULL_IP_VERSION, OnSelchangeComPullIpVersion)
	ON_BN_CLICKED(IDC_BTN_DEL_IPC, OnBtnDelIpc)
	ON_BN_CLICKED(IDC_BTN_MOD_IPC, OnBtnModIpc)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_BATCH_DEL, &CDlgTermManage::OnBnClickedBtnBatchDel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTermManage message handlers

BOOL CDlgTermManage::OnInitDialog()
{
    CDialog::OnInitDialog();
	
	m_pListIpc = (CListCtrl*)GetDlgItem(IDC_LIST_IPC);
	
	m_pListTerm = (CListCtrl*)GetDlgItem(IDC_LIST_TERM);
	
	m_comRegType.InsertString(0, _T("pull"));
    m_comRegType.InsertString(1, _T("push"));
	
	m_comPullAddrFormatType.InsertString(0, _T("ipaddress"));
    m_comPullAddrFormatType.InsertString(1, _T("hostname"));
	
	m_comPullIPVersion.InsertString(0, _T("v4"));
    m_comPullIPVersion.InsertString(1, _T("v6"));
	m_comPullIPVersion.InsertString(2, _T("dual"));
	
	m_comIpcType.InsertString(0, _T("normal"));
    m_comIpcType.InsertString(1, _T("passengerStatistics"));
	m_comIpcType.InsertString(1, _T("validPassengerStatistics"));
	
	m_comIpcIPVersion.InsertString(0, _T("v4"));
    m_comIpcIPVersion.InsertString(1, _T("v6"));
	m_comIpcIPVersion.InsertString(2, _T("dual"));
	
	
	LONG lStyle;
    lStyle = GetWindowLong(m_pListIpc->m_hWnd, GWL_STYLE);
    lStyle &= ~LVS_TYPEMASK;
    lStyle |= LVS_REPORT;
    SetWindowLong(m_pListIpc->m_hWnd, GWL_STYLE, lStyle);
	//SetWindowLong(m_pListTerm->m_hWnd, GWL_STYLE, lStyle);
    
    DWORD dwStyle = m_pListIpc->GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;
    dwStyle |= LVS_EX_GRIDLINES;
    m_pListIpc->SetExtendedStyle(dwStyle);
	m_pListTerm->SetExtendedStyle(dwStyle);

    m_pListIpc->InsertColumn(0, "Index", LVCFMT_LEFT, 50);
    m_pListIpc->InsertColumn(1, "ID", LVCFMT_LEFT, 100);
    m_pListIpc->InsertColumn(2, "IPC Type", LVCFMT_LEFT, 100);
	
	m_pListTerm->InsertColumn(0, "Index", LVCFMT_LEFT, 50);
    m_pListTerm->InsertColumn(1, "ID", LVCFMT_LEFT, 100);
    m_pListTerm->InsertColumn(2, "Terminal Name", LVCFMT_LEFT, 150);
	
	
	GetDlgItem(IDC_BTN_GET)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_SET)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);
	
	m_nOperateType = 3;
	OnRadAdd();

	UpdateData(FALSE);
	
	return TRUE;
}

void CDlgTermManage::OnRadGetOne()
{
	m_nOperateType = 0;
	
	m_bGetOne = TRUE;

	GetDlgItem(IDC_LIST_TERM)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDT_TERM_ID)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDT_TERM_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_COM_REG_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_COND_CODE)->EnableWindow(FALSE);
	GetDlgItem(IDC_COM_ADDR_FORMAT_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_HOST_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_COM_PULL_IP_VERSION)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_PULL_IP4_ADDR)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_PULL_IP6_ADDR)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_PULL_PORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_PULL_USER_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_PULL_PWD)->EnableWindow(FALSE);

	GetDlgItem(IDC_LIST_IPC)->EnableWindow(TRUE);
	GetDlgItem(IDC_COM_IPC_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_ADDR_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_IPC_HOST_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_COM_IPC_IP_VERSION)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_IPC_IP4_ADDR)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_IPC_IP6_ADDR)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_IPC_PORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_IPC_USER_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_IPC_PWD)->EnableWindow(FALSE);

	GetDlgItem(IDC_BTN_GET)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_SET)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);
}

void CDlgTermManage::OnRadGetMore()
{
	m_nOperateType = 1;

	m_bGetOne = FALSE;

	GetDlgItem(IDC_LIST_TERM)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDT_TERM_ID)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_TERM_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_COM_REG_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_COND_CODE)->EnableWindow(FALSE);
	GetDlgItem(IDC_COM_ADDR_FORMAT_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_HOST_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_COM_PULL_IP_VERSION)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_PULL_IP4_ADDR)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_PULL_IP6_ADDR)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_PULL_PORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_PULL_USER_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_PULL_PWD)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_LIST_IPC)->EnableWindow(TRUE);
	GetDlgItem(IDC_COM_IPC_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_ADDR_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_IPC_HOST_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_COM_IPC_IP_VERSION)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_IPC_IP4_ADDR)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_IPC_IP6_ADDR)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_IPC_PORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_IPC_USER_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_IPC_PWD)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_BTN_GET)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_SET)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);
}

void CDlgTermManage::OnRadSet()
{
	m_nOperateType = 2;

	GetDlgItem(IDC_LIST_TERM)->EnableWindow(TRUE);

	GetDlgItem(IDC_EDT_TERM_ID)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDT_TERM_NAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_COM_REG_TYPE)->EnableWindow(TRUE);
	m_comRegType.SetCurSel(0);
	OnSelchangeComRegType();
	
	GetDlgItem(IDC_LIST_IPC)->EnableWindow(TRUE);
	GetDlgItem(IDC_COM_IPC_TYPE)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_ADDR_TYPE)->EnableWindow(TRUE);
	m_cmbAddrType.SetCurSel(0);
	OnSelchangeComboAddrType();
	GetDlgItem(IDC_EDT_IPC_PORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDT_IPC_USER_NAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDT_IPC_PWD)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_BTN_GET)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_SET)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);
}

void CDlgTermManage::OnRadAdd()
{
	m_nOperateType = 3;

	GetDlgItem(IDC_LIST_TERM)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_EDT_TERM_ID)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_TERM_NAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_COM_REG_TYPE)->EnableWindow(TRUE);
	m_comRegType.SetCurSel(0);
	OnSelchangeComRegType();
	
	GetDlgItem(IDC_LIST_IPC)->EnableWindow(TRUE);
	GetDlgItem(IDC_COM_IPC_TYPE)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_ADDR_TYPE)->EnableWindow(TRUE);
	m_cmbAddrType.SetCurSel(0);
	OnSelchangeComboAddrType();
	GetDlgItem(IDC_EDT_IPC_PORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDT_IPC_USER_NAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDT_IPC_PWD)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_BTN_GET)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_SET)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_ADD)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(FALSE);
}

void CDlgTermManage::OnRadDel()
{
	m_nOperateType = 4;

	GetDlgItem(IDC_LIST_TERM)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDT_TERM_ID)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDT_TERM_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_COM_REG_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_COND_CODE)->EnableWindow(FALSE);
	GetDlgItem(IDC_COM_ADDR_FORMAT_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_HOST_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_COM_PULL_IP_VERSION)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_PULL_IP4_ADDR)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_PULL_IP6_ADDR)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_PULL_PORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_PULL_USER_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_PULL_PWD)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_LIST_IPC)->EnableWindow(TRUE);
	GetDlgItem(IDC_COM_IPC_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_ADDR_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_IPC_HOST_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_COM_IPC_IP_VERSION)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_IPC_IP4_ADDR)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_IPC_IP6_ADDR)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_IPC_PORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_IPC_USER_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDT_IPC_PWD)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_BTN_GET)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_SET)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DEL)->EnableWindow(TRUE);
}

void CDlgTermManage::OnBtnAddIpc()
{
	UpdateData(TRUE);

	IPC_INFO stIpcInfo = {0};

	stIpcInfo.dwID = m_dwIpcInfoCount+1;
	m_dwIpcID = stIpcInfo.dwID;
	CSTRING_TO_CHARS(m_csIpcType, stIpcInfo.szIpcType);
	CSTRING_TO_CHARS(m_csIpcAddrFormatType, stIpcInfo.szAddrFormatType);
	CSTRING_TO_CHARS(m_csIpcHostName, stIpcInfo.szHostName);
	CSTRING_TO_CHARS(m_csIpcIPVersion, stIpcInfo.szIPVersion);
	CSTRING_TO_CHARS(m_csIpcIPv4, stIpcInfo.szIPv4);
	CSTRING_TO_CHARS(m_csIpcIPv6, stIpcInfo.szIPv6);
	stIpcInfo.dwPort = m_dwIpcPort;
	CSTRING_TO_CHARS(m_csIpcUserName, stIpcInfo.szUser);
	CSTRING_TO_CHARS(m_csIpcPwd, stIpcInfo.szPwd);
	stIpcInfo.dwTermiChannelNo = m_dwTerminalChannel;
	
	m_aIPCInfo[m_dwIpcInfoCount] = stIpcInfo;
	
	m_dwIpcInfoCount++;
	
	CString strInfo;
	strInfo.Format("%d", m_dwIpcInfoCount);
	int nRow = m_pListIpc->InsertItem(m_dwIpcInfoCount-1, strInfo);//插入行
	m_pListIpc->SetItemState(m_dwIpcInfoIndex, 0, -1);
	m_pListIpc->SetItemState(m_dwIpcInfoCount-1, LVIS_SELECTED, LVIS_SELECTED);
	m_pListIpc->SetFocus();
	m_dwIpcInfoIndex = m_dwIpcInfoCount-1;
	strInfo.Format("%d", m_dwIpcID);
    m_pListIpc->SetItemText(nRow, 1, strInfo);//设置数据
    m_pListIpc->SetItemText(nRow, 2, m_csIpcType);//设置数据

	UpdateData(FALSE);
}

void CDlgTermManage::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	memset(m_aIPCInfo, 0, sizeof(m_aIPCInfo));
	m_dwIpcInfoCount = 0;
	m_dwIpcInfoIndex = 0;
	
	memset(m_paTermInfo, 0, sizeof(TERM_INFO)*MAX_NUM_TERMINAL);
	m_dwTermInfoCount = 0;
	m_dwTermInfoIndex = 0;

	memset(&m_struTermInfo, 0, sizeof(m_struTermInfo));
	
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
		sprintf((char*)m_szRequestURL, "GET /ISAPI/Publish/TerminalMgr/terminals/%d\r\n", m_dwTermID);
	}
	else
	{
		sprintf((char*)m_szRequestURL, "GET /ISAPI/Publish/TerminalMgr/terminals\r\n");
	}
	
	struXMLCfgInput.lpRequestUrl = (char*)m_szRequestURL;
	struXMLCfgInput.dwRequestUrlLen = strlen(m_szRequestURL);
	
	NET_DVR_XML_CONFIG_OUTPUT struXMLCfgOutput = {0};
	struXMLCfgOutput.dwSize = sizeof(struXMLCfgOutput);
	struXMLCfgOutput.lpOutBuffer = (char*)m_pXMLResultBuf;
	struXMLCfgOutput.dwOutBufferSize = ISAPI_DATA_LEN;
	struXMLCfgOutput.lpStatusBuffer = (char*)m_szXMLStatus;
	struXMLCfgOutput.dwStatusSize = sizeof(m_szXMLStatus);
	
	if (NET_DVR_STDXMLConfig(m_lUserID, &struXMLCfgInput, &struXMLCfgOutput))
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
		if (m_bGetOne)
		{
			//获取一个
			if(struXmlResult.FindElem("Terminals") && struXmlResult.IntoElem())
			{
				if (struXmlResult.FindElem("id"))
				{
					ConvertSingleNodeData(&m_struTermInfo.dwID, struXmlResult, "id", NODE_STRING_TO_INT);
				}
				if (struXmlResult.FindElem("terminalName"))
				{
					ConvertSingleNodeData((char*)&m_struTermInfo.szTermName, struXmlResult, "terminalName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
				}
				
				if (struXmlResult.FindElem("registerType"))
				{
					ConvertSingleNodeData((char*)&m_struTermInfo.szRegType, struXmlResult, "registerType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
				}

				if (struXmlResult.FindElem("PushModeInfo") && struXmlResult.IntoElem())
				{
					if (struXmlResult.FindElem("characteristicCode"))
					{
						ConvertSingleNodeData((char*)&m_struTermInfo.szCondCode, struXmlResult, "characteristicCode", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
					}
					struXmlResult.OutOfElem();
				}
				if (struXmlResult.FindElem("PullModeInfo") && struXmlResult.IntoElem())
				{
					if (struXmlResult.FindElem("TerminalAddress") && struXmlResult.IntoElem())
					{
						if (struXmlResult.FindElem("addressingFormatType"))
						{
							ConvertSingleNodeData((char*)&m_struTermInfo.szAddrFormatType, struXmlResult, "addressingFormatType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						}

						if (struXmlResult.FindElem("hostName"))
						{
							ConvertSingleNodeData((char*)&m_struTermInfo.szHostName, struXmlResult, "hostName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						}

						if (struXmlResult.FindElem("IpAddress") && struXmlResult.IntoElem())
						{
							if (struXmlResult.FindElem("ipVersion"))
							{
								ConvertSingleNodeData((char*)&m_struTermInfo.szIPVersion, struXmlResult, "ipVersion", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							}
							if (struXmlResult.FindElem("ipAddress"))
							{
								ConvertSingleNodeData((char*)&m_struTermInfo.szIPv4, struXmlResult, "ipAddress", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							}
							if (struXmlResult.FindElem("ipv6Address"))
							{
								ConvertSingleNodeData((char*)&m_struTermInfo.szIPv6, struXmlResult, "ipv6Address", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							}

							struXmlResult.OutOfElem();
						}//IpAddress

						struXmlResult.OutOfElem();
					}//ipAddress

					if (struXmlResult.FindElem("portNo"))
					{
						ConvertSingleNodeData(&m_struTermInfo.dwPort, struXmlResult, "portNo", NODE_STRING_TO_INT);
					}
					if (struXmlResult.FindElem("userName"))
					{
						ConvertSingleNodeData((char*)&m_struTermInfo.szUser, struXmlResult, "userName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
					}
					if (struXmlResult.FindElem("passWord"))
					{
						ConvertSingleNodeData((char*)&m_struTermInfo.szPwd, struXmlResult, "passWord", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
					}
					struXmlResult.OutOfElem();
				}//PullModeInfo

				if (struXmlResult.FindElem("IPCList") && struXmlResult.IntoElem())
				{
					if (struXmlResult.FindElem("IPC") && struXmlResult.IntoElem())
					{
						IPC_INFO stIpcInfo = {0};
						if (struXmlResult.FindElem("id"))
						{
							ConvertSingleNodeData(&stIpcInfo.dwID, struXmlResult, "id", NODE_STRING_TO_INT);
						}
						if (struXmlResult.FindElem("IPCType"))
						{
							ConvertSingleNodeData((char*)&stIpcInfo.szIpcType, struXmlResult, "IPCType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						}
						if (struXmlResult.FindElem("channelNo"))
						{
							ConvertSingleNodeData((char*)&stIpcInfo.dwTermiChannelNo, struXmlResult, "channelNo", NODE_STRING_TO_INT);
						}

						if (struXmlResult.FindElem("IPCAddress") && struXmlResult.IntoElem())
						{
							if (struXmlResult.FindElem("addressingFormatType"))
							{
								ConvertSingleNodeData((char*)&stIpcInfo.szAddrFormatType, struXmlResult, "addressingFormatType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							}
							
							if (struXmlResult.FindElem("hostName"))
							{
								ConvertSingleNodeData((char*)&stIpcInfo.szHostName, struXmlResult, "hostName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							}
							
							if (struXmlResult.FindElem("IpAddress") && struXmlResult.IntoElem())
							{
								if (struXmlResult.FindElem("ipVersion"))
								{
									ConvertSingleNodeData((char*)&stIpcInfo.szIPVersion, struXmlResult, "ipVersion", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								if (struXmlResult.FindElem("ipAddress"))
								{
									ConvertSingleNodeData((char*)&stIpcInfo.szIPv4, struXmlResult, "ipAddress", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								if (struXmlResult.FindElem("ipv6Address"))
								{
									ConvertSingleNodeData((char*)&stIpcInfo.szIPv6, struXmlResult, "ipv6Address", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								
								struXmlResult.OutOfElem();
							}//IpAddress
							
							struXmlResult.OutOfElem();
						}//ipAddress

						if (struXmlResult.FindElem("portNo"))
						{
							ConvertSingleNodeData(&stIpcInfo.dwPort, struXmlResult, "portNo", NODE_STRING_TO_INT);
						}
						if (struXmlResult.FindElem("userName"))
						{
							ConvertSingleNodeData((char*)&stIpcInfo.szUser, struXmlResult, "userName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						}
						if (struXmlResult.FindElem("passWord"))
						{
							ConvertSingleNodeData((char*)&stIpcInfo.szPwd, struXmlResult, "passWord", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						}

						m_struTermInfo.aIPCInfo[m_struTermInfo.dwIpcInfoCount] = stIpcInfo;

						m_struTermInfo.dwIpcInfoCount++;

						struXmlResult.OutOfElem();

						while (struXmlResult.NextSibElem() && struXmlResult.IntoElem())
						{
							IPC_INFO stIpcInfo = {0};
							if (struXmlResult.FindElem("id"))
							{
								ConvertSingleNodeData(&stIpcInfo.dwID, struXmlResult, "id", NODE_STRING_TO_INT);
							}
							if (struXmlResult.FindElem("IPCType"))
							{
								ConvertSingleNodeData((char*)&stIpcInfo.szIpcType, struXmlResult, "IPCType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							}
							if (struXmlResult.FindElem("channelNo"))
							{
								ConvertSingleNodeData((char*)&stIpcInfo.dwTermiChannelNo, struXmlResult, "channelNo", NODE_STRING_TO_INT);
							}
							
							if (struXmlResult.FindElem("IPCAddress") && struXmlResult.IntoElem())
							{
								if (struXmlResult.FindElem("addressingFormatType"))
								{
									ConvertSingleNodeData((char*)&stIpcInfo.szAddrFormatType, struXmlResult, "addressingFormatType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								
								if (struXmlResult.FindElem("hostName"))
								{
									ConvertSingleNodeData((char*)&stIpcInfo.szHostName, struXmlResult, "hostName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								
								if (struXmlResult.FindElem("IpAddress") && struXmlResult.IntoElem())
								{
									if (struXmlResult.FindElem("ipVersion"))
									{
										ConvertSingleNodeData((char*)&stIpcInfo.szIPVersion, struXmlResult, "ipVersion", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
									}
									if (struXmlResult.FindElem("ipAddress"))
									{
										ConvertSingleNodeData((char*)&stIpcInfo.szIPv4, struXmlResult, "ipAddress", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
									}
									if (struXmlResult.FindElem("ipv6Address"))
									{
										ConvertSingleNodeData((char*)&stIpcInfo.szIPv6, struXmlResult, "ipv6Address", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
									}
									
									struXmlResult.OutOfElem();
								}//IpAddress
								
								struXmlResult.OutOfElem();
							}//ipAddress
							
							if (struXmlResult.FindElem("portNo"))
							{
								ConvertSingleNodeData(&stIpcInfo.dwPort, struXmlResult, "portNo", NODE_STRING_TO_INT);
							}
							if (struXmlResult.FindElem("userName"))
							{
								ConvertSingleNodeData((char*)&stIpcInfo.szUser, struXmlResult, "userName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							}
							if (struXmlResult.FindElem("passWord"))
							{
								ConvertSingleNodeData((char*)&stIpcInfo.szPwd, struXmlResult, "passWord", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							}
							
							m_struTermInfo.aIPCInfo[m_struTermInfo.dwIpcInfoCount] = stIpcInfo;
							
							m_struTermInfo.dwIpcInfoCount++;

							if (m_struTermInfo.dwIpcInfoCount >= MAX_IPCS_A_TERMINAL)
							{
								break;
							}
							
							struXmlResult.OutOfElem();
						}
					}//IPC
					struXmlResult.OutOfElem();
				}//IPCList
				ConvertSingleNodeData(&m_struTermInfo.dwBelongGroup, struXmlResult, "belongGroup", NODE_STRING_TO_INT);
                ConvertSingleNodeData(&m_struTermInfo.dwOrgNo, struXmlResult, "orgNo", NODE_STRING_TO_INT);
				struXmlResult.OutOfElem();

				m_dwTermInfoCount = 1;
				m_dwTermInfoIndex = 0;
				m_dwTermID = m_struTermInfo.dwID;
				m_csTermName = m_struTermInfo.szTermName;
				m_csRegType = m_struTermInfo.szRegType;	
				m_CondCode = m_struTermInfo.szCondCode;//特征代码	
				m_csPullAddrFormatType = m_struTermInfo.szAddrFormatType;
				m_csPullHostName = m_struTermInfo.szHostName;
				m_csPullIPVersion = m_struTermInfo.szIPVersion;
				m_csPullIPv4 = m_struTermInfo.szIPv4;
				m_csPullIPv6 = m_struTermInfo.szIPv6;
				m_dwPullPort = m_struTermInfo.dwPort;
				m_csPullUserName = m_struTermInfo.szUser;
				m_csPullPwd = m_struTermInfo.szPwd;
				m_dwBelongGroup = m_struTermInfo.dwBelongGroup;
                m_dwOrgNo = m_struTermInfo.dwOrgNo;
				UpdateData(FALSE);

				memcpy(m_aIPCInfo, m_struTermInfo.aIPCInfo, sizeof(m_aIPCInfo));
				m_dwIpcInfoCount = m_struTermInfo.dwIpcInfoCount;
				m_pListIpc->DeleteAllItems();
				CString strInfo;
				for (int i = 0; i < m_dwIpcInfoCount; i++)
				{
					strInfo.Format("%d", i+1);
					int nRow = m_pListIpc->InsertItem(i, strInfo);//插入行 
					strInfo.Format("%d", m_aIPCInfo[i].dwID);
					m_pListIpc->SetItemText(nRow, 1, strInfo);//设置数据
					m_pListIpc->SetItemText(nRow, 2, m_aIPCInfo[i].szIpcType);//设置数据
				}
			}
		}
		else
		{
			m_pListTerm->DeleteAllItems();
			m_pListIpc->DeleteAllItems();
			//获取多个
			if(struXmlResult.FindElem("TerminalsList") && struXmlResult.IntoElem())
			{
				if (struXmlResult.FindElem("Terminals") && struXmlResult.IntoElem())
				{
					if (struXmlResult.FindElem("id"))
					{
						ConvertSingleNodeData(&m_paTermInfo[m_dwTermInfoCount].dwID, struXmlResult, "id", NODE_STRING_TO_INT);
					}
					if (struXmlResult.FindElem("terminalName"))
					{
						ConvertSingleNodeData((char*)&m_paTermInfo[m_dwTermInfoCount].szTermName, struXmlResult, "terminalName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
					}
					
					if (struXmlResult.FindElem("registerType"))
					{
						ConvertSingleNodeData((char*)&m_paTermInfo[m_dwTermInfoCount].szRegType, struXmlResult, "registerType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
					}
					
					if (struXmlResult.FindElem("PushModeInfo") && struXmlResult.IntoElem())
					{
						if (struXmlResult.FindElem("characteristicCode"))
						{
							ConvertSingleNodeData((char*)&m_paTermInfo[m_dwTermInfoCount].szCondCode, struXmlResult, "characteristicCode", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						}
						struXmlResult.OutOfElem();
					}
					if (struXmlResult.FindElem("PullModeInfo") && struXmlResult.IntoElem())
					{
						if (struXmlResult.FindElem("TerminalAddress") && struXmlResult.IntoElem())
						{
							if (struXmlResult.FindElem("addressingFormatType"))
							{
								ConvertSingleNodeData((char*)&m_paTermInfo[m_dwTermInfoCount].szAddrFormatType, struXmlResult, "addressingFormatType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							}
							
							if (struXmlResult.FindElem("hostName"))
							{
								ConvertSingleNodeData((char*)&m_paTermInfo[m_dwTermInfoCount].szHostName, struXmlResult, "hostName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							}
							
							if (struXmlResult.FindElem("IpAddress") && struXmlResult.IntoElem())
							{
								if (struXmlResult.FindElem("ipVersion"))
								{
									ConvertSingleNodeData((char*)&m_paTermInfo[m_dwTermInfoCount].szIPVersion, struXmlResult, "ipVersion", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								if (struXmlResult.FindElem("ipAddress"))
								{
									ConvertSingleNodeData((char*)&m_paTermInfo[m_dwTermInfoCount].szIPv4, struXmlResult, "ipAddress", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								if (struXmlResult.FindElem("ipv6Address"))
								{
									ConvertSingleNodeData((char*)&m_paTermInfo[m_dwTermInfoCount].szIPv6, struXmlResult, "ipv6Address", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								
								struXmlResult.OutOfElem();
							}//IpAddress
							
							struXmlResult.OutOfElem();
						}//ipAddress
						
						if (struXmlResult.FindElem("portNo"))
						{
							ConvertSingleNodeData(&m_paTermInfo[m_dwTermInfoCount].dwPort, struXmlResult, "portNo", NODE_STRING_TO_INT);
						}
						if (struXmlResult.FindElem("userName"))
						{
							ConvertSingleNodeData((char*)&m_paTermInfo[m_dwTermInfoCount].szUser, struXmlResult, "userName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						}
						if (struXmlResult.FindElem("passWord"))
						{
							ConvertSingleNodeData((char*)&m_paTermInfo[m_dwTermInfoCount].szPwd, struXmlResult, "passWord", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						}
						struXmlResult.OutOfElem();
					}//PullModeInfo
					
					if (struXmlResult.FindElem("IPCList") && struXmlResult.IntoElem())
					{
						if (struXmlResult.FindElem("IPC") && struXmlResult.IntoElem())
						{
							IPC_INFO stIpcInfo = {0};
							if (struXmlResult.FindElem("id"))
							{
								ConvertSingleNodeData(&stIpcInfo.dwID, struXmlResult, "id", NODE_STRING_TO_INT);
							}
							if (struXmlResult.FindElem("IPCType"))
							{
								ConvertSingleNodeData((char*)&stIpcInfo.szIpcType, struXmlResult, "IPCType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							}
							if (struXmlResult.FindElem("channelNo"))
							{
								ConvertSingleNodeData((char*)&stIpcInfo.dwTermiChannelNo, struXmlResult, "channelNo", NODE_STRING_TO_INT);
							}
							
							if (struXmlResult.FindElem("IPCAddress") && struXmlResult.IntoElem())
							{
								if (struXmlResult.FindElem("addressingFormatType"))
								{
									ConvertSingleNodeData((char*)&stIpcInfo.szAddrFormatType, struXmlResult, "addressingFormatType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								
								if (struXmlResult.FindElem("hostName"))
								{
									ConvertSingleNodeData((char*)&stIpcInfo.szHostName, struXmlResult, "hostName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								
								if (struXmlResult.FindElem("IpAddress") && struXmlResult.IntoElem())
								{
									if (struXmlResult.FindElem("ipVersion"))
									{
										ConvertSingleNodeData((char*)&stIpcInfo.szIPVersion, struXmlResult, "ipVersion", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
									}
									if (struXmlResult.FindElem("ipAddress"))
									{
										ConvertSingleNodeData((char*)&stIpcInfo.szIPv4, struXmlResult, "ipAddress", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
									}
									if (struXmlResult.FindElem("ipv6Address"))
									{
										ConvertSingleNodeData((char*)&stIpcInfo.szIPv6, struXmlResult, "ipv6Address", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
									}
									
									struXmlResult.OutOfElem();
								}//IpAddress
								
								struXmlResult.OutOfElem();
							}//ipAddress
							
							if (struXmlResult.FindElem("portNo"))
							{
								ConvertSingleNodeData(&stIpcInfo.dwPort, struXmlResult, "portNo", NODE_STRING_TO_INT);
							}
							if (struXmlResult.FindElem("userName"))
							{
								ConvertSingleNodeData((char*)&stIpcInfo.szUser, struXmlResult, "userName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							}
							if (struXmlResult.FindElem("passWord"))
							{
								ConvertSingleNodeData((char*)&stIpcInfo.szPwd, struXmlResult, "passWord", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							}
							
							m_paTermInfo[m_dwTermInfoCount].aIPCInfo[m_paTermInfo[m_dwTermInfoCount].dwIpcInfoCount] = stIpcInfo;
							
							m_paTermInfo[m_dwTermInfoCount].dwIpcInfoCount++;
							
							struXmlResult.OutOfElem();

							while (struXmlResult.NextSibElem() && struXmlResult.IntoElem())
							{
								IPC_INFO stIpcInfo = {0};
								if (struXmlResult.FindElem("id"))
								{
									ConvertSingleNodeData(&stIpcInfo.dwID, struXmlResult, "id", NODE_STRING_TO_INT);
								}
								if (struXmlResult.FindElem("IPCType"))
								{
									ConvertSingleNodeData((char*)&stIpcInfo.szIpcType, struXmlResult, "IPCType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								if (struXmlResult.FindElem("channelNo"))
								{
									ConvertSingleNodeData((char*)&stIpcInfo.dwTermiChannelNo, struXmlResult, "channelNo", NODE_STRING_TO_INT);
								}
								
								if (struXmlResult.FindElem("IPCAddress") && struXmlResult.IntoElem())
								{
									if (struXmlResult.FindElem("addressingFormatType"))
									{
										ConvertSingleNodeData((char*)&stIpcInfo.szAddrFormatType, struXmlResult, "addressingFormatType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
									}
									
									if (struXmlResult.FindElem("hostName"))
									{
										ConvertSingleNodeData((char*)&stIpcInfo.szHostName, struXmlResult, "hostName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
									}
									
									if (struXmlResult.FindElem("IpAddress") && struXmlResult.IntoElem())
									{
										if (struXmlResult.FindElem("ipVersion"))
										{
											ConvertSingleNodeData((char*)&stIpcInfo.szIPVersion, struXmlResult, "ipVersion", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
										}
										if (struXmlResult.FindElem("ipAddress"))
										{
											ConvertSingleNodeData((char*)&stIpcInfo.szIPv4, struXmlResult, "ipAddress", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
										}
										if (struXmlResult.FindElem("ipv6Address"))
										{
											ConvertSingleNodeData((char*)&stIpcInfo.szIPv6, struXmlResult, "ipv6Address", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
										}
										
										struXmlResult.OutOfElem();
									}//IpAddress
									
									struXmlResult.OutOfElem();
								}//ipAddress
								
								if (struXmlResult.FindElem("portNo"))
								{
									ConvertSingleNodeData(&stIpcInfo.dwPort, struXmlResult, "portNo", NODE_STRING_TO_INT);
								}
								if (struXmlResult.FindElem("userName"))
								{
									ConvertSingleNodeData((char*)&stIpcInfo.szUser, struXmlResult, "userName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								if (struXmlResult.FindElem("passWord"))
								{
									ConvertSingleNodeData((char*)&stIpcInfo.szPwd, struXmlResult, "passWord", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								
								m_paTermInfo[m_dwTermInfoCount].aIPCInfo[m_paTermInfo[m_dwTermInfoCount].dwIpcInfoCount] = stIpcInfo;
								
								m_paTermInfo[m_dwTermInfoCount].dwIpcInfoCount++;

								if (m_paTermInfo[m_dwTermInfoCount].dwIpcInfoCount >= MAX_IPCS_A_TERMINAL)
								{
									break;
								}
								
								struXmlResult.OutOfElem();
							}
						}
						struXmlResult.OutOfElem();
					}
					ConvertSingleNodeData(&m_struTermInfo.dwBelongGroup, struXmlResult, "belongGroup", NODE_STRING_TO_INT);
                    ConvertSingleNodeData(&m_struTermInfo.dwOrgNo, struXmlResult, "orgNo", NODE_STRING_TO_INT);
					struXmlResult.OutOfElem();
					
					CString strInfo;
					strInfo.Format("%d", m_dwTermInfoCount+1);
					int nRow = m_pListTerm->InsertItem(m_dwTermInfoCount, strInfo);//插入行 
					strInfo.Format("%d", m_paTermInfo[m_dwTermInfoCount].dwID);
					m_pListTerm->SetItemText(nRow, 1, strInfo);//设置数据
					m_pListTerm->SetItemText(nRow, 2, m_paTermInfo[m_dwTermInfoCount].szTermName);//设置数据
					
					m_dwTermInfoCount++;

					while (struXmlResult.NextSibElem() && struXmlResult.IntoElem())
					{
						if (struXmlResult.FindElem("id"))
						{
							ConvertSingleNodeData(&m_paTermInfo[m_dwTermInfoCount].dwID, struXmlResult, "id", NODE_STRING_TO_INT);
						}
						if (struXmlResult.FindElem("terminalName"))
						{
							ConvertSingleNodeData((char*)&m_paTermInfo[m_dwTermInfoCount].szTermName, struXmlResult, "terminalName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						}
						
						if (struXmlResult.FindElem("registerType"))
						{
							ConvertSingleNodeData((char*)&m_paTermInfo[m_dwTermInfoCount].szRegType, struXmlResult, "registerType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
						}
						
						if (struXmlResult.FindElem("PushModeInfo") && struXmlResult.IntoElem())
						{
							if (struXmlResult.FindElem("characteristicCode"))
							{
								ConvertSingleNodeData((char*)&m_paTermInfo[m_dwTermInfoCount].szCondCode, struXmlResult, "characteristicCode", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							}
							struXmlResult.OutOfElem();
						}
						if (struXmlResult.FindElem("PullModeInfo") && struXmlResult.IntoElem())
						{
							if (struXmlResult.FindElem("TerminalAddress") && struXmlResult.IntoElem())
							{
								if (struXmlResult.FindElem("addressingFormatType"))
								{
									ConvertSingleNodeData((char*)&m_paTermInfo[m_dwTermInfoCount].szAddrFormatType, struXmlResult, "addressingFormatType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								
								if (struXmlResult.FindElem("hostName"))
								{
									ConvertSingleNodeData((char*)&m_paTermInfo[m_dwTermInfoCount].szHostName, struXmlResult, "hostName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								
								if (struXmlResult.FindElem("IpAddress") && struXmlResult.IntoElem())
								{
									if (struXmlResult.FindElem("ipVersion"))
									{
										ConvertSingleNodeData((char*)&m_paTermInfo[m_dwTermInfoCount].szIPVersion, struXmlResult, "ipVersion", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
									}
									if (struXmlResult.FindElem("ipAddress"))
									{
										ConvertSingleNodeData((char*)&m_paTermInfo[m_dwTermInfoCount].szIPv4, struXmlResult, "ipAddress", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
									}
									if (struXmlResult.FindElem("ipv6Address"))
									{
										ConvertSingleNodeData((char*)&m_paTermInfo[m_dwTermInfoCount].szIPv6, struXmlResult, "ipv6Address", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
									}
									
									struXmlResult.OutOfElem();
								}//IpAddress
								
								struXmlResult.OutOfElem();
							}//ipAddress
							
							if (struXmlResult.FindElem("portNo"))
							{
								ConvertSingleNodeData(&m_paTermInfo[m_dwTermInfoCount].dwPort, struXmlResult, "portNo", NODE_STRING_TO_INT);
							}
							if (struXmlResult.FindElem("userName"))
							{
								ConvertSingleNodeData((char*)&m_paTermInfo[m_dwTermInfoCount].szUser, struXmlResult, "userName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							}
							if (struXmlResult.FindElem("passWord"))
							{
								ConvertSingleNodeData((char*)&m_paTermInfo[m_dwTermInfoCount].szPwd, struXmlResult, "passWord", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
							}
							struXmlResult.OutOfElem();
						}//PullModeInfo
						
						if (struXmlResult.FindElem("IPCList") && struXmlResult.IntoElem())
						{
							if (struXmlResult.FindElem("IPC") && struXmlResult.IntoElem())
							{
								IPC_INFO stIpcInfo = {0};
								if (struXmlResult.FindElem("id"))
								{
									ConvertSingleNodeData(&stIpcInfo.dwID, struXmlResult, "id", NODE_STRING_TO_INT);
								}
								if (struXmlResult.FindElem("IPCType"))
								{
									ConvertSingleNodeData((char*)&stIpcInfo.szIpcType, struXmlResult, "IPCType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								if (struXmlResult.FindElem("channelNo"))
								{
									ConvertSingleNodeData((char*)&stIpcInfo.dwTermiChannelNo, struXmlResult, "channelNo", NODE_STRING_TO_INT);
								}
								
								if (struXmlResult.FindElem("IPCAddress") && struXmlResult.IntoElem())
								{
									if (struXmlResult.FindElem("addressingFormatType"))
									{
										ConvertSingleNodeData((char*)&stIpcInfo.szAddrFormatType, struXmlResult, "addressingFormatType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
									}
									
									if (struXmlResult.FindElem("hostName"))
									{
										ConvertSingleNodeData((char*)&stIpcInfo.szHostName, struXmlResult, "hostName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
									}
									
									if (struXmlResult.FindElem("IpAddress") && struXmlResult.IntoElem())
									{
										if (struXmlResult.FindElem("ipVersion"))
										{
											ConvertSingleNodeData((char*)&stIpcInfo.szIPVersion, struXmlResult, "ipVersion", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
										}
										if (struXmlResult.FindElem("ipAddress"))
										{
											ConvertSingleNodeData((char*)&stIpcInfo.szIPv4, struXmlResult, "ipAddress", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
										}
										if (struXmlResult.FindElem("ipv6Address"))
										{
											ConvertSingleNodeData((char*)&stIpcInfo.szIPv6, struXmlResult, "ipv6Address", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
										}
										
										struXmlResult.OutOfElem();
									}//IpAddress
									
									struXmlResult.OutOfElem();
								}//ipAddress
								
								if (struXmlResult.FindElem("portNo"))
								{
									ConvertSingleNodeData(&stIpcInfo.dwPort, struXmlResult, "portNo", NODE_STRING_TO_INT);
								}
								if (struXmlResult.FindElem("userName"))
								{
									ConvertSingleNodeData((char*)&stIpcInfo.szUser, struXmlResult, "userName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								if (struXmlResult.FindElem("passWord"))
								{
									ConvertSingleNodeData((char*)&stIpcInfo.szPwd, struXmlResult, "passWord", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
								}
								
								m_paTermInfo[m_dwTermInfoCount].aIPCInfo[m_paTermInfo[m_dwTermInfoCount].dwIpcInfoCount] = stIpcInfo;
								
								m_paTermInfo[m_dwTermInfoCount].dwIpcInfoCount++;
								
								struXmlResult.OutOfElem();
								
								while (struXmlResult.NextSibElem() && struXmlResult.IntoElem())
								{
									IPC_INFO stIpcInfo = {0};
									if (struXmlResult.FindElem("id"))
									{
										ConvertSingleNodeData(&stIpcInfo.dwID, struXmlResult, "id", NODE_STRING_TO_INT);
									}
									if (struXmlResult.FindElem("IPCType"))
									{
										ConvertSingleNodeData((char*)&stIpcInfo.szIpcType, struXmlResult, "IPCType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
									}
									if (struXmlResult.FindElem("channelNo"))
									{
										ConvertSingleNodeData((char*)&stIpcInfo.dwTermiChannelNo, struXmlResult, "channelNo", NODE_STRING_TO_INT);
									}
									
									if (struXmlResult.FindElem("IPCAddress") && struXmlResult.IntoElem())
									{
										if (struXmlResult.FindElem("addressingFormatType"))
										{
											ConvertSingleNodeData((char*)&stIpcInfo.szAddrFormatType, struXmlResult, "addressingFormatType", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
										}
										
										if (struXmlResult.FindElem("hostName"))
										{
											ConvertSingleNodeData((char*)&stIpcInfo.szHostName, struXmlResult, "hostName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
										}
										
										if (struXmlResult.FindElem("IpAddress") && struXmlResult.IntoElem())
										{
											if (struXmlResult.FindElem("ipVersion"))
											{
												ConvertSingleNodeData((char*)&stIpcInfo.szIPVersion, struXmlResult, "ipVersion", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
											}
											if (struXmlResult.FindElem("ipAddress"))
											{
												ConvertSingleNodeData((char*)&stIpcInfo.szIPv4, struXmlResult, "ipAddress", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
											}
											if (struXmlResult.FindElem("ipv6Address"))
											{
												ConvertSingleNodeData((char*)&stIpcInfo.szIPv6, struXmlResult, "ipv6Address", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
											}
											
											struXmlResult.OutOfElem();
										}//IpAddress
										
										struXmlResult.OutOfElem();
									}//ipAddress
									
									if (struXmlResult.FindElem("portNo"))
									{
										ConvertSingleNodeData(&stIpcInfo.dwPort, struXmlResult, "portNo", NODE_STRING_TO_INT);
									}
									if (struXmlResult.FindElem("userName"))
									{
										ConvertSingleNodeData((char*)&stIpcInfo.szUser, struXmlResult, "userName", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
									}
									if (struXmlResult.FindElem("passWord"))
									{
										ConvertSingleNodeData((char*)&stIpcInfo.szPwd, struXmlResult, "passWord", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
									}
									
									m_paTermInfo[m_dwTermInfoCount].aIPCInfo[m_paTermInfo[m_dwTermInfoCount].dwIpcInfoCount] = stIpcInfo;
									
									m_paTermInfo[m_dwTermInfoCount].dwIpcInfoCount++;

									if (m_paTermInfo[m_dwTermInfoCount].dwIpcInfoCount >= MAX_IPCS_A_TERMINAL)
									{
										break;
									}
									
									struXmlResult.OutOfElem();
								}
							}
							struXmlResult.OutOfElem();
						}
						ConvertSingleNodeData(&m_struTermInfo.dwBelongGroup, struXmlResult, "belongGroup", NODE_STRING_TO_INT);
						struXmlResult.OutOfElem();
					
						CString strInfo;
						strInfo.Format("%d", m_dwTermInfoCount+1);
						int nRow = m_pListTerm->InsertItem(m_dwTermInfoCount, strInfo);//插入行 
						strInfo.Format("%d", m_paTermInfo[m_dwTermInfoCount].dwID);
						m_pListTerm->SetItemText(nRow, 1, strInfo);//设置数据
						m_pListTerm->SetItemText(nRow, 2, m_paTermInfo[m_dwTermInfoCount].szTermName);//设置数据
					
						m_dwTermInfoCount++;

						if (m_dwTermInfoCount >= MAX_NUM_TERMINAL)
						{
							break;
						}
					}
				}
				struXmlResult.OutOfElem(); //TerminalsList
			}
		}
	}	
}

void CDlgTermManage::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	memset(&m_szRequestURL, '\0' ,sizeof(m_szRequestURL));
	m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;
	memset(m_pXMLResultBuf, 0, ISAPI_DATA_LEN);
	m_dwXMLResultBufLen = ISAPI_DATA_LEN;
	memset(&m_szXMLStatus, '\0', sizeof(m_szXMLStatus));

	char szTerminalName[MAX_XML_ELEM_LEN] = {0};
	char szRegType[MAX_XML_ELEM_LEN] = {0};
	char szCondCode[MAX_XML_ELEM_LEN] = {0};
	char szAddrFormatType[MAX_XML_ELEM_LEN] = {0};
	char szHostName[MAX_XML_ELEM_LEN] = {0};
	char szIPVersion[MAX_XML_ELEM_LEN] = {0};
	char szIPv4[MAX_XML_ELEM_LEN] = {0};
	char szIPv6[MAX_XML_ELEM_LEN] = {0};
	char szUser[MAX_XML_ELEM_LEN] = {0};
	char szPwd[MAX_XML_ELEM_LEN] = {0};

	CSTRING_TO_CHARS(m_csTermName, szTerminalName);
	CSTRING_TO_CHARS(m_csRegType, szRegType);
	CSTRING_TO_CHARS(m_CondCode, szCondCode);
	CSTRING_TO_CHARS(m_csPullAddrFormatType, szAddrFormatType);
	CSTRING_TO_CHARS(m_csPullHostName, szHostName);
	CSTRING_TO_CHARS(m_csPullIPVersion, szIPVersion);
	CSTRING_TO_CHARS(m_csPullIPv4, szIPv4);
	CSTRING_TO_CHARS(m_csPullIPv6, szIPv6);
	CSTRING_TO_CHARS(m_csPullUserName, szUser);
	CSTRING_TO_CHARS(m_csPullPwd, szPwd);

	
	//填充并转化信息
	CXmlBase struXmlParam;
	struXmlParam.CreateRoot("Terminals");
	struXmlParam.SetAttribute("version", "2.0");
	struXmlParam.SetAttribute("xmlns", "http://www.isapi.org/ver20/XMLSchema");
	
	ConvertSingleNodeData(&m_dwTermID, struXmlParam, "id", NODE_INT_TO_STRING);
	ConvertSingleNodeData((char*)&szTerminalName, struXmlParam, "terminalName", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
	ConvertSingleNodeData((char*)&szRegType, struXmlParam, "registerType", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);

	if (struXmlParam.AddNode("PushModeInfo"))
	{
		ConvertSingleNodeData((char*)&szCondCode, struXmlParam, "characteristicCode", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
		struXmlParam.OutOfElem();
	}

	if (struXmlParam.AddNode("PullModeInfo"))
	{
		if (struXmlParam.AddNode("TerminalAddress"))
		{
			ConvertSingleNodeData((char*)&szAddrFormatType, struXmlParam, "addressingFormatType", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
			ConvertSingleNodeData((char*)&szHostName, struXmlParam, "hostName", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
			if (struXmlParam.AddNode("IpAddress"))
			{
				ConvertSingleNodeData((char*)&szIPVersion, struXmlParam, "ipVersion", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
				ConvertSingleNodeData((char*)&szIPv4, struXmlParam, "ipAddress", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
				ConvertSingleNodeData((char*)&szIPv6, struXmlParam, "ipv6Address", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
				struXmlParam.OutOfElem();
			}
			struXmlParam.OutOfElem();
		}
		ConvertSingleNodeData(&m_dwPullPort, struXmlParam, "portNo", NODE_INT_TO_STRING);
		ConvertSingleNodeData((char*)&szUser, struXmlParam, "userName", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
		ConvertSingleNodeData((char*)&szPwd, struXmlParam, "passWord", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
		struXmlParam.OutOfElem();
	}

	if (struXmlParam.AddNode("IPCList"))
	{
		IPC_INFO stIpcInfo = {0};
		for (int i = 0; i < m_dwIpcInfoCount; i++)
		{
			stIpcInfo = m_aIPCInfo[i];
			if (struXmlParam.AddNode("IPC"))
			{
				ConvertSingleNodeData(&stIpcInfo.dwID, struXmlParam, "id", NODE_INT_TO_STRING);
				ConvertSingleNodeData((char*)&stIpcInfo.szIpcType, struXmlParam, "IPCType", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
				ConvertSingleNodeData((char*)&stIpcInfo.dwTermiChannelNo, struXmlParam, "channelNo", NODE_INT_TO_STRING);
				if (struXmlParam.AddNode("IPCAddress"))
				{
					ConvertSingleNodeData((char*)&stIpcInfo.szAddrFormatType, struXmlParam, "addressingFormatType", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
					ConvertSingleNodeData((char*)&stIpcInfo.szHostName, struXmlParam, "hostName", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
					if (struXmlParam.AddNode("IpAddress"))
					{
						ConvertSingleNodeData((char*)&stIpcInfo.szIPVersion, struXmlParam, "ipVersion", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
						ConvertSingleNodeData((char*)&stIpcInfo.szIPv4, struXmlParam, "ipAddress", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
						ConvertSingleNodeData((char*)&stIpcInfo.szIPv6, struXmlParam, "ipv6Address", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
						struXmlParam.OutOfElem();
					}
					struXmlParam.OutOfElem();
				}
				ConvertSingleNodeData(&stIpcInfo.dwPort, struXmlParam, "portNo", NODE_INT_TO_STRING);
				ConvertSingleNodeData((char*)&stIpcInfo.szUser, struXmlParam, "userName", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
				ConvertSingleNodeData((char*)&stIpcInfo.szPwd, struXmlParam, "passWord", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);

				struXmlParam.OutOfElem();
			}
		}
		struXmlParam.OutOfElem();
	}
	ConvertSingleNodeData(&m_dwBelongGroup, struXmlParam, "belongGroup", NODE_INT_TO_STRING);

	if (!PrintXmlToNewBuffer(&m_pXMLParamBuf, m_dwXMLParamBufLen, struXmlParam))
	{
		return;
	}

	NET_DVR_XML_CONFIG_INPUT struXMLCfgInput = {0};
	struXMLCfgInput.dwSize = sizeof(struXMLCfgInput);
	sprintf((char*)m_szRequestURL, "PUT /ISAPI/Publish/TerminalMgr/terminals/%d\r\n", m_dwTermID);
	struXMLCfgInput.lpRequestUrl = (char*)m_szRequestURL;
	struXMLCfgInput.dwRequestUrlLen = strlen(m_szRequestURL);
	struXMLCfgInput.lpInBuffer      = m_pXMLParamBuf;
	struXMLCfgInput.dwInBufferSize  = m_dwXMLParamBufLen;
	
	NET_DVR_XML_CONFIG_OUTPUT struXMLCfgOutput = {0};
	struXMLCfgOutput.dwSize = sizeof(struXMLCfgOutput);
	struXMLCfgOutput.lpOutBuffer = NULL;
	struXMLCfgOutput.dwOutBufferSize = 0;
	struXMLCfgOutput.lpStatusBuffer = (char*)m_szXMLStatus;
	struXMLCfgOutput.dwStatusSize = sizeof(m_szXMLStatus);
	
	if (NET_DVR_STDXMLConfig(m_lUserID, &struXMLCfgInput, &struXMLCfgOutput))
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");			
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
    }
	
	delete[] m_pXMLParamBuf;
	m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;
	
	UpdateData(FALSE);	
	
}

void CDlgTermManage::OnBtnAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	memset(&m_szRequestURL, '\0' ,sizeof(m_szRequestURL));
	m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;
	memset(m_pXMLResultBuf, 0, ISAPI_DATA_LEN);
	m_dwXMLResultBufLen = ISAPI_DATA_LEN;
	memset(&m_szXMLStatus, '\0', sizeof(m_szXMLStatus));

	char szTerminalName[MAX_XML_ELEM_LEN] = {0};
	char szRegType[MAX_XML_ELEM_LEN] = {0};
	char szCondCode[MAX_XML_ELEM_LEN] = {0};
	char szAddrFormatType[MAX_XML_ELEM_LEN] = {0};
	char szHostName[MAX_XML_ELEM_LEN] = {0};
	char szIPVersion[MAX_XML_ELEM_LEN] = {0};
	char szIPv4[MAX_XML_ELEM_LEN] = {0};
	char szIPv6[MAX_XML_ELEM_LEN] = {0};
	char szUser[MAX_XML_ELEM_LEN] = {0};
	char szPwd[MAX_XML_ELEM_LEN] = {0};

	CSTRING_TO_CHARS(m_csTermName, szTerminalName);
	CSTRING_TO_CHARS(m_csRegType, szRegType);
	CSTRING_TO_CHARS(m_CondCode, szCondCode);
	CSTRING_TO_CHARS(m_csPullAddrFormatType, szAddrFormatType);
	CSTRING_TO_CHARS(m_csPullHostName, szHostName);
	CSTRING_TO_CHARS(m_csPullIPVersion, szIPVersion);
	CSTRING_TO_CHARS(m_csPullIPv4, szIPv4);
	CSTRING_TO_CHARS(m_csPullIPv6, szIPv6);
	CSTRING_TO_CHARS(m_csPullUserName, szUser);
	CSTRING_TO_CHARS(m_csPullPwd, szPwd);

	
	//填充并转化信息
	CXmlBase struXmlParam;
	struXmlParam.CreateRoot("Terminals");
	struXmlParam.SetAttribute("version", "2.0");
	struXmlParam.SetAttribute("xmlns", "http://www.isapi.org/ver20/XMLSchema");
	
	ConvertSingleNodeData(&m_dwTermID, struXmlParam, "id", NODE_INT_TO_STRING);
	ConvertSingleNodeData((char*)&szTerminalName, struXmlParam, "terminalName", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
	ConvertSingleNodeData((char*)&szRegType, struXmlParam, "registerType", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);

	if (struXmlParam.AddNode("PushModeInfo"))
	{
		ConvertSingleNodeData((char*)&szCondCode, struXmlParam, "characteristicCode", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
		struXmlParam.OutOfElem();
	}

	if (struXmlParam.AddNode("PullModeInfo"))
	{
		if (struXmlParam.AddNode("TerminalAddress"))
		{
			ConvertSingleNodeData((char*)&szAddrFormatType, struXmlParam, "addressingFormatType", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
			ConvertSingleNodeData((char*)&szHostName, struXmlParam, "hostName", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
			if (struXmlParam.AddNode("IpAddress"))
			{
				ConvertSingleNodeData((char*)&szIPVersion, struXmlParam, "ipVersion", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
				ConvertSingleNodeData((char*)&szIPv4, struXmlParam, "ipAddress", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
				ConvertSingleNodeData((char*)&szIPv6, struXmlParam, "ipv6Address", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
				struXmlParam.OutOfElem();
			}
			struXmlParam.OutOfElem();
		}
		ConvertSingleNodeData(&m_dwPullPort, struXmlParam, "portNo", NODE_INT_TO_STRING);
		ConvertSingleNodeData((char*)&szUser, struXmlParam, "userName", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
		ConvertSingleNodeData((char*)&szPwd, struXmlParam, "passWord", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
		struXmlParam.OutOfElem();
	}

	if (struXmlParam.AddNode("IPCList"))
	{
		IPC_INFO stIpcInfo = {0};
		for (int i = 0; i < m_dwIpcInfoCount; i++)
		{

			stIpcInfo = m_aIPCInfo[i];
			if (struXmlParam.AddNode("IPC"))
			{

				ConvertSingleNodeData(&stIpcInfo.dwID, struXmlParam, "id", NODE_INT_TO_STRING);
				ConvertSingleNodeData((char*)&stIpcInfo.szIpcType, struXmlParam, "IPCType", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
				ConvertSingleNodeData((char*)&stIpcInfo.dwTermiChannelNo, struXmlParam, "channelNo", NODE_INT_TO_STRING);
				if (struXmlParam.AddNode("IPCAddress"))
				{
					ConvertSingleNodeData((char*)&stIpcInfo.szAddrFormatType, struXmlParam, "addressingFormatType", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
					ConvertSingleNodeData((char*)&stIpcInfo.szHostName, struXmlParam, "hostName", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
					if (struXmlParam.AddNode("IpAddress"))
					{
						ConvertSingleNodeData((char*)&stIpcInfo.szIPVersion, struXmlParam, "ipVersion", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
						ConvertSingleNodeData((char*)&stIpcInfo.szIPv4, struXmlParam, "ipAddress", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
						ConvertSingleNodeData((char*)&stIpcInfo.szIPv6, struXmlParam, "ipv6Address", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
						struXmlParam.OutOfElem();
					}
					struXmlParam.OutOfElem();
				}
				ConvertSingleNodeData(&stIpcInfo.dwPort, struXmlParam, "portNo", NODE_INT_TO_STRING);
				ConvertSingleNodeData((char*)&stIpcInfo.szUser, struXmlParam, "userName", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);
				ConvertSingleNodeData((char*)&stIpcInfo.szPwd, struXmlParam, "passWord", NODE_ARRAY_TO_STRING, MAX_XML_ELEM_LEN);

				struXmlParam.OutOfElem();
			}
		}
		struXmlParam.OutOfElem();
	}
	ConvertSingleNodeData(&m_dwBelongGroup, struXmlParam, "belongGroup", NODE_INT_TO_STRING);
    ConvertSingleNodeData(&m_dwOrgNo, struXmlParam, "orgNo", NODE_INT_TO_STRING);

	if (!PrintXmlToNewBuffer(&m_pXMLParamBuf, m_dwXMLParamBufLen, struXmlParam))
	{
		return;
	}

	NET_DVR_XML_CONFIG_INPUT struXMLCfgInput = {0};
	struXMLCfgInput.dwSize = sizeof(struXMLCfgInput);
	sprintf((char*)m_szRequestURL, "POST /ISAPI/Publish/TerminalMgr/terminals\r\n");
	struXMLCfgInput.lpRequestUrl = (char*)m_szRequestURL;
	struXMLCfgInput.dwRequestUrlLen = strlen(m_szRequestURL);
	struXMLCfgInput.lpInBuffer      = m_pXMLParamBuf;
	struXMLCfgInput.dwInBufferSize  = m_dwXMLParamBufLen;
	
	NET_DVR_XML_CONFIG_OUTPUT struXMLCfgOutput = {0};
	struXMLCfgOutput.dwSize = sizeof(struXMLCfgOutput);
	struXMLCfgOutput.lpOutBuffer = NULL;
	struXMLCfgOutput.dwOutBufferSize = 0;
	struXMLCfgOutput.lpStatusBuffer = (char*)m_szXMLStatus;
	struXMLCfgOutput.dwStatusSize = sizeof(m_szXMLStatus);
	
	if (NET_DVR_STDXMLConfig(m_lUserID, &struXMLCfgInput, &struXMLCfgOutput))
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");			
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
    }
	
	m_dwTermID = GetResponseStatusID(m_szXMLStatus);
	
	delete[] m_pXMLParamBuf;
	m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;
	
	UpdateData(FALSE);		
}

void CDlgTermManage::OnBtnDel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	memset(&m_szRequestURL, '\0' ,sizeof(m_szRequestURL));
	m_pXMLParamBuf = NULL;
	m_dwXMLParamBufLen = 0;
	memset(m_pXMLResultBuf, 0, ISAPI_DATA_LEN);
	m_dwXMLResultBufLen = ISAPI_DATA_LEN;
	memset(&m_szXMLStatus, '\0', sizeof(m_szXMLStatus));
		
	NET_DVR_XML_CONFIG_INPUT struXMLCfgInput = {0};
	struXMLCfgInput.dwSize = sizeof(struXMLCfgInput);
	sprintf((char*)m_szRequestURL, "DELETE /ISAPI/Publish/TerminalMgr/terminals/%d\r\n", m_dwTermID);
	struXMLCfgInput.lpRequestUrl = (char*)m_szRequestURL;
	struXMLCfgInput.dwRequestUrlLen = strlen(m_szRequestURL);
	struXMLCfgInput.lpInBuffer      = NULL;
	struXMLCfgInput.dwInBufferSize  = 0;
	
	NET_DVR_XML_CONFIG_OUTPUT struXMLCfgOutput = {0};
	struXMLCfgOutput.dwSize = sizeof(struXMLCfgOutput);
	struXMLCfgOutput.lpOutBuffer = NULL;
	struXMLCfgOutput.dwOutBufferSize = 0;
	struXMLCfgOutput.lpStatusBuffer = (char*)m_szXMLStatus;
	struXMLCfgOutput.dwStatusSize = sizeof(m_szXMLStatus);
	
	if (NET_DVR_STDXMLConfig(m_lUserID, &struXMLCfgInput, &struXMLCfgOutput))
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");			
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
    }
	
	UpdateData(FALSE);
	
}

CString CDlgTermManage::ProcessXMLStatus(int iDeviceIndex, char* lpStatusBuf)
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
            if (struXmlStatus.FindElem("statusCode") && struXmlStatus.IntoElem())
            {
                ConvertSingleNodeData(&dwStatusCode, struXmlStatus, "statusCode", NODE_STRING_TO_INT);
				
                sprintf((char*)szStatusInfo, "%s", GetStatusCodeInfo(dwStatusCode));
                if (dwStatusCode == 0 || dwStatusCode == 1)
                {
                    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szStatusInfo);
                }
                else
                {
                    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szStatusInfo);
                    if (struXmlStatus.FindElem("statusString") && struXmlStatus.IntoElem())
                    {
                        ConvertSingleNodeData(&szStatusString, struXmlStatus, "statusString", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
                        sprintf((char*)szStatusInfo, "StatusString: %s", szStatusString);
                        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szStatusInfo);
                        struXmlStatus.OutOfElem();
                    }	
                }
				if (struXmlStatus.FindElem("ID") && struXmlStatus.IntoElem())
				{
					ConvertSingleNodeData(&szID, struXmlStatus, "ID", NODE_STRING_TO_ARRAY, MAX_XML_ELEM_LEN);
					csRet = szID;
					struXmlStatus.OutOfElem();
				}

                struXmlStatus.OutOfElem();
            }
            struXmlStatus.OutOfElem();	
        }
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Status XML Parse Error");
    }
	return csRet;
}

void CDlgTermManage::OnClickLstTermInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    
	if(pNMListView->iItem != -1)
    {
		//判断Item状态，是否为选中状态
		if(m_pListTerm->GetItemState(pNMListView->iItem, LVIS_SELECTED) == LVIS_SELECTED)
		{
			m_dwTermInfoIndex = pNMListView->iItem;
			
			m_dwTermID = m_paTermInfo[m_dwTermInfoIndex].dwID;
			m_csTermName = m_paTermInfo[m_dwTermInfoIndex].szTermName;
			m_csRegType = m_paTermInfo[m_dwTermInfoIndex].szRegType;	
			m_CondCode = m_paTermInfo[m_dwTermInfoIndex].szCondCode;//特征代码	
			m_csPullAddrFormatType = m_paTermInfo[m_dwTermInfoIndex].szAddrFormatType;
			m_csPullHostName = m_paTermInfo[m_dwTermInfoIndex].szHostName;
			m_csPullIPVersion = m_paTermInfo[m_dwTermInfoIndex].szIPVersion;
			m_csPullIPv4 = m_paTermInfo[m_dwTermInfoIndex].szIPv4;
			m_csPullIPv6 = m_paTermInfo[m_dwTermInfoIndex].szIPv6;
			m_dwPullPort = m_paTermInfo[m_dwTermInfoIndex].dwPort;
			m_csPullUserName = m_paTermInfo[m_dwTermInfoIndex].szUser;
			m_csPullPwd = m_paTermInfo[m_dwTermInfoIndex].szPwd;
			m_dwBelongGroup = m_paTermInfo[m_dwTermInfoIndex].dwBelongGroup;
			
			m_pListIpc->DeleteAllItems();
			
			memcpy(m_aIPCInfo, m_paTermInfo[m_dwTermInfoIndex].aIPCInfo, sizeof(m_aIPCInfo));
			m_dwIpcInfoCount = m_paTermInfo[m_dwTermInfoIndex].dwIpcInfoCount;
			CString strInfo;
			for (int i = 0; i < m_dwIpcInfoCount; i++)
			{
				strInfo.Format("%d", i+1);
				int nRow = m_pListIpc->InsertItem(i, strInfo);//插入行 
				strInfo.Format("%d", m_aIPCInfo[i].dwID);
				m_pListIpc->SetItemText(nRow, 1, strInfo);//设置数据
				m_pListIpc->SetItemText(nRow, 2, m_aIPCInfo[i].szIpcType);//设置数据
			}
			UpdateData(FALSE);
		}
    }
	
	*pResult = 0;
}

void CDlgTermManage::OnClickLstIpcInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if(pNMListView->iItem != -1)
    {
		//判断Item状态，是否为选中状态
		if(m_pListIpc->GetItemState(pNMListView->iItem, LVIS_SELECTED) == LVIS_SELECTED)
		{
			m_dwIpcInfoIndex = pNMListView->iItem;
			
			m_dwIpcID = m_aIPCInfo[m_dwIpcInfoIndex].dwID;
			m_csIpcType = m_aIPCInfo[m_dwIpcInfoIndex].szIpcType;
			m_csIpcAddrFormatType = m_aIPCInfo[m_dwIpcInfoIndex].szAddrFormatType;
			m_csIpcHostName = m_aIPCInfo[m_dwIpcInfoIndex].szHostName;
			m_csIpcIPVersion = m_aIPCInfo[m_dwIpcInfoIndex].szIPVersion;
			m_csIpcIPv4 = m_aIPCInfo[m_dwIpcInfoIndex].szIPv4;
			m_csIpcIPv6 = m_aIPCInfo[m_dwIpcInfoIndex].szIPv6;
			m_dwIpcPort = m_aIPCInfo[m_dwIpcInfoIndex].dwPort;
			m_csIpcUserName = m_aIPCInfo[m_dwIpcInfoIndex].szUser;
			m_csIpcPwd = m_aIPCInfo[m_dwIpcInfoIndex].szPwd;
			m_dwTerminalChannel = m_aIPCInfo[m_dwIpcInfoIndex].dwTermiChannelNo;
			UpdateData(FALSE);
		}
	}

	*pResult = 0;
}


void CDlgTermManage::OnSelchangeComAddrFormatType() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_comPullAddrFormatType.GetCurSel();
	if (nSel == CB_ERR)
	{
		return;
	}
	CString strAddrType;
	m_comPullAddrFormatType.GetLBText(nSel, strAddrType);
	if (0 == strcmp(strAddrType, "ipaddress"))
	{
		GetDlgItem(IDC_EDT_HOST_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_COM_PULL_IP_VERSION)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDT_PULL_IP4_ADDR)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDT_PULL_IP6_ADDR)->EnableWindow(TRUE);
		m_comPullIPVersion.SetCurSel(0);
		OnSelchangeComPullIpVersion();
	}
	else if (0 == strcmp(strAddrType, "hostname"))
	{
		GetDlgItem(IDC_EDT_HOST_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_COM_PULL_IP_VERSION)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_PULL_IP4_ADDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_PULL_IP6_ADDR)->EnableWindow(FALSE);
	}
}

void CDlgTermManage::OnSelchangeComIpcIpVersion() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_comIpcIPVersion.GetCurSel();
	if (nSel == CB_ERR)
	{
		return;
	}
	CString strIPVersion;
	m_comIpcIPVersion.GetLBText(nSel, strIPVersion);
	if (0 == strcmp(strIPVersion, "v4"))
	{
		GetDlgItem(IDC_EDT_IPC_IP4_ADDR)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDT_IPC_IP6_ADDR)->EnableWindow(FALSE);
	}
	else if (0 == strcmp(strIPVersion, "v6"))
	{
		GetDlgItem(IDC_EDT_IPC_IP4_ADDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_IPC_IP6_ADDR)->EnableWindow(TRUE);
	}
	else if (0 == strcmp(strIPVersion, "dual"))
	{
		GetDlgItem(IDC_EDT_IPC_IP4_ADDR)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDT_IPC_IP6_ADDR)->EnableWindow(TRUE);
	}
}

void CDlgTermManage::OnSelchangeComRegType() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_comRegType.GetCurSel();
	if (nSel == CB_ERR)
	{
		return;
	}
	CString strRegType;
	m_comRegType.GetLBText(nSel, strRegType);
	if (0 == strcmp(strRegType, "pull"))
	{
		GetDlgItem(IDC_EDT_COND_CODE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COM_ADDR_FORMAT_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDT_HOST_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_COM_PULL_IP_VERSION)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDT_PULL_IP4_ADDR)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDT_PULL_IP6_ADDR)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDT_PULL_PORT)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDT_PULL_USER_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDT_PULL_PWD)->EnableWindow(TRUE);
		m_comPullAddrFormatType.SetCurSel(0);
		OnSelchangeComAddrFormatType();
	}
	else if (0 == strcmp(strRegType, "push"))
	{
		GetDlgItem(IDC_EDT_COND_CODE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COM_ADDR_FORMAT_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_HOST_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_COM_PULL_IP_VERSION)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_PULL_IP4_ADDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_PULL_IP6_ADDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_PULL_PORT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_PULL_USER_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_PULL_PWD)->EnableWindow(FALSE);
	}
}

void CDlgTermManage::OnSelchangeComboAddrType() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cmbAddrType.GetCurSel();
	if (nSel == CB_ERR)
	{
		return;
	}
	CString strAddrType;
	m_cmbAddrType.GetLBText(nSel, strAddrType);
	if (0 == strcmp(strAddrType, "ipaddress"))
	{
		GetDlgItem(IDC_EDT_IPC_HOST_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_COM_IPC_IP_VERSION)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDT_IPC_IP4_ADDR)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDT_IPC_IP6_ADDR)->EnableWindow(TRUE);
		m_comIpcIPVersion.SetCurSel(0);
		OnSelchangeComIpcIpVersion();
	}
	else if (0 == strcmp(strAddrType, "hostname"))
	{
		GetDlgItem(IDC_EDT_IPC_HOST_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_COM_IPC_IP_VERSION)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_IPC_IP4_ADDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_IPC_IP6_ADDR)->EnableWindow(FALSE);
	}
}

void CDlgTermManage::OnSelchangeComPullIpVersion() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_comPullIPVersion.GetCurSel();
	if (nSel == CB_ERR)
	{
		return;
	}
	CString strIPVersion;
	m_comPullIPVersion.GetLBText(nSel, strIPVersion);
	if (0 == strcmp(strIPVersion, "v4"))
	{
		GetDlgItem(IDC_EDT_PULL_IP4_ADDR)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDT_PULL_IP6_ADDR)->EnableWindow(FALSE);
	}
	else if (0 == strcmp(strIPVersion, "v6"))
	{
		GetDlgItem(IDC_EDT_PULL_IP4_ADDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_PULL_IP6_ADDR)->EnableWindow(TRUE);
	}
	else if (0 == strcmp(strIPVersion, "dual"))
	{
		GetDlgItem(IDC_EDT_PULL_IP4_ADDR)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDT_PULL_IP6_ADDR)->EnableWindow(TRUE);
	}
}

void CDlgTermManage::OnBtnDelIpc() 
{
	// TODO: Add your control notification handler code here
	if (m_dwIpcInfoIndex < 0)
	{
		return;
	}
	
	for (int nCnt = m_dwIpcInfoIndex; nCnt < m_dwIpcInfoCount-1; nCnt++)
	{
		CString str;
		str.Format("%d", nCnt+1);
		m_pListIpc->SetItemText(nCnt, 1, str);
		m_pListIpc->SetItemText(nCnt, 2, m_pListIpc->GetItemText(nCnt+1, 2));
		memcpy(&m_aIPCInfo[nCnt], &m_aIPCInfo[nCnt+1], sizeof(m_aIPCInfo[nCnt+1]));
		m_aIPCInfo[nCnt].dwID = nCnt+1;
	}
	
	memset(&m_aIPCInfo[m_dwIpcInfoCount-1], 0, sizeof(m_aIPCInfo[m_dwIpcInfoCount-1]));
	m_pListIpc->DeleteItem(m_dwIpcInfoCount-1);
	m_dwIpcInfoIndex = -1;
	
	m_dwIpcInfoCount--;

	m_cmbAddrType.SetCurSel(0);
	OnSelchangeComboAddrType();
}

void CDlgTermManage::OnBtnModIpc() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (m_dwIpcInfoIndex < 0)
	{
		return;
	}
	
	IPC_INFO stIpcInfo = {0};
	
	stIpcInfo.dwID = m_dwIpcID;
	CSTRING_TO_CHARS(m_csIpcType, stIpcInfo.szIpcType);
	CSTRING_TO_CHARS(m_csIpcAddrFormatType, stIpcInfo.szAddrFormatType);
	CSTRING_TO_CHARS(m_csIpcHostName, stIpcInfo.szHostName);
	CSTRING_TO_CHARS(m_csIpcIPVersion, stIpcInfo.szIPVersion);
	CSTRING_TO_CHARS(m_csIpcIPv4, stIpcInfo.szIPv4);
	CSTRING_TO_CHARS(m_csIpcIPv6, stIpcInfo.szIPv6);
	stIpcInfo.dwPort = m_dwIpcPort;
	CSTRING_TO_CHARS(m_csIpcUserName, stIpcInfo.szUser);
	CSTRING_TO_CHARS(m_csIpcPwd, stIpcInfo.szPwd);
	stIpcInfo.dwTermiChannelNo = m_dwTerminalChannel;
	
	m_aIPCInfo[m_dwIpcInfoIndex] = stIpcInfo;
	
	CString strInfo;
	strInfo.Format("%d", m_dwIpcID);
    m_pListIpc->SetItemText(m_dwIpcInfoIndex, 1, strInfo);
    m_pListIpc->SetItemText(m_dwIpcInfoIndex, 2, m_csIpcType);
	
	UpdateData(FALSE);
}

void CDlgTermManage::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	delete[] m_paTermInfo;
	m_paTermInfo = NULL;
	delete[] m_pXMLResultBuf;
	m_pXMLResultBuf = NULL;
}


void CDlgTermManage::OnBnClickedBtnBatchDel()
{
    // TODO:  在此添加控件通知处理程序代码
    POSITION pos = m_listTermianl.GetFirstSelectedItemPosition();
    if (pos == NULL)
    {
        return;
    }
    else
    {
        m_nCountId = 0;
        memset(m_nArrayId, 0, MAX_ID);
        int arry[MAX_ID] = { 0 };
        while (pos)
        {
            int nItem = m_listTermianl.GetNextSelectedItem(pos);
            CString strid = m_listTermianl.GetItemText(nItem, 1);
            int intId = atoi(strid);
            m_nArrayId[m_nCountId] = intId;
            m_nCountId++;
            arry[m_nCountId] = nItem;
            //m_listProgram.DeleteItem(nItem);
        }
    }
    char* pInputBuff = NULL;
    DWORD dwInputSize = 0;
    if (!ConvertTerminalIdToXml(m_nArrayId, m_nCountId, &pInputBuff, dwInputSize))
    {
        if (pInputBuff != NULL)
        {
            delete[] pInputBuff;
            pInputBuff = NULL;
        }
        return;
    }
    CString strCommand;
    strCommand.Format("DELETE /ISAPI/Publish/TerminalMgr/terminals\r\n");
    NET_DVR_XML_CONFIG_INPUT struInputParam = { 0 };
    struInputParam.dwSize = sizeof(struInputParam);
    struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
    struInputParam.dwRequestUrlLen = strCommand.GetLength();
    struInputParam.lpInBuffer = pInputBuff;
    struInputParam.dwInBufferSize = dwInputSize;

    char szStatusBuff[1024] = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT struOutputParam = { 0 };
    struOutputParam.dwSize = sizeof(struOutputParam);
    struOutputParam.lpStatusBuffer = szStatusBuff;
    struOutputParam.dwStatusSize = sizeof(szStatusBuff);

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
        if (pInputBuff != NULL)
        {
            delete[] pInputBuff;
            pInputBuff = NULL;
        }
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");


    if (pInputBuff != NULL)
    {
        delete[] pInputBuff;
        pInputBuff = NULL;
    }
}
