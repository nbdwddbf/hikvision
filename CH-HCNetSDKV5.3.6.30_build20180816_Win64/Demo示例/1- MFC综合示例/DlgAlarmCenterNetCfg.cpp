// DlgAlarmCenterNetCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmCenterNetCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmCenterNetCfg dialog


CDlgAlarmCenterNetCfg::CDlgAlarmCenterNetCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmCenterNetCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAlarmCenterNetCfg)
	m_csAuxiliaryAddr = _T("");
	m_iAuxiliaryPort = 0;
	m_csHostAddr1 = _T("");
	m_wHostPort1 = 0;
	m_csHostAddr2 = _T("");
	m_wHostPort2 = 0;
	m_csHostAddr3 = _T("");
	m_wHostPort3 = 0;
	m_csHostAddr4 = _T("");
	m_wHostPort4 = 0;
	m_csHostAddr5 = _T("");
	m_wHostPort5 = 0;
	m_csHostAddr6 = _T("");
	m_wHostPort6 = 0;
	//}}AFX_DATA_INIT
}


void CDlgAlarmCenterNetCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmCenterNetCfg)
	DDX_Text(pDX, IDC_EDT_AUXILIARY_ADDR, m_csAuxiliaryAddr);
	DDX_Text(pDX, IDC_EDT_AUXILIARY_PORT, m_iAuxiliaryPort);
	DDX_Text(pDX, IDC_EDIT_HOST_ADDR1, m_csHostAddr1);
	DDX_Text(pDX, IDC_EDIT_HOST_PORT1, m_wHostPort1);
	DDX_Text(pDX, IDC_EDIT_HOST_ADDR2, m_csHostAddr2);
	DDX_Text(pDX, IDC_EDIT_HOST_PORT2, m_wHostPort2);
	DDX_Text(pDX, IDC_EDIT_HOST_ADDR3, m_csHostAddr3);
	DDX_Text(pDX, IDC_EDIT_HOST_PORT3, m_wHostPort3);
	DDX_Text(pDX, IDC_EDIT_HOST_ADDR4, m_csHostAddr4);
	DDX_Text(pDX, IDC_EDIT_HOST_PORT4, m_wHostPort4);
	DDX_Text(pDX, IDC_EDIT_HOST_ADDR5, m_csHostAddr5);
	DDX_Text(pDX, IDC_EDIT_HOST_PORT5, m_wHostPort5);
	DDX_Text(pDX, IDC_EDIT_HOST_ADDR6, m_csHostAddr6);
	DDX_Text(pDX, IDC_EDIT_HOST_PORT6, m_wHostPort6);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmCenterNetCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmCenterNetCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmCenterNetCfg message handlers

void CDlgAlarmCenterNetCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here

	NET_DVR_ALARMCENTER_NETCFG struAlarmCenterNetCfg = {0};
	struAlarmCenterNetCfg.dwSize = sizeof(NET_DVR_ALARMCENTER_NETCFG);

	DWORD dwReturn = -1;
	char szLan[128] = {0};

	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_ALARMCENTER_NETCFG, 0, &struAlarmCenterNetCfg, sizeof(struAlarmCenterNetCfg), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMCENTER_NETCFG");
		g_StringLanType(szLan, "获取报警中心网络参数失败", "Get alarm center network paramter failed!");
		MessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARMCENTER_NETCFG");
		g_StringLanType(szLan, "获取报警中心网络参数成功", "Get alarm center network paramter Successful!");
	}

	m_iAuxiliaryPort = (int)struAlarmCenterNetCfg.wAuxiliaryAlarmPort;
	char czAuxiliaryAddr[MAX_DOMAIN_NAME+1] = {0};
	memcpy(czAuxiliaryAddr, struAlarmCenterNetCfg.byAuxiliaryAlarmAddr, MAX_DOMAIN_NAME);
	m_csAuxiliaryAddr = czAuxiliaryAddr;

	m_csHostAddr1 = struAlarmCenterNetCfg.struHostAddr[0].szDomainAddr;
	m_wHostPort1  = struAlarmCenterNetCfg.struHostAddr[0].wPort;

	m_csHostAddr2 = struAlarmCenterNetCfg.struHostAddr[1].szDomainAddr;
	m_wHostPort2  = struAlarmCenterNetCfg.struHostAddr[1].wPort;

	m_csHostAddr3 = struAlarmCenterNetCfg.struHostAddr[2].szDomainAddr;
	m_wHostPort3  = struAlarmCenterNetCfg.struHostAddr[2].wPort;

	m_csHostAddr4 = struAlarmCenterNetCfg.struHostAddr[3].szDomainAddr;
	m_wHostPort4  = struAlarmCenterNetCfg.struHostAddr[3].wPort;

	m_csHostAddr5 = struAlarmCenterNetCfg.struHostAddr[4].szDomainAddr;
	m_wHostPort5  = struAlarmCenterNetCfg.struHostAddr[4].wPort;

	m_csHostAddr6 = struAlarmCenterNetCfg.struHostAddr[5].szDomainAddr;
	m_wHostPort6  = struAlarmCenterNetCfg.struHostAddr[5].wPort;

	UpdateData(FALSE);
}

void CDlgAlarmCenterNetCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	NET_DVR_ALARMCENTER_NETCFG struAlarmCenterNetCfg = {0};
	struAlarmCenterNetCfg.dwSize = sizeof(NET_DVR_ALARMCENTER_NETCFG);

	struAlarmCenterNetCfg.wAuxiliaryAlarmPort = m_iAuxiliaryPort;
	memcpy(struAlarmCenterNetCfg.byAuxiliaryAlarmAddr, m_csAuxiliaryAddr, MAX_DOMAIN_NAME);

	strncpy((char*)struAlarmCenterNetCfg.struHostAddr[0].szDomainAddr,m_csHostAddr1.GetBuffer(0),MAX_DOMAIN_NAME);
	struAlarmCenterNetCfg.struHostAddr[0].wPort = m_wHostPort1;
	
	strncpy((char*)struAlarmCenterNetCfg.struHostAddr[1].szDomainAddr,m_csHostAddr2.GetBuffer(0),MAX_DOMAIN_NAME);
	struAlarmCenterNetCfg.struHostAddr[1].wPort = m_wHostPort2;
	
	strncpy((char*)struAlarmCenterNetCfg.struHostAddr[2].szDomainAddr,m_csHostAddr3.GetBuffer(0),MAX_DOMAIN_NAME);
	struAlarmCenterNetCfg.struHostAddr[2].wPort = m_wHostPort3;
	
	strncpy((char*)struAlarmCenterNetCfg.struHostAddr[3].szDomainAddr,m_csHostAddr4.GetBuffer(0),MAX_DOMAIN_NAME);
	struAlarmCenterNetCfg.struHostAddr[3].wPort = m_wHostPort4;
	
	strncpy((char*)struAlarmCenterNetCfg.struHostAddr[4].szDomainAddr,m_csHostAddr5.GetBuffer(0),MAX_DOMAIN_NAME);
	struAlarmCenterNetCfg.struHostAddr[4].wPort = m_wHostPort5;
	
	strncpy((char*)struAlarmCenterNetCfg.struHostAddr[5].szDomainAddr,m_csHostAddr6.GetBuffer(0),MAX_DOMAIN_NAME);
	struAlarmCenterNetCfg.struHostAddr[5].wPort = m_wHostPort6;

	char szLan[128] = {0};

	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_ALARMCENTER_NETCFG, 0, &struAlarmCenterNetCfg, sizeof(struAlarmCenterNetCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_ALARMCENTER_NETCFG");
		g_StringLanType(szLan, "设置报警中心网络参数失败", "Set alarm center network paramter Failed");
		MessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_ALARMCENTER_NETCFG");
		g_StringLanType(szLan, "设置报警中心网络参数成功", "Set alarm center network paramter Successful");
	}
}

BOOL CDlgAlarmCenterNetCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	
	OnBtnGet();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
