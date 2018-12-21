// DlgAudioUploadDownload.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAudioUploadDownload.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define UPLOADSTART 1
#define DOWNLOADSTART 2
/////////////////////////////////////////////////////////////////////////////
// CDlgAudioUploadDownload dialog
void CALLBACK /*DATADOWNLOAD*/AudioDownloadCallBack(LONG nDownloadHandle, DWORD dwDataType, void* pBuffer, DWORD dwBufSize, void *pUser)
{
	CDlgAudioUploadDownload* pAudioDownload = static_cast<CDlgAudioUploadDownload*>(pUser);
	pAudioDownload->m_fileDown.Write(pBuffer, dwBufSize);
}

CDlgAudioUploadDownload::CDlgAudioUploadDownload(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAudioUploadDownload::IDD, pParent)
	,m_pAudioBuf(NULL)
	,m_dwAudioLen(-1)
{
	//{{AFX_DATA_INIT(CDlgAudioUploadDownload)
	m_csDownloadPath = _T("");
	m_csUploadPath = _T("");
	m_csDownload = _T("");
	m_csUpload = _T("");
	m_radioDownload = -1;
	m_radioUpload = -1;
	m_strName = _T("");
	//}}AFX_DATA_INIT
	m_pAudioBuf = new char[1024*1024];
}

