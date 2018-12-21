// DlgVcaSnapDatabase.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaSnapDatabase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSnapDatabase dialog
CDlgVcaSnapDatabase *g_pVcaSnapDataBase = NULL;

void CALLBACK FunInquireSnapDBCallBack(LONG lHandle, DWORD dwType, DWORD dwResultNum, BYTE* pBuffer, DWORD dwBufSize,void *pUser)
{
	DWORD dwSearchType = 0;
	char *pRecordMsg = new char[dwBufSize];
	if (pRecordMsg == NULL)
	{
		return;
	}
	memcpy(pRecordMsg, pBuffer, dwBufSize);
	if (g_pVcaSnapDataBase->m_bInquiring)
	{
		dwSearchType = INQUIRE_SNAP_DATABASE;
		((LPNET_VCA_INQUIRE_SNAPRECORD_RESULT)pRecordMsg)->pFacePic = new BYTE[((LPNET_VCA_INQUIRE_SNAPRECORD_RESULT)pRecordMsg)->dwFacePicLen];
		memset(((LPNET_VCA_INQUIRE_SNAPRECORD_RESULT)pRecordMsg)->pFacePic, 0, ((LPNET_VCA_INQUIRE_SNAPRECORD_RESULT)pRecordMsg)->dwFacePicLen);
		memcpy(((LPNET_VCA_INQUIRE_SNAPRECORD_RESULT)pRecordMsg)->pFacePic, ((LPNET_VCA_INQUIRE_SNAPRECORD_RESULT)pBuffer)->pFacePic, ((LPNET_VCA_INQUIRE_SNAPRECORD_RESULT)pRecordMsg)->dwFacePicLen);
	}
	
    ::PostMessage(g_pVcaSnapDataBase->m_hWnd, WM_PROC_SNAPCALLBACK, (DWORD)dwSearchType, (LPARAM)pRecordMsg);
}

void CALLBACK FunSearchSnapDBCallBack(LONG lHandle, DWORD dwType, DWORD dwResultNum, BYTE* pBuffer, DWORD dwBufSize,void *pUser)
{
	DWORD dwSearchType = 0;
	char *pRecordMsg = new char[dwBufSize];
	if (pRecordMsg == NULL)
	{
		return;
	}
	memcpy(pRecordMsg, pBuffer, dwBufSize);
	if (g_pVcaSnapDataBase->m_bSearching)
	{
		dwSearchType = SEARCH_SNAP_DATABASE;
		((LPNET_VCA_SEARCH_SNAPRECORD_RESULT)pRecordMsg)->pFacePic = new BYTE[((LPNET_VCA_SEARCH_SNAPRECORD_RESULT)pRecordMsg)->dwFacePicLen];
		memset(((LPNET_VCA_SEARCH_SNAPRECORD_RESULT)pRecordMsg)->pFacePic, 0, ((LPNET_VCA_SEARCH_SNAPRECORD_RESULT)pRecordMsg)->dwFacePicLen);
		memcpy(((LPNET_VCA_SEARCH_SNAPRECORD_RESULT)pRecordMsg)->pFacePic, ((LPNET_VCA_SEARCH_SNAPRECORD_RESULT)pBuffer)->pFacePic, ((LPNET_VCA_SEARCH_SNAPRECORD_RESULT)pRecordMsg)->dwFacePicLen);
	}
	
    ::PostMessage(g_pVcaSnapDataBase->m_hWnd, WM_PROC_SNAPCALLBACK, (DWORD)dwSearchType, (LPARAM)pRecordMsg);
}


CDlgVcaSnapDatabase::CDlgVcaSnapDatabase(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaSnapDatabase::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaSnapDatabase)
	m_ctStartDate = 0;
	m_ctStopDate = 0;
	m_dwDatabaseID = 0;
	m_csMaxBirthdate = _T("");
	m_csMinBirthdate = _T("");
	m_dwRecordID = 0;
	m_dwSearchMaxNum = 0;
	m_dwThreshold = 0;
	m_ctStartTime = 0;
	m_ctStopTime = 0;
	m_iChannel = 0;
	m_dwTotalRecordNum = 0;
	m_bChkAdvanceEn = FALSE;
	m_dwAdvanceDBId = 0;
	m_dwAdvanceRecordId = 0;
	//}}AFX_DATA_INIT
	m_lServerID = -1;
	m_bInquiring = FALSE;
	m_bSearching = FALSE;
	m_lRecordNum = 0;
	m_lTotalNum=0;
	m_lHandle = -1;
	memset(&m_struInquireCond, 0, sizeof(m_struInquireCond));
	memset(&m_struSearchCond, 0, sizeof(m_struSearchCond));
	memset(&m_struDeleteRecord, 0, sizeof(m_struDeleteRecord));
	memset(&m_struRecordResult, 0, sizeof(m_struRecordResult));
}


