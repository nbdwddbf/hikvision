// DlgRtspConfig.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRtspConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRtspConfig dialog


CDlgRtspConfig::CDlgRtspConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRtspConfig::IDD, pParent)
{
	m_iDeviceIndex = -1;
	memset(&m_struRtspCfg, 0, sizeof(NET_DVR_RTSPCFG));
	//{{AFX_DATA_INIT(CDlgRtspConfig)
	m_iPort = 0;
	//}}AFX_DATA_INIT
}


void CDlgRtspConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRtspConfig)
	DDX_Text(pDX, IDC_EDIT_RTSP_PORT, m_iPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRtspConfig, CDialog)
	//{{AFX_MSG_MAP(CDlgRtspConfig)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRtspConfig message handlers
BOOL CDlgRtspConfig::OnInitDialog()
{
	CDialog::OnInitDialog();
	if (!NET_DVR_GetRtspConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, 0, &m_struRtspCfg, sizeof(NET_DVR_RTSPCFG)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetRtspConfig");
		AfxMessageBox("Get Rtsp Config Err!");
		GetDlgItem(IDC_BTN_SET)->EnableWindow(FALSE);
		return FALSE;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetRtspConfig");
	m_iPort = m_struRtspCfg.wPort;
	UpdateData(FALSE);
	return TRUE;
}

void CDlgRtspConfig::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struRtspCfg.wPort = m_iPort;
	if (NET_DVR_SetRtspConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, 0, &m_struRtspCfg, sizeof(NET_DVR_RTSPCFG)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SetRtspConfig");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SetRtspConfig");
	}
}

void CDlgRtspConfig::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}
