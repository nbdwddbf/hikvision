// DlgIPCPlateRecog.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgIPCPlateRecog.h"
#include "DlgVcaITCTriggerCfg.h"
#include "DlgITSOverlapCfg.h"
#include "DlgITSIpcCfg.h"
#include "DlgManualSnap.h"
#include "DlgCloudStorageCfg.h"
#include "MimeProtocolParsing.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIPCPlateRecog dialog


CDlgIPCPlateRecog::CDlgIPCPlateRecog(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIPCPlateRecog::IDD, pParent)
    , m_bLane(FALSE)
    , m_strLaneID(_T(""))
{
	//{{AFX_DATA_INIT(CDlgIPCPlateRecog)
	m_iHour11 = 0;
	m_iHour12 = 0;
	m_iHour21 = 0;
	m_iHour22 = 0;
	m_iHour31 = 0;
	m_iHour32 = 0;
	m_iHour41 = 0;
	m_iHour42 = 0;
	m_iHour51 = 0;
	m_iHour52 = 0;
	m_iHour61 = 0;
	m_iHour62 = 0;
	m_iHour71 = 0;
	m_iHour72 = 0;
	m_iHour81 = 0;
	m_iHour82 = 0;
	m_iMin11 = 0;
	m_iMin12 = 0;
	m_iMin21 = 0;
	m_iMin22 = 0;
	m_iMin31 = 0;
	m_iMin32 = 0;
	m_iMin41 = 0;
	m_iMin42 = 0;
	m_iMin51 = 0;
	m_iMin52 = 0;
	m_iMin61 = 0;
	m_iMin62 = 0;
	m_iMin71 = 0;
	m_iMin72 = 0;
	m_iMin81 = 0;
	m_iMin82 = 0;
	m_bUploadCenter = FALSE;
	m_byPicQuality = 0;
	m_dwPicSize = 0;
	m_bFTP = FALSE;
    m_bCloud = FALSE;
	m_bChkInvokeAlarmOut = FALSE;
	//}}AFX_DATA_INIT

	m_lServerID = -1; // 用户ID
    m_iDevIndex = -1; // 设备索引
	m_lChannel = -1;
	memset(&m_struGuardCfg, 0, sizeof(m_struGuardCfg));
	memset(&m_struGuardCond, 0, sizeof(m_struGuardCond));

	m_pbAlarmOut = NULL;

	m_pbAlarmOut = new BOOL[MAX_ALARMOUT_V40];
    if (m_pbAlarmOut == NULL)
    {
        return;
    }
    memset(m_pbAlarmOut,0,sizeof(BOOL)*MAX_ALARMOUT_V40);
    m_pbRecordChan = NULL;
    m_pbRecordChan = new BOOL[MAX_CHANNUM_V40];
    if (m_pbRecordChan == NULL)
    {
        return;
    }
	
    memset(m_pbRecordChan,0,sizeof(BOOL)*MAX_CHANNUM_V40);
}

/*********************************************************
Function:	CDlgIPCPlateRecog
Desc:		destructor
Input:	
Output:	
Return:	
**********************************************************/
CDlgIPCPlateRecog::~CDlgIPCPlateRecog()
{
	// TODO: add construction code here,
	if (m_pbAlarmOut != NULL)
	{
		delete[] m_pbAlarmOut;
		m_pbAlarmOut = NULL;
	}

	if (m_pbRecordChan != NULL)
	{
		delete[] m_pbRecordChan;
		m_pbRecordChan = NULL;
	}

}
void CDlgIPCPlateRecog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgIPCPlateRecog)
    DDX_Control(pDX, IDC_COMBO_GROUP, m_cmbGroupNo);
    DDX_Control(pDX, IDC_TREE_RECORDCHAN, m_treeChan);
    DDX_Control(pDX, IDC_TREE_TRIGGER_ALARM_OUT, m_treeAlarmOut);
    DDX_Control(pDX, IDC_COMBO_PIC_RELATE_TYPE, m_comPicRelateType);
    DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cmbChannel);
    DDX_Control(pDX, IDC_COMBO_RELATE_TYPE, m_comRelateType);
    DDX_Control(pDX, IDC_COMBOCOPYTIME, m_comboCopyTime);
    DDX_Control(pDX, IDC_COMBOWEEKDAY, m_comboWeekday);
    DDX_Text(pDX, IDC_EDITHOUR11, m_iHour11);
    DDX_Text(pDX, IDC_EDITHOUR12, m_iHour12);
    DDX_Text(pDX, IDC_EDITHOUR21, m_iHour21);
    DDX_Text(pDX, IDC_EDITHOUR22, m_iHour22);
    DDX_Text(pDX, IDC_EDITHOUR31, m_iHour31);
    DDX_Text(pDX, IDC_EDITHOUR32, m_iHour32);
    DDX_Text(pDX, IDC_EDITHOUR41, m_iHour41);
    DDX_Text(pDX, IDC_EDITHOUR42, m_iHour42);
    DDX_Text(pDX, IDC_EDITHOUR51, m_iHour51);
    DDX_Text(pDX, IDC_EDITHOUR52, m_iHour52);
    DDX_Text(pDX, IDC_EDITHOUR61, m_iHour61);
    DDX_Text(pDX, IDC_EDITHOUR62, m_iHour62);
    DDX_Text(pDX, IDC_EDITHOUR71, m_iHour71);
    DDX_Text(pDX, IDC_EDITHOUR72, m_iHour72);
    DDX_Text(pDX, IDC_EDITHOUR81, m_iHour81);
    DDX_Text(pDX, IDC_EDITHOUR82, m_iHour82);
    DDX_Text(pDX, IDC_EDITMIN11, m_iMin11);
    DDX_Text(pDX, IDC_EDITMIN12, m_iMin12);
    DDX_Text(pDX, IDC_EDITMIN21, m_iMin21);
    DDX_Text(pDX, IDC_EDITMIN22, m_iMin22);
    DDX_Text(pDX, IDC_EDITMIN31, m_iMin31);
    DDX_Text(pDX, IDC_EDITMIN32, m_iMin32);
    DDX_Text(pDX, IDC_EDITMIN41, m_iMin41);
    DDX_Text(pDX, IDC_EDITMIN42, m_iMin42);
    DDX_Text(pDX, IDC_EDITMIN51, m_iMin51);
    DDX_Text(pDX, IDC_EDITMIN52, m_iMin52);
    DDX_Text(pDX, IDC_EDITMIN61, m_iMin61);
    DDX_Text(pDX, IDC_EDITMIN62, m_iMin62);
    DDX_Text(pDX, IDC_EDITMIN71, m_iMin71);
    DDX_Text(pDX, IDC_EDITMIN72, m_iMin72);
    DDX_Text(pDX, IDC_EDITMIN81, m_iMin81);
    DDX_Text(pDX, IDC_EDITMIN82, m_iMin82);
    DDX_Check(pDX, IDC_CHK_UPLOAD_CENTER, m_bUploadCenter);
    DDX_Text(pDX, IDC_EDIT_PIC_QUALITY, m_byPicQuality);
    DDX_Text(pDX, IDC_EDIT_PIC_SIZE, m_dwPicSize);
    DDX_Text(pDX, IDC_EDIT_SCENE_ID1, m_iSceneID1);
    DDX_Text(pDX, IDC_EDIT_SCENE_ID2, m_iSceneID2);
    DDX_Text(pDX, IDC_EDIT_SCENE_ID3, m_iSceneID3);
    DDX_Text(pDX, IDC_EDIT_SCENE_ID4, m_iSceneID4);
    DDX_Text(pDX, IDC_EDIT_SCENE_ID5, m_iSceneID5);
    DDX_Text(pDX, IDC_EDIT_SCENE_ID6, m_iSceneID6);
    DDX_Text(pDX, IDC_EDIT_SCENE_ID7, m_iSceneID7);
    DDX_Text(pDX, IDC_EDIT_SCENE_ID8, m_iSceneID8);
    DDX_Control(pDX, IDC_COMBO_PIC_TYPE, m_comPicType);
    DDX_Check(pDX, IDC_CHK_PIC_FTP, m_bFTP);
    DDX_Check(pDX, IDC_CHK_PIC_CLOUD, m_bCloud);
    DDX_Check(pDX, IDC_CHK_INVOKE_ALARM_OUT, m_bChkInvokeAlarmOut);
    DDX_Check(pDX, IDC_CHK_ALARM_EMAP, m_bEMap);
    DDX_Check(pDX, IDC_CHK_ALARM_FOCUS, m_bFocus);
    DDX_Check(pDX, IDC_CHK_ALARM_PTZ, m_bPTZ);
    DDX_Check(pDX, IDC_CHK_ALARMIN_INVOKE_ALARMOUT, m_bInvokeAlarmOut);
    DDX_Check(pDX, IDC_CHK_ALARMIN_MONITOR, m_bMonitor);
    DDX_Check(pDX, IDC_CHK_INVOKE_JPEG_CAPTURE, m_bJepgCap);
    DDX_Check(pDX, IDC_CHK_ALARMIN_VOICE, m_bVoice);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMBO_DIRECTION, m_comEventTriggerDirection);
    DDX_Check(pDX, IDC_CHECK_LANE, m_bLane);
    DDX_Text(pDX, IDC_EDIT_LANE_ID, m_strLaneID);
}


