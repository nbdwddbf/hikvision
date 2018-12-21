// DlgCourseList.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgCourseList.h"

#include <string>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_AC_GET_COURSE_LIST_FINISH 10001
void CALLBACK g_fGetCourselList(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData);
/////////////////////////////////////////////////////////////////////////////
// DlgCourseList dialog

DlgCourseList::DlgCourseList(CWnd* pParent /*=NULL*/)
	: CDialog(DlgCourseList::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgCourseList)
	m_byCourseName = _T("");
	m_byInstructorName = _T("");
	m_startTime = COleDateTime::GetCurrentTime();
	m_endTime = COleDateTime::GetCurrentTime();
	m_endDate = COleDateTime::GetCurrentTime();
	m_startDate = 0;
	//}}AFX_DATA_INIT
}


void DlgCourseList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgCourseList)
	DDX_Control(pDX, IDC_COURSE_LIST, m_listCourse);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_byCourseType);
	DDX_Text(pDX, IDC_EDIT_COURSE_NAME, m_byCourseName);
	DDX_Text(pDX, IDC_EDIT_INSTRUCTOR, m_byInstructorName);
	DDX_DateTimeCtrl(pDX, IDC_TIME_START, m_startTime);
	DDX_DateTimeCtrl(pDX, IDC_TIME_END, m_endTime);
	DDX_DateTimeCtrl(pDX, IDC_DATE_END, m_endDate);
	DDX_DateTimeCtrl(pDX, IDC_DATE_START, m_startDate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgCourseList, CDialog)
	//{{AFX_MSG_MAP(DlgCourseList)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnBtnGetCourseList)
    ON_MESSAGE(WM_AC_GET_COURSE_LIST_FINISH, OnMsgGetCourseListFinish)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgCourseList message handlers

BOOL DlgCourseList::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    m_lCourseListHandle = -1;

    char szLan[128] = {0};
    m_listCourse.SetExtendedStyle(m_listCourse.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
    g_StringLanType(szLan, "课程名称", "course name");
    m_listCourse.InsertColumn(0, szLan, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLan, "授课老师", "Instructor");
    m_listCourse.InsertColumn(1, szLan, LVCFMT_LEFT, 100, -1);
    g_StringLanType(szLan, "课程简介", "Course Description");
    m_listCourse.InsertColumn(2, szLan, LVCFMT_LEFT, 100, -1);
    g_StringLanType(szLan, "UUID", "UUID");
    m_listCourse.InsertColumn(3, szLan, LVCFMT_LEFT, 100, -1);
    g_StringLanType(szLan, "课表类型", "Course Type");
    m_listCourse.InsertColumn(4, szLan, LVCFMT_LEFT, 60, -1);
    g_StringLanType(szLan, "开始时间", "Start Time");
    m_listCourse.InsertColumn(5, szLan, LVCFMT_LEFT, 100, -1);
    g_StringLanType(szLan, "结束时间", "End Time");
    m_listCourse.InsertColumn(6, szLan, LVCFMT_LEFT, 100, -1);

    m_byCourseType.ResetContent();
    int iIndex ; 
    g_StringLanType(szLan, "所有", "all");
    iIndex = m_byCourseType.AddString(szLan);
    m_byCourseType.SetItemData(iIndex, iIndex);

    g_StringLanType(szLan, "手动课表", "manual curriculum");
    iIndex = m_byCourseType.AddString(szLan);
    m_byCourseType.SetItemData(iIndex, iIndex);

    m_byCourseType.SetCurSel(0);

    return TRUE;
}

void CALLBACK g_fGetCourselList(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    DlgCourseList* pDlg = (DlgCourseList*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
    pDlg->ProcGetCourseList(dwType,lpBuffer,dwBufLen);
    
}

void DlgCourseList::ProcGetCourseList(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{
    CString strItem = "";
    if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        NET_DVR_COURSE_CFG* pConnectDevCfg = (NET_DVR_COURSE_CFG*)lpBuffer;
        AddCourseListItem(*pConnectDevCfg);
    }
    else if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
        DWORD dwStatus = *(DWORD*)lpBuffer;
        if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            PostMessage(WM_AC_GET_COURSE_LIST_FINISH,0,0);
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "ProcGetCourseList finish");
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "ProcGetCourseList failed");
        }
    }
}