void CDlgVcaSnapDatabase::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaSnapDatabase)
	DDX_Control(pDX, IDC_COMBO_ADVANCE_DB_TYPE, m_comboAdvanceDBType);
	DDX_Control(pDX, IDC_LIST_DATABASE, m_listDataBase);
	DDX_Control(pDX, IDC_COMBO_SEX, m_comboSex);
	DDX_DateTimeCtrl(pDX, IDC_DATE_START, m_ctStartDate);
	DDX_DateTimeCtrl(pDX, IDC_DATE_STOP, m_ctStopDate);
	DDX_Text(pDX, IDC_EDIT_DATABASE_ID, m_dwDatabaseID);
	DDX_Text(pDX, IDC_EDIT_MAX_BIRTHDATE, m_csMaxBirthdate);
	DDX_Text(pDX, IDC_EDIT_MIN_BIRTHDATE, m_csMinBirthdate);
	DDX_Text(pDX, IDC_EDIT_RECORD_ID, m_dwRecordID);
	DDX_Text(pDX, IDC_EDIT_SEARCH_MAXNUM, m_dwSearchMaxNum);
	DDX_Text(pDX, IDC_EDIT_THRESHOLD, m_dwThreshold);
	DDX_DateTimeCtrl(pDX, IDC_TIME_START, m_ctStartTime);
	DDX_DateTimeCtrl(pDX, IDC_TIME_STOP, m_ctStopTime);
	DDX_Text(pDX, IDC_EDIT_CHANNEL, m_iChannel);
	DDX_Text(pDX, IDC_EDIT_TOTAL_RECORD_NUM, m_dwTotalRecordNum);
	DDX_Check(pDX, IDC_CHK_ADVANCE_SEARCH, m_bChkAdvanceEn);
	DDX_Text(pDX, IDC_EDIT_ADVANCE_DATABASE_ID, m_dwAdvanceDBId);
	DDX_Text(pDX, IDC_EDIT_ADVANCE_RECORD_ID, m_dwAdvanceRecordId);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaSnapDatabase, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaSnapDatabase)
	ON_BN_CLICKED(IDC_BTN_INQUIRE_SNAPDB, OnBtnInquireSnapdb)
	ON_BN_CLICKED(IDC_BTN_STOP_INQUIRE_SNAPDB, OnBtnStopInquireSnapdb)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_START_SEARCH_SNAPDB, OnBtnStartSearchSnapdb)
	ON_BN_CLICKED(IDC_BTN_STOP_SEARCH, OnBtnStopSearch)
	ON_BN_CLICKED(IDC_BTN_DELETE_SINGLE, OnBtnDeleteSingle)
	ON_BN_CLICKED(IDC_BTN_DELETE_BATCH, OnBtnDeleteBatch)
	ON_BN_CLICKED(IDC_BTN_GET_FACE_PIC, OnBtnGetFacePic)
	ON_MESSAGE(WM_PROC_SNAPCALLBACK, OnWMProcFaceCallback)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSnapDatabase message handlers
BOOL CDlgVcaSnapDatabase::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_comboSex.SetCurSel(0);
	
	g_pVcaSnapDataBase = this;
	
	char szLan[128] = {0};

	CTime timeCur = CTime::GetCurrentTime();
	CTime timeStart(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),0,0,0);
	CTime timeStop(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),23,59,59);
	m_ctStartDate = timeStart;
	m_ctStartTime = timeStart;
	m_ctStopDate = timeStop;
	m_ctStopTime = timeStop;
    
    m_listDataBase.SetExtendedStyle(m_listDataBase.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
    g_StringLanType(szLan, "序号", "NO.");
    m_listDataBase.InsertColumn(0, szLan, LVCFMT_RIGHT, 60, -1);
	g_StringLanType(szLan, "记录ID", "Record ID");
	m_listDataBase.InsertColumn(1, szLan, LVCFMT_LEFT, 80, -1);
	g_StringLanType(szLan, "抓拍时间", "Snap time");
	m_listDataBase.InsertColumn(2, szLan, LVCFMT_LEFT, 100, -1);
	g_StringLanType(szLan, "性别", "Sex");
    m_listDataBase.InsertColumn(3, szLan, LVCFMT_LEFT,60, -1);
    
	g_StringLanType(szLan, "年龄区间(低)", "Age low");
	m_listDataBase.InsertColumn(4, szLan, LVCFMT_LEFT, 200, -1);
	g_StringLanType(szLan, "年龄区间(高)", "Age high");
	m_listDataBase.InsertColumn(5, szLan, LVCFMT_LEFT, 200, -1);
	g_StringLanType(szLan, "相似度", "Similarity");
	m_listDataBase.InsertColumn(6, szLan, LVCFMT_LEFT, 200, -1);

	UpdateData(FALSE);
	
	return TRUE;
}

