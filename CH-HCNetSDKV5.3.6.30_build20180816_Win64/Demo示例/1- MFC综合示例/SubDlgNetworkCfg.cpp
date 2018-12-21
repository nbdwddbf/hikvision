// SubDlgNetworkCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "SubDlgNetworkCfg.h"
#include "DlgRemoteAdvanceNetConfig.h"
#include "DialogMultiNetCard.h"
#include "DlgWifi.h"
#include "DlgNetworkFlowTest.h"
#include "MatDecDnsCfg.h"
#include "DlgNetworkBonding.h"
#include "DlgEthernetIpv6Cfg.h"
#include "DlgUpnpCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubDlgNetworkCfg dialog


CSubDlgNetworkCfg::CSubDlgNetworkCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubDlgNetworkCfg::IDD, pParent)
    , m_bDNS(FALSE)
    , m_csAlarmHostIP2(_T(""))
    , m_iAlarmHostPort2(0)
    , m_strEthernetPort(_T(""))
{
	//{{AFX_DATA_INIT(CSubDlgNetworkCfg)
	//}}AFX_DATA_INIT
	m_iDeviceIndex = -1;
	m_lLoginID = -1;
	m_lIpTest = -1;
	m_hIpTest = NULL;
	m_iMainPort = 0;
	m_iMainPort2 = 0;
	m_iHttpPort = 0;
	m_iAlarmHostPort = 0;
	m_wMTU = 0;
	memset(&m_struNetCfg,0,sizeof(m_struNetCfg));
}


void CSubDlgNetworkCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CSubDlgNetworkCfg)
    DDX_Control(pDX, IDC_SUB_COMBO_NET_FACE, m_comboNetFace);
    DDX_Check(pDX, IDC_CHK_DHCP, m_bChkDhcp);
    DDX_Text(pDX, IDC_SUB_EDIT_DEVIP, m_csDeviceIP);
    DDX_Text(pDX, IDC_SUB_EDIT_IPMASK, m_csIPMask);
    DDX_Text(pDX, IDC_SUB_EDIT_GATEWAY, m_csGatewayIP);
    DDX_Text(pDX, IDC_SUB_EDIT_DNS_IP1, m_csDNSIP1);
    DDX_Text(pDX, IDC_SUB_DNS_IP2, m_csDNSIP2);
    DDX_Text(pDX, IDC_SUB_EDIT_MACIP, m_csMacAddr);
    DDX_Text(pDX, IDC_SUB_EDIT_RESOLVER_IP, m_csIPResolver);
    DDX_Text(pDX, IDC_SUB_EDIT_PORT, m_iMainPort);
    DDX_Text(pDX, IDC_SUB_EDIT_PORT2, m_iMainPort2);
    DDX_Text(pDX, IDC_SUB_EDIT_HTTP_PORT, m_iHttpPort);
    DDX_Text(pDX, IDC_SUB_EDIT_MULTIIP, m_csMultiIP);
    DDX_Text(pDX, IDC_SUB_ALARM_HOSTIP, m_csAlarmHostIP);
    DDX_Text(pDX, IDC_SUB_ALARM_HOST_PORT, m_iAlarmHostPort);
    DDX_Text(pDX, IDC_SUB_MTU, m_wMTU);
    DDX_Control(pDX, IDC_SUB_COMBO_IPV6_MODE, m_comboIPv6Mode);
    DDX_Check(pDX, IDC_CHK_PRIVATE_MULTICAST_DISCOVERY, m_bEnablePrivateMulticastDiscovery);
    DDX_Check(pDX, IDC_CHK_ONVIF_MULTICAST_DISCOVERY, m_bEnableOnvifMulticastDiscovery);
    DDX_Check(pDX, IDC_CHECK_DNS_ENABLE, m_bDNS);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_SUB_ALARM_HOSTIP2, m_csAlarmHostIP2);
    DDX_Text(pDX, IDC_SUB_ALARM_HOST_PORT2, m_iAlarmHostPort2);
    DDX_Text(pDX, IDC_EDIT_ETHERNET_PORT, m_strEthernetPort);
    DDX_Control(pDX, IDC_COMBO_SHOW_MODE, m_comboShowMode);
}


