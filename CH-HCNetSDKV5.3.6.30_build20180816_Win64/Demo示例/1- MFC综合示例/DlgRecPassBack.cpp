// DlgRecPassBack.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRecPassBack.h"
#include "DlgRecPassBackScheCfg.h"
#include "DlgRecPassbackTaskExecutable.h"
#include "DlgRecPassBackHistorySchdule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRecPassBack dialog


CDlgRecPassBack::CDlgRecPassBack(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRecPassBack::IDD, pParent)
    , m_bTimeRange(FALSE)
    , m_dwTaskID(0)
    , m_dwTaskIDGet(0)
    , m_dwHistoryChannelPlan(0)
    , m_bRecPassbackHistory(FALSE)
    , m_strStreamIDHistory(_T(""))
{
	//{{AFX_DATA_INIT(CDlgRecPassBack)
	m_csStreamID4 = _T("");
	m_nChannel4 = 0;
	m_csStatus = _T("");
	m_oleDateStart = COleDateTime::GetCurrentTime();
	m_oleDateStop = COleDateTime::GetCurrentTime();
	m_oleTimeStart = COleDateTime::GetCurrentTime();
	m_oleTimeStop = COleDateTime::GetCurrentTime();
	m_nChannel2 = 0;
	m_csStreamID2 = _T("");
	m_nDelTaskID = 0;
	m_csDelStreamID = _T("");
	m_nDelChannel = 0;
	m_csDelStatus = _T("");
	m_bChkRecPassBackSche = FALSE;
	m_csStreamIDPlan = _T("");
	m_nChannelPlan = 0;
    m_oleDateStart1 = COleDateTime::GetCurrentTime();
    m_oleDateStop1 = COleDateTime::GetCurrentTime();
    m_oleTimeStart1 = COleDateTime::GetCurrentTime();
    m_oleTimeStop1 = COleDateTime::GetCurrentTime();
    m_nChannelGetAllTask = 0;
    m_csStreamIDGetAllTask = _T("");
	//}}AFX_DATA_INIT

	m_ilastDelTypeSel = -1;
	m_lGetAllTaskHandle = -1;
	m_bGetAllTaskNext = FALSE;
	m_hGetAllTaskThread = NULL;
	memset(&m_struRecordPassBackTaskRet, 0, sizeof(m_struRecordPassBackTaskRet));

	m_pStruRecordPassBackSchCfg = new NET_DVR_RECORD_PASSBACK_SCH_CFG;
	if(m_pStruRecordPassBackSchCfg != NULL)
	{
		memset(m_pStruRecordPassBackSchCfg, 0, sizeof(NET_DVR_RECORD_PASSBACK_SCH_CFG));
	}
    m_pStruRecordPassBackHistoryPlanCfg = new NET_DVR_RECORD_PASSBACK_HISTORY_PLAN_CFG;
    if (m_pStruRecordPassBackHistoryPlanCfg != NULL)
    {
        memset(m_pStruRecordPassBackHistoryPlanCfg, 0, sizeof(NET_DVR_RECORD_PASSBACK_HISTORY_PLAN_CFG));
    }
	//memset(&m_struRecordPassBackSchCfg, 0, sizeof(m_struRecordPassBackSchCfg));
}


void CDlgRecPassBack::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRecPassBack)
	DDX_Control(pDX, IDC_CMB_TASK_CTRL, m_cmbTaskCtrl);
	DDX_Control(pDX, IDC_CMB_DEL_TYPE, m_cmbDelType);
	DDX_Control(pDX, IDC_LIST_DEL_TASK_INFO, m_listDelTaskInfo);
	DDX_Control(pDX, IDC_CMB_GET_TYPE, m_cmbCheckType);
	DDX_Control(pDX, IDC_LIST_ALL_TASK_INFO, m_listAllTaskInfo);
	DDX_Text(pDX, IDC_EDIT_STREAM_ID4, m_csStreamID4);
	DDX_Text(pDX, IDC_EDIT_CHANNEL4, m_nChannel4);
	DDX_Text(pDX, IDC_EDIT_STATUS, m_csStatus);
	DDX_Control(pDX, IDC_LIST_ADD_REC_PASSBACK_TASK, m_listAddRecPassBackTask);
	DDX_DateTimeCtrl(pDX, IDC_DATE_START, m_oleDateStart);
	DDX_DateTimeCtrl(pDX, IDC_DATE_STOP, m_oleDateStop);
	DDX_DateTimeCtrl(pDX, IDC_TIME_START, m_oleTimeStart);
	DDX_DateTimeCtrl(pDX, IDC_TIME_STOP, m_oleTimeStop);
// 	DDX_Text(pDX, IDC_EDIT_CHANNEL2, m_nChannel2);
// 	DDX_Text(pDX, IDC_EDIT_STREAM_ID2, m_csStreamID2);
	DDX_Text(pDX, IDC_EDIT_DEL_TASK_ID, m_nDelTaskID);
	DDX_Text(pDX, IDC_EDIT_DEL_STREAM_ID, m_csDelStreamID);
	DDX_Text(pDX, IDC_EDIT_DEL_CHANNEL, m_nDelChannel);
	DDX_Text(pDX, IDC_EDIT_DEL_STATUS, m_csDelStatus);
	DDX_Check(pDX, IDC_CHK_RECORD_PASS_BACK, m_bChkRecPassBackSche);
	DDX_Text(pDX, IDC_EDIT_STREAM_ID_PLAN, m_csStreamIDPlan);
	DDX_Text(pDX, IDC_EDIT_CHANNEL_PLAN, m_nChannelPlan);
    DDX_DateTimeCtrl(pDX, IDC_GET_TASK_DATE_START, m_oleDateStart1);
    DDX_DateTimeCtrl(pDX, IDC_GET_TASK_DATE_STOP, m_oleDateStop1);
    DDX_DateTimeCtrl(pDX, IDC_GET_TASK_TIME_START, m_oleTimeStart1);
    DDX_DateTimeCtrl(pDX, IDC_GET_TASK_TIME_STOP, m_oleTimeStop1);
    DDX_Check(pDX, IDC_CHK_TIME_RANGE, m_bTimeRange);
    DDX_Text(pDX, IDC_EDIT_GET_ALL_TASK_STREAM_ID, m_csStreamIDGetAllTask);
    DDX_Text(pDX, IDC_EDIT_GET_ALL_TASK_CHANNEL, m_nChannelGetAllTask);
	//}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_TASK_ID, m_dwTaskID);
    DDX_Text(pDX, IDC_EDIT_GET_TASK_ID, m_dwTaskIDGet);
    DDX_Text(pDX, IDC_EDIT_CHANNEL_HISTORY_PLAN, m_dwHistoryChannelPlan);
    DDX_Check(pDX, IDC_CHK_RECORD_PASS_BACK_HISTORY, m_bRecPassbackHistory);
    DDX_Text(pDX, IDC_EDIT_STREAM_ID_HISTORY_PLAN, m_strStreamIDHistory);
}


