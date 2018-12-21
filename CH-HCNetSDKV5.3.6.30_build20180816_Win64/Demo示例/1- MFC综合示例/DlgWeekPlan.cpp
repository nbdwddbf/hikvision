// DlgWeekPlan.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgWeekPlan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWeekPlan dialog


CDlgWeekPlan::CDlgWeekPlan(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWeekPlan::IDD, pParent)
    ,m_iLastSel(-1)
    ,m_iLastSelH(-1)
    ,m_iLastGroupIndex(-1)
    ,m_iLastGroupIndexP(-1)
    ,m_iCurGroupNo(-1)
    ,m_iCurGroupNoP(-1)
    , m_iWeekPlanLocalController(0)
    , m_iHolidayPlanLocalController(0)
    , m_iHolidayGroupLocalController(0)
    , m_iPlanTemplateLocalController(0)
{
	//{{AFX_DATA_INIT(CDlgWeekPlan)
	m_dwPlanNo = 1;
	m_BEnable = FALSE;
	m_BTSEnable = FALSE;
	m_BEnableH = FALSE;
	m_BTSEnableH = FALSE;
	m_dtEndDate = COleDateTime::GetCurrentTime();
	m_dtStartDate = COleDateTime::GetCurrentTime();
	m_dtEndTimeH = COleDateTime::GetCurrentTime();
	m_dtStartTimeH = COleDateTime::GetCurrentTime();
    m_DTStartTime = COleDateTime::GetCurrentTime();
    m_DTEndTime = COleDateTime::GetCurrentTime();
	m_dwPlanNoH = 1;
	m_BEnableG = FALSE;
	m_csGroupName = _T("");
	m_dwGroupNo = 1;
	m_dwGroupPlanNo = 1;
	m_BEnableP = FALSE;
	m_dwGroupNoP = 1;
	m_csTemplateName = _T("");
	m_dwTemplateNo = 1;
	m_dwWeekPlanNoP = 1;
	m_dwTemplatePlanNo = 1;
	m_dwDoorNo = 1;
	m_csDoorOrCardNo = _T("");
	//}}AFX_DATA_INIT
}


void CDlgWeekPlan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWeekPlan)
	DDX_Control(pDX, IDC_LST_ACWP_TEMPLATE, m_lstTemplate);
	DDX_Control(pDX, IDC_LST_ACWP_HOLIDAYPLAY, m_lstHolidayPlan);
	DDX_Control(pDX, IDC_COM_ACSP_DEVICETYPE, m_cmbDeviceTypeS);
	DDX_Control(pDX, IDC_COMB_ACPT_GROUPINDEX, m_cmbGroupIndexP);
	DDX_Control(pDX, IDC_COM_ACPT_DEVICETYPE, m_cmbDeviceTypeP);
	DDX_Control(pDX, IDC_COM_ACHG_DEVICETYPE, m_cmbDeviceTypeG);
	DDX_Control(pDX, IDC_COMB_ACHG_GROUPINDEX, m_cmbGroupIndex);
	DDX_Control(pDX, IDC_COM_ACHP_TIMESEGMENT_VERIFY, m_cmbVerifyH);
	DDX_Control(pDX, IDC_COM_ACHP_TIMESEGMENT_DOORSTATUS, m_cmbDoorStatusH);
	DDX_Control(pDX, IDC_COM_ACHP_TIMESEGMENT, m_cmbTimeSegmentH);
	DDX_Control(pDX, IDC_COM_ACHP_DEVICETYPE, m_cmbDeviceTypeH);
    DDX_DateTimeCtrl(pDX, IDC_DATETIME_ACWP_TIMESEGMENT_STARTTIME, m_DTStartTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_ACWP_TIMESEGMENT_ENDTIME, m_DTEndTime);
	DDX_Control(pDX, IDC_COM_ACWP_TIMESEGMENT_VERIFY, m_cmbVerify);
	DDX_Control(pDX, IDC_COM_ACWP_TIMESEGMENT_DOORSTATUS, m_cmbDoorStatus);
	DDX_Control(pDX, IDC_COM_ACWP_TIMESEGMENT, m_cmbTimeSegment);
	DDX_Control(pDX, IDC_COM_ACWP_DEVICETYPE, m_cmbDeviceType);
	DDX_Control(pDX, IDC_COM_ACWP_DAY, m_cmbDay);
	DDX_Text(pDX, IDC_EDT_ACWP_PLANNO, m_dwPlanNo);
	DDX_Check(pDX, IDC_CHK_ACWP_ENABLE, m_BEnable);
	DDX_Check(pDX, IDC_CHK_ACWP_TIMESEGMENT_ENABLE, m_BTSEnable);
	DDX_Check(pDX, IDC_CHK_ACHP_ENABLE, m_BEnableH);
	DDX_Check(pDX, IDC_CHK_ACHP_TIMESEGMENT_ENABLE, m_BTSEnableH);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_ACHP_ENDDATE, m_dtEndDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_ACHP_STARTDATE, m_dtStartDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_ACHP_TIMESEGMENT_ENDTIME, m_dtEndTimeH);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_ACHP_TIMESEGMENT_STARTTIME, m_dtStartTimeH);
	DDX_Text(pDX, IDC_EDT_ACHP_PLANNO, m_dwPlanNoH);
	DDX_Check(pDX, IDC_CHK_ACHG_ENABLE, m_BEnableG);
	DDX_Text(pDX, IDC_EDT_ACHG_GROUPNAME, m_csGroupName);
	DDX_Text(pDX, IDC_EDT_ACHG_GROUPNO, m_dwGroupNo);
	DDX_Text(pDX, IDC_EDT_ACHG_GROUPSNO, m_dwGroupPlanNo);
	DDX_Check(pDX, IDC_CHK_ACPT_ENABLE, m_BEnableP);
	DDX_Text(pDX, IDC_EDT_ACPT_GROUPNO, m_dwGroupNoP);
	DDX_Text(pDX, IDC_EDT_ACPT_PLANTEMPLATENAME, m_csTemplateName);
	DDX_Text(pDX, IDC_EDT_ACPT_PLANTEMPLATENO, m_dwTemplateNo);
	DDX_Text(pDX, IDC_EDT_ACPT_WEEKPLANNO, m_dwWeekPlanNoP);
	DDX_Text(pDX, IDC_EDT_ACSP_PLANTEMPLATENO, m_dwTemplatePlanNo);
	DDX_Text(pDX, IDC_EDT_ACSP_DOORCARDNO, m_dwDoorNo);
	DDX_Text(pDX, IDC_STATIC_ACSP_DOORNO, m_csDoorOrCardNo);
	//}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDT_ACWP_LOCAL_CONTROLLER, m_iWeekPlanLocalController);
    DDX_Text(pDX, IDC_EDT_ACHP_LOCAL_CONTROLLER, m_iHolidayPlanLocalController);
    DDX_Text(pDX, IDC_EDT_ACHG_LOCAL_CONTROLLER, m_iHolidayGroupLocalController);
    DDX_Text(pDX, IDC_EDT_ACPT_LOCAL_CONTROLLER, m_iPlanTemplateLocalController);
}


