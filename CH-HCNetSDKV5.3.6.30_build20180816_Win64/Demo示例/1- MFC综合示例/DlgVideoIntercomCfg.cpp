// DlgVideoIntercomCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVideoIntercomCfg.h"
#include "DlgVideoIntercomDeviceIDCfg.h"
#include "DlgVideoIntercomPrivilegePwdCfg.h"
#include "DlgVideoIntercomOpTimeCfg.h"
#include "DlgVideoIntercomRelateDevCfg.h"
#include "DlgVideoIntercomNoticeDataCfg.h"
#include "DlgTransConfig.h"
#include "DlgVideoIntercomGateway.h"
#include "DlgGatewayCardCfg.h"
#include "DlgVideoIntercomIOInCfg.h"
#include "DlgVideoIntercomIOOutCfg.h"
#include "DlgVideoIntercomElevatorCfg.h"
#include "DlgVideoIntercomStreamCfg.h"
#include "DlgDoorConfig.h"
#include "DlgAlarmHostRs485.h"
#include "DlgVISRegisterInfo.h"
#include "DlgVISDevInfo.h"
#include "DlgVideoIntercomAuthCfg.h"
#include "DlgWDRCfg.h"
#include "DlgAudioInVolumeCfg.h"
#include "DlgAudioOutVolumeCfg.h"
#include "DlgVideoIntercomCallRoomCfg.h"
#include "DlgVideoIntercomCall.h"
#include "DlgVideoIntercomAlarmCfg.h"
#include "DlgBellFileCfg.h"
#include "DlgAcsXmlDiffusion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomCfg dialog


CDlgVideoIntercomCfg::CDlgVideoIntercomCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVideoIntercomCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVideoIntercomCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lServerID = -1;
	m_iDevIndex = -1;
}


void CDlgVideoIntercomCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVideoIntercomCfg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVideoIntercomCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVideoIntercomCfg)
	ON_BN_CLICKED(IDC_BTN_DEVICEID_CFG, OnBtnDeviceidCfg)
	ON_BN_CLICKED(IDC_BTN_PRIVILEGE_PWD_CFG, OnBtnPrivilegePwdCfg)
	ON_BN_CLICKED(IDC_BTN_RELATEDEVICE, OnBtnRelatedevice)
	ON_BN_CLICKED(IDC_BTN_NOTICE_DATA, OnBtnNoticeData)
	ON_BN_CLICKED(IDC_BTN_OPERATION_TIME_CFG, OnBtnOperationTimeCfg)
	ON_BN_CLICKED(IDC_BTN_STREAM_SRC_INFO, OnBtnStreamSrcInfo)
	ON_BN_CLICKED(IDC_BTN_GATEWAY, OnBtnGateway)
	ON_BN_CLICKED(IDC_BTN_GATEWAY_CARD, OnBtnGatewayCard)
	ON_BN_CLICKED(IDC_BTN_IOIN_CFG, OnBtnIoinCfg)
	ON_BN_CLICKED(IDC_BTN_IOOUT_CFG, OnBtnIooutCfg)
	ON_BN_CLICKED(IDC_BTN_ELEVATOR_CONTROL_CFG, OnBtnElevatorControlCfg)
	ON_BN_CLICKED(IDC_BTN_STREAM_CFG, OnBtnStreamCfg)
	ON_BN_CLICKED(IDC_BUT_AC_DOORCONFIG, OnButAcDoorconfig)
	ON_BN_CLICKED(IDC_BTN_RS485, OnBtnRs485)
	ON_BN_CLICKED(IDC_BTN_GET_DEVINFO, OnBtnGetDevinfo)
	ON_BN_CLICKED(IDC_BTN_GET_REGISTER, OnBtnGetRegister)
	ON_BN_CLICKED(IDC_BTN_WDR, OnBtnWdr)
	ON_BN_CLICKED(IDC_BTN_AUTH, OnBtnAuth)
	ON_BN_CLICKED(IDC_BTN_AUDIOIN_VOLUME, OnBtnAudioinVolume)
	ON_BN_CLICKED(IDC_BTN_AUDIOOUT_VOLUME, OnBtnAudiooutVolume)
	ON_BN_CLICKED(IDC_BTN_ROOM_CALL_CFG, OnBtnRoomCallCfg)
	ON_BN_CLICKED(IDC_BTN_VIDEO_CALL, OnBtnVideoCall)
	ON_BN_CLICKED(IDC_BUTTON_ALARM_CFG, OnButtonAlarmCfg)
	ON_BN_CLICKED(IDC_BUTTON_BELLFILE_CFG, OnButtonBellfileCfg)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_ROOM_CUSTOM_CFG, &CDlgVideoIntercomCfg::OnBnClickedBtnRoomCustomCfg)
    ON_BN_CLICKED(IDC_BTN_NOTICE_VIDEO_DATA, &CDlgVideoIntercomCfg::OnBnClickedBtnNoticeVideoData)
    ON_BN_CLICKED(IDC_BTN_XML_CFG, &CDlgVideoIntercomCfg::OnBnClickedBtnXmlCfg)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomCfg message handlers

void CDlgVideoIntercomCfg::OnBtnDeviceidCfg() 
{
	CDlgVideoIntercomDeviceIDCfg dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
	
}

