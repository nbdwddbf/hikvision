// DlgVcaVQDAlarmPic.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaVQDAlarmPic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDT_TIMER_DOWNLOAD_ALARM_PIC 1002
#define WM_MSG_DOWNLOAD_FINISH       1003
/////////////////////////////////////////////////////////////////////////////
// CDlgVcaVQDAlarmPic dialog


CDlgVcaVQDAlarmPic::CDlgVcaVQDAlarmPic(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaVQDAlarmPic::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaVQDAlarmPic)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lDownloadHandle = -1;
}


void CDlgVcaVQDAlarmPic::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaVQDAlarmPic)
	DDX_Control(pDX, IDC_PROGRESS_DOWNLOAD, m_ctrlDownloadProgress);
	DDX_Control(pDX, IDC_COMBO_VQD_EVENT, m_comboVQDEvent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaVQDAlarmPic, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaVQDAlarmPic)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_DOWNLOAD_ALARMPIC, OnBtnDownloadAlarmPic)
	ON_MESSAGE(WM_MSG_DOWNLOAD_FINISH,OnMsgDownloadAlarmPicFinish)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaVQDAlarmPic message handlers

BOOL CDlgVcaVQDAlarmPic::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitCtrlState();

	return TRUE;
}

void CDlgVcaVQDAlarmPic::OnBtnDownloadAlarmPic() 
{
	DownLoadVQDEventAlarmPic();
	
}

void CDlgVcaVQDAlarmPic::InitCtrlState()
{
	char szText[64] = "\0";
	g_StringLanType(szText, "图像模糊", "Image Blur");
	m_comboVQDEvent.InsertString(0,szText);
	m_comboVQDEvent.SetItemData(0,ENUM_VQD_EVENT_BLUR);
    
	g_StringLanType(szText, "亮度异常", "Brightness Abnormal");
	m_comboVQDEvent.InsertString(1,szText);
	m_comboVQDEvent.SetItemData(1,ENUM_VQD_EVENT_LUMA);
    
	g_StringLanType(szText, "图像偏色", "Image Colour Cast ");
	m_comboVQDEvent.InsertString(2,szText);
	m_comboVQDEvent.SetItemData(2,ENUM_VQD_EVENT_CHROMA);
	
	g_StringLanType(szText, "雪花干扰", "Snowflakes Interference");
	m_comboVQDEvent.InsertString(3,szText);
	m_comboVQDEvent.SetItemData(3,ENUM_VQD_EVENT_SNOW);
	
	g_StringLanType(szText, "条纹干扰", "Streak Interference");
	m_comboVQDEvent.InsertString(4,szText);
	m_comboVQDEvent.SetItemData(4,ENUM_VQD_EVENT_STREAK);
	
	g_StringLanType(szText, "画面冻结", "Image Freeze");
	m_comboVQDEvent.InsertString(5,szText);
	m_comboVQDEvent.SetItemData(5,ENUM_VQD_EVENT_FREEZE);
	
	g_StringLanType(szText, "信号丢失", "Signal Loss");
	m_comboVQDEvent.InsertString(6,szText);
	m_comboVQDEvent.SetItemData(6,ENUM_VQD_EVENT_SIGNAL_LOSS);
	
	g_StringLanType(szText, "云台失控", "PTZ Abnormal");
	m_comboVQDEvent.InsertString(7,szText);
	m_comboVQDEvent.SetItemData(7,ENUM_VQD_EVENT_PTZ);
	
	g_StringLanType(szText, "场景突变", "Scene Change");
	m_comboVQDEvent.InsertString(8,szText);
	m_comboVQDEvent.SetItemData(8,ENUM_VQD_EVENT_SCNENE_CHANGE);
	
	g_StringLanType(szText, "视频异常", "Video Abnormal");
	m_comboVQDEvent.InsertString(9,szText);
	m_comboVQDEvent.SetItemData(1,ENUM_VQD_EVENT_VIDEO_ABNORMAL);
	
	g_StringLanType(szText, "视频遮挡", "Video Block");
	m_comboVQDEvent.InsertString(10,szText);
	m_comboVQDEvent.SetItemData(10,ENUM_VQD_EVENT_VIDEO_BLOCK);

	m_comboVQDEvent.SetCurSel(0);

	m_ctrlDownloadProgress.SetRange(0,100);
}


void CDlgVcaVQDAlarmPic::DownLoadVQDEventAlarmPic()
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

	NET_DVR_VQD_EVENT_COND struEventCond = {0};
	struEventCond.dwChannel = m_lChannel;
	struEventCond.dwEventType = m_comboVQDEvent.GetItemData(m_comboVQDEvent.GetCurSel());
    
	m_lDownloadHandle = NET_DVR_StartDownload(m_lServerID,NET_SDK_DOWNLOAD_VQD_ALARM_PIC,&struEventCond,sizeof(struEventCond),strFilePath);
	if (m_lDownloadHandle == -1)
	{   
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_SDK_DOWNLOAD_VQD_ALARM_PIC Chan[%d]", m_lChannel);
		
		char szText[64] = "\0";
		g_StringLanType(szText, "下载失败", "Download failed");
		AfxMessageBox(szText);
	}
	else
	{
		SetTimer(IDT_TIMER_DOWNLOAD_ALARM_PIC,1000,NULL);
		GetDlgItem(IDC_BTN_DOWNLOAD_ALARMPIC)->EnableWindow(FALSE);
	}
}

LRESULT CDlgVcaVQDAlarmPic::OnMsgDownloadAlarmPicFinish(WPARAM wParam,LPARAM lParam)
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
	
	GetDlgItem(IDC_BTN_DOWNLOAD_ALARMPIC)->EnableWindow(TRUE);
	
	return 0;
}

#if (_MSC_VER >= 1500)	//vs2008
void CDlgVcaVQDAlarmPic::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgVcaVQDAlarmPic::OnTimer(UINT nIDEvent) 
#endif
{
	CDialog::OnTimer(nIDEvent);
	if (nIDEvent == IDT_TIMER_DOWNLOAD_ALARM_PIC)
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
			KillTimer(IDT_TIMER_DOWNLOAD_ALARM_PIC);
			PostMessage(WM_MSG_DOWNLOAD_FINISH,0,lResult);
		}
	}
}