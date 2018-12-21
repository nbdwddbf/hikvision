// DlgInfoDiffusionSchedule.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInfoDiffusionSchedule.h"
#include "DlgInfoDiffusionRelease.h"
#include "DlgInfoDiffusionScheduleSelfdefine.h"
#include "DlgInfoDiffusionScheduleSearch.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionSchedule dialog

BOOL fExportCallBack(LONG lHandle, NET_DOWNLOAD_CB_INFO *pCBInfo, void *pUserData)
{
    CDlgInfoDiffusionSchedule *pDlg = (CDlgInfoDiffusionSchedule*)pUserData;
    if (pCBInfo->dwType == 3)
    {
        NET_DVR_SCHEDULE_FILE_RET struFile = { 0 };
        memcpy(&struFile, pCBInfo->pFileInfo, pCBInfo->dwFileInfoLen);
        char szFilePath[256] = { 0 };
        sprintf(szFilePath, "C:\\Schedule\\%s", struFile.szFileName);
        FILE *pFile = fopen(szFilePath, "wb");
        if (pFile == NULL)
        {
         //   g_pMainDlg->AddLog(pDlg->m_iDeviceIndex, OPERATION_FAIL_T, szFilePath);
            return FALSE;
        }
        fwrite(pCBInfo->pData, pCBInfo->dwDataLen, 1, pFile);
        fclose(pFile);
        pFile = NULL;
       // g_pMainDlg->AddLog(pDlg->m_iDeviceIndex, OPERATION_SUCC_T, szFilePath);
    }
    return TRUE;
}


CDlgInfoDiffusionSchedule::CDlgInfoDiffusionSchedule(CWnd* pParent /*=NULL*/)
: CDialog(CDlgInfoDiffusionSchedule::IDD, pParent)
, m_csModeType(_T(""))
, m_dwOrgNo(0)
{
    //{{AFX_DATA_INIT(CDlgInfoDiffusionSchedule)
    m_timeEndDate = COleDateTime::GetCurrentTime();
    m_timeEndTime = COleDateTime::GetCurrentTime();
    m_timeStartDate = COleDateTime::GetCurrentTime();
    m_timeStartTime = COleDateTime::GetCurrentTime();
    m_dwScheduleID = 0;
    m_szScheduleName = _T("");
    m_szScheduleRemarks = _T("");
    m_dwProgramID = 0;
    m_szApproveRemarks = _T("");
    //}}AFX_DATA_INIT
    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
    memset(&m_struSchedule, 0, sizeof(m_struSchedule));
    m_struSchedule.dwSize = sizeof(m_struSchedule);
    m_nCurSelSpan = -1;
    m_pOutputXmlBuffer = new char[MAX_LEN_XML];
    memset(m_pOutputXmlBuffer, 0, sizeof(char)*MAX_LEN_XML);
    m_bExport = FALSE;
    m_lExportHandle = -1;
    memset(&m_struSchedule, 0, sizeof(m_struSchedule));
}


void CDlgInfoDiffusionSchedule::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgInfoDiffusionSchedule)
    DDX_Control(pDX, IDC_COMBO_APPROVE, m_cmbApprove);
    DDX_Control(pDX, IDC_LIST_SPAN, m_listSpan);
    DDX_Control(pDX, IDC_COMBO_WEEKDAY, m_cmbWeekday);
    DDX_Control(pDX, IDC_COMBO_SHARE_PROP, m_cmbShareProp);
    DDX_Control(pDX, IDC_COMBO_SCHEDULE_TYPE, m_cmbScheduleType);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_END_DATE, m_timeEndDate);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_END_TIME, m_timeEndTime);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START_DATE, m_timeStartDate);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START_TIME, m_timeStartTime);
    DDX_Text(pDX, IDC_EDIT_SCHEDULE_ID, m_dwScheduleID);
    DDX_Text(pDX, IDC_EDIT_SCHEDULE_NAME, m_szScheduleName);
    DDX_Text(pDX, IDC_EDIT_SCHEDULE_REMARKS, m_szScheduleRemarks);
    DDX_Text(pDX, IDC_EDIT_PROGRAM_ID, m_dwProgramID);
    DDX_Text(pDX, IDC_EDIT_APPROVE_REMARKS, m_szApproveRemarks);
    //}}AFX_DATA_MAP
    DDX_CBString(pDX, IDC_COMBO_MODE_TYPE, m_csModeType);
    DDX_Text(pDX, IDC_EDIT_ORG_ID, m_dwOrgNo);
    DDX_Control(pDX, IDC_EXPORT_PROGRESS, m_ctrlProgress);
    DDX_Control(pDX, IDC_STATIC_PROGRESS, m_statProgress);
}


BEGIN_MESSAGE_MAP(CDlgInfoDiffusionSchedule, CDialog)
    //{{AFX_MSG_MAP(CDlgInfoDiffusionSchedule)
    ON_BN_CLICKED(IDC_BTN_SCHEDULE_DEL, OnBtnScheduleDel)
    ON_BN_CLICKED(IDC_BTN_SCHEDULE_GET, OnBtnScheduleGet)
    ON_BN_CLICKED(IDC_BTN_SCHEDULE_NEW, OnBtnScheduleNew)
    ON_BN_CLICKED(IDC_BTN_SCHEDULE_SET, OnBtnScheduleSet)
    ON_BN_CLICKED(IDC_BTN_SPAN_ADD, OnBtnSpanAdd)
    ON_BN_CLICKED(IDC_BTN_SPAN_DEL, OnBtnSpanDel)
    ON_BN_CLICKED(IDC_BTN_SPAN_MOD, OnBtnSpanMod)
    ON_NOTIFY(NM_CLICK, IDC_LIST_SPAN, OnClickListSpan)
    ON_CBN_SELCHANGE(IDC_COMBO_SCHEDULE_TYPE, OnSelchangeComboScheduleType)
    ON_CBN_SELCHANGE(IDC_COMBO_WEEKDAY, OnSelchangeComboWeekday)
    ON_BN_CLICKED(IDC_BTN_RELEASE_MANAGE, OnBtnReleaseManage)
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_BTN_SELFDEFINE_SCHEDULE, OnBtnSelfdefineSchedule)
    ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_EXPORT, &CDlgInfoDiffusionSchedule::OnBnClickedBtnExport)
    ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionSchedule message handlers

