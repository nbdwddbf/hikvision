// configDlg.cpp : implementation file

/**********************************************************
FileName:    configDlg.cpp
Description: 创建主对话框。      
Date:        
Note: 		 the global Macro definition and structure is in "GeneralDef.h", global variable and function is in "Config.cpp"
Modification History:      
<version>    <time>         <desc>

***********************************************************/

#include "stdafx.h"
#include "config.h"
#include "configDlg.h"
#include "GeneralDef.h"

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
// CConfigDlg dialog

CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigDlg)
	m_iDevPort = 8000;
	m_csPassword = _T("12345");
	m_csUserName = _T("admin");
	m_bIsLogin = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigDlg)
	DDX_Control(pDX, IDC_DEV_IPADDRESS, m_ipctrlDevIP);
	DDX_Control(pDX, IDC_TAB_CONFIG_DLG, m_tabConfigDlg);
	DDX_Text(pDX, IDC_EDIT_DEV_PORT, m_iDevPort);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csPassword);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_csUserName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CONFIG_DLG, OnSelchangeTabConfigDlg)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, OnButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_SHUTDOWN, OnButtonShutdown)
	ON_BN_CLICKED(IDC_BUTTON_REBOOT, OnButtonReboot)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, OnButtonRefreshCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg message handlers

