// DlgPosConnectMode.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPosConnectMode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPosConnectMode dialog


CDlgPosConnectMode::CDlgPosConnectMode(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPosConnectMode::IDD, pParent)
    , m_szRestrictRemoteIP(_T(""))
{
	//{{AFX_DATA_INIT(CDlgPosConnectMode)
	m_wRecvPort = 0;
	m_wDstPort = 0;
	m_csSourceAddr = _T("");
	m_wSourcePort = 0;
	m_csDstAddr = _T("");
	m_bEnableDstAddr = FALSE;
	m_bEnableDstPort = FALSE;
	m_bEnableSourcePort = FALSE;
	m_csMultiCastAddr = _T("");
	m_wMultiCastPort = 0;
	m_iUserID = -1;
	m_iDevIndex = -1;
	m_byUSBToRS232SerialNum = 0;
	//}}AFX_DATA_INIT
}


void CDlgPosConnectMode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPosConnectMode)
	DDX_Control(pDX, IDC_COMBO_FILTER_ID, m_cmbFilterID);
	DDX_Control(pDX, IDC_COMBO_RS232_STOPBIT, m_comboRS232StopBit);
	DDX_Control(pDX, IDC_COMBO_RS232_PARITY, m_comboRS232Parity);
	DDX_Control(pDX, IDC_COMBO_RS232_FLOWCTRL, m_comboRS232FlowCtrl);
	DDX_Control(pDX, IDC_COMBO_RS232_DATABIT, m_comboRS232DataBit);
	DDX_Control(pDX, IDC_COMBO_RS232_BAUDRATE, m_comboRS232BaudRate);
	DDX_Control(pDX, IDC_COMBO_RS2232_WORKMODE, m_comboRS232WorkMode);
	DDX_Control(pDX, IDC_COMBO_CONNECT_MODE, m_comboConnectMode);
	DDX_Text(pDX, IDC_EDIT_NET_RECEIVE_PORT, m_wRecvPort);
	DDX_Text(pDX, IDC_EDIT_DST_PORT, m_wDstPort);
	DDX_Text(pDX, IDC_EDIT_SOURCE_ADDR, m_csSourceAddr);
	DDX_Text(pDX, IDC_EDIT_SOURCE_PORT, m_wSourcePort);
	DDX_Text(pDX, IDC_EDIT_DST_ADDR, m_csDstAddr);
	DDX_Check(pDX, IDC_CHK_ENABLE_DST_ADDR, m_bEnableDstAddr);
	DDX_Check(pDX, IDC_CHK_ENABLE_DST_PORT, m_bEnableDstPort);
	DDX_Check(pDX, IDC_CHK_ENABLE_SOURCE_PORT, m_bEnableSourcePort);
	DDX_Text(pDX, IDC_EDIT_MULTICAST_ADDR, m_csMultiCastAddr);
	DDX_Text(pDX, IDC_EDIT_MULTICAST_PORT, m_wMultiCastPort);
	DDX_Text(pDX, IDC_EDIT_USB_RS232_SERIAL_PORT, m_byUSBToRS232SerialNum);
	//}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_RESTRICT_REMOTR_IP, m_szRestrictRemoteIP);
}


