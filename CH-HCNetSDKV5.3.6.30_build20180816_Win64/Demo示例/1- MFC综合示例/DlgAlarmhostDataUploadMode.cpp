// DlgAlarmhostDataUploadMode.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmhostDataUploadMode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmhostDataUploadMode dialog


CDlgAlarmhostDataUploadMode::CDlgAlarmhostDataUploadMode(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmhostDataUploadMode::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAlarmhostDataUploadMode)
	//}}AFX_DATA_INIT
}


void CDlgAlarmhostDataUploadMode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmhostDataUploadMode)
	DDX_Control(pDX, IDC_COMBO_VALUE_UPLOAD_MODE, m_cmValueUploadMode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmhostDataUploadMode, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmhostDataUploadMode)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmhostDataUploadMode message handlers

BOOL CDlgAlarmhostDataUploadMode::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;


	m_cmValueUploadMode.ResetContent();
	g_StringLanType(m_szLan, "按通道上传", "Upload by channel");
	m_cmValueUploadMode.AddString(m_szLan);
	g_StringLanType(m_szLan, "按监控点上传", "Upload by Point");
	m_cmValueUploadMode.AddString(m_szLan);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgAlarmhostDataUploadMode::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
	m_struAlarmMode.dwSize = sizeof(m_struAlarmMode);
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_ALARMHOST_ALARM_MODE, 0, &m_struAlarmMode, sizeof(m_struAlarmMode), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMHOST_ALARM_MODE FAILED");
		return ;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARMHOST_ALARM_MODE SUCC");
		m_cmValueUploadMode.SetCurSel(m_struAlarmMode.byDataUploadMode - 1);
	}
	UpdateData(FALSE);
}



void CDlgAlarmhostDataUploadMode::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struAlarmMode.dwSize = sizeof(m_struAlarmMode);
	m_struAlarmMode.byDataUploadMode = m_cmValueUploadMode.GetCurSel() + 1;
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_ALARMHOST_ALARM_MODE, 0, &m_struAlarmMode, sizeof(m_struAlarmMode)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_ALARMHOST_ALARM_MODE FAILED");
		return ;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_ALARMHOST_ALARM_MODE SUCC");
	}
	UpdateData(FALSE);
}
