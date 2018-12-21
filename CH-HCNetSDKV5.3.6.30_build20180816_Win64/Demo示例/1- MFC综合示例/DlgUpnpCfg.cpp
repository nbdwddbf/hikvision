// DlgUpnpCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgUpnpCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgUpnpCfg dialog


CDlgUpnpCfg::CDlgUpnpCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUpnpCfg::IDD, pParent)
    , m_iSdkOverTlsPort(0)
    , m_bSdkOverTlsEnable(FALSE)
{
	//{{AFX_DATA_INIT(CDlgUpnpCfg)
	m_iServerPort = 0;
	m_iRtspPort = 0;
	m_csNatIp = _T("");
	m_iAdminPort = 0;
	m_bEnableNat = FALSE;
	m_bEnableWeb = FALSE;
	m_bEnableUpnp = FALSE;
	m_bEnableRtsp = FALSE;
	m_bEnableAdmin = FALSE;
	m_bEnableHttps = FALSE;
	m_csPoeIP = _T("");
	m_csFriendName = _T("");
	m_bEnableHppts = FALSE;
	m_iHttpsPort = 0;
	//}}AFX_DATA_INIT
}


void CDlgUpnpCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgUpnpCfg)
    DDX_Control(pDX, IDC_COMBO_NAT_TYPE, m_comboNatType);
    DDX_Control(pDX, IDC_LIST_STATE, m_listState);
    DDX_Text(pDX, IDC_EDIT_SERVER_PORT, m_iServerPort);
    DDX_Text(pDX, IDC_EDIT_RTSP_PORT, m_iRtspPort);
    DDX_Text(pDX, IDC_EDIT_NAT_IP, m_csNatIp);
    DDX_Text(pDX, IDC_EDIT_ADMIN_PORT, m_iAdminPort);
    DDX_Text(pDX, IDC_EDIT_HTTPS_PORT, m_iHttpsPort);
    DDX_Check(pDX, IDC_CHK_NAT, m_bEnableNat);
    DDX_Check(pDX, IDC_CHK_ENABLE_WEB, m_bEnableWeb);
    DDX_Check(pDX, IDC_CHK_ENABLE_UPNP, m_bEnableUpnp);
    DDX_Check(pDX, IDC_CHK_ENABLE_RTSP, m_bEnableRtsp);
    DDX_Check(pDX, IDC_CHK_ENABLE_ADMIN, m_bEnableAdmin);
    DDX_Check(pDX, IDC_CHK_ENABLE_HTTPS, m_bEnableHttps);
    DDX_Text(pDX, IDC_EDIT_POE_IP, m_csPoeIP);
    DDX_Text(pDX, IDC_EDIT_UPNP_FRIEND_NAME, m_csFriendName);
    DDX_Text(pDX, IDC_EDIT_HTTPS_PORT, m_iHttpsPort);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_SDKOVERTLS_PORT, m_iSdkOverTlsPort);
    DDX_Check(pDX, IDC_CHK_ENABLE_SDKOVERTLS, m_bSdkOverTlsEnable);
}


BEGIN_MESSAGE_MAP(CDlgUpnpCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgUpnpCfg)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_SETIP, OnButtonSetup)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_STATE, OnButtonUpdateState)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_GET_POE, OnButtonGetPoe)
	ON_BN_CLICKED(IDC_BUTTON_SET_POE, OnButtonSetPoe)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgUpnpCfg message handlers

