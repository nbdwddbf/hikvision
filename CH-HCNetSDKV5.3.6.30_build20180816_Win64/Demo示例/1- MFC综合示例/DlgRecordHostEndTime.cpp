// DlgRecordHostEndTime.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRecordHostEndTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgRecordHostEndTime dialog


DlgRecordHostEndTime::DlgRecordHostEndTime(CWnd* pParent /*=NULL*/)
	: CDialog(DlgRecordHostEndTime::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgRecordHostEndTime)
	m_ctData = 0;
	m_ctTime = 0;
	//}}AFX_DATA_INIT
	memset(&m_TimeEx, 0 ,sizeof(m_TimeEx));
	m_lUserID = 0;
	m_iDeviceIndex = 0;
	m_iStartChannel = 0;
	m_iMirrorNum = 0;
}


void DlgRecordHostEndTime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgRecordHostEndTime)
	DDX_DateTimeCtrl(pDX, IDC_DATE, m_ctData);
	DDX_DateTimeCtrl(pDX, IDC_TIME, m_ctTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgRecordHostEndTime, CDialog)
	//{{AFX_MSG_MAP(DlgRecordHostEndTime)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgRecordHostEndTime message handlers
BOOL DlgRecordHostEndTime::OnInitDialog()
{
	CDialog::OnInitDialog();
	OnBtnGet();
	return TRUE;
}

void DlgRecordHostEndTime::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturnned = 0;
	char szLan[128] = {0};
	if (!NET_DVR_GetDVRConfig(m_lUserID,NET_DVR_GET_RECORDING_END_TIME,m_iStartChannel,&m_TimeEx,sizeof(m_TimeEx),&dwReturnned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_RECORDING_END_TIME,  %s", "Get Record end time faild");
		g_StringLanType(szLan, "获取录播剩余时间失败", "Get Record end time failed");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_RECORDING_END_TIME,  %s", "Get Record end time success");
		g_StringLanType(szLan, "获取录播剩余时间成功", "Get Record end time success");
		//AfxMessageBox(szLan);
	}
	if (m_TimeEx.wYear != 0)
	{
		CTime Time(m_TimeEx.wYear,m_TimeEx.byMonth,m_TimeEx.byDay,m_TimeEx.byHour,m_TimeEx.byMinute,m_TimeEx.bySecond);
	//	CTime Time(m_TimeEx.wYear,m_TimeEx.byMonth,m_TimeEx.byDay,23,59,59);
		m_ctData = Time;
		m_ctTime = Time;
		AfxMessageBox(szLan);
	}
	else
	{
		AfxMessageBox("获取值为0");
	}
	
	UpdateData(FALSE);
}
