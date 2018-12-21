// PlayBackDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PlayBack.h"
#include "PlayBackDlg.h"
#include "AddDevice.h"

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
// CPlayBackDlg dialog

CPlayBackDlg::CPlayBackDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlayBackDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlayBackDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
//	m_Playback.Construct("playback");
//	m_nCurDevCount = 0;
//	m_iCurDeviceIndex = -1;
	m_iCurChanIndex = -1;
	m_hCurDeviceItem = NULL;
	m_hCurChanItem = NULL;
	m_nDevPort = 8000;
	m_csUser = "admin";
	m_csPWD = "12345";
	m_bIsLogin = FALSE;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPlayBackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlayBackDlg)
	DDX_Control(pDX, IDC_TREE_CHAN, m_ctrlTreeChan);
	DDX_Control(pDX, IDC_TAB_PLAYBACK, m_ctrlTab);
	DDX_Control(pDX, IDC_IPADDRESS_DEV, m_ctrlDevIp);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nDevPort);
	DDX_Text(pDX, IDC_EDIT_USER, m_csUser);
	DDX_Text(pDX, IDC_EDIT_PWD, m_csPWD);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPlayBackDlg, CDialog)
	//{{AFX_MSG_MAP(CPlayBackDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_PLAYBACK, OnSelchangeTabPlayback)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, OnButtonLogin)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_CHAN, OnSelchangedTreeChan)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayBackDlg message handlers

BOOL CPlayBackDlg::OnInitDialog()
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
	

	m_ctrlDevIp.SetAddress(172,7,39,253);
	//初始化属性页
	// TODO: Add extra initialization here
	//属性页设置为WS_CHILD时时间控件打开会出问题，不知道为什么
// 	m_Playback.AddPage(&m_PageRemote);
// 	m_Playback.AddPage(&m_PageLocal);
//  m_Playback.Create(this,WS_CHILD|WS_VISIBLE);
//	MoveWindow(0,0,1024,768);
	m_ctrlTab.InsertItem(0,"远程回放");
	m_PageRemote.Create(IDD_PAGE_REMOTE,&m_ctrlTab);
	m_ctrlTab.InsertItem(1,"时间回放");
	m_PageTime.Create(IDD_PAGE_TIME,&m_ctrlTab);
//	m_ctrlTab.InsertItem(2,"本地回放");
//	m_PageLocal.Create(IDD_PAGE_LOCAL,&m_ctrlTab);
	
 	CRect rc;
 	m_ctrlTab.GetWindowRect(&rc);


    m_PageRemote.MoveWindow(1,20,rc.Width()-4,rc.Height()-25);
//	m_PageLocal.MoveWindow(1,20,rc.Width()-4,rc.Height()-25);
	m_PageTime.MoveWindow(1,20,rc.Width()-4,rc.Height()-25);
	m_PageRemote.ShowWindow(SW_SHOW);
//	m_PageLocal.ShowWindow(SW_SHOW);
	m_ctrlTab.SetCurSel(0);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPlayBackDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPlayBackDlg::OnPaint() 
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
HCURSOR CPlayBackDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPlayBackDlg::OnSelchangeTabPlayback(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int CurSel;
	CurSel = m_ctrlTab.GetCurSel();
	switch (CurSel)
	{
	case 0:
		m_PageRemote.ShowWindow(SW_SHOW);
		m_PageTime.ShowWindow(SW_HIDE);
//		m_PageLocal.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_PageRemote.ShowWindow(SW_HIDE);
		m_PageTime.ShowWindow(SW_SHOW);
//		m_PageLocal.ShowWindow(SW_HIDE);
		break;
	case 2:
		m_PageRemote.ShowWindow(SW_HIDE);
		m_PageTime.ShowWindow(SW_HIDE);
//		m_PageLocal.ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}
	*pResult = 0;
}

BOOL CPlayBackDlg::DoLogin()
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
		TRACE("NET_DVR_Login_V30 failed! Error code:%d\n",NET_DVR_GetLastError());
		return FALSE;
	}
    m_struDeviceInfo.lLoginID = lLoginID;
	m_struDeviceInfo.iDeviceChanNum = DeviceInfoTmp.byChanNum;
    m_struDeviceInfo.iIPChanNum = DeviceInfoTmp.byIPChanNum;
    m_struDeviceInfo.iStartChan  = DeviceInfoTmp.byStartChan;
	return TRUE;
}




