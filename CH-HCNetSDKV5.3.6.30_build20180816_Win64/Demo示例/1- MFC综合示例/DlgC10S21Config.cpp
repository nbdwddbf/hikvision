// DlgC10S21Config.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgC10S21Config.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgC10S21Config dialog


CDlgC10S21Config::CDlgC10S21Config(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgC10S21Config::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgC10S21Config)
	m_dwInputNo = 0;
	m_sIPAddress = _T("");
	m_sPassword = _T("");
	m_dwPort = 0;
	m_dwServerNo = 0;
	m_sUserName = _T("");
	m_dwVideoWallNo = 0;
	//}}AFX_DATA_INIT
	m_iDevIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDevIndex].lLoginID;
	memset(&m_struLoginCfg, 0, sizeof(m_struLoginCfg));
	m_struLoginCfg.dwSize = sizeof(m_struLoginCfg);
	memset(&m_struLoginCfgList, 0, sizeof(m_struLoginCfgList));
	m_struLoginCfgList.dwSize = sizeof(m_struLoginCfgList);
	m_nCurItem = -1;
	m_pXmlOutput = new char[ISAPI_DATA_LEN];
	memset(m_pXmlOutput, 0, ISAPI_DATA_LEN);
}


void CDlgC10S21Config::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgC10S21Config)
	DDX_Control(pDX, IDC_LIST_LOGIN_CFG, m_listLoginCfg);
	DDX_Text(pDX, IDC_EDIT_INPUT_NO, m_dwInputNo);
	DDX_Text(pDX, IDC_EDIT_IP_ADDRESS, m_sIPAddress);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_sPassword);
	DDX_Text(pDX, IDC_EDIT_PORT, m_dwPort);
	DDX_Text(pDX, IDC_EDIT_SERVER_NO, m_dwServerNo);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_sUserName);
	DDX_Text(pDX, IDC_EDIT_VIDEOWALL_NO, m_dwVideoWallNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgC10S21Config, CDialog)
	//{{AFX_MSG_MAP(CDlgC10S21Config)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_GET_ALL, OnBtnGetAll)
	ON_BN_CLICKED(IDC_BTN_ONEKEY_RESET, OnBtnOnekeyReset)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_CLICK, IDC_LIST_LOGIN_CFG, OnClickListLoginCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgC10S21Config message handlers

void CDlgC10S21Config::OnBtnAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	memset(&m_struLoginCfg, 0, sizeof(m_struLoginCfg));
	m_struLoginCfg.dwSize = sizeof(m_struLoginCfg);
	strcpy(m_struLoginCfg.struIPAddr.sIpV4, m_sIPAddress);
	strcpy((char*)m_struLoginCfg.sUserName, m_sUserName);
	strcpy((char*)m_struLoginCfg.sPassword, m_sPassword);
	m_struLoginCfg.dwPortNo = m_dwPort;
	m_struLoginCfg.dwInputNo = m_dwInputNo;
	
	char* pXmlInput = NULL;
	DWORD dwInSize = 0;
	if (!ConvertScreenServerLoginParamStruToXml(&m_struLoginCfg, &pXmlInput, dwInSize))
	{
		return;
	}
	char sCommand[256] = {0};
	sprintf(sCommand, "POST /ISAPI/DisplayDev/Auxiliary/ScreenServer/loginCfg\r\n");
	NET_DVR_XML_CONFIG_INPUT struInput = {0};
    struInput.dwSize = sizeof(struInput);
	struInput.lpRequestUrl = sCommand;
    struInput.dwRequestUrlLen = strlen(sCommand);
	struInput.lpInBuffer = pXmlInput;
	struInput.dwInBufferSize = dwInSize;
	NET_DVR_XML_CONFIG_OUTPUT struOutput = {0};
    struOutput.dwSize = sizeof(struOutput);
	char sStatusBuf[1024] = {0};
	struOutput.lpStatusBuffer = sStatusBuf;
	struOutput.dwStatusSize = sizeof(sStatusBuf);
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOutput))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
	}
	
	m_dwServerNo = GetIDFromResponseStatus(m_pXmlOutput);
	m_struLoginCfg.dwServerNo = m_dwServerNo;
	DWORD dwIndex = m_listLoginCfg.GetItemCount();
	memcpy(&m_struLoginCfgList.struList[dwIndex], &m_struLoginCfg, sizeof(m_struLoginCfg));
	CString str;
	str.Format("%d", dwIndex+1);
	m_listLoginCfg.InsertItem(dwIndex, str);
	m_listLoginCfg.SetItemState(m_nCurItem, 0, -1);
	m_listLoginCfg.SetItemState(dwIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_listLoginCfg.SetFocus();
	m_nCurItem = dwIndex;
	RefreshListItem(dwIndex);
	
	UpdateData(FALSE);
}

