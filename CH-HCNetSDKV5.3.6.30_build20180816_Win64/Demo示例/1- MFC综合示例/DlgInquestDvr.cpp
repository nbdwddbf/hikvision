// DlgInquestDvr.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInquestDvr.h"
#include "DlgInquestFile.h"
#include "DlgInquestEvent.h"
#include "DlgInquestTrayConfig.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInquestDvr dialog


CDlgInquestDvr::CDlgInquestDvr(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInquestDvr::IDD, pParent)
    , m_bAutoOpenTray(FALSE)
{
	//{{AFX_DATA_INIT(CDlgInquestDvr)
	m_bCancelWrite = FALSE;
	m_bEncrypt = FALSE;
	m_bPause = FALSE;
	m_bCheckCD1 = FALSE;
	m_bCheckCD2 = FALSE;
	m_bCheckCD3 = FALSE;
	m_bCheckCD4 = FALSE;
	m_bCDStateEnable = FALSE;
	m_bKeySet = FALSE;
	m_cdDateStart = 0;
	m_ctDateStop = 0;
	m_ctTimeStart = 0;
	m_cTimeStop = 0;
	m_csCDName = _T("");
	m_csEncKey = _T("");
	m_iBackChan = 0;
	m_iShowChan = 0;
	m_iPIPX = 0;
	m_iPIPY = 0;
	m_bHDException = FALSE;
	m_bCdrwStart = FALSE;
	m_iChanPIP = 0;
	m_iCdrwNum = 0;
	m_csMessage = _T("");
	m_wSensorAddr = 0;
	m_bChkYouli = FALSE;
	m_bChkMile = FALSE;
	m_bChkLeicai = FALSE;
	m_dwFreeSpace = 0;
	m_dwVolumn = 0;
	m_csDeviceVersion = _T("");
	m_byAudioThreshold = 0;
	m_strDiskName = _T("");
	m_wPipHeight = 0;
	m_wWidth = 0;
	m_bAudoDelRecord = FALSE;
	m_dwTimeLeft = 0;
	m_byCDType = 0;
	m_ctInquestDateStart = 0;
	m_ctInquestTimeStart = 0;
	m_iPipCount = 0;
	//}}AFX_DATA_INIT

	m_lLoginID = -1;
	m_lStartChannel = 0;
	m_bKeyState = 0;
	m_bBackuping = FALSE;
	m_lBackupHandle = -1;
	m_hBackupThread = NULL;
	m_hRemoteConfig = -1;
	m_hThread = NULL;
	m_bStatusGeting = FALSE;
	memset(&m_bEnc[0], 0, MAX_CHANNUM_V30*sizeof(DWORD));
	memset(&m_strCdrwCfg, 0, sizeof(NET_DVR_INQUEST_CDRW_CFG));
	memset(&m_strPIPStatus, 0, sizeof(NET_DVR_INQUEST_PIP_STATUS));
	memset(&m_strCdrwStatus, 0, sizeof(NET_DVR_INQUEST_CDRW_STATUS));
	memset(&m_struBackupTimeParam, 0, sizeof(NET_DVR_BACKUP_TIME_PARAM));
	memset(&m_strInquestRoom, 0, sizeof(NET_DVR_INQUEST_ROOM));
	memset(&m_strSystemInfo, 0, sizeof(NET_DVR_INQUEST_SYSTEM_INFO));
	memset(&m_strDeviceVersion, 0, sizeof(m_strDeviceVersion));
}	

