// DlgSafeCabinState.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgSafeCabinState.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSafeCabinState dialog


CDlgSafeCabinState::CDlgSafeCabinState(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSafeCabinState::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSafeCabinState)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSafeCabinState::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSafeCabinState)
	DDX_Control(pDX, IDC_CMB_URGENCY_BTN_STATE, m_cmbUrgencyBtnState);
	DDX_Control(pDX, IDC_CMB_PERSON_STATE, m_cmbPersonState);
	DDX_Control(pDX, IDC_CMB_LOCK_STATE, m_cmbLockState);
	DDX_Control(pDX, IDC_CMB_LIGHT_STATE, m_cmbLightState);
	DDX_Control(pDX, IDC_CMB_FAN_STATE, m_cmbFanState);
	DDX_Control(pDX, IDC_CMB_EXIT_BTN_STATE, m_cmbExitBtnState);
	DDX_Control(pDX, IDC_CMB_ENTER_BTN_STATE, m_cmbEnterBtnState);
	DDX_Control(pDX, IDC_CMB_DOOR_STATE, m_cmbDoorState);
	DDX_Control(pDX, IDC_CMB_ABNORMAL_STATE, m_cmbAbnormalState);
	DDX_Control(pDX, IDC_CMB_FOLLOW_STATE, m_cmbFollowState);
	DDX_Control(pDX, IDC_CMB_FAINT_STATE, m_cmbFaintState);
	DDX_Control(pDX, IDC_CMB_MANY_PERSON_STATE, m_cmbManyPersonState);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSafeCabinState, CDialog)
	//{{AFX_MSG_MAP(CDlgSafeCabinState)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSafeCabinState message handlers

void CDlgSafeCabinState::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	DWORD dwReturned = 0;
	NET_DVR_ALARMHOST_SAFETYCABINSTATE struSafeCabinState = {0};
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_SAFETYCABIN_STATE, 0, &struSafeCabinState, sizeof(struSafeCabinState), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SAFETYCABIN_STATE");
		g_StringLanType(szLan, "»ñÈ¡Ê§°Ü", "Get failed");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SAFETYCABIN_STATE");
	}
	
	m_cmbAbnormalState.SetCurSel(struSafeCabinState.byAbnormal);
	m_cmbUrgencyBtnState.SetCurSel(struSafeCabinState.byUrgencyButton);
	m_cmbPersonState.SetCurSel(struSafeCabinState.byManState);
	m_cmbLockState.SetCurSel(struSafeCabinState.byLockState);
	m_cmbLightState.SetCurSel(struSafeCabinState.byLightState);
	m_cmbFanState.SetCurSel(struSafeCabinState.byFanState);
	m_cmbExitBtnState.SetCurSel(struSafeCabinState.byExitButton);
	m_cmbEnterBtnState.SetCurSel(struSafeCabinState.byEnterButton);
	m_cmbDoorState.SetCurSel(struSafeCabinState.byDoorState);
	m_cmbFollowState.SetCurSel(struSafeCabinState.byFollow);
	m_cmbFaintState.SetCurSel(struSafeCabinState.byFaint);
	m_cmbManyPersonState.SetCurSel(struSafeCabinState.byManyPerson);

	
	UpdateData(FALSE);
}

BOOL CDlgSafeCabinState::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	OnBtnGet();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
