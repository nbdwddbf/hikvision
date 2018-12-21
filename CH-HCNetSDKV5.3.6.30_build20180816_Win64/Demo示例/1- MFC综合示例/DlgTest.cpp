// DlgTest.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgTest.h"
#include "afxdialogex.h"


// CDlgTest 对话框

IMPLEMENT_DYNAMIC(CDlgTest, CDialogEx)

CDlgTest::CDlgTest(CWnd* pParent /*=NULL*/)
: CDialogEx(CDlgTest::IDD, pParent)
, m_dwChan(0)
, m_dwIn(0)
, m_dwOut(0)
, m_dwST(0)
, m_dwEt(0)
, m_dwEh(0)
, m_dwAlarm(0)
, m_csFilePath(_T(""))
, m_csDeepeyesFilePath(_T(""))
, m_dwFileType(0)
{
    memset(&struCameraWorkMode, 0, sizeof(struCameraWorkMode));
    m_bUpLoadingTX1 = false;
}

CDlgTest::~CDlgTest()
{
}

void CDlgTest::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_CAHN, m_dwChan);
    DDX_Text(pDX, IDC_EDIT_IN, m_dwIn);
    DDX_Text(pDX, IDC_EDIT_OUT, m_dwOut);
    DDX_Text(pDX, IDC_EDIT_STIME, m_dwST);
    DDX_Text(pDX, IDC_EDIT_ETIME, m_dwEt);
    DDX_Text(pDX, IDC_EDIT_EHOME, m_dwEh);
    DDX_Text(pDX, IDC_EDIT_ALARM, m_dwAlarm);
    DDX_Control(pDX, IDC_CMB_WORK_MODE, m_cmbWorkMode);
    DDX_Control(pDX, IDC_CMB_PREVIEW_IMAGE_MODE, m_cmbPreviewImageMode);
    DDX_Text(pDX, IDC_EDIT3, m_csFilePath);
    DDX_Text(pDX, IDC_EDIT_DEEPEYES_BINOCULAR_DIR, m_csDeepeyesFilePath);
    DDX_Control(pDX, IDC_COMBO_FILETYPE, m_comFileType);
}


BEGIN_MESSAGE_MAP(CDlgTest, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_SET, &CDlgTest::OnBnClickedBtnSet)
    ON_BN_CLICKED(IDC_BTN_SET_COUNTING, &CDlgTest::OnBnClickedBtnSetCounting)
    ON_BN_CLICKED(IDC_BTN_GET_COUNTING, &CDlgTest::OnBnClickedBtnGetCounting)
    ON_BN_CLICKED(IDC_BTN_FILE_PATH, &CDlgTest::OnBnClickedBtnFilePath)
    ON_BN_CLICKED(IDC_BTN_FILE_UPLOAD, &CDlgTest::OnBnClickedBtnFileUpload)
    ON_BN_CLICKED(IDC_BTN_FILE_UPLOAD_DEEPEYES_BINOCULAR, &CDlgTest::OnBnClickedBtnFileUploadDeepeyesBinocular)
    ON_BN_CLICKED(IDC_BTN_FILE_PATH_DEEPEYES_BINOCULAR, &CDlgTest::OnBnClickedBtnFilePathDeepeyesBinocular)
    ON_BN_CLICKED(IDC_BTN_FILE_PATH_DEEPEYES_BINOCULAR, &CDlgTest::OnBnClickedBtnFilePathDeepeyesBinocular)
    ON_CBN_SELCHANGE(IDC_COMBO_FILETYPE, &CDlgTest::OnCbnSelchangeComboFiletype)
END_MESSAGE_MAP()


// CDlgTest 消息处理程序


void CDlgTest::OnBnClickedBtnSet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    NET_DVR_FLASH_CFG struWD1Cfg = { 0 };
    struWD1Cfg.dwSize = sizeof(NET_DVR_FLASH_CFG);
    struWD1Cfg.dwAlarmFlag = m_dwAlarm;
    struWD1Cfg.dwChan = m_dwChan;
    struWD1Cfg.dwStartTime = m_dwST;
    struWD1Cfg.dwEndTime = m_dwEt;
    struWD1Cfg.dwInNumbers = m_dwIn;
    struWD1Cfg.dwOutNumbers = m_dwOut;
    struWD1Cfg.dwEhomeFlag = m_dwEh;


    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_FLASH_CFG, m_lChannel, &struWD1Cfg, sizeof(NET_DVR_FLASH_CFG)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_FLASH_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_FLASH_CFG");
    }
}





