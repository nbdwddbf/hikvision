// DlgImExportIPCCfgFile.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgImExportIPCCfgFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgImExportIPCCfgFile dialog


/////////////////////////////////////////////////////////////////////////////
// DlgImexporIPCCfgFile dialog


DlgImexporIPCCfgFile::DlgImexporIPCCfgFile(CWnd* pParent /*=NULL*/)
	: CDialog(DlgImexporIPCCfgFile::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgImexporIPCCfgFile)
	m_csDevice = _T("");
	m_csFileName = _T("");
	m_csCopyFile = _T("");
	m_strOutput = _T("");
	m_strStatus = _T("");
	//}}AFX_DATA_INIT
	m_lHandle = -1;
	m_lDownloadHandle = -1;
	m_timerHandle = -1;
	m_iRecvFailedNum= 0;
    m_bProcessing = FALSE;
}


void DlgImexporIPCCfgFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgImexporIPCCfgFile)
	DDX_Control(pDX, IDC_TREEALL, m_treeAll);
	DDX_Text(pDX, IDC_EDIT_DEVICE, m_csDevice);
	DDX_Text(pDX, IDC_EDIT_FILE_NAME, m_csFileName);
	DDX_Text(pDX, IDC_EDIT_COPY_FILE, m_csCopyFile);
	DDX_Text(pDX, IDC_EDIT_OUTPUT, m_strOutput);
	DDX_Text(pDX, IDC_STATIC_DOWNLOAD_STATUS, m_strStatus);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgImexporIPCCfgFile, CDialog)
	//{{AFX_MSG_MAP(DlgImexporIPCCfgFile)
	ON_NOTIFY(NM_CLICK, IDC_TREEALL, OnClickTreeall)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_BROWSE_FILE, OnBtnBrowseFile)
	ON_BN_CLICKED(ID_BTN_GET_FLASH, OnBtnGetFile)
	ON_BN_CLICKED(ID_BTN_COPY_FLASH, OnBtnImport)
	ON_WM_CLOSE()
	ON_MESSAGE(MSG_IMPORT_IPC_CFG_FILE_STATUS, OnImportIPCCfgFileMessage)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgImexporIPCCfgFile message handlers

BOOL DlgImexporIPCCfgFile::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow();
	LoadTreeImage();
	CreateTree();
	return TRUE;
}

void DlgImexporIPCCfgFile::LoadTreeImage(void)
{
	CBitmap bmp[3];

	m_TreeImage.Create(16,16,ILC_COLOR32 | ILC_MASK,1,1);
	bmp[TREE_ALL].LoadBitmap(IDB_BITMAP_TREE);
	m_TreeImage.Add(&bmp[TREE_ALL],RGB(1,1,1));
	bmp[DEVICE_LOGOUT].LoadBitmap(IDB_BITMAP_LOGOUT);
	m_TreeImage.Add(&bmp[DEVICE_LOGOUT],RGB(1,1,1));
	bmp[DEVICE_LOGIN].LoadBitmap(IDB_BITMAP_LOGIN);
	m_TreeImage.Add(&bmp[DEVICE_LOGIN],RGB(1,1,1));
	
	m_treeAll.SetImageList(&m_TreeImage, LVSIL_NORMAL);
}

void DlgImexporIPCCfgFile::CreateTree(void)
{
	HTREEITEM hRoot = m_treeAll.InsertItem("All Devices", TREE_ALL, TREE_ALL,TVI_ROOT);
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0;
	HTREEITEM hDevice = NULL;
	for (i = 0; i < MAX_DEVICES; i++)
	{
		if (g_struDeviceInfo[i].iDeviceChanNum != -1)
		{
			strTemp.Format("%s", g_struDeviceInfo[i].chLocalNodeName);
			if (g_struDeviceInfo[i].lLoginID >= 0)
			{
				hDevice =  m_treeAll.InsertItem(strTemp, DEVICE_LOGIN, DEVICE_LOGIN,hRoot);
				m_treeAll.SetItemData(hDevice, DEVICE_LOGIN*1000 + g_struDeviceInfo[i].iDeviceIndex);
			}
			else
			{
				hDevice =  m_treeAll.InsertItem(strTemp, DEVICE_LOGOUT, DEVICE_LOGOUT,hRoot);
				m_treeAll.SetItemData(hDevice, DEVICE_LOGOUT*1000 + g_struDeviceInfo[i].iDeviceIndex);
			}	
		}
	}
	m_treeAll.Expand(hRoot,TVE_EXPAND);
	m_treeAll.Expand(m_treeAll.GetRootItem(),TVE_EXPAND);
}

