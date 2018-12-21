// DlgVcaBaselineScene.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaBaselineScene.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDT_TIMER_DOWNLOAD 1000
#define WM_MSG_DOWNLOAD_FINISH 1001
/////////////////////////////////////////////////////////////////////////////
// CDlgVcaBaselineScene dialog


CDlgVcaBaselineScene::CDlgVcaBaselineScene(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaBaselineScene::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaBaselineScene)
	m_bEnable = FALSE;
	//}}AFX_DATA_INIT
	memset(&m_struBaselienScene,0,sizeof(m_struBaselienScene));
	memset(&m_struCtrlBaselineSceneParam,0,sizeof(m_struCtrlBaselineSceneParam));

	m_lDownloadHandle = -1;
}


void CDlgVcaBaselineScene::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaBaselineScene)
	DDX_Control(pDX, IDC_PROGRESS_DOWNLOAD, m_ctrlDownloadProgress);
	DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaBaselineScene, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaBaselineScene)
	ON_BN_CLICKED(IDC_BTN_UPDATE_BASELINE_SCENE, OnBtnUpdateBaselineScene)
	ON_BN_CLICKED(IDC_BTN_GET_BASELINE_SCENE_PIC, OnBtnGetBaselineScenePic)
	ON_BN_CLICKED(IDC_BTN_GET_BASELINE_SCENE, OnBtnGetBaselineScene)
	ON_BN_CLICKED(IDC_BTN_SET_BASELINE_SCENE, OnBtnSetBaselineScene)
	ON_WM_TIMER()
	ON_MESSAGE(WM_MSG_DOWNLOAD_FINISH,OnMsgDownloadFinished)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaBaselineScene message handlers
BOOL CDlgVcaBaselineScene::OnInitDialog()
{
	CDialog::OnInitDialog();
    m_ctrlDownloadProgress.SetRange(0,100);
	return TRUE;
}

void CDlgVcaBaselineScene::OnBtnGetBaselineScene() 
{
	char szError[32] = "\0";
	if (!GetBaseLineSceneCfg())
	{
       	g_StringLanType(szError, "获取失败","Get failed");
		AfxMessageBox(szError);
		
	}
	else
	{
		LoadBaseLineWndContent();
	}
}

void CDlgVcaBaselineScene::OnBtnSetBaselineScene() 
{
	SaveBaseLineWndContent();
	
	char szError[32] = "\0";
	if (SetBaseLineSceneCfg())
	{
        g_StringLanType(szError, "保存成功","Saved successfully");
	}
	else
	{
		g_StringLanType(szError, "保存失败","Save failed");
	}
	AfxMessageBox(szError);
}

void CDlgVcaBaselineScene::OnBtnUpdateBaselineScene() 
{   
	char szError[32] = "\0";
	if (UpdateBaseLineScene())
	{
		 g_StringLanType(szError, "操作成功","Operate successfully");
	}
	else
	{
		g_StringLanType(szError, "操作失败","Operate failed");
	}
	AfxMessageBox(szError);
}

void CDlgVcaBaselineScene::OnBtnGetBaselineScenePic() 
{
	DownloadBaseLinePic();
	
}

BOOL CDlgVcaBaselineScene::GetBaseLineSceneCfg()
{
	BOOL bRet      = FALSE;
	DWORD dwReturn = 0;
	
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_BASELINE_SCENE,m_lChannel,&m_struBaselienScene,
		sizeof(m_struBaselienScene),&dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_BASELINE_SCENE Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_BASELINE_SCENE Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
	return bRet;
}

BOOL CDlgVcaBaselineScene::SetBaseLineSceneCfg()
{
	BOOL bRet      = FALSE;
	
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_BASELINE_SCENE,m_lChannel,&m_struBaselienScene,
		sizeof(m_struBaselienScene)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_BASELINE_SCENE Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_BASELINE_SCENE Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
	return bRet;
}

