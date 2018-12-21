// DlgIpViewCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgIpViewCfg.h"
#include "DlgAlarmExceptionHandle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIpViewCfg dialog


CDlgIpViewCfg::CDlgIpViewCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIpViewCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgIpViewCfg)
	m_bChkAutoRes = FALSE;
	m_bChkUseAlarm1 = FALSE;
	m_bChkUseAlarm2 = FALSE;
	m_strAlarm1 = _T("");
	m_strAlarm2 = _T("");
	m_byResTime = 0;
	m_bChkAutoLogin = FALSE;
	m_strDevName = _T("");
	m_strIP = _T("");
	m_strLocalNum = _T("");
	m_dwLocalPort = 0;
	m_byLoginCycle = 0;
	m_dwPort = 0;
	m_strUserName = _T("");
	m_strUserPwd = _T("");
	m_byRingType = 0;
	m_byRingVolume = 0;
	m_byRingInVolume = 0;
	m_byRingOutVolume = 0;
	m_wRtpPort = 0;
	m_dwPreviewDelayTime = 0;
	m_dwDecibel = 0;
	m_bAudioLimitAlarm = FALSE;
	m_bButtonDownAlarm = FALSE;
    m_csDomainName = _T("");
    m_csSipProxyDomain = _T("");
    m_csSipStunDomain = _T("");
    m_csProxyIP = _T("");
    m_csStunIP = _T("");
    m_dwProxyPort = 0;
    m_dwStunPort = 0;
	//}}AFX_DATA_INIT
	memset(&m_struSipCfg, 0, sizeof(NET_DVR_SIP_CFG));
	memset(&m_struButtonDownAlarmCfg, 0, sizeof(NET_IPC_BUTTON_DOWN_ALARM_CFG));
	memset(&m_struAudioLimitAlarmCfg, 0, sizeof(NET_IPC_AUDIO_LIMIT_ALARM_CFG));
	memset(&m_struIpViewCallCfg, 0, sizeof(m_struIpViewCallCfg));
}


void CDlgIpViewCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIpViewCfg)
	DDX_Control(pDX, IDC_COMBO_AUDIO_PACKET_LENGTH2, m_comboAudioPacketLength2);
	DDX_Control(pDX, IDC_COMBO_AUDIO_PACKET_LENGTH, m_comboAudioPacketLength);
	DDX_Control(pDX, IDC_COMBO_AUDIO_ENCODE_PRIO2, m_comboAudioEncodePrio2);
	DDX_Control(pDX, IDC_COMBO_AUDIO_ENCODE_PRIO1, m_comboAudioEncodePrio1);
	DDX_Check(pDX, IDC_CHK_AUTO_RES, m_bChkAutoRes);
	DDX_Check(pDX, IDC_CHK_USE_ALARM_NUM1, m_bChkUseAlarm1);
	DDX_Check(pDX, IDC_CHK_USE_ALARM_NUM2, m_bChkUseAlarm2);
	DDX_Text(pDX, IDC_EDIT_ALARM_NUM1, m_strAlarm1);
	DDX_Text(pDX, IDC_EDIT_ALARM_NUM2, m_strAlarm2);
	DDX_Text(pDX, IDC_EDIT_AUTO_RES_TIME, m_byResTime);
	DDX_Control(pDX, IDC_COMBO_LOGIN_STATE, m_comboLoginState);
	DDX_Check(pDX, IDC_CHK_AUTO_LOGIN, m_bChkAutoLogin);
	DDX_Text(pDX, IDC_EDIT_DEV_NAME, m_strDevName);
	DDX_Text(pDX, IDC_EDIT_IP, m_strIP);
	DDX_Text(pDX, IDC_EDIT_LOCAL_NUM, m_strLocalNum);
	DDX_Text(pDX, IDC_EDIT_LOCAL_PORT, m_dwLocalPort);
	DDX_Text(pDX, IDC_EDIT_LOGIN_CYCLE, m_byLoginCycle);
	DDX_Text(pDX, IDC_EDIT_PORT, m_dwPort);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_strUserName);
	DDX_Text(pDX, IDC_EDIT_USER_PWD, m_strUserPwd);
	DDX_Text(pDX, IDC_EDIT_RING_TYPE, m_byRingType);
	DDX_Text(pDX, IDC_EDIT_RING_VOLUME, m_byRingVolume);
	DDX_Text(pDX, IDC_EDIT_RING_IN_VOLUME, m_byRingInVolume);
	DDX_Text(pDX, IDC_EDIT_RING_OUT_VOLUME, m_byRingOutVolume);
	DDX_Text(pDX, IDC_EDIT_RTP_PORT, m_wRtpPort);
	DDX_Text(pDX, IDC_EDIT_PREVIEW_DELAY_TIME, m_dwPreviewDelayTime);
	DDV_MinMaxDWord(pDX, m_dwPreviewDelayTime, 0, 30);
	DDX_Text(pDX, IDC_EDIT_DECIBEL, m_dwDecibel);
	DDX_Check(pDX, IDC_CHK_AUDIO_LIMIT_ALARM, m_bAudioLimitAlarm);
	DDX_Check(pDX, IDC_CHK_BUTTON_DOWN_ALARM, m_bButtonDownAlarm);
    DDX_Control(pDX, IDC_COMBO_ADDR_TYPE, m_comboAddrType);
    DDX_Text(pDX, IDC_EDIT_DOMIAN_NAME_IN, m_csDomainName);
    DDX_Text(pDX, IDC_EDIT_DOAMIN_PROXY, m_csSipProxyDomain);
    DDX_Text(pDX, IDC_EDIT_DOMAIN_STUN, m_csSipStunDomain);
    DDX_Text(pDX, IDC_EDIT_IP_PROXY, m_csProxyIP);
    DDX_Text(pDX, IDC_EDIT_IP_STUN, m_csStunIP);
    DDX_Text(pDX, IDC_EDIT_PORT_PROXY, m_dwProxyPort);
    DDX_Text(pDX, IDC_EDIT_PORT_STUN, m_dwStunPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIpViewCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgIpViewCfg)
	ON_BN_CLICKED(IDC_BTN_SET_IP_VIEW_CALL_CFG, OnBtnSetIpViewCallCfg)
	ON_BN_CLICKED(IDC_BTN_GET_IP_VIEW_CALL_CFG, OnBtnGetIpViewCallCfg)
	ON_BN_CLICKED(IDC_BTN_GET_SIP_CFG, OnBtnGetSipCfg)
	ON_BN_CLICKED(IDC_BTN_SET_SIP_CFG, OnBtnSetSipCfg)
	ON_BN_CLICKED(IDC_BTN_SET_IP_VIEW_DEV_CFG, OnBtnSetIpViewDevCfg)
	ON_BN_CLICKED(IDC_BTN_GET_IP_VIEW_DEV_CFG, OnBtnGetIpViewDevCfg)
	ON_BN_CLICKED(IDC_BTN_SET_AUDIO_PARM_CFG, OnBtnSetAudioParmCfg)
	ON_BN_CLICKED(IDC_BTN_GET_AUDIO_PARM_CFG, OnBtnGetAudioParmCfg)
	ON_BN_CLICKED(IDC_BTN_AUDIO_LIMIT_CFG, OnBtnAudioLimitCfg)
	ON_BN_CLICKED(IDC_BTN_BUTTON_DOWN_CFG, OnBtnButtonDownCfg)
	ON_BN_CLICKED(IDC_BTN_SET_IP_VIEW_ALARM_CFG, OnBtnSetIpViewAlarmCfg)
	ON_BN_CLICKED(IDC_BTN_GET_IP_VIEW_ALARM_CFG, OnBtnGetIpViewAlarmCfg)
	ON_BN_CLICKED(IDC_CHK_AUDIO_LIMIT_ALARM, OnChkAudioLimitAlarm)
	ON_BN_CLICKED(IDC_CHK_BUTTON_DOWN_ALARM, OnChkButtonDownAlarm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgIpViewCfg message handlers

void CDlgIpViewCfg::OnBtnSetIpViewCallCfg() 
{
	UpdateData(TRUE);
	memset(&m_struIpViewCallCfg, 0, sizeof(m_struIpViewCallCfg));
	m_struIpViewCallCfg.dwSize = sizeof(NET_DVR_IP_VIEW_CALL_CFG);
	m_struIpViewCallCfg.byEnableAutoResponse = m_bChkAutoRes;
	m_struIpViewCallCfg.byAudoResponseTime = m_byResTime;
	m_struIpViewCallCfg.byEnableAlarmNumber1 = m_bChkUseAlarm1;
	sprintf((char *)m_struIpViewCallCfg.byAlarmNumber1, "%s", m_strAlarm1);
	m_struIpViewCallCfg.byEnableAlarmNumber2 = m_bChkUseAlarm2;
	sprintf((char *)m_struIpViewCallCfg.byAlarmNumber2, "%s", m_strAlarm2);
	
	if (!NET_DVR_SetDVRConfig(m_lServerID,NET_DVR_SET_IP_VIEW_CALL_CFG, 0XFF, &m_struIpViewCallCfg, sizeof(NET_DVR_IP_VIEW_CALL_CFG)))	
	{
		char szLan[128] = {0};
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_IP_VIEW_CALL_CFG");
		g_StringLanType(szLan, "参数保存失败", "Save failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_IP_VIEW_CALL_CFG");	
	}
	
}

void CDlgIpViewCfg::OnBtnGetIpViewCallCfg() 
{
	DWORD dwReturned = 0;
	if (!NET_DVR_GetDVRConfig(m_lServerID,NET_DVR_GET_IP_VIEW_CALL_CFG, 0XFF, &m_struIpViewCallCfg, sizeof(NET_DVR_IP_VIEW_CALL_CFG), &dwReturned))	
	{
		char szLan[128] = {0};
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_IP_VIEW_CALL_CFG");
		g_StringLanType(szLan, "参数保存失败", "Save failed");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_IP_VIEW_CALL_CFG");	
	}
	
	m_bChkAutoRes = m_struIpViewCallCfg.byEnableAutoResponse;
	m_byResTime = m_struIpViewCallCfg.byAudoResponseTime;
	m_bChkUseAlarm1 = m_struIpViewCallCfg.byEnableAlarmNumber1;
	m_strAlarm1.Format("%s", m_struIpViewCallCfg.byAlarmNumber1);
	m_bChkUseAlarm2 = m_struIpViewCallCfg.byEnableAlarmNumber2;
	m_strAlarm2.Format("%s", m_struIpViewCallCfg.byAlarmNumber2);
	UpdateData(FALSE);
	
}

void CDlgIpViewCfg::OnBtnGetSipCfg() 
{
	DWORD dwReturned = 0;
    memset(&m_struSipCfg, 0, sizeof(m_struSipCfg));
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_SIP_CFG_V50, 0XFF, &m_struSipCfg, sizeof(NET_DVR_SIP_CFG_V50), &dwReturned))
	//if (!NET_DVR_GetDVRConfig(m_lServerID,NET_DVR_GET_SIP_CFG, 0XFF, &m_struSipCfg, sizeof(NET_DVR_SIP_CFG), &dwReturned))	
	{
		char szLan[128] = {0};
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SIP_CFG_V50");
		g_StringLanType(szLan, "参数获取失败", "Save failed");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SIP_CFG_V50");	
	}
	
	m_bChkAutoLogin = m_struSipCfg.byEnableAutoLogin;
	m_comboLoginState.SetCurSel(m_struSipCfg.byLoginStatus);
	m_strIP.Format("%s", m_struSipCfg.stuServerIP.sIpV4);
	m_dwPort = m_struSipCfg.wServerPort;
	m_strUserName.Format("%s", m_struSipCfg.byUserName);
	m_strUserPwd.Format("%s", m_struSipCfg.byPassWord);
	m_strLocalNum.Format("%s", m_struSipCfg.byLocalNo);
	m_strDevName.Format("%s", m_struSipCfg.byDispalyName);
	m_dwLocalPort = m_struSipCfg.wLocalPort;
	m_byLoginCycle = m_struSipCfg.byLoginCycle;
    m_csDomainName.Format("%s", m_struSipCfg.bySIPServerDomain);
    //m_comboAddrType.SetCurSel(m_struSipCfg.byType); 

    m_csProxyIP.Format("%s", m_struSipCfg.stuProxyServerIP.sIpV4);
    m_csStunIP.Format("%s", m_struSipCfg.stuSTUNServerIP.sIpV4);
    m_csSipStunDomain.Format("%s", m_struSipCfg.bySTUNServerDomain);
    m_csSipProxyDomain.Format("%s", m_struSipCfg.byProxyServerDomain);

    m_dwProxyPort = m_struSipCfg.wProxyServerPort;
    m_dwStunPort = m_struSipCfg.wSTUNServerPort;

	UpdateData(FALSE);
	
}

