// DlgJpegCaptureCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgJpegCaptureCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgJpegCaptureCfg dialog

CDlgJpegCaptureCfg::CDlgJpegCaptureCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgJpegCaptureCfg::IDD, pParent)
	, m_bCheckAllDay(FALSE)
	, m_iHour11(0)
	, m_iMin11(0)
	, m_iHour12(0)
	, m_iMin12(0)
	, m_iHour21(0)
	, m_iMin21(0)
	, m_iHour22(0)
	, m_iMin22(0)
	, m_iHour31(0)
	, m_iMin31(0)
	, m_iHour32(0)
	, m_iMin32(0)
	, m_iHour41(0)
	, m_iMin41(0)
	, m_iHour42(0)
	, m_iMin42(0)
	, m_iHour51(0)
	, m_iMin51(0)
	, m_iHour52(0)
	, m_iMin52(0)
	, m_iHour61(0)
	, m_iMin61(0)
	, m_iHour62(0)
	, m_iMin62(0)
	, m_iHour71(0)
	, m_iMin71(0)
	, m_iHour72(0)
	, m_iMin72(0)
	, m_iHour81(0)
	, m_iMin81(0)
	, m_iHour82(0)
	, m_iMin82(0)
	, m_pCompresscfgAbility(NULL)
	, m_lFtpServerTest(-1)
{
	//{{AFX_DATA_INIT(CDlgJpegCaptureCfg)
	m_dwIntervalEvent = 0;
	m_dwIntrvalTime = 0;
	m_bEnableCapture = FALSE;
	m_dwPicSaveDays = 0;
	m_csIP = _T("");
	m_dwPort = 0;
	m_csPassword = _T("");
	m_csUserName = _T("");
	m_csIP2 = _T("");
	m_dwPort2 = 0;
	m_csPassword2 = _T("");
	m_csUserName2 = _T("");
	m_byEventCapTimes = 0;
	m_bChkAnony = FALSE;
	m_csMainFirstUserDir = _T("");
	m_csMainSecordUserDir = _T("");
	m_bChkAnony2 = FALSE;
	m_csSubFirstUserDir = _T("");
	m_csSubSecordUserDir = _T("");
	m_csIPv6 = _T("");
	m_csIP2v6 = _T("");
	m_bFTPPicType = FALSE;
	m_bFTPPicType2 = FALSE;
	m_Delimiter = _T("");
	m_Delimiter2 = _T("");
	m_byPicArchivingInterval = 0;
	m_byPicArchivingInterval2 = 0;
	m_csPicNamePrefix = _T("");
	m_csPicNamePrefix2 = _T("");
	//}}AFX_DATA_INIT
    m_lUserID = -1;
    m_lChannelNum = -1;
	m_iChanShowNO = -1;
    m_lChannel = -1;
	m_iChanCount = 0;
	m_dwDevIndex = 0;
   // memset(&m_pStruJpegCapture, 0, sizeof(m_pStruJpegCapture));
    memset(&m_struCaptureSched, 0, sizeof(m_struCaptureSched));
	memset(&m_strFtpCfg, 0, sizeof(m_strFtpCfg));
	m_pCompresscfgAbility = new NET_DVR_COMPRESSIONCFG_ABILITY;
	memset(m_pCompresscfgAbility, 0, sizeof(NET_DVR_COMPRESSIONCFG_ABILITY));
	memset(&m_struFtpServerTest, 0, sizeof(m_struFtpServerTest));

	m_pStruJpegCapture = new NET_DVR_JPEG_CAPTURE_CFG_V40;
    m_dwCurAlarmInChanNum = 0;
    m_dwCurEventChanNum = 0;
	
    m_pbAlarmInChan = new BOOL[MAX_CHANNUM_V40];
    if(m_pbAlarmInChan != NULL)
    {
        memset(m_pbAlarmInChan,0,sizeof(BOOL)*MAX_CHANNUM_V40);
		
    }
    m_pbEventChan = new BOOL[MAX_CHANNUM_V40];
    if (m_pbEventChan != NULL)
    {
        memset(m_pbEventChan,0, sizeof(BOOL)*MAX_CHANNUM_V40);
    }
}

CDlgJpegCaptureCfg::~CDlgJpegCaptureCfg()
{
    if (m_pCompresscfgAbility != NULL)
    {
        delete m_pCompresscfgAbility;
        m_pCompresscfgAbility = NULL;
    }
    if (m_pStruJpegCapture != NULL)
    {
        delete m_pStruJpegCapture;
        m_pStruJpegCapture = NULL;
    }
	
    if (m_pbAlarmInChan != NULL)
    {
        delete [] m_pbAlarmInChan;
        m_pbAlarmInChan = NULL;
    }
	
    if (m_pbEventChan != NULL)
    {
        delete[] m_pbEventChan;
        m_pbEventChan = NULL;
    }
}

void CDlgJpegCaptureCfg::GetResolutionAbility()
{
    for (int nAbilityCount = 0; nAbilityCount < m_pCompresscfgAbility->dwAbilityNum; nAbilityCount++)
    {
        if (MAIN_RESOLUTION_ABILITY == m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwAbilityType)
        {
            m_comboTimePicResolution.ResetContent();
			m_comboEventPicResolution.ResetContent();
            for (int i = 0; i < m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum; i++)
            {
				m_comboTimePicResolution.AddString((char*)m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_comboTimePicResolution.SetItemData(i, m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].iValue);

                m_comboEventPicResolution.AddString((char*)m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_comboEventPicResolution.SetItemData(i, m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].iValue);
            }
            m_comboTimePicResolution.AddString("2560*1440");
            m_comboTimePicResolution.SetItemData(m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum, 70);

            m_comboTimePicResolution.AddString("3072*1728");
            m_comboTimePicResolution.SetItemData(m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum + 1, 66);

            m_comboTimePicResolution.AddString("4096*2160");
            m_comboTimePicResolution.SetItemData(m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum + 2, 63);

            m_comboTimePicResolution.AddString("3840*2160");
            m_comboTimePicResolution.SetItemData(m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum + 3, 64);

            m_comboEventPicResolution.AddString("2560*1440");
            m_comboEventPicResolution.SetItemData(m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum, 70);

            m_comboEventPicResolution.AddString("3072*1728");
            m_comboEventPicResolution.SetItemData(m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum + 1, 66);

            m_comboEventPicResolution.AddString("4096*2160");
            m_comboEventPicResolution.SetItemData(m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum + 2, 63);

            m_comboEventPicResolution.AddString("3840*2160");
            m_comboEventPicResolution.SetItemData(m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum + 3, 64);
        }
    }
}

void CDlgJpegCaptureCfg::SetTimeResolutionCurSel(DWORD dwData)
{
    for (int i = 0; i < m_comboTimePicResolution.GetCount(); i++)
    {
        if (m_comboTimePicResolution.GetItemData(i) == dwData)
        {
            m_comboTimePicResolution.SetCurSel(i);
            return;
        }
    }
}

void CDlgJpegCaptureCfg::SetEventResolutionCurSel(DWORD dwData)
{
    for (int i = 0; i < m_comboEventPicResolution.GetCount(); i++)
    {
        if (m_comboEventPicResolution.GetItemData(i) == dwData)
        {
            m_comboEventPicResolution.SetCurSel(i);
            return;
        }
    }
}

BOOL CDlgJpegCaptureCfg::GetCompressCfgAbility(DWORD dwIPChanIndex)
{
    if (!NET_DVR_GetDeviceAbility(m_lUserID, PIC_CAPTURE_ABILITY, (char*)&dwIPChanIndex, sizeof(dwIPChanIndex), (char*)m_pCompresscfgAbility, sizeof(NET_DVR_COMPRESSIONCFG_ABILITY)))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "PIC_CAPTURE_ABILITY");
        return FALSE;    
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "PIC_CAPTURE_ABILITY");
        return TRUE;
    }
}

/*********************************************************
Function:	TimeTest
Desc:		check time settings
Input:	
Output:	
Return:	TRUE,correct schedule;FALSE,incorrect schedule;
**********************************************************/
BOOL CDlgJpegCaptureCfg::TimeTest()
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

void CDlgJpegCaptureCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgJpegCaptureCfg)
	DDX_Control(pDX, IDC_COMBO_PICRULE_TYPE2, m_comPicRuleType2);
	DDX_Control(pDX, IDC_COMBO_PICRULE_TYPE, m_comPicRuleType);
	DDX_Control(pDX, IDC_COMBO_STREAM_TYPE, m_comStreamType);
	DDX_Control(pDX, IDC_COMBONAMEITEM_FTP2, m_NameItemCtrl2);
	DDX_Control(pDX, IDC_COMBONAMEITEM_FTP, m_NameItemCtrl);
	DDX_Control(pDX, IDC_COMBONAMEELEMENT_FTP2, m_NameElementCtrl2);
	DDX_Control(pDX, IDC_COMBONAMEELEMENT_FTP, m_NameElementCtrl);
	DDX_Control(pDX, IDC_COMBO_PROTOCALTYPE2, m_comboProtocalType2);
	DDX_Control(pDX, IDC_COMBO_SERVERTYPE2, m_comboServerType2);
	DDX_Control(pDX, IDC_COMBO_SERVERTYPE, m_comboServerType);
	DDX_Control(pDX, IDC_COMBO_PROTOCALTYPE, m_comboProtocalType);
	DDX_Control(pDX, IDC_COMBOUSEFTPUP2, m_UseFTPUpCtrl2);
	DDX_Control(pDX, IDC_COMBO_SUB_SECORD_DIRMODE, m_comboSubSecordDirModeCtrl);
	DDX_Control(pDX, IDC_COMBO_SUB_FIRST_DIRMODE, m_comboSubFirstDirModeCtr);
	DDX_Control(pDX, IDC_COMBO_SECORD_DIRMODE, m_comboMainSecordDirModeCtrl);
	DDX_Control(pDX, IDC_COMBO_FIRST_DIRMODE, m_comboMainFirstDirModeCtr);
	DDX_Control(pDX, IDC_COMBO_SUB_DIR_LEVEL, m_DirLevelCtrl2);
	DDX_Control(pDX, IDC_COMBO_DIR_LEVEL, m_DirLevelCtrl);
	DDX_Control(pDX, IDC_COMBOUSEFTPUP, m_UseFTPUpCtrl);
	DDX_Control(pDX, IDC_TREE_EVENT, m_treeEvent);
	DDX_Control(pDX, IDC_TREE_ALARMIN, m_treeAlarmin);
	DDX_Control(pDX, IDC_COMBO_ALARM_IN, m_comboAlarmIn);
	DDX_Control(pDX, IDC_COMBO_OTHER_EVENT, m_comboEvent);
	DDX_Control(pDX, IDC_COMBO_TIME_PIC_RESOLUTION, m_comboTimePicResolution);
	DDX_Control(pDX, IDC_COMBO_TIME_PIC_QUALITY, m_comboTimePicQuality);
	DDX_Control(pDX, IDC_COMBO_CAPTURE_INTERVAL_EVENT, m_comboIntervalEvent);
	DDX_Control(pDX, IDC_COMBO_CAPTURE_INTERVAL_TIME, m_comboIntervalTime);
	DDX_Control(pDX, IDC_COMBO_EVENT_PIC_RESOLUTION, m_comboEventPicResolution);
	DDX_Control(pDX, IDC_COMBO_EVENT_PIC_QUALITY, m_comboEventPicQuality);
	DDX_Text(pDX, IDC_EDIT_CAPTURE_INTERVAL_EVENT, m_dwIntervalEvent);
	DDX_Text(pDX, IDC_EDIT_CAPTURE_INTERVAL_TIME, m_dwIntrvalTime);
	DDX_Control(pDX, IDC_COMBO_WEEK_DAY, m_comboWeekday);
	DDX_Check(pDX, IDC_CHK_ALL_DAY, m_bCheckAllDay);
	DDX_Control(pDX, IDC_COMBO_ALL_DAY_TYPE, m_comboAllDayType);
	DDX_Text(pDX, IDC_EDIT_HOUR11, m_iHour11);
	DDX_Text(pDX, IDC_EDIT_MIN11, m_iMin11);
	DDX_Text(pDX, IDC_EDIT_HOUR12, m_iHour12);
	DDX_Text(pDX, IDC_EDIT_MIN12, m_iMin12);
	DDX_Text(pDX, IDC_EDIT_HOUR21, m_iHour21);
	DDX_Text(pDX, IDC_EDIT_MIN21, m_iMin21);
	DDX_Text(pDX, IDC_EDIT_HOUR22, m_iHour22);
	DDX_Text(pDX, IDC_EDIT_MIN22, m_iMin22);
	DDX_Text(pDX, IDC_EDIT_HOUR31, m_iHour31);
	DDX_Text(pDX, IDC_EDIT_MIN31, m_iMin31);
	DDX_Text(pDX, IDC_EDIT_HOUR32, m_iHour32);
	DDX_Text(pDX, IDC_EDIT_MIN32, m_iMin32);
	DDX_Text(pDX, IDC_EDIT_HOUR41, m_iHour41);
	DDX_Text(pDX, IDC_EDIT_MIN41, m_iMin41);
	DDX_Text(pDX, IDC_EDIT_HOUR42, m_iHour42);
	DDX_Text(pDX, IDC_EDIT_MIN42, m_iMin42);
	DDX_Text(pDX, IDC_EDIT_HOUR51, m_iHour51);
	DDX_Text(pDX, IDC_EDIT_MIN51, m_iMin51);
	DDX_Text(pDX, IDC_EDIT_HOUR52, m_iHour52);
	DDX_Text(pDX, IDC_EDIT_MIN52, m_iMin52);
	DDX_Text(pDX, IDC_EDIT_HOUR61, m_iHour61);
	DDX_Text(pDX, IDC_EDIT_MIN61, m_iMin61);
	DDX_Text(pDX, IDC_EDIT_HOUR62, m_iHour62);
	DDX_Text(pDX, IDC_EDIT_MIN62, m_iMin62);
	DDX_Text(pDX, IDC_EDIT_HOUR71, m_iHour71);
	DDX_Text(pDX, IDC_EDIT_MIN71, m_iMin71);
	DDX_Text(pDX, IDC_EDIT_HOUR72, m_iHour72);
	DDX_Text(pDX, IDC_EDIT_MIN72, m_iMin72);
	DDX_Text(pDX, IDC_EDIT_HOUR81, m_iHour81);
	DDX_Text(pDX, IDC_EDIT_MIN81, m_iMin81);
	DDX_Text(pDX, IDC_EDIT_HOUR82, m_iHour82);
	DDX_Text(pDX, IDC_EDIT_MIN82, m_iMin82);
	DDX_Control(pDX, IDC_COMBO_TIME_REC_TYPE1, m_comboTimeRecType1);
	DDX_Control(pDX, IDC_COMBO_TIME_REC_TYPE2, m_comboTimeRecType2);
	DDX_Control(pDX, IDC_COMBO_TIME_REC_TYPE3, m_comboTimeRecType3);
	DDX_Control(pDX, IDC_COMBO_TIME_REC_TYPE4, m_comboTimeRecType4);
	DDX_Control(pDX, IDC_COMBO_COPY_WEEKDAY, m_comboCopyWeekday);
	DDX_Control(pDX, IDC_COMBO_TIME_REC_TYPE5, m_comboTimeRecType5);
	DDX_Control(pDX, IDC_COMBO_TIME_REC_TYPE6, m_comboTimeRecType6);
	DDX_Control(pDX, IDC_COMBO_TIME_REC_TYPE7, m_comboTimeRecType7);
	DDX_Control(pDX, IDC_COMBO_TIME_REC_TYPE8, m_comboTimeRecType8);
	DDX_Check(pDX, IDC_CHK_ENABLE_CAPTURE, m_bEnableCapture);
	DDX_Text(pDX, IDC_EDIT_PICTURE_SAVE_DAYS, m_dwPicSaveDays);
	DDX_Text(pDX, IDC_EDIT_IP, m_csIP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_dwPort);
	DDX_Text(pDX, IDC_EDIT_PSWD, m_csPassword);
	DDX_Text(pDX, IDC_EDIT_USER, m_csUserName);
	DDX_Text(pDX, IDC_EDIT_IP2, m_csIP2);
	DDX_Text(pDX, IDC_EDIT_PORT2, m_dwPort2);
	DDX_Text(pDX, IDC_EDIT_PSWD2, m_csPassword2);
	DDX_Text(pDX, IDC_EDIT_USER2, m_csUserName2);
	DDX_Text(pDX, IDC_EDIT_EVENT_CAPTIMES, m_byEventCapTimes);
	DDX_Check(pDX, IDC_CHK_ANONY_ENABLE, m_bChkAnony);
	DDX_Text(pDX, IDC_EDIT_FIRST_USERDIR, m_csMainFirstUserDir);
	DDX_Text(pDX, IDC_EDIT_SECOND_USERDIR, m_csMainSecordUserDir);
	DDX_Check(pDX, IDC_CHK_ANONY_ENABLE_2, m_bChkAnony2);
	DDX_Text(pDX, IDC_EDIT_SUB_FIRST_USERDIR, m_csSubFirstUserDir);
	DDX_Text(pDX, IDC_EDIT_SUB_SECOND_USERDIR, m_csSubSecordUserDir);
	DDX_Text(pDX, IDC_EDIT_IPV6_FIRST, m_csIPv6);
	DDX_Text(pDX, IDC_EDIT_IP2V6, m_csIP2v6);
	DDX_Check(pDX, IDC_CHECK_PICTYPE, m_bFTPPicType);
	DDX_Check(pDX, IDC_CHECK_PICTYPE2, m_bFTPPicType2);
	DDX_Text(pDX, IDC_EDITDELIMITER, m_Delimiter);
	DDX_Text(pDX, IDC_EDITDELIMITER2, m_Delimiter2);
	DDX_Text(pDX, IDC_EDIT_PIC_ARCHIVING_INTERVAL, m_byPicArchivingInterval);
	DDX_Text(pDX, IDC_EDIT_PIC_ARCHIVING_INTERVAL2, m_byPicArchivingInterval2);
	DDX_Text(pDX, IDC_PICNAME_PREFIX, m_csPicNamePrefix);
	DDX_Text(pDX, IDC_PICNAME_PREFIX2, m_csPicNamePrefix2);
	//}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMBO_DELAY_TIME, m_comboDelayTime);
}


