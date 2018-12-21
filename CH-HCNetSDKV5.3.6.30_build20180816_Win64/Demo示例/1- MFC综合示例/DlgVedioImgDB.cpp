// DlgVedioImgDB.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVedioImgDB.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVedioImgDB dialog

DWORD WINAPI CDlgVedioImgDB::UpLoadSendThread(LPVOID pParam)
{
    CDlgVedioImgDB *pThis = ( CDlgVedioImgDB*)pParam;
	char szOutPut[512] = {0};


	//发送文件内容
	
	BYTE *pSendData = new BYTE[MAX_BUFFER_LEN];
	DWORD iReadLen = 0;
	
	while(!pThis->m_bStop)
	{
		memset(pSendData, 0, MAX_BUFFER_LEN);
		ReadFile(pThis->m_hFile, pSendData, MAX_BUFFER_LEN, &iReadLen, NULL);

        if (iReadLen <= 0)
        {
            //OutputDebugString("iReadLen==0\n");
            break;
        }
		NET_DVR_SEND_PARAM_IN struSendParamIn = {0};
		struSendParamIn.pSendData = pSendData;
		struSendParamIn.dwSendDataLen = iReadLen;

        
		int iRet = NET_DVR_UploadSend(pThis->m_lUploadHandle, &struSendParamIn, NULL);
		sprintf(szOutPut, "send %d, iReadLen[%d]\n", iRet, iReadLen);
		OutputDebugString(szOutPut);
		if (iReadLen < MAX_BUFFER_LEN || iRet != iReadLen)
		{
			break;
		}
		
	}
	
    CloseHandle(pThis->m_hFile);
	delete [] pSendData;


	OutputDebugString("UpLoadSendThread exit \n");
    return FALSE;
}

BOOL DOWNLOAD_VIDEO_IMG_DB_CALLBACK(LONG lHandle,  NET_DOWNLOAD_CB_INFO *pCBInfo, void *pUserData)
{
	char szLan[128] = {0};
	CDlgVedioImgDB *pThis = (CDlgVedioImgDB *)pUserData;
	if (pThis->m_fp == NULL)
	{
		CString strFilePath;
		strFilePath.Format("C:\\DownLoad\\%s", pThis->m_strFileID);
		pThis->m_fp = fopen(strFilePath,"wb");
	}


	if (pThis->m_fp != NULL)
	{
		fwrite(pCBInfo->pData, 1, pCBInfo->dwDataLen, pThis->m_fp);
	}
	
	sprintf(szLan, "data download, len=%d, pUserData=%x\n", pCBInfo->dwDataLen, pUserData);
	OutputDebugString(szLan);
	return TRUE;
}


CDlgVedioImgDB::CDlgVedioImgDB(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVedioImgDB::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVedioImgDB)
	m_i64Available =  _T("");
	m_i64Capacity =  _T("");
	m_strFileID = _T("");
	m_i64FileLen =  _T("");
	m_i64Used =  _T("");
	m_i64Offset =  _T("");
	m_strStatus = _T("");
	m_lUploadHandle = -1;
	m_lDownloadHandle = -1;
	m_dwSpeed = 0;
	m_fp = NULL;
	//}}AFX_DATA_INIT
	m_bStop = FALSE;
	memset(m_szFileName, 0, MAX_PATH);
}

CDlgVedioImgDB::~CDlgVedioImgDB()
{
	if (m_fp != NULL)
	{
		fclose(m_fp);
		m_fp = NULL;	
	}
}


void CDlgVedioImgDB::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVedioImgDB)
	DDX_Text(pDX, IDC_EDIT_AVAILABLE_LOW, m_i64Available);
	DDX_Text(pDX, IDC_EDIT_CAP_LOW, m_i64Capacity);
	DDX_Text(pDX, IDC_EDIT_FILE_ID, m_strFileID);
	DDX_Text(pDX, IDC_EDIT_FILE_LEN, m_i64FileLen);
	DDX_Text(pDX, IDC_EDIT_USED_LOW, m_i64Used);
	DDX_Text(pDX, IDC_EDIT_FILE_OFFSET, m_i64Offset);
	DDX_Text(pDX, IDC_STATIC_DOWNLOAD_PROGRESS, m_strStatus);
	DDX_Text(pDX, IDC_EDIT_DOWNLOAD_DB_FILE_SPEED, m_dwSpeed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVedioImgDB, CDialog)
	//{{AFX_MSG_MAP(CDlgVedioImgDB)
	ON_BN_CLICKED(IDC_BUTTON_GET_CAP, OnButtonGetCap)
	ON_BN_CLICKED(IDC_BUTTON_SET_CAP, OnButtonSetCap)
	ON_BN_CLICKED(IDC_BUTTON_QUERY, OnButtonQueryFile)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDelFile)
	ON_BN_CLICKED(IDC_BUTTON_UPLOAD_START, OnButtonUploadStart)
	ON_BN_CLICKED(IDC_BUTTON_UPLOAD_CLOSE, OnButtonUploadClose)
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD_START, OnButtonDownloadStart)
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD_CLOSE, OnButtonDownloadClose)
	ON_BN_CLICKED(IDC_BUTTON_CONTROL_SPEED, OnButtonControlSpeed)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVedioImgDB message handlers