BEGIN_MESSAGE_MAP(CSubDlgNetworkCfg, CDialog)
	//{{AFX_MSG_MAP(CSubDlgNetworkCfg)
	ON_BN_CLICKED(IDC_BTN_IP_TEST, OnBtnIpTest)
	ON_BN_CLICKED(IDC_BTN_ADVANCE_NET_SETUP, OnBtnAdvanceNetSetup)
	ON_BN_CLICKED(IDC_BTN_BONDING_CFG, OnBtnBondingCfg)
	ON_BN_CLICKED(IDC_BTN_GET_ETHERNET_IPV6_CFG, OnBtnGetEthernetIpv6Cfg)
	ON_BN_CLICKED(IDC_BTN_HIGH_NET_CFG, OnBtnHighNetCfg)
	ON_BN_CLICKED(IDC_BTN_MAT_DEC_DNS, OnBtnMatDecDns)
	ON_BN_CLICKED(IDC_BTN_NETWORK_FLOWTEST, OnBtnNetworkFlowtest)
	ON_BN_CLICKED(IDC_BTN_WIFI_CONFIG, OnBtnWifiConfig)
	ON_BN_CLICKED(IDC_BUTTON_MULT_NETCARD, OnButtonMultNetcard)
	ON_BN_CLICKED(IDC_BUTTON_UPNP, OnButtonUpnp)
	ON_BN_CLICKED(IDC_CHK_DHCP, OnChkDhcp)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_CHECK_DNS_ENABLE, &CSubDlgNetworkCfg::OnBnClickedCheckDnsEnable)
    ON_CBN_SELCHANGE(IDC_COMBO_SHOW_MODE, &CSubDlgNetworkCfg::OnCbnSelchangeComboShowMode)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubDlgNetworkCfg message handlers
BOOL CSubDlgNetworkCfg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rc(0, 0, 0, 0);
    GetParent()->GetClientRect(&rc);
    ((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);
    UpdateData(TRUE);
    GetDlgItem(IDC_SUB_EDIT_DEVIP)->EnableWindow(!m_bChkDhcp);
    GetDlgItem(IDC_SUB_EDIT_IPMASK)->EnableWindow(!m_bChkDhcp);
    GetDlgItem(IDC_SUB_EDIT_GATEWAY)->EnableWindow(!m_bChkDhcp);
    //	GetDlgItem(IDC_SUB_EDIT_DNS_IP1)->EnableWindow(!m_bChkDhcp);
    //	GetDlgItem(IDC_SUB_DNS_IP2)->EnableWindow(!m_bChkDhcp);
    if (m_bChkDhcp == FALSE)
    {
        GetDlgItem(IDC_CHECK_DNS_ENABLE)->EnableWindow(m_bChkDhcp);
        GetDlgItem(IDC_SUB_EDIT_DNS_IP1)->EnableWindow(!m_bChkDhcp);
        GetDlgItem(IDC_SUB_DNS_IP2)->EnableWindow(!m_bChkDhcp);
        m_bDNS = FALSE;
    }
    else
    {
        GetDlgItem(IDC_CHECK_DNS_ENABLE)->EnableWindow(m_bChkDhcp);
    }
    UpdateData(FALSE);
	return TRUE;
}

void CSubDlgNetworkCfg::OnBtnIpTest() 
{
	UpdateData(TRUE);
	NET_DVR_SERVER_TEST_PARA struIpTest;
	memset(&struIpTest, 0, sizeof(struIpTest));
	struIpTest.dwSize = sizeof(struIpTest);
	
    int iShowMode = m_comboShowMode.GetCurSel();
    if (iShowMode == 0)
    {
        //ipv4
        sprintf((char *)struIpTest.unionServerPara.struIpPara.struIp.sIpV4, m_csDeviceIP);
    }
    else if (iShowMode == 1)
    {
        //ipv6
        sprintf((char *)struIpTest.unionServerPara.struIpPara.struIp.byIPv6, m_csDeviceIP);
    }
	
	m_lIpTest = NET_DVR_StartRemoteConfig(m_lLoginID, NET_DVR_IP_TEST, &struIpTest, sizeof(struIpTest), NULL, this);
	if (m_lIpTest >= 0)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Start Remote Config successfully");
		DWORD dwThreadId;
		m_hIpTest = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetServerTestInfoThread1), this, 0, &dwThreadId);
	} 
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Start Remote Config failed");
		return;
	}
}

