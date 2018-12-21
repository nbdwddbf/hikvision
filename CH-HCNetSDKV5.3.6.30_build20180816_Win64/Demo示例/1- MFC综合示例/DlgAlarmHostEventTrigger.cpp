// DlgAlarmHostEventTrigger.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmHostEventTrigger.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostEventTrigger dialog


CDlgAlarmHostEventTrigger::CDlgAlarmHostEventTrigger(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmHostEventTrigger::IDD, pParent)
	,m_iCurSubSystemIndex(1)
	,m_iDeviceIndex(-1)
	,m_lUserID(-1)
{
	//{{AFX_DATA_INIT(CDlgAlarmHostEventTrigger)
	//}}AFX_DATA_INIT
}


void CDlgAlarmHostEventTrigger::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmHostEventTrigger)
	DDX_Control(pDX, IDC_LIST_SUBSYSTEM_EVENT_TRIGGER_ON, m_listSubsystemTriggerOn);
	DDX_Control(pDX, IDC_LIST_SUBSYSTEM_EVENT_TRIGGER_OFF, m_listSubsystemTriggerOff);
	DDX_Control(pDX, IDC_LIST_OVERALL_EVENT_TRIGGER_OFF, m_listOverallTriggerOff);
	DDX_Control(pDX, IDC_LIST_OVERALL_EVENT_TRIGGER_ON, m_listOverallTriggerOn);
	DDX_Control(pDX, IDC_COMBO_SUBSYSTEM, m_cmSubsystem);
	DDX_Control(pDX, IDC_COMBO_ALARMOUT, m_cmAlarmout);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmHostEventTrigger, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmHostEventTrigger)
	ON_CBN_SELCHANGE(IDC_COMBO_SUBSYSTEM, OnSelchangeComboSubsystem)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostEventTrigger message handlers

BOOL CDlgAlarmHostEventTrigger::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	DWORD dwReturn = 0;
    if (NET_DVR_GetDeviceAbility(m_lUserID, ALARMHOST_ABILITY, NULL, 0, (char*)&m_struAlarmHostAbility, sizeof(m_struAlarmHostAbility)))
    {
        char szLan[128] = {0};
        g_pMainDlg->AddLog(m_lUserID, OPERATION_SUCC_T, "ALARMHOST_ABILITY");
    }
    else
    {
        g_pMainDlg->AddLog(m_lUserID, OPERATION_FAIL_T, "ALARMHOST_ABILITY");
        return FALSE;
    }
	memset(&m_struEventTrigger, 0, sizeof(m_struEventTrigger));
	InitSubSystemList();
	InitOverallList();
	InitComboBox();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlarmHostEventTrigger::InitComboBox() 
{
	char szLan[128] = {0};
	CString csStr;
	m_cmSubsystem.ResetContent();
	int i=0; 
	for (i=0; i<m_struAlarmHostAbility.wSubSystemNum; i++)
	{
		csStr.Format("%d", i+1);
		m_cmSubsystem.AddString(csStr);
	}
	g_StringLanType(szLan, "所有子系统", "All subsystem");
	csStr.Format("%s", szLan);
	m_cmSubsystem.AddString(csStr);

	m_cmAlarmout.ResetContent();
	for (i=0; i<m_struAlarmHostAbility.wLocalAlarmOutNum+m_struAlarmHostAbility.wExpandAlarmOutNum; i++)
	{
		csStr.Format("%d", i+1);
		m_cmAlarmout.AddString(csStr);
	}
}

