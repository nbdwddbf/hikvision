// DlgLCDScreen.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgLCDScreen.h"
#include "DlgLCDScreenDisplay.h"
#include "DlgLcdSwitchCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLCDScreen dialog


CDlgLCDScreen::CDlgLCDScreen(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLCDScreen::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLCDScreen)
	m_bySpliceIndex = 0;
	m_bySpliceX = 0;
	m_bySpliceY = 0;
	m_byTemperatureLimitValue = 0;
	m_byClock = 0;
	m_byHorizontalPosition = 0;
	m_byPhase = 0;
	m_byVerticalPosition = 0;
	m_wHeightPip = 0;
	m_wWidthPip = 0;
	m_wXCoordinate = 0;
	m_wYCoordinate = 0;
	m_bySpliceHeight = 0;
	m_bySpliceWidth = 0;
	m_byScreenPosCol = 0;
	m_byScreenPosRow = 0;
	m_dwSignalNo = 0;
	m_dwBottomValue = 0;
	m_dwLeftValue = 0;
	m_dwRightValue = 0;
	m_dwTopValue = 0;
	m_dwWndID = 0;
	m_dwLeftTopX = 0;
	m_dwLeftTopY = 0;
	m_dwRightBtmX = 0;
	m_dwRightBtmY = 0;
	//}}AFX_DATA_INIT
	m_lUserID = -1;
	m_iDevIndex = -1;
}


