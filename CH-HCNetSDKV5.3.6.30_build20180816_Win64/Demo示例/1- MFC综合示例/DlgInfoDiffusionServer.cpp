// DlgInfoDiffusionServer.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInfoDiffusionServer.h"
#include "DlgInfoDiffusionXmlCfg.h"
#include "DlgInfoDiffusionXmlUpdownload.h"
#include "DlgInfoDiffusionMaterial.h"
#include "DlgInfoDiffusionProgram.h"
#include "DlgInfoDiffusionSchedule.h"
#include "DlgInfoDiffusionTerminal.h"
#include "DlgInfoDiffusionTernimalPreview.h"
#include "DlgInfoDiffusionShutdown.h"
#include "DlgInfoDiffusionCapabilites.h"
#include "DlgInfoDiffusionVolum.h"
#include "DlgInfoXmlCfgWithUrl.h"
#include "DlgDyanmicPic.h"
#include "DlgInfoGerenal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionServer dialog


CDlgInfoDiffusionServer::CDlgInfoDiffusionServer(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInfoDiffusionServer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInfoDiffusionServer)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgInfoDiffusionServer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInfoDiffusionServer)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInfoDiffusionServer, CDialog)
	//{{AFX_MSG_MAP(CDlgInfoDiffusionServer)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_XML_CFG, OnBtnXmlCfg)
	ON_BN_CLICKED(IDC_BTN_UPDOWNLOAD, OnBtnUpdownload)
	ON_BN_CLICKED(IDC_BTN_MATERIAL_MANAGE, OnBtnMaterialManage)
	ON_BN_CLICKED(IDC_BTN_SCHEDULE_MANAGE, OnBtnScheduleManage)
	ON_BN_CLICKED(IDC_BTN_TERMINAL_MANAGE, OnBtnTerminalManage)
	ON_BN_CLICKED(IDC_BTN_CAPABILITES, OnBtnCapabilites)
	ON_BN_CLICKED(IDC_BTN_SHUTDOWN, OnBtnShutdown)
	ON_BN_CLICKED(IDC_BTN_PROGRAM_MANAGE, OnBtnProgramManage)
	ON_BN_CLICKED(IDC_BTN_VOLUME, OnBtnVolume)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_XML_TEST, &CDlgInfoDiffusionServer::OnBnClickedBtnXmlTest)
    ON_BN_CLICKED(IDC_BTN_PIC, &CDlgInfoDiffusionServer::OnBnClickedBtnPic)
    ON_BN_CLICKED(IDC_BTN_CALL, &CDlgInfoDiffusionServer::OnBnClickedBtnCall)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionServer message handlers

void CDlgInfoDiffusionServer::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CDlgInfoDiffusionServer::OnBtnXmlCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgInfoDiffusionXmlCfg dlg;
	dlg.DoModal();
}

void CDlgInfoDiffusionServer::OnBtnUpdownload() 
{
	// TODO: Add your control notification handler code here
	CDlgInfoDiffusionXmlUpdownload dlg;
	dlg.DoModal();
}

void CDlgInfoDiffusionServer::OnBtnMaterialManage() 
{
	// TODO: Add your control notification handler code here
	CDlgInfoDiffusionMaterial dlg;
	dlg.DoModal();
}

void CDlgInfoDiffusionServer::OnBtnProgramManage() 
{
	// TODO: Add your control notification handler code here
	CDlgInfoDiffusionProgram dlg;
	dlg.DoModal();
}

void CDlgInfoDiffusionServer::OnBtnScheduleManage() 
{
	// TODO: Add your control notification handler code here
	CDlgInfoDiffusionSchedule dlg;
	dlg.DoModal();
}

void CDlgInfoDiffusionServer::OnBtnTerminalManage() 
{
	// TODO: Add your control notification handler code here
	CDlgInfoDiffusionTerminal dlg;
	dlg.DoModal();
}

void CDlgInfoDiffusionServer::OnBtnCapabilites() 
{
	// TODO: Add your control notification handler code here
	CDlgInfoDiffusionCapabilites dlg;
	dlg.DoModal();
}

void CDlgInfoDiffusionServer::OnBtnShutdown() 
{
	// TODO: Add your control notification handler code here
	CDlgInfoDiffusionShutdown dlg;
	dlg.DoModal();
}

void CDlgInfoDiffusionServer::OnBtnVolume() 
{
	// TODO: Add your control notification handler code here
    CDlgInfoDiffusionVolum dlg;
	dlg.DoModal();
}


void CDlgInfoDiffusionServer::OnBnClickedBtnXmlTest()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgInfoXmlCfgWithUrl dlg;
    dlg.DoModal();
}


void CDlgInfoDiffusionServer::OnBnClickedBtnPic()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgDyanmicPic dlg;
    dlg.DoModal();
}


void CDlgInfoDiffusionServer::OnBnClickedBtnCall()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgInfoGerenal dlg;
    dlg.DoModal();
}
