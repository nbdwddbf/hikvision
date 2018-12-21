// DlgRemoteControlPlay.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRemoteControlPlay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteControlPlay dialog


CDlgRemoteControlPlay::CDlgRemoteControlPlay(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteControlPlay::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRemoteControlPlay)
	m_bHDMI1 = FALSE;
	m_bHDMI2 = FALSE;
	m_bVGA1 = FALSE;
	m_bVGA2 = FALSE;
	m_bVGA3 = FALSE;
	m_bVGA4 = FALSE;
	m_bVGA5_10 = FALSE;
	m_sPlayFile = _T("");
	//}}AFX_DATA_INIT
}


void CDlgRemoteControlPlay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteControlPlay)
	DDX_Check(pDX, IDC_CHK_HDMI1, m_bHDMI1);
	DDX_Check(pDX, IDC_CHK_HDMI2, m_bHDMI2);
	DDX_Check(pDX, IDC_CHK_VGA1, m_bVGA1);
	DDX_Check(pDX, IDC_CHK_VGA2, m_bVGA2);
	DDX_Check(pDX, IDC_CHK_VGA3, m_bVGA3);
	DDX_Check(pDX, IDC_CHK_VGA4, m_bVGA4);
	DDX_Check(pDX, IDC_CHK_VGA5_10, m_bVGA5_10);
	DDX_Text(pDX, IDC_PLAY_FILE, m_sPlayFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRemoteControlPlay, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteControlPlay)
	ON_BN_CLICKED(IDC_BTN_PLAY, OnBtnPlay)
	ON_BN_CLICKED(IDC_BTN_STOP_PLAY, OnBtnStopPlay)
	ON_BN_CLICKED(IDC_BTN_PAUSE, OnBtnPause)
	ON_BN_CLICKED(IDC_BTN_RESUME, OnBtnResume)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteControlPlay message handlers

void CDlgRemoteControlPlay::OnBtnPlay() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_REMOTE_PLAY struRemotePlay = {0};
	struRemotePlay.dwSize = sizeof(NET_DVR_REMOTE_PLAY);
	sprintf((char*)struRemotePlay.byFileName,"%s",m_sPlayFile);
	struRemotePlay.byType = 1;
	struRemotePlay.byVideoOut[0] = m_bVGA1;
	struRemotePlay.byVideoOut[1] = m_bVGA2;
	struRemotePlay.byVideoOut[2] = m_bVGA3;
	struRemotePlay.byVideoOut[3] = m_bVGA4;
	struRemotePlay.byVideoOut[4] = m_bVGA5_10;
	struRemotePlay.byVideoOut[5] = m_bHDMI1;
	struRemotePlay.byVideoOut[6] = m_bHDMI2;
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	LONG lLogiNID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	if(NET_DVR_SetDVRConfig(lLogiNID,NET_DVR_REMOTE_CONTROL_PLAY,0,&struRemotePlay,sizeof(struRemotePlay)))
	{
		g_pMainDlg->AddLog(iDeviceIndex,OPERATION_SUCC_T,"NET_DVR_REMOTE_CONTROL_PLAY");
	}
	else
	{
		g_pMainDlg->AddLog(iDeviceIndex,OPERATION_FAIL_T,"NET_DVR_REMOTE_CONTROL_PLAY");
		AfxMessageBox("²¥·ÅÊ§°Ü");
	}
}