CDlgAudioUploadDownload::~CDlgAudioUploadDownload()
{
	if (m_lUploadHandle != -1)
	{
		NET_DVR_StopAudioOperate(m_lUploadHandle);
		m_lUploadHandle = -1;
	}
	if (m_lDownloadHandle != -1)
	{
		NET_DVR_StopAudioOperate(m_lDownloadHandle);
		m_lDownloadHandle = -1;
	}
	if (NULL != m_pAudioBuf)
	{
		delete[] m_pAudioBuf;
	}
}
void CDlgAudioUploadDownload::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAudioUploadDownload)
	DDX_Control(pDX, IDC_COMBO_AUDIONUM, m_cmAudioNum);
	DDX_Control(pDX, IDC_COMBO_CTRLPARAM, m_cmAudioCtrl);
	DDX_Control(pDX, IDC_PROGRESS_UPLOAD, m_progressUpload);
	DDX_Control(pDX, IDC_PROGRESS_DOWNLOAD, m_progressDownload);
	DDX_Text(pDX, IDC_EDIT_DOWNLOAD, m_csDownloadPath);
	DDX_Text(pDX, IDC_EDIT_UPLOAD, m_csUploadPath);
	DDX_Text(pDX, IDC_STATIC_DOWNLOAD, m_csDownload);
	DDX_Text(pDX, IDC_STATIC_UPLOAD, m_csUpload);
	DDX_Radio(pDX, IDC_RADIO_DOWNLOAD_BYFILE, m_radioDownload);
	DDX_Radio(pDX, IDC_RADIO_UPLOAD_BYFILE, m_radioUpload);
	DDX_Text(pDX, IDC_EDT_SETAUDIONAME, m_strName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAudioUploadDownload, CDialog)
	//{{AFX_MSG_MAP(CDlgAudioUploadDownload)
	ON_BN_CLICKED(IDC_BTN_UPLOAD_START, OnBtnUploadStart)
	ON_BN_CLICKED(IDC_BTN_UPLOADPATH, OnBtnUploadpath)
	ON_BN_CLICKED(IDC_BTN_UPLOAD_STOP, OnBtnUploadStop)
	ON_BN_CLICKED(IDC_BTN_DOWNLOAD_START, OnBtnDownloadStart)
	ON_BN_CLICKED(IDC_BTN_DOWNLOAD_STOP, OnBtnDownloadStop)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_CTRL, OnBtnCtrl)
	ON_BN_CLICKED(IDC_RADIO_UPLOAD_BYFILE, OnRadioUploadByfile)
	ON_BN_CLICKED(IDC_RADIO_UPLOAD_BYBUFFER, OnRadioUploadBybuffer)
	ON_BN_CLICKED(IDC_RADIO_DOWNLOAD_BYFILE, OnRadioDownloadByfile)
	ON_BN_CLICKED(IDC_RADIO_DOWNLOAD_BYBUFFER, OnRadioDownloadBybuffer)
	ON_BN_CLICKED(IDC_BTN_SETAUDIONAME, OnBtnSetAudioName)
	ON_BN_CLICKED(IDC_BTN_GETAUDIONAME, OnBtnGetAudioName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAudioUploadDownload message handlers

BOOL CDlgAudioUploadDownload::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitComboBox();
	memset(&m_struDownload, 0, sizeof(m_struDownload));
	memset(&m_struUpload, 0, sizeof(m_struUpload));

	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();

	m_progressUpload.SetRange(0,100);
	m_progressUpload.SetPos(0);
	
	m_progressDownload.SetRange(0,100);
	m_progressDownload.SetPos(0);

	m_csDownloadPath.Format("%s", "C:\\Privatetest.wav");
	if(!NET_DVR_GetDeviceAbility(g_struDeviceInfo[m_iDeviceIndex].lLoginID, ALARMHOST_ABILITY, NULL, 0, (char*)&m_struAbility, sizeof(m_struAbility)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetDeviceAbility FAILED");
		//return FALSE;
		CString csStr;
		char szLan[128] = {0};
		for (int i = 0; i < 11; i++) //本来是要获取软硬件能力集的，但是解析起来太麻烦，直接写死十一个，第十一个用于测试异常情况
		{
			g_StringLanType(szLan, "语音", "Audio");
			csStr.Format("%s%d", szLan, i+1);
			m_cmAudioNum.InsertString(i, csStr);
			m_cmAudioNum.SetItemData(i, i);
		}
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetDeviceAbility SUCC");
		CString csStr;
		char szLan[128] = {0};
		if (m_struAbility.byAudioNum > 0)
		{
			m_cmAudioNum.ResetContent();
			for (int i=0; i<m_struAbility.byAudioNum; i++)
			{
				g_StringLanType(szLan, "语音", "Audio");
				csStr.Format("%s%d", szLan, i+1);
				m_cmAudioNum.AddString(csStr);
			}
		}
		else
		{
			//老设备能力集中没有byAudioNum，语音个数是固定值6，包括设备自助行V1.0，ATM防护舱V1.0
			m_cmAudioNum.ResetContent();
			g_StringLanType(szLan, "进门提示音", "Enter door");
			m_cmAudioNum.AddString(szLan);
			g_StringLanType(szLan, "出门提示音", "Exit door");
			m_cmAudioNum.AddString(szLan);
			g_StringLanType(szLan, "有人提示音", "Someone in");
			m_cmAudioNum.AddString(szLan);
			g_StringLanType(szLan, "ATM暂停使用", "ATM Suspended");
			m_cmAudioNum.AddString(szLan);
			g_StringLanType(szLan, "门未关", "Door open");
			m_cmAudioNum.AddString(szLan);
			g_StringLanType(szLan, "其他", "other");
			m_cmAudioNum.AddString(szLan);
		}
	}


	m_fileDown.Open("D:\\Privatetest.wav", CFile::modeRead|CFile::modeWrite|CFile::modeNoTruncate|CFile::modeCreate);

	FunEnableWindow(TRUE, UPLOADSTART);
	FunEnableWindow(TRUE, DOWNLOADSTART);
	UpdateData(FALSE);
	return TRUE;  
}

void CDlgAudioUploadDownload::InitComboBox() 
{
	char szLan[128] = {0};
	m_cmAudioCtrl.ResetContent();
	g_StringLanType(szLan, "播放语音", "PLAY AUDIO");
	m_cmAudioCtrl.AddString(szLan);
	g_StringLanType(szLan, "清空语音", "CLEAR AUDIO");
	m_cmAudioCtrl.AddString(szLan);
}

void CDlgAudioUploadDownload::OnBtnUploadStart() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_lPos = 0;
	m_lAudioNum = m_cmAudioNum.GetCurSel()+1;
	//m_lUploadHandle = NET_DVR_StartUploadAudio(g_struDeviceInfo[m_iDeviceIndex].lLoginID, m_lAudioNum, 0, sFilePath);
	m_struUpload.dwSize = sizeof(NET_DVR_UPLOAD_PARAM);
	m_struUpload.byDataNum = m_lAudioNum;
	m_struUpload.byDataType = 1;
	m_struUpload.byAudioType = 0;
	if (m_radioUpload == 0)
	{
		m_struUpload.byUploadType = 1; //从文件中读取数据
		m_struUpload.lpBuffer = NULL;
		m_struUpload.dwBufferSize = 0;
		if (0 == m_csUploadPath.GetLength())
		{
			MessageBox("Please Input File Path.\n");
			return;
		}
		else
		{
			sprintf(m_struUpload.sFileName, "%s", m_csUploadPath);
		}
	}
	else if (m_radioUpload == 1)
	{
		//初始化发送的缓冲区，用来测试
		char sFileName[265] = {0};
		if (0 == m_csUploadPath.GetLength())
		{
			MessageBox("Please Input File Path.\n");
			return;
		}
		else
		{
			sprintf(sFileName, "%s", m_csUploadPath);
		}

		CFile fileTest;
		if (!fileTest.Open(sFileName, CFile::modeRead))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Open AudioFile Failed");
			return;
		}
		m_dwAudioLen = fileTest.GetLength();
		fileTest.Read(m_pAudioBuf, m_dwAudioLen);
		fileTest.Close();
		//固定将文件“c:\Privatetest.wav”的数据读入到缓冲区，然后发送给设备（这个只是做测试用）
		m_struUpload.byUploadType = 2;//从缓冲区读取数据
		m_struUpload.lpBuffer = m_pAudioBuf;
		m_struUpload.dwBufferSize = m_dwAudioLen;
		memset(m_struUpload.sFileName, 0, sizeof(m_struUpload.sFileName));
	}
	else
	{
		g_StringLanType(m_szLan, "请选择数据传入方式", "Please Select Type of Inputting data.\n");
		MessageBox(m_szLan);
		return;
	}
	CString csStr;
	m_lUploadHandle =  NET_DVR_StartUploadFile(g_struDeviceInfo[m_iDeviceIndex].lLoginID, &m_struUpload);
	if(m_lUploadHandle == -1)
	{
		csStr.Format("%s", "NET_DVR_StartUploadFile FAILED");
		MessageBox(csStr);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartUploadFile FAILED");
		return ;
	}
	else
	{
		FunEnableWindow(FALSE, UPLOADSTART);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StartUploadFile SUCC");
	}
	m_lUploadTimer = SetTimer(AUDIOUPLOAD_TIMER, 500, NULL);
}

