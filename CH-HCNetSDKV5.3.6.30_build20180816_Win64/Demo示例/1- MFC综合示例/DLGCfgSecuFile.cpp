// DLGCfgSecuFile.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DLGCfgSecuFile.h"
#include "afxdialogex.h"


// CDLGCfgSecuFile 对话框

IMPLEMENT_DYNAMIC(CDLGCfgSecuFile, CDialogEx)

CDLGCfgSecuFile::CDLGCfgSecuFile(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDLGCfgSecuFile::IDD, pParent)
    , m_strFilePath(_T(""))
    , m_strSecretKey(_T(""))
{

}

CDLGCfgSecuFile::~CDLGCfgSecuFile()
{
}

void CDLGCfgSecuFile::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDT_FILE_PATH_FD, m_strFilePath);
    DDX_Text(pDX, IDC_EDT_SECRET_KEY, m_strSecretKey);
}


BEGIN_MESSAGE_MAP(CDLGCfgSecuFile, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_FILE_BROWER, &CDLGCfgSecuFile::OnBnClickedBtnFileBrower)
    ON_BN_CLICKED(IDC_BTN_UPLOAD, &CDLGCfgSecuFile::OnBnClickedBtnUpload)
    ON_BN_CLICKED(IDC_BTN_DWONLOAD, &CDLGCfgSecuFile::OnBnClickedBtnDwonload)
END_MESSAGE_MAP()


// CDLGCfgSecuFile 消息处理程序


void CDLGCfgSecuFile::OnBnClickedBtnFileBrower()
{
    UpdateData(TRUE);

    char szLan[1024] = { 0 };
    static char szFilter[] = "All File(*.*)|*.*||";
    CFileDialog dlg(TRUE, "*.*", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
    if (dlg.DoModal() == IDOK)
    {
        m_strFilePath = dlg.GetPathName();
        SetDlgItemText(IDC_EDT_FILE_PATH_FD, m_strFilePath);
    }

    m_hFile = CreateFile(m_strFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (INVALID_HANDLE_VALUE == m_hFile)
    {
        g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
        AfxMessageBox(szLan);
        return;
    }
    BY_HANDLE_FILE_INFORMATION struFileInfo = { 0 };
    if (!GetFileInformationByHandle(m_hFile, &struFileInfo))
    {
        g_StringLanType(szLan, "获取文件信息失败", "Get file info failed ");
        AfxMessageBox(szLan);
        return;
    }

    m_iFileSize = (((INT64)struFileInfo.nFileSizeHigh << 32)) + (INT64)struFileInfo.nFileSizeLow;
    if (m_iFileSize == 0)
    {
        g_StringLanType(szLan, "文件为空", "Configure file is empty");
        AfxMessageBox(szLan);
        return;
    }
}

DWORD  GetUpLoadCfgFileThread(LPVOID pParam)
{
    CDLGCfgSecuFile *pThis = (CDLGCfgSecuFile*)pParam;

    DWORD dwState = 0;
    DWORD dwProgress = 0;
    char szLan[256] = { 0 };


    while (TRUE)
    {
        dwState = NET_DVR_GetUploadState(pThis->m_lUploadHandle, &dwProgress);
        if (dwState == 1)
        {
            g_StringLanType(szLan, "上传成功", "Upload successfully");
            pThis->GetDlgItem(IDC_STAT_PROGRESS)->SetWindowText(szLan);
            pThis->m_bUpLoading = FALSE;
            g_StringLanType(szLan, "上传", "Upload");
            pThis->GetDlgItem(IDC_BTN_UPLOAD)->SetWindowText(szLan);
            pThis->m_bUpLoading = FALSE;
            break;
        }
        else if (dwState == 2)
        {
            g_StringLanType(szLan, "正在上传,已上传:", "Is uploading,progress:");
            sprintf(szLan, "%s%d", szLan, dwProgress);
            pThis->GetDlgItem(IDC_STAT_PROGRESS)->SetWindowText(szLan);
        }
        else if (dwState == 3)
        {
            g_StringLanType(szLan, "上传失败", "Upload failed");
            pThis->GetDlgItem(IDC_STAT_PROGRESS)->SetWindowText(szLan);
            break;
        }
        else if (dwState == 34)
        {
            g_StringLanType(szLan, "安全校验密钥错误", "Secret Key Error");
            pThis->GetDlgItem(IDC_STAT_PROGRESS)->SetWindowText(szLan);
            break;
        }
        else if (dwState == 4)
        {
            if (dwProgress == 100)
            {
                g_StringLanType(szLan, "上传成功", "Upload successfully");
                pThis->GetDlgItem(IDC_STAT_PROGRESS)->SetWindowText(szLan);
                g_StringLanType(szLan, "上传", "UpLoad");
                pThis->GetDlgItem(IDC_BTN_UPLOAD)->SetWindowText(szLan);
                pThis->m_bUpLoading = FALSE;
                break;
            }
            else
            {
                g_StringLanType(szLan, "网络断开，状态未知", "Network disconnect, status unknown");
                pThis->GetDlgItem(IDC_STAT_PROGRESS)->SetWindowText(szLan);
                break;
            }

        }

        if (dwState != 2 && dwState != 5)
        {
            NET_DVR_UploadClose(pThis->m_lUploadHandle);
            pThis->m_bUpLoading = FALSE;
            g_StringLanType(szLan, "上传", "UpLoad");
            pThis->GetDlgItem(IDC_BTN_UPLOAD)->SetWindowText(szLan);
        }
    }

    return FALSE;
}

void CDLGCfgSecuFile::OnBnClickedBtnUpload()
{
    UpdateData(TRUE);
    char szLan[128] = { 0 };
    char strFileName[129] = { 0 };
    strncpy(strFileName, m_strFilePath, 128);
    NET_DVR_SECURITY_CFG_FILE_COND struCfgSecFileData = { 0 };
    struCfgSecFileData.dwSize = sizeof(struCfgSecFileData);

    strncpy(struCfgSecFileData.szSecretKey, m_strSecretKey.GetBuffer(m_strSecretKey.GetLength()), NET_SDK_SECRETKEY_LEN);

    m_lUploadHandle = NET_DVR_UploadFile(m_lUserID, UPLOAD_SECURITY_CFG_FILE, &struCfgSecFileData, sizeof(struCfgSecFileData), strFileName);


    if (m_lUploadHandle < 0)
    {
        NET_DVR_StopUploadFile(m_lUploadHandle);
        AfxMessageBox("UPLOAD_SECURITY_CFG_FILE Upload Failed");
        return;
    }

    DWORD dwThreadId = 0;
    m_hUpLoadThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetUpLoadCfgFileThread), this, 0, &dwThreadId);
    if (m_hUpLoadThread == NULL)
    {
        char szLan[256] = { 0 };
        g_StringLanType(szLan, "打开长传文件线程失败!", "open UpLoad thread Fail!");
        AfxMessageBox(szLan);
        return;
    }
    m_bUpLoading = TRUE;
}

