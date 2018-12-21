// DlgWIFIServerCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgWIFIServerCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWIFIServerCfg dialog


CDlgWIFIServerCfg::CDlgWIFIServerCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWIFIServerCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgWIFIServerCfg)
	m_bChkWifiAP = FALSE;
	m_bChkBroadcast = FALSE;
	m_bChkDHCP = FALSE;
	m_bChkWlanShare = FALSE;
	m_csDNS1 = _T("");
	m_csDNS2 = _T("");
	m_csSSID = _T("");
	m_csEndIP = _T("");
	m_csGateway = _T("");
	m_csIP = _T("");
	m_csIPMask = _T("");
	m_csStartIP = _T("");
	m_csEncryptionKey1 = _T("");
	m_csEncryptionKey2 = _T("");
	m_csEncryptionKey3 = _T("");
	m_csEncryptionKey4 = _T("");
	m_csSharedKey = _T("");
	m_bCHKDefaultPass = FALSE;
	m_byWPAKeyLen = 0;
	//}}AFX_DATA_INIT
    m_lServerID = -1; // 用户ID
    m_iDevIndex = -1; // 设备索引
	m_lChannel  = -1;	
    m_nNetworkCardNo = 1;
    memset(&m_struWifiServerCfg, 0, sizeof(m_struWifiServerCfg));
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
}


void CDlgWIFIServerCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWIFIServerCfg)
	DDX_Control(pDX, IDC_COMBO_WEPKEY_TYPE, m_comKeyType);
	DDX_Control(pDX, IDC_COMBO_ALGORITHM_TYPE, m_comAlgorithmType);
	DDX_Control(pDX, IDC_COMBO_WEPKEYLEN_TYPE, m_comWepKeyLenType);
	DDX_Control(pDX, IDC_COMBO_TRANSMITKEY_INDEX, m_comDefaultTransmitKeyIndex);
	DDX_Control(pDX, IDC_COMBO_SECURITY_MODE, m_comSecurityMode);
	DDX_Control(pDX, IDC_COMBO_AUTHENTICATION_TYPE, m_comAuthenticationType);
	DDX_Control(pDX, IDC_COMBO_IPTYPE, m_comboIPType);
	DDX_Check(pDX, IDC_CHK_WIFI_AP_ENABLE, m_bChkWifiAP);
	DDX_Check(pDX, IDC_CHK_BROADCAST_ENABLE, m_bChkBroadcast);
	DDX_Check(pDX, IDC_CHK_DHCP_ENABLE, m_bChkDHCP);
	DDX_Check(pDX, IDC_CHK_WLAN_SHARE_ENABLE, m_bChkWlanShare);
	DDX_Text(pDX, IDC_EDIT_DNS1, m_csDNS1);
	DDX_Text(pDX, IDC_EDIT_DNS2, m_csDNS2);
	DDX_Text(pDX, IDC_EDIT_SSID, m_csSSID);
	DDX_Text(pDX, IDC_EDIT_END_IPADDRESS, m_csEndIP);
	DDX_Text(pDX, IDC_EDIT_GATEWAY, m_csGateway);
	DDX_Text(pDX, IDC_EDIT_IPADDRESS, m_csIP);
	DDX_Text(pDX, IDC_EDIT_IPMASK, m_csIPMask);
	DDX_Text(pDX, IDC_EDIT_START_IPADDRESS, m_csStartIP);
	DDX_Text(pDX, IDC_EDIT_WEP_ENCRYPTION_KEY1, m_csEncryptionKey1);
	DDX_Text(pDX, IDC_EDIT_WEP_ENCRYPTION_KEY2, m_csEncryptionKey2);
	DDX_Text(pDX, IDC_EDIT_WEP_ENCRYPTION_KEY3, m_csEncryptionKey3);
	DDX_Text(pDX, IDC_EDIT_WEP_ENCRYPTION_KEY4, m_csEncryptionKey4);
	DDX_Text(pDX, IDC_EDIT_WPA_SHARED_KEY, m_csSharedKey);
	DDX_Check(pDX, IDC_CHECK_DEFAULT_PASSWORD, m_bCHKDefaultPass);
	DDX_Text(pDX, IDC_EDIT_WPA_KEY_LEN, m_byWPAKeyLen);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWIFIServerCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgWIFIServerCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_CBN_SELCHANGE(IDC_COMBO_SECURITY_MODE, OnSelchangeComboSecurityMode)
	ON_CBN_SELCHANGE(IDC_COMBO_TRANSMITKEY_INDEX, OnSelchangeComboTransmitkeyIndex)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWIFIServerCfg message handlers
