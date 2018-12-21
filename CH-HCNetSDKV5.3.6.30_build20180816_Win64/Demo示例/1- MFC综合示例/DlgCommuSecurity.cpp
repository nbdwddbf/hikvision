// DlgCommuSecurity.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgCommuSecurity.h"
#include "DlgSecurityCfg.h"
#include "DlgLockedInfo.h"
#include "DlgEncryptCert.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgCommuSecurity dialog


DlgCommuSecurity::DlgCommuSecurity(CWnd* pParent /*=NULL*/)
	: CDialog(DlgCommuSecurity::IDD, pParent)
    , m_lUSerID(-1)
    , m_lChannel(-1)
{
	//{{AFX_DATA_INIT(DlgCommuSecurity)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgCommuSecurity::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgCommuSecurity)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgCommuSecurity, CDialog)
	//{{AFX_MSG_MAP(DlgCommuSecurity)
	ON_BN_CLICKED(IDC_BTN_SECRITY_CFG, OnBtnSecrityCfg)
	ON_BN_CLICKED(IDC_BTN_PW_MANAGE_CFG, OnBtnPwManageCfg)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_ENCRYPT_CERT, &DlgCommuSecurity::OnBnClickedBtnEncryptCert)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgCommuSecurity message handlers

void DlgCommuSecurity::OnBtnSecrityCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgSecurityCfg dlg;
    dlg.DoModal();
}

void DlgCommuSecurity::OnBtnPwManageCfg() 
{
	// TODO: Add your control notification handler code here
    CDlgLockedInfo dlg;
    dlg.DoModal();
}


void DlgCommuSecurity::OnBnClickedBtnEncryptCert()
{
	// TODO:  在此添加控件通知处理程序代码
    CDlgEncryptCert dlg;
    dlg.m_lUSerID = m_lUSerID;
    dlg.m_lChannel = m_lChannel;
    dlg.DoModal();
}
