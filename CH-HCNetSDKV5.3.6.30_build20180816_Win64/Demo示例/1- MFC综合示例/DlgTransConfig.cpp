// DlgTransConfig.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgTransConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTransConfig dialog


CDlgTransConfig::CDlgTransConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTransConfig::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTransConfig)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgTransConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTransConfig)
	DDX_Control(pDX, IDC_TAB_CONFIG_TYPE, m_tabCfgType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTransConfig, CDialog)
	//{{AFX_MSG_MAP(CDlgTransConfig)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CONFIG_TYPE, OnSelchangeTabConfigType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTransConfig message handlers

BOOL CDlgTransConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iTabSel = 0;
	memset(m_lpStreamInfo, 0, sizeof(m_lpStreamInfo));
	m_dwItemCount = 0;

	char szLan[128] = {0};
	g_StringLanType(szLan, "流来源配置", "Stream source config");
	m_tabCfgType.InsertItem(0, szLan);
	m_dlgStreamSrc.Create(IDD_DLG_TRANS_STREAM_SRC_CFG, &m_tabCfgType);
	m_dlgStreamSrc.ShowWindow(SW_SHOW);

	g_StringLanType(szLan, "转码压缩参数配置", "Trans code compression config");
	m_tabCfgType.InsertItem(1, szLan);
	m_dlgTransCmp.m_lUserID = m_lUserID;
	m_dlgTransCmp.Create(IDD_DLG_TRANS_COMPRESSION, &m_tabCfgType);
	m_dlgTransCmp.ShowWindow(SW_HIDE);

	g_StringLanType(szLan, "被动转码", "Passive trans code");
	m_tabCfgType.InsertItem(2, szLan);
	m_dlgPassiveTransCode.m_lUserID = m_lUserID;
	m_dlgPassiveTransCode.Create(IDD_DLG_PASSIVE_TRANS_CODE, &m_tabCfgType);
	m_dlgPassiveTransCode.ShowWindow(SW_HIDE);

	g_StringLanType(szLan, "转码设备状态", "Trans device status");
	m_tabCfgType.InsertItem(3, szLan);
	m_dlgTransDevStatus.m_lUserID = m_lUserID;
	m_dlgTransDevStatus.Create(IDD_DLG_TRANS_DEV_STATUS, &m_tabCfgType);
	m_dlgTransDevStatus.ShowWindow(SW_HIDE);

	g_StringLanType(szLan, "设备管理", "Device management");
	m_tabCfgType.InsertItem(4, szLan);
	m_dlgTransAutoReboot.m_lUserID = m_lUserID;
	m_dlgTransAutoReboot.Create(IDD_DLG_TRANS_AUTO_REBOOT, &m_tabCfgType);
	m_dlgTransAutoReboot.ShowWindow(SW_HIDE);	

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTransConfig::OnSelchangeTabConfigType(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_iTabSel = m_tabCfgType.GetCurSel();

	switch (m_iTabSel)
	{
	case 0:
		m_dlgStreamSrc.ShowWindow(SW_SHOW);
		m_dlgTransCmp.ShowWindow(SW_HIDE);
		m_dlgPassiveTransCode.ShowWindow(SW_HIDE);
		m_dlgTransDevStatus.ShowWindow(SW_HIDE);
		m_dlgTransDevStatus.KillTimer(TRANS_DEVICE_TIMER);
		m_dlgTransAutoReboot.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_dlgStreamSrc.GetStreamInfoFromList(m_lpStreamInfo, &m_dwItemCount);
		m_dlgTransCmp.AddStreamInfoToList(m_lpStreamInfo, m_dwItemCount);
		m_dlgStreamSrc.ShowWindow(SW_HIDE);
		m_dlgTransCmp.ShowWindow(SW_SHOW);
		m_dlgPassiveTransCode.ShowWindow(SW_HIDE);
		m_dlgTransDevStatus.ShowWindow(SW_HIDE);
		m_dlgTransDevStatus.KillTimer(TRANS_DEVICE_TIMER);
		m_dlgTransAutoReboot.ShowWindow(SW_HIDE);
		break;
	case 2:
		m_dlgStreamSrc.ShowWindow(SW_HIDE);
		m_dlgTransCmp.ShowWindow(SW_HIDE);
		m_dlgPassiveTransCode.ShowWindow(SW_SHOW);
		m_dlgTransDevStatus.ShowWindow(SW_HIDE);
		m_dlgTransDevStatus.KillTimer(TRANS_DEVICE_TIMER);
		m_dlgTransAutoReboot.ShowWindow(SW_HIDE);
		break;
	case 3:
		m_dlgStreamSrc.ShowWindow(SW_HIDE);
		m_dlgTransCmp.ShowWindow(SW_HIDE);
		m_dlgPassiveTransCode.ShowWindow(SW_HIDE);
		m_dlgTransDevStatus.ShowWindow(SW_SHOW);
		m_dlgTransDevStatus.SetTimer(TRANS_DEVICE_TIMER, 3000, NULL);
		m_dlgTransAutoReboot.ShowWindow(SW_HIDE);
		break;
	case 4:
		m_dlgStreamSrc.ShowWindow(SW_HIDE);
		m_dlgTransCmp.ShowWindow(SW_HIDE);
		m_dlgPassiveTransCode.ShowWindow(SW_HIDE);
		m_dlgTransDevStatus.ShowWindow(SW_HIDE);
		m_dlgTransDevStatus.KillTimer(TRANS_DEVICE_TIMER);
		m_dlgTransAutoReboot.ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}
	*pResult = 0;
}

void CDlgTransConfig::OnCancel() 
{
	// TODO: Add extra cleanup here
	CDialog::OnCancel();
}
