// DlgFiberRingCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgFiberRingCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFiberRingCfg dialog


CDlgFiberRingCfg::CDlgFiberRingCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFiberRingCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFiberRingCfg)
	m_BEnable = FALSE;
	m_byPortNo = 1;
	m_byPortNo2 = 1;
	m_dwRingNo = 1;
	//}}AFX_DATA_INIT
}


void CDlgFiberRingCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFiberRingCfg)
	DDX_Control(pDX, IDC_COMBO_FR_DEVICE_MASTERSLAVE, m_cmbDeviceMasterSlave);
	DDX_Control(pDX, IDC_COMBO_FR_STATUS, m_cmbStatus);
	DDX_Control(pDX, IDC_COMBO_FR_PROTOTYPE, m_cmbProtoType);
	DDX_Control(pDX, IDC_COMBO_FR_PORTETHERNETTYPE2, m_cmbPortEthernet2);
	DDX_Control(pDX, IDC_COMBO_FR_PORTETHERNETTYPE, m_cmbPortEthernet);
	DDX_Control(pDX, IDC_COMBO_FR_MASTERSLAVE2, m_cmbMasterSlave2);
	DDX_Control(pDX, IDC_COMBO_FR_MASTERSLAVE, m_cmbMasterSlave);
	DDX_Control(pDX, IDC_COMBO_FR_BANDWIDTH, m_cmbBandwidth);
	DDX_Check(pDX, IDC_CHK_FR_ENABLE, m_BEnable);
	DDX_Text(pDX, IDC_EDT_FR_PORTNO, m_byPortNo);
	DDX_Text(pDX, IDC_EDT_FR_PORTNO2, m_byPortNo2);
	DDX_Text(pDX, IDC_EDT_FR_RINGNO, m_dwRingNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFiberRingCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgFiberRingCfg)
	ON_BN_CLICKED(IDC_BUT_GET, OnButGet)
	ON_BN_CLICKED(IDC_BUT_SET, OnButSet)
	ON_BN_CLICKED(IDC_BUT_GET_STATUS, OnButGetStatus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFiberRingCfg message handlers

void CDlgFiberRingCfg::OnButGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
	NET_DVR_NS_RING_CFG struRingCfg = {0}; 
	DWORD dwRet; 
	if ( !NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_NS_RING_CFG, m_dwRingNo, &struRingCfg, sizeof(struRingCfg), &dwRet) )
	{
		g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_GET_NS_RING_CFG" ); 
		return ; 
	}
	g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_GET_NS_RING_CFG" );
	m_BEnable = struRingCfg.byEnable; 
	m_cmbProtoType.SetCurSel(struRingCfg.byProtoType-1); 
	m_cmbBandwidth.SetCurSel(struRingCfg.byBandWidth-1); 

	m_byPortNo = struRingCfg.struRingPort[0].byPort; 
	m_cmbMasterSlave.SetCurSel(struRingCfg.struRingPort[0].byMasterSlaveProperty-1); 
	m_cmbPortEthernet.SetCurSel(struRingCfg.struRingPort[0].byPortEthernetType-1); 
	m_byPortNo2 = struRingCfg.struRingPort[1].byPort; 
	m_cmbMasterSlave2.SetCurSel(struRingCfg.struRingPort[1].byMasterSlaveProperty-1); 
	m_cmbPortEthernet2.SetCurSel(struRingCfg.struRingPort[1].byPortEthernetType-1); 

	UpdateData(FALSE); 
}

void CDlgFiberRingCfg::OnButSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
	NET_DVR_NS_RING_CFG struRingCfg = {0}; 
	struRingCfg.dwSize= sizeof(struRingCfg); 
	struRingCfg.byEnable = 	m_BEnable ; 
	struRingCfg.byProtoType = m_cmbProtoType.GetCurSel() + 1; 
	struRingCfg.byBandWidth = m_cmbBandwidth.GetCurSel() + 1; 
	struRingCfg.struRingPort[0].byPort = 	m_byPortNo ; 
	struRingCfg.struRingPort[0].byMasterSlaveProperty = m_cmbMasterSlave.GetCurSel() + 1; 
	struRingCfg.struRingPort[0].byPortEthernetType = m_cmbPortEthernet.GetCurSel() + 1; 
	struRingCfg.struRingPort[1].byPort = 	m_byPortNo2 ; 
	struRingCfg.struRingPort[1].byMasterSlaveProperty = m_cmbMasterSlave2.GetCurSel() + 1; 
	struRingCfg.struRingPort[1].byPortEthernetType = m_cmbPortEthernet2.GetCurSel() + 1; 
	if ( !NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_NS_RING_CFG, m_dwRingNo, &struRingCfg, sizeof(struRingCfg)) )
	{
		g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_SET_NS_RING_CFG" ); 
		return ; 
	}
	g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_SET_NS_RING_CFG" ); 
}

void CDlgFiberRingCfg::OnButGetStatus() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
	NET_DVR_NS_RING_STATUS struRingStatus = {0}; 
	DWORD dwRet; 
	if ( !NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_NS_RING_STATUS, m_dwRingNo, &struRingStatus, sizeof(struRingStatus), &dwRet) )
	{
		g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_GET_NS_RING_STATUS" ); 
		return ; 
	}
	g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_GET_NS_RING_STATUS" ); 
	m_cmbStatus.SetCurSel(struRingStatus.byStatus-1); 
	m_cmbDeviceMasterSlave.SetCurSel(struRingStatus.byMasterSlaveProperty-1); 
	UpdateData(TRUE); 
}

BOOL CDlgFiberRingCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_lDeviceID = g_pMainDlg->GetCurDeviceIndex(); 
	m_lUserID = g_struDeviceInfo[m_lDeviceID].lLoginID; 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
