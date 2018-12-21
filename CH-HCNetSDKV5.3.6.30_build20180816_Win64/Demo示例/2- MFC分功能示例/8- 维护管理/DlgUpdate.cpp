/*******************************************************
Copyright 2008-2011 Hikvision Digital Technology Co., Ltd. 
文  件：	DlgUpdate.cpp
开发单位：	杭州海康威视
编  写：	shizhiping
日  期：	2009.5
描  述：	远程升级
修  改：	
********************************************************/

#include "stdafx.h"
#include "Manage.h"
#include "DlgUpdate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgUpdate dialog


CDlgUpdate::CDlgUpdate(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUpdate::IDD, pParent)
	, m_csUpgradeFile(_T(""))
	, m_csUpgradeStat(_T(""))
	, m_lUpgradeHandle(0)
	, m_lServerID(-1)
	, m_lpUpgradeTimer(NULL)
	, m_bUpgrade(FALSE)
{
	//{{AFX_DATA_INIT(CDlgUpdate)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgUpdate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgUpdate)
	DDX_Control(pDX, IDC_COMBO_ENVIRONMENT, m_comboEnvironment);
	DDX_Control(pDX, IDC_PROGRESS_UPGRADE, m_progressUpgrade);
	DDX_Text(pDX, IDC_EDIT_UPGRADE_FILE, m_csUpgradeFile);
	DDX_Text(pDX, IDC_STATIC_UPGRADE, m_csUpgradeStat);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgUpdate, CDialog)
	//{{AFX_MSG_MAP(CDlgUpdate)
	ON_BN_CLICKED(IDC_BTN_SET_ENVIRO, OnBtnSetEnviro)
	ON_BN_CLICKED(IDC_BTN_BROWSE_FILE, OnBtnBrowseFile)
	ON_BN_CLICKED(IDC_BTN_UPGRADE_EXIT, OnBtnUpgradeExit)
	ON_BN_CLICKED(IDC_BTN_UPGRADE, OnBtnUpgrade)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgUpdate message handlers

/*************************************************
函数名:    	OnBtnSetEnviro
函数描述:	设置网络环境
输入参数:   
输出参数:   	
返回值:	   
*************************************************/
void CDlgUpdate::OnBtnSetEnviro() 
{
	if (!NET_DVR_SetNetworkEnvironment(m_comboEnvironment.GetCurSel()))
	{
		MessageBox("设置网络环境失败");
	}

	
}

/*************************************************
函数名:    	OnInitDialog
函数描述:	初始化对话框
输入参数:   
输出参数:   	
返回值:	   
*************************************************/
BOOL CDlgUpdate::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_csUpgradeFile.Format("c:\\digicap");
	UpdateData(FALSE);
	m_bUpgrade = FALSE;
	m_progressUpgrade.SetRange(0,100);
	m_progressUpgrade.SetPos(0);
	m_progressUpgrade.ShowWindow(SW_HIDE);
	m_comboEnvironment.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*************************************************
函数名:    	OnBtnBrowseFile
函数描述:	浏览本地文件
输入参数:   
输出参数:   	
返回值:	   
*************************************************/
void CDlgUpdate::OnBtnBrowseFile() 
{
	CFileDialog FileDlg(TRUE,NULL,"digicap",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"All Files(*.*)|*.*||");
	if(IDOK == FileDlg.DoModal())
	{
		m_csUpgradeFile = FileDlg.GetPathName();
		UpdateData(FALSE);
	}
	
}

/*************************************************
函数名:    	OnBtnUpgradeExit
函数描述:	退出
输入参数:   
输出参数:   	
返回值:	   
*************************************************/
void CDlgUpdate::OnBtnUpgradeExit() 
{
	if (m_lpUpgradeTimer)
	{
		KillTimer(UPGRADE_TIMER);
	}
	CDialog::OnCancel();
	
}

/*************************************************
函数名:    	OnBtnUpgrade
函数描述:	升级
输入参数:   
输出参数:   	
返回值:	   
*************************************************/
void CDlgUpdate::OnBtnUpgrade() 
{
	LONG lLoginID = g_pMainDlg->m_struDeviceInfo.lLoginID;
	if(lLoginID == -1)
	{
		MessageBox("请先注册");
	}

	UpdateData(TRUE);
	char m_szFileName[256]={0};
	strcpy(m_szFileName,m_csUpgradeFile);
	CFile cFile;
	char szLan[128] = {0};
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

    if(IDYES != MessageBox("确定要升级设备吗？","Warning",MB_YESNO))
	{
		return;
	}

    m_lUpgradeHandle = NET_DVR_Upgrade(lLoginID,m_szFileName);
	if(m_lUpgradeHandle == -1)
	{
          MessageBox("升级失败");
	      return;

	}

	GetDlgItem(IDC_STATIC_UPGRADE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BTN_UPGRADE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_UPGRADE_EXIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_BROWSE_FILE)->EnableWindow(FALSE);
	m_progressUpgrade.SetPos(0);
	m_progressUpgrade.ShowWindow(SW_SHOW);

	m_csUpgradeStat = "状态：正在升级服务器，请等待......";
	m_bUpgrade = TRUE;
    
	m_lpUpgradeTimer = SetTimer(UPGRADE_TIMER,500,NULL);
	UpdateData(FALSE);
	

}

/*************************************************
函数名:    	OnTimer
函数描述:	定时器函数，获取升级状态
输入参数:   
输出参数:   	
返回值:	   
*************************************************/
void CDlgUpdate::OnTimer(UINT_PTR nIDEvent) 
{
	
	char szLan[128] = {0};
	if (nIDEvent == UPGRADE_TIMER)
	{
		if (m_bUpgrade)
		{
			int UpgradeStatic = NET_DVR_GetUpgradeState(m_lUpgradeHandle);
			int iPos = NET_DVR_GetUpgradeProgress(m_lUpgradeHandle);
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
				switch (UpgradeStatic)
				{
				case -1:
					g_StringLanType(szLan, "升级失败", "Upgrade failed");
					AfxMessageBox(szLan);			
					break;
				case 1:
					g_StringLanType(szLan, "状态：升级设备成功", "Status:upgrade successfully");
					m_csUpgradeStat.Format(szLan);
					m_progressUpgrade.SetPos(100);
					break;			
				case 3:
					g_StringLanType(szLan, "状态：升级设备失败", "Status:upgrade failed");
					m_csUpgradeStat.Format(szLan);			
					break;
				case 4:
					g_StringLanType(szLan, "状态：网络断开,状态未知", "Status:Network disconnect, status unknown");
					m_csUpgradeStat.Format(szLan);					
					break;
				case 5:
					g_StringLanType(szLan, "状态：升级文件语言版本不匹配", "Status:Upgrade file language mismatch");
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
				NET_DVR_CloseUpgradeHandle(m_lUpgradeHandle);
			}
		}		
	}
	CDialog::OnTimer(nIDEvent);
}
