// DlgAlarmhostModuleCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmhostModuleCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmhostModuleCfg dialog


CDlgAlarmhostModuleCfg::CDlgAlarmhostModuleCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmhostModuleCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAlarmhostModuleCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgAlarmhostModuleCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmhostModuleCfg)
	DDX_Control(pDX, IDC_COMBO_ZONE_TYPE, m_cmZoneType);
	DDX_Control(pDX, IDC_COMBO_TRIGGER_TYPE, m_cmTriggerType);
	DDX_Control(pDX, IDC_COMBO_MODULE_TYPE, m_cmModuleType);
	DDX_Control(pDX, IDC_COMBO_MODULE_ADDR, m_cmModuleAddress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmhostModuleCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmhostModuleCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmhostModuleCfg message handlers

void CDlgAlarmhostModuleCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	memset(&m_struModuleCfg, 0, sizeof(m_struModuleCfg));
	m_struModuleCfg.dwSize = sizeof(m_struModuleCfg);
	DWORD dwReturn = 0;
	int iModuleAddr = m_cmModuleAddress.GetCurSel();
	int iZoneTypeCount = m_cmZoneType.GetCount();
	int iTriggerTypeCount = m_cmTriggerType.GetCount();
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_ALARMHOST_MODULE_CFG, iModuleAddr, &m_struModuleCfg, sizeof(m_struModuleCfg), &dwReturn))
	{
		MessageBox("Get Module Config Failed");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMHOST_MODULE_CFG failed");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARMHOST_MODULE_CFG successful");
	}

	m_cmModuleType.SetCurSel(m_struModuleCfg.byModuleType - 1);
	if (0xff == m_struModuleCfg.byZoneType)
	{
		m_cmZoneType.SetCurSel(iZoneTypeCount - 1);
	}
	else
	{
		m_cmZoneType.SetCurSel(m_struModuleCfg.byZoneType - 1);
	}
	if (0xff == m_struModuleCfg.byTriggerType)
	{
		m_cmTriggerType.SetCurSel(iTriggerTypeCount - 1);
	}
	else
	{
		m_cmTriggerType.SetCurSel(m_struModuleCfg.byTriggerType - 1);
	}
	UpdateData(FALSE);
}

BOOL CDlgAlarmhostModuleCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	int i = 0;
	CString csStr;
	m_cmModuleAddress.ResetContent();
	for (i=0; i<256; i++)
	{
		csStr.Format("%d", i);
		m_cmModuleAddress.AddString(csStr);
	}
	g_StringLanType(m_szLan, "防区", "Zone");
	csStr.Format("%s", m_szLan);
	m_cmModuleType.AddString(csStr);
	g_StringLanType(m_szLan, "触发器", "Trigger");
	csStr.Format("%s", m_szLan);
	m_cmModuleType.AddString(csStr);
	g_StringLanType(m_szLan, "防区触发器", "Trigger");
	csStr.Format("%s", m_szLan);
	m_cmModuleType.AddString(csStr);

	g_StringLanType(m_szLan, "本地防区", "local zone");
	csStr.Format("%s", m_szLan);
	m_cmZoneType.AddString(csStr);
	g_StringLanType(m_szLan, "单防区", "single zone");
	csStr.Format("%s", m_szLan);
	m_cmZoneType.AddString(csStr);
	g_StringLanType(m_szLan, "双防区", "double zone");
	csStr.Format("%s", m_szLan);
	m_cmZoneType.AddString(csStr);
	g_StringLanType(m_szLan, "8防区", "8 zone");
	csStr.Format("%s", m_szLan);
	m_cmZoneType.AddString(csStr);
	g_StringLanType(m_szLan, "模拟量防区", "sensor zone");
	csStr.Format("%s", m_szLan);
	m_cmZoneType.AddString(csStr);
	g_StringLanType(m_szLan, "单防区触发器", "sensor zone");
	csStr.Format("%s", m_szLan);
	m_cmZoneType.AddString(csStr);
	g_StringLanType(m_szLan, "未知类型", "unknown");
	csStr.Format("%s", m_szLan);
	m_cmZoneType.AddString(csStr);

	g_StringLanType(m_szLan, "本地触发器", "local zone");
	csStr.Format("%s", m_szLan);
	m_cmTriggerType.AddString(csStr);
	g_StringLanType(m_szLan, "4路触发器", "single zone");
	csStr.Format("%s", m_szLan);
	m_cmTriggerType.AddString(csStr);
	g_StringLanType(m_szLan, "8路触发器", "double zone");
	csStr.Format("%s", m_szLan);
	m_cmTriggerType.AddString(csStr);
	g_StringLanType(m_szLan, "单防区触发器", "double zone");
	csStr.Format("%s", m_szLan);
	m_cmTriggerType.AddString(csStr);
	g_StringLanType(m_szLan, "未知类型", "unknown");
	csStr.Format("%s", m_szLan);
	m_cmTriggerType.AddString(csStr);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
