// DlgInfoDiffusionTerminalUpgrade.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInfoDiffusionTerminalUpgrade.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CALLBACK ProcessUpgradeProgress(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
	CDlgInfoDiffusionTerminalUpgrade* pDlg = (CDlgInfoDiffusionTerminalUpgrade*)pUserData;
	if (pDlg == NULL)
	{
		return;
	}
	CString strTips;
	if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
	{
		if (lpBuffer == NULL || dwBufLen != sizeof(NET_DVR_UPGRADE_PROGRESS_RESULT))
		{
			return;
		}
		LPNET_DVR_UPGRADE_PROGRESS_RESULT lpProgress = (LPNET_DVR_UPGRADE_PROGRESS_RESULT)lpBuffer;
		if (lpProgress->dwSubProgressNum != 0)
		{
			strTips.Format("终端组升级进度[%d", lpProgress->dwMainProgress);
			strTips += _T("%]");
		}
		else
		{
			strTips.Format("终端升级进度[%d", lpProgress->dwMainProgress);
			strTips += _T("%]");
		}
		pDlg->ShowUpgradeProgress(lpProgress->dwMainProgress, strTips);
	}
	else if (dwType == NET_SDK_CALLBACK_TYPE_STATUS && *(DWORD*)lpBuffer == NET_SDK_CALLBACK_STATUS_SUCCESS)
	{
		strTips += _T("完成升级[100%]");
		pDlg->ShowUpgradeProgress(100, strTips);
		pDlg->PostMessage(WM_STOP_REMOTE_CONFIG, 0, 0);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionTerminalUpgrade dialog


CDlgInfoDiffusionTerminalUpgrade::CDlgInfoDiffusionTerminalUpgrade(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInfoDiffusionTerminalUpgrade::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInfoDiffusionTerminalUpgrade)
	m_dwTerminalNo = 0;
	m_dwGroupNo = 0;
	m_sFilePath = _T("");
	//}}AFX_DATA_INIT
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	memset(m_dwaTerminal, 0, sizeof(DWORD)*1024);
	m_nCurSelTerminal = -1;
	m_lConfigHandle = -1;
}


void CDlgInfoDiffusionTerminalUpgrade::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInfoDiffusionTerminalUpgrade)
	DDX_Control(pDX, IDC_COMBO_UPGRADE_TYPE, m_cmbUpgradeType);
	DDX_Control(pDX, IDC_LIST_TERMINAL, m_listTerminal);
	DDX_Control(pDX, IDC_PROGRESS, m_progressUpgrade);
	DDX_Text(pDX, IDC_EDIT_TERMINAL_NO, m_dwTerminalNo);
	DDX_Text(pDX, IDC_EDIT_GROUP_NO, m_dwGroupNo);
	DDX_Text(pDX, IDC_EDIT_FILE_PATH, m_sFilePath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInfoDiffusionTerminalUpgrade, CDialog)
	//{{AFX_MSG_MAP(CDlgInfoDiffusionTerminalUpgrade)
	ON_BN_CLICKED(IDC_BTN_UPGRADE_MOD, OnBtnUpgradeMod)
	ON_BN_CLICKED(IDC_BTN_UPGRADE_DEL, OnBtnUpgradeDel)
	ON_BN_CLICKED(IDC_BTN_UPGRADE_ADD, OnBtnUpgradeAdd)
	ON_BN_CLICKED(IDC_BTN_UPGRADE, OnBtnUpgrade)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_CHOOSE, OnBtnChoose)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_CLICK, IDC_LIST_TERMINAL, OnClickListTerminal)
	ON_CBN_SELCHANGE(IDC_COMBO_UPGRADE_TYPE, OnSelchangeComboUpgradeType)
	ON_WM_TIMER()
	ON_MESSAGE(WM_STOP_REMOTE_CONFIG, OnStopRemoteConfig)
	//}}AFX_MSG_MAP
	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionTerminalUpgrade message handlers

void CDlgInfoDiffusionTerminalUpgrade::OnBtnUpgradeMod() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (m_nCurSelTerminal < 0)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "请选择终端", "Please choose a terminal first.");
		g_StringLanType(szLan2, "终端升级", "Terminal Upgrade");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	int nSel = m_cmbUpgradeType.GetCurSel();
	if (nSel+1 == 1)
	{
		CString str;
		str.Format("%d", m_dwTerminalNo);
		m_listTerminal.SetItemText(m_nCurSelTerminal, 1, str);
		m_dwaTerminal[m_nCurSelTerminal] = m_dwTerminalNo;
	}
}