BEGIN_MESSAGE_MAP(CDlgIPCPlateRecog, CDialog)
	//{{AFX_MSG_MAP(CDlgIPCPlateRecog)
	ON_BN_CLICKED(IDC_TIME_OK2, OnTimeOk2)
	ON_BN_CLICKED(IDC_TIME_COPY2, OnTimeCopy2)
	ON_BN_CLICKED(IDC_BTN_SET_GUARD, OnBtnSetGuard)
	ON_BN_CLICKED(IDC_BTN_GET_GUARD, OnBtnGetGuard)
	ON_CBN_SELCHANGE(IDC_COMBOWEEKDAY, OnSelchangeComboweekday)
	ON_CBN_SELCHANGE(IDC_COMBO_PIC_TYPE, OnSelchangeComPicType)
	ON_BN_CLICKED(IDC_BTN_GET_PIC_INFO, OnBtnGetPicInfo)
	ON_BN_CLICKED(IDC_BTN_SET_PIC_INFO, OnBtnSetPicInfo)
	ON_BN_CLICKED(IDC_BTN_TRIGGEREX_CFG, OnBtnTriggerexCfg)
	ON_BN_CLICKED(IDC_BTN_OVERLAP_CFG, OnBtnOverlapCfg)
	ON_BN_CLICKED(IDC_BTN_IPC_CHAN_CFG, OnBtnIpcChanCfg)
	ON_BN_CLICKED(IDC_BTN_MANUAL_SNAP_PLATE, OnBtnManualSnapPlate)
	ON_BN_CLICKED(IDC_BTN_CLOUDSTORAGE_CFG, OnBtnCloudStorageCfg)
	ON_BN_CLICKED(IDC_BTN_COMPLETE_RESTORE, OnBtnCompleteRestore)
	ON_BN_CLICKED(IDC_CHK_INVOKE_ALARM_OUT, OnChkInvokeAlarmOut)
	ON_NOTIFY(NM_CLICK, IDC_TREE_TRIGGER_ALARM_OUT, OnClickTreeTriggerAlarmOut)
	ON_NOTIFY(NM_CLICK, IDC_TREE_RECORDCHAN, OnClickTreeRecordchan)
	ON_CBN_SELCHANGE(IDC_COMBO_GROUP, OnSelchangeComboGroup)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON_TRIGGER, &CDlgIPCPlateRecog::OnBnClickedButtonTrigger)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgIPCPlateRecog message handlers

