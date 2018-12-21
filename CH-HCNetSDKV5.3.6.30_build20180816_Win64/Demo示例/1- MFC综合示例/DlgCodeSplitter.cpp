// DlgCodeSplitter.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgCodeSplitter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCodeSplitter dialog


CDlgCodeSplitter::CDlgCodeSplitter(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCodeSplitter::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCodeSplitter)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgCodeSplitter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCodeSplitter)
	DDX_Control(pDX, IDC_TAB, m_Tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCodeSplitter, CDialog)
	//{{AFX_MSG_MAP(CDlgCodeSplitter)
	ON_BN_CLICKED(IDC_BTN_RESTORE, OnBtnRestore)
	ON_BN_CLICKED(IDC_BTN_REBOOT, OnBtnReboot)
	ON_BN_CLICKED(ID_BTN_EXIT, OnBtnExit)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCodeSplitter message handlers

BOOL CDlgCodeSplitter::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here	
	
	char szLan[128] = {0};
	g_StringLanType(szLan, "解码器配置", "Decoder config");
	m_Tab.InsertItem(0,szLan);
	g_StringLanType(szLan, "云台控制", "PTZ control");
    m_Tab.InsertItem(1,szLan);
	g_StringLanType(szLan, "设备基本信息", "Device config");
    m_Tab.InsertItem(2,szLan);
	g_StringLanType(szLan, "用户参数配置", "User config");
    m_Tab.InsertItem(3,szLan);
	g_StringLanType(szLan, "透明通道参数配置", "Transparent channel config");
	m_Tab.InsertItem(4,szLan);
	
	m_DlgDecoder.m_lServerID = m_lServerID;	

    m_DlgDecoder.Create(IDD_DLG_SPLITTER_DECODERCFG,&m_Tab);
    m_DlgPtz.Create(IDD_DLG_SPLITTER_PTZCONTROL,&m_Tab);
    m_DlgDevice.Create(IDD_DLG_SPLITTER_DEVICE_CFG,&m_Tab);    
	m_DlgUser.Create(IDD_DLG_SPLITTER_USER_CFG,&m_Tab);
    m_DlgTransparent.Create(IDD_DLG_SPLITTER_TRANSPARENT, &m_Tab);
    CRect rc;
    m_Tab.GetWindowRect(&rc);
    
    m_DlgDecoder.MoveWindow(1,20,rc.Width()-5,rc.Height()-25);
    m_DlgPtz.MoveWindow(1,20,rc.Width()-5,rc.Height()-25);    
    m_DlgDevice.MoveWindow(1,20,rc.Width()-5,rc.Height()-25);
    m_DlgUser.MoveWindow(1,20,rc.Width()-5,rc.Height()-25);   
	m_DlgTransparent.MoveWindow(1,20,rc.Width()-5,rc.Height()-25);
    m_Tab.SetCurSel(0);
	
    
    m_DlgDecoder.ShowWindow(SW_SHOW);
    //切换tab页时对此页信息进行更新。
    m_DlgPtz.ShowWindow(SW_HIDE);
    m_DlgDevice.ShowWindow(SW_HIDE);
    m_DlgUser.ShowWindow(SW_HIDE); 
	m_DlgTransparent.ShowWindow(SW_HIDE);

	//LONG style = GetDlgItem(IDD_DLG_CODESPITTER)->GetExStyle();
	//GetDlgItem(IDD_DLG_CODESPITTER)->ModifyStyleEx(1, WS_EX_APPWINDOW);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCodeSplitter::OnBtnRestore() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	if (m_lServerID < 0)
    {
		g_StringLanType(szLan, "尚未登录", "Please login first");
        MessageBox(szLan);
        return;
    }
	
	g_StringLanType(szLan, "确定要恢复默认参数?", "Sure to restore default configuration?");
    if (IDOK != MessageBox(szLan, "Warning", IDOK))
    {
        return;
    }
    
    if (!NET_DVR_RestoreConfig(m_lServerID))
    {
        MessageBox(NET_DVR_GetErrorMsg());
        return;
    }
    
	g_StringLanType(szLan, "恢复默认参数成功", "Success to restore default configuration");
    MessageBox(szLan);
}

void CDlgCodeSplitter::OnBtnReboot() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	if (m_lServerID < 0)
    {
		g_StringLanType(szLan, "尚未登录", "Please login first");
        MessageBox(szLan);
        return;
    }
	
	g_StringLanType(szLan, "确定要重启?", "Sure to reboot");
    if (IDOK != MessageBox(szLan,"Warning", IDOK))
    {
        return;
    }
	
    if (!NET_DVR_RebootDVR(m_lServerID))
    {
        MessageBox(NET_DVR_GetErrorMsg());
        return;
    }
	
	g_StringLanType(szLan, "设备正在重启...", "Rebooting...");
    MessageBox(szLan);
}

void CDlgCodeSplitter::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CDlgCodeSplitter::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	if (m_lServerID < 0)
    {
		g_StringLanType(szLan, "尚未登录", "Please login first");
        MessageBox(szLan);
        return;
    }
    
    int iCurSel = m_Tab.GetCurSel();
    switch(iCurSel)
    {
    case 0:
        m_DlgDecoder.ShowWindow(SW_SHOW);
        m_DlgDecoder.m_lServerID = m_lServerID;
		m_DlgDecoder.CheckInit();
        //切换tab页时对此页信息进行更新。
        m_DlgDevice.ShowWindow(SW_HIDE);
        m_DlgUser.ShowWindow(SW_HIDE);
        m_DlgPtz.ShowWindow(SW_HIDE);
		m_DlgTransparent.ShowWindow(SW_HIDE);
        break;
    case 1:
        m_DlgDecoder.ShowWindow(SW_HIDE);
        m_DlgDevice.ShowWindow(SW_HIDE);
        m_DlgUser.ShowWindow(SW_HIDE);
        m_DlgPtz.ShowWindow(SW_SHOW);
		m_DlgPtz.m_lServerID = m_lServerID;
		m_DlgTransparent.ShowWindow(SW_HIDE);
        break;
    case 2:
        m_DlgDecoder.ShowWindow(SW_HIDE);
        //切换tab页时对此页信息进行更新。
        m_DlgPtz.ShowWindow(SW_HIDE);
        m_DlgDevice.ShowWindow(SW_SHOW);
        m_DlgDevice.m_lServerID = m_lServerID;
        m_DlgDevice.GetDeviceParam();
        m_DlgUser.ShowWindow(SW_HIDE);
		m_DlgTransparent.ShowWindow(SW_HIDE);
        break;
    case 3:
        m_DlgDecoder.ShowWindow(SW_HIDE);
        //切换tab页时对此页信息进行更新。
        m_DlgPtz.ShowWindow(SW_HIDE);
        m_DlgDevice.ShowWindow(SW_HIDE);
        m_DlgUser.ShowWindow(SW_SHOW);
        m_DlgUser.m_lServerID = m_lServerID;  
		m_DlgTransparent.ShowWindow(SW_HIDE);
        break;
	case 4:
		m_DlgDecoder.ShowWindow(SW_HIDE);
        //切换tab页时对此页信息进行更新。
        m_DlgPtz.ShowWindow(SW_HIDE);
        m_DlgDevice.ShowWindow(SW_HIDE);
        m_DlgUser.ShowWindow(SW_HIDE);          
		m_DlgTransparent.ShowWindow(SW_SHOW);
		m_DlgTransparent.m_lServerID = m_lServerID;
        break;
    default:
        break;
    }
	*pResult = 0;
}