BEGIN_MESSAGE_MAP(CDlgRecPassBack, CDialog)
	//{{AFX_MSG_MAP(CDlgRecPassBack)
	ON_BN_CLICKED(IDC_BTN_ADD_TASK, OnBtnAddTask)
	ON_BN_CLICKED(IDC_BTN_DEL_TASK, OnBtnDelTask)
	ON_BN_CLICKED(IDC_BTN_SET_TASK, OnBtnSetTask)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ADD_REC_PASSBACK_TASK, OnClickListAddRecPassbackTask)
	ON_BN_CLICKED(IDC_BTN_GET_ALL_TASK, OnBtnGetAllTask)
	ON_BN_CLICKED(IDC_BTN_SET_DEL_TASK, OnBtnSetDelTask)
	ON_BN_CLICKED(IDC_BTN_REMOVE_DEL_TASK, OnBtnRemoveDelTask)
	ON_BN_CLICKED(IDC_BTN_ADD_DEL_TASK, OnBtnAddDelTask)
	ON_CBN_SELCHANGE(IDC_CMB_DEL_TYPE, OnSelchangeCmbDelType)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DEL_TASK_INFO, OnClickListDelTaskInfo)
	ON_BN_CLICKED(IDC_BTN_TASK_CTRL, OnBtnTaskCtrl)
	ON_BN_CLICKED(IDC_CHK_RECORD_PASS_BACK, OnChkRecordPassBack)
	ON_BN_CLICKED(IDC_BTN_RECORD_PASS_BACK_SETUP, OnBtnRecordPassBackSetup)
	ON_BN_CLICKED(IDC_BTN_PASS_BACK_SCHED_GET, OnBtnPassBackSchedGet)
	ON_BN_CLICKED(IDC_BTN_PASS_BACK_SCHED_SET, OnBtnPassBackSchedSet)
    ON_BN_CLICKED(IDC_BTN_PASS_BACK_SCHED_GET2, OnBnClickedBtnPassBackSchedGet2)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_RECORD_PASS_BACK_SETUP_HISTORY, &CDlgRecPassBack::OnBnClickedBtnRecordPassBackSetupHistory)
    ON_BN_CLICKED(IDC_BTN_PASS_BACK_SCHED_GET_HISTORY, &CDlgRecPassBack::OnBnClickedBtnPassBackSchedGetHistory)
    ON_BN_CLICKED(IDC_BTN_PASS_BACK_SCHED_SET_HISTORY, &CDlgRecPassBack::OnBnClickedBtnPassBackSchedSetHistory)
    ON_BN_CLICKED(IDC_CHK_RECORD_PASS_BACK_HISTORY, &CDlgRecPassBack::OnBnClickedChkRecordPassBackHistory)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRecPassBack message handlers

