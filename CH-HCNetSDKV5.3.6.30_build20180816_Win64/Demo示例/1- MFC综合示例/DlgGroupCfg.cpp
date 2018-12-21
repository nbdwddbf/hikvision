// DlgGroupCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgGroupCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGroupCfg dialog


CDlgGroupCfg::CDlgGroupCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGroupCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGroupCfg)
	m_bEnable = FALSE;
	m_bValidEnable = FALSE;
	m_csGroupName = _T("");
	m_startDate = COleDateTime::GetCurrentTime();
	m_startTime = COleDateTime::GetCurrentTime();
	m_stopDate = COleDateTime::GetCurrentTime();
	m_stopTime = COleDateTime::GetCurrentTime();
	m_dwGroupNo = 1;
	//}}AFX_DATA_INIT

    m_lUserID = -1;
	m_lChannel = -1;
	m_iDevIndex = -1;

	memset(&m_struGroupCfg, 0, sizeof(m_struGroupCfg));
}


void CDlgGroupCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGroupCfg)
	DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
	DDX_Check(pDX, IDC_CHECK_VALID_ENABLE, m_bValidEnable);
	DDX_Text(pDX, IDC_EDIT_GROUP_NAME, m_csGroupName);
	DDX_DateTimeCtrl(pDX, IDC_START_DATE, m_startDate);
	DDX_DateTimeCtrl(pDX, IDC_START_TIME, m_startTime);
	DDX_DateTimeCtrl(pDX, IDC_STOP_DATE, m_stopDate);
	DDX_DateTimeCtrl(pDX, IDC_STOP_TIME, m_stopTime);
	DDX_Text(pDX, IDC_EDIT_GROUP_GROUPNO, m_dwGroupNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGroupCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgGroupCfg)
	ON_BN_CLICKED(IDC_BTN_GET_GROUP_CFG, OnBtnGetGroupCfg)
	ON_BN_CLICKED(IDC_BTN_SET_GROUP_CFG, OnBtnSetGroupCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGroupCfg message handlers

BOOL CDlgGroupCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	OnBtnGetGroupCfg() ;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgGroupCfg::OnBtnGetGroupCfg() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
	DWORD dwReturn = 0;
	
 	memset(&m_struGroupCfg, 0, sizeof(m_struGroupCfg));
    if (NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_GROUP_CFG, m_dwGroupNo, &m_struGroupCfg, sizeof(m_struGroupCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_GROUP_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_GROUP_CFG");
        return;
    }

	m_bEnable = m_struGroupCfg.byEnable;
	m_csGroupName.Format(_T("%s"), m_struGroupCfg.byGroupName);
	m_bValidEnable = m_struGroupCfg.struValidPeriodCfg.byEnable;
	m_startDate.SetDate(m_struGroupCfg.struValidPeriodCfg.struBeginTime.wYear, m_struGroupCfg.struValidPeriodCfg.struBeginTime.byMonth, m_struGroupCfg.struValidPeriodCfg.struBeginTime.byDay);
	m_startTime.SetTime(m_struGroupCfg.struValidPeriodCfg.struBeginTime.byHour, m_struGroupCfg.struValidPeriodCfg.struBeginTime.byMinute, m_struGroupCfg.struValidPeriodCfg.struBeginTime.bySecond);
	m_stopDate.SetDate(m_struGroupCfg.struValidPeriodCfg.struEndTime.wYear, m_struGroupCfg.struValidPeriodCfg.struEndTime.byMonth, m_struGroupCfg.struValidPeriodCfg.struEndTime.byDay);
	m_stopTime.SetTime(m_struGroupCfg.struValidPeriodCfg.struEndTime.byHour, m_struGroupCfg.struValidPeriodCfg.struEndTime.byMinute, m_struGroupCfg.struValidPeriodCfg.struEndTime.bySecond);
	UpdateData(FALSE);
}

void CDlgGroupCfg::OnBtnSetGroupCfg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	memset(&m_struGroupCfg, 0, sizeof(m_struGroupCfg));
	m_struGroupCfg.dwSize = sizeof(m_struGroupCfg);
	m_struGroupCfg.byEnable = m_bEnable;
	memcpy(m_struGroupCfg.byGroupName, m_csGroupName, m_csGroupName.GetLength());

	m_struGroupCfg.struValidPeriodCfg.byEnable = m_bValidEnable;
	m_struGroupCfg.struValidPeriodCfg.struBeginTime.wYear = m_startDate.GetYear();
	m_struGroupCfg.struValidPeriodCfg.struBeginTime.byMonth = m_startDate.GetMonth();
	m_struGroupCfg.struValidPeriodCfg.struBeginTime.byDay = m_startDate.GetDay();
	m_struGroupCfg.struValidPeriodCfg.struBeginTime.byHour = m_startTime.GetHour();
	m_struGroupCfg.struValidPeriodCfg.struBeginTime.byMinute = m_startTime.GetMinute();
	m_struGroupCfg.struValidPeriodCfg.struBeginTime.bySecond = m_startTime.GetSecond();
	
	m_struGroupCfg.struValidPeriodCfg.struEndTime.wYear = m_stopDate.GetYear();
	m_struGroupCfg.struValidPeriodCfg.struEndTime.byMonth = m_stopDate.GetMonth();
	m_struGroupCfg.struValidPeriodCfg.struEndTime.byDay = m_stopDate.GetDay();
	m_struGroupCfg.struValidPeriodCfg.struEndTime.byHour = m_stopTime.GetHour();
	m_struGroupCfg.struValidPeriodCfg.struEndTime.byMinute = m_stopTime.GetMinute();
	m_struGroupCfg.struValidPeriodCfg.struEndTime.bySecond = m_stopTime.GetSecond();

	if (NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_GROUP_CFG, m_dwGroupNo, &m_struGroupCfg, sizeof(m_struGroupCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_GROUP_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_GROUP_CFG");
        return;
    }

}