void CDlgAlarmHostEventTrigger::InitOverallList() 
{
	char szLan[128] = {0};
	int iIndex = 0;
	int iBitIndex = 0;
	BOOL bBitState = 0;
    m_listOverallTriggerOn.SetExtendedStyle(LVS_EX_CHECKBOXES);
	m_listOverallTriggerOff.SetExtendedStyle(LVS_EX_CHECKBOXES);

	while (iBitIndex<32)
	{
		switch (iBitIndex)
		{
		case 0:
			g_StringLanType(szLan, "交流电断电", "AC outage");
			break;
		case 1:
			g_StringLanType(szLan, "电池电压低", "low voltage of battery");
			break;
		case 2:
			g_StringLanType(szLan, "电话线掉线", "telephone off_line");
			break;
		case 3:
			g_StringLanType(szLan, "有线网络异常", "network abnormal");
			break;
		case 4:
			g_StringLanType(szLan, "无线网络异常", "Wireless network abnormal");
			break;
		case 5:
			g_StringLanType(szLan, "硬盘故障", "hard disk fault");
			break;
        case 6:
            g_StringLanType(szLan, "3G/4G信号异常", "3G/4G signal abnormal");
            break;
        case 7:
            g_StringLanType(szLan, "第三方主机掉线", "third host offline");
            break;
        case 8:
            g_StringLanType(szLan, "WIFI通信故障", "WifiFault");
            break;
        case 9:
            g_StringLanType(szLan, "RF信号干扰故障", "RFSignalFault");
            break;
		default:
			break;
		}
		bBitState = (m_struAlarmHostAbility.dwOverallEvent >> iBitIndex) & 0x01;
		if (1 == bBitState)
		{
			m_listOverallTriggerOn.InsertItem(iIndex, szLan);
			m_listOverallTriggerOff.InsertItem(iIndex, szLan);
			m_listOverallTriggerOn.SetItemData(iIndex, iBitIndex);
			m_listOverallTriggerOff.SetItemData(iIndex++, iBitIndex);
		}
		iBitIndex++;
	}
}

void CDlgAlarmHostEventTrigger::InitSubSystemList() 
{
	char szLan[128] = {0};
	int iIndex = 0;
	int iBitIndex = 0;
	BOOL bBitState = 0;
	m_listSubsystemTriggerOn.SetExtendedStyle(LVS_EX_CHECKBOXES);
	m_listSubsystemTriggerOff.SetExtendedStyle(LVS_EX_CHECKBOXES);
	//bit0-进入延时，bit1-退出延时，bit2-布防，bit3-撤防，bit4-报警，bit5-消除报警记忆
	while (iBitIndex<32)
	{
		switch (iBitIndex)
		{
		case 0:
			g_StringLanType(szLan, "进入延时", "enter delay time");
			break;
		case 1:
			g_StringLanType(szLan, "退出延时", "exit delay time");
			break;
		case 2:
			g_StringLanType(szLan, "布防", "arm");
			break;
		case 3:
			g_StringLanType(szLan, "撤防", "disarm");
			break;
		case 4:
			g_StringLanType(szLan, "报警", "alarm");
			break;
		case 5:
			g_StringLanType(szLan, "消除报警记忆", "clear alarm");
			break;
		case 6:
			g_StringLanType(szLan, "报警恢复", "alarm restore");
			break;
		default:
			break;
		}
		bBitState = (m_struAlarmHostAbility.dwSubSystemEvent >> iBitIndex) & 0x01;
		if (1 == bBitState)
		{
			m_listSubsystemTriggerOn.InsertItem(iIndex, szLan);
			m_listSubsystemTriggerOff.InsertItem(iIndex, szLan);
			m_listSubsystemTriggerOn.SetItemData(iIndex, iBitIndex);
			m_listSubsystemTriggerOff.SetItemData(iIndex++, iBitIndex);
		}
		iBitIndex++;
	}
}

