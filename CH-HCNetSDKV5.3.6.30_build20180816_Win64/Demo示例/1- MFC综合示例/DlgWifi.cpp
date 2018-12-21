// DlgWifi.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgWifi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWifi dialog


CDlgWifi::CDlgWifi(CWnd* pParent /*=NULL*/)
: CDialog(CDlgWifi::IDD, pParent)
, m_iDeviceIndex(-1)
{
	//{{AFX_DATA_INIT(CDlgWifi)
	m_Active1 = FALSE;
	m_csPassword = _T("");
	m_csPrivateKeyPwd = _T("");
	m_csUserName = _T("");
	m_csUploadState = _T("");
	m_csAnonyIdentity = _T("");
	m_csIdentity = _T("");
	m_uApNum = 0;
	m_bAutoDns = FALSE;
	m_strDns1 = _T("");
	m_strDns2 = _T("");
	m_strEncKey = _T("");
	m_strGatewayAddr = _T("");
	m_strHideCode = _T("");
	m_strHostAddr = _T("");
	m_strIpAddress = _T("");
	m_uKeyLen = 0;
	m_strKey1 = _T("");
	m_strKey2 = _T("");
	m_strKey3 = _T("");
	m_strKey4 = _T("");
	m_strSsid = _T("");
	m_bStartDhcp = FALSE;
    m_byCloseWifi = FALSE;
	m_csCertPath = _T("");
	//}}AFX_DATA_INIT
	memset(&m_WifiWorkMode,0,sizeof(NET_DVR_WIFI_WORKMODE));
	memset(&m_ApInfo,0,sizeof(NET_DVR_AP_INFO_LIST));
	memset(&m_WifiCfg,0,sizeof(NET_DVR_WIFI_CFG));
	memset(&m_struWifiStatus, 0, sizeof(NET_DVR_WIFI_CONNECT_STATUS));
}


void CDlgWifi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWifi)
	DDX_Control(pDX, IDC_CMB_UNCONNECTED_ERROR_CODE, m_cmbErrorCode);
	DDX_Control(pDX, IDC_CMB_CONNECT_STATUS, m_cmbConnectStatus);
	DDX_Control(pDX, IDC_COMBO_PEAP_VERSION, m_comboPeapVer);
	DDX_Control(pDX, IDC_COMBO_PEAP_INTER_AUTH_TYPE, m_comboPeapInterAuth);
	DDX_Control(pDX, IDC_COMBO_PEAP_LABEL, m_comboPeapLabel);
	DDX_Control(pDX, IDC_COMBO_AUTH_TYPE, m_comboAuthType);
	DDX_Control(pDX, IDC_COMBO_CERT_TYPE, m_comboCertType);
	DDX_Control(pDX, IDC_COMBO_FILE_TYPE, m_comboFileType);
	DDX_Control(pDX, IDC_COMBO_INTER_AUTH_TYPE, m_comboInterAuthType);
	DDX_Control(pDX, IDC_COMBO_EAPOL_VERSION, m_comboEapolVer);
	DDX_Control(pDX, IDC_COMBO_WPA_ENTER_ENCRY_TYPE, m_comboWPAEnterEncry);
	DDX_Control(pDX, IDC_COMBO_WPA_ENCTYPE, m_comboWpaEncType);
	DDX_Control(pDX, IDC_COMBO_ACTIVE_KEY, m_ActiveKey);
    DDX_Control(pDX, IDC_COMBO_KEY_TYPE, m_comboKeyType);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csPassword);
	DDX_Text(pDX, IDC_EDIT_PRIVATE_KEY_PWD, m_csPrivateKeyPwd);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_csUserName);
	DDX_Text(pDX, IDC_UPLOADSTATE, m_csUploadState);
	DDX_Text(pDX, IDC_EDIT_ANONY_IDENTITY, m_csAnonyIdentity);
	DDX_Text(pDX, IDC_EDIT_IDENTITY, m_csIdentity);
	DDX_Text(pDX, IDC_EDIT_CERT_PATH, m_csCertPath);
	DDX_Control(pDX, IDC_WORDMODE, m_WorkModeCtrl);
	DDX_Control(pDX, IDC_WIFI_LIST, m_WifiList);
	DDX_Control(pDX, IDC_KEYTYPE, m_KeyTypeCtrl);
	DDX_Control(pDX, IDC_KEYLENGTH, m_KeyLenCtrl);
	DDX_Control(pDX, IDC_ETHERNET_WORKMODE, m_EthernetWorkMode);
	DDX_Control(pDX, IDC_ENCRYPTTYPE, m_EncryptTypeCtrl);
	DDX_Control(pDX, IDC_AUTHENTICATION, m_AuthCtrl);
	DDX_Text(pDX, IDC_APNUMBER, m_uApNum);
	DDX_Check(pDX, IDC_AUTODNS, m_bAutoDns);
	DDX_Text(pDX, IDC_DNS1, m_strDns1);
	DDX_Text(pDX, IDC_DNS2, m_strDns2);
	DDX_Text(pDX, IDC_ENCKEY, m_strEncKey);
	DDX_Text(pDX, IDC_GATEWAYADDRESS, m_strGatewayAddr);
	DDX_Text(pDX, IDC_HIDECODE, m_strHideCode);
	DDX_Text(pDX, IDC_HOSTADDR, m_strHostAddr);
	DDX_Text(pDX, IDC_IPADDRESS, m_strIpAddress);
	DDX_Text(pDX, IDC_KEY_LENGTH, m_uKeyLen);
	DDX_Text(pDX, IDC_KEY1, m_strKey1);
	DDX_Text(pDX, IDC_KEY2, m_strKey2);
	DDX_Text(pDX, IDC_KEY3, m_strKey3);
	DDX_Text(pDX, IDC_KEY4, m_strKey4);
	DDX_Text(pDX, IDC_SSID, m_strSsid);
	DDX_Check(pDX, IDC_STARTDHCP, m_bStartDhcp);
    DDX_Check(pDX, IDC_CHECK_CLOSE_WIFI, m_byCloseWifi);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWifi, CDialog)
//{{AFX_MSG_MAP(CDlgWifi)
	ON_BN_CLICKED(IDC_BTN_SCAN_CERT, OnBtnScanCert)
	ON_BN_CLICKED(IDC_BTN_UPLOAD_CERT, OnBtnUploadCert)
	ON_WM_TIMER()
	ON_CBN_EDITCHANGE(IDC_COMBO_AUTH_TYPE, OnSelchangeComboAuthType)
	ON_BN_CLICKED(IDC_BTN_GET_CONNECT_STATUS, OnBtnGetConnectStatus)
	//}}AFX_MSG_MAP
