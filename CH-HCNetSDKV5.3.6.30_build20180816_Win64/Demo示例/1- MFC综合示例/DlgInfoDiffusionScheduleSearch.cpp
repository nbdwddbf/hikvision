// DlgInfoDiffusionScheduleSearch.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInfoDiffusionScheduleSearch.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionScheduleSearch dialog


CDlgInfoDiffusionScheduleSearch::CDlgInfoDiffusionScheduleSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInfoDiffusionScheduleSearch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInfoDiffusionScheduleSearch)
	m_sSearchID = _T("");
	m_dwMaxResults = 0;
	m_dwStartPosition = 0;
	m_sUploader = _T("");
	m_tmEndDate = COleDateTime::GetCurrentTime();
	m_tmEndTime = COleDateTime::GetCurrentTime();
	m_tmStartDate = COleDateTime::GetCurrentTime();
	m_tmStartTime = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	memset(&m_struDescription, 0, sizeof(m_struDescription));
	m_lpSearchResult = new NET_DVR_SCHEDULE_SEARCH_RESULT;
	memset(m_lpSearchResult, 0, sizeof(*m_lpSearchResult));
	m_pOutputXmlBuffer = new char[MAX_LEN_XML];
	memset(m_pOutputXmlBuffer, 0, sizeof(char)*MAX_LEN_XML);
}


void CDlgInfoDiffusionScheduleSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInfoDiffusionScheduleSearch)
	DDX_Control(pDX, IDC_LIST_SCHEDULE_SEARCH, m_listSchedule);
	DDX_Control(pDX, IDC_COMBO_SEARCH_SHEDULE_TYPE, m_cmbScheduleType);
	DDX_Control(pDX, IDC_COMBO_SEARCH_SHARE_PROP, m_cmbShareProp);
	DDX_Control(pDX, IDC_COMBO_SEARCH_APPROVE_STATE, m_cmbApproveState);
	DDX_Text(pDX, IDC_EDIT_SEARCH_ID, m_sSearchID);
	DDX_Text(pDX, IDC_EDIT_SEARCH_MAX_RESULTS, m_dwMaxResults);
	DDX_Text(pDX, IDC_EDIT_SEARCH_START_POSITION, m_dwStartPosition);
	DDX_Text(pDX, IDC_EDIT_SEARCH_UPLOADER, m_sUploader);
	DDX_DateTimeCtrl(pDX, IDC_END_DATE, m_tmEndDate);
	DDX_DateTimeCtrl(pDX, IDC_END_TIME, m_tmEndTime);
	DDX_DateTimeCtrl(pDX, IDC_START_DATE, m_tmStartDate);
	DDX_DateTimeCtrl(pDX, IDC_START_TIME, m_tmStartTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInfoDiffusionScheduleSearch, CDialog)
	//{{AFX_MSG_MAP(CDlgInfoDiffusionScheduleSearch)
	ON_BN_CLICKED(IDC_BTN_SCHEDULE_SEARCH, OnBtnScheduleSearch)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_BATCH_DEL, &CDlgInfoDiffusionScheduleSearch::OnBnClickedBtnBatchDel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionScheduleSearch message handlers

