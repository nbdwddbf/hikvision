// DlgAlarmHostGPRS.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmHostGPRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostGPRS dialog


CDlgAlarmHostGPRS::CDlgAlarmHostGPRS(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmHostGPRS::IDD, pParent)
	, m_iDeviceIndex(-1)
	, m_lUserID(-1)
	, m_nSignalQuality(0)
	, m_strDialStatus(_T(""))
	, m_strIPAddr(_T(""))
	, m_strIPMask(_T(""))
	, m_strGatewayAddr(_T(""))
	, m_strDNSAddr(_T(""))
	, m_nNetworkCardNo(0)
{
	//{{AFX_DATA_INIT(CDlgAlarmHostGPRS)
	m_csAPNPassword = _T("");
	m_csAPNUserName = _T("");
	m_csAPNName = _T("");
	m_byDetectLinkTime = 0;
	m_csDevID = _T("");
	m_byOverTime = 0;
	m_iPort = 0;
	m_byReconnectTime = 0;
	m_csSIMNum = _T("");
	m_csDomain = _T("");
	//}}AFX_DATA_INIT
	memset(&m_struGPRSCfg, 0, sizeof(NET_DVR_ALARMHOST_WIRELESS_NETWORK_CFG));
}


void CDlgAlarmHostGPRS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmHostGPRS)
	DDX_Control(pDX, IDC_CMB_ADDR_TYPE, m_cmbAddrType);
	DDX_Control(pDX, IDC_IPADDRESS_SIMIP, m_ipSIM);
	DDX_Control(pDX, IDC_IPADDRESS_IPV4, m_ipCenter);
	DDX_Control(pDX, IDC_COMBO_PROTOCOLTYPE, m_cmProtocolType);
	DDX_Control(pDX, IDC_COMBO_CENTER, m_cmCenter);
	DDX_Text(pDX, IDC_EDIT_APN_PASSWORD, m_csAPNPassword);
	DDX_Text(pDX, IDC_EDIT_APN_USERNAME, m_csAPNUserName);
	DDX_Text(pDX, IDC_EDIT_APNNAME, m_csAPNName);
	DDX_Text(pDX, IDC_EDIT_DETECTLINKTIME, m_byDetectLinkTime);
	DDX_Text(pDX, IDC_EDIT_DEVICEID, m_csDevID);
	DDX_Text(pDX, IDC_EDIT_OVERTIME, m_byOverTime);
	DDX_Text(pDX, IDC_EDIT_PORT, m_iPort);
	DDV_MinMaxInt(pDX, m_iPort, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_RECONNECTTIME, m_byReconnectTime);
	DDX_Text(pDX, IDC_EDIT_SIMNUM, m_csSIMNum);
	DDX_Text(pDX, IDC_EDIT_DOMAIN, m_csDomain);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_CMB_UIM_STATUS, m_cmbUIMStatus);
	DDX_Control(pDX, IDC_CMB_REALTIME_MODE, m_cmbRealtimeMode);
	DDX_Text(pDX, IDC_EDIT_SIGNAL_QUALITY, m_nSignalQuality);
	DDX_Text(pDX, IDC_EDIT_DIAL_STATUS, m_strDialStatus);
	DDX_Text(pDX, IDC_EDIT_IP_ADDR2, m_strIPAddr);
	DDX_Text(pDX, IDC_EDIT_IP_MASK, m_strIPMask);
	DDX_Text(pDX, IDC_EDIT_GATEWAY, m_strGatewayAddr);
	DDX_Text(pDX, IDC_EDIT_DNS_ADDR, m_strDNSAddr);
	DDX_CBIndex(pDX, IDC_CMB_CARD_SEL, m_nNetworkCardNo);
}


