// DlgHolidayCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgHolidayCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgHolidayCfg dialog


CDlgHolidayCfg::CDlgHolidayCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHolidayCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHolidayCfg)
	m_csHolidayName = _T("");
	m_bEnable = FALSE;
	m_iEndDayA = 0;
	m_iEndDayC = 0;
	m_iEndMonthB = 0;
	m_iEndMonthC = 0;
	m_iEndWeeknumB = 0;
	m_iEndYearC = 0;
	m_iEndMonthA = 0;
	m_iStartDayC = 0;
	m_iStartMonthA = 0;
	m_iStartMonthB = 0;
	m_iStartMonthC = 0;
	m_iStartWeeknumB = 0;
	m_iStartYearC = 0;
	m_iStartDayA = 0;
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    memset(&m_struHolidayParamCfg, 0, sizeof(m_struHolidayParamCfg));

}


void CDlgHolidayCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHolidayCfg)
	DDX_Control(pDX, IDC_COMBO_STOP_WEEKDAY_B_, m_comboStopWeekdayB);
	DDX_Control(pDX, IDC_COMBO_START_WEEKDAY_B_, m_comboStartWeekdayB);
	DDX_Control(pDX, IDC_COMBO_HOLIDAY_INDEX, m_comboHolidayIndex);
	DDX_Control(pDX, IDC_COMBO_HOLI_DATE_MODE, m_comboHoliDateMode);
	DDX_Text(pDX, IDC_EDIT_HOLIDAY_NAME, m_csHolidayName);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	DDX_Text(pDX, IDC_EDIT_END_DAY_A, m_iEndDayA);
	DDX_Text(pDX, IDC_EDIT_END_DAY_C, m_iEndDayC);
	DDX_Text(pDX, IDC_EDIT_END_MONTH_B, m_iEndMonthB);
	DDX_Text(pDX, IDC_EDIT_END_MONTH_C, m_iEndMonthC);
	DDX_Text(pDX, IDC_EDIT_END_WEEKNUM_B, m_iEndWeeknumB);
	DDX_Text(pDX, IDC_EDIT_END_YEAR_C, m_iEndYearC);
	DDX_Text(pDX, IDC_EDIT_END_MONTH_A, m_iEndMonthA);
	DDX_Text(pDX, IDC_EDIT_START_DAY_C, m_iStartDayC);
	DDX_Text(pDX, IDC_EDIT_START_MONTH_A, m_iStartMonthA);
	DDX_Text(pDX, IDC_EDIT_START_MONTH_B, m_iStartMonthB);
	DDX_Text(pDX, IDC_EDIT_START_MONTH_C, m_iStartMonthC);
	DDX_Text(pDX, IDC_EDIT_START_WEEKNUM_B, m_iStartWeeknumB);
	DDX_Text(pDX, IDC_EDIT_START_YEAR_C, m_iStartYearC);
	DDX_Text(pDX, IDC_EDIT_START_DAY_A, m_iStartDayA);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHolidayCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgHolidayCfg)
	ON_CBN_SELCHANGE(IDC_COMBO_HOLI_DATE_MODE, OnSelchangeComboHoliDateMode)
	ON_CBN_SELCHANGE(IDC_COMBO_HOLIDAY_INDEX, OnSelchangeComboHolidayIndex)
	ON_BN_CLICKED(IDC_BTN_CONFIRM, OnBtnConfirm)
	ON_BN_CLICKED(IDC_BTN_SET_UP, OnBtnSetUp)
	ON_BN_CLICKED(IDC_BTN_UPDATE_HOLIDAY, OnButtonUpdate)
	ON_BN_CLICKED(IDC_BTN_EXIT_HOLIDAY, OnButtonExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgHolidayCfg message handlers

BOOL CDlgHolidayCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitWnd();
    GetHolidayParmCfg(m_struHolidayParamCfg);
    m_comboHolidayIndex.SetCurSel(0);
    OnSelchangeComboHolidayIndex();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgHolidayCfg::InitWnd()
{
    InitHolidayIndexCombo();
    InitHoliDateModeCombo();
}

void CDlgHolidayCfg::InitHolidayIndexCombo()
{
   m_comboHolidayIndex.ResetContent();
   char szLanCn[128] = {0};
   char szLanEn[128] = {0};
   char szLan[128] = {0};
   for (int i = 0; i < MAX_HOLIDAY_NUM; i++)
   {
        sprintf(szLanCn, "¼ÙÈÕ %d", i);
        sprintf(szLanEn, "Holiday %d", i);
        g_StringLanType(szLan, szLanCn, szLanEn);
        m_comboHolidayIndex.AddString(szLan);
   }
}

void CDlgHolidayCfg::InitHoliDateModeCombo()
{

    m_comboHoliDateMode.ResetContent();
    m_comboHoliDateMode.AddString("M-D");
    m_comboHoliDateMode.AddString ("M-Weeknum-Week");
    m_comboHoliDateMode.AddString("Y-M-D");
}

void CDlgHolidayCfg::ShowHoliDateMode(int nDateMode)
{
    ShowHoliDateModeA(SW_HIDE);
    ShowHoliDateModeB(SW_HIDE);
    ShowHoliDateModeC(SW_HIDE);
    switch (nDateMode)
    {
    case HOLIDATE_MODEA:
        ShowHoliDateModeA(SW_SHOW);
    	break;
    case HOLIDATE_MODEB:
        ShowHoliDateModeB(SW_SHOW);
        break;
    case HOLIDATE_MODEC:
        ShowHoliDateModeC(SW_SHOW);
        break;
    default:
        break;
    }
}

void CDlgHolidayCfg::ShowHoliDateModeA(int nCmdShow)
{
    GetDlgItem(IDC_EDIT_START_MONTH_A)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_EDIT_START_DAY_A)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_EDIT_END_MONTH_A)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_EDIT_END_DAY_A)->ShowWindow(nCmdShow);
    
    GetDlgItem(IDC_STATIC_A1)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_STATIC_A2)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_STATIC_A3)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_STATIC_A4)->ShowWindow(nCmdShow);
}

