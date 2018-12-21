// DlgLcdSwitchCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgLcdSwitchCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLcdSwitchCfg dialog


CDlgLcdSwitchCfg::CDlgLcdSwitchCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLcdSwitchCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLcdSwitchCfg)
	m_dwDelayBootTme = 0;
	m_ctHms = COleDateTime::GetCurrentTime();
	m_ctHmsTp1 = COleDateTime::GetCurrentTime();
	m_ctHmsTp2 = COleDateTime::GetCurrentTime();
	m_ctHmsTp3 = COleDateTime::GetCurrentTime();
	m_ctYmd = COleDateTime::GetCurrentTime();
	m_byWallNo = 0;
	m_bTp1 = FALSE;
	m_bTp2 = FALSE;
	m_bTp3 = FALSE;
	m_bTp4 = FALSE;
	m_bHolidayTp = FALSE;
	m_ctHmsTp4 = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}


void CDlgLcdSwitchCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLcdSwitchCfg)
	DDX_Control(pDX, IDC_COMBO_WEEK_DAY, m_comboWeekDay);
	DDX_Control(pDX, IDC_COMBO_SWITCH_TYPE4, m_comboSwitchType4);
	DDX_Control(pDX, IDC_COMBO_SWITCH_TYPE3, m_comboSwitchType3);
	DDX_Control(pDX, IDC_COMBO_SWITCH_TYPE2, m_comboSwitchType2);
	DDX_Control(pDX, IDC_COMBO_SWITCH_TYPE1, m_comboSwitchType1);
	DDX_Control(pDX, IDC_COMBO_SWITCH_TYPE_HOLIDAY, m_comboSwitchTypeHoliday);
	DDX_Control(pDX, IDC_COMBO_HOLIDAY_TP_NO, m_comboHolidayNo);
	DDX_Control(pDX, IDC_COMBO_COPY_WEEKDAY, m_comboCopy);
	DDX_Text(pDX, IDC_EDIT_DELAY_BOOT_TIME, m_dwDelayBootTme);
	DDX_DateTimeCtrl(pDX, IDC_HMS, m_ctHms);
	DDX_DateTimeCtrl(pDX, IDC_HMS_TP1, m_ctHmsTp1);
	DDX_DateTimeCtrl(pDX, IDC_HMS_TP2, m_ctHmsTp2);
	DDX_DateTimeCtrl(pDX, IDC_HMS_TP3, m_ctHmsTp3);
	DDX_DateTimeCtrl(pDX, IDC_YMD, m_ctYmd);
	DDX_Text(pDX, IDC_EDIT_WALL_NO, m_byWallNo);
	DDX_Check(pDX, IDC_CHK_TP1, m_bTp1);
	DDX_Check(pDX, IDC_CHK_TP2, m_bTp2);
	DDX_Check(pDX, IDC_CHK_TP3, m_bTp3);
	DDX_Check(pDX, IDC_CHK_TP4, m_bTp4);
	DDX_Check(pDX, IDC_CHK_HOLIDAY_TP, m_bHolidayTp);
	DDX_DateTimeCtrl(pDX, IDC_HMS_TP4, m_ctHmsTp4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLcdSwitchCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgLcdSwitchCfg)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_LCD_SWITCH_OK, OnBtnLcdSwitchOk)
	ON_BN_CLICKED(IDC_BTN_LCD_SWITCH_COPY, OnBtnLcdSwitchCopy)
	ON_BN_CLICKED(IDC_BTN_LCD_HOLIDAY_OK, OnBtnLcdHolidayOk)
	ON_CBN_SELCHANGE(IDC_COMBO_WEEK_DAY, OnSelchangeComboWeekDay)
	ON_CBN_SELCHANGE(IDC_COMBO_HOLIDAY_TP_NO, OnSelchangeComboHolidayTpNo)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLcdSwitchCfg message handlers

