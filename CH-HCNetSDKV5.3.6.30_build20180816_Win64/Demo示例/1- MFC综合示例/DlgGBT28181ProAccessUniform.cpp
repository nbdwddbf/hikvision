// DlgGBT28181ProtocolAccess2.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgGBT28181ProAccessUniform.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGBT28181ProAccessUniform dialog

//更新比较条件函数
bool ChannelCmp (const void *ItemF, const void *ItemS)
{
    const NET_DVR_STREAM_INFO * CfgItemF = (const NET_DVR_STREAM_INFO *) ItemF; 
    const NET_DVR_STREAM_INFO * CfgItemS = (const NET_DVR_STREAM_INFO *) ItemS; 
    return (CfgItemF->dwChannel == CfgItemS->dwChannel);
}
 
CDlgGBT28181ProAccessUniform::CDlgGBT28181ProAccessUniform(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGBT28181ProAccessUniform::IDD, pParent)
    , m_byTCPConnectMod(0)
{
	//{{AFX_DATA_INIT(CDlgGBT28181ProAccessUniform)
	m_bGBT28181Enable = FALSE;
	m_csIP = _T("");
	m_iHeartBeatInterval = 0;
	m_iLocalSipPort = 0;
	m_iRegisterValid = 0;
	m_csServerID = _T("");
	m_iServerSipPort = 0;
	m_csSipAuthenticateID = _T("");
	m_csSipAuthenticatePasswd = _T("");
	m_csSipUserName = _T("");
	m_iMaxHeartbeatTimeOut = 0;
	m_csAlarmInID = _T("");
	m_csVideoChannelID = _T("");
	m_csServerDomain = _T("");
	m_BCodeChan = FALSE;
	m_BDecodeChan = FALSE;
	m_BAlarmInChan = FALSE;
	m_dwServerID = 1;
	m_dwVideCodeChan = 0;
	m_BVideoChanNotRelate = FALSE;
	//}}AFX_DATA_INIT
	
	m_lServerID = -1;
	m_dwDevIndex = -1;
    m_dwAlarmOutNum = -1;
	m_dwAlarmInNum = -1;
    m_nChannel = -1;
    m_lStartChan = -1;
	memset(&m_struGBT28181Accesscfg, 0, sizeof(m_struGBT28181Accesscfg));
	memset(&m_struIPAlarmInCfg, 0, sizeof(m_struIPAlarmInCfg));

	m_pstruAlarmInInfoCond = NULL;
	m_pstruGBT28181AlarmInCfg = NULL;
	
	m_pstruStreamInfoCond = NULL;
	m_pstruGBT28181ChanInfoCfg = NULL;
	iAlarmInSel = 0;
}

CDlgGBT28181ProAccessUniform::~CDlgGBT28181ProAccessUniform()
{
	if (m_pstruAlarmInInfoCond != NULL)
	{
		delete [] m_pstruAlarmInInfoCond;
	}
	if (m_pstruGBT28181AlarmInCfg != NULL)
	{
		delete [] m_pstruGBT28181AlarmInCfg;
	}

	if (m_pstruStreamInfoCond != NULL)
	{
		delete [] m_pstruStreamInfoCond;
	}
	if (m_pstruGBT28181ChanInfoCfg != NULL)
	{
		delete [] m_pstruGBT28181ChanInfoCfg;
	}
}

void CDlgGBT28181ProAccessUniform::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgGBT28181ProAccessUniform)
    DDX_Control(pDX, IDC_COMBO_TRANS_PROTOCOL, m_comTransProtocol);
    DDX_Control(pDX, IDC_COMBO_PRO_VERSION, m_comProtocolVersion);
    DDX_Control(pDX, IDC_COMBO_28181_CHANTEPE, m_cmbChanType);
    DDX_Control(pDX, IDC_COMBO_DEV_STATUS, m_comDevStatus);
    DDX_Control(pDX, IDC_COMBO_VIDEO_CHANNEL, m_comboVideoChannel);
    DDX_Control(pDX, IDC_COMBO_ALARM_IN, m_comboAlarmIn);
    DDX_Control(pDX, IDC_COMBO_STREAM_TYPE, m_comboStreamType);
    DDX_Check(pDX, IDC_CHK_GBT28181_ENABLE, m_bGBT28181Enable);
    DDX_Text(pDX, IDC_EDIT_DEV_ADDRESSIP, m_csIP);
    DDX_Text(pDX, IDC_EDIT_HEARTBEAT_INTERVAL, m_iHeartBeatInterval);
    DDX_Text(pDX, IDC_EDIT_LOCALSIPPORT, m_iLocalSipPort);
    DDX_Text(pDX, IDC_EDIT_REGISTER_VALID, m_iRegisterValid);
    DDX_Text(pDX, IDC_EDIT_SERVERID, m_csServerID);
    DDX_Text(pDX, IDC_EDIT_SERVERSIPPORT, m_iServerSipPort);
    DDX_Text(pDX, IDC_EDIT_SIP_AUTHENTICATE_ID, m_csSipAuthenticateID);
    DDX_Text(pDX, IDC_EDIT_SIP_AUTHENTICATE_PASSWD, m_csSipAuthenticatePasswd);
    DDX_Text(pDX, IDC_EDIT_SIP_USERNAME, m_csSipUserName);
    DDX_Text(pDX, IDC_EDIT_MAXHEARTBEAT_TIMEOUT, m_iMaxHeartbeatTimeOut);
    DDX_Text(pDX, IDC_EDIT_ALARMIN_ID, m_csAlarmInID);
    DDX_Text(pDX, IDC_EDIT_VIDEOCHANNEL_ID, m_csVideoChannelID);
    DDX_Text(pDX, IDC_EDIT_SERVER_DOMAIN, m_csServerDomain);
    DDX_Check(pDX, IDC_CHK_CODE_CHANNEL, m_BCodeChan);
    DDX_Check(pDX, IDC_CHK_DECODE_CHANNEL, m_BDecodeChan);
    DDX_Check(pDX, IDC_CHK_ALARMIN_CHANNEL, m_BAlarmInChan);
    DDX_Text(pDX, IDC_EDIT_28181_SERVERID, m_dwServerID);
    DDX_Text(pDX, IDC_EDIT_28181_VIDEOCHAN, m_dwVideCodeChan);
    DDX_Check(pDX, IDC_CHK_VM_28181_NOTRELATE, m_BVideoChanNotRelate);
    //}}AFX_DATA_MAP
    DDX_CBIndex(pDX, IDC_COMBO_LINK_TYPE, m_byTCPConnectMod);
}


