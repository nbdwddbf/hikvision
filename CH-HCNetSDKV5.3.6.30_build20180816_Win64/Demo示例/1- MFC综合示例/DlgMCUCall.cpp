// DlgMCUCall.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMCUCall.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUCall dialog

#define WM_MSG_ADD_LIST 1110
void Test(NET_DVR_STD_CONFIG *); 

UINT __cdecl  fQueryCallRecord(LPVOID pParam)
{
	CDlgMCUCall *pDlg = (CDlgMCUCall *)pParam; 
	pDlg->QueryNextResult(); 
	return 0; 
}

CDlgMCUCall::CDlgMCUCall(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMCUCall::IDD, pParent)
	, m_dwChannel(0)
	, m_bSimulate(FALSE)
	, m_bDigital(FALSE)
	, m_dwSimulate(0)
	, m_dwDigital(0)
	, m_csGainType(_T(""))
	, m_bHMS(FALSE)
	, m_dwSity(0)
	, m_HMSTime(0)
    , m_CallRate(0)
{
	//{{AFX_DATA_INIT(CDlgMCUCall)
	m_csTerminalUrl = _T("");
	m_byVolumn = 0;
	m_chkMute = FALSE;
	m_DisableAudioInput = FALSE;
	m_csSearchID = _T("");
	m_dwMaxCount = 0;
	m_dwSearchPos = 0;
	m_csResultStatus = _T("");
	m_byVolumeIn = 0;
	//}}AFX_DATA_INIT
	m_pProcThread = NULL;
	memset(&m_struQueryCond, 0, sizeof(m_struQueryCond));
	m_struQueryCond.dwSize = sizeof(m_struQueryCond);
	memset(&m_struQueryResult, 0, sizeof(m_struQueryResult));
	m_struQueryResult.dwSize = sizeof(m_struQueryResult);
	memset(m_struQuerySingle, 0, sizeof(m_struQuerySingle));
}


void CDlgMCUCall::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgMCUCall)
    DDX_Control(pDX, IDC_LST_CALLQUERY_RESULT, m_lstResult);
    DDX_Control(pDX, IDC_COMB_CALL_QUERY_CALLTYPE, m_cmbCallType);
    DDX_Control(pDX, IDC_COMB_CALL_PROTOCOLTYPE, m_cmbProtoType);
    DDX_Control(pDX, IDC_COMB_CALL_ANSWERTYPE, m_cmbAnswerType);
    DDX_Control(pDX, IDC_COMB_CALL_OPERATIONTYPE, m_cmbOperateType);
    DDX_Text(pDX, IDC_EDT_TERMINAL_URL, m_csTerminalUrl);
    DDX_Text(pDX, IDC_EDT_VOLUMN, m_byVolumn);
    DDX_Check(pDX, IDC_CHK_MUTE, m_chkMute);
    DDX_Check(pDX, IDC_CHK_DISABLE_AUDIOINPUT, m_DisableAudioInput);
    DDX_Text(pDX, IDC_EDT_CALLQUERY_SERACHID, m_csSearchID);
    DDX_Text(pDX, IDC_EDT_MAXCOUNT, m_dwMaxCount);
    DDV_MinMaxDWord(pDX, m_dwMaxCount, 0, 256);
    DDX_Text(pDX, IDC_EDT_SEARCHPOS, m_dwSearchPos);
    DDX_DateTimeCtrl(pDX, IDC_DATE_CALLQUERY_START, m_dtStart);
    DDX_DateTimeCtrl(pDX, IDC_DATE_CALLQUERY_STOP, m_dtStop);
    DDX_DateTimeCtrl(pDX, IDC_TIME_CALLQUERY_START, m_tStart);
    DDX_DateTimeCtrl(pDX, IDC_TIME_CALLQUERY_STOP, m_tStop);
    DDX_Text(pDX, IDC_EDT_CALLQUERY_RESULTSTATUS, m_csResultStatus);
    DDX_Text(pDX, IDC_EDIT_VOLUMN_IN, m_byVolumeIn);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDT_CHANNEL, m_dwChannel);
    DDX_Control(pDX, IDC_COMB_GAIN_TYPE, m_ctrlGainType);
    DDX_Check(pDX, IDC_CHK_SIMULATE, m_bSimulate);
    DDX_Check(pDX, IDC_CHK_DIGITAL, m_bDigital);
    DDX_Text(pDX, IDC_EDT_SIMULATE, m_dwSimulate);
    DDX_Text(pDX, IDC_EDIT_DIGITAL, m_dwDigital);
    DDX_CBString(pDX, IDC_COMB_GAIN_TYPE, m_csGainType);
    DDX_Check(pDX, IDC_CHK_HMS, m_bHMS);
    DDX_Text(pDX, IDC_EDT_SIMITY, m_dwSity);
    DDX_Text(pDX, IDC_EDT_TIME, m_HMSTime);
    DDX_Control(pDX, IDC_COMB_HMS_TYPE, m_cmbHMSType);
    DDX_Text(pDX, IDC_EDIT_CALLRATE, m_CallRate);
    DDX_Control(pDX, IDC_COMB_TRANSMISSION_PROTOCOLTYPE, m_comboTransmissionProtocol);
}


