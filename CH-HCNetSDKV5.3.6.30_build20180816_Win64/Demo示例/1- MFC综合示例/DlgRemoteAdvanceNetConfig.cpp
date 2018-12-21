/**********************************************************
FileName:    DlgRemoteAdvanceNetConfig.cpp
Description: Advanced Network Config     
Date:        2008/05/29
Note: 		<global>struct, pleasse refer to GeneralDef.h for macro definition,  and ClientDemo.cpp for API and global variants   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/29>       <created>
***********************************************************/

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgRemoteAdvanceNetConfig.h"
#include "DlgRemoteEmailAddReceiver.h"
#include ".\dlgremoteadvancenetconfig.h"
#include "DlgSnmpCfg.h"

// CDlgRemoteAdvanceNetConfig dialog
extern BOOL CheckEmailAddress(CString csEmailAddr);
CDlgRemoteAdvanceNetConfig *g_pRemoteAdvaceNetConfig = NULL;

/*********************************************************
Function:	CDlgRemoteAdvanceNetConfig
Desc:		Constructor
Input:	
Output:	
Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgRemoteAdvanceNetConfig, CDialog)
CDlgRemoteAdvanceNetConfig::CDlgRemoteAdvanceNetConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteAdvanceNetConfig::IDD, pParent)
	, m_csSenderName(_T(""))
	, m_csSenderAddr(_T(""))
	, m_csAccountPwd(_T(""))
	, m_csAccountPwdConfirm(_T(""))
	, m_csAccount(_T(""))
	, m_bChkAuthen(FALSE)
	, m_bChkAttach(FALSE)
	, m_csDnsIP(_T(""))
	, m_bChkNtp(FALSE)
	, m_csNtpAddr(_T(""))
	, m_iNtpInterval(0)
	, m_iNTPInterHour(0)
	, m_iNTPInterMin(0)
	, m_bChkDdns(FALSE)
	, m_csDDNSAddr(_T(""))
	, m_csDDNSUserName(_T(""))
	, m_csDDNSPwd(_T(""))
	, m_csDDNSPwdConfirm(_T(""))
	, m_bChkEnablePPPoE(FALSE)
	, m_csPPPoEUserName(_T(""))
	, m_csPPPoEPwd(_T(""))
	, m_csPPPoEIP(_T(""))
	, m_csSmtpSvrAddr(_T(""))
	, m_csPop3SvrAddr(_T(""))
	, m_uDDNSPort(0)
	, m_iDeviceIndex(0)
	, m_uNtpPort(0)
	, m_wSmtpPort(0)
    , m_lEmailTestHandle(-1)
	, m_lNtpTestHandle(-1)
	, m_lEmailTestWithParaHandle(-1)
{
	memset(&m_struNTPPara, 0, sizeof(NET_DVR_NTPPARA));
	memset(&m_struDDNSPara, 0, sizeof(NET_DVR_DDNSPARA));
	memset(&m_struDDNSParaEx, 0, sizeof(NET_DVR_DDNSPARA_EX));
	memset(&m_struEmailCfg, 0, sizeof(NET_DVR_EMAILCFG_V30));
	memset(&m_struServerTestPara, 0, sizeof(NET_DVR_SERVER_TEST_PARA));
}

/*********************************************************
Function:	~CDlgRemoteAdvanceNetConfig
Desc:		destructor
Input:	
Output:	
Return:	
**********************************************************/
CDlgRemoteAdvanceNetConfig::~CDlgRemoteAdvanceNetConfig()
{
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteAdvanceNetConfig::DoDataExchange(CDataExchange* pDX)
{

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteAdvanceNetConfig)
	DDX_Control(pDX, IDC_COMBO_DDNS_STATUS, m_cmbDDNSStatus);
	DDX_Control(pDX, IDC_COMBO_ENCRYPT_TYPE, m_comboEncryptType);
	DDX_Control(pDX, IDC_COMBO_DDNS_TYPE, m_comboDDNSType);
	DDX_Text(pDX, IDC_EDIT_EMAIL_SEND_NAME, m_csSenderName);
	DDX_Text(pDX, IDC_EDIT_EMAIL_SENDER_ADDR, m_csSenderAddr);
	DDX_Text(pDX, IDC_EDIT_EMAIL_PWD, m_csAccountPwd);
	DDX_Text(pDX, IDC_EDIT_EMAIL_PWD_CONFIRM, m_csAccountPwdConfirm);
	DDX_Text(pDX, IDC_EDIT_EMAIL_ACCOUNT, m_csAccount);
	DDX_Check(pDX, IDC_CHK_AUTHEN, m_bChkAuthen);
	DDX_Check(pDX, IDC_CHK_ATTACH, m_bChkAttach);
	DDX_Control(pDX, IDC_COMBO_EMAIL_INTERVAL, m_comboSendInterval);
	DDX_Check(pDX, IDC_CHK_USE_NTP, m_bChkNtp);
	DDX_Text(pDX, IDC_EDIT_NTP_ADDR, m_csNtpAddr);
	DDX_Text(pDX, IDC_EDIT_NTP_INTERVAL, m_iNtpInterval);
	DDX_Text(pDX, IDC_EDIT_NTP_INTERVAL_HOUR, m_iNTPInterHour);
	DDX_Text(pDX, IDC_EDIT_NTP_INTERVAL_MIN, m_iNTPInterMin);
	DDX_Check(pDX, IDC_CHK_DDNS, m_bChkDdns);
	DDX_Text(pDX, IDC_EDIT_DDNS_ADDR, m_csDDNSAddr);
	DDX_Text(pDX, IDC_EDIT_DDNS_USER_NAME, m_csDDNSUserName);
	DDX_Text(pDX, IDC_EDIT_DDNS_PWD, m_csDDNSPwd);
	DDX_Text(pDX, IDC_EDIT_DDNS_PWD_CONFIRM, m_csDDNSPwdConfirm);
	DDX_Control(pDX, IDC_LIST_RECEIVER, m_listEmailReceiver);
	DDX_Text(pDX, IDC_EDIT_PPPOE_NAME, m_csPPPoEUserName);
	DDX_Text(pDX, IDC_EDIT_PPPOE_PWD, m_csPPPoEPwd);
	DDX_Text(pDX, IDC_EDIT_PPPOE_VERI_PWD, m_csPPPoEVeriPwd);
	DDX_Text(pDX, IDC_SUB_PPPOEIP, m_csPPPoEIP);
	DDX_Text(pDX, IDC_EDIT_SMTP_SVR_ADDR, m_csSmtpSvrAddr);
	DDX_Text(pDX, IDC_EDIT_POP3_SVR_ADDR, m_csPop3SvrAddr);
	DDX_Text(pDX, IDC_DDNS_PORT, m_uDDNSPort);
	DDX_Text(pDX, IDC_DEV_DOMAIN, m_csDevDomain);
	DDX_Text(pDX, IDC_EDIT_NTP_PORT, m_uNtpPort);
	DDX_Text(pDX, IDC_EDIT_SMTP_PORT, m_wSmtpPort);
	DDX_Text(pDX, IDC_EDIT_COUNTRYID, m_wCountrtID);
	DDX_Check(pDX, IDC_CHK_ENABLE_PPPOE, m_bChkEnablePPPoE);
	DDX_Check(pDX, IDC_CHECK_START_TLS, m_bChkStartTLS);
	//}}AFX_DATA_MAP
}