void CDlgInquestDvr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInquestDvr)
	DDX_Control(pDX, IDC_CMB_INIT_CD, m_cmbInitCD);
	DDX_Control(pDX, IDC_CMB_HASH_CHK, m_cmbHashCheckCD);
	DDX_Control(pDX, IDC_COMBO_SHOW_MODE, m_comboShowMode);
	DDX_Control(pDX, IDC_COMBO_INQUEST_CHANNEL_RESOLUTION, m_cmbInquestChannelResolution);
	DDX_Control(pDX, IDC_COMBO_CALC_MODE, m_cmbCalcMode);
	DDX_Control(pDX, IDC_COMBO_INQUEST_TIME, m_cmbInquestTime);
	DDX_Control(pDX, IDC_COMBO_INQUEST_ROOM_SYS, m_cmbInquestRoomSys);
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_comboResolution);
	DDX_Control(pDX, IDC_COMBO_INQUEST_ROOM, m_comboInquestRoom);
	DDX_Control(pDX, IDC_COMBO_RECORD_MODE, m_comboReocrdMode);
	DDX_Control(pDX, IDC_COMBO_SENSOR, m_comboSensorNum);
	DDX_Control(pDX, IDC_COMBO_SENSOR_TYPE, m_comboSensorType);
	DDX_Control(pDX, IDC_COMBO_WORK_MODE, m_comboWorkMode);
	DDX_Control(pDX, IDC_COMBO_PIP_MODE, m_comboPIPMode);
	DDX_Control(pDX, IDC_COMBO_CHAN_TIME, m_comboChanTime);
	DDX_Control(pDX, IDC_COMBO_PIP_NUM, m_comboPIPNum);
	DDX_Control(pDX, IDC_COMBO_CHAN_SECRET, m_comboChanSecret);
	DDX_Control(pDX, IDC_COMBO_CHAN_CDRW, m_comboChanCdrw);
	DDX_Control(pDX, IDC_COMBO_CDRW_TYPE, m_comboCdrwType);
	DDX_Control(pDX, IDC_COMBO_CDRW_STATE, m_comboCdrwState);
	DDX_Control(pDX, IDC_COMBO_CDRW_NUMBER, m_comboCdrwNumber);
	DDX_Control(pDX, IDC_COMBO_CDRW_MODE, m_comboCdrwMode);
	DDX_Control(pDX, IDC_COMBO_CDRW_INTERVAL, m_comboCdrwInterval);
	DDX_Check(pDX, IDC_CHECK_BCANCELWRITE, m_bCancelWrite);
	DDX_Check(pDX, IDC_CHECK_BENC, m_bEncrypt);
	DDX_Check(pDX, IDC_CHECK_BPAUSE, m_bPause);
	DDX_Check(pDX, IDC_CHECK_CD1, m_bCheckCD1);
	DDX_Check(pDX, IDC_CHECK_CD2, m_bCheckCD2);
	DDX_Check(pDX, IDC_CHECK_CD3, m_bCheckCD3);
	DDX_Check(pDX, IDC_CHECK_CD4, m_bCheckCD4);
	DDX_Check(pDX, IDC_CHECK_CDSTATE_ENABLE, m_bCDStateEnable);
	DDX_Check(pDX, IDC_CHECK_KEY_BSET, m_bKeySet);
	DDX_DateTimeCtrl(pDX, IDC_COMBO_DATE_START, m_cdDateStart);
	DDX_DateTimeCtrl(pDX, IDC_COMBO_DATE_STOP, m_ctDateStop);
	DDX_DateTimeCtrl(pDX, IDC_COMBO_TIME_START, m_ctTimeStart);
	DDX_DateTimeCtrl(pDX, IDC_COMBO_TIME_STOP, m_cTimeStop);
	DDX_Text(pDX, IDC_EDIT_CD_NAME, m_csCDName);
	DDX_Text(pDX, IDC_EDIT_ENC_KEY, m_csEncKey);
	DDX_Text(pDX, IDC_EDIT_PIP_BACK_CHAN, m_iBackChan);
	DDX_Text(pDX, IDC_EDIT_PIP_SHOW_CHAN, m_iShowChan);
	DDX_Text(pDX, IDC_EDIT_PIP_X, m_iPIPX);
	DDX_Text(pDX, IDC_EDIT_PIP_Y, m_iPIPY);
	DDX_Check(pDX, IDC_CHECK_BHD_ECXEP, m_bHDException);
	DDX_Check(pDX, IDC_CHECK_BCDRW_START, m_bCdrwStart);
	DDX_Text(pDX, IDC_EDIT_CHAN_PIP, m_iChanPIP);
	DDX_Text(pDX, IDC_EDIT_CDRW_NUM, m_iCdrwNum);
	DDX_Text(pDX, IDC_EDIT_INQUEST_MESS, m_csMessage);
	DDX_Text(pDX, IDC_EDIT_SENSOR_ADDR, m_wSensorAddr);
	DDX_Check(pDX, IDC_CHK_YOULI, m_bChkYouli);
	DDX_Check(pDX, IDC_CHK_MILE, m_bChkMile);
	DDX_Check(pDX, IDC_CHK_LEICAI, m_bChkLeicai);
	DDX_Text(pDX, IDC_EDIT_FREE_SPACE, m_dwFreeSpace);
	DDX_Text(pDX, IDC_EDIT_VOLUMN, m_dwVolumn);
	DDX_Text(pDX, IDC_STATIC_DEVICE_VERSION, m_csDeviceVersion);
	DDX_Text(pDX, IDC_EDIT_AUDIO_THRESHOLD, m_byAudioThreshold);
	DDX_Text(pDX, IDC_EDIT_CD_NAME_SYS, m_strDiskName);
	DDX_Text(pDX, IDC_EDIT_PIP_HEIGHT, m_wPipHeight);
	DDX_Text(pDX, IDC_EDIT_PIP_WIDTH, m_wWidth);
	DDX_Check(pDX, IDC_CHECK_AUTO_DEL_RECORD, m_bAudoDelRecord);
	DDX_Text(pDX, IDC_EDIT_CDRW_TIME_LEFT, m_dwTimeLeft);
	DDX_Text(pDX, IDC_EDIT_CD_TYPE, m_byCDType);
	DDX_DateTimeCtrl(pDX, IDC_COMBO_INQUEST_DATE_START, m_ctInquestDateStart);
	DDX_DateTimeCtrl(pDX, IDC_COMBO_INQUEST_TIME_START, m_ctInquestTimeStart);
	DDX_Text(pDX, IDC_EDIT_PIP_COUNT, m_iPipCount);
    DDX_Check(pDX, IDC_CHK_AUTO_OPEN_TRAY, m_bAutoOpenTray);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInquestDvr, CDialog)
	//{{AFX_MSG_MAP(CDlgInquestDvr)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_CBN_SELCHANGE(IDC_COMBO_CHAN_SECRET, OnSelchangeComboChanSecret)
	ON_CBN_SELCHANGE(IDC_COMBO_CHAN_CDRW, OnSelchangeComboChanCdrw)
	ON_BN_CLICKED(IDC_BUTTON_CDRW_OK, OnButtonCdrwOk)
	ON_BN_CLICKED(IDC_BUTTON_CDRW_SET, OnButtonCdrwSet)
	ON_BN_CLICKED(IDC_BUTTON_SET_SECRET_KEY, OnButtonSetSecretKey)
	ON_BN_CLICKED(IDC_BUTTON_SET_ENC_STATE, OnButtonSetEncState)
	ON_BN_CLICKED(IDC_BUTTON_START_CDRW, OnButtonStartCdrw)
	ON_BN_CLICKED(IDC_BUTTON_STOP_CDRW, OnButtonStopCdrw)
	ON_BN_CLICKED(IDC_BUTTON_CDRW_TIME, OnButtonCdrwTime)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_STATE, OnButtonUpdateState)
	ON_CBN_SELCHANGE(IDC_COMBO_CDRW_NUMBER, OnSelchangeComboCdrwNumber)
	ON_BN_CLICKED(IDC_BUTTON_FILE, OnButtonFile)
	ON_CBN_SELCHANGE(IDC_COMBO_PIP_NUM, OnSelchangeComboPipNum)
	ON_BN_CLICKED(IDC_BUTTON_PIP_OK, OnButtonPipOk)
	ON_BN_CLICKED(IDC_BUTTON_PIP_SET, OnButtonPipSet)
	ON_CBN_SELCHANGE(IDC_COMBO_INQUEST_ROOM, OnSelchangeComboInquestRoom)
	ON_BN_CLICKED(IDC_BUTTON_SEND_MESSAGE, OnButtonSendMessage)
	ON_CBN_SELCHANGE(IDC_COMBO_SENSOR, OnSelchangeComboSensor)
	ON_BN_CLICKED(IDC_BUTTON_SENSOR_OK, OnButtonSensorOk)
	ON_BN_CLICKED(IDC_BUTTON_SETUP_SYSTEM, OnButtonSetupSystem)
	ON_BN_CLICKED(IDC_BUTTON_INQUEST_EVENT, OnButtonInquestEvent)
	ON_BN_CLICKED(IDC_BUTTON_SET_SDK_SECRET, OnButtonSetSdkSecret)
	ON_BN_CLICKED(IDC_BUTTON_INQUEST_ROOM_OK, OnButtonInquestRoomSysOk)
	ON_CBN_SELCHANGE(IDC_COMBO_INQUEST_ROOM_SYS, OnSelchangeComboInquestRoomSys)
	ON_CBN_SELCHANGE(IDC_COMBO_CALC_MODE, OnSelchangeComboCalcMode)
    ON_BN_CLICKED(IDC_BUTTON_PAUSE_CDRW, OnButtonPauseCdrw)
	ON_BN_CLICKED(IDC_BUTTON_RESUMEE_CDRW, OnButtonResumeeCdrw)
	ON_BN_CLICKED(IDC_BTN_INQ_USER_RIGHT, OnBtnInqUserRight)
	ON_BN_CLICKED(IDC_BTN_MIX_AUDIOIN, OnBtnMixAudioin)
	ON_BN_CLICKED(IDC_BTN_INQ_CASE_INFO, OnBtnInquestCaseInfo)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON_TRAY_CONFIG, &CDlgInquestDvr::OnBnClickedButtonTrayConfig)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInquestDvr message handlers