BOOL CDlgIPCPlateRecog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char szLan[128] ={0};
	m_comPicType.SetCurSel(0);
	m_cmbChannel.ResetContent();
    DWORD dwIndex = 0;
	int i = 0;

    for ( i = 0; i< g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;i++)
    {
        m_cmbChannel.AddString(g_struDeviceInfo[m_iDevIndex].pStruChanInfo[i].chChanName);
        m_cmbChannel.SetItemData(dwIndex++, g_struDeviceInfo[m_iDevIndex].pStruChanInfo[i].iChannelNO);
    }
    m_cmbChannel.SetCurSel(0);

	m_comRelateType.SetCurSel(0);
    m_comPicRelateType.SetCurSel(0);

    if ((g_struDeviceInfo[m_iDevIndex].bySupport7 & 0x02) != 0x02)
    {
        GetDlgItem(IDC_COMBO_PIC_RELATE_TYPE)->EnableWindow(FALSE);
    }
    else
    {
        GetDlgItem(IDC_COMBO_PIC_RELATE_TYPE)->EnableWindow(TRUE);
    }

	m_cmbGroupNo.ResetContent();

	if (g_struDeviceInfo[m_iDevIndex].iIPChanNum == 0)
	{
		m_cmbGroupNo.AddString("0");
	}
	else
	{
		DWORD  dwMaxChanNo = 0;
		DWORD  dwMaxGroupNO = 0;
		DWORD  dwMaxGroupNoByAlarm = 0;
		if (g_struDeviceInfo[m_iDevIndex].pStruIPAlarmOutCfgV40 != NULL)
		{
			dwMaxGroupNoByAlarm = g_struDeviceInfo[m_iDevIndex].pStruIPAlarmOutCfgV40->dwCurIPAlarmOutNum + 32;
			if (dwMaxGroupNoByAlarm%MAX_CHANNUM_V30 == 0)
			{
				dwMaxGroupNoByAlarm = dwMaxGroupNoByAlarm/MAX_CHANNUM_V30;
			}
			else
			{
				dwMaxGroupNoByAlarm = dwMaxGroupNoByAlarm /MAX_CHANNUM_V30 +1;
			}
		}

		dwMaxChanNo = g_struDeviceInfo[m_iDevIndex].iIPChanNum + g_struDeviceInfo[m_iDevIndex].pStruIPParaCfgV40[0].dwStartDChan -1;
		if (dwMaxChanNo % MAX_CHANNUM_V30 == 0)
		{
			dwMaxGroupNO = dwMaxChanNo/MAX_CHANNUM_V30;
		}
		else
		{
			dwMaxGroupNO = dwMaxChanNo/MAX_CHANNUM_V30 +1;
		}

		if (dwMaxGroupNoByAlarm > dwMaxGroupNO)
		{
			dwMaxGroupNO =dwMaxGroupNoByAlarm;
		}

		for (i =0; i< dwMaxGroupNO;i++)
		{
			sprintf(szLan,"Group%d",i+1);
			m_cmbGroupNo.AddString(szLan);
		}
	}

	m_cmbGroupNo.SetCurSel(0);
	DWORD dwGroupNo = m_cmbGroupNo.GetCurSel();
	g_CreateAlarmOutTreeByGroup(m_treeAlarmOut,m_iDevIndex, m_pbAlarmOut,dwGroupNo);
	g_CreateChannelTreeByGroup(m_treeChan, m_iDevIndex, m_pbRecordChan,dwGroupNo);

	OnSelchangeComPicType();

	OnBtnGetGuard();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgIPCPlateRecog::OnTimeOk2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    if (!F_TimeTest())
    {
        return;
    }
    int	i = m_comboWeekday.GetCurSel();	
	if (i == 7)
	{
		m_struGuardCfg.struHolidayTime[0].struSchedTime.byStartHour = (BYTE)m_iHour11;
		m_struGuardCfg.struHolidayTime[0].struSchedTime.byStartMin = (BYTE)m_iMin11;
		m_struGuardCfg.struHolidayTime[0].struSchedTime.byStopHour = (BYTE)m_iHour12;
		m_struGuardCfg.struHolidayTime[0].struSchedTime.byStopMin = (BYTE)m_iMin12;
		m_struGuardCfg.struHolidayTime[1].struSchedTime.byStartHour = (BYTE)m_iHour21;
		m_struGuardCfg.struHolidayTime[1].struSchedTime.byStartMin = (BYTE)m_iMin21;
		m_struGuardCfg.struHolidayTime[1].struSchedTime.byStopHour = (BYTE)m_iHour22;
		m_struGuardCfg.struHolidayTime[1].struSchedTime.byStopMin = (BYTE)m_iMin22;

		m_struGuardCfg.struHolidayTime[2].struSchedTime.byStartHour = (BYTE)m_iHour31;
		m_struGuardCfg.struHolidayTime[2].struSchedTime.byStartMin = (BYTE)m_iMin31;
		m_struGuardCfg.struHolidayTime[2].struSchedTime.byStopHour = (BYTE)m_iHour32;
		m_struGuardCfg.struHolidayTime[2].struSchedTime.byStopMin = (BYTE)m_iMin32;
		m_struGuardCfg.struHolidayTime[3].struSchedTime.byStartHour = (BYTE)m_iHour41;
		m_struGuardCfg.struHolidayTime[3].struSchedTime.byStartMin = (BYTE)m_iMin41;
		m_struGuardCfg.struHolidayTime[3].struSchedTime.byStopHour = (BYTE)m_iHour42;
		m_struGuardCfg.struHolidayTime[3].struSchedTime.byStopMin = (BYTE)m_iMin42;

		m_struGuardCfg.struHolidayTime[4].struSchedTime.byStartHour = (BYTE)m_iHour51;
		m_struGuardCfg.struHolidayTime[4].struSchedTime.byStartMin = (BYTE)m_iMin51;
		m_struGuardCfg.struHolidayTime[4].struSchedTime.byStopHour = (BYTE)m_iHour52;
		m_struGuardCfg.struHolidayTime[4].struSchedTime.byStopMin = (BYTE)m_iMin52;
		m_struGuardCfg.struHolidayTime[5].struSchedTime.byStartHour = (BYTE)m_iHour61;
		m_struGuardCfg.struHolidayTime[5].struSchedTime.byStartMin = (BYTE)m_iMin61;
		m_struGuardCfg.struHolidayTime[5].struSchedTime.byStopHour = (BYTE)m_iHour62;
		m_struGuardCfg.struHolidayTime[5].struSchedTime.byStopMin = (BYTE)m_iMin62;

		m_struGuardCfg.struHolidayTime[6].struSchedTime.byStartHour = (BYTE)m_iHour71;
		m_struGuardCfg.struHolidayTime[6].struSchedTime.byStartMin = (BYTE)m_iMin71;
		m_struGuardCfg.struHolidayTime[6].struSchedTime.byStopHour = (BYTE)m_iHour72;
		m_struGuardCfg.struHolidayTime[6].struSchedTime.byStopMin = (BYTE)m_iMin72;
		m_struGuardCfg.struHolidayTime[7].struSchedTime.byStartHour = (BYTE)m_iHour81;
		m_struGuardCfg.struHolidayTime[7].struSchedTime.byStartMin = (BYTE)m_iMin81;
		m_struGuardCfg.struHolidayTime[7].struSchedTime.byStopHour = (BYTE)m_iHour82;
		m_struGuardCfg.struHolidayTime[7].struSchedTime.byStopMin = (BYTE)m_iMin82;
	}
	else
	{
		GetAlarmTimeFromWnd(&m_struGuardCfg.struAlarmSched[0][0], i);
	}
	SceneIDToDlg(i, FALSE);
}

void CDlgIPCPlateRecog::OnTimeCopy2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    int j,k;
    int i = m_comboWeekday.GetCurSel();
    int m_nCopyTime = m_comboCopyTime.GetCurSel() - 1;
    
    if(m_nCopyTime == -1)
    {
        for(j=0; j<MAX_DAYS; j++)
        {
            if(j == i)
                continue;
            for(k=0; k<MAX_TIMESEGMENT_V30/*MAX_TIMESEGMENT_2*/; k++)
            {
                memcpy(&(m_struGuardCfg.struAlarmSched[j][k]), &(m_struGuardCfg.struAlarmSched[i][k]), sizeof(NET_DVR_TIME_DETECTION));
            }
        }
    }
	else if (i> -1 && i<7)
	{
		for(k=0; k<MAX_TIMESEGMENT_V30/*MAX_TIMESEGMENT_2*/; k++)
		{
			memcpy(&(m_struGuardCfg.struAlarmSched[m_nCopyTime][k]), &(m_struGuardCfg.struAlarmSched[i][k]), sizeof(NET_DVR_TIME_DETECTION));
		}
	}
	else
	{
		for(k=0; k<MAX_TIMESEGMENT_V30/*MAX_TIMESEGMENT_2*/; k++)
		{
			memcpy(&(m_struGuardCfg.struHolidayTime[k]), &(m_struGuardCfg.struAlarmSched[i][k]), sizeof(NET_DVR_TIME_DETECTION));
		}
	}
}