/*********************************************************
Function:	OnInitDialog
Desc:		初始化对话框。Initialize the dialog。
Input:	
Output:	
Return:	
**********************************************************/
BOOL CConfigDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here

	m_ipctrlDevIP.SetAddress(192,0,0,64);//初始化ip地址控件栏的ip地址

	/**********************************初始化tab控件 begin*****************************************/
	m_tabConfigDlg.InsertItem(0,"设备参数配置");
	m_tabConfigDlg.InsertItem(1,"通道参数配置");
	m_tabConfigDlg.InsertItem(2,"串口参数配置");
	m_tabConfigDlg.InsertItem(3,"报警参数配置");
	m_tabConfigDlg.InsertItem(4,"用户配置");
	m_tabConfigDlg.InsertItem(5,"异常信息");

    m_DlgDeviceCfg.Create(IDD_DIALOG_DEVICE_CFG,&m_tabConfigDlg);
	m_DlgChanCfg.Create(IDD_DIALOG_CHAN_CFG,&m_tabConfigDlg);
	m_DlgSerialCfg.Create(IDD_DIALOG_SERIAL_CFG,&m_tabConfigDlg);
	m_DlgAlarmCfg.Create(IDD_DIALOG_ALARM_CFG,&m_tabConfigDlg);
	m_DlgUserCfg.Create(IDD_DIALOG_USER_CFG,&m_tabConfigDlg);
	m_DlgExceptionCfg.Create(IDD_DIALOG_EXCEPTION_CFG,&m_tabConfigDlg);

	
	CRect rc;
	m_tabConfigDlg.GetWindowRect(&rc);
	
    m_DlgDeviceCfg.MoveWindow(1,20,rc.Width()-5,rc.Height()-25);
	m_DlgChanCfg.MoveWindow(1,20,rc.Width()-5,rc.Height()-25);
	m_DlgSerialCfg.MoveWindow(1,20,rc.Width()-5,rc.Height()-25);
	m_DlgAlarmCfg.MoveWindow(1,20,rc.Width()-5,rc.Height()-25);
	m_DlgUserCfg.MoveWindow(1,20,rc.Width()-5,rc.Height()-25);
	m_DlgExceptionCfg.MoveWindow(1,20,rc.Width()-5,rc.Height()-25);
    m_DlgDeviceCfg.ShowWindow(SW_SHOW);
	m_tabConfigDlg.SetCurSel(0);
	/**********************************初始化tab控件 end******************************************/
    
	//在注册到设备之前让各个对话框非使能，注册成功后使之使能。
	//m_tabConfigDlg.EnableWindow(FALSE);//或者只让tab控件非使能就可以了，省去下面的六句。
	m_DlgDeviceCfg.EnableWindow(FALSE);
	m_DlgChanCfg.EnableWindow(FALSE);
	m_DlgSerialCfg.EnableWindow(FALSE);
	m_DlgAlarmCfg.EnableWindow(FALSE);
	m_DlgUserCfg.EnableWindow(FALSE);
	m_DlgExceptionCfg.EnableWindow(FALSE);
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CConfigDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CConfigDlg::OnPaint() 
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
HCURSOR CConfigDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*********************************************************
Function:	OnSelchangeTabConfigDlg
Desc:		tab页选择的消息响应函数
Input:	
Output:	
Return:	
**********************************************************/
void CConfigDlg::OnSelchangeTabConfigDlg(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int iCurSel = m_tabConfigDlg.GetCurSel();
	switch(iCurSel)
	{
	case 0:
		m_DlgDeviceCfg.ShowWindow(SW_SHOW);
		//切换tab页时对此页信息进行更新。
		//m_DlgDeviceCfg.GetDeviceCfg();
	    //m_DlgDeviceCfg.GetNetCfg();
		m_DlgChanCfg.ShowWindow(SW_HIDE);
		m_DlgSerialCfg.ShowWindow(SW_HIDE);
		m_DlgAlarmCfg.ShowWindow(SW_HIDE);
		m_DlgUserCfg.ShowWindow(SW_HIDE);
		m_DlgExceptionCfg.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_DlgDeviceCfg.ShowWindow(SW_HIDE);
		m_DlgChanCfg.ShowWindow(SW_SHOW);
		//切换tab页时对此页信息进行更新。
		//m_DlgChanCfg.CurCfgUpdate();
		m_DlgSerialCfg.ShowWindow(SW_HIDE);
		m_DlgAlarmCfg.ShowWindow(SW_HIDE);
		m_DlgUserCfg.ShowWindow(SW_HIDE);
		m_DlgExceptionCfg.ShowWindow(SW_HIDE);
		break;
	case 2:
		m_DlgDeviceCfg.ShowWindow(SW_HIDE);
		m_DlgChanCfg.ShowWindow(SW_HIDE);
		m_DlgSerialCfg.ShowWindow(SW_SHOW);
		//切换tab页时对此页信息进行更新。
		//m_DlgSerialCfg.GetRS232Cfg();
	    //m_DlgSerialCfg.GetRS485Cfg();
		m_DlgAlarmCfg.ShowWindow(SW_HIDE);
		m_DlgUserCfg.ShowWindow(SW_HIDE);
		m_DlgExceptionCfg.ShowWindow(SW_HIDE);
		break;
	case 3:
		m_DlgDeviceCfg.ShowWindow(SW_HIDE);
		m_DlgChanCfg.ShowWindow(SW_HIDE);
		m_DlgSerialCfg.ShowWindow(SW_HIDE);
		m_DlgAlarmCfg.ShowWindow(SW_SHOW);
		//切换tab页时对此页信息进行更新。
		//m_DlgAlarmCfg.CurCfgUpdate();
		m_DlgUserCfg.ShowWindow(SW_HIDE);
		m_DlgExceptionCfg.ShowWindow(SW_HIDE);
		break;
	case 4:
		m_DlgDeviceCfg.ShowWindow(SW_HIDE);
		m_DlgChanCfg.ShowWindow(SW_HIDE);
		m_DlgSerialCfg.ShowWindow(SW_HIDE);
		m_DlgAlarmCfg.ShowWindow(SW_HIDE);
		m_DlgUserCfg.ShowWindow(SW_SHOW);
		//切换tab页时对此页信息进行更新。
		//m_DlgUserCfg.CurCfgUpdate();
		m_DlgExceptionCfg.ShowWindow(SW_HIDE);
		break;
	case 5:
		m_DlgDeviceCfg.ShowWindow(SW_HIDE);
		m_DlgChanCfg.ShowWindow(SW_HIDE);
		m_DlgSerialCfg.ShowWindow(SW_HIDE);
		m_DlgAlarmCfg.ShowWindow(SW_HIDE);
		m_DlgUserCfg.ShowWindow(SW_HIDE);
		m_DlgExceptionCfg.ShowWindow(SW_SHOW);
		//切换tab页时对此页信息进行更新。
		//m_DlgExceptionCfg.CurCfgUpdate();
		break;

	default:
		break;
	}
	*pResult = 0;
}
/*********************************************************
Function:	OnButtonLogin
Desc:		判断是否已经注册，注册成功将按钮的状态改为“注销”
Input:	
Output:	
Return:	
**********************************************************/
void CConfigDlg::OnButtonLogin() 
{
	if(!m_bIsLogin)    //login
	{
		if(!DoLogin())
		{
			return;
		}
		GetDlgItem(IDC_BUTTON_LOGIN)->SetWindowText("注销");
		m_bIsLogin = TRUE;		
		
	    //注册成功后，让几个配置对话框使能。
		m_DlgDeviceCfg.EnableWindow(TRUE);
		m_DlgChanCfg.EnableWindow(TRUE);
		m_DlgSerialCfg.EnableWindow(TRUE);
		m_DlgAlarmCfg.EnableWindow(TRUE);
		m_DlgUserCfg.EnableWindow(TRUE);
	    m_DlgExceptionCfg.EnableWindow(TRUE);
	}
	else      //logout
	{
		NET_DVR_Logout_V30(g_lUserID);

		//给全局结构体g_struDeviceInfo[0]重新初始化
		STRU_DEVICE_INFO Tem_g_struDeviceInfo;
		memcpy(&g_struDeviceInfo[0],&Tem_g_struDeviceInfo,sizeof(STRU_DEVICE_INFO));
		
		GetDlgItem(IDC_BUTTON_LOGIN)->SetWindowText("注册");
		g_lUserID = -1;
		m_bIsLogin = FALSE;

		//注销成功后让六个对话框非使能。
		m_DlgDeviceCfg.EnableWindow(FALSE);
		m_DlgChanCfg.EnableWindow(FALSE);
		m_DlgSerialCfg.EnableWindow(FALSE);
		m_DlgAlarmCfg.EnableWindow(FALSE);
		m_DlgUserCfg.EnableWindow(FALSE);
	    m_DlgExceptionCfg.EnableWindow(FALSE);
	}
}

