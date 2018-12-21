// DlgVideoIntercomOpTimeCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVideoIntercomOpTimeCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomOpTimeCfg dialog


CDlgVideoIntercomOpTimeCfg::CDlgVideoIntercomOpTimeCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVideoIntercomOpTimeCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVideoIntercomOpTimeCfg)
	m_nMaxMessageTime = 0;
	m_nMaxMonitoringTime = 0;
	m_nMaxRingTime = 0;
	m_nMaxTalkTime = 0;
	m_dwCallForwardingTime = 0;
	//}}AFX_DATA_INIT
	m_nUnitType = ENUM_OUTDOOR_UNIT;
	m_lServerID = -1;
	m_iDevIndex = -1;
}


void CDlgVideoIntercomOpTimeCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVideoIntercomOpTimeCfg)
	DDX_Text(pDX, IDC_EDIT_MESSAGE_TIME, m_nMaxMessageTime);
	DDX_Text(pDX, IDC_EDIT_MONITORING_TIME, m_nMaxMonitoringTime);
	DDX_Text(pDX, IDC_EDIT_RING_TIME, m_nMaxRingTime);
	DDX_Text(pDX, IDC_EDIT_TALK_TIME, m_nMaxTalkTime);
	DDX_Text(pDX, IDC_EDIT_CALL_FORWARDING_TIME, m_dwCallForwardingTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVideoIntercomOpTimeCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVideoIntercomOpTimeCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_RADIO_INDOOR_UNIT, OnRadioIndoor)
	ON_BN_CLICKED(IDC_RADIO_MANAGE_UNIT, OnRadioManage)
	ON_BN_CLICKED(IDC_RADIO_OUTDOOR_UNIT, OnRadioOutdoor)
	ON_BN_CLICKED(IDC_RADIO_FENCE_UNIT, OnRadioFenceUnit)
	ON_BN_CLICKED(IDC_RADIO_AGAIN_UNIT, OnRadioAgainUnit)
	ON_BN_CLICKED(IDC_RADIO_VILLA_OUTDOOR_UNIT, OnRadioVillaOutdoorUnit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomOpTimeCfg message handlers

void CDlgVideoIntercomOpTimeCfg::OnBtnGet() 
{
	char szError[64] = "\0";
	if (!GetVideoIntercomOpTimeCfg())
	{   
		g_StringLanType(szError, "获取参数失败","Get parameters failed");
		AfxMessageBox(szError);
	}
}

void CDlgVideoIntercomOpTimeCfg::OnBtnSet() 
{
	char szError[32] = "\0";
	if (SetVideoIntercomOpTimeCfg())
	{   
		g_StringLanType(szError, "保存成功","Saved successfully");
	}
	else
	{
		g_StringLanType(szError, "保存失败","Save failed");
	}
	AfxMessageBox(szError);
}

void CDlgVideoIntercomOpTimeCfg::OnRadioIndoor() 
{
	m_nUnitType = ENUM_INDOOR_UNIT;
	CheckRaidoBtn();
}

void CDlgVideoIntercomOpTimeCfg::OnRadioManage() 
{
	m_nUnitType = ENUM_MANAGE_UNIT;
	CheckRaidoBtn();
}

void CDlgVideoIntercomOpTimeCfg::OnRadioOutdoor() 
{
	m_nUnitType = ENUM_OUTDOOR_UNIT;
	CheckRaidoBtn();
}

void CDlgVideoIntercomOpTimeCfg::CheckRaidoBtn()
{
    CheckDlgButton(IDC_RADIO_INDOOR_UNIT,m_nUnitType == ENUM_INDOOR_UNIT);
    CheckDlgButton(IDC_RADIO_OUTDOOR_UNIT,m_nUnitType == ENUM_OUTDOOR_UNIT);
    CheckDlgButton(IDC_RADIO_MANAGE_UNIT,m_nUnitType == ENUM_MANAGE_UNIT);
    CheckDlgButton(IDC_RADIO_FENCE_UNIT,m_nUnitType == ENUM_FENCE_UNIT);
    CheckDlgButton(IDC_RADIO_VILLA_OUTDOOR_UNIT,m_nUnitType == ENUM_VILLA_OUTDOOR_UNIT);
    CheckDlgButton(IDC_RADIO_AGAIN_UNIT,m_nUnitType == ENUM_AGAIN_UNIT);

	GetDlgItem(IDC_EDIT_MESSAGE_TIME)->EnableWindow(m_nUnitType == ENUM_OUTDOOR_UNIT || m_nUnitType == ENUM_FENCE_UNIT||m_nUnitType == ENUM_VILLA_OUTDOOR_UNIT || m_nUnitType == ENUM_AGAIN_UNIT);
	GetDlgItem(IDC_EDIT_RING_TIME)->EnableWindow(m_nUnitType == ENUM_INDOOR_UNIT || m_nUnitType == ENUM_MANAGE_UNIT);
	GetDlgItem(IDC_EDIT_TALK_TIME)->EnableWindow(m_nUnitType == ENUM_OUTDOOR_UNIT || m_nUnitType == ENUM_FENCE_UNIT || m_nUnitType == ENUM_MANAGE_UNIT||m_nUnitType == ENUM_VILLA_OUTDOOR_UNIT || m_nUnitType == ENUM_AGAIN_UNIT);
	GetDlgItem(IDC_EDIT_MONITORING_TIME)->EnableWindow(m_nUnitType == ENUM_INDOOR_UNIT || m_nUnitType == ENUM_MANAGE_UNIT);
    GetDlgItem(IDC_EDIT_CALL_FORWARDING_TIME)->EnableWindow(m_nUnitType == ENUM_INDOOR_UNIT);
}

BOOL CDlgVideoIntercomOpTimeCfg::GetVideoIntercomOpTimeCfg()
{
	DWORD dwReturn = 0;
	BOOL  bRst = FALSE;
	
	NET_DVR_VIDEO_INTERCOM_OPERATION_TIME_CFG struOpTimeCfg = {0};
	struOpTimeCfg.dwSize = sizeof(struOpTimeCfg);
	
	if (NET_DVR_GetDVRConfig(m_lServerID,NET_DVR_GET_OPERATION_TIME_CFG,0,&struOpTimeCfg,sizeof(struOpTimeCfg),&dwReturn))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_OPERATION_TIME_CFG");
		ShowParamToWnd(&struOpTimeCfg);
		bRst = TRUE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_OPERATION_TIME_CFG");
		bRst = FALSE;
	}
	
	return bRst;
}

