// DlgAlarmOperatorUser.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmOperatorUser.h"
#include "DlgKeyboardCfg.h"
#include "DlgAlarmKeyboardUser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmOperatorUser dialog
typedef enum tagPOP_MENU_TYPE
{
    ALARM_ON = 1,
    ALARM_OFF,
    BYPASS
}POP_MENU_TYPE;


CDlgAlarmOperatorUser::CDlgAlarmOperatorUser(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmOperatorUser::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAlarmOperatorUser)
	m_csPassword = _T("");
	m_csUserName = _T("");
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    m_dwOperatorUserNum = 0;
    m_lUserIndex = -1;
    m_dwAlarmInNum = 0;
    m_iSubSystemNum = 0;
    m_dwKeyboardUserNum = 0;
    memset(&m_struOperatorUser, 0, sizeof(m_struOperatorUser));
    m_iPopMenuType = 0;
}


void CDlgAlarmOperatorUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmOperatorUser)
	DDX_Control(pDX, IDC_COMBO_SUBSYSTEM, m_cmSubsystem);
	DDX_Control(pDX, IDC_COMBO_USER_INDEX, m_comboUserIndex);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csPassword);
	DDV_MaxChars(pDX, m_csPassword, 16);
	DDX_Text(pDX, IDC_EDIT_USRE_NAME, m_csUserName);
	DDV_MaxChars(pDX, m_csUserName, 32);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmOperatorUser, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmOperatorUser)
	ON_CBN_SELCHANGE(IDC_COMBO_USER_INDEX, OnSelchangeComboUserIndex)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
    ON_BN_CLICKED(IDC_BTN_KEYBORAD_CFG, OnBtnKeyboradCfg)
    ON_BN_CLICKED(IDC_BTN_KEYBOARD_USER, OnBtnKeyboardUser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmOperatorUser message handlers

BOOL CDlgAlarmOperatorUser::OnInitDialog() 
{
	CDialog::OnInitDialog();
//	InitWnd();
	InitCombox();
	InitUserIndexCombo();
	m_comboUserIndex.SetCurSel(0);
	UpdateData(FALSE);
    OnSelchangeComboUserIndex();
	
    return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlarmOperatorUser::InitCombox()
{
	char szLan[128] = {0};
	m_cmSubsystem.ResetContent();
	g_StringLanType(szLan, "单布防，无布防报告，不能旁路", "It can arm, hos no arm report, can not bypass");
	m_cmSubsystem.AddString(szLan);
	g_StringLanType(szLan, "单撤防，无撤防报告，不能旁路", "It can disarm, has no disarm report, can not bypass");
	m_cmSubsystem.AddString(szLan);
	g_StringLanType(szLan, "布撤防，无布撤防报告，不能旁路", "It can arm and disarm, can not receive any report, can not bypass");
	m_cmSubsystem.AddString(szLan);
	g_StringLanType(szLan, "单布防，有布防报告，不能旁路", "It can arm, has arm report and can not bypass");
	m_cmSubsystem.AddString(szLan);
	g_StringLanType(szLan, "单撤防，有撤防报告，不能旁路", "It can disarm, has disarm report and can not bypass");
	m_cmSubsystem.AddString(szLan);
	g_StringLanType(szLan, "布撤防，有布撤防报告，不能旁路", "It can arm and disarm, receive any report and can not bypass");
	m_cmSubsystem.AddString(szLan);
	g_StringLanType(szLan, "单布防，无布撤防报告，允许旁路", "It can arm, can not receive any report and can bypass");
	m_cmSubsystem.AddString(szLan);
	g_StringLanType(szLan, "单撤防，无布撤防报告，允许旁路", "It can disarm, can not receive any report and can bypass");
	m_cmSubsystem.AddString(szLan);
	g_StringLanType(szLan, "布撤防，无布撤防报告，允许旁路", "It can arm and disarm, can not receive any report and can bypass");
	m_cmSubsystem.AddString(szLan);
	g_StringLanType(szLan, "单布防，有布防报告，允许旁路", "It can arm, has arm report and it can bypass");
	m_cmSubsystem.AddString(szLan);
	g_StringLanType(szLan, "单撤防，有撤防报告，允许旁路", "It can disarm, has disarm report, it can bypass");
	m_cmSubsystem.AddString(szLan);
	g_StringLanType(szLan, "布撤防，有布撤防报告，允许旁路", "It can arm and disarm, receive any report and bypass");
	m_cmSubsystem.AddString(szLan);
	UpdateData(FALSE);
} 



// void CDlgAlarmOperatorUser::InitWnd()
// {
//     InitUserIndexCombo();
//     InitAlarmOnList();
//     InitAlarmOffList();
//     InitBypassList();
//     InitSubSystemList();
// }
// 
// 
// void CDlgAlarmOperatorUser::InitAlarmOnList()
// {
//     char szLan[128] = {0};
//     
//     m_listAlarmOn.SetExtendedStyle(LVS_EX_CHECKBOXES);
//     for (int i = 0; i < m_dwAlarmInNum; i++)
//     {
//         sprintf(szLan, "Alarm In %d", (i+1));
//         m_listAlarmOn.InsertItem(i, szLan);
//     }
// }
// 
// void CDlgAlarmOperatorUser::InitSubSystemList()
// {
//     char szLan[128] = {0};
//     
//     m_listSubSystem.SetExtendedStyle(LVS_EX_CHECKBOXES);
//     for (int i = 0; i < m_iSubSystemNum; i++)
//     {
//         sprintf(szLan, "SubSystem %d", (i+1));
//         m_listSubSystem.InsertItem(i, szLan);
//     }
// }
// void CDlgAlarmOperatorUser::InitAlarmOffList()
// {
//     char szLan[128] = {0};
//     
//     m_listAlarmOff.SetExtendedStyle(LVS_EX_CHECKBOXES);
//     for (int i = 0; i < m_dwAlarmInNum; i++)
//     {
//         sprintf(szLan, "Alarm In %d", (i+1));
//         m_listAlarmOff.InsertItem(i, szLan);
//     }
// }
// 
// void CDlgAlarmOperatorUser::InitBypassList()
// {
//     char szLan[128] = {0};
//     
//     m_listBypass.SetExtendedStyle(LVS_EX_CHECKBOXES);
//     for (int i = 0; i < m_dwAlarmInNum; i++)
//     {
//         sprintf(szLan, "Alarm In %d", (i+1));
//         m_listBypass.InsertItem(i, szLan);
//     }
// }



// void CDlgAlarmOperatorUser::GetOperateUserFromWnd(NET_DVR_OPERATE_USER &struOperatorUser)
// {
//     strncpy((char*)struOperatorUser.sUserName, m_csUserName.GetBuffer(0), sizeof(struOperatorUser.sUserName));
//     strncpy((char*)struOperatorUser.sPassword, m_csPassword.GetBuffer(0),sizeof(struOperatorUser.sPassword));
//     GetAlarmOnFromWnd(struOperatorUser.byAlarmOnArea, ARRAY_SIZE(struOperatorUser.byAlarmOnArea));
//     GetAlarmOffFromWnd(struOperatorUser.byAlarmOffArea, ARRAY_SIZE(struOperatorUser.byAlarmOffArea));
//     GetBypassFromWnd(struOperatorUser.byBypassArea, ARRAY_SIZE(struOperatorUser.byBypassArea));
// }
// 
// void CDlgAlarmOperatorUser::SetOperateUserToWnd(NET_DVR_OPERATE_USER &struOperatorUser)
// {
//     char szLan[40] = {0};
//     strncpy(szLan, (char*)struOperatorUser.sUserName, sizeof(struOperatorUser.sUserName));
//     m_csUserName = szLan;
//     memset(szLan,0 ,sizeof(szLan));
//     strncpy(szLan, (char*)struOperatorUser.sPassword,sizeof(struOperatorUser.sPassword));
//     m_csPassword = szLan;
//     SetAlarmOnToWnd(struOperatorUser.byAlarmOnArea, ARRAY_SIZE(struOperatorUser.byAlarmOnArea));
//     SetAlarmOffToWnd(struOperatorUser.byAlarmOffArea, ARRAY_SIZE(struOperatorUser.byAlarmOffArea));
//     SetBypassToWnd(struOperatorUser.byBypassArea, ARRAY_SIZE(struOperatorUser.byBypassArea));
// 
// }

// void CDlgAlarmOperatorUser::GetAlarmOnFromWnd(BYTE *byAlarmIn, DWORD dwSize)
// {
//     for (int i = 0; i < m_listAlarmOn.GetItemCount(); i++)
//     {
//         if (m_listAlarmOn.GetCheck(i))
//         {
//             byAlarmIn[i] = 1;
//         }
//         else
//         {
//             byAlarmIn[i] = 0;
//         }
//     }
// }

// void CDlgAlarmOperatorUser::GetAlarmOffFromWnd(BYTE *byAlarmIn, DWORD dwSize)
// {
//     for (int i = 0; i < m_listAlarmOff.GetItemCount(); i++)
//     {
//         if (m_listAlarmOff.GetCheck(i))
//         {
//             byAlarmIn[i] = 1;
//         }
//         else
//         {
//             byAlarmIn[i] = 0;
//         }
//     }
// }

// void CDlgAlarmOperatorUser::GetBypassFromWnd(BYTE *byAlarmIn, DWORD dwSize)
// {
//     for (int i = 0; i < m_listBypass.GetItemCount(); i++)
//     {
//         if (m_listBypass.GetCheck(i))
//         {
//             byAlarmIn[i] = 1;
//         }
//         else
//         {
//             byAlarmIn[i] = 0;
//         }
//     }
// }

// void CDlgAlarmOperatorUser::SetAlarmOnToWnd(BYTE *byAlarmIn, DWORD dwSize)
// {
//     for (int i = 0; i < m_listAlarmOn.GetItemCount(); i++)
//     {
//         if (1 == byAlarmIn[i])
//         {
//             m_listAlarmOn.SetCheck(i, TRUE);
//         }
//         else
//         {
//             m_listAlarmOn.SetCheck(i, FALSE);
//         }
//     }
// }

// void CDlgAlarmOperatorUser::SetAlarmOffToWnd(BYTE *byAlarmIn, DWORD dwSize)
// {
//     for (int i = 0; i < m_listAlarmOff.GetItemCount(); i++)
//     {
//         if (1 == byAlarmIn[i])
//         {
//             m_listAlarmOff.SetCheck(i, TRUE);
//         }
//         else
//         {
//             m_listAlarmOff.SetCheck(i, FALSE);
//         }
//     }
// }

// void CDlgAlarmOperatorUser::SetBypassToWnd(BYTE *byAlarmIn, DWORD dwSize)
// {
//     for (int i = 0; i < m_listBypass.GetItemCount(); i++)
//     {
//         if (1 == byAlarmIn[i])
//         {
//             m_listBypass.SetCheck(i, TRUE);
//         }
//         else
//         {
//             m_listBypass.SetCheck(i, FALSE);
//         }
//     }
// }

// void CDlgAlarmOperatorUser::SetSubSystemToWnd(BYTE *bySubSystem, DWORD dwSize)
// {
//     for (int i = 0; i < m_listSubSystem.GetItemCount(); i++)
//     {
//         if (1 == bySubSystem[i])
//         {
//             m_listSubSystem.SetCheck(i, TRUE);
//         }
//         else
//         {
//             m_listSubSystem.SetCheck(i, FALSE);
//         }
//     }
// }


// 
// void CDlgAlarmOperatorUser::OnRclickListAlarmOn(NMHDR* pNMHDR, LRESULT* pResult) 
// {
// 	// TODO: Add your control notification handler code here
//     CMenu pMenu;
//     
//     if (!pMenu.LoadMenu(IDR_MENU_SELECT_MODE))
//     {
//         return;
//     }
//     CPoint point;
//     GetCursorPos(&point);
//     m_iPopMenuType = ALARM_ON;
//     pMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
//     *pResult = 0;
// }
// 
// void CDlgAlarmOperatorUser::OnRclickListAlarmOff(NMHDR* pNMHDR, LRESULT* pResult) 
// {
//     CMenu pMenu;
//     
//     if (!pMenu.LoadMenu(IDR_MENU_SELECT_MODE))
//     {
//         return;
//     }
//     CPoint point;
//     GetCursorPos(&point);
//     m_iPopMenuType = ALARM_OFF;
//     pMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
//     *pResult = 0;
// }
// 
// void CDlgAlarmOperatorUser::OnRclickListBypass(NMHDR* pNMHDR, LRESULT* pResult) 
// {
//     CMenu pMenu;
//     
//     if (!pMenu.LoadMenu(IDR_MENU_SELECT_MODE))
//     {
//         return;
//     }
//     CPoint point;
//     GetCursorPos(&point);
//     m_iPopMenuType = BYPASS;
//     pMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
//     *pResult = 0;
// }
// 
// void CDlgAlarmOperatorUser::OnMenuSelectAll() 
// {
//     if (ALARM_ON == m_iPopMenuType)
//     {
//         for (int i =0 ; i < m_listAlarmOn.GetItemCount(); i++)
//         {
//             m_listAlarmOn.SetCheck(i, TRUE);
//         }
//     }
//     else if (ALARM_OFF == m_iPopMenuType)
//     {
//         for (int i =0 ; i < m_listAlarmOff.GetItemCount(); i++)
//         {
//             m_listAlarmOff.SetCheck(i, TRUE);
//         }
//     }
//     else if (BYPASS == m_iPopMenuType)
//     {
//         for (int i =0 ; i < m_listBypass.GetItemCount(); i++)
//         {
//             m_listBypass.SetCheck(i, TRUE);
//         }
//     }
// }
// 
// void CDlgAlarmOperatorUser::OnMenuCancelAll() 
// {
//     if (ALARM_ON == m_iPopMenuType)
//     {
//         for (int i =0 ; i < m_listAlarmOn.GetItemCount(); i++)
//         {
//             m_listAlarmOn.SetCheck(i, FALSE);
//         }
//     }
//     else if (ALARM_OFF == m_iPopMenuType)
//     {
//         for (int i =0 ; i < m_listAlarmOff.GetItemCount(); i++)
//         {
//             m_listAlarmOff.SetCheck(i, FALSE);
//         }
//     }
//     else if (BYPASS == m_iPopMenuType)
//     {
//         for (int i =0 ; i < m_listBypass.GetItemCount(); i++)
//         {
//             m_listBypass.SetCheck(i, FALSE);
//         }
//     }
// }

void CDlgAlarmOperatorUser::InitUserIndexCombo()
{
    char szLan[128] = {0};
    m_comboUserIndex.ResetContent();
	g_StringLanType(szLan, "安装员", "Installer");
	m_comboUserIndex.AddString(szLan);
    for (int i = 0; i < m_dwOperatorUserNum; i++)
    {
        sprintf(szLan, "User %d", i+1);
        m_comboUserIndex.AddString(szLan);
    }
}

void CDlgAlarmOperatorUser::OnSelchangeComboUserIndex() 
{
	char strTemp[128] = {0};
	UpdateData(TRUE);
    m_lUserIndex = m_comboUserIndex.GetCurSel();
    GetOperateUser(m_struOperatorUser);
	memcpy(strTemp, m_struOperatorUser.sUserName, NAME_LEN);
	m_csUserName.Format("%s", strTemp);
	memset(strTemp, 0, sizeof(strTemp));
	memcpy(strTemp, m_struOperatorUser.sPassword, PASSWD_LEN);
	m_csPassword.Format("%s", strTemp);
	m_cmSubsystem.SetCurSel(m_struOperatorUser.bySubSystemPermission - 1);
    UpdateData(FALSE);	
}



BOOL CDlgAlarmOperatorUser::GetOperateUser(NET_DVR_OPERATE_USER &struOperatorUser)
{
	m_struOperatorUser.dwSize = sizeof(NET_DVR_OPERATE_USER);
    if (NET_DVR_GetOperateUser(m_lServerID, m_lUserIndex, &struOperatorUser))
    {
        g_pMainDlg->AddLog(m_lServerID, OPERATION_SUCC_T, "NET_DVR_GetOperateUser");
		char strTemp[128] = {0};
		memcpy(strTemp, m_struOperatorUser.sUserName, NAME_LEN);
		m_csUserName.Format("%s", strTemp);
		memset(strTemp, 0, sizeof(strTemp));
		memcpy(strTemp, m_struOperatorUser.sPassword, PASSWD_LEN);
		m_csPassword.Format("%s", strTemp);
		m_cmSubsystem.SetCurSel(m_struOperatorUser.bySubSystemPermission - 1);
		UpdateData(FALSE);	
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_lServerID, OPERATION_FAIL_T, "NET_DVR_GetOperateUser");
        return FALSE;
    }
}

BOOL CDlgAlarmOperatorUser::SetOperateUser(NET_DVR_OPERATE_USER &struOperatorUser)
{
	struOperatorUser.dwSize = sizeof(NET_DVR_OPERATE_USER);
    if (NET_DVR_SetOperateUser(m_lServerID, m_lUserIndex, &struOperatorUser))
    {
        g_pMainDlg->AddLog(m_lServerID, OPERATION_SUCC_T, "NET_DVR_SetOperateUser");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_lServerID, OPERATION_FAIL_T, "NET_DVR_SetOperateUser");
        return FALSE;
    }
}


