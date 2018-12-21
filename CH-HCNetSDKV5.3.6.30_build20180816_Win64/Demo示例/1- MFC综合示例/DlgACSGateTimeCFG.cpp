// DlgACSGateTimeCFG.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgACSGateTimeCFG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgACSGateTimeCFG dialog


CDlgACSGateTimeCFG::CDlgACSGateTimeCFG(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgACSGateTimeCFG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgACSGateTimeCFG)
	m_uHoldonAlarmTime = 0;
	m_uHoldonGateOpenTime = 0;
	m_uNolaneAccessTimeLimitTime = 0;
	m_uPostponeIntrusionAlarmTime = 0;
	m_uSafetyZoneStayTime = 0;
    m_uIRTriggerTimeoutTime = 0;
	//}}AFX_DATA_INIT
}


void CDlgACSGateTimeCFG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgACSGateTimeCFG)
	DDX_Text(pDX, IDC_EDIT_HOLDON_ALARM_TIME, m_uHoldonAlarmTime);
	DDX_Text(pDX, IDC_EDIT_HOLDON_GATE_OPEN_TIME, m_uHoldonGateOpenTime);
	DDX_Text(pDX, IDC_EDIT_NOLANE_ACCESS_TIME_LIMIT_TIME, m_uNolaneAccessTimeLimitTime);
	DDX_Text(pDX, IDC_EDIT_POSTPONE_INTRUSI0N_ALARM_TIME, m_uPostponeIntrusionAlarmTime);
	DDX_Text(pDX, IDC_EDIT_SAFETY_ZONE_STAY_TIME, m_uSafetyZoneStayTime);
    DDX_Text(pDX, IDC_EDIT_IR_TRIGGER_TIMEOUT_TIME, m_uIRTriggerTimeoutTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgACSGateTimeCFG, CDialog)
	//{{AFX_MSG_MAP(CDlgACSGateTimeCFG)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgACSGateTimeCFG message handlers

void CDlgACSGateTimeCFG::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    DWORD dwReturn = 0;
    NET_DVR_GATE_TIME_CFG struGateTimeCfg = {0};
    struGateTimeCfg.dwSize = sizeof(struGateTimeCfg);
    
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_GATE_TIME_CFG, 0, &struGateTimeCfg, sizeof(struGateTimeCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_GATE_TIME_CFG Failed");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_GATE_TIME_CFG SUCC");
        m_uHoldonAlarmTime = struGateTimeCfg.dwHoldOnALarmTime;
        m_uHoldonGateOpenTime = struGateTimeCfg.dwHoldOnGateOpenTime;
        m_uNolaneAccessTimeLimitTime = struGateTimeCfg.dwNoLaneAccessTimeLimitTime;
        m_uPostponeIntrusionAlarmTime = struGateTimeCfg.dwPostponeIntrusionAlarmTime;
        m_uSafetyZoneStayTime = struGateTimeCfg.dwSafetyZoneStayTime;
        m_uIRTriggerTimeoutTime = struGateTimeCfg.byIRTriggerTimeoutTime;
        UpdateData(FALSE);
	}
}

void CDlgACSGateTimeCFG::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_GATE_TIME_CFG struGateTimeCfg = {0};
    struGateTimeCfg.dwSize = sizeof(struGateTimeCfg);
    
    struGateTimeCfg.dwHoldOnALarmTime = m_uHoldonAlarmTime;
    struGateTimeCfg.dwHoldOnGateOpenTime = m_uHoldonGateOpenTime;
    struGateTimeCfg.dwNoLaneAccessTimeLimitTime = m_uNolaneAccessTimeLimitTime;
    struGateTimeCfg.dwPostponeIntrusionAlarmTime = m_uPostponeIntrusionAlarmTime;
    struGateTimeCfg.dwSafetyZoneStayTime = m_uSafetyZoneStayTime;
    struGateTimeCfg.byIRTriggerTimeoutTime = m_uIRTriggerTimeoutTime;
 
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_GATE_TIME_CFG, 0, &struGateTimeCfg, sizeof(struGateTimeCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_GATE_TIME_CFG Failed");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_GATE_TIME_CFG SUCC");
	}
}