void CDlgInfoDiffusionSchedule::OnBtnScheduleDel()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);

    CString strCommand;
    strCommand.Format("DELETE /ISAPI/Publish/ScheduleMgr/playSchedule/%d\r\n", m_dwScheduleID);
    NET_DVR_XML_CONFIG_INPUT struInputParam = { 0 };
    struInputParam.dwSize = sizeof(struInputParam);
    struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
    struInputParam.dwRequestUrlLen = strCommand.GetLength();

    char szStatusBuff[1024] = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT struOutputParam = { 0 };
    struOutputParam.dwSize = sizeof(struOutputParam);
    struOutputParam.lpStatusBuffer = szStatusBuff;
    struOutputParam.dwStatusSize = sizeof(szStatusBuff);

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");

    UpdateData(FALSE);
}

void CDlgInfoDiffusionSchedule::OnBtnScheduleGet()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);

    CString strCommand;
    strCommand.Format("GET /ISAPI/Publish/ScheduleMgr/playSchedule/%d\r\n", m_dwScheduleID);
    NET_DVR_XML_CONFIG_INPUT struInputParam = { 0 };
    struInputParam.dwSize = sizeof(struInputParam);
    struInputParam.lpRequestUrl = strCommand.GetBuffer(0);
    struInputParam.dwRequestUrlLen = strCommand.GetLength();

    char szStatusBuff[1024] = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT struOutputParam = { 0 };
    struOutputParam.dwSize = sizeof(struOutputParam);
    memset(m_pOutputXmlBuffer, 0, MAX_LEN_XML);
    struOutputParam.lpOutBuffer = m_pOutputXmlBuffer;
    struOutputParam.dwOutBufferSize = MAX_LEN_XML;
    struOutputParam.lpStatusBuffer = szStatusBuff;
    struOutputParam.dwStatusSize = sizeof(szStatusBuff);

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");

    LPNET_DVR_PLAY_SCHEDULE lpSchedule = &m_struSchedule;
    memset(lpSchedule, 0, sizeof(*lpSchedule));
    lpSchedule->dwSize = sizeof(*lpSchedule);
    ConvertScheduleParamsXmlToStru(m_pOutputXmlBuffer, lpSchedule);
    UpdateScheduleInfo();

    UpdateData(FALSE);
}

void CDlgInfoDiffusionSchedule::OnBtnScheduleNew()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);

    LPNET_DVR_PLAY_SCHEDULE lpSchedule = &m_struSchedule;
    lpSchedule->dwSize = sizeof(*lpSchedule);
    memcpy(lpSchedule->szScheduleName, m_szScheduleName, strlen(m_szScheduleName));
    memcpy(lpSchedule->szScheduleRemarks, m_szScheduleRemarks, strlen(m_szScheduleRemarks));
    memcpy(lpSchedule->szScheduleMode, m_csModeType, m_csModeType.GetLength());
    lpSchedule->dwOrgNo = m_dwOrgNo;
    int nSel = m_cmbShareProp.GetCurSel();
    if (nSel == CB_ERR)
    {
        char szLan1[512] = { 0 };
        char szLan2[512] = { 0 };
        g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
        g_StringLanType(szLan2, "日程管理", "Schedule Management");
        MessageBox(szLan1, szLan2, MB_ICONWARNING);
        return;
    }
    m_cmbShareProp.GetLBText(nSel, lpSchedule->szShareProp);
    nSel = m_cmbApprove.GetCurSel();
    if (nSel == CB_ERR)
    {
        char szLan1[512] = { 0 };
        char szLan2[512] = { 0 };
        g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
        g_StringLanType(szLan2, "日程管理", "Schedule Management");
        MessageBox(szLan1, szLan2, MB_ICONWARNING);
        return;
    }
    m_cmbApprove.GetLBText(nSel, lpSchedule->szApprove);
    memcpy(lpSchedule->szApproveRemarks, m_szApproveRemarks, strlen(m_szApproveRemarks));
    nSel = m_cmbScheduleType.GetCurSel();
    if (nSel == CB_ERR)
    {
        char szLan1[512] = { 0 };
        char szLan2[512] = { 0 };
        g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
        g_StringLanType(szLan2, "日程管理", "Schedule Management");
        MessageBox(szLan1, szLan2, MB_ICONWARNING);
        return;
    }
    m_cmbScheduleType.GetLBText(nSel, lpSchedule->szScheduleType);

    char* pInputBuff = NULL;
    DWORD dwInputSize = 0;
    ConvertScheduleParamsStruToXml(lpSchedule, &pInputBuff, dwInputSize);

    CString strCommand;
    strCommand.Format("POST /ISAPI/Publish/ScheduleMgr/playSchedule\r\n");
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
        delete[] pInputBuff;
        pInputBuff = NULL;
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");

    m_dwScheduleID = GetResponseStatusID(szStatusBuff);
    lpSchedule->dwScheduleID = m_dwScheduleID;

    delete[] pInputBuff;
    pInputBuff = NULL;

    UpdateData(FALSE);
}