void CSubDlgNetworkCfg::OnBtnAdvanceNetSetup() 
{
	CDlgRemoteAdvanceNetConfig dlg;
	dlg.m_pPPPoECfg = &m_struNetCfg.struPPPoE;
	dlg.m_lServerID = m_lLoginID;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.DoModal();
}

void CSubDlgNetworkCfg::OnBtnBondingCfg() 
{
	CDlgNetworkBonding dlg;
    dlg.m_lServerID = m_lLoginID;
    dlg.m_iDevIndex = g_pMainDlg->GetCurDeviceIndex();
    dlg.m_dwNetworkNum = 16;     // 网卡数目 todo!!!
    dlg.DoModal();
}

void CSubDlgNetworkCfg::OnBtnGetEthernetIpv6Cfg() 
{
	CDlgEthernetIpv6Cfg dlg;
	dlg.m_lUserID = m_lLoginID;
	dlg.m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	dlg.DoModal();
}

void CSubDlgNetworkCfg::OnBtnHighNetCfg() 
{
	// TODO: Add your control notification handler code here
	
}

void CSubDlgNetworkCfg::OnBtnMatDecDns() 
{
	CDlgRemoteMatDecDnsCfg dlg;
	dlg.m_lLoginID = m_lLoginID;
	dlg.DoModal();
}

void CSubDlgNetworkCfg::OnBtnNetworkFlowtest() 
{
	CDlgNetworkFlowTest dlg;
    dlg.m_lServerID = m_lLoginID;
    dlg.m_iDevIndex = g_pMainDlg->GetCurDeviceIndex();
    dlg.DoModal();
}

void CSubDlgNetworkCfg::OnBtnWifiConfig() 
{
	CDlgWifi dlg;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.DoModal();
}

void CSubDlgNetworkCfg::OnButtonMultNetcard() 
{
	CDialogMultiNetCard dlg;
    dlg.DoModal();
}

void CSubDlgNetworkCfg::OnButtonUpnp() 
{
	CDlgUpnpCfg dlg;
	dlg.m_lUserID = m_lLoginID;
    dlg.m_dwDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    dlg.DoModal();
}

void CSubDlgNetworkCfg::OnChkDhcp() 
{
	UpdateData(TRUE);
	EnableDhcp();
}


void CSubDlgNetworkCfg::EnableDhcp()
{
	GetDlgItem(IDC_SUB_EDIT_DEVIP)->EnableWindow(!m_bChkDhcp);
	GetDlgItem(IDC_SUB_EDIT_IPMASK)->EnableWindow(!m_bChkDhcp);
	GetDlgItem(IDC_SUB_EDIT_GATEWAY)->EnableWindow(!m_bChkDhcp);
    //	GetDlgItem(IDC_SUB_EDIT_DNS_IP1)->EnableWindow(!m_bChkDhcp);
    //	GetDlgItem(IDC_SUB_DNS_IP2)->EnableWindow(!m_bChkDhcp);
    if (m_bChkDhcp == FALSE)
    {
        GetDlgItem(IDC_CHECK_DNS_ENABLE)->EnableWindow(m_bChkDhcp);
        GetDlgItem(IDC_SUB_EDIT_DNS_IP1)->EnableWindow(!m_bChkDhcp);
        GetDlgItem(IDC_SUB_DNS_IP2)->EnableWindow(!m_bChkDhcp);
        m_bDNS = FALSE;
    }
    else
    {
        GetDlgItem(IDC_CHECK_DNS_ENABLE)->EnableWindow(m_bChkDhcp);
    }
    UpdateData(FALSE);
}