void CDlgAlarmOperatorUser::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwUserIndex = m_comboUserIndex.GetCurSel();
	GetOperateUser(m_struOperatorUser);
}

void CDlgAlarmOperatorUser::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	/*    GetOperateUserFromWnd(m_struOperatorUser);*/
	memset(&m_struOperatorUser, 0, sizeof(m_struOperatorUser));
	DWORD dwUserIndex = m_comboUserIndex.GetCurSel();
	memcpy(m_struOperatorUser.sUserName, m_csUserName, NAME_LEN);
	memcpy(m_struOperatorUser.sPassword, m_csPassword, PASSWD_LEN);
	m_struOperatorUser.bySubSystemPermission = m_cmSubsystem.GetCurSel() + 1;
   	SetOperateUser(m_struOperatorUser);
}

void CDlgAlarmOperatorUser::OnBtnKeyboradCfg()
{
    // TODO: Add your control notification handler code here
    CDlgKeyboardCfg dlg;

    int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    if (iDeviceIndex < 0)
    {
        return;
    }

    int iChanIndex = g_pMainDlg->GetCurChanIndex();
    if (iChanIndex < 0)
    {
        iChanIndex = 0;//default to config channel one
    }
    dlg.m_iDeviceIndex = iDeviceIndex;
    dlg.m_lUserID = g_struDeviceInfo[iDeviceIndex].lLoginID;

    dlg.DoModal();
}

void CDlgAlarmOperatorUser::OnBtnKeyboardUser()
{
    CDlgAlarmKeyboardUser dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_dwKeyboardUserNum = m_dwKeyboardUserNum;
    dlg.m_dwAlarmInNum = m_dwAlarmInNum;
    dlg.DoModal();
}