void CDlgAlarmHostEventTrigger::OnSelchangeComboSubsystem() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iSubSystemIndex = m_cmSubsystem.GetCurSel()+1;
	int i=0;
	int iBitIndex = 0;
	char szLan[128] = {0};
	if ((m_struAlarmHostAbility.wSubSystemNum+1) == m_iCurSubSystemIndex)
	{
		g_StringLanType(szLan, "是否修改所有子系统故障配置 ?", "modify all the sub system fault config?");
		if(IDOK != MessageBox(szLan, NULL, MB_OKCANCEL))
		{
			for (i=0; i<m_listSubsystemTriggerOn.GetItemCount(); i++)
			{
				iBitIndex = m_listSubsystemTriggerOn.GetItemData(i);
				m_listSubsystemTriggerOn.SetCheck(i, (BOOL)(m_struEventTrigger.dwSubSystemEventTriggerAlarmoutOn[iSubSystemIndex-1]>>iBitIndex)&0x01);
				m_listSubsystemTriggerOff.SetCheck(i, (BOOL)(m_struEventTrigger.dwSubSystemEventTriggerAlarmoutOff[iSubSystemIndex-1]>>iBitIndex)&0x01);
			}
			m_iCurSubSystemIndex = iSubSystemIndex;
			return;
		}
		m_struEventTrigger.dwSubSystemEventTriggerAlarmoutOn[0] = 0;
		m_struEventTrigger.dwSubSystemEventTriggerAlarmoutOff[0] = 0;
		for (i=0; i<m_listSubsystemTriggerOn.GetItemCount(); i++)
		{
			iBitIndex = m_listSubsystemTriggerOn.GetItemData(i);
			m_struEventTrigger.dwSubSystemEventTriggerAlarmoutOn[0] |= (m_listSubsystemTriggerOn.GetCheck(i) << iBitIndex);
			m_struEventTrigger.dwSubSystemEventTriggerAlarmoutOff[0] |= (m_listSubsystemTriggerOff.GetCheck(i) << iBitIndex);
		}
		//全部子系统
		for (int i=0; i<m_struAlarmHostAbility.wSubSystemNum; i++)
		{
			m_struEventTrigger.dwSubSystemEventTriggerAlarmoutOn[i] = m_struEventTrigger.dwSubSystemEventTriggerAlarmoutOn[0];	
			m_struEventTrigger.dwSubSystemEventTriggerAlarmoutOff[i] = m_struEventTrigger.dwSubSystemEventTriggerAlarmoutOff[0];
		}
	}
	else
	{
		m_struEventTrigger.dwSubSystemEventTriggerAlarmoutOn[m_iCurSubSystemIndex-1] = 0;
		m_struEventTrigger.dwSubSystemEventTriggerAlarmoutOff[m_iCurSubSystemIndex-1] = 0;
		for (i=0; i<m_listSubsystemTriggerOn.GetItemCount(); i++)
		{
			iBitIndex = m_listSubsystemTriggerOn.GetItemData(i);
			m_struEventTrigger.dwSubSystemEventTriggerAlarmoutOn[m_iCurSubSystemIndex-1] |= (m_listSubsystemTriggerOn.GetCheck(i) << iBitIndex);
			m_struEventTrigger.dwSubSystemEventTriggerAlarmoutOff[m_iCurSubSystemIndex-1] |= (m_listSubsystemTriggerOff.GetCheck(i) << iBitIndex);
		}
	}
	
	
	if ((m_struAlarmHostAbility.wSubSystemNum+1) == iSubSystemIndex)
	{
		//选择所有子系统时，将显示界面清空
		for (i=0; i<m_listSubsystemTriggerOn.GetItemCount(); i++)
		{
			m_listSubsystemTriggerOn.SetCheck(i, FALSE);
			m_listSubsystemTriggerOff.SetCheck(i, FALSE);
		}
	}
	else
	{
		for (i=0; i<m_listSubsystemTriggerOn.GetItemCount(); i++)
		{
			iBitIndex = m_listSubsystemTriggerOn.GetItemData(i);
			m_listSubsystemTriggerOn.SetCheck(i, (BOOL)(m_struEventTrigger.dwSubSystemEventTriggerAlarmoutOn[iSubSystemIndex-1]>>iBitIndex)&0x01);
			m_listSubsystemTriggerOff.SetCheck(i, (BOOL)(m_struEventTrigger.dwSubSystemEventTriggerAlarmoutOff[iSubSystemIndex-1]>>iBitIndex)&0x01);
		}
	}
	m_iCurSubSystemIndex = iSubSystemIndex;
	UpdateData(FALSE);
}