void CPlayBackDlg::OnButtonLogin() 
{
	
	if(!m_bIsLogin)    //login
	{
		if(!DoLogin())
			return;
		DoGetDeviceResoureCfg();  //获取设备资源信息	
		CreateDeviceTree();        //创建通道树
		GetDlgItem(IDC_BUTTON_LOGIN)->SetWindowText("Logout");
		m_bIsLogin = TRUE;
		
	}
	else      //logout
	{
		
		
	/*	if(m_bIsPlaying|| m_bIsRecording)
		{
			MessageBox("Stop Play or record first!");
			return;
		}*/
        NET_DVR_Logout_V30(m_struDeviceInfo.lLoginID); 
		GetDlgItem(IDC_BUTTON_LOGIN)->SetWindowText("Login");
		m_ctrlTreeChan.DeleteAllItems();
		m_struDeviceInfo.lLoginID = -1;
		m_bIsLogin = FALSE;
	}
}


//获取通道信息
void CPlayBackDlg::DoGetDeviceResoureCfg()
{
	NET_DVR_IPPARACFG_V40 IpAccessCfg;
	memset(&IpAccessCfg,0,sizeof(IpAccessCfg));	
	DWORD  dwReturned;
	
	m_struDeviceInfo.bIPRet = NET_DVR_GetDVRConfig(m_struDeviceInfo.lLoginID,NET_DVR_GET_IPPARACFG_V40,0,&IpAccessCfg,sizeof(NET_DVR_IPPARACFG_V40),&dwReturned);
	
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
			if(IpAccessCfg.struStreamMode[i].uGetStream.struChanInfo.byEnable)  //ip通道在线
			{
				m_struDeviceInfo.struChanInfo[i+MAX_ANALOG_CHANNUM].bEnable = TRUE;
                m_struDeviceInfo.struChanInfo[i+MAX_ANALOG_CHANNUM].iChanIndex = IpAccessCfg.dwStartDChan+i;
				sprintf(m_struDeviceInfo.struChanInfo[i+MAX_ANALOG_CHANNUM].chChanName,"IP Camera %d",i+1);
				
			}
			else
			{
				m_struDeviceInfo.struChanInfo[i+MAX_ANALOG_CHANNUM].bEnable = FALSE;
				m_struDeviceInfo.struChanInfo[i+MAX_ANALOG_CHANNUM].iChanIndex = -1;
			}
		}
		
		
	}
	
}

void CPlayBackDlg::CreateDeviceTree()
{
	m_hDevItem = m_ctrlTreeChan.InsertItem("Dev");
	m_ctrlTreeChan.SetItemData(m_hDevItem,DEVICETYPE*1000);
    for(int i=0; i<MAX_CHANNUM_V30; i++)
	{
		if(m_struDeviceInfo.struChanInfo[i].bEnable)  //通道有效，插入通道树
		{
			HTREEITEM ChanItem = m_ctrlTreeChan.InsertItem(m_struDeviceInfo.struChanInfo[i].chChanName,m_hDevItem);
			m_ctrlTreeChan.SetItemData(ChanItem,CHANNELTYPE*1000+i);   //Data对应通道在数组中的索引
		}
	}
	m_ctrlTreeChan.Expand(m_hDevItem,TVE_EXPAND);
}


void CPlayBackDlg::OnSelchangedTreeChan(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	HTREEITEM hSelected = m_ctrlTreeChan.GetSelectedItem();
	//未选中
	if(NULL == hSelected)
		return;
	DWORD itemData = m_ctrlTreeChan.GetItemData(hSelected);
	HTREEITEM hParent = NULL;
	int itype = itemData/1000;    //
	int iIndex = itemData%1000;
	
	switch(itype)
	{
	case DEVICETYPE:
		m_iCurChanIndex = -1;
		break;
	case CHANNELTYPE:
		m_iCurChanIndex = iIndex;
		TRACE("select chan: %d\n",iIndex);
		break;
	default:
		break;
		
	}
	*pResult = 0;
}

void CPlayBackDlg::OnClose() 
{
	if(m_PageRemote.m_hPlayHandle != -1)
	{
         m_PageRemote.StopPlayback();
	}
	
	CDialog::OnClose();
}
