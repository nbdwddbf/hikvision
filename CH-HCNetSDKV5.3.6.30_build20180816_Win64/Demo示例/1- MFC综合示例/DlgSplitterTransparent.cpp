// DlgSplitterTransparent.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgSplitterTransparent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSplitterTransparent dialog
#include "DlgSplitterStartTrans.h"

CDlgSplitterTransparent::CDlgSplitterTransparent(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSplitterTransparent::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSplitterTransparent)
	m_bEnable = FALSE;
	m_csRemoteIp = _T("");
	m_wPort = 0;
	m_wLocalPort = 0;
	//}}AFX_DATA_INIT
}


void CDlgSplitterTransparent::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSplitterTransparent)
	DDX_Control(pDX, IDC_COMBO_SERIAL_TYPE, m_comboSerialType);
	DDX_Control(pDX, IDC_COMBO_TRANSPARENT_MODE, m_comboTransparentMode);
	DDX_Control(pDX, IDC_COMBO_TRANSPARENT_NUM, m_comboTransparentNum);
	DDX_Control(pDX, IDC_COMBO_RS485_NUM, m_comboRs485Num);
	DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
	DDX_Text(pDX, IDC_EDIT_REMOTE_HOST_IP, m_csRemoteIp);
	DDX_Text(pDX, IDC_EDIT_PORT, m_wPort);
	DDX_Text(pDX, IDC_EDIT_LOCAL_PORT, m_wLocalPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSplitterTransparent, CDialog)
	//{{AFX_MSG_MAP(CDlgSplitterTransparent)
	ON_BN_CLICKED(IDC_BTN_SAVE_PARA, OnBtnSavePara)
	ON_CBN_SELCHANGE(IDC_COMBO_TRANSPARENT_MODE, OnSelchangeComboTransparentMode)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_COPY_ALL, OnBtnCopyAll)
	ON_CBN_SELCHANGE(IDC_COMBO_TRANSPARENT_NUM, OnSelchangeComboTransparentNum)
	ON_CBN_SELCHANGE(IDC_COMBO_RS485_NUM, OnSelchangeComboRs485Num)
	ON_BN_CLICKED(IDC_BTN_START_TRANSPARENT, OnBtnStartTransparent)
	ON_CBN_SELCHANGE(IDC_COMBO_SERIAL_TYPE, OnSelchangeComboSerialType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSplitterTransparent message handlers

BOOL CDlgSplitterTransparent::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	// TODO: Add extra initialization here	
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();

	m_comboSerialType.SetCurSel(1);
	OnSelchangeComboSerialType();
	memset(m_struTransChanCfgServer, 0, sizeof(m_struTransChanCfgServer));
	memset(m_struTransChanCfgClinet, 0, sizeof(m_struTransChanCfgClinet));
	int i = 0;
	for (i = 0; i < 9; i++)
	{
		m_struTransChanCfgClinet[i].dwSize = sizeof(m_struTransChanCfgClinet[0]);
		m_struTransChanCfgServer[i].dwSize = sizeof(m_struTransChanCfgServer[0]);
		m_struTransChanCfgClinet[i].byWorkMode = 1;
		m_struTransChanCfgServer[i].byWorkMode = 2;
	}
	
	OnSelchangeComboTransparentMode();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSplitterTransparent::OnBtnSavePara() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int iSel = m_comboTransparentNum.GetCurSel();
	int iType = m_comboSerialType.GetCurSel();
	int iChannel = m_comboRs485Num.GetCurSel() + 1;

	if (-1 == iSel)
	{
		return;
	}
	if (m_comboTransparentMode.GetCurSel() == 0)
	{
		if (iType == 0)
		{
			m_struTransChanCfgClinet[0].struTransparentPara.struClientMode.struClientSingle[iSel].byEnable = m_bEnable;
			strncpy(m_struTransChanCfgClinet[0].struTransparentPara.struClientMode.struClientSingle[iSel].struIP.sIpV4, m_csRemoteIp, 16);
			m_struTransChanCfgClinet[0].struTransparentPara.struClientMode.struClientSingle[iSel].wPort = m_wPort;
		}
		else
		{
			m_struTransChanCfgClinet[iChannel].struTransparentPara.struClientMode.struClientSingle[iSel].byEnable = m_bEnable;
			strncpy(m_struTransChanCfgClinet[iChannel].struTransparentPara.struClientMode.struClientSingle[iSel].struIP.sIpV4, m_csRemoteIp, 16);
			m_struTransChanCfgClinet[iChannel].struTransparentPara.struClientMode.struClientSingle[iSel].wPort = m_wPort;
		}
				
	}
	else
	{
		if (iType == 0)
		{
			m_struTransChanCfgServer[0].struTransparentPara.struServerMode.struServerSingle[iSel].byEnable = m_bEnable;
			strncpy(m_struTransChanCfgServer[0].struTransparentPara.struServerMode.struServerSingle[iSel].struIP.sIpV4, m_csRemoteIp, 16);
			m_struTransChanCfgServer[0].struTransparentPara.struServerMode.wPort = m_wLocalPort;
		}
		else
		{
			m_struTransChanCfgServer[iChannel].struTransparentPara.struServerMode.struServerSingle[iSel].byEnable = m_bEnable;
			strncpy(m_struTransChanCfgServer[iChannel].struTransparentPara.struServerMode.struServerSingle[iSel].struIP.sIpV4, m_csRemoteIp, 16);
			m_struTransChanCfgServer[iChannel].struTransparentPara.struServerMode.wPort = m_wLocalPort;
		}		
	}
}

