// DlgAlarmOutCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmOutCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmOutCfg dialog


CDlgAlarmOutCfg::CDlgAlarmOutCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmOutCfg::IDD, pParent)
,m_iSirenDelayTime(0)
,m_iDevIndex(-1)
, m_csOutputIndex(_T(""))
{
	//{{AFX_DATA_INIT(CDlgAlarmOutCfg)
	m_iDelayTime = 0;
	m_csName = _T("");
	m_csSirenName = _T("");
	m_iSirenDelayTime = 0;
	m_TimeOff = 0;
	m_TimeOn = 0;
	//}}AFX_DATA_INIT
    memset(&m_struAbility, 0, sizeof(m_struAbility));
    m_lServerID = -1;
    m_iDevIndex = -1;
    memset(&m_struAlarmOutParam, 0, sizeof(m_struAlarmOutParam));
    memset(&m_struSirenParam, 0, sizeof(m_struSirenParam));
}


void CDlgAlarmOutCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgAlarmOutCfg)
    DDX_Control(pDX, IDC_COMBO_WORK_MODE, m_comWorkMode);
    DDX_Control(pDX, IDC_COMBO_ALARMOUT_MODE, m_comAlarmOutMode);
    DDX_Control(pDX, IDC_COMBO_OUT_MODULE_TYPE, m_comAlarmOutModuleMode);
    DDX_Control(pDX, IDC_COMBO_SUBSYSTEM_NO, m_cmSubsystemNo);
    DDX_Control(pDX, IDC_LIST_SUBSYSTEM_EVENT_ON, m_listSubsystemEventOn);
    DDX_Control(pDX, IDC_LIST_SUBSYSTEM_EVENT_OFF, m_listSubsystemEventOff);
    DDX_Control(pDX, IDC_LIST_OVERALL_EVENT_ON, m_listOverallEventOn);
    DDX_Control(pDX, IDC_LIST_OVERALL_EVENT_OFF, m_listOverallEventOff);
    DDX_Control(pDX, IDC_COMBO_SIREN_INDEX, m_comboSirenIndex);
    DDX_Control(pDX, IDC_COMBO_ALARMLAMP_INDEX, m_comboAlarmLampIndex);
    DDX_Control(pDX, IDC_COMBO_ALARMOUT_INDEX, m_comboAlarmOutIndex);
    DDX_Text(pDX, IDC_EDIT_DELAY_TIME, m_iDelayTime);
    DDX_Text(pDX, IDC_EDIT_NAME, m_csName);
    DDV_MaxChars(pDX, m_csName, 32);
    DDX_Text(pDX, IDC_EDIT_SIREN_NAME, m_csSirenName);
    DDV_MaxChars(pDX, m_csSirenName, 32);
    DDX_Text(pDX, IDC_EDIT_SIREN_DELAYTIME, m_iSirenDelayTime);
    DDX_Text(pDX, IDC_TIME_OFF, m_TimeOff);
    DDX_Text(pDX, IDC_TIME_ON, m_TimeOn);
    //}}AFX_DATA_MAP
    DDX_CBString(pDX, IDC_COMBO_ALARMOUT_INDEX, m_csOutputIndex);
}


