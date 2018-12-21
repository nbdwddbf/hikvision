// DlgSubITSCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgSubITSCfg.h"
#include "DlgTsSeries.h"
#include "DlgITSIOinCfg.h"
#include "DlgITSConfig.h"
#include "DlgITSMonitor.h"
#include "DlgITSMiniPost.h"
#include "DlgWIFIServerCfg.h"
#include "DlgMobileTriggerCfg.h"
#include "DlgPostRadarCfg.h"
#include "DlgUHFRFIDReaderCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSubITSCfg dialog


CSubDlgITSCfg::CSubDlgITSCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubDlgITSCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSubITSCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lDeviceIndex = -1;
	m_lUserID = -1;
	m_lChannel = -1;
	m_lChanCount = -1;
}


void CSubDlgITSCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSubITSCfg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubDlgITSCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgSubITSCfg)
	ON_BN_CLICKED(IDC_BTN_TS, OnBtnTs)
	ON_BN_CLICKED(IDC_BTN_ITS_IOIN_CFG, OnBtnItsIoinCfg)
	ON_BN_CLICKED(IDC_BTN_ITS_CONFIG, OnBtnItsConfig)
	ON_BN_CLICKED(IDC_BTN_ITS_MONITOR, OnBtnItsMonitor)
	ON_BN_CLICKED(IDC_BTN_ITS_MINI_POST, OnBtnItsMiniPost)
	ON_BN_CLICKED(IDC_BTN_WIFI_SERVER_CFG, OnBtnWifiServerCfg)
	ON_BN_CLICKED(IDC_BTN_MOBILE_TRIGGER_CFG, OnBtnMobileTriggerCfg)
    ON_BN_CLICKED(IDC_BTN_POSTRADAR, OnBtnPostRadarCfg)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON_UHF_RFID_READER, &CSubDlgITSCfg::OnBnClickedButtonUhfRfidReader)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSubITSCfg message handlers

void CSubDlgITSCfg::CurCfgUpdate()
{
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    if (iDeviceIndex < 0)
    {
		EnableWindow(FALSE);
        return;
    }
	
	EnableWindow(TRUE);
    int iChanIndex = g_pMainDlg->GetCurChanIndex();
    if (iChanIndex < 0)
    {
        iChanIndex = 0;//default to config channel one
    }
    m_lDeviceIndex = iDeviceIndex;
    m_lUserID = g_struDeviceInfo[iDeviceIndex].lLoginID;
    m_lChannel= iChanIndex+g_struDeviceInfo[iDeviceIndex].iStartChan;
	m_lChanCount = g_struDeviceInfo[iDeviceIndex].iDeviceChanNum;
}

void CSubDlgITSCfg::OnBtnTs() 
{
	// TODO: Add your control notification handler code here
	CDlgTsSeries dlg;
	dlg.m_lLoginID = m_lUserID;	
	dlg.m_iDeviceIndex = m_lDeviceIndex;			
	dlg.m_lChannel = m_lChannel;
	dlg.DoModal();
}

void CSubDlgITSCfg::OnBtnItsIoinCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgITSIOinCfg dlg; 
    dlg.m_lUserID = m_lUserID;
    dlg.m_dwChannel = m_lChannel;
    dlg.m_iDevIndex = m_lDeviceIndex;
	dlg.DoModal();
}

void CSubDlgITSCfg::OnBtnItsConfig() 
{
	// TODO: Add your control notification handler code here
	CDlgITSConfig dlg;
	dlg.m_lServerID = m_lUserID;			
	dlg.m_iDevIndex = m_lDeviceIndex;			
	dlg.m_lChannel = m_lChannel;
	dlg.DoModal();	
}

void CSubDlgITSCfg::OnBtnItsMonitor() 
{
	// TODO: Add your control notification handler code here
    CDlgITSMonitor dlg;
    dlg.m_lServerID = m_lUserID;			
    dlg.m_iDevIndex = m_lDeviceIndex;			
    dlg.m_lChannel = m_lChannel;
	dlg.DoModal();	
}

void CSubDlgITSCfg::OnBtnItsMiniPost() 
{
	// TODO: Add your control notification handler code here
	CDlgITSMiniPost dlg;
    dlg.m_lServerID = m_lUserID;			
    dlg.m_iDevIndex = m_lDeviceIndex;			
    dlg.m_lChannel = m_lChannel;
	dlg.DoModal();
}

void CSubDlgITSCfg::OnBtnWifiServerCfg() 
{
	// TODO: Add your control notification handler code here
    CDlgWIFIServerCfg dlg;
    dlg.m_lChannel = m_lChannel;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_lDeviceIndex;
	dlg.DoModal();
}

void CSubDlgITSCfg::OnBtnMobileTriggerCfg() 
{
	// TODO: Add your control notification handler code here
    CDlgMobileTriggerCfg dlg;
    dlg.m_lChannel = m_lChannel;
    dlg.m_lServerID = m_lUserID;
    dlg.m_iDevIndex = m_lDeviceIndex;
	dlg.DoModal();
}

void CSubDlgITSCfg::OnBtnPostRadarCfg()
{
    CDlgPostRadarCfg dlg;
    dlg.m_lChannel = m_lChannel;
    dlg.m_lLoginID = m_lUserID;
    dlg.m_iDeviceIndex = m_lDeviceIndex;
    dlg.DoModal();
}

void CSubDlgITSCfg::OnBnClickedButtonUhfRfidReader()
{
     //TODO:  在此添加控件通知处理程序代码
    CDlgUHFRFIDReaderCfg dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_lDeviceIndex;
    dlg.DoModal();
}