void DlgCourseList::AddCourseListItem(const NET_DVR_COURSE_CFG &Item)
{
    BOOL bTemp = FALSE;
    
    int iItemCount = m_listCourse.GetItemCount();
    m_listCourse.InsertItem(iItemCount, "");
    
    char szStr[128] = {0};

    //0课程名称
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%s", Item.byCourseName);
    string strCourseName = UTF82ASCII(szStr);
    m_listCourse.SetItemText(iItemCount, 0, strCourseName.c_str());
    
    //1授课老师
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%s", Item.byInstructorName);
    //szStr[MACADDR_LEN] = 0;
    string strInstructorName= UTF82ASCII(szStr);
    m_listCourse.SetItemText(iItemCount, 1, strInstructorName.c_str());

    //2课程简介
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%s", Item.byCourseDescription);
    string strCourseDescription= UTF82ASCII(szStr);
    m_listCourse.SetItemText(iItemCount, 2, strCourseDescription.c_str());

    //3手动课表UUID
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%s", Item.byRecUUID);
    string strRecUUID= UTF82ASCII(szStr);
    m_listCourse.SetItemText(iItemCount, 3, strRecUUID.c_str());

    //4课表类型
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr, "%d", Item.byCourseType);
    m_listCourse.SetItemText(iItemCount, 4, szStr);
    
    //5开始时间
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr,"%04d-%02d-%02d-%02d-%02d-%02d",Item.struStartTime.wYear, \
        Item.struStartTime.byMonth, Item.struStartTime.byDay, Item.struStartTime.byHour,\
        Item.struStartTime.byMinute, Item.struStartTime.bySecond);
    m_listCourse.SetItemText(iItemCount, 5, szStr);

    //6结束时间
    memset(szStr, 0, sizeof(szStr));
    sprintf(szStr,"%04d-%02d-%02d-%02d-%02d-%02d",Item.struEndTime.wYear, \
        Item.struEndTime.byMonth, Item.struEndTime.byDay, Item.struEndTime.byHour,\
        Item.struEndTime.byMinute, Item.struEndTime.bySecond);
    m_listCourse.SetItemText(iItemCount, 6, szStr);

}

LRESULT DlgCourseList::OnMsgGetCourseListFinish(WPARAM wParam,LPARAM lParam)
{
    StopCourselList();
    return 0;
}

void DlgCourseList::OnBtnGetCourseList() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    if (m_lCourseListHandle>=0)
    {
        StopCourselList();
    }
    
    NET_DVR_COURSE_LIST_COND struCourseCond = {0};
    struCourseCond.dwSize = sizeof(struCourseCond);
    struCourseCond.byCourseType = m_byCourseType.GetItemData(m_byCourseType.GetCurSel());

    struCourseCond.struStartTime.wYear = m_startDate.GetYear();
    struCourseCond.struStartTime.byMonth = m_startDate.GetMonth();
    struCourseCond.struStartTime.byDay = m_startDate.GetDay();
    struCourseCond.struStartTime.byHour = m_startTime.GetHour();
    struCourseCond.struStartTime.byMinute = m_startTime.GetMinute();
    struCourseCond.struStartTime.bySecond = m_startTime.GetSecond();

    struCourseCond.struEndTime.wYear = m_endDate.GetYear();
    struCourseCond.struEndTime.byMonth = m_endDate.GetMonth();
    struCourseCond.struEndTime.byDay = m_endDate.GetDay();
    struCourseCond.struEndTime.byHour = m_endTime.GetHour();
    struCourseCond.struEndTime.byMinute = m_endTime.GetMinute();
    struCourseCond.struEndTime.bySecond = m_endTime.GetSecond();
    
    sprintf((char *)struCourseCond.byCourseName,"%s",ASCII2UTF8(m_byCourseName.GetBuffer(m_byCourseName.GetLength())).c_str());
    sprintf((char *)struCourseCond.byInstructorName,"%s",ASCII2UTF8(m_byInstructorName.GetBuffer(m_byInstructorName.GetLength())).c_str());


    m_lCourseListHandle = NET_DVR_StartRemoteConfig(m_lUserID,NET_DVR_GET_COURSE_LIST,&struCourseCond,sizeof(struCourseCond),g_fGetCourselList, this);
    if (m_lCourseListHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_CONNECT_LIST");
        return;
    }
    else
    {
        m_listCourse.DeleteAllItems();
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_CONNECT_LIST");
	}
}

void DlgCourseList::StopCourselList()
{
    char szLan[128] = {0};
    if (m_lCourseListHandle>=0)
    {
        if (!NET_DVR_StopRemoteConfig(m_lCourseListHandle))
        {
            g_StringLanType(szLan, "获取课程列表停止失败", "Dev List Stop Failed");
            AfxMessageBox(szLan);
            return;
        }
        m_lCourseListHandle = -1;
    }
}
