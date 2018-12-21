/**********************************************************
FileName:    DlgPlayLocalFile.cpp
Description: local file playback   
Date:        2008/05/17
Note: 	     <global>struct, refer to GeneralDef.h, global variants and functions refer to ClientDemo.cpp  
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/


#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgPlayLocalFile.h"
#include ".\dlgplaylocalfile.h"
#include "DlgUploadFile.h"


// CDlgPlayLocalFile dialog

#define TIMER_INTERVAL 500//local play back timer refresh interval
#define USED_PORT 99		//card decode port
CDlgPlayLocalFile *g_pDlgPlayLocalFile = NULL;

/*********************************************************
Function:	FileRefDone
Desc:		callback function of file reference
Input:		nUser,CDlgPlayLocalFile pointer to class;
Output:	
Return:	
**********************************************************/
void CALLBACK FileRefDone(DWORD nReserved,DWORD nUser)
{
	CDlgPlayLocalFile* pOwner=(CDlgPlayLocalFile*)nUser;
	pOwner->UpdateStepBackUI(TRUE);	
}

/*********************************************************
Function:	DisplayCBFun
Desc:		callback function of capture
Input:		nPort,port; pBuf, image buffer; nSize,image size; nWidth,image width; nHeight,image height; nType,type;
Output:	
Return:	
**********************************************************/
void CALLBACK DisplayCBFun(long nPort,char * pBuf,long nSize,long nWidth,long nHeight,long nStamp,long nType,long nReserved)
{
	if (!g_bLocalCapPic)
	{
		return;
	}
	//switch function, of time-consuming; do not call it if you don't wanna save pic
	CString csDir;
	CString csFile;
	CTime time=CTime::GetCurrentTime();
	csDir.Format("%s",g_struLocalParam.chPictureSavePath);
	csFile.Format("%s\\Picture_%s_%02d_%4d%02d%02d_%02d%02d%02d_%d.bmp",csDir.GetBuffer(0), g_pDlgPlayLocalFile->m_csDeviceIP.GetBuffer(0),g_pDlgPlayLocalFile->m_iCurPlayChan,\
		time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond(), GetTickCount());
	if (!PlayM4_ConvertToBmpFile(pBuf, nSize, nWidth, nHeight, nType, csFile.GetBuffer(csFile.GetLength())))
	{
		g_pMainDlg->AddLog(g_pDlgPlayLocalFile->m_iDeviceIndex, OPERATION_FAIL_T, "PlayM4_ConvertToBmpFile");
	}
	else
	{
		g_pMainDlg->AddLog(g_pDlgPlayLocalFile->m_iDeviceIndex, OPERATION_SUCC_T, "PlayM4_ConvertToBmpFile[%s]", csFile);
	}
	g_bLocalCapPic=FALSE;
}

/*********************************************************
  Function:	~CDlgPlayLocalFile
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgPlayLocalFile, CDialog)
CDlgPlayLocalFile::CDlgPlayLocalFile(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPlayLocalFile::IDD, pParent)
	, m_ctDateStart(0)
	, m_ctTimeStart(0)
	, m_ctDateStop(0)
	, m_ctTimeStop(0)
	, m_iCurPlayChan(0)
	, m_csDeviceIP(_T(""))
	, m_iDeviceIndex(-1)
	, m_iChanIndex(-1)
	, m_lLoginID(-1)
	, m_lStartChan(0)
	, m_iChanCount(0)
	, m_hPareTabWnd(NULL)
	, m_hPareDlgWnd(NULL)
	, m_bPlay(FALSE)
	, m_bPause(FALSE)
	, m_bSound(FALSE)
	, m_iTotalSeconds(0)
	, m_hPlayWnd(NULL)
	, m_bFullScreen(FALSE)
	, m_iFileIndex(-1)
	, m_bStep(FALSE)
	, m_bFileRefCreated(NULL)
	, m_bChkAll(FALSE)
{
	m_hPlayEnableIcon =			AfxGetApp()->LoadIcon(IDI_PLAY_ENABLE);
	m_hPlayDisableIcon =		AfxGetApp()->LoadIcon(IDI_PLAY_DISABLE);
	m_hPauseEnableIcon =		AfxGetApp()->LoadIcon(IDI_PAUSE_ENABLE);
	m_hPauseDisableIcon =		AfxGetApp()->LoadIcon(IDI_PAUSE_DISABLE);
	m_hStopEnableIcon =			AfxGetApp()->LoadIcon(IDI_STOP_ENABLE);
	m_hStopDisableIcon =		AfxGetApp()->LoadIcon(IDI_STOP_DISABLE);
	m_hSoundStartIcon=			AfxGetApp()->LoadIcon(IDI_SOUND_ENABLE);
	m_hSoundStopIcon=			AfxGetApp()->LoadIcon(IDI_SOUND_DISABLE);
	m_hGotoHeadDisableIcon =	AfxGetApp()->LoadIcon(IDI_GOTOSTART_DISABLE);
	m_hGotoTailDisableIcon =	AfxGetApp()->LoadIcon(IDI_GOTOEND_DISABLE);
	m_hFastDisableIcon =		AfxGetApp()->LoadIcon(IDI_FASTFORWARD_DISABLE);
	m_hSlowDisableIcon=			AfxGetApp()->LoadIcon(IDI_FASTBACKWARD_DISABLE);
	m_hGotoHeadEnableIcon =		AfxGetApp()->LoadIcon(IDI_GOTOSTART_ENABLE);
	m_hGotoTailEnableIcon =		AfxGetApp()->LoadIcon(IDI_GOTOEND_ENABLE);
	m_hFastEnableIcon =			AfxGetApp()->LoadIcon(IDI_FASTFORWARD_ENABLE);
	m_hSlowEnableIcon =			AfxGetApp()->LoadIcon(IDI_FASTBACKWARD_ENABLE);
	m_hStepEnableIcon=			AfxGetApp()->LoadIcon(IDI_STEP_ENABLE);
	m_hStepDisableIcon =		AfxGetApp()->LoadIcon(IDI_STEP_DISABLE);
	m_hStepBackEnableIcon =		AfxGetApp()->LoadIcon(IDI_STEPBACK_ENABLE);
	m_hStepBackDisableIcon =	AfxGetApp()->LoadIcon(IDI_STEPBACK_DISABLE);
	m_hCaptureIcon	=			AfxGetApp()->LoadIcon(IDI_PIC);
}

/*********************************************************
  Function:	~CDlgPlayLocalFile
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgPlayLocalFile::~CDlgPlayLocalFile()
{
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayLocalFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPlayLocalFile)
	DDX_Control(pDX, IDC_COMBO_LOCAL_FILE_TYPE, m_comboFileType);
	DDX_DateTimeCtrl(pDX, IDC_DATE_LOCAL_START, m_ctDateStart);
	DDX_DateTimeCtrl(pDX, IDC_TIME_LOCAL_START, m_ctTimeStart);
	DDX_DateTimeCtrl(pDX, IDC_DATE_LOCAL_STOP, m_ctDateStop);
	DDX_DateTimeCtrl(pDX, IDC_TIME_LOCAL_STOP, m_ctTimeStop);
	DDX_Control(pDX, IDC_LIST_LOCAL_FILE, m_listFile);
	DDX_Control(pDX, IDC_STATIC_LOCAL_FILE_WND, m_staticPlayWnd);
	DDX_Control(pDX, IDC_SLIDER_LOCAL_PLAY_PROGRESS, m_sliderPlayProgress);
	DDX_Control(pDX, IDC_SLIDER_LOCAL_VOLUME, m_sliderVolume);
	DDX_Check(pDX, IDC_CHK_ALL, m_bChkAll);
	//}}AFX_DATA_MAP

}


/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgPlayLocalFile, CDialog)
	//{{AFX_MSG_MAP(CDlgPlayLocalFile)	
	ON_BN_CLICKED(IDC_BTN_SEARCH_LOCAL_LIST, OnBnClickedBtnSearchLocalList)
	ON_BN_CLICKED(IDC_BTN_DELETE_LOCAL_FILE, OnBnClickedBtnDeleteLocalFile)
	ON_BN_CLICKED(IDC_BTN_DELETE_ALL_LOCAL_FILE, OnBnClickedBtnDeleteAllLocalFile)
	ON_BN_CLICKED(IDC_BTN_LOCAL_PLAY, OnBnClickedBtnLocalPlay)
	ON_BN_CLICKED(IDC_BTN_LOCAL_STOP, OnBnClickedBtnLocalStop)
	ON_BN_CLICKED(IDC_BTN_LOCAL_SLOW, OnBnClickedBtnLocalSlow)
	ON_BN_CLICKED(IDC_BTN_LOCAL_FAST, OnBnClickedBtnLocalFast)
	ON_BN_CLICKED(IDC_BTN_LOCAL_PIC_SNATCH, OnBnClickedBtnLocalPicSnatch)
	ON_BN_CLICKED(IDC_BTN_LOCAL_STEP_BACK, OnBnClickedBtnLocalStepBack)
	ON_BN_CLICKED(IDC_BTN_LOCAL_STEP_FORWARD, OnBnClickedBtnLocalStepForward)
	ON_BN_CLICKED(IDC_BTN_LOCAL_SOUND, OnBnClickedBtnLocalSound)
	ON_WM_HSCROLL()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_LOCAL_PLAY_PROGRESS, OnReleasedcaptureSliderLocalPlayProgress)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_LOCAL_VOLUME, OnReleasedcaptureSliderLocalVolume)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_UPLOAD_RECORDFILE, OnBtnUploadRecordfile)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()


// CDlgPlayLocalFile message handlers
/*********************************************************
  Function:	SetParentWnd
  Desc:		transmit the handle of parent dialog box
  Input:	hhWnd, pointer to handle array
  Output:	
  Return:	
**********************************************************/
void CDlgPlayLocalFile::SetParentWnd(HWND *hhWnd, int iParentNum)
{
	VERIFY(iParentNum==2);
	m_hPareDlgWnd=hhWnd[0];
	m_hPareTabWnd=hhWnd[1];
}

