// DlgDecorder.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgDecorder.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDecorder dialog


CDlgDecorder::CDlgDecorder(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDecorder::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDecorder)
	m_bRoamEnable = FALSE;
	//}}AFX_DATA_INIT
	m_lUserID = -1;
	m_iDeviceIndex = -1;
}


void CDlgDecorder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDecorder)
	DDX_Check(pDX, IDC_CHECK_ROAM_ENABLE, m_bRoamEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDecorder, CDialog)
	//{{AFX_MSG_MAP(CDlgDecorder)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDecorder message handlers

void CDlgDecorder::OnButtonGet() 
{
	// TODO: Add your control notification handler code here
	memset(&m_struRoamCfg, 0, sizeof(m_struRoamCfg));
	m_struRoamCfg.dwSize = sizeof(m_struRoamCfg);
	DWORD dwRetBytes = 0;
	if (NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_WIN_ROAM_SWITCH_CFG, 0, &m_struRoamCfg, sizeof(m_struRoamCfg), &dwRetBytes))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetDVRConfig NET_DVR_GET_WIN_ROAM_SWITCH_CFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetDVRConfig NET_DVR_GET_WIN_ROAM_SWITCH_CFG");
	}
	m_bRoamEnable = m_struRoamCfg.byEnableRoam;
	UpdateData(FALSE);
}

void CDlgDecorder::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	memset(&m_struRoamCfg, 0, sizeof(m_struRoamCfg));
	m_struRoamCfg.dwSize = sizeof(m_struRoamCfg);
	m_struRoamCfg.byEnableRoam = m_bRoamEnable;
	if (NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_WIN_ROAM_SWITCH_CFG, 0, &m_struRoamCfg, sizeof(m_struRoamCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SetDVRConfig NET_DVR_SET_WIN_ROAM_SWITCH_CFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SetDVRConfig NET_DVR_SET_WIN_ROAM_SWITCH_CFG");
	}
}
