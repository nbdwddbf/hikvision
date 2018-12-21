// DlgAlarmHostStatus.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmHostStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostStatus dialog

CDlgAlarmHostStatus::CDlgAlarmHostStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmHostStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAlarmHostStatus)
	m_bSirenStaus = FALSE;
    m_bSirenStaus1 = FALSE;
    m_bSirenStaus2 = FALSE;
	//}}AFX_DATA_INIT
    memset(&m_struAlarmHostAbility, 0, sizeof(m_struAlarmHostAbility));
    m_iDevIndex = -1;
    m_lServerID = -1;
    m_lStartChan = -1;
    m_lChannel = -1;
    memset(&m_struAlarmMainStatus, 0, sizeof(m_struAlarmMainStatus));
    memset(&m_struAlarmOtherStatus, 0, sizeof(m_struAlarmOtherStatus));
    memset(&m_struAlarmInSetup, 0, sizeof(m_struAlarmInSetup));
    m_iPopMenuType = 0;
}


void CDlgAlarmHostStatus::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgAlarmHostStatus)
    DDX_Control(pDX, IDC_LIST_MEMORY_STATUS, m_listMemoryStatus);
    DDX_Control(pDX, IDC_LIST_FAULT_STATUS, m_listFaultStatus);
    DDX_Control(pDX, IDC_LIST_SUBSYSTEM, m_listSubSystem);
    DDX_Control(pDX, IDC_LIST_BYPASS_STATUS, m_listBypassStatus);
    DDX_Control(pDX, IDC_LIST_SETUP_ALARMIN_STATUS, m_listSetupAlarmInStatus);
    DDX_Control(pDX, IDC_LIST_ALARMOUT_STATUS, m_listAlarmOutStatus);
    DDX_Control(pDX, IDC_LIST_ALARMIN_STATUS, m_listAlarmInStaus);
    DDX_Check(pDX, IDC_CHK_SIREN_STATUS, m_bSirenStaus);
    DDX_Check(pDX, IDC_CHK_SIREN_STATUS2, m_bSirenStaus1);
    DDX_Check(pDX, IDC_CHK_SIREN_STATUS3, m_bSirenStaus2);
    DDX_Control(pDX, IDC_LIST_DETECTOR_STATUS, m_listDetectorStatus);
    //}}AFX_DATA_MAP
//     DDX_Control(pDX, IDC_LIST_DETECTOR_CONNECTION_STATUS, m_listDetectorConnectionStatus);
//     DDX_Control(pDX, IDC_LIST_DETECTOR_POWER_STATUS, m_listDetectorPowerStatus);
}


BEGIN_MESSAGE_MAP(CDlgAlarmHostStatus, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmHostStatus)
	ON_BN_CLICKED(IDC_BTN_REFRESH, OnBtnRefresh)
	ON_BN_CLICKED(IDC_BTN_BYPASS_ALARMCHAN, OnBtnBypassAlarmchan)
	ON_BN_CLICKED(IDC_BTN_CLOSE_ALARMCHAN, OnBtnCloseAlarmchan)
	ON_BN_CLICKED(IDC_BTN_SETUP_ALARMCHAN, OnBtnSetupAlarmchan)
	ON_BN_CLICKED(IDC_BTN_UN_BYPASS_ALARMCHAN, OnBtnUnBypassAlarmchan)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_SETUP_ALARMIN_STATUS, OnRclickListSetupAlarminStatus)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_BYPASS_STATUS, OnRclickListBypassStatus)
	ON_COMMAND(ID_MENU_SELECT_ALL, OnMenuSelectAll)
	ON_COMMAND(ID_MENU_CANCEL_ALL, OnMenuCancelAll)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostStatus message handlers

