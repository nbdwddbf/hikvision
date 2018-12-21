// DlgInteractiveScreenFileUpload.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInteractiveScreenFileUpload.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInteractiveScreenFileUpload dialog


CDlgInteractiveScreenFileUpload::CDlgInteractiveScreenFileUpload(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInteractiveScreenFileUpload::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInteractiveScreenFileUpload)
	m_csFileName = _T("");
	m_dwPPTPage = 0;
	m_dwFileIndex = 0;
	m_szSavePath = _T("");
	//}}AFX_DATA_INIT
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	m_lUpdownloadHandle = -1;
	m_bUploading = FALSE;
	m_bDownloading = FALSE;
	m_sFileName = _T("");
    m_lDownloadHandle = -1;
}


void CDlgInteractiveScreenFileUpload::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgInteractiveScreenFileUpload)
    DDX_Control(pDX, IDC_STAT_PROGRESS, m_statProgress);
    DDX_Control(pDX, IDC_PROGRESS_UPLOAD, m_ctrlProgress);
    DDX_Control(pDX, IDC_COM_VIDEOFORMAT, m_comVideoFormat);
    DDX_Control(pDX, IDC_COM_PICFORMAT, m_comPicFormat);
    DDX_Control(pDX, IDC_COM_FILETYPE, m_comFileType);
    DDX_Text(pDX, IDC_EDT_FILENAME, m_csFileName);
    DDX_Text(pDX, IDC_EDT_PPTPAGE, m_dwPPTPage);
    DDX_Text(pDX, IDC_EDT_FILEINDEX, m_dwFileIndex);
    DDX_Text(pDX, IDC_EDIT_SAVE_PATH, m_szSavePath);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COM_DOCFORMAT, m_cmbDocFormat);
}


BEGIN_MESSAGE_MAP(CDlgInteractiveScreenFileUpload, CDialog)
	//{{AFX_MSG_MAP(CDlgInteractiveScreenFileUpload)
	ON_BN_CLICKED(IDC_BTN_DOWNLOAD, OnBtnDownload)
	ON_BN_CLICKED(IDC_BTN_UPLOAD, OnBtnUpload)
	ON_BN_CLICKED(IDC_BTN_CHOOSE, OnBtnChoose)
	ON_BN_CLICKED(IDC_BTN_SAVE_FILE, OnBtnSaveFile)
	ON_CBN_SELCHANGE(IDC_COM_FILETYPE, OnSelchangeComFiletype)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInteractiveScreenFileUpload message handlers

BOOL CDlgInteractiveScreenFileUpload::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ctrlProgress.SetRange(0, 100);
	m_ctrlProgress.SetStep(1);
	m_ctrlProgress.SetPos(0);
	m_statProgress.SetWindowText(_T("0%"));

	m_comFileType.SetCurSel(0);
	OnSelchangeComFiletype();
	
	return TRUE;  
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgInteractiveScreenFileUpload::OnBtnDownload() 
{
	// TODO: Add your control notification handler code here
	if (m_bUploading || m_bDownloading)
	{
		return;
	}
	
	UpdateData(TRUE);

	memset(&m_struDownload, 0, sizeof(m_struDownload));
	m_struDownload.dwSize = sizeof(m_struDownload);
	m_struDownload.dwFileIndex = m_dwFileIndex;
	m_struDownload.dwPPTPageNo = m_dwPPTPage;
	
	m_lUpdownloadHandle = NET_DVR_StartDownload(m_lUserID, NET_DVR_DOWNLOAD_SCREEN_FILE, &m_struDownload, sizeof(m_struDownload), m_szSavePath.GetBuffer(0));
	if (m_lUpdownloadHandle == -1)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartDownload NET_DVR_DOWNLOAD_SCREEN_FILE");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StartDownload NET_DVR_DOWNLOAD_SCREEN_FILE");
	
	m_bDownloading = TRUE;
	m_ctrlProgress.SetPos(0);
	m_ctrlProgress.SetWindowText(_T("0%"));
	SetTimer(TIMER_UPDOWNLOAD_MATERIAL_PROGRESS, 100, NULL);