BOOL CDlgRecPassBack::OnInitDialog() 
{
	CDialog::OnInitDialog(); 
		
	// TODO: Add extra initialization here
	char szLan[128] = {0};
	m_listAddRecPassBackTask.SetExtendedStyle(m_listAddRecPassBackTask.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	
	g_StringLanType(szLan, "序号", "Serial No.");
	m_listAddRecPassBackTask.InsertColumn(0, szLan, LVCFMT_LEFT, 50, -1);
	
	g_StringLanType(szLan, "流ID", "Stream ID");
	m_listAddRecPassBackTask.InsertColumn(1, szLan, LVCFMT_LEFT, 100, -1);
	
	g_StringLanType(szLan, "关联通道", "Related channel");
	m_listAddRecPassBackTask.InsertColumn(2, szLan, LVCFMT_LEFT, 60, -1);
	
	g_StringLanType(szLan, "回传录像开始时间", "Record passback start time");
	m_listAddRecPassBackTask.InsertColumn(3, szLan, LVCFMT_LEFT, 100, -1);
	
	g_StringLanType(szLan, "回传的录像结束时间", "Record passback stop time");
	m_listAddRecPassBackTask.InsertColumn(4, szLan, LVCFMT_LEFT, 100, -1);
	
	g_StringLanType(szLan, "状态", "Status");
	m_listAddRecPassBackTask.InsertColumn(5, szLan, LVCFMT_LEFT, 60, -1);

    g_StringLanType(szLan, "任务ID", "Task ID");
    m_listAddRecPassBackTask.InsertColumn(6, szLan, LVCFMT_LEFT, 60, -1);

	m_listAllTaskInfo.SetExtendedStyle(m_listAllTaskInfo.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	
	g_StringLanType(szLan, "任务ID", "Task ID");
	m_listAllTaskInfo.InsertColumn(0, szLan, LVCFMT_LEFT, 50, -1);
	
	g_StringLanType(szLan, "流ID", "Stream ID");
	m_listAllTaskInfo.InsertColumn(1, szLan, LVCFMT_LEFT, 80, -1);
	
	g_StringLanType(szLan, "任务状态", "Task Status");
	m_listAllTaskInfo.InsertColumn(2, szLan, LVCFMT_LEFT, 50, -1);
	
	g_StringLanType(szLan, "回传录像开始时间", "Start time");
	m_listAllTaskInfo.InsertColumn(3, szLan, LVCFMT_LEFT, 120, -1);	
	g_StringLanType(szLan, "回传录像结束时间", "Stop Time");
	m_listAllTaskInfo.InsertColumn(4, szLan, LVCFMT_LEFT, 120, -1);
	
	g_StringLanType(szLan, "任务实际执行开始时间", "Start time");
	m_listAllTaskInfo.InsertColumn(5, szLan, LVCFMT_LEFT, 120, -1);	
	g_StringLanType(szLan, "任务实际执行结束时间", "Stop Time");
	m_listAllTaskInfo.InsertColumn(6, szLan, LVCFMT_LEFT, 120, -1);

	m_listDelTaskInfo.SetExtendedStyle(m_listDelTaskInfo.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	
	g_StringLanType(szLan, "任务ID", "Task ID");
	m_listDelTaskInfo.InsertColumn(0, szLan, LVCFMT_LEFT, 50, -1);
	
	g_StringLanType(szLan, "流ID", "Stream ID");
	m_listDelTaskInfo.InsertColumn(1, szLan, LVCFMT_LEFT, 100, -1);
	
	g_StringLanType(szLan, "关联通道", "Task Status");
	m_listDelTaskInfo.InsertColumn(2, szLan, LVCFMT_LEFT, 60, -1);
	
	g_StringLanType(szLan, "状态", "Start time");
	m_listDelTaskInfo.InsertColumn(3, szLan, LVCFMT_LEFT, 50, -1);

    g_StringLanType(szLan, "获取剩余任务", "Get remaining tasks");
    m_cmbCheckType.InsertString(0, szLan);

    g_StringLanType(szLan, "根据流ID获取剩余任务", "Get remaining tasks by stream ID");
    m_cmbCheckType.InsertString(1, szLan);

    g_StringLanType(szLan, "获取全部任务", "Get all tasks");
    m_cmbCheckType.InsertString(2, szLan);

    g_StringLanType(szLan, "根据流ID获取全部任务", "Get all tasks by stream ID");
    m_cmbCheckType.InsertString(3, szLan);

    g_StringLanType(szLan, "根据任务ID获取任务", "Get task by task ID");
    m_cmbCheckType.InsertString(4, szLan);

	m_cmbCheckType.SetCurSel(0);

    g_StringLanType(szLan, "根据任务ID删除", "Delete by task ID");
    m_cmbDelType.InsertString(0, szLan);

    g_StringLanType(szLan, "根据流ID删除", "Delete by stream ID");
    m_cmbDelType.InsertString(1, szLan);

    g_StringLanType(szLan, "删除全部任务", "Delete all tasks");
    m_cmbDelType.InsertString(2, szLan);

	m_cmbDelType.SetCurSel(0);

    g_StringLanType(szLan, "暂停所有手动任务", "Suspend all manual tasks");
    m_cmbTaskCtrl.InsertString(0, szLan);

    g_StringLanType(szLan, "恢复所有手动任务", "Restore all manual tasks");
    m_cmbTaskCtrl.InsertString(1, szLan);

	m_cmbTaskCtrl.SetCurSel(0);

	COleDateTime timeCur = COleDateTime::GetCurrentTime();
	COleDateTime timeStart(timeCur.GetYear(), timeCur.GetMonth(), timeCur.GetDay(), 0, 0, 0);
	COleDateTime timeStop(timeCur.GetYear(), timeCur.GetMonth(), timeCur.GetDay(), 23, 59, 59);
	
	m_oleDateStart = timeStart;
	m_oleTimeStart = timeStart;
	m_oleDateStop = timeStop;
	m_oleTimeStop = timeStop;

    m_oleDateStart1 = timeStart;
    m_oleTimeStart1 = timeStart;
    m_oleDateStop1 = timeStop;
    m_oleTimeStop1 = timeStop;

	/*
	CTime timeCur;
	timeCur = GetCurrentTime();
	
	CTime timeStart(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),0,0,0);
	CTime timeStop(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),23,59,59);
	
	m_ctDateStart3 = timeStart;
	m_ctTimeStart3 = timeStart;
	m_ctDateStop3 = timeStop;
	m_ctTimeStop3 = timeStop;
	*/
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRecPassBack::OnBtnAddTask() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	char szLan[128] = {0};
	CString strTemp;
	
	// 	if ("" == m_strStreamID)
	// 	{
	// 		g_StringLanType(szLan,"流ID为空","Stream ID is NULL");
	// 		AfxMessageBox(szLan);
	// 		return;
	// 	}
	
	int iItemCount = m_listAddRecPassBackTask.GetItemCount();
	if (iItemCount > 64)
	{
		g_StringLanType(szLan,"超过64个","More than 64");
		AfxMessageBox(szLan);
		return;
	}
	strTemp.Format("%02d", iItemCount + 1);
	
	m_listAddRecPassBackTask.InsertItem(iItemCount, strTemp);
	m_listAddRecPassBackTask.SetItemText(iItemCount, 1, m_csStreamID4);
	
	strTemp.Format("%d", m_nChannel4);
	m_listAddRecPassBackTask.SetItemText(iItemCount, 2, strTemp);
	
	strTemp.Format("%04d%02d%02d%02d%02d%02d",m_oleDateStart.GetYear(), m_oleDateStart.GetMonth(), \
		m_oleDateStart.GetDay(), m_oleTimeStart.GetHour(), m_oleTimeStart.GetMinute(),m_oleTimeStart.GetSecond());
	m_listAddRecPassBackTask.SetItemText(iItemCount, 3, strTemp);
	
	strTemp.Format("%04d%02d%02d%02d%02d%02d",m_oleDateStop.GetYear(), m_oleDateStop.GetMonth(), \
		m_oleDateStop.GetDay(), m_oleTimeStop.GetHour(), m_oleTimeStop.GetMinute(),m_oleTimeStop.GetSecond());
	m_listAddRecPassBackTask.SetItemText(iItemCount, 4, strTemp);
}

void CDlgRecPassBack::OnBtnDelTask() 
{
	// TODO: Add your control notification handler code here
	while( m_listAddRecPassBackTask.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED) != -1 )
	{
		int nItem = m_listAddRecPassBackTask.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED);
		m_listAddRecPassBackTask.DeleteItem(nItem);
	}
}

void CDlgRecPassBack::OnBtnSetTask() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    char szLan[128] = {0};

	LPNET_DVR_ADD_RECORD_PASSBACK_MANUAL_CFG pRecordPassBackManulCfg = NULL;
	LPNET_DVR_ADD_RECORD_PASSBACK_MANUAL_CFG pRecordPassBackManulCfgTemp = NULL;
	
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	LONG lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	
	int iItemCount = m_listAddRecPassBackTask.GetItemCount();
	
	LPNET_DVR_ADD_RECORD_PASSBACK_MANUAL_COND pRecordPassBackManulCond = NULL;
	LPNET_DVR_ADD_RECORD_PASSBACK_MANUAL_COND pRecordPassBackManulCondTemp = NULL;

    LPNET_DVR_RECORD_PASSBACK_TASK_CFG pRecordPassBackTaskCfg = NULL;

	if (0 == iItemCount)
	{
// 		if ("" == m_strStreamID)
// 		{
// 			g_StringLanType(szLan,"流ID为空","Stream ID is NULL");
// 			AfxMessageBox(szLan);
// 			return;
// 		}
		pRecordPassBackManulCond = new NET_DVR_ADD_RECORD_PASSBACK_MANUAL_COND;
		if (NULL == pRecordPassBackManulCond)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pRecordPassBackManulCond, 0, sizeof(NET_DVR_ADD_RECORD_PASSBACK_MANUAL_COND));

		pRecordPassBackManulCond->dwSize = sizeof(NET_DVR_ADD_RECORD_PASSBACK_MANUAL_COND);
		pRecordPassBackManulCond->struStreamInfo.dwSize = sizeof(NET_DVR_STREAM_INFO);
		pRecordPassBackManulCond->struStreamInfo.dwChannel = m_nChannel4;
		strncpy((char*)pRecordPassBackManulCond->struStreamInfo.byID, m_csStreamID4.GetBuffer(0), STREAM_ID_LEN);

		pRecordPassBackManulCfg = new NET_DVR_ADD_RECORD_PASSBACK_MANUAL_CFG;
		if (NULL == pRecordPassBackManulCfg)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pRecordPassBackManulCfg, 0, sizeof(NET_DVR_ADD_RECORD_PASSBACK_MANUAL_CFG));
		pRecordPassBackManulCfg->dwSize = sizeof(NET_DVR_ADD_RECORD_PASSBACK_MANUAL_CFG);

		pRecordPassBackManulCfg->struBeginTime.wYear = m_oleDateStart.GetYear();
		pRecordPassBackManulCfg->struBeginTime.byMonth = m_oleDateStart.GetMonth();
		pRecordPassBackManulCfg->struBeginTime.byDay = m_oleDateStart.GetDay();
		pRecordPassBackManulCfg->struBeginTime.byHour = m_oleTimeStart.GetHour();
		pRecordPassBackManulCfg->struBeginTime.byMinute = m_oleTimeStart.GetMinute();
		pRecordPassBackManulCfg->struBeginTime.bySecond = m_oleTimeStart.GetSecond();
		
		pRecordPassBackManulCfg->struEndTime.wYear = m_oleDateStop.GetYear();
		pRecordPassBackManulCfg->struEndTime.byMonth = m_oleDateStop.GetMonth();
		pRecordPassBackManulCfg->struEndTime.byDay = m_oleDateStop.GetDay();
		pRecordPassBackManulCfg->struEndTime.byHour = m_oleTimeStop.GetHour();
		pRecordPassBackManulCfg->struEndTime.byMinute = m_oleTimeStop.GetMinute();
		pRecordPassBackManulCfg->struEndTime.bySecond = m_oleTimeStop.GetSecond();

		DWORD dwStatus = 0;

        pRecordPassBackTaskCfg = new NET_DVR_RECORD_PASSBACK_TASK_CFG;
        if (NULL == pRecordPassBackTaskCfg)
        {
            g_StringLanType(szLan, "申请内存失败", "new memory failed");
            AfxMessageBox(szLan);
            return;
        }
        memset(pRecordPassBackTaskCfg, 0, sizeof(NET_DVR_RECORD_PASSBACK_TASK_CFG));

        NET_DVR_IN_PARAM struInputPapam = { 0 };
        NET_DVR_OUT_PARAM struOutputPapam = { 0 };
        struInputPapam.struCondBuf.pBuf = pRecordPassBackManulCond;
        struInputPapam.struCondBuf.nLen = sizeof(NET_DVR_ADD_RECORD_PASSBACK_MANUAL_COND);
        struInputPapam.struInParamBuf.pBuf = pRecordPassBackManulCfg;
        struInputPapam.struInParamBuf.nLen = sizeof(NET_DVR_ADD_RECORD_PASSBACK_MANUAL_CFG);
        struOutputPapam.lpStatusList = &dwStatus;
        struOutputPapam.struOutBuf.pBuf = pRecordPassBackTaskCfg;
        struOutputPapam.struOutBuf.nLen = sizeof(NET_DVR_RECORD_PASSBACK_TASK_CFG);

        BOOL bRet = NET_DVR_SetDeviceConfigEx(m_lUserID, NET_DVR_ADD_RECORD_PASSBACK_TASK_MANUAL_V50, iItemCount, &struInputPapam, &struOutputPapam);
		if (bRet && (0 == dwStatus))
		{
			g_StringLanType(szLan,"添加任务成功","Add task succ");
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Add task succ");
			AfxMessageBox(szLan);
		}
		else
		{        
			g_StringLanType(szLan,"添加任务失败","Add task failed");
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Add task failed");
			AfxMessageBox(szLan);
		}

		m_csStatus.Format("%d", dwStatus);
        m_dwTaskID = pRecordPassBackTaskCfg->dwTaskID;

        if (NULL != pRecordPassBackManulCond)
        {
            delete pRecordPassBackManulCond;
            pRecordPassBackManulCond = NULL;
        }
        if (NULL != pRecordPassBackManulCfg)
        {
            delete pRecordPassBackManulCfg;
            pRecordPassBackManulCfg = NULL;
        }
        if (NULL != pRecordPassBackTaskCfg)
        {
            delete pRecordPassBackTaskCfg;
            pRecordPassBackTaskCfg = NULL;
        }
	}
	else
	{
		// 申请iItemCount个NET_DVR_STREAM_INFO
		pRecordPassBackManulCond = new NET_DVR_ADD_RECORD_PASSBACK_MANUAL_COND[iItemCount];
		if (NULL == pRecordPassBackManulCond)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pRecordPassBackManulCond, 0, iItemCount * sizeof(NET_DVR_ADD_RECORD_PASSBACK_MANUAL_COND));
		pRecordPassBackManulCondTemp = pRecordPassBackManulCond;

		// 申请iItemCount个NET_DVR_ADD_RECORD_PASSBACK_MANUAL_CFG
		pRecordPassBackManulCfg = new NET_DVR_ADD_RECORD_PASSBACK_MANUAL_CFG[iItemCount];
		if (NULL == pRecordPassBackManulCfg)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pRecordPassBackManulCfg, 0, iItemCount*sizeof(NET_DVR_ADD_RECORD_PASSBACK_MANUAL_CFG));
		pRecordPassBackManulCfgTemp = pRecordPassBackManulCfg;

		int i = 0; 
		for (i = 0; i < iItemCount; i++)
		{
		 	pRecordPassBackManulCondTemp->dwSize = sizeof(NET_DVR_ADD_RECORD_PASSBACK_MANUAL_COND);
			pRecordPassBackManulCondTemp->struStreamInfo.dwSize = sizeof(NET_DVR_STREAM_INFO);	
			strncpy((char*)pRecordPassBackManulCondTemp->struStreamInfo.byID, m_listAddRecPassBackTask.GetItemText(i, 1), STREAM_ID_LEN);
		 	pRecordPassBackManulCondTemp->struStreamInfo.dwChannel = atoi(m_listAddRecPassBackTask.GetItemText(i, 2));
		 	
			pRecordPassBackManulCfgTemp->dwSize = sizeof(NET_DVR_ADD_RECORD_PASSBACK_MANUAL_CFG);

			CString csTemp;
			csTemp = m_listAddRecPassBackTask.GetItemText(i, 3);

			pRecordPassBackManulCfgTemp->struBeginTime.wYear = atoi(csTemp.Left(4));
			pRecordPassBackManulCfgTemp->struBeginTime.byMonth = atoi(csTemp.Mid(4,2));
			pRecordPassBackManulCfgTemp->struBeginTime.byDay = atoi(csTemp.Mid(6,2));
			pRecordPassBackManulCfgTemp->struBeginTime.byHour = atoi(csTemp.Mid(8,2));
			pRecordPassBackManulCfgTemp->struBeginTime.byMinute = atoi(csTemp.Mid(10,2));
			pRecordPassBackManulCfgTemp->struBeginTime.bySecond = atoi(csTemp.Right(2));

			csTemp = m_listAddRecPassBackTask.GetItemText(i, 4);
			
			pRecordPassBackManulCfgTemp->struEndTime.wYear = atoi(csTemp.Left(4));
			pRecordPassBackManulCfgTemp->struEndTime.byMonth = atoi(csTemp.Mid(4,2));
			pRecordPassBackManulCfgTemp->struEndTime.byDay = atoi(csTemp.Mid(6,2));
			pRecordPassBackManulCfgTemp->struEndTime.byHour = atoi(csTemp.Mid(8,2));
			pRecordPassBackManulCfgTemp->struEndTime.byMinute = atoi(csTemp.Mid(10,2));
			pRecordPassBackManulCfgTemp->struEndTime.bySecond = atoi(csTemp.Right(2));

			pRecordPassBackManulCondTemp++;
			pRecordPassBackManulCfgTemp++;
		}

		DWORD *pStatus = new DWORD[iItemCount];
		memset(pStatus, 0, sizeof(DWORD)*iItemCount);

        pRecordPassBackTaskCfg = new NET_DVR_RECORD_PASSBACK_TASK_CFG[iItemCount];
        if (NULL == pRecordPassBackTaskCfg)
        {
            g_StringLanType(szLan, "申请内存失败", "new memory failed");
            AfxMessageBox(szLan);
            return;
        }
        memset(pRecordPassBackTaskCfg, 0, iItemCount*sizeof(NET_DVR_RECORD_PASSBACK_TASK_CFG));

        NET_DVR_IN_PARAM struInputPapam = { 0 };
        NET_DVR_OUT_PARAM struOutputPapam = { 0 };
        struInputPapam.struCondBuf.pBuf = pRecordPassBackManulCond;
        struInputPapam.struCondBuf.nLen = iItemCount * sizeof(NET_DVR_ADD_RECORD_PASSBACK_MANUAL_COND);
        struInputPapam.struInParamBuf.pBuf = pRecordPassBackManulCfg;
        struInputPapam.struInParamBuf.nLen = iItemCount * sizeof(NET_DVR_ADD_RECORD_PASSBACK_MANUAL_CFG);
        struOutputPapam.lpStatusList = pStatus;
        struOutputPapam.struOutBuf.pBuf = pRecordPassBackTaskCfg;
        struOutputPapam.struOutBuf.nLen = iItemCount*sizeof(NET_DVR_RECORD_PASSBACK_TASK_CFG);


        if (NET_DVR_SetDeviceConfigEx(m_lUserID, NET_DVR_ADD_RECORD_PASSBACK_TASK_MANUAL_V50, iItemCount, &struInputPapam, &struOutputPapam))
		{
			g_StringLanType(szLan,"添加任务成功","Add task succ");
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Add task succ");
			AfxMessageBox(szLan);
		}
		else
		{        
			g_StringLanType(szLan,"添加任务失败","Add task failed");
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Add task failed");
			AfxMessageBox(szLan);
		}

        DWORD *pStatusTemp = pStatus;
        LPNET_DVR_RECORD_PASSBACK_TASK_CFG pRecordPassBackTaskCfgTemp = pRecordPassBackTaskCfg;

		for (i=0; i<iItemCount; i++)
		{
			CString strStatus;
            strStatus.Format("%d", *pStatusTemp);
            m_listAddRecPassBackTask.SetItemText(i, 5, strStatus);
            pStatusTemp++;

            strStatus.Format("%d", pRecordPassBackTaskCfgTemp->dwTaskID);
            m_listAddRecPassBackTask.SetItemText(i, 6, strStatus);
            pRecordPassBackTaskCfgTemp++;
		}

        if (NULL != pRecordPassBackManulCond)
        {
            delete[]pRecordPassBackManulCond;
            pRecordPassBackManulCond = NULL;
        }
        if (NULL != pRecordPassBackManulCfg)
        {
            delete[]pRecordPassBackManulCfg;
            pRecordPassBackManulCfg = NULL;
        }
        if (NULL != pRecordPassBackTaskCfg)
        {
            delete[]pRecordPassBackTaskCfg;
            pRecordPassBackTaskCfg = NULL;
        }
        if (NULL != pStatus)
        {
            delete[]pStatus;
            pStatus = NULL;
        }
	}

	UpdateData(FALSE);
}