void CDlgVcaSnapDatabase::OnBtnInquireSnapdb() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	
	void *pUser = NULL;

	m_struInquireCond.dwChannel = m_iChannel;
	m_struInquireCond.bySex = m_comboSex.GetCurSel();
	memcpy(m_struInquireCond.byStartBirthDate, m_csMinBirthdate, MAX_HUMAN_BIRTHDATE_LEN);
	memcpy(m_struInquireCond.byEndBirthDate, m_csMaxBirthdate, MAX_HUMAN_BIRTHDATE_LEN);
	m_struInquireCond.struStartTime.dwYear = (WORD)m_ctStartDate.GetYear();
	m_struInquireCond.struStartTime.dwMonth = (WORD)m_ctStartDate.GetMonth();
	m_struInquireCond.struStartTime.dwDay = (WORD)m_ctStartDate.GetDay();
	m_struInquireCond.struStartTime.dwHour = (char)m_ctStartTime.GetHour();
	m_struInquireCond.struStartTime.dwMinute = (char)m_ctStartTime.GetMinute();
	m_struInquireCond.struStartTime.dwSecond = (char)m_ctStartTime.GetSecond();
	m_struInquireCond.struStopTime.dwYear = (WORD)m_ctStopDate.GetYear();
	m_struInquireCond.struStopTime.dwMonth = (WORD)m_ctStopDate.GetMonth();
	m_struInquireCond.struStopTime.dwDay = (WORD)m_ctStopDate.GetDay();
	m_struInquireCond.struStopTime.dwHour = (char)m_ctStopTime.GetHour();
	m_struInquireCond.struStopTime.dwMinute = (char)m_ctStopTime.GetMinute();
	m_struInquireCond.struStopTime.dwSecond = (char)m_ctStopTime.GetSecond();
	m_lHandle = NET_DVR_InquireSnapDBRecord(m_lServerID, m_dwDatabaseID, &m_struInquireCond, FunInquireSnapDBCallBack, pUser);
	if (m_lHandle < 0)
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_InquireSnapDBRecord m_dwDatabaseID[%d] ",m_dwDatabaseID);
        g_StringLanType(szLan, "查询抓拍数据库失败", "Fail to inquire record");
        AfxMessageBox(szLan);
		return;
    }
    else
    {
		m_lRecordNum = 0;
		m_lTotalNum=0;
		m_listDataBase.DeleteAllItems();
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_InquireSnapDBRecord m_dwDatabaseID[%d] ",m_dwDatabaseID);
		m_bInquiring = TRUE;
		SetTimer(SNAP_DATABASE_INQUIRE, 200, NULL);
//		g_StringLanType(szLan, "查询抓拍数据库成功", "Succ to inquire record");
//        AfxMessageBox(szLan);
    }
}

void CDlgVcaSnapDatabase::OnBtnStopInquireSnapdb() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	
	m_bInquiring = FALSE;
	if (m_lHandle >= 0)
	{
		if (!NET_DVR_StopSearchDB(m_lHandle))
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopSearchDB m_lHandle[%d] ",m_lHandle);
			g_StringLanType(szLan, "停止抓拍数据库查询失败", "Fail to inquire");
			AfxMessageBox(szLan);
		}
		else
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopSearchDB m_lHandle[%d] ",m_lHandle);
			m_lHandle = -1;
//			g_StringLanType(szLan, "停止抓拍数据库查询成功", "Succ to inquire");
//			AfxMessageBox(szLan);
		}
	}
	m_dwTotalRecordNum = m_lTotalNum;
	UpdateData(FALSE);
}

