// DlgGBT28181ProtocolAccess.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgGBT28181ProtocolAccess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGBT28181ProtocolAccess dialog


CDlgGBT28181ProtocolAccess::CDlgGBT28181ProtocolAccess(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGBT28181ProtocolAccess::IDD, pParent)
    , m_AudioOutNumID(_T(""))
{
	//{{AFX_DATA_INIT(CDlgGBT28181ProtocolAccess)
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
	m_csVideoChannel = _T("");
	m_csVideoChannelID = _T("");
	m_csServerDomain = _T("");
	m_iRegisterInterval = 0;
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

    m_pstruGBT28181AudioOutCond = NULL;
    m_pstruGBT28181AudioOutCfg = NULL;
}

CDlgGBT28181ProtocolAccess::~CDlgGBT28181ProtocolAccess()
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

    if (m_pstruGBT28181AudioOutCond != NULL)
    {
        delete[] m_pstruGBT28181AudioOutCond;
    }
    if (m_pstruGBT28181AudioOutCfg != NULL)
    {
        delete[] m_pstruGBT28181AudioOutCfg;
    }
}

void CDlgGBT28181ProtocolAccess::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGBT28181ProtocolAccess)
	DDX_Control(pDX, IDC_COMBO_PRO_VERSION, m_comProtocolVersion);
	DDX_Control(pDX, IDC_COMBO_TRANSPROTOCOL, m_comboTransProtocol);
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
	DDX_CBString(pDX, IDC_COMBO_VIDEO_CHANNEL, m_csVideoChannel);
	DDX_Text(pDX, IDC_EDIT_VIDEOCHANNEL_ID, m_csVideoChannelID);
	DDX_Text(pDX, IDC_EDIT_SERVER_DOMAIN, m_csServerDomain);
	DDX_Text(pDX, IDC_EDIT_REGISTER_INTERVAL, m_iRegisterInterval);
	//}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMBO_AUDIO_CHANNEL, m_comboAudioChannel);
    DDX_Text(pDX, IDC_EDIT2, m_AudioOutNumID);
}


BEGIN_MESSAGE_MAP(CDlgGBT28181ProtocolAccess, CDialog)
	//{{AFX_MSG_MAP(CDlgGBT28181ProtocolAccess)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_IN, OnSelchangeComboAlarmIn)
	ON_BN_CLICKED(IDC_BTN_GETALARM, OnBtnGetalarm)
	ON_BN_CLICKED(IDC_BTN_SETALARM, OnBtnSetalarm)
	ON_BN_CLICKED(IDC_BTN_SAVE_VIDEOCHANNEL, OnBtnSaveVideochannel)
	ON_CBN_SELCHANGE(IDC_COMBO_VIDEO_CHANNEL, OnSelchangeComboVideoChannel)
	ON_BN_CLICKED(IDC_BTN_GET_VIDEOCHANNEL, OnBtnGetVideochannel)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_BTN_SET_VIDEOCHANNEL, OnBtnSetVideochannel)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_SET_AUDIOCHANNEL, &CDlgGBT28181ProtocolAccess::OnBnClickedBtnSetAudiochannel)
    ON_BN_CLICKED(IDC_BTN_GET_AUDIOCHANNEL, &CDlgGBT28181ProtocolAccess::OnBnClickedBtnGetAudiochannel)
    ON_BN_CLICKED(IDC_BTN_SAVE_AUDIOCHANNEL, &CDlgGBT28181ProtocolAccess::OnBnClickedBtnSaveAudiochannel)
    ON_CBN_SELCHANGE(IDC_COMBO_AUDIO_CHANNEL, &CDlgGBT28181ProtocolAccess::OnSelchangeComboAudioChannel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGBT28181ProtocolAccess message handlers

inline BOOL CDlgGBT28181ProtocolAccess::ValidIPv6(BYTE *ip)
{
	if (strlen((char *)ip) >= 2 && strchr((char *)ip, ':') != NULL)
	{
		return TRUE;
	}
	return FALSE;
}

void CDlgGBT28181ProtocolAccess::GetParamFromWnd()
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
	m_struGBT28181Accesscfg.byTransProtocol = m_comboTransProtocol.GetCurSel();
    m_struGBT28181Accesscfg.byProtocolVersion = m_comProtocolVersion.GetCurSel();
	m_struGBT28181Accesscfg.dwRegisterInterval = m_iRegisterInterval;
}