BOOL CSubDlgNetworkCfg::CfgSetup()
{    
	BOOL bRet = TRUE;
	char szLan[128] = {0};
    m_struNetCfg.dwSize = sizeof(m_struNetCfg);
    if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_NETCFG_V50, 0, &(m_struNetCfg), sizeof(NET_DVR_NETCFG_V50)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_NETCFG_V50");
		g_StringLanType(szLan, "网络参数保存失败", "Save Network configuration failed");
		AfxMessageBox(szLan);
		bRet = FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_NETCFG_V50");
	}
	//setting succeed, save device configurtaion
	
    int iShowMode = m_comboShowMode.GetCurSel();
    if (iShowMode == 0)
    {
        //ipv4
        sprintf(g_struDeviceInfo[m_iDeviceIndex].chDeviceMultiIP, "%s", m_struNetCfg.struMulticastIpAddr.sIpV4);
    }
    else if (iShowMode == 1)
    {
        //ipv6
        sprintf(g_struDeviceInfo[m_iDeviceIndex].chDeviceMultiIP, "%s", m_struNetCfg.struMulticastIpAddr.byIPv6);
    }
    return bRet;
}

void CSubDlgNetworkCfg::OnBtnSet() 
{
    UpdateData(TRUE);
    char szLan[128] = {0};

    if (m_iMainPort <= 0)
    {
        g_StringLanType(szLan, "非法的设备端口号", "Illegal device port number");
        AfxMessageBox(szLan);
    return;
    }

    if (m_iMainPort2 <= 0)
    {
        g_StringLanType(szLan, "非法的设备端口号2", "Illegal device port number2");
        //AfxMessageBox(szLan);
        //return;
    }

    if (/*(m_csDeviceIP == "0.0.0.0") ||*/ (m_csDeviceIP == "") || (!CheckIPStr(m_csDeviceIP) && 
    !ValidIPv6((BYTE*)m_csDeviceIP.GetBuffer(m_csDeviceIP.GetLength()))))
    {
        g_StringLanType(szLan, "非法的设备IP地址", "Illegal device ip address");
        AfxMessageBox(szLan);
        return;
    }

    if (!CheckIPStr(m_csIPMask) && !ValidIPv6((BYTE*)m_csIPMask.GetBuffer(m_csIPMask.GetLength())))
    {
        g_StringLanType(szLan, "非法的掩码地址", "Illegal device MAC address");
        AfxMessageBox(szLan);
        return;
    }

    if (m_comboNetFace.GetCurSel() == 5)//1000M full
    {	
        g_StringLanType(szLan, "请确认为1000M网络，否则无法再登陆设备", "Please this is 1000M network, or can not login device again");
        if (IDOK != MessageBox(szLan, "Waring", IDOK))
        {
            return;
        }
    }

    if (!CheckIPStr(m_csMultiIP) && !ValidIPv6((BYTE*)m_csMultiIP.GetBuffer(m_csMultiIP.GetLength())))
    {
        g_StringLanType(szLan, "非法的多播IP地址", "Illegal Multicast address");
        AfxMessageBox(szLan);
        return;
    }

    if (!CheckIPStr(m_csGatewayIP) && !ValidIPv6((BYTE*)m_csGatewayIP.GetBuffer(m_csGatewayIP.GetLength())))
    {
        g_StringLanType(szLan, "非法的网关IP地址", "Illegal Gateway ip address");
        AfxMessageBox(szLan);
        return;
    }

// 	if (!CheckIPStr(m_csRemoteManageHost1IP) && !ValidIPv6((BYTE*)m_csRemoteManageHost1IP.GetBuffer(m_csRemoteManageHost1IP.GetLength())))
// 	{
// 		g_StringLanType(szLan, "非法的管理主机IP地址", "Illegal Manage host ip address");
// 		AfxMessageBox(szLan);
// 		return; 
// 	}

//Save device configuration
    //2010-01-16
//     m_struDeviceCfg.bySubProto = m_comboSubProtocol.GetCurSel();
//     m_struDeviceCfg.byMainProto = m_comboMainProtocol.GetCurSel();
    //m_struDeviceCfg.byIPCPlug = m_comboPlug.GetCurSel();
    //m_struDeviceCfg.byEsataUseage = m_comboEsata.GetCurSel(); 
	//m_struDeviceCfg.byZeroChanNum = m_iZeroChanNum;
    //m_struDeviceCfg.byStorageMode = m_comboStorageMode.GetCurSel();

	//m_struDeviceCfg.dwDVRID = m_iYKQID;
	//memcpy(m_struDeviceCfg.sDVRName, m_csDeviceName, NAME_LEN);	
//	m_struDeviceCfg.dwRecycleRecord = m_comboCycleRec.GetCurSel();
	//if (m_bSupScale)
	//{
//		//m_dwUseZoom = m_comboUseZoom.GetCurSel();	
//	}
//	m_bDeviceCfgSet = TRUE;

//Save network configuration
    if (m_bEnablePrivateMulticastDiscovery == 0)
    {
        m_struNetCfg.byEnablePrivateMulticastDiscovery = 2;
    }
    else
    {
        m_struNetCfg.byEnablePrivateMulticastDiscovery = 1;	
    }

    if (m_bEnableOnvifMulticastDiscovery == 0)
    {
        m_struNetCfg.byEnableOnvifMulticastDiscovery = 2;
    }
    else
    {
        m_struNetCfg.byEnableOnvifMulticastDiscovery = 1;	
    }

    m_struNetCfg.byUseDhcp = (BYTE)m_bChkDhcp;

    //手动切换显示模式，add by qianshuo 2018-6-2
    int iShowMode = m_comboShowMode.GetCurSel();
    if (iShowMode == 0)
    {
        //ipv4
        strncpy(m_struNetCfg.struEtherNet[0].struDVRIP.sIpV4, m_csDeviceIP, 16);
        strncpy(m_struNetCfg.struEtherNet[0].struDVRIPMask.sIpV4, m_csIPMask, 16);
        memset(&m_struNetCfg.struMulticastIpAddr.byIPv6, 0, 128);//2013-09-03
        strncpy(m_struNetCfg.struMulticastIpAddr.sIpV4, m_csMultiIP, 16);
        strncpy(m_struNetCfg.struGatewayIpAddr.sIpV4, m_csGatewayIP, 16);
        strncpy(m_struNetCfg.struDnsServer1IpAddr.sIpV4, m_csDNSIP1, 16);
        strncpy(m_struNetCfg.struDnsServer2IpAddr.sIpV4, m_csDNSIP2, 16);
        memset(&m_struNetCfg.struAlarmHostIpAddr.byIPv6, 0, 128);//2013-09-03
        strncpy(m_struNetCfg.struAlarmHostIpAddr.sIpV4, m_csAlarmHostIP, 16);
        memset(&m_struNetCfg.struAlarmHost2IpAddr.byIPv6, 0, 128);//2013-09-03
        strncpy(m_struNetCfg.struAlarmHost2IpAddr.sIpV4, m_csAlarmHostIP2, 16);
    }
    else if (iShowMode == 1)
    {
        //ipv6
        strncpy((char *)m_struNetCfg.struEtherNet[0].struDVRIP.byIPv6, m_csDeviceIP, 128);
        strncpy((char *)m_struNetCfg.struEtherNet[0].struDVRIPMask.byIPv6, m_csIPMask, 128);
        memset(&m_struNetCfg.struMulticastIpAddr.sIpV4, 0, 16);//2013-09-03
        strncpy((char *)m_struNetCfg.struMulticastIpAddr.byIPv6, m_csMultiIP, 128);
        strncpy((char *)m_struNetCfg.struGatewayIpAddr.byIPv6, m_csGatewayIP, 128);
        strncpy((char *)m_struNetCfg.struDnsServer1IpAddr.byIPv6, m_csDNSIP1, 128);
        strncpy((char *)m_struNetCfg.struDnsServer2IpAddr.byIPv6, m_csDNSIP2, 128);
        memset(&m_struNetCfg.struAlarmHostIpAddr.sIpV4, 0, 16);//2013-09-03
        strncpy((char *)m_struNetCfg.struAlarmHostIpAddr.byIPv6, m_csAlarmHostIP, 128);
        memset(&m_struNetCfg.struAlarmHost2IpAddr.sIpV4, 0, 16);//2013-09-03
        strncpy((char *)m_struNetCfg.struAlarmHost2IpAddr.byIPv6, m_csAlarmHostIP2, 128);
    }

	memcpy(m_struNetCfg.byIpResolver, m_csIPResolver, MAX_DOMAIN_NAME);
	//m_struNetCfg.wIpResolverPort = m_iResolverPort;

	m_struNetCfg.struEtherNet[0].wDVRPort = (WORD)m_iMainPort;
	m_struNetCfg.struEtherNet[1].wDVRPort = (WORD)m_iMainPort2;
	m_struNetCfg.struEtherNet[0].wMTU = m_wMTU;
// 	memcpy(m_struNetCfg.struManageHost1IpAddr.sIpV4, m_csRemoteManageHost1IP,16);
// 	m_struNetCfg.wManageHost1Port = m_iRemoteManageHost1Port;
// 	memcpy(m_struNetCfg.struManageHost2IpAddr.sIpV4, m_csAuxoManageHostIP,16);
// 	m_struNetCfg.wManageHost2Port = m_iAuxoManagePort;
    m_struNetCfg.wAlarmHostIpPort = (WORD)m_iAlarmHostPort;
    m_struNetCfg.wAlarmHost2IpPort = (WORD)m_iAlarmHostPort2;

    m_struNetCfg.struEtherNet[0].dwNetInterface = m_comboNetFace.GetCurSel()+1;
    m_struNetCfg.byIPv6Mode = m_comboIPv6Mode.GetCurSel();
    m_struNetCfg.wHttpPortNo = (WORD)m_iHttpPort;
    if (m_bDNS)
    {
        m_struNetCfg.byEnableDNS = 1;
    }
    else
    {
        m_struNetCfg.byEnableDNS = 2;
    }
	//m_struDeviceCfg.byLockFrontPanel.GetCurSel();
	//m_bNetCfgSet = TRUE;
	g_bMustReboot = g_pMainDlg->IsNeedRebootDevType();
}