BEGIN_MESSAGE_MAP(CDlgAlarmOutCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmOutCfg)
	ON_BN_CLICKED(IDC_BTN_SET_ALARMOUT_PARAM, OnBtnSetAlarmoutParam)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARMOUT_INDEX, OnSelchangeComboAlarmoutIndex)
	ON_BN_CLICKED(IDC_BTN_OPEN_ALARMOUT, OnBtnOpenAlarmout)
	ON_BN_CLICKED(IDC_BTN_CLOSE_ALARMOUT, OnBtnCloseAlarmout)
	ON_BN_CLICKED(IDC_BNT_SET_SIREN_PARAM, OnBntSetSirenParam)
	ON_CBN_SELCHANGE(IDC_COMBO_SIREN_INDEX, OnSelchangeComboSirenIndex)
	ON_BN_CLICKED(IDC_BTN_OPEN_SIREN, OnBtnOpenSiren)
	ON_BN_CLICKED(IDC_BTN_CLOSE_SIREN, OnBtnCloseSiren)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_ALARM_IN, OnRclickListAlarmIn)
	ON_BN_CLICKED(IDC_BTN_OPEN_ALARMOUT_ALL, OnBtnOpenAlarmoutAll)
	ON_BN_CLICKED(IDC_BTN_CLOSE_ALARMOUT_ALL, OnBtnCloseAlarmoutAll)
	ON_CBN_SELCHANGE(IDC_COMBO_SUBSYSTEM_NO, OnSelchangeComboSubsystemNo)
    ON_BN_CLICKED(IDC_BTN_OPEN_ALARMLAMP, OnBtnOpenAlarmlamp)
    ON_BN_CLICKED(IDC_BTN_CLOSE_ALARMLAMP, OnBtnCloseAlarmlamp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmOutCfg message handlers

BOOL CDlgAlarmOutCfg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    InitWnd();

    m_comboAlarmOutIndex.SetCurSel(0);
    OnSelchangeComboAlarmoutIndex();
    
    if (m_struAbility.wSirenNum > 0)
    {
        m_comboSirenIndex.SetCurSel(0);
        OnSelchangeComboSirenIndex();
    }
    if (m_struAbility.byAlarmLampNum > 0)
    {
        m_comboAlarmLampIndex.SetCurSel(0);
    }
	SetAlarmOutParamToWnd(m_struAlarmOutParam);
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlarmOutCfg::InitWnd()
{
    InitAlarmOutIndex();
    InitSirenIndexCombo();
    InitAlarmLampIndexCombo();
	InitOverallList();
	InitSubsystemList();
	InitSubsystemIndex();
}


void CDlgAlarmOutCfg::InitAlarmOutIndex()
{
    char szLan[128] = {0};
    
    for (int i = 0; i < (m_struAbility.wLocalAlarmOutNum + m_struAbility.wExpandAlarmOutNum); i++)
    {
        sprintf(szLan, "Alarm out %d", i + 1);
        m_comboAlarmOutIndex.AddString(szLan);
    }
}


void CDlgAlarmOutCfg::InitSirenIndexCombo()
{
    char szLan[128] = {0};
    for (int i = 0; i <m_struAbility.wSirenNum; i++)
    {
        sprintf(szLan, "Siren %d", (i+1));
        m_comboSirenIndex.AddString(szLan);
    }
}

void CDlgAlarmOutCfg::InitAlarmLampIndexCombo()
{
    char szLan[128] = { 0 };
    for (int i = 0; i < m_struAbility.byAlarmLampNum; i++)
    {
        sprintf(szLan, "Lamp %d", (i + 1));
        m_comboAlarmLampIndex.AddString(szLan);
    }
}

void CDlgAlarmOutCfg::InitOverallList() 
{
	char szLan[128] = {0};
	int iIndex = 0;
	int iBitIndex = 0;
	BOOL bBitState = 0;
    m_listOverallEventOn.SetExtendedStyle(LVS_EX_CHECKBOXES);	
	g_StringLanType(szLan, "主机防拆", "Tamper Alarm");
	m_listOverallEventOn.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "全局键盘紧急报警", "Emergency Keypad Alarms");
	m_listOverallEventOn.InsertItem(iIndex++, szLan);

	g_StringLanType(szLan, "交流电断电", "AC power off");
	m_listOverallEventOn.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "电池电压低", "Low battery voltage");
	m_listOverallEventOn.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "电话线掉线", "The phone off line");
	m_listOverallEventOn.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "有线网络异常", "The wired network anomaly");
	m_listOverallEventOn.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "无线网络异常", "Wireless network anomaly");
	m_listOverallEventOn.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "键盘485断线", "Keyboard 485 break");
	m_listOverallEventOn.InsertItem(iIndex++, szLan);
    g_StringLanType(szLan, "WIFI通信故障", "wifi fault");
    m_listOverallEventOn.InsertItem(iIndex++, szLan);
    g_StringLanType(szLan, "RF信号干扰故障", "RF signal fault");
    m_listOverallEventOn.InsertItem(iIndex++, szLan);

	iIndex = 0;
	m_listOverallEventOff.SetExtendedStyle(LVS_EX_CHECKBOXES);