void CDlgAudioUploadDownload::OnBtnUploadpath() 
{
	// TODO: Add your control notification handler code here
	static char szFilter[]="All File(*.*)|*.*||";
	CFileDialog dlg(TRUE,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	if (dlg.DoModal()==IDOK)
	{
		m_csUploadPath = dlg.GetPathName();
//		memcpy(m_struUpload.sFileName, m_csUploadPath, m_csUploadPath.GetLength());
		UpdateData(FALSE);
	}
}

void CDlgAudioUploadDownload::OnBtnUploadStop() 
{
	// TODO: Add your control notification handler code here
	CString csStr;
	//if(!NET_DVR_StopAudioOperate(m_lUploadHandle))
	if (!NET_DVR_StopUploadFile(m_lUploadHandle))
	{
		csStr.Format("%s", "NET_DVR_StopAudioOperate FAILED");
		MessageBox(csStr);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopUploadFile FAILED");
	}
	else
	{
		m_lUploadHandle = -1;
		FunEnableWindow(TRUE, UPLOADSTART);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopUploadFile SUCC");
	}
}

void CDlgAudioUploadDownload::OnBtnDownloadStart() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString csStr;
	m_lPos = 0;
	m_lAudioNum = m_cmAudioNum.GetCurSel()+1;
	m_struDownload.dwSize = sizeof(m_struDownload);
	m_struDownload.byDataNum = m_lAudioNum;
	m_struDownload.byDataType = 1;
	if (m_radioDownload == 0)
	{
		char sFilePath[260] = {0};
		sprintf(m_struDownload.sFileName, "%s", m_csDownloadPath);
		m_struDownload.byDownType = 1; //保存到文件
		m_struDownload.lpDataCallBack = NULL;
		m_struDownload.pUserData = NULL;
	}
	else if (1 == m_radioDownload)
	{
		memset(m_struUpload.sFileName, 0, sizeof(m_struUpload.sFileName));
		m_struDownload.lpDataCallBack = AudioDownloadCallBack;
		m_struDownload.byDownType = 2;
		m_struDownload.pUserData = this;
	}
	else
	{
		g_StringLanType(m_szLan, "请选择数据保存方式", "Please Select Type of Saving data.\n");
		MessageBox(m_szLan);
		return;
	}
	//m_lDownloadHandle = NET_DVR_StartDownloadAudio(g_struDeviceInfo[m_iDeviceIndex].lLoginID, m_lAudioNum, sFilePath);
	m_lDownloadHandle = NET_DVR_StartDownloadFile(g_struDeviceInfo[m_iDeviceIndex].lLoginID, &m_struDownload);
	if (m_lDownloadHandle == -1)
	{
		csStr.Format("%s", "NET_DVR_StartDownloadAudio FAILED");
		MessageBox(csStr);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartDownloadAudio FAILED");
	}
	else
	{
		FunEnableWindow(FALSE, DOWNLOADSTART);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StartDownloadAudio SUCC");
	}
	m_lDownloadTimer = SetTimer(AUDIODOWNLOAD_TIMER, 500, NULL);
}

