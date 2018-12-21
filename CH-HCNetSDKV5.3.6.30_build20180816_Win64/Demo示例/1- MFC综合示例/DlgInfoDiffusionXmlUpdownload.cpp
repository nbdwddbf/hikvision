// DlgInfoDiffusionXmlUpdownload.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInfoDiffusionXmlUpdownload.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionXmlUpdownload dialog


CDlgInfoDiffusionXmlUpdownload::CDlgInfoDiffusionXmlUpdownload(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInfoDiffusionXmlUpdownload::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInfoDiffusionXmlUpdownload)
	m_szOutputParam = _T("");
	m_szInputParam = _T("");
	m_dwMaterialIndex = 0;
	m_szSavePath = _T("");
	m_szFilePath = _T("");
	//}}AFX_DATA_INIT
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	m_lUpdownloadHandle = -1;
	m_bUploading = FALSE;
	m_bDownloading = FALSE;
}


void CDlgInfoDiffusionXmlUpdownload::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInfoDiffusionXmlUpdownload)
	DDX_Control(pDX, IDC_STATIC_PROGRESS, m_statProgress);
	DDX_Control(pDX, IDC_PROGRESS_UPDOWNLOAD, m_ctrlProgress);
	DDX_Text(pDX, IDC_EDIT_PARAM_OUTPUT, m_szOutputParam);
	DDX_Text(pDX, IDC_EDIT_PARAM_INPUT, m_szInputParam);
	DDX_Text(pDX, IDC_EDIT_MATERIAL_INDEX, m_dwMaterialIndex);
	DDX_Text(pDX, IDC_EDIT_FILE_SAVEPATH, m_szSavePath);
	DDX_Text(pDX, IDC_EDIT_FILE_PATH, m_szFilePath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInfoDiffusionXmlUpdownload, CDialog)
	//{{AFX_MSG_MAP(CDlgInfoDiffusionXmlUpdownload)
	ON_BN_CLICKED(IDC_BTN_UPLOAD, OnBtnUpload)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_DOWNLOAD, OnBtnDownload)
	ON_BN_CLICKED(IDC_BTN_CHOSE_SAVEPATH, OnBtnChoseSavepath)
	ON_BN_CLICKED(IDC_BTN_CHOSE_FILE, OnBtnChoseFile)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionXmlUpdownload message handlers

void CDlgInfoDiffusionXmlUpdownload::OnBtnUpload() 
{
	// TODO: Add your control notification handler code here
	if (m_bUploading || m_bDownloading)
	{
		return;
	}

	UpdateData(TRUE);

	char szOutputBuff[1024] = {0};
	m_lUpdownloadHandle = NET_DVR_UploadFile_V40(m_lUserID, UPLOAD_PUBLISH_MATERIAL, m_szInputParam.GetBuffer(0), m_szInputParam.GetLength(), m_szFilePath.GetBuffer(0), szOutputBuff, sizeof(szOutputBuff));
	if (m_lUpdownloadHandle == -1)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UploadFile_V40 UPLOAD_PUBLISH_MATERIAL");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UploadFile_V40 UPLOAD_PUBLISH_MATERIAL");
	m_bUploading = TRUE;
	m_ctrlProgress.SetPos(0);
	m_statProgress.SetWindowText(_T("0%"));
	SetTimer(TIMER_UPDOWNLOAD_MATERIAL_PROGRESS, 100, NULL);

	m_szOutputParam = szOutputBuff;
	UpdateData(FALSE);
}