/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgRemoteAdvanceNetConfig, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteAdvanceNetConfig)	
	ON_BN_CLICKED(IDC_CHK_ENABLE_PPPOE, OnBnClickedChkEnablePppoe)
	ON_BN_CLICKED(IDC_BTN_PPPOE_OK, OnBnClickedBtnPppoeOk)
	ON_BN_CLICKED(IDC_BTN_NTP_OK, OnBnClickedBtnNtpOk)
	ON_BN_CLICKED(IDC_BTN_DDNS_OK, OnBnClickedBtnDdnsOk)
	ON_BN_CLICKED(IDC_BTN_EMAILE_OK, OnBnClickedBtnEmaileOk)
	ON_BN_CLICKED(IDC_BTN_ADD_RECEIVER, OnBnClickedBtnAddReceiver)
	ON_BN_CLICKED(IDC_BTN_DEL_RECEIVER, OnBnClickedBtnDelReceiver)
	ON_BN_CLICKED(IDC_CHK_USE_NTP, OnBnClickedChkUseNtp)
	ON_BN_CLICKED(IDC_CHK_DDNS, OnBnClickedChkDdns)
	ON_BN_CLICKED(IDC_BTN_HIGH_NET_CONFIG_OK, OnBnClickedBtnHighNetConfigOk)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_CBN_SELCHANGE(IDC_COMBO_DDNS_TYPE, OnSelchangeComboDdnsType)
	ON_BN_CLICKED(IDC_BTN_TEST, OnBtnTest)
	ON_BN_CLICKED(IDC_BTN_SNMP_CFG, OnBtnSnmpCfg)
	ON_BN_CLICKED(IDC_BTN_NTP_SERVER_TEST, OnBtnNtpServerTest)
	ON_BN_CLICKED(IDC_BTN_EMAIL_SERVER_TEST_WITH_PARAM, OnBtnEmailServerTestWithParam)
	//}}AFX_MSG_MAP
	
END_MESSAGE_MAP()


// CDlgRemoteAdvanceNetConfig message handlers
/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgRemoteAdvanceNetConfig::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString sTemp;
	DWORD dwReturned;
	CString csToName;
	CString csToAddr;
	unsigned int i = 0;
	char csPPPoeName[NAME_LEN+1] = {0};
	char csPPPoEPwd[PASSWD_LEN+1] = {0};
	char szLan[65] = {0};

    g_pRemoteAdvaceNetConfig = this;
	AddStatusList();
	m_bChkEnablePPPoE = m_pPPPoECfg->dwPPPOE;
	EnablePPPOEItem(m_bChkEnablePPPoE);
	if (m_bChkEnablePPPoE)
	{
		memcpy(csPPPoeName, m_pPPPoECfg->sPPPoEUser, NAME_LEN);
		m_csPPPoEUserName.Format("%s", csPPPoeName);
		memcpy(csPPPoEPwd, m_pPPPoECfg->sPPPoEPassword, PASSWD_LEN);
		m_csPPPoEPwd.Format("%s", csPPPoEPwd);
		m_csPPPoEVeriPwd.Format("%s",csPPPoEPwd);
		m_csPPPoEIP.Format("%s", m_pPPPoECfg->struPPPoEIP.sIpV4);
	}

	memset(&m_struNTPPara, 0, sizeof(NET_DVR_NTPPARA));
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_NTPCFG, 0, &m_struNTPPara, sizeof(NET_DVR_NTPPARA), &dwReturned))
	{
		GetDlgItem(IDC_CHK_USE_NTP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_NTP_OK)->EnableWindow(FALSE);
		EnableNTPItem(FALSE);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_NTPCFG");	
		m_bNTPGet = FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_NTPCFG");
		m_bChkNtp = m_struNTPPara.byEnableNTP;
		EnableNTPItem(m_bChkNtp);
		if (m_bChkNtp)
		{
			//m_csNtpAddr.Format("%s", m_struNTPPara.sNTPServer);
			memcpy(szLan, m_struNTPPara.sNTPServer, 64);
			m_csNtpAddr.Format("%s", szLan);
			m_iNtpInterval = m_struNTPPara.wInterval;
			m_iNTPInterHour = m_struNTPPara.cTimeDifferenceH;
			m_iNTPInterMin = m_struNTPPara.cTimeDifferenceM;
			m_uNtpPort = m_struNTPPara.wNtpPort;
		}
		m_bNTPGet = TRUE;
	}
	memset(&m_struDDNSPara, 0, sizeof(NET_DVR_GET_DDNSCFG_V30));
	memset(&m_struDDNSParaEx, 0, sizeof(NET_DVR_GET_DDNSCFG_EX));

	if (DS_19AXX == g_struDeviceInfo[m_iDeviceIndex].iDeviceType)
	{ 
		if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_DDNSCFG_EX, 0, &m_struDDNSParaEx, sizeof(NET_DVR_DDNSPARA_EX), &dwReturned))
		{
			GetDlgItem(IDC_CHK_DDNS)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_DDNS_OK)->EnableWindow(FALSE);	
			m_bChkDdns = FALSE;
			m_uDDNSPort = 0;
			SwitchDDNSCtrlStat(-1);
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_DDNSCFG_EX");
			m_bDDNSGet = FALSE;
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_DDNSCFG_EX");
			GetDlgItem(IDC_CHK_DDNS)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_DDNS_OK)->EnableWindow(TRUE);
			m_bChkDdns = m_struDDNSParaEx.byEnableDDNS;
			m_comboDDNSType.ResetContent();
			m_comboDDNSType.AddString("IPServer");
			m_comboDDNSType.AddString("DynDNS");
			m_comboDDNSType.AddString("PeanutHull");
			m_comboDDNSType.AddString("NO-IP");
			m_comboDDNSType.AddString("hiDDNS");
			m_comboDDNSType.SetCurSel(m_struDDNSParaEx.byHostIndex);
			SwitchDDNSCtrlStat(m_struDDNSParaEx.byHostIndex);
			m_bDDNSGet = TRUE;
		}
	} 
	else
	{
		if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_DDNSCFG_V30, 0, &m_struDDNSPara, sizeof(NET_DVR_DDNSPARA_V30), &dwReturned))
		{
			GetDlgItem(IDC_CHK_DDNS)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_DDNS_OK)->EnableWindow(FALSE);	
			m_bChkDdns = FALSE;
			m_uDDNSPort = 0;
			SwitchDDNSCtrlStat(-1);
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_DDNSCFG_V30");
			m_bDDNSGet = FALSE;
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_DDNSCFG_V30");
			GetDlgItem(IDC_CHK_DDNS)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_DDNS_OK)->EnableWindow(TRUE);
			m_bChkDdns = m_struDDNSPara.byEnableDDNS;
			m_comboDDNSType.ResetContent();
			m_comboDDNSType.AddString("IPServer");
			m_comboDDNSType.AddString("DynDNS");
			m_comboDDNSType.AddString("PeanutHull");
			m_comboDDNSType.AddString("NO-IP");
			m_comboDDNSType.AddString("hiDDNS");
			m_comboDDNSType.SetCurSel(m_struDDNSPara.byHostIndex);
			SwitchDDNSCtrlStat(m_struDDNSPara.byHostIndex);
			m_bDDNSGet = TRUE;
		}
	}
	

	memset(&m_struEmailCfg, 0, sizeof(NET_DVR_EMAILCFG_V30));
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_EMAILCFG_V30, 0, &m_struEmailCfg, sizeof(NET_DVR_EMAILCFG_V30), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_EMAILCFG_V30");
		GetDlgItem(IDC_LIST_RECEIVER)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_EMAIL_INTERVAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_ATTACH)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_AUTHEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_EMAIL_ACCOUNT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_EMAIL_PWD_CONFIRM)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_EMAIL_PWD)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_EMAIL_SENDER_ADDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_EMAIL_SEND_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_EMAIL_SENDER_ADDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_ADD_RECEIVER)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_POP3_SVR_ADDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SMTP_SVR_ADDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_DEL_RECEIVER)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_EMAILE_OK)->EnableWindow(FALSE);
		m_bEmailGet = FALSE;
	}
	else
	{
		char szLan[128] = {0};
		char szName[33] = {0};
		char szRecPswd[49] = {0};
		char szAddress[49] = {0};
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_EMAILCFG_V30");
		m_comboSendInterval.SetCurSel(m_struEmailCfg.byMailInterval);
		m_listEmailReceiver.SetExtendedStyle(m_listEmailReceiver.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		g_StringLanType(szLan, "接收方姓名", "Receiver Name");
		m_listEmailReceiver.InsertColumn(0, szLan, LVCFMT_LEFT, 90, -1);
		g_StringLanType(szLan, "接收方Email地址", "Recevier Email address");
		m_listEmailReceiver.InsertColumn(1, szLan, LVCFMT_LEFT, 200, -1);
		memcpy(szName, m_struEmailCfg.struSender.sName, 32);
		m_csSenderName.Format("%s", szName);
		memcpy(szAddress,m_struEmailCfg.struSender.sAddress,48);
		m_csSenderAddr.Format("%s", szAddress);
		memset(szName, 0, 33);
		memcpy(szName,m_struEmailCfg.sAccount,32);
		m_csAccount.Format("%s", szName);
		if (!m_csAccount.IsEmpty())
		{
			memset(szName,0,33);
			memcpy(szName, m_struEmailCfg.sPassword,32);
			m_csAccountPwd.Format("%s", szName);
			m_csAccountPwdConfirm = m_csAccountPwd;
		}

		for (i = 0; i < 3; i++)
		{
			memset(szName,0,33);
			memcpy(szName, m_struEmailCfg.struReceiver[i].sName,32);
			memset(szAddress,0,49);
			memcpy(szAddress,m_struEmailCfg.struReceiver[i].sAddress,48);
			csToName.Format("%s", szName);
			csToAddr.Format("%s", szAddress);
			if (!csToName.IsEmpty())
			{
				int iIndex = m_listEmailReceiver.InsertItem(m_listEmailReceiver.GetItemCount(), csToName);
				m_listEmailReceiver.SetItemText(iIndex, 1, csToAddr);
			}
		}

		m_bChkAuthen = m_struEmailCfg.bySmtpServerVerify;
		if (m_bChkAuthen != TRUE)
		{
			m_bChkAuthen = FALSE;
		}
		m_bChkAttach = m_struEmailCfg.byAttachment;
		if (m_bChkAttach != TRUE)
		{
			m_bChkAttach = FALSE;
		}
		//m_comboSendInterval.SetCurSel(m_struEmailCfg.byMailinterval);
		memset(szAddress,0,49);
		memcpy(szAddress, m_struEmailCfg.sSmtpServer,48);
		m_csSmtpSvrAddr.Format("%s",szAddress);
		//m_csPop3SvrAddr.Format("%s", m_struEmailCfg.sPop3Server);
		if (m_struEmailCfg.byEnableSSL == 1)
		{
			m_comboEncryptType.SetCurSel(1);
		}
		else if (m_struEmailCfg.byEnableTLS == 1)
		{
			m_comboEncryptType.SetCurSel(2);
		}
		else
		{
			m_comboEncryptType.SetCurSel(0);
		}

		m_wSmtpPort = m_struEmailCfg.wSmtpPort;
		m_bChkStartTLS = m_struEmailCfg.byStartTLS;
		m_bEmailGet = TRUE;
	}

	UpdateData(FALSE);
	return TRUE;  
}

