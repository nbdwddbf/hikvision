// DlgAcsSetExamInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgAcsSetExamInfo.h"
#include "afxdialogex.h"

#define WM_MSG_SET_EXAM_INFO_FINISH 1002

// CDlgAcsSetExamInfo 对话框

IMPLEMENT_DYNAMIC(CDlgAcsSetExamInfo, CDialog)

CDlgAcsSetExamInfo::CDlgAcsSetExamInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAcsSetExamInfo::IDD, pParent)
{
    m_csExamRoundNo = _T("123456789");
    m_csExamNo = _T("1234");
    m_csExamSubject = _T("5678");
    m_csTeacherNo = _T("4321");
    m_csTeacherName = _T("zhangsan");
    m_bExamInfoValid = TRUE;
    m_startDate = COleDateTime::GetCurrentTime();
    m_startTime = COleDateTime::GetCurrentTime();
    m_endDate = COleDateTime::GetCurrentTime();
    m_endTime = COleDateTime::GetCurrentTime();

    m_lSetExamInfoHandle = -1;
    m_dwSendIndex = 0;
}

CDlgAcsSetExamInfo::~CDlgAcsSetExamInfo()
{
}

void CDlgAcsSetExamInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_SET_EXAM_INFO, m_listSetExamInfo);
    DDX_Text(pDX, IDC_EDIT_EXAM_ROUND_NO, m_csExamRoundNo);
    DDX_Text(pDX, IDC_EDIT_EXAM_NO, m_csExamNo);
    DDX_Text(pDX, IDC_EDIT_EXAM_SUBJECT, m_csExamSubject);
    DDX_Text(pDX, IDC_EDIT_TEACHER_NO, m_csTeacherNo);
    DDX_Text(pDX, IDC_EDIT_TEACHER_NAME, m_csTeacherName);
    DDX_DateTimeCtrl(pDX, IDC_DATE_START, m_startDate);
    DDX_DateTimeCtrl(pDX, IDC_TIME_START, m_startTime);
    DDX_DateTimeCtrl(pDX, IDC_DATE_END, m_endDate);
    DDX_DateTimeCtrl(pDX, IDC_TIME_END, m_endTime);
}


BEGIN_MESSAGE_MAP(CDlgAcsSetExamInfo, CDialog)
    ON_BN_CLICKED(IDC_BTN_ADD, &CDlgAcsSetExamInfo::OnBnClickedBtnAdd)
    ON_BN_CLICKED(IDC_BTN_DELETE, &CDlgAcsSetExamInfo::OnBnClickedBtnDelete)
    ON_BN_CLICKED(IDC_BTN_CLEAR, &CDlgAcsSetExamInfo::OnBnClickedBtnClear)
    ON_BN_CLICKED(IDC_BTN_SET_LIST, &CDlgAcsSetExamInfo::OnBnClickedBtnSetList)
    ON_BN_CLICKED(IDC_BTN_DELETE_BYNO, &CDlgAcsSetExamInfo::OnBnClickedBtnDeleteByno)
    ON_BN_CLICKED(IDC_BTN_EXIT, &CDlgAcsSetExamInfo::OnBnClickedBtnExit)
    ON_MESSAGE(WM_MSG_SET_EXAM_INFO_FINISH, &CDlgAcsSetExamInfo::OnMsgSetExamInfoFinish)
END_MESSAGE_MAP()


// CDlgAcsSetExamInfo 消息处理程序

afx_msg LRESULT CDlgAcsSetExamInfo::OnMsgSetExamInfoFinish(WPARAM wParam, LPARAM lParam)
{
    if (!NET_DVR_StopRemoteConfig(m_lSetExamInfoHandle))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopRemoteConfig failed");
        return 0;
    }
    m_lSetExamInfoHandle = -1;
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_EXAM_INFO finished");
    return 0;
}

void CALLBACK g_fExamInfoCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CDlgAcsSetExamInfo* pDlg = (CDlgAcsSetExamInfo*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
    pDlg->ProcessExamInfoCallbackData(dwType, lpBuffer, dwBufLen);
}

