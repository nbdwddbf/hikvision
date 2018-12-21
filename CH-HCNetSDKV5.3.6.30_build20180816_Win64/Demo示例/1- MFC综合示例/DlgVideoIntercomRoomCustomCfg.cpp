// DlgVideoIntercomRoomCustomCfg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgVideoIntercomRoomCustomCfg.h"
#include "afxdialogex.h"

#define WM_MSG_SET_ROOM_CUSTOM_CFG_FINISH 1002
#define WM_MSG_GET_ROOM_CUSTOM_CFG_FINISH 1003
#define WM_MSG_ADD_ROOM_CUSTOM_CFG_TOLIST 1004

void CALLBACK g_fSetRoomCustomCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData);
void CALLBACK g_fGetRoomCustomCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData);

// CDlgVideoIntercomRoomCustomCfg 对话框

IMPLEMENT_DYNAMIC(CDlgVideoIntercomRoomCustomCfg, CDialog)

CDlgVideoIntercomRoomCustomCfg::CDlgVideoIntercomRoomCustomCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVideoIntercomRoomCustomCfg::IDD, pParent)
{
    m_dwFormerRoomNo = 0;
    m_dwCustomRoomNo = 0;
    m_lpRoomCustomCfg = NULL;
    m_lSetRoomCustomCfgHandle = -1;
    m_lGetRoomCustomCfgHandle = -1;
    m_dwSendIndex = 0;
    m_lpNowSendRoomCustom = NULL;
}

CDlgVideoIntercomRoomCustomCfg::~CDlgVideoIntercomRoomCustomCfg()
{
    /*m_listRoomCustomCfg.DeleteAllItems();*/
    LPDWORD lpArr = GetRoomCustomCfgPoint();
    for (int i = 0; i < 6000; i++)
    {
        if (lpArr[i] == NULL)
        {
            return;
        }
        delete[](LPNET_DVR_ROOM_CUSTOM_CFG)lpArr[i];
        lpArr[i] = NULL;
    }
}

void CDlgVideoIntercomRoomCustomCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_FORMER_ROOM_NO, m_dwFormerRoomNo);
    DDX_Text(pDX, IDC_EDIT_CUSTOM_ROOM_NO, m_dwCustomRoomNo);
    DDX_Control(pDX, IDC_LIST_ROOM_CUSTOM_CFG, m_listRoomCustomCfg);
}


BEGIN_MESSAGE_MAP(CDlgVideoIntercomRoomCustomCfg, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_ADD, &CDlgVideoIntercomRoomCustomCfg::OnBnClickedButtonAdd)
    ON_BN_CLICKED(IDC_BUTTON_SET, &CDlgVideoIntercomRoomCustomCfg::OnBnClickedButtonSet)
    ON_BN_CLICKED(IDC_BUTTON_GET, &CDlgVideoIntercomRoomCustomCfg::OnBnClickedButtonGet)
    ON_BN_CLICKED(IDC_BUTTON_DEL, &CDlgVideoIntercomRoomCustomCfg::OnBnClickedButtonDel)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ROOM_CUSTOM_CFG, &CDlgVideoIntercomRoomCustomCfg::OnLvnItemchangedListRoomCustomCfg)
    ON_MESSAGE(WM_MSG_SET_ROOM_CUSTOM_CFG_FINISH, OnMsgSetRoomCustomCfgFinish)
    ON_MESSAGE(WM_MSG_GET_ROOM_CUSTOM_CFG_FINISH, OnMsgGetRoomCustomCfgFinish)
    ON_MESSAGE(WM_MSG_ADD_ROOM_CUSTOM_CFG_TOLIST, OnMsgAddRoomCustomCfgTolist)
END_MESSAGE_MAP()

LRESULT CDlgVideoIntercomRoomCustomCfg::OnMsgSetRoomCustomCfgFinish(WPARAM wParam, LPARAM lParam)
{
    if (!NET_DVR_StopRemoteConfig(m_lSetRoomCustomCfgHandle))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopRemoteConfig failed");
        return 0;
    }
    m_lSetRoomCustomCfgHandle = -1;
    g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_ROOM_CUSTOM_CFG Set finish");
    return 0;
}

LRESULT CDlgVideoIntercomRoomCustomCfg::OnMsgGetRoomCustomCfgFinish(WPARAM wParam, LPARAM lParam)
{
    NET_DVR_StopRemoteConfig(m_lGetRoomCustomCfgHandle);
    m_lGetRoomCustomCfgHandle = -1;
    g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ROOM_CUSTOM_CFG Get finish");
    return 0;
}