/*********************************************************
Function:	OnBnClickedBtnAddReceiver
Desc:		add email receiver info
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteAdvanceNetConfig::OnBnClickedBtnAddReceiver()
{
	char szLan[128] = {0};
	if (m_listEmailReceiver.GetItemCount() >= 3)
	{
		g_StringLanType(szLan, "目前只支持3个接收端!", "Now only suppert 3 receviers!");
		AfxMessageBox(szLan);
		return;
	}
	CDlgRemoteEmailAddReceiver dlgEmail;
	if (IDOK == dlgEmail.DoModal())
	{
		int iIndex = m_listEmailReceiver.InsertItem(m_listEmailReceiver.GetItemCount(), dlgEmail.m_csReceiverName);
		m_listEmailReceiver.SetItemText(iIndex, 1, dlgEmail.m_csReceiverAddr);
	}
}

/*********************************************************
Function:	OnBnClickedBtnDelReceiver
Desc:		delete email receiver info
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteAdvanceNetConfig::OnBnClickedBtnDelReceiver()
{
	POSITION iPos = m_listEmailReceiver.GetFirstSelectedItemPosition();
	int iIndex = m_listEmailReceiver.GetNextSelectedItem(iPos);
	if (iIndex < 0)
	{
		return;
	}
	m_listEmailReceiver.DeleteItem(iIndex);
}

/*********************************************************
Function:	OnBnClickedChkUseNtp
Desc:		update Ntp control status
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteAdvanceNetConfig::OnBnClickedChkUseNtp()
{
	UpdateData(TRUE);
	EnableNTPItem(m_bChkNtp);
}

/*********************************************************
Function:	OnBnClickedChkDdns
Desc:		update ddns control status
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteAdvanceNetConfig::OnBnClickedChkDdns()
{
	UpdateData(TRUE);
	SwitchDDNSCtrlStat(m_comboDDNSType.GetCurSel());
	UpdateData(FALSE);
}

/*********************************************************
Function:	OnBnClickedBtnHighNetConfigOk
Desc:		set advanced network configuration
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteAdvanceNetConfig::OnBnClickedBtnHighNetConfigOk()
{
	UpdateData(TRUE);

	CString sTemp;
	BOOL error = FALSE;
	char szLan[128] = {0};
	if (m_bNTPGet)
	{
		if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_NTPCFG, 0, &m_struNTPPara, sizeof(NET_DVR_NTPPARA)))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_NTPCFG"); 
			g_StringLanType(szLan, "NTP参数保存失败!", "NTP configure error!");
			AfxMessageBox(szLan);		
			error = TRUE;
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_NTPCFG");
		}
	}

	if (m_bDDNSGet)
	{
		if (DS_19AXX == g_struDeviceInfo[m_iDeviceIndex].iDeviceType)
		{
			if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_DDNSCFG_EX, 0, &m_struDDNSParaEx, sizeof(NET_DVR_DDNSPARA_EX)))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_DDNSCFG_EX"); 
				g_StringLanType(szLan, "DDNS参数保存失败!", "DDNS configure save error!");
				AfxMessageBox(szLan);	
				error = TRUE;
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_DDNSCFG_EX"); 
			}
		} 
		else
		{
			if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_DDNSCFG_V30, 0, &m_struDDNSPara, sizeof(NET_DVR_DDNSPARA_V30)))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_DDNSCFG_V30"); 
				g_StringLanType(szLan, "DDNS参数保存失败!", "DDNS configure save error!");
				AfxMessageBox(szLan);	
				error = TRUE;
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_DDNSCFG_V30"); 
			}
		}	
	}

	if (m_bEmailGet)
	{
		if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_EMAILCFG_V30, 0, &m_struEmailCfg, sizeof(NET_DVR_EMAILCFG_V30)))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_EMAILCFG_V30"); 
			g_StringLanType(szLan, "Email参数保存失败!", "Email configure save error!");
			AfxMessageBox(szLan);	
			error = TRUE;
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_EMAILCFG_V30");
		}
	}

	if (!error)
	{
		g_StringLanType(szLan, "参数保存成功!", "save successfully!");
		AfxMessageBox(szLan);
	}
}

/*********************************************************
Function:	EnableNTPItem
Desc:		enable ntp
Input:	
Output:	
Return:		TRUE,enable;FALSE,disable
**********************************************************/
void CDlgRemoteAdvanceNetConfig::EnableNTPItem(BOOL bEnable)
{
	GetDlgItem(IDC_EDIT_NTP_ADDR)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_NTP_INTERVAL)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_NTP_INTERVAL_HOUR)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_NTP_INTERVAL_MIN)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_NTP_PORT)->EnableWindow(bEnable);
	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnBnClickedChkEnablePppoe
  Desc:		enable/disable pppoe
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteAdvanceNetConfig::OnBnClickedChkEnablePppoe()
{
	UpdateData(TRUE);
	EnablePPPOEItem(m_bChkEnablePPPoE);
}

