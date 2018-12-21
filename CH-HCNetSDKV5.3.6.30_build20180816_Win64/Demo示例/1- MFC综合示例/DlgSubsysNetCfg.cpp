// DlgSubsysNetCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgSubsysNetCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSubsysNetCfg dialog


CDlgSubsysNetCfg::CDlgSubsysNetCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSubsysNetCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSubsysNetCfg)
	m_bCardDHCP = FALSE;
	m_csDNSFirst = _T("");
	m_csDNSSecond = _T("");
	m_csGateway = _T("");
	m_csIP = _T("");
	m_csMacAddr = _T("");
	m_csMask = _T("");
	m_wMTU = 0;
	m_byCardNum = 0;
	m_dwSlotChan = 0;
	//}}AFX_DATA_INIT
    memset(&m_struNetCfg, 0, sizeof(m_struNetCfg));
    m_struNetCfg.dwSize = sizeof(m_struNetCfg);
}


void CDlgSubsysNetCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSubsysNetCfg)
	DDX_Control(pDX, IDC_COMB_SUBSYSTEM_NETCARDTYPE, m_cmbNetCardType);
	DDX_Control(pDX, IDC_COMBO_SUBSYSTEM_NETINTERFACE, m_cmbNetInterface);
//	DDX_Control(pDX, IDC_COMBO_CARD1, m_cmbCardType);
	DDX_Control(pDX, IDC_COMB_SUBSYSTEM_NETCARD, m_cmbNetCard);
	DDX_Check(pDX, IDC_CHECK_CARD1_DHCP, m_bCardDHCP);
	DDX_Text(pDX, IDC_EDIT_CARD1_DNS1, m_csDNSFirst);
	DDX_Text(pDX, IDC_EDIT_CARD1_DNS2, m_csDNSSecond);
	DDX_Text(pDX, IDC_EDIT_CARD1_GATEWAY, m_csGateway);
	DDX_Text(pDX, IDC_EDIT_CARD1_IP, m_csIP);
	DDX_Text(pDX, IDC_EDIT_CARD1_MAC, m_csMacAddr);
	DDX_Text(pDX, IDC_EDIT_CARD1_MASK, m_csMask);
	DDX_Text(pDX, IDC_EDIT_CARD1_MTU, m_wMTU);
	DDX_Text(pDX, IDC_EDIT_SUBSYSTEM_NETCARD_NUM, m_byCardNum);
	DDX_Text(pDX, IDC_EDIT_SUBSYSTEM_SLOTCHANNEL, m_dwSlotChan);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSubsysNetCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgSubsysNetCfg)
	ON_CBN_SELCHANGE(IDC_COMB_SUBSYSTEM_NETCARD, OnSelchangeNetcard)
	ON_BN_CLICKED(IDC_BUT_SUBSYSTEM_GET, OnButGet)
	ON_BN_CLICKED(IDC_BUT_SUBSYSTEM_SAVE, OnButSave)
	ON_BN_CLICKED(IDC_BUT_SUBSYSTEM_SET, OnButSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSubsysNetCfg message handlers
void ChoseToCopy(CString &csSrc , NET_DVR_IPADDR &struDst)
{
   if ( strlen((char *)struDst.sIpV4) != 0 )
   {
        csSrc.Format("%s", (char *)struDst.sIpV4); 
        return; 
   }
   csSrc.Format("%s", (char *)struDst.byIPv6); 
} 


void CDlgSubsysNetCfg::OnSelchangeNetcard() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    int iSel = m_cmbNetCard.GetItemData(m_cmbNetCard.GetCurSel());
    LPNET_DVR_ETHERNET_MULTI lpEther = &m_struNetCfg.struEtherNet[iSel]; 

    m_bCardDHCP = lpEther->byUseDhcp; 
    m_cmbNetInterface.SetCurSel(lpEther->dwNetInterface - 1);
    m_cmbNetCardType.SetCurSel(lpEther->byCardType); 

    ChoseToCopy(m_csIP, lpEther->struDVRIP); 
    ChoseToCopy(m_csMask, lpEther->struDVRIPMask); 
    ChoseToCopy(m_csGateway, lpEther->struGatewayIpAddr); 
    ChoseToCopy(m_csDNSFirst, lpEther->struDnsServer1IpAddr); 
    ChoseToCopy(m_csDNSSecond, lpEther->struDnsServer2IpAddr); 
    UpdateData(FALSE); 

    GetDlgItem(IDC_EDIT_CARD1_MAC)->EnableWindow(); 
    m_csMacAddr.Format("%s", (char *)lpEther->byMACAddr); 
    GetDlgItem(IDC_EDIT_CARD1_MAC)->EnableWindow(FALSE);
    
    GetDlgItem(IDC_EDIT_CARD1_MTU)->EnableWindow(); 
    m_wMTU = lpEther->wMTU; 
    GetDlgItem(IDC_EDIT_CARD1_MTU)->EnableWindow(FALSE);
}

