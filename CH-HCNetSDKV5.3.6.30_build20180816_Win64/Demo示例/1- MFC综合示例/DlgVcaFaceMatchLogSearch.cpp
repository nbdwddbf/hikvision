// DlgVcaFaceMatchLogSearch.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaFaceMatchLogSearch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaFaceMatchLogSearch dialog
CDlgVcaFaceMatchLogSearch *g_pVcaFindMatch = NULL;
UINT GetFindFaceMatchLogThread(LPVOID pParam)
{
	
    UNREFERENCED_PARAMETER(pParam);
	
	LONG bRet = -1;
	NET_VCA_FACESNAP_MATCH_ALARM_LOG struFaceMatchLog;
    memset(&struFaceMatchLog, 0, sizeof(struFaceMatchLog));
	CString csTmp;
	char szLan[256] = {0};
	while (1) 
	{
		bRet = NET_DVR_FindNextFaceMatchAlarm(g_pVcaFindMatch->m_lFindHandle, &struFaceMatchLog);
        if (bRet == NET_DVR_FILE_SUCCESS)
		{
			csTmp.Format("%d", g_pVcaFindMatch->m_lFaceMatchLogNum+1);
			g_pVcaFindMatch->m_listFindData.InsertItem(g_pVcaFindMatch->m_lFaceMatchLogNum, csTmp,0);

			NET_DVR_TIME  struAbsTime = {0};
			struAbsTime.dwYear = GET_YEAR(struFaceMatchLog.struSnapInfoLog.dwAbsTime);
			struAbsTime.dwMonth = GET_MONTH(struFaceMatchLog.struSnapInfoLog.dwAbsTime);
			struAbsTime.dwDay = GET_DAY(struFaceMatchLog.struSnapInfoLog.dwAbsTime);
			struAbsTime.dwHour = GET_HOUR(struFaceMatchLog.struSnapInfoLog.dwAbsTime);
			struAbsTime.dwMinute = GET_MINUTE(struFaceMatchLog.struSnapInfoLog.dwAbsTime);
            struAbsTime.dwSecond = GET_SECOND(struFaceMatchLog.struSnapInfoLog.dwAbsTime);
            csTmp.Format("%04d-%02d-%02d %02d:%02d:%02d", struAbsTime.dwYear, struAbsTime.dwMonth, struAbsTime.dwDay, \
				struAbsTime.dwHour,struAbsTime.dwMinute, struAbsTime.dwSecond);
			g_pVcaFindMatch->m_listFindData.SetItemText(g_pVcaFindMatch->m_lFaceMatchLogNum, 1, csTmp);	


            csTmp.Format("%d", struFaceMatchLog.struSnapInfoLog.dwSnapFacePicID);
			g_pVcaFindMatch->m_listFindData.SetItemText(g_pVcaFindMatch->m_lFaceMatchLogNum, 2, csTmp);

			csTmp.Format("%d", struFaceMatchLog.struBlackListInfoLog.struBlackListInfo.dwRegisterID);
			g_pVcaFindMatch->m_listFindData.SetItemText(g_pVcaFindMatch->m_lFaceMatchLogNum, 3, csTmp);

			csTmp.Format("%d", struFaceMatchLog.struBlackListInfoLog.dwBlackListPicID);
			g_pVcaFindMatch->m_listFindData.SetItemText(g_pVcaFindMatch->m_lFaceMatchLogNum, 4, csTmp);

			g_pVcaFindMatch->m_lFaceMatchLogNum++;
		}
		else
		{
			if (bRet == NET_DVR_ISFINDING)
			{
				g_pVcaFindMatch->GetDlgItem(IDC_STATIC_SEARCH)->ShowWindow(SW_SHOW);
				g_pVcaFindMatch->GetDlgItem(IDC_STATIC_SEARCH)->SetWindowText("Searching......");
				Sleep(5);
				continue;
			}
			if ((bRet == NET_DVR_NOMOREFILE) || (bRet == NET_DVR_FILE_NOFIND))
			{
				g_StringLanType(szLan, "搜索", "search snap picture");
                g_pVcaFindMatch->GetDlgItem(IDC_BTN_FIND)->SetWindowText(szLan);
				
				g_pVcaFindMatch->GetDlgItem(IDC_STATIC_SEARCH)->ShowWindow(SW_HIDE);
				g_StringLanType(szLan, "搜索黑名单比对报警信息结束!", "Search Facematch Alarm Ending");
				AfxMessageBox(szLan);
				break;
			}
			else
			{
				g_StringLanType(szLan, "搜索", "Search snap picture");
                g_pVcaFindMatch->GetDlgItem(IDC_BTN_FIND)->SetWindowText(szLan);
				g_StringLanType(szLan, "由于服务器忙,或网络故障,搜索异常终止!",\
					"Since the server is busy, or network failure, search abnormal termination");
				AfxMessageBox(szLan);
				break;
			}
		}
	}
	CloseHandle(g_pVcaFindMatch->m_hFindThread);
	g_pVcaFindMatch->m_hFindThread = NULL;
	NET_DVR_FindFaceMatchAlarmClose(g_pVcaFindMatch->m_lFindHandle);
	
	return 0;
}