void CDlgAcsSetExamInfo::ProcessExamInfoCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{
    if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
        DWORD dwStatus = *(DWORD*)lpBuffer;
        if (dwStatus == NET_SDK_CALLBACK_STATUS_PROCESSING)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Set Exam Info PROCESSING %d", m_dwSendIndex);

            SendNext();
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Set Exam Info Err:NET_SDK_CALLBACK_STATUS_FAILED %d", m_dwSendIndex);

            SendNext();
        }
        //下面两个关闭长连接
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Set Exam Info SUCCESS");
            PostMessage(WM_MSG_SET_EXAM_INFO_FINISH, 0, 0);
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_EXCEPTION)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Set Exam Info Exception");
            PostMessage(WM_MSG_SET_EXAM_INFO_FINISH, 0, 0);
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Set Exam Info SUCCESS");
            PostMessage(WM_MSG_SET_EXAM_INFO_FINISH, 0, 0);
        }
    }
    else if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        NET_DVR_EXAM_INFO_STATUS struExamInfoStatus = { 0 };
        memcpy(&struExamInfoStatus, lpBuffer, sizeof(struExamInfoStatus));


        BOOL bSendOk = FALSE;

        if (struExamInfoStatus.byStatus == 2)
        {
            bSendOk = TRUE;
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Set Exam Info PROCESSING,Exam Round No:%s", struExamInfoStatus.byExamRoundNo);
        }

        if (!bSendOk)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Set Exam Info Failed,Exam Round No:%s", struExamInfoStatus.byExamRoundNo);
        }

        SendNext();
    }
}

