// DlgAutoReboot.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAutoReboot.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAutoReboot dialog


CDlgAutoReboot::CDlgAutoReboot(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAutoReboot::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAutoReboot)
	m_byHour = 0;
	m_byMin = 0;
	//}}AFX_DATA_INIT
}


void CDlgAutoReboot::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAutoReboot)
	DDX_Control(pDX, IDC_COMBO_DATE, m_comboDate);
	DDX_Text(pDX, IDC_EDIT_HOUR, m_byHour);
	DDX_Text(pDX, IDC_EDIT_MIN, m_byMin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAutoReboot, CDialog)
	//{{AFX_MSG_MAP(CDlgAutoReboot)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAutoReboot message handlers

void CDlgAutoReboot::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturned = 0;
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_AUTO_REBOOT_CFG, 0, &m_struRebootTime, sizeof(m_struRebootTime), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_AUTO_REBOOT_CFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_AUTO_REBOOT_CFG");
        m_comboDate.SetCurSel(m_struRebootTime.struRebootTime.byDate - 1);
		m_byHour = m_struRebootTime.struRebootTime.byHour;
		m_byMin = m_struRebootTime.struRebootTime.byMinute;
		UpdateData(FALSE);
	}
}

void CDlgAutoReboot::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_byHour < 0 || m_byHour >=  24 || m_byMin < 0 || m_byMin >= 60)
	{
		AfxMessageBox("输入的时间有误");
		return;
	}
	m_struRebootTime.dwSize = sizeof(NET_DVR_AUTO_REBOOT_CFG);
	m_struRebootTime.struRebootTime.byDate = m_comboDate.GetCurSel() + 1;
	m_struRebootTime.struRebootTime.byHour = m_byHour;
	m_struRebootTime.struRebootTime.byMinute = m_byMin;
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_AUTO_REBOOT_CFG, 0, &m_struRebootTime, sizeof(m_struRebootTime)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_AUTO_REBOOT_CFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_AUTO_REBOOT_CFG");
	}
}

BOOL CDlgAutoReboot::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here	
	memset(&m_struRebootTime, 0, sizeof(m_struRebootTime));
	OnBtnGet();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
