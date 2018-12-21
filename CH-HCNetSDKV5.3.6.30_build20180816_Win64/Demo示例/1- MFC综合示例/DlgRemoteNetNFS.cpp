/**********************************************************
FileName:    DlgRemoteNetNFS.cpp
Description: NAS configuration      
Date:        2008/06/03
Note: 		<Global>struct, macro refer to GeneralDef.h, global variants and API refer to ClientDemo.cpp      
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/06/03>       <created>
***********************************************************/
#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRemoteNetNFS.h"
#include ".\dlgremotenetnfs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CDlgRemoteNetNFS *g_pDlgRemoteNfs = NULL;
UINT FindNasDirThread(LPVOID pParam);
/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteNetNFS dialog
UINT GetDirectoryThread(LPVOID pParam)
{	
    LONG lRet = -1;
    NET_DVR_IPSAN_SERACH_RET struSearchRet = {0};
	
    
    CString csTmp;
	char szLan[256] = {0};

	while (1)
	{
		lRet = NET_DVR_FindNextDirectory(g_pDlgRemoteNfs->m_lSearchHandle, &struSearchRet);
		if (lRet == NET_DVR_FILE_SUCCESS)
		{			
            sprintf(szLan, "%d", g_pDlgRemoteNfs->m_iDirectoryNum);
			g_pDlgRemoteNfs->m_listDirectory.InsertItem(g_pDlgRemoteNfs->m_iDirectoryNum, szLan ,0);
            g_pDlgRemoteNfs->m_listDirectory.SetItemText(g_pDlgRemoteNfs->m_iDirectoryNum, 1, (char*)struSearchRet.byDirectory);
			g_pDlgRemoteNfs->m_iDirectoryNum++;
		}
		else
		{
			if (lRet == NET_DVR_ISFINDING)
			{
				Sleep(5);
				continue;
			}
			if ((lRet == NET_DVR_NOMOREFILE) || (lRet == NET_DVR_FILE_NOFIND))
			{
				g_StringLanType(szLan, "查找", "Search");
				g_pDlgRemoteNfs->GetDlgItem(IDC_BTN_SEARCH_DIRECTORY)->SetWindowText(szLan);
				g_pDlgRemoteNfs->m_bSearching = FALSE;
				(g_pDlgRemoteNfs->GetDlgItem(IDC_STATIC_REMOTE_SEARCH_STATE))->ShowWindow(SW_HIDE);
				g_pMainDlg->AddLog(g_pDlgRemoteNfs->m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_FindNextDirectory file num[%d]", g_pDlgRemoteNfs->m_iDirectoryNum);

				g_pDlgRemoteNfs->m_iDirectoryNum = 0;
				break;
			}
			else
			{
				g_pDlgRemoteNfs->GetDlgItem(IDC_BTN_SEARCH_DIRECTORY)->SetWindowText("查找");
				g_pDlgRemoteNfs->m_bSearching = FALSE;
				(g_pDlgRemoteNfs->GetDlgItem(IDC_STATIC_REMOTE_SEARCH_STATE))->ShowWindow(SW_HIDE);
                g_StringLanType(szLan, "由于服务器忙,或网络故障,获取列表异常终止", "Since the server is busy, or network failure, abnormal termination of access to the  list");
                AfxMessageBox(szLan);
				g_pDlgRemoteNfs->m_iDirectoryNum = 0;
					break;
			}
		}
	}
	CloseHandle(g_pDlgRemoteNfs->m_hSearchThread);
	g_pDlgRemoteNfs->m_hSearchThread = NULL;
	NET_DVR_FindDirectoryClose(g_pDlgRemoteNfs->m_lSearchHandle);
	g_pDlgRemoteNfs->m_lSearchHandle = -1;
	g_pDlgRemoteNfs->m_bSearching = FALSE;
	return 0;
}

CDlgRemoteNetNFS::CDlgRemoteNetNFS(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteNetNFS::IDD, pParent)
	, m_csNFSIP(_T(""))
	, m_csNFSDir(_T(""))
	, m_iCurDisk(0)
{
	//{{AFX_DATA_INIT(CDlgRemoteNetNFS)
	m_wPort = 0;
	m_csFindNasIP = _T("");
	m_wFindNasPort = 0;
	m_csPasswd = _T("");
	m_csUserName = _T("");
	m_csNFSDomain = _T("");
	//}}AFX_DATA_INIT
    m_lSearchHandle = -1;
    m_lServerID = -1;
    m_iDevIndex = -1;
    m_lSearchHandle = -1;
    m_bSearching = FALSE;
    m_hSearchThread = NULL;
	m_hFindNasThread = NULL;
    m_iDirectoryNum = 0;
	m_lFindNasHandle = 0;
	m_lListNum= 0 ;
	m_lNasTestHandle = -1;
	memset(&m_struNasServerTestParam, 0, sizeof(NET_DVR_SERVER_TEST_PARA));
}

void CDlgRemoteNetNFS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteNetNFS)
	DDX_Control(pDX, IDC_COMBO_DISK_TYPE, m_comboDiskType);
	DDX_Control(pDX, IDC_COMBO_MOUNT_TYPE, m_comboMountType);
	DDX_Control(pDX, IDC_LIST_NASDIRCTORY, m_listFindNasDir);
	DDX_Control(pDX, IDC_LIST_DIRECTORY, m_listDirectory);
	DDX_Control(pDX, IDC_COMBO_NFS_DISK, m_comboNFSDisk);
	DDX_Text(pDX, IDC_EDIT_HIGH_NFS_IP, m_csNFSIP);
	DDX_Text(pDX, IDC_EDIT_NFS_DIR, m_csNFSDir);
	DDX_Text(pDX, IDC_EDIT_PORT, m_wPort);
	DDX_Text(pDX, IDC_EDIT_FINDNAS_IP, m_csFindNasIP);
	DDX_Text(pDX, IDC_EDIT_FINDNAS_PORT, m_wFindNasPort);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csPasswd);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_csUserName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgRemoteNetNFS, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteNetNFS)
	ON_BN_CLICKED(IDC_BTN_NFS_SAVE, OnBnClickedBtnNfsSave)
	ON_CBN_SELCHANGE(IDC_COMBO_NFS_DISK, OnCbnSelchangeComboNfsDisk)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBnClickedBtnExit)	
	ON_CBN_SELCHANGE(IDC_COMBO_DISK_TYPE, OnSelchangeComboDiskType)
	ON_BN_CLICKED(IDC_BTN_SEARCH_DIRECTORY, OnBtnSearchDirectory)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DIRECTORY, OnClickListDirectory)
	ON_BN_CLICKED(IDC_BTN_FINDNAS_DIR, OnBtnFindnasDir)
	ON_CBN_SELCHANGE(IDC_COMBO_MOUNT_TYPE, OnSelchangeComboMountType)
	ON_BN_CLICKED(IDC_BTN_NAS_SERVER_TEST, OnBtnNasServerTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteNetNFS message handlers
BOOL CDlgRemoteNetNFS::OnInitDialog()
{
	CDialog::OnInitDialog();
    g_pDlgRemoteNfs = this;
	CenterWindow();
	CString sTemp = _T("");
	char szTmp[129] = {0};
	DWORD dwReturned = 0;
	char szLan[128] = {0};
	memset(&m_struNetDiskCfg, 0, sizeof(NET_DVR_NET_DISKCFG_V40));
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_NET_DISKCFG_V40, 0, &m_struNetDiskCfg, sizeof(NET_DVR_NET_DISKCFG_V40), &dwReturned))
	{
		g_pMainDlg->AddLog(g_pMainDlg->m_iCurDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_NET_DISKCFG");
		g_StringLanType(szLan, "获取参数失败", "Get parameter failed");
		AfxMessageBox(szLan);
		GetDlgItem(IDC_BTN_NFS_SAVE)->EnableWindow(FALSE);
		return FALSE;
	}
	//Information of NFS
	for (int i=0; i<MAX_NET_DISK; i++)
	{
		sTemp.Format("%d", i+1);
		m_comboNFSDisk.AddString(sTemp);
	}
	m_iCurDisk = 0;
	m_comboNFSDisk.SetCurSel(m_iCurDisk);
	m_comboDiskType.SetCurSel(m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].byNetDiskType);

	memcpy(szTmp, m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].sDirectory, 128);
	m_csNFSDir.Format("%s", szTmp);
	m_csNFSIP.Format("%s", m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].byDevAddr);
    m_wPort = m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].wPort;

    m_listDirectory.SetExtendedStyle(m_listDirectory.GetExtendedStyle()|LVS_EX_FULLROWSELECT);
    int nIndex = 0;
    g_StringLanType(szLan, "序号", "Index");
    m_listDirectory.InsertColumn(nIndex, szLan,LVCFMT_LEFT,60,-1);
    nIndex++;
    
    g_StringLanType(szLan, "文件路径", "Directory");
    m_listDirectory.InsertColumn(nIndex, szLan,LVCFMT_LEFT, 400,-1);
    nIndex++;

	m_listFindNasDir.InsertColumn(0,"序号",LVCFMT_LEFT, 60, -1);
	m_listFindNasDir.InsertColumn(1,"目录名称",LVCFMT_LEFT, 400, -1);

	SetMountTypeToWnd(m_iCurDisk);

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRemoteNetNFS::SetMountTypeToWnd(int m_iCurDisk)
{
	char szLan[128] = {0};
	GetDlgItem(IDC_EDIT_USERNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_PASSWORD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_USERNAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_PASSWD)->ShowWindow(SW_HIDE);	
	GetDlgItem(IDC_STATIC_MOUNTTYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO_MOUNT_TYPE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_PORT)->ShowWindow(SW_HIDE);
	
	if (m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].byNetDiskType == 0)
	{
		GetDlgItem(IDC_STATIC_MOUNTTYPE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_MOUNT_TYPE)->ShowWindow(SW_SHOW);
		if (m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].uMountMethodParam.struNasMountParam.byMountType == 2)
		{
			m_comboMountType.SetCurSel(1);
			GetDlgItem(IDC_EDIT_USERNAME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_EDIT_PASSWORD)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_USERNAME)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_STATIC_PASSWD)->ShowWindow(SW_SHOW);	
			
			memcpy(szLan, m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].uMountMethodParam.struNasMountParam.uMountParam.struIdentificationParam.sPassword, \
				PASSWD_LEN);
			m_csPasswd.Format("%s", szLan);
			memset(szLan, 0, 128);
			memcpy(szLan, m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].uMountMethodParam.struNasMountParam.uMountParam.struIdentificationParam.sUserName, \
				NAME_LEN);
			m_csUserName.Format("%s", szLan);
		}
		else
		{
			m_comboMountType.SetCurSel(0);
		}
		
	}
	else if (m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].byNetDiskType == 1)
	{
		GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PORT)->ShowWindow(SW_SHOW);
	}
}

