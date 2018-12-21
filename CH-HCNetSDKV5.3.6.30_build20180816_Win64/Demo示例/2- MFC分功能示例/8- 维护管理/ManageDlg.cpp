/*******************************************************
Copyright 2008-2011 Hikvision Digital Technology Co., Ltd. 
文  件：	ManageDlg.cpp
开发单位：	杭州海康威视
编  写：	shizhiping
日  期：	2009.5
描  述：	设备管理主对话框
修  改：	
********************************************************/
#include "stdafx.h"
#include "Manage.h"
#include "ManageDlg.h"
#include "DlgCheckTime.h"
#include "DlgUpdate.h"
#include "DlgFormatHD.h"
#include "DlgLogSearch.h"
#include "DlgDeviceState.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManageDlg dialog

CManageDlg::CManageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CManageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CManageDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_nDevPort = 8000;
	m_csUser = _T("admin");
	m_csPWD = _T("12345");
	m_bIsLogin = FALSE;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CManageDlg)
	DDX_Control(pDX, IDC_TAB1, m_ctrlTab);
	DDX_Control(pDX, IDC_IPADDRESS_DEV, m_ctrlDevIp);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nDevPort);
	DDX_Text(pDX, IDC_EDIT_USER, m_csUser);
	DDX_Text(pDX, IDC_EDIT_PWD, m_csPWD);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CManageDlg, CDialog)
	//{{AFX_MSG_MAP(CManageDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CHECK_TIME, OnButtonCheckTime)
	ON_BN_CLICKED(IDC_BUTTON_DEFAULT_CFG, OnButtonDefaultCfg)
	ON_BN_CLICKED(IDC_BUTTON_HD_FORMAT, OnButtonHdFormat)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, OnButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_REBOOT, OnButtonReboot)
	ON_BN_CLICKED(IDC_BUTTON_SHUTDOWN, OnButtonShutdown)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManageDlg message handlers

