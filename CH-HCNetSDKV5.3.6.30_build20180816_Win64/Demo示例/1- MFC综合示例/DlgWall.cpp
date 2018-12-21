// DlgWall.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgWall.h"


#include "DlgWallWin.h"
#include "DlgScreenLogoCfg.h"
#include "DlgSenceControl.h"
#include "DlgDecWinStatus.h"
#include "DlgWinPreview.h"
#include "DlgWallCfg.h"
#include "DlgMatUnitedSystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWall dialog


CDlgWall::CDlgWall(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWall::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgWall)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgWall::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWall)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWall, CDialog)
	//{{AFX_MSG_MAP(CDlgWall)
	ON_BN_CLICKED(IDC_BTN_WALL_CFG, OnBtnWallCfg)
	ON_BN_CLICKED(IDC_BTN_WINCFG, OnBtnWincfg)
	ON_BN_CLICKED(IDC_BTN_PIC, OnBtnPic)
	ON_BN_CLICKED(IDC_BTN_SENCE, OnBtnSence)
	ON_BN_CLICKED(IDC_BTN_WALL_WIN_STATUS, OnBtnWallWinStatus)
	ON_BN_CLICKED(IDC_BTN_PIC_PREVIEW, OnBtnPicPreview)
	ON_BN_CLICKED(IDC_BTN_UNITED_SYSTEM, OnBtnUnitedSystem)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWall message handlers

void CDlgWall::OnBtnWallCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgWallCfg dlg;
	dlg.m_lUserID = m_lServerID;
	dlg.DoModal();
}

void CDlgWall::OnBtnWincfg() 
{
	// TODO: Add your control notification handler code here
	CDlgWallWin dlg;
	dlg.m_lUserID = m_lServerID;
	dlg.DoModal();
}

void CDlgWall::OnBtnPic() 
{
	// TODO: Add your control notification handler code here
	CDlgScreenLogoCfg dlg;
	dlg.DoModal();
}

void CDlgWall::OnBtnSence() 
{
	// TODO: Add your control notification handler code here
	CDlgSenceControl dlg;
	dlg.m_lUserID = m_lServerID;
	dlg.DoModal();
}

void CDlgWall::OnBtnWallWinStatus() 
{
	// TODO: Add your control notification handler code here
	CDlgDecWinStatus dlg;
	dlg.m_lUserID = m_lServerID;
	dlg.DoModal();
}

void CDlgWall::OnBtnPicPreview() 
{
	// TODO: Add your control notification handler code here
	CDlgWinPreview dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.DoModal();
}

void CDlgWall::OnBtnUnitedSystem() 
{
	// TODO: Add your control notification handler code here
	CDlgMatUnitedSystem dlg;
	dlg.m_lUserID = m_lServerID;
	dlg.DoModal();
}

void CDlgWall::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}