BOOL CDlgWIFIServerCfg::ValidIPv6(BYTE *ip)
{
    if (strlen((char *)ip) >= 2 && strchr((char *)ip, ':') != NULL)
    {
        return TRUE;
    }
    return FALSE;
}

void CDlgWIFIServerCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    DWORD dwReturned = 0;
	char szLan[128] = {0};

    if (m_lServerID < 0)
    {
        return;
    }

    NET_DVR_STD_CONFIG struCfg = {0};
    memset(&m_struWifiServerCfg, 0, sizeof(m_struWifiServerCfg));
    struCfg.lpCondBuffer = &m_nNetworkCardNo;
    struCfg.dwCondSize = sizeof(m_nNetworkCardNo);
    struCfg.lpOutBuffer = &m_struWifiServerCfg;
    struCfg.dwOutSize = sizeof(m_struWifiServerCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_WIRELESSSERVER_FULLVERSION_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_WIRELESSSERVER_FULLVERSION_CFG");
        g_StringLanType(szLan, "获取WIFI热点参数失败", "Get WIFI Server Configure failed");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_WIRELESSSERVER_FULLVERSION_CFG");
	}
    m_bChkWifiAP = m_struWifiServerCfg.byWifiAPEnabled;
    m_bChkBroadcast = m_struWifiServerCfg.byBroadcastEnabled;
    m_bChkWlanShare = m_struWifiServerCfg.byWlanShareEnabled;
    m_bChkDHCP = m_struWifiServerCfg.byDHCPEnabled;
    m_comboIPType.SetCurSel(m_struWifiServerCfg.byIPType);
    m_csSSID.Format("%s", m_struWifiServerCfg.bySSID);
    if (ValidIPv6(m_struWifiServerCfg.struIPAddr.byIPv6))
    {
        m_csIP.Format("%s", m_struWifiServerCfg.struIPAddr.byIPv6);
    }
    else
    {
        m_csIP.Format("%s", m_struWifiServerCfg.struIPAddr.sIpV4);
	}

    if (ValidIPv6(m_struWifiServerCfg.struIPMask.byIPv6))
    {
        m_csIPMask.Format("%s", m_struWifiServerCfg.struIPMask.byIPv6);
    }
    else
    {
        m_csIPMask.Format("%s", m_struWifiServerCfg.struIPMask.sIpV4);
	}

    if (ValidIPv6(m_struWifiServerCfg.struStartIPAddrPool.byIPv6))
    {
        m_csStartIP.Format("%s", m_struWifiServerCfg.struStartIPAddrPool.byIPv6);
    }
    else
    {
        m_csStartIP.Format("%s", m_struWifiServerCfg.struStartIPAddrPool.sIpV4);
	}

    if (ValidIPv6(m_struWifiServerCfg.struEndIPAddrPool.byIPv6))
    {
        m_csEndIP.Format("%s", m_struWifiServerCfg.struEndIPAddrPool.byIPv6);
    }
    else
    {
        m_csEndIP.Format("%s", m_struWifiServerCfg.struEndIPAddrPool.sIpV4);
	}
    
    if (ValidIPv6(m_struWifiServerCfg.struGatewayIPMask.byIPv6))
    {
        m_csGateway.Format("%s", m_struWifiServerCfg.struGatewayIPMask.byIPv6);
    }
    else
    {
        m_csGateway.Format("%s", m_struWifiServerCfg.struGatewayIPMask.sIpV4);
	}

    if (ValidIPv6(m_struWifiServerCfg.struDNSServerIpAddr[0].byIPv6))
    {
        m_csDNS1.Format("%s", m_struWifiServerCfg.struDNSServerIpAddr[0].byIPv6);
    }
    else
    {
        m_csDNS1.Format("%s", m_struWifiServerCfg.struDNSServerIpAddr[0].sIpV4);
	}

    if (ValidIPv6(m_struWifiServerCfg.struDNSServerIpAddr[1].byIPv6))
    {
        m_csDNS2.Format("%s", m_struWifiServerCfg.struDNSServerIpAddr[1].byIPv6);
    }
    else
    {
        m_csDNS2.Format("%s", m_struWifiServerCfg.struDNSServerIpAddr[1].sIpV4);
	}

	m_comSecurityMode.SetCurSel(m_struWifiServerCfg.struWirelessSecurityCfg.bySecurityMode);
	m_comAuthenticationType.SetCurSel(m_struWifiServerCfg.struWirelessSecurityCfg.struWEPCfg.byAuthenticationType);
	m_comDefaultTransmitKeyIndex.SetCurSel(m_struWifiServerCfg.struWirelessSecurityCfg.struWEPCfg.byDefaultTransmitKeyIndex - 1);
    m_comWepKeyLenType.SetCurSel(m_struWifiServerCfg.struWirelessSecurityCfg.struWEPCfg.byWepKeyLenType);
	m_comKeyType.SetCurSel(m_struWifiServerCfg.struWirelessSecurityCfg.struWEPCfg.byKeyType);
    m_csEncryptionKey1.Format(_T("%s"), m_struWifiServerCfg.struWirelessSecurityCfg.struWEPCfg.struWEPKeyCfg[0].csWEPKey);
	m_csEncryptionKey2.Format(_T("%s"), m_struWifiServerCfg.struWirelessSecurityCfg.struWEPCfg.struWEPKeyCfg[1].csWEPKey);
	m_csEncryptionKey3.Format(_T("%s"), m_struWifiServerCfg.struWirelessSecurityCfg.struWEPCfg.struWEPKeyCfg[2].csWEPKey);
	m_csEncryptionKey4.Format(_T("%s"), m_struWifiServerCfg.struWirelessSecurityCfg.struWEPCfg.struWEPKeyCfg[3].csWEPKey);

	m_comAlgorithmType.SetCurSel(m_struWifiServerCfg.struWirelessSecurityCfg.struWPACfg.byAlgorithmType);
	m_byWPAKeyLen = m_struWifiServerCfg.struWirelessSecurityCfg.struWPACfg.byWPAKeyLen;
	m_bCHKDefaultPass = m_struWifiServerCfg.struWirelessSecurityCfg.struWPACfg.byDefaultPassword;
	m_csSharedKey.Format(_T("%s"), m_struWifiServerCfg.struWirelessSecurityCfg.struWPACfg.csSharedKey);

	UpdateData(FALSE);
	OnSelchangeComboSecurityMode();
