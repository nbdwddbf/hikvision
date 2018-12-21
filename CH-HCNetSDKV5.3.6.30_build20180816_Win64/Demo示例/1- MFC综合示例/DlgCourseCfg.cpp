// DlgCourseCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgCourseCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgCourseCfg dialog


DlgCourseCfg::DlgCourseCfg(CWnd* pParent /*=NULL*/)
	: CDialog(DlgCourseCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgCourseCfg)
	m_ctData = 0;
	m_nDayNum = 0;
	m_nEndHour = 0;
	m_nEndMin = 0;
	m_nLessionIndex = 0;
	m_nStartHour = 0;
	m_nStartMin = 0;
	m_nCourseIndex = 0;
	//}}AFX_DATA_INIT
	m_lUserID = 0;
	m_iDeviceIndex = 0;
	memset(&m_struCurriculum[0],0,64*sizeof(NET_DVR_CURRICULUM_CFG));
	memset(&m_struDate[0],0,64*sizeof(NET_DVR_DATE));
	m_index = -1;
	m_iStartChannel = 0;
	m_iMirrorNum = 0;
	m_nOldDay = 0;
	m_nDayCount = 0;
	m_nOldIndex = -1;
}


void DlgCourseCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgCourseCfg)
	DDX_Control(pDX, IDC_COM_LESSION_INDEX, m_comLessionIndex);
	DDX_Control(pDX, IDC_COM_DAY_INDEX, m_comDayIndex);
	DDX_DateTimeCtrl(pDX, IDC_DATE, m_ctData);
	DDX_Text(pDX, IDC_DAY_NUM, m_nDayNum);
	DDX_Text(pDX, IDC_END_HOUR, m_nEndHour);
	DDX_Text(pDX, IDC_END_MIN, m_nEndMin);
	DDX_Text(pDX, IDC_LESSION_INDEX, m_nLessionIndex);
	DDX_Text(pDX, IDC_START_HOUR, m_nStartHour);
	DDX_Text(pDX, IDC_START_MIN, m_nStartMin);
	DDX_Text(pDX, IDC_COURSE_INDEX, m_nCourseIndex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgCourseCfg, CDialog)
	//{{AFX_MSG_MAP(DlgCourseCfg)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_DAY_NUM_OK, OnBtnDayNumOk)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_CBN_SELCHANGE(IDC_COM_DAY_INDEX, OnSelchangeComDayIndex)
	ON_CBN_SELCHANGE(IDC_COM_LESSION_INDEX, OnSelchangeComLessionIndex)
	ON_BN_CLICKED(IDC_BTN_DATA_OK, OnBtnDataOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgCourseCfg message handlers
BOOL DlgCourseCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_comLessionIndex.SetCurSel(0);
	m_comDayIndex.SetCurSel(0);
	CTime timeCur = CTime::GetCurrentTime();
	CTime Data(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),0,0,0);
	m_ctData = Data;
	UpdateData(FALSE);
	return TRUE;
}

void DlgCourseCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	if (m_nDayNum == 0)
	{
		AfxMessageBox("请先输入天数!");
		return;
	}
	if (!m_bDataOK)
	{
		return;
	}
	if (m_nDayCount > 0)
	{
		AfxMessageBox("不是所有的索引（天）都赋值日期!");
		return;
	}
	OnBtnOk();
	DWORD *pStatus = new DWORD[m_nDayNum];
	char szLan[128] = {0};
	for (int i = 0; i < 64; i++)
	{
		m_struCurriculum[i].dwSize = sizeof(NET_DVR_CURRICULUM_CFG);
	}
	if (!NET_DVR_SetDeviceConfig(m_lUserID,NET_DVR_SET_CURRICULUM_CFG,m_nDayNum,&m_struDate[0],m_nDayNum*sizeof(NET_DVR_DATE),pStatus,&m_struCurriculum[0],m_nDayNum*sizeof(NET_DVR_CURRICULUM_CFG)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_CURRICULUM_CFG,  %s", "Set record faild");
		g_StringLanType(szLan, "设置课程失败", "Get record failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_CURRICULUM_CFG,  %s", " set course sucess");
		g_StringLanType(szLan, "设置课程成功", "set course sucess");
		AfxMessageBox(szLan);
	}

    if (NULL != pStatus)
    {
        delete[] pStatus;
        pStatus = NULL;
	}
	return;
}

void DlgCourseCfg::OnBtnDayNumOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_nDayNum > 64)
	{
		AfxMessageBox("请输入的天数小于等于64");
		return;
	}
	if (m_nOldDay != m_nDayNum)
	{
		m_comDayIndex.ResetContent();
		for (int i = 0; i < m_nDayNum; i++)
		{
			char chDay[20];
			sprintf(chDay,"第%d天",i);
			CString strDay;
			strDay.Format("%s",chDay);
			m_comDayIndex.AddString(strDay);
		}
		m_nOldDay = m_nDayNum;
		m_nDayCount = m_nDayNum;
	}
	UpdateData(FALSE);
}

