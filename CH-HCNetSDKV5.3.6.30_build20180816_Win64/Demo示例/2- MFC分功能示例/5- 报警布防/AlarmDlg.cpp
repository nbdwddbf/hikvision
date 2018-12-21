// AlarmDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winver.h"
#include "Alarm.h"
#include "AlarmDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CAlarmDlg * g_pMainDlg = NULL;	//
BOOL m_balarm[MAX_DEVICES] = {0};
int m_nlnm[MAX_DEVICES] = {0};

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
// CAlarmDlg dialog

CAlarmDlg::CAlarmDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAlarmDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAlarmDlg)
	m_DeviceName = _T("test");
	m_DevicePort = 8000;
	m_Password = _T("12345");
	m_UserName = _T("admin");
	m_iDeviceIndex = 0;
	m_fAlarm = NULL;
	m_fLog = NULL;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAlarmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlarmDlg)
	DDX_Control(pDX, IDC_LIST_DEV, m_listDev);
	DDX_Control(pDX, IDC_LIST_ALARM_INFO, m_listAlarmInfo);
	DDX_Control(pDX, IDC_DeviceIP, m_ctrlDeviceIP);
	DDX_Text(pDX, IDC_EDIT_DeviceName, m_DeviceName);
	DDX_Text(pDX, IDC_EDIT_Port, m_DevicePort);
	DDX_Text(pDX, IDC_EDIT_Password, m_Password);
	DDX_Text(pDX, IDC_EDIT_UserName, m_UserName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAlarmDlg, CDialog)
	//{{AFX_MSG_MAP(CAlarmDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK_ConnectDevice, OnConnectDevice)
	ON_BN_CLICKED(IDDEL_ConnectDevice, OnConnectDeviceDel)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CLEAN, OnClean)
	ON_MESSAGE(WM_ADD_LOG, OnWMAddLog)
	ON_MESSAGE(WM_PROC_ALARM, OnWMProcAlarm)
	ON_BN_CLICKED(IDC_BUTTON1, OnButtonRecSetAlarm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlarmDlg message handlers

BOOL CAlarmDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.
    m_DeviceName.Format("dev%02d", m_iDeviceIndex);
	m_Password.Format("12345");
	m_UserName.Format("admin");
	m_ctrlDeviceIP.SetAddress(192,0,0,64);
    UpdateData(FALSE);
    g_pMainDlg = this;

	char szLan[128] = {0};
	m_listAlarmInfo.InsertColumn(0,"",LVCFMT_LEFT,0,-1); 
	g_StringLanType(szLan, "Time", "Time");
	m_listAlarmInfo.InsertColumn(1, szLan,LVCFMT_LEFT,150);
	g_StringLanType(szLan, "Alarm Info", "Alarm Info");
	m_listAlarmInfo.InsertColumn(2, szLan,LVCFMT_LEFT,400);
	g_StringLanType(szLan, "Device Info", "Device Info");
	m_listAlarmInfo.InsertColumn(3, szLan,LVCFMT_LEFT,160);
	m_listAlarmInfo.SetExtendedStyle(m_listAlarmInfo.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);

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

	NET_DVR_SetLogToFile(3, "c:\\SdkLog\\", TRUE);   //SDK log

	//SDK uploads the info such as alarm and log sent from DVR by calling callback function 
	NET_DVR_SetDVRMessageCallBack_V30(MessageCallback, NULL);
	//SDK detects exception and uploads it, such as network disconnect

	return TRUE;  // return TRUE  unless you set the focus to a control
}

//the structure of the log information
typedef struct tagLOCAL_LOG_INFO 
{
	int iLogType;
	char szTime[64];
	char szLogInfo[512];
	char szDevInfo[128];
	char szErrInfo[256];
	tagLOCAL_LOG_INFO ()
	{
		iLogType = 0;
		szTime[0] = '\0';
		szLogInfo[0] = '\0';
		szDevInfo[0] = '\0';
		szErrInfo[0] = '\0';
	}
}LOCAL_LOG_INFO, *LPLOCAL_LOG_INFO;

