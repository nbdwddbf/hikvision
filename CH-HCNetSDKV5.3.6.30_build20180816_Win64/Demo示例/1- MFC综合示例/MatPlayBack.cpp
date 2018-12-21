// MatPlayBack.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "MatPlayBack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMatPlayBack dialog
#define GETSTATE_TIMER WM_USER+1

CMatPlayBack::CMatPlayBack(CWnd* pParent /*=NULL*/)
	: CDialog(CMatPlayBack::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMatPlayBack)
	m_PlayBackName = _T("");
	m_PlayBackIP = _T("172.7.160.2");
	m_PlayBackPass = _T("12345");
	m_PlayBackChan = 1;
	m_PlayBackPort = 8000;
	m_PlayBackUser = _T("admin");
	m_PlayStatus = _T("");
	m_strDnnsAddr = _T("");
	m_strDdnsName = _T("");
	m_wDdnsPort = 0;
	m_strStreamID = _T("");
	m_dwSubWinNo = 0;
	m_dwWallNo = 0;
	m_dwWinNo = 0;
	m_csDecodeChanTitle = _T("");
	//}}AFX_DATA_INIT
	m_hPlayEnableIcon =			AfxGetApp()->LoadIcon(IDI_PLAY_ENABLE);
	m_hPlayDisableIcon =		AfxGetApp()->LoadIcon(IDI_PLAY_DISABLE);
	m_hPauseEnableIcon =		AfxGetApp()->LoadIcon(IDI_PAUSE_ENABLE);
	m_hPauseDisableIcon =		AfxGetApp()->LoadIcon(IDI_PAUSE_DISABLE);
	m_hStopEnableIcon =			AfxGetApp()->LoadIcon(IDI_STOP_ENABLE);
	m_hStopDisableIcon =		AfxGetApp()->LoadIcon(IDI_STOP_DISABLE);
	m_hSoundStartIcon=			AfxGetApp()->LoadIcon(IDI_SOUND_ENABLE);
	m_hSoundStopIcon=			AfxGetApp()->LoadIcon(IDI_SOUND_DISABLE);
	m_hFastDisableIcon =		AfxGetApp()->LoadIcon(IDI_FASTFORWARD_DISABLE);
	m_hSlowDisableIcon=			AfxGetApp()->LoadIcon(IDI_FASTBACKWARD_DISABLE);
	m_hFastEnableIcon =			AfxGetApp()->LoadIcon(IDI_FASTFORWARD_ENABLE);
	m_hSlowEnableIcon =			AfxGetApp()->LoadIcon(IDI_FASTBACKWARD_ENABLE);
	m_hStepEnableIcon=			AfxGetApp()->LoadIcon(IDI_STEP_ENABLE);
	m_hStepDisableIcon =		AfxGetApp()->LoadIcon(IDI_STEP_DISABLE);

	m_bSound = FALSE;
	m_bPlay = FALSE;
	m_bPause = FALSE;

//	memset(&m_struState, 0, sizeof(m_struState));

}


