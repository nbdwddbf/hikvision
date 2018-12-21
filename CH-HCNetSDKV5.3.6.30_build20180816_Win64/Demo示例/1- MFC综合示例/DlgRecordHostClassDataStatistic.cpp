// DlgRecordHostClassDataStatistic.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgRecordHostClassDataStatistic.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"


// CDlgRecordHostClassDataStatistic 对话框

IMPLEMENT_DYNAMIC(CDlgRecordHostClassDataStatistic, CDialogEx)

void CALLBACK g_fGetStatisticDataCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData);
#define WM_MSG_GETDATA_FINISH 1002
#define WM_MSG_ADD_DATA_TOLIST 1003

CDlgRecordHostClassDataStatistic::CDlgRecordHostClassDataStatistic(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRecordHostClassDataStatistic::IDD, pParent)
	, m_bEnable(FALSE)
	, m_ctStartTime(0)
	, m_ctEndTime(0)
	, m_lUserID(-1)
	, m_iDeviceIndex(-1)
	, m_lGetStatisticDataHandle(-1)
	, m_ctStartDate(0)
	, m_ctEndDate(0)
{

}

CDlgRecordHostClassDataStatistic::~CDlgRecordHostClassDataStatistic()
{
}

void CDlgRecordHostClassDataStatistic::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
	DDX_Control(pDX, IDC_COMBO_TARGET_TYPE, m_comTargetType);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START_TIME, m_ctStartTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_END_TIME, m_ctEndTime);
	DDX_Control(pDX, IDC_LIST_STATISTIC_DATA, m_listStatisticData);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START_DATE, m_ctStartDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_END_DATE, m_ctEndDate);
}


BEGIN_MESSAGE_MAP(CDlgRecordHostClassDataStatistic, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CDlgRecordHostClassDataStatistic::OnBnClickedButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_GET, &CDlgRecordHostClassDataStatistic::OnBnClickedButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CDlgRecordHostClassDataStatistic::OnBnClickedButtonSearch)
	ON_MESSAGE(WM_MSG_GETDATA_FINISH, OnMsgGetStatisticDataFinish)
	ON_MESSAGE(WM_MSG_ADD_DATA_TOLIST, OnMsgAddStatisticDataToList)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


void CALLBACK g_fGetStatisticDataCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
	CDlgRecordHostClassDataStatistic *pDlg = (CDlgRecordHostClassDataStatistic *)pUserData;
	if (pDlg == NULL)
	{
		return;
	}
	pDlg->ProcessGetStatisticDataCallbackData(dwType, lpBuffer, dwBufLen);
}

// CDlgRecordHostClassDataStatistic 消息处理程序