BEGIN_MESSAGE_MAP(CDlgGBT28181ProAccessUniform, CDialog)
	//{{AFX_MSG_MAP(CDlgGBT28181ProAccessUniform)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_IN, OnSelchangeComboAlarmIn)
	ON_BN_CLICKED(IDC_BTN_GETALARM, OnBtnGetalarm)
	ON_BN_CLICKED(IDC_BTN_SETALARM, OnBtnSetalarm)
	ON_BN_CLICKED(IDC_BTN_SAVE_VIDEOCHANNEL, OnBtnSaveVideochannel)
	ON_CBN_SELCHANGE(IDC_COMBO_VIDEO_CHANNEL, OnSelchangeComboVideoChannel)
	ON_BN_CLICKED(IDC_BTN_GET_VIDEOCHANNEL, OnBtnGetVideochannel)
	ON_BN_CLICKED(IDC_BTN_SET_VIDEOCHANNEL, OnBtnSetVideochannel)
	ON_BN_CLICKED(IDC_CHK_VM_28181_NOTRELATE, OnChkVm28181Notrelate)
	ON_WM_CANCELMODE()
	ON_CBN_SELCHANGE(IDC_COMBO_28181_CHANTEPE, OnSelchangeChantype)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGBT28181ProAccessUniform message handlers

inline BOOL CDlgGBT28181ProAccessUniform::ValidIPv6(BYTE *ip)
{
	if (strlen((char *)ip) >= 2 && strchr((char *)ip, ':') != NULL)
	{
		return TRUE;
	}
	return FALSE;
}

void CDlgGBT28181ProAccessUniform::GetParamFromWnd()
{	
	UpdateData(TRUE);
	m_struGBT28181Accesscfg.byEnable = m_bGBT28181Enable;
	m_struGBT28181Accesscfg.wLocalSipPort = m_iLocalSipPort;
	memcpy(m_struGBT28181Accesscfg.szServerID, m_csServerID, MAX_SERVERID_LEN);
//	m_struGBT28181Accesscfg.byAddressType = 0;

// 	if (m_csIP.Find(':') != -1)
// 	{
// 		strncpy((char *)m_struGBT28181Accesscfg.unionServer.struAddrIP.struIp.byIPv6, m_csIP, 128);
// 	}
// 	else
// 	{
// 		strncpy(m_struGBT28181Accesscfg.unionServer.struAddrIP.struIp.sIpV4, m_csIP, 16);
// 	}
	
	memcpy(m_struGBT28181Accesscfg.szServerDomain, m_csServerDomain, 128);
	memcpy(m_struGBT28181Accesscfg.szSipServerAddress, m_csIP, 128);
	

	m_struGBT28181Accesscfg.wServerSipPort = m_iServerSipPort;
	memcpy(m_struGBT28181Accesscfg.szSipUserName, m_csSipUserName, MAX_SERVERNAME_LEN);
	memcpy(m_struGBT28181Accesscfg.szSipAuthenticateID, m_csSipAuthenticateID, MAX_AUTHENTICATEID_LEN);
	memcpy(m_struGBT28181Accesscfg.szSipAuthenticatePasswd, m_csSipAuthenticatePasswd, MAX_AUTHENTICATEPASSWD_LEN);
	m_struGBT28181Accesscfg.dwRegisterValid = m_iRegisterValid;
	m_struGBT28181Accesscfg.byHeartbeatInterval = m_iHeartBeatInterval;
	m_struGBT28181Accesscfg.byMaxHeartbeatTimeOut = m_iMaxHeartbeatTimeOut;
	m_struGBT28181Accesscfg.byStreamType = m_comboStreamType.GetCurSel();
	m_struGBT28181Accesscfg.byDeviceStatus = m_comDevStatus.GetCurSel()+1;
    m_struGBT28181Accesscfg.byProtocolVersion = m_comProtocolVersion.GetCurSel();
    m_struGBT28181Accesscfg.byTransProtocol = m_comTransProtocol.GetCurSel();
    m_struGBT28181Accesscfg.dwAutoAllocChannelID = m_BCodeChan + ((BYTE)m_BAlarmInChan << 1 )+ ((BYTE)m_BDecodeChan << 2); 
    m_struGBT28181Accesscfg.byTCPConnectMod = m_byTCPConnectMod;
}