void CDlgSplitterTransparent::OnSelchangeComboTransparentMode() 
{
	// TODO: Add your control notification handler code here
	int iSel = m_comboTransparentMode.GetCurSel();
	char szLan[128] = {0};

	switch (iSel)
	{
	case 0:
		g_StringLanType(szLan, "客户端模式", "Client mode");
		GetDlgItem(IDC_STATIC_GROUP_MODE)->SetWindowText(szLan);
		g_StringLanType(szLan, "远程主机IP", "Remote host IP");
		GetDlgItem(IDC_STATIC_IP)->SetWindowText(szLan);
		GetDlgItem(IDC_STATIC_LOCAL_PORT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_LOCAL_PORT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PORT)->ShowWindow(SW_SHOW);
		break;
	case 1:
		g_StringLanType(szLan, "服务器模式", "Server mode");
		GetDlgItem(IDC_STATIC_GROUP_MODE)->SetWindowText(szLan);
		g_StringLanType(szLan, "允许接入IP", "Allow Access IP");
		GetDlgItem(IDC_STATIC_IP)->SetWindowText(szLan);
		GetDlgItem(IDC_STATIC_LOCAL_PORT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_LOCAL_PORT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PORT)->ShowWindow(SW_HIDE);
		break;
	default:
		g_StringLanType(szLan, "远程主机IP", "Remote host IP");
		GetDlgItem(IDC_STATIC_IP)->SetWindowText(szLan);
		GetDlgItem(IDC_STATIC_LOCAL_PORT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_LOCAL_PORT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PORT)->ShowWindow(SW_SHOW);
		break;
	}

	m_comboTransparentNum.SetCurSel(0);
	OnSelchangeComboTransparentNum();

	UpdateData(FALSE);	
}

void CDlgSplitterTransparent::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	OnBtnSavePara();

	DWORD dwChannel = m_comboRs485Num.GetCurSel() + 1;
	if (m_comboSerialType.GetCurSel() == 0)
	{
		dwChannel |= 0x80000000;
	}

	NET_DVR_TRANSPARENT_CHAN_CFG m_struTransChanCfg = {0};
	m_struTransChanCfg.dwSize = sizeof(m_struTransChanCfg);
	if (m_comboTransparentMode.GetCurSel() == 0)
	{
		if (m_comboSerialType.GetCurSel() == 0)
		{
			memcpy(&m_struTransChanCfg, &m_struTransChanCfgClinet[0], sizeof(m_struTransChanCfg));
		}
		else
		{
			memcpy(&m_struTransChanCfg, &m_struTransChanCfgClinet[dwChannel], sizeof(m_struTransChanCfg));
		}		
	}
	else
	{
		if (m_comboSerialType.GetCurSel() == 0)
		{
			memcpy(&m_struTransChanCfg, &m_struTransChanCfgServer[0], sizeof(m_struTransChanCfg));
			m_struTransChanCfgServer[0].struTransparentPara.struServerMode.wPort = m_wLocalPort;
		}
		else
		{
			memcpy(&m_struTransChanCfg, &m_struTransChanCfgServer[dwChannel], sizeof(m_struTransChanCfg));
			m_struTransChanCfgServer[dwChannel].struTransparentPara.struServerMode.wPort = m_wLocalPort;
		}
	}