BEGIN_MESSAGE_MAP(CDlgJpegCaptureCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgJpegCaptureCfg)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_IN, OnSelchangeComboAlarmIn)
	ON_CBN_SELCHANGE(IDC_COMBO_OTHER_EVENT, OnSelchangeComboOtherEvent)
	ON_NOTIFY(NM_CLICK, IDC_TREE_ALARMIN, OnClickTreeAlarmin)
	ON_NOTIFY(NM_CLICK, IDC_TREE_EVENT, OnClickTreeEvent)
	ON_BN_CLICKED(IDC_BTN_SET_JPEG_CAPTURE, OnBtnSetJpegCapture)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_CAPTURE_DAY_OK, OnCaptureDayOk)
	ON_CBN_SELCHANGE(IDC_COMBO_WEEKDAY, OnSelchangeComboWeekday)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_SCHED, OnButtonUpdateSched)
	ON_BN_CLICKED(IDC_BTN_SET_JPEG_CAPTURE_SCHED, OnBtnSetJpegCaptureSched)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_FTP, OnButtonUpdateFtp)
	ON_CBN_SELCHANGE(IDC_COMBO_DIR_LEVEL, OnSelchangeComboDirLevel)
	ON_CBN_SELCHANGE(IDC_COMBO_SUB_DIR_LEVEL, OnSelchangeComboSubDirLevel)
	ON_CBN_SELCHANGE(IDC_COMBO_FIRST_DIRMODE, OnSelchangeComboDirModeOne)
	ON_CBN_SELCHANGE(IDC_COMBO_SECORD_DIRMODE, OnSelchangeComboDirModeTwo)
	ON_CBN_SELCHANGE(IDC_COMBO_SUB_FIRST_DIRMODE, OnSelchangeSubComboDirModeOne)
	ON_CBN_SELCHANGE(IDC_COMBO_SUB_SECORD_DIRMODE, OnSelchangeSubComboDirModeTwo)	
	ON_BN_CLICKED(IDC_BTN_SET_FTP, OnBtnSetFtp)
	ON_BN_CLICKED(IDC_BTN_DAY_COPY, OnBtnDayCopy)
	ON_BN_CLICKED(IDC_CHK_ALL_DAY, OnChkAllDay)
	ON_BN_CLICKED(IDC_BUTTON_ALARMIN_ALL, OnButtonAlarminAll)
	ON_BN_CLICKED(IDC_BUTTON_ALARMIN_CLEAN, OnButtonAlarminClean)
	ON_BN_CLICKED(IDC_BUTTON_EVENT_ALL, OnButtonEventAll)
	ON_BN_CLICKED(IDC_BUTTON_EVENT_CLEAN, OnButtonEventClean)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_FTP2, OnButtonUpdateFtp2)
	ON_BN_CLICKED(IDC_BTN_SET_FTP2, OnBtnSetFtp2)
	ON_CBN_EDITCHANGE(IDC_COMBO_SERVERTYPE2, OnEditchangeComboServertype2)
	ON_CBN_EDITCHANGE(IDC_COMBO_SERVERTYPE, OnEditchangeComboServertype)
	ON_CBN_SELCHANGE(IDC_COMBO_SERVERTYPE, OnSelchangeComboServertype)
	ON_CBN_SELCHANGE(IDC_COMBO_SERVERTYPE2, OnSelchangeComboServertype2)
	ON_BN_CLICKED(IDC_BUTJPEGNAME, OnButjpegname)
	ON_BN_CLICKED(IDC_BUTJPEGNAME2, OnButjpegname2)
	ON_CBN_SELCHANGE(IDC_COMBONAMEITEM_FTP, OnSelchangeCombonameitemFtp)
	ON_CBN_SELCHANGE(IDC_COMBONAMEITEM_FTP2, OnSelchangeCombonameitemFtp2)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_FTP_SERVER_TEST, OnBtnFtpServerTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////
//CDlgJpegCaptureCfg messagehandlers

BOOL CDlgJpegCaptureCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	char szLan[128] = {0};

	//add alarmin chan
	m_comboAlarmIn.ResetContent();    
	m_comboAlarmIn.AddString("AlarmIn1");
	m_comboAlarmIn.SetCurSel(0);
    m_comboDelayTime.SetCurSel(0);

	//add other event type
    m_comboEvent.ResetContent();    
    g_StringLanType(szLan, "移动侦测", "Motion");
    m_comboEvent.AddString(szLan);
    g_StringLanType(szLan, "视频遮挡", "Hide");
    m_comboEvent.AddString(szLan);
	g_StringLanType(szLan, "视频丢失", "Lost");
    m_comboEvent.AddString(szLan);
	g_StringLanType(szLan, "PIR报警", "PIR");
    m_comboEvent.AddString(szLan);
	g_StringLanType(szLan, "无线报警", "Wireless");
    m_comboEvent.AddString(szLan);
	g_StringLanType(szLan, "呼救报警", "Call help");
    m_comboEvent.AddString(szLan);
	g_StringLanType(szLan, "智能报警", "VCA");
    m_comboEvent.AddString(szLan);
	g_StringLanType(szLan, "人脸侦测报警", "Face Detect");
    m_comboEvent.AddString(szLan);
	g_StringLanType(szLan, "越界侦测", "Overstep Detect");
    m_comboEvent.AddString(szLan);
	g_StringLanType(szLan, "入侵侦测", "Invade Detect");
    m_comboEvent.AddString(szLan);
	g_StringLanType(szLan, "场景变更侦测", "Scene Change Detect");//2013-07-17场景变更侦测抓图
    m_comboEvent.AddString(szLan);
    g_StringLanType(szLan, "进入区域侦测", "Enter the region detection");
    m_comboEvent.AddString(szLan);
    g_StringLanType(szLan, "离开区域侦测", "Leave the region detection");
    m_comboEvent.AddString(szLan);
    g_StringLanType(szLan, "徘徊侦测", "Hovering detection");
    m_comboEvent.AddString(szLan);
    g_StringLanType(szLan, "人员聚集侦测", "Researchers gathered detection");
    m_comboEvent.AddString(szLan);
    g_StringLanType(szLan, "快速运动侦测", "Fast motion detection");
    m_comboEvent.AddString(szLan);
    g_StringLanType(szLan, "停车侦测", "Parking detection");
    m_comboEvent.AddString(szLan);
    g_StringLanType(szLan, "物品遗留侦测", "Goods Legacy Detection");
    m_comboEvent.AddString(szLan);
    g_StringLanType(szLan, "物品拿取侦测", "Goods Take Detection");
    m_comboEvent.AddString(szLan);
	m_comboEvent.SetCurSel(0);

	m_comboTimePicResolution.ResetContent();
    m_comboTimePicResolution.AddString("CIF");
    m_comboTimePicResolution.SetItemData(0, 0);
    m_comboTimePicResolution.AddString("QCIF");
    m_comboTimePicResolution.SetItemData(1, 1);
    m_comboTimePicResolution.AddString("D1");
    m_comboTimePicResolution.SetItemData(2, 2);
	m_comboTimePicResolution.SetCurSel(0);

    m_comboEventPicResolution.ResetContent();
    m_comboEventPicResolution.AddString("CIF");
    m_comboEventPicResolution.SetItemData(0, 0);
    m_comboEventPicResolution.AddString("QCIF");
    m_comboEventPicResolution.SetItemData(1, 1);
    m_comboEventPicResolution.AddString("D1");
    m_comboEventPicResolution.SetItemData(2, 2);
	m_comboEventPicResolution.SetCurSel(0);

	if (GetCompressCfgAbility(m_iChanShowNO))
	{
		GetResolutionAbility();
	}

	m_comboEventPicQuality.ResetContent();
	m_comboTimePicQuality.ResetContent();
	g_StringLanType(szLan, "最好", "Best");
	m_comboEventPicQuality.AddString(szLan);    
    m_comboTimePicQuality.AddString(szLan);
	g_StringLanType(szLan, "较好", "Better");
    m_comboEventPicQuality.AddString(szLan);
    m_comboTimePicQuality.AddString(szLan);
	g_StringLanType(szLan, "一般", "Normal");
    m_comboEventPicQuality.AddString(szLan);
    m_comboTimePicQuality.AddString(szLan);
	m_comboEventPicQuality.SetCurSel(0);
	m_comboTimePicQuality.SetCurSel(0);	
	m_comboIntervalEvent.SetCurSel(1);
	m_comboIntervalTime.SetCurSel(1);
	m_comboWeekday.SetCurSel(0);
	m_comboCopyWeekday.SetCurSel(0);

    int nIndex = 0;
    int nCaptureType = 0;
    m_comboAllDayType.ResetContent();
    m_comboTimeRecType1.ResetContent();
    m_comboTimeRecType2.ResetContent();
    m_comboTimeRecType3.ResetContent();
    m_comboTimeRecType4.ResetContent();
    m_comboTimeRecType5.ResetContent();
    m_comboTimeRecType6.ResetContent();
    m_comboTimeRecType7.ResetContent();
    m_comboTimeRecType8.ResetContent();

    g_StringLanType(szLan, "定时抓图", "Timing");
    m_comboAllDayType.InsertString(nIndex, szLan);
    m_comboAllDayType.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType1.InsertString(nIndex, szLan);
    m_comboTimeRecType1.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType2.InsertString(nIndex, szLan);
    m_comboTimeRecType2.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType3.InsertString(nIndex, szLan);
    m_comboTimeRecType3.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType4.InsertString(nIndex, szLan);
    m_comboTimeRecType4.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType5.InsertString(nIndex, szLan);
    m_comboTimeRecType5.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType6.InsertString(nIndex, szLan);
    m_comboTimeRecType6.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType7.InsertString(nIndex, szLan);
    m_comboTimeRecType7.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType8.InsertString(nIndex, szLan);
    m_comboTimeRecType8.SetItemData(nIndex, nCaptureType);
    nIndex++;

    nCaptureType = 1;
    g_StringLanType(szLan, "移动侦测抓图", "Motion");
    m_comboAllDayType.InsertString(nIndex, szLan);
    m_comboAllDayType.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType1.InsertString(nIndex, szLan);
    m_comboTimeRecType1.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType2.InsertString(nIndex, szLan);
    m_comboTimeRecType2.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType3.InsertString(nIndex, szLan);
    m_comboTimeRecType3.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType4.InsertString(nIndex, szLan);
    m_comboTimeRecType4.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType5.InsertString(nIndex, szLan);
    m_comboTimeRecType5.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType6.InsertString(nIndex, szLan);
    m_comboTimeRecType6.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType7.InsertString(nIndex, szLan);
    m_comboTimeRecType7.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType8.InsertString(nIndex, szLan);
    m_comboTimeRecType8.SetItemData(nIndex, nCaptureType);
    nIndex++;

    nCaptureType = 2;
    g_StringLanType(szLan, "报警抓图", "Alarm");
    m_comboAllDayType.InsertString(nIndex, szLan);
    m_comboAllDayType.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType1.InsertString(nIndex, szLan);
    m_comboTimeRecType1.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType2.InsertString(nIndex, szLan);
    m_comboTimeRecType2.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType3.InsertString(nIndex, szLan);
    m_comboTimeRecType3.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType4.InsertString(nIndex, szLan);
    m_comboTimeRecType4.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType5.InsertString(nIndex, szLan);
    m_comboTimeRecType5.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType6.InsertString(nIndex, szLan);
    m_comboTimeRecType6.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType7.InsertString(nIndex, szLan);
    m_comboTimeRecType7.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType8.InsertString(nIndex, szLan);
    m_comboTimeRecType8.SetItemData(nIndex, nCaptureType);
    nIndex++;

    nCaptureType = 3;
    g_StringLanType(szLan, "移动侦测|报警抓图", "Motion or Alarm");
    m_comboAllDayType.InsertString(nIndex, szLan);
    m_comboAllDayType.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType1.InsertString(nIndex, szLan);
    m_comboTimeRecType1.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType2.InsertString(nIndex, szLan);
    m_comboTimeRecType2.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType3.InsertString(nIndex, szLan);
    m_comboTimeRecType3.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType4.InsertString(nIndex, szLan);
    m_comboTimeRecType4.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType5.InsertString(nIndex, szLan);
    m_comboTimeRecType5.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType6.InsertString(nIndex, szLan);
    m_comboTimeRecType6.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType7.InsertString(nIndex, szLan);
    m_comboTimeRecType7.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType8.InsertString(nIndex, szLan);
    m_comboTimeRecType8.SetItemData(nIndex, nCaptureType);
    nIndex++;

    nCaptureType = 4;
    g_StringLanType(szLan, "移动侦测&报警抓图", "Motion and Alarm");
    m_comboAllDayType.InsertString(nIndex, szLan);
    m_comboAllDayType.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType1.InsertString(nIndex, szLan);
    m_comboTimeRecType1.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType2.InsertString(nIndex, szLan);
    m_comboTimeRecType2.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType3.InsertString(nIndex, szLan);
    m_comboTimeRecType3.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType4.InsertString(nIndex, szLan);
    m_comboTimeRecType4.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType5.InsertString(nIndex, szLan);
    m_comboTimeRecType5.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType6.InsertString(nIndex, szLan);
    m_comboTimeRecType6.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType7.InsertString(nIndex, szLan);
    m_comboTimeRecType7.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType8.InsertString(nIndex, szLan);
    m_comboTimeRecType8.SetItemData(nIndex, nCaptureType);
    nIndex++;

    nCaptureType = 5;
    g_StringLanType(szLan, "命令触发抓图", "Command");
    m_comboAllDayType.InsertString(nIndex, szLan);
    m_comboAllDayType.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType1.InsertString(nIndex, szLan);
    m_comboTimeRecType1.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType2.InsertString(nIndex, szLan);
    m_comboTimeRecType2.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType3.InsertString(nIndex, szLan);
    m_comboTimeRecType3.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType4.InsertString(nIndex, szLan);
    m_comboTimeRecType4.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType5.InsertString(nIndex, szLan);
    m_comboTimeRecType5.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType6.InsertString(nIndex, szLan);
    m_comboTimeRecType6.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType7.InsertString(nIndex, szLan);
    m_comboTimeRecType7.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType8.InsertString(nIndex, szLan);
    m_comboTimeRecType8.SetItemData(nIndex, nCaptureType);
    nIndex++;

    nCaptureType = 6;
    g_StringLanType(szLan, "智能抓图", "VCA");
    m_comboAllDayType.InsertString(nIndex, szLan);
    m_comboAllDayType.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType1.InsertString(nIndex, szLan);
    m_comboTimeRecType1.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType2.InsertString(nIndex, szLan);
    m_comboTimeRecType2.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType3.InsertString(nIndex, szLan);
    m_comboTimeRecType3.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType4.InsertString(nIndex, szLan);
    m_comboTimeRecType4.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType5.InsertString(nIndex, szLan);
    m_comboTimeRecType5.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType6.InsertString(nIndex, szLan);
    m_comboTimeRecType6.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType7.InsertString(nIndex, szLan);
    m_comboTimeRecType7.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType8.InsertString(nIndex, szLan);
    m_comboTimeRecType8.SetItemData(nIndex, nCaptureType);
    nIndex++;

    nCaptureType = 7;
    g_StringLanType(szLan, "智能侦测抓图", "Intelligent detection");
    m_comboAllDayType.InsertString(nIndex, szLan);
    m_comboAllDayType.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType1.InsertString(nIndex, szLan);
    m_comboTimeRecType1.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType2.InsertString(nIndex, szLan);
    m_comboTimeRecType2.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType3.InsertString(nIndex, szLan);
    m_comboTimeRecType3.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType4.InsertString(nIndex, szLan);
    m_comboTimeRecType4.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType5.InsertString(nIndex, szLan);
    m_comboTimeRecType5.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType6.InsertString(nIndex, szLan);
    m_comboTimeRecType6.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType7.InsertString(nIndex, szLan);
    m_comboTimeRecType7.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType8.InsertString(nIndex, szLan);
    m_comboTimeRecType8.SetItemData(nIndex, nCaptureType);
    nIndex++;

    nCaptureType = 8;
    g_StringLanType(szLan, "所有事件抓图", "All");
    m_comboAllDayType.InsertString(nIndex, szLan);
    m_comboAllDayType.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType1.InsertString(nIndex, szLan);
    m_comboTimeRecType1.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType2.InsertString(nIndex, szLan);
    m_comboTimeRecType2.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType3.InsertString(nIndex, szLan);
    m_comboTimeRecType3.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType4.InsertString(nIndex, szLan);
    m_comboTimeRecType4.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType5.InsertString(nIndex, szLan);
    m_comboTimeRecType5.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType6.InsertString(nIndex, szLan);
    m_comboTimeRecType6.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType7.InsertString(nIndex, szLan);
    m_comboTimeRecType7.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType8.InsertString(nIndex, szLan);
    m_comboTimeRecType8.SetItemData(nIndex, nCaptureType);
    nIndex++;

    nCaptureType = 39;
    g_StringLanType(szLan, "离线测温抓图", "OffLine Thermometry");
    m_comboAllDayType.InsertString(nIndex, szLan);
    m_comboAllDayType.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType1.InsertString(nIndex, szLan);
    m_comboTimeRecType1.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType2.InsertString(nIndex, szLan);
    m_comboTimeRecType2.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType3.InsertString(nIndex, szLan);
    m_comboTimeRecType3.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType4.InsertString(nIndex, szLan);
    m_comboTimeRecType4.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType5.InsertString(nIndex, szLan);
    m_comboTimeRecType5.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType6.InsertString(nIndex, szLan);
    m_comboTimeRecType6.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType7.InsertString(nIndex, szLan);
    m_comboTimeRecType7.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType8.InsertString(nIndex, szLan);
    m_comboTimeRecType8.SetItemData(nIndex, nCaptureType);
    nIndex++;

    nCaptureType = 40;
    g_StringLanType(szLan, "防区报警", "AlarmIN Alarm");
    m_comboAllDayType.InsertString(nIndex, szLan);
    m_comboAllDayType.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType1.InsertString(nIndex, szLan);
    m_comboTimeRecType1.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType2.InsertString(nIndex, szLan);
    m_comboTimeRecType2.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType3.InsertString(nIndex, szLan);
    m_comboTimeRecType3.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType4.InsertString(nIndex, szLan);
    m_comboTimeRecType4.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType5.InsertString(nIndex, szLan);
    m_comboTimeRecType5.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType6.InsertString(nIndex, szLan);
    m_comboTimeRecType6.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType7.InsertString(nIndex, szLan);
    m_comboTimeRecType7.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType8.InsertString(nIndex, szLan);
    m_comboTimeRecType8.SetItemData(nIndex, nCaptureType);
    nIndex++;

    nCaptureType = 41;
    g_StringLanType(szLan, "紧急求助", "Emergency Call Help");
    m_comboAllDayType.InsertString(nIndex, szLan);
    m_comboAllDayType.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType1.InsertString(nIndex, szLan);
    m_comboTimeRecType1.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType2.InsertString(nIndex, szLan);
    m_comboTimeRecType2.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType3.InsertString(nIndex, szLan);
    m_comboTimeRecType3.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType4.InsertString(nIndex, szLan);
    m_comboTimeRecType4.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType5.InsertString(nIndex, szLan);
    m_comboTimeRecType5.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType6.InsertString(nIndex, szLan);
    m_comboTimeRecType6.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType7.InsertString(nIndex, szLan);
    m_comboTimeRecType7.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType8.InsertString(nIndex, szLan);
    m_comboTimeRecType8.SetItemData(nIndex, nCaptureType);
    nIndex++;

    nCaptureType = 42;
    g_StringLanType(szLan, "业务咨询", "Consult");
    m_comboAllDayType.InsertString(nIndex, szLan);
    m_comboAllDayType.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType1.InsertString(nIndex, szLan);
    m_comboTimeRecType1.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType2.InsertString(nIndex, szLan);
    m_comboTimeRecType2.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType3.InsertString(nIndex, szLan);
    m_comboTimeRecType3.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType4.InsertString(nIndex, szLan);
    m_comboTimeRecType4.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType5.InsertString(nIndex, szLan);
    m_comboTimeRecType5.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType6.InsertString(nIndex, szLan);
    m_comboTimeRecType6.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType7.InsertString(nIndex, szLan);
    m_comboTimeRecType7.SetItemData(nIndex, nCaptureType);
    m_comboTimeRecType8.InsertString(nIndex, szLan);
    m_comboTimeRecType8.SetItemData(nIndex, nCaptureType);
    nIndex++;

	OnButtonUpdateSched();
	OnButtonUpdate();
	OnButtonUpdateSched();
	OnButtonUpdateFtp();
	//OnButtonUpdateFtp2();
	OnButtonUpdate();
	return TRUE;
}