/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgPlayLocalFile::OnInitDialog()
{
	CDialog::OnInitDialog();

    m_listFile.SetExtendedStyle(m_listFile.GetExtendedStyle()|LVS_EX_FULLROWSELECT);
	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);
	char szLan[128] = {0};
	g_StringLanType(szLan, "文件名称", "File Name");
	m_listFile.InsertColumn(0, szLan,LVCFMT_LEFT,120,-1);

	g_StringLanType(szLan, "大小", "Size");
	m_listFile.InsertColumn(1, szLan,LVCFMT_LEFT,40,-1);

	g_StringLanType(szLan, "类型", "Type");
	m_listFile.InsertColumn(2, szLan, LVCFMT_LEFT, 40, -1);

	g_StringLanType(szLan, "开始时间", "Start time");
	m_listFile.InsertColumn(3, szLan, LVCFMT_LEFT, 120, -1);

	g_StringLanType(szLan, "结束时间", "Stop Time");
	m_listFile.InsertColumn(4, szLan, LVCFMT_LEFT, 120, -1);

	m_hPlayWnd = GetDlgItem(IDC_STATIC_LOCAL_FILE_WND)->m_hWnd;

	InitUI();
	GetDlgItem(IDC_STATIC_LOCAL_FILE_WND)->GetWindowRect(m_rcWnd);
	ScreenToClient(m_rcWnd);
	ShowWindow(SW_SHOW);
	CTime ctCurTime = CTime::GetCurrentTime();
	CTime ctStart(ctCurTime.GetYear(), ctCurTime.GetMonth(), ctCurTime.GetDay(), 0,0,0);
	CTime ctStop(ctCurTime.GetYear(), ctCurTime.GetMonth(), ctCurTime.GetDay(), 23,59,59);
	m_ctDateStart = ctStart;
	m_ctTimeStart = ctStart;
	m_ctDateStop = ctStop;
	m_ctTimeStop = ctStop;
	m_comboFileType.SetCurSel(0);
	
	g_pDlgPlayLocalFile=this;

	UpdateData(FALSE);
	return TRUE;
}

/*********************************************************
  Function:	CheckInitParam
  Desc:		check current device parameters, and initialize dialog box parameters
  Input:	
  Output:	
  Return:	TRUE,check and initialize correctly;FALSE,check failed,not initialized;
**********************************************************/
BOOL CDlgPlayLocalFile::CheckInitParam()
{
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	if (iDeviceIndex == -1)
	{
		UpdateData(FALSE);
		return FALSE;
	}

	//if (iDeviceIndex != m_iDeviceIndex)
	//{
		m_iDeviceIndex = iDeviceIndex;
		m_lLoginID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
		m_iChanCount = g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum;
		//m_lDeviceType = g_struDeviceInfo[m_iDeviceIndex].iDeviceType;
		m_lStartChan = g_struDeviceInfo[m_iDeviceIndex].iStartChan;
	//}
	int iChanIndex = g_pMainDlg->GetCurChanIndex();

	if (iChanIndex != m_iChanIndex)//-1 all channel
	{
		m_iChanIndex = iChanIndex;
	}
//refresh the parameters as below while selecting another device
	m_bPlay=FALSE;
	m_bPause=FALSE;
	m_bSound=FALSE;
	m_iTotalSeconds=0;
	m_bStep=FALSE;
	m_bFileRefCreated=FALSE;
	m_bFullScreen=FALSE;
	m_listFile.DeleteAllItems();
	m_csDeviceIP.Format("%s",g_struDeviceInfo[m_iDeviceIndex].chDeviceIP);//each search acord to only one device

	UpdateData(FALSE); 
	return TRUE;
}

