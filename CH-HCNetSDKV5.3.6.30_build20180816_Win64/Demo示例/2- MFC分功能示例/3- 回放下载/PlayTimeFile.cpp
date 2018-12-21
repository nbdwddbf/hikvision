// PlayTimeFile.cpp : implementation file
//

#include "stdafx.h"
#include "PlayBack.h"
#include "PlayTimeFile.h"
#include "HCNetSDK.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlayTimeFile property page

IMPLEMENT_DYNCREATE(CPlayTimeFile, CPropertyPage)

CPlayTimeFile::CPlayTimeFile() : CPropertyPage(CPlayTimeFile::IDD)
{
	//{{AFX_DATA_INIT(CPlayTimeFile)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hPlayHandle = -1;
	m_IsDownloading = FALSE;
	m_lDownloadHandle = -1;;
	m_IsPlaying = FALSE;
	m_IsPause = FALSE;
	m_bChangeSpeed = FALSE;
	m_bIsSaving = FALSE;

	m_hPlayEnableIcon =			AfxGetApp()->LoadIcon(IDI_PLAY_ENABLE);
	m_hPlayDisableIcon =		AfxGetApp()->LoadIcon(IDI_PLAY_DISABLE);
	m_hPauseEnableIcon =		AfxGetApp()->LoadIcon(IDI_PAUSE_ENABLE);
	m_hPauseDisableIcon =		AfxGetApp()->LoadIcon(IDI_PAUSE_DISABLE);
	m_hStopEnableIcon =			AfxGetApp()->LoadIcon(IDI_STOP_ENABLE);
	m_hStopDisableIcon =		AfxGetApp()->LoadIcon(IDI_STOP_DISABLE);
	m_hFastDisableIcon =		AfxGetApp()->LoadIcon(IDI_FASTFORWARD_DISABLE);
	m_hFastEnableIcon =			AfxGetApp()->LoadIcon(IDI_FASTFORWARD_ENABLE);
	m_hSlowDisableIcon=			AfxGetApp()->LoadIcon(IDI_FASTBACKWARD_DISABLE);
	m_hSlowEnableIcon =			AfxGetApp()->LoadIcon(IDI_FASTBACKWARD_ENABLE);
}

CPlayTimeFile::~CPlayTimeFile()
{
}

void CPlayTimeFile::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlayTimeFile)
	DDX_Control(pDX, IDC_TIME_START_TIME, m_ctrlTimeStart);
	DDX_Control(pDX, IDC_TIME_END_TIME, m_ctrlTimeStop);
	DDX_Control(pDX, IDC_DATE_END_TIME, m_ctrlDateStop);
	DDX_Control(pDX, IDC_DATE_START_TIME, m_ctrlDateStart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlayTimeFile, CPropertyPage)
	//{{AFX_MSG_MAP(CPlayTimeFile)
	ON_BN_CLICKED(IDC_BUTTON_PLAY_BYTIME, OnBtnPlayBytime)
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD, OnBtnDownloadByTime)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BUTTON_STOP_BYTIME, OnBtnStopTime)
	ON_BN_CLICKED(IDC_BUTTON_FAST_BYTIME, OnBtnFast)
	ON_BN_CLICKED(IDC_BUTTON_SLOW_BYTIME, OnBtnSlow)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayTimeFile message handlers



BOOL CPlayTimeFile::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	InitUI();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPlayTimeFile::InitUI()
{
	// 初始化按钮
	CButton *pButton;
	
	pButton = (CButton *)GetDlgItem(IDC_BUTTON_PLAY_BYTIME);
	pButton->SetIcon(m_hPlayEnableIcon);
	pButton->EnableWindow(TRUE);
	
	pButton = (CButton *)GetDlgItem(IDC_BUTTON_STOP_BYTIME);
	pButton->SetIcon(m_hStopDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_BUTTON_FAST_BYTIME);
	pButton->SetIcon(m_hFastDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_BUTTON_SLOW_BYTIME);
	pButton->SetIcon(m_hSlowDisableIcon);
	pButton->EnableWindow(FALSE);
	
	
}