void CDlgInfoDiffusionXmlUpdownload::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CDlgInfoDiffusionXmlUpdownload::OnBtnDownload() 
{
	// TODO: Add your control notification handler code here
	if (m_bUploading || m_bDownloading)
	{
		return;
	}
	
	UpdateData(TRUE);
	
	m_lUpdownloadHandle = NET_DVR_StartDownload(m_lUserID, NET_SDK_DOWNLOAD_PUBLISH_MATERIAL, &m_dwMaterialIndex, sizeof(m_dwMaterialIndex), m_szSavePath.GetBuffer(0));
	if (m_lUpdownloadHandle == -1)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartDownload NET_SDK_DOWNLOAD_PUBLISH_MATERIAL");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StartDownload NET_SDK_DOWNLOAD_PUBLISH_MATERIAL");
	m_bDownloading = TRUE;
	m_ctrlProgress.SetPos(0);
	m_statProgress.SetWindowText(_T("0%"));
	SetTimer(TIMER_UPDOWNLOAD_MATERIAL_PROGRESS, 100, NULL);
}

void CDlgInfoDiffusionXmlUpdownload::OnBtnChoseSavepath() 
{
	// TODO: Add your control notification handler code here
	CString strFilter = _T("Picture(*.bmp,*,gif,*.jpg,*.png)|*.bmp;*.gif;*.jpg;*.png|Flash(*.swf)|*.swf|Audio(*.mp3,*.wav,*.wma)|*.mp3;*.wav;*.wma|Video(*.rm,*.rmvb,*.asf,*.avi,*.mpg,*.3gp,*.mov,*.mkv,*.wmv,*.flv,*.mp4)|*.rm;*.rmvb;*.asf;*.avi;*.mpg;*.3gp;*.mov;*.mkv;*.wmv;*.flv;*.mp4|Document(*.txt,*.ppt,*.pptx,*.doc,*.docx,*.xls,*.xlsx,*.pdf)|*.txt;*.ppt;*.pptx;*.doc;*.docx;*.xls;*.xlsx;*.pdf|Template(*.tpl,*.dstpl)|*.tpl;*.dstpl|All Files(*.*)|*.*|");
	CFileDialog fileSave(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
	if (fileSave.DoModal() != IDOK)
	{
		return;
	}
	m_szSavePath = fileSave.GetPathName();
	GetDlgItem(IDC_EDIT_FILE_SAVEPATH)->SetWindowText(m_szSavePath);
}

void CDlgInfoDiffusionXmlUpdownload::OnBtnChoseFile() 
{
	// TODO: Add your control notification handler code here
	CString strFilter = _T("Picture(*.bmp,*,gif,*.jpg,*.png)|*.bmp;*.gif;*.jpg;*.png|Flash(*.swf)|*.swf|Audio(*.mp3,*.wav,*.wma)|*.mp3;*.wav;*.wma|\
		Video(*.rm,*.rmvb,*.asf,*.avi,*.mpg,*.3gp,*.mov,*.mkv,*.wmv,*.flv,*.mp4)|*.rm;*.rmvb;*.asf;*.avi;*.mpg;*.3gp;*.mov;*.mkv;*.wmv;*.flv;*.mp4|\
		Document(*.txt,*.ppt,*.pptx,*.doc,*.docx,*.xls,*.xlsx,*.pdf)|*.txt;*.ppt;*.pptx;*.doc;*.docx;*.xls;*.xlsx;*.pdf|Template(*.tpl,*.dstpl)|*.tpl;*.dstpl|All Files(*.*)|*.*||");
	CFileDialog fileChose(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);
	if (fileChose.DoModal() != IDOK)
	{
		return;
	}
	m_szFilePath = fileChose.GetPathName();
	GetDlgItem(IDC_EDIT_FILE_PATH)->SetWindowText(m_szFilePath);
}

#if (_MSC_VER >= 1500)	//vs2008
void CDlgInfoDiffusionXmlUpdownload::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgInfoDiffusionXmlUpdownload::OnTimer(UINT nIDEvent)
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

BOOL CDlgInfoDiffusionXmlUpdownload::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ctrlProgress.SetRange(0, 100);
	m_ctrlProgress.SetStep(1);
	m_ctrlProgress.SetPos(0);
	m_statProgress.SetWindowText(_T("0%"));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
