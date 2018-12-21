// DlgInfoDiffusionContainer.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInfoDiffusionContainer.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionContainer dialog


CDlgInfoDiffusionContainer::CDlgInfoDiffusionContainer(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInfoDiffusionContainer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInfoDiffusionContainer)
	m_dwContainerID = 0;
	m_szContainerName = _T("");
	m_dwPlayDuration = 0;
	m_dwSwitchTime = 0;
	//}}AFX_DATA_INIT
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	m_lpContainerList = new NET_DVR_CONTAINER_LIST;
	memset(m_lpContainerList, 0, sizeof(*m_lpContainerList));
	m_lpContainerList->dwSize = sizeof(*m_lpContainerList);
	m_pOutputXmlBuffer = new char[MAX_LEN_XML];
	memset(m_pOutputXmlBuffer, 0, sizeof(char)*MAX_LEN_XML);
	m_nCurSelContainer = -1;
}


void CDlgInfoDiffusionContainer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInfoDiffusionContainer)
	DDX_Control(pDX, IDC_LIST_CONTAINER, m_listContainer);
	DDX_Control(pDX, IDC_COMBO_SWITCH_EFFECT, m_cmbSwitchEffect);
	DDX_Text(pDX, IDC_EDIT_CONTAINER_ID, m_dwContainerID);
	DDX_Text(pDX, IDC_EDIT_CONTAINER_NAME, m_szContainerName);
	DDX_Text(pDX, IDC_EDIT_PLAY_DURATION, m_dwPlayDuration);
	DDX_Text(pDX, IDC_EDIT_SWITCH_TIME, m_dwSwitchTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInfoDiffusionContainer, CDialog)
	//{{AFX_MSG_MAP(CDlgInfoDiffusionContainer)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_NEW, OnBtnNew)
	ON_BN_CLICKED(IDC_BTN_GETALL, OnBtnGetall)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CONTAINER, OnClickListContainer)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionContainer message handlers

void CDlgInfoDiffusionContainer::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	if (m_nCurSelContainer < 0)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "请选择垫片", "Please choose a container first.");
		g_StringLanType(szLan2, "垫片管理", "Container Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	
	//更新垫片配置
	LPNET_DVR_CONTAINER lpContainer = &m_lpContainerList->struContainerList[m_nCurSelContainer];
	lpContainer->dwContainerID = m_dwContainerID;
	memcpy(lpContainer->szContainerName, m_szContainerName, sizeof(m_szContainerName));
	lpContainer->dwPlayDuration = m_dwPlayDuration;
	lpContainer->dwSwitchTime = m_dwSwitchTime;
	int nSel = m_cmbSwitchEffect.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "垫片管理", "Container Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbSwitchEffect.GetLBText(nSel, lpContainer->szSwitchEffect);
	RefreshContainerItem(m_nCurSelContainer); //刷新配置到列表中
	
	//调用接口设置垫片
	char* pInputBuff = NULL;
	DWORD dwInputSize = 0;
	ConvertContainerParamsStruToXml(lpContainer, &pInputBuff, dwInputSize);

	CString strCommand;
	strCommand.Format("PUT /ISAPI/Publish/ProgramMgr/container/%d\r\n", lpContainer->dwContainerID);
	NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
	struInputParam.dwSize = sizeof(struInputParam);
	struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
	struInputParam.dwRequestUrlLen = strCommand.GetLength();
	struInputParam.lpInBuffer = pInputBuff;
	struInputParam.dwInBufferSize = dwInputSize;
	
	char szStatusBuff[1024] = {0};
	NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
	struOutputParam.dwSize = sizeof(struOutputParam);
	struOutputParam.lpStatusBuffer = szStatusBuff;
	struOutputParam.dwStatusSize = sizeof(szStatusBuff);
	
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		delete[] pInputBuff;
		pInputBuff = NULL;
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");

	delete[] pInputBuff;
	pInputBuff = NULL;

	UpdateData(FALSE);
}