void CMatPlayBack::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMatPlayBack)
	DDX_Control(pDX, IDC_COMBO_DDNS_SERVER_TYPE, m_comboDdnsServerType);
	DDX_Control(pDX, IDC_COMBO_CHANNEL_TYPE, m_comboChannelType);
	DDX_Control(pDX, IDC_COMBO_DEV_ADDRESS_TYPE, m_comboDevAddrType);
	DDX_Control(pDX, IDC_COMBODECCHAN, m_DecChanCombo);
	DDX_Control(pDX, IDC_PROGRESS_SLIDER, m_ctlProgress);
	DDX_Control(pDX, IDC_DATETIMEPICKER4, m_StopTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER3, m_StopDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_StartTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_StartDate);
	DDX_Text(pDX, IDC_EDITBACKNAME, m_PlayBackName);
	DDX_Text(pDX, IDC_EDITIP, m_PlayBackIP);
	DDX_Text(pDX, IDC_EDITPASSWD, m_PlayBackPass);
	DDX_Text(pDX, IDC_EDITCHAN, m_PlayBackChan);
	DDX_Text(pDX, IDC_EDITPORT, m_PlayBackPort);
	DDX_Text(pDX, IDC_EDITUSER, m_PlayBackUser);
	DDX_Text(pDX, IDC_PLAYSTATUS, m_PlayStatus);
	DDX_Text(pDX, IDC_EDIT_DDNS_ADDRESS, m_strDnnsAddr);
	DDX_Text(pDX, IDC_EDIT_DDNS_NAME, m_strDdnsName);
	DDX_Text(pDX, IDC_EDIT_DDNS_PORT, m_wDdnsPort);
	DDX_Text(pDX, IDC_EDIT_STREAM_ID, m_strStreamID);
	DDX_Text(pDX, IDC_EDIT_CYCLE_SUBWINNO2, m_dwSubWinNo);
	DDX_Text(pDX, IDC_EDIT_CYCLE_WALLNO, m_dwWallNo);
	DDX_Text(pDX, IDC_EDIT_CYCLE_WINNO2, m_dwWinNo);
	DDX_Text(pDX, IDC_STATIC_PLAYBACK_DECODECHAN, m_csDecodeChanTitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMatPlayBack, CDialog)
	//{{AFX_MSG_MAP(CMatPlayBack)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_FAST, OnFast)
	ON_BN_CLICKED(IDC_PLAY_FILE, OnPlayFile)
	ON_BN_CLICKED(IDC_SLOW, OnSlow)
	ON_BN_CLICKED(IDC_SOUND, OnSound)
	ON_BN_CLICKED(IDC_STEP, OnStep)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_RADIONAME, OnRadioname)
	ON_BN_CLICKED(IDC_RADIOTIME, OnRadiotime)
	ON_BN_CLICKED(IDC_SETUP, OnSetup)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_PROGRESS_SLIDER, OnReleasedcaptureProgressSlider)
	ON_BN_CLICKED(IDC_STOPSOUND, OnStopsound)
	ON_CBN_SELCHANGE(IDC_COMBO_DEV_ADDRESS_TYPE, OnSelchangeComboDevAddressType)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL_TYPE, OnSelchangeComboChannelType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatPlayBack message handlers

void CMatPlayBack::F_InitUI()
{
	// 初始化按钮
	CButton *pButton;
	
	pButton = (CButton *)GetDlgItem(IDC_PLAY_FILE);
	pButton->SetIcon(m_hPlayDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_STOP);
	pButton->SetIcon(m_hStopDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_FAST);
	pButton->SetIcon(m_hFastDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_SLOW);
	pButton->SetIcon(m_hSlowDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_STEP);
	pButton->SetIcon(m_hStepDisableIcon);
	pButton->EnableWindow(FALSE);
	
    pButton = (CButton *)GetDlgItem(IDC_SOUND);
    //if(m_bSound)
    pButton->SetIcon(m_hSoundStartIcon);
    //else
    pButton = (CButton *)GetDlgItem(IDC_STOPSOUND);
    pButton->SetIcon(m_hSoundStopIcon);
//	pButton = (CButton *)GetDlgItem(IDC_SOUND);
	//	pButton->SetIcon(m_hSoundStopIcon);
	//	pButton->EnableWindow(FALSE);
	
}

void CMatPlayBack::F_SetStopState()
{
	CButton *pButton;
	
	m_ctlProgress.SetPos(0);
	m_ctlProgress.EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_PLAY_FILE);
	pButton->SetIcon(m_hPlayEnableIcon);
	pButton->EnableWindow(TRUE);
	
	pButton = (CButton *)GetDlgItem(IDC_STOP);
	pButton->SetIcon(m_hStopDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_FAST);
	pButton->SetIcon(m_hFastDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_SLOW);
	pButton->SetIcon(m_hSlowDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_STEP);
	pButton->SetIcon(m_hStepDisableIcon);
	pButton->EnableWindow(FALSE);

    pButton = (CButton *)GetDlgItem(IDC_SOUND);
    //if(m_bSound)
    pButton->SetIcon(m_hSoundStartIcon);
    //else
    pButton = (CButton *)GetDlgItem(IDC_STOPSOUND);
    pButton->SetIcon(m_hSoundStopIcon);
	
//	pButton = (CButton *)GetDlgItem(IDC_SOUND);
	//	pButton->SetIcon(m_hSoundStopIcon);
	//	pButton->EnableWindow(FALSE);	
	
}

