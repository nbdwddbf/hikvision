// DlgInfoDiffusionRelease.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInfoDiffusionRelease.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CALLBACK ProcessReleaseProgress(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
	CDlgInfoDiffusionRelease* pDlg = (CDlgInfoDiffusionRelease*)pUserData;
	if (pDlg == NULL)
	{
		return;
	}
	CString strTips;
	if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
	{
		if (lpBuffer == NULL || dwBufLen != sizeof(NET_DVR_SCHEDULE_PROGRESS_RESULT))
		{
			return;
		}
		LPNET_DVR_SCHEDULE_PROGRESS_RESULT lpProgress = (LPNET_DVR_SCHEDULE_PROGRESS_RESULT)lpBuffer;
		if (lpProgress->dwSubProgressNum != 0)
		{
			strTips.Format("终端发布总进度[%d", lpProgress->dwMainProgress);
			strTips += _T("%]");
		}
		else
		{
			strTips.Format("终端组发布进度[%d", lpProgress->dwMainProgress);
			strTips += _T("%]");
		}
		pDlg->ShowReleaseProgress(lpProgress->dwMainProgress, strTips);
	}
	else if (dwType == NET_SDK_CALLBACK_TYPE_STATUS && *(DWORD*)lpBuffer == NET_SDK_CALLBACK_STATUS_SUCCESS)
	{
		strTips += _T("完成发布[100%]");
		pDlg->ShowReleaseProgress(100, strTips);
		pDlg->PostMessage(WM_STOP_REMOTE_CONFIG, 0, 0);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionRelease dialog


CDlgInfoDiffusionRelease::CDlgInfoDiffusionRelease(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInfoDiffusionRelease::IDD, pParent)
    , m_time(COleDateTime::GetCurrentTime())
    , m_dateDate(COleDateTime::GetCurrentTime())
{
	//{{AFX_DATA_INIT(CDlgInfoDiffusionRelease)
	m_dwScheduleID = 0;
	m_dwTerminalID = 0;
	//}}AFX_DATA_INIT
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	m_nCurSelTerminal = -1;
	m_lpRelease = new NET_DVR_SCHEDULE_RELEASE;
	memset(m_lpRelease, 0, sizeof(*m_lpRelease));
	m_lpRelease->dwSize = sizeof(*m_lpRelease);
	m_pOutputXmlBuffer = new char[MAX_LEN_XML];
	memset(m_pOutputXmlBuffer, 0, sizeof(char)*MAX_LEN_XML);
	m_lConfigHandle = -1;
}


void CDlgInfoDiffusionRelease::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgInfoDiffusionRelease)
    DDX_Control(pDX, IDC_RELEASE_PROGRESS, m_progressRelease);
    DDX_Control(pDX, IDC_LIST_TERMINAL, m_listTerminal);
    DDX_Control(pDX, IDC_COMBO_RELEASE_TYPE, m_cmbReleaseType);
    DDX_Text(pDX, IDC_EDIT_SCHEDULE_ID, m_dwScheduleID);
    DDX_Text(pDX, IDC_EDIT_TERMINAL_ID, m_dwTerminalID);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_DATETIMEPICKER_START_DATE, m_date);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START_TIME, m_time);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START_DATE, m_dateDate);
}


BEGIN_MESSAGE_MAP(CDlgInfoDiffusionRelease, CDialog)
	//{{AFX_MSG_MAP(CDlgInfoDiffusionRelease)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_RELEASE, OnBtnRelease)
	ON_BN_CLICKED(IDC_BTN_TERMINAL_ADD, OnBtnTerminalAdd)
	ON_BN_CLICKED(IDC_BTN_TERMINAL_DEL, OnBtnTerminalDel)
	ON_BN_CLICKED(IDC_BTN_TERMINAL_MOD, OnBtnTerminalMod)
	ON_CBN_SELCHANGE(IDC_COMBO_RELEASE_TYPE, OnSelchangeComboReleaseType)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_CLICK, IDC_LIST_TERMINAL, OnClickListTerminal)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_STOP_REMOTE_CONFIG, OnStopRemoteConfig)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionRelease message handlers