DWORD CfgDataDownloadThread(LPVOID pParam)
{
    CDLGCfgSecuFile *pThis = (CDLGCfgSecuFile*)pParam;
    DWORD dwProgress = 0;
    LONG    lStatus = 0;
    while (1)
    {
        if (pThis->m_bStopDownload)
        {
            break;
        }

        lStatus = NET_DVR_GetDownloadState(pThis->m_lDownloadHandle, &dwProgress);
        if (lStatus == -1)
        {
            g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetDownloadState");
        }
        else
        {
            g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetDownloadState,status[%d], progress[%d]", lStatus, dwProgress);
        }
        Sleep(1000);
        if (lStatus != 2)
        {
            break;
        }
    }
    return 0;
}

void CDLGCfgSecuFile::OnBnClickedBtnDwonload()
{
    UpdateData(TRUE);

    char cFilename[256] = { 0 };
    CString sTemp = "c:\\CfgFile";
    CTime time = CTime::GetCurrentTime();
    DWORD dwRet = GetFileAttributes(sTemp);
    if ((dwRet == -1) || !(dwRet & FILE_ATTRIBUTE_DIRECTORY))
    {
        CreateDirectory(sTemp, NULL);
    }

    sprintf(cFilename, "%s\\%s_%4d%02d%02d_%02d%02d%02d.txt", \
        sTemp, g_struDeviceInfo[m_iDeviceIndex].chDeviceIPInFileName, \
        time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());

    NET_DVR_SECURITY_CFG_FILE_COND struCfgSecFileData;
    memset(&struCfgSecFileData, 0, sizeof(NET_DVR_SECURITY_CFG_FILE_COND));

    struCfgSecFileData.dwSize = sizeof(NET_DVR_SECURITY_CFG_FILE_COND);

    strncpy(struCfgSecFileData.szSecretKey, m_strSecretKey.GetBuffer(m_strSecretKey.GetLength()), NET_SDK_SECRETKEY_LEN);

    m_lDownloadHandle = NET_DVR_StartDownload(m_lUserID, NET_SDK_DOWNLOAD_SECURITY_CFG_FILE, &struCfgSecFileData, sizeof(struCfgSecFileData), cFilename);
    if (m_lDownloadHandle >= 0)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StartDownload[%s]", cFilename);
        m_bStopDownload = FALSE;
        DWORD dwThreadID = 0;
        m_hDownloadThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(CfgDataDownloadThread), this, 0, &dwThreadID);
        if (m_hDownloadThread == NULL)
        {
            char szLan[128] = { 0 };
            g_StringLanType(szLan, "打开下载配置文件线程失败!", "open Download picture thread Fail!");
            AfxMessageBox(szLan);
            return;
        }
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartDownload[%s]", cFilename);
    }
}


