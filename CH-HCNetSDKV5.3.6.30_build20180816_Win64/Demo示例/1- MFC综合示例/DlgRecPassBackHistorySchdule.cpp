// DlgRecPassBackHistorySchdule.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgRecPassBackHistorySchdule.h"
#include "afxdialogex.h"


// CDlgRecPassBackHistorySchdule 对话框

IMPLEMENT_DYNAMIC(CDlgRecPassBackHistorySchdule, CDialogEx)

CDlgRecPassBackHistorySchdule::CDlgRecPassBackHistorySchdule(CWnd* pParent /*=NULL*/)
: CDialogEx(CDlgRecPassBackHistorySchdule::IDD, pParent)
, m_bCheckAllDay(FALSE)
, m_iHour11(0)
, m_iMin11(0)
, m_iHour12(0)
, m_iMin12(0)
, m_iHour21(0)
, m_iMin21(0)
, m_iHour22(0)
, m_iMin22(0)
, m_iHour31(0)
, m_iMin31(0)
, m_iHour32(0)
, m_iMin32(0)
, m_iHour41(0)
, m_iMin41(0)
, m_iHour42(0)
, m_iMin42(0)
, m_iHour51(0)
, m_iMin51(0)
, m_iHour52(0)
, m_iMin52(0)
, m_iHour61(0)
, m_iMin61(0)
, m_iHour62(0)
, m_iMin62(0)
, m_iHour71(0)
, m_iMin71(0)
, m_iHour72(0)
, m_iMin72(0)
, m_iHour81(0)
, m_iMin81(0)
, m_iHour82(0)
, m_iMin82(0)
, m_nDate(0)
, m_nCopyDate(0)
, m_pStruRecordPassBackHistoryPlanCfg(NULL)
{
    //{{AFX_DATA_INIT(CDlgRecPassBackScheCfg)
    m_bCheckAllDay = FALSE;
    //}}AFX_DATA_INIT
    m_nDate = 0;
    m_nCopyDate = 0;
}

CDlgRecPassBackHistorySchdule::~CDlgRecPassBackHistorySchdule()
{
}

void CDlgRecPassBackHistorySchdule::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_WEEK_DAY, m_comboWeekday);
    DDX_Check(pDX, IDC_CHK_ALL_DAY, m_bCheckAllDay);
    DDX_Control(pDX, IDC_COMBO_COPY_WEEKDAY, m_comboCopyWeekday);
    DDX_Text(pDX, IDC_EDIT_HOUR11, m_iHour11);
    DDX_Text(pDX, IDC_EDIT_MIN11, m_iMin11);
    DDX_Text(pDX, IDC_EDIT_HOUR12, m_iHour12);
    DDX_Text(pDX, IDC_EDIT_MIN12, m_iMin12);
    DDX_Text(pDX, IDC_EDIT_HOUR21, m_iHour21);
    DDX_Text(pDX, IDC_EDIT_MIN21, m_iMin21);
    DDX_Text(pDX, IDC_EDIT_HOUR22, m_iHour22);
    DDX_Text(pDX, IDC_EDIT_MIN22, m_iMin22);
    DDX_Text(pDX, IDC_EDIT_HOUR31, m_iHour31);
    DDX_Text(pDX, IDC_EDIT_MIN31, m_iMin31);
    DDX_Text(pDX, IDC_EDIT_HOUR32, m_iHour32);
    DDX_Text(pDX, IDC_EDIT_MIN32, m_iMin32);
    DDX_Text(pDX, IDC_EDIT_HOUR41, m_iHour41);
    DDX_Text(pDX, IDC_EDIT_MIN41, m_iMin41);
    DDX_Text(pDX, IDC_EDIT_HOUR42, m_iHour42);
    DDX_Text(pDX, IDC_EDIT_MIN42, m_iMin42);
    DDX_Text(pDX, IDC_EDIT_HOUR51, m_iHour51);
    DDX_Text(pDX, IDC_EDIT_MIN51, m_iMin51);
    DDX_Text(pDX, IDC_EDIT_HOUR52, m_iHour52);
    DDX_Text(pDX, IDC_EDIT_MIN52, m_iMin52);
    DDX_Text(pDX, IDC_EDIT_HOUR61, m_iHour61);
    DDX_Text(pDX, IDC_EDIT_MIN61, m_iMin61);
    DDX_Text(pDX, IDC_EDIT_HOUR62, m_iHour62);
    DDX_Text(pDX, IDC_EDIT_MIN62, m_iMin62);
    DDX_Text(pDX, IDC_EDIT_HOUR71, m_iHour71);
    DDX_Text(pDX, IDC_EDIT_MIN71, m_iMin71);
    DDX_Text(pDX, IDC_EDIT_HOUR72, m_iHour72);
    DDX_Text(pDX, IDC_EDIT_MIN72, m_iMin72);
    DDX_Text(pDX, IDC_EDIT_HOUR81, m_iHour81);
    DDX_Text(pDX, IDC_EDIT_MIN81, m_iMin81);
    DDX_Text(pDX, IDC_EDIT_HOUR82, m_iHour82);
    DDX_Text(pDX, IDC_EDIT_MIN82, m_iMin82);
}