void CDlgVedioImgDB::OnButtonGetCap() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpOutBuffer = &m_struVideoImgDBCfg;
    struCfg.dwOutSize = sizeof(m_struVideoImgDBCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_VIDEO_IMAGE_DB_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VIDEO_IMAGE_DB_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_VIDEO_IMAGE_DB_CFG");
    }

	//更新控件
	m_i64Capacity.Format("%I64d", m_struVideoImgDBCfg.i64Capacity);
	m_i64Used.Format("%I64d", m_struVideoImgDBCfg.i64UsedSpace);
	m_i64Available.Format("%I64d", m_struVideoImgDBCfg.i64AvailableSpace);


	UpdateData(FALSE);
}

void CDlgVedioImgDB::OnButtonSetCap() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struVideoImgDBCfg.i64Capacity = _atoi64(m_i64Capacity);
	m_struVideoImgDBCfg.i64UsedSpace = _atoi64(m_i64Used);
	m_struVideoImgDBCfg.i64AvailableSpace = _atoi64(m_i64Available);


	NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpInBuffer = &m_struVideoImgDBCfg;
    struCfg.dwInSize = sizeof(m_struVideoImgDBCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
	
    m_struVideoImgDBCfg.dwSize = sizeof(m_struVideoImgDBCfg);    
    if(!NET_DVR_SetSTDConfig(m_lUserID, NET_DVR_SET_VIDEO_IMAGE_DB_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VIDEO_IMAGE_DB_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VIDEO_IMAGE_DB_CFG");
    }
}

void CDlgVedioImgDB::OnButtonQueryFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	strncpy(m_struFileInfoIn.szFileID, m_strFileID, MAX_FILE_ID_LEN);
	NET_DVR_STD_CONFIG struCfg = {0};
	struCfg.lpCondBuffer = &m_struFileInfoIn;
    struCfg.dwCondSize = sizeof(m_struFileInfoIn);
    struCfg.lpOutBuffer = &m_struQueryInfo;
    struCfg.dwOutSize = sizeof(m_struQueryInfo);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_FILE_INFO_BY_ID, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_FILE_INFO_BY_ID");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_FILE_INFO_BY_ID");
    }
	
	//更新控件
	m_i64FileLen.Format("%I64d", m_struQueryInfo.i64FileLen);
	UpdateData(FALSE);
}

void CDlgVedioImgDB::OnButtonDelFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    char szLan[512] = {0};
    strncpy(m_struFileInfoIn.szFileID, m_strFileID, MAX_FILE_ID_LEN);
	
    NET_DVR_STD_CONTROL struControl = {0};
    struControl.lpCondBuffer = &m_struFileInfoIn;
    struControl.dwCondSize = sizeof(m_struFileInfoIn);
    
    memset(m_szStatusBuf, 0, 1024);
    struControl.lpStatusBuffer = m_szStatusBuf;
    struControl.dwStatusSize = 1024;
    
    if(!NET_DVR_STDControl(m_lUserID, NET_DVR_DEL_FILE_FROM_DB, &struControl))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_DEL_FILE_FROM_DB");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DEL_FILE_FROM_DB");
    }
}