BOOL CDlgLcdSwitchCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    memset(&m_struWallArea, 0, sizeof(m_struWallArea));
    memset(&m_struTimeSwitch, 0, sizeof(m_struTimeSwitch));
    memset(&m_struDelayTime, 0, sizeof(m_struDelayTime));

    m_struDelayTime.dwSize = sizeof(m_struDelayTime);
    m_struTimeSwitch.dwSize = sizeof(m_struTimeSwitch);
    m_struWallArea.dwSize = sizeof(m_struWallArea);

    int i = 0;
    CString cs;

    for (i = 0; i < 16; i++)
    {
        cs.Format("%d", i + 1);
        m_comboHolidayNo.AddString(cs);
    }
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLcdSwitchCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

    char szLan[64] = {0};

    m_struWallArea.byWallNo = m_byWallNo;
    m_struDelayTime.dwDelayTime = m_dwDelayBootTme;

    OnBtnLcdSwitchOk();
    OnBtnLcdHolidayOk();

    if (!NET_DVR_SetDVRConfig(m_lUserId, NET_DVR_SET_POWERON_DELAY_CFG, 0, &m_struDelayTime, sizeof(m_struDelayTime)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_POWERON_DELAY_CFG");
        g_StringLanType(szLan, "设置屏幕延时开机参数失败", "Set screen delay boot parameter fail");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_POWERON_DELAY_CFG");
    }

    if (!NET_DVR_SetDeviceConfig(m_lUserId, NET_DVR_SET_SWITCH_CFG, 1, &m_struWallArea, sizeof(m_struWallArea), NULL, &m_struTimeSwitch, sizeof(m_struTimeSwitch)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SWITCH_CFG");
        g_StringLanType(szLan, "设置屏幕定时开关机参数失败", "Set screen timing power on ,power off parameter fail");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_SWITCH_CFG");
    }
}

void CDlgLcdSwitchCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    char szLan[64] = {0};
    DWORD dwReturned = 0;

    m_struWallArea.byWallNo = m_byWallNo;

    if (!NET_DVR_GetDVRConfig(m_lUserId, NET_DVR_GET_POWERON_DELAY_CFG, 0, &m_struDelayTime, sizeof(m_struWallArea), &dwReturned))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_POWERON_DELAY_CFG");
        g_StringLanType(szLan, "获取屏幕延时开关机参数失败", "Get screen delay boot parameter fail");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_POWERON_DELAY_CFG");
        m_dwDelayBootTme = m_struDelayTime.dwDelayTime; 
        UpdateData(FALSE); 
    }

    if (!NET_DVR_GetDeviceConfig(m_lUserId, NET_DVR_GET_SWITCH_CFG, 1, &m_struWallArea, sizeof(m_struWallArea), NULL, &m_struTimeSwitch, sizeof(m_struTimeSwitch)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SWITCH_CFG");
        g_StringLanType(szLan, "获取屏幕定时开关机参数失败", "Get screen timing power on, power off parameter fail");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SWITCH_CFG");
        OnSelchangeComboWeekDay(); 
        OnSelchangeComboHolidayTpNo(); 
    }
	
}