/*********************************************************
Function:	OnBnClickedBtnNfsSave
Desc:		Save current NFS config for theselected HD
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteNetNFS::OnBnClickedBtnNfsSave()
{
	UpdateData(TRUE);
	CString sTemp;
	char szLan[128] ={0};
	//加入了支持域名，因此此处去除判断是否为IP
/*	if (m_csNFSIP.IsEmpty() && !CheckIPStr(m_csNFSIP))
	{
		g_StringLanType(szLan, "请填写IP或域名", "IP address is null");
		AfxMessageBox(szLan);
		return;
	}*/
	ZeroMemory(&m_struNetDiskCfg.struNetDiskParam[m_iCurDisk], sizeof(m_struNetDiskCfg.struNetDiskParam[m_iCurDisk]));
	m_struNetDiskCfg.dwSize = sizeof(m_struNetDiskCfg);
	m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].byNetDiskType = m_comboDiskType.GetCurSel();	
	memcpy(m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].sDirectory, m_csNFSDir, m_csNFSDir.GetLength());
	sprintf((char *)m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].byDevAddr, "%s", m_csNFSIP);
    m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].wPort = m_wPort;

	if (m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].byNetDiskType == 0)//NFS
	{
		m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].uMountMethodParam.struNasMountParam.byMountType = \
			/*m_comboMountType.GetDlgItem(*/m_comboMountType.GetCurSel()+1;
			if (m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].uMountMethodParam.struNasMountParam.byMountType == 2) //0 ~1~NFS 2CFS
			{
				memcpy(m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].uMountMethodParam.struNasMountParam.uMountParam.struIdentificationParam.sPassword, \
					m_csPasswd, m_csPasswd.GetLength());
				memcpy(m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].uMountMethodParam.struNasMountParam.uMountParam.struIdentificationParam.sUserName, \
					m_csUserName, m_csUserName.GetLength());
			}
	}
	
	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_NET_DISKCFG_V40, 0, &m_struNetDiskCfg, sizeof(NET_DVR_NET_DISKCFG)))
	{
		g_pMainDlg->AddLog(g_pMainDlg->m_iCurDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_NET_DISKCFG");
		g_StringLanType(szLan, "参数保存失败", "save the parameter failed");
		AfxMessageBox(szLan);					
	}
	else
	{
		g_pMainDlg->AddLog(g_pMainDlg->m_iCurDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_NET_DISKCFG"); 
		g_StringLanType(szLan, "参数保存成功", "save the parameter successfully");
		AfxMessageBox(szLan);
	}
}

/*********************************************************
Function:	OnCbnSelchangeComboNfsDisk
Desc:		nfs disk selection
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteNetNFS::OnCbnSelchangeComboNfsDisk()
{
	UpdateData(TRUE);
	char szLan[128] ={0};
	/*if (m_csNFSIP.IsEmpty() && !CheckIPStr(m_csNFSIP))
	{
		g_StringLanType(szLan, "IP地址有误", "IP address error");
		AfxMessageBox(szLan);
		return;
	}*/
	CString csIP;
	char szTmp[200] = {0};
	//save the last disk configure
	sprintf((char *)m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].byDevAddr, "%s", m_csNFSIP);
	memcpy(m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].sDirectory, m_csNFSDir, m_csNFSDir.GetLength());
	m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].wPort = m_wPort;
	m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].byNetDiskType = (BYTE)m_comboDiskType.GetCurSel();
	//
	m_iCurDisk = m_comboNFSDisk.GetCurSel();
	// 9000_1.1 [2009-8-6]
    m_comboDiskType.SetCurSel(m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].byNetDiskType);
	if (m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].byNetDiskType == 0)
	{   
		GetDlgItem(IDC_EDIT_PORT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_HIDE);
	}
	else
	{
		m_wPort = m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].wPort;
		GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PORT)->ShowWindow(SW_SHOW);
	}
	memcpy(szTmp, m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].byDevAddr, 64);
	csIP.Format("%s", szTmp);
	m_csNFSIP = csIP;
	memset(szTmp, 0, 200);
	memcpy(szTmp, m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].sDirectory, PATHNAME_LEN);
	m_csNFSDir.Format("%s", szTmp);
	

	SetMountTypeToWnd(m_iCurDisk);
	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnBnClickedBtnExit
  Desc:		exit
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteNetNFS::OnBnClickedBtnExit()
{
	CDialog::OnCancel();
}



