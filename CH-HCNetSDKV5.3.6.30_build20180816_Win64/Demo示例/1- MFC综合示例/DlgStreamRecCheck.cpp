// DlgStreamRecCheck.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgStreamRecCheck.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_MSG_REC_CHECK_FINISH 1000

/////////////////////////////////////////////////////////////////////////////
// CDlgStreamRecCheck dialog


CDlgStreamRecCheck::CDlgStreamRecCheck(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStreamRecCheck::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgStreamRecCheck)
	m_oleDateStart = COleDateTime::GetCurrentTime();
	m_oleDateStop = COleDateTime::GetCurrentTime();
	m_oleTimeStart = COleDateTime::GetCurrentTime();
	m_oleTimeStop = COleDateTime::GetCurrentTime();
	m_nChannel = 0;
	m_csStreamID = _T("");
	m_oleDateStart2 = COleDateTime::GetCurrentTime();
	m_oleDateStop2 = COleDateTime::GetCurrentTime();
	m_nChannel2 = 0;
	m_csStreamID2 = _T("");
	m_nTotalRecSize = 0;
	m_oleTimeStart2 = COleDateTime::GetCurrentTime();
	m_oleTimeStop2 = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT

	memset(&m_struRecordCheckRet, 0, sizeof(m_struRecordCheckRet));
	m_lRecordCheckHandle = -1;
	m_bGetRecordCheckNext = FALSE;
	m_hGetRecordCheckThread = NULL;

	memset(&m_struRecordSegmentRet, 0, sizeof(m_struRecordSegmentRet));
	m_lRecordSegmentHandle = -1;
	m_bRecordSegmentNext = FALSE;
	m_hRecordSegmentThread = NULL;
}


CDlgStreamRecCheck::~CDlgStreamRecCheck()
{	
	if (m_hGetRecordCheckThread)
	{
		TerminateThread(m_hGetRecordCheckThread, 0);	
		CloseHandle(m_hGetRecordCheckThread);
		m_hGetRecordCheckThread = NULL;
	}

	if (m_hRecordSegmentThread)
	{
		TerminateThread(m_hRecordSegmentThread, 0);	
		CloseHandle(m_hRecordSegmentThread);
		m_hRecordSegmentThread = NULL;
	}
}


void CDlgStreamRecCheck::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgStreamRecCheck)
	DDX_Control(pDX, IDC_CMB_RECORD_RESULT, m_cmbRecNotComplete);
	DDX_Control(pDX, IDC_LIST_MISSING_REC_FILE, m_listMissingRecFile);
	DDX_Control(pDX, IDC_CMB_CHECK_TYPE, m_cmbCheckType);
	DDX_DateTimeCtrl(pDX, IDC_DATE_RT_START, m_oleDateStart);
	DDX_DateTimeCtrl(pDX, IDC_DATE_RT_STOP, m_oleDateStop);
	DDX_DateTimeCtrl(pDX, IDC_TIME_RT_START, m_oleTimeStart);
	DDX_DateTimeCtrl(pDX, IDC_TIME_RT_STOP, m_oleTimeStop);
	DDX_Text(pDX, IDC_EDIT_CHANNEL, m_nChannel);
	DDX_Text(pDX, IDC_EDIT_STREAM_ID, m_csStreamID);
	DDX_DateTimeCtrl(pDX, IDC_DATE_RT_START2, m_oleDateStart2);
	DDX_DateTimeCtrl(pDX, IDC_DATE_RT_STOP2, m_oleDateStop2);
	DDX_Text(pDX, IDC_EDIT_CHANNEL2, m_nChannel2);
	DDX_Text(pDX, IDC_EDIT_STREAM_ID2, m_csStreamID2);
	DDX_Text(pDX, IDC_EDIT_TOTAL_REC, m_nTotalRecSize);
	DDX_DateTimeCtrl(pDX, IDC_TIME_RT_START2, m_oleTimeStart2);
	DDX_DateTimeCtrl(pDX, IDC_TIME_RT_STOP2, m_oleTimeStop2);
	DDX_Control(pDX, IDC_CMB_TOTAL_REC, m_cmbTotalRec);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgStreamRecCheck, CDialog)
	//{{AFX_MSG_MAP(CDlgStreamRecCheck)
	ON_BN_CLICKED(IDC_BTN_CHECK, OnBtnCheck)
	ON_BN_CLICKED(IDC_BTN_GET_SEGMENT_REC, OnBtnGetSegmentRec)
	ON_MESSAGE(WM_MSG_REC_CHECK_FINISH, OnMsgRecCheckFinish)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgStreamRecCheck message handlers

