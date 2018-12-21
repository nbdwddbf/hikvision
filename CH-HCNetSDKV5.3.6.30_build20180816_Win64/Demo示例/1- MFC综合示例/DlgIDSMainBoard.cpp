// DlgIDSMainBoard.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgIDSMainBoard.h"
#include "DlgKeyboardCfg.h"
#include "DlgAlarmCenterServerCfg.h"
#include "DlgDelayPreviewCfg.h"
#include "DlgZoneLinkageChanCfg.h"
#include "DlgAlarmPicCfg.h"
#include "DlgWhiteList.h"
#include "DlgSystemTimeAlarm.h"
#include "DlgAlarmHostGetAllModule.h"
#include "DlgWirelessBusinessSearch.h"
#include "DlgRemoteControllerManage.h"
#include "DlgRemoteControllerCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIDSMainBoard dialog


CDlgIDSMainBoard::CDlgIDSMainBoard(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIDSMainBoard::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgIDSMainBoard)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgIDSMainBoard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIDSMainBoard)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIDSMainBoard, CDialog)
	//{{AFX_MSG_MAP(CDlgIDSMainBoard)
	ON_BN_CLICKED(IDC_BTN_GET_ALL_MODULE, OnBtnGerAllModule)
	ON_BN_CLICKED(IDC_BTN_SUB_SYSTEM_ALARM, OnBtnSubSystemAlarm)
	ON_BN_CLICKED(IDC_BTN_WHITE_LIST_CFG, OnBtnWhiteListCfg)
	ON_BN_CLICKED(IDC_BTN_WIRELESS_BUSINNESS_SEARCH, OnBtnWirelessBusinnessSearch)
	ON_BN_CLICKED(IDC_BTN_GET_ALL_REMOTE_CONTROLLER, OnBtnGetAllRemoteController)
	ON_BN_CLICKED(IDC_BTN_REMOTE_CONTROLLER_CFG, OnBtnRemoteControllerCfg)
	ON_BN_CLICKED(IDC_BTN_KEYBORAD_CFG, OnBtnKeyboradCfg)
	ON_BN_CLICKED(IDC_BTN_ALARM_CAPTRUE_CFG, OnBtnAlarmCaptrueCfg)
	ON_BN_CLICKED(IDC_BTN_CENTER_SVR_CFG, OnBtnCenterSvrCfg)
	ON_BN_CLICKED(IDC_BTN_LINKAGE_CHAN, OnBtnLinkageChan)
	ON_BN_CLICKED(IDC_BTN_DELAY_PREVIEW_CFG, OnBnClickedBtnDelayPreviewCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgIDSMainBoard message handlers



void CDlgIDSMainBoard::OnBtnWirelessBusinnessSearch() 
{
	// TODO: Add your control notification handler code here
	CDlgWirelessBusinessSearch dlg;
	
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    if (iDeviceIndex < 0)
    {
        return;
    }
	
    int iChanIndex = g_pMainDlg->GetCurChanIndex();
    if (iChanIndex < 0)
    {
        iChanIndex = 0;//default to config channel one
    }
    dlg.m_iDevIndex = iDeviceIndex;
    dlg.m_lUserID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	
	dlg.DoModal();
}


void CDlgIDSMainBoard::OnBtnGetAllRemoteController() 
{
	// TODO: Add your control notification handler code here
	CDlgRemoteControllerManage dlg;
	dlg.DoModal();
}


void CDlgIDSMainBoard::OnBtnRemoteControllerCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgRemoteControllerCfg dlg;
	
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    if (iDeviceIndex < 0)
    {
        return;
    }
	
    int iChanIndex = g_pMainDlg->GetCurChanIndex();
    if (iChanIndex < 0)
    {
        iChanIndex = 0;//default to config channel one
    }
    dlg.m_iDeviceIndex = iDeviceIndex;
    dlg.m_lUserID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	
	dlg.DoModal();
}


void CDlgIDSMainBoard::OnBtnGerAllModule()
{
	DlgAlarmHostGetAllModule dlg;

	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    if (iDeviceIndex < 0)
    {
        return;
    }
    dlg.m_iDevIndex = iDeviceIndex;
    dlg.m_lServerID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	
	dlg.DoModal();
}


void CDlgIDSMainBoard::OnBtnSubSystemAlarm()
{
	DlgSystemTimeAlarm dlg;

	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    if (iDeviceIndex < 0)
    {
        return;
    }
    dlg.m_iDevIndex = iDeviceIndex;
    dlg.m_lServerID = g_struDeviceInfo[iDeviceIndex].lLoginID;

	dlg.DoModal();
}


void CDlgIDSMainBoard::OnBtnWhiteListCfg()
{
	DlgWhiteList dlg;

	dlg.DoModal();
}


void CDlgIDSMainBoard::OnBtnKeyboradCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgKeyboardCfg dlg;

	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    if (iDeviceIndex < 0)
    {
        return;
    }
	
    int iChanIndex = g_pMainDlg->GetCurChanIndex();
    if (iChanIndex < 0)
    {
        iChanIndex = 0;//default to config channel one
    }
    dlg.m_iDeviceIndex = iDeviceIndex;
    dlg.m_lUserID = g_struDeviceInfo[iDeviceIndex].lLoginID;

	dlg.DoModal();
}


void CDlgIDSMainBoard::OnBtnAlarmCaptrueCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgAlarmPicCfg dlg;
	dlg.DoModal();
}


void CDlgIDSMainBoard::OnBtnLinkageChan() 
{
	// TODO: Add your control notification handler code here
	CDlgZoneLinkageChanCfg dlg;
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    if (iDeviceIndex < 0)
    {
        return;
    }
	dlg.m_lUserID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	dlg.m_iDeviceIndex = iDeviceIndex;
	dlg.DoModal();
}


void CDlgIDSMainBoard::OnBtnCenterSvrCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgAlarmCenterServerCfg dlg;
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    if (iDeviceIndex < 0)
    {
        return;
    }
	dlg.m_lUserID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	dlg.m_iDeviceIndex = iDeviceIndex;
	dlg.DoModal();
	
}



void CDlgIDSMainBoard::OnBnClickedBtnDelayPreviewCfg()
{
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    if (iDeviceIndex < 0)
    {
        return;
    }  
    int iChanIndex = g_pMainDlg->GetCurChanIndex();
    if (iChanIndex < 0)
    {
        iChanIndex = 0;
    }
	
	CDlgDelayPreviewCfg dlg;
	dlg.m_lUserID = g_struDeviceInfo[iDeviceIndex].lLoginID;
    dlg.m_lChannel = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iChanIndex].iChannelNO;//iChanIndex + g_struDeviceInfo[iDeviceIndex].iStartChan;
    dlg.m_iDeviceIndex = iDeviceIndex;
	
	dlg.DoModal();
}