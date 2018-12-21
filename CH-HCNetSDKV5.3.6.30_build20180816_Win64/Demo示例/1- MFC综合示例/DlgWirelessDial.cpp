// DlgWirelessDial1.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgWirelessDial.h"

// #ifdef _DEBUG
// #define new DEBUG_NEW
// #undef THIS_FILE
// static char THIS_FILE[] = __FILE__;
// #endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWirelessDial dialog


CDlgWirelessDial::CDlgWirelessDial(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWirelessDial::IDD, pParent)
    , m_iHour11(0)
    , m_iMin11(0)
    , m_iHour12(0)
    , m_iMin12(0)
    , m_iHour21(0)
    , m_iMin21(0)
    , m_iHour22(0)
    , m_iMin22(0)
    , m_iHour31(0)
    , m_iMin31(0)
    , m_iHour32(0)
    , m_iMin32(0)
    , m_iHour41(0)
    , m_iMin41(0)
    , m_iHour42(0)
    , m_iMin42(0)
    , m_iHour51(0)
    , m_iMin51(0)
    , m_iHour52(0)
    , m_iMin52(0)
    , m_iHour61(0)
    , m_iMin61(0)
    , m_iHour62(0)
    , m_iMin62(0)
    , m_iHour71(0)
    , m_iMin71(0)
    , m_iHour72(0)
    , m_iMin72(0)
    , m_iHour81(0)
    , m_iMin81(0)
    , m_iHour82(0)
    , m_iMin82(0)
    , m_lLoginID(-1)
    , m_iDeviceIndex(-1)
    , m_strNetAPN(_T(""))
{
	//{{AFX_DATA_INIT(CDlgWirelessDial)
	m_bEnableWirelessDial = FALSE;
	m_strAPNName = _T("");
	m_strDialStatus = _T("");
	m_strDialNum = _T("");
	m_strDNSAddr = _T("");
	m_strGatewayAddr = _T("");
	m_strIPAddr = _T("");
	m_strIPMask = _T("");
	m_nMTU = 0;
	m_nNetworkCardNo = 1;
	m_nOffTime = 0;
	m_strPassword = _T("");
	m_nSignalQuality = 0;
	m_strUIMCardNum = _T("");
	m_strUserName = _T("");
	//}}AFX_DATA_INIT

    memset(&m_struWirelessDialCfg, 0, sizeof(m_struWirelessDialCfg));
    memset(&m_struWirelessDialStatus, 0, sizeof(m_struWirelessDialStatus));
    memset(&m_struWirelessDialSchedule, 0, sizeof(m_struWirelessDialSchedule));
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
}