void CDlgVideoIntercomCfg::OnBtnPrivilegePwdCfg() 
{
	CDlgVideoIntercomPrivilegePwdCfg dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
	
}

void CDlgVideoIntercomCfg::OnBtnRelatedevice() 
{
	CDlgVideoIntercomRelateDevCfg dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CDlgVideoIntercomCfg::OnBtnNoticeData() 
{
	CDlgVideoIntercomNoticeDataCfg dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CDlgVideoIntercomCfg::OnBtnOperationTimeCfg() 
{
	CDlgVideoIntercomOpTimeCfg dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CDlgVideoIntercomCfg::OnBtnStreamSrcInfo() 
{
    CDlgTransConfig dlg;
    dlg.m_lUserID = m_lServerID;
	dlg.DoModal();	
}

void CDlgVideoIntercomCfg::OnBtnGateway() 
{
	CDlgVideoIntercomGateway dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
	
}

void CDlgVideoIntercomCfg::OnBtnGatewayCard() 
{
	CDlgGatewayCardCfg dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CDlgVideoIntercomCfg::OnBtnIoinCfg() 
{
	// TODO: Add your control notification handler code here
	DlgVideoIntercomIOInCfg dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CDlgVideoIntercomCfg::OnBtnIooutCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgVideoIntercomIOOutCfg dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CDlgVideoIntercomCfg::OnBtnElevatorControlCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgVideoIntercomElevatorCfg dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CDlgVideoIntercomCfg::OnBtnStreamCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgVideoIntercomStreamCfg dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CDlgVideoIntercomCfg::OnButAcDoorconfig() 
{
	// TODO: Add your control notification handler code here
	CDlgDoorConfig dlg; 
	dlg.m_lUserID = m_lServerID;
	dlg.m_lDeviceID = m_iDevIndex;
    dlg.DoModal(); 
}

void CDlgVideoIntercomCfg::OnBtnRs485() 
{
	// TODO: Add your control notification handler code here
	CDlgAlarmHostRs485 dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    memset(&dlg.m_struDevAbility, 0, sizeof(dlg.m_struDevAbility)); 
	//    memcpy(&dlg.m_struDevAbility, &m_struAlarmHostAbility, sizeof(m_struAlarmHostAbility));
    dlg.m_i485SlotNum = 0; 
    dlg.m_iRS485Num = 4;
    dlg.DoModal();
}

void CDlgVideoIntercomCfg::OnBtnGetDevinfo() 
{
	// TODO: Add your control notification handler code here
	CDlgVISDevInfo dlg;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lUserID = m_lServerID;
    dlg.DoModal();
}

void CDlgVideoIntercomCfg::OnBtnGetRegister() 
{
	// TODO: Add your control notification handler code here
    CDlgVISRegisterInfo dlg;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lUserID = m_lServerID;
    dlg.DoModal();
}

void CDlgVideoIntercomCfg::OnBtnWdr() 
{
	// TODO: Add your control notification handler code here
    CDlgWDRCfg dlg;
    dlg.m_lUserID=  m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVideoIntercomCfg::OnBtnAuth() 
{
	// TODO: Add your control notification handler code here
    CDlgVideoIntercomAuthCfg dlg;
    dlg.m_lUserID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVideoIntercomCfg::OnBtnAudioinVolume() 
{
	// TODO: Add your control notification handler code here
	CDlgAudioInVolumeCfg dlg;
    dlg.m_lUserID = m_lServerID;
    dlg.m_dwDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVideoIntercomCfg::OnBtnAudiooutVolume() 
{
	// TODO: Add your control notification handler code here
    CDlgAudioOutVolumeCfg dlg;
    dlg.m_lUserID = m_lServerID;
    dlg.m_dwDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVideoIntercomCfg::OnBtnRoomCallCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgVideoIntercomCallRoomCfg dlg;
    dlg.m_lUserID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVideoIntercomCfg::OnBtnVideoCall() 
{
	// TODO: Add your control notification handler code here
	CDlgVideoIntercomCall dlg;
    dlg.m_lUserID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_byRequestType = 0;
    dlg.DoModal();
}

void CDlgVideoIntercomCfg::CurCfgUpadate()
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
	
    m_iDevIndex = iDeviceIndex;
    m_lServerID = g_struDeviceInfo[iDeviceIndex].lLoginID;
}


void CDlgVideoIntercomCfg::OnButtonAlarmCfg() 
{
	// TODO: Add your control notification handler code here
    DlgVideoIntercomAlarmCfg dlg;
    dlg.m_lUserID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVideoIntercomCfg::OnButtonBellfileCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgBellFileCfg dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

#include "DlgVideoIntercomRoomCustomCfg.h"
void CDlgVideoIntercomCfg::OnBnClickedBtnRoomCustomCfg()
{
    // TODO:  在此添加控件通知处理程序代码
    // TODO:  在此添加控件通知处理程序代码
    CDlgVideoIntercomRoomCustomCfg dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

#include "DlgVideoIntercomNoticeVideoDataCfg.h"
void CDlgVideoIntercomCfg::OnBnClickedBtnNoticeVideoData()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgVideoIntercomNoticeVideoDataCfg dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}


void CDlgVideoIntercomCfg::OnBnClickedBtnXmlCfg()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAcsXmlDiffusion dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}
