// DlgAttendanceRecordInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgAttendanceRecordInfo.h"
#include "afxdialogex.h"


// CDlgAttendanceRecordInfo 对话框

IMPLEMENT_DYNAMIC(CDlgAttendanceRecordInfo, CDialog)

CDlgAttendanceRecordInfo::CDlgAttendanceRecordInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAttendanceRecordInfo::IDD, pParent)
{
    memset(&m_struSearchInfoCond, 0, sizeof(m_struSearchInfoCond));
    memset(&m_struAttendanceRecordCfg, 0, sizeof(m_struAttendanceRecordCfg));
    m_iEmployeeNo = 0;
    m_csName = _T("");
    m_startDate = COleDateTime::GetCurrentTime();
    m_startTime = COleDateTime::GetCurrentTime();
    m_stopDate = COleDateTime::GetCurrentTime();
    m_stopTime = COleDateTime::GetCurrentTime();
    m_lHandle = -1;
    m_bGetNext = FALSE;
    m_hGetInfoThread = NULL;
}

CDlgAttendanceRecordInfo::~CDlgAttendanceRecordInfo()
{
    char szLan[128] = { 0 };

    if (m_lHandle >= 0)
    {
        if (!NET_DVR_StopRemoteConfig(m_lHandle))
        {
            g_StringLanType(szLan, "考勤记录信息查询停止失败", "get attendance record info stop failed");
            AfxMessageBox(szLan);
            return;
        }
    }
}

void CDlgAttendanceRecordInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_COMMAND, m_cmbCommand);
    DDX_Text(pDX, IDC_EDIT_EMPLOYEENO, m_iEmployeeNo);
    DDX_Text(pDX, IDC_EDIT_NAME, m_csName);
    DDX_Control(pDX, IDC_LIST_ATTENDANCE_RECORD_INFO, m_lstAttendanceRecordInfo);
    DDX_DateTimeCtrl(pDX, IDC_START_DATE, m_startDate);
    DDX_DateTimeCtrl(pDX, IDC_START_TIME, m_startTime);
    DDX_DateTimeCtrl(pDX, IDC_STOP_DATE, m_stopDate);
    DDX_DateTimeCtrl(pDX, IDC_STOP_TIME, m_stopTime);
}

BOOL CDlgAttendanceRecordInfo::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_cmbCommand.SetCurSel(0);
    char szLanTemp[128] = { 0 };
    m_lstAttendanceRecordInfo.SetExtendedStyle(m_lstAttendanceRecordInfo.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES);
    g_StringLanType(szLanTemp, "工号", "Employee No");
    m_lstAttendanceRecordInfo.InsertColumn(0, szLanTemp, LVCFMT_LEFT, 40, -1);
    g_StringLanType(szLanTemp, "姓名", "Name");
    m_lstAttendanceRecordInfo.InsertColumn(1, szLanTemp, LVCFMT_LEFT, 40, -1);
    g_StringLanType(szLanTemp, "部门名称", "Department Name");
    m_lstAttendanceRecordInfo.InsertColumn(2, szLanTemp, LVCFMT_LEFT, 80, -1);
    g_StringLanType(szLanTemp, "考勤时间", "Attendance Time");
    m_lstAttendanceRecordInfo.InsertColumn(3, szLanTemp, LVCFMT_LEFT, 100, -1);

    return TRUE;
}