/*********************************************************
Function:	F_TimeTest
Desc:		Check Fortify time
Input:	
Output:	
Return:	BOOL
**********************************************************/
BOOL CDlgIPCPlateRecog::F_TimeTest()
{
	int i = 0;
	int j = 0;
	WORD wStartTime[MAX_TIMESEGMENT_V30], wStopTime[MAX_TIMESEGMENT_V30];
	char szLan[128] = {0};
	UpdateData(TRUE);
	if ((m_iHour11 < 0) || (m_iHour11 > 24) || (m_iHour12 < 0) || (m_iHour12 > 24) ||	\
		(m_iHour21 < 0) || (m_iHour21 > 24) || (m_iHour22 < 0) || (m_iHour22 > 24) ||	\
		(m_iHour31 < 0) || (m_iHour31 > 24) || (m_iHour32 < 0) || (m_iHour32 > 24) ||	\
		(m_iHour41 < 0) || (m_iHour41 > 24) || (m_iHour42 < 0) || (m_iHour42 > 24) ||   \
		(m_iHour51 < 0) || (m_iHour51 > 24) || (m_iHour52 < 0) || (m_iHour52 > 24) ||	\
		(m_iHour61 < 0) || (m_iHour61 > 24) || (m_iHour62 < 0) || (m_iHour62 > 24) ||	\
		(m_iHour71 < 0) || (m_iHour71 > 24) || (m_iHour72 < 0) || (m_iHour72 > 24) ||	\
		(m_iHour81 < 0) || (m_iHour81 > 24) || (m_iHour82 < 0) || (m_iHour82 > 24))
	{
		g_StringLanType(szLan, "小时范围在0 -- 24之间", "Hour between 0 - 24 ");
		AfxMessageBox(szLan);
		return FALSE;
	}
	if ((m_iMin11 < 0) || (m_iMin11 > 60) || (m_iMin12 < 0) || (m_iMin12 > 60) ||	\
		(m_iMin21 < 0) || (m_iMin21 > 60) || (m_iMin22 < 0) || (m_iMin22 > 60) ||	\
		(m_iMin31 < 0) || (m_iMin31 > 60) || (m_iMin32 < 0) || (m_iMin32 > 60) ||	\
		(m_iMin41 < 0) || (m_iMin41 > 60) || (m_iMin42 < 0) || (m_iMin42 > 60) ||   \
		(m_iMin51 < 0) || (m_iMin51 > 60) || (m_iMin52 < 0) || (m_iMin52 > 60) ||	\
		(m_iMin61 < 0) || (m_iMin61 > 60) || (m_iMin62 < 0) || (m_iMin62 > 60) ||	\
		(m_iMin71 < 0) || (m_iMin71 > 60) || (m_iMin72 < 0) || (m_iMin72 > 60) ||	\
		(m_iMin81 < 0) || (m_iMin81 > 60) || (m_iMin82 < 0) || (m_iMin82 > 60))
	{
		g_StringLanType(szLan, "分钟范围在0 -- 60之间", "Minute between 0 - 60 ");
		AfxMessageBox(szLan);
		return FALSE;
	}
	wStartTime[0] = (WORD)(m_iHour11 * 100 + m_iMin11);
	wStartTime[1] = (WORD)(m_iHour21 * 100 + m_iMin21);
	wStartTime[2] = (WORD)(m_iHour31 * 100 + m_iMin31);
	wStartTime[3] = (WORD)(m_iHour41 * 100 + m_iMin41);
	wStopTime[0] = (WORD)(m_iHour12 * 100 + m_iMin12);
	wStopTime[1] = (WORD)(m_iHour22 * 100 + m_iMin22);
	wStopTime[2] = (WORD)(m_iHour32 * 100 + m_iMin32);
	wStopTime[3] = (WORD)(m_iHour42 * 100 + m_iMin42);
	wStartTime[4] = (WORD)(m_iHour51 * 100 + m_iMin51);
	wStartTime[5] = (WORD)(m_iHour61 * 100 + m_iMin61);
	wStartTime[6] = (WORD)(m_iHour71 * 100 + m_iMin71);
	wStartTime[7] = (WORD)(m_iHour81 * 100 + m_iMin81);
	wStopTime[4] = (WORD)(m_iHour52 * 100 + m_iMin52);
	wStopTime[5] = (WORD)(m_iHour62 * 100 + m_iMin62);
	wStopTime[6] = (WORD)(m_iHour72 * 100 + m_iMin72);
	wStopTime[7] = (WORD)(m_iHour82 * 100 + m_iMin82);
	for (i = 0; i < MAX_TIMESEGMENT_V30; i++)
	{
		if ((wStartTime[i] > 2400) || (wStopTime[i] > 2400))
		{
			g_StringLanType(szLan, "布防时间不能超过24:00", "Fortify time can not be more than 24:00");
			AfxMessageBox(szLan);
			return FALSE;
		}
		if (wStartTime[i] > wStopTime[i])
		{
			g_StringLanType(szLan, "布防起始时间不能大于停止时间", "Fortify start time can not be larger than the record to stop time");
			AfxMessageBox(szLan);
			return FALSE;
		}
		for (j = 0; j < MAX_TIMESEGMENT_V30; j++)
		{
			if (i == j)
			{
				continue;
			}
			if ((wStartTime[i] > wStartTime[j]) && (wStartTime[i] < wStopTime[j]) ||	\
				(wStopTime[i] > wStartTime[j]) && (wStopTime[i] < wStopTime[j]))
			{
				g_StringLanType(szLan, "时间段不能重复", "time can not be repeated");
				AfxMessageBox(szLan);
				return FALSE;
			}
		}
	}
	return TRUE;
}

void CDlgIPCPlateRecog::SetAlarmTimeToWnd(NET_DVR_TIME_DETECTION const *pAlarmTime, int nDay)
{
    m_iHour11 = pAlarmTime[nDay*8+0].struSchedTime.byStartHour;
    m_iMin11 = pAlarmTime[nDay*8+0].struSchedTime.byStartMin;
    m_iHour12 = pAlarmTime[nDay*8+0].struSchedTime.byStopHour;
    m_iMin12 = pAlarmTime[nDay*8+0].struSchedTime.byStopMin;
    m_iHour21 = pAlarmTime[nDay*8+1].struSchedTime.byStartHour;
    m_iMin21 = pAlarmTime[nDay*8+1].struSchedTime.byStartMin;
    m_iHour22 = pAlarmTime[nDay*8+1].struSchedTime.byStopHour;
    m_iMin22 = pAlarmTime[nDay*8+1].struSchedTime.byStopMin;
	
	m_iHour31 = pAlarmTime[nDay*8+2].struSchedTime.byStartHour;
	m_iMin31 = pAlarmTime[nDay*8+2].struSchedTime.byStartMin;
	m_iHour32 = pAlarmTime[nDay*8+2].struSchedTime.byStopHour;
	m_iMin32 = pAlarmTime[nDay*8+2].struSchedTime.byStopMin;
	m_iHour41 = pAlarmTime[nDay*8+3].struSchedTime.byStartHour;
	m_iMin41 = pAlarmTime[nDay*8+3].struSchedTime.byStartMin;
	m_iHour42 = pAlarmTime[nDay*8+3].struSchedTime.byStopHour;
	m_iMin42 = pAlarmTime[nDay*8+3].struSchedTime.byStopMin;
	
	m_iHour51 = pAlarmTime[nDay*8+4].struSchedTime.byStartHour;
	m_iMin51 = pAlarmTime[nDay*8+4].struSchedTime.byStartMin;
	m_iHour52 = pAlarmTime[nDay*8+4].struSchedTime.byStopHour;
	m_iMin52 = pAlarmTime[nDay*8+4].struSchedTime.byStopMin;
	m_iHour61 = pAlarmTime[nDay*8+5].struSchedTime.byStartHour;
	m_iMin61 = pAlarmTime[nDay*8+5].struSchedTime.byStartMin;
	m_iHour62 = pAlarmTime[nDay*8+5].struSchedTime.byStopHour;
	m_iMin62 = pAlarmTime[nDay*8+5].struSchedTime.byStopMin;
	
	m_iHour71 = pAlarmTime[nDay*8+6].struSchedTime.byStartHour;
	m_iMin71 = pAlarmTime[nDay*8+6].struSchedTime.byStartMin;
	m_iHour72 = pAlarmTime[nDay*8+6].struSchedTime.byStopHour;
	m_iMin72 = pAlarmTime[nDay*8+6].struSchedTime.byStopMin;
	m_iHour81 = pAlarmTime[nDay*8+7].struSchedTime.byStartHour;
	m_iMin81 = pAlarmTime[nDay*8+7].struSchedTime.byStartMin;
	m_iHour82 = pAlarmTime[nDay*8+7].struSchedTime.byStopHour;
	m_iMin82 = pAlarmTime[nDay*8+7].struSchedTime.byStopMin;
}