void CDlgRemoteNetNFS::OnSelchangeComboDiskType() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].byNetDiskType = (BYTE)m_comboDiskType.GetCurSel();
	if (m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].byNetDiskType == 0)
	{
		GetDlgItem(IDC_EDIT_PORT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_HIDE);
		
		GetDlgItem(IDC_STATIC_MOUNTTYPE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_MOUNT_TYPE)->ShowWindow(SW_SHOW);
	}
	else
	{
		m_struNetDiskCfg.struNetDiskParam[m_iCurDisk].wPort = m_wPort;
		GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PORT)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC_MOUNTTYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_MOUNT_TYPE)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_EDIT_USERNAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_USERNAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PASSWORD)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PASSWD)->ShowWindow(SW_HIDE);

	}
	UpdateData(FALSE);
}

void CDlgRemoteNetNFS::OnBtnSearchDirectory() 
{
    UpdateData(TRUE);
    char szLan[128] = {0};
    if (!m_bSearching)
    {
        NET_DVR_IPSAN_SERACH_PARAM struIpSanSearchParam = {0};
        UpdateData(TRUE);
        strncpy(struIpSanSearchParam.struIP.sIpV4, m_csNFSIP.GetBuffer(0), sizeof(struIpSanSearchParam.struIP.sIpV4));
        struIpSanSearchParam.wPort = m_wPort;
        
        m_lSearchHandle = NET_DVR_FindIpSanDirectory(m_lServerID, &struIpSanSearchParam);
        if (m_lSearchHandle == -1)
        {
            g_pMainDlg->AddLog(g_pMainDlg->m_iCurDeviceIndex, OPERATION_FAIL_T, "NET_DVR_FindIpSanDirectory");
            AfxMessageBox("Fail to find IpSan directory");
            return;
        }
        
        m_listDirectory.DeleteAllItems();
        
        DWORD dwThreadId;
        if (m_hSearchThread == NULL)
        {
            m_hSearchThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetDirectoryThread),this,0,&dwThreadId);		
        }
        if (dwThreadId == NULL)
        {
            g_StringLanType(szLan, "打开查找线程失败!", "Fail to open finding thread!");
            AfxMessageBox(szLan);
            return;
        }
        g_StringLanType(szLan, "停止查找", "Stop Searching");
        GetDlgItem(IDC_BTN_SEARCH_DIRECTORY)->SetWindowText(szLan);
        m_bSearching = TRUE;
        GetDlgItem(IDC_STATIC_REMOTE_SEARCH_STATE)->ShowWindow(SW_SHOW);
    }
    else
    {
        if (m_hSearchThread)
        {
            TerminateThread(m_hSearchThread, 0);
        }
        CloseHandle(m_hSearchThread);
        m_hSearchThread = NULL;
        NET_DVR_FindDirectoryClose(m_lSearchHandle);
        g_StringLanType(szLan, "查找", "Search");
        GetDlgItem(IDC_BTN_SEARCH_DIRECTORY)->SetWindowText(szLan);
        m_bSearching = FALSE;
        GetDlgItem(IDC_STATIC_REMOTE_SEARCH_STATE)->ShowWindow(SW_HIDE);
        //    m_iDirectoryNum = 0;
    }
    
}

