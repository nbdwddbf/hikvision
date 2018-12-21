// DlgLEDCheckCond.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgLEDCheckCond.h"
#include "afxdialogex.h"


// CDlgLEDCheckCond 对话框

IMPLEMENT_DYNAMIC(CDlgLEDCheckCond, CDialogEx)

CDlgLEDCheckCond::CDlgLEDCheckCond(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgLEDCheckCond::IDD, pParent)
    , m_dwNo(0)
    , m_szUploadFile(_T(""))
    , m_szDownloadFile(_T(""))
    , m_szProgress(_T(""))
	, m_iStartPosColumn(0)
	, m_iStartPosLine(0)
    , m_iStartType(0)
    , m_dwX(0)
    , m_dwY(0)
    , m_dwW(0)
    , m_dwH(0)
{
   
    m_lUpDownloadHandle = -1;
    m_bDownloading = FALSE;
    m_bUploading = FALSE;
    m_dwFileLength = 0;
    memset(&m_struCheckCond, 0, sizeof(m_struCheckCond));
    m_struCheckCond.dwSize = sizeof(m_struCheckCond);

}

CDlgLEDCheckCond::~CDlgLEDCheckCond()
{
}

void CDlgLEDCheckCond::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_NO, m_dwNo);
    DDX_Text(pDX, IDC_EDIT_CHECK_UPLOAD, m_szUploadFile);
    DDX_Text(pDX, IDC_EDIT_DOWNLOAD, m_szDownloadFile);
    DDX_Control(pDX, IDC_PROGRESS1, m_CtrlProgress);
    DDX_Text(pDX, IDC_STATIC_PROGRESS, m_szProgress);
    DDX_Control(pDX, IDC_STATIC_PROGRESS, m_StaticProgress);
    DDX_Text(pDX, IDC_EDIT_STARTPOS_COLUMN, m_iStartPosColumn);
    DDX_Text(pDX, IDC_EDIT_STARTPOS_LINE, m_iStartPosLine);
    DDX_CBIndex(pDX, IDC_COMBO_Start, m_iStartType);
    DDX_Text(pDX, IDC_EDIT_X, m_dwX);
    DDX_Text(pDX, IDC_EDIT_Y, m_dwY);
    DDX_Text(pDX, IDC_EDIT_W, m_dwW);
    DDX_Text(pDX, IDC_EDIT1_H, m_dwH);
}


BEGIN_MESSAGE_MAP(CDlgLEDCheckCond, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_UPLOAD_SCAN, &CDlgLEDCheckCond::OnBnClickedBtnUploadScan)
    ON_BN_CLICKED(IDC_BTN_DOWNLOAD_SCAN, &CDlgLEDCheckCond::OnBnClickedBtnDownloadScan)
    ON_BN_CLICKED(IDC_BTN_UPLOAD, &CDlgLEDCheckCond::OnBnClickedBtnUpload)
    ON_BN_CLICKED(IDC_BTN_CHECK_DOWNALOD, &CDlgLEDCheckCond::OnBnClickedBtnCheckDownalod)
    ON_WM_TIMER()
END_MESSAGE_MAP()


// CDlgLEDCheckCond 消息处理程序