#if (_MSC_VER >= 1500)	//vs2008
void CDlgVcaSnapDatabase::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgVcaSnapDatabase::OnTimer(UINT nIDEvent)
#endif
{
	// TODO: Add your message handler code here and/or call default
	DWORD dwState = 0;
	char szLan[128] = {0};
	
	switch (nIDEvent)
	{
	case SNAP_DATABASE_INQUIRE:
		if (m_bInquiring)
		{
            NET_DVR_GetInquireSnapDBProgress(m_lHandle, &dwState);
			if (dwState == 100)
			{
				m_bInquiring = FALSE;
				m_dwTotalRecordNum = m_lTotalNum;
				g_StringLanType(szLan, "查询结束", "Inquire complete");
				AfxMessageBox(szLan);
                if (!NET_DVR_StopSearchDB(m_lHandle))
				{
					g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopSearchDB m_lHandle[%d] ",m_lHandle);
					g_StringLanType(szLan, "停止查询失败", "Fail to inquire");
					AfxMessageBox(szLan);
				}
				else
				{
					g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopSearchDB m_lHandle[%d] ",m_lHandle);
//					g_StringLanType(szLan, "停止查询成功", "Succ to inquire");
//					AfxMessageBox(szLan);
					m_lHandle = -1;
				}
			}
		}
		
		if (m_bSearching)
		{
			NET_DVR_GetSearchSnapDBProgress(m_lSearchHandle, &dwState);
			if (dwState == 100)
			{
				m_bSearching = FALSE;
				m_dwTotalRecordNum = m_lTotalNum;
				g_StringLanType(szLan, "检索结束", "Search complete");
				AfxMessageBox(szLan);
                if (!NET_DVR_StopSearchDB(m_lSearchHandle))
				{
					g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopSearchDB m_lSearchHandle[%d] ",m_lSearchHandle);
					g_StringLanType(szLan, "停止检索失败", "Fail to search");
					AfxMessageBox(szLan);
				}
				else
				{
					g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopSearchDB m_lSearchHandle[%d] ",m_lSearchHandle);
//					g_StringLanType(szLan, "停止检索成功", "Succ to search");
//					AfxMessageBox(szLan);
					m_lSearchHandle = -1;
				}
			}
		}
		break;
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

void CDlgVcaSnapDatabase::OnDestroy() 
{
	KillTimer(SNAP_DATABASE_INQUIRE);
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CDlgVcaSnapDatabase::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	
	m_bInquiring = FALSE;
	m_bSearching = FALSE;
	
	if (m_lHandle > 0)
	{
		if (!NET_DVR_StopSearchDB(m_lHandle))
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopSearchDB m_lHandle[%d] ",m_lHandle);
			g_StringLanType(szLan, "停止查询失败", "Fail to inquire");
			AfxMessageBox(szLan);
		}
		else
		{
			m_lHandle = -1;
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopSearchDB m_lHandle[%d] ",m_lHandle);
//			g_StringLanType(szLan, "停止查询成功", "Succ to inquire");
//			AfxMessageBox(szLan);
		}
	}
	
	if (m_lSearchHandle > 0)
	{
        if (!NET_DVR_StopSearchDB(m_lSearchHandle))
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopSearchDB m_lSearchHandle[%d] ",m_lSearchHandle);
			g_StringLanType(szLan, "停止检索失败", "Fail to search");
			AfxMessageBox(szLan);
		}
		else
		{
			m_lSearchHandle = -1;
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopSearchDB m_lSearchHandle[%d] ",m_lSearchHandle);
//			g_StringLanType(szLan, "停止检索成功", "Succ to search");
//			AfxMessageBox(szLan);
		}
	}	
	CDialog::OnCancel();
}

