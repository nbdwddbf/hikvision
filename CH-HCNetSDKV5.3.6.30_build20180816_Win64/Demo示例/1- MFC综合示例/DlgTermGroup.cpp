// DlgTermGroup.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgTermGroup.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTermGroup dialog


CDlgTermGroup::CDlgTermGroup(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTermGroup::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTermGroup)
	m_dwGroupID = 0;
	m_dwTerminalID = 0;
	m_szGroupName = _T("");
	//}}AFX_DATA_INIT
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	m_lpGroup = new NET_DVR_TERMINAL_GROUP;
	memset(m_lpGroup, 0, sizeof(*m_lpGroup));
	m_lpGroup->dwSize = sizeof(*m_lpGroup);
	m_lpGroupList = new NET_DVR_TERMINAL_GROUP_LIST;
	memset(m_lpGroupList, 0, sizeof(*m_lpGroupList));
	m_lpGroupList->dwSize = sizeof(*m_lpGroupList);
	m_pOutputXmlBuffer = new char[MAX_LEN_XML];
	memset(m_pOutputXmlBuffer, 0, sizeof(char)*MAX_LEN_XML);
	m_nCurSelGroup = -1;
	m_nCurSelTerminal = -1;
}


void CDlgTermGroup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTermGroup)
	DDX_Control(pDX, IDC_LIST_TERMINAL, m_listTerminal);
	DDX_Control(pDX, IDC_LIST_GROUP, m_listGroup);
	DDX_Text(pDX, IDC_EDIT_GROUP_ID, m_dwGroupID);
	DDX_Text(pDX, IDC_EDIT_TERMINAL_ID, m_dwTerminalID);
	DDX_Text(pDX, IDC_EDIT_GROUP_NAME, m_szGroupName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTermGroup, CDialog)
	//{{AFX_MSG_MAP(CDlgTermGroup)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_BN_CLICKED(IDC_BTN_DEL_GROUP, OnBtnDelGroup)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_GET_ALL, OnBtnGetAll)
	ON_BN_CLICKED(IDC_BTN_MOD, OnBtnMod)
	ON_BN_CLICKED(IDC_BTN_NEW, OnBtnNew)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_CLICK, IDC_LIST_GROUP, OnClickListGroup)
	ON_NOTIFY(NM_CLICK, IDC_LIST_TERMINAL, OnClickListTerminal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTermGroup message handlers

void CDlgTermGroup::OnBtnAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	CString str;
	int nIndex = m_listTerminal.GetItemCount();
	str.Format("%d", nIndex+1);
	m_listTerminal.InsertItem(nIndex, str);
	str.Format("%d", m_dwTerminalID);
	m_listTerminal.SetItemText(nIndex, 1, str);
	m_listTerminal.SetItemState(m_nCurSelTerminal, 0, -1);
	m_listTerminal.SetItemState(nIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_listTerminal.SetFocus();
	m_nCurSelTerminal = nIndex;
	m_lpGroup->dwTerminalList[nIndex] = m_dwTerminalID;
	m_lpGroup->dwTermCount++;
}

void CDlgTermGroup::OnBtnDel() 
{
	// TODO: Add your control notification handler code here
	for (int nTerCnt = m_nCurSelTerminal; nTerCnt < m_listTerminal.GetItemCount()-1; nTerCnt++)
	{
		m_lpGroup->dwTerminalList[nTerCnt] = m_lpGroup->dwTerminalList[nTerCnt+1];
	}
	m_lpGroup->dwTerminalList[m_listTerminal.GetItemCount()-1] = 0;
	m_listTerminal.DeleteItem(m_listTerminal.GetItemCount()-1);
	m_nCurSelTerminal = -1;
	m_lpGroup->dwTermCount--;
}

void CDlgTermGroup::OnBtnDelGroup() 
{
	// TODO: Add your control notification handler code here
	if (m_nCurSelGroup < 0)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "ÇëÑ¡ÔñÖÕ¶Ë×é", "Please choose a terminal group first.");
		g_StringLanType(szLan2, "ÖÕ¶Ë×é¹ÜÀí", "Terminal Group Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	
	CString strCommand;
	strCommand.Format("DELETE /ISAPI/Publish/TerminalMgr/terminalGroups/%d\r\n", m_lpGroup->dwGroupID);
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
	
	m_listGroup.DeleteItem(m_nCurSelGroup);
	memset(&m_lpGroupList->struGroupList[m_nCurSelGroup], 0, sizeof(m_lpGroupList->struGroupList[m_nCurSelGroup]));
	m_nCurSelGroup = -1;
}

void CDlgTermGroup::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CDlgTermGroup::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	if (m_nCurSelGroup < 0)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "ÇëÑ¡ÔñÖÕ¶Ë×é", "Please choose a terminal group first.");
		g_StringLanType(szLan2, "ÖÕ¶Ë×é¹ÜÀí", "Terminal Group Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	
	UpdateData(TRUE);
	
	CString strCommand;
	strCommand.Format("GET /ISAPI/Publish/TerminalMgr/terminalGroups/%d\r\n", m_lpGroup->dwGroupID);
	NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
	struInputParam.dwSize = sizeof(struInputParam);
	struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
	struInputParam.dwRequestUrlLen = strCommand.GetLength();
	
	char szStatusBuff[1024] = {0};
	NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
	struOutputParam.dwSize = sizeof(struOutputParam);
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
	
	memset(m_lpGroup, 0, sizeof(*m_lpGroup));
	m_lpGroup->dwSize = sizeof(*m_lpGroup);
	ConvertTermGrpParamsXmlToStru(m_pOutputXmlBuffer, m_lpGroup);
	UpdateGroupInfo(m_lpGroup);
	m_listGroup.SetItemText(m_nCurSelGroup, 2, m_lpGroup->szGroupName);

	UpdateData(FALSE);
}