//Alarm host
typedef struct tagLOCAL_ALARM_INFO
{
	int iDeviceIndex;
	LONG lCommand;
	LONG lLoginID;
	tagLOCAL_ALARM_INFO()
	{
		iDeviceIndex = -1;
		lCommand = -1;
	}
}LOCAL_ALARM_INFO, *LPLOCAL_ALARM_INFO;
/*********************************************************
Function:	MessageCallback
Desc:		alarm, callback functions dealing with the info of card in ATM
Input:	lCommand,message type; pAlarmer,info of device which upload message;pAlarmInfo, message info content;dwBufLen,message length; pUser, user parameter
Output:	
Return:	
**********************************************************/
void CALLBACK MessageCallback(LONG lCommand, NET_DVR_ALARMER *pAlarmer, char *pAlarmInfo, DWORD dwBufLen, void* pUser)
{
	UNREFERENCED_PARAMETER(pUser);	
	UINT iDeviceIndex = 0;
	UINT i = 0;
	if (g_pMainDlg == NULL)
	{
		TRACE("exit ...\n");
		return;
	}
	
	for (i=0; i<MAX_DEVICES; i++)
	{//IP address that client have acquired
		if (strcmp(g_struDeviceInfo[i].chDeviceIP, pAlarmer->sDeviceIP) == 0)
		{
			break;
		}
	}
	iDeviceIndex = i;
	
	if (iDeviceIndex >= MAX_DEVICES || iDeviceIndex < 0)
	{
		return;
	}
	try
	{
		char *pAlarmMsg = new char[dwBufLen];
		if (pAlarmMsg == NULL)
		{
			return;
		}
		memcpy(pAlarmMsg, pAlarmInfo, dwBufLen);		
		LPLOCAL_ALARM_INFO pAlarmDev = new LOCAL_ALARM_INFO;
		if (pAlarmDev == NULL)
		{
			delete [] pAlarmMsg;
			pAlarmMsg = NULL;
			return;
		}
		pAlarmDev->iDeviceIndex = iDeviceIndex;
		pAlarmDev->lCommand = lCommand;
        pAlarmDev->lLoginID = pAlarmer->lUserID;
		
		::PostMessage(g_pMainDlg->m_hWnd, WM_PROC_ALARM, (DWORD)pAlarmDev, (LONG)pAlarmMsg);	
	}
	catch (...)
	{
		OutputDebugString("New Alarm Exception!\n");
	}
	
	return;
}



/*********************************************************
Function:	OnWMProcAlarm
Desc:		responding to the message WM_PROC_ALARM
Input:	wParam, parameter 1;lParam, parameter 2;
Output:	none
Return:	result code
**********************************************************/
LRESULT CAlarmDlg::OnWMProcAlarm(WPARAM wParam, LPARAM lParam)
{
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	char *pAlarmInfo = (char *)(lParam);		
	int iDeviceIndex = pAlarmDev->iDeviceIndex;
	if (iDeviceIndex < 0 && iDeviceIndex >= MAX_DEVICES)
	{
		delete [] pAlarmInfo;
		delete pAlarmDev;
		return NULL;
	}
	
	switch (pAlarmDev->lCommand)
	{
		case COMM_ALARM_V30:
			ProcAlarmV30(wParam, lParam);
		break;
		case COMM_ALARM:
			ProcAlarm(wParam, lParam);
		break;
		default:
		break;
	}
	if (pAlarmInfo != NULL)
	{
		delete pAlarmInfo;
		pAlarmInfo = NULL;
	}
	if (pAlarmDev != NULL)
	{
		delete pAlarmDev;
		pAlarmDev = NULL;
	}

	return 0;
}
void CAlarmDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAlarmDlg::OnPaint() 
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
HCURSOR CAlarmDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAlarmDlg::OnConnectDevice() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD DeviceIP;
	NET_DVR_DEVICEINFO_V30 struLocalDeviceInfo;
	char szDeviceIP[16] = {0};
	char szUserName[100] = {0};
	char szPassword[20] = {0};
	LONG lUserId = -1;
	DWORD Err = 0;
	if (m_ctrlDeviceIP.IsBlank())
	{
		AfxMessageBox("Device IP address can not be empty!");
		return;
	}	
	if (m_DevicePort <= 0)
	{
		AfxMessageBox("Illegal port number!");
		return;
	}
    if (strlen(m_UserName) == 0 || strlen(m_Password) == 0)
    {
		AfxMessageBox("User name or password can not be empty!");
		return;
    }
	if (strlen(m_UserName) > 16 || strlen(m_Password) > 16)
	{
		AfxMessageBox("User name or password is too long!");
		return;
	}

	m_ctrlDeviceIP.GetAddress(DeviceIP);
	CString csTemp;
	unsigned char *pIP = (unsigned char*)&DeviceIP;
    csTemp.Format("%u.%u.%u.%u",*(pIP+3),*(pIP+2),*(pIP+1),*(pIP));
	strcpy(szDeviceIP,csTemp);
	strncpy(szPassword,m_Password,PASSWD_LEN);
	strncpy(szUserName,m_UserName,MAX_NAMELEN);
	memset(&struLocalDeviceInfo,0,sizeof(struLocalDeviceInfo));
	lUserId = NET_DVR_Login_V30(szDeviceIP,(WORD)m_DevicePort,szUserName,szPassword,&struLocalDeviceInfo);
	if(lUserId < 0)
	{
		Err =  NET_DVR_GetLastError();
		if(Err == NET_DVR_PASSWORD_ERROR)
		{
			AfxMessageBox("User name password is incorrect!");
			return;
		}
		else
		{
			AfxMessageBox("device is busy or the network reasons, Login fail");
			return;
		}
	}
    m_iDeviceIndex = lUserId;

	g_struDeviceInfo[m_iDeviceIndex].lLoginID = lUserId;
    sprintf(g_struDeviceInfo[m_iDeviceIndex].chLocalNodeName, "%s", m_DeviceName);
	sprintf(g_struDeviceInfo[m_iDeviceIndex].chDeviceIP, "%s", szDeviceIP);
	g_struDeviceInfo[m_iDeviceIndex].iDeviceIndex = m_iDeviceIndex;
	
	g_struDeviceInfo[m_iDeviceIndex].iDeviceType = struLocalDeviceInfo.wDevType;  
	g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum = struLocalDeviceInfo.byChanNum;
	g_struDeviceInfo[m_iDeviceIndex].iStartChan = struLocalDeviceInfo.byStartChan;
	g_struDeviceInfo[m_iDeviceIndex].iDiskNum = struLocalDeviceInfo.byDiskNum;
	g_struDeviceInfo[m_iDeviceIndex].iAlarmOutNum = struLocalDeviceInfo.byAlarmOutPortNum;
	g_struDeviceInfo[m_iDeviceIndex].iAlarmInNum = struLocalDeviceInfo.byAlarmInPortNum;
	g_struDeviceInfo[m_iDeviceIndex].iAudioNum = struLocalDeviceInfo.byAudioChanNum;
	g_struDeviceInfo[m_iDeviceIndex].iIPChanNum = struLocalDeviceInfo.byIPChanNum;
    g_struDeviceInfo[m_iDeviceIndex].byZeroChanNum = struLocalDeviceInfo.byZeroChanNum;
    g_struDeviceInfo[m_iDeviceIndex].byMainProto = struLocalDeviceInfo.byMainProto;
    g_struDeviceInfo[m_iDeviceIndex].bySubProto = struLocalDeviceInfo.bySubProto;


	CTime ctCurTime = CTime::GetCurrentTime();
	NET_DVR_TIME CurTime;
	CurTime.dwYear = ctCurTime.GetYear();
	CurTime.dwMonth = ctCurTime.GetMonth();
	CurTime.dwDay = ctCurTime.GetDay();
	CurTime.dwHour = ctCurTime.GetHour();
	CurTime.dwMinute = ctCurTime.GetMinute();
	CurTime.dwSecond = ctCurTime.GetSecond();

	if (NET_DVR_SetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_SET_TIMECFG, 0, &CurTime, sizeof(NET_DVR_TIME)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_TIMECFG");	
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_TIMECFG");
	}

    g_struDeviceInfo[m_iDeviceIndex].lFortifyHandle = NET_DVR_SetupAlarmChan_V30(g_struDeviceInfo[m_iDeviceIndex].lLoginID);
	if(g_struDeviceInfo[m_iDeviceIndex].lFortifyHandle == -1)
	{	
		AfxMessageBox( "Set Alarm Fail");
		return;
	}
	else
	{
		AfxMessageBox( "Set Alarm Success");
        int itest = m_listDev.GetItemCount();
		m_listDev.InsertItem(itest, "", -1);
		m_listDev.SetItemText(itest, 0, g_struDeviceInfo[m_iDeviceIndex].chLocalNodeName);
        m_listDev.SetItemData(itest, m_iDeviceIndex);
		SetTimer(m_iDeviceIndex,1000, NULL);
		m_balarm[m_iDeviceIndex] = FALSE;
		return;
	}

	return;
}