LRESULT CDlgVideoIntercomRoomCustomCfg::OnMsgAddRoomCustomCfgTolist(WPARAM wParam, LPARAM lParam)
{
    LPNET_DVR_ROOM_CUSTOM_CFG lpRoomCustomCfg = (LPNET_DVR_ROOM_CUSTOM_CFG)wParam;
    if (lpRoomCustomCfg->dwSize == 0)
    {
        return 0;
    }

    AddToRoomCustomList(*lpRoomCustomCfg);
    delete lpRoomCustomCfg;
    UpdateData(FALSE);
    return 0;
}


// CDlgVideoIntercomRoomCustomCfg 消息处理程序


void CDlgVideoIntercomRoomCustomCfg::OnBnClickedButtonAdd()
{
    // TODO:  在此添加控件通知处理程序代码
    NET_DVR_ROOM_CUSTOM_CFG struRoomCustomCfg = { 0 };
    UpdateRoomCustomCfg(struRoomCustomCfg);
    AddToRoomCustomList(struRoomCustomCfg);
}


void CDlgVideoIntercomRoomCustomCfg::OnBnClickedButtonSet()
{
    // TODO:  在此添加控件通知处理程序代码
    if (m_lSetRoomCustomCfgHandle != -1)
    {
        NET_DVR_StopRemoteConfig(m_lSetRoomCustomCfgHandle);
    }

    UpdateData(TRUE);

    NET_DVR_ROOM_CUSTOM_COND struRoomCustomCond = { 0 };
    struRoomCustomCond.dwSize = sizeof(struRoomCustomCond);
    struRoomCustomCond.dwRoomNumber = m_listRoomCustomCfg.GetItemCount();

    m_lSetRoomCustomCfgHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_SET_ROOM_CUSTOM_CFG, &struRoomCustomCond, sizeof(struRoomCustomCond), g_fSetRoomCustomCallback, this);
    if (m_lSetRoomCustomCfgHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_ROOM_CUSTOM_CFG failed");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_ROOM_CUSTOM_CFG success");
    }

    //发送第一个房间自定义信息, 失败关闭连接
    m_dwSendIndex = 0;
    if (!SendFirstRoomCustom())
    {
        NET_DVR_StopRemoteConfig(m_lSetRoomCustomCfgHandle);
        m_lSetRoomCustomCfgHandle = -1;
    }
}


void CDlgVideoIntercomRoomCustomCfg::OnBnClickedButtonGet()
{
    // TODO:  在此添加控件通知处理程序代码
    if (m_lGetRoomCustomCfgHandle != -1)
    {
        NET_DVR_StopRemoteConfig(m_lGetRoomCustomCfgHandle);
    }

    m_listRoomCustomCfg.DeleteAllItems();
    LPDWORD lpArr = GetRoomCustomCfgPoint();
    for (int i = 0; i < 6000; i++)
    {
        if (lpArr[i] == NULL)
        {
            break;
        }
        delete[](LPNET_DVR_ROOM_CUSTOM_CFG)lpArr[i];
        lpArr[i] = NULL;
    }

    NET_DVR_ROOM_CUSTOM_COND struRoomCustomCond = { 0 };
    struRoomCustomCond.dwSize = sizeof(struRoomCustomCond);
    
    m_lGetRoomCustomCfgHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_GET_ROOM_CUSTOM_CFG, &struRoomCustomCond, sizeof(struRoomCustomCond), g_fGetRoomCustomCallback, this);
    if (m_lGetRoomCustomCfgHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ROOM_CUSTOM_CFG failed");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ROOM_CUSTOM_CFG success");
    }
}


void CDlgVideoIntercomRoomCustomCfg::OnBnClickedButtonDel()
{
    // TODO:  在此添加控件通知处理程序代码
    m_listRoomCustomCfg.DeleteAllItems();
    LPDWORD lpArr = GetRoomCustomCfgPoint();
    for (int i = 0; i < 6000; i++)
    {
        if (lpArr[i] == NULL)
        {
            return;
        }
        delete[](LPNET_DVR_ROOM_CUSTOM_CFG)lpArr[i];
        lpArr[i] = NULL;
    }
}


void CDlgVideoIntercomRoomCustomCfg::OnLvnItemchangedListRoomCustomCfg(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    // TODO:  在此添加控件通知处理程序代码
    *pResult = 0;
}

BOOL CDlgVideoIntercomRoomCustomCfg::OnInitDialog()
{
    CDialog::OnInitDialog();

    char szLan[128] = { 0 };

    m_listRoomCustomCfg.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    g_StringLanType(szLan, "编号", "No");
    m_listRoomCustomCfg.InsertColumn(0, szLan, LVCFMT_LEFT, 75, -1);
    g_StringLanType(szLan, "原房间号", "Former Room No");
    m_listRoomCustomCfg.InsertColumn(1, szLan, LVCFMT_LEFT, 140, -1);
    g_StringLanType(szLan, "自定义序号", "Custom Room No");
    m_listRoomCustomCfg.InsertColumn(2, szLan, LVCFMT_LEFT, 140, -1);

    return TRUE;
}