void CDlgRemoteNetNFS::OnClickListDirectory(NMHDR* pNMHDR, LRESULT* pResult) 
{
    POSITION posVD = m_listDirectory.GetFirstSelectedItemPosition();
    
    char szLan[128] = {0};
    if (posVD == 0)
    {

        return;
    }
    int iVDCurSel = m_listDirectory.GetNextSelectedItem(posVD);
    
    m_csNFSDir = m_listDirectory.GetItemText(iVDCurSel, 1);

    UpdateData(FALSE);
    
 
    
	*pResult = 0;
}

void CDlgRemoteNetNFS::OnBtnFindnasDir() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

	m_listFindNasDir.DeleteAllItems();

	NET_DVR_NET_DISK_SERACH_PARAM   struDiskSerach = {0};
	char szLan[1024] = {0};
	struDiskSerach.wPort = m_wFindNasPort;

	if ( m_csFindNasIP.IsEmpty())
	{
		g_StringLanType(szLan, "IP地址不能为空!", "IP address can not be empty");
		AfxMessageBox(szLan);
		return ;
	}
	sprintf(struDiskSerach.struIP.sIpV4, "%s", m_csFindNasIP);
	m_lFindNasHandle = NET_DVR_StartRemoteConfig(m_lServerID,NET_DVR_FIND_NAS_DIRECTORY,&struDiskSerach,sizeof(struDiskSerach),NULL,this);
	if (m_lFindNasHandle< 0)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_FIND_NAS_DIRECTORY");
		return ;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_FIND_NAS_DIRECTORY");
		//SetTimer(NAS_FIND_TIMER,50,NULL);
		//获取查找状态
		DWORD dwState = 0;
		if (!NET_DVR_GetRemoteConfigState(m_lFindNasHandle,&dwState))
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetRemoteConfigState NET_DVR_FIND_NAS_DIRECTORY ");
			GetDlgItem(IDC_STATIC_NASFIND_STATUS)->SetWindowText("状态： 获取失败");
			NET_DVR_StopRemoteConfig(m_lFindNasHandle);
			//关闭计时器
		}
		else   //开启获取进度线程
		{
			DWORD dwThreadId;
			if (m_hFindNasThread == NULL)
			{
				m_hFindNasThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(FindNasDirThread),this,0,&dwThreadId);		
			}
			if (m_hFindNasThread == NULL)
			{
				g_StringLanType(szLan, "打开查找线程失败!", "Fail to open finding thread!");
				AfxMessageBox(szLan);

			}
		}
		
	}
}