void CDlgAcsSetExamInfo::OnBnClickedBtnAdd()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    //1.get data from control
    NET_DVR_EXAM_INFO_CFG struExamInfoCfg = { 0 };
    struExamInfoCfg.dwSize = sizeof(struExamInfoCfg);
    struExamInfoCfg.byExamInfoValid = m_bExamInfoValid;
    strncpy((char *)struExamInfoCfg.byExamRoundNo, ASCII2UTF8((LPCTSTR)m_csExamRoundNo).c_str(), NET_SDK_MAX_EXAM_ROUND_NO);
    strncpy((char *)struExamInfoCfg.byExamNo, ASCII2UTF8((LPCTSTR)m_csExamNo).c_str(), NET_SDK_MAX_EXAM_NO);
    strncpy((char *)struExamInfoCfg.byExamSubject, ASCII2UTF8((LPCTSTR)m_csExamSubject).c_str(), NET_SDK_MAX_EXAM_SUBJECT);
    strncpy((char *)struExamInfoCfg.byTeacherNo, ASCII2UTF8((LPCTSTR)m_csTeacherNo).c_str(), NET_SDK_MAX_TEACHER_NO);
    strncpy((char *)struExamInfoCfg.byTeacherName, ASCII2UTF8((LPCTSTR)m_csTeacherName).c_str(), NET_SDK_MAX_TEACHER_NAME);
    struExamInfoCfg.struStartTime.dwYear = m_startDate.GetYear();
    struExamInfoCfg.struStartTime.dwMonth = m_startDate.GetMonth();
    struExamInfoCfg.struStartTime.dwDay = m_startDate.GetDay();
    struExamInfoCfg.struStartTime.dwHour = m_startTime.GetHour();
    struExamInfoCfg.struStartTime.dwMinute = m_startTime.GetMinute();
    struExamInfoCfg.struStartTime.dwSecond = m_startTime.GetSecond();
    struExamInfoCfg.struEndTime.dwYear = m_endDate.GetYear();
    struExamInfoCfg.struEndTime.dwMonth = m_endDate.GetMonth();
    struExamInfoCfg.struEndTime.dwDay = m_endDate.GetDay();
    struExamInfoCfg.struEndTime.dwHour = m_endTime.GetHour();
    struExamInfoCfg.struEndTime.dwMinute = m_endTime.GetMinute();
    struExamInfoCfg.struEndTime.dwSecond = m_endTime.GetSecond();

    //2.is duplicated?
    LPNET_DVR_EXAM_INFO_CFG pExamInfoCfg = NULL;
    int iItemIndex = GetExistItem(&struExamInfoCfg);
    if (iItemIndex == -1)
    {
        pExamInfoCfg = new NET_DVR_EXAM_INFO_CFG();
        if (pExamInfoCfg == NULL)
        {
            return;
        }
        int iSize = sizeof(NET_DVR_EXAM_INFO_CFG);
        int nItemCount = m_listSetExamInfo.GetItemCount();

        CString strItem = "";
        strItem.Format("%d", nItemCount + 1);
        iItemIndex = m_listSetExamInfo.InsertItem(nItemCount, strItem);
        m_listSetExamInfo.SetItemData(nItemCount, (DWORD)pExamInfoCfg);
    }
    else
    {
        pExamInfoCfg = (LPNET_DVR_EXAM_INFO_CFG)m_listSetExamInfo.GetItemData(iItemIndex);
    }
    memcpy(pExamInfoCfg, &struExamInfoCfg, sizeof(struExamInfoCfg));

    //3.set to list
    CString csTmp;
    char szExamRoundNo[128] = { 0 };
    char szExamNo[128] = { 0 };
    char szExamSubject[128] = { 0 };
    char szTeacherNo[128] = { 0 };
    char szTeacherName[128] = { 0 };

    memcpy(szExamRoundNo, (LPCTSTR)m_csExamRoundNo, NET_SDK_MAX_EXAM_ROUND_NO);
    csTmp.Format("%s", szExamRoundNo);
    m_listSetExamInfo.SetItemText(iItemIndex, 1, csTmp);
    memcpy(szExamNo, (LPCTSTR)m_csExamNo, NET_SDK_MAX_EXAM_NO);
    csTmp.Format("%s", szExamNo);
    m_listSetExamInfo.SetItemText(iItemIndex, 2, csTmp);
    memcpy(szExamSubject, (LPCTSTR)m_csExamSubject, NET_SDK_MAX_EXAM_SUBJECT);
    csTmp.Format("%s", szExamSubject);
    m_listSetExamInfo.SetItemText(iItemIndex, 3, csTmp);
    memcpy(szTeacherNo, (LPCTSTR)m_csTeacherNo, NET_SDK_MAX_TEACHER_NO);
    csTmp.Format("%s", szTeacherNo);
    m_listSetExamInfo.SetItemText(iItemIndex, 4, csTmp);
    memcpy(szTeacherName, (LPCTSTR)m_csTeacherName, NET_SDK_MAX_TEACHER_NAME);
    csTmp.Format("%s", szTeacherName);
    m_listSetExamInfo.SetItemText(iItemIndex, 5, csTmp);
    csTmp.Format("%04d-%02d-%02d %02d:%02d:%02d", pExamInfoCfg->struStartTime.dwYear, pExamInfoCfg->struStartTime.dwMinute, pExamInfoCfg->struStartTime.dwDay, \
        pExamInfoCfg->struStartTime.dwHour, pExamInfoCfg->struStartTime.dwMinute, pExamInfoCfg->struStartTime.dwSecond);
    m_listSetExamInfo.SetItemText(iItemIndex, 6, csTmp);
    csTmp.Format("%04d-%02d-%02d %02d:%02d:%02d", pExamInfoCfg->struEndTime.dwYear, pExamInfoCfg->struEndTime.dwMinute, pExamInfoCfg->struEndTime.dwDay, \
        pExamInfoCfg->struEndTime.dwHour, pExamInfoCfg->struEndTime.dwMinute, pExamInfoCfg->struEndTime.dwSecond);
    m_listSetExamInfo.SetItemText(iItemIndex, 7, csTmp);

    UpdateData(FALSE);
}


void CDlgAcsSetExamInfo::OnBnClickedBtnDelete()
{
    // TODO:  在此添加控件通知处理程序代码
    POSITION pos = m_listSetExamInfo.GetFirstSelectedItemPosition();

    int nItem = 0;
    int itemCount = m_listSetExamInfo.GetItemCount();

    if (pos == NULL)
    {
        TRACE(_T("No items were selected!\n"));
    }
    else
    {
        while (pos)
        {
            nItem = m_listSetExamInfo.GetNextSelectedItem(pos);
            TRACE(_T("Item %d was selected!\n"), nItem);
            // do own processing on nItem here

            LPNET_DVR_EXAM_INFO_CFG pExamInfoCfg = (LPNET_DVR_EXAM_INFO_CFG)m_listSetExamInfo.GetItemData(nItem);
            if (pExamInfoCfg != NULL)
            {
                delete pExamInfoCfg;
                pExamInfoCfg = NULL;
                m_listSetExamInfo.SetItemData(nItem, 0);
            }

            //所有的后续item，向前挪动一个单位
            for (int i = nItem + 1; i < itemCount; i++)
            {
                CString strTmp = m_listSetExamInfo.GetItemText(i, 0);
                strTmp.Format("%d", atoi((LPSTR)(LPCTSTR)strTmp) - 1);
                m_listSetExamInfo.SetItemText(i, 0, strTmp);
            }

            m_listSetExamInfo.DeleteItem(nItem);
        }
    }
}