BOOL CDlgVideoIntercomRoomCustomCfg::UpdateRoomCustomCfg(NET_DVR_ROOM_CUSTOM_CFG &struRoomCustomCfg)
{
    UpdateData(TRUE);
    struRoomCustomCfg.dwSize = sizeof(NET_DVR_ROOM_CUSTOM_CFG);
    struRoomCustomCfg.dwFormerRoomNo = m_dwFormerRoomNo;
    struRoomCustomCfg.dwCustomRoomNo = m_dwCustomRoomNo;

    return TRUE;
}

void CDlgVideoIntercomRoomCustomCfg::AddToRoomCustomList(const NET_DVR_ROOM_CUSTOM_CFG &struRoomCustomCfg)
{
    LPNET_DVR_ROOM_CUSTOM_CFG pRoomCustomInfo = NULL;
    int iItemIndex = GetExistItem(&struRoomCustomCfg);
    if (iItemIndex == -1)
    {
        pRoomCustomInfo = new NET_DVR_ROOM_CUSTOM_CFG;
        if (pRoomCustomInfo == NULL)
        {
            return;
        }
        int iSize = sizeof(NET_DVR_ROOM_CUSTOM_CFG);
        int nItemCount = m_listRoomCustomCfg.GetItemCount();

        CString strItem = "";
        strItem.Format("%d", nItemCount + 1);
        iItemIndex = m_listRoomCustomCfg.InsertItem(nItemCount, strItem);
        m_listRoomCustomCfg.SetItemData(nItemCount, (DWORD)pRoomCustomInfo);
    }
    else
    {
        pRoomCustomInfo = (LPNET_DVR_ROOM_CUSTOM_CFG)m_listRoomCustomCfg.GetItemData(iItemIndex);
    }
    memcpy(pRoomCustomInfo, &struRoomCustomCfg, sizeof(struRoomCustomCfg));
    UpdateList(iItemIndex, *pRoomCustomInfo);
    LPDWORD lpArr = GetRoomCustomCfgPoint();
    lpArr[iItemIndex] = (DWORD)pRoomCustomInfo;
}

int CDlgVideoIntercomRoomCustomCfg::GetExistItem(const NET_DVR_ROOM_CUSTOM_CFG *lpRoomCustomCfg)
{
    int nItemCount = m_listRoomCustomCfg.GetItemCount();
    int i = 0;
    LPNET_DVR_ROOM_CUSTOM_CFG lpTemp = NULL;
    for (i = 0; i < nItemCount; i++)
    {
        lpTemp = (LPNET_DVR_ROOM_CUSTOM_CFG)m_listRoomCustomCfg.GetItemData(i);
        if (!lpRoomCustomCfg)
        {
            continue;
        }
        if (lpTemp->dwFormerRoomNo == lpRoomCustomCfg->dwFormerRoomNo)
        {
            return i;
        }
    }
    return -1;
}

void CDlgVideoIntercomRoomCustomCfg::UpdateList(int iInsertIndex, const NET_DVR_ROOM_CUSTOM_CFG& struRoomCustomCfg)
{
    char szLan[1024] = { 0 };

    sprintf(szLan, "%d", iInsertIndex);
    sprintf(szLan, "%d", struRoomCustomCfg.dwFormerRoomNo);
    m_listRoomCustomCfg.SetItemText(iInsertIndex, 1, szLan);
    sprintf(szLan, "%d", struRoomCustomCfg.dwCustomRoomNo);
    m_listRoomCustomCfg.SetItemText(iInsertIndex, 2, szLan);
}

LPDWORD CDlgVideoIntercomRoomCustomCfg::GetRoomCustomCfgPoint()
{
    if (!m_lpRoomCustomCfg)
    {
        const int iMaxRoomCustomNum = 6000;
        m_lpRoomCustomCfg = new DWORD[iMaxRoomCustomNum];
        memset(m_lpRoomCustomCfg, 0, sizeof(DWORD)*iMaxRoomCustomNum);
    }
    return m_lpRoomCustomCfg;
}