void CDlgLCDScreen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLCDScreen)
	DDX_Control(pDX, IDC_COMBO_ZOOM_STATUS, m_cmbZoomStatus);
	DDX_Control(pDX, IDC_COMBO_SCREEN_WALL_EABLE, m_comScreenWallEable);
	DDX_Control(pDX, IDC_COMBO_DEFOG_MODEL, m_comDefogModel);
	DDX_Control(pDX, IDC_COMBO_DEFOG_LEVEL, m_comDefogLevel);
	DDX_Control(pDX, IDC_COMBO_DEFOG_ENABLE, m_comDefogEnable);
	DDX_Control(pDX, IDC_COMBO_SOURCE_PIP, m_comSourcePip);
	DDX_Control(pDX, IDC_COMBO_ENABLE_PIP, m_comEnablePip);
	DDX_Control(pDX, IDC_COMBO_COLOR_PIP, m_comPipColor);
	DDX_Control(pDX, IDC_COMBO_DURATION, m_comDuration);
	DDX_Control(pDX, IDC_COMBO_TRANSPARENCY, m_comTransparency);
	DDX_Control(pDX, IDC_COMBO_LANGUAGE, m_comMenuLanguage);
	DDX_Control(pDX, IDC_COMBO_ENABLE_AUTO, m_comEnableAuto);
	DDX_Control(pDX, IDC_COMBO_WORK_MODE, m_comWorkMode);
	DDX_Control(pDX, IDC_COMBO_SIGNALTYPE, m_comSignlType);
	DDX_Control(pDX, IDC_COMBO_SIGNALPIC, m_comSignlPic);
	DDX_Text(pDX, IDC_EDIT_SPLICEINDEX, m_bySpliceIndex);
	DDX_Text(pDX, IDC_EDIT_SPLICE_X, m_bySpliceX);
	DDX_Text(pDX, IDC_EDIT_SPLICE_Y, m_bySpliceY);
	DDX_Text(pDX, IDC_EDIT_TEMPERATURE_VALUE, m_byTemperatureLimitValue);
	DDX_Text(pDX, IDC_EDIT_CLOCK, m_byClock);
	DDX_Text(pDX, IDC_EDIT_HORIZONTAL, m_byHorizontalPosition);
	DDX_Text(pDX, IDC_EDIT_PHASE, m_byPhase);
	DDX_Text(pDX, IDC_EDIT_VERTICAL, m_byVerticalPosition);
	DDX_Text(pDX, IDC_EDIT_HEIGHT_PIP, m_wHeightPip);
	DDX_Text(pDX, IDC_EDIT_WIDTH_PIP, m_wWidthPip);
	DDX_Text(pDX, IDC_EDIT_X_COORDINATE, m_wXCoordinate);
	DDX_Text(pDX, IDC_EDIT_Y_COORDINATE, m_wYCoordinate);
	DDX_Text(pDX, IDC_EDIT_SPLICE_HEIGHT, m_bySpliceHeight);
	DDX_Text(pDX, IDC_EDIT_SPLICE_WIDTH, m_bySpliceWidth);
	DDX_Text(pDX, IDC_EDIT_SCREEN_POS_COL, m_byScreenPosCol);
	DDX_Text(pDX, IDC_EDIT_SCREEN_POS_ROW, m_byScreenPosRow);
	DDX_Text(pDX, IDC_EDIT_SIGNAL_NO, m_dwSignalNo);
	DDX_Text(pDX, IDC_EDIT_VALUE_BOTTOM, m_dwBottomValue);
	DDX_Text(pDX, IDC_EDIT_VALUE_LEFT, m_dwLeftValue);
	DDX_Text(pDX, IDC_EDIT_VALUE_RIGHT, m_dwRightValue);
	DDX_Text(pDX, IDC_EDIT_VALUE_TOP, m_dwTopValue);
	DDX_Text(pDX, IDC_EDIT_WND_ID, m_dwWndID);
	DDX_Text(pDX, IDC_EDIT_LEFTTOP_X, m_dwLeftTopX);
	DDX_Text(pDX, IDC_EDIT_LEFTTOP_Y, m_dwLeftTopY);
	DDX_Text(pDX, IDC_EDIT_RIGHTBTM_X, m_dwRightBtmX);
	DDX_Text(pDX, IDC_EDIT_RIGHTBTM_Y, m_dwRightBtmY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLCDScreen, CDialog)
	//{{AFX_MSG_MAP(CDlgLCDScreen)
	ON_BN_CLICKED(IDC_BTN_REMOTE_OPEN, OnBtnRemoteOpen)
	ON_BN_CLICKED(IDC_BTN_REMOTE_CLOSE, OnBtnRemoteClose)
	ON_BN_CLICKED(IDC_BTN_SIGNAL, OnBtnSignal)
	ON_BN_CLICKED(IDC_BTN_MENU, OnBtnMenu)
	ON_BN_CLICKED(IDC_BTN_INFO, OnBtnInfo)
	ON_BN_CLICKED(IDC_BTN_ASCERTAIN, OnBtnAscertain)
	ON_BN_CLICKED(IDC_BTN_UP, OnBtnUp)
	ON_BN_CLICKED(IDC_BTN_LEFT, OnBtnLeft)
	ON_BN_CLICKED(IDC_BTN_RIGHT, OnBtnRight)
	ON_BN_CLICKED(IDC_BTN_DOWN, OnBtnDown)
	ON_BN_CLICKED(IDC_BTN_RETURN, OnBtnReturn)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET_SPLICE, OnBtnSetSplice)
	ON_BN_CLICKED(IDC_BTN_GET_SPLICE, OnBtnGetSplice)
	ON_BN_CLICKED(IDC_BTN_SET_FAN, OnBtnSetFan)
	ON_BN_CLICKED(IDC_BTN_GET_FAN, OnBtnGetFan)
	ON_CBN_SELCHANGE(IDC_COMBO_WORK_MODE, OnSelchangeComboWorkMode)
	ON_BN_CLICKED(IDC_BTN_SCREEN_WORK_STATUS, OnBtnScreenWorkStatus)
	ON_CBN_SELCHANGE(IDC_COMBO_ENABLE_AUTO, OnSelchangeComboEnableAuto)
	ON_BN_CLICKED(IDC_BNT_SET_VGA, OnBntSetVga)
	ON_BN_CLICKED(IDC_BNT_GET_VGA, OnBntGetVga)
	ON_BN_CLICKED(IDC_BTN_SET_MENU, OnBtnSetMenu)
	ON_BN_CLICKED(IDC_BTN_GET_MENU, OnBtnGetMenu)
	ON_BN_CLICKED(IDC_BTN_SET_PIP, OnBtnSetPip)
	ON_BN_CLICKED(IDC_BTN_GET_PIP, OnBtnGetPip)
	ON_CBN_SELCHANGE(IDC_COMBO_ENABLE_PIP, OnSelchangeComboEnablePip)
	ON_CBN_SELCHANGE(IDC_COMBO_DEFOG_ENABLE, OnSelchangeComboDefogEnable)
	ON_CBN_SELCHANGE(IDC_COMBO_DEFOG_MODEL, OnSelchangeComboDefogModel)
	ON_BN_CLICKED(IDC_BTN_SET_DEFOG, OnBtnSetDefog)
	ON_BN_CLICKED(IDC_BTN_GET_DEFOG, OnBtnGetDefog)
	ON_BN_CLICKED(IDC_BTN_SCREEN_DISPLAY, OnBtnScreenDisplay)
	ON_BN_CLICKED(IDC_BTN_SHOW_IP, OnBtnShowIp)
	ON_BN_CLICKED(IDC_BTN_MAINTENANCE_WALL, OnBtnMaintenanceWall)
	ON_BN_CLICKED(IDC_BTN_SET_SCREEN_POS, OnBtnSetScreenPos)
	ON_BN_CLICKED(IDC_BTN_GET_SCREEN_POS, OnBtnGetScreenPos)
	ON_BN_CLICKED(IDC_BTN_TYPENUM, OnBtnTypenum)
	ON_BN_CLICKED(IDC_BTN_CONTROL0, OnBtnControl0)
	ON_BN_CLICKED(IDC_BTN_CONTROL1, OnBtnControl1)
	ON_BN_CLICKED(IDC_BTN_CONTROL2, OnBtnControl2)
	ON_BN_CLICKED(IDC_BTN_CONTROL3, OnBtnControl3)
	ON_BN_CLICKED(IDC_BTN_CONTROL4, OnBtnControl4)
	ON_BN_CLICKED(IDC_BTN_CONTROL5, OnBtnControl5)
	ON_BN_CLICKED(IDC_BTN_CONTROL6, OnBtnControl6)
	ON_BN_CLICKED(IDC_BTN_CONTROL7, OnBtnControl7)
	ON_BN_CLICKED(IDC_BTN_CONTROL8, OnBtnControl8)
	ON_BN_CLICKED(IDC_BTN_CONTROL9, OnBtnControl9)
	ON_BN_CLICKED(IDC_BTN_SIGNAL_CUT, OnBtnSignalCut)
	ON_BN_CLICKED(IDC_BTN_GET_CUTPARAM, OnBtnGetCutparam)
	ON_BN_CLICKED(IDC_BUTTON_ZOOMIN, OnButtonZoomin)
	ON_BN_CLICKED(IDC_BUTTON_GET_ZOOM_STATUS, OnButtonGetZoomStatus)
	ON_BN_CLICKED(IDC_BTN_SCREEN_TIMER, OnBtnScreenTimer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLCDScreen message handlers


BOOL CDlgLCDScreen::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_comWorkMode.SetCurSel(0);
	GetDlgItem(IDC_STATIC_TEMPERATURE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_TEMPERATURE_VALUE)->ShowWindow(SW_HIDE);

	m_comEnableAuto.SetCurSel(0);
	m_comEnablePip.SetCurSel(0);
	GetDlgItem(IDC_STATIC_SOURCE_PIP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO_SOURCE_PIP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_COLOR_PIP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO_COLOR_PIP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_POSITION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_X_COORDINATE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_X_COORDINATE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_Y_COORDINATE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_Y_COORDINATE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_WIDTH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_WIDTH_PIP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_HEIGHT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_HEIGHT_PIP)->ShowWindow(SW_HIDE);

	m_comDefogEnable.SetCurSel(0);
	m_comDefogModel.SetCurSel(0);
	m_comDefogLevel.SetCurSel(0);
	GetDlgItem(IDC_STATIC_DEFOG_MODEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO_DEFOG_MODEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_DEFOG_LEVEL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO_DEFOG_LEVEL)->ShowWindow(SW_HIDE);

	m_comScreenWallEable.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgLCDScreen::SetRemoteScreen(BYTE byControlType)
{
	char szLan[128] = {0};
	memset(&m_struRemoteScreen, 0, sizeof(m_struRemoteScreen));
	m_struRemoteScreen.dwSize = sizeof(m_struRemoteScreen);
	m_struRemoteScreen.byControlType = byControlType;
	
	if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_SIMULATE_REMOTE_CONTROL, &m_struRemoteScreen, sizeof(NET_DVR_SIMULATE_SCREEN_REMOTE_CTRL)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_SIMULATE_REMOTE_CONTROL ");
		g_StringLanType(szLan, "²Ù×÷Ê§°Ü", "control failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_SIMULATE_REMOTE_CONTROL");
	}
}