BOOL CDlgVedioImgDB::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVedioImgDB::OnButtonUploadStart() 
{
	// TODO: Add your control notification handler code here
	char szLan[1024] = {0};
	m_bStop = FALSE;
	if (m_lUploadHandle != -1)
	{
        g_StringLanType(szLan, "上传已经开始", "Already start upload");
        AfxMessageBox(szLan);
        return;
	}

	UpdateData(TRUE);
	
	static char szFilter[] = "All File(*.*)|*.*||";
    CFileDialog dlg(TRUE,"*.*", NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter);
    if (dlg.DoModal() == IDOK)
    {
		strcpy(m_szFileName, dlg.GetPathName());
        //szFileName = dlg.GetPathName();
        //UpdateData(FALSE);
	}

	m_hFile = CreateFile(m_szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == m_hFile)
	{
		g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
		AfxMessageBox(szLan);
		return;
	}
	BY_HANDLE_FILE_INFORMATION struFileInfo = {0}; 
	if(!GetFileInformationByHandle(m_hFile, &struFileInfo))
	{
		g_StringLanType(szLan, "获取文件信息失败", "Get file info failed ");
		AfxMessageBox(szLan);
		return;
	}

	INT64 iFileSize = (((INT64)struFileInfo.nFileSizeHigh << 32)) + (INT64)struFileInfo.nFileSizeLow;
	if (iFileSize == 0)
	{
		g_StringLanType(szLan, "文件为空", "Configure file is empty");
		AfxMessageBox(szLan);
		return;
	}

	//打开上传句柄

	NET_DVR_UPLOAD_DB_IN struUploadDBIn = {0};
	NET_DVR_UPLOAD_DB_OUT struUploadDBOut = {0};
	if (m_strFileID == "")
	{
		struUploadDBIn.byContinueUpload = 0;
		struUploadDBIn.i64FileLen = iFileSize;
	}
	else
	{
		//断点续传可以不给长度
		struUploadDBIn.byContinueUpload = 1;
	}
	
    m_lUploadHandle = NET_DVR_UploadFile_V40(m_lUserID, UPLOAD_DATA_TO_DB, &struUploadDBIn, sizeof(struUploadDBIn), m_strFileID, &struUploadDBOut, sizeof(struUploadDBOut));
    if (m_lUploadHandle < 0)
    {
		g_StringLanType(szLan, "上传失败", "Upload Failed");
		sprintf(szLan, "%s %s %d", szLan, NET_DVR_GetErrorMsg(), NET_DVR_GetLastError());     
        AfxMessageBox(szLan);
        return;	
    }
    else
    {
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "UPLOAD_DATA_TO_DB");
		SetTimer(UPLOAD_DB_FILE_TIMER, 50, NULL);
		
    }



    m_hUpLoadThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(UpLoadSendThread), this, 0, &m_dwThreadId);
    if (m_hUpLoadThread  == NULL)
    {
        g_StringLanType(szLan, "打开上传线程失败!", "Open UpLoad thread Fail!");
        AfxMessageBox(szLan);
        return;
    }

	//更新界面文件ID
	m_strFileID.Format("%s", struUploadDBOut.szFileID);
	UpdateData(FALSE);
}

void CDlgVedioImgDB::OnButtonUploadClose() 
{
	// TODO: Add your control notification handler code here
	m_bStop = TRUE;
	if (m_lUploadHandle != -1)
	{
		NET_DVR_UploadClose(m_lUploadHandle);
		m_lUploadHandle = -1;
	}
}

void CDlgVedioImgDB::OnButtonDownloadStart() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	if (m_lDownloadHandle != -1)
	{
        g_StringLanType(szLan, "下载已经开始", "Already start download");
        AfxMessageBox(szLan);
        return;
	}

	UpdateData(TRUE);
	
	NET_DVR_DOWNLOAD_CB_PARAM struParam;
	memset(&struParam, 0, sizeof(struParam));
	
	struParam.i64Offset = _atoi64(m_i64Offset);
	struParam.fnDownloadDataCB = DOWNLOAD_VIDEO_IMG_DB_CALLBACK;
	struParam.pUserData = this;

	
	m_lDownloadHandle = NET_DVR_StartDownload(m_lUserID, NET_SDK_DOWNLOAD_FILE_FORM_DB, &struParam, sizeof(struParam), m_strFileID);
	if (m_lDownloadHandle >= 0)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StartDownload[%s]", m_strFileID);
		m_timerHandle = SetTimer(DOWNLOAD_DB_FILE_TIMER, 50, NULL);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StartDownload[%s]", m_strFileID);
		char szLan[128] = {0};
		g_StringLanType(szLan, "下载失败", "Download failed");
		AfxMessageBox(szLan);
	}
}



