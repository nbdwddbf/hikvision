// DlgVideoIntercomAuthCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVideoIntercomAuthCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomAuthCfg dialog


CDlgVideoIntercomAuthCfg::CDlgVideoIntercomAuthCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVideoIntercomAuthCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVideoIntercomAuthCfg)
	m_csPassWord = _T("");
	//}}AFX_DATA_INIT
}


void CDlgVideoIntercomAuthCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVideoIntercomAuthCfg)
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csPassWord);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVideoIntercomAuthCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVideoIntercomAuthCfg)
	ON_BN_CLICKED(IDC_BTN_TEST, OnBtnTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomAuthCfg message handlers

void CDlgVideoIntercomAuthCfg::OnBtnTest() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

    if (m_lUserID < 0)
    {
        return;
    }
    
    NET_DVR_OPERATION_AUTH struAuth = {0};
    struAuth.dwSize = sizeof(struAuth);
    strncpy((char*)struAuth.byPassword, m_csPassWord,PASSWD_LEN);
    
    if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_REMOTECONTROL_OPERATION_AUTH,&struAuth, sizeof(struAuth)))
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_REMOTECONTROL_OPERATION_AUTH");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_REMOTECONTROL_OPERATION_AUTH");
    }
	   
}