void CDlgInfoDiffusionContainer::OnBtnNew() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	//新建垫片配置
	int nContainerIndex = 0;
	int nContainerCnt = 0;
	for (nContainerCnt = 0; nContainerCnt < MAX_NUM_CONTAINER; nContainerCnt++)
	{
		if (0 == m_lpContainerList->struContainerList[nContainerCnt].dwContainerID)
		{
			nContainerIndex = nContainerCnt;
			break;;
		}
	}
	LPNET_DVR_CONTAINER lpContainer = &m_lpContainerList->struContainerList[nContainerCnt];
	memset(lpContainer, 0, sizeof(*lpContainer));
	lpContainer->dwSize = sizeof(*lpContainer);
	lpContainer->dwContainerID = m_dwContainerID;
	memcpy(lpContainer->szContainerName, m_szContainerName, sizeof(m_szContainerName));
	lpContainer->dwPlayDuration = m_dwPlayDuration;
	lpContainer->dwSwitchTime = m_dwSwitchTime;
	int nSel = m_cmbSwitchEffect.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "垫片管理", "Container Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbSwitchEffect.GetLBText(nSel, lpContainer->szSwitchEffect);
	
	//调用新建接口添加垫片
	char* pInputBuff = NULL;
	DWORD dwInputSize = 0;
	ConvertContainerParamsStruToXml(lpContainer, &pInputBuff, dwInputSize);

	CString strCommand;
	strCommand.Format("POST /ISAPI/Publish/ProgramMgr/container\r\n");
	NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
	struInputParam.dwSize = sizeof(struInputParam);
	struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
	struInputParam.dwRequestUrlLen = strCommand.GetLength();
	struInputParam.lpInBuffer = pInputBuff;
	struInputParam.dwInBufferSize = dwInputSize;
	
	char szStatusBuff[1024] = {0};
	NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
	struOutputParam.dwSize = sizeof(struOutputParam);
	struOutputParam.lpStatusBuffer = szStatusBuff;
	struOutputParam.dwStatusSize = sizeof(szStatusBuff);
	
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		delete[] pInputBuff;
		pInputBuff = NULL;
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
	
	//获取设备返回的垫片编号
	m_dwContainerID = GetResponseStatusID(szStatusBuff);
	lpContainer->dwContainerID = m_dwContainerID;
	CString str;
	str.Format("%d", nContainerIndex+1);
	m_listContainer.InsertItem(nContainerIndex, str);
	m_listContainer.SetItemState(m_nCurSelContainer, 0, -1);
	m_listContainer.SetItemState(nContainerIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_listContainer.SetFocus();
	m_nCurSelContainer = nContainerIndex;
	RefreshContainerItem(nContainerIndex);

	delete[] pInputBuff;
	pInputBuff = NULL;
	
	UpdateData(FALSE);
}

void CDlgInfoDiffusionContainer::OnBtnGetall() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString strCommand;
	strCommand.Format("GET /ISAPI/Publish/ProgramMgr/container\r\n");
	NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
	struInputParam.dwSize = sizeof(struInputParam);
	struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
	struInputParam.dwRequestUrlLen = strCommand.GetLength();
	
	char szStatusBuff[1024] = {0};
	NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
	struOutputParam.dwSize = sizeof(struOutputParam);
	memset(m_pOutputXmlBuffer, 0, MAX_LEN_XML);
	struOutputParam.lpOutBuffer = m_pOutputXmlBuffer;
	struOutputParam.dwOutBufferSize = MAX_LEN_XML;
	struOutputParam.lpStatusBuffer = szStatusBuff;
	struOutputParam.dwStatusSize = sizeof(szStatusBuff);
	
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
	
	memset(m_lpContainerList, 0, sizeof(*m_lpContainerList));
	m_lpContainerList->dwSize = sizeof(*m_lpContainerList);
	ConvertContainerParamsXmlToStruList(m_pOutputXmlBuffer, m_lpContainerList);
	
	RefreshContainerList();

	UpdateData(FALSE);
}

void CDlgInfoDiffusionContainer::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (m_nCurSelContainer < 0)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "请选择垫片", "Please choose a container first.");
		g_StringLanType(szLan2, "垫片管理", "Container Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	
	CString strCommand;
	strCommand.Format("GET /ISAPI/Publish/ProgramMgr/container/%d\r\n", 
		m_lpContainerList->struContainerList[m_nCurSelContainer].dwContainerID);
	NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
	struInputParam.dwSize = sizeof(struInputParam);
	struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
	struInputParam.dwRequestUrlLen = strCommand.GetLength();
	
	char szStatusBuff[1024] = {0};
	NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
	struOutputParam.dwSize = sizeof(struOutputParam);
	memset(m_pOutputXmlBuffer, 0, MAX_LEN_XML);
	struOutputParam.lpOutBuffer = m_pOutputXmlBuffer;
	struOutputParam.dwOutBufferSize = MAX_LEN_XML;
	struOutputParam.lpStatusBuffer = szStatusBuff;
	struOutputParam.dwStatusSize = sizeof(szStatusBuff);
	
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
	
	LPNET_DVR_CONTAINER lpContainer = &m_lpContainerList->struContainerList[m_nCurSelContainer];
	memset(lpContainer, 0, sizeof(*lpContainer));
	lpContainer->dwSize = sizeof(*lpContainer);
	ConvertContainerParamsXmlToStru(m_pOutputXmlBuffer, lpContainer);
	
	RefreshContainerItem(m_nCurSelContainer);

	UpdateContainerInfo(m_nCurSelContainer);

	UpdateData(FALSE);
}

void CDlgInfoDiffusionContainer::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

BOOL CDlgInfoDiffusionContainer::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitContainerCtrlList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgInfoDiffusionContainer::InitContainerCtrlList()
{
	DWORD dwExStyle = m_listContainer.GetExtendedStyle();
	dwExStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
	m_listContainer.SetExtendedStyle(dwExStyle);
	
	char szLan[512] = {0};
	g_StringLanType(szLan, "序号", "Index");
	m_listContainer.InsertColumn(0, szLan);
	m_listContainer.SetColumnWidth(0, 40);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "垫片名称", "Container Name");
	m_listContainer.InsertColumn(1, szLan);
	m_listContainer.SetColumnWidth(1, 80);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "播放时间", "Play Duration");
	m_listContainer.InsertColumn(2, szLan);
	m_listContainer.SetColumnWidth(2, 80);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "切换时间", "Switch Time");
	m_listContainer.InsertColumn(3, szLan);
	m_listContainer.SetColumnWidth(3, 80);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "切换效果", "Switch Effect");
	m_listContainer.InsertColumn(4, szLan);
	m_listContainer.SetColumnWidth(4, 80);
}