void CDlgWirelessDial::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgWirelessDial)
    DDX_Control(pDX, IDC_COMBO_ALARMIN_COPY_TIME, m_comboCopyTime);
    DDX_Control(pDX, IDC_COMBO_ALARMIN_WEEKDAY, m_comboWeekday);
    DDX_Control(pDX, IDC_CMB_VERIF_PROTOCOL, m_cmbVerifProtocol);
    DDX_Control(pDX, IDC_CMB_UIM_STATUS, m_cmbUIMStatus);
    DDX_Control(pDX, IDC_CMB_REALTIME_MODE, m_cmbRealtimeMode);
    DDX_Control(pDX, IDC_CMB_NETWORK_MODE, m_cmbNetworkMode);
    DDX_Control(pDX, IDC_CMB_DIALMODE, m_cmbDialMode);
    DDX_Check(pDX, IDC_CHK_ENABLE_WIRELESSDIAL, m_bEnableWirelessDial);
    DDX_Text(pDX, IDC_EDIT_APNNAME, m_strAPNName);
    DDX_Text(pDX, IDC_EDIT_DIAL_STATUS, m_strDialStatus);
    DDX_Text(pDX, IDC_EDIT_DIALNUM, m_strDialNum);
    DDX_Text(pDX, IDC_EDIT_DNS_ADDR, m_strDNSAddr);
    DDX_Text(pDX, IDC_EDIT_GATEWAY, m_strGatewayAddr);
    DDX_Text(pDX, IDC_EDIT_IP_ADDR, m_strIPAddr);
    DDX_Text(pDX, IDC_EDIT_IP_MASK, m_strIPMask);
    DDX_Text(pDX, IDC_EDIT_MTU, m_nMTU);
    DDX_Text(pDX, IDC_EDIT_NETWORK_CARD_NO, m_nNetworkCardNo);
    DDX_Text(pDX, IDC_EDIT_OFF_TIME, m_nOffTime);
    DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
    DDX_Text(pDX, IDC_EDIT_SIGNAL_QUALITY, m_nSignalQuality);
    DDX_Text(pDX, IDC_EDIT_UIM_CARDNUM, m_strUIMCardNum);
    DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUserName);
    DDX_Text(pDX, IDC_EDIT_HOUR11, m_iHour11);
    DDX_Text(pDX, IDC_EDIT_MIN11, m_iMin11);
    DDX_Text(pDX, IDC_EDIT_HOUR12, m_iHour12);
    DDX_Text(pDX, IDC_EDIT_MIN12, m_iMin12);
    DDX_Text(pDX, IDC_EDIT_HOUR21, m_iHour21);
    DDX_Text(pDX, IDC_EDIT_MIN21, m_iMin21);
    DDX_Text(pDX, IDC_EDIT_HOUR22, m_iHour22);
    DDX_Text(pDX, IDC_EDIT_MIN22, m_iMin22);
    DDX_Text(pDX, IDC_EDIT_HOUR31, m_iHour31);
    DDX_Text(pDX, IDC_EDIT_MIN31, m_iMin31);
    DDX_Text(pDX, IDC_EDIT_HOUR32, m_iHour32);
    DDX_Text(pDX, IDC_EDIT_MIN32, m_iMin32);
    DDX_Text(pDX, IDC_EDIT_HOUR41, m_iHour41);
    DDX_Text(pDX, IDC_EDIT_MIN41, m_iMin41);
    DDX_Text(pDX, IDC_EDIT_HOUR42, m_iHour42);
    DDX_Text(pDX, IDC_EDIT_MIN42, m_iMin42);
    DDX_Text(pDX, IDC_EDIT_HOUR51, m_iHour51);
    DDX_Text(pDX, IDC_EDIT_MIN51, m_iMin51);
    DDX_Text(pDX, IDC_EDIT_HOUR52, m_iHour52);
    DDX_Text(pDX, IDC_EDIT_MIN52, m_iMin52);
    DDX_Text(pDX, IDC_EDIT_HOUR61, m_iHour61);
    DDX_Text(pDX, IDC_EDIT_MIN61, m_iMin61);
    DDX_Text(pDX, IDC_EDIT_HOUR62, m_iHour62);
    DDX_Text(pDX, IDC_EDIT_MIN62, m_iMin62);
    DDX_Text(pDX, IDC_EDIT_HOUR71, m_iHour71);
    DDX_Text(pDX, IDC_EDIT_MIN71, m_iMin71);
    DDX_Text(pDX, IDC_EDIT_HOUR72, m_iHour72);
    DDX_Text(pDX, IDC_EDIT_MIN72, m_iMin72);
    DDX_Text(pDX, IDC_EDIT_HOUR81, m_iHour81);
    DDX_Text(pDX, IDC_EDIT_MIN81, m_iMin81);
    DDX_Text(pDX, IDC_EDIT_HOUR82, m_iHour82);
    DDX_Text(pDX, IDC_EDIT_MIN82, m_iMin82);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_PRIVATE_APN, m_strNetAPN);
	DDV_MaxChars(pDX, m_strNetAPN, 32);
}


