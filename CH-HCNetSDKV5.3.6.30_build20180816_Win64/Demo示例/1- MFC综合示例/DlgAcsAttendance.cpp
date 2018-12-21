// DlgAcsAttendance.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgAcsAttendance.h"
#include "afxdialogex.h"


// CDlgAcsAttendance 对话框

IMPLEMENT_DYNAMIC(CDlgAcsAttendance, CDialog)

CDlgAcsAttendance::CDlgAcsAttendance(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAcsAttendance::IDD, pParent)
{

}

CDlgAcsAttendance::~CDlgAcsAttendance()
{
}

void CDlgAcsAttendance::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgAcsAttendance, CDialog)
    ON_BN_CLICKED(IDC_BTN_SCHEDULE_INFO, &CDlgAcsAttendance::OnBnClickedBtnScheduleInfo)
    ON_BN_CLICKED(IDC_BTN_ATTENDANCE_SUMMARY_INFO, &CDlgAcsAttendance::OnBnClickedBtnAttendanceSummaryInfo)
    ON_BN_CLICKED(IDC_BTN_ATTENDANCE_RECORD_INFO, &CDlgAcsAttendance::OnBnClickedBtnAttendanceRecordInfo)
    ON_BN_CLICKED(IDC_BTN_ATTENDANCE_RECORD_INFO, &CDlgAcsAttendance::OnBnClickedBtnAttendanceRecordInfo)
    ON_BN_CLICKED(IDC_BTN_ABNORMAL_INFO, &CDlgAcsAttendance::OnBnClickedBtnAbnormalInfo)
    ON_BN_CLICKED(IDC_BTN_DEPARTMENT_PARAM, &CDlgAcsAttendance::OnBnClickedBtnDepartmentParam)
    ON_BN_CLICKED(IDC_BTN_SCHEDULE_PLAN, &CDlgAcsAttendance::OnBnClickedBtnSchedulePlan)
    ON_BN_CLICKED(IDC_BTN_ATTENDANCE_RULE, &CDlgAcsAttendance::OnBnClickedBtnAttendanceRule)
    ON_BN_CLICKED(IDC_BTN_ORDINARY_CLASS, &CDlgAcsAttendance::OnBnClickedBtnOrdinaryClass)
    ON_BN_CLICKED(IDC_BTN_WORKING_CLASS, &CDlgAcsAttendance::OnBnClickedBtnWorkingClass)
    ON_BN_CLICKED(IDC_BTN_ATTENDANCE_HOLIDAY_GROUP, &CDlgAcsAttendance::OnBnClickedBtnAttendanceHolidayGroup)
    ON_BN_CLICKED(IDC_BTN_ATTENDANCE_HOLIDAY_PLAN, &CDlgAcsAttendance::OnBnClickedBtnAttendanceHolidayPlan)
END_MESSAGE_MAP()


// CDlgAcsAttendance 消息处理程序

#include "DlgScheduleInfo.h"
void CDlgAcsAttendance::OnBnClickedBtnScheduleInfo()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgScheduleInfo dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

#include "DlgAttendanceSummaryInfo.h"
void CDlgAcsAttendance::OnBnClickedBtnAttendanceSummaryInfo()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAttendanceSummaryInfo dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

#include "DlgAttendanceRecordInfo.h"
void CDlgAcsAttendance::OnBnClickedBtnAttendanceRecordInfo()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAttendanceRecordInfo dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

#include "DlgAbnormalInfo.h"
void CDlgAcsAttendance::OnBnClickedBtnAbnormalInfo()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAbnormalInfo dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

#include "DlgDepartmentParam.h"
void CDlgAcsAttendance::OnBnClickedBtnDepartmentParam()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgDepartmentParam dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

#include "DlgSchedulePlan.h"
void CDlgAcsAttendance::OnBnClickedBtnSchedulePlan()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgSchedulePlan dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

#include "DlgAttendanceRule.h"
void CDlgAcsAttendance::OnBnClickedBtnAttendanceRule()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAttendanceRule dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

#include "DlgOrdinaryClass.h"
void CDlgAcsAttendance::OnBnClickedBtnOrdinaryClass()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgOrdinaryClass dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

#include "DlgWorkingClass.h"
void CDlgAcsAttendance::OnBnClickedBtnWorkingClass()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgWorkingClass dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

#include "DlgAttendanceHolidayGroup.h"
void CDlgAcsAttendance::OnBnClickedBtnAttendanceHolidayGroup()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAttendanceHolidayGroup dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

#include "DlgAttendanceHolidayPlan.h"
void CDlgAcsAttendance::OnBnClickedBtnAttendanceHolidayPlan()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgAttendanceHolidayPlan dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}