BEGIN_MESSAGE_MAP(CDlgRecPassBackHistorySchdule, CDialogEx)
    ON_BN_CLICKED(ID_BTN_REMOTE_REC_OK, OnBnClickedBtnRemoteRecOk)
    ON_BN_CLICKED(ID_BTN_REMOTE_REC_EXIT, OnBnClickedBtnRemoteRecExit)
    ON_BN_CLICKED(IDC_BTN_REMOTE_REC_COPY, OnBnClickedBtnRemoteRecCopy)
    ON_CBN_SELCHANGE(IDC_COMBO_WEEK_DAY, OnCbnSelchangeComboWeekDay)
    ON_BN_CLICKED(IDC_CHK_ALL_DAY, OnBnClickedChkAllDay)
END_MESSAGE_MAP()


// CDlgRecPassBackHistorySchdule 消息处理程序

BOOL CDlgRecPassBackHistorySchdule::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO: Add extra initialization here
    m_comboWeekday.SetCurSel(m_nDate);

    m_comboCopyWeekday.SetCurSel(m_nCopyDate);
    m_bCheckAllDay = m_pStruRecordPassBackHistoryPlanCfg->struPassBackDay[m_nDate].byAllDay;

    m_iHour11 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][0].struPassBackTime.byStartHour;
    m_iHour12 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][0].struPassBackTime.byStopHour;
    m_iHour21 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][1].struPassBackTime.byStartHour;
    m_iHour22 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][1].struPassBackTime.byStopHour;
    m_iHour31 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][2].struPassBackTime.byStartHour;
    m_iHour32 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][2].struPassBackTime.byStopHour;
    m_iHour41 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][3].struPassBackTime.byStartHour;
    m_iHour42 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][3].struPassBackTime.byStopHour;
    m_iMin11 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][0].struPassBackTime.byStartMin;
    m_iMin12 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][0].struPassBackTime.byStopMin;
    m_iMin21 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][1].struPassBackTime.byStartMin;
    m_iMin22 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][1].struPassBackTime.byStopMin;
    m_iMin31 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][2].struPassBackTime.byStartMin;
    m_iMin32 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][2].struPassBackTime.byStopMin;
    m_iMin41 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][3].struPassBackTime.byStartMin;
    m_iMin42 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][3].struPassBackTime.byStopMin;

    m_iHour51 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][4].struPassBackTime.byStartHour;
    m_iHour52 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][4].struPassBackTime.byStopHour;
    m_iHour61 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][5].struPassBackTime.byStartHour;
    m_iHour62 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][5].struPassBackTime.byStopHour;
    m_iHour71 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][6].struPassBackTime.byStartHour;
    m_iHour72 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][6].struPassBackTime.byStopHour;
    m_iHour81 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][7].struPassBackTime.byStartHour;
    m_iHour82 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][7].struPassBackTime.byStopHour;
    m_iMin51 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][4].struPassBackTime.byStartMin;
    m_iMin52 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][4].struPassBackTime.byStopMin;
    m_iMin61 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][5].struPassBackTime.byStartMin;
    m_iMin62 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][5].struPassBackTime.byStopMin;
    m_iMin71 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][6].struPassBackTime.byStartMin;
    m_iMin72 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][6].struPassBackTime.byStopMin;
    m_iMin81 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][7].struPassBackTime.byStartMin;
    m_iMin82 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][7].struPassBackTime.byStopMin;
    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgRecPassBackHistorySchdule::OnBnClickedChkAllDay()
{
    UpdateData(TRUE);
    EnableControlAllDay(!m_bCheckAllDay);
}


