// MatVedioPlatform.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "MatVedioPlatform.h"
#include "DlgRemoteFanException.h"
#include "DlgRemotePullException.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMatVedioPlatform dialog

LPNET_DVR_TEMPERATUREALARMCFG g_TemperatureAlarmCfg = NULL;
LPNET_DVR_BOARDALARMCFG       g_BoardAlarmCfg = NULL;

CMatVedioPlatform::CMatVedioPlatform(CWnd* pParent /*=NULL*/)
	: CDialog(CMatVedioPlatform::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMatVedioPlatform)
	m_strDnsIp = _T("");
	m_strDomainName = _T("");
	m_iSubSystemChan = 0;
	m_strSubSystemIp = _T("");
	m_strSubSystemPsw = _T("");
	m_dwSubSystemPort = 0;
	m_strSubSystemUser = _T("");
	m_strSerial = _T("");
	m_strMaskIp = _T("");
	m_strGateWayIp = _T("");
	m_strNat1IP = _T("");
	m_strNat2Ip = _T("");
	m_strNat1Gateway = _T("");
	m_strNat1Mask = _T("");
	m_strNat2Gateway = _T("");
	m_strNat2Mask = _T("");
	m_bAudioAlarm = FALSE;
	m_bJpegCapture = FALSE;
	m_bMonitorAlarm = FALSE;
	m_bReportCenter = FALSE;
	m_iSubSlotNum = 0;
	m_iNums = 0;
	m_iSlotNum = 0;
	m_iConnectSlot = 0;
	m_iConnectSubWnd = 0;
	m_iConnectDispChan = 0;
	//}}AFX_DATA_INIT
}


