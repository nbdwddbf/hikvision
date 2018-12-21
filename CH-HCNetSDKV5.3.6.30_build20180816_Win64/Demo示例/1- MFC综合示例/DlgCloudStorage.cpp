// DlgCloudStorage.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgCloudStorage.h"
#include "xml/XmlBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCloudStorage dialog


CDlgCloudStorage::CDlgCloudStorage(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCloudStorage::IDD, pParent)
{
    m_lUserID = -1;
    m_iDeviceIndex = -1;
    m_iStartPoolID = -1;
    m_iMaxPoolID = -1;
    m_iPoolCount = -1;
    m_lUploadPicHandle = -1;
    m_hPicUpLoadThread = NULL;
    m_hPicDownloadThread = NULL;
    m_bStopUploadPic = FALSE;
    m_bStopDownloadPic = FALSE;
    m_lDownloadPicHandle = -1;
    memset(&m_struPicRet, 0, sizeof(m_struPicRet));
	//{{AFX_DATA_INIT(CDlgCloudStorage)
	m_strPicCameraID = _T("1234567890");
	m_strPicPath = _T("c:/Picture");
	m_strPicCommenState = _T("");
	m_strPicSingleState = _T("");
	m_dwTotalSpace = 0;
	m_dwOnlineSpace = 0;
	m_dwFreeSpace = 0;
	m_dwAllocatedSpace = 0;
	m_dwCoverCycle = 0;
	m_dwPoolFreeSize = 0;
	m_strPoolName = _T("");
	m_dwPoolSize = 0;
    m_pPoolList = NULL;
    m_dwPoolListLen = 1024*1024;
	m_strDownloadCmrID = _T("");
	m_strStartTime = _T("");
	m_strStopTime = _T("");
	m_strSavePath = _T("");
	m_iQualityPer = 99;
	m_iScalePer = 99;
	m_iHeight = 0;
	m_iWidth = 0;
	m_bBmp = FALSE;
	m_bJpg = FALSE;
	m_bPng = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgCloudStorage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCloudStorage)
	DDX_Control(pDX, IDC_CMB_ZOOM_TYPE, m_cmbZoomType);
	DDX_Control(pDX, IDC_CMB_POOL_COVER_TYPE, m_cmbCoverType);
	DDX_Control(pDX, IDC_CMB_POOL_TYPE, m_cmbPoolType);
	DDX_Control(pDX, IDC_CMB_POOL_ID, m_cmbPoolID);
	DDX_Control(pDX, IDC_CMB_CLUSTER_STATUS, m_cmbClusterStatus);
	DDX_Text(pDX, IDC_EDIT_PIC_CAMERAID, m_strPicCameraID);
	DDV_MaxChars(pDX, m_strPicCameraID, 64);
	DDX_Text(pDX, IDC_EDIT_PIC_PATH, m_strPicPath);
	DDX_Text(pDX, IDC_STATIC_PIC_COMMEN_STATE, m_strPicCommenState);
	DDX_Text(pDX, IDC_STATIC_PIC_SINGLE_STATE, m_strPicSingleState);
	DDX_Text(pDX, IDC_EDIT_TOTAL_SPACE, m_dwTotalSpace);
	DDX_Text(pDX, IDC_EDIT_ONLINE_SPACE, m_dwOnlineSpace);
	DDX_Text(pDX, IDC_EDIT_FREE_SPACE, m_dwFreeSpace);
	DDX_Text(pDX, IDC_EDIT_ALLOCATED_SPACE, m_dwAllocatedSpace);
	DDX_Text(pDX, IDC_EDIT_POOL_COVER_CYCLE, m_dwCoverCycle);
	DDX_Text(pDX, IDC_EDIT_POOL_FREE_SIZE, m_dwPoolFreeSize);
	DDX_Text(pDX, IDC_EDIT_POOL_NAME, m_strPoolName);
	DDX_Text(pDX, IDC_EDIT_POOL_SIZE, m_dwPoolSize);
	DDX_Text(pDX, IDC_EDIT_PIC_CAMERAID_DOWNLOAD, m_strDownloadCmrID);
	DDX_Text(pDX, IDC_EDIT_PIC_DOWNLOAD_STARTTIME, m_strStartTime);
	DDX_Text(pDX, IDC_EDIT_PIC_DOWNLOAD_STOPTIME, m_strStopTime);
	DDX_Text(pDX, IDC_EDIT_PIC_SAVE_PATH, m_strSavePath);
	DDX_Text(pDX, IDC_EDIT_QUALITY_PER, m_iQualityPer);
	DDV_MinMaxInt(pDX, m_iQualityPer, 1, 99);
	DDX_Text(pDX, IDC_EDIT_SCALE_PER, m_iScalePer);
	DDV_MinMaxInt(pDX, m_iScalePer, 1, 99);
	DDX_Text(pDX, IDC_EDIT_RESOLUTION_HEIGHT, m_iHeight);
	DDX_Text(pDX, IDC_EDIT_RESOLUTION_WIDTH, m_iWidth);
	DDX_Check(pDX, IDC_CK_BMP, m_bBmp);
	DDX_Check(pDX, IDC_CK_JPG, m_bJpg);
	DDX_Check(pDX, IDC_CK_PNG, m_bPng);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCloudStorage, CDialog)
	//{{AFX_MSG_MAP(CDlgCloudStorage)
	ON_BN_CLICKED(IDC_BTN_UPLOAD_PIC, OnBtnUploadPic)
	ON_BN_CLICKED(IDC_BTN_UPLOAD_PIC_STOP, OnBtnUploadPicStop)
	ON_BN_CLICKED(IDC_BTN_GET_CLUSTERRESOURCE, OnBtnGetClusterresource)
	ON_BN_CLICKED(IDC_BTN_CREATE_POOL, OnBtnCreatePool)
	ON_BN_CLICKED(IDC_BTN_DELETE_POOL, OnBtnDeletePool)
	ON_BN_CLICKED(IDC_BTN_GET_POOL, OnBtnGetPool)
	ON_BN_CLICKED(IDC_BTN_SET_POOL, OnBtnSetPool)
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_CMB_POOL_ID, OnSelchangeCmbPoolId)
	ON_BN_CLICKED(IDC_BTN_STOP_DOWLOAD_PIC, OnBtnStopDowloadPic)
	ON_BN_CLICKED(IDC_BTN_DOWLOAD_PIC, OnBtnDowloadPic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCloudStorage message handlers

void CDlgCloudStorage::OnBtnUploadPic() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    NET_DVR_START_FILE_TO_CLOUD_COND    struFileCond = {0};
    struFileCond.dwSize = sizeof(struFileCond);
    memcpy(struFileCond.aCameraID, m_strPicCameraID.GetBuffer(0), m_strPicCameraID.GetLength());
    struFileCond.dwPoolID = m_cmbPoolID.GetItemData(m_cmbPoolID.GetCurSel());
    
    m_lUploadPicHandle = NET_DVR_UploadFile_V40(m_lUserID, UPLOAD_PICTURE_TO_CLOUD, &struFileCond, sizeof(struFileCond), NULL, NULL, 0);
    if (m_lUploadPicHandle < 0)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "UPLOAD_PICTURE_TO_CLOUD");
        return ;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "UPLOAD_PICTURE_TO_CLOUD");
    }
    m_bStopUploadPic = FALSE;
    DWORD dwThreadID = 0;
    m_hPicUpLoadThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(PicUpLoadThread), this, 0, &dwThreadID);
    if (m_hPicUpLoadThread == NULL)
    {
        char szLan[128] = {0};
        g_StringLanType(szLan, "打开上传图片线程失败!", "open UpLoad picture thread Fail!");
        AfxMessageBox(szLan);
        return;
    }
}
DWORD WINAPI CDlgCloudStorage::PicDownloadThread(LPVOID pParam)
{
    CDlgCloudStorage *pThis = (CDlgCloudStorage*)pParam;
    DWORD dwProgress = 0;
    LONG    lStatus = 0;
    while(1)
    {
        if (pThis->m_bStopDownloadPic)
        {
            break;
        }

        lStatus = NET_DVR_GetDownloadState(pThis->m_lDownloadPicHandle, &dwProgress);
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
DWORD WINAPI CDlgCloudStorage::PicUpLoadThread(LPVOID pParam)
{
    CDlgCloudStorage *pThis = (CDlgCloudStorage*)pParam;
    CFileFind finder;
    if (!finder.FindFile(pThis->m_strPicPath + "\\*.*"))
    {
        pThis->SetDlgItemText(IDC_STATIC_PIC_SINGLE_STATE, "打开文件夹失败");
        return 0;
    }
    FILE *pFile = NULL;
    BYTE byPicType = 0;
    BOOL bFindFile = TRUE;
    while (bFindFile)   //一张图片一次循环
    {
        if (pThis->m_bStopUploadPic)
        {
            break;
        }
        bFindFile = finder.FindNextFile();
        if(finder.IsDots())
        {
            continue;
        }
        else if(finder.IsDirectory())
        {
            continue;
        }
        else
        {
            CString strFilePath = finder.GetFilePath();
            CString strFileName = finder.GetFileName();
            if (strFileName.Find(".jpg") != -1 || strFileName.Find(".JPG") != -1)
            {
                byPicType = 1;
            }
            else if (strFileName.Find(".bmp") != -1 || strFileName.Find(".BMP") != -1)
            {
                byPicType = 2;
            }
            else if (strFileName.Find(".png") != -1 || strFileName.Find(".PNG") != -1)
            {
                byPicType = 3;
            }
            else
            {
                continue;
            }
            if (!pThis->PicUpload(strFileName, strFilePath, byPicType))
            {
                break;
            }
        }
        
        if (!bFindFile)
        {
            pThis->SetDlgItemText(IDC_STATIC_PIC_SINGLE_STATE, "已无更多文件");
            break;
        }
    }
    finder.Close();
    return 0;
}

BOOL CDlgCloudStorage::PicUpload(CString strFileName, CString strFilePath, BYTE byPicType)
{
    FILE* pFile;
    pFile = fopen(strFilePath.GetBuffer(0), "rb");
    if (pFile == NULL)
    {
        return FALSE;
    }

    long curpos,length;
    curpos=ftell(pFile);
    fseek(pFile,0L,SEEK_END);
    length=ftell(pFile);
    fseek(pFile,curpos,SEEK_SET);
    
    BYTE *pBuf = new BYTE[length];
    memset(pBuf, 0, length);
    fread(pBuf, length, 1, pFile);
    fclose(pFile);

    NET_DVR_SEND_PARAM_IN   struParamIn = {0};
    struParamIn.byPicType = byPicType;
    SYSTEMTIME sysTime = {0};
    GetLocalTime(&sysTime);
    struParamIn.struTime.wYear = sysTime.wYear;
    struParamIn.struTime.byMonth = sysTime.wMonth;
    struParamIn.struTime.byDay = sysTime.wDay;
    struParamIn.struTime.byHour = sysTime.wHour;
    struParamIn.struTime.byMinute = sysTime.wMinute;
    struParamIn.struTime.bySecond = sysTime.wSecond;
    struParamIn.struTime.wMilliSec = sysTime.wMilliseconds;
    struParamIn.pSendData = pBuf;
    struParamIn.dwSendDataLen = length;
    if(NET_DVR_UploadSend(m_lUploadPicHandle, &struParamIn, NULL) < 0)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadSend");
        delete[] pBuf;
        pBuf = NULL;
        return FALSE;
    }

    DWORD dwProgress = 0;
    int iStatus = -1;
    char szStatus[256] = {0};
    BOOL bRet = FALSE;
    while(1)
    {
        if (m_bStopUploadPic)
        {
            break;
        }
        memset(szStatus, 0, 256);
        iStatus = NET_DVR_GetUploadState(m_lUploadPicHandle, &dwProgress);
        if (iStatus == -1)  //即人口返回失败
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetUploadState");
            break;
        }
        else if (iStatus == 2) //正在上传
        {
            sprintf(szStatus, "File[%s],status[%d],progress[%d]", strFileName.GetBuffer(0), iStatus, dwProgress);
            SetDlgItemText(IDC_STATIC_PIC_SINGLE_STATE, szStatus);
            Sleep(100);
            continue;
        }
        else if (iStatus == 1) //上传成功
        {
            sprintf(szStatus, "File[%s],status[%d],progress[%d]", strFileName.GetBuffer(0), iStatus, dwProgress);
            SetDlgItemText(IDC_STATIC_PIC_SINGLE_STATE, szStatus);
            memset(&m_struPicRet, 0, sizeof(m_struPicRet));
            NET_DVR_GetUploadResult(m_lUploadPicHandle, &m_struPicRet, sizeof(m_struPicRet));
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, (char*)m_struPicRet.sUrl);
            Sleep(100); //这个sleep只是为了addlog能够有时间执行
            bRet = TRUE;
            break;
        }
        else //上传失败,显示状态
        {
            sprintf(szStatus, "File[%s],status[%d],progress[%d]", strFileName.GetBuffer(0), iStatus, dwProgress);
            SetDlgItemText(IDC_STATIC_PIC_SINGLE_STATE, szStatus);
            break;
        }
    }
    delete[] pBuf;
    pBuf = NULL;
    
    return bRet;
}