BEGIN_MESSAGE_MAP(CDlgWirelessDial, CDialog)
	//{{AFX_MSG_MAP(CDlgWirelessDial)
	ON_BN_CLICKED(IDC_BTN_WIRELESS_DIAL_REFRESH, OnBtnWirelessDialRefresh)
	ON_BN_CLICKED(IDC_BTN_WIRELESS_DIAL_SAVE, OnBtnWirelessDialSave)
	ON_BN_CLICKED(IDC_BTN_STATUS_REFRESH, OnBtnStatusRefresh)
	ON_BN_CLICKED(IDC_BTN_CONNECT, OnBtnConnect)
	ON_BN_CLICKED(IDC_BTN_DISCONNECT, OnBtnDisconnect)
	ON_BN_CLICKED(IDC_BTN_DIAL_SCHEDULE, OnBtnDialSchedule)
	ON_BN_CLICKED(IDC_BTN_DIAL_SCHEDULE_REFRESH, OnBtnDialScheduleRefresh)
	ON_BN_CLICKED(IDC_BTN_ALARM_IN_TIME_OK, OnBtnAlarmInTimeOk)
	ON_BN_CLICKED(IDC_BTN_ALARMIN_TIME_COPY, OnBtnAlarminTimeCopy)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARMIN_WEEKDAY, OnSelchangeComboAlarminWeekday)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWirelessDial message handlers

void CDlgWirelessDial::OnBtnWirelessDialRefresh() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_nNetworkCardNo;
    struCfg.dwCondSize = sizeof(m_nNetworkCardNo);
    struCfg.lpOutBuffer = &m_struWirelessDialCfg;
    struCfg.dwOutSize = sizeof(m_struWirelessDialCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_WIRELESS_DIAL, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_WIRELESS_DIAL");
    }
    else
    {
       g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_WIRELESS_DIAL");
       m_bEnableWirelessDial = m_struWirelessDialCfg.byEnabled;
       m_cmbDialMode.SetCurSel(m_struWirelessDialCfg.byDialMode);
       m_cmbNetworkMode.SetCurSel(m_struWirelessDialCfg.byNetworkMode);
       m_strDialNum = m_struWirelessDialCfg.byDialNum;
       m_strUserName = m_struWirelessDialCfg.byUserName;
//     m_strPassword = m_struWirelessDialCfg.byPassword;
       char csUIMCardNum[NAME_LEN + 1];
       csUIMCardNum[NAME_LEN] = 0;
       memcpy(csUIMCardNum, m_struWirelessDialCfg.byUIMCardNum, NAME_LEN);
       m_strUIMCardNum = csUIMCardNum;

       char csAPNName[NAME_LEN+1];
       csAPNName[NAME_LEN] = 0;
       memcpy(csAPNName, m_struWirelessDialCfg.byAPNName, NAME_LEN);
       char csNetAPN[NAME_LEN + 1];
       csNetAPN[NAME_LEN] = 0;
       memcpy(csNetAPN, m_struWirelessDialCfg.byNetAPN, NAME_LEN);

       m_cmbVerifProtocol.SetCurSel(m_struWirelessDialCfg.byVerifProtocol);
       m_nMTU = m_struWirelessDialCfg.wMTU;
       m_nOffTime = m_struWirelessDialCfg.dwOffineTime;
       m_strAPNName = m_struWirelessDialCfg.byAPNName;
       m_strNetAPN = m_struWirelessDialCfg.byNetAPN;
    }
    UpdateData(FALSE);
}