void CDlgInfoDiffusionSchedule::OnBtnScheduleSet()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);

    LPNET_DVR_PLAY_SCHEDULE lpSchedule = &m_struSchedule;
    lpSchedule->dwSize = sizeof(*lpSchedule);
    lpSchedule->dwScheduleID = m_dwScheduleID;
    memcpy(lpSchedule->szScheduleName, m_szScheduleName, strlen(m_szScheduleName));
    memcpy(lpSchedule->szScheduleRemarks, m_szScheduleRemarks, strlen(m_szScheduleRemarks));
    int nSel = m_cmbShareProp.GetCurSel();
    if (nSel == CB_ERR)
    {
        char szLan1[512] = { 0 };
        char szLan2[512] = { 0 };
        g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
        g_StringLanType(szLan2, "日程管理", "Schedule Management");
        MessageBox(szLan1, szLan2, MB_ICONWARNING);
        return;
    }
    m_cmbShareProp.GetLBText(nSel, lpSchedule->szShareProp);
    // 	nSel = m_cmbApprove.GetCurSel();
    // 	if (nSel == CB_ERR)
    // 	{
    // 		char szLan1[512] = {0};
    // 		char szLan2[512] = {0};
    // 		g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
    // 		g_StringLanType(szLan2, "日程管理", "Schedule Management");
    // 		MessageBox(szLan1, szLan2, MB_ICONWARNING);
    // 		return;
    // 	}
    // 	m_cmbApprove.GetLBText(nSel, lpSchedule->szApprove);
    // 	memcpy(lpSchedule->szApproveRemarks, m_szApproveRemarks, strlen(m_szApproveRemarks));
    nSel = m_cmbScheduleType.GetCurSel();
    if (nSel == CB_ERR)
    {
        char szLan1[512] = { 0 };
        char szLan2[512] = { 0 };
        g_StringLanType(szLan1, "输入参数不完整", "Input parameters is not enough.");
        g_StringLanType(szLan2, "日程管理", "Schedule Management");
        MessageBox(szLan1, szLan2, MB_ICONWARNING);
        return;
    }
    m_cmbScheduleType.GetLBText(nSel, lpSchedule->szScheduleType);

    char* pInputBuff = NULL;
    DWORD dwInputSize = 0;
    ConvertScheduleParamsStruToXml(lpSchedule, &pInputBuff, dwInputSize);

    CString strCommand;
    strCommand.Format("PUT /ISAPI/Publish/ScheduleMgr/playSchedule/%d\r\n", m_dwScheduleID);
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
        delete[] pInputBuff;
        pInputBuff = NULL;
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");

    delete[] pInputBuff;
    pInputBuff = NULL;

    UpdateData(FALSE);
}

void CDlgInfoDiffusionSchedule::OnBtnSpanAdd()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);

    int nSel = m_cmbScheduleType.GetCurSel();
    if (nSel == CB_ERR)
    {
        return;
    }
    CString strScheduleType;
    m_cmbScheduleType.GetLBText(nSel, strScheduleType);
    CString str;
    int nSpanIndex = -1;
    int nSpanCnt = 0;
    if (0 == strcmp(strScheduleType, "daily"))
    {
        for (nSpanCnt = 0; nSpanCnt < MAX_SPANS_A_DAY; nSpanCnt++)
        {
            if (0 == m_struSchedule.struDailySchedule[nSpanCnt].dwSpanID)
            {
                nSpanIndex = nSpanCnt;
                break;
            }
        }
        if (nSpanIndex < 0)
        {
            char szLan1[512] = { 0 };
            char szLan2[512] = { 0 };
            g_StringLanType(szLan1, "时段数量已达上限", "The number of span is limited.");
            g_StringLanType(szLan2, "日程管理", "Schedule Management");
            MessageBox(szLan1, szLan2, MB_ICONWARNING);
            return;
        }
        LPNET_DVR_PLAY_SPAN lpSpan = &m_struSchedule.struDailySchedule[nSpanIndex];
        lpSpan->dwSpanID = nSpanIndex + 1;
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
        str.Format("%d", nSpanIndex + 1);
        m_listSpan.InsertItem(nSpanIndex, str);
        m_listSpan.SetItemState(nSpanIndex, 0, -1);
        m_listSpan.SetItemState(nSpanIndex, LVIS_SELECTED, LVIS_SELECTED);
        m_listSpan.SetFocus();
        m_nCurSelSpan = nSpanIndex;
        str.Format("%d", lpSpan->dwProgramID);
        m_listSpan.SetItemText(nSpanIndex, 1, str);
        str.Format("%02d:%02d:%02d",
            lpSpan->struTimeRange.struBeginTime.dwHour,
            lpSpan->struTimeRange.struBeginTime.dwMinute,
            lpSpan->struTimeRange.struBeginTime.dwSecond);
        m_listSpan.SetItemText(nSpanIndex, 2, str);
        str.Format("%02d:%02d:%02d",
            lpSpan->struTimeRange.struEndTime.dwHour,
            lpSpan->struTimeRange.struEndTime.dwMinute,
            lpSpan->struTimeRange.struEndTime.dwSecond);
        m_listSpan.SetItemText(nSpanIndex, 3, str);
    }
    else if (0 == strcmp(strScheduleType, "weekly"))
    {
        nSel = m_cmbWeekday.GetCurSel();
        if (nSel == CB_ERR)
        {
            return;
        }
        m_cmbWeekday.GetLBText(nSel, m_struSchedule.struWeeklySchedule[nSel].szWeekday);
        m_struSchedule.struWeeklySchedule[nSel].dwDayID = nSel + 1;
        for (nSpanCnt = 0; nSpanCnt < MAX_SPANS_A_DAY; nSpanCnt++)
        {
            if (0 == m_struSchedule.struWeeklySchedule[nSel].struSpanList[nSpanCnt].dwSpanID)
            {
                nSpanIndex = nSpanCnt;
                break;
            }
        }
        if (nSpanIndex < 0)
        {
            char szLan1[512] = { 0 };
            char szLan2[512] = { 0 };
            g_StringLanType(szLan1, "时段数量已达上限", "The number of span is limited.");
            g_StringLanType(szLan2, "日程管理", "Schedule Management");
            MessageBox(szLan1, szLan2, MB_ICONWARNING);
            return;
        }
        LPNET_DVR_PLAY_SPAN lpSpan = &m_struSchedule.struWeeklySchedule[nSel].struSpanList[nSpanIndex];
        lpSpan->dwSpanID = nSpanIndex + 1;
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
        str.Format("%d", nSpanIndex + 1);
        m_listSpan.InsertItem(nSpanIndex, str);
        m_listSpan.SetItemState(nSpanIndex, 0, -1);
        m_listSpan.SetItemState(nSpanIndex, LVIS_SELECTED, LVIS_SELECTED);
        m_listSpan.SetFocus();
        m_nCurSelSpan = nSpanIndex;
        str.Format("%d", lpSpan->dwProgramID);
        m_listSpan.SetItemText(nSpanIndex, 1, str);
        str.Format("%02d:%02d:%02d",
            lpSpan->struTimeRange.struBeginTime.dwHour,
            lpSpan->struTimeRange.struBeginTime.dwMinute,
            lpSpan->struTimeRange.struBeginTime.dwSecond);
        m_listSpan.SetItemText(nSpanIndex, 2, str);
        str.Format("%02d:%02d:%02d",
            lpSpan->struTimeRange.struEndTime.dwHour,
            lpSpan->struTimeRange.struEndTime.dwMinute,
            lpSpan->struTimeRange.struEndTime.dwSecond);
        m_listSpan.SetItemText(nSpanIndex, 3, str);
    }
    else if (0 == strcmp(strScheduleType, "loop"))
    {
        for (nSpanCnt = 0; nSpanCnt < MAX_PROGRAMS_A_LOOP; nSpanCnt++)
        {
            if (0 == m_struSchedule.struLoopSchedule[nSpanCnt].dwLoopID)
            {
                nSpanIndex = nSpanCnt;
                break;
            }
        }
        if (nSpanIndex < 0)
        {
            char szLan1[512] = { 0 };
            char szLan2[512] = { 0 };
            g_StringLanType(szLan1, "时段数量已达上限", "The number of span is limited.");
            g_StringLanType(szLan2, "日程管理", "Schedule Management");
            MessageBox(szLan1, szLan2, MB_ICONWARNING);
            return;
        }
        m_struSchedule.struLoopSchedule[nSpanIndex].dwLoopID = nSpanIndex + 1;
        m_struSchedule.struLoopSchedule[nSpanIndex].dwProgramID = m_dwProgramID;
        str.Format("%d", nSpanIndex + 1);
        m_listSpan.InsertItem(nSpanIndex, str);
        m_listSpan.SetItemState(nSpanIndex, 0, -1);
        m_listSpan.SetItemState(nSpanIndex, LVIS_SELECTED, LVIS_SELECTED);
        m_listSpan.SetFocus();
        m_nCurSelSpan = nSpanIndex;
        str.Format("%d", m_dwProgramID);
        m_listSpan.SetItemText(nSpanIndex, 1, str);
    }
}