// 	g_StringLanType(szLan, "紧急报警", "Emergency Keypad Alarms");
// 	m_listOverallEventOff.InsertItem(iIndex++, szLan);
// 	g_StringLanType(szLan, "主机防拆", "Tamper Alarm");
// 	m_listOverallEventOff.InsertItem(iIndex++, szLan);
}

void CDlgAlarmOutCfg::InitSubsystemList() 
{
	char szLan[128] = {0};
	int iIndex = 0;
	int iBitIndex = 0;
	BOOL bBitState = 0;
    m_listSubsystemEventOn.SetExtendedStyle(LVS_EX_CHECKBOXES);	
	g_StringLanType(szLan, "紧急报警", "Emergency Keypad Alarms");
	m_listSubsystemEventOn.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "布防", "Arm");
	m_listSubsystemEventOn.InsertItem(iIndex++, szLan);
	g_StringLanType(szLan, "撤防", "Disarm");
	m_listSubsystemEventOn.InsertItem(iIndex++, szLan);
// 	g_StringLanType(szLan, "主机防拆", "Tamper Alarm");
// 	m_listSubsystemEventOn.InsertItem(iIndex++, szLan);
	
	iIndex = 0;
	m_listSubsystemEventOff.SetExtendedStyle(LVS_EX_CHECKBOXES);
// 	g_StringLanType(szLan, "紧急报警", "Emergency Keypad Alarms");
// 	m_listSubsystemEventOff.InsertItem(iIndex++, szLan);
// 	g_StringLanType(szLan, "主机防拆", "Tamper Alarm");
// 	m_listSubsystemEventOff.InsertItem(iIndex++, szLan);
}

void CDlgAlarmOutCfg::InitSubsystemIndex()
{
    char szLan[128] = {0};
    
    for (int i = 0; i < (m_struAbility.wSubSystemNum); i++)
    {
        sprintf(szLan, "Subsystem %d", i + 1);
        m_cmSubsystemNo.AddString(szLan);
    }
	//m_cmSubsystemNo.SetCurSel(0);
	m_iCurSubSystemIndex = 0;
}

BOOL CDlgAlarmOutCfg::GetAlarmOutParam(NET_DVR_ALARMOUT_PARAM& struAlarmOutParam, LONG lAlarmOutPort)
{
    BOOL bRet = FALSE;
    DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_ALARMOUT_PARAM, lAlarmOutPort, &struAlarmOutParam, sizeof(struAlarmOutParam), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARMOUT_PARAM");
        bRet = TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMOUT_PARAM");
        bRet = FALSE;
    }

    return bRet;
}

BOOL CDlgAlarmOutCfg::SetAlarmOutParam(NET_DVR_ALARMOUT_PARAM& struAlarmOutParam, LONG lAlarmOutPort)
{
    BOOL bRet = FALSE;

    if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_ALARMOUT_PARAM, lAlarmOutPort, &struAlarmOutParam, sizeof(struAlarmOutParam)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_ALARMOUT_PARAM");
        bRet = TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_ALARMOUT_PARAM");
        bRet = FALSE;
    }
    return bRet;
}

BOOL CDlgAlarmOutCfg::SetAlarmOut(LONG lAlarmOutPort, LONG lAlarmOutStatic)
{
    BOOL bRet = FALSE;
    
    if (NET_DVR_SetAlarmHostOut(m_lServerID, lAlarmOutPort, lAlarmOutStatic))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SetAlarmHostOut");
        bRet = TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SetAlarmHostOut");
        bRet = FALSE;
    }
    return bRet;
}

BOOL CDlgAlarmOutCfg::GetSirenParam(NET_DVR_SIREN_PARAM& struSirenParam)
{
	UpdateData(TRUE);
    BOOL bRet = FALSE;
    DWORD dwRetrun = 0;
    LONG lSirenIndex = m_comboSirenIndex.GetCurSel() + 1;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_SIREN_PARAM, lSirenIndex, &struSirenParam, sizeof(struSirenParam), &dwRetrun))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SIREN_PARAM");
        bRet = TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SIREN_PARAM");
        bRet = FALSE;
    }
    return bRet;
}