void CDlgGBT28181ProAccessUniform::SetParamFromWnd()
{
	m_bGBT28181Enable = m_struGBT28181Accesscfg.byEnable;
	m_iLocalSipPort = m_struGBT28181Accesscfg.wLocalSipPort;	
	char cTemp[200] = {0};
	memcpy(cTemp, m_struGBT28181Accesscfg.szServerID, MAX_SERVERID_LEN);
	m_csServerID = cTemp;

// 	if (ValidIPv6(m_struGBT28181Accesscfg.unionServer.struAddrIP.struIp.byIPv6))
// 	{
// 		m_csIP.Format("%s", m_struGBT28181Accesscfg.unionServer.struAddrIP.struIp.byIPv6);
// 	}
// 	else
// 	{
// 		m_csIP.Format("%s", m_struGBT28181Accesscfg.unionServer.struAddrIP.struIp.sIpV4);
// 	}
	memcpy(cTemp, m_struGBT28181Accesscfg.szSipServerAddress, 128);
	m_csIP = cTemp;
	memcpy(cTemp, m_struGBT28181Accesscfg.szServerDomain, 128);
	m_csServerDomain = cTemp;

	m_iServerSipPort = m_struGBT28181Accesscfg.wServerSipPort;
	memcpy(cTemp, m_struGBT28181Accesscfg.szSipUserName, MAX_SERVERNAME_LEN);
	m_csSipUserName = cTemp;
	memcpy(cTemp, m_struGBT28181Accesscfg.szSipAuthenticateID, MAX_AUTHENTICATEID_LEN);
	m_csSipAuthenticateID = cTemp;
	memcpy(cTemp, m_struGBT28181Accesscfg.szSipAuthenticatePasswd, MAX_AUTHENTICATEPASSWD_LEN);
	m_csSipAuthenticatePasswd = cTemp;
	m_iRegisterValid = m_struGBT28181Accesscfg.dwRegisterValid;
	m_iHeartBeatInterval = m_struGBT28181Accesscfg.byHeartbeatInterval;
	m_iMaxHeartbeatTimeOut = m_struGBT28181Accesscfg.byMaxHeartbeatTimeOut;
	m_comboStreamType.SetCurSel(m_struGBT28181Accesscfg.byStreamType);
	
	if (m_struGBT28181Accesscfg.byDeviceStatus > 0) //2014-03-21
	{
		m_comDevStatus.SetCurSel(m_struGBT28181Accesscfg.byDeviceStatus - 1);
	}
	m_BCodeChan = m_struGBT28181Accesscfg.dwAutoAllocChannelID & 0x1; 
    m_BAlarmInChan = (m_struGBT28181Accesscfg.dwAutoAllocChannelID >> 1) & 0x1; 
    m_BDecodeChan = (m_struGBT28181Accesscfg.dwAutoAllocChannelID >> 2) & 0x1;

    m_comProtocolVersion.SetCurSel(m_struGBT28181Accesscfg.byProtocolVersion);
    m_comTransProtocol.SetCurSel(m_struGBT28181Accesscfg.byTransProtocol);
    m_byTCPConnectMod = m_struGBT28181Accesscfg.byTCPConnectMod;
	UpdateData(FALSE);
}


void CDlgGBT28181ProAccessUniform::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
	DWORD dwReturn = 0;
	char szLan[128] = {0};

    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_GBT28181_ACCESS_CFG, m_dwServerID, &m_struGBT28181Accesscfg,sizeof(NET_DVR_GBT28181_ACCESS_CFG), &dwReturn))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_GBT28181_ACCESS_CFG %d",NET_DVR_GetLastError());
		g_StringLanType(szLan, "参数获取失败", "Get failed");
		AfxMessageBox(szLan);
    }
	SetParamFromWnd();
}

void CDlgGBT28181ProAccessUniform::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};

	GetParamFromWnd();
	m_struGBT28181Accesscfg.dwSize = sizeof(m_struGBT28181Accesscfg);
	if (!NET_DVR_SetDVRConfig(m_lServerID,NET_DVR_SET_GBT28181_ACCESS_CFG, m_dwServerID,&m_struGBT28181Accesscfg, sizeof(NET_DVR_GBT28181_ACCESS_CFG)))	
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_GBT28181_ACCESS_CFG %d",NET_DVR_GetLastError());
		g_StringLanType(szLan, "参数保存失败", "Save failed");
		AfxMessageBox(szLan);
	}
}

