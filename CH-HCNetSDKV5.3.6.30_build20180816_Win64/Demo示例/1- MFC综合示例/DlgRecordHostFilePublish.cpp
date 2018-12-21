// DlgRecordHostFilePublish.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRecordHostFilePublish.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordHostFilePublish dialog


CDlgRecordHostFilePublish::CDlgRecordHostFilePublish(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRecordHostFilePublish::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRecordHostFilePublish)
		// NOTE: the ClassWizard will add member initialization here
    m_csFileID = _T("");
	m_csFileIDCond = _T("");
    m_csCourseName = _T("");
    m_csInstructorName = _T("");
    m_csCoureDescription = _T("");
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

	//}}AFX_DATA_INIT
}


void CDlgRecordHostFilePublish::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgRecordHostFilePublish)
    // NOTE: the ClassWizard will add DDX and DDV calls here
    DDX_Control(pDX, IDC_COMBO_PUBLISH_STATUS, m_comPubilshStatus);
    DDX_Control(pDX, IDC_COMBO_CMD_TYPE, m_comCMDType);
    DDX_Control(pDX, IDC_COMBO_CHANNEL_NUMBER, m_comChannel);

    DDX_Text(pDX, IDC_EDIT_FILEID, m_csFileID);
    DDX_Text(pDX, IDC_EDIT_FILEID_COND, m_csFileIDCond);
    DDX_Text(pDX, IDC_EDIT_PUBILSH_PERCENT, m_byPubilshPercent);
    DDX_Text(pDX, IDC_EDIT_COURSE_NAME2, m_csCourseName);
    DDX_Text(pDX, IDC_EDIT_INSTRUCTOR_NAME, m_csInstructorName);
    DDX_Text(pDX, IDC_EDIT_COURSE_DESCRIPTION, m_csCoureDescription);
    DDX_DateTimeCtrl(pDX, IDC_START_DATE, m_startDate);
    DDX_DateTimeCtrl(pDX, IDC_START_TIME, m_startTime);
    DDX_DateTimeCtrl(pDX, IDC_STOP_DATE, m_stopDate);
    DDX_DateTimeCtrl(pDX, IDC_STOP_TIME, m_stopTime);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMBO_FILE_TYPE, m_ComboFileType);
}


BEGIN_MESSAGE_MAP(CDlgRecordHostFilePublish, CDialog)
	//{{AFX_MSG_MAP(CDlgRecordHostFilePublish)
	ON_BN_CLICKED(IDC_BUTTON_SET_RECORDING_PUBLISH_FILE, OnButtonSetRecordingPublishFile)
	ON_BN_CLICKED(IDC_BUTTON_GET_PUBLISH_PROGRESS, OnButtonGetPublishProgress)
    ON_BN_CLICKED(IDC_BUTTON_GET_PUBLISH_FILE_INFO, OnButtonGetPublishFileInfo)
    ON_BN_CLICKED(IDC_BUTTON_SET_PUBLISH_FILE_INFO, OnButtonSetPublishFileInfo)
    ON_BN_CLICKED(IDC_RAD_RECORDING_PUBLISH_FILE, OnButtonRecordingPublishFile)
    ON_BN_CLICKED(IDC_RAD_PUBLISH_PROGRESS, OnButtonPublishProgress)
    ON_BN_CLICKED(IDC_RAD_PUBLISH_FILE_INFO, OnButtonPublishInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgRecordHostFilePublish::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_comChannel.SetCurSel(0);
    GetDlgItem(IDC_START_DATE)->EnableWindow(FALSE);
    GetDlgItem(IDC_START_TIME)->EnableWindow(FALSE);
    GetDlgItem(IDC_STOP_DATE)->EnableWindow(FALSE);
    GetDlgItem(IDC_STOP_TIME)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_FILEID)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_CMD_TYPE)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_SET_RECORDING_PUBLISH_FILE)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_FILEID_COND)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_GET_PUBLISH_PROGRESS)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_PUBILSH_PERCENT)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_PUBLISH_STATUS)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_COURSE_NAME2)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_INSTRUCTOR_NAME)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_COURSE_DESCRIPTION)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_GET_PUBLISH_FILE_INFO)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_SET_PUBLISH_FILE_INFO)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_CHANNEL_NUMBER)->EnableWindow(FALSE);

    m_ComboFileType.SetCurSel(0);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordHostFilePublish message handlers

void CDlgRecordHostFilePublish::OnButtonSetRecordingPublishFile() 
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

void CDlgRecordHostFilePublish::OnButtonGetPublishProgress() 
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

