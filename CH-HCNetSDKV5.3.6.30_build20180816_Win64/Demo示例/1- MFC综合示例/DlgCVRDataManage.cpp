// DlgCVRDataManage.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgCVRDataManage.h"
#include "afxdialogex.h"


// CDlgCVRDataManage 对话框

IMPLEMENT_DYNAMIC(CDlgCVRDataManage, CDialogEx)

CDlgCVRDataManage::CDlgCVRDataManage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCVRDataManage::IDD, pParent)
    , m_strDownloadUrl(_T(""))
    , m_strFileName(_T(""))
    , m_strFilePath(_T(""))
    , m_dwFileSize(0)
    , m_iFileVolumeID(0)
    , m_strUploadUrl(_T(""))
    , m_strSavePath(_T(""))
    , m_bUploadSubpackage(FALSE)
    , m_bDownloadDataCallback(FALSE)
    , m_strFileSearchUrl(_T(""))
    , m_strFileLockUrl(_T(""))
    , m_iUploadSpeed(0)
    , m_iDownloadSpeed(0)
    , m_iLockTime(0)
    , m_bArchive(FALSE)
{
    m_lServerID = -1;
    m_lDeviceIndex = -1;
    m_lUploadHandle = -1;
    m_bUpLoading = FALSE;
    m_hUpLoadThread = NULL;
    m_dwThreadId = 0;
    m_hUpLoadSendThread = NULL;
    m_dwSendThreadId = 0;
    memset(&m_struFileVolumeDataInfo, 0, sizeof(m_struFileVolumeDataInfo));

    m_bDownLoading = FALSE;
    m_lDownloadHandle = -1;
    m_hDownloadThread = NULL;
    memset(&m_struFileVolumeDataParam, 0, sizeof(m_struFileVolumeDataParam));

    m_iRowCount = 0;
    m_bSelectItem = FALSE;
    m_iSubItem = -1;
    m_iLastItem = -1;

    m_iRowCountLock = 0;
    m_bSelectItemLock = FALSE;
    m_iSubItemLock = -1;
    m_iLastItemLock = -1;
}

CDlgCVRDataManage::~CDlgCVRDataManage()
{
}

void CDlgCVRDataManage::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_FILE_TYPE, m_comboFileType);
    DDX_Text(pDX, IDC_EDIT_DOWNLOAD_URL, m_strDownloadUrl);
    DDX_Text(pDX, IDC_EDIT_FILE_NAME, m_strFileName);
    DDX_Text(pDX, IDC_EDIT_FILE_PATH, m_strFilePath);
    DDX_Text(pDX, IDC_EDIT_FILE_SIZE, m_dwFileSize);
    DDX_Text(pDX, IDC_EDIT_FILE_VOLUME_ID, m_iFileVolumeID);
    DDX_Text(pDX, IDC_EDIT_UPLOAD_URL, m_strUploadUrl);
    DDX_Text(pDX, IDC_EDIT_SAVE_PATH, m_strSavePath);
    DDX_Check(pDX, IDC_CHECK_UPLOAD_SUBPACKAGE, m_bUploadSubpackage);
    DDX_Check(pDX, IDC_CHECK_DOWNLOAD_DATA_CALLBACK, m_bDownloadDataCallback);
    DDX_Control(pDX, IDC_LIST_FILE_SEARCH, m_listFileSearch);
    DDX_Control(pDX, IDC_LIST_FILE_LOCK, m_listFileLock);
    DDX_Text(pDX, IDC_EDIT_FILE_SEARCH_URL, m_strFileSearchUrl);
    DDX_Text(pDX, IDC_EDIT_FILE_LOCK_URL, m_strFileLockUrl);
    DDX_Text(pDX, IDC_EDIT_UPLOAD_SPEED_TRANSFER, m_iUploadSpeed);
    DDX_Text(pDX, IDC_EDIT_DOWNLOAD_SPEED_TRANSFER, m_iDownloadSpeed);
    DDX_Control(pDX, IDC_COMBO_LOCK_TYPE, m_comboLockType);
    DDX_Text(pDX, IDC_EDIT_LOCK_TIME, m_iLockTime);
    DDX_Check(pDX, IDC_CHECK_ARCHIVE, m_bArchive);
}