/*********************************************************
Function:	OnWMProcAlarm
Desc:		process alarm information when 
Input:	none
Output:	none
Return:	none
**********************************************************/
void CAlarmDlg::ProcAlarm(WPARAM wParam, LPARAM lParam)
{
	char szInfoBuf[1024] = {0};
	BOOL bDisk = FALSE;
	int i = 0;
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	char *pAlarmInfo = (char *)(lParam);		
	int iDeviceIndex = pAlarmDev->iDeviceIndex;

	int iDevInde = pAlarmDev->lLoginID;

	char szLan[128] ={0};
	NET_DVR_ALARMINFO m_struAlarmInfo;
	memcpy(&m_struAlarmInfo, pAlarmInfo, sizeof(NET_DVR_ALARMINFO));
	if (!(g_struDeviceInfo[iDeviceIndex].bAlarm))
	{
		g_struDeviceInfo[iDeviceIndex].bAlarm = TRUE;		
	}
	
	switch (m_struAlarmInfo.dwAlarmType)
	{
	case 0://signal alarm
		m_balarm[iDevInde] = TRUE;
		g_StringLanType(szLan, "Switch alarm", "Switch alarm input");
		sprintf(szInfoBuf,"%s alarm port: %d", szLan, m_struAlarmInfo.dwAlarmInputNumber+1); 
		g_StringLanType(szLan, ",Trigger channel video:", ", Invoke record Channel:");
		sprintf(szInfoBuf,"%s%s", szInfoBuf, szLan); 
		for (i=0; i<MAX_CHANNUM; i++)
		{
			if (m_struAlarmInfo.dwAlarmRelateChannel[i] == 1)
			{
				sprintf(szInfoBuf,"%s start channel number: %d,", szInfoBuf, i+g_struDeviceInfo[iDeviceIndex].iStartChan); 
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T,szInfoBuf);
		break;
	case 1://hard disk full alarm
		m_balarm[iDevInde] = TRUE;
		g_StringLanType(szInfoBuf, "Hard disk full alarm:", "HDD is Full:");
		for (i=0; i<MAX_DISKNUM; i++)
		{
			if (m_struAlarmInfo.dwDiskNumber[i] == 1)
			{
				sprintf(szInfoBuf, "%s HDD%d ", szInfoBuf, i);
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T,szInfoBuf);
		break;
	case 2://video loss alarm
		m_balarm[iDevInde] = TRUE;
		g_StringLanType(szInfoBuf, "Video signal loss alarm:", "The video signal lost:");
		for (i=0; i<MAX_CHANNUM; i++)
		{
			if (m_struAlarmInfo.dwChannel[i] == 1)
			{
				if (!(g_struDeviceInfo[iDeviceIndex].struChanInfo[i].bAlarm))
				{
					g_struDeviceInfo[iDeviceIndex].struChanInfo[i].bAlarm = TRUE;
					::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));	
				}
				sprintf(szInfoBuf, "%s %s Alarm port: %d", szInfoBuf, g_struDeviceInfo[iDeviceIndex].struChanInfo[i].chChanName, \
					m_struAlarmInfo.dwAlarmInputNumber+1);				
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	case 3://motion detection alarm
		m_balarm[iDevInde] = TRUE;
		g_StringLanType(szInfoBuf, "Motion detection alarm", "motion detection");
		for (i=0; i<MAX_CHANNUM; i++)
		{
			if (m_struAlarmInfo.dwChannel[i] == 1)
			{
				if (!g_struDeviceInfo[iDeviceIndex].struChanInfo[i].bAlarm)
				{
					g_struDeviceInfo[iDeviceIndex].struChanInfo[i].bAlarm = TRUE;
					::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));		
				}
				sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].struChanInfo[i].chChanName);
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	case 4://hard disk unformatted alarm
		m_balarm[iDevInde] = TRUE;
		g_StringLanType(szInfoBuf, "Hard disk is not formatted alarm", "HDD not formatted:");
		for (i=0; i<MAX_DISKNUM; i++)
		{
			if (m_struAlarmInfo.dwDiskNumber[i] == 1)
			{
				sprintf(szInfoBuf, "%s HDD%d", szInfoBuf, i);
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	case 5://hard disk alarm
		m_balarm[iDevInde] = TRUE;
		for (i=0; i<MAX_DISKNUM; i++)
		{
			if (m_struAlarmInfo.dwDiskNumber[i] == 1)
			{
				bDisk = TRUE;
				g_StringLanType(szLan, "Read-write hard disk error", "failed to read and write HDD");
				sprintf(szInfoBuf, "%sHDD%d ", szLan, i);
				g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
			}
		}
		if (bDisk == FALSE)
		{
			g_StringLanType(szInfoBuf, "Missed the hard disk error alarm", "no HDD");
			g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		}
		bDisk = FALSE;
		break;
	case 6://mask alarm
		m_balarm[iDevInde] = TRUE;
		g_StringLanType(szInfoBuf, "Occlusion alarm occurs", "Mask alarm");
		for (i=0; i<MAX_CHANNUM; i++)
		{
			if (m_struAlarmInfo.dwChannel[i] == 1)
			{
				if (!g_struDeviceInfo[iDeviceIndex].struChanInfo[i].bAlarm)
				{
					g_struDeviceInfo[iDeviceIndex].struChanInfo[i].bAlarm = TRUE;
					::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));		
				}
				sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].struChanInfo[i].chChanName);
			}
		}	
		
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	case 7:	//type unmatched
		m_balarm[iDevInde] = TRUE;
		g_StringLanType(szInfoBuf, "Standard does not match", "input and output video standard not match");
		for (i=0; i<MAX_CHANNUM; i++)
		{
			if (m_struAlarmInfo.dwChannel[i] == 1)
			{
				if (!g_struDeviceInfo[iDeviceIndex].struChanInfo[i].bAlarm)
				{
					g_struDeviceInfo[iDeviceIndex].struChanInfo[i].bAlarm = TRUE;
					::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));		
				}
				sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].struChanInfo[i].chChanName);
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	case 8:
		m_balarm[iDevInde] = TRUE;
		g_StringLanType(szInfoBuf, "Illegal access", "illegal access");
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);		
        break;
	case 9:
		m_balarm[iDevInde] = TRUE;
        g_StringLanType(szInfoBuf, "Video signal abnormalities", "video exception");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);		
		break;
    case 10:
		m_balarm[iDevInde] = TRUE;
        g_StringLanType(szInfoBuf, "Video abnormal", "record exception");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);		
		break;
    case 11:
		m_balarm[iDevInde] = TRUE;
        g_StringLanType(szInfoBuf, "Intelligent Scene Change", "Vca scene change");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T,szInfoBuf);
        break;
	default:
		g_StringLanType(szLan, "Unknown alarm type:", "Unknown Alarm Type:");
		sprintf(szInfoBuf, "%s 0x%x", szLan, m_struAlarmInfo.dwAlarmType);
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	}
}

