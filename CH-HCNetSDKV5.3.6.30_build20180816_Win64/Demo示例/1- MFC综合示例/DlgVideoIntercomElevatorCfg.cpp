// DlgVideoIntercomElevatorCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVideoIntercomElevatorCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomElevatorCfg dialog


CDlgVideoIntercomElevatorCfg::CDlgVideoIntercomElevatorCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVideoIntercomElevatorCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVideoIntercomElevatorCfg)
	m_bEnable = FALSE;
    m_dwNegativeFloor = 0;
	m_csServiceIP = _T("");
	m_wPort = 0;
	//}}AFX_DATA_INIT
	m_lServerID = -1;
	m_iDevIndex = -1;
	memset(&m_struElevatorCfg, 0, sizeof(m_struElevatorCfg));
    m_csUserName = _T("");
    m_csPassword = _T("");
    m_dwElevatorNo = 0;
}


void CDlgVideoIntercomElevatorCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVideoIntercomElevatorCfg)
	DDX_Control(pDX, IDC_COMBO_RS485_PROTOCOL_TYPE, m_comboRS485Protocol);
	DDX_Control(pDX, IDC_COMBO_NETWORK_PROTOCOL_TYPE, m_comboNetworkProtocol);
	DDX_Control(pDX, IDC_COMBO_INTERFACE_TYPE, m_comboInterfaceType);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
    DDX_Text(pDX, IDC_EDIT_FLOOR, m_dwNegativeFloor);
	DDX_Text(pDX, IDC_EDIT_SERVICE_IPADDR, m_csServiceIP);
	DDX_Text(pDX, IDC_EDIT_SERVICE_PORT, m_wPort);
    DDX_Control(pDX, IDC_CMB_ELEVATOR_CONTROL_TYPE, m_cmbElevatorControlType);
    DDX_Text(pDX, IDC_EDIT_USER_NAME, m_csUserName);
    DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csPassword);
    DDX_Text(pDX, IDC_EDIT_ELEVATOR_NO, m_dwElevatorNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVideoIntercomElevatorCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVideoIntercomElevatorCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomElevatorCfg message handlers
BOOL CDlgVideoIntercomElevatorCfg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString tmp;
	char szLan[128] = {0};

	m_comboRS485Protocol.ResetContent();
	m_comboNetworkProtocol.ResetContent();

	g_StringLanType(szLan, "无", "None");
	m_comboRS485Protocol.AddString(szLan);
	m_comboRS485Protocol.SetItemData(0, 0);

	g_StringLanType(szLan, "私有", "Private");
	m_comboRS485Protocol.AddString(szLan);
	m_comboRS485Protocol.SetItemData(1, 1);

	g_StringLanType(szLan, "自定义", "Custom");
	m_comboRS485Protocol.AddString(szLan);
	m_comboRS485Protocol.SetItemData(2, 255);

	g_StringLanType(szLan, "无", "None");
	m_comboNetworkProtocol.AddString(szLan);
	m_comboNetworkProtocol.SetItemData(0, 0);
	
	g_StringLanType(szLan, "私有", "Private");
	m_comboNetworkProtocol.AddString(szLan);
	m_comboNetworkProtocol.SetItemData(1, 1);
	
	g_StringLanType(szLan, "自定义", "Custom");
	m_comboNetworkProtocol.AddString(szLan);
	m_comboNetworkProtocol.SetItemData(2, 255);

    m_cmbElevatorControlType.SetCurSel(0);

	return TRUE;
}

void CDlgVideoIntercomElevatorCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReturn = 0;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_ELEVATORCONTROL_CFG_V50, m_dwElevatorNo, &m_struElevatorCfg, sizeof(m_struElevatorCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ELEVATORCONTROL_CFG_V50");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ELEVATORCONTROL_CFG_V50");
    }

	m_bEnable = m_struElevatorCfg.byEnable;
    m_dwNegativeFloor = m_struElevatorCfg.byNegativeFloor;
	m_comboInterfaceType.SetCurSel(m_struElevatorCfg.byInterfaceType);
    m_cmbElevatorControlType.SetCurSel(m_struElevatorCfg.byElevatorControlType);
    m_csUserName = m_struElevatorCfg.sUserName;
    m_csPassword = m_struElevatorCfg.sPassword;
    
    int i = 0;
    for (i=0; i<m_comboRS485Protocol.GetCount(); i++)
    {
        if (m_comboRS485Protocol.GetItemData(i) == m_struElevatorCfg.byRS485Protocol)
        {
            m_comboRS485Protocol.SetCurSel(i);
            break;
        }
    }
    
    for (i=0; i<m_comboNetworkProtocol.GetCount(); i++)
    {
        if (m_comboNetworkProtocol.GetItemData(i) == m_struElevatorCfg.byNetworkType)
        {
            m_comboNetworkProtocol.SetCurSel(i);
            break;
        }
    }
    
    
    if (ValidIPv6(m_struElevatorCfg.struServerIP.byIPv6))
    {
        m_csServiceIP.Format("%s", m_struElevatorCfg.struServerIP.byIPv6);
    }
    else
    {
        m_csServiceIP.Format("%s", m_struElevatorCfg.struServerIP.sIpV4);
    }
    
    m_wPort = m_struElevatorCfg.wServerPort;
    UpdateData(FALSE);
}

inline BOOL CDlgVideoIntercomElevatorCfg::ValidIPv6(BYTE *ip)
{
    if (strlen((char *)ip) > 2 && strchr((char *)ip, ':') != NULL)
    {
        return TRUE;
    }
    return FALSE;
}

void CDlgVideoIntercomElevatorCfg::OnBtnSet() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char szLan[128] = {0};
    m_struElevatorCfg.dwSize = sizeof(m_struElevatorCfg);
    m_struElevatorCfg.byEnable = m_bEnable;
    m_struElevatorCfg.byNegativeFloor = (BYTE)m_dwNegativeFloor;
    m_struElevatorCfg.byInterfaceType = m_comboInterfaceType.GetCurSel();
    m_struElevatorCfg.byRS485Protocol = m_comboRS485Protocol.GetItemData(m_comboRS485Protocol.GetCurSel());
    m_struElevatorCfg.byNetworkType = m_comboNetworkProtocol.GetItemData(m_comboNetworkProtocol.GetCurSel());
    m_struElevatorCfg.byElevatorControlType = m_cmbElevatorControlType.GetCurSel();
    memcpy(m_struElevatorCfg.sUserName, m_csUserName, m_csUserName.GetLength());
    memcpy(m_struElevatorCfg.sPassword, m_csPassword, m_csPassword.GetLength());
    if (!CheckIPStr(m_csServiceIP) && !ValidIPv6((BYTE*)m_csServiceIP.GetBuffer(m_csServiceIP.GetLength())))
    {
        g_StringLanType(szLan, "非法的多播IP地址", "Illegal Multicast address");
        AfxMessageBox(szLan);
        return;
    }
    
    if (m_csServiceIP.Find(':') != -1)
    {
        memset(&m_struElevatorCfg.struServerIP.sIpV4, 0, 16);//2013-09-03
        strncpy((char *)m_struElevatorCfg.struServerIP.byIPv6, m_csServiceIP, 128);
    }
    else
    {
        memset(&m_struElevatorCfg.struServerIP.byIPv6, 0, 128);//2013-09-03
        strncpy(m_struElevatorCfg.struServerIP.sIpV4, m_csServiceIP, 16);
    }
    m_struElevatorCfg.wServerPort = m_wPort;

    
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_ELEVATORCONTROL_CFG_V50, m_dwElevatorNo, &m_struElevatorCfg, sizeof(m_struElevatorCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_ELEVATORCONTROL_CFG_V50");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_ELEVATORCONTROL_CFG_V50");
    }
}