void CDlgWirelessDial::OnBtnWirelessDialSave() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_struWirelessDialCfg.dwSize = sizeof(m_struWirelessDialCfg);
    m_struWirelessDialCfg.byEnabled = m_bEnableWirelessDial;
    m_struWirelessDialCfg.byDialMode = m_cmbDialMode.GetCurSel();
    m_struWirelessDialCfg.byNetworkMode = m_cmbNetworkMode.GetCurSel();
    memcpy(m_struWirelessDialCfg.byDialNum, m_strDialNum.GetBuffer(0), MAX_DIALNUM_LENGTH);
    memcpy(m_struWirelessDialCfg.byUserName, m_strUserName.GetBuffer(0), NAME_LEN);
    memcpy(m_struWirelessDialCfg.byPassword, m_strPassword.GetBuffer(0), NAME_LEN);
    memcpy(m_struWirelessDialCfg.byUIMCardNum, m_strUIMCardNum .GetBuffer(0), NAME_LEN);
    memcpy(m_struWirelessDialCfg.byAPNName, m_strAPNName.GetBuffer(0), NAME_LEN);
    memcpy(m_struWirelessDialCfg.byNetAPN, m_strNetAPN.GetBuffer(0), NAME_LEN);
    m_struWirelessDialCfg.byVerifProtocol = m_cmbVerifProtocol.GetCurSel();
    m_struWirelessDialCfg.wMTU = m_nMTU;
    m_struWirelessDialCfg.dwOffineTime = m_nOffTime;

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_nNetworkCardNo;
    struCfg.dwCondSize = sizeof(m_nNetworkCardNo);
    struCfg.lpInBuffer = &m_struWirelessDialCfg;
    struCfg.dwInSize = sizeof(m_struWirelessDialCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_WIRELESS_DIAL, &struCfg))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_WIRELESS_DIAL");
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_WIRELESS_DIAL");
    }
    UpdateData(FALSE);
}

void CDlgWirelessDial::OnBtnStatusRefresh() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_nNetworkCardNo;
    struCfg.dwCondSize = sizeof(m_nNetworkCardNo);
    struCfg.lpOutBuffer = &m_struWirelessDialStatus;
    struCfg.dwOutSize = sizeof(m_struWirelessDialStatus);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_WIRELESSDIAL_STATUS, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_WIRELESSDIAL_STATUS");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_WIRELESSDIAL_STATUS");
        SetItemData(m_cmbRealtimeMode, (char*)m_struWirelessDialStatus.byRealtimeMode);
        SetItemData(m_cmbUIMStatus, (char*)m_struWirelessDialStatus.byUIMStatus);
        m_nSignalQuality = m_struWirelessDialStatus.dwSignalQuality;
        m_strDialStatus = m_struWirelessDialStatus.byDialStatus;
        if (ValidIPv6(m_struWirelessDialStatus.struIpAddr.byIPv6))
        {
            m_strIPAddr.Format("%s", m_struWirelessDialStatus.struIpAddr.byIPv6);
        }
        else
        {
            m_strIPAddr.Format("%s", m_struWirelessDialStatus.struIpAddr.sIpV4);
	    }
        if (ValidIPv6(m_struWirelessDialStatus.struIPMask.byIPv6))
        {
            m_strIPMask.Format("%s", m_struWirelessDialStatus.struIPMask.byIPv6);
        }
        else
        {
            m_strIPMask.Format("%s", m_struWirelessDialStatus.struIPMask.sIpV4);
	    }
        if (ValidIPv6(m_struWirelessDialStatus.struGatewayIPMask.byIPv6))
        {
            m_strGatewayAddr.Format("%s", m_struWirelessDialStatus.struGatewayIPMask.byIPv6);
        }
        else
        {
            m_strGatewayAddr.Format("%s", m_struWirelessDialStatus.struGatewayIPMask.sIpV4);
	    }
        if (ValidIPv6(m_struWirelessDialStatus.struDnsServerIpAddr.byIPv6))
        {
            m_strDNSAddr.Format("%s", m_struWirelessDialStatus.struDnsServerIpAddr.byIPv6);
        }
        else
        {
            m_strDNSAddr.Format("%s", m_struWirelessDialStatus.struDnsServerIpAddr.sIpV4);
	    }
    }
    UpdateData(FALSE);
}

BOOL CDlgWirelessDial::ValidIPv6(BYTE *ip)
{
    if (strlen((char *)ip) >= 2 && strchr((char *)ip, ':') != NULL)
    {
        return TRUE;
    }
    return FALSE;
}