void CDlgIpViewCfg::OnBtnSetSipCfg() 
{
	UpdateData(TRUE);
	memset(&m_struSipCfg, 0, sizeof(m_struSipCfg));
    m_struSipCfg.dwSize = sizeof(NET_DVR_SIP_CFG_V50);
    char szLan[256] = { 0 };
    if (m_dwPort < 0 || m_dwPort > 65535||m_dwLocalPort<0 ||m_dwLocalPort>65535)
    {
        g_StringLanType(szLan, "请输入正确的端口号！", "Please Input right port!");
        AfxMessageBox(szLan);
        return;
    }
	m_struSipCfg.byEnableAutoLogin = m_bChkAutoLogin;
	m_struSipCfg.byLoginStatus = m_comboLoginState.GetCurSel();
	sprintf((char *)m_struSipCfg.stuServerIP.sIpV4, "%s", m_strIP);
	m_struSipCfg.wServerPort = m_dwPort;
	sprintf((char *)m_struSipCfg.byUserName, "%s", m_strUserName);
	sprintf((char *)m_struSipCfg.byPassWord, "%s", m_strUserPwd);
	sprintf((char *)m_struSipCfg.byLocalNo, "%s", m_strLocalNum);
	sprintf((char *)m_struSipCfg.byDispalyName, "%s", m_strDevName);
	m_struSipCfg.wLocalPort = m_dwLocalPort;
	m_struSipCfg.byLoginCycle = m_byLoginCycle;
    //m_struSipCfg.byType = m_comboAddrType.GetCurSel();
    //sprintf((char *)m_struSipCfg.byDomainName, "%s", m_csDomainName);

    sprintf((char *)m_struSipCfg.bySIPServerDomain, "%s", m_csDomainName);
    sprintf((char *)m_struSipCfg.stuProxyServerIP.sIpV4, "%s", m_csProxyIP);
    sprintf((char *)m_struSipCfg.stuSTUNServerIP.sIpV4, "%s", m_csStunIP);
    sprintf((char *)m_struSipCfg.bySTUNServerDomain, "%s", m_csSipStunDomain);
    sprintf((char *)m_struSipCfg.byProxyServerDomain, "%s", m_csSipProxyDomain);
    m_struSipCfg.wProxyServerPort = m_dwProxyPort;
    m_struSipCfg.wSTUNServerPort = m_dwStunPort;
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_SIP_CFG_V50, 0XFF, &m_struSipCfg, sizeof(NET_DVR_SIP_CFG_V50)))
	//if (!NET_DVR_SetDVRConfig(m_lServerID,NET_DVR_SET_SIP_CFG, 0XFF, &m_struSipCfg, sizeof(NET_DVR_SIP_CFG)))	
	{
		char szLan[128] = {0};
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SIP_CFG_V50");
		g_StringLanType(szLan, "参数设置失败", "Save failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SIP_CFG_V50");	
	}
	
}

