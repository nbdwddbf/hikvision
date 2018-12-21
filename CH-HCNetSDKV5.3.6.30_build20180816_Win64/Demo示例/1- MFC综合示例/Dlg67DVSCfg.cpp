// Dlg67DVSCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "Dlg67DVSCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg67DVSCfg dialog


CDlg67DVSCfg::CDlg67DVSCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg67DVSCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg67DVSCfg)
	m_bBonjour = FALSE;
	m_bHttps = FALSE;
	m_bSocks = FALSE;
	m_strFriendName = _T("");
	m_strHostName = _T("");
	m_strLocalAddress = _T("");
	m_strPassword = _T("");
	m_strProxyIP = _T("");
	m_strUserName = _T("");
	m_byVersion = 0;
	m_dwManageDscp = 0;
	m_dwAlarmDscp = 0;
	m_dwAudioDscp = 0;
	m_dwVideoDscp = 0;
	m_bQosEnable = FALSE;
	m_wHttpsPort = 0;
	m_wProxyPort = 0;
	//}}AFX_DATA_INIT
}


void CDlg67DVSCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg67DVSCfg)
	DDX_Control(pDX, IDC_COMBO_FLAG, m_cmbFlag);
	DDX_Check(pDX, IDC_CHECK_BONJOUR, m_bBonjour);
	DDX_Check(pDX, IDC_CHECK_HTTPS, m_bHttps);
	DDX_Check(pDX, IDC_CHECK_SOCKS, m_bSocks);
	DDX_Text(pDX, IDC_EDIT_FRIEND_NAME, m_strFriendName);
	DDX_Text(pDX, IDC_EDIT_HOST_NAME, m_strHostName);
	DDX_Text(pDX, IDC_EDIT_LOCAL_ADDRESS, m_strLocalAddress);
	DDX_Text(pDX, IDC_EDIT_PASSWD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_PROXY_IP, m_strProxyIP);
	DDX_Text(pDX, IDC_EDIT_HTTPS_PORT, m_wHttpsPort);
	DDX_Text(pDX, IDC_EDIT_PROXY_PORT, m_wProxyPort);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_strUserName);
	DDX_Text(pDX, IDC_EDIT_VERSION, m_byVersion);
	DDX_Text(pDX, IDC_EDIT_MANAGE_DSCP, m_dwManageDscp);
	DDX_Text(pDX, IDC_EDIT_ALARM_DSCP, m_dwAlarmDscp);
	DDX_Text(pDX, IDC_EDIT_AUDIO_DSCP, m_dwAudioDscp);
	DDX_Text(pDX, IDC_EDIT_VIDEO_DSCP, m_dwVideoDscp);
	DDX_Check(pDX, IDC_CHECK_QOS, m_bQosEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg67DVSCfg, CDialog)
	//{{AFX_MSG_MAP(CDlg67DVSCfg)
	ON_BN_CLICKED(IDC_BUTTON_BONJOUR_GET, OnButtonBonjourGet)
	ON_BN_CLICKED(IDC_BUTTON_BONJOUR_SET, OnButtonBonjourSet)
	ON_BN_CLICKED(IDC_BUTTON_SOCKS_GET, OnButtonSocksGet)
	ON_BN_CLICKED(IDC_BUTTON_SOCKS_SET, OnButtonSocksSet)
	ON_BN_CLICKED(IDC_BUTTON_QOS_GET, OnButtonQosGet)
	ON_BN_CLICKED(IDC_BUTTON_QOS_SET, OnButtonQosSet)
	ON_BN_CLICKED(IDC_BUTTON_HTTPS_GET, OnButtonHttpsGet)
	ON_BN_CLICKED(IDC_BUTTON_HTTPS_SET, OnButtonHttpsSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg67DVSCfg message handlers

void CDlg67DVSCfg::OnButtonBonjourGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturned = 0;
	NET_DVR_BONJOUR_CFG struBonjourInfo;
	memset(&struBonjourInfo, 0, sizeof(NET_DVR_BONJOUR_CFG));
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_BONJOUR_CFG, 0, &struBonjourInfo, sizeof(NET_DVR_BONJOUR_CFG), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_BONJOUR_CFG");
		AfxMessageBox("NET_DVR_GET_BONJOUR_CFG failed");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_BONJOUR_CFG");
	}

	m_bBonjour = struBonjourInfo.byEnableBonjour;
	m_strFriendName.Format("%s", struBonjourInfo.byFriendlyName);

	UpdateData(FALSE);
	
}

BOOL CDlg67DVSCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cmbFlag.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg67DVSCfg::OnButtonBonjourSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_BONJOUR_CFG struBonjourInfo;
	memset(&struBonjourInfo, 0, sizeof(NET_DVR_BONJOUR_CFG));
	struBonjourInfo.dwSize = sizeof(NET_DVR_BONJOUR_CFG);
	struBonjourInfo.byEnableBonjour = m_bBonjour;
	strcpy((char*)struBonjourInfo.byFriendlyName, m_strFriendName);
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_BONJOUR_CFG, 0, &(struBonjourInfo), sizeof(NET_DVR_BONJOUR_CFG)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_BONJOUR_CFG");
		AfxMessageBox("NET_DVR_SET_BONJOUR_CFG failed");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_BONJOUR_CFG");
	}
}

