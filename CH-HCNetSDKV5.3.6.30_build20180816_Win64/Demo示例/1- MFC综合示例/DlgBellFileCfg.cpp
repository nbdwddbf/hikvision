// DlgBellFileCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgBellFileCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBellFileCfg dialog
void CALLBACK g_fGetBellCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData);
#define WM_MSG_GETBELL_FINISH 1003
#define WM_MSG_ADD_BELLCFG_TOLIST 1004
#define WM_MSG_UPDATEDATA_INTERFACE   1005

CDlgBellFileCfg::CDlgBellFileCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBellFileCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBellFileCfg)
	m_csBellFilePath = _T("");
	m_dwBellNO = 0;
	//}}AFX_DATA_INIT
	m_iSelectItem = -1;
	m_lServerID = -1;
	m_iDevIndex = -1;
	m_lGetBellHandle = -1;
	m_lSetBellHandle = -1;
}

CDlgBellFileCfg::~CDlgBellFileCfg()
{
}


void CDlgBellFileCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBellFileCfg)
	DDX_Control(pDX, IDC_STATUS_COMBO, m_comboStatus);
	DDX_Control(pDX, IDC_BELLFILE_LIST, m_BellFileList);
	DDX_Text(pDX, IDC_BELLFILEPATH_EDIT, m_csBellFilePath);
	DDX_Text(pDX, IDC_BELLNO_EDIT, m_dwBellNO);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBellFileCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgBellFileCfg)
	ON_BN_CLICKED(IDC_SEARCH_BUTTON, OnSearchButton)
	ON_MESSAGE(WM_MSG_GETBELL_FINISH,OnMsgGetbellCfgFinish)
    ON_MESSAGE(WM_MSG_ADD_BELLCFG_TOLIST,OnMsgAddbellCfgToList)
    ON_MESSAGE(WM_MSG_UPDATEDATA_INTERFACE,OnMsgUpdateData)
	ON_BN_CLICKED(IDC_UPLOAD_BUTTON, OnUploadButton)
	ON_NOTIFY(NM_CLICK, IDC_BELLFILE_LIST, OnClickBellfileList)
	ON_BN_CLICKED(IDC_BROWSE_BUTTON, OnBrowseButton)
	ON_BN_CLICKED(IDC_ADD_BUTTON, OnAddButton)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBellFileCfg message handlers

BOOL CDlgBellFileCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char szLan[64] = {0};

	g_StringLanType(szLan, "上传成功", "UploadSucc");
	m_comboStatus.InsertString(0, szLan);
	g_StringLanType(szLan, "正在上传", "ContinueUploading");
	m_comboStatus.InsertString(1, szLan);
	g_StringLanType(szLan, "上传失败", "UploadFail");
	m_comboStatus.InsertString(2, szLan);
	g_StringLanType(szLan, "网络断开", "NetworkDisconnection");
	m_comboStatus.InsertString(3, szLan);
	g_StringLanType(szLan, "硬盘错误", "HardDiskError");
	m_comboStatus.InsertString(4, szLan);
	g_StringLanType(szLan, "无审讯文件存放盘", "NoInterrogationFileStorageDisc");
	m_comboStatus.InsertString(5, szLan);
	g_StringLanType(szLan, "容量不足", "CapacityInsufficient");
	m_comboStatus.InsertString(6, szLan);
	g_StringLanType(szLan, "设备资源不足", "LackOfEquipmentResources");
	m_comboStatus.InsertString(7, szLan);
	g_StringLanType(szLan, "文件个数超过最大值", "FileNumberMoreThanMaximumValue");
	m_comboStatus.InsertString(8, szLan);
	g_StringLanType(szLan, "未获取状态", "NotGetState");
	m_comboStatus.InsertString(9, szLan);
	m_comboStatus.SetCurSel(9);
	m_comboStatus.EnableWindow(FALSE);

	m_BellFileList.DeleteAllItems();
	g_StringLanType(szLan, "序号", "No");
    m_BellFileList.InsertColumn(0, szLan, LVCFMT_LEFT,40);
	g_StringLanType(szLan, "铃声编号", "BellNo");
    m_BellFileList.InsertColumn(1, szLan, LVCFMT_LEFT,60);
	g_StringLanType(szLan, "铃声名", "BellName");
    m_BellFileList.InsertColumn(2, szLan, LVCFMT_LEFT,100);
	g_StringLanType(szLan, "文件大小", "FileSize");
    m_BellFileList.InsertColumn(3, szLan, LVCFMT_LEFT,60);
	g_StringLanType(szLan, "铃声类型", "BellType");
    m_BellFileList.InsertColumn(4, szLan, LVCFMT_LEFT,60);
	g_StringLanType(szLan, "铃声文件路径", "BellFilePath");
    m_BellFileList.InsertColumn(5, szLan, LVCFMT_LEFT,120);
    m_BellFileList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CALLBACK g_fGetBellCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
	CDlgBellFileCfg* pDlg = (CDlgBellFileCfg*)pUserData;
	if (pDlg == NULL)
	{
		return;
	}
	pDlg->ProcessGetBellCallbackData(dwType,lpBuffer,dwBufLen);
}