void CDlgIpViewCfg::OnBtnSetIpViewDevCfg() 
{
	UpdateData(TRUE);
	memset(&m_struIpViewDevCfg, 0, sizeof(m_struIpViewDevCfg));
	m_struIpViewDevCfg.dwSize = sizeof(NET_DVR_IP_VIEW_DEVCFG);
	m_struIpViewDevCfg.byDefaultRing = m_byRingType;
	m_struIpViewDevCfg.byRingVolume = m_byRingVolume;
	m_struIpViewDevCfg.byInputVolume = m_byRingInVolume;
	m_struIpViewDevCfg.byOutputVolume = m_byRingOutVolume;
	m_struIpViewDevCfg.wRtpPort = m_wRtpPort;
	m_struIpViewDevCfg.dwPreviewDelayTime = m_dwPreviewDelayTime;

	if (!NET_DVR_SetDVRConfig(m_lServerID,NET_DVR_SET_IP_VIEW_DEVCFG, 0XFF, &m_struIpViewDevCfg, sizeof(NET_DVR_IP_VIEW_DEVCFG)))	
	{
		char szLan[128] = {0};
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_IP_VIEW_DEVCFG");
		g_StringLanType(szLan, "参数保存失败", "Save failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_IP_VIEW_DEVCFG");		
	}
	
}