void CDlgRecordHostFilePublish::OnButtonGetPublishFileInfo() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_RECORDING_PUBLISH_FILE_INFO struRecordingPublishFileInfo = {0};
    struRecordingPublishFileInfo.dwSize = sizeof(struRecordingPublishFileInfo);

    NET_DVR_RECORDING_PUBLISH_FILE_COND struRecordingPublishFileCond = {0};
    struRecordingPublishFileCond.dwSize = sizeof(struRecordingPublishFileCond);
    struRecordingPublishFileCond.dwChannel = m_lChannel;
    strncpy((char*)(struRecordingPublishFileCond.byFileID), m_csFileID.GetBuffer(m_csFileID.GetLength()), MAX_ID_LEN);

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &struRecordingPublishFileCond;
    struCfg.dwCondSize = sizeof(struRecordingPublishFileCond);
    struCfg.lpOutBuffer = &struRecordingPublishFileInfo;
    struCfg.dwOutSize = sizeof(struRecordingPublishFileInfo);
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_RECORDING_PUBLISH_FILE_INFO, &struCfg))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_RECORDING_PUBLISH_FILE_INFO");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_RECORDING_PUBLISH_FILE_INFO");
    }
    if (struRecordingPublishFileInfo.struStartTime.wYear >= 1900 && struRecordingPublishFileInfo.struStartTime.wYear <= 2100 && struRecordingPublishFileInfo.struStartTime.byMonth >=1 && struRecordingPublishFileInfo.struStartTime.byMonth <= 12 && struRecordingPublishFileInfo.struStartTime.byDay >=1 && struRecordingPublishFileInfo.struStartTime.byDay <= 31 && \
    struRecordingPublishFileInfo.struStartTime.byHour >= 0 && struRecordingPublishFileInfo.struStartTime.byHour <= 24 && struRecordingPublishFileInfo.struStartTime.byMinute >= 0 && struRecordingPublishFileInfo.struStartTime.byMinute <= 60 && struRecordingPublishFileInfo.struStartTime.bySecond >= 0 && struRecordingPublishFileInfo.struStartTime.bySecond <= 60)
    {
        m_startDate.SetDate(struRecordingPublishFileInfo.struStartTime.wYear, struRecordingPublishFileInfo.struStartTime.byMonth, struRecordingPublishFileInfo.struStartTime.byDay);
        m_startTime.SetTime(struRecordingPublishFileInfo.struStartTime.byHour, struRecordingPublishFileInfo.struStartTime.byMinute, struRecordingPublishFileInfo.struStartTime.bySecond);
    }
    if (struRecordingPublishFileInfo.struEndTime.wYear >= 1900 && struRecordingPublishFileInfo.struEndTime.wYear <= 2100 && struRecordingPublishFileInfo.struEndTime.byMonth >=1 && struRecordingPublishFileInfo.struEndTime.byMonth <= 12 && struRecordingPublishFileInfo.struEndTime.byDay >=1 && struRecordingPublishFileInfo.struEndTime.byDay <= 31 && \
    struRecordingPublishFileInfo.struEndTime.byHour >= 0 && struRecordingPublishFileInfo.struEndTime.byHour <= 24 && struRecordingPublishFileInfo.struEndTime.byMinute >= 0 && struRecordingPublishFileInfo.struEndTime.byMinute <= 60 && struRecordingPublishFileInfo.struEndTime.bySecond >= 0 && struRecordingPublishFileInfo.struEndTime.bySecond <= 60)
    {
        m_stopDate.SetDate(struRecordingPublishFileInfo.struEndTime.wYear, struRecordingPublishFileInfo.struEndTime.byMonth, struRecordingPublishFileInfo.struEndTime.byDay);
        m_stopTime.SetTime(struRecordingPublishFileInfo.struEndTime.byHour, struRecordingPublishFileInfo.struEndTime.byMinute, struRecordingPublishFileInfo.struEndTime.bySecond);
    }
    
    m_csCourseName = struRecordingPublishFileInfo.byCourseName;
    m_csInstructorName = struRecordingPublishFileInfo.byInstructorName;
    m_csCoureDescription = struRecordingPublishFileInfo.byCourseDescription;

    UpdateData(FALSE);
}

void CDlgRecordHostFilePublish::OnButtonSetPublishFileInfo() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_RECORDING_PUBLISH_FILE_INFO struRecordingPublishFileInfo = {0};
    struRecordingPublishFileInfo.dwSize = sizeof(struRecordingPublishFileInfo);
    strncpy((char*)struRecordingPublishFileInfo.byCourseName, m_csCourseName, COURSE_NAME_LEN_128);
    strncpy((char*)struRecordingPublishFileInfo.byInstructorName, m_csInstructorName, INSTRUCTOR_NAME_LEN_64);
    strncpy((char*)struRecordingPublishFileInfo.byCourseDescription, m_csCoureDescription, COURSE_DESCRIPTION_LEN);
    struRecordingPublishFileInfo.struStartTime.wYear = m_startDate.GetYear();
    struRecordingPublishFileInfo.struStartTime.byMonth = m_startDate.GetMonth();
    struRecordingPublishFileInfo.struStartTime.byDay = m_startDate.GetDay();
    struRecordingPublishFileInfo.struStartTime.byHour = m_startTime.GetHour();
    struRecordingPublishFileInfo.struStartTime.byMinute = m_startTime.GetMinute();
    struRecordingPublishFileInfo.struStartTime.bySecond = m_startTime.GetSecond();

    struRecordingPublishFileInfo.struEndTime.wYear = m_stopDate.GetYear();
    struRecordingPublishFileInfo.struEndTime.byMonth = m_stopDate.GetMonth();
    struRecordingPublishFileInfo.struEndTime.byDay = m_stopDate.GetDay();
    struRecordingPublishFileInfo.struEndTime.byHour = m_stopTime.GetHour();
    struRecordingPublishFileInfo.struEndTime.byMinute = m_stopTime.GetMinute();
    struRecordingPublishFileInfo.struEndTime.bySecond = m_stopTime.GetSecond();

    NET_DVR_RECORDING_PUBLISH_FILE_COND struRecordingPublishFileCond = {0};
    struRecordingPublishFileCond.dwSize = sizeof(struRecordingPublishFileCond);
    struRecordingPublishFileCond.dwChannel = m_lChannel;
    strncpy((char*)(struRecordingPublishFileCond.byFileID), m_csFileID.GetBuffer(m_csFileID.GetLength()), MAX_ID_LEN);

    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &struRecordingPublishFileCond;
    struCfg.dwCondSize = sizeof(struRecordingPublishFileCond);
    struCfg.lpInBuffer = &struRecordingPublishFileInfo;
    struCfg.dwInSize = sizeof(struRecordingPublishFileInfo);
    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_RECORDING_PUBLISH_FILE_INFO, &struCfg))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_RECORDING_PUBLISH_FILE_INFO");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_RECORDING_PUBLISH_FILE_INFO");
    }

    UpdateData(FALSE);
}