ON_BN_CLICKED(IDC_REFURBISH, OnRefurbish)
ON_BN_CLICKED(IDC_SAVEWIFIPARAM, OnSavewifiparam)
ON_CBN_SELCHANGE(IDC_ENCRYPTTYPE, OnSelchangeEncrypttype)
ON_BN_CLICKED(IDC_STARTDHCP, OnStartdhcp)
ON_BN_CLICKED(IDC_AUTODNS, OnAutodns)
ON_NOTIFY(NM_DBLCLK, IDC_WIFI_LIST, OnDblclkWifiList)
ON_BN_CLICKED(IDC_EXIT, OnExit)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWifi message handlers
BOOL CDlgWifi::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_WorkModeCtrl.InsertString(0,"manage");
	m_WorkModeCtrl.InsertString(1,"ad-hoc");
	m_EthernetWorkMode.InsertString(0,"Auto Switch");
	m_EthernetWorkMode.InsertString(1,"Wire Mode");		
	
	m_WifiList.InsertColumn(0,"SSID", LVCFMT_LEFT, 150, -1);
	m_WifiList.InsertColumn(1,"Work Mode", LVCFMT_LEFT, 90, -1);
	m_WifiList.InsertColumn(2,"Safety Type", LVCFMT_LEFT, 90, -1);
	m_WifiList.InsertColumn(3,"Channel", LVCFMT_LEFT, 60, -1);
	m_WifiList.InsertColumn(4,"Signal Strength", LVCFMT_LEFT, 80, -1);
	m_WifiList.InsertColumn(5,"rate", LVCFMT_LEFT, 60, -1);
	
	m_EncryptTypeCtrl.InsertString(0,"None");
	m_EncryptTypeCtrl.InsertString(1,"wep");
	m_EncryptTypeCtrl.InsertString(2,"wpa-psk");
	m_EncryptTypeCtrl.InsertString(3,"wpa-Enterprise");
	m_EncryptTypeCtrl.InsertString(4,"wpa2-psk");
    m_EncryptTypeCtrl.InsertString(5,"wpa2-Enterprise");

	m_comboWpaEncType.InsertString(0,"AES");
	m_comboWpaEncType.InsertString(1,"TKIP");
	
	m_AuthCtrl.InsertString(0,"Open mode");
	m_AuthCtrl.InsertString(1,"Share mode");
	
	m_KeyLenCtrl.InsertString(0,"64");
	m_KeyLenCtrl.InsertString(1,"128");
	m_KeyLenCtrl.InsertString(2,"152");

    m_comboKeyType.SetCurSel(1);
	
	if (!GetParam())
	{
		AfxMessageBox("Device doesn't support this.");
		CDialog::OnOK();
		return FALSE;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgWifi::OnRefurbish() 
{
	m_WifiList.DeleteAllItems();
	DWORD dwReturned = 0;
	if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID,NET_DVR_GET_AP_INFO_LIST, 0,&m_ApInfo, sizeof(NET_DVR_AP_INFO_LIST), &dwReturned))	
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_AP_INFO_LIST");
		AfxMessageBox("NET_DVR_GET_AP_INFO_LIST Err!");
		GetDlgItem(IDC_BTN_SAVE)->EnableWindow(FALSE);
	}
	else
	{
		if (m_ApInfo.dwCount > WIFI_MAX_AP_COUNT)
		{
			m_ApInfo.dwCount = WIFI_MAX_AP_COUNT;
		}
		else
		{
			m_uApNum = m_ApInfo.dwCount;
			DWORD dwApNum = 0;
			CString strTemp;
			while (dwApNum < m_ApInfo.dwCount)
			{							
				m_WifiList.InsertItem(dwApNum, m_ApInfo.struApInfo[dwApNum].sSsid, 0);
				switch(m_ApInfo.struApInfo[dwApNum].dwMode) 
				{
				case 0:
					m_WifiList.SetItemText(dwApNum, 1, "manage");
					break;
				case 1:
					m_WifiList.SetItemText(dwApNum, 1, "ad-hoc");
					break;
				default:
					m_WifiList.SetItemText(dwApNum, 1, "");
				}
				switch(m_ApInfo.struApInfo[dwApNum].dwSecurity)
				{
				case 0:
					m_WifiList.SetItemText(dwApNum, 2, "None");
					break;
				case 1:
					m_WifiList.SetItemText(dwApNum, 2, "wep");
					break;
				case 2:
					m_WifiList.SetItemText(dwApNum, 2, "wpa-psk");
					break;
				case 3:
					m_WifiList.SetItemText(dwApNum, 2, "wpa-Enterprise");
					break;
				case 4:
					m_WifiList.SetItemText(dwApNum, 2, "wpa2-psk");
					break;
				case 5:
					m_WifiList.SetItemText(dwApNum, 2, "wpa2-Enterprise");
					break;
				default:
					m_WifiList.SetItemText(dwApNum, 2, "None");
				}
				
				strTemp.Format("%d",m_ApInfo.struApInfo[dwApNum].dwChannel);
				m_WifiList.SetItemText(dwApNum, 3, strTemp);
				strTemp.Format("%d",m_ApInfo.struApInfo[dwApNum].dwSignalStrength);
				m_WifiList.SetItemText(dwApNum, 4, strTemp);
				strTemp.Format("%d",m_ApInfo.struApInfo[dwApNum].dwSpeed);
				m_WifiList.SetItemText(dwApNum, 5, strTemp);
				
				dwApNum++;
			}
		}
	}
	UpdateData(FALSE);
}