void CDlgRecPassBackHistorySchdule::EnableControlAllDay(BOOL bEnable)
{
    GetDlgItem(IDC_EDIT_HOUR11)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_HOUR21)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_HOUR31)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_HOUR41)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_HOUR51)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_HOUR61)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_HOUR71)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_HOUR81)->EnableWindow(bEnable);

    GetDlgItem(IDC_EDIT_MIN11)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_MIN21)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_MIN31)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_MIN41)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_MIN51)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_MIN61)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_MIN71)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_MIN81)->EnableWindow(bEnable);

    GetDlgItem(IDC_EDIT_HOUR12)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_HOUR22)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_HOUR32)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_HOUR42)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_HOUR52)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_HOUR62)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_HOUR72)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_HOUR82)->EnableWindow(bEnable);

    GetDlgItem(IDC_EDIT_MIN12)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_MIN22)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_MIN32)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_MIN42)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_MIN52)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_MIN62)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_MIN72)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_MIN82)->EnableWindow(bEnable);
}


void CDlgRecPassBackHistorySchdule::OnCbnSelchangeComboWeekDay()
{
    m_nDate = m_comboWeekday.GetCurSel();

    m_bCheckAllDay = m_pStruRecordPassBackHistoryPlanCfg->struPassBackDay[m_nDate].byAllDay;

    m_iHour11 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][0].struPassBackTime.byStartHour;
    m_iHour12 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][0].struPassBackTime.byStopHour;
    m_iHour21 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][1].struPassBackTime.byStartHour;
    m_iHour22 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][1].struPassBackTime.byStopHour;
    m_iHour31 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][2].struPassBackTime.byStartHour;
    m_iHour32 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][2].struPassBackTime.byStopHour;
    m_iHour41 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][3].struPassBackTime.byStartHour;
    m_iHour42 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][3].struPassBackTime.byStopHour;
    m_iMin11 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][0].struPassBackTime.byStartMin;
    m_iMin12 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][0].struPassBackTime.byStopMin;
    m_iMin21 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][1].struPassBackTime.byStartMin;
    m_iMin22 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][1].struPassBackTime.byStopMin;
    m_iMin31 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][2].struPassBackTime.byStartMin;
    m_iMin32 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][2].struPassBackTime.byStopMin;
    m_iMin41 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][3].struPassBackTime.byStartMin;
    m_iMin42 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][3].struPassBackTime.byStopMin;

    m_iHour51 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][4].struPassBackTime.byStartHour;
    m_iHour52 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][4].struPassBackTime.byStopHour;
    m_iHour61 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][5].struPassBackTime.byStartHour;
    m_iHour62 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][5].struPassBackTime.byStopHour;
    m_iHour71 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][6].struPassBackTime.byStartHour;
    m_iHour72 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][6].struPassBackTime.byStopHour;
    m_iHour81 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][7].struPassBackTime.byStartHour;
    m_iHour82 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][7].struPassBackTime.byStopHour;
    m_iMin51 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][4].struPassBackTime.byStartMin;
    m_iMin52 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][4].struPassBackTime.byStopMin;
    m_iMin61 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][5].struPassBackTime.byStartMin;
    m_iMin62 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][5].struPassBackTime.byStopMin;
    m_iMin71 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][6].struPassBackTime.byStartMin;
    m_iMin72 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][6].struPassBackTime.byStopMin;
    m_iMin81 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][7].struPassBackTime.byStartMin;
    m_iMin82 = m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][7].struPassBackTime.byStopMin;

    EnableControlAllDay(!m_bCheckAllDay);
    GetDlgItem(IDC_BTN_REMOTE_REC_COPY)->EnableWindow(FALSE);
    UpdateData(FALSE);
}