void CDlgLEDCheckCond::OnBnClickedBtnUploadScan()
{
    // TODO:  在此添加控件通知处理程序代码
    CString strFilter;
    CFileDialog fileChose(TRUE, NULL, NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
    if (fileChose.DoModal() != IDOK)
    {
        return;
    }
    m_szUploadFile = fileChose.GetPathName();
    CFile file;
    if (!file.Open(m_szUploadFile, CFile::modeRead))
    {
        char szLan1[512] = { 0 };
        char szLan2[512] = { 0 };
        g_StringLanType(szLan1, "打开文件失败", "Open file fail");
        g_StringLanType(szLan2, "LED校正导入导出配置", "LED check upload download config");
        MessageBox(szLan1, szLan2, MB_ICONWARNING);
        return;
    }
    m_dwFileLength = file.GetLength();
    file.Close();
    GetDlgItem(IDC_EDIT_CHECK_UPLOAD)->SetWindowText(m_szUploadFile);
}


void CDlgLEDCheckCond::OnBnClickedBtnDownloadScan()
{
    // TODO:  在此添加控件通知处理程序代码
    CString strFilter = _T("All Files(*.*)|*.*||");
    CFileDialog fileChose(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
    if (fileChose.DoModal() != IDOK)
    {
        return;
    }
    m_szDownloadFile = fileChose.GetPathName();
    GetDlgItem(IDC_EDIT_DOWNLOAD)->SetWindowText(m_szDownloadFile);
    
}


void CDlgLEDCheckCond::OnBnClickedBtnUpload()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    memset(&m_struCheckCond, 0, sizeof(m_struCheckCond));
    m_struCheckCond.dwSize = sizeof(m_struCheckCond);
    m_struCheckCond.dwOutputNo = m_dwNo;

    m_struCheckCond.byStartPosType = m_iStartType;
    if (m_iStartType == 0)
    {
        m_struCheckCond.struPosStart.wColumn = (WORD)m_iStartPosColumn;
        m_struCheckCond.struPosStart.wLine = (WORD)m_iStartPosLine;
    }
    else
    {
        m_struCheckCond.dwXCoordinate = m_dwX;
        m_struCheckCond.dwYCoordinate = m_dwY;
    }


    if (m_bDownloading || m_bUploading)
    {
        return;
    }
    DWORD dwIndex = 0;
	m_lUpDownloadHandle = NET_DVR_UploadFile_V40(m_lUserID, UPLOAD_LED_CHECK_FILE, &m_struCheckCond, sizeof(m_struCheckCond), m_szUploadFile.GetBuffer(0), NULL, 0);
    if (m_lUpDownloadHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadFile_V40 UPLOAD_DOOR_CONTENT");
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadFile_V40 UPLOAD_DOOR_CONTENT");

    m_bUploading = TRUE;
    m_CtrlProgress.SetPos(0);
    m_StaticProgress.SetWindowText(_T("0%"));
    SetTimer(TIMER_UPDOWNLOAD_CONFIG_PROGRESS, 100, NULL);
    UpdateData(FALSE);
}


void CDlgLEDCheckCond::OnBnClickedBtnCheckDownalod()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    memset(&m_struCheckCond, 0, sizeof(m_struCheckCond));
    m_struCheckCond.dwSize = sizeof(m_struCheckCond);
    m_struCheckCond.dwOutputNo = m_dwNo;
    m_struCheckCond.byStartPosType = m_iStartType;

    if (m_iStartType == 0)
    {
        m_struCheckCond.struPosStart.wColumn = (WORD)m_iStartPosColumn;
        m_struCheckCond.struPosStart.wLine = (WORD)m_iStartPosLine;
    }
    else
    {
        m_struCheckCond.dwXCoordinate = m_dwX;
        m_struCheckCond.dwYCoordinate = m_dwY;
    }


    m_struCheckCond.dwHeight = m_dwH;
    m_struCheckCond.dwWidth = m_dwW;

    if (m_bUploading || m_bDownloading)
    {
        return;
    }

    WIN32_FIND_DATA  FindFileData;
    HANDLE hFind;
    hFind = FindFirstFile(m_szDownloadFile.GetBuffer(0), &FindFileData);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        printf("Invalid File Handle. Get Last Error reports %d ", GetLastError());
    }
    else
    {
        printf("The first file found is %s ", FindFileData.cFileName);
        FindClose(hFind);
        DeleteFile(m_szDownloadFile.GetBuffer(0));
    }

    m_lUpDownloadHandle = NET_DVR_StartDownload(m_lUserID, NET_SDK_DOWNLOAD_LED_CHECK_FILE, &m_struCheckCond, sizeof(m_struCheckCond), m_szDownloadFile.GetBuffer(0));
    if (m_lUpDownloadHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartDownload NET_SDK_DOWNLOAD_DOOR_CONTENT");
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StartDownload NET_SDK_DOWNLOAD_DOOR_CONTENT");
    m_bDownloading = TRUE;
    m_CtrlProgress.SetPos(0);
    m_StaticProgress.SetWindowText(_T("0%"));
    SetTimer(TIMER_UPDOWNLOAD_CONFIG_PROGRESS, 100, NULL);
}


BOOL CDlgLEDCheckCond::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;

    m_CtrlProgress.SetRange(0, 100);
    m_CtrlProgress.SetStep(1);
    m_CtrlProgress.SetPos(0);
    //m_szProgress = "0%";
    m_StaticProgress.SetWindowText(_T("0%"));
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}