/*********************************************************
Function:	ProcAlarmV30
Desc:		process alarm information for version 30
Input:	none
Output:	none
Return:	none
**********************************************************/
void CAlarmDlg::ProcAlarmV30(WPARAM wParam, LPARAM lParam)
{
	char szInfoBuf[1024] = {0};
	BOOL bDisk = FALSE;
	int i = 0;
	LPLOCAL_ALARM_INFO pAlarmDev = (LPLOCAL_ALARM_INFO)(wParam);
	char *pAlarmInfo = (char *)(lParam);		
	int iDeviceIndex = pAlarmDev->iDeviceIndex;

	int iDevInde = pAlarmDev->lLoginID;

	char szLan[128] = {0};
	NET_DVR_ALARMINFO_V30 m_struAlarmInfoV30;

	memcpy(&m_struAlarmInfoV30, pAlarmInfo, sizeof(NET_DVR_ALARMINFO_V30));

	if (!(g_struDeviceInfo[iDeviceIndex].bAlarm))
	{
		g_struDeviceInfo[iDeviceIndex].bAlarm = TRUE;		
	}
	
	switch (m_struAlarmInfoV30.dwAlarmType)
	{
	case 0://signal alarm
		m_balarm[iDevInde] = TRUE;
		g_StringLanType(szLan, "Switch alarm", "Switch alarm input");
		sprintf(szInfoBuf,"%s alarm port: %d", szLan, m_struAlarmInfoV30.dwAlarmInputNumber+1); 
		g_StringLanType(szLan, ",Trigger channel video:", "Invoke record Channel:");
		sprintf(szInfoBuf,"%s%s", szInfoBuf, szLan); 
		for (i=0; i<MAX_CHANNUM_V30; i++)
		{
			if (m_struAlarmInfoV30.byAlarmRelateChannel[i] == 1)
			{
				sprintf(szInfoBuf,"%s %d,", szInfoBuf, i+g_struDeviceInfo[iDeviceIndex].iStartChan); 					
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T,szInfoBuf);
		break;
	case 1://hard disk full alarm
		m_balarm[iDevInde] = TRUE;
		g_StringLanType(szInfoBuf, "Hard disk full alarm", "HD is full:");
		for (i=0; i<MAX_DISKNUM_V30; i++)
		{
			if (m_struAlarmInfoV30.byDiskNumber[i] == 1)
			{
				sprintf(szInfoBuf, "%s HDD%d ", szInfoBuf, i);
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T,szInfoBuf);
		break;
	case 2://video loss alarm
		m_balarm[iDevInde] = TRUE;
		g_StringLanType(szInfoBuf, "Video signal loss alarm", "The signal lost");
		sprintf(szInfoBuf,"%s alarm port: %d", szInfoBuf, m_struAlarmInfoV30.dwAlarmInputNumber+1); 
		for (i=0; i<MAX_CHANNUM_V30; i++)
		{
			if (m_struAlarmInfoV30.byChannel[i] == 1)
			{
				if (!(g_struDeviceInfo[iDeviceIndex].struChanInfo[i].bAlarm))
				{
					g_struDeviceInfo[iDeviceIndex].struChanInfo[i].bAlarm = TRUE;
					::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));			
				}
				sprintf(szInfoBuf, "%s %s ", szInfoBuf, g_struDeviceInfo[iDeviceIndex].struChanInfo[i].chChanName);	
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T,szInfoBuf);
		break;
	case 3://motion detection alarm
		m_balarm[iDevInde] = TRUE;
		g_StringLanType(szInfoBuf, "Motion detection alarm", "motion detection");
		for (i=0; i<MAX_CHANNUM_V30; i++)
		{
			if (m_struAlarmInfoV30.byChannel[i] == 1)
			{
				if (!g_struDeviceInfo[iDeviceIndex].struChanInfo[i].bAlarm)
				{
					g_struDeviceInfo[iDeviceIndex].struChanInfo[i].bAlarm = TRUE;
					::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));		
				}
				sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].struChanInfo[i].chChanName);
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	case 4://hard disk unformatted alarm
		m_balarm[iDevInde] = TRUE;
		g_StringLanType(szInfoBuf, "Hard disk is not formatted alarm", "not formatted");
		for (i=0; i<MAX_DISKNUM_V30; i++)
		{
			if (m_struAlarmInfoV30.byDiskNumber[i] == 1)
			{
				sprintf(szInfoBuf, "%s HDD%d ", szInfoBuf, i);
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	case 5://hard disk alarm
		m_balarm[iDevInde] = TRUE;
		for (i=0; i<MAX_DISKNUM_V30; i++)
		{
			if (m_struAlarmInfoV30.byDiskNumber[i] == 1)
			{
				bDisk = TRUE;
				g_StringLanType(szLan, "Read-write hard disk error", "failed to read and write HDD");
				sprintf(szInfoBuf, "%sHDD%d ", szLan, i);
				g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
			}
		}
		if (bDisk == FALSE)
		{
			g_StringLanType(szInfoBuf, "Missed the hard disk error alarm", "No HDD");
			g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		}
		bDisk = FALSE;
		break;
		m_balarm[iDevInde] = TRUE;
		g_StringLanType(szInfoBuf, "Occlusion alarm occurs", "Mask alarm");
		for (i=0; i<MAX_CHANNUM_V30; i++)
		{
			if (m_struAlarmInfoV30.byChannel[i] == 1)
			{
				if (!g_struDeviceInfo[iDeviceIndex].struChanInfo[i].bAlarm)
				{
					g_struDeviceInfo[iDeviceIndex].struChanInfo[i].bAlarm = TRUE;
					::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));		
				}
				sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].struChanInfo[i].chChanName);
			}
		}	
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	case 7:	//type unmatched
		m_balarm[iDevInde] = TRUE;
		g_StringLanType(szInfoBuf, "Standard does not match", "input and output video standard not match");
		for (i=0; i<MAX_CHANNUM_V30; i++)
		{
			if (m_struAlarmInfoV30.byChannel[i] == 1)
			{
				if (!g_struDeviceInfo[iDeviceIndex].struChanInfo[i].bAlarm)
				{
					g_struDeviceInfo[iDeviceIndex].struChanInfo[i].bAlarm = TRUE;
					::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));		
				}
				sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].struChanInfo[i].chChanName);
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	case 8:
		m_balarm[iDevInde] = TRUE;
		g_StringLanType(szInfoBuf, "Unauthorized access ", "illegal access");
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);		
		break;
    case 9:
		m_balarm[iDevInde] = TRUE;
        g_StringLanType(szInfoBuf, "Video signal abnormalities", "video exception");
        for (i=0; i<MAX_CHANNUM_V30; i++)
        {
            if (m_struAlarmInfoV30.byChannel[i] == 1)
            {
                if (!(g_struDeviceInfo[iDeviceIndex].struChanInfo[i].bAlarm))
                {
                    g_struDeviceInfo[iDeviceIndex].struChanInfo[i].bAlarm = TRUE;
                    ::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));			
                }
                sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].struChanInfo[i].chChanName);		
            }
        }
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T,szInfoBuf);
        break;
    case 10:
		m_balarm[iDevInde] = TRUE;
        g_StringLanType(szInfoBuf, "Video abnormal", "record exception");
        for (i=0; i<MAX_CHANNUM_V30; i++)
        {
            if (m_struAlarmInfoV30.byChannel[i] == 1)
            {
                if (!(g_struDeviceInfo[iDeviceIndex].struChanInfo[i].bAlarm))
                {
                    g_struDeviceInfo[iDeviceIndex].struChanInfo[i].bAlarm = TRUE;
                    ::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));			
                }
                sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].struChanInfo[i].chChanName);		
            }
        }
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T,szInfoBuf);		
		break;
    case 11:
		m_balarm[iDevInde] = TRUE;
        g_StringLanType(szInfoBuf, "Intelligent Scene Change", "Vca scene change");
        for (i=0; i<MAX_CHANNUM_V30; i++)
        {
            if (m_struAlarmInfoV30.byChannel[i] == 1)
            {
                sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].struChanInfo[i].chChanName);		
            }
        }
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T,szInfoBuf);
        break;
    case 12:
		m_balarm[iDevInde] = TRUE;
        g_StringLanType(szInfoBuf, "Array of abnormal", "Array exception");
        g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T,szInfoBuf);
        break;
	case 13:
		m_balarm[iDevInde] = TRUE;
		g_StringLanType(szInfoBuf, "Front-end / video resolution does not match", "resolution mismatch");
		for (i=0; i<MAX_CHANNUM_V30; i++)
		{
			if (m_struAlarmInfoV30.byChannel[i] == 1)
			{
				if (!(g_struDeviceInfo[iDeviceIndex].struChanInfo[i].bAlarm))
				{
					g_struDeviceInfo[iDeviceIndex].struChanInfo[i].bAlarm = TRUE;
					::PostMessage(g_pMainDlg->m_hWnd, WM_CHANGE_CHANNEL_ITEM_IMAGE, WPARAM(iDeviceIndex), LPARAM(i));			
				}
				sprintf(szInfoBuf, "%s %s", szInfoBuf, g_struDeviceInfo[iDeviceIndex].struChanInfo[i].chChanName);		
			}
		}
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T,szInfoBuf);
        break;
	default:
		g_StringLanType(szLan, "Unknown alarm type:", "Unknown Alarm Type:");
		sprintf(szInfoBuf, "%s 0x%x-htonl%d", szLan, m_struAlarmInfoV30.dwAlarmType, ntohl(m_struAlarmInfoV30.dwAlarmType));
		g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, szInfoBuf);
		break;
	}
}

