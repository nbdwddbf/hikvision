// DlgJPEGPicDownloadMedical.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgJPEGPicDownloadMedical.h"
#include "afxdialogex.h"
#include "Picture.h"
#include "DlgPictureUpload.h"

// CDlgJPEGPicDownloadMedical 对话框
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgJPEGPicDownloadMedical *g_pDlgRemoteFile;
CPicture *lpPicture = NULL;
LONG lNum = 0;

static void CALLBACK g_fDownloadPictureByTimeCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData);
#define WM_MSG_GETDATA_FINISH 1002
#define WM_MSG_SAVE_PICTURE_FILE 1003

static UINT GetPicThread(LPVOID pParam)
{
    CDlgJPEGPicDownloadMedical *GetPic = (CDlgJPEGPicDownloadMedical *)pParam;
    CString csFileName;
    CString csPicTime;
    CString csCardNum;
    CString csTemp, csDir;
    char nFileName[256] = { 0 };
    char sMessageCn[256] = { 0 };
    char sMessageEn[256] = { 0 };
    int fileselpos = 0;

    char szLan[256] = { 0 };

    while (GetPic->pos)
    {
        if (!GetPic->m_bDown)
        {
            break;
        }
        fileselpos = GetPic->m_PicList.GetNextSelectedItem(GetPic->pos);
        csFileName.Format("%s", GetPic->m_PicList.GetItemText(fileselpos, 0));
        if (csFileName.IsEmpty())
        {
            g_StringLanType(szLan, "下载", "Download");
            GetPic->GetDlgItem(IDC_DOWNLOAD)->SetWindowText(szLan);
            GetPic->GetDlgItem(IDC_STATICSTATE2)->ShowWindow(SW_HIDE);
            GetPic->m_downProgress.SetPos(0);
            GetPic->m_bDown = FALSE;
            CloseHandle(GetPic->m_hGetThread);
            GetPic->m_hGetThread = NULL;
            g_StringLanType(szLan, "文件名为空!", "File name is blank!");
            AfxMessageBox(szLan);
            return 1;
        }

        csPicTime.Format("%s", GetPic->m_PicList.GetItemText(fileselpos, 2));
        csCardNum.Format("%s", GetPic->m_PicList.GetItemText(fileselpos, 3));
        sprintf(GetPic->filenamedownload, "%s", csFileName);

        csDir.Format("%s\\", g_struLocalParam.chPictureSavePath);

        //BOOL bShowIpv6 = g_ValidIPv6((BYTE*)g_struDeviceInfo[GetPic->m_iDeviceIndex].chDeviceIP);
        //if (bShowIpv6)
        //{
        //	sprintf(nFileName, "%s_ipv6_%02d_D%s_%s_%d.jpg",csDir, GetPic->m_iChannel, csPicTime,csCardNum, fileselpos + 1);
        //} 
        //else
        //{
        //	sprintf(nFileName, "%s%s_%02d_D%s_%s_%d.jpg",csDir, g_struDeviceInfo[GetPic->m_iDeviceIndex].chDeviceIP, GetPic->m_iChannel, csPicTime,csCardNum, fileselpos + 1);
        //}
        //
        //  	if (NET_DVR_GetPicture(GetPic->m_lServerID, GetPic->filenamedownload, nFileName))
        //{			
        //   		Sleep(10);
        //	GetPic->nDownPics++;
        //	GetPic->m_downProgress.SetPos(GetPic->nDownPics*100/GetPic->nSelPics);
        //}

        char *sSavedFileBuf = NULL;
        DWORD dwRetLen = 0;

        NET_DVR_PIC_PARAM struPicParam = { 0 };
        struPicParam.pDVRFileName = GetPic->filenamedownload;
        struPicParam.pSavedFileBuf = sSavedFileBuf;
        struPicParam.lpdwRetLen = &dwRetLen;
        CString szIp;
        CString szPort;
        szIp.Format("%s", GetPic->m_PicList.GetItemText(fileselpos, 8));
        //ipv4
        if (!g_ValidIPv6((BYTE*)(LPCSTR)szIp))
        {
            sprintf(struPicParam.struAddr.struIP.sIpV4, "%s", szIp);
        }
        else
        {
            sprintf((char *)struPicParam.struAddr.struIP.byIPv6, "%s", szIp);
        }

        szPort = GetPic->m_PicList.GetItemText(fileselpos, 9);
        struPicParam.struAddr.wPort = _ttoi(szPort);

        if (szIp.GetLength() != 0)
        {
            sprintf(nFileName, "%s%s_%02d_D%s_%s_%d.jpg", csDir, szIp, GetPic->m_iChannel, csPicTime, csCardNum, fileselpos + 1);
        }
        else
        {
            BOOL bShowIpv6 = g_ValidIPv6((BYTE*)g_struDeviceInfo[GetPic->m_iDeviceIndex].chDeviceIP);
            if (bShowIpv6)
            {
                sprintf(nFileName, "%s_ipv6_%02d_D%s_%s_%d.jpg", csDir, GetPic->m_iChannel, csPicTime, csCardNum, fileselpos + 1);
            }
            else
            {
                sprintf(nFileName, "%s%s_%02d_D%s_%s_%d.jpg", csDir, g_struDeviceInfo[GetPic->m_iDeviceIndex].chDeviceIP, GetPic->m_iChannel, csPicTime, csCardNum, fileselpos + 1);
            }
        }

        if (NET_DVR_GetPicture_V50(GetPic->m_lServerID, &struPicParam))
        {
            if (0 != dwRetLen)
            {
                sSavedFileBuf = new char[dwRetLen];
                memset(sSavedFileBuf, 0, dwRetLen);
                struPicParam.pSavedFileBuf = sSavedFileBuf;
                struPicParam.dwBufLen = dwRetLen;

                if (NET_DVR_GetPicture_V50(GetPic->m_lServerID, &struPicParam))
                {
                    if (NULL != sSavedFileBuf && 0 != dwRetLen)
                    {
                        char cFilename[256] = { 0 };
                        HANDLE hFile;
                        DWORD dwReturn;
                        hFile = CreateFile(nFileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                        if (hFile == INVALID_HANDLE_VALUE)
                        {
                            if (NULL != sSavedFileBuf)
                            {
                                delete[]sSavedFileBuf;
                                sSavedFileBuf = NULL;
                            }
                            break;
                        }
                        WriteFile(hFile, sSavedFileBuf, dwRetLen, &dwReturn, NULL);
                        CloseHandle(hFile);
                        hFile = NULL;
                    }

                    Sleep(10);
                    GetPic->nDownPics++;
                    GetPic->m_downProgress.SetPos(GetPic->nDownPics * 100 / GetPic->nSelPics);
                }
                else
                {
                    g_pMainDlg->AddLog(GetPic->m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetPicture_V50");
                }

                if (NULL != sSavedFileBuf)
                {
                    delete[]sSavedFileBuf;
                    sSavedFileBuf = NULL;
                }
            }
        }
    }

    GetPic->m_downProgress.SetPos(0);
    g_StringLanType(szLan, "下载", "Download");
    GetPic->GetDlgItem(IDC_DOWNLOAD)->SetWindowText(szLan);
    GetPic->GetDlgItem(IDC_STATICSTATE2)->ShowWindow(SW_HIDE);
    GetPic->m_bDown = FALSE;
    CloseHandle(GetPic->m_hGetThread);
    GetPic->m_hGetThread = NULL;
    sprintf(sMessageCn, "选择了 %d 张图片,下载了 %d 张图片", GetPic->nSelPics, GetPic->nDownPics);
    sprintf(sMessageEn, "selected %d picture，downloaded %d picture", GetPic->nSelPics, GetPic->nDownPics);
    g_StringLanType(szLan, sMessageCn, sMessageEn);                                                  
    AfxMessageBox(szLan);
    GetPic->nSelPics = 0;
    GetPic->nDownPics = 0;
    return 0;
}


static UINT SearchPicThread(LPVOID pParam)
{
    CDlgJPEGPicDownloadMedical *RPic = (CDlgJPEGPicDownloadMedical *)pParam;
    LONG bRet = -1;
    CString tempstring;
    char tempfile[100];
    char szLan[256] = { 0 };
    NET_DVR_FIND_PICTURE_V40 strFileInfoV40 = { 0 };
    while (1)
    {
        if (!RPic->m_bSearchDown)
        {
            return 0;
        }
        bRet = NET_DVR_GetNextRemoteConfig(RPic->m_lFileHandle, &strFileInfoV40, sizeof(NET_DVR_FIND_PICTURE_V40));
        if (bRet == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            strcpy(tempfile, strFileInfoV40.sFileName);
            RPic->m_PicList.InsertItem(RPic->m_iFileNum, tempfile, 0);
            tempstring.Format("%d", strFileInfoV40.dwFileSize);
            RPic->m_PicList.SetItemText(RPic->m_iFileNum, 1, tempstring);
            tempstring.Format("%04d%02d%02d%02d%02d%02d", strFileInfoV40.struTime.dwYear, strFileInfoV40.struTime.dwMonth, strFileInfoV40.struTime.dwDay, strFileInfoV40.struTime.dwHour, strFileInfoV40.struTime.dwMinute, strFileInfoV40.struTime.dwSecond);
            RPic->m_PicList.SetItemText(RPic->m_iFileNum, 2, tempstring);
            tempstring.Format("%s", strFileInfoV40.sCardNum);
            RPic->m_PicList.SetItemText(RPic->m_iFileNum, 3, tempstring);
            tempstring.Format("%d", strFileInfoV40.byFileType);
            RPic->m_PicList.SetItemText(RPic->m_iFileNum, 4, tempstring);
            tempstring.Format("X:%04f Y:%04f WITH:%04f HEGHT:%04f", strFileInfoV40.uPicExtraInfo.struFaceExtraInfo.struVcaRect[0].fX, strFileInfoV40.uPicExtraInfo.struFaceExtraInfo.struVcaRect[0].fY, \
                strFileInfoV40.uPicExtraInfo.struFaceExtraInfo.struVcaRect[0].fWidth, strFileInfoV40.uPicExtraInfo.struFaceExtraInfo.struVcaRect[0].fHeight);
            RPic->m_PicList.SetItemText(RPic->m_iFileNum, 5, tempstring);
            tempstring.Format("%d", strFileInfoV40.byEventSearchStatus);
            RPic->m_PicList.SetItemText(RPic->m_iFileNum, 6, tempstring);
            tempstring.Format("%d", strFileInfoV40.byRecogResult);
            RPic->m_PicList.SetItemText(RPic->m_iFileNum, 7, tempstring);
            tempstring.Format("%s", strFileInfoV40.sLicense);
            RPic->m_PicList.SetItemText(RPic->m_iFileNum, 8, tempstring);
            RPic->m_iFileNum++;
            TRACE("m_iFileNum is %d\n", RPic->m_iFileNum);
        }
        else
        {
            if (bRet == NET_SDK_GET_NETX_STATUS_NEED_WAIT)
            {
                g_pMainDlg->AddLog(0, OPERATION_SUCC_T, "正在查询!");
                Sleep(5);
                continue;
            }
            if (bRet == NET_SDK_GET_NEXT_STATUS_FINISH)
            {
                g_StringLanType(szLan, "查找", "search");
                RPic->GetDlgItem(IDC_SEARCHLIST)->SetWindowText(szLan);
                RPic->m_bSearchDown = FALSE;
                (RPic->GetDlgItem(IDC_STATICSTATE))->ShowWindow(SW_HIDE);
                g_StringLanType(szLan, "查找到图片数:", "Searched picture sum:");
                tempstring.Format("%s%d", szLan, RPic->m_iFileNum);
                AfxMessageBox(tempstring);
                RPic->m_iFileNum = 0;
                break;
            }
            else
            {
                g_StringLanType(szLan, "查找", "search");
                RPic->GetDlgItem(IDC_SEARCHLIST)->SetWindowText(szLan);
                RPic->m_bSearchDown = FALSE;
                (RPic->GetDlgItem(IDC_STATICSTATE))->ShowWindow(SW_HIDE);
                AfxMessageBox("exception end!");
                break;
            }
        }
    }

    CloseHandle(RPic->m_hFileThread);
    RPic->m_hFileThread = NULL;
    NET_DVR_StopRemoteConfig(RPic->m_lFileHandle);

    return 0;
}

static DWORD  GetBackupPicThread(LPVOID pParam)
{
    CDlgJPEGPicDownloadMedical *pDlgRemotPlay = (CDlgJPEGPicDownloadMedical*)pParam;
    pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->ShowWindow(SW_SHOW);
    DWORD dwState = 0;
    char szLan[256] = { 0 };
    while (1)
    {
        if (!NET_DVR_GetBackupProgress(pDlgRemotPlay->m_lBackupHandle, &dwState))
        {
            DWORD dwErr = NET_DVR_GetLastError();
            //may be successful too quick
            g_StringLanType(szLan, "备份完成", "Succ to backup");
            pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->SetWindowText(szLan);
            g_StringLanType(szLan, "图片备份", "Backup");
            pDlgRemotPlay->GetDlgItem(IDC_BTN_BACKUP)->SetWindowText(szLan);
            pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->ShowWindow(SW_HIDE);
            g_pMainDlg->AddLog(pDlgRemotPlay->m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetBackupProgress");
            break;
        }
        g_pMainDlg->AddLog(pDlgRemotPlay->m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetBackupProgress [%d]", dwState);


        if (dwState == 100)
        {
            g_StringLanType(szLan, "备份完成", "Succ to backup");
            pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->SetWindowText(szLan);
            g_StringLanType(szLan, "图片备份", "Backup");
            pDlgRemotPlay->GetDlgItem(IDC_BTN_BACKUP)->SetWindowText(szLan);
            pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->ShowWindow(SW_HIDE);
            break;
        }
        else if (dwState == 400)
        {
            g_StringLanType(szLan, "备份异常", "backup exception");
            pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->SetWindowText(szLan);
            g_StringLanType(szLan, "图片备份", "Backup");
            pDlgRemotPlay->GetDlgItem(IDC_BTN_BACKUP)->SetWindowText(szLan);
            pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->ShowWindow(SW_HIDE);
            break;
        }
        else if (dwState == 500)
        {
            g_StringLanType(szLan, "备份失败", "Failed to backup");
            pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->SetWindowText(szLan);
            g_StringLanType(szLan, "图片备份", "Backup");
            pDlgRemotPlay->GetDlgItem(IDC_BTN_BACKUP)->SetWindowText(szLan);
            pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->ShowWindow(SW_HIDE);
            break;
        }
        //进度值
        else if (dwState >= 0 && dwState < 100)
        {
            char szLanCn[128] = { 0 };
            char szLanEn[128] = { 0 };
            sprintf(szLanCn, "正在备份[%d]", dwState);
            sprintf(szLanEn, "backuping[%d]", dwState);
            g_StringLanType(szLan, szLanCn, szLanCn);
            pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->SetWindowText(szLan);
        }
        //中间过程
        else if (dwState == BACKUP_SEARCH_DEVICE)
        {
            g_StringLanType(szLan, "正在搜索备份设备", "searching backup device");
            pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->SetWindowText(szLan);
        }
        else if (dwState == BACKUP_SEARCH_FILE)
        {
            g_StringLanType(szLan, "正在搜索图片", "searching picture files");
            pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->SetWindowText(szLan);
        }
        //错误值
        else if (dwState >= BACKUP_TIME_SEG_NO_FILE)
        {
            char szLanCn[128] = { 0 };
            char szLanEn[128] = { 0 };
            sprintf(szLanCn, "备份失败, 错误值[%d]", dwState);
            sprintf(szLanEn, "Backup failed, ErrorCode[%d]", dwState);
            g_StringLanType(szLan, szLanCn, szLanEn);
            pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->SetWindowText(szLan);

            g_StringLanType(szLan, "图片备份", "Backup");
            pDlgRemotPlay->GetDlgItem(IDC_BTN_BACKUP)->SetWindowText(szLan);
            pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->ShowWindow(SW_HIDE);
            break;
        }
        else if (dwState == BACKUP_CHANGE_DEVICE)
        {
            g_StringLanType(szLan, "备份设备已满, 请更换设备继续备份", "Device of backup is full, change another device and continue backuping");
            pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->SetWindowText(szLan);
            g_StringLanType(szLan, "备份", "Backup");
            pDlgRemotPlay->GetDlgItem(IDC_BTN_BACKUP)->SetWindowText(szLan);
            pDlgRemotPlay->m_bBackuping = FALSE;
            break;
        }

        Sleep(100);
    }

    Sleep(2000);
    if (!NET_DVR_StopBackup(pDlgRemotPlay->m_lBackupHandle))
    {
        g_pMainDlg->AddLog(pDlgRemotPlay->m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetBackupProgress");
    }
    pDlgRemotPlay->m_lBackupHandle = -1;
    pDlgRemotPlay->m_bBackuping = FALSE;

    CloseHandle(g_pDlgRemoteFile->m_hBackupThread);
    g_pDlgRemoteFile->m_hBackupThread = NULL;

    return 0;
}
IMPLEMENT_DYNAMIC(CDlgJPEGPicDownloadMedical, CDialog)

CDlgJPEGPicDownloadMedical::CDlgJPEGPicDownloadMedical(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgJPEGPicDownloadMedical::IDD, pParent)
    , m_strStreamID(_T(""))
    , m_dwPicIntervalTime(0)
    , m_iDownloadPicByTimeSum(0)
    , m_csPatientID(_T(""))
{
    m_sCardNum = _T("");
    m_bChkCard = FALSE;
    m_ctDateStart = 0;
    m_ctDateStop = 0;
    m_ctTimeStart = 0;
    m_ctTimeStop = 0;
    m_bContinue = FALSE;
    m_bRetWithFaceRect = FALSE;
    m_sLicense = _T("");
    //}}AFX_DATA_INIT
    m_lBackupHandle = -1;
    m_bBackuping = FALSE;
    m_hBackupThread = NULL;
    memset(&m_struFindPictureParam, 0, sizeof(m_struFindPictureParam));
    memset(&m_struDiskList, 0, sizeof(m_struDiskList));
    m_iIPChanNum = 0;
    m_iChanNum = 0;
    m_lDownPicByTimeHandle = -1;
    m_lPort = -1;
}

CDlgJPEGPicDownloadMedical::~CDlgJPEGPicDownloadMedical()
{
}

void CDlgJPEGPicDownloadMedical::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_COUNTRY_TYPE, m_comCountry);
    DDX_Control(pDX, IDC_COMBO_REGION_TYPE, m_comRegion);
    DDX_Control(pDX, IDC_COMBO_HVT_TYPE, m_comHvtType);
    DDX_Control(pDX, IDC_COMBO_PROVINCE_TYPE, m_comProvince);
    DDX_Control(pDX, IDC_COMBO_DISK_LIST, m_comboDiskList);
    DDX_Control(pDX, IDC_SHOWJPEG, m_ShowJpegCtrl);
    DDX_Control(pDX, IDC_DOWNPROGRESS, m_downProgress);
    DDX_Control(pDX, IDC_REMOTEPICLIST, m_PicList);
    DDX_Control(pDX, IDC_PICTYPE, m_PicTypeCtrl);
    DDX_Control(pDX, IDC_COMBOPORT, m_ChannelCtrl);
    DDX_Text(pDX, IDC_CARDNUM, m_sCardNum);
    DDX_Check(pDX, IDC_CHECKCARD, m_bChkCard);
    DDX_DateTimeCtrl(pDX, IDC_DATESTART, m_ctDateStart);
    DDX_DateTimeCtrl(pDX, IDC_DATESTOP, m_ctDateStop);
    DDX_DateTimeCtrl(pDX, IDC_TIMESTART, m_ctTimeStart);
    DDX_DateTimeCtrl(pDX, IDC_TIMESTOP, m_ctTimeStop);
    DDX_Check(pDX, IDC_CHK_CONTINUE_BACKUP, m_bContinue);
    DDX_Text(pDX, IDC_EDIT_LICENSE, m_sLicense);
    DDX_Check(pDX, IDC_CHK_RET_WITH_FACE_RECT, m_bRetWithFaceRect);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_STREAM_ID, m_strStreamID);
    DDX_Text(pDX, IDC_EDIT_PIC_INTERVAL_TIME, m_dwPicIntervalTime);
    DDV_MinMaxUInt(pDX, m_dwPicIntervalTime, 0, 86400);
    DDX_Text(pDX, IDC_EDIT_DOWNLOAD_FILE_NUM, m_iDownloadPicByTimeSum);
    DDX_Control(pDX, IDC_COMBO_FILE_TYPE, m_comboFileType);
    DDX_Text(pDX, IDC_EDIT_PATIENT_ID, m_csPatientID);
}


BEGIN_MESSAGE_MAP(CDlgJPEGPicDownloadMedical, CDialog)
    ON_BN_CLICKED(IDC_SEARCHLIST, OnSearchlist)
    ON_BN_CLICKED(IDC_DOWNLOAD, OnDownload)
    ON_BN_CLICKED(IDC_CHECKCARD, OnCheckcard)
    ON_NOTIFY(NM_CLICK, IDC_REMOTEPICLIST, OnClickRemotepiclist)
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_BTN_BACKUP, OnBtnBackup)
    ON_CBN_SELCHANGE(IDC_COMBO_DISK_LIST, OnSelchangeComboDiskList)
    ON_BN_CLICKED(IDC_UPLOAD, OnUpload)
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD_PICTURE_BY_TIME, &CDlgJPEGPicDownloadMedical::OnBnClickedButtonDownloadPictureByTime)
    ON_MESSAGE(WM_MSG_GETDATA_FINISH, OnMsgDownloacPicByTimeFinish)
    ON_MESSAGE(WM_MSG_SAVE_PICTURE_FILE, OnMsgAddStaticBoxFileSum)
    ON_BN_CLICKED(IDC_BUTTON_STOP_DOWNLOAD, &CDlgJPEGPicDownloadMedical::OnBnClickedButtonStopDownload)
    ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgJPEGPicDownloadMedical 消息处理程序