// 	m_struTansChanCfg.dwSize = sizeof(m_struTansChanCfg);
// 	m_struTansChanCfg.byWorkMode = m_comboTransparentMode.GetCurSel() + 1;
// 	if (m_struTansChanCfg.byWorkMode == 2)
// 	{
// 		m_struTansChanCfg.struTransparentPara.struServerMode.wPort = m_wLocalPort;
// 	}
	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_SPLITTER_TRANS_CHAN_CFG, dwChannel, &m_struTransChanCfg, sizeof(m_struTransChanCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SPLITTER_TRANS_CHAN_CFG");
		AfxMessageBox(NET_DVR_GetErrorMsg());
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_SPLITTER_TRANS_CHAN_CFG");
		AfxMessageBox("Success");
	}
}

void CDlgSplitterTransparent::OnBtnCopyAll() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	OnBtnSavePara();
	
	DWORD dwChannel = 0;
	NET_DVR_TRANSPARENT_CHAN_CFG m_struTransChanCfg = {0};
	int iSel = m_comboTransparentNum.GetCurSel();
	int iType = m_comboSerialType.GetCurSel();
	
	if (iType == 0)
	{
		if (m_comboTransparentMode.GetCurSel() == 0)
		{
			memcpy(&m_struTransChanCfg, &m_struTransChanCfgClinet[0], sizeof(m_struTransChanCfg));
		}
		else
		{
			memcpy(&m_struTransChanCfg, &m_struTransChanCfgServer[0], sizeof(m_struTransChanCfg));
		}
	}
	else
	{
		if (m_comboTransparentMode.GetCurSel() == 0)
		{
			memcpy(&m_struTransChanCfg, &m_struTransChanCfgClinet[iSel], sizeof(m_struTransChanCfg));
		}
		else
		{
			memcpy(&m_struTransChanCfg, &m_struTransChanCfgServer[iSel], sizeof(m_struTransChanCfg));
		}
	}
// 	m_struTansChanCfg.dwSize = sizeof(m_struTansChanCfg);
// 	m_struTansChanCfg.byWorkMode = m_comboTransparentMode.GetCurSel() + 1;

	for (dwChannel = 1; dwChannel < m_comboRs485Num.GetCount() + 1; dwChannel++)
	{	
		if (m_comboSerialType.GetCurSel() == 0)
		{
			dwChannel |= 0x80000000;
		}
		if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_SPLITTER_TRANS_CHAN_CFG, dwChannel, &m_struTransChanCfg, sizeof(m_struTransChanCfg)))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Channel:[%d]NET_DVR_SET_SPLITTER_TRANS_CHAN_CFG", dwChannel);
			AfxMessageBox(NET_DVR_GetErrorMsg());
			return;
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Channel:[%d]NET_DVR_SET_SPLITTER_TRANS_CHAN_CFG", dwChannel);			
		}
	}
	
	AfxMessageBox("Success");
}

void CDlgSplitterTransparent::OnSelchangeComboTransparentNum() 
{
	// TODO: Add your control notification handler code here
	//UpdateData(TRUE);

	int iSel = m_comboTransparentNum.GetCurSel();
	int iType = m_comboSerialType.GetCurSel();
	int iChannel = m_comboRs485Num.GetCurSel() + 1;

	if (iSel == -1)
	{
		return;
	}

	if (m_comboTransparentMode.GetCurSel() == 0)
	{
		if (iType == 0)
		{
			m_bEnable = m_struTransChanCfgClinet[0].struTransparentPara.struClientMode.struClientSingle[iSel].byEnable;
			m_csRemoteIp = m_struTransChanCfgClinet[0].struTransparentPara.struClientMode.struClientSingle[iSel].struIP.sIpV4;
			m_wPort = m_struTransChanCfgClinet[0].struTransparentPara.struClientMode.struClientSingle[iSel].wPort;
		}
		else
		{
			m_bEnable = m_struTransChanCfgClinet[iChannel].struTransparentPara.struClientMode.struClientSingle[iSel].byEnable;
			m_csRemoteIp = m_struTransChanCfgClinet[iChannel].struTransparentPara.struClientMode.struClientSingle[iSel].struIP.sIpV4;
			m_wPort = m_struTransChanCfgClinet[iChannel].struTransparentPara.struClientMode.struClientSingle[iSel].wPort;
		}		
	}
	else
	{
		if (iType == 0)
		{
			m_bEnable = m_struTransChanCfgServer[0].struTransparentPara.struServerMode.struServerSingle[iSel].byEnable;
			m_csRemoteIp = m_struTransChanCfgServer[0].struTransparentPara.struServerMode.struServerSingle[iSel].struIP.sIpV4;
		}
		else
		{
			m_bEnable = m_struTransChanCfgServer[iChannel].struTransparentPara.struServerMode.struServerSingle[iSel].byEnable;
			m_csRemoteIp = m_struTransChanCfgServer[iChannel].struTransparentPara.struServerMode.struServerSingle[iSel].struIP.sIpV4;
		}		
		//m_wLocalPort = m_struTansChanCfg.struTransparentPara.struServerMode.wPort;
	}

	UpdateData(FALSE);
	
}

