// DlgCloudManage.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgCloudManage.h"
#include "DlgCloudUrlCfg.h"
#include "DlgCloudCfg.h"
#include "DlgCloudUploadstrategyCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCloudManage dialog


CDlgCloudManage::CDlgCloudManage(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCloudManage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCloudManage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgCloudManage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCloudManage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCloudManage, CDialog)
	//{{AFX_MSG_MAP(CDlgCloudManage)
	ON_BN_CLICKED(IDC_BTN_CLOUD_URL_CFG, OnBtnCloudUrlCfg)
	ON_BN_CLICKED(IDC_BTN_CLOUD_CFG, OnBtnCloudCfg)
	ON_BN_CLICKED(IDC_BTN_CLOUD_UPLOADSTRATEGY_CFG, OnBtnCloudUploadstrategyCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCloudManage message handlers

void CDlgCloudManage::OnBtnCloudUrlCfg() 
{
	// TODO: Add your control notification handler code here
    CDlgCloudUrlCfg dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_lChanNo = m_lChanNo;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgCloudManage::OnBtnCloudCfg() 
{
	// TODO: Add your control notification handler code here
    CDlgCloudCfg dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_lChanNo = m_lChanNo;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgCloudManage::OnBtnCloudUploadstrategyCfg() 
{
	// TODO: Add your control notification handler code here
    CDlgCloudUploadstrategyCfg dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_lChanNo = m_lChanNo;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}