//播放暂停键
void CPlayTimeFile::OnBtnPlayBytime() 
{
	// TODO: Add your control notification handler code here
	//获取查找的时间段
	if(m_hPlayHandle == -1)   //没有播放
	{
		NET_DVR_TIME StartTime;
		NET_DVR_TIME StopTime;
		
		GetStartStopTime(StartTime,StopTime);
		
		//当前选中设备和通道
//		int iCurDevice = g_pMainDlg->m_iCurDeviceIndex;
//		int iCurChannel = g_pMainDlg->m_iCurChanIndex;
		int iCurChanIndex = g_pMainDlg->m_iCurChanIndex;
        int iCurChannel = g_pMainDlg->m_struDeviceInfo.struChanInfo[iCurChanIndex].iChanIndex;
		
		if(iCurChannel == -1)   //未选中通道
		{
			MessageBox("请选择一个通道");
			return;
		}
		//Login ID
		//LONG LoginID = g_struDevInfo[iCurDevice].lLoginID;
		LONG LoginID = g_pMainDlg->m_struDeviceInfo.lLoginID;
		//播放窗口句柄
		HWND hPlayWnd = GetDlgItem(IDC_STATIC_PLAY_WND_TIME)->GetSafeHwnd();
		
		m_hPlayHandle = NET_DVR_PlayBackByTime(LoginID,iCurChannel,&StartTime,&StopTime,hPlayWnd);
		if(-1 == m_hPlayHandle)
		{
			MessageBox("回放失败");
			return;
		}
		
		if(!NET_DVR_PlayBackControl(m_hPlayHandle,NET_DVR_PLAYSTART,0,NULL))
		{
			MessageBox("回放控制失败");
			return;
		}
		SetTimer(PLAYBYTIME_TIMER,500,NULL);
		SetPlayState(PLAY_NORMAL);
	}
	else
	{
		if(FALSE == m_IsPause) //正在播放，暂停
		{
			if(m_bChangeSpeed)
			{
                NET_DVR_PlayBackControl(m_hPlayHandle,NET_DVR_PLAYNORMAL,0,NULL);
				m_bChangeSpeed = FALSE;

			}
			NET_DVR_PlayBackControl(m_hPlayHandle,NET_DVR_PLAYPAUSE,0,NULL);
			m_IsPause = TRUE;
			SetPlayState(PLAY_PAUSE);

		}
		else                   //暂停，重新播放
		{
			if(m_bChangeSpeed)
			{
                NET_DVR_PlayBackControl(m_hPlayHandle,NET_DVR_PLAYNORMAL,0,NULL);
				m_bChangeSpeed = FALSE;
				
			}
            NET_DVR_PlayBackControl(m_hPlayHandle,NET_DVR_PLAYRESTART,0,NULL);
			m_IsPause = FALSE;
			SetPlayState(PLAY_NORMAL);
		}

		//if(TRUE == m_IsPause)  //暂停时，重新播放
	}
}


void CPlayTimeFile::OnBtnDownloadByTime() 
{
	if(m_IsDownloading == FALSE)
	{
		
		//获取查找的时间段
		NET_DVR_TIME StartTime;
		NET_DVR_TIME StopTime;
		
		GetStartStopTime(StartTime,StopTime);
		
		//当前选中设备和通道
//		int iCurDevice = g_pMainDlg->m_iCurDeviceIndex;
		int iCurChanIndex = g_pMainDlg->m_iCurChanIndex;
        int iCurChannel = g_pMainDlg->m_struDeviceInfo.struChanInfo[iCurChanIndex].iChanIndex;
		
		if(iCurChannel == -1)   //未选中通道
		{
			MessageBox("请选择一个通道");
			return;
		}
		//Login ID
//		LONG LoginID = g_struDevInfo[iCurDevice].lLoginID;
		LONG LoginID = g_pMainDlg->m_struDeviceInfo.lLoginID;
		char fName[100]={0};
		sprintf(fName,"download_%d%02d%02d%02d%02d%02d.mp4",StartTime.dwYear,StartTime.dwMonth,StartTime.dwDay,StartTime.dwHour,StartTime.dwMinute,StartTime.dwSecond);
		m_lDownloadHandle = NET_DVR_GetFileByTime(LoginID,iCurChannel,&StartTime,&StopTime,fName);
		if(m_lDownloadHandle == -1)
		{
			MessageBox("下载失败");
			return;
		}
		if(NET_DVR_PlayBackControl(m_lDownloadHandle,NET_DVR_PLAYSTART,0,NULL))
		{
			m_IsDownloading = TRUE;
			SetTimer(DOWNBYTIME_TIMER,500,NULL);
			GetDlgItem(IDC_BUTTON_DOWNLOAD)->SetWindowText("停止");
		}
	}
	else
	{
		NET_DVR_StopGetFile(m_lDownloadHandle);
		m_lDownloadHandle = -1;
		m_IsDownloading = FALSE;
		GetDlgItem(IDC_BUTTON_DOWNLOAD)->SetWindowText("下载");
		KillTimer(DOWNBYTIME_TIMER);
	}
}