LRESULT CDlgBellFileCfg::OnMsgGetbellCfgFinish(WPARAM wParam,LPARAM lParam)
{
	NET_DVR_UploadClose(m_lGetBellHandle);
	m_lGetBellHandle = -1;
    g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_RING_LIST Get finish");
	return 0;
}

LRESULT CDlgBellFileCfg::OnMsgAddbellCfgToList(WPARAM wParam,LPARAM lParam)
{ 
    LPNET_DVR_RING_SEARCH_CFG lpBellCfg = (LPNET_DVR_RING_SEARCH_CFG)wParam; 
    if ( lpBellCfg->dwSize == 0)
    {
        return 0; 
    }
    AddToBellList(*lpBellCfg, lpBellCfg->dwRingID); 
    delete lpBellCfg; 
    return 0; 
}

LRESULT CDlgBellFileCfg::OnMsgUpdateData(WPARAM wParam,LPARAM lParam)
{
    DWORD dwTrue = (DWORD)wParam; 
    UpdateData(dwTrue); 
    return 0; 
}

void CDlgBellFileCfg::AddToBellList(const NET_DVR_RING_SEARCH_CFG& struBellInfo , const DWORD dwBellNo, CString strFilePath)
{
	LPNET_DVR_RING_SEARCH_CFG pBellCfg = NULL;
	char szLan[128] = { 0 };
	CString strItem = "";
	int iIndex = -1;
	if (m_BellFileList.GetItemCount() >= dwBellNo)
	{
		iIndex = struBellInfo.dwRingID - 1;
		pBellCfg = (LPNET_DVR_RING_SEARCH_CFG)m_BellFileList.GetItemData(iIndex);
	}
	else
	{
		pBellCfg = new NET_DVR_RING_SEARCH_CFG;
		iIndex = m_BellFileList.GetItemCount();
		strItem.Format("%d", iIndex + 1);
		m_BellFileList.InsertItem(iIndex, strItem);
	}
	if (iIndex < 0)
	{
		return;
	}
	memcpy(pBellCfg, &struBellInfo, sizeof(struBellInfo));
	m_BellFileList.SetItemData(iIndex, (DWORD)pBellCfg);
	strItem.Format("%d", struBellInfo.dwRingID);
	m_BellFileList.SetItemText(iIndex, 1, strItem);
	m_BellFileList.SetItemText(iIndex, 2, (char *)struBellInfo.byRingName);
    strItem.Format("%d", struBellInfo.dwRingSize);
	m_BellFileList.SetItemText(iIndex, 3, strItem);
	if (struBellInfo.byRingType == 0)
	{
		m_BellFileList.SetItemText(iIndex, 4, "wav");
	}
	else
	{
		m_BellFileList.SetItemText(iIndex, 4, "");
	}
	if (strFilePath == "远程文件")
	{
		g_StringLanType(szLan, "远程文件", "RemoteFile");
		m_BellFileList.SetItemText(iIndex, 5, szLan);
	}
	else
	{
		m_BellFileList.SetItemText(iIndex, 5, strFilePath);
	}
	//delete pBellCfg;
	UpdateData(FALSE);
}

