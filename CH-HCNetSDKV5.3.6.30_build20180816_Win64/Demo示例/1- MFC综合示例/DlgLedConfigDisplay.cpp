// DlgLedConfigDisplay.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgLedConfigDisplay.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLedConfigDisplay dialog


CDlgLedConfigDisplay::CDlgLedConfigDisplay(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLedConfigDisplay::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLedConfigDisplay)
	m_bTestSignalEnable = FALSE;
	m_dwEndCol = 0;
	m_dwEndRow = 0;
	m_dwStartCol = 0;
	m_dwStartRow = 0;
	m_dwSignalBlue = 0;
	m_dwSignalGreen = 0;
	m_dwSignalRed = 0;
	m_dwBlue = 0;
	m_dwBlueOffset = 0;
	m_dwContrast = 0;
	m_dwGreen = 0;
	m_dwGreenOffset = 0;
	m_dwHue = 0;
	m_dwLight = 0;
	m_dwPort = 0;
	m_dwRed = 0;
	m_dwRedOffset = 0;
	m_dwSaturation = 0;
	m_dwSharpness = 0;
	m_dwNoSignalOutputNo = 0;
	//}}AFX_DATA_INIT
	m_lUserID = -1;
	m_iDeviceIndex = -1;
	m_iDisplayType = -1;
	m_byDisplayMode = 0xff;
	m_bySignalType = 0xff;
}


void CDlgLedConfigDisplay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLedConfigDisplay)
	DDX_Control(pDX, IDC_COMBO_TESTSIGNAL_TYPE, m_cmbTestSignalType);
	DDX_Control(pDX, IDC_COMBO_NOSIGNAL_MODE, m_cmbNoSignalMode);
	DDX_Control(pDX, IDC_COMBO_DISPLAY_TYPE, m_cmbDisplayType);
	DDX_Control(pDX, IDC_COMBO_DISPLAY_IMAGE_MODE, m_cmbImageMode);
	DDX_Control(pDX, IDC_COMBO_DISPLAY_DISPLAY_MODE, m_cmbDisplayMode);
	DDX_Check(pDX, IDC_CHK_TESTSIGNAL_ENABLE, m_bTestSignalEnable);
	DDX_Text(pDX, IDC_EDIT_DISPLAY_END_COL, m_dwEndCol);
	DDX_Text(pDX, IDC_EDIT_DISPLAY_END_ROW, m_dwEndRow);
	DDX_Text(pDX, IDC_EDIT_DISPLAY_START_COL, m_dwStartCol);
	DDX_Text(pDX, IDC_EDIT_DISPLAY_START_ROW, m_dwStartRow);
	DDX_Text(pDX, IDC_EDIT_TESTSIGNAL_BLUE, m_dwSignalBlue);
	DDX_Text(pDX, IDC_EDIT_TESTSIGNAL_GREEN, m_dwSignalGreen);
	DDX_Text(pDX, IDC_EDIT_TESTSIGNAL_RED, m_dwSignalRed);
	DDX_Text(pDX, IDC_EDT_DISPLAY_PARAMETER_BLUE, m_dwBlue);
	DDX_Text(pDX, IDC_EDT_DISPLAY_PARAMETER_BLUEOFFSET, m_dwBlueOffset);
	DDX_Text(pDX, IDC_EDT_DISPLAY_PARAMETER_CONTRAST, m_dwContrast);
	DDX_Text(pDX, IDC_EDT_DISPLAY_PARAMETER_GREEN, m_dwGreen);
	DDX_Text(pDX, IDC_EDT_DISPLAY_PARAMETER_GREENOFFSET, m_dwGreenOffset);
	DDX_Text(pDX, IDC_EDT_DISPLAY_PARAMETER_HUE, m_dwHue);
	DDX_Text(pDX, IDC_EDT_DISPLAY_PARAMETER_LIGHT, m_dwLight);
	DDX_Text(pDX, IDC_EDT_DISPLAY_PARAMETER_PORT, m_dwPort);
	DDX_Text(pDX, IDC_EDT_DISPLAY_PARAMETER_RED, m_dwRed);
	DDX_Text(pDX, IDC_EDT_DISPLAY_PARAMETER_REDOFFSET, m_dwRedOffset);
	DDX_Text(pDX, IDC_EDT_DISPLAY_PARAMETER_SATURATION, m_dwSaturation);
	DDX_Text(pDX, IDC_EDT_DISPLAY_PARAMETER_SHARPNESS, m_dwSharpness);
	DDX_Text(pDX, IDC_EDIT_NOSIGNAL_OUTPUTNO, m_dwNoSignalOutputNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLedConfigDisplay, CDialog)
	//{{AFX_MSG_MAP(CDlgLedConfigDisplay)
	ON_BN_CLICKED(IDC_BTN_NOSIGNAL_GET, OnBtnNosignalGet)
	ON_BN_CLICKED(IDC_BTN_NOSIGNAL_SET, OnBtnNosignalSet)
	ON_BN_CLICKED(IDC_BTN_TESTSIGNAL_GET, OnBtnTestsignalGet)
	ON_BN_CLICKED(IDC_BTN_TESTSIGNAL_SET, OnBtnTestsignalSet)
	ON_BN_CLICKED(IDC_BUT_DISPLAY_PARAMETER_GET, OnButDisplayParameterGet)
	ON_BN_CLICKED(IDC_BUT_DISPLAY_PARAMETER_SET, OnButDisplayParameterSet)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_CBN_SELCHANGE(IDC_COMBO_DISPLAY_DISPLAY_MODE, OnSelchangeComboDisplayDisplayMode)
	ON_CBN_SELCHANGE(IDC_COMBO_DISPLAY_TYPE, OnSelchangeComboDisplayType)
	ON_CBN_SELCHANGE(IDC_COMBO_TESTSIGNAL_TYPE, OnSelchangeComboTestsignalType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLedConfigDisplay message handlers

void CDlgLedConfigDisplay::OnBtnNosignalGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_LED_NOSIGNAL_CFG struNoSignalCfg = {0};
	struNoSignalCfg.dwSize = sizeof(struNoSignalCfg);
	DWORD dwRet;
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_LED_NOSIGNAL_CFG , m_dwNoSignalOutputNo, &struNoSignalCfg, sizeof(struNoSignalCfg), &dwRet))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_LED_NOSIGNAL_CFG");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_LED_NOSIGNAL_CFG");
	m_cmbNoSignalMode.SetCurSel(struNoSignalCfg.byNoSignalMode-1);
	UpdateData(FALSE);
}