CDlgVcaFaceMatchLogSearch::CDlgVcaFaceMatchLogSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaFaceMatchLogSearch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaFaceMatchLogSearch)
	m_ctDateStart = 0;
	m_ctDateEnd = 0;
	m_ctTimeStart = 0;
	m_ctTimeEnd = 0;
	m_dwBlackListFaceID = 0;
	m_dwBlackListID = 0;
	m_dwSnapFaceID = 0;
	//}}AFX_DATA_INIT
	m_lServerID = -1;
    m_lChannel  = -1;
    m_iDevIndex = -1;
	m_lFindHandle = -1;
	m_hFindThread = NULL;
	m_lFaceMatchLogNum = 0;
}


void CDlgVcaFaceMatchLogSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaFaceMatchLogSearch)
	DDX_Control(pDX, IDC_LIST_FIND_DATA, m_listFindData);
	DDX_DateTimeCtrl(pDX, IDC_DATE_START, m_ctDateStart);
	DDX_DateTimeCtrl(pDX, IDC_DATE_END, m_ctDateEnd);
	DDX_DateTimeCtrl(pDX, IDC_TIME_START, m_ctTimeStart);
	DDX_DateTimeCtrl(pDX, IDC_TIME_END, m_ctTimeEnd);
	DDX_Text(pDX, IDC_EDIT_BLACKLIST_FACE_ID, m_dwBlackListFaceID);
	DDX_Text(pDX, IDC_EDIT_BLACKLIST_ID, m_dwBlackListID);
	DDX_Text(pDX, IDC_EDIT_SNAP_FACE_ID, m_dwSnapFaceID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaFaceMatchLogSearch, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaFaceMatchLogSearch)
	ON_BN_CLICKED(IDC_BTN_FIND, OnBtnFind)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_GET_FACEMATCH_PIC, OnBtnGetFacematchPic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaFaceMatchLogSearch message handlers
BOOL CDlgVcaFaceMatchLogSearch::OnInitDialog()
{
	CDialog::OnInitDialog();
	g_pVcaFindMatch = this;
	
	m_listFindData.SetExtendedStyle(m_listFindData.GetExtendedStyle()|LVS_EX_FULLROWSELECT);
	
	char szLan[128] = {0};
	g_StringLanType(szLan, "序号", "NO.");
	m_listFindData.InsertColumn(0, szLan,LVCFMT_LEFT,50,-1);
	g_StringLanType(szLan, "抓拍时间", "Snap Time");
	m_listFindData.InsertColumn(1, szLan,LVCFMT_LEFT,100,-1);
	g_StringLanType(szLan, "抓拍图片ID", "Face Pic ID");
	m_listFindData.InsertColumn(2, szLan, LVCFMT_LEFT, 120, -1);	
	g_StringLanType(szLan, "黑名单ID", "Blacklist ID");
	m_listFindData.InsertColumn(3, szLan, LVCFMT_LEFT, 120, -1);
	g_StringLanType(szLan, "黑名单图片ID", "Blacklist Pic ID");
	m_listFindData.InsertColumn(4, szLan, LVCFMT_LEFT, 120, -1);
	
	CTime timeCur = CTime::GetCurrentTime();
	CTime timeStart(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),0,0,0);
	CTime timeStop(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),23,59,59);
	m_ctDateStart = timeStart;
	m_ctTimeStart = timeStart;
	m_ctDateEnd = timeStop;
	m_ctTimeEnd = timeStop;
	
	UpdateData(FALSE);
	return TRUE;
}

void CDlgVcaFaceMatchLogSearch::OnBtnFind() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	
    NET_VCA_FIND_PICTURECOND struFindCond = {0};
	struFindCond.struStartTime.dwYear = (WORD)m_ctDateStart.GetYear();
	struFindCond.struStartTime.dwMonth = (WORD)m_ctDateStart.GetMonth();
	struFindCond.struStartTime.dwDay = (WORD)m_ctDateStart.GetDay();
	struFindCond.struStartTime.dwHour = (char)m_ctTimeStart.GetHour();
	struFindCond.struStartTime.dwMinute = (char)m_ctTimeStart.GetMinute();
	struFindCond.struStartTime.dwSecond = (char)m_ctTimeStart.GetSecond();
	struFindCond.struStopTime.dwYear = (WORD)m_ctDateEnd.GetYear();
	struFindCond.struStopTime.dwMonth = (WORD)m_ctDateEnd.GetMonth();
	struFindCond.struStopTime.dwDay = (WORD)m_ctDateEnd.GetDay();
	struFindCond.struStopTime.dwHour = (char)m_ctTimeEnd.GetHour();
	struFindCond.struStopTime.dwMinute = (char)m_ctTimeEnd.GetMinute();
	struFindCond.struStopTime.dwSecond = (char)m_ctTimeEnd.GetSecond();
	struFindCond.lChannel = m_lChannel;
	
	m_lFindHandle = NET_DVR_FindFaceMatchAlarm(m_lServerID, &struFindCond);
	if (m_lFindHandle < 0)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_FindFaceMatchAlarm");
		
		g_StringLanType(szLan, "搜索黑名单比对报警信息失败", "Search FaceMatch Alarm failed");
		AfxMessageBox(szLan);
        return;
	}
	else
	{
// 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_FindFaceMatchAlarm");
// 		
// 		g_StringLanType(szLan, "搜索黑名单比对报警信息成功", "Search FaceMatch Alarm succ");
// 		AfxMessageBox(szLan);
	}
	
	m_lFaceMatchLogNum = 0;
	m_listFindData.DeleteAllItems();
	DWORD dwThreadId = 0;
	if (m_hFindThread == NULL)
	{
		m_hFindThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetFindFaceMatchLogThread), this, 0, &dwThreadId);
	}
	
	if (m_hFindThread  == NULL)
	{
		g_StringLanType(szLan, "打开线程失败", "Open thread failed");
		AfxMessageBox(szLan);
		return;
    }
	
	g_StringLanType(szLan, "停止搜索", "Stop Searching");
	GetDlgItem(IDC_BTN_FIND)->SetWindowText(szLan);
}