void CDlgRecPassBack::OnClickListAddRecPassbackTask(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nItem = 0;
	CString strChannel;
	
	POSITION pos = m_listAddRecPassBackTask.GetFirstSelectedItemPosition();
	if (pos == NULL)
		TRACE0("No items were selected!\n");
	else
	{
		nItem = m_listAddRecPassBackTask.GetNextSelectedItem(pos);
		
		//显示信息
		m_csStreamID4 = m_listAddRecPassBackTask.GetItemText(nItem, 1);
		m_nChannel4 = atoi(m_listAddRecPassBackTask.GetItemText(nItem, 2));
		
		CString csTemp;
		csTemp = m_listAddRecPassBackTask.GetItemText(nItem, 3);

		COleDateTime timeStart(atoi(csTemp.Left(4)), atoi(csTemp.Mid(4,2)), atoi(csTemp.Mid(6,2)), \
			atoi(csTemp.Mid(8,2)), atoi(csTemp.Mid(10,2)), atoi(csTemp.Right(2)));
		
		csTemp = m_listAddRecPassBackTask.GetItemText(nItem, 4);
		
		COleDateTime timeStop(atoi(csTemp.Left(4)), atoi(csTemp.Mid(4,2)), atoi(csTemp.Mid(6,2)), \
			atoi(csTemp.Mid(8,2)), atoi(csTemp.Mid(10,2)), atoi(csTemp.Right(2)));;
		
		m_oleDateStart = timeStart;
		m_oleTimeStart = timeStart;
		m_oleDateStop = timeStop;
		m_oleTimeStop = timeStop;
		
		m_csStatus = m_listAddRecPassBackTask.GetItemText(nItem, 5);

        m_dwTaskID = atoi(m_listAddRecPassBackTask.GetItemText(nItem, 6));
		
		UpdateData(FALSE);
	}
	
	*pResult = 0;
}

