// DlgInteractiveFileInfoCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInteractiveFileInfoCfg.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInteractiveFileInfoCfg dialog


CDlgInteractiveFileInfoCfg::CDlgInteractiveFileInfoCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInteractiveFileInfoCfg::IDD, pParent)
    , m_sOtherFileFormat(_T(""))
{
	//{{AFX_DATA_INIT(CDlgInteractiveFileInfoCfg)
	m_csFileName = _T("");
	m_dwFileIndex = 0;
	m_dwFileSize = 0;
	m_dwPPTPage = 0;
	//}}AFX_DATA_INIT
	m_iDevIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lServerID = g_struDeviceInfo[m_iDevIndex].lLoginID;
	m_lChannel = -1;
	m_nCurSelFile = 0;
	m_nFileType = 0;
}


void CDlgInteractiveFileInfoCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgInteractiveFileInfoCfg)
    DDX_Control(pDX, IDC_COM_VIDEOFORMAT, m_comVideoFormat);
    DDX_Control(pDX, IDC_COM_PICFORMAT, m_comPicFormat);
    DDX_Control(pDX, IDC_LIST_FILEINFO, m_listFileInfoCfg);
    DDX_Text(pDX, IDC_EDT_FILENAME, m_csFileName);
    DDX_Radio(pDX, IDC_RAD_PIC, m_nFileType);
    DDX_Text(pDX, IDC_EDT_FILEINDEX, m_dwFileIndex);
    DDX_Text(pDX, IDC_EDT_FILESIZE, m_dwFileSize);
    DDX_Text(pDX, IDC_EDT_PPTPAGE, m_dwPPTPage);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COM_DOCFORMAT, m_cmbDocFormat);
    DDX_Text(pDX, IDC_EDT_OTHERFORMAT, m_sOtherFileFormat);
}


BEGIN_MESSAGE_MAP(CDlgInteractiveFileInfoCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgInteractiveFileInfoCfg)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_RAD_PIC, OnRadPic)
	ON_BN_CLICKED(IDC_RAD_VIDEO, OnRadVideo)
	ON_BN_CLICKED(IDC_BTN_GET_FILEINFO, OnBtnGetFileinfo)
	ON_NOTIFY(NM_CLICK, IDC_LIST_FILEINFO, OnClickListFileinfo)
	ON_BN_CLICKED(IDC_RADIO_ALL, OnRadioAll)
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBtnClear)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_RAD_DOC, &CDlgInteractiveFileInfoCfg::OnBnClickedRadDoc)
    ON_BN_CLICKED(IDC_RAD_OTHER, &CDlgInteractiveFileInfoCfg::OnBnClickedRadOther)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInteractiveFileInfoCfg message handlers
BOOL CDlgInteractiveFileInfoCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    m_listFileInfoCfg.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_listFileInfoCfg.InsertColumn(0, "文件索引", LVCFMT_LEFT,80, -1);	
	m_listFileInfoCfg.InsertColumn(1, "文件类型",LVCFMT_LEFT,80,-1);
    m_listFileInfoCfg.InsertColumn(2, "图片格式",LVCFMT_LEFT,80,-1);
	m_listFileInfoCfg.InsertColumn(3, "视频格式",LVCFMT_LEFT,80,-1);
    m_listFileInfoCfg.InsertColumn(4, "文档格式", LVCFMT_LEFT, 80, -1);
    m_listFileInfoCfg.InsertColumn(5, "其他格式", LVCFMT_LEFT, 80, -1);
    m_listFileInfoCfg.InsertColumn(6, "屏幕文件名",LVCFMT_LEFT,80,-1);
	m_listFileInfoCfg.InsertColumn(7, "文件大小",LVCFMT_LEFT,80,-1);
    m_listFileInfoCfg.InsertColumn(8, "PPT页码值",LVCFMT_LEFT,80,-1);

	UpdateData(FALSE);

	OnRadPic();

    return TRUE;  
}

void CDlgInteractiveFileInfoCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	if (m_nCurSelFile == CB_ERR)
	{
		return;
	}

	UpdateData(TRUE);

	CString strFileIndex;
	strFileIndex = m_listFileInfoCfg.GetItemText(m_nCurSelFile, 0);
	m_lChannel = atoi(strFileIndex);

	m_struScreenFileInfo.dwSize = sizeof(m_struScreenFileInfo);
	strcpy((char*)m_struScreenFileInfo.byFileName, m_csFileName);
	
	NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &m_struScreenFileInfo;
    struCfg.dwInSize = sizeof(m_struScreenFileInfo);
	
	if (!NET_DVR_SetSTDConfig(m_lServerID, NET_DVR_SET_SCREEN_FILEINFO,&struCfg))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SCREEN_FILEINFO");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SCREEN_FILEINFO");
    }
	
	m_listFileInfoCfg.SetItemText(m_nCurSelFile, 6, m_csFileName);
}

void CDlgInteractiveFileInfoCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	if (m_nCurSelFile == CB_ERR)
	{
		return;
	}
	
	CString strFileIndex;
	strFileIndex = m_listFileInfoCfg.GetItemText(m_nCurSelFile, 0);
	m_lChannel = atoi(strFileIndex);
	
	memset(&m_struScreenFileInfo, 0, sizeof(m_struScreenFileInfo));
	m_struScreenFileInfo.dwSize = sizeof(m_struScreenFileInfo);
	
	NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &m_struScreenFileInfo;
    struCfg.dwOutSize = sizeof(m_struScreenFileInfo);
	
	if (!NET_DVR_GetSTDConfig(m_lServerID, NET_DVR_GET_SCREEN_FILEINFO, &struCfg))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SCREEN_FILEINFO");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SCREEN_FILEINFO");
    }
	
	char* pcaFileType[] = {"none", "图片", "视频", "文档", "其他"};
	char* pcaPicFormat[] = {"none", "bmp", "jpeg", "png", "swf", "gif"};
	char* pcaVideoFormat[] = {"none", "avi", "wmv", "mp4", "flv", "vod", "mkv", "rmvb"};
    char* pcaDocFormat[] = { "ppt", "txt", "doc", "xls" };
	CString str;
    m_listFileInfoCfg.SetItemText(m_nCurSelFile, 1, pcaFileType[m_struScreenFileInfo.byFileType]);
    m_listFileInfoCfg.SetItemText(m_nCurSelFile, 2, pcaPicFormat[m_struScreenFileInfo.byPictureFormat]);
    m_listFileInfoCfg.SetItemText(m_nCurSelFile, 3, pcaVideoFormat[m_struScreenFileInfo.byVideoFormat]);
    m_listFileInfoCfg.SetItemText(m_nCurSelFile, 4, pcaDocFormat[m_struScreenFileInfo.byDocumentFormat]);
    m_listFileInfoCfg.SetItemText(m_nCurSelFile, 5, (char*)m_struScreenFileInfo.byOtherFileFormat);
    m_listFileInfoCfg.SetItemText(m_nCurSelFile, 6, (char*)m_struScreenFileInfo.byFileName);
    str.Format("%d", m_struScreenFileInfo.dwFileSize);
    m_listFileInfoCfg.SetItemText(m_nCurSelFile, 7, str);
    str.Format("%d", m_struScreenFileInfo.dwPPTPage);
    m_listFileInfoCfg.SetItemText(m_nCurSelFile, 8, str);
	
	m_dwFileIndex = m_struScreenFileInfo.dwFileIndex;
	m_dwFileSize = m_struScreenFileInfo.dwFileSize;
	m_dwPPTPage = m_struScreenFileInfo.dwPPTPage;
    m_comPicFormat.SetCurSel(m_struScreenFileInfo.byPictureFormat - 1);
    m_comVideoFormat.SetCurSel(m_struScreenFileInfo.byVideoFormat - 1);
    m_cmbDocFormat.SetCurSel(m_struScreenFileInfo.byDocumentFormat);
    m_sOtherFileFormat = m_listFileInfoCfg.GetItemText(m_nCurSelFile, 5);
    m_nFileType = m_struScreenFileInfo.byFileType - 1;
	if (m_nFileType == 0)
	{
		OnRadPic();
	}
    else if (m_nFileType == 1)
    {
        OnRadVideo();
    }
    else if (m_nFileType == 2)
    {
        OnBnClickedRadDoc();
    }
    else if (m_nFileType == 3)
    {
        OnBnClickedRadOther();
    }
	m_csFileName = m_struScreenFileInfo.byFileName;
	
	UpdateData(FALSE);
}

void CDlgInteractiveFileInfoCfg::OnRadPic() 
{
	// TODO: Add your control notification handler code here
	m_nFileType = 0;
	GetDlgItem(IDC_COM_PICFORMAT)->EnableWindow(TRUE);
	GetDlgItem(IDC_COM_VIDEOFORMAT)->EnableWindow(FALSE);
    GetDlgItem(IDC_COM_DOCFORMAT)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDT_OTHERFORMAT)->EnableWindow(FALSE);
}