void CDlgInfoDiffusionContainer::RefreshContainerItem(int nContainer)
{
	if (nContainer < 0 || nContainer >= MAX_NUM_CONTAINER)
	{
		return;
	}
	LPNET_DVR_CONTAINER lpContainer = &m_lpContainerList->struContainerList[nContainer];
	m_listContainer.SetItemText(nContainer, 1, lpContainer->szContainerName);
	CString str;
	str.Format("%d", lpContainer->dwPlayDuration);
	m_listContainer.SetItemText(nContainer, 2, str);
	str.Format("%d", lpContainer->dwSwitchTime);
	m_listContainer.SetItemText(nContainer, 3, str);
	m_listContainer.SetItemText(nContainer, 4, lpContainer->szSwitchEffect);
}

void CDlgInfoDiffusionContainer::RefreshContainerList()
{
	m_listContainer.DeleteAllItems();
	for (int nContainerCnt = 0; nContainerCnt < MAX_NUM_CONTAINER; nContainerCnt++)
	{
		if (0 == m_lpContainerList->struContainerList[nContainerCnt].dwContainerID)
		{
			break;
		}
		RefreshContainerItem(nContainerCnt);
	}
}

void CDlgInfoDiffusionContainer::UpdateContainerInfo(int nContainer)
{
	if (nContainer < 0 || nContainer >= MAX_NUM_CONTAINER)
	{
		return;
	}
	m_dwContainerID = m_lpContainerList->struContainerList[nContainer].dwContainerID;
	m_szContainerName = m_lpContainerList->struContainerList[nContainer].szContainerName;
	m_dwPlayDuration = m_lpContainerList->struContainerList[nContainer].dwPlayDuration;
	m_dwSwitchTime = m_lpContainerList->struContainerList[nContainer].dwSwitchTime;
	m_cmbSwitchEffect.SetCurSel(m_cmbSwitchEffect.FindString(-1, m_lpContainerList->struContainerList[nContainer].szSwitchEffect));
	UpdateData(FALSE);
}

void CDlgInfoDiffusionContainer::OnClickListContainer(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listContainer.GetFirstSelectedItemPosition();
	if (pos)
	{
		m_nCurSelContainer = m_listContainer.GetNextSelectedItem(pos);
		UpdateContainerInfo(m_nCurSelContainer);
	}
	
	*pResult = 0;
}

void CDlgInfoDiffusionContainer::OnBtnDel() 
{
	// TODO: Add your control notification handler code here
	if (m_nCurSelContainer < 0)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "请选择垫片", "Please choose a container first.");
		g_StringLanType(szLan2, "垫片管理", "Container Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	
	CString strCommand;
	strCommand.Format("DELETE /ISAPI/Publish/ProgramMgr/container/%d\r\n", 
		m_lpContainerList->struContainerList[m_nCurSelContainer].dwContainerID);
	NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
	struInputParam.dwSize = sizeof(struInputParam);
	struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
	struInputParam.dwRequestUrlLen = strCommand.GetLength();
	
	char szStatusBuff[1024] = {0};
	NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
	struOutputParam.dwSize = sizeof(struOutputParam);
	struOutputParam.lpStatusBuffer = szStatusBuff;
	struOutputParam.dwStatusSize = sizeof(szStatusBuff);
	
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
	
	for (int nContainerCnt = m_nCurSelContainer; nContainerCnt < m_listContainer.GetItemCount()-1; nContainerCnt++)
	{
		m_listContainer.SetItemText(nContainerCnt, 1, m_listContainer.GetItemText(nContainerCnt+1, 1));
		m_listContainer.SetItemText(nContainerCnt, 2, m_listContainer.GetItemText(nContainerCnt+1, 2));
		m_listContainer.SetItemText(nContainerCnt, 3, m_listContainer.GetItemText(nContainerCnt+1, 3));
		m_listContainer.SetItemText(nContainerCnt, 4, m_listContainer.GetItemText(nContainerCnt+1, 4));
		memcpy(&m_lpContainerList->struContainerList[nContainerCnt], &m_lpContainerList->struContainerList[nContainerCnt+1], sizeof(NET_DVR_CONTAINER));
	}
	memset(&m_lpContainerList->struContainerList[m_listContainer.GetItemCount()-1], 0, sizeof(NET_DVR_CONTAINER));
	m_listContainer.DeleteItem(m_listContainer.GetItemCount()-1);
	m_nCurSelContainer = -1;

	UpdateData(FALSE);
}

void CDlgInfoDiffusionContainer::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	delete m_lpContainerList;
	m_lpContainerList = NULL;
	delete[] m_pOutputXmlBuffer;
	m_pOutputXmlBuffer = NULL;
}