BOOL CDlgAlarmOutCfg::SetSirenParam(NET_DVR_SIREN_PARAM& struSirenParam)
{
    BOOL bRet = FALSE;
    LONG lSirenIndex = m_comboSirenIndex.GetCurSel() + 1;
    if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_SIREN_PARAM, lSirenIndex, &struSirenParam, sizeof(struSirenParam)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SIREN_PARAM");
        bRet = TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SIREN_PARAM");
        bRet = FALSE;
    }
    return bRet;
}

BOOL CDlgAlarmOutCfg::SirenControl(LONG lSirenStatic)
{
    BOOL bRet = FALSE;
    LONG lSirenIndex = m_comboSirenIndex.GetCurSel() + 1;

    if (NET_DVR_AlarmHostAssistantControl(m_lServerID, 4, lSirenIndex, lSirenStatic))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_AlarmHostAssistantControl [%d]", lSirenStatic);
        bRet = TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_AlarmHostAssistantControl [%d]", lSirenStatic);
        bRet = FALSE;
    }
    return bRet;
}

BOOL CDlgAlarmOutCfg::AlarmLampControl(LONG lAlarmLampStatic)
{
    BOOL bRet = FALSE;
    LONG lAlarmIndex = m_comboAlarmLampIndex.GetCurSel() + 1;

    if (NET_DVR_AlarmHostAssistantControl(m_lServerID, 5, lAlarmIndex, lAlarmLampStatic))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_AlarmHostAssistantControl [%d]", lAlarmLampStatic);
        bRet = TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_AlarmHostAssistantControl [%d]", lAlarmLampStatic);
        bRet = FALSE;
    }
    return bRet;
}

void CDlgAlarmOutCfg::GetAlarmOutParamFromWnd(NET_DVR_ALARMOUT_PARAM &struAlarmOutParam)
{
	UpdateData(TRUE);
    strncpy((char*)struAlarmOutParam.byName, m_csName.GetBuffer(0), sizeof(struAlarmOutParam.byName));
    struAlarmOutParam.wDelay = m_iDelayTime;
	struAlarmOutParam.byTimeOn = m_TimeOn;
	struAlarmOutParam.byTimeOff = m_TimeOff;
	struAlarmOutParam.byWorkMode = m_comWorkMode.GetCurSel() + 1;
	struAlarmOutParam.byAlarmOutMode = m_comAlarmOutMode.GetCurSel() + 1;
    struAlarmOutParam.byModuleType = m_comAlarmOutModuleMode.GetCurSel() + 1;
//	GetAlarmoutEventTriggerFromWnd(&struAlarmOutParam.dwEventTriggerAlarmOn, &struAlarmOutParam.dwEventTriggerAlarmOff);
}


void CDlgAlarmOutCfg::SetAlarmOutParamToWnd(NET_DVR_ALARMOUT_PARAM &struAlarmOutParam)
{
    char szLan[40] = {0};
    strncpy(szLan, (char*)struAlarmOutParam.byName, sizeof(struAlarmOutParam.byName));
    m_csName = szLan;
    m_iDelayTime = struAlarmOutParam.wDelay;
	m_TimeOn = struAlarmOutParam.byTimeOn;
	m_TimeOff = struAlarmOutParam.byTimeOff;
	m_comWorkMode.SetCurSel(struAlarmOutParam.byWorkMode-1);
	m_comAlarmOutMode.SetCurSel(struAlarmOutParam.byAlarmOutMode-1);
    m_comAlarmOutModuleMode.SetCurSel(struAlarmOutParam.byModuleType - 1);
	UpdateData(FALSE);
}

void CDlgAlarmOutCfg::OnBtnSetAlarmoutParam() 
{
    UpdateData(TRUE);
	GetAlarmOutParamFromWnd(m_struAlarmOutParam);
    SetAlarmOutParam(m_struAlarmOutParam, m_comboAlarmOutIndex.GetCurSel());
}