void CDlgSplitterTransparent::OnSelchangeComboRs485Num() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	DWORD dwChannel = m_comboRs485Num.GetCurSel() + 1;

	if (dwChannel == 0)
	{
		return;
	}

	if (m_comboSerialType.GetCurSel() == 0)
	{
		dwChannel |= 0x80000000;
	}

	DWORD dwReturned = 0;
	NET_DVR_TRANSPARENT_CHAN_CFG m_struTransChanCfg = {0};
	if (!NET_DVR_GetDVRConfig(m_lServerID,  NET_DVR_GET_SPLITTER_TRANS_CHAN_CFG, dwChannel, &m_struTransChanCfg, sizeof(m_struTransChanCfg), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SPLITTER_TRANS_CHAN_CFG");
		AfxMessageBox(NET_DVR_GetErrorMsg());
	}
	else
	{
		m_comboTransparentMode.SetCurSel(m_struTransChanCfg.byWorkMode - 1);		

		if (m_struTransChanCfg.byWorkMode == 1)
		{
			m_comboTransparentMode.SetCurSel(0);
			m_comboTransparentNum.SetCurSel(0);
			m_bEnable = m_struTransChanCfg.struTransparentPara.struClientMode.struClientSingle[0].byEnable;
			m_csRemoteIp = m_struTransChanCfg.struTransparentPara.struClientMode.struClientSingle[0].struIP.sIpV4;
			m_wPort = m_struTransChanCfg.struTransparentPara.struClientMode.struClientSingle[0].wPort;
			if (m_comboSerialType.GetCurSel() == 0)
			{
				memcpy(&m_struTransChanCfgClinet[0], &m_struTransChanCfg, sizeof(m_struTransChanCfg));
			}
			else
			{
				memcpy(&m_struTransChanCfgClinet[dwChannel], &m_struTransChanCfg, sizeof(m_struTransChanCfg));
			}			
		}
		else
		{
			m_comboTransparentMode.SetCurSel(1);
			m_comboTransparentNum.SetCurSel(0);
			m_bEnable = m_struTransChanCfg.struTransparentPara.struServerMode.struServerSingle[0].byEnable;
			m_csRemoteIp = m_struTransChanCfg.struTransparentPara.struServerMode.struServerSingle[0].struIP.sIpV4;
			m_wLocalPort = m_struTransChanCfg.struTransparentPara.struServerMode.wPort;
			if (m_comboSerialType.GetCurSel() == 0)
			{
				memcpy(&m_struTransChanCfgServer[0], &m_struTransChanCfg, sizeof(m_struTransChanCfg));
			}
			else
			{
				memcpy(&m_struTransChanCfgServer[dwChannel], &m_struTransChanCfg, sizeof(m_struTransChanCfg));
			}			
		}

		OnSelchangeComboTransparentMode();
		UpdateData(FALSE);
	}
}

void CDlgSplitterTransparent::OnBtnStartTransparent() 
{
	// TODO: Add your control notification handler code here
	CDlgSplitterStartTrans dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.DoModal();
}

void CDlgSplitterTransparent::OnSelchangeComboSerialType() 
{
	// TODO: Add your control notification handler code here
	CString cs;
	int i = 0;

	if (m_comboSerialType.GetCurSel() == 0)
	{
		m_comboRs485Num.ResetContent();
		m_comboRs485Num.AddString("1");
	}
	else
	{
		m_comboRs485Num.ResetContent();
		for (i = 0; i < 8; i++)
		{
			cs.Format("%d", i + 1);
			m_comboRs485Num.AddString(cs);
		}
	}
}