/*********************************************************
Function:	DoLogin
Desc:		注册过程，注册成功则读取设备的各种配置参数信息。
Input:	
Output:	
Return:	
**********************************************************/
BOOL CConfigDlg::DoLogin()
{
	UpdateData(TRUE);
	g_lUserID=-1;
	
	CString DeviceIp;
	//BYTE nField0,nField1,nField2,nField3; 
	//m_ctrlDevIp.GetAddress(nField0,nField1,nField2,nField3);//GetAddress是IP地址控件对应关联变量CCIPAddressCtrl的一个使用函数。可以查看msdn。
	//DeviceIp.Format("%d.%d.%d.%d",nField0,nField1,nField2,nField3);//DeviceIP成为了“172.7.94.6”类型的字符串。
	m_ipctrlDevIP.GetWindowText(DeviceIp);	
	
	memset(&DeviceInfoTmp,0,sizeof(NET_DVR_DEVICEINFO_V30));
	
	//开始注册(手动填入IP，端口，用户名，密码。)
	g_lUserID =  NET_DVR_Login_V30(DeviceIp.GetBuffer(DeviceIp.GetLength()),m_iDevPort, \
		m_csUserName.GetBuffer(m_csUserName.GetLength()),m_csPassword.GetBuffer(m_csPassword.GetLength()),&DeviceInfoTmp);
	
	if(g_lUserID == -1)
	{
		MessageBox("注册到设备失败!\n");
		return FALSE;
	}
	else
	{
		MessageBox("成功注册到设备!\n");
	}
	
	g_struDeviceInfo[0].iDeviceChanNum = DeviceInfoTmp.byChanNum;//获取设备的模拟通道数
	g_struDeviceInfo[0].iStartChan = DeviceInfoTmp.byStartChan;//起始通道数，一般是1.除非9000设备可以禁掉设备。
	g_struDeviceInfo[0].lLoginID = g_lUserID;//登陆ID
    g_struDeviceInfo[0].iAlarmOutNum = DeviceInfoTmp.byAlarmOutPortNum;//报警输出个数
	g_struDeviceInfo[0].iAlarmInNum = DeviceInfoTmp.byAlarmInPortNum;
	g_struDeviceInfo[0].iAudioNum = DeviceInfoTmp.byAudioChanNum;
	g_struDeviceInfo[0].iIPChanNum = DeviceInfoTmp.byIPChanNum;
	sprintf(g_struDeviceInfo[0].chLoginUserName, "%s", m_csUserName.GetBuffer(0));
	
	
	if(DoGetDeviceResoureCfg(0))//获得设备的通道使能信息。8000的通道全使能，9000的要做判断。NET_DVR_IPALARMININFO结构体。
	{
		DoGetIPAlarmInCfg(0);//获得ip设备的报警输入输出通道信息。NET_DVR_IPALARMINCFG和NET_DVR_IPALARMOUTINFO结构体。
		DoGetIPAlarmOutCfg(0);
	}
	
	//获取设备的各种配置信息，并显示到对话框上。
	m_DlgDeviceCfg.GetDeviceCfg();
	m_DlgDeviceCfg.GetNetCfg();
	m_DlgChanCfg.CurCfgUpdate();
	m_DlgSerialCfg.GetRS232Cfg();
	m_DlgSerialCfg.GetRS485Cfg();
	m_DlgAlarmCfg.CurCfgUpdate();
	m_DlgUserCfg.CurCfgUpdate();
	m_DlgExceptionCfg.CurCfgUpdate();
	
	return TRUE;
}

