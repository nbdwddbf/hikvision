// DlgVCAAlarmLogo.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVCAAlarmLogo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgVCAAlarmLogo dialog


DlgVCAAlarmLogo::DlgVCAAlarmLogo(CWnd* pParent /*=NULL*/)
	: CDialog(DlgVCAAlarmLogo::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgVCAAlarmLogo)
	m_BEnableLogo = FALSE;
	m_BAlarmFlash = FALSE;
	m_dwChannel = 1;
	m_dwFlashTime = 0;
	m_dwLogoX = 0;
	m_dwLogoY = 0;
	//}}AFX_DATA_INIT
}


void DlgVCAAlarmLogo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgVCAAlarmLogo)
	DDX_Check(pDX, IDC_CHK_ENABLE_LOGO, m_BEnableLogo);
	DDX_Check(pDX, IDC_CHK_VCA_ALARM_FLASH, m_BAlarmFlash);
	DDX_Text(pDX, IDC_EDT_VCA_CHANNEL, m_dwChannel);
	DDX_Text(pDX, IDC_EDT_VCA_FLASHTIME, m_dwFlashTime);
	DDX_Text(pDX, IDC_EDT_VCA_LOGOX, m_dwLogoX);
	DDX_Text(pDX, IDC_EDT_VCA_LOGOY, m_dwLogoY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgVCAAlarmLogo, CDialog)
	//{{AFX_MSG_MAP(DlgVCAAlarmLogo)
	ON_BN_CLICKED(IDC_BUT_VCA_GET, OnButVcaGet)
	ON_BN_CLICKED(IDC_BUT_VCA_SET, OnButVcaSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgVCAAlarmLogo message handlers

void DlgVCAAlarmLogo::OnButVcaGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    NET_DVR_VCA_ALARM_CFG struVcaAlarmCfg = {0}; 
    DWORD  dwReturn = 0; 
    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_DEC_VCA_CFG, m_dwChannel, &struVcaAlarmCfg, sizeof(struVcaAlarmCfg), &dwReturn))
    {      
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_GET_DEC_VCA_CFG");
        return ; 
    }
    g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_GET_DEC_VCA_CFG");
    m_BEnableLogo = struVcaAlarmCfg.struAlarmLogo.byEnableLogo;
    m_BAlarmFlash = struVcaAlarmCfg.struAlarmLogo.byFlash;
    m_dwFlashTime = struVcaAlarmCfg.struAlarmLogo.wFlashTime;
    m_dwLogoX = struVcaAlarmCfg.struAlarmLogo.dwLogoX;
	m_dwLogoY = struVcaAlarmCfg.struAlarmLogo.dwLogoY;
    UpdateData(FALSE); 
}

void DlgVCAAlarmLogo::OnButVcaSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    NET_DVR_VCA_ALARM_CFG struVcaAlarmCfg = {0}; 
    struVcaAlarmCfg.dwSize = sizeof(struVcaAlarmCfg); 
    struVcaAlarmCfg.struAlarmLogo.byEnableLogo = m_BEnableLogo; 
    struVcaAlarmCfg.struAlarmLogo.byFlash = m_BAlarmFlash; 
    struVcaAlarmCfg.struAlarmLogo.wFlashTime = m_dwFlashTime; 
    struVcaAlarmCfg.struAlarmLogo.dwLogoX = m_dwLogoX; 
    struVcaAlarmCfg.struAlarmLogo.dwLogoY = m_dwLogoY; 
    if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_DEC_VCA_CFG, m_dwChannel, &struVcaAlarmCfg, sizeof(struVcaAlarmCfg)))
    {      
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_SET_DEC_VCA_CFG");
        return ; 
    }
    g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_SET_DEC_VCA_CFG");

}

BOOL DlgVCAAlarmLogo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_lDeviceID = g_pMainDlg->GetCurDeviceIndex(); 
	m_lUserID =  g_struDeviceInfo[m_lDeviceID].lLoginID; 

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
