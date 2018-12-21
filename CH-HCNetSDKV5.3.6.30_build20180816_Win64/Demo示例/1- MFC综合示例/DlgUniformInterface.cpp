// DlgUniformInterface.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgUniformInterface.h"
#include "DLGCreateWall.h"
#include "DlgSenceControlUniform.h"
#include "DlgWallPreview.h"
#include "DlgScreenLogoCfgUniform.h"
#include "DlgWallBasemapWin.h"
#include "DlgDecWinStatusUniform.h"
#include "DlgVideoWallElse.h"
#include "DlgGBT28181ProAccessUniform.h"
#include "DlgAudioChanCfg.h"










#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgUniformInterface dialog


CDlgUniformInterface::CDlgUniformInterface(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUniformInterface::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgUniformInterface)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgUniformInterface::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgUniformInterface)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgUniformInterface, CDialog)
	//{{AFX_MSG_MAP(CDlgUniformInterface)
	ON_BN_CLICKED(IDC_BTN_VIDEOWALL_CREATEWALL, OnBtnVideowallCreatewall)
	ON_BN_CLICKED(IDC_BTN_SENCE, OnBtnSence)
	ON_BN_CLICKED(IDC_BTN_PIC_PREVIEW, OnBtnPicPreview)
	ON_BN_CLICKED(IDC_BTN_PIC, OnBtnPic)
	ON_BN_CLICKED(IDC_BTN_BASEMAP, OnBtnBasemap)
	ON_BN_CLICKED(IDC_BTN_WALL_WIN_STATUS, OnBtnWallWinStatus)
	ON_BN_CLICKED(IDC_BUT_VIDEOWALL_ELSE, OnButVideowallElse)
	ON_BN_CLICKED(IDC_BUT_VM_AUDIOCFG, OnButVmAudiocfg)
	ON_BN_CLICKED(IDC_BUT_VM_GBT28181, OnButVmGbt28181)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgUniformInterface message handlers

void CDlgUniformInterface::OnBtnVideowallCreatewall() 
{
	// TODO: Add your control notification handler code here
	CDLGCreateWall dlg; 
    dlg.m_lUserID = m_lServerID; 
    dlg.m_iDeviceIndex = m_iDeviceIndex; 
    dlg.DoModal(); 
}

void CDlgUniformInterface::OnBtnSence() 
{
	// TODO: Add your control notification handler code here
	CDlgSenceControlUniform dlg;
	dlg.m_lUserID = m_lServerID;
    dlg.m_iDeviceIndex = m_iDeviceIndex; 
	dlg.DoModal();
}
void CDlgUniformInterface::OnBtnPicPreview() 
{
	// TODO: Add your control notification handler code here
	CDlgWallPreview dlg;
	dlg.m_lUserID = m_lServerID;
    dlg.m_iDeviceIndex = m_iDeviceIndex; 
 	dlg.DoModal();
}
void CDlgUniformInterface::OnBtnPic() 
{
	// TODO: Add your control notification handler code here
	CDlgScreenLogoCfgUniform dlg;
	dlg.DoModal();
}

void CDlgUniformInterface::OnBtnBasemap() 
{
	// TODO: Add your control notification handler code here
	CDlgWallBasemapWin dlg;
    dlg.m_lUserID = m_lServerID;
	dlg.DoModal();
}
void CDlgUniformInterface::OnBtnWallWinStatus() 
{
	// TODO: Add your control notification handler code here
	CDlgDecWinStatusUniform dlg;
	dlg.m_lUserID = m_lServerID;
	dlg.DoModal();
}

void CDlgUniformInterface::OnButVideowallElse() 
{
	// TODO: Add your control notification handler code here
	CDlgVideoWallElse dlg; 
    dlg.m_lUserID = m_lServerID;
    dlg.m_iDeviceIndex = m_iDeviceIndex; 
	dlg.DoModal();	
}

void CDlgUniformInterface::OnButVmAudiocfg() 
{
	// TODO: Add your control notification handler code here
	CDlgAudioChanCfg dlg; 
	dlg.DoModal(); 
}


void CDlgUniformInterface::OnButVmGbt28181() 
{
	// TODO: Add your control notification handler code here
	CDlgGBT28181ProAccessUniform dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_dwDevIndex = m_iDeviceIndex;
    dlg.m_dwAlarmOutNum = g_struDeviceInfo[m_iDeviceIndex].iAlarmOutNum;
    dlg.m_nChannel = g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum;
    dlg.m_lStartChan = g_struDeviceInfo[m_iDeviceIndex].iStartChan;
    dlg.m_dwAlarmInNum = g_struDeviceInfo[m_iDeviceIndex].iAlarmInNum;
	dlg.DoModal();
}

BOOL CDlgUniformInterface::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex(); 
	m_lServerID = g_struDeviceInfo[m_iDeviceIndex].lLoginID; 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