void CDlgWifi::OnSavewifiparam() 
{
	UpdateData(TRUE);
	m_WifiWorkMode.dwSize = sizeof(m_WifiWorkMode);
	m_WifiWorkMode.dwNetworkInterfaceMode = m_EthernetWorkMode.GetCurSel();
	
	m_WifiCfg.dwSize = sizeof(m_WifiCfg);
	m_WifiCfg.struWifiCfg.dwMode = m_WorkModeCtrl.GetCurSel();
	m_WifiCfg.struWifiCfg.dwSecurity = m_EncryptTypeCtrl.GetCurSel();
	memcpy(m_WifiCfg.struWifiCfg.sEssid, m_strSsid, IW_ESSID_MAX_SIZE);
	m_WifiCfg.struWifiCfg.struEtherNet.dwAutoDns = m_bAutoDns;
	m_WifiCfg.struWifiCfg.struEtherNet.dwEnableDhcp = m_bStartDhcp;
    m_WifiCfg.struWifiCfg.struEtherNet.byCloseWifi = m_byCloseWifi;
	
	memcpy(m_WifiCfg.struWifiCfg.struEtherNet.sIpAddress, m_strIpAddress, 16);
	memcpy(m_WifiCfg.struWifiCfg.struEtherNet.sFirstDns,m_strDns1,16);
	memcpy(m_WifiCfg.struWifiCfg.struEtherNet.sSecondDns,m_strDns2,16);
	memcpy(m_WifiCfg.struWifiCfg.struEtherNet.sGatewayIpAddr,m_strGatewayAddr,16);
	memcpy(m_WifiCfg.struWifiCfg.struEtherNet.sIpMask,m_strHideCode,16);
	
	if (m_WifiCfg.struWifiCfg.dwSecurity == 1)
	{
		m_WifiCfg.struWifiCfg.key.wep.dwAuthentication = m_AuthCtrl.GetCurSel();
		m_WifiCfg.struWifiCfg.key.wep.dwKeyLength = m_KeyLenCtrl.GetCurSel();
		m_WifiCfg.struWifiCfg.key.wep.dwKeyType = m_KeyTypeCtrl.GetCurSel();
		m_WifiCfg.struWifiCfg.key.wep.dwActive = m_ActiveKey.GetCurSel();
		memcpy(m_WifiCfg.struWifiCfg.key.wep.sKeyInfo[0],m_strKey1,WIFI_WEP_MAX_KEY_LENGTH);
		memcpy(m_WifiCfg.struWifiCfg.key.wep.sKeyInfo[1],m_strKey2,WIFI_WEP_MAX_KEY_LENGTH);
		memcpy(m_WifiCfg.struWifiCfg.key.wep.sKeyInfo[2],m_strKey3,WIFI_WEP_MAX_KEY_LENGTH);
		memcpy(m_WifiCfg.struWifiCfg.key.wep.sKeyInfo[3],m_strKey4,WIFI_WEP_MAX_KEY_LENGTH);
		if (m_AuthCtrl.GetCurSel() == -1)
		{
			AfxMessageBox("Please select verification mode.");
			return;
		}
		if (m_KeyLenCtrl.GetCurSel() == -1)
		{
			AfxMessageBox("Please select key's length");
			return;
		}
		if (m_KeyTypeCtrl.GetCurSel() == -1)
		{
			AfxMessageBox("Please select key's type");
			return;
		}
		if (m_ActiveKey.GetCurSel() == -1)
		{
			AfxMessageBox("Please activate one key");
			return;
		}
		int i = m_KeyLenCtrl.GetCurSel();
		int j = m_KeyTypeCtrl.GetCurSel();
		switch(i) 
		{
		case 0:
			if (j == 0)
			{
				int len = strlen(m_WifiCfg.struWifiCfg.key.wep.sKeyInfo[m_ActiveKey.GetCurSel()]);
				if (len != 10) 
				{
					AfxMessageBox("64 bits Hex number, please input 10 Hex number and can't be all 0");	
					return;
				}
			}	
			else
			{
				if (strlen(m_WifiCfg.struWifiCfg.key.wep.sKeyInfo[m_ActiveKey.GetCurSel()]) != 5) 
				{
					AfxMessageBox("64 bits ASCII code, please input 5 characters.");	
					return;
				}
			}
			break;
		case 1:
			if (j == 0)
			{
				if (strlen(m_WifiCfg.struWifiCfg.key.wep.sKeyInfo[m_ActiveKey.GetCurSel()]) != 26) 
				{
					AfxMessageBox("128 bits Hex number, please input 26 Hex number and can't be all 0");	
					return;
				}
			}	
			else
			{
				if (strlen(m_WifiCfg.struWifiCfg.key.wep.sKeyInfo[m_ActiveKey.GetCurSel()]) != 13) 
				{
					AfxMessageBox("128 bits ASCII code, please input 13 characters");	
					return;
				}
			}
			break;
		case 2:
			if (j == 0)
			{
				if (strlen(m_WifiCfg.struWifiCfg.key.wep.sKeyInfo[m_ActiveKey.GetCurSel()]) != 32) 
				{								
					AfxMessageBox("152 bits Hex number, please input 32 Hex number and can't be all 0");	
					return;
				}
			}	
			else
			{
				if (strlen(m_WifiCfg.struWifiCfg.key.wep.sKeyInfo[m_ActiveKey.GetCurSel()]) != 16) 
				{
					AfxMessageBox("152 bits ASCII code, please input 16 characters");	
					return;
				}
			}
		default:
			break;
		}
	}
	else if (m_WifiCfg.struWifiCfg.dwSecurity == 2 || m_WifiCfg.struWifiCfg.dwSecurity == 4)
	{
		if (m_uKeyLen < 8||m_uKeyLen > 64)
		{
			AfxMessageBox("Character length should be 8~64");
			return;
		}
		if (m_uKeyLen != strlen(m_strEncKey))
		{
			AfxMessageBox("Character length is not correct");
			return;
		}
		m_WifiCfg.struWifiCfg.key.wpa_psk.dwKeyLength = m_uKeyLen;
        m_WifiCfg.struWifiCfg.key.wpa_psk.byKeyType = m_comboKeyType.GetCurSel();
        if (m_WifiCfg.struWifiCfg.key.wpa_psk.byKeyType == 1)
        {
            memcpy(m_WifiCfg.struWifiCfg.key.wpa_psk.sNewKeyInfo, m_strEncKey, WIFI_WPA_PSK_MAX_HEXKEY_LENGTH);
        }
        else
        {
            memcpy(m_WifiCfg.struWifiCfg.key.wpa_psk.sKeyInfo, m_strEncKey, WIFI_WPA_PSK_MAX_HEXKEY_LENGTH);
        }
        

		m_WifiCfg.struWifiCfg.key.wpa_psk.byEncryptType = m_comboWpaEncType.GetCurSel();
	}
	else if (m_WifiCfg.struWifiCfg.dwSecurity == 3 || m_WifiCfg.struWifiCfg.dwSecurity == 5)
	{
		m_WifiCfg.struWifiCfg.key.wpa_wpa2.byEncryptType = m_comboWPAEnterEncry.GetCurSel();
		m_WifiCfg.struWifiCfg.key.wpa_wpa2.byAuthType = m_comboAuthType.GetCurSel();
		if (m_WifiCfg.struWifiCfg.key.wpa_wpa2.byAuthType == 0)
		{
			m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_TTLS.byEapolVersion = m_comboEapolVer.GetCurSel();
			m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_TTLS.byAuthType = m_comboInterAuthType.GetCurSel();
			memcpy(m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_TTLS.byAnonyIdentity,m_csAnonyIdentity,NAME_LEN);
			memcpy(m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_TTLS.byUserName, m_csUserName, NAME_LEN);
			memcpy(m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_TTLS.byPassword, m_csPassword, NAME_LEN);
		}
		else if (m_WifiCfg.struWifiCfg.key.wpa_wpa2.byAuthType == 1)
		{
			m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_PEAP.byEapolVersion = m_comboEapolVer.GetCurSel();
			m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_PEAP.byAuthType = m_comboPeapInterAuth.GetCurSel();
			m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_PEAP.byPeapVersion = m_comboPeapVer.GetCurSel();
			m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_PEAP.byPeapLabel = m_comboPeapLabel.GetCurSel();
			memcpy(m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_PEAP.byAnonyIdentity, m_csAnonyIdentity, NAME_LEN);
			memcpy(m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_PEAP.byUserName, m_csUserName, NAME_LEN);
		}
		else if (m_WifiCfg.struWifiCfg.key.wpa_wpa2.byAuthType == 2)
		{
			m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_TLS.byEapolVersion = m_comboEapolVer.GetCurSel();
			memcpy(m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_TLS.byIdentity, m_csIdentity, NAME_LEN);
			memcpy(m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_TLS.byPrivateKeyPswd, m_csPrivateKeyPwd, NAME_LEN);
		}
	}
	
 
    if (-1 != m_strHostAddr.Find("-"))
    {
        sscanf(m_strHostAddr, "%02x-%02x-%02x-%02x-%02x-%02x"\
            , &m_WifiCfg.struWifiCfg.struEtherNet.byMACAddr[0]
            , &m_WifiCfg.struWifiCfg.struEtherNet.byMACAddr[1]
            , &m_WifiCfg.struWifiCfg.struEtherNet.byMACAddr[2]
            , &m_WifiCfg.struWifiCfg.struEtherNet.byMACAddr[3]
            , &m_WifiCfg.struWifiCfg.struEtherNet.byMACAddr[4]
            , &m_WifiCfg.struWifiCfg.struEtherNet.byMACAddr[5]
            );
    }
    else if (-1 != m_strHostAddr.Find(":"))
    {
        sscanf(m_strHostAddr, "%02x:%02x:%02x:%02x:%02x:%02x"\
            , &m_WifiCfg.struWifiCfg.struEtherNet.byMACAddr[0]
            , &m_WifiCfg.struWifiCfg.struEtherNet.byMACAddr[1]
            , &m_WifiCfg.struWifiCfg.struEtherNet.byMACAddr[2]
            , &m_WifiCfg.struWifiCfg.struEtherNet.byMACAddr[3]
            , &m_WifiCfg.struWifiCfg.struEtherNet.byMACAddr[4]
            , &m_WifiCfg.struWifiCfg.struEtherNet.byMACAddr[5]
            );
    }

	if(!NET_DVR_SetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_SET_WIFI_CFG, 0, &m_WifiCfg, sizeof(NET_DVR_WIFI_CFG)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_WIFI_CFG");
		CString str;
		str.Format("Failed to config server info: NET_DVR_SET_WIFI_CFG = %d \n", NET_DVR_GetLastError());
		AfxMessageBox(str);
	}
	
	if(!NET_DVR_SetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_SET_WIFI_WORKMODE, 0, &m_WifiWorkMode, sizeof(NET_DVR_WIFI_WORKMODE)))
	{
		CString str;
		str.Format("Failed to cinfig server info: NET_DVR_SET_WIFI_WORKMODE = %d \n", NET_DVR_GetLastError());
		AfxMessageBox(str);
	}	
}

