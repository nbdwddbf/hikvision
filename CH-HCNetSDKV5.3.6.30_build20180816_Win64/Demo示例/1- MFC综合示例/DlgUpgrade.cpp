/**********************************************************
FileName:    DlgUpgrade.cpp
Description: update dialogbox     
Date:        2008/05/17
Note: 		<Global>struct, macro refer to GeneralDef.h, global variants and API refer to ClientDemo.cpp   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgUpgrade.h"
#include ".\dlgupgrade.h"


// CDlgUpgrade dialog
/*********************************************************
  Function:	CDlgUpgrade
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgUpgrade, CDialog)
CDlgUpgrade::CDlgUpgrade(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUpgrade::IDD, pParent)
	, m_csUpgradeFile(_T(""))
	, m_csUpgradeStat(_T(""))
	, m_lUpgradeHandle(0)
	, m_lServerID(-1)
	, m_lChannel(-1)
	, m_lpUpgradeTimer(NULL)
	, m_bUpgrade(FALSE)
    , m_dwAcsNo(0)
{
}

/*********************************************************
  Function:	~CDlgUpgrade
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgUpgrade::~CDlgUpgrade()
{
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgUpgrade::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgUpgrade)
	DDX_Control(pDX, IDC_PROGRESS_STEP, m_progressSub);
	DDX_Control(pDX, IDC_COMBO_CHAN, m_comboChan);
	DDX_Control(pDX, IDC_COMBO_UPGRADE_TYPE, m_comboUpgradeType);
	DDX_Control(pDX, IDC_COMBO_ENVIRONMENT, m_comboEnvironment);
	DDX_Control(pDX, IDC_PROGRESS_UPGRADE, m_progressUpgrade);
	DDX_Control(pDX, IDC_COMBO_CARD_TYPE, m_comboCardType);
    DDX_Control(pDX, IDC_COMBO_AUX_DEV, m_comboAuxDev);
	DDX_Text(pDX, IDC_EDIT_UPGRADE_FILE, m_csUpgradeFile);
	DDX_Text(pDX, IDC_STATIC_UPGRADE, m_csUpgradeStat);
	DDX_Text(pDX, IDC_STATIC_STEP, m_csUpgradeStep);
	DDX_Check(pDX, IDC_CHK_FUZZYUPGRADE, m_bFuzzyUpgrade);
    DDX_Text(pDX, IDC_EDIT_ACS_NO, m_dwAcsNo);
    DDX_Text(pDX, IDC_EDT_UNIT_ID, m_csUnitID);
    //}}AFX_DATA_MAP
}


/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgUpgrade, CDialog)
	//{{AFX_MSG_MAP(CDlgUpgrade)	
	ON_BN_CLICKED(IDC_BTN_BROWSE_FILE, OnBnClickedBtnBrowseFile)
	ON_BN_CLICKED(IDC_BTN_UPGRADE, OnBnClickedBtnUpgrade)
	ON_BN_CLICKED(IDC_BTN_UPGRADE_EXIT, OnBnClickedBtnUpgradeExit)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_SET_ENVIRO, OnBtnSetEnviro)
	ON_CBN_SELCHANGE(IDC_COMBO_UPGRADE_TYPE, OnSelchangeComboUpgradeType)
	ON_BN_CLICKED(IDC_BTN_GETUPGRADEINFO, OnBtnGetupgradeinfo)
	//}}AFX_MSG_MAP
	
END_MESSAGE_MAP()


// CDlgUpgrade message handlers
/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgUpgrade::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	m_csUpgradeFile.Format("c:\\digicap");
	UpdateData(FALSE);
	m_bUpgrade = FALSE;
	m_progressUpgrade.SetRange(0,100);
	m_progressUpgrade.SetPos(0);
	m_progressUpgrade.ShowWindow(SW_HIDE);
	m_comboEnvironment.SetCurSel(0);

    m_comboUpgradeType.ResetContent();
    m_comboUpgradeType.AddString("DVR");
    m_comboUpgradeType.AddString("Adapter");
    m_comboUpgradeType.AddString("Vca lib");
    m_comboUpgradeType.AddString("ACS");
	m_comboUpgradeType.AddString("IDS");
	m_comboUpgradeType.AddString("LED");
    m_comboUpgradeType.AddString("Intelligent");
    m_comboUpgradeType.SetCurSel(0);
	OnSelchangeComboUpgradeType();
    
    m_comboAuxDev.ResetContent();
    m_comboAuxDev.AddString("Keyboard");
    m_comboAuxDev.AddString("Movement");
	m_comboAuxDev.AddString("NetModule");
    m_comboAuxDev.AddString("Router");
    m_comboAuxDev.AddString("Zone");
    m_comboAuxDev.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/*********************************************************
  Function:	OnBnClickedBtnBrowseFile
  Desc:		browse update firmware
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgUpgrade::OnBnClickedBtnBrowseFile()
{
	UpdateData(TRUE);
	if (m_bFuzzyUpgrade)
	{
		CString Str = F_GetDirectoryPath();
		if(Str != "")
		{
			m_csUpgradeFile = Str;
			UpdateData(FALSE);
		}
	} 
	else
	{
		static char szFilter[]="All File(*.*)|*.*||";
		CFileDialog dlg(TRUE,"*.*","digicap",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
			szFilter);
		if (dlg.DoModal()==IDOK)
		{
			m_csUpgradeFile = dlg.GetPathName();
			UpdateData(FALSE);
		}
	}	
}

CString CDlgUpgrade::F_GetDirectoryPath()
{
    LPITEMIDLIST pidlRoot = NULL;
    SHGetSpecialFolderLocation(m_hWnd, CSIDL_DRIVES, &pidlRoot);
    BROWSEINFO bi;   //必须传入的参数,下面就是这个结构的参数的初始化
    CString strDisplayName;   //用来得到,你选择的活页夹路径,相当于提供一个缓冲区
    bi.hwndOwner = GetSafeHwnd();   //得到父窗口Handle值
    bi.pidlRoot = pidlRoot;   //这个变量就是我们在上面得到的.
    bi.pszDisplayName = strDisplayName.GetBuffer(MAX_PATH + 1);   //得到缓冲区指针
    bi.lpszTitle = "文件夹";   //设置标题
    bi.ulFlags = BIF_RETURNONLYFSDIRS;   //设置标志
    bi.lpfn = NULL;
    bi.lParam = 0;
    bi.iImage = 0;   //上面这个是一些无关的参数的设置,最好设置起来,
    LPITEMIDLIST lpIDList = SHBrowseForFolder(&bi);	//打开对话框
    strDisplayName.ReleaseBuffer();   //和上面的GetBuffer()相对应
    char pPath[MAX_PATH];
    CString Str;
    if(lpIDList)
    {
        SHGetPathFromIDList(lpIDList, pPath);
        Str = pPath;
    }
	
    return Str;
}

/*********************************************************
  Function:	start update
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgUpgrade::OnBnClickedBtnUpgrade()
{
	char m_szFileName[MAX_PATH];

	UpdateData(TRUE);
	strcpy(m_szFileName,m_csUpgradeFile);
    char szLan[128] = {0};
	/*
	CFile cFile;
	if (!cFile.Open(m_szFileName,NULL))
	{
		g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
		AfxMessageBox(szLan);
		return;
	}
	DWORD dwFileSize = (DWORD)cFile.GetLength();
	if (dwFileSize == 0)
	{
		g_StringLanType(szLan, "升级文件为空", "Upgrade file is empty");
		AfxMessageBox(szLan);
	}
	cFile.Close();
	*/
     
    if (m_comboUpgradeType.GetCurSel() == 0) // DVR upgrade 
    {
	    m_lUpgradeHandle = NET_DVR_Upgrade(m_lServerID, m_szFileName);
    }
    else if (m_comboUpgradeType.GetCurSel() == 1) // adapter upgrade
    {
        m_lUpgradeHandle = NET_DVR_AdapterUpgrade(m_lServerID, m_szFileName);
    }
    else if (m_comboUpgradeType.GetCurSel() == 2) // vca lib upgrade
    {
        m_lUpgradeHandle = NET_DVR_VcalibUpgrade(m_lServerID, m_comboChan.GetCurSel() + 1, m_szFileName);
    }
    else if (m_comboUpgradeType.GetCurSel() == 3)
    {
        DWORD dwDevNo = m_dwAcsNo;
        m_lUpgradeHandle = NET_DVR_Upgrade_V40(m_lServerID, ENUM_UPGRADE_ACS, m_szFileName, &dwDevNo, sizeof(dwDevNo));
    }
	else if (m_comboUpgradeType.GetCurSel() == 4)
	{
		NET_DVR_AUXILIARY_DEV_UPGRADE_PARAM struAuxiliaryDevUpgradeParam = {0};
		struAuxiliaryDevUpgradeParam.dwSize = sizeof(struAuxiliaryDevUpgradeParam);
		//struAuxiliaryDevUpgradeParam.byDevType = 0;//目前视频报警主机辅助设备类型只有键盘
        struAuxiliaryDevUpgradeParam.byDevType = m_comboAuxDev.GetCurSel();
		struAuxiliaryDevUpgradeParam.dwDevNo = m_comboChan.GetCurSel();
		m_lUpgradeHandle = NET_DVR_Upgrade_V40(m_lServerID, ENUM_UPGRADE_AUXILIARY_DEV, m_szFileName, &struAuxiliaryDevUpgradeParam, sizeof(struAuxiliaryDevUpgradeParam));
	}
	else if (m_comboUpgradeType.GetCurSel() == 5)
	{
		DWORD dwCardType = m_comboCardType.GetCurSel()+1;
		m_lUpgradeHandle = NET_DVR_Upgrade_V40(m_lServerID, ENUM_UPGRADE_LED, m_szFileName, &dwCardType, sizeof(dwCardType));
	}
    else if (m_comboUpgradeType.GetCurSel() == 6)
    {
        DWORD dwCardType = m_comboCardType.GetCurSel() + 1;
        NET_DVR_UPGRADE_PARAM struUpgradeParam = { 0 };
        struUpgradeParam.dwUpgradeType = ENUM_UPGRADE_INTELLIGENT;
        struUpgradeParam.sFileName = m_szFileName;
        char szUnitID[128] = { 0 };
        strncpy(szUnitID, (char*)m_csUnitID.GetBuffer(), 128);

        struUpgradeParam.pUnitIdList[0] = szUnitID;// "829282394af74ffca1a11d3d5c68e29b";
        m_lUpgradeHandle = NET_DVR_Upgrade_V50(m_lServerID, &struUpgradeParam);
    }

	if (m_lUpgradeHandle < 0)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_Upgrade");
		g_StringLanType(szLan, "升级失败", "Upgrade failed");
		AfxMessageBox(szLan);
	}
	else
	{
		GetDlgItem(IDC_STATIC_UPGRADE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_UPGRADE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_UPGRADE_EXIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BROWSE_FILE)->EnableWindow(FALSE);
		m_progressUpgrade.SetPos(0);
		m_progressUpgrade.ShowWindow(SW_SHOW);
		g_StringLanType(szLan, "状态：正在升级服务器，请等待......", "Status: Server is upgrading, please wait......");
		m_csUpgradeStat.Format(szLan);
		m_bUpgrade = TRUE;
		m_lpUpgradeTimer = SetTimer(UPGRADE_TIMER, 500, NULL);
		UpdateData(FALSE);
	}	
}

