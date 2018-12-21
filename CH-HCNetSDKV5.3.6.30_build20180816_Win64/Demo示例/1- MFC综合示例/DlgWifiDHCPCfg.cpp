// DlgWifiDHCPCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgWifiDHCPCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWifiDHCPCfg dialog


CDlgWifiDHCPCfg::CDlgWifiDHCPCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWifiDHCPCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgWifiDHCPCfg)
	m_strEndIPAddr = _T("");
	m_strStartIPAddr = _T("");
	//}}AFX_DATA_INIT
}


void CDlgWifiDHCPCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWifiDHCPCfg)
	DDX_Text(pDX, IDC_EDIT_END_IP, m_strEndIPAddr);
	DDX_Text(pDX, IDC_EDIT_START_IP, m_strStartIPAddr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWifiDHCPCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgWifiDHCPCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWifiDHCPCfg message handlers

BOOL CDlgWifiDHCPCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	OnBtnGet();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgWifiDHCPCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	
	char szLan[128] = {0};
	NET_DVR_WIFI_DHCP_ADDR_CFG struWifiDHCPCfg = {0};
	memset(&struWifiDHCPCfg, 0, sizeof(NET_DVR_WIFI_DHCP_ADDR_CFG));
	
	DWORD dwReturnedBytes = 0;
	
	if(NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_WIFI_DHCP_ADDR_CFG, 0, &struWifiDHCPCfg, sizeof(NET_DVR_WIFI_DHCP_ADDR_CFG), &dwReturnedBytes))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_WIFI_DHCP_ADDR_CFG");
		g_StringLanType(szLan, "获取无线DHCP地址范围参数配置成功!", "Success to get wifi DHCP address range parameter config");
		//	AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_WIFI_DHCP_ADDR_CFG");
		g_StringLanType(szLan, "获取无线DHCP地址范围参数配置失败!", "Fail to get wifi DHCP address range parameter config");
		AfxMessageBox(szLan);
		return;
	}

	char szTemp[16] = {0};
	memcpy(szTemp, struWifiDHCPCfg.struStartAddr.sIpV4, 16);
	m_strStartIPAddr = szTemp;
	memcpy(szTemp, struWifiDHCPCfg.struEndAddr.sIpV4, 16);
	m_strEndIPAddr = szTemp;
	
	UpdateData(FALSE);
}

void CDlgWifiDHCPCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);
	
	char szLan[128] = {0};
	NET_DVR_WIFI_DHCP_ADDR_CFG struWifiDHCPCfg = {0};
	memset(&struWifiDHCPCfg, 0, sizeof(NET_DVR_WIFI_DHCP_ADDR_CFG));
	
	struWifiDHCPCfg.dwSize = sizeof(NET_DVR_WIFI_DHCP_ADDR_CFG);

	memcpy(struWifiDHCPCfg.struStartAddr.sIpV4, (LPTSTR)(LPCTSTR)m_strStartIPAddr, 16);
	memcpy(struWifiDHCPCfg.struEndAddr.sIpV4, (LPTSTR)(LPCTSTR)m_strEndIPAddr, 16);
	
	if(NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_WIFI_DHCP_ADDR_CFG, 0, &struWifiDHCPCfg, sizeof(NET_DVR_WIFI_DHCP_ADDR_CFG)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_WIFI_DHCP_ADDR_CFG");
		g_StringLanType(szLan, "设置无线DHCP地址范围参数配置成功!", "Success to set wifi DHCP address range parameter config");
		//	AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_WIFI_DHCP_ADDR_CFG");
		g_StringLanType(szLan, "设置无线DHCP地址范围参数配置失败!", "Fail to set wifi DHCP address range parameter config");
		AfxMessageBox(szLan);
		return;
	}

    UpdateData(FALSE);
}