void CDlgAudioUploadDownload::OnBtnDownloadStop() 
{
	// TODO: Add your control notification handler code here
	CString csStr;
	//if(!NET_DVR_StopAudioOperate(m_lDownloadHandle))
	if(!NET_DVR_StopDownloadFile(m_lDownloadHandle))
	{
		csStr.Format("%s", "NET_DVR_StopAudioOperate FAILED");
		MessageBox(csStr);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopAudioOperate FAILED");
	}
	else
	{
		m_lDownloadHandle = -1;
		FunEnableWindow(TRUE, DOWNLOADSTART);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopAudioOperate SUCC");
	}
}

void CDlgAudioUploadDownload::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

#if (_MSC_VER >= 1500)	//vs2008
void CDlgAudioUploadDownload::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgAudioUploadDownload::OnTimer(UINT nIDEvent)
#endif
{
	// TODO: Add your message handler code here and/or call default
	UpdateData(TRUE);
	m_lAudioNum = m_cmAudioNum.GetCurSel() + 1;
	char szLan[128] = {0};
	CString csStr;
	if (nIDEvent == AUDIOUPLOAD_TIMER)
	{
		//m_lPos = NET_DVR_GetAudioProgress(m_lUploadHandle);
		m_lPos = NET_DVR_GetUploadFileProgress(m_lUploadHandle);
		m_progressUpload.SetPos(m_lPos);
		//if (m_lPos == 100)
		if(1 == NET_DVR_GetUploadFileState(m_lUploadHandle))
		{
			m_csUpload.Format("上传完成");
			if (!NET_DVR_StopUploadFile(m_lUploadHandle) && m_lUploadHandle>=0)
			{
				csStr.Format("%s", "NET_DVR_StopUploadFile FAILED");
				MessageBox(csStr);
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopUploadFile FAILED");
			}
			else
			{
				FunEnableWindow(TRUE, UPLOADSTART);
				m_lUploadHandle = -1;
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopUploadFile SUCC");
			}
		}
		else if(2 == NET_DVR_GetUploadFileState(m_lUploadHandle))
		{
			m_csUpload.Format("上传%%%d", m_lPos);
		}
		else if (3 == NET_DVR_GetUploadFileState(m_lUploadHandle))
		{
			m_csUpload.Format("上传失败");
		}
		UpdateData(FALSE);
	}
	else if (nIDEvent == AUDIODOWNLOAD_TIMER)
	{
		//m_lPos = NET_DVR_GetAudioProgress(m_lDownloadHandle);
		m_lPos = NET_DVR_GetDownloadFileProgress(m_lDownloadHandle);
		m_progressDownload.SetPos(m_lPos);
		if (1 == NET_DVR_GetDownloadFileState(m_lDownloadHandle))
		{
			m_csDownload.Format("下载完成");
			if (!NET_DVR_StopAudioOperate(m_lDownloadHandle))
			{
				csStr.Format("%s", "NET_DVR_StopAudioOperate FAILED");
				MessageBox(csStr);
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopAudioOperate FAILED");
			}
			else
			{
				FunEnableWindow(TRUE, DOWNLOADSTART);
				m_lDownloadHandle = -1;
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopAudioOperate SUCC");
			}
		}
		else if(2 == NET_DVR_GetDownloadFileState(m_lDownloadHandle))
		{
			m_csDownload.Format("下载%%%d", m_lPos);
		}
		else if (3 == NET_DVR_GetDownloadFileState(m_lDownloadHandle))
		{
			m_csDownload.Format("下载失败");
		}
		UpdateData(FALSE);
	}
	CDialog::OnTimer(nIDEvent);
}