void DlgImexporIPCCfgFile::OnClickTreeall(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	CPoint pt(0,0);
	CRect rc(0,0,0,0);
	GetCursorPos(&pt);
	GetDlgItem(IDC_TREEALL)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	ScreenToClient(&pt);
	pt.x = pt.x - rc.left;
	pt.y = pt.y - rc.top;

	UINT uFlag = 0;
	HTREEITEM hSelect= m_treeAll.HitTest(pt, &uFlag);

	if (NULL == hSelect) 
	{
		return;
	}
	
	m_treeAll.SelectItem(hSelect);

	BOOL bCheck = m_treeAll.GetCheck(hSelect);
	bCheck = !bCheck;

	if (TREE_ALL_T == m_treeAll.GetItemData(hSelect)/1000)
	{
		CheckAllDevState(hSelect, bCheck, uFlag);
	}
	else
	{
		m_iDeviceIndex = m_treeAll.GetItemData(hSelect)%1000;
		
		if (g_struDeviceInfo[m_iDeviceIndex].lLoginID >= 0)
		{
			m_csDevice.Format("%s--%s", g_struDeviceInfo[m_iDeviceIndex].chLocalNodeName, g_struDeviceInfo[m_iDeviceIndex].chDeviceIP);
			m_csFileName.Format("%s\\%s_ipc_cfg_file.xls", g_struLocalParam.chRemoteCfgSavePath, g_struDeviceInfo[m_iDeviceIndex].chLocalNodeName);
			GetDlgItem(ID_BTN_GET_FLASH)->EnableWindow(TRUE);
		}
		if ((g_struDeviceInfo[m_iDeviceIndex].lLoginID >= 0 && uFlag != LVHT_TOLEFT)\
			|| (g_struDeviceInfo[m_iDeviceIndex].lLoginID < 0 && uFlag == LVHT_TOLEFT) )
		{
			m_treeAll.SetCheck(hSelect, bCheck);
		}
		else
		{
			m_treeAll.SetCheck(hSelect, !bCheck);
		}
	}
	UpdateData(FALSE);
	*pResult = 0;
}

void DlgImexporIPCCfgFile::CheckAllDevState(HTREEITEM hRoot, BOOL bCheck, int uFlag)
{
	if (uFlag == LVHT_TOLEFT)
	{
		m_treeAll.SetCheck(hRoot, !bCheck);
	}
	else
	{
		m_treeAll.SetCheck(hRoot, bCheck);
	}
	

	HTREEITEM hChild = m_treeAll.GetChildItem(hRoot);
	while (hChild)
	{
		int iDevIndex = m_treeAll.GetItemData(hChild)%1000;
		int iLoginType = m_treeAll.GetItemData(hChild)/1000;

		if (g_struDeviceInfo[iDevIndex].lLoginID >= 0)
		{
			m_treeAll.SetCheck(hChild, bCheck);
		}

		hChild = m_treeAll.GetNextSiblingItem(hChild);
	}
}

void DlgImexporIPCCfgFile::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	if (m_lHandle >= 0)
	{
		NET_DVR_StopRemoteConfig(m_lHandle);
		m_lHandle = -1;
	}
	CDialog::OnCancel();
}

void DlgImexporIPCCfgFile::OnBtnBrowseFile() 
{
	// TODO: Add your control notification handler code here
	static char szFilter[]="All File(*.*)|*.*||";
	CFileDialog dlg(TRUE,"*.*","ini",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		szFilter);
	if (dlg.DoModal()==IDOK)
	{
		m_csCopyFile = dlg.GetPathName();
		UpdateData(FALSE);
	}	
}