/*********************************************************
  Function:	OnBnClickedBtnSearchLocalList
  Desc:		search response function, searching local files, displaying list
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPlayLocalFile::OnBnClickedBtnSearchLocalList()
{
	UpdateData(TRUE);
	CString m_csDeviceIP;
	CTime tStartTime,tStopTime;
	int iSum = 0;//sum of files that have been searched
	int iType;
	int i,j;

	if (!CheckDate(m_ctDateStart,m_ctDateStop))
	{
		return;
	}
	m_listFile.DeleteAllItems();
	m_iFileIndex = 0;
	tStartTime = CTime(m_ctDateStart.GetYear(),m_ctDateStart.GetMonth(),m_ctDateStart.GetDay(),m_ctTimeStart.GetHour(),m_ctTimeStart.GetMinute(),m_ctTimeStart.GetSecond());
	tStopTime = CTime(m_ctDateStop.GetYear(),m_ctDateStop.GetMonth(),m_ctDateStop.GetDay(),m_ctTimeStop.GetHour(),m_ctTimeStop.GetMinute(),m_ctTimeStop.GetSecond());
	iType = m_comboFileType.GetCurSel();
	if (m_bChkAll)
	{
		iSum = SearchLocalFile(1, 0, tStartTime, tStopTime);
		iSum = iSum + ShowDownloadFile(0, tStartTime, tStopTime);
	}
	else if (m_iChanIndex == -1)
	{//all channel
		for (i=0; i<=m_iChanCount; i++)
		{
			if (iType!=0)
			{
				iSum = iSum + SearchLocalFile(iType, i+m_lStartChan, tStartTime, tStopTime);
			}
			else
			{//all file
				for (j = 1;j<=3;j++)
				{
					iSum = iSum + SearchLocalFile(j, i+m_lStartChan, tStartTime, tStopTime);
				}
			}
		}
	}
	else
	{
		if (iType!=0)
		{
			iSum = SearchLocalFile(iType, m_iChanIndex+m_lStartChan, tStartTime, tStopTime);
		}
		else
		{
			for (j = 1;j<=3;j++)
			{
				iSum = iSum + SearchLocalFile(j, m_iChanIndex+m_lStartChan, tStartTime, tStopTime);
			}
		}
	}
	
	if (iSum > 0)
	{
		SetStopState();
	}
	else
	{
		InitUI();
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Find %d local record files", iSum);
	char szLan[1024] = {0};
	g_StringLanType(szLan, "文件查找结束", "Find the end of file");
	AfxMessageBox(szLan);
	UpdateData(FALSE);	
}

/*********************************************************
  Function:	OnBnClickedBtnDeleteLocalFile
  Desc:		response function of deleting selected local files in list 
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPlayLocalFile::OnBnClickedBtnDeleteLocalFile()
{
	UpdateData(TRUE);

	int iFilePosSel = 0;
	CString csFileName;
	CString csTemp;
	char szLan[1024] = {0};
	
	POSITION  iPos = m_listFile.GetFirstSelectedItemPosition();
	if (iPos == NULL)
	{
		return;
	}
	iFilePosSel = m_listFile.GetNextSelectedItem(iPos);
	csFileName=m_listFile.GetItemText(iFilePosSel,0);
	if (csFileName.GetLength()==0)
	{
		return;
	}
	csTemp.Format("Delete Mp4 szFileName = %s", csFileName.GetBuffer(0));
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, csTemp.GetBuffer(0));
	g_StringLanType(szLan, "确定删除此文件吗?", "Sure to delete the file?");
	if (IDOK!=MessageBox(szLan,"Warning!",IDOK))
	{
		return;
	}
	if (DeleteFile(csFileName))
	{
		m_listFile.DeleteItem(iFilePosSel);
	}
	else
	{
		CString csError;
		g_StringLanType(szLan, "不能删除文件", "Can not delete file");
		csError.Format("不能删除文件:%s!", szLan, csFileName.GetBuffer(0));
		MessageBox(csError);
	}
}

/*********************************************************
  Function:	OnBnClickedBtnDeleteAllLocalFile
  Desc:		delete all video files in the list
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPlayLocalFile::OnBnClickedBtnDeleteAllLocalFile()
{
	int iCount, i;
	CString csFileName;
	char szLan[1024] = {0};

	iCount = m_listFile.GetItemCount();
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "OnBnClickedBtnDeleteAllLocalFile iCount = %d", iCount);
	if (iCount < 1)
	{
		return;
	}
	g_StringLanType(szLan, "确定删除所有文件吗?", "Sure to delete all the files");
	if (IDOK!=MessageBox(szLan,"Warning!",IDOK))
	{
		return;
	}
	for (i = iCount; i > 0; i--)
	{
		csFileName = m_listFile.GetItemText(i-1, 0);
		if (csFileName.GetLength() == 0)
		{
			continue;
		}

		if (DeleteFile(csFileName))
		{
			m_listFile.DeleteItem(i-1);
		}
		else
		{
			CString csError;
			g_StringLanType(szLan, "不能删除文件", "Can not delete file");
			csError.Format("不能删除文件:%s!", szLan, csFileName.GetBuffer(0));
			MessageBox(csError);
		}
	}
}

/*********************************************************
  Function:	OnBnClickedBtnLocalPlay
  Desc:		playback selected local video files
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPlayLocalFile::OnBnClickedBtnLocalPlay()
{
	if (m_bPlay)
	{
		if (m_bStep)
		{
			if (PlayM4_Play(USED_PORT,m_hPlayWnd))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "PlayM4_Play");
			}
			
			SetPlayState();
			m_bStep=FALSE;
		}
		else
		{
			Pause();
		}
		return;
	}

	PlayBack();

	if (m_bPlay)
	{
		SetPlayState();
		Sound(TRUE);
		SetTimer(PLAY_TIMER,TIMER_INTERVAL,NULL);
	}
}

/*********************************************************
  Function:	OnBnClickedBtnLocalStop
  Desc:		suspend play of local video file
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPlayLocalFile::OnBnClickedBtnLocalStop()
{
	if (!m_bPlay)
	{
		return;
	}
	m_sliderPlayProgress.SetPos(0); 
	CString csText;	
	GetDlgItem(IDC_STATIC_LOCAL_PLAY_STATUS)->SetWindowText(csText);
	KillTimer(PLAY_TIMER);
	csText.Format("%d/%d  %02d:%02d:%02d/%02d:%02d:%02d",0,0,0,0,0,0,0,0);
	UpdateData(FALSE);
	Invalidate(TRUE);
	StopPlayBack();
}

/*********************************************************
  Function:	OnBnClickedBtnLocalSlow
  Desc:		response function of slow play 
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPlayLocalFile::OnBnClickedBtnLocalSlow()
{
	PlayM4_Slow(USED_PORT);
}

/*********************************************************
  Function:	OnBnClickedBtnLocalFast
  Desc:		response function of fast play
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPlayLocalFile::OnBnClickedBtnLocalFast()
{
	PlayM4_Fast(USED_PORT);
}

/*********************************************************
  Function:	OnBnClickedBtnLocalPicSnatch
  Desc:		response function of capture
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPlayLocalFile::OnBnClickedBtnLocalPicSnatch()
{
	g_bLocalCapPic=TRUE;
}

/*********************************************************
Function:	OnBnClickedBtnLocalStepBack
Desc:		play forward by frame
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayLocalFile::OnBnClickedBtnLocalStepBack()
{
	if (m_bPause)
	{
		Pause();
	}
	PlayM4_OneByOneBack(USED_PORT);
	m_bStep=TRUE;
	SetPauseState();
}

/*********************************************************
  Function:	OnBnClickedBtnLocalStepForward
  Desc:		play forward in step by frame
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPlayLocalFile::OnBnClickedBtnLocalStepForward()
{
	if (m_bPause)
	{
		Pause();
	}
	PlayM4_OneByOne(USED_PORT);
	m_bStep=TRUE;
	SetPauseState();
}

/*********************************************************
  Function:	OnBnClickedBtnLocalSound
  Desc:		enable audio of playback
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPlayLocalFile::OnBnClickedBtnLocalSound()
{
	Sound(!m_bSound);
}

/*********************************************************
Function:	OnHScroll
Desc:		response function of draging bar by mouse, play corresponding part
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayLocalFile::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (pScrollBar->m_hWnd==m_sliderPlayProgress.m_hWnd&&m_bPlay)
	{
		nPos = m_sliderPlayProgress.GetPos();
		m_sliderPlayProgress.SetPos(nPos);
	}
	else if (pScrollBar->m_hWnd == m_sliderVolume.m_hWnd&&m_bSound)
	{
		nPos = m_sliderVolume.GetPos();
		m_sliderVolume.SetPos(nPos);
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

/*********************************************************
Function:	OnLButtonDblClk
Desc:		double click screen to enlarge image
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayLocalFile::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	if (IsInWnd(point)&&m_bPlay)
	{
		m_bFullScreen=!m_bFullScreen;
		//main interface display or hide
		g_pMainDlg->FullScreen(m_bFullScreen);
		if (m_bFullScreen)
		{
			PlayBackFullScreen();
		}
		else
		{
			PlayBackShowNormal();
		}
		PlayM4_RefreshPlay(USED_PORT);
	}
	CDialog::OnLButtonDblClk(nFlags, point);
}

/*********************************************************
Function:	IsInWnd
Desc:		check whether playback screen double clicked by mouse
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgPlayLocalFile::IsInWnd(CPoint point)
{
	CRect rc;
	GetDlgItem(IDC_STATIC_LOCAL_FILE_WND)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	if (PtInRect(&rc,point))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*********************************************************
  Function:	OnPaint
  Desc:		refresh playback screen
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPlayLocalFile::OnPaint() 
{
	CPaintDC dc(this); 
	CWnd *pWnd=GetDlgItem(IDC_STATIC_LOCAL_FILE_WND);
	pWnd->Invalidate();
	pWnd->UpdateWindow();

	PlayM4_RefreshPlay(USED_PORT);
	// Do not call CDialog::OnPaint() for painting messages
}

/*********************************************************
  Function:	OnTimer
  Desc:		response function of timer
  Input:	
  Output:	
  Return:	
**********************************************************/
#if (_MSC_VER >= 1500)	//vs2008
void CDlgPlayLocalFile::OnTimer(UINT_PTR nIDEvent) 
#else
void CDlgPlayLocalFile::OnTimer(UINT nIDEvent) 
#endif
{
	if (nIDEvent==PLAY_TIMER)
	{
		ShowPlayBackState();
	}
	CDialog::OnTimer(nIDEvent);
}

