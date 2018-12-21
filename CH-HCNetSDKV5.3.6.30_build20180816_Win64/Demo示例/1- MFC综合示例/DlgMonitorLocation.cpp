// DlgMonitorLocation.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMonitorLocation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMonitorLocation dialog


CDlgMonitorLocation::CDlgMonitorLocation(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMonitorLocation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMonitorLocation)
	m_csDevID = _T("");
	m_csMonitorInfo = _T("");
	m_csMonitoringSiteID = _T("");
	//}}AFX_DATA_INIT
    m_lUserID = -1;
    m_dwDevIndex = -1;
    m_lChannel = -1;
}


void CDlgMonitorLocation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMonitorLocation)
	DDX_Control(pDX, IDC_COMBO_RELATE_TYPE, m_comRelateType);
	DDX_Control(pDX, IDC_COMBO_DIRECTION, m_comDirection);
	DDX_Text(pDX, IDC_EDIT_DEV_ID, m_csDevID);
	DDX_Text(pDX, IDC_EDIT_MONIT_INFO, m_csMonitorInfo);
	DDX_Text(pDX, IDC_EDIT_MONIT_SITE_ID, m_csMonitoringSiteID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMonitorLocation, CDialog)
	//{{AFX_MSG_MAP(CDlgMonitorLocation)
	ON_BN_CLICKED(IDC_BTN_GET_MONITOR_LOCATION, OnBtnGetMonitorLocation)
	ON_BN_CLICKED(IDC_BTN_SET_MONITOR_LOCATION, OnBtnSetMonitorLocation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMonitorLocation message handlers

BOOL CDlgMonitorLocation::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_comRelateType.SetCurSel(0);
    m_comDirection.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMonitorLocation::OnBtnGetMonitorLocation() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

    NET_DVR_MONITOR_LOCATION_COND struMonitorCond = {0};
    struMonitorCond.dwSize = sizeof(struMonitorCond);
    struMonitorCond.dwChan = m_lChannel;
    struMonitorCond.byRelateType = m_comRelateType.GetCurSel();

    NET_DVR_MONITOR_LOCATION_CFG  struMonitorCfg = {0};
    struMonitorCfg.dwSize = sizeof(NET_DVR_MONITOR_LOCATION_CFG);

    BOOL bRet      = FALSE;
    DWORD dwStatus = 0;
    
    if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_MONITOR_LOCATION_INFO, 1, &struMonitorCond, sizeof(struMonitorCond),
        &dwStatus,&struMonitorCfg, sizeof(struMonitorCfg)))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_MONITOR_LOCATION_INFO Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_MONITOR_LOCATION_INFO Chan[%d]", m_lChannel);
        bRet = TRUE;
    }

    if (bRet)
    {
        m_csMonitoringSiteID.Format(_T("%s"), struMonitorCfg.byMonitoringSiteID);
        m_csDevID.Format(_T("%s"), struMonitorCfg.byDeviceID);
        m_comDirection.SetCurSel(struMonitorCfg.byDirectionNo - 1);
        m_csMonitorInfo.Format(_T("%s"), struMonitorCfg.byMonitorInfo);
    }
    UpdateData(FALSE);
}

void CDlgMonitorLocation::OnBtnSetMonitorLocation() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    
    NET_DVR_MONITOR_LOCATION_COND struMonitorCond = {0};
    struMonitorCond.dwSize = sizeof(struMonitorCond);
    struMonitorCond.dwChan = m_lChannel;
    struMonitorCond.byRelateType = m_comRelateType.GetCurSel();

    NET_DVR_MONITOR_LOCATION_CFG  struMonitorCfg = {0};
    struMonitorCfg.dwSize = sizeof(NET_DVR_MONITOR_LOCATION_CFG);

    strncpy((char*)struMonitorCfg.byMonitoringSiteID, m_csMonitoringSiteID.GetBuffer(0), sizeof(struMonitorCfg.byMonitoringSiteID));
    strncpy((char*)struMonitorCfg.byDeviceID, m_csDevID.GetBuffer(0), sizeof(struMonitorCfg.byDeviceID));
    struMonitorCfg.byDirectionNo = m_comDirection.GetCurSel() + 1;
    strncpy((char*)struMonitorCfg.byMonitorInfo, m_csMonitorInfo.GetBuffer(0), sizeof(struMonitorCfg.byMonitorInfo));
    DWORD dwStatus = 0;

    if (!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_SET_MONITOR_LOCATION_INFO, 1, &struMonitorCond, sizeof(struMonitorCond),
        &dwStatus,&struMonitorCfg, sizeof(struMonitorCfg)))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_MONITOR_LOCATION_INFO Chan[%d]", m_lChannel);
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_MONITOR_LOCATION_INFO Chan[%d]", m_lChannel);
    }
	
}