void CMatPlayBack::F_SetPlayState() 
{
	m_ctlProgress.EnableWindow(TRUE);

	CButton *pButton;
	
	pButton = (CButton *)GetDlgItem(IDC_PLAY_FILE);
	pButton->SetIcon(m_hPauseEnableIcon);
	pButton->EnableWindow(TRUE);
	
	pButton = (CButton *)GetDlgItem(IDC_STOP);
	pButton->SetIcon(m_hStopEnableIcon);
	pButton->EnableWindow(TRUE);
	
	pButton = (CButton *)GetDlgItem(IDC_FAST);
	pButton->SetIcon(m_hFastEnableIcon);
	pButton->EnableWindow(TRUE);
	
	pButton = (CButton *)GetDlgItem(IDC_SLOW);
	pButton->SetIcon(m_hSlowEnableIcon);
	pButton->EnableWindow(TRUE);
	
	pButton = (CButton *)GetDlgItem(IDC_SOUND);
	//if(m_bSound)
    pButton->SetIcon(m_hSoundStartIcon);
	//else
    pButton = (CButton *)GetDlgItem(IDC_STOPSOUND);
		pButton->SetIcon(m_hSoundStopIcon);
	pButton->EnableWindow(TRUE);
	
	pButton = (CButton *)GetDlgItem(IDC_STEP);
	pButton->SetIcon(m_hStepEnableIcon);
	pButton->EnableWindow(TRUE);
}

void CMatPlayBack::F_SetPauseState()
{
	CButton *pButton;	
	pButton = (CButton *)GetDlgItem(IDC_PLAY_FILE);
	pButton->SetIcon(m_hPlayEnableIcon);
	pButton->EnableWindow(TRUE);
}

void CMatPlayBack::EnableControl(BOOL bEnable)
{
	GetDlgItem(IDC_EDITBACKNAME)->EnableWindow(bEnable);
	GetDlgItem(IDC_DATETIMEPICKER1)->EnableWindow(!bEnable);
	GetDlgItem(IDC_DATETIMEPICKER2)->EnableWindow(!bEnable);
	GetDlgItem(IDC_DATETIMEPICKER3)->EnableWindow(!bEnable);
	GetDlgItem(IDC_DATETIMEPICKER4)->EnableWindow(!bEnable);
}

BOOL CMatPlayBack::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	F_InitUI();
	
	CString tmp;
	char szLan[128] = {0};
	g_StringLanType(szLan, "通道", "Channel");
	for (int i=0; i<m_iChannelNumber; i++)
	{
		tmp.Format("%s %d",szLan, i+m_lStartChan);
		m_DecChanCombo.AddString(tmp);
	}

	m_DecChanCombo.SetCurSel(0);
	m_ctlProgress.SetRange(0, 100);
	m_ctlProgress.SetPos(0);
	m_comboDevAddrType.SetCurSel(0);
	OnSelchangeComboDevAddressType();
	
	m_comboChannelType.SetCurSel(0);
	UpdateData(FALSE);
	OnSelchangeComboChannelType();

	CTime ct = CTime::GetCurrentTime();
	SYSTEMTIME st;
	st.wYear = ct.GetYear();
	st.wMonth = ct.GetMonth();
	st.wDay = ct.GetDay();
	st.wHour = 0;
	st.wMinute = 0;
	st.wSecond = 0;
	m_StartDate.SetTime(&st);
	m_StartTime.SetTime(&st);
	st.wHour = 23;
	st.wMinute = 59;
	st.wSecond = 59;
	m_StopDate.SetTime(&st);
	m_StopTime.SetTime(&st);

	CheckRadioButton(IDC_RADIONAME, IDC_RADIOTIME, IDC_RADIONAME);
	EnableControl(TRUE);
	
	F_SetStopState();
	m_lDeviceID = g_pMainDlg->GetCurDeviceIndex(); 
	m_BUseWinNo = IsDevWinControl(m_lDeviceID); 
	if (m_BUseWinNo)
	{
		m_csDecodeChanTitle = "墙号.子窗口.窗口"; 
		GetDlgItem(IDC_STATIC_PLAYBACK_DECODECHAN)->ShowWindow(SW_HIDE); 		
		GetDlgItem(IDC_EDIT_CYCLE_WALLNO)->ShowWindow(SW_SHOW); 
		GetDlgItem(IDC_EDIT_CYCLE_SUBWINNO2)->ShowWindow(SW_SHOW); 
		GetDlgItem(IDC_EDIT_CYCLE_WINNO2)->ShowWindow(SW_SHOW); 
	}
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