BOOL CDlgAlarmHostStatus::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    InitWnd();
    GetAlarmHostMainStatus(m_struAlarmMainStatus);
    SetAlarmHostMainStatusToWnd(m_struAlarmMainStatus);
    GetAlarmHostOtherStatus(m_struAlarmOtherStatus);
    SetAlarmHostOtherStatusToWnd(m_struAlarmOtherStatus);
	SetTimer(NULL, 500, NULL);
    UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgAlarmHostStatus::InitWnd()
{
    m_struAlarmHostAbility.wTotalAlarmInNum = m_struAlarmHostAbility.wTotalAlarmInNum == 0 ? 512 : m_struAlarmHostAbility.wTotalAlarmInNum;
    m_struAlarmHostAbility.wTotalAlarmOutNum = m_struAlarmHostAbility.wTotalAlarmOutNum == 0 ? 512 : m_struAlarmHostAbility.wTotalAlarmOutNum;
    m_struAlarmHostAbility.wSubSystemNum = m_struAlarmHostAbility.wSubSystemNum == 0 ? 32 : m_struAlarmHostAbility.wSubSystemNum;

    char szLan[128] = {0};
    m_listSetupAlarmInStatus.SetExtendedStyle(LVS_EX_CHECKBOXES); 
	int i = 0;
    //报警输入、输出采用总数
    for (i = 0; i < (m_struAlarmHostAbility.wTotalAlarmInNum); i++)
    {
        sprintf(szLan, "Alarm In %d", (i+1));
        m_listSetupAlarmInStatus.InsertItem(i, szLan);
    }
    
    m_listAlarmOutStatus.SetExtendedStyle(LVS_EX_CHECKBOXES);
    for (i = 0; i < (m_struAlarmHostAbility.wTotalAlarmOutNum); i++)
    {
        sprintf(szLan, "Alarm out %d", (i+1));
        m_listAlarmOutStatus.InsertItem(i, szLan);
    }

    m_listAlarmInStaus.SetExtendedStyle(LVS_EX_CHECKBOXES);
    for (i = 0; i < (m_struAlarmHostAbility.wTotalAlarmInNum); i++)
    {
        sprintf(szLan, "Alarm In %d", (i+1));
        m_listAlarmInStaus.InsertItem(i, szLan);
    }

    m_listBypassStatus.SetExtendedStyle(LVS_EX_CHECKBOXES);
    for (i = 0; i < (m_struAlarmHostAbility.wTotalAlarmInNum); i++)
    {
        sprintf(szLan, "Alarm In %d", (i+1));
        m_listBypassStatus.InsertItem(i, szLan);
    }

	m_listSubSystem.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT/* | LVS_EX_CHECKBOXES*/);
	g_StringLanType(szLan,"撤防","Disarm");
	m_listSubSystem.InsertColumn(0, "子系统号", LVCFMT_LEFT, 80, -1);
	m_listSubSystem.InsertColumn(1, "布防状态", LVCFMT_LEFT, 80, -1);
	//m_listSubSystem.SetExtendedStyle(LVS_EX_CHECKBOXES);
	for (i=0; i<m_struAlarmHostAbility.wSubSystemNum; i++)
	{
		sprintf(szLan, "Subsystem %d", (i+1));
		m_listSubSystem.InsertItem(i, szLan);
	}

	//故障状态
    m_listFaultStatus.SetExtendedStyle(LVS_EX_CHECKBOXES);
    for (i = 0; i < (m_struAlarmHostAbility.wTotalAlarmInNum); i++)
    {
        sprintf(szLan, "Alarm In %d", (i+1));
        m_listFaultStatus.InsertItem(i, szLan);
    }

	m_listMemoryStatus.SetExtendedStyle(LVS_EX_CHECKBOXES);
    for (i = 0; i < (m_struAlarmHostAbility.wTotalAlarmInNum); i++)
    {
        sprintf(szLan, "Alarm In %d", (i+1));
        m_listMemoryStatus.InsertItem(i, szLan);
    }

//     m_listDetectorConnectionStatus.SetExtendedStyle(LVS_EX_CHECKBOXES);
//     for (i = 0; i < (m_struAlarmHostAbility.wLocalAlarmInNum + m_struAlarmHostAbility.wExpandAlarmInNum); i++)
//     {
//         sprintf(szLan, "Alarm In %d", (i + 1));
//         m_listDetectorConnectionStatus.InsertItem(i, szLan);
//     }
//     m_listDetectorPowerStatus.SetExtendedStyle(LVS_EX_CHECKBOXES);
//     for (i = 0; i < (m_struAlarmHostAbility.wLocalAlarmInNum + m_struAlarmHostAbility.wExpandAlarmInNum); i++)
//     {
//         sprintf(szLan, "Alarm In %d", (i + 1));
//         m_listDetectorPowerStatus.InsertItem(i, szLan);
//     }

    m_listDetectorStatus.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT/* | LVS_EX_CHECKBOXES*/);
    m_listDetectorStatus.InsertColumn(0, "探测器号", LVCFMT_LEFT, 80, -1);
    m_listDetectorStatus.InsertColumn(1, "连接状态", LVCFMT_LEFT, 80, -1);
    m_listDetectorStatus.InsertColumn(2, "电量状态", LVCFMT_LEFT, 80, -1);
    for (i = 0; i < m_struAlarmHostAbility.wTotalAlarmInNum; i++)
    {
        sprintf(szLan, "Detector %d", (i + 1));
        m_listDetectorStatus.InsertItem(i, szLan);
    }
}