BOOL CDlgGBT28181ProAccessUniform::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CheckInitParam();

	char szLan[128] = {0};
	int i = 0;
	CString tmp =_T("");
	
	if (m_pstruAlarmInInfoCond != NULL)
	{
		delete [] m_pstruAlarmInInfoCond;
	}

	if (m_pstruGBT28181AlarmInCfg != NULL)
	{
		delete [] m_pstruGBT28181AlarmInCfg;
	}

	if (m_pstruStreamInfoCond != NULL)
	{
		delete [] m_pstruStreamInfoCond;
	}
	if (m_pstruGBT28181ChanInfoCfg != NULL)
	{
		delete [] m_pstruGBT28181ChanInfoCfg;
	}

	int iAlarmInCount = m_comboAlarmIn.GetCount();
	m_pstruAlarmInInfoCond = new NET_DVR_ALARMIN_INFO[iAlarmInCount];
	memset(m_pstruAlarmInInfoCond, 0, iAlarmInCount*sizeof(NET_DVR_ALARMIN_INFO));
	LPNET_DVR_ALARMIN_INFO m_pstruAlarmInInfoCondTmp = m_pstruAlarmInInfoCond;

	m_pstruGBT28181AlarmInCfg = new NET_DVR_GBT28181_ALARMINCFG[iAlarmInCount];
	memset(m_pstruGBT28181AlarmInCfg, 0, iAlarmInCount*sizeof(NET_DVR_GBT28181_ALARMINCFG));

	for (i = 0; i < iAlarmInCount; i++)
	{
		m_pstruAlarmInInfoCondTmp->dwAlarmInChannel = m_comboAlarmIn.GetItemData(i);
		m_pstruAlarmInInfoCondTmp->struStreamInfo.dwSize = sizeof(NET_DVR_STREAM_INFO);
		m_pstruAlarmInInfoCondTmp->struStreamInfo.dwChannel = m_nChannel;

		m_pstruAlarmInInfoCondTmp++;
	}
	
	int iChannelInCount = m_comboVideoChannel.GetCount();
	m_pstruStreamInfoCond = new NET_DVR_STREAM_INFO[iChannelInCount];
	memset(m_pstruStreamInfoCond, 0, iChannelInCount*sizeof(NET_DVR_STREAM_INFO));
	LPNET_DVR_STREAM_INFO m_pstruStreamInfoCondTmp = m_pstruStreamInfoCond;
	
	m_pstruGBT28181ChanInfoCfg = new NET_DVR_GBT28181_CHANINFO_CFG[iChannelInCount];
	memset(m_pstruGBT28181ChanInfoCfg, 0, iChannelInCount*sizeof(NET_DVR_GBT28181_CHANINFO_CFG));
	
    LPNET_DVR_GBT28181_CHANINFO_CFG lpCfgTmp = m_pstruGBT28181ChanInfoCfg; 
	for (i = 0; i < iChannelInCount; i++)
	{
		m_pstruStreamInfoCondTmp->dwChannel = m_comboVideoChannel.GetItemData(i);
		m_pstruStreamInfoCondTmp->dwSize = sizeof(NET_DVR_STREAM_INFO);
        lpCfgTmp->dwSize = sizeof(*lpCfgTmp);
        lpCfgTmp ++; 
        m_pstruStreamInfoCondTmp ++; 
	}


	if (m_comboVideoChannel.GetCount() >= 1)
	{
		m_comboVideoChannel.SetCurSel(0);
	}
	if (m_comboAlarmIn.GetCount() >= 1)
	{
		m_comboAlarmIn.SetCurSel(0);
	}
	m_cmbChanType.SetCurSel(0); 

    m_RecordBM.Init(m_pstruStreamInfoCond, sizeof(*m_pstruStreamInfoCond), m_pstruGBT28181ChanInfoCfg, sizeof(*m_pstruGBT28181ChanInfoCfg),  iChannelInCount); 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CDlgGBT28181ProAccessUniform::CheckInitParam(BOOL bInit, int iInGroupNO, int iOutGroupNO)
{
	m_csAlarmInName = _T("");
	int i = 0;
	CString sTemp;
	m_comboAlarmIn.ResetContent();
	int iCopyIndex = 0;
	if (m_lServerID < 0)
	{
		return FALSE;
	}
	
	for (i=0; i<MAX_CHANNUM_V30; i++)
	{
// 		if (g_struDeviceInfo[m_dwDevIndex].struChanInfo[i].bEnable)
// 		{
//			sTemp.Format("%s", g_struDeviceInfo[m_dwDevIndex].struChanInfo[i].chChanName);
            sTemp.Format("%d", i);
			m_comboVideoChannel.AddString(sTemp);
			m_comboVideoChannel.SetItemData(iCopyIndex, i+1);
			iCopyIndex++;
//		}
	}

	if (g_struDeviceInfo[m_dwDevIndex].iIPChanNum > 0)
	{
		if (g_pMainDlg->DoGetIPAlarmInCfg(m_dwDevIndex))
		{
			memcpy(&m_struIPAlarmInCfg, &g_struDeviceInfo[m_dwDevIndex].struAlarmInCfg, sizeof(NET_DVR_IPALARMINCFG));
		}
	}

	for (i=0; i<MAX_ALARMIN_V30; i++)//m_dwAlarmInNum
	{	
		m_bGetAlarmIn[i] = FALSE;
		m_bSetAlarmIn[i] = FALSE;
		//int iIPAlarmIndex = 0;
		char szLan[128]={0};
		DWORD dwReturned = 0;
		int iIPAlarmIndex = 0; 
		//int iAlarmInSel = 0;

		if (i<(int)m_dwAlarmInNum || (i>=MAX_ANALOG_ALARMIN && m_struIPAlarmInCfg.struIPAlarmInInfo[i-MAX_ANALOG_ALARMIN].byIPID > 0))
		{
			
// 			if (i >= MAX_ANALOG_ALARMIN)
// 			{
// 				iIPAlarmIndex = i + MAX_IP_ALARMIN*m_iIPAlarmInGroupNO;
// 			}
// 			else
			{
				iIPAlarmIndex = i;
			}
			
			//此处代码用于验证测试部提的用老接口设置后出现中文乱码的情况
			// 			NET_DVR_ALARMINCFG struAlaraming = {0};
			// 			if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_ALARMINCFG, iIPAlarmIndex, &struAlaraming, sizeof(NET_DVR_ALARMINCFG), &dwReturned))
			// 			{
			// 				m_bGetAlarmIn[i] = FALSE;
			// 				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMINCFG_V30 chanindex[%d]", iIPAlarmIndex);	
			// 				g_StringLanType(szLan, "获取报警输入参数失败", "Alarm input parameters to get the failure");
			// 				AfxMessageBox(szLan);
			// 				return FALSE;
			// 			}
			// 
			//             memcpy(m_struAlarmInCfg[i].sAlarmInName, struAlaraming.sAlarmInName ,NAME_LEN);
			// 			m_struAlarmInCfg[i].byChannel = struAlaraming.byChannel;
			// 			m_struAlarmInCfg[i].byAlarmType = struAlaraming.byAlarmType;
			// 			memcpy(m_struAlarmInCfg[i].byCruiseNo,struAlaraming.byCruiseNo,MAX_CHANNUM);
			// 			memcpy(m_struAlarmInCfg[i].byRelRecordChan,struAlaraming.byRelRecordChan,MAX_CHANNUM);
			// 			memcpy(m_struAlarmInCfg[i].byPresetNo,struAlaraming.byPresetNo,MAX_CHANNUM);
			// 			memcpy(m_struAlarmInCfg[i].byEnablePreset,struAlaraming.byEnablePreset,MAX_CHANNUM);
			// 			memcpy(m_struAlarmInCfg[i].byEnableCruise,struAlaraming.byEnableCruise,MAX_CHANNUM);
			// 			memcpy(m_struAlarmInCfg[i].byPTZTrack,struAlaraming.byPTZTrack,MAX_CHANNUM);
			// 			memcpy(m_struAlarmInCfg[i].byEnablePtzTrack,struAlaraming.byEnablePtzTrack,MAX_CHANNUM);
			if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_ALARMINCFG_V30, iIPAlarmIndex, &m_struAlarmInCfg[i], sizeof(NET_DVR_ALARMINCFG_V30), &dwReturned))
			{
				m_bGetAlarmIn[i] = FALSE;
				g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMINCFG_V30 chanindex[%d]", iIPAlarmIndex);	
				g_StringLanType(szLan, "获取报警输入参数失败", "Alarm input parameters to get the failure");
				AfxMessageBox(szLan);
				return FALSE;
			}
			if (i<(int)m_dwAlarmInNum)
			{			
				sTemp.Format(ALARM_IN_NAME, (1+i));
			}
			else
			{
				sTemp.Format(IP_ALARM_IN_NAME, (1 + iIPAlarmIndex-MAX_ANALOG_ALARMIN));
			}	
			
			m_bGetAlarmIn[i] = TRUE;
			m_comboAlarmIn.AddString(sTemp);
			m_comboAlarmIn.SetItemData(iAlarmInSel, iIPAlarmIndex+1);
			
// 			m_comboCopyAlarmIn.AddString(sTemp);
// 			m_comboCopyAlarmIn.SetItemData(iAlarmInSel+1, iIPAlarmIndex);
			iAlarmInSel++;
		}		
	}
	return TRUE;
}

