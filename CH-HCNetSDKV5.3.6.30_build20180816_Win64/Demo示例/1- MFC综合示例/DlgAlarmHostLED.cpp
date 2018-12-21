// DlgAlarmHostLED.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmHostLED.h"
#include "DlgLEDTimerSwitch.h"
#include "DlgAlarmHostLEDBrightness.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostLED dialog


CDlgAlarmHostLED::CDlgAlarmHostLED(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmHostLED::IDD, pParent)
	, m_iDeviceIndex(-1)
	, m_lUserID(-1)
{
	//{{AFX_DATA_INIT(CDlgAlarmHostLED)
	m_csLEDContent = _T("");
	m_csLEDName = _T("");
	m_checkTimeDay = COleDateTime::GetCurrentTime();
	m_checkTimeTime = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}


void CDlgAlarmHostLED::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmHostLED)
	DDX_Control(pDX, IDC_COMBO_OEPOLARITY, m_cmOEPolarity);
	DDX_Control(pDX, IDC_COMBO_LEDWIDTH, m_cmLEDWidth);
	DDX_Control(pDX, IDC_COMBO_TRANSMODE, m_cmTranseMode);
	DDX_Control(pDX, IDC_COMBO_SCANTYPE, m_cmScanType);
	DDX_Control(pDX, IDC_COMBO_PROTOCOLTYPE, m_cmProtocolType);
	DDX_Control(pDX, IDC_COMBO_LEDHEIGHT, m_cmLEDHeight);
	DDX_Control(pDX, IDC_COMBO_LEDCOLOR, m_cmLEDColor);
	DDX_Control(pDX, IDC_COMBO_DATAPOLARITY, m_cmDataPolarity);
	DDX_Control(pDX, IDC_COMBO_CONTENTSTAYTIME, m_cmContentStayTime);
	DDX_Control(pDX, IDC_COMBO_CONTENTSPEED, m_cmContentSpeed);
	DDX_Control(pDX, IDC_COMBO_CONTENTACT, m_cmContentAct);
	DDX_Text(pDX, IDC_EDIT_LEDCONTENT, m_csLEDContent);
	DDX_Text(pDX, IDC_LED_NAME, m_csLEDName);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_CHECKTIME_DAY, m_checkTimeDay);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_CHECKTIME_TIME, m_checkTimeTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmHostLED, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmHostLED)
	ON_BN_CLICKED(IDC_BTN_GET_LEDPARAM, OnBtnGetLedparam)
	ON_BN_CLICKED(IDC_BTN_SET_LEDPARAM, OnBtnSetLedparam)
	ON_BN_CLICKED(IDC_BTN_GET_LEDCONTENT, OnBtnGetLedcontent)
	ON_BN_CLICKED(IDC_BTN_SET_LEDCONTENT, OnBtnSetLedcontent)
	ON_BN_CLICKED(IDC_BTN_LED_TURNON, OnBtnLedTurnon)
	ON_BN_CLICKED(IDC_BTN_LED_TURNOFF, OnBtnLedTurnoff)
	ON_BN_CLICKED(IDC_BTN_CHECKTIME, OnBtnChecktime)
	ON_BN_CLICKED(IDC_BTN_LED_BRIGHTNESS, OnBtnLedBrightness)
	ON_BN_CLICKED(IDC_BTN_TIMER_SWITCH, OnBtnTimerSwitch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostLED message handlers

BOOL CDlgAlarmHostLED::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char szLan[128] = {0};
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;

	memset(&m_struLEDCfg, 0, sizeof(m_struLEDCfg));
	memset(&m_struLEDContent, 0, sizeof(m_struLEDContent));
	memset(&m_struLEDStatus, 0, sizeof(m_struLEDStatus));

	//获取LED开关机状态
//	DWORD dwReturn;
// 	m_struLEDStatus.dwSize = sizeof(m_struLEDStatus);
// 	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_LED_STATUS, 0, &m_struLEDStatus, sizeof(m_struLEDStatus), &dwReturn))
// 	{
// 		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_LED_STATUS FAILED");
// 		MessageBox("NET_DVR_GET_LED_STATUS FAILED");
// 	}
// 	else
// 	{
// 		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_LED_STATUS SUCC");
// 	}
// 
// 	//开机状态
// 	if (m_struLEDStatus.bySwitchState == 1)
// 	{
// 		GetDlgItem(IDC_BTN_LED_TURNON)->EnableWindow(FALSE);
// 		GetDlgItem(IDC_BTN_LED_TURNOFF)->EnableWindow(TRUE);
// 	}
// 	//关机状态
// 	else if(m_struLEDStatus.bySwitchState == 2)
// 	{
// 		GetDlgItem(IDC_BTN_LED_TURNON)->EnableWindow(TRUE);
// 		GetDlgItem(IDC_BTN_LED_TURNOFF)->EnableWindow(FALSE);
// 	}

	int i = 16;
	CString csStr;

	//分辨率
	for (i=0; i<2048/16; i++)
	{
		csStr.Format("%d", (i+1)*16);
		m_cmLEDHeight.AddString(csStr);
		m_cmLEDHeight.SetItemData(i, (i+1)*16);
		m_cmLEDWidth.AddString(csStr);
		m_cmLEDWidth.SetItemData(i, (i+1)*16);
	}

	//屏显速度 1-24
	for (i=0; i<24; i++)
	{
		csStr.Format("%d", i+1);
		m_cmContentSpeed.AddString(csStr);
	}

	//屏显停留时间
	for (i=0; i<256; i++)
	{
		csStr.Format("%.1f", (float)i/2);
		m_cmContentStayTime.AddString(csStr);
		m_cmContentStayTime.SetItemData(i, i);
	}

	//通信方式
	g_StringLanType(szLan, "串口通信", "Serial Communication");
	m_cmTranseMode.ResetContent();
	m_cmTranseMode.AddString(szLan);

	//颜色
	m_cmLEDColor.ResetContent();
	g_StringLanType(szLan, "单色", "monochrome");
	m_cmLEDColor.AddString(szLan);
	g_StringLanType(szLan, "双色", "two-color");
	m_cmLEDColor.AddString(szLan);
	g_StringLanType(szLan, "256级灰度双基色", "256 grayscale dual color");
	m_cmLEDColor.AddString(szLan);
	g_StringLanType(szLan, "全彩色", "full-color");
	m_cmLEDColor.AddString(szLan);

	
	//极性	
	m_cmDataPolarity.ResetContent();
	g_StringLanType(szLan, "负极", "Negative electrode");
	m_cmDataPolarity.AddString(szLan);
	g_StringLanType(szLan, "正极", "Positive electrode");
	m_cmDataPolarity.AddString(szLan);
	UpdateData(FALSE);

	//电平
	m_cmOEPolarity.ResetContent();
	g_StringLanType(szLan, "低电平有效", "Active-low");
	m_cmOEPolarity.AddString(szLan);
	g_StringLanType(szLan, "高电平有效", "Active-high");
	m_cmOEPolarity.AddString(szLan);
	UpdateData(FALSE);

	//字符显示动作
	m_cmContentAct.ResetContent();
	g_StringLanType(szLan, "静态", "Static");
	m_cmContentAct.AddString(szLan);
	g_StringLanType(szLan, "快速打出", "Quick play");
	m_cmContentAct.AddString(szLan);
	g_StringLanType(szLan, "向左移动", "Move to the left");
	m_cmContentAct.AddString(szLan);
	g_StringLanType(szLan, "向右移动", "Move to the right");
	m_cmContentAct.AddString(szLan);
	g_StringLanType(szLan, "向上移动", "Move up");
	m_cmContentAct.AddString(szLan);
	g_StringLanType(szLan, "向下移动", "Move down");
	m_cmContentAct.AddString(szLan);
	//
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlarmHostLED::OnBtnGetLedparam() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturnLen = 0;
	m_struLEDCfg.dwSize = sizeof(m_struLEDCfg);
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_LED_SCREEN_CFG, 0, &m_struLEDCfg, sizeof(m_struLEDCfg), &dwReturnLen))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_LED_SCREEN_CFG FAILED");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_LED_SCREEN_CFG SUCC");
	}
	m_csLEDName.Format("%s", m_struLEDCfg.sLEDName);
	m_cmTranseMode.SetCurSel(m_struLEDCfg.byTransMode - 1);
	m_cmProtocolType.SetCurSel(0);
	m_cmLEDColor.SetCurSel(m_struLEDCfg.byLEDColor - 1);
	m_cmDataPolarity.SetCurSel(m_struLEDCfg.byDataPolarity);
	m_cmOEPolarity.SetCurSel(m_struLEDCfg.byOEPolarity);
	m_cmScanType.SetCurSel(m_struLEDCfg.byScanMode - 1);
	int iIndex;
	memset(m_szTemp, 0, sizeof(m_szTemp));
	itoa(m_struLEDCfg.wLEDWidth, m_szTemp, 10);
	iIndex = m_cmLEDWidth.FindStringExact(0, m_szTemp);
	m_cmLEDWidth.SetCurSel(iIndex);

	memset(m_szTemp, 0, sizeof(m_szTemp));
	itoa(m_struLEDCfg.wLEDHeight, m_szTemp, 10);
	iIndex = m_cmLEDHeight.FindStringExact(0, m_szTemp);
	m_cmLEDHeight.SetCurSel(iIndex);
	UpdateData(FALSE);
}

