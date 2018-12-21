// DlgITSIpcCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgITSIpcCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgITSIpcCfg dialog


CDlgITSIpcCfg::CDlgITSIpcCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgITSIpcCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgITSIpcCfg)
	m_csDeviceID = _T("");
	m_csMointorInfo = _T("");
	m_csMointorID = _T("");
	//}}AFX_DATA_INIT
	m_lServerID = -1;
    m_iDevIndex = -1;
	m_lChannel = -1;
	memset(&m_struIPCChan, 0, sizeof(m_struIPCChan));
}


void CDlgITSIpcCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgITSIpcCfg)
	DDX_Control(pDX, IDC_COMBO_IPC_TYPE, m_comboIpcType);
	DDX_Control(pDX, IDC_COMBO_DIRECTION_TYPE, m_comboDirectionType);
	DDX_Text(pDX, IDC_EDIT_DEVICE_ID, m_csDeviceID);
	DDX_Text(pDX, IDC_EDIT_MONITOR_INFO, m_csMointorInfo);
	DDX_Text(pDX, IDC_EDIT_MONITOR_SITE_ID, m_csMointorID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgITSIpcCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgITSIpcCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgITSIpcCfg message handlers

void CDlgITSIpcCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	memset(&m_struIPCChan, 0, sizeof(m_struIPCChan));
	DWORD dwReturn = 0;
	char szLan[49] = {0};
	if (NET_DVR_GetDVRConfig(m_lServerID, NET_ITS_GET_IPC_CHAN_CFG, m_lChannel, &m_struIPCChan,
		sizeof(m_struIPCChan), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_ITS_GET_IPC_CHAN_CFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_ITS_GET_IPC_CHAN_CFG");
	}
	m_comboIpcType.SetCurSel(m_struIPCChan.byCameraType);
	m_comboDirectionType.SetCurSel(m_struIPCChan.byDirectionNo);
	memcpy(szLan,m_struIPCChan.byDeviceID,48);
	m_csDeviceID.Format("%s", szLan);
	memset(szLan, 0, 49);
	memcpy(szLan,m_struIPCChan.byMonitoringSiteID,48);
	m_csMointorID.Format("%s", szLan);
	memset(szLan,0,49);
	memcpy(szLan, m_struIPCChan.byMonitorInfo,48);
	m_csMointorInfo.Format("%s",szLan);
	UpdateData(FALSE);
}

void CDlgITSIpcCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	m_struIPCChan.dwSize = sizeof(m_struIPCChan);
	m_struIPCChan.byCameraType = m_comboIpcType.GetCurSel();
	m_struIPCChan.byDirectionNo = m_comboDirectionType.GetCurSel();
	memcpy(&m_struIPCChan.byDeviceID, m_csDeviceID, 48);
	memcpy(&m_struIPCChan.byMonitorInfo, m_csMointorInfo, 48);
	memcpy(&m_struIPCChan.byMonitoringSiteID, m_csMointorID, 48);
	if (NET_DVR_SetDVRConfig(m_lServerID, NET_ITS_SET_IPC_CHAN_CFG, m_lChannel, &m_struIPCChan, sizeof(m_struIPCChan)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_ITS_SET_IPC_CHAN_CFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_ITS_SET_IPC_CHAN_CFG");
	}
}