void CDlgGBT28181ProAccessUniform::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	LPNET_DVR_GBT28181_ALARMINCFG pstruGBT28181AlarmInCfgTmp = m_pstruGBT28181AlarmInCfg;
	pstruGBT28181AlarmInCfgTmp += m_comboAlarmIn.GetCurSel();
	pstruGBT28181AlarmInCfgTmp->dwSize = sizeof(NET_DVR_GBT28181_ALARMINCFG);
	memcpy(pstruGBT28181AlarmInCfgTmp->szAlarmInNumID, m_csAlarmInID, MAX_COMPRESSIONID_LEN);
}

void CDlgGBT28181ProAccessUniform::OnSelchangeComboAlarmIn() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	LPNET_DVR_GBT28181_ALARMINCFG pstruGBT28181AlarmInCfgTmp = m_pstruGBT28181AlarmInCfg;
	pstruGBT28181AlarmInCfgTmp += m_comboAlarmIn.GetCurSel();

	char cTmp[200] = {0};
	memcpy(cTmp, pstruGBT28181AlarmInCfgTmp->szAlarmInNumID, MAX_COMPRESSIONID_LEN);
	m_csAlarmInID = cTmp;
	UpdateData(FALSE);
}

void CDlgGBT28181ProAccessUniform::OnBtnGetalarm() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	char szTemp[256] = {0};
	
	int iAlarmInCount = m_comboAlarmIn.GetCount();
	DWORD *pStatus = new DWORD[iAlarmInCount];
	memset(pStatus, 0, sizeof(DWORD)*iAlarmInCount);
	
	if (NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_GBT28181_ALARMINCFG, iAlarmInCount, m_pstruAlarmInInfoCond, \
		sizeof(NET_DVR_ALARMIN_INFO)*iAlarmInCount, pStatus, m_pstruGBT28181AlarmInCfg, iAlarmInCount*sizeof(NET_DVR_GBT28181_ALARMINCFG)))
	{
		DWORD *pStatusTmp = pStatus;
		for (int i = 0; i < iAlarmInCount; i++)
		{
			if (*pStatusTmp != 0)
			{
				g_StringLanType(szLan, "获取参数失败", "Get Param configuration failed");
				sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
				AfxMessageBox(szTemp);
				delete [] pStatus;
				return;
			}
			pStatusTmp++;			 
		}
	}
	else
	{
		delete [] pStatus;
		g_StringLanType(szLan, "获取参数失败", "Get Param configuration failed");
		sprintf(szTemp, "%s %s %d", szLan, NET_DVR_GetErrorMsg(), NET_DVR_GetLastError());
		AfxMessageBox(szTemp);
		return;	
	}
	delete [] pStatus;

	m_comboAlarmIn.SetCurSel(0);
	OnSelchangeComboAlarmIn();
}