BEGIN_MESSAGE_MAP(CDlgAlarmHostGPRS, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmHostGPRS)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_CBN_SELCHANGE(IDC_COMBO_CENTER, OnSelchangeComboCenter)
	ON_CBN_SELCHANGE(IDC_COMBO_PROTOCOLTYPE, OnSelchangeComboProtocoltype)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_SURE, OnBtnSure)
	ON_CBN_SELCHANGE(IDC_CMB_ADDR_TYPE, OnSelchangeCmbAddrType)
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_CMB_UIM_STATUS, &CDlgAlarmHostGPRS::OnCbnSelchangeCmbUimStatus)
	ON_BN_CLICKED(IDC_BTN_STATUS_REFRESH, &CDlgAlarmHostGPRS::OnBnClickedBtnStatusRefresh)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostGPRS message handlers

BOOL CDlgAlarmHostGPRS::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char szLan[128] = {0};
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	//GetDlgItem(IDC_IPADDRESS_SIMIP)->EnableWindow(FALSE);
	m_struAbility.dwSize = sizeof(m_struAbility);
	if (!NET_DVR_GetDeviceAbility(m_lUserID, ALARMHOST_ABILITY, NULL, 0, (char*)&m_struAbility, sizeof(m_struAbility)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetDeviceAbility FAILED");
        CString csStr;
        int i = 0;
        for (i=0; i<1; i++)
        {
            g_StringLanType(szLan, "GPRS中心", "GPRS Center");
            csStr.Format("%s %d", szLan, i+1);
            m_cmCenter.AddString(csStr);
			}
	}
	else
	{
		CString csStr;
		int i = 0;
		if (m_struAbility.by3GNum > 0)
		{
			for (i=0; i<m_struAbility.by3GNum; i++)
			{
				g_StringLanType(szLan, "3G中心", "3G Center");
				csStr.Format("%s %d",szLan, i+1);
				m_cmCenter.AddString(csStr);
			}
			GetDlgItem(IDC_EDIT_APNNAME)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_APN_USERNAME)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_APN_PASSWORD)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_APNNAME)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_DETECTLINKTIME)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_OVERTIME)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_RECONNECTTIME)->EnableWindow(FALSE);
		}
		else if (m_struAbility.byGPRSNum > 0)
		{
			for (i=0; i<m_struAbility.byGPRSNum; i++)
			{
				g_StringLanType(szLan, "GPRS中心", "GPRS Center");
				csStr.Format("%s %d", szLan, i+1);
				m_cmCenter.AddString(csStr);
			}
		}
	}
	OnBtnGet();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlarmHostGPRS::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
	char szLan[1024] = {0};
	m_struGPRSCfg.dwSize = sizeof(NET_DVR_ALARMHOST_WIRELESS_NETWORK_CFG);
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_ALARMHOST_WIRELESS_NETWORK_CFG, 0, &m_struGPRSCfg, sizeof(m_struGPRSCfg), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Get GPRS/3G Param FAILED");
		g_StringLanType(szLan, "获取失败", "Get wireless network Param FAILED");
		MessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Get wireless network Param SUCC");
		m_cmCenter.SetCurSel(0);
		UpdateData(FALSE);
		SetGPRSParaToDlg(&m_struGPRSCfg);
	}
}

void CDlgAlarmHostGPRS::SetGPRSParaToDlg(LPNET_DVR_ALARMHOST_WIRELESS_NETWORK_CFG lpInter)
{
	UpdateData(TRUE);
	OnSelchangeComboCenter();
	m_csAPNName.Format("%s", lpInter->byAPNName);
	m_csAPNUserName.Format("%s", lpInter->byAPNUserName);
	m_csAPNPassword.Format("%s", lpInter->byAPNPassWord);
	m_byReconnectTime = lpInter->byReconnTime;
	m_byOverTime = lpInter->byOverTime;
	m_byDetectLinkTime = lpInter->byDetectLinkTime;
	m_csSIMNum.Format("%s", lpInter->bySIMNum);
	DWORD dwIP = ntohl(inet_addr(lpInter->struSIMIP.sIpV4));
	m_ipSIM.SetAddress(dwIP);
	UpdateData(FALSE);
}