void CDlgLedConfigDisplay::OnBtnNosignalSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_LED_NOSIGNAL_CFG struNoSignalCfg = {0};
	struNoSignalCfg.dwSize = sizeof(struNoSignalCfg);
	struNoSignalCfg.byNoSignalMode = m_cmbNoSignalMode.GetCurSel()+1;
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_LED_NOSIGNAL_CFG , m_dwNoSignalOutputNo, &struNoSignalCfg, sizeof(struNoSignalCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_LED_NOSIGNAL_CFG");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_LED_NOSIGNAL_CFG");
}

void CDlgLedConfigDisplay::OnBtnTestsignalGet() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_LED_TEST_SIGNAL_CFG struSignalCfg = {0};
	struSignalCfg.dwSize = sizeof(struSignalCfg);
	DWORD dwRet;
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_LED_TEST_SIGNAL_CFG , -1, &struSignalCfg, sizeof(struSignalCfg), &dwRet))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_LED_TEST_SIGNAL_CFG");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_LED_TEST_SIGNAL_CFG");
	m_bTestSignalEnable = struSignalCfg.byEnabled;
	if (struSignalCfg.bySignalType == 0xff) //自定义
	{
		m_cmbTestSignalType.SetCurSel(m_cmbTestSignalType.GetCount()-1);
	}
	else
	{
		m_cmbTestSignalType.SetCurSel(struSignalCfg.bySignalType-1);
	}
	m_dwSignalBlue = struSignalCfg.struSignalColor.byBlue;
	m_dwSignalGreen = struSignalCfg.struSignalColor.byGreen;
	m_dwSignalRed = struSignalCfg.struSignalColor.byRed;
	UpdateData(FALSE);
	OnSelchangeComboTestsignalType();
}

void CDlgLedConfigDisplay::OnBtnTestsignalSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_LED_TEST_SIGNAL_CFG struSignalCfg = {0};
	struSignalCfg.dwSize = sizeof(struSignalCfg);
	struSignalCfg.byEnabled = m_bTestSignalEnable;
	struSignalCfg.bySignalType = m_bySignalType;
	struSignalCfg.struSignalColor.byBlue = m_dwSignalBlue;
	struSignalCfg.struSignalColor.byGreen = m_dwSignalGreen;
	struSignalCfg.struSignalColor.byRed = m_dwSignalRed;
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_LED_TEST_SIGNAL_CFG , -1, &struSignalCfg, sizeof(struSignalCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_LED_TEST_SIGNAL_CFG");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_LED_TEST_SIGNAL_CFG");
}