void CDlgWirelessDial::SetItemData(CComboBox &combo, char* szData)
{
    CString strTmp;
    for (int i = 0; i < combo.GetCount(); i++)
    {
        combo.GetLBText(i, strTmp);
        if (strTmp.Compare(szData) == 0)
        {
            combo.SetCurSel(i);
            break;
        }            
    }
}

void CDlgWirelessDial::OnBtnConnect() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    NET_DVR_WIRELESSDIAL_CONNECT_PARAM struConnect = {0};
    struConnect.dwSize = sizeof(struConnect);
    struConnect.dwInterface = m_nNetworkCardNo;
    struConnect.byEnableConnect = 1;
    
    NET_DVR_STD_CONTROL struControl = {0};
    struControl.lpCondBuffer = &struConnect;
    struControl.dwCondSize = sizeof(struConnect);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struControl.lpStatusBuffer = m_szStatusBuf;
    struControl.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_STDControl(m_lLoginID, NET_DVR_WIRELESSDIAL_CONNECT, &struControl))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_WIRELESSDIAL_CONNECT");
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_WIRELESSDIAL_CONNECT");
    }
}

void CDlgWirelessDial::OnBtnDisconnect() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    
    NET_DVR_WIRELESSDIAL_CONNECT_PARAM struConnect = {0};
    struConnect.dwSize = sizeof(struConnect);
    struConnect.dwInterface = m_nNetworkCardNo;
    struConnect.byEnableConnect = 0;
    
    NET_DVR_STD_CONTROL struControl = {0};
    struControl.lpCondBuffer = &struConnect;
    struControl.dwCondSize = sizeof(struConnect);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struControl.lpStatusBuffer = m_szStatusBuf;
    struControl.dwStatusSize = ISAPI_STATUS_LEN;
    
    if (!NET_DVR_STDControl(m_lLoginID, NET_DVR_WIRELESSDIAL_CONNECT, &struControl))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_WIRELESSDIAL_CONNECT");
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_WIRELESSDIAL_CONNECT");
    }
}

void CDlgWirelessDial::OnBtnDialSchedule() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_nNetworkCardNo;
    struCfg.dwCondSize = sizeof(m_nNetworkCardNo);
    struCfg.lpInBuffer = &m_struWirelessDialSchedule;
    struCfg.dwInSize = sizeof(m_struWirelessDialSchedule);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_WIRELESSDIAL_SCHEDULE, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_WIRELESSDIAL_SCHEDULE");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_WIRELESSDIAL_SCHEDULE");
        OutputDebugString(m_szStatusBuf);   
    }
}

void CDlgWirelessDial::OnBtnDialScheduleRefresh() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_nNetworkCardNo;
    struCfg.dwCondSize = sizeof(m_nNetworkCardNo);
    struCfg.lpOutBuffer = &m_struWirelessDialSchedule;
    struCfg.dwOutSize = sizeof(m_struWirelessDialSchedule);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_WIRELESSDIAL_SCHEDULE, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_WIRELESSDIAL_SCHEDULE");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_WIRELESSDIAL_SCHEDULE");
        
    }
    m_comboWeekday.SetCurSel(0);
    OnSelchangeComboAlarminWeekday();
}