BEGIN_MESSAGE_MAP(CDlgCVRDataManage, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_BROWSE, &CDlgCVRDataManage::OnBnClickedButtonBrowse)
    ON_BN_CLICKED(IDC_BUTTON_UPLOAD, &CDlgCVRDataManage::OnBnClickedButtonUpload)
    ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD, &CDlgCVRDataManage::OnBnClickedButtonDownload)
    ON_BN_CLICKED(IDC_BUTTON_SAVE_PATH_BROWSE, &CDlgCVRDataManage::OnBnClickedButtonSavePathBrowse)
    ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CDlgCVRDataManage::OnBnClickedButtonSearch)
    ON_BN_CLICKED(IDC_BUTTON_GET, &CDlgCVRDataManage::OnBnClickedButtonGet)
    ON_BN_CLICKED(IDC_BUTTON_SET, &CDlgCVRDataManage::OnBnClickedButtonSet)
    ON_BN_CLICKED(IDC_BUTTON_ADD, &CDlgCVRDataManage::OnBnClickedButtonAdd)
    ON_BN_CLICKED(IDC_BUTTON_ADD_LOCK, &CDlgCVRDataManage::OnBnClickedButtonAddLock)
    ON_BN_CLICKED(IDC_BUTTON_FILE_LOCK, &CDlgCVRDataManage::OnBnClickedButtonFileLock)
    ON_BN_CLICKED(IDC_BUTTON_DELETE_SEARCH, &CDlgCVRDataManage::OnBnClickedButtonDeleteSearch)
    ON_BN_CLICKED(IDC_BUTTON_DELETE_LOCK, &CDlgCVRDataManage::OnBnClickedButtonDeleteLock)
    ON_NOTIFY(NM_CLICK, IDC_LIST_FILE_SEARCH, &CDlgCVRDataManage::OnNMClickListFileSearch)
    ON_NOTIFY(NM_CLICK, IDC_LIST_FILE_LOCK, &CDlgCVRDataManage::OnNMClickListFileLock)
END_MESSAGE_MAP()


// CDlgCVRDataManage 消息处理程序

BOOL CDlgCVRDataManage::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化

    char szLan[128] = { 0 };
    m_listFileSearch.SetExtendedStyle(m_listFileSearch.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES);

    g_StringLanType(szLan, "序号", "Index");
    m_listFileSearch.InsertColumn(0, szLan, LVCFMT_LEFT, 60, -1);

    g_StringLanType(szLan, "url", "url");
    m_listFileSearch.InsertColumn(1, szLan, LVCFMT_LEFT, 240, -1);

    g_StringLanType(szLan, "文件是否存在", "File exist");
    m_listFileSearch.InsertColumn(2, szLan, LVCFMT_LEFT, 60, -1);

    g_StringLanType(szLan, "文件大小", "File size");
    m_listFileSearch.InsertColumn(3, szLan, LVCFMT_LEFT, 80, -1);

    g_StringLanType(szLan, "文件是否加锁", "File lock");
    m_listFileSearch.InsertColumn(4, szLan, LVCFMT_LEFT, 60, -1);

    g_StringLanType(szLan, "距离自动解锁文件时间", "Unlock time");
    m_listFileSearch.InsertColumn(5, szLan, LVCFMT_LEFT, 120, -1);


    m_listFileLock.SetExtendedStyle(m_listFileLock.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES);

    g_StringLanType(szLan, "序号", "Index");
    m_listFileLock.InsertColumn(0, szLan, LVCFMT_LEFT, 60, -1);

    g_StringLanType(szLan, "url", "url");
    m_listFileLock.InsertColumn(1, szLan, LVCFMT_LEFT, 240, -1);

    g_StringLanType(szLan, "控制命令", "Command");
    m_listFileLock.InsertColumn(2, szLan, LVCFMT_LEFT, 80, -1);

    g_StringLanType(szLan, "加锁时间", "Lock time");
    m_listFileLock.InsertColumn(3, szLan, LVCFMT_LEFT, 80, -1);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}


