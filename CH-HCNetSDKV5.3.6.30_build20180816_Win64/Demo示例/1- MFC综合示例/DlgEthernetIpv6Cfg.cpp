// DlgEthernetIpv6Cfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgEthernetIpv6Cfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEthernetIpv6Cfg dialog

DWORD WINAPI CDlgEthernetIpv6Cfg::GetEthernetIPV6ListThread(LPVOID lpArg)
{
	CDlgEthernetIpv6Cfg* pThis = reinterpret_cast<CDlgEthernetIpv6Cfg*>(lpArg);
	int iRet =0;
	char szLan[128] = {0};
	while(pThis->m_bGetNext)
	{
		if (-1 == pThis->m_lFindHandle)
		{
			continue;
		}
		iRet = NET_DVR_GetNextRemoteConfig(pThis->m_lFindHandle, &pThis->m_lpStruEthernetIpv6Cfg[pThis->m_iEthernetCount], sizeof(NET_DVR_ETHERNET_IPV6_CFG));
		if (iRet == NET_SDK_GET_NEXT_STATUS_SUCCESS)
		{
			pThis->AddEthernetIPV6InfoToDlg(&(pThis->m_lpStruEthernetIpv6Cfg[pThis->m_iEthernetCount])); //
			pThis->m_iEthernetCount++;
		} 
		else
		{
			if (iRet == NET_SDK_GET_NETX_STATUS_NEED_WAIT)
			{
				Sleep(5);
				continue;
			}
			if (iRet == NET_SDK_GET_NEXT_STATUS_FINISH)
			{
				g_StringLanType(szLan, "获取列表结束!", "Get route info Ending");
				//AfxMessageBox(szLan);
				break;
			}
			else if(iRet == NET_SDK_GET_NEXT_STATUS_FAILED)
			{
				g_StringLanType(szLan, "获取列表失败!", "Get route info failed");
				AfxMessageBox(szLan);
				break;
			}
			else
			{
				g_StringLanType(szLan, "未知状态", "Unknown status");
				//	AfxMessageBox(szLan);
				break;
			}
		}
	}
	if (-1 != pThis->m_lFindHandle)
	{
		if (!NET_DVR_StopRemoteConfig(pThis->m_lFindHandle))
		{
			g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_FAIL_T, "Stop Remote Config Failed");
		}
		else
		{
			g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_SUCC_T, "Stop Remote Config Successful");
			pThis->m_bGetNext = FALSE;
			pThis->m_lFindHandle = -1;
		}
	}
	return 0;
}

CDlgEthernetIpv6Cfg::CDlgEthernetIpv6Cfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEthernetIpv6Cfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEthernetIpv6Cfg)
	//m_csMacAddr = _T("");
	//}}AFX_DATA_INIT
	m_lFindHandle = -1;
	m_bGetNext = FALSE;
	m_hGetInfoThread = NULL;
	m_lpStruEthernetIpv6Cfg = NULL;
	m_iEthernetCount = 0;
	memset(&m_struEthernetIpv6Cond, 0, sizeof(m_struEthernetIpv6Cond));
}

CDlgEthernetIpv6Cfg::~CDlgEthernetIpv6Cfg()
{
	delete[] m_lpStruEthernetIpv6Cfg;
	m_lpStruEthernetIpv6Cfg = NULL;
}

void CDlgEthernetIpv6Cfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEthernetIpv6Cfg)
	DDX_Control(pDX, IDC_LIST_ETHERNET_IPV6, m_EthernetIpv6Cfglist);
//	DDX_Text(pDX, IDC_EDIT_MACADDR, m_csMacAddr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEthernetIpv6Cfg, CDialog)
	//{{AFX_MSG_MAP(CDlgEthernetIpv6Cfg)
	ON_BN_CLICKED(IDC_BTN_GET_ETHERNET_IPV6, OnBtnGetEthernetIpv6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEthernetIpv6Cfg message handlers

BOOL CDlgEthernetIpv6Cfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	char szLan[100] = "\0";
	g_StringLanType(szLan,"序号","NO.");
	m_EthernetIpv6Cfglist.SetExtendedStyle(m_EthernetIpv6Cfglist.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
	m_EthernetIpv6Cfglist.InsertColumn(0, szLan, LVCFMT_LEFT, 60, -1);

    g_StringLanType(szLan,"IPV6状态","IPV6 Status");
	m_EthernetIpv6Cfglist.InsertColumn(1, szLan, LVCFMT_LEFT, 120, -1);

	g_StringLanType(szLan,"IPV6地址","IPV6 Address");
	m_EthernetIpv6Cfglist.InsertColumn(2, szLan, LVCFMT_LEFT, 300, -1);

	m_lpStruEthernetIpv6Cfg = new NET_DVR_ETHERNET_IPV6_CFG[64];
	memset(m_lpStruEthernetIpv6Cfg, 0, 64*sizeof(NET_DVR_ETHERNET_IPV6_CFG));

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgEthernetIpv6Cfg::OnBtnGetEthernetIpv6() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int i = 0;
	NET_DVR_NETCFG_V30 struNetCfg = {0};
    DWORD dwRetrun = 0;
	char szLan[128] = {0};
	m_EthernetIpv6Cfglist.DeleteAllItems();

	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_NETCFG_V30, 0, &struNetCfg, sizeof(NET_DVR_NETCFG_V30), &dwRetrun))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_NETCFG_V30");
		g_StringLanType(szLan, "获取物理MAC地址失败", "Get Network Configure failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_NETCFG_V30");
	}

	
	LONG IRet = 0;
	m_iEthernetCount = 0;
	m_struEthernetIpv6Cond.dwSize = sizeof(m_struEthernetIpv6Cond);
	memcpy(m_struEthernetIpv6Cond.byMACAddr, struNetCfg.struEtherNet[0].byMACAddr, MACADDR_LEN);

	if (m_lFindHandle >= 0)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "It is getting data, wait for a moment");
	} 
	else
	{
		m_lFindHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_GET_IPV6_LIST, &m_struEthernetIpv6Cond, sizeof(m_struEthernetIpv6Cond), NULL, this);
		if (m_lFindHandle < 0)
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_IPV6_LIST");
			return;
		} 
		else
		{
			m_bGetNext = TRUE;
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Start Remote Config successfully");
			DWORD dwThreadId;
			m_hGetInfoThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetEthernetIPV6ListThread),this,0,&dwThreadId);
		}
	}
}

void CDlgEthernetIpv6Cfg::AddEthernetIPV6InfoToDlg(LPNET_DVR_ETHERNET_IPV6_CFG lpInter)
{
	char szStr[128] = {0};

	int iCount = m_EthernetIpv6Cfglist.GetItemCount();
	//序号
	sprintf(szStr, "%3d", iCount);
	m_EthernetIpv6Cfglist.InsertItem(iCount, szStr);
	//IPV6状态
	char szLan[128] = {0};
	g_StringLanType(szLan,"路由公告","Router Advertisement");
	if (lpInter->byState == 0) //0-路由分配，1-自动设置
	{
		m_EthernetIpv6Cfglist.SetItemText(iCount, 1, szLan);
	} 
	else
	{
		m_EthernetIpv6Cfglist.SetItemText(iCount, 1, "DHCP");
	}

	memset(szStr, 0, sizeof(szStr));
	memcpy(szStr, lpInter->byIPv6, MAX_IPV6_LEN);
	m_EthernetIpv6Cfglist.SetItemText(iCount, 2, szStr);
}