void CDlgBellFileCfg::ProcessGetBellCallbackData(DWORD dwType, void* lpBuffer, DWORD dwBufLen)
{   
	if (dwType == NET_SDK_CALLBACK_TYPE_DATA)
	{
        LPNET_DVR_RING_SEARCH_CFG lpBellCfg =  new NET_DVR_RING_SEARCH_CFG; 
        memcpy(lpBellCfg, lpBuffer, sizeof(*lpBellCfg)); 
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "GetBellFile PROCESSING %d", lpBellCfg->dwRingID);
		PostMessage(WM_MSG_ADD_BELLCFG_TOLIST, (WPARAM)lpBellCfg,0); 
	}
	else if (dwType == NET_SDK_CALLBACK_TYPE_STATUS)
	{
		DWORD dwStatus = *(DWORD*)lpBuffer;
		if (dwStatus == NET_SDK_CALLBACK_STATUS_SUCCESS)
		{
			PostMessage(WM_MSG_GETBELL_FINISH,0,0);
		}
		else if ( dwStatus == NET_SDK_CALLBACK_STATUS_FAILED )
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "GetBellFile STATUS_FAILED");
		}
	}
}

void CDlgBellFileCfg::OnSearchButton() 
{
	// TODO: Add your control notification handler code here
	if (m_lGetBellHandle != -1)
	{
		NET_DVR_StopRemoteConfig(m_lGetBellHandle);
	}
	m_BellFileList.DeleteAllItems();
	UpdateData(TRUE);
	NET_DVR_RING_SEARCH_COND struCond = {0};
	struCond.dwSize = sizeof(struCond);
	struCond.dwRingID = m_dwBellNO;

	m_lGetBellHandle = NET_DVR_StartRemoteConfig(m_lServerID,NET_DVR_GET_RING_LIST,&struCond,sizeof(struCond),g_fGetBellCallback,this);
	if (m_lGetBellHandle == -1)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_RING_LIST");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_RING_LIST");
	}
}

void CDlgBellFileCfg::OnUploadButton() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = { 0 };
	if (m_lSetBellHandle != -1)
	{
		g_StringLanType(szLan, "上传", "Upload");
		SetDlgItemText(IDC_UPLOAD_BUTTON, szLan);
		NET_DVR_UploadClose(m_lSetBellHandle);
		m_lSetBellHandle = -1;
		KillTimer(8);
		return;
	}
	//发送选择项

    if (m_iSelectItem < 0)
    {
        MessageBox("Select list item first"); 
        return ;
    }
	if (m_BellFileList.GetItemText(m_iSelectItem, 5) == "远程文件" || m_BellFileList.GetItemText(m_iSelectItem, 5) == "RemoteFile")
	{
		g_StringLanType(szLan, "远程铃声文件，无法上传！", "Remote bell file, can't upload! ");
		MessageBox(szLan);
		return;
	}
    LPNET_DVR_RING_SEARCH_CFG pSearchData = NULL; 
    pSearchData = (LPNET_DVR_RING_SEARCH_CFG)m_BellFileList.GetItemData(m_iSelectItem);

	NET_DVR_RING_UPLOAD_CFG struSendData = {0};
	struSendData.dwSize = sizeof(NET_DVR_RING_UPLOAD_CFG);
	struSendData.dwRingID = pSearchData->dwRingID;
	strncpy((char *)struSendData.byRingName, (char *)pSearchData->byRingName, NAME_LEN);
	struSendData.dwRingSize = pSearchData->dwRingSize;
	struSendData.byRingType = pSearchData->byRingType;
	
	BYTE byFilePath[256] = {0};
	memcpy(byFilePath, m_BellFileList.GetItemText(m_iSelectItem, 5).GetBuffer(m_BellFileList.GetItemText(m_iSelectItem, 5).GetLength()),\
		m_BellFileList.GetItemText(m_iSelectItem, 5).GetLength());

    m_lSetBellHandle = NET_DVR_UploadFile_V40(m_lServerID,UPLOAD_RING_FILE,&struSendData,0/*sizeof(NET_DVR_RING_UPLOAD_CFG)*/, (char *)byFilePath, NULL, 0);
    if (m_lSetBellHandle == -1)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "UPLOAD_RING_FILE");
    }
    else
    {
		m_comboStatus.SetCurSel(1);
		SetTimer(8, 1000, NULL);
		g_StringLanType(szLan, "停止上传", "StopUpload");
		SetDlgItemText(IDC_UPLOAD_BUTTON, szLan);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "UPLOAD_RING_FILE");               
	}
}

