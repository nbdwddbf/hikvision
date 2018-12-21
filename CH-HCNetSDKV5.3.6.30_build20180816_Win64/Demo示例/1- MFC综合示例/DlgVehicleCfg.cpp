// DlgVehicleCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVehicleCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVehicleCfg dialog


CDlgVehicleCfg::CDlgVehicleCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVehicleCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVehicleCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_iChannelIndex = -1;
}


void CDlgVehicleCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVehicleCfg)
	DDX_Control(pDX, IDC_TAB_VEHICLE_CFG, m_tabVehicleCfg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVehicleCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVehicleCfg)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_VEHICLE_CFG, OnSelchangeTabVehicleCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVehicleCfg message handlers

void CDlgVehicleCfg::OnSelchangeTabVehicleCfg(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int iSel = m_tabVehicleCfg.GetCurSel();

	m_struVehicleControl.ShowWindow(SW_HIDE);
	m_struVehicleMvaCfg.ShowWindow(SW_HIDE);
	switch (iSel)
	{
	case 0:
		m_struVehicleControl.ShowWindow(SW_SHOW);
		break;
	case 1:
		m_struVehicleMvaCfg.ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}
	*pResult = 0;
}

BOOL CDlgVehicleCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	char szLan[128] = {0};
	g_StringLanType(szLan, "车载控制参数配置", "Vehicle Control Param Setup");
	m_tabVehicleCfg.InsertItem(0, szLan);
	g_StringLanType(szLan, "车载MVA参数配置", "Vehicle MVA Param Setup");
	m_tabVehicleCfg.InsertItem(1, szLan);

	m_struVehicleControl.m_lServerID = m_lServerID;
	m_struVehicleControl.m_dwAlarmOutNum = m_dwAlarmOutNum;
	m_struVehicleControl.m_dwDevIndex = m_dwDevIndex;
	m_struVehicleControl.m_nChannel = m_nChannel;
	m_struVehicleControl.m_lStartChan = m_lStartChan;
    m_struVehicleControl.Create(IDD_SUBDLG_VEHICLE_CONTROL_CFG, &m_tabVehicleCfg);
	m_struVehicleControl.ShowWindow(SW_SHOW);

	m_struVehicleMvaCfg.m_lServerID = m_lServerID;
	m_struVehicleMvaCfg.m_dwDevIndex = m_dwDevIndex;
	m_struVehicleMvaCfg.m_lChannal = m_iChannelIndex;
	m_struVehicleMvaCfg.Create(IDD_SUBDLG_VEHICLE_MVA_CFG, &m_tabVehicleCfg);
	m_struVehicleMvaCfg.ShowWindow(SW_HIDE);
	
//	m_tabVehicleCfg.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