#if (_MSC_VER >= 1500)	//vs2008
void CMatPlayBack::OnTimer(UINT_PTR nIDEvent)
#else
void CMatPlayBack::OnTimer(UINT nIDEvent) 
#endif
{
	CDialog::OnTimer(nIDEvent);
	NET_DVR_MATRIX_DEC_CHAN_STATUS MDStatus;
	CString tmp;
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == GETSTATE_TIMER)
	{
		if (m_bPlay)
		{
			DWORD dwDecChanNum =  m_DecChanCombo.GetCurSel()+m_lStartChan;
			if ( m_BUseWinNo )
			{
				dwDecChanNum = m_dwWinNo + ((m_dwSubWinNo&0xff) << 16) + ((m_dwWallNo&0xff) << 24); 
			}
 			memset(&MDStatus, 0, sizeof(MDStatus));
 			if (!NET_DVR_MatrixGetDecChanStatus(m_lServerID, dwDecChanNum, &MDStatus))
 			{
 				tmp.Format("Error: NET_DVR_MatrixGetDecChanStatus = %d", NET_DVR_GetLastError());
 				//AfxMessageBox(tmp);
 			}
 			else
 			{
 				if (MDStatus.dwIsLinked < 3)
 				{
 					OutputDebugString("Please wait, decoding has not started!");
 				}
 				else
 				{
 					UpdateData(TRUE);
 					memset(&m_struState, 0, sizeof(m_struState));
 					if (!NET_DVR_MatrixGetRemotePlayStatus(m_lServerID, dwDecChanNum, &m_struState))
 					{
 						tmp.Format("Error: NET_DVR_MatrixGetRemotePlayStatus = %d", NET_DVR_GetLastError());
 						OutputDebugString(tmp);
 					}
 					else
 					{
 						m_PlayStatus.Format("Pos: %u/%u  Time: %u/%u  Frame: %u",
 							m_struState.dwCurMediaFilePosition, m_struState.dwCurMediaFileLen, 
							m_struState.dwCurPlayTime, m_struState.dwCurMediaFileDuration, 
							m_struState.dwCurMediaFIleFrames);
 
 						if (m_struState.dwCurMediaFileDuration > 0)
 						{
 							m_ctlProgress.SetPos((m_struState.dwCurPlayTime * 100) / m_struState.dwCurMediaFileDuration);
 						}
 
  						if (m_struState.dwCurDataType == 21)
 						{
 							m_ctlProgress.SetPos(0);
 							m_bPlay = FALSE;
 							m_bPause = FALSE;
 							F_SetStopState();
							char szLan[128] = {0};
							g_StringLanType(szLan, "回放结束", "Playback Failed");
							AfxMessageBox(szLan);
 						}
 					}
 					UpdateData(FALSE);
 				}
 			}	
		}
	}
}	

void CMatPlayBack::OnFast() 
{
	// TODO: Add your control notification handler code here
	DWORD dwDecChanNum =  m_DecChanCombo.GetCurSel()+m_lStartChan;
	if ( m_BUseWinNo )
	{
		dwDecChanNum = m_dwWinNo + ((m_dwSubWinNo&0xff) << 16) + ((m_dwWallNo&0xff) << 24); 
	}
 	if (!NET_DVR_MatrixSetRemotePlayControl(m_lServerID, dwDecChanNum, NET_DVR_PLAYFAST, 2, NULL))
 	{
 		CString tmp;
 		tmp.Format("Error: NET_DVR_MatrixSetRemotePlayControl = %d", NET_DVR_GetLastError());
 		AfxMessageBox(tmp);
 	}
}