/*********************************************************
Function:	EnablePPPOEItem
Desc:		pppoe status
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteAdvanceNetConfig::EnablePPPOEItem(BOOL bFlag)
{
	GetDlgItem(IDC_EDIT_PPPOE_NAME)->EnableWindow(bFlag);
	GetDlgItem(IDC_EDIT_PPPOE_PWD)->EnableWindow(bFlag);
	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnBnClickedBtnPppoeOk
  Desc:		get PPPoe status
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteAdvanceNetConfig::OnBnClickedBtnPppoeOk()
{
	UpdateData(TRUE);
	char szLan[128] = {0};
	if(m_csPPPoEPwd != m_csPPPoEVeriPwd)
	{
		g_StringLanType(szLan, "密码与确认密码不一致!", "Password and Confirm Password inconsistent!");
		AfxMessageBox(szLan);
		return;
	}
	m_pPPPoECfg->dwPPPOE = m_bChkEnablePPPoE;
	if (m_bChkEnablePPPoE)
	{
		memcpy(m_pPPPoECfg->sPPPoEUser, m_csPPPoEUserName, NAME_LEN);
		memcpy(m_pPPPoECfg->sPPPoEPassword, m_csPPPoEPwd, PASSWD_LEN);
		memcpy(m_pPPPoECfg->struPPPoEIP.sIpV4, m_csPPPoEIP, 16);
	}
	//should set pppoe by netcfg_v30
	g_pMainDlg->m_dlgRemoteCfg->m_subDlgDeviceCfg.CfgSetup();
}

/*********************************************************
Function:	OnBnClickedBtnNtpOk
Desc:		get ntp status
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteAdvanceNetConfig::OnBnClickedBtnNtpOk()
{
	UpdateData(TRUE);
	char szLan[128] = {0};
	if (m_iNTPInterHour < -12 || m_iNTPInterHour > 13 || m_iNTPInterMin < 0 || m_iNTPInterMin >59)
	{
		g_StringLanType(szLan, "时差输入有误!", "Time Zone Error!");
		AfxMessageBox(szLan);
		return;
	}

	m_struNTPPara.byEnableNTP = (BYTE)m_bChkNtp;
	if (m_bChkNtp)
	{
		memcpy(m_struNTPPara.sNTPServer, m_csNtpAddr, MAX_DOMAIN_NAME);
		m_struNTPPara.wInterval = m_iNtpInterval;
		m_struNTPPara.cTimeDifferenceH = (char)m_iNTPInterHour;
		m_struNTPPara.cTimeDifferenceM = (char)m_iNTPInterMin;
		m_struNTPPara.wNtpPort = (WORD)m_uNtpPort;
	}
}

/*********************************************************
Function:	OnBnClickedBtnDdnsOk
Desc:		get ddns config
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteAdvanceNetConfig::OnBnClickedBtnDdnsOk()
{
	UpdateData(TRUE);

	if (DS_19AXX == g_struDeviceInfo[m_iDeviceIndex].iDeviceType)
	{
		m_struDDNSParaEx.byEnableDDNS = (BYTE)m_bChkDdns;
		m_struDDNSParaEx.byHostIndex = (BYTE)m_comboDDNSType.GetCurSel();
		
		if (m_bChkDdns)
		{
			memcpy(m_struDDNSParaEx.sServerName, m_csDDNSAddr, MAX_DOMAIN_NAME);
			m_struDDNSParaEx.wDDNSPort = (WORD)m_uDDNSPort;
			memcpy(m_struDDNSParaEx.sUsername, m_csDDNSUserName, NAME_LEN);
			memcpy(m_struDDNSParaEx.sPassword, m_csDDNSPwd, PASSWD_LEN);
			memcpy(m_struDDNSParaEx.sDomainName, m_csDevDomain, MAX_DOMAIN_NAME);
		}
	} 
	else
	{
		m_struDDNSPara.byEnableDDNS = (BYTE)m_bChkDdns;
		m_struDDNSPara.byHostIndex = (BYTE)m_comboDDNSType.GetCurSel();
		
		if (m_bChkDdns)
		{
			memcpy(m_struDDNSPara.struDDNS[m_struDDNSPara.byHostIndex].sServerName, m_csDDNSAddr, MAX_DOMAIN_NAME);
			m_struDDNSPara.struDDNS[m_struDDNSPara.byHostIndex].wDDNSPort = (WORD)m_uDDNSPort;
			memcpy(m_struDDNSPara.struDDNS[m_struDDNSPara.byHostIndex].sUsername, m_csDDNSUserName, NAME_LEN);
			memcpy(m_struDDNSPara.struDDNS[m_struDDNSPara.byHostIndex].sPassword, m_csDDNSPwd, PASSWD_LEN);
			memcpy(m_struDDNSPara.struDDNS[m_struDDNSPara.byHostIndex].sDomainName, m_csDevDomain, MAX_DOMAIN_NAME);
			m_struDDNSPara.struDDNS[m_struDDNSPara.byHostIndex].byStatus = m_cmbDDNSStatus.GetCurSel();
			
			if(m_struDDNSPara.byHostIndex == 4 /*HiDDNS*/)
			{
				m_struDDNSPara.struDDNS[m_struDDNSPara.byHostIndex].wCountryID = m_wCountrtID;
			}
		}
	}
}