void DlgImexporIPCCfgFile::OnBtnGetFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szFilePath[256] = {0};
	sprintf(szFilePath, "%s", m_csFileName.GetBuffer(0));
	char szLan[1024] = {0};
	m_iRecvFailedNum = 0;
    m_strOutput = "";
    m_bProcessing = FALSE;

	m_lDownloadHandle = NET_DVR_StartDownload(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_SDK_DOWNLOAD_IPC_CFG_FILE, NULL, 0, szFilePath);
	if (m_lDownloadHandle >= 0)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StartDownload[%s]", szFilePath);
		m_timerHandle = SetTimer(DOWNLOAD_IPC_CFG_FILE_TIMER, 50, NULL);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartDownload[%s]", szFilePath);
		g_StringLanType(szLan, "下载失败", "Download failed");
		AfxMessageBox(szLan);
	}

}

void __stdcall cbIPCCfgFileStatus(DWORD dwType, LPVOID lpBuffer, DWORD dwBufLen, LPVOID pUserData)
{
	DlgImexporIPCCfgFile *pThis = (DlgImexporIPCCfgFile*)pUserData;
	HWND hWnd = pThis->GetSafeHwnd();
	if (dwType == 1002)
	{
		::SendMessage(hWnd, MSG_IMPORT_IPC_CFG_FILE_STATUS, (WPARAM)dwType, (LPARAM)lpBuffer);
	}
	if (NULL == hWnd)
	{
		return;
	}
	
	
	::SendMessage(hWnd, MSG_IMPORT_IPC_CFG_FILE_STATUS, (WPARAM)dwType, (LPARAM)lpBuffer);
}

LRESULT DlgImexporIPCCfgFile::OnImportIPCCfgFileMessage(WPARAM wParam, LPARAM lParam)
{
	DWORD dwStatus = (DWORD)wParam;
	CString strTemp = "";
	if (NET_SDK_CALLBACK_STATUS_SUCCESS == dwStatus)
	{
		strTemp.Format("Status = Success \r\n");
		m_strOutput += strTemp;
	}
	if (NET_SDK_CALLBACK_STATUS_PROCESSING == dwStatus)
	{
		if (!m_bProcessing)
		{
			
			strTemp.Format("Status = in processing \r\n");
			m_strOutput += strTemp;
			m_bProcessing = TRUE;
		}
	}
	else if (NET_SDK_CALLBACK_STATUS_FAILED == dwStatus)
	{
		if (m_iRecvFailedNum == 0)
		{
			strTemp.Format("Status = failed \r\n");
			m_strOutput += strTemp;
		}
		if (lParam != NULL)
		{
			LPNET_DVR_IPC_CFG_FILE_ERR_INFO lpErrInfo = (LPNET_DVR_IPC_CFG_FILE_ERR_INFO)lParam;
			for (int i=0; i<64; i++)
			{
				CString strTemp;
				strTemp.Format("[%d] Row=%d ErrCode=%d\r\n", i+ m_iRecvFailedNum *64 + 1, lpErrInfo->struErrInfoSingle[i].wRow, lpErrInfo->struErrInfoSingle[i].wErrCode);
				m_strOutput += strTemp;
			}
			m_iRecvFailedNum ++;
		}
	}


	UpdateData(FALSE);

	return NULL;
}

void DlgImexporIPCCfgFile::OnBtnImport() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	char szFilePath[256] = {0};
	char szLan[1024] = {0};

	if (m_csCopyFile.GetLength() == 0)
	{
		g_StringLanType(szLan, "选择一个文件!", "choose a file!");
		AfxMessageBox(szLan);
		return;
	}


	NET_DVR_IPC_CFG_FILE_PARAM struIPCCfgFileParam = {0};
	strcpy(struIPCCfgFileParam.szFileName, m_csCopyFile.GetBuffer(0));
	if(m_iDeviceIndex < 0 || m_iDeviceIndex > 2048)
	{
		g_StringLanType(szLan, "先选择一个设备!", "choose a device!");
		AfxMessageBox(szLan);
		return;
	}
	
	m_lHandle = NET_DVR_StartRemoteConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_IMPORT_IPC_CFG_FILE, &struIPCCfgFileParam, sizeof(NET_DVR_IPC_CFG_FILE_PARAM), cbIPCCfgFileStatus, this);
	if (m_lHandle == -1)
	{
		g_StringLanType(szLan,"启动失败","Fail to start");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartRemoteConfig");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_StringLanType(szLan,"启动成功","Succeed to start");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StartRemoteConfig");
	}

}

