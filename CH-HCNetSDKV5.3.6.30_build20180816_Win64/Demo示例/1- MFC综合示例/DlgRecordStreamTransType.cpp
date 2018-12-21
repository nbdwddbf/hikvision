// DlgRecordStreamTransType.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRecordStreamTransType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordStreamTransType dialog


CDlgRecordStreamTransType::CDlgRecordStreamTransType(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRecordStreamTransType::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRecordStreamTransType)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgRecordStreamTransType::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRecordStreamTransType)
	DDX_Control(pDX, IDC_COMBO_STREAM_TRANS_TYPE, m_ctrlStreamTransType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRecordStreamTransType, CDialog)
	//{{AFX_MSG_MAP(CDlgRecordStreamTransType)
	ON_BN_CLICKED(IDC_BTN_SAVE_STREAM_TYPE, OnBtnSaveStreamType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordStreamTransType message handlers

void CDlgRecordStreamTransType::OnBtnSaveStreamType() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	g_dwStreamTransType = m_ctrlStreamTransType.GetCurSel();
}

BOOL CDlgRecordStreamTransType::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ctrlStreamTransType.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