void CDlgC10S21Config::OnBtnDel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	if (m_nCurItem < 0)
	{
		return;
	}
	
	char sCommand[256] = {0};
	sprintf(sCommand, "DELETE /ISAPI/DisplayDev/Auxiliary/ScreenServer/%d/loginCfg\r\n", m_dwServerNo);
	NET_DVR_XML_CONFIG_INPUT struInput = {0};
    struInput.dwSize = sizeof(struInput);
	struInput.lpRequestUrl = sCommand;
    struInput.dwRequestUrlLen = strlen(sCommand);
	NET_DVR_XML_CONFIG_OUTPUT struOutput = {0};
    struOutput.dwSize = sizeof(struOutput);
	char sStatusBuf[1024] = {0};
	struOutput.lpStatusBuffer = sStatusBuf;
	struOutput.dwStatusSize = sizeof(sStatusBuf);
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOutput))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
	}
	
	for (int nCnt = m_nCurItem; nCnt < m_listLoginCfg.GetItemCount()-1; nCnt++)
	{
		m_listLoginCfg.SetItemText(nCnt, 1, m_listLoginCfg.GetItemText(nCnt+1, 1));
		m_listLoginCfg.SetItemText(nCnt, 2, m_listLoginCfg.GetItemText(nCnt+1, 2));
		m_listLoginCfg.SetItemText(nCnt, 3, m_listLoginCfg.GetItemText(nCnt+1, 3));
		m_listLoginCfg.SetItemText(nCnt, 4, m_listLoginCfg.GetItemText(nCnt+1, 4));
		m_listLoginCfg.SetItemText(nCnt, 5, m_listLoginCfg.GetItemText(nCnt+1, 5));
		m_listLoginCfg.SetItemText(nCnt, 6, m_listLoginCfg.GetItemText(nCnt+1, 6));
		memcpy(&m_struLoginCfgList.struList[nCnt], &m_struLoginCfgList.struList[nCnt+1], sizeof(NET_DVR_SCREEN_SERVER_LOGIN_CFG));
	}
	memset(&m_struLoginCfgList.struList[m_listLoginCfg.GetItemCount()-1], 0, sizeof(NET_DVR_SCREEN_SERVER_LOGIN_CFG));
	m_listLoginCfg.DeleteItem(m_listLoginCfg.GetItemCount()-1);
	m_listLoginCfg.SetItemState(m_listLoginCfg.GetItemCount()-1, 0, -1);
	m_nCurItem = -1;
}

void CDlgC10S21Config::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CDlgC10S21Config::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	if (m_nCurItem < 0)
	{
		return;
	}
	
	memset(&m_struLoginCfg, 0, sizeof(m_struLoginCfg));
	m_struLoginCfg.dwSize = sizeof(m_struLoginCfg);
	NET_DVR_XML_CONFIG_INPUT struInput = {0};
    struInput.dwSize = sizeof(struInput);
	char sCommand[256] = {0};
	sprintf(sCommand, "GET /ISAPI/DisplayDev/Auxiliary/ScreenServer/%d/loginCfg\r\n", m_dwServerNo);
	struInput.lpRequestUrl = sCommand;
    struInput.dwRequestUrlLen = strlen(sCommand);
	NET_DVR_XML_CONFIG_OUTPUT struOutput = {0};
    struOutput.dwSize = sizeof(struOutput);
	struOutput.lpOutBuffer = m_pXmlOutput;
	struOutput.dwOutBufferSize = ISAPI_DATA_LEN;
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOutput))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
	}
	if (!ConvertScreenServerLoginParamXmlToStru(m_pXmlOutput, &m_struLoginCfg))
	{
		return;
	}

	memcpy(&m_struLoginCfgList.struList[m_nCurItem], &m_struLoginCfg, sizeof(m_struLoginCfg));
	RefreshListItem(m_nCurItem);
	UpdateLoginCfgToDlg(m_nCurItem);
}