void CDlgCVRDataManage::OnBnClickedButtonBrowse()
{
    // TODO:  在此添加控件通知处理程序代码
    char szLan[128] = { 0 };
    static char szFilter[] = "All File(*.*)|*.*||";
    CFileDialog dlg(TRUE, "*.*", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
    if (dlg.DoModal() == IDOK)
    {
        m_strFilePath = dlg.GetPathName();
        m_strFileName = dlg.GetFileName();
        CFile cFile;
        if (!cFile.Open(m_strFilePath, CFile::modeRead))
        {
            g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
            AfxMessageBox(szLan);
        }
        m_dwFileSize = (DWORD)cFile.GetLength();
        cFile.Close();
        UpdateData(FALSE);
    }
}

DWORD WINAPI CDlgCVRDataManage::GetUpLoadDataThread(LPVOID pParam)
{
    CDlgCVRDataManage *pThis = (CDlgCVRDataManage*)pParam;

    DWORD dwState = 0;
    DWORD dwProgress = 0;
    char szLan[256] = { 0 };


    while (TRUE)
    {
        dwState = NET_DVR_GetUploadState(pThis->m_lUploadHandle, &dwProgress);
        if (dwState == 1)
        {
            g_StringLanType(szLan, "上传成功", "Upload successfully");
            pThis->GetDlgItem(IDC_STATIC_UPLOAD_STATUC)->SetWindowText(szLan);
            pThis->m_bUpLoading = FALSE;
            g_StringLanType(szLan, "上传", "Upload");
            pThis->GetDlgItem(IDC_BUTTON_UPLOAD)->SetWindowText(szLan);
            pThis->m_bUpLoading = FALSE;

            NET_DVR_UPLOAD_FILE_RET struUploadFileRet = { 0 };
            if (NET_DVR_GetUploadResult(pThis->m_lUploadHandle, &struUploadFileRet, sizeof(struUploadFileRet)))
            {
                CString strUrl;
                strUrl.Format(_T("%s"), struUploadFileRet.sUrl);
                pThis->GetDlgItem(IDC_EDIT_UPLOAD_URL)->SetWindowText(strUrl);
            }
            else
            {
                AfxMessageBox("NET_DVR_GetUploadResult Failed");
            }
            break;
        }
        else if (dwState == 2)
        {
            g_StringLanType(szLan, "正在上传,已上传:", "Is uploading,progress:");
            sprintf(szLan, "%s%d", szLan, dwProgress);
            pThis->GetDlgItem(IDC_STATIC_UPLOAD_STATUC)->SetWindowText(szLan);
        }
        else if (dwState == 3)
        {
            g_StringLanType(szLan, "上传失败", "Upload failed");
            pThis->GetDlgItem(IDC_STATIC_UPLOAD_STATUC)->SetWindowText(szLan);
            break;
        }
        else if (dwState == 4)
        {
            if (dwProgress == 100)
            {
                g_StringLanType(szLan, "上传成功", "Upload successfully");
                pThis->GetDlgItem(IDC_STATIC_UPLOAD_STATUC)->SetWindowText(szLan);
                g_StringLanType(szLan, "上传", "UpLoad");
                pThis->GetDlgItem(IDC_BUTTON_UPLOAD)->SetWindowText(szLan);
                pThis->m_bUpLoading = FALSE;
                break;
            }
            else
            {
                g_StringLanType(szLan, "网络断开，状态未知", "Network disconnect, status unknown");
                pThis->GetDlgItem(IDC_STATIC_UPLOAD_STATUC)->SetWindowText(szLan);
                break;
            }
        }
        if (dwState != 2 && dwState != 5)
        {
            NET_DVR_UploadClose(pThis->m_lUploadHandle);
            pThis->m_bUpLoading = FALSE;
            g_StringLanType(szLan, "上传", "UpLoad");
            pThis->GetDlgItem(IDC_BUTTON_UPLOAD)->SetWindowText(szLan);
            break;
        }
    }

    return FALSE;
}

DWORD WINAPI CDlgCVRDataManage::GetUpLoadSendDataThread(LPVOID pParam)
{
    CDlgCVRDataManage *pThis = (CDlgCVRDataManage*)pParam;

    char szOutPut[512] = { 0 };


    //发送文件内容

    BYTE *pSendData = new BYTE[MAX_BUFFER_LEN];
    DWORD iReadLen = 0;

    while (pThis->m_bUpLoading)
    {
        memset(pSendData, 0, MAX_BUFFER_LEN);

        iReadLen = pThis->m_cSendFile.Read(pSendData, MAX_BUFFER_LEN);

        if (iReadLen <= 0)
        {
            //OutputDebugString("iReadLen==0\n");
            break;
        }
        NET_DVR_SEND_PARAM_IN struSendParamIn = { 0 };
        struSendParamIn.pSendData = pSendData;
        struSendParamIn.dwSendDataLen = iReadLen;

        if (pThis->m_lUploadHandle < 0)
        {
            break;
        }

        int iRet = NET_DVR_UploadSend(pThis->m_lUploadHandle, &struSendParamIn, NULL);
        sprintf(szOutPut, "send %d, iReadLen[%d]\n", iRet, iReadLen);
        OutputDebugString(szOutPut);
        if (iReadLen < MAX_BUFFER_LEN || iRet != iReadLen)
        {
            break;
        }

    }

    pThis->m_cSendFile.Close();
    if (pSendData != NULL)
    {
        delete[] pSendData;
    }


    OutputDebugString("UpLoadSendThread exit \n");
    return FALSE;
}

void CDlgCVRDataManage::OnBnClickedButtonUpload()
{
    // TODO:  在此添加控件通知处理程序代码
    char szLan[128] = { 0 };
    if (m_bUpLoading == FALSE)
    {
        UpdateData(TRUE);
        char szFilePath[MAX_PATH] = { 0 };

        if (m_dwFileSize == 0)
        {
            g_StringLanType(szLan, "文件为空", "File is empty");
            AfxMessageBox(szLan);
            return;
        }

        GetDlgItem(IDC_STATIC_UPLOAD_STATUC)->SetWindowText(szLan);
        memset(&m_struFileVolumeDataInfo, 0, sizeof(m_struFileVolumeDataInfo));
        m_struFileVolumeDataInfo.dwSize = sizeof(m_struFileVolumeDataInfo);
        m_struFileVolumeDataInfo.byFileType = m_comboFileType.GetCurSel();
        m_struFileVolumeDataInfo.byFileVolnumeID = m_iFileVolumeID;
        m_struFileVolumeDataInfo.dwFileSize = m_dwFileSize;
        strncpy(m_struFileVolumeDataInfo.szFileName, m_strFileName, sizeof(m_struFileVolumeDataInfo.szFileName));
        m_struFileVolumeDataInfo.byArchive = m_bArchive;

        if (m_bUploadSubpackage)
        {
            if (m_cSendFile.m_hFile != INVALID_HANDLE_VALUE)
            {
                m_cSendFile.Close();
            }
            if (!m_cSendFile.Open(m_strFilePath, CFile::modeRead))
            {
                g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
                AfxMessageBox(szLan);
                return;
            }
            m_lUploadHandle = NET_DVR_UploadFile_V40(m_lServerID, UPLOAD_FILEVOLUME_DATA, &m_struFileVolumeDataInfo, sizeof(m_struFileVolumeDataInfo), NULL, NULL, 0);
        }
        else
        {
            strcpy(szFilePath, m_strFilePath);
            m_lUploadHandle = NET_DVR_UploadFile_V40(m_lServerID, UPLOAD_FILEVOLUME_DATA, &m_struFileVolumeDataInfo, sizeof(m_struFileVolumeDataInfo), szFilePath, NULL, 0);
        }


        if (m_lUploadHandle < 0)
        {
            g_StringLanType(szLan, "数据上传失败", "UPLOAD_PICTURE_FILE Upload Failed");
            sprintf(szLan, "%s %s %d", szLan, NET_DVR_GetErrorMsg(), NET_DVR_GetLastError());
            AfxMessageBox(szLan);
            return;
        }

        m_bUpLoading = TRUE;

        if (m_bUploadSubpackage)
        {
            m_hUpLoadSendThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetUpLoadSendDataThread), this, 0, &m_dwSendThreadId);
            if (m_hUpLoadSendThread == NULL)
            {
                m_bUpLoading = FALSE;
                g_StringLanType(szLan, "打开发送文件线程失败!", "open UpLoad thread Fail!");
                AfxMessageBox(szLan);
                return;
            }
        }

        m_hUpLoadThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetUpLoadDataThread), this, 0, &m_dwThreadId);
        if (m_hUpLoadThread == NULL)
        {
            m_bUpLoading = FALSE;
            g_StringLanType(szLan, "打开长传文件线程失败!", "open UpLoad thread Fail!");
            AfxMessageBox(szLan);
            return;
        }

        g_StringLanType(szLan, "停止上传", "Stop UpLoad");
        GetDlgItem(IDC_BUTTON_UPLOAD)->SetWindowText(szLan);
    }
    else
    {
        NET_DVR_UploadClose(m_lUploadHandle);
        m_lUploadHandle = -1;
        m_bUpLoading = FALSE;
        g_StringLanType(szLan, "上传", "UpLoad");
        GetDlgItem(IDC_BUTTON_UPLOAD)->SetWindowText(szLan);
    }
    UpdateData(FALSE);
}

