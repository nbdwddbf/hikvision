// DlgRemoteControlStatus.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRemoteControlStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteControlStatus dialog


CDlgRemoteControlStatus::CDlgRemoteControlStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteControlStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRemoteControlStatus)
	m_dwAlarmDealyTime = 0;
	m_dwDisAlarmDealyTime = 0;
    m_lServerID = -1;
    m_iDevIndex = -1;
    m_lChannel = -1;
	//}}AFX_DATA_INIT
}


void CDlgRemoteControlStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteControlStatus)
	DDX_Control(pDX, IDC_COMBO_ALARM_STATUS, m_comAlarmStatus);
	DDX_Text(pDX, IDC_EDIT_ALARM_DEALYTIME, m_dwAlarmDealyTime);
	DDX_Text(pDX, IDC_EDIT_DIS_ALARM_DEALYTIME, m_dwDisAlarmDealyTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRemoteControlStatus, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteControlStatus)
	ON_BN_CLICKED(IDC_BTN_GET_REMOTECONTROL_STATUS, OnBtnGetRemotecontrolStatus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteControlStatus message handlers

BOOL CDlgRemoteControlStatus::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_comAlarmStatus.SetCurSel(0);

    OnBtnGetRemotecontrolStatus();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRemoteControlStatus::OnBtnGetRemotecontrolStatus() 
{
	// TODO: Add your control notification handler code here
    char szLan[128] = {0};
    DWORD dwStatus = 0;

    NET_DVR_REMOTECONTROL_COND struRemoteControlCond = {0};
    struRemoteControlCond.dwSize = sizeof(struRemoteControlCond);
    struRemoteControlCond.dwChannel = m_lChannel;

    NET_DVR_REMOTECONTROL_STATUS struRemoteControlStatus = {0};
    //struRemoteControlStatus.dwSize = sizeof(struRemoteControlStatus);


    if (!NET_DVR_GetDeviceStatus(m_lServerID, NET_DVR_GET_REMOTECONTROL_STATUS, 1, &struRemoteControlCond, sizeof(struRemoteControlCond), \
        &dwStatus, &struRemoteControlStatus, sizeof(struRemoteControlStatus)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_REMOTECONTROL_STATUS Fail ");

        return;
	}
    g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_REMOTECONTROL_STATUS Succ ");
    m_comAlarmStatus.SetCurSel(struRemoteControlStatus.byAlarmStatus - 1);
    m_dwAlarmDealyTime = struRemoteControlStatus.wAlarmDealyTime;
    m_dwDisAlarmDealyTime = struRemoteControlStatus.wDisAlarmDealyTime;

    UpdateData(FALSE);
}