/*********************************************************
Function:	AddLog
Desc:		add local log
Input:	iLogType, log type, 0-alam, 1-operate log, 2-debug info; csLogInfo log info
Output:	
Return:	
**********************************************************/
void CAlarmDlg::AddLog(int iDeviceIndex, int iLogType, const char* format, ...)
{	
	CTime  cTime = CTime::GetCurrentTime();
	int iLen = 0;
	char szTime[64] = {0};
	char szLogType[32] = "FAIL";
	char szLogInfo[1024] = {0};
	char szDevInfo[256] = {0};
	char szErrInfo[256] = {0};
	char szLog[1024] = {0};
	va_list arglist;
	va_start(arglist,format);
	vsprintf(szLogInfo,format,arglist); 
	va_end(arglist);
	m_curTime = COleDateTime::GetCurrentTime();

	sprintf(szTime, "%s", cTime.Format("%y-%m-%d %H:%M:%S").GetBuffer(0));
	
	if (iDeviceIndex != -1 && iDeviceIndex < 512)
	{
		sprintf(szDevInfo, "[%s]-[%s]", g_struDeviceInfo[iDeviceIndex].chDeviceIP, g_struDeviceInfo[iDeviceIndex].chLocalNodeName);
	}
	
	switch (iLogType)
	{
	case OPERATION_SUCC_T:
	case PLAY_SUCC_T:
		sprintf(szErrInfo, "");
		sprintf(szLogType, "SUCC");
		break;
	case PLAY_FAIL_T:
		sprintf(szErrInfo, "PLAY_M4 Eorror!!!");	
		break;
	case OPERATION_FAIL_T:
	default:
		sprintf(szErrInfo, "err[%d:%s]", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());	
		break;
	}

	if (iLogType == ALARM_INFO_T )
	{
		if (m_fAlarm!= NULL)
		{
			fclose(m_fAlarm);
		}

		CString filepath;
		filepath.Format("%s\\AlarmInfo_%4d%02d%02d%02d.txt",\
			"C:\\SaveRemoteCfgFile", m_curTime.GetYear(), m_curTime.GetMonth(),\
		m_curTime.GetDay(), m_curTime.GetHour());

		if ((m_fAlarm = fopen(filepath, "a+")) == NULL)
		{
		    AfxMessageBox("Open the file fail");
		}

		iLen = sprintf(szLog, "%s %s %s\n", szTime, szLogInfo, szDevInfo);
		if (m_fAlarm != NULL)
		{
			if (fwrite(szLog, 1, iLen, m_fAlarm) != (unsigned)iLen)
			{
				OutputDebugString("write err");
			}
		}
	}
	else
	{
        if (m_fLog != NULL)
        {
			fclose(m_fLog);
        }

		CString csLogFile;
		csLogFile.Format("%s\\LogFile888_%4d%02d%02d.txt",\
			"C:\\SaveRemoteCfgFile", m_curTime.GetYear(), m_curTime.GetMonth(),\
			m_curTime.GetDay());
		if ((m_fLog = fopen(csLogFile.GetBuffer(0), "a+")) == NULL)
		{
			AfxMessageBox("Open LogFile fail");
		}
		iLen = sprintf(szLog, "%s %s %s %s %s\n", szTime, szLogType, szLogInfo, szDevInfo, szErrInfo);
		if (m_fLog != NULL)
		{
			if (fwrite(szLog, 1, iLen, m_fLog) != (unsigned)iLen)
			{
				OutputDebugString("write err");
			}
		}
	}
	
	LPLOCAL_LOG_INFO pLogInfo = NULL;
	try
    {  		
		pLogInfo = new LOCAL_LOG_INFO;
		memset(pLogInfo, 0, sizeof(LOCAL_LOG_INFO));
		if (pLogInfo == NULL)
		{
			return;
		}
		pLogInfo->iLogType = iLogType;
		memcpy(pLogInfo->szTime, szTime, 64);
		memcpy(pLogInfo->szLogInfo, szLogInfo, 512);
		memcpy(pLogInfo->szDevInfo, szDevInfo, 128);
		memcpy(pLogInfo->szErrInfo, szErrInfo, 256);
		::PostMessage(g_pMainDlg->m_hWnd, WM_ADD_LOG, iDeviceIndex, (LONG)pLogInfo);
	}
	catch (...)
	{
		if (pLogInfo != NULL)
		{
			return;
		}
		OutputDebugString("New Log Exception!!\n");
	}
}