void CDlgSubsysNetCfg::OnButGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
    DWORD dwChannelEx = m_dwSlotChan; 
    DWORD dwRet; 
    char szLan[128]; 
    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_SUBSYSTEM_NETCFG, dwChannelEx, &m_struNetCfg, sizeof(m_struNetCfg), &dwRet))
    {
        g_StringLanType(szLan, "获取子系统网卡信息失败", "Failed to get Subsystem netcard info");
        sprintf(szLan, "%s Error Code %d", szLan, NET_DVR_GetLastError()); 
        AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SUBSYSTEM_NETCFG");
        return ; 
    }
    m_cmbNetCard.SetCurSel(0); 
    OnSelchangeNetcard(); 
}

void ChoseToCopy(NET_DVR_IPADDR &struDst, const CString &csSrc)
{
    if ( csSrc.GetLength() > 16)
    {
        strcpy((char *)struDst.byIPv6 , (LPCSTR)csSrc); 
    }
    else
        strcpy((char *)struDst.sIpV4 , (LPCSTR)csSrc); 
} 


void CDlgSubsysNetCfg::OnButSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    m_byCardNum = m_struNetCfg.byNetworkCardNum; 

    int iSel = m_cmbNetCard.GetItemData(m_cmbNetCard.GetCurSel());
    LPNET_DVR_ETHERNET_MULTI lpEther = &m_struNetCfg.struEtherNet[iSel]; 

    lpEther->byCardType = m_cmbNetCardType.GetCurSel();
    lpEther->byUseDhcp = m_bCardDHCP; 
    lpEther->dwNetInterface = m_cmbNetInterface.GetCurSel() + 1 ; 

    ChoseToCopy(lpEther->struDVRIP, m_csIP); 
    ChoseToCopy(lpEther->struDVRIPMask, m_csMask); 
    ChoseToCopy(lpEther->struGatewayIpAddr, m_csGateway); 
    ChoseToCopy(lpEther->struDnsServer1IpAddr, m_csDNSFirst); 
    ChoseToCopy(lpEther->struDnsServer2IpAddr, m_csDNSSecond); 
}

void CDlgSubsysNetCfg::OnButSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    DWORD dwChannelEx = m_dwSlotChan; 
    char szLan[128];
    if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_SUBSYSTEM_NETCFG, dwChannelEx, &m_struNetCfg, sizeof(m_struNetCfg)))
    {
        g_StringLanType(szLan, "设置子系统网卡信息失败", "Failed to set Subsystem netcard info");
        sprintf(szLan, "%s Error Code %d", szLan, NET_DVR_GetLastError()); 
        AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SUBSYSTEM_NETCFG");
    }
}

BOOL CDlgSubsysNetCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    CString csTmp ; 
    for (int i=0; i<MAX_NETWORK_CARD; i++)
    {
        csTmp.Format("%d", i); 
        m_cmbNetCard.AddString(csTmp); 
        m_cmbNetCard.SetItemData(i, i); 
    }
	OnButGet(); 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
