// DLGResetLoginPassWord.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DLGResetLoginPassWord.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"

// CDLGResetLoginPassWord 对话框

IMPLEMENT_DYNAMIC(CDLGResetLoginPassWord, CDialogEx)

CDLGResetLoginPassWord::CDLGResetLoginPassWord(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDLGResetLoginPassWord::IDD, pParent)
    , m_LoginPassWordCheck(_T(""))
    , m_sAnswer(_T(""))
    , m_bMark(FALSE)
    , m_sAnswer2(_T(""))
    , m_bMark2(FALSE)
    , m_bMark3(FALSE)
    , m_sAnswer3(_T(""))
    , m_csFilePath(_T(""))
{
    m_lDownloadHandle = -1;
    m_bDownLoading = FALSE;
    m_hDownloadThread = NULL;

    //IDC_BTN_MAINTENANCE_WALL
    //GetDlgItem(IDC_BTN_MANUAL_CHECK)->ShowWindow(SW_HIDE);
}

CDLGResetLoginPassWord::~CDLGResetLoginPassWord()
{
}

void CDLGResetLoginPassWord::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_LOGINPW, m_LoginPassWordCheck);
    DDX_Control(pDX, IDC_COMBO_INDEX, m_dwIndex);
    DDX_Text(pDX, IDC_EDIT_ANSWER, m_sAnswer);
    DDX_Check(pDX, IDC_CHECK_MARK, m_bMark);
    DDX_Control(pDX, IDC_COMBO_INDEX2, m_dwIndex2);
    DDX_Text(pDX, IDC_EDIT_ANSWER2, m_sAnswer2);
    DDX_Check(pDX, IDC_CHECK_MARK2, m_bMark2);
    DDX_Check(pDX, IDC_CHECK_MARK3, m_bMark3);
    DDX_Text(pDX, IDC_EDIT_ANSWER3, m_sAnswer3);
    DDX_Control(pDX, IDC_COMBO_INDEX3, m_dwIndex3);
    DDX_Text(pDX, IDC_EDIT_FILE_PATH, m_csFilePath);
}


BEGIN_MESSAGE_MAP(CDLGResetLoginPassWord, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_GET, &CDLGResetLoginPassWord::OnBnClickedBtnGet)
    ON_BN_CLICKED(IDC_BTN_SET, &CDLGResetLoginPassWord::OnBnClickedBtnSet)
    ON_BN_CLICKED(IDC_BTN_FILE_PATH, &CDLGResetLoginPassWord::OnBnClickedBtnFilePath)
    ON_BN_CLICKED(IDC_BTN_FILE_DOWNLOAD, &CDLGResetLoginPassWord::OnBnClickedBtnFileDownload)
    ON_BN_CLICKED(IDC_BTN_MANUAL_CHECK, &CDLGResetLoginPassWord::OnBnClickedBtnManualCheck)
END_MESSAGE_MAP()


// CDLGResetLoginPassWord 消息处理程序


void CDLGResetLoginPassWord::OnBnClickedBtnLoginpwCheck()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    memset(&m_struLoginPassWord, 0, sizeof(m_struLoginPassWord));

    m_struLoginPassWord.dwSize = sizeof(m_struLoginPassWord);
    sprintf(m_struLoginPassWord.sLoginPassWord, "%s", m_LoginPassWordCheck);
    return;

    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &m_struLoginPassWord;
    struCfg.dwInSize = sizeof(m_struLoginPassWord);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lUserID, NET_DVR_CHECK_LOGIN_PASSWORDCFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_CHECK_LOGIN_PASSWORDCFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_CHECK_LOGIN_PASSWORDCFG");
    }
    UpdateData(FALSE);
}


void CDLGResetLoginPassWord::OnBnClickedBtnGet()
{
    UpdateData(TRUE);
    // TODO:  在此添加控件通知处理程序代码
    NET_DVR_SECURITY_QUESTION_CFG m_struSEQConfig = { 0 };
    NET_DVR_STD_CONFIG struCfg = { 0 };

    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &m_struSEQConfig;
    struCfg.dwOutSize = sizeof(m_struSEQConfig);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_SECURITY_QUESTION_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SECURITY_QUESTION_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SECURITY_QUESTION_CFG");

    }

    int temp = 0;
    for (int i = 0; i < 32;i++)
    {

        if (m_struSEQConfig.struSecurityQuestion[i].byMark==1)
        {
            if (temp==0)
            {
                m_dwIndex.SetCurSel(m_struSEQConfig.struSecurityQuestion[i].dwId - 1);
                m_sAnswer = "";
                m_bMark = m_struSEQConfig.struSecurityQuestion[i].byMark;
            }
            else if (temp == 1)
            {
                m_dwIndex2.SetCurSel(m_struSEQConfig.struSecurityQuestion[i].dwId - 1);
                m_sAnswer2 = "";
                m_bMark2 = m_struSEQConfig.struSecurityQuestion[i].byMark;
            }
            else
            {
                m_dwIndex3.SetCurSel(m_struSEQConfig.struSecurityQuestion[i].dwId - 1);
                m_sAnswer3 = "";
                m_bMark3 = m_struSEQConfig.struSecurityQuestion[i].byMark;
            }
            temp = temp + 1;
        }
    }

    UpdateData(FALSE);

}