void CDlgInfoDiffusionRelease::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CDlgInfoDiffusionRelease::OnBtnRelease() 
{
	// TODO: Add your control notification handler code here
	if (m_lConfigHandle >= 0)
	{
		return; //正在发布中，直接返回
	}

	UpdateData(TRUE);

	NET_DVR_SCHEDULE_PROGRESS_COND struCond = {0};
	
	m_lpRelease->dwScheduleID = m_dwScheduleID;
	int nSel = m_cmbReleaseType.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "发布管理", "Release Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbReleaseType.GetLBText(nSel, m_lpRelease->szReleaseType);
    CString strTime;
    strTime.Format("%04d%02d%02dT%02d:%02d:02d+08", m_dateDate.GetYear(), m_dateDate.GetMonth(), m_dateDate.GetDay(),
        m_time.GetHour(), m_time.GetMinute(), m_time.GetSecond());

	char* pInputBuff = NULL;
	DWORD dwInputSize = 0;
	ConvertScheduleReleaseParamsStruToXml(m_lpRelease, &pInputBuff, dwInputSize);

	CString strCommand;
	strCommand.Format("PUT /ISAPI/Publish/ScheduleMgr/release\r\n");
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

	struCond.dwSize = sizeof(struCond);
	struCond.dwScheduleNo = m_dwScheduleID;
	if (0 == strcmp(m_lpRelease->szReleaseType, "byGroup"))
	{
		struCond.byProgressType = 1;
		struCond.dwGroupNo = m_lpRelease->dwTerminalGroupList[0];
	}
	else if (0 == strcmp(m_lpRelease->szReleaseType, "byTerminal"))
	{
		struCond.byProgressType = 2;
		struCond.dwTerminalNo = m_lpRelease->dwTerminalList[0];
	}
	m_lConfigHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_GET_SCHEDULE_PUBLISH_PROGRESS, &struCond, sizeof(struCond), ProcessReleaseProgress, this);
	if (m_lConfigHandle < 0)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartRemoteConfig NET_DVR_GET_SCHEDULE_PUBLISH_PROGRESS");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StartRemoteConfig NET_DVR_GET_SCHEDULE_PUBLISH_PROGRESS");
	ShowReleaseProgress(0, "");
}

void CDlgInfoDiffusionRelease::OnBtnTerminalAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	int nSel = m_cmbReleaseType.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "发布管理", "Release Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	CString strReleaseType;
	m_cmbReleaseType.GetLBText(nSel, strReleaseType);
	int nIndex = m_listTerminal.GetItemCount();
	if (0 == strcmp(strReleaseType, "byTerminal"))
	{
		m_lpRelease->dwTerminalList[nIndex] = m_dwTerminalID;
		m_lpRelease->dwTerminalCount++; //数量+1
	}
	else if (0 == strcmp(strReleaseType, "byGroup"))
	{
		m_lpRelease->dwTerminalGroupList[nIndex] = m_dwTerminalID;
		m_lpRelease->dwGroupCount++; //数量+1
	}
	CString str;
	str.Format("%d", nIndex+1);
	m_listTerminal.InsertItem(nIndex, str);
	m_listTerminal.SetItemState(m_nCurSelTerminal, 0, -1);
	m_listTerminal.SetItemState(nIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_listTerminal.SetFocus();
	m_nCurSelTerminal = nIndex;
	str.Format("%d", m_dwTerminalID);
	m_listTerminal.SetItemText(nIndex, 1, str);
}