static void CALLBACK g_fDownloadPictureByTimeCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CDlgJPEGPicDownloadMedical *pDlg = (CDlgJPEGPicDownloadMedical *)pUserData;
    if (pDlg == NULL)
    {
        return;
    }
    pDlg->ProcessDownloadPicByTimeCallbackData(dwType, lpBuffer, dwBufLen);
}

//void CDlgJPEGPicDownloadMedical::OnOK()
//{
//    // TODO: Add extra validation here
//
//    //CDialog::OnOK();
//}
//
//void CDlgJPEGPicDownloadMedical::OnCancel()
//{
//    // TODO: Add extra cleanup here
//
//    //CDialog::OnCancel();
//}

BOOL CDlgJPEGPicDownloadMedical::OnInitDialog()
{
    CDialog::OnInitDialog();
    CRect rc(0, 0, 0, 0);
    GetParent()->GetClientRect(&rc);
    ((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
    MoveWindow(&rc);

    // TODO: Add extra initialization here
    g_pDlgRemoteFile = this;

    lpPicture = NULL;
    m_bDown = FALSE;
    m_hFileThread = NULL;
    m_hGetThread = NULL;
    m_iFileNum = 0;
    m_lFileHandle = 0;
    nSelPics = 0;
    nDownPics = 0;
   // m_lServerID = -1;
    m_bSearchDown = FALSE;
    m_downProgress.SetRange(0, 100);
    m_downProgress.SetPos(0);

    m_ChannelCtrl.SetCurSel(1);
    m_iChannel = 0;
    m_PicList.SetExtendedStyle(m_PicList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

    char szLan[128] = { 0 };

    g_StringLanType(szLan, "图片名称", "pic name");
    m_PicList.InsertColumn(0, szLan, LVCFMT_LEFT, 140, -1);

    g_StringLanType(szLan, "图片大小", "pic size");
    m_PicList.InsertColumn(1, szLan, LVCFMT_LEFT, 60, -1);

    g_StringLanType(szLan, "图片时间", "pic time");
    m_PicList.InsertColumn(2, szLan, LVCFMT_LEFT, 110, -1);

    g_StringLanType(szLan, "卡号", "card num");
    m_PicList.InsertColumn(3, szLan, LVCFMT_LEFT, 80, -1);

    g_StringLanType(szLan, "图片类型", "pic type");
    m_PicList.InsertColumn(4, szLan, LVCFMT_LEFT, 80, -1);

    g_StringLanType(szLan, "子图坐标", "vca rect");
    m_PicList.InsertColumn(5, szLan, LVCFMT_LEFT, 100, -1);

    g_StringLanType(szLan, "图片状态", "EventSearchStatus");
    m_PicList.InsertColumn(6, szLan, LVCFMT_LEFT, 100, -1);

    g_StringLanType(szLan, "车标", "RecogResult");
    m_PicList.InsertColumn(7, szLan, LVCFMT_LEFT, 100, -1);

    g_StringLanType(szLan, "车牌号码", "License");
    m_PicList.InsertColumn(8, szLan, LVCFMT_LEFT, 100, -1);

    g_StringLanType(szLan, "图片所在CS的IP", "Picture location");
    m_PicList.InsertColumn(8, szLan, LVCFMT_LEFT, 100, -1);

    g_StringLanType(szLan, "端口号", "Port");
    m_PicList.InsertColumn(9, szLan, LVCFMT_LEFT, 100, -1);

    CTime time1 = CTime::GetCurrentTime();
    CTime time(time1.GetYear(), time1.GetMonth(), time1.GetDay(), 0, 0, 0);
    CTime time0(time1.GetYear(), time1.GetMonth(), time1.GetDay(), 23, 59, 59);
    m_ctDateStart = time;
    m_ctTimeStart = time;
    m_ctDateStop = time;
    m_ctTimeStop = time0;
    m_lStartChan = 0;

    m_PicTypeCtrl.ResetContent();

    g_StringLanType(szLan, "全部", "All");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(0, 0xff);

    g_StringLanType(szLan, "定时抓图", "Schedule");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(1, 0);

    g_StringLanType(szLan, "移动侦测", "Motion Detect");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(2, 1);

    g_StringLanType(szLan, "报警触发", "Alarm");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(3, 2);

    g_StringLanType(szLan, "报警|动测", "Alarm|Motion");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(4, 3);

    g_StringLanType(szLan, "报警&动测", "Alarm&Motion");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(5, 4);

    g_StringLanType(szLan, "手动抓图", "Manual Capture");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(6, 6);

    g_StringLanType(szLan, "智能报警", "VCA alarm");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(7, 9);

    g_StringLanType(szLan, "PIR报警", "PIR Alarm");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(8, 10);

    g_StringLanType(szLan, "无线报警", "Wireless alarm");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(9, 11);

    g_StringLanType(szLan, "呼救报警", "Call help alarm");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(10, 12);

    g_StringLanType(szLan, "预览时截图", "Preview capture");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(11, 0xa);

    g_StringLanType(szLan, "人脸检测报警", "Detect face alarm");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(12, 0xd);

    //#ifdef NET_DVR_GET_TRAVERSE_PLANE_DETECTION
    g_StringLanType(szLan, "越界侦测", "NULL");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(13, 0xe);
    //#endif //NET_DVR_GET_TRAVERSE_PLANE_DETECTION

    g_StringLanType(szLan, "区域入侵侦测", "Field detection alarm");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(14, 0xf);

    //2013-07-17场景变更侦测图片查询
    g_StringLanType(szLan, "场景变更侦测", "Scene Change detection alarm");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(15, 0x10);

    g_StringLanType(szLan, "设备本地回放时截图", "capture in device playback");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(16, 0x11);

    g_StringLanType(szLan, "智能侦测", "intelligent detection");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(17, 0x12);

    g_StringLanType(szLan, "进入区域侦测", "Enter region detection");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(18, 0x13);

    g_StringLanType(szLan, "离开区域侦测", "Leave region detection");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(19, 0x14);

    g_StringLanType(szLan, "徘徊侦测", "Hovering detection");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(20, 0x15);

    g_StringLanType(szLan, "人员聚集侦测", "Researchers gathered detection");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(21, 0x16);

    g_StringLanType(szLan, "快速运动侦测", "Fast motion detection");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(22, 0x17);

    g_StringLanType(szLan, "停车侦测", "Parking detection");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(23, 0x18);

    g_StringLanType(szLan, "物品遗留侦测", "Goods Legacy Detection");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(24, 0x19);

    g_StringLanType(szLan, "物品拿取侦测", "Goods Take Detection");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(25, 0x1a);

    g_StringLanType(szLan, "车牌侦测", "License Detection");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(26, 0x1b);

    g_StringLanType(szLan, "混行检测", "HVT Detection");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(27, 0x1c);

    g_StringLanType(szLan, "取证事件", "Evidence");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(28, 0x1d);

    g_StringLanType(szLan, "火点检测", "Fire Detection");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(29, 0x1e);

    g_StringLanType(szLan, "防破坏检测", "VandalProof Detection");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(30, 0x1f);

    g_StringLanType(szLan, "船只检测", "Ships Detection");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(31, 0x20);

    g_StringLanType(szLan, "测温预警", "Temperature Warning");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(32, 0x21);

    g_StringLanType(szLan, "测温报警", "Temperature Alarm");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(33, 0x22);


    g_StringLanType(szLan, "温差报警", "Temperature Diff Alarm");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(34, 0x23);

    g_StringLanType(szLan, "违停检测", "Illegal park check");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(35, 0x24);

    g_StringLanType(szLan, "人脸抓拍", "Face snap");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(36, 0x25);

    g_StringLanType(szLan, "离线测温报警", "Temperature Offline Alarm");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(37, 0x26);


    g_StringLanType(szLan, "起身检测", "Get up");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(38, 0x2a);

    g_StringLanType(szLan, "折线攀高", "Adv ReachHeight");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(39, 0x2b);

    g_StringLanType(szLan, "如厕超时", "Toilet Tarry");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(40, 0x2c);

    g_StringLanType(szLan, "安全帽检测", "Safety Helmet");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(41, 0x2d);

    g_StringLanType(szLan, "周界抓拍", "Perimeter Capture");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(42, 0x2e);

    g_StringLanType(szLan, "人体目标抓拍", "Human Recognition");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(43, 0x2f);

    g_StringLanType(szLan, "人脸抓拍建模", "Face Snap Modeling");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(44, 0x30);

    g_StringLanType(szLan, "混合目标检测", "Mixed Target Detection");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(45, 0x31);

    g_StringLanType(szLan, "防区报警", "AlarmIn Alarm");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(46, 0x32);

    g_StringLanType(szLan, "紧急求助报警", "EmergencyCall");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(47, 0x33);

    g_StringLanType(szLan, "业务咨询", "Consult Alarm");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(48, 0x34);

    g_StringLanType(szLan, "非法摆摊", "unregistered Street Vendor");
    m_PicTypeCtrl.AddString(szLan);
    m_PicTypeCtrl.SetItemData(49, 0x35);

    m_PicTypeCtrl.SetCurSel(0);

    m_comboFileType.ResetContent();

    g_StringLanType(szLan, "I帧", "I Frame");
    m_comboFileType.InsertString(0, szLan);

    g_StringLanType(szLan, "图片", "Picture");
    m_comboFileType.InsertString(1, szLan);

    m_comboFileType.SetCurSel(0);

    UpdateData(FALSE);
    CheckInitParam();
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

/*********************************************************
Function:	ConverPictureFun
Desc:		callback function of capture
Input:		nPort,port; pBuf, image buffer; nSize,image size; nWidth,image width; nHeight,image height; nType,type;
Output:
Return:
**********************************************************/
static void CALLBACK ConverPictureFun(long nPort, char * pBuf, long nSize, FRAME_INFO * pFrameInfo, long nReserved1, long nReserved2)
{
    CTime csbegin = CTime::GetCurrentTime();
    CString csPath, csDir;
    CTime time = CTime::GetCurrentTime();
    csPath.Format("%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[g_pDlgRemoteFile->m_iDeviceIndex].chDeviceIP);
    if (GetFileAttributes(csPath) != FILE_ATTRIBUTE_DIRECTORY)
    {
        CreateDirectory(csPath, NULL);
    }
    csDir.Format("%s\\%d_%d_%d_%d_%d_%d_%d_%d.jpg", csPath, lNum, time.GetYear(),
        time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond(), time.GetTickCount());
    if (!PlayM4_ConvertToJpegFile(pBuf, nSize, pFrameInfo->nWidth, pFrameInfo->nHeight, pFrameInfo->nType, csDir.GetBuffer(csDir.GetLength())))
    {
        g_pMainDlg->AddLog(g_pDlgRemoteFile->m_iDeviceIndex, OPERATION_FAIL_T, "PlayM4_ConvertToJpegFile");
    }
    else
    {
        lNum++;
        g_pMainDlg->AddLog(g_pDlgRemoteFile->m_iDeviceIndex, OPERATION_SUCC_T, "PlayM4_ConvertToJpegFile[%s]", csDir);
    }
    CTime csEnd = CTime::GetCurrentTime();
    CString cstem;
    cstem.Format("%d\n", csbegin.GetTickCount() - csEnd.GetTickCount());
    OutputDebugString(cstem);
}

LRESULT CDlgJPEGPicDownloadMedical::OnMsgDownloacPicByTimeFinish(WPARAM wParam, LPARAM lParam)
{
    NET_DVR_StopRemoteConfig(m_lDownPicByTimeHandle);
    m_lDownPicByTimeHandle = -1;
    if (m_lPort >= 0)
    {
        if (!PlayM4_InputData(m_lPort, NULL, -1))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, PLAY_FAIL_T, "PlayM4_InputData err[%d]", PlayM4_GetLastError(m_lPort));
            Sleep(1);
        }
        else
        {
            Sleep(5);
        }
        Sleep(1000);
        PlayM4_FreePort(m_lPort);
        m_lPort = -1;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_THUMBNAILS Get finish");
    return 0;
}

LRESULT CDlgJPEGPicDownloadMedical::OnMsgAddStaticBoxFileSum(WPARAM wParam, LPARAM lParam)
{
    UpdateData(TRUE);
    LPNET_DVR_THUMBNAILS_RESULT lpFindPictureData = (LPNET_DVR_THUMBNAILS_RESULT)wParam;
    if (lpFindPictureData->dwFileSize <= 0)
    {
        return 0;
    }
    if (lpFindPictureData->byResultDataType == NET_DVR_SYSHEAD)
    {
        if (m_lPort < 0)
        {
            //PlayM4_FreePort(lPort);
            if (!PlayM4_GetPort(&m_lPort))
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, PLAY_FAIL_T, "PlayM4_GetPort");
                return 0;
            }
            else
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, PLAY_SUCC_T, "PlayM4_GetPort");
            }
        }
        //start player
        if (!PlayM4_OpenStream(m_lPort, (BYTE *)lpFindPictureData->pBuffer, lpFindPictureData->dwFileSize, 2 * 1024 * 1024))
        {
            m_lPort = -1;
            g_pMainDlg->AddLog(m_iDeviceIndex, PLAY_FAIL_T, "PlayM4_OpenStream err[%d]", PlayM4_GetLastError(m_lPort));
            return 0;
        }
        if (!PlayM4_SetDecCallBack(m_lPort, ConverPictureFun))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, PLAY_FAIL_T, "PlayM4_SetDisplayCallBack err[%d]", PlayM4_GetLastError(m_lPort));
        }
        if (!PlayM4_SetDecodeFrameType(m_lPort, 1))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, PLAY_FAIL_T, "PlayM4_SetDecodeFrameType err[%d]", PlayM4_GetLastError(m_lPort));
        }
        if (!PlayM4_SetDisplayBuf(m_lPort, 1))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, PLAY_FAIL_T, "PlayM4_SetDisplayBuf err[%d]", PlayM4_GetLastError(m_lPort));
        }
        if (!PlayM4_Play(m_lPort, NULL))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, PLAY_FAIL_T, "PlayM4_Play err[%d]", PlayM4_GetLastError(m_lPort));
        }
        if (!PlayM4_Fast(m_lPort))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, PLAY_FAIL_T, "PlayM4_Fast err[%d]", PlayM4_GetLastError(m_lPort));
        }
        if (!PlayM4_Fast(m_lPort))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, PLAY_FAIL_T, "PlayM4_Fast err[%d]", PlayM4_GetLastError(m_lPort));
        }
        if (!PlayM4_Fast(m_lPort))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, PLAY_FAIL_T, "PlayM4_Fast err[%d]", PlayM4_GetLastError(m_lPort));
        }
        if (!PlayM4_Fast(m_lPort))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, PLAY_FAIL_T, "PlayM4_Fast err[%d]", PlayM4_GetLastError(m_lPort));
        }
    }
    else if (lpFindPictureData->byResultDataType == 0)
    {
        if (lpFindPictureData->dwFileSize > 0 && m_lPort != -1)
        {
            int iTemp = 0;
            while (iTemp < 3)
            {
                if (!PlayM4_InputData(m_lPort, (BYTE*)lpFindPictureData->pBuffer, lpFindPictureData->dwFileSize))
                {
                    g_pMainDlg->AddLog(m_iDeviceIndex, PLAY_FAIL_T, "PlayM4_InputData err[%d]", PlayM4_GetLastError(m_lPort));
                    iTemp++;
                    Sleep(1);
                }
                else
                {
                    break;
                }
            }
            Sleep(50);
            m_iDownloadPicByTimeSum++;
        }
    }
    else if (lpFindPictureData->byResultDataType == 2)
    {
        CString csPath, csDir;
        csPath.Format("%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[g_pDlgRemoteFile->m_iDeviceIndex].chDeviceIP);
        if (GetFileAttributes(csPath) != FILE_ATTRIBUTE_DIRECTORY)
        {
            CreateDirectory(csPath, NULL);
        }
        csDir.Format("%s\\%d_%d_%d_%d_%d_%d_%d_%d_%d.jpg", csPath, m_iDownloadPicByTimeSum, lpFindPictureData->struTime.wYear,
            lpFindPictureData->struTime.byMonth, lpFindPictureData->struTime.byDay, lpFindPictureData->struTime.byHour, lpFindPictureData->struTime.byMinute,
            lpFindPictureData->struTime.bySecond, (lpFindPictureData->struTime.cTimeDifferenceH - '\0'), (lpFindPictureData->struTime.cTimeDifferenceM - '\0'));
        CFile file(csDir, CFile::modeCreate | CFile::modeWrite);
        file.Write(lpFindPictureData->pBuffer, lpFindPictureData->dwFileSize);
        file.Close();
        g_pMainDlg->AddLog(g_pDlgRemoteFile->m_iDeviceIndex, OPERATION_SUCC_T, "GetJpegFile[%s]", csDir);
        m_iDownloadPicByTimeSum++;
    }

    if (lpFindPictureData->pBuffer != NULL)
    {
        delete[](lpFindPictureData->pBuffer);
        lpFindPictureData->pBuffer = NULL;
    }

    if (lpFindPictureData != NULL)
    {
        delete lpFindPictureData;
        lpFindPictureData = NULL;
    }

    UpdateData(FALSE);
    return 0;
}