BOOL CDlgStreamRecCheck::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);

	m_listMissingRecFile.SetExtendedStyle(m_listMissingRecFile.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	
	char szLan[128] = {0};
	g_StringLanType(szLan, "开始时间", "Start time");
	m_listMissingRecFile.InsertColumn(0, szLan, LVCFMT_LEFT, 120, -1);	
	g_StringLanType(szLan, "结束时间", "Stop Time");
	m_listMissingRecFile.InsertColumn(1, szLan, LVCFMT_LEFT, 120, -1);

	COleDateTime timeCur = COleDateTime::GetCurrentTime();
	COleDateTime timeStart(timeCur.GetYear(), timeCur.GetMonth(), timeCur.GetDay(), 0, 0, 0);
	COleDateTime timeStop(timeCur.GetYear(), timeCur.GetMonth(), timeCur.GetDay(), 23, 59, 59);
	
	m_oleDateStart = timeStart;
	m_oleTimeStart = timeStart;
	m_oleDateStop = timeStop;
	m_oleTimeStop = timeStop;

	m_oleDateStart2 = timeStart;
	m_oleTimeStart2 = timeStart;
	m_oleDateStop2 = timeStop;
	m_oleTimeStop2 = timeStop;

	m_iDevIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDevIndex].lLoginID;

	m_cmbCheckType.SetCurSel(0);

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgStreamRecCheck::OnBtnCheck()
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);
	char szLan[128] = {0};
	
	NET_DVR_RECORD_CHECK_COND struRecordCheckCond = {0};
	
	struRecordCheckCond.dwSize = sizeof(NET_DVR_RECORD_CHECK_COND);
	struRecordCheckCond.struStreamInfo.dwSize = sizeof(NET_DVR_STREAM_INFO);
	strncpy((char*)struRecordCheckCond.struStreamInfo.byID, m_csStreamID.GetBuffer(0), STREAM_ID_LEN);
	struRecordCheckCond.struStreamInfo.dwChannel = m_nChannel;
	
	struRecordCheckCond.byCheckType = m_cmbCheckType.GetCurSel();

	struRecordCheckCond.struBeginTime.wYear = m_oleDateStart.GetYear();
	struRecordCheckCond.struBeginTime.byMonth = m_oleDateStart.GetMonth();
	struRecordCheckCond.struBeginTime.byDay = m_oleDateStart.GetDay();
	struRecordCheckCond.struBeginTime.byHour = m_oleTimeStart.GetHour();
	struRecordCheckCond.struBeginTime.byMinute = m_oleTimeStart.GetMinute();
	struRecordCheckCond.struBeginTime.bySecond = m_oleTimeStart.GetSecond();
	
	struRecordCheckCond.struEndTime.wYear = m_oleDateStop.GetYear();
	struRecordCheckCond.struEndTime.byMonth = m_oleDateStop.GetMonth();
	struRecordCheckCond.struEndTime.byDay = m_oleDateStop.GetDay();
	struRecordCheckCond.struEndTime.byHour = m_oleTimeStop.GetHour();
	struRecordCheckCond.struEndTime.byMinute = m_oleTimeStop.GetMinute();
	struRecordCheckCond.struEndTime.bySecond = m_oleTimeStop.GetSecond();
	
	if (m_lRecordCheckHandle >= 0)
	{
		g_StringLanType(szLan, "检测中，先停止", "Processing，stop it first");
		AfxMessageBox(szLan);
		return;
	}
	
	m_lRecordCheckHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_RECORD_CHECK, \
		&struRecordCheckCond, sizeof(struRecordCheckCond), NULL, NULL);
	if (m_lRecordCheckHandle >= 0)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RECORD_CHECK succ");
		m_bGetRecordCheckNext = TRUE;
		DWORD dwThreadId;
		m_listMissingRecFile.DeleteAllItems();
		m_hGetRecordCheckThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetRecordCheckThread), this, 0, &dwThreadId);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RECORD_CHECK failed");
		g_StringLanType(szLan, "检查失败", "NET_DVR_RECORD_CHECK Failed");
		AfxMessageBox(szLan);
		return;
	}
}

