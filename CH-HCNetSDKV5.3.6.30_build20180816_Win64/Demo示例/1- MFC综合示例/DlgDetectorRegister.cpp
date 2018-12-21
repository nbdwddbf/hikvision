// DlgDetectorRegister.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgDetectorRegister.h"
#include "afxdialogex.h"

// CDlgDetectorRegister 对话框

IMPLEMENT_DYNAMIC(CDlgDetectorRegister, CDialog)

DWORD WINAPI CDlgDetectorRegister::GetConfigThread(LPVOID lpArg)
{
    CDlgDetectorRegister* pThis = reinterpret_cast<CDlgDetectorRegister*>(lpArg);
    int bRet = 0;
    char szLan[128] = { 0 };
    while (pThis->m_bGetNext)
    {
        bRet = NET_DVR_GetNextRemoteConfig(pThis->m_lTranHandle, &pThis->m_struInfo, sizeof(pThis->m_struInfo));
        if (bRet == NET_SDK_GET_NEXT_STATUS_SUCCESS)
        {
            pThis->AddInfoToDlg();
        }
        else
        {
            if (bRet == NET_SDK_GET_NETX_STATUS_NEED_WAIT)
            {
                Sleep(5);
                continue;
            }
            if (bRet == NET_SDK_GET_NEXT_STATUS_FINISH)
            {
                g_StringLanType(szLan, "注册结束!", "Register Ending");
                g_pMainDlg->AddLog(pThis->m_iDevIndex, OPERATION_SUCC_T, szLan);
                //AfxMessageBox(szLan);
                break;
            }
            else if (bRet == NET_SDK_GET_NEXT_STATUS_FAILED)
            {
                g_StringLanType(szLan, "注册失败!", "Register failed");
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
    if (-1 != pThis->m_lTranHandle)
    {
        if (!NET_DVR_StopRemoteConfig(pThis->m_lTranHandle))
        {
            g_pMainDlg->AddLog(pThis->m_iDevIndex, OPERATION_FAIL_T, "Stop Remote Config Failed");
            pThis->m_bGetNext = FALSE;
        }
        else
        {
            g_pMainDlg->AddLog(pThis->m_iDevIndex, OPERATION_SUCC_T, "Stop Remote Config Successful");
            pThis->m_bGetNext = FALSE;
            pThis->m_lTranHandle = -1;
        }
    }
    return 0;
}

void CDlgDetectorRegister::AddInfoToDlg()
{
    //时间点
    if (m_struInfo.byDetectorSerialNo[0] == '\0')
    {
        return;
    }
    char sTemp[256];
    memcpy(sTemp, m_struInfo.byDetectorSerialNo,sizeof(sTemp));
    m_listData.InsertItem(m_iRowCount,sTemp);
    sprintf(sTemp, "%d", m_struInfo.dwAlarmIn);
    m_listData.SetItemText(m_iRowCount, 1, sTemp);
    if (m_struInfo.wDetectorType==0)
    {
        g_StringLanType(sTemp, "紧急开关", "Panic Button");
        m_listData.SetItemText(m_iRowCount, 2, sTemp);
    }
    else if (m_struInfo.wDetectorType == 1)
    {
        g_StringLanType(sTemp, "门磁开关", "Magnetic Contact");
        m_listData.SetItemText(m_iRowCount, 2, sTemp);
    }
    else if (m_struInfo.wDetectorType == 2)
    {
        g_StringLanType(sTemp, "烟感探测器", "Smoke Detector");
        m_listData.SetItemText(m_iRowCount, 2, sTemp);
    }
    else if (m_struInfo.wDetectorType == 3)
    {
        g_StringLanType(sTemp, "主动红外探测器", "Active Infrared Detector");
        m_listData.SetItemText(m_iRowCount, 2, sTemp);
    }
    else if (m_struInfo.wDetectorType == 4)
    {
        g_StringLanType(sTemp, "被动红外探测器", "Passive Infrared Detector");
        m_listData.SetItemText(m_iRowCount, 2, sTemp);
    }
    else if (m_struInfo.wDetectorType == 5)
    {
        g_StringLanType(sTemp, "玻璃破碎探测器", "Glass Break Detector");
        m_listData.SetItemText(m_iRowCount, 2, sTemp);
    }
    else if (m_struInfo.wDetectorType == 6)
    {
        g_StringLanType(sTemp, "震动探测器", "Vibration detector");
        m_listData.SetItemText(m_iRowCount, 2, sTemp);
    }
    else if (m_struInfo.wDetectorType == 7)
    {
        g_StringLanType(sTemp, "双鉴移动探测器", "Dual Technology PIR detector");
        m_listData.SetItemText(m_iRowCount, 2, sTemp);
    }
    else if (m_struInfo.wDetectorType == 8)
    {
        g_StringLanType(sTemp, "三技术探测器", "Triple Technology PIR detector");
        m_listData.SetItemText(m_iRowCount, 2, sTemp);
    }
    else if (m_struInfo.wDetectorType == 9)
    {
        g_StringLanType(sTemp, "湿度探测器", "Humidity Dectector");
        m_listData.SetItemText(m_iRowCount, 2, sTemp);
    }
    else if (m_struInfo.wDetectorType == 10)
    {
        g_StringLanType(sTemp, "温感探测器", "Temperature Dectector");
        m_listData.SetItemText(m_iRowCount, 2, sTemp);

    }
    else if (m_struInfo.wDetectorType == 11)
    {
        g_StringLanType(sTemp, "可燃气体探测器", "Combustible Gas Detector");
        m_listData.SetItemText(m_iRowCount, 2, sTemp);

    }
    else if (m_struInfo.wDetectorType == 12)
    {
        g_StringLanType(sTemp, "随动开关", "dynamic switch");
        m_listData.SetItemText(m_iRowCount, 2, sTemp);

    }
    else if (m_struInfo.wDetectorType == 13)
    {
        g_StringLanType(sTemp, "控制开关", "control switch");
        m_listData.SetItemText(m_iRowCount, 2, sTemp);
    }
    else if (m_struInfo.wDetectorType == 14)
    {
        g_StringLanType(sTemp, "智能锁", "smart lock");
        m_listData.SetItemText(m_iRowCount, 2, sTemp);
    }
    else if (m_struInfo.wDetectorType == 15)
    {
        g_StringLanType(sTemp, "水感探测器", "water detector");
        m_listData.SetItemText(m_iRowCount, 2, sTemp);
    }
    else if (m_struInfo.wDetectorType == 16)
    {
        g_StringLanType(sTemp, "位移探测器", "displacement detector");
        m_listData.SetItemText(m_iRowCount, 2, sTemp);
    }
    else if (m_struInfo.wDetectorType == 17)
    {
        g_StringLanType(sTemp, "单体门磁探测器", "single infrared detector");
        m_listData.SetItemText(m_iRowCount, 2, sTemp);
    }
    else if (m_struInfo.wDetectorType == 18)
    {
        g_StringLanType(sTemp, "无线单防区模块", "wireless single zone module");
        m_listData.SetItemText(m_iRowCount, 2, sTemp);
    }
    else if (m_struInfo.wDetectorType == 19)
    {
        g_StringLanType(sTemp, "其他探测器", "Other Detector");
        m_listData.SetItemText(m_iRowCount, 2, sTemp);
    }
    //UpdateData(FALSE);
}

CDlgDetectorRegister::CDlgDetectorRegister(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDetectorRegister::IDD, pParent)
{
    m_iDevIndex = 0;
    m_lServerID = -1;
    m_iRowCount = 0;
    m_lTranHandle = -1;
}

CDlgDetectorRegister::~CDlgDetectorRegister()
{
}

void CDlgDetectorRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_ALL_REGISTER_DETECTOR, m_listData);
}


BEGIN_MESSAGE_MAP(CDlgDetectorRegister, CDialog)
    ON_BN_CLICKED(IDC_BTN_DETECTOR_REGISTER, &CDlgDetectorRegister::OnBnClickedBtnDetectorRegister)
END_MESSAGE_MAP()


// CDlgDetectorRegister 消息处理程序
BOOL CDlgDetectorRegister::OnInitDialog()
{
    CDialog::OnInitDialog();
    char szLan[128] = { 0 };
    m_listData.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    g_StringLanType(szLan, "探测器序列号", "Serial");
    m_listData.InsertColumn(0, szLan, LVCFMT_LEFT, 150, -1);
    g_StringLanType(szLan, "防区号", "zone number");
    m_listData.InsertColumn(1, szLan, LVCFMT_LEFT, 300, -1);
    g_StringLanType(szLan, "类型", "type");
    m_listData.InsertColumn(2, szLan, LVCFMT_LEFT, 250, -1);
    UpdateData(FALSE);
    return TRUE;
}

void CDlgDetectorRegister::OnBnClickedBtnDetectorRegister()
{
    // TODO:  在此添加控件通知处理程序代码
    m_listData.DeleteAllItems();
    m_iRowCount = 0;
    if (m_lTranHandle >= 0)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "It is getting data, wait for a moment");
    }
    else
    {
        m_lTranHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_ALARMHOST_REGISTER_DETECTOR, NULL, 0, NULL, this);
        if (m_lTranHandle >= 0)
        {
            m_bGetNext = TRUE;
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Start Remote Config successfully");
            DWORD dwThreadId;
            m_hGetInfoThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetConfigThread), this, 0, &dwThreadId);
            if (m_hGetInfoThread == NULL)
            {
                char szLan[128] = { 0 };
                g_StringLanType(szLan, "打开注册线程失败!", "open register thread Fail!");
                AfxMessageBox(szLan);
                return;
            }
            CloseHandle(m_hGetInfoThread);
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Start Remote Config failed");
            return;
        }
    }
}