void CDlgInfoDiffusionRelease::OnBtnTerminalDel() 
{
	// TODO: Add your control notification handler code here
	if (m_nCurSelTerminal < 0)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "请选择终端/终端组", "Please choose a terminal/group first.");
		g_StringLanType(szLan2, "发布管理", "Release Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	
	int nSel = m_cmbReleaseType.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "发布管理", "Release Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	CString strReleaseType;
	m_cmbReleaseType.GetLBText(nSel, strReleaseType);
	if (0 == strcmp(strReleaseType, "byTerminal"))
	{
		for (int nTerCnt = m_nCurSelTerminal; nTerCnt < m_listTerminal.GetItemCount()-1; nTerCnt++)
		{
			m_listTerminal.SetItemText(nTerCnt, 1, m_listTerminal.GetItemText(nTerCnt+1, 1));
			m_lpRelease->dwTerminalList[nTerCnt] = m_lpRelease->dwTerminalList[nTerCnt+1];
		}
		m_lpRelease->dwTerminalList[m_listTerminal.GetItemCount()-1] = 0;
		m_lpRelease->dwTerminalCount--; //数量-1;
	}
	else if (0 == strcmp(strReleaseType, "byGroup"))
	{
		for (int nGrpCnt = m_nCurSelTerminal; nGrpCnt < m_listTerminal.GetItemCount()-1; nGrpCnt++)
		{
			m_listTerminal.SetItemText(nGrpCnt, 1, m_listTerminal.GetItemText(nGrpCnt+1, 1));
			m_lpRelease->dwTerminalGroupList[nGrpCnt] = m_lpRelease->dwTerminalGroupList[nGrpCnt+1];
		}
		m_lpRelease->dwTerminalGroupList[m_listTerminal.GetItemCount()-1] = 0;
		m_lpRelease->dwGroupCount--; //数量-1;
	}
	m_listTerminal.DeleteItem(m_listTerminal.GetItemCount()-1);
	m_nCurSelTerminal = -1;
}

void CDlgInfoDiffusionRelease::OnBtnTerminalMod() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (m_nCurSelTerminal < 0)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "请选择终端/终端组", "Please choose a terminal/group first.");
		g_StringLanType(szLan2, "发布管理", "Release Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	
	int nSel = m_cmbReleaseType.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "发布管理", "Release Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	CString strReleaseType;
	m_cmbReleaseType.GetLBText(nSel, strReleaseType);
	if (0 == strcmp(strReleaseType, "byTerminal"))
	{
		m_lpRelease->dwTerminalList[m_nCurSelTerminal] = m_dwTerminalID;
	}
	else if (0 == strcmp(strReleaseType, "byGroup"))
	{
		m_lpRelease->dwTerminalGroupList[m_nCurSelTerminal] = m_dwTerminalID;
	}
	CString str;
	str.Format("%d", m_dwTerminalID);
	m_listTerminal.SetItemText(m_nCurSelTerminal, 1, str);
}

BOOL CDlgInfoDiffusionRelease::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitTerminalCtrlList();
	m_cmbReleaseType.SetCurSel(0);
	OnSelchangeComboReleaseType();
	m_progressRelease.SetPos(0);
	m_progressRelease.SetStep(1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgInfoDiffusionRelease::InitTerminalCtrlList()
{
	DWORD dwExStyle = m_listTerminal.GetExtendedStyle();
	dwExStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
	m_listTerminal.SetExtendedStyle(dwExStyle);
	
	char szLan[512] = {0};
	g_StringLanType(szLan, "序号", "Index");
	m_listTerminal.InsertColumn(0, szLan);
	m_listTerminal.SetColumnWidth(0, 60);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "编号", "Number");
	m_listTerminal.InsertColumn(1, szLan);
	m_listTerminal.SetColumnWidth(1, 100);
}

void CDlgInfoDiffusionRelease::RefreshTernimalList(CString strReleaseType)
{
	m_listTerminal.DeleteAllItems();
	CString str;
	if (0 == strcmp(strReleaseType, "byTerminal"))
	{
		for (int nTerCnt = 0; nTerCnt < m_lpRelease->dwTerminalCount; nTerCnt++)
		{
			str.Format("%d", nTerCnt+1);
			m_listTerminal.InsertItem(nTerCnt, str);
			str.Format("%d", m_lpRelease->dwTerminalList[nTerCnt]);
			m_listTerminal.SetItemText(nTerCnt, 1, str);
		}
	}
	else if (0 == strcmp(strReleaseType, "byGroup"))
	{
		for (int nGrpCnt = 0; nGrpCnt < m_lpRelease->dwGroupCount; nGrpCnt++)
		{
			str.Format("%d", nGrpCnt+1);
			m_listTerminal.InsertItem(nGrpCnt, str);
			str.Format("%d", m_lpRelease->dwTerminalGroupList[nGrpCnt]);
			m_listTerminal.SetItemText(nGrpCnt, 1, str);
		}
	}
}