void CDlg67DVSCfg::OnButtonSocksGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturned = 0;
	NET_DVR_SOCKS_CFG struSocksInfo;
	memset(&struSocksInfo, 0, sizeof(NET_DVR_SOCKS_CFG));
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_SOCKS_CFG, 0, &struSocksInfo, sizeof(NET_DVR_SOCKS_CFG), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SOCKS_CFG");
		AfxMessageBox("NET_DVR_GET_SOCKS_CFG failed");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SOCKS_CFG");
	}

	m_strLocalAddress.Format("%s", struSocksInfo.byLocalAddr);
	m_bSocks = struSocksInfo.byEnableSocks;
	m_byVersion = struSocksInfo.byVersion;
	m_wProxyPort = struSocksInfo.wProxyPort;
	m_strProxyIP.Format("%s", struSocksInfo.byProxyaddr);
	m_strUserName.Format("%s", struSocksInfo.byUserName);
	m_strPassword.Format("%s", struSocksInfo.byPassword);

	UpdateData(FALSE);
}

void CDlg67DVSCfg::OnButtonSocksSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_SOCKS_CFG struSocksInfo;
	memset(&struSocksInfo, 0, sizeof(NET_DVR_SOCKS_CFG));
	if (m_strLocalAddress.GetLength() > 96)
	{
		AfxMessageBox("Local address len is big than 96");
		return;
	}

	strncpy((char*)struSocksInfo.byLocalAddr, m_strLocalAddress, m_strLocalAddress.GetLength());
	struSocksInfo.byEnableSocks = m_bSocks;
	struSocksInfo.byVersion = m_byVersion;
	struSocksInfo.wProxyPort = m_wProxyPort;
	strcpy((char*)struSocksInfo.byProxyaddr, m_strProxyIP);
	strcpy((char*)struSocksInfo.byUserName, m_strUserName);
	strcpy((char*)struSocksInfo.byPassword, m_strPassword);
	
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_SOCKS_CFG, 0, &(struSocksInfo), sizeof(NET_DVR_SOCKS_CFG)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SOCKS_CFG");
		AfxMessageBox("NET_DVR_SET_SOCKS_CFG failed");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SOCKS_CFG");
	}
}

void CDlg67DVSCfg::OnButtonQosGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturned = 0;
	NET_DVR_QOS_CFG struQosInfo;
	memset(&struQosInfo, 0, sizeof(NET_DVR_QOS_CFG));

	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_QOS_CFG, NULL, &struQosInfo, sizeof(NET_DVR_QOS_CFG), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_QOS_CFG");
		AfxMessageBox("NET_DVR_GET_QOS_CFG failed");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_QOS_CFG");
	}

	m_bQosEnable = struQosInfo.byEnable;
	m_cmbFlag.SetCurSel(struQosInfo.byFlag);
	m_dwAlarmDscp = struQosInfo.byAlarmDscp;
	m_dwAudioDscp = struQosInfo.byAudioDscp;
	m_dwManageDscp = struQosInfo.byManageDscp;
	m_dwVideoDscp = struQosInfo.byVideoDscp;
	UpdateData(FALSE);
	
}

void CDlg67DVSCfg::OnButtonQosSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_QOS_CFG struQosInfo;
	memset(&struQosInfo, 0, sizeof(NET_DVR_QOS_CFG));

	struQosInfo.dwSize = sizeof(NET_DVR_QOS_CFG);
	struQosInfo.byEnable = m_bQosEnable;
	struQosInfo.byFlag = m_cmbFlag.GetCurSel();
	struQosInfo.byAlarmDscp = m_dwAlarmDscp;
	struQosInfo.byAudioDscp = m_dwAudioDscp;
	struQosInfo.byManageDscp = m_dwManageDscp;
	struQosInfo.byVideoDscp = m_dwVideoDscp;

	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_QOS_CFG, 0, &(struQosInfo), sizeof(NET_DVR_QOS_CFG)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_QOS_CFG");
		AfxMessageBox("NET_DVR_SET_QOS_CFG failed");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_QOS_CFG");
	}
	
}

void CDlg67DVSCfg::OnButtonHttpsGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturned = 0;
	NET_DVR_HTTPS_CFG struHttpsInfo;
	memset(&struHttpsInfo, 0, sizeof(NET_DVR_HTTPS_CFG));

	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_HTTPS_CFG, 0, &struHttpsInfo, sizeof(NET_DVR_HTTPS_CFG), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_HTTPS_CFG");
		AfxMessageBox("NET_DVR_GET_HTTPS_CFG failed");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_HTTPS_CFG");
	}

	m_bHttps = struHttpsInfo.byEnable;
	m_wHttpsPort = struHttpsInfo.wHttpsPort;
	UpdateData(FALSE);
	
}

void CDlg67DVSCfg::OnButtonHttpsSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_HTTPS_CFG struHttpsInfo;
	memset(&struHttpsInfo, 0, sizeof(NET_DVR_HTTPS_CFG));

	struHttpsInfo.dwSize = sizeof(NET_DVR_HTTPS_CFG);
	struHttpsInfo.byEnable = m_bHttps;
	struHttpsInfo.wHttpsPort = m_wHttpsPort;

	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_HTTPS_CFG, 0, &(struHttpsInfo), sizeof(NET_DVR_HTTPS_CFG)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_HTTPS_CFG");
		AfxMessageBox("NET_DVR_SET_HTTPS_CFG failed");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_HTTPS_CFG");
	}
}