void CDlgInfoDiffusionScheduleSearch::OnBtnScheduleSearch() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	strcpy(m_struDescription.sSearchID, m_sSearchID);
// 	int nSel = m_cmbApproveState.GetCurSel();
// 	if (nSel == CB_ERR)
// 	{
// 		char szLan1[512] = {0};
// 		char szLan2[512] = {0};
// 		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
// 		g_StringLanType(szLan2, "日程查询", "Schedule Search");
// 		MessageBox(szLan1, szLan2, MB_ICONWARNING);
// 		return;
// 	}
// 	m_cmbApproveState.GetLBText(nSel, m_struDescription.sApproveState);
	int nSel = m_cmbShareProp.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "日程查询", "Schedule Search");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbShareProp.GetLBText(nSel, m_struDescription.sShareProperty);
	nSel = m_cmbScheduleType.GetCurSel();
	if (nSel == CB_ERR)
	{
		char szLan1[512] = {0};
		char szLan2[512] = {0};
		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
		g_StringLanType(szLan2, "日程查询", "Schedule Search");
		MessageBox(szLan1, szLan2, MB_ICONWARNING);
		return;
	}
	m_cmbScheduleType.GetLBText(nSel, m_struDescription.sScheduleType);
	strcpy(m_struDescription.sUploader, m_sUploader);
	m_struDescription.struTimeRange.struBeginTime.dwYear = m_tmStartDate.GetYear();
	m_struDescription.struTimeRange.struBeginTime.dwMonth = m_tmStartDate.GetMonth();
	m_struDescription.struTimeRange.struBeginTime.dwDay = m_tmStartDate.GetDay();
	m_struDescription.struTimeRange.struBeginTime.dwHour = m_tmStartTime.GetHour();
	m_struDescription.struTimeRange.struBeginTime.dwMinute = m_tmStartTime.GetMinute();
	m_struDescription.struTimeRange.struBeginTime.dwSecond = m_tmStartTime.GetSecond();
	m_struDescription.struTimeRange.struEndTime.dwYear = m_tmEndDate.GetYear();
	m_struDescription.struTimeRange.struEndTime.dwMonth = m_tmEndDate.GetMonth();
	m_struDescription.struTimeRange.struEndTime.dwDay = m_tmEndDate.GetDay();
	m_struDescription.struTimeRange.struEndTime.dwHour = m_tmEndTime.GetHour();
	m_struDescription.struTimeRange.struEndTime.dwMinute = m_tmEndTime.GetMinute();
	m_struDescription.struTimeRange.struEndTime.dwSecond = m_tmEndTime.GetSecond();
	m_struDescription.dwMaxResults = m_dwMaxResults;
	m_struDescription.dwSearchResultsPosition = m_dwStartPosition;

	char* pInputBuff = NULL;
	DWORD dwInputSize = 0;
	ConvertScheduleSearchDescriptionParamsStruToXml(&m_struDescription, &pInputBuff, dwInputSize);
	
	CString strCommand;
	strCommand.Format("POST /ISAPI/Publish/ScheduleMgr/scheduleSearch\r\n");
	NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
	struInputParam.dwSize = sizeof(struInputParam);
	struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
	struInputParam.dwRequestUrlLen = strCommand.GetLength();
	struInputParam.lpInBuffer = pInputBuff;
	struInputParam.dwInBufferSize = dwInputSize;
	
	NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
	struOutputParam.dwSize = sizeof(struOutputParam);
	memset(m_pOutputXmlBuffer, 0, MAX_LEN_XML);
	struOutputParam.lpOutBuffer = m_pOutputXmlBuffer;
	struOutputParam.dwOutBufferSize = MAX_LEN_XML;
	
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		delete[] pInputBuff;
		pInputBuff = NULL;
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
	memset(m_lpSearchResult, 0, sizeof(*m_lpSearchResult));
	ConvertScheduleSearchResultParamsXmlToStru(m_pOutputXmlBuffer, m_lpSearchResult);
	RefreshScheduleList();
	
	delete[] pInputBuff;
	pInputBuff = NULL;
}

void CDlgInfoDiffusionScheduleSearch::InitScheduleCtrlList()
{
	DWORD dwExStyle = m_listSchedule.GetExtendedStyle();
	dwExStyle |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
	m_listSchedule.SetExtendedStyle(dwExStyle);
	
	char szLan[512] = {0};
	g_StringLanType(szLan, "序号", "Index");
	m_listSchedule.InsertColumn(0, szLan);
	m_listSchedule.SetColumnWidth(0, 40);

	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "日程编号", "Schedule No.");
	m_listSchedule.InsertColumn(1, szLan);
	m_listSchedule.SetColumnWidth(1, 60);

	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "日程名称", "Schedule Name");
	m_listSchedule.InsertColumn(2, szLan);
	m_listSchedule.SetColumnWidth(2, 80);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "类型", "Type");
	m_listSchedule.InsertColumn(3, szLan);
	m_listSchedule.SetColumnWidth(3, 80);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "共享属性", "Share Property");
	m_listSchedule.InsertColumn(4, szLan);
	m_listSchedule.SetColumnWidth(4, 80);
	
	memset(szLan, 0, sizeof(szLan));
	g_StringLanType(szLan, "备注", "Remarks");
	m_listSchedule.InsertColumn(5, "备注");
	m_listSchedule.SetColumnWidth(5, 400);
}