void CDlgLCDScreen::OnBtnRemoteOpen() 
{
	// TODO: Add your control notification handler code here
	BYTE byControlType = REMOTE_CTRL_POWERSUPPLY_OPEN; 
	SetRemoteScreen(byControlType);
}

void CDlgLCDScreen::OnBtnRemoteClose() 
{
	// TODO: Add your control notification handler code here
	BYTE byControlType = REMOTE_CTRL_POWERSUPPLY_CLOSE; 
	SetRemoteScreen(byControlType);
}

void CDlgLCDScreen::OnBtnSignal() 
{
	// TODO: Add your control notification handler code here
	BYTE byControlType = REMOTE_CTRL_SIGNALSOURCE; 
	SetRemoteScreen(byControlType);
}

void CDlgLCDScreen::OnBtnMenu() 
{
	// TODO: Add your control notification handler code here
	BYTE byControlType = REMOTE_CTRL_MENU; 
	SetRemoteScreen(byControlType);
}

void CDlgLCDScreen::OnBtnInfo() 
{
	// TODO: Add your control notification handler code here
	BYTE byControlType = REMOTE_CTRL_INFO; 
	SetRemoteScreen(byControlType);
}

void CDlgLCDScreen::OnBtnAscertain() 
{
	// TODO: Add your control notification handler code here
	BYTE byControlType = REMOTE_CTRL_DETERMINATION; 
	SetRemoteScreen(byControlType);
}

void CDlgLCDScreen::OnBtnUp() 
{
	// TODO: Add your control notification handler code here
	BYTE byControlType = REMOTE_CTRL_ON; 
	SetRemoteScreen(byControlType);
}

void CDlgLCDScreen::OnBtnLeft() 
{
	// TODO: Add your control notification handler code here
	BYTE byControlType = REMOTE_CTRL_LEFT; 
	SetRemoteScreen(byControlType);
}

void CDlgLCDScreen::OnBtnRight() 
{
	// TODO: Add your control notification handler code here
	BYTE byControlType = REMOTE_CTRL_RIGHT; 
	SetRemoteScreen(byControlType);
}

void CDlgLCDScreen::OnBtnDown() 
{
	// TODO: Add your control notification handler code here
	BYTE byControlType = REMOTE_CTRL_UNDER; 
	SetRemoteScreen(byControlType);
}

void CDlgLCDScreen::OnBtnReturn() 
{
	// TODO: Add your control notification handler code here
	BYTE byControlType = REMOTE_CTRL_RETURN; 
	SetRemoteScreen(byControlType);
}

void CDlgLCDScreen::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	memset(&m_struSignalCFG, 0, sizeof(m_struSignalCFG));
	m_struSignalCFG.dwSize = sizeof(m_struSignalCFG);
	m_struSignalCFG.bySignalSourceType = m_comSignlType.GetCurSel();
	m_struSignalCFG.byNoSignalPic = m_comSignlPic.GetCurSel();

	if (NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_SCREEN_SIGNAL_CFG, -1, &m_struSignalCFG, sizeof(m_struSignalCFG)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SCREEN_SIGNAL_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SCREEN_SIGNAL_CFG");
        return;
    }
}

void CDlgLCDScreen::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
	memset(&m_struSignalCFG, 0, sizeof(m_struSignalCFG));
    if (NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_SCREEN_SIGNAL_CFG, -1, &m_struSignalCFG, sizeof(m_struSignalCFG), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SCREEN_SIGNAL_CFG");
		m_comSignlType.SetCurSel(m_struSignalCFG.bySignalSourceType);
		m_comSignlPic.SetCurSel(m_struSignalCFG.byNoSignalPic);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SCREEN_SIGNAL_CFG");
		m_comSignlType.SetCurSel(0);
		m_comSignlPic.SetCurSel(0);
        return;
    }
}

void CDlgLCDScreen::OnBtnSetSplice() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	memset(&m_struSpliceCFG, 0, sizeof(m_struSpliceCFG));
	m_struSpliceCFG.dwSize = sizeof(m_struSpliceCFG);
	m_struSpliceCFG.bySpliceIndex = m_bySpliceIndex;
	m_struSpliceCFG.bySpliceX = m_bySpliceX;
	m_struSpliceCFG.bySpliceY = m_bySpliceY;
	m_struSpliceCFG.byWidth = m_bySpliceWidth;
	m_struSpliceCFG.byHeight = m_bySpliceHeight;
	
	if (NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_SCREEN_SPLICE_CFG, -1, &m_struSpliceCFG, sizeof(m_struSpliceCFG)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SCREEN_SPLICE_CFG");
		UpdateData(FALSE);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SCREEN_SPLICE_CFG");
		UpdateData(FALSE);
        return;
    }
}

void CDlgLCDScreen::OnBtnGetSplice() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
	memset(&m_struSpliceCFG, 0, sizeof(m_struSpliceCFG));
    if (NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_SCREEN_SPLICE_CFG, -1, &m_struSpliceCFG, sizeof(m_struSpliceCFG), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SCREEN_SPLICE_CFG");
		m_bySpliceIndex = m_struSpliceCFG.bySpliceIndex;
		m_bySpliceX = m_struSpliceCFG.bySpliceX;
		m_bySpliceY = m_struSpliceCFG.bySpliceY;
		m_bySpliceWidth = m_struSpliceCFG.byWidth;
		m_bySpliceHeight = m_struSpliceCFG.byHeight;
		UpdateData(FALSE);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SCREEN_SPLICE_CFG");
		m_bySpliceIndex = 0;
		m_bySpliceX = 0;
		m_bySpliceY = 0;
		m_bySpliceWidth = 0;
		m_bySpliceHeight = 0;
		UpdateData(FALSE);
        return;
    }
}