void CDlgTest::OnBnClickedBtnSetCounting()
{

    UpdateData(TRUE);

    struCameraWorkMode.dwSize = sizeof(NET_DVR_CAMERA_WORK_MODE);
    struCameraWorkMode.byWorkMode = m_cmbWorkMode.GetCurSel();
    struCameraWorkMode.byPreviewImageMode = m_cmbPreviewImageMode.GetCurSel();

    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struCameraWorkMode;
    struCfg.dwInSize = sizeof(struCameraWorkMode);

    if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_CAMERA_WORK_MODE, &struCfg))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_CAMERA_WORK_MODE");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_CAMERA_WORK_MODE");
    }
}


void CDlgTest::OnBnClickedBtnGetCounting()
{
    UpdateData(TRUE);
    memset(&struCameraWorkMode, 0, sizeof(struCameraWorkMode));

    NET_DVR_STD_CONFIG struStdConfig = { 0 };
    struStdConfig.lpCondBuffer = &m_lChannel;
    struStdConfig.dwCondSize = sizeof(m_lChannel);
    struStdConfig.lpOutBuffer = (LPVOID)&struCameraWorkMode;
    struStdConfig.dwOutSize = sizeof(struCameraWorkMode);
    if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_CAMERA_WORK_MODE, &struStdConfig))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_CAMERA_WORK_MODE");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_CAMERA_WORK_MODE");
    }
    m_cmbPreviewImageMode.SetCurSel(struCameraWorkMode.byPreviewImageMode);
    m_cmbWorkMode.SetCurSel(struCameraWorkMode.byWorkMode);

    UpdateData(FALSE);
}


