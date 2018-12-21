// DlgBatchConfig.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgBatchConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBatchConfig dialog


CDlgBatchConfig::CDlgBatchConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBatchConfig::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBatchConfig)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgBatchConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBatchConfig)
	DDX_Control(pDX, IDC_TAB_BATCH_CONFIG, m_tabBatchConfig);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBatchConfig, CDialog)
	//{{AFX_MSG_MAP(CDlgBatchConfig)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_BATCH_CONFIG, OnSelchangeTabBatchConfig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBatchConfig message handlers

BOOL CDlgBatchConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char szLan[128] = {0};
	g_StringLanType(szLan, "用户权限配置", "User right config");
	m_tabBatchConfig.InsertItem(0, szLan);

	
	m_UserRightCfg.Create(IDD_DLG_BATCH_USER_RIGHT_CFG, &m_tabBatchConfig);

	m_UserRightCfg.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*********************************************************
  Function:	BatchConfigUpdate
  Desc:		paramter Update
  Input:	iConfigType, relative batch config page
  Output:	
  Return:	
**********************************************************/
void CDlgBatchConfig::BatchConfigUpdate(void)
{

	switch (m_iTabIndex)
	{
	case 0:
		m_UserRightCfg.ShowWindow(SW_SHOW);
		break;
	default:
		m_UserRightCfg.ShowWindow(SW_SHOW);
		break;
	}
}

void CDlgBatchConfig::OnSelchangeTabBatchConfig(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_iTabIndex = m_tabBatchConfig.GetCurSel();
	BatchConfigUpdate();

	*pResult = 0;
}
