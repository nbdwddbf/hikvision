// DlgPDCSearch.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPDCSearch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPDCSearch dialog
CDlgPDCSearch * g_pPDCInfoSearch = NULL;
UINT GetPDCInfohread(LPVOID pParam)
{

    UNREFERENCED_PARAMETER(pParam);

	LONG bRet = -1;
	NET_DVR_PDC_QUERY struPDCQueryData;
    memset(&struPDCQueryData, 0, sizeof(struPDCQueryData));
	CString csTmp;
	char szLan[128] = {0};
	while (1) 
	{
		bRet = NET_DVR_FindNextPDCInfo(g_pPDCInfoSearch->m_lFindHandle, &struPDCQueryData);
        if (bRet == NET_DVR_FILE_SUCCESS)
		{
			csTmp.Format("%d", g_pPDCInfoSearch->m_lPDCInfoNum+1);
			g_pPDCInfoSearch->m_listPDCInfo.InsertItem(g_pPDCInfoSearch->m_lPDCInfoNum, csTmp,0);
			csTmp.Format("%04d-%02d-%02d %02d:%02d:%02d", struPDCQueryData.tmStart.dwYear, struPDCQueryData.tmStart.dwMonth, struPDCQueryData.tmStart.dwDay, \
				struPDCQueryData.tmStart.dwHour,struPDCQueryData.tmStart.dwMinute, struPDCQueryData.tmStart.dwSecond);
			g_pPDCInfoSearch->m_listPDCInfo.SetItemText(g_pPDCInfoSearch->m_lPDCInfoNum, 1, csTmp);	

            csTmp.Format("%04d-%02d-%02d %02d:%02d:%02d", struPDCQueryData.tmEnd.dwYear, struPDCQueryData.tmEnd.dwMonth, struPDCQueryData.tmEnd.dwDay, \
                struPDCQueryData.tmEnd.dwHour,struPDCQueryData.tmEnd.dwMinute, struPDCQueryData.tmEnd.dwSecond);
            g_pPDCInfoSearch->m_listPDCInfo.SetItemText(g_pPDCInfoSearch->m_lPDCInfoNum, 2, csTmp);	
            
            csTmp.Format("Enter:%d", struPDCQueryData.dwLeaveNum);
            g_pPDCInfoSearch->m_listPDCInfo.SetItemText(g_pPDCInfoSearch->m_lPDCInfoNum, 3, csTmp);

            
            csTmp.Format("Leave:%d", struPDCQueryData.dwEnterNum);
            g_pPDCInfoSearch->m_listPDCInfo.SetItemText(g_pPDCInfoSearch->m_lPDCInfoNum, 4, csTmp);

			g_pPDCInfoSearch->m_lPDCInfoNum++;
		}
		else
		{
			if (bRet == NET_DVR_ISFINDING)
			{
				g_pPDCInfoSearch->GetDlgItem(IDC_STATIC_SEARCH)->ShowWindow(SW_SHOW);
				g_pPDCInfoSearch->GetDlgItem(IDC_STATIC_SEARCH)->SetWindowText("Searching......");
				Sleep(5);
				continue;
			}
			if ((bRet == NET_DVR_NOMOREFILE) || (bRet == NET_DVR_FILE_NOFIND))
			{
				g_StringLanType(szLan, "搜索人流量", "search PDC");
				g_pPDCInfoSearch->GetDlgItem(IDC_BTN_SEARCH)->SetWindowText(szLan);
//				g_pPDCInfoSearch->m_bSearch = FALSE;
				g_pPDCInfoSearch->GetDlgItem(IDC_STATIC_SEARCH)->ShowWindow(SW_HIDE);
				g_StringLanType(szLan, "搜索人流量信息结束!", "Search PDC Ending");
				AfxMessageBox(szLan);
				break;
			}
			else
			{
				g_StringLanType(szLan, "搜索人流量", "Search PDC");
				g_pPDCInfoSearch->GetDlgItem(IDC_BTN_SEARCH)->SetWindowText(szLan);
//				g_pPDCInfoSearch->m_bSearch = FALSE;
				g_StringLanType(szLan, "由于服务器忙,或网络故障,搜索异常终止!",\
					"Since the server is busy, or network failure, search abnormal termination");
				AfxMessageBox(szLan);
				break;
			}
		}
	}
	CloseHandle(g_pPDCInfoSearch->m_hPdcFindThread);
	g_pPDCInfoSearch->m_hPdcFindThread = NULL;
	NET_DVR_FindLogClose_V30(g_pPDCInfoSearch->m_lFindHandle);

	return 0;

}

CDlgPDCSearch::CDlgPDCSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPDCSearch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPDCSearch)
    m_ctDateStart = 0;
    m_ctTimeStart = 0;
	m_ctDateStop = 0;
    m_ctTimeStop = 0;
	//}}AFX_DATA_INIT
    m_lFindHandle = -1;
    m_lServerID = -1; 
    m_lChannel = -1;  
    m_iDevIndex = -1; 
    m_lPDCInfoNum = 0;
    m_hPdcFindThread = NULL;
}


void CDlgPDCSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPDCSearch)
	DDX_Control(pDX, IDC_LIST_PDC_INFO, m_listPDCInfo);
	DDX_DateTimeCtrl(pDX, IDC_TIME_PDC_STOP, m_ctTimeStop);
	DDX_DateTimeCtrl(pDX, IDC_TIME_PDC_START, m_ctTimeStart);
	DDX_DateTimeCtrl(pDX, IDC_DATE_PDC_START, m_ctDateStart);
	DDX_DateTimeCtrl(pDX, IDC_DATE_PDC_STOP, m_ctDateStop);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPDCSearch, CDialog)
	//{{AFX_MSG_MAP(CDlgPDCSearch)
	ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPDCSearch message handlers

void CDlgPDCSearch::OnBtnSearch() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char szLan[128] = {0};

        NET_DVR_TIME StartTime;
        NET_DVR_TIME StopTime;
        
        StartTime.dwYear = (WORD)m_ctDateStart.GetYear();
        StartTime.dwMonth = (WORD)m_ctDateStart.GetMonth();
        StartTime.dwDay = (WORD)m_ctDateStart.GetDay();
        StartTime.dwHour = (char)m_ctTimeStart.GetHour();
        StartTime.dwMinute = (char)m_ctTimeStart.GetMinute();
        StartTime.dwSecond = (char)m_ctTimeStart.GetSecond();
        
        StopTime.dwYear = (WORD)m_ctDateStop.GetYear();
        StopTime.dwMonth = (WORD)m_ctDateStop.GetMonth();
        StopTime.dwDay = (WORD)m_ctDateStop.GetDay();
        StopTime.dwHour = (char)m_ctTimeStop.GetHour();
        StopTime.dwMinute = (char)m_ctTimeStop.GetMinute();
        StopTime.dwSecond = (char)m_ctTimeStop.GetSecond();
        


        m_lFindHandle = NET_DVR_FindPDCInfo(m_lServerID, m_lChannel,&StartTime, &StopTime);
        if (m_lFindHandle < 0)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_FindPDCInfo");
            
            g_StringLanType(szLan, "搜索人数统计信息失败", "Search log failed");
            AfxMessageBox(szLan);
            return;
        }
        m_lPDCInfoNum = 0;
        m_listPDCInfo.DeleteAllItems();
        DWORD dwThreadId;
        if (m_hPdcFindThread == NULL)
        {
            m_hPdcFindThread  = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetPDCInfohread),this,0,&dwThreadId);		
        }
        if (m_hPdcFindThread  == NULL)
        {
            g_StringLanType(szLan, "打开线程失败", "Open thread failed");
            AfxMessageBox(szLan);
            return;
        }
//         g_StringLanType(szLan, "停止搜索", "Stop Search");
//         GetDlgItem(IDC_BTN_SEARCH)->SetWindowText(szLan);
//         m_bSearch = TRUE;

}


void CDlgPDCSearch::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
    if (m_hPdcFindThread)
    {
        TerminateThread(m_hPdcFindThread, 0);
        CloseHandle(m_hPdcFindThread);
        m_hPdcFindThread = NULL;
        NET_DVR_FindLogClose_V30(m_lFindHandle);
    }
	CDialog::OnCancel();
}

BOOL CDlgPDCSearch::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_pPDCInfoSearch = this;
	// TODO: Add extra initialization here
    CTime ctCurTime = CTime::GetCurrentTime();
    CTime time(ctCurTime.GetYear(),ctCurTime.GetMonth(),ctCurTime.GetDay(),0,0,0);
    CTime time0(ctCurTime.GetYear(),ctCurTime.GetMonth(),ctCurTime.GetDay(),23,59,59);
    m_ctDateStart = time;
    m_ctTimeStart = time;
    m_ctDateStop = ctCurTime;
	m_ctTimeStop = time0;

    char szLan[128] = {0};
    
    m_listPDCInfo.SetExtendedStyle(m_listPDCInfo.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
    g_StringLanType(szLan, "序号", "No.");
    m_listPDCInfo.InsertColumn(0, szLan, LVCFMT_RIGHT, 60, -1);
    g_StringLanType(szLan, "开始时间", "Start Time");
    m_listPDCInfo.InsertColumn(1, szLan, LVCFMT_LEFT, 140, -1);
    g_StringLanType(szLan, "结束时间", "Stop Time");
    m_listPDCInfo.InsertColumn(2, szLan, LVCFMT_LEFT,140, -1);
    g_StringLanType(szLan, "离开人数", "Leave Num");
    m_listPDCInfo.InsertColumn(3, szLan, LVCFMT_LEFT, 80, -1);
    g_StringLanType(szLan, "进入人数", "Enter Num");
    m_listPDCInfo.InsertColumn(4, szLan, LVCFMT_LEFT, 80, -1);
    

    UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
