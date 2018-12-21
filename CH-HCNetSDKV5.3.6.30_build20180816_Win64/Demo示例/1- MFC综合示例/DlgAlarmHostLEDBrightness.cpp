// DlgAlarmHostLEDBrightness.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmHostLEDBrightness.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostLEDBrightness dialog


CDlgAlarmHostLEDBrightness::CDlgAlarmHostLEDBrightness(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmHostLEDBrightness::IDD, pParent)
	,m_iDeviceIndex(-1)
	, m_lUserID(-1)
{
	//{{AFX_DATA_INIT(CDlgAlarmHostLEDBrightness)
	m_radioCtrl = -1;
	m_chTimeValid = FALSE;
	//}}AFX_DATA_INIT

	memset(&m_struBrightnessStep, 0, sizeof(m_struBrightnessStep));
}


void CDlgAlarmHostLEDBrightness::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmHostLEDBrightness)
	DDX_Control(pDX, IDC_COMBO_BRIGHTNESS_TIME, m_cmTime);
	DDX_Control(pDX, IDC_SLIDER_BRIGHTNESS, m_sliderBrightness);
	DDX_Radio(pDX, IDC_RADIO_MANUAL, m_radioCtrl);
	DDX_Check(pDX, IDC_CHECK_VALID, m_chTimeValid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmHostLEDBrightness, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmHostLEDBrightness)
	ON_BN_CLICKED(IDC_RADIO_MANUAL, OnRadioManual)
	ON_BN_CLICKED(IDC_RADIO_TIMER, OnRadioTimer)
//	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_BRIGHTNESS, OnCustomdrawSliderBrightness)
	ON_BN_CLICKED(IDC_BTN_COPYTOALL, OnBtnCopytoall)
	ON_CBN_SELCHANGE(IDC_COMBO_BRIGHTNESS_TIME, OnSelchangeComboBrightnessTime)
	ON_BN_CLICKED(IDC_BTN_GET_TIMER_BRIGHTNESS, OnBtnGetTimerBrightness)
	ON_BN_CLICKED(IDC_BTN_SET_TIMER_BRIGHTNESS, OnBtnSetTimerBrightness)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostLEDBrightness message handlers

BOOL CDlgAlarmHostLEDBrightness::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char szLan[128] = {0};
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;

	memset(&m_struLEDStatus, 0, sizeof(m_struLEDStatus));
	m_struLEDStatus.dwSize = sizeof(m_struLEDStatus);
	//获取手动亮度调节的亮度值
	DWORD dwReturn;
	m_struLEDStatus.dwSize = sizeof(m_struLEDStatus);
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_LED_STATUS, 0, &m_struLEDStatus, sizeof(m_struLEDStatus), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_LED_STATUS FAILED");
		MessageBox("NET_DVR_GET_LED_STATUS FAILED");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_LED_STATUS SUCC");
	}

	//亮度调节时间段
	CString csStr;
	for (int i=0; i<48; i++)
	{
		if (i%2)//半点
		{
			sprintf(m_szTemp, "%d:30", i/2);	
		}
		else
		{
			sprintf(m_szTemp, "%d:00", i/2);	
		}
		csStr.Format(m_szTemp);
		m_cmTime.AddString(m_szTemp);
		m_cmTime.SetItemData(i, i);
	}
	
	//亮度刻度条
	m_sliderBrightness.SetRange(0, 15, TRUE);
	m_sliderBrightness.SetLineSize(1);
	m_sliderBrightness.SetPageSize(5);
	m_sliderBrightness.SetPos(0);
	m_sliderBrightness.SetTicFreq(1); //显示刻度的间隔
	m_sliderBrightness.SetPos(m_struLEDStatus.byBrightness);
	g_StringLanType(szLan, "亮度值", "Brightness");
	sprintf((char*)m_szTemp, "%s: %d", szLan, m_struLEDStatus.byBrightness);
	SetDlgItemText(IDC_STATIC_BRIGHTNESS, m_szTemp);
	m_radioCtrl = 0;
	UpdateData(FALSE);
	OnRadioManual();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlarmHostLEDBrightness::OnRadioManual() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_radioCtrl == 0)
	{
		GetDlgItem(IDC_COMBO_BRIGHTNESS_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_COPYTOALL)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_GET_TIMER_BRIGHTNESS)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SET_TIMER_BRIGHTNESS)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK_VALID)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_TIME)->EnableWindow(FALSE);
	}
	DWORD dwReturn;
	m_struLEDStatus.dwSize = sizeof(m_struLEDStatus);
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_LED_STATUS, 0, &m_struLEDStatus, sizeof(m_struLEDStatus), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_LED_STATUS FAILED");
		MessageBox("NET_DVR_GET_LED_STATUS FAILED");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_LED_STATUS SUCC");
	}
	m_sliderBrightness.SetPos(m_struLEDStatus.byBrightness);
	UpdateData(FALSE);
}