void CDlgTest::OnBnClickedBtnFilePath()
{
    // TODO: Add your control notification handler code here
    static char szFilter[] = "All File(*.*)|*.*||";
    CFileDialog dlg(TRUE, "*.*", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
    if (dlg.DoModal() == IDOK)
    {
        m_csFilePath = dlg.GetPathName();
        UpdateData(FALSE);
    }
}

DWORD  GetUpLoadFileCountThread(LPVOID pParam)
{
    CDlgTest *pThis = (CDlgTest*)pParam;

    DWORD dwState = 0;
    DWORD dwProgress = 0;
    char szLan[256] = { 0 };


    while (TRUE)
    {
        dwState = NET_DVR_GetUploadState(pThis->m_lUploadHandle, &dwProgress);
        if (dwState == 1)
        {
            g_StringLanType(szLan, "上传成功", "Upload successfully");
            pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
            pThis->m_bUpLoading = FALSE;
            g_StringLanType(szLan, "上传", "Upload");
            pThis->GetDlgItem(IDC_BTN_FILE_UPLOAD)->SetWindowText(szLan);
            pThis->m_bUpLoading = FALSE;
            break;
        }
        else if (dwState == 2)
        {
            g_StringLanType(szLan, "正在上传,已上传:", "Is uploading,progress:");
            sprintf(szLan, "%s%d", szLan, dwProgress);
            pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        }
        else if (dwState == 3)
        {
            g_StringLanType(szLan, "上传失败", "Upload failed");
            pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
            break;
        }
        else if (dwState == 4)
        {
            if (dwProgress == 100)
            {
                g_StringLanType(szLan, "上传成功", "Upload successfully");
                pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
                g_StringLanType(szLan, "上传", "UpLoad");
                pThis->GetDlgItem(IDC_BTN_FILE_UPLOAD)->SetWindowText(szLan);
                pThis->m_bUpLoading = FALSE;
                break;
            }
            else
            {
                g_StringLanType(szLan, "网络断开，状态未知", "Network disconnect, status unknown");
                pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
                break;
            }

        }

        if (dwState != 2 && dwState != 5)
        {
            NET_DVR_UploadClose(pThis->m_lUploadHandle);
            pThis->m_bUpLoading = FALSE;
            g_StringLanType(szLan, "上传", "UpLoad");
            pThis->GetDlgItem(IDC_BTN_FILE_UPLOAD)->SetWindowText(szLan);
        }
    }

    return FALSE;
}

void CDlgTest::OnBnClickedBtnFileUpload()
{
    // TODO: Add your control notification handler code here
    char szLan[128] = { 0 };
    if (m_bUpLoading == FALSE)
    {
        UpdateData(TRUE);
        char szFileName[MAX_PATH];
        strcpy(szFileName, m_csFilePath);
        CFile cFile;
        GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        if (!cFile.Open(szFileName, NULL))
        {
            g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
            AfxMessageBox(szLan);
            return;
        }
        DWORD dwFileSize = (DWORD)cFile.GetLength();
        if (dwFileSize == 0)
        {
            g_StringLanType(szLan, "配置文件为空", "Configure file is empty");
            AfxMessageBox(szLan);
        }
        cFile.Close();


        m_lUploadHandle = NET_DVR_UploadFile(m_lServerID, UPLOAD_BINOCULAR_COUNTING, NULL, NULL, szFileName);
        if (m_lUploadHandle < 0)
        {
            NET_DVR_StopUploadFile(m_lUploadHandle);
            AfxMessageBox("UPLOAD_BINOCULAR_COUNTING Upload Failed");
            return;
        }

        DWORD dwThreadId = 0;
        m_hUpLoadThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetUpLoadFileCountThread), this, 0, &dwThreadId);
        if (m_hUpLoadThread == NULL)
        {
            char szLan[256] = { 0 };
            g_StringLanType(szLan, "打开长传文件线程失败!", "open UpLoad thread Fail!");
            AfxMessageBox(szLan);
            return;
        }
        g_StringLanType(szLan, "停止上传", "Stop UpLoad");
        GetDlgItem(IDC_BTN_FILE_UPLOAD)->SetWindowText(szLan);
        m_bUpLoading = TRUE;
    }
    else
    {
        NET_DVR_UploadClose(m_lUploadHandle);
        m_bUpLoading = FALSE;
        g_StringLanType(szLan, "上传", "UpLoad");
        GetDlgItem(IDC_BTN_FILE_UPLOAD)->SetWindowText(szLan);
    }
    UpdateData(FALSE);
}

DWORD  GetUpLoadTX1FileCountThread(LPVOID pParam)
{
    CDlgTest *pThis = (CDlgTest*)pParam;

    DWORD dwState = 0;
    DWORD dwProgress = 0;
    char szLan[256] = { 0 };


    while (TRUE)
    {
        dwState = NET_DVR_GetUploadState(pThis->m_lUploadHandleTX1, &dwProgress);
        if (dwState == 1)
        {
            g_StringLanType(szLan, "上传成功", "Upload successfully");
            pThis->GetDlgItem(IDC_STATIC_STATUS_TX1)->SetWindowText(szLan);
            pThis->m_bUpLoadingTX1 = FALSE;
            g_StringLanType(szLan, "上传", "Upload");
            pThis->GetDlgItem(IDC_BTN_FILE_UPLOAD_DEEPEYES_BINOCULAR)->SetWindowText(szLan);
            pThis->m_bUpLoadingTX1 = FALSE;
            break;
        }
        else if (dwState == 2)
        {
            g_StringLanType(szLan, "正在上传,已上传:", "Is uploading,progress:");
            sprintf(szLan, "%s%d", szLan, dwProgress);
            pThis->GetDlgItem(IDC_STATIC_STATUS_TX1)->SetWindowText(szLan);
        }
        else if (dwState == 3)
        {
            g_StringLanType(szLan, "上传失败", "Upload failed");
            pThis->GetDlgItem(IDC_STATIC_STATUS_TX1)->SetWindowText(szLan);
            break;
        }
        else if (dwState == 4)
        {
            if (dwProgress == 100)
            {
                g_StringLanType(szLan, "上传成功", "Upload successfully");
                pThis->GetDlgItem(IDC_STATIC_STATUS_TX1)->SetWindowText(szLan);
                g_StringLanType(szLan, "上传", "UpLoad");
                pThis->GetDlgItem(IDC_BTN_FILE_UPLOAD_DEEPEYES_BINOCULAR)->SetWindowText(szLan);
                pThis->m_bUpLoadingTX1 = FALSE;
                break;
            }
            else
            {
                g_StringLanType(szLan, "网络断开，状态未知", "Network disconnect, status unknown");
                pThis->GetDlgItem(IDC_STATIC_STATUS_TX1)->SetWindowText(szLan);
                break;
            }

        }

        if (dwState != 2 && dwState != 5)
        {
            NET_DVR_UploadClose(pThis->m_lUploadHandleTX1);
            pThis->m_bUpLoadingTX1 = FALSE;
            g_StringLanType(szLan, "上传", "UpLoad");
            pThis->GetDlgItem(IDC_BTN_FILE_UPLOAD_DEEPEYES_BINOCULAR)->SetWindowText(szLan);
            break;
        }
    }

    return FALSE;
}

