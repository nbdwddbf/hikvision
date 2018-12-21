// DlgAcsSearchExamCompareResult.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgAcsSearchExamCompareResult.h"
#include "afxdialogex.h"

void CALLBACK g_fSearchExamCompareResultCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData);
#define WM_MSG_ADD_EXAM_COMPARE_RESULT_TOLIST 1002
#define WM_MSG_SEARCH_EXAM_COMPARE_RESULT_FINISH 1003

// CDlgAcsSearchExamCompareResult 对话框
CDlgAcsSearchExamCompareResult * pSearchExamCompareResult = NULL;

IMPLEMENT_DYNAMIC(CDlgAcsSearchExamCompareResult, CDialog)

CDlgAcsSearchExamCompareResult::CDlgAcsSearchExamCompareResult(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAcsSearchExamCompareResult::IDD, pParent)
{
    m_csExamRoundNo = _T("123456789");
    m_csExamNo = _T("1234");
    m_startDate = COleDateTime::GetCurrentTime();
    m_startTime = COleDateTime::GetCurrentTime();
    m_endDate = COleDateTime::GetCurrentTime();
    m_endTime = COleDateTime::GetCurrentTime();

    m_lSearchExamCompareResultHandle = -1;
}

CDlgAcsSearchExamCompareResult::~CDlgAcsSearchExamCompareResult()
{
}

void CDlgAcsSearchExamCompareResult::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_SEARCH_EXAM_COMPARE_RESULT, m_listSearchExamCompareResult);
    DDX_Text(pDX, IDC_EDIT_EXAM_ROUND_NO, m_csExamRoundNo);
    DDX_Text(pDX, IDC_EDIT_EXAM_NO, m_csExamNo);
    DDX_DateTimeCtrl(pDX, IDC_DATE_START, m_startDate);
    DDX_DateTimeCtrl(pDX, IDC_TIME_START, m_startTime);
    DDX_DateTimeCtrl(pDX, IDC_DATE_END, m_endDate);
    DDX_DateTimeCtrl(pDX, IDC_TIME_END, m_endTime);
}


BEGIN_MESSAGE_MAP(CDlgAcsSearchExamCompareResult, CDialog)
    ON_BN_CLICKED(IDC_BTN_SEARCH, &CDlgAcsSearchExamCompareResult::OnBnClickedBtnSearch)
    ON_MESSAGE(WM_MSG_ADD_EXAM_COMPARE_RESULT_TOLIST, OnMsgAddExamCompareResultToList)
    ON_MESSAGE(WM_MSG_SEARCH_EXAM_COMPARE_RESULT_FINISH, OnMsgSearchExamCompareResultFinish)
END_MESSAGE_MAP()


// CDlgAcsSearchExamCompareResult 消息处理程序


void CDlgAcsSearchExamCompareResult::OnBnClickedBtnSearch()
{
    // TODO:  在此添加控件通知处理程序代码
    m_listSearchExamCompareResult.DeleteAllItems();
    UpdateData(TRUE);

    NET_DVR_EXAM_COMPARE_RESULT_COND struExamCompareResultCond = { 0 };
    struExamCompareResultCond.dwSize = sizeof(struExamCompareResultCond);
    strncpy((char *)struExamCompareResultCond.byExamRoundNo, ASCII2UTF8((LPCTSTR)m_csExamRoundNo).c_str(), NET_SDK_MAX_EXAM_ROUND_NO);
    strncpy((char *)struExamCompareResultCond.byExamNo, ASCII2UTF8((LPCTSTR)m_csExamNo).c_str(), NET_SDK_MAX_EXAM_NO);
    struExamCompareResultCond.struStartTime.dwYear = m_startDate.GetYear();
    struExamCompareResultCond.struStartTime.dwMonth = m_startDate.GetMonth();
    struExamCompareResultCond.struStartTime.dwDay = m_startDate.GetDay();
    struExamCompareResultCond.struStartTime.dwHour = m_startTime.GetHour();
    struExamCompareResultCond.struStartTime.dwMinute = m_startTime.GetMinute();
    struExamCompareResultCond.struStartTime.dwSecond = m_startTime.GetSecond();
    struExamCompareResultCond.struEndTime.dwYear = m_endDate.GetYear();
    struExamCompareResultCond.struEndTime.dwMonth = m_endDate.GetMonth();
    struExamCompareResultCond.struEndTime.dwDay = m_endDate.GetDay();
    struExamCompareResultCond.struEndTime.dwHour = m_endTime.GetHour();
    struExamCompareResultCond.struEndTime.dwMinute = m_endTime.GetMinute();
    struExamCompareResultCond.struEndTime.dwSecond = m_endTime.GetSecond();

    if (m_lSearchExamCompareResultHandle != -1)
    {
        NET_DVR_StopRemoteConfig(m_lSearchExamCompareResultHandle);
    }
    m_lSearchNum = 0;
    m_lSearchExamCompareResultHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_SEARCH_EXAM_COMPARE_RESULT, &struExamCompareResultCond, sizeof(struExamCompareResultCond), g_fSearchExamCompareResultCallback, this);
    if (m_lSearchExamCompareResultHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SEARCH_EXAM_COMPARE_RESULT");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SEARCH_EXAM_COMPARE_RESULT");
    }

    UpdateData(FALSE);
}