BOOL fDownloadDataFile(LONG lHandle, NET_DOWNLOAD_CB_INFO *pCBInfo, void *pUserData)
{
    CDlgCVRDataManage* pThis = (CDlgCVRDataManage*)pUserData;

    char szLan[128] = { 0 };

    if (pThis->m_cRecvFile == CFile::hFileNull)
    {
        if (!pThis->m_cRecvFile.Open(pThis->m_strSavePath, CFile::modeCreate | CFile::modeWrite))
        {
            g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
            AfxMessageBox(szLan);
            return FALSE;
        }
    }
    pThis->m_cRecvFile.Write(pCBInfo->pData, pCBInfo->dwDataLen);

    return TRUE;
}

DWORD GetDownloadDataFileThread(LPVOID pParam)
{
    CDlgCVRDataManage *pThis = (CDlgCVRDataManage*)pParam;

    DWORD dwState = 0;
    DWORD dwProgress = 0;
    char szLan[256] = { 0 };

    while (TRUE)
    {
        dwState = NET_DVR_GetDownloadState(pThis->m_lDownloadHandle, &dwProgress);
        if (dwState == 1)
        {
            g_StringLanType(szLan, "下载成功", "Download successfully");
            pThis->GetDlgItem(IDC_STATIC_DOWNLOAD_STATUC)->SetWindowText(szLan);
            pThis->m_bDownLoading = FALSE;
            g_StringLanType(szLan, "下载", "Download");
            pThis->GetDlgItem(IDC_BUTTON_DOWNLOAD)->SetWindowText(szLan);
            pThis->m_bDownLoading = FALSE;
            break;
        }
        else if (dwState == 2)
        {
            g_StringLanType(szLan, "正在下载,已下载:", "Is Downloading,progress:");
            sprintf(szLan, "%s%d", szLan, dwProgress);
            pThis->GetDlgItem(IDC_STATIC_DOWNLOAD_STATUC)->SetWindowText(szLan);
        }
        else if (dwState == 3)
        {
            g_StringLanType(szLan, "下载失败", "Download failed");
            pThis->GetDlgItem(IDC_STATIC_DOWNLOAD_STATUC)->SetWindowText(szLan);
            break;
        }
        else if (dwState == 4)
        {
            if (dwProgress == 100)
            {
                g_StringLanType(szLan, "下载成功", "Download successfully");
                pThis->GetDlgItem(IDC_STATIC_DOWNLOAD_STATUC)->SetWindowText(szLan);
                g_StringLanType(szLan, "下载", "DownLoad");
                pThis->GetDlgItem(IDC_BUTTON_DOWNLOAD)->SetWindowText(szLan);
                pThis->m_bDownLoading = FALSE;
                break;
            }
            else
            {
                g_StringLanType(szLan, "网络断开，状态未知", "Network disconnect, status unknown");
                pThis->GetDlgItem(IDC_STATIC_DOWNLOAD_STATUC)->SetWindowText(szLan);
                break;
            }
        }

        if (dwState != 2 && dwState != 5)
        {
            NET_DVR_StopDownload(pThis->m_lDownloadHandle);
            pThis->m_bDownLoading = FALSE;
            g_StringLanType(szLan, "下载", "Download");
            pThis->GetDlgItem(IDC_BUTTON_DOWNLOAD)->SetWindowText(szLan);
            break;
        }
    }

    if (pThis->m_cRecvFile != CFile::hFileNull)
    {
        pThis->m_cRecvFile.Close();
    }

    return FALSE;
}