void CDlgIpViewCfg::OnBtnGetIpViewDevCfg() 
{
	DWORD dwReturn = 0;
	if (!NET_DVR_GetDVRConfig(m_lServerID,NET_DVR_GET_IP_VIEW_DEVCFG, 0XFF, &m_struIpViewDevCfg, sizeof(NET_DVR_IP_VIEW_DEVCFG), &dwReturn))	
	{
		char szLan[128] = {0};
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_IP_VIEW_DEVCFG");
		g_StringLanType(szLan, "参数保存失败", "Save failed");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_IP_VIEW_DEVCFG");	
	}

	m_byRingType = m_struIpViewDevCfg.byDefaultRing;
	m_byRingVolume = m_struIpViewDevCfg.byRingVolume;
	m_byRingInVolume = m_struIpViewDevCfg.byInputVolume;
	m_byRingOutVolume= m_struIpViewDevCfg.byOutputVolume;
	m_wRtpPort = m_struIpViewDevCfg.wRtpPort;
	m_dwPreviewDelayTime = m_struIpViewDevCfg.dwPreviewDelayTime;
	UpdateData(FALSE);
	
}

void CDlgIpViewCfg::OnBtnSetAudioParmCfg() 
{
	UpdateData(TRUE);
	memset(&m_struIpViewAudioCfg, 0, sizeof(m_struIpViewAudioCfg));
	m_struIpViewAudioCfg.dwSize = sizeof(NET_DVR_IP_VIEW_AUDIO_CFG);
	m_struIpViewAudioCfg.byAudioEncPri1 = m_comboAudioEncodePrio1.GetItemData(m_comboAudioEncodePrio1.GetCurSel());
	m_struIpViewAudioCfg.byAudioEncPri2 = m_comboAudioEncodePrio1.GetItemData(m_comboAudioEncodePrio2.GetCurSel());
	m_struIpViewAudioCfg.wAudioPacketLen1 = m_comboAudioPacketLength.GetItemData(m_comboAudioPacketLength.GetCurSel());
	m_struIpViewAudioCfg.wAudioPacketLen2 = m_comboAudioPacketLength2.GetItemData(m_comboAudioPacketLength2.GetCurSel());
	
	if (!NET_DVR_SetDVRConfig(m_lServerID,NET_DVR_SET_IP_VIEW_AUDIO_CFG, 0XFF, &m_struIpViewAudioCfg, sizeof(NET_DVR_IP_VIEW_AUDIO_CFG)))	
	{
		char szLan[128] = {0};
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_IP_VIEW_AUDIO_CFG");
		g_StringLanType(szLan, "参数设置失败", "Save failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_IP_VIEW_AUDIO_CFG");	
	}
	
}