void CMatVedioPlatform::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMatVedioPlatform)
	DDX_Control(pDX, IDC_COMBO_SCENE, m_SceneCtrl);
	DDX_Control(pDX, IDC_COMBO_TRUNKSTATUS, m_TrunkStatusCtrl);
	DDX_Control(pDX, IDC_COMBO_DECCONNECTSTATUS, m_DecConnectStatusCtrl);
	DDX_Control(pDX, IDC_COMBO_DECCHAN, m_DecChanCtrl);
	DDX_Control(pDX, IDC_COMBO_CURRENTDECABILITY, m_CurrentDecAbilityCtrl);
	DDX_Control(pDX, IDC_COMBO_CONNECTSTATUS, m_ConnectStatusCtrl);
	DDX_Control(pDX, IDC_COMBO_BINDSTATUS, m_BindStatusCtrl);
	DDX_Control(pDX, IDC_COMBO_ALARMTYPE, m_AlarmTypeCtrl);
	DDX_Control(pDX, IDC_COMBO_USENAT, m_UseNatCtrl);
	DDX_Control(pDX, IDC_COMBOSUBSYSTEMTYPE, m_SubSystemTypeCtrl);
	DDX_Control(pDX, IDC_COMBOSUBSYSTEMNUM, m_SubSystemCtrl);
	DDX_Control(pDX, IDC_COMBOLOGINTYPE, m_LoginTypeCtrl);
	DDX_Text(pDX, IDC_DNSIP, m_strDnsIp);
	DDX_Text(pDX, IDC_DOMAINNAME, m_strDomainName);
	DDX_Text(pDX, IDC_EDITSUBSYSTEMCHAN, m_iSubSystemChan);
	DDX_Text(pDX, IDC_EDITSUBSYSTEMIP, m_strSubSystemIp);
	DDX_Text(pDX, IDC_EDITSUBSYSTEMPASSWD, m_strSubSystemPsw);
	DDX_Text(pDX, IDC_EDITSUBSYSTEMPORT, m_dwSubSystemPort);
	DDX_Text(pDX, IDC_EDITSUBSYSTEMUSER, m_strSubSystemUser);
	DDX_Text(pDX, IDC_SERIALNUM, m_strSerial);
	DDX_Text(pDX, IDC_MASKIP, m_strMaskIp);
	DDX_Text(pDX, IDC_GATEWAYIP, m_strGateWayIp);
	DDX_Text(pDX, IDC_EDIT_IPADDRESS1, m_strNat1IP);
	DDX_Text(pDX, IDC_EDIT_IPADDRESS2, m_strNat2Ip);
	DDX_Text(pDX, IDC_EDIT_NAT1GATEWAY, m_strNat1Gateway);
	DDX_Text(pDX, IDC_EDIT_NAT1IPMASK, m_strNat1Mask);
	DDX_Text(pDX, IDC_EDIT_NAT2GATEWAY, m_strNat2Gateway);
	DDX_Text(pDX, IDC_EDIT_NAT2IPMASK, m_strNat2Mask);
	DDX_Check(pDX, IDC_CHK_AUDIO_ALARM, m_bAudioAlarm);
	DDX_Check(pDX, IDC_CHK_INVOKE_JPEG_CAPTURE, m_bJpegCapture);
	DDX_Check(pDX, IDC_CHK_MONITOR_ALARM, m_bMonitorAlarm);
	DDX_Check(pDX, IDC_CHK_REPORT_CENTER, m_bReportCenter);
	DDX_Text(pDX, IDC_EDITSUBSLOTNUM, m_iSubSlotNum);
	DDX_Text(pDX, IDC_EDIT_NUM1, m_iNums);
	DDX_Text(pDX, IDC_EDIT_SLOTNUM, m_iSlotNum);
	DDX_Text(pDX, IDC_EDIT_CONNECTSLOT, m_iConnectSlot);
	DDX_Text(pDX, IDC_EDIT_CONNECTSUBWND, m_iConnectSubWnd);
	DDX_Text(pDX, IDC_EDIT_CONNECTDISPCHAN, m_iConnectDispChan);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMatVedioPlatform, CDialog)
	//{{AFX_MSG_MAP(CMatVedioPlatform)
	ON_BN_CLICKED(IDC_SETVEDIOPLATFORM, OnSetvedioplatform)
	ON_BN_CLICKED(IDC_SAVEPARA, OnSavepara)
	ON_CBN_SELCHANGE(IDC_COMBOLOGINTYPE, OnSelchangeCombologintype)
	ON_CBN_SELCHANGE(IDC_COMBOSUBSYSTEMNUM, OnSelchangeCombosubsystemnum)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GETTEMPALARM, OnBtnGettempalarm)
	ON_BN_CLICKED(IDC_BTN_SETTEMPALARM, OnBtnSettempalarm)
	ON_BN_CLICKED(IDC_BUTTON_TEMP, OnButtonTemp)
	ON_BN_CLICKED(IDC_BUTTON_PULL, OnButtonPull)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARMTYPE, OnSelchangeComboAlarmtype)
	ON_BN_CLICKED(IDC_BUTTON_SURE, OnButtonSure)
	ON_CBN_SELCHANGE(IDC_COMBO_DECCHAN, OnSelchangeComboDecchan)
	ON_BN_CLICKED(IDC_BUTTON_SWITCH, OnButtonSwitch)
	ON_BN_CLICKED(IDC_BUTTON_INIT, OnButtonInit)
	ON_BN_CLICKED(IDC_BUTTON_FORCESWITCH, OnButtonForceswitch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatVedioPlatform message handlers

void CMatVedioPlatform::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CMatVedioPlatform::OnSetvedioplatform() 
{
	// TODO: Add your control notification handler code here
	if (!NET_DVR_MatrixSetSubSystemInfo_V40(m_lServerID, &m_AllSubSystemInfo))
    {
        MessageBox(NET_DVR_GetErrorMsg());
        return;
	}

    MessageBox("Succ");
}

void CMatVedioPlatform::OnSavepara() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int sel = m_SubSystemCtrl.GetCurSel();
    m_AllSubSystemInfo.struSubSystemInfo[sel].byChan = m_iSubSystemChan;
    m_AllSubSystemInfo.struSubSystemInfo[sel].byLoginType = m_LoginTypeCtrl.GetCurSel() + 1;
    memcpy(m_AllSubSystemInfo.struSubSystemInfo[sel].sDomainName, m_strDomainName, MAX_DOMAIN_NAME);
    memcpy(m_AllSubSystemInfo.struSubSystemInfo[sel].sPassword, m_strSubSystemPsw, PASSWD_LEN);
    memcpy(m_AllSubSystemInfo.struSubSystemInfo[sel].sDnsAddress, m_strDnsIp, 64);
    memcpy(m_AllSubSystemInfo.struSubSystemInfo[sel].struSubSystemIP.sIpV4, m_strSubSystemIp, 16);
    m_AllSubSystemInfo.struSubSystemInfo[sel].wSubSystemPort = m_dwSubSystemPort;
    memcpy(m_AllSubSystemInfo.struSubSystemInfo[sel].struGatewayIpAddr.sIpV4, m_strGateWayIp, 16);
    memcpy(m_AllSubSystemInfo.struSubSystemInfo[sel].struSubSystemIPMask.sIpV4, m_strMaskIp, 16);
}