void CDlgInfoDiffusionSchedule::OnBtnSpanDel()
{
    // TODO: Add your control notification handler code here
    if (m_nCurSelSpan < 0)
    {
        char szLan1[512] = { 0 };
        char szLan2[512] = { 0 };
        g_StringLanType(szLan1, "请选择播放时段", "Please choose a Span first.");
        g_StringLanType(szLan2, "日程管理", "Schedule Management");
        MessageBox(szLan1, szLan2, MB_ICONWARNING);
        return;
    }

    int nSel = m_cmbScheduleType.GetCurSel();
    if (nSel == CB_ERR)
    {
        return;
    }
    CString strScheduleType;
    m_cmbScheduleType.GetLBText(nSel, strScheduleType);
    CString str;
    if (0 == strcmp(strScheduleType, "daily"))
    {
        for (int nSpanCnt = m_nCurSelSpan; nSpanCnt < m_listSpan.GetItemCount() - 1; nSpanCnt++)
        {
            m_listSpan.SetItemText(nSpanCnt, 1, m_listSpan.GetItemText(nSpanCnt + 1, 1));
            m_listSpan.SetItemText(nSpanCnt, 2, m_listSpan.GetItemText(nSpanCnt + 1, 2));
            m_listSpan.SetItemText(nSpanCnt, 3, m_listSpan.GetItemText(nSpanCnt + 1, 3));
            memcpy(&m_struSchedule.struDailySchedule[nSpanCnt],
                &m_struSchedule.struDailySchedule[nSpanCnt + 1],
                sizeof(NET_DVR_PLAY_SPAN));
            m_struSchedule.struDailySchedule[nSpanCnt].dwSpanID = nSpanCnt + 1;
        }
        LPNET_DVR_PLAY_SPAN lpSpan = &m_struSchedule.struDailySchedule[m_listSpan.GetItemCount() - 1];
        memset(lpSpan, 0, sizeof(*lpSpan));
        m_listSpan.DeleteItem(m_listSpan.GetItemCount() - 1);
    }
    else if (0 == strcmp(strScheduleType, "weekly"))
    {
        nSel = m_cmbWeekday.GetCurSel();
        if (nSel == CB_ERR)
        {
            return;
        }
        for (int nSpanCnt = m_nCurSelSpan; nSpanCnt < m_listSpan.GetItemCount() - 1; nSpanCnt++)
        {
            m_listSpan.SetItemText(nSpanCnt, 1, m_listSpan.GetItemText(nSpanCnt + 1, 1));
            m_listSpan.SetItemText(nSpanCnt, 2, m_listSpan.GetItemText(nSpanCnt + 1, 2));
            m_listSpan.SetItemText(nSpanCnt, 3, m_listSpan.GetItemText(nSpanCnt + 1, 3));
            memcpy(&m_struSchedule.struWeeklySchedule[nSel].struSpanList[nSpanCnt],
                &m_struSchedule.struWeeklySchedule[nSel].struSpanList[nSpanCnt + 1],
                sizeof(NET_DVR_PLAY_SPAN));
            m_struSchedule.struWeeklySchedule[nSel].struSpanList[nSpanCnt].dwSpanID = nSpanCnt + 1;
        }
        LPNET_DVR_PLAY_SPAN lpSpan = &m_struSchedule.struWeeklySchedule[nSel].struSpanList[m_listSpan.GetItemCount() - 1];
        memset(lpSpan, 0, sizeof(*lpSpan));
        m_listSpan.DeleteItem(m_listSpan.GetItemCount() - 1);
        if (m_listSpan.GetItemCount() == 0)
        {
            m_struSchedule.struWeeklySchedule[nSel].dwDayID = 0;
        }
    }
    else if (0 == strcmp(strScheduleType, "loop"))
    {
        for (int nSpanCnt = m_nCurSelSpan; nSpanCnt < m_listSpan.GetItemCount() - 1; nSpanCnt++)
        {
            m_listSpan.SetItemText(nSpanCnt, 1, m_listSpan.GetItemText(nSpanCnt + 1, 1));
            m_listSpan.SetItemText(nSpanCnt, 2, m_listSpan.GetItemText(nSpanCnt + 1, 2));
            m_listSpan.SetItemText(nSpanCnt, 3, m_listSpan.GetItemText(nSpanCnt + 1, 3));
            memcpy(&m_struSchedule.struLoopSchedule[nSpanCnt],
                &m_struSchedule.struLoopSchedule[nSpanCnt + 1], sizeof(NET_DVR_PLAY_LOOP));
            m_struSchedule.struLoopSchedule[nSpanCnt].dwLoopID = nSpanCnt + 1;
        }
        memset(&m_struSchedule.struLoopSchedule[m_listSpan.GetItemCount() - 1], 0, sizeof(NET_DVR_PLAY_LOOP));
        m_listSpan.DeleteItem(m_listSpan.GetItemCount() - 1);
    }
    m_nCurSelSpan = -1;
}

