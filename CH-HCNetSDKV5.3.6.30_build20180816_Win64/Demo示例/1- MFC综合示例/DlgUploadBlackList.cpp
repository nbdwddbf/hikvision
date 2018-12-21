// DlgUploadBlackList.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgUploadBlackList.h"
#include "afxdialogex.h"


// CDlgUploadBlackList 对话框

IMPLEMENT_DYNAMIC(CDlgUploadBlackList, CDialogEx)

CDlgUploadBlackList::CDlgUploadBlackList(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgUploadBlackList::IDD, pParent)
    , m_szDowndFilePath(_T(""))
{
    m_lServerID = -1;
    m_iDeviceIndex = -1;
    m_lChannel = 1;
    m_strFilePath = _T("");
    m_iFileSize = 0;
    m_lUploadHandle = -1;
    m_lDownloadHandle = -1;

    m_bUploading = FALSE;
    m_bDownloading = FALSE;
    m_timerHandle = -1;

    m_dwUploadAudioNo = 0;
    m_dwDownloadAudioNo = 0;
}

CDlgUploadBlackList::~CDlgUploadBlackList()
{
}

void CDlgUploadBlackList::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_BLACKLIST_DOWNLOAD_DIR, m_szDowndFilePath);
    DDX_Control(pDX, IDC_PROGRESS1, m_ctrlProgress);
    DDX_Control(pDX, IDC_STATIC_PROGRESS, m_statProgress);
    DDX_Control(pDX, IDC_CMB_UPLOAD, m_cmbUploadType);
    DDX_Control(pDX, IDC_CMB_DOWNLOAD, m_cmbDownLoadType);
    DDX_Text(pDX, IDC_EDIT_UPLOAD_AUDIO_NO, m_dwUploadAudioNo);
    DDX_Text(pDX, IDC_EDIT_DOWNLOAD_AUDIO_NO, m_dwDownloadAudioNo);
}


BEGIN_MESSAGE_MAP(CDlgUploadBlackList, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_GET_FILEPATH, &CDlgUploadBlackList::OnBnClickedBtnGetFilepath)
    ON_BN_CLICKED(IDC_BTN_UPLAOD, &CDlgUploadBlackList::OnBnClickedBtnUplaod)
    ON_BN_CLICKED(IDC_BTN_STOP, &CDlgUploadBlackList::OnBnClickedBtnStop)
    ON_BN_CLICKED(IDC_BTN_EXIT, &CDlgUploadBlackList::OnBnClickedBtnExit)
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_BTN_SET_FILEPATH, &CDlgUploadBlackList::OnBnClickedBtnSetFilepath)
    ON_BN_CLICKED(IDC_BTN_DOWNLOAD, &CDlgUploadBlackList::OnBnClickedBtnDownload)
    ON_CBN_SELCHANGE(IDC_CMB_UPLOAD, &CDlgUploadBlackList::OnCbnSelchangeCmbUpload)
    ON_CBN_SELCHANGE(IDC_CMB_DOWNLOAD, &CDlgUploadBlackList::OnCbnSelchangeCmbDownload)
END_MESSAGE_MAP()


// CDlgUploadBlackList 消息处理程序


void CDlgUploadBlackList::OnBnClickedBtnGetFilepath()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    static char szFilter[] = "All File(*.*)|*.*||";
    CFileDialog dlg(TRUE, "*.*", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
    if (dlg.DoModal() == IDOK)
    {
        m_strFilePath = dlg.GetPathName();
        SetDlgItemText(IDC_EDIT_BLACKLIST_UPLOAD_DIR, m_strFilePath);
    }
    GetDlgItem(IDC_BTN_UPLAOD)->EnableWindow(TRUE);
}


BOOL CDlgUploadBlackList::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    m_ctrlProgress.SetRange(0, 100);
    m_ctrlProgress.SetStep(1);
    m_ctrlProgress.SetPos(0);
    m_statProgress.SetWindowText(_T("0%"));

    m_cmbUploadType.SetCurSel(0);
    m_cmbDownLoadType.SetCurSel(0);

    GetDlgItem(IDC_BTN_UPLAOD)->EnableWindow(FALSE);
    GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);

    GetDlgItem(IDC_STATIC_UPLOAD_AUDIO)->ShowWindow(FALSE);
    GetDlgItem(IDC_EDIT_UPLOAD_AUDIO_NO)->ShowWindow(FALSE);
    GetDlgItem(IDC_STATIC_DOWNLOAD_AUDIO)->ShowWindow(FALSE);
    GetDlgItem(IDC_EDIT_DOWNLOAD_AUDIO_NO)->ShowWindow(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}