void CDlgRecPassBack::OnBtnGetAllTask() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	
	NET_DVR_RECORD_PASSBACK_MANUAL_COND struRecordPassBackCond = {0};
	
	struRecordPassBackCond.dwSize = sizeof(NET_DVR_RECORD_PASSBACK_MANUAL_COND);
	struRecordPassBackCond.struStreamInfo.dwSize = sizeof(NET_DVR_STREAM_INFO);
    strncpy((char*)struRecordPassBackCond.struStreamInfo.byID, m_csStreamIDGetAllTask.GetBuffer(0), STREAM_ID_LEN);
    struRecordPassBackCond.struStreamInfo.dwChannel = m_nChannelGetAllTask;
	
	struRecordPassBackCond.byType = m_cmbCheckType.GetCurSel();

    struRecordPassBackCond.byTimeSegmentQuety = m_bTimeRange;

    if (m_bTimeRange)
    {
        struRecordPassBackCond.struBeginTime.wYear = m_oleDateStart1.GetYear();
        struRecordPassBackCond.struBeginTime.byMonth = m_oleDateStart1.GetMonth();
        struRecordPassBackCond.struBeginTime.byDay = m_oleDateStart1.GetDay();
        struRecordPassBackCond.struBeginTime.byHour = m_oleTimeStart1.GetHour();
        struRecordPassBackCond.struBeginTime.byMinute = m_oleTimeStart1.GetMinute();
        struRecordPassBackCond.struBeginTime.bySecond = m_oleTimeStart1.GetSecond();

        struRecordPassBackCond.struEndTime.wYear = m_oleDateStop1.GetYear();
        struRecordPassBackCond.struEndTime.byMonth = m_oleDateStop1.GetMonth();
        struRecordPassBackCond.struEndTime.byDay = m_oleDateStop1.GetDay();
        struRecordPassBackCond.struEndTime.byHour = m_oleTimeStop1.GetHour();
        struRecordPassBackCond.struEndTime.byMinute = m_oleTimeStop1.GetMinute();
        struRecordPassBackCond.struEndTime.bySecond = m_oleTimeStop1.GetSecond();
    }
    struRecordPassBackCond.dwTaskID = m_dwTaskIDGet;
	
	if (m_lGetAllTaskHandle >= 0)
	{
		g_StringLanType(szLan, "获取中，先停止", "Processing, stop it first");
		AfxMessageBox(szLan);
		return;
	}
	
	m_lGetAllTaskHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_GET_ALL_RECORD_PASSBACK_TASK_MANUAL, \
		&struRecordPassBackCond, sizeof(struRecordPassBackCond), NULL, NULL);
	if (m_lGetAllTaskHandle >= 0)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALL_RECORD_PASSBACK_TASK_MANUAL succ");
		m_bGetAllTaskNext = TRUE;
		DWORD dwThreadId;
		m_listAllTaskInfo.DeleteAllItems();
		m_hGetAllTaskThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetAllTaskThread), this, 0, &dwThreadId);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALL_RECORD_PASSBACK_TASK_MANUAL failed");
		g_StringLanType(szLan, "获取失败", "NET_DVR_GET_ALL_RECORD_PASSBACK_TASK_MANUAL Failed");
		AfxMessageBox(szLan);
		return;
	}
}

