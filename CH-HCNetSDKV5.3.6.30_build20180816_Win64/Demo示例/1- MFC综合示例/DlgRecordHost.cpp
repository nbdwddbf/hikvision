// DlgRecordHost.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRecordHost.h"
#include "DlgRecordHostCfg.h"
#include "DlgSDIAutoTrackCfg.h"
#include "DlgRecordPublishCfg.h"
#include "DlgRecordControl.h"
#include "DlgRecordHostEndTime.h"
#include "DlgOneKeyPublish.h"
#include "DlgCourseInfo.h"
#include "DlgCourseCfg.h"
#include "DlgOneKeyBackupCfg.h"
#include "DlgRecordHostRTMPCfg.h"
#include "DlgRecordHostFilePublish.h"
#include "DlgRecordHostFilmModeCfg.h"
#include "DlgRecordHostDirectedStrategyCfg.h"
#include "DlgRecordHostFrameCfg.h"
#include "DlgRecordHostAudioEffectiveCfg.h"
#include "DlgRecordHostBackgroundPicCfg.h"
#include "DlgRecordHostVideoCfg.h"
#include "DlgRecordStatus.h"
#include "DlgCourseList.h"
#include "DlgImageDiffDetectionCfg.h"
#include "DlgRecordHostClassDataStatistic.h"
#include "DlgRecordHostDirectedAdvanceCfg.h"
#include "DlgRecordHostEducationServerCfg.h"
#include "DlgRecordHostVedioSwitchConfig.h"
#include "DlgRecordHostVideoTitleConfig.h"
#include "DlgUploadLogo.h"
#include "DlgPictureSwitchCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgRecordHost dialog


DlgRecordHost::DlgRecordHost(CWnd* pParent /*=NULL*/)
	: CDialog(DlgRecordHost::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgRecordHost)
	m_nMirrorNum = 0;
	m_nStartChannel = 0;
	//}}AFX_DATA_INIT
	m_iDeviceIndex = 0;
	m_lServerID = 0;
}


void DlgRecordHost::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgRecordHost)
	DDX_Text(pDX, IDC_MIRROR_NUM, m_nMirrorNum);
	DDX_Text(pDX, IDC_START_CHANNEL, m_nStartChannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgRecordHost, CDialog)
	//{{AFX_MSG_MAP(DlgRecordHost)
	ON_BN_CLICKED(IDC_BTN_RECORD_HOST_CFG, OnBtnRecordHostCfg)
	ON_BN_CLICKED(IDC_BTN_SDI_AUTO_TRACK, OnBtnSdiAutoTrack)
	ON_BN_CLICKED(IDC_BTN_PUBLISH_CFG, OnBtnPublishCfg)
	ON_BN_CLICKED(IDC_BTN_RECORD_CONTROL, OnBtnRecordControl)
	ON_BN_CLICKED(IDC_BTN_GET_END_TIME, OnBtnGetEndTime)
	ON_BN_CLICKED(IDC_BTN_PUBLISH, OnBtnPublish)
	ON_BN_CLICKED(IDC_BTN_COURSE_CFG, OnBtnCourseCfg)
	ON_BN_CLICKED(IDC_BTN_CURRICULUM_CFG, OnBtnCurriculumCfg)
	ON_BN_CLICKED(IDC_BTN_PPT_DETECT, OnBtnPptDetect)
    ON_BN_CLICKED(IDC_BTN_BACKUP, OnBtnBackupCfg)
	ON_BN_CLICKED(IDC_BTN_RTMP_CFG, OnBtnRtmpCfg)
    ON_BN_CLICKED(IDC_BTN_FILE_PUBLISH, OnBtnFilePublish)
    ON_BN_CLICKED(IDC_BTN_FILM_MODE, OnBtnFilmMode)
    ON_BN_CLICKED(IDC_BTN_DIRECT_STRATEGY_CFG, OnBtnDirectStrategyCfg)
    ON_BN_CLICKED(IDC_BTN_FRAME_CFG, OnBtnFrameCfg)
    ON_BN_CLICKED(IDC_BTN_AUDIO_EFFECT_CFG, OnBtnAudioEffectCfg)
    ON_BN_CLICKED(IDC_BTN_BACKGROUND_PIC_CFG, OnBtnBackgroundPicCfg)
	ON_BN_CLICKED(IDC_BTN_VIDEO_CFG, OnBtnVideoCfg)
	ON_BN_CLICKED(IDC_BTN_RECORD_STATUS, OnBtnGetRecordStatus)
	ON_BN_CLICKED(IDC_BUTTON_GET_COURSE_LIST, OnButtonGetCourseList)
	ON_BN_CLICKED(IDC_BTN_IMAGE_DIFF_DETECTION_CFG, OnBtnImageDiffDetectionCfg)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_CLASSDATA_STATISTIC, &DlgRecordHost::OnBnClickedBtnClassdataStatistic)
	ON_BN_CLICKED(IDC_BTN_DIRECTED_ADVANCE_CFG, &DlgRecordHost::OnBnClickedBtnDirectedAdvanceCfg)
    ON_BN_CLICKED(IDC_BUTTON_VIDEOSWITCHCONFIG, &DlgRecordHost::OnBnClickedButtonVideoswitchconfig)
    ON_BN_CLICKED(IDC_BTN_EDUCATION_SERVER_CFG, &DlgRecordHost::OnBnClickedBtnEducationServerCfg)
    ON_BN_CLICKED(IDC_BTN_VIDEO_TITLE_CONFIG, &DlgRecordHost::OnBnClickedBtnVideoTitleConfig)
    ON_BN_CLICKED(IDC_BTN_UPLOAD_LOGO, &DlgRecordHost::OnBnClickedBtnUploadLogo)
    ON_BN_CLICKED(IDC_BTN_PICTURE_SWITCH_CTRL, &DlgRecordHost::OnBnClickedBtnPictureSwitchCtrl)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgRecordHost message handlers