BOOL CMatVedioPlatform::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	for(int i = 0; i < MAX_SUBSYSTEM_NUM_V40; i++)
    {
        CString tmp;
        tmp.Format("%d", i + 1);
        m_SubSystemCtrl.AddString(tmp);
    }

    for (int j = 0; j < MAX_DECODECHANNUM; j++)
    {
        CString tmp;
        tmp.Format("%d", j + 1);
        m_DecChanCtrl.AddString(tmp);
    }
    memset(&m_AllSubSystemInfo, 0, sizeof(m_AllSubSystemInfo));
    if (!NET_DVR_MatrixGetSubSystemInfo_V40(m_lServerID, &m_AllSubSystemInfo))
    {
        MessageBox(NET_DVR_GetErrorMsg());
        return FALSE;
    }
    
    m_SubSystemCtrl.SetCurSel(0);
    m_SubSystemTypeCtrl.SetCurSel(m_AllSubSystemInfo.struSubSystemInfo[0].bySubSystemType);
    m_LoginTypeCtrl.SetCurSel(m_AllSubSystemInfo.struSubSystemInfo[0].byLoginType);
    m_strDnsIp = m_AllSubSystemInfo.struSubSystemInfo[0].sDnsAddress;
    m_strDomainName = m_AllSubSystemInfo.struSubSystemInfo[0].sDomainName;
    m_iSubSystemChan = m_AllSubSystemInfo.struSubSystemInfo[0].byChan;
    m_strSubSystemIp = m_AllSubSystemInfo.struSubSystemInfo[0].struSubSystemIP.sIpV4;
    m_strSubSystemPsw = m_AllSubSystemInfo.struSubSystemInfo[0].sPassword;
    m_dwSubSystemPort = m_AllSubSystemInfo.struSubSystemInfo[0].wSubSystemPort;
    m_strSubSystemUser = m_AllSubSystemInfo.struSubSystemInfo[0].sUserName;
    m_strSerial = m_AllSubSystemInfo.struSubSystemInfo[0].sSerialNumber;
    m_strMaskIp = m_AllSubSystemInfo.struSubSystemInfo[0].struSubSystemIPMask.sIpV4;
    m_strGateWayIp = m_AllSubSystemInfo.struSubSystemInfo[0].struGatewayIpAddr.sIpV4;
    
    memset(&m_struSubSystemStatus, 0, sizeof(m_struSubSystemStatus));
    if (!NET_DVR_MatrixGetSubDecSystemJoinInfo_V41(m_lServerID, &m_struSubSystemStatus))
    {
        MessageBox(NET_DVR_GetErrorMsg());
        //return FALSE;
    }
    m_ConnectStatusCtrl.SetCurSel(m_struSubSystemStatus.struSingleSubSystemJoinInfo[0].byConnectStatus);
    m_iNums = m_struSubSystemStatus.struSingleSubSystemJoinInfo[0].byMatrixNum;
    m_iSlotNum = m_struSubSystemStatus.struSingleSubSystemJoinInfo[0].bySlotNum;
    m_BindStatusCtrl.SetCurSel(m_struSubSystemStatus.struSingleSubSystemJoinInfo[0].byBindStatus);
    m_TrunkStatusCtrl.SetCurSel(m_struSubSystemStatus.struSingleSubSystemJoinInfo[0].byUsedTrunk);

    NET_DVR_VIDEOPLATFORM_ABILITY_V40 struAbility = {0};
    if (!NET_DVR_GetDeviceAbility(m_lServerID, VIDEOPLATFORM_ABILITY_V40, NULL, 0, (char *)&struAbility, sizeof(struAbility)))
    {
        MessageBox(NET_DVR_GetErrorMsg());
    }
    else
    {
        for (int m = 0; m < struAbility.bySupportSceneNums; m++)
        {
            CString tmp;
            tmp.Format("%d", m + 1);
            m_SceneCtrl.AddString(tmp);
        }
    }
    m_SceneCtrl.SetCurSel(0);
    m_DecChanCtrl.SetCurSel(0);
    UpdateData(FALSE);
	OnBtnGet();
    OnBtnGettempalarm();
    m_AlarmTypeCtrl.SetCurSel(0);
    OnSelchangeComboAlarmtype();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMatVedioPlatform::OnSelchangeCombologintype() 
{
	// TODO: Add your control notification handler code here    
}