/*********************************************************
  Function:	SwitchDDNSCtrlStat
  Desc:		change the control status about ddns
  Input:	iHost, the ddns type
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteAdvanceNetConfig::SwitchDDNSCtrlStat(int iHost)
{	
	char csUserName[NAME_LEN+1] = {0};
	char csServerName[MAX_DOMAIN_NAME + 1] = {0};
	char csPassword[PASSWD_LEN+1] = {0};
	if (m_bChkDdns)
	{
		switch(iHost)
		{
		case 0://private
			GetDlgItem(IDC_EDIT_DDNS_ADDR)->EnableWindow(TRUE);
			GetDlgItem(IDC_DDNS_PORT)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_DDNS_USER_NAME)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_DDNS_PWD)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_DDNS_PWD_CONFIRM)->EnableWindow(FALSE);
			GetDlgItem(IDC_DEV_DOMAIN)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_COUNTRYID)->ShowWindow(FALSE);
            GetDlgItem(IDC_EDIT_COUNTRYID)->ShowWindow(FALSE);
			//	
			//m_uDDNSPort = 7070;
			//m_csDevDomain.Format("");			
			if (DS_19AXX == g_struDeviceInfo[m_iDeviceIndex].iDeviceType)
			{
				memcpy(csServerName, m_struDDNSParaEx.sServerName, MAX_DOMAIN_NAME);
				m_uDDNSPort = m_struDDNSParaEx.wDDNSPort;
				m_csDevDomain = m_struDDNSParaEx.sDomainName;
			}
			else
			{
				memcpy(csServerName, m_struDDNSPara.struDDNS[iHost].sServerName, MAX_DOMAIN_NAME);
				m_uDDNSPort = m_struDDNSPara.struDDNS[iHost].wDDNSPort;
				m_csDevDomain = m_struDDNSPara.struDDNS[iHost].sDomainName;
				m_cmbDDNSStatus.SetCurSel(m_struDDNSPara.struDDNS[iHost].byStatus);
			}
			m_csDDNSAddr.Format("%s", csServerName);
			m_csDDNSUserName.Format("");
			m_csDDNSPwd.Format("");
			m_csDDNSPwdConfirm.Format("");
			break;
		case 1://DynDNS
			GetDlgItem(IDC_EDIT_DDNS_ADDR)->EnableWindow(TRUE);
			GetDlgItem(IDC_DDNS_PORT)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_DDNS_USER_NAME)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_DDNS_PWD)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_DDNS_PWD_CONFIRM)->EnableWindow(TRUE);
			GetDlgItem(IDC_DEV_DOMAIN)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_COUNTRYID)->ShowWindow(FALSE);
            GetDlgItem(IDC_EDIT_COUNTRYID)->ShowWindow(FALSE);

			if (DS_19AXX == g_struDeviceInfo[m_iDeviceIndex].iDeviceType)
			{
				memcpy(csServerName, m_struDDNSParaEx.sServerName, MAX_DOMAIN_NAME);
				m_csDDNSAddr.Format("%s", csServerName);
				memcpy(csUserName, m_struDDNSParaEx.sUsername, NAME_LEN);
				m_csDDNSUserName.Format("%s", csUserName);
				memcpy(csPassword, m_struDDNSParaEx.sPassword, PASSWD_LEN);
				m_csDDNSPwd.Format("%s", csPassword);
				m_csDDNSPwdConfirm = m_csDDNSPwd;
				m_uDDNSPort = m_struDDNSParaEx.wDDNSPort;
				m_csDevDomain = m_struDDNSParaEx.sDomainName;
			} 
			else
			{
				memcpy(csServerName, m_struDDNSPara.struDDNS[iHost].sServerName, MAX_DOMAIN_NAME);
				m_csDDNSAddr.Format("%s", csServerName);
				memcpy(csUserName, m_struDDNSPara.struDDNS[iHost].sUsername, NAME_LEN);
				m_csDDNSUserName.Format("%s", csUserName);
				memcpy(csPassword, m_struDDNSPara.struDDNS[iHost].sPassword, PASSWD_LEN);
				m_csDDNSPwd.Format("%s", csPassword);
				m_csDDNSPwdConfirm = m_csDDNSPwd;
				m_uDDNSPort = m_struDDNSPara.struDDNS[iHost].wDDNSPort;
				m_csDevDomain = m_struDDNSPara.struDDNS[iHost].sDomainName;
				m_cmbDDNSStatus.SetCurSel(m_struDDNSPara.struDDNS[iHost].byStatus);
			}
			
			break;
		case 2://PeanutHull
			GetDlgItem(IDC_EDIT_DDNS_ADDR)->EnableWindow(FALSE);
			GetDlgItem(IDC_DDNS_PORT)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_DDNS_USER_NAME)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_DDNS_PWD)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_DDNS_PWD_CONFIRM)->EnableWindow(TRUE);
			GetDlgItem(IDC_DEV_DOMAIN)->EnableWindow(FALSE);
            GetDlgItem(IDC_STATIC_COUNTRYID)->ShowWindow(FALSE);
            GetDlgItem(IDC_EDIT_COUNTRYID)->ShowWindow(FALSE);
			
			if (DS_19AXX == g_struDeviceInfo[m_iDeviceIndex].iDeviceType)
			{
				memcpy(csServerName, m_struDDNSParaEx.sServerName, MAX_DOMAIN_NAME);
				m_csDDNSAddr.Format("%s", csServerName);
				memcpy(csUserName, m_struDDNSParaEx.sUsername, NAME_LEN);
				m_csDDNSUserName.Format("%s", csUserName);
				memcpy(csPassword, m_struDDNSParaEx.sPassword, PASSWD_LEN);
				m_csDDNSPwd.Format("%s", csPassword);
				m_csDDNSPwdConfirm = m_csDDNSPwd;
				m_csDevDomain = m_struDDNSParaEx.sDomainName;
				m_uDDNSPort = 0;//
				m_csDevDomain.Format("");
			} 
			else
			{
				memcpy(csServerName, m_struDDNSPara.struDDNS[iHost].sServerName, MAX_DOMAIN_NAME);
				m_csDDNSAddr.Format("%s", csServerName);
				memcpy(csUserName, m_struDDNSPara.struDDNS[iHost].sUsername, NAME_LEN);
				m_csDDNSUserName.Format("%s", csUserName);
				memcpy(csPassword, m_struDDNSPara.struDDNS[iHost].sPassword, PASSWD_LEN);
				m_csDDNSPwd.Format("%s", csPassword);
				m_csDDNSPwdConfirm = m_csDDNSPwd;
				m_csDevDomain = m_struDDNSPara.struDDNS[iHost].sDomainName;
				m_uDDNSPort = 0;//
				m_csDevDomain.Format("");
				m_cmbDDNSStatus.SetCurSel(m_struDDNSPara.struDDNS[iHost].byStatus);
			}
			break;
		case 3://NO-IP
			GetDlgItem(IDC_EDIT_DDNS_ADDR)->EnableWindow(FALSE);
			GetDlgItem(IDC_DDNS_PORT)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_DDNS_USER_NAME)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_DDNS_PWD)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_DDNS_PWD_CONFIRM)->EnableWindow(TRUE);
			GetDlgItem(IDC_DEV_DOMAIN)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_COUNTRYID)->ShowWindow(FALSE);
            GetDlgItem(IDC_EDIT_COUNTRYID)->ShowWindow(FALSE);

			if (DS_19AXX == g_struDeviceInfo[m_iDeviceIndex].iDeviceType)
			{
				memcpy(csServerName, m_struDDNSParaEx.sServerName, MAX_DOMAIN_NAME);
				m_csDDNSAddr.Format("%s", csServerName);
				memcpy(csUserName, m_struDDNSParaEx.sUsername, NAME_LEN);
				m_csDDNSUserName.Format("%s", csUserName);
				memcpy(csPassword, m_struDDNSParaEx.sPassword, PASSWD_LEN);
				m_csDDNSPwd.Format("%s", csPassword);
				m_csDDNSPwdConfirm = m_csDDNSPwd;
				m_uDDNSPort = m_struDDNSParaEx.wDDNSPort;
				m_csDevDomain = m_struDDNSParaEx.sDomainName;
			}
			else
			{
				memcpy(csServerName, m_struDDNSPara.struDDNS[iHost].sServerName, MAX_DOMAIN_NAME);
				m_csDDNSAddr.Format("%s", csServerName);
				memcpy(csUserName, m_struDDNSPara.struDDNS[iHost].sUsername, NAME_LEN);
				m_csDDNSUserName.Format("%s", csUserName);
				memcpy(csPassword, m_struDDNSPara.struDDNS[iHost].sPassword, PASSWD_LEN);
				m_csDDNSPwd.Format("%s", csPassword);
				m_csDDNSPwdConfirm = m_csDDNSPwd;
				m_csDevDomain = m_struDDNSPara.struDDNS[iHost].sDomainName;
				m_uDDNSPort = 0;//
				m_csDevDomain = m_struDDNSPara.struDDNS[iHost].sDomainName;
				m_cmbDDNSStatus.SetCurSel(m_struDDNSPara.struDDNS[iHost].byStatus);
			}
			break;
        case 4://EDDNS
            GetDlgItem(IDC_EDIT_DDNS_ADDR)->EnableWindow(TRUE);
            GetDlgItem(IDC_DDNS_PORT)->EnableWindow(TRUE);
            GetDlgItem(IDC_EDIT_DDNS_USER_NAME)->EnableWindow(FALSE);
            GetDlgItem(IDC_EDIT_DDNS_PWD)->EnableWindow(FALSE);
            GetDlgItem(IDC_EDIT_DDNS_PWD_CONFIRM)->EnableWindow(FALSE);
            GetDlgItem(IDC_DEV_DOMAIN)->EnableWindow(TRUE);
            GetDlgItem(IDC_STATIC_COUNTRYID)->ShowWindow(TRUE);
            GetDlgItem(IDC_EDIT_COUNTRYID)->ShowWindow(TRUE);
            
			if (DS_19AXX == g_struDeviceInfo[m_iDeviceIndex].iDeviceType)
			{
				memcpy(csServerName, m_struDDNSParaEx.sServerName, MAX_DOMAIN_NAME);
				m_csDDNSAddr.Format("%s", csServerName);
				memcpy(csUserName, m_struDDNSParaEx.sUsername, NAME_LEN);
				m_csDDNSUserName.Format("%s", csUserName);
				memcpy(csPassword, m_struDDNSParaEx.sPassword, PASSWD_LEN);
				m_csDDNSPwd.Format("%s", csPassword);
				m_csDDNSPwdConfirm = m_csDDNSPwd;
				m_uDDNSPort = m_struDDNSParaEx.wDDNSPort;
				m_csDevDomain = m_struDDNSParaEx.sDomainName;
			}
			else
			{
				memcpy(csServerName, m_struDDNSPara.struDDNS[iHost].sServerName, MAX_DOMAIN_NAME);
				m_csDDNSAddr.Format("%s", csServerName);
				memcpy(csUserName, m_struDDNSPara.struDDNS[iHost].sUsername, NAME_LEN);
				m_csDDNSUserName.Format("%s", csUserName);
				memcpy(csPassword, m_struDDNSPara.struDDNS[iHost].sPassword, PASSWD_LEN);
				m_csDDNSPwd.Format("%s", csPassword);
				m_csDDNSPwdConfirm = m_csDDNSPwd;
				m_csDevDomain = m_struDDNSPara.struDDNS[iHost].sDomainName;
				m_uDDNSPort = m_struDDNSPara.struDDNS[iHost].wDDNSPort;
				m_csDevDomain = m_struDDNSPara.struDDNS[iHost].sDomainName;
				m_wCountrtID = m_struDDNSPara.struDDNS[iHost].wCountryID;
				m_cmbDDNSStatus.SetCurSel(m_struDDNSPara.struDDNS[iHost].byStatus);
			}
			break;
		default:
			break;
		}
		GetDlgItem(IDC_COMBO_DDNS_TYPE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_COMBO_DDNS_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DDNS_ADDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_DDNS_PORT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DDNS_USER_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DDNS_PWD)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DDNS_PWD_CONFIRM)->EnableWindow(FALSE);
		GetDlgItem(IDC_DEV_DOMAIN)->EnableWindow(FALSE);
	}

	 UpdateData(FALSE);
}

/*********************************************************
Function:	OnBnClickedBtnEmaileOk
Desc:		get email configuration
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteAdvanceNetConfig::OnBnClickedBtnEmaileOk()
{
	UpdateData(TRUE);
	int i = 0;
	char szLan[128] = {0};
	if (!m_csSenderAddr.IsEmpty() && !CheckEmailAddress(m_csSenderAddr))
	{
		g_StringLanType(szLan, "Email地址有误", "Email Address error");
		AfxMessageBox(szLan);
		return;
	}
	if (m_csAccountPwd != m_csAccountPwdConfirm)
	{
		g_StringLanType(szLan, "Email帐户密码不匹配", "Email account password does not match");
		AfxMessageBox(szLan);
		return;
	}
	if (m_bChkDdns &&m_csDDNSPwd != m_csDDNSPwdConfirm)
	{
		g_StringLanType(szLan, "DDNS帐户密码不匹配", "DDNS account password does not match");
		AfxMessageBox(szLan);
		return;
	}

	if (!m_csAccountPwd.IsEmpty() && m_csAccount.IsEmpty())
	{
		g_StringLanType(szLan, "Email帐户名不能为空", "Email account name should not be empty");
		AfxMessageBox(szLan);
		return;
	}


	ZeroMemory(&m_struEmailCfg, sizeof(m_struEmailCfg));
	m_struEmailCfg.dwSize = sizeof(m_struEmailCfg);
	sprintf((char *)(m_struEmailCfg.sAccount), "%s", m_csAccount);
	sprintf((char *)(m_struEmailCfg.sPassword), "%s", m_csAccountPwd);
	sprintf((char *)(m_struEmailCfg.struSender.sName), "%s", m_csSenderName);
	sprintf((char *)(m_struEmailCfg.struSender.sAddress), "%s", m_csSenderAddr);
	for (i = 0;i<m_listEmailReceiver.GetItemCount(); i++)
	{
		sprintf((char *)(m_struEmailCfg.struReceiver[i].sName), "%s", m_listEmailReceiver.GetItemText(i,0));
		sprintf((char *)(m_struEmailCfg.struReceiver[i].sAddress), "%s", m_listEmailReceiver.GetItemText(i,1));
	}

	sprintf((char *)(m_struEmailCfg.sSmtpServer), "%s", m_csSmtpSvrAddr);
	sprintf((char *)(m_struEmailCfg.sPop3Server), "%s", m_csPop3SvrAddr);
	m_struEmailCfg.byAttachment = (BYTE)m_bChkAttach;
	m_struEmailCfg.bySmtpServerVerify = (BYTE)m_bChkAuthen;
	m_struEmailCfg.byMailInterval = (BYTE)m_comboSendInterval.GetCurSel();
	switch (m_comboEncryptType.GetCurSel())
	{
	case 0:
		m_struEmailCfg.byEnableSSL = 0;
		m_struEmailCfg.byEnableTLS = 0;
		break;
	case 1:
		m_struEmailCfg.byEnableSSL = 1;
		m_struEmailCfg.byEnableTLS = 0;
		break;
	case 2:
		m_struEmailCfg.byEnableSSL = 0;
		m_struEmailCfg.byEnableTLS = 1;
		break;	
	}
	//m_struEmailCfg.byEnableSSL = (BYTE)m_bEnableSSL;
	m_struEmailCfg.wSmtpPort = m_wSmtpPort;
	m_struEmailCfg.byStartTLS = m_bChkStartTLS;
}

/*********************************************************
  Function: OnBtnExit	
  Desc:		exit the advance net configure
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteAdvanceNetConfig::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

/*********************************************************
  Function:	OnSelchangeComboDdnsType
  Desc:		select the ddns type
  Input:	void
  Output:	void
  Return:	void
**********************************************************/
void CDlgRemoteAdvanceNetConfig::OnSelchangeComboDdnsType() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	SwitchDDNSCtrlStat(m_comboDDNSType.GetCurSel());
	UpdateData(FALSE);
}

