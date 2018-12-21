/*******************************************************
Copyright 2008-2011 Hikvision Digital Technology Co., Ltd. 
文  件：	VoiceDlg.cpp
开发单位：	杭州海康威视
编  写：	shizhiping
日  期：	2009.5
描  述：	语音对讲转发对话框
修  改：	
********************************************************/

#include "stdafx.h"
#include "Voice.h"
#include "VoiceDlg.h"
//#include "HCNetSDK.h"

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
// CVoiceDlg dialog

CVoiceDlg::CVoiceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVoiceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVoiceDlg)
	m_nDevPort = 8000;
	m_csUser = _T("admin");
	m_csPWD = _T("12345");
	//}}AFX_DATA_INIT

	m_bIsLogin = FALSE;
//	m_lUserID = -1;
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVoiceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVoiceDlg)
	DDX_Control(pDX, IDC_IPADDRESS_DEV, m_ctrlDevIp);
	DDX_Control(pDX, IDC_TAB_VOICE, m_ctrlTab);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nDevPort);
	DDX_Text(pDX, IDC_EDIT_USER, m_csUser);
	DDX_Text(pDX, IDC_EDIT_PWD, m_csPWD);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVoiceDlg, CDialog)
	//{{AFX_MSG_MAP(CVoiceDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_VOICE, OnSelchangeTabVoice)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, OnButtonLogin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVoiceDlg message handlers

BOOL CVoiceDlg::OnInitDialog()
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
 
    //默认IP
	m_ctrlDevIp.SetAddress(172,7,94,6);
 
	//属性页
	m_ctrlTab.InsertItem(0,"语音对讲");
	m_VoiceTalk.Create(IDD_DIALOG_VOICE_TALK,&m_ctrlTab);
	m_ctrlTab.InsertItem(1,"语音转发");
	m_TalkMR.Create(IDD_DIALOG_TALK_MR,&m_ctrlTab);


	CRect rc;
	m_ctrlTab.GetWindowRect(&rc);
	
    m_VoiceTalk.MoveWindow(1,20,rc.Width()-4,rc.Height()-25);
	m_TalkMR.MoveWindow(1,20,rc.Width()-4,rc.Height()-25);

	m_VoiceTalk.ShowWindow(SW_SHOW);
	m_ctrlTab.SetCurSel(0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVoiceDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CVoiceDlg::OnPaint() 
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
HCURSOR CVoiceDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*************************************************
函数名:    	OnSelchangeTabVoice
函数描述:	属性页切换
输入参数:   
输出参数:   		
返回值:	   
*************************************************/
void CVoiceDlg::OnSelchangeTabVoice(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int CurSel;
	CurSel = m_ctrlTab.GetCurSel();
	switch (CurSel)
	{
	case 0:
		m_VoiceTalk.ShowWindow(SW_SHOW);
		m_TalkMR.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_VoiceTalk.ShowWindow(SW_HIDE);
		m_TalkMR.ShowWindow(SW_SHOW);
	//	m_TalkMR.CreateChannelTree()
		break;
	default:
		break;
	}
	*pResult = 0;
}

/*************************************************
函数名:    	OnButtonLogin
函数描述:	注册/注销 按钮
输入参数:   
输出参数:   		
返回值:	   
*************************************************/
void CVoiceDlg::OnButtonLogin() 
{
	if(!m_bIsLogin)    //login
	{
		if(!DoLogin())
			return;
		GetDevWorkState();   //Get chan status		
		GetDlgItem(IDC_BUTTON_LOGIN)->SetWindowText("Logout");
		m_bIsLogin = TRUE;

		m_VoiceTalk.SetChanRadioState(m_DeviceInfo.iVoiceChanNum,m_DeviceInfo.AudioChanStatus);
		m_TalkMR.CreateChannelTree(m_DeviceInfo.iVoiceChanNum,m_DeviceInfo.AudioChanStatus);
		//set the property pages
	}
	else      //logout
	{

		//close voice fisrt
		if(m_VoiceTalk.m_lVoiceHandle>=0 || m_TalkMR.m_bIsTalkMR)
		{
			MessageBox("Stop Voice first!");
			return;
		}
        NET_DVR_Logout_V30(m_DeviceInfo.lLoginID); 
		GetDlgItem(IDC_BUTTON_LOGIN)->SetWindowText("Login");
		m_DeviceInfo.lLoginID = -1;
		m_bIsLogin = FALSE;
	}
	
}

/*************************************************
函数名:    	DoLogin
函数描述:	向设备注册
输入参数:   
输出参数:   		
返回值:	   
*************************************************/
BOOL CVoiceDlg::DoLogin()
{
	UpdateData(TRUE);
	CString DeviceIp;
	BYTE nField0,nField1,nField2,nField3; 
	m_ctrlDevIp.GetAddress(nField0,nField1,nField2,nField3);
	DeviceIp.Format("%d.%d.%d.%d",nField0,nField1,nField2,nField3);

	NET_DVR_DEVICEINFO_V30 DeviceInfoTmp;
	memset(&DeviceInfoTmp,0,sizeof(NET_DVR_DEVICEINFO_V30));

	LONG m_lUserID = NET_DVR_Login_V30(DeviceIp.GetBuffer(DeviceIp.GetLength()),m_nDevPort, \
		m_csUser.GetBuffer(m_csUser.GetLength()),m_csPWD.GetBuffer(m_csPWD.GetLength()),&DeviceInfoTmp);
	if(m_lUserID == -1)
	{
		MessageBox("Login to Device failed!\n");
		return FALSE;
	}
    m_DeviceInfo.lLoginID = m_lUserID;
	m_DeviceInfo.iVoiceChanNum = DeviceInfoTmp.byAudioChanNum;  //voice chan num
   return TRUE;
}


/*************************************************
函数名:    	GetDevWorkState
函数描述:	获取设备工作状态（语音通道状态）
输入参数:   
输出参数:   		
返回值:	   
*************************************************/
BOOL CVoiceDlg::GetDevWorkState()
{
	NET_DVR_WORKSTATE_V30 DeviceState;
	memset(&DeviceState,0,sizeof(NET_DVR_WORKSTATE_V30));
	if(!NET_DVR_GetDVRWorkState_V30(m_DeviceInfo.lLoginID,&DeviceState))
	{
		MessageBox("Get device work state failed");
		return FALSE; 
	}
    
	memcpy(m_DeviceInfo.AudioChanStatus,DeviceState.byAudioChanStatus,MAX_AUDIO_V30*sizeof(BYTE));
     return TRUE;
}

