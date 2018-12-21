// DlgThermalDoubleSpectrum.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgThermalDoubleSpectrum.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgThermalDoubleSpectrum dialog


CDlgThermalDoubleSpectrum::CDlgThermalDoubleSpectrum(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgThermalDoubleSpectrum::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgThermalDoubleSpectrum)
	m_struStartTime = COleDateTime::GetCurrentTime();
	m_struStopTime = COleDateTime::GetCurrentTime();
	m_bZoomLinkageEnable = FALSE;
	m_byEnabled = FALSE;
	//}}AFX_DATA_INIT

	m_lChannel = -1;
    m_lUserID = -1;
    m_iDeviceIndex = -1;
    memset(&m_szStatusBuf, 0, ISAPI_STATUS_LEN);

}


void CDlgThermalDoubleSpectrum::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgThermalDoubleSpectrum)
	DDX_Control(pDX, IDC_COMBO_MODE, m_byMode);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_START, m_struStartTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_STOP, m_struStopTime);
	DDX_Check(pDX, IDC_CHECK_ZOOMLINKAGE_ENABLE, m_bZoomLinkageEnable);
	DDX_Check(pDX, IDC_CHECK_ENABLED, m_byEnabled);
	//}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMBO_CURRENT_LOCK, m_comboCurrentLock);
}


BEGIN_MESSAGE_MAP(CDlgThermalDoubleSpectrum, CDialog)
	//{{AFX_MSG_MAP(CDlgThermalDoubleSpectrum)
	ON_BN_CLICKED(IDC_BUTTON_SET_LOWPOWER, OnButtonSetLowpower)
	ON_BN_CLICKED(IDC_BUTTON_GET_LOWPOWER, OnButtonGetLowpower)
	ON_BN_CLICKED(IDC_BUTTON_SET_ZOOMLINKAGE, OnButtonSetZoomlinkage)
	ON_BN_CLICKED(IDC_BUTTON_GET_ZOOMLINKAGE, OnButtonGetZoomlinkage)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON_SET_CURRENT_LOCK, &CDlgThermalDoubleSpectrum::OnBnClickedButtonSetCurrentLock)
    ON_BN_CLICKED(IDC_BUTTON_GET_CURRENT_LOCK, &CDlgThermalDoubleSpectrum::OnBnClickedButtonGetCurrentLock)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgThermalDoubleSpectrum message handlers

void CDlgThermalDoubleSpectrum::OnButtonSetLowpower() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[512] = {0};
    NET_DVR_LOWPOWER struLowpower = {0};
    
    struLowpower.byMode = m_byMode.GetCurSel();
    struLowpower.byEnabled = m_byEnabled;
    
    struLowpower.struSchedTime.struStartTime.byHour = m_struStartTime.GetHour();
    struLowpower.struSchedTime.struStartTime.byMinute = m_struStartTime.GetMinute();
    struLowpower.struSchedTime.struStartTime.bySecond = m_struStartTime.GetSecond();
    
    struLowpower.struSchedTime.struStopTime.byHour = m_struStopTime.GetHour();
    struLowpower.struSchedTime.struStopTime.byMinute = m_struStopTime.GetMinute();
    struLowpower.struSchedTime.struStopTime.bySecond = m_struStopTime.GetSecond();
    
    struLowpower.dwSize = sizeof(struLowpower);
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struLowpower;
    struCfg.dwInSize = sizeof(struLowpower);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lUserID, NET_DVR_SET_LOWPOWER, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_LOWPOWER");
        sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_LOWPOWER");
    }
	
}

void CDlgThermalDoubleSpectrum::OnButtonGetLowpower() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_LOWPOWER struLowpower = {0};
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &struLowpower;
    struCfg.dwOutSize = sizeof(struLowpower);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_LOWPOWER, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_LOWPOWER");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_LOWPOWER");
    }
	
    m_byMode.SetCurSel(struLowpower.byMode);
	m_byEnabled = struLowpower.byEnabled;
    //开始时间
    m_struStartTime.SetTime(struLowpower.struSchedTime.struStartTime.byHour, \
        struLowpower.struSchedTime.struStartTime.byMinute, \
        struLowpower.struSchedTime.struStartTime.bySecond
        );
    
    //结束时间	
    m_struStopTime.SetTime(struLowpower.struSchedTime.struStopTime.byHour, \
        struLowpower.struSchedTime.struStopTime.byMinute, \
        struLowpower.struSchedTime.struStopTime.bySecond
		);
    UpdateData(FALSE);
}

void CDlgThermalDoubleSpectrum::OnButtonSetZoomlinkage() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[512] = {0};
    NET_DVR_ZOOMLINKAGE struZoomLinkage = {0};
    
    struZoomLinkage.byEnable = m_bZoomLinkageEnable;
		
	struZoomLinkage.dwSize = sizeof(struZoomLinkage);
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struZoomLinkage;
    struCfg.dwInSize = sizeof(struZoomLinkage);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lUserID, NET_DVR_SET_ZOOMLINKAGE, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_ZOOMLINKAGE");
        sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_ZOOMLINKAGE");
    }
}

void CDlgThermalDoubleSpectrum::OnButtonGetZoomlinkage() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_ZOOMLINKAGE struZoomLinkage = {0};
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &struZoomLinkage;
    struCfg.dwOutSize = sizeof(struZoomLinkage);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_ZOOMLINKAGE, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ZOOMLINKAGE");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ZOOMLINKAGE");
    }
	
	m_bZoomLinkageEnable = struZoomLinkage.byEnable;
    UpdateData(FALSE);
}



void CDlgThermalDoubleSpectrum::OnBnClickedButtonSetCurrentLock()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    char szLan[512] = { 0 };
    NET_DVR_CURRENT_LOCK struLock = { 0 };

    struLock.byCurrentLock = m_comboCurrentLock.GetCurSel() + 1;
    struLock.dwSize = sizeof(struLock);

    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struLock;
    struCfg.dwInSize = sizeof(struLock);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lUserID, NET_DVR_SET_CURRENT_LOCK, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_CURRENT_LOCK");
        sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_CURRENT_LOCK");
    }
}


void CDlgThermalDoubleSpectrum::OnBnClickedButtonGetCurrentLock()
{
    // TODO:  在此添加控件通知处理程序代码
    NET_DVR_CURRENT_LOCK struLock = { 0 };

    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &struLock;
    struCfg.dwOutSize = sizeof(struLock);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if (!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_CURRENT_LOCK, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_CURRENT_LOCK");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_CURRENT_LOCK");
    }

    m_comboCurrentLock.SetCurSel(struLock.byCurrentLock - 1);

    UpdateData(FALSE);
}