void CDlgCVRDataManage::OnBnClickedButtonDownload()
{
    // TODO:  在此添加控件通知处理程序代码
    char szLan[128] = { 0 }, szSavePath[1024] = { 0 };
    if (m_bDownLoading == FALSE)
    {
        UpdateData(TRUE);
        GetDlgItem(IDC_STATIC_DOWNLOAD_STATUC)->SetWindowText(szLan);

        memset(&m_struFileVolumeDataParam, 0, sizeof(m_struFileVolumeDataParam));
        m_struFileVolumeDataParam.dwSize = sizeof(m_struFileVolumeDataParam);
        strncpy((char*)m_struFileVolumeDataParam.sUrl, m_strDownloadUrl, sizeof(m_struFileVolumeDataParam.sUrl));

        if (m_bDownloadDataCallback)
        {
            m_struFileVolumeDataParam.fnDownloadDataCB = fDownloadDataFile;
            m_struFileVolumeDataParam.pUserData = this;
            m_lDownloadHandle = NET_DVR_StartDownload(m_lServerID, NET_SDK_DOWNLOAD_FILEVOLUME_DATA, &m_struFileVolumeDataParam, sizeof(m_struFileVolumeDataParam), NULL);
        }
        else
        {
            sprintf(szSavePath, "%s", m_strSavePath);
            m_struFileVolumeDataParam.fnDownloadDataCB = NULL;
            m_struFileVolumeDataParam.pUserData = NULL;
            m_lDownloadHandle = NET_DVR_StartDownload(m_lServerID, NET_SDK_DOWNLOAD_FILEVOLUME_DATA, &m_struFileVolumeDataParam, sizeof(m_struFileVolumeDataParam), szSavePath);
        }

        if (m_lDownloadHandle < 0)
        {
            NET_DVR_StopDownloadFile(m_lDownloadHandle);
            AfxMessageBox("NET_SDK_DOWNLOAD_DATA_FILE Download Failed");
            return;
        }

        DWORD dwThreadId = 0;
        m_hDownloadThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetDownloadDataFileThread), this, 0, &dwThreadId);
        if (m_hDownloadThread == NULL)
        {
            char szLan[256] = { 0 };
            g_StringLanType(szLan, "打开下载文件线程失败!", "open DownLoad thread Fail!");
            AfxMessageBox(szLan);
            return;
        }
        g_StringLanType(szLan, "停止下载", "Stop DownLoad");
        GetDlgItem(IDC_BUTTON_DOWNLOAD)->SetWindowText(szLan);
        m_bDownLoading = TRUE;
    }
    else
    {
        NET_DVR_StopDownload(m_lDownloadHandle);
        m_bDownLoading = FALSE;
        g_StringLanType(szLan, "下载", "DownLoad");
        GetDlgItem(IDC_BUTTON_DOWNLOAD)->SetWindowText(szLan);
    }
    UpdateData(FALSE);
}