void CDlgLcdSwitchCfg::OnBtnLcdSwitchOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

    int iWeekDay = m_comboWeekDay.GetCurSel();
    if (iWeekDay == CB_ERR)
    {
        return;
    }

    m_struTimeSwitch.struSwitchDayTime[iWeekDay][0].byEnable = m_bTp1;
    m_struTimeSwitch.struSwitchDayTime[iWeekDay][0].bySwitchType = m_comboSwitchType1.GetCurSel();
    m_struTimeSwitch.struSwitchDayTime[iWeekDay][0].struTimePoint.byHour = m_ctHmsTp1.GetHour();
    m_struTimeSwitch.struSwitchDayTime[iWeekDay][0].struTimePoint.byMinute = m_ctHmsTp1.GetMinute();
    m_struTimeSwitch.struSwitchDayTime[iWeekDay][0].struTimePoint.bySecond = m_ctHmsTp1.GetSecond();

    m_struTimeSwitch.struSwitchDayTime[iWeekDay][1].byEnable = m_bTp2;
    m_struTimeSwitch.struSwitchDayTime[iWeekDay][1].bySwitchType = m_comboSwitchType2.GetCurSel();
    m_struTimeSwitch.struSwitchDayTime[iWeekDay][1].struTimePoint.byHour = m_ctHmsTp2.GetHour();
    m_struTimeSwitch.struSwitchDayTime[iWeekDay][1].struTimePoint.byMinute = m_ctHmsTp2.GetMinute();
    m_struTimeSwitch.struSwitchDayTime[iWeekDay][1].struTimePoint.bySecond = m_ctHmsTp2.GetSecond();

    m_struTimeSwitch.struSwitchDayTime[iWeekDay][2].byEnable = m_bTp3;
    m_struTimeSwitch.struSwitchDayTime[iWeekDay][2].bySwitchType = m_comboSwitchType3.GetCurSel();
    m_struTimeSwitch.struSwitchDayTime[iWeekDay][2].struTimePoint.byHour = m_ctHmsTp3.GetHour();
    m_struTimeSwitch.struSwitchDayTime[iWeekDay][2].struTimePoint.byMinute = m_ctHmsTp3.GetMinute();
    m_struTimeSwitch.struSwitchDayTime[iWeekDay][2].struTimePoint.bySecond = m_ctHmsTp3.GetSecond();

    m_struTimeSwitch.struSwitchDayTime[iWeekDay][3].byEnable = m_bTp4;
    m_struTimeSwitch.struSwitchDayTime[iWeekDay][3].bySwitchType = m_comboSwitchType4.GetCurSel();
    m_struTimeSwitch.struSwitchDayTime[iWeekDay][3].struTimePoint.byHour = m_ctHmsTp4.GetHour();
    m_struTimeSwitch.struSwitchDayTime[iWeekDay][3].struTimePoint.byMinute = m_ctHmsTp4.GetMinute();
    m_struTimeSwitch.struSwitchDayTime[iWeekDay][3].struTimePoint.bySecond = m_ctHmsTp4.GetSecond();


}

void CDlgLcdSwitchCfg::OnBtnLcdSwitchCopy() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    int i = 0;
    int iWeekDay = m_comboWeekDay.GetCurSel();
    int iWeekDayCopy = m_comboCopy.GetCurSel();

    if (iWeekDayCopy == CB_ERR || iWeekDay == CB_ERR)
    {
        return;
    }

    OnBtnLcdSwitchOk();

    if (iWeekDayCopy == 0)
    {
        for (i = 0; i < MAX_DAYS; i++)
        {
            memcpy(m_struTimeSwitch.struSwitchDayTime[i], m_struTimeSwitch.struSwitchDayTime[iWeekDay], \
        sizeof(m_struTimeSwitch.struSwitchDayTime[i]));
        }
    }
    else
    {
        memcpy(m_struTimeSwitch.struSwitchDayTime[iWeekDayCopy], m_struTimeSwitch.struSwitchDayTime[iWeekDay], \
        sizeof(m_struTimeSwitch.struSwitchDayTime[iWeekDayCopy]));
    }    	
}

void CDlgLcdSwitchCfg::OnBtnLcdHolidayOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

    int iHolidaySel = m_comboHolidayNo.GetCurSel();
    if (iHolidaySel == CB_ERR)
    {
        return;
    }

    m_struTimeSwitch.struSwitchTimePoint[iHolidaySel].byEnable = m_bHolidayTp;
    m_struTimeSwitch.struSwitchTimePoint[iHolidaySel].bySwitchType = m_comboSwitchTypeHoliday.GetCurSel();
    m_struTimeSwitch.struSwitchTimePoint[iHolidaySel].struTimePoint.wYear = m_ctYmd.GetYear();
    m_struTimeSwitch.struSwitchTimePoint[iHolidaySel].struTimePoint.wMonth = m_ctYmd.GetMonth();
    m_struTimeSwitch.struSwitchTimePoint[iHolidaySel].struTimePoint.wDay = m_ctYmd.GetDay();
    m_struTimeSwitch.struSwitchTimePoint[iHolidaySel].struTimePoint.wHour = m_ctHms.GetHour();
    m_struTimeSwitch.struSwitchTimePoint[iHolidaySel].struTimePoint.wMinute = m_ctHms.GetMinute();
    m_struTimeSwitch.struSwitchTimePoint[iHolidaySel].struTimePoint.wSecond = m_ctHms.GetSecond();
}

