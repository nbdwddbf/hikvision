// DlgBatteryPower.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgBatteryPower.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgBatteryPower dialog


DlgBatteryPower::DlgBatteryPower(CWnd* pParent /*=NULL*/)
	: CDialog(DlgBatteryPower::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgBatteryPower)
	m_byBatteryPower = FALSE;
	m_fX = 0.0f;
	m_fY = 0.0f;
	//}}AFX_DATA_INIT
}


void DlgBatteryPower::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgBatteryPower)
	DDX_Check(pDX, IDC_CHECK_BATTERY_POWER, m_byBatteryPower);
    DDX_Control(pDX, IDC_COMBO_CHANNEL, m_comChannel);
	DDX_Text(pDX, IDC_EDIT_BATTERY_POWER_X, m_fX);
	DDX_Text(pDX, IDC_EDIT_BATTERY_POWER_Y, m_fY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgBatteryPower, CDialog)
	//{{AFX_MSG_MAP(DlgBatteryPower)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgBatteryPower message handlers

BOOL DlgBatteryPower::OnInitDialog()
{
    CDialog::OnInitDialog();
    
    CString csStr;
    char szLan[128] = {0};

    for (int i=0; i<512; i++)
    {
        g_StringLanType(szLan, "", "");
        csStr.Format("%s%d", szLan, i);
        m_comChannel.InsertString(i, csStr);
	}
    
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgBatteryPower::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char szLan[512] = {0};
    NET_DVR_OSD_BATTERY_POWER_CFG struBatteryPower = {0};
    
    struBatteryPower.struOSDBatteryPower.fX = m_fX;
    struBatteryPower.struOSDBatteryPower.fY = m_fY;
    struBatteryPower.byOSDBatteryPower = m_byBatteryPower;
    
    struBatteryPower.dwSize = sizeof(struBatteryPower);
    
    DWORD dwChannel = 0;
    dwChannel = m_comChannel.GetCurSel();
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &dwChannel;
    struCfg.dwCondSize = sizeof(dwChannel);
    struCfg.lpInBuffer = &struBatteryPower;
    struCfg.dwInSize = sizeof(struBatteryPower);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lUserID, NET_DVR_SET_OSD_BATTERY_POWER_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_OSD_BATTERY_POWER_CFG");
        sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_WIRELESSSERVER");
    }	
}

void DlgBatteryPower::OnButtonGet() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_OSD_BATTERY_POWER_CFG struBatteryPower = {0};
    
    DWORD dwChannel = 0;
    dwChannel = m_comChannel.GetCurSel();
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &dwChannel;
    struCfg.dwCondSize = sizeof(dwChannel);
    struCfg.lpOutBuffer = &struBatteryPower;
    struCfg.dwOutSize = sizeof(struBatteryPower);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_OSD_BATTERY_POWER_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_OSD_BATTERY_POWER_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_OSD_BATTERY_POWER_CFG");
    }

    m_fX = struBatteryPower.struOSDBatteryPower.fX;
    m_fY = struBatteryPower.struOSDBatteryPower.fY;
    m_byBatteryPower = struBatteryPower.byOSDBatteryPower;
    
    UpdateData(FALSE);
    
}