BOOL CDlgCloudStorage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    if (m_pPoolList == NULL)
    {
        m_pPoolList = new char[m_dwPoolListLen];
        memset(m_pPoolList, 0, m_dwPoolListLen);
    }
    
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//获取当前存储池的起始编号和数量
BOOL CDlgCloudStorage::GetCloudStoragePoolProperty()
{
    NET_DVR_XML_CONFIG_INPUT    struInput = {0};
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = {0};
    struInput.dwSize = sizeof(struInput);
    struInput.lpRequestUrl = "GET /ISAPI/ContentMgmt/CloudStorageServer/pool/count";
    struInput.dwRequestUrlLen = strlen("GET /ISAPI/ContentMgmt/CloudStorageServer/pool/count");
    DWORD dwOutputLen = 1024 * 1024;
    char *pOutBuf = new char[dwOutputLen];
    memset(pOutBuf, 0, dwOutputLen);
    struOuput.lpOutBuffer = pOutBuf;
    struOuput.dwOutBufferSize = dwOutputLen;
    struOuput.dwSize = sizeof(struOuput);
    
    if(!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "GET /ISAPI/ContentMgmt/CloudStorageServer/pool/count");
        delete []pOutBuf;
        pOutBuf = NULL;
        return FALSE;
    }

    BOOL bRet = FALSE;
    CXmlBase xmlBase;
    xmlBase.Parse(pOutBuf);
    if (xmlBase.FindElem("PoolListProperty") && xmlBase.IntoElem())
    {
        if (xmlBase.FindElem("count"))
        {
            m_iPoolCount = atoi(xmlBase.GetData().c_str());
            if (xmlBase.FindElem("startPoolID"))
            {
                m_iStartPoolID = atoi(xmlBase.GetData().c_str());
                if (xmlBase.FindElem("maxPoolID"))
                {
                    m_iMaxPoolID = atoi(xmlBase.GetData().c_str());
                    bRet = TRUE;
                }                
            }   
        }
    }
    
    delete []pOutBuf;
    pOutBuf = NULL;
    
    return bRet;
}
//找一个图片存储池
BOOL CDlgCloudStorage::GetPicturePoolID()
{    
    DWORD dwOutputLen = 10 * 1024;
    char *pOutBuf = new char[dwOutputLen];
    NET_DVR_XML_CONFIG_INPUT    struInput = {0};
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = {0};
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    BOOL bRet = FALSE;
    int i = 0;
    int iCount = 0;
    for (i = m_iStartPoolID; i <= m_iMaxPoolID && iCount < m_iPoolCount; i++)
    {
        memset(pOutBuf, 0, dwOutputLen);
        char szUrl[256] = {0};    
        sprintf(szUrl, "GET /ISAPI/ContentMgmt/CloudStorageServer/pool/%d", i);
        struInput.lpRequestUrl = szUrl;
        struInput.dwRequestUrlLen = strlen(szUrl);
        struOuput.lpOutBuffer = pOutBuf;
        struOuput.dwOutBufferSize = dwOutputLen;

        if(!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "szUrl");
            break;
        }

        iCount++;
        CXmlBase xmlBase;
        xmlBase.Parse(pOutBuf);
        if (xmlBase.FindElem("StoragePool") && xmlBase.IntoElem())
        {
            if (xmlBase.FindElem("poolType"))
            {
                if (xmlBase.GetData().compare("picture") == 0)
                {
                    m_iPucturePoolID = i;
                    bRet = TRUE;
                    break;
                }
            }
        }
    }
    if (!bRet)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "can't find a picture storage pool");
    }
    
    delete []pOutBuf;
    pOutBuf = NULL;
    return bRet;
}