BOOL CDlgVideoIntercomOpTimeCfg::SetVideoIntercomOpTimeCfg()
{
	BOOL  bRst = FALSE;
	
	NET_DVR_VIDEO_INTERCOM_OPERATION_TIME_CFG struOpTimeCfg = {0};
	struOpTimeCfg.dwSize = sizeof(struOpTimeCfg);
	
	GetParamFromWnd(&struOpTimeCfg);
	
	if (NET_DVR_SetDVRConfig(m_lServerID,NET_DVR_SET_OPERATION_TIME_CFG,0,&struOpTimeCfg,sizeof(struOpTimeCfg)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_OPERATION_TIME_CFG");
		bRst = TRUE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_OPERATION_TIME_CFG");
		bRst = FALSE;
	}
	
	return bRst;
}

inline BOOL CDlgVideoIntercomOpTimeCfg::ValidIPv6(BYTE *ip)
{
    if (strlen((char *)ip) > 2 && strchr((char *)ip, ':') != NULL)
    {
        return TRUE;
    }
    return FALSE;
}

void CDlgVideoIntercomOpTimeCfg::ShowParamToWnd(NET_DVR_VIDEO_INTERCOM_OPERATION_TIME_CFG* pOpTimeCfg)
{   
	m_nUnitType = pOpTimeCfg->byUnitType;

	if (m_nUnitType == ENUM_OUTDOOR_UNIT || m_nUnitType == ENUM_FENCE_UNIT || m_nUnitType == ENUM_VILLA_OUTDOOR_UNIT ||\
        m_nUnitType == ENUM_AGAIN_UNIT)
	{
		m_nMaxMessageTime = pOpTimeCfg->uVideoIntercomUnit.struOutdoorUnit.dwMaxMessageTime;
		m_nMaxTalkTime = pOpTimeCfg->uVideoIntercomUnit.struOutdoorUnit.dwMaxTalkTime;
		
	}
	else if (m_nUnitType == ENUM_MANAGE_UNIT)
	{
		m_nMaxMonitoringTime = pOpTimeCfg->uVideoIntercomUnit.struManageUnit.dwMaxMonitoringTime;
     	m_nMaxRingTime	= pOpTimeCfg->uVideoIntercomUnit.struManageUnit.dwMaxRingTime;
        m_nMaxTalkTime  = pOpTimeCfg->uVideoIntercomUnit.struManageUnit.dwMaxTalkTime;
	}
	else if (m_nUnitType == ENUM_INDOOR_UNIT)
	{
		m_nMaxMonitoringTime = pOpTimeCfg->uVideoIntercomUnit.struIndoorUnit.dwMaxMonitoringTime;
		m_nMaxRingTime = pOpTimeCfg->uVideoIntercomUnit.struIndoorUnit.dwMaxRingTime;
        m_dwCallForwardingTime = pOpTimeCfg->uVideoIntercomUnit.struIndoorUnit.dwCallForwardingTime;
	}
	

	CheckRaidoBtn();

	UpdateData(FALSE);
}

void CDlgVideoIntercomOpTimeCfg::GetParamFromWnd(NET_DVR_VIDEO_INTERCOM_OPERATION_TIME_CFG* pOpTimeCfg)
{
	UpdateData(TRUE);
	
    if (m_nUnitType == ENUM_OUTDOOR_UNIT || m_nUnitType == ENUM_FENCE_UNIT || m_nUnitType == ENUM_VILLA_OUTDOOR_UNIT ||\
        m_nUnitType == ENUM_AGAIN_UNIT)
	{
		pOpTimeCfg->uVideoIntercomUnit.struOutdoorUnit.dwMaxMessageTime = m_nMaxMessageTime;
		pOpTimeCfg->uVideoIntercomUnit.struOutdoorUnit.dwMaxTalkTime = m_nMaxTalkTime;
		
	}
	else if (m_nUnitType == ENUM_MANAGE_UNIT)
	{
		pOpTimeCfg->uVideoIntercomUnit.struManageUnit.dwMaxMonitoringTime = m_nMaxMonitoringTime;
		pOpTimeCfg->uVideoIntercomUnit.struManageUnit.dwMaxRingTime = m_nMaxRingTime;
        pOpTimeCfg->uVideoIntercomUnit.struManageUnit.dwMaxTalkTime = m_nMaxTalkTime;
	}
	else if (m_nUnitType == ENUM_INDOOR_UNIT)
	{
		pOpTimeCfg->uVideoIntercomUnit.struIndoorUnit.dwMaxMonitoringTime = m_nMaxMonitoringTime;
		pOpTimeCfg->uVideoIntercomUnit.struIndoorUnit.dwMaxRingTime = m_nMaxRingTime;
        pOpTimeCfg->uVideoIntercomUnit.struIndoorUnit.dwCallForwardingTime = m_dwCallForwardingTime;
	}
	
	pOpTimeCfg->byUnitType = m_nUnitType;
}

void CDlgVideoIntercomOpTimeCfg::OnRadioFenceUnit() 
{
	// TODO: Add your control notification handler code here
	m_nUnitType = ENUM_FENCE_UNIT;
	CheckRaidoBtn();
}

void CDlgVideoIntercomOpTimeCfg::OnRadioAgainUnit() 
{
	// TODO: Add your control notification handler code here
    m_nUnitType = ENUM_AGAIN_UNIT;
	CheckRaidoBtn();
}

void CDlgVideoIntercomOpTimeCfg::OnRadioVillaOutdoorUnit() 
{
	// TODO: Add your control notification handler code here
    m_nUnitType = ENUM_VILLA_OUTDOOR_UNIT;
	CheckRaidoBtn();
}