void CDlgJPEGPicDownloadMedical::ProcessDownloadPicByTimeCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{
    CString strItem = "";
    if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        char *pDataBuf = new char[sizeof(NET_DVR_THUMBNAILS_RESULT)];
        if (pDataBuf == NULL)
        {
            dwType = NET_SDK_CALLBACK_STATUS_FAILED;
        }
        memset(pDataBuf, 0, sizeof(NET_DVR_THUMBNAILS_RESULT));
        memcpy(pDataBuf, lpBuffer, sizeof(NET_DVR_THUMBNAILS_RESULT));

        LPNET_DVR_THUMBNAILS_RESULT pThumbnailsResultTemp = (NET_DVR_THUMBNAILS_RESULT*)pDataBuf;
        pThumbnailsResultTemp->pBuffer = NULL;
        LPNET_DVR_THUMBNAILS_RESULT pThumbnailsResultCfg = (NET_DVR_THUMBNAILS_RESULT*)lpBuffer;

        if (pThumbnailsResultCfg->dwFileSize != 0)
        {
            pThumbnailsResultTemp->pBuffer = new char[pThumbnailsResultCfg->dwFileSize];
            if (pThumbnailsResultTemp->pBuffer == NULL)
            {
                return;
            }
            memset(pThumbnailsResultTemp->pBuffer, 0, pThumbnailsResultCfg->dwFileSize);
            memcpy(pThumbnailsResultTemp->pBuffer, pThumbnailsResultCfg->pBuffer, pThumbnailsResultCfg->dwFileSize);
        }
        //PostMessage(WM_MSG_SAVE_PICTURE_FILE, (WPARAM)pDataBuf, 0);

    }
    else if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
    {
        DWORD dwStatus = *(DWORD*)lpBuffer;
        if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            //PostMessage(WM_MSG_GETDATA_FINISH, 0, 0);
        }
        else if (dwStatus == NET_SDK_CALLBACK_STATUS_FAILED)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_THUMBNAILS STATUS_FAILED, Error code %d", NET_DVR_GetLastError());
        }
    }
}