void CDlgLCDScreen::OnBtnSetFan() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	memset(&m_struFanMode, 0, sizeof(m_struFanMode));
	m_struFanMode.dwSize = sizeof(m_struFanMode);
	m_struFanMode.byWorkMode = m_comWorkMode.GetCurSel() + 1;
	if (2 == m_struFanMode.byWorkMode)
	{
		m_struFanMode.byTemperatureLimitValue = m_byTemperatureLimitValue;
	}

		
	if (NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_SCREEN_FAN_WORK_MODE, -1, &m_struFanMode, sizeof(m_struFanMode)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SCREEN_FAN_WORK_MODE");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SCREEN_FAN_WORK_MODE");
        return;
    }
}

void CDlgLCDScreen::OnBtnGetFan() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReturn = 0;
	memset(&m_struFanMode, 0, sizeof(m_struFanMode));
    if (NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_SCREEN_FAN_WORK_MODE, -1, &m_struFanMode, sizeof(m_struFanMode), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SCREEN_FAN_WORK_MODE");
		m_comWorkMode.SetCurSel(m_struFanMode.byWorkMode - 1);
		m_byTemperatureLimitValue = m_struFanMode.byTemperatureLimitValue;
		OnSelchangeComboWorkMode();
		UpdateData(FALSE);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SCREEN_FAN_WORK_MODE");
		m_comWorkMode.SetCurSel(0);
		m_byTemperatureLimitValue = 0;
		UpdateData(FALSE);
        return;
    }
}

void CDlgLCDScreen::OnSelchangeComboWorkMode() 
{
	// TODO: Add your control notification handler code here
	int i = m_comWorkMode.GetCurSel() + 1;
	if (2 == i)
	{
		GetDlgItem(IDC_STATIC_TEMPERATURE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_TEMPERATURE_VALUE)->ShowWindow(SW_SHOW);
		m_byTemperatureLimitValue = m_struFanMode.byTemperatureLimitValue;
	}
	else
	{
		GetDlgItem(IDC_STATIC_TEMPERATURE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_TEMPERATURE_VALUE)->ShowWindow(SW_HIDE);
	}
}

void CDlgLCDScreen::OnBtnScreenWorkStatus() 
{
	// TODO: Add your control notification handler code here
	
	if (NET_DVR_RemoteControl(m_lUserID, NET_DVR_SHOW_SCREEN_WORK_STATUS, NULL, 0))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SHOW_SCREEN_WORK_STATUS");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SHOW_SCREEN_WORK_STATUS");
        return;
    }
}



void CDlgLCDScreen::OnSelchangeComboEnableAuto() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int i = m_comEnableAuto.GetCurSel();
	if (0 == i)
	{
		GetDlgItem(IDC_STATIC_HORIZONTAL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_HORIZONTAL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_VERTICAL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_VERTICAL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CLOCK)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_CLOCK)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PHASE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PHASE)->ShowWindow(SW_SHOW);
		
		m_byHorizontalPosition = m_struVGA.byHorizontalPosition;
		m_byVerticalPosition = m_struVGA.byVerticalPosition;
		m_byClock = m_struVGA.byClock;
		m_byPhase = m_struVGA.byPhase;
	}
	else
	{
		GetDlgItem(IDC_STATIC_HORIZONTAL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_HORIZONTAL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_VERTICAL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_VERTICAL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CLOCK)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_CLOCK)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PHASE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PHASE)->ShowWindow(SW_HIDE);
	}
	UpdateData(FALSE);
}

void CDlgLCDScreen::OnBntSetVga() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	memset(&m_struVGA, 0, sizeof(m_struVGA));
	m_struVGA.dwSize = sizeof(m_struVGA);
	m_struVGA.byEnableAutoAdjust = m_comEnableAuto.GetCurSel();
	if (0 == m_struVGA.byEnableAutoAdjust)
	{
		m_struVGA.byHorizontalPosition = m_byHorizontalPosition;
		m_struVGA.byVerticalPosition = m_byVerticalPosition;
		m_struVGA.byClock = m_byClock;
		m_struVGA.byPhase = m_byPhase;
	}
	
	if (NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_VGA_CFG, -1, &m_struVGA, sizeof(m_struVGA)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VGA_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VGA_CFG");
        return;
    }
}

void CDlgLCDScreen::OnBntGetVga() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReturn = 0;
	memset(&m_struVGA, 0, sizeof(m_struVGA));
    if (NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_VGA_CFG, -1, &m_struVGA, sizeof(m_struVGA), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_VGA_CFG");
		m_comEnableAuto.SetCurSel(m_struVGA.byEnableAutoAdjust);
		OnSelchangeComboEnableAuto();
		m_byHorizontalPosition = m_struVGA.byHorizontalPosition;
		m_byVerticalPosition = m_struVGA.byVerticalPosition;
		m_byClock = m_struVGA.byClock;
		m_byPhase = m_struVGA.byPhase;
		UpdateData(FALSE);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VGA_CFG");
		m_comEnableAuto.SetCurSel(0);
		OnSelchangeComboEnableAuto();
		m_byHorizontalPosition = 0;
		m_byVerticalPosition = 0;
		m_byClock = 0;
		m_byPhase = 0;
		UpdateData(FALSE);
        return;
    }
}

void CDlgLCDScreen::OnBtnSetMenu() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	memset(&m_struMenu, 0, sizeof(m_struMenu));
	m_struMenu.dwSize = sizeof(m_struMenu);
	m_struMenu.byMenuLanguage = m_comMenuLanguage.GetCurSel() + 1;
	m_struMenu.byTransparency = m_comTransparency.GetCurSel();
	m_struMenu.byDuration = m_comDuration.GetCurSel();
	
	if (NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_SCREEN_MENU_CFG, -1, &m_struMenu, sizeof(m_struMenu)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SCREEN_MENU_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SCREEN_MENU_CFG");
        return;
    }
}

void CDlgLCDScreen::OnBtnGetMenu() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReturn = 0;
	memset(&m_struMenu, 0, sizeof(m_struMenu));
    if (NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_SCREEN_MENU_CFG, -1, &m_struMenu, sizeof(m_struMenu), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SCREEN_MENU_CFG");
		m_comMenuLanguage.SetCurSel(m_struMenu.byMenuLanguage - 1);
		m_comTransparency.SetCurSel(m_struMenu.byTransparency);
		m_comDuration.SetCurSel(m_struMenu.byDuration);
		UpdateData(FALSE);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SCREEN_MENU_CFG");
		UpdateData(FALSE);
        return;
    }
}