void CDlgInquestDvr::initDialog() 
{
	m_lLoginID = g_struDeviceInfo[m_dwDeviceIndex].lLoginID;
	m_lStartChannel = g_struDeviceInfo[m_dwDeviceIndex].iStartChan;

	int i = 0;
	CString sTemp;
	DWORD dwCopyIndex = 0; 
	DWORD dwChanShow = 0;  
	char szLan[128] = {0};

	for (i = 0; i < MAX_CHANNUM_V30; i++)
	{
		dwChanShow = i + m_lStartChannel;
		
		if (i < MAX_ANALOG_CHANNUM)
		{
			sTemp.Format(ANALOG_C_FORMAT, dwChanShow);
		}
		else if(i >= MAX_ANALOG_CHANNUM)
		{
			sTemp.Format(DIGITAL_C_FORMAT, dwChanShow - MAX_ANALOG_CHANNUM);
		}

		if (g_struDeviceInfo[m_dwDeviceIndex].pStruChanInfo[i].bEnable)
		{	
			m_comboChanSecret.AddString(sTemp);
			m_comboChanCdrw.AddString(sTemp);
			m_comboChanTime.AddString(sTemp);

			m_comboChanSecret.SetItemData(dwCopyIndex, i);
			m_comboChanCdrw.SetItemData(dwCopyIndex, i);	
			m_comboChanTime.SetItemData(dwCopyIndex, i);	

			dwCopyIndex ++;
		}
		else 
		{
			continue;
		}
	}

	m_comboChanSecret.AddString("All Channel");
	m_comboChanSecret.SetItemData(dwCopyIndex, 0xff);	
	
	m_comboChanTime.AddString("All Channel");
	m_comboChanTime.SetItemData(dwCopyIndex, 0xff);	

	//Init combobox
	m_comboChanSecret.SetCurSel(0);
	m_comboChanCdrw.SetCurSel(0);
	m_comboChanTime.SetCurSel(0);
	m_comboPIPNum.SetCurSel(0);
	m_cmbInquestRoomSys.SetCurSel(0);
	m_cmbInquestTime.SetCurSel(0);
	m_cmbCalcMode.SetCurSel(0);
	m_strInquestRoom.byRoomIndex = 1;

	OnSelchangeComboCalcMode();

	m_cdDateStart = CTime::GetCurrentTime();
	m_ctDateStop = CTime::GetCurrentTime();
	m_ctTimeStart = CTime::GetCurrentTime();
	m_cTimeStop = CTime::GetCurrentTime();

	m_ctInquestDateStart = CTime::GetCurrentTime();
	m_ctInquestTimeStart = CTime::GetCurrentTime();
}


void CDlgInquestDvr::CheckInitPara() 
{
	char szLan[128] = {0};
	int i = 0;
	int iChanShow = 0;

	if(!NET_DVR_InquestGetDeviceVersion(m_lLoginID, &m_strDeviceVersion))
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_InquestGetDeviceVersion");
	}
	else
	{
		m_csDeviceVersion.Format("%d.%d.%d.%d", (DWORD)m_strDeviceVersion.byMainVersion,\
			                                    (DWORD)m_strDeviceVersion.bySubVersion,\
												(DWORD)m_strDeviceVersion.byUpgradeVersion,\
												(DWORD)m_strDeviceVersion.byCustomizeVersion);
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_InquestGetDeviceVersion");
	}
	
	if(!NET_DVR_InquestGetCDRWScheme(m_lLoginID, &m_strCdrwCfg))
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_InquestGetCDRWScheme");
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_InquestGetCDRWScheme");
	}

	for (i = 0; i < MAX_CHANNUM_V30; i++)
	{
		iChanShow = i + m_lStartChannel;
		if (g_struDeviceInfo[m_dwDeviceIndex].pStruChanInfo[i].bEnable)
		{
			if (!NET_DVR_InquestGetEncryptState(m_lLoginID, iChanShow, (BOOL*)&m_bEnc[i]))
			{
				g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_InquestGetEncryptState %s", g_struDeviceInfo[m_dwDeviceIndex].pStruChanInfo[i].chChanName);
			}
			else
			{
				g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_InquestGetEncryptState");
			}
		}
	}
	
	if(!NET_DVR_InquestCheckSecretKey(m_lLoginID, &m_bKeyState))
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_InquestCheckSecretKey");
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_InquestCheckSecretKey");
	}

	if(!NET_DVR_InquestGetSystemInfo(m_lLoginID, &m_strSystemInfo))
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_InquestGetSystemInfo");

		if(m_comboInquestRoom.GetCount() == 0)
		{
			m_comboInquestRoom.AddString("Inquest Room 1");
			m_comboInquestRoom.SetCurSel(0);
		}
	}
	else
	{
		if(m_comboInquestRoom.GetCount() == 0)
		{
			m_comboInquestRoom.AddString("Inquest Room 1");
			m_comboInquestRoom.AddString("Inquest Room 2");
			m_comboInquestRoom.SetCurSel(0);
		}
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_InquestGetSystemInfo");
	}
	
	m_bCheckCD1 = m_strCdrwCfg.dwRwSelectPara[0]&0x01;
	m_bCheckCD2 = (m_strCdrwCfg.dwRwSelectPara[0]>>1)&0x01;
	m_bCheckCD3 = (m_strCdrwCfg.dwRwSelectPara[0]>>2)&0x01;	
	m_bCheckCD4 = (m_strCdrwCfg.dwRwSelectPara[0]>>3)&0x01;	
		
	m_bEncrypt = m_bEnc[0];

	m_bKeySet = m_bKeyState;
	
	m_iCdrwNum = m_strCdrwCfg.dwNum;
	m_comboCdrwMode.SetCurSel(m_strCdrwCfg.dwModeSelect);
	m_comboCdrwInterval.SetCurSel(m_strCdrwCfg.dwInterval);
	m_bCdrwStart = m_strCdrwCfg.dwStartCDRW;
	m_bHDException = m_strCdrwCfg.dwHdExcp;
	m_csCDName.Format("%s", m_strCdrwCfg.sLable);

	m_comboReocrdMode.SetCurSel(m_strSystemInfo.dwRecordMode - 1);
	m_comboWorkMode.SetCurSel(m_strSystemInfo.dwWorkMode);
	m_comboResolution.SetCurSel(m_strSystemInfo.dwResolutionMode);
	m_cmbHashCheckCD.SetCurSel(m_strSystemInfo.byEnableHashCheck);
	m_cmbInitCD.SetCurSel(m_strSystemInfo.byEnableInitCD);

	m_bChkMile = m_strSystemInfo.struSensorInfo.dwSupportPro & 0x01;
    m_bChkLeicai =  (m_strSystemInfo.struSensorInfo.dwSupportPro >> 1)& 0x01;
	m_bChkYouli = (m_strSystemInfo.struSensorInfo.dwSupportPro >> 2)& 0x01;

	m_comboSensorNum.SetCurSel(0);
	OnSelchangeComboSensor();

	m_cmbInquestRoomSys.SetCurSel(0);
	OnSelchangeComboInquestRoomSys();

	m_cmbCalcMode.SetCurSel(m_strSystemInfo.struInquestRoomInfo[m_cmbInquestRoomSys.GetCurSel()].byCalcType);
	OnSelchangeComboCalcMode();

	OnSelchangeComboInquestRoom();
}

BOOL CDlgInquestDvr::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	initDialog();

	CheckInitPara();

	UpdateData(FALSE);
	
	return TRUE;
}

void CDlgInquestDvr::OnButtonExit() 
{
	if (m_hBackupThread)
	{
		TerminateThread(m_hBackupThread, 0);
		CloseHandle(m_hBackupThread);
		m_hBackupThread = NULL;
		NET_DVR_StopBackup(m_lBackupHandle);
	}

	if (m_hThread)
	{
		TerminateThread(m_hThread, 0);
		CloseHandle(m_hThread);
		m_hThread = NULL;
		NET_DVR_StopRemoteConfig(m_hRemoteConfig);
		m_hRemoteConfig = -1;
		m_bStatusGeting = FALSE;
	}

	CDialog::OnCancel();
}

