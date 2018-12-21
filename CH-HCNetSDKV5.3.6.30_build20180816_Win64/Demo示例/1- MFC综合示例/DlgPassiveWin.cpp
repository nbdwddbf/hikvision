// DlgPassiveWin.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPassiveWin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CDlgOutput g_passiveWin;
/////////////////////////////////////////////////////////////////////////////
// CDlgPassiveWin dialog


CDlgPassiveWin::CDlgPassiveWin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPassiveWin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPassiveWin)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgPassiveWin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPassiveWin)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPassiveWin, CDialog)
	//{{AFX_MSG_MAP(CDlgPassiveWin)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPassiveWin message handlers

BOOL CDlgPassiveWin::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	g_passiveWin.Create(IDD_DLG_OUTPUT,this);
	MoveWindow();
	g_passiveWin.ShowWindow(SW_SHOW);	
	g_passiveWin.DrawOutputBorder();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPassiveWin::MoveWindow()
{
	CRect cRect;
	GetClientRect(&cRect);
	g_passiveWin.MoveWindow(cRect.left + 40, cRect.top + 20, cRect.Width() - 80, cRect.Height() - 80);
}

void CDlgPassiveWin::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	g_passiveWin.StopSound();
	this->ShowWindow(SW_HIDE);
	//CDialog::OnCancel();
}
