// DlgInfoDiffusionScheduleSelfdefine.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInfoDiffusionScheduleSelfdefine.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionScheduleSelfdefine dialog


CDlgInfoDiffusionScheduleSelfdefine::CDlgInfoDiffusionScheduleSelfdefine(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInfoDiffusionScheduleSelfdefine::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInfoDiffusionScheduleSelfdefine)
	m_timeEndDate = COleDateTime::GetCurrentTime();
	m_timeEndTime = COleDateTime::GetCurrentTime();
	m_timeStartDate = COleDateTime::GetCurrentTime();
	m_timeStartTime = COleDateTime::GetCurrentTime();
	m_dwProgramID = 0;
	//}}AFX_DATA_INIT
	memset(m_struSeldefineSchedule, 0, sizeof(m_struSeldefineSchedule));
	m_nCurSelSpan = -1;
}


void CDlgInfoDiffusionScheduleSelfdefine::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInfoDiffusionScheduleSelfdefine)
	DDX_Control(pDX, IDC_LIST_SPAN, m_listSpan);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_END_DATE, m_timeEndDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_END_TIME, m_timeEndTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START_DATE, m_timeStartDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START_TIME, m_timeStartTime);
	DDX_Text(pDX, IDC_EDIT_PROGRAM_ID, m_dwProgramID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInfoDiffusionScheduleSelfdefine, CDialog)
	//{{AFX_MSG_MAP(CDlgInfoDiffusionScheduleSelfdefine)
	ON_BN_CLICKED(IDC_BTN_CANCEL, OnBtnCancel)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_BN_CLICKED(IDC_BTN_SPAN_ADD, OnBtnSpanAdd)
	ON_BN_CLICKED(IDC_BTN_SPAN_DEL, OnBtnSpanDel)
	ON_BN_CLICKED(IDC_BTN_SPAN_MOD, OnBtnSpanMod)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SPAN, OnClickListSpan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionScheduleSelfdefine message handlers

void CDlgInfoDiffusionScheduleSelfdefine::InitializeData(NET_DVR_PLAY_SELDEFINE* lpSelfdefine)
{
	if (lpSelfdefine == NULL)
	{
		return;
	}
	memcpy(m_struSeldefineSchedule, lpSelfdefine, sizeof(NET_DVR_PLAY_SELDEFINE)*MAX_NUM_SELDEFINE);
}

void CDlgInfoDiffusionScheduleSelfdefine::SaveData(NET_DVR_PLAY_SELDEFINE* lpSelfdefine)
{
	if (lpSelfdefine == NULL)
	{
		return;
	}
	memcpy(lpSelfdefine, m_struSeldefineSchedule, sizeof(NET_DVR_PLAY_SELDEFINE)*MAX_NUM_SELDEFINE);
}

void CDlgInfoDiffusionScheduleSelfdefine::InitPlaySpanList()
{
	DWORD dwExStyle = m_listSpan.GetExtendedStyle();
	dwExStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
	m_listSpan.SetExtendedStyle(dwExStyle);
	
	char szLan[512] = {0};
	g_StringLanType(szLan, "序号", "Index");
	m_listSpan.InsertColumn(0, szLan);
	m_listSpan.SetColumnWidth(0, 40);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "节目编号", "Program No.");
	m_listSpan.InsertColumn(1, szLan);
	m_listSpan.SetColumnWidth(1, 80);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "起始时间", "Start Time");
	m_listSpan.InsertColumn(2, szLan);
	m_listSpan.SetColumnWidth(2, 120);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "结束时间", "End Time");
	m_listSpan.InsertColumn(3, szLan);
	m_listSpan.SetColumnWidth(3, 120);
}