/*********************************************************
Function:	GetFileThread
Desc:		get recorded file list thread
Input:		pParam,pointer to parameters
Output:	
Return:	
**********************************************************/
UINT FindNasDirThread(LPVOID pParam)
{

	LONG lRet = -1;
	CString csTmp;
	char szLan[128] = {0};
	//void* pBuffer = NULL;
	DWORD dwOutBufferSize = 0 ;
	LONG lFindNasNext =  -1 ;
	NET_DVR_NET_DISK_SERACH_RET struDiskSearchResult = {0};
	CDlgRemoteNetNFS * pFindNasDirDlg = (CDlgRemoteNetNFS *)pParam;
	pFindNasDirDlg->m_lListNum = 0;
		//pFindNasDirDlg->UpdateData(TRUE);
	while (1)
	{
        lFindNasNext = NET_DVR_GetNextRemoteConfig(pFindNasDirDlg->m_lFindNasHandle,&struDiskSearchResult, sizeof(struDiskSearchResult));

	   if (NET_SDK_GET_NEXT_STATUS_SUCCESS == lFindNasNext)// 未完待续
	   {
		   pFindNasDirDlg->GetDlgItem(IDC_STATIC_NASFIND_STATUS)->SetWindowText("状态：接受中");
           NET_DVR_NET_DISK_SERACH_RET *struNetDiskSerachRet = (NET_DVR_NET_DISK_SERACH_RET*)&struDiskSearchResult;
		   
		   pFindNasDirDlg->m_lListNum++;
		   sprintf(szLan,"%d",pFindNasDirDlg->m_lListNum );
		   pFindNasDirDlg->m_listFindNasDir.InsertItem(pFindNasDirDlg->m_lListNum,szLan);
           sprintf(szLan,"%s",struNetDiskSerachRet->byDirectory);
		   pFindNasDirDlg->m_listFindNasDir.SetItemText(pFindNasDirDlg->m_lListNum - 1,1,szLan);
		   continue;
		   pFindNasDirDlg->UpdateData(TRUE);
	   }
	   else if (NET_SDK_GET_NETX_STATUS_NEED_WAIT == lFindNasNext)	// 需等待
	   {
		   Sleep(5);
		   continue;
	   } 
	   else if(NET_SDK_GET_NEXT_STATUS_FINISH == lFindNasNext)// 数据全部取完
	   {
		  pFindNasDirDlg->GetDlgItem(IDC_STATIC_NASFIND_STATUS)->SetWindowText("状态：结束");
		  pFindNasDirDlg->m_lListNum = 0;
		  break;
	   }
	   else// 出现异常
	   {
		   pFindNasDirDlg->GetDlgItem(IDC_STATIC_NASFIND_STATUS)->SetWindowText("状态：异常");
		   sprintf(szLan," 出现异常 %d",lFindNasNext);
		   AfxMessageBox(szLan);
		   pFindNasDirDlg->m_lListNum = 0;
		   break;
	   }
	}
 	CloseHandle(pFindNasDirDlg->m_hFindNasThread);
 	pFindNasDirDlg->m_hFindNasThread = NULL;
	NET_DVR_StopRemoteConfig(pFindNasDirDlg->m_lFindNasHandle);

//	pFindNasDirDlg->UpdateWindow();
	return 0;
}