BEGIN_MESSAGE_MAP(CDlgPosConnectMode, CDialog)
	//{{AFX_MSG_MAP(CDlgPosConnectMode)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_CBN_SELCHANGE(IDC_COMBO_CONNECT_MODE, OnSelchangeComboConnectMode)
	ON_EN_KILLFOCUS(IDC_EDIT_NET_RECEIVE_PORT, OnKillfocusEditNetReceivePort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPosConnectMode message handlers

BOOL CDlgPosConnectMode::OnInitDialog() 
{
	CDialog::OnInitDialog();
	memset(&m_struConnectPosCfg,0,sizeof(m_struConnectPosCfg));
	ShowConnectInfo(MODE_NET_RECEIVE);
	m_comboConnectMode.SetCurSel(1);
	m_cmbFilterID.SetCurSel(0);

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPosConnectMode::ShowConnectInfo(UINT dwType)
{

	switch(dwType)
	{
	case MODE_NET_TCP_MONITER:
		ShowNetReceiveInfo(FALSE);
		ShowNetMonitorInfo(TRUE);
		ShowRS232Info(FALSE);
        ShowUSBToRS232Info(FALSE);
		break;
	case MODE_NET_RECEIVE:
		ShowNetReceiveInfo(TRUE);
		ShowNetMonitorInfo(FALSE);
		ShowRS232Info(FALSE);
        ShowUSBToRS232Info(FALSE);
		break;
	case MODE_RS232:
		ShowNetReceiveInfo(FALSE);
		ShowNetMonitorInfo(FALSE);
		ShowRS232Info(TRUE);
        ShowUSBToRS232Info(FALSE);
		break;
	case MODE_NET_UDP_MONITER:
		ShowNetReceiveInfo(FALSE);
		ShowNetMonitorInfo(TRUE);
		ShowRS232Info(FALSE);
        ShowUSBToRS232Info(FALSE);
		break;
	case MODE_MULTICAST:
		ShowNetReceiveInfo(FALSE);
		ShowNetMonitorInfo(FALSE);
		ShowRS232Info(FALSE);
        ShowUSBToRS232Info(FALSE);
		break;
	case MODE_SNIFF:
		ShowNetReceiveInfo(FALSE);
		ShowNetMonitorInfo(FALSE);
		ShowRS232Info(FALSE);
        ShowUSBToRS232Info(FALSE);
		break;
	case MODE_USB_RS232:
		ShowNetReceiveInfo(FALSE);
		ShowNetMonitorInfo(FALSE);
		ShowRS232Info(FALSE);
        ShowUSBToRS232Info(TRUE);
		break;
	default:
		ShowNetReceiveInfo(TRUE);
		ShowNetMonitorInfo(FALSE);
		ShowRS232Info(FALSE);
        ShowUSBToRS232Info(FALSE);
		break;
	}
}

//显示网络接受相关信息
void CDlgPosConnectMode::ShowNetReceiveInfo(BOOL bShow)
{
	GetDlgItem(IDC_STATIC_NET_RECEIVE)->ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_NET_RECEIVE_PORT)->ShowWindow(bShow);
	GetDlgItem(IDC_EDIT_NET_RECEIVE_PORT)->ShowWindow(bShow);
    GetDlgItem(IDC_EDIT_RESTRICT_REMOTR_IP)->ShowWindow(bShow);
    GetDlgItem(IDC_STATIC_ROMTE_IP)->ShowWindow(bShow);
}

//设置网络监听相关信息
void CDlgPosConnectMode::ShowNetMonitorInfo(BOOL bShow)
{
	GetDlgItem(IDC_STATIC_NET_MONITOR)->ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_NET_RECEIVE_PORT)->ShowWindow(bShow);
	GetDlgItem(IDC_EDIT_NET_RECEIVE_PORT)->ShowWindow(bShow);
    GetDlgItem(IDC_EDIT_RESTRICT_REMOTR_IP)->ShowWindow(bShow);
    GetDlgItem(IDC_STATIC_ROMTE_IP)->ShowWindow(bShow);
}

//显示RS232相关信息
void CDlgPosConnectMode::ShowRS232Info(BOOL bShow)
{
	GetDlgItem(IDC_STATIC_RS232)->ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_RS232_BAUDRATE)->ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_RS232_DATABIT)->ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_RS232_FLOWCTRL)->ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_RS232_PARITY)->ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_RS232_STOPBIT)->ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_RS2232_WORKMODE)->ShowWindow(bShow);
    GetDlgItem(IDC_STATIC_USB_RS2232)->ShowWindow(!bShow);
    
    GetDlgItem(IDC_COMBO_RS232_BAUDRATE)->ShowWindow(bShow);
    GetDlgItem(IDC_COMBO_RS232_DATABIT)->ShowWindow(bShow);
    GetDlgItem(IDC_COMBO_RS232_FLOWCTRL)->ShowWindow(bShow);
    GetDlgItem(IDC_COMBO_RS232_PARITY)->ShowWindow(bShow);
    GetDlgItem(IDC_COMBO_RS232_STOPBIT)->ShowWindow(bShow);
	GetDlgItem(IDC_COMBO_RS2232_WORKMODE)->ShowWindow(bShow);
    GetDlgItem(IDC_EDIT_USB_RS232_SERIAL_PORT)->ShowWindow(!bShow);
}