void CDlgAlarmHostGPRS::OnSelchangeComboCenter() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_ALARMHOST_NETPARAM struNetParam = {0};

	memcpy(&struNetParam, &m_struGPRSCfg.struNetCenter[m_cmCenter.GetCurSel()], sizeof(struNetParam));
	DWORD dwIP = ntohl(inet_addr(struNetParam.struIP.sIpV4));
	m_ipCenter.SetAddress(dwIP);
	m_iPort = struNetParam.wPort;
	m_cmProtocolType.SetCurSel(struNetParam.byReportProtocol - 1);
	m_csDomain.Format("%s", struNetParam.byDomainName);
	m_cmbAddrType.SetCurSel(struNetParam.byAddressType);
	UpdateData(FALSE);
	OnSelchangeComboProtocoltype();
	OnSelchangeCmbAddrType();
}

void CDlgAlarmHostGPRS::OnSelchangeComboProtocoltype() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwCenterIndex = m_cmCenter.GetCurSel();
	m_csDevID.Format("%s", m_struGPRSCfg.struNetCenter[dwCenterIndex].byDevID);
	UpdateData(FALSE);
}

void CDlgAlarmHostGPRS::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	GetGPRSParaFromDlg();
	m_struGPRSCfg.dwSize = sizeof(m_struGPRSCfg);
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_ALARMHOST_WIRELESS_NETWORK_CFG, 0, &m_struGPRSCfg, sizeof(m_struGPRSCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Set GPRS/3G Param FAILED");
		g_StringLanType(szLan, "设置无线网络参数失败", "Set wireless network Param FAILED");
		MessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Set wireless network Param SUCC");
	}
}

void CDlgAlarmHostGPRS::GetGPRSParaFromDlg()
{
	UpdateData(TRUE);
	OnBtnSure();
	memcpy(m_struGPRSCfg.byAPNName, m_csAPNName, APN_NAME_LEN);
	memcpy(m_struGPRSCfg.byAPNUserName, m_csAPNUserName, APN_USERNAME_LEN);
	memcpy(m_struGPRSCfg.byAPNPassWord, m_csAPNPassword, APN_USERPASSWORD_LEN);
	m_struGPRSCfg.byReconnTime = m_byReconnectTime;
	m_struGPRSCfg.byOverTime = m_byOverTime;
	m_struGPRSCfg.byDetectLinkTime = m_byDetectLinkTime;
	DWORD dwIP = 0;
	m_ipSIM.GetAddress(dwIP);
	memcpy(m_struGPRSCfg.struSIMIP.sIpV4, IPToStr(dwIP), 16);
	memcpy(m_struGPRSCfg.bySIMNum, m_csSIMNum, NAME_LEN); //手机号的长度
}

void CDlgAlarmHostGPRS::OnBtnSure() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_ALARMHOST_NETPARAM struNetParam = {0};
	DWORD dwIP = 0;
	m_ipCenter.GetAddress(dwIP);
	memcpy(struNetParam.struIP.sIpV4, IPToStr(dwIP), 16);
	struNetParam.wPort = m_iPort;
	struNetParam.byReportProtocol = m_cmProtocolType.GetCurSel() + 1;
	memcpy(struNetParam.byDomainName, m_csDomain, MAX_DOMAIN_NAME);
	memcpy(struNetParam.byDevID, m_csDevID, m_csDevID.GetLength());
	struNetParam.byAddressType = m_cmbAddrType.GetCurSel();

	memcpy(&m_struGPRSCfg.struNetCenter[m_cmCenter.GetCurSel()], &struNetParam, sizeof(struNetParam));

	
}