/*********************************************************
Function:	EnableControl
Desc:		Dialog control enable
Input:	
Output:	
Return:	
	**********************************************************/
void CDlgJpegCaptureCfg::EnableControl(BOOL bEnable)
{
	GetDlgItem(IDC_EDIT_HOUR11)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR21)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR31)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR41)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR51)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR61)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR71)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR81)->EnableWindow(bEnable);
	
	GetDlgItem(IDC_EDIT_MIN11)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN21)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN31)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN41)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN51)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN61)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN71)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN81)->EnableWindow(bEnable);
	
	GetDlgItem(IDC_EDIT_HOUR12)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR22)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR32)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR42)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR52)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR62)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR72)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR82)->EnableWindow(bEnable);
	
	GetDlgItem(IDC_EDIT_MIN12)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN22)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN32)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN42)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN52)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN62)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN72)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN82)->EnableWindow(bEnable);
	
	GetDlgItem(IDC_COMBO_TIME_REC_TYPE1)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_TIME_REC_TYPE2)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_TIME_REC_TYPE3)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_TIME_REC_TYPE4)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_TIME_REC_TYPE5)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_TIME_REC_TYPE6)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_TIME_REC_TYPE7)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_TIME_REC_TYPE8)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_ALL_DAY_TYPE)->EnableWindow(!bEnable);
}

void CDlgJpegCaptureCfg::OnButtonUpdate() 
{
	DWORD dwBytesReturned = 0;

	NET_DVR_CHANNEL_GROUP struChanGroup = {0};
	
    struChanGroup.dwSize = sizeof(NET_DVR_CHANNEL_GROUP);
    struChanGroup.dwChannel = m_lChannel;
    struChanGroup.dwGroup = 0;
	
    if (m_pStruJpegCapture == NULL)
    {
        return;
    }
	
	
    memset(m_pStruJpegCapture, 0, sizeof(NET_DVR_JPEG_CAPTURE_CFG_V40));
	
	
    DWORD dwListStatus = 0;

	if(!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_JPEG_CAPTURE_CFG_V40,0, &struChanGroup,sizeof(struChanGroup),&dwListStatus,\
        m_pStruJpegCapture, sizeof(*m_pStruJpegCapture)) || dwListStatus > 0)
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_GET_JPEG_CAPTURE_CFG_V40", m_lChannel);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "chan[%d] NET_DVR_GET_JPEG_CAPTURE_CFG", m_lChannel);
		m_comboTimePicQuality.SetCurSel(m_pStruJpegCapture->struTimingCapture.struJpegPara.wPicQuality);
		SetTimeResolutionCurSel(m_pStruJpegCapture->struTimingCapture.struJpegPara.wPicSize);
		SetEventResolutionCurSel(m_pStruJpegCapture->struEventCapture.struJpegPara.wPicSize);
		m_comboEventPicQuality.SetCurSel(m_pStruJpegCapture->struEventCapture.struJpegPara.wPicQuality);
		m_dwIntrvalTime = m_pStruJpegCapture->struTimingCapture.dwPicInterval;
		m_dwIntervalEvent = m_pStruJpegCapture->struEventCapture.dwPicInterval;
	//	m_comboIntervalEvent.SetCurSel(m_struJpegCapture.struEventCapture.dwPicInterval - 1);
	//	m_comboIntervalTime.SetCurSel(m_struJpegCapture.struTimingCapture.dwPicInterval - 1);
		m_byEventCapTimes = m_pStruJpegCapture->struEventCapture.byCapTimes;
        m_comStreamType.SetCurSel(m_pStruJpegCapture->byStreamType);
		OnSelchangeComboAlarmIn();
		OnSelchangeComboOtherEvent();
	}
	UpdateData(FALSE);
}

void CDlgJpegCaptureCfg::OnSelchangeComboAlarmIn() 
{
	int iIndex = m_comboAlarmIn.GetCurSel();
	CreateChanTreeAlarmIn(iIndex);
}

void CDlgJpegCaptureCfg::OnSelchangeComboOtherEvent() 
{
	int iIndex = m_comboEvent.GetCurSel();
	CreateChanTreeEvent(iIndex);
}

void CDlgJpegCaptureCfg::CreateChanTreeAlarmIn(int iIndex, BOOL bSetAll, BOOL bClearAll)
{
	//create channel tree
	m_treeAlarmin.DeleteAllItems();
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0,k = 0;
	HTREEITEM hChanItem = NULL;
	if (m_iChanCount <= 0)
	{
		m_treeAlarmin.EnableWindow(FALSE);
	}
	
	memset(m_pbAlarmInChan, 0, sizeof(BOOL)* MAX_CHANNUM_V40);
    for (i = 0; i < MAX_CHANNUM_V40; i++)
    {
        if (m_pStruJpegCapture->struEventCapture.struAlarmInCapture[iIndex].dwChanNo[i] != 0xffffffff)
        {
            m_pbAlarmInChan[m_pStruJpegCapture->struEventCapture.struAlarmInCapture[iIndex].dwChanNo[i] -1] = 1; 
        }
        
    }

	for (i = 0; i < MAX_CHANNUM_V40; i++)
	{
		if ((i < m_iChanCount) && g_struDeviceInfo[m_dwDevIndex].pStruChanInfo[i].bEnable)
		{
			strTemp.Format(ANALOG_C_FORMAT, i+g_struDeviceInfo[m_dwDevIndex].iStartChan);
			hChanItem =  m_treeAlarmin.InsertItem(strTemp, 0, 0, TVI_ROOT);
			m_treeAlarmin.SetItemData(hChanItem, 0*1000 + i);
			if(bSetAll)
			{
				//m_pStruJpegCapture->struEventCapture.struAlarmInCapture[iIndex].byChan[i/8] |= (0x01<<(i%8));
				m_pStruJpegCapture->struEventCapture.struAlarmInCapture[iIndex].dwChanNo[k++] =  (i + 1);

			}
			if(bClearAll)
			{
				m_pStruJpegCapture->struEventCapture.struAlarmInCapture[iIndex].dwChanNo[k++] =  0xffffffff;

//				m_pStruJpegCapture->struEventCapture.struAlarmInCapture[iIndex].byChan[i/8] = 0;
			}
			if(m_pStruJpegCapture->struEventCapture.struAlarmInCapture[iIndex].dwChanNo[i] != 0xffffffff)
			{
		        m_treeAlarmin.SetCheck(hChanItem, TRUE);

			}
		}
		else if (i >= MAX_ANALOG_CHANNUM && g_struDeviceInfo[m_dwDevIndex].pStruChanInfo[i].bEnable)
		{
			if(bSetAll)
			{
				m_pStruJpegCapture->struEventCapture.struAlarmInCapture[iIndex].dwChanNo[k++] =  i +1;
			}
			if(bClearAll)
			{
				m_pStruJpegCapture->struEventCapture.struAlarmInCapture[iIndex].dwChanNo[k++] = 0xffffffff;
			}
			strTemp.Format(DIGITAL_C_FORMAT, i+g_struDeviceInfo[m_dwDevIndex].iStartChan-MAX_ANALOG_CHANNUM);
			hChanItem =  m_treeAlarmin.InsertItem(strTemp, 0, 0, TVI_ROOT);
			m_treeAlarmin.SetItemData(hChanItem, 1*1000 + i);
			if(m_pStruJpegCapture->struEventCapture.struAlarmInCapture[iIndex].dwChanNo[i] != 0xffffffff)
			{
				m_treeAlarmin.SetCheck(hChanItem, TRUE);
			}
		}
	}
	m_treeAlarmin.SelectItem(hChanItem);
	m_treeAlarmin.Expand(m_treeAlarmin.GetRootItem(),TVE_EXPAND);
}

void CDlgJpegCaptureCfg::CreateChanTreeEvent(int iIndex, BOOL bSetAll, BOOL bClearAll)
{
	//create channel tree
	m_treeEvent.DeleteAllItems();
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0;
	int k = 0;
	HTREEITEM hChanItem = NULL;
	if (m_iChanCount <= 0)
	{
		m_treeEvent.EnableWindow(FALSE);
	}
	 memset(m_pbAlarmInChan, 0, sizeof(BOOL)* MAX_CHANNUM_V40);

	 for (i = 0; i < MAX_CHANNUM_V40; i++)
	 {
		 if ((i < m_iChanCount) && g_struDeviceInfo[m_dwDevIndex].pStruChanInfo[i].bEnable)
		 {
			 if(bSetAll)
			 {
				 m_pStruJpegCapture->struEventCapture.struRelCaptureChan[iIndex].dwChanNo[k++] = i+1;
			 }
			 if(bClearAll)
			 {
				 m_pStruJpegCapture->struEventCapture.struRelCaptureChan[iIndex].dwChanNo[k++] = 0xffffffff;
			 }
			 strTemp.Format(ANALOG_C_FORMAT, i+g_struDeviceInfo[m_dwDevIndex].iStartChan);
			 hChanItem =  m_treeEvent.InsertItem(strTemp, 0, 0, TVI_ROOT);
			 m_treeEvent.SetItemData(hChanItem, 0*1000 + i);
			 if(m_pStruJpegCapture->struEventCapture.struRelCaptureChan[iIndex].dwChanNo[i]  != 0xffffffff)
			 {
				 m_treeEvent.SetCheck(hChanItem, TRUE);
			 }
		 }
		 else if (i >= MAX_ANALOG_CHANNUM && g_struDeviceInfo[m_dwDevIndex].pStruChanInfo[i].bEnable)
		 {
			 if(bSetAll)
			 {
				 m_pStruJpegCapture->struEventCapture.struRelCaptureChan[iIndex].dwChanNo[k++] = i+1;
			 }
			 if(bClearAll)
			 {
				 m_pStruJpegCapture->struEventCapture.struRelCaptureChan[iIndex].dwChanNo[k++] = 0xfffffff;
			 }
			 strTemp.Format(DIGITAL_C_FORMAT, i+g_struDeviceInfo[m_dwDevIndex].iStartChan-MAX_ANALOG_CHANNUM);
			 hChanItem =  m_treeEvent.InsertItem(strTemp, 0, 0, TVI_ROOT);
			 m_treeEvent.SetItemData(hChanItem, 1*1000 + i);
			 if(m_pStruJpegCapture->struEventCapture.struRelCaptureChan[iIndex].dwChanNo[i] != 0xffffffff)
			 {
				 m_treeEvent.SetCheck(hChanItem, TRUE);
			 }
		 }
	}

	m_treeEvent.SelectItem(hChanItem);
	m_treeEvent.Expand(m_treeEvent.GetRootItem(),TVE_EXPAND);
	UpdateData(FALSE);
}

void CDlgJpegCaptureCfg::OnClickTreeAlarmin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	CPoint pt(0,0);
	CRect rc(0,0,0,0);
	GetCursorPos(&pt);
	GetDlgItem(IDC_TREE_ALARMIN)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	ScreenToClient(&pt);
	pt.x = pt.x - rc.left;
	pt.y = pt.y - rc.top;
	
	UINT uFlag = 0;
	HTREEITEM hSelect = m_treeAlarmin.HitTest(pt, &uFlag);
	
	if (NULL == hSelect) 
	{
		return;
	}
	m_treeAlarmin.SelectItem(hSelect);
	DWORD dwIndex = m_treeAlarmin.GetItemData(hSelect)%1000;
	BOOL bCheck = m_treeAlarmin.GetCheck(hSelect);
	m_pbAlarmInChan[dwIndex] = !bCheck;
	//switch checkbox status on click
	if (uFlag != LVHT_TOLEFT)
	{
		m_treeAlarmin.SetCheck(hSelect, !bCheck);
	}
	else
	{
		m_treeAlarmin.SetCheck(hSelect, bCheck);
	}
	
	*pResult = 0;

	DWORD dwCurNum = 0;
    memset(m_pStruJpegCapture->struEventCapture.struAlarmInCapture[0].dwChanNo, INVALID_VALUE_UINT32, sizeof(BOOL)*MAX_CHANNUM_V40);
    for (int i = 0; i < MAX_CHANNUM_V40; i++)
    {
        if (m_pbAlarmInChan[i])
        {
            m_pStruJpegCapture->struEventCapture.struAlarmInCapture[0].dwChanNo[dwCurNum++] = i+1;
        }
    }
}

void CDlgJpegCaptureCfg::OnClickTreeEvent(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	CPoint pt(0,0);
	CRect rc(0,0,0,0);
	GetCursorPos(&pt);
	GetDlgItem(IDC_TREE_EVENT)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	ScreenToClient(&pt);
	pt.x = pt.x - rc.left;
	pt.y = pt.y - rc.top;
	
	UINT uFlag = 0;
	HTREEITEM hSelect = m_treeAlarmin.HitTest(pt, &uFlag);
	int iEventIndex = m_comboEvent.GetCurSel();

	if (NULL == hSelect) 
	{
		return;
	}
	m_treeEvent.SelectItem(hSelect);
	DWORD dwIndex = m_treeEvent.GetItemData(hSelect)%1000;
	BOOL bCheck = m_treeEvent.GetCheck(hSelect);
	m_pbEventChan[dwIndex] = !bCheck;
	//switch checkbox status on click
	if (uFlag != LVHT_TOLEFT)
	{
		m_treeEvent.SetCheck(hSelect, !bCheck);
	}
	else
	{
		m_treeEvent.SetCheck(hSelect, bCheck);
	}
	
	*pResult = 0;

	DWORD dwCurNum = 0;
    memset(m_pStruJpegCapture->struEventCapture.struRelCaptureChan[iEventIndex].dwChanNo, INVALID_VALUE_UINT32, sizeof(BOOL)*MAX_CHANNUM_V40);
    for (int i = 0; i < MAX_CHANNUM_V40; i++)
    {
        if (m_pbEventChan[i])
        {
            m_pStruJpegCapture->struEventCapture.struRelCaptureChan[iEventIndex].dwChanNo[dwCurNum++] = i+1;
        }
    }
}

void CDlgJpegCaptureCfg::OnBtnSetJpegCapture() 
{
	UpdateData(TRUE);
	
	
    NET_DVR_CHANNEL_GROUP struChanGroup = {0};
    
    struChanGroup.dwSize = sizeof(NET_DVR_CHANNEL_GROUP);
    struChanGroup.dwChannel = m_lChannel;
    struChanGroup.dwGroup = 0;
	
	
	m_pStruJpegCapture->struTimingCapture.struJpegPara.wPicSize = m_comboTimePicResolution.GetItemData(m_comboTimePicResolution.GetCurSel());
	m_pStruJpegCapture->struTimingCapture.struJpegPara.wPicQuality = m_comboTimePicQuality.GetCurSel();
	m_pStruJpegCapture->struEventCapture.struJpegPara.wPicSize = m_comboEventPicResolution.GetItemData(m_comboEventPicResolution.GetCurSel());
	m_pStruJpegCapture->struEventCapture.struJpegPara.wPicQuality = m_comboEventPicQuality.GetCurSel();
	m_pStruJpegCapture->struTimingCapture.dwPicInterval = m_dwIntrvalTime;
	m_pStruJpegCapture->struEventCapture.dwPicInterval = m_dwIntervalEvent;
	m_pStruJpegCapture->struEventCapture.byCapTimes = m_byEventCapTimes;
    //m_pStruJpegCapture->struTimingCapture.dwPicInterval = m_comboIntervalTime.GetCurSel() + 1;
	//m_pStruJpegCapture->struEventCapture.dwPicInterval = m_comboIntervalEvent.GetCurSel() + 1;

    m_pStruJpegCapture->byStreamType = m_comStreamType.GetCurSel();
	
    
    DWORD dwListStatus = 0;
    
    if(!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_SET_JPEG_CAPTURE_CFG_V40,0, &struChanGroup,sizeof(struChanGroup),&dwListStatus,\
        m_pStruJpegCapture, sizeof(*m_pStruJpegCapture)) || dwListStatus > 0)
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_SET_JPEG_CAPTURE_CFG_V40 status[%d]", m_lChannel, dwListStatus);
    }
    else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "chan[%d] NET_DVR_SET_JPEG_CAPTURE_CFG_V40", m_lChannel);
	}	
}

void CDlgJpegCaptureCfg::OnButtonExit() 
{
	if (m_pCompresscfgAbility != NULL)
	{
		delete m_pCompresscfgAbility;
		m_pCompresscfgAbility = NULL;
	}
	CDialog::OnCancel();
}