void CDlgWifi::OnSelchangeEncrypttype() 
{
	UpdateData(TRUE);
	int i = m_EncryptTypeCtrl.GetCurSel();
	switch(i)
	{
	case 0: 
		
		//			GetDlgItem(IDC_STATIC_DECLARE)->ShowWindow(FALSE);
		//			GetDlgItem(IDC_STATIC_WEP)->ShowWindow(FALSE);
		//			GetDlgItem(IDC_STATIC_WPAPSK)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_KEY1)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_KEY2)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_KEY3)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_KEY4)->ShowWindow(FALSE);
		GetDlgItem(IDC_KEY1)->ShowWindow(FALSE);
		GetDlgItem(IDC_KEY2)->ShowWindow(FALSE);
		GetDlgItem(IDC_KEY3)->ShowWindow(FALSE);
		GetDlgItem(IDC_KEY4)->ShowWindow(FALSE);
		GetDlgItem(IDC_AUTHENTICATION)->ShowWindow(FALSE);
		GetDlgItem(IDC_KEYLENGTH)->ShowWindow(FALSE);
		GetDlgItem(IDC_KEYTYPE)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_KEYTYPE)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_KEYLENGTH)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_AUTHEN)->ShowWindow(FALSE);
		
		GetDlgItem(IDC_STATIC_WPALIMIT)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_ENCRYPTKEY)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_KEYLEN)->ShowWindow(FALSE);
		GetDlgItem(IDC_ENCKEY)->ShowWindow(FALSE);
		GetDlgItem(IDC_KEY_LENGTH)->ShowWindow(FALSE);	
		GetDlgItem(IDC_STATIC_WPA_ENCTYPTTYPE)->ShowWindow(FALSE);
		GetDlgItem(IDC_COMBO_WPA_ENCTYPE)->ShowWindow(FALSE);
		break;
	case 1:	
		GetDlgItem(IDC_STATIC_DECLARE)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_WEP)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_KEY1)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_KEY2)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_KEY3)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_KEY4)->ShowWindow(TRUE);
		GetDlgItem(IDC_KEY1)->ShowWindow(TRUE);
		GetDlgItem(IDC_KEY2)->ShowWindow(TRUE);
		GetDlgItem(IDC_KEY3)->ShowWindow(TRUE);
		GetDlgItem(IDC_KEY4)->ShowWindow(TRUE);
		GetDlgItem(IDC_AUTHENTICATION)->ShowWindow(TRUE);
		GetDlgItem(IDC_KEYLENGTH)->ShowWindow(TRUE);
		GetDlgItem(IDC_KEYTYPE)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_KEYTYPE)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_KEYLENGTH)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_AUTHEN)->ShowWindow(TRUE);
		
		GetDlgItem(IDC_STATIC_WPALIMIT)->ShowWindow(FALSE);
		//			GetDlgItem(IDC_STATIC_WPAPSK)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_ENCRYPTKEY)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_KEYLEN)->ShowWindow(FALSE);
		GetDlgItem(IDC_ENCKEY)->ShowWindow(FALSE);
		GetDlgItem(IDC_KEY_LENGTH)->ShowWindow(FALSE);	
		GetDlgItem(IDC_STATIC_WPA_ENCTYPTTYPE)->ShowWindow(FALSE);
		GetDlgItem(IDC_COMBO_WPA_ENCTYPE)->ShowWindow(FALSE);
		break;
	case 2:	
		GetDlgItem(IDC_STATIC_DECLARE)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_WEP)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_KEY1)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_KEY2)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_KEY3)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_KEY4)->ShowWindow(FALSE);
		GetDlgItem(IDC_KEY1)->ShowWindow(FALSE);
		GetDlgItem(IDC_KEY2)->ShowWindow(FALSE);
		GetDlgItem(IDC_KEY3)->ShowWindow(FALSE);
		GetDlgItem(IDC_KEY4)->ShowWindow(FALSE);
		GetDlgItem(IDC_AUTHENTICATION)->ShowWindow(FALSE);
		GetDlgItem(IDC_KEYLENGTH)->ShowWindow(FALSE);
		GetDlgItem(IDC_KEYTYPE)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_KEYTYPE)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_KEYLENGTH)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_AUTHEN)->ShowWindow(FALSE);
		
		GetDlgItem(IDC_STATIC_WPALIMIT)->ShowWindow(TRUE);
		//			GetDlgItem(IDC_STATIC_WPAPSK)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_ENCRYPTKEY)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_KEYLEN)->ShowWindow(TRUE);
		GetDlgItem(IDC_ENCKEY)->ShowWindow(TRUE);
		GetDlgItem(IDC_KEY_LENGTH)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_WPA_ENCTYPTTYPE)->ShowWindow(TRUE);
		GetDlgItem(IDC_COMBO_WPA_ENCTYPE)->ShowWindow(TRUE);
		break;
	case 4:
        GetDlgItem(IDC_STATIC_DECLARE)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_WEP)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_KEY1)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_KEY2)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_KEY3)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_KEY4)->ShowWindow(FALSE);
		GetDlgItem(IDC_KEY1)->ShowWindow(FALSE);
		GetDlgItem(IDC_KEY2)->ShowWindow(FALSE);
		GetDlgItem(IDC_KEY3)->ShowWindow(FALSE);
		GetDlgItem(IDC_KEY4)->ShowWindow(FALSE);
		GetDlgItem(IDC_AUTHENTICATION)->ShowWindow(FALSE);
		GetDlgItem(IDC_KEYLENGTH)->ShowWindow(FALSE);
		GetDlgItem(IDC_KEYTYPE)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_KEYTYPE)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_KEYLENGTH)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_AUTHEN)->ShowWindow(FALSE);
		
		GetDlgItem(IDC_STATIC_WPALIMIT)->ShowWindow(TRUE);
		//			GetDlgItem(IDC_STATIC_WPAPSK)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_ENCRYPTKEY)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_KEYLEN)->ShowWindow(TRUE);
		GetDlgItem(IDC_ENCKEY)->ShowWindow(TRUE);
		GetDlgItem(IDC_KEY_LENGTH)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_WPA_ENCTYPTTYPE)->ShowWindow(TRUE);
		GetDlgItem(IDC_COMBO_WPA_ENCTYPE)->ShowWindow(TRUE);
		break;
	default:
		GetDlgItem(IDC_STATIC_DECLARE)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_WEP)->ShowWindow(FALSE);
		//			GetDlgItem(IDC_STATIC_WPAPSK)->ShowWindow(FALSE);	
		GetDlgItem(IDC_STATIC_KEY1)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_KEY2)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_KEY3)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_KEY4)->ShowWindow(FALSE);
		GetDlgItem(IDC_KEY1)->ShowWindow(FALSE);
		GetDlgItem(IDC_KEY2)->ShowWindow(FALSE);
		GetDlgItem(IDC_KEY3)->ShowWindow(FALSE);
		GetDlgItem(IDC_KEY4)->ShowWindow(FALSE);
		GetDlgItem(IDC_AUTHENTICATION)->ShowWindow(FALSE);
		GetDlgItem(IDC_KEYLENGTH)->ShowWindow(FALSE);
		GetDlgItem(IDC_KEYTYPE)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_KEYTYPE)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_KEYLENGTH)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_AUTHEN)->ShowWindow(FALSE);
		
		GetDlgItem(IDC_STATIC_WPALIMIT)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_ENCRYPTKEY)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_KEYLEN)->ShowWindow(FALSE);
		GetDlgItem(IDC_ENCKEY)->ShowWindow(FALSE);
		GetDlgItem(IDC_KEY_LENGTH)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_WPA_ENCTYPTTYPE)->ShowWindow(FALSE);
		GetDlgItem(IDC_COMBO_WPA_ENCTYPE)->ShowWindow(FALSE);
		break;
	}
}