void CDlgCloudStorage::OnBtnUploadPicStop() 
{
	// TODO: Add your control notification handler code here
    m_bStopUploadPic = TRUE;
	if(!NET_DVR_UploadClose(m_lUploadPicHandle))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadClose");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadClose");
    }
}

void CDlgCloudStorage::OnBtnGetClusterresource() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_XML_CONFIG_INPUT    struInput = {0};
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = {0};
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    struInput.lpRequestUrl = "GET /ISAPI/ContentMgmt/CloudStorageServer/clusterResource";
    struInput.dwRequestUrlLen = strlen("GET /ISAPI/ContentMgmt/CloudStorageServer/clusterResource");
    DWORD dwOutputLen = 1024 * 1024;
    char *pOutBuf = new char[dwOutputLen];
    memset(pOutBuf, 0, dwOutputLen);
    struOuput.lpOutBuffer = pOutBuf;
    struOuput.dwOutBufferSize = dwOutputLen;
    
    if(!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "GET /ISAPI/ContentMgmt/CloudStorageServer/clusterResource");
        delete []pOutBuf;
        pOutBuf = NULL;
        return ;
    }
    
    CXmlBase xmlBase;
    xmlBase.Parse(pOutBuf);
    if (xmlBase.FindElem("ClusterResouce") && xmlBase.IntoElem())
    {
        if (xmlBase.FindElem("status"))
        {
            if (xmlBase.GetData().compare("normal") == 0)
            {
                m_cmbClusterStatus.SetCurSel(0);
            }
            else if (xmlBase.GetData().compare("resourceShortage") == 0)
            {
                m_cmbClusterStatus.SetCurSel(1);
            }
        }
        if (xmlBase.FindElem("totalSpace"))
        {
            m_dwTotalSpace = atoi(xmlBase.GetData().c_str());
        }
        if (xmlBase.FindElem("onlineSpace"))
        {
            m_dwOnlineSpace = atoi(xmlBase.GetData().c_str());
        }
        if (xmlBase.FindElem("freeSpace"))
        {
            m_dwFreeSpace = atoi(xmlBase.GetData().c_str());
        }
        if (xmlBase.FindElem("allocatedSpace"))
        {
            m_dwAllocatedSpace = atoi(xmlBase.GetData().c_str());
        }
    }
    
    delete []pOutBuf;
    pOutBuf = NULL;
    
    UpdateData(FALSE);	
}

