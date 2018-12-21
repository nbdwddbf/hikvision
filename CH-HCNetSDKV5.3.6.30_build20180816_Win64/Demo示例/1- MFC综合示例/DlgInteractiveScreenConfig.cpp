// DlgInteractiveScreenConfig.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInteractiveScreenConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInteractiveScreenConfig dialog


CDlgInteractiveScreenConfig::CDlgInteractiveScreenConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInteractiveScreenConfig::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInteractiveScreenConfig)
	m_dwBrightness = 0;
	m_dwContrast = 0;
	m_dwVolume = 0;
	//}}AFX_DATA_INIT
	m_iDevIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lServerID = g_struDeviceInfo[m_iDevIndex].lLoginID;
	m_lChannel = -1;
}


void CDlgInteractiveScreenConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInteractiveScreenConfig)
	DDX_Control(pDX, IDC_COM_SCREENSHOW, m_comScreenShow);
	DDX_Control(pDX, IDC_COM_SCREENLOCK, m_comScreenLock);
	DDX_Control(pDX, IDC_COM_BLACKSCREEN, m_comBlackScreen);
	DDX_Text(pDX, IDC_EDT_BRIGHTNESS, m_dwBrightness);
	DDX_Text(pDX, IDC_EDT_CONTRAST, m_dwContrast);
	DDX_Text(pDX, IDC_EDT_VOLUME, m_dwVolume);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInteractiveScreenConfig, CDialog)
	//{{AFX_MSG_MAP(CDlgInteractiveScreenConfig)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInteractiveScreenConfig message handlers

void CDlgInteractiveScreenConfig::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	memset(&m_struScreenCfg, 0, sizeof(m_struScreenCfg));
	m_struScreenCfg.dwSize = sizeof(m_struScreenCfg);

	NET_DVR_STD_CONFIG struConfig = {0};
	struConfig.lpOutBuffer = &m_struScreenCfg;
	struConfig.dwOutSize = sizeof(m_struScreenCfg);
    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_SCREEN_CONFIG, &struConfig))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SCREEN_CONFIG");
		
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SCREEN_CONFIG");

		m_dwVolume = m_struScreenCfg.byVolume;
		m_dwContrast = m_struScreenCfg.byContrast;
		m_dwBrightness = m_struScreenCfg.byBrightness;
		m_comScreenShow.SetCurSel(m_struScreenCfg.byScreenShowEnabled);
		m_comScreenLock.SetCurSel(m_struScreenCfg.byScreenLocked);
		m_comBlackScreen.SetCurSel(m_struScreenCfg.byBlackScreenEnabled);
    }
	
	UpdateData(FALSE);
}

void CDlgInteractiveScreenConfig::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	memset(&m_struScreenCfg, 0, sizeof(m_struScreenCfg));
	m_struScreenCfg.dwSize = sizeof(m_struScreenCfg);
	m_struScreenCfg.byVolume = m_dwVolume;
	m_struScreenCfg.byContrast = m_dwContrast;
	m_struScreenCfg.byBrightness = m_dwBrightness;
	m_struScreenCfg.byBlackScreenEnabled = m_comBlackScreen.GetCurSel();
	m_struScreenCfg.byScreenLocked = m_comScreenLock.GetCurSel();
	m_struScreenCfg.byScreenShowEnabled = m_comScreenShow.GetCurSel();
	
	NET_DVR_STD_CONFIG struConfig = {0};
	struConfig.lpInBuffer = &m_struScreenCfg;
	struConfig.dwInSize = sizeof(m_struScreenCfg);
	if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_SCREEN_CONFIG, &struConfig))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SCREEN_CONFIG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SCREEN_CONFIG");
    }
}