//显示RS232相关信息
void CDlgPosConnectMode::ShowUSBToRS232Info(BOOL bShow)
{
    GetDlgItem(IDC_STATIC_RS232)->ShowWindow(bShow);
    GetDlgItem(IDC_STATIC_RS232_BAUDRATE)->ShowWindow(bShow);
    GetDlgItem(IDC_STATIC_RS232_DATABIT)->ShowWindow(bShow);
    GetDlgItem(IDC_STATIC_RS232_FLOWCTRL)->ShowWindow(bShow);
    GetDlgItem(IDC_STATIC_RS232_PARITY)->ShowWindow(bShow);
    GetDlgItem(IDC_STATIC_RS232_STOPBIT)->ShowWindow(bShow);
    GetDlgItem(IDC_STATIC_RS2232_WORKMODE)->ShowWindow(!bShow);   
    GetDlgItem(IDC_STATIC_USB_RS2232)->ShowWindow(bShow);

    GetDlgItem(IDC_COMBO_RS232_BAUDRATE)->ShowWindow(bShow);
    GetDlgItem(IDC_COMBO_RS232_DATABIT)->ShowWindow(bShow);
    GetDlgItem(IDC_COMBO_RS232_FLOWCTRL)->ShowWindow(bShow);
    GetDlgItem(IDC_COMBO_RS232_PARITY)->ShowWindow(bShow);
    GetDlgItem(IDC_COMBO_RS232_STOPBIT)->ShowWindow(bShow);
	GetDlgItem(IDC_COMBO_RS2232_WORKMODE)->ShowWindow(!bShow);
    GetDlgItem(IDC_EDIT_USB_RS232_SERIAL_PORT)->ShowWindow(bShow);

}

void CDlgPosConnectMode::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	memset(&m_struConnectPosCfg, 0, sizeof(m_struConnectPosCfg));
	m_struConnectPosCfg.dwSize = sizeof(m_struConnectPosCfg);
 
	CString strLen = "";

	m_struConnectPosCfg.byConnectMode = m_comboConnectMode.GetCurSel();

	switch(m_struConnectPosCfg.byConnectMode)
	{
	case MODE_NET_TCP_MONITER:
		GetTcpMonitorInfo();
		break;
	case MODE_NET_RECEIVE:
		GetNetSeceiveInfo();
		break;
	case MODE_RS232:
		GetRS232Info();
		break;
	case MODE_NET_UDP_MONITER:
		GetTcpMonitorInfo();
		break;
	case MODE_SNIFF:
		GetSniffInfo();
		break;
	case MODE_MULTICAST:
		GetMultiCastInfo();
		break;
	case MODE_USB_RS232:
		GetUSBToRS232Info();
		break;
	default:
		GetTcpMonitorInfo();
		break;
	}

	DWORD dwFilterID = m_cmbFilterID.GetCurSel()+1;
	
	if (NET_DVR_SetDVRConfig(m_iUserID, NET_DVR_SET_CONNECT_POS_CFG, dwFilterID, &m_struConnectPosCfg, sizeof(m_struConnectPosCfg)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_CONNECT_POS_CFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_CONNECT_POS_CFG");
	}
}

void CDlgPosConnectMode::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReturn = 0;
	memset(&m_struConnectPosCfg, 0, sizeof(m_struConnectPosCfg));
	m_struConnectPosCfg.dwSize = sizeof(m_struConnectPosCfg);
 
	DWORD dwFilterID = m_cmbFilterID.GetCurSel() +1;
	if (NET_DVR_GetDVRConfig(m_iUserID, NET_DVR_GET_CONNECT_POS_CFG,dwFilterID , &m_struConnectPosCfg, sizeof(m_struConnectPosCfg), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_CONNECT_POS_CFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_CONNECT_POS_CFG");
		return;
	}

	//显示信息
	switch (m_struConnectPosCfg.byConnectMode)
	{
	case MODE_NET_RECEIVE:
		SetNetSeceiveInfo();
		break;
	case MODE_NET_TCP_MONITER:
		SetTcpMonitorInfo();
		break;
	case MODE_RS232:
		SetRS232Info();
		break;
	default:
		SetTcpMonitorInfo();
		break;
	}

	UpdateData(FALSE);

}

void CDlgPosConnectMode::GetNetSeceiveInfo()
{
	UpdateData(TRUE);
	char szLan[128] = {0};
	if (m_iUserID < 0)
	{
		g_StringLanType(szLan,"请先登录设备!", "Please Login Frist!");
		AfxMessageBox(szLan);
		return;
	}

	if (m_wRecvPort <= 0)
	{
		g_StringLanType(szLan, "非法的端口号!", "illeage port!");
		AfxMessageBox(szLan);
		return;
	}
	m_struConnectPosCfg.uPosConnMode.struNetRecv.wNetPort = m_wRecvPort;
	UpdateData(FALSE);
}