void CDlgAudioUploadDownload::OnBtnCtrl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwCtrlParam = m_cmAudioCtrl.GetCurSel() + 1;
	CString csStr;
	m_lAudioNum = m_cmAudioNum.GetCurSel() + 1;
	if (!NET_DVR_AudioCtrl(g_struDeviceInfo[m_iDeviceIndex].lLoginID, m_lAudioNum, dwCtrlParam))
	{
		csStr.Format("%s", "NET_DVR_AudioCtrl FAILED");
		MessageBox(csStr);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_AudioCtrl FAILED");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_AudioCtrl SUCC");
	}
}

void CDlgAudioUploadDownload::FunEnableWindow(BOOL bEnableStart, BYTE byType)
{
	if (byType == UPLOADSTART)//
	{
		GetDlgItem(IDC_BTN_UPLOAD_START)->EnableWindow(bEnableStart);
		GetDlgItem(IDC_BTN_UPLOAD_STOP)->EnableWindow(!bEnableStart);
	}
	else if (byType == DOWNLOADSTART)
	{
		GetDlgItem(IDC_BTN_DOWNLOAD_START)->EnableWindow(bEnableStart);
		GetDlgItem(IDC_BTN_DOWNLOAD_STOP)->EnableWindow(!bEnableStart);
	}
	UpdateData(FALSE);
}

void CDlgAudioUploadDownload::OnRadioUploadByfile() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	//sprintf(m_struUpload.sFileName, "%s", m_csUploadPath);
}

void CDlgAudioUploadDownload::OnRadioUploadBybuffer() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

}

void CDlgAudioUploadDownload::OnRadioDownloadByfile() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

}

void CDlgAudioUploadDownload::OnRadioDownloadBybuffer() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

}

void CDlgAudioUploadDownload::OnBtnSetAudioName() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	//条件
	NET_DVR_CHANNEL_INDEX struChanIndex = {0};
	struChanIndex.dwChannel = 1;
	struChanIndex.dwIndex = m_cmAudioNum.GetCurSel() + 1;
	struChanIndex.dwSize = sizeof(NET_DVR_CHANNEL_INDEX);

	NET_DVR_AUDIO_NAME struAudioName = {0};
	struAudioName.dwSize = sizeof(NET_DVR_AUDIO_NAME);

    sprintf(struAudioName.cName, m_strName, NAME_LEN);

	DWORD dwRet = 0;
	BOOL bRet = NET_DVR_SetDeviceConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_SET_AUDIO_NAME, 1, &struChanIndex, sizeof(struChanIndex),
		&dwRet, &struAudioName, sizeof(struAudioName));
	if (!bRet || dwRet != 0)
	{
		CString csStr;
		csStr.Format("%s", "NET_DVR_SET_AUDIO_NAME FAILED");
		MessageBox(csStr);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_AUDIO_NAME FAILED");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_AUDIO_NAME SUCC");
	}
}

void CDlgAudioUploadDownload::OnBtnGetAudioName() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	//条件
	NET_DVR_CHANNEL_INDEX struChanIndex = {0};
	struChanIndex.dwChannel = 1;
	struChanIndex.dwIndex = m_cmAudioNum.GetCurSel() + 1;
	struChanIndex.dwSize = sizeof(NET_DVR_CHANNEL_INDEX);
	
	NET_DVR_AUDIO_NAME struAudioName = {0};
	struAudioName.dwSize = sizeof(NET_DVR_AUDIO_NAME);
	
	DWORD dwRet = 0;
	BOOL bRet = NET_DVR_GetDeviceConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_GET_AUDIO_NAME, 1, &struChanIndex,
		sizeof(struChanIndex), &dwRet, &struAudioName, sizeof(struAudioName));

	if (bRet = 0 || dwRet != 0)
	{
		CString csStr;
		csStr.Format("%s", "NET_DVR_SET_AUDIO_NAME FAILED");
		MessageBox(csStr);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_AUDIO_NAME FAILED");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_AUDIO_NAME SUCC");
	}

	m_strName.Format("%s", struAudioName.cName);
	UpdateData(FALSE);
}