// 	NET_DVR_SCREEM_FILE_DOWNLOAD_PARAM struDownloadInfo[4];
// 	for (int nCnt = 0; nCnt < 4; nCnt++)
// 	{
// 		memset(&struDownloadInfo[nCnt], 0, sizeof(NET_DVR_SCREEM_FILE_DOWNLOAD_PARAM));
// 		struDownloadInfo[nCnt].dwSize = sizeof(NET_DVR_SCREEM_FILE_DOWNLOAD_PARAM);
// 		struDownloadInfo[nCnt].dwFileIndex = 1;
// 		struDownloadInfo[nCnt].dwPPTPageNo = nCnt+1;
// 		CString strFileName;
// 		strFileName.Format("%d.bmp", nCnt+1);
// 		strFileName = m_szSavePath + strFileName;
// 		m_lDownloadHandle[nCnt] = NET_DVR_StartDownload(m_lUserID, NET_DVR_DOWNLOAD_SCREEN_FILE, &struDownloadInfo[nCnt], sizeof(struDownloadInfo[nCnt]), strFileName.GetBuffer(0));
// 		if (m_lDownloadHandle[nCnt] == -1)
// 		{
// 			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartDownload NET_DVR_DOWNLOAD_SCREEN_FILE %d", nCnt+1);
// 			return;
// 		}
// 		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StartDownload NET_DVR_DOWNLOAD_SCREEN_FILE %d", nCnt+1);
// 	}
// 	SetTimer(TIMER_UPDOWNLOAD_MATERIAL_PROGRESS, 10, NULL);
}

void CDlgInteractiveScreenFileUpload::OnBtnUpload() 
{
	// TODO: Add your control notification handler code here
	if (m_bUploading || m_bDownloading)
	{
		return;
	}
	
	UpdateData(TRUE);

	if (m_comFileType.GetCurSel() == CB_ERR)
	{
		char sTitle[64] = {0};
		char sMsg[64] = {0};
		g_StringLanType(sTitle, "上传/下载", "Upload/Download");
		g_StringLanType(sMsg, "输入参数不完整", "Input parameter is not enough.");
		MessageBox(sMsg, sTitle, MB_OK|MB_ICONWARNING);
		return;
	}
	
	memset(&m_struUpload, 0, sizeof(m_struUpload));
	m_struUpload.dwSize = sizeof(m_struUpload);
    strcpy((char*)m_struUpload.byFileName, m_sFileName);
    m_struUpload.byFileType = m_comFileType.GetCurSel() + 1;
	if (m_struUpload.byFileType == 1)
	{
        m_struUpload.byPictureFormat = m_comPicFormat.GetCurSel() + 1;
	}
    else if (m_struUpload.byFileType == 2)
	{
        m_struUpload.byVideoFormat = m_comVideoFormat.GetCurSel() + 1;
	}
    else if (m_struUpload.byFileType == 3)
    {
        m_struUpload.byDocumentFormat = m_cmbDocFormat.GetCurSel();
    }
    else if (m_struUpload.byFileType == 4)
    {
        char* pStartPos = strstr((char*)m_struUpload.byFileName, ".");
        strcpy((char*)m_struUpload.byOtherFileFormat, pStartPos + 1);
        int i = 0;
        while (m_struUpload.byOtherFileFormat[i])
        {
            m_struUpload.byOtherFileFormat[i] = toupper(m_struUpload.byOtherFileFormat[i]);
            i++;
        }
    }
	
	DWORD dwFileIndex;
	m_lUpdownloadHandle = NET_DVR_UploadFile_V40(m_lUserID, UPLOAD_SCREEN_FILE, &m_struUpload, sizeof(m_struUpload), m_csFileName.GetBuffer(0), &dwFileIndex, sizeof(dwFileIndex));
	if (m_lUpdownloadHandle == -1)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadFile_V40 UPLOAD_SCREEN_FILE");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadFile_V40 UPLOAD_SCREEN_FILE");
	m_bUploading = TRUE;
	m_ctrlProgress.SetPos(0);
	m_ctrlProgress.SetWindowText(_T("0%"));
	SetTimer(TIMER_UPDOWNLOAD_MATERIAL_PROGRESS, 100, NULL);
	
	UpdateData(FALSE);
}

