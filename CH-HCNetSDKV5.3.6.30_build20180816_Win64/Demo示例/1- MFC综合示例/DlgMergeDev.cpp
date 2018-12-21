// DlgMergeDev.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMergeDev.h"
#include "DlgWallCfgUniform.h"
#include "DlgWallWinVideoWall.h"
#include "DlgSenceControlUniform.h"
#include "DlgMergeDevPic.h"
#include "DlgMergeDecOsd.h"
#include "DlgMergeDevResource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMergeDev dialog


CDlgMergeDev::CDlgMergeDev(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMergeDev::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMergeDev)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgMergeDev::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMergeDev)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMergeDev, CDialog)
	//{{AFX_MSG_MAP(CDlgMergeDev)
	ON_BN_CLICKED(IDC_BTN_OUTPUT_CFG, OnBtnOutputCfg)
	ON_BN_CLICKED(IDC_BTN_WIN_CFG, OnBtnWinCfg)
	ON_BN_CLICKED(IDC_BTN_OUTPUT_PIC, OnBtnOutputPic)
	ON_BN_CLICKED(IDC_BTN_OUTPUT_OSD, OnBtnOutputOsd)
	ON_BN_CLICKED(IDC_BTN_CHAN_RESOURCE, OnBtnChanResource)
	ON_BN_CLICKED(IDC_BTN_SCENE, OnBtnScene)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMergeDev message handlers

BOOL CDlgMergeDev::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgMergeDev::OnBtnOutputCfg() 
{
	// TODO: Add your control notification handler code here
    CDlgWallCfg_Uniform dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();	
}

void CDlgMergeDev::OnBtnWinCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgWallWinVideoWall dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
}

void CDlgMergeDev::OnBtnOutputPic() 
{
	// TODO: Add your control notification handler code here

    CDlgMergeDevPic dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();

}

void CDlgMergeDev::OnBtnOutputOsd() 
{
	// TODO: Add your control notification handler code here
	CDlgMergeDecOsd dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
}

void CDlgMergeDev::OnBtnChanResource() 
{
	// TODO: Add your control notification handler code here
    CDlgMergeDevResource dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();	
}

void CDlgMergeDev::OnBtnScene() 
{
	// TODO: Add your control notification handler code here
    CDlgSenceControlUniform dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();	
}

void CDlgMergeDev::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
