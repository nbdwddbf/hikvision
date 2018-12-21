// DlgFaceData.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgFaceData.h"
#include "afxdialogex.h"
#include <afxinet.h>
#include "DlgUploadFaceLib.h"
#include "DlgFacelibSearch.h"

// CDlgFaceData 对话框

IMPLEMENT_DYNAMIC(CDlgFaceData, CDialog)

CDlgFaceData::CDlgFaceData(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFaceData::IDD, pParent)
    , m_szPicID(_T(""))
    , m_szFDID(_T(""))
    , m_strFilePath(_T(""))
    , m_dwUploadProgress(0)
    , m_szCheckCode(_T(""))
    , m_szPathFD(_T(""))
    , m_strFDCustomInfo(_T(""))
    , m_bCover(FALSE)
{

}

CDlgFaceData::~CDlgFaceData()
{
}

void CDlgFaceData::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDT_PIC_ID, m_szPicID);
    DDX_Text(pDX, IDC_EDT_FD_ID, m_szFDID);
    DDX_Text(pDX, IDC_EDT_FILE_PATH, m_strFilePath);
    DDX_Text(pDX, IDC_STAT_PROGRESS, m_dwUploadProgress);
    DDX_Text(pDX, IDC_EDIT_FD_CUSTOM_INFO, m_strFDCustomInfo);
    DDX_Control(pDX, IDC_COMBO_FD_TYPE, m_comFDLibType);
    DDX_Text(pDX, IDC_EDT_CHECK_CODE, m_szCheckCode);
    DDX_Text(pDX, IDC_EDT_FILE_PATH_FD, m_szPathFD);
    DDX_Check(pDX, IDC_CHECK1, m_bCover);
}


BEGIN_MESSAGE_MAP(CDlgFaceData, CDialog)
    ON_BN_CLICKED(IDC_BTN_START_UPLOAD, &CDlgFaceData::OnBnClickedBtnStartUpload)
    ON_BN_CLICKED(IDC_BTN_SELECT_FILE, &CDlgFaceData::OnBnClickedBtnSelectFile)
    ON_BN_CLICKED(IDC_BTN_UODATE, &CDlgFaceData::OnBnClickedBtnUodate)
    ON_BN_CLICKED(IDC_BTN_STOP_UPLOAD, &CDlgFaceData::OnBnClickedBtnStopUpload)
    ON_BN_CLICKED(IDC_BTN_UPLOAD_FACELIB, &CDlgFaceData::OnBnClickedBtnUploadFacelib)
    ON_BN_CLICKED(IDC_BTN_FILE_BROWER, &CDlgFaceData::OnBnClickedBtnFileBrower)
    ON_BN_CLICKED(IDC_BTN_UPLOAD, &CDlgFaceData::OnBnClickedBtnUpload)
    ON_BN_CLICKED(IDC_BTN_DWONLOAD, &CDlgFaceData::OnBnClickedBtnDwonload)
    ON_BN_CLICKED(IDC_BTN_FACELIB_SEARCH, &CDlgFaceData::OnBnClickedBtnFacelibSearch)
END_MESSAGE_MAP()


// CDlgFaceData 消息处理程序