void CDlgInfoDiffusionSchedule::OnBtnSpanMod()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);

    if (m_nCurSelSpan < 0)
    {
        char szLan1[512] = { 0 };
        char szLan2[512] = { 0 };
        g_StringLanType(szLan1, "请选择播放时段", "Please choose a Span first.");
        g_StringLanType(szLan2, "日程管理", "Schedule Management");
        MessageBox(szLan1, szLan2, MB_ICONWARNING);
        return;
    }
    int nSel = m_cmbScheduleType.GetCurSel();
    if (nSel == CB_ERR)
    {
        return;
    }
    CString strScheduleType;
    m_cmbScheduleType.GetLBText(nSel, strScheduleType);
    CString str;
    if (0 == strcmp(strScheduleType, "daily"))
    {
        LPNET_DVR_PLAY_SPAN lpSpan = &m_struSchedule.struDailySchedule[m_nCurSelSpan];
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
        str.Format("%02d:%02d:%02d",
            lpSpan->struTimeRange.struBeginTime.dwHour,
            lpSpan->struTimeRange.struBeginTime.dwMinute,
            lpSpan->struTimeRange.struBeginTime.dwSecond);
        m_listSpan.SetItemText(m_nCurSelSpan, 2, str);
        str.Format("%02d:%02d:%02d",
            lpSpan->struTimeRange.struEndTime.dwHour,
            lpSpan->struTimeRange.struEndTime.dwMinute,
            lpSpan->struTimeRange.struEndTime.dwSecond);
        m_listSpan.SetItemText(m_nCurSelSpan, 3, str);
    }
    else if (0 == strcmp(strScheduleType, "weekly"))
    {
        nSel = m_cmbWeekday.GetCurSel();
        if (nSel == CB_ERR)
        {
            return;
        }
        LPNET_DVR_PLAY_SPAN lpSpan = &m_struSchedule.struWeeklySchedule[nSel].struSpanList[m_nCurSelSpan];
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
        str.Format("%02d:%02d:%02d",
            lpSpan->struTimeRange.struBeginTime.dwHour,
            lpSpan->struTimeRange.struBeginTime.dwMinute,
            lpSpan->struTimeRange.struBeginTime.dwSecond);
        m_listSpan.SetItemText(m_nCurSelSpan, 2, str);
        str.Format("%02d:%02d:%02d",
            lpSpan->struTimeRange.struEndTime.dwHour,
            lpSpan->struTimeRange.struEndTime.dwMinute,
            lpSpan->struTimeRange.struEndTime.dwSecond);
        m_listSpan.SetItemText(m_nCurSelSpan, 3, str);
    }
    else if (0 == strcmp(strScheduleType, "loop"))
    {
        m_struSchedule.struLoopSchedule[m_nCurSelSpan].dwProgramID = m_dwProgramID;
        str.Format("%d", m_dwProgramID);
        m_listSpan.SetItemText(m_nCurSelSpan, 1, str);
    }
}