/*********************************************************
Function:	OnWMAddLog
Desc:		responding to the message WM_ADD_LOG
Input:	wParam, parameter 1;lParam, parameter 2;
Output:	none
Return:	result code
**********************************************************/
LRESULT CAlarmDlg::OnWMAddLog(WPARAM wParam, LPARAM lParam)
{
	LPLOCAL_LOG_INFO pLogInfo = LPLOCAL_LOG_INFO(lParam);
	if (NULL == pLogInfo)
	{
		return 0;
	}
	char szLogType[32] = "FAIL";
	
	char szTime[64] = {0};
	char szLogInfo[512] = {0};
	char szDevInfo[128] = {0};
	char szErrInfo[256] = {0};
	memcpy(szTime, pLogInfo->szTime, 64);
	memcpy(szLogInfo, pLogInfo->szLogInfo, 512);
	memcpy(szDevInfo, pLogInfo->szDevInfo, 128);
	memcpy(szErrInfo, pLogInfo->szErrInfo, 256);
	
	switch (pLogInfo->iLogType)
	{
	case ALARM_INFO_T:
		sprintf(szLogType, "Alarm");
		m_listAlarmInfo.InsertItem(0, "", -1);
		m_listAlarmInfo.SetItemText(0, 1, szTime);
		m_listAlarmInfo.SetItemText(0, 2, szLogInfo);
		m_listAlarmInfo.SetItemText(0, 3, szDevInfo);
		break;
	default:
		break;
	}
	if (pLogInfo != NULL)
	{
		delete pLogInfo;
		pLogInfo = NULL;
	}
	return 0;
}