BOOL ValidIPv6(BYTE *ip)
{
	if (strlen((char *)ip) > 2 && strchr((char *)ip, ':') != NULL)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CDlgUpnpCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	char szLan[1024] = {0};
	m_listState.SetExtendedStyle(m_listState.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
 
	g_StringLanType(szLan, "端口", "Port");
    m_listState.InsertColumn(0, szLan, LVCFMT_LEFT, 50, -1);
	g_StringLanType(szLan, "启用", "Enable");
    m_listState.InsertColumn(1, szLan, LVCFMT_LEFT, 40, -1);
    g_StringLanType(szLan, "映射前端口", "Internal Port");
    m_listState.InsertColumn(2, szLan, LVCFMT_LEFT, 80, -1);
    g_StringLanType(szLan, "映射后端口", "External Port");
    m_listState.InsertColumn(3, szLan, LVCFMT_LEFT,80, -1);
    g_StringLanType(szLan, "状态", "State");
    m_listState.InsertColumn(4, szLan, LVCFMT_LEFT, 200, -1);
    g_StringLanType(szLan, "映射后IP", "External IP");
    m_listState.InsertColumn(5, szLan, LVCFMT_LEFT, 100, -1);
    g_StringLanType(szLan, "路由器LAN IP", "Router LAN IP");
    m_listState.InsertColumn(6, szLan, LVCFMT_LEFT, 100, -1);	

	m_listState.InsertItem(0, "Web", 0);	
	m_listState.InsertItem(1, "Admin", 0);
	m_listState.InsertItem(2, "RTSP", 0);
	m_listState.InsertItem(3, "Https",0);
    m_listState.InsertItem(4, "SHIPIN7_CMD", 0);
    m_listState.InsertItem(5, "SHIPIN7_STREAM", 0);
    m_listState.InsertItem(6, "SDK over TLS", 0);

	OnButtonUpdateState();
	OnButtonUpdate();
	OnButtonGetPoe();
	
	return TRUE;
}

void CDlgUpnpCfg::OnButtonUpdate() 
{
	char strTemp[65] = {0};
	memset(strTemp,0,65);
	memset(&m_strNatCfg, 0, sizeof(m_strNatCfg));
	DWORD dwReturned = 0;
	if(!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_NAT_CFG, 0xff, &m_strNatCfg, sizeof(m_strNatCfg), &dwReturned))
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_NAT_CFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_NAT_CFG");
		m_bEnableUpnp = m_strNatCfg.wEnableUpnp;
		m_bEnableNat = m_strNatCfg.wEnableNat;
		
		//暂不支持V6
		m_csNatIp.Format("%s", m_strNatCfg.struIpAddr.sIpV4);
		
		m_bEnableWeb = m_strNatCfg.struHttpPort.wEnable;
		m_iServerPort = m_strNatCfg.struHttpPort.wExtPort;

		m_bEnableAdmin = m_strNatCfg.struCmdPort.wEnable;
		m_iAdminPort = m_strNatCfg.struCmdPort.wExtPort;

		m_bEnableRtsp = m_strNatCfg.struRtspPort.wEnable;
		m_iRtspPort = m_strNatCfg.struRtspPort.wExtPort;

		m_bEnableHttps = m_strNatCfg.struHttpsPort.wEnable;
	

		m_iHttpsPort = m_strNatCfg.struHttpsPort.wExtPort;

        m_bSdkOverTlsEnable = m_strNatCfg.struSDKOverTLSPort.wEnable;
        m_iSdkOverTlsPort = m_strNatCfg.struSDKOverTLSPort.wExtPort;

		m_comboNatType.SetCurSel(m_strNatCfg.byNatType);
		memcpy(strTemp,m_strNatCfg.byFriendName, 64);
		m_csFriendName.Format("%s", strTemp);
		UpdateData(FALSE);
	}
}