void CDlgRemoteNetNFS::OnSelchangeComboMountType() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (/*m_comboMountType.GetDlgItem(*/m_comboMountType.GetCurSel()/*)*/ == 1)
	{
		GetDlgItem(IDC_EDIT_USERNAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PASSWORD)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_USERNAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PASSWD)->ShowWindow(SW_SHOW);
	} 
	else
	{
		GetDlgItem(IDC_EDIT_USERNAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PASSWORD)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_USERNAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PASSWD)->ShowWindow(SW_HIDE);
	}
}

DWORD WINAPI CDlgRemoteNetNFS::GetNasServerTestInfoThread(LPVOID lpArg)
{
	CDlgRemoteNetNFS* pThis = reinterpret_cast<CDlgRemoteNetNFS*>(lpArg);
	DWORD dwState = 0;
	CString csErrInfo;
	while (1)
	{
		
		if (!NET_DVR_GetRemoteConfigState(pThis->m_lNasTestHandle, &dwState))
		{
			g_pMainDlg->AddLog(pThis->m_lNasTestHandle, OPERATION_FAIL_T, "NET_DVR_GetRemoteConfigState NET_DVR_FIND_NAS_DIRECTORY ");
			pThis->GetDlgItem(IDC_STATIC_NAS_SERVER_TEST_STATE)->SetWindowText("Get state Fail!");
			NET_DVR_StopRemoteConfig(pThis->m_lNasTestHandle);
			return -1;
		}
		else
		{
			if (dwState == PROCESSING)
			{
				pThis->GetDlgItem(IDC_STATIC_NAS_SERVER_TEST_STATE)->SetWindowText("Testing...");
			}
			else if (dwState == PROCESS_SUCCESS)
			{
				pThis->GetDlgItem(IDC_STATIC_NAS_SERVER_TEST_STATE)->SetWindowText("Test Success!");
				break;
			}
			else if (dwState == PROCESS_EXCEPTION)
			{
				pThis->GetDlgItem(IDC_STATIC_NAS_SERVER_TEST_STATE)->SetWindowText("Test Exception!");
				break;
			}
			else
			{
				csErrInfo.Format("Test Fail %d", dwState);
				pThis->GetDlgItem(IDC_STATIC_NAS_SERVER_TEST_STATE)->SetWindowText(csErrInfo);
				break;
			}
			
		}
		
	}
	if (-1 != pThis->m_lNasTestHandle)
	{
		if (!NET_DVR_StopRemoteConfig(pThis->m_lNasTestHandle))
		{
			g_pMainDlg->AddLog(pThis->m_iDevIndex, OPERATION_FAIL_T, "Stop Remote Config Failed");
		}
		else
		{
			g_pMainDlg->AddLog(pThis->m_iDevIndex, OPERATION_SUCC_T, "Stop Remote Config Successful");
			pThis->m_lNasTestHandle = -1;
		}
	}
	return 0 ;
}