BOOL CDlgCloudStorage::CreateStoragePool(DWORD dwPoolID, char* pBuf, DWORD dwBufLen, int &dwRet)
{
    CXmlBase xmlBase;
    xmlBase.CreateRoot("StoragePool");
    xmlBase.SetAttribute("version", "2.0");
    char szPoolID[32] = {0};
    sprintf(szPoolID, "%d", dwPoolID);
    xmlBase.AddNode("id", szPoolID);
    xmlBase.OutOfElem();
    xmlBase.AddNode("poolName", m_strPoolName.GetBuffer(0));
    xmlBase.OutOfElem();
    char szPoolType[16] = {0};
    if (m_cmbPoolType.GetCurSel() == 0)
    {
        sprintf(szPoolType, "general");
    }
    else if (m_cmbPoolType.GetCurSel() == 1)
    {
        sprintf(szPoolType, "video");
    }
    else if (m_cmbPoolType.GetCurSel() == 2)
    {
        sprintf(szPoolType, "picture");
    }
    xmlBase.AddNode("poolType", szPoolType);
    xmlBase.OutOfElem();
    char szCoverType[16] = {0};
    if (m_cmbCoverType.GetCurSel() == 0)
    {
        sprintf(szCoverType, "noCover");
    }
    else if (m_cmbCoverType.GetCurSel() == 1)
    {
        sprintf(szCoverType, "capacity");
    }
    else if (m_cmbCoverType.GetCurSel() == 2)
    {
        sprintf(szCoverType, "periodic");
    }
    xmlBase.AddNode("coverType", szCoverType);
    xmlBase.OutOfElem();
    if (m_cmbCoverType.GetCurSel() == 2)
    {
        char szPoolCycle[16] = {0};
        sprintf(szPoolCycle, "%d", m_dwCoverCycle);
        xmlBase.AddNode("poolCycle", szPoolCycle);
        xmlBase.OutOfElem();
    }
    char szPoolSize[32] = {0};
    sprintf(szPoolSize, "%d", m_dwPoolSize);
    xmlBase.AddNode("poolSize", szPoolSize);
    xmlBase.OutOfElem();

    return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}