void CDlgAlarmOutCfg::OnSelchangeComboAlarmoutIndex() 
{
    GetAlarmOutParam(m_struAlarmOutParam, m_comboAlarmOutIndex.GetCurSel());
    SetAlarmOutParamToWnd(m_struAlarmOutParam);
    UpdateData(FALSE);
}

void CDlgAlarmOutCfg::OnBtnOpenAlarmout() 
{
    UpdateData(TRUE);
    DWORD dwOutputIndex = atoi(m_csOutputIndex);
    if (!SetAlarmOut(dwOutputIndex, 1))
    {
        AfxMessageBox("Fail to set alarm out");
    }
}

void CDlgAlarmOutCfg::OnBtnCloseAlarmout() 
{
    UpdateData(TRUE);
    DWORD dwOutputIndex = atoi(m_csOutputIndex);
    if (!SetAlarmOut(dwOutputIndex, 0))
    {
        AfxMessageBox("Fail to set alarm out");
    }	
}

void CDlgAlarmOutCfg::OnBntSetSirenParam() 
{
	UpdateData(TRUE);
    GetSirenParamFromWnd(m_struSirenParam);
    SetSirenParam(m_struSirenParam);
}

void CDlgAlarmOutCfg::OnSelchangeComboSirenIndex() 
{
   	GetSirenParam(m_struSirenParam);
    SetSirenParamToWnd(m_struSirenParam);
	m_cmSubsystemNo.SetCurSel(0);
    UpdateData(FALSE);
	OnSelchangeComboSubsystemNo();
}

void CDlgAlarmOutCfg::GetSirenParamFromWnd(NET_DVR_SIREN_PARAM &struSirenParam)
{
    struSirenParam.wDelay = m_iSirenDelayTime;
    strncpy((char*)struSirenParam.byName, m_csSirenName.GetBuffer(0), sizeof(struSirenParam.byName));
	m_struSirenParam.dwOverallEventJointSirenOn = 0;
	//m_struSirenParam.dwOverallEventJointSirenOff = 0;
	int i=0;
	for (i=0; i<m_listOverallEventOn.GetItemCount(); i++)
	{
		m_struSirenParam.dwOverallEventJointSirenOn |= m_listOverallEventOn.GetCheck(i)<<i;
	}

	for (i=0; i<m_listOverallEventOn.GetItemCount(); i++)
	{
		m_struSirenParam.dwOverallEventJointSirenOn |= m_listOverallEventOn.GetCheck(i)<<i;
	}

	OnSelchangeComboSubsystemNo();
}   

void CDlgAlarmOutCfg::SetSirenParamToWnd(NET_DVR_SIREN_PARAM &struSirenParam)
{
    m_iSirenDelayTime = struSirenParam.wDelay;
    char szLan[40] = {0};
    strncpy(szLan, (char *)struSirenParam.byName, sizeof(struSirenParam.byName));
    m_csSirenName = szLan;

	for (int i=0; i<m_listOverallEventOn.GetItemCount(); i++)
	{
		m_listOverallEventOn.SetCheck(i, (BOOL)(m_struSirenParam.dwOverallEventJointSirenOn>>i)&0x01);
	//	m_listOverallEventOff.SetCheck(i, (BOOL)(m_struSirenParam.dwOverallEventJointSirenOff>>i)&0x01);
	}
	UpdateData(FALSE);

}

void CDlgAlarmOutCfg::OnBtnOpenSiren() 
{
    if (!SirenControl(1))
    {
        AfxMessageBox("Fail to set open siren");
    }
}

void CDlgAlarmOutCfg::OnBtnCloseSiren() 
{
    if (!SirenControl(0))
    {
        AfxMessageBox("Fail to set close siren"); 
    }
}

void CDlgAlarmOutCfg::OnRclickListAlarmIn(NMHDR* pNMHDR, LRESULT* pResult) 
{
    CMenu pMenu;
    
    if (!pMenu.LoadMenu(IDR_MENU_SELECT_MODE))
    {
        return;
    }
    CPoint point;
    GetCursorPos(&point);
    pMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
    *pResult = 0;
}