void CAlarmDlg::OnConnectDeviceDel() 
{
	// TODO: Add your control notification handler code here
    int nItem = -1;
	POSITION  pos = m_listDev.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		return;
	}
	else
	{
		while(pos)
		{
			nItem = m_listDev.GetNextSelectedItem(pos);
		}
	}

	m_iDeviceIndex = m_listDev.GetItemData(nItem);

	if (-1 != g_struDeviceInfo[m_iDeviceIndex].lFortifyHandle)
	{
		if(NET_DVR_CloseAlarmChan_V30(g_struDeviceInfo[m_iDeviceIndex].lFortifyHandle))
		{
			g_struDeviceInfo[m_iDeviceIndex].lFortifyHandle = -1;
			AfxMessageBox("Alarm disarm success!");
		}
		else
		{
			AfxMessageBox("Alarm disarm fail!");
			return ;
		}
	}

	if (-1 != g_struDeviceInfo[m_iDeviceIndex].lLoginID)
	{
		if (!NET_DVR_Logout(g_struDeviceInfo[m_iDeviceIndex].lLoginID))
		{
			AfxMessageBox("Logout fail!");
			return ;
		}
		else
		{
			int nItem = m_listDev.GetNextItem(-1, LVNI_SELECTED);
			m_listDev.DeleteItem(nItem);
			g_struDeviceInfo[m_iDeviceIndex].lLoginID = -1;
			AfxMessageBox("Logout success!");	
		}
	}	
	UpdateData(FALSE);
}