/*********************************************************
  Function:	OnBnClickedBtnUpgradeExit
  Desc:		exit update
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgUpgrade::OnBnClickedBtnUpgradeExit()
{
	if (m_lpUpgradeTimer)
	{
		KillTimer(UPGRADE_TIMER);
	}
	CDialog::OnCancel();
}

/*********************************************************
  Function:	OnTimer
  Desc:		refresh update status timer
  Input:	
  Output:	
  Return:	
**********************************************************/
#if (_MSC_VER >= 1500)	//vs2008
void CDlgUpgrade::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgUpgrade::OnTimer(UINT nIDEvent) 
#endif
{
	// TODO: Add your message handler code here and/or call default
	char szLan[128] = {0};
	if (nIDEvent == UPGRADE_TIMER)
	{
		if (m_bUpgrade)
		{
			int UpgradeStatic = NET_DVR_GetUpgradeState(m_lUpgradeHandle);
			DWORD dwError = NET_DVR_GetLastError();
			int iPos = NET_DVR_GetUpgradeProgress(m_lUpgradeHandle);
			
			LONG iSubProgress = -1;
			int iStep = NET_DVR_GetUpgradeStep(m_lUpgradeHandle, &iSubProgress);

			if(iStep != -1)
			{
				GetDlgItem(IDC_STATIC_STEP)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_PROGRESS_STEP)->ShowWindow(SW_SHOW);	
				m_progressSub.SetPos(iSubProgress);
				switch(iStep)
				{
				case STEP_READY:
					g_StringLanType(szLan, "正在准备升级", "Ready to upgrade file");
					m_csUpgradeStep.Format("%s", szLan);
					break;
				case STEP_RECV_DATA:
					g_StringLanType(szLan, "正在读取升级文件", "Receving upgrade file");
					m_csUpgradeStep.Format("%s", szLan);
					break;
				case STEP_UPGRADE:
					g_StringLanType(szLan, "正在升级系统", "Upgrading system");
					m_csUpgradeStep.Format("%s", szLan);
					break;
				case STEP_BACKUP:
					g_StringLanType(szLan, "正在备份系统", "Backuping system");
					m_csUpgradeStep.Format("%s", szLan);
					break;
				case STEP_SEARCH:
					g_StringLanType(szLan, "正在搜索升级文件", "Searching  upgrade file");
					m_csUpgradeStep.Format("%s", szLan);
					break;
				default:
					g_StringLanType(szLan, "未知阶段", "Unknow step");
					m_csUpgradeStep.Format("%s:%d", szLan, iStep);
					break;
				}
			}

			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetUpgradeProgress= [%d]",iPos);
			if (iPos >0)
			{
				m_progressUpgrade.SetPos(iPos);
			}
			if (UpgradeStatic == 2)
			{
				g_StringLanType(szLan, "状态：正在升级设备，请等待......", "Status: Device is upgrading, please wait......");
				m_csUpgradeStat.Format(szLan);
				UpdateData(FALSE);
			}
			else
			{
                bool modelFileNeedUpdate = false;
				switch (UpgradeStatic)
				{
				case -1:
					g_StringLanType(szLan, "升级失败", "Upgrade failed");
//					AfxMessageBox(szLan);			
					break;
                case 1:
                    if (true)
                    {
                        NET_DVR_XML_CONFIG_INPUT xmlInput = { 0 };
                        NET_DVR_XML_CONFIG_OUTPUT xmlOutput = { 0 };
                        xmlInput.dwSize = sizeof(NET_DVR_XML_CONFIG_INPUT);
                        xmlOutput.dwSize = sizeof(NET_DVR_XML_CONFIG_OUTPUT);
                        char *strUrl = "GET /ISAPI/ITC/AlgorithmsState\r\n";
                        xmlInput.lpRequestUrl = strUrl;
                        xmlInput.dwRequestUrlLen = strlen(strUrl);
                        xmlInput.lpInBuffer = NULL;
                        xmlInput.dwInBufferSize = 0;
                        xmlInput.dwRecvTimeOut = 1000;

                        char *pOutBuf = new char[5 * 1024];
                        memset(pOutBuf, 0, 5 * 1024);
                        xmlOutput.lpOutBuffer = pOutBuf;
                        xmlOutput.dwOutBufferSize = 5 * 1024;
                        if (NET_DVR_STDXMLConfig(m_lServerID, &xmlInput, &xmlOutput))
                        {
                            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
                            CString strRetXml = (const char*)xmlOutput.lpOutBuffer;
                            if (strRetXml.Find("modelFileNeedUpdate") > 0)
                            {
                                modelFileNeedUpdate = true;
                            }
                        }
                        else
                        {
                            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
                        }
                        delete[]pOutBuf;
                    }
                    if (m_comboUpgradeType.GetCurSel() == 4)
                    {
                        if (modelFileNeedUpdate)
                        {
                            g_StringLanType(szLan, "状态：升级设备成功并且需要升级模型文件", "Status:upgrade successfully and model file need update");
                        }
                        else
                        {
                            g_StringLanType(szLan, "状态：升级设备成功", "Status:upgrade successfully");
                        }
                    }
                    else
                    {
                        if (modelFileNeedUpdate)
                        {
                            g_StringLanType(szLan, "状态：升级设备成功,请升级模型文件并重启设备", "Status:upgrade successfully, update mode file and reboot please");
                        }
                        else
                        {
                            g_StringLanType(szLan, "状态：升级设备成功,请重启设备", "Status:upgrade successfully, reboot please");
                        }
                    }

					m_csUpgradeStat.Format(szLan);
					m_progressUpgrade.SetPos(100);
					break;			
				case 3:
					g_StringLanType(szLan, "状态：升级设备失败", "Status:upgrade failed");
					m_csUpgradeStat.Format(szLan);	
					break;
				case 4:
					g_StringLanType(szLan, "状态：从设备接收数据错误, 状态未知", "Status:get data with probrem from device, status unknown");
					m_csUpgradeStat.Format(szLan);					
					break;
				case 5:
					g_StringLanType(szLan, "状态：升级文件语言版本不匹配", "Status:Upgrade file language mismatch");
					m_csUpgradeStat.Format(szLan);				
					break;
				case 6:
					g_StringLanType(szLan, "状态：升级文件写flash文件失败", "Status:Upgrade file write Flash Fail!");
					m_csUpgradeStat.Format(szLan);				
					break;
                case 7:
                    g_StringLanType(szLan, "状态：升级包类型不匹配", "Status:Upgrade Pack Type Mismatch!");
                    m_csUpgradeStat.Format(szLan);				
					break;
                case 8:
                    g_StringLanType(szLan, "状态：升级包版本不匹配", "Status:Upgrade Pack Version Mismatch!");
                    m_csUpgradeStat.Format(szLan);				
					break;
                case 9:
                    g_StringLanType(szLan, "状态：系统被加锁（文件锁）", "Status:System has been locked (file lock)!");
                    m_csUpgradeStat.Format(szLan);
                    break;
                case 10:
                    g_StringLanType(szLan, "状态：备份区域异常", "Status:Backup regional anomaly!");
                    m_csUpgradeStat.Format(szLan);
                    break;
                case 11:
                    g_StringLanType(szLan, "状态：系统卡满", "Status:System card is full!");
                    m_csUpgradeStat.Format(szLan);
                    break;
                case 12:
                    g_StringLanType(szLan, "状态：重连升级失败（无效的SessionID）", "Status:Reconnect failed(Invalid SessionID)!");
                    m_csUpgradeStat.Format(szLan);
                    break;
                case 13:
                    g_StringLanType(szLan, "状态：服务正忙", "Status:Server is Busy!");
                    m_csUpgradeStat.Format(szLan);
                    break;
				default: 
					break;
				}
				UpdateData(FALSE);
				m_bUpgrade = FALSE;
				GetDlgItem(IDC_BTN_UPGRADE)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_UPGRADE_EXIT)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_BROWSE_FILE)->EnableWindow(TRUE);
				if (!NET_DVR_CloseUpgradeHandle(m_lUpgradeHandle))
				{
					g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_CloseUpgradeHandle");
				}
				GetDlgItem(IDC_STATIC_STEP)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_PROGRESS_STEP)->ShowWindow(SW_HIDE);	
				m_lUpgradeHandle = -1;
			}
		}		
	}
	CDialog::OnTimer(nIDEvent);
}