BEGIN_MESSAGE_MAP(CDlgWeekPlan, CDialog)
	//{{AFX_MSG_MAP(CDlgWeekPlan)
	ON_BN_CLICKED(IDC_BUT_ACWP_WEEKPLAN_GET, OnButGet)
	ON_BN_CLICKED(IDC_BUT_ACWP_WEEKPLAN_SET, OnButSet)
	ON_CBN_SELCHANGE(IDC_COM_ACWP_TIMESEGMENT, OnSelchangeTimeSegment)
	ON_BN_CLICKED(IDC_BUT_ACHP_WEEKPLAN_GET, OnButGetHoliday)
	ON_BN_CLICKED(IDC_BUT_ACHP_WEEKPLAN_SET, OnButSetHoliday)
	ON_CBN_SELCHANGE(IDC_COM_ACHP_TIMESEGMENT, OnSelchangeTimesegmentH)
	ON_BN_CLICKED(IDC_BUT_ACHG_GET, OnButAchgGet)
	ON_BN_CLICKED(IDC_BUT_ACHG_SET, OnButAchgSet)
	ON_CBN_SELCHANGE(IDC_COMB_ACHG_GROUPINDEX, OnSelchangeGroupIndex)
	ON_BN_CLICKED(IDC_BUT_ACPT_GET, OnButAcptGet)
	ON_BN_CLICKED(IDC_BUT_ACPT_SET, OnButAcptSet)
	ON_CBN_SELCHANGE(IDC_COMB_ACPT_GROUPINDEX, OnSelchangeGroupindexP)
	ON_BN_CLICKED(IDC_BUT_ACSP_GET, OnButAcspGet)
	ON_BN_CLICKED(IDC_BUT_ACSP_SET, OnButAcspSet)
	ON_CBN_SELCHANGE(IDC_COM_ACSP_DEVICETYPE, OnSelchangeAcspDevicetype)
	ON_CBN_SELCHANGE(IDC_COM_ACWP_DAY, OnSelchangeDay)
	ON_NOTIFY(NM_CLICK, IDC_LST_ACWP_HOLIDAYPLAY, OnClickLstHolidayplan)
	ON_EN_CHANGE(IDC_EDT_ACHG_GROUPNO, OnChangeEdtAchgGroupno)
	ON_EN_KILLFOCUS(IDC_EDT_ACHG_GROUPNO, OnKillfocusEdtAchgGroupno)
	ON_NOTIFY(NM_CLICK, IDC_LST_ACWP_TEMPLATE, OnClickLstAcwpTemplate)
	ON_EN_KILLFOCUS(IDC_EDT_ACPT_GROUPNO, OnKillfocusEdtAcptGroupno)
	ON_BN_CLICKED(IDC_BUT_ACWP_TIMESEGEMENT, OnButAcwpTimesegementSet)
	ON_BN_CLICKED(IDC_BUT_ACWP_TIMESEGEMENT_H, OnButAcwpTimesegementH)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWeekPlan message handlers

BOOL CDlgWeekPlan::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_lDeviceID = g_pMainDlg->GetCurDeviceIndex(); 
    m_lUserID = g_struDeviceInfo[m_lDeviceID].lLoginID; 
        
    memset(&m_struPlanCfg, 0, sizeof(m_struPlanCfg));
    m_struPlanCfg.dwSize = sizeof(m_struPlanCfg); 
    memset(&m_struPlanCfgH, 0, sizeof(m_struPlanCfgH));
    m_struPlanCfgH.dwSize = sizeof(m_struPlanCfgH);  
    memset(&m_struGroupCfg, 0, sizeof(m_struGroupCfg));
    m_struGroupCfg.dwSize = sizeof(m_struGroupCfg); 

    memset(&m_struTemplateCfg, 0, sizeof(m_struTemplateCfg));
    m_struTemplateCfg.dwSize = sizeof(m_struTemplateCfg); 

    memset(&m_struPlanCond, 0, sizeof(m_struPlanCond));
    m_struPlanCond.dwSize = sizeof(m_struPlanCond);
    memset(&m_struPlanCondH, 0, sizeof(m_struPlanCondH));
    m_struPlanCondH.dwSize = sizeof(m_struPlanCondH);
    memset(&m_struGroupCond, 0, sizeof(m_struGroupCond));
    m_struGroupCond.dwSize = sizeof(m_struGroupCond);
    memset(&m_struTemplateCond, 0, sizeof(m_struTemplateCond));
    m_struTemplateCond.dwSize = sizeof(m_struTemplateCond);

	int i=0; 
    int iIndex = 0; 
    CString tmp; 
    for (i=0; i<MAX_TIMESEGMENT_V30; i++)
    {
        tmp.Format("Ê±¼ä¶Î%d", i+1); 
        iIndex = m_cmbTimeSegment.AddString(tmp); 
        m_cmbTimeSegment.SetItemData(iIndex, i); 
        iIndex = m_cmbTimeSegmentH.AddString(tmp); 
        m_cmbTimeSegmentH.SetItemData(iIndex, i); 
    }
    m_cmbTimeSegment.SetCurSel(0); 
    m_cmbTimeSegmentH.SetCurSel(0); 
//     m_cmbDeviceType.SetCurSel(0); 
//     m_cmbDeviceTypeH.SetCurSel(0); 
    m_cmbDay.SetCurSel(0); 
    
    for (i=0; i<MAX_HOLIDAY_PLAN_NUM; i++)
    {
        tmp.Format("%d", i); 
        iIndex = m_cmbGroupIndex.AddString(tmp); 
        m_cmbGroupIndex.SetItemData(iIndex, i); 
    }
    
    for (i=0; i<MAX_HOLIDAY_GROUP_NUM; i++)
    {
        tmp.Format("%d", i); 
        iIndex = m_cmbGroupIndexP.AddString(tmp); 
        m_cmbGroupIndexP.SetItemData(iIndex, i); 
    }
    char szLan[128]; 
    g_StringLanType(szLan, "ÐòºÅ", "Index");
    m_lstHolidayPlan.SetExtendedStyle(LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT);
    m_lstHolidayPlan.InsertColumn(0, szLan, LVCFMT_LEFT,80, -1); 
    g_StringLanType(szLan, "¼ÙÈÕ¼Æ»®±àºÅ", "Holiday Plan No.");
    m_lstHolidayPlan.InsertColumn(1, szLan, LVCFMT_LEFT,80, -1); 

    g_StringLanType(szLan, "ÐòºÅ", "Index");
    m_lstTemplate.SetExtendedStyle(LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT);
    m_lstTemplate.InsertColumn(0, szLan, LVCFMT_LEFT,80, -1); 
    g_StringLanType(szLan, "¼ÙÈÕ×é±àºÅ", "Holiday Group No.");
    m_lstTemplate.InsertColumn(1, szLan, LVCFMT_LEFT,80, -1); 

    UpdateLstGroupNo(); 
    UpdateLstGroupNoP();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgWeekPlan::OnButGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    DWORD dwCommand = 0;
    DWORD dwReturned = 0;
    char szLan[128];
    char *szCommand[] = { "NET_DVR_GET_WEEK_PLAN_CFG", "NET_DVR_GET_VERIFY_WEEK_PLAN", "NET_DVR_GET_CARD_RIGHT_WEEK_PLAN_V50" };
    switch (m_cmbDeviceType.GetCurSel())
    {
    case 0:
        dwCommand = NET_DVR_GET_WEEK_PLAN_CFG;
        m_iLastSel = -1;
        if (!NET_DVR_GetDVRConfig(m_lUserID, dwCommand, m_dwPlanNo, &m_struPlanCfg, sizeof(m_struPlanCfg), &dwReturned))
        {
            sprintf(szLan, "%s", szCommand[m_cmbDeviceType.GetCurSel()]);
            MessageBox(szLan);
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "%s", szCommand[m_cmbDeviceType.GetCurSel()]);
            return;
        }
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "%s", szCommand[m_cmbDeviceType.GetCurSel()]);
        m_cmbDay.SetCurSel(0);
        m_cmbTimeSegment.SetCurSel(0);
        m_BEnable = m_struPlanCfg.byEnable;
        UpdateData(FALSE);
        break;
    case 1:
        dwCommand = NET_DVR_GET_VERIFY_WEEK_PLAN;
        m_iLastSel = -1;
        if (!NET_DVR_GetDVRConfig(m_lUserID, dwCommand, m_dwPlanNo, &m_struPlanCfg, sizeof(m_struPlanCfg), &dwReturned))
        {
            sprintf(szLan, "%s", szCommand[m_cmbDeviceType.GetCurSel()]);
            MessageBox(szLan);
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "%s", szCommand[m_cmbDeviceType.GetCurSel()]);
            return;
        }
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "%s", szCommand[m_cmbDeviceType.GetCurSel()]);
        m_cmbDay.SetCurSel(0);
        m_cmbTimeSegment.SetCurSel(0);
        m_BEnable = m_struPlanCfg.byEnable;
        UpdateData(FALSE);
        break;
    case 2:
        dwCommand = NET_DVR_GET_CARD_RIGHT_WEEK_PLAN_V50;
        m_iLastSel = -1;
        m_struPlanCond.dwWeekPlanNumber = m_dwPlanNo;
        m_struPlanCond.wLocalControllerID = m_iWeekPlanLocalController;
        if (!NET_DVR_GetDeviceConfig(m_lUserID, dwCommand, 1, &m_struPlanCond, sizeof(m_struPlanCond), &dwReturned, &m_struPlanCfg, sizeof(m_struPlanCfg)))
        {
            sprintf(szLan, "%s", szCommand[m_cmbDeviceType.GetCurSel()]);
            MessageBox(szLan);
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "%s", szCommand[m_cmbDeviceType.GetCurSel()]);
            return;
        }
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "%s", szCommand[m_cmbDeviceType.GetCurSel()]);
        m_cmbDay.SetCurSel(0);
        m_cmbTimeSegment.SetCurSel(0);
        m_BEnable = m_struPlanCfg.byEnable;
        UpdateData(FALSE);
        break;
    default:
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "unknow command");
        return;
    }

    //UpdateTimeSegment();
}