DWORD WINAPI CDlgAttendanceRecordInfo::GetAttendanceRecordThread(LPVOID lpAttendanceRecord)
{
    CDlgAttendanceRecordInfo* pThis = reinterpret_cast<CDlgAttendanceRecordInfo*>(lpAttendanceRecord);
    int iRet = 0;
    char szLan[128] = { 0 };
    char szInfoBuf[128] = { 0 };
    while (pThis->m_bGetNext)
    {
        iRet = NET_DVR_GetNextRemoteConfig(pThis->m_lHandle, &pThis->m_struAttendanceRecordCfg, sizeof(NET_DVR_ATTENDANCE_RECORD_CFG));
        if (iRet == NET_SDK_GET_NEXT_STATUS_SUCCESS)
        {
            //成功处理函数
            pThis->AddAttendanceRecordCfg(&pThis->m_struAttendanceRecordCfg);
        }
        else
        {
            if (iRet == NET_SDK_GET_NETX_STATUS_NEED_WAIT)
            {
                g_pMainDlg->AddLog(0, OPERATION_SUCC_T, "正在查询!");
                Sleep(200);
                continue;
            }
            else if (iRet == NET_SDK_GET_NEXT_STATUS_FINISH)
            {
                g_StringLanType(szLan, "考勤记录信息查询结束!", "get attendance record info finish");
                sprintf(szInfoBuf, "%s[Info Count:%d]", szLan, pThis->m_lstAttendanceRecordInfo.GetItemCount());
                AfxMessageBox(szInfoBuf);
                break;
            }
            else if (iRet == NET_SDK_GET_NEXT_STATUS_FAILED)
            {
                g_StringLanType(szLan, "长连接考勤记录信息查询失败", "get attendance record info failed");
                AfxMessageBox(szLan);
                break;
            }
            else
            {
                g_StringLanType(szLan, "未知状态", "unknown status");
                AfxMessageBox(szLan);
                break;
            }
        }
    }

    return 0;
}

void CDlgAttendanceRecordInfo::AddAttendanceRecordCfg(LPNET_DVR_ATTENDANCE_RECORD_CFG lpInter)
{
    int iItemCount = m_lstAttendanceRecordInfo.GetItemCount();
    m_lstAttendanceRecordInfo.InsertItem(iItemCount, "");

    char szStr[128] = { 0 };
    int count = 0;
    //工号
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%d", lpInter->dwEmployeeNo);
    m_lstAttendanceRecordInfo.SetItemText(iItemCount, count, szStr);
    count += 1;
    //姓名
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%s", lpInter->byName);
    m_lstAttendanceRecordInfo.SetItemText(iItemCount, count, szStr);
    count += 1;
    //部门名称
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%s", lpInter->byDepartmentName);
    m_lstAttendanceRecordInfo.SetItemText(iItemCount, count, szStr);
    count += 1;
    //考勤时间
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%d-%d-%d %d:%d:%d", lpInter->struAttendanceTime.wYear, lpInter->struAttendanceTime.byMonth, \
        lpInter->struAttendanceTime.byDay, lpInter->struAttendanceTime.byHour, lpInter->struAttendanceTime.byMinute, \
        lpInter->struAttendanceTime.bySecond);
    m_lstAttendanceRecordInfo.SetItemText(iItemCount, count, szStr);
    count += 1;
}

BEGIN_MESSAGE_MAP(CDlgAttendanceRecordInfo, CDialog)
    ON_BN_CLICKED(IDC_BTN_CLEAN_ATTENDANCE_RECORD_INFO, &CDlgAttendanceRecordInfo::OnBnClickedBtnCleanAttendanceRecordInfo)
    ON_BN_CLICKED(IDC_BTN_GET_ATTENDANCE_RECORD_INFO, &CDlgAttendanceRecordInfo::OnBnClickedBtnGetAttendanceRecordInfo)
    ON_CBN_SELCHANGE(IDC_COMBO_COMMAND, &CDlgAttendanceRecordInfo::OnCbnSelchangeComboCommand)
END_MESSAGE_MAP()


// CDlgAttendanceRecordInfo 消息处理程序