BOOL DlgRecordHost::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lServerID =g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	m_nMirrorNum = m_iMirrorNum;
	m_nStartChannel = m_iStartChannel;
	UpdateData(FALSE);
	return TRUE;
}

void DlgRecordHost::OnBtnRecordHostCfg() 
{
	// TODO: Add your control notification handler code here
	DlgRecordHostCfg dlg;
	dlg.m_lUserID = m_lServerID;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.m_iMirrorNum = m_iMirrorNum;
	dlg.m_iStartChannel = m_iStartChannel;
	dlg.DoModal();
}

void DlgRecordHost::OnBtnSdiAutoTrack() 
{
	// TODO: Add your control notification handler code here
	DlgSDIAutoTrackCfg dlg;
	dlg.m_lUserID = m_lServerID;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.m_iMirrorNum = m_iMirrorNum;
	dlg.m_iStartChannel = m_iStartChannel;
	dlg.DoModal();
}

void DlgRecordHost::OnBtnPublishCfg() 
{
	// TODO: Add your control notification handler code here
	DlgRecordPublishCfg dlg;
	dlg.m_lUserID = m_lServerID;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.m_iMirrorNum = m_iMirrorNum;
	dlg.m_iStartChannel = m_iStartChannel;
	dlg.DoModal();
}

void DlgRecordHost::OnBtnRecordControl() 
{
	// TODO: Add your control notification handler code here
	DlgRecordControl dlg;
	dlg.m_lUserID = m_lServerID;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.m_iMirrorNum = m_iMirrorNum;
	dlg.m_iStartChannel = m_iStartChannel;
	dlg.DoModal();
}

void DlgRecordHost::OnBtnGetEndTime() 
{
	// TODO: Add your control notification handler code here
	DlgRecordHostEndTime dlg;
	dlg.m_lUserID = m_lServerID;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.m_iMirrorNum = m_iMirrorNum;
	dlg.m_iStartChannel = m_iStartChannel;
	dlg.DoModal();
}

void DlgRecordHost::OnBtnPublish() 
{
	// TODO: Add your control notification handler code here
	DlgOneKeyPublish dlg;
	dlg.m_lUserID = m_lServerID;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.m_iMirrorNum = m_iMirrorNum;
	dlg.m_iStartChannel = m_iStartChannel;
	dlg.DoModal();
}