void CDlgInfoDiffusionTerminalUpgrade::OnBtnUpgradeDel() 
{
	// TODO: Add your control notification handler code here
	if (m_nCurSelTerminal < 0)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "请选择终端", "Please choose a terminal first.");
		g_StringLanType(szLan2, "终端升级", "Terminal Upgrade");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	int nSel = m_cmbUpgradeType.GetCurSel();
	if (nSel+1 == 1)
	{
		for (int nCnt = m_nCurSelTerminal; nCnt < m_listTerminal.GetItemCount()-1; nCnt++)
		{
			m_listTerminal.SetItemText(nCnt, 1, m_listTerminal.GetItemText(nCnt+1, 1));
			m_dwaTerminal[nCnt] = m_dwaTerminal[nCnt+1];
		}
		m_dwaTerminal[m_listTerminal.GetItemCount()-1] = 0;
		m_listTerminal.DeleteItem(m_listTerminal.GetItemCount()-1);
		m_nCurSelTerminal = -1;
	}
}

void CDlgInfoDiffusionTerminalUpgrade::OnBtnUpgradeAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	int nSel = m_cmbUpgradeType.GetCurSel();
	if (nSel+1 == 1)
	{
		int nIndex = m_listTerminal.GetItemCount();
		CString str;
		str.Format("%d", nIndex+1);
		m_listTerminal.InsertItem(nIndex, str);
		m_listTerminal.SetItemState(m_nCurSelTerminal, 0, -1);
		m_listTerminal.SetItemState(nIndex, LVIS_SELECTED, LVIS_SELECTED);
		m_listTerminal.SetFocus();
		m_nCurSelTerminal = nIndex;
		str.Format("%d", m_dwTerminalNo);
		m_listTerminal.SetItemText(nIndex, 1, str);
		m_dwaTerminal[nIndex] = m_dwTerminalNo;
	}
}

void CDlgInfoDiffusionTerminalUpgrade::OnBtnUpgrade() 
{
	// TODO: Add your control notification handler code here
	if (m_lConfigHandle >= 0)
	{
		return;
	}
	
	UpdateData(TRUE);
	
	int nSel = m_cmbUpgradeType.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "终端升级", "Terminal Upgrade");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	NET_DVR_PUBLISH_UPGRADE_COND struUpgradeCond = {0};
	struUpgradeCond.dwSize = sizeof(struUpgradeCond);
	if (nSel+1 == 1)
	{
		struUpgradeCond.dwUpgradeType = 1;
		struUpgradeCond.dwTerminalNum = m_listTerminal.GetItemCount();
		struUpgradeCond.pTerminalNo = (DWORD*)m_dwaTerminal;
	}
	else if (nSel+1 == 2)
	{
		struUpgradeCond.dwUpgradeType = 2;
		struUpgradeCond.dwGroupNo = m_dwGroupNo;
	}
	
	m_lConfigHandle = NET_DVR_UploadFile_V40(m_lUserID, UPLOAD_PUBLISH_UPGRADE_FILE, &struUpgradeCond, sizeof(struUpgradeCond), m_sFilePath.GetBuffer(0), NULL, 0);
	if (m_lConfigHandle < 0)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadFile_V40 UPLOAD_PUBLISH_UPGRADE_FILE");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadFile_V40 UPLOAD_PUBLISH_UPGRADE_FILE");
	
	SetTimer(999, 100, NULL);
	GetDlgItem(IDC_STATIC_TIPS)->SetWindowText("正在上传升级文件[0%]……");
}

void CDlgInfoDiffusionTerminalUpgrade::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CDlgInfoDiffusionTerminalUpgrade::OnBtnChoose() 
{
	// TODO: Add your control notification handler code here
	CString strFilter = _T("All Files(*.*)|*.*||)");
	CFileDialog fileChose(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
	if (fileChose.DoModal() != IDOK)
	{
		return;
	}
	m_sFilePath = fileChose.GetPathName();
	GetDlgItem(IDC_EDIT_FILE_PATH)->SetWindowText(m_sFilePath);
}

BOOL CDlgInfoDiffusionTerminalUpgrade::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitTerminalCtrlList();
	m_progressUpgrade.SetPos(0);
	m_progressUpgrade.SetStep(1);
	OnSelchangeComboUpgradeType();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgInfoDiffusionTerminalUpgrade::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	StopRemoteConfig();
}

void CDlgInfoDiffusionTerminalUpgrade::InitTerminalCtrlList()
{
	DWORD dwExStyle = m_listTerminal.GetExtendedStyle();
	dwExStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
	m_listTerminal.SetExtendedStyle(dwExStyle);
	
	char szLan[512] = {0};
	g_StringLanType(szLan, "序号", "Index");
	m_listTerminal.InsertColumn(0, szLan);
	m_listTerminal.SetColumnWidth(0, 60);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "终端号", "Terminal");
	m_listTerminal.InsertColumn(1, szLan);
	m_listTerminal.SetColumnWidth(1, 100);
}

void CDlgInfoDiffusionTerminalUpgrade::StopRemoteConfig()
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

void CDlgInfoDiffusionTerminalUpgrade::ShowUpgradeProgress(DWORD dwProgress, CString strTips)
{
	m_progressUpgrade.SetPos(dwProgress);
	GetDlgItem(IDC_STATIC_TIPS)->SetWindowText(strTips);
}