void CDlgInteractiveScreenFileUpload::OnBtnChoose() 
{
	// TODO: Add your control notification handler code here
	CString strFilter = _T("All Files(*.*)|*.*||");
	CFileDialog fileChose(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
	if (fileChose.DoModal() != IDOK)
	{
		return;
	}
	m_sFileName = fileChose.GetFileName();
	m_csFileName = fileChose.GetPathName();
	GetDlgItem(IDC_EDT_FILENAME)->SetWindowText(m_csFileName);
}

void CDlgInteractiveScreenFileUpload::OnBtnSaveFile() 
{
	// TODO: Add your control notification handler code here
	CString strFilter = _T("All Files(*.*)|*.*|");
	CFileDialog fileSave(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
	if (fileSave.DoModal() != IDOK)
	{
		return;
	}
	m_szSavePath = fileSave.GetPathName();
	GetDlgItem(IDC_EDIT_SAVE_PATH)->SetWindowText(m_szSavePath);
}

void CDlgInteractiveScreenFileUpload::OnSelchangeComFiletype() 
{
	// TODO: Add your control notification handler code here
	int nSel = m_comFileType.GetCurSel();
	if (nSel + 1 == 1)
	{
		GetDlgItem(IDC_COM_PICFORMAT)->EnableWindow(TRUE);
		GetDlgItem(IDC_COM_VIDEOFORMAT)->EnableWindow(FALSE);
        GetDlgItem(IDC_COM_DOCFORMAT)->EnableWindow(FALSE);
	}
    else if (nSel + 1 == 2)
	{
		GetDlgItem(IDC_COM_PICFORMAT)->EnableWindow(FALSE);
		GetDlgItem(IDC_COM_VIDEOFORMAT)->EnableWindow(TRUE);
        GetDlgItem(IDC_COM_DOCFORMAT)->EnableWindow(FALSE);
	}
    else if (nSel + 1 == 3)
    {
        GetDlgItem(IDC_COM_PICFORMAT)->EnableWindow(FALSE);
        GetDlgItem(IDC_COM_VIDEOFORMAT)->EnableWindow(FALSE);
        GetDlgItem(IDC_COM_DOCFORMAT)->EnableWindow(TRUE);
    }
    else if (nSel + 1 == 4)
    {
        GetDlgItem(IDC_COM_PICFORMAT)->EnableWindow(FALSE);
        GetDlgItem(IDC_COM_VIDEOFORMAT)->EnableWindow(FALSE);
        GetDlgItem(IDC_COM_DOCFORMAT)->EnableWindow(FALSE);
    }
}

#if (_MSC_VER >= 1500)	//vs2008
void CDlgInteractiveScreenFileUpload::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgInteractiveScreenFileUpload::OnTimer(UINT nIDEvent)
#endif
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == TIMER_UPDOWNLOAD_MATERIAL_PROGRESS)
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
				m_ctrlProgress.SetPos(dwProgress);
				CString str;
				str.Format("%d", dwProgress);
				str += _T("%");
				m_statProgress.SetWindowText(str);
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
				KillTimer(TIMER_UPDOWNLOAD_MATERIAL_PROGRESS);
				char sTitle[64] = {0};
				char sMsg[64] = {0};
				g_StringLanType(sTitle, "上传/下载", "Upload/Download");
				g_StringLanType(sMsg, "上传/下载完成", "Upload/Download finished.");
				MessageBox(sMsg, sTitle, MB_OK|MB_ICONWARNING);
				break;
			}
		case 2: //正在上传或下载
			{
				m_ctrlProgress.SetPos(dwProgress);
				CString str;
				str.Format("%d", dwProgress);
				str += _T("%");
				m_statProgress.SetWindowText(str);
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
				KillTimer(TIMER_UPDOWNLOAD_MATERIAL_PROGRESS);
				char sTitle[64] = {0};
				char sMsg[64] = {0};
				g_StringLanType(sTitle, "上传/下载", "Upload/Download");
				g_StringLanType(sMsg, "上传/下载失败", "Upload/Download failed.");
				MessageBox(sMsg, sTitle, MB_OK|MB_ICONWARNING);
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
				KillTimer(TIMER_UPDOWNLOAD_MATERIAL_PROGRESS);
				char sTitle[64] = {0};
				char sMsg[64] = {0};
				g_StringLanType(sTitle, "上传/下载", "Upload/Download");
				g_StringLanType(sMsg, "网络断开", "Network disconnection.");
				MessageBox(sMsg, sTitle, MB_OK|MB_ICONWARNING);
				break;
			}
		}
	}
	
	CDialog::OnTimer(nIDEvent);
}
