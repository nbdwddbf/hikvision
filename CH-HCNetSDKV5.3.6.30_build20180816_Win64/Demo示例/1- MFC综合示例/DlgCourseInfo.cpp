// DlgCourseInfo.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgCourseInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgCourseInfo dialog


DlgCourseInfo::DlgCourseInfo(CWnd* pParent /*=NULL*/)
	: CDialog(DlgCourseInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgCourseInfo)
	m_sCourseDescription = _T("");
	m_sCourseName = _T("");
	m_sTeacherName = _T("");
	m_index = 0;
	//}}AFX_DATA_INIT
	memset(&m_struCourseRecordInfo,0,sizeof(m_struCourseRecordInfo));
	m_lUserID = 0;
	m_iDeviceIndex = 0;
	m_iStartChannel = 0;
	m_iMirrorNum = 0;
}


void DlgCourseInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgCourseInfo)
	DDX_Text(pDX, IDC_COURSE_DESCRIPTION, m_sCourseDescription);
	DDX_Text(pDX, IDC_COURSE_NAME, m_sCourseName);
	DDX_Text(pDX, IDC_TEACHER_NAME, m_sTeacherName);
	DDX_Text(pDX, IDC_INDEX, m_index);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgCourseInfo, CDialog)
	//{{AFX_MSG_MAP(DlgCourseInfo)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgCourseInfo message handlers
BOOL DlgCourseInfo::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_index = 1;
	UpdateData(FALSE);
	OnBtnGet();
	return TRUE;
}

void DlgCourseInfo::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReturnned = 0;
	char szLan[128] = {0};
	if (!NET_DVR_GetDVRConfig(m_lUserID,NET_DVR_GET_COURSE_INDEX_CFG,m_index,&m_struCourseRecordInfo,sizeof(m_struCourseRecordInfo),&dwReturnned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_COURSE_INDEX_CFG,  %s", "Get rcourse index faild");
		g_StringLanType(szLan, "获取课程配置失败", "Get course index failed");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_COURSE_INDEX_CFG,  %s", "Get course index success");
		g_StringLanType(szLan, "获取课程配置成功", "Get course index success");
		AfxMessageBox(szLan);
	}
	m_index = m_struCourseRecordInfo.byIndex;
	char sCourseDescroption[COURSE_DESCRIPTION_LEN] = {0};
	char sInstructorName[COURSE_DESCRIPTION_LEN] = {0};
	char sCourseName[COURSE_DESCRIPTION_LEN] = {0};
	memcpy(sCourseDescroption,m_struCourseRecordInfo.sCourseDescription,COURSE_DESCRIPTION_LEN);
	memcpy(sCourseName,m_struCourseRecordInfo.sCourseName,COURSE_NAME_LEN);
	memcpy(sInstructorName,m_struCourseRecordInfo.sInstructorName,INSTRUCTOR_NAME_LEN);
	m_sCourseDescription.Format("%s",sCourseDescroption);
	m_sCourseName.Format("%s",sCourseName);
	m_sTeacherName.Format("%s",sInstructorName);
	UpdateData(FALSE);
}

void DlgCourseInfo::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	UpdateData(TRUE);
	char sCourseDescroption[COURSE_DESCRIPTION_LEN] = {0};
	char sInstructorName[COURSE_DESCRIPTION_LEN] = {0};
	char sCourseName[COURSE_DESCRIPTION_LEN] = {0};

// 	if (m_sCourseDescription.GetLength() > COURSE_DESCRIPTION_LEN)
// 	{
// 		AfxMessageBox("课程名称超出最大字数限额");
// 		return;
// 	}
// 	if (m_sCourseName.GetLength() > COURSE_DESCRIPTION_LEN)
// 	{
// 		AfxMessageBox("课程名称超出最大字数限额");
// 		return;
// 	}
	sprintf(sCourseDescroption,"%s",m_sCourseDescription);
	memcpy(m_struCourseRecordInfo.sCourseDescription,sCourseDescroption,COURSE_DESCRIPTION_LEN);
	sprintf(sCourseName,"%s",m_sCourseName);
	memcpy(m_struCourseRecordInfo.sCourseName,sCourseName,COURSE_NAME_LEN);
	sprintf(sInstructorName,"%s",m_sTeacherName);
	memcpy(m_struCourseRecordInfo.sInstructorName,sInstructorName,INSTRUCTOR_NAME_LEN);
	m_struCourseRecordInfo.byIndex = m_index;
	m_struCourseRecordInfo.dwSize = sizeof(m_struCourseRecordInfo);
	char szLan[128] = {0};
	if(!NET_DVR_SetDVRConfig(m_lUserID,NET_DVR_SET_COURSE_INDEX_CFG,m_index,&m_struCourseRecordInfo,sizeof(m_struCourseRecordInfo)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_COURSE_INDEX_CFG,  %s", "Set course index faild");
		g_StringLanType(szLan, "设置课程配置失败", "Get record course index failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_COURSE_INDEX_CFG,  %s", " publish course index sucess");
		g_StringLanType(szLan, "设置课程配置成功", "publish course index sucess");
		AfxMessageBox(szLan);
	}
}