BOOL CDlgJPEGPicDownloadMedical::GetDiskList(NET_DVR_DISKABILITY_LIST &struDiskList)
{
    memset(&m_struDiskList, 0, sizeof(m_struDiskList));
    if (!NET_DVR_GetDiskList(m_lServerID, &struDiskList))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetDiskList");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetDiskList");
        return TRUE;
    }
}

void CDlgJPEGPicDownloadMedical::OnSearchlist()
{
    // TODO: Add your control notification handler code here
    char szLan[128] = { 0 };

    UpdateData(TRUE);
    if (m_lServerID == -1)
    {
        g_StringLanType(szLan, "请选择服务器", "Please select server!");
        AfxMessageBox(szLan);
        return;
    }
    if (!m_bSearchDown)
    {

        GetFindPictureParamFromWnd();

        m_lFileHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_SDK_FINDMEDICALPICTURE, &m_struFindPictureParam, sizeof(m_struFindPictureParam), NULL, NULL);

        if (m_lFileHandle < 0)
        {
            m_bSearchDown = FALSE;
            g_StringLanType(szLan, "获取图片列表失败", "Get picture list failed!");
            AfxMessageBox(szLan);
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_SDK_FINDMEDICALPICTURE");
            return;
        }
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_SDK_FINDMEDICALPICTURE");

        m_PicList.DeleteAllItems();
        m_iFileNum = 0;
        DWORD dwThreadId;
        if (m_hFileThread == NULL)
        {
            m_hFileThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(SearchPicThread), this, 0, &dwThreadId);
        }
        if (m_hFileThread == NULL)
        {
            g_StringLanType(szLan, "创建线程失败", "Open thread failed!");
            AfxMessageBox(szLan);
            return;
        }
        m_bSearchDown = TRUE;
        g_StringLanType(szLan, "停止搜索", "Stop search");
        GetDlgItem(IDC_SEARCHLIST)->SetWindowText(szLan);
        GetDlgItem(IDC_STATICSTATE)->ShowWindow(SW_SHOW);
    }
    else
    {
        m_bSearchDown = FALSE;
        if (m_lFileHandle != -1)
        {
            NET_DVR_StopRemoteConfig(m_lFileHandle);
        }
        CloseHandle(m_hFileThread);
        m_hFileThread = NULL;
        g_StringLanType(szLan, "查找", "Search");
        GetDlgItem(IDC_SEARCHLIST)->SetWindowText(szLan);
        GetDlgItem(IDC_STATICSTATE)->ShowWindow(SW_HIDE);
        g_StringLanType(szLan, "检索到图片数目:", "Search picture sum:");
        CString tempstring;
        tempstring.Format("%s[%d]", szLan, m_iFileNum);
        AfxMessageBox(tempstring);
        m_iFileNum = 0;
    }
}