void CDlgGBT28181ProtocolAccess::SetParamFromWnd()
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

	m_comboTransProtocol.SetCurSel(m_struGBT28181Accesscfg.byTransProtocol);
    m_comProtocolVersion.SetCurSel(m_struGBT28181Accesscfg.byProtocolVersion);
	m_iRegisterInterval = m_struGBT28181Accesscfg.dwRegisterInterval;
	UpdateData(FALSE);
}


void CDlgGBT28181ProtocolAccess::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
	char szLan[128] = {0};

    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_GBT28181_ACCESS_CFG, m_nChannel, &m_struGBT28181Accesscfg,sizeof(NET_DVR_GBT28181_ACCESS_CFG), &dwReturn))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_GBT28181_ACCESS_CFG %d",NET_DVR_GetLastError());
		g_StringLanType(szLan, "参数获取失败", "Get failed");
		AfxMessageBox(szLan);
    }
	SetParamFromWnd();
}

void CDlgGBT28181ProtocolAccess::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};

	GetParamFromWnd();
	m_struGBT28181Accesscfg.dwSize = sizeof(m_struGBT28181Accesscfg);
	if (!NET_DVR_SetDVRConfig(m_lServerID,NET_DVR_SET_GBT28181_ACCESS_CFG, m_nChannel,&m_struGBT28181Accesscfg, sizeof(NET_DVR_GBT28181_ACCESS_CFG)))	
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_GBT28181_ACCESS_CFG %d",NET_DVR_GetLastError());
		g_StringLanType(szLan, "参数保存失败", "Save failed");
		AfxMessageBox(szLan);
	}
}