void CDlgVcaSnapDatabase::OnBtnStartSearchSnapdb() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	
	void *pUser = NULL;
	m_struSearchCond.dwChannel = m_iChannel;
	m_struSearchCond.dwDataBaseID = m_dwDatabaseID;
	m_struSearchCond.dwMaxSearchNum = m_dwSearchMaxNum;
	m_struSearchCond.wThreshold = m_dwThreshold;

	m_struSearchCond.bySex = m_comboSex.GetCurSel();
	memcpy(m_struSearchCond.byStartBirthDate, m_csMinBirthdate, MAX_HUMAN_BIRTHDATE_LEN);
	memcpy(m_struSearchCond.byEndBirthDate, m_csMaxBirthdate, MAX_HUMAN_BIRTHDATE_LEN);
	m_struSearchCond.struStartTime.dwYear = (WORD)m_ctStartDate.GetYear();
	m_struSearchCond.struStartTime.dwMonth = (WORD)m_ctStartDate.GetMonth();
	m_struSearchCond.struStartTime.dwDay = (WORD)m_ctStartDate.GetDay();
	m_struSearchCond.struStartTime.dwHour = (char)m_ctStartTime.GetHour();
	m_struSearchCond.struStartTime.dwMinute = (char)m_ctStartTime.GetMinute();
	m_struSearchCond.struStartTime.dwSecond = (char)m_ctStartTime.GetSecond();
	m_struSearchCond.struStopTime.dwYear = (WORD)m_ctStopDate.GetYear();
	m_struSearchCond.struStopTime.dwMonth = (WORD)m_ctStopDate.GetMonth();
	m_struSearchCond.struStopTime.dwDay = (WORD)m_ctStopDate.GetDay();
	m_struSearchCond.struStopTime.dwHour = (char)m_ctStopTime.GetHour();
	m_struSearchCond.struStopTime.dwMinute = (char)m_ctStopTime.GetMinute();
	m_struSearchCond.struStopTime.dwSecond = (char)m_ctStopTime.GetSecond();

	if (m_bChkAdvanceEn)
	{
		m_struSearchCond.struSearchParam.dwSearchType = VCA_ADVANCE_SEARCH_DATABASE;
		m_struSearchCond.struSearchParam.uSearchCond.struAdvanceFind.dwDataBaseID = m_dwAdvanceDBId;
		m_struSearchCond.struSearchParam.uSearchCond.struAdvanceFind.dwDataBaseType = m_comboAdvanceDBType.GetCurSel()+1;
		m_struSearchCond.struSearchParam.uSearchCond.struAdvanceFind.dwFacePicID  = m_dwAdvanceRecordId;
	}
	else
	{
		m_struSearchCond.struSearchParam.dwSearchType = VCA_NORMAL_SEARCH_DATABASE;
		m_struSearchCond.struSearchParam.uSearchCond.struNormalFind.dwImageID = g_struFacePic[0].dwImageID;
		m_struSearchCond.struSearchParam.uSearchCond.struNormalFind.dwFaceScore = g_struFacePic[0].dwFaceScore;
		memcpy(&m_struSearchCond.struSearchParam.uSearchCond.struNormalFind.struVcaRect, &g_struFacePic[0].struVcaRect, sizeof(NET_VCA_RECT));
	}
		m_lSearchHandle = NET_DVR_SearchSnapDB(m_lServerID, &m_struSearchCond, FunSearchSnapDBCallBack, pUser);
	if (m_lSearchHandle < 0)
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SearchSnapDB m_dwDatabaseID[%d] ",m_dwDatabaseID);
        g_StringLanType(szLan, "检索失败", "Fail to search record");
        AfxMessageBox(szLan);
		return;
    }
    else
    {
		m_lRecordNum = 0;
		m_lTotalNum = 0;
		m_listDataBase.DeleteAllItems();
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SearchSnapDB m_dwDatabaseID[%d] ",m_dwDatabaseID);
		m_bSearching = TRUE;
		SetTimer(FACE_DATABASE_INQUIRE, 200, NULL);
//		g_StringLanType(szLan, "检索成功", "Succ to search record");
//        AfxMessageBox(szLan);
    }
}

void CDlgVcaSnapDatabase::OnBtnStopSearch() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	m_bSearching = FALSE;
	if (m_lSearchHandle >= 0)
	{
        if (!NET_DVR_StopSearchDB(m_lSearchHandle))
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopSearchDB m_lSearchHandle[%d] ",m_lSearchHandle);
			g_StringLanType(szLan, "停止检索失败", "Fail to search");
			AfxMessageBox(szLan);
		}
		else
		{
			m_lSearchHandle = -1;
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopSearchDB m_lSearchHandle[%d] ",m_lSearchHandle);
//			g_StringLanType(szLan, "停止检索成功", "Succ to search");
//			AfxMessageBox(szLan);
		}
	}
	m_dwTotalRecordNum = m_lTotalNum;
	UpdateData(FALSE);
}

void CDlgVcaSnapDatabase::OnBtnDeleteSingle() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	
	m_struDeleteRecord.dwDeleteType = DELETE_RECORD_SINGLE;
	m_struDeleteRecord.uDeleteCond.dwRecordID = m_dwRecordID;
	if (!NET_DVR_DeleteSnapDBRecord(m_lServerID, m_dwDatabaseID, &m_struDeleteRecord))
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_DeleteSnapDBRecord m_dwDatabaseID[%d] ",m_dwDatabaseID);
        g_StringLanType(szLan, "删除记录失败", "Fail to delete record");
        AfxMessageBox(szLan);
    }
    else
    {
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DeleteSnapDBRecord m_dwDatabaseID[%d] ",m_dwDatabaseID);
//		g_StringLanType(szLan, "删除记录成功", "Succ to delete record");
//        AfxMessageBox(szLan);
    }
}

