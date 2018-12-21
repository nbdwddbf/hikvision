/**********************************************************
FileName:    DlgLocalConfig.cpp
Description: local configuration     
Date:        2008/05/17
Note: 		 <global>struct, refer to GeneralDef.h, global variants and functions refer to ClientDemo.cpp   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/


#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgLocalConfig.h"
#include ".\dlglocalconfig.h"
#include "DlgLocalRecordSchedule.h"
#include ".\clientdemodlg.h"


// CDlgLocalConfig dialog
/*********************************************************
  Function:	CDlgLocalConfig
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgLocalConfig, CDialog)
CDlgLocalConfig::CDlgLocalConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLocalConfig::IDD, pParent)
	, m_iCycleTime(5)
	, m_iFileInterval(1)
	, m_csDownLoadPath(_T(""))
	, m_csPicSnatchPath(_T(""))
	, m_csLogPath(_T(""))
	, m_ctimeCheckDeviceTime(0)
	, m_bCyclePlay(FALSE)
	, m_bAutoRecord(FALSE)
	, m_bCycleRecord(FALSE)
	, m_bUseCard(FALSE)
	, m_bChkDeviceTime(FALSE)
	, m_iListenPort(7200)
	, m_lListenHandle(-1)
    , m_bWriteSdkLog(FALSE)
	, m_wMaxTcpPort(0)
	, m_wMinTcpPort(0)
	, m_wMaxUdpPort(0)
	, m_wMinUdpPort(0)
	, m_dwMaxMemBlocks(0)
	, m_dwReleaseInterval(0)
	, m_bRtpSort(FALSE)
	, m_dwMaxBuffNum(0)
	, m_iConnectTimeout(3000)
	, m_dwObjectRelease(0)
	, m_dwSDKLogNum(0)
    , m_sPTProxyIP(_T(""))
    , m_dwPTProxyPort(0)
    , m_bChkResumeEnable(FALSE)
    , m_iReusmeTimeout(0)
    , m_bOldJsonCallback(FALSE)
    , m_bJsonAlarmPictureSeparate(FALSE)
  {
    m_strSdklog = "c:\\sdklog\\";
	m_dwPreviewTimeout = 0;
	m_dwAlarmTimeout = 0;
	m_dwVodTimeout = 0;
	m_dwOtherModuleTimeout = 0;
	memset(&m_struLoaclCheckDev,0,sizeof(m_struLoaclCheckDev));
	memset(&struStreamCallBackCfg, 0, sizeof(struStreamCallBackCfg));
}
/*********************************************************
  Function:	~CDlgLocalConfig
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgLocalConfig::~CDlgLocalConfig()
{
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgLocalConfig::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgLocalConfig)
    DDX_Control(pDX, IDC_COMBO_IPTYPE, m_comIPType);
    DDX_Control(pDX, IDC_COMBO_SECURITY_LEVEL, m_cmLevel);
    DDX_Control(pDX, IDC_COMBO_TALK_MODE, m_cmTalkMode);
    DDX_Control(pDX, IDC_COMBO_IPADDRESS, m_AllAddressCtrl);
    DDX_Control(pDX, IDC_COMBO_SDK_LOG, m_comboSDKLog);
    DDX_Control(pDX, IDC_COMBO_B_FRAME, m_comboBFrame);
    DDX_Control(pDX, IDC_COMBO_SOUND_MODE, m_comboSoundMode);
    DDX_Control(pDX, IDC_CHK_CYCLE_PLAY, m_chkCyclePlay);
    DDX_Control(pDX, IDC_CHK_USE_CARD, m_chkUseCard);
    DDX_Text(pDX, IDC_EDIT_CYCLE_TIME, m_iCycleTime);
    DDX_Control(pDX, IDC_CHK_AUTO_RECORD, m_chkAutoRecord);
    DDX_Control(pDX, IDC_CHK_CYCLE_RECORD, m_chkCycleRecord);
    DDX_Control(pDX, IDC_COMBO_FIRST_DISK, m_comboRecFirstDisk);
    DDX_Control(pDX, IDC_COMBO_LAST_DISK, m_comboRecLastDisk);
    DDX_Text(pDX, IDC_EDIT_FILE_INTERVAL, m_iFileInterval);
    DDX_Text(pDX, IDC_EDIT_DOWNLOAD_PATH, m_csDownLoadPath);
    DDX_Text(pDX, IDC_EDIT_PIC_PATH, m_csPicSnatchPath);
    DDX_Text(pDX, IDC_EDIT_LOG_PATH, m_csLogPath);
    DDX_Control(pDX, IDC_CHK_SYSTIME, m_chkSysTime);
    DDX_DateTimeCtrl(pDX, IDC_DATETIME_PICKER, m_ctimeCheckDeviceTime);
    DDX_Check(pDX, IDC_CHK_CYCLE_PLAY, m_bCyclePlay);
    DDX_Check(pDX, IDC_CHK_AUTO_RECORD, m_bAutoRecord);
    DDX_Check(pDX, IDC_CHK_CYCLE_RECORD, m_bCycleRecord);
    DDX_Check(pDX, IDC_CHK_USE_CARD, m_bUseCard);
    DDX_Check(pDX, IDC_CHK_SYSTIME, m_bChkDeviceTime);
    DDX_Control(pDX, IDC_DATETIME_PICKER, m_ctCheckTime);
    DDX_Control(pDX, IDC_COMBO_VIDEO_FORMAT, m_comboVideoFormat);
    DDX_Check(pDX, IDC_CHK_NO_DECODE, m_bChkNoDecode);
    DDX_Check(pDX, IDC_CHK_PREVIEW_BLOCK, m_bBlock);
    DDX_Text(pDX, IDC_EDIT_RECV_TIMEOUT, m_iTimeOut);
    DDV_MinMaxInt(pDX, m_iTimeOut, 1, 120000);
    DDX_Text(pDX, IDC_EDIT_SDKLOG, m_strSdklog);
    DDX_Check(pDX, IDC_CHECK_CYCLEWRITE, m_bWriteSdkLog);
    DDX_Check(pDX, IDC_CHECK_RECONNECT, m_bReconnect);
    DDX_Text(pDX, IDC_EDIT_LISETN_PORT, m_iListenPort);
    DDX_Text(pDX, IDC_EDIT_TCP_MAX_PORT, m_wMaxTcpPort);
    DDX_Text(pDX, IDC_EDIT_TCP_MIN_PORT, m_wMinTcpPort);
    DDX_Text(pDX, IDC_EDIT_UDP_MAX_PORT, m_wMaxUdpPort);
    DDX_Text(pDX, IDC_EDIT_UDP_MIN_PORT, m_wMinUdpPort);
    DDX_Text(pDX, IDC_EDIT_MAX_MEM_BLOCKS, m_dwMaxMemBlocks);
    DDX_Text(pDX, IDC_EDIT_RELEASE_INTERVAL, m_dwReleaseInterval);
    DDX_Text(pDX, IDC_EDIT_PREVIEW_TIMEOUT, m_dwPreviewTimeout);
    DDX_Text(pDX, IDC_EDIT_VOD_TIMEOUT, m_dwVodTimeout);
    DDX_Text(pDX, IDC_EDIT_ALARM_TIMEOUT, m_dwAlarmTimeout);
    DDX_Text(pDX, IDC_EDIT_OTHER_TIMEOUT, m_dwOtherModuleTimeout);
    DDX_Check(pDX, IDC_CHECK_USE_ABILITY_PARSE, m_bUseAbilityParse);
    DDX_Check(pDX, IDC_CHECK_SORT, m_bRtpSort);
    DDX_Text(pDX, IDC_EDIT_BUFF_NUM, m_dwMaxBuffNum);
    DDX_Text(pDX, IDC_EDIT_CONNECT_TIMEOUT, m_iConnectTimeout);
    DDX_Text(pDX, IDC_EDIT_NET_FAIL_NUM, m_dwNetFailNum);
    DDX_Text(pDX, IDC_EDIT_HEART_CHECK_TIME, m_dwHeartCheckTime);
    DDX_Text(pDX, IDC_EDIT_IPV6_ADDRESS, m_csIPV6);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_PT_PROXY_IP, m_sPTProxyIP);
    DDX_Text(pDX, IDC_EDIT_PT_PROXY_PORT, m_dwPTProxyPort);
    DDX_Text(pDX, IDC_EDIT_OBJECT_RELEASE, m_dwObjectRelease);
    DDX_Text(pDX, IDC_EDIT_SDK_LOG_NUM, m_dwSDKLogNum);
    DDX_Control(pDX, IDC_COMBO_PLAYBACK_ENDFLAG, m_comboPlayBackEndFlag);
    DDX_Control(pDX, IDC_COMBO_EXCEPTION_CB_TYPE, m_cmbExceptionCBType);
    DDX_Check(pDX, IDC_CHECK_RESUME_ENABLE, m_bChkResumeEnable);
    DDX_Text(pDX, IDC_EDIT_RESUME_TIMEOUT, m_iReusmeTimeout);
    DDV_MinMaxInt(pDX, m_iReusmeTimeout, 0, 3600000);
    DDX_Check(pDX, IDC_CHECK_OLD_JSON_CALLBACK, m_bOldJsonCallback);
    DDX_Check(pDX, IDC_CHECK_JSON_ALARM_PICTURE_SEPARATE, m_bJsonAlarmPictureSeparate);
}

/*********************************************************
  Function:	BEGIN_MESSAGE_MAP
  Desc:		map between message and function
  Input:	
  Output:	
  Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgLocalConfig, CDialog)
	//{{AFX_MSG_MAP(CDlgLocalConfig)	
	ON_BN_CLICKED(IDC_BTN_SELECT_DOWNLOAD_PATH, OnBnClickedBtnSelectDownLoadPath)
	ON_BN_CLICKED(IDC_LOCAL_OK, OnBnClickedLocalOk)
	ON_BN_CLICKED(IDC_CHK_CYCLE_PLAY, OnBnClickedChkCyclePlay)
	ON_BN_CLICKED(IDC_CHK_AUTO_RECORD, OnBnClickedChkAutoRecord)
	ON_BN_CLICKED(IDC_BTN_SET_TIME, OnBnClickedBtnSetTime)
	ON_BN_CLICKED(IDC_BTN_SELECT_PIC_PATH, OnBnClickedBtnSelectPicPath)
	ON_BN_CLICKED(IDC_BTN_SELECT_LOG_PATH, OnBnClickedBtnSelectLogPath)
	ON_BN_CLICKED(IDC_CHK_SYSTIME, OnBnClickedChkSystime)
	ON_BN_CLICKED(IDC_CHK_USE_CARD, OnBnClickedChkUseCard)
	ON_CBN_SELCHANGE(IDC_COMBO_SOUND_MODE, OnSelchangeComboSoundMode)
	ON_BN_CLICKED(IDC_BUTTON_START_LISTEN, OnButtonStartListen)
	ON_BN_CLICKED(IDC_BUTTON_STOP_LISTEN, OnButtonStopListen)
	ON_BN_CLICKED(IDC_BUTTON_REFRUSH, OnButtonRefrush)
	ON_BN_CLICKED(IDC_BTN_SELECT_SDKLOG_PATH, OnBtnSelectSdklogPath)
	ON_BN_CLICKED(IDC_BTN_BIND_IP, OnBtnBindIp)
	ON_BN_CLICKED(IDC_BUTTON_SET_SDK_CFG, OnButtonSetSdkCfg)
	ON_BN_CLICKED(IDC_BUTTON_GET_SDK_CFG, OnButtonGetSdkCfg)
	ON_BN_CLICKED(IDC_BTN_SET_MODULE_TIMEOUT, OnBtnSetModuleTimeout)
	ON_BN_CLICKED(IDC_BTN_GET_MODULE_TIMEOUT, OnBtnGetModuleTimeout)
	ON_BN_CLICKED(IDC_CHECK_USE_ABILITY_PARSE, OnCheckUseAbilityParse)
	ON_CBN_SELCHANGE(IDC_COMBO_TALK_MODE, OnSelchangeComboTalkMode)
	ON_CBN_SELCHANGE(IDC_COMBO_IPTYPE, OnSelchangeComboIptype)
	//}}AFX_MSG_MAP

	ON_BN_CLICKED(IDC_BTN_RELEASE_SDK_MEMPOOL, &CDlgLocalConfig::OnBnClickedBtnReleaseSdkMempool)
	ON_BN_CLICKED(IDC_BTN_CALLBACK, &CDlgLocalConfig::OnBnClickedBtnCallback)
    ON_BN_CLICKED(IDC_BTN_SET_PROXY, &CDlgLocalConfig::OnBnClickedBtnSetProxy)
    ON_BN_CLICKED(IDC_CHECK_OLD_JSON_CALLBACK, &CDlgLocalConfig::OnBnClickedCheckOldJsonCallback)
    ON_BN_CLICKED(IDC_CHECK_JSON_ALARM_PICTURE_SEPARATE, &CDlgLocalConfig::OnBnClickedCheckJsonAlarmPictureSeparate)
END_MESSAGE_MAP()


// CDlgLocalConfig message handlers
/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgLocalConfig::OnInitDialog()
{
	CDialog::OnInitDialog();
	int i = 0;
	m_comboSoundMode.SetCurSel(g_bShareSound);
	m_bCyclePlay = g_struLocalParam.bCyclePlay;
	if (m_bCyclePlay)
	{
		GetDlgItem(IDC_EDIT_CYCLE_TIME)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_CYCLE_TIME)->EnableWindow(FALSE);
	}

	m_iCycleTime = g_struLocalParam.iCycleTime;
	m_bUseCard = g_struLocalParam.bUseCard;
	m_bChkNoDecode = g_struLocalParam.bNoDecode;
	m_bBlock = g_struLocalParam.bPreviewBlock;
	m_comboVideoFormat.SetCurSel(g_struLocalParam.bNTSC);//
	m_comboBFrame.SetCurSel(g_struLocalParam.dwBFrameNum);

	if (m_bUseCard)
	{
		GetDlgItem(IDC_COMBO_VIDEO_FORMAT)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_COMBO_VIDEO_FORMAT)->EnableWindow(FALSE);
	}

	CString csHardDriver;
	for (i = 0; i < (int)(g_pMainDlg->m_iDriverNum); i++)
	{
		csHardDriver.Format("%c%s", g_pMainDlg->m_cHardDriver[i], ":\\");
		m_comboRecFirstDisk.AddString(csHardDriver);
		m_comboRecLastDisk.AddString(csHardDriver);
	}
	m_comboRecFirstDisk.SetCurSel(g_struLocalParam.iStartRecordDriver);
	m_comboRecLastDisk.SetCurSel(g_struLocalParam.iEndRecordDriver);

	m_iFileInterval = g_struLocalParam.iRecordFileInterval;
	m_bCycleRecord = g_struLocalParam.bCycleRecord;
	m_bAutoRecord = g_struLocalParam.bAutoRecord;

	if (m_bAutoRecord)
	{
		GetDlgItem(IDC_BTN_SET_TIME)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_SET_TIME)->EnableWindow(FALSE);
	}

	m_csDownLoadPath.Format("%s",g_struLocalParam.chDownLoadPath);
	m_csPicSnatchPath.Format("%s",g_struLocalParam.chPictureSavePath);
	m_csLogPath.Format("%s",g_struLocalParam.chRemoteCfgSavePath);
	m_bChkDeviceTime = g_struLocalParam.bAutoCheckDeviceTime;
	CTime ctTime(2008, 7, 17, g_struLocalParam.lCheckDeviceTime/10000, (g_struLocalParam.lCheckDeviceTime%10000)/100, g_struLocalParam.lCheckDeviceTime%100);
	m_ctimeCheckDeviceTime = ctTime;
	m_comboSDKLog.SetCurSel(g_struLocalParam.nLogLevel);
	m_iTimeOut = g_struLocalParam.nTimeout;
	if (m_bChkDeviceTime)
	{
		GetDlgItem(IDC_DATETIME_PICKER)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_DATETIME_PICKER)->EnableWindow(FALSE);
	}

    char sAllIp[16][16] = {0};
    DWORD dwIpNum = 0;
    BOOL bBind = FALSE;
    if (!NET_DVR_GetLocalIP(sAllIp, &dwIpNum, &bBind))
    {
        MessageBox(NET_DVR_GetErrorMsg());
        return FALSE;
    }
    
    for (i = 0; i < dwIpNum; i++)
    {
        m_AllAddressCtrl.AddString(sAllIp[i]);
    }
    m_AllAddressCtrl.SetCurSel(0);

    m_bWriteSdkLog = g_struLocalParam.bCycleWriteLog;
    m_bReconnect = g_struLocalParam.bReconnect;

	m_cmTalkMode.SetCurSel(0);
	NET_DVR_GetSDKLocalCfg(NET_SDK_LOCAL_CFG_TYPE_CHECK_DEV,&m_struLoaclCheckDev);
    m_dwHeartCheckTime = m_struLoaclCheckDev.dwCheckOnlineTimeout/1000;
    m_dwNetFailNum = m_struLoaclCheckDev.dwCheckOnlineNetFailMax;

	NET_DVR_GetSDKLocalCfg(NET_DVR_LOCAL_CFG_TYPE_STREAM_CALLBACK, &struStreamCallBackCfg);
	m_comboPlayBackEndFlag.SetCurSel(struStreamCallBackCfg.byPlayBackEndFlag);

    m_comIPType.SetCurSel(0);
    OnSelchangeComboIptype();

    NET_DVR_SOCKS_PROXYS struProxys = { 0 };
    NET_DVR_GetSDKLocalCfg(NET_SDK_LOCAL_CFG_TYPE_PROXYS, &struProxys);
    m_sPTProxyIP = struProxys.struProxy[0].byIP;
    m_dwPTProxyPort = struProxys.struProxy[0].wPort;

    m_cmbExceptionCBType.SetCurSel(0);
    NET_DVR_LOCAL_GENERAL_CFG struGeneralCfg = { 0 };
    NET_DVR_GetSDKLocalCfg(NET_DVR_LOCAL_CFG_TYPE_GENERAL, &struGeneralCfg);
    m_cmbExceptionCBType.SetCurSel(struGeneralCfg.byExceptionCbDirectly);
    m_bChkResumeEnable = struGeneralCfg.byResumeUpgradeEnable == 1 ? TRUE : FALSE;
    m_iReusmeTimeout = struGeneralCfg.dwResumeUpgradeTimeout;
    m_bJsonAlarmPictureSeparate = struGeneralCfg.byAlarmJsonPictureSeparate;

    NET_DVR_MESSAGE_CALLBACK_PARAM_V51 struMsgCallbackCfg = { 0 };
    if (!NET_DVR_GetSDKLocalCfg(NET_DVR_LOCAL_CFG_MESSAGE_CALLBACK_V51, &struMsgCallbackCfg))
    {
        MessageBox("Get NET_DVR_LOCAL_CFG_MESSAGE_CALLBACK_V51 failed");
    }
    else
    {
        m_bOldJsonCallback = struMsgCallbackCfg.byVcaAlarmJsonType;
        g_pMainDlg->AddLog(0, OPERATION_SUCC_T, "Get NET_DVR_LOCAL_CFG_MESSAGE_CALLBACK_V51 successful");
    }

	UpdateData(FALSE);
	return TRUE;
}

/*********************************************************
  Function:	GetDirectoryPath
  Desc:		get directory pathe
  Input:	
  Output:	
  Return:	
**********************************************************/
CString CDlgLocalConfig::GetDirectoryPath()
{
	LPITEMIDLIST pidlRoot=NULL;
	SHGetSpecialFolderLocation(m_hWnd,CSIDL_DRIVES,&pidlRoot);
	BROWSEINFO bi;   //the input parameters needed
	CString strDisplayName;  
	bi.hwndOwner=GetSafeHwnd();   //get handle value of parent window 
	bi.pidlRoot=pidlRoot;   
	bi.pszDisplayName=strDisplayName.GetBuffer(MAX_PATH+1);   //get buffer pointer
	char szLan[32] = {0};
	g_StringLanType(szLan, "文件夹", "Directory");
	bi.lpszTitle=szLan;   //set title
	bi.ulFlags=BIF_RETURNONLYFSDIRS;   //set flag
	bi.lpfn=NULL;
	bi.lParam=0;
	bi.iImage=0;   //The above parameters are not related to the settings, better set up,
	LPITEMIDLIST lpIDList= SHBrowseForFolder(&bi);	//open dialog
	strDisplayName.ReleaseBuffer();   //correspond to GetBuffer()
	char pPath[MAX_PATH];
	CString Str;
	if (lpIDList)
	{
		SHGetPathFromIDList (lpIDList, pPath);
		Str=pPath;
	}
	return Str;
}