void CDlgWifi::OnStartdhcp() 
{
	UpdateData(TRUE);
	if (m_bStartDhcp)
	{
		GetDlgItem(IDC_AUTODNS) ->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_AUTODNS) ->EnableWindow(FALSE);
	}
}

void CDlgWifi::OnAutodns() 
{
	UpdateData(TRUE);
	if (m_bAutoDns)
	{
		
	}
}

void CDlgWifi::OnDblclkWifiList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	int iItemSel = 0;
	CString csTxt;
	
	POSITION  iPos = m_WifiList.GetFirstSelectedItemPosition();
	if (iPos == NULL)
	{
		return;
	}
	iItemSel = m_WifiList.GetNextSelectedItem(iPos);
	csTxt.Format("%s",m_WifiList.GetItemText(iItemSel,0));
	GetDlgItem(IDC_SSID) ->SetWindowText(csTxt);
	
	csTxt.Format("%s",m_WifiList.GetItemText(iItemSel,1));
	UINT i; 
	if (csTxt == "manage")
	{
		i = 0;
	}
	else
	{
		i = 1;
	}		
	m_WorkModeCtrl.SetCurSel(i);
	
	
	csTxt.Format("%s",m_WifiList.GetItemText(iItemSel,2));
	if (csTxt == "wpa-psk")
	{
		i = 2;
	}
	else if (csTxt == "wep")
	{
		i = 1;
	}
	else if (csTxt == "wpa2-psk")
	{
		i = 4;
	}
	else
	{
		i = 0;
	}	
	
	m_EncryptTypeCtrl.SetCurSel(i);
	
	OnSelchangeEncrypttype();
	
	*pResult = 0;
}