void CMatVedioPlatform::OnSelchangeCombosubsystemnum() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int sel = m_SubSystemCtrl.GetCurSel();
    m_SubSystemTypeCtrl.SetCurSel(m_AllSubSystemInfo.struSubSystemInfo[sel].bySubSystemType);
    m_LoginTypeCtrl.SetCurSel(m_AllSubSystemInfo.struSubSystemInfo[sel].byLoginType - 1);
    m_strDnsIp = m_AllSubSystemInfo.struSubSystemInfo[sel].struSubSystemIP.sIpV4;
    m_strDomainName = m_AllSubSystemInfo.struSubSystemInfo[sel].sDomainName;
    m_iSubSystemChan = m_AllSubSystemInfo.struSubSystemInfo[sel].byChan;
    m_strSubSystemIp = m_AllSubSystemInfo.struSubSystemInfo[sel].struSubSystemIP.sIpV4;
    m_strSubSystemPsw = m_AllSubSystemInfo.struSubSystemInfo[sel].sPassword;
    m_dwSubSystemPort = m_AllSubSystemInfo.struSubSystemInfo[sel].wSubSystemPort;
    m_strSubSystemUser = m_AllSubSystemInfo.struSubSystemInfo[sel].sUserName;
    m_strSerial = m_AllSubSystemInfo.struSubSystemInfo[sel].sSerialNumber;
    m_strMaskIp = m_AllSubSystemInfo.struSubSystemInfo[sel].struSubSystemIPMask.sIpV4;
    m_strGateWayIp = m_AllSubSystemInfo.struSubSystemInfo[sel].struGatewayIpAddr.sIpV4;
	m_iSubSlotNum = m_AllSubSystemInfo.struSubSystemInfo[sel].bySlotNum;
    
    m_ConnectStatusCtrl.SetCurSel(m_struSubSystemStatus.struSingleSubSystemJoinInfo[sel].byConnectStatus);
    m_iNums = m_struSubSystemStatus.struSingleSubSystemJoinInfo[sel].byMatrixNum;
    m_iSlotNum = m_struSubSystemStatus.struSingleSubSystemJoinInfo[sel].bySlotNum;
    m_BindStatusCtrl.SetCurSel(m_struSubSystemStatus.struSingleSubSystemJoinInfo[sel].byBindStatus);
    m_TrunkStatusCtrl.SetCurSel(m_struSubSystemStatus.struSingleSubSystemJoinInfo[sel].byUsedTrunk);
    UpdateData(FALSE);
}

void CMatVedioPlatform::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturned = -1;
	memset(&m_struNatAssociateCfg, 0, sizeof(m_struNatAssociateCfg));
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_NATASSOCIATECFG_GET, -1, &m_struNatAssociateCfg, sizeof(m_struNatAssociateCfg), &dwReturned))
	{
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}

	m_UseNatCtrl.SetCurSel(m_struNatAssociateCfg.byNATEnable);
	m_strNat1IP = m_struNatAssociateCfg.struNatIpAddress[0].struEtherNet->struDVRIP.sIpV4;
	m_strNat2Ip = m_struNatAssociateCfg.struNatIpAddress[1].struEtherNet->struDVRIP.sIpV4;
	m_strNat1Mask = m_struNatAssociateCfg.struNatIpAddress[0].struEtherNet->struDVRIPMask.sIpV4;
	m_strNat2Mask = m_struNatAssociateCfg.struNatIpAddress[1].struEtherNet->struDVRIPMask.sIpV4;
	m_strNat1Gateway = m_struNatAssociateCfg.struNatIpAddress[0].struGatewayIpAddr.sIpV4;
	m_strNat2Gateway = m_struNatAssociateCfg.struNatIpAddress[1].struGatewayIpAddr.sIpV4;
	UpdateData(FALSE);
	MessageBox("Get NAT parameter successfully!");
}