void CDlgAlarmOutCfg::OnBtnOpenAlarmoutAll() 
{
//    for (int i = 1; i <= m_comboAlarmOutIndex.GetCount(); i++)
    {
        SetAlarmOut(0xffffffff, 1);
    }
}

void CDlgAlarmOutCfg::OnBtnCloseAlarmoutAll() 
{
//    for (int i = 1; i <= m_comboAlarmOutIndex.GetCount(); i++)
    {
        SetAlarmOut(0xffffffff, 0);
    }	
}

void CDlgAlarmOutCfg::OnSelchangeComboSubsystemNo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	int iSubSystemIndex = m_cmSubsystemNo.GetCurSel()+1;
	int i=0;
	int iBitIndex = 0;
	char szLan[128] = {0};
	if ((m_struAbility.wSubSystemNum+1) == m_iCurSubSystemIndex)
	{
		g_StringLanType(szLan, "是否修改所有子系统配置 ?", "modify all the sub system config?");
		if(IDOK != MessageBox(szLan, NULL, MB_OKCANCEL))
		{
			for (i=0; i<m_listSubsystemEventOn.GetItemCount(); i++)
			{
				//iBitIndex = m_listSubsystemEventOn.GetItemData(i);
				m_listSubsystemEventOn.SetCheck(i, (BOOL)(m_struSirenParam.dwSubsystemEventJointSirenOn[iSubSystemIndex-1]>>i)&0x01);
			}
			m_iCurSubSystemIndex = iSubSystemIndex;
			return;
		}
		m_struSirenParam.dwSubsystemEventJointSirenOn[0] = 0;
		for (i=0; i<m_listSubsystemEventOn.GetItemCount(); i++)
		{
			//iBitIndex = m_listSubsystemEventOn.GetItemData(i);
			m_struSirenParam.dwSubsystemEventJointSirenOn[0] |= (m_listSubsystemEventOn.GetCheck(i) << i);
		}
		//全部子系统
		for (int i=0; i<m_struAbility.wSubSystemNum; i++)
		{
			m_struSirenParam.dwSubsystemEventJointSirenOn[i] = m_struSirenParam.dwSubsystemEventJointSirenOn[0];	
		}
	}
	else
	{
		m_struSirenParam.dwSubsystemEventJointSirenOn[m_iCurSubSystemIndex-1] = 0;
		for (i=0; i<m_listSubsystemEventOn.GetItemCount(); i++)
		{
			//iBitIndex = m_listSubsystemEventOn.GetItemData(i);
			m_struSirenParam.dwSubsystemEventJointSirenOn[m_iCurSubSystemIndex-1] |= (m_listSubsystemEventOn.GetCheck(i) << i);
		}
	}
	
	if ((m_struAbility.wSubSystemNum+1) == iSubSystemIndex)
	{
		//选择所有子系统时，将显示界面清空
		for (i=0; i<m_listSubsystemEventOn.GetItemCount(); i++)
		{
			m_listSubsystemEventOn.SetCheck(i, FALSE);
			m_listSubsystemEventOff.SetCheck(i, FALSE);
		}
	}
	else
	{
		for (i=0; i<m_listSubsystemEventOn.GetItemCount(); i++)
		{
			m_listSubsystemEventOn.SetCheck(i, (BOOL)(m_struSirenParam.dwSubsystemEventJointSirenOn[iSubSystemIndex-1]>>i)&0x01);
		}
	}
	m_iCurSubSystemIndex = iSubSystemIndex;
}

void CDlgAlarmOutCfg::OnBtnOpenAlarmlamp()
{
    // TODO:  在此添加控件通知处理程序代码
    if (!AlarmLampControl(1))
    {
        AfxMessageBox("Fail to set open alarm lamp");
    }
}


void CDlgAlarmOutCfg::OnBtnCloseAlarmlamp()
{
    // TODO:  在此添加控件通知处理程序代码
    if (!AlarmLampControl(0))
    {
        AfxMessageBox("Fail to set close alarm lamp");
    }
}