/*********************************************************
  Function:	OnBtnSetEnviro
  Desc:		set the environment of the network
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgUpgrade::OnBtnSetEnviro() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};

	if (!NET_DVR_SetNetworkEnvironment(m_comboEnvironment.GetCurSel()))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SetNetworkEnvironment[%d]", m_comboEnvironment.GetCurSel());
		g_StringLanType(szLan, "设置网络环境", "Set up the network environment!");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SetNetworkEnvironment[%d]", m_comboEnvironment.GetCurSel());
	}
	
}

void CDlgUpgrade::OnSelchangeComboUpgradeType() 
{
    char szLan[64] = {0};
    if (m_comboUpgradeType.GetCurSel() == 2)
    {
		g_StringLanType(szLan, "通道", "Chan");
		GetDlgItem(IDC_STATIC_CHAN)->SetWindowText(szLan);
        GetDlgItem(IDC_STATIC_CHAN)->ShowWindow(SW_SHOW);
        m_comboChan.ShowWindow(SW_SHOW);

		m_comboChan.ResetContent();
		char szLan[128] = {0};
		for (int i = 0; i < g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum; i++)
		{
			sprintf(szLan, "Chan %d", i + 1);
			m_comboChan.AddString(szLan);
		}
    }
    else
    {
        GetDlgItem(IDC_STATIC_CHAN)->ShowWindow(SW_HIDE);
        m_comboChan.ShowWindow(SW_HIDE);
    }
    if (m_comboUpgradeType.GetCurSel() == 3)
    {
        GetDlgItem(IDC_STATIC_ACS_NO)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_ACS_NO)->ShowWindow(SW_SHOW);
    }
    else
    {
        GetDlgItem(IDC_STATIC_ACS_NO)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_ACS_NO)->ShowWindow(SW_HIDE);
    }
    if (m_comboUpgradeType.GetCurSel() == 4)
    {
        g_StringLanType(szLan, "设备", "Dev");
        GetDlgItem(IDC_STATIC_CHAN)->SetWindowText(szLan);
        GetDlgItem(IDC_STATIC_CHAN)->ShowWindow(SW_SHOW);
        m_comboChan.ShowWindow(SW_SHOW);
        
        m_comboChan.ResetContent();        
        for (int i = 0; i < 32; i++)
        {
            sprintf(szLan, "Dev %d", i);
            m_comboChan.AddString(szLan);
        }
    }
    else
    {
        GetDlgItem(IDC_STATIC_CHAN)->ShowWindow(SW_HIDE);
        m_comboChan.ShowWindow(SW_HIDE);
    }
	if (m_comboUpgradeType.GetCurSel() == 5)
	{
		g_StringLanType(szLan, "类型", "Type");
        GetDlgItem(IDC_STATIC_CHAN)->SetWindowText(szLan);
		GetDlgItem(IDC_STATIC_TYPE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_CARD_TYPE)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_STATIC_TYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_CARD_TYPE)->ShowWindow(SW_HIDE);
	}
}

void CDlgUpgrade::OnBtnGetupgradeinfo() 
{
	// TODO: Add your control notification handler code here
	//2013-06-17
	UpdateData(TRUE);
	if(m_csUpgradeFile.Compare(_T("")) == 0)
	{
		AfxMessageBox("文件路径为空!");
		return;
	}
	char szFileName[64] = {0};
	long lFileNameLen = 64;
	CString strFileName;
	CString strFilePath;
	char* szFilePath = new char[m_csUpgradeFile.GetLength()+1];
	memset(szFilePath, 0, sizeof(szFilePath));
	memcpy(szFilePath, m_csUpgradeFile, m_csUpgradeFile.GetLength()+1);
 	
// 	if(!NET_DVR_FindTargetFile(m_lServerID, m_lChannel, szFilePath, szFileName, lFileNameLen))
// 	{
// 		delete []szFilePath;
// 		szFilePath = NULL;
// 		DWORD dwRet = NET_DVR_GetLastError();
// 		if (dwRet == NET_DVR_DIR_ERROR)
// 		{
// 			AfxMessageBox("路径错误!");
// 			return;
// 		}
// 		if (dwRet == NET_DVR_NO_CURRENT_UPDATEFILE)
// 		{
// 			AfxMessageBox("没有匹配文件!");
// 			return;
// 		}
// 		return;
// 	}

	NET_DVR_FUZZY_UPGRADE struFuzzyUpgrade = {0};
	DWORD dwReturn = 0;
	BOOL bRet = NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_FUZZY_UPGRADE, m_lChannel, &struFuzzyUpgrade, sizeof(struFuzzyUpgrade), &dwReturn);
	if (!bRet)
	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "获取信息失败", "Get ParamInfo failed");
 		AfxMessageBox(szLan);
		return;
	}
	char chTargeName[260] = {0};
	int iRet = findTargetFile(szFilePath, struFuzzyUpgrade.sUpgradeInfo, chTargeName);
	if(iRet == 0)
	{
 		strFileName.Format(_T("%s"), chTargeName);
		m_csUpgradeFile.Format(_T("%s"), strFileName);
		delete []szFilePath;
		szFilePath = NULL;
	}
	delete []szFilePath;
	szFilePath = NULL;
	UpdateData(FALSE);
}

/******************************************
函数:	ConvertData
描述:	利用简单的异或进行数据变换，用于升级文件的打包和解包  
输入:	src - source data
		len - data length
输出:	dst - destination  data
返回值: HPR_OK-成功，HPR_ERROR-失败
******************************************/
int CDlgUpgrade::ConvertData(const char *src, char *dst, int nLen)
{
    /* 固定的幻数，用于异或变换 */
    BYTE byMagic[16] = {0xba, 0xcd, 0xbc, 0xfe, 0xd6, 0xca, 0xdd, 0xd3,
		0xba, 0xb9, 0xa3, 0xab, 0xbf, 0xcb, 0xb5, 0xbe};
    int i, j;
    int nMagiclen, nStartMagic;
	
	//判断参数有效性
    if(src == NULL || dst == NULL)
    {
        return -1;
    }
	
    nMagiclen = sizeof(byMagic);
	//lint --e{440}
    for(i = 0, nStartMagic = 0; i<nLen; nStartMagic = (nStartMagic + 1) % nMagiclen)
    {
        //用startmagic控制每次内循环magic的起始位置
        for(j = 0; (j < nMagiclen) && (i < nLen); j++, i++)
        {
			// 进行异或变换
            //“(char)”类型强制转换不会有问题，因为是在做异或操作
            *dst++ = *src++ ^ (char)byMagic[(nStartMagic + j) % nMagiclen];   
        }
    }
    return 0;
}
#define UPDATE_FILE_FLAG_SIZE  18
#define UPDATE_FILE_HEAD_SIZE  64

