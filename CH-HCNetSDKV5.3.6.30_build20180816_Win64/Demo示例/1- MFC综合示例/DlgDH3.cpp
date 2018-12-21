// DlgDH3.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgDH3.h"
#include "DlgGetAllPointCfg.h"
#include "DlgGetAllSensor.h"
#include "DlgGetAllRs485Cfg.h"
#include "DlgGetAllRs485Slot.h"
#include "DlgDeviceSelfCheckState.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgDH3 dialog


DlgDH3::DlgDH3(CWnd* pParent /*=NULL*/)
	: CDialog(DlgDH3::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgDH3)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgDH3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgDH3)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgDH3, CDialog)
	//{{AFX_MSG_MAP(DlgDH3)
	ON_BN_CLICKED(IDC_BTN_GET_ALL_POINT, OnBtnGetAllPoint)
	ON_BN_CLICKED(IDC_BTN_GET_ALL_SENSOR, OnBtnGetAllSensor)
	ON_BN_CLICKED(IDC_BTN_GET_ALL_RS485_CFG, OnBtnGetAllRs485Cfg)
	ON_BN_CLICKED(IDC_BTN_GET_ALL_RS485_SLOT_CFG, OnBtnGetAllRs485SlotCfg)
	ON_BN_CLICKED(IDC_BTN_GET_DEVICE_STATE, OnBtnGetDeviceState)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgDH3 message handlers

void DlgDH3::OnBtnGetAllPoint() 
{
	// TODO: Add your control notification handler code here
	DlgGetAllPointCfg dlg;
	dlg.DoModal();
}

void DlgDH3::OnBtnGetAllSensor() 
{
	// TODO: Add your control notification handler code here
	DlgGetAllSensor dlg;
	dlg.DoModal();
}

void DlgDH3::OnBtnGetAllRs485Cfg() 
{
	// TODO: Add your control notification handler code here
	DlgGetAllRs485Cfg dlg;
	dlg.DoModal();
}

void DlgDH3::OnBtnGetAllRs485SlotCfg() 
{
	// TODO: Add your control notification handler code here
	DlgGetAllRs485Slot dlg;
	dlg.DoModal();
}

void DlgDH3::OnBtnGetDeviceState() 
{
	// TODO: Add your control notification handler code here
	DlgDeviceSelfCheckState dlg;
	dlg.DoModal();
}