BOOL CDlgWifi::GetParam()
{
	DWORD dwReturned = 0;
	if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID,NET_DVR_GET_WIFI_WORKMODE, 0,&m_WifiWorkMode, sizeof(NET_DVR_WIFI_WORKMODE), &dwReturned))	
	{
		CString sTemp;
		sTemp.Format("ERROR: NET_DVR_GET_WIFI_WORKMODE = %d \n", NET_DVR_GetLastError());
		TRACE(sTemp);
		//return FALSE;
	}
	else
	{
		m_EthernetWorkMode.SetCurSel(m_WifiWorkMode.dwNetworkInterfaceMode);
	}
	
	if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID,NET_DVR_GET_AP_INFO_LIST, 0,&m_ApInfo, sizeof(NET_DVR_AP_INFO_LIST), &dwReturned))	
	{
		CString sTemp;
		sTemp.Format("ERROR: NET_DVR_GET_AP_INFO_LIST = %d \n", NET_DVR_GetLastError());
		TRACE(sTemp);
		//return FALSE;
	}
	else
	{
		if (m_ApInfo.dwCount > WIFI_MAX_AP_COUNT)
		{
			m_ApInfo.dwCount = WIFI_MAX_AP_COUNT;
		}
		else
		{
			m_uApNum = m_ApInfo.dwCount;
			DWORD dwApNum = 0;
			CString strTemp;
			while (dwApNum < m_ApInfo.dwCount)
			{							
				m_WifiList.InsertItem(dwApNum, m_ApInfo.struApInfo[dwApNum].sSsid, 0);
				switch(m_ApInfo.struApInfo[dwApNum].dwMode) 
				{
				case 0:
					m_WifiList.SetItemText(dwApNum, 1, "manage");
					break;
				case 1:
					m_WifiList.SetItemText(dwApNum, 1, "ad-hoc");
					break;
				default:
					m_WifiList.SetItemText(dwApNum, 1, "");
				}
				switch(m_ApInfo.struApInfo[dwApNum].dwSecurity)
				{
				case 0:
					m_WifiList.SetItemText(dwApNum, 2, "None");
					break;
				case 1:
					m_WifiList.SetItemText(dwApNum, 2, "wep");
					break;
				case 2:
					m_WifiList.SetItemText(dwApNum, 2, "wpa-psk");
					break;
				case 3:
					m_WifiList.SetItemText(dwApNum, 2, "wpa-Enterprise");
					break;
				case 4:
					m_WifiList.SetItemText(dwApNum, 2, "wpa2-psk");
					break;
				default:
					m_WifiList.SetItemText(dwApNum, 2, "None");
				}
				
				strTemp.Format("%d",m_ApInfo.struApInfo[dwApNum].dwChannel);
				m_WifiList.SetItemText(dwApNum, 3, strTemp);
				strTemp.Format("%d",m_ApInfo.struApInfo[dwApNum].dwSignalStrength);
				m_WifiList.SetItemText(dwApNum, 4, strTemp);
				strTemp.Format("%d",m_ApInfo.struApInfo[dwApNum].dwSpeed);
				m_WifiList.SetItemText(dwApNum, 5, strTemp);
				
				dwApNum++;
			}
		}
	}
	
	m_WifiCfg.dwSize = sizeof(m_WifiCfg);
	if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID,NET_DVR_GET_WIFI_CFG, 0,&m_WifiCfg, sizeof(NET_DVR_WIFI_CFG), &dwReturned))	
	{
		CString sTemp;
		sTemp.Format("ERROR: NET_DVR_GET_WIFI_CFG = %d \n", NET_DVR_GetLastError());
		TRACE(sTemp);
		//return FALSE;
	}
	else
	{
		m_strIpAddress = m_WifiCfg.struWifiCfg.struEtherNet.sIpAddress;
		m_strDns1 = m_WifiCfg.struWifiCfg.struEtherNet.sFirstDns;
		m_strDns2 = m_WifiCfg.struWifiCfg.struEtherNet.sSecondDns;
		m_strGatewayAddr = m_WifiCfg.struWifiCfg.struEtherNet.sGatewayIpAddr;
		CString str;
		str.Format("%x:%x:%x:%x:%x;%x",m_WifiCfg.struWifiCfg.struEtherNet.byMACAddr[0],m_WifiCfg.struWifiCfg.struEtherNet.byMACAddr[1]
			,m_WifiCfg.struWifiCfg.struEtherNet.byMACAddr[2],m_WifiCfg.struWifiCfg.struEtherNet.byMACAddr[3]
			,m_WifiCfg.struWifiCfg.struEtherNet.byMACAddr[4],m_WifiCfg.struWifiCfg.struEtherNet.byMACAddr[5]);
		TRACE(str);
		m_strHostAddr = str;
		m_strHideCode = m_WifiCfg.struWifiCfg.struEtherNet.sIpMask;
		m_strSsid = m_WifiCfg.struWifiCfg.sEssid;
		m_WorkModeCtrl.SetCurSel(m_WifiCfg.struWifiCfg.dwMode);
		m_EncryptTypeCtrl.SetCurSel(m_WifiCfg.struWifiCfg.dwSecurity);
		
		if (m_WifiCfg.struWifiCfg.dwSecurity == 1) 
		{
			m_AuthCtrl.SetCurSel(m_WifiCfg.struWifiCfg.key.wep.dwAuthentication);
			m_KeyLenCtrl.SetCurSel(m_WifiCfg.struWifiCfg.key.wep.dwKeyLength);
			m_KeyTypeCtrl.SetCurSel(m_WifiCfg.struWifiCfg.key.wep.dwKeyType);	
			m_ActiveKey.SetCurSel(m_WifiCfg.struWifiCfg.key.wep.dwActive);
			m_strKey1 = m_WifiCfg.struWifiCfg.key.wep.sKeyInfo[0];
			m_strKey2 = m_WifiCfg.struWifiCfg.key.wep.sKeyInfo[1];
			m_strKey3 = m_WifiCfg.struWifiCfg.key.wep.sKeyInfo[2];
			m_strKey4 = m_WifiCfg.struWifiCfg.key.wep.sKeyInfo[3];
			GetDlgItem(IDC_STATIC_DECLARE)->ShowWindow(TRUE);
			GetDlgItem(IDC_STATIC_WEP)->ShowWindow(TRUE);
			GetDlgItem(IDC_STATIC_KEY1)->ShowWindow(TRUE);
			GetDlgItem(IDC_STATIC_KEY2)->ShowWindow(TRUE);
			GetDlgItem(IDC_STATIC_KEY3)->ShowWindow(TRUE);
			GetDlgItem(IDC_STATIC_KEY4)->ShowWindow(TRUE);
			GetDlgItem(IDC_KEY1)->ShowWindow(TRUE);
			GetDlgItem(IDC_KEY2)->ShowWindow(TRUE);
			GetDlgItem(IDC_KEY3)->ShowWindow(TRUE);
			GetDlgItem(IDC_KEY4)->ShowWindow(TRUE);
			GetDlgItem(IDC_AUTHENTICATION)->ShowWindow(TRUE);
			GetDlgItem(IDC_KEYLENGTH)->ShowWindow(TRUE);
			GetDlgItem(IDC_KEYTYPE)->ShowWindow(TRUE);
			GetDlgItem(IDC_STATIC_KEYTYPE)->ShowWindow(TRUE);
			GetDlgItem(IDC_STATIC_KEYLENGTH)->ShowWindow(TRUE);
			GetDlgItem(IDC_STATIC_AUTHEN)->ShowWindow(TRUE);
			
			GetDlgItem(IDC_STATIC_WPALIMIT)->ShowWindow(FALSE);
			//					GetDlgItem(IDC_STATIC_WPAPSK)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC_ENCRYPTKEY)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC_KEYLEN)->ShowWindow(FALSE);
			GetDlgItem(IDC_ENCKEY)->ShowWindow(FALSE);
			GetDlgItem(IDC_KEY_LENGTH)->ShowWindow(FALSE);	
			GetDlgItem(IDC_STATIC_WPA_ENCTYPTTYPE)->ShowWindow(FALSE);
			GetDlgItem(IDC_COMBO_WPA_ENCTYPE)->ShowWindow(FALSE);
		}
		else if (m_WifiCfg.struWifiCfg.dwSecurity == 2 || m_WifiCfg.struWifiCfg.dwSecurity == 4)
		{
			m_uKeyLen = m_WifiCfg.struWifiCfg.key.wpa_psk.dwKeyLength;
            if (0 == m_WifiCfg.struWifiCfg.key.wpa_psk.byKeyType)
            {
                m_strEncKey = m_WifiCfg.struWifiCfg.key.wpa_psk.sKeyInfo;
            }
			else if (1 == m_WifiCfg.struWifiCfg.key.wpa_psk.byKeyType)
            {
                m_strEncKey = m_WifiCfg.struWifiCfg.key.wpa_psk.sNewKeyInfo;
            }
			GetDlgItem(IDC_STATIC_DECLARE)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC_WEP)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC_KEY1)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC_KEY2)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC_KEY3)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC_KEY4)->ShowWindow(FALSE);
			GetDlgItem(IDC_KEY1)->ShowWindow(FALSE);
			GetDlgItem(IDC_KEY2)->ShowWindow(FALSE);
			GetDlgItem(IDC_KEY3)->ShowWindow(FALSE);
			GetDlgItem(IDC_KEY4)->ShowWindow(FALSE);
			GetDlgItem(IDC_AUTHENTICATION)->ShowWindow(FALSE);
			GetDlgItem(IDC_KEYLENGTH)->ShowWindow(FALSE);
			GetDlgItem(IDC_KEYTYPE)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC_KEYTYPE)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC_KEYLENGTH)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC_AUTHEN)->ShowWindow(FALSE);
			
			GetDlgItem(IDC_STATIC_WPALIMIT)->ShowWindow(TRUE);
			//					GetDlgItem(IDC_STATIC_WPAPSK)->ShowWindow(TRUE);
			GetDlgItem(IDC_STATIC_ENCRYPTKEY)->ShowWindow(TRUE);
			GetDlgItem(IDC_STATIC_KEYLEN)->ShowWindow(TRUE);
			GetDlgItem(IDC_ENCKEY)->ShowWindow(TRUE);
			GetDlgItem(IDC_KEY_LENGTH)->ShowWindow(TRUE);	
			GetDlgItem(IDC_STATIC_WPA_ENCTYPTTYPE)->ShowWindow(TRUE);
			GetDlgItem(IDC_COMBO_WPA_ENCTYPE)->ShowWindow(TRUE);
			m_comboWpaEncType.SetCurSel(m_WifiCfg.struWifiCfg.key.wpa_psk.byEncryptType);
		}
		else if (m_WifiCfg.struWifiCfg.dwSecurity == 3 || m_WifiCfg.struWifiCfg.dwSecurity ==5)
		{
			GetDlgItem(IDC_STATIC_DECLARE)->ShowWindow(FALSE);
			//					GetDlgItem(IDC_STATIC_WPAPSK)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC_WEP)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC_KEY1)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC_KEY2)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC_KEY3)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC_KEY4)->ShowWindow(FALSE);
			GetDlgItem(IDC_KEY1)->ShowWindow(FALSE);
			GetDlgItem(IDC_KEY2)->ShowWindow(FALSE);
			GetDlgItem(IDC_KEY3)->ShowWindow(FALSE);
			GetDlgItem(IDC_KEY4)->ShowWindow(FALSE);
			GetDlgItem(IDC_AUTHENTICATION)->ShowWindow(FALSE);
			GetDlgItem(IDC_KEYLENGTH)->ShowWindow(FALSE);
			GetDlgItem(IDC_KEYTYPE)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC_KEYTYPE)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC_KEYLENGTH)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC_AUTHEN)->ShowWindow(FALSE);
			
			GetDlgItem(IDC_STATIC_WPALIMIT)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC_ENCRYPTKEY)->ShowWindow(FALSE);
			GetDlgItem(IDC_STATIC_KEYLEN)->ShowWindow(FALSE);
			GetDlgItem(IDC_ENCKEY)->ShowWindow(FALSE);
			GetDlgItem(IDC_KEY_LENGTH)->ShowWindow(FALSE);	
			m_comboWPAEnterEncry.SetCurSel(m_WifiCfg.struWifiCfg.key.wpa_wpa2.byEncryptType);
			m_comboAuthType.SetCurSel(m_WifiCfg.struWifiCfg.key.wpa_wpa2.byAuthType);
			if (m_WifiCfg.struWifiCfg.key.wpa_wpa2.byAuthType == 0)
			{
				m_comboEapolVer.SetCurSel(m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_TTLS.byEapolVersion);
				m_comboInterAuthType.SetCurSel(m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_TTLS.byAuthType);
				m_csAnonyIdentity = m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_TTLS.byAnonyIdentity;
				m_csUserName = m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_TTLS.byUserName;
				m_csPassword = m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_TTLS.byPassword;
			}
			else if (m_WifiCfg.struWifiCfg.key.wpa_wpa2.byAuthType == 1)
			{
				m_comboEapolVer.SetCurSel(m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_PEAP.byEapolVersion);
				m_comboPeapInterAuth.SetCurSel(m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_PEAP.byAuthType);
				m_comboPeapVer.SetCurSel(m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_PEAP.byPeapVersion);
				m_comboPeapLabel.SetCurSel(m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_PEAP.byPeapLabel);
				m_csAnonyIdentity = m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_PEAP.byAnonyIdentity;
				m_csUserName = m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_PEAP.byUserName;
			}
			else if (m_WifiCfg.struWifiCfg.key.wpa_wpa2.byAuthType == 2)
			{
				m_comboEapolVer.SetCurSel(m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_TLS.byEapolVersion);
				m_csPrivateKeyPwd = m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_TLS.byPrivateKeyPswd;
				m_csIdentity = m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_TLS.byIdentity;
			}
		}