void DlgRecordHost::OnBtnCourseCfg() 
{
	// TODO: Add your control notification handler code here
	DlgCourseInfo dlg;
	dlg.m_lUserID = m_lServerID;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.m_iMirrorNum = m_iMirrorNum;
	dlg.m_iStartChannel = m_iStartChannel;
	dlg.DoModal();
}

void DlgRecordHost::OnBtnCurriculumCfg() 
{
	// TODO: Add your control notification handler code here
	DlgCourseCfg dlg;
	dlg.m_lUserID = m_lServerID;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.m_iMirrorNum = m_iMirrorNum;
	dlg.m_iStartChannel = m_iStartChannel;
	dlg.DoModal();
}

#include "DlgPPTDetect.h"
void DlgRecordHost::OnBtnPptDetect() 
{
	// TODO: Add your control notification handler code here
	CDlgPPTDetect dlg;
	dlg.DoModal();
}

void DlgRecordHost::OnBtnBackupCfg() 
{
	// TODO: Add your control notification handler code here
	DlgOneKeyBackupCfg dlg;
	dlg.m_lUserID = m_lServerID;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.m_iStartChannel = m_iStartChannel;
	dlg.DoModal();
}

void DlgRecordHost::OnBtnRtmpCfg() 
{
	// TODO: Add your control notification handler code here
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
    if (iChanIndex < 0)
    {
        iChanIndex = 0;
    }
    if (iChanIndex >= MIRROR_CHAN_INDEX && g_struDeviceInfo[m_iDeviceIndex].byMirrorChanNum > 0)//支持导播通道
    {
        iChanIndex = g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].iChannelNO;
    }
    else
    {
        iChanIndex = g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[iChanIndex].iChannelNO;
    }
    CDlgRecordHostRTMPCfg dlg;
	dlg.m_lUserID = m_lServerID;
    dlg.m_lChannel = iChanIndex;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.DoModal();
}


void DlgRecordHost::OnBtnFilePublish() 
{
    // TODO: Add your control notification handler code here	
    int iChanIndex = g_pMainDlg->GetCurChanIndex();
    if (iChanIndex < 0)
    {
        iChanIndex = 0;//default to config channel one
    }
    if (iChanIndex >= MIRROR_CHAN_INDEX && g_struDeviceInfo[m_iDeviceIndex].byMirrorChanNum > 0)//支持导播通道
    {
        iChanIndex = g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].iChannelNO;
    }
    else
    {
        iChanIndex = g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[iChanIndex].iChannelNO;
    }
    
    CDlgRecordHostFilePublish dlg;
    dlg.m_lLoginID = m_lServerID;
    dlg.m_lChannel = iChanIndex;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
}

void DlgRecordHost::OnBtnFilmMode() 
{
    // TODO: Add your control notification handler code here
    int iChanIndex = g_pMainDlg->GetCurChanIndex();
    if (iChanIndex < 0)
    {
        iChanIndex = 0;//default to config channel one
    }
    CDlgRecordHostFilmModeCfg dlg;
    dlg.m_lLoginID = m_lServerID;
    dlg.m_dwChannel = iChanIndex+g_struDeviceInfo[m_iDeviceIndex].iStartChan;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
    
}

void DlgRecordHost::OnBtnDirectStrategyCfg() 
{
    // TODO: Add your control notification handler code here
    int iChanIndex = g_pMainDlg->GetCurChanIndex();
    if (iChanIndex < 0)
    {
        iChanIndex = 0;//default to config channel one
    }
    CDlgRecordHostDirectedStrategyCfg dlg;
    dlg.m_lUserID = m_lServerID;
    dlg.m_lChannel = iChanIndex+g_struDeviceInfo[m_iDeviceIndex].iStartChan;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
}

void DlgRecordHost::OnBtnFrameCfg() 
{
    // TODO: Add your control notification handler code here
    CDlgRecordHostFrameCfg dlg;
    dlg.m_lUserID = m_lServerID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
}