void CDlgLCDScreen::OnBtnSetPip() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	memset(&m_struPip, 0, sizeof(m_struPip));
	m_struPip.dwSize = sizeof(m_struPip);
	m_struPip.byEnable = m_comEnablePip.GetCurSel();
	if (1 == m_struPip.byEnable)
	{
		m_struPip.bySubWindowSource = m_comSourcePip.GetCurSel();
		m_struPip.bySubWindowBorderColor = m_comPipColor.GetCurSel();
		m_struPip.struPosition.wXCoordinate = m_wXCoordinate;
		m_struPip.struPosition.wYCoordinate = m_wYCoordinate;
		m_struPip.struPosition.wHeight = m_wHeightPip;
		m_struPip.struPosition.wWidth = m_wWidthPip;
	}
	
	if (NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_PIP_CFG, -1, &m_struPip, sizeof(m_struPip)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_PIP_CFG");
		UpdateData(FALSE);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_PIP_CFG");
		UpdateData(FALSE);
        return;
    }
}

void CDlgLCDScreen::OnBtnGetPip() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReturn = 0;
	memset(&m_struPip, 0, sizeof(m_struPip));
    if (NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_PIP_CFG, -1, &m_struPip, sizeof(m_struPip), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PIP_CFG");
		m_comEnablePip.SetCurSel(m_struPip.byEnable);
		if (1 == m_struPip.byEnable)
		{
			m_comSourcePip.SetCurSel(m_struPip.bySubWindowSource);
			m_comPipColor.SetCurSel(m_struPip.bySubWindowBorderColor);
			m_wXCoordinate = m_struPip.struPosition.wXCoordinate;
			m_wYCoordinate = m_struPip.struPosition.wYCoordinate;
			m_wHeightPip = m_struPip.struPosition.wHeight;
			m_wWidthPip = m_struPip.struPosition.wWidth;
		}
		OnSelchangeComboEnablePip();
		UpdateData(FALSE);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PIP_CFG");
		m_comEnablePip.SetCurSel(0);
		m_comSourcePip.SetCurSel(0);
		m_comPipColor.SetCurSel(0);
		m_wXCoordinate = 0;
		m_wYCoordinate = 0;
		m_wHeightPip = 0;
		m_wWidthPip = 0;

		OnSelchangeComboEnablePip();
		UpdateData(FALSE);
        return;
    }
}

void CDlgLCDScreen::OnSelchangeComboEnablePip() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int i = m_comEnablePip.GetCurSel();
	if (1 == i)
	{
		GetDlgItem(IDC_STATIC_SOURCE_PIP)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_SOURCE_PIP)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_COLOR_PIP)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_COLOR_PIP)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_POSITION)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_X_COORDINATE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_X_COORDINATE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_Y_COORDINATE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_Y_COORDINATE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_WIDTH)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_WIDTH_PIP)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_HEIGHT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_HEIGHT_PIP)->ShowWindow(SW_SHOW);

// 		m_comEnablePip.SetCurSel(m_struPip.byEnable);
// 		if (1 == m_struPip.byEnable)
// 		{
// 			m_comSourcePip.SetCurSel(m_struPip.bySubWindowSource);
// 			m_comPipColor.SetCurSel(m_struPip.bySubWindowBorderColor);
// 			m_wXCoordinate = m_struPip.struPosition.wXCoordinate;
// 			m_wYCoordinate = m_struPip.struPosition.wYCoordinate;
// 			m_wHeightPip = m_struPip.struPosition.wHeight;
// 			m_wWidthPip = m_struPip.struPosition.wWidth;
// 		}
	}
	else
	{
		GetDlgItem(IDC_STATIC_SOURCE_PIP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_SOURCE_PIP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_COLOR_PIP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_COLOR_PIP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_POSITION)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_X_COORDINATE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_X_COORDINATE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_Y_COORDINATE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_Y_COORDINATE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_WIDTH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_WIDTH_PIP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_HEIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_HEIGHT_PIP)->ShowWindow(SW_HIDE);
	}
	UpdateData(FALSE);
}

void CDlgLCDScreen::OnSelchangeComboDefogEnable() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (1 == m_comDefogEnable.GetCurSel())
	{
		GetDlgItem(IDC_STATIC_DEFOG_MODEL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_DEFOG_MODEL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_DEFOG_LEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_DEFOG_LEVEL)->ShowWindow(SW_HIDE);

		m_comDefogModel.SetCurSel(m_struDefog.byDefogModel);
		if (1 == m_struDefog.byDefogModel)
		{
			m_comDefogLevel.SetCurSel(m_struDefog.byDefogLevel);
		}
	}
	else
	{
		GetDlgItem(IDC_STATIC_DEFOG_MODEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_DEFOG_MODEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_DEFOG_LEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_DEFOG_LEVEL)->ShowWindow(SW_HIDE);
	}
	UpdateData(FALSE);
}

void CDlgLCDScreen::OnSelchangeComboDefogModel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (1 == m_comDefogModel.GetCurSel())
	{
		GetDlgItem(IDC_STATIC_DEFOG_LEVEL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_DEFOG_LEVEL)->ShowWindow(SW_SHOW);
		
		m_comDefogLevel.SetCurSel(m_struDefog.byDefogLevel);
	}
	else
	{
		GetDlgItem(IDC_STATIC_DEFOG_LEVEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_DEFOG_LEVEL)->ShowWindow(SW_HIDE);
	}
	UpdateData(FALSE);
}

void CDlgLCDScreen::OnBtnSetDefog() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	memset(&m_struDefog, 0, sizeof(m_struDefog));
	m_struDefog.dwSize = sizeof(m_struDefog);
	m_struDefog.byDefogEnable = m_comDefogEnable.GetCurSel();
	if (1 == m_struDefog.byDefogEnable)
	{
		m_struDefog.byDefogModel = m_comDefogModel.GetCurSel();
		if (1 == m_struDefog.byDefogModel)
		{
			m_struDefog.byDefogLevel = m_comDefogLevel.GetCurSel();
		}
	}
	
	if (NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_DEFOG_LCD, -1, &m_struDefog, sizeof(m_struDefog)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_DEFOG_LCD");
		UpdateData(FALSE);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_DEFOG_LCD");
		UpdateData(FALSE);
        return;
    }
}