UINT GetEmailTestStatus(LPVOID pParam)
{
    CDlgRemoteAdvanceNetConfig *pEmailTest = (CDlgRemoteAdvanceNetConfig*)pParam;

    BOOL bKeepLoop = TRUE;
    DWORD dwState = 0;
    while (bKeepLoop)
    {

       if (!NET_DVR_GetEmailTestProgress(pEmailTest->m_lEmailTestHandle, &dwState))
       {
            AfxMessageBox(" 获取邮件测试状态失败");
            bKeepLoop = FALSE;
       }
       if (PROCESS_SUCCESS == dwState)
       {
           pEmailTest->SetEmailTestState("邮件测试成功");
           bKeepLoop = FALSE;
       }
       else if (PROCESS_FAILED == dwState)
       {
           pEmailTest->SetEmailTestState("邮件测试失败");
           bKeepLoop = FALSE;
       }
       else if (PROCESS_EXCEPTION == dwState)
       {
           pEmailTest->SetEmailTestState("邮件测试网络异常");
           bKeepLoop = FALSE;
       }
       else if (PROCESSING == dwState)
       {
           pEmailTest->SetEmailTestState("邮件测试中");
       }
       Sleep(1000);
    }
    
    NET_DVR_StopEmailTest(pEmailTest->m_lEmailTestHandle);;
    return 0;
}

void CDlgRemoteAdvanceNetConfig::SetEmailTestState(LPCTSTR lpszString)
{
    GetDlgItem(IDC_STATIC_EMAILTEST)->SetWindowText(lpszString);
}
/*********************************************************
  Function:	OnBtnTest
  Desc:		test email configure is ok or not
  Input:	void
  Output:	void
  Return:	void
**********************************************************/
void CDlgRemoteAdvanceNetConfig::OnBtnTest() 
{
    m_lEmailTestHandle =  NET_DVR_StartEmailTest(m_lServerID);
    if (-1 == m_lEmailTestHandle)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartEmailTest");
        MessageBox("邮件测试失败");
    }
    
    m_hEmailTestThread = CreateThread(NULL,0, LPTHREAD_START_ROUTINE(GetEmailTestStatus),this,0,NULL);		
    if (m_hEmailTestThread != NULL)
    {
        CloseHandle(m_hEmailTestThread);
        m_hEmailTestThread = NULL;
    }

}