void CDLGResetLoginPassWord::OnBnClickedBtnSet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    NET_DVR_SECURITY_QUESTION_CFG struSEQConfig = { 0 };
    struSEQConfig.dwSize = sizeof(struSEQConfig);

    sprintf_s(struSEQConfig.sLoginPassWord, "%s", m_LoginPassWordCheck);

    struSEQConfig.struSecurityQuestion[0].dwId = m_dwIndex.GetCurSel() + 1;
    sprintf_s(struSEQConfig.struSecurityQuestion[0].sAnswer, "%s", m_sAnswer);
    struSEQConfig.struSecurityQuestion[0].byMark = m_bMark;

    struSEQConfig.struSecurityQuestion[1].dwId = m_dwIndex2.GetCurSel() + 1;
    sprintf_s(struSEQConfig.struSecurityQuestion[1].sAnswer, "%s", m_sAnswer2);
    struSEQConfig.struSecurityQuestion[1].byMark = m_bMark2;

    struSEQConfig.struSecurityQuestion[2].dwId = m_dwIndex3.GetCurSel() + 1;
    sprintf_s(struSEQConfig.struSecurityQuestion[2].sAnswer, "%s", m_sAnswer3);
    struSEQConfig.struSecurityQuestion[2].byMark = m_bMark3;

    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struSEQConfig;
    struCfg.dwInSize = sizeof(struSEQConfig);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lUserID, NET_DVR_SET_SECURITY_QUESTION_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SECURITY_QUESTION_CFG");

        //解析respons
        CString lockstatus = "";
        CString reslocktime = "";
        CString resretrytimes = "";
        CXmlBase xmlBase;
        xmlBase.Parse(m_szStatusBuf);
        if (xmlBase.FindElem("ResponseStatus") && xmlBase.IntoElem())
        {
            if (xmlBase.FindElem("lockStatus"))
            {
                lockstatus = xmlBase.GetData().c_str();                
            }
            if (xmlBase.FindElem("retryTimes"))
            {
                resretrytimes = xmlBase.GetData().c_str();
            }
            if (xmlBase.FindElem("resLockTime"))
            {
                reslocktime = xmlBase.GetData().c_str();
            }
        }

        char szLan[1024] = { 0 };
        sprintf_s(szLan, "锁定状态：%s，剩余重试次数：%s次，剩余锁定时间：%s秒。",lockstatus, resretrytimes, reslocktime);
        MessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_SECURITY_QUESTION_CFG");
        OutputDebugString(m_szStatusBuf);
    }
    UpdateData(FALSE);
}


void CDLGResetLoginPassWord::OnBnClickedBtnFilePath()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    static char szFilter[] = "All File(*.*)|*.*||";
    CFileDialog dlg(TRUE, "*.*", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
    if (dlg.DoModal() == IDOK)
    {
        m_csFilePath = dlg.GetPathName();
        UpdateData(FALSE);
    }
}