void CDlgInquestDvr::OnSelchangeComboChanSecret() 
{
	UpdateData(TRUE);
	int iChan = m_comboChanSecret.GetItemData(m_comboChanSecret.GetCurSel());
	if(iChan == 0xff)
	{
		return;
	}
	m_bEncrypt = (m_bEnc[iChan] == 0)?FALSE:TRUE;
	UpdateData(FALSE);
}

void CDlgInquestDvr::OnSelchangeComboChanCdrw() 
{
	UpdateData(TRUE);
	int iChan = m_comboChanCdrw.GetItemData(m_comboChanCdrw.GetCurSel());
	m_bCheckCD1 = m_strCdrwCfg.dwRwSelectPara[iChan]&0x01;
	m_bCheckCD2 = (m_strCdrwCfg.dwRwSelectPara[iChan]>>1)&0x01;
	m_bCheckCD3 = (m_strCdrwCfg.dwRwSelectPara[iChan]>>2)&0x01;	
	m_bCheckCD4 = (m_strCdrwCfg.dwRwSelectPara[iChan]>>3)&0x01;	
	UpdateData(FALSE);
}

void CDlgInquestDvr::OnButtonCdrwOk() 
{
	UpdateData(TRUE);
	int iChan = m_comboChanCdrw.GetItemData(m_comboChanCdrw.GetCurSel());
	m_strCdrwCfg.dwRwSelectPara[iChan] = 0;
	m_strCdrwCfg.dwRwSelectPara[iChan]|= m_bCheckCD1;
	m_strCdrwCfg.dwRwSelectPara[iChan]|= (m_bCheckCD2<<1);
	m_strCdrwCfg.dwRwSelectPara[iChan]|= (m_bCheckCD3<<2);
	m_strCdrwCfg.dwRwSelectPara[iChan]|= (m_bCheckCD4<<3);
}

void CDlgInquestDvr::OnButtonCdrwSet() 
{
	UpdateData(TRUE);
	OnButtonCdrwOk();

	char szLan[128] = {0};

	m_strCdrwCfg.dwModeSelect = m_comboCdrwMode.GetCurSel();
	m_strCdrwCfg.dwInterval = m_comboCdrwInterval.GetCurSel();
	memcpy(m_strCdrwCfg.sLable, (char*)m_csCDName.GetBuffer(0), 64);

	if(!NET_DVR_InquestSetCDRWScheme(m_lLoginID, &m_strCdrwCfg))
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_InquestSetCDRWScheme");
		g_StringLanType(szLan, "设置刻录参数失败", "Set cdrw para failed!");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_InquestSetCDRWScheme");
	}
}

void CDlgInquestDvr::OnButtonSetSecretKey() 
{	
	UpdateData(TRUE);

	char szLan[128] = {0};
	NET_DVR_INQUEST_SECRET_INFO strSecretInfo = {0};
	
    memcpy(strSecretInfo.sSecretKey, m_csEncKey, 16);
	if(!NET_DVR_InquestSetSecretKey(m_lLoginID, &strSecretInfo))
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_InquestSetSecretKey");
		g_StringLanType(szLan, "设置码流加密密钥失败", "Set stream encrypt secret key failed!");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_InquestSetSecretKey");
	}
}

void CDlgInquestDvr::OnButtonSetEncState() 
{
	UpdateData(TRUE);
	
	char szLan[128] = {0};
	int iChan = m_comboChanSecret.GetItemData(m_comboChanSecret.GetCurSel());

	if(iChan != 0xff)
	{
		iChan += m_lStartChannel;
	}

	if(!NET_DVR_InquestStreamEncrypt(m_lLoginID, iChan, m_bEncrypt))
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_InquestStreamEncrypt");
		g_StringLanType(szLan, "控制通道码流加密失败", "Set encrypt state failed!");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_InquestStreamEncrypt");
		if(iChan == 0xff)
		{
			for (int i = 0; i < MAX_CHANNUM_V30; i++)
			{
				m_bEnc[i] = m_bEncrypt?1:0;
			}
			return;
		}
		m_bEnc[iChan - 1] = m_bEncrypt?1:0;
	}	
}

void CDlgInquestDvr::OnButtonStartCdrw() 
{
	UpdateData(TRUE);
	
	char szLan[128] = {0};
	if(!NET_DVR_InquestStartCDW_V30(m_lLoginID, &m_strInquestRoom, m_bPause))
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_InquestStartCDW");
		g_StringLanType(szLan, "开始刻录失败", "Start CD write failed!");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_InquestStartCDW");
	}	
}

void CDlgInquestDvr::OnButtonStopCdrw() 
{
	UpdateData(TRUE);
	
	char szLan[128] = {0};
	if(!NET_DVR_InquestStopCDW_V30(m_lLoginID, &m_strInquestRoom, m_bCancelWrite))
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_InquestStopCDW");
		g_StringLanType(szLan, "停止刻录失败", "Stop Cd write failed!");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_InquestStopCDW");
	}	
}

DWORD  GetCDWriteTimeThread(LPVOID pParam)
{
    CDlgInquestDvr *pThis = (CDlgInquestDvr*)pParam;
    pThis->GetDlgItem(IDC_STATIC_CDWRITE_STATE)->ShowWindow(SW_SHOW);
    DWORD dwState = 0;
    char szLan[256] = {0};

    while (1)
    {
        NET_DVR_GetBackupProgress(pThis->m_lBackupHandle, &dwState);

		TRACE("TUTU dwState[%d]", dwState);
        
        if (dwState == 100)
        {
            g_StringLanType(szLan, "刻录完成", "Succ to CD write");
            pThis->GetDlgItem(IDC_STATIC_CDWRITE_STATE)->SetWindowText(szLan);
			Sleep(1000);
            NET_DVR_StopBackup(pThis->m_lBackupHandle);
            g_StringLanType(szLan, "刻录", "CD Write");
            pThis->GetDlgItem(IDC_BUTTON_CDRW_TIME)->SetWindowText(szLan);
            pThis->m_bBackuping = FALSE;
            pThis->GetDlgItem(IDC_STATIC_CDWRITE_STATE)->ShowWindow(SW_HIDE);
            break;
        }
        else if (dwState == 400)
        {
            g_StringLanType(szLan, "接收状态异常", "Get state exception");
            pThis->GetDlgItem(IDC_STATIC_CDWRITE_STATE)->SetWindowText(szLan);
			Sleep(1000);
            NET_DVR_StopBackup(pThis->m_lBackupHandle);
            g_StringLanType(szLan, "刻录", "CD write");
            pThis->GetDlgItem(IDC_BUTTON_CDRW_TIME)->SetWindowText(szLan);
            pThis->m_bBackuping = FALSE;
            pThis->GetDlgItem(IDC_STATIC_CDWRITE_STATE)->ShowWindow(SW_HIDE);
            break;
        }
        else if (dwState == 500)
        {
            g_StringLanType(szLan, "刻录失败", "Failed to CD write");
            pThis->GetDlgItem(IDC_STATIC_CDWRITE_STATE)->SetWindowText(szLan);
			Sleep(1000);
            NET_DVR_StopBackup(pThis->m_lBackupHandle);
            g_StringLanType(szLan, "刻录", "CD write");
            pThis->GetDlgItem(IDC_BUTTON_CDRW_TIME)->SetWindowText(szLan);
            pThis->m_bBackuping = FALSE;
            pThis->GetDlgItem(IDC_STATIC_CDWRITE_STATE)->ShowWindow(SW_HIDE);
            break;
        }
        else if (dwState >= 0 && dwState < 100)
        {
            char szLanCn[128] = {0};
            char szLanEn[128] = {0};
            sprintf(szLanCn, "正在刻录[%d]", dwState);
            sprintf(szLanEn, "CD Writing[%d]", dwState);
            g_StringLanType(szLan, szLanCn, szLanCn);
            pThis->GetDlgItem(IDC_STATIC_CDWRITE_STATE)->SetWindowText(szLan);
        }
		//中间过程
		else if(dwState == BACKUP_SEARCH_DEVICE)
		{
            g_StringLanType(szLan, "正在搜索刻录设备", "searching CD write device");
            pThis->GetDlgItem(IDC_STATIC_CDWRITE_STATE)->SetWindowText(szLan);
		}
		else if(dwState == BACKUP_SEARCH_FILE)
		{
            g_StringLanType(szLan, "正在搜索录像文件", "searching record files");
            pThis->GetDlgItem(IDC_STATIC_CDWRITE_STATE)->SetWindowText(szLan);
		}
		//错误值
		else if(dwState >= BACKUP_TIME_SEG_NO_FILE)
		{
            char szLanCn[128] = {0};
            char szLanEn[128] = {0};
            sprintf(szLanCn, "刻录失败, 错误值[%d]", dwState);
            sprintf(szLanEn, "CD write failed, ErrorCode[%d]", dwState);
			g_StringLanType(szLan, szLanCn, szLanEn);
            pThis->GetDlgItem(IDC_STATIC_CDWRITE_STATE)->SetWindowText(szLan);
			Sleep(2000);	
            NET_DVR_StopBackup(pThis->m_lBackupHandle);
            g_StringLanType(szLan, "刻录", "CD Write");
            pThis->GetDlgItem(IDC_BUTTON_CDRW_TIME)->SetWindowText(szLan);
            pThis->m_bBackuping = FALSE;
            pThis->GetDlgItem(IDC_STATIC_CDWRITE_STATE)->ShowWindow(SW_HIDE);
            break;
		}
        Sleep(1000);
    }
    CloseHandle(pThis->m_hBackupThread);
    pThis->m_hBackupThread = NULL;
    
    return 0;
}

