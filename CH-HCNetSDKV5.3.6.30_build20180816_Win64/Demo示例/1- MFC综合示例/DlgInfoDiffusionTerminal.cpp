// DlgInfoDiffusionTerminal.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInfoDiffusionTerminal.h"
#include "DlgTermManage.h"
#include "DlgTermState.h"
#include "DlgTermPlay.h"
#include "DlgTermGroup.h"
#include "DlgInfoDiffusionPlay.h"
#include "DlgInfoDiffusionTerminalUpgrade.h"
#include "DlgInfoDiffusionTernimalPreview.h"
#include "DlgInfoDiffusionTermainlServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionTerminal dialog


CDlgInfoDiffusionTerminal::CDlgInfoDiffusionTerminal(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInfoDiffusionTerminal::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInfoDiffusionTerminal)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgInfoDiffusionTerminal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInfoDiffusionTerminal)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInfoDiffusionTerminal, CDialog)
	//{{AFX_MSG_MAP(CDlgInfoDiffusionTerminal)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_TERMINAL_CONFIG, OnBtnTerminalConfig)
	ON_BN_CLICKED(IDC_BTN_TERMINAL_CONTROL, OnBtnTerminalControl)
	ON_BN_CLICKED(IDC_BTN_TERMINAL_STATUS, OnBtnTerminalStatus)
	ON_BN_CLICKED(IDC_BTN_TERMINAL_PLAY, OnBtnTerminalPlay)
	ON_BN_CLICKED(IDC_BTN_TERMINAL_GROUP, OnBtnTerminalGroup)
	ON_BN_CLICKED(IDC_BTN_TERMINAL_UPGRADE, OnBtnTerminalUpgrade)
	ON_BN_CLICKED(IDC_BTN_TERMINAL_PREVIEW, OnBtnTerminalPreview)
	ON_BN_CLICKED(IDC_BTN_TERMINAL_SERVER, OnBtnTerminalServer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionTerminal message handlers

void CDlgInfoDiffusionTerminal::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CDlgInfoDiffusionTerminal::OnBtnTerminalConfig() 
{
	// TODO: Add your control notification handler code here
	CDlgTermManage dlg;
	dlg.DoModal();
}

void CDlgInfoDiffusionTerminal::OnBtnTerminalControl() 
{
	// TODO: Add your control notification handler code here
	CDlgInfoDiffusionPlay dlg;
	dlg.DoModal();
}

void CDlgInfoDiffusionTerminal::OnBtnTerminalStatus() 
{
	// TODO: Add your control notification handler code here
	CDlgTermState dlg;
	dlg.DoModal();
}

void CDlgInfoDiffusionTerminal::OnBtnTerminalPlay() 
{
	// TODO: Add your control notification handler code here
	CDlgTermPlay dlg;
	dlg.DoModal();
}

void CDlgInfoDiffusionTerminal::OnBtnTerminalGroup() 
{
	// TODO: Add your control notification handler code here
	CDlgTermGroup dlg;
	dlg.DoModal();
}

void CDlgInfoDiffusionTerminal::OnBtnTerminalUpgrade() 
{
	// TODO: Add your control notification handler code here
	CDlgInfoDiffusionTerminalUpgrade dlg;
	dlg.DoModal();
}

void CDlgInfoDiffusionTerminal::OnBtnTerminalPreview() 
{
	// TODO: Add your control notification handler code here
	CDlgInfoDiffusionTernimalPreview dlg;
	dlg.DoModal();
}

void CDlgInfoDiffusionTerminal::OnBtnTerminalServer() 
{
	// TODO: Add your control notification handler code here
	CDlgInfoDiffusionTermainlServer dlg;
    dlg.DoModal();
}