BOOL CManageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//默认IP
	m_ctrlDevIp.SetAddress(172,7,96,7);

	//tab
	m_ctrlTab.InsertItem(0,"日志查询");
	m_DlgLogSearch.Create(IDD_DIALOG_LOG_SEARCH,&m_ctrlTab);
	m_ctrlTab.InsertItem(1,"设备状态");
	m_DlgDeviceState.Create(IDD_DIALOG_DEVICE_STATE,&m_ctrlTab);

	CRect rc;
	m_ctrlTab.GetWindowRect(&rc);
	
    m_DlgLogSearch.MoveWindow(1,20,rc.Width()-4,rc.Height()-25);
	m_DlgDeviceState.MoveWindow(1,20,rc.Width()-4,rc.Height()-25);
	
	m_DlgLogSearch.ShowWindow(SW_SHOW);
	m_ctrlTab.SetCurSel(0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CManageDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CManageDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CManageDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*************************************************
函数名:    	OnButtonCheckTime
函数描述:	校时按钮
输入参数:   
输出参数:   	
返回值:	   
*************************************************/
void CManageDlg::OnButtonCheckTime() 
{
	CDlgCheckTime Dlg;
	Dlg.DoModal();
	
}

/*************************************************
函数名:    	OnButtonDefaultCfg
函数描述:	恢复默认参数按钮
输入参数:   
输出参数:   	
返回值:	   
*************************************************/
void CManageDlg::OnButtonDefaultCfg() 
{
	LONG lLoginID = m_struDeviceInfo.lLoginID;
	if(lLoginID == -1)
	{
		MessageBox("设备未登录");
		return;
	}
	if(IDOK == MessageBox("确定要恢复默认参数？","Warning",MB_OKCANCEL))
	{
        if(!NET_DVR_RestoreConfig(lLoginID))
		{
			MessageBox("恢复默认参数失败");
			return;
		}
	}
	
}

/*************************************************
函数名:    	OnButtonHdFormat
函数描述:	格式化硬盘按钮
输入参数:   
输出参数:   	
返回值:	   
*************************************************/
void CManageDlg::OnButtonHdFormat() 
{
	LONG lLoginID = m_struDeviceInfo.lLoginID;
	if(lLoginID == -1)
	{
		MessageBox("设备未登录");
		return;
	}
	CDlgFormatHD Dlg;
	Dlg.m_dwDiskNum = m_struDeviceInfo.byDiskNum;
	Dlg.DoModal();
	
}

/*************************************************
函数名:    	OnButtonLogin
函数描述:	注册/注销按钮
输入参数:   
输出参数:   	
返回值:	   
*************************************************/
void CManageDlg::OnButtonLogin() 
{
	
	if(!m_bIsLogin)    //login
	{
		if(!DoLogin())
			return;
		DoGetDeviceResoureCfg();
		GetDlgItem(IDC_BUTTON_LOGIN)->SetWindowText("Logout");
		m_DlgDeviceState.UpdateDeviceInfo();
		m_bIsLogin = TRUE;
		
	}
	else      //logout
	{
		
		
        NET_DVR_Logout_V30(m_struDeviceInfo.lLoginID); 
		GetDlgItem(IDC_BUTTON_LOGIN)->SetWindowText("Login");
		m_bIsLogin = FALSE;
	}
}

/*************************************************
函数名:    	OnButtonReboot
函数描述:	重启按钮
输入参数:   
输出参数:   	
返回值:	   
*************************************************/
void CManageDlg::OnButtonReboot() 
{
	LONG lLoginID = g_pMainDlg->m_struDeviceInfo.lLoginID;
	if(lLoginID == -1)
	{
		MessageBox("设备未登录");
		return;
	}
	if(IDOK == MessageBox("确定要重启设备？","Warning",MB_OKCANCEL))
	{
		if(!NET_DVR_RebootDVR(lLoginID))
		{
			MessageBox("设备重启失败");
		    return;
		}
	}
	
}

/*************************************************
函数名:    	OnButtonShutdown
函数描述:	关机按钮
输入参数:   
输出参数:   	
返回值:	   
*************************************************/
void CManageDlg::OnButtonShutdown() 
{
	LONG lLoginID = g_pMainDlg->m_struDeviceInfo.lLoginID;
	if(lLoginID == -1)
	{
		MessageBox("设备未登录");
		return;
	}
	if(IDOK == MessageBox("确定要关闭设备？","Warning",MB_OKCANCEL))
	{
		if(!NET_DVR_ShutDownDVR(lLoginID))
		{
			MessageBox("设备关闭失败");
			return;
		}
	}
	
}

/*************************************************
函数名:    	OnButtonUpdate
函数描述:	升级按钮
输入参数:   
输出参数:   	
返回值:	   
*************************************************/
void CManageDlg::OnButtonUpdate() 
{
	CDlgUpdate Dlg;
	Dlg.DoModal();
	
}

/*************************************************
函数名:    	OnSelchangeTab1
函数描述:	属性页切换
输入参数:   
输出参数:   	
返回值:	   
*************************************************/
void CManageDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int iSelIndex = m_ctrlTab.GetCurSel();
	switch(iSelIndex)
	{
	case 0:
		m_DlgLogSearch.ShowWindow(SW_SHOW);
		m_DlgDeviceState.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_DlgLogSearch.ShowWindow(SW_HIDE);
		m_DlgDeviceState.ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}
	
	*pResult = 0;
}

/*************************************************
函数名:    	DoLogin
函数描述:	向设备注册
输入参数:   
输出参数:   	
返回值:	   
*************************************************/
BOOL CManageDlg::DoLogin()
{
    UpdateData(TRUE);
	CString DeviceIp;
	BYTE nField0,nField1,nField2,nField3; 
	m_ctrlDevIp.GetAddress(nField0,nField1,nField2,nField3);
	DeviceIp.Format("%d.%d.%d.%d",nField0,nField1,nField2,nField3);
	
	NET_DVR_DEVICEINFO_V30 DeviceInfoTmp;
	memset(&DeviceInfoTmp,0,sizeof(NET_DVR_DEVICEINFO_V30));
	
	LONG lLoginID = NET_DVR_Login_V30(DeviceIp.GetBuffer(DeviceIp.GetLength()),m_nDevPort, \
		m_csUser.GetBuffer(m_csUser.GetLength()),m_csPWD.GetBuffer(m_csPWD.GetLength()),&DeviceInfoTmp);
	if(lLoginID == -1)
	{
		MessageBox("Login to Device failed!\n");
		return FALSE;
	}
    m_struDeviceInfo.lLoginID = lLoginID;
	m_struDeviceInfo.iDeviceChanNum = DeviceInfoTmp.byChanNum;
    m_struDeviceInfo.iIPChanNum = DeviceInfoTmp.byIPChanNum;
    m_struDeviceInfo.iStartChan  = DeviceInfoTmp.byStartChan;
    m_struDeviceInfo.byDiskNum = DeviceInfoTmp.byDiskNum;
    m_struDeviceInfo.byDVRType = DeviceInfoTmp.byDVRType;
	sprintf(m_struDeviceInfo.sSerialNumber,"%s",DeviceInfoTmp.sSerialNumber);
	sprintf(m_struDeviceInfo.chDevIP,"%s",DeviceIp.GetBuffer(DeviceIp.GetLength()));
	return TRUE;
}

