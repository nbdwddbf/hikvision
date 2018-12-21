// DlgNetraSeries.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgNetraSeries.h"
#include "DlgNetraEventVedio.h"
#include "DlgNetraRecordPackage.h"
#include "DlgNetraHttps.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNetraSeries dialog


CDlgNetraSeries::CDlgNetraSeries(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNetraSeries::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNetraSeries)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgNetraSeries::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNetraSeries)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNetraSeries, CDialog)
	//{{AFX_MSG_MAP(CDlgNetraSeries)
	ON_BN_CLICKED(IDC_BTN_EVENT_TRIGER_VEDIO, OnBtnEventTrigerVedio)
	ON_BN_CLICKED(IDC_BTN_RECORD_PACKAGE, OnBtnRecordPackage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNetraSeries message handlers

void CDlgNetraSeries::OnBtnEventTrigerVedio() 
{
	// TODO: Add your control notification handler code here
	CDlgNetraEventVedio dlg ;
	dlg.m_lLoginID = m_lLoginID;
	dlg.m_lChannel = m_lChannel;
	dlg.m_iDeviceIndex = m_iDevIndex ;
	dlg.DoModal();
	
}

BOOL CDlgNetraSeries::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgNetraSeries::OnBtnRecordPackage() 
{
	// TODO: Add your control notification handler code here
	CDlgNetraRecordPackage  dlg ;
	dlg.m_lLoginID = m_lLoginID;
	dlg.m_lChannel = m_lChannel;
	dlg.m_iDevIndex = m_iDevIndex ;
	dlg.DoModal();

}