DWORD WINAPI CDlgRecPassBack::GetAllTaskThread( LPVOID lpGetAllTask )
{
	CDlgRecPassBack* pThis = reinterpret_cast<CDlgRecPassBack*>(lpGetAllTask);
	int iRet = 0;
	char szLan[128] = {0};
	char szInfoBuf[128] = {0};
	while (pThis->m_bGetAllTaskNext)
	{
		iRet = NET_DVR_GetNextRemoteConfig(pThis->m_lGetAllTaskHandle, &pThis->m_struRecordPassBackTaskRet, sizeof(NET_DVR_RECORD_PASSBACK_MANUAL_TASK_RET)); 
		if (iRet == NET_SDK_GET_NEXT_STATUS_SUCCESS)
		{
			pThis->AddTaskInfoToDlg(&pThis->m_struRecordPassBackTaskRet);
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
				g_StringLanType(szLan, "获取结束!", "Get Finished");
				sprintf(szInfoBuf, "%s[Task Count:%d]", szLan, pThis->m_listAllTaskInfo.GetItemCount());
				AfxMessageBox(szInfoBuf);
				break;
			}
			else if(iRet == NET_SDK_GET_NEXT_STATUS_FAILED)
			{
				g_StringLanType(szLan, "获取失败", "Get Failed");
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
	NET_DVR_StopRemoteConfig(pThis->m_lGetAllTaskHandle);
	pThis->m_bGetAllTaskNext = FALSE;
	pThis->m_lGetAllTaskHandle = -1;
	return 0 ;
}

void CDlgRecPassBack::AddTaskInfoToDlg( LPNET_DVR_RECORD_PASSBACK_MANUAL_TASK_RET lpInter )
{
	int iItemCount = m_listAllTaskInfo.GetItemCount();
	
	m_listAllTaskInfo.InsertItem(iItemCount, "");
	
	CString csTmp;
	char szLan[64] = {0};
	
	csTmp.Format("%d",lpInter->dwTaskID);
	m_listAllTaskInfo.SetItemText(iItemCount, 0, csTmp);
	
	csTmp.Format("%s",lpInter->struStreamInfo.byID);
	m_listAllTaskInfo.SetItemText(iItemCount, 1, csTmp);
	
	if (0 == lpInter->byTaskStatus)
	{
		g_StringLanType(szLan, "未执行", "Not executed");
	} 
	else if (1 == lpInter->byTaskStatus)
	{
		g_StringLanType(szLan, "暂停中", "Paused");		
	} 
	else if (2 == lpInter->byTaskStatus)
	{
		g_StringLanType(szLan, "已执行", "Executed");	
	}
	else if (3 == lpInter->byTaskStatus)
	{
		g_StringLanType(szLan, "回传中", "Passing back");	
	} 
	else
	{
		g_StringLanType(szLan, "未知状态", "Unknown status");
	}
	csTmp.Format("%s", szLan);
	m_listAllTaskInfo.SetItemText(iItemCount, 2, csTmp);
	
	csTmp.Format("%04d%02d%02d%02d%02d%02d",lpInter->struStartTime.wYear, \
		lpInter->struStartTime.byMonth, lpInter->struStartTime.byDay, \
		lpInter->struStartTime.byHour, lpInter->struStartTime.byMinute,\
		lpInter->struStartTime.bySecond);
	m_listAllTaskInfo.SetItemText(iItemCount, 3, csTmp);
	
	csTmp.Format("%04d%02d%02d%02d%02d%02d", lpInter->struStopTime.wYear, lpInter->struStopTime.byMonth,\
		lpInter->struStopTime.byDay, lpInter->struStopTime.byHour, \
		lpInter->struStopTime.byMinute, lpInter->struStopTime.bySecond);
	m_listAllTaskInfo.SetItemText(iItemCount, 4, csTmp);
	
	csTmp.Format("%04d%02d%02d%02d%02d%02d",lpInter->struExecuteStartTime.wYear, \
		lpInter->struExecuteStartTime.byMonth, lpInter->struExecuteStartTime.byDay, \
		lpInter->struExecuteStartTime.byHour, lpInter->struExecuteStartTime.byMinute,\
		lpInter->struExecuteStartTime.bySecond);
	m_listAllTaskInfo.SetItemText(iItemCount, 5, csTmp);
	
	csTmp.Format("%04d%02d%02d%02d%02d%02d", lpInter->struExecuteStopTime.wYear, lpInter->struExecuteStopTime.byMonth,\
		lpInter->struExecuteStopTime.byDay, lpInter->struExecuteStopTime.byHour, \
		lpInter->struExecuteStopTime.byMinute, lpInter->struExecuteStopTime.bySecond);
	m_listAllTaskInfo.SetItemText(iItemCount, 6, csTmp);
}

void CDlgRecPassBack::OnBtnSetDelTask() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    char szLan[128] = {0};

	LPNET_DVR_DEL_RECORD_PASSBACK_MANUAL_CFG pDelRecordPassBackManulCfg = NULL;
	LPNET_DVR_DEL_RECORD_PASSBACK_MANUAL_CFG pDelRecordPassBackManulCfgTemp = NULL;
	
	int iItemCount = m_listDelTaskInfo.GetItemCount();
	
	LPNET_DVR_DEL_RECORD_PASSBACK_MANUAL_COND pDelRecordPassBackManulCond = NULL;
	LPNET_DVR_DEL_RECORD_PASSBACK_MANUAL_COND pDelRecordPassBackManulCondTemp = NULL;

	if (0 == iItemCount)
	{
// 		if ("" == m_strStreamID)
// 		{
// 			g_StringLanType(szLan,"流ID为空","Stream ID is NULL");
// 			AfxMessageBox(szLan);
// 			return;
// 		}
		pDelRecordPassBackManulCond = new NET_DVR_DEL_RECORD_PASSBACK_MANUAL_COND;
		if (NULL == pDelRecordPassBackManulCond)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pDelRecordPassBackManulCond, 0, sizeof(NET_DVR_DEL_RECORD_PASSBACK_MANUAL_COND));

		pDelRecordPassBackManulCond->dwSize = sizeof(NET_DVR_DEL_RECORD_PASSBACK_MANUAL_COND);

		pDelRecordPassBackManulCond->byDelType = m_cmbDelType.GetCurSel();

		pDelRecordPassBackManulCfg = new NET_DVR_DEL_RECORD_PASSBACK_MANUAL_CFG;
		if (NULL == pDelRecordPassBackManulCfg)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pDelRecordPassBackManulCfg, 0, sizeof(NET_DVR_DEL_RECORD_PASSBACK_MANUAL_CFG));

		pDelRecordPassBackManulCfg->dwSize = sizeof(NET_DVR_DEL_RECORD_PASSBACK_MANUAL_CFG);
		pDelRecordPassBackManulCfg->dwTaskID = m_nDelTaskID;

		pDelRecordPassBackManulCfg->struStreamInfo.dwSize = sizeof(NET_DVR_STREAM_INFO);
		pDelRecordPassBackManulCfg->struStreamInfo.dwChannel = m_nDelChannel;
		strncpy((char*)pDelRecordPassBackManulCfg->struStreamInfo.byID, m_csDelStreamID.GetBuffer(0), STREAM_ID_LEN);

		DWORD dwStatus = 0;
		BOOL bRet = NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_DEL_RECORD_PASSBACK_TASK_MANUAL, iItemCount, \
			pDelRecordPassBackManulCond, sizeof(NET_DVR_DEL_RECORD_PASSBACK_MANUAL_COND), &dwStatus, \
			pDelRecordPassBackManulCfg, sizeof(NET_DVR_DEL_RECORD_PASSBACK_MANUAL_CFG));
		if (bRet && (0 == dwStatus))
		{
			g_StringLanType(szLan,"删除任务成功","Del task succ");
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Del task succ");
			AfxMessageBox(szLan);
		}
		else
		{        
			g_StringLanType(szLan,"删除任务失败","Del task failed");
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Del task failed");
			AfxMessageBox(szLan);
		}

		m_csDelStatus.Format("%d", dwStatus);
	}
	else
	{
		// 申请iItemCount个NET_DVR_STREAM_INFO
		pDelRecordPassBackManulCond = new NET_DVR_DEL_RECORD_PASSBACK_MANUAL_COND[iItemCount];
		if (NULL == pDelRecordPassBackManulCond)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pDelRecordPassBackManulCond, 0, iItemCount * sizeof(NET_DVR_DEL_RECORD_PASSBACK_MANUAL_COND));
		pDelRecordPassBackManulCondTemp = pDelRecordPassBackManulCond;

		// 申请iItemCount个NET_DVR_DEL_RECORD_PASSBACK_MANUAL_CFG
		pDelRecordPassBackManulCfg = new NET_DVR_DEL_RECORD_PASSBACK_MANUAL_CFG[iItemCount];
		if (NULL == pDelRecordPassBackManulCfg)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pDelRecordPassBackManulCfg, 0, iItemCount*sizeof(NET_DVR_DEL_RECORD_PASSBACK_MANUAL_CFG));
		pDelRecordPassBackManulCfgTemp = pDelRecordPassBackManulCfg;

		int i = 0; 
		for (i = 0; i < iItemCount; i++)
		{
		 	pDelRecordPassBackManulCondTemp->dwSize = sizeof(NET_DVR_DEL_RECORD_PASSBACK_MANUAL_COND);
			pDelRecordPassBackManulCondTemp->byDelType = m_cmbDelType.GetCurSel();
		 	
			pDelRecordPassBackManulCfgTemp->dwSize = sizeof(NET_DVR_DEL_RECORD_PASSBACK_MANUAL_CFG);
			pDelRecordPassBackManulCfgTemp->dwTaskID = atoi(m_listDelTaskInfo.GetItemText(i, 0));

			pDelRecordPassBackManulCfgTemp->struStreamInfo.dwSize = sizeof(NET_DVR_STREAM_INFO);
			strncpy((char*)pDelRecordPassBackManulCfgTemp->struStreamInfo.byID, m_listDelTaskInfo.GetItemText(i, 1), STREAM_ID_LEN);
		 	pDelRecordPassBackManulCfgTemp->struStreamInfo.dwChannel = atoi(m_listDelTaskInfo.GetItemText(i, 2));

			pDelRecordPassBackManulCondTemp++;
			pDelRecordPassBackManulCfgTemp++;
		}

		DWORD *pStatus = new DWORD[iItemCount];
		memset(pStatus, 0, sizeof(DWORD)*iItemCount);


		if (NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_DEL_RECORD_PASSBACK_TASK_MANUAL, iItemCount, \
			pDelRecordPassBackManulCond, iItemCount*sizeof(NET_DVR_DEL_RECORD_PASSBACK_MANUAL_COND), \
			pStatus, pDelRecordPassBackManulCfg, iItemCount*sizeof(NET_DVR_DEL_RECORD_PASSBACK_MANUAL_CFG)))
		{
			g_StringLanType(szLan,"删除任务成功","Del task succ");
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Del task succ");
			AfxMessageBox(szLan);
		}
		else
		{        
			g_StringLanType(szLan,"删除任务失败","Del task failed");
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Del task failed");
			AfxMessageBox(szLan);
		}

		for (i=0; i<iItemCount; i++)
		{
			CString strStatus;
			strStatus.Format("%d", *pStatus);
			m_listDelTaskInfo.SetItemText(i, 3, strStatus);
			pStatus++;
		}
	}

	UpdateData(FALSE);
}