void CDlgVedioImgDB::OnButtonDownloadClose() 
{
	// TODO: Add your control notification handler code here
	if (m_lDownloadHandle != -1)
	{
		char szLan[128] = {0};
		KillTimer(m_timerHandle);
		g_StringLanType(szLan, "停止下载", "Download Stop");
		m_strStatus.Format(szLan);

		NET_DVR_StopDownload(m_lDownloadHandle);
		m_lDownloadHandle = -1;
	}

	if (m_fp != NULL)
	{
		fclose(m_fp);
		m_fp = NULL;	
	}
}

void CDlgVedioImgDB::OnButtonControlSpeed() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	if (m_lDownloadHandle == -1)
	{
        g_StringLanType(szLan, "下载还未开始", "Download not start");
        AfxMessageBox(szLan);
        return;
	}

	UpdateData(TRUE);
	NET_DVR_DOWNLOAD_QOS struQos = {0};
	struQos.dwMaxSpeed = m_dwSpeed;

	if(!NET_DVR_DownloadControl(m_lDownloadHandle, ENUM_DOWNLOAD_CONTROL_QOS, &struQos, sizeof(struQos), NULL, 0))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "ENUM_DOWNLOAD_CONTROL_QOS");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "ENUM_DOWNLOAD_CONTROL_QOS");
    }
	
}

#if (_MSC_VER >= 1500)	//vs2008
void CDlgVedioImgDB::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgVedioImgDB::OnTimer(UINT nIDEvent) 
#endif
{
	// TODO: Add your message handler code here and/or call default
	char szLan[128] = {0};
	if (nIDEvent == DOWNLOAD_DB_FILE_TIMER)
	{
		DWORD dwProgress = 0;
		DWORD dwState = 0;
		dwState = NET_DVR_GetDownloadState(m_lDownloadHandle, &dwProgress);
		
		if (dwState == 1)
		{
			g_StringLanType(szLan, "下载成功", "Download successfully");
			m_strStatus.Format(szLan);


		}
		else if (dwState == 2)
		{
			g_StringLanType(szLan, "正在下载,已下载:%d", "Is Downloading,progress:%d");
			m_strStatus.Format(szLan, dwProgress);
		}
		else if (dwState == 3)
		{
			g_StringLanType(szLan, "下载失败", "Download failed");
			m_strStatus.Format(szLan);
		}
		else if (dwState == 4)
		{
			g_StringLanType(szLan, "网络断开，状态未知", "Network disconnect, status unknown");
			m_strStatus.Format(szLan);
			if (100 == dwProgress )
			{
				KillTimer(DOWNLOAD_DB_FILE_TIMER);
				g_StringLanType(szLan, "下载成功", "Download successfully");
				m_strStatus.Format(szLan);
			}
			
		}
		
		if (dwState != 2)
		{        
			KillTimer(DOWNLOAD_DB_FILE_TIMER);
			NET_DVR_StopDownload(m_lDownloadHandle);
			m_lDownloadHandle = -1;

			if (m_fp != NULL)
			{
				fclose(m_fp);
				m_fp = NULL;	
			}
		}

		

	}
	else if(nIDEvent == UPLOAD_DB_FILE_TIMER)
	{
		DWORD dwProgress = 0;
		int state = NET_DVR_GetUploadState(m_lUploadHandle, &dwProgress);
		
		if (state == 1)
		{
			g_StringLanType(szLan, "上传成功", "Upload successfully");
			m_strStatus.Format(szLan);
		}
		else if (state == 2)
		{
			g_StringLanType(szLan, "正在上传", "Is uploading");
			m_strStatus.Format(szLan);
		}
		else if (state == 3)
		{
			g_StringLanType(szLan, "上传失败", "Upload failed");
			m_strStatus.Format(szLan);
		}
		else if (state == 4)
		{
			g_StringLanType(szLan, "网络断开，状态未知", "Network disconnect, status unknown");
			m_strStatus.Format(szLan);
		}
		
		// 		g_StringLanType(szLan, "上传状态%d", "Upload successfully");
		// 		m_strUploadStatus.Format(szLan,state);
		if (state != 2)
		{        
			KillTimer(UPLOAD_DB_FILE_TIMER);
			NET_DVR_UploadClose(m_lUploadHandle);
		}
	}
	
	UpdateData(FALSE);
	CDialog::OnTimer(nIDEvent);
}