void CDlgInteractiveFileInfoCfg::OnRadVideo() 
{
	// TODO: Add your control notification handler code here
	m_nFileType = 1;
	GetDlgItem(IDC_COM_PICFORMAT)->EnableWindow(FALSE);
	GetDlgItem(IDC_COM_VIDEOFORMAT)->EnableWindow(TRUE);
    GetDlgItem(IDC_COM_DOCFORMAT)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDT_OTHERFORMAT)->EnableWindow(FALSE);
}

void CDlgInteractiveFileInfoCfg::OnBtnGetFileinfo() 
{
	// TODO: Add your control notification handler code here
	m_listFileInfoCfg.DeleteAllItems();

	NET_DVR_SCREEN_FILE_COND struFileCond = {0};
	struFileCond.dwSize = sizeof(struFileCond);
	struFileCond.byFileType = m_nFileType+1;
	
	LONG lHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_GET_SCREEN_FLIE_LIST, &struFileCond, sizeof(struFileCond), NULL, NULL);
    if (lHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SCREEN_FLIE_LIST");	
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SCREEN_FLIE_LIST");
    }
	
	LONG lStatus = -1;
	memset(&m_struScreenFileInfo, 0, sizeof(m_struScreenFileInfo));
	m_struScreenFileInfo.dwSize = sizeof(m_struScreenFileInfo);
	while (1)
	{
		lStatus = NET_DVR_GetNextRemoteConfig(lHandle, &m_struScreenFileInfo, sizeof(m_struScreenFileInfo));
		if (lStatus == -1)
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetNextRemoteConfig");
			if (!NET_DVR_StopRemoteConfig(lHandle))
			{
				g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopRemoteConfig");
			}
			else
			{
				g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopRemoteConfig");
			}
			break;
		}
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetNextRemoteConfig");
		if (lStatus == 1000) //后面还有数据
		{
			int nFileCount = m_listFileInfoCfg.GetItemCount();
			char* pcaFileType[] = {"none", "图片", "视频", "文档", "其他"};
			char* pcaPicFormat[] = {"none", "bmp", "jpeg", "png", "swf", "gif"};
			char* pcaVideoFormat[] = {"none", "avi", "wmv", "mp4", "flv", "vod", "mkv", "rmvb"};
            char* pcaDocFormat[] = { "ppt", "txt", "doc", "xls" };
			CString str;
			str.Format("%d", m_struScreenFileInfo.dwFileIndex);
			m_listFileInfoCfg.InsertItem(nFileCount, str);
			m_listFileInfoCfg.SetItemText(nFileCount, 1, pcaFileType[m_struScreenFileInfo.byFileType]);
			m_listFileInfoCfg.SetItemText(nFileCount, 2, pcaPicFormat[m_struScreenFileInfo.byPictureFormat]);
			m_listFileInfoCfg.SetItemText(nFileCount, 3, pcaVideoFormat[m_struScreenFileInfo.byVideoFormat]);
            m_listFileInfoCfg.SetItemText(nFileCount, 4, pcaDocFormat[m_struScreenFileInfo.byDocumentFormat]);
            m_listFileInfoCfg.SetItemText(nFileCount, 5, (char*)m_struScreenFileInfo.byOtherFileFormat);
			m_listFileInfoCfg.SetItemText(nFileCount, 6, (char*)m_struScreenFileInfo.byFileName);
			str.Format("%d", m_struScreenFileInfo.dwFileSize);
			m_listFileInfoCfg.SetItemText(nFileCount, 7, str);
			str.Format("%d", m_struScreenFileInfo.dwPPTPage);
			m_listFileInfoCfg.SetItemText(nFileCount, 8, str);
			continue;
		}
		else if (lStatus == 1001) //等待设备发送数据
		{
			Sleep(100);
			continue;
		}
		else
		{
			if (!NET_DVR_StopRemoteConfig(lHandle))
			{
				g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopRemoteConfig");
			}
			else
			{
				g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopRemoteConfig");
			}
			char sTitle[64] = {0};
			char sMsg[64] = {0};
			g_StringLanType(sTitle, "文件参数配置", "File configuration");
			if (lStatus == 1002)
			{
				g_StringLanType(sMsg, "文件列表获取完成", "Get file list successfully.");
			}
			else //1003
			{
				g_StringLanType(sMsg, "文件列表获取失败", "Get file list failed.");
			}
			MessageBox(sMsg, sTitle, MB_OK|MB_ICONWARNING);
			break;
		}
	}
}

