// DlgTermPlay.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgTermPlay.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTermPlay dialog


CDlgTermPlay::CDlgTermPlay(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTermPlay::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTermPlay)
	m_dwTerminalID = 0;
	m_dwBackBrightLevel = 0;
	m_bLogoEnable = FALSE;
	m_dwVolume = 0;
	//}}AFX_DATA_INIT
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	m_lpPlayCfgList = new NET_DVR_PLAY_CFG_LIST;
	memset(m_lpPlayCfgList, 0, sizeof(*m_lpPlayCfgList));
	m_lpPlayCfgList->dwSize = sizeof(*m_lpPlayCfgList);
	m_pOutputXmlBuffer = new char[MAX_LEN_XML];
	memset(m_pOutputXmlBuffer, 0, sizeof(char)*MAX_LEN_XML);
	m_nCurSelTerminal = -1;
}


void CDlgTermPlay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTermPlay)
	DDX_Control(pDX, IDC_LST_TERMINAL, m_listTerminal);
	DDX_Text(pDX, IDC_EDIT_TERMINAL_ID, m_dwTerminalID);
	DDX_Text(pDX, IDC_EDT_BACKLIGHT_LEV, m_dwBackBrightLevel);
	DDX_Check(pDX, IDC_CHECK_LOGO_ENABLE, m_bLogoEnable);
	DDX_Text(pDX, IDC_EDT_PLAYER_VOLUME, m_dwVolume);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTermPlay, CDialog)
	//{{AFX_MSG_MAP(CDlgTermPlay)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_GET_ALL, OnBtnGetAll)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_CLICK, IDC_LST_TERMINAL, OnClickLstTerminal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTermPlay message handlers

void CDlgTermPlay::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CDlgTermPlay::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	if (m_nCurSelTerminal < 0)
	{
		return;
	}

	UpdateData(TRUE);
	
	CString strCommand;
	strCommand.Format("GET /ISAPI/Publish/TerminalMgr/terminals/config/%d\r\n", m_dwTerminalID);
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
	
	LPNET_DVR_PLAY_CFG lpPlayCfg = &m_lpPlayCfgList->struPlayCfgList[m_nCurSelTerminal];
	memset(lpPlayCfg, 0, sizeof(*lpPlayCfg));
	lpPlayCfg->dwSize = sizeof(*lpPlayCfg);
	ConvertPlayParamsXmlToStru(m_pOutputXmlBuffer, lpPlayCfg);
	UpdatePlayParameters(m_nCurSelTerminal);
	
	UpdateData(FALSE);
}

void CDlgTermPlay::OnBtnGetAll() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	CString strCommand;
	strCommand.Format("GET /ISAPI/Publish/TerminalMgr/terminals/config\r\n");
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
	
	memset(m_lpPlayCfgList, 0, sizeof(*m_lpPlayCfgList));
	m_lpPlayCfgList->dwSize = sizeof(*m_lpPlayCfgList);
	ConvertPlayParamsXmlToStruList(m_pOutputXmlBuffer, m_lpPlayCfgList);
	RefreshTerminalList();
	
	UpdateData(FALSE);
}

void CDlgTermPlay::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	if (m_nCurSelTerminal < 0)
	{
		return;
	}
	
	UpdateData(TRUE);
	
	m_lpPlayCfgList->struPlayCfgList[m_nCurSelTerminal].dwSize = sizeof(m_lpPlayCfgList->struPlayCfgList[m_nCurSelTerminal]);
	m_lpPlayCfgList->struPlayCfgList[m_nCurSelTerminal].struScreenParam.dwBackLightLevel = m_dwBackBrightLevel;
	m_lpPlayCfgList->struPlayCfgList[m_nCurSelTerminal].struScreenParam.byBootLogoEnabled = m_bLogoEnable;
	m_lpPlayCfgList->struPlayCfgList[m_nCurSelTerminal].dwPlayerVolume = m_dwVolume;
	char* pInputBuff = NULL;
	DWORD dwInputSize = 0;
	ConvertPlayParamsStruToXml(&m_lpPlayCfgList->struPlayCfgList[m_nCurSelTerminal], &pInputBuff, dwInputSize);
	
	CString strCommand;
	strCommand.Format("PUT /ISAPI/Publish/TerminalMgr/terminals/config/%d\r\n", m_dwTerminalID);
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

void CDlgTermPlay::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	delete[] m_pOutputXmlBuffer;
	m_pOutputXmlBuffer = NULL;
	delete m_lpPlayCfgList;
	m_lpPlayCfgList = NULL;
}

BOOL CDlgTermPlay::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitTerminalCtrlList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTermPlay::InitTerminalCtrlList()
{
	DWORD dwExStyle = m_listTerminal.GetExtendedStyle();
	dwExStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
	m_listTerminal.SetExtendedStyle(dwExStyle);
	
	char szLan[512] = {0};
	g_StringLanType(szLan, "–Ú∫≈", "Index");
	m_listTerminal.InsertColumn(0, szLan);
	m_listTerminal.SetColumnWidth(0, 60);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "÷’∂À±‡∫≈", "Terminal No.");
	m_listTerminal.InsertColumn(1, szLan);
	m_listTerminal.SetColumnWidth(1, 100);
	
	m_listTerminal.DeleteAllItems();
}

void CDlgTermPlay::RefreshTerminalList()
{
	m_listTerminal.DeleteAllItems();
	CString str;
	for (int nTerCnt = 0; nTerCnt < MAX_NUM_TERMINAL; nTerCnt++)
	{
		if (0 == m_lpPlayCfgList->struPlayCfgList[nTerCnt].dwTerminalID)
		{
			break;
		}
		str.Format("%d", nTerCnt+1);
		m_listTerminal.InsertItem(nTerCnt, str);
		str.Format("%d", m_lpPlayCfgList->struPlayCfgList[nTerCnt].dwTerminalID);
		m_listTerminal.SetItemText(nTerCnt, 1, str);
	}
}

void CDlgTermPlay::UpdatePlayParameters(int nTerminalIndex)
{
	if (nTerminalIndex < 0 || nTerminalIndex >= MAX_NUM_TERMINAL)
	{
		return;
	}
	m_dwTerminalID = m_lpPlayCfgList->struPlayCfgList[nTerminalIndex].dwTerminalID;
	m_dwBackBrightLevel = m_lpPlayCfgList->struPlayCfgList[nTerminalIndex].struScreenParam.dwBackLightLevel;
	m_bLogoEnable = m_lpPlayCfgList->struPlayCfgList[nTerminalIndex].struScreenParam.byBootLogoEnabled;
	m_dwVolume = m_lpPlayCfgList->struPlayCfgList[nTerminalIndex].dwPlayerVolume;
	UpdateData(FALSE);
}

void CDlgTermPlay::OnClickLstTerminal(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listTerminal.GetFirstSelectedItemPosition();
	if (pos)
	{
		m_nCurSelTerminal = m_listTerminal.GetNextSelectedItem(pos);
		UpdatePlayParameters(m_nCurSelTerminal);
	}
	
	*pResult = 0;
}