void CDlgJpegCaptureCfg::OnCaptureDayOk() 
{
	UpdateData(TRUE);
	if (!TimeTest())
	{
		return;
	}
    
	int iIndex = m_comboWeekday.GetCurSel();

    if (7 == iIndex) // 假日 单独配 
    {
        m_struCaptureSched.struCaptureHoliday.byAllDayCapture = (WORD)m_bCheckAllDay;
        if (m_bCheckAllDay)
        {		
            m_struCaptureSched.struCaptureHoliday.byCaptureType = (BYTE)m_comboAllDayType.GetItemData(m_comboAllDayType.GetCurSel());
        }
		else
		{
            m_struCaptureSched.struHolidaySched[0].byCaptureType = (BYTE)m_comboTimeRecType1.GetItemData(m_comboTimeRecType1.GetCurSel());
            m_struCaptureSched.struHolidaySched[1].byCaptureType = (BYTE)m_comboTimeRecType2.GetItemData(m_comboTimeRecType2.GetCurSel());
            m_struCaptureSched.struHolidaySched[2].byCaptureType = (BYTE)m_comboTimeRecType3.GetItemData(m_comboTimeRecType3.GetCurSel());
            m_struCaptureSched.struHolidaySched[3].byCaptureType = (BYTE)m_comboTimeRecType4.GetItemData(m_comboTimeRecType4.GetCurSel());
            m_struCaptureSched.struHolidaySched[4].byCaptureType = (BYTE)m_comboTimeRecType5.GetItemData(m_comboTimeRecType5.GetCurSel());
            m_struCaptureSched.struHolidaySched[5].byCaptureType = (BYTE)m_comboTimeRecType6.GetItemData(m_comboTimeRecType6.GetCurSel());
            m_struCaptureSched.struHolidaySched[6].byCaptureType = (BYTE)m_comboTimeRecType7.GetItemData(m_comboTimeRecType7.GetCurSel());
            m_struCaptureSched.struHolidaySched[7].byCaptureType = (BYTE)m_comboTimeRecType8.GetItemData(m_comboTimeRecType8.GetCurSel());
			
			m_struCaptureSched.struHolidaySched[0].struCaptureTime.byStartHour = (BYTE)m_iHour11;
			m_struCaptureSched.struHolidaySched[0].struCaptureTime.byStopHour = (BYTE)m_iHour12;
			m_struCaptureSched.struHolidaySched[1].struCaptureTime.byStartHour = (BYTE)m_iHour21;
			m_struCaptureSched.struHolidaySched[1].struCaptureTime.byStopHour = (BYTE)m_iHour22;
			m_struCaptureSched.struHolidaySched[2].struCaptureTime.byStartHour = (BYTE)m_iHour31;
			m_struCaptureSched.struHolidaySched[2].struCaptureTime.byStopHour = (BYTE)m_iHour32;
			m_struCaptureSched.struHolidaySched[3].struCaptureTime.byStartHour = (BYTE)m_iHour41;
			m_struCaptureSched.struHolidaySched[3].struCaptureTime.byStopHour = (BYTE)m_iHour42;
			
			m_struCaptureSched.struHolidaySched[0].struCaptureTime.byStartMin = (BYTE)m_iMin11;
			m_struCaptureSched.struHolidaySched[0].struCaptureTime.byStopMin = (BYTE)m_iMin12;
			m_struCaptureSched.struHolidaySched[1].struCaptureTime.byStartMin = (BYTE)m_iMin21;
			m_struCaptureSched.struHolidaySched[1].struCaptureTime.byStopMin = (BYTE)m_iMin22;
			m_struCaptureSched.struHolidaySched[2].struCaptureTime.byStartMin = (BYTE)m_iMin31;
			m_struCaptureSched.struHolidaySched[2].struCaptureTime.byStopMin = (BYTE)m_iMin32;
			m_struCaptureSched.struHolidaySched[3].struCaptureTime.byStartMin = (BYTE)m_iMin41;
			m_struCaptureSched.struHolidaySched[3].struCaptureTime.byStopMin = (BYTE)m_iMin42;
			
			m_struCaptureSched.struHolidaySched[4].struCaptureTime.byStartHour = (BYTE)m_iHour51;
			m_struCaptureSched.struHolidaySched[4].struCaptureTime.byStopHour = (BYTE)m_iHour52;
			m_struCaptureSched.struHolidaySched[5].struCaptureTime.byStartHour = (BYTE)m_iHour61;
			m_struCaptureSched.struHolidaySched[5].struCaptureTime.byStopHour = (BYTE)m_iHour62;
			m_struCaptureSched.struHolidaySched[6].struCaptureTime.byStartHour = (BYTE)m_iHour71;
			m_struCaptureSched.struHolidaySched[6].struCaptureTime.byStopHour = (BYTE)m_iHour72;
			m_struCaptureSched.struHolidaySched[7].struCaptureTime.byStartHour = (BYTE)m_iHour81;
			m_struCaptureSched.struHolidaySched[7].struCaptureTime.byStopHour = (BYTE)m_iHour82;
			
			m_struCaptureSched.struHolidaySched[4].struCaptureTime.byStartMin = (BYTE)m_iMin51;
			m_struCaptureSched.struHolidaySched[4].struCaptureTime.byStopMin = (BYTE)m_iMin52;
			m_struCaptureSched.struHolidaySched[5].struCaptureTime.byStartMin = (BYTE)m_iMin61;
			m_struCaptureSched.struHolidaySched[5].struCaptureTime.byStopMin = (BYTE)m_iMin62;
			m_struCaptureSched.struHolidaySched[6].struCaptureTime.byStartMin = (BYTE)m_iMin71;
			m_struCaptureSched.struHolidaySched[6].struCaptureTime.byStopMin = (BYTE)m_iMin72;
			m_struCaptureSched.struHolidaySched[7].struCaptureTime.byStartMin = (BYTE)m_iMin81;
			m_struCaptureSched.struHolidaySched[7].struCaptureTime.byStopMin = (BYTE)m_iMin82; 
		}
	   
    }
    else
    {
		m_struCaptureSched.struCaptureDay[iIndex].byAllDayCapture = (WORD)m_bCheckAllDay;
        if (m_bCheckAllDay)
        {		
            m_struCaptureSched.struCaptureDay[iIndex].byCaptureType = (BYTE)m_comboAllDayType.GetItemData(m_comboAllDayType.GetCurSel());
        }
        m_struCaptureSched.struCaptureSched[iIndex][0].byCaptureType = (BYTE)m_comboTimeRecType1.GetItemData(m_comboTimeRecType1.GetCurSel());
        m_struCaptureSched.struCaptureSched[iIndex][1].byCaptureType = (BYTE)m_comboTimeRecType2.GetItemData(m_comboTimeRecType2.GetCurSel());
        m_struCaptureSched.struCaptureSched[iIndex][2].byCaptureType = (BYTE)m_comboTimeRecType3.GetItemData(m_comboTimeRecType3.GetCurSel());
        m_struCaptureSched.struCaptureSched[iIndex][3].byCaptureType = (BYTE)m_comboTimeRecType4.GetItemData(m_comboTimeRecType4.GetCurSel());
        m_struCaptureSched.struCaptureSched[iIndex][4].byCaptureType = (BYTE)m_comboTimeRecType5.GetItemData(m_comboTimeRecType5.GetCurSel());
        m_struCaptureSched.struCaptureSched[iIndex][5].byCaptureType = (BYTE)m_comboTimeRecType6.GetItemData(m_comboTimeRecType6.GetCurSel());
        m_struCaptureSched.struCaptureSched[iIndex][6].byCaptureType = (BYTE)m_comboTimeRecType7.GetItemData(m_comboTimeRecType7.GetCurSel());
        m_struCaptureSched.struCaptureSched[iIndex][7].byCaptureType = (BYTE)m_comboTimeRecType8.GetItemData(m_comboTimeRecType8.GetCurSel());
        
        m_struCaptureSched.struCaptureSched[iIndex][0].struCaptureTime.byStartHour = (BYTE)m_iHour11;
        m_struCaptureSched.struCaptureSched[iIndex][0].struCaptureTime.byStopHour = (BYTE)m_iHour12;
        m_struCaptureSched.struCaptureSched[iIndex][1].struCaptureTime.byStartHour = (BYTE)m_iHour21;
        m_struCaptureSched.struCaptureSched[iIndex][1].struCaptureTime.byStopHour = (BYTE)m_iHour22;
        m_struCaptureSched.struCaptureSched[iIndex][2].struCaptureTime.byStartHour = (BYTE)m_iHour31;
        m_struCaptureSched.struCaptureSched[iIndex][2].struCaptureTime.byStopHour = (BYTE)m_iHour32;
        m_struCaptureSched.struCaptureSched[iIndex][3].struCaptureTime.byStartHour = (BYTE)m_iHour41;
        m_struCaptureSched.struCaptureSched[iIndex][3].struCaptureTime.byStopHour = (BYTE)m_iHour42;
        
        m_struCaptureSched.struCaptureSched[iIndex][0].struCaptureTime.byStartMin = (BYTE)m_iMin11;
        m_struCaptureSched.struCaptureSched[iIndex][0].struCaptureTime.byStopMin = (BYTE)m_iMin12;
        m_struCaptureSched.struCaptureSched[iIndex][1].struCaptureTime.byStartMin = (BYTE)m_iMin21;
        m_struCaptureSched.struCaptureSched[iIndex][1].struCaptureTime.byStopMin = (BYTE)m_iMin22;
        m_struCaptureSched.struCaptureSched[iIndex][2].struCaptureTime.byStartMin = (BYTE)m_iMin31;
        m_struCaptureSched.struCaptureSched[iIndex][2].struCaptureTime.byStopMin = (BYTE)m_iMin32;
        m_struCaptureSched.struCaptureSched[iIndex][3].struCaptureTime.byStartMin = (BYTE)m_iMin41;
        m_struCaptureSched.struCaptureSched[iIndex][3].struCaptureTime.byStopMin = (BYTE)m_iMin42;
        
        m_struCaptureSched.struCaptureSched[iIndex][4].struCaptureTime.byStartHour = (BYTE)m_iHour51;
        m_struCaptureSched.struCaptureSched[iIndex][4].struCaptureTime.byStopHour = (BYTE)m_iHour52;
        m_struCaptureSched.struCaptureSched[iIndex][5].struCaptureTime.byStartHour = (BYTE)m_iHour61;
        m_struCaptureSched.struCaptureSched[iIndex][5].struCaptureTime.byStopHour = (BYTE)m_iHour62;
        m_struCaptureSched.struCaptureSched[iIndex][6].struCaptureTime.byStartHour = (BYTE)m_iHour71;
        m_struCaptureSched.struCaptureSched[iIndex][6].struCaptureTime.byStopHour = (BYTE)m_iHour72;
        m_struCaptureSched.struCaptureSched[iIndex][7].struCaptureTime.byStartHour = (BYTE)m_iHour81;
        m_struCaptureSched.struCaptureSched[iIndex][7].struCaptureTime.byStopHour = (BYTE)m_iHour82;
        
        m_struCaptureSched.struCaptureSched[iIndex][4].struCaptureTime.byStartMin = (BYTE)m_iMin51;
        m_struCaptureSched.struCaptureSched[iIndex][4].struCaptureTime.byStopMin = (BYTE)m_iMin52;
        m_struCaptureSched.struCaptureSched[iIndex][5].struCaptureTime.byStartMin = (BYTE)m_iMin61;
        m_struCaptureSched.struCaptureSched[iIndex][5].struCaptureTime.byStopMin = (BYTE)m_iMin62;
        m_struCaptureSched.struCaptureSched[iIndex][6].struCaptureTime.byStartMin = (BYTE)m_iMin71;
        m_struCaptureSched.struCaptureSched[iIndex][6].struCaptureTime.byStopMin = (BYTE)m_iMin72;
        m_struCaptureSched.struCaptureSched[iIndex][7].struCaptureTime.byStartMin = (BYTE)m_iMin81;
        m_struCaptureSched.struCaptureSched[iIndex][7].struCaptureTime.byStopMin = (BYTE)m_iMin82;
    }        
	GetDlgItem(IDC_BTN_DAY_COPY)->EnableWindow(TRUE);
}

void CDlgJpegCaptureCfg::setComboTimeRecType(int nComboType, BYTE byCaptureType)
{
    int i = 0;
    if (0 == nComboType)
    {
        for (i = 0; i < m_comboAllDayType.GetCount(); i++)
        {
            if (byCaptureType == m_comboAllDayType.GetItemData(i))
            {
                m_comboAllDayType.SetCurSel(i);
            }
        }
    }
    else if (1 == nComboType)
    {
        for (i = 0; i < m_comboTimeRecType1.GetCount(); i++)
        {
            if (byCaptureType == m_comboTimeRecType1.GetItemData(i))
            {
                m_comboTimeRecType1.SetCurSel(i);
            }
        }
    }
    else if (2 == nComboType)
    {
        for (i = 0; i < m_comboTimeRecType2.GetCount(); i++)
        {
            if (byCaptureType == m_comboTimeRecType2.GetItemData(i))
            {
                m_comboTimeRecType2.SetCurSel(i);
            }
        }
    }
    else if (3 == nComboType)
    {
        for (i = 0; i < m_comboTimeRecType3.GetCount(); i++)
        {
            if (byCaptureType == m_comboTimeRecType3.GetItemData(i))
            {
                m_comboTimeRecType3.SetCurSel(i);
            }
        }
    }
    else if (4 == nComboType)
    {
        for (i = 0; i < m_comboTimeRecType4.GetCount(); i++)
        {
            if (byCaptureType == m_comboTimeRecType4.GetItemData(i))
            {
                m_comboTimeRecType4.SetCurSel(i);
            }
        }
    }
    else if (5 == nComboType)
    {
        for (i = 0; i < m_comboTimeRecType5.GetCount(); i++)
        {
            if (byCaptureType == m_comboTimeRecType5.GetItemData(i))
            {
                m_comboTimeRecType5.SetCurSel(i);
            }
        }
    }
    else if (6 == nComboType)
    {
        for (i = 0; i < m_comboTimeRecType6.GetCount(); i++)
        {
            if (byCaptureType == m_comboTimeRecType6.GetItemData(i))
            {
                m_comboTimeRecType6.SetCurSel(i);
            }
        }
    }
    else if (7 == nComboType)
    {
        for (i = 0; i < m_comboTimeRecType7.GetCount(); i++)
        {
            if (byCaptureType == m_comboTimeRecType7.GetItemData(i))
            {
                m_comboTimeRecType7.SetCurSel(i);
            }
        }
    }
    else if (8 == nComboType)
    {
        for (i = 0; i < m_comboTimeRecType8.GetCount(); i++)
        {
            if (byCaptureType == m_comboTimeRecType8.GetItemData(i))
            {
                m_comboTimeRecType8.SetCurSel(i);
            }
        }
    }
}

void CDlgJpegCaptureCfg::OnSelchangeComboWeekday() 
{
	int iIndex = m_comboWeekday.GetCurSel();	
	if (iIndex == 7) // 假日录像计划 
	{
        m_bCheckAllDay = m_struCaptureSched.struCaptureHoliday.byAllDayCapture;
        setComboTimeRecType(0, m_struCaptureSched.struCaptureHoliday.byCaptureType);

        setComboTimeRecType(1, m_struCaptureSched.struHolidaySched[0].byCaptureType);
        setComboTimeRecType(2, m_struCaptureSched.struHolidaySched[1].byCaptureType);
        setComboTimeRecType(3, m_struCaptureSched.struHolidaySched[2].byCaptureType);
        setComboTimeRecType(4, m_struCaptureSched.struHolidaySched[3].byCaptureType);
        setComboTimeRecType(5, m_struCaptureSched.struHolidaySched[4].byCaptureType);
        setComboTimeRecType(6, m_struCaptureSched.struHolidaySched[5].byCaptureType);
        setComboTimeRecType(7, m_struCaptureSched.struHolidaySched[6].byCaptureType);
        setComboTimeRecType(8, m_struCaptureSched.struHolidaySched[7].byCaptureType);

        m_iHour11 = m_struCaptureSched.struHolidaySched[0].struCaptureTime.byStartHour;
        m_iHour12 = m_struCaptureSched.struHolidaySched[0].struCaptureTime.byStopHour;
        m_iHour21 = m_struCaptureSched.struHolidaySched[1].struCaptureTime.byStartHour;
        m_iHour22 = m_struCaptureSched.struHolidaySched[1].struCaptureTime.byStopHour;
        m_iHour31 = m_struCaptureSched.struHolidaySched[2].struCaptureTime.byStartHour;
        m_iHour32 = m_struCaptureSched.struHolidaySched[2].struCaptureTime.byStopHour;
        m_iHour41 = m_struCaptureSched.struHolidaySched[3].struCaptureTime.byStartHour;
        m_iHour42 = m_struCaptureSched.struHolidaySched[3].struCaptureTime.byStopHour;
        m_iMin11 = m_struCaptureSched.struHolidaySched[0].struCaptureTime.byStartMin;
        m_iMin12 = m_struCaptureSched.struHolidaySched[0].struCaptureTime.byStopMin;
        m_iMin21 = m_struCaptureSched.struHolidaySched[1].struCaptureTime.byStartMin;
        m_iMin22 = m_struCaptureSched.struHolidaySched[1].struCaptureTime.byStopMin;
        m_iMin31 = m_struCaptureSched.struHolidaySched[2].struCaptureTime.byStartMin;
        m_iMin32 = m_struCaptureSched.struHolidaySched[2].struCaptureTime.byStopMin;
        m_iMin41 = m_struCaptureSched.struHolidaySched[3].struCaptureTime.byStartMin;
        m_iMin42 = m_struCaptureSched.struHolidaySched[3].struCaptureTime.byStopMin;
		m_iHour51 = m_struCaptureSched.struHolidaySched[4].struCaptureTime.byStartHour;
        m_iHour52 = m_struCaptureSched.struHolidaySched[4].struCaptureTime.byStopHour;
        m_iHour61 = m_struCaptureSched.struHolidaySched[5].struCaptureTime.byStartHour;
        m_iHour62 = m_struCaptureSched.struHolidaySched[5].struCaptureTime.byStopHour;
        m_iHour71 = m_struCaptureSched.struHolidaySched[6].struCaptureTime.byStartHour;
        m_iHour72 = m_struCaptureSched.struHolidaySched[6].struCaptureTime.byStopHour;
        m_iHour81 = m_struCaptureSched.struHolidaySched[7].struCaptureTime.byStartHour;
        m_iHour82 = m_struCaptureSched.struHolidaySched[7].struCaptureTime.byStopHour;
        m_iMin51 = m_struCaptureSched.struHolidaySched[4].struCaptureTime.byStartMin;
        m_iMin52 = m_struCaptureSched.struHolidaySched[4].struCaptureTime.byStopMin;
        m_iMin61 = m_struCaptureSched.struHolidaySched[5].struCaptureTime.byStartMin;
        m_iMin62 = m_struCaptureSched.struHolidaySched[5].struCaptureTime.byStopMin;
        m_iMin71 = m_struCaptureSched.struHolidaySched[6].struCaptureTime.byStartMin;
        m_iMin72 = m_struCaptureSched.struHolidaySched[6].struCaptureTime.byStopMin;
        m_iMin81 = m_struCaptureSched.struHolidaySched[7].struCaptureTime.byStartMin;
        m_iMin82 = m_struCaptureSched.struHolidaySched[7].struCaptureTime.byStopMin;	
	}
    else
    {
        m_bCheckAllDay = m_struCaptureSched.struCaptureDay[iIndex].byAllDayCapture;
        setComboTimeRecType(0, m_struCaptureSched.struCaptureDay[iIndex].byCaptureType);

        setComboTimeRecType(1, m_struCaptureSched.struCaptureSched[iIndex][0].byCaptureType);
        setComboTimeRecType(2, m_struCaptureSched.struCaptureSched[iIndex][1].byCaptureType);
        setComboTimeRecType(3, m_struCaptureSched.struCaptureSched[iIndex][2].byCaptureType);
        setComboTimeRecType(4, m_struCaptureSched.struCaptureSched[iIndex][3].byCaptureType);
        setComboTimeRecType(5, m_struCaptureSched.struCaptureSched[iIndex][4].byCaptureType);
        setComboTimeRecType(6, m_struCaptureSched.struCaptureSched[iIndex][5].byCaptureType);
        setComboTimeRecType(7, m_struCaptureSched.struCaptureSched[iIndex][6].byCaptureType);
        setComboTimeRecType(8, m_struCaptureSched.struCaptureSched[iIndex][7].byCaptureType);
        
		m_iHour11 = m_struCaptureSched.struCaptureSched[iIndex][0].struCaptureTime.byStartHour;
        m_iHour12 = m_struCaptureSched.struCaptureSched[iIndex][0].struCaptureTime.byStopHour;
        m_iHour21 = m_struCaptureSched.struCaptureSched[iIndex][1].struCaptureTime.byStartHour;
        m_iHour22 = m_struCaptureSched.struCaptureSched[iIndex][1].struCaptureTime.byStopHour;
        m_iHour31 = m_struCaptureSched.struCaptureSched[iIndex][2].struCaptureTime.byStartHour;
        m_iHour32 = m_struCaptureSched.struCaptureSched[iIndex][2].struCaptureTime.byStopHour;
        m_iHour41 = m_struCaptureSched.struCaptureSched[iIndex][3].struCaptureTime.byStartHour;
        m_iHour42 = m_struCaptureSched.struCaptureSched[iIndex][3].struCaptureTime.byStopHour;
        m_iMin11 = m_struCaptureSched.struCaptureSched[iIndex][0].struCaptureTime.byStartMin;
        m_iMin12 = m_struCaptureSched.struCaptureSched[iIndex][0].struCaptureTime.byStopMin;
        m_iMin21 = m_struCaptureSched.struCaptureSched[iIndex][1].struCaptureTime.byStartMin;
        m_iMin22 = m_struCaptureSched.struCaptureSched[iIndex][1].struCaptureTime.byStopMin;
        m_iMin31 = m_struCaptureSched.struCaptureSched[iIndex][2].struCaptureTime.byStartMin;
        m_iMin32 = m_struCaptureSched.struCaptureSched[iIndex][2].struCaptureTime.byStopMin;
        m_iMin41 = m_struCaptureSched.struCaptureSched[iIndex][3].struCaptureTime.byStartMin;
        m_iMin42 = m_struCaptureSched.struCaptureSched[iIndex][3].struCaptureTime.byStopMin;
		m_iHour51 = m_struCaptureSched.struCaptureSched[iIndex][4].struCaptureTime.byStartHour;
        m_iHour52 = m_struCaptureSched.struCaptureSched[iIndex][4].struCaptureTime.byStopHour;
        m_iHour61 = m_struCaptureSched.struCaptureSched[iIndex][5].struCaptureTime.byStartHour;
        m_iHour62 = m_struCaptureSched.struCaptureSched[iIndex][5].struCaptureTime.byStopHour;
        m_iHour71 = m_struCaptureSched.struCaptureSched[iIndex][6].struCaptureTime.byStartHour;
        m_iHour72 = m_struCaptureSched.struCaptureSched[iIndex][6].struCaptureTime.byStopHour;
        m_iHour81 = m_struCaptureSched.struCaptureSched[iIndex][7].struCaptureTime.byStartHour;
        m_iHour82 = m_struCaptureSched.struCaptureSched[iIndex][7].struCaptureTime.byStopHour;
        m_iMin51 = m_struCaptureSched.struCaptureSched[iIndex][4].struCaptureTime.byStartMin;
        m_iMin52 = m_struCaptureSched.struCaptureSched[iIndex][4].struCaptureTime.byStopMin;
        m_iMin61 = m_struCaptureSched.struCaptureSched[iIndex][5].struCaptureTime.byStartMin;
        m_iMin62 = m_struCaptureSched.struCaptureSched[iIndex][5].struCaptureTime.byStopMin;
        m_iMin71 = m_struCaptureSched.struCaptureSched[iIndex][6].struCaptureTime.byStartMin;
        m_iMin72 = m_struCaptureSched.struCaptureSched[iIndex][6].struCaptureTime.byStopMin;
        m_iMin81 = m_struCaptureSched.struCaptureSched[iIndex][7].struCaptureTime.byStartMin;
        m_iMin82 = m_struCaptureSched.struCaptureSched[iIndex][7].struCaptureTime.byStopMin;
    }
	EnableControl(!m_bCheckAllDay);
	GetDlgItem(IDC_BTN_DAY_COPY)->EnableWindow(FALSE);
	UpdateData(FALSE);
}

