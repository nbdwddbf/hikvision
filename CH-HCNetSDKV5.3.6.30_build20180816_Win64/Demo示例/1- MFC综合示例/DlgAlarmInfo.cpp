// DlgAlarmInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgAlarmInfo.h"
#include "afxdialogex.h"

void CALLBACK g_fGetAlarmInfo(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData);
// CDlgAlarmInfo 对话框

IMPLEMENT_DYNAMIC(CDlgAlarmInfo, CDialog)
#define WM_MSG_FINISH 1003

CDlgAlarmInfo::CDlgAlarmInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmInfo::IDD, pParent)
    , m_strUID(_T(""))
    , m_bUID(FALSE)
    , m_bTime(FALSE)
    , m_bUTC(FALSE)
{
    memset(&m_struAlarmSearchCond, 0, sizeof(m_struAlarmSearchCond));
    memset(&m_struAlarmSearchResult, 0, sizeof(m_struAlarmSearchResult));
    m_startDate = COleDateTime::GetCurrentTime();
    m_startTime = COleDateTime::GetCurrentTime();
    m_stopDate = COleDateTime::GetCurrentTime();
    m_stopTime = COleDateTime::GetCurrentTime();
    m_lHandle = -1;

}

CDlgAlarmInfo::~CDlgAlarmInfo()
{
}

void CDlgAlarmInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_COMMAND, m_cmbCommand);
    DDX_DateTimeCtrl(pDX, IDC_START_DATE, m_startDate);
    DDX_DateTimeCtrl(pDX, IDC_START_TIME, m_startTime);
    DDX_DateTimeCtrl(pDX, IDC_STOP_DATE, m_stopDate);
    DDX_DateTimeCtrl(pDX, IDC_STOP_TIME, m_stopTime);
    DDX_Text(pDX, IDC_EDIT_UID, m_strUID);
    DDX_Check(pDX, IDC_CHECK_UID, m_bUID);
    DDX_Check(pDX, IDC_CHECK_TIME, m_bTime);
    DDX_Check(pDX, IDC_CHECK_UTC, m_bUTC);
}


BEGIN_MESSAGE_MAP(CDlgAlarmInfo, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_ALARM_INFO_GET, &CDlgAlarmInfo::OnBnClickedButtonAlarmInfoGet)
    ON_BN_CLICKED(IDC_BUTTON_ALARM_INFO_GET, &CDlgAlarmInfo::OnBnClickedButtonAlarmInfoGet)
    ON_MESSAGE(WM_MSG_FINISH, Finish)
END_MESSAGE_MAP()


// CDlgAlarmInfo 消息处理程序


void CDlgAlarmInfo::OnBnClickedButtonAlarmInfoGet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    char szLan[128] = { 0 };
    memset(&m_struAlarmSearchCond, 0, sizeof(m_struAlarmSearchCond));
    memset(&m_struAlarmSearchResult, 0, sizeof(m_struAlarmSearchResult));
    m_struAlarmSearchCond.dwSize = sizeof(m_struAlarmSearchCond);
    m_struAlarmSearchCond.dwAlarmComm = m_cmbCommand.GetItemData(m_cmbCommand.GetCurSel());
    if (m_struAlarmSearchCond.dwAlarmComm == 0)
    {
        //memcpy(m_struSearchInfoCond.byName, (LPCSTR)m_csName, m_csName.GetAllocLength());
    }
    if (m_bTime)
    {
        m_struAlarmSearchCond.strStartTime.wYear = m_startDate.GetYear();
        m_struAlarmSearchCond.strStartTime.byMonth = m_startDate.GetMonth();
        m_struAlarmSearchCond.strStartTime.byDay = m_startDate.GetDay();
        m_struAlarmSearchCond.strStartTime.byHour = m_startTime.GetHour();
        m_struAlarmSearchCond.strStartTime.byMinute = m_startTime.GetMinute();
        m_struAlarmSearchCond.strStartTime.bySecond = m_startTime.GetSecond();
        m_struAlarmSearchCond.strStopTime.wYear = m_stopDate.GetYear();
        m_struAlarmSearchCond.strStopTime.byMonth = m_stopDate.GetMonth();
        m_struAlarmSearchCond.strStopTime.byDay = m_stopDate.GetDay();
        m_struAlarmSearchCond.strStopTime.byHour = m_stopTime.GetHour();
        m_struAlarmSearchCond.strStopTime.byMinute = m_stopTime.GetMinute();
        m_struAlarmSearchCond.strStopTime.bySecond = m_stopTime.GetSecond();
        if (m_bUTC)
        {
            m_struAlarmSearchCond.strStartTime.byLocalOrUTC = 1;
            m_struAlarmSearchCond.strStopTime.byLocalOrUTC = 1;
        }
    }


    if (m_lHandle >= 0)
    {
        if (!NET_DVR_StopRemoteConfig(m_lHandle))
        {
            g_StringLanType(szLan, "报警信息查询停止失败", "get abnormal info stop failed");
            AfxMessageBox(szLan);
            return;
        }
    }
    if (m_bUID)
    {
        strncpy(m_struAlarmSearchCond.sAlarmUID, m_strUID.GetBuffer(m_strUID.GetLength()), 64);
    }

    m_lHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_GET_ALARM_INFO, &m_struAlarmSearchCond, sizeof(m_struAlarmSearchCond), g_fGetAlarmInfo, this);
    if (m_lHandle >= 0)
    {
        m_bGetNext = TRUE;
        DWORD dwThreadId;
        //m_lstAbnormalInfo.DeleteAllItems();
        //m_hGetInfoThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetAbnormalInfoThread), this, 0, &dwThreadId);
        g_StringLanType(szLan, "报警信息查询成功", "get alarm info succeed");
        AfxMessageBox(szLan);
        //g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, szLan);
    }
    else
    {
        DWORD dwRelt = NET_DVR_GetLastError();
        m_bGetNext = FALSE;
        g_StringLanType(szLan, "报警信息查询失败", "get abnormal info failed");
        AfxMessageBox(szLan);
        // g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARM_INFO");
        return;
    }

    UpdateData(FALSE);

}

