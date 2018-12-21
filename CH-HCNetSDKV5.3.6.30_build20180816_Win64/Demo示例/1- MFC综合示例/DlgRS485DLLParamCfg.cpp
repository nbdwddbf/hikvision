// DlgRS485DLLParamCfg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgRS485DLLParamCfg.h"
#include "afxdialogex.h"


// CDlgRS485DLLParamCfg 对话框

IMPLEMENT_DYNAMIC(CDlgRS485DLLParamCfg, CDialog)

CDlgRS485DLLParamCfg::CDlgRS485DLLParamCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRS485DLLParamCfg::IDD, pParent)
    , m_sFilePath(_T(""))
    , m_sSaveFilePath(_T(""))
{
    m_iUserID = -1;
    m_iDeviceIndex = -1;
    m_lUpdownloadHandle = -1;
    m_bUploading = FALSE;
    m_bDownloading = FALSE;
    m_dwUpLoadFileSize = 0;
}

CDlgRS485DLLParamCfg::~CDlgRS485DLLParamCfg()
{
    if (m_bUploading)
    {
        if (!NET_DVR_UploadClose(m_lUpdownloadHandle))
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
        if (!NET_DVR_StopDownload(m_lUpdownloadHandle))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopDownload");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopDownload");
        }
        m_bDownloading = FALSE;
    }
    m_lUpdownloadHandle = -1;
    m_iUserID = -1;
    m_iDeviceIndex = -1;
    m_bUploading = FALSE;
    m_bDownloading = FALSE;
}

void CDlgRS485DLLParamCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_DLL_FILE_PATH, m_sFilePath);
    DDV_MaxChars(pDX, m_sFilePath, 64);
    DDX_Text(pDX, IDC_EDIT_DLL_FILE_SAVE_PATH, m_sSaveFilePath);
    DDV_MaxChars(pDX, m_sSaveFilePath, 64);
}


BEGIN_MESSAGE_MAP(CDlgRS485DLLParamCfg, CDialog)
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_BTN_CHOOSE_DLL_FILE, &CDlgRS485DLLParamCfg::OnBnClickedBtnChooseDllFile)
    ON_BN_CLICKED(IDC_BTN_SAVE_DLL_FILE, &CDlgRS485DLLParamCfg::OnBnClickedBtnSaveDllFile)
    ON_BN_CLICKED(IDC_BTN_IMPORT_DLL, &CDlgRS485DLLParamCfg::OnBnClickedBtnImportDll)
    ON_BN_CLICKED(IDC_BTN_EXPORT_DLL, &CDlgRS485DLLParamCfg::OnBnClickedBtnExportDll)
END_MESSAGE_MAP()


// CDlgRS485DLLParamCfg 消息处理程序


void CDlgRS485DLLParamCfg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO:  在此添加消息处理程序代码和/或调用默认值
    if (nIDEvent == TIME_RS485_DLL_FILE_PROGRESS)
    {
        DWORD dwProgress = 0;
        LONG lStatus = -1;
        if (m_bUploading)
        {
            lStatus = NET_DVR_GetUploadState(m_lUpdownloadHandle, &dwProgress);
            if (lStatus == -1)
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetUploadState");
                if (!NET_DVR_UploadClose(m_lUpdownloadHandle))
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
            lStatus = NET_DVR_GetDownloadState(m_lUpdownloadHandle, &dwProgress);
            if (lStatus == -1)
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetDownloadState");
                if (!NET_DVR_StopDownload(m_lUpdownloadHandle))
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
                    if (m_bUploading)
                    {
                        if (!NET_DVR_UploadClose(m_lUpdownloadHandle))
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
                        if (!NET_DVR_StopDownload(m_lUpdownloadHandle))
                        {
                            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopDownload");
                        }
                        else
                        {
                            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopDownload");
                        }
                        m_bDownloading = FALSE;
                    }
                    m_lUpdownloadHandle = -1;
                    KillTimer(TIME_RS485_DLL_FILE_PROGRESS);
                    MessageBox("RS485协议库文件导入导出成功", "导入导出", MB_OK | MB_ICONWARNING);
                    break;
        }
        case 2: //正在上传或下载
        {
                    break;
        }
        case 3: //上传或下载失败
        {
                    if (m_bUploading)
                    {
                        if (!NET_DVR_UploadClose(m_lUpdownloadHandle))
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
                        if (!NET_DVR_StopDownload(m_lUpdownloadHandle))
                        {
                            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopDownload");
                        }
                        else
                        {
                            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopDownload");
                        }
                        m_bDownloading = FALSE;
                    }
                    m_lUpdownloadHandle = -1;
                    KillTimer(TIME_RS485_DLL_FILE_PROGRESS);
                    MessageBox("RS485协议库文件导入导出失败", "导入导出", MB_OK | MB_ICONWARNING);
                    break;
        }
        case 4: //网络断开
        {
                    if (m_bUploading)
                    {
                        if (!NET_DVR_UploadClose(m_lUpdownloadHandle))
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
                        if (!NET_DVR_StopDownload(m_lUpdownloadHandle))
                        {
                            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopDownload");
                        }
                        else
                        {
                            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopDownload");
                        }
                        m_bDownloading = FALSE;
                    }
                    m_lUpdownloadHandle = -1;
                    KillTimer(TIME_RS485_DLL_FILE_PROGRESS);
                    MessageBox("网络异常", "导入导出", MB_OK | MB_ICONWARNING);
                    break;
        }
        }
    }
    CDialog::OnTimer(nIDEvent);
}