BOOL CDlgFaceData::OnInitDialog()
{
    CDialog::OnInitDialog();

    //FIXME:
    //m_comDirectedChannel.InsertStream(0, _T(""));
    //m_comDirectedChannel.SetCurSel(0);

    memset(&m_struFaceDataRet, 0, sizeof(m_struFaceDataRet));
    
    UpdateData(FALSE);

    return TRUE;
}
DWORD  GetUpLoadFDFileThread(LPVOID pParam)
{
    CDlgFaceData *pThis = (CDlgFaceData*)pParam;

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
            NET_DVR_GetUploadResult(pThis->m_lUploadHandle, &pThis->m_struFaceDataRet, sizeof(pThis->m_struFaceDataRet));
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
        else if (dwState == 4)
        {
            if (dwProgress == 100)
            {
                g_StringLanType(szLan, "上传成功", "Upload successfully");
                pThis->GetDlgItem(IDC_STAT_PROGRESS)->SetWindowText(szLan);
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
        else if (dwState == 35)
        {
            g_StringLanType(szLan, "图片URL未开始下载", "URL Download Not Start");
            pThis->GetDlgItem(IDC_STAT_PROGRESS_FD)->SetWindowText(szLan);
            break;
        }
        else if (dwState == 36)
        {
            g_StringLanType(szLan, "customHumanID重复", "customHumanID Repeat");
            pThis->GetDlgItem(IDC_STAT_PROGRESS_FD)->SetWindowText(szLan);
            break;
        }
        else if (dwState == 37)
        {
            g_StringLanType(szLan, "customHumanID有误", "customHumanID error");
            pThis->GetDlgItem(IDC_STAT_PROGRESS_FD)->SetWindowText(szLan);
            break;
        }

        if (dwState != 2 && dwState != 5)
        {
            NET_DVR_UploadClose(pThis->m_lUploadHandle);
            pThis->m_bUpLoading = FALSE;
        }
    }
    return FALSE;
}


void CDlgFaceData::OnBnClickedBtnStartUpload()
{
    UpdateData(TRUE);

    NET_DVR_UPLOAD_FACE_DATA struFacedataParam = { 0 };
    struFacedataParam.dwSize = sizeof(struFacedataParam);

    strncpy(struFacedataParam.szFDID, m_szFDID.GetBuffer(m_szFDID.GetLength()), NET_SDK_MAX_PICID_LEN);

    struFacedataParam.byFDLibType = m_comFDLibType.GetCurSel();
    sprintf_s(struFacedataParam.szCustomInfo, "%s", m_strFDCustomInfo);

    m_lUploadHandle = NET_DVR_UploadFile_V40(m_lUserID, UPLOAD_FACE_DATA, &struFacedataParam, sizeof(struFacedataParam), m_strFilePath, NULL, 0);

    if (m_lUploadHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "UPLOAD_BACKGROUND_PIC");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "UPLOAD_BACKGROUND_PIC");
        DWORD dwThreadId = 0;
        m_hUpLoadThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetUpLoadFDFileThread), this, 0, &dwThreadId);
        if (m_hUpLoadThread == NULL)
        {
            char szLan[256] = { 0 };
            g_StringLanType(szLan, "打开长传文件线程失败!", "open UpLoad thread Fail!");
            AfxMessageBox(szLan);
            return;
        }
        
    }
    UpdateData(FALSE);
}