BEGIN_MESSAGE_MAP(CDlgMCUCall, CDialog)
	//{{AFX_MSG_MAP(CDlgMCUCall)
	ON_BN_CLICKED(IDC_BUT_CONTROL_SET, OnButControlSet)
	ON_BN_CLICKED(IDC_BUT_CONTROL_CALLCFG_GET, OnButCallcfgGet)
	ON_BN_CLICKED(IDC_BUT_CONTROL_CALLCFG_SET, OnButCallcfgSet)
	ON_BN_CLICKED(IDC_BUT_CONTROL_CALLCFG_QUERY, OnButCallcfgQuery)
	ON_MESSAGE(WM_MSG_ADD_LIST,AddList)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMCUCall message handlers

void CDlgMCUCall::OnButControlSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
	NET_DVR_TERMINAL_CTRL_PARAM struCallCtrl = {0}; 
	struCallCtrl.dwSize = sizeof(struCallCtrl); 
	struCallCtrl.byOperateType = m_cmbOperateType.GetCurSel()+1; 
	switch (struCallCtrl.byOperateType)
	{
	case 3:
		strncpy((char *)struCallCtrl.struCtrlParam.struCallInfo.byTermianlURL, (LPCSTR)m_csTerminalUrl, sizeof(struCallCtrl.struCtrlParam.struCallInfo.byTermianlURL));
        struCallCtrl.struCtrlParam.struCallInfo.dwCallRate = m_CallRate;
		break; 
	case 4:
		struCallCtrl.struCtrlParam.struAudioCtrl.byVolume = m_byVolumn; 
		struCallCtrl.struCtrlParam.struAudioCtrl.byMute = m_chkMute; 
		struCallCtrl.struCtrlParam.struAudioCtrl.byAudioInputDisabled = m_DisableAudioInput;
        struCallCtrl.struCtrlParam.struAudioCtrl.byAudioInputVolume = m_byVolumeIn;
		break; 
	case 8:
		struCallCtrl.struCtrlParam.struInputAudio.dwChannel = m_dwChannel;
		struCallCtrl.struCtrlParam.struInputAudio.byGainType = m_ctrlGainType.GetCurSel()+1;
		struCallCtrl.struCtrlParam.struInputAudio.byEnableDigital = m_bDigital;
		struCallCtrl.struCtrlParam.struInputAudio.byVolumeDigital = m_dwDigital;
		struCallCtrl.struCtrlParam.struInputAudio.byEnableSimulate = m_bSimulate;
		struCallCtrl.struCtrlParam.struInputAudio.byVolumeSimulate = m_dwSimulate;
		struCallCtrl.struCtrlParam.struInputAudio.struHsParam.byEnabled = m_bHMS;
		struCallCtrl.struCtrlParam.struInputAudio.struHsParam.byHsMode = m_cmbHMSType.GetCurSel();
		struCallCtrl.struCtrlParam.struInputAudio.struHsParam.byHsSensibility = m_dwSity;
		struCallCtrl.struCtrlParam.struInputAudio.struHsParam.dwHsTime = m_HMSTime;
	}
	NET_DVR_STD_CONTROL struSTDControl = {0}; 
	struSTDControl.lpCondBuffer = &struCallCtrl; 
	struSTDControl.dwCondSize = sizeof(struCallCtrl);
	
	if (!NET_DVR_STDControl(m_lUserID, NET_DVR_TERMINAL_CTRL, &struSTDControl))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_TERMINAL_CTRL");
		return ; 
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_TERMINAL_CTRL");
}