BOOL CDlgVideoIntercomRoomCustomCfg::SendFirstRoomCustom()
{
    if (m_lSetRoomCustomCfgHandle == -1)
    {
        return FALSE;
    }

    m_dwSendIndex = 0;
    LPDWORD lpArr = GetRoomCustomCfgPoint();
    m_lpNowSendRoomCustom = (LPNET_DVR_ROOM_CUSTOM_CFG)lpArr[m_dwSendIndex];
    
    if (!NET_DVR_SendRemoteConfig(m_lSetRoomCustomCfgHandle, ENUM_VIDEO_INTERCOM_SEND_DATA, (char *)m_lpNowSendRoomCustom, sizeof(*m_lpNowSendRoomCustom)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Send Fail,Former Room No: %d", m_lpNowSendRoomCustom->dwFormerRoomNo);
        return FALSE;
    }
    return TRUE;
}

BOOL CDlgVideoIntercomRoomCustomCfg::SendNextRoomCustom()
{
    if (m_lSetRoomCustomCfgHandle == -1)
    {
        return FALSE;
    }

    LPDWORD lpArr = GetRoomCustomCfgPoint();

    m_dwSendIndex++;
    if (lpArr == NULL)
    {
        return FALSE;
    }
    if (m_dwSendIndex >= m_listRoomCustomCfg.GetItemCount())
    {
        PostMessage(WM_MSG_SET_ROOM_CUSTOM_CFG_FINISH, 0, 0);
        return FALSE;
    }
    m_lpNowSendRoomCustom = (LPNET_DVR_ROOM_CUSTOM_CFG)lpArr[m_dwSendIndex];

    if (!NET_DVR_SendRemoteConfig(m_lSetRoomCustomCfgHandle, ENUM_VIDEO_INTERCOM_SEND_DATA, (char *)m_lpNowSendRoomCustom, sizeof(*m_lpNowSendRoomCustom)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Send Fail,Former Room No: %d", m_lpNowSendRoomCustom->dwFormerRoomNo);
        //发送失败  关闭连接
        PostMessage(WM_MSG_SET_ROOM_CUSTOM_CFG_FINISH, 0, 0);
        return FALSE;
    }
    return TRUE;
}

void CALLBACK g_fSetRoomCustomCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CDlgVideoIntercomRoomCustomCfg* pDlg = (CDlgVideoIntercomRoomCustomCfg*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
    pDlg->ProcessSetRoomCustomCfgCallbackData(dwType, lpBuffer, dwBufLen);
}

void CDlgVideoIntercomRoomCustomCfg::ProcessSetRoomCustomCfgCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{
    if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
        DWORD dwStatus = *(DWORD*)lpBuffer;
        if (dwStatus == NET_SDK_CALLBACK_STATUS_PROCESSING)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Set Room Custom PROCESSING");

            SendNextRoomCustom();
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Set Room Custom Err:NET_SDK_CALLBACK_STATUS_FAILED");

            SendNextRoomCustom();
        }
        //下面两个关闭长连接
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Set Room Custom SUCCESS");
            PostMessage(WM_MSG_SET_ROOM_CUSTOM_CFG_FINISH, 0, 0);

        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_EXCEPTION)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Set Room Custom Exception");
            PostMessage(WM_MSG_SET_ROOM_CUSTOM_CFG_FINISH, 0, 0);
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Set Room Custom SUCCESS");
            PostMessage(WM_MSG_SET_ROOM_CUSTOM_CFG_FINISH, 0, 0);
        }

    }
    else if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        NET_DVR_ROOM_CUSTOM_STATUS struCfg = { 0 };
        memcpy(&struCfg, lpBuffer, sizeof(struCfg));

        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Set Room Custom PROCESSING, Former Room No:%d, Status:%d", struCfg.dwFormerRoomNo, struCfg.byStatus);
    
        SendNextRoomCustom();
    }
}

void CALLBACK g_fGetRoomCustomCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CDlgVideoIntercomRoomCustomCfg* pDlg = (CDlgVideoIntercomRoomCustomCfg*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
    pDlg->ProcessGetRoomCustomCfgCallbackData(dwType, lpBuffer, dwBufLen);
}

void CDlgVideoIntercomRoomCustomCfg::ProcessGetRoomCustomCfgCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{
    if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        LPNET_DVR_ROOM_CUSTOM_CFG lpRoomCustomCfg = new NET_DVR_ROOM_CUSTOM_CFG;
        memcpy(lpRoomCustomCfg, lpBuffer, sizeof(*lpRoomCustomCfg));

        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Get Room Custom PROCESSING");

        PostMessage(WM_MSG_ADD_ROOM_CUSTOM_CFG_TOLIST, (WPARAM)lpRoomCustomCfg, 0);
    }
    else if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
        DWORD dwStatus = *(DWORD*)lpBuffer;
        if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            PostMessage(WM_MSG_GET_ROOM_CUSTOM_CFG_FINISH, 0, 0);
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
        {
            DWORD dwErrCode = *(DWORD*)((char *)lpBuffer + 4);
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "GetCard STATUS_FAILED, Error code %d", dwErrCode);
        }
    }
}