void CDlgRecPassBack::OnBtnRemoveDelTask()
{
	// TODO: Add your control notification handler code here
	while( m_listDelTaskInfo.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED) != -1 )
	{
		int nItem = m_listDelTaskInfo.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
		m_listDelTaskInfo.DeleteItem(nItem);
	}
}

void CDlgRecPassBack::OnBtnAddDelTask() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	char szLan[128] = {0};
	CString strTemp;
	
	// 	if ("" == m_csDelStreamID)
	// 	{
	// 		g_StringLanType(szLan,"流ID为空","Stream ID is NULL");
	// 		AfxMessageBox(szLan);
	// 		return;
	// 	}
	
	int iItemCount = m_listDelTaskInfo.GetItemCount();
	if (iItemCount > 64)
	{
		g_StringLanType(szLan,"超过64个","More than 64");
		AfxMessageBox(szLan);
		return;
	}

	int iSel = m_cmbDelType.GetCurSel();

	if (0  == iSel)
	{
		strTemp.Format("%d", m_nDelTaskID);	
		m_listDelTaskInfo.InsertItem(iItemCount, strTemp);
	}
	if (1  == iSel)
	{
		strTemp = _T("");
		m_listDelTaskInfo.InsertItem(iItemCount, strTemp);
		m_listDelTaskInfo.SetItemText(iItemCount, 1, m_csDelStreamID);
		
		strTemp.Format("%d", m_nDelChannel);
		m_listDelTaskInfo.SetItemText(iItemCount, 2, strTemp);		
	}
}

void CDlgRecPassBack::OnSelchangeCmbDelType() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int iSel = m_cmbDelType.GetCurSel();

	if (iSel != m_ilastDelTypeSel)
	{
		m_listDelTaskInfo.DeleteAllItems();
	}

	if (0  == iSel)
	{
		GetDlgItem(IDC_LIST_DEL_TASK_INFO)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_ADD_DEL_TASK)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_REMOVE_DEL_TASK)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DEL_TASK_ID)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DEL_STREAM_ID)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DEL_CHANNEL)->EnableWindow(FALSE);
	}
	if (1  == iSel)
	{
		GetDlgItem(IDC_LIST_DEL_TASK_INFO)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_ADD_DEL_TASK)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_REMOVE_DEL_TASK)->EnableWindow(TRUE);
		GetDlgItem(IDC_LIST_DEL_TASK_INFO)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DEL_TASK_ID)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DEL_STREAM_ID)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DEL_CHANNEL)->EnableWindow(TRUE);		
	}
	if (2  == iSel)
	{
		GetDlgItem(IDC_LIST_DEL_TASK_INFO)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_ADD_DEL_TASK)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_REMOVE_DEL_TASK)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DEL_TASK_ID)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DEL_STREAM_ID)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DEL_CHANNEL)->EnableWindow(FALSE);
	}

	m_ilastDelTypeSel = m_cmbDelType.GetCurSel();

	UpdateData(FALSE);
}

void CDlgRecPassBack::OnClickListDelTaskInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nItem = 0;
	
	POSITION pos = m_listDelTaskInfo.GetFirstSelectedItemPosition();
	if (pos == NULL)
		TRACE0("No items were selected!\n");
	else
	{
		nItem = m_listDelTaskInfo.GetNextSelectedItem(pos);
		
		//显示信息
		m_nDelTaskID = atoi(m_listDelTaskInfo.GetItemText(nItem, 0));
		m_csDelStreamID = m_listDelTaskInfo.GetItemText(nItem, 1);
		m_nDelChannel = atoi(m_listDelTaskInfo.GetItemText(nItem, 2));	
		m_csDelStatus = m_listDelTaskInfo.GetItemText(nItem, 3);
		
		UpdateData(FALSE);
	}
	
	*pResult = 0;
}

void CDlgRecPassBack::OnBtnTaskCtrl() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};

	NET_DVR_RECORD_PASSBACK_MANUAL_CTRL struRecordPassBackCtrl = {0};
	struRecordPassBackCtrl.dwSize = sizeof(struRecordPassBackCtrl);
	struRecordPassBackCtrl.byControlType = m_cmbTaskCtrl.GetCurSel();

	if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_RECORD_PASSBACK_TASK_MANUAL_CTRL, &struRecordPassBackCtrl, sizeof(struRecordPassBackCtrl)))
	{
		g_StringLanType(szLan, "控制失败", "Control Failed");
		MessageBox(szLan);
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, szLan);
		return;
	}
	else
	{
		g_StringLanType(szLan, "控制故障提示音成功", "Control Successful");
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, szLan);
	}
}