void CDlgWeekPlan::OnButSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    DWORD dwCommand = 0;
    DWORD dwReturned = 0;
    char szLan[128];
    char *szCommand[] = { "NET_DVR_SET_WEEK_PLAN_CFG", "NET_DVR_SET_VERIFY_WEEK_PLAN", "NET_DVR_SET_CARD_RIGHT_WEEK_PLAN_V50" };
    switch (m_cmbDeviceType.GetCurSel())
    {
    case 0:
        dwCommand = NET_DVR_SET_WEEK_PLAN_CFG;
        m_struPlanCfg.byEnable = m_BEnable;
        if (!NET_DVR_SetDVRConfig(m_lUserID, dwCommand, m_dwPlanNo, &m_struPlanCfg, sizeof(m_struPlanCfg)))
        {
            sprintf(szLan, "%s", szCommand[m_cmbDeviceType.GetCurSel()]);
            MessageBox(szLan);
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "%s", szCommand[m_cmbDeviceType.GetCurSel()]);
            return;
        }
        else
        {
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "%s", szCommand[m_cmbDeviceType.GetCurSel()]);
        }
        break;
    case 1:
        dwCommand = NET_DVR_SET_VERIFY_WEEK_PLAN;
        m_struPlanCfg.byEnable = m_BEnable;
        if (!NET_DVR_SetDVRConfig(m_lUserID, dwCommand, m_dwPlanNo, &m_struPlanCfg, sizeof(m_struPlanCfg)))
        {
            sprintf(szLan, "%s", szCommand[m_cmbDeviceType.GetCurSel()]);
            MessageBox(szLan);
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "%s", szCommand[m_cmbDeviceType.GetCurSel()]);
            return;
        }
        else
        {
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "%s", szCommand[m_cmbDeviceType.GetCurSel()]);
        }
        break;
    case 2:
        dwCommand = NET_DVR_SET_CARD_RIGHT_WEEK_PLAN_V50;
        m_struPlanCond.dwWeekPlanNumber = m_dwPlanNo;
        m_struPlanCond.wLocalControllerID = m_iWeekPlanLocalController;
        m_struPlanCfg.byEnable = m_BEnable;
        if (!NET_DVR_SetDeviceConfig(m_lUserID, dwCommand, 1, &m_struPlanCond, sizeof(m_struPlanCond), &dwReturned, &m_struPlanCfg, sizeof(m_struPlanCfg)))
        {
            sprintf(szLan, "%s", szCommand[m_cmbDeviceType.GetCurSel()]);
            MessageBox(szLan);
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "%s", szCommand[m_cmbDeviceType.GetCurSel()]);
            return;
        }
        else
        {
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "%s", szCommand[m_cmbDeviceType.GetCurSel()]);
        }
        break;
    default:
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "unknow command");
        return;
    }
}

void CDlgWeekPlan::UpdateTimeSegment(BYTE byDay, BYTE byTimeSegment)
{
    if (m_iLastSel != -1)
    {
        SaveTimeSegment(m_iLastSel); 
    }
    m_iLastSel = ((DWORD) byDay << 8) +  byTimeSegment; 

    NET_DVR_SINGLE_PLAN_SEGMENT &struPlanCfg = m_struPlanCfg.struPlanCfg[byDay][byTimeSegment]; 
    m_BTSEnable = struPlanCfg.byEnable;    
    UpdateData(FALSE); 
    m_cmbDoorStatus.SetCurSel(struPlanCfg.byDoorStatus); 
    m_cmbVerify.SetCurSel(struPlanCfg.byVerifyMode); 
    if ( !CheckDate(struPlanCfg.struTimeSegment.struEndTime) || !CheckDate(struPlanCfg.struTimeSegment.struBeginTime) )
    {
        return ; 
    }
   
    m_DTEndTime.SetTime(struPlanCfg.struTimeSegment.struEndTime.byHour,\
                    struPlanCfg.struTimeSegment.struEndTime.byMinute,\
                    struPlanCfg.struTimeSegment.struEndTime.bySecond ); 
    m_DTStartTime.SetTime(struPlanCfg.struTimeSegment.struBeginTime.byHour,\
                      struPlanCfg.struTimeSegment.struBeginTime.byMinute,\
                        struPlanCfg.struTimeSegment.struBeginTime.bySecond ); 

    UpdateData(FALSE); 
}

void CDlgWeekPlan::UpdateTimeSegmentH(BYTE byTimeSegment)
{
    if (m_iLastSelH != -1)
    {
        SaveTimeSegmentH(m_iLastSelH); 
    }
    m_iLastSelH = byTimeSegment; 

    NET_DVR_SINGLE_PLAN_SEGMENT &struPlanCfg = m_struPlanCfgH.struPlanCfg[byTimeSegment]; 
    m_BTSEnableH = struPlanCfg.byEnable; 

    UpdateData(FALSE); 
    m_cmbDoorStatusH.SetCurSel(struPlanCfg.byDoorStatus); 
    m_cmbVerifyH.SetCurSel(struPlanCfg.byVerifyMode); 
    if ( !CheckDate(struPlanCfg.struTimeSegment.struEndTime) || !CheckDate(struPlanCfg.struTimeSegment.struBeginTime) )
    {
        return ; 
    }

    m_dtEndTimeH.SetTime(struPlanCfg.struTimeSegment.struEndTime.byHour,\
                    struPlanCfg.struTimeSegment.struEndTime.byMinute,\
                    struPlanCfg.struTimeSegment.struEndTime.bySecond ); 
    m_dtStartTimeH.SetTime(struPlanCfg.struTimeSegment.struBeginTime.byHour,\
                      struPlanCfg.struTimeSegment.struBeginTime.byMinute,\
                      struPlanCfg.struTimeSegment.struBeginTime.bySecond ); 
    UpdateData(FALSE); 
} 

void CDlgWeekPlan::OnSelchangeTimeSegment() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
    BYTE byDay = m_cmbDay.GetCurSel(); 
    BYTE byTimeSegment = m_cmbTimeSegment.GetCurSel(); 
    //UpdateTimeSegment(byDay, byTimeSegment); 
}