void CDlgInquestDvr::OnButtonCdrwTime() 
{
	UpdateData(TRUE);
	memset(&m_struBackupTimeParam, 0, sizeof(m_struBackupTimeParam));
    char szLan[256] = {0};
    if (!m_bBackuping)
    {
		int iChannel = m_comboChanTime.GetItemData(m_comboChanTime.GetCurSel());
		if(iChannel != 0xff)
		{
			iChannel += m_lStartChannel;
		}
		m_struBackupTimeParam.lChannel = iChannel;
        m_struBackupTimeParam.struStartTime.dwYear = m_cdDateStart.GetYear();
        m_struBackupTimeParam.struStartTime.dwMonth = m_cdDateStart.GetMonth();
        m_struBackupTimeParam.struStartTime.dwDay = m_cdDateStart.GetDay();
        m_struBackupTimeParam.struStartTime.dwHour = m_ctTimeStart.GetHour();
        m_struBackupTimeParam.struStartTime.dwMinute = m_ctTimeStart.GetMinute();
        m_struBackupTimeParam.struStartTime.dwSecond = m_ctTimeStart.GetSecond();
        m_struBackupTimeParam.struStopTime.dwYear = m_ctDateStop.GetYear();
        m_struBackupTimeParam.struStopTime.dwMonth = m_ctDateStop.GetMonth();
        m_struBackupTimeParam.struStopTime.dwDay = m_ctDateStop.GetDay();
        m_struBackupTimeParam.struStopTime.dwHour = m_cTimeStop.GetHour();
        m_struBackupTimeParam.struStopTime.dwMinute = m_cTimeStop.GetMinute();
		m_struBackupTimeParam.struStopTime.dwSecond = m_cTimeStop.GetSecond();
     
        m_lBackupHandle = NET_DVR_BackupByTime(m_lLoginID, &m_struBackupTimeParam);
        if (m_lBackupHandle == -1)
        {
            g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_BackupByTime");
            return;
        }
        else
        {
            g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_BackupByTime");
        }
        g_StringLanType(szLan, "停止刻录", "stop CD write");
        GetDlgItem(IDC_BUTTON_CDRW_TIME)->SetWindowText(szLan);
        
        DWORD dwThreadId = 0;
        if (m_hBackupThread == NULL)
        {
            m_hBackupThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetCDWriteTimeThread), this, 0, &dwThreadId);		
        }
        if (m_hBackupThread  == NULL)
        {
            char szLan[256] = {0};
            g_StringLanType(szLan, "打开刻录线程失败!", "Fail to open CD write thread!");
            AfxMessageBox(szLan);
            return;
        }
        g_StringLanType(szLan, "停止", "Stop");
        GetDlgItem(IDC_BUTTON_CDRW_TIME)->SetWindowText(szLan);
        m_bBackuping = TRUE;
        GetDlgItem(IDC_STATIC_CDWRITE_STATE)->ShowWindow(SW_SHOW);
    }
    else
    {
        if (m_hBackupThread)
        {
            TerminateThread(m_hBackupThread, 0);
        }
        
        CloseHandle(m_hBackupThread);
        m_hBackupThread = NULL;
        NET_DVR_StopBackup(m_lBackupHandle);
        g_StringLanType(szLan, "刻录", "CD Write");
        GetDlgItem(IDC_BUTTON_CDRW_TIME)->SetWindowText(szLan);
        m_bBackuping = FALSE;
        GetDlgItem(IDC_STATIC_CDWRITE_STATE)->ShowWindow(SW_HIDE);
    }
}

void CDlgInquestDvr::OnButtonUpdate() 
{
	m_comboChanSecret.SetCurSel(0);
	m_comboChanCdrw.SetCurSel(0);
	m_comboPIPNum.SetCurSel(0);
	m_comboSensorNum.SetCurSel(0);
	
	m_cdDateStart = CTime::GetCurrentTime();
	m_ctDateStop = CTime::GetCurrentTime();
	m_ctTimeStart = CTime::GetCurrentTime();
	m_cTimeStop = CTime::GetCurrentTime();
	
	CheckInitPara();
}

