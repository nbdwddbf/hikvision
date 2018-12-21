// DlgPwManageCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPwManageCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPwManageCfg dialog


CDlgPwManageCfg::CDlgPwManageCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPwManageCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPwManageCfg)
	m_byLockCount = 0;
	m_dwLockTime = 0;
	//}}AFX_DATA_INIT
}


void CDlgPwManageCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPwManageCfg)
	DDX_Text(pDX, IDC_EDIT_LOCK_COUNT, m_byLockCount);
	DDX_Text(pDX, IDC_EDIT_LOCK_TIME, m_dwLockTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPwManageCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgPwManageCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_LOCK_INFO, OnBtnLockInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPwManageCfg message handlers

BOOL CDlgPwManageCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserId = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	OnBtnGet();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPwManageCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struPwManageCfg.dwSize = sizeof(m_struPwManageCfg);
	DWORD dwReturn = 0;
	if (!NET_DVR_GetDVRConfig(m_lUserId, NET_DVR_GET_PASSWORD_MANAGE_CFG, 0, &m_struPwManageCfg, sizeof(m_struPwManageCfg), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "get password manage failed");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "get password manage successful");
	}
	m_byLockCount = m_struPwManageCfg.byLockCount;
	m_dwLockTime = m_struPwManageCfg.dwLockTime;
	UpdateData(FALSE);
}

void CDlgPwManageCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struPwManageCfg.dwSize = sizeof(m_struPwManageCfg);
	m_struPwManageCfg.byLockCount = m_byLockCount;
	m_struPwManageCfg.dwLockTime = m_dwLockTime;
	if (!NET_DVR_SetDVRConfig(m_lUserId, NET_DVR_SET_PASSWORD_MANAGE_CFG, 0, &m_struPwManageCfg, sizeof(m_struPwManageCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Set password manage failed");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Set password manage successful");
	}
}

#include "DlgLockedInfo.h"
void CDlgPwManageCfg::OnBtnLockInfo() 
{
	// TODO: Add your control notification handler code here
	CDlgLockedInfo dlg;
    dlg.DoModal();
}