BOOL CDlgGBT28181ProtocolAccess::OnInitDialog() 
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

    if (m_pstruGBT28181AudioOutCond != NULL)
    {
        delete[] m_pstruGBT28181AudioOutCond;
    }
    if (m_pstruGBT28181AudioOutCfg != NULL)
    {
        delete[] m_pstruGBT28181AudioOutCfg;
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
	
	for (i = 0; i < iChannelInCount; i++)
	{
		m_pstruStreamInfoCondTmp->dwChannel = m_comboVideoChannel.GetItemData(i);
		m_pstruStreamInfoCondTmp->dwSize = sizeof(NET_DVR_STREAM_INFO);
		m_pstruStreamInfoCondTmp++;
	}

    int iAudioOutCount = m_comboAudioChannel.GetCount();
    m_pstruGBT28181AudioOutCond = new NET_DVR_GBT28181_AUDIO_OUTPUT_COND[iAudioOutCount];
    memset(m_pstruGBT28181AudioOutCond, 0, iAudioOutCount*sizeof(NET_DVR_GBT28181_AUDIO_OUTPUT_COND));
    LPNET_DVR_GBT28181_AUDIO_OUTPUT_COND m_pstruGBT28181AudioOutCondTmp = m_pstruGBT28181AudioOutCond;

    m_pstruGBT28181AudioOutCfg = new NET_DVR_GBT28181_AUDIO_OUTPUT_CFG[iAudioOutCount];
    memset(m_pstruGBT28181AudioOutCfg, 0, iAudioOutCount*sizeof(NET_DVR_GBT28181_AUDIO_OUTPUT_CFG));

    for (i = 0; i < iAudioOutCount; i++)
    {
        m_pstruGBT28181AudioOutCondTmp->dwAudioChannel = m_comboAudioChannel.GetItemData(i);
        m_pstruGBT28181AudioOutCondTmp->dwSize = sizeof(NET_DVR_GBT28181_AUDIO_OUTPUT_COND);

        m_pstruGBT28181AudioOutCondTmp++;
    }


	if (m_comboVideoChannel.GetCount() >= 1)
	{
		m_comboVideoChannel.SetCurSel(0);
	}
	if (m_comboAlarmIn.GetCount() >= 1)
	{
		m_comboAlarmIn.SetCurSel(0);
	}
    if (m_comboAudioChannel.GetCount() >= 1)
    {
        m_comboAudioChannel.SetCurSel(0);
    }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CDlgGBT28181ProtocolAccess::CheckInitParam(BOOL bInit, int iInGroupNO, int iOutGroupNO)
{
	m_csAlarmInName = _T("");
	int i = 0;
	CString sTemp;
	m_comboAlarmIn.ResetContent();
	int iCopyIndex = 0;
    int iAudioIndex = 0;
	if (m_lServerID < 0)
	{
		return FALSE;
	}
	
	for (i=0; i<MAX_CHANNUM_V30; i++)
	{
		if (g_struDeviceInfo[m_dwDevIndex].pStruChanInfo[i].bEnable)
		{
			sTemp.Format("%s", g_struDeviceInfo[m_dwDevIndex].pStruChanInfo[i].chChanName);
			m_comboVideoChannel.AddString(sTemp);
			m_comboVideoChannel.SetItemData(iCopyIndex, i+1);

			iCopyIndex++;
		}
	}

	if (g_struDeviceInfo[m_dwDevIndex].iIPChanNum > 0)
	{
		if (g_pMainDlg->DoGetIPAlarmInCfg(m_dwDevIndex, FALSE, 0))
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
//				AfxMessageBox(szLan);
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

    for (int i = 1; i <= g_struDeviceInfo[m_dwDevIndex].iAudioNum + g_struDeviceInfo[m_dwDevIndex].iIPChanNum; i++)
    {
        char sTemp[20] = { 0 };
        if (i <= g_struDeviceInfo[m_dwDevIndex].iAudioNum)  //模拟语音对讲通道
        {
            sprintf(sTemp, "Audio%d", i);
            m_comboAudioChannel.AddString(sTemp);
            m_comboAudioChannel.SetItemData(iAudioIndex, iAudioIndex + 1);
            iAudioIndex++;
        }
        else    // 数字语音对讲通道
        {

            if (i - g_struDeviceInfo[m_dwDevIndex].iAudioNum - 1 <= MAX_CHANNUM_V40)
            {
                sprintf(sTemp, "DigitalAudio%d", i - g_struDeviceInfo[m_dwDevIndex].iAudioNum);
                m_comboAudioChannel.AddString(sTemp);
                m_comboAudioChannel.SetItemData(iAudioIndex, iAudioIndex - g_struDeviceInfo[m_dwDevIndex].iAudioNum + g_struDeviceInfo[m_dwDevIndex].byStartDTalkChan);
                iAudioIndex++;
            }
        }
    }
    m_comboAudioChannel.SetCurSel(0);

	return TRUE;
}

void CDlgGBT28181ProtocolAccess::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	LPNET_DVR_GBT28181_ALARMINCFG pstruGBT28181AlarmInCfgTmp = m_pstruGBT28181AlarmInCfg;
	pstruGBT28181AlarmInCfgTmp += m_comboAlarmIn.GetCurSel();
	pstruGBT28181AlarmInCfgTmp->dwSize = sizeof(NET_DVR_GBT28181_ALARMINCFG);
	memcpy(pstruGBT28181AlarmInCfgTmp->szAlarmInNumID, m_csAlarmInID, MAX_COMPRESSIONID_LEN);
}

void CDlgGBT28181ProtocolAccess::OnSelchangeComboAlarmIn() 
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

void CDlgGBT28181ProtocolAccess::OnBtnGetalarm() 
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

void CDlgGBT28181ProtocolAccess::OnBtnSetalarm() 
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

void CDlgGBT28181ProtocolAccess::OnBtnSaveVideochannel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	LPNET_DVR_GBT28181_CHANINFO_CFG pstruGBT28181ChanInfoCfgTmp = m_pstruGBT28181ChanInfoCfg;
	pstruGBT28181ChanInfoCfgTmp += m_comboVideoChannel.GetCurSel();
	pstruGBT28181ChanInfoCfgTmp->dwSize = sizeof(NET_DVR_GBT28181_CHANINFO_CFG);
	memcpy(pstruGBT28181ChanInfoCfgTmp->szVideoChannelNumID, m_csVideoChannelID, MAX_COMPRESSIONID_LEN);
}