void CDlgLCDScreen::OnBtnGetDefog() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReturn = 0;
	memset(&m_struDefog, 0, sizeof(m_struDefog));
    if (NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_DEFOG_LCD, -1, &m_struDefog, sizeof(m_struDefog), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_DEFOG_LCD");
		m_comDefogEnable.SetCurSel(m_struDefog.byDefogEnable);
		OnSelchangeComboDefogEnable();
		if (1 == m_struDefog.byDefogEnable)
		{
			m_comDefogModel.SetCurSel(m_struDefog.byDefogModel);
			OnSelchangeComboDefogModel();
			if (1 == m_struDefog.byDefogModel)
			{
				m_comDefogLevel.SetCurSel(m_struDefog.byDefogLevel);
			}
		}
		UpdateData(FALSE);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_DEFOG_LCD");
		m_comDefogEnable.SetCurSel(0);
		m_comDefogModel.SetCurSel(0);
		m_comDefogLevel.SetCurSel(0);

		UpdateData(FALSE);
        return;
    }
}

void CDlgLCDScreen::OnBtnScreenDisplay() 
{
	// TODO: Add your control notification handler code here
	CDlgLCDScreenDisplay dlg;
	dlg.m_lUserID = m_lUserID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CDlgLCDScreen::OnBtnShowIp() 
{
	// TODO: Add your control notification handler code here
	
	if (NET_DVR_RemoteControl(m_lUserID, NET_DVR_SHOW_IP, NULL, 0))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SHOW_IP");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SHOW_IP");
        return;
    }
}

void CDlgLCDScreen::OnBtnMaintenanceWall() 
{
	// TODO: Add your control notification handler code here
	
	NET_DVR_SCREEN_WALL_CFG struScreenWall;
	memset(&struScreenWall, 0, sizeof(NET_DVR_SCREEN_WALL_CFG));
	struScreenWall.dwSize = sizeof(NET_DVR_SCREEN_WALL_CFG);
	struScreenWall.byEnable = m_comScreenWallEable.GetCurSel();
	if (NET_DVR_RemoteControl(m_lUserID, NET_DVR_SCREEN_MAINTENANCE_WALL, &struScreenWall, sizeof(NET_DVR_SCREEN_WALL_CFG)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SCREEN_MAINTENANCE_WALL");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SCREEN_MAINTENANCE_WALL");
        return;
    }
}

void CDlgLCDScreen::OnBtnSetScreenPos() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	NET_DVR_SCREEN_POS_CFG struScreenPos;
	memset(&struScreenPos, 0, sizeof(NET_DVR_SCREEN_POS_CFG));
	struScreenPos.dwSize = sizeof(NET_DVR_SCREEN_POS_CFG);
	struScreenPos.byScreenRowNum = m_byScreenPosRow;
	struScreenPos.byScreenColNum = m_byScreenPosCol;
	
	if (NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_SCREEN_POS, -1, &struScreenPos, sizeof(NET_DVR_SCREEN_POS_CFG)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SCREEN_POS");
		UpdateData(FALSE);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SCREEN_POS");
		UpdateData(FALSE);
        return;
    }
}

void CDlgLCDScreen::OnBtnGetScreenPos() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReturn = 0;
	NET_DVR_SCREEN_POS_CFG struScreenPos;
	memset(&struScreenPos, 0, sizeof(NET_DVR_SCREEN_POS_CFG));

    if (NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_SCREEN_POS, -1, &struScreenPos, sizeof(NET_DVR_SCREEN_POS_CFG), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SCREEN_POS");
		m_byScreenPosRow = struScreenPos.byScreenRowNum;
		m_byScreenPosCol = struScreenPos.byScreenColNum;
		UpdateData(FALSE);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SCREEN_POS");
		m_byScreenPosRow = 0;
		m_byScreenPosCol = 0;			
		UpdateData(FALSE);
        return;
    }
}

void CDlgLCDScreen::OnBtnTypenum() 
{
	// TODO: Add your control notification handler code here
    m_struRemoteScreen.byControlType = REMOTE_CTRL_NUM;
}

void CDlgLCDScreen::OnBtnControl0() 
{
	// TODO: Add your control notification handler code here
    if (m_struRemoteScreen.byControlType == REMOTE_CTRL_NUM)
    {
        char szLan[128] = {0};
        memset(&m_struRemoteScreen, 0, sizeof(m_struRemoteScreen));
        m_struRemoteScreen.dwSize = sizeof(m_struRemoteScreen);
		m_struRemoteScreen.byControlType = REMOTE_CTRL_NUM;
        m_struRemoteScreen.byControlParam = 0;
        
        if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_SIMULATE_REMOTE_CONTROL, &m_struRemoteScreen, sizeof(NET_DVR_SIMULATE_SCREEN_REMOTE_CTRL)))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_SIMULATE_REMOTE_CONTROL");
            g_StringLanType(szLan, "²Ù×÷Ê§°Ü", "control failed");
            AfxMessageBox(szLan);
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_SIMULATE_REMOTE_CONTROL");
        }
    }
    return;
}

void CDlgLCDScreen::OnBtnControl1() 
{
	// TODO: Add your control notification handler code here
    if (m_struRemoteScreen.byControlType == REMOTE_CTRL_NUM)
    {
        char szLan[128] = {0};
        memset(&m_struRemoteScreen, 0, sizeof(m_struRemoteScreen));
        m_struRemoteScreen.dwSize = sizeof(m_struRemoteScreen);
		m_struRemoteScreen.byControlType = REMOTE_CTRL_NUM;
        m_struRemoteScreen.byControlParam = 1;
        
        if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_SIMULATE_REMOTE_CONTROL, &m_struRemoteScreen, sizeof(NET_DVR_SIMULATE_SCREEN_REMOTE_CTRL)))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_SIMULATE_REMOTE_CONTROL ");
            g_StringLanType(szLan, "²Ù×÷Ê§°Ü", "control failed");
            AfxMessageBox(szLan);
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_SIMULATE_REMOTE_CONTROL");
        }
    }
    return;
}