void CDlgGBT28181ProAccessUniform::OnBtnSetalarm() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	char szTemp[256] = {0};
	
	int iAlarmInCount = m_comboAlarmIn.GetCount();
	DWORD *pStatus = new DWORD[iAlarmInCount];
	memset(pStatus, 0, sizeof(DWORD)*iAlarmInCount);
	if (!NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_GBT28181_ALARMINCFG, iAlarmInCount, m_pstruAlarmInInfoCond, iAlarmInCount*sizeof(NET_DVR_ALARMIN_INFO), \
		pStatus, m_pstruGBT28181AlarmInCfg, iAlarmInCount*sizeof(NET_DVR_GBT28181_ALARMINCFG)))
	{
		g_StringLanType(szLan, "设置参数失败", "Set Param configuration failed");
		sprintf(szTemp, "%s %s %d", szLan, NET_DVR_GetErrorMsg(),NET_DVR_GetLastError());
		AfxMessageBox(szTemp);
		delete [] pStatus;
		return;
	}
	else
	{
		for (int i = 0; i < iAlarmInCount; i++)
		{
			DWORD *pStatusTmp = pStatus;
			if (*pStatusTmp != 0)
			{
				g_StringLanType(szLan, "设置参数失败", "Set Param configuration failed");
				sprintf(szTemp, "%s %s %d", szLan, NET_DVR_GetErrorMsg(),NET_DVR_GetLastError());
				AfxMessageBox(szTemp);
				delete [] pStatus;
				return;
			}
			pStatusTmp++;
		}
	}
	delete [] pStatus;
}

void CDlgGBT28181ProAccessUniform::OnBtnSaveVideochannel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	LPNET_DVR_GBT28181_CHANINFO_CFG pstruGBT28181ChanInfoCfgTmp = m_pstruGBT28181ChanInfoCfg;
    int iSel = m_comboVideoChannel.GetCurSel(); 
    if ( iSel == -1)
    {
        AfxMessageBox("没有选择序号"); 
        return ; 
    }
    pstruGBT28181ChanInfoCfgTmp += iSel;
    pstruGBT28181ChanInfoCfgTmp->dwSize = sizeof(*pstruGBT28181ChanInfoCfgTmp); 
    if ( m_BVideoChanNotRelate )
    {
        m_pstruStreamInfoCond[iSel].dwChannel = 0xffffffff; 
    }
    else
    {
        m_pstruStreamInfoCond[iSel].dwChannel = m_dwVideCodeChan; 
    }

    m_comboVideoChannel.SetItemData(iSel, m_dwVideCodeChan); 
	memcpy(pstruGBT28181ChanInfoCfgTmp->szVideoChannelNumID, m_csVideoChannelID, MAX_COMPRESSIONID_LEN);

    m_RecordBM.Add(&m_pstruStreamInfoCond[iSel], pstruGBT28181ChanInfoCfgTmp, ChannelCmp); 
    UpdateData(FALSE); 
}

void CDlgGBT28181ProAccessUniform::OnSelchangeComboVideoChannel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	LPNET_DVR_GBT28181_CHANINFO_CFG pstruGBT28181ChanInfoCfgTmp = m_pstruGBT28181ChanInfoCfg;
    int iSel = m_comboVideoChannel.GetCurSel(); 
    DWORD dwVideoChan = m_comboVideoChannel.GetItemData(iSel); 
    if ( dwVideoChan == 0xffffffff )
    {
        m_BVideoChanNotRelate = TRUE; 
    }
    else
    {
        m_BVideoChanNotRelate = FALSE;
        m_dwVideCodeChan = dwVideoChan; 
    }

    OnChkVm28181Notrelate(); 
	pstruGBT28181ChanInfoCfgTmp += iSel;
	
	char cTmp[200] = {0};
	memcpy(cTmp, pstruGBT28181ChanInfoCfgTmp->szVideoChannelNumID, MAX_COMPRESSIONID_LEN);
	m_csVideoChannelID = cTmp;

	UpdateData(FALSE);
}