void CDlgGBT28181ProtocolAccess::OnSelchangeComboVideoChannel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	LPNET_DVR_GBT28181_CHANINFO_CFG pstruGBT28181ChanInfoCfgTmp = m_pstruGBT28181ChanInfoCfg;
	pstruGBT28181ChanInfoCfgTmp += m_comboVideoChannel.GetCurSel();
	
	char cTmp[200] = {0};
	memcpy(cTmp, pstruGBT28181ChanInfoCfgTmp->szVideoChannelNumID, MAX_COMPRESSIONID_LEN);
	m_csVideoChannelID = cTmp;
	UpdateData(FALSE);
}

void CDlgGBT28181ProtocolAccess::OnBtnGetVideochannel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	char szTemp[256] = {0};
	
	int iChannelCount = m_comboVideoChannel.GetCount();
	DWORD *pStatus = new DWORD[iChannelCount];
	memset(pStatus, 0, sizeof(DWORD)*iChannelCount);
	
	if (NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_GBT28181_CHANINFO_CFG, iChannelCount, m_pstruStreamInfoCond, \
		sizeof(NET_DVR_STREAM_INFO)*iChannelCount, pStatus, m_pstruGBT28181ChanInfoCfg, iChannelCount*sizeof(NET_DVR_GBT28181_ALARMINCFG)))
	{
		DWORD *pStatusTmp = pStatus;
		for (int i = 0; i < iChannelCount; i++)
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
		sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
		AfxMessageBox(szTemp);
		return;	
	}
	delete [] pStatus;
	
	m_comboVideoChannel.SetCurSel(0);
	OnSelchangeComboVideoChannel();
}

void CDlgGBT28181ProtocolAccess::OnBtnSetVideochannel() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	char szTemp[256] = {0};
	
	int iChannelCount = m_comboVideoChannel.GetCount();
	DWORD *pStatus = new DWORD[iChannelCount];
	memset(pStatus, 0, sizeof(DWORD)*iChannelCount);
	if (!NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_GBT28181_CHANINFO_CFG, iChannelCount, m_pstruStreamInfoCond, iChannelCount*sizeof(NET_DVR_STREAM_INFO), \
		pStatus, m_pstruGBT28181ChanInfoCfg, iChannelCount*sizeof(NET_DVR_GBT28181_ALARMINCFG)))
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



