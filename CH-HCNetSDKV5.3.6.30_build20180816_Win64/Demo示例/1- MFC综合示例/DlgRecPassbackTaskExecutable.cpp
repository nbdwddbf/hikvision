// DlgRecPassbackTaskExecutable.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgRecPassbackTaskExecutable.h"
#include "afxdialogex.h"


// CDlgRecPassbackTaskExecutable 对话框

IMPLEMENT_DYNAMIC(CDlgRecPassbackTaskExecutable, CDialogEx)

CDlgRecPassbackTaskExecutable::CDlgRecPassbackTaskExecutable(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRecPassbackTaskExecutable::IDD, pParent)
    , m_csStreamID(_T(""))
{
    m_nChannel = 0;
    m_lSearchTaskExecutableHandle = -1;
    m_nItemCount = 0;

    memset(&m_struRecPassBackExecutableSend, 0, sizeof(m_struRecPassBackExecutableSend));
    memset(&m_struRecPassBackExecutableRet, 0, sizeof(m_struRecPassBackExecutableRet));
}

CDlgRecPassbackTaskExecutable::~CDlgRecPassbackTaskExecutable()
{
    char szLan[128] = { 0 };
    if (m_lSearchTaskExecutableHandle < 0)
    {
        return;
    }
    else
    {
        if (!NET_DVR_StopRemoteConfig(m_lSearchTaskExecutableHandle))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopRemoteConfig failed");
            return;
        }
        else
        {
            m_lSearchTaskExecutableHandle = -1;
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopRemoteConfig succ");
        }
    }
}

void CDlgRecPassbackTaskExecutable::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_STREAM_ID, m_csStreamID);
    DDX_Text(pDX, IDC_EDIT_CHANNEL, m_nChannel);
    DDX_Control(pDX, IDC_LIST_REC_PASSBACK_TASK_EXECUTABLE, m_listCtrlTaskExecutable);
}


BEGIN_MESSAGE_MAP(CDlgRecPassbackTaskExecutable, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_ADD, &CDlgRecPassbackTaskExecutable::OnBnClickedBtnAdd)
    ON_BN_CLICKED(IDC_BTN_REMOVE, &CDlgRecPassbackTaskExecutable::OnBnClickedBtnRemove)
    ON_BN_CLICKED(IDC_BTN_SET, &CDlgRecPassbackTaskExecutable::OnBnClickedBtnSet)
    ON_BN_CLICKED(IDC_BTN_STOP, &CDlgRecPassbackTaskExecutable::OnBnClickedBtnStop)
END_MESSAGE_MAP()


// CDlgRecPassbackTaskExecutable 消息处理程序


void CDlgRecPassbackTaskExecutable::OnBnClickedBtnAdd()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    char szLan[128] = { 0 };
    CString strTemp;

    // 	if ("" == m_strStreamID)
    // 	{
    // 		g_StringLanType(szLan,"流ID为空","Stream ID is NULL");
    // 		AfxMessageBox(szLan);
    // 		return;
    // 	}

    int iItemCount = m_listCtrlTaskExecutable.GetItemCount();

//     if (iItemCount > 64)
//     {
//         g_StringLanType(szLan, "超过64个", "More than 64");
//         AfxMessageBox(szLan);
//         return;
//     }

    strTemp.Format("%02d", iItemCount + 1);

    m_listCtrlTaskExecutable.InsertItem(iItemCount, strTemp);
    m_listCtrlTaskExecutable.SetItemText(iItemCount, 1, m_csStreamID);

    strTemp.Format("%d", m_nChannel);
    m_listCtrlTaskExecutable.SetItemText(iItemCount, 2, strTemp);
}


BOOL CDlgRecPassbackTaskExecutable::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    char szLan[128] = { 0 };
    m_listCtrlTaskExecutable.SetExtendedStyle(m_listCtrlTaskExecutable.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

    g_StringLanType(szLan, "序号", "Serial No.");
    m_listCtrlTaskExecutable.InsertColumn(0, szLan, LVCFMT_LEFT, 50, -1);

    g_StringLanType(szLan, "流ID", "Stream ID");
    m_listCtrlTaskExecutable.InsertColumn(1, szLan, LVCFMT_LEFT, 100, -1);

    g_StringLanType(szLan, "关联通道", "Related channel");
    m_listCtrlTaskExecutable.InsertColumn(2, szLan, LVCFMT_LEFT, 60, -1);

    g_StringLanType(szLan, "可执行状态", "Executable Status");
    m_listCtrlTaskExecutable.InsertColumn(3, szLan, LVCFMT_LEFT, 60, -1);

    g_StringLanType(szLan, "原因", "Reason");
    m_listCtrlTaskExecutable.InsertColumn(4, szLan, LVCFMT_LEFT, 60, -1);

    g_StringLanType(szLan, "状态", "Status");
    m_listCtrlTaskExecutable.InsertColumn(5, szLan, LVCFMT_LEFT, 60, -1);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}