BOOL CDlgMCUCall::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex(); 
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID; 

	char szLan[128]; 
	m_lstResult.SetExtendedStyle(m_lstResult.GetExtendedStyle()|LVS_EX_FULLROWSELECT);
    g_StringLanType(szLan, "序号", "Index.");
	m_lstResult.InsertColumn(0, szLan, LVCFMT_LEFT,40, -1);	
	g_StringLanType(szLan, "呼叫类型", "Call Type");
	m_lstResult.InsertColumn(1, szLan,LVCFMT_LEFT,60,-1);
	g_StringLanType(szLan, "对端终端名", "Terminal Name");
    m_lstResult.InsertColumn(2, szLan, LVCFMT_LEFT,100,-1);
	g_StringLanType(szLan, "对端URL地址", "Address Url");
    m_lstResult.InsertColumn(3, szLan, LVCFMT_LEFT,100,-1);	
	g_StringLanType(szLan, "呼叫开始", "Call Start");
	m_lstResult.InsertColumn(4, szLan,LVCFMT_LEFT,100,-1);
	g_StringLanType(szLan, "呼叫结束", "Call End");
	m_lstResult.InsertColumn(5, szLan,LVCFMT_LEFT,100,-1);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMCUCall::OnButCallcfgGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_TERMINAL_CALL_CFG struCallCfg = {0}; 
	struCallCfg.dwSize = sizeof(struCallCfg);
	NET_DVR_STD_CONFIG struConfig = {0}; 
	struConfig.lpOutBuffer = &struCallCfg; 
	struConfig.dwOutSize = sizeof(struCallCfg);
	if (!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_TERMINAL_CALL_CFG, &struConfig))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_TERMINAL_CALL_CFG");
		return ; 
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_TERMINAL_CALL_CFG");
	m_cmbAnswerType.SetCurSel(struCallCfg.byAnswerType-1);
	m_cmbProtoType.SetCurSel(struCallCfg.byProtocolType-1); 
    m_comboTransmissionProtocol.SetCurSel(struCallCfg.byTransmissionProtocol);
	UpdateData(FALSE); 
}

void CDlgMCUCall::OnButCallcfgSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_TERMINAL_CALL_CFG struCallCfg = {0}; 
	struCallCfg.dwSize = sizeof(struCallCfg); 
	struCallCfg.byAnswerType = m_cmbAnswerType.GetCurSel()+1; 
	struCallCfg.byProtocolType = m_cmbProtoType.GetCurSel()+1; 
    struCallCfg.byTransmissionProtocol = m_comboTransmissionProtocol.GetCurSel();
	
	NET_DVR_STD_CONFIG struConfig = {0}; 
	struConfig.lpInBuffer = &struCallCfg; 
	struConfig.dwInSize = sizeof(struCallCfg);
	if (!NET_DVR_SetSTDConfig(m_lUserID, NET_DVR_SET_TERMINAL_CALL_CFG, &struConfig))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_TERMINAL_CALL_CFG");
		return ; 
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_TERMINAL_CALL_CFG");
}

