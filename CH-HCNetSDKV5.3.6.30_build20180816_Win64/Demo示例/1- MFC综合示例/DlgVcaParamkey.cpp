// DlgVcaParamkey.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaParamkey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaParamkey dialog


CDlgVcaParamkey::CDlgVcaParamkey(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaParamkey::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaParamkey)
	m_iKey = 0;
	m_nParamKey = 0;
	//}}AFX_DATA_INIT
}


void CDlgVcaParamkey::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaParamkey)
	DDX_Control(pDX, IDC_COMBO_PARAMKEY, m_ComboParamkey);
	DDX_Text(pDX, IDC_EDIT_KEY, m_iKey);
	DDX_Text(pDX, IDC_EDIT_PARAM_KEY, m_nParamKey);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaParamkey, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaParamkey)
	ON_BN_CLICKED(IDC_BUTTON_GET_PARAMKEY, OnButtonGetParamkey)
	ON_CBN_SELCHANGE(IDC_COMBO_PARAMKEY, OnSelchangeComboParamkey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaParamkey message handlers

BOOL CDlgVcaParamkey::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVcaParamkey::OnButtonGetParamkey() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_dwParameterKey = GetParamIndex();
	if (!NET_DVR_GetBehaviorParamKey(m_lServerID,  m_lChannel, m_dwParameterKey, &m_iKey))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetBehaviorParamKey %d", m_lChannel);
		AfxMessageBox("Get keyword fail!");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetBehaviorParamKey %d", m_lChannel);
	}
	UpdateData(FALSE);
}

void CDlgVcaParamkey::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	m_dwParameterKey = GetParamIndex();
	if (!NET_DVR_SetBehaviorParamKey(m_lServerID,  m_lChannel, m_dwParameterKey, m_iKey))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SetBehaviorParamKey %d", m_lChannel);
		AfxMessageBox("Set keyword fail");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SetBehaviorParamKey %d", m_lChannel);
		AfxMessageBox("Set keyword succ");
	}

//	CDialog::OnOK();
}

int CDlgVcaParamkey::GetParamIndex()
{
	UpdateData(TRUE);
    return m_nParamKey;
}

void CDlgVcaParamkey::OnSelchangeComboParamkey() 
{
	// TODO: Add your control notification handler code here
	
}