void CPlayTimeFile::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	if(m_hPlayHandle == -1)
	{
		MessageBox("先播放");
		return;
	}

	char RecName[256] = {0};
	
	CTime CurTime = CTime::GetCurrentTime();;
	sprintf(RecName,"save_%04d%02d%02d%02d%02d%02d.mp4",CurTime.GetYear(),CurTime.GetMonth(),CurTime.GetDay(), \
		CurTime.GetHour(),CurTime.GetMinute(),CurTime.GetSecond());

	if(!m_bIsSaving)
	{
        if(!NET_DVR_PlayBackSaveData(m_hPlayHandle,RecName))
		{
			MessageBox("保存失败");
			return;
		}
		m_bIsSaving = TRUE;
		GetDlgItem(IDC_BUTTON_SAVE)->SetWindowText("停止保存");
	}
	else
	{
		NET_DVR_StopPlayBackSave(m_hPlayHandle);
		m_bIsSaving = FALSE;
		GetDlgItem(IDC_BUTTON_SAVE)->SetWindowText("保存");
	}
	

}

void CPlayTimeFile::GetStartStopTime(NET_DVR_TIME &StartDayTime, NET_DVR_TIME &StopDayTime)
{
    CTime StartDay,StartTime;
	CTime StopDay,StopTime;
	
	m_ctrlDateStart.GetTime(StartDay);
	m_ctrlTimeStart.GetTime(StartTime);
	m_ctrlDateStop.GetTime(StopDay);
	m_ctrlTimeStop.GetTime(StopTime);
	
	
	StartDayTime.dwYear = StartDay.GetYear();
	StartDayTime.dwMonth = StartDay.GetMonth();
    StartDayTime.dwDay = StartDay.GetDay();
    StartDayTime.dwHour = StartTime.GetHour();
	StartDayTime.dwMinute = StartTime.GetMinute();
	StartDayTime.dwSecond = StartTime.GetSecond();
	
	StopDayTime.dwYear = StopDay.GetYear();
	StopDayTime.dwMonth = StopDay.GetMonth();
    StopDayTime.dwDay = StopDay.GetDay();
    StopDayTime.dwHour = StopTime.GetHour();
	StopDayTime.dwMinute = StopTime.GetMinute();
	StopDayTime.dwSecond = StopTime.GetSecond();
}

void CPlayTimeFile::OnBtnStopTime() 
{
	// TODO: Add your control notification handler code here
	if(m_hPlayHandle >= 0)
	{
		//停止播放
        NET_DVR_StopPlayBack(m_hPlayHandle);
		m_hPlayHandle = -1;
		m_IsPlaying = FALSE;
		m_IsPause = FALSE;
	    m_bChangeSpeed = FALSE;
		GetDlgItem(IDC_BUTTON_PLAY_BYTIME)->SetWindowText("播放");
		//停止保存
		NET_DVR_StopPlayBackSave(m_hPlayHandle);
		m_bIsSaving = FALSE;
		GetDlgItem(IDC_BUTTON_SAVE)->SetWindowText("保存");
		GetDlgItem(IDC_STATIC_PLAY_WND_TIME)->Invalidate();
        SetPlayState(PLAY_STOP);
	}
	
}

