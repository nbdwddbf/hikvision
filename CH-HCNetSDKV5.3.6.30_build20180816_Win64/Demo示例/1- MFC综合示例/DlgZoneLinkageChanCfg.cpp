// DlgZoneLinkageChanCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgZoneLinkageChanCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgZoneLinkageChanCfg dialog


CDlgZoneLinkageChanCfg::CDlgZoneLinkageChanCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgZoneLinkageChanCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgZoneLinkageChanCfg)
	m_csIP = _T("");
	m_csIPV6 = _T("");
	m_nPort = 0;
	m_csPwd = _T("");
	m_csUser = _T("");
	m_nChan = 0;
	m_csDevName = _T("");
	m_csDevSerialNo = _T("");
	m_nServerPort = 0;
	m_csServerAddr = _T("");
	//}}AFX_DATA_INIT
	memset(&m_struZoneChannLinkageCfg, 0, sizeof(m_struZoneChannLinkageCfg));
}


void CDlgZoneLinkageChanCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgZoneLinkageChanCfg)
	DDX_Control(pDX, IDC_CMB_SERVER_TYPE, m_cmbServerType);
	DDX_Control(pDX, IDC_CMB_DEV_ADDR_TYPE, m_cmbDevAddrType);
	DDX_Control(pDX, IDC_CMB_CHAN_NO, m_cmbChanNo);
	DDX_Text(pDX, IDC_EDIT_IP, m_csIP);
	DDX_Text(pDX, IDC_EDIT_IPV6, m_csIPV6);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_PSWD, m_csPwd);
	DDX_Text(pDX, IDC_EDIT_USER, m_csUser);
	DDX_Text(pDX, IDC_EDIT_CHAN, m_nChan);
	DDX_Control(pDX, IDC_CMB_ZONE_NO, m_cmbZoneIndex);
	DDX_Text(pDX, IDC_EDIT_DEV_NAME, m_csDevName);
	DDX_Text(pDX, IDC_EDIT_DEV_SERIAL_NO, m_csDevSerialNo);
	DDX_Text(pDX, IDC_EDIT_PORT_SERVER_PORT, m_nServerPort);
	DDX_Text(pDX, IDC_EDIT_SERVER_ADDR, m_csServerAddr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgZoneLinkageChanCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgZoneLinkageChanCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_CBN_SELCHANGE(IDC_CMB_DEV_ADDR_TYPE, OnSelchangeComboDevAddrType)
	ON_CBN_SELCHANGE(IDC_CMB_CHAN_NO, OnSelchangeComboChan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgZoneLinkageChanCfg message handlers

void CDlgZoneLinkageChanCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwBytesReturned = -1;
	char szLan[128] = {0};
	
	m_struZoneChannLinkageCfg.dwSize = sizeof(NET_DVR_ZONE_CHANNEL_LINKAGE_CFG);
	int iAlarmInNo = m_cmbZoneIndex.GetCurSel();
	
	BOOL bRet = FALSE;
	bRet = NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_ZONE_CHANNEL_LINKAGE_CFG, iAlarmInNo, &m_struZoneChannLinkageCfg, sizeof(m_struZoneChannLinkageCfg), &dwBytesReturned);
	if (!bRet)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ZONE_CHANNEL_LINKAGE_CFG");	
		sprintf(szLan,"NET_DVR_GET_ZONE_CHANNEL_LINKAGE_CFG failed: %d",NET_DVR_GetLastError());
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ZONE_CHANNEL_LINKAGE_CFG");	
	}

	m_cmbChanNo.SetCurSel(0);
	OnSelchangeComboChan();

}

void CDlgZoneLinkageChanCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	char szLan[128] = {0};
	
	OnBtnSave();
	m_struZoneChannLinkageCfg.dwSize = sizeof(NET_DVR_ZONE_CHANNEL_LINKAGE_CFG);

	int iAlarmInNo = m_cmbZoneIndex.GetCurSel();
	
	if (NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_ZONE_CHANNEL_LINKAGE_CFG, iAlarmInNo, &m_struZoneChannLinkageCfg, sizeof(m_struZoneChannLinkageCfg)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_ZONE_CHANNEL_LINKAGE_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_ZONE_CHANNEL_LINKAGE_CFG");
		sprintf(szLan,"NET_DVR_SET_ZONE_CHANNEL_LINKAGE_CFG failed: %d",NET_DVR_GetLastError());
		AfxMessageBox(szLan);
    }
}

BOOL CDlgZoneLinkageChanCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	DWORD dwReturn = 0;
	NET_DVR_ALARMHOST_ABILITY struAlarmHostAbility = {0};
    if (NET_DVR_GetDeviceAbility(m_lUserID, ALARMHOST_ABILITY, NULL, 0, (char*)&struAlarmHostAbility, sizeof(struAlarmHostAbility)))
    {
        g_pMainDlg->AddLog(m_lUserID, OPERATION_SUCC_T, "ALARMHOST_ABILITY");
    }
    else
    {
        g_pMainDlg->AddLog(m_lUserID, OPERATION_FAIL_T, "ALARMHOST_ABILITY");
        return FALSE;
    }

	int iZoneNum = struAlarmHostAbility.wTotalAlarmInNum;

	m_cmbZoneIndex.ResetContent();
	CString csTemp;
	int i = -1;
	for (i = 0; i < iZoneNum; i++)
	{
		csTemp.Format("alarm in %d", i+1);
		m_cmbZoneIndex.AddString(csTemp);
	}

	m_cmbZoneIndex.SetCurSel(0);	
	OnBtnGet();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgZoneLinkageChanCfg::OnSelchangeComboDevAddrType()
{
	if (m_cmbDevAddrType.GetCurSel())
	{
		//GetDlgItem(IDC_EDIT_IPV6)->EnableWindow(FALSE);
		//GetDlgItem(IDC_STATIC__V6)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC__V4)->SetWindowText("domain:");
	}
	else
	{
		//GetDlgItem(IDC_EDIT_IPV6)->EnableWindow(TRUE);
		//GetDlgItem(IDC_STATIC__V6)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC__V4)->SetWindowText("IPv4:");
	}
	
	UpdateWindow();
}

void CDlgZoneLinkageChanCfg::OnSelchangeComboChan()
{
	int iZoneLinkageChanIndex = m_cmbChanNo.GetCurSel();

	m_cmbServerType.SetCurSel(m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].byDDNSType);
	m_nServerPort = (UINT)m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].wDDNSPort;
	m_csServerAddr = m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].byServerAddr;
	char csTmp[MAX_DOMAIN_NAME+1] = {0};
	strncpy((char*)csTmp, (char*)m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].byDevName, MAX_DOMAIN_NAME);
	m_csDevName = csTmp;
	strncpy((char*)csTmp, (char*)m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].byDevSerialNum, SERIALNO_LEN);
	m_csDevSerialNo = csTmp;

	m_cmbDevAddrType.SetCurSel(m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].byAddressType);
	OnSelchangeComboDevAddrType();

	memset(csTmp, 0, sizeof(csTmp));
	strncpy((char*)csTmp, (char*)m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].sUserName, NAME_LEN);
	m_csUser = csTmp;
	memset(csTmp, 0, sizeof(csTmp));
	strncpy((char*)csTmp, (char*)m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].sPassword, PASSWD_LEN);
	m_csPwd = csTmp;

	m_nPort = (UINT)m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].wDevPort;
	m_nChan = (UINT)m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].dwChannel;
	
	if (m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].byAddressType)
	{
		m_csIP = m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].unionDevAddr.struDomain.szDomain;
	}
	else
	{
		//if (inet_addr(m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].unionAddr.struAddrIP.struIp.sIpV4) == 0)
		{
			m_csIPV6 = m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].unionDevAddr.struAddrIP.struIp.byIPv6;
		}
		//else
		{
			m_csIP = m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].unionDevAddr.struAddrIP.struIp.sIpV4;
		}
	}
	
	UpdateData(FALSE);
}

void CDlgZoneLinkageChanCfg::OnBtnSave()
{
	UpdateData(TRUE);

	int iZoneLinkageChanIndex = m_cmbChanNo.GetCurSel();
	
	m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].byAddressType = m_cmbDevAddrType.GetCurSel();
	m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].wDevPort = (WORD)m_nPort;
	m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].dwChannel = (DWORD)m_nChan;
	strncpy((char*)m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].sUserName, m_csUser, NAME_LEN);
	strncpy((char*)m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].sPassword, m_csPwd, PASSWD_LEN);

	m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].byDDNSType = m_cmbServerType.GetCurSel();
	m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].wDDNSPort = (WORD)m_nServerPort;
	strncpy((char*)m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].byServerAddr, m_csServerAddr, MAX_DOMAIN_NAME);
	strncpy((char*)m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].byDevName, m_csDevName, MAX_DOMAIN_NAME);
	strncpy((char*)m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].byDevSerialNum, m_csDevSerialNo, SERIALNO_LEN);
	
	if (m_cmbDevAddrType.GetCurSel())
	{
		strncpy((char*)m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].unionDevAddr.struDomain.szDomain, m_csIP, MAX_DOMAIN_NAME);
	}
	else
	{
		//if (m_csIP.Find(":") == -1)
		{
			strncpy((char*)m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].unionDevAddr.struAddrIP.struIp.sIpV4, m_csIP, 16);
		}
		//else
		{
			sprintf((char*)m_struZoneChannLinkageCfg.struLinkChannels[iZoneLinkageChanIndex].unionDevAddr.struAddrIP.struIp.byIPv6, m_csIPV6, 128);
		}
	}
	UpdateData(FALSE);
}