void CDlgC10S21Config::OnBtnGetAll() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	memset(&m_struLoginCfgList, 0, sizeof(m_struLoginCfgList));
	m_struLoginCfgList.dwSize = sizeof(m_struLoginCfgList);
	NET_DVR_XML_CONFIG_INPUT struInput = {0};
    struInput.dwSize = sizeof(struInput);
	char sCommand[256] = {0};
	sprintf(sCommand, "GET /ISAPI/DisplayDev/Auxiliary/ScreenServer/loginCfg\r\n");
	struInput.lpRequestUrl = sCommand;
    struInput.dwRequestUrlLen = strlen(sCommand);
	NET_DVR_XML_CONFIG_OUTPUT struOutput = {0};
    struOutput.dwSize = sizeof(struOutput);
	struOutput.lpOutBuffer = m_pXmlOutput;
	struOutput.dwOutBufferSize = ISAPI_DATA_LEN;
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOutput))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
	}
	if (!ConvertScreenServerLoginParamXmlToStruList(m_pXmlOutput, &m_struLoginCfgList))
	{
		return;
	}
	
	RefreshList();
}

void CDlgC10S21Config::OnBtnOnekeyReset() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwWallNo = m_dwVideoWallNo<<24;
	if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_RESET_VIDEOWALLDISPLAYPOSITION, &dwWallNo, sizeof(dwWallNo)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_RESET_VIDEOWALLDISPLAYPOSITION");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_RESET_VIDEOWALLDISPLAYPOSITION");
	}
}

void CDlgC10S21Config::InitListCtrl()
{
	DWORD dwStyle = m_listLoginCfg.GetExtendedStyle();
	dwStyle |= LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT;
	m_listLoginCfg.SetExtendedStyle(dwStyle);
	char sColumName[32] = {0};
	g_StringLanType(sColumName, "索引", "Index");
	m_listLoginCfg.InsertColumn(0, sColumName, LVCFMT_LEFT, 40, -1);
	
	g_StringLanType(sColumName, "服务器编号", "Server No.");
	m_listLoginCfg.InsertColumn(1, sColumName, LVCFMT_LEFT, 80, -1);
	
	g_StringLanType(sColumName, "IP地址", "IP Address");
	m_listLoginCfg.InsertColumn(2, sColumName, LVCFMT_LEFT, 80, -1);
	
	g_StringLanType(sColumName, "端口号", "Port");
	m_listLoginCfg.InsertColumn(3, sColumName, LVCFMT_LEFT, 80, -1);
	
	g_StringLanType(sColumName, "用户名", "Username");
	m_listLoginCfg.InsertColumn(4, sColumName, LVCFMT_LEFT, 80, -1);
	
	g_StringLanType(sColumName, "密码", "Password");
	m_listLoginCfg.InsertColumn(5, sColumName, LVCFMT_LEFT, 80, -1);
	
	g_StringLanType(sColumName, "输入口编号", "Input No.");
	m_listLoginCfg.InsertColumn(6, sColumName, LVCFMT_LEFT, 80, -1);
}

void CDlgC10S21Config::RefreshList()
{
	m_listLoginCfg.DeleteAllItems();
	for (int nCnt = 0; nCnt < MAX_NUM_SCREEN_SERVER; nCnt++)
	{
		if (0 == m_struLoginCfgList.struList[nCnt].dwServerNo)
		{
			break;
		}
		CString str;
		str.Format("%d", nCnt+1);
		m_listLoginCfg.InsertItem(nCnt, str);
		RefreshListItem(nCnt);
	}
}