BOOL CDlgRecordHostClassDataStatistic::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	InitStatisticDataList();

	char szLan[64] = { 0 };
	g_StringLanType(szLan, "统计所有对象", "allTarget");
	m_comTargetType.InsertString(0, szLan);
	g_StringLanType(szLan, "PPT报警", "pptTargetAlarm");
	m_comTargetType.InsertString(1, szLan);
	g_StringLanType(szLan, "PPT视图", "pptTargetView");
	m_comTargetType.InsertString(2, szLan);
	g_StringLanType(szLan, "单个学生报警", "studentSingleAlarm");
	m_comTargetType.InsertString(3, szLan);
	g_StringLanType(szLan, "单个学生视图", "studentSingleView");
	m_comTargetType.InsertString(4, szLan);
	g_StringLanType(szLan, "多个学生报警", "studentMultAlarm");
	m_comTargetType.InsertString(5, szLan);
	g_StringLanType(szLan, "多个学生视图", "studentMultView");
	m_comTargetType.InsertString(6, szLan);
	g_StringLanType(szLan, "师生互动视图", "studentTeacherView");
	m_comTargetType.InsertString(7, szLan);
	g_StringLanType(szLan, "教师上下讲台", "teacherUpDownAlarm");
	m_comTargetType.InsertString(8, szLan);
	g_StringLanType(szLan, "教师授课视图", "teacherStartView");
	m_comTargetType.InsertString(9, szLan);
	g_StringLanType(szLan, "书写板书报警", "blackboardWriteAlarm");
	m_comTargetType.InsertString(10, szLan);
	g_StringLanType(szLan, "书写板书视图", "blackboardWriteView");
	m_comTargetType.InsertString(11, szLan);
	g_StringLanType(szLan, "教师全景视图", "teacherFullView");
	m_comTargetType.InsertString(12, szLan);
	g_StringLanType(szLan, "教师开始授课报警", "teacherStartAlarm");
	m_comTargetType.InsertString(13, szLan);
	g_StringLanType(szLan, "教师走动报警", "teacherWalkAlarm");
	m_comTargetType.InsertString(14, szLan);
	g_StringLanType(szLan, "教师离开报警", "teacherLeftAlarm");
	m_comTargetType.InsertString(15, szLan);
	g_StringLanType(szLan, "教师奔跑报警", "teacherRunAlarm");
	m_comTargetType.InsertString(16, szLan);
	g_StringLanType(szLan, "教师多人报警", "teacherMultAlarm");
	m_comTargetType.InsertString(17, szLan);
	m_comTargetType.SetCurSel(0);

	CTime timeCur = CTime::GetCurrentTime();
	CTime timeStart(timeCur.GetYear(), timeCur.GetMonth(), timeCur.GetDay(), 0, 0, 0);
	CTime timeStop(timeCur.GetYear(), timeCur.GetMonth(), timeCur.GetDay(), 23, 59, 59);
	m_ctStartDate = timeStart;
	m_ctStartTime = timeStart;
	m_ctEndDate = timeStop;
	m_ctEndTime = timeStop;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRecordHostClassDataStatistic::InitStatisticDataList()
{
	char szLan[128] = { 0 };
	
	m_listStatisticData.SetExtendedStyle(m_listStatisticData.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	g_StringLanType(szLan, "事件序号", "EventNo");
	m_listStatisticData.InsertColumn(0, szLan, LVCFMT_CENTER, 30);
	g_StringLanType(szLan, "统计对象类型", "StatisticTargetType");
	m_listStatisticData.InsertColumn(1, szLan, LVCFMT_CENTER, 100);
	g_StringLanType(szLan, "事件开始时间", "EventStartTime");
	m_listStatisticData.InsertColumn(2, szLan, LVCFMT_CENTER, 150);
	g_StringLanType(szLan, "事件结束时间", "EventStopTime");
	m_listStatisticData.InsertColumn(3, szLan, LVCFMT_CENTER, 150);
}

LRESULT CDlgRecordHostClassDataStatistic::OnMsgGetStatisticDataFinish(WPARAM wParam, LPARAM lParam)
{
	NET_DVR_StopRemoteConfig(m_lGetStatisticDataHandle);
	m_lGetStatisticDataHandle = -1;
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_STATISTIC_DATA Get finish");
	return 0;
}

LRESULT CDlgRecordHostClassDataStatistic::OnMsgAddStatisticDataToList(WPARAM wParam, LPARAM lParam)
{
	UpdateData(TRUE);
	char szLan[128] = { 0 };
	int iIndex = m_listStatisticData.GetItemCount();
	LPNET_DVR_STATISTIC_DATA_CFG lpStatisticData = (LPNET_DVR_STATISTIC_DATA_CFG)wParam;
	if (lpStatisticData->dwSize == 0)
	{
		return 0;
	}
	CString strItem = "";
	strItem.Format("%d", iIndex + 1);
	m_listStatisticData.InsertItem(iIndex, strItem);
	switch (lpStatisticData->dwTypeTarget)
	{
	case 0:
		g_StringLanType(szLan, "统计所有对象", "allTarget");
		break;
	case 1:
		g_StringLanType(szLan, "PPT报警", "pptTargetAlarm");
		break;
	case 2:
		g_StringLanType(szLan, "PPT视图", "pptTargetView");
		break;
	case 3:
		g_StringLanType(szLan, "单个学生报警", "studentSingleAlarm");
		break;
	case 4:
		g_StringLanType(szLan, "单个学生视图", "studentSingleView");
		break;
	case 5:
		g_StringLanType(szLan, "多个学生报警", "studentMultAlarm");
		break;
	case 6:
		g_StringLanType(szLan, "多个学生视图", "studentMultView");
		break;
	case 7:
		g_StringLanType(szLan, "师生互动视图", "studentTeacherView");
		break;
	case 8:
		g_StringLanType(szLan, "教师上下讲台", "teacherUpDownAlarm");
		break;
	case 9:
		g_StringLanType(szLan, "教师授课视图", "teacherStartView");
		break;
	case 10:
		g_StringLanType(szLan, "书写板书报警", "blackboardWriteAlarm");
		break;
	case 11:
		g_StringLanType(szLan, "书写板书视图", "blackboardWriteView");
		break;
	case 12:
		g_StringLanType(szLan, "教师全景视图", "teacherFullView");
		break;
	case 13:
		g_StringLanType(szLan, "教师开始授课报警", "teacherStartAlarm");
		break;
	case 14:
		g_StringLanType(szLan, "教师走动报警", "teacherWalkAlarm");
		break;
	case 15:
		g_StringLanType(szLan, "教师离开报警", "teacherLeftAlarm");
		break;
	case 16:
		g_StringLanType(szLan, "教师奔跑报警", "teacherRunAlarm");
		break;
	case 17:
		g_StringLanType(szLan, "教师多人报警", "teacherMultAlarm");
		break;
	default:
		break;
	}
	m_listStatisticData.SetItemText(iIndex, 1, szLan);
	const NET_DVR_TIME *lpTime = &lpStatisticData->struStartTime;
	strItem.Format("%d-%d-%d, %2d:%2d:%2d", lpTime->dwYear, lpTime->dwMonth, lpTime->dwDay, lpTime->dwHour, lpTime->dwMinute, lpTime->dwSecond);
	m_listStatisticData.SetItemText(iIndex, 2, strItem);
	lpTime = &lpStatisticData->struStopTime;
	strItem.Format("%d-%d-%d, %2d:%2d:%2d", lpTime->dwYear, lpTime->dwMonth, lpTime->dwDay, lpTime->dwHour, lpTime->dwMinute, lpTime->dwSecond);
	m_listStatisticData.SetItemText(iIndex, 3, strItem);
	UpdateData(FALSE);
	delete lpStatisticData;
	return 0;
}

void CDlgRecordHostClassDataStatistic::ProcessGetStatisticDataCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{
	CString strItem = "";
	if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
	{
		LPNET_DVR_STATISTIC_DATA_CFG lpDataCfg = new NET_DVR_STATISTIC_DATA_CFG;
		memcpy(lpDataCfg, lpBuffer, sizeof(*lpDataCfg));
		PostMessage(WM_MSG_ADD_DATA_TOLIST, (WPARAM)lpDataCfg, 0);
	}
	else if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
	{
		DWORD dwStatus = *(DWORD*)lpBuffer;
		if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
		{
			PostMessage(WM_MSG_GETDATA_FINISH, 0, 0);
		}
		else if (dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "GetStatisticData STATUS_FAILED, Error code %d", NET_DVR_GetLastError());
		}
	}
}