void CDlgAcsSetExamInfo::OnBnClickedBtnClear()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    m_listSetExamInfo.DeleteAllItems();
    Clear();
    UpdateData(FALSE);
}


void CDlgAcsSetExamInfo::OnBnClickedBtnSetList()
{
    // TODO:  在此添加控件通知处理程序代码
    if (m_lSetExamInfoHandle != -1)
    {
        NET_DVR_StopRemoteConfig(m_lSetExamInfoHandle);
    }

    UpdateData(TRUE);

    NET_DVR_EXAM_INFO_COND struCond = { 0 };
    struCond.dwSize = sizeof(struCond);
    struCond.dwExamNumber = m_listSetExamInfo.GetItemCount();

    m_lSetExamInfoHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_SET_EXAM_INFO, &struCond, sizeof(struCond), g_fExamInfoCallback, this);
    if (m_lSetExamInfoHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_EXAM_INFO failed");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_EXAM_INFO success");
    }

    //上传第一项考试信息, 失败时关闭连接
    m_dwSendIndex = 0;
    if (!SendFirst())
    {
        NET_DVR_StopRemoteConfig(m_lSetExamInfoHandle);
        m_lSetExamInfoHandle = -1;
    }
}


void CDlgAcsSetExamInfo::OnBnClickedBtnDeleteByno()
{
    // TODO:  在此添加控件通知处理程序代码
    m_bExamInfoValid = FALSE;
    CDlgAcsSetExamInfo::OnBnClickedBtnSetList();
    m_bExamInfoValid = TRUE;
}


void CDlgAcsSetExamInfo::OnBnClickedBtnExit()
{
    // TODO:  在此添加控件通知处理程序代码
    Clear();
    CDialog::OnCancel();
}

BOOL CDlgAcsSetExamInfo::OnInitDialog()
{
    CDialog::OnInitDialog();

    UpdateData(TRUE);

    char szLan[128] = { 0 };
    m_listSetExamInfo.SetExtendedStyle(m_listSetExamInfo.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES);
    g_StringLanType(szLan, "序号", "No");
    m_listSetExamInfo.InsertColumn(0, szLan, LVCFMT_CENTER, 40, -1);
    g_StringLanType(szLan, "考试场次编号", "Exam Round No");
    m_listSetExamInfo.InsertColumn(1, szLan, LVCFMT_CENTER, 100, -1);
    g_StringLanType(szLan, "考试编号", "Exam No");
    m_listSetExamInfo.InsertColumn(2, szLan, LVCFMT_CENTER, 100, -1);
    g_StringLanType(szLan, "考试科目", "Exam Subject");
    m_listSetExamInfo.InsertColumn(3, szLan, LVCFMT_CENTER, 100, -1);
    g_StringLanType(szLan, "监考老师编号", "Teacher No");
    m_listSetExamInfo.InsertColumn(4, szLan, LVCFMT_CENTER, 100, -1);
    g_StringLanType(szLan, "监考老师姓名", "Teacher Name");
    m_listSetExamInfo.InsertColumn(5, szLan, LVCFMT_CENTER, 100, -1);
    g_StringLanType(szLan, "考试开始时间", "Start Time");
    m_listSetExamInfo.InsertColumn(6, szLan, LVCFMT_CENTER, 100, -1);
    g_StringLanType(szLan, "考试结束时间", "End Time");
    m_listSetExamInfo.InsertColumn(7, szLan, LVCFMT_CENTER, 100, -1);

    UpdateData(FALSE);
    return TRUE;
}

