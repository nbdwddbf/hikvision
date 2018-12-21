// DlgConfigFlash.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgConfigFlash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgConfigFlash dialog


CDlgConfigFlash::CDlgConfigFlash(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgConfigFlash::IDD, pParent)
{
	m_iDeviceIndex = -1;
	//{{AFX_DATA_INIT(CDlgConfigFlash)
	m_csDevice = _T("");
	m_csFileName = _T("");
	m_csUpgrade = _T("");
	m_csCopyFile = _T("");
	//}}AFX_DATA_INIT
}


void CDlgConfigFlash::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgConfigFlash)
	DDX_Control(pDX, IDC_TREEALL, m_treeAll);
	DDX_Text(pDX, IDC_EDIT_DEVICE, m_csDevice);
	DDX_Text(pDX, IDC_EDIT_FILE_NAME, m_csFileName);
	DDX_Text(pDX, IDC_EDIT_COPY_FILE, m_csCopyFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgConfigFlash, CDialog)
	//{{AFX_MSG_MAP(CDlgConfigFlash)
	ON_NOTIFY(NM_CLICK, IDC_TREEALL, OnClickTreeall)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_BROWSE_FILE, OnBtnBrowseFile)
	ON_BN_CLICKED(ID_BTN_GET_FLASH, OnBtnGetFlash)
	ON_BN_CLICKED(ID_BTN_COPY_FLASH, OnBtnCopyFlash)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgConfigFlash message handlers
BOOL CDlgConfigFlash::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow();
	LoadTreeImage();
	CreateTree();
	return TRUE;
}

void CDlgConfigFlash::LoadTreeImage(void)
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

void CDlgConfigFlash::CreateTree(void)
{
	HTREEITEM hRoot = m_treeAll.InsertItem("All Devices");
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

void CDlgConfigFlash::OnClickTreeall(NMHDR* pNMHDR, LRESULT* pResult) 
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
			if (!g_ValidIPv6((BYTE *)(g_struDeviceInfo[m_iDeviceIndex].chLocalNodeName)))
			{
				m_csFileName.Format("%s\\%s.cfg", g_struLocalParam.chRemoteCfgSavePath, g_struDeviceInfo[m_iDeviceIndex].chLocalNodeName);
			} 
			else
			{
				char chNewNodeName[130] = {0};
				g_replace(g_struDeviceInfo[m_iDeviceIndex].chLocalNodeName, chNewNodeName, ":", "-");
				m_csFileName.Format("%s\\%s.cfg", g_struLocalParam.chRemoteCfgSavePath, chNewNodeName);
			}			
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

void CDlgConfigFlash::CheckAllDevState(HTREEITEM hRoot, BOOL bCheck, int uFlag)
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

void CDlgConfigFlash::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CDlgConfigFlash::OnBtnBrowseFile() 
{
	// TODO: Add your control notification handler code here
	static char szFilter[]="All File(*.*)|*.*||";
	CFileDialog dlg(TRUE,"*.*","digicap",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		szFilter);
	if (dlg.DoModal()==IDOK)
	{
		m_csCopyFile = dlg.GetPathName();
		UpdateData(FALSE);
	}	
}

void CDlgConfigFlash::OnBtnGetFlash() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szFilePath[256] = {0};
	sprintf(szFilePath, "%s", m_csFileName.GetBuffer(0));
	char szLan[1024] = {0};
	if (!NET_DVR_GetConfigFile(g_struDeviceInfo[m_iDeviceIndex].lLoginID, szFilePath))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetConfigFile");
		g_StringLanType(szLan, "获取失败!", "get configure file fail!");
	}
	else
	{
		m_csCopyFile = m_csFileName;
		g_StringLanType(szLan, "获取成功!", "get configure file succ!");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetConfigFile %s", szFilePath);
	}	
	AfxMessageBox(szLan);
	UpdateData(FALSE);
}

void CDlgConfigFlash::OnBtnCopyFlash() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (g_struDeviceInfo[m_iDeviceIndex].iDeviceType == DS90XX_HF_S)
	{
		char szLan[1024] = {0};
		g_StringLanType(szLan, "导入配置参数后设备将自动重启!", "if load the configure file, the device will reboot!");

		if (IDOK!=MessageBox(szLan,"Warning",IDOK))
		{
			return;
		}
	}

	char szFilePath[256] = {0};
	HTREEITEM hRoot;
	HTREEITEM hChild;

	int iDevIndex = -1;
	CString sTemp;
	BOOL bChk = TRUE;
	BOOL bRet = FALSE;
	int iLoadDev = 0;//number of loading device
	if (m_csCopyFile.GetLength() == 0)
	{
		char szLan[1024] = {0};
		g_StringLanType(szLan, "选择一个文件!", "choose a file!");
		AfxMessageBox(szLan);
		return;
	}
	hRoot = m_treeAll.GetRootItem();
	if (hRoot==NULL)
	{
		return;
	}

	hChild = m_treeAll.GetChildItem(hRoot);
	
	while(hChild!=NULL)
	{
		iDevIndex=m_treeAll.GetItemData(hChild)%1000;
		bChk = m_treeAll.GetCheck(hChild);
		if(bChk)
		{
            if (!NET_DVR_SetConfigFile(g_struDeviceInfo[iDevIndex].lLoginID, m_csCopyFile.GetBuffer(0)))
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SetConfigFile");
                bRet = FALSE;
            }
            else
            {
                iLoadDev++;
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SetConfigFile");
            }
		}

		hChild =m_treeAll.GetNextSiblingItem(hChild);
	}
	char szLan1[1024] = {0};
	if (iLoadDev>0)
	{
		g_StringLanType(szLan1, "导入成功!", "load successfully!");	
	}
	else
	{
		g_StringLanType(szLan1, "未成功导入!", "load failed!");
	}
	AfxMessageBox(szLan1);
}