void CDlgIPCPlateRecog::SceneIDToDlg(int nDay, BOOL bSceneToDlg)
{
	if (bSceneToDlg)
	{
		if (nDay == 7)
		{
			m_iSceneID1 = m_struGuardCfg.struHolidayTime[0].byDetSceneID;
			m_iSceneID2 = m_struGuardCfg.struHolidayTime[1].byDetSceneID;
			m_iSceneID3 = m_struGuardCfg.struHolidayTime[2].byDetSceneID;
			m_iSceneID4 = m_struGuardCfg.struHolidayTime[3].byDetSceneID;
			m_iSceneID5 = m_struGuardCfg.struHolidayTime[4].byDetSceneID;
			m_iSceneID6 = m_struGuardCfg.struHolidayTime[5].byDetSceneID;
			m_iSceneID7 = m_struGuardCfg.struHolidayTime[6].byDetSceneID;
			m_iSceneID8 = m_struGuardCfg.struHolidayTime[7].byDetSceneID;
		}
		else
		{
			m_iSceneID1 = m_struGuardCfg.struAlarmSched[nDay][0].byDetSceneID;
			m_iSceneID2 = m_struGuardCfg.struAlarmSched[nDay][1].byDetSceneID;
			m_iSceneID3 = m_struGuardCfg.struAlarmSched[nDay][2].byDetSceneID;
			m_iSceneID4 = m_struGuardCfg.struAlarmSched[nDay][3].byDetSceneID;
			m_iSceneID5 = m_struGuardCfg.struAlarmSched[nDay][4].byDetSceneID;
			m_iSceneID6 = m_struGuardCfg.struAlarmSched[nDay][5].byDetSceneID;
			m_iSceneID7 = m_struGuardCfg.struAlarmSched[nDay][6].byDetSceneID;
			m_iSceneID8 = m_struGuardCfg.struAlarmSched[nDay][7].byDetSceneID;
		}
	}
	else
	{
		if (nDay == 7)
		{
			m_struGuardCfg.struHolidayTime[0].byDetSceneID = m_iSceneID1;
			m_struGuardCfg.struHolidayTime[1].byDetSceneID = m_iSceneID2;
			m_struGuardCfg.struHolidayTime[2].byDetSceneID = m_iSceneID3;
			m_struGuardCfg.struHolidayTime[3].byDetSceneID = m_iSceneID4;
			m_struGuardCfg.struHolidayTime[4].byDetSceneID = m_iSceneID5;
			m_struGuardCfg.struHolidayTime[5].byDetSceneID = m_iSceneID6;
			m_struGuardCfg.struHolidayTime[6].byDetSceneID = m_iSceneID7;
			m_struGuardCfg.struHolidayTime[7].byDetSceneID = m_iSceneID8;
		}
		else
		{
			m_struGuardCfg.struAlarmSched[nDay][0].byDetSceneID = m_iSceneID1;
			m_struGuardCfg.struAlarmSched[nDay][1].byDetSceneID = m_iSceneID2;
			m_struGuardCfg.struAlarmSched[nDay][2].byDetSceneID = m_iSceneID3;
			m_struGuardCfg.struAlarmSched[nDay][3].byDetSceneID = m_iSceneID4;
			m_struGuardCfg.struAlarmSched[nDay][4].byDetSceneID = m_iSceneID5;
			m_struGuardCfg.struAlarmSched[nDay][5].byDetSceneID = m_iSceneID6;
			m_struGuardCfg.struAlarmSched[nDay][6].byDetSceneID = m_iSceneID7;
			m_struGuardCfg.struAlarmSched[nDay][7].byDetSceneID = m_iSceneID8;
		}
	}
}

void CDlgIPCPlateRecog::GetAlarmTimeFromWnd(NET_DVR_TIME_DETECTION *pAlarmTime, int nDay)
{
    pAlarmTime[nDay*8+0].struSchedTime.byStartHour = (BYTE)m_iHour11;
    pAlarmTime[nDay*8+0].struSchedTime.byStartMin = (BYTE)m_iMin11;
    pAlarmTime[nDay*8+0].struSchedTime.byStopHour = (BYTE)m_iHour12;
    pAlarmTime[nDay*8+0].struSchedTime.byStopMin = (BYTE)m_iMin12;
    pAlarmTime[nDay*8+1].struSchedTime.byStartHour = (BYTE)m_iHour21;
    pAlarmTime[nDay*8+1].struSchedTime.byStartMin = (BYTE)m_iMin21;
    pAlarmTime[nDay*8+1].struSchedTime.byStopHour = (BYTE)m_iHour22;
    pAlarmTime[nDay*8+1].struSchedTime.byStopMin = (BYTE)m_iMin22;
	
	pAlarmTime[nDay*8+2].struSchedTime.byStartHour = (BYTE)m_iHour31;
    pAlarmTime[nDay*8+2].struSchedTime.byStartMin = (BYTE)m_iMin31;
    pAlarmTime[nDay*8+2].struSchedTime.byStopHour = (BYTE)m_iHour32;
    pAlarmTime[nDay*8+2].struSchedTime.byStopMin = (BYTE)m_iMin32;
    pAlarmTime[nDay*8+3].struSchedTime.byStartHour = (BYTE)m_iHour41;
    pAlarmTime[nDay*8+3].struSchedTime.byStartMin = (BYTE)m_iMin41;
    pAlarmTime[nDay*8+3].struSchedTime.byStopHour = (BYTE)m_iHour42;
    pAlarmTime[nDay*8+3].struSchedTime.byStopMin = (BYTE)m_iMin42;
	
	pAlarmTime[nDay*8+4].struSchedTime.byStartHour = (BYTE)m_iHour51;
    pAlarmTime[nDay*8+4].struSchedTime.byStartMin = (BYTE)m_iMin51;
    pAlarmTime[nDay*8+4].struSchedTime.byStopHour = (BYTE)m_iHour52;
    pAlarmTime[nDay*8+4].struSchedTime.byStopMin = (BYTE)m_iMin52;
    pAlarmTime[nDay*8+5].struSchedTime.byStartHour = (BYTE)m_iHour61;
    pAlarmTime[nDay*8+5].struSchedTime.byStartMin = (BYTE)m_iMin61;
    pAlarmTime[nDay*8+5].struSchedTime.byStopHour = (BYTE)m_iHour62;
    pAlarmTime[nDay*8+5].struSchedTime.byStopMin = (BYTE)m_iMin62;
	
	pAlarmTime[nDay*8+6].struSchedTime.byStartHour = (BYTE)m_iHour71;
    pAlarmTime[nDay*8+6].struSchedTime.byStartMin = (BYTE)m_iMin71;
    pAlarmTime[nDay*8+6].struSchedTime.byStopHour = (BYTE)m_iHour72;
    pAlarmTime[nDay*8+6].struSchedTime.byStopMin = (BYTE)m_iMin72;
    pAlarmTime[nDay*8+7].struSchedTime.byStartHour = (BYTE)m_iHour81;
    pAlarmTime[nDay*8+7].struSchedTime.byStartMin = (BYTE)m_iMin81;
    pAlarmTime[nDay*8+7].struSchedTime.byStopHour = (BYTE)m_iHour82;
    pAlarmTime[nDay*8+7].struSchedTime.byStopMin = (BYTE)m_iMin82;
}

void CDlgIPCPlateRecog::SetGuardCond()
{
	UpdateData(TRUE);
	m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
	m_struGuardCond.dwSize = sizeof(m_struGuardCond);
	m_struGuardCond.dwChannel = m_lChannel;
	m_struGuardCond.byRelateType = m_comRelateType.GetCurSel() + 1;
	m_struGuardCond.byGroupNo = m_cmbGroupNo.GetCurSel();
}