void CDlgC10S21Config::RefreshListItem(int nItemIndex)
{
	if (nItemIndex < 0 || nItemIndex >= MAX_NUM_SCREEN_SERVER)
	{
		return;
	}
	CString str;
	str.Format("%d", m_struLoginCfgList.struList[nItemIndex].dwServerNo);
	m_listLoginCfg.SetItemText(nItemIndex, 1, str);
	m_listLoginCfg.SetItemText(nItemIndex, 2, m_struLoginCfgList.struList[nItemIndex].struIPAddr.sIpV4);
	str.Format("%d", m_struLoginCfgList.struList[nItemIndex].dwPortNo);
	m_listLoginCfg.SetItemText(nItemIndex, 3, str);
	m_listLoginCfg.SetItemText(nItemIndex, 4, m_struLoginCfgList.struList[nItemIndex].sUserName);
	m_listLoginCfg.SetItemText(nItemIndex, 5, m_struLoginCfgList.struList[nItemIndex].sPassword);
	str.Format("%d", m_struLoginCfgList.struList[nItemIndex].dwInputNo);
	m_listLoginCfg.SetItemText(nItemIndex, 6, str);
}

void CDlgC10S21Config::UpdateLoginCfgToDlg(int nItemIndex)
{   
	UpdateData(TRUE);

	if (nItemIndex < 0 || nItemIndex >= MAX_NUM_SCREEN_SERVER)
	{
		return;
	}
	m_dwServerNo = m_struLoginCfgList.struList[nItemIndex].dwServerNo;
	m_sIPAddress = m_struLoginCfgList.struList[nItemIndex].struIPAddr.sIpV4;
	m_dwPort = m_struLoginCfgList.struList[nItemIndex].dwPortNo;
	m_sUserName = m_struLoginCfgList.struList[nItemIndex].sUserName;
	m_sPassword = m_struLoginCfgList.struList[nItemIndex].sPassword;
	m_dwInputNo = m_struLoginCfgList.struList[nItemIndex].dwInputNo;

	UpdateData(FALSE);
}

BOOL CDlgC10S21Config::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitListCtrl();
	OnBtnGetAll();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgC10S21Config::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	if (m_nCurItem < 0)
	{
		return;
	}
	
	memset(&m_struLoginCfg, 0, sizeof(m_struLoginCfg));
	m_struLoginCfg.dwSize = sizeof(m_struLoginCfg);
	m_struLoginCfg.dwServerNo = m_dwServerNo;
	strcpy(m_struLoginCfg.struIPAddr.sIpV4, m_sIPAddress);
	strcpy((char*)m_struLoginCfg.sUserName, m_sUserName);
	strcpy((char*)m_struLoginCfg.sPassword, m_sPassword);
	m_struLoginCfg.dwPortNo = m_dwPort;
	m_struLoginCfg.dwInputNo = m_dwInputNo;
	
	char* pXmlInput = NULL;
	DWORD dwInSize = 0;
	if (!ConvertScreenServerLoginParamStruToXml(&m_struLoginCfg, &pXmlInput, dwInSize))
	{
		return;
	}
	char sCommand[256] = {0};
	sprintf(sCommand, "PUT /ISAPI/DisplayDev/Auxiliary/ScreenServer/%d/loginCfg\r\n", m_dwServerNo);
	NET_DVR_XML_CONFIG_INPUT struInput = {0};
    struInput.dwSize = sizeof(struInput);
	struInput.lpRequestUrl = sCommand;
    struInput.dwRequestUrlLen = strlen(sCommand);
	struInput.lpInBuffer = pXmlInput;
	struInput.dwInBufferSize = dwInSize;
	NET_DVR_XML_CONFIG_OUTPUT struOutput = {0};
    struOutput.dwSize = sizeof(struOutput);
	char sStatusBuf[1024] = {0};
	struOutput.lpStatusBuffer = sStatusBuf;
	struOutput.dwStatusSize = sizeof(sStatusBuf);
	
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOutput))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
	}
	
	memcpy(&m_struLoginCfgList.struList[m_nCurItem], &m_struLoginCfg, sizeof(m_struLoginCfg));
	RefreshListItem(m_nCurItem);
}

void CDlgC10S21Config::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if (m_pXmlOutput)
	{
		delete[] m_pXmlOutput;
		m_pXmlOutput = NULL;
	}
}

void CDlgC10S21Config::OnClickListLoginCfg(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listLoginCfg.GetFirstSelectedItemPosition();
	if (pos)
	{
		m_nCurItem = m_listLoginCfg.GetNextSelectedItem(pos);
		memcpy(&m_struLoginCfg, &m_struLoginCfgList.struList[m_nCurItem], sizeof(m_struLoginCfg));
		UpdateLoginCfgToDlg(m_nCurItem);
	}
	
	*pResult = 0;
}