BOOL CDlgAcsSearchExamCompareResult::OnInitDialog()
{
    CDialog::OnInitDialog();

    UpdateData(TRUE);

    pSearchExamCompareResult = this;

    char szLan[128] = { 0 };
    m_listSearchExamCompareResult.SetExtendedStyle(m_listSearchExamCompareResult.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES);
    g_StringLanType(szLan, "序号", "No");
    m_listSearchExamCompareResult.InsertColumn(0, szLan, LVCFMT_CENTER, 40, -1);
    g_StringLanType(szLan, "时间", "Time");
    m_listSearchExamCompareResult.InsertColumn(1, szLan, LVCFMT_CENTER, 100, -1);
    g_StringLanType(szLan, "考生编号", "Examinee No");
    m_listSearchExamCompareResult.InsertColumn(2, szLan, LVCFMT_CENTER, 100, -1);
    g_StringLanType(szLan, "准考证号", "Admission Ticket");
    m_listSearchExamCompareResult.InsertColumn(3, szLan, LVCFMT_CENTER, 100, -1);
    g_StringLanType(szLan, "考试编号", "Exam No");
    m_listSearchExamCompareResult.InsertColumn(4, szLan, LVCFMT_CENTER, 100, -1);
    g_StringLanType(szLan, "考试场次编号", "Exam Round No");
    m_listSearchExamCompareResult.InsertColumn(5, szLan, LVCFMT_CENTER, 100, -1);
    g_StringLanType(szLan, "姓名", "Name");
    m_listSearchExamCompareResult.InsertColumn(6, szLan, LVCFMT_CENTER, 100, -1);
    g_StringLanType(szLan, "考生关联的卡号", "Card No");
    m_listSearchExamCompareResult.InsertColumn(7, szLan, LVCFMT_CENTER, 100, -1);

    UpdateData(FALSE);
    return TRUE;
}

void CALLBACK g_fSearchExamCompareResultCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CDlgAcsSearchExamCompareResult* pDlg = (CDlgAcsSearchExamCompareResult*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
    pDlg->ProcessSearchExamCompareResultData(dwType, lpBuffer, dwBufLen);
}

void CDlgAcsSearchExamCompareResult::ProcessSearchExamCompareResultData(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{
    CString strItem = "";
    if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        LPNET_DVR_EXAM_COMPARE_RESULT_CFG lpExamCompareResultCfg = new NET_DVR_EXAM_COMPARE_RESULT_CFG;
        memcpy(lpExamCompareResultCfg, lpBuffer, sizeof(*lpExamCompareResultCfg));
        if (lpExamCompareResultCfg->dwPicDataLen != 0)
        {
            char* pPicData = new char[lpExamCompareResultCfg->dwPicDataLen];
            if (lpExamCompareResultCfg->pPicData == NULL)
            {
                return;
            }
            memset(pPicData, 0, lpExamCompareResultCfg->dwPicDataLen);
            memcpy(pPicData, lpExamCompareResultCfg->pPicData, lpExamCompareResultCfg->dwPicDataLen);
            lpExamCompareResultCfg->pPicData = pPicData;
        }
        PostMessage(WM_MSG_ADD_EXAM_COMPARE_RESULT_TOLIST, (WPARAM)lpExamCompareResultCfg, 0);
    }
    else if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
        DWORD dwStatus = *(DWORD*)lpBuffer;
        if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            PostMessage(WM_MSG_SEARCH_EXAM_COMPARE_RESULT_FINISH, 0, 0);
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SEARCH_EXAM_COMPARE_RESULT failed");
        }
    }
}

