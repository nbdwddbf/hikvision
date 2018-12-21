// DlgPictureSwitchCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgPictureSwitchCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPictureSwitchCtrl dialog


CDlgPictureSwitchCtrl::CDlgPictureSwitchCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPictureSwitchCtrl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPictureSwitchCtrl)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lUserID = 0;
    m_iDevIndex = 0;
    m_dwChannel = 0;
}


void CDlgPictureSwitchCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPictureSwitchCtrl)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPictureSwitchCtrl, CDialog)
	//{{AFX_MSG_MAP(CDlgPictureSwitchCtrl)
	ON_BN_CLICKED(IDC_BTN_SWITCH, OnBtnSwitch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgPictureSwitchCtrl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// CDlgPictureSwitchCtrl message handlers

void CDlgPictureSwitchCtrl::OnBtnSwitch() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	memset(&m_struScreenSwitch, 0, sizeof(NET_DVR_SCREEN_SWITCH));
	m_struScreenSwitch.dwSize = sizeof(NET_DVR_SCREEN_SWITCH);

	BOOL bIPRet = FALSE;
	bIPRet = NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_SCREEN_SWITCH, m_dwChannel, &m_struScreenSwitch, sizeof(NET_DVR_SCREEN_SWITCH));
	if (bIPRet)
	{		
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SCREEN_SWITCH");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SCREEN_SWITCH");
	}
}