void DlgImexporIPCCfgFile::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if (m_lHandle >= 0)
	{
		NET_DVR_StopRemoteConfig(m_lHandle);
		m_lHandle = -1;
	}
	CDialog::OnClose();
}

// void DlgImexporIPCCfgFile::OnTimer(UINT nIDEvent) 
// {
// 	// TODO: Add your message handler code here and/or call default
// 	char szLan[128] = {0};
// 	if (nIDEvent == DOWNLOAD_IPC_CFG_FILE_TIMER)
// 	{
// 		DWORD dwProgress = 0;
// 		DWORD dwState = 0;
// 		dwState = NET_DVR_GetDownloadState(m_lDownloadHandle, &dwProgress);
// 		
// 		if (dwState == 1)
// 		{
// 			g_StringLanType(szLan, "下载成功", "Download successfully");
// 			m_strStatus.Format(szLan);
// 		}
// 		else if (dwState == 2)
// 		{
// 			g_StringLanType(szLan, "正在下载,已下载:%d", "Is Downloading,progress:%d");
// 			m_strStatus.Format(szLan, dwProgress);
// 		}
// 		else if (dwState == 3)
// 		{
// 			g_StringLanType(szLan, "下载失败", "Download failed");
// 			m_strStatus.Format(szLan);
// 		}
// 		else if (dwState == 4)
// 		{
// 			g_StringLanType(szLan, "网络断开，状态未知", "Network disconnect, status unknown");
// 			m_strStatus.Format(szLan);
// 			if (100 == dwProgress )
// 			{
// 				KillTimer(m_timerHandle);
// 				g_StringLanType(szLan, "下载成功", "Download successfully");
// 				m_strStatus.Format(szLan);
// 			}
// 			
// 		}		
// 		if (dwState != 2)
// 		{        
// 			KillTimer(DOWNLOAD_IPC_CFG_FILE_TIMER);
// 			NET_DVR_StopDownload(m_lDownloadHandle);
// 		}
// 	}
// 
// 
// 	UpdateData(FALSE);
// 	
// 	CDialog::OnTimer(nIDEvent);
// }

#if (_MSC_VER >= 1500)	//vs2008
void DlgImexporIPCCfgFile::OnTimer(UINT_PTR nIDEvent)
#else
void DlgImexporIPCCfgFile::OnTimer(UINT nIDEvent)
#endif
{
	// TODO: Add your message handler code here and/or call default
	char szLan[128] = {0};
	if (nIDEvent == DOWNLOAD_IPC_CFG_FILE_TIMER)
	{
		DWORD dwProgress = 0;
		DWORD dwState = 0;
		dwState = NET_DVR_GetDownloadState(m_lDownloadHandle, &dwProgress);
		
		if (dwState == 1)
		{
			g_StringLanType(szLan, "下载成功", "Download successfully");
			m_strStatus.Format(szLan);
		}
		else if (dwState == 2)
		{
			g_StringLanType(szLan, "正在下载,已下载:%d", "Is Downloading,progress:%d");
			m_strStatus.Format(szLan, dwProgress);
		}
		else if (dwState == 3)
		{
			g_StringLanType(szLan, "下载失败", "Download failed");
			m_strStatus.Format(szLan);
		}
		else if (dwState == 4)
		{
			g_StringLanType(szLan, "网络断开，状态未知", "Network disconnect, status unknown");
			m_strStatus.Format(szLan);
			if (100 == dwProgress )
			{
				KillTimer(m_timerHandle);
				g_StringLanType(szLan, "下载成功", "Download successfully");
				m_strStatus.Format(szLan);
			}
			
		}		
		if (dwState != 2)
		{        
			KillTimer(DOWNLOAD_IPC_CFG_FILE_TIMER);
			NET_DVR_StopDownload(m_lDownloadHandle);
		}
	}
	
	
	UpdateData(FALSE);
	CDialog::OnTimer(nIDEvent);
}