LRESULT CDlgAcsSearchExamCompareResult::OnMsgAddExamCompareResultToList(WPARAM wParam, LPARAM lParam)
{
    LPNET_DVR_EXAM_COMPARE_RESULT_CFG lpExamCompareResultCfg = (LPNET_DVR_EXAM_COMPARE_RESULT_CFG)wParam;
    if (lpExamCompareResultCfg->dwSize == 0)
    {
        if (lpExamCompareResultCfg->pPicData != NULL)
        {
            delete[] lpExamCompareResultCfg->pPicData;
        }
        lpExamCompareResultCfg->pPicData = NULL;
        if (lpExamCompareResultCfg != NULL)
        {
            delete lpExamCompareResultCfg;
        }
        lpExamCompareResultCfg = NULL;
        return 0;
    }

    //LONG bRet = -1;

    CString csTmp;

    csTmp.Format("%d", pSearchExamCompareResult->m_lSearchNum + 1);
    pSearchExamCompareResult->m_listSearchExamCompareResult.InsertItem(pSearchExamCompareResult->m_lSearchNum, csTmp, 0);

    csTmp.Format("%04d-%02d-%02d %02d:%02d:%02d", lpExamCompareResultCfg->struTime.dwYear, lpExamCompareResultCfg->struTime.dwMonth, lpExamCompareResultCfg->struTime.dwDay, \
        lpExamCompareResultCfg->struTime.dwHour, lpExamCompareResultCfg->struTime.dwMinute, lpExamCompareResultCfg->struTime.dwSecond);
    pSearchExamCompareResult->m_listSearchExamCompareResult.SetItemText(pSearchExamCompareResult->m_lSearchNum, 1, csTmp);

    csTmp.Format("%s", lpExamCompareResultCfg->byExamineeNo);
    pSearchExamCompareResult->m_listSearchExamCompareResult.SetItemText(pSearchExamCompareResult->m_lSearchNum, 2, csTmp);

    csTmp.Format("%s", lpExamCompareResultCfg->byAdmissionTicket);
    pSearchExamCompareResult->m_listSearchExamCompareResult.SetItemText(pSearchExamCompareResult->m_lSearchNum, 3, csTmp);

    csTmp.Format("%s", lpExamCompareResultCfg->byExamNo);
    pSearchExamCompareResult->m_listSearchExamCompareResult.SetItemText(pSearchExamCompareResult->m_lSearchNum, 4, csTmp);

    csTmp.Format("%s", lpExamCompareResultCfg->byExamRoundNo);
    pSearchExamCompareResult->m_listSearchExamCompareResult.SetItemText(pSearchExamCompareResult->m_lSearchNum, 5, csTmp);

    csTmp.Format("%s", lpExamCompareResultCfg->byName);
    pSearchExamCompareResult->m_listSearchExamCompareResult.SetItemText(pSearchExamCompareResult->m_lSearchNum, 6, csTmp);

    csTmp.Format("%s", lpExamCompareResultCfg->byCardNo);
    pSearchExamCompareResult->m_listSearchExamCompareResult.SetItemText(pSearchExamCompareResult->m_lSearchNum, 7, csTmp);
    

    if (lpExamCompareResultCfg->dwPicDataLen > 0 && lpExamCompareResultCfg->pPicData != NULL)
    {
        SYSTEMTIME t;
        GetLocalTime(&t);
        char chTime[128];
        char cPicName[256] = { 0 };
        DWORD dwWrittenBytes = 0;
        sprintf(chTime, "%4.4d-%2.2d-%2.2d_%2.2d-%2.2d-%2.2d", lpExamCompareResultCfg->struTime.dwYear, lpExamCompareResultCfg->struTime.dwMonth, lpExamCompareResultCfg->struTime.dwDay, \
            lpExamCompareResultCfg->struTime.dwHour, lpExamCompareResultCfg->struTime.dwMinute, lpExamCompareResultCfg->struTime.dwSecond);

        sprintf(cPicName, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[m_iDeviceIndex].chDeviceIP);

        if (GetFileAttributes(cPicName) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(cPicName, NULL);
        }

        sprintf(cPicName, "%s\\LocalTime[%s]ExamCompareResultPicture[%d].jpg", cPicName, chTime, pSearchExamCompareResult->m_lSearchNum);

        HANDLE hFile = CreateFile(cPicName, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            if (lpExamCompareResultCfg->pPicData != NULL)
            {
                delete[] lpExamCompareResultCfg->pPicData;
            }
            lpExamCompareResultCfg->pPicData = NULL;
            if (lpExamCompareResultCfg != NULL)
            {
                delete lpExamCompareResultCfg;
            }
            lpExamCompareResultCfg = NULL;
            return 0;
        }
        DWORD dwRet = WriteFile(hFile, lpExamCompareResultCfg->pPicData, lpExamCompareResultCfg->dwPicDataLen, &dwWrittenBytes, NULL);
        if (dwRet == 0 || dwWrittenBytes < lpExamCompareResultCfg->dwPicDataLen)
        {
            DWORD dwError = GetLastError();
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Exam Compare Result Picture Write to File Fail.System Error:%d, dwPicLen:%d, pBuffer:%d ", dwError, lpExamCompareResultCfg->dwPicDataLen, dwWrittenBytes);
        }
        CloseHandle(hFile);
        hFile = NULL;
    }

    pSearchExamCompareResult->m_lSearchNum++;
    if (lpExamCompareResultCfg->pPicData != NULL)
    {
        delete[] lpExamCompareResultCfg->pPicData;
    }
    lpExamCompareResultCfg->pPicData = NULL;
    if (lpExamCompareResultCfg != NULL)
    {
        delete lpExamCompareResultCfg;
    }
    lpExamCompareResultCfg = NULL;
    return 0;
}

LRESULT CDlgAcsSearchExamCompareResult::OnMsgSearchExamCompareResultFinish(WPARAM wParam, LPARAM lParam)
{
    if (m_lSearchExamCompareResultHandle != -1)
    {
        NET_DVR_StopRemoteConfig(m_lSearchExamCompareResultHandle);
        m_lSearchExamCompareResultHandle = -1;
    }
    m_lSearchNum = 0;
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SEARCH_EXAM_COMPARE_RESULT finish");
    return 0;
}