void CDlgHolidayCfg::ShowHoliDateModeB(int nCmdShow)
{
    GetDlgItem(IDC_EDIT_START_MONTH_B)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_EDIT_START_WEEKNUM_B)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_EDIT_END_MONTH_B)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_EDIT_END_WEEKNUM_B)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_COMBO_START_WEEKDAY_B_)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_COMBO_STOP_WEEKDAY_B_)->ShowWindow(nCmdShow);

    GetDlgItem(IDC_STATIC_B1)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_STATIC_B2)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_STATIC_B4)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_STATIC_B5)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_STATIC_B6)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_STATIC_B8)->ShowWindow(nCmdShow);
}

void CDlgHolidayCfg::ShowHoliDateModeC(int nCmdShow)
{
    GetDlgItem(IDC_EDIT_START_YEAR_C)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_EDIT_START_MONTH_C)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_EDIT_START_DAY_C)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_EDIT_END_YEAR_C)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_EDIT_END_MONTH_C)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_EDIT_END_DAY_C)->ShowWindow(nCmdShow);

    GetDlgItem(IDC_STATIC_C1)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_STATIC_C2)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_STATIC_C3)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_STATIC_C4)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_STATIC_C5)->ShowWindow(nCmdShow);
    GetDlgItem(IDC_STATIC_C6)->ShowWindow(nCmdShow);
}

BOOL CDlgHolidayCfg::GetHolidayParmCfg(NET_DVR_HOLIDAY_PARAM_CFG &struHolidayParmCfg)
{
    BOOL bRet = FALSE;
    DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_HOLIDAY_PARAM_CFG, -1, &struHolidayParmCfg, sizeof(struHolidayParmCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_HOLIDAY_PARAM_CFG");
        bRet = TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_HOLIDAY_PARAM_CFG");
        bRet = FALSE;
    }

    return bRet;
}