void CDlgPosConnectMode::GetTcpMonitorInfo()
{
	UpdateData(TRUE);
	m_struConnectPosCfg.uPosConnMode.struTcpMonitor.wPort = m_wRecvPort;
	 	
    strncpy(m_struConnectPosCfg.uPosConnMode.struTcpMonitor.struRestrictRemoteIP.sIpV4, m_szRestrictRemoteIP, 16);
	UpdateData(FALSE);
}

void CDlgPosConnectMode::GetUdpMonitorInfo()
{
	UpdateData(TRUE);
	m_struConnectPosCfg.uPosConnMode.struUdpMonitor.wPort = m_wRecvPort;
    strncpy(m_struConnectPosCfg.uPosConnMode.struTcpMonitor.struRestrictRemoteIP.sIpV4, m_szRestrictRemoteIP, 16);
	UpdateData(FALSE);
}

void CDlgPosConnectMode::GetRS232Info()
{
	UpdateData(TRUE);

    m_struConnectPosCfg.uPosConnMode.struRS232.dwBaudRate = m_comboRS232BaudRate.GetCurSel();
	m_struConnectPosCfg.uPosConnMode.struRS232.byDataBit = m_comboRS232DataBit.GetCurSel();
	m_struConnectPosCfg.uPosConnMode.struRS232.byStopBit = m_comboRS232StopBit.GetCurSel();
	m_struConnectPosCfg.uPosConnMode.struRS232.byFlowcontrol = m_comboRS232FlowCtrl.GetCurSel();
	m_struConnectPosCfg.uPosConnMode.struRS232.byParity = m_comboRS232Parity.GetCurSel();
	m_struConnectPosCfg.uPosConnMode.struRS232.dwWorkMode = m_comboRS232WorkMode.GetCurSel();
	UpdateData(FALSE);

}
void CDlgPosConnectMode::GetUSBToRS232Info()
{
    UpdateData(TRUE);
    m_struConnectPosCfg.uPosConnMode.struUSBRS232.dwBaudRate = m_comboRS232BaudRate.GetCurSel();
    m_struConnectPosCfg.uPosConnMode.struUSBRS232.byDataBit = m_comboRS232DataBit.GetCurSel();
    m_struConnectPosCfg.uPosConnMode.struUSBRS232.byStopBit = m_comboRS232StopBit.GetCurSel();
    m_struConnectPosCfg.uPosConnMode.struUSBRS232.byFlowcontrol = m_comboRS232FlowCtrl.GetCurSel();
    m_struConnectPosCfg.uPosConnMode.struUSBRS232.byParity = m_comboRS232Parity.GetCurSel();
	m_struConnectPosCfg.uPosConnMode.struUSBRS232.byVirtualSerialPort = (BYTE)m_byUSBToRS232SerialNum;
    UpdateData(FALSE);
}

void CDlgPosConnectMode::GetSniffInfo()
{
	UpdateData(TRUE);
	m_struConnectPosCfg.uPosConnMode.struSniff.byEnableSourcePort = m_bEnableSourcePort;

	memcpy(m_struConnectPosCfg.uPosConnMode.struSniff.bySourceIpAddr, m_csSourceAddr,m_csSourceAddr.GetLength());
	m_struConnectPosCfg.uPosConnMode.struSniff.wSourcePort = m_wSourcePort;
	
	m_struConnectPosCfg.uPosConnMode.struSniff.byEnableDestAddr = m_bEnableDstAddr;
	memcpy(m_struConnectPosCfg.uPosConnMode.struSniff.byDestinationIpAddr, m_csDstAddr, m_csDstAddr.GetLength());
	m_struConnectPosCfg.uPosConnMode.struSniff.byEnableDestPort = m_bEnableDstPort;
	m_struConnectPosCfg.uPosConnMode.struSniff.wDestinationPort = m_wDstPort;
	UpdateData(FALSE);
}

