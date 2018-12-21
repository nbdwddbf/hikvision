// DlgAlarmKeyboardUser.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmKeyboardUser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmKeyboardUser dialog


CDlgAlarmKeyboardUser::CDlgAlarmKeyboardUser(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmKeyboardUser::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAlarmKeyboardUser)
	m_dwUserID = 0;
	//}}AFX_DATA_INIT
    m_lServerID  = 0;
    m_iDevIndex = 0;
    m_dwKeyboardUserNum = 0;
    m_dwAlarmInNum = 0;
    m_lUserIndex = -1;
    memset(&m_struKeyboardUser, 0, sizeof(m_struKeyboardUser));

}


void CDlgAlarmKeyboardUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmKeyboardUser)
	DDX_Control(pDX, IDC_LIST_ALARM_IN, m_listAlarmIn);
	DDX_Control(pDX, IDC_COMBO_USER_INDEX, m_comboUserIndex);
	DDX_Text(pDX, IDC_EDIT_USER_ID, m_dwUserID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmKeyboardUser, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmKeyboardUser)
	ON_CBN_SELCHANGE(IDC_COMBO_USER_INDEX, OnSelchangeComboUserIndex)
	ON_BN_CLICKED(IDC_BTN_SETUP, OnBtnSetup)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_ALARM_IN, OnRclickListAlarmIn)
	ON_COMMAND(ID_MENU_CANCEL_ALL, OnMenuCancelAll)
	ON_COMMAND(ID_MENU_SELECT_ALL, OnMenuSelectAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmKeyboardUser message handlers

BOOL CDlgAlarmKeyboardUser::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    InitWnd();
	m_comboUserIndex.SetCurSel(0);
    OnSelchangeComboUserIndex();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgAlarmKeyboardUser::InitWnd()
{
    InitUserIndexCombo();
    InitAlarmInList();
}

void CDlgAlarmKeyboardUser::InitUserIndexCombo()
{
    char szLan[128] = {0};
    m_comboUserIndex.ResetContent();
    for (int i = 0; i < m_dwKeyboardUserNum; i++)
    {
        sprintf(szLan, "User %d", i+1);
        m_comboUserIndex.AddString(szLan);
    }
}

void CDlgAlarmKeyboardUser::InitAlarmInList()
{
    char szLan[128] = {0};
    
    m_listAlarmIn.SetExtendedStyle(LVS_EX_CHECKBOXES);
    for (int i = 0; i < m_dwAlarmInNum; i++)
    {
        sprintf(szLan, "Alarm In %d", (i+1));
        m_listAlarmIn.InsertItem(i, szLan);
    }
}

BOOL CDlgAlarmKeyboardUser::GetKeyboardUser(NET_DVR_KEYBOARD_USER &struKeyboardUser)
{
    if (NET_DVR_GetKeyboardUser(m_lServerID, m_lUserIndex, &struKeyboardUser))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetKeyboardUser");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetKeyboardUser");
        return FALSE;
    }
    
}

BOOL CDlgAlarmKeyboardUser::SetKeyboardUser(NET_DVR_KEYBOARD_USER &struKeyboardUser)
{
    if (NET_DVR_SetKeyboardUser(m_lServerID, m_lUserIndex, &struKeyboardUser))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SetKeyboardUser");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SetKeyboardUser");
        return FALSE;
    }
}

void CDlgAlarmKeyboardUser::GetKeyboardUserFromWnd(NET_DVR_KEYBOARD_USER &struKeyboardUser)
{
    struKeyboardUser.dwID = m_dwUserID;
    
    for (int i = 0; i < m_listAlarmIn.GetItemCount(); i++)
    {
        if (TRUE == m_listAlarmIn.GetCheck(i))
        {
            struKeyboardUser.byDefanceArea[i] = 1;
        }
        else
        {
            struKeyboardUser.byDefanceArea[i] = 0;
        }
    }
}

void CDlgAlarmKeyboardUser::SetKeyboardUserToWnd(NET_DVR_KEYBOARD_USER &struKeyboardUser)
{
    m_dwUserID = struKeyboardUser.dwID;
    for (int i = 0; i < m_listAlarmIn.GetItemCount(); i++)
    {
        if (1 == struKeyboardUser.byDefanceArea[i])
        {
            m_listAlarmIn.SetCheck(i, TRUE);
        }
        else
        {
            m_listAlarmIn.SetCheck(i, FALSE);
        }
    }
}

void CDlgAlarmKeyboardUser::OnSelchangeComboUserIndex() 
{
    m_lUserIndex = m_comboUserIndex.GetCurSel() + 1;	
    if (!GetKeyboardUser(m_struKeyboardUser))
    {
        AfxMessageBox("Fail to get keyboard user");
    }
    
    SetKeyboardUserToWnd(m_struKeyboardUser);
    UpdateData(FALSE);
}

void CDlgAlarmKeyboardUser::OnBtnSetup() 
{
    UpdateData(TRUE);
    GetKeyboardUserFromWnd(m_struKeyboardUser);
    if (!SetKeyboardUser(m_struKeyboardUser))
    {
        AfxMessageBox("Fail to set keyboard user");
    }
}

void CDlgAlarmKeyboardUser::OnRclickListAlarmIn(NMHDR* pNMHDR, LRESULT* pResult) 
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

void CDlgAlarmKeyboardUser::OnMenuCancelAll() 
{
    for (int i = 0; i < m_listAlarmIn.GetItemCount(); i++)
    {
        m_listAlarmIn.SetCheck(i, FALSE);
    }
}

void CDlgAlarmKeyboardUser::OnMenuSelectAll() 
{
    for (int i = 0; i < m_listAlarmIn.GetItemCount(); i++)
    {
        m_listAlarmIn.SetCheck(i, TRUE);
    }
}