void CDlgWeekPlan::SaveTimeSegmentH(DWORD dwSelH)
{
    UpdateData(TRUE); 
    BYTE byTimeSegment = dwSelH & 0xff; 
    NET_DVR_SINGLE_PLAN_SEGMENT &struPlanCfg = m_struPlanCfgH.struPlanCfg[byTimeSegment]; 
    struPlanCfg.byEnable = m_BTSEnableH; 
    struPlanCfg.byVerifyMode   = m_cmbVerifyH.GetCurSel(); 
    struPlanCfg.byDoorStatus = m_cmbDoorStatusH.GetCurSel(); 
    struPlanCfg.struTimeSegment.struBeginTime.byHour = m_dtStartTimeH.GetHour();
    struPlanCfg.struTimeSegment.struBeginTime.byMinute = m_dtStartTimeH.GetMinute();
    struPlanCfg.struTimeSegment.struBeginTime.bySecond = m_dtStartTimeH.GetSecond();
    struPlanCfg.struTimeSegment.struEndTime.byHour = m_dtEndTimeH.GetHour();
    struPlanCfg.struTimeSegment.struEndTime.byMinute = m_dtEndTimeH.GetMinute();
    struPlanCfg.struTimeSegment.struEndTime.bySecond = m_dtEndTimeH.GetSecond();
    UpdateData(FALSE); 
} 

void CDlgWeekPlan::SaveTimeSegment(DWORD dwSel)
{
    UpdateData(TRUE); 
    BYTE byDay = (dwSel >> 8) &0xff ; 
    BYTE byTimeSegment = dwSel & 0xff; 
    NET_DVR_SINGLE_PLAN_SEGMENT &struPlanCfg = m_struPlanCfg.struPlanCfg[byDay][byTimeSegment]; 
    struPlanCfg.byEnable = m_BTSEnable; 
    struPlanCfg.byVerifyMode   = m_cmbVerify.GetCurSel(); 
    struPlanCfg.byDoorStatus = m_cmbDoorStatus.GetCurSel(); 
    struPlanCfg.struTimeSegment.struBeginTime.byHour = m_DTStartTime.GetHour();
    struPlanCfg.struTimeSegment.struBeginTime.byMinute = m_DTStartTime.GetMinute();
    struPlanCfg.struTimeSegment.struBeginTime.bySecond = m_DTStartTime.GetSecond();
    struPlanCfg.struTimeSegment.struEndTime.byHour = m_DTEndTime.GetHour();
    struPlanCfg.struTimeSegment.struEndTime.byMinute = m_DTEndTime.GetMinute();
    struPlanCfg.struTimeSegment.struEndTime.bySecond = m_DTEndTime.GetSecond();
    UpdateData(FALSE); 
}

void CDlgWeekPlan::OnButGetHoliday() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    DWORD dwCommand = 0;
    DWORD dwReturned = 0;
    char szLan[128] = { 0 };
    char *szCommand[] = { "NET_DVR_GET_DOOR_STATUS_HOLIDAY_PLAN", "NET_DVR_GET_VERIFY_HOLIDAY_PLAN", "NET_DVR_GET_CARD_RIGHT_HOLIDAY_PLAN_V50" };
    switch (m_cmbDeviceTypeH.GetCurSel())
    {
    case 0:
        dwCommand = NET_DVR_GET_DOOR_STATUS_HOLIDAY_PLAN;
        m_iLastSelH = -1;
        if (!NET_DVR_GetDVRConfig(m_lUserID, dwCommand, m_dwPlanNoH, &m_struPlanCfgH, sizeof(m_struPlanCfgH), &dwReturned))
        {
            sprintf(szLan, "%s", szCommand[m_cmbDeviceTypeH.GetCurSel()]);
            MessageBox(szLan);
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "%s", szCommand[m_cmbDeviceTypeH.GetCurSel()]);
            return;
        }
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "%s", szCommand[m_cmbDeviceTypeH.GetCurSel()]);
        m_cmbTimeSegmentH.SetCurSel(0);
        if (!CheckDate(m_struPlanCfgH.struBeginDate) || !CheckDate(m_struPlanCfgH.struEndDate))
        {
            return;
        }

        m_dtStartDate.SetDate(m_struPlanCfgH.struBeginDate.wYear, m_struPlanCfgH.struBeginDate.byMonth, m_struPlanCfgH.struBeginDate.byDay);
        m_dtEndDate.SetDate(m_struPlanCfgH.struEndDate.wYear, m_struPlanCfgH.struEndDate.byMonth, m_struPlanCfgH.struEndDate.byDay);
        m_BEnableH = m_struPlanCfgH.byEnable;
        UpdateData(FALSE);
       // UpdateTimeSegmentH();
        break;
    case 1:
        dwCommand = NET_DVR_GET_VERIFY_HOLIDAY_PLAN;
        m_iLastSelH = -1;
        if (!NET_DVR_GetDVRConfig(m_lUserID, dwCommand, m_dwPlanNoH, &m_struPlanCfgH, sizeof(m_struPlanCfgH), &dwReturned))
        {
            sprintf(szLan, "%s", szCommand[m_cmbDeviceTypeH.GetCurSel()]);
            MessageBox(szLan);
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "%s", szCommand[m_cmbDeviceTypeH.GetCurSel()]);
            return;
        }
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "%s", szCommand[m_cmbDeviceTypeH.GetCurSel()]);
        m_cmbTimeSegmentH.SetCurSel(0);
        if (!CheckDate(m_struPlanCfgH.struBeginDate) || !CheckDate(m_struPlanCfgH.struEndDate))
        {
            return;
        }

        m_dtStartDate.SetDate(m_struPlanCfgH.struBeginDate.wYear, m_struPlanCfgH.struBeginDate.byMonth, m_struPlanCfgH.struBeginDate.byDay);
        m_dtEndDate.SetDate(m_struPlanCfgH.struEndDate.wYear, m_struPlanCfgH.struEndDate.byMonth, m_struPlanCfgH.struEndDate.byDay);
        m_BEnableH = m_struPlanCfgH.byEnable;
        UpdateData(FALSE);
        //UpdateTimeSegmentH();
        break;
    case 2:
        dwCommand = NET_DVR_GET_CARD_RIGHT_HOLIDAY_PLAN_V50;
        m_iLastSelH = -1;
        m_struPlanCondH.dwHolidayPlanNumber = m_dwPlanNoH;
        m_struPlanCondH.wLocalControllerID = m_iHolidayPlanLocalController;
        if (!NET_DVR_GetDeviceConfig(m_lUserID, dwCommand, 1, &m_struPlanCondH, sizeof(m_struPlanCondH), &dwReturned, &m_struPlanCfgH, sizeof(m_struPlanCfgH)))
        {
            sprintf(szLan, "%s", szCommand[m_cmbDeviceTypeH.GetCurSel()]);
            MessageBox(szLan);
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "%s", szCommand[m_cmbDeviceTypeH.GetCurSel()]);
            return;
        }
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "%s", szCommand[m_cmbDeviceTypeH.GetCurSel()]);
        m_cmbTimeSegmentH.SetCurSel(0);
        if (!CheckDate(m_struPlanCfgH.struBeginDate) || !CheckDate(m_struPlanCfgH.struEndDate))
        {
            return;
        }

        m_dtStartDate.SetDate(m_struPlanCfgH.struBeginDate.wYear, m_struPlanCfgH.struBeginDate.byMonth, m_struPlanCfgH.struBeginDate.byDay);
        m_dtEndDate.SetDate(m_struPlanCfgH.struEndDate.wYear, m_struPlanCfgH.struEndDate.byMonth, m_struPlanCfgH.struEndDate.byDay);
        m_BEnableH = m_struPlanCfgH.byEnable;
        UpdateData(FALSE);
       // UpdateTimeSegmentH();
        break;
    default:
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "unknow command");
        return;
    }
}

