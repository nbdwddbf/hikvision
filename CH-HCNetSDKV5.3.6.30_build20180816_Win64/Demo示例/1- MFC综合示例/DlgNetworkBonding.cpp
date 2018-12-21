// DlgNetworkBonding.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgNetworkBonding.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNetworkBonding dialog


CDlgNetworkBonding::CDlgNetworkBonding(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNetworkBonding::IDD, pParent)
    , m_strEthernetPort(_T(""))
{
	//{{AFX_DATA_INIT(CDlgNetworkBonding)
	m_bEnable = FALSE;
	m_bStatus = FALSE;
	m_bDhcp = FALSE;
	m_csBondIP = _T("");
	m_csBondMac = _T("");
	m_csBondMask = _T("");
	m_csGatewayIP = _T("");
	m_iBondMtu = 0;
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    m_dwNetworkNum = 0;
    memset(&m_struNetworkBonding, 0, sizeof(m_struNetworkBonding));
}

void CDlgNetworkBonding::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNetworkBonding)
	DDX_Control(pDX, IDC_COMBO_BOND_TYPE, m_comboBondType);
	DDX_Control(pDX, IDC_LIST_BOND_CARD, m_listBondCard);
	DDX_Control(pDX, IDC_COMBO_MASTER_CARD, m_comboMasterCard);
	DDX_Control(pDX, IDC_COMBO_WORK_MODE, m_comboWorkMode);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	DDX_Check(pDX, IDC_CHK_STATUS, m_bStatus);
	DDX_Check(pDX, IDC_CHK_DHCP, m_bDhcp);
	DDX_Text(pDX, IDC_EDIT_BOND_IP, m_csBondIP);
	DDX_Text(pDX, IDC_EDIT_BOND_MAC, m_csBondMac);
	DDX_Text(pDX, IDC_EDIT_BOND_MASK, m_csBondMask);
	DDX_Text(pDX, IDC_EDIT_GATEWAY_IP, m_csGatewayIP);
	DDX_Text(pDX, IDC_EDIT_BOND_MTU, m_iBondMtu);
	//}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMBO_BOND_MODE, m_comboBondMode);
    DDX_Text(pDX, IDC_EDIT_ETHERNET_PORT, m_strEthernetPort);
}


BEGIN_MESSAGE_MAP(CDlgNetworkBonding, CDialog)
	//{{AFX_MSG_MAP(CDlgNetworkBonding)
	ON_BN_CLICKED(IDC_BTN_SET_UP, OnBtnSetUp)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNetworkBonding message handlers

BOOL CDlgNetworkBonding::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    InitWnd();
    
    GetNetworkBonding(m_struNetworkBonding);
    
    SetNetworkBondingToWnd(m_struNetworkBonding);
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgNetworkBonding::InitWnd()
{
   InitWorkModeCombo();
   InitMasterCardCombo();
   InitBondCardList();
}

void CDlgNetworkBonding::InitWorkModeCombo()
{
    char szLan[128] = {0};
    m_comboWorkMode.ResetContent();
    g_StringLanType(szLan, "ÍøÂçÈÝ´í","Network fault tolerance");
    m_comboWorkMode.AddString(szLan);
    g_StringLanType(szLan, "¸ºÔØ¾ùºâ", "Load balancing");
    m_comboWorkMode.AddString(szLan);
}

void CDlgNetworkBonding::InitMasterCardCombo()
{
    unsigned int i = 0;
    char szLan[128] = {0};
    for (i = 0; i< m_dwNetworkNum; i++)
    {
        sprintf(szLan, "eth %d", i);
        m_comboMasterCard.AddString(szLan);
    }
}

void CDlgNetworkBonding::InitBondCardList()
{
    m_listBondCard.SetExtendedStyle(LVS_EX_CHECKBOXES);
    char szLan[128] = {0};
    int i = 0;
    for (i = 0; i < m_dwNetworkNum; i++)
    {
        sprintf(szLan, "eth %d", i);
        m_listBondCard.InsertItem(i, szLan);
    }
}

BOOL CDlgNetworkBonding::GetNetworkBonding(NET_DVR_NETWORK_BONDING &struNetworkBonding)
{
    DWORD dwRetrun = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_NETWORK_BONDING, -1, &struNetworkBonding, sizeof(struNetworkBonding), &dwRetrun))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_NETWORK_BONDING");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_NETWORK_BONDING");
        return FALSE;
    }
}

BOOL CDlgNetworkBonding::SetNetworkBonding(NET_DVR_NETWORK_BONDING &struNetworkBonding)
{
    if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_NETWORK_BONDING, -1, &struNetworkBonding, sizeof(struNetworkBonding)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_NETWORK_BONDING");
        return TRUE;
    } 
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_NETWORK_BONDING");
        return FALSE;
    }
}

void CDlgNetworkBonding::GetNetworkBondingFromWnd(NET_DVR_NETWORK_BONDING &struNetworkBonding)
{
    struNetworkBonding.byEnable = m_bEnable;
	struNetworkBonding.byNum = 1; // Ä¿Ç°	
    GetOneBondingFromWnd(m_struNetworkBonding.struOneBond[0]);
}

void CDlgNetworkBonding::SetNetworkBondingToWnd(NET_DVR_NETWORK_BONDING &struNetworkBonding)
{
    m_bEnable = struNetworkBonding.byEnable;
    struNetworkBonding.byNum = 1;
    SetOneBondingToWnd(struNetworkBonding.struOneBond[0]);
}