void CDlgAlarmHostLED::OnBtnSetLedparam() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struLEDCfg.dwSize = sizeof(m_struLEDCfg);
	sprintf((char*)m_struLEDCfg.sLEDName, "%s", m_csLEDName);
	m_struLEDCfg.byTransMode = m_cmTranseMode.GetCurSel() + 1;
	m_struLEDCfg.byProtocolType = 0;
	m_struLEDCfg.byLEDColor = m_cmLEDColor.GetCurSel() + 1;
	m_struLEDCfg.byDataPolarity = m_cmDataPolarity.GetCurSel();
	m_struLEDCfg.byOEPolarity = m_cmOEPolarity.GetCurSel();
	m_struLEDCfg.byScanMode = m_cmScanType.GetCurSel() + 1;
	m_struLEDCfg.wLEDHeight = m_cmLEDHeight.GetItemData(m_cmLEDHeight.GetCurSel());
	m_struLEDCfg.wLEDWidth = m_cmLEDWidth.GetItemData(m_cmLEDWidth.GetCurSel());

	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_LED_SCREEN_CFG, 0, &m_struLEDCfg, sizeof(m_struLEDCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_LED_SCREEN_CFG FAILED");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_LED_SCREEN_CFG SUCC");
	}
}

void CDlgAlarmHostLED::OnBtnGetLedcontent() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturnLen = 0;
	m_struLEDContent.dwSize = sizeof(m_struLEDContent);
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_LED_CONTENT_CFG, 0, &m_struLEDContent, sizeof(m_struLEDContent), &dwReturnLen))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_LED_CONTENT_CFG FAILED");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_LED_CONTENT_CFG SUCC");
	}
	char sContentTemp[513] = {0};
	memcpy(sContentTemp, m_struLEDContent.sLEDContent, MAX_CONTENT_LEN);
	m_csLEDContent.Format("%s", sContentTemp);
	m_cmContentAct.SetCurSel(m_struLEDContent.byContentAct -1);
	m_cmContentSpeed.SetCurSel(m_struLEDContent.byContentSpeed - 1);
	int iIndex = m_struLEDContent.byContentStayTime;
	m_cmContentStayTime.SetCurSel(iIndex);
	UpdateData(FALSE);
}