void CDlgUploadBlackList::OnBnClickedBtnUplaod()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    if (m_bUploading || m_bDownloading)
    {
        return;
    }
    m_ctrlProgress.SetPos(0);
    char szFileName[MAX_PATH];
    strcpy(szFileName, m_strFilePath);
    CFile cFile;
    char szLan[128] = { 0 };
    if (!cFile.Open(szFileName, NULL))
    {
        g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
        AfxMessageBox(szLan);
        return;
    }
    DWORD dwFileSize = (DWORD)cFile.GetLength();
    if (dwFileSize == 0)
    {
        g_StringLanType(szLan, "文件为空", "Certificate Black list file is empty");
        AfxMessageBox(szLan);
    }
    cFile.Close();

    if (m_cmbUploadType.GetCurSel() == 0)
    {
        m_lUploadHandle = NET_DVR_UploadFile_V40(m_lServerID, UPLOAD_CERTIFICATE_BLACK_LIST, NULL, 0, szFileName, NULL, 0);
        if (-1 == m_lUploadHandle)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadFile_V40 UPLOAD_CERTIFICATE_BLACK_LIST");
            AfxMessageBox("NET_DVR_UploadFile_V40 failed");
            //NET_DVR_UploadClose(m_lUploadHandle);
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText("Upload Certificate Black list Failed!");
        }
        else
        {
            m_bUploading = TRUE;
            m_ctrlProgress.SetPos(0);
            m_statProgress.SetWindowText(_T("0%"));
            GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadFile_V40 UPLOAD_CERTIFICATE_BLACK_LIST");
            m_timerHandle = SetTimer(UPLOAD_BLACK_LIST_TIMER, 100, NULL);
            Sleep(50);
        }
    }
    else if (m_cmbUploadType.GetCurSel() == 1)
    {
        int iAudioNo = m_dwUploadAudioNo;
        if (iAudioNo <1 || iAudioNo >32)
        {
            g_StringLanType(szLan, "音频文件ID无效", "Audio file No is invalid");
            AfxMessageBox(szLan);
            return;
        }
        NET_DVR_RIGHT_CONTROLLER_AUDIO_PARAM struRightControllerAudioParam = { 0 };
        struRightControllerAudioParam.dwSize = sizeof(struRightControllerAudioParam);
        struRightControllerAudioParam.dwFileSize = dwFileSize;
        struRightControllerAudioParam.dwAudioID = iAudioNo;
        m_lUploadHandle = NET_DVR_UploadFile_V40(m_lServerID, UPLOAD_RIGHT_CONTROLLER_AUDIO, &struRightControllerAudioParam, sizeof(struRightControllerAudioParam), szFileName, NULL, 0);
        if (-1 == m_lUploadHandle)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadFile_V40 UPLOAD_RIGHT_CONTROLLER_AUDIO");
            AfxMessageBox("NET_DVR_UploadFile_V40 failed");
            //NET_DVR_UploadClose(m_lUploadHandle);
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText("Upload Right Controller Audio Failed!");
        }
        else
        {
            m_bUploading = TRUE;
            m_ctrlProgress.SetPos(0);
            m_statProgress.SetWindowText(_T("0%"));
            GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadFile_V40 UPLOAD_RIGHT_CONTROLLER_AUDIO");
            m_timerHandle = SetTimer(UPLOAD_BLACK_LIST_TIMER, 100, NULL);
            Sleep(50);
        }
    }
    else
    {
        ;
    }
    UpdateData(FALSE);
}


void CDlgUploadBlackList::OnBnClickedBtnStop()
{
    // TODO:  在此添加控件通知处理程序代码
    KillTimer(UPLOAD_BLACK_LIST_TIMER);
    NET_DVR_UploadClose(m_lUploadHandle);
    NET_DVR_StopDownload(m_lDownloadHandle);
    GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
}

