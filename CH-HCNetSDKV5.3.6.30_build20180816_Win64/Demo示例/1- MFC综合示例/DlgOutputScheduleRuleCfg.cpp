// OutputScheduleRuleCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgOutputScheduleRuleCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputScheduleRuleCfg dialog


CDlgOutputScheduleRuleCfg::CDlgOutputScheduleRuleCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOutputScheduleRuleCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COutputScheduleRuleCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_lUserID      = -1;
	m_iDeviceIndex = -1;
	memset(&m_struOutputRuleCfg,0,sizeof(m_struOutputRuleCfg));
	m_nCurRuleIndex = 0;
	m_bEnableRule   = FALSE;
	m_nBeginDate_month = 0;
	m_nBeginDate_day   = 0;
	m_nEndDate_month   = 0;
	m_nEndDate_day     = 0;
}


void CDlgOutputScheduleRuleCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COutputScheduleRuleCfg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_COMBO_RULENO,m_comboRuleNo);
	
	DDX_Text(pDX,IDC_EDIT_BEGINDATE_MONTH,m_nBeginDate_month);
	DDX_Text(pDX,IDC_EDIT_BEGINDATE_DAY,  m_nBeginDate_day);
	DDX_Text(pDX,IDC_EDIT_ENDDATE_MONTH,m_nEndDate_month);
	DDX_Text(pDX,IDC_EDIT_ENDDATE_DAY,m_nEndDate_day);
//	DDV_MinMaxInt(pDX,IDC_EDIT_BEGINDATE_MONTH,1,12);
//	DDV_MinMaxInt(pDX,IDC_EDIT_BEGINDATE_DAY,1,31);
//	DDV_MinMaxInt(pDX,IDC_EDIT_ENDDATE_MONTH,1,12);
//	DDV_MinMaxInt(pDX,IDC_EDIT_ENDDATE_DAY,1,31);

	DDX_Control(pDX,IDC_DATETIMEPICKER_OUTPUT_1_BEGINTIME,m_dtCtrlArryBeginTime[0]);
    DDX_Control(pDX,IDC_DATETIMEPICKER_OUTPUT_2_BEGINTIME,m_dtCtrlArryBeginTime[1]);
	DDX_Control(pDX,IDC_DATETIMEPICKER_OUTPUT_3_BEGINTIME,m_dtCtrlArryBeginTime[2]);
	DDX_Control(pDX,IDC_DATETIMEPICKER_OUTPUT_4_BEGINTIME,m_dtCtrlArryBeginTime[3]);
	DDX_Control(pDX,IDC_DATETIMEPICKER_OUTPUT_5_BEGINTIME,m_dtCtrlArryBeginTime[4]);
	DDX_Control(pDX,IDC_DATETIMEPICKER_OUTPUT_6_BEGINTIME,m_dtCtrlArryBeginTime[5]);
	DDX_Control(pDX,IDC_DATETIMEPICKER_OUTPUT_7_BEGINTIME,m_dtCtrlArryBeginTime[6]);
	DDX_Control(pDX,IDC_DATETIMEPICKER_OUTPUT_8_BEGINTIME,m_dtCtrlArryBeginTime[7]);

	DDX_Control(pDX,IDC_DATETIMEPICKER_OUTPUT_1_ENDTIME,m_dtCtrlArryEndTime[0]);
	DDX_Control(pDX,IDC_DATETIMEPICKER_OUTPUT_2_ENDTIME,m_dtCtrlArryEndTime[1]);
	DDX_Control(pDX,IDC_DATETIMEPICKER_OUTPUT_3_ENDTIME,m_dtCtrlArryEndTime[2]);
	DDX_Control(pDX,IDC_DATETIMEPICKER_OUTPUT_4_ENDTIME,m_dtCtrlArryEndTime[3]);
	DDX_Control(pDX,IDC_DATETIMEPICKER_OUTPUT_5_ENDTIME,m_dtCtrlArryEndTime[4]);
	DDX_Control(pDX,IDC_DATETIMEPICKER_OUTPUT_6_ENDTIME,m_dtCtrlArryEndTime[5]);
	DDX_Control(pDX,IDC_DATETIMEPICKER_OUTPUT_7_ENDTIME,m_dtCtrlArryEndTime[6]);
	DDX_Control(pDX,IDC_DATETIMEPICKER_OUTPUT_8_ENDTIME,m_dtCtrlArryEndTime[7]);


	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER_OUTPUT_1_BEGINTIME,m_dtArryOutputBeginTime[0]);
    DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER_OUTPUT_2_BEGINTIME,m_dtArryOutputBeginTime[1]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER_OUTPUT_3_BEGINTIME,m_dtArryOutputBeginTime[2]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER_OUTPUT_4_BEGINTIME,m_dtArryOutputBeginTime[3]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER_OUTPUT_5_BEGINTIME,m_dtArryOutputBeginTime[4]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER_OUTPUT_6_BEGINTIME,m_dtArryOutputBeginTime[5]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER_OUTPUT_7_BEGINTIME,m_dtArryOutputBeginTime[6]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER_OUTPUT_8_BEGINTIME,m_dtArryOutputBeginTime[7]);

	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER_OUTPUT_1_ENDTIME,m_dtArryOutputEndTime[0]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER_OUTPUT_2_ENDTIME,m_dtArryOutputEndTime[1]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER_OUTPUT_3_ENDTIME,m_dtArryOutputEndTime[2]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER_OUTPUT_4_ENDTIME,m_dtArryOutputEndTime[3]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER_OUTPUT_5_ENDTIME,m_dtArryOutputEndTime[4]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER_OUTPUT_6_ENDTIME,m_dtArryOutputEndTime[5]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER_OUTPUT_7_ENDTIME,m_dtArryOutputEndTime[6]);
	DDX_DateTimeCtrl(pDX,IDC_DATETIMEPICKER_OUTPUT_8_ENDTIME,m_dtArryOutputEndTime[7]);

	DDX_Check(pDX,IDC_CHECK_OUTPUT_1_ENABLE,m_bArryOutputEnable[0]);
	DDX_Check(pDX,IDC_CHECK_OUTPUT_2_ENABLE,m_bArryOutputEnable[1]);
	DDX_Check(pDX,IDC_CHECK_OUTPUT_3_ENABLE,m_bArryOutputEnable[2]);
	DDX_Check(pDX,IDC_CHECK_OUTPUT_4_ENABLE,m_bArryOutputEnable[3]);
	DDX_Check(pDX,IDC_CHECK_OUTPUT_5_ENABLE,m_bArryOutputEnable[4]);
	DDX_Check(pDX,IDC_CHECK_OUTPUT_6_ENABLE,m_bArryOutputEnable[5]);
	DDX_Check(pDX,IDC_CHECK_OUTPUT_7_ENABLE,m_bArryOutputEnable[6]);
	DDX_Check(pDX,IDC_CHECK_OUTPUT_8_ENABLE,m_bArryOutputEnable[7]);

	DDX_Check(pDX,IDC_CHECK_ENABLE_RULE,m_bEnableRule);
	DDX_Control(pDX, IDC_LIST_TRIGGER, m_listTrigger);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOutputScheduleRuleCfg, CDialog)
	//{{AFX_MSG_MAP(COutputScheduleRuleCfg)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_CBN_SELCHANGE(IDC_COMBO_RULENO, OnSelchangeComboRuleno)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputScheduleRuleCfg message handlers

BOOL CDlgOutputScheduleRuleCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitCtrlState();
    GetOutputScheduleRuleCfg();

	CString csStr;
	m_listTrigger.SetExtendedStyle(LVS_EX_CHECKBOXES);
	for (int i=0; i<512; i++)
	{
		csStr.Format("trigger%d", i+1);
		m_listTrigger.InsertItem(i, csStr);
	}

	m_nCurRuleIndex = 0;
	LoadWndRuleContent(m_nCurRuleIndex);
	return TRUE;
}
void CDlgOutputScheduleRuleCfg::InitCtrlState()
{   
	//m_dtBeginDate.SetDate(COleDateTime::GetCurrentTime().GetYear(),1,1);
//	m_dtEndDate.SetDate(COleDateTime::GetCurrentTime().GetYear(),12,31);
//	m_dtCtrlBeginDate.SetFormat(_T("MM-dd"));
//	m_dtCtrlEndDate.SetFormat(_T("MM-dd"));

	CString strRuleNo = "";
	m_comboRuleNo.ResetContent();


//	m_dtBeginDate = COleDateTime::GetCurrentTime();
//	m_dtEndDate  = COleDateTime::GetCurrentTime();

	for (int i = 0; i < MAX_RULE_NUM; i++)
	{   
		strRuleNo.Format("%d", i +1);
		m_comboRuleNo.InsertString(i,strRuleNo);
	}

	for (int j = 0; j < MAX_TIMESEGMENT_V30; j++)
	{
		m_dtArryOutputBeginTime[j] = COleDateTime::GetCurrentTime();
		m_dtArryOutputEndTime[j] = COleDateTime::GetCurrentTime();
		
		m_dtCtrlArryBeginTime[j].SetFormat(_T("HH:mm"));
		m_dtCtrlArryEndTime[j].SetFormat(_T("HH:mm"));
		m_bArryOutputEnable[j] = FALSE;
		m_dtArryOutputBeginTime[j].SetTime(0,0,0);
		m_dtArryOutputEndTime[j].SetTime(0,0,0);
	}
    
	m_comboRuleNo.SetCurSel(m_nCurRuleIndex);
	UpdateData(FALSE);
}

void CDlgOutputScheduleRuleCfg::OnBtnSave() 
{   
	SaveWndRuleContent(m_nCurRuleIndex);
    
	char szError[32] = "\0";
	if (SetOutputScheduleRuleCfg())
	{   
		g_StringLanType(szError, "保存成功","Saved successfully");
	}
	else
	{
		g_StringLanType(szError, "保存失败","Save failed");
	}
	AfxMessageBox(szError);
}

