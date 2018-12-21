// DlgAcsCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAcsCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgAcsCfg dialog


DlgAcsCfg::DlgAcsCfg(CWnd* pParent /*=NULL*/)
	: CDialog(DlgAcsCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgAcsCfg)
	m_byRS485Backup = FALSE;
    m_byInputCardNo = FALSE;
	m_bOverlayUserInfo = FALSE;
	m_bShowCapPic = FALSE;
	m_bShowCardNo = FALSE;
	m_bShowUserInfo = FALSE;
	m_bVoicePrompt = FALSE;
    m_bLinkCapPic = FALSE;
	m_bSaveCapPic = FALSE;
    m_byEnableWifiDetect = FALSE;
    m_byEnable3G4G = FALSE;
	//}}AFX_DATA_INIT
}


void DlgAcsCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgAcsCfg)
	DDX_Check(pDX, IDC_CHECK_RS485, m_byRS485Backup);
    DDX_Check(pDX, IDC_CHECK_INPUT_CARDNO, m_byInputCardNo);
	DDX_Check(pDX, IDC_CHK_OVERLAY_USERINFO, m_bOverlayUserInfo);
	DDX_Check(pDX, IDC_CHK_SHOW_CAP_PIC, m_bShowCapPic);
	DDX_Check(pDX, IDC_CHK_SHOW_CARDNO, m_bShowCardNo);
	DDX_Check(pDX, IDC_CHK_SHOW_USER_INFO, m_bShowUserInfo);
	DDX_Check(pDX, IDC_CHK_VOICE_PROMPT, m_bVoicePrompt);
    DDX_Check(pDX, IDC_CHK_UPLOAD_CAP_PIC, m_bLinkCapPic);
	DDX_Check(pDX, IDC_CHK_SAVE_CAP_PIC, m_bSaveCapPic);
    DDX_Check(pDX, IDC_CHECK_ENABLE_WIFI_DETECT, m_byEnableWifiDetect);
    DDX_Check(pDX, IDC_CHECK_ENABLE_3G4G, m_byEnable3G4G);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgAcsCfg, CDialog)
	//{{AFX_MSG_MAP(DlgAcsCfg)
    ON_BN_CLICKED(IDC_BUTTON_SET, OnSet)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgAcsCfg message handlers

BOOL DlgAcsCfg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    UpdateData(TRUE);
    DWORD dwDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    char szLan[128] = {0};
    DWORD dwReturn;
    if(NET_DVR_GetDVRConfig(g_struDeviceInfo[dwDeviceIndex].lLoginID,NET_DVR_GET_ACS_CFG,0,&m_struAcsCfg,sizeof(m_struAcsCfg),&dwReturn))
    {
        g_pMainDlg->AddLog(g_struDeviceInfo[dwDeviceIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_GET_ACS_CFG SUCC");
        g_StringLanType(szLan, "获取成功", "Get acs cfg successed!");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(g_struDeviceInfo[dwDeviceIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_GET_ACS_CFG Failed");
        g_StringLanType(szLan, "获取失败", "Get acs cfg failed!");
        AfxMessageBox(szLan);
    }
    m_byRS485Backup = m_struAcsCfg.byRS485Backup;
    m_byInputCardNo = m_struAcsCfg.byInputCardNo;
    m_bShowCapPic = m_struAcsCfg.byShowCapPic;
    m_bShowCardNo = m_struAcsCfg.byShowCardNo;
    m_bShowUserInfo = m_struAcsCfg.byShowUserInfo;
    m_bVoicePrompt = m_struAcsCfg.byVoicePrompt;
    m_bOverlayUserInfo = m_struAcsCfg.byOverlayUserInfo;
    m_bLinkCapPic = m_struAcsCfg.byUploadCapPic;
    m_bSaveCapPic = m_struAcsCfg.bySaveCapPic;
    m_byEnableWifiDetect = m_struAcsCfg.byEnableWifiDetect;
    m_byEnable3G4G = m_struAcsCfg.byEnable3G4G;

    UpdateData(FALSE);
    return TRUE;
}
void DlgAcsCfg::OnSet() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_struAcsCfg.byRS485Backup = m_byRS485Backup;
    m_struAcsCfg.byInputCardNo = m_byInputCardNo;
    
	m_struAcsCfg.byShowCapPic = m_bShowCapPic;
	m_struAcsCfg.byShowCardNo = m_bShowCardNo;
	m_struAcsCfg.byShowUserInfo = m_bShowUserInfo;
	m_struAcsCfg.byVoicePrompt = m_bVoicePrompt;
	m_struAcsCfg.byOverlayUserInfo = m_bOverlayUserInfo;
    m_struAcsCfg.byUploadCapPic = m_bLinkCapPic;
	m_struAcsCfg.bySaveCapPic = m_bSaveCapPic;
    m_struAcsCfg.byEnableWifiDetect = m_byEnableWifiDetect;
    m_struAcsCfg.byEnable3G4G = m_byEnable3G4G;
    m_struAcsCfg.dwSize = sizeof(m_struAcsCfg);
    
    DWORD dwDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    char szLan[128] = {0};
    if(NET_DVR_SetDVRConfig(g_struDeviceInfo[dwDeviceIndex].lLoginID,NET_DVR_SET_ACS_CFG,0,&m_struAcsCfg,sizeof(m_struAcsCfg)))
    {
        g_pMainDlg->AddLog(g_struDeviceInfo[dwDeviceIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_SET_ACS_CFG SUCC");
        g_StringLanType(szLan, "设置成功", "Set acs cfg successed!");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(g_struDeviceInfo[dwDeviceIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_SET_ACS_CFG Failed");
        g_StringLanType(szLan, "设置失败", "Set acs cfg failed!");
        AfxMessageBox(szLan);
    }
}

void DlgAcsCfg::OnGet() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    DWORD dwDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    char szLan[128] = {0};
    DWORD dwReturn;
    if(NET_DVR_GetDVRConfig(g_struDeviceInfo[dwDeviceIndex].lLoginID,NET_DVR_GET_ACS_CFG,0,&m_struAcsCfg,sizeof(m_struAcsCfg),&dwReturn))
    {
        g_pMainDlg->AddLog(g_struDeviceInfo[dwDeviceIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_GET_ACS_CFG SUCC");
        g_StringLanType(szLan, "获取成功", "Get acs cfg successed!");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(g_struDeviceInfo[dwDeviceIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_GET_ACS_CFG Failed");
        g_StringLanType(szLan, "获取失败", "Get acs cfg failed!");
        AfxMessageBox(szLan);
    }
    m_byRS485Backup = m_struAcsCfg.byRS485Backup;
    m_byInputCardNo = m_struAcsCfg.byInputCardNo;
    UpdateData(FALSE);
	m_bShowCapPic = m_struAcsCfg.byShowCapPic;
	m_bShowCardNo = m_struAcsCfg.byShowCardNo;
	m_bShowUserInfo = m_struAcsCfg.byShowUserInfo;
	m_bVoicePrompt  = m_struAcsCfg.byVoicePrompt;
	m_bOverlayUserInfo = m_struAcsCfg.byOverlayUserInfo;
    m_bLinkCapPic  = m_struAcsCfg.byUploadCapPic;
	m_bSaveCapPic = m_struAcsCfg.bySaveCapPic;
    m_byEnableWifiDetect = m_struAcsCfg.byEnableWifiDetect;
    m_byEnable3G4G = m_struAcsCfg.byEnable3G4G;
    UpdateData(FALSE);
}