void CDlgGBT28181ProtocolAccess::OnBnClickedBtnSetAudiochannel()
{
    char szLan[128] = { 0 };
    char szTemp[256] = { 0 };

    int iAudioOutCount = m_comboAudioChannel.GetCount();
    DWORD *pStatus = new DWORD[iAudioOutCount];
    memset(pStatus, 0, sizeof(DWORD)*iAudioOutCount);
    if (!NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_GBT28181_AUDIO_OUTPUT_CFG, iAudioOutCount, m_pstruGBT28181AudioOutCond, iAudioOutCount*sizeof(NET_DVR_GBT28181_AUDIO_OUTPUT_COND), \
        pStatus, m_pstruGBT28181AudioOutCfg, iAudioOutCount*sizeof(NET_DVR_GBT28181_AUDIO_OUTPUT_CFG)))
    {
        g_StringLanType(szLan, "设置参数失败", "Set Param configuration failed");
        sprintf(szTemp, "%s %s %d", szLan, NET_DVR_GetErrorMsg(), NET_DVR_GetLastError());
        AfxMessageBox(szTemp);
        delete[] pStatus;
        return;
    }
    else
    {
        for (int i = 0; i < iAudioOutCount; i++)
        {
            DWORD *pStatusTmp = pStatus;
            if (*pStatusTmp != 0)
            {
                g_StringLanType(szLan, "设置参数失败", "Set Param configuration failed");
                sprintf(szTemp, "%s %s %d", szLan, NET_DVR_GetErrorMsg(), NET_DVR_GetLastError());
                AfxMessageBox(szTemp);
                delete[] pStatus;
                return;
            }
            pStatusTmp++;
        }
    }
    delete[] pStatus;
}


void CDlgGBT28181ProtocolAccess::OnBnClickedBtnGetAudiochannel()
{
    UpdateData(TRUE);
    char szLan[128] = { 0 };
    char szTemp[256] = { 0 };

    int iAudioOutCount = m_comboAudioChannel.GetCount();
    DWORD *pStatus = new DWORD[iAudioOutCount];
    memset(pStatus, 0, sizeof(DWORD)*iAudioOutCount);

    if (NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_GBT28181_AUDIO_OUTPUT_CFG, iAudioOutCount, m_pstruGBT28181AudioOutCond, \
        sizeof(NET_DVR_GBT28181_AUDIO_OUTPUT_COND)*iAudioOutCount, pStatus, m_pstruGBT28181AudioOutCfg, iAudioOutCount*sizeof(NET_DVR_GBT28181_AUDIO_OUTPUT_CFG)))
    {
        DWORD *pStatusTmp = pStatus;
        for (int i = 0; i < iAudioOutCount; i++)
        {
            if (*pStatusTmp != 0)
            {
                g_StringLanType(szLan, "获取参数失败", "Get Param configuration failed");
                sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
                AfxMessageBox(szTemp);
                delete[] pStatus;
                return;
            }
            pStatusTmp++;
        }
    }
    else
    {
        delete[] pStatus;
        g_StringLanType(szLan, "获取参数失败", "Get Param configuration failed");
        sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
        AfxMessageBox(szTemp);
        return;
    }
    delete[] pStatus;

    m_comboAudioChannel.SetCurSel(0);
    OnSelchangeComboAudioChannel();
}


void CDlgGBT28181ProtocolAccess::OnBnClickedBtnSaveAudiochannel()
{
    UpdateData(TRUE);
    LPNET_DVR_GBT28181_AUDIO_OUTPUT_CFG pstruGBT28181AudioOutCfgTmp = m_pstruGBT28181AudioOutCfg;
    pstruGBT28181AudioOutCfgTmp += m_comboAudioChannel.GetCurSel();
    pstruGBT28181AudioOutCfgTmp->dwSize = sizeof(NET_DVR_GBT28181_AUDIO_OUTPUT_CFG);
    memcpy(pstruGBT28181AudioOutCfgTmp->szAudioOutNumID, m_AudioOutNumID, MAX_COMPRESSIONID_LEN);
}


void CDlgGBT28181ProtocolAccess::OnSelchangeComboAudioChannel()
{
    UpdateData(TRUE);
    LPNET_DVR_GBT28181_AUDIO_OUTPUT_CFG pstruGBT28181AudioOutCfgTmp = m_pstruGBT28181AudioOutCfg;
    pstruGBT28181AudioOutCfgTmp += m_comboAudioChannel.GetCurSel();

    char cTmp[200] = { 0 };
    memcpy(cTmp, pstruGBT28181AudioOutCfgTmp->szAudioOutNumID, MAX_COMPRESSIONID_LEN);
    m_AudioOutNumID = cTmp;
    UpdateData(FALSE);
}
