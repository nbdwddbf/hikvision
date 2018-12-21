// DlgRemoteControllerCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRemoteControllerCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteControllerCfg dialog


CDlgRemoteControllerCfg::CDlgRemoteControllerCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteControllerCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRemoteControllerCfg)
	m_bArmReportRight = FALSE;
	m_bArmRight = FALSE;
	m_bClearArmRight = FALSE;
	m_bDisArmRight = FALSE;
	m_bDisArmReportRight = FALSE;
	m_bEnable = FALSE;
    m_bEnableDel = FALSE;
	m_strSerialNo = _T("");
	m_iKeyBoradAddr = 0;
	//}}AFX_DATA_INIT
}


void CDlgRemoteControllerCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteControllerCfg)
	DDX_Control(pDX, IDC_CMB_SUBSYS_NO, m_cmb_SubSysNo);
	DDX_Control(pDX, IDC_CMB_REMOTE_CONTROLLER_NO, m_cmb_RemoteControllerNo);
	DDX_Check(pDX, IDC_CHK_ARM_REPORT, m_bArmReportRight);
	DDX_Check(pDX, IDC_CHK_ARM1, m_bArmRight);
	DDX_Check(pDX, IDC_CHK_CLEAR_ALARM, m_bClearArmRight);
	DDX_Check(pDX, IDC_CHK_DISARM, m_bDisArmRight);
	DDX_Check(pDX, IDC_CHK_DISARM_REPORT, m_bDisArmReportRight);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
    DDX_Check(pDX, IDC_CHK_DISENABLE, m_bEnableDel);
	DDX_Text(pDX, IDC_EDIT_SERIAL_NO, m_strSerialNo);
	DDX_Text(pDX, IDC_EDIT_KEYBORAD_ADDR, m_iKeyBoradAddr);
    DDX_Control(pDX, IDC_CMB_ALWAYS_OPEN_RIGHT, m_cmbAlwaysOpenRight);
    DDX_Control(pDX, IDC_CMB_OPENING_DIRECTION, m_cmbOpeningDirection);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRemoteControllerCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteControllerCfg)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteControllerCfg message handlers

BOOL CDlgRemoteControllerCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	m_cmb_RemoteControllerNo.SetCurSel(0);
    m_cmbAlwaysOpenRight.SetCurSel(0);
    m_cmbOpeningDirection.SetCurSel(0);
	return TRUE;
}

void CDlgRemoteControllerCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	LONG lRemoteControllerNo = m_cmb_RemoteControllerNo.GetCurSel() + 1;

	NET_DVR_REMOTECONTROLLER_PERMISSION_CFG struRemoteConPermCfg = {0};
	struRemoteConPermCfg.dwSize = sizeof(NET_DVR_REMOTECONTROLLER_PERMISSION_CFG);

	struRemoteConPermCfg.bySubSystemID = m_cmb_SubSysNo.GetCurSel() + 1;
	struRemoteConPermCfg.byEnable = (BYTE)m_bEnable;
	strncpy((char*)struRemoteConPermCfg.sDevSn, m_strSerialNo, 16);
	struRemoteConPermCfg.byKeyboardAddr = m_iKeyBoradAddr;

	struRemoteConPermCfg.byArmRight = (BYTE)m_bArmRight;
	struRemoteConPermCfg.byDisArmRight = (BYTE)m_bDisArmRight;
	struRemoteConPermCfg.byArmReportRight = (BYTE)m_bArmReportRight;
	struRemoteConPermCfg.byDisArmReportRight = (BYTE)m_bDisArmReportRight;
	struRemoteConPermCfg.byClearAlarmRight = (BYTE)m_bClearArmRight;

    struRemoteConPermCfg.byEnableDel = (BYTE)m_bEnableDel;

    struRemoteConPermCfg.byAlwaysOpenRight = m_cmbAlwaysOpenRight.GetCurSel();
    struRemoteConPermCfg.byOpeningDirection = m_cmbOpeningDirection.GetCurSel();

    if (NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_REMOTECONTROLLER_PERMISION_CFG, lRemoteControllerNo, &struRemoteConPermCfg, sizeof(struRemoteConPermCfg)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_REMOTECONTROLLER_PERMISION_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_REMOTECONTROLLER_PERMISION_CFG");
    }
}

void CDlgRemoteControllerCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	LONG lRemoteControllerNo = m_cmb_RemoteControllerNo.GetCurSel() + 1;
    DWORD dwReturn = 0;

	NET_DVR_REMOTECONTROLLER_PERMISSION_CFG struRemoteConPermCfg = {0};
	struRemoteConPermCfg.dwSize = sizeof(NET_DVR_REMOTECONTROLLER_PERMISSION_CFG);

    if (NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_REMOTECONTROLLER_PERMISION_CFG, lRemoteControllerNo, &struRemoteConPermCfg, sizeof(struRemoteConPermCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_REMOTECONTROLLER_PERMISION_CFG");
    }
    else   
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_REMOTECONTROLLER_PERMISION_CFG");
        return;
    }
	
	m_cmb_SubSysNo.SetCurSel((int)struRemoteConPermCfg.bySubSystemID - 1);
	m_bEnable = (BOOL)struRemoteConPermCfg.byEnable;
	char sDevSn[16] = {0};
	memcpy(sDevSn, struRemoteConPermCfg.sDevSn, 16);
	m_strSerialNo = sDevSn;
	m_bArmRight = (BOOL)struRemoteConPermCfg.byArmRight;
	m_bDisArmRight = (BOOL)struRemoteConPermCfg.byDisArmRight;
	m_bArmReportRight = (BOOL)struRemoteConPermCfg.byArmReportRight;
	m_bDisArmReportRight = (BOOL)struRemoteConPermCfg.byDisArmReportRight;
	m_bClearArmRight = (BOOL)struRemoteConPermCfg.byClearAlarmRight;
	m_iKeyBoradAddr = struRemoteConPermCfg.byKeyboardAddr;
    m_bEnableDel = (BOOL)struRemoteConPermCfg.byEnableDel;
    m_cmbAlwaysOpenRight.SetCurSel(struRemoteConPermCfg.byAlwaysOpenRight);
    m_cmbOpeningDirection.SetCurSel(struRemoteConPermCfg.byOpeningDirection);

	UpdateData(FALSE);
}
