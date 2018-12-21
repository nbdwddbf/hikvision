/**********************************************************
FileName:    DlgConfigAll.cpp
Description: remote and local configuration, acquire log, device state switch      
Date:        2008/05/17
Note: 		 <global>struct, refer to GeneralDef.h, global variants and functions refer to ClientDemo.cpp    
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/


#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgConfigAll.h"
#include ".\dlgconfigall.h"


// CDlgConfigAll dialog
/*********************************************************
  Function:	CDlgConfigAll
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgConfigAll, CDialog)
CDlgConfigAll::CDlgConfigAll(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgConfigAll::IDD, pParent)
	, m_iDeviceIndex(-1)
	, m_iConfigType(REMOTE_DEVICE_CFG_T)
{
}

/*********************************************************
  Function:	~CDlgConfigAll
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgConfigAll::~CDlgConfigAll()
{
}

/*********************************************************
  Function:	DoDataExchange
  Desc:		exchange between control and data
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgConfigAll::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	        //{{AFX_DATA_MAP(CDlgConfigAll)

	        //}}AFX_DATA_MAP
}

/*********************************************************
  Function:	BEGIN_MESSAGE_MAP
  Desc:		message map list
  Input:	CDlgConfigAll,current subclass;CDialog,parent class;
  Output:	
  Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgConfigAll, CDialog)
	//{{AFX_MSG_MAP(CDlgConfigAll)
	ON_BN_CLICKED(IDC_BTN_REMOTE_CONFIG, OnBnClickedBtnRemoteConfig)
	ON_BN_CLICKED(IDC_BTN_LOCAL_CONFIG, OnBnClickedBtnLocalConfig)
	ON_BN_CLICKED(IDC_BTN_IP_ACCESS, OnBnClickedBtnIPAccess)
	ON_BN_CLICKED(IDC_BTN_BACK_PREVIEW, OnBnClickedBtnBackPreview)
	ON_BN_CLICKED(IDC_BTN_HARD_DISK, OnBnClickedBtnHDConfig)	
	ON_BN_CLICKED(IDC_BTN_BATCH_CONFIG, OnBtnBatchConfig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*********************************************************
  Function:	OnBnClickedBtnRemoteConfig
  Desc:		switch to remote configuration interface
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgConfigAll::OnBnClickedBtnRemoteConfig()
{
	m_iConfigType = g_pMainDlg->m_dlgRemoteCfg->m_iRemoteConfigType;
	g_pMainDlg->ListRestore();
	g_pMainDlg->m_dlgLocalCfg->ShowWindow(SW_HIDE);
	g_pMainDlg->m_dlgIPAccess->ShowWindow(SW_HIDE);
	g_pMainDlg->m_dlgHDConfig->ShowWindow(SW_HIDE);
	g_pMainDlg->m_dlgBatchCfg->ShowWindow(SW_HIDE);
	g_pMainDlg->m_dlgRemoteCfg->ShowWindow(SW_SHOW);
	
	g_pMainDlg->m_dlgRemoteCfg->RemoteConfigUpdate(m_iConfigType);
	GetDlgItem(IDC_BTN_LOCAL_CONFIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_REMOTE_CONFIG)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_IP_ACCESS)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_HARD_DISK)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_BATCH_CONFIG)->EnableWindow(TRUE);
}

/*********************************************************
  Function:	OnBnClickedBtnLocalConfig
  Desc:		switch to local configuration
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgConfigAll::OnBnClickedBtnLocalConfig()
{
	m_iConfigType = LOCAL_CFG_T;
	g_pMainDlg->ListRestore();
	g_pMainDlg->m_dlgRemoteCfg->ShowWindow(SW_HIDE);
	g_pMainDlg->m_dlgIPAccess->ShowWindow(SW_HIDE);
	g_pMainDlg->m_dlgHDConfig->ShowWindow(SW_HIDE);
	g_pMainDlg->m_dlgBatchCfg->ShowWindow(SW_HIDE);
	g_pMainDlg->m_dlgLocalCfg->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_BTN_LOCAL_CONFIG)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_REMOTE_CONFIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_IP_ACCESS)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_HARD_DISK)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_BATCH_CONFIG)->EnableWindow(TRUE);
}

/*********************************************************
  Function:	OnBnClickedBtnIPAccess
  Desc:		switch to setup ip access configure
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgConfigAll::OnBnClickedBtnIPAccess()
{
	m_iConfigType = LOG_QUERY_T;
	g_pMainDlg->ListRestore();
	g_pMainDlg->m_dlgRemoteCfg->ShowWindow(SW_HIDE);
	g_pMainDlg->m_dlgLocalCfg->ShowWindow(SW_HIDE);
	g_pMainDlg->m_dlgHDConfig->ShowWindow(SW_HIDE);
	g_pMainDlg->m_dlgBatchCfg->ShowWindow(SW_HIDE);
	g_pMainDlg->m_dlgIPAccess->CheckInitParam();

	GetDlgItem(IDC_BTN_LOCAL_CONFIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_REMOTE_CONFIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_IP_ACCESS)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_HARD_DISK)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_BATCH_CONFIG)->EnableWindow(TRUE);
}

/*********************************************************
  Function:	OnBnClickedBtnHDConfig
  Desc:		hard disk configure
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgConfigAll::OnBnClickedBtnHDConfig()
{
	m_iConfigType = DECODE_CARD_CFG_T;
	g_pMainDlg->ListRestore();
	g_pMainDlg->m_dlgRemoteCfg->ShowWindow(SW_HIDE);
	g_pMainDlg->m_dlgLocalCfg->ShowWindow(SW_HIDE);
	g_pMainDlg->m_dlgIPAccess->ShowWindow(SW_HIDE);
	g_pMainDlg->m_dlgBatchCfg->ShowWindow(SW_HIDE);
	g_pMainDlg->m_dlgHDConfig->CheckInitParam();
	
	GetDlgItem(IDC_BTN_LOCAL_CONFIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_REMOTE_CONFIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_IP_ACCESS)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_BATCH_CONFIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_HARD_DISK)->EnableWindow(FALSE);
}

/*********************************************************
  Function:	ConfigWndUpdate
  Desc:		configure window update
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgConfigAll::ConfigWndUpdate()
{
	if (m_iConfigType == LOCAL_CFG_T)
	{
		OnBnClickedBtnLocalConfig();
	}
	else if (m_iConfigType == LOG_QUERY_T)
	{
		OnBnClickedBtnIPAccess();
	}
	else if (m_iConfigType == DECODE_CARD_CFG_T)
	{
		OnBnClickedBtnHDConfig();
	}
	else if (m_iConfigType == BATCH_CFG_T)
	{
		OnBtnBatchConfig();
	}
	else
	{
		//m_iConfigType = REMOTE_DEVICE_CFG_T;
		OnBnClickedBtnRemoteConfig();
	}
}

/*********************************************************
  Function:	OnBnClickedBtnBackPreview
  Desc:		return to preview
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgConfigAll::OnBnClickedBtnBackPreview()
{
	g_pMainDlg->ListRestore();
	g_pMainDlg->OnBnClickedBtnPreview();
}

void CDlgConfigAll::OnBtnBatchConfig() 
{
	// TODO: Add your control notification handler code here
	m_iConfigType = BATCH_CFG_T;
	g_pMainDlg->ListRestore();
	g_pMainDlg->m_dlgLocalCfg->ShowWindow(SW_HIDE);
	g_pMainDlg->m_dlgIPAccess->ShowWindow(SW_HIDE);
	g_pMainDlg->m_dlgHDConfig->ShowWindow(SW_HIDE);
	g_pMainDlg->m_dlgRemoteCfg->ShowWindow(SW_HIDE);
	g_pMainDlg->m_dlgBatchCfg->ShowWindow(SW_SHOW);
	
	g_pMainDlg->m_dlgBatchCfg->BatchConfigUpdate();
	GetDlgItem(IDC_BTN_LOCAL_CONFIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_REMOTE_CONFIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_IP_ACCESS)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_HARD_DISK)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_BATCH_CONFIG)->EnableWindow(FALSE);
	
}