DWORD  GetDownloadGUIDFileThread(LPVOID pParam)
{
    CDLGResetLoginPassWord *pThis = (CDLGResetLoginPassWord*)pParam;

    DWORD dwState = 0;
    DWORD dwProgress = 0;
    char szLan[256] = { 0 };


    while (TRUE)
    {
        dwState = NET_DVR_GetDownloadState(pThis->m_lDownloadHandle, &dwProgress);
        if (dwState == 1)
        {
            g_StringLanType(szLan, "下载成功", "Download successfully");
            pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
            pThis->m_bDownLoading = FALSE;
            g_StringLanType(szLan, "下载", "Download");
            pThis->GetDlgItem(IDC_BTN_FILE_DOWNLOAD)->SetWindowText(szLan);
            pThis->m_bDownLoading = FALSE;
            break;
        }
        else if (dwState == 2)
        {
            g_StringLanType(szLan, "正在下载,已下载:", "Is Downloading,progress:");
            sprintf(szLan, "%s%d", szLan, dwProgress);
            pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        }
        else if (dwState == 3)
        {
            g_StringLanType(szLan, "下载失败", "Download failed");
            pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
            break;
        }
        else if (dwState == 4)
        {
            if (dwProgress == 100)
            {
                g_StringLanType(szLan, "下载成功", "Download successfully");
                pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
                g_StringLanType(szLan, "下载", "DownLoad");
                pThis->GetDlgItem(IDC_BTN_FILE_DOWNLOAD)->SetWindowText(szLan);
                pThis->m_bDownLoading = FALSE;
                break;
            }
            else
            {
                g_StringLanType(szLan, "网络断开，状态未知", "Network disconnect, status unknown");
                pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
                break;
            }
        }
        else if (dwState == 6)
        {
            NET_DVR_GUID_FILE_STATUS_INFO m_struStatusInfo = { 0 };
            m_struStatusInfo.dwSize = sizeof(NET_DVR_GUID_FILE_STATUS_INFO);
            NET_DVR_GetDownloadStateInfo(pThis->m_lDownloadHandle, &m_struStatusInfo);

            CString locstatus = "";

            if (m_struStatusInfo.byLockStatus==0)
            {
                locstatus = "未锁定";
            }
            else
            {
                locstatus = "锁定";
            }
            sprintf_s(szLan, "锁定状态：%s，剩余重试次数：%d次，剩余锁定时间：%d秒。", locstatus, m_struStatusInfo.byRetryNum, m_struStatusInfo.dwLockTime);
            pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
            g_StringLanType(szLan, "下载失败", "Download failed");
            pThis->GetDlgItem(IDC_BTN_FILE_DOWNLOAD)->SetWindowText(szLan);

            NET_DVR_StopDownload(pThis->m_lDownloadHandle);
            pThis->m_bDownLoading = FALSE;
            break;
        }


        if (dwState != 2 && dwState != 5)
        {
            NET_DVR_StopDownload(pThis->m_lDownloadHandle);
            pThis->m_bDownLoading = FALSE;
            g_StringLanType(szLan, "下载", "Download");
            pThis->GetDlgItem(IDC_BTN_FILE_DOWNLOAD)->SetWindowText(szLan);
        }
    }

    return FALSE;
}

void CDLGResetLoginPassWord::OnBnClickedBtnFileDownload()
{
    // TODO:  在此添加控件通知处理程序代码
    char szLan[128] = { 0 };
    if (m_bDownLoading == FALSE)
    {
        UpdateData(TRUE);
        GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        char szFileName[MAX_PATH];
        char szInfoBuf[128] = { 0 };
        if (m_csFilePath.IsEmpty())
        {
            MessageBox("保存文件路径不能为空");
            return;
        }
        strcpy(szFileName, m_csFilePath);

        NET_DVR_GUID_FILE_EXPORT struGUIDFileExport;
        memset(&struGUIDFileExport, 0, sizeof(NET_DVR_GUID_FILE_EXPORT));

        struGUIDFileExport.dwSize = sizeof(NET_DVR_GUID_FILE_EXPORT);
        sprintf(struGUIDFileExport.sLoginPassWord, "%s", m_LoginPassWordCheck);
        //sprintf(struGUIDFileExport.sLoginPassWord, "%s", "ddd");

        m_lDownloadHandle = NET_DVR_StartDownload(m_lUserID, NET_SDK_DOWNLOAD_GUID_FILE, &struGUIDFileExport, sizeof(struGUIDFileExport), szFileName);
        if (m_lDownloadHandle < 0)
        {
            int iError = NET_DVR_GetLastError();
            char szLan[256] = { 0 };
            sprintf(szLan, "NET_SDK_DOWNLOAD_GUID_FILE Download Faile. Error:%d", iError);
            AfxMessageBox(szLan);
            return;
        }

        DWORD dwThreadId = 0;
        m_hDownloadThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetDownloadGUIDFileThread), this, 0, &dwThreadId);
        if (m_hDownloadThread == NULL)
        {
            char szLan[256] = { 0 };
            g_StringLanType(szLan, "打开下载文件线程失败!", "open DownLoad thread Fail!");
            AfxMessageBox(szLan);
            return;
        }
        g_StringLanType(szLan, "停止下载", "Stop DownLoad");
        GetDlgItem(IDC_BTN_FILE_DOWNLOAD)->SetWindowText(szLan);
        m_bDownLoading = TRUE;
    }
    else
    {
        NET_DVR_StopDownload(m_lDownloadHandle);
        m_bDownLoading = FALSE;
        g_StringLanType(szLan, "下载", "DownLoad");
        GetDlgItem(IDC_BTN_FILE_DOWNLOAD)->SetWindowText(szLan);
    }
    UpdateData(FALSE);
}


void CDLGResetLoginPassWord::OnBnClickedBtnManualCheck()
{
    // TODO:  在此添加控件通知处理程序代码
}