//	OnSelchangeComboTransmitkeyIndex();
}

void CDlgWIFIServerCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	memset(&m_struWifiServerCfg, 0, sizeof(m_struWifiServerCfg));
    m_struWifiServerCfg.dwSize = sizeof(m_struWifiServerCfg);
    m_struWifiServerCfg.byWifiAPEnabled = m_bChkWifiAP;
    m_struWifiServerCfg.byBroadcastEnabled = m_bChkBroadcast;
    m_struWifiServerCfg.byWlanShareEnabled = m_bChkWlanShare;
    m_struWifiServerCfg.byDHCPEnabled = m_bChkDHCP;
    m_struWifiServerCfg.byIPType = 0/*m_comboIPType.GetCurSel()*/;
    strncpy((char *)m_struWifiServerCfg.bySSID, m_csSSID, 32);

    if (m_csIP.Find(':') != -1)
    {
        strncpy((char *)m_struWifiServerCfg.struIPAddr.byIPv6, m_csIP, 128);
    }
    else
    {
        strncpy(m_struWifiServerCfg.struIPAddr.sIpV4, m_csIP, 16);
	}

    if (m_csIPMask.Find(':') != -1)
    {
        strncpy((char *)m_struWifiServerCfg.struIPMask.byIPv6, m_csIPMask, 128);
    }
    else
    {
        strncpy(m_struWifiServerCfg.struIPMask.sIpV4, m_csIPMask, 16);
	}

    if (m_csStartIP.Find(':') != -1)
    {
        strncpy((char *)m_struWifiServerCfg.struStartIPAddrPool.byIPv6, m_csStartIP, 128);
    }
    else
    {
        strncpy(m_struWifiServerCfg.struStartIPAddrPool.sIpV4, m_csStartIP, 16);
	}

    if (m_csEndIP.Find(':') != -1)
    {
        strncpy((char *)m_struWifiServerCfg.struEndIPAddrPool.byIPv6, m_csEndIP, 128);
    }
    else
    {
        strncpy(m_struWifiServerCfg.struEndIPAddrPool.sIpV4, m_csEndIP, 16);
	}

    if (m_csGateway.Find(':') != -1)
    {
        strncpy((char *)m_struWifiServerCfg.struGatewayIPMask.byIPv6, m_csGateway, 128);
    }
    else
    {
        strncpy(m_struWifiServerCfg.struGatewayIPMask.sIpV4, m_csGateway, 16);
	}
    
    if (m_csDNS1.Find(':') != -1)
    {
        strncpy((char *)m_struWifiServerCfg.struDNSServerIpAddr[0].byIPv6, m_csDNS1, 128);
    }
    else
    {
        strncpy(m_struWifiServerCfg.struDNSServerIpAddr[0].sIpV4, m_csDNS1, 16);
	}

    if (m_csDNS2.Find(':') != -1)
    {
        strncpy((char *)m_struWifiServerCfg.struDNSServerIpAddr[1].byIPv6, m_csDNS2, 128);
    }
    else
    {
        strncpy(m_struWifiServerCfg.struDNSServerIpAddr[1].sIpV4, m_csDNS2, 16);
	}

	m_struWifiServerCfg.struWirelessSecurityCfg.bySecurityMode = m_comSecurityMode.GetCurSel();
	m_struWifiServerCfg.struWirelessSecurityCfg.struWEPCfg.byAuthenticationType = m_comAuthenticationType.GetCurSel();
	m_struWifiServerCfg.struWirelessSecurityCfg.struWEPCfg.byDefaultTransmitKeyIndex = m_comDefaultTransmitKeyIndex.GetCurSel() + 1;
    m_struWifiServerCfg.struWirelessSecurityCfg.struWEPCfg.byWepKeyLenType = m_comWepKeyLenType.GetCurSel();
	m_struWifiServerCfg.struWirelessSecurityCfg.struWEPCfg.byKeyType = m_comKeyType.GetCurSel();
	strncpy((char *)m_struWifiServerCfg.struWirelessSecurityCfg.struWEPCfg.struWEPKeyCfg[0].csWEPKey, m_csEncryptionKey1, WEP_KEY_MAX_SIZE);
	strncpy((char *)m_struWifiServerCfg.struWirelessSecurityCfg.struWEPCfg.struWEPKeyCfg[1].csWEPKey, m_csEncryptionKey2, WEP_KEY_MAX_SIZE);
	strncpy((char *)m_struWifiServerCfg.struWirelessSecurityCfg.struWEPCfg.struWEPKeyCfg[2].csWEPKey, m_csEncryptionKey3, WEP_KEY_MAX_SIZE);
	strncpy((char *)m_struWifiServerCfg.struWirelessSecurityCfg.struWEPCfg.struWEPKeyCfg[3].csWEPKey, m_csEncryptionKey4, WEP_KEY_MAX_SIZE);

	m_struWifiServerCfg.struWirelessSecurityCfg.struWPACfg.byAlgorithmType = m_comAlgorithmType.GetCurSel();
	m_struWifiServerCfg.struWirelessSecurityCfg.struWPACfg.byWPAKeyLen = m_byWPAKeyLen;
	m_struWifiServerCfg.struWirelessSecurityCfg.struWPACfg.byDefaultPassword = m_bCHKDefaultPass;
	strncpy((char *)m_struWifiServerCfg.struWirelessSecurityCfg.struWPACfg.csSharedKey, m_csSharedKey, WPA_KEY_MAX_SIZE);


    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_nNetworkCardNo;
    struCfg.dwCondSize = sizeof(m_nNetworkCardNo);
    struCfg.lpInBuffer = &m_struWifiServerCfg;
    struCfg.dwInSize = sizeof(m_struWifiServerCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_WIRELESSSERVER_FULLVERSION_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_WIRELESSSERVER_FULLVERSION_CFG");
        g_StringLanType(szLan, "设置WIFI热点参数失败", "Set WIFI Server Configure failed");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_WIRELESSSERVER_FULLVERSION_CFG");
	}

}


