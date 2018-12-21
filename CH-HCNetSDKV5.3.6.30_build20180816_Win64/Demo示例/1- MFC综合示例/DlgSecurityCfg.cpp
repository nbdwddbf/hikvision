// DlgSecurityCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgSecurityCfg.h"
#include "DlgLockedInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSecurityCfg dialog


CDlgSecurityCfg::CDlgSecurityCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSecurityCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSecurityCfg)
	m_bchkTelnet = -1;
	//}}AFX_DATA_INIT
}


void CDlgSecurityCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSecurityCfg)
	DDX_Control(pDX, IDC_COMBO_LOGIN_LEVEL, m_cmLoginLevel);
	DDX_Check(pDX, IDC_CHK_TELNET, m_bchkTelnet);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSecurityCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgSecurityCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTIN_SET, OnBtinSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSecurityCfg message handlers
BOOL CDlgSecurityCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserId = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	OnBtnGet();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgSecurityCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struSecurityCfg.dwSize = sizeof(m_struSecurityCfg);
	DWORD dwReturn = 0;
	if (!NET_DVR_GetDVRConfig(m_lUserId, NET_DVR_GET_SECURITY_CFG, 1, &m_struSecurityCfg, sizeof(m_struSecurityCfg), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "get security config failed");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "get security config successful");
	}

	m_cmLoginLevel.SetCurSel(m_struSecurityCfg.byCommuMode);
	m_bchkTelnet = m_struSecurityCfg.byTelnetServer;
	UpdateData(FALSE);
}



void CDlgSecurityCfg::OnBtinSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struSecurityCfg.dwSize = sizeof(m_struSecurityCfg);
	m_struSecurityCfg.byCommuMode = m_cmLoginLevel.GetCurSel();
	m_struSecurityCfg.byTelnetServer = m_bchkTelnet;
	if (!NET_DVR_SetDVRConfig(m_lUserId, NET_DVR_SET_SECURITY_CFG, 1, &m_struSecurityCfg, sizeof(m_struSecurityCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Set security config failed");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Set security config successful");
	}
}