void CDlgJPEGPicDownloadMedical::OnDownload()
{
    UpdateData(TRUE);
    char szLan[128] = { 0 };

    if (!m_bDown)
    {
        pos = m_PicList.GetFirstSelectedItemPosition();
        if (pos == NULL)
        {
            g_StringLanType(szLan, "请选择文件!", "Please select the file!");
            AfxMessageBox(szLan);
            return;
        }
        m_bDown = TRUE;
        nSelPics = m_PicList.GetSelectedCount();
        nDownPics = 0;

        DWORD dwThreadId;
        if (!m_hGetThread)
        {
            m_hGetThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetPicThread), this, 0, &dwThreadId);
        }
        else
        {
            TerminateThread(m_hGetThread, 0);
            m_hGetThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetPicThread), this, 0, &dwThreadId);
        }
        GetDlgItem(IDC_DOWNLOAD)->SetWindowText("Stop download");
        GetDlgItem(IDC_STATICSTATE2)->ShowWindow(SW_SHOW);
    }
    else
    {
        if (!m_hGetThread)
        {
            g_StringLanType(szLan, "请选择文件!", "Please select the file!");
            AfxMessageBox(szLan);
            return;
        }
        m_bDown = FALSE;
    }
    UpdateData(FALSE);
}

void CDlgJPEGPicDownloadMedical::OnCheckcard()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if (m_bChkCard)
    {
        GetDlgItem(IDC_CARDNUM)->EnableWindow(TRUE);
    }
    else
    {
        GetDlgItem(IDC_CARDNUM)->EnableWindow(FALSE);
    }
    UpdateData(FALSE);
}