/** @fn  CDlgAcsSetExamInfo::GetExistItem(const NET_DVR_EXAM_INFO_CFG *lpExamInfoCfg)
*  @brief 从列表中查找是否存在相同的实例
*  @param(IN) NET_DVR_EXAM_INFO_CFG *lpExamInfoCfg
*  @return  index--the index, -1--no duplicate.
*/
int CDlgAcsSetExamInfo::GetExistItem(const NET_DVR_EXAM_INFO_CFG *lpExamInfoCfg)
{
    int nItemCount = m_listSetExamInfo.GetItemCount();
    int i = 0;
    LPNET_DVR_EXAM_INFO_CFG lpTemp = NULL;
    for (i = 0; i < nItemCount; i++)
    {
        lpTemp = (LPNET_DVR_EXAM_INFO_CFG)m_listSetExamInfo.GetItemData(i);
        if (!lpExamInfoCfg)
        {
            continue;
        }
        //考试场次编号做唯一标识，进行重复判断
        if (strcmp((char *)lpExamInfoCfg->byExamRoundNo, (char *)lpTemp->byExamRoundNo) == 0)
        {
            return i;
        }
    }
    return -1;
}

/** @fn  void CDlgAcsSetExamInfo::Clear()
*  @brief 资源释放
*  @return  void
*/
void CDlgAcsSetExamInfo::Clear()
{
    int nItemCount = m_listSetExamInfo.GetItemCount();
    for (int i = 0; i < nItemCount; i++)
    {
        LPNET_DVR_EXAM_INFO_CFG pExamInfoCfg = (LPNET_DVR_EXAM_INFO_CFG)m_listSetExamInfo.GetItemData(i);
        if (pExamInfoCfg != NULL)
        {
            delete pExamInfoCfg;
            pExamInfoCfg = NULL;
            m_listSetExamInfo.SetItemData(i, 0);
        }
    }
    return;
}

/** @fn BOOL SendFirst()
*  @brief 发送第一项考试信息
*  @return  HPR_TRUE--success, HPR_FALSE--fail.
*/
BOOL CDlgAcsSetExamInfo::SendFirst()
{
    int nItemCount = m_listSetExamInfo.GetItemCount();

    if (nItemCount <= 0)
    {
        AfxMessageBox("Please add info to list at first");
        return FALSE;
    }

    m_dwSendIndex = 0;

    //获取第一个考试数据
    LPNET_DVR_EXAM_INFO_CFG pExamInfoCfg = (LPNET_DVR_EXAM_INFO_CFG)m_listSetExamInfo.GetItemData(m_dwSendIndex);

    if (pExamInfoCfg == NULL)
    {
        return FALSE;
    }

    pExamInfoCfg->byExamInfoValid = m_bExamInfoValid;

    if (!NET_DVR_SendRemoteConfig(m_lSetExamInfoHandle, ENUM_ACS_SEND_DATA, (char *)pExamInfoCfg, sizeof(*pExamInfoCfg)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Send Fail,Exam Round No: %s", pExamInfoCfg->byExamRoundNo);
        return FALSE;
    }

    return TRUE;
}

/** @fn BOOL SendNext()
*  @brief 发送下一项考试信息
*  @return  HPR_TRUE--success, HPR_FALSE--fail.
*/
BOOL CDlgAcsSetExamInfo::SendNext()
{
    int nItemCount = m_listSetExamInfo.GetItemCount();

    if (nItemCount < 0)
    {
        AfxMessageBox("Please add info to list at first");
    }

    m_dwSendIndex++;

    //已经发完了
    if (m_dwSendIndex >= nItemCount)
    {
        return TRUE;
    }

    LPNET_DVR_EXAM_INFO_CFG pExamInfoCfg = (LPNET_DVR_EXAM_INFO_CFG)m_listSetExamInfo.GetItemData(m_dwSendIndex);

    pExamInfoCfg->byExamInfoValid = m_bExamInfoValid;

    if (pExamInfoCfg == NULL)
    {
        return FALSE;
    }

    if (!NET_DVR_SendRemoteConfig(m_lSetExamInfoHandle, ENUM_ACS_SEND_DATA, (char *)pExamInfoCfg, sizeof(*pExamInfoCfg)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Send Fail,Exam Round No: %s", pExamInfoCfg->byExamRoundNo);
        PostMessage(WM_MSG_SET_EXAM_INFO_FINISH, 0, 0);
        return FALSE;
    }

    return TRUE;
}