void CDlgIpViewCfg::OnBtnGetAudioParmCfg() 
{
	DWORD dwReturn = 0;
	int i = 0;
	
	if (!NET_DVR_GetDVRConfig(m_lServerID,NET_DVR_GET_IP_VIEW_AUDIO_CFG, 0XFF, &m_struIpViewAudioCfg, sizeof(NET_DVR_IP_VIEW_AUDIO_CFG), &dwReturn))	
	{
		char szLan[128] = {0};
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_IP_VIEW_AUDIO_CFG");
		g_StringLanType(szLan, "参数保存失败", "Save failed");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_IP_VIEW_AUDIO_CFG");
		
	}
	
	for (i = 0; i < m_comboAudioEncodePrio1.GetCount(); i++)
	{
		if (m_comboAudioEncodePrio1.GetItemData(i) == m_struIpViewAudioCfg.byAudioEncPri1)
		{
			m_comboAudioEncodePrio1.SetCurSel(i);
			break;
		}
	}

	for (i = 0; i < m_comboAudioEncodePrio2.GetCount(); i++)
	{
		if (m_comboAudioEncodePrio2.GetItemData(i) == m_struIpViewAudioCfg.byAudioEncPri2)
		{
			m_comboAudioEncodePrio2.SetCurSel(i);
			break;
		}
	}
	
	for (i = 0; i < m_comboAudioPacketLength.GetCount(); i++)
	{
		if (m_comboAudioPacketLength.GetItemData(i) == m_struIpViewAudioCfg.wAudioPacketLen1)
		{
			m_comboAudioPacketLength.SetCurSel(i);
			break;
		}
	}

	for (i = 0; i < m_comboAudioPacketLength2.GetCount(); i++)
	{
		if (m_comboAudioPacketLength2.GetItemData(i) == m_struIpViewAudioCfg.wAudioPacketLen2)
		{
			m_comboAudioPacketLength2.SetCurSel(i);
			break;
		}
	}

	UpdateData(FALSE);
	
}

BOOL CDlgIpViewCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_comboAudioEncodePrio1.SetItemData(0, 0);
	m_comboAudioEncodePrio1.SetItemData(1, 1);
	m_comboAudioEncodePrio1.SetItemData(2, 2);
	m_comboAudioEncodePrio1.SetItemData(3, 5);
	m_comboAudioEncodePrio1.SetItemData(4, 6);
	m_comboAudioEncodePrio1.SetItemData(5, 7);

	m_comboAudioEncodePrio2.SetItemData(0, 0);
	m_comboAudioEncodePrio2.SetItemData(1, 1);
	m_comboAudioEncodePrio2.SetItemData(2, 2);
	m_comboAudioEncodePrio2.SetItemData(3, 5);
	m_comboAudioEncodePrio2.SetItemData(4, 6);
	m_comboAudioEncodePrio2.SetItemData(5, 7);

	m_comboAudioEncodePrio1.SetCurSel(0);
	m_comboAudioEncodePrio2.SetCurSel(0);
	m_comboLoginState.SetCurSel(0);

	m_comboAudioPacketLength.SetItemData(0, 160);
	m_comboAudioPacketLength.SetItemData(1, 320);

	m_comboAudioPacketLength2.SetItemData(0, 160);
	m_comboAudioPacketLength2.SetItemData(1, 320);

	OnChkAudioLimitAlarm();
	OnChkButtonDownAlarm();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgIpViewCfg::OnBtnAudioLimitCfg() 
{
	
	CDlgAlarmExceptionHandle dlg;
	dlg.m_dwDevIndex = m_dwDevIndex;
	dlg.m_struHandleException = &m_struAudioLimitAlarmCfg.struHandleException;
	if (dlg.DoModal())
	{
		
	}
}

void CDlgIpViewCfg::OnBtnButtonDownCfg() 
{
	CDlgAlarmExceptionHandle dlg;
	dlg.m_dwDevIndex = m_dwDevIndex;
	dlg.m_struHandleException = &m_struButtonDownAlarmCfg.struHandleException;
	if (dlg.DoModal())
	{
	}
	
}