/*********************************************************
  Function:	ShowPlayBackState
  Desc:		display current playback state
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPlayLocalFile::ShowPlayBackState()
{
	if (m_iTotalSeconds == 0)
	{
		return;
	}

	DWORD nCurSecond=PlayM4_GetPlayedTime(USED_PORT);
	m_sliderPlayProgress.SetPos(nCurSecond*100/m_iTotalSeconds);
	CString csStatus;
	csStatus.Format("%02d:%02d:%02d/%02d:%02d:%02d",\
		nCurSecond/3600,(nCurSecond%3600)/60,nCurSecond%60,\
		m_iTotalSeconds/3600,(m_iTotalSeconds%3600)/60,m_iTotalSeconds%60);
	float fCurPos = PlayM4_GetPlayPos(USED_PORT);
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "PlayM4_GetPlayPos %f", fCurPos);
	if (fCurPos <= 1.00+0.000001 && fCurPos >= 1.00-0.000001)
	{
		OnBnClickedBtnLocalStop();
	}


	GetDlgItem(IDC_STATIC_LOCAL_PLAY_STATUS)->SetWindowText(csStatus);
}

/*********************************************************
  Function:	StopPlayBack
  Desc:		stop playback to release corresponding resource
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPlayLocalFile::StopPlayBack()
{
	m_bPause=FALSE;
	if (m_bPlay)
	{
		m_bPlay=FALSE;
		PlayM4_Stop(USED_PORT);
		PlayM4_CloseFile(USED_PORT);
		if (m_bSound)
		{
			Sound(FALSE);
		}
		SetStopState();
	}
}

/*********************************************************
  Function:	InitUI
  Desc:		initialize UI
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPlayLocalFile::InitUI()
{
	// initialize button
	CButton *pButton;

	m_rcScreen=CRect(0,0,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));
	//initialize scroll
	m_sliderPlayProgress.SetRange(0,100);
	m_sliderPlayProgress.SetPos(0);
	m_sliderVolume.SetRange(0,0xffff);
	m_sliderVolume.SetPos(0x7fff);
	m_sliderPlayProgress.EnableWindow(FALSE);
	m_sliderVolume.EnableWindow(FALSE);

	pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_PLAY); 
	pButton->SetIcon(m_hPlayDisableIcon);
	pButton->EnableWindow(FALSE);

	pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_STOP);
	pButton->SetIcon(m_hStopDisableIcon);
	pButton->EnableWindow(FALSE);

	pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_FAST);
	pButton->SetIcon(m_hFastDisableIcon);
	pButton->EnableWindow(FALSE);

	pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_SLOW);
	pButton->SetIcon(m_hSlowDisableIcon);
	pButton->EnableWindow(FALSE);

	pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_STEP_FORWARD);
	pButton->SetIcon(m_hStepDisableIcon);
	pButton->EnableWindow(FALSE);

	pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_STEP_BACK);
	pButton->SetIcon(m_hStepBackDisableIcon);
	pButton->EnableWindow(FALSE);

	pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_PIC_SNATCH);
	pButton->SetIcon(m_hCaptureIcon);
	pButton->EnableWindow(FALSE);

	pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_SOUND);
	pButton->SetIcon(m_hSoundStopIcon);
	pButton->EnableWindow(FALSE);
}

/*********************************************************
  Function:	CheckDate
  Desc:		check start and stop time
  Input:	tFrom,start time; tTo,stop time;
  Output:	
  Return:	TRUE,correct time;FALSE,timing error;
**********************************************************/
BOOL CDlgPlayLocalFile::CheckDate(CTime tFrom, CTime tTo)
{
	if (tFrom.GetYear() > tTo.GetYear())
	{
		return FALSE;
	}
	else
	{
		if (tFrom.GetYear() == tTo.GetYear())
		{
			if (tFrom.GetMonth() > tTo.GetMonth())
			{
				return FALSE;
			}
			else
			{
				if (tFrom.GetMonth() == tTo.GetMonth())
				{
					if (tFrom.GetDay() > tTo.GetDay())
					{
						return FALSE;
					}
					else
					{
						if (tFrom.GetDay() == tTo.GetDay())
						{
							if (tFrom.GetHour() > tTo.GetHour())
							{
								return FALSE;
							}
							else
							{
								if (tFrom.GetHour() == tTo.GetHour())
								{
									if (tFrom.GetMinute() > tTo.GetMinute())
									{
										return FALSE;
									}
									else
									{
										if (tFrom.GetMinute() == tTo.GetMinute())
										{
											if (tFrom.GetSecond() > tTo.GetSecond())
											{
												return FALSE;
											}
										}//end sec
									}//end min
								}
							}//end hour
						}
					}//end day
				}
			}//end month
		}
	}//end year
	return TRUE;
}