DWORD WINAPI CDlgStreamRecCheck::GetRecordCheckThread( LPVOID lpRecordCheck )
{
	CDlgStreamRecCheck* pThis = reinterpret_cast<CDlgStreamRecCheck*>(lpRecordCheck);
	int iRet = 0;
	char szLan[128] = {0};
	char szInfoBuf[128] = {0};
	while (pThis->m_bGetRecordCheckNext)
	{
		iRet = NET_DVR_GetNextRemoteConfig(pThis->m_lRecordCheckHandle, &pThis->m_struRecordCheckRet, sizeof(NET_DVR_RECORD_CHECK_RET)); 
		if (iRet == NET_SDK_GET_NEXT_STATUS_SUCCESS)
		{
			pThis->AddRecordCheckInfoToDlg(&pThis->m_struRecordCheckRet);
		}
		else
		{
			if (iRet == NET_SDK_GET_NETX_STATUS_NEED_WAIT)
			{
				Sleep(5);
				continue;
			}
			if (iRet == NET_SDK_GET_NEXT_STATUS_FINISH)
			{				
				g_StringLanType(szLan, "检查结束!", "Check Finished");
				sprintf(szInfoBuf, "%s[Info Count:%d]", szLan, pThis->m_listMissingRecFile.GetItemCount());
				AfxMessageBox(szInfoBuf);
				break;
			}
			else if(iRet == NET_SDK_GET_NEXT_STATUS_FAILED)
			{
				g_StringLanType(szLan, "检查失败", "Check Failed");
				AfxMessageBox(szLan);
				break;
			}
			else
			{
				g_StringLanType(szLan, "未知状态", "Unknown status");
				AfxMessageBox(szLan);
				break;
			}
		}
	}
	NET_DVR_StopRemoteConfig(pThis->m_lRecordCheckHandle);
	pThis->m_bGetRecordCheckNext = FALSE;
	pThis->m_lRecordCheckHandle = -1;
	return 0 ;
}

void CDlgStreamRecCheck::AddRecordCheckInfoToDlg( LPNET_DVR_RECORD_CHECK_RET lpInter )
{
	if (lpInter->byRecordNotComplete >= 0)
	{
		m_cmbRecNotComplete.SetCurSel(lpInter->byRecordNotComplete);
	}
	
	int iItemCount = m_listMissingRecFile.GetItemCount();
	
	m_listMissingRecFile.InsertItem(iItemCount, "");
	
	CString csTmp;
	
	csTmp.Format("%04d%02d%02d%02d%02d%02d",lpInter->struBeginTime.wYear, \
		lpInter->struBeginTime.byMonth, lpInter->struBeginTime.byDay, \
		lpInter->struBeginTime.byHour, lpInter->struBeginTime.byMinute,\
		lpInter->struBeginTime.bySecond);
	m_listMissingRecFile.SetItemText(iItemCount, 0, csTmp);
	
	csTmp.Format("%04d%02d%02d%02d%02d%02d", lpInter->struEndTime.wYear, lpInter->struEndTime.byMonth,\
		lpInter->struEndTime.byDay, lpInter->struEndTime.byHour, \
		lpInter->struEndTime.byMinute, lpInter->struEndTime.bySecond);
	m_listMissingRecFile.SetItemText(iItemCount, 1, csTmp);
}

void CDlgStreamRecCheck::OnBtnGetSegmentRec() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	
	NET_DVR_RECORD_SEGMENT_COND struRecordSegmentCond = {0};
	
	struRecordSegmentCond.dwSize = sizeof(NET_DVR_RECORD_SEGMENT_COND);
	struRecordSegmentCond.struStreanInfo.dwSize = sizeof(NET_DVR_STREAM_INFO);
	strncpy((char*)struRecordSegmentCond.struStreanInfo.byID, m_csStreamID2.GetBuffer(0), STREAM_ID_LEN);
	struRecordSegmentCond.struStreanInfo.dwChannel = m_nChannel2;

	struRecordSegmentCond.struStartTime.wYear = m_oleDateStart2.GetYear();
	struRecordSegmentCond.struStartTime.byMonth = m_oleDateStart2.GetMonth();
	struRecordSegmentCond.struStartTime.byDay = m_oleDateStart2.GetDay();
	struRecordSegmentCond.struStartTime.byHour = m_oleTimeStart2.GetHour();
	struRecordSegmentCond.struStartTime.byMinute = m_oleTimeStart2.GetMinute();
	struRecordSegmentCond.struStartTime.bySecond = m_oleTimeStart2.GetSecond();
	
	struRecordSegmentCond.struStopTime.wYear = m_oleDateStop2.GetYear();
	struRecordSegmentCond.struStopTime.byMonth = m_oleDateStop2.GetMonth();
	struRecordSegmentCond.struStopTime.byDay = m_oleDateStop2.GetDay();
	struRecordSegmentCond.struStopTime.byHour = m_oleTimeStop2.GetHour();
	struRecordSegmentCond.struStopTime.byMinute = m_oleTimeStop2.GetMinute();
	struRecordSegmentCond.struStopTime.bySecond = m_oleTimeStop2.GetSecond();
	
	if (m_lRecordSegmentHandle >= 0)
	{
		g_StringLanType(szLan, "获取中，先停止", "Processing, stop it first");
		AfxMessageBox(szLan);
		return;
	}

	m_cmbTotalRec.ResetContent();
	
	m_lRecordSegmentHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_GET_RECORD_SEGMENT_CFG, \
		&struRecordSegmentCond, sizeof(struRecordSegmentCond), NULL, NULL);
	if (m_lRecordSegmentHandle >= 0)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_RECORD_SEGMENT_CFG succ");
		m_bRecordSegmentNext = TRUE;
		DWORD dwThreadId;
		m_hRecordSegmentThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetRecordSegmentThread), this, 0, &dwThreadId);	
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_RECORD_SEGMENT_CFG failed");
		g_StringLanType(szLan, "获取失败", "NET_DVR_GET_RECORD_SEGMENT_CFG Failed");
		AfxMessageBox(szLan);
		return;
	}

}