void CDlgWIFIServerCfg::OnSelchangeComboSecurityMode() 
{
	// TODO: Add your control notification handler code here
	if (0 == m_comSecurityMode.GetCurSel())
	{
		GetDlgItem(IDC_COMBO_AUTHENTICATION_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_TRANSMITKEY_INDEX)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_WEPKEYLEN_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_WEPKEY_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY4)->EnableWindow(FALSE);

		GetDlgItem(IDC_COMBO_ALGORITHM_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_WPA_KEY_LEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_DEFAULT_PASSWORD)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_WPA_SHARED_KEY)->EnableWindow(FALSE);
	} 
	else if (1 == m_comSecurityMode.GetCurSel())
	{
		GetDlgItem(IDC_COMBO_AUTHENTICATION_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_TRANSMITKEY_INDEX)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_WEPKEYLEN_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_WEPKEY_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY2)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY3)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY4)->EnableWindow(TRUE);
		
		GetDlgItem(IDC_COMBO_ALGORITHM_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_WPA_KEY_LEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_DEFAULT_PASSWORD)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_WPA_SHARED_KEY)->EnableWindow(FALSE);

// 		m_comDefaultTransmitKeyIndex.SetCurSel(0);
// 	    OnSelchangeComboTransmitkeyIndex();

	}
	else if (2 == m_comSecurityMode.GetCurSel() || 3 == m_comSecurityMode.GetCurSel())
	{
		GetDlgItem(IDC_COMBO_AUTHENTICATION_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_TRANSMITKEY_INDEX)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_WEPKEYLEN_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_WEPKEY_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY4)->EnableWindow(FALSE);
		
		GetDlgItem(IDC_COMBO_ALGORITHM_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_WPA_KEY_LEN)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_DEFAULT_PASSWORD)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_WPA_SHARED_KEY)->EnableWindow(TRUE);
	}
}