void CDlgRecPassbackTaskExecutable::OnBnClickedBtnRemove()
{
    // TODO:  在此添加控件通知处理程序代码
//     int nItem = 0;
// 
//     POSITION pos = m_listCtrlTaskExecutable.GetFirstSelectedItemPosition();
//     if (pos == NULL)
//         TRACE0("No items were selected!\n");
//     else
//     {
//         nItem = m_listCtrlTaskExecutable.GetNextSelectedItem(pos);
// 
//         //显示信息
//         m_nDelTaskID = atoi(m_listCtrlTaskExecutable.GetItemText(nItem, 0));
//         m_csDelStreamID = m_listCtrlTaskExecutable.GetItemText(nItem, 1);
//         m_nDelChannel = atoi(m_listCtrlTaskExecutable.GetItemText(nItem, 2));
//         m_csDelStatus = m_listCtrlTaskExecutable.GetItemText(nItem, 3);
// 
//         UpdateData(FALSE);
//     }
// 
//     *pResult = 0;

    while (m_listCtrlTaskExecutable.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED) != -1)
    {
        int nItem = m_listCtrlTaskExecutable.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
        m_listCtrlTaskExecutable.DeleteItem(nItem);
    }
}


void CALLBACK g_fTaskExecutableDataCallBack(DWORD dwType, void *pRecvDataBuffer, DWORD dwBufSize, void* pUserData)
{
    char szLan[128] = { 0 };
    CString strTemp;

    CDlgRecPassbackTaskExecutable* pDlg = (CDlgRecPassbackTaskExecutable*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }

    int iItemCount = pDlg->m_listCtrlTaskExecutable.GetItemCount();

    if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
        DWORD dwStatus = *(DWORD *)pRecvDataBuffer;

        if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            pDlg->m_listCtrlTaskExecutable.SetItemText(pDlg->m_nItemCount - 1, 5, "设备发送信息成功");

            if (pDlg->m_nItemCount >= iItemCount)
            {
                return;
            }
            else
            {
                memcpy(pDlg->m_struRecPassBackExecutableSend.struStreamInfo.byID, pDlg->m_listCtrlTaskExecutable.GetItemText(pDlg->m_nItemCount, 1), STREAM_ID_LEN);
                if (!NET_DVR_SendRemoteConfig(pDlg->m_lSearchTaskExecutableHandle, ENUM_CVR_PASSBACK_SEND_DATA, (char *)(&pDlg->m_struRecPassBackExecutableSend), sizeof(NET_DVR_REC_PASSBACK_MANUAL_EXECUTABLE_SEND)))
                {
                    g_pMainDlg->AddLog(pDlg->m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SendRemoteConfig");

                    if (!NET_DVR_StopRemoteConfig(pDlg->m_lSearchTaskExecutableHandle))
                    {
                        g_pMainDlg->AddLog(pDlg->m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopRemoteConfig");
                        return;
                    }
                    pDlg->m_lSearchTaskExecutableHandle = -1;
                }
                else
                {
                    pDlg->m_nItemCount++;
                }
            }
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_PROCESSING)
        {
            pDlg->m_listCtrlTaskExecutable.SetItemText(pDlg->m_nItemCount - 1, 5, "设备发送信息处理中");
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
        {
            pDlg->m_listCtrlTaskExecutable.SetItemText(pDlg->m_nItemCount - 1, 5, "接收设备信息失败");
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_EXCEPTION)
        {
            pDlg->m_listCtrlTaskExecutable.SetItemText(pDlg->m_nItemCount - 1, 5, "设备返回异常");
        }
    }
    else if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        LPNET_DVR_REC_PASSBACK_MANUAL_EXECUTABLE_RET pStru = (LPNET_DVR_REC_PASSBACK_MANUAL_EXECUTABLE_RET)pRecvDataBuffer;
        
        switch (pStru->byExecutable)
        {
        case 0:
            g_StringLanType(szLan, "不可立即回传", "can not pass back");
        	break;
        case 1:
            g_StringLanType(szLan, "可立即回传", "can pass back");
            //strTemp.Format("%s", "可立即回传");
            break;
        default:
            g_StringLanType(szLan, "未知", "Unknown");
            //strTemp.Format("%s", "Unknown");
            break;
        }
        strTemp.Format("%s", szLan);
        pDlg->m_listCtrlTaskExecutable.SetItemText(pDlg->m_nItemCount - 1, 3, strTemp);
        
        //0 - 需要排队，1 - 编码器无连接，2 - 流ID不存在，3 - CVR异常，4-无输入视频, 5-编码器用户名或密码错, 6-前端设备不兼容, 7-其他原因
        switch (pStru->byUnexecutableReason)
        {
        case 0:
            g_StringLanType(szLan, "需要排队", "need wait");
            break;
        case 1:
            g_StringLanType(szLan, "编码器无连接", "disconnect");
            break;
        case 2:
            g_StringLanType(szLan, "流ID不存在", "stream id is not exist");
            break;
        case 3:
            g_StringLanType(szLan, "CVR异常", "cvr error");
            break;
        case 4:
            g_StringLanType(szLan, "无输入视频", "no Video");
            break;
        case 5:
            g_StringLanType(szLan, "编码器用户名或密码错", "encoder username or password error");
            break;
        case 6:
            g_StringLanType(szLan, "前端设备不兼容", "The front-end device is not compatible");
            break;
        case 7:
            g_StringLanType(szLan, "其他原因", "other reason");
            break;
        default:
            g_StringLanType(szLan, "未知", "Unknown");
            break;
        }
        strTemp.Format("%s", szLan);
        pDlg->m_listCtrlTaskExecutable.SetItemText(pDlg->m_nItemCount - 1, 4, strTemp);
    }

    return;
}