void CDlgAlarmInfo::AddResolution()
{

    int index = 0;
    m_cmbCommand.InsertString(index, "智能检测报警");
    m_cmbCommand.SetItemData(index, 0x4993);
    index++;

    //m_cmbCommand.InsertString(index, "人脸识别结果上传");
    //m_cmbCommand.SetItemData(index, 125);
    //index++;

    //m_cmbCommand.InsertString(index, "人脸比对结果上传");
    //m_cmbCommand.SetItemData(index, 127);
    //index++;

    //m_cmbCommand.InsertString(index, "所有");
    //m_cmbCommand.SetItemData(index, 0xffff);
    //index++;
}
void CALLBACK g_fGetAlarmInfo(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CDlgAlarmInfo* pDlg = (CDlgAlarmInfo*)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
    pDlg->ProcGetAlarmInfo(dwType, lpBuffer, dwBufLen);

}

typedef struct tagLOCAL_ALARM_INFO
{
    int iDeviceIndex;
    LONG lCommand;
    char sDeviceIP[128];    			/* IP地址 */
    DWORD dwBufLen;
    tagLOCAL_ALARM_INFO()
    {
        iDeviceIndex = -1;
        lCommand = -1;
        memset(&sDeviceIP, 0, 128);
        dwBufLen = 0;
    }
}LOCAL_ALARM_INFO, *LPLOCAL_ALARM_INFO;

void CDlgAlarmInfo::ProcGetAlarmInfo(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{
    CString strItem = "";
    HWND hWnd = this->GetSafeHwnd();
    if (NULL == hWnd)
    {
        return;
    }

    if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        int len = sizeof(NET_DVR_ALARM_SEARCH_RESULT);
        int len1 = sizeof(NET_DVR_ALARMER);
        NET_DVR_ALARM_SEARCH_RESULT struAlarmSearchResult = *(LPNET_DVR_ALARM_SEARCH_RESULT)lpBuffer;
        AlarmMessage(struAlarmSearchResult.dwAlarmComm, &struAlarmSearchResult.struAlarmer, struAlarmSearchResult.pAlarmInfo, struAlarmSearchResult.dwAlarmLen);
    }

    else if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
        DWORD dwStatus = *(DWORD*)lpBuffer;
        if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            PostMessage(WM_MSG_FINISH, 0, 0);

        }
    }
}

LRESULT CDlgAlarmInfo::Finish(WPARAM wParam, LPARAM lParam)
{
    if (m_lHandle == -1)
    {
        return 0;
    }
    NET_DVR_StopRemoteConfig(m_lHandle);
    m_lHandle = -1;
    return 0;
}
BOOL CDlgAlarmInfo::OnInitDialog()
{
    CDialog::OnInitDialog();
    AddResolution();
    m_cmbCommand.SetCurSel(0);

    return TRUE;
}

