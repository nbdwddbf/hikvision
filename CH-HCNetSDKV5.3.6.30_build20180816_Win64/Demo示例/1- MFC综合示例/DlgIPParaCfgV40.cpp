// DlgIPParaCfgV40.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgIPParaCfgV40.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIPParaCfgV40 dialog


CDlgIPParaCfgV40::CDlgIPParaCfgV40(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIPParaCfgV40::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgIPParaCfgV40)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    memset(&m_struIPParaCfgV40, 0, sizeof(m_struIPParaCfgV40));
}


void CDlgIPParaCfgV40::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIPParaCfgV40)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIPParaCfgV40, CDialog)
	//{{AFX_MSG_MAP(CDlgIPParaCfgV40)
	ON_BN_CLICKED(IDC_BTN_SETUP, OnBtnSetup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgIPParaCfgV40 message handlers

void CDlgIPParaCfgV40::OnBtnSetup() 
{
	// TODO: Add your control notification handler code here

    if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_IPPARACFG_V40, 0, &m_struIPParaCfgV40, sizeof(m_struIPParaCfgV40)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_IPPARACFG_V40");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_IPPARACFG_V40");
    }

}

BOOL CDlgIPParaCfgV40::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_IPPARACFG_V40, 0, &m_struIPParaCfgV40, sizeof(m_struIPParaCfgV40), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_IPPARACFG_V40");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_IPPARACFG_V40");
    }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