void CDlgIPCPlateRecog::OnBtnSetGuard() 
{
	// TODO: Add your control notification handler code here

	char szLan[128] = {0};
	DWORD dwStatus = 0;

	SetGuardCond();
	
	m_struGuardCfg.dwSize = sizeof(m_struGuardCfg);
	m_struGuardCfg.struHandleException.dwHandleType = 0;
	if (m_bUploadCenter)
	{
		m_struGuardCfg.struHandleException.dwHandleType |= 0x04;
	}

	if (m_bFTP)
	{
		m_struGuardCfg.struHandleException.dwHandleType |= 0x200;
	}

    if (m_bCloud)
    {
        m_struGuardCfg.struHandleException.dwHandleType |= 0x1000;
    }

	if (m_bChkInvokeAlarmOut)
	{
		m_struGuardCfg.struHandleException.dwHandleType |= 0x08;
	}
	m_struGuardCfg.struHandleException.dwMaxRelAlarmOutChanNum = 1;
	m_struGuardCfg.struHandleException.dwRelAlarmOutChanNum = 0;

	GetRelateChanInfo(m_struGuardCond.byGroupNo);

	//报警输出通道
	int j = 0;
	for (int i=0; i < MAX_CHANNUM_V30; i++)
	{
		if (m_pbAlarmOut[i])
		{
			m_struGuardCfg.struHandleException.dwRelAlarmOut[j] = i+1;
			m_struGuardCfg.struHandleException.dwRelAlarmOutChanNum++;
			j++;
		}	
	}
    m_struGuardCfg.byDirection = m_comEventTriggerDirection.GetCurSel();
	BOOL bRet = NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_GUARDCFG, 1, &m_struGuardCond, sizeof(m_struGuardCond), \
		&dwStatus, &m_struGuardCfg, (sizeof(m_struGuardCfg)));	
	if (bRet)
	{
		if (dwStatus != 0)
		{
			sprintf(szLan,"错误状态返回值:%d",dwStatus);
			AfxMessageBox(szLan);
		}
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_GUARDCFG Success");
	}
	else
	{        
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_GUARDCFG Fail");
	}
}


void CDlgIPCPlateRecog::OnBtnGetGuard() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	DWORD dwStatus = 0;
	
	SetGuardCond();
	
    if (!NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_GUARDCFG, 1, &m_struGuardCond, sizeof(m_struGuardCond),\
		&dwStatus, &m_struGuardCfg, sizeof(m_struGuardCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_GUARDCFG Fail");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_GUARDCFG Success");
    }
	
	m_bMonitor = (m_struGuardCfg.struHandleException.dwHandleType >> 0)&0x01;
    m_bVoice =  (m_struGuardCfg.struHandleException.dwHandleType >> 1)&0x01;
    m_bUploadCenter = (m_struGuardCfg.struHandleException.dwHandleType >> 2)&0x01;
    m_bInvokeAlarmOut = (m_struGuardCfg.struHandleException.dwHandleType >> 3)&0x01;
    m_bJepgCap = (m_struGuardCfg.struHandleException.dwHandleType >> 4)&0x01;
    m_bEMap = (m_struGuardCfg.struHandleException.dwHandleType >> 6)&0x01;
    m_bFTP = (m_struGuardCfg.struHandleException.dwHandleType >> 9)&0x01;
    m_bCloud = (m_struGuardCfg.struHandleException.dwHandleType >> 12) & 0x01;
//	m_bChkInvokeAlarmOut = (m_struGuardCfg.struHandleException.dwHandleType >>3)&0x01;

	m_treeAlarmOut.EnableWindow(m_bChkInvokeAlarmOut);

	int nDay = 0;
	m_comboWeekday.SetCurSel(0);
	
	SetAlarmTimeToWnd(&m_struGuardCfg.struAlarmSched[0][0], nDay);
	SceneIDToDlg(nDay, TRUE);
	//CreateTree();
	UpdateRelateChanInfo();
	DWORD dwGroupNo = m_cmbGroupNo.GetCurSel();
	g_CreateAlarmOutTreeByGroup(m_treeAlarmOut,m_iDevIndex, m_pbAlarmOut,dwGroupNo);
	g_CreateChannelTreeByGroup(m_treeChan, m_iDevIndex, m_pbRecordChan,dwGroupNo);

    m_comEventTriggerDirection.SetCurSel(m_struGuardCfg.byDirection);

    UpdateData(FALSE);	
}

void CDlgIPCPlateRecog::OnSelchangeComboweekday() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    int	nDay = m_comboWeekday.GetCurSel();	
	if (nDay == 7)
	{
		m_iHour11 = m_struGuardCfg.struHolidayTime[0].struSchedTime.byStartHour;
		m_iMin11 = m_struGuardCfg.struHolidayTime[0].struSchedTime.byStartMin;
		m_iHour12 = m_struGuardCfg.struHolidayTime[0].struSchedTime.byStopHour;
		m_iMin12 = m_struGuardCfg.struHolidayTime[0].struSchedTime.byStopMin;
		m_iHour21 = m_struGuardCfg.struHolidayTime[1].struSchedTime.byStartHour;
		m_iMin21 = m_struGuardCfg.struHolidayTime[1].struSchedTime.byStartMin;
		m_iHour22 = m_struGuardCfg.struHolidayTime[1].struSchedTime.byStopHour;
		m_iMin22 = m_struGuardCfg.struHolidayTime[1].struSchedTime.byStopMin;

		m_iHour31 = m_struGuardCfg.struHolidayTime[2].struSchedTime.byStartHour;
		m_iMin31 = m_struGuardCfg.struHolidayTime[2].struSchedTime.byStartMin;
		m_iHour32 = m_struGuardCfg.struHolidayTime[2].struSchedTime.byStopHour;
		m_iMin32 = m_struGuardCfg.struHolidayTime[2].struSchedTime.byStopMin;
		m_iHour41 = m_struGuardCfg.struHolidayTime[3].struSchedTime.byStartHour;
		m_iMin41 = m_struGuardCfg.struHolidayTime[3].struSchedTime.byStartMin;
		m_iHour42 = m_struGuardCfg.struHolidayTime[3].struSchedTime.byStopHour;
		m_iMin42 = m_struGuardCfg.struHolidayTime[3].struSchedTime.byStopMin;

		m_iHour51 = m_struGuardCfg.struHolidayTime[4].struSchedTime.byStartHour;
		m_iMin51 = m_struGuardCfg.struHolidayTime[4].struSchedTime.byStartMin;
		m_iHour52 = m_struGuardCfg.struHolidayTime[4].struSchedTime.byStopHour;
		m_iMin52 = m_struGuardCfg.struHolidayTime[4].struSchedTime.byStopMin;
		m_iHour61 = m_struGuardCfg.struHolidayTime[5].struSchedTime.byStartHour;
		m_iMin61 = m_struGuardCfg.struHolidayTime[5].struSchedTime.byStartMin;
		m_iHour62 = m_struGuardCfg.struHolidayTime[5].struSchedTime.byStopHour;
		m_iMin62 = m_struGuardCfg.struHolidayTime[5].struSchedTime.byStopMin;

		m_iHour71 = m_struGuardCfg.struHolidayTime[6].struSchedTime.byStartHour;
		m_iMin71 = m_struGuardCfg.struHolidayTime[6].struSchedTime.byStartMin;
		m_iHour72 = m_struGuardCfg.struHolidayTime[6].struSchedTime.byStopHour;
		m_iMin72 = m_struGuardCfg.struHolidayTime[6].struSchedTime.byStopMin;
		m_iHour81 = m_struGuardCfg.struHolidayTime[7].struSchedTime.byStartHour;
		m_iMin81 = m_struGuardCfg.struHolidayTime[7].struSchedTime.byStartMin;
		m_iHour82 = m_struGuardCfg.struHolidayTime[7].struSchedTime.byStopHour;
		m_iMin82 = m_struGuardCfg.struHolidayTime[7].struSchedTime.byStopMin;

	}
	else
	{
		SetAlarmTimeToWnd(&m_struGuardCfg.struAlarmSched[0][0], nDay);
	}
	SceneIDToDlg(nDay, TRUE);
    UpdateData(FALSE);
}

void CDlgIPCPlateRecog::OnBtnGetPicInfo() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
	NET_DVR_SNAPINFOCFG struPicInfo;
	memset(&struPicInfo, 0, sizeof(struPicInfo));
    struPicInfo.dwSize = sizeof(struPicInfo);
	DWORD dwReturn = 0;

	 m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
