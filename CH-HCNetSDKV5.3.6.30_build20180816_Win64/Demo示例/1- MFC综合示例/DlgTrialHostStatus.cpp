// DlgTrialHostStatus.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgTrialHostStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTrialHostStatus dialog


CDlgTrialHostStatus::CDlgTrialHostStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTrialHostStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTrialHostStatus)
	m_bChkFpgaTempWarn = FALSE;
	m_bChkMainTempWarn = FALSE;
	m_nFPGATemp = 0;
	m_nMainBoardTemp = 0;
	m_nFanSpeed = 0;
	//}}AFX_DATA_INIT
	memset(&m_struTrialHostStatus,0,sizeof(m_struTrialHostStatus));
}


void CDlgTrialHostStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTrialHostStatus)
	DDX_Check(pDX, IDC_CHK_FPGA_TEMP_WARN, m_bChkFpgaTempWarn);
	DDX_Check(pDX, IDC_CHK_MAIN_TEMP_WARN, m_bChkMainTempWarn);
	DDX_Text(pDX, IDC_FPGA_TEMP, m_nFPGATemp);
	DDX_Text(pDX, IDC_MAIN_BOARD_TEMP, m_nMainBoardTemp);
	DDX_Text(pDX, IDC_FAN_SPEED, m_nFanSpeed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTrialHostStatus, CDialog)
	//{{AFX_MSG_MAP(CDlgTrialHostStatus)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTrialHostStatus message handlers

void CDlgTrialHostStatus::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	DWORD dwRet = 0;
	if (!NET_DVR_GetDVRConfig(m_lUserID,NET_DVR_GET_TRIAL_HOST_STATUS,0,&m_struTrialHostStatus,sizeof(NET_DVR_TRIAL_HOST_STATUS),&dwRet))
	{
		char szLan[128] = {0};
		g_pMainDlg->AddLog(m_lUserID, OPERATION_FAIL_T, "NET_DVR_GET_TRIAL_HOST_STATUS");
		g_StringLanType(szLan, "获取庭审主机状态失败", "Fail to get case host status");
		AfxMessageBox(szLan);
		return;
	}
    else
    {
        g_pMainDlg->AddLog(m_lUserID, OPERATION_SUCC_T, "NET_DVR_GET_TRIAL_HOST_STATUS");
    }
	m_bChkMainTempWarn = m_struTrialHostStatus.byFpgaTempWarn[0];
	m_bChkFpgaTempWarn = m_struTrialHostStatus.byFpgaTempWarn[1];

	m_nMainBoardTemp = m_struTrialHostStatus.wMainBoardTemp[0];
	m_nFPGATemp = m_struTrialHostStatus.wMainBoardTemp[1];
	m_nFanSpeed = m_struTrialHostStatus.dwFanSpeed[0];
	UpdateData(FALSE);
}

BOOL CDlgTrialHostStatus::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	OnBtnGet();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