void CDlgInfoDiffusionScheduleSearch::RefreshScheduleItem(int nScheduleIndex)
{
	if (nScheduleIndex < 0 || nScheduleIndex >= MAX_NUM_SCHEDULE)
	{
		return;
	}
	LPNET_DVR_SCHEDULE_BASIC_INFO lpSchedule = &m_lpSearchResult->struScheduleList[nScheduleIndex];
	CString str;
	str.Format("%d", lpSchedule->dwScheduleID);
	m_listSchedule.SetItemText(nScheduleIndex, 1, str);
	m_listSchedule.SetItemText(nScheduleIndex, 2, lpSchedule->szScheduleName);
	m_listSchedule.SetItemText(nScheduleIndex, 3, lpSchedule->szScheduleType);
	m_listSchedule.SetItemText(nScheduleIndex, 4, lpSchedule->szShareProp);
	m_listSchedule.SetItemText(nScheduleIndex, 5, lpSchedule->szScheduleRemarks);
}

void CDlgInfoDiffusionScheduleSearch::RefreshScheduleList()
{
	m_listSchedule.DeleteAllItems();
	for (int nScheduleCnt = 0; nScheduleCnt < m_lpSearchResult->dwNumOfMatches; nScheduleCnt++)
	{
		if (0 == m_lpSearchResult->struScheduleList[nScheduleCnt].dwScheduleID)
		{
			break;
		}
		CString str;
		str.Format("%d", nScheduleCnt+1);
		m_listSchedule.InsertItem(nScheduleCnt, str);
		RefreshScheduleItem(nScheduleCnt);
	}
}

void CDlgInfoDiffusionScheduleSearch::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if (m_lpSearchResult)
	{
		delete m_lpSearchResult;
		m_lpSearchResult = NULL;
	}
	if (m_pOutputXmlBuffer)
	{
		delete[] m_pOutputXmlBuffer;
		m_pOutputXmlBuffer = NULL;
	}
}

BOOL CDlgInfoDiffusionScheduleSearch::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitScheduleCtrlList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgInfoDiffusionScheduleSearch::OnBnClickedBtnBatchDel()
{
    // TODO:  在此添加控件通知处理程序代码
    
    POSITION pos = m_listSchedule.GetFirstSelectedItemPosition();
    if (pos == NULL)
    {
        return;
    }
    else
    {
        m_nCountId = 0;
        memset(m_nArrayId, 0, MAX_ID);
        int arry[MAX_ID] = { 0 };
        while (pos)
        {
            int nItem = m_listSchedule.GetNextSelectedItem(pos);
            CString strid = m_listSchedule.GetItemText(nItem, 1);
            int intId = atoi(strid);
            m_nArrayId[m_nCountId] = intId;
            m_nCountId++;
            arry[m_nCountId] = nItem;
            //m_listProgram.DeleteItem(nItem);
        }
    }
    char* pInputBuff = NULL;
    DWORD dwInputSize = 0;
    if (!ConvertScheduleIdToXml(m_nArrayId, m_nCountId, &pInputBuff, dwInputSize))
    {
        if (pInputBuff != NULL)
        {
            delete[] pInputBuff;
            pInputBuff = NULL;
        }
        return;
    }
    CString strCommand;
    strCommand.Format("DELETE /ISAPI/Publish/ScheduleMgr/playSchedule\r\n");
    NET_DVR_XML_CONFIG_INPUT struInputParam = { 0 };
    struInputParam.dwSize = sizeof(struInputParam);
    struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
    struInputParam.dwRequestUrlLen = strCommand.GetLength();
    struInputParam.lpInBuffer = pInputBuff;
    struInputParam.dwInBufferSize = dwInputSize;

    char szStatusBuff[1024] = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT struOutputParam = { 0 };
    struOutputParam.dwSize = sizeof(struOutputParam);
    struOutputParam.lpStatusBuffer = szStatusBuff;
    struOutputParam.dwStatusSize = sizeof(szStatusBuff);

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
        if (pInputBuff != NULL)
        {
            delete[] pInputBuff;
            pInputBuff = NULL;
        }
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");


    if (pInputBuff != NULL)
    {
        delete[] pInputBuff;
        pInputBuff = NULL;
    }
}
