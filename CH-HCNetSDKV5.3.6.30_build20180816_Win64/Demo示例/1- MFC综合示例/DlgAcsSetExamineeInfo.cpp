// DlgAcsSetExamineeInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgAcsSetExamineeInfo.h"
#include "afxdialogex.h"

#define WM_MSG_SET_EXAMINEE_INFO_FINISH 1003

// CDlgAcsSetExamineeInfo 对话框

IMPLEMENT_DYNAMIC(CDlgAcsSetExamineeInfo, CDialog)

CDlgAcsSetExamineeInfo::CDlgAcsSetExamineeInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAcsSetExamineeInfo::IDD, pParent)
{
    m_csExamineeNo = _T("123456789");
    m_csAdmissionTicket = _T("987654321");
    m_csExamRoundNo = _T("123456789");
    m_csName = _T("lisi");
    m_csCardNo = _T("43218765");
    m_bExamineeInfoValid = TRUE;

    m_lSetExamineeInfoHandle = -1;
    m_dwSendIndex = 0;
}

CDlgAcsSetExamineeInfo::~CDlgAcsSetExamineeInfo()
{
}

void CDlgAcsSetExamineeInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_SET_EXAMINEE_INFO, m_listSetExamineeInfo);
    DDX_Text(pDX, IDC_EDIT_EXAMINEE_NO, m_csExamineeNo);
    DDX_Text(pDX, IDC_EDIT_ADMISSION_TICKET, m_csAdmissionTicket);
    DDX_Text(pDX, IDC_EDIT_EXAM_ROUND_NO, m_csExamRoundNo);
    DDX_Text(pDX, IDC_EDIT_NAME, m_csName);
    DDX_Text(pDX, IDC_EDIT_CARD_NO, m_csCardNo);
    DDX_Control(pDX, IDC_CMB_SEX, m_cmbSex);
}


BEGIN_MESSAGE_MAP(CDlgAcsSetExamineeInfo, CDialog)
    ON_BN_CLICKED(IDC_BTN_ADD, &CDlgAcsSetExamineeInfo::OnBnClickedBtnAdd)
    ON_BN_CLICKED(IDC_BTN_DELETE, &CDlgAcsSetExamineeInfo::OnBnClickedBtnDelete)
    ON_BN_CLICKED(IDC_BTN_CLEAR, &CDlgAcsSetExamineeInfo::OnBnClickedBtnClear)
    ON_BN_CLICKED(IDC_BTN_SET_LIST, &CDlgAcsSetExamineeInfo::OnBnClickedBtnSetList)
    ON_BN_CLICKED(IDC_BTN_DELETE_BYNO, &CDlgAcsSetExamineeInfo::OnBnClickedBtnDeleteByno)
    ON_BN_CLICKED(IDC_BTN_EXIT, &CDlgAcsSetExamineeInfo::OnBnClickedBtnExit)
    ON_MESSAGE(WM_MSG_SET_EXAMINEE_INFO_FINISH, &CDlgAcsSetExamineeInfo::OnMsgSetExamineeInfoFinish)
END_MESSAGE_MAP()


// CDlgAcsSetExamineeInfo 消息处理程序
afx_msg LRESULT CDlgAcsSetExamineeInfo::OnMsgSetExamineeInfoFinish(WPARAM wParam, LPARAM lParam)
{
    if (!NET_DVR_StopRemoteConfig(m_lSetExamineeInfoHandle))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopRemoteConfig failed");
        return 0;
    }
    m_lSetExamineeInfoHandle = -1;
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_EXAM_INFO finished");
    return 0;
}

void CALLBACK g_fExamineeInfoCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CDlgAcsSetExamineeInfo* pDlg = (CDlgAcsSetExamineeInfo*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
    pDlg->ProcessExamineeInfoCallbackData(dwType, lpBuffer, dwBufLen);
}

