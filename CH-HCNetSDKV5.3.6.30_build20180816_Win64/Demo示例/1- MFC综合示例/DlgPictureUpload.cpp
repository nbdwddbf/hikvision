// DlgPictureUpload.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPictureUpload.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPictureUpload dialog


CDlgPictureUpload::CDlgPictureUpload(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPictureUpload::IDD, pParent)
    , m_csIp(_T(""))
    , m_dwPort(0)
{
	//{{AFX_DATA_INIT(CDlgPictureUpload)
	m_csFilePath = _T("");
	m_csPicUrl = _T("");
	m_bPicStruct = FALSE;
	m_date = COleDateTime::GetCurrentTime();
	m_time = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_lChannel = -1;
    m_lUploadHandle = -1;
    m_bUpLoading = FALSE;
	m_hUpLoadThread = NULL;
    m_pPicInfo = NULL;
    m_dwThreadId = 0 ;
    m_lDeviceIndex = -1;

    memset(&m_struPicInfo, 0, sizeof(m_struPicInfo));
}

CDlgPictureUpload::~CDlgPictureUpload()
{ 
    if (NULL != m_lUploadHandle)
    {
        NET_DVR_CloseUploadHandle(m_lUploadHandle);
    }

    if (NULL != m_pPicInfo)
    {
        delete []m_pPicInfo;
        m_pPicInfo = NULL;
    }
}

void CDlgPictureUpload::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgPictureUpload)
    DDX_Control(pDX, IDC_COMBO_PICTURE_TYPE, m_comPicType);
    DDX_Text(pDX, IDC_EDIT_FILE_PATH, m_csFilePath);
    DDX_Text(pDX, IDC_EDIT_PIC_URL, m_csPicUrl);
    DDX_Check(pDX, IDC_CHECK_PIC_STRUCT, m_bPicStruct);
    DDX_DateTimeCtrl(pDX, IDC_DATE, m_date);
    DDX_DateTimeCtrl(pDX, IDC_TIME, m_time);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_STATIC_STATUS, m_csIp);
    DDX_Text(pDX, IDC_EDIT_FILE_PORT, m_dwPort);
}


BEGIN_MESSAGE_MAP(CDlgPictureUpload, CDialog)
	//{{AFX_MSG_MAP(CDlgPictureUpload)
	ON_BN_CLICKED(IDC_BTN_FILE_PATH, OnBtnFilePath)
	ON_BN_CLICKED(IDC_BTN_PIC_UPLOAD, OnBtnPicUpload)
	ON_BN_CLICKED(IDC_CHECK_PIC_STRUCT, OnCheckPicStruct)
	ON_BN_CLICKED(IDC_BTN_PIC_DOWNLOAD, OnBtnPicDownload)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_PIC_DOWNLOADV50, &CDlgPictureUpload::OnBnClickedBtnPicDownloadv50)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPictureUpload message handlers

BOOL CDlgPictureUpload::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

    OnCheckPicStruct(); 
    
    m_comPicType.SetCurSel(0);
  
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPictureUpload::OnBtnFilePath() 
{
	// TODO: Add your control notification handler code here
    static char szFilter[] = "All File(*.*)|*.*||";
    CFileDialog dlg(TRUE,"*.*", NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter);
    if (dlg.DoModal() == IDOK)
    {
        m_csFilePath = dlg.GetPathName();
        UpdateData(FALSE);
	}
}

// void CDlgPictureUpload::ShowPicUrl(CString strUrl) 
// {
//     m_csPicUrl = strUrl;
//     UpdateData(FALSE);
// }