BOOL CDlgRecordHostClassDataStatistic::CreateClassDataControl(char* pBuf, DWORD dwBufLen, int &dwRet)
{
	CXmlBase xmlBase;
	xmlBase.CreateRoot("ClassDataControl");
	xmlBase.SetAttribute("version", "2.0");
	if (m_bEnable)
	{
		xmlBase.AddNode("enabled", "true");
	}
	else
	{
		xmlBase.AddNode("enabled", "false");
	}
	xmlBase.OutOfElem();

	return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}

void CDlgRecordHostClassDataStatistic::OnBnClickedButtonSet()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	DWORD dwBufLen = 10 * 1024;
	char *pBuf = new char[dwBufLen];
	memset(pBuf, 0, dwBufLen);
	int dwXmlLen = 0;
	if (!CreateClassDataControl(pBuf, dwBufLen, dwXmlLen))
	{
		delete[]pBuf;
		pBuf = NULL;
		return;
	}

	char szUrl[256] = { 0 };
	sprintf(szUrl, "PUT /ISAPI/ContentMgmt/RecordingHost/ClassDataControl\r\n");
	NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
	NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
	struInput.dwSize = sizeof(struInput);
	struOuput.dwSize = sizeof(struOuput);
	struInput.lpRequestUrl = szUrl;
	struInput.dwRequestUrlLen = strlen(szUrl);
	struInput.lpInBuffer = pBuf;
	struInput.dwInBufferSize = dwXmlLen;
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szUrl);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);
	}
	UpdateData(FALSE);
	delete[]pBuf;
	pBuf = NULL;
}