/*********************************************************
Function:	GetCDWStatusThread
Desc:		get fc thread
Input:		pParam,pointer to parameters
Output:	
Return:	
**********************************************************/
UINT GetCDWStatusThread(LPVOID pParam)
{
	LONG lRet = -1;
	CString csTmp;
	char szLan[128] = {0};

	CDlgInquestDvr *pThis = (CDlgInquestDvr*)pParam;
// 	HWND hWnd = pThis->GetSafeHwnd();
// 	if (NULL == hWnd)
// 	{
// 		return -1;
// 	}

	CButton *pBtnStateEnable = (CButton*)(pThis->GetDlgItem(IDC_CHECK_CDSTATE_ENABLE));
	CDateTimeCtrl *pInquestDateStart = (CDateTimeCtrl*)(pThis->GetDlgItem(IDC_COMBO_INQUEST_DATE_START));
	CDateTimeCtrl *pInquestTimeStart = (CDateTimeCtrl*)(pThis->GetDlgItem(IDC_COMBO_INQUEST_TIME_START));

	while (1)
	{
		lRet = NET_DVR_GetNextRemoteConfig(pThis->m_hRemoteConfig, &pThis->m_strCdrwStatus, sizeof(NET_DVR_INQUEST_CDRW_STATUS));
		if (lRet == NET_SDK_GET_NEXT_STATUS_SUCCESS)
		{	
			pThis->m_comboCdrwType.SetCurSel(pThis->m_strCdrwStatus.dwType);
			pThis->m_comboCdrwNumber.SetCurSel(0);
			pThis->m_comboCdrwState.SetCurSel(pThis->m_strCdrwStatus.strCDRWNum[0].dwStatus);
			pBtnStateEnable->SetCheck(pThis->m_strCdrwStatus.strCDRWNum[0].dwEnable);

			csTmp.Format("%d", pThis->m_strCdrwStatus.strCDRWNum[0].dwTimeLeft);
			pThis->GetDlgItem(IDC_EDIT_CDRW_TIME_LEFT)->SetWindowText(csTmp);

			csTmp.Format("%d", pThis->m_strCdrwStatus.strCDRWNum[0].dwVolumn);
			pThis->GetDlgItem(IDC_EDIT_VOLUMN)->SetWindowText(csTmp);

			csTmp.Format("%d", pThis->m_strCdrwStatus.strCDRWNum[0].dwFreeSpace);
			pThis->GetDlgItem(IDC_EDIT_FREE_SPACE)->SetWindowText(csTmp);

			csTmp.Format("%d", pThis->m_strCdrwStatus.strCDRWNum[0].byCDType);
			pThis->GetDlgItem(IDC_EDIT_CD_TYPE)->SetWindowText(csTmp);

            if (pThis->m_strCdrwStatus.struInquestStartTime.wYear >= 1970)
            {
                CTime ctTemp(pThis->m_strCdrwStatus.struInquestStartTime.wYear,
                    pThis->m_strCdrwStatus.struInquestStartTime.byMonth,
                    pThis->m_strCdrwStatus.struInquestStartTime.byDay,
                    pThis->m_strCdrwStatus.struInquestStartTime.byHour,
                    pThis->m_strCdrwStatus.struInquestStartTime.byMinute,
                    pThis->m_strCdrwStatus.struInquestStartTime.bySecond);
                pInquestDateStart->SetTime(&ctTemp);
                pInquestTimeStart->SetTime(&ctTemp);
            }
		}
		else if(lRet == NET_SDK_GET_NETX_STATUS_NEED_WAIT)
		{
			Sleep(5);
			continue;
		}
		else if (lRet == NET_SDK_GET_NEXT_STATUS_FINISH) 
		{
			g_StringLanType(szLan, "刷新状态", "Get Status");
			pThis->GetDlgItem(IDC_BUTTON_UPDATE_STATE)->SetWindowText(szLan);
			pThis->m_bStatusGeting = FALSE;
			break;
		}
		else
		{
			g_StringLanType(szLan, "刷新状态", "Get Status");
			pThis->GetDlgItem(IDC_BUTTON_UPDATE_STATE)->SetWindowText(szLan);
			pThis->m_bStatusGeting = FALSE;
			g_StringLanType(szLan, "由于服务器忙,或网络故障,获取异常终止", "Since the server is busy, or network failure, abnormal termination of access  info");
			AfxMessageBox(szLan);
			break;
		}
	}
	
	CloseHandle(pThis->m_hThread);
	pThis->m_hThread = NULL;
	NET_DVR_StopRemoteConfig(pThis->m_hRemoteConfig);
	pThis->m_hRemoteConfig = -1;
	pThis->m_bStatusGeting = FALSE;
	return 0;
}

void CDlgInquestDvr::OnButtonUpdateState() 
{

	UpdateData(TRUE);
	char szLan[128] = {0};
	if (!m_bStatusGeting)
	{
		
		m_hRemoteConfig = NET_DVR_StartRemoteConfig(m_lLoginID, NET_DVR_INQUEST_GET_CDW_STATUS, &m_strInquestRoom, sizeof(NET_DVR_INQUEST_ROOM), NULL, NULL);
		if (m_hRemoteConfig < 0)
		{
			g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartRemoteConfig NET_DVR_INQUEST_GET_CDW_STATUS");
			g_StringLanType(szLan, "获取刻录状态失败!", "Fail to get cdw status");
			AfxMessageBox(szLan);
			return;
		}

		DWORD dwThreadId;
		if (m_hThread == NULL)
		{
			m_hThread = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetCDWStatusThread), this, 0, &dwThreadId);		
		}
		
		if (m_hThread == NULL)
		{
			g_StringLanType(szLan, "打开线程失败!", "Fail to open thread!");
			AfxMessageBox(szLan);
			return;
		}
		
		g_StringLanType(szLan, "停止获取", "Stop Getting");
		GetDlgItem(IDC_BUTTON_UPDATE_STATE)->SetWindowText(szLan);
		m_bStatusGeting = TRUE;
	}
	else
	{
		if (m_hThread)
		{
			TerminateThread(m_hThread, 0);
		}
		CloseHandle(m_hThread);
		m_hThread = NULL;
		NET_DVR_StopRemoteConfig(m_hRemoteConfig);
		g_StringLanType(szLan, "刷新状态", "Get Status");
		GetDlgItem(IDC_BUTTON_UPDATE_STATE)->SetWindowText(szLan);
		m_bStatusGeting = FALSE;
	}

}

void CDlgInquestDvr::OnSelchangeComboCdrwNumber() 
{
	UpdateData(TRUE);
    
	int iCdNum = m_comboCdrwNumber.GetCurSel();
	m_comboCdrwState.SetCurSel(m_strCdrwStatus.strCDRWNum[iCdNum].dwStatus);
	m_bCDStateEnable = m_strCdrwStatus.strCDRWNum[iCdNum].dwEnable;
	m_dwVolumn = m_strCdrwStatus.strCDRWNum[iCdNum].dwVolumn;
	m_dwFreeSpace = m_strCdrwStatus.strCDRWNum[iCdNum].dwFreeSpace;
	m_dwTimeLeft = m_strCdrwStatus.strCDRWNum[iCdNum].dwTimeLeft;
	m_byCDType = m_strCdrwStatus.strCDRWNum[iCdNum].byCDType;

	UpdateData(FALSE);	
}

void CDlgInquestDvr::OnButtonFile() 
{
	CDlgInquestFile dlg;
	dlg.m_lLoginID = m_lLoginID;
	dlg.m_dwDeviceIndex = m_dwDeviceIndex;
	dlg.m_strInquestRoom.byRoomIndex = m_strInquestRoom.byRoomIndex;
	dlg.DoModal();
}

void CDlgInquestDvr::OnSelchangeComboPipNum() 
{
	UpdateData(TRUE);
    
	int iPIPNum = m_comboPIPNum.GetCurSel();
	m_iShowChan = m_strPIPStatus.strPipPara[iPIPNum].byPipChan;
	m_iPIPX = m_strPIPStatus.strPipPara[iPIPNum].wTopLeftX;
	m_iPIPY = m_strPIPStatus.strPipPara[iPIPNum].wTopLeftY;
	m_wPipHeight = m_strPIPStatus.strPipPara[iPIPNum].wHeight;
	m_wWidth = m_strPIPStatus.strPipPara[iPIPNum].wWidth;
	
	UpdateData(FALSE);	
}