BOOL CDlgAlarmHostStatus::GetAlarmHostMainStatus(NET_DVR_ALARMHOST_MAIN_STATUS_V51& struAlarmMainStatus)
{
    BOOL bRet = FALSE;
    DWORD dwReturn = 0;
    
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_ALARMHOST_MAIN_STATUS_V51, 0, &struAlarmMainStatus, sizeof(struAlarmMainStatus), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMHOST_MAIN_STATUS_V51");
        bRet = FALSE;
    } 
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARMHOST_MAIN_STATUS_V51");
        bRet = TRUE;
    }
    return bRet;
}

BOOL CDlgAlarmHostStatus::GetAlarmHostOtherStatus(NET_DVR_ALARMHOST_OTHER_STATUS_V51& struAlarmOtherStatus)
{
    BOOL bRet = FALSE;
    DWORD dwReturn = 0;
    
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_ALARMHOST_OTHER_STATUS_V51, 0, &struAlarmOtherStatus, sizeof(struAlarmOtherStatus), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMHOST_OTHER_STATUS_V51");
        bRet = FALSE;
    } 
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARMHOST_OTHER_STATUS_V51");
        bRet = TRUE;
    }
    return bRet;
}

void CDlgAlarmHostStatus::SetAlarmHostMainStatusToWnd(NET_DVR_ALARMHOST_MAIN_STATUS_V51& struAlarmMainStatus)
{
	int i = 0;
	char szLan[128] = {0};

    for (i = 0; i < m_listAlarmInStaus.GetItemCount(); i++ )
    {
        if (1 ==  struAlarmMainStatus.byAlarmInStatus[i])
        {
            m_listAlarmInStaus.SetCheck(i, TRUE);
        }
        else
        {
            m_listAlarmInStaus.SetCheck(i, FALSE);
        }
    }

    for ( i = 0; i < m_listAlarmOutStatus.GetItemCount(); i++ )
    {
        if (1 == struAlarmMainStatus.byAlarmOutStatus[i])
        {
            m_listAlarmOutStatus.SetCheck(i, TRUE);
        }
        else
        {
            m_listAlarmOutStatus.SetCheck(i, FALSE);
        }
    }

    for ( i = 0; i < m_listSetupAlarmInStatus.GetItemCount(); i++ )
    {
        if (1 == struAlarmMainStatus.bySetupAlarmStatus[i])
        {
            m_listSetupAlarmInStatus.SetCheck(i, TRUE);
        }
        else
        {
            m_listSetupAlarmInStatus.SetCheck(i, FALSE);
        }
    }
   
    for ( i = 0; i < m_listBypassStatus.GetItemCount(); i++ )
    {
        if (1 == struAlarmMainStatus.byBypassStatus[i])
        {
            m_listBypassStatus.SetCheck(i, TRUE);
        }
        else
        {
            m_listBypassStatus.SetCheck(i, FALSE);
        }
    }

	for (i=0; i<m_listSubSystem.GetItemCount(); i++)
	{
		if(0 == struAlarmMainStatus.byEnableSubSystem[i] || 2 == struAlarmMainStatus.byEnableSubSystem[i])
		{
			if (1 == struAlarmMainStatus.bySubSystemGuardStatus[i])
			{
				switch (struAlarmMainStatus.bySubSystemGuardType[i])
				{
				case 0:
					g_StringLanType(szLan,"布防","Arm");
					break;
				case 1:
					g_StringLanType(szLan,"外出布防","Out Arm");
					break;
				case 2:
					g_StringLanType(szLan,"即时布防","Immedately Arm");
					break;
				case 3:
					g_StringLanType(szLan,"留守布防","Stay Arm");
					break;
				default:
					g_StringLanType(szLan,"未知状态","Unknown");
					break;
				}
			}
			else
			{
				g_StringLanType(szLan,"撤防","Disarm");
			}
		}
		else if (1 == struAlarmMainStatus.byEnableSubSystem[i])
		{
			g_StringLanType(szLan,"子系统无效","Subsystem Invalid");
		} 
		else
		{
			g_StringLanType(szLan,"未知状态","Unknown");
		}
		m_listSubSystem.SetItemText(i, 1, szLan);
	}

	//故障状态
	for (i=0; i<m_listFaultStatus.GetItemCount(); i++)
	{
		m_listFaultStatus.SetCheck(i, (BOOL)struAlarmMainStatus.byAlarmInFaultStatus[i]);
	}

	for (i=0; i<m_listMemoryStatus.GetItemCount(); i++)
	{
		if (1 == struAlarmMainStatus.byAlarmInMemoryStatus[i])
		{
			m_listMemoryStatus.SetCheck(i, TRUE);
		}
		else
		{
			m_listMemoryStatus.SetCheck(i, FALSE);
		}
	}
	UpdateData(FALSE);
}