//创建之后需要重新获取
void CDlgCloudStorage::OnBtnCreatePool() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

    DWORD dwBufLen = 10*1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);
    int dwXmlLen = 0;
    if(!CreateStoragePool(0, pBuf, dwBufLen, dwXmlLen))
    {
        delete []pBuf;
        pBuf = NULL;
        return;
    }

    NET_DVR_XML_CONFIG_INPUT    struInput = {0};
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = {0};
    struInput.dwSize = sizeof(struInput);
    struInput.lpRequestUrl = "POST /ISAPI/ContentMgmt/CloudStorageServer/pool";
    struInput.dwRequestUrlLen = strlen("POST /ISAPI/ContentMgmt/CloudStorageServer/pool");
    struInput.lpInBuffer = pBuf;
    struInput.dwInBufferSize = dwXmlLen;
    char szOutBuf[1024] = {0};
    struOuput.lpOutBuffer = szOutBuf;
    struOuput.dwOutBufferSize = 1024;    
    struOuput.dwSize = sizeof(struOuput);
    if(!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "POST /ISAPI/ContentMgmt/CloudStorageServer/pool");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "POST /ISAPI/ContentMgmt/CloudStorageServer/pool");
    }

    delete []pBuf;
    pBuf = NULL;
}

void CDlgCloudStorage::OnBtnDeletePool() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    DWORD dwPoolID = m_cmbPoolID.GetItemData(m_cmbPoolID.GetCurSel());
    char szUrl[256] = {0};
    sprintf(szUrl, "DELETE /ISAPI/ContentMgmt/CloudStorageServer/pool/%d", dwPoolID);
    NET_DVR_XML_CONFIG_INPUT    struInput = {0};
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = {0};
    struInput.dwSize = sizeof(struInput);
    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    struOuput.dwSize = sizeof(struOuput);
    if(!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szUrl);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);
    }
}