void CDlgInquestDvr::OnButtonPipOk() 
{
	UpdateData(TRUE);
    
	int iPIPNum = m_comboPIPNum.GetCurSel();
	m_strPIPStatus.strPipPara[iPIPNum].byPipChan = m_iShowChan;
	m_strPIPStatus.strPipPara[iPIPNum].wTopLeftX = m_iPIPX;
	m_strPIPStatus.strPipPara[iPIPNum].wTopLeftY = m_iPIPY;
	m_strPIPStatus.strPipPara[iPIPNum].wHeight = m_wPipHeight;
	m_strPIPStatus.strPipPara[iPIPNum].wWidth = m_wWidth;
}

void CDlgInquestDvr::OnButtonPipSet() 
{
	UpdateData(TRUE);
	char szLan[128] = {0};
	
	OnButtonPipOk();
	m_strPIPStatus.struStructHead.wLength = sizeof(m_strPIPStatus);
	m_strPIPStatus.byBaseChan = m_iChanPIP;
	m_strPIPStatus.byBackChan = m_iBackChan;
	m_strPIPStatus.byPIPMode = m_comboPIPMode.GetCurSel();
	
	m_strPIPStatus.byPipCount = m_iPipCount;
	m_strPIPStatus.byPicShowMode = m_comboShowMode.GetCurSel();
	if(!NET_DVR_InquestSetPIPStatus_V40(m_lLoginID, &m_strInquestRoom, &m_strPIPStatus))
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_InquestSetPIPStatus_V40");
		g_StringLanType(szLan, "设置画中画参数失败", "Set PIP para failed!");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_InquestSetPIPStatus_V40");
	}	
}

void CDlgInquestDvr::OnSelchangeComboInquestRoom() 
{
	char szLan[256] = {0};

	m_strInquestRoom.byRoomIndex = m_comboInquestRoom.GetCurSel() + 1;

	if (!NET_DVR_InquestGetPIPStatus_V40(m_lLoginID, &m_strInquestRoom, &m_strPIPStatus))
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_InquestGetPIPStatus_V40");
		g_StringLanType(szLan, "获取画中画状态失败", "Get PIP state  failed");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_InquestGetPIPStatus_V40");
	}
	m_iShowChan = m_strPIPStatus.strPipPara[0].byPipChan;
	m_iPIPX = m_strPIPStatus.strPipPara[0].wTopLeftX;
	m_iPIPY = m_strPIPStatus.strPipPara[0].wTopLeftY;
	m_wPipHeight = m_strPIPStatus.strPipPara[0].wHeight;
	m_wWidth = m_strPIPStatus.strPipPara[0].wWidth;
	m_iChanPIP = m_strPIPStatus.byBaseChan;
	m_iBackChan = m_strPIPStatus.byBackChan;
	m_iPipCount = m_strPIPStatus.byPipCount;
	m_comboShowMode.SetCurSel(m_strPIPStatus.byPicShowMode);
	m_comboPIPMode.SetCurSel(m_strPIPStatus.byPIPMode);
	
	UpdateData(FALSE);
}

void CDlgInquestDvr::OnButtonSendMessage() 
{
	UpdateData(TRUE);
	char szLan[256] = {0};
	if(m_csMessage.GetLength() > (INQUEST_MESSAGE_LEN -1))
	{
		g_StringLanType(szLan, "重点标记信息长度需小于44", "Inquest message length should be less than 44");
		AfxMessageBox(szLan);
	}
	else
	{
		NET_DVR_INQUEST_MESSAGE strMessage = {0};
		memcpy(strMessage.sMessage, m_csMessage.GetBuffer(0), m_csMessage.GetLength());
		if(!NET_DVR_InquestSendMessage(m_lLoginID, &m_strInquestRoom, &strMessage))
		{
			g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_InquestSendMessage");
		}
		else
		{
			g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_InquestSetPIPStatus");
		}
	}
}

void CDlgInquestDvr::OnSelchangeComboSensor() 
{
	int iSensorIndex = m_comboSensorNum.GetCurSel();

	m_comboSensorType.SetCurSel(m_strSystemInfo.struSensorInfo.struSensorDevice[iSensorIndex].wDeviceType);
	m_wSensorAddr = m_strSystemInfo.struSensorInfo.struSensorDevice[iSensorIndex].wDeviceAddr;

	UpdateData(FALSE);
}

void CDlgInquestDvr::OnButtonSensorOk() 
{
	UpdateData(TRUE);
	int iSensorIndex = m_comboSensorNum.GetCurSel();

	m_strSystemInfo.struSensorInfo.struSensorDevice[iSensorIndex].wDeviceType = m_comboSensorType.GetCurSel();
	m_strSystemInfo.struSensorInfo.struSensorDevice[iSensorIndex].wDeviceAddr = m_wSensorAddr;
}

void CDlgInquestDvr::OnButtonSetupSystem() 
{
	m_strSystemInfo.dwRecordMode = m_comboReocrdMode.GetCurSel() + 1;
	m_strSystemInfo.dwResolutionMode = m_comboResolution.GetCurSel();
	m_strSystemInfo.dwWorkMode = m_comboWorkMode.GetCurSel();
	m_strSystemInfo.byEnableHashCheck = m_cmbHashCheckCD.GetCurSel();
	m_strSystemInfo.byEnableInitCD = m_cmbInitCD.GetCurSel();

	char szLan[256] = {0};
	if(!NET_DVR_InquestSetSystemInfo(m_lLoginID, &m_strSystemInfo))
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_InquestSetSystemInfo");
		g_StringLanType(szLan, "设置审讯系统信息失败", "Set Inquest System info failed!");
		AfxMessageBox(szLan);
		return;	
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_InquestSetSystemInfo");
	}
}

void CDlgInquestDvr::OnButtonInquestEvent() 
{
	CDlgInquestEvent dlg;
	dlg.m_lLoginID = m_lLoginID;
	dlg.m_iDeviceIndex = m_dwDeviceIndex;
	dlg.m_byRoomIndex = m_strInquestRoom.byRoomIndex;
	dlg.DoModal();	
}

void CDlgInquestDvr::OnButtonSetSdkSecret() 
{
	UpdateData(TRUE);
	char sSecretKey[16] = {0};
	memcpy(sSecretKey, m_csEncKey, sizeof(sSecretKey));

	//设置sdk内部解码密钥
	NET_DVR_SetSDKSecretKey(m_lLoginID, sSecretKey);
}

void CDlgInquestDvr::OnButtonInquestRoomSysOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iRoomIndex = m_cmbInquestRoomSys.GetCurSel();
	
	m_strSystemInfo.struInquestRoomInfo[iRoomIndex].byAlarmThreshold = m_byAudioThreshold;
	m_strSystemInfo.struInquestRoomInfo[iRoomIndex].byAutoDelRecord = m_bAudoDelRecord;
	m_strSystemInfo.struInquestRoomInfo[iRoomIndex].byInquestChannelResolution = m_cmbInquestChannelResolution.GetCurSel();
	m_strSystemInfo.struInquestRoomInfo[iRoomIndex].byCalcType = m_cmbCalcMode.GetCurSel();
	if (0 == m_cmbCalcMode.GetCurSel())
	{
		m_strSystemInfo.struInquestRoomInfo[iRoomIndex].uCalcMode.byBitRate = m_cmbInquestTime.GetCurSel();
	}
	else if(1 == m_cmbCalcMode.GetCurSel())
	{
		m_strSystemInfo.struInquestRoomInfo[iRoomIndex].uCalcMode.byInquestTime = m_cmbInquestTime.GetCurSel();
	}
	
	strncpy(m_strSystemInfo.struInquestRoomInfo[iRoomIndex].szCDName, m_strDiskName, 31);

    m_strSystemInfo.struInquestRoomInfo[iRoomIndex].byAutoOpenTray = m_bAutoOpenTray;
}