/*********************************************************
  Function:	SearchLocalFile
  Desc:		search local files related to channel
  Input:	iFileType:1-normal,2-alarm,3-download; iChanShowIndex,show channel index;tFrom,start time;tTo,stop time;
  Output:	
  Return:	
**********************************************************/
int CDlgPlayLocalFile::SearchLocalFile(int iFileType,int iChanShowIndex, CTime tFrom, CTime tTo)
{
	int iFindSum=0;
	int j;
	CTime tFileTime;
	char szLan[128] = {0};
	CString sTemp;
	CString csDir, csChildDir, csFindFile, csFileName;
	CFileFind fdDir;
	CFileFind fdRecFile;//record file
	BOOL bFineDir;
	BOOL bFindFile;

	switch (iFileType)
	{
	case 1:
		g_StringLanType(szLan, "正常", "Normal");
		for (j=g_struLocalParam.iStartRecordDriver; j < g_struLocalParam.iEndRecordDriver+1; j++)
		{
			csDir.Format("%c:\\mpeg4record\\*.*", g_pMainDlg->m_cHardDriver[j]);
			bFineDir=fdDir.FindFile(csDir);
			while (bFineDir)
			{
				bFineDir=fdDir.FindNextFile();
				if (fdDir.IsDots())
				{
					continue;
				}
				if (fdDir.IsDirectory())
				{
					csChildDir.Format("%c:\\mpeg4record\\%s",g_pMainDlg->m_cHardDriver[j],fdDir.GetFileName());
					if (m_bChkAll)
					{
						csFindFile.Format("%s\\*.mp4",csChildDir);
					}
					else
					{
						csFindFile.Format("%s\\%s_%02d*.mp4",csChildDir, m_csDeviceIP, iChanShowIndex);
					}
					
					bFindFile=fdRecFile.FindFile(csFindFile);
					while (bFindFile)
					{
						bFindFile = fdRecFile.FindNextFile();
						if (fdRecFile.IsDots())
						{
							continue;
						}
						csFileName.Format("%s\\%s", csChildDir, fdRecFile.GetFileName());
						g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "The finded file name: %s", csFileName);
						fdRecFile.GetCreationTime(tFileTime);
						if (CheckDate(tFrom, tFileTime) && CheckDate(tFileTime, tTo))
						{
							m_listFile.InsertItem(m_iFileIndex,csFileName,0);
							sTemp.Format("%d",fdRecFile.GetLength());
							m_listFile.SetItemText(m_iFileIndex,1,sTemp);
							m_listFile.SetItemText(m_iFileIndex,2,szLan);
							m_listFile.SetItemText(m_iFileIndex,3,tFileTime.Format("%Y%m%d %H:%M:%S"));
							fdRecFile.GetLastWriteTime(tFileTime);
							m_listFile.SetItemText(m_iFileIndex,4,tFileTime.Format("%Y%m%d %H:%M:%S"));
							iFindSum++;
							m_iFileIndex++;
						}
					}//end while find file
				}
			}//end while find dir
		}
		break;
	case 2:

		break;
	case 3://件download record files from device
		iFindSum = ShowDownloadFile(iChanShowIndex, tFrom, tTo);
		break;
	default:
		iFindSum = 0;
		break;
	}
	return iFindSum;
}