void CDlgAcsSetExamineeInfo::ProcessExamineeInfoCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{
    if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
        DWORD dwStatus = *(DWORD*)lpBuffer;
        if (dwStatus == NET_SDK_CALLBACK_STATUS_PROCESSING)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Set Examinee Info PROCESSING %d", m_dwSendIndex);

            SendNext();
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Set Examinee Info Err:NET_SDK_CALLBACK_STATUS_FAILED %d", m_dwSendIndex);

            SendNext();
        }
        //下面两个关闭长连接
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Set Examinee Info SUCCESS");
            PostMessage(WM_MSG_SET_EXAMINEE_INFO_FINISH, 0, 0);
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_EXCEPTION)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Set Examinee Info Exception");
            PostMessage(WM_MSG_SET_EXAMINEE_INFO_FINISH, 0, 0);
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Set Examinee Info SUCCESS");
            PostMessage(WM_MSG_SET_EXAMINEE_INFO_FINISH, 0, 0);
        }
    }
    else if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        NET_DVR_EXAMINEE_INFO_STATUS struExamineeInfoStatus = { 0 };
        memcpy(&struExamineeInfoStatus, lpBuffer, sizeof(struExamineeInfoStatus));


        BOOL bSendOk = FALSE;

        if (struExamineeInfoStatus.byStatus == 2)
        {
            bSendOk = TRUE;
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Set Examinee Info PROCESSING,Examinee No:%s", struExamineeInfoStatus.byExamineeNo);
        }

        if (!bSendOk)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Set Examinee Info Failed,Examinee No:%s", struExamineeInfoStatus.byExamineeNo);
        }

        SendNext();
    }
}