void CDlgWeekPlan::OnButSetHoliday() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    DWORD dwCommand = 0;
    DWORD dwReturned = 0;
    char szLan[128] = { 0 };
    char *szCommand[] = { "NET_DVR_SET_DOOR_STATUS_HOLIDAY_PLAN", "NET_DVR_SET_VERIFY_HOLIDAY_PLAN", "NET_DVR_SET_CARD_RIGHT_HOLIDAY_PLAN_V50" };
    switch (m_cmbDeviceTypeH.GetCurSel())
    {
    case 0:
        dwCommand = NET_DVR_SET_DOOR_STATUS_HOLIDAY_PLAN;
        m_struPlanCfgH.byEnable = m_BEnableH;
        m_struPlanCfgH.struBeginDate.wYear = m_dtStartDate.GetYear();
        m_struPlanCfgH.struBeginDate.byMonth = m_dtStartDate.GetMonth();
        m_struPlanCfgH.struBeginDate.byDay = m_dtStartDate.GetDay();
        m_struPlanCfgH.struEndDate.wYear = m_dtEndDate.GetYear();
        m_struPlanCfgH.struEndDate.byMonth = m_dtEndDate.GetMonth();
        m_struPlanCfgH.struEndDate.byDay = m_dtEndDate.GetDay();

        if (!NET_DVR_SetDVRConfig(m_lUserID, dwCommand, m_dwPlanNoH, &m_struPlanCfgH, sizeof(m_struPlanCfgH)))
        {
            sprintf(szLan, "%s", szCommand[m_cmbDeviceTypeH.GetCurSel()]);
            MessageBox(szLan);
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "%s", szCommand[m_cmbDeviceTypeH.GetCurSel()]);
            return;
        }
        else
        {
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "%s", szCommand[m_cmbDeviceTypeH.GetCurSel()]);
        }
        break;
    case 1:
        dwCommand = NET_DVR_SET_VERIFY_HOLIDAY_PLAN;
        m_struPlanCfgH.byEnable = m_BEnableH;
        m_struPlanCfgH.struBeginDate.wYear = m_dtStartDate.GetYear();
        m_struPlanCfgH.struBeginDate.byMonth = m_dtStartDate.GetMonth();
        m_struPlanCfgH.struBeginDate.byDay = m_dtStartDate.GetDay();
        m_struPlanCfgH.struEndDate.wYear = m_dtEndDate.GetYear();
        m_struPlanCfgH.struEndDate.byMonth = m_dtEndDate.GetMonth();
        m_struPlanCfgH.struEndDate.byDay = m_dtEndDate.GetDay();

        if (!NET_DVR_SetDVRConfig(m_lUserID, dwCommand, m_dwPlanNoH, &m_struPlanCfgH, sizeof(m_struPlanCfgH)))
        {
            sprintf(szLan, "%s", szCommand[m_cmbDeviceTypeH.GetCurSel()]);
            MessageBox(szLan);
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "%s", szCommand[m_cmbDeviceTypeH.GetCurSel()]);
            return;
        }
        else
        {
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "%s", szCommand[m_cmbDeviceTypeH.GetCurSel()]);
        }
        break;
    case 2:
        dwCommand = NET_DVR_SET_CARD_RIGHT_HOLIDAY_PLAN_V50;
        m_struPlanCondH.dwHolidayPlanNumber = m_dwPlanNoH;
        m_struPlanCondH.wLocalControllerID = m_iHolidayPlanLocalController;
        m_struPlanCfgH.byEnable = m_BEnableH;
        m_struPlanCfgH.struBeginDate.wYear = m_dtStartDate.GetYear();
        m_struPlanCfgH.struBeginDate.byMonth = m_dtStartDate.GetMonth();
        m_struPlanCfgH.struBeginDate.byDay = m_dtStartDate.GetDay();
        m_struPlanCfgH.struEndDate.wYear = m_dtEndDate.GetYear();
        m_struPlanCfgH.struEndDate.byMonth = m_dtEndDate.GetMonth();
        m_struPlanCfgH.struEndDate.byDay = m_dtEndDate.GetDay();

        if (!NET_DVR_SetDeviceConfig(m_lUserID, dwCommand, 1, &m_struPlanCondH, sizeof(m_struPlanCondH), &dwReturned, &m_struPlanCfgH, sizeof(m_struPlanCfgH)))
        {
            sprintf(szLan, "%s", szCommand[m_cmbDeviceTypeH.GetCurSel()]);
            MessageBox(szLan);
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "%s", szCommand[m_cmbDeviceTypeH.GetCurSel()]);
            return;
        }
        else
        {
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "%s", szCommand[m_cmbDeviceTypeH.GetCurSel()]);
        }
        break;
    default:
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "unknow command");
        return;
    }
}

void CDlgWeekPlan::OnSelchangeTimesegmentH() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    BYTE byTimeSegment = m_cmbTimeSegmentH.GetCurSel(); 
    //UpdateTimeSegmentH(byTimeSegment); 
}

void CDlgWeekPlan::OnButAchgGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    DWORD dwCommand = 0;
    DWORD dwReturned = 0;
    char szLan[128] = { 0 };
    char *szCommand[] = { "NET_DVR_GET_DOOR_STATUS_HOLIDAY_GROUP", "NET_DVR_GET_VERIFY_HOLIDAY_GROUP", "NET_DVR_GET_CARD_RIGHT_HOLIDAY_GROUP_V50" };
    switch (m_cmbDeviceTypeG.GetCurSel())
    {
    case 0:
        dwCommand = NET_DVR_GET_DOOR_STATUS_HOLIDAY_GROUP;
        m_iLastGroupIndex = -1;
        if (!NET_DVR_GetDVRConfig(m_lUserID, dwCommand, m_dwGroupPlanNo, &m_struGroupCfg, sizeof(m_struGroupCfg), &dwReturned))
        {
            sprintf(szLan, "%s", szCommand[m_cmbDeviceTypeG.GetCurSel()]);
            MessageBox(szLan);
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "%s", szCommand[m_cmbDeviceTypeG.GetCurSel()]);
            return;
        }
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "%s", szCommand[m_cmbDeviceTypeG.GetCurSel()]);
        m_BEnableG = m_struGroupCfg.byEnable;
        m_csGroupName.Format("%s", (char *)m_struGroupCfg.byGroupName);
        m_cmbGroupIndex.SetCurSel(0);
        UpdateData(FALSE);
        break;
    case 1:
        dwCommand = NET_DVR_GET_VERIFY_HOLIDAY_GROUP;
        m_iLastGroupIndex = -1;
        if (!NET_DVR_GetDVRConfig(m_lUserID, dwCommand, m_dwGroupPlanNo, &m_struGroupCfg, sizeof(m_struGroupCfg), &dwReturned))
        {
            sprintf(szLan, "%s", szCommand[m_cmbDeviceTypeG.GetCurSel()]);
            MessageBox(szLan);
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "%s", szCommand[m_cmbDeviceTypeG.GetCurSel()]);
            return;
        }
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "%s", szCommand[m_cmbDeviceTypeG.GetCurSel()]);
        m_BEnableG = m_struGroupCfg.byEnable;
        m_csGroupName.Format("%s", (char *)m_struGroupCfg.byGroupName);
        m_cmbGroupIndex.SetCurSel(0);
        UpdateData(FALSE);
        break;
    case 2:
        dwCommand = NET_DVR_GET_CARD_RIGHT_HOLIDAY_GROUP_V50;
        m_struGroupCond.dwHolidayGroupNumber = m_dwGroupPlanNo;
        m_struGroupCond.wLocalControllerID = m_iHolidayGroupLocalController;
        m_iLastGroupIndex = -1;
        if (!NET_DVR_GetDeviceConfig(m_lUserID, dwCommand, 1, &m_struGroupCond, sizeof(m_struGroupCond), &dwReturned, &m_struGroupCfg, sizeof(m_struGroupCfg)))
        {
            sprintf(szLan, "%s", szCommand[m_cmbDeviceTypeG.GetCurSel()]);
            MessageBox(szLan);
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "%s", szCommand[m_cmbDeviceTypeG.GetCurSel()]);
            return;
        }
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "%s", szCommand[m_cmbDeviceTypeG.GetCurSel()]);
        m_BEnableG = m_struGroupCfg.byEnable;
        m_csGroupName.Format("%s", (char *)m_struGroupCfg.byGroupName);
        m_cmbGroupIndex.SetCurSel(0);
        UpdateData(FALSE);
        break;
    default:
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "unknow command");
        return;
    }
    UpdateLstGroupNo();
}