BOOL CDlgWIFIServerCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_comSecurityMode.SetCurSel(0);
	OnSelchangeComboSecurityMode();

	m_comAuthenticationType.SetCurSel(0);
	m_comDefaultTransmitKeyIndex.SetCurSel(0);
//	OnSelchangeComboTransmitkeyIndex();
	m_comWepKeyLenType.SetCurSel(0);
	m_comKeyType.SetCurSel(0);

	m_comAlgorithmType.SetCurSel(0);


	OnBtnGet() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgWIFIServerCfg::OnSelchangeComboTransmitkeyIndex() 
{
	// TODO: Add your control notification handler code here
// 	if (0 == m_comDefaultTransmitKeyIndex.GetCurSel() && 1 == m_comSecurityMode.GetCurSel())
// 	{
// 		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY1)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY2)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY3)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY4)->EnableWindow(FALSE);
// 	}
// 	else if (1 == m_comDefaultTransmitKeyIndex.GetCurSel() && 1 == m_comSecurityMode.GetCurSel())
// 	{
// 		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY1)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY2)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY3)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY4)->EnableWindow(FALSE);
// 	}
// 	else if (2 == m_comDefaultTransmitKeyIndex.GetCurSel() && 1 == m_comSecurityMode.GetCurSel())
// 	{
// 		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY1)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY2)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY3)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY4)->EnableWindow(FALSE);
// 	}
// 	else if (3 == m_comDefaultTransmitKeyIndex.GetCurSel() && 1 == m_comSecurityMode.GetCurSel())
// 	{
// 		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY1)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY2)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY3)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY4)->EnableWindow(TRUE);
// 	}
// 	else
// 	{
// 		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY1)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY2)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY3)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_EDIT_WEP_ENCRYPTION_KEY4)->EnableWindow(FALSE);
// 	}
}