void CDlgGBT28181ProAccessUniform::OnBtnGetVideochannel() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    DWORD dwCommand = 0; 
    if ( m_cmbChanType.GetCurSel() == 0)
    {
        dwCommand = NET_DVR_GET_GBT28181_CHANINFO_CFG; 
    }
    else if ( m_cmbChanType.GetCurSel() == 1)
    {
        dwCommand = NET_DVR_GET_GBT28181_DECCHANINFO_CFG; 
    }
    else
    {
        return ;     
    }
	char szLan[128] = {0};
	char szTemp[256] = {0};
	
	int iChannelCount = m_comboVideoChannel.GetCount();
	DWORD *pStatus = new DWORD[iChannelCount];
	memset(pStatus, 0, sizeof(DWORD)*iChannelCount);
	
	if (NET_DVR_GetDeviceConfig(m_lServerID, dwCommand, iChannelCount, m_pstruStreamInfoCond, \
		sizeof(NET_DVR_STREAM_INFO)*iChannelCount, pStatus, m_pstruGBT28181ChanInfoCfg, iChannelCount*sizeof(NET_DVR_GBT28181_CHANINFO_CFG)))
	{
		DWORD *pStatusTmp = pStatus;
		for (int i = 0; i < iChannelCount; i++)
		{
			if (*pStatusTmp != 0)
			{
				g_StringLanType(szLan, "获取参数失败", "Get Param configuration failed");
				sprintf(szTemp, "%s %d", szLan, NET_DVR_GetLastError());
				AfxMessageBox(szTemp);
				delete [] pStatus;
				return;
			}
			pStatusTmp++;			 
		}
        m_RecordBM.Clear(); 
	}
	else
	{
		delete [] pStatus;
		g_StringLanType(szLan, "获取参数失败", "Get Param configuration failed");
		sprintf(szTemp, "%s %d", szLan, NET_DVR_GetLastError());
		AfxMessageBox(szTemp);
		return;	
	}
	delete [] pStatus;
	
	m_comboVideoChannel.SetCurSel(0);
	OnSelchangeComboVideoChannel();
}

void CDlgGBT28181ProAccessUniform::OnBtnSetVideochannel() 
{
	// TODO: Add your control notification handler code here
//    UpdateData(TRUE); 
	char szLan[128] = {0};
	char szTemp[256] = {0};
    DWORD dwCommand = 0; 
    if ( m_cmbChanType.GetCurSel() == 0)
    {
        dwCommand = NET_DVR_SET_GBT28181_CHANINFO_CFG; 
    }
    else if ( m_cmbChanType.GetCurSel() == 1)
    {
        dwCommand = NET_DVR_SET_GBT28181_DECCHANINFO_CFG; 
    }
    else
    {
        return ;     
    }

//	int iChannelCount = m_comboVideoChannel.GetCount();
    LPNET_DVR_STREAM_INFO lpStreamInfo = NULL; 
    LPNET_DVR_GBT28181_CHANINFO_CFG lpCfg = NULL; 
    int iChannelCount = m_RecordBM.GetModify((void **)&lpStreamInfo,  (void **)&lpCfg); 
	DWORD *pStatus = new DWORD[iChannelCount];
	memset(pStatus, 0, sizeof(DWORD)*iChannelCount);
    
	if (!NET_DVR_SetDeviceConfig(m_lServerID, dwCommand, iChannelCount, lpStreamInfo, iChannelCount*sizeof(NET_DVR_STREAM_INFO), \
		pStatus, lpCfg, iChannelCount*sizeof(NET_DVR_GBT28181_CHANINFO_CFG)))
	{
		g_StringLanType(szLan, "设置参数失败", "Set Param configuration failed");
		sprintf(szTemp, "%s %s %d", szLan, NET_DVR_GetErrorMsg(),NET_DVR_GetLastError());
		AfxMessageBox(szTemp);
		delete [] pStatus;
		return;
	}
	else
	{
		for (int i = 0; i < iChannelCount; i++)
		{
			DWORD *pStatusTmp = pStatus;
			if (*pStatusTmp != 0)
			{
				g_StringLanType(szLan, "设置参数失败", "Set Param configuration failed");
				sprintf(szTemp, "%s %s %d", szLan, NET_DVR_GetErrorMsg(),NET_DVR_GetLastError());
				AfxMessageBox(szTemp);
				delete [] pStatus;
				return;
			}
			pStatusTmp++;
		}
	}
	delete [] pStatus;
}

void CDlgGBT28181ProAccessUniform::OnChkVm28181Notrelate() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
    GetDlgItem(IDC_EDIT_28181_VIDEOCHAN)->EnableWindow(FALSE); 
    if (! m_BVideoChanNotRelate )
    {
        GetDlgItem(IDC_EDIT_28181_VIDEOCHAN)->EnableWindow(TRUE); 
    }
    UpdateData(FALSE); 
}

void CDlgGBT28181ProAccessUniform::OnSelchangeChantype() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    int iChannelCount = m_comboVideoChannel.GetCount();
    memset(m_pstruStreamInfoCond,0,  iChannelCount*sizeof(NET_DVR_STREAM_INFO)); 
    memset(m_pstruGBT28181ChanInfoCfg, 0, iChannelCount*sizeof(NET_DVR_GBT28181_CHANINFO_CFG)); 
    LPNET_DVR_STREAM_INFO m_pstruStreamInfoCondTmp = m_pstruStreamInfoCond;
    LPNET_DVR_GBT28181_CHANINFO_CFG lpCfgTemp  = m_pstruGBT28181ChanInfoCfg; 
    int i; 
    for (i = 0; i < iChannelCount; i++)
    {
        m_pstruStreamInfoCondTmp->dwChannel = m_comboVideoChannel.GetItemData(i);
        m_pstruStreamInfoCondTmp->dwSize = sizeof(NET_DVR_STREAM_INFO);
        lpCfgTemp->dwSize = sizeof(*lpCfgTemp); 
        lpCfgTemp ++; 
        m_pstruStreamInfoCondTmp ++; 
	}	
}