/*********************************************************
Function:	OnButtonShutdown
Desc:		关闭设备
Input:	
Output:	
Return:	
**********************************************************/
void CConfigDlg::OnButtonShutdown() 
{
	if (g_lUserID < 0)
	{
		MessageBox("请先登录设备！");
		return;
	}

	if(IDOK == MessageBox("确定要关闭设备?","Warning",MB_OKCANCEL))//让用户选择是不是要关机。
	{
        
        BOOL SuccessShutDown;
		SuccessShutDown=NET_DVR_ShutDownDVR(g_lUserID);
		if(SuccessShutDown)
		{
			MessageBox("关机成功!","注意");
		}
		else
		{
			MessageBox("关机失败","warning");
			// CString err;
			//err.Format("关机失败,错误代码%d",NET_DVR_GetLastError());//以错误码的形式显示错误			
			//err.Format("关机失败,%s",NET_DVR_GetErrorMsg());//以错误描述信息（英文）来描述错误。
			//MessageBox(err,"warning");
		}
	}	
}

/*********************************************************
Function:	OnButtonReboot
Desc:		重启设备
Input:	
Output:	
Return:	
**********************************************************/
void CConfigDlg::OnButtonReboot() 
{
	if (g_lUserID < 0)
	{
		MessageBox("请先登录设备！");
		return;
	}

	if(IDOK == MessageBox("确定要重启设备?","Warning",MB_OKCANCEL))//让用户选择是不是要重启。
	{
        BOOL SuccessReboot;
		SuccessReboot=NET_DVR_RebootDVR(g_lUserID);
		if(SuccessReboot)
		{
			MessageBox("重启成功!请稍候。","注意");
		}
		else
		{
			MessageBox("重启失败");
		}
	}	
}

/*********************************************************
Function:	OnCancel
Desc:		退出主对话框时，提示是否退出程序，并在没有注销的情况下注销。
Input:	
Output:	
Return:	
**********************************************************/
void CConfigDlg::OnCancel()
{
	char szLan[128] = {0};
	g_StringLanType(szLan, "确定要退出程序?", "Sure to exit?");
	
	if (IDOK != MessageBox(szLan,"Warning",IDOK))
	{
		return;
	}
	if (g_lUserID >= 0)
	{
		NET_DVR_Logout_V30(g_lUserID);
	}
	CDialog::OnCancel();
}

/*********************************************************
Function:	OnButtonRefreshCfg
Desc:		刷新设备的参数信息
Input:	
Output:	
Return:	
**********************************************************/
void CConfigDlg::OnButtonRefreshCfg() 
{
	if (g_lUserID < 0)
	{
		MessageBox("请先登录设备！");
		return;
	}
	
    //刷新当前页面的配置信息
	int iCurSel = m_tabConfigDlg.GetCurSel();
	switch(iCurSel)
	{
	case 0:
		m_DlgDeviceCfg.GetDeviceCfg();
		m_DlgDeviceCfg.GetNetCfg();
		break;
	case 1:
		m_DlgChanCfg.CurCfgUpdate();
		break;	
	case 2:
		m_DlgSerialCfg.GetRS232Cfg();
		m_DlgSerialCfg.GetRS485Cfg();
		break;
	case 3:
		m_DlgAlarmCfg.CurCfgUpdate();
		break;
	case 4:
		m_DlgUserCfg.CurCfgUpdate();
		break;
	case 5:
		m_DlgExceptionCfg.CurCfgUpdate();
		break;		
	default:
		break;
	}
}