DWORD WINAPI CDlgPictureUpload::GetUpLoadFileThread(LPVOID pParam)
{
    CDlgPictureUpload *pThis = ( CDlgPictureUpload*)pParam;
    
    DWORD dwState = 0;
    DWORD dwProgress = 0;
    char szLan[256] = {0};
    
    
    while (TRUE)
    {
        dwState = NET_DVR_GetUploadState(pThis->m_lUploadHandle,&dwProgress);
        if (dwState == 1)
        {
            g_StringLanType(szLan, "上传成功", "Upload successfully");
            pThis->GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
            pThis->m_bUpLoading = FALSE;
            g_StringLanType(szLan,"上传","Upload");
            pThis->GetDlgItem(IDC_BTN_PIC_UPLOAD)->SetWindowText(szLan);
            pThis->m_bUpLoading = FALSE;

            NET_DVR_UPLOAD_FILE_RET struUploadFileRet = {0};
            if (NET_DVR_GetUploadResult(pThis->m_lUploadHandle, &struUploadFileRet, sizeof(struUploadFileRet)))
            {
                CString strUrl;
                strUrl.Format(_T("%s"), struUploadFileRet.sUrl);
                pThis->GetDlgItem(IDC_EDIT_PIC_URL)->SetWindowText(strUrl);
                //pThis->UpdateData(FALSE);
                //pThis->ShowPicUrl(strUrl);
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
                g_StringLanType(szLan,"上传","UpLoad");
                pThis->GetDlgItem(IDC_BTN_PIC_UPLOAD)->SetWindowText(szLan);
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
            g_StringLanType(szLan,"图片上传","UpLoad");
            pThis->GetDlgItem(IDC_BTN_PIC_UPLOAD)->SetWindowText(szLan);

            if (NULL != pThis->m_pPicInfo)
            {
                delete []pThis->m_pPicInfo;
                pThis->m_pPicInfo = NULL;
            }
            
        }
    }
    
    return FALSE;
}

void CDlgPictureUpload::OnBtnPicUpload() 
{
	// TODO: Add your control notification handler code here
    char szLan[128] = {0};
    if (m_bUpLoading == FALSE)
    {
        UpdateData(TRUE);
        char szFileName[MAX_PATH];
        strcpy(szFileName, m_csFilePath);
        CFile cFile;
        GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        if (!cFile.Open(szFileName, CFile::modeRead))
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
        memset(&m_struPicInfo, 0, sizeof(m_struPicInfo));
        m_struPicInfo.dwSize = sizeof(m_struPicInfo);
        m_struPicInfo.dwChannel = m_lChannel;
        m_struPicInfo.byPictureType = m_comPicType.GetCurSel();
        
        m_struPicInfo.struTime.wYear = m_date.GetYear();
        m_struPicInfo.struTime.byMonth = m_date.GetMonth();
        m_struPicInfo.struTime.byDay = m_date.GetDay();
        m_struPicInfo.struTime.byHour = m_time.GetHour();
        m_struPicInfo.struTime.byMinute = m_time.GetMinute();
        m_struPicInfo.struTime.bySecond = m_time.GetSecond();
        
        if (m_bPicStruct)
        {
            m_pPicInfo = new char[dwFileSize];
            cFile.Read(m_pPicInfo, dwFileSize);
            m_struPicInfo.sPictureBuffer = m_pPicInfo;
            m_struPicInfo.dwPictureLength = dwFileSize;

            cFile.Close();

            m_lUploadHandle = NET_DVR_UploadFile_V40(m_lServerID, UPLOAD_PICTURE_FILE, &m_struPicInfo, sizeof(m_struPicInfo), NULL, NULL, 0);
        }
        else
        {
            cFile.Close();
            
            m_lUploadHandle = NET_DVR_UploadFile_V40(m_lServerID, UPLOAD_PICTURE_FILE, &m_struPicInfo, sizeof(m_struPicInfo), szFileName, NULL, 0);
        }
     
        if (m_lUploadHandle < 0)
        {
   	    	g_StringLanType(szLan, "图片上传失败", "UPLOAD_PICTURE_FILE Upload Failed");
	    	sprintf(szLan, "%s %s %d", szLan, NET_DVR_GetErrorMsg(), NET_DVR_GetLastError());     
            AfxMessageBox(szLan);
            return;	
        }
        else
        {
            //AfxMessageBox("NET_SDK_DOWNLOAD_DATABASE_CONFIGURATION_FILE Upload Succ");
            
            //Sleep(1000);
            //NET_DVR_UploadClose(lHandle);
        }
        m_hUpLoadThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetUpLoadFileThread),this,0,&m_dwThreadId);
        if (m_hUpLoadThread  == NULL)
        {
            g_StringLanType(szLan, "打开长传文件线程失败!", "open UpLoad thread Fail!");
            AfxMessageBox(szLan);
            return;
        }
        g_StringLanType(szLan, "停止上传", "Stop UpLoad");
        GetDlgItem(IDC_BTN_PIC_UPLOAD)->SetWindowText(szLan);
        m_bUpLoading = TRUE;
    }
    else
    {
        NET_DVR_CloseUploadHandle(m_lUploadHandle);
        m_bUpLoading = FALSE;
        g_StringLanType(szLan,"图片上传","UpLoad");
        GetDlgItem(IDC_BTN_PIC_UPLOAD)->SetWindowText(szLan);
    }
	UpdateData(FALSE);
}