BOOL CDlgVcaBaselineScene::UpdateBaseLineScene()
{
	BOOL bRet = FALSE;

	m_struCtrlBaselineSceneParam.dwSize = sizeof(m_struCtrlBaselineSceneParam);
	m_struCtrlBaselineSceneParam.dwChannel = m_lChannel;
	m_struCtrlBaselineSceneParam.byCommand = 2;

	if (!NET_DVR_RemoteControl(m_lServerID,NET_DVR_CONTROL_BASELINE_SCENE,&m_struCtrlBaselineSceneParam,
		sizeof(m_struCtrlBaselineSceneParam)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_CONTROL_BASELINE_SCENE Chan[%d]", m_lChannel);
        bRet = FALSE;
	}
	else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_CONTROL_BASELINE_SCENE Chan[%d]", m_lChannel);
        bRet = TRUE;
    }

	return bRet;
}

void CDlgVcaBaselineScene::DownloadBaseLinePic()
{
	CString strFilter = "jpg(*.jpg)|*.jpg||";
	
	CFileDialog dlg(FALSE,"jpg",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,strFilter,this);
	if (dlg.DoModal() != IDOK)
	{   
		return;
	}
	CString strFilePath = dlg.GetPathName();

	if (m_lDownloadHandle != -1)
	{
		NET_DVR_StopDownload(m_lDownloadHandle);
		m_lDownloadHandle = -1;
	}
    
	m_lDownloadHandle = NET_DVR_StartDownload(m_lServerID,NET_SDK_DOWNLOAD_BASELINE_SCENE_PIC,&m_lChannel,sizeof(DWORD),strFilePath);
	if (m_lDownloadHandle == -1)
	{   
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_SDK_DOWNLOAD_BASELINE_SCENE_PIC Chan[%d]", m_lChannel);

		char szText[64] = "\0";
		g_StringLanType(szText, "下载失败", "Download failed");
		AfxMessageBox(szText);
	}
	else
	{
		SetTimer(IDT_TIMER_DOWNLOAD,1000,NULL);
		GetDlgItem(IDC_BTN_GET_BASELINE_SCENE_PIC)->EnableWindow(FALSE);
	}
}

void CDlgVcaBaselineScene::LoadBaseLineWndContent()
{   
	m_bEnable = m_struBaselienScene.byEnable;
	UpdateData(FALSE);
}

void CDlgVcaBaselineScene::SaveBaseLineWndContent()
{   
	UpdateData(TRUE);
	m_struBaselienScene.dwSize = sizeof(m_struBaselienScene);
	m_struBaselienScene.byEnable = m_bEnable;
}

#if (_MSC_VER >= 1500)	//vs2008
void CDlgVcaBaselineScene::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgVcaBaselineScene::OnTimer(UINT nIDEvent) 
#endif
{
	CDialog::OnTimer(nIDEvent);
	if (nIDEvent == IDT_TIMER_DOWNLOAD)
	{
		if (m_lDownloadHandle == -1)
		{
			return;
		}

		DWORD dwProgress = 0;

		LONG lResult = NET_DVR_GetDownloadState(m_lDownloadHandle,&dwProgress);
		if (lResult == -1)
		{
			return;
		}
		else if (lResult == DOWNLOAD_STATUS_PROCESSING)
		{
			m_ctrlDownloadProgress.SetPos(dwProgress);
		}
		else
		{   
			KillTimer(IDT_TIMER_DOWNLOAD);
			PostMessage(WM_MSG_DOWNLOAD_FINISH,0,lResult);
		}
	}
}

LRESULT CDlgVcaBaselineScene::OnMsgDownloadFinished(WPARAM wParam,LPARAM lParam)
{   
	LONG lStatus = lParam;

	char szText[64] = "\0";
	switch (lStatus)
	{
	case DOWNLOAD_STATUS_FINISH:
		g_StringLanType(szText, "下载完成", "Download completed");
		break;
	case DOWNLOAD_STATUS_PROCESSING:
		g_StringLanType(szText, "正在下载", "Downloading");
		break;
	case DOWNLOAD_STATUS_FAILED:
		g_StringLanType(szText, "下载失败", "Download failed");
		break;
	case DOWNLOAD_STATUS_NETWORK_ERROR:
		g_StringLanType(szText, "网络异常", "Network error");
		break;
	default:
		break;
	}
	NET_DVR_StopDownload(m_lDownloadHandle);
	m_lDownloadHandle = -1;
	m_ctrlDownloadProgress.SetPos(100);
	AfxMessageBox(szText);

	GetDlgItem(IDC_BTN_GET_BASELINE_SCENE_PIC)->EnableWindow(TRUE);
   
	return 0;
}