void CDlgInfoDiffusionSchedule::OnClickListSpan(NMHDR* pNMHDR, LRESULT* pResult)
{
    // TODO: Add your control notification handler code here
    POSITION pos = m_listSpan.GetFirstSelectedItemPosition();
    if (pos)
    {
        m_nCurSelSpan = m_listSpan.GetNextSelectedItem(pos);
        int nSel = m_cmbScheduleType.GetCurSel();
        if (nSel == CB_ERR)
        {
            return;
        }
        CString strScheduleType;
        m_cmbScheduleType.GetLBText(nSel, strScheduleType);
        if (0 == strcmp(strScheduleType, "daily"))
        {
            m_dwProgramID = m_struSchedule.struDailySchedule[m_nCurSelSpan].dwProgramID;
            m_timeStartDate.SetDate(m_struSchedule.struDailySchedule[m_nCurSelSpan].struTimeRange.struBeginTime.dwYear,
                m_struSchedule.struDailySchedule[m_nCurSelSpan].struTimeRange.struBeginTime.dwMonth,
                m_struSchedule.struDailySchedule[m_nCurSelSpan].struTimeRange.struBeginTime.dwDay);
            m_timeStartTime.SetTime(m_struSchedule.struDailySchedule[m_nCurSelSpan].struTimeRange.struBeginTime.dwHour,
                m_struSchedule.struDailySchedule[m_nCurSelSpan].struTimeRange.struBeginTime.dwMinute,
                m_struSchedule.struDailySchedule[m_nCurSelSpan].struTimeRange.struBeginTime.dwSecond);
            m_timeEndDate.SetDate(m_struSchedule.struDailySchedule[m_nCurSelSpan].struTimeRange.struEndTime.dwYear,
                m_struSchedule.struDailySchedule[m_nCurSelSpan].struTimeRange.struEndTime.dwMonth,
                m_struSchedule.struDailySchedule[m_nCurSelSpan].struTimeRange.struEndTime.dwDay);
            m_timeEndTime.SetTime(m_struSchedule.struDailySchedule[m_nCurSelSpan].struTimeRange.struEndTime.dwHour,
                m_struSchedule.struDailySchedule[m_nCurSelSpan].struTimeRange.struEndTime.dwMinute,
                m_struSchedule.struDailySchedule[m_nCurSelSpan].struTimeRange.struEndTime.dwSecond);
        }
        else if (0 == strcmp(strScheduleType, "weekly"))
        {
            nSel = m_cmbWeekday.GetCurSel();
            if (nSel == CB_ERR)
            {
                return;
            }
            m_dwProgramID = m_struSchedule.struWeeklySchedule[nSel].struSpanList[m_nCurSelSpan].dwProgramID;
            m_timeStartDate.SetDate(m_struSchedule.struWeeklySchedule[nSel].struSpanList[m_nCurSelSpan].struTimeRange.struBeginTime.dwYear,
                m_struSchedule.struWeeklySchedule[nSel].struSpanList[m_nCurSelSpan].struTimeRange.struBeginTime.dwMonth,
                m_struSchedule.struWeeklySchedule[nSel].struSpanList[m_nCurSelSpan].struTimeRange.struBeginTime.dwDay);
            m_timeStartTime.SetTime(m_struSchedule.struWeeklySchedule[nSel].struSpanList[m_nCurSelSpan].struTimeRange.struBeginTime.dwHour,
                m_struSchedule.struWeeklySchedule[nSel].struSpanList[m_nCurSelSpan].struTimeRange.struBeginTime.dwMinute,
                m_struSchedule.struWeeklySchedule[nSel].struSpanList[m_nCurSelSpan].struTimeRange.struBeginTime.dwSecond);
            m_timeEndDate.SetDate(m_struSchedule.struWeeklySchedule[nSel].struSpanList[m_nCurSelSpan].struTimeRange.struEndTime.dwYear,
                m_struSchedule.struWeeklySchedule[nSel].struSpanList[m_nCurSelSpan].struTimeRange.struEndTime.dwMonth,
                m_struSchedule.struWeeklySchedule[nSel].struSpanList[m_nCurSelSpan].struTimeRange.struEndTime.dwDay);
            m_timeEndTime.SetTime(m_struSchedule.struWeeklySchedule[nSel].struSpanList[m_nCurSelSpan].struTimeRange.struEndTime.dwHour,
                m_struSchedule.struWeeklySchedule[nSel].struSpanList[m_nCurSelSpan].struTimeRange.struEndTime.dwMinute,
                m_struSchedule.struWeeklySchedule[nSel].struSpanList[m_nCurSelSpan].struTimeRange.struEndTime.dwSecond);
        }
        else if (0 == strcmp(strScheduleType, "loop"))
        {
            m_dwProgramID = m_struSchedule.struLoopSchedule[m_nCurSelSpan].dwProgramID;
        }
        UpdateData(FALSE);
    }

    *pResult = 0;
}

void CDlgInfoDiffusionSchedule::OnSelchangeComboScheduleType()
{
    // TODO: Add your control notification handler code here
    int nSel = m_cmbScheduleType.GetCurSel();
    if (nSel == CB_ERR)
    {
        return;
    }
    CString strScheduleType;
    m_cmbScheduleType.GetLBText(nSel, strScheduleType);
    if (0 == strcmp(strScheduleType, "daily"))
    {
        GetDlgItem(IDC_COMBO_WEEKDAY)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_PROGRAM_ID)->EnableWindow(TRUE);
        GetDlgItem(IDC_DATETIMEPICKER_START_DATE)->EnableWindow(FALSE);
        GetDlgItem(IDC_DATETIMEPICKER_START_TIME)->EnableWindow(TRUE);
        GetDlgItem(IDC_DATETIMEPICKER_END_DATE)->EnableWindow(FALSE);
        GetDlgItem(IDC_DATETIMEPICKER_END_TIME)->EnableWindow(TRUE);
        RefreshPlaySpanList(&m_struSchedule, strScheduleType);
    }
    else if (0 == strcmp(strScheduleType, "weekly"))
    {
        GetDlgItem(IDC_COMBO_WEEKDAY)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_PROGRAM_ID)->EnableWindow(TRUE);
        GetDlgItem(IDC_DATETIMEPICKER_START_DATE)->EnableWindow(FALSE);
        GetDlgItem(IDC_DATETIMEPICKER_START_TIME)->EnableWindow(TRUE);
        GetDlgItem(IDC_DATETIMEPICKER_END_DATE)->EnableWindow(FALSE);
        GetDlgItem(IDC_DATETIMEPICKER_END_TIME)->EnableWindow(TRUE);
        m_cmbWeekday.SetCurSel(0);
        OnSelchangeComboWeekday();
    }
    else if (0 == strcmp(strScheduleType, "loop"))
    {
        GetDlgItem(IDC_COMBO_WEEKDAY)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_PROGRAM_ID)->EnableWindow(TRUE);
        GetDlgItem(IDC_DATETIMEPICKER_START_DATE)->EnableWindow(FALSE);
        GetDlgItem(IDC_DATETIMEPICKER_START_TIME)->EnableWindow(FALSE);
        GetDlgItem(IDC_DATETIMEPICKER_END_DATE)->EnableWindow(FALSE);
        GetDlgItem(IDC_DATETIMEPICKER_END_TIME)->EnableWindow(FALSE);
        RefreshPlaySpanList(&m_struSchedule, strScheduleType);
    }
}