/*************************************************
Function: findTargetFile 
Description: 查找目标文件
Input:     szFilePath: 文件夹路径
szFileFlag: 匹配标识
Output: szTargetFileName: 目标文件 
Return: 0成功,-1失败
*************************************************/
int CDlgUpgrade::findTargetFile(const char* szFilePath, const char* szFileFlag, char* szTargetFileName)
{
#if defined(_WIN32) || defined(_WIN64)
	char szFind[MAX_PATH] = {0};
	char szFile[MAX_PATH] = {0};
	WIN32_FIND_DATA FindFileData;
	strcpy(szFind, szFilePath);
    strcat(szFind, "\\*.*");
	HANDLE hFind = ::FindFirstFileA(szFind, &FindFileData);
    if (INVALID_HANDLE_VALUE == hFind)
	{
		FindClose(hFind);
		return -1;
	}
	while(TRUE)
    {
        if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            if(FindFileData.cFileName[0] != '.') //存在子文件夹
            {
                strcpy(szFile, szFilePath);
                strcat(szFile, "\\");
                strcat(szFile, FindFileData.cFileName);
                if (findTargetFile(szFile, szFileFlag, szTargetFileName) == 0)
                {
					return 0;
                }
            }
        }
        else
        {      //deal with FindFileData.cFileName
			strcpy(szFile,szFilePath);
			strcat(szFile, "\\");
			strcat(szFile,FindFileData.cFileName);
			
			HANDLE hFile = ::CreateFileA(szFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (INVALID_HANDLE_VALUE != hFind)
			{
				if (::SetFilePointer(hFile, 0, 0, FILE_BEGIN) != HFILE_ERROR)
				{
					char szReadBuf[UPDATE_FILE_HEAD_SIZE+1] = {0};
					DWORD dwRealReadNum = 0;
					if (ReadFile(hFile, szReadBuf, UPDATE_FILE_HEAD_SIZE, &dwRealReadNum, NULL))
					{
						if (dwRealReadNum == UPDATE_FILE_HEAD_SIZE)
						{
							char szDecodeRes[UPDATE_FILE_HEAD_SIZE+1] = {0};
							char szDecodeFlag[UPDATE_FILE_FLAG_SIZE+1] = {0};
							//解码文件头信息
							ConvertData(szReadBuf, szDecodeRes, UPDATE_FILE_HEAD_SIZE);
							//从文件头中取出FLAG
							for (int i = 0; i < UPDATE_FILE_FLAG_SIZE; i++)
							{
								szDecodeFlag[i] = szDecodeRes[i+44];
							}
						//	DebugString("Flag:%s", szDecodeFlag);
							if (strcmp(szDecodeFlag, szFileFlag) == 0)  //找到匹配文件，不在继续搜索
							{
								strcpy(szTargetFileName, szFile);
								CloseHandle(hFile);
								FindClose(hFind);
								return 0;
							}
						}
					}
				}
			}
			CloseHandle(hFile);
			
        }
		if(!FindNextFile(hFind,&FindFileData)) //文件搜索结束
		{
			break;
		}
    }
    FindClose(hFind);
	return -1;
#else
	return -1;
#endif
}