void CDlgWeekPlan::OnButAchgSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    DWORD dwCommand = 0;
    DWORD dwReturned = 0;
    char szLan[128] = { 0 };
    char *szCommand[] = { "NET_DVR_SET_DOOR_STATUS_HOLIDAY_GROUP", "NET_DVR_SET_VERIFY_HOLIDAY_GROUP", "NET_DVR_SET_CARD_RIGHT_HOLIDAY_GROUP_V50" };
    switch (m_cmbDeviceTypeG.GetCurSel())
    {
    case 0:
        dwCommand = NET_DVR_SET_DOOR_STATUS_HOLIDAY_GROUP;
        m_struGroupCfg.dwSize = sizeof(m_struGroupCfg);
        m_struGroupCfg.byEnable = m_BEnableG;
        strncpy((char *)m_struGroupCfg.byGroupName, (LPCTSTR)m_csGroupName, sizeof(m_struGroupCfg.byGroupName));
        //    m_struGroupCfg.dwHolidayPlanNo[m_cmbGroupIndex.GetCurSel()] = m_dwGroupNo; 
        if (!NET_DVR_SetDVRConfig(m_lUserID, dwCommand, m_dwGroupPlanNo, &m_struGroupCfg, sizeof(m_struGroupCfg)))
        {
            sprintf(szLan, "%s", szCommand[m_cmbDeviceTypeG.GetCurSel()]);
            MessageBox(szLan);
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "%s", szCommand[m_cmbDeviceTypeG.GetCurSel()]);
            return;
        }
        else
        {
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "%s", szCommand[m_cmbDeviceTypeG.GetCurSel()]);
        }
        break;
    case 1:
        dwCommand = NET_DVR_SET_VERIFY_HOLIDAY_GROUP;
        m_struGroupCfg.dwSize = sizeof(m_struGroupCfg);
        m_struGroupCfg.byEnable = m_BEnableG;
        strncpy((char *)m_struGroupCfg.byGroupName, (LPCTSTR)m_csGroupName, sizeof(m_struGroupCfg.byGroupName));
        //    m_struGroupCfg.dwHolidayPlanNo[m_cmbGroupIndex.GetCurSel()] = m_dwGroupNo; 
        if (!NET_DVR_SetDVRConfig(m_lUserID, dwCommand, m_dwGroupPlanNo, &m_struGroupCfg, sizeof(m_struGroupCfg)))
        {
            sprintf(szLan, "%s", szCommand[m_cmbDeviceTypeG.GetCurSel()]);
            MessageBox(szLan);
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "%s", szCommand[m_cmbDeviceTypeG.GetCurSel()]);
            return;
        }
        else
        {
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "%s", szCommand[m_cmbDeviceTypeG.GetCurSel()]);
        }
        break;
    case 2:
        dwCommand = NET_DVR_SET_CARD_RIGHT_HOLIDAY_GROUP_V50;
        m_struGroupCond.dwHolidayGroupNumber = m_dwGroupPlanNo;
        m_struGroupCond.wLocalControllerID = m_iHolidayGroupLocalController;
        m_struGroupCfg.dwSize = sizeof(m_struGroupCfg);
        m_struGroupCfg.byEnable = m_BEnableG;
        strncpy((char *)m_struGroupCfg.byGroupName, (LPCTSTR)m_csGroupName, sizeof(m_struGroupCfg.byGroupName));
        //    m_struGroupCfg.dwHolidayPlanNo[m_cmbGroupIndex.GetCurSel()] = m_dwGroupNo; 
        if (!NET_DVR_SetDeviceConfig(m_lUserID, dwCommand, 1, &m_struGroupCond, sizeof(m_struGroupCond), &dwReturned, &m_struGroupCfg, sizeof(m_struGroupCfg)))
        {
            sprintf(szLan, "%s", szCommand[m_cmbDeviceTypeG.GetCurSel()]);
            MessageBox(szLan);
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "%s", szCommand[m_cmbDeviceTypeG.GetCurSel()]);
            return;
        }
        else
        {
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "%s", szCommand[m_cmbDeviceTypeG.GetCurSel()]);
        }
        break;
    default:
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "unknow command");
        return;
    }
}

void CDlgWeekPlan::OnSelchangeGroupIndex() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    if (m_iLastGroupIndex != -1)
    {
        m_struGroupCfg.dwHolidayPlanNo[m_iLastGroupIndex] = m_dwGroupNo; 
    }
    int iIndex = m_cmbGroupIndex.GetCurSel(); 
    if (iIndex >= 0)
    {
        m_dwGroupNo = m_struGroupCfg.dwHolidayPlanNo[iIndex]; 
        m_iLastGroupIndex = iIndex; 
    }
    UpdateData(FALSE); 
}

void CDlgWeekPlan::OnButAcptGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    DWORD dwCommand = 0;
    DWORD dwReturned = 0;
    char szLan[128] = { 0 };
    char csTemplateName[TEMPLATE_NAME_LEN + 1] = { 0 };
    char *szCommand[] = { "NET_DVR_GET_DOOR_STATUS_PLAN_TEMPLATE", "NET_DVR_GET_VERIFY_PLAN_TEMPLATE", "NET_DVR_GET_CARD_RIGHT_PLAN_TEMPLATE_V50" };
    switch (m_cmbDeviceTypeP.GetCurSel())
    {
    case 0:
        dwCommand = NET_DVR_GET_DOOR_STATUS_PLAN_TEMPLATE;
        m_iLastGroupIndexP = -1;
        if (!NET_DVR_GetDVRConfig(m_lUserID, dwCommand, m_dwTemplateNo, &m_struTemplateCfg, sizeof(m_struTemplateCfg), &dwReturned))
        {
            sprintf(szLan, "%s", szCommand[m_cmbDeviceTypeP.GetCurSel()]);
            MessageBox(szLan);
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "%s", szCommand[m_cmbDeviceTypeP.GetCurSel()]);
            return;
        }
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "%s", szCommand[m_cmbDeviceTypeP.GetCurSel()]);
        m_BEnableP = m_struTemplateCfg.byEnable;
        m_dwWeekPlanNoP = m_struTemplateCfg.dwWeekPlanNo;

        csTemplateName[TEMPLATE_NAME_LEN] = 0;
        memcpy(csTemplateName, m_struTemplateCfg.byTemplateName, TEMPLATE_NAME_LEN);
        m_csTemplateName.Format("%s", csTemplateName);

        m_cmbGroupIndexP.SetCurSel(0);
        UpdateData(FALSE);
        break;
    case 1:
        dwCommand = NET_DVR_GET_VERIFY_PLAN_TEMPLATE;
        m_iLastGroupIndexP = -1;
        if (!NET_DVR_GetDVRConfig(m_lUserID, dwCommand, m_dwTemplateNo, &m_struTemplateCfg, sizeof(m_struTemplateCfg), &dwReturned))
        {
            sprintf(szLan, "%s", szCommand[m_cmbDeviceTypeP.GetCurSel()]);
            MessageBox(szLan);
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "%s", szCommand[m_cmbDeviceTypeP.GetCurSel()]);
            return;
        }
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "%s", szCommand[m_cmbDeviceTypeP.GetCurSel()]);
        m_BEnableP = m_struTemplateCfg.byEnable;
        m_dwWeekPlanNoP = m_struTemplateCfg.dwWeekPlanNo;

        csTemplateName[TEMPLATE_NAME_LEN] = 0;
        memcpy(csTemplateName, m_struTemplateCfg.byTemplateName, TEMPLATE_NAME_LEN);
        m_csTemplateName.Format("%s", csTemplateName);

        m_cmbGroupIndexP.SetCurSel(0);
        UpdateData(FALSE);
        break;
    case 2:
        dwCommand = NET_DVR_GET_CARD_RIGHT_PLAN_TEMPLATE_V50;
        m_struTemplateCond.dwPlanTemplateNumber = m_dwTemplateNo;
        m_struTemplateCond.wLocalControllerID = m_iPlanTemplateLocalController;
        m_iLastGroupIndexP = -1;
        if (!NET_DVR_GetDeviceConfig(m_lUserID, dwCommand, 1, &m_struTemplateCond, sizeof(m_struTemplateCond), &dwReturned, &m_struTemplateCfg, sizeof(m_struTemplateCfg)))
        {
            sprintf(szLan, "%s", szCommand[m_cmbDeviceTypeP.GetCurSel()]);
            MessageBox(szLan);
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "%s", szCommand[m_cmbDeviceTypeP.GetCurSel()]);
            return;
        }
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "%s", szCommand[m_cmbDeviceTypeP.GetCurSel()]);
        m_BEnableP = m_struTemplateCfg.byEnable;
        m_dwWeekPlanNoP = m_struTemplateCfg.dwWeekPlanNo;

        csTemplateName[TEMPLATE_NAME_LEN] = 0;
        memcpy(csTemplateName, m_struTemplateCfg.byTemplateName, TEMPLATE_NAME_LEN);
        m_csTemplateName.Format("%s", csTemplateName);

        m_cmbGroupIndexP.SetCurSel(0);
        UpdateData(FALSE);
        break;
    default:
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "unknow command");
        return;
    }
    UpdateLstGroupNoP();
}

