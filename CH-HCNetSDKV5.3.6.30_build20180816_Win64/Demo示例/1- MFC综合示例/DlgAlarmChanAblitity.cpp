// DlgAlarmChanAblitity.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmChanAblitity.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmChanAblitity dialog


CDlgAlarmChanAblitity::CDlgAlarmChanAblitity(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmChanAblitity::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAlarmChanAblitity)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgAlarmChanAblitity::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmChanAblitity)
	DDX_Control(pDX, IDC_LIST_SENSOR_CHAN, m_listSensorChan);
	DDX_Control(pDX, IDC_LIST_RS485_CHAN, m_listRs485Chan);
	DDX_Control(pDX, IDC_LIST_ALARMOUT_CHAN, m_listAlarmOutChan);
	DDX_Control(pDX, IDC_LIST_ALARMIN_CHAN, m_listAlarmInChan);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmChanAblitity, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmChanAblitity)
	ON_BN_CLICKED(IDC_BTN_REFRESH, OnBtnRefresh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmChanAblitity message handlers

BOOL CDlgAlarmChanAblitity::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int i = 0;
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	CString csStr;
	m_listSensorChan.SetExtendedStyle(LVS_EX_CHECKBOXES);
	for ( i=0; i<64; i++)
	{
		csStr.Format("sensor %d", i+1);
		m_listSensorChan.InsertItem(i, csStr);
	}

	m_listRs485Chan.SetExtendedStyle(LVS_EX_CHECKBOXES);
	for (i=0; i<64; i++)
	{
		csStr.Format("RS485 %d", i+1);
		m_listRs485Chan.InsertItem(i, csStr);
	}

	m_listAlarmOutChan.SetExtendedStyle(LVS_EX_CHECKBOXES);
	for (i=0; i<64; i++)
	{
		csStr.Format("AlarmOut %d", i+1);
		m_listAlarmOutChan.InsertItem(i, csStr);
	}

	m_listAlarmInChan.SetExtendedStyle(LVS_EX_CHECKBOXES);
	for (i=0; i<64; i++)
	{
		csStr.Format("AlarmIn %d", i+1);
		m_listAlarmInChan.InsertItem(i, csStr);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlarmChanAblitity::OnBtnRefresh() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_ALARM_CHAN_ABLITITY struAlarmChanAblitity = {0};
	struAlarmChanAblitity.dwSize = sizeof(struAlarmChanAblitity);
	DWORD dwRet = 0;
	if (NET_DVR_GetDVRConfig(m_lUserID,NET_DVR_GET_ALARM_CHAN_ABLITITY,0,&struAlarmChanAblitity,sizeof(struAlarmChanAblitity),&dwRet))
	{
		g_pMainDlg->AddLog(m_lUserID, OPERATION_SUCC_T, "NET_DVR_GET_ALARM_CHAN_ABLITITY");
	}
	else
	{
		g_pMainDlg->AddLog(m_lUserID, OPERATION_FAIL_T, "NET_DVR_GET_ALARM_CHAN_ABLITITY");
		return;
	}
	int i = 0;
	for (i=0; i<64; i++)
	{
		m_listRs485Chan.SetCheck(i, (BOOL)(struAlarmChanAblitity.by485Chan[i]));
	}
	for (i=0; i<64; i++)
	{
		m_listSensorChan.SetCheck(i, (BOOL)(struAlarmChanAblitity.bySensorChan[i]));
	}
	for (i=0; i<64; i++)
	{
		m_listAlarmInChan.SetCheck(i, (BOOL)(struAlarmChanAblitity.byAlarmInChan[i]));
	}
	for (i=0; i<64; i++)
	{
		m_listAlarmOutChan.SetCheck(i, (BOOL)(struAlarmChanAblitity.byAlarmOutChan[i]));
	}
	UpdateData(FALSE);
}