void CDlgLedConfigDisplay::OnButDisplayParameterGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_LED_DISPLAY_CFG struDisplayCfg = {0};
	struDisplayCfg.dwSize = sizeof(struDisplayCfg);
	NET_DVR_LED_RECV_CARD_CFG_COND struCfgCond = {0};
	struCfgCond.dwSize = sizeof(struCfgCond);
	if (m_iDisplayType == 0) //接收卡
	{
		DWORD dwRet;
		if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_LED_DISPLAY_CFG , m_dwPort, &struDisplayCfg, sizeof(struDisplayCfg), &dwRet))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_LED_DISPLAY_CFG");
			return;
		}
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_LED_DISPLAY_CFG");
	}
	else //LED显示屏
	{
		struCfgCond.dwOutputNo = m_dwPort;
		struCfgCond.struPosStart.wColumn = m_dwStartCol;
		struCfgCond.struPosStart.wLine = m_dwStartRow;
		struCfgCond.struPosEnd.wColumn = m_dwEndCol;
		struCfgCond.struPosEnd.wLine = m_dwEndRow;
		if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_LED_SCREEN_DISPLAY_CFG, 1, &struCfgCond, sizeof(struCfgCond), NULL, &struDisplayCfg, sizeof(struDisplayCfg)))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_LED_SCREEN_DISPLAY_CFG");
			return;
		}
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_LED_SCREEN_DISPLAY_CFG");
	}
	m_dwBlue = struDisplayCfg.struColorTemp.byBlue;
	m_dwBlueOffset = struDisplayCfg.struColorTemp.byBlueOffset;
	m_dwGreen = struDisplayCfg.struColorTemp.byGreen;
	m_dwGreenOffset = struDisplayCfg.struColorTemp.byGreenOffset;
	m_dwRed = struDisplayCfg.struColorTemp.byRed;
	m_dwRedOffset = struDisplayCfg.struColorTemp.byRedOffset;
	if (struDisplayCfg.struVoutCfg.byDisplayMode == 0xff) //自定义
	{
		m_cmbDisplayMode.SetCurSel(m_cmbDisplayMode.GetCount()-1);
	}
	else
	{
		m_cmbDisplayMode.SetCurSel(struDisplayCfg.struVoutCfg.byDisplayMode-1);
	}
	m_dwLight = struDisplayCfg.struVoutCfg.byBrightnessLevel;
	m_dwContrast = struDisplayCfg.struVoutCfg.byContrastLevel;
	m_dwHue = struDisplayCfg.struVoutCfg.byHueLevel;
	m_cmbImageMode.SetCurSel(struDisplayCfg.struVoutCfg.byImageMode);
	m_dwSaturation = struDisplayCfg.struVoutCfg.bySaturationLevel;
	m_dwSharpness = struDisplayCfg.struVoutCfg.bySharpnessLevel;
	UpdateData(FALSE);
	OnSelchangeComboDisplayDisplayMode();
}