BOOL CDlgInfoDiffusionSchedule::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO: Add extra initialization here
    InitPlaySpanList();
    m_cmbScheduleType.SetCurSel(0);
    OnSelchangeComboScheduleType();

    m_ctrlProgress.SetRange(0, 100);
    m_ctrlProgress.SetStep(1);
    m_ctrlProgress.SetPos(0);
    m_statProgress.SetWindowText(_T("0%"));

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgInfoDiffusionSchedule::UpdateScheduleInfo()
{
    LPNET_DVR_PLAY_SCHEDULE lpSchedule = &m_struSchedule;
    m_dwScheduleID = lpSchedule->dwScheduleID;
    m_szScheduleName = lpSchedule->szScheduleName;
    m_szScheduleRemarks = lpSchedule->szScheduleRemarks;
    m_cmbShareProp.SetCurSel(m_cmbShareProp.FindString(-1, lpSchedule->szShareProp));
    m_cmbApprove.SetCurSel(m_cmbApprove.FindString(-1, m_struSchedule.szApprove));
    m_szApproveRemarks = m_struSchedule.szApproveRemarks;
    m_cmbScheduleType.SetCurSel(m_cmbScheduleType.FindString(-1, lpSchedule->szScheduleType));
    OnSelchangeComboScheduleType();
    UpdateData(FALSE);
}

void CDlgInfoDiffusionSchedule::InitPlaySpanList()
{
    DWORD dwExStyle = m_listSpan.GetExtendedStyle();
    dwExStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
    m_listSpan.SetExtendedStyle(dwExStyle);

    char szLan[512] = { 0 };
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

void CDlgInfoDiffusionSchedule::RefreshPlaySpanList(LPNET_DVR_PLAY_SCHEDULE lpSchedule, CString strScheduleType, int nWeekday /* = -1 */)
{
    if (lpSchedule == NULL)
    {
        return;
    }

    m_listSpan.DeleteAllItems();
    int nSpanCnt = 0;
    CString str;
    if (0 == strcmp(strScheduleType, "daily"))
    {
        for (nSpanCnt = 0; nSpanCnt < MAX_SPANS_A_DAY; nSpanCnt++)
        {
            LPNET_DVR_PLAY_SPAN lpSpan = &lpSchedule->struDailySchedule[nSpanCnt];
            if (0 == lpSpan->dwSpanID)
            {
                break;
            }
            str.Format("%d", nSpanCnt + 1);
            m_listSpan.InsertItem(nSpanCnt, str);
            str.Format("%d", lpSpan->dwProgramID);
            m_listSpan.SetItemText(nSpanCnt, 1, str);
            str.Format("%02d:%02d:%02d",
                lpSpan->struTimeRange.struBeginTime.dwHour,
                lpSpan->struTimeRange.struBeginTime.dwMinute,
                lpSpan->struTimeRange.struBeginTime.dwSecond);
            m_listSpan.SetItemText(nSpanCnt, 2, str);
            str.Format("%02d:%02d:%02d",
                lpSpan->struTimeRange.struEndTime.dwHour,
                lpSpan->struTimeRange.struEndTime.dwMinute,
                lpSpan->struTimeRange.struEndTime.dwSecond);
            m_listSpan.SetItemText(nSpanCnt, 3, str);
        }
    }
    else if (0 == strcmp(strScheduleType, "weekly"))
    {
        if (nWeekday == -1)
        {
            return;
        }
        for (nSpanCnt = 0; nSpanCnt < MAX_SPANS_A_DAY; nSpanCnt++)
        {
            LPNET_DVR_PLAY_SPAN lpSpan = &lpSchedule->struWeeklySchedule[nWeekday].struSpanList[nSpanCnt];
            if (0 == lpSpan->dwSpanID)
            {
                break;
            }
            str.Format("%d", nSpanCnt + 1);
            m_listSpan.InsertItem(nSpanCnt, str);
            str.Format("%d", lpSpan->dwProgramID);
            m_listSpan.SetItemText(nSpanCnt, 1, str);
            str.Format("%02d:%02d:%02d",
                lpSpan->struTimeRange.struBeginTime.dwHour,
                lpSpan->struTimeRange.struBeginTime.dwMinute,
                lpSpan->struTimeRange.struBeginTime.dwSecond);
            m_listSpan.SetItemText(nSpanCnt, 2, str);
            str.Format("%02d:%02d:%02d",
                lpSpan->struTimeRange.struEndTime.dwHour,
                lpSpan->struTimeRange.struEndTime.dwMinute,
                lpSpan->struTimeRange.struEndTime.dwSecond);
            m_listSpan.SetItemText(nSpanCnt, 3, str);
        }
    }
    else if (0 == strcmp(strScheduleType, "loop"))
    {
        for (nSpanCnt = 0; nSpanCnt < MAX_PROGRAMS_A_LOOP; nSpanCnt++)
        {
            if (0 == lpSchedule->struLoopSchedule[nSpanCnt].dwLoopID)
            {
                break;
            }
            str.Format("%d", nSpanCnt + 1);
            m_listSpan.InsertItem(nSpanCnt, str);
            str.Format("%d", lpSchedule->struLoopSchedule[nSpanCnt].dwProgramID);
            m_listSpan.SetItemText(nSpanCnt, 1, str);
        }
    }
}

void CDlgInfoDiffusionSchedule::OnSelchangeComboWeekday()
{
    // TODO: Add your control notification handler code here
    int nSel = m_cmbScheduleType.GetCurSel();
    if (nSel == CB_ERR)
    {
        return;
    }
    CString strScheduleType;
    m_cmbScheduleType.GetLBText(nSel, strScheduleType);
    nSel = m_cmbWeekday.GetCurSel();
    if (nSel == CB_ERR)
    {
        return;
    }
    RefreshPlaySpanList(&m_struSchedule, strScheduleType, nSel);
}

void CDlgInfoDiffusionSchedule::OnBtnReleaseManage()
{
    // TODO: Add your control notification handler code here
    CDlgInfoDiffusionRelease dlg;
    dlg.DoModal();
}

void CDlgInfoDiffusionSchedule::OnDestroy()
{
    CDialog::OnDestroy();

    // TODO: Add your message handler code here
    delete[] m_pOutputXmlBuffer;
    m_pOutputXmlBuffer = NULL;
}

void CDlgInfoDiffusionSchedule::OnBtnSelfdefineSchedule()
{
    // TODO: Add your control notification handler code here
    CDlgInfoDiffusionScheduleSelfdefine dlg;
    dlg.InitializeData(m_struSchedule.struSeldefineSchedule);
    if (IDOK != dlg.DoModal())
    {
        return;
    }
    dlg.SaveData(m_struSchedule.struSeldefineSchedule);
}

void CDlgInfoDiffusionSchedule::OnBtnSearch()
{
    // TODO: Add your control notification handler code here
    CDlgInfoDiffusionScheduleSearch dlg;
    dlg.DoModal();
}


void CDlgInfoDiffusionSchedule::OnBnClickedBtnExport()
{
    // TODO:  在此添加控件通知处理程序代码
    if (m_bExport)
    {
        MessageBox("正在导出请稍等");
        return;
    }
    UpdateData(TRUE);

    char szFile[256] = { 0 };
    memcpy(szFile, "C:\\Schedule", strlen("C:\\Schedule"));
    if (!PathFileExists(szFile))
    {
        if (!CreateDirectory(szFile, NULL))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Create file failed!");
            return;
        }
    }

    NET_DVR_EXPORT_PUBLISH_SCHEDULE struSchedule = { 0 };
    struSchedule.dwScheduleID = m_dwScheduleID;
    struSchedule.fnDownloadFileCallBack = fExportCallBack;
    struSchedule.pUser = this;
    m_lExportHandle = NET_DVR_StartDownload(m_lUserID, NET_SDK_DOWNLOAD_PUBLISH_SCHEDULE, &struSchedule, sizeof(struSchedule), NULL);
    if (m_lExportHandle < 0)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_SDK_DOWNLOAD_PUBLISH_SCHEDULE");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_SDK_DOWNLOAD_PUBLISH_SCHEDULE");
    }

    m_bExport = TRUE;
    m_ctrlProgress.SetPos(0);
    m_statProgress.SetWindowText(_T("0%"));
    SetTimer(TIMER_SCHEDULE_EXPORT_PROGRESS, 100, NULL);
}