/*********************************************************
  Function:	ShowDownloadFile
  Desc:		show current downloaded file
  Input:	iChanShowIndex, channel index corresponding to device;tFrom,start time;tTo,stop time;
  Output:	
  Return:	file number
**********************************************************/
int CDlgPlayLocalFile::ShowDownloadFile(int iChanShowIndex, CTime tFrom, CTime tTo)
{
	//display file title
	char szFileName[200];
	char szChan[4];
	CString sTemp, sTemp1;
	int iFindSum=0;
	WIN32_FIND_DATA struFindFileData;
	HANDLE hFind;
	CTime tFileTime;
	CString	csType;

	if (m_bChkAll)
	{
		strcpy(szFileName,g_struLocalParam.chDownLoadPath);
		strcat(szFileName,"\\");
		strcat(szFileName,"*.mp4");
	}
	else
	{
		sprintf(szChan,"%02d",iChanShowIndex);
		strcpy(szFileName,g_struLocalParam.chDownLoadPath);
		strcat(szFileName,"\\");
		strcat(szFileName,m_csDeviceIP);
		strcat(szFileName,"_");
		strcat(szFileName,szChan);
		strcat(szFileName,"_D*.mp4");
	}

	csType.Format(_T("Download"));
	sTemp1.Format("%s", g_struLocalParam.chDownLoadPath);

	hFind = FindFirstFile(szFileName, &struFindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		FindClose(hFind);
		return 0;
	}
	else
	{
		tFileTime = CTime((const FILETIME&)(struFindFileData.ftCreationTime));
		if (CheckDate( tFrom, tFileTime) && CheckDate(tFileTime, tTo) || m_bChkAll)
		{
			sTemp.Format("%s\\%s",sTemp1,struFindFileData.cFileName);
			m_listFile.InsertItem(m_iFileIndex,sTemp,0);
			sTemp.Format("%d,%03d",struFindFileData.nFileSizeLow/1000, struFindFileData.nFileSizeLow%1000);//1024?
		//	sTemp.Format("%d",iChanShowIndex);
			m_listFile.SetItemText(m_iFileIndex,1,sTemp);
			m_listFile.SetItemText(m_iFileIndex,2,csType);
			m_listFile.SetItemText(m_iFileIndex,3,tFileTime.Format("%Y%m%d %H:%M:%S"));
			tFileTime = CTime((const FILETIME&)(struFindFileData.ftLastWriteTime));
			m_listFile.SetItemText(m_iFileIndex,4,tFileTime.Format("%Y%m%d %H:%M:%S"));
			iFindSum++;
			m_iFileIndex++;
		}
	}
	while (FindNextFile(hFind,&struFindFileData))
	{
		tFileTime = CTime((const FILETIME&)(struFindFileData.ftCreationTime));
		if (CheckDate(tFrom, tFileTime) && CheckDate(tFileTime, tTo) || m_bChkAll)
		{
			sTemp.Format("%s\\%s",sTemp1,struFindFileData.cFileName);
			
			m_listFile.InsertItem(m_iFileIndex,sTemp,0);
			sTemp.Format("%d,%03d",struFindFileData.nFileSizeLow/1000, struFindFileData.nFileSizeLow%1000);//1024
			//sTemp.Format("%d",iChanShowIndex);
			m_listFile.SetItemText(m_iFileIndex,1,sTemp);
			m_listFile.SetItemText(m_iFileIndex,2,csType);
			m_listFile.SetItemText(m_iFileIndex,3,tFileTime.Format("%Y%m%d %H:%M:%S"));
			tFileTime = CTime((const FILETIME&)(struFindFileData.ftLastWriteTime));
			m_listFile.SetItemText(m_iFileIndex,4,tFileTime.Format("%Y%m%d %H:%M:%S"));
			iFindSum++;
			m_iFileIndex++;
		}
	}
	return iFindSum;
}