void CDlgWeekPlan::OnButAcptSet()
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    DWORD dwCommand = 0;
    DWORD dwReturned = 0;
    char szLan[128] = { 0 };
    char *szCommand[] = { "NET_DVR_SET_DOOR_STATUS_PLAN_TEMPLATE", "NET_DVR_SET_VERIFY_PLAN_TEMPLATE", "NET_DVR_SET_CARD_RIGHT_PLAN_TEMPLATE_V50" };
    switch (m_cmbDeviceTypeP.GetCurSel())
    {
    case 0:
        dwCommand = NET_DVR_SET_DOOR_STATUS_PLAN_TEMPLATE;
        m_struTemplateCfg.dwSize = sizeof(m_struTemplateCfg);
        m_struTemplateCfg.byEnable = m_BEnableP;

        strcpy((char *)m_struTemplateCfg.byTemplateName, (LPCTSTR)m_csTemplateName);
        m_struTemplateCfg.dwWeekPlanNo = m_dwWeekPlanNoP;
        //    m_struTemplateCfg.dwHolidayGroupNo[m_cmbGroupIndexP.GetCurSel()] = m_dwGroupNoP; 
        if (!NET_DVR_SetDVRConfig(m_lUserID, dwCommand, m_dwTemplateNo, &m_struTemplateCfg, sizeof(m_struTemplateCfg)))
        {
            sprintf(szLan, "%s", szCommand[m_cmbDeviceTypeP.GetCurSel()]);
            MessageBox(szLan);
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "%s", szCommand[m_cmbDeviceTypeP.GetCurSel()]);
            return;
        }
        else
        {
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "%s", szCommand[m_cmbDeviceTypeP.GetCurSel()]);
        }
        break;
    case 1:
        dwCommand = NET_DVR_SET_VERIFY_PLAN_TEMPLATE;
        m_struTemplateCfg.dwSize = sizeof(m_struTemplateCfg);
        m_struTemplateCfg.byEnable = m_BEnableP;

        strcpy((char *)m_struTemplateCfg.byTemplateName, (LPCTSTR)m_csTemplateName);
        m_struTemplateCfg.dwWeekPlanNo = m_dwWeekPlanNoP;
        //    m_struTemplateCfg.dwHolidayGroupNo[m_cmbGroupIndexP.GetCurSel()] = m_dwGroupNoP; 
        if (!NET_DVR_SetDVRConfig(m_lUserID, dwCommand, m_dwTemplateNo, &m_struTemplateCfg, sizeof(m_struTemplateCfg)))
        {
            sprintf(szLan, "%s", szCommand[m_cmbDeviceTypeP.GetCurSel()]);
            MessageBox(szLan);
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "%s", szCommand[m_cmbDeviceTypeP.GetCurSel()]);
            return;
        }
        else
        {
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "%s", szCommand[m_cmbDeviceTypeP.GetCurSel()]);
        }
        break;
    case 2:
        dwCommand = NET_DVR_SET_CARD_RIGHT_PLAN_TEMPLATE_V50;
        m_struTemplateCond.dwPlanTemplateNumber = m_dwTemplateNo;
        m_struTemplateCond.wLocalControllerID = m_iPlanTemplateLocalController;
        m_struTemplateCfg.dwSize = sizeof(m_struTemplateCfg);
        m_struTemplateCfg.byEnable = m_BEnableP;

        strcpy((char *)m_struTemplateCfg.byTemplateName, (LPCTSTR)m_csTemplateName);
        m_struTemplateCfg.dwWeekPlanNo = m_dwWeekPlanNoP;
        //    m_struTemplateCfg.dwHolidayGroupNo[m_cmbGroupIndexP.GetCurSel()] = m_dwGroupNoP; 
        if (!NET_DVR_SetDeviceConfig(m_lUserID, dwCommand, 1, &m_struTemplateCond, sizeof(m_struTemplateCond), &dwReturned, &m_struTemplateCfg, sizeof(m_struTemplateCfg)))
        {
            sprintf(szLan, "%s", szCommand[m_cmbDeviceTypeP.GetCurSel()]);
            MessageBox(szLan);
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "%s", szCommand[m_cmbDeviceTypeP.GetCurSel()]);
            return;
        }
        else
        {
            g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "%s", szCommand[m_cmbDeviceTypeP.GetCurSel()]);
        }
        break;
    default:
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "unknow command");
        return;
    }
}

void CDlgWeekPlan::OnSelchangeGroupindexP() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if (m_iLastGroupIndexP != -1)
    {
        m_struTemplateCfg.dwHolidayGroupNo[m_iLastGroupIndexP] = m_dwGroupNoP; 
    }
    int iIndex = m_cmbGroupIndexP.GetCurSel(); 
    if (iIndex >= 0)
    {
        m_dwGroupNoP =  m_struTemplateCfg.dwHolidayGroupNo[iIndex]; 
        m_iLastGroupIndexP = iIndex; 
    }
    UpdateData(FALSE); 	
}

void CDlgWeekPlan::OnButAcspGet()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
    DWORD dwCommand; 
    DWORD dwReturned; 
    char szLan[128] = { 0 };
	char *szCommand[] = {"NET_DVR_GET_DOOR_STATUS_PLAN", "NET_DVR_GET_CARD_READER_PLAN"}; 
    NET_DVR_DOOR_STATUS_PLAN struStatusPlan = {0}; 
    LPNET_DVR_DOOR_STATUS_PLAN lpStatusPlan = &struStatusPlan;
    switch(m_cmbDeviceTypeS.GetCurSel())
    {
    case 0:
        dwCommand = NET_DVR_GET_DOOR_STATUS_PLAN ;
        break; 
    case 1:
        dwCommand = NET_DVR_GET_CARD_READER_PLAN;    
        break;     
    default:
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "unknow command"); 
        return; 
    }
    if (!NET_DVR_GetDVRConfig(m_lUserID, dwCommand, m_dwDoorNo, lpStatusPlan, sizeof(*lpStatusPlan), &dwReturned) )
    {
        sprintf(szLan, "%s",szCommand[m_cmbDeviceTypeS.GetCurSel() ]);
        MessageBox(szLan); 
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "%s",szCommand[m_cmbDeviceTypeS.GetCurSel() ]); 
        return ; 
    }
    else
    {
		g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "%s",szCommand[m_cmbDeviceTypeS.GetCurSel() ]); 
        m_dwTemplatePlanNo = lpStatusPlan->dwTemplateNo; 
        UpdateData(FALSE); 
    }
}