void CDlgLEDCheckCond::OnTimer(UINT_PTR nIDEvent)
{
    // TODO:  在此添加消息处理程序代码和/或调用默认值
    if (nIDEvent == TIMER_UPDOWNLOAD_CONFIG_PROGRESS)
    {
        DWORD dwProgress = 0;
        LONG lStatus = -1;
        if (m_bUploading)
        {
            lStatus = NET_DVR_GetUploadState(m_lUpDownloadHandle, &dwProgress);
            if (lStatus == -1)
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetUploadState");
                if (!NET_DVR_UploadClose(m_lUpDownloadHandle))
                {
                    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadClose");
                }
                else
                {
                    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadClose");
                }
            }
            else
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetUploadState");
            }
        }
        else if (m_bDownloading)
        {
            lStatus = NET_DVR_GetDownloadState(m_lUpDownloadHandle, &dwProgress);
            if (lStatus == -1)
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetDownloadState");
                if (!NET_DVR_StopDownload(m_lUpDownloadHandle))
                {
                    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopDownload");
                }
                else
                {
                    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopDownload");
                }
            }
            else
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetDownloadState");
            }
        }
        switch (lStatus)
        {
        case 1: //上传或下载成功
        {
                    m_CtrlProgress.SetPos(dwProgress);
                    CString str;
                    str.Format("%d", dwProgress);
                    str += _T("%");
                    m_StaticProgress.SetWindowText(str);
                    if (m_bUploading)
                    {
                        if (!NET_DVR_UploadClose(m_lUpDownloadHandle))
                        {
                            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadClose");
                        }
                        else
                        {
                            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadClose");
                        }
                        m_bUploading = FALSE;
                    }
                    else if (m_bDownloading)
                    {
                        if (!NET_DVR_StopDownload(m_lUpDownloadHandle))
                        {
                            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopDownload");
                        }
                        else
                        {
                            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopDownload");
                        }
                        m_bDownloading = FALSE;
                    }
                    m_lUpDownloadHandle = -1;
                    KillTimer(TIMER_UPDOWNLOAD_CONFIG_PROGRESS);
                    char sTitle[64] = { 0 };
                    char sMsg[64] = { 0 };
                    g_StringLanType(sTitle, "LED校正导入导出配置", "LED check config");
                    g_StringLanType(sMsg, "上传/下载完成", "Upload/Download finished.");
                    MessageBox(sMsg, sTitle, MB_OK | MB_ICONWARNING);
                    break;
        }
        case 2: //正在上传或下载
        {
                    m_CtrlProgress.SetPos(dwProgress);
                    CString str;
                    str.Format("%d", dwProgress);
                    str += _T("%");
                    m_StaticProgress.SetWindowText(str);
                    break;
        }
        case 3: //上传或下载失败
        {
                    if (m_bUploading)
                    {
                        if (!NET_DVR_UploadClose(m_lUpDownloadHandle))
                        {
                            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadClose");
                        }
                        else
                        {
                            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadClose");
                        }
                        m_bUploading = FALSE;
                    }
                    else if (m_bDownloading)
                    {
                        if (!NET_DVR_StopDownload(m_lUpDownloadHandle))
                        {
                            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopDownload");
                        }
                        else
                        {
                            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopDownload");
                        }
                        m_bDownloading = FALSE;
                    }
                    m_lUpDownloadHandle = -1;
                    KillTimer(TIMER_UPDOWNLOAD_CONFIG_PROGRESS);
                    char sTitle[64] = { 0 };
                    char sMsg[64] = { 0 };
                    g_StringLanType(sTitle, "LED校正导入导出配置", "LED check config");
                    g_StringLanType(sMsg, "上传/下载失败", "Upload/Download failed.");
                    MessageBox(sMsg, sTitle, MB_OK | MB_ICONWARNING);
                    break;
        }
        case 4: //网络断开
        {
                    if (m_bUploading)
                    {
                        if (!NET_DVR_UploadClose(m_lUpDownloadHandle))
                        {
                            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadClose");
                        }
                        else
                        {
                            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadClose");
                        }
                        m_bUploading = FALSE;
                    }
                    else if (m_bDownloading)
                    {
                        if (!NET_DVR_StopDownload(m_lUpDownloadHandle))
                        {
                            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopDownload");
                        }
                        else
                        {
                            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopDownload");
                        }
                        m_bDownloading = FALSE;
                    }
                    m_lUpDownloadHandle = -1;
                    KillTimer(TIMER_UPDOWNLOAD_CONFIG_PROGRESS);
                    char sTitle[64] = { 0 };
                    char sMsg[64] = { 0 };
                    g_StringLanType(sTitle, "LED校正导入导出配置", "LED check config");
                    g_StringLanType(sMsg, "网络断开", "Network disconnection.");
                    MessageBox(sMsg, sTitle, MB_OK | MB_ICONWARNING);
                    break;
        }
        }
    }

    CDialogEx::OnTimer(nIDEvent);
}
