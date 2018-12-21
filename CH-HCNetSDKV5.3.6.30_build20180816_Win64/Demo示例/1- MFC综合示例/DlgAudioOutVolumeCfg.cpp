// DlgAudioOutVolumeCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAudioOutVolumeCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAudioOutVolumeCfg dialog


CDlgAudioOutVolumeCfg::CDlgAudioOutVolumeCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAudioOutVolumeCfg::IDD, pParent)
    , m_iAudioInIndex(1)
    , m_iAudioInVolume(0)
{
	//{{AFX_DATA_INIT(CDlgAudioOutVolumeCfg)
	//}}AFX_DATA_INIT
}


void CDlgAudioOutVolumeCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgAudioOutVolumeCfg)
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_AUDIO_IN_INDEX, m_iAudioInIndex);
    DDX_Text(pDX, IDC_EDIT_AUDIO_IN_VOLUME, m_iAudioInVolume);
}


BEGIN_MESSAGE_MAP(CDlgAudioOutVolumeCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgAudioOutVolumeCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAudioOutVolumeCfg message handlers
void CDlgAudioOutVolumeCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
	
	char szLan[128] = {0};
	NET_DVR_VOLUME_CFG struVolumeCfg = {0};
	memset(&struVolumeCfg, 0, sizeof(NET_DVR_VOLUME_CFG));

    DWORD dwReturnedBytes = 0;

    if (NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_AUDIOOUT_VOLUME_CFG, m_iAudioInIndex, &struVolumeCfg, sizeof(NET_DVR_VOLUME_CFG), &dwReturnedBytes))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_AUDIOOUT_VOLUME_CFG");
		g_StringLanType(szLan, "获取音频输出口音量调节参数成功!", "Success to get audio out volume parameter config");
		//	AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_AUDIOOUT_VOLUME_CFG");
		g_StringLanType(szLan, "获取音频输出口音量调节参数失败!", "Fail to get audio out volume parameter config");
		AfxMessageBox(szLan);
		return;
	}
	
    m_iAudioInVolume = struVolumeCfg.wVolume[0];

	UpdateData(FALSE);
}

void CDlgAudioOutVolumeCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);
	
	char szLan[128] = {0};
	NET_DVR_VOLUME_CFG struVolumeCfg = {0};
	memset(&struVolumeCfg, 0, sizeof(NET_DVR_VOLUME_CFG));
	
	struVolumeCfg.dwSize = sizeof(NET_DVR_VOLUME_CFG);
	
	struVolumeCfg.wVolume[0] = m_iAudioInVolume;

	if(NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_AUDIOOUT_VOLUME_CFG, m_iAudioInIndex, &struVolumeCfg, sizeof(NET_DVR_VOLUME_CFG)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_AUDIOOUT_VOLUME_CFG");
		g_StringLanType(szLan, "设置音频输出口音量调节参数成功!", "Success to set audio out volume parameter config");
		//	AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_AUDIOOUT_VOLUME_CFG");
		g_StringLanType(szLan, "设置音频输出口音量调节参数失败!", "Fail to set audio out volume parameter config");
		AfxMessageBox(szLan);
		return;
	}
}

BOOL CDlgAudioOutVolumeCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	OnBtnGet();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