void CDlgWirelessDial::OnBtnAlarmInTimeOk() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    
    int	i = m_comboWeekday.GetCurSel();	    
    /*    {*/
    m_struWirelessDialSchedule.struAlarmTime[i][0].byStartHour = (BYTE)m_iHour11;
    m_struWirelessDialSchedule.struAlarmTime[i][0].byStartMin = (BYTE)m_iMin11;
    m_struWirelessDialSchedule.struAlarmTime[i][0].byStopHour = (BYTE)m_iHour12;
    m_struWirelessDialSchedule.struAlarmTime[i][0].byStopMin = (BYTE)m_iMin12;
    m_struWirelessDialSchedule.struAlarmTime[i][1].byStartHour = (BYTE)m_iHour21;
    m_struWirelessDialSchedule.struAlarmTime[i][1].byStartMin = (BYTE)m_iMin21;
    m_struWirelessDialSchedule.struAlarmTime[i][1].byStopHour = (BYTE)m_iHour22;
    m_struWirelessDialSchedule.struAlarmTime[i][1].byStopMin = (BYTE)m_iMin22;
    m_struWirelessDialSchedule.struAlarmTime[i][2].byStartHour = (BYTE)m_iHour31;
    m_struWirelessDialSchedule.struAlarmTime[i][2].byStartMin = (BYTE)m_iMin31;
    m_struWirelessDialSchedule.struAlarmTime[i][2].byStopHour = (BYTE)m_iHour32;
    m_struWirelessDialSchedule.struAlarmTime[i][2].byStopMin = (BYTE)m_iMin32;
    m_struWirelessDialSchedule.struAlarmTime[i][3].byStartHour = (BYTE)m_iHour41;
    m_struWirelessDialSchedule.struAlarmTime[i][3].byStartMin = (BYTE)m_iMin41;
    m_struWirelessDialSchedule.struAlarmTime[i][3].byStopHour = (BYTE)m_iHour42;
    m_struWirelessDialSchedule.struAlarmTime[i][3].byStopMin = (BYTE)m_iMin42;
    m_struWirelessDialSchedule.struAlarmTime[i][4].byStartHour = (BYTE)m_iHour51;
    m_struWirelessDialSchedule.struAlarmTime[i][4].byStartMin = (BYTE)m_iMin51;
    m_struWirelessDialSchedule.struAlarmTime[i][4].byStopHour = (BYTE)m_iHour52;
    m_struWirelessDialSchedule.struAlarmTime[i][4].byStopMin = (BYTE)m_iMin52;
    m_struWirelessDialSchedule.struAlarmTime[i][5].byStartHour = (BYTE)m_iHour61;
    m_struWirelessDialSchedule.struAlarmTime[i][5].byStartMin = (BYTE)m_iMin61;
    m_struWirelessDialSchedule.struAlarmTime[i][5].byStopHour = (BYTE)m_iHour62;
    m_struWirelessDialSchedule.struAlarmTime[i][5].byStopMin = (BYTE)m_iMin62;
    m_struWirelessDialSchedule.struAlarmTime[i][6].byStartHour = (BYTE)m_iHour71;
    m_struWirelessDialSchedule.struAlarmTime[i][6].byStartMin = (BYTE)m_iMin71;
    m_struWirelessDialSchedule.struAlarmTime[i][6].byStopHour = (BYTE)m_iHour72;
    m_struWirelessDialSchedule.struAlarmTime[i][6].byStopMin = (BYTE)m_iMin72;
    m_struWirelessDialSchedule.struAlarmTime[i][7].byStartHour = (BYTE)m_iHour81;
    m_struWirelessDialSchedule.struAlarmTime[i][7].byStartMin = (BYTE)m_iMin81;
    m_struWirelessDialSchedule.struAlarmTime[i][7].byStopHour = (BYTE)m_iHour82;
    m_struWirelessDialSchedule.struAlarmTime[i][7].byStopMin = (BYTE)m_iMin82;
        
	GetDlgItem(IDC_BTN_ALARMIN_TIME_COPY)->EnableWindow(TRUE);
}