void CDlgRecPassbackTaskExecutable::OnBnClickedBtnSet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    char szLan[128] = { 0 };
    m_nItemCount = 0;

    int iItemCount = m_listCtrlTaskExecutable.GetItemCount();

    NET_DVR_REC_PASSBACK_MANUAL_EXECUTABLE_SEND struRecordPassBackCond = { 0 };

    m_struRecPassBackExecutableSend.dwSize = sizeof(m_struRecPassBackExecutableSend);
    m_struRecPassBackExecutableSend.struStreamInfo.dwSize = sizeof(NET_DVR_STREAM_INFO);
    strncpy((char*)m_struRecPassBackExecutableSend.struStreamInfo.byID, m_csStreamID.GetBuffer(0), STREAM_ID_LEN);
    m_struRecPassBackExecutableSend.struStreamInfo.dwChannel = m_nChannel;

    if (m_lSearchTaskExecutableHandle >= 0)
    {
        g_StringLanType(szLan, "查询中，先停止", "Searching, stop it first");
        AfxMessageBox(szLan);
        return;
    }

    m_lSearchTaskExecutableHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_GET_REC_PASSBACK_TASK_EXECUTABLE, NULL, 0, g_fTaskExecutableDataCallBack, this);
    if (m_lSearchTaskExecutableHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StartRemoteConfig Failed!");
        AfxMessageBox("Start NET_DVR_StartRemoteConfig Failed");
        return;
    }

    g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StartRemoteConfig Success!");
    //MessageBox("success to start!");

    memcpy(m_struRecPassBackExecutableSend.struStreamInfo.byID, m_listCtrlTaskExecutable.GetItemText(m_nItemCount, 1), STREAM_ID_LEN);

    if (!NET_DVR_SendRemoteConfig(m_lSearchTaskExecutableHandle, ENUM_CVR_PASSBACK_SEND_DATA, (char *)(&m_struRecPassBackExecutableSend), sizeof(NET_DVR_REC_PASSBACK_MANUAL_EXECUTABLE_SEND)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SendRemoteConfig");
    }

    m_nItemCount++;
}


void CDlgRecPassbackTaskExecutable::OnBnClickedBtnStop()
{
    // TODO:  在此添加控件通知处理程序代码
    char szLan[128] = { 0 };
    if (m_lSearchTaskExecutableHandle < 0)
    {
        g_StringLanType(szLan, "当前已经处于停止状态", "It has not started!");
        AfxMessageBox(szLan);
        return;
    }
    else
    {
        if (!NET_DVR_StopRemoteConfig(m_lSearchTaskExecutableHandle))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopRemoteConfig failed");
            return;
        }
        else
        {
            m_lSearchTaskExecutableHandle = -1;
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopRemoteConfig succ");
        }
    }
}