void CDlgAlarmHostStatus::SetAlarmHostOtherStatusToWnd(NET_DVR_ALARMHOST_OTHER_STATUS_V51& struAlarmOtherStatus)
{
    m_bSirenStaus = struAlarmOtherStatus.bySirenStatus[0]; // 目前只有一个
    m_bSirenStaus1 = struAlarmOtherStatus.bySirenStatus[1];
    m_bSirenStaus2 = struAlarmOtherStatus.bySirenStatus[2];
    int i = 0;
    char szLan[128] = { 0 };
//     //探测器连接状态
//     for (i = 0; i < m_listDetectorConnectionStatus.GetItemCount(); i++)
//     {
//         m_listDetectorConnectionStatus.SetCheck(i, (BOOL)struAlarmOtherStatus.byDetetorConnection[i]);
//     }
// 
//     //探测器电量状态
//     for (i = 0; i < m_listDetectorPowerStatus.GetItemCount(); i++)
//     {
//         m_listDetectorPowerStatus.SetCheck(i, (BOOL)struAlarmOtherStatus.byDetetorPower[i]);
//     }

    for (i = 0; i < m_listDetectorStatus.GetItemCount(); i++)
    {
        if (0 == struAlarmOtherStatus.byDetetorConnection[i])
        {
            g_StringLanType(szLan, "未注册", "Unregedit");
        }
        else if (1 == struAlarmOtherStatus.byDetetorConnection[i])
        {
            g_StringLanType(szLan, "不在线", "Disconnect");
        }
        else if (1 == struAlarmOtherStatus.byDetetorConnection[i])
        {
            g_StringLanType(szLan, "在线", "Connect");
        }
        else
        {
            //目前只会返回0、1，如果后续支持具体信号强度值，将等于1的分支去掉
            sprintf(szLan, "Signal Intensity:[%d]", struAlarmOtherStatus.byDetetorConnection[i]);
        }
        m_listDetectorStatus.SetItemText(i, 1, szLan);

        sprintf(szLan, "Power:[%d]", struAlarmOtherStatus.byDetetorPower[i]);
        m_listDetectorStatus.SetItemText(i, 2, szLan);
    }

	UpdateData(FALSE);
}

void CDlgAlarmHostStatus::GetSetupAlarmChanFromWnd(NET_DVR_ALARMIN_SETUP &struAlarmInSetup)
{
	UpdateData(TRUE);
    for (int i = 0; i < m_listSetupAlarmInStatus.GetItemCount(); i++)
    {
        if (TRUE == m_listSetupAlarmInStatus.GetCheck(i))
        {
            struAlarmInSetup.byAssiciateAlarmIn[i] = 1;
        }
        else
        {
            struAlarmInSetup.byAssiciateAlarmIn[i] = 0;
        }
    }
}

void CDlgAlarmHostStatus::GetBypassAlarmChanFromWnd(NET_DVR_ALARMIN_SETUP &struAlarmInSetup)
{
	UpdateData(TRUE);
    for (int i = 0; i < m_listBypassStatus.GetItemCount(); i++)
    {
        if (TRUE == m_listBypassStatus.GetCheck(i))
        {
            struAlarmInSetup.byAssiciateAlarmIn[i] = 1;
        }
        else
        {
            struAlarmInSetup.byAssiciateAlarmIn[i] = 0;
        }
    }
}

void CDlgAlarmHostStatus::OnBtnRefresh() 
{
    GetAlarmHostMainStatus(m_struAlarmMainStatus);
    SetAlarmHostMainStatusToWnd(m_struAlarmMainStatus);
	GetAlarmHostOtherStatus(m_struAlarmOtherStatus);
    SetAlarmHostOtherStatusToWnd(m_struAlarmOtherStatus);
//	OnInitDialog();
    UpdateData(FALSE);
}

void CDlgAlarmHostStatus::OnBtnBypassAlarmchan() 
{
    GetBypassAlarmChanFromWnd(m_struAlarmInSetup);
    BypassAlarmChan(m_struAlarmInSetup);
}

void CDlgAlarmHostStatus::OnBtnCloseAlarmchan() 
{
    GetSetupAlarmChanFromWnd(m_struAlarmInSetup);
    AlarmHostCloseAlarmChan(m_struAlarmInSetup);
	
}