void CDlgWirelessDial::OnBtnAlarminTimeCopy() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int j,k;
    int i = m_comboWeekday.GetCurSel();
    int m_nCopyTime = m_comboCopyTime.GetCurSel() - 1;
    
    if (m_nCopyTime == -1)
    {
        for (j=0; j<MAX_DAYS; j++)
        {
            if (j == i)
            {
                continue;
            }
            for (k=0; k<MAX_TIMESEGMENT_V30; k++)
            {
                memcpy(&(m_struWirelessDialSchedule.struAlarmTime[j][k]), &(m_struWirelessDialSchedule.struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
            }
        }
    }
    else
    {
        for (k=0; k<MAX_TIMESEGMENT_V30; k++)
        {
            memcpy(&(m_struWirelessDialSchedule.struAlarmTime[m_nCopyTime][k]), &(m_struWirelessDialSchedule.struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
        }
    }
}

BOOL CDlgWirelessDial::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgWirelessDial::OnSelchangeComboAlarminWeekday() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int	i = m_comboWeekday.GetCurSel();	
    /*    {*/
    m_iHour11 = m_struWirelessDialSchedule.struAlarmTime[i][0].byStartHour;
    m_iMin11 = m_struWirelessDialSchedule.struAlarmTime[i][0].byStartMin;
    m_iHour12 = m_struWirelessDialSchedule.struAlarmTime[i][0].byStopHour;
    m_iMin12 = m_struWirelessDialSchedule.struAlarmTime[i][0].byStopMin;
    m_iHour21 = m_struWirelessDialSchedule.struAlarmTime[i][1].byStartHour;
    m_iMin21 = m_struWirelessDialSchedule.struAlarmTime[i][1].byStartMin;
    m_iHour22 = m_struWirelessDialSchedule.struAlarmTime[i][1].byStopHour;
    m_iMin22 = m_struWirelessDialSchedule.struAlarmTime[i][1].byStopMin;
    m_iHour31 = m_struWirelessDialSchedule.struAlarmTime[i][2].byStartHour;
    m_iMin31 = m_struWirelessDialSchedule.struAlarmTime[i][2].byStartMin;
    m_iHour32 = m_struWirelessDialSchedule.struAlarmTime[i][2].byStopHour;
    m_iMin32 = m_struWirelessDialSchedule.struAlarmTime[i][2].byStopMin;
    m_iHour41 = m_struWirelessDialSchedule.struAlarmTime[i][3].byStartHour;
    m_iMin41 = m_struWirelessDialSchedule.struAlarmTime[i][3].byStartMin;
    m_iHour42 = m_struWirelessDialSchedule.struAlarmTime[i][3].byStopHour;
    m_iMin42 = m_struWirelessDialSchedule.struAlarmTime[i][3].byStopMin;
    m_iHour51 = m_struWirelessDialSchedule.struAlarmTime[i][4].byStartHour;
    m_iMin51 = m_struWirelessDialSchedule.struAlarmTime[i][4].byStartMin;
    m_iHour52 = m_struWirelessDialSchedule.struAlarmTime[i][4].byStopHour;
    m_iMin52 = m_struWirelessDialSchedule.struAlarmTime[i][4].byStopMin;
    m_iHour61 = m_struWirelessDialSchedule.struAlarmTime[i][5].byStartHour;
    m_iMin61 = m_struWirelessDialSchedule.struAlarmTime[i][5].byStartMin;
    m_iHour62 = m_struWirelessDialSchedule.struAlarmTime[i][5].byStopHour;
    m_iMin62 = m_struWirelessDialSchedule.struAlarmTime[i][5].byStopMin;
    m_iHour71 = m_struWirelessDialSchedule.struAlarmTime[i][6].byStartHour;
    m_iMin71 = m_struWirelessDialSchedule.struAlarmTime[i][6].byStartMin;
    m_iHour72 = m_struWirelessDialSchedule.struAlarmTime[i][6].byStopHour;
    m_iMin72 = m_struWirelessDialSchedule.struAlarmTime[i][6].byStopMin;
    m_iHour81 = m_struWirelessDialSchedule.struAlarmTime[i][7].byStartHour;
    m_iMin81 = m_struWirelessDialSchedule.struAlarmTime[i][7].byStartMin;
    m_iHour82 = m_struWirelessDialSchedule.struAlarmTime[i][7].byStopHour;
    m_iMin82 = m_struWirelessDialSchedule.struAlarmTime[i][7].byStopMin;
    /*    }*/
    
    UpdateData(FALSE);	
}