/*********************************************************
  Function:	OnBnClickedLocalOk
  Desc:		finish local configuration
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgLocalConfig::OnBnClickedLocalOk()
{
	int i = 0, j = 0;
	char szLan[32] = {0};
	UpdateData(TRUE);
	if ((m_iFileInterval < 1) || (m_iFileInterval > 60))
	{
		g_StringLanType(szLan, "非法的文件打包时间!", "Illegal file packing time");
		AfxMessageBox(szLan);
		return;
	}
	if ((m_csDownLoadPath == "") || (m_csPicSnatchPath == "") || (m_csLogPath == ""))
	{
		g_StringLanType(szLan, "请选择文件保存路径!", "Please select the file path");
		AfxMessageBox(szLan);
		return;
	}


	i = m_comboRecFirstDisk.GetCurSel();
	j = m_comboRecLastDisk.GetCurSel();
	if (i > j)
	{
		g_StringLanType(szLan, "起始驱动器和终止驱动器不匹配!", "First drive and last drive is mismatch");
		AfxMessageBox(szLan);
		return;
	}

	if (m_iCycleTime < 5)
	{
		m_iCycleTime = 5;
	}
	g_struLocalParam.bCyclePlay = m_bCyclePlay;
	g_struLocalParam.iCycleTime = m_iCycleTime;
	if (g_struLocalParam.bUseCard != m_bUseCard)
	{
		if (!g_struLocalParam.bUseCard)
		{
			g_bCardInit = FALSE;
		}
		else
		{
			g_bCardInit = TRUE;
		}
	}
	g_struLocalParam.bUseCard = m_bUseCard;
	g_struLocalParam.bNTSC = m_comboVideoFormat.GetCurSel();

	g_struLocalParam.bAutoRecord = m_bAutoRecord;
	g_struLocalParam.bCycleRecord = m_bCycleRecord;
	g_struLocalParam.iRecordFileInterval = m_iFileInterval;

	g_struLocalParam.iStartRecordDriver = i;
	g_struLocalParam.iEndRecordDriver = j;
	g_struLocalParam.bNoDecode = m_bChkNoDecode;
	g_struLocalParam.bPreviewBlock = m_bBlock;
	g_struLocalParam.dwBFrameNum = m_comboBFrame.GetCurSel();

	sprintf(g_struLocalParam.chDownLoadPath, "%s", m_csDownLoadPath.GetBuffer(0));
	sprintf(g_struLocalParam.chPictureSavePath, "%s", m_csPicSnatchPath.GetBuffer(0));
	sprintf(g_struLocalParam.chRemoteCfgSavePath, "%s", m_csLogPath.GetBuffer(0));
	g_struLocalParam.bAutoCheckDeviceTime = m_bChkDeviceTime;
	g_struLocalParam.lCheckDeviceTime = m_ctimeCheckDeviceTime.GetHour()*10000 + m_ctimeCheckDeviceTime.GetMinute()*100 + m_ctimeCheckDeviceTime.GetSecond();
	g_struLocalParam.nLogLevel = m_comboSDKLog.GetCurSel();
    g_struLocalParam.bCycleWriteLog = m_bWriteSdkLog;

    g_struLocalParam.bReconnect = m_bReconnect;
    NET_DVR_SetReconnect(5000, g_struLocalParam.bReconnect);
    char sLogPath[256] = {0};
    strncpy(sLogPath, m_strSdklog, 256);
	if(!NET_DVR_SetLogToFile(g_struLocalParam.nLogLevel, sLogPath))
	{
		MessageBox(NET_DVR_GetErrorMsg());
	}
	g_struLocalParam.nTimeout = m_iTimeOut;
	NET_DVR_SetRecvTimeOut(m_iTimeOut);
    NET_DVR_SetConnectTime(2000, 1);

	//NET_DVR_SetLogPrint(TRUE);
	//NET_DVR_SetLogPrintAction(g_struLocalParam.nLogLevel, 1, 0, 0, 0);
	//initial operation after conform

    m_struLoaclCheckDev.dwCheckOnlineTimeout = m_dwHeartCheckTime*1000;
    m_struLoaclCheckDev.dwCheckOnlineNetFailMax = m_dwNetFailNum;
    
    NET_DVR_SetSDKLocalCfg(NET_SDK_LOCAL_CFG_TYPE_CHECK_DEV,&m_struLoaclCheckDev);

	NET_DVR_LOCAL_LOG_CFG struLocalLogCfg = { 0 };
	struLocalLogCfg.wSDKLogNum = m_dwSDKLogNum;
	NET_DVR_SetSDKLocalCfg(NET_DVR_LOCAL_CFG_TYPE_LOG, &struLocalLogCfg);

    NET_DVR_LOCAL_SECURITY struLocalSecurity = {0};
    struLocalSecurity.bySecurityLevel = m_cmLevel.GetCurSel();
    if(!NET_DVR_SetSDKLocalCfg(NET_SDK_LOCAL_CFG_TYPE_SECURITY, &struLocalSecurity))
    {
        g_pMainDlg->AddLog(0, OPERATION_FAIL_T, "SET NET_SDK_LOCAL_CFG_TYPE_SECURITY failed");
    }
    else
    {
        g_pMainDlg->AddLog(0, OPERATION_SUCC_T, "SET NET_SDK_LOCAL_CFG_TYPE_SECURITY successful");
    }

    NET_DVR_LOCAL_GENERAL_CFG struGeneralCfg = { 0 };
    struGeneralCfg.byExceptionCbDirectly = m_cmbExceptionCBType.GetCurSel();
    struGeneralCfg.byResumeUpgradeEnable = m_bChkResumeEnable ? 1 : 0;
    struGeneralCfg.dwResumeUpgradeTimeout = m_iReusmeTimeout;
    if (!NET_DVR_SetSDKLocalCfg(NET_DVR_LOCAL_CFG_TYPE_GENERAL, &struGeneralCfg))
    {
        g_pMainDlg->AddLog(0, OPERATION_FAIL_T, "SET NET_DVR_LOCAL_CFG_TYPE_GENERAL failed");
    }
    else
    {
        g_pMainDlg->AddLog(0, OPERATION_SUCC_T, "SET NET_DVR_LOCAL_CFG_TYPE_GENERAL successful");
    }

	WriteLocalConfig();
}

/*********************************************************
  Function:	OnBnClickedChkCyclePlay
  Desc:		whether cycle play response function
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgLocalConfig::OnBnClickedChkCyclePlay()
{
	if (m_chkCyclePlay.GetCheck() == 1)
	{
		GetDlgItem(IDC_EDIT_CYCLE_TIME)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_CYCLE_TIME)->EnableWindow(FALSE);
	}
}

/*********************************************************
  Function:	OnBnClickedChkAutoRecord
  Desc:		whether auto record response function
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgLocalConfig::OnBnClickedChkAutoRecord()
{
	if (m_chkAutoRecord.GetCheck() == 1)
	{
		GetDlgItem(IDC_BTN_SET_TIME)->EnableWindow(TRUE);
		g_pMainDlg->IsDiskFull();
	}
	else
	{
		GetDlgItem(IDC_BTN_SET_TIME)->EnableWindow(FALSE);
	}
}

/*********************************************************
  Function:	OnBnClickedBtnSetTime
  Desc:		set auto record time
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgLocalConfig::OnBnClickedBtnSetTime()
{
	CDlgLocalRecordSchedule	dlgLocalRecordSchedule;
	dlgLocalRecordSchedule.DoModal();
}

/*********************************************************
  Function:	OnBnClickedBtnSelectDownLoadPath
  Desc:		choose download path response function
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgLocalConfig::OnBnClickedBtnSelectDownLoadPath()
{
	CString csPath = GetDirectoryPath();
	if (csPath != "")
	{
		m_csDownLoadPath = csPath;
		UpdateData(FALSE);
	}
}

/*********************************************************
  Function:	OnBnClickedBtnSelectPicPath
  Desc:		choose pic save path response function
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgLocalConfig::OnBnClickedBtnSelectPicPath()
{
	CString csPath = GetDirectoryPath();
	if (csPath != "")
	{
		m_csPicSnatchPath = csPath;
		UpdateData(FALSE);
	}
}

/*********************************************************
  Function:	OnBnClickedBtnSelectLogPath
  Desc:		choose log file save path
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgLocalConfig::OnBnClickedBtnSelectLogPath()
{
	CString csPath = GetDirectoryPath();
	if (csPath != "")
	{
		m_csLogPath = csPath;
		UpdateData(FALSE);
	}
}

/*********************************************************
  Function:	OnBnClickedChkSystime
  Desc:		whether check system time
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgLocalConfig::OnBnClickedChkSystime()
{
	UpdateData(TRUE);
	if (m_bChkDeviceTime)
	{
		GetDlgItem(IDC_DATETIME_PICKER)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_DATETIME_PICKER)->EnableWindow(FALSE);
	}
}

/*********************************************************
  Function:	OnBnClickedChkUseCard
  Desc:		use card to decode the stream and enable the control or not
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgLocalConfig::OnBnClickedChkUseCard()
{
	UpdateData(TRUE);
	GetDlgItem(IDC_COMBO_VIDEO_FORMAT)->EnableWindow(m_bUseCard);
}

void CDlgLocalConfig::OnSelchangeComboSoundMode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	g_bShareSound = m_comboSoundMode.GetCurSel();
	if (!g_bShareSound)
	{
		NET_DVR_SetAudioMode(MONOPOLIZE_MODE);
		g_bShareSound = FALSE;
		g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "MONOPOLIZE_MODE");
	}
	else
	{
		NET_DVR_SetAudioMode(SHARE_MODE);
		g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "SHARE_MODE");
		g_bShareSound = TRUE;
	}	
}

// void CDlgLocalConfig::OnChkDefaultIp() 
// {
// 	UpdateData(TRUE);
// 	GetDlgItem(IDC_EDIT_LISTEN_IP)->ShowWindow(!m_bDefaultListenIP);
// }

void CDlgLocalConfig::OnButtonStartListen() 
{
	UpdateData(TRUE);

    char sIP[64] = {0};
    if (0 == m_comIPType.GetCurSel())
    {
        int sel = m_AllAddressCtrl.GetLBText(m_AllAddressCtrl.GetCurSel(), sIP);
    } 
    else
    {
        memcpy(sIP, m_csIPV6, m_csIPV6.GetLength());
    }
   // int sel = m_AllAddressCtrl.GetLBText(m_AllAddressCtrl.GetCurSel(), sIP);

    if(m_lListenHandle == -1)
    {
        m_lListenHandle = NET_DVR_StartListen_V30(sIP, m_iListenPort, MessageCallback, NULL);
        if(m_lListenHandle < 0)
		{
			m_lListenHandle = -1;
	    	g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_StartListen_V30");
		}
		else
		{
	    	g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_StartListen_V30");
		}
	}
}

void CDlgLocalConfig::OnButtonStopListen() 
{
	if(m_lListenHandle == -1)
	{
		return;
	}

	if(!NET_DVR_StopListen_V30(m_lListenHandle))
	{
	    g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_StopListen_V30");
	}
	else
	{
	    g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_StopListen_V30");
		m_lListenHandle = -1;	
	}
}

void CDlgLocalConfig::OnButtonRefrush() 
{
	// TODO: Add your control notification handler code here
    m_AllAddressCtrl.ResetContent();
    char sAllIp[16][16] = {0};
    DWORD dwIpNum = 0;
    BOOL bBind = FALSE;
    if (!NET_DVR_GetLocalIP(sAllIp, &dwIpNum, &bBind))
    {
        MessageBox(NET_DVR_GetErrorMsg());
        return;
    }
    
    for (int i = 0; i < dwIpNum; i++)
    {
        m_AllAddressCtrl.AddString(sAllIp[i]);
    }
    m_AllAddressCtrl.SetCurSel(0);
    UpdateData(FALSE);
}

void CDlgLocalConfig::OnBtnSelectSdklogPath() 
{
	// TODO: Add your control notification handler code here
    CString csPath = GetDirectoryPath();
    if (csPath != "")
    {
        m_strSdklog = csPath;
        UpdateData(FALSE);
	}
}

void CDlgLocalConfig::OnBtnBindIp() 
{
	// TODO: Add your control notification handler code here
	if (NET_DVR_SetValidIP(m_AllAddressCtrl.GetCurSel(), true))
	{
		g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_SetValidIP");
	}
	else
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_SetValidIP");
	}	
}

void CDlgLocalConfig::OnButtonSetSdkCfg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_LOCAL_MEM_POOL_CFG struLocalMemPool = {0};
	struLocalMemPool.dwAlarmReleaseInterval = m_dwReleaseInterval;
	struLocalMemPool.dwAlarmMaxBlockNum = m_dwMaxMemBlocks;
	struLocalMemPool.dwObjectReleaseInterval = m_dwObjectRelease;
	if(!NET_DVR_SetSDKLocalCfg(NET_SDK_LOCAL_CFG_TYPE_MEM_POOL, &struLocalMemPool))
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_SetSDKLocalCfg NET_SDK_LOCAL_CFG_TYPE_MEM_POOL");
	}
	else
	{
		g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_SetSDKLocalCfg NET_SDK_LOCAL_CFG_TYPE_MEM_POOL");
	}

	NET_DVR_LOCAL_TCP_PORT_BIND_CFG struTcpPort = {0};
	struTcpPort.wLocalBindTcpMinPort = m_wMinTcpPort;
	struTcpPort.wLocalBindTcpMaxPort = m_wMaxTcpPort;
	if(!NET_DVR_SetSDKLocalCfg(NET_SDK_LOCAL_CFG_TYPE_TCP_PORT_BIND, &struTcpPort))
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_SetSDKLocalCfg NET_SDK_LOCAL_CFG_TYPE_TCP_PORT_BIND");
	}
	else
	{
		g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_SetSDKLocalCfg NET_SDK_LOCAL_CFG_TYPE_TCP_PORT_BIND");
	}
	
	NET_DVR_LOCAL_UDP_PORT_BIND_CFG struUdpPort = {0};
	struUdpPort.wLocalBindUdpMinPort = m_wMinUdpPort;
	struUdpPort.wLocalBindUdpMaxPort = m_wMaxUdpPort;
	if(!NET_DVR_SetSDKLocalCfg(NET_SDK_LOCAL_CFG_TYPE_UDP_PORT_BIND, &struUdpPort))
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_SetSDKLocalCfg NET_SDK_LOCAL_CFG_TYPE_UDP_PORT_BIND");
	}
	else
	{
		g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_SetSDKLocalCfg NET_SDK_LOCAL_CFG_TYPE_UDP_PORT_BIND");
	}


	NET_DVR_RTSP_PARAMS_CFG struRtspParams = {0};
	struRtspParams.byUseSort = m_bRtpSort;
	struRtspParams.dwMaxBuffRoomNum = m_dwMaxBuffNum;
	if(!NET_DVR_SetSDKLocalCfg(NET_SDK_LOCAL_CFG_TYPE_RTSP_PARAMS, &struRtspParams))
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_SetSDKLocalCfg NET_SDK_LOCAL_CFG_TYPE_RTSP_PARAMS");
	}
	else
	{
		g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_SetSDKLocalCfg NET_SDK_LOCAL_CFG_TYPE_RTSP_PARAMS");
	}


}

void CDlgLocalConfig::OnButtonGetSdkCfg() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_LOCAL_MEM_POOL_CFG struLocalMemPool = {0};
	NET_DVR_LOCAL_TCP_PORT_BIND_CFG struTcpPort = {0};
	NET_DVR_LOCAL_UDP_PORT_BIND_CFG struUdpPort = {0};
	NET_DVR_RTSP_PARAMS_CFG struRtspParams = {0};

	if(!NET_DVR_GetSDKLocalCfg(NET_SDK_LOCAL_CFG_TYPE_MEM_POOL, &struLocalMemPool))
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_GetSDKLocalCfg NET_SDK_LOCAL_CFG_TYPE_MEM_POOL");
	}
	else
	{
		g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_GetSDKLocalCfg NET_SDK_LOCAL_CFG_TYPE_MEM_POOL");
		m_dwReleaseInterval = struLocalMemPool.dwAlarmReleaseInterval;
		m_dwMaxMemBlocks = struLocalMemPool.dwAlarmMaxBlockNum;
		m_dwObjectRelease = struLocalMemPool.dwObjectReleaseInterval;
	}
	
	if(!NET_DVR_GetSDKLocalCfg(NET_SDK_LOCAL_CFG_TYPE_TCP_PORT_BIND, &struTcpPort))
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_GetSDKLocalCfg NET_SDK_LOCAL_CFG_TYPE_TCP_PORT_BIND");
	}
	else
	{
		g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_GetSDKLocalCfg NET_SDK_LOCAL_CFG_TYPE_TCP_PORT_BIND");
		m_wMinTcpPort = struTcpPort.wLocalBindTcpMinPort;
		m_wMaxTcpPort = struTcpPort.wLocalBindTcpMaxPort;
	}
	
	if(!NET_DVR_GetSDKLocalCfg(NET_SDK_LOCAL_CFG_TYPE_UDP_PORT_BIND, &struUdpPort))
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_GetSDKLocalCfg NET_SDK_LOCAL_CFG_TYPE_UDP_PORT_BIND");
	}
	else
	{
		g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_GetSDKLocalCfg NET_SDK_LOCAL_CFG_TYPE_UDP_PORT_BIND");
		m_wMinUdpPort = struUdpPort.wLocalBindUdpMinPort;
		m_wMaxUdpPort = struUdpPort.wLocalBindUdpMaxPort;
	}

	if(!NET_DVR_GetSDKLocalCfg(NET_SDK_LOCAL_CFG_TYPE_RTSP_PARAMS, &struRtspParams))
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_GetSDKLocalCfg NET_SDK_LOCAL_CFG_TYPE_RTSP_PARAMS");
	}
	else
	{
		g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_GetSDKLocalCfg NET_SDK_LOCAL_CFG_TYPE_RTSP_PARAMS");
		m_bRtpSort = struRtspParams.byUseSort;
		m_dwMaxBuffNum = struRtspParams.dwMaxBuffRoomNum;
	}

	UpdateData(FALSE);
}

void CDlgLocalConfig::OnBtnSetModuleTimeout() 
{
	UpdateData(TRUE);
	NET_DVR_LOCAL_MODULE_RECV_TIMEOUT_CFG struLocalTimeout = {0};
	struLocalTimeout.dwPreviewTime = m_dwPreviewTimeout;
	struLocalTimeout.dwVodTime = m_dwVodTimeout;
	struLocalTimeout.dwAlarmTime = m_dwAlarmTimeout;
	struLocalTimeout.dwElse = m_dwOtherModuleTimeout;
	if(!NET_DVR_SetSDKLocalCfg(NET_SDK_LOCAL_CFG_TYPE_MODULE_RECV_TIMEOUT, &struLocalTimeout))
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_SetSDKLocalCfg NET_SDK_LOCAL_CFG_TYPE_MODULE_RECV_TIMEOUT");
		AfxMessageBox("set fail!");
	}
	else
	{
		g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_SetSDKLocalCfg NET_SDK_LOCAL_CFG_TYPE_MODULE_RECV_TIMEOUT");
		AfxMessageBox("set success!");
	}
	
}

void CDlgLocalConfig::OnBtnGetModuleTimeout() 
{
	NET_DVR_LOCAL_MODULE_RECV_TIMEOUT_CFG struLocalTimeout = {0};
	
	if(!NET_DVR_GetSDKLocalCfg(NET_SDK_LOCAL_CFG_TYPE_MODULE_RECV_TIMEOUT, &struLocalTimeout))
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_SetSDKLocalCfg NET_SDK_LOCAL_CFG_TYPE_MODULE_RECV_TIMEOUT");
	}
	else
	{
		g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_SetSDKLocalCfg NET_SDK_LOCAL_CFG_TYPE_MODULE_RECV_TIMEOUT");
		m_dwPreviewTimeout = struLocalTimeout.dwPreviewTime;
		m_dwVodTimeout = struLocalTimeout.dwVodTime;
		m_dwAlarmTimeout = struLocalTimeout.dwAlarmTime;
		m_dwOtherModuleTimeout = struLocalTimeout.dwElse;
	}
	
	UpdateData(FALSE);
}

void CDlgLocalConfig::OnCheckUseAbilityParse() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_LOCAL_ABILITY_PARSE_CFG struAbilityParse = {0};
	struAbilityParse.byEnableAbilityParse = (BYTE)m_bUseAbilityParse;
	if (!NET_DVR_SetSDKLocalCfg(NET_SDK_LOCAL_CFG_TYPE_ABILITY_PARSE, &struAbilityParse))
	{
		MessageBox("Set ability parse failed");
	}
	else
	{
		g_pMainDlg->AddLog(0, OPERATION_SUCC_T, "Set ability parse successful");
	}

// 	NET_DVR_LOCAL_ABILITY_PARSE_CFG struAbilityParse1 = {0};
// 	if (!NET_DVR_GetSDKLocalCfg(NET_SDK_LOCAL_CFG_TYPE_ABILITY_PARSE, &struAbilityParse1))
// 	{
// 		g_pMainDlg->AddLog(0, OPERATION_FAIL_T, "Get NET_SDK_LOCAL_CFG_TYPE_ABILITY_PARSE failed");
// 		return;
// 	}
// 
// 	if (struAbilityParse1.byEnableAbilityParse != struAbilityParse.byEnableAbilityParse)
// 	{
// 		g_pMainDlg->AddLog(0, OPERATION_FAIL_T, "Set NET_SDK_LOCAL_CFG_TYPE_ABILITY_PARSE failed");
// 		return;
// 	}

}

void CDlgLocalConfig::OnSelchangeComboTalkMode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	//设置对讲模式
	NET_DVR_LOCAL_TALK_MODE_CFG struTalkModeCfg = {0};
	struTalkModeCfg.byTalkMode = m_cmTalkMode.GetCurSel();
	if (!NET_DVR_SetSDKLocalCfg(NET_SDK_LOCAL_CFG_TYPE_TALK_MODE, &struTalkModeCfg))
	{
		MessageBox("Set talk mode failed");
	}
	else
	{
		g_pMainDlg->AddLog(0, OPERATION_SUCC_T, "Set talk mode successful");
	}

// 	NET_DVR_LOCAL_TALK_MODE_CFG struTalkModeCfg1 = {0};
// 	if (!NET_DVR_GetSDKLocalCfg(NET_SDK_LOCAL_CFG_TYPE_TALK_MODE, &struTalkModeCfg1))
// 	{
// 		g_pMainDlg->AddLog(0, OPERATION_FAIL_T, "Get NET_SDK_LOCAL_CFG_TYPE_TALK_MODE failed");
// 		return;
// 	}
// 	if (struTalkModeCfg1.byTalkMode != struTalkModeCfg.byTalkMode)
// 	{
// 		g_pMainDlg->AddLog(0, OPERATION_FAIL_T, "Set NET_SDK_LOCAL_CFG_TYPE_TALK_MODE failed");
// 	}
}

void CDlgLocalConfig::OnSelchangeComboIptype() 
{
	// TODO: Add your control notification handler code here
    if (0 == m_comIPType.GetCurSel())
    {
        GetDlgItem(IDC_COMBO_IPADDRESS)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_IPV6_ADDRESS)->ShowWindow(SW_HIDE);
    } 
    else
    {
        GetDlgItem(IDC_COMBO_IPADDRESS)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_IPV6_ADDRESS)->ShowWindow(SW_SHOW);
    }
    	
}

void CDlgLocalConfig::OnBnClickedBtnReleaseSdkMempool()
{
	// TODO:  在此添加控件通知处理程序代码
	NET_DVR_SDKMEMPOOL_CFG struSDKMemPoolCfg = { 0 };

	if (!NET_DVR_ReleaseSDKMemPool(&struSDKMemPoolCfg))
	{
		g_pMainDlg->AddLog(0, OPERATION_FAIL_T, "Set Release Sdk MemPool fail");
	}
	else
	{
		g_pMainDlg->AddLog(0, OPERATION_SUCC_T, "Set Release Sdk MemPool successful");
	}
}


void CDlgLocalConfig::OnBnClickedBtnCallback()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	struStreamCallBackCfg.byPlayBackEndFlag = m_comboPlayBackEndFlag.GetCurSel();

	if (!NET_DVR_SetSDKLocalCfg(NET_DVR_LOCAL_CFG_TYPE_STREAM_CALLBACK, &struStreamCallBackCfg))
	{
		MessageBox("Set StreamCallBackCfg failed");
	}
	else
	{
		g_pMainDlg->AddLog(0, OPERATION_SUCC_T, "Set StreamCallBackCfg successful");
	}
}

void CDlgLocalConfig::OnBnClickedBtnSetProxy()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

    NET_DVR_SOCKS_PROXYS struProxys = { 0 };
    strcpy((char*)struProxys.struProxy[0].byIP, m_sPTProxyIP);
    struProxys.struProxy[0].wPort = m_dwPTProxyPort;
    NET_DVR_SetSDKLocalCfg(NET_SDK_LOCAL_CFG_TYPE_PROXYS, &struProxys);
}


void CDlgLocalConfig::OnBnClickedCheckOldJsonCallback()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    NET_DVR_MESSAGE_CALLBACK_PARAM_V51 struMsgCallbackCfg = { 0 };
    struMsgCallbackCfg.byVcaAlarmJsonType = (BYTE)m_bOldJsonCallback;
    if (!NET_DVR_SetSDKLocalCfg(NET_DVR_LOCAL_CFG_MESSAGE_CALLBACK_V51, &struMsgCallbackCfg))
    {
        MessageBox("Set NET_DVR_LOCAL_CFG_MESSAGE_CALLBACK_V51 failed");
    }
    else
    {
        g_pMainDlg->AddLog(0, OPERATION_SUCC_T, "Set NET_DVR_LOCAL_CFG_MESSAGE_CALLBACK_V51 successful");
    }
}




void CDlgLocalConfig::OnBnClickedCheckJsonAlarmPictureSeparate()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    NET_DVR_LOCAL_GENERAL_CFG struGeneralCfg = { 0 };
    struGeneralCfg.byExceptionCbDirectly = m_cmbExceptionCBType.GetCurSel();
    struGeneralCfg.byResumeUpgradeEnable = m_bChkResumeEnable ? 1 : 0;
    struGeneralCfg.dwResumeUpgradeTimeout = m_iReusmeTimeout;
    struGeneralCfg.byAlarmJsonPictureSeparate = (BYTE)m_bJsonAlarmPictureSeparate;
    if (!NET_DVR_SetSDKLocalCfg(NET_DVR_LOCAL_CFG_TYPE_GENERAL, &struGeneralCfg))
    {
        MessageBox("Set NET_DVR_LOCAL_CFG_TYPE_GENERAL failed");
    }
    else
    {
        g_pMainDlg->AddLog(0, OPERATION_SUCC_T, "Set NET_DVR_LOCAL_CFG_TYPE_GENERAL successful");
    }
}