void CDlgAlarmHostLED::OnBtnSetLedcontent() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struLEDContent.dwSize = sizeof(m_struLEDContent);
	sprintf((char*)m_struLEDContent.sLEDContent, "%s", m_csLEDContent);
	m_struLEDContent.byContentAct = m_cmContentAct.GetCurSel() + 1;
	m_struLEDContent.byContentSpeed = m_cmContentSpeed.GetCurSel() + 1;
	m_struLEDContent.byContentStayTime = m_cmContentStayTime.GetItemData(m_cmContentStayTime.GetCurSel());
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_LED_CONTENT_CFG, 0, &m_struLEDContent, sizeof(m_struLEDContent)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_LED_CONTENT_CFG FAILED");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_LED_CONTENT_CFG SUCC");
	}
}


void CDlgAlarmHostLED::OnBtnLedTurnon() 
{
	// TODO: Add your control notification handler code here
	memset(&m_struCtrlParam, 0, sizeof(NET_DVR_CONTROL_PARAM));
	m_struCtrlParam.dwSize = sizeof(NET_DVR_CONTROL_PARAM);
	m_struCtrlParam.wChan = 0;
	if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_TURNON_LED, &m_struCtrlParam, sizeof(m_struCtrlParam)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_TURNON_LED FAILED");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_TURNON_LED SUCC");
	}
}

void CDlgAlarmHostLED::OnBtnLedTurnoff() 
{
	// TODO: Add your control notification handler code here
	memset(&m_struCtrlParam, 0, sizeof(NET_DVR_CONTROL_PARAM));
	m_struCtrlParam.dwSize = sizeof(NET_DVR_CONTROL_PARAM);
	m_struCtrlParam.wChan = 0;
	if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_TURNOFF_LED, &m_struCtrlParam, sizeof(m_struCtrlParam)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_TURNOFF_LED FAILED");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_TURNOFF_LED SUCC");
	}
}

void CDlgAlarmHostLED::OnBtnChecktime() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struCheckTime.wYear = m_checkTimeDay.GetYear();
	m_struCheckTime.byMonth = m_checkTimeDay.GetMonth();
	m_struCheckTime.byDay = m_checkTimeDay.GetDay();
	m_struCheckTime.byHour = m_checkTimeTime.GetHour();
	m_struCheckTime.byMinute = m_checkTimeTime.GetMinute();
 	m_struCheckTime.bySecond = m_checkTimeTime.GetSecond();
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_LED_CHECKTIME, 0, &m_struCheckTime, sizeof(m_struCheckTime)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_LED_CHECKTIME FAILED");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_LED_CHECKTIME SUCC");
	}
}

void CDlgAlarmHostLED::OnBtnLedBrightness() 
{
	// TODO: Add your control notification handler code here
	CDlgAlarmHostLEDBrightness dlg;
	dlg.DoModal();
}


void CDlgAlarmHostLED::OnBtnTimerSwitch() 
{
	// TODO: Add your control notification handler code here
	CDlgLEDTimerSwitch dlg;
	dlg.DoModal();
}
