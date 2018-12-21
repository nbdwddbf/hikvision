// DlgThscreen.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgThscreen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgThscreen dialog


CDlgThscreen::CDlgThscreen(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgThscreen::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgThscreen)
	m_bEnable = FALSE;
	m_bOSDDisplayEnable = FALSE;
	m_iInterval = 0;
	m_fX = 0.0f;
	m_fY = 0.0f;
	//}}AFX_DATA_INIT

	m_lLoginID = -1;
    m_iDeviceIndex = -1;
	m_lChannel = -1;
    memset(m_szStatusBuf, 0, sizeof(m_szStatusBuf));
}


void CDlgThscreen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgThscreen)
	DDX_Control(pDX, IDC_COMBO_TIMINGMODE, m_comTimingMode);
	DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
	DDX_Check(pDX, IDC_CHECK_OSD_DISPLAY_ENABLE, m_bOSDDisplayEnable);
	DDX_Text(pDX, IDC_EDIT_INTERVAL, m_iInterval);
	DDX_Text(pDX, IDC_EDIT_OSD_X, m_fX);
	DDX_Text(pDX, IDC_EDIT_OSD_Y, m_fY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgThscreen, CDialog)
	//{{AFX_MSG_MAP(CDlgThscreen)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
    ON_BN_CLICKED(IDC_BTN_THSCREEN_TIMING, OnBtnThScreenTiming)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgThscreen message handlers

void CDlgThscreen::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_THSCREEN struThscreenCfg = {0};
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &struThscreenCfg;
    struCfg.dwOutSize = sizeof(struThscreenCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_THSCREEN, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_THSCREEN");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_THSCREEN");
    }
    
    m_bEnable = struThscreenCfg.byEnable;
    m_bOSDDisplayEnable = struThscreenCfg.byTHOSDDisplay;
	m_fX = struThscreenCfg.struTHOSDPoint.fX;
	m_fY = struThscreenCfg.struTHOSDPoint.fY;
	m_comTimingMode.SetCurSel(struThscreenCfg.byTimingMode);
	m_iInterval = struThscreenCfg.wInterval;
    
    UpdateData(FALSE);
}

void CDlgThscreen::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    NET_DVR_THSCREEN struThscreenCfg = {0};
    struThscreenCfg.byEnable = m_bEnable;
    struThscreenCfg.byTHOSDDisplay = m_bOSDDisplayEnable;
	struThscreenCfg.struTHOSDPoint.fX = m_fX;
	struThscreenCfg.struTHOSDPoint.fY = m_fY;
	struThscreenCfg.byTimingMode = m_comTimingMode.GetCurSel();
	struThscreenCfg.wInterval = m_iInterval;

    struThscreenCfg.dwSize = sizeof(struThscreenCfg);
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struThscreenCfg;
    struCfg.dwInSize = sizeof(struThscreenCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_THSCREEN, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_THSCREEN");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_THSCREEN");
    }
}

void CDlgThscreen::OnBtnThScreenTiming()
{
    NET_DVR_STD_CONTROL struSTDCtrl = {0};
    if(!NET_DVR_STDControl(m_lLoginID, NET_DVR_THSCREEN_TIMING, &struSTDCtrl))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_THSCREEN_TIMING");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_THSCREEN_TIMING");
    }   
}