DWORD WINAPI CDlgStreamRecCheck::GetRecordSegmentThread( LPVOID lpRecordSegment )
{
	CDlgStreamRecCheck* pThis = reinterpret_cast<CDlgStreamRecCheck*>(lpRecordSegment);
	int iRet = 0;
	char szLan[128] = {0};
	while (pThis->m_bRecordSegmentNext)
	{
		iRet = NET_DVR_GetNextRemoteConfig(pThis->m_lRecordSegmentHandle, &pThis->m_struRecordSegmentRet, sizeof(NET_DVR_RECORD_SEGMENT_RET)); 
		if (iRet == NET_SDK_GET_NEXT_STATUS_SUCCESS)
		{
			pThis->AddRecordSegmentInfoToDlg(&pThis->m_struRecordSegmentRet);
			//pThis->PostMessage(WM_MSG_REC_CHECK_FINISH, (WPARAM)iRet, 0);
			//pThis->PostMessage(WM_MSG_REC_CHECK_FINISH,0,0);
		}
		else
		{
			if (iRet == NET_SDK_GET_NETX_STATUS_NEED_WAIT)
			{
				Sleep(5);
				continue;
			}
			if (iRet == NET_SDK_GET_NEXT_STATUS_FINISH)
			{
				//pThis->PostMessage(WM_MSG_REC_CHECK_FINISH, (WPARAM)iRet, 0);
				g_StringLanType(szLan, "获取结束!", "Get Finished");
				AfxMessageBox(szLan);
				break;
			}
			else if(iRet == NET_SDK_GET_NEXT_STATUS_FAILED)
			{
				//pThis->PostMessage(WM_MSG_REC_CHECK_FINISH, (WPARAM)iRet, 0);
				g_StringLanType(szLan, "获取失败", "Get Failed");
				AfxMessageBox(szLan);
				break;
			}
			else
			{
				//pThis->PostMessage(WM_MSG_REC_CHECK_FINISH, (WPARAM)iRet, 0);
				g_StringLanType(szLan, "未知状态", "Unknown status");
				AfxMessageBox(szLan);
				break;
			}
		}
	}

	NET_DVR_StopRemoteConfig(pThis->m_lRecordSegmentHandle);
	pThis->m_bRecordSegmentNext = FALSE;
	pThis->m_lRecordSegmentHandle = -1;
	
	return 0 ;
}

void CDlgStreamRecCheck::AddRecordSegmentInfoToDlg( LPNET_DVR_RECORD_SEGMENT_RET lpInter )
{
	//m_nTotalRecSize = lpInter->dwRecordTotalSize;

	m_cmbTotalRec.ResetContent();

	char szLan[32] = { 0 };
	sprintf(szLan, "%d", lpInter->dwRecordTotalSize);

	m_cmbTotalRec.InsertString(0, szLan);

	m_cmbTotalRec.SetCurSel(0);
}

LRESULT CDlgStreamRecCheck::OnMsgRecCheckFinish(WPARAM wParam, LPARAM lParam)
{
// 	int iRet = (int)wParam;
// 	char szLan[128] = { 0 };

	UpdateData(FALSE);

	return TRUE;
}