void CDlgJPEGPicDownloadMedical::OnClickRemotepiclist(NMHDR* pNMHDR, LRESULT* pResult)
{
    // TODO: Add your control notification handler code here
    POSITION tempPos;
    tempPos = m_PicList.GetFirstSelectedItemPosition();
    if (tempPos == NULL)
    {
        return;
    }
    CString csFileName;
    CString csPicTime;
    CString csCardNum;
    CString csTemp, csDir;
    char nFileName[256];
    CString csMessage;
    int fileselpos = 0;

    fileselpos = m_PicList.GetNextSelectedItem(tempPos);
    csFileName.Format("%s", m_PicList.GetItemText(fileselpos, 0));
    if (csFileName.IsEmpty())
    {
        return;
    }
    csPicTime.Format("%s", m_PicList.GetItemText(fileselpos, 2));
    csCardNum.Format("%s", m_PicList.GetItemText(fileselpos, 3));
    sprintf(filenamedownload, "%s", csFileName);
    csDir.Format("%s\\", g_struLocalParam.chDownLoadPath);


    char *sSavedFileBuf = NULL;
    DWORD dwRetLen = 0;

    NET_DVR_PIC_PARAM struPicParam = { 0 };
    struPicParam.pDVRFileName = const_cast<char*>((LPCSTR)csFileName);
    struPicParam.pSavedFileBuf = sSavedFileBuf;
    struPicParam.lpdwRetLen = &dwRetLen;
    CString szIp;
    CString szPort;
    szIp.Format("%s", m_PicList.GetItemText(fileselpos, 8));
    //ipv4
    if (!g_ValidIPv6((BYTE*)(LPCSTR)szIp))
    {
        sprintf(struPicParam.struAddr.struIP.sIpV4, "%s", szIp);
    }
    else
    {
        sprintf((char *)struPicParam.struAddr.struIP.byIPv6, "%s", szIp);
    }

    szPort = m_PicList.GetItemText(fileselpos, 9);
    struPicParam.struAddr.wPort = _ttoi(szPort);

    if (szIp.GetLength() != 0)
    {
        sprintf(nFileName, "%s%s_%02d_D%s_%s_%d.jpg", csDir, szIp, m_iChannel, csPicTime, csCardNum, fileselpos + 1);
    }
    else
    {
        BOOL bShowIpv6 = g_ValidIPv6((BYTE*)g_struDeviceInfo[m_iDeviceIndex].chDeviceIP);
        if (bShowIpv6)
        {
            sprintf(nFileName, "%s_ipv6_%02d_D%s_%s_%d.jpg", csDir, m_iChannel, csPicTime, csCardNum, fileselpos + 1);
        }
        else
        {
            sprintf(nFileName, "%s%s_%02d_D%s_%s_%d.jpg", csDir, g_struDeviceInfo[m_iDeviceIndex].chDeviceIP, m_iChannel, csPicTime, csCardNum, fileselpos + 1);
        }
    }

    if (NET_DVR_GetPicture_V50(m_lServerID, &struPicParam))
    {
        if (0 != dwRetLen)
        {
            sSavedFileBuf = new char[dwRetLen];
            memset(sSavedFileBuf, 0, dwRetLen);
            struPicParam.pSavedFileBuf = sSavedFileBuf;
            struPicParam.dwBufLen = dwRetLen;

            if (NET_DVR_GetPicture_V50(m_lServerID, &struPicParam))
            {
                if (NULL != sSavedFileBuf && 0 != dwRetLen)
                {
                    char cFilename[256] = { 0 };
                    HANDLE hFile;
                    DWORD dwReturn;

                    hFile = CreateFile(nFileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                    if (hFile == INVALID_HANDLE_VALUE)
                    {
                        if (NULL != sSavedFileBuf)
                        {
                            delete[]sSavedFileBuf;
                            sSavedFileBuf = NULL;
                        }
                        return;
                    }
                    WriteFile(hFile, sSavedFileBuf, dwRetLen, &dwReturn, NULL);
                    CloseHandle(hFile);
                    hFile = NULL;
                }
            }
            else
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetPicture_V50");
                if (NULL != sSavedFileBuf)
                {
                    delete[]sSavedFileBuf;
                    sSavedFileBuf = NULL;
                }
                *pResult = 0;
                return;
            }

            if (NULL != sSavedFileBuf)
            {
                delete[]sSavedFileBuf;
                sSavedFileBuf = NULL;
            }
        }
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetPicture_V50");
    }

    //BOOL bShowIpv6 = g_ValidIPv6((BYTE*)g_struDeviceInfo[m_iDeviceIndex].chDeviceIP);
    //if (bShowIpv6)
    //{
    //    sprintf(nFileName, "%s_ipv6_%02d_D%s_%sjpg", csDir, m_iChannel, csPicTime, csCardNum);
    //}
    //else
    //{
    //    sprintf(nFileName, "%s%s_%02d_D%s_%sjpg", csDir, g_struDeviceInfo[m_iDeviceIndex].chDeviceIP, m_iChannel, csPicTime, csCardNum);
    //}



    //if (!NET_DVR_GetPicture(m_lServerID, filenamedownload, nFileName))
    //{
    //    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetPicture");
    //    *pResult = 0;
    //    return;
    //}

    CRect rc;
    CDC* pDC = m_ShowJpegCtrl.GetDC();
    m_ShowJpegCtrl.GetClientRect(&rc);
    pDC->SetViewportOrg(rc.left, rc.top);
    rc.bottom = -rc.bottom;
    if (!lpPicture)
    {
        lpPicture = new CPicture;
    }
    lpPicture->LoadPicture(nFileName, pDC->m_hDC, abs(rc.Width()), abs(rc.Height()));

    DeleteFile(nFileName);
    *pResult = 0;
}