void CDlgTest::OnBnClickedBtnFileUploadDeepeyesBinocular()
{
    char szLan[128] = { 0 };
    if (m_bUpLoadingTX1 == FALSE)
    {
        UpdateData(TRUE);
        char szFileName[MAX_PATH];
        strcpy(szFileName, m_csDeepeyesFilePath);
        CFile cFile;
        GetDlgItem(IDC_STATIC_STATUS_TX1)->SetWindowText(szLan);
        if (!cFile.Open(szFileName, NULL))
        {
            g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
            AfxMessageBox(szLan);
            return;
        }
        DWORD dwFileSize = (DWORD)cFile.GetLength();
        if (dwFileSize == 0)
        {
            g_StringLanType(szLan, "配置文件为空", "Configure file is empty");
            AfxMessageBox(szLan);
        }
        cFile.Close();


        m_lUploadHandleTX1 = NET_DVR_UploadFile(m_lServerID, m_dwFileType, NULL, NULL, szFileName);
        if (m_lUploadHandleTX1 < 0)
        {
            NET_DVR_StopUploadFile(m_lUploadHandleTX1);
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadFile");
            return;
        }

        DWORD dwThreadId = 0;
        m_hUpLoadThreadTX1 = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetUpLoadTX1FileCountThread), this, 0, &dwThreadId);
        if (m_hUpLoadThreadTX1 == NULL)
        {
            char szLan[256] = { 0 };
            g_StringLanType(szLan, "打开长传文件线程失败!", "open UpLoad thread Fail!");
            AfxMessageBox(szLan);
            return;
        }
        g_StringLanType(szLan, "停止上传", "Stop UpLoad");
        GetDlgItem(IDC_BTN_FILE_UPLOAD_DEEPEYES_BINOCULAR)->SetWindowText(szLan);
        m_bUpLoadingTX1 = TRUE;
    }
    else
    {
        NET_DVR_UploadClose(m_lUploadHandle);
        m_bUpLoadingTX1 = FALSE;
        g_StringLanType(szLan, "上传", "UpLoad");
        GetDlgItem(IDC_BTN_FILE_UPLOAD_DEEPEYES_BINOCULAR)->SetWindowText(szLan);
    }
    UpdateData(FALSE);
}


void CDlgTest::OnBnClickedBtnFilePathDeepeyesBinocular()
{
    static char szFilter[] = "All File(*.*)|*.*||";
    CFileDialog dlg(TRUE, "*.*", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
    if (dlg.DoModal() == IDOK)
    {
        m_csDeepeyesFilePath = dlg.GetPathName();
        UpdateData(FALSE);
    }
}


void CDlgTest::OnCbnSelchangeComboFiletype()
{
    // TODO:  在此添加控件通知处理程序代码
    int i = m_comFileType.GetCurSel();

    if (0 == i)
    {
        m_dwFileType = UPLOAD_DEEPEYES_BINOCULAR;
    } 
    else if (1 == i)
    {
        m_dwFileType = UPLOAD_LEFTEYE_4K_CALIBFILE;
    }
}


BOOL CDlgTest::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    m_comFileType.SetCurSel(0);
    OnCbnSelchangeComboFiletype();
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}