void CDlgLCDScreen::OnBtnControl2() 
{
	// TODO: Add your control notification handler code here
    if (m_struRemoteScreen.byControlType == REMOTE_CTRL_NUM)
    {
        char szLan[128] = {0};
        memset(&m_struRemoteScreen, 0, sizeof(m_struRemoteScreen));
        m_struRemoteScreen.dwSize = sizeof(m_struRemoteScreen);
		m_struRemoteScreen.byControlType = REMOTE_CTRL_NUM;
        m_struRemoteScreen.byControlParam = 2;
        
        if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_SIMULATE_REMOTE_CONTROL, &m_struRemoteScreen, sizeof(NET_DVR_SIMULATE_SCREEN_REMOTE_CTRL)))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_SIMULATE_REMOTE_CONTROL ");
            g_StringLanType(szLan, "²Ù×÷Ê§°Ü", "control failed");
            AfxMessageBox(szLan);
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_SIMULATE_REMOTE_CONTROL");
        }
    }
    return;
}

void CDlgLCDScreen::OnBtnControl3() 
{
	// TODO: Add your control notification handler code here
    if (m_struRemoteScreen.byControlType == REMOTE_CTRL_NUM)
    {
        char szLan[128] = {0};
        memset(&m_struRemoteScreen, 0, sizeof(m_struRemoteScreen));
        m_struRemoteScreen.dwSize = sizeof(m_struRemoteScreen);
		m_struRemoteScreen.byControlType = REMOTE_CTRL_NUM;
        m_struRemoteScreen.byControlParam = 3;
        
        if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_SIMULATE_REMOTE_CONTROL, &m_struRemoteScreen, sizeof(NET_DVR_SIMULATE_SCREEN_REMOTE_CTRL)))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_SIMULATE_REMOTE_CONTROL ");
            g_StringLanType(szLan, "²Ù×÷Ê§°Ü", "control failed");
            AfxMessageBox(szLan);
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_SIMULATE_REMOTE_CONTROL");
        }
    }
    return;
}

void CDlgLCDScreen::OnBtnControl4() 
{
	// TODO: Add your control notification handler code here
    if (m_struRemoteScreen.byControlType == REMOTE_CTRL_NUM)
    {
        char szLan[128] = {0};
        memset(&m_struRemoteScreen, 0, sizeof(m_struRemoteScreen));
        m_struRemoteScreen.dwSize = sizeof(m_struRemoteScreen);
		m_struRemoteScreen.byControlType = REMOTE_CTRL_NUM;
        m_struRemoteScreen.byControlParam = 4;
        
        if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_SIMULATE_REMOTE_CONTROL, &m_struRemoteScreen, sizeof(NET_DVR_SIMULATE_SCREEN_REMOTE_CTRL)))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_SIMULATE_REMOTE_CONTROL ");
            g_StringLanType(szLan, "²Ù×÷Ê§°Ü", "control failed");
            AfxMessageBox(szLan);
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_SIMULATE_REMOTE_CONTROL");
        }
    }
    return;
}

void CDlgLCDScreen::OnBtnControl5() 
{
	// TODO: Add your control notification handler code here
    if (m_struRemoteScreen.byControlType == REMOTE_CTRL_NUM)
    {
        char szLan[128] = {0};
        memset(&m_struRemoteScreen, 0, sizeof(m_struRemoteScreen));
        m_struRemoteScreen.dwSize = sizeof(m_struRemoteScreen);
		m_struRemoteScreen.byControlType = REMOTE_CTRL_NUM;
        m_struRemoteScreen.byControlParam = 5;
        
        if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_SIMULATE_REMOTE_CONTROL, &m_struRemoteScreen, sizeof(NET_DVR_SIMULATE_SCREEN_REMOTE_CTRL)))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_SIMULATE_REMOTE_CONTROL ");
            g_StringLanType(szLan, "²Ù×÷Ê§°Ü", "control failed");
            AfxMessageBox(szLan);
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_SIMULATE_REMOTE_CONTROL");
        }
    }
    return;
}

void CDlgLCDScreen::OnBtnControl6() 
{
	// TODO: Add your control notification handler code here
    if (m_struRemoteScreen.byControlType == REMOTE_CTRL_NUM)
    {
        char szLan[128] = {0};
        memset(&m_struRemoteScreen, 0, sizeof(m_struRemoteScreen));
        m_struRemoteScreen.dwSize = sizeof(m_struRemoteScreen);
		m_struRemoteScreen.byControlType = REMOTE_CTRL_NUM;
        m_struRemoteScreen.byControlParam = 6;
        
        if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_SIMULATE_REMOTE_CONTROL, &m_struRemoteScreen, sizeof(NET_DVR_SIMULATE_SCREEN_REMOTE_CTRL)))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_SIMULATE_REMOTE_CONTROL ");
            g_StringLanType(szLan, "²Ù×÷Ê§°Ü", "control failed");
            AfxMessageBox(szLan);
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_SIMULATE_REMOTE_CONTROL");
        }
    }
    return;
}

void CDlgLCDScreen::OnBtnControl7() 
{
	// TODO: Add your control notification handler code here
    if (m_struRemoteScreen.byControlType == REMOTE_CTRL_NUM)
    {
        char szLan[128] = {0};
        memset(&m_struRemoteScreen, 0, sizeof(m_struRemoteScreen));
        m_struRemoteScreen.dwSize = sizeof(m_struRemoteScreen);
		m_struRemoteScreen.byControlType = REMOTE_CTRL_NUM;
        m_struRemoteScreen.byControlParam = 7;
        
        if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_SIMULATE_REMOTE_CONTROL, &m_struRemoteScreen, sizeof(NET_DVR_SIMULATE_SCREEN_REMOTE_CTRL)))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_SIMULATE_REMOTE_CONTROL ");
            g_StringLanType(szLan, "²Ù×÷Ê§°Ü", "control failed");
            AfxMessageBox(szLan);
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_SIMULATE_REMOTE_CONTROL");
        }
    }
    return;
}

