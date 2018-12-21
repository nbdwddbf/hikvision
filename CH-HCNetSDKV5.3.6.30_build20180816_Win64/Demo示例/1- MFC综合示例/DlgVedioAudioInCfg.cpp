// DlgVedioAudioInCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVedioAudioInCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgVedioAudioInCfg dialog


DlgVedioAudioInCfg::DlgVedioAudioInCfg(CWnd* pParent /*=NULL*/)
	: CDialog(DlgVedioAudioInCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgVedioAudioInCfg)
	m_AudioSource = FALSE;
	m_AudioChannel = 0;
	m_VedioChannel = 0;
	//}}AFX_DATA_INIT
	memset(&m_struVedioAudioInCfg,0,sizeof(m_struVedioAudioInCfg));
}


void DlgVedioAudioInCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgVedioAudioInCfg)
	DDX_Check(pDX, IDC_AUDIO_SOURCE, m_AudioSource);
	DDX_Text(pDX, IDC_AUDIO_CHANNEL, m_AudioChannel);
	DDX_Text(pDX, IDC_VEDIO_CHANNEL, m_VedioChannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgVedioAudioInCfg, CDialog)
	//{{AFX_MSG_MAP(DlgVedioAudioInCfg)
	ON_BN_CLICKED(IDC_SET, OnSet)
	ON_BN_CLICKED(IDC_GET, OnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgVedioAudioInCfg message handlers

void DlgVedioAudioInCfg::OnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struVedioAudioInCfg.byEnable = m_AudioSource;
	m_struVedioAudioInCfg.dwChanNo = m_VedioChannel;
	m_struVedioAudioInCfg.dwSize = sizeof(m_struVedioAudioInCfg);
	DWORD dwDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	char szLan[128] = {0};
	if(NET_DVR_SetDVRConfig(g_struDeviceInfo[dwDeviceIndex].lLoginID,NET_DVR_SET_VIDEO_AUDIOIN_CFG,m_AudioChannel,&m_struVedioAudioInCfg,sizeof(m_struVedioAudioInCfg)))
	{
		g_pMainDlg->AddLog(g_struDeviceInfo[dwDeviceIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_SET_VEDIO_AUDIOIN_CFG");
		g_StringLanType(szLan, "设置成功", "Set vedio audio in  cfg successed!");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(g_struDeviceInfo[dwDeviceIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_SET_VEDIO_AUDIOIN_CFG");
		g_StringLanType(szLan, "设置失败", "Set vedio audio in cfg failed!");
		AfxMessageBox(szLan);
	}
}

void DlgVedioAudioInCfg::OnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	char szLan[128] = {0};
	DWORD dwReturn;
	if(NET_DVR_GetDVRConfig(g_struDeviceInfo[dwDeviceIndex].lLoginID,NET_DVR_GET_VIDEO_AUDIOIN_CFG,m_AudioChannel,&m_struVedioAudioInCfg,sizeof(m_struVedioAudioInCfg),&dwReturn))
	{
		g_pMainDlg->AddLog(g_struDeviceInfo[dwDeviceIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_GET_VEDIO_AUDIOIN_CFG");
		g_StringLanType(szLan, "获取成功", "Get vedio audio in cfg successed!");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(g_struDeviceInfo[dwDeviceIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_GET_VEDIO_AUDIOIN_CFG");
		g_StringLanType(szLan, "获取失败", "Get vedio audio in cfg failed!");
		AfxMessageBox(szLan);
	}
	m_AudioSource = m_struVedioAudioInCfg.byEnable;
	m_VedioChannel = m_struVedioAudioInCfg.dwChanNo;
	UpdateData(FALSE);
}