void CDlgVcaSnapDatabase::OnBtnDeleteBatch() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	
	m_struDeleteRecord.dwDeleteType = DELETE_RECORD_BATCH;
	m_struDeleteRecord.uDeleteCond.struAttribute.dwChannel = m_iChannel;
	m_struDeleteRecord.uDeleteCond.struAttribute.bySex = m_comboSex.GetCurSel();
	memcpy(m_struDeleteRecord.uDeleteCond.struAttribute.byStartBirthDate, m_csMinBirthdate, MAX_HUMAN_BIRTHDATE_LEN);
	memcpy(m_struDeleteRecord.uDeleteCond.struAttribute.byEndBirthDate, m_csMaxBirthdate, MAX_HUMAN_BIRTHDATE_LEN);
	m_struDeleteRecord.uDeleteCond.struAttribute.struStartTime.dwYear = (WORD)m_ctStartDate.GetYear();
	m_struDeleteRecord.uDeleteCond.struAttribute.struStartTime.dwMonth = (WORD)m_ctStartDate.GetMonth();
	m_struDeleteRecord.uDeleteCond.struAttribute.struStartTime.dwDay = (WORD)m_ctStartDate.GetDay();
	m_struDeleteRecord.uDeleteCond.struAttribute.struStartTime.dwHour = (char)m_ctStartTime.GetHour();
	m_struDeleteRecord.uDeleteCond.struAttribute.struStartTime.dwMinute = (char)m_ctStartTime.GetMinute();
	m_struDeleteRecord.uDeleteCond.struAttribute.struStartTime.dwSecond = (char)m_ctStartTime.GetSecond();
	m_struDeleteRecord.uDeleteCond.struAttribute.struStopTime.dwYear = (WORD)m_ctStopDate.GetYear();
	m_struDeleteRecord.uDeleteCond.struAttribute.struStopTime.dwMonth = (WORD)m_ctStopDate.GetMonth();
	m_struDeleteRecord.uDeleteCond.struAttribute.struStopTime.dwDay = (WORD)m_ctStopDate.GetDay();
	m_struDeleteRecord.uDeleteCond.struAttribute.struStopTime.dwHour = (char)m_ctStopTime.GetHour();
	m_struDeleteRecord.uDeleteCond.struAttribute.struStopTime.dwMinute = (char)m_ctStopTime.GetMinute();
	m_struDeleteRecord.uDeleteCond.struAttribute.struStopTime.dwSecond = (char)m_ctStopTime.GetSecond();
	if (!NET_DVR_DeleteSnapDBRecord(m_lServerID, m_dwDatabaseID, &m_struDeleteRecord))
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_DeleteSnapDBRecord m_dwDatabaseID[%d] ",m_dwDatabaseID);
        g_StringLanType(szLan, "删除记录失败", "Fail to delete record");
        AfxMessageBox(szLan);
    }
    else
    {
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DeleteFaceDBRecord m_dwDatabaseID[%d] ",m_dwDatabaseID);
//		g_StringLanType(szLan, "删除记录成功", "Succ to delete record");
 //       AfxMessageBox(szLan);
    }
}

void CDlgVcaSnapDatabase::OnBtnGetFacePic() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CRect struRect; 
	char szLan[128] = {0};
	NET_VCA_FIND_MATCHPIC_COND struCond = {0};
	struCond.dwSize = sizeof(struCond);
	struCond.dwDataBaseType = DATABASE_SNAP;
	struCond.dwDataBaseID = m_dwDatabaseID;
	struCond.dwRecordID = m_dwRecordID;
	
	NET_VCA_FIND_MATCHPIC_RESULT struRecvBuf = {0};
	struRecvBuf.pPicBuffer = new BYTE[2*1024*1024];
	if (struRecvBuf.pPicBuffer == NULL)
	{
		return;
	}
	memset(struRecvBuf.pPicBuffer, 0, 2*1024*1024);
	
	if (!NET_DVR_FindMatchPicture(m_lServerID, &struCond, &struRecvBuf))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_FindMatchPicture");
		g_StringLanType(szLan, "按条件查找背景图失败", "Fail to find match picture");
        AfxMessageBox(szLan);
		delete []struRecvBuf.pPicBuffer;
		struRecvBuf.pPicBuffer = NULL;
		return;
	}
	else
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_FindMatchPicture");
	}
	if (struRecvBuf.dwPicLen > 0)
    {       
        char cFilename[256] = {0};
        HANDLE hFile;
        DWORD dwReturn;
        
        SYSTEMTIME t;
        GetLocalTime(&t);
        char chTime[128];
        sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
        
        sprintf(cFilename, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[m_iDevIndex].chDeviceIP);
        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cFilename, NULL);
        }
        
        sprintf(cFilename, "%s\\LocalTime[SnapDB][%s].jpg",cFilename, chTime);
        hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        WriteFile(hFile, struRecvBuf.pPicBuffer, struRecvBuf.dwPicLen, &dwReturn, NULL);
        CloseHandle(hFile);
        hFile = NULL;
	}
	
	if (struRecvBuf.pPicBuffer != NULL)
	{
		delete []struRecvBuf.pPicBuffer;
		struRecvBuf.pPicBuffer = NULL;
	}
	UpdateData(FALSE);
}