void CMatPlayBack::OnPlayFile() 
{
	UpdateData(TRUE);
	// TODO: Add your control notification handler code here
	DWORD dwDecChanNum =  m_DecChanCombo.GetCurSel()+m_lStartChan;
	if ( m_BUseWinNo )
	{
		dwDecChanNum = m_dwWinNo + ((m_dwSubWinNo&0xff) << 16) + ((m_dwWallNo&0xff) << 24); 
	}
 	if (m_bPause && m_bPlay)
 	{	
 		if (!NET_DVR_MatrixSetRemotePlayControl(m_lServerID, dwDecChanNum, NET_DVR_PLAYRESTART, 0, NULL))
 		{
 			CString tmp;
 			tmp.Format("Error: NET_DVR_MatrixSetRemotePlayControl = %d", NET_DVR_GetLastError());
 			AfxMessageBox(tmp);
 			return;
 		}
 		m_bPause = FALSE;
 		F_SetPlayState();
 	}
 	else if (m_bPlay)
 	{
 		if (!NET_DVR_MatrixSetRemotePlayControl(m_lServerID, dwDecChanNum, NET_DVR_PLAYPAUSE, 0, NULL))
 		{
 			CString tmp;
 			tmp.Format("Error: NET_DVR_MatrixSetRemotePlayControl = %d", NET_DVR_GetLastError());
 			AfxMessageBox(tmp);
 			return;
 		}
 		m_bPause = TRUE;
 		F_SetPauseState();
 	}
 	else
 	{
 		if (!NET_DVR_MatrixSetRemotePlayControl(m_lServerID, dwDecChanNum, NET_DVR_PLAYSTART, 0, NULL))
 		{
 			CString tmp;
 			tmp.Format("Error: NET_DVR_MatrixSetRemotePlayControl = %d", NET_DVR_GetLastError());
 			AfxMessageBox(tmp);
 			return;
 		}
 		m_bPlay = TRUE;
 		m_bPause = FALSE;
 		F_SetPlayState();
 		SetTimer(GETSTATE_TIMER, 2000, NULL);
 	}
 
 	UpdateData(FALSE);
}

void CMatPlayBack::OnSlow() 
{
	// TODO: Add your control notification handler code here
	DWORD dwDecChanNum =  m_DecChanCombo.GetCurSel()+m_lStartChan;
	if ( m_BUseWinNo )
	{
		dwDecChanNum = m_dwWinNo + ((m_dwSubWinNo&0xff) << 16) + ((m_dwWallNo&0xff) << 24); 
	}
 	if (!NET_DVR_MatrixSetRemotePlayControl(m_lServerID, dwDecChanNum, NET_DVR_PLAYSLOW, 2, NULL))
 	{
 		CString tmp;
 		tmp.Format("Error: NET_DVR_MatrixSetRemotePlayControl = %d", NET_DVR_GetLastError());
 		AfxMessageBox(tmp);
 	}
}

void CMatPlayBack::OnSound() 
{
	DWORD dwDecChanNum =  m_DecChanCombo.GetCurSel()+m_lStartChan;
	if ( m_BUseWinNo )
	{
		dwDecChanNum = m_dwWinNo + ((m_dwSubWinNo&0xff) << 16) + ((m_dwWallNo&0xff) << 24); 
	}
    if (!NET_DVR_MatrixSetRemotePlayControl(m_lServerID, dwDecChanNum, NET_DVR_PLAYSTARTAUDIO, 0, NULL))
    {
        CString tmp;
        tmp.Format("Error: NET_DVR_MatrixSetRemotePlayControl = %d", NET_DVR_GetLastError());
        AfxMessageBox(tmp);
        return;
    }
}

void CMatPlayBack::OnStep() 
{
	// TODO: Add your control notification handler code here
	DWORD dwDecChanNum =  m_DecChanCombo.GetCurSel()+m_lStartChan;
	if ( m_BUseWinNo )
	{
		dwDecChanNum = m_dwWinNo + ((m_dwSubWinNo&0xff) << 16) + ((m_dwWallNo&0xff) << 24); 
	}
 	if (!NET_DVR_MatrixSetRemotePlayControl(m_lServerID, dwDecChanNum, NET_DVR_PLAYNORMAL, 0, NULL))
 	{
 		CString tmp;
 		tmp.Format("Error: NET_DVR_MatrixSetRemotePlayControl = %d", NET_DVR_GetLastError());
 		AfxMessageBox(tmp);
 	}
}

void CMatPlayBack::OnStop() 
{
	UpdateData(TRUE);
	// TODO: Add your control notification handler code here
	DWORD dwDecChanNum =  m_DecChanCombo.GetCurSel()+m_lStartChan;
	if ( m_BUseWinNo )
	{
		dwDecChanNum = m_dwWinNo + ((m_dwSubWinNo&0xff) << 16) + ((m_dwWallNo&0xff) << 24); 
	}
 	if (!NET_DVR_MatrixSetRemotePlayControl(m_lServerID, dwDecChanNum, NET_DVR_PLAYSTOP, 0, NULL))
 	{
 		CString tmp;
 		tmp.Format("Error: NET_DVR_MatrixSetRemotePlayControl = %d", NET_DVR_GetLastError());
 		AfxMessageBox(tmp);
 		return;
 	}
 	m_PlayStatus.Empty();
 	m_bPlay = FALSE;
 	m_bPause = FALSE;
 	F_SetStopState();
 	KillTimer(GETSTATE_TIMER);
 
 	UpdateData(FALSE);
}