// 		else
// 		{
//             m_uKeyLen = m_WifiCfg.struWifiCfg.key.wpa_psk.dwKeyLength;
// 			m_strEncKey = m_WifiCfg.struWifiCfg.key.wpa_psk.sKeyInfo;
// 			GetDlgItem(IDC_STATIC_DECLARE)->ShowWindow(FALSE);
// 			GetDlgItem(IDC_STATIC_WEP)->ShowWindow(FALSE);
// 			GetDlgItem(IDC_STATIC_KEY1)->ShowWindow(FALSE);
// 			GetDlgItem(IDC_STATIC_KEY2)->ShowWindow(FALSE);
// 			GetDlgItem(IDC_STATIC_KEY3)->ShowWindow(FALSE);
// 			GetDlgItem(IDC_STATIC_KEY4)->ShowWindow(FALSE);
// 			GetDlgItem(IDC_KEY1)->ShowWindow(FALSE);
// 			GetDlgItem(IDC_KEY2)->ShowWindow(FALSE);
// 			GetDlgItem(IDC_KEY3)->ShowWindow(FALSE);
// 			GetDlgItem(IDC_KEY4)->ShowWindow(FALSE);
// 			GetDlgItem(IDC_AUTHENTICATION)->ShowWindow(FALSE);
// 			GetDlgItem(IDC_KEYLENGTH)->ShowWindow(FALSE);
// 			GetDlgItem(IDC_KEYTYPE)->ShowWindow(FALSE);
// 			GetDlgItem(IDC_STATIC_KEYTYPE)->ShowWindow(FALSE);
// 			GetDlgItem(IDC_STATIC_KEYLENGTH)->ShowWindow(FALSE);
// 			GetDlgItem(IDC_STATIC_AUTHEN)->ShowWindow(FALSE);
// 			
// 			GetDlgItem(IDC_STATIC_WPALIMIT)->ShowWindow(TRUE);
// 			//					GetDlgItem(IDC_STATIC_WPAPSK)->ShowWindow(TRUE);
// 			GetDlgItem(IDC_STATIC_ENCRYPTKEY)->ShowWindow(TRUE);
// 			GetDlgItem(IDC_STATIC_KEYLEN)->ShowWindow(TRUE);
// 			GetDlgItem(IDC_ENCKEY)->ShowWindow(TRUE);
// 			GetDlgItem(IDC_KEY_LENGTH)->ShowWindow(TRUE);	
// 			GetDlgItem(IDC_STATIC_WPA_ENCTYPTTYPE)->ShowWindow(TRUE);
// 			GetDlgItem(IDC_COMBO_WPA_ENCTYPE)->ShowWindow(TRUE);
// 			m_comboWpaEncType.SetCurSel(m_WifiCfg.struWifiCfg.key.wpa_psk.byEncryptType);
// 		}
		
		m_bStartDhcp = m_WifiCfg.struWifiCfg.struEtherNet.dwEnableDhcp;
		m_bAutoDns = m_WifiCfg.struWifiCfg.struEtherNet.dwAutoDns;
        m_byCloseWifi = m_WifiCfg.struWifiCfg.struEtherNet.byCloseWifi;
		
	}
	if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID,NET_DVR_GET_WIFI_STATUS, 0,&m_struWifiStatus, sizeof(NET_DVR_WIFI_CONNECT_STATUS), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_WIFI_STATUS");
	}
	else
	{
		m_cmbConnectStatus.SetCurSel(m_struWifiStatus.byCurStatus - 1);
		m_cmbErrorCode.SetCurSel(m_struWifiStatus.dwErrorCode);
	}
	UpdateData(FALSE);	
	return TRUE;
}