void CPlayTimeFile::OnBtnFast() 
{
	// TODO: Add your control notification handler code here
	if(m_hPlayHandle >= 0 && !m_IsPause)
	{
		NET_DVR_PlayBackControl(m_hPlayHandle,NET_DVR_PLAYFAST,0,NULL);
		m_bChangeSpeed = TRUE;
	}
	
}

void CPlayTimeFile::OnBtnSlow() 
{
	// TODO: Add your control notification handler code here
	if(m_hPlayHandle >= 0 && !m_IsPause)
	{
		NET_DVR_PlayBackControl(m_hPlayHandle,NET_DVR_PLAYSLOW,0,NULL);
		m_bChangeSpeed = TRUE;
	}
}

void CPlayTimeFile::OnTimer(UINT_PTR nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	switch(nIDEvent)
	{
	case PLAYBYTIME_TIMER:
		{
			DWORD pos;
			NET_DVR_PlayBackControl(m_hPlayHandle,NET_DVR_PLAYGETPOS,0,&pos);
			break;
		}
	case DOWNBYTIME_TIMER:
		{
			DWORD pos;
			pos = NET_DVR_GetDownloadPos(m_lDownloadHandle);
			if(pos == 100)
			{
				NET_DVR_StopGetFile(m_lDownloadHandle);
				m_IsDownloading = FALSE;
				m_lDownloadHandle = -1;
				GetDlgItem(IDC_BUTTON_DOWNLOAD)->SetWindowText("下载");
				KillTimer(DOWNBYTIME_TIMER);
				MessageBox("下载结束");
			}
			else if(pos == 200)
			{
				MessageBox("下载异常");
				NET_DVR_StopGetFile(m_lDownloadHandle);
				m_IsDownloading = FALSE;
				m_lDownloadHandle = -1;
				GetDlgItem(IDC_BUTTON_DOWNLOAD)->SetWindowText("下载");
				KillTimer(DOWNBYTIME_TIMER);
			}
			break;
		}
	default:
		break;
	}
	CPropertyPage::OnTimer(nIDEvent);
}

void CPlayTimeFile::SetPlayState(int iState)
{
	CButton *pButton;
    switch(iState)
	{
	case PLAY_STOP:
		pButton = (CButton *)GetDlgItem(IDC_BUTTON_PLAY_BYTIME);
		pButton->SetIcon(m_hPlayEnableIcon);
		pButton->EnableWindow(TRUE);
		
		pButton = (CButton *)GetDlgItem(IDC_BUTTON_STOP_BYTIME);
		pButton->SetIcon(m_hStopDisableIcon);
		pButton->EnableWindow(FALSE);
		
		pButton = (CButton *)GetDlgItem(IDC_BUTTON_FAST_BYTIME);
		pButton->SetIcon(m_hFastDisableIcon);
		pButton->EnableWindow(FALSE);
		
		pButton = (CButton *)GetDlgItem(IDC_BUTTON_SLOW_BYTIME);
		pButton->SetIcon(m_hSlowDisableIcon);
		pButton->EnableWindow(FALSE);
		
		
		break;
	case PLAY_NORMAL:
		pButton = (CButton *)GetDlgItem(IDC_BUTTON_PLAY_BYTIME);
		pButton->SetIcon(m_hPauseEnableIcon);
		pButton->EnableWindow(TRUE);
		
		pButton = (CButton *)GetDlgItem(IDC_BUTTON_STOP_BYTIME);
		pButton->SetIcon(m_hStopEnableIcon);
		pButton->EnableWindow(TRUE);
		
		pButton = (CButton *)GetDlgItem(IDC_BUTTON_FAST_BYTIME);
		pButton->SetIcon(m_hFastEnableIcon);
		pButton->EnableWindow(TRUE);
		
		pButton = (CButton *)GetDlgItem(IDC_BUTTON_SLOW_BYTIME);
		pButton->SetIcon(m_hSlowEnableIcon);
		pButton->EnableWindow(TRUE);
		
		break;
	case PLAY_PAUSE:
		pButton = (CButton *)GetDlgItem(IDC_BUTTON_PLAY_BYTIME);
		pButton->SetIcon(m_hPlayEnableIcon);
		pButton->EnableWindow(TRUE);
		break;
	case PLAY_FAST:
		break;
	case PLAY_SLOW:
		break;
	default:
		break;
	}
}