void CDlgAcsSetExamineeInfo::OnBnClickedBtnAdd()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    //1.get data from control
    NET_DVR_EXAMINEE_INFO_CFG struExamineeInfoCfg = { 0 };
    struExamineeInfoCfg.dwSize = sizeof(struExamineeInfoCfg);
    struExamineeInfoCfg.byExamineeInfoValid = m_bExamineeInfoValid;
    strncpy((char *)struExamineeInfoCfg.byExamineeNo, ASCII2UTF8((LPCTSTR)m_csExamineeNo).c_str(), NET_SDK_MAX_EXAMINEE_NO);
    strncpy((char *)struExamineeInfoCfg.byAdmissionTicket, ASCII2UTF8((LPCTSTR)m_csAdmissionTicket).c_str(), NET_SDK_MAX_ADMISSION_TICKET);
    strncpy((char *)struExamineeInfoCfg.byExamRoundNo, ASCII2UTF8((LPCTSTR)m_csExamRoundNo).c_str(), NET_SDK_MAX_EXAM_ROUND_NO);
    strncpy((char *)struExamineeInfoCfg.byName, ASCII2UTF8((LPCTSTR)m_csName).c_str(), NAME_LEN);
    strncpy((char *)struExamineeInfoCfg.byCardNo, ASCII2UTF8((LPCTSTR)m_csCardNo).c_str(), ACS_CARD_NO_LEN);
    struExamineeInfoCfg.bySex = m_cmbSex.GetCurSel();
    
    //2.is duplicated?
    LPNET_DVR_EXAMINEE_INFO_CFG pExamineeInfoCfg = NULL;
    int iItemIndex = GetExistItem(&struExamineeInfoCfg);
    if (iItemIndex == -1)
    {
        pExamineeInfoCfg = new NET_DVR_EXAMINEE_INFO_CFG();
        if (pExamineeInfoCfg == NULL)
        {
            return;
        }
        int iSize = sizeof(NET_DVR_EXAMINEE_INFO_CFG);
        int nItemCount = m_listSetExamineeInfo.GetItemCount();

        CString strItem = "";
        strItem.Format("%d", nItemCount + 1);
        iItemIndex = m_listSetExamineeInfo.InsertItem(nItemCount, strItem);
        m_listSetExamineeInfo.SetItemData(nItemCount, (DWORD)pExamineeInfoCfg);
    }
    else
    {
        pExamineeInfoCfg = (LPNET_DVR_EXAMINEE_INFO_CFG)m_listSetExamineeInfo.GetItemData(iItemIndex);
    }
    memcpy(pExamineeInfoCfg, &struExamineeInfoCfg, sizeof(struExamineeInfoCfg));

    //3.set to list
    CString csTmp;
    char szLan[128] = { 0 };
    char szExamineeNo[128] = { 0 };
    char szAdmissionTicket[128] = { 0 };
    char szExamRoundNo[128] = { 0 };
    char szName[128] = { 0 };
    char szCardNo[128] = { 0 };

    memcpy(szExamineeNo, (LPCTSTR)m_csExamineeNo, NET_SDK_MAX_EXAMINEE_NO);
    csTmp.Format("%s", szExamineeNo);
    m_listSetExamineeInfo.SetItemText(iItemIndex, 1, csTmp);
    memcpy(szAdmissionTicket, (LPCTSTR)m_csAdmissionTicket, NET_SDK_MAX_ADMISSION_TICKET);
    csTmp.Format("%s", szAdmissionTicket);
    m_listSetExamineeInfo.SetItemText(iItemIndex, 2, csTmp);
    memcpy(szExamRoundNo, (LPCTSTR)m_csExamRoundNo, NET_SDK_MAX_EXAM_ROUND_NO);
    csTmp.Format("%s", szExamRoundNo);
    m_listSetExamineeInfo.SetItemText(iItemIndex, 3, csTmp);
    memcpy(szName, (LPCTSTR)m_csName, NAME_LEN);
    csTmp.Format("%s", szName);
    m_listSetExamineeInfo.SetItemText(iItemIndex, 4, csTmp);
    memcpy(szCardNo, (LPCTSTR)m_csCardNo, ACS_CARD_NO_LEN);
    csTmp.Format("%s", szCardNo);
    m_listSetExamineeInfo.SetItemText(iItemIndex, 5, csTmp);

    switch (pExamineeInfoCfg->bySex)
    {
    case 0:
        g_StringLanType(szLan, "无效", "Invalid");
        csTmp.Format("%s", szLan);
        break;
    case 1:
        g_StringLanType(szLan, "男", "Male");
        csTmp.Format("%s", szLan);
        break;
    case 2:
        g_StringLanType(szLan, "女", "Female");
        csTmp.Format("%s", szLan);
        break;
    }
    m_listSetExamineeInfo.SetItemText(iItemIndex, 6, csTmp);

    UpdateData(FALSE);
}


void CDlgAcsSetExamineeInfo::OnBnClickedBtnDelete()
{
    // TODO:  在此添加控件通知处理程序代码
    POSITION pos = m_listSetExamineeInfo.GetFirstSelectedItemPosition();

    int nItem = 0;
    int itemCount = m_listSetExamineeInfo.GetItemCount();

    if (pos == NULL)
    {
        TRACE(_T("No items were selected!\n"));
    }
    else
    {
        while (pos)
        {
            nItem = m_listSetExamineeInfo.GetNextSelectedItem(pos);
            TRACE(_T("Item %d was selected!\n"), nItem);
            // do own processing on nItem here

            LPNET_DVR_EXAMINEE_INFO_CFG pExamineeInfoCfg = (LPNET_DVR_EXAMINEE_INFO_CFG)m_listSetExamineeInfo.GetItemData(nItem);
            if (pExamineeInfoCfg != NULL)
            {
                delete pExamineeInfoCfg;
                pExamineeInfoCfg = NULL;
                m_listSetExamineeInfo.SetItemData(nItem, 0);
            }

            //所有的后续item，向前挪动一个单位
            for (int i = nItem + 1; i < itemCount; i++)
            {
                CString strTmp = m_listSetExamineeInfo.GetItemText(i, 0);
                strTmp.Format("%d", atoi((LPSTR)(LPCTSTR)strTmp) - 1);
                m_listSetExamineeInfo.SetItemText(i, 0, strTmp);
            }

            m_listSetExamineeInfo.DeleteItem(nItem);
        }
    }
}