void CDlgNetworkBonding::GetOneBondingFromWnd(NET_DVR_ONE_BONDING &struOneBonding)
{
    struOneBonding.byMode = m_comboWorkMode.GetCurSel();
    struOneBonding.byUseDhcp = m_bDhcp;
    struOneBonding.byMasterCard = m_comboMasterCard.GetCurSel();
	struOneBonding.byStatus = m_bStatus;
    struOneBonding.byBondMode = m_comboBondMode.GetCurSel();
    for (int i = 0; i < m_listBondCard.GetItemCount(); i++)
    {
        if (i < MAX_NETWORK_CARD)
        {
            if (TRUE == m_listBondCard.GetCheck(i))
            {
                struOneBonding.byBond[i] = 1;
            }
            else
            {
                struOneBonding.byBond[i] = 0;
            }
        }
        else if (i >= MAX_NETWORK_CARD && i < MAX_NETWORK_CARD_EX + MAX_NETWORK_CARD)
        {
            if (TRUE == m_listBondCard.GetCheck(i))
            {
                struOneBonding.byBond2[i - MAX_NETWORK_CARD] = 1;
            }
            else
            {
                struOneBonding.byBond2[i - MAX_NETWORK_CARD] = 0;
            }
        }
    }
    GetEthernetV30FromWnd(struOneBonding.struEtherNet);
    strncpy(struOneBonding.struGatewayIpAddr.sIpV4, m_csGatewayIP.GetBuffer(0), sizeof(struOneBonding.struGatewayIpAddr.sIpV4));
}


void CDlgNetworkBonding::SetOneBondingToWnd(NET_DVR_ONE_BONDING &struOneBonding)
{
    m_comboWorkMode.SetCurSel(struOneBonding.byMode);
    m_bDhcp = struOneBonding.byUseDhcp;
    m_comboMasterCard.SetCurSel(struOneBonding.byMasterCard);
	m_bStatus = struOneBonding.byStatus;
    m_comboBondMode.SetCurSel(struOneBonding.byBondMode);
    for (int i = 0; i < m_listBondCard.GetItemCount(); i++)
    {
        if (i < MAX_NETWORK_CARD)
        {
            if (TRUE == struOneBonding.byBond[i])
            {
                m_listBondCard.SetCheck(i, TRUE);
            }
            else
            {
                m_listBondCard.SetCheck(i, FALSE);
            }
        }
        else if (i >= MAX_NETWORK_CARD && i < MAX_NETWORK_CARD_EX + MAX_NETWORK_CARD)
        {
            if (TRUE == struOneBonding.byBond2[i - MAX_NETWORK_CARD])
            {
                m_listBondCard.SetCheck(i, TRUE);
            }
            else
            {
                m_listBondCard.SetCheck(i, FALSE);
            }
        }
    }
    SetEthernetV30ToWnd(struOneBonding.struEtherNet);
    m_csGatewayIP = struOneBonding.struGatewayIpAddr.sIpV4;   

}

void CDlgNetworkBonding::SetEthernetV30ToWnd(NET_DVR_ETHERNET_V30 &struEthernet)
{
    m_csBondIP = struEthernet.struDVRIP.sIpV4;
    m_csBondMask = struEthernet.struDVRIPMask.sIpV4;
    m_comboBondType.SetCurSel(struEthernet.dwNetInterface - 1);

    m_iBondMtu = struEthernet.wMTU;
    m_csBondMac.Format("%02x:%02x:%02x:%02x:%02x:%02x", struEthernet.byMACAddr[0],struEthernet.byMACAddr[1],
        struEthernet.byMACAddr[2],struEthernet.byMACAddr[3],struEthernet.byMACAddr[4],struEthernet.byMACAddr[5]);
}

void CDlgNetworkBonding::GetEthernetV30FromWnd(NET_DVR_ETHERNET_V30 &struEthernet)
{
    strncpy(struEthernet.struDVRIP.sIpV4, m_csBondIP.GetBuffer(0), sizeof(struEthernet.struDVRIP.sIpV4));
    strncpy(struEthernet.struDVRIPMask.sIpV4, m_csBondMask.GetBuffer(0), sizeof(struEthernet.struDVRIPMask.sIpV4));
    struEthernet.dwNetInterface = m_comboBondType.GetCurSel() + 1;
    struEthernet.wMTU = m_iBondMtu;

    if (struEthernet.byEthernetPortNo > 0)
    {
        m_strEthernetPort.Format("Port %d", struEthernet.byEthernetPortNo - 1);
    }
}

void CDlgNetworkBonding::OnBtnSetUp() 
{
    UpdateData(TRUE);
    GetNetworkBondingFromWnd(m_struNetworkBonding);
 
	char szLan[128] = {0};

    if (!SetNetworkBonding(m_struNetworkBonding))
    {
		g_StringLanType(szLan, "ÉèÖÃBondingÍø¿¨Ê§°Ü!", "Fail to set network bonding!");
        AfxMessageBox(szLan);
    }
}

void CDlgNetworkBonding::OnButtonExit() 
{
	CDialog::OnCancel();
}

void CDlgNetworkBonding::OnButtonUpdate() 
{
    GetNetworkBonding(m_struNetworkBonding);
    
    SetNetworkBondingToWnd(m_struNetworkBonding);
    UpdateData(FALSE);
}