void DlgCourseCfg::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_nDayNum == 0)
	{
		AfxMessageBox("请先输入天数!");
		return;
	}
	if (m_index == -1)
	{
		AfxMessageBox("请先选择第几天!");
		return;
	}
	int sel = m_comLessionIndex.GetCurSel();
	m_struCurriculum[m_index].struLessonInfo[sel].struSchedTime.byStartHour = m_nStartHour;
	m_struCurriculum[m_index].struLessonInfo[sel].struSchedTime.byStartMin = m_nStartMin;
	m_struCurriculum[m_index].struLessonInfo[sel].struSchedTime.byStopHour = m_nEndHour;
	m_struCurriculum[m_index].struLessonInfo[sel].struSchedTime.byStopMin = m_nEndMin;
	m_struCurriculum[m_index].struLessonInfo[sel].wSessionIndex = m_nLessionIndex;
	m_struCurriculum[m_index].struLessonInfo[sel].wCourseIndex = m_nCourseIndex;
	UpdateData(FALSE);
}

void DlgCourseCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	if (m_nDayNum == 0)
	{
		AfxMessageBox("请先输入天数!");
		return;
	}
	if (!m_bDataOK)
	{
		return;
	}
	if (m_nDayCount > 0)
	{
		AfxMessageBox("不是所有的索引（天）都赋值日期!");
		return;
	}
	DWORD dwReturnned = 0;
	DWORD Status = 0;
	char szLan[128] = {0};
	if (!NET_DVR_GetDeviceConfig(m_lUserID,NET_DVR_GET_CURRICULUM_CFG,m_nDayNum,&m_struDate[0],m_nDayNum*sizeof(NET_DVR_DATE),&Status,&m_struCurriculum[0],m_nDayNum*sizeof(NET_DVR_CURRICULUM_CFG)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_CURRICULUM_CFG,  %s", "Get rcourse faild");
		g_StringLanType(szLan, "获取课程失败", "Get course failed");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_CURRICULUM_CFG,  %s", "Get course success");
		g_StringLanType(szLan, "获取课程成功", "Get course success");
		AfxMessageBox(szLan);
	}
	m_comLessionIndex.SetCurSel(0);
	UpdateData(FALSE);
	OnSelchangeComLessionIndex();
}

void DlgCourseCfg::OnSelchangeComDayIndex() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_index = m_comDayIndex.GetCurSel();
	if (0 != m_struDate[m_index].wYear)
	{
		CTime Data(m_struDate[m_index].wYear,m_struDate[m_index].byMonth,m_struDate[m_index].byDay,0,0,0);
		m_ctData = Data;
	}
	else
	{
		CTime timeCur = CTime::GetCurrentTime();
		CTime Data(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),0,0,0);
		m_ctData = Data;
	}
	m_comLessionIndex.SetCurSel(0);
	UpdateData(FALSE);
	OnSelchangeComLessionIndex();
}

void DlgCourseCfg::OnSelchangeComLessionIndex() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_nDayNum == 0)
	{
		AfxMessageBox("请先输入天数!");
		return;
	}
	if (m_index == -1)
	{
		AfxMessageBox("请先选择第几天!");
		return;
	}
	int sel = m_comLessionIndex.GetCurSel();
	m_nStartHour = m_struCurriculum[m_index].struLessonInfo[sel].struSchedTime.byStartHour;
	m_nStartMin = m_struCurriculum[m_index].struLessonInfo[sel].struSchedTime.byStartMin;
	m_nEndHour = m_struCurriculum[m_index].struLessonInfo[sel].struSchedTime.byStopHour;
	m_nEndMin = m_struCurriculum[m_index].struLessonInfo[sel].struSchedTime.byStopMin;
	m_nLessionIndex = m_struCurriculum[m_index].struLessonInfo[sel].wSessionIndex;
	m_nCourseIndex = m_struCurriculum[m_index].struLessonInfo[sel].wCourseIndex;
	UpdateData(FALSE);
}

void DlgCourseCfg::OnBtnDataOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_index = m_comDayIndex.GetCurSel();
	if (-1 == m_index)
	{
		AfxMessageBox("请先选择第几天!");
		m_bDataOK = FALSE;

		return ;
	}
	m_struDate[m_index].wYear = m_ctData.GetYear();
	m_struDate[m_index].byMonth = m_ctData.GetMonth();
	m_struDate[m_index].byDay = m_ctData.GetDay();
	if (m_nDayCount > 0 && m_index != m_nOldIndex)
	{
		m_nDayCount--;
	}
	m_nOldIndex = m_index;
	m_bDataOK = TRUE;
	return ;
}