void CDlgAlarmHostLEDBrightness::OnRadioTimer() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_radioCtrl == 1)
	{
		GetDlgItem(IDC_COMBO_BRIGHTNESS_TIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_COPYTOALL)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_GET_TIMER_BRIGHTNESS)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_SET_TIMER_BRIGHTNESS)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_VALID)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_TIME)->EnableWindow(TRUE);
	}
	UpdateData(FALSE);
	OnBtnGetTimerBrightness();
}

void CDlgAlarmHostLEDBrightness::OnBtnCopytoall() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	for (int i=0; i<TIME_SEGMENT_A_DAY; i++)
	{
		m_struBrightnessStep.byBrightnessStep[i] = m_sliderBrightness.GetPos();
	}
}

void CDlgAlarmHostLEDBrightness::OnSelchangeComboBrightnessTime() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	int iIndex = m_cmTime.GetCurSel();
	m_sliderBrightness.SetPos(m_struBrightnessStep.byBrightnessStep[iIndex]);
	g_StringLanType(szLan, "亮度值", "Brightness");
	sprintf((char*)m_szTemp, "%s: %d", szLan, m_struBrightnessStep.byBrightnessStep[iIndex]);
	SetDlgItemText(IDC_STATIC_BRIGHTNESS, m_szTemp);
	UpdateData(FALSE);
}

void CDlgAlarmHostLEDBrightness::OnBtnGetTimerBrightness() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn;
	m_struBrightnessStep.dwSize = sizeof(m_struBrightnessStep);
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_LED_TIMER_BRIGHTNESS, 0, &m_struBrightnessStep, sizeof(m_struBrightnessStep), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_LED_TIMER_BRIGHTNESS FAILED");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_LED_TIMER_BRIGHTNESS SUCC");
	}
	m_chTimeValid = m_struBrightnessStep.byValid;
	m_cmTime.SetCurSel(0);
	UpdateData(FALSE);
	OnSelchangeComboBrightnessTime();
}

void CDlgAlarmHostLEDBrightness::OnBtnSetTimerBrightness() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struBrightnessStep.dwSize = sizeof(m_struBrightnessStep);
	m_struBrightnessStep.byValid = m_chTimeValid;
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_LED_TIMER_BRIGHTNESS, 0, &m_struBrightnessStep, sizeof(m_struBrightnessStep)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_LED_TIMER_BRIGHTNESS FAILED");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_LED_TIMER_BRIGHTNESS SUCC");
	}
}

void CDlgAlarmHostLEDBrightness::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	if ((GetDlgItem(IDC_SLIDER_BRIGHTNESS) != pScrollBar) || (nSBCode != SB_ENDSCROLL))
	{
		return;
	}
	char szLan[128] = {0};
	UpdateData(TRUE);
	g_StringLanType(szLan, "亮度值", "Brightness");
	sprintf((char*)m_szTemp, "%s: %d", szLan, m_sliderBrightness.GetPos());
	SetDlgItemText(IDC_STATIC_BRIGHTNESS, m_szTemp);
	UpdateData(FALSE);
	//手动调节亮度
	if (m_radioCtrl == 0)
	{
		memset(&m_struCtrlParam, 0, sizeof(m_struCtrlParam));
		m_struCtrlParam.dwSize = sizeof(m_struCtrlParam);
		m_struCtrlParam.wChan = 0;
		m_struCtrlParam.dwControlParam = m_sliderBrightness.GetPos();
		if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_SET_LED_BRIGHTNESS, &m_struCtrlParam, sizeof(m_struCtrlParam)))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_LED_BRIGHTNESS FAILED");
			return;
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_LED_BRIGHTNESS SUCC");
		}
	}
	//分时亮度调节
	else if(m_radioCtrl == 1)
	{
		m_struBrightnessStep.byBrightnessStep[m_cmTime.GetCurSel()] = m_sliderBrightness.GetPos();
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