void CDlgCloudStorage::OnBtnGetPool() 
{
	// TODO: Add your control notification handler code here
	if(!GetCloudStoragePoolProperty())
    {
        return ;
    }
    CXmlBase xmlBase;
    xmlBase.CreateRoot("PoolList");

    DWORD dwOutputLen = 10 * 1024;
    char *pOutBuf = new char[dwOutputLen];
    NET_DVR_XML_CONFIG_INPUT    struInput = {0};
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = {0};
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    int i = 0;
    int iCount = 0;
    int iIndex = 0;
    m_cmbPoolID.ResetContent();
    for (i = m_iStartPoolID; i <= m_iMaxPoolID && iCount < m_iPoolCount; i++)
    {
        memset(pOutBuf, 0, dwOutputLen);
        char szUrl[256] = {0};    
        sprintf(szUrl, "GET /ISAPI/ContentMgmt/CloudStorageServer/pool/%d", i);
        struInput.lpRequestUrl = szUrl;
        struInput.dwRequestUrlLen = strlen(szUrl);
        struOuput.lpOutBuffer = pOutBuf;
        struOuput.dwOutBufferSize = dwOutputLen;
        
        if(!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
        {
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szUrl);
            continue;
        }
        else
        {
            char szID[32] = {0};
            sprintf(szID, "%d", i);
            m_cmbPoolID.InsertString(iIndex, szID);
            m_cmbPoolID.SetItemData(iIndex, i);
            iIndex++;
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);
        }
        
        iCount++;
        CXmlBase xmlTmp;
        xmlTmp.Parse(pOutBuf);
        xmlTmp.SetRoot();
        xmlBase.AddNode(xmlTmp);
        xmlBase.OutOfElem();
    }
    
    delete []pOutBuf;
    pOutBuf = NULL;

    int dwRet;
    memset(m_pPoolList, 0, m_dwPoolListLen);
    xmlBase.WriteToBuf(m_pPoolList, m_dwPoolListLen, dwRet);
    ShowPoolCfg(0);
}

void CDlgCloudStorage::OnBtnSetPool() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    DWORD dwPoolID = m_cmbPoolID.GetItemData(m_cmbPoolID.GetCurSel());
    DWORD dwBufLen = 10*1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);
    int dwXmlLen = 0;
    if(!CreateStoragePool(dwPoolID, pBuf, dwBufLen, dwXmlLen))
    {
        delete []pBuf;
        pBuf = NULL;
        return;
    }

    char szUrl[256] = {0};
    sprintf(szUrl, "PUT /ISAPI/ContentMgmt/CloudStorageServer/pool/%d", dwPoolID);
    NET_DVR_XML_CONFIG_INPUT    struInput = {0};
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = {0};
    struInput.dwSize = sizeof(struInput);
    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    struInput.lpInBuffer = pBuf;
    struInput.dwInBufferSize = dwXmlLen;  
    struOuput.dwSize = sizeof(struOuput);
    if(!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szUrl);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);
    }

    delete []pBuf;
    pBuf = NULL;
}