BOOL CSubDlgNetworkCfg::ValidIPv6(BYTE *ip)
{
 	if (strlen((char *)ip) >= 2 && strchr((char *)ip, ':') != NULL)
 	{
        return TRUE;
    }
    return FALSE;
}

BOOL CSubDlgNetworkCfg::CheckInitParam()
{
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	DWORD dwReturned = 0;
	char szLan[128] = {0};

	if (iDeviceIndex == -1)
	{
		return FALSE;
	}

	if (m_iDeviceIndex == iDeviceIndex)
	{
		return TRUE;
	}
	else
	{
		m_iDeviceIndex = iDeviceIndex;
		m_lLoginID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	}

	m_csIPResolver = _T("");
	m_csDeviceIP = _T("");
	m_csMultiIP = _T("");
	m_iMainPort = 0;
	m_iMainPort2 = 0;
	m_csGatewayIP = _T("");
	m_csIPMask = _T("");
	m_csMacAddr = _T("");
	m_iHttpPort = 0;

	if (m_lLoginID < 0)
	{
		return FALSE;
	}
    memset(&m_struNetCfg, 0, sizeof(NET_DVR_NETCFG_V50));
    if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_NETCFG_V50, 0, &m_struNetCfg, sizeof(NET_DVR_NETCFG_V50), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_NETCFG_V50");
		g_StringLanType(szLan, "获取网络参数失败", "Get Network Configure failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_NETCFG_V50");
	}

	UpdateData(FALSE);
	return TRUE;
}