void CDlgLCDScreen::OnBtnControl8() 
{
	// TODO: Add your control notification handler code here
    if (m_struRemoteScreen.byControlType == REMOTE_CTRL_NUM)
    {
        char szLan[128] = {0};
        memset(&m_struRemoteScreen, 0, sizeof(m_struRemoteScreen));
        m_struRemoteScreen.dwSize = sizeof(m_struRemoteScreen);
		m_struRemoteScreen.byControlType = REMOTE_CTRL_NUM;
        m_struRemoteScreen.byControlParam = 8;
        
        if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_SIMULATE_REMOTE_CONTROL, &m_struRemoteScreen, sizeof(NET_DVR_SIMULATE_SCREEN_REMOTE_CTRL)))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_SIMULATE_REMOTE_CONTROL ");
            g_StringLanType(szLan, "²Ù×÷Ê§°Ü", "control failed");
            AfxMessageBox(szLan);
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_SIMULATE_REMOTE_CONTROL");
        }
    }
    return;
}

void CDlgLCDScreen::OnBtnControl9() 
{
	// TODO: Add your control notification handler code here
    if (m_struRemoteScreen.byControlType == REMOTE_CTRL_NUM)
    {
        char szLan[128] = {0};
        memset(&m_struRemoteScreen, 0, sizeof(m_struRemoteScreen));
        m_struRemoteScreen.dwSize = sizeof(m_struRemoteScreen);
		m_struRemoteScreen.byControlType = REMOTE_CTRL_NUM;
        m_struRemoteScreen.byControlParam = 9;
        
        if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_SIMULATE_REMOTE_CONTROL, &m_struRemoteScreen, sizeof(NET_DVR_SIMULATE_SCREEN_REMOTE_CTRL)))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_SIMULATE_REMOTE_CONTROL ");
            g_StringLanType(szLan, "²Ù×÷Ê§°Ü", "control failed");
            AfxMessageBox(szLan);
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_SIMULATE_REMOTE_CONTROL");
        }
    }
    return;
}

void CDlgLCDScreen::OnBtnSignalCut() 
{
	// TODO: Add your control notification handler code here
// 	UpdateData(TRUE);
// 	NET_DVR_SIGNAL_CUTPARAM struCutParam;
// 	memset(&struCutParam, 0, sizeof(struCutParam));
// 	struCutParam.dwSize = sizeof(struCutParam);
// 	struCutParam.dwCutBottom = m_dwBottomValue;
// 	struCutParam.dwCutLeft = m_dwLeftValue;
// 	struCutParam.dwCutRight = m_dwRightValue;
// 	struCutParam.dwCutTop = m_dwTopValue;
// 	struCutParam.dwSignalNo = m_dwSignalNo;
// 	if (NET_DVR_RemoteControl(m_lUserID, NET_DVR_SIGNAL_CUT, &struCutParam, sizeof(struCutParam)))
// 	{
// 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_SIGNAL_CUT");
// 	}
// 	else
// 	{
// 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_SIGNAL_CUT");
// 	}
}

void CDlgLCDScreen::OnBtnGetCutparam() 
{
	// TODO: Add your control notification handler code here
// 	NET_DVR_SIGNAL_CUTPARAM struCutParam;
// 	memset(&struCutParam, 0, sizeof(struCutParam));
// 	struCutParam.dwSize = sizeof(struCutParam);
// 	DWORD dwRetBytes = 0;
// 	if (NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_SIGNAL_CUTPARAM, -1, &struCutParam, sizeof(struCutParam), &dwRetBytes))
// 	{
// 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetDVRConfig NET_DVR_GET_SIGNAL_CUTPARAM");
// 		m_dwBottomValue = struCutParam.dwCutBottom;
// 		m_dwLeftValue = struCutParam.dwCutLeft;
// 		m_dwRightValue = struCutParam.dwCutRight;
// 		m_dwTopValue = struCutParam.dwCutTop;
// 		m_dwSignalNo = struCutParam.dwSignalNo;
// 		UpdateData(FALSE);
// 	}
// 	else
// 	{
// 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetDVRConfig NET_DVR_GET_SIGNAL_CUTPARAM");
// 	}
}

void CDlgLCDScreen::OnButtonZoomin() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_SCREENZOOM struScreenZoom;
	memset(&struScreenZoom, 0, sizeof(struScreenZoom));
	struScreenZoom.dwSize = sizeof(struScreenZoom);
	struScreenZoom.dwScreenNum = m_dwWndID;
	struScreenZoom.struPointFrame.xTop = m_dwLeftTopX;
	struScreenZoom.struPointFrame.yTop = m_dwLeftTopY;
	struScreenZoom.struPointFrame.xBottom = m_dwRightBtmX;
	struScreenZoom.struPointFrame.yBottom = m_dwRightBtmY;
	if (NET_DVR_ScreenZoomIn(m_lUserID, &struScreenZoom))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_ScreenZoomIn");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_ScreenZoomIn");
	}
}

void CDlgLCDScreen::OnButtonGetZoomStatus() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_WIN_ZOOM_STATUS struZoomStatus;
	memset(&struZoomStatus, 0, sizeof(struZoomStatus));
	struZoomStatus.dwSize = sizeof(struZoomStatus);
	DWORD dwReturnBytes = 0;
	if (NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_WIN_ZOOM_STATUS, m_dwWndID, &struZoomStatus, sizeof(struZoomStatus), &dwReturnBytes))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetDVRConfig NET_DVR_GET_WIN_ZOOM_STATUS");
		m_cmbZoomStatus.SetCurSel(struZoomStatus.byZoomStatus);
		m_dwLeftTopX = struZoomStatus.struPointFrame.xTop;
		m_dwLeftTopY = struZoomStatus.struPointFrame.yTop;
		m_dwRightBtmX = struZoomStatus.struPointFrame.xBottom;
		m_dwRightBtmY = struZoomStatus.struPointFrame.yBottom;
		UpdateData(FALSE);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetDVRConfig NET_DVR_GET_WIN_ZOOM_STATUS");
	}
}

void CDlgLCDScreen::OnBtnScreenTimer() 
{
	// TODO: Add your control notification handler code here
	CDlgLcdSwitchCfg dlg;
	dlg.m_lUserId = m_lUserID;
	dlg.m_iDeviceIndex = m_iDevIndex;
	dlg.DoModal();
}