void CDlgTermGroup::OnBtnGetAll() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	CString strCommand;
	strCommand.Format("GET /ISAPI/Publish/TerminalMgr/terminalGroups\r\n");
	NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
	struInputParam.dwSize = sizeof(struInputParam);
	struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
	struInputParam.dwRequestUrlLen = strCommand.GetLength();
	
	char szStatusBuff[1024] = {0};
	NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
	struOutputParam.dwSize = sizeof(struOutputParam);
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
	
	memset(m_lpGroupList, 0, sizeof(*m_lpGroupList));
	m_lpGroupList->dwSize = sizeof(*m_lpGroupList);
	ConvertTermGrpParamsXmlToStruList(m_pOutputXmlBuffer, m_lpGroupList);
	RefreshGroupList();
	
	UpdateData(FALSE);
}

void CDlgTermGroup::OnBtnMod() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	CString str;
	str.Format("%d", m_dwTerminalID);
	m_listTerminal.SetItemText(m_nCurSelTerminal, 1, str);
	m_lpGroup->dwTerminalList[m_nCurSelTerminal] = m_dwTerminalID;
}

void CDlgTermGroup::OnBtnNew() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	strcpy(m_lpGroup->szGroupName, m_szGroupName);
	m_lpGroup->dwSize = sizeof(*m_lpGroup);
	char* pInputBuff = NULL;
	DWORD dwInputSize = 0;
	ConvertTermGrpParamsStruToXml(m_lpGroup, &pInputBuff, dwInputSize);
	
	CString strCommand;
	strCommand.Format("POST /ISAPI/Publish/TerminalMgr/terminalGroups\r\n");
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
	
	m_dwGroupID = GetResponseStatusID(szStatusBuff);
	m_lpGroup->dwGroupID = m_dwGroupID;
	int nIndex = m_listGroup.GetItemCount();
	CString str;
	str.Format("%d", nIndex+1);
	m_listGroup.InsertItem(nIndex, str);
	m_listGroup.SetItemState(m_nCurSelGroup, 0, -1);
	m_listGroup.SetItemState(nIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_listGroup.SetFocus();
	str.Format("%d", m_lpGroup->dwGroupID);
	m_listGroup.SetItemText(nIndex, 1, str);
	m_listGroup.SetItemText(nIndex, 2, m_lpGroup->szGroupName);
	m_nCurSelGroup = nIndex;
	memcpy(&m_lpGroupList->struGroupList[nIndex], m_lpGroup, sizeof(*m_lpGroup));
	
	delete[] pInputBuff;
	pInputBuff = NULL;
	
	UpdateData(FALSE);
}

void CDlgTermGroup::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	if (m_nCurSelGroup < 0)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "ÇëÑ¡ÔñÖÕ¶Ë×é", "Please choose a terminal group first.");
		g_StringLanType(szLan2, "ÖÕ¶Ë×é¹ÜÀí", "Terminal Group Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	
	UpdateData(TRUE);
	
	strcpy(m_lpGroup->szGroupName, m_szGroupName);
	m_lpGroup->dwSize = sizeof(*m_lpGroup);
	char* pInputBuff = NULL;
	DWORD dwInputSize = 0;
	ConvertTermGrpParamsStruToXml(m_lpGroup, &pInputBuff, dwInputSize);
	
	CString strCommand;
	strCommand.Format("PUT /ISAPI/Publish/TerminalMgr/terminalGroups/%d\r\n", m_lpGroup->dwGroupID);
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
	
	m_listGroup.SetItemText(m_nCurSelGroup, 2, m_lpGroup->szGroupName);
	memcpy(&m_lpGroupList->struGroupList[m_nCurSelGroup], m_lpGroup, sizeof(*m_lpGroup));
	
	delete[] pInputBuff;
	pInputBuff = NULL;
	
	UpdateData(FALSE);
}