void CDlgInfoDiffusionTerminalUpgrade::OnClickListTerminal(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listTerminal.GetFirstSelectedItemPosition();
	if (pos)
	{
		m_nCurSelTerminal = m_listTerminal.GetNextSelectedItem(pos);
		m_dwTerminalNo = m_dwaTerminal[m_nCurSelTerminal];
		
		UpdateData(FALSE);
	}
	
	*pResult = 0;
}

void CDlgInfoDiffusionTerminalUpgrade::OnSelchangeComboUpgradeType() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_cmbUpgradeType.GetCurSel();
	if (nSel+1 == 1)
	{
		GetDlgItem(IDC_EDIT_GROUP_NO)->EnableWindow(FALSE);
		GetDlgItem(IDC_LIST_TERMINAL)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_TERMINAL_NO)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_UPGRADE_ADD)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_UPGRADE_MOD)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_UPGRADE_DEL)->EnableWindow(TRUE);
	}
	else if (nSel+1 == 2)
	{
		GetDlgItem(IDC_EDIT_GROUP_NO)->EnableWindow(TRUE);
		GetDlgItem(IDC_LIST_TERMINAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_TERMINAL_NO)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_UPGRADE_ADD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_UPGRADE_MOD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_UPGRADE_DEL)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_GROUP_NO)->EnableWindow(FALSE);
		GetDlgItem(IDC_LIST_TERMINAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_TERMINAL_NO)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_UPGRADE_ADD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_UPGRADE_MOD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_UPGRADE_DEL)->EnableWindow(FALSE);
	}
}

#if (_MSC_VER >= 1500)	//vs2008
void CDlgInfoDiffusionTerminalUpgrade::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgInfoDiffusionTerminalUpgrade::OnTimer(UINT nIDEvent)
#endif
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 999)
	{
		DWORD dwProgress = 0;
		LONG lStatus = -1;
		
		lStatus = NET_DVR_GetUploadState(m_lConfigHandle, &dwProgress);
		if (lStatus == -1)
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetUploadState");
			if (!NET_DVR_UploadClose(m_lConfigHandle))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadClose");
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadClose");
			}
			m_lConfigHandle = -1;
			KillTimer(999);
			return;
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetUploadState");
		}
		switch (lStatus)
		{
		case 1: //上传成功
			{
				m_progressUpgrade.SetPos(dwProgress);
				CString str;
				str.Format("正在上传升级文件……[%d]", dwProgress);
				str += _T("%");
				GetDlgItem(IDC_STATIC_TIPS)->SetWindowText(str);
				if (!NET_DVR_UploadClose(m_lConfigHandle))
				{
					g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadClose");
				}
				else
				{
					g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadClose");
				}
				m_lConfigHandle = -1;
				KillTimer(999);

				//开始获取升级状态
				m_lConfigHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_GET_PUBLISH_UPGRADE_PROGRESS, NULL, 0, ProcessUpgradeProgress, this);
				if (m_lConfigHandle < 0)
				{
					g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartRemoteConfig NET_DVR_GET_PUBLISH_UPGRADE_PROGRESS");
					return;
				}
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StartRemoteConfig NET_DVR_GET_PUBLISH_UPGRADE_PROGRESS");
				break;
			}
		case 2: //正在上传
			{
				m_progressUpgrade.SetPos(dwProgress);
				CString str;
				str.Format("正在上传升级文件……[%d]", dwProgress);
				str += _T("%");
				GetDlgItem(IDC_STATIC_TIPS)->SetWindowText(str);
				break;
			}
		case 3: //上传失败
			{
				if (!NET_DVR_UploadClose(m_lConfigHandle))
				{
					g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadClose");
				}
				else
				{
					g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadClose");
				}
				m_lConfigHandle = -1;
				KillTimer(999);
				char sTitle[64] = {0};
				char sMsg[64] = {0};
				g_StringLanType(sTitle, "终端升级", "Terminal Upgrade");
				g_StringLanType(sMsg, "上传升级文件失败", "Upload upgrade file failed.");
				MessageBox(sMsg, sTitle, MB_OK|MB_ICONWARNING);
				break;
			}
		case 4: //网络断开
			{
				if (!NET_DVR_UploadClose(m_lConfigHandle))
				{
					g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadClose");
				}
				else
				{
					g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadClose");
				}
				
				m_lConfigHandle = -1;
				KillTimer(999);
				char sTitle[64] = {0};
				char sMsg[64] = {0};
				g_StringLanType(sTitle, "终端升级", "Terminal Upgrade");
				g_StringLanType(sMsg, "网络断开", "Network disconnection.");
				MessageBox(sMsg, sTitle, MB_OK|MB_ICONWARNING);
				break;
			}
		}
	}
	
	CDialog::OnTimer(nIDEvent);
}

LRESULT CDlgInfoDiffusionTerminalUpgrade::OnStopRemoteConfig(WPARAM wParam, LPARAM lParam)
{
	StopRemoteConfig();
	return 0;
}

DWORD CDlgInfoDiffusionTerminalUpgrade::GetRemoteConfigState()
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
