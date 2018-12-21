// DlgExternalDev.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgExternalDev.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgExternalDev dialog


DlgExternalDev::DlgExternalDev(CWnd* pParent /*=NULL*/)
	: CDialog(DlgExternalDev::IDD, pParent)
    , m_bySensitivity(0)
    , m_byBrightness(0)
{
	//{{AFX_DATA_INIT(DlgExternalDev)
	m_byEnable = FALSE;
	m_struStartTime = COleDateTime::GetCurrentTime();
	m_struStopTime = COleDateTime::GetCurrentTime();
	m_HighBeamBrightness = 0;
	m_LowBeamBrightness = 0;
    m_dwFilteringTime = 0;
	//}}AFX_DATA_INIT
}


void DlgExternalDev::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(DlgExternalDev)
    DDX_Control(pDX, IDC_COMBO_MODE, m_byMode);
    DDX_Check(pDX, IDC_CHECK_ENABLE, m_byEnable);
    DDX_DateTimeCtrl(pDX, IDC_DATETIME_START, m_struStartTime);
    DDX_DateTimeCtrl(pDX, IDC_DATETIME_STOP, m_struStopTime);
    DDX_Text(pDX, IDC_EDIT_HIGH_BEAM_BRN, m_HighBeamBrightness);
    DDX_Text(pDX, IDC_EDIT_LOW_BEAM_BRN, m_LowBeamBrightness);
    DDX_Text(pDX, IDC_EDIT_FILTERING_TIME, m_dwFilteringTime);

    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_sensitivity, m_bySensitivity);
    DDX_Text(pDX, IDC_EDIT_BRIGHTNESS, m_byBrightness);

    DDX_Control(pDX, IDC_COMBO_BRT_REGULATE_MODE, m_bBrightnessRegulatMode);
}


BEGIN_MESSAGE_MAP(DlgExternalDev, CDialog)
	//{{AFX_MSG_MAP(DlgExternalDev)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgExternalDev message handlers
BOOL DlgExternalDev::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgExternalDev::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char szLan[512] = {0};
    NET_DVR_EXTERNALDEVICE struExternalDevice = {0};
    
    struExternalDevice.struSupplementLight.byEnable = m_byEnable;
    struExternalDevice.struSupplementLight.byMode = m_byMode.GetCurSel();
    struExternalDevice.struSupplementLight.byHighBeamBrightness = m_HighBeamBrightness;
    struExternalDevice.struSupplementLight.byLowBeamBrightness = m_LowBeamBrightness;
    
    struExternalDevice.struSupplementLight.struSchedTime.struStartTime.byHour = m_struStartTime.GetHour();
    struExternalDevice.struSupplementLight.struSchedTime.struStartTime.byMinute = m_struStartTime.GetMinute();
    struExternalDevice.struSupplementLight.struSchedTime.struStartTime.bySecond = m_struStartTime.GetSecond();
    
    struExternalDevice.struSupplementLight.struSchedTime.struStopTime.byHour = m_struStopTime.GetHour();
    struExternalDevice.struSupplementLight.struSchedTime.struStopTime.byMinute = m_struStopTime.GetMinute();
    struExternalDevice.struSupplementLight.struSchedTime.struStopTime.bySecond = m_struStopTime.GetSecond();
    
    struExternalDevice.struSupplementLight.wFilteringTime = m_dwFilteringTime;
    struExternalDevice.struSupplementLight.byBrightness = m_byBrightness;
    struExternalDevice.struSupplementLight.bySensitivity = m_bySensitivity;
    struExternalDevice.struSupplementLight.byBrightnessRegulatMode = m_bBrightnessRegulatMode.GetCurSel();

    struExternalDevice.dwSize = sizeof(struExternalDevice);
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = NULL;
    struCfg.dwCondSize = 0;
    struCfg.lpInBuffer = &struExternalDevice;
    struCfg.dwInSize = sizeof(struExternalDevice);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lUserID, NET_DVR_SET_EXTERNALDEVICE, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_EXTERNALDEVICE");
        sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_EXTERNALDEVICE");
    }
	
}

void DlgExternalDev::OnButtonGet() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_EXTERNALDEVICE struExternalDevice = {0};
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = NULL;
    struCfg.dwCondSize = 0;
    struCfg.lpOutBuffer = &struExternalDevice;
    struCfg.dwOutSize = sizeof(struExternalDevice);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_EXTERNALDEVICE, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_EXTERNALDEVICE");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_EXTERNALDEVICE");
    }

    m_byEnable = struExternalDevice.struSupplementLight.byEnable;
    m_byMode.SetCurSel(struExternalDevice.struSupplementLight.byMode);
    m_HighBeamBrightness = struExternalDevice.struSupplementLight.byHighBeamBrightness;
    m_LowBeamBrightness = struExternalDevice.struSupplementLight.byLowBeamBrightness;
    m_byBrightness = struExternalDevice.struSupplementLight.byBrightness;
    m_bySensitivity = struExternalDevice.struSupplementLight.bySensitivity;
    m_bBrightnessRegulatMode.SetCurSel(struExternalDevice.struSupplementLight.byBrightnessRegulatMode);

    //开始时间
    m_struStartTime.SetTime(struExternalDevice.struSupplementLight.struSchedTime.struStartTime.byHour, \
        struExternalDevice.struSupplementLight.struSchedTime.struStartTime.byMinute, \
        struExternalDevice.struSupplementLight.struSchedTime.struStartTime.bySecond
        );
    
    //结束时间	
    m_struStopTime.SetTime(struExternalDevice.struSupplementLight.struSchedTime.struStopTime.byHour, \
        struExternalDevice.struSupplementLight.struSchedTime.struStopTime.byMinute, \
        struExternalDevice.struSupplementLight.struSchedTime.struStopTime.bySecond
		);

    m_dwFilteringTime = struExternalDevice.struSupplementLight.wFilteringTime;


    UpdateData(FALSE);
	
}