CString BrowseFolderPage(HWND hWnd, LPCTSTR lpTitle)
{

    char szPath[MAX_PATH] = { 0 };
    BROWSEINFO m_bi;

    m_bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
    m_bi.hwndOwner = hWnd;
    m_bi.pidlRoot = NULL;
    m_bi.lpszTitle = lpTitle;
    m_bi.lpfn = NULL;
    m_bi.lParam = NULL;
    m_bi.pszDisplayName = szPath;

    LPITEMIDLIST pidl = ::SHBrowseForFolder(&m_bi);
    if (pidl)
    {
        if (!::SHGetPathFromIDList(pidl, szPath))
        {
            szPath[0] = 0;
        }

        IMalloc * pMalloc = NULL;
        if (SUCCEEDED(::SHGetMalloc(&pMalloc)))  // 取得IMalloc分配器接口
        {
            pMalloc->Free(pidl);    // 释放内存
            pMalloc->Release();       // 释放接口
        }
    }
    return szPath;
}

void CDlgCVRDataManage::OnBnClickedButtonSavePathBrowse()
{
    // TODO:  在此添加控件通知处理程序代码
    CString strFilePath = _T("");
    strFilePath = BrowseFolderPage(this->m_hWnd, "选择目录");
    if (strFilePath.IsEmpty())
    {
        MessageBox("保存文件路径不能为空");
        return;
    }
    m_strSavePath = strFilePath + _T("\\") +m_strFileName;
    GetDlgItem(IDC_EDIT_SAVE_PATH)->SetWindowText(m_strSavePath);
}

BOOL CDlgCVRDataManage::CreateTransferSpeedCfg(char* pBuf, DWORD dwBufLen, int &dwRet)
{
    CString strParam = _T("");
    CXmlBase xmlBase;
    xmlBase.CreateRoot("TransferSpeedConfiguration");
    xmlBase.SetAttribute("version", "2.0");
    strParam.Format("%d", m_iUploadSpeed);
    xmlBase.AddNode("uploadSpeed", strParam.GetBuffer(0));
    xmlBase.OutOfElem();
    strParam.Format("%d", m_iDownloadSpeed);
    xmlBase.AddNode("downloadSpeed", strParam.GetBuffer(0));
    xmlBase.OutOfElem();

    return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}

void CDlgCVRDataManage::OnBnClickedButtonGet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    char szUrl[256] = { 0 };
    sprintf(szUrl, "GET /ISAPI/ContentMgmt/FileData/TransferSpeedConfiguration\r\n");

    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    DWORD dwOutputLen = 1024 * 1024;
    char *pOutBuf = new char[dwOutputLen];
    memset(pOutBuf, 0, dwOutputLen);
    struOuput.lpOutBuffer = pOutBuf;
    struOuput.dwOutBufferSize = dwOutputLen;

    if (!NET_DVR_STDXMLConfig(m_lServerID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_lDeviceIndex, OPERATION_FAIL_T, szUrl);
        delete[]pOutBuf;
        pOutBuf = NULL;
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_lDeviceIndex, OPERATION_SUCC_T, szUrl);
    }

    BOOL bRet = FALSE;
    CXmlBase xmlBase;
    xmlBase.Parse(pOutBuf);
    if (xmlBase.FindElem("TransferSpeedConfiguration") && xmlBase.IntoElem())
    {
        if (xmlBase.FindElem("uploadSpeed"))
        {
            m_iUploadSpeed = atoi(xmlBase.GetData().c_str());
        }

        if (xmlBase.FindElem("downloadSpeed"))
        {
            m_iDownloadSpeed = atoi(xmlBase.GetData().c_str());
        }

        xmlBase.OutOfElem();
    }

    if (pOutBuf != NULL)
    {
        delete[]pOutBuf;
        pOutBuf = NULL;
    }

    UpdateData(FALSE);
    return;
}


void CDlgCVRDataManage::OnBnClickedButtonSet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    DWORD dwBufLen = 10 * 1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);
    int dwXmlLen = 0;
    if (!CreateTransferSpeedCfg(pBuf, dwBufLen, dwXmlLen))
    {
        delete[]pBuf;
        pBuf = NULL;
        return;
    }

    char szUrl[256] = { 0 };
    sprintf(szUrl, "PUT /ISAPI/ContentMgmt/FileData/TransferSpeedConfiguration\r\n");
    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    struInput.lpInBuffer = pBuf;
    struInput.dwInBufferSize = dwXmlLen;
    if (!NET_DVR_STDXMLConfig(m_lServerID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_lDeviceIndex, OPERATION_FAIL_T, szUrl);
    }
    else
    {
        g_pMainDlg->AddLog(m_lDeviceIndex, OPERATION_SUCC_T, szUrl);
    }

    delete[]pBuf;
    pBuf = NULL;

    UpdateData(FALSE);
}