void CDlgJPEGPicDownloadMedical::F_Close()
{
    if (m_hGetThread)
    {
        TerminateThread(m_hGetThread, 0);
        CloseHandle(m_hGetThread);
        m_hGetThread = NULL;
    }

    if (m_hFileThread)
    {
        TerminateThread(m_hFileThread, 0);
        CloseHandle(m_hFileThread);
        m_hFileThread = NULL;
    }

    if (lpPicture)
    {
        lpPicture->FreePicture();
        delete lpPicture;
        lpPicture = NULL;
    }
}

void CDlgJPEGPicDownloadMedical::OnDestroyResource()
{
    if (m_lDownPicByTimeHandle != -1)
    {
        NET_DVR_StopRemoteConfig(m_lDownPicByTimeHandle);
        m_lDownPicByTimeHandle = -1;
    }
    if (m_lPort >= 0)
    {
        PlayM4_FreePort(m_lPort);
        m_lPort = -1;
    }
    CDialog::OnDestroy();

    // TODO: Add your message handler code here

}
/*********************************************************
Function:	CheckInitParam
Desc:		check device parameters and initialize dialog parameters
Input:
Output:
Return:	    TRUE,check correct, parameters initialized; FALSE,check error, not initialized;
**********************************************************/
BOOL CDlgJPEGPicDownloadMedical::CheckInitParam()
{
    int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    if (iDeviceIndex == -1)
    {
        UpdateData(FALSE);
        return FALSE;
    }
    if (m_iDeviceIndex == -1 || m_iDeviceIndex != iDeviceIndex)
    {
        // m_iChanIndex = -1;
    }
    int iChanIndex = g_pMainDlg->GetCurChanIndex();
    if (iChanIndex == -1)
    {
        iChanIndex = 0;
    }

    UpdateData(TRUE);
    char szLan[128] = { 0 };

    m_iDeviceIndex = iDeviceIndex;
    m_lServerID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
    m_iChanNum = g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum;
    m_iIPChanNum = g_struDeviceInfo[m_iDeviceIndex].iIPChanNum;
    m_lServerType = g_struDeviceInfo[m_iDeviceIndex].iDeviceType;
    m_lStartChan = g_struDeviceInfo[m_iDeviceIndex].iStartChan;

    m_ChannelCtrl.ResetContent();
    DWORD dwIndex = 0;

    for (int i = 0; i< g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum; i++)
    {
        if (g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].bEnable)
        {
            m_ChannelCtrl.AddString(g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].chChanName);
            m_ChannelCtrl.SetItemData(dwIndex, g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChannelNO);
            dwIndex++;
        }
    }

    m_iChannel = 0;
    m_ChannelCtrl.SetCurSel(m_iChannel);

    if (m_lServerID < 0)
    {
        UpdateData(FALSE);
        return FALSE;
    }

    GetDiskList(m_struDiskList);
    m_comboDiskList.ResetContent();
    for (int j = 0; j < m_struDiskList.dwNodeNum; j++)
    {
        m_comboDiskList.AddString((char*)m_struDiskList.struDescNode[j].byDescribe);
        m_comboDiskList.SetItemData(j, m_struDiskList.struDescNode[j].iValue);
    }
    m_comboDiskList.SetCurSel(0);
    OnSelchangeComboDiskList();

    UpdateData(FALSE);
    return TRUE;
}
/*********************************************************
Function:	SetParentWnd
Desc:		transmit the handle of parent dialog box
Input:	hhWnd, pointer to handle array
Output:
Return:
**********************************************************/
void CDlgJPEGPicDownloadMedical::SetParentWnd(HWND *hhWnd, int iParentNum)
{
    VERIFY(iParentNum == 2);
    m_hPareDlgWnd = hhWnd[0];
    m_hPareTabWnd = hhWnd[1];
}

void CDlgJPEGPicDownloadMedical::GetFindPictureParamFromWnd()
{
    //struPictureParam.lChannel = m_ChannelCtrl.GetCurSel()+m_lStartChan;
    int iChanIndex = g_pMainDlg->GetCurChanIndex();
    m_struFindPictureParam.lChannel = m_iChannel + 1;
    m_struFindPictureParam.dwSize = sizeof(NET_DVR_FIND_PICTURE_MEDICAL_PARAM);
    m_struFindPictureParam.byFileType = m_PicTypeCtrl.GetItemData(m_PicTypeCtrl.GetCurSel());
    //	m_struFindPictureParam.byRetWithFaceRect = m_bRetWithFaceRect;
    m_struFindPictureParam.byNeedCard = m_bChkCard;
    if (35 == m_comProvince.GetCurSel())
    {
        m_struFindPictureParam.byProvince = 0xff;
    }
    else
    {
        m_struFindPictureParam.byProvince = m_comProvince.GetCurSel();
    }
	strncpy(m_struFindPictureParam.szPatientID, m_csPatientID.GetBuffer(0), PATIENTID_LEN - 1);
    m_struFindPictureParam.struStartTime.dwYear = (WORD)m_ctDateStart.GetYear();
    m_struFindPictureParam.struStartTime.dwMonth = (WORD)m_ctDateStart.GetMonth();
    m_struFindPictureParam.struStartTime.dwDay = (WORD)m_ctDateStart.GetDay();
    m_struFindPictureParam.struStartTime.dwHour = (char)m_ctTimeStart.GetHour();
    m_struFindPictureParam.struStartTime.dwMinute = (char)m_ctTimeStart.GetMinute();
    m_struFindPictureParam.struStartTime.dwSecond = (char)m_ctTimeStart.GetSecond();
    m_struFindPictureParam.struStopTime.dwYear = (WORD)m_ctDateStop.GetYear();
    m_struFindPictureParam.struStopTime.dwMonth = (WORD)m_ctDateStop.GetMonth();
    m_struFindPictureParam.struStopTime.dwDay = (WORD)m_ctDateStop.GetDay();
    m_struFindPictureParam.struStopTime.dwHour = (char)m_ctTimeStop.GetHour();
    m_struFindPictureParam.struStopTime.dwMinute = (char)m_ctTimeStop.GetMinute();
    m_struFindPictureParam.struStopTime.dwSecond = (char)m_ctTimeStop.GetSecond();

}

/******************************************
函数:	ProcessFileSize
描述:
输入:
输出:
返回值:
******************************************/
DWORD CDlgJPEGPicDownloadMedical::ProcessFileSize(CString csFileSize)
{
    DWORD dwFileSize = 0;
    if (csFileSize[csFileSize.GetLength() - 1] == 'M')
    {
        dwFileSize = atoi(csFileSize.GetBuffer(csFileSize.GetLength() - 1));
        dwFileSize *= (1024 * 1024);
    }
    else if (csFileSize[csFileSize.GetLength() - 1] == 'K')
    {
        dwFileSize = atoi(csFileSize.GetBuffer(csFileSize.GetLength() - 1));
        dwFileSize *= 1024;
    }
    else
    {
        dwFileSize = atoi(csFileSize.GetBuffer(csFileSize.GetLength()));
    }
    return dwFileSize;
}