void CSubDlgNetworkCfg::CurCfgUpdate()
{
	if (!CheckInitParam())
	{
		UpdateData(FALSE);
		EnableWindow(FALSE);
		return;
	}
	EnableWindow(TRUE);
	
	char cTemp[200] = {0};
    char szLan[128] = {0};
   
	if (m_struNetCfg.byUseDhcp == 0xff)
	{
		GetDlgItem(IDC_CHK_DHCP)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_CHK_DHCP)->EnableWindow(TRUE);
		m_bChkDhcp = m_struNetCfg.byUseDhcp;
		EnableDhcp();
	}

    if (m_struNetCfg.byEnablePrivateMulticastDiscovery == 2)
    {
        m_bEnablePrivateMulticastDiscovery = 0;
    }
    else if(m_struNetCfg.byEnablePrivateMulticastDiscovery == 1)
    {
        m_bEnablePrivateMulticastDiscovery = 1;
    }

    if (m_struNetCfg.byEnableOnvifMulticastDiscovery == 2)
    {
        m_bEnableOnvifMulticastDiscovery = 0;
    }
    else if(m_struNetCfg.byEnableOnvifMulticastDiscovery == 1)
    {
        m_bEnableOnvifMulticastDiscovery = 1;
    }

    if (m_struNetCfg.byEnableDNS == 1)
    {
        m_bDNS = 1;
    }
    else if (m_struNetCfg.byEnableDNS == 2)
    {
        m_bDNS = 0;
    }
    EnableDns();
	m_csIPResolver = m_struNetCfg.byIpResolver;
	//2011-7-19,对使用ipv6登陆的设备，优先显示其ipv6地址
	BOOL bShowIpv6 = ValidIPv6((BYTE*)g_struDeviceInfo[m_iDeviceIndex].chDeviceIP);
    int iShowMode = 0;
    if (bShowIpv6)
    {
        //ipv6
        iShowMode = 1;
    }
    else
    {
        //ipv4
        iShowMode = 0;
    }
    m_comboShowMode.SetCurSel(iShowMode);
    ShowNetworkCfg(iShowMode);

    m_csMacAddr.Format("%02x:%02x:%02x:%02x:%02x:%02x", m_struNetCfg.struEtherNet[0].byMACAddr[0], m_struNetCfg.struEtherNet[0].byMACAddr[1], m_struNetCfg.struEtherNet[0].byMACAddr[2], m_struNetCfg.struEtherNet[0].byMACAddr[3], m_struNetCfg.struEtherNet[0].byMACAddr[4], m_struNetCfg.struEtherNet[0].byMACAddr[5]);

    m_wMTU = m_struNetCfg.struEtherNet[0].wMTU;
    m_iMainPort = m_struNetCfg.struEtherNet[0].wDVRPort;
    m_iMainPort2 = m_struNetCfg.struEtherNet[1].wDVRPort;

    m_iAlarmHostPort = m_struNetCfg.wAlarmHostIpPort;
    m_iAlarmHostPort2 = m_struNetCfg.wAlarmHost2IpPort;
    ZeroMemory(cTemp, 200);
    memcpy(cTemp, m_struNetCfg.byIpResolver, MAX_DOMAIN_NAME);
    m_csIPResolver = cTemp;

    m_comboNetFace.SetCurSel(m_struNetCfg.struEtherNet[0].dwNetInterface - 1);
    m_iHttpPort = m_struNetCfg.wHttpPortNo;
    m_comboIPv6Mode.SetCurSel(m_struNetCfg.byIPv6Mode);

    if (m_struNetCfg.struEtherNet[0].byEthernetPortNo > 0)
    {
        m_strEthernetPort.Format("Port %d", m_struNetCfg.struEtherNet[0].byEthernetPortNo - 1);
    }

    UpdateData(FALSE);
}