void CDlgRemoteNetNFS::OnBtnNasServerTest() 
{
	UpdateData(TRUE);
	memset(&m_struNasServerTestParam, 0, sizeof(NET_DVR_SERVER_TEST_PARA));
	m_struNasServerTestParam.dwSize = sizeof(m_struNasServerTestParam);

	CString sTemp;
	char szLan[128] ={0};
	/*if (m_csNFSIP.IsEmpty() && !CheckIPStr(m_csNFSIP))
	{
		g_StringLanType(szLan, "IP或域名为空", "IP or domain address is null");
		AfxMessageBox(szLan);
		return;
	}*/

	m_struNasServerTestParam.unionServerPara.struNasPara.struNasPara.byNetDiskType = m_comboDiskType.GetCurSel();
	sprintf((char *)m_struNasServerTestParam.unionServerPara.struNasPara.struNasPara.byDevAddr, "%s", m_csNFSIP);
	memcpy(m_struNasServerTestParam.unionServerPara.struNasPara.struNasPara.sDirectory, m_csNFSDir, m_csNFSDir.GetLength());
    m_struNasServerTestParam.unionServerPara.struNasPara.struNasPara.wPort = m_wPort;
	
	if (m_struNasServerTestParam.unionServerPara.struNasPara.struNasPara.byNetDiskType == 0)//NFS
	{
		m_struNasServerTestParam.unionServerPara.struNasPara.struNasPara.uMountMethodParam.struNasMountParam.byMountType = \
			/*m_comboMountType.GetDlgItem(*/m_comboMountType.GetCurSel()+1;
			if (m_struNasServerTestParam.unionServerPara.struNasPara.struNasPara.uMountMethodParam.struNasMountParam.byMountType == 2) //0 ~1~NFS 2CFS
			{
				memcpy(m_struNasServerTestParam.unionServerPara.struNasPara.struNasPara.uMountMethodParam.struNasMountParam.uMountParam.struIdentificationParam.sPassword, \
					m_csPasswd, m_csPasswd.GetLength());
				memcpy(m_struNasServerTestParam.unionServerPara.struNasPara.struNasPara.uMountMethodParam.struNasMountParam.uMountParam.struIdentificationParam.sUserName, \
					m_csUserName, m_csUserName.GetLength());
			}
	}

	m_lNasTestHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_NAS_SERVER_TEST, &m_struNasServerTestParam, sizeof(m_struNasServerTestParam), NULL, this);
	if (m_lNasTestHandle >= 0)
	{
		g_pMainDlg->AddLog(m_lNasTestHandle, OPERATION_SUCC_T, "Start Remote Config successfully");
		DWORD dwThreadId;
		m_hGetInfoThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetNasServerTestInfoThread), this, 0, &dwThreadId);
		GetDlgItem(IDC_BTN_NFS_SAVE)->EnableWindow(TRUE);
	} 
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Start Remote Config failed");
		return;
	}
}