void CDlgCloudStorage::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if (m_pPoolList != NULL)
	{
        delete []m_pPoolList;
        m_pPoolList = NULL;
	}
	CDialog::OnClose();
}
//0表示取第一个
BOOL CDlgCloudStorage::ShowPoolCfg(DWORD dwPoolID)
{
    CXmlBase xmlBase;
    xmlBase.Parse(m_pPoolList);
    BOOL bRet = FALSE;
    int i = 0;
    if (xmlBase.FindElem("PoolList") && xmlBase.IntoElem())
    {
        do 
        {
            if (xmlBase.FindElem("StoragePool") && xmlBase.IntoElem())
            {
                if (xmlBase.FindElem("id"))
                {
                    m_cmbPoolID.SetCurSel(i);
                    DWORD dwID = atoi(xmlBase.GetData().c_str());
                    if (dwID == dwPoolID || dwPoolID == 0)
                    {
                        if (xmlBase.FindElem("poolName"))
                        {
                            m_strPoolName = xmlBase.GetData().c_str();
                        }
                        if (xmlBase.FindElem("poolType"))
                        {
                            if (xmlBase.GetData().compare("general") == 0)
                            {
                                m_cmbPoolType.SetCurSel(0);
                            }
                            else if (xmlBase.GetData().compare("video") == 0)
                            {
                                m_cmbPoolType.SetCurSel(1);
                            }
                            else if (xmlBase.GetData().compare("picture") == 0)
                            {
                                m_cmbPoolType.SetCurSel(2);
                            }
                        }
                        if (xmlBase.FindElem("coverType"))
                        {
                            if (xmlBase.GetData().compare("noCover") == 0)
                            {
                                m_cmbCoverType.SetCurSel(0);
                            }
                            else if (xmlBase.GetData().compare("capacity") == 0)
                            {
                                m_cmbCoverType.SetCurSel(1);
                            }
                            else if (xmlBase.GetData().compare("periodic") == 0)
                            {
                                m_cmbCoverType.SetCurSel(2);
                            }
                        }
                        if (xmlBase.FindElem("poolCycle"))
                        {
                            m_dwCoverCycle = atoi(xmlBase.GetData().c_str());
                        }
                        if (xmlBase.FindElem("poolSize"))
                        {
                            m_dwPoolSize = atoi(xmlBase.GetData().c_str());
                        }
                        if (xmlBase.FindElem("freeSize"))
                        {
                            m_dwPoolFreeSize = atoi(xmlBase.GetData().c_str());
                        }
                        bRet = TRUE;
                        break;
                    }
                    i++;
                }
                xmlBase.OutOfElem();
            }
        } while (xmlBase.NextSibElem());
    }
    
    UpdateData(FALSE);
    return bRet;
}

void CDlgCloudStorage::OnSelchangeCmbPoolId() 
{
	// TODO: Add your control notification handler code here
	ShowPoolCfg(m_cmbPoolID.GetItemData(m_cmbPoolID.GetCurSel()));
}

void CDlgCloudStorage::OnBtnStopDowloadPic() 
{
	// TODO: Add your control notification handler code here
    m_bStopDownloadPic = TRUE;
	if(NET_DVR_StopDownload(m_lDownloadPicHandle))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopDownload");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopDownload");
    }
}