//初始化资源
BOOL GBT28181BM::Init(LPNET_DVR_GBT28181_CHANINFO_CFG lpSrc, LPNET_DVR_STREAM_INFO lpIndex,  DWORD max)
{
    return (m_RecordCfg.Init( lpSrc, max, sizeof(*lpSrc)) && m_RecordInfo.Init( lpIndex, max, sizeof(*lpIndex)));
}   

//获取修改过资源, 返回个数
int GBT28181BM::GetModify(LPNET_DVR_GBT28181_CHANINFO_CFG &lpModifySrc, LPNET_DVR_STREAM_INFO &lpIndex)
{
    int iRetNumCfg = 0;
    int iRetNumInfo = 0; 
    void * pSrc = (void *) lpModifySrc; 
    void * pIndex = (void *) lpIndex; 
    iRetNumCfg	 = m_RecordCfg.GetMod( ((void **)&lpModifySrc) );
    iRetNumInfo	 = m_RecordInfo.GetMod( ((void **)&lpIndex) );
    return (iRetNumCfg == iRetNumInfo)?iRetNumInfo:-1; 
}   
  
//重新
BOOL GBT28181BM::Update(DWORD dwNum, const NET_DVR_GBT28181_CHANINFO_CFG *lpItemCfg, const NET_DVR_STREAM_INFO *lpIndex)    
{
    m_RecordInfo.Clear(); 
    m_RecordCfg.Clear(); 
    NET_DVR_VIDEO_WALL_INFO struWallInfo = {0}; 
    int iIndex = -1; 
    try
    {
        for (int i=0 ; i<dwNum; i++)
        {
            iIndex = m_RecordCfg.Update(lpItemCfg+i);        
            m_RecordInfo.Update(lpIndex+i,  iIndex ); 
        }
    }
    catch (...)
    {
        return FALSE; 
    }
    return TRUE; 
}
// 
// //更新比较条件函数
// bool ChannelCmp (const void *ItemF, const void *ItemS)
// {
//     const NET_DVR_STREAM_INFO * CfgItemF = (const NET_DVR_STREAM_INFO *) ItemF; 
//     const NET_DVR_STREAM_INFO * CfgItemS = (const NET_DVR_STREAM_INFO *) ItemS; 
//     return (CfgItemF->dwChannel == CfgItemS->dwChannel);
// }

//刷新某一项 
BOOL GBT28181BM::Update(const NET_DVR_GBT28181_CHANINFO_CFG &ItemCfg, const NET_DVR_STREAM_INFO &ItemIndex)
{
    int iIndex; 
    if (( iIndex = m_RecordInfo.Update(&ItemIndex , ChannelCmp)) != -1)
    {
        return  m_RecordCfg.Update(& ItemCfg, iIndex); 
    }
    return FALSE; 
}

//本地添加某一项
BOOL GBT28181BM::Add(const NET_DVR_GBT28181_CHANINFO_CFG &ItemCfg, const NET_DVR_STREAM_INFO &ItemInfo)
{
    int iIndex; 
    if (( iIndex = m_RecordInfo.Add(& ItemInfo, ChannelCmp)) != -1)
    {
        return m_RecordCfg.Add(&ItemCfg, iIndex); 
    }
	return FALSE; 
}  

////修改已有项
BOOL GBT28181BM::Modify(const NET_DVR_GBT28181_CHANINFO_CFG &ItemCfg, const NET_DVR_STREAM_INFO &ItemInfo)
{
    int iIndex; 
    if (( iIndex = m_RecordInfo.Modify(& ItemInfo, ChannelCmp)) != -1)
    {
        return m_RecordCfg.Modify(&ItemCfg, iIndex); 
    }
	return FALSE; 
}  

//获取数量
int  GBT28181BM::GetNum()  
{
    return (m_RecordCfg.GetUsedNum() == m_RecordInfo.GetUsedNum()) ? m_RecordCfg.GetUsedNum() : -1; 
}   

//获取原始资源地址
bool GBT28181BM::GetSrc(LPNET_DVR_GBT28181_CHANINFO_CFG &ItemCfg, LPNET_DVR_STREAM_INFO &ItemInfo)
{
    ItemCfg = (LPNET_DVR_GBT28181_CHANINFO_CFG) m_RecordCfg.GetSrc(); 
    ItemInfo = (LPNET_DVR_STREAM_INFO ) m_RecordInfo.GetSrc(); 
    return true;   
}

//删除某一项场景
BOOL GBT28181BM::Del(int iChannel)
{
    NET_DVR_STREAM_INFO ItemInfo = {0}; 
    ItemInfo.dwSize = sizeof(ItemInfo); 
    ItemInfo.dwChannel = iChannel; 
    int iIndex = -1; 
    if ((iIndex = m_RecordCfg.Del(&ItemInfo, ChannelCmp)) != -1)
    {
        m_RecordInfo.Del(iIndex);
    }
    return TRUE; 
}

//清楚修改记录                    
BOOL GBT28181BM::Clear()
{
    m_RecordInfo.Clear(); 
    m_RecordCfg.Clear(); 
    return TRUE; 
}