BOOL CDlgHolidayCfg::SetHolidayParmCfg(NET_DVR_HOLIDAY_PARAM_CFG &struHolidayParmCfg)
{
    BOOL bRet = FALSE;
        
    if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_HOLIDAY_PARAM_CFG, -1, &struHolidayParmCfg, sizeof(struHolidayParmCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_HOLIDAY_PARAM_CFG");
        bRet = TRUE;
    } 
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_HOLIDAY_PARAM_CFG");
        bRet = FALSE;
    }

    return bRet;
}


void CDlgHolidayCfg::SetHolidayParamToWnd(NET_DVR_HOLIDAY_PARAM &struHolidayParam)
{
    m_bEnable = struHolidayParam.byEnable;
    m_csHolidayName = struHolidayParam.byName;
    m_comboHoliDateMode.SetCurSel(struHolidayParam.byDateMode);

    OnSelchangeComboHoliDateMode();
    SetHolidateUnionToWnd(struHolidayParam.uHolidate, struHolidayParam.byDateMode);
}


void CDlgHolidayCfg::GetHolidayParamFromWnd(NET_DVR_HOLIDAY_PARAM &struHolidayParam)
{
    struHolidayParam.byEnable = m_bEnable;
    strncpy((char*)struHolidayParam.byName, m_csHolidayName.GetBuffer(0), sizeof(struHolidayParam.byName));
    struHolidayParam.byDateMode = m_comboHoliDateMode.GetCurSel();
    GetHolidateUnionFromWnd(struHolidayParam.uHolidate, struHolidayParam.byDateMode);
}

void CDlgHolidayCfg::GetHolidateUnionFromWnd(NET_DVR_HOLIDATE_UNION &uHolidate, int nDateMode)
{
    switch (nDateMode)
    {
    case HOLIDATE_MODEA:
        GetHoliDateModeAFromWnd(uHolidate.struModeA);       
        break;
    case HOLIDATE_MODEB:
        GetHoliDateModeBFromWnd(uHolidate.struModeB);
        break;
    case HOLIDATE_MODEC:
        GetHoliDateModeCFromWnd(uHolidate.struModeC);
        break;
    }
}

void CDlgHolidayCfg::SetHolidateUnionToWnd(NET_DVR_HOLIDATE_UNION &uHolidate, int nDateMode)
{
    switch (nDateMode)
    {
    case HOLIDATE_MODEA:
        SetHoliDateModeAToWnd(uHolidate.struModeA);       
        break;
    case HOLIDATE_MODEB:
        SetHoliDateModeBToWnd(uHolidate.struModeB);
        break;
    case HOLIDATE_MODEC:
        SetHoliDateModeCToWnd(uHolidate.struModeC);
        break;
    }
}


void CDlgHolidayCfg::SetHoliDateModeAToWnd(NET_DVR_HOLIDATE_MODEA &struHolidateModeA)
{
    m_iStartMonthA = struHolidateModeA.byStartMonth;
    m_iStartDayA = struHolidateModeA.byStartDay;
    m_iEndMonthA = struHolidateModeA.byEndMonth;
    m_iEndDayA = struHolidateModeA.byEndDay;
}

void CDlgHolidayCfg::GetHoliDateModeAFromWnd(NET_DVR_HOLIDATE_MODEA &struHolidateModeA)
{
    struHolidateModeA.byStartMonth = m_iStartMonthA;
    struHolidateModeA.byStartDay = m_iStartDayA;
    struHolidateModeA.byEndMonth = m_iEndMonthA;
    struHolidateModeA.byEndDay = m_iEndDayA;
}