void CMatVedioPlatform::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
 	memset(&m_struNatAssociateCfg, 0, sizeof(m_struNatAssociateCfg));
	m_struNatAssociateCfg.byNATEnable = m_UseNatCtrl.GetCurSel();
    memcpy(&m_struNatAssociateCfg.struNatIpAddress[0].struGatewayIpAddr.sIpV4, m_strNat1Gateway, 16);
	memcpy(&m_struNatAssociateCfg.struNatIpAddress[0].struEtherNet->struDVRIP.sIpV4, m_strNat1IP, 16);
	memcpy(&m_struNatAssociateCfg.struNatIpAddress[0].struEtherNet->struDVRIPMask, m_strNat1Mask, 16);

	memcpy(&m_struNatAssociateCfg.struNatIpAddress[1].struGatewayIpAddr.sIpV4, m_strNat2Gateway, 16);
	memcpy(&m_struNatAssociateCfg.struNatIpAddress[1].struEtherNet->struDVRIP.sIpV4, m_strNat2Ip, 16);
	memcpy(&m_struNatAssociateCfg.struNatIpAddress[1].struEtherNet->struDVRIPMask, m_strNat2Mask, 16);
	m_struNatAssociateCfg.dwSize = sizeof(m_struNatAssociateCfg);

	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_NATASSOCIATECFG_SET, -1, &m_struNatAssociateCfg, sizeof(m_struNatAssociateCfg)))
	{
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}

	MessageBox("Set NAT parameter successfully!");
}

void CMatVedioPlatform::OnBtnGettempalarm() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturned = -1;
	memset(&m_struAlarmTemperatureCfg, 0, sizeof(m_struAlarmTemperatureCfg));
	m_struAlarmTemperatureCfg.dwSize = sizeof(m_struAlarmTemperatureCfg);
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_VIDEOPLATFORMALARMCFG_GET, -1, &m_struAlarmTemperatureCfg, sizeof(m_struAlarmTemperatureCfg), &dwReturned))
	{
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}

    g_TemperatureAlarmCfg = &(m_struAlarmTemperatureCfg.struTempAlarmCfg);
    g_BoardAlarmCfg       = &(m_struAlarmTemperatureCfg.struBoardAlarmCfg);
    
	UpdateData(FALSE);
	MessageBox("Get Temperature Alarm parameter successfully!");
}

void CMatVedioPlatform::OnBtnSettempalarm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	//memset(&m_struAlarmTemperatureCfg, 0, sizeof(m_struAlarmTemperatureCfg));
	m_struAlarmTemperatureCfg.dwSize = sizeof(m_struAlarmTemperatureCfg);

	//m_struAlarmTemperatureCfg.struBoardAlarmCfg.byEnablePullAlarm = m_bPullAlarm;
	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_VIDEOPLATFORMALARMCFG_SET, -1, &m_struAlarmTemperatureCfg, sizeof(m_struAlarmTemperatureCfg)))
	{
		MessageBox(NET_DVR_GetErrorMsg());
		return;
	}
	
	MessageBox("Set Temperature Alarm parameter successfully!");
}

void CMatVedioPlatform::OnButtonTemp() 
{
	// TODO: Add your control notification handler code here
    CDlgRemoteFanException dlgRemoteTempException;
   
    g_TemperatureAlarmCfg = &(m_struAlarmTemperatureCfg.struTempAlarmCfg);
    dlgRemoteTempException.m_lLoginID = m_lServerID;
    dlgRemoteTempException.m_dwAlarmOutNum = 0;
    dlgRemoteTempException.DoModal();
}