void CAlarmDlg::OnDestroy() 
{	
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	if (m_fLog != NULL)
	{
		fclose(m_fLog);
	}
	if (m_fAlarm != NULL)
	{
		fclose(m_fAlarm);
	}

	if (-1 != g_struDeviceInfo[m_iDeviceIndex].lFortifyHandle)
	{
		if(NET_DVR_CloseAlarmChan_V30(g_struDeviceInfo[m_iDeviceIndex].lFortifyHandle))
		{
			g_struDeviceInfo[m_iDeviceIndex].lFortifyHandle = -1;
		}
	}
    
	if (-1 != g_struDeviceInfo[m_iDeviceIndex].lLoginID)
	{
		if (NET_DVR_Logout(g_struDeviceInfo[m_iDeviceIndex].lLoginID))
		{
			g_struDeviceInfo[m_iDeviceIndex].lLoginID = -1;
		}
	}

	NET_DVR_Cleanup();
}

void CAlarmDlg::OnTimer(UINT_PTR nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_balarm[nIDEvent] == TRUE)
	{
		m_balarm[nIDEvent] = FALSE;
		m_nlnm[nIDEvent] = 0;
	}
	else
	{
		if ((m_nlnm[nIDEvent]++) > 90)
		{
			if (g_struDeviceInfo[nIDEvent].lFortifyHandle != -1)
			{		
				if(NET_DVR_CloseAlarmChan_V30(g_struDeviceInfo[nIDEvent].lFortifyHandle))
				{
					g_struDeviceInfo[nIDEvent].lFortifyHandle = -1;
					m_nlnm[nIDEvent] = 0;
				    KillTimer(nIDEvent);
					AfxMessageBox("Alarm disarm success!");
				}
			}
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CAlarmDlg::OnClean() 
{
	// TODO: Add your control notification handler code here
	m_listAlarmInfo.DeleteAllItems();
}

void CAlarmDlg::OnButtonRecSetAlarm() 
{
	// TODO: Add your control notification handler code here
   int nItem = -1;
   POSITION  pos = m_listDev.GetFirstSelectedItemPosition();
   if (pos == NULL)
   {
	   return;
   }
   else
   {
	   while(pos)
	   {
		   nItem = m_listDev.GetNextSelectedItem(pos);
	   }
   }
   
   m_iDeviceIndex = m_listDev.GetItemData(nItem);
   g_struDeviceInfo[m_iDeviceIndex].lFortifyHandle = NET_DVR_SetupAlarmChan_V30(g_struDeviceInfo[m_iDeviceIndex].lLoginID);
   if(g_struDeviceInfo[m_iDeviceIndex].lFortifyHandle == -1)
   {	
	   AfxMessageBox( "Set Alarm Fail");
	   return;
   }
   else
   {
	   AfxMessageBox( "Set Alarm Success");
	   SetTimer(m_iDeviceIndex,1000, NULL);
	   m_balarm[m_iDeviceIndex] = FALSE;
	   return;
   }
  
}