void CDlgRemoteControlPlay::OnBtnStopPlay() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_REMOTE_PLAY struRemotePlay = {0};
	struRemotePlay.dwSize = sizeof(NET_DVR_REMOTE_PLAY);
	sprintf((char*)struRemotePlay.byFileName,"%s",m_sPlayFile);
	struRemotePlay.byType = 2;
	struRemotePlay.byVideoOut[0] = m_bVGA1;
	struRemotePlay.byVideoOut[1] = m_bVGA2;
	struRemotePlay.byVideoOut[2] = m_bVGA3;
	struRemotePlay.byVideoOut[3] = m_bVGA4;
	struRemotePlay.byVideoOut[4] = m_bVGA5_10;
	struRemotePlay.byVideoOut[5] = m_bHDMI1;
	struRemotePlay.byVideoOut[6] = m_bHDMI2;
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	LONG lLogiNID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	if(NET_DVR_SetDVRConfig(lLogiNID,NET_DVR_REMOTE_CONTROL_PLAY,0,&struRemotePlay,sizeof(struRemotePlay)))
	{
		g_pMainDlg->AddLog(iDeviceIndex,OPERATION_SUCC_T,"NET_DVR_REMOTE_CONTROL_PLAY");
	}
	else
	{
		g_pMainDlg->AddLog(iDeviceIndex,OPERATION_FAIL_T,"NET_DVR_REMOTE_CONTROL_PLAY");
		AfxMessageBox("Í£Ö¹Ê§°Ü");
	}
}

void CDlgRemoteControlPlay::OnBtnPause() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_REMOTE_PLAY struRemotePlay = {0};
	struRemotePlay.dwSize = sizeof(NET_DVR_REMOTE_PLAY);
	sprintf((char*)struRemotePlay.byFileName,"%s",m_sPlayFile);
	struRemotePlay.byType = 3;
	struRemotePlay.byVideoOut[0] = m_bVGA1;
	struRemotePlay.byVideoOut[1] = m_bVGA2;
	struRemotePlay.byVideoOut[2] = m_bVGA3;
	struRemotePlay.byVideoOut[3] = m_bVGA4;
	struRemotePlay.byVideoOut[4] = m_bVGA5_10;
	struRemotePlay.byVideoOut[5] = m_bHDMI1;
	struRemotePlay.byVideoOut[6] = m_bHDMI2;
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	LONG lLogiNID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	if(NET_DVR_SetDVRConfig(lLogiNID,NET_DVR_REMOTE_CONTROL_PLAY,0,&struRemotePlay,sizeof(struRemotePlay)))
	{
		g_pMainDlg->AddLog(iDeviceIndex,OPERATION_SUCC_T,"NET_DVR_REMOTE_CONTROL_PLAY");
	}
	else
	{
		g_pMainDlg->AddLog(iDeviceIndex,OPERATION_FAIL_T,"NET_DVR_REMOTE_CONTROL_PLAY");
		AfxMessageBox("ÔÝÍ£Ê§°Ü");
	}
}

void CDlgRemoteControlPlay::OnBtnResume() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_REMOTE_PLAY struRemotePlay = {0};
	struRemotePlay.dwSize = sizeof(NET_DVR_REMOTE_PLAY);
	sprintf((char*)struRemotePlay.byFileName,"%s",m_sPlayFile);
	struRemotePlay.byType = 4;
	struRemotePlay.byVideoOut[0] = m_bVGA1;
	struRemotePlay.byVideoOut[1] = m_bVGA2;
	struRemotePlay.byVideoOut[2] = m_bVGA3;
	struRemotePlay.byVideoOut[3] = m_bVGA4;
	struRemotePlay.byVideoOut[4] = m_bVGA5_10;
	struRemotePlay.byVideoOut[5] = m_bHDMI1;
	struRemotePlay.byVideoOut[6] = m_bHDMI2;
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	LONG lLogiNID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	if(NET_DVR_SetDVRConfig(lLogiNID,NET_DVR_REMOTE_CONTROL_PLAY,0,&struRemotePlay,sizeof(struRemotePlay)))
	{
		g_pMainDlg->AddLog(iDeviceIndex,OPERATION_SUCC_T,"NET_DVR_REMOTE_CONTROL_PLAY");
	}
	else
	{
		g_pMainDlg->AddLog(iDeviceIndex,OPERATION_FAIL_T,"NET_DVR_REMOTE_CONTROL_PLAY");
		AfxMessageBox("ÔÝÍ£Ê§°Ü");
	}
}