DWORD WINAPI CSubDlgNetworkCfg::GetServerTestInfoThread1(LPVOID lpArg)
{
	CSubDlgDeviceCfg* pThis = reinterpret_cast<CSubDlgDeviceCfg*>(lpArg);
	DWORD dwState = 0;
	CString csErrInfo;
	while (1)
	{
		
		if (!NET_DVR_GetRemoteConfigState(pThis->m_lIpTest, &dwState))
		{
			g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetRemoteConfigState NET_DVR_FIND_NAS_DIRECTORY ");
			pThis->GetDlgItem(IDC_STATIC_IP_TEST)->SetWindowText("Get state Fail!");
			NET_DVR_StopRemoteConfig(pThis->m_lIpTest);
			return -1;
		}
		else
		{
			if (dwState == PROCESSING)
			{
				pThis->GetDlgItem(IDC_STATIC_IP_TEST)->SetWindowText("Testing...");
				Sleep(1000);
			}
			else if (dwState == PROCESS_SUCCESS)
			{
				pThis->GetDlgItem(IDC_STATIC_IP_TEST)->SetWindowText("Test Success!");
				break;
			}
			else if (dwState == PROCESS_EXCEPTION)
			{
				pThis->GetDlgItem(IDC_STATIC_IP_TEST)->SetWindowText("Test Exception!");
				break;
			}
			else
			{
				csErrInfo.Format("Test Fail %d", dwState);
				pThis->GetDlgItem(IDC_STATIC_IP_TEST)->SetWindowText(csErrInfo);
				break;
			}
		}
		
	}
	if (-1 != pThis->m_lIpTest)
	{
		if (!NET_DVR_StopRemoteConfig(pThis->m_lIpTest))
		{
			g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_FAIL_T, "Stop Remote Config Failed");
		}
		else
		{
			g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_SUCC_T, "Stop Remote Config Successful");
			pThis->m_lIpTest = -1;
		}
	}
	return 0 ;
}

