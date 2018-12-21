 // DecCallBack_DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DecCallBack_Demo.h"
#include "DecCallBack_DemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
int iPicNum=0;//Set channel NO.
LONG nPort=-1;
FILE *Videofile=NULL;
FILE *Audiofile=NULL;
char filename[100];
HWND hPlayWnd=NULL;
CString ErrorNum;

//////////////////////////////////////////////////////////////////////////
// IP to String
CString IPToStr(DWORD dwIP)
{
	CString strIP = _T("");
	WORD add1,add2,add3,add4;
	
	add1=(WORD)(dwIP&255);
	add2=(WORD)((dwIP>>8)&255);
	add3=(WORD)((dwIP>>16)&255);
	add4=(WORD)((dwIP>>24)&255);
	strIP.Format("%d.%d.%d.%d",add4,add3,add2,add1);
	return strIP;
}
//////////////////////////////////////////////////////////////////////////
////解码回调 视频为YUV数据(YV12)，音频为PCM数据
void CALLBACK DecCBFun(long nPort,char * pBuf,long nSize,FRAME_INFO * pFrameInfo, long nReserved1,long nReserved2)
{
 	long lFrameType = pFrameInfo->nType;	
	if (lFrameType ==T_AUDIO16)
	{
		TRACE("Audio nStamp:%d\n",pFrameInfo->nStamp);
		OutputDebugString("test_DecCb_Write Audio16 \n");
		if (Audiofile==NULL)
		{
			sprintf(filename,"AudionPCM.pcm",iPicNum);
			Audiofile = fopen(filename,"wb");
		}
		fwrite(pBuf,nSize,1,Audiofile);
	}

	else if(lFrameType ==T_YV12)
	{		
	    TRACE("Video nStamp:%d\n",pFrameInfo->nStamp);
		OutputDebugString("test_DecCb_Write YUV \n");
		if (Videofile==NULL)
		{
			sprintf(filename,"VideoYV12.yuv",iPicNum);
			Videofile = fopen(filename,"wb");
		}
		fwrite(pBuf,nSize,1,Videofile);
	}
	else
	{

	}
}
//////////////////////////////////////////////////////////////////////////
///实时流回调
void CALLBACK fRealDataCallBack(LONG lRealHandle,DWORD dwDataType,BYTE *pBuffer,DWORD dwBufSize,void *pUser)
{
	DWORD dRet = 0;
	BOOL inData = FALSE;

	switch (dwDataType)
	{
	case NET_DVR_SYSHEAD:
		if (!PlayM4_GetPort(&nPort))
		{
			break;
		}
		if (!PlayM4_OpenStream(nPort,pBuffer,dwBufSize,1024*1024))
		{
			dRet=PlayM4_GetLastError(nPort);
			break;
		}

		//设置解码回调函数 只解码不显示
// 		if (!PlayM4_SetDecCallBack(nPort,DecCBFun))
// 		{
// 			dRet=PlayM4_GetLastError(nPort);
// 			break;
// 		}
		
		//设置解码回调函数 解码且显示
		if (!PlayM4_SetDecCallBackEx(nPort,DecCBFun,NULL,NULL))
		{
			dRet=PlayM4_GetLastError(nPort);
			break;
		}

		//打开视频解码
		if (!PlayM4_Play(nPort,hPlayWnd))
		{
			dRet=PlayM4_GetLastError(nPort);
			break;
		}

		//打开音频解码, 需要码流是复合流
		if (!PlayM4_PlaySound(nPort))
		{
			dRet=PlayM4_GetLastError(nPort);
			break;
		}
		break;
		
	case NET_DVR_STREAMDATA:
        inData=PlayM4_InputData(nPort,pBuffer,dwBufSize);
		while (!inData)
		{
			Sleep(10);
			inData=PlayM4_InputData(nPort,pBuffer,dwBufSize);
			OutputDebugString("PlayM4_InputData failed \n");	
		}
		break;
	default:
		inData=PlayM4_InputData(nPort,pBuffer,dwBufSize);
		while (!inData)
		{
			Sleep(10);
			inData=PlayM4_InputData(nPort,pBuffer,dwBufSize);
			OutputDebugString("PlayM4_InputData failed \n");	
		}
		break;
	}
}
//////////////////////////////////////////////////////////////////////////
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
// CDecCallBack_DemoDlg dialog

CDecCallBack_DemoDlg::CDecCallBack_DemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDecCallBack_DemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDecCallBack_DemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDecCallBack_DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDecCallBack_DemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
    DDX_Control(pDX,IDC_STATIC_SCREEN,m_picplay);
	DDX_Text(pDX, IDC_EDIT_IPCH, iPChannel);
	DDX_Control(pDX, IDC_IPADDRESS, m_ctrlDeviceIP);
	DDX_Text(pDX, IDC_EDIT_Username, m_csUserName);
	DDX_Text(pDX, IDC_EDIT_Password, m_csPassword);
	DDX_Text(pDX, IDC_EDIT_Port, m_nLoginPort);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDecCallBack_DemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDecCallBack_DemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Login, OnBUTTONLogin)
	ON_BN_CLICKED(IDC_BUTTON_CAPTURE, OnButtonCapture)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDecCallBack_DemoDlg message handlers