void CDlgAcsSetExamineeInfo::OnBnClickedBtnClear()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    m_listSetExamineeInfo.DeleteAllItems();
    Clear();
    UpdateData(FALSE);
}


void CDlgAcsSetExamineeInfo::OnBnClickedBtnSetList()
{
    // TODO:  在此添加控件通知处理程序代码
    if (m_lSetExamineeInfoHandle != -1)
    {
        NET_DVR_StopRemoteConfig(m_lSetExamineeInfoHandle);
    }

    UpdateData(TRUE);

    NET_DVR_EXAMINEE_INFO_COND struCond = { 0 };
    struCond.dwSize = sizeof(struCond);
    struCond.dwExamineeNumber = m_listSetExamineeInfo.GetItemCount();

    m_lSetExamineeInfoHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_SET_EXAMINEE_INFO, &struCond, sizeof(struCond), g_fExamineeInfoCallback, this);
    if (m_lSetExamineeInfoHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_EXAMINEE_INFO failed");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_EXAMINEE_INFO success");
    }

    //上传第一项考试信息, 失败时关闭连接
    m_dwSendIndex = 0;
    if (!SendFirst())
    {
        NET_DVR_StopRemoteConfig(m_lSetExamineeInfoHandle);
        m_lSetExamineeInfoHandle = -1;
    }
}


void CDlgAcsSetExamineeInfo::OnBnClickedBtnDeleteByno()
{
    // TODO:  在此添加控件通知处理程序代码
}


void CDlgAcsSetExamineeInfo::OnBnClickedBtnExit()
{
    // TODO:  在此添加控件通知处理程序代码
    Clear();
    CDialog::OnCancel();
}

BOOL CDlgAcsSetExamineeInfo::OnInitDialog()
{
    CDialog::OnInitDialog();

    UpdateData(TRUE);

    char szLan[128] = { 0 };
    m_listSetExamineeInfo.SetExtendedStyle(m_listSetExamineeInfo.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES);
    g_StringLanType(szLan, "序号", "No");
    m_listSetExamineeInfo.InsertColumn(0, szLan, LVCFMT_CENTER, 40, -1);
    g_StringLanType(szLan, "考生编号", "Examinee No");
    m_listSetExamineeInfo.InsertColumn(1, szLan, LVCFMT_CENTER, 100, -1);
    g_StringLanType(szLan, "准考证号", "Admission Ticket");
    m_listSetExamineeInfo.InsertColumn(2, szLan, LVCFMT_CENTER, 100, -1);
    g_StringLanType(szLan, "考试场次编号", "Exam Round No");
    m_listSetExamineeInfo.InsertColumn(3, szLan, LVCFMT_CENTER, 100, -1);
    g_StringLanType(szLan, "姓名", "Name");
    m_listSetExamineeInfo.InsertColumn(4, szLan, LVCFMT_CENTER, 100, -1);
    g_StringLanType(szLan, "考生关联的卡号", "Card No");
    m_listSetExamineeInfo.InsertColumn(5, szLan, LVCFMT_CENTER, 100, -1);
    g_StringLanType(szLan, "性别", "Sex");
    m_listSetExamineeInfo.InsertColumn(6, szLan, LVCFMT_CENTER, 100, -1);

    m_cmbSex.SetCurSel(1);

    UpdateData(FALSE);
    return TRUE;
}