void CDlgWifi::OnExit() 
{
	CDialog::OnOK();
}

void CDlgWifi::OnSelchangeComboAuthType() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_comboAuthType.GetCurSel() == 0)
	{
		m_comboEapolVer.SetCurSel(m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_TTLS.byEapolVersion);
		m_comboInterAuthType.SetCurSel(m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_TTLS.byAuthType);
		m_csAnonyIdentity = m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_TTLS.byAnonyIdentity;
		m_csUserName = m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_TTLS.byUserName;
		m_csPassword = m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_TTLS.byPassword;
	}
	else if (m_comboAuthType.GetCurSel() == 1)
	{
		m_comboEapolVer.SetCurSel(m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_PEAP.byEapolVersion);
		m_comboPeapInterAuth.SetCurSel(m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_PEAP.byAuthType);
		m_comboPeapVer.SetCurSel(m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_PEAP.byPeapVersion);
		m_comboPeapLabel.SetCurSel(m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_PEAP.byPeapLabel);
		m_csAnonyIdentity = m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_PEAP.byAnonyIdentity;
		m_csUserName = m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_PEAP.byUserName;
	}
	else if (m_comboAuthType.GetCurSel() == 2)
	{
		m_comboEapolVer.SetCurSel(m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_TLS.byEapolVersion);
		m_csPrivateKeyPwd = m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_TLS.byPrivateKeyPswd;
		m_csIdentity = m_WifiCfg.struWifiCfg.key.wpa_wpa2.auth_param.EAP_TLS.byIdentity;
	}
	
}

void CDlgWifi::OnBtnScanCert() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	char szLan[128] = {0};
    OPENFILENAME ofn = {0};
	CRect struRect;
	
    memset(m_chFilename, 0, MAX_PATH);
    
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner   = this->GetSafeHwnd();
    ofn.lpstrFilter = "All Files\0*.*\0\0";
    ofn.lpstrFile   = m_chFilename;
    ofn.nMaxFile    = MAX_PATH;
    ofn.Flags       = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
    
    if (GetOpenFileName(&ofn))
    {
        m_csCertPath.Format("%s", m_chFilename);
    }
	
	if (strlen(m_chFilename) == 0)
	{
		return;
	}
	
	UpdateData(FALSE);
	
}
#define UPLOAD_TIMER WM_USER+1

void CDlgWifi::OnBtnUploadCert() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    
	char szLan[128] = {0};
	
	NET_DVR_CERT_PARAM struInBuf = {0};
	struInBuf.dwSize = sizeof(struInBuf);
	struInBuf.byFileType = m_comboFileType.GetCurSel();
	struInBuf.wCertType = m_comboCertType.GetCurSel();
	struInBuf.wCertFunc = 0;
    m_lUploadHandle = NET_DVR_UploadFile(g_struDeviceInfo[m_iDeviceIndex].lLoginID, UPLOAD_CERTIFICATE, &struInBuf, sizeof(struInBuf),m_chFilename);
    if (m_lUploadHandle == -1)
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadFile");
		g_StringLanType(szLan, "上传文件失败", "Start upload file failed!");
		m_csUploadState.Format("%s", szLan);	
		AfxMessageBox(szLan);
		
		return;
    }
    else
    {   
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadFile");
        SetTimer(UPLOAD_TIMER, 50, NULL);
    }
	
    UpdateData(FALSE);	
}

#if (_MSC_VER >= 1500)	//vs2008
void CDlgWifi::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgWifi::OnTimer(UINT nIDEvent)
#endif
{
	// TODO: Add your message handler code here and/or call default
	UpdateData(TRUE);
	char szLan[128] = {0};
	if (nIDEvent == UPLOAD_TIMER)
	{
		DWORD dwProgress = 0;
		int state = NET_DVR_GetUploadState(m_lUploadHandle, &dwProgress);
		
		if (state == 1)
		{
			g_StringLanType(szLan, "上传成功", "Upload successfully");
			m_csUploadState.Format(szLan);
		}
		else if (state == 2)
		{
			g_StringLanType(szLan, "正在上传,已上传:%d", "Is uploading,progress:%d");
			m_csUploadState.Format(szLan, dwProgress);
		}
		else if (state == 3)
		{
			g_StringLanType(szLan, "上传失败", "Upload failed");
			m_csUploadState.Format(szLan);
		}
		else if (state == 4)
		{
			g_StringLanType(szLan, "网络断开，状态未知", "Network disconnect, status unknown");
			m_csUploadState.Format(szLan);
		}
		
		if (state != 2 && state != 5)
		{        
			KillTimer(UPLOAD_TIMER);
			NET_DVR_UploadClose(m_lUploadHandle);
		}
	}
	CDialog::OnTimer(nIDEvent);
	
	UpdateData(FALSE);
}

void CDlgWifi::OnBtnGetConnectStatus() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturned = 0;
	if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID,NET_DVR_GET_WIFI_STATUS, 0,&m_struWifiStatus, sizeof(NET_DVR_WIFI_CONNECT_STATUS), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_WIFI_STATUS");
	}
	else
	{
		m_cmbConnectStatus.SetCurSel(m_struWifiStatus.byCurStatus - 1);
		m_cmbErrorCode.SetCurSel(m_struWifiStatus.dwErrorCode);
	}
}