void CDlgJpegCaptureCfg::OnButtonUpdateSched() 
{
 	DWORD dwBytesReturned = 0;
	if(!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_SCHED_CAPTURECFG, m_lChannel, &m_struCaptureSched, sizeof(m_struCaptureSched), &dwBytesReturned))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_GET_SCHED_CAPTURECFG", m_lChannel);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "chan[%d] NET_DVR_GET_SCHED_CAPTURECFG", m_lChannel);
			
		m_bEnableCapture = m_struCaptureSched.byEnable;
		m_dwPicSaveDays = m_struCaptureSched.dwRecorderDuration;
        m_comboDelayTime.SetCurSel(m_struCaptureSched.dwDelayTime);

		OnSelchangeComboWeekday();
	}

	UpdateData(FALSE);
}

void CDlgJpegCaptureCfg::OnBtnSetJpegCaptureSched() 
{
	OnCaptureDayOk();
	m_struCaptureSched.byEnable = m_bEnableCapture;
	m_struCaptureSched.dwRecorderDuration = m_dwPicSaveDays;
    m_struCaptureSched.dwDelayTime = m_comboDelayTime.GetCurSel();

	if(!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_SCHED_CAPTURECFG, m_lChannel, &m_struCaptureSched, sizeof(m_struCaptureSched)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_SET_SCHED_CAPTURECFG", m_lChannel);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "chan[%d] NET_DVR_SET_SCHED_CAPTURECFG", m_lChannel);
	}
}

void CDlgJpegCaptureCfg::OnButtonUpdateFtp() 
{
	DWORD dwBytesReturned = 0;
	char szLan[1024] = {0};

	memset(m_struFtpCfgV40,0,sizeof(m_struFtpCfgV40));
	NET_DVR_FTP_TYPE struTempFtpType[2] = {0};
	struTempFtpType[0].byType = 0;
	struTempFtpType[1].byType = 1;
	DWORD dwStatus[2] = {0}; 

	if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_FTPCFG_V40,2,&struTempFtpType,sizeof(struTempFtpType),&dwStatus,&m_struFtpCfgV40, sizeof(m_struFtpCfgV40)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_GET_FTPCFG_V40", m_lChannel);
		
		sprintf(szLan,"%d",NET_DVR_GetLastError());
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "chan[%d] NET_DVR_GET_FTPCFG_V40", m_lChannel);
		SetFtpV40Info();
		//设置备份		
	}
	
	
}

void CDlgJpegCaptureCfg::OnSelchangeComboDirLevel() 
{
	UpdateData(TRUE);
	SetMainFtpSelDirShow(FALSE);
	SetMainFtpSelSecondDirShow(FALSE);
	int temp;
	temp = m_DirLevelCtrl.GetCurSel();
	switch (temp)
	{
	case 0:	
		m_comboMainFirstDirModeCtr.EnableWindow(FALSE);
        m_comboMainSecordDirModeCtrl.EnableWindow(FALSE);		
		break;
	case 1:
		m_comboMainFirstDirModeCtr.EnableWindow(TRUE); 
		m_comboMainSecordDirModeCtrl.EnableWindow(FALSE);
		break;
	case 2:
		m_comboMainFirstDirModeCtr.EnableWindow(TRUE);
		m_comboMainSecordDirModeCtrl.EnableWindow(TRUE);
		break;
	default:	
		break;
	}
	
	UpdateData(FALSE);
}

void CDlgJpegCaptureCfg::OnSelchangeComboDirModeOne()
{
   	UpdateData(TRUE);
	int temp;
	temp = m_comboMainFirstDirModeCtr.GetCurSel();
	switch (temp)
	{
	case 3:
		SetMainFtpSelDirShow(TRUE);
		break;
	default:
		SetMainFtpSelDirShow(FALSE);
		//SetMainFtpSelSecondDirShow(FALSE);
		break;
	}
	
	UpdateData(FALSE);
}
void CDlgJpegCaptureCfg::OnSelchangeComboDirModeTwo()
{
	UpdateData(TRUE);
	int temp;
	temp = m_comboMainSecordDirModeCtrl.GetCurSel();
	
	switch(temp)
	{
	case 2:
		SetMainFtpSelSecondDirShow(TRUE);
		break;
	default:
		SetMainFtpSelSecondDirShow(FALSE);
		break;
	}
	UpdateData(FALSE);		
	
	
}	
void CDlgJpegCaptureCfg::OnSelchangeSubComboDirModeOne()
{
	UpdateData(TRUE);
	int temp;
	temp = m_comboSubFirstDirModeCtr.GetCurSel();
	
	switch(temp)
	{
	case 3:
		SetSubFtpSelDirShow(TRUE);
		break;
	default:
		SetSubFtpSelDirShow(FALSE);
	//	SetSubFtpSelSecondDirShow(FALSE);
		break;
	}
	UpdateData(FALSE);	
	
}
void CDlgJpegCaptureCfg::OnSelchangeSubComboDirModeTwo()
{
	UpdateData(TRUE);
	int temp;
	temp = m_comboSubSecordDirModeCtrl.GetCurSel();
	
	switch(temp)
	{
	case 2:
		SetSubFtpSelSecondDirShow(TRUE);
		break;
	default:
		SetSubFtpSelSecondDirShow(FALSE);
		break;
	}
	UpdateData(FALSE);
}

void CDlgJpegCaptureCfg::OnBtnSetFtp() 
{
	UpdateData(TRUE);
	CString sTemp;
	char szLan[128] = {0};
	//获取参数信息
	GetFtpV40Info();    
	NET_DVR_FTP_TYPE struTempFtpType[2] = {0};	
	
	memset(struTempFtpType, 0, 2*sizeof(NET_DVR_FTP_TYPE));
	struTempFtpType[0].byType = 0;
	struTempFtpType[1].byType = 1;
	
	DWORD dwStatus[2] = {0}; 
	if (!NET_DVR_SetDeviceConfig(m_lUserID,NET_DVR_SET_FTPCFG_V40,2,&struTempFtpType,2*sizeof(NET_DVR_FTP_TYPE),&dwStatus,&m_struFtpCfgV40,sizeof(m_struFtpCfgV40)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_SET_FTPCFG_V40", m_lChannel);
		sprintf(szLan,"%d",NET_DVR_GetLastError());
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "chan[%d] NET_DVR_SET_FTPCFG_V40", m_lChannel);	
	}
}