#if (_MSC_VER >= 1500)	//vs2008
void CDlgUploadBlackList::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgUploadBlackList::OnTimer(UINT nIDEvent)
#endif
{
    // TODO: Add your message handler code here and/or call default

    char szLan[128] = { 0 };
    if (nIDEvent == UPLOAD_BLACK_LIST_TIMER)
    {
        DWORD dwProgress = 0;
        if (m_bUploading)
        {
            int state = NET_DVR_GetUploadState(m_lUploadHandle, &dwProgress);

            if (state == 1)
            {
                m_ctrlProgress.SetPos(dwProgress);
                CString str;
                str.Format("%d", dwProgress);
                str += _T("%");
                m_statProgress.SetWindowText(str);
                g_StringLanType(szLan, "上传成功", "Upload successfully");
                // m_strUploadStatus.Format(szLan);
                GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
            }
            else if (state == 2)
            {
                m_ctrlProgress.SetPos(dwProgress);
                CString str;
                str.Format("%d", dwProgress);
                str += _T("%");
                m_statProgress.SetWindowText(str);
                g_StringLanType(szLan, "正在上传,已上传:%d", "Is uploading,progress:%d");

                CString	strUploadStatus;
                strUploadStatus.Format(szLan, dwProgress);
                GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(strUploadStatus);
            }
            else if (state == 3)
            {
                g_StringLanType(szLan, "上传失败", "Upload failed");
                GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
            }
            else if (state == 4)
            {
                g_StringLanType(szLan, "网络断开，状态未知", "Network disconnect, status unknown");
                GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
            }

            // 		g_StringLanType(szLan, "上传状态%d", "Upload successfully");
            // 		m_strUploadStatus.Format(szLan,state);
            if (state != 2)
            {
                KillTimer(UPLOAD_BLACK_LIST_TIMER);
                if (!NET_DVR_UploadClose(m_lUploadHandle))
                {
                    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadClose");
                }
                else
                {
                    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadClose");
                }
                m_lUploadHandle = -1;
                m_bUploading = FALSE;
            }
        }
        else if (m_bDownloading)
        {
            int state = NET_DVR_GetDownloadState(m_lDownloadHandle, &dwProgress);

            if (state == 1)
            {
                m_ctrlProgress.SetPos(dwProgress);
                CString str;
                str.Format("%d", dwProgress);
                str += _T("%");
                m_statProgress.SetWindowText(str);
                g_StringLanType(szLan, "下载成功", "Download successfully");
                // m_strUploadStatus.Format(szLan);
                GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
            }
            else if (state == 2)
            {
                m_ctrlProgress.SetPos(dwProgress);
                CString str;
                str.Format("%d", dwProgress);
                str += _T("%");
                m_statProgress.SetWindowText(str);
                g_StringLanType(szLan, "正在下载,已下载:%d", "Is Downloading,progress:%d");
                CString	strDownloadStatus;
                strDownloadStatus.Format(szLan, dwProgress);
                GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(strDownloadStatus);
            }
            else if (state == 3)
            {
                g_StringLanType(szLan, "下载失败", "Download failed");
                GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
            }
            else if (state == 4)
            {
                g_StringLanType(szLan, "网络断开，状态未知", "Network disconnect, status unknown");
                GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
            }

            // 		g_StringLanType(szLan, "下载状态%d", "Download successfully");
            // 		m_strDownloadStatus.Format(szLan,state);
            if (state != 2)
            {
                KillTimer(UPLOAD_BLACK_LIST_TIMER);
                if (!NET_DVR_StopDownload(m_lDownloadHandle))
                {
                    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopDownload");
                }
                else
                {
                    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopDownload");
                }
                m_lDownloadHandle = -1;
                m_bDownloading = FALSE;
                m_strFilePath = m_szDowndFilePath;
                GetDlgItem(IDC_BTN_UPLAOD)->EnableWindow(TRUE);
            }
        }
    }
    UpdateData(FALSE);

    CDialog::OnTimer(nIDEvent);
}

void CDlgUploadBlackList::OnBnClickedBtnExit()
{
    // TODO:  在此添加控件通知处理程序代码
    CDialog::OnCancel();
}