void CDlgMCUCall::DrawList(const NET_DVR_CALL_QUERY_RESULT &struQueryResult, BOOL bRedraw)
{
	UpdateData(TRUE); 
	int insertPos = m_lstResult.GetItemCount(); 
	if ( bRedraw )
	{
		insertPos = 0; 
		m_lstResult.DeleteAllItems(); 
	}

	CString csTmp; 
	LPNET_DVR_CALL_QUERY_SINGLE lpQuerySingle = NULL;
	char *pCallType[] = {"未知值", "已接", "未接", "已拨"}; 
	for (int i=insertPos; i< struQueryResult.dwCount+insertPos; i++)
	{
		lpQuerySingle = (LPNET_DVR_CALL_QUERY_SINGLE)(struQueryResult.pResults+i*sizeof(NET_DVR_CALL_QUERY_SINGLE));
		csTmp.Format("%d", i+1); 
		m_lstResult.InsertItem(i, csTmp); 
		csTmp.Format("%s(%d)", pCallType[lpQuerySingle->byCallType%4], lpQuerySingle->byCallType);
		m_lstResult.SetItemText(i, 1, csTmp);
		csTmp = (char *)lpQuerySingle->byTerminalName;
		m_lstResult.SetItemText(i, 2, csTmp);
		csTmp = (char *)lpQuerySingle->byAddressURL;
		m_lstResult.SetItemText(i, 3, csTmp);
		LPNET_DVR_TIME lpTime = &lpQuerySingle->struStartTime;
		csTmp.Format("%4d-%02d-%02d %02d:%02d:%02d", lpTime->dwYear, lpTime->dwMonth, lpTime->dwDay, lpTime->dwHour, lpTime->dwMinute, lpTime->dwSecond); 
		m_lstResult.SetItemText(i, 4, csTmp);
		lpTime = &lpQuerySingle->struEndTime;
		csTmp.Format("%4d-%02d-%02d %02d:%02d:%02d", lpTime->dwYear, lpTime->dwMonth, lpTime->dwDay, lpTime->dwHour, lpTime->dwMinute, lpTime->dwSecond); 
		m_lstResult.SetItemText(i, 5, csTmp);
	}
	char *pResultStatus[] = {"OK", "FAIL", "MORE", "NOMATCH", "PARAMERROR", "INVALIDTIME", "TIMEOUT"}; 
	m_csResultStatus = (char *)pResultStatus[struQueryResult.byStatus%7]; 
	UpdateData(FALSE); 
} 

void CDlgMCUCall::OnButCallcfgQuery() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_CALL_QUERY_COND &struQueryCond = m_struQueryCond;
	struQueryCond.dwSize = sizeof(struQueryCond);
	struQueryCond.byCallType = m_cmbCallType.GetCurSel()+1; 
	strncpy((char *)struQueryCond.bySearchID, (LPCSTR)m_csSearchID, sizeof(struQueryCond.bySearchID));
	struQueryCond.dwMaxResults = m_dwMaxCount; 
	struQueryCond.dwSearchPos = m_dwSearchPos; 
	struQueryCond.struStartTime.dwYear = m_dtStart.GetYear();
	struQueryCond.struStartTime.dwMonth = m_dtStart.GetMonth();
	struQueryCond.struStartTime.dwDay = m_dtStart.GetDay();
	struQueryCond.struStartTime.dwHour = m_tStart.GetHour(); 
	struQueryCond.struStartTime.dwMinute = m_tStart.GetMinute(); 
	struQueryCond.struStartTime.dwSecond = m_tStart.GetSecond(); 

	struQueryCond.struEndTime.dwYear = m_dtStop.GetYear();
	struQueryCond.struEndTime.dwMonth = m_dtStop.GetMonth();
	struQueryCond.struEndTime.dwDay = m_dtStop.GetDay();
	struQueryCond.struEndTime.dwHour = m_tStop.GetHour(); 
	struQueryCond.struEndTime.dwMinute = m_tStop.GetMinute(); 
	struQueryCond.struEndTime.dwSecond = m_tStop.GetSecond(); 

	
	NET_DVR_CALL_QUERY_RESULT  &struResult = m_struQueryResult;
	struResult.dwSize = sizeof(struResult);
	struResult.pResults = (BYTE *)m_struQuerySingle;
	memset(m_struQuerySingle, 0, sizeof(m_struQuerySingle));
	NET_DVR_STD_CONFIG struConfig = {0}; 
	struConfig.lpCondBuffer = &struQueryCond; 
	struConfig.dwCondSize = sizeof(struQueryCond);
	struConfig.lpOutBuffer = &struResult; 
	struConfig.dwOutSize = sizeof(struResult);
	if (! NET_DVR_GetSTDConfig(m_lUserID,NET_DVR_GET_CALLINFO_BY_COND, &struConfig) )
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_CALLINFO_BY_COND");
		return ; 
	}

	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_CALLINFO_BY_COND");
	DrawList(struResult);
	//如果还有更多开线程获取
	if ( struResult.byStatus != CALL_QUERY_RESULT_MORE)
	{
		return ; 
	}
	m_pProcThread = AfxBeginThread(fQueryCallRecord,this,THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED,NULL);
	if (m_pProcThread != NULL)
	{
		m_pProcThread->m_bAutoDelete = FALSE;
		m_pProcThread->ResumeThread();
	}
}