void CDlgInfoDiffusionSchedule::OnTimer(UINT_PTR nIDEvent)
{
    // TODO:  在此添加消息处理程序代码和/或调用默认值

    if (nIDEvent == TIMER_SCHEDULE_EXPORT_PROGRESS)
    {
        DWORD dwProgress = 0;
        LONG lStatus = -1;

        lStatus = NET_DVR_GetDownloadState(m_lExportHandle, &dwProgress);
        if (lStatus == -1)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetDownloadState");
            if (!NET_DVR_StopDownload(m_lExportHandle))
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopDownload");
            }
            else
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopDownload");
            }
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetDownloadState");
        }
        switch (lStatus)
        {
        case 1: //下载成功
        {
                    m_ctrlProgress.SetPos(dwProgress);
                    CString str;
                    str.Format("%d", dwProgress);
                    str += _T("%");
                    m_statProgress.SetWindowText(str);
                    if (!NET_DVR_StopDownload(m_lExportHandle))
                    {
                        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopDownload");
                    }
                    else
                    {
                        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopDownload");
                    }
                    m_bExport = FALSE;
                    m_lExportHandle = -1;
                    KillTimer(TIMER_SCHEDULE_EXPORT_PROGRESS);
                    char sTitle[64] = { 0 };
                    char sMsg[64] = { 0 };
                    g_StringLanType(sTitle, "日程管理", "Schedule Management");
                    g_StringLanType(sMsg, "导出完成", "Download finished.");
                    MessageBox(sMsg, sTitle, MB_OK | MB_ICONWARNING);
                    break;
        }
        case 2: //正在下载
        {
                    m_ctrlProgress.SetPos(dwProgress);
                    CString str;
                    str.Format("%d", dwProgress);
                    str += _T("%");
                    m_statProgress.SetWindowText(str);
                    break;
        }
        case 3://下载失败
        {
                   if (!NET_DVR_StopDownload(m_lExportHandle))
                   {
                       g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopDownload");
                   }
                   else
                   {
                       g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopDownload");
                   }
                   m_bExport = FALSE;
                   m_lExportHandle = -1;
                   KillTimer(TIMER_SCHEDULE_EXPORT_PROGRESS);
                   char sTitle[64] = { 0 };
                   char sMsg[64] = { 0 };
                   g_StringLanType(sTitle, "日程管理", "Schedule Management");
                   g_StringLanType(sMsg, "导出失败", "Download fail.");
                   MessageBox(sMsg, sTitle, MB_OK | MB_ICONWARNING);
                   break;

        }
        case 4: //网络断开
        {
                    if (!NET_DVR_StopDownload(m_lExportHandle))
                    {
                        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopDownload");
                    }
                    else
                    {
                        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopDownload");
                    }
                    m_bExport = FALSE;
                    m_lExportHandle = -1;
                    KillTimer(TIMER_SCHEDULE_EXPORT_PROGRESS);
                    char sTitle[64] = { 0 };
                    char sMsg[64] = { 0 };
                    g_StringLanType(sTitle, "日程管理", "Schedule Management");
                    g_StringLanType(sMsg, "网络断开", "network disconnect");
                    MessageBox(sMsg, sTitle, MB_OK | MB_ICONWARNING);
                    break;
        }
        }
        CDialog::OnTimer(nIDEvent);

    }
}