void CDlgRecordHostFilePublish::OnButtonRecordingPublishFile()
{
    GetDlgItem(IDC_START_DATE)->EnableWindow(TRUE);
    GetDlgItem(IDC_START_TIME)->EnableWindow(TRUE);
    GetDlgItem(IDC_STOP_DATE)->EnableWindow(TRUE);
    GetDlgItem(IDC_STOP_TIME)->EnableWindow(TRUE);
    GetDlgItem(IDC_EDIT_FILEID)->EnableWindow(TRUE);
    GetDlgItem(IDC_COMBO_CMD_TYPE)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_SET_RECORDING_PUBLISH_FILE)->EnableWindow(TRUE);
    GetDlgItem(IDC_EDIT_FILEID_COND)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_GET_PUBLISH_PROGRESS)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_PUBILSH_PERCENT)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_PUBLISH_STATUS)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_COURSE_NAME2)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_INSTRUCTOR_NAME)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_COURSE_DESCRIPTION)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_GET_PUBLISH_FILE_INFO)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_SET_PUBLISH_FILE_INFO)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_CHANNEL_NUMBER)->EnableWindow(FALSE);
};

void CDlgRecordHostFilePublish::OnButtonPublishProgress()
{
    GetDlgItem(IDC_START_DATE)->EnableWindow(FALSE);
    GetDlgItem(IDC_START_TIME)->EnableWindow(FALSE);
    GetDlgItem(IDC_STOP_DATE)->EnableWindow(FALSE);
    GetDlgItem(IDC_STOP_TIME)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_FILEID)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_CMD_TYPE)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_SET_RECORDING_PUBLISH_FILE)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_FILEID_COND)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_GET_PUBLISH_PROGRESS)->EnableWindow(TRUE);
    GetDlgItem(IDC_EDIT_PUBILSH_PERCENT)->EnableWindow(TRUE);
    GetDlgItem(IDC_COMBO_PUBLISH_STATUS)->EnableWindow(TRUE);
    GetDlgItem(IDC_EDIT_COURSE_NAME2)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_INSTRUCTOR_NAME)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_COURSE_DESCRIPTION)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_GET_PUBLISH_FILE_INFO)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_SET_PUBLISH_FILE_INFO)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_CHANNEL_NUMBER)->EnableWindow(FALSE);
};

void CDlgRecordHostFilePublish::OnButtonPublishInfo()
{
    GetDlgItem(IDC_START_DATE)->EnableWindow(TRUE);
    GetDlgItem(IDC_START_TIME)->EnableWindow(TRUE);
    GetDlgItem(IDC_STOP_DATE)->EnableWindow(TRUE);
    GetDlgItem(IDC_STOP_TIME)->EnableWindow(TRUE);
    GetDlgItem(IDC_EDIT_FILEID)->EnableWindow(TRUE);
    GetDlgItem(IDC_COMBO_CMD_TYPE)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_SET_RECORDING_PUBLISH_FILE)->EnableWindow(FALSE);   
    GetDlgItem(IDC_EDIT_FILEID_COND)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_GET_PUBLISH_PROGRESS)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_PUBILSH_PERCENT)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_PUBLISH_STATUS)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_COURSE_NAME2)->EnableWindow(TRUE);
    GetDlgItem(IDC_EDIT_INSTRUCTOR_NAME)->EnableWindow(TRUE);
    GetDlgItem(IDC_EDIT_COURSE_DESCRIPTION)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_GET_PUBLISH_FILE_INFO)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_SET_PUBLISH_FILE_INFO)->EnableWindow(TRUE);
    GetDlgItem(IDC_COMBO_CHANNEL_NUMBER)->EnableWindow(TRUE);
};