//     if ((g_struDeviceInfo[m_iDevIndex].bySupport7 & 0x02) != 0x02)
//     {
// 	    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_SNAPINFO_CFG, m_lChannel, &struPicInfo, sizeof(struPicInfo), &dwReturn))
//         {
//             g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SNAPINFO_CFG");
//         }
//         else
//         {
//             g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SNAPINFO_CFG");
//             return;
//         }
//     }
//     else
    {
        NET_DVR_SNAPINFO_COND struPicCond = {0};
        struPicCond.dwSize = sizeof(NET_DVR_SNAPINFO_COND);
        struPicCond.byRelateType = m_comPicRelateType.GetCurSel();
        struPicCond.dwChan = m_lChannel;

        DWORD dwStatus = 0;
        if (!NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_SNAPINFO_CFG_V40, 1, &struPicCond, sizeof(struPicCond),
            &dwStatus,&struPicInfo, sizeof(struPicInfo)))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SNAPINFO_CFG_V40 Chan[%d]", m_lChannel);
            return;
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SNAPINFO_CFG_V40 Chan[%d]", m_lChannel);
        }

    }

	m_dwPicSize = struPicInfo.dwPicSize;
	m_byPicQuality = struPicInfo.byPicQuality;
	m_comPicType.SetCurSel(struPicInfo.byCurPicType);
	OnSelchangeComPicType();
	UpdateData(FALSE);
}

void CDlgIPCPlateRecog::OnBtnSetPicInfo() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_SNAPINFOCFG struPicInfo;
	memset(&struPicInfo, 0, sizeof(struPicInfo));
	struPicInfo.dwSize = sizeof(struPicInfo);
	struPicInfo.dwPicSize = m_dwPicSize;
	struPicInfo.byPicQuality = m_byPicQuality;
	struPicInfo.byCurPicType = m_comPicType.GetCurSel();
	m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());

//     if ((g_struDeviceInfo[m_iDevIndex].bySupport7 & 0x02) != 0x02)
//     {
// 	    if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_SNAPINFO_CFG, m_lChannel, &struPicInfo, sizeof(struPicInfo)))
//         {
//             g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SNAPINFO_CFG");
//         }
//         else
//         {
//             g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SNAPINFO_CFG ErrCode:%d", NET_DVR_GetLastError());
//             return;
//         }
//     }
//     else
    {
        NET_DVR_SNAPINFO_COND struPicCond = {0};
        struPicCond.dwSize = sizeof(NET_DVR_SNAPINFO_COND);
        struPicCond.byRelateType = m_comPicRelateType.GetCurSel();
        struPicCond.dwChan = m_lChannel;
        
        DWORD dwStatus = 0;
        if (!NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_SNAPINFO_CFG_V40, 1, &struPicCond, sizeof(struPicCond),
            &dwStatus,&struPicInfo, sizeof(struPicInfo)))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SNAPINFO_CFG_V40 Chan[%d]", m_lChannel);
            return;
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SNAPINFO_CFG_V40 Chan[%d]", m_lChannel);
        }
    }
}

void CDlgIPCPlateRecog::OnBtnTriggerexCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaITCTriggerCfg dlg;
	dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel = m_lChannel;
    dlg.DoModal();
}

void CDlgIPCPlateRecog::OnBtnOverlapCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgITSOverlapCfg dlg;
	dlg.m_lServerID = m_lServerID;			
	dlg.m_iDevIndex = m_iDevIndex;			
	dlg.m_lChannel = m_lChannel;
	dlg.DoModal();
}

void CDlgIPCPlateRecog::OnBtnIpcChanCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgITSIpcCfg dlg;
	dlg.m_lServerID = m_lServerID;			
	dlg.m_iDevIndex = m_iDevIndex;			
	dlg.m_lChannel = m_lChannel;
	dlg.DoModal();
}

void CDlgIPCPlateRecog::OnBtnManualSnapPlate() 
{
	// TODO: Add your control notification handler code here
	CDlgManualSnap dlg;
	dlg.m_lServerID = m_lServerID;			
	dlg.m_iDevIndex = m_iDevIndex;			
	dlg.m_lChannel = m_lChannel;
	dlg.DoModal();
}

void CDlgIPCPlateRecog::OnBtnCloudStorageCfg()
{
	CDlgCloudStorageCfg dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.DoModal();
}

void CDlgIPCPlateRecog::OnSelchangeComPicType()
{
	int i = m_comPicType.GetCurSel();
	if (0 == i)
	{
		GetDlgItem(IDC_EDIT_PIC_SIZE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PIC_QUALITY)->EnableWindow(TRUE); 

	} 
	else
	{
		GetDlgItem(IDC_EDIT_PIC_SIZE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PIC_QUALITY)->EnableWindow(FALSE); 
	}
}

void CDlgIPCPlateRecog::OnBtnCompleteRestore()
{

	NET_DVR_COMPLETE_RESTORE_INFO m_struRestoreInfo = {0};
	m_struRestoreInfo.dwSize = sizeof(NET_DVR_COMPLETE_RESTORE_INFO);
	m_struRestoreInfo.dwChannel = m_lChannel;
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_COMPLETE_RESTORE_CTRL, &m_struRestoreInfo, sizeof(NET_DVR_COMPLETE_RESTORE_INFO)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_COMPLETE_RESTORE_CTRL ");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_COMPLETE_RESTORE_CTRL");
	}
}

void CDlgIPCPlateRecog::CreateTree()
{
	g_CreateAlarmOutTree(m_treeAlarmOut, m_iDevIndex, m_pbAlarmOut);
}

void CDlgIPCPlateRecog::OnChkInvokeAlarmOut() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_treeAlarmOut.EnableWindow(m_bChkInvokeAlarmOut);
}

void CDlgIPCPlateRecog::OnClickTreeTriggerAlarmOut(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CPoint pt(0,0);
	CRect rc(0,0,0,0);
	GetCursorPos(&pt);
	GetDlgItem(IDC_TREE_TRIGGER_ALARM_OUT)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	ScreenToClient(&pt);
	pt.x = pt.x - rc.left;
	pt.y = pt.y - rc.top;
	
	UINT uFlag = 0;
	HTREEITEM hSelect = m_treeAlarmOut.HitTest(pt, &uFlag);
	
	if (NULL == hSelect) 
	{
		return;
	}
	m_treeAlarmOut.SelectItem(hSelect);
	DWORD dwIndex = m_treeAlarmOut.GetItemData(hSelect)%1000;
	
	BOOL bCheck = m_treeAlarmOut.GetCheck(hSelect);
	if (!bCheck)	
	{
		m_pbAlarmOut[dwIndex] = 1;
	}
	else
	{
		m_pbAlarmOut[dwIndex] = 0;
	}
	
	//switch checkbox status on click
	if (uFlag != LVHT_TOLEFT)
	{
		m_treeAlarmOut.SetCheck(hSelect, !bCheck);
	}
	else
	{
		m_treeAlarmOut.SetCheck(hSelect, bCheck);
	}

	*pResult = 0;
}

void CDlgIPCPlateRecog::OnClickTreeRecordchan(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    CPoint pt(0,0);
    CRect rc(0,0,0,0);
    GetCursorPos(&pt);
    GetDlgItem(IDC_TREE_RECORDCHAN)->GetWindowRect(&rc);
    ScreenToClient(&rc);
    ScreenToClient(&pt);
    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;
    
    UINT uFlag = 0;
    HTREEITEM hSelect = m_treeChan.HitTest(pt, &uFlag);
    
    if (NULL == hSelect) 
    {
        return;
    }
    m_treeChan.SelectItem(hSelect);
    DWORD dwIndex = m_treeChan.GetItemData(hSelect)%1000;
    BOOL bCheck = m_treeChan.GetCheck(hSelect);
    if (!bCheck)
    {
        m_pbRecordChan[dwIndex] = 1;
    }
    else
    {
        m_pbRecordChan[dwIndex] = 0;
    }
    
    //switch checkbox status on click
    if (uFlag != LVHT_TOLEFT)
    {
        m_treeChan.SetCheck(hSelect, !bCheck);
    }
    else
    {
        m_treeChan.SetCheck(hSelect, bCheck);
    }
    
	*pResult = 0;
}