void CDlgLedConfigDisplay::OnButDisplayParameterSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_LED_DISPLAY_CFG struDisplayCfg = {0};
	struDisplayCfg.dwSize = sizeof(struDisplayCfg);
	NET_DVR_LED_RECV_CARD_CFG_COND struCfgCond = {0};
	struCfgCond.dwSize = sizeof(struCfgCond);
	struDisplayCfg.struColorTemp.byBlue = m_dwBlue;
	struDisplayCfg.struColorTemp.byBlueOffset = m_dwBlueOffset;
	struDisplayCfg.struColorTemp.byGreen = m_dwGreen;
	struDisplayCfg.struColorTemp.byGreenOffset = m_dwGreenOffset;
	struDisplayCfg.struColorTemp.byRed = m_dwRed;
	struDisplayCfg.struColorTemp.byRedOffset = m_dwRedOffset;
	struDisplayCfg.struVoutCfg.byImageMode = m_cmbImageMode.GetCurSel();
	struDisplayCfg.struVoutCfg.byDisplayMode = m_byDisplayMode;
	struDisplayCfg.struVoutCfg.byBrightnessLevel = m_dwLight;
	struDisplayCfg.struVoutCfg.byContrastLevel = m_dwContrast;
	struDisplayCfg.struVoutCfg.byHueLevel = m_dwHue;
	struDisplayCfg.struVoutCfg.bySaturationLevel = m_dwSaturation;
	struDisplayCfg.struVoutCfg.bySharpnessLevel = m_dwSharpness;
	if (m_iDisplayType == 0) //接收卡
	{
		if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_LED_DISPLAY_CFG , m_dwPort, &struDisplayCfg, sizeof(struDisplayCfg)))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_LED_DISPLAY_CFG");
			return;
		}
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_LED_DISPLAY_CFG");
	}
	else //LED显示屏
	{
		struCfgCond.dwOutputNo = m_dwPort;
		struCfgCond.struPosStart.wColumn = m_dwStartCol;
		struCfgCond.struPosStart.wLine = m_dwStartRow;
		struCfgCond.struPosEnd.wColumn = m_dwEndCol;
		struCfgCond.struPosEnd.wLine = m_dwEndRow;
		if (!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_SET_LED_SCREEN_DISPLAY_CFG, 1, &struCfgCond, sizeof(struCfgCond), NULL, &struDisplayCfg, sizeof(struDisplayCfg)))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_LED_SCREEN_DISPLAY_CFG");
			return;
		}
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_LED_SCREEN_DISPLAY_CFG");
	}
}

void CDlgLedConfigDisplay::OnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CDlgLedConfigDisplay::OnSelchangeComboDisplayDisplayMode() 
{
	// TODO: Add your control notification handler code here
	m_byDisplayMode = m_cmbDisplayMode.GetCurSel()+1;
	if (m_byDisplayMode == m_cmbDisplayMode.GetCount()) //自定义
	{
		m_byDisplayMode = 0xff;
		GetDlgItem(IDC_EDT_DISPLAY_PARAMETER_HUE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDT_DISPLAY_PARAMETER_LIGHT)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDT_DISPLAY_PARAMETER_SATURATION)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDT_DISPLAY_PARAMETER_SHARPNESS)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDT_DISPLAY_PARAMETER_CONTRAST)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDT_DISPLAY_PARAMETER_HUE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_DISPLAY_PARAMETER_LIGHT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_DISPLAY_PARAMETER_SATURATION)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_DISPLAY_PARAMETER_SHARPNESS)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_DISPLAY_PARAMETER_CONTRAST)->EnableWindow(FALSE);
	}
}

void CDlgLedConfigDisplay::OnSelchangeComboDisplayType() 
{
	// TODO: Add your control notification handler code here
	m_iDisplayType = m_cmbDisplayType.GetCurSel();
	if (m_iDisplayType == 0) //接收卡
	{
		GetDlgItem(IDC_EDIT_DISPLAY_START_COL)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DISPLAY_START_ROW)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DISPLAY_END_COL)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DISPLAY_END_ROW)->EnableWindow(FALSE);
	}
	else //LED显示屏
	{
		GetDlgItem(IDC_EDIT_DISPLAY_START_COL)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DISPLAY_START_ROW)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DISPLAY_END_COL)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DISPLAY_END_ROW)->EnableWindow(TRUE);
	}
}

void CDlgLedConfigDisplay::OnSelchangeComboTestsignalType() 
{
	// TODO: Add your control notification handler code here
	m_bySignalType = m_cmbTestSignalType.GetCurSel()+1;
	if (m_bySignalType == m_cmbTestSignalType.GetCount()) //自定义
	{
		m_bySignalType = 0xff;
		GetDlgItem(IDC_EDIT_TESTSIGNAL_BLUE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_TESTSIGNAL_GREEN)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_TESTSIGNAL_RED)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_TESTSIGNAL_BLUE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_TESTSIGNAL_GREEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_TESTSIGNAL_RED)->EnableWindow(FALSE);
	}
}

BOOL CDlgLedConfigDisplay::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cmbDisplayType.SetCurSel(0);
	m_iDisplayType = 0;
	OnSelchangeComboDisplayType();
	m_cmbDisplayMode.SetCurSel(0);
	m_byDisplayMode = 0;
	OnSelchangeComboDisplayDisplayMode();
	m_cmbTestSignalType.SetCurSel(0);
	m_bySignalType = 0;
	OnSelchangeComboTestsignalType();
	
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