BOOL CDecCallBack_DemoDlg::OnInitDialog()
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
    UpdateData(TRUE);
	NET_DVR_Init();

	llRealHandle=-1;
	lUserID=-1;
	iPChannel=1;

	m_ctrlDeviceIP.SetAddress(172, 6, 22, 86);
	m_csUserName="admin";
	m_csPassword="12345";
	m_nLoginPort=8000;

	hPlayWnd = GetDlgItem(IDC_STATIC_SCREEN)->m_hWnd;

    UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDecCallBack_DemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDecCallBack_DemoDlg::OnPaint() 
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
HCURSOR CDecCallBack_DemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDecCallBack_DemoDlg::OnBUTTONLogin() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwDeviceIP;
	char DeviceIP[16] = {0};
	char cUserName[100] = {0};
	char cPassword[100] = {0};
	CString csTemp;	

	m_ctrlDeviceIP.GetAddress(dwDeviceIP);
	csTemp = IPToStr(dwDeviceIP);
	sprintf(DeviceIP, "%s", csTemp.GetBuffer(0));
	strncpy(cUserName, m_csUserName, MAX_NAMELEN);
	strncpy(cPassword, m_csPassword, PASSWD_LEN);

	//登录设备，需要设备IP、端口、用户名、密码 Login the device
	NET_DVR_DEVICEINFO_V30 devInfo;
	lUserID = NET_DVR_Login_V30(DeviceIP,m_nLoginPort,cUserName,cPassword,&devInfo);

	DWORD dwReturned = 0;

	if(lUserID<0)
		AfxMessageBox("Login failed!");
	else
	{
		AfxMessageBox("Login successfully!");
	}
	UpdateData(FALSE);
	return;
}

void CDecCallBack_DemoDlg::OnOK() 
{
	// TODO: Add extra validation here
	BOOL bRet1;
	UpdateData(TRUE);
	if (llRealHandle<0)
	{
		UpdateData(TRUE);

		if (lUserID<0)
		{
			ErrorNum.Format("Login failed Error number ：%d\n",NET_DVR_GetLastError());
			OutputDebugString(ErrorNum);
		}

		//////////////////////////////////////////////////////////////////////////
		NET_DVR_CLIENTINFO ClientInfo;
		ClientInfo.lChannel = iPChannel; //Channel number 设备通道号
		ClientInfo.hPlayWnd = NULL;  //窗口为空，设备SDK不解码只取流
		ClientInfo.lLinkMode = 0;    //Main Stream
		ClientInfo.sMultiCastIP = NULL;
        
		//预览取流 
     	llRealHandle = NET_DVR_RealPlay_V30(lUserID,&ClientInfo,fRealDataCallBack,NULL,TRUE);
        
		if (llRealHandle<0)
        {
			ErrorNum.Format("NET_DVR_RealPlay_V30 failed! Error number: %d\n",NET_DVR_GetLastError());
			AfxMessageBox(ErrorNum);
			return;
        }

		GetDlgItem(IDOK)->SetWindowText("Stop");
	}
	else
	{	
		//停止预览
		if (NET_DVR_StopRealPlay(llRealHandle))
		{
			bRet1=NET_DVR_GetLastError();
		}		
	    llRealHandle=-1;

		//停止解码
		if (nPort>-1)
		{
			if (!PlayM4_StopSound())
			{
				bRet1=PlayM4_GetLastError(nPort);
			}
			if (!PlayM4_Stop(nPort))
			{
				bRet1=PlayM4_GetLastError(nPort);
			}
			if (!PlayM4_CloseStream(nPort))
			{
				bRet1=PlayM4_GetLastError(nPort);
			}
			PlayM4_FreePort(nPort);
			nPort=-1;
		}		

		//关闭保存解码后数据的音视频文件
		if (Audiofile!=NULL)
		{
			fclose(Audiofile);
			Audiofile=NULL;
		}

		if (Videofile!=NULL)
		{
			fclose(Videofile);
			Videofile=NULL;
		}		
		
		GetDlgItem(IDOK)->SetWindowText("Start Play");
	}

	UpdateData(FALSE);
//	CDialog::OnOK();
}

void CDecCallBack_DemoDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	if(llRealHandle>=0)
	{
		AfxMessageBox("Stop preview!");
		return;
	}

	NET_DVR_Logout_V30(lUserID);
	NET_DVR_Cleanup();	

	CDialog::OnCancel();
}

void CDecCallBack_DemoDlg::OnButtonCapture() 
{
	// TODO: Add your control notification handler code here
	FILE *file=NULL;

	NET_DVR_JPEGPARA JpegPara;
    JpegPara.wPicQuality=0;
    JpegPara.wPicSize=0xff;

	char *JpegPicBuffer= new char[352*288*2]; 
	//这里的缓冲区大小需要根据抓图的分辨率大小自己调节，建议设置成2*图片的分辨率宽*图片的分辨率高
	
	DWORD  SizeReturned=0;	
	BOOL bRet= NET_DVR_CaptureJPEGPicture_NEW(lUserID, iPChannel,&JpegPara,JpegPicBuffer,352*288*2,&SizeReturned);
	if (!bRet)
	{
		ErrorNum.Format("NET_DVR_CaptureJPEGPicture_NEW failed! Error number: %d\n",NET_DVR_GetLastError());
		AfxMessageBox(ErrorNum);
		return;
	}
	else
	{
		AfxMessageBox("NET_DVR_CaptureJPEGPicture_NEW successful");
	}

	if (file==NULL)
	{
		sprintf(filename,"..\\bin\\JPEGCAPTest_%d.jpg",iPicNum);
		file = fopen(filename,"wb");
	}
    fwrite(JpegPicBuffer,SizeReturned,1,file);
    iPicNum++;

	delete JpegPicBuffer;
    fclose(file);
    file=NULL;

	return;
}