void CDlgFaceData::OnBnClickedBtnSelectFile()
{

    UpdateData(TRUE);

    char szLan[1024] = { 0 };
    static char szFilter[] = "All File(*.*)|*.*||";
    CFileDialog dlg(TRUE, "*.*", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
    if (dlg.DoModal() == IDOK)
    {
        m_strFilePath = dlg.GetPathName();
        SetDlgItemText(IDC_EDT_FILE_PATH, m_strFilePath);
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


DWORD FaceDataDownloadThread(LPVOID pParam)
{
    CDlgFaceData *pThis = (CDlgFaceData*)pParam;
    DWORD dwProgress = 0;
    LONG    lStatus = 0;
    while (1)
    {
        if (pThis->m_bStopDownloadPic)
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



void CDlgFaceData::OnBnClickedBtnUodate()
{
    m_szPicID = m_struFaceDataRet.szPicID;
    UpdateData(FALSE);
}


void CDlgFaceData::OnBnClickedBtnStopUpload()
{
    // TODO:  在此添加控件通知处理程序代码
}


void CDlgFaceData::OnBnClickedBtnUploadFacelib()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgUploadFaceLib dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
}



void CDlgFaceData::OnBnClickedBtnFileBrower()
{
    UpdateData(TRUE);

    char szLan[1024] = { 0 };
    static char szFilter[] = "All File(*.*)|*.*||";
    CFileDialog dlg(TRUE, "*.*", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
    if (dlg.DoModal() == IDOK)
    {
        m_szPathFD = dlg.GetPathName();
        SetDlgItemText(IDC_EDT_FILE_PATH_FD, m_szPathFD);
    }

    m_hFile = CreateFile(m_szPathFD, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
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
DWORD  GetUpLoadLibFileThread(LPVOID pParam)
{
    CDlgFaceData *pThis = (CDlgFaceData*)pParam;

    DWORD dwState = 0;
    DWORD dwProgress = 0;
    char szLan[256] = { 0 };


    while (TRUE)
    {
        dwState = NET_DVR_GetUploadState(pThis->m_lUploadHandleFD, &dwProgress);
        if (dwState == 1)
        {
            g_StringLanType(szLan, "上传成功", "Upload successfully");
            pThis->GetDlgItem(IDC_STAT_PROGRESS_FD)->SetWindowText(szLan);
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
            pThis->GetDlgItem(IDC_STAT_PROGRESS_FD)->SetWindowText(szLan);
        }
        else if (dwState == 3)
        {
            g_StringLanType(szLan, "上传失败", "Upload failed");
            pThis->GetDlgItem(IDC_STAT_PROGRESS_FD)->SetWindowText(szLan);
            break;
        }
        else if (dwState == 4)
        {
            if (dwProgress == 100)
            {
                g_StringLanType(szLan, "上传成功", "Upload successfully");
                pThis->GetDlgItem(IDC_STAT_PROGRESS_FD)->SetWindowText(szLan);
                g_StringLanType(szLan, "上传", "UpLoad");
                pThis->GetDlgItem(IDC_BTN_UPLOAD)->SetWindowText(szLan);
                pThis->m_bUpLoading = FALSE;
                break;
            }
            else
            {
                g_StringLanType(szLan, "网络断开，状态未知", "Network disconnect, status unknown");
                pThis->GetDlgItem(IDC_STAT_PROGRESS_FD)->SetWindowText(szLan);
                break;
            }

        }
        else if (dwState == 35)
        {
            g_StringLanType(szLan, "图片URL未开始下载", "URL Download Not Start");
            pThis->GetDlgItem(IDC_STAT_PROGRESS_FD)->SetWindowText(szLan);
            break;
        }
        else if (dwState == 36)
        {
            g_StringLanType(szLan, "customHumanID重复", "customHumanID Repeat");
            pThis->GetDlgItem(IDC_STAT_PROGRESS_FD)->SetWindowText(szLan);
            break; 
        }
        else if (dwState == 37)
        {
            g_StringLanType(szLan, "customHumanID有误", "customHumanID error");
            pThis->GetDlgItem(IDC_STAT_PROGRESS_FD)->SetWindowText(szLan);
            break;
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

void CDlgFaceData::OnBnClickedBtnUpload()
{
    UpdateData(TRUE);
    char szLan[128] = { 0 };
    char strFileName[129] = { 0 };
    strncpy(strFileName, m_szPathFD, 128);
    NET_DVR_FD_DATA_COND struFDData = { 0 };
    struFDData.dwSize = sizeof(struFDData);

    strncpy(struFDData.szFDID, m_szFDID.GetBuffer(m_szFDID.GetLength()), NET_SDK_MAX_FDID_LEN);
    strncpy(struFDData.szCheckCode, m_szCheckCode.GetBuffer(m_szCheckCode.GetLength()), NET_SDK_CHECK_CODE_LEN);
    struFDData.byCover = m_bCover;

    m_lUploadHandleFD = NET_DVR_UploadFile(m_lUserID, UPLOAD_FD_DATA, &struFDData, sizeof(struFDData), strFileName);


    if (m_lUploadHandleFD < 0)
    {
        NET_DVR_StopUploadFile(m_lUploadHandleFD);
        AfxMessageBox("UPLOAD_THERMOMETRIC_FILE Upload Failed");
        return;
    }

    DWORD dwThreadId = 0;
    m_hUpLoadThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetUpLoadLibFileThread), this, 0, &dwThreadId);
    if (m_hUpLoadThread == NULL)
    {
        char szLan[256] = { 0 };
        g_StringLanType(szLan, "打开长传文件线程失败!", "open UpLoad thread Fail!");
        AfxMessageBox(szLan);
        return;
    }
    m_bUpLoading = TRUE;
}


void CDlgFaceData::OnBnClickedBtnDwonload()
{
    UpdateData(TRUE);

    char cFilename[256] = { 0 };
    CString sTemp = "c:\\Facedata";
    CTime time = CTime::GetCurrentTime();
    DWORD dwRet = GetFileAttributes(sTemp);
    if ((dwRet == -1) || !(dwRet & FILE_ATTRIBUTE_DIRECTORY))
    {
        CreateDirectory(sTemp, NULL);
    }

    sprintf(cFilename, "%s\\%s_%4d%02d%02d_%02d%02d%02d.txt", \
        sTemp, g_struDeviceInfo[m_iDeviceIndex].chDeviceIPInFileName, \
        time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());

    NET_DVR_FD_DATA_COND struFDData;
    memset(&struFDData, 0, sizeof(NET_DVR_FD_DATA_COND));

    struFDData.dwSize = sizeof(NET_DVR_FD_DATA_COND);

    strncpy(struFDData.szFDID, m_szFDID.GetBuffer(m_szFDID.GetLength()), NET_SDK_MAX_FDID_LEN);
    strncpy(struFDData.szCheckCode, m_szCheckCode.GetBuffer(m_szCheckCode.GetLength()), NET_SDK_CHECK_CODE_LEN);

    m_lDownloadHandle = NET_DVR_StartDownload(m_lUserID, NET_SDK_DOWNLOAD_FD_DATA, &struFDData, sizeof(struFDData), cFilename);
    if (m_lDownloadHandle >= 0)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StartDownload[%s]", cFilename);
        m_bStopDownloadPic = FALSE;
        DWORD dwThreadID = 0;
        m_hPicDownloadThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(FaceDataDownloadThread), this, 0, &dwThreadID);
        if (m_hPicDownloadThread == NULL)
        {
            char szLan[128] = { 0 };
            g_StringLanType(szLan, "打开下载图片线程失败!", "open Download picture thread Fail!");
            AfxMessageBox(szLan);
            return;
        }
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartDownload[%s]", cFilename);
    }
}


void CDlgFaceData::OnBnClickedBtnFacelibSearch()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgFacelibSearch dlg;
    dlg.m_lUserID = m_lUserID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
}