LRESULT CDlgVcaSnapDatabase::OnWMProcFaceCallback(WPARAM wParam, LPARAM lParam)
{
	DWORD dwType = (DWORD)(wParam);
	char *pRecordInfo = (char *)(lParam);		
	
	char szLan[128] ={0};
	switch (dwType)
	{
	case INQUIRE_SNAP_DATABASE:
		ProcInquireSnapCallback(wParam, lParam);
		break;
	case SEARCH_SNAP_DATABASE:
		ProcSearchSnapCallback(wParam, lParam);
		break;
	default:
		break;
	}

	if (pRecordInfo != NULL)
	{
		delete[] pRecordInfo;
		pRecordInfo = NULL;
	}

	return NULL;
}

void CDlgVcaSnapDatabase::ProcInquireSnapCallback(WPARAM wParam, LPARAM lParam)
{
	CString csTmp;
	char szLan[128] = {0};
    char *pDataInfo = (char *)(lParam);
    
	NET_VCA_INQUIRE_SNAPRECORD_RESULT struInquireResult = {0};
	memcpy(&struInquireResult, /*(NET_VCA_INQUIRE_SNAPRECORD_RESULT*)*/pDataInfo, sizeof(NET_VCA_INQUIRE_SNAPRECORD_RESULT));

	g_pVcaSnapDataBase->m_lTotalNum++;
	if (g_pVcaSnapDataBase->m_lRecordNum <= 2000)
	{
		csTmp.Format("%d", g_pVcaSnapDataBase->m_lTotalNum);
		g_pVcaSnapDataBase->m_listDataBase.InsertItem(g_pVcaSnapDataBase->m_lRecordNum, csTmp,0);
		
		csTmp.Format("%d", struInquireResult.dwRecordID);
		g_pVcaSnapDataBase->m_listDataBase.SetItemText(g_pVcaSnapDataBase->m_lRecordNum, 1, csTmp);
		
		csTmp.Format("[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d]", struInquireResult.struSnapTime.dwYear, struInquireResult.struSnapTime.dwMonth, struInquireResult.struSnapTime.dwDay, struInquireResult.struSnapTime.dwHour,
			struInquireResult.struSnapTime.dwMinute, struInquireResult.struSnapTime.dwSecond);
		g_pVcaSnapDataBase->m_listDataBase.SetItemText(g_pVcaSnapDataBase->m_lRecordNum, 2, csTmp);
		
		switch (struInquireResult.bySex)
		{
		case 0:
			g_StringLanType(szLan, "无", "No");
			break;
		case 1:
			g_StringLanType(szLan, "男", "Man");
			break;
		case 2:
			g_StringLanType(szLan, "女", "Woman");
			break;
		default:
			g_StringLanType(szLan, "未知", "Unknow");
			break;
		}
		csTmp.Format("%s", szLan);
		g_pVcaSnapDataBase->m_listDataBase.SetItemText(g_pVcaSnapDataBase->m_lRecordNum, 3, csTmp);
		
		csTmp.Format("%s", struInquireResult.byStartBirthDate);
		g_pVcaSnapDataBase->m_listDataBase.SetItemText(g_pVcaSnapDataBase->m_lRecordNum, 4, csTmp);
		
		csTmp.Format("%s", struInquireResult.byEndBirthDate);
		g_pVcaSnapDataBase->m_listDataBase.SetItemText(g_pVcaSnapDataBase->m_lRecordNum, 5, csTmp);
		
		g_pVcaSnapDataBase->m_lRecordNum++;

		if (struInquireResult.dwFacePicLen > 0 && struInquireResult.pFacePic != NULL)
		{        
			char cFilename[256] = {0};
			HANDLE hFile;
			DWORD dwReturn;			
			SYSTEMTIME t;
			GetLocalTime(&t);
			char chTime[128];
			sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
						
			sprintf(cFilename, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[g_pVcaSnapDataBase->m_iDevIndex].chDeviceIP);
			if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
			{
				CreateDirectory(cFilename, NULL);
			}
 				
			sprintf(cFilename, "%s\\INQUIRE_SNAPDATA[%s]_database[%d]_record[%d].jpg",cFilename, chTime, struInquireResult.dwDataBaseID,struInquireResult.dwRecordID);
			hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile == INVALID_HANDLE_VALUE)
			{
				return;
			}
			WriteFile(hFile, struInquireResult.pFacePic, struInquireResult.dwFacePicLen, &dwReturn, NULL);
			CloseHandle(hFile);
			hFile = NULL;
		}
	}

	if (struInquireResult.pFacePic != NULL)
	{
		delete []struInquireResult.pFacePic;
		struInquireResult.pFacePic = NULL;
	}
}