void CDlgAlarmHostStatus::OnBtnSetupAlarmchan() 
{
    GetSetupAlarmChanFromWnd(m_struAlarmInSetup);
    AlarmHostSetAlarmChan(m_struAlarmInSetup);
}

void CDlgAlarmHostStatus::OnBtnUnBypassAlarmchan() 
{
    GetBypassAlarmChanFromWnd(m_struAlarmInSetup);
    UnBypassAlarmChan(m_struAlarmInSetup);
}


BOOL CDlgAlarmHostStatus::AlarmHostSetAlarmChan(NET_DVR_ALARMIN_SETUP &struAlarmInSetup)
{
    BOOL bRet = FALSE;
    
    if (!NET_DVR_AlarmHostSetupAlarmChan(m_lServerID, &struAlarmInSetup))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_AlarmHostSetupAlarmChan");
        bRet =FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_AlarmHostSetupAlarmChan");
        bRet = TRUE;
    }
    return bRet;
}

BOOL CDlgAlarmHostStatus::AlarmHostCloseAlarmChan(NET_DVR_ALARMIN_SETUP &struAlarmInSetup)
{
    BOOL bRet = FALSE;
    if (!NET_DVR_AlarmHostCloseAlarmChan(m_lServerID, &struAlarmInSetup))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_AlarmHostCloseAlarmChan");
        bRet =FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_AlarmHostCloseAlarmChan");
        bRet = TRUE;
    }
    return bRet;
}

BOOL CDlgAlarmHostStatus::BypassAlarmChan(NET_DVR_ALARMIN_SETUP &struAlarmInSetup)
{
    if (NET_DVR_BypassAlarmChan(m_lServerID, &struAlarmInSetup))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_BypassAlarmChan");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_BypassAlarmChan");
        return FALSE;
    }

}

BOOL CDlgAlarmHostStatus::UnBypassAlarmChan(NET_DVR_ALARMIN_SETUP &struAlarmInSetup)
{
    if (NET_DVR_UnBypassAlarmChan(m_lServerID, &struAlarmInSetup))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_UnBypassAlarmChan");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_UnBypassAlarmChan");
        return FALSE;
    }
}

void CDlgAlarmHostStatus::OnRclickListSetupAlarminStatus(NMHDR* pNMHDR, LRESULT* pResult) 
{
    CMenu pMenu;
    
    if (!pMenu.LoadMenu(IDR_MENU_SELECT_MODE))
    {
        return;
    }
    CPoint point;
    GetCursorPos(&point);
    m_iPopMenuType = 1;
    pMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
    *pResult = 0;
}

void CDlgAlarmHostStatus::OnRclickListBypassStatus(NMHDR* pNMHDR, LRESULT* pResult) 
{
    CMenu pMenu;
    
    if (!pMenu.LoadMenu(IDR_MENU_SELECT_MODE))
    {
        return;
    }
    CPoint point;
    GetCursorPos(&point);
    m_iPopMenuType = 2;
    pMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
    *pResult = 0;
}

void CDlgAlarmHostStatus::OnMenuSelectAll() 
{
	if (1 == m_iPopMenuType)
	{
        for (int i = 0; i < m_listSetupAlarmInStatus.GetItemCount(); i++)
        {
            m_listSetupAlarmInStatus.SetCheck(i, TRUE);
        }
	}
    else if(2 == m_iPopMenuType)
    {
        for (int i = 0; i < m_listBypassStatus.GetItemCount(); i++)
        {
            m_listBypassStatus.SetCheck(i, TRUE);
        }
    }
}

void CDlgAlarmHostStatus::OnMenuCancelAll() 
{
    if (1 == m_iPopMenuType)
    {
        for (int i = 0; i < m_listSetupAlarmInStatus.GetItemCount(); i++)
        {
            m_listSetupAlarmInStatus.SetCheck(i, FALSE);
        }
    }
    else if(2 == m_iPopMenuType)
    {
        for (int i = 0; i < m_listBypassStatus.GetItemCount(); i++)
        {
            m_listBypassStatus.SetCheck(i, FALSE);
        }
    }
	
}

#if (_MSC_VER >= 1500)	//vs2008
void CDlgAlarmHostStatus::OnTimer(UINT_PTR nIDEvent) 
#else
void CDlgAlarmHostStatus::OnTimer(UINT nIDEvent) 
#endif
{
	// TODO: Add your message handler code here and/or call default
//	OnBtnRefresh();
	CDialog::OnTimer(nIDEvent);
}