void CDlgPictureUpload::OnCheckPicStruct() 
{
	// TODO: Add your control notification handler code here
	 UpdateData(TRUE);

//      if (!m_bPicStruct)
//      {
//         GetDlgItem(IDC_COMBO_PICTURE_TYPE)->EnableWindow(FALSE);
//         GetDlgItem(IDC_DATE)->EnableWindow(FALSE);
//         GetDlgItem(IDC_TIME)->EnableWindow(FALSE);
//      } 
//      else
//      {
//          GetDlgItem(IDC_COMBO_PICTURE_TYPE)->EnableWindow(TRUE);
//          GetDlgItem(IDC_DATE)->EnableWindow(TRUE);
//          GetDlgItem(IDC_TIME)->EnableWindow(TRUE);
//      }

     UpdateData(FALSE);
}

void CDlgPictureUpload::OnBtnPicDownload() 
{
	// TODO: Add your control notification handler code here
    char szLan[128] = {0};
    char szPicUrl[256] = {0};
    UpdateData(TRUE);
    if (m_csPicUrl == _T(""))
    {
        g_StringLanType(szLan, "图片URL为空", "Picture URL is empty");     
        AfxMessageBox(szLan);
        return;
    }
    
    char *sSavedFileBuf = NULL;
    DWORD dwRetLen = 0;
    strncpy(szPicUrl, m_csPicUrl.GetBuffer(0), m_csPicUrl.GetLength());
	if(NET_DVR_GetPicture_V30(m_lServerID, szPicUrl, sSavedFileBuf, 0, &dwRetLen))
    {
       if(0 != dwRetLen)
       {
           sSavedFileBuf = new char[dwRetLen];
           memset(sSavedFileBuf, 0, dwRetLen);

           if(NET_DVR_GetPicture_V30(m_lServerID, szPicUrl, sSavedFileBuf, dwRetLen, &dwRetLen))
           {
               if (NULL != sSavedFileBuf && 0 != dwRetLen)
               {
                   
                   char cFilename[256] = {0};
                   HANDLE hFile;
                   DWORD dwReturn;
                   
                   SYSTEMTIME t;
                   GetLocalTime(&t);
                   char chTime[128];
                   sprintf(chTime,"%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
                   
                   sprintf(cFilename, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[m_lDeviceIndex].chDeviceIP);
                   if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
                   {
                       CreateDirectory(cFilename, NULL);
                   }
                   
                   
                   sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpg",cFilename, chTime,rand() % GetTickCount());
                   
                   //sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpg",cFilename, chTime, i);
                   hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                   if (hFile == INVALID_HANDLE_VALUE)
                   {
                       return;
                   }
                   WriteFile(hFile, sSavedFileBuf, dwRetLen, &dwReturn, NULL);
                   CloseHandle(hFile);
                   hFile = NULL;

                   g_StringLanType(szLan, "图片下载成功", "NET_DVR_GetPicture_V30 SUCC");
                   AfxMessageBox(szLan);
            
               }
           }
           else
           {
               g_StringLanType(szLan, "图片下载失败", "NET_DVR_GetPicture_V30 Failed");
               sprintf(szLan, "%s %s %d", szLan, NET_DVR_GetErrorMsg(), NET_DVR_GetLastError());     
               AfxMessageBox(szLan);
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
        g_StringLanType(szLan, "图片下载失败", "NET_DVR_GetPicture_V30 Failed");
	    sprintf(szLan, "%s %s %d", szLan, NET_DVR_GetErrorMsg(), NET_DVR_GetLastError());     
        AfxMessageBox(szLan);
        return;
    }
}

void CDlgPictureUpload::OnBnClickedBtnPicDownloadv50()
{
        // TODO:  在此添加控件通知处理程序代码
        char szLan[128] = { 0 };
        char szPicUrl[256] = { 0 };
        UpdateData(TRUE);
        if (m_csPicUrl == _T(""))
        {
            g_StringLanType(szLan, "图片URL为空", "Picture URL is empty");
            AfxMessageBox(szLan);
            return;
        }

        if (m_csIp == _T("") || m_dwPort == 0)
        {
            g_StringLanType(szLan, "图片所在CS的地址或端口号为空（通过查询获取的）", "Picture location ip or port is empty(gained by search)");
            AfxMessageBox(szLan);
            return;
        }

        char *sSavedFileBuf = NULL;
        DWORD dwRetLen = 0;
        strncpy(szPicUrl, m_csPicUrl.GetBuffer(0), m_csPicUrl.GetLength());

        NET_DVR_PIC_PARAM struPicture = { 0 };
        struPicture.pDVRFileName = szPicUrl;
        struPicture.pSavedFileBuf = sSavedFileBuf;
        struPicture.dwBufLen = 0;
        struPicture.lpdwRetLen = &dwRetLen;
        //ipv4
        if (!g_ValidIPv6((BYTE*)m_csIp.GetBuffer()))
        {
            sprintf(struPicture.struAddr.struIP.sIpV4, "%s", m_csIp);
        }
        else
        {
            sprintf((char *)struPicture.struAddr.struIP.byIPv6, "%s", m_csIp);
        }
        struPicture.struAddr.wPort = m_dwPort;

        if (NET_DVR_GetPicture_V50(m_lServerID, &struPicture))
        {
            if (0 != dwRetLen)
            {
                sSavedFileBuf = new char[dwRetLen];
                memset(sSavedFileBuf, 0, dwRetLen);
                struPicture.dwBufLen = dwRetLen;

                if (NET_DVR_GetPicture_V50(m_lServerID, &struPicture))
                {
                    if (NULL != sSavedFileBuf && 0 != dwRetLen)
                    {

                        char cFilename[256] = { 0 };
                        HANDLE hFile;
                        DWORD dwReturn;

                        SYSTEMTIME t;
                        GetLocalTime(&t);
                        char chTime[128];
                        sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);

                        sprintf(cFilename, "%s\\%s", g_struLocalParam.chPictureSavePath, g_struDeviceInfo[m_lDeviceIndex].chDeviceIP);
                        if (GetFileAttributes(cFilename) != FILE_ATTRIBUTE_DIRECTORY)
                        {
                            CreateDirectory(cFilename, NULL);
                        }


                        sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpg", cFilename, chTime, rand() % GetTickCount());

                        //sprintf(cFilename, "%s\\LocalTime[%s]_%d.jpg",cFilename, chTime, i);
                        hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                        if (hFile == INVALID_HANDLE_VALUE)
                        {
                            return;
                        }
                        WriteFile(hFile, sSavedFileBuf, dwRetLen, &dwReturn, NULL);
                        CloseHandle(hFile);
                        hFile = NULL;

                        g_StringLanType(szLan, "图片下载成功", "NET_DVR_GetPicture_V30 SUCC");
                        AfxMessageBox(szLan);

                    }
                }
                else
                {
                    g_StringLanType(szLan, "图片下载失败", "NET_DVR_GetPicture_V30 Failed");
                    sprintf(szLan, "%s %s %d", szLan, NET_DVR_GetErrorMsg(), NET_DVR_GetLastError());
                    AfxMessageBox(szLan);
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
            g_StringLanType(szLan, "图片下载失败", "NET_DVR_GetPicture_V30 Failed");
            sprintf(szLan, "%s %s %d", szLan, NET_DVR_GetErrorMsg(), NET_DVR_GetLastError());
            AfxMessageBox(szLan);
            return;
        }
}