/*************************************************
函数名:    	DoGetDeviceResoureCfg
函数描述:	获取设备通道资源
输入参数:   
输出参数:   	
返回值:	   
*************************************************/
void CManageDlg::DoGetDeviceResoureCfg()
{
    NET_DVR_IPPARACFG IpAccessCfg;
	memset(&IpAccessCfg,0,sizeof(IpAccessCfg));	
	DWORD  dwReturned;
	
	m_struDeviceInfo.bIPRet = NET_DVR_GetDVRConfig(m_struDeviceInfo.lLoginID,NET_DVR_GET_IPPARACFG,0,&IpAccessCfg,sizeof(NET_DVR_IPPARACFG),&dwReturned);
	
	int i;
    if(!m_struDeviceInfo.bIPRet)   //不支持ip接入,9000以下设备不支持禁用模拟通道
	{
		for(i=0; i<MAX_ANALOG_CHANNUM; i++)
		{
			if (i < m_struDeviceInfo.iDeviceChanNum)
			{
				sprintf(m_struDeviceInfo.struChanInfo[i].chChanName,"camera%d",i+m_struDeviceInfo.iStartChan);
				m_struDeviceInfo.struChanInfo[i].iChanIndex=i+m_struDeviceInfo.iStartChan;  //通道号
				m_struDeviceInfo.struChanInfo[i].bEnable = TRUE;
				
			}
			else
			{
				m_struDeviceInfo.struChanInfo[i].iChanIndex = -1;
				m_struDeviceInfo.struChanInfo[i].bEnable = FALSE;
				sprintf(m_struDeviceInfo.struChanInfo[i].chChanName, "");	
			}
		}
	}
	else        //支持IP接入，9000设备
	{
		for(i=0; i<MAX_ANALOG_CHANNUM; i++)  //模拟通道
		{
			if (i < m_struDeviceInfo.iDeviceChanNum)
			{
				sprintf(m_struDeviceInfo.struChanInfo[i].chChanName,"camera%d",i+m_struDeviceInfo.iStartChan);
				m_struDeviceInfo.struChanInfo[i].iChanIndex=i+m_struDeviceInfo.iStartChan;
				if(IpAccessCfg.byAnalogChanEnable[i])
				{
					m_struDeviceInfo.struChanInfo[i].bEnable = TRUE;
				}
				else
				{
					m_struDeviceInfo.struChanInfo[i].bEnable = FALSE;
				}
				
			}
			else//clear the state of other channel
			{
				m_struDeviceInfo.struChanInfo[i].iChanIndex = -1;
				m_struDeviceInfo.struChanInfo[i].bEnable = FALSE;
				sprintf(m_struDeviceInfo.struChanInfo[i].chChanName, "");	
			}		
		}
		
		//数字通道
		for(i=0; i<MAX_IP_CHANNEL; i++)
		{
			if(IpAccessCfg.struIPChanInfo[i].byEnable)  //ip通道在线
			{
				m_struDeviceInfo.struChanInfo[i+MAX_ANALOG_CHANNUM].bEnable = TRUE;
                m_struDeviceInfo.struChanInfo[i+MAX_ANALOG_CHANNUM].iChanIndex = IpAccessCfg.struIPChanInfo[i].byChannel;
				sprintf(m_struDeviceInfo.struChanInfo[i+MAX_ANALOG_CHANNUM].chChanName,"IP Camera %d",IpAccessCfg.struIPChanInfo[i].byChannel);
				
			}
			else
			{
				m_struDeviceInfo.struChanInfo[i+MAX_ANALOG_CHANNUM].bEnable = FALSE;
				m_struDeviceInfo.struChanInfo[i+MAX_ANALOG_CHANNUM].iChanIndex = -1;
			}
		}
		
		
	}
}