void CDlgRecPassBackHistorySchdule::OnBnClickedBtnRemoteRecCopy()
{
    UpdateData(TRUE);
    m_nCopyDate = m_comboCopyWeekday.GetCurSel() - 1;
    if (!TimeTest())
    {
        return;
    }

    if (m_nCopyDate != -1)
    {
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackDay[m_nDate].byAllDay = (BYTE)m_bCheckAllDay;

        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][0].struPassBackTime.byStartHour = (BYTE)m_iHour11;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][0].struPassBackTime.byStopHour = (BYTE)m_iHour12;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][1].struPassBackTime.byStartHour = (BYTE)m_iHour21;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][1].struPassBackTime.byStopHour = (BYTE)m_iHour22;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][2].struPassBackTime.byStartHour = (BYTE)m_iHour31;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][2].struPassBackTime.byStopHour = (BYTE)m_iHour32;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][3].struPassBackTime.byStartHour = (BYTE)m_iHour41;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][3].struPassBackTime.byStopHour = (BYTE)m_iHour42;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][4].struPassBackTime.byStartHour = (BYTE)m_iHour51;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][4].struPassBackTime.byStopHour = (BYTE)m_iHour52;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][5].struPassBackTime.byStartHour = (BYTE)m_iHour61;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][5].struPassBackTime.byStopHour = (BYTE)m_iHour62;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][6].struPassBackTime.byStartHour = (BYTE)m_iHour71;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][6].struPassBackTime.byStopHour = (BYTE)m_iHour72;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][7].struPassBackTime.byStartHour = (BYTE)m_iHour81;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][7].struPassBackTime.byStopHour = (BYTE)m_iHour82;

        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][0].struPassBackTime.byStartMin = (BYTE)m_iMin11;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][0].struPassBackTime.byStopMin = (BYTE)m_iMin12;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][1].struPassBackTime.byStartMin = (BYTE)m_iMin21;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][1].struPassBackTime.byStopMin = (BYTE)m_iMin22;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][2].struPassBackTime.byStartMin = (BYTE)m_iMin31;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][2].struPassBackTime.byStopMin = (BYTE)m_iMin32;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][3].struPassBackTime.byStartMin = (BYTE)m_iMin41;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][3].struPassBackTime.byStopMin = (BYTE)m_iMin42;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][4].struPassBackTime.byStartMin = (BYTE)m_iMin51;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][4].struPassBackTime.byStopMin = (BYTE)m_iMin52;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][5].struPassBackTime.byStartMin = (BYTE)m_iMin61;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][5].struPassBackTime.byStopMin = (BYTE)m_iMin62;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][6].struPassBackTime.byStartMin = (BYTE)m_iMin71;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][6].struPassBackTime.byStopMin = (BYTE)m_iMin72;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][7].struPassBackTime.byStartMin = (BYTE)m_iMin81;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nCopyDate][7].struPassBackTime.byStopMin = (BYTE)m_iMin82;
    }
    else
    {
        for (int i = 0; i < MAX_DAYS; i++)
        {
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackDay[i].byAllDay = (BYTE)m_bCheckAllDay;

            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][0].struPassBackTime.byStartHour = (BYTE)m_iHour11;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][0].struPassBackTime.byStopHour = (BYTE)m_iHour12;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][1].struPassBackTime.byStartHour = (BYTE)m_iHour21;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][1].struPassBackTime.byStopHour = (BYTE)m_iHour22;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][2].struPassBackTime.byStartHour = (BYTE)m_iHour31;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][2].struPassBackTime.byStopHour = (BYTE)m_iHour32;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][3].struPassBackTime.byStartHour = (BYTE)m_iHour41;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][3].struPassBackTime.byStopHour = (BYTE)m_iHour42;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][4].struPassBackTime.byStartHour = (BYTE)m_iHour51;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][4].struPassBackTime.byStopHour = (BYTE)m_iHour52;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][5].struPassBackTime.byStartHour = (BYTE)m_iHour61;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][5].struPassBackTime.byStopHour = (BYTE)m_iHour62;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][6].struPassBackTime.byStartHour = (BYTE)m_iHour71;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][6].struPassBackTime.byStopHour = (BYTE)m_iHour72;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][7].struPassBackTime.byStartHour = (BYTE)m_iHour81;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][7].struPassBackTime.byStopHour = (BYTE)m_iHour82;

            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][0].struPassBackTime.byStartMin = (BYTE)m_iMin11;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][0].struPassBackTime.byStopMin = (BYTE)m_iMin12;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][1].struPassBackTime.byStartMin = (BYTE)m_iMin21;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][1].struPassBackTime.byStopMin = (BYTE)m_iMin22;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][2].struPassBackTime.byStartMin = (BYTE)m_iMin31;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][2].struPassBackTime.byStopMin = (BYTE)m_iMin32;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][3].struPassBackTime.byStartMin = (BYTE)m_iMin41;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][3].struPassBackTime.byStopMin = (BYTE)m_iMin42;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][4].struPassBackTime.byStartMin = (BYTE)m_iMin51;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][4].struPassBackTime.byStopMin = (BYTE)m_iMin52;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][5].struPassBackTime.byStartMin = (BYTE)m_iMin61;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][5].struPassBackTime.byStopMin = (BYTE)m_iMin62;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][6].struPassBackTime.byStartMin = (BYTE)m_iMin71;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][6].struPassBackTime.byStopMin = (BYTE)m_iMin72;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][7].struPassBackTime.byStartMin = (BYTE)m_iMin81;
            m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[i][7].struPassBackTime.byStopMin = (BYTE)m_iMin82;
        }
    }
}