void DlgRecordHost::OnBtnAudioEffectCfg() 
{
    // TODO: Add your control notification handler code here
    
    CDlgRecordHostAudioEffectiveCfg dlg;
    dlg.m_lUserID = m_lServerID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();	
}

void DlgRecordHost::OnBtnBackgroundPicCfg() 
{
    // TODO: Add your control notification handler code here
    
    CDlgRecordHostBackgroundPicCfg dlg;
    dlg.m_lUserID = m_lServerID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
}

void DlgRecordHost::OnBtnVideoCfg() 
{
    // TODO: Add your control notification handler code here
    CDlgRecordHostVideoCfg dlg;
    dlg.m_lUserID = m_lServerID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();	
}

void DlgRecordHost::OnBtnGetRecordStatus() 
{
	// TODO: Add your control notification handler code here
    CDlgRecordStatus dlg;
    
    dlg.m_lUserID = m_lServerID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.m_iStartChannel = m_iStartChannel;
    dlg.DoModal();	
}

void DlgRecordHost::OnButtonGetCourseList() 
{
    // TODO: Add your control notification handler code here
    DlgCourseList dlg;
    
    dlg.m_lUserID = m_lServerID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
	
}

void DlgRecordHost::OnBtnImageDiffDetectionCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgImageDiffDetectionCfg dlg;
    dlg.m_lServerID = m_lServerID; 
    dlg.m_iDevIndex = m_iDeviceIndex; 

    int iChanIndex = g_pMainDlg->GetCurChanIndex();
    if (iChanIndex < 0)
    {
        iChanIndex = 0;
    }
    if (iChanIndex >= MIRROR_CHAN_INDEX && g_struDeviceInfo[m_iDeviceIndex].byMirrorChanNum > 0)//支持导播通道
    {
        iChanIndex = g_struDeviceInfo[m_iDeviceIndex].struMirrorChan[iChanIndex - MIRROR_CHAN_INDEX].iChannelNO;
    }
    else
    {
        iChanIndex = g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[iChanIndex].iChannelNO;
    }

    dlg.m_iChannel = iChanIndex;

    dlg.DoModal();
}


void DlgRecordHost::OnBnClickedBtnClassdataStatistic()
{
	// TODO:  在此添加控件通知处理程序代码
	CDlgRecordHostClassDataStatistic dlg;
	dlg.m_lUserID = m_lServerID;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.DoModal();
}


void DlgRecordHost::OnBnClickedBtnDirectedAdvanceCfg()
{
	// TODO:  在此添加控件通知处理程序代码
	CDlgRecordHostDirectedAdvanceCfg dlg;
	dlg.m_lUserID = m_lServerID;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.DoModal();
}

void DlgRecordHost::OnBnClickedButtonVideoswitchconfig()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgRecordHostVedioSwitchConfig dlg;
    dlg.m_lUserID = m_lServerID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
}


void DlgRecordHost::OnBnClickedBtnEducationServerCfg()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgRecordHostEducationServerCfg dlg;
    dlg.m_lUserID = m_lServerID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
}


void DlgRecordHost::OnBnClickedBtnVideoTitleConfig()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgRecordHostVideoTitleConfig dlg;
    dlg.m_lUserID = m_lServerID;
    dlg.m_iDeviceIndex = m_iDeviceIndex;
    dlg.DoModal();
}


void DlgRecordHost::OnBnClickedBtnUploadLogo()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgUploadLogo dlg;
    dlg.m_iDevIndex = m_iDeviceIndex;
    dlg.m_lServerID = m_lServerID;
    dlg.DoModal();
}


void DlgRecordHost::OnBnClickedBtnPictureSwitchCtrl()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgPictureSwitchCtrl dlg;
    int iChanIndex = g_pMainDlg->GetCurChanIndex();
    if (iChanIndex < 0)
    {
        iChanIndex = 0;//default to config channel one
    }
    dlg.m_dwChannel = iChanIndex + g_struDeviceInfo[m_iDeviceIndex].iStartChan;
    dlg.m_lUserID = m_lServerID;
    dlg.m_iDevIndex = m_iDeviceIndex;
    dlg.DoModal();
}