void CDlgRecPassBack::OnChkRecordPassBack()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_bChkRecPassBackSche)
	{
		GetDlgItem(IDC_BTN_RECORD_PASS_BACK_SETUP)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_RECORD_PASS_BACK_SETUP)->EnableWindow(FALSE);
	}
}

void CDlgRecPassBack::OnBtnRecordPassBackSetup() 
{
	// TODO: Add your control notification handler code here
	CDlgRecPassBackScheCfg dlg;
//     dlg.m_lServerID = m_lLoginID;
//     dlg.m_lChannel = g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[m_iCurChanIndex].iChannelNO;     
//     dlg.m_iDevIndex = m_iDeviceIndex;
	
	dlg.m_pStruRecordPassBackSchCfg = m_pStruRecordPassBackSchCfg;
	if (dlg.DoModal() == IDOK)
	{
// 		m_pbSetChannelPara[m_iCurChanIndex] = TRUE;
// 		g_bMustReboot = g_pMainDlg->IsNeedRebootDevType();
	}
}

void CDlgRecPassBack::OnBtnPassBackSchedGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    char szLan[128];
	DWORD dwStatus = 0;

	NET_DVR_STREAM_INFO struStreamInfo = {0};
	struStreamInfo.dwSize = sizeof(NET_DVR_STREAM_INFO);
	strncpy((char*)struStreamInfo.byID, m_csStreamIDPlan.GetBuffer(0), STREAM_ID_LEN);
	struStreamInfo.dwChannel = m_nChannelPlan;

    m_pStruRecordPassBackSchCfg->dwSize = sizeof(NET_DVR_RECORD_PASSBACK_SCH_CFG);

	if (NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_RECORD_PASSBACK_PLAN_CFG, 1, &struStreamInfo, \
		sizeof(NET_DVR_STREAM_INFO), &dwStatus, m_pStruRecordPassBackSchCfg, sizeof(NET_DVR_RECORD_PASSBACK_SCH_CFG)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_RECORD_PASSBACK_PLAN_CFG SUCC");
		m_bChkRecPassBackSche = m_pStruRecordPassBackSchCfg->byEnable;
		UpdateData(FALSE);
		OnChkRecordPassBack();   
	}
	else
	{       
		g_StringLanType(szLan,"获取录像回传计划失败","get Failed");
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "get Failed");
		AfxMessageBox(szLan);
	}
}

void CDlgRecPassBack::OnBtnPassBackSchedSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	char szLan[128];
	DWORD dwStatus = 0;
	
	NET_DVR_STREAM_INFO struStreamInfo = {0};
	struStreamInfo.dwSize = sizeof(NET_DVR_STREAM_INFO);
	strncpy((char*)struStreamInfo.byID, m_csStreamIDPlan.GetBuffer(0), STREAM_ID_LEN);
	struStreamInfo.dwChannel = m_nChannelPlan;

    m_pStruRecordPassBackSchCfg->dwSize = sizeof(NET_DVR_RECORD_PASSBACK_SCH_CFG);
	m_pStruRecordPassBackSchCfg->byEnable = m_bChkRecPassBackSche;

	if (NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_SET_RECORD_PASSBACK_PLAN_CFG, 1, &struStreamInfo, \
		sizeof(NET_DVR_STREAM_INFO), &dwStatus, m_pStruRecordPassBackSchCfg, sizeof(NET_DVR_RECORD_PASSBACK_SCH_CFG)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_RECORD_PASSBACK_PLAN_CFG SUCC");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_RECORD_PASSBACK_PLAN_CFG Failed");
        g_StringLanType(szLan, "设置录像回传计划失败", "set Failed");
        AfxMessageBox(szLan);
	}
}



void CDlgRecPassBack::OnBnClickedBtnRecordPassBackSetupHistory()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgRecPassBackHistorySchdule dlg;
    dlg.m_pStruRecordPassBackHistoryPlanCfg = m_pStruRecordPassBackHistoryPlanCfg;
    if (dlg.DoModal() == IDOK)
    {

    }
}


void CDlgRecPassBack::OnBnClickedBtnPassBackSchedGetHistory()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    NET_DVR_STREAM_INFO struStreamInfo = { 0 };
    struStreamInfo.dwSize = sizeof(struStreamInfo);
    strncpy((char *)struStreamInfo.byID, m_strStreamIDHistory.GetBuffer(0), STREAM_ID_LEN);
    struStreamInfo.dwChannel = m_dwHistoryChannelPlan;

    m_pStruRecordPassBackHistoryPlanCfg->dwSize = sizeof(*m_pStruRecordPassBackHistoryPlanCfg);

    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &struStreamInfo;
    struCfg.dwCondSize = sizeof(struStreamInfo);
    struCfg.lpOutBuffer = (void*)m_pStruRecordPassBackHistoryPlanCfg;
    struCfg.dwOutSize = sizeof(*m_pStruRecordPassBackHistoryPlanCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if (!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_RECORD_PASSBACK_HISTORY_PLAN_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_RECORD_PASSBACK_HISTORY_PLAN_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_RECORD_PASSBACK_HISTORY_PLAN_CFG");
        m_bRecPassbackHistory = m_pStruRecordPassBackHistoryPlanCfg->byEnable;
    }

    UpdateData(FALSE);
    OnBnClickedChkRecordPassBackHistory();
}


void CDlgRecPassBack::OnBnClickedBtnPassBackSchedSetHistory()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    NET_DVR_STREAM_INFO struStreamInfo = { 0 };
    struStreamInfo.dwSize = sizeof(struStreamInfo);
    strncpy((char *)struStreamInfo.byID, m_strStreamIDHistory.GetBuffer(0), STREAM_ID_LEN);
    struStreamInfo.dwChannel = m_dwHistoryChannelPlan;

    m_pStruRecordPassBackHistoryPlanCfg->dwSize = sizeof(*m_pStruRecordPassBackHistoryPlanCfg);
    m_pStruRecordPassBackHistoryPlanCfg->byEnable = m_bRecPassbackHistory;

    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &struStreamInfo;
    struCfg.dwCondSize = sizeof(struStreamInfo);
    struCfg.lpInBuffer = (void*)m_pStruRecordPassBackHistoryPlanCfg;
    struCfg.dwInSize = sizeof(*m_pStruRecordPassBackHistoryPlanCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lUserID, NET_DVR_SET_RECORD_PASSBACK_HISTORY_PLAN_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_RECORD_PASSBACK_HISTORY_PLAN_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_RECORD_PASSBACK_HISTORY_PLAN_CFG");
    }

    UpdateData(FALSE);
}


void CDlgRecPassBack::OnBnClickedChkRecordPassBackHistory()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    if (m_bRecPassbackHistory)
    {
        GetDlgItem(IDC_BTN_RECORD_PASS_BACK_SETUP_HISTORY)->EnableWindow(TRUE);
    }
    else
    {
        GetDlgItem(IDC_BTN_RECORD_PASS_BACK_SETUP_HISTORY)->EnableWindow(FALSE);
    }
}

void CDlgRecPassBack::OnBnClickedBtnPassBackSchedGet2()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgRecPassbackTaskExecutable dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}