void CDlgAttendanceRecordInfo::OnBnClickedBtnGetAttendanceRecordInfo()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    char szLan[128] = { 0 };
    memset(&m_struSearchInfoCond, 0, sizeof(m_struSearchInfoCond));
    memset(&m_struAttendanceRecordCfg, 0, sizeof(m_struAttendanceRecordCfg));
    m_struSearchInfoCond.byCommand = m_cmbCommand.GetCurSel();
    if (m_struSearchInfoCond.byCommand == 0)
    {
        m_struSearchInfoCond.dwEmployeeNo = m_iEmployeeNo;
        memcpy(m_struSearchInfoCond.byName, (LPCSTR)m_csName, m_csName.GetAllocLength());
    }
    m_struSearchInfoCond.struStartTime.wYear = m_startDate.GetYear();
    m_struSearchInfoCond.struStartTime.byMonth = m_startDate.GetMonth();
    m_struSearchInfoCond.struStartTime.byDay = m_startDate.GetDay();
    m_struSearchInfoCond.struStartTime.byHour = m_startTime.GetHour();
    m_struSearchInfoCond.struStartTime.byMinute = m_startTime.GetMinute();
    m_struSearchInfoCond.struStartTime.bySecond = m_startTime.GetSecond();
    m_struSearchInfoCond.struEndTime.wYear = m_stopDate.GetYear();
    m_struSearchInfoCond.struEndTime.byMonth = m_stopDate.GetMonth();
    m_struSearchInfoCond.struEndTime.byDay = m_stopDate.GetDay();
    m_struSearchInfoCond.struEndTime.byHour = m_stopTime.GetHour();
    m_struSearchInfoCond.struEndTime.byMinute = m_stopTime.GetMinute();
    m_struSearchInfoCond.struEndTime.bySecond = m_stopTime.GetSecond();

    if (m_lHandle >= 0)
    {
        if (!NET_DVR_StopRemoteConfig(m_lHandle))
        {
            g_StringLanType(szLan, "考勤记录信息查询停止失败", "get attendance record info stop failed");
            AfxMessageBox(szLan);
            return;
        }
    }

    m_lHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_GET_ATTENDANCE_RECORD_INFO, &m_struSearchInfoCond, sizeof(m_struSearchInfoCond), NULL, NULL);
    if (m_lHandle >= 0)
    {
        m_bGetNext = TRUE;
        DWORD dwThreadId;
        m_lstAttendanceRecordInfo.DeleteAllItems();
        m_hGetInfoThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetAttendanceRecordThread), this, 0, &dwThreadId);
        g_StringLanType(szLan, "考勤记录信息查询成功", "get attendance record info succeed");
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, szLan);
    }
    else
    {
        m_bGetNext = FALSE;
        g_StringLanType(szLan, "考勤记录信息查询失败", "get attendance record info failed");
        AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ATTENDANCE_RECORD_INFO");
        return;
    }

    UpdateData(FALSE);
}

void CDlgAttendanceRecordInfo::OnBnClickedBtnCleanAttendanceRecordInfo()
{
    // TODO:  在此添加控件通知处理程序代码
    m_lstAttendanceRecordInfo.DeleteAllItems();
}


void CDlgAttendanceRecordInfo::OnCbnSelchangeComboCommand()
{
    // TODO:  在此添加控件通知处理程序代码
    if (0 == m_cmbCommand.GetCurSel())
    {
        GetDlgItem(IDC_STATIC_EMPLOYEENO)->ShowWindow(true);
        GetDlgItem(IDC_STATIC_NAME)->ShowWindow(true);
        GetDlgItem(IDC_EDIT_EMPLOYEENO)->ShowWindow(true);
        GetDlgItem(IDC_EDIT_NAME)->ShowWindow(true);
    }
    else
    {
        GetDlgItem(IDC_STATIC_EMPLOYEENO)->ShowWindow(false);
        GetDlgItem(IDC_STATIC_NAME)->ShowWindow(false);
        GetDlgItem(IDC_EDIT_EMPLOYEENO)->ShowWindow(false);
        GetDlgItem(IDC_EDIT_NAME)->ShowWindow(false);
    }
}