void CDlgRemoteAdvanceNetConfig::OnBtnSnmpCfg() 
{
    CDlgSnmpCfg dlg;
   	dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDeviceIndex;
    dlg.DoModal();
}

DWORD WINAPI CDlgRemoteAdvanceNetConfig::GetNtpServerTestInfoThread(LPVOID lpArg)
{
	CDlgRemoteAdvanceNetConfig* pThis = reinterpret_cast<CDlgRemoteAdvanceNetConfig*>(lpArg);
	CString csErrInfo;
	DWORD dwState = 0;
	while (1)
	{
		
		if (!NET_DVR_GetRemoteConfigState(pThis->m_lNtpTestHandle, &dwState))
		{
			g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetRemoteConfigState NET_DVR_FIND_NAS_DIRECTORY ");
			pThis->GetDlgItem(IDC_STATIC_NTP_SERVER_TEST)->SetWindowText("Get state Fail!");
			NET_DVR_StopRemoteConfig(pThis->m_lNtpTestHandle);
			return -1;
		}
		else
		{
			if (dwState == PROCESSING)
			{
				pThis->GetDlgItem(IDC_STATIC_NTP_SERVER_TEST)->SetWindowText("Testing...");
				Sleep(1000);
			}
			else if (dwState == PROCESS_SUCCESS)
			{
				pThis->GetDlgItem(IDC_STATIC_NTP_SERVER_TEST)->SetWindowText("Test Success!");
				break;
			}
			else if (dwState == PROCESS_EXCEPTION)
			{
				pThis->GetDlgItem(IDC_STATIC_NTP_SERVER_TEST)->SetWindowText("Test Exception!!");
				break;
			}
			else
			{
				csErrInfo.Format("Test Fail %d", dwState);
				pThis->GetDlgItem(IDC_STATIC_NTP_SERVER_TEST)->SetWindowText(csErrInfo);
				break;
			}
			
		}
		
	}
	if (-1 != pThis->m_lNtpTestHandle)
	{
		if (!NET_DVR_StopRemoteConfig(pThis->m_lNtpTestHandle))
		{
			g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_FAIL_T, "Stop Remote Config Failed");
		}
		else
		{
			g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_SUCC_T, "Stop Remote Config Successful");
			pThis->m_lNtpTestHandle = -1;
		}
	}
	return 0 ;
}


void CDlgRemoteAdvanceNetConfig::OnBtnNtpServerTest() 
{
	UpdateData(TRUE);
	GetDlgItem(IDC_BTN_NTP_OK)->EnableWindow(FALSE);
	memset(&m_struServerTestPara, 0, sizeof(NET_DVR_SERVER_TEST_PARA));
	m_struServerTestPara.dwSize = sizeof(m_struServerTestPara);
	
	char szLan[128] = {0};
	if (m_iNTPInterHour < -12 || m_iNTPInterHour > 13 || m_iNTPInterMin < 0 || m_iNTPInterMin >59)
	{
		g_StringLanType(szLan, "时差输入有误!", "Time Zone Error!");
		AfxMessageBox(szLan);
		return;
	}
	m_struServerTestPara.unionServerPara.struNtpPara.struNtpPara.byEnableNTP = (BYTE)m_bChkNtp;
	if (m_bChkNtp)
	{
		memcpy(m_struServerTestPara.unionServerPara.struNtpPara.struNtpPara.sNTPServer, m_csNtpAddr, MAX_DOMAIN_NAME);
		m_struServerTestPara.unionServerPara.struNtpPara.struNtpPara.wInterval = m_iNtpInterval;
		m_struServerTestPara.unionServerPara.struNtpPara.struNtpPara.cTimeDifferenceH = (char)m_iNTPInterHour;
		m_struServerTestPara.unionServerPara.struNtpPara.struNtpPara.cTimeDifferenceM = (char)m_iNTPInterMin;
		m_struServerTestPara.unionServerPara.struNtpPara.struNtpPara.wNtpPort = (WORD)m_uNtpPort;
	}
	
	
	m_lNtpTestHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_NTP_SERVER_TEST, &m_struServerTestPara, sizeof(m_struServerTestPara), NULL, this);
	if (m_lNtpTestHandle >= 0)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Start Remote Config successfully");
		DWORD dwThreadId;
		m_hGetInfoThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetNtpServerTestInfoThread), this, 0, &dwThreadId);
		GetDlgItem(IDC_BTN_NTP_OK)->EnableWindow(TRUE);
	} 
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Start Remote Config failed");
		return;
	}
	
}

DWORD WINAPI CDlgRemoteAdvanceNetConfig::GetEmailTestWithParamInfoThread(LPVOID lpArg)
{
	CDlgRemoteAdvanceNetConfig* pThis = reinterpret_cast<CDlgRemoteAdvanceNetConfig*>(lpArg);
	DWORD dwState = 0;
	CString csErrInfo;
	while (1)
	{
		
		if (!NET_DVR_GetRemoteConfigState(pThis->m_lEmailTestWithParaHandle, &dwState))
		{
			g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetRemoteConfigState NET_DVR_FIND_NAS_DIRECTORY ");
			pThis->GetDlgItem(IDC_STATIC_EMAIL_SERVER_TEST_WITH_PARAM)->SetWindowText("Get state Fail!");
			NET_DVR_StopRemoteConfig(pThis->m_lEmailTestWithParaHandle);
			return -1;
		}
		else
		{
			if (dwState == PROCESSING)
			{
				pThis->GetDlgItem(IDC_STATIC_EMAIL_SERVER_TEST_WITH_PARAM)->SetWindowText("Testing...");
				Sleep(1000);
			}
			else if (dwState == PROCESS_SUCCESS)
			{
				pThis->GetDlgItem(IDC_STATIC_EMAIL_SERVER_TEST_WITH_PARAM)->SetWindowText("Test Success!");
				break;
			}
			else if (dwState == PROCESS_EXCEPTION)
			{
				pThis->GetDlgItem(IDC_STATIC_EMAIL_SERVER_TEST_WITH_PARAM)->SetWindowText("Test Exception!");
				break;
			}
			else
			{
				csErrInfo.Format("Test Fail %d", dwState);
				pThis->GetDlgItem(IDC_STATIC_EMAIL_SERVER_TEST_WITH_PARAM)->SetWindowText(csErrInfo);
				break;
			}
		}
		
	}
	if (-1 != pThis->m_lEmailTestWithParaHandle)
	{
		if (!NET_DVR_StopRemoteConfig(pThis->m_lEmailTestWithParaHandle))
		{
			g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_FAIL_T, "Stop Remote Config Failed");
		}
		else
		{
			g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_SUCC_T, "Stop Remote Config Successful");
			pThis->m_lNtpTestHandle = -1;
		}
	}
	return 0 ;
}

