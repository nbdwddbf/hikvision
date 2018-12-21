// B10SeriesConfig.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "B10SeriesConfig.h"

#include "DlgMatOutputCfg.h"
#include "DlgFiberRingCfg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CB10SeriesConfig dialog


CB10SeriesConfig::CB10SeriesConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CB10SeriesConfig::IDD, pParent)
{
	//{{AFX_DATA_INIT(CB10SeriesConfig)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CB10SeriesConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CB10SeriesConfig)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CB10SeriesConfig, CDialog)
	//{{AFX_MSG_MAP(CB10SeriesConfig)
	ON_BN_CLICKED(IDC_BUT_DISPLAYCHAN_CONFIG, OnButDisplaychanConfig)
	ON_BN_CLICKED(IDC_BUT_B10X_RINGCFG, OnButB10xRingcfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CB10SeriesConfig message handlers

void CB10SeriesConfig::OnButDisplaychanConfig() 
{
	// TODO: Add your control notification handler code here
	CDlgMatOutputCfg dlg;
	dlg.DoModal();
}

void CB10SeriesConfig::OnButB10xRingcfg() 
{
	// TODO: Add your control notification handler code here
	CDlgFiberRingCfg dlg; 
	dlg.DoModal(); 
}