void CDlgOutputScheduleRuleCfg::OnSelchangeComboRuleno() 
{
	int nSelRuleIndex = m_comboRuleNo.GetCurSel();
	if (nSelRuleIndex != CB_ERR)
	{
		SaveWndRuleContent(m_nCurRuleIndex);
		
		m_nCurRuleIndex = nSelRuleIndex;
		
		LoadWndRuleContent(nSelRuleIndex);
	}
}


BOOL CDlgOutputScheduleRuleCfg::GetOutputScheduleRuleCfg()
{
	DWORD dwReturn = 0;
	BOOL bRet      = FALSE;
	m_struOutputRuleCfg.dwSize = sizeof(m_struOutputRuleCfg);
	
    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_OUTPUT_SCHEDULE_RULECFG_V40,1,&m_struOutputRuleCfg, sizeof(m_struOutputRuleCfg),
		&dwReturn))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_OUTPUT_SCHEDULE_RULECFG_V40 Chan[%d]", 1);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_OUTPUT_SCHEDULE_RULECFG_V40 Chan[%d]", 1);
        bRet = TRUE;
    }
	return bRet;
}

BOOL CDlgOutputScheduleRuleCfg::SetOutputScheduleRuleCfg()
{
	DWORD dwReturn = 0;
	BOOL bRet      = FALSE;
	m_struOutputRuleCfg.dwSize = sizeof(m_struOutputRuleCfg);
	
    if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_OUTPUT_SCHEDULE_RULECFG_V40,1,&m_struOutputRuleCfg, sizeof(m_struOutputRuleCfg)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_OUTPUT_SCHEDULE_RULECFG_V40 Chan[%d]", 1);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_OUTPUT_SCHEDULE_RULECFG_V40 Chan[%d]", 1);
        bRet = TRUE;
    }
	return bRet;
}

void CDlgOutputScheduleRuleCfg::LoadWndRuleContent(int nRuleIndex)
{   
	const NET_DVR_ONE_OUTPUT_SCHEDULE_RULE_V40& struOneRuleCfg = m_struOutputRuleCfg.struOutputRule[nRuleIndex];

	m_bEnableRule = struOneRuleCfg.byEnable;

	m_nBeginDate_month = struOneRuleCfg.struDate.byStartMonth;
	m_nBeginDate_day   = struOneRuleCfg.struDate.byStartDay;
	m_nEndDate_month   = struOneRuleCfg.struDate.byStopMonth;
	m_nEndDate_day     = struOneRuleCfg.struDate.byStopDay;

    int i = 0;

	for ( i = 0; i < MAX_TIMESEGMENT_V30; i++)
	{
		const NET_DVR_OUTPUT_SCHEDULE& struOutputSchedule = struOneRuleCfg.struOutputSchedule[i];
		m_bArryOutputEnable[i] = struOutputSchedule.byState;

		const NET_DVR_SCHEDTIME& struTime = struOutputSchedule.struTime;
		m_dtArryOutputBeginTime[i].SetTime(struTime.byStartHour,struTime.byStartMin,0);
		m_dtArryOutputEndTime[i].SetTime(struTime.byStopHour,struTime.byStopMin,0);	
	}

	for ( i = 0; i < 512; i++)
	{
		m_listTrigger.SetCheck(i, (BOOL)(struOneRuleCfg.byTriggerIndex[i]));
	}

	UpdateData(FALSE);
}

void CDlgOutputScheduleRuleCfg::SaveWndRuleContent(int nRuleIndex)
{
	UpdateData(TRUE);

	NET_DVR_ONE_OUTPUT_SCHEDULE_RULE_V40& struOneRuleCfg = m_struOutputRuleCfg.struOutputRule[nRuleIndex];

	struOneRuleCfg.byEnable = m_bEnableRule;

	struOneRuleCfg.struDate.byStartMonth = m_nBeginDate_month;
	struOneRuleCfg.struDate.byStartDay   = m_nBeginDate_day;
	struOneRuleCfg.struDate.byStopMonth  = m_nEndDate_month;
	struOneRuleCfg.struDate.byStopDay    = m_nEndDate_day;
	
    int i = 0;
	for (i = 0; i < MAX_TIMESEGMENT_V30; i++)
	{
		NET_DVR_OUTPUT_SCHEDULE& struOutputSchedule = struOneRuleCfg.struOutputSchedule[i];
		struOutputSchedule.byState = m_bArryOutputEnable[i];

		struOutputSchedule.struTime.byStartHour = m_dtArryOutputBeginTime[i].GetHour();
		struOutputSchedule.struTime.byStartMin  = m_dtArryOutputBeginTime[i].GetMinute();
		struOutputSchedule.struTime.byStopHour  = m_dtArryOutputEndTime[i].GetHour();
		struOutputSchedule.struTime.byStopMin   = m_dtArryOutputEndTime[i].GetMinute();
	}
	for (i = 0; i < 512; i++)
	{
		struOneRuleCfg.byTriggerIndex[i] = m_listTrigger.GetCheck(i);
	}
}