void CDlgInfoDiffusionScheduleSelfdefine::RefreshPlaySpanList()
{
	m_listSpan.DeleteAllItems();
	int nSpanCnt = 0;
	CString str;
	for (nSpanCnt = 0; nSpanCnt < MAX_SPANS_A_DAY; nSpanCnt++)
	{
		LPNET_DVR_PLAY_SELDEFINE lpSpan = &m_struSeldefineSchedule[nSpanCnt];
		if (0 == lpSpan->dwSeldefineID)
		{
			break;
		}
		str.Format("%d", nSpanCnt+1);
		m_listSpan.InsertItem(nSpanCnt, str);
		str.Format("%d", lpSpan->dwProgramID);
		m_listSpan.SetItemText(nSpanCnt, 1, str);
		str.Format("%d%02d%02d %02d:%02d:%02d", lpSpan->struTimeRange.struBeginTime.dwYear,
			lpSpan->struTimeRange.struBeginTime.dwMonth,
			lpSpan->struTimeRange.struBeginTime.dwDay,
			lpSpan->struTimeRange.struBeginTime.dwHour,
			lpSpan->struTimeRange.struBeginTime.dwMinute,
			lpSpan->struTimeRange.struBeginTime.dwSecond);
		m_listSpan.SetItemText(nSpanCnt, 2, str);
		str.Format("%d%02d%02d %02d:%02d:%02d", lpSpan->struTimeRange.struEndTime.dwYear,
			lpSpan->struTimeRange.struEndTime.dwMonth,
			lpSpan->struTimeRange.struEndTime.dwDay,
			lpSpan->struTimeRange.struEndTime.dwHour,
			lpSpan->struTimeRange.struEndTime.dwMinute,
			lpSpan->struTimeRange.struEndTime.dwSecond);
		m_listSpan.SetItemText(nSpanCnt, 3, str);
	}
}

void CDlgInfoDiffusionScheduleSelfdefine::OnBtnCancel() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CDlgInfoDiffusionScheduleSelfdefine::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CDlgInfoDiffusionScheduleSelfdefine::OnBtnSpanAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	CString str;
	int nSpanIndex = -1;
	int nSpanCnt = 0;
	for (nSpanCnt = 0; nSpanCnt < MAX_SPANS_A_DAY; nSpanCnt++)
	{
		if (0 == m_struSeldefineSchedule[nSpanCnt].dwSeldefineID)
		{
			nSpanIndex = nSpanCnt;
			break;
		}
	}
	if (nSpanIndex < 0)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "时段数量已达上限", "The number of span is limited.");
		g_StringLanType(szLan2, "自定义日程配置", "Self-define Schedule Configuration");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	LPNET_DVR_PLAY_SELDEFINE lpSpan = &m_struSeldefineSchedule[nSpanIndex];
	lpSpan->dwSeldefineID = nSpanIndex+1;
	lpSpan->dwProgramID = m_dwProgramID;
	lpSpan->struTimeRange.struBeginTime.dwYear = m_timeStartDate.GetYear();
	lpSpan->struTimeRange.struBeginTime.dwMonth = m_timeStartDate.GetMonth();
	lpSpan->struTimeRange.struBeginTime.dwDay = m_timeStartDate.GetDay();
	lpSpan->struTimeRange.struBeginTime.dwHour = m_timeStartTime.GetHour();
	lpSpan->struTimeRange.struBeginTime.dwMinute = m_timeStartTime.GetMinute();
	lpSpan->struTimeRange.struBeginTime.dwSecond = m_timeStartTime.GetSecond();
	lpSpan->struTimeRange.struEndTime.dwYear = m_timeEndDate.GetYear();
	lpSpan->struTimeRange.struEndTime.dwMonth = m_timeEndDate.GetMonth();
	lpSpan->struTimeRange.struEndTime.dwDay = m_timeEndDate.GetDay();
	lpSpan->struTimeRange.struEndTime.dwHour = m_timeEndTime.GetHour();
	lpSpan->struTimeRange.struEndTime.dwMinute = m_timeEndTime.GetMinute();
	lpSpan->struTimeRange.struEndTime.dwSecond = m_timeEndTime.GetSecond();
	str.Format("%d", nSpanIndex+1);
	m_listSpan.InsertItem(nSpanIndex, str);
	m_listSpan.SetItemState(nSpanIndex, 0, -1);
	m_listSpan.SetItemState(nSpanIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_listSpan.SetFocus();
	m_nCurSelSpan = nSpanIndex;
	str.Format("%d", lpSpan->dwProgramID);
	m_listSpan.SetItemText(nSpanIndex, 1, str);
	str.Format("%d%02d%02d %02d:%02d:%02d", lpSpan->struTimeRange.struBeginTime.dwYear,
		lpSpan->struTimeRange.struBeginTime.dwMonth,
		lpSpan->struTimeRange.struBeginTime.dwDay,
		lpSpan->struTimeRange.struBeginTime.dwHour,
		lpSpan->struTimeRange.struBeginTime.dwMinute,
		lpSpan->struTimeRange.struBeginTime.dwSecond);
	m_listSpan.SetItemText(nSpanIndex, 2, str);
	str.Format("%d%02d%02d %02d:%02d:%02d", lpSpan->struTimeRange.struEndTime.dwYear,
		lpSpan->struTimeRange.struEndTime.dwMonth,
		lpSpan->struTimeRange.struEndTime.dwDay,
		lpSpan->struTimeRange.struEndTime.dwHour,
		lpSpan->struTimeRange.struEndTime.dwMinute,
		lpSpan->struTimeRange.struEndTime.dwSecond);
	m_listSpan.SetItemText(nSpanIndex, 3, str);
}