void CDlgLcdSwitchCfg::OnSelchangeComboWeekDay() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

    int iWeekDaySel = m_comboWeekDay.GetCurSel();
    if (iWeekDaySel == CB_ERR)
    {
        return;
    }

    m_bTp1 = m_struTimeSwitch.struSwitchDayTime[iWeekDaySel][0].byEnable;
    m_ctHmsTp1.SetTime(m_struTimeSwitch.struSwitchDayTime[iWeekDaySel][0].struTimePoint.byHour, \
        m_struTimeSwitch.struSwitchDayTime[iWeekDaySel][0].struTimePoint.byMinute, \
        m_struTimeSwitch.struSwitchDayTime[iWeekDaySel][0].struTimePoint.bySecond);
    m_comboSwitchType1.SetCurSel(m_struTimeSwitch.struSwitchDayTime[iWeekDaySel][0].bySwitchType);

    m_bTp2 = m_struTimeSwitch.struSwitchDayTime[iWeekDaySel][1].byEnable;
    m_ctHmsTp2.SetTime(m_struTimeSwitch.struSwitchDayTime[iWeekDaySel][1].struTimePoint.byHour, \
        m_struTimeSwitch.struSwitchDayTime[iWeekDaySel][1].struTimePoint.byMinute, \
        m_struTimeSwitch.struSwitchDayTime[iWeekDaySel][1].struTimePoint.bySecond);
    m_comboSwitchType2.SetCurSel(m_struTimeSwitch.struSwitchDayTime[iWeekDaySel][1].bySwitchType);

    m_bTp3 = m_struTimeSwitch.struSwitchDayTime[iWeekDaySel][2].byEnable;
    m_ctHmsTp3.SetTime(m_struTimeSwitch.struSwitchDayTime[iWeekDaySel][2].struTimePoint.byHour, \
        m_struTimeSwitch.struSwitchDayTime[iWeekDaySel][2].struTimePoint.byMinute, \
        m_struTimeSwitch.struSwitchDayTime[iWeekDaySel][2].struTimePoint.bySecond);
    m_comboSwitchType3.SetCurSel(m_struTimeSwitch.struSwitchDayTime[iWeekDaySel][2].bySwitchType);

    m_bTp4 = m_struTimeSwitch.struSwitchDayTime[iWeekDaySel][3].byEnable;
    m_ctHmsTp4.SetTime(m_struTimeSwitch.struSwitchDayTime[iWeekDaySel][3].struTimePoint.byHour, \
        m_struTimeSwitch.struSwitchDayTime[iWeekDaySel][3].struTimePoint.byMinute, \
        m_struTimeSwitch.struSwitchDayTime[iWeekDaySel][3].struTimePoint.bySecond);
    m_comboSwitchType4.SetCurSel(m_struTimeSwitch.struSwitchDayTime[iWeekDaySel][3].bySwitchType);

    UpdateData(FALSE);
}

void CDlgLcdSwitchCfg::OnSelchangeComboHolidayTpNo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

    int iHolidaySel = m_comboHolidayNo.GetCurSel();

    if (CB_ERR == iHolidaySel)
    {
        return;
    }
    
    m_bHolidayTp = m_struTimeSwitch.struSwitchTimePoint[iHolidaySel].byEnable;
    if (m_struTimeSwitch.struSwitchTimePoint[iHolidaySel].struTimePoint.wYear > 1752)
    {
        m_ctYmd.SetDate(m_struTimeSwitch.struSwitchTimePoint[iHolidaySel].struTimePoint.wYear, \
        m_struTimeSwitch.struSwitchTimePoint[iHolidaySel].struTimePoint.wMonth, \
        m_struTimeSwitch.struSwitchTimePoint[iHolidaySel].struTimePoint.wDay);
    }
    m_ctHms.SetTime(m_struTimeSwitch.struSwitchTimePoint[iHolidaySel].struTimePoint.wHour, \
        m_struTimeSwitch.struSwitchTimePoint[iHolidaySel].struTimePoint.wMinute, \
        m_struTimeSwitch.struSwitchTimePoint[iHolidaySel].struTimePoint.wSecond);

    m_comboSwitchTypeHoliday.SetCurSel(m_struTimeSwitch.struSwitchTimePoint[iHolidaySel].bySwitchType); 
    UpdateData(FALSE);
}

void CDlgLcdSwitchCfg::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
    CDialog::OnCancel();
}