/** @fn  CDlgAcsSetExamineeInfo::GetExistItem(const NET_DVR_EXAMINEE_INFO_CFG *lpExamineeInfoCfg)
*  @brief 从列表中查找是否存在相同的实例
*  @param(IN) NET_DVR_EXAMINEE_INFO_CFG *lpExamineeInfoCfg
*  @return  index--the index, -1--no duplicate.
*/
int CDlgAcsSetExamineeInfo::GetExistItem(const NET_DVR_EXAMINEE_INFO_CFG *lpExamineeInfoCfg)
{
    int nItemCount = m_listSetExamineeInfo.GetItemCount();
    int i = 0;
    LPNET_DVR_EXAMINEE_INFO_CFG lpTemp = NULL;
    for (i = 0; i < nItemCount; i++)
    {
        lpTemp = (LPNET_DVR_EXAMINEE_INFO_CFG)m_listSetExamineeInfo.GetItemData(i);
        if (!lpExamineeInfoCfg)
        {
            continue;
        }
        //考生编号和考试场次编号做唯一标识，进行重复判断
        if ((strcmp((char *)lpExamineeInfoCfg->byExamineeNo, (char *)lpTemp->byExamineeNo) == 0) && (strcmp((char *)lpExamineeInfoCfg->byExamRoundNo, (char *)lpTemp->byExamRoundNo) == 0))
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
void CDlgAcsSetExamineeInfo::Clear()
{
    int nItemCount = m_listSetExamineeInfo.GetItemCount();
    for (int i = 0; i < nItemCount; i++)
    {
        LPNET_DVR_EXAMINEE_INFO_CFG pExamineeInfoCfg = (LPNET_DVR_EXAMINEE_INFO_CFG)m_listSetExamineeInfo.GetItemData(i);
        if (pExamineeInfoCfg != NULL)
        {
            delete pExamineeInfoCfg;
            pExamineeInfoCfg = NULL;
            m_listSetExamineeInfo.SetItemData(i, 0);
        }
    }
    return;
}

/** @fn BOOL SendFirst()
*  @brief 发送第一项考生信息
*  @return  HPR_TRUE--success, HPR_FALSE--fail.
*/
BOOL CDlgAcsSetExamineeInfo::SendFirst()
{
    int nItemCount = m_listSetExamineeInfo.GetItemCount();

    if (nItemCount <= 0)
    {
        AfxMessageBox("Please add info to list at first");
        return FALSE;
    }

    m_dwSendIndex = 0;

    //获取第一个考生数据
    LPNET_DVR_EXAMINEE_INFO_CFG pExamineeInfoCfg = (LPNET_DVR_EXAMINEE_INFO_CFG)m_listSetExamineeInfo.GetItemData(m_dwSendIndex);

    if (pExamineeInfoCfg == NULL)
    {
        return FALSE;
    }

    pExamineeInfoCfg->byExamineeInfoValid = m_bExamineeInfoValid;

    if (!NET_DVR_SendRemoteConfig(m_lSetExamineeInfoHandle, ENUM_ACS_SEND_DATA, (char *)pExamineeInfoCfg, sizeof(*pExamineeInfoCfg)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Send Fail,Examinee No: %s", pExamineeInfoCfg->byExamineeNo);
        return FALSE;
    }

    return TRUE;
}

/** @fn BOOL SendNext()
*  @brief 发送下一项考生信息
*  @return  HPR_TRUE--success, HPR_FALSE--fail.
*/
BOOL CDlgAcsSetExamineeInfo::SendNext()
{
    int nItemCount = m_listSetExamineeInfo.GetItemCount();

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

    LPNET_DVR_EXAMINEE_INFO_CFG pExamineeInfoCfg = (LPNET_DVR_EXAMINEE_INFO_CFG)m_listSetExamineeInfo.GetItemData(m_dwSendIndex);

    pExamineeInfoCfg->byExamineeInfoValid = m_bExamineeInfoValid;

    if (pExamineeInfoCfg == NULL)
    {
        return FALSE;
    }

    if (!NET_DVR_SendRemoteConfig(m_lSetExamineeInfoHandle, ENUM_ACS_SEND_DATA, (char *)pExamineeInfoCfg, sizeof(*pExamineeInfoCfg)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Send Fail,Examinee No: %s", pExamineeInfoCfg->byExamineeNo);
        PostMessage(WM_MSG_SET_EXAMINEE_INFO_FINISH, 0, 0);
        return FALSE;
    }

    return TRUE;
}