BOOL CDlgCVRDataManage::CreateSearchFileCondition(char* pBuf, DWORD dwBufLen, int &dwRet)
{
    int iRowCount = m_listFileSearch.GetItemCount();

    CString strParam = _T("");
    CXmlBase xmlBase;
    xmlBase.CreateRoot("SearchFileCondition");
    xmlBase.SetAttribute("version", "2.0");
    xmlBase.AddNode("SearchList");

    for (int i = 0; i < iRowCount; i++)
    {
        xmlBase.AddNode("SearchInfo");
        strParam.Format("%s", m_listFileSearch.GetItemText(i, 1));
        xmlBase.AddNode("url", strParam.GetBuffer(0));
        xmlBase.OutOfElem();
        xmlBase.OutOfElem();
    }
    xmlBase.OutOfElem();

    return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}

void CDlgCVRDataManage::OnBnClickedButtonSearch()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    char szLan[128] = { 0 };

    int iRowCount = m_listFileSearch.GetItemCount();

    DWORD dwBufLen = 10 * 1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);
    int dwXmlLen = 0;
    if (!CreateSearchFileCondition(pBuf, dwBufLen, dwXmlLen))
    {
        delete[]pBuf;
        pBuf = NULL;
        return;
    }

    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    char szUrl[256] = { 0 };
    sprintf(szUrl, "POST /ISAPI/ContentMgmt/FileData/SearchFile\r\n");

    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    struInput.lpInBuffer = pBuf;
    struInput.dwInBufferSize = dwXmlLen;
    DWORD dwOutputLen = 1024 * 1024;
    char *pOutBuf = new char[dwOutputLen];
    memset(pOutBuf, 0, dwOutputLen);
    struOuput.lpOutBuffer = pOutBuf;
    struOuput.dwOutBufferSize = dwOutputLen;

    if (!NET_DVR_STDXMLConfig(m_lServerID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_lDeviceIndex, OPERATION_FAIL_T, szUrl);
        delete[]pOutBuf;
        pOutBuf = NULL;
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_lDeviceIndex, OPERATION_SUCC_T, szUrl);
    }

    BOOL bRet = FALSE;
    CXmlBase xmlBase;
    xmlBase.Parse(pOutBuf);
    if (xmlBase.FindElem("SearchFileResult") && xmlBase.IntoElem())
    {
        if (xmlBase.FindElem("FileList") && xmlBase.IntoElem())
        {
            for (int i = 0; i < iRowCount; i++)
            {
                if (xmlBase.FindElem("FileInfo") && xmlBase.IntoElem())
                {
                    if (xmlBase.FindElem("fileExist"))
                    {
                        if (xmlBase.GetData().compare("true") == 0)
                        {
                            g_StringLanType(szLan, "存在", "true");
                        }
                        else if (xmlBase.GetData().compare("false") == 0)
                        {
                            g_StringLanType(szLan, "不存在", "false");
                        }
                        m_listFileSearch.SetItemText(i, 2, szLan);
                    }
                    if (xmlBase.FindElem("fileSize"))
                    {
                        m_listFileSearch.SetItemText(i, 3, xmlBase.GetData().c_str());
                    }
                    if (xmlBase.FindElem("fileLock"))
                    {
                        if (xmlBase.GetData().compare("lock") == 0)
                        {
                            g_StringLanType(szLan, "锁定", "lock");
                        }
                        else if (xmlBase.GetData().compare("unlock") == 0)
                        {
                            g_StringLanType(szLan, "解锁", "unlock");
                        }
                        m_listFileSearch.SetItemText(i, 4, szLan);
                    }
                    if (xmlBase.FindElem("unlockTime"))
                    {
                        m_listFileSearch.SetItemText(i, 5, xmlBase.GetData().c_str());
                    }
                    else
                    {
                        m_listFileSearch.SetItemText(i, 5, "0");
                    }
                    xmlBase.OutOfElem();
                }
                xmlBase.NextSibElem();
            }
            xmlBase.OutOfElem();
        }
        xmlBase.OutOfElem();
    }

    if (pOutBuf != NULL)
    {
        delete[]pOutBuf;
        pOutBuf = NULL;
    }

    if (pBuf != NULL)
    {
        delete[]pBuf;
        pBuf = NULL;
    }

    UpdateData(FALSE);
    return;
}

void CDlgCVRDataManage::OnBnClickedButtonAdd()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    int iRowCount = m_listFileSearch.GetItemCount();
    CString strTemp = _T("");
    strTemp.Format("%d", iRowCount);
    m_listFileSearch.InsertItem(iRowCount, strTemp);
    m_listFileSearch.SetItemText(iRowCount, 1, m_strFileSearchUrl);
    UpdateData(FALSE);
}