void CDlgRecordHostClassDataStatistic::OnBnClickedButtonGet()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	NET_DVR_XML_CONFIG_INPUT    struInput = {0};
	NET_DVR_XML_CONFIG_OUTPUT   struOuput = {0};
	struInput.dwSize = sizeof(struInput);
	struOuput.dwSize = sizeof(struOuput);
	struInput.lpRequestUrl = "GET /ISAPI/ContentMgmt/RecordingHost/ClassDataControl\r\n";
	struInput.dwRequestUrlLen = strlen("GET /ISAPI/ContentMgmt/RecordingHost/ClassDataControl\r\n");
	DWORD dwOutputLen = 1024 * 1024;
	char *pOutBuf = new char[dwOutputLen];
	memset(pOutBuf, 0, dwOutputLen);
	struOuput.lpOutBuffer = pOutBuf;
	struOuput.dwOutBufferSize = dwOutputLen;

	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "GET /ISAPI/ContentMgmt/RecordingHost/ClassDataControl\r\n");
		delete[]pOutBuf;
		pOutBuf = NULL;
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "GET /ISAPI/ContentMgmt/RecordingHost/ClassDataControl\r\n");
	}

	CXmlBase xmlBase;
	xmlBase.Parse(pOutBuf);
	if (xmlBase.FindElem("ClassDataControl") && xmlBase.IntoElem())
	{
		if (xmlBase.FindElem("enabled"))
		{
			if (xmlBase.GetData().compare("true") == 0)
			{
				m_bEnable = TRUE;
			}
			else if (xmlBase.GetData().compare("false") == 0)
			{
				m_bEnable = FALSE;
			}
		}
	}
	UpdateData(FALSE);

	delete[]pOutBuf;
	pOutBuf = NULL;

	return;
}


void CDlgRecordHostClassDataStatistic::OnBnClickedButtonSearch()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_lGetStatisticDataHandle != -1)
	{
		NET_DVR_StopRemoteConfig(m_lGetStatisticDataHandle);
	}
	m_listStatisticData.DeleteAllItems();
	UpdateData(TRUE);
	NET_DVR_STATISTIC_DATA_COND struStatisticDataCond = { 0 };
	struStatisticDataCond.dwSize = sizeof(struStatisticDataCond);
	struStatisticDataCond.dwTypeTarget = m_comTargetType.GetCurSel();
	struStatisticDataCond.struStartTime.dwYear = m_ctStartDate.GetYear();
	struStatisticDataCond.struStartTime.dwMonth = m_ctStartDate.GetMonth();
	struStatisticDataCond.struStartTime.dwDay = m_ctStartDate.GetDay();
	struStatisticDataCond.struStartTime.dwHour = m_ctStartTime.GetHour();
	struStatisticDataCond.struStartTime.dwMinute = m_ctStartTime.GetMinute();
	struStatisticDataCond.struStartTime.dwSecond = m_ctStartTime.GetSecond();

	struStatisticDataCond.struStopTime.dwYear = m_ctEndDate.GetYear();
	struStatisticDataCond.struStopTime.dwMonth = m_ctEndDate.GetMonth();
	struStatisticDataCond.struStopTime.dwDay = m_ctEndDate.GetDay();
	struStatisticDataCond.struStopTime.dwHour = m_ctEndTime.GetHour();
	struStatisticDataCond.struStopTime.dwMinute = m_ctEndTime.GetMinute();
	struStatisticDataCond.struStopTime.dwSecond = m_ctEndTime.GetSecond();

	m_lGetStatisticDataHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_GET_STATISTIC_DATA_LIST, &struStatisticDataCond, sizeof(struStatisticDataCond), g_fGetStatisticDataCallback, this);
	if (m_lGetStatisticDataHandle == -1)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_STATISTIC_DATA_LIST");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_STATISTIC_DATA_LIST");
	}
}



void CDlgRecordHostClassDataStatistic::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (m_lGetStatisticDataHandle != -1)
	{
		NET_DVR_StopRemoteConfig(m_lGetStatisticDataHandle);
		m_lGetStatisticDataHandle = -1;
	}
	CDialogEx::OnClose();
}