BOOL fDownloadPicFromCloud( LONG lHandle, NET_DOWNLOAD_CB_INFO *pCBInfo, void *pUserData)
{
    CDlgCloudStorage* pThis = (CDlgCloudStorage*)pUserData;
    if (pCBInfo->dwType == 2)
    {   
        NET_DVR_START_PICTURE_FROM_CLOUD_RET    struPicRet = {0};
        memcpy(&struPicRet, pCBInfo->pFileInfo, pCBInfo->dwFileInfoLen);
        char szBuf[128] = {0};
        sprintf(szBuf, "picture count:%d", struPicRet.dwFileCount);
        pThis->SetDlgItemText(IDC_STATIC_PIC_COUNT, szBuf);
    }
    else if (pCBInfo->dwType == 1)
    {
        NET_DVR_PICTURE_FROM_CLOUD_RET  struPicInfo = {0};
        memcpy(&struPicInfo, pCBInfo->pFileInfo, pCBInfo->dwFileInfoLen);
        char szFilePath[260] = {0};
        if (struPicInfo.byPicType == 1) //jpg
        {
            sprintf(szFilePath, "%s/%04d%02d%02d%02d%02d%02d%d.jpg", pThis->m_strSavePath.GetBuffer(0), struPicInfo.struTime.wYear, struPicInfo.struTime.byMonth,
                struPicInfo.struTime.byDay, struPicInfo.struTime.byHour, struPicInfo.struTime.byMinute, struPicInfo.struTime.bySecond);
        }
        else if (struPicInfo.byPicType == 2) //bmp
        {
            sprintf(szFilePath, "%s/%04d%02d%02d%02d%02d%02d%d.bmp", pThis->m_strSavePath.GetBuffer(0), struPicInfo.struTime.wYear, struPicInfo.struTime.byMonth,
                struPicInfo.struTime.byDay, struPicInfo.struTime.byHour, struPicInfo.struTime.byMinute, struPicInfo.struTime.bySecond);
        }
        else if (struPicInfo.byPicType == 3) // png
        {
            sprintf(szFilePath, "%s/%04d%02d%02d%02d%02d%02d%d.png", pThis->m_strSavePath.GetBuffer(0), struPicInfo.struTime.wYear, struPicInfo.struTime.byMonth,
                struPicInfo.struTime.byDay, struPicInfo.struTime.byHour, struPicInfo.struTime.byMinute, struPicInfo.struTime.bySecond);
        }
        else
        {
            return FALSE;
        }
        FILE *pFile = fopen(szFilePath, "wb");
        if (pFile == NULL)
        {
            g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_FAIL_T, szFilePath);
            return FALSE;
        }
        fwrite(pCBInfo->pData, pCBInfo->dwDataLen, 1, pFile);
        fclose(pFile);
        pFile = NULL;
        g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_SUCC_T, szFilePath);
    }
    return TRUE;
}
void CDlgCloudStorage::OnBtnDowloadPic() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    NET_DVR_START_PICTURE_FROM_CLOUD_COND   struPicCond = {0};
    struPicCond.dwSize = sizeof(struPicCond);
    memcpy(struPicCond.aCameraID, m_strDownloadCmrID, m_strDownloadCmrID.GetLength());
    sscanf(m_strStartTime.GetBuffer(0), "%04d-%02d-%02d %02d:%02d:%02d", struPicCond.struBeginTime.wYear, struPicCond.struBeginTime.byMonth,
        struPicCond.struBeginTime.byDay, struPicCond.struBeginTime.byHour, struPicCond.struBeginTime.byMinute, struPicCond.struBeginTime.bySecond);
    sscanf(m_strStopTime.GetBuffer(0),  "%04d-%02d-%02d %02d:%02d:%02d", struPicCond.struEndTime.wYear, struPicCond.struEndTime.byMonth,
        struPicCond.struEndTime.byDay, struPicCond.struEndTime.byHour, struPicCond.struEndTime.byMinute, struPicCond.struEndTime.bySecond);
    struPicCond.dwPicType |= m_bJpg;
    struPicCond.dwPicType |= (m_bBmp << 1);
    struPicCond.dwPicType |= (m_bPng << 2);
    struPicCond.byZoomType = m_cmbZoomType.GetCurSel();
    if (m_cmbZoomType.GetCurSel() == 1)
    {
        struPicCond.uZoomParam.struScale.byScale = m_iScalePer;
    }
    else if (m_cmbZoomType.GetCurSel() == 2)
    {
        struPicCond.uZoomParam.struQuality.byQuality = m_iQualityPer;
    }
    else if (m_cmbZoomType.GetCurSel() == 3)
    {
        struPicCond.uZoomParam.struResolution.dwWidth = m_iWidth;
        struPicCond.uZoomParam.struResolution.dwHeight = m_iHeight;
    }
    struPicCond.fnDownloadFileCallBack = fDownloadPicFromCloud;
    struPicCond.pUser = this;
    m_lDownloadPicHandle = NET_DVR_StartDownload(m_lUserID, NET_SDK_DOWNLOAD_FILE_FORM_CLOUD, &struPicCond, sizeof(struPicCond), NULL);
    if (m_lDownloadPicHandle < 0)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartDownload");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StartDownload");
    }
    m_bStopDownloadPic = FALSE;
    DWORD dwThreadID = 0;
    m_hPicDownloadThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(PicDownloadThread), this, 0, &dwThreadID);
    if (m_hPicDownloadThread == NULL)
    {
        char szLan[128] = {0};
        g_StringLanType(szLan, "打开下载图片线程失败!", "open Download picture thread Fail!");
        AfxMessageBox(szLan);
        return;
    }
}