void CDlgInteractiveFileInfoCfg::OnClickListFileinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listFileInfoCfg.GetFirstSelectedItemPosition();
	if (pos)
	{
		m_nCurSelFile = m_listFileInfoCfg.GetNextSelectedItem(pos);
		m_dwFileIndex = atoi(m_listFileInfoCfg.GetItemText(m_nCurSelFile, 0));
		char* pcaFileType[] = {"none", "图片", "视频", "文档", "其他"};
		for (int nCnt = 0; nCnt < sizeof(pcaFileType)/sizeof(pcaFileType[0]); nCnt++)
		{
			if (0 == strcmp(pcaFileType[nCnt], m_listFileInfoCfg.GetItemText(m_nCurSelFile, 1)))
			{
				m_nFileType = nCnt - 1;
				break;
			}
		}
		if (m_nFileType == 0)
		{
			OnRadPic();
		}
		else if (m_nFileType == 1)
		{
			OnRadVideo();
		}
        else if (m_nFileType == 2)
        {
            OnBnClickedRadDoc();
        }
        else if (m_nFileType == 3)
        {
            OnBnClickedRadOther();
        }
		m_comPicFormat.SetCurSel(m_comPicFormat.FindString(-1, m_listFileInfoCfg.GetItemText(m_nCurSelFile, 2)));
		m_comVideoFormat.SetCurSel(m_comVideoFormat.FindString(-1, m_listFileInfoCfg.GetItemText(m_nCurSelFile, 3)));
        m_cmbDocFormat.SetCurSel(m_cmbDocFormat.FindString(-1, m_listFileInfoCfg.GetItemText(m_nCurSelFile, 4)));
        m_sOtherFileFormat = m_listFileInfoCfg.GetItemText(m_nCurSelFile, 5);
		m_csFileName = m_listFileInfoCfg.GetItemText(m_nCurSelFile, 6);
		m_dwFileSize = atoi(m_listFileInfoCfg.GetItemText(m_nCurSelFile, 7));
		m_dwPPTPage = atoi(m_listFileInfoCfg.GetItemText(m_nCurSelFile, 8));
		UpdateData(FALSE);
		
		strcpy((char*)m_struScreenFileInfo.byFileName, m_csFileName);
        m_struScreenFileInfo.byFileType = m_nFileType + 1;
        m_struScreenFileInfo.byPictureFormat = m_comPicFormat.GetCurSel() + 1;
        m_struScreenFileInfo.byVideoFormat = m_comVideoFormat.GetCurSel() + 1;
        m_struScreenFileInfo.byDocumentFormat = m_cmbDocFormat.GetCurSel();
        strcpy((char*)m_struScreenFileInfo.byOtherFileFormat, m_sOtherFileFormat);
		m_struScreenFileInfo.dwFileIndex = m_dwFileIndex;
		m_struScreenFileInfo.dwFileIndex = m_dwFileSize;
		m_struScreenFileInfo.dwPPTPage = m_dwPPTPage;
	}
	
	*pResult = 0;
}

void CDlgInteractiveFileInfoCfg::OnRadioAll() 
{
	// TODO: Add your control notification handler code here
	m_nFileType = 0xff;
	GetDlgItem(IDC_COM_PICFORMAT)->EnableWindow(TRUE);
	GetDlgItem(IDC_COM_VIDEOFORMAT)->EnableWindow(TRUE);
    GetDlgItem(IDC_COM_DOCFORMAT)->EnableWindow(TRUE);
    GetDlgItem(IDC_EDT_OTHERFORMAT)->EnableWindow(TRUE);
}

void CDlgInteractiveFileInfoCfg::OnBtnClear() 
{
	// TODO: Add your control notification handler code here
	m_listFileInfoCfg.DeleteAllItems();
	m_nCurSelFile = -1;
}


void CDlgInteractiveFileInfoCfg::OnBnClickedRadDoc()
{
    // TODO:  在此添加控件通知处理程序代码
    m_nFileType = 2;
    GetDlgItem(IDC_COM_PICFORMAT)->EnableWindow(FALSE);
    GetDlgItem(IDC_COM_VIDEOFORMAT)->EnableWindow(FALSE);
    GetDlgItem(IDC_COM_DOCFORMAT)->EnableWindow(TRUE);
    GetDlgItem(IDC_EDT_OTHERFORMAT)->EnableWindow(FALSE);
}


void CDlgInteractiveFileInfoCfg::OnBnClickedRadOther()
{
    // TODO:  在此添加控件通知处理程序代码
    m_nFileType = 3;
    GetDlgItem(IDC_COM_PICFORMAT)->EnableWindow(FALSE);
    GetDlgItem(IDC_COM_VIDEOFORMAT)->EnableWindow(FALSE);
    GetDlgItem(IDC_COM_DOCFORMAT)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDT_OTHERFORMAT)->EnableWindow(TRUE);
}