BOOL CDlgJPEGPicDownloadMedical::GetBackupPictureParamFromWnd_FILE(NET_DVR_BACKUP_PICTURE_PARAM &struBackPicturParam)
{
    UpdateData(TRUE);

    CString csDiskDesc = "";
    char szLan[128] = { 0 };
    if (m_comboDiskList.GetCurSel() != CB_ERR)
    {
        m_comboDiskList.GetLBText(m_comboDiskList.GetCurSel(), csDiskDesc);
    }
    else
    {
        g_StringLanType(szLan, "请选择磁盘备份列表", "Please select backup disk");
        AfxMessageBox(szLan);
        return FALSE;
    }

    struBackPicturParam.dwSize = sizeof(struBackPicturParam);

    strncpy((char*)(struBackPicturParam.byDiskDes), (char*)csDiskDesc.GetBuffer(0), sizeof(struBackPicturParam.byDiskDes));
    struBackPicturParam.byContinue = m_bContinue;

    int iItemCount = 0;
    int iIndex = 0;
    POSITION pos = m_PicList.GetFirstSelectedItemPosition();
    CString csFileSize;
    CString csFileTime;
    while ((pos != NULL) && (iItemCount < ARRAY_SIZE(struBackPicturParam.struPicture)))
    {
        iIndex = m_PicList.GetNextSelectedItem(pos);
        sprintf(struBackPicturParam.struPicture[iItemCount].sFileName, "%s", m_PicList.GetItemText(iIndex, 0));

        csFileSize = m_PicList.GetItemText(iIndex, 1);
        struBackPicturParam.struPicture[iItemCount].dwFileSize = ProcessFileSize(csFileSize);

        csFileTime = m_PicList.GetItemText(iIndex, 2);
        sscanf(csFileTime, "%04d%02d%02d%02d%02d%02d", &(struBackPicturParam.struPicture[iItemCount].struTime.dwYear), \
            &(struBackPicturParam.struPicture[iItemCount].struTime.dwMonth), \
            &(struBackPicturParam.struPicture[iItemCount].struTime.dwDay), \
            &(struBackPicturParam.struPicture[iItemCount].struTime.dwHour), \
            &(struBackPicturParam.struPicture[iItemCount].struTime.dwMinute), \
            &(struBackPicturParam.struPicture[iItemCount].struTime.dwSecond));

        iItemCount++;
    }
    struBackPicturParam.dwPicNum = iItemCount;
    return TRUE;
}

void CDlgJPEGPicDownloadMedical::OnBtnBackup()
{
    char szLan[256] = { 0 };
    if (!m_bBackuping)
    {
        //backup by file
        NET_DVR_BACKUP_PICTURE_PARAM struBackupPictureParam = { 0 };
        if (!GetBackupPictureParamFromWnd_FILE(struBackupPictureParam))
        {
            return;
        }
        m_lBackupHandle = NET_DVR_BackupPicture(m_lServerID, &struBackupPictureParam);

        if (m_lBackupHandle == -1)
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_BackupPicture");
            return;
        }
        else
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_BackupPicture");
        }

        DWORD dwThreadId = 0;
        if (m_hBackupThread == NULL)
        {
            m_hBackupThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetBackupPicThread), this, 0, &dwThreadId);
        }
        if (m_hBackupThread == NULL)
        {
            char szLan[256] = { 0 };
            g_StringLanType(szLan, "打开备份线程失败!", "Fail to open backup thread!");
            AfxMessageBox(szLan);
            return;
        }
        g_StringLanType(szLan, "停止备份", "Stop Bakcup");
        GetDlgItem(IDC_BTN_BACKUP)->SetWindowText(szLan);
        m_bBackuping = TRUE;
        GetDlgItem(IDC_STATIC_BACK_STATE)->ShowWindow(SW_SHOW);
    }
    else
    {
        if (m_hBackupThread)
        {
            TerminateThread(m_hBackupThread, 0);
        }

        CloseHandle(m_hBackupThread);
        m_hBackupThread = NULL;
        NET_DVR_StopBackup(m_lBackupHandle);
        g_StringLanType(szLan, "图片备份", "Backup");
        GetDlgItem(IDC_BTN_BACKUP)->SetWindowText(szLan);
        m_bBackuping = FALSE;
        GetDlgItem(IDC_STATIC_BACK_STATE)->ShowWindow(SW_HIDE);
    }
}

void CDlgJPEGPicDownloadMedical::OnSelchangeComboDiskList()
{
    DWORD dwDiskFreeSpace = m_struDiskList.struDescNode[m_comboDiskList.GetCurSel()].dwFreeSpace;
    char szLanCn[256] = { 0 };
    char szLanEn[256] = { 0 };
    char szLan[256] = { 0 };
    sprintf(szLanCn, "剩余磁盘空间%dM", dwDiskFreeSpace);
    sprintf(szLanEn, "Free Disk Spcace%dM", dwDiskFreeSpace);
    g_StringLanType(szLan, szLanCn, szLanEn);
    GetDlgItem(IDC_STATIC_BACKUP_DISK_SIZE)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_STATIC_BACKUP_DISK_SIZE)->SetWindowText(szLan);
}

void CDlgJPEGPicDownloadMedical::PostNcDestroy()
{

    CDialog::PostNcDestroy();
}

void CDlgJPEGPicDownloadMedical::OnBnClickedButtonDownloadPictureByTime()
{
    // TODO:  在此添加控件通知处理程序代码
    OnBnClickedButtonStopDownload();
    SetDlgItemText(IDC_EDIT_DOWNLOAD_FILE_NUM, "0");
    UpdateData(TRUE);
    NET_DVR_THUMBNAILS_COND struDownloadPictureByTimeCond = { 0 };
    struDownloadPictureByTimeCond.dwSize = sizeof(struDownloadPictureByTimeCond);

    struDownloadPictureByTimeCond.struStreamInfo.dwSize = sizeof(NET_DVR_STREAM_INFO);
    struDownloadPictureByTimeCond.struStreamInfo.dwChannel = m_ChannelCtrl.GetItemData(m_ChannelCtrl.GetCurSel());
    //sprintf((char*)struDownloadPictureByTimeCond.struStreamInfo.byID, "%s", m_strStreamID.GetBuffer(m_strStreamID.GetLength()));
    strncpy((char*)struDownloadPictureByTimeCond.struStreamInfo.byID, m_strStreamID.GetBuffer(0), sizeof(struDownloadPictureByTimeCond.struStreamInfo.byID));
    struDownloadPictureByTimeCond.bySearchDataType = m_comboFileType.GetCurSel();

    struDownloadPictureByTimeCond.struStartTime.wYear = m_ctDateStart.GetYear();
    struDownloadPictureByTimeCond.struStartTime.byMonth = m_ctDateStart.GetMonth();
    struDownloadPictureByTimeCond.struStartTime.byDay = m_ctDateStart.GetDay();
    struDownloadPictureByTimeCond.struStartTime.byHour = m_ctTimeStart.GetHour();
    struDownloadPictureByTimeCond.struStartTime.byMinute = m_ctTimeStart.GetMinute();
    struDownloadPictureByTimeCond.struStartTime.bySecond = m_ctTimeStart.GetSecond();

    struDownloadPictureByTimeCond.struStopTime.wYear = m_ctDateStop.GetYear();
    struDownloadPictureByTimeCond.struStopTime.byMonth = m_ctDateStop.GetMonth();
    struDownloadPictureByTimeCond.struStopTime.byDay = m_ctDateStop.GetDay();
    struDownloadPictureByTimeCond.struStopTime.byHour = m_ctTimeStop.GetHour();
    struDownloadPictureByTimeCond.struStopTime.byMinute = m_ctTimeStop.GetMinute();
    struDownloadPictureByTimeCond.struStopTime.bySecond = m_ctTimeStop.GetSecond();

    struDownloadPictureByTimeCond.dwIntervalTime = m_dwPicIntervalTime;

    m_lDownPicByTimeHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_GET_THUMBNAILS, &struDownloadPictureByTimeCond, sizeof(struDownloadPictureByTimeCond), g_fDownloadPictureByTimeCallback, this);
    if (m_lDownPicByTimeHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_THUMBNAILS");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_THUMBNAILS");
    }
}


void CDlgJPEGPicDownloadMedical::OnBnClickedButtonStopDownload()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    if (m_lDownPicByTimeHandle != -1)
    {
        NET_DVR_StopRemoteConfig(m_lDownPicByTimeHandle);
        m_lDownPicByTimeHandle = -1;
    }
    if (m_lPort >= 0)
    {
        if (!PlayM4_InputData(m_lPort, NULL, -1))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, PLAY_FAIL_T, "PlayM4_InputData err[%d]", PlayM4_GetLastError(m_lPort));
            Sleep(1);
        }
        else
        {
            Sleep(5);
        }
        Sleep(1000);
        PlayM4_FreePort(m_lPort);
        m_lPort = -1;
    }
    lNum = 0;
    UpdateData(FALSE);
}

void CDlgJPEGPicDownloadMedical::OnUpload()
{
    // TODO: Add your control notification handler code here
    CDlgPictureUpload dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_lChannel = m_ChannelCtrl.GetItemData(m_ChannelCtrl.GetCurSel());
    dlg.m_lDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
}


void CDlgJPEGPicDownloadMedical::OnBnClickedBtnMedical()
{
    // TODO:  在此添加控件通知处理程序代码
}


void CDlgJPEGPicDownloadMedical::OnClose()
{
    // TODO:  在此添加消息处理程序代码和/或调用默认值

    CDialog::OnClose();
}