void CDlgRecPassBackHistorySchdule::OnBnClickedBtnRemoteRecExit()
{
    CDialog::OnOK();
}

void CDlgRecPassBackHistorySchdule::OnBnClickedBtnRemoteRecOk()
{
    UpdateData(TRUE);


    if (!TimeTest())
    {
        return;
    }

    m_pStruRecordPassBackHistoryPlanCfg->struPassBackDay[m_nDate].byAllDay = (BYTE)m_bCheckAllDay;

    if (!m_bCheckAllDay)
    {
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][0].struPassBackTime.byStartHour = (BYTE)m_iHour11;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][0].struPassBackTime.byStopHour = (BYTE)m_iHour12;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][1].struPassBackTime.byStartHour = (BYTE)m_iHour21;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][1].struPassBackTime.byStopHour = (BYTE)m_iHour22;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][2].struPassBackTime.byStartHour = (BYTE)m_iHour31;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][2].struPassBackTime.byStopHour = (BYTE)m_iHour32;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][3].struPassBackTime.byStartHour = (BYTE)m_iHour41;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][3].struPassBackTime.byStopHour = (BYTE)m_iHour42;

        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][0].struPassBackTime.byStartMin = (BYTE)m_iMin11;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][0].struPassBackTime.byStopMin = (BYTE)m_iMin12;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][1].struPassBackTime.byStartMin = (BYTE)m_iMin21;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][1].struPassBackTime.byStopMin = (BYTE)m_iMin22;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][2].struPassBackTime.byStartMin = (BYTE)m_iMin31;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][2].struPassBackTime.byStopMin = (BYTE)m_iMin32;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][3].struPassBackTime.byStartMin = (BYTE)m_iMin41;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][3].struPassBackTime.byStopMin = (BYTE)m_iMin42;

        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][4].struPassBackTime.byStartHour = (BYTE)m_iHour51;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][4].struPassBackTime.byStopHour = (BYTE)m_iHour52;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][5].struPassBackTime.byStartHour = (BYTE)m_iHour61;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][5].struPassBackTime.byStopHour = (BYTE)m_iHour62;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][6].struPassBackTime.byStartHour = (BYTE)m_iHour71;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][6].struPassBackTime.byStopHour = (BYTE)m_iHour72;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][7].struPassBackTime.byStartHour = (BYTE)m_iHour81;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][7].struPassBackTime.byStopHour = (BYTE)m_iHour82;

        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][4].struPassBackTime.byStartMin = (BYTE)m_iMin51;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][4].struPassBackTime.byStopMin = (BYTE)m_iMin52;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][5].struPassBackTime.byStartMin = (BYTE)m_iMin61;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][5].struPassBackTime.byStopMin = (BYTE)m_iMin62;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][6].struPassBackTime.byStartMin = (BYTE)m_iMin71;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][6].struPassBackTime.byStopMin = (BYTE)m_iMin72;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][7].struPassBackTime.byStartMin = (BYTE)m_iMin81;
        m_pStruRecordPassBackHistoryPlanCfg->struPassBackSched[m_nDate][7].struPassBackTime.byStopMin = (BYTE)m_iMin82;
    }

    GetDlgItem(IDC_BTN_REMOTE_REC_COPY)->EnableWindow(TRUE);
}

