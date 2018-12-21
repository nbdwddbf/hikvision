// DlgClearAcsParam.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgClearAcsParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgClearAcsParam dialog


CDlgClearAcsParam::CDlgClearAcsParam(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgClearAcsParam::IDD, pParent)
    , m_iLocalControllerID(0)
    , m_bBlackListPic(FALSE)
    , m_bBlackList(FALSE)
    , m_bFailedFace(FALSE)
{
	//{{AFX_DATA_INIT(CDlgClearAcsParam)
	m_bCard = FALSE;
	m_bCardRightHolidayGroup = FALSE;
	m_bCardRightHoliDayPlan = FALSE;
	m_bCardRightPlanTemplate = FALSE;
	m_bCardRightWeekPlan = FALSE;
	m_bDoorStatusHolidayGroup = FALSE;
	m_bDoorStatusHolidayPlan = FALSE;
	m_bDoorStatusPlanTemplate = FALSE;
	m_bDoorStatusWeekPlan = FALSE;
	m_bGroup = FALSE;
	m_bVerifyHolidayGroup = FALSE;
	m_bVerifyHolidayPaln = FALSE;
	m_bVerifyPlanTemplate = FALSE;
	m_bVerifyWeekPaln = FALSE;
    m_bAntiSneakCfg = FALSE;
    m_bDoorEventCardLinkge = FALSE;
	m_bDoorCardPasswdCfg = FALSE;
	m_bPersonStatistical = FALSE;
    m_bExamInfo = FALSE;
    m_bExamineeInfo = FALSE;
    m_bBlackListPic = FALSE;
    m_bBlackList = FALSE;
	//}}AFX_DATA_INIT

	 m_lUserID = -1;
	 m_lChannel = -1;
	 m_iDevIndex = -1;
}


void CDlgClearAcsParam::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgClearAcsParam)
    DDX_Check(pDX, IDC_CHECK_CARD, m_bCard);
    DDX_Check(pDX, IDC_CHECK_CARD_RIGHT_HOLIDAY_GROUP, m_bCardRightHolidayGroup);
    DDX_Check(pDX, IDC_CHECK_CARD_RIGHT_HOLIDAY_PLAN, m_bCardRightHoliDayPlan);
    DDX_Check(pDX, IDC_CHECK_CARD_RIGHT_PALN_TEMPLATE, m_bCardRightPlanTemplate);
    DDX_Check(pDX, IDC_CHECK_CARD_RIGHT_WEEK_PLAN, m_bCardRightWeekPlan);
    DDX_Check(pDX, IDC_CHECK_DOOR_STATUS_HOLIDAY_GROUP, m_bDoorStatusHolidayGroup);
    DDX_Check(pDX, IDC_CHECK_DOOR_STATUS_HOLIDAY_PLAN, m_bDoorStatusHolidayPlan);
    DDX_Check(pDX, IDC_CHECK_DOOR_STATUS_PLAN_TEMPLATE, m_bDoorStatusPlanTemplate);
    DDX_Check(pDX, IDC_CHECK_DOOR_STATUS_WEEK_PLAN, m_bDoorStatusWeekPlan);
    DDX_Check(pDX, IDC_CHECK_GROUP, m_bGroup);
    DDX_Check(pDX, IDC_CHECK_VERIFY_HOLIDAY_GROUP, m_bVerifyHolidayGroup);
    DDX_Check(pDX, IDC_CHECK_VERIFY_HOLIDAY_PALN, m_bVerifyHolidayPaln);
    DDX_Check(pDX, IDC_CHECK_VERIFY_PALN_TEMPLATE, m_bVerifyPlanTemplate);
    DDX_Check(pDX, IDC_CHECK_VERIFY_WEEK_PALN, m_bVerifyWeekPaln);
    DDX_Check(pDX, IDC_CHECK_SNEAK_CFG, m_bAntiSneakCfg);
    DDX_Check(pDX, IDC_CHECK_EVENT_CARD_LINKAGE, m_bDoorEventCardLinkge);
    DDX_Check(pDX, IDC_CHECK_CARD_PASSWD_CFG, m_bDoorCardPasswdCfg);
    DDX_Check(pDX, IDC_CHECK_PERSON_STATISTICAL, m_bPersonStatistical);
    DDX_Check(pDX, IDC_CHECK_EXAM_INFO, m_bExamInfo);
    DDX_Check(pDX, IDC_CHECK_EXAMINEE_INFO, m_bExamineeInfo);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_ACS_LOCALCONTROLLER_ID, m_iLocalControllerID);
    DDX_Check(pDX, IDC_CHECK_BLACK_LIST_PIC, m_bBlackListPic);
    DDX_Check(pDX, IDC_CHECK_BLACK_LIST, m_bBlackList);
    DDX_Check(pDX, IDC_CHECK_BLACK_FAILED_FACE, m_bFailedFace);
}


BEGIN_MESSAGE_MAP(CDlgClearAcsParam, CDialog)
	//{{AFX_MSG_MAP(CDlgClearAcsParam)
	ON_BN_CLICKED(IDC_BTN_CLEAR_ACS_PARAM, OnBtnClearAcsParam)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgClearAcsParam message handlers

BOOL CDlgClearAcsParam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgClearAcsParam::OnBtnClearAcsParam() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	NET_DVR_ACS_PARAM_TYPE struAcsParam = {0};
	struAcsParam.dwSize = sizeof(struAcsParam);

	struAcsParam.dwParamType |= (m_bDoorStatusWeekPlan << 0);
	struAcsParam.dwParamType |= (m_bVerifyWeekPaln << 1);
	struAcsParam.dwParamType |= (m_bCardRightWeekPlan << 2);
	struAcsParam.dwParamType |= (m_bDoorStatusHolidayPlan << 3);
	struAcsParam.dwParamType |= (m_bVerifyHolidayPaln << 4);
	struAcsParam.dwParamType |= (m_bCardRightHoliDayPlan << 5);
	struAcsParam.dwParamType |= (m_bDoorStatusHolidayGroup << 6);
	struAcsParam.dwParamType |= (m_bVerifyHolidayGroup << 7);
	struAcsParam.dwParamType |= (m_bCardRightHolidayGroup << 8);
	struAcsParam.dwParamType |= (m_bDoorStatusPlanTemplate << 9);
	struAcsParam.dwParamType |= (m_bVerifyPlanTemplate << 10);
	struAcsParam.dwParamType |= (m_bCardRightPlanTemplate << 11);
	struAcsParam.dwParamType |= (m_bCard << 12);
	struAcsParam.dwParamType |= (m_bGroup << 13);
    struAcsParam.dwParamType |= (m_bAntiSneakCfg << 14);
    struAcsParam.dwParamType |= (m_bDoorEventCardLinkge << 15);
    struAcsParam.dwParamType |= (m_bDoorCardPasswdCfg << 16);
	struAcsParam.dwParamType |= (m_bPersonStatistical << 17);
    struAcsParam.dwParamType |= (m_bBlackListPic << 18);
    struAcsParam.dwParamType |= (m_bBlackList << 19);
    struAcsParam.dwParamType |= (m_bExamInfo << 20);
    struAcsParam.dwParamType |= (m_bExamineeInfo << 21);
    struAcsParam.dwParamType |= (m_bFailedFace << 22);

    struAcsParam.wLocalControllerID = m_iLocalControllerID;

	if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_CLEAR_ACS_PARAM, &struAcsParam, sizeof(struAcsParam)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_CLEAR_ACS_PARAM FAIL");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_CLEAR_ACS_PARAM SUCC");
	}
}