void CDlgJpegCaptureCfg::OnBtnDayCopy() 
{
	UpdateData(TRUE);
	int iIndex = m_comboCopyWeekday.GetCurSel() - 1;
	if (!TimeTest())
	{
		return;
	}

	if (iIndex != -1)
	{
        if (iIndex == 7) // 假日
        {
            m_struCaptureSched.struCaptureHoliday.byAllDayCapture = m_bCheckAllDay;
            m_struCaptureSched.struCaptureHoliday.byCaptureType = (BYTE)m_comboAllDayType.GetItemData(m_comboAllDayType.GetCurSel());
            m_struCaptureSched.struHolidaySched[0].byCaptureType = (BYTE)m_comboTimeRecType1.GetItemData(m_comboTimeRecType1.GetCurSel());
            m_struCaptureSched.struHolidaySched[1].byCaptureType = (BYTE)m_comboTimeRecType2.GetItemData(m_comboTimeRecType2.GetCurSel());
            m_struCaptureSched.struHolidaySched[2].byCaptureType = (BYTE)m_comboTimeRecType3.GetItemData(m_comboTimeRecType3.GetCurSel());
            m_struCaptureSched.struHolidaySched[3].byCaptureType = (BYTE)m_comboTimeRecType4.GetItemData(m_comboTimeRecType4.GetCurSel());
            m_struCaptureSched.struHolidaySched[4].byCaptureType = (BYTE)m_comboTimeRecType5.GetItemData(m_comboTimeRecType5.GetCurSel());
            m_struCaptureSched.struHolidaySched[5].byCaptureType = (BYTE)m_comboTimeRecType6.GetItemData(m_comboTimeRecType6.GetCurSel());
            m_struCaptureSched.struHolidaySched[6].byCaptureType = (BYTE)m_comboTimeRecType7.GetItemData(m_comboTimeRecType7.GetCurSel());
            m_struCaptureSched.struHolidaySched[7].byCaptureType = (BYTE)m_comboTimeRecType8.GetItemData(m_comboTimeRecType8.GetCurSel());
			
            m_struCaptureSched.struHolidaySched[0].struCaptureTime.byStartHour = (BYTE)m_iHour11;
            m_struCaptureSched.struHolidaySched[0].struCaptureTime.byStopHour = (BYTE)m_iHour12;
            m_struCaptureSched.struHolidaySched[1].struCaptureTime.byStartHour = (BYTE)m_iHour21;
            m_struCaptureSched.struHolidaySched[1].struCaptureTime.byStopHour = (BYTE)m_iHour22;
            m_struCaptureSched.struHolidaySched[2].struCaptureTime.byStartHour = (BYTE)m_iHour31;
            m_struCaptureSched.struHolidaySched[2].struCaptureTime.byStopHour = (BYTE)m_iHour32;
            m_struCaptureSched.struHolidaySched[3].struCaptureTime.byStartHour = (BYTE)m_iHour41;
            m_struCaptureSched.struHolidaySched[3].struCaptureTime.byStopHour = (BYTE)m_iHour42;
			m_struCaptureSched.struHolidaySched[4].struCaptureTime.byStartHour = (BYTE)m_iHour51;
            m_struCaptureSched.struHolidaySched[4].struCaptureTime.byStopHour = (BYTE)m_iHour52;
            m_struCaptureSched.struHolidaySched[5].struCaptureTime.byStartHour = (BYTE)m_iHour61;
            m_struCaptureSched.struHolidaySched[5].struCaptureTime.byStopHour = (BYTE)m_iHour62;
            m_struCaptureSched.struHolidaySched[6].struCaptureTime.byStartHour = (BYTE)m_iHour71;
            m_struCaptureSched.struHolidaySched[6].struCaptureTime.byStopHour = (BYTE)m_iHour72;
            m_struCaptureSched.struHolidaySched[7].struCaptureTime.byStartHour = (BYTE)m_iHour81;
            m_struCaptureSched.struHolidaySched[7].struCaptureTime.byStopHour = (BYTE)m_iHour82;
            
            m_struCaptureSched.struHolidaySched[0].struCaptureTime.byStartMin = (BYTE)m_iMin11;
            m_struCaptureSched.struHolidaySched[0].struCaptureTime.byStopMin = (BYTE)m_iMin12;
            m_struCaptureSched.struHolidaySched[1].struCaptureTime.byStartMin = (BYTE)m_iMin21;
            m_struCaptureSched.struHolidaySched[1].struCaptureTime.byStopMin = (BYTE)m_iMin22;
            m_struCaptureSched.struHolidaySched[2].struCaptureTime.byStartMin = (BYTE)m_iMin31;
            m_struCaptureSched.struHolidaySched[2].struCaptureTime.byStopMin = (BYTE)m_iMin32;
            m_struCaptureSched.struHolidaySched[3].struCaptureTime.byStartMin = (BYTE)m_iMin41;
            m_struCaptureSched.struHolidaySched[3].struCaptureTime.byStopMin = (BYTE)m_iMin42;
			m_struCaptureSched.struHolidaySched[4].struCaptureTime.byStartMin = (BYTE)m_iMin51;
            m_struCaptureSched.struHolidaySched[4].struCaptureTime.byStopMin = (BYTE)m_iMin52;
            m_struCaptureSched.struHolidaySched[5].struCaptureTime.byStartMin = (BYTE)m_iMin61;
            m_struCaptureSched.struHolidaySched[5].struCaptureTime.byStopMin = (BYTE)m_iMin62;
            m_struCaptureSched.struHolidaySched[6].struCaptureTime.byStartMin = (BYTE)m_iMin71;
            m_struCaptureSched.struHolidaySched[6].struCaptureTime.byStopMin = (BYTE)m_iMin72;
            m_struCaptureSched.struHolidaySched[7].struCaptureTime.byStartMin = (BYTE)m_iMin81;
            m_struCaptureSched.struHolidaySched[7].struCaptureTime.byStopMin = (BYTE)m_iMin82;
        }
        else
        {
            m_struCaptureSched.struCaptureDay[iIndex].byAllDayCapture = m_bCheckAllDay;
            m_struCaptureSched.struCaptureDay[iIndex].byCaptureType = (BYTE)m_comboAllDayType.GetItemData(m_comboAllDayType.GetCurSel());
            m_struCaptureSched.struCaptureSched[iIndex][0].byCaptureType = (BYTE)m_comboTimeRecType1.GetItemData(m_comboTimeRecType1.GetCurSel());
            m_struCaptureSched.struCaptureSched[iIndex][1].byCaptureType = (BYTE)m_comboTimeRecType2.GetItemData(m_comboTimeRecType2.GetCurSel());
            m_struCaptureSched.struCaptureSched[iIndex][2].byCaptureType = (BYTE)m_comboTimeRecType3.GetItemData(m_comboTimeRecType3.GetCurSel());
            m_struCaptureSched.struCaptureSched[iIndex][3].byCaptureType = (BYTE)m_comboTimeRecType4.GetItemData(m_comboTimeRecType4.GetCurSel());
            m_struCaptureSched.struCaptureSched[iIndex][4].byCaptureType = (BYTE)m_comboTimeRecType5.GetItemData(m_comboTimeRecType5.GetCurSel());
            m_struCaptureSched.struCaptureSched[iIndex][5].byCaptureType = (BYTE)m_comboTimeRecType6.GetItemData(m_comboTimeRecType6.GetCurSel());
            m_struCaptureSched.struCaptureSched[iIndex][6].byCaptureType = (BYTE)m_comboTimeRecType7.GetItemData(m_comboTimeRecType7.GetCurSel());
            m_struCaptureSched.struCaptureSched[iIndex][7].byCaptureType = (BYTE)m_comboTimeRecType8.GetItemData(m_comboTimeRecType8.GetCurSel());

            m_struCaptureSched.struCaptureSched[iIndex][0].struCaptureTime.byStartHour = (BYTE)m_iHour11;
            m_struCaptureSched.struCaptureSched[iIndex][0].struCaptureTime.byStopHour = (BYTE)m_iHour12;
            m_struCaptureSched.struCaptureSched[iIndex][1].struCaptureTime.byStartHour = (BYTE)m_iHour21;
            m_struCaptureSched.struCaptureSched[iIndex][1].struCaptureTime.byStopHour = (BYTE)m_iHour22;
            m_struCaptureSched.struCaptureSched[iIndex][2].struCaptureTime.byStartHour = (BYTE)m_iHour31;
            m_struCaptureSched.struCaptureSched[iIndex][2].struCaptureTime.byStopHour = (BYTE)m_iHour32;
            m_struCaptureSched.struCaptureSched[iIndex][3].struCaptureTime.byStartHour = (BYTE)m_iHour41;
            m_struCaptureSched.struCaptureSched[iIndex][3].struCaptureTime.byStopHour = (BYTE)m_iHour42;
			m_struCaptureSched.struCaptureSched[iIndex][4].struCaptureTime.byStartHour = (BYTE)m_iHour51;
            m_struCaptureSched.struCaptureSched[iIndex][4].struCaptureTime.byStopHour = (BYTE)m_iHour52;
            m_struCaptureSched.struCaptureSched[iIndex][5].struCaptureTime.byStartHour = (BYTE)m_iHour61;
            m_struCaptureSched.struCaptureSched[iIndex][5].struCaptureTime.byStopHour = (BYTE)m_iHour62;
            m_struCaptureSched.struCaptureSched[iIndex][6].struCaptureTime.byStartHour = (BYTE)m_iHour71;
            m_struCaptureSched.struCaptureSched[iIndex][6].struCaptureTime.byStopHour = (BYTE)m_iHour72;
            m_struCaptureSched.struCaptureSched[iIndex][7].struCaptureTime.byStartHour = (BYTE)m_iHour81;
            m_struCaptureSched.struCaptureSched[iIndex][7].struCaptureTime.byStopHour = (BYTE)m_iHour82;
            
            m_struCaptureSched.struCaptureSched[iIndex][0].struCaptureTime.byStartMin = (BYTE)m_iMin11;
            m_struCaptureSched.struCaptureSched[iIndex][0].struCaptureTime.byStopMin = (BYTE)m_iMin12;
            m_struCaptureSched.struCaptureSched[iIndex][1].struCaptureTime.byStartMin = (BYTE)m_iMin21;
            m_struCaptureSched.struCaptureSched[iIndex][1].struCaptureTime.byStopMin = (BYTE)m_iMin22;
            m_struCaptureSched.struCaptureSched[iIndex][2].struCaptureTime.byStartMin = (BYTE)m_iMin31;
            m_struCaptureSched.struCaptureSched[iIndex][2].struCaptureTime.byStopMin = (BYTE)m_iMin32;
            m_struCaptureSched.struCaptureSched[iIndex][3].struCaptureTime.byStartMin = (BYTE)m_iMin41;
            m_struCaptureSched.struCaptureSched[iIndex][3].struCaptureTime.byStopMin = (BYTE)m_iMin42;
			m_struCaptureSched.struCaptureSched[iIndex][4].struCaptureTime.byStartMin = (BYTE)m_iMin51;
            m_struCaptureSched.struCaptureSched[iIndex][4].struCaptureTime.byStopMin = (BYTE)m_iMin52;
            m_struCaptureSched.struCaptureSched[iIndex][5].struCaptureTime.byStartMin = (BYTE)m_iMin61;
            m_struCaptureSched.struCaptureSched[iIndex][5].struCaptureTime.byStopMin = (BYTE)m_iMin62;
            m_struCaptureSched.struCaptureSched[iIndex][6].struCaptureTime.byStartMin = (BYTE)m_iMin71;
            m_struCaptureSched.struCaptureSched[iIndex][6].struCaptureTime.byStopMin = (BYTE)m_iMin72;
            m_struCaptureSched.struCaptureSched[iIndex][7].struCaptureTime.byStartMin = (BYTE)m_iMin81;
            m_struCaptureSched.struCaptureSched[iIndex][7].struCaptureTime.byStopMin = (BYTE)m_iMin82;
        }
	}
	else
	{
		for (int i = 0;i < MAX_DAYS;i++)
		{	
			m_struCaptureSched.struCaptureDay[i].byAllDayCapture = m_bCheckAllDay;
            m_struCaptureSched.struCaptureDay[i].byCaptureType = (BYTE)m_comboAllDayType.GetItemData(m_comboAllDayType.GetCurSel());

            m_struCaptureSched.struCaptureSched[i][0].byCaptureType = (BYTE)m_comboTimeRecType1.GetItemData(m_comboTimeRecType1.GetCurSel());
            m_struCaptureSched.struCaptureSched[i][1].byCaptureType = (BYTE)m_comboTimeRecType2.GetItemData(m_comboTimeRecType2.GetCurSel());
            m_struCaptureSched.struCaptureSched[i][2].byCaptureType = (BYTE)m_comboTimeRecType3.GetItemData(m_comboTimeRecType3.GetCurSel());
            m_struCaptureSched.struCaptureSched[i][3].byCaptureType = (BYTE)m_comboTimeRecType4.GetItemData(m_comboTimeRecType4.GetCurSel());
            m_struCaptureSched.struCaptureSched[i][4].byCaptureType = (BYTE)m_comboTimeRecType5.GetItemData(m_comboTimeRecType5.GetCurSel());
            m_struCaptureSched.struCaptureSched[i][5].byCaptureType = (BYTE)m_comboTimeRecType6.GetItemData(m_comboTimeRecType6.GetCurSel());
            m_struCaptureSched.struCaptureSched[i][6].byCaptureType = (BYTE)m_comboTimeRecType7.GetItemData(m_comboTimeRecType7.GetCurSel());
            m_struCaptureSched.struCaptureSched[i][7].byCaptureType = (BYTE)m_comboTimeRecType8.GetItemData(m_comboTimeRecType8.GetCurSel());

			m_struCaptureSched.struCaptureSched[i][0].struCaptureTime.byStartHour = (BYTE)m_iHour11;
			m_struCaptureSched.struCaptureSched[i][0].struCaptureTime.byStopHour = (BYTE)m_iHour12;
			m_struCaptureSched.struCaptureSched[i][1].struCaptureTime.byStartHour = (BYTE)m_iHour21;
			m_struCaptureSched.struCaptureSched[i][1].struCaptureTime.byStopHour = (BYTE)m_iHour22;
			m_struCaptureSched.struCaptureSched[i][2].struCaptureTime.byStartHour = (BYTE)m_iHour31;
			m_struCaptureSched.struCaptureSched[i][2].struCaptureTime.byStopHour = (BYTE)m_iHour32;
			m_struCaptureSched.struCaptureSched[i][3].struCaptureTime.byStartHour = (BYTE)m_iHour41;
			m_struCaptureSched.struCaptureSched[i][3].struCaptureTime.byStopHour = (BYTE)m_iHour42;
			m_struCaptureSched.struCaptureSched[i][4].struCaptureTime.byStartHour = (BYTE)m_iHour51;
			m_struCaptureSched.struCaptureSched[i][4].struCaptureTime.byStopHour = (BYTE)m_iHour52;
			m_struCaptureSched.struCaptureSched[i][5].struCaptureTime.byStartHour = (BYTE)m_iHour61;
			m_struCaptureSched.struCaptureSched[i][5].struCaptureTime.byStopHour = (BYTE)m_iHour62;
			m_struCaptureSched.struCaptureSched[i][6].struCaptureTime.byStartHour = (BYTE)m_iHour71;
			m_struCaptureSched.struCaptureSched[i][6].struCaptureTime.byStopHour = (BYTE)m_iHour72;
			m_struCaptureSched.struCaptureSched[i][7].struCaptureTime.byStartHour = (BYTE)m_iHour81;
			m_struCaptureSched.struCaptureSched[i][7].struCaptureTime.byStopHour = (BYTE)m_iHour82;

			m_struCaptureSched.struCaptureSched[i][0].struCaptureTime.byStartMin = (BYTE)m_iMin11;
			m_struCaptureSched.struCaptureSched[i][0].struCaptureTime.byStopMin = (BYTE)m_iMin12;
			m_struCaptureSched.struCaptureSched[i][1].struCaptureTime.byStartMin = (BYTE)m_iMin21;
			m_struCaptureSched.struCaptureSched[i][1].struCaptureTime.byStopMin = (BYTE)m_iMin22;
			m_struCaptureSched.struCaptureSched[i][2].struCaptureTime.byStartMin = (BYTE)m_iMin31;
			m_struCaptureSched.struCaptureSched[i][2].struCaptureTime.byStopMin = (BYTE)m_iMin32;
			m_struCaptureSched.struCaptureSched[i][3].struCaptureTime.byStartMin = (BYTE)m_iMin41;
			m_struCaptureSched.struCaptureSched[i][3].struCaptureTime.byStopMin = (BYTE)m_iMin42;
			m_struCaptureSched.struCaptureSched[i][4].struCaptureTime.byStartMin = (BYTE)m_iMin51;
			m_struCaptureSched.struCaptureSched[i][4].struCaptureTime.byStopMin = (BYTE)m_iMin52;
			m_struCaptureSched.struCaptureSched[i][5].struCaptureTime.byStartMin = (BYTE)m_iMin61;
			m_struCaptureSched.struCaptureSched[i][5].struCaptureTime.byStopMin = (BYTE)m_iMin62;
			m_struCaptureSched.struCaptureSched[i][6].struCaptureTime.byStartMin = (BYTE)m_iMin71;
			m_struCaptureSched.struCaptureSched[i][6].struCaptureTime.byStopMin = (BYTE)m_iMin72;
			m_struCaptureSched.struCaptureSched[i][7].struCaptureTime.byStartMin = (BYTE)m_iMin81;
			m_struCaptureSched.struCaptureSched[i][7].struCaptureTime.byStopMin = (BYTE)m_iMin82;
		}
	}	
}

void CDlgJpegCaptureCfg::OnChkAllDay() 
{
	UpdateData(TRUE);
	EnableControl(!m_bCheckAllDay);
}

void CDlgJpegCaptureCfg::OnButtonAlarminAll() 
{
	int iIndex = m_comboAlarmIn.GetCurSel();
	
	CreateChanTreeAlarmIn(iIndex, TRUE, FALSE);
}

void CDlgJpegCaptureCfg::OnButtonAlarminClean() 
{
	int iIndex = m_comboAlarmIn.GetCurSel();
	
	CreateChanTreeAlarmIn(iIndex, FALSE, TRUE);
}

void CDlgJpegCaptureCfg::OnButtonEventAll() 
{
	int iIndex = m_comboEvent.GetCurSel();
	
	CreateChanTreeEvent(iIndex, TRUE, FALSE);
}

void CDlgJpegCaptureCfg::OnButtonEventClean() 
{
	int iIndex = m_comboEvent.GetCurSel();
	
	CreateChanTreeEvent(iIndex, FALSE, TRUE);	
}

void CDlgJpegCaptureCfg::OnButtonUpdateFtp2() 
{
	// TODO: Add your control notification handler code here
	DWORD dwBytesReturned = 0;
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_FTPCFG_SECOND, 0,&m_strFtpCfg2, sizeof(NET_DVR_FTPCFG), &dwBytesReturned))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_GET_FTPCFG_SECOND", m_lChannel);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "chan[%d] NET_DVR_GET_FTPCFG_SECOND", m_lChannel);
		m_DirLevelCtrl2.SetCurSel(m_strFtpCfg2.dwDirLevel);
        int temp;
        temp = m_DirLevelCtrl2.GetCurSel();
        switch (temp)
        {
        case 0:	
			m_comboSubFirstDirModeCtr.EnableWindow(FALSE);
            m_comboSubSecordDirModeCtrl.EnableWindow(FALSE);
            break;
        case 1:
            m_comboSubFirstDirModeCtr.EnableWindow(TRUE); 
            if (m_strFtpCfg2.wTopDirMode == 0x1)
            {
                m_comboSubFirstDirModeCtr.SetCurSel(0);
            }
            if (m_strFtpCfg2.wTopDirMode == 0x2)
            {
				m_comboSubFirstDirModeCtr.SetCurSel(1);
            }
            if (m_strFtpCfg2.wTopDirMode == 0x3)
            {
                m_comboSubFirstDirModeCtr.SetCurSel(2);
            }
			if (m_strFtpCfg2.wTopDirMode == 0x6)
			{
				m_comboSubFirstDirModeCtr.SetCurSel(3);
			}
            m_comboSubSecordDirModeCtrl.EnableWindow(FALSE);
            break;
        case 2:
            m_comboSubFirstDirModeCtr.EnableWindow(TRUE);
            m_comboSubSecordDirModeCtrl.EnableWindow(TRUE);
            if (m_strFtpCfg2.wTopDirMode == 0x1)
            {
                m_comboSubFirstDirModeCtr.SetCurSel(0);
            }
            if (m_strFtpCfg2.wTopDirMode == 0x2)
            {
                m_comboSubFirstDirModeCtr.SetCurSel(1);
            }
            if (m_strFtpCfg2.wTopDirMode == 0x3)
            {
                m_comboSubFirstDirModeCtr.SetCurSel(2);
            }
            if (m_strFtpCfg2.wSubDirMode == 0x1 )
            {
                m_comboSubSecordDirModeCtrl.SetCurSel(0);
            }
            if (m_strFtpCfg2.wSubDirMode == 0x2 )
            {
                m_comboSubSecordDirModeCtrl.SetCurSel(1);
            }
            break;
        default:	
            break;
        }
		
		m_UseFTPUpCtrl2.SetCurSel(m_strFtpCfg2.dwEnableFTP);	
		m_dwPort2 = m_strFtpCfg2.dwFTPPort;
		m_csPassword2 = m_strFtpCfg2.sPassword;
		m_csUserName2 = m_strFtpCfg2.sUserName;
		m_csIP2 = m_strFtpCfg2.sFTPIP;
	}
	
	UpdateData(FALSE);
}

void CDlgJpegCaptureCfg::OnBtnSetFtp2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString sTemp;
	char szLan[128] = {0};
	
	//FTP配置	
	int temp, tmp1, tmp2;
    temp = m_DirLevelCtrl2.GetCurSel();
    switch (temp)
    {
    case 0:
        m_strFtpCfg2.dwDirLevel = 0;
        break;
    case 1:
        m_strFtpCfg2.dwDirLevel = 1;

		tmp1 = m_comboSubFirstDirModeCtr.GetCurSel();
        if (tmp1 == 0)
        {
            m_strFtpCfg2.wTopDirMode = 0x1;
        }
        if (tmp1 == 1)
        {
            m_strFtpCfg2.wTopDirMode = 0x2;
        }
        if (tmp1 == 2)
        {
            m_strFtpCfg2.wTopDirMode = 0x3;
        }
		if (tmp1 == 3)
		{
			m_strFtpCfg2.wTopDirMode = 0x6;

		}
        break;
    case 2:
        m_strFtpCfg2.dwDirLevel = 2;
        tmp1 = m_comboSubFirstDirModeCtr.GetCurSel();
        if (tmp1 == 0)
        {
            m_strFtpCfg2.wTopDirMode = 0x1;
        }
        if (tmp1 == 1)
        {
            m_strFtpCfg2.wTopDirMode = 0x2;
        }
        if (tmp1 == 2)
        {
            m_strFtpCfg2.wTopDirMode = 0x3;
        }
		tmp2 = m_comboSubSecordDirModeCtrl.GetCurSel();
        if (tmp2 == 0)
        {
            m_strFtpCfg2.wSubDirMode = 0x1;
        }
        if (tmp2 == 1)
        {
            m_strFtpCfg2.wSubDirMode = 0x2;
        }
    default:
        break;
    }
	
	m_strFtpCfg2.dwEnableFTP = m_UseFTPUpCtrl2.GetCurSel();
	
	m_strFtpCfg2.dwFTPPort = m_dwPort2;
	sprintf((char*)m_strFtpCfg2.sPassword, m_csPassword2, PASSWD_LEN);
	sprintf((char*)m_strFtpCfg2.sUserName, m_csUserName2, NAME_LEN);
	sprintf((char*)m_strFtpCfg2.sFTPIP, m_csIP2, 16);
	
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_FTPCFG_SECOND, 0, &m_strFtpCfg2, sizeof(NET_DVR_FTPCFG)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_SET_FTPCFG_SECOND", m_lChannel);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "chan[%d] NET_DVR_SET_FTPCFG_SECOND", m_lChannel);	
	}
}

