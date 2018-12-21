// DlgAlarmHostAudioAssociateAlarm.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmHostAudioAssociateAlarm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostAudioAssociateAlarm dialog


CDlgAlarmHostAudioAssociateAlarm::CDlgAlarmHostAudioAssociateAlarm(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmHostAudioAssociateAlarm::IDD, pParent)
	, m_iDeviceIndex(-1)
	, m_lUserID(-1)
	, m_iCurrentAudioIndex(1)
{
	//{{AFX_DATA_INIT(CDlgAlarmHostAudioAssociateAlarm)
	//}}AFX_DATA_INIT
}


void CDlgAlarmHostAudioAssociateAlarm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmHostAudioAssociateAlarm)
	DDX_Control(pDX, IDC_LIST_EXITDOOR, m_listExitDoor);
	DDX_Control(pDX, IDC_LIST_ENTERDOOR, m_listEnterDoor);
	DDX_Control(pDX, IDC_LIST_ALARMIN, m_listAlarmIn);
	DDX_Control(pDX, IDC_COMBO_AUDIO_NUM, m_cmAudioNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmHostAudioAssociateAlarm, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmHostAudioAssociateAlarm)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_SELECTALL, OnBtnSelectall)
	ON_BN_CLICKED(IDC_BTN_CANCELALL, OnBtnCancelall)
	ON_CBN_SELCHANGE(IDC_COMBO_AUDIO_NUM, OnSelchangeComboAudioNum)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostAudioAssociateAlarm message handlers

BOOL CDlgAlarmHostAudioAssociateAlarm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	memset(&m_struAudioAssoiateAlarm, 0, sizeof(m_struAudioAssoiateAlarm));
	
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;

	if(!NET_DVR_GetDeviceAbility(m_lUserID, ALARMHOST_ABILITY, NULL, 0, (char*)&m_struAbility, sizeof(m_struAbility)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetDeviceAbility FAILED");
		return FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetDeviceAbility SUCC");
	}
	
	char szLan[128] = {0};
	//初始化音频列表框
	int i = 0;
	for (i=0; i<m_struAbility.byAudioNum; i++)
	{
		g_StringLanType(szLan, "音频", "Audio");
		sprintf((char*)m_szLan, "%s %d",szLan, i+1);
		m_cmAudioNum.AddString(m_szLan);
	}

	//初始化门禁列表框	
	m_listEnterDoor.SetExtendedStyle(LVS_EX_CHECKBOXES);
    for (i = 0; i < m_struAbility.wGatewayNum; i++)
    {
		g_StringLanType(szLan, "进门", "Enter Door");
        sprintf((char*)m_szLan, "%s %d", szLan, i+1);
        m_listEnterDoor.InsertItem(i, (char*)m_szLan);
    }

	m_listExitDoor.SetExtendedStyle(LVS_EX_CHECKBOXES);
    for (i = 0; i < m_struAbility.wGatewayNum; i++)
    {
		g_StringLanType(szLan, "出门", "Exit Door");
        sprintf((char*)m_szLan, "%s %d", szLan, i+1);
        m_listExitDoor.InsertItem(i, (char*)m_szLan);
    }
	//初始化报警输入列表框
    m_listAlarmIn.SetExtendedStyle(LVS_EX_CHECKBOXES);
    for (i = 0; i < m_struAbility.wTotalAlarmInNum; i++)
    {
        sprintf((char*)m_szLan, "AlarmIn%d", i+1);
        m_listAlarmIn.InsertItem(i, (char*)m_szLan);
    }

	OnBtnGet();
	m_cmAudioNum.SetCurSel(0);
	m_iCurrentAudioIndex = 1;
	UpdateData(FALSE);
	SetCurrentDataToDlg();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlarmHostAudioAssociateAlarm::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturnLen = 0;
//	int iAudioIndex = m_cmAudioNum.GetCurSel();
	memset(&m_struAudioAssoiateAlarm, 0, sizeof(m_struAudioAssoiateAlarm));
	m_struAudioAssoiateAlarm.dwSize = sizeof(m_struAudioAssoiateAlarm);
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_ALARMHOST_AUDIO_ASSOCIATE_ALARM, 0, &m_struAudioAssoiateAlarm, sizeof(m_struAudioAssoiateAlarm), &dwReturnLen))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMHOST_AUDIO_ASSOCIATE_ALARM FAILED");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARMHOST_AUDIO_ASSOCIATE_ALARM SUCC");
	}
	SetCurrentDataToDlg();
}