void CMatPlayBack::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	// TODO: Add your message handler code here and/or call default
	if (GetDlgItem(IDC_PROGRESS_SLIDER) == pScrollBar)
	{
 		
	}
}

void CMatPlayBack::OnRadioname() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CheckRadioButton(IDC_RADIONAME, IDC_RADIOTIME, IDC_RADIONAME);
	EnableControl(TRUE);

	UpdateData(FALSE);
}

void CMatPlayBack::OnRadiotime() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	CheckRadioButton(IDC_RADIONAME, IDC_RADIOTIME, IDC_RADIOTIME);
	EnableControl(FALSE);
	
	UpdateData(FALSE);
}

void CMatPlayBack::OnSetup() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwDecChanNum =  m_DecChanCombo.GetCurSel()+m_lStartChan;
	if ( m_BUseWinNo )
	{
		dwDecChanNum = m_dwWinNo + ((m_dwSubWinNo&0xff) << 16) + ((m_dwWallNo&0xff) << 24); 
	}
 	memset(&m_struPlay, 0, sizeof(m_struPlay));
 	m_struPlay.dwSize = sizeof(m_struPlay);
	m_struPlay.dwDecChannel = dwDecChanNum;
	m_struPlay.dwChannel = m_PlayBackChan; 
	m_struPlay.byChannelType = m_comboChannelType.GetCurSel();
	m_struPlay.byAddressType = m_comboDevAddrType.GetCurSel();
	sprintf((char *)m_struPlay.sUserName, "%s", m_PlayBackUser);
	sprintf((char *)m_struPlay.sPassword, "%s", m_PlayBackPass);

	switch (m_comboDevAddrType.GetCurSel())
	{
	case 0:		/*IP*/
		sprintf((char *)m_struPlay.unionAddr.struIpAddr.byDevAddress, "%s", m_PlayBackIP);
		m_struPlay.unionAddr.struIpAddr.wDevPort = m_PlayBackPort;
		break;
	case 1:		/*DNNS*/
		sprintf((char *)m_struPlay.unionAddr.struDdnsAddr.byDevAddress, "%s", m_strDdnsName);
		sprintf((char *)m_struPlay.unionAddr.struDdnsAddr.byDevDdns, "%s", m_strDnnsAddr);
		m_struPlay.unionAddr.struDdnsAddr.wDevPort = m_PlayBackPort;
		m_struPlay.unionAddr.struDdnsAddr.byDdnsType = m_comboDdnsServerType.GetCurSel();
		m_struPlay.unionAddr.struDdnsAddr.wDdnsPort = m_wDdnsPort;
		break;
	default:
		break;
	}

 	if (GetCheckedRadioButton(IDC_RADIONAME, IDC_RADIOTIME) == IDC_RADIOTIME)
 	{
 		SYSTEMTIME st;
 		m_StartDate.GetTime(&st);
 		m_struPlay.unionPlayBackInfo.struPlayBackByTime.StartTime.dwYear = st.wYear;
 		m_struPlay.unionPlayBackInfo.struPlayBackByTime.StartTime.dwMonth = st.wMonth;
 		m_struPlay.unionPlayBackInfo.struPlayBackByTime.StartTime.dwDay = st.wDay;
 		m_StartTime.GetTime(&st);
 		m_struPlay.unionPlayBackInfo.struPlayBackByTime.StartTime.dwHour = st.wHour;
 		m_struPlay.unionPlayBackInfo.struPlayBackByTime.StartTime.dwMinute = st.wMinute;
 		m_struPlay.unionPlayBackInfo.struPlayBackByTime.StartTime.dwSecond = st.wSecond;
 
 		m_StopDate.GetTime(&st);
 		m_struPlay.unionPlayBackInfo.struPlayBackByTime.StopTime.dwYear = st.wYear;
 		m_struPlay.unionPlayBackInfo.struPlayBackByTime.StopTime.dwMonth = st.wMonth;
 		m_struPlay.unionPlayBackInfo.struPlayBackByTime.StopTime.dwDay = st.wDay;
 		m_StopTime.GetTime(&st);
 		m_struPlay.unionPlayBackInfo.struPlayBackByTime.StopTime.dwHour = st.wHour;
 		m_struPlay.unionPlayBackInfo.struPlayBackByTime.StopTime.dwMinute = st.wMinute;
 		m_struPlay.unionPlayBackInfo.struPlayBackByTime.StopTime.dwSecond = st.wSecond;
 
 		m_struPlay.dwPlayMode = 1;
 	}
 	else
 	{
 		sprintf(m_struPlay.unionPlayBackInfo.sFileName, "%s", m_PlayBackName);
 		m_struPlay.dwPlayMode = 0;
 	}
 
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_DEC_PLAY_REMOTE_FILE, &m_struPlay, sizeof(NET_DVR_MATRIX_DEC_REMOTE_PLAY_EX)))
 	{
		CString tmp;
		tmp.Format("Error: NET_DVR_RemoteControl = %d", NET_DVR_GetLastError());
		AfxMessageBox(tmp);
		return;
 	}
 	
	KillTimer(GETSTATE_TIMER);
	char szLan[128] = {0};
	g_StringLanType(szLan, "设置成功", "Set Successfully");
	AfxMessageBox(szLan);
}

