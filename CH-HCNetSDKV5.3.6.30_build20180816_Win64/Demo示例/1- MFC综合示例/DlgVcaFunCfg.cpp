// DlgVcaFunCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaFunCfg.h"
#include "DlgVcaSavePathConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaFunCfg dialog


CDlgVcaFunCfg::CDlgVcaFunCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaFunCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaFunCfg)
	m_dwReserveTime = 0;
	//}}AFX_DATA_INIT
	m_lServerID = -1; 
    m_iDevIndex = -1; 
	m_iChannelIndex = 1;
}


void CDlgVcaFunCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaFunCfg)
	DDX_Text(pDX, IDC_EDIT_RESERVE_TIME, m_dwReserveTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaFunCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaFunCfg)
	ON_BN_CLICKED(IDC_BTN_GET_TRIAL_CFG, OnBtnGetTrialCfg)
	ON_BN_CLICKED(IDC_BTN_SYN_CHAN_NAME, OnBtnSynChanName)
	ON_BN_CLICKED(IDC_BTN_DISK_CFG, OnBtnDiskCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaFunCfg message handlers

void CDlgVcaFunCfg::OnBtnGetTrialCfg() 
{
	// TODO: Add your control notification handler code here
	BOOL bRet = FALSE;
    DWORD dwReturn = 0;
	NET_DVR_TRIAL_VERSION_CFG struTrialVersion = {0};
	if(!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_TRIAL_VERSION_CFG, m_iChannelIndex, &struTrialVersion, sizeof(struTrialVersion), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_TRIAL_VERSION_CFG");            
		bRet = FALSE;
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_TRIAL_VERSION_CFG");            
		bRet = TRUE;
		m_dwReserveTime = struTrialVersion.wReserveTime;
	}

	UpdateData(FALSE);
}

void CDlgVcaFunCfg::OnBtnSynChanName() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_SYN_CHANNEL_NAME_PARAM struControl = {0};
	struControl.dwSize = sizeof(struControl);
	struControl.dwChannel = m_iChannelIndex;
	
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_SYN_CHANNEL_NAME, &struControl, sizeof(struControl)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_SYN_CHANNEL_NAME");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_SYN_CHANNEL_NAME");
		return;
	}
}

void CDlgVcaFunCfg::OnBtnDiskCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaSavePathConfig dlg;
    dlg.m_lServerID = m_lServerID;
	dlg.m_lChannel = m_iChannelIndex;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}