/*********************************************************
  Function:	SetStopState
  Desc:		change control state of stopping playback
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPlayLocalFile::SetStopState()
{
	CButton *pButton;

	m_sliderPlayProgress.SetPos(0);
	m_sliderPlayProgress.EnableWindow(FALSE);
	m_sliderVolume.EnableWindow(FALSE);

	pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_PLAY);
	pButton->SetIcon(m_hPlayEnableIcon);
	pButton->EnableWindow(TRUE);

	pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_STOP);
	pButton->SetIcon(m_hStopDisableIcon);
	pButton->EnableWindow(FALSE);

	pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_FAST);
	pButton->SetIcon(m_hFastDisableIcon);
	pButton->EnableWindow(FALSE);

	pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_SLOW);
	pButton->SetIcon(m_hSlowDisableIcon);
	pButton->EnableWindow(FALSE);

	pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_STEP_FORWARD);
	pButton->SetIcon(m_hStepDisableIcon);
	pButton->EnableWindow(FALSE);

	pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_STEP_BACK);
	pButton->SetIcon(m_hStepBackDisableIcon);
	pButton->EnableWindow(FALSE);

	pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_PIC_SNATCH);
	pButton->SetIcon(m_hCaptureIcon);
	pButton->EnableWindow(FALSE);

	pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_SOUND);
	pButton->SetIcon(m_hSoundStopIcon);
	pButton->EnableWindow(FALSE);

	pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_STEP_FORWARD);
	pButton->SetIcon(m_hStepDisableIcon);
	pButton->EnableWindow(FALSE);

	UpdateStepBackUI(FALSE);	
}

/*********************************************************
  Function:	UpdateStepBackUI
  Desc:		update step back control state
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPlayLocalFile::UpdateStepBackUI(BOOL bEnable)
{
	m_bFileRefCreated=bEnable;
	CButton *pButton;
	if (m_bFileRefCreated)
	{
		pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_STEP_BACK);
		pButton->SetIcon(m_hStepBackEnableIcon);
		pButton->EnableWindow(TRUE);
	}
	else
	{
		pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_STEP_BACK);
		pButton->SetIcon(m_hStepBackDisableIcon);
		pButton->EnableWindow(FALSE);
	}
}

/*********************************************************
  Function:	SetPlayState
  Desc:		update control state of playback 
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPlayLocalFile::SetPlayState()
{
	CButton *pButton;

	m_sliderPlayProgress.EnableWindow(TRUE);
	m_sliderVolume.EnableWindow(TRUE);

	pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_PLAY);
	pButton->SetIcon(m_hPauseEnableIcon);
	pButton->EnableWindow(TRUE);

	pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_STOP);
	pButton->SetIcon(m_hStopEnableIcon);
	pButton->EnableWindow(TRUE);

	pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_FAST);
	pButton->SetIcon(m_hFastEnableIcon);
	pButton->EnableWindow(TRUE);

	pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_SLOW);
	pButton->SetIcon(m_hSlowEnableIcon);
	pButton->EnableWindow(TRUE);

	pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_PIC_SNATCH);
	pButton->SetIcon(m_hCaptureIcon);
	pButton->EnableWindow(TRUE);

	pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_SOUND);
	if (m_bSound)
	{
		pButton->SetIcon(m_hSoundStartIcon);
	}
	else
	{
		pButton->SetIcon(m_hSoundStopIcon);
	}
	pButton->EnableWindow(TRUE);

	pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_STEP_FORWARD);
	pButton->SetIcon(m_hStepEnableIcon);
	pButton->EnableWindow(TRUE);

}

/*********************************************************
  Function:	SetPauseState
  Desc:		set pause state
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPlayLocalFile::SetPauseState()
{
	CButton *pButton;
	pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_PLAY);
	pButton->SetIcon(m_hPlayEnableIcon);
	pButton->EnableWindow(TRUE);
}

/*********************************************************
  Function:	PlayBack
  Desc:		playback video files
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPlayLocalFile::PlayBack()
{
	int iFilePosSel = 0;
	CString csFileName;//path of video file
	CString csDeviceIP;
	CString csTemp;
	CString sTemp1;
	int nPos = 0;
	char szLan[128] = {0};
	UpdateData(TRUE);
	POSITION  iPos = m_listFile.GetFirstSelectedItemPosition();
	if (iPos == NULL)
	{
		g_StringLanType(szLan, "请选择要播放的文件", "Please select the file to play");
		AfxMessageBox(szLan);
		return;
	}
	iFilePosSel = m_listFile.GetNextSelectedItem(iPos);

	PlayM4_SetFileRefCallBack(USED_PORT,FileRefDone,(DWORD)this);
	csFileName = m_listFile.GetItemText(iFilePosSel,0);
	if (csFileName.GetLength()==0)
	{
		return;
	}
	csTemp.Format("%s",csFileName);
	nPos=csTemp.Find("\\",0);
	while (nPos>=0)
	{
		csDeviceIP.Format("%s",csTemp.Right(csTemp.GetLength()-nPos-1));
		csTemp.Format("%s",csDeviceIP);
		nPos=csTemp.Find("\\",0);
	}
	nPos=csTemp.Find("_",0);
	csDeviceIP.Format("%s",csTemp.Left(nPos));
	m_csDeviceIP.Format("%s",csDeviceIP);//

		//set stream secret key
	if(strcmp(g_sSecretKey, "StreamNotEncrypt") != 0)
	{
		if(!PlayM4_SetSecretKey(USED_PORT, 1, g_sSecretKey, 128))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "PlayM4_SetSecretKey %d", PlayM4_GetLastError(USED_PORT));
		}
	}

	if (!PlayM4_OpenFile(USED_PORT, csFileName.GetBuffer(csFileName.GetLength())))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "PlayM4_OpenFile %d", PlayM4_GetLastError(USED_PORT));
		return;
	}
	sTemp1 = m_listFile.GetItemText(iFilePosSel, 1);
	m_iChanIndex = atoi(sTemp1);
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Play file[%s] m_iChanIndex[%d]", sTemp1, m_iChanIndex);
	m_iTotalSeconds=PlayM4_GetFileTime(USED_PORT);
	if (m_iTotalSeconds<=0)
	{
		PlayM4_CloseFile(USED_PORT);
		g_StringLanType(szLan, "文件大小为0", "File size is 0");
		AfxMessageBox(szLan);
		return;
	}

	if (!PlayM4_SetDisplayCallBack(USED_PORT,DisplayCBFun))
	{
		g_pMainDlg->AddLog(-1, PLAY_FAIL_T, "PlayM4_SetDisplayCallBack err[%d]", PlayM4_GetLastError(USED_PORT));
	}

	if ((m_bPlay=PlayM4_Play(USED_PORT,m_hPlayWnd))==FALSE)
	{
		PlayM4_CloseFile(USED_PORT);
		g_pMainDlg->AddLog(m_iDeviceIndex, PLAY_FAIL_T, "PlayM4_Play err[%d]", PlayM4_GetLastError(USED_PORT));
		return;
	}
}

/*********************************************************
  Function:	Pause
  Desc:		pause or play
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPlayLocalFile::Pause()
{
	if (PlayM4_Pause(USED_PORT,!m_bPause))
	{
		m_bPause=!m_bPause;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "PlayM4_Pause %d", PlayM4_GetLastError(USED_PORT));
	}

	if (m_bPause)
	{
		SetPauseState();
	}
	else
	{
		SetPlayState();
	}
}

/*********************************************************
  Function:	Sound
  Desc:		on or off audio in playback
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPlayLocalFile::Sound(BOOL bSound)
{
	if (!m_bPlay)
	{
		return;
	}

	if (bSound)
	{
		m_bSound=PlayM4_PlaySound(USED_PORT);
		PlayM4_SetVolume(USED_PORT,(WORD)m_sliderVolume.GetPos());
	}
	else
	{
		PlayM4_StopSound();
		m_bSound=FALSE;
	}

	if (m_bSound)
	{
		SetPlaySoundState();
	}
	else
	{
		SetStopSoundState();
	}
}

/*********************************************************
  Function:	SetPlaySoundState
  Desc:		enable audio state of play control
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPlayLocalFile::SetPlaySoundState()
{
	CButton *pButton;
	pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_SOUND);
	pButton->SetIcon(m_hSoundStartIcon);
	pButton->EnableWindow(TRUE);

}

/*********************************************************
Function:	SetPlaySoundState
Desc:		turn off audio state of play control
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayLocalFile::SetStopSoundState()
{
	CButton *pButton;
	pButton = (CButton *)GetDlgItem(IDC_BTN_LOCAL_SOUND);
	pButton->SetIcon(m_hSoundStopIcon);
	pButton->EnableWindow(TRUE);
}

/*********************************************************
Function:	PlayBackFullScreen
Desc:		full screen while playback
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayLocalFile::PlayBackFullScreen()
{
	EnableFlashWnd(FALSE);
	CRect rc,rcClient;
	::GetWindowRect(m_hPareDlgWnd,m_rcPareDlg);

	::GetWindowRect(m_hPareTabWnd,m_rcPareTab);
	::ScreenToClient(m_hPareDlgWnd,(POINT*)(&m_rcPareTab));
	::ScreenToClient(m_hPareDlgWnd,(POINT*)(&m_rcPareTab)+1);

	::GetWindowRect(m_hWnd,m_rcParent);
	::ScreenToClient(m_hPareTabWnd,(POINT*)(&m_rcParent));
	::ScreenToClient(m_hPareTabWnd,(POINT*)(&m_rcParent)+1);


	::SetWindowPos(m_hPareDlgWnd,NULL,m_rcScreen.left-SCREEN_EDGE,m_rcScreen.top-SCREEN_EDGE,m_rcScreen.Width()+2*SCREEN_EDGE,m_rcScreen.Height()+2*SCREEN_EDGE,SWP_SHOWWINDOW);

	::GetClientRect(m_hPareDlgWnd,rc);
	::SetWindowPos(m_hPareTabWnd,NULL,rc.left,rc.top,rc.Width(),rc.Height(),SWP_SHOWWINDOW);

	::GetClientRect(m_hPareTabWnd,rc);
	::SetWindowPos(m_hWnd,NULL,rc.left,rc.top,rc.Width(),rc.Height(),SWP_SHOWWINDOW);

	GetDlgItem(IDC_STATIC_LOCAL_FILE_WND)->GetClientRect(rcClient);
	GetDlgItem(IDC_STATIC_LOCAL_FILE_WND)->GetWindowRect(rc);
	int iEdge=(rc.Width()-rcClient.Width())/2;
	rc=m_rcScreen;
	rc.left-=iEdge;
	rc.right+=iEdge;
	rc.top-=iEdge;
	rc.bottom+=iEdge;
	this->ScreenToClient(rc);
	::SetWindowPos(GetDlgItem(IDC_STATIC_LOCAL_FILE_WND)->m_hWnd,NULL,rc.left,rc.top,rc.Width(),rc.Height(),SWP_SHOWWINDOW);
	Invalidate(FALSE);
	UpdateWindow();	
}

/*********************************************************
  Function:	PlayBackShowNormal
  Desc:		return to original interface of playback
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPlayLocalFile::PlayBackShowNormal()
{

	GetDlgItem(IDC_STATIC_LOCAL_FILE_WND)->SetWindowPos(NULL,m_rcWnd.left,m_rcWnd.top,m_rcWnd.Width(),m_rcWnd.Height(),SWP_SHOWWINDOW);
	::SetWindowPos(m_hWnd,NULL,m_rcParent.left,m_rcParent.top,m_rcParent.Width(),m_rcParent.Height(),SWP_SHOWWINDOW);
	::SetWindowPos(m_hPareTabWnd,NULL,m_rcPareTab.left,m_rcPareTab.top,m_rcPareTab.Width(),m_rcPareTab.Height(),SWP_SHOWWINDOW);
	::SetWindowPos(m_hPareDlgWnd,NULL,m_rcPareDlg.left,m_rcPareDlg.top,m_rcPareDlg.Width(),m_rcPareDlg.Height(),SWP_SHOWWINDOW);
	EnableFlashWnd(TRUE);
	Invalidate(FALSE);
	UpdateWindow();
}

/*********************************************************
  Function:	EnableFlashWnd
  Desc:		refresh control state
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPlayLocalFile::EnableFlashWnd(BOOL bEnable)
{
	if (bEnable)
	{
		//THE same to multiplay
		GetDlgItem(IDC_STATIC_LOCAL_PLAY_STATUS)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_BTN_LOCAL_PLAY)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_BTN_LOCAL_STOP)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_BTN_LOCAL_SLOW)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_BTN_LOCAL_FAST)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_BTN_LOCAL_SOUND)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_VOLUME_SLIDER)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_DATE_LOCAL_START)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_DATE_LOCAL_STOP)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_TIME_LOCAL_STOP)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_TIME_LOCAL_START)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_COMBO_LOCAL_FILE_TYPE)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_BTN_SEARCH_LOCAL_LIST)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_SLIDER_LOCAL_PLAY_PROGRESS)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_BTN_LOCAL_PIC_SNATCH)->ModifyStyle(0,WS_VISIBLE,0);

		//the only for single play
		GetDlgItem(IDC_LIST_LOCAL_FILE)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_BTN_LOCAL_STEP_FORWARD)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_BTN_LOCAL_STEP_BACK)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_BTN_DELETE_ALL_LOCAL_FILE)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_BTN_DELETE_LOCAL_FILE)->ModifyStyle(0,WS_VISIBLE,0);
	}
	else
	{
		//THE same to multiplay
		GetDlgItem(IDC_STATIC_LOCAL_PLAY_STATUS)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_BTN_LOCAL_PLAY)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_BTN_LOCAL_STOP)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_BTN_LOCAL_SLOW)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_BTN_LOCAL_FAST)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_BTN_LOCAL_SOUND)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_VOLUME_SLIDER)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_SLIDER_LOCAL_PLAY_PROGRESS)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_DATE_LOCAL_START)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_DATE_LOCAL_STOP)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_TIME_LOCAL_STOP)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_TIME_LOCAL_START)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_COMBO_LOCAL_FILE_TYPE)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_BTN_SEARCH_LOCAL_LIST)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_BTN_LOCAL_PIC_SNATCH)->ModifyStyle(WS_VISIBLE,0,0);

		//the only for single play
		GetDlgItem(IDC_LIST_LOCAL_FILE)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_BTN_LOCAL_STEP_FORWARD)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_BTN_LOCAL_STEP_BACK)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_BTN_DELETE_ALL_LOCAL_FILE)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_BTN_DELETE_LOCAL_FILE)->ModifyStyle(WS_VISIBLE,0,0);
	}	
}

void CDlgPlayLocalFile::OnReleasedcaptureSliderLocalPlayProgress(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nPos = 0;
	nPos = m_sliderPlayProgress.GetPos();
	m_sliderPlayProgress.SetPos(nPos);
	if (!PlayM4_SetPlayedTimeEx(USED_PORT, m_iTotalSeconds*nPos*10))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "PlayM4_SetPlayedTimeEx %d", m_iTotalSeconds*nPos*10);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "PlayM4_SetPlayedTimeEx %d", m_iTotalSeconds*nPos*10);
	}
	*pResult = 0;
}

void CDlgPlayLocalFile::OnReleasedcaptureSliderLocalVolume(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nPos = 0; 
	nPos = m_sliderVolume.GetPos();
	m_sliderVolume.SetPos(nPos);
	if (!PlayM4_SetVolume(USED_PORT,(WORD)m_sliderVolume.GetPos()))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "PlayM4_SetVolume");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "PlayM4_SetVolume");
	}
		
	*pResult = 0;
}

void CDlgPlayLocalFile::OnBtnUploadRecordfile() 
{
    // TODO: Add your control notification handler code here
    CDlgUploadFile dlg;
    dlg.m_lUserID = m_lLoginID;
    dlg.m_iDevIndex = m_iDeviceIndex;
    dlg.DoModal();
}