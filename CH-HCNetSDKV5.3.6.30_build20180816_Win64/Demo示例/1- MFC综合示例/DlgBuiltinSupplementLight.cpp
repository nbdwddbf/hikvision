// DlgBuiltinSupplementLight.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgBuiltinSupplementLight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBuiltinSupplementLight dialog


CDlgBuiltinSupplementLight::CDlgBuiltinSupplementLight(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBuiltinSupplementLight::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBuiltinSupplementLight)
	m_iBLimit = 0;
	m_TimeStart = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT

    memset(&m_struBuiltinSupplementLight, 0, sizeof(m_struBuiltinSupplementLight));
    m_lServerID = -1;
    m_iDeviceIndex = -1;
    m_lChannel = -1;
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
}


void CDlgBuiltinSupplementLight::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBuiltinSupplementLight)
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_STOP, m_TimeStop);
	DDX_Control(pDX, IDC_COMBO_MODE, m_comboMode);
	DDX_Text(pDX, IDC_EDIT_BLimit, m_iBLimit);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_START, m_TimeStart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBuiltinSupplementLight, CDialog)
	//{{AFX_MSG_MAP(CDlgBuiltinSupplementLight)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBuiltinSupplementLight message handlers

void CDlgBuiltinSupplementLight::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    m_struBuiltinSupplementLight.dwSize = sizeof(m_struBuiltinSupplementLight);
    m_struBuiltinSupplementLight.byBrightnessLimit = m_iBLimit;
    m_struBuiltinSupplementLight.byMode = m_comboMode.GetCurSel();
    m_struBuiltinSupplementLight.struSchedTime.struStartTime.byHour = m_TimeStart.GetHour();
    m_struBuiltinSupplementLight.struSchedTime.struStartTime.byMinute = m_TimeStart.GetMinute();
    m_struBuiltinSupplementLight.struSchedTime.struStartTime.bySecond = m_TimeStart.GetSecond();

    m_struBuiltinSupplementLight.struSchedTime.struStopTime.byHour = m_TimeStop.GetHour();
    m_struBuiltinSupplementLight.struSchedTime.struStopTime.byMinute = m_TimeStop.GetMinute();
    m_struBuiltinSupplementLight.struSchedTime.struStopTime.bySecond = m_TimeStop.GetSecond();

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &m_struBuiltinSupplementLight;
    struCfg.dwInSize = sizeof(m_struBuiltinSupplementLight);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_SUPPLEMENTLIGHT, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SUPPLEMENTLIGHT");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_SUPPLEMENTLIGHT");
        OutputDebugString(m_szStatusBuf);   
    }
}

void CDlgBuiltinSupplementLight::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &m_struBuiltinSupplementLight;
    struCfg.dwOutSize = sizeof(m_struBuiltinSupplementLight);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_SUPPLEMENTLIGHT, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SUPPLEMENTLIGHT");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SUPPLEMENTLIGHT");
        
    }

    //开始时间
    m_TimeStart.SetTime(m_struBuiltinSupplementLight.struSchedTime.struStartTime.byHour, \
        m_struBuiltinSupplementLight.struSchedTime.struStartTime.byMinute, \
        m_struBuiltinSupplementLight.struSchedTime.struStartTime.bySecond
        );
    
    //结束时间	
    m_TimeStop.SetTime(m_struBuiltinSupplementLight.struSchedTime.struStopTime.byHour, \
        m_struBuiltinSupplementLight.struSchedTime.struStopTime.byMinute, \
        m_struBuiltinSupplementLight.struSchedTime.struStopTime.bySecond
		);

    m_iBLimit = m_struBuiltinSupplementLight.byBrightnessLimit;
    m_comboMode.SetCurSel(m_struBuiltinSupplementLight.byMode);

    UpdateData(FALSE);
}
