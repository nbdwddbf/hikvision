// DlgPtzParkActionCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPtzParkActionCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPtzParkActionCfg dialog


CDlgPtzParkActionCfg::CDlgPtzParkActionCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPtzParkActionCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPtzParkActionCfg)
	m_dwID = 0;
	m_dwParkActionTime = 0;
	m_bChkTrace = FALSE;
	m_bChkEnable = FALSE;
	m_bChkOneKey = FALSE;
	//}}AFX_DATA_INIT
	m_iDevIndex = -1;
	m_lLoginID = -1;
	m_lChanNum = 0;
	memset(&m_strMotionTtackCfg, 0, sizeof(m_strMotionTtackCfg));
	memset(&m_struPtzParkAciton, 0, sizeof(m_struPtzParkAciton));
}


void CDlgPtzParkActionCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPtzParkActionCfg)
	DDX_Control(pDX, IDC_COMBO_LINEARSCAN_TYPE, m_comLinearScanType);
	DDX_Control(pDX, IDC_COMBO_ACTION_TYPE, m_comboActionType);
	DDX_Text(pDX, IDC_EDIT_ID, m_dwID);
	DDX_Text(pDX, IDC_EDIT_PARKACTION_TIME, m_dwParkActionTime);
	DDX_Check(pDX, IDC_CHK_TRACE, m_bChkTrace);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bChkEnable);
	DDX_Check(pDX, IDC_CHECK_ONEKET, m_bChkOneKey);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPtzParkActionCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgPtzParkActionCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_SET_LINEARSCAN, OnBtnSetLinearscan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPtzParkActionCfg message handlers
BOOL CDlgPtzParkActionCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
	OnBtnGet();
	return TRUE;
}

void CDlgPtzParkActionCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn;
    if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_PTZ_PARKACTION_CFG, m_lChanNum, &m_struPtzParkAciton, sizeof(m_struPtzParkAciton), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PTZ_PARKACTION_CFG");
        AfxMessageBox("NET_DVR_GET_PTZ_PARKACTION_CFG fail");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PTZ_PARKACTION_CFG");
		m_bChkEnable = m_struPtzParkAciton.byEnable;
		m_dwParkActionTime = m_struPtzParkAciton.dwParkTime;
		m_comboActionType.SetCurSel(m_struPtzParkAciton.wActionType);
		m_dwID = m_struPtzParkAciton.wID;
		m_bChkOneKey = m_struPtzParkAciton.byOneTouchSwitch;
    }

	if (!NET_DVR_GetDVRConfig(m_lLoginID,  NET_DVR_GET_MOTION_TRACK_CFG, m_lChanNum, &m_strMotionTtackCfg, sizeof(m_strMotionTtackCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_MOTION_TRACK_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_MOTION_TRACK_CFG");
    }
	m_bChkTrace = m_strMotionTtackCfg.byEnableTrack;
	UpdateData(FALSE);
}

void CDlgPtzParkActionCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struPtzParkAciton.dwSize = sizeof(m_struPtzParkAciton);
	m_struPtzParkAciton.byEnable = m_bChkEnable;
	m_struPtzParkAciton.dwParkTime = m_dwParkActionTime;
	m_struPtzParkAciton.wActionType = m_comboActionType.GetCurSel();
	m_struPtzParkAciton.wID = m_dwID;
	m_struPtzParkAciton.byOneTouchSwitch = m_bChkOneKey;
    if (!NET_DVR_SetDVRConfig(m_lLoginID,NET_DVR_SET_PTZ_PARKACTION_CFG, m_lChanNum, &m_struPtzParkAciton, sizeof(m_struPtzParkAciton)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_PTZ_PARKACTION_CFG");
        AfxMessageBox("NET_DVR_SET_PTZ_PARKACTION_CFG fail");
		return;
    }
    else 
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_PTZ_PARKACTION_CFG");
    }

	m_strMotionTtackCfg.dwSize = sizeof(m_strMotionTtackCfg);
	m_strMotionTtackCfg.byEnableTrack = m_bChkTrace;
	
	if (NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_MOTION_TRACK_CFG, 1, &m_strMotionTtackCfg, sizeof(m_strMotionTtackCfg)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_MOTION_TRACK_CFG");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_MOTION_TRACK_CFG");
		return;
	}
}

void CDlgPtzParkActionCfg::OnBtnSetLinearscan() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_LINEARSCAN struLinearScan = {0};
	struLinearScan.dwSize = sizeof(NET_DVR_LINEARSCAN);
	struLinearScan.dwChan = m_lChanNum;
	struLinearScan.byLinearScanType = m_comLinearScanType.GetCurSel() + 1;

	if (NET_DVR_RemoteControl(m_lLoginID, NET_DVR_REMOTECONTROL_LINEARSCAN, &struLinearScan, sizeof(struLinearScan)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_REMOTECONTROL_LINEARSCAN");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_REMOTECONTROL_LINEARSCAN");
		return;
	}
}