void CDlgInfoDiffusionScheduleSelfdefine::OnBtnSpanDel() 
{
	// TODO: Add your control notification handler code here
	if (m_nCurSelSpan < 0)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "请选择播放时段", "Please choose a Span first.");
		g_StringLanType(szLan2, "自定义日程配置", "Self-define Schedule Configuration");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	
	CString str;
	for (int nSpanCnt = m_nCurSelSpan; nSpanCnt < m_listSpan.GetItemCount()-1; nSpanCnt++)
	{
		m_listSpan.SetItemText(nSpanCnt, 1, m_listSpan.GetItemText(nSpanCnt+1, 1));
		m_listSpan.SetItemText(nSpanCnt, 2, m_listSpan.GetItemText(nSpanCnt+1, 2));
		m_listSpan.SetItemText(nSpanCnt, 3, m_listSpan.GetItemText(nSpanCnt+1, 3));
		memcpy(&m_struSeldefineSchedule[nSpanCnt], &m_struSeldefineSchedule[nSpanCnt+1], sizeof(NET_DVR_PLAY_SELDEFINE));
		m_struSeldefineSchedule[nSpanCnt].dwSeldefineID = nSpanCnt+1;
	}
	LPNET_DVR_PLAY_SELDEFINE lpSpan = &m_struSeldefineSchedule[m_listSpan.GetItemCount()-1];
	memset(lpSpan, 0, sizeof(*lpSpan));
	m_listSpan.DeleteItem(m_listSpan.GetItemCount()-1);
	m_nCurSelSpan = -1;
}