void CDlgHolidayCfg::SetHoliDateModeBToWnd(NET_DVR_HOLIDATE_MODEB &struHolidateModeB)
{
    m_iStartMonthB = struHolidateModeB.byStartMonth;
    m_iStartWeeknumB = struHolidateModeB.byStartWeekNum;
    m_comboStartWeekdayB.SetCurSel(struHolidateModeB.byStartWeekday -1);
    m_iEndMonthB = struHolidateModeB.byEndMonth;
    m_iEndWeeknumB = struHolidateModeB.byEndWeekNum;
    m_comboStopWeekdayB.SetCurSel(struHolidateModeB.byEndWeekday -1);
}

void CDlgHolidayCfg::GetHoliDateModeBFromWnd(NET_DVR_HOLIDATE_MODEB &struHolidateModeB)
{
    struHolidateModeB.byStartMonth = m_iStartMonthB;
    struHolidateModeB.byStartWeekNum = m_iStartWeeknumB;
    struHolidateModeB.byStartWeekday = m_comboStartWeekdayB.GetCurSel() + 1;
    struHolidateModeB.byEndMonth = m_iEndMonthB;
    struHolidateModeB.byEndWeekNum = m_iEndWeeknumB;
    struHolidateModeB.byEndWeekday = m_comboStopWeekdayB.GetCurSel() + 1;
}

void CDlgHolidayCfg::SetHoliDateModeCToWnd(NET_DVR_HOLIDATE_MODEC &struHolidateModeC)
{
    m_iStartYearC = struHolidateModeC.wStartYear;
    m_iStartMonthC = struHolidateModeC.byStartMon;
    m_iStartDayC = struHolidateModeC.byStartDay;
    m_iEndYearC = struHolidateModeC.wEndYear;
    m_iEndMonthC = struHolidateModeC.byEndMon;
    m_iEndDayC = struHolidateModeC.byEndDay;
}

void CDlgHolidayCfg::GetHoliDateModeCFromWnd(NET_DVR_HOLIDATE_MODEC &struHolidateModeC)
{
    struHolidateModeC.wStartYear = m_iStartYearC;
    struHolidateModeC.byStartMon = m_iStartMonthC;
    struHolidateModeC.byStartDay = m_iStartDayC;
    struHolidateModeC.wEndYear = m_iEndYearC;
    struHolidateModeC.byEndMon = m_iEndMonthC;
    struHolidateModeC.byEndDay = m_iEndDayC;
}

void CDlgHolidayCfg::OnSelchangeComboHoliDateMode() 
{
    int nDateMode = m_comboHoliDateMode.GetCurSel();
       
    ShowHoliDateMode(nDateMode);
    
}

void CDlgHolidayCfg::OnSelchangeComboHolidayIndex() 
{
    int nIndex = m_comboHolidayIndex.GetCurSel();
    
    SetHolidayParamToWnd(m_struHolidayParamCfg.struHolidayParam[nIndex]);
    UpdateData(FALSE);
}

void CDlgHolidayCfg::OnBtnConfirm() 
{
   int nIndex = m_comboHolidayIndex.GetCurSel();
   GetHolidayParamFromWnd(m_struHolidayParamCfg.struHolidayParam[nIndex]);
}

void CDlgHolidayCfg::OnBtnSetUp() 
{
    int nIndex = m_comboHolidayIndex.GetCurSel();
    UpdateData(TRUE);
    GetHolidayParamFromWnd(m_struHolidayParamCfg.struHolidayParam[nIndex]);

    if (!SetHolidayParmCfg(m_struHolidayParamCfg))
    {
        AfxMessageBox("Fail to set holiday param");
    }
}

void CDlgHolidayCfg::OnButtonUpdate() 
{
    GetHolidayParmCfg(m_struHolidayParamCfg);
    m_comboHolidayIndex.SetCurSel(0);
    OnSelchangeComboHolidayIndex();
}

void CDlgHolidayCfg::OnButtonExit() 
{
	CDialog::OnCancel();
}