void CDlgIpViewCfg::OnBtnSetIpViewAlarmCfg() 
{
	UpdateData(TRUE);
	//memset(&m_struAudioLimitAlarmCfg, 0, sizeof(NET_IPC_AUDIO_LIMIT_ALARM_CFG));
	m_struAudioLimitAlarmCfg.dwSize = sizeof(NET_IPC_AUDIO_LIMIT_ALARM_CFG);
	m_struAudioLimitAlarmCfg.byEnable = m_bAudioLimitAlarm;
	m_struAudioLimitAlarmCfg.dwDecibelLimit = m_dwDecibel;
	
	if (!NET_DVR_SetDVRConfig(m_lServerID,NET_DVR_SET_AUDIO_LIMIT_ALARM_CFG, 0XFF, &m_struAudioLimitAlarmCfg, sizeof(NET_IPC_AUDIO_LIMIT_ALARM_CFG)))	
	{
		char szLan[128] = {0};
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_AUDIO_LIMIT_ALARM_CFG");
		g_StringLanType(szLan, "参数设置失败", "Save failed");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_AUDIO_LIMIT_ALARM_CFG");		
	}

	//memset(&m_struButtonDownAlarmCfg, 0, sizeof(NET_IPC_BUTTON_DOWN_ALARM_CFG));
	m_struButtonDownAlarmCfg.dwSize = sizeof(NET_IPC_BUTTON_DOWN_ALARM_CFG);
	m_struButtonDownAlarmCfg.byEnable = m_bButtonDownAlarm;

	
	if (!NET_DVR_SetDVRConfig(m_lServerID,NET_DVR_SET_BUTTON_DOWN_ALARM_CFG, 0XFF, &m_struButtonDownAlarmCfg, sizeof(NET_IPC_BUTTON_DOWN_ALARM_CFG)))	
	{
		char szLan[128] = {0};
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_BUTTON_DOWN_ALARM_CFG");
		g_StringLanType(szLan, "参数设置失败", "Save failed");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_BUTTON_DOWN_ALARM_CFG");	
	}
	
}

void CDlgIpViewCfg::OnBtnGetIpViewAlarmCfg() 
{
	DWORD dwReturn = 0;
	memset(&m_struAudioLimitAlarmCfg, 0, sizeof(NET_IPC_AUDIO_LIMIT_ALARM_CFG));
	if (!NET_DVR_GetDVRConfig(m_lServerID,NET_DVR_GET_AUDIO_LIMIT_ALARM_CFG, 0XFF, &m_struAudioLimitAlarmCfg, sizeof(NET_IPC_AUDIO_LIMIT_ALARM_CFG), &dwReturn))	
	{
		char szLan[128] = {0};
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_AUDIO_LIMIT_ALARM_CFG");
		g_StringLanType(szLan, "参数保存失败", "Save failed");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_AUDIO_LIMIT_ALARM_CFG");
		m_bAudioLimitAlarm = m_struAudioLimitAlarmCfg.byEnable;
		UpdateData(FALSE);
		OnChkAudioLimitAlarm();
		m_dwDecibel = m_struAudioLimitAlarmCfg.dwDecibelLimit;
	}
	
	memset(&m_struButtonDownAlarmCfg, 0, sizeof(NET_IPC_BUTTON_DOWN_ALARM_CFG));
	if (!NET_DVR_GetDVRConfig(m_lServerID,NET_DVR_GET_BUTTON_DOWN_ALARM_CFG, 0XFF, &m_struButtonDownAlarmCfg, sizeof(NET_IPC_BUTTON_DOWN_ALARM_CFG), &dwReturn))	
	{
		char szLan[128] = {0};
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_BUTTON_DOWN_ALARM_CFG");
		g_StringLanType(szLan, "参数保存失败", "Save failed");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_BUTTON_DOWN_ALARM_CFG");
		m_bButtonDownAlarm = m_struButtonDownAlarmCfg.byEnable;
		UpdateData(FALSE);
		OnChkButtonDownAlarm();
	}

	//UpdateData(FALSE);
}

void CDlgIpViewCfg::OnChkAudioLimitAlarm() 
{
	UpdateData(TRUE);
	if (m_bAudioLimitAlarm)
	{
		GetDlgItem(IDC_BTN_AUDIO_LIMIT_CFG)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DECIBEL)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_AUDIO_LIMIT_CFG)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DECIBEL)->EnableWindow(FALSE);
	}
}

void CDlgIpViewCfg::OnChkButtonDownAlarm() 
{
	UpdateData(TRUE);
	if (m_bButtonDownAlarm)
	{
		GetDlgItem(IDC_BTN_BUTTON_DOWN_CFG)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_BUTTON_DOWN_CFG)->EnableWindow(FALSE);
	}	
}
