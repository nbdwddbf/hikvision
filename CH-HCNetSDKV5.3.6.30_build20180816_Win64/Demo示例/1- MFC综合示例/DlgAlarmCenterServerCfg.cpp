// DlgAlarmCenterServerCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmCenterServerCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmCenterServerCfg dialog


CDlgAlarmCenterServerCfg::CDlgAlarmCenterServerCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmCenterServerCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAlarmCenterServerCfg)
	m_nIntervalTime = 0;
	m_csIP = _T("");
	m_nPort = 0;
	m_csIPV6 = _T("");
	//}}AFX_DATA_INIT
}


void CDlgAlarmCenterServerCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmCenterServerCfg)
	DDX_Control(pDX, IDC_COMBO_SERVERTYPE, m_cmbServerType);
	DDX_Text(pDX, IDC_EDIT_INTERVAL_TIME, m_nIntervalTime);
	DDX_Text(pDX, IDC_EDIT_IP, m_csIP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_IPV6, m_csIPV6);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmCenterServerCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmCenterServerCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_CBN_SELCHANGE(IDC_COMBO_SERVERTYPE, OnSelchangeComboServertype)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmCenterServerCfg message handlers

BOOL CDlgAlarmCenterServerCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	OnBtnGet();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlarmCenterServerCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwBytesReturned = -1;
	char szLan[128] = {0};
	
	NET_DVR_CENTER_SERVER_CFG struCenterServerCfg = {0};
	struCenterServerCfg.dwSize = sizeof(NET_DVR_CENTER_SERVER_CFG);
	
	BOOL bRet = FALSE;
	bRet = NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_CENTER_SERVER_CFG, -1, &struCenterServerCfg, sizeof(struCenterServerCfg), &dwBytesReturned);
	if (!bRet)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_CENTER_SERVER_CFG");	
		sprintf(szLan,"NET_DVR_GET_CENTER_SERVER_CFG failed: %d",NET_DVR_GetLastError());
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_CENTER_SERVER_CFG");	
	}

	m_cmbServerType.SetCurSel(struCenterServerCfg.byAddressType);
	m_nPort = struCenterServerCfg.wServerPort;
	m_nIntervalTime = struCenterServerCfg.wInterval;
	
	OnSelchangeComboServertype();

	if (struCenterServerCfg.byAddressType)
	{
		m_csIP = struCenterServerCfg.unionServer.struDomain.szDomain;
	}
	else
	{
		//if (inet_addr(struCenterServerCfg.unionServer.struAddrIP.struIp.sIpV4) == 0)
		{
			m_csIPV6 = struCenterServerCfg.unionServer.struAddrIP.struIp.byIPv6;
		}
		//else
		{
			m_csIP = struCenterServerCfg.unionServer.struAddrIP.struIp.sIpV4;
		}
	}

	UpdateData(FALSE);
}

void CDlgAlarmCenterServerCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);

	char szLan[128] = {0};

	NET_DVR_CENTER_SERVER_CFG struCenterServerCfg = {0};
	memset(&struCenterServerCfg, 0, sizeof(NET_DVR_CENTER_SERVER_CFG));

	struCenterServerCfg.dwSize = sizeof(NET_DVR_CENTER_SERVER_CFG);
	struCenterServerCfg.byAddressType = m_cmbServerType.GetCurSel();
	struCenterServerCfg.wInterval = (WORD)m_nIntervalTime;
	struCenterServerCfg.wServerPort = (WORD)m_nPort;

	if (m_cmbServerType.GetCurSel())
	{
		sprintf((char*)struCenterServerCfg.unionServer.struDomain.szDomain, m_csIP, MAX_DOMAIN_NAME);
	}
	else
	{
		//if (m_csIP.Find(":") == -1)
		{
			sprintf((char*)struCenterServerCfg.unionServer.struAddrIP.struIp.sIpV4, m_csIP, 16);
		}
		//else
		{
			sprintf((char*)struCenterServerCfg.unionServer.struAddrIP.struIp.byIPv6, m_csIPV6, 128);
		}
	}
	
	if (NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_CENTER_SERVER_CFG, -1, &struCenterServerCfg, sizeof(NET_DVR_CENTER_SERVER_CFG)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_CENTER_SERVER_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_CENTER_SERVER_CFG");
		sprintf(szLan,"NET_DVR_SET_CENTER_SERVER_CFG failed: %d",NET_DVR_GetLastError());
		AfxMessageBox(szLan);
    }
}

void CDlgAlarmCenterServerCfg::OnSelchangeComboServertype() 
{
	// TODO: Add your control notification handler code here
	if (m_cmbServerType.GetCurSel())
	{
		//GetDlgItem(IDC_EDIT_IPV6)->EnableWindow(FALSE);
		//GetDlgItem(IDC_STATIC_V6)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_V4)->SetWindowText("”Ú√˚:");
	}
	else
	{
		//GetDlgItem(IDC_EDIT_IPV6)->EnableWindow(TRUE);
		//GetDlgItem(IDC_STATIC_V6)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_V4)->SetWindowText("IPv4µÿ÷∑:");
	}

	UpdateWindow();
}