void CDlgIPCPlateRecog::UpdateRelateChanInfo()
{
	char szLan[128] = {0};
	int i = 0;
	memset(m_pbRecordChan,0,sizeof(DWORD)*MAX_CHANNUM_V40);

	for (i = 0; i< m_struGuardCfg.dwRelRecordChanNum && i < MAX_CHANNUM_V30;i++)
	{
		if (m_struGuardCfg.dwRelRecordChan[i]  == 0xffffffff)
		{
			break;
		}
		else if (m_struGuardCfg.dwRelRecordChan[i] > 0 &&m_struGuardCfg.dwRelRecordChan[i] < MAX_CHANNUM_V40)
		{
			m_pbRecordChan[m_struGuardCfg.dwRelRecordChan[i] - 1] =1;
		}
		else
		{
			sprintf(szLan,"Relate Record Chan Exception Index[%d] Value[%d]",i,m_struGuardCfg.dwRelRecordChan[i]);
			AfxMessageBox(szLan);
			break;
		}
	}

	memset(m_pbAlarmOut,0,sizeof(DWORD)*MAX_ALARMOUT_V40);
	for (i = 0; i< m_struGuardCfg.struHandleException.dwRelAlarmOutChanNum && i < MAX_CHANNUM_V30;i++)
	{
		if (m_struGuardCfg.struHandleException.dwRelAlarmOut[i]  == 0xffffffff)
		{
			break;
		}
		else if (m_struGuardCfg.struHandleException.dwRelAlarmOut[i] < MAX_ALARMOUT_V40)
		{
			m_pbAlarmOut[m_struGuardCfg.struHandleException.dwRelAlarmOut[i]-1] =1;
		}
		else
		{
			sprintf(szLan,"Relate Alarmout Chan Exception Index[%d] Value[%d]",i,m_struGuardCfg.dwRelRecordChan[i]);
			AfxMessageBox(szLan);
			break;
		}
	}
}

void CDlgIPCPlateRecog::GetRelateChanInfo(DWORD dwGroupNo)
{
	UpdateData(TRUE);
	char szLan[128] = {0};
	int i = 0;
	memset(m_struGuardCfg.dwRelRecordChan,0xff,sizeof(DWORD)*MAX_CHANNUM_V30);
	m_struGuardCfg.dwRelRecordChanNum = 0;
	for (i = 0; i< MAX_CHANNUM_V30;i++)
	{
		if (m_struGuardCfg.dwRelRecordChanNum  == MAX_CHANNUM_V30)
		{
			sprintf(szLan,"Relate Record Chan Exception Index[%d]",i);
			AfxMessageBox(szLan);
			break;
		}

		if (m_pbRecordChan[i+dwGroupNo*MAX_CHANNUM_V30] == 1)
		{
			m_struGuardCfg.dwRelRecordChan[m_struGuardCfg.dwRelRecordChanNum++] = i+1+dwGroupNo*MAX_CHANNUM_V30;
		}

	}

	memset(m_struGuardCfg.struHandleException.dwRelAlarmOut,0xff,sizeof(DWORD)*MAX_CHANNUM_V30);
	m_struGuardCfg.struHandleException.dwRelAlarmOutChanNum = 0;
	for (i = 0; i < MAX_CHANNUM_V30;i++)
	{
		if (m_struGuardCfg.dwRelRecordChanNum  == MAX_CHANNUM_V30)
		{
			sprintf(szLan,"Relate Alarmout Chan Alarmout Index[%d]",i);
			AfxMessageBox(szLan);
			break;
		}

		if (m_pbAlarmOut[i+dwGroupNo*MAX_CHANNUM_V30] == 1)
		{
			m_struGuardCfg.struHandleException.dwRelAlarmOut[m_struGuardCfg.struHandleException.dwRelAlarmOutChanNum++] = i +1+dwGroupNo*MAX_CHANNUM_V30;  
		}
	}
}

void CDlgIPCPlateRecog::OnSelchangeComboGroup() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwGroupNo = m_cmbGroupNo.GetCurSel();
	OnBtnGetGuard();
	g_CreateAlarmOutTreeByGroup(m_treeAlarmOut,m_iDevIndex, m_pbAlarmOut,dwGroupNo);
	g_CreateChannelTreeByGroup(m_treeChan, m_iDevIndex, m_pbRecordChan,dwGroupNo);

	UpdateData(FALSE);
}

void CDlgIPCPlateRecog::OnBnClickedButtonTrigger()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    char szUrl[256] = { 0 };

    m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    if (m_bLane)
    {
        sprintf(szUrl, "GET /ISAPI/Traffic/channels/%d/vehicleDetect/manualTrigger/%s\r\n", m_lChannel, m_strLaneID);
    }
    else
    {
        sprintf(szUrl, "GET /ISAPI/Traffic/channels/%d/vehicleDetect/manualTrigger\r\n", m_lChannel);
    }

    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    DWORD dwOutputLen = 1024 * 1024 * 10;
    char *pOutBuf = new char[dwOutputLen];
    memset(pOutBuf, 0, dwOutputLen);
    struOuput.lpOutBuffer = pOutBuf;
    struOuput.dwOutBufferSize = dwOutputLen;

    if (!NET_DVR_STDXMLConfig(m_lServerID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, szUrl);
        delete[]pOutBuf;
        pOutBuf = NULL;
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, szUrl);
    }

    char *mfd = pOutBuf;
    DWORD dwBufLen = struOuput.dwReturnedXMLSize;
    char* boundary = get_boundary(pOutBuf);
    int contentLen = 0;
    int offsetLen = 0;
    int i = 0;
    while (1) {
        char *type, *content;
        mfd = mutipart_form_data(mfd, boundary, &type, &content, (dwBufLen - offsetLen), contentLen, offsetLen);
        if (mfd == NULL) {
            break;
        }

        SYSTEMTIME t;
        GetLocalTime(&t);
        char chTime[128];
        sprintf(chTime, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d%3.3d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);

        char cFilename[256] = { 0 };
        sprintf(cFilename, "%s\\%s_%d.%s", g_struLocalParam.chPictureSavePath, chTime, i, type);

        HANDLE hFile = CreateFile(cFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return;
        }
        DWORD dwWrittenBytes = 0;
        DWORD dwRet = WriteFile(hFile, content, contentLen, &dwWrittenBytes, NULL);
        if (dwRet == 0 || dwWrittenBytes < contentLen)
        {
            DWORD dwError = GetLastError();
            //g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Face Snap Json Info Wtite to File Fail.System Error:%d, dwJsonDataLen:%d, WrittenBytes:%d ", dwError, struFaceSnap.dwJsonDataLen, dwWrittenBytes);
        }
        CloseHandle(hFile);
        hFile = NULL;

        free(type);
        free(content);
        if (mfd == NULL) {
            break;
            i = 0;
        }
        i++;
    }

    if (pOutBuf != NULL)
    {
        delete[]pOutBuf;
        pOutBuf = NULL;
    }

    if (boundary != NULL)
    {
        delete[] boundary;
        boundary = NULL;
    }

    UpdateData(FALSE);
    return;
}
