// DlgGetAllSensorJointCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgGetAllSensorJointCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgGetAllSensorJointCfg dialog


DlgGetAllSensorJointCfg::DlgGetAllSensorJointCfg(CWnd* pParent /*=NULL*/)
	: CDialog(DlgGetAllSensorJointCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgGetAllSensorJointCfg)
	//}}AFX_DATA_INIT
	memset(&m_struAlarmHostSensorJoint,0,sizeof(m_struAlarmHostSensorJoint));
}


void DlgGetAllSensorJointCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgGetAllSensorJointCfg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgGetAllSensorJointCfg, CDialog)
	//{{AFX_MSG_MAP(DlgGetAllSensorJointCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgGetAllSensorJointCfg message handlers
// DlgGetAllPointCfg message handlers
BOOL DlgGetAllSensorJointCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	m_listSensorJoint.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listSensorJoint.InsertColumn(0, "点号", LVCFMT_LEFT, 80, -1);
	m_listSensorJoint.InsertColumn(1,"点号描述", LVCFMT_LEFT, 150, -1);
	m_listSensorJoint.InsertColumn(2,"通道号", LVCFMT_LEFT, 80, -1);
	m_listSensorJoint.InsertColumn(3,"槽位号", LVCFMT_LEFT, 80, -1);
	m_listSensorJoint.InsertColumn(4,"变量编号", LVCFMT_LEFT, 80, -1);
	m_listSensorJoint.InsertColumn(5,"点号类型", LVCFMT_LEFT, 80, -1);
	m_listSensorJoint.InsertColumn(6,"接入类型", LVCFMT_LEFT, 100, -1);
	
	return TRUE;
}

void DlgGetAllSensorJointCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	m_listSensorJoint.DeleteAllItems();
	m_iRowCount = 0;
	if (m_lHandle>=0)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "It is getting data, wait for a moment");
	}
	else
	{
		m_lHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_GET_ALL_ALARM_POINT_CFG, NULL, 0, NULL, this);
		if (m_lHandle>=0)
		{
			m_bGetNext = TRUE;
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Start Remote Config successfully");
		//	DWORD dwThreadId;
		//	m_hGetInfoThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetConfigThread), this, 0, &dwThreadId);
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Start Remote Config failed");
			return;
		}
	}
}