void CDlgInfoDiffusionRelease::OnSelchangeComboReleaseType()
{
	// TODO: Add your control notification handler code here
	int nSel = m_cmbReleaseType.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "发布管理", "Release Management");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	CString strReleaseType;
	m_cmbReleaseType.GetLBText(nSel, strReleaseType);
	if (0 == strcmp(strReleaseType, "byTerminal"))
	{
		char szLan[512] = {0};
		g_StringLanType(szLan, "终端编号", "Terminal No.");
		GetDlgItem(IDC_STAT_GRP_ID)->SetWindowText(szLan);
	}
	else if (0 == strcmp(strReleaseType, "byGroup"))
	{
		char szLan[512] = {0};
		g_StringLanType(szLan, "终端组编号", "Group No.");
		GetDlgItem(IDC_STAT_GRP_ID)->SetWindowText(szLan);
	}
	RefreshTernimalList(strReleaseType);
}

void CDlgInfoDiffusionRelease::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	delete m_lpRelease;
	m_lpRelease = NULL;
	
	delete[] m_pOutputXmlBuffer;
	m_pOutputXmlBuffer = NULL;
	
	StopRemoteConfig();
}

void CDlgInfoDiffusionRelease::OnClickListTerminal(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listTerminal.GetFirstSelectedItemPosition();
	if (pos)
	{
		m_nCurSelTerminal = m_listTerminal.GetNextSelectedItem(pos);
		int nSel = m_cmbReleaseType.GetCurSel();
		if (nSel == CB_ERR)
		{
			char szLan1[512] = {0};
			char szLan2[512] = {0};
			g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
			g_StringLanType(szLan2, "发布管理", "Release Management");
			MessageBox(szLan1, szLan2, MB_ICONWARNING);
			return;
		}
		CString strReleaseType;
		m_cmbReleaseType.GetLBText(nSel, strReleaseType);
		if (0 == strcmp(strReleaseType, "byTerminal"))
		{
			m_dwTerminalID = m_lpRelease->dwTerminalList[m_nCurSelTerminal];
		}
		else if (0 == strcmp(strReleaseType, "byGroup"))
		{
			m_dwTerminalID = m_lpRelease->dwTerminalGroupList[m_nCurSelTerminal];
		}
		
		UpdateData(FALSE);
	}
	
	*pResult = 0;
}

void CDlgInfoDiffusionRelease::StopRemoteConfig()
{
	Sleep(100);
	if (m_lConfigHandle >= 0)
	{
		if (!NET_DVR_StopRemoteConfig(m_lUserID))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopRemoteConfig");
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopRemoteConfig");
			m_lConfigHandle = -1;
		}
	}
}

void CDlgInfoDiffusionRelease::ShowReleaseProgress(DWORD dwProgress, CString strTips)
{
	m_progressRelease.SetPos(dwProgress);
	GetDlgItem(IDC_STATIC_TIPS)->SetWindowText(strTips);
}

DWORD CDlgInfoDiffusionRelease::GetRemoteConfigState()
{
	DWORD dwState = 0;
	if (!NET_DVR_GetRemoteConfigState(m_lConfigHandle, &dwState))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetRemoteConfigState");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetRemoteConfigState");
	}
	return dwState;
}

LRESULT CDlgInfoDiffusionRelease::OnStopRemoteConfig(WPARAM wParam, LPARAM lParam)
{
	StopRemoteConfig();
	return 0;
}