void CDlgAlarmHostGPRS::OnSelchangeCmbAddrType() 
{
	// TODO: Add your control notification handler code here
	if (0 == m_cmbAddrType.GetCurSel() || 1 == m_cmbAddrType.GetCurSel())
	{
		GetDlgItem(IDC_IPADDRESS_IPV4)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DOMAIN)->EnableWindow(FALSE);	
	} 
	else
	{
		GetDlgItem(IDC_IPADDRESS_IPV4)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DOMAIN)->EnableWindow(TRUE);
	}
}


void CDlgAlarmHostGPRS::OnCbnSelchangeCmbUimStatus()
{
	// TODO: Add your control notification handler code here
}

void CDlgAlarmHostGPRS::SetItemData(CComboBox &combo, char* szData)
{
	CString strTmp;
	for (int i = 0; i < combo.GetCount(); i++)
	{
		combo.GetLBText(i, strTmp);
		if (strTmp.Compare(szData) == 0)
		{
			combo.SetCurSel(i);
			break;
		}
	}
}

void CDlgAlarmHostGPRS::OnBnClickedBtnStatusRefresh()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_STD_CONFIG struCfg = { 0 };
	m_nNetworkCardNo += 1;
	struCfg.lpCondBuffer = &m_nNetworkCardNo;
	struCfg.dwCondSize = sizeof(m_nNetworkCardNo);
	struCfg.lpOutBuffer = &m_struWirelessDialStatus;
	struCfg.dwOutSize = sizeof(m_struWirelessDialStatus);
	memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
	struCfg.lpStatusBuffer = m_szStatusBuf;
	struCfg.dwStatusSize = ISAPI_STATUS_LEN;

	if (!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_WIRELESSDIAL_STATUS, &struCfg))
	{
		OutputDebugString(m_szStatusBuf);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_WIRELESSDIAL_STATUS");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_WIRELESSDIAL_STATUS");
		SetItemData(m_cmbRealtimeMode, (char*)m_struWirelessDialStatus.byRealtimeMode);
		SetItemData(m_cmbUIMStatus, (char*)m_struWirelessDialStatus.byUIMStatus);
		m_nSignalQuality = m_struWirelessDialStatus.dwSignalQuality;
		m_strDialStatus = m_struWirelessDialStatus.byDialStatus;
		if (ValidIPv6(m_struWirelessDialStatus.struIpAddr.byIPv6))
		{
			m_strIPAddr.Format("%s", m_struWirelessDialStatus.struIpAddr.byIPv6);
		}
		else
		{
			m_strIPAddr.Format("%s", m_struWirelessDialStatus.struIpAddr.sIpV4);
		}
		if (ValidIPv6(m_struWirelessDialStatus.struIPMask.byIPv6))
		{
			m_strIPMask.Format("%s", m_struWirelessDialStatus.struIPMask.byIPv6);
		}
		else
		{
			m_strIPMask.Format("%s", m_struWirelessDialStatus.struIPMask.sIpV4);
		}
		if (ValidIPv6(m_struWirelessDialStatus.struGatewayIPMask.byIPv6))
		{
			m_strGatewayAddr.Format("%s", m_struWirelessDialStatus.struGatewayIPMask.byIPv6);
		}
		else
		{
			m_strGatewayAddr.Format("%s", m_struWirelessDialStatus.struGatewayIPMask.sIpV4);
		}
		if (ValidIPv6(m_struWirelessDialStatus.struDnsServerIpAddr.byIPv6))
		{
			m_strDNSAddr.Format("%s", m_struWirelessDialStatus.struDnsServerIpAddr.byIPv6);
		}
		else
		{
			m_strDNSAddr.Format("%s", m_struWirelessDialStatus.struDnsServerIpAddr.sIpV4);
		}
	}
	UpdateData(FALSE);
}

BOOL CDlgAlarmHostGPRS::ValidIPv6(BYTE *ip)
{
	if (strlen((char *)ip) >= 2 && strchr((char *)ip, ':') != NULL)
	{
		return TRUE;
	}
	return FALSE;
}