void CDlgVcaFaceMatchLogSearch::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	if (m_hFindThread != NULL)
	{
		TerminateThread(m_hFindThread, 0);
		CloseHandle(m_hFindThread);
		m_hFindThread = NULL;
		NET_DVR_FindFaceMatchAlarmClose(m_lFindHandle);
	}
	CDialog::OnCancel();
}

void CDlgVcaFaceMatchLogSearch::OnBtnGetFacematchPic() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	char cFilename[256] = {0};
	HANDLE hFile;
	DWORD dwReturn;
	NET_VCA_FACEMATCH_PICCOND struFindCond = {0};
	struFindCond.dwSize = sizeof(struFindCond);
	struFindCond.dwSnapFaceID = m_dwSnapFaceID;
	struFindCond.dwBlackListID = m_dwBlackListID;
	struFindCond.dwBlackListFaceID = m_dwBlackListFaceID;

	NET_VCA_FACEMATCH_PICTURE struFindRet = {0};
	struFindRet.pSnapFace = new BYTE[1024*1024];
	memset(struFindRet.pSnapFace, 0, 1024*1024);
	struFindRet.pBlackListFace = new BYTE[1024*1024];
    memset(struFindRet.pBlackListFace, 0, 1024*1024);
	if (!NET_DVR_GetFaceMatchPic(m_lServerID, &struFindCond, &struFindRet))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetFaceMatchPic");
		
		g_StringLanType(szLan, "下载比对图片失败", "Get Match Picture failed");
		AfxMessageBox(szLan);
        return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetFaceMatchPic");
		
		g_StringLanType(szLan, "下载比对图片成功", "Get Match Picture succ");
		AfxMessageBox(szLan);
	}

	if (struFindRet.dwSnapFaceLen > 0)
	{
		SYSTEMTIME t;
		GetLocalTime(&t);
		char chTime[128];
		sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds/*struSnapPicData.struSnapTime.dwYear,struSnapPicData.struSnapTime.dwMonth,struSnapPicData.struSnapTime.dwDay,struSnapPicData.struSnapTime.dwHour,struSnapPicData.struSnapTime.dwMinute,struSnapPicData.struSnapTime.dwSecond*/);
		
		sprintf(cFilename, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[m_iDevIndex].chDeviceIP);
		if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
		{
			CreateDirectory(cFilename, NULL);
		}
		
		sprintf(cFilename, "%s\\MatchAlarmLog_S[%s][%d].jpg",cFilename, chTime, struFindCond.dwSnapFaceID);
		hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return;
		}
		WriteFile(hFile, struFindRet.pSnapFace, struFindRet.dwSnapFaceLen, &dwReturn, NULL);
		CloseHandle(hFile);
		hFile = NULL;
	}

	if (struFindRet.dwBlackListFaceLen > 0)
	{	
		SYSTEMTIME t;
		GetLocalTime(&t);
		char chTime[128];
		sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds/*struSnapPicData.struSnapTime.dwYear,struSnapPicData.struSnapTime.dwMonth,struSnapPicData.struSnapTime.dwDay,struSnapPicData.struSnapTime.dwHour,struSnapPicData.struSnapTime.dwMinute,struSnapPicData.struSnapTime.dwSecond*/);
		
		sprintf(cFilename, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[m_iDevIndex].chDeviceIP);
		if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
		{
			CreateDirectory(cFilename, NULL);
		}
		
		sprintf(cFilename, "%s\\MatchAlarmLog_B[%s][%d].jpg",cFilename, chTime, struFindCond.dwBlackListFaceID);
		hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return;
		}
		WriteFile(hFile, struFindRet.pBlackListFace, struFindRet.dwBlackListFaceLen, &dwReturn, NULL);
		CloseHandle(hFile);
		hFile = NULL;
	}
}
