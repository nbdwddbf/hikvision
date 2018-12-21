// DlgInteractive.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInteractive.h"
#include "DlgInteractiveControl.h"
#include "DlgInteractiveFileInfoCfg.h"
#include "DlgInteractiveScreenConfig.h"
#include "DlgInteractiveScreenFileUpload.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInteractive dialog


CDlgInteractive::CDlgInteractive(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInteractive::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInteractive)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgInteractive::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInteractive)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInteractive, CDialog)
	//{{AFX_MSG_MAP(CDlgInteractive)
	ON_BN_CLICKED(IDC_BTN_FILE_CONFIG, OnBtnFileConfig)
	ON_BN_CLICKED(IDC_BTN_SCREEN_CTRL, OnBtnScreenCtrl)
	ON_BN_CLICKED(IDC_BTN_SCREEN_PARAM, OnBtnScreenParam)
	ON_BN_CLICKED(IDC_BTN_UPDOWNLOAD, OnBtnUpdownload)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInteractive message handlers

void CDlgInteractive::OnBtnFileConfig() 
{
	// TODO: Add your control notification handler code here
	CDlgInteractiveFileInfoCfg dlg;
	dlg.DoModal();
}

void CDlgInteractive::OnBtnScreenCtrl() 
{
	// TODO: Add your control notification handler code here
	CDlgInteractiveControl dlg;
	dlg.DoModal();
}

void CDlgInteractive::OnBtnScreenParam() 
{
	// TODO: Add your control notification handler code here
	CDlgInteractiveScreenConfig dlg;
	dlg.DoModal();
}

void CDlgInteractive::OnBtnUpdownload() 
{
	// TODO: Add your control notification handler code here
	CDlgInteractiveScreenFileUpload dlg;
	dlg.DoModal();
}