void CDlgMCUCall::QueryNextResult()
{
	NET_DVR_CALL_QUERY_RESULT struResut;
	memcpy(&struResut, &m_struQueryResult, sizeof(m_struQueryResult));

	NET_DVR_STD_CONFIG struConfig = {0}; 
	struConfig.lpCondBuffer = &m_struQueryCond; 
	struConfig.dwCondSize = sizeof(m_struQueryCond);
	struConfig.lpOutBuffer = &struResut; 
	struConfig.dwOutSize = sizeof(struResut);
	while (struResut.byStatus == CALL_QUERY_RESULT_MORE )
	{
		memcpy(m_struQueryCond.bySearchID, struResut.bySearchID, sizeof(struResut.bySearchID));
		m_struQueryCond.dwSearchPos += struResut.dwCount; 
		if (! NET_DVR_GetSTDConfig(m_lUserID,NET_DVR_GET_CALLINFO_BY_COND, &struConfig) )
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_CALLINFO_BY_COND");
			return ; 
		}
		char *pResultStatus[] = {"OK", "FAIL", "MORE", "NOMATCH", "PARAMERROR", "INVALIDTIME", "TIMEOUT"}; 
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_CALLINFO_BY_COND %d %s",  struResut.dwCount, pResultStatus[struResut.byStatus]);
		memcpy(&m_struQueryResult, &struResut, sizeof(struResut));
		m_struQueryResult.pResults = (BYTE *)m_struQuerySingleForDraw;
		memcpy(m_struQuerySingleForDraw, m_struQuerySingle, struResut.dwCount*sizeof(m_struQuerySingle[0]));
		PostMessage(WM_MSG_ADD_LIST, (WPARAM)&m_struQueryResult,0);
	}
	
}


LRESULT CDlgMCUCall::AddList(WPARAM wParam,LPARAM lParam)
{
	DrawList(m_struQueryResult, FALSE); 
	return 0; 
}

void CDlgMCUCall::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if (m_pProcThread != NULL)
	{   	
		DWORD dwExitCode = 0;
		if (GetExitCodeThread(m_pProcThread->m_hThread,&dwExitCode) && dwExitCode == STILL_ACTIVE)
		{   
			TerminateThread(m_pProcThread->m_hThread,0);
		}		
	}
	CDialog::OnClose();
}


void Test(NET_DVR_STD_CONFIG *lpConfig)
{
	static int count = 0; 
	LPNET_DVR_CALL_QUERY_RESULT struResut = (LPNET_DVR_CALL_QUERY_RESULT)lpConfig->lpOutBuffer;
	struResut->dwCount = 5; 
	if ( (count++)%2 == 0)
	{
		struResut->byStatus = CALL_QUERY_RESULT_MORE;
	}
	else 
		struResut->byStatus = CALL_QUERY_RESULT_OK;
	LPNET_DVR_CALL_QUERY_SINGLE lpq = (LPNET_DVR_CALL_QUERY_SINGLE)struResut->pResults;
	for (int i=0; i<struResut->dwCount; i++)
	{
		strcpy((char *)struResut->bySearchID, "Test1"); 
		sprintf((char *)lpq->byAddressURL, "Address_%d", i+count);
		sprintf((char *)lpq->byTerminalName, "Name_%d", i+count);
		lpq->byCallType = 1; 
	}
}
