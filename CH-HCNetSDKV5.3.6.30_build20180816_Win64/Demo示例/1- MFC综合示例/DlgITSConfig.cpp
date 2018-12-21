// DlgITSConfig.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgITSConfig.h"
#include "DlgITSUpload.h"
#include "DlgITSBaseInfo.h"
#include "DlgITSImageMergeCfg.h"
#include "DlgITSIpcCfg.h"
#include "DlgITSOverlapCfg.h"
#include "DlgITSWorkState.h"
#include "DlgITSRoadInfo.h"
#include "DlgITCAblity.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgITSConfig dialog


CDlgITSConfig::CDlgITSConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgITSConfig::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgITSConfig)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgITSConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgITSConfig)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgITSConfig, CDialog)
	//{{AFX_MSG_MAP(CDlgITSConfig)
	ON_BN_CLICKED(IDC_BTN_DATA_UPLOAD_CFG, OnBtnDataUploadCfg)
	ON_BN_CLICKED(IDC_BTN_GET_ITS_BASEINFO, OnBtnGetItsBaseinfo)
	ON_BN_CLICKED(IDC_BTN_ITS_IMGMERGE, OnBtnItsImgmerge)
	ON_BN_CLICKED(IDC_BTN_REUPLOAD_CFG, OnBtnReuploadCfg)
	ON_BN_CLICKED(IDC_BTN_ITS_IPC_CFG, OnBtnItsIpcCfg)
	ON_BN_CLICKED(IDC_BTN_ITS_OVERLAP_CFG, OnBtnItsOverlapCfg)
	ON_BN_CLICKED(IDC_BTN_ROAD_INFO_GET, OnBtnRoadInfoGet)
	ON_BN_CLICKED(IDC_BTN_DEVICE, OnBtnDevice)
	ON_BN_CLICKED(IDC_BTN_GETITC_ABLITY, OnBtnGetitcAblity)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgITSConfig message handlers

void CDlgITSConfig::OnBtnDataUploadCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgITSUpload dlg;
	dlg.m_lServerID = m_lServerID;			
	dlg.m_iDevIndex = m_iDevIndex;			
	dlg.m_lChannel = m_lChannel;
	dlg.DoModal();	
}

void CDlgITSConfig::OnBtnGetItsBaseinfo() 
{
	// TODO: Add your control notification handler code here
	CDlgITSBaseInfo dlg;
	dlg.m_lServerID = m_lServerID;			
	dlg.m_iDevIndex = m_iDevIndex;			
	dlg.m_lChannel = m_lChannel;
	dlg.DoModal();
}

void CDlgITSConfig::OnBtnItsImgmerge() 
{
	// TODO: Add your control notification handler code here
	CDlgITSImageMergeCfg dlg;
	dlg.m_lServerID = m_lServerID;			
	dlg.m_iDevIndex = m_iDevIndex;			
	dlg.m_lChannel = m_lChannel;
	dlg.DoModal();
}

void CDlgITSConfig::OnBtnReuploadCfg() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgITSConfig::OnBtnItsIpcCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgITSIpcCfg dlg;
	dlg.m_lServerID = m_lServerID;			
	dlg.m_iDevIndex = m_iDevIndex;			
	dlg.m_lChannel = m_lChannel;
	dlg.DoModal();
}

void CDlgITSConfig::OnBtnItsOverlapCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgITSOverlapCfg dlg;
	dlg.m_lServerID = m_lServerID;			
	dlg.m_iDevIndex = m_iDevIndex;			
	dlg.m_lChannel = m_lChannel;
	dlg.DoModal();
}

void CDlgITSConfig::OnBtnRoadInfoGet() 
{
	// TODO: Add your control notification handler code here
	CDlgITSRoadInfo dlg;
	dlg.m_lServerID = m_lServerID;			
	dlg.m_iDevIndex = m_iDevIndex;			
//	dlg.m_lChannel = m_lChannel;
	dlg.DoModal();
}

void CDlgITSConfig::OnBtnDevice() 
{
	// TODO: Add your control notification handler code here
	CDlgITSWorkState dlg;
	dlg.m_lLoginID = m_lServerID;			
	dlg.m_iDeviceIndex = m_iDevIndex;			
	dlg.DoModal();
}

void CDlgITSConfig::OnBtnGetitcAblity() 
{
	// TODO: Add your control notification handler code here
	CDlgITCAblity dlg;
	dlg.m_lServerID = m_lServerID;			
	dlg.m_iDeviceIndex = m_iDevIndex;			
	dlg.DoModal();
}