void CDlgBellFileCfg::OnClickBellfileList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    POSITION  iPos = m_BellFileList.GetFirstSelectedItemPosition();
    if (iPos == NULL)
    {
        return;
    }
    m_iSelectItem = m_BellFileList.GetNextSelectedItem(iPos);
	m_BellFileList.SetItemState(m_iSelectItem, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
	UpdateData(FALSE);
	*pResult = 0;
}

void CDlgBellFileCfg::OnBrowseButton() 
{
	// TODO: Add your control notification handler code here
	
	// 设置过滤器  
	char szLan[128] = { 0 };
	g_StringLanType(szLan, "音频文件(*.wav)|*.wav|所有文件(*.*)|*.*||", "Audio file(*.wav)|*.wav|All file(*.*)|*.*||"); 
    // 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szLan, this);
    CString strFilePath;     
	
    // 显示打开文件对话框   
    if (IDOK == fileDlg.DoModal())     
    {   
        // 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里     
        strFilePath = fileDlg.GetPathName();     
        SetDlgItemText(IDC_BELLFILEPATH_EDIT, strFilePath);     
    }
}

void CDlgBellFileCfg::OnAddButton() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = { 0 };
	CFile oFile;
	CString strFileName = "";
	if (!oFile.Open(m_csBellFilePath, oFile.modeRead))
	{
		g_StringLanType(szLan, "打开文件失败！", "OpenFileFailure");
		MessageBox(szLan);
		return;
	}
	
	NET_DVR_RING_SEARCH_CFG struSendData = {0};
	struSendData.dwSize = sizeof(NET_DVR_RING_SEARCH_CFG);
	struSendData.dwRingID = m_BellFileList.GetItemCount() + 1;
	struSendData.dwRingSize = oFile.GetLength();
	struSendData.byRingType = 0;
	strFileName = oFile.GetFileName();
	int iPos = strFileName.ReverseFind('.');
	memcpy(struSendData.byRingName, strFileName.GetBuffer(strFileName.GetLength()), iPos);
	AddToBellList(struSendData, struSendData.dwRingID, m_csBellFilePath);
	oFile.Close();
	UpdateData(FALSE);

}

void CDlgBellFileCfg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	UpdateData(TRUE);
	int i = 0;
	for (i = 0; i < m_BellFileList.GetItemCount(); i++)
	{
		LPNET_DVR_RING_SEARCH_CFG pSendData = NULL; 
		pSendData = (LPNET_DVR_RING_SEARCH_CFG)m_BellFileList.GetItemData(i);
		if (NULL != pSendData)
		{
			delete pSendData;
			pSendData = NULL;
		}
	}
	if (m_lGetBellHandle != -1)
	{
		NET_DVR_StopRemoteConfig(m_lGetBellHandle);
		m_lGetBellHandle = -1;
	}
	if (m_lSetBellHandle != -1)
	{
		NET_DVR_UploadClose(m_lSetBellHandle);
		m_lSetBellHandle = -1;
		KillTimer(8);
	}
	CDialog::OnClose();
}

#if (_MSC_VER >= 1500)	//vs2008
void CDlgBellFileCfg::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgBellFileCfg::OnTimer(UINT nIDEvent)
#endif
{
	// TODO: Add your message handler code here and/or call default
	DWORD dwProgress = 0;
	LONG lSelectIndex = -1;
	switch(nIDEvent)
	{
	case 8:
		lSelectIndex = NET_DVR_GetUploadState(m_lSetBellHandle, &dwProgress);
		if (lSelectIndex <= 0)
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "GetUploadState"); 
		}
		else if (lSelectIndex == 1)
		{
			m_comboStatus.SetCurSel(lSelectIndex - 1);
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "GetUploadState Finish"); 
		}
		else if(lSelectIndex <= 4)
		{
			m_comboStatus.SetCurSel(lSelectIndex - 1);
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "GetUploadState"); 
		}
		else if (lSelectIndex > 4)
		{
			m_comboStatus.SetCurSel(lSelectIndex - 2);
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "GetUploadState"); 
		}
		if (lSelectIndex != 2)
		{
			SetDlgItemText(IDC_UPLOAD_BUTTON, "上传");
			NET_DVR_UploadClose(m_lSetBellHandle);
			m_lSetBellHandle = -1;
			KillTimer(8);
		}
		UpdateData(FALSE);
		break;
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}