void CDlgJpegCaptureCfg::SetFtpV40Info()
{
	int temp;
	
	//先将自定义目录信息隐藏
	SetMainFtpSelDirShow(FALSE);
	SetMainFtpSelSecondDirShow(FALSE);
	SetSubFtpSelDirShow(FALSE);
	SetSubFtpSelSecondDirShow(FALSE);
	m_DirLevelCtrl.SetCurSel(m_struFtpCfgV40[0].byDirLevel);
	temp = m_DirLevelCtrl.GetCurSel();
	switch (temp)
	{
	case 0:	
		m_comboMainFirstDirModeCtr.EnableWindow(FALSE);
		m_comboMainSecordDirModeCtrl.EnableWindow(FALSE);
		break;
	case 1:
		m_comboMainFirstDirModeCtr.EnableWindow(TRUE); 
		if (m_struFtpCfgV40[0].byTopDirMode == 0x1)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(0);
		}
		if (m_struFtpCfgV40[0].byTopDirMode == 0x2)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(1);
		}
		if (m_struFtpCfgV40[0].byTopDirMode == 0x3)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(2);
		}
		if (m_struFtpCfgV40[0].byTopDirMode == 0x6)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(3);
			SetMainFtpSelDirShow(TRUE);
		}
		/*if (m_struFtpCfgV40[0].byTopDirMode == 0x5)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(4);
		}
		if (m_struFtpCfgV40[0].byTopDirMode == 0x6)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(5);
		}
		if (m_struFtpCfgV40[0].byTopDirMode == 0x7)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(6);
		}
		if (m_struFtpCfgV40[0].byTopDirMode == 0x8)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(7);
		}
		if (m_struFtpCfgV40[0].byTopDirMode == 0x9)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(8);
		}*/
		m_comboMainSecordDirModeCtrl.EnableWindow(FALSE);
		break;
	case 2:
		m_comboMainFirstDirModeCtr.EnableWindow(TRUE);
		m_comboMainSecordDirModeCtrl.EnableWindow(TRUE);
		if (m_struFtpCfgV40[0].byTopDirMode == 0x1)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(0);
		}
		if (m_struFtpCfgV40[0].byTopDirMode == 0x2)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(1);
		}
		if (m_struFtpCfgV40[0].byTopDirMode == 0x3)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(2);
		}
		if (m_struFtpCfgV40[0].byTopDirMode == 0x6)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(3);
			SetMainFtpSelDirShow(TRUE);
		}
		/*if (m_struFtpCfgV40[0].byTopDirMode == 0x5)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(4);
		}
		if (m_struFtpCfgV40[0].byTopDirMode == 0x6)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(5);
		}
		if (m_struFtpCfgV40[0].byTopDirMode == 0x7)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(6);
		}
		if (m_struFtpCfgV40[0].byTopDirMode == 0x8)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(7);
		}
		if (m_struFtpCfgV40[0].byTopDirMode == 0x9)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(8);
		}*/
		

		if (m_struFtpCfgV40[0].bySubDirMode == 0x1 )
		{
			m_comboMainSecordDirModeCtrl.SetCurSel(0);
		}
		if (m_struFtpCfgV40[0].bySubDirMode == 0x2 )
		{
			m_comboMainSecordDirModeCtrl.SetCurSel(1);
		}
		if (m_struFtpCfgV40[0].bySubDirMode == 0x5 )
		{
			m_comboMainSecordDirModeCtrl.SetCurSel(2);
			SetMainFtpSelSecondDirShow(TRUE);
		}
		/*if (m_struFtpCfgV40[0].bySubDirMode == 0x4 )
		{
			m_comboMainSecordDirModeCtrl.SetCurSel(3);
		}
		if (m_struFtpCfgV40[0].bySubDirMode == 0x5)
		{
			m_comboMainSecordDirModeCtrl.SetCurSel(4);			
		}
		if (m_struFtpCfgV40[0].bySubDirMode == 0x6 )
		{
			m_comboMainSecordDirModeCtrl.SetCurSel(5);
		}
		if (m_struFtpCfgV40[0].bySubDirMode == 0x7 )
		{
			m_comboMainSecordDirModeCtrl.SetCurSel(6);
		}
		if (m_struFtpCfgV40[0].bySubDirMode == 0x8 )
		{
			m_comboMainSecordDirModeCtrl.SetCurSel(7);
		}
		if (m_struFtpCfgV40[0].bySubDirMode == 0x9 )
		{
			m_comboMainSecordDirModeCtrl.SetCurSel(8);
		}*/
		break;
	default:	
		break;
	}
	m_UseFTPUpCtrl.SetCurSel(m_struFtpCfgV40[0].byEnableFTP);	
	m_dwPort = m_struFtpCfgV40[0].wFTPPort;
	char cUserTemp[NAME_LEN+1] = {0};
	char cFirstUserDir[65] = {0};
	char cSecondUserDir[65] = {0};

	memcpy(cUserTemp, m_struFtpCfgV40[0].szUserName, NAME_LEN);
	m_csUserName = cUserTemp;
	char cPawdTemp[PASSWD_LEN+1] = {0};
	memcpy(cPawdTemp, m_struFtpCfgV40[0].szPassWORD, PASSWD_LEN);
	
	m_csPassword = cPawdTemp;
	m_comboProtocalType.SetCurSel(m_struFtpCfgV40[0].byProtocolType);
	m_comboServerType.SetCurSel(m_struFtpCfgV40[0].byAddresType);
	
	if (m_struFtpCfgV40[0].byAddresType)
	{
		m_csIP = m_struFtpCfgV40[0].unionServer.struDomain.szDomain;
		GetDlgItem(IDC_STATIC_V4)->SetWindowText("域名：");
		GetDlgItem(IDC_STATIC_V6)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_IPV6_FIRST)->ShowWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_STATIC_V4)->SetWindowText("IPv4/6地址:");
		GetDlgItem(IDC_STATIC_V6)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_IPV6_FIRST)->ShowWindow(FALSE);
		if (inet_addr(m_struFtpCfgV40[0].unionServer.struAddrIP.struIp.sIpV4) == 0)
		{
			m_csIP = m_struFtpCfgV40[0].unionServer.struAddrIP.struIp.byIPv6;
		}
		else
		{
			m_csIP = m_struFtpCfgV40[0].unionServer.struAddrIP.struIp.sIpV4;
		}
		
		
	}

	memcpy(cFirstUserDir, m_struFtpCfgV40[0].szTopCustomDir, 64);
	memcpy(cSecondUserDir, m_struFtpCfgV40[0].szSubCustomDir, 64);
	m_csMainFirstUserDir = cFirstUserDir;
	m_csMainSecordUserDir = cSecondUserDir;

	m_bChkAnony = m_struFtpCfgV40[0].byEnableAnony;

	//图片命名规则 2013-09-27
	m_bFTPPicType = m_struFtpCfgV40[0].byFTPPicType;
	if (m_bFTPPicType)
	{
		char cTemp[4];
		memcpy(cTemp, &( m_struFtpCfgV40[0].struPicNameRule.byDelimiter), 1);
		memcpy(cTemp+1, "\0", 1);
		m_Delimiter.Format("%s",cTemp);
		m_NameItemCtrl.SetCurSel(0);
		m_NameElementCtrl.SetCurSel( m_struFtpCfgV40[0].struPicNameRule.byItemOrder[0]);
	}
	
    m_byPicArchivingInterval = m_struFtpCfgV40[0].byPicArchivingInterval;
    m_csPicNamePrefix.Format(_T("%s"), m_struFtpCfgV40[0].struPicNameRule.byPicNamePrefix);
    m_comPicRuleType.SetCurSel(m_struFtpCfgV40[0].byPicNameRuleType);


	//设置备份信息
	m_DirLevelCtrl2.SetCurSel(m_struFtpCfgV40[1].byDirLevel);
	temp = m_DirLevelCtrl2.GetCurSel();
	switch (temp)
	{
	case 0:	
		m_comboSubFirstDirModeCtr.EnableWindow(FALSE);
		m_comboSubSecordDirModeCtrl.EnableWindow(FALSE);
		break;
	case 1:
		m_comboSubFirstDirModeCtr.EnableWindow(TRUE); 
		if (m_struFtpCfgV40[1].byTopDirMode == 0x1)
		{
			m_comboSubFirstDirModeCtr.SetCurSel(0);
		}
		if (m_struFtpCfgV40[1].byTopDirMode == 0x2)
		{
			m_comboSubFirstDirModeCtr.SetCurSel(1);
		}
		if (m_struFtpCfgV40[1].byTopDirMode == 0x3)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(2);
		}
		if (m_struFtpCfgV40[1].byTopDirMode == 0x6)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(3);
			SetSubFtpSelDirShow(TRUE);
		}
		/*if (m_struFtpCfgV40[1].byTopDirMode == 0x5)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(4);
		}
		if (m_struFtpCfgV40[1].byTopDirMode == 0x6)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(5);
			SetSubFtpSelDirShow(TRUE);
		}
		if (m_struFtpCfgV40[1].byTopDirMode == 0x7)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(6);
		}
		if (m_struFtpCfgV40[1].byTopDirMode == 0x8)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(7);
		}
		if (m_struFtpCfgV40[1].byTopDirMode == 0x9)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(8);
		}*/
		m_comboSubSecordDirModeCtrl.EnableWindow(FALSE);
		break;
	case 2:
		m_comboSubFirstDirModeCtr.EnableWindow(TRUE);
		m_comboSubSecordDirModeCtrl.EnableWindow(TRUE);
		if (m_struFtpCfgV40[1].byTopDirMode == 0x1)
		{
			m_comboSubFirstDirModeCtr.SetCurSel(0);
		}
		if (m_struFtpCfgV40[1].byTopDirMode == 0x2)
		{
			m_comboSubFirstDirModeCtr.SetCurSel(1);
		}
		if (m_struFtpCfgV40[1].byTopDirMode == 0x3)
		{
			m_comboSubFirstDirModeCtr.SetCurSel(2);
		}
		if (m_struFtpCfgV40[1].byTopDirMode == 0x6)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(3);
			SetSubFtpSelDirShow(TRUE);
		}
		/*if (m_struFtpCfgV40[1].byTopDirMode == 0x5)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(4);
		}
		if (m_struFtpCfgV40[1].byTopDirMode == 0x6)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(5);
			SetSubFtpSelDirShow(TRUE);
		}
		if (m_struFtpCfgV40[1].byTopDirMode == 0x7)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(6);
		}
		if (m_struFtpCfgV40[1].byTopDirMode == 0x8)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(7);
		}
		if (m_struFtpCfgV40[1].byTopDirMode == 0x9)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(8);
		}*/


		if (m_struFtpCfgV40[1].bySubDirMode == 0x1 )
		{
			m_comboSubSecordDirModeCtrl.SetCurSel(0);
		}
		if (m_struFtpCfgV40[1].bySubDirMode == 0x2 )
		{
			m_comboSubSecordDirModeCtrl.SetCurSel(1);
		}
		if (m_struFtpCfgV40[1].bySubDirMode == 0x5 )
		{
			m_comboMainSecordDirModeCtrl.SetCurSel(2);
			SetSubFtpSelSecondDirShow(TRUE);
		}
		/*if (m_struFtpCfgV40[1].bySubDirMode == 0x4 )
		{
			m_comboMainSecordDirModeCtrl.SetCurSel(3);
		}
		if (m_struFtpCfgV40[1].bySubDirMode == 0x5)
		{
			m_comboMainSecordDirModeCtrl.SetCurSel(4);
			SetSubFtpSelSecondDirShow(TRUE);			
		}
		if (m_struFtpCfgV40[1].bySubDirMode == 0x6 )
		{
			m_comboMainSecordDirModeCtrl.SetCurSel(5);
		}
		if (m_struFtpCfgV40[1].bySubDirMode == 0x7 )
		{
			m_comboMainSecordDirModeCtrl.SetCurSel(6);
		}
		if (m_struFtpCfgV40[1].bySubDirMode == 0x8 )
		{
			m_comboMainSecordDirModeCtrl.SetCurSel(7);
		}
		if (m_struFtpCfgV40[1].bySubDirMode == 0x9 )
		{
			m_comboMainSecordDirModeCtrl.SetCurSel(8);
		}*/
		break;
	default:	
		break;
	}
	m_UseFTPUpCtrl2.SetCurSel(m_struFtpCfgV40[1].byEnableFTP);	
	m_dwPort2 = m_struFtpCfgV40[1].wFTPPort;
	 
	memcpy(cUserTemp, m_struFtpCfgV40[1].szUserName, NAME_LEN);
	m_csUserName2 = cUserTemp;
 
	memcpy(cPawdTemp, m_struFtpCfgV40[1].szPassWORD, PASSWD_LEN);
	
	m_csPassword2 = cPawdTemp;
	m_comboProtocalType2.SetCurSel(m_struFtpCfgV40[1].byProtocolType);
	m_comboServerType2.SetCurSel(m_struFtpCfgV40[1].byAddresType);
	
	if (m_struFtpCfgV40[1].byAddresType)
	{
		m_csIP2v6 = m_struFtpCfgV40[1].unionServer.struDomain.szDomain;

		GetDlgItem(IDC_STATIC2_V4)->SetWindowText("域名:");
		GetDlgItem(IDC_STATIC2_V6)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_IP2)->ShowWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_STATIC2_V4)->SetWindowText("IPv4/6地址:");
		GetDlgItem(IDC_STATIC2_V6)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_IP2)->ShowWindow(FALSE);
		if (inet_addr(m_struFtpCfgV40[1].unionServer.struAddrIP.struIp.sIpV4)!= 0)
		{
			m_csIP2v6 = m_struFtpCfgV40[1].unionServer.struAddrIP.struIp.sIpV4;
		}
		else
		{
			m_csIP2v6  =  m_struFtpCfgV40[1].unionServer.struAddrIP.struIp.byIPv6;
			//GetDlgItem(IDC_EDIT_IP2)->SetWindowText(m_csIP2);
		}
	}

	memset(cFirstUserDir, 0, sizeof(cFirstUserDir));
	memset(cSecondUserDir, 0, sizeof(cSecondUserDir));
	memcpy(cFirstUserDir, m_struFtpCfgV40[1].szTopCustomDir, 64);
	memcpy(cSecondUserDir, m_struFtpCfgV40[1].szSubCustomDir, 64);

	m_csSubFirstUserDir = cFirstUserDir;
	m_csSubSecordUserDir = cSecondUserDir;

	m_bChkAnony2 = m_struFtpCfgV40[1].byEnableAnony;

	//图片命名规则 2013-09-27
	m_bFTPPicType2 = m_struFtpCfgV40[1].byFTPPicType;
	if (m_bFTPPicType2)
	{
		char cTemp2[4];
		memcpy(cTemp2, &( m_struFtpCfgV40[1].struPicNameRule.byDelimiter), 1);
		memcpy(cTemp2+1, "\0", 1);
		m_Delimiter2.Format("%s",cTemp2);
		m_NameItemCtrl2.SetCurSel(0);
		m_NameElementCtrl2.SetCurSel( m_struFtpCfgV40[1].struPicNameRule.byItemOrder[0]);
	}

    m_byPicArchivingInterval2 = m_struFtpCfgV40[1].byPicArchivingInterval;
    m_csPicNamePrefix2.Format(_T("%s"), m_struFtpCfgV40[1].struPicNameRule.byPicNamePrefix);
    m_comPicRuleType2.SetCurSel(m_struFtpCfgV40[1].byPicNameRuleType);
	UpdateData(FALSE);
	//UpdateWindow();
}