void CDlgRS485DLLParamCfg::OnBnClickedBtnChooseDllFile()
{
    // TODO:  在此添加控件通知处理程序代码
    CString strFilter = _T("DLL(*.dll)|*.dll|All Files(*.*)|*.*||)");
    CFileDialog fileChose(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
    if (fileChose.DoModal() != IDOK)
    {
        return;
    }
    m_sFilePath = fileChose.GetPathName();
    GetDlgItem(IDC_EDIT_DLL_FILE_PATH)->SetWindowText(m_sFilePath);

    CFileStatus fileStatus;

    if (CFile::GetStatus(m_sFilePath, fileStatus))
    {
        m_dwUpLoadFileSize = fileStatus.m_size;
    }
}


void CDlgRS485DLLParamCfg::OnBnClickedBtnSaveDllFile()
{
    // TODO:  在此添加控件通知处理程序代码
    CString strFilter = _T("DLL(*.dll)|*.dll|All Files(*.*)|*.*||)");
    CFileDialog fileChose(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
    if (fileChose.DoModal() != IDOK)
    {
        return;
    }
    m_sSaveFilePath = fileChose.GetPathName();
    GetDlgItem(IDC_EDIT_DLL_FILE_SAVE_PATH)->SetWindowText(m_sSaveFilePath);
}


void CDlgRS485DLLParamCfg::OnBnClickedBtnImportDll()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    if (m_bUploading || m_bDownloading)
    {
        return;
    }
    DWORD dwInterBuff = m_dwUpLoadFileSize;
    m_lUpdownloadHandle = NET_DVR_UploadFile_V40(m_iUserID, UPLOAD_RS485_PROTOCOL_DLL_FILE, &dwInterBuff, sizeof(DWORD), m_sFilePath.GetBuffer(0), NULL, 0);
    if (m_lUpdownloadHandle == -1)
    {
        DWORD dwErr = NET_DVR_GetLastError();
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadFile_V40 UPLOAD_RS485_PROTOCOL_DLL_FILE, err[%d]", dwErr);
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadFile_V40 UPLOAD_RS485_PROTOCOL_DLL_FILE");

    m_bUploading = TRUE;
    SetTimer(TIME_RS485_DLL_FILE_PROGRESS, 100, NULL);
}


void CDlgRS485DLLParamCfg::OnBnClickedBtnExportDll()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);

    if (m_bUploading || m_bDownloading)
    {
        return;
    }

    m_lUpdownloadHandle = NET_DVR_StartDownload(m_iUserID, NET_SDK_DOWNLOAD_RS485_PROTOCOL_DLL_FILE, NULL, 0, m_sSaveFilePath.GetBuffer(0));
    if (m_lUpdownloadHandle == -1)
    {
        DWORD dwErr = NET_DVR_GetLastError();
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartDownload NET_SDK_DOWNLOAD_RS485_PROTOCOL_DLL_FILE, err[%d]", dwErr);
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StartDownload NET_SDK_DOWNLOAD_RS485_PROTOCOL_DLL_FILE");

    m_bDownloading = TRUE;
    SetTimer(TIME_RS485_DLL_FILE_PROGRESS, 100, NULL);
}