void CDlgWeekPlan::OnButAcspSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
    DWORD dwCommand; 
	char *szCommand[] = {"NET_DVR_SET_DOOR_STATUS_PLAN", "NET_DVR_SET_CARD_READER_PLAN"}; 
	char szLan[128] = {0};
    NET_DVR_DOOR_STATUS_PLAN struStatusPlan = {0}; 
    struStatusPlan.dwSize = sizeof(struStatusPlan); 
    struStatusPlan.dwTemplateNo = m_dwTemplatePlanNo; 
    LPNET_DVR_DOOR_STATUS_PLAN lpStatusPlan = &struStatusPlan;
    switch(m_cmbDeviceTypeS.GetCurSel())
    {
    case 0:
        dwCommand = NET_DVR_SET_DOOR_STATUS_PLAN ;
        break; 
    case 1:
        dwCommand = NET_DVR_SET_CARD_READER_PLAN;    
        break;     
    default:
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "unknow command"); 
        return; 
    }  
    if (!NET_DVR_SetDVRConfig(m_lUserID, dwCommand, m_dwDoorNo, lpStatusPlan, sizeof(*lpStatusPlan)))
    {
        sprintf(szLan, "%s",szCommand[m_cmbDeviceTypeS.GetCurSel() ]);
        MessageBox(szLan); 
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "%s",szCommand[m_cmbDeviceTypeS.GetCurSel() ]);
		return ; 
    }
    else
    {
        g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "%s",szCommand[m_cmbDeviceTypeS.GetCurSel() ]);
	}	
}

void CDlgWeekPlan::OnSelchangeAcspDevicetype() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

    char szLan[128];

    if (m_cmbDeviceTypeS.GetCurSel() == 0 )
    {
        g_StringLanType(szLan, "ÃÅ±àºÅ", "door number");
        m_csDoorOrCardNo.Format(szLan);
    }
    else if( m_cmbDeviceTypeS.GetCurSel() == 1)
    {
        g_StringLanType(szLan, "¶Á¿¨Æ÷±àºÅ", "reader number");
        m_csDoorOrCardNo.Format(szLan);
    }
    UpdateData(FALSE); 
}

void CDlgWeekPlan::OnSelchangeDay() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    BYTE byDay = m_cmbDay.GetCurSel(); 
    BYTE byTimeSegment = m_cmbTimeSegment.GetCurSel(); 
   // UpdateTimeSegment(byDay, byTimeSegment); 
}


BOOL CDlgWeekPlan::CheckDate(const NET_DVR_SIMPLE_DAYTIME& struItem)
{
    if (struItem.byHour >23 ||  struItem.byMinute > 59 || struItem.bySecond > 59 )
    {
        return FALSE; 
    }
    return TRUE; 
}   

BOOL CDlgWeekPlan::CheckDate(const NET_DVR_DATE& struItem)
{
    if (struItem.wYear < 1970 ||  struItem.byMonth > 12 || struItem.byDay > 31 )
    {
        return FALSE; 
    }
    return TRUE;     
}

void CDlgWeekPlan::OnClickLstHolidayplan(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    POSITION  iPos = m_lstHolidayPlan.GetFirstSelectedItemPosition();
    if (iPos == NULL)
    {
        return;
    }
    m_iCurGroupNo  = m_lstHolidayPlan.GetNextSelectedItem(iPos);
	DWORD dwIndex = m_lstHolidayPlan.GetItemData(m_iCurGroupNo); 

    m_dwGroupNo = m_struGroupCfg.dwHolidayPlanNo[dwIndex]; 
    UpdateData(FALSE); 
	*pResult = 0;
}

void CDlgWeekPlan::UpdateLstGroupNo()
{
    UpdateData(TRUE); 
    m_lstHolidayPlan.DeleteAllItems(); 
    int iItemNum = sizeof(m_struGroupCfg.dwHolidayPlanNo) / sizeof(m_struGroupCfg.dwHolidayPlanNo[0]); 
    CString csTmp ; 
    int iIndex; 
    for (int i=0; i<iItemNum; i++)
    {
        csTmp.Format("%d",i+1); 
        iIndex = m_lstHolidayPlan.InsertItem(i, csTmp); 
        m_lstHolidayPlan.SetItemData(i, i); 
        csTmp.Format("%d", m_struGroupCfg.dwHolidayPlanNo[i]);
        m_lstHolidayPlan.SetItemText(iIndex, 1, csTmp);
    }
    m_lstHolidayPlan.SetItemState(m_iCurGroupNo, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
    UpdateData(FALSE); 
}

void CDlgWeekPlan::OnChangeEdtAchgGroupno() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here

}

void CDlgWeekPlan::OnKillfocusEdtAchgGroupno() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if ( m_iCurGroupNo == -1)
    {
        return; 
    }
    m_struGroupCfg.dwHolidayPlanNo[m_iCurGroupNo] = m_dwGroupNo;
    UpdateLstGroupNo(); 
}

void CDlgWeekPlan::OnClickLstAcwpTemplate(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    POSITION  iPos = m_lstTemplate.GetFirstSelectedItemPosition();
    if (iPos == NULL)
    {
        return;
    }
    m_iCurGroupNoP  = m_lstTemplate.GetNextSelectedItem(iPos);
    DWORD dwIndex = m_lstTemplate.GetItemData(m_iCurGroupNoP); 

    m_dwGroupNoP = m_struTemplateCfg.dwHolidayGroupNo[dwIndex]; 
    UpdateData(FALSE); 
	*pResult = 0;
}

void CDlgWeekPlan::OnKillfocusEdtAcptGroupno() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if ( m_iCurGroupNoP == -1)
    {
        return; 
    }
    m_struTemplateCfg.dwHolidayGroupNo[m_iCurGroupNoP] = m_dwGroupNoP;
    UpdateLstGroupNoP();
}

void CDlgWeekPlan::UpdateLstGroupNoP()
{
    UpdateData(TRUE); 
    m_lstTemplate.DeleteAllItems(); 
    int iItemNum = sizeof(m_struTemplateCfg.dwHolidayGroupNo) / sizeof(m_struTemplateCfg.dwHolidayGroupNo[0]); 
    CString csTmp ; 
    int iIndex; 
    for (int i=0; i<iItemNum; i++)
    {
        csTmp.Format("%d",i+1); 
        iIndex = m_lstTemplate.InsertItem(i, csTmp); 
        m_lstTemplate.SetItemData(i, i); 
        csTmp.Format("%d", m_struTemplateCfg.dwHolidayGroupNo[i]);
        m_lstTemplate.SetItemText(iIndex, 1, csTmp);
    }
    m_lstTemplate.SetItemState(m_iCurGroupNoP, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
    UpdateData(FALSE); 
}

#include "TimeSegment.h"
void CDlgWeekPlan::OnButAcwpTimesegementSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
    int iDate = m_cmbDay.GetCurSel(); 
    CTimeSegment dlg; 
    dlg.SetTimeSegment( (NET_DVR_SINGLE_PLAN_SEGMENT *)m_struPlanCfg.struPlanCfg[iDate] );
    if ( dlg.DoModal() == IDOK)
    {
        NET_DVR_SINGLE_PLAN_SEGMENT *lpPlanSegment = &m_struPlanCfg.struPlanCfg[iDate][0];
        dlg.GetTimeSegment(lpPlanSegment);
    }
    UpdateData(FALSE); 
}

void CDlgWeekPlan::OnButAcwpTimesegementH() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    CTimeSegment dlg; 
    dlg.SetTimeSegment( (NET_DVR_SINGLE_PLAN_SEGMENT *)m_struPlanCfgH.struPlanCfg );
    if ( dlg.DoModal() == IDOK)
    {
        NET_DVR_SINGLE_PLAN_SEGMENT *lpPlanSegment = &m_struPlanCfgH.struPlanCfg[0];
        dlg.GetTimeSegment(lpPlanSegment);
    }
    UpdateData(FALSE); 
}