BOOL CDlgTermGroup::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitTerminalCtrlList();
	InitGroupCtrlList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTermGroup::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	delete m_lpGroup;
	m_lpGroup = NULL;
	delete m_lpGroupList;
	m_lpGroupList = NULL;
	delete[] m_pOutputXmlBuffer;
	m_pOutputXmlBuffer = NULL;
}

void CDlgTermGroup::InitTerminalCtrlList()
{
	DWORD dwExStyle = m_listTerminal.GetExtendedStyle();
	dwExStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
	m_listTerminal.SetExtendedStyle(dwExStyle);
	
	char szLan[512] = {0};
	g_StringLanType(szLan, "ÐòºÅ", "Index");
	m_listTerminal.InsertColumn(0, szLan);
	m_listTerminal.SetColumnWidth(0, 60);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "ÖÕ¶Ë±àºÅ", "Terminal No.");
	m_listTerminal.InsertColumn(1, szLan);
	m_listTerminal.SetColumnWidth(1, 100);

	m_listTerminal.DeleteAllItems();
}

void CDlgTermGroup::InitGroupCtrlList()
{
	DWORD dwExStyle = m_listGroup.GetExtendedStyle();
	dwExStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
	m_listGroup.SetExtendedStyle(dwExStyle);
	
	char szLan[512] = {0};
	g_StringLanType(szLan, "ÐòºÅ", "Index");
	m_listGroup.InsertColumn(0, szLan);
	m_listGroup.SetColumnWidth(0, 60);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "ÖÕ¶Ë×é±àºÅ", "Group No.");
	m_listGroup.InsertColumn(1, szLan);
	m_listGroup.SetColumnWidth(1, 80);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "×éÃû³Æ", "Group Name");
	m_listGroup.InsertColumn(2, szLan);
	m_listGroup.SetColumnWidth(2, 100);

	m_listGroup.DeleteAllItems();
}

void CDlgTermGroup::RefreshTerminalList(DWORD dwaTerminal[], DWORD dwTermCount)
{
	if (dwTermCount < 1 || dwTermCount > MAX_TERS_A_GROUP)
	{
		return;
	}
	m_listTerminal.DeleteAllItems();
	for (int nTermCnt = 0; nTermCnt < dwTermCount; nTermCnt++)
	{
		CString str;
		str.Format("%d", nTermCnt+1);
		m_listTerminal.InsertItem(nTermCnt, str);
		str.Format("%d", dwaTerminal[nTermCnt]);
		m_listTerminal.SetItemText(nTermCnt, 1, str);
	}
}

void CDlgTermGroup::RefreshGroupList()
{
	if (NULL == m_lpGroupList)
	{
		return;
	}
	m_listGroup.DeleteAllItems();
	CString str;
	for (int nGrpCnt = 0; nGrpCnt < MAX_NUM_TERGROUP; nGrpCnt++)
	{
		if (0 == m_lpGroupList->struGroupList[nGrpCnt].dwGroupID)
		{
			break;
		}
		str.Format("%d", nGrpCnt+1);
		m_listGroup.InsertItem(nGrpCnt, str);
		str.Format("%d", m_lpGroupList->struGroupList[nGrpCnt].dwGroupID);
		m_listGroup.SetItemText(nGrpCnt, 1, str);
		m_listGroup.SetItemText(nGrpCnt, 2, m_lpGroupList->struGroupList[nGrpCnt].szGroupName);
	}
}

void CDlgTermGroup::UpdateGroupInfo(LPNET_DVR_TERMINAL_GROUP lpGroup)
{
	if (lpGroup == NULL)
	{
		return;
	}
	m_dwGroupID = lpGroup->dwGroupID;
	m_szGroupName = lpGroup->szGroupName;
	RefreshTerminalList(lpGroup->dwTerminalList, lpGroup->dwTermCount);
	UpdateData(FALSE);
}

void CDlgTermGroup::OnClickListGroup(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listGroup.GetFirstSelectedItemPosition();
	if (pos)
	{
		m_nCurSelGroup = m_listGroup.GetNextSelectedItem(pos);
		memcpy(m_lpGroup, &m_lpGroupList->struGroupList[m_nCurSelGroup], sizeof(m_lpGroupList->struGroupList[m_nCurSelGroup]));
		UpdateGroupInfo(m_lpGroup);
	}
	
	*pResult = 0;
}

void CDlgTermGroup::OnClickListTerminal(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if (m_nCurSelGroup < 0)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "ÇëÑ¡ÔñÖÕ¶Ë×é", "Please choose a terminal group first.");
		g_StringLanType(szLan2, "ÖÕ¶Ë×é¹ÜÀí", "Terminal Group Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	POSITION pos = m_listTerminal.GetFirstSelectedItemPosition();
	if (pos)
	{
		m_nCurSelTerminal = m_listTerminal.GetNextSelectedItem(pos);
		m_dwTerminalID = m_lpGroup->dwTerminalList[m_nCurSelTerminal];
		UpdateData(FALSE);
	}
	
	*pResult = 0;
}