void CMatPlayBack::OnCancel() 
{
	// TODO: Add extra cleanup here
	if (m_bPlay)
	{
		OnStop();
	}

	CDialog::OnCancel();
}

void CMatPlayBack::OnReleasedcaptureProgressSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if (m_bPlay && m_struPlay.dwPlayMode == 0)
	{
		DWORD dwDecChanNum =  m_DecChanCombo.GetCurSel()+m_lStartChan;
		if ( m_BUseWinNo )
		{
			dwDecChanNum = m_dwWinNo + ((m_dwSubWinNo&0xff) << 16) + ((m_dwWallNo&0xff) << 24); 
		}
		int pos = m_ctlProgress.GetPos();
		if (!NET_DVR_MatrixSetRemotePlayControl(m_lServerID, dwDecChanNum, NET_DVR_PLAYSETPOS, pos, NULL))
		{
			CString tmp;
			tmp.Format("Error: NET_DVR_MatrixSetRemotePlayControl = %d", NET_DVR_GetLastError());
			AfxMessageBox(tmp);
		}
 	}
	
	*pResult = 0;
}

void CMatPlayBack::OnStopsound() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
	DWORD dwDecChanNum =  m_DecChanCombo.GetCurSel()+m_lStartChan;
	if ( m_BUseWinNo )
	{
		dwDecChanNum = m_dwWinNo + ((m_dwSubWinNo&0xff) << 16) + ((m_dwWallNo&0xff) << 24); 
	}
	if (!NET_DVR_MatrixSetRemotePlayControl(m_lServerID, dwDecChanNum, NET_DVR_PLAYSTOPAUDIO, 0, NULL))
    {
        CString tmp;
        tmp.Format("Error: NET_DVR_MatrixSetRemotePlayControl = %d", NET_DVR_GetLastError());
        AfxMessageBox(tmp);
        return;
    }
}

void CMatPlayBack::OnSelchangeComboDevAddressType() 
{
	switch (m_comboDevAddrType.GetCurSel())
	{
	case 0:		/*IP*/
		GetDlgItem(IDC_EDITIP)->EnableWindow(TRUE);
		//GetDlgItem(IDC_EDITPORT)->EnableWindow(TRUE);

		GetDlgItem(IDC_EDIT_DDNS_ADDRESS)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DDNS_PORT)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_DDNS_SERVER_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DDNS_NAME)->EnableWindow(FALSE);

		break;
	case 1:		/*DNNS*/
		GetDlgItem(IDC_EDITIP)->EnableWindow(FALSE);
		//GetDlgItem(IDC_EDITPORT)->EnableWindow(FALSE);
		
		GetDlgItem(IDC_EDIT_DDNS_ADDRESS)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DDNS_PORT)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_DDNS_SERVER_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DDNS_NAME)->EnableWindow(TRUE);
		break;
	default:
		break;
	}
	
}

void CMatPlayBack::OnSelchangeComboChannelType() 
{
	UpdateData(TRUE);
	
	GetDlgItem(IDC_EDITCHAN)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_STREAM_ID)->EnableWindow(FALSE);
	switch (m_comboChannelType.GetCurSel())
	{
	case 0:
	case 1:
		break;
	case 2:
		GetDlgItem(IDC_EDIT_STREAM_ID)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDITCHAN)->EnableWindow(FALSE);
		break;
	default:
		break;
	}
	UpdateData(FALSE);
	
}