void CDlgInfoDiffusionScheduleSelfdefine::OnBtnSpanMod() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (m_nCurSelSpan < 0)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "请选择播放时段", "Please choose a Span first.");
		g_StringLanType(szLan2, "自定义日程配置", "Self-define Schedule Configuration");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}

	CString str;
	LPNET_DVR_PLAY_SELDEFINE lpSpan = &m_struSeldefineSchedule[m_nCurSelSpan];
	lpSpan->dwProgramID = m_dwProgramID;
	lpSpan->struTimeRange.struBeginTime.dwYear = m_timeStartDate.GetYear();
	lpSpan->struTimeRange.struBeginTime.dwMonth = m_timeStartDate.GetMonth();
	lpSpan->struTimeRange.struBeginTime.dwDay = m_timeStartDate.GetDay();
	lpSpan->struTimeRange.struBeginTime.dwHour = m_timeStartTime.GetHour();
	lpSpan->struTimeRange.struBeginTime.dwMinute = m_timeStartTime.GetMinute();
	lpSpan->struTimeRange.struBeginTime.dwSecond = m_timeStartTime.GetSecond();
	lpSpan->struTimeRange.struEndTime.dwYear = m_timeEndDate.GetYear();
	lpSpan->struTimeRange.struEndTime.dwMonth = m_timeEndDate.GetMonth();
	lpSpan->struTimeRange.struEndTime.dwDay = m_timeEndDate.GetDay();
	lpSpan->struTimeRange.struEndTime.dwHour = m_timeEndTime.GetHour();
	lpSpan->struTimeRange.struEndTime.dwMinute = m_timeEndTime.GetMinute();
	lpSpan->struTimeRange.struEndTime.dwSecond = m_timeEndTime.GetSecond();
	str.Format("%d", lpSpan->dwProgramID);
	m_listSpan.SetItemText(m_nCurSelSpan, 1, str);
	str.Format("%d%02d%02d %02d:%02d:%02d", lpSpan->struTimeRange.struBeginTime.dwYear,
		lpSpan->struTimeRange.struBeginTime.dwMonth,
		lpSpan->struTimeRange.struBeginTime.dwDay,
		lpSpan->struTimeRange.struBeginTime.dwHour,
		lpSpan->struTimeRange.struBeginTime.dwMinute,
		lpSpan->struTimeRange.struBeginTime.dwSecond);
	m_listSpan.SetItemText(m_nCurSelSpan, 2, str);
	str.Format("%d%02d%02d %02d:%02d:%02d", lpSpan->struTimeRange.struEndTime.dwYear,
		lpSpan->struTimeRange.struEndTime.dwMonth,
		lpSpan->struTimeRange.struEndTime.dwDay,
		lpSpan->struTimeRange.struEndTime.dwHour,
		lpSpan->struTimeRange.struEndTime.dwMinute,
		lpSpan->struTimeRange.struEndTime.dwSecond);
	m_listSpan.SetItemText(m_nCurSelSpan, 3, str);
}

BOOL CDlgInfoDiffusionScheduleSelfdefine::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitPlaySpanList();
	RefreshPlaySpanList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgInfoDiffusionScheduleSelfdefine::OnClickListSpan(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listSpan.GetFirstSelectedItemPosition();
	if (pos)
	{
		m_nCurSelSpan = m_listSpan.GetNextSelectedItem(pos);
		m_dwProgramID = m_struSeldefineSchedule[m_nCurSelSpan].dwProgramID;
		m_timeStartDate.SetDate(m_struSeldefineSchedule[m_nCurSelSpan].struTimeRange.struBeginTime.dwYear,
			m_struSeldefineSchedule[m_nCurSelSpan].struTimeRange.struBeginTime.dwMonth,
			m_struSeldefineSchedule[m_nCurSelSpan].struTimeRange.struBeginTime.dwDay);
		m_timeStartTime.SetTime(m_struSeldefineSchedule[m_nCurSelSpan].struTimeRange.struBeginTime.dwHour,
			m_struSeldefineSchedule[m_nCurSelSpan].struTimeRange.struBeginTime.dwMinute,
			m_struSeldefineSchedule[m_nCurSelSpan].struTimeRange.struBeginTime.dwSecond);
		m_timeEndDate.SetDate(m_struSeldefineSchedule[m_nCurSelSpan].struTimeRange.struEndTime.dwYear,
			m_struSeldefineSchedule[m_nCurSelSpan].struTimeRange.struEndTime.dwMonth,
			m_struSeldefineSchedule[m_nCurSelSpan].struTimeRange.struEndTime.dwDay);
		m_timeEndTime.SetTime(m_struSeldefineSchedule[m_nCurSelSpan].struTimeRange.struEndTime.dwHour,
			m_struSeldefineSchedule[m_nCurSelSpan].struTimeRange.struEndTime.dwMinute,
			m_struSeldefineSchedule[m_nCurSelSpan].struTimeRange.struEndTime.dwSecond);
		UpdateData(FALSE);
	}
	
	*pResult = 0;
}