void CMatVedioPlatform::OnButtonPull() 
{
	// TODO: Add your control notification handler code here
    CDlgRemotePullException dlgRemotePullException;
    
    g_BoardAlarmCfg = &(m_struAlarmTemperatureCfg.struBoardAlarmCfg);
    dlgRemotePullException.m_lLoginID = m_lServerID;
    dlgRemotePullException.m_dwAlarmOutNum = 0;
    dlgRemotePullException.DoModal();
}

void CMatVedioPlatform::OnSelchangeComboAlarmtype() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    int i = m_AlarmTypeCtrl.GetCurSel();
    
    m_bMonitorAlarm = m_struAlarmTemperatureCfg.struHandleException[i].dwHandleType &0x01;
    m_bAudioAlarm = (m_struAlarmTemperatureCfg.struHandleException[i].dwHandleType>>1)&0x01;
    m_bReportCenter = (m_struAlarmTemperatureCfg.struHandleException[i].dwHandleType>>2)&0x01;
    //m_bChkInvokeAlarmOut = (m_struAlarmTemperatureCfg.struHandleException[i].dwHandleType>>3)&0x01;
    m_bJpegCapture = (m_struAlarmTemperatureCfg.struHandleException[i].dwHandleType>>4)&0x01;
    UpdateData(FALSE);
}

void CMatVedioPlatform::OnButtonSure() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int i = m_AlarmTypeCtrl.GetCurSel();
    m_struAlarmTemperatureCfg.struHandleException[i].dwHandleType = 0;
    m_struAlarmTemperatureCfg.struHandleException[i].dwHandleType |= (m_bMonitorAlarm << 0);
    m_struAlarmTemperatureCfg.struHandleException[i].dwHandleType |= (m_bAudioAlarm << 1);
    m_struAlarmTemperatureCfg.struHandleException[i].dwHandleType |= (m_bReportCenter << 2);
    //m_struAlarmTemperatureCfg.struHandleException[i].dwHandleType |= (m_bChkInvokeAlarmOut << 3);
    m_struAlarmTemperatureCfg.struHandleException[i].dwHandleType |= (m_bJpegCapture << 4);
}

void CMatVedioPlatform::OnSelchangeComboDecchan() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    
    int sel = m_SubSystemCtrl.GetCurSel();
    int iDecChan = m_DecChanCtrl.GetCurSel();

    m_DecConnectStatusCtrl.SetCurSel(m_struSubSystemStatus.struSingleSubSystemJoinInfo[sel].struSubSystem[iDecChan].byJoinStatus);
    m_iConnectDispChan = m_struSubSystemStatus.struSingleSubSystemJoinInfo[sel].struSubSystem[iDecChan].byJoinDispNum;
    m_iConnectSlot = m_struSubSystemStatus.struSingleSubSystemJoinInfo[sel].struSubSystem[iDecChan].byJoinSubSystem;
    m_iConnectSubWnd = m_struSubSystemStatus.struSingleSubSystemJoinInfo[sel].struSubSystem[iDecChan].byJoinSubWindowNum;
    m_CurrentDecAbilityCtrl.SetCurSel(m_struSubSystemStatus.struSingleSubSystemJoinInfo[sel].struSubSystem[iDecChan].byDecodeAbility);
    UpdateData(FALSE);
}

void CMatVedioPlatform::OnButtonSwitch() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
	if (!NET_DVR_MatrixSceneControl(m_lServerID, m_SceneCtrl.GetCurSel() + 1, 1, 0))
	{
        MessageBox(NET_DVR_GetErrorMsg());
        return;
	}

    MessageBox("scene switch success!");
}

void CMatVedioPlatform::OnButtonInit() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if (!NET_DVR_MatrixSceneControl(m_lServerID, m_SceneCtrl.GetCurSel() + 1, 2, 0))
    {
        MessageBox(NET_DVR_GetErrorMsg());
        return;
    }
    
    MessageBox("scene init success!");
}

void CMatVedioPlatform::OnButtonForceswitch() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if (!NET_DVR_MatrixSceneControl(m_lServerID, m_SceneCtrl.GetCurSel() + 1, 3, 0))
    {
        MessageBox(NET_DVR_GetErrorMsg());
        return;
    }
    
    MessageBox("scene force switch success!");
}