void CDlgUpnpCfg::OnButtonSetup() 
{
	UpdateData(TRUE);
	m_strNatCfg.dwSize = sizeof(m_strNatCfg);

	m_strNatCfg.wEnableUpnp = m_bEnableUpnp;
	m_strNatCfg.wEnableNat = m_bEnableNat;
	
	//暂不支持V6
	sprintf(m_strNatCfg.struIpAddr.sIpV4, "%s", m_csNatIp);
	
	m_strNatCfg.struHttpPort.wEnable = m_bEnableWeb;
	m_strNatCfg.struHttpPort.wExtPort = m_iServerPort;
	
	m_strNatCfg.struCmdPort.wEnable = m_bEnableAdmin;
	m_strNatCfg.struCmdPort.wExtPort = m_iAdminPort;
	
	m_strNatCfg.struRtspPort.wEnable = m_bEnableRtsp;
	m_strNatCfg.struRtspPort.wExtPort = m_iRtspPort;

	m_strNatCfg.struHttpsPort.wEnable = m_bEnableHttps;
	m_strNatCfg.struHttpsPort.wExtPort = m_iHttpsPort;

    m_strNatCfg.struSDKOverTLSPort.wEnable = m_bSdkOverTlsEnable;
    m_strNatCfg.struSDKOverTLSPort.wExtPort = m_iSdkOverTlsPort;

	m_strNatCfg.byNatType = m_comboNatType.GetCurSel();
	memcpy(m_strNatCfg.byFriendName,m_csFriendName,64);

	if(!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_NAT_CFG, 0xff, &m_strNatCfg, sizeof(m_strNatCfg)))
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_NAT_CFG");
		CString cs;
		cs.Format("NET_DVR_SET_UPNP_CFG failed!Error[%d]", NET_DVR_GetLastError());
		AfxMessageBox(cs);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_UPNP_CFG");
	}
}

void CDlgUpnpCfg::OnButtonUpdateState() 
{
	NET_DVR_UPNP_NAT_STATE strState = {0};
	CString csTemp;

	if(!NET_DVR_GetUpnpNatState(m_lUserID, &strState))
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetUpnpNatState");
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetUpnpNatState");
        for (int i = 0; i < UPNP_PORT_NUM; i++)
		{
			csTemp = (strState.strUpnpPort[i].dwEnabled == 0)?"N":"Y";
			m_listState.SetItemText(i, 1, csTemp);
	
			csTemp.Format("%d", strState.strUpnpPort[i].wInternalPort);
			m_listState.SetItemText(i, 2, csTemp);	
			
			csTemp.Format("%d", strState.strUpnpPort[i].wExternalPort);
			m_listState.SetItemText(i, 3, csTemp);	
			 
			switch(strState.strUpnpPort[i].dwStatus)
			{
			case 0:
			csTemp = "Invalid";
			break;
			case 1:
			csTemp = "Invalid:src port = dst port";
			break;		
			case 2:
			csTemp = "Invalid:src port is used";
			break;	
			case 3:
			csTemp = "Valid";
			break;
			default:
				csTemp = "Unkonw state";
				break;
			}		
			m_listState.SetItemText(i, 4, csTemp);	
		
			m_listState.SetItemText(i, 5, strState.strUpnpPort[i].struNatExternalIp.sIpV4);	
			
			m_listState.SetItemText(i, 6, strState.strUpnpPort[i].struNatInternalIp.sIpV4);		
		}
	}	
}

void CDlgUpnpCfg::OnButtonGetPoe()
{
	ZeroMemory(&m_strPoeCfg, sizeof(m_strPoeCfg));
	DWORD dwReturned = 0;
	if(!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_POE_CFG, -1, &m_strPoeCfg, sizeof(m_strPoeCfg), &dwReturned))
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_POE_CFG");
	}
	else
	{
		m_csPoeIP.Format("%s", m_strPoeCfg.struIP.sIpV4);
		UpdateData(FALSE);
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_POE_CFG");
	}
}

void CDlgUpnpCfg::OnButtonSetPoe()
{
	UpdateData(TRUE);
	sprintf(m_strPoeCfg.struIP.sIpV4, "%s", m_csPoeIP);
	if(!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_POE_CFG, -1, &m_strPoeCfg, sizeof(m_strPoeCfg)))
	{
		CString cs;
		cs.Format("NET_DVR_SET_POE_CFG failed!Error[%d]", NET_DVR_GetLastError());
		AfxMessageBox(cs);
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_POE_CFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_POE_CFG");
	}
}

void  CDlgUpnpCfg::OnButtonExit()
{
	CDialog::OnCancel();
}