void CDlgPosConnectMode::GetMultiCastInfo()
{
	UpdateData(TRUE);	

   	m_struConnectPosCfg.uPosConnMode.struMcast.wPort = m_wMultiCastPort;
	if (!m_csMultiCastAddr.Find(":"))
	{
		strncpy((char*)m_struConnectPosCfg.uPosConnMode.struMcast.struIP.byIPv6, m_csMultiCastAddr.GetBuffer(0), sizeof(m_struConnectPosCfg.uPosConnMode.struMcast.struIP.byIPv6));
	}
	else
	{
	strncpy(m_struConnectPosCfg.uPosConnMode.struMcast.struIP.sIpV4, m_csMultiCastAddr.GetBuffer(0), sizeof(m_struConnectPosCfg.uPosConnMode.struMcast.struIP.sIpV4));
	}

	UpdateData(FALSE);	
}
void CDlgPosConnectMode::SetNetSeceiveInfo()
{
	UpdateData(TRUE);	
   	m_wRecvPort = m_struConnectPosCfg.uPosConnMode.struNetRecv.wNetPort;
	UpdateData(FALSE);

}

void CDlgPosConnectMode::SetTcpMonitorInfo()
{
	UpdateData(TRUE);
	m_wRecvPort = m_struConnectPosCfg.uPosConnMode.struTcpMonitor.wPort;
    m_szRestrictRemoteIP = m_struConnectPosCfg.uPosConnMode.struTcpMonitor.struRestrictRemoteIP.sIpV4;
    UpdateData(FALSE);
}

void CDlgPosConnectMode::SetUDPMonitorInfo()
{
	UpdateData(TRUE);
	m_wRecvPort = m_struConnectPosCfg.uPosConnMode.struUdpMonitor.wPort;
    m_szRestrictRemoteIP = m_struConnectPosCfg.uPosConnMode.struUdpMonitor.struRestrictRemoteIP.sIpV4;
	UpdateData(FALSE);
}

void CDlgPosConnectMode::SetRS232Info()
{
	UpdateData(TRUE);	
    m_comboRS232BaudRate.SetCurSel(m_struConnectPosCfg.uPosConnMode.struRS232.dwBaudRate);
	m_comboRS232DataBit.SetCurSel(m_struConnectPosCfg.uPosConnMode.struRS232.byDataBit);
	m_comboRS232StopBit.SetCurSel(m_struConnectPosCfg.uPosConnMode.struRS232.byStopBit);
	m_comboRS232FlowCtrl.SetCurSel(m_struConnectPosCfg.uPosConnMode.struRS232.byFlowcontrol);
	m_comboRS232Parity.SetCurSel(m_struConnectPosCfg.uPosConnMode.struRS232.byParity);
	m_comboRS232WorkMode.SetCurSel(m_struConnectPosCfg.uPosConnMode.struRS232.dwWorkMode);
	UpdateData(FALSE);
}

void CDlgPosConnectMode::SetUsbToRS232Info()
{
	UpdateData(TRUE);	
    m_comboRS232BaudRate.SetCurSel(m_struConnectPosCfg.uPosConnMode.struUSBRS232.dwBaudRate);
	m_comboRS232DataBit.SetCurSel(m_struConnectPosCfg.uPosConnMode.struUSBRS232.byDataBit);
	m_comboRS232StopBit.SetCurSel(m_struConnectPosCfg.uPosConnMode.struUSBRS232.byStopBit);
	m_comboRS232FlowCtrl.SetCurSel(m_struConnectPosCfg.uPosConnMode.struUSBRS232.byFlowcontrol);
	m_comboRS232Parity.SetCurSel(m_struConnectPosCfg.uPosConnMode.struUSBRS232.byParity);
	m_byUSBToRS232SerialNum = m_struConnectPosCfg.uPosConnMode.struUSBRS232.byVirtualSerialPort;
	UpdateData(FALSE);
}
void CDlgPosConnectMode::OnSelchangeComboConnectMode() 
{
	// TODO: Add your control notification handler code here
	UINT dwSelectIndex = 0;
	dwSelectIndex = m_comboConnectMode.GetCurSel();
	ShowConnectInfo(dwSelectIndex);
}

void CDlgPosConnectMode::OnKillfocusEditNetReceivePort() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128]= {0};
	if (m_wRecvPort <10000)
	{
		g_StringLanType(szLan,"网路监听端口为10000--65535!","Internet listening port between 10000 and 65535!");
		AfxMessageBox(szLan);
		return;
	}
}