void CDlgInquestDvr::OnSelchangeComboInquestRoomSys() 
{
	// TODO: Add your control notification handler code here
	int iRoomIndex = m_cmbInquestRoomSys.GetCurSel();

	m_byAudioThreshold = m_strSystemInfo.struInquestRoomInfo[iRoomIndex].byAlarmThreshold;
	m_bAudoDelRecord = m_strSystemInfo.struInquestRoomInfo[iRoomIndex].byAutoDelRecord;
	m_cmbCalcMode.SetCurSel(m_strSystemInfo.struInquestRoomInfo[iRoomIndex].byCalcType);
	m_cmbInquestChannelResolution.SetCurSel(m_strSystemInfo.struInquestRoomInfo[iRoomIndex].byInquestChannelResolution);
	if (0 == m_cmbCalcMode.GetCurSel())
	{
		m_cmbInquestTime.SetCurSel(m_strSystemInfo.struInquestRoomInfo[iRoomIndex].uCalcMode.byBitRate);
	}
	else if(1 == m_cmbCalcMode.GetCurSel())
	{
		m_cmbInquestTime.SetCurSel(m_strSystemInfo.struInquestRoomInfo[iRoomIndex].uCalcMode.byInquestTime);
	}
	m_strDiskName.Format("%s", m_strSystemInfo.struInquestRoomInfo[iRoomIndex].szCDName);

    m_bAutoOpenTray = m_strSystemInfo.struInquestRoomInfo[iRoomIndex].byAutoOpenTray;

	UpdateData(FALSE);
}

void CDlgInquestDvr::OnSelchangeComboCalcMode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (0 == m_cmbCalcMode.GetCurSel())
	{
		GetDlgItem(IDC_STATIC_CALC_MODE)->SetWindowText("码率");
		m_cmbInquestTime.ResetContent();
		m_cmbInquestTime.AddString("32");
		m_cmbInquestTime.AddString("48");
		m_cmbInquestTime.AddString("64");
		m_cmbInquestTime.AddString("80");
		m_cmbInquestTime.AddString("96");
		m_cmbInquestTime.AddString("128");
		m_cmbInquestTime.AddString("160");
		m_cmbInquestTime.AddString("192");
		m_cmbInquestTime.AddString("224");
		m_cmbInquestTime.AddString("256");
		m_cmbInquestTime.AddString("320");
		m_cmbInquestTime.AddString("384");
		m_cmbInquestTime.AddString("448");
		m_cmbInquestTime.AddString("512");
		m_cmbInquestTime.AddString("640");
		m_cmbInquestTime.AddString("768");
		m_cmbInquestTime.AddString("896");
		m_cmbInquestTime.AddString("1024");
		m_cmbInquestTime.AddString("1280");
		m_cmbInquestTime.AddString("1536");
		m_cmbInquestTime.AddString("1792");
		m_cmbInquestTime.AddString("2048");
		m_cmbInquestTime.AddString("3072");
		m_cmbInquestTime.AddString("4096");
		m_cmbInquestTime.AddString("6144");
		m_cmbInquestTime.SetCurSel(m_strSystemInfo.struInquestRoomInfo[m_cmbInquestRoomSys.GetCurSel()].uCalcMode.byBitRate);
	}
	else if(1 == m_cmbCalcMode.GetCurSel())
	{
		GetDlgItem(IDC_STATIC_CALC_MODE)->SetWindowText("时间");
		m_cmbInquestTime.ResetContent();
		m_cmbInquestTime.AddString("1小时");
		m_cmbInquestTime.AddString("2小时");
		m_cmbInquestTime.AddString("3小时");
		m_cmbInquestTime.AddString("4小时");
		m_cmbInquestTime.AddString("6小时");
		m_cmbInquestTime.AddString("8小时");
		m_cmbInquestTime.AddString("10小时");
		m_cmbInquestTime.AddString("12小时");
		m_cmbInquestTime.AddString("16小时");
		m_cmbInquestTime.AddString("20小时");
		m_cmbInquestTime.AddString("22小时");
		m_cmbInquestTime.AddString("24小时");
		m_cmbInquestTime.SetCurSel(m_strSystemInfo.struInquestRoomInfo[m_cmbInquestRoomSys.GetCurSel()].uCalcMode.byInquestTime);
	}

	UpdateData(FALSE);
	
}

void CDlgInquestDvr::OnButtonPauseCdrw() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    memset(&m_strInquestRoom,0,sizeof(m_strInquestRoom));
    m_strInquestRoom.byFileType = 2;
    m_strInquestRoom.byRoomIndex = 1;
    
    if(!NET_DVR_RemoteControl(m_lLoginID, NET_DVR_INQUEST_PAUSE_CDW,&m_strInquestRoom, sizeof(m_strInquestRoom)))
    {
        g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_INQUEST_PAUSE_CDW");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_INQUEST_PAUSE_CDW");
    }
    
    UpdateData(FALSE);
}

void CDlgInquestDvr::OnButtonResumeeCdrw() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    memset(&m_strInquestRoom,0,sizeof(m_strInquestRoom));
    m_strInquestRoom.byFileType = 2;
    m_strInquestRoom.byRoomIndex = 1;
    
    if(!NET_DVR_RemoteControl(m_lLoginID, NET_DVR_INQUEST_RESUME_CDW,&m_strInquestRoom, sizeof(m_strInquestRoom)))
    {
        g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_FAIL_T, "NET_DVR_INQUEST_RESUME_CDW");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDeviceIndex, OPERATION_SUCC_T, "NET_DVR_INQUEST_RESUME_CDW");
        
    }
}


#include "DlgInqUserRight.h"
void CDlgInquestDvr::OnBtnInqUserRight() 
{
	// TODO: Add your control notification handler code here
	CDlgInqUserRight dlg;
	dlg.m_lUserID = m_lLoginID;
	dlg.m_iDeviceIndex = m_dwDeviceIndex;
	dlg.DoModal();
}

#include "DlgInqMixAudioInCfg.h"
void CDlgInquestDvr::OnBtnMixAudioin() 
{
	// TODO: Add your control notification handler code here
	CDlgInqMixAudioInCfg dlg;
	dlg.m_lUserID = m_lLoginID;
	dlg.m_iDeviceIndex = m_dwDeviceIndex;
	dlg.DoModal();
}

#include "DlgInquestCaseInfo.h"
void CDlgInquestDvr::OnBtnInquestCaseInfo()
{
	CDlgInquestCaseInfo dlg;
	dlg.DoModal();
}


void CDlgInquestDvr::OnBnClickedButtonTrayConfig()
{
    // TODO:  在此添加控件通知处理程序代码
    CDlgInquestTrayConfig dlg;
    dlg.m_lUserID = m_lLoginID;
    dlg.m_iDeviceIndex = m_dwDeviceIndex;
    dlg.DoModal();
}