void CDlgJpegCaptureCfg::GetFtpV40Info()
{
	//FTP配置
	int temp, tmp1, tmp2;
    temp = m_DirLevelCtrl.GetCurSel();
//	memset(&m_struFtpCfgV40,0,sizeof(m_struFtpCfgV40));
	m_struFtpCfgV40[0].struStruceHead.wLength = sizeof(m_struFtpCfgV40[0]);
    switch (temp)
    {
    case 0:
		m_struFtpCfgV40[0].byDirLevel = 0;
        break;
    case 1:
		m_struFtpCfgV40[0].byDirLevel = 1;
		tmp1 = m_comboMainFirstDirModeCtr.GetCurSel();
        if (tmp1 == 0)
        {
			m_struFtpCfgV40[0].byTopDirMode = 0x1;
        }
        if (tmp1 == 1)
        {
			m_struFtpCfgV40[0].byTopDirMode = 0x2;
        }
        if (tmp1 == 2)
        {
			m_struFtpCfgV40[0].byTopDirMode = 0x3;
        }
		if (tmp1 == 3)
		{
			//一集目录自定义发往设备的值是0x6
			m_struFtpCfgV40[0].byTopDirMode = 0x6;
		}
		/*
		if (tmp1 == 4)
		{
			m_struFtpCfgV40[0].byTopDirMode = 0x5;
		}
		if (tmp1 == 5)
		{
			m_struFtpCfgV40[0].byTopDirMode = 0x6;
		}
		if (tmp1 == 6)
		{
			m_struFtpCfgV40[0].byTopDirMode = 0x7;
		}
		if (tmp1 == 7)
		{
			m_struFtpCfgV40[0].byTopDirMode = 0x8;
		}
		if (tmp1 == 8)
		{
			m_struFtpCfgV40[0].byTopDirMode = 0x9;
		}*/
        break;
    case 2:
		m_struFtpCfgV40[0].byDirLevel = 2;
        tmp1 = m_comboMainFirstDirModeCtr.GetCurSel();
        if (tmp1 == 0)
        {
			m_struFtpCfgV40[0].byTopDirMode = 0x1;
        }
        if (tmp1 == 1)
        {
			m_struFtpCfgV40[0].byTopDirMode = 0x2;
        }
        if (tmp1 == 2)
        {
			m_struFtpCfgV40[0].byTopDirMode = 0x3;
        }
		if (tmp1 == 3)
		{
			//一集目录自定义发往设备的值是0x6
			m_struFtpCfgV40[0].byTopDirMode = 0x6;
		}
		/*if (tmp1 == 4)
		{
			m_struFtpCfgV40[0].byTopDirMode = 0x5;
		}
		if (tmp1 == 5)
		{
			m_struFtpCfgV40[0].byTopDirMode = 0x6;
		}
		if (tmp1 == 6)
		{
			m_struFtpCfgV40[0].byTopDirMode = 0x7;
		}
		if (tmp1 == 7)
		{
			m_struFtpCfgV40[0].byTopDirMode = 0x8;
		}
		if (tmp1 == 8)
		{
			m_struFtpCfgV40[0].byTopDirMode = 0x9;
		}*/

		tmp2 = m_comboMainSecordDirModeCtrl.GetCurSel();
        if (tmp2 == 0)
        {
			m_struFtpCfgV40[0].bySubDirMode = 0x1;
        }
        if (tmp2 == 1)
        {
			m_struFtpCfgV40[0].bySubDirMode = 0x2;
        }
		if (tmp2 == 2)
		{
			//二级目录自定义时发往设备的值是0X5
			m_struFtpCfgV40[0].bySubDirMode = 0x5;
		}
		/*if (tmp2 == 3)
		{
			m_struFtpCfgV40[0].bySubDirMode = 0x4;
		}
		if (tmp2 == 4)
		{
			m_struFtpCfgV40[0].bySubDirMode = 0x5;
		}
		if (tmp2 == 5)
		{
			m_struFtpCfgV40[0].bySubDirMode = 0x6;
		}
		if (tmp2 == 6)
		{
			m_struFtpCfgV40[0].bySubDirMode = 0x7;
		}
		if (tmp2 == 7)
		{
			m_struFtpCfgV40[0].bySubDirMode = 0x8;
		}
		if (tmp2 == 8)
		{
			m_struFtpCfgV40[0].bySubDirMode = 0x9;
		}*/
    default:
        break;
    }
	
    m_struFtpCfgV40[0].byAddresType = m_comboServerType.GetCurSel();
	m_struFtpCfgV40[0].byProtocolType = m_comboProtocalType.GetCurSel();

	memcpy(m_struFtpCfgV40[0].szTopCustomDir, m_csMainFirstUserDir, 64);
	memcpy(m_struFtpCfgV40[0].szSubCustomDir, m_csMainSecordUserDir, 64);

	m_struFtpCfgV40[0].byEnableFTP = m_UseFTPUpCtrl.GetCurSel();
	m_struFtpCfgV40[0].byEnableAnony = m_bChkAnony;
	
	m_struFtpCfgV40[0].wFTPPort = (WORD)m_dwPort;

	memcpy(m_struFtpCfgV40[0].szPassWORD, m_csPassword, PASSWD_LEN);
	memcpy(m_struFtpCfgV40[0].szUserName, m_csUserName, NAME_LEN);

	if (m_comboServerType.GetCurSel())
	{
		sprintf((char*)m_struFtpCfgV40[0].unionServer.struDomain.szDomain, m_csIP, 64);
	}
	else
	{
		if (m_csIP.Find(":") == -1)
		{
			sprintf((char*)(&m_struFtpCfgV40[0])->unionServer.struAddrIP.struIp.sIpV4,m_csIP,16);
		}
		else
		{
			sprintf((char*)m_struFtpCfgV40[0].unionServer.struAddrIP.struIp.byIPv6,m_csIP,128);
		}
		
		
	}
	m_struFtpCfgV40[0].byType = 0;
	
    m_struFtpCfgV40[0].byPicArchivingInterval = m_byPicArchivingInterval;
    memcpy(m_struFtpCfgV40[0].struPicNameRule.byPicNamePrefix, m_csPicNamePrefix, PICNAME_PREFIX);
    m_struFtpCfgV40[0].byPicNameRuleType = m_comPicRuleType.GetCurSel();
    
// 	//2013-09-27 命名规则
// 	int num = m_NameItemCtrl.GetCurSel();
// 	m_struFtpCfgV40[0].struPicNameRule.byItemOrder[num] = m_NameElementCtrl.GetCurSel();
// 	if ("" != m_Delimiter)
// 	{
// 		m_struFtpCfgV40[0].struPicNameRule.byDelimiter = m_Delimiter.GetAt(0);
// 	}

	//FTP配置
	
    temp = m_DirLevelCtrl2.GetCurSel();
	m_struFtpCfgV40[1].struStruceHead.wLength = sizeof(m_struFtpCfgV40[0]);
    switch (temp)
    {
    case 0:
		m_struFtpCfgV40[1].byDirLevel = 0;
        break;
    case 1:
	    m_struFtpCfgV40[1].byDirLevel = 1;
		tmp1 = m_comboSubFirstDirModeCtr.GetCurSel();
        if (tmp1 == 0)
        {
			m_struFtpCfgV40[1].byTopDirMode = 0x1;
        }
        if (tmp1 == 1)
        {
			m_struFtpCfgV40[1].byTopDirMode = 0x2;
        }
        if (tmp1 == 2)
        {
			m_struFtpCfgV40[1].byTopDirMode = 0x3;
        }
		if (tmp1 == 3)
        {
			//一集目录自定义发往设备的值是0x6
			m_struFtpCfgV40[1].byTopDirMode = 0x6;
        }
		/*if (tmp1 == 4)
        {
			m_struFtpCfgV40[1].byTopDirMode = 0x5;
        }
		if (tmp1 == 5)
        {
			m_struFtpCfgV40[1].byTopDirMode = 0x6;
        }
		if (tmp1 == 6)
        {
			m_struFtpCfgV40[1].byTopDirMode = 0x7;
        }
		if (tmp1 == 7)
        {
			m_struFtpCfgV40[1].byTopDirMode = 0x8;
        }
		if (tmp1 == 8)
        {
			m_struFtpCfgV40[1].byTopDirMode = 0x9;
        }*/
		break;
    case 2:
		m_struFtpCfgV40[01].byDirLevel = 2;
        tmp1 = m_comboSubFirstDirModeCtr.GetCurSel();
        if (tmp1 == 0)
        {
			m_struFtpCfgV40[1].byTopDirMode = 0x1;
        }
        if (tmp1 == 1)
        {
			m_struFtpCfgV40[1].byTopDirMode = 0x2;
        }
        if (tmp1 == 2)
        {
			m_struFtpCfgV40[1].byTopDirMode = 0x3;
        }
		if (tmp1 == 3)
        {
			//一集目录自定义发往设备的值是0x6
			m_struFtpCfgV40[1].byTopDirMode = 0x6;
        }
	/*	if (tmp1 == 4)
        {
			m_struFtpCfgV40[1].byTopDirMode = 0x5;
        }
		if (tmp1 == 5)
        {
			m_struFtpCfgV40[1].byTopDirMode = 0x6;
        }
		if (tmp1 == 6)
        {
			m_struFtpCfgV40[1].byTopDirMode = 0x7;
        }
		if (tmp1 == 7)
        {
			m_struFtpCfgV40[1].byTopDirMode = 0x8;
        }
		if (tmp1 == 8)
        {
			m_struFtpCfgV40[1].byTopDirMode = 0x9;
        }*/


		tmp2 = m_comboSubSecordDirModeCtrl.GetCurSel();
        if (tmp2 == 0)
        {
			m_struFtpCfgV40[1].bySubDirMode = 0x1;
        }
        if (tmp2 == 1)
        {
			m_struFtpCfgV40[1].bySubDirMode = 0x2;
        }
		if (tmp2 == 2)
        {
			//二级目录自定义发往设备的值是0x5
			m_struFtpCfgV40[1].bySubDirMode = 0x5;
        }
	/*	if (tmp2 == 3)
        {
			m_struFtpCfgV40[1].bySubDirMode = 0x4;
        }
		if (tmp2 == 4)
        {
			m_struFtpCfgV40[1].bySubDirMode = 0x5;
        }
		if (tmp2 == 5)
        {
			m_struFtpCfgV40[1].bySubDirMode = 0x6;
        }
		if (tmp2 == 6)
        {
			m_struFtpCfgV40[1].bySubDirMode = 0x7;
        }
		if (tmp2 == 7)
        {
			m_struFtpCfgV40[1].bySubDirMode = 0x8;
        }
		if (tmp2 == 8)
        {
			m_struFtpCfgV40[1].bySubDirMode = 0x9;
        }*/
    default:
        break;
    }
	
    m_struFtpCfgV40[1].byAddresType = m_comboServerType2.GetCurSel();
	m_struFtpCfgV40[1].byProtocolType = m_comboProtocalType2.GetCurSel();

	memcpy(m_struFtpCfgV40[1].szTopCustomDir, m_csSubFirstUserDir, 64);
	memcpy(m_struFtpCfgV40[1].szSubCustomDir, m_csSubSecordUserDir, 64);
	
	m_struFtpCfgV40[1].byEnableFTP = m_UseFTPUpCtrl2.GetCurSel();
	
	m_struFtpCfgV40[1].wFTPPort = (WORD)m_dwPort2;

	memcpy(m_struFtpCfgV40[1].szPassWORD, m_csPassword2, PASSWD_LEN);
	memcpy(m_struFtpCfgV40[1].szUserName, m_csUserName2, NAME_LEN);
	m_struFtpCfgV40[1].byEnableAnony = m_bChkAnony2;//2013-05-22
	if (m_comboServerType2.GetCurSel())
	{
		sprintf((char*)m_struFtpCfgV40[1].unionServer.struDomain.szDomain, m_csIP2v6, 64);
	}
	else
	{
		sprintf((char*)m_struFtpCfgV40[1].unionServer.struAddrIP.struIp.byIPv6,m_csIP2v6,128);
		sprintf((char*)(&m_struFtpCfgV40[1])->unionServer.struAddrIP.struIp.sIpV4,m_csIP2,16);
 		if (m_csIP2v6.Find(":") == -1)
		{
			sprintf((char*)(&m_struFtpCfgV40[1])->unionServer.struAddrIP.struIp.sIpV4,m_csIP2v6,16);
		}
		else
		{
			sprintf((char*)m_struFtpCfgV40[1].unionServer.struAddrIP.struIp.byIPv6,m_csIP2v6,128);
		}
	}
	m_struFtpCfgV40[1].byType = 1;

    m_struFtpCfgV40[1].byPicArchivingInterval = m_byPicArchivingInterval2;
    memcpy(m_struFtpCfgV40[1].struPicNameRule.byPicNamePrefix, m_csPicNamePrefix2, PICNAME_PREFIX);
    m_struFtpCfgV40[1].byPicNameRuleType = m_comPicRuleType2.GetCurSel();
// 	//2013-09-27 命名规则
// 	int num2 = m_NameItemCtrl2.GetCurSel();
// 	m_struFtpCfgV40[1].struPicNameRule.byItemOrder[num2] = m_NameElementCtrl2.GetCurSel();
// 	if ("" != m_Delimiter)
// 	{
// 		m_struFtpCfgV40[1].struPicNameRule.byDelimiter = m_Delimiter2.GetAt(0);
// 	}
}

void CDlgJpegCaptureCfg::OnEditchangeComboServertype2() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgJpegCaptureCfg::OnEditchangeComboServertype() 
{
	// TODO: Add your control notification handler code here
	if (m_comboServerType.GetCurSel())
	{
		GetDlgItem(IDC_EDIT_IPV6_FIRST)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_V6)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_V4)->SetWindowText("IPv4地址:");
		UpdateWindow();
	}
	else
	{
		GetDlgItem(IDC_EDIT_IPV6_FIRST)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_V6)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_V4)->SetWindowText("域名:");
		UpdateWindow();
	}
}

void CDlgJpegCaptureCfg::OnSelchangeComboServertype() 
{
	// TODO: Add your control notification handler code here
	if (m_comboServerType.GetCurSel())
	{
		GetDlgItem(IDC_EDIT_IPV6_FIRST)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_V6)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_V4)->SetWindowText("域名:");
		UpdateWindow();
	}
	else
	{
		GetDlgItem(IDC_EDIT_IPV6_FIRST)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_V6)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_V4)->SetWindowText("IPv4/6地址:");
		UpdateWindow();
	}
}

void CDlgJpegCaptureCfg::OnSelchangeComboServertype2() 
{
	// TODO: Add your control notification handler code here
	if (m_comboServerType2.GetCurSel())
	{
		GetDlgItem(IDC_EDIT_IP2)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC2_V6)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC2_V4)->SetWindowText("域名:");
	}
	else
	{
		GetDlgItem(IDC_EDIT_IP2)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC2_V6)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC2_V4)->SetWindowText("IPv4/6地址:");
	}
}

void CDlgJpegCaptureCfg::SetMainFtpSelDirShow(BOOL bShow )
{
  	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_STATIC_SELF_FIR_DIR)->ShowWindow(bShow);
	GetDlgItem(IDC_EDIT_FIRST_USERDIR)->ShowWindow(bShow);
}

void CDlgJpegCaptureCfg::SetMainFtpSelSecondDirShow(BOOL bShow )
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_STATIC_SELF_SEC_DIR)->ShowWindow(bShow);
	GetDlgItem(IDC_EDIT_SECOND_USERDIR)->ShowWindow(bShow);
}

void CDlgJpegCaptureCfg::SetSubFtpSelDirShow(BOOL bShow )
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_STATIC_SELF_FIR_DIR_SUB)->ShowWindow(bShow);
	GetDlgItem(IDC_EDIT_SUB_FIRST_USERDIR)->ShowWindow(bShow);
}

void CDlgJpegCaptureCfg::SetSubFtpSelSecondDirShow(BOOL bShow )
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_STATIC_SELF_SEC_DIR_SUB)->ShowWindow(bShow);
	GetDlgItem(IDC_EDIT_SUB_SECOND_USERDIR)->ShowWindow(bShow);
}

void CDlgJpegCaptureCfg::OnSelchangeComboSubDirLevel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	SetSubFtpSelDirShow(FALSE);
	SetSubFtpSelSecondDirShow(FALSE);
	int temp;
	temp = m_DirLevelCtrl2.GetCurSel();
	switch (temp)
	{
	case 0:	
		m_comboSubFirstDirModeCtr.EnableWindow(FALSE);
        m_comboSubSecordDirModeCtrl.EnableWindow(FALSE);		
		break;
	case 1:
		m_comboSubFirstDirModeCtr.EnableWindow(TRUE); 
		m_comboSubSecordDirModeCtrl.EnableWindow(FALSE);
		break;
	case 2:
		m_comboSubFirstDirModeCtr.EnableWindow(TRUE);
		m_comboSubSecordDirModeCtrl.EnableWindow(TRUE);
		break;
	default:	
		break;
	}
	
	UpdateData(FALSE);
	
}

//2013-09-27 命名规则
void CDlgJpegCaptureCfg::OnButjpegname() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	m_struFtpCfgV40[0].byFTPPicType = m_bFTPPicType;
	if (!m_bFTPPicType)
	{
		return;
	}

	int temp = m_NameItemCtrl.GetCurSel();
	m_struFtpCfgV40[0].struPicNameRule.byItemOrder[temp] = m_NameElementCtrl.GetCurSel();
	if ("" != m_Delimiter)
	{
		m_struFtpCfgV40[0].struPicNameRule.byDelimiter = m_Delimiter.GetAt(0);
	}
}

void CDlgJpegCaptureCfg::OnButjpegname2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	m_struFtpCfgV40[1].byFTPPicType = m_bFTPPicType2;
	if (!m_bFTPPicType2)
	{
		return;
	}
	
	int temp = m_NameItemCtrl2.GetCurSel();
	m_struFtpCfgV40[1].struPicNameRule.byItemOrder[temp] = m_NameElementCtrl2.GetCurSel();
	if ("" != m_Delimiter2)
	{
		m_struFtpCfgV40[1].struPicNameRule.byDelimiter = m_Delimiter2.GetAt(0);
	}
}

//2013-09-27
void CDlgJpegCaptureCfg::OnSelchangeCombonameitemFtp() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	int temp = m_NameItemCtrl.GetCurSel();
	m_NameElementCtrl.SetCurSel(m_struFtpCfgV40[0].struPicNameRule.byItemOrder[temp]);
	
	UpdateData(FALSE);	
}

void CDlgJpegCaptureCfg::OnSelchangeCombonameitemFtp2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	int temp = m_NameItemCtrl2.GetCurSel();
	m_NameElementCtrl2.SetCurSel(m_struFtpCfgV40[1].struPicNameRule.byItemOrder[temp]);
	
	UpdateData(FALSE);	
}

BOOL CDlgJpegCaptureCfg::CheckInitParam()
{
    OnButtonUpdate();
    OnButtonUpdateSched();
    OnButtonUpdateFtp();
    return TRUE;
}

void CDlgJpegCaptureCfg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	OnButtonUpdate();
	// Do not call CDialog::OnPaint() for painting messages
}

DWORD WINAPI CDlgJpegCaptureCfg::GetFtpServerTestInfoThread(LPVOID lpArg)
{
	CDlgJpegCaptureCfg* pThis = reinterpret_cast<CDlgJpegCaptureCfg*>(lpArg);
	DWORD dwState = 0;
	CString csErrInfo;
	while (1)
	{
		
		if (!NET_DVR_GetRemoteConfigState(pThis->m_lFtpServerTest, &dwState))
		{
			g_pMainDlg->AddLog(pThis->m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GetRemoteConfigState NET_DVR_FIND_NAS_DIRECTORY ");
			pThis->GetDlgItem(IDC_STATIC_FTP_SERVER_TEST)->SetWindowText("Get state Fail!");
			NET_DVR_StopRemoteConfig(pThis->m_lFtpServerTest);
			return -1;
		}
		else
		{
			if (dwState == PROCESSING)
			{
				pThis->GetDlgItem(IDC_STATIC_FTP_SERVER_TEST)->SetWindowText("Testing...");
				Sleep(1000);
			}
			else if (dwState == PROCESS_SUCCESS)
			{
				pThis->GetDlgItem(IDC_STATIC_FTP_SERVER_TEST)->SetWindowText("Test Success!");
				break;
			}
			else if (dwState == PROCESS_EXCEPTION)
			{
				pThis->GetDlgItem(IDC_STATIC_FTP_SERVER_TEST)->SetWindowText("Test Exception!!");
				break;
			}
			else
			{
				csErrInfo.Format("Test Fail %d", dwState);
				pThis->GetDlgItem(IDC_STATIC_FTP_SERVER_TEST)->SetWindowText(csErrInfo);
				break;
			}
		}
		
	}
	if (-1 != pThis->m_lFtpServerTest)
	{
		if (!NET_DVR_StopRemoteConfig(pThis->m_lFtpServerTest))
		{
			g_pMainDlg->AddLog(pThis->m_dwDevIndex, OPERATION_FAIL_T, "Stop Remote Config Failed");
		}
		else
		{
			g_pMainDlg->AddLog(pThis->m_dwDevIndex, OPERATION_SUCC_T, "Stop Remote Config Successful");
			pThis->m_lFtpServerTest = -1;
		}
	}
	return 0 ;
}

void CDlgJpegCaptureCfg::OnBtnFtpServerTest() 
{
	UpdateData(TRUE);
	memset(&m_struFtpServerTest, 0, sizeof(m_struFtpServerTest));
	m_struFtpServerTest.dwSize = sizeof(m_struFtpServerTest);
	m_struFtpServerTest.unionServerPara.struFtpPara.struFtpPara.dwSize = sizeof(m_struFtpServerTest.unionServerPara.struFtpPara.struFtpPara);
	m_struFtpServerTest.unionServerPara.struFtpPara.struFtpPara.byEnableFTP = m_UseFTPUpCtrl.GetCurSel();
	m_struFtpServerTest.unionServerPara.struFtpPara.struFtpPara.byProtocolType = m_comboProtocalType.GetCurSel();
	m_struFtpServerTest.unionServerPara.struFtpPara.struFtpPara.wFTPPort = (WORD)m_dwPort;
	if (m_comboServerType.GetCurSel())
	{
		sprintf((char *)m_struFtpServerTest.unionServerPara.struFtpPara.struFtpPara.unionServer.struDomain.szDomain, m_csIP, 64);
	}
	else
	{
		if (m_csIP.Find(":") == -1)
		{
			sprintf(m_struFtpServerTest.unionServerPara.struFtpPara.struFtpPara.unionServer.struAddrIP.struIp.sIpV4,m_csIP,16);
		}
		else
		{
			sprintf((char *)m_struFtpServerTest.unionServerPara.struFtpPara.struFtpPara.unionServer.struAddrIP.struIp.byIPv6,m_csIP,128);
		}	
	}
	memcpy(m_struFtpServerTest.unionServerPara.struFtpPara.struFtpPara.szPassWORD, m_csPassword, PASSWD_LEN);
	memcpy(m_struFtpServerTest.unionServerPara.struFtpPara.struFtpPara.szUserName,m_csUserName,NAME_LEN);
	memcpy(m_struFtpServerTest.unionServerPara.struFtpPara.struFtpPara.szTopCustomDir, m_csMainFirstUserDir, 64);
	memcpy(m_struFtpServerTest.unionServerPara.struFtpPara.struFtpPara.szSubCustomDir, m_csMainSecordUserDir, 64);
	
	m_struFtpServerTest.unionServerPara.struFtpPara.struFtpPara.byDirLevel = m_DirLevelCtrl.GetCurSel();
	if (m_comboMainFirstDirModeCtr.GetCurSel() == 3)
	{
		m_struFtpServerTest.unionServerPara.struFtpPara.struFtpPara.byTopDirMode = 6;
	}
	else
	{
		m_struFtpServerTest.unionServerPara.struFtpPara.struFtpPara.byTopDirMode = m_comboMainFirstDirModeCtr.GetCurSel() + 1;
	}
	
	if (m_comboMainSecordDirModeCtrl.GetCurSel() == 2)
	{
		m_struFtpServerTest.unionServerPara.struFtpPara.struFtpPara.bySubDirMode = 5;
	}
	else
	{
		m_struFtpServerTest.unionServerPara.struFtpPara.struFtpPara.bySubDirMode = m_comboMainSecordDirModeCtrl.GetCurSel() + 1;
	}
	
	m_struFtpServerTest.unionServerPara.struFtpPara.struFtpPara.byType = 0;
	m_struFtpServerTest.unionServerPara.struFtpPara.struFtpPara.byEnableAnony = m_bChkAnony;
	m_struFtpServerTest.unionServerPara.struFtpPara.struFtpPara.byAddresType = m_comboServerType.GetCurSel();
	
	
	m_lFtpServerTest = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_FTP_SERVER_TEST, &m_struFtpServerTest, sizeof(m_struFtpServerTest), NULL, this);
	if (m_lFtpServerTest >= 0)
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "Start Remote Config successfully");
		DWORD dwThreadId;
		m_hFtpServerTest = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(GetFtpServerTestInfoThread), this, 0, &dwThreadId);
	} 
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "Start Remote Config failed");
		return;
	}
	
}