void CDlgAlarmHostEventTrigger::GetEventInfoFromDlg()
{
	UpdateData(TRUE);
	int i=0;
	int iBitIndex = 0;
	m_struEventTrigger.dwOverallEventTriggerAlarmoutOn = 0;
	m_struEventTrigger.dwOverallEventTriggerAlarmoutOff = 0;
	for (i=0; i<m_listOverallTriggerOn.GetItemCount(); i++)
	{
		iBitIndex = m_listOverallTriggerOn.GetItemData(i);
		m_struEventTrigger.dwOverallEventTriggerAlarmoutOn |= ((m_listOverallTriggerOn.GetCheck(i) << iBitIndex));
		m_struEventTrigger.dwOverallEventTriggerAlarmoutOff |= ((m_listOverallTriggerOff.GetCheck(i) << iBitIndex));
	}
	OnSelchangeComboSubsystem();	
}

void CDlgAlarmHostEventTrigger::SetEventInfoToDlg()
{
	UpdateData(TRUE);
	int i=0;
	int iBitIndex = 0;
	for (i=0; i<m_listOverallTriggerOn.GetItemCount(); i++)
	{
		iBitIndex = m_listOverallTriggerOn.GetItemData(i);
		m_listOverallTriggerOn.SetCheck(i, (BOOL)(m_struEventTrigger.dwOverallEventTriggerAlarmoutOn>>iBitIndex)&0x01);
		m_listOverallTriggerOff.SetCheck(i, (BOOL)(m_struEventTrigger.dwOverallEventTriggerAlarmoutOff>>iBitIndex)&0x01);
	}
	m_cmSubsystem.SetCurSel(0);
	for (i=0; i<m_listSubsystemTriggerOn.GetItemCount(); i++)
	{
		iBitIndex = m_listSubsystemTriggerOn.GetItemData(i);
		m_listSubsystemTriggerOn.SetCheck(i, (BOOL)(m_struEventTrigger.dwSubSystemEventTriggerAlarmoutOn[0]>>iBitIndex)&0x01);
		m_listSubsystemTriggerOff.SetCheck(i, (BOOL)(m_struEventTrigger.dwSubSystemEventTriggerAlarmoutOff[0]>>iBitIndex)&0x01);
	}
	UpdateData(FALSE);
	m_iCurSubSystemIndex = 1;
}

void CDlgAlarmHostEventTrigger::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	m_struEventTrigger.dwSize = sizeof(m_struEventTrigger);
	DWORD dwReturn = 0;
	int iAlarmoutIndex = m_cmAlarmout.GetCurSel();
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_ALARMHOST_EVENT_TRIG_ALARMOUT_CFG, iAlarmoutIndex, &m_struEventTrigger, sizeof(m_struEventTrigger), &dwReturn))
	{
		g_StringLanType(szLan, "获取事件触发报警输出配置失败", "Get event trig alarmout config failed");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szLan);
		return;
	}
	else
	{
		g_StringLanType(szLan, "获取事件触发报警输出配置成功", "Get event trig alarmout config successful");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szLan);
	}
	SetEventInfoToDlg();	
}

void CDlgAlarmHostEventTrigger::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	GetEventInfoFromDlg();
	m_struEventTrigger.dwSize = sizeof(m_struEventTrigger);
	int iAlarmoutIndex = m_cmAlarmout.GetCurSel();
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_ALARMHOST_EVENT_TRIG_ALARMOUT_CFG, iAlarmoutIndex, &m_struEventTrigger, sizeof(m_struEventTrigger)))
	{
		g_StringLanType(szLan, "设置事件触发报警输出配置失败", "Get fault process config failed");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szLan);
		return;
	}
	else
	{
		g_StringLanType(szLan, "设置事件触发报警输出配置成功", "Get fault process config successful");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szLan);
	}
}