void CDlgAlarmHostAudioAssociateAlarm::GetDataFromDlg() 
{
	//UpdateData(TRUE);
	//int iAudioIndex = m_cmAudioNum.GetCurSel() + 1;
	//memset(&m_struAudioAssoiateAlarm, 0, sizeof(m_struAudioAssoiateAlarm));
	//门禁
	int i = 0;
	for (i = 0; i < m_struAbility.wGatewayNum; i++ )
    {
		if (m_listEnterDoor.GetCheck(i))
		{
			m_struAudioAssoiateAlarm.byEnterDoor[i] = m_iCurrentAudioIndex;
		}
		else
		{
			if (m_struAudioAssoiateAlarm.byEnterDoor[i]==m_iCurrentAudioIndex)
			{
				m_struAudioAssoiateAlarm.byEnterDoor[i] = 0;
			}
		}
		if (m_listExitDoor.GetCheck(i))
		{
			m_struAudioAssoiateAlarm.byExitDoor[i] = m_iCurrentAudioIndex;
		}
		else
		{
			if (m_struAudioAssoiateAlarm.byExitDoor[i]==m_iCurrentAudioIndex)
			{
				m_struAudioAssoiateAlarm.byExitDoor[i] = 0;
			}
		}
	}
	//报警输入
	for (i = 0; i < m_listAlarmIn.GetItemCount(); i++ )
    {
		if (m_listAlarmIn.GetCheck(i))
		{
			m_struAudioAssoiateAlarm.byAlarmIn[i] = m_iCurrentAudioIndex;
		}
		else
		{
			if(m_struAudioAssoiateAlarm.byAlarmIn[i]==m_iCurrentAudioIndex)
			{
				m_struAudioAssoiateAlarm.byAlarmIn[i] = 0;
			}
		}
    }	
}

void CDlgAlarmHostAudioAssociateAlarm::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	GetDataFromDlg();
	m_struAudioAssoiateAlarm.dwSize = sizeof(m_struAudioAssoiateAlarm);

	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_ALARMHOST_AUDIO_ASSOCIATE_ALARM, 0, &m_struAudioAssoiateAlarm, sizeof(m_struAudioAssoiateAlarm)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_ALARMHOST_AUDIO_ASSOCIATE_ALARM FAILED");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_ALARMHOST_AUDIO_ASSOCIATE_ALARM SUCC");
	}
}

void CDlgAlarmHostAudioAssociateAlarm::OnBtnSelectall() 
{
	// TODO: Add your control notification handler code here
	for (int i = 0; i < m_listAlarmIn.GetItemCount(); i++ )
    {
        m_listAlarmIn.SetCheck(i, TRUE);
    }
	UpdateData(FALSE);
} 

void CDlgAlarmHostAudioAssociateAlarm::OnBtnCancelall() 
{
	// TODO: Add your control notification handler code here
	for (int i = 0; i < m_listAlarmIn.GetItemCount(); i++ )
    {
        m_listAlarmIn.SetCheck(i, FALSE);
    }
	UpdateData(FALSE);
}

void CDlgAlarmHostAudioAssociateAlarm::OnSelchangeComboAudioNum() 
{
	// TODO: Add your control notification handler code here
	GetDataFromDlg();
	SetCurrentDataToDlg();
}

void CDlgAlarmHostAudioAssociateAlarm::SetCurrentDataToDlg()
{
	UpdateData(TRUE);
	m_iCurrentAudioIndex = m_cmAudioNum.GetCurSel() + 1;
	
	m_listAlarmIn.DeleteAllItems();
	m_listEnterDoor.DeleteAllItems();
	m_listExitDoor.DeleteAllItems();
	char szLan[128] = {0};
	//初始化门禁列表框	
	m_listEnterDoor.SetExtendedStyle(LVS_EX_CHECKBOXES);
	int i = 0;
    for (i = 0; i < m_struAbility.wGatewayNum; i++)
    {
		g_StringLanType(szLan, "进门", "Enter Door");
        sprintf((char*)m_szLan, "%s %d<%d>", szLan, i+1, m_struAudioAssoiateAlarm.byEnterDoor[i]);
        m_listEnterDoor.InsertItem(i, (char*)m_szLan);
    }
	
	m_listExitDoor.SetExtendedStyle(LVS_EX_CHECKBOXES);
    for (i = 0; i < m_struAbility.wGatewayNum; i++)
    {
		g_StringLanType(szLan, "出门", "Exit Door");
        sprintf((char*)m_szLan, "%s %d<%d>",szLan, i+1, m_struAudioAssoiateAlarm.byExitDoor[i]);
        m_listExitDoor.InsertItem(i, (char*)m_szLan);
    }
	//初始化报警输入列表框
    m_listAlarmIn.SetExtendedStyle(LVS_EX_CHECKBOXES);
    for (i = 0; i < m_struAbility.wTotalAlarmInNum; i++)
    {
        sprintf((char*)m_szLan, "AlarmIn%d<%d>", i+1, m_struAudioAssoiateAlarm.byAlarmIn[i]);
        m_listAlarmIn.InsertItem(i, (char*)m_szLan);
    }
	
	
	//报警输入
	for (i = 0; i < m_listAlarmIn.GetItemCount(); i++ )
    {
        if (m_iCurrentAudioIndex ==  m_struAudioAssoiateAlarm.byAlarmIn[i])
        {
            m_listAlarmIn.SetCheck(i, TRUE);
        }
        else
        {
            m_listAlarmIn.SetCheck(i, FALSE);
        }
    }
	//门禁	
	for (i = 0; i < m_struAbility.wGatewayNum; i++ )
    {
		//进门
        if (m_iCurrentAudioIndex ==  m_struAudioAssoiateAlarm.byEnterDoor[i])
        {
            m_listEnterDoor.SetCheck(i, TRUE);
        }
        else
        {
            m_listEnterDoor.SetCheck(i, FALSE);
        }
		//出门
		if (m_iCurrentAudioIndex ==  m_struAudioAssoiateAlarm.byExitDoor[i])
        {
            m_listExitDoor.SetCheck(i, TRUE);
        }
        else
        {
            m_listExitDoor.SetCheck(i, FALSE);
        }
    }
	UpdateData(FALSE);
} 
