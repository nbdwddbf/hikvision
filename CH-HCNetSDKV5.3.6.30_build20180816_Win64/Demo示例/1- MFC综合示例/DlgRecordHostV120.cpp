// DlgRecordHostV120.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRecordHostV120.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordHostV120 dialog


CDlgRecordHostV120::CDlgRecordHostV120(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRecordHostV120::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRecordHostV120)
	m_csFileID = _T("");
	m_csFileIDCond = _T("");
	m_byPubilshPercent = 0;
	m_startDate = COleDateTime::GetCurrentTime();
	m_startTime = COleDateTime::GetCurrentTime();
	m_stopDate = COleDateTime::GetCurrentTime();
	m_stopTime = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
    m_lLoginID = -1;
    m_iDeviceIndex = -1;
    m_lChannel = -1;
    memset(m_szStatusBuf, 0, sizeof(m_szStatusBuf));

}


void CDlgRecordHostV120::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgRecordHostV120)
    DDX_Control(pDX, IDC_COMBO_PUBLISH_STATUS, m_comPubilshStatus);
    DDX_Control(pDX, IDC_COMBO_EXPORT_TYPE, m_comExportType);
    DDX_Control(pDX, IDC_COMBO_CMD_TYPE, m_comCMDType);
    DDX_Text(pDX, IDC_EDIT_FILEID, m_csFileID);
    DDX_Text(pDX, IDC_EDIT_FILEID_COND, m_csFileIDCond);
    DDX_Text(pDX, IDC_EDIT_PUBILSH_PERCENT, m_byPubilshPercent);
    DDX_DateTimeCtrl(pDX, IDC_START_DATE, m_startDate);
    DDX_DateTimeCtrl(pDX, IDC_START_TIME, m_startTime);
    DDX_DateTimeCtrl(pDX, IDC_STOP_DATE, m_stopDate);
    DDX_DateTimeCtrl(pDX, IDC_STOP_TIME, m_stopTime);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMBO_FILE_TYPE, m_ComboFileType);
}


BEGIN_MESSAGE_MAP(CDlgRecordHostV120, CDialog)
	//{{AFX_MSG_MAP(CDlgRecordHostV120)
	ON_BN_CLICKED(IDC_BUTTON_SET_RECORDING_PUBLISH_FILE, OnButtonSetRecordingPublishFile)
	ON_BN_CLICKED(IDC_BUTTON_GET_PUBLISH_PROGRESS, OnButtonGetPublishProgress)
	ON_BN_CLICKED(IDC_BUTTON_SET_RECORD_VIDEO, OnButtonSetRecordVideo)
	ON_BN_CLICKED(IDC_BUTTON_GET_RECORD_VIDEO, OnButtonGetRecordVideo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordHostV120 message handlers

void CDlgRecordHostV120::OnButtonSetRecordingPublishFile() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_RECORDING_PUBLISH_FILE_CFG struRecordingPublishFile = {0};
    struRecordingPublishFile.byCmdType = m_comCMDType.GetCurSel() + 1;
    memcpy(struRecordingPublishFile.byFileID,  m_csFileID.GetBuffer(0), m_csFileID.GetLength());
    struRecordingPublishFile.struStartTime.wYear = m_startDate.GetYear();
    struRecordingPublishFile.struStartTime.byMonth = m_startDate.GetMonth();
    struRecordingPublishFile.struStartTime.byDay = m_startDate.GetDay();
    struRecordingPublishFile.struStartTime.byHour = m_startTime.GetHour();
    struRecordingPublishFile.struStartTime.byMinute = m_startTime.GetMinute();
    struRecordingPublishFile.struStartTime.bySecond = m_startTime.GetSecond();
    
    struRecordingPublishFile.struEndTime.wYear = m_stopDate.GetYear();
    struRecordingPublishFile.struEndTime.byMonth = m_stopDate.GetMonth();
    struRecordingPublishFile.struEndTime.byDay = m_stopDate.GetDay();
    struRecordingPublishFile.struEndTime.byHour = m_stopTime.GetHour();
    struRecordingPublishFile.struEndTime.byMinute = m_stopTime.GetMinute();
	struRecordingPublishFile.struEndTime.bySecond = m_stopTime.GetSecond();

    struRecordingPublishFile.byFileType = m_ComboFileType.GetCurSel();

    struRecordingPublishFile.dwSize = sizeof(struRecordingPublishFile);
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struRecordingPublishFile;
    struCfg.dwInSize = sizeof(struRecordingPublishFile);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_RECORDING_PUBLISH_FILE, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RECORDING_PUBLISH_FILE");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_RECORDING_PUBLISH_FILE");
    }
}

void CDlgRecordHostV120::OnButtonGetPublishProgress() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_PUBLISH_PROGRESS_COND struPubilshProgressCond = {0};
    struPubilshProgressCond.dwSize = sizeof(struPubilshProgressCond);
    struPubilshProgressCond.dwChannel = m_lChannel;
    memcpy(struPubilshProgressCond.byFileID,  m_csFileIDCond.GetBuffer(0), m_csFileIDCond.GetLength());
    NET_DVR_PUBLISH_PROGRESS_CFG struPubilshProgress = {0};
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &struPubilshProgressCond;
    struCfg.dwCondSize = sizeof(struPubilshProgressCond);
    struCfg.lpOutBuffer = &struPubilshProgress;
    struCfg.dwOutSize = sizeof(struPubilshProgress);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_PUBLISH_PROGRESS, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PUBLISH_PROGRESS");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_PUBLISH_PROGRESS");
    }
    
    m_byPubilshPercent = struPubilshProgress.byPublishPercent;
    m_comPubilshStatus.SetCurSel(struPubilshProgress.byPublishStatus);
    
    UpdateData(FALSE);
}

void CDlgRecordHostV120::OnButtonSetRecordVideo() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_RECORD_VIDEO_CFG struRecordVideo = {0};
    struRecordVideo.byExportType = m_comExportType.GetCurSel();
    struRecordVideo.dwSize = sizeof(struRecordVideo);
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpInBuffer = &struRecordVideo;
    struCfg.dwInSize = sizeof(struRecordVideo);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_RECORD_VIDEO_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_RECORD_VIDEO_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_RECORD_VIDEO_CFG");
    }
}

void CDlgRecordHostV120::OnButtonGetRecordVideo() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_RECORD_VIDEO_CFG struRecordVideo = {0};
    
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_lChannel;
    struCfg.dwCondSize = sizeof(m_lChannel);
    struCfg.lpOutBuffer = &struRecordVideo;
    struCfg.dwOutSize = sizeof(struRecordVideo);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_RECORD_VIDEO_CFG, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_RECORD_VIDEO_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_RECORD_VIDEO_CFG");
    }
    
 
    m_comExportType.SetCurSel(struRecordVideo.byExportType);
 
    UpdateData(FALSE);
}