void CSubDlgNetworkCfg::OnBnClickedCheckDnsEnable()
{
    UpdateData(TRUE);
    EnableDns();
}

void CSubDlgNetworkCfg::EnableDns()
{
    GetDlgItem(IDC_SUB_EDIT_DNS_IP1)->EnableWindow(!m_bDNS);
    GetDlgItem(IDC_SUB_DNS_IP2)->EnableWindow(!m_bDNS);
}

void CSubDlgNetworkCfg::OnCbnSelchangeComboShowMode()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    int iShowMode = m_comboShowMode.GetCurSel();
    ShowNetworkCfg(iShowMode);
    UpdateData(FALSE);
}


// iShowMode:0表示显示ipv4,1表示显示ipv6
void CSubDlgNetworkCfg::ShowNetworkCfg(int iShowMode)
{
    if (iShowMode == 0)
    {
        //显示ipv4
        m_csGatewayIP.Format("%s", m_struNetCfg.struGatewayIpAddr.sIpV4);
        m_csDeviceIP.Format("%s", m_struNetCfg.struEtherNet[0].struDVRIP.sIpV4);
        m_csIPMask.Format("%s", m_struNetCfg.struEtherNet[0].struDVRIPMask.sIpV4);
        m_csMultiIP.Format("%s", m_struNetCfg.struMulticastIpAddr.sIpV4);
        m_csDNSIP1.Format("%s", m_struNetCfg.struDnsServer1IpAddr.sIpV4);
        m_csDNSIP2.Format("%s", m_struNetCfg.struDnsServer2IpAddr.sIpV4);
        m_csAlarmHostIP.Format("%s", m_struNetCfg.struAlarmHostIpAddr.sIpV4);
        m_csAlarmHostIP2.Format("%s", m_struNetCfg.struAlarmHost2IpAddr.sIpV4);
    }
    else if (iShowMode == 1)
    {
        //显示ipv6
        m_csGatewayIP.Format("%s", m_struNetCfg.struGatewayIpAddr.byIPv6);
        m_csDeviceIP.Format("%s", m_struNetCfg.struEtherNet[0].struDVRIP.byIPv6);
        m_csIPMask.Format("%s", m_struNetCfg.struEtherNet[0].struDVRIPMask.byIPv6);
        m_csMultiIP.Format("%s", m_struNetCfg.struMulticastIpAddr.byIPv6);
        m_csDNSIP1.Format("%s", m_struNetCfg.struDnsServer1IpAddr.byIPv6);
        m_csDNSIP2.Format("%s", m_struNetCfg.struDnsServer2IpAddr.byIPv6);
        m_csAlarmHostIP.Format("%s", m_struNetCfg.struAlarmHostIpAddr.byIPv6);
        m_csAlarmHostIP2.Format("%s", m_struNetCfg.struAlarmHost2IpAddr.byIPv6);
    }
}