void CDlgCVRDataManage::OnBnClickedButtonDeleteSearch()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    m_iRowCount = m_listFileSearch.GetItemCount();
    if (m_iLastItem >= 0 && m_iLastItem < m_iRowCount)
    {
        m_listFileSearch.DeleteItem(m_iLastItem);
    }
    UpdateData(FALSE);
}

void CDlgCVRDataManage::OnNMClickListFileSearch(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // TODO:  在此添加控件通知处理程序代码

    m_iLastItem = pNMItemActivate->iItem;
    m_iSubItem = pNMItemActivate->iSubItem;
    m_bSelectItem = TRUE;

    *pResult = 0;
}

void CDlgCVRDataManage::OnBnClickedButtonAddLock()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    char szLan[128] = { 0 };
    int iRowCount = m_listFileLock.GetItemCount();
    CString strTemp = _T("");
    strTemp.Format("%d", iRowCount);
    m_listFileLock.InsertItem(iRowCount, strTemp);
    m_listFileLock.SetItemText(iRowCount, 1, m_strFileLockUrl);
    if (0 == m_comboLockType.GetCurSel())
    {
        g_StringLanType(szLan, "加锁", "lock");
        m_listFileLock.SetItemText(iRowCount, 2, szLan);
    }
    else if (1 == m_comboLockType.GetCurSel())
    {
        g_StringLanType(szLan, "解锁", "unlock");
        m_listFileLock.SetItemText(iRowCount, 2, szLan);
    }
    strTemp.Format("%d", m_iLockTime);
    m_listFileLock.SetItemText(iRowCount, 3, strTemp);
    UpdateData(FALSE);
}

BOOL CDlgCVRDataManage::CreateLockConfiguration(char* pBuf, DWORD dwBufLen, int &dwRet)
{
    int iRowCount = m_listFileLock.GetItemCount();

    CString strParam = _T("");
    CXmlBase xmlBase;
    xmlBase.CreateRoot("LockConfiguration");
    xmlBase.SetAttribute("version", "2.0");
    xmlBase.AddNode("LockList");

    for (int i = 0; i < iRowCount; i++)
    {
        xmlBase.AddNode("LockInfo");

        strParam.Format("%d", iRowCount);
        xmlBase.AddNode("id", strParam.GetBuffer(0));
        xmlBase.OutOfElem();

        strParam.Format("%s", m_listFileLock.GetItemText(i, 1));
        xmlBase.AddNode("url", strParam.GetBuffer(0));
        xmlBase.OutOfElem();

        strParam.Format("%s", m_listFileLock.GetItemText(i, 2));
        if (strParam == _T("加锁") || strParam == _T("lock"))
        {
            xmlBase.AddNode("command", "lock");
        }
        else if (strParam == _T("解锁") || strParam == _T("unlock"))
        {
            xmlBase.AddNode("command", "unlock");
        }
        xmlBase.OutOfElem();

        strParam.Format("%s", m_listFileLock.GetItemText(i, 3));
        xmlBase.AddNode("duration", strParam.GetBuffer(0));
        xmlBase.OutOfElem();

        xmlBase.OutOfElem();
    }
    xmlBase.OutOfElem();

    return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}

void CDlgCVRDataManage::OnBnClickedButtonFileLock()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    DWORD dwBufLen = 10 * 1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);
    int dwXmlLen = 0;
    if (!CreateLockConfiguration(pBuf, dwBufLen, dwXmlLen))
    {
        delete[]pBuf;
        pBuf = NULL;
        return;
    }

    char szUrl[256] = { 0 };
    sprintf(szUrl, "PUT /ISAPI/ContentMgmt/FileData/LockConfiguration\r\n");
    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    struInput.lpInBuffer = pBuf;
    struInput.dwInBufferSize = dwXmlLen;
    if (!NET_DVR_STDXMLConfig(m_lServerID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_lDeviceIndex, OPERATION_FAIL_T, szUrl);
    }
    else
    {
        g_pMainDlg->AddLog(m_lDeviceIndex, OPERATION_SUCC_T, szUrl);
    }

    delete[]pBuf;
    pBuf = NULL;

    UpdateData(FALSE);
}

void CDlgCVRDataManage::OnBnClickedButtonDeleteLock()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    m_iRowCountLock = m_listFileLock.GetItemCount();
    if (m_iLastItemLock >= 0 && m_iLastItemLock < m_iRowCountLock)
    {
        m_listFileLock.DeleteItem(m_iLastItemLock);
    }
    UpdateData(FALSE);
}



void CDlgCVRDataManage::OnNMClickListFileLock(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // TODO:  在此添加控件通知处理程序代码

    m_iLastItemLock = pNMItemActivate->iItem;
    m_iSubItemLock = pNMItemActivate->iSubItem;
    m_bSelectItemLock = TRUE;

    *pResult = 0;
}
