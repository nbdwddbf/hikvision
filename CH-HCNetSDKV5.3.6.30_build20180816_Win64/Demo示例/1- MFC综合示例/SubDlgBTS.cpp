// SubDlgBTS.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "SubDlgBTS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubDlgBTS dialog


CSubDlgBTS::CSubDlgBTS(CWnd* pParent /*=NULL*/)
	: CDialog(CSubDlgBTS::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSubDlgBTS)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSubDlgBTS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubDlgBTS)
	DDX_Control(pDX, IDC_COMBO_BTS, m_cmbBTS);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubDlgBTS, CDialog)
	//{{AFX_MSG_MAP(CSubDlgBTS)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSetBTS)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGetBTS)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubDlgBTS message handlers

BOOL CSubDlgBTS::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cmbBTS.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSubDlgBTS::CheckInitParam()
{
    m_iDevIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lServerID = g_struDeviceInfo[m_iDevIndex].lLoginID;
	
    return TRUE;
}


void CSubDlgBTS::OnBtnGetBTS() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturned = 0;
	char szLan[128] = {0};
	NET_DVR_RAID_BTS_CFG struRaidBtsCfg = {0};
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_RAID_BACKGROUND_TASK_SPEED, 0, &struRaidBtsCfg, sizeof(NET_DVR_RAID_BTS_CFG), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_RAID_BACKGROUND_TASK_SPEED");
		g_StringLanType(szLan, "»ñÈ¡Ê§°Ü", "Get failed");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_RAID_BACKGROUND_TASK_SPEED");	
	}

	m_cmbBTS.SetCurSel(struRaidBtsCfg.bySpeed);
	UpdateData(FALSE);
	
}

void CSubDlgBTS::OnBtnSetBTS() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	NET_DVR_RAID_BTS_CFG struRaidBtsCfg = {0};
	struRaidBtsCfg.dwSize = sizeof(NET_DVR_RAID_BTS_CFG);
	struRaidBtsCfg.bySpeed = m_cmbBTS.GetCurSel();
	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_RAID_BACKGROUND_TASK_SPEED, 0, &struRaidBtsCfg, sizeof(NET_DVR_RAID_BTS_CFG)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_RAID_BACKGROUND_TASK_SPEED");
		g_StringLanType(szLan, "ÉèÖÃÊ§°Ü", "Set failed");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_RAID_BACKGROUND_TASK_SPEED");	
	}
	
	
}