BOOL CDlgRecPassBackHistorySchdule::TimeTest()
{
    UpdateData(TRUE);

    int i = 0;
    int j = 0;
    WORD wStartTime[MAX_TIMESEGMENT_V30], wStopTime[MAX_TIMESEGMENT_V30];
    char szLan[128] = { 0 };

    if ((m_iHour11 < 0) || (m_iHour11 > 24) || (m_iHour12 < 0) || (m_iHour12 > 24) || \
        (m_iHour21 < 0) || (m_iHour21 > 24) || (m_iHour22 < 0) || (m_iHour22 > 24) || \
        (m_iHour31 < 0) || (m_iHour31 > 24) || (m_iHour32 < 0) || (m_iHour32 > 24) || \
        (m_iHour41 < 0) || (m_iHour41 > 24) || (m_iHour42 < 0) || (m_iHour42 > 24) || \
        (m_iHour51 < 0) || (m_iHour51 > 24) || (m_iHour52 < 0) || (m_iHour52 > 24) || \
        (m_iHour61 < 0) || (m_iHour61 > 24) || (m_iHour62 < 0) || (m_iHour62 > 24) || \
        (m_iHour71 < 0) || (m_iHour71 > 24) || (m_iHour72 < 0) || (m_iHour72 > 24) || \
        (m_iHour81 < 0) || (m_iHour81 > 24) || (m_iHour82 < 0) || (m_iHour82 > 24))
    {
        g_StringLanType(szLan, "小时范围在0 -- 24之间", "Hour between 0 - 24 ");
        AfxMessageBox(szLan);
        return FALSE;
    }
    if ((m_iMin11 < 0) || (m_iMin11 > 60) || (m_iMin12 < 0) || (m_iMin12 > 60) || \
        (m_iMin21 < 0) || (m_iMin21 > 60) || (m_iMin22 < 0) || (m_iMin22 > 60) || \
        (m_iMin31 < 0) || (m_iMin31 > 60) || (m_iMin32 < 0) || (m_iMin32 > 60) || \
        (m_iMin41 < 0) || (m_iMin41 > 60) || (m_iMin42 < 0) || (m_iMin42 > 60) || \
        (m_iMin51 < 0) || (m_iMin51 > 60) || (m_iMin52 < 0) || (m_iMin52 > 60) || \
        (m_iMin61 < 0) || (m_iMin61 > 60) || (m_iMin62 < 0) || (m_iMin62 > 60) || \
        (m_iMin71 < 0) || (m_iMin71 > 60) || (m_iMin72 < 0) || (m_iMin72 > 60) || \
        (m_iMin81 < 0) || (m_iMin81 > 60) || (m_iMin82 < 0) || (m_iMin82 > 60))
    {
        g_StringLanType(szLan, "分钟范围在0 -- 60之间", "Minute between 0 - 60 ");
        AfxMessageBox(szLan);
        return FALSE;
    }
    wStartTime[0] = (WORD)(m_iHour11 * 100 + m_iMin11);
    wStartTime[1] = (WORD)(m_iHour21 * 100 + m_iMin21);
    wStartTime[2] = (WORD)(m_iHour31 * 100 + m_iMin31);
    wStartTime[3] = (WORD)(m_iHour41 * 100 + m_iMin41);
    wStopTime[0] = (WORD)(m_iHour12 * 100 + m_iMin12);
    wStopTime[1] = (WORD)(m_iHour22 * 100 + m_iMin22);
    wStopTime[2] = (WORD)(m_iHour32 * 100 + m_iMin32);
    wStopTime[3] = (WORD)(m_iHour42 * 100 + m_iMin42);
    wStartTime[4] = (WORD)(m_iHour51 * 100 + m_iMin51);
    wStartTime[5] = (WORD)(m_iHour61 * 100 + m_iMin61);
    wStartTime[6] = (WORD)(m_iHour71 * 100 + m_iMin71);
    wStartTime[7] = (WORD)(m_iHour81 * 100 + m_iMin81);
    wStopTime[4] = (WORD)(m_iHour52 * 100 + m_iMin52);
    wStopTime[5] = (WORD)(m_iHour62 * 100 + m_iMin62);
    wStopTime[6] = (WORD)(m_iHour72 * 100 + m_iMin72);
    wStopTime[7] = (WORD)(m_iHour82 * 100 + m_iMin82);
    for (i = 0; i < MAX_TIMESEGMENT_V30; i++)
    {
        if ((wStartTime[i] > 2400) || (wStopTime[i] > 2400))
        {
            g_StringLanType(szLan, "布防时间不能超过24:00", "Fortify time can not be more than 24:00");
            AfxMessageBox(szLan);
            return FALSE;
        }
        if (wStartTime[i] > wStopTime[i])
        {
            g_StringLanType(szLan, "布防起始时间不能大于停止时间", "Fortify start time can not be larger than the record to stop time");
            AfxMessageBox(szLan);
            return FALSE;
        }
        for (j = 0; j < MAX_TIMESEGMENT_V30; j++)
        {
            if (i == j)
            {
                continue;
            }
            if ((wStartTime[i] > wStartTime[j]) && (wStartTime[i] < wStopTime[j]) || \
                (wStopTime[i] > wStartTime[j]) && (wStopTime[i] < wStopTime[j]))
            {
                g_StringLanType(szLan, "时间段不能重复", "time can not be repeated");
                AfxMessageBox(szLan);
                return FALSE;
            }
        }
    }
    return TRUE;
}