void CDlgRemoteAdvanceNetConfig::OnBtnEmailServerTestWithParam() 
{
	UpdateData(TRUE);
	memset(&m_struServerTestPara, 0, sizeof(NET_DVR_SERVER_TEST_PARA));
	m_struServerTestPara.dwSize = sizeof(m_struServerTestPara);

	int i = 0;
	char szLan[128] = {0};
	if (!m_csSenderAddr.IsEmpty() && !CheckEmailAddress(m_csSenderAddr))
	{
		g_StringLanType(szLan, "Email地址有误", "Email Address error");
		AfxMessageBox(szLan);
		return;
	}
	if (m_csAccountPwd != m_csAccountPwdConfirm)
	{
		g_StringLanType(szLan, "Email帐户密码不匹配", "Email account password does not match");
		AfxMessageBox(szLan);
		return;
	}
	if (m_bChkDdns &&m_csDDNSPwd != m_csDDNSPwdConfirm)
	{
		g_StringLanType(szLan, "DDNS帐户密码不匹配", "DDNS account password does not match");
		AfxMessageBox(szLan);
		return;
	}
	
	if (!m_csAccountPwd.IsEmpty() && m_csAccount.IsEmpty())
	{
		g_StringLanType(szLan, "Email帐户名不能为空", "Email account name should not be empty");
		AfxMessageBox(szLan);
		return;
	}

	m_struServerTestPara.unionServerPara.struEmailPara.struEmailPara.dwSize = sizeof(m_struEmailCfg);
	sprintf((char *)(m_struServerTestPara.unionServerPara.struEmailPara.struEmailPara.sAccount), "%s", m_csAccount);
	sprintf((char *)(m_struServerTestPara.unionServerPara.struEmailPara.struEmailPara.sPassword), "%s", m_csAccountPwd);
	sprintf((char *)(m_struServerTestPara.unionServerPara.struEmailPara.struEmailPara.struSender.sName), "%s", m_csSenderName);
	sprintf((char *)(m_struServerTestPara.unionServerPara.struEmailPara.struEmailPara.struSender.sAddress), "%s", m_csSenderAddr);
	for (i = 0;i<m_listEmailReceiver.GetItemCount(); i++)
	{
		sprintf((char *)(m_struServerTestPara.unionServerPara.struEmailPara.struEmailPara.struReceiver[i].sName), "%s", m_listEmailReceiver.GetItemText(i,0));
		sprintf((char *)(m_struServerTestPara.unionServerPara.struEmailPara.struEmailPara.struReceiver[i].sAddress), "%s", m_listEmailReceiver.GetItemText(i,1));
	}
	
	sprintf((char *)(m_struServerTestPara.unionServerPara.struEmailPara.struEmailPara.sSmtpServer), "%s", m_csSmtpSvrAddr);
	sprintf((char *)(m_struServerTestPara.unionServerPara.struEmailPara.struEmailPara.sPop3Server), "%s", m_csPop3SvrAddr);
	m_struServerTestPara.unionServerPara.struEmailPara.struEmailPara.byAttachment = (BYTE)m_bChkAttach;
	m_struServerTestPara.unionServerPara.struEmailPara.struEmailPara.bySmtpServerVerify = (BYTE)m_bChkAuthen;
	m_struServerTestPara.unionServerPara.struEmailPara.struEmailPara.byMailInterval = (BYTE)m_comboSendInterval.GetCurSel();
	//m_struServerTestPara.unionServerPara.struEmailPara.struEmailPara.byEnableSSL = (BYTE)m_bEnableSSL;
	m_struServerTestPara.unionServerPara.struEmailPara.struEmailPara.wSmtpPort = m_wSmtpPort;
	m_struServerTestPara.unionServerPara.struEmailPara.struEmailPara.byStartTLS = m_bChkStartTLS;
	//m_struServerTestPara.unionServerPara.struEmailPara.struEmailPara.byEnableTLS = (BYTE)m_bEnableTSL;
	switch (m_comboEncryptType.GetCurSel())
	{
	case 0:
		m_struServerTestPara.unionServerPara.struEmailPara.struEmailPara.byEnableSSL = 0;
		m_struServerTestPara.unionServerPara.struEmailPara.struEmailPara.byEnableTLS = 0;
		break;
	case 1:
		m_struServerTestPara.unionServerPara.struEmailPara.struEmailPara.byEnableSSL = 1;
		m_struServerTestPara.unionServerPara.struEmailPara.struEmailPara.byEnableTLS = 0;
		break;
	case 2:
		m_struServerTestPara.unionServerPara.struEmailPara.struEmailPara.byEnableSSL = 0;
		m_struServerTestPara.unionServerPara.struEmailPara.struEmailPara.byEnableTLS = 1;
		break;	
	}


	m_lEmailTestWithParaHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_EMAIL_SERVER_TEST, &m_struServerTestPara, sizeof(m_struServerTestPara), NULL, this);
	if (m_lEmailTestWithParaHandle >= 0)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Start Remote Config successfully");
		DWORD dwThreadId;
		m_hGetInfoThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetEmailTestWithParamInfoThread), this, 0, &dwThreadId);
	} 
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Start Remote Config failed");
		return;
	}
	
}

void CDlgRemoteAdvanceNetConfig::AddStatusList()
{
    m_cmbDDNSStatus.ResetContent();
    DWORD dwIndex = 0;
    char szLan[128] = {0};
	
    g_StringLanType(szLan,"无意义","Meaningless");
    m_cmbDDNSStatus.AddString(szLan);
    m_cmbDDNSStatus.SetItemData(dwIndex++,0);
    
    g_StringLanType(szLan,"连接服务器失败","connServerfail");
    m_cmbDDNSStatus.AddString(szLan);
    m_cmbDDNSStatus.SetItemData(dwIndex++,1);
    
    g_StringLanType(szLan,"解析地址消息失败","solveAddrMesFail");
    m_cmbDDNSStatus.AddString(szLan);
    m_cmbDDNSStatus.SetItemData(dwIndex++,2);
    
    g_StringLanType(szLan,"连接心跳服务器失败","connHeartSrvfail");
    m_cmbDDNSStatus.AddString(szLan);
    m_cmbDDNSStatus.SetItemData(dwIndex++,3);
    
    g_StringLanType(szLan,"解析心跳服务器消息失败","solveHeartMesFail");
    m_cmbDDNSStatus.AddString(szLan);
    m_cmbDDNSStatus.SetItemData(dwIndex++,4);
    
    g_StringLanType(szLan,"连接域名服务器失败","connHostSrvfail");
    m_cmbDDNSStatus.AddString(szLan);
    m_cmbDDNSStatus.SetItemData(dwIndex++,5);
    
    g_StringLanType(szLan,"解析域名服务器消息失败","solveHostMesFail");
    m_cmbDDNSStatus.AddString(szLan);
    m_cmbDDNSStatus.SetItemData(dwIndex++,6);
    
    g_StringLanType(szLan,"DDNS状态正常","updateSuccess");
    m_cmbDDNSStatus.AddString(szLan);
    m_cmbDDNSStatus.SetItemData(dwIndex++,7);
    
    g_StringLanType(szLan,"未启用","disable");
    m_cmbDDNSStatus.AddString(szLan);
    m_cmbDDNSStatus.SetItemData(dwIndex++,8);
    
    g_StringLanType(szLan,"注册域名成功","registHostSuccess");
    m_cmbDDNSStatus.AddString(szLan);
    m_cmbDDNSStatus.SetItemData(dwIndex++,9);
    
    g_StringLanType(szLan,"DNS服务器未配置","noDNSSrv");
    m_cmbDDNSStatus.AddString(szLan);
    m_cmbDDNSStatus.SetItemData(dwIndex++,10);
    
    
    g_StringLanType(szLan,"域名被占用","DomainConflict");
    m_cmbDDNSStatus.AddString(szLan);
    m_cmbDDNSStatus.SetItemData(dwIndex++,11);
    
    g_StringLanType(szLan,"别名(域名)不合法","invalidAlias");
    m_cmbDDNSStatus.AddString(szLan);
    m_cmbDDNSStatus.SetItemData(dwIndex++,12);
    
    g_StringLanType(szLan,"鉴权失败","authenticationFail");
    m_cmbDDNSStatus.AddString(szLan);
    m_cmbDDNSStatus.SetItemData(dwIndex++,13);
    
    g_StringLanType(szLan,"注册服务器错误","registServerError");
    m_cmbDDNSStatus.AddString(szLan);
    m_cmbDDNSStatus.SetItemData(dwIndex++,14);
    
    g_StringLanType(szLan,"注册失败","registFail");
    m_cmbDDNSStatus.AddString(szLan);
    m_cmbDDNSStatus.SetItemData(dwIndex++,15);
}