void CDlgVcaSnapDatabase::ProcSearchSnapCallback(WPARAM wParam, LPARAM lParam)
{
	CString csTmp;
	char szLan[128] = {0};
	char *pDataInfo = (char *)(lParam);
	g_pVcaSnapDataBase->m_lTotalNum++;
	
	NET_VCA_SEARCH_SNAPRECORD_RESULT struSearchResult = {0};
	memcpy(&struSearchResult, pDataInfo, sizeof(NET_VCA_SEARCH_SNAPRECORD_RESULT));
	if (g_pVcaSnapDataBase->m_lRecordNum <= 2000)
	{
		csTmp.Format("%d", g_pVcaSnapDataBase->m_lTotalNum);
		g_pVcaSnapDataBase->m_listDataBase.InsertItem(g_pVcaSnapDataBase->m_lRecordNum, csTmp,0);
		
		csTmp.Format("%d", struSearchResult.dwRecordID);
		g_pVcaSnapDataBase->m_listDataBase.SetItemText(g_pVcaSnapDataBase->m_lRecordNum, 1, csTmp);
		
		csTmp.Format("[%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d]", struSearchResult.struSnapTime.dwYear, struSearchResult.struSnapTime.dwMonth, struSearchResult.struSnapTime.dwDay, struSearchResult.struSnapTime.dwHour,
			struSearchResult.struSnapTime.dwMinute, struSearchResult.struSnapTime.dwSecond);
		g_pVcaSnapDataBase->m_listDataBase.SetItemText(g_pVcaSnapDataBase->m_lRecordNum, 2, csTmp);
		
		switch (struSearchResult.bySex)
		{
		case 0:
			g_StringLanType(szLan, "无", "No");
			break;
		case 1:
			g_StringLanType(szLan, "男", "Man");
			break;
		case 2:
			g_StringLanType(szLan, "女", "Woman");
			break;
		default:
			g_StringLanType(szLan, "未知", "Unknow");
			break;
		}
		csTmp.Format("%s", szLan);
		g_pVcaSnapDataBase->m_listDataBase.SetItemText(g_pVcaSnapDataBase->m_lRecordNum, 3, csTmp);
		
		csTmp.Format("%s", struSearchResult.byStartBirthDate);
		g_pVcaSnapDataBase->m_listDataBase.SetItemText(g_pVcaSnapDataBase->m_lRecordNum, 4, csTmp);
		
		csTmp.Format("%d", struSearchResult.byEndBirthDate);
		g_pVcaSnapDataBase->m_listDataBase.SetItemText(g_pVcaSnapDataBase->m_lRecordNum, 5, csTmp);
		
		csTmp.Format("%f", struSearchResult.fSimilarity);
		g_pVcaSnapDataBase->m_listDataBase.SetItemText(g_pVcaSnapDataBase->m_lRecordNum, 6, csTmp);
		
		if (g_pVcaSnapDataBase->m_lRecordNum == 10000)
		{
			g_pVcaSnapDataBase->m_lRecordNum = 0;
		}
		else
		{
			g_pVcaSnapDataBase->m_lRecordNum++;
		}
		
		if (struSearchResult.dwFacePicLen > 0 && struSearchResult.pFacePic != NULL)
		{        
			char cFilename[256] = {0};
			HANDLE hFile;
			DWORD dwReturn;
        
			SYSTEMTIME t;
			GetLocalTime(&t);
			char chTime[128];
			sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
        
			sprintf(cFilename, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[g_pVcaSnapDataBase->m_iDevIndex].chDeviceIP);
			if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
			{
				CreateDirectory(cFilename, NULL);
			}
        
			sprintf(cFilename, "%s\\SEARCH_SNAPDATA[%s]_database[%d]_record[%d].jpg",cFilename, chTime, struSearchResult.dwDataBaseID,struSearchResult.dwRecordID);
			hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile == INVALID_HANDLE_VALUE)
			{
				return;
			}
			WriteFile(hFile, struSearchResult.pFacePic, struSearchResult.dwFacePicLen, &dwReturn, NULL);
			CloseHandle(hFile);
			hFile = NULL;
		}
	}
	
	if (struSearchResult.pFacePic != NULL)
	{
		delete []struSearchResult.pFacePic;
		struSearchResult.pFacePic = NULL;
	}
}