void CDlgUploadBlackList::OnBnClickedBtnSetFilepath()
{
    // TODO:  在此添加控件通知处理程序代码
    CString strFilter = _T("All Files(*.*)|*.*||");
    CFileDialog fileChose(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
    if (fileChose.DoModal() != IDOK)
    {
        return;
    }
    m_szDowndFilePath = fileChose.GetPathName();
    GetDlgItem(IDC_EDIT_BLACKLIST_DOWNLOAD_DIR)->SetWindowText(m_szDowndFilePath);
}


void CDlgUploadBlackList::OnBnClickedBtnDownload()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    if (m_bUploading || m_bDownloading)
    {
        return;
    }
    char szLan[128] = { 0 };
    m_ctrlProgress.SetPos(0);
    if (m_cmbDownLoadType.GetCurSel() == 0)
    {
        m_lDownloadHandle = NET_DVR_StartDownload(m_lServerID, NET_SDK_DOWNLOAD_CERTIFICATE_BLACK_LIST_TEMPLET, NULL, 0, m_szDowndFilePath.GetBuffer(0));
        if (m_lDownloadHandle == -1)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartDownload NET_SDK_DOWNLOAD_CERTIFICATE_BLACK_LIST_TEMPLET");
            AfxMessageBox("NET_DVR_StartDownload failed");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText("Download Certificate Black list template Failed!");
        }
        else
        {
            GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StartDownload NET_SDK_DOWNLOAD_CERTIFICATE_BLACK_LIST_TEMPLET");
            m_bDownloading = TRUE;
            m_ctrlProgress.SetPos(0);
            m_statProgress.SetWindowText(_T("0%"));
            m_timerHandle = SetTimer(UPLOAD_BLACK_LIST_TIMER, 100, NULL);
        }
    }
    else if (m_cmbDownLoadType.GetCurSel() == 1)
    {
        int iAudioNo = m_dwDownloadAudioNo;
        if (iAudioNo <1 || iAudioNo >32)
        {
            g_StringLanType(szLan, "音频文件ID无效", "Audio file No is invalid");
            AfxMessageBox(szLan);
            return;
        }

        NET_DVR_RIGHT_CONTROLLER_AUDIO_PARAM struRightControllerAudioParam = { 0 };
        struRightControllerAudioParam.dwSize = sizeof(struRightControllerAudioParam);
        struRightControllerAudioParam.dwAudioID = iAudioNo;

        m_lDownloadHandle = NET_DVR_StartDownload(m_lServerID, NET_SDK_DOWNLOAD_RIGHT_CONTROLLER_AUDIO, &struRightControllerAudioParam, sizeof(struRightControllerAudioParam), m_szDowndFilePath.GetBuffer(0));
        if (m_lDownloadHandle == -1)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartDownload NET_SDK_DOWNLOAD_RIGHT_CONTROLLER_AUDIO");
            AfxMessageBox("NET_DVR_StartDownload failed");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText("Download Right Controller Audio Failed!");
        }
        else
        {
            GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StartDownload NET_SDK_DOWNLOAD_RIGHT_CONTROLLER_AUDIO");
            m_bDownloading = TRUE;
            m_ctrlProgress.SetPos(0);
            m_statProgress.SetWindowText(_T("0%"));
            m_timerHandle = SetTimer(UPLOAD_BLACK_LIST_TIMER, 100, NULL);
        }
    }
    else
    {
        ;
    }

    UpdateData(FALSE);
}


void CDlgUploadBlackList::OnCbnSelchangeCmbUpload()
{
    // TODO:  在此添加控件通知处理程序代码
    if (m_cmbUploadType.GetCurSel() == 0)
    {
        GetDlgItem(IDC_STATIC_UPLOAD_AUDIO)->ShowWindow(FALSE);
        GetDlgItem(IDC_EDIT_UPLOAD_AUDIO_NO)->ShowWindow(FALSE);
    }
    if (m_cmbUploadType.GetCurSel() == 1)
    {
        GetDlgItem(IDC_STATIC_UPLOAD_AUDIO)->ShowWindow(TRUE);
        GetDlgItem(IDC_EDIT_UPLOAD_AUDIO_NO)->ShowWindow(TRUE);
    }
}


void CDlgUploadBlackList::OnCbnSelchangeCmbDownload()
{
    // TODO:  在此添加控件通知处理程序代码
    if (m_cmbDownLoadType.GetCurSel() == 0)
    {
        GetDlgItem(IDC_STATIC_DOWNLOAD_AUDIO)->ShowWindow(FALSE);
        GetDlgItem(IDC_EDIT_DOWNLOAD_AUDIO_NO)->ShowWindow(FALSE);
    }
    if (m_cmbDownLoadType.GetCurSel() == 1)
    {
        GetDlgItem(IDC_STATIC_DOWNLOAD_AUDIO)->ShowWindow(TRUE);
        GetDlgItem(IDC_EDIT_DOWNLOAD_AUDIO_NO)->ShowWindow(TRUE);
    }
}
