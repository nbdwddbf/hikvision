/**********************************************************
FileName:    DlgPlayEvent.cpp
Description: remote event play back      
Date:        2009/05/17
Note: 		  
Modification History:      
<version> <time>         <desc>
<1.0    > <2009/05/17>       <created>
***********************************************************/


#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgPlayEvent.h"


// CDlgPlayEvent dialog
//BOOL g_bRmtCapPic = FALSE;
CDlgPlayEvent* g_pDlgPlayEvent;

char szEventMap[][32] = 
{
	"TRAVERSE_PLANE", 
		"ENTER_AREA",				
		"EXIT_AREA",				
		"INTRUSION",			
		"LOITER",				 
		"LEFT_TAKE",	
		"PARKING",			
		"RUN",					
		"High DENSITY",			
		"STICK UP",
		"INSTALL SCANNER",
		"OPERATE OVERTIME",
		"FACE DETECT",
		"LEFT",
		"TAKE",
		"LEAVE_POSITION",
		"TRAIL",
		"NULL",
		"NULL",
		"FALL_DOWN",
		"OBJECT_PASTE",
		"FACE_CAPTURE",
		"MULTI_FACES",
		"AUDIO_ABNORMAL"
};
//#define CALLBACK_PLAY
/*********************************************************
Function:	PlayDataCallBack
Description:		
Input:		lPlayHandle, playback handle;dwDataType,data type,data head or stream;pBuffer,data buffer;dwBufSize,data size;dwUser,user data;
Output:	
Return:	
**********************************************************/
extern void CALLBACK PlayDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize,DWORD dwUser);


/*********************************************************
Function:	GetEventThread
Desc:		
Input:		pParam, point to event dialog
Output:	
Return:	
**********************************************************/
UINT GetEventThread(LPVOID pParam)
{
	LONG lRet = -1;
	NET_DVR_SEARCH_EVENT_RET_V50 struEventInfo;
	char szTmp[36] = {0};
	char szTmp1[256] = {0};
    char szDetail[4 * 512] = { 0 };
	char szLan[1024] = {0};
	int iSize = 0;
    int i = 0;
    int iCount = 0;
	CString strFileIndex;
    CString csTmp;

    CString strFileName;
	
	while (g_pDlgPlayEvent->m_IsQuit)
	{
        memset(szTmp, 0, 36);
        memset(szTmp1, 0, 36);
        memset(&struEventInfo, 0, sizeof(NET_DVR_SEARCH_EVENT_RET_V50));
        lRet = NET_DVR_FindNextEvent_V50(g_pDlgPlayEvent->m_lFileHandle, &struEventInfo);
		//lRet = NET_DVR_FindNextEvent_V40(g_pDlgPlayEvent->m_lFileHandle, &struEventInfo);
		if (lRet == NET_DVR_FILE_SUCCESS)
		{		
			switch(struEventInfo.wMajorType)
			{
			case EVENT_MOT_DET:
				sprintf(szTmp, "Motdet");
				sprintf(szTmp1, "%d",struEventInfo.uSeniorRet.struMotionRet.dwMotDetNo);
				break;
			case EVENT_ALARM_IN:
				sprintf(szTmp, "AlarmIn ");
				sprintf(szTmp1, "%d",struEventInfo.uSeniorRet.struAlarmRet.dwAlarmInNo);
				break;
			case EVENT_VCA_BEHAVIOR:
                if (struEventInfo.wMinorType == 20)
                {
                    strncpy(szEventMap[struEventInfo.wMinorType], "Object Paste", sizeof(szEventMap[struEventInfo.wMinorType]));
                }
				sprintf(szTmp, "Vca Behavior %s", szEventMap[struEventInfo.wMinorType]);
				sprintf(szTmp1, "ch%d rule%d %s",struEventInfo.uSeniorRet.struVcaRet.dwChanNo, 
					struEventInfo.uSeniorRet.struVcaRet.byRuleID,\
					(char *)(struEventInfo.uSeniorRet.struVcaRet.byRuleName));
				break;
			case EVENT_STREAM_INFO:
				sprintf(szTmp, "Stream ID");
				sprintf(szTmp1, "type:%d size:%dMB lock flag:%d position:%d tapeIndex:%s", struEventInfo.uSeniorRet.struStreamIDRet.dwRecordType, 
					struEventInfo.uSeniorRet.struStreamIDRet.dwRecordLength/1048576, struEventInfo.uSeniorRet.struStreamIDRet.byLockFlag,
                    struEventInfo.uSeniorRet.struStreamIDRet.byPosition, struEventInfo.uSeniorRet.struStreamIDRet.byTapeIndex);
				strFileIndex.Format("%d", struEventInfo.uSeniorRet.struStreamIDRet.dwFileIndex);
                strFileName.Format("%s", struEventInfo.uSeniorRet.struStreamIDRet.byFileNameEx);
				break;
			case EVENT_VCA_DETECTION:
				sprintf(szTmp, "Vca Detect");
				break;
            case EVENT_POS:
                sprintf(szTmp, "POS Event");
                break;
            case EVENT_IOT_CASE:
                sprintf(szTmp, "IOT Event");
                sprintf(szTmp1, "ch%d", struEventInfo.uSeniorRet.struIOTRet.dwChanNo);
                break;
			default:
				sprintf(szTmp, "Unknown Event%d", struEventInfo.wMajorType);
				break;
			}			
			g_pDlgPlayEvent->m_listRemoteFile.InsertItem(g_pDlgPlayEvent->m_iFileNum, szTmp,0);			
			g_pDlgPlayEvent->m_listRemoteFile.SetItemText(g_pDlgPlayEvent->m_iFileNum, 3, szTmp1);	
            sprintf(szTmp, "%04d%02d%02d%02d%02d%02d", struEventInfo.struStartTime.wYear, \
                struEventInfo.struStartTime.byMonth, struEventInfo.struStartTime.byDay, \
                struEventInfo.struStartTime.byHour, struEventInfo.struStartTime.byMinute, \
                struEventInfo.struStartTime.bySecond);
            g_pDlgPlayEvent->m_listRemoteFile.SetItemText(g_pDlgPlayEvent->m_iFileNum, 1, szTmp);
            sprintf(szTmp, "%04d%02d%02d%02d%02d%02d", struEventInfo.struEndTime.wYear, struEventInfo.struEndTime.byMonth, \
                struEventInfo.struEndTime.byDay, struEventInfo.struEndTime.byHour, \
                struEventInfo.struEndTime.byMinute, struEventInfo.struEndTime.bySecond);
            g_pDlgPlayEvent->m_listRemoteFile.SetItemText(g_pDlgPlayEvent->m_iFileNum, 2, szTmp);
            g_pDlgPlayEvent->m_listRemoteFile.SetItemText(g_pDlgPlayEvent->m_iFileNum, 5, strFileIndex);

            if (strcmp(struEventInfo.struAddr.struIP.sIpV4, "") && struEventInfo.struAddr.struIP.sIpV4 != NULL)
            {
                csTmp.Format("%s", struEventInfo.struAddr.struIP.sIpV4);
            }
            else
            {
                csTmp.Format("%s", (char *)struEventInfo.struAddr.struIP.byIPv6);
            }
            g_pDlgPlayEvent->m_listRemoteFile.SetItemText(g_pDlgPlayEvent->m_iFileNum, 6, csTmp);
            csTmp.Format("%d", struEventInfo.struAddr.wPort);
            g_pDlgPlayEvent->m_listRemoteFile.SetItemText(g_pDlgPlayEvent->m_iFileNum, 7, csTmp);
            g_pDlgPlayEvent->m_listRemoteFile.SetItemText(g_pDlgPlayEvent->m_iFileNum, 8, strFileName);

            memset(szDetail, 0, 4 * 512);
			iSize = 0;
			for (i=0; i<MAX_CHANNUM_V40; i++)
			{
                if (struEventInfo.wChan[i] != 0xffff)
                {
                    sprintf(szDetail + iSize * 4, "%3d,", struEventInfo.wChan[i]);
                    iSize++;
                }
                else
                {
                    break;
                }
			}
			g_pDlgPlayEvent->m_listRemoteFile.SetItemText(g_pDlgPlayEvent->m_iFileNum, 4, szDetail);
			g_pDlgPlayEvent->m_iFileNum++;
			TRACE("%d\n", g_pDlgPlayEvent->m_iFileNum);
		}
		else
		{
			if (lRet == NET_DVR_ISFINDING)
			{
				Sleep(5);
				continue;
			}
			if ((lRet == NET_DVR_NOMOREFILE) || (lRet == NET_DVR_FILE_NOFIND))
			{
				g_StringLanType(szLan, "查找", "Search");
				g_pDlgPlayEvent->GetDlgItem(IDC_BTN_EVENT_SEARCH_LIST)->SetWindowText(szLan);
				g_pDlgPlayEvent->m_bSearching = FALSE;
				(g_pDlgPlayEvent->GetDlgItem(IDC_STATIC_EVENT_SEARCH_STATE))->ShowWindow(SW_HIDE);
				if (g_pDlgPlayEvent->m_iFileNum > 0)
				{
					g_pMainDlg->AddLog(g_pDlgPlayEvent->m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_FindNextEvent_V50 file num[%d]", g_pDlgPlayEvent->m_iFileNum);
					g_StringLanType(szLan, "获取文件列表成功, 所有文件已列出", "Finish to get file list, and documents have all been listed");
					AfxMessageBox(szLan);
				}
				else
				{
					g_StringLanType(szLan, "搜索结束, 没有搜到文件", "Finish to get file list, and There is no record file");
					AfxMessageBox(szLan);
				}
				
				g_pDlgPlayEvent->m_iFileNum = 0;
				if (g_pDlgPlayEvent->m_lPlayHandle == -1)
				{
					g_pDlgPlayEvent->SetStopState();
					g_pDlgPlayEvent->SetStopStateIDTime();
					g_pDlgPlayEvent->GetDlgItem(IDC_BTN_EVENT_FILE_PLAY)->EnableWindow(FALSE);
					g_pDlgPlayEvent->GetDlgItem(IDC_BTN_EVENT_FILE_PLAY_BY_ID_AND_TIME)->EnableWindow(FALSE);
				}
				break;
			}
			else
			{
				g_pDlgPlayEvent->GetDlgItem(IDC_BTN_EVENT_SEARCH_LIST)->SetWindowText("Search");
				g_pDlgPlayEvent->m_bSearching = FALSE;
				(g_pDlgPlayEvent->GetDlgItem(IDC_STATIC_EVENT_SEARCH_STATE))->ShowWindow(SW_HIDE);
				g_StringLanType(szLan, "由于服务器忙或网络故障, 搜索异常结束", "Since the server is busy, or network failure, abnormal termination of access file list");
				AfxMessageBox(szLan);
				g_pDlgPlayEvent->m_iFileNum = 0;
				if (g_pDlgPlayEvent->m_lPlayHandle == -1)
				{
					g_pDlgPlayEvent->SetStopState();
					g_pDlgPlayEvent->SetStopStateIDTime();
					g_pDlgPlayEvent->GetDlgItem(IDC_BTN_EVENT_FILE_PLAY)->EnableWindow(FALSE);
					g_pDlgPlayEvent->GetDlgItem(IDC_BTN_EVENT_FILE_PLAY_BY_ID_AND_TIME)->EnableWindow(FALSE);
				}
				break;
			}
		}
	}
	NET_DVR_FindClose(g_pDlgPlayEvent->m_lFileHandle);
	//	TerminateThread(g_pDlgPlayEvent->m_hFileThread, 0);
	CloseHandle(g_pDlgPlayEvent->m_hFileThread);
	g_pDlgPlayEvent->m_hFileThread = NULL;	
	return 0;
}

/*********************************************************
Function:	CDlgPlayEvent
Desc:		Constructor
Input:	
Output:	
Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgPlayEvent, CDialog)
CDlgPlayEvent::CDlgPlayEvent(CWnd* pParent /*=NULL*/)
: CDialog(CDlgPlayEvent::IDD, pParent)
, m_ctDateStart(0)
, m_ctTimeStart(0)
, m_ctDateStop(0)
, m_ctTimeStop(0)
, m_iDeviceIndex(-1)
, m_lLoginID(-1)
, m_iChanIndex(-1)
, m_lPlayHandle(-1)
, m_bDownloading(FALSE)
, m_bSearching(FALSE)
, m_bFullScreen(FALSE)
, m_hFileThread(NULL)
, m_lDeviceType(0)
, m_bGetMaxTime(FALSE)
, m_hPareTabWnd(NULL)
, m_hPareDlgWnd(NULL)
, m_lDownloadHandle(-1)
, m_bPause(FALSE)
, m_bSound(FALSE)
, m_hPlayWnd(NULL)
, m_iFileNum(0)
, m_iChanShowNum(0)
, m_iMajorType(0)
, m_lFileHandle(-1)
, m_nFileTime(0)
, m_nTotalFrames(0)
, m_nTotalSecond(0)
, m_nTotalMinute(0)
, m_nTotalHour(0)
, m_lStartChan(0)
, m_bSaveFile(FALSE)
, m_bSetFrame(FALSE)
, m_iChanNum(0)
, m_iItemSel(-1)
, m_lPort(-1)
, m_iTime(5)
, m_dwBackupVolume(0)
, m_iRelatedChannel(0)
, m_IsQuit(TRUE)
, m_bQuickSearch(FALSE)
, m_strArchiveLabel(_T(""))
, m_strFileName(_T(""))
, m_bSaveByPlay(FALSE)
, m_iPlaybackChannel(1)
{
	memset(m_szFileName, 0, 200);
	memset(m_szDownLoadFileName, 0, 256);
    memset(&m_ctDateStart, 0, sizeof(m_ctDateStart));
    memset(&m_ctDateStop, 0, sizeof(m_ctDateStop));
	m_hPlayEnableIcon =			AfxGetApp()->LoadIcon(IDI_PLAY_ENABLE);
	m_hPlayDisableIcon =		AfxGetApp()->LoadIcon(IDI_PLAY_DISABLE);
	m_hPauseEnableIcon =		AfxGetApp()->LoadIcon(IDI_PAUSE_ENABLE);
	m_hPauseDisableIcon =		AfxGetApp()->LoadIcon(IDI_PAUSE_DISABLE);
	m_hStopEnableIcon =			AfxGetApp()->LoadIcon(IDI_STOP_ENABLE);
	m_hStopDisableIcon =		AfxGetApp()->LoadIcon(IDI_STOP_DISABLE);
	m_hSoundStartIcon=			AfxGetApp()->LoadIcon(IDI_SOUND_ENABLE);
	m_hSoundStopIcon=			AfxGetApp()->LoadIcon(IDI_SOUND_DISABLE);
	m_hGotoHeadDisableIcon =	AfxGetApp()->LoadIcon(IDI_GOTOSTART_DISABLE);
	m_hGotoTailDisableIcon =	AfxGetApp()->LoadIcon(IDI_GOTOEND_DISABLE);
	m_hFastDisableIcon =		AfxGetApp()->LoadIcon(IDI_FASTFORWARD_DISABLE);
	m_hSlowDisableIcon=			AfxGetApp()->LoadIcon(IDI_FASTBACKWARD_DISABLE);
	m_hGotoHeadEnableIcon =		AfxGetApp()->LoadIcon(IDI_GOTOSTART_ENABLE);
	m_hGotoTailEnableIcon =		AfxGetApp()->LoadIcon(IDI_GOTOEND_ENABLE);
	m_hFastEnableIcon =			AfxGetApp()->LoadIcon(IDI_FASTFORWARD_ENABLE);
	m_hSlowEnableIcon =			AfxGetApp()->LoadIcon(IDI_FASTBACKWARD_ENABLE);
	m_hStepEnableIcon=			AfxGetApp()->LoadIcon(IDI_STEP_ENABLE);
	m_hStepDisableIcon =		AfxGetApp()->LoadIcon(IDI_STEP_DISABLE);
	m_hStepBackEnableIcon =		AfxGetApp()->LoadIcon(IDI_STEPBACK_ENABLE);
	m_hStepBackDisableIcon =	AfxGetApp()->LoadIcon(IDI_STEPBACK_DISABLE);
	m_hCaptureIcon	=			AfxGetApp()->LoadIcon(IDI_PIC);	
}

/*********************************************************
Function:	~CDlgPlayEvent
Desc:		destructor
Input:	
Output:	
Return:	
**********************************************************/
CDlgPlayEvent::~CDlgPlayEvent()
{
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgPlayEvent)
    DDX_Control(pDX, IDC_COMBO_RULEID, m_comboRuleID);
    DDX_Control(pDX, IDC_LIST_CHAN, m_listChan);
    DDX_Control(pDX, IDC_COMBO_MINOR_EVENT, m_comboMinorEvent);
    DDX_Control(pDX, IDC_COMBO_MAJOR_EVENT, m_comboMajorType);
    DDX_DateTimeCtrl(pDX, IDC_COMBO_EVENT_DATE_START, m_ctDateStart);
    DDX_DateTimeCtrl(pDX, IDC_COMBO_EVENT_TIME_START, m_ctTimeStart);
    DDX_DateTimeCtrl(pDX, IDC_COMBO_EVENT_DATE_STOP, m_ctDateStop);
    DDX_DateTimeCtrl(pDX, IDC_COMBO_EVENT_TIME_STOP, m_ctTimeStop);
    DDX_Control(pDX, IDC_LIST_EVENT_FILE, m_listRemoteFile);
    DDX_Control(pDX, IDC_STATIC_EVENT_FILE_WND, m_staticPlayWnd);
    DDX_Control(pDX, IDC_SLIDER_EVENT_FILE_VOLUME, m_sliderVolume);
    DDX_Text(pDX, IDC_EDIT_TIME, m_iTime);
    DDV_MinMaxInt(pDX, m_iTime, 0, 60);
    DDX_Text(pDX, IDC_EDIT_STREAM_ID, m_strStreamID);
    DDX_Text(pDX, IDC_EDIT_RELATED_CHANNEL, m_iRelatedChannel);
    DDX_Text(pDX, IDC_EDIT_BACKUP_VOLUME, m_dwBackupVolume);
    DDX_Check(pDX, IDC_CHECK_DRAW_FRAME, m_bDrawFrame);
    DDX_Text(pDX, IDC_EDIT_KEYWORD1, m_csKeyWord1);
    DDX_Text(pDX, IDC_EDIT_KEYWORD4, m_csKeyWord2);
    DDX_Text(pDX, IDC_EDIT_KEYWORD5, m_csKeyWord3);
    DDX_Check(pDX, IDC_CHK_COMBINATEMODE, m_bCombinateMode);
    DDX_Check(pDX, IDC_CHK_CASESENSITIVE, m_bCaseSensitive);
    DDX_Control(pDX, IDC_COMBO_ACS_MAJOR_EVENT, m_cmbMajorType);
    DDX_Control(pDX, IDC_COMBO_ACS_MINOR_EVENT, m_cmbMinorType);
    DDX_Text(pDX, IDC_EDIT_ACS_CARD_NO, m_csCardNo);
    DDX_Text(pDX, IDC_EDIT_ACS_NAME, m_csName);
    DDX_Text(pDX, IDC_EDIT_MAC_ADDR, m_sMacAddr);
    //}}AFX_DATA_MAP
    DDX_Check(pDX, IDC_CHECK_QUCIK_SEARCH, m_bQuickSearch);
    DDX_Text(pDX, IDC_EDIT_ARCHIVE_LABEL, m_strArchiveLabel);
    DDX_Check(pDX, IDC_CHECK_SAVE_BY_PLAY, m_bSaveByPlay);
    DDX_Control(pDX, IDC_COMBO_DEVICE_TYPE, m_comboDeviceType);
    DDX_Control(pDX, IDC_COMBO_FIND_SUB_TYPE, m_comboFindSubType);
    DDX_Text(pDX, IDC_EDIT_PLAYBACK_CHANNEL, m_iPlaybackChannel);
}


/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgPlayEvent, CDialog)
//{{AFX_MSG_MAP(CDlgPlayEvent)	
ON_BN_CLICKED(IDC_BTN_EVENT_SEARCH_LIST, OnBnClickedBtnRemoteSearchList)
ON_NOTIFY(NM_DBLCLK, IDC_LIST_EVENT_FILE, OnNMDblclkListRemoteFile)
ON_BN_CLICKED(IDC_BTN_EVENT_FILE_PLAY, OnBnClickedBtnRemoteFilePlay)
ON_BN_CLICKED(IDC_BTN_EVENT_FILE_STOP, OnBnClickedBtnRemoteFileStop)
ON_BN_CLICKED(IDC_BTN_EVENT_FILE_STOP_SAVE, OnBnClickedBtnRemoteFileStopSave)
ON_BN_CLICKED(IDC_BTN_EVENT_FILE_SLOW, OnBnClickedBtnRemoteFileSlow)
ON_BN_CLICKED(IDC_BTN_EVENT_FILE_SNATCH_PIC, OnBnClickedBtnRemoteFileSnatchPic)
ON_BN_CLICKED(IDC_BTN_EVENT_FILE_STEP, OnBnClickedBtnRemoteFileStep)
ON_BN_CLICKED(IDC_BTN_EVENT_FILE_SOUND, OnBnClickedBtnRemoteFileSound)
ON_BN_CLICKED(IDC_BTN_EVENT_FILE_FAST, OnBnClickedBtnRemoteFileFast)
ON_BN_CLICKED(IDC_BTN_EVENT_FILE_SAVE, OnBnClickedBtnRemoteFileSave)
ON_WM_LBUTTONDBLCLK()
ON_WM_TIMER()
ON_NOTIFY(NM_CLICK, IDC_LIST_EVENT_FILE, OnClickListRemoteFile)
ON_WM_DESTROY()
ON_WM_CTLCOLOR()
ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_EVENT_FILE_VOLUME, OnReleasedcaptureSliderRemoteFileVolume)
ON_NOTIFY(NM_CLICK, IDC_LIST_CHAN, OnClickListChan)
ON_CBN_SELCHANGE(IDC_COMBO_MAJOR_EVENT, OnSelchangeComboMajorEvent)
ON_CBN_SELCHANGE(IDC_COMBO_MINOR_EVENT, OnSelchangeComboMinorEvent)
ON_CBN_SELCHANGE(IDC_COMBO_ACS_MAJOR_EVENT, OnSelchangeComboAcsMajorEvent)
ON_WM_HSCROLL()
ON_WM_PAINT()
ON_WM_MOVE()
ON_WM_CANCELMODE()
ON_WM_CAPTURECHANGED()
ON_BN_CLICKED(IDC_BTN_EVENT_FILE_PLAY_BY_ID_AND_TIME, OnBtnEventFilePlayByIdAndTime)
//}}AFX_MSG_MAP
ON_CBN_SELCHANGE(IDC_COMBO_DEVICE_TYPE, &CDlgPlayEvent::OnCbnSelchangeComboDeviceType)
END_MESSAGE_MAP()


// CDlgPlayEvent message handlers
/*********************************************************
Function:	SetParentWnd
Desc:		transfer config parent dialog handle
Input:	hhWnd,point of handle array, parent point number
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::SetParentWnd(HWND *hhWnd, int iParentNum)
{
	VERIFY(iParentNum==2);
	m_hPareDlgWnd=hhWnd[0];
	m_hPareTabWnd=hhWnd[1];
}

/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgPlayEvent::OnInitDialog()
{
	CDialog::OnInitDialog();
	
    m_listRemoteFile.SetExtendedStyle(m_listRemoteFile.GetExtendedStyle()|LVS_EX_FULLROWSELECT);
	
	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);
	InitUI();
	char szLan[128] = {0};
	g_StringLanType(szLan, "主类型", "Major Type");
	m_listRemoteFile.InsertColumn(0, szLan,LVCFMT_LEFT,120,-1);
	// 	g_StringLanType(szLan, "次类型", "Minor Type");
	// 	m_listRemoteFile.InsertColumn(1, szLan,LVCFMT_LEFT,50,-1);
	g_StringLanType(szLan, "开始时间", "Start time");
	m_listRemoteFile.InsertColumn(1, szLan, LVCFMT_LEFT, 120, -1);
	
	g_StringLanType(szLan, "结束时间", "Stop Time");
	m_listRemoteFile.InsertColumn(2, szLan, LVCFMT_LEFT, 120, -1);
	g_StringLanType(szLan, "高级参数", "Senior Param");
	m_listRemoteFile.InsertColumn(3, szLan,LVCFMT_LEFT,50,-1);
	g_StringLanType(szLan, "触发通道", "Invoke Chan");
	m_listRemoteFile.InsertColumn(4, szLan,LVCFMT_LEFT,50,-1);
	g_StringLanType(szLan, "文件索引", "File Index");
	m_listRemoteFile.InsertColumn(5, szLan, LVCFMT_LEFT, 50, -1);
    g_StringLanType(szLan, "文件所在CS的IP", "File Location");
    m_listRemoteFile.InsertColumn(6, szLan, LVCFMT_LEFT, 50, -1);
    g_StringLanType(szLan, "端口号", "Port");
    m_listRemoteFile.InsertColumn(7, szLan, LVCFMT_LEFT, 50, -1);

    g_StringLanType(szLan, "文件名", "File name");
    m_listRemoteFile.InsertColumn(8, szLan, LVCFMT_LEFT, 120, -1);
	m_listChan.SetExtendedStyle(m_listChan.GetExtendedStyle()|LVS_EX_CHECKBOXES);
	CTime timeCur = CTime::GetCurrentTime();
	CTime timeStart(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),0,0,0);
	CTime timeStop(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),23,59,59);
	m_ctDateStart = timeStart;
	m_ctTimeStart = timeStart;
	m_ctDateStop = timeStop;
	m_ctTimeStop = timeStop;
	m_hPlayWnd = GetDlgItem(IDC_STATIC_EVENT_FILE_WND)->m_hWnd;
	m_sliderVolume.SetRange(0,100);
	m_sliderVolume.SetPos(50);
    m_csCardNo = _T("");
    m_csName = _T("");
    m_sMacAddr = _T("");
	
	GetDlgItem(IDC_STATIC_EVENT_FILE_WND)->GetWindowRect(m_rcWnd);
	ScreenToClient(m_rcWnd);
	g_pDlgPlayEvent=this;
	
	int index=0;
	m_comboRuleID.ResetContent();
	g_StringLanType(szLan, "全部", "All");
	m_comboRuleID.AddString(szLan);
	m_comboRuleID.SetItemData(index, 0xff);
	index++;
	
	m_comboRuleID.AddString("0");
	m_comboRuleID.SetItemData(index, 0);
	index++;
	
	m_comboRuleID.AddString("1");
	m_comboRuleID.SetItemData(index, 1);
	index++;
	
	m_comboRuleID.AddString("2");
	m_comboRuleID.SetItemData(index, 2);
	index++;
	
	m_comboRuleID.AddString("3");
	m_comboRuleID.SetItemData(index, 3);
	index++;
	
	m_comboRuleID.AddString("4");
	m_comboRuleID.SetItemData(index, 4);
	index++;
	
	m_comboRuleID.AddString("5");
	m_comboRuleID.SetItemData(index, 5);
	index++;
	
	m_comboRuleID.AddString("6");
	m_comboRuleID.SetItemData(index, 6);
	index++;
	
	m_comboRuleID.AddString("7");
	m_comboRuleID.SetItemData(index, 7);
	index++;
	//minor event, now for behavior analysis

    m_cmbMajorType.ResetContent();
    m_cmbMajorType.AddString("All");
    m_cmbMajorType.SetItemData(0, 0xffffffff);
    m_cmbMajorType.AddString("Device");
    m_cmbMajorType.SetItemData(1, 0);
    m_cmbMajorType.AddString("Alarm");
    m_cmbMajorType.SetItemData(2, 1);
    m_cmbMajorType.AddString("Door");
    m_cmbMajorType.SetItemData(3, 2);
    m_cmbMajorType.AddString("CardReader");
    m_cmbMajorType.SetItemData(4, 3);

    m_cmbMinorType.ResetContent();
    int iSel = 0;
    iSel = AddMinorAllString(iSel);
    iSel = AddMinorDeviceString(iSel);
    iSel = AddMinorAlarmString(iSel);
    iSel = AddMinorDoorString(iSel);
    iSel = AddMinorCardReaderString(iSel);
    m_cmbMajorType.SetCurSel(0);
    m_cmbMinorType.SetCurSel(0);

	CheckInitParam();
	UpdateMinorEvent();
	m_comboMajorType.SetCurSel(0);
	m_comboMinorEvent.SetCurSel(0);

    int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    int iChanIndex = g_pMainDlg->GetCurChanIndex();
    if (iDeviceIndex != -1 && iChanIndex != -1)
    {
        m_iPlaybackChannel = g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[m_iChanIndex].iChannelNO;
    }
    else
    {
        m_iPlaybackChannel = 1;
    }

	UpdateData(FALSE);
	return TRUE;
}



/*********************************************************
Function:	CheckInitParam
Desc:		Verify current device's parameters, and initialize the parameter of dialog
Input:	
Output:	
Return:	TRUE,Verify successfully and initialize parameters; FALSE,verify failed and won't initialize parameters;
**********************************************************/
BOOL CDlgPlayEvent::CheckInitParam()
{
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	if (iDeviceIndex == -1)
	{
		UpdateData(FALSE);
		return FALSE;
	}
	if ( m_iDeviceIndex == -1 || m_iDeviceIndex != iDeviceIndex)
	{
		m_iChanIndex = -1;
	}
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	if (iChanIndex == -1)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "set the channel index = 0");
		iChanIndex = 0;
		//AfxMessageBox("please select a channel!");
		//UpdateData(FALSE);
		//return FALSE;
	}
	
	UpdateData(TRUE);
	char szLan[128] = {0};
	
	m_iDeviceIndex = iDeviceIndex;
	m_lLoginID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	m_iChanNum = g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum;
	m_lDeviceType = g_struDeviceInfo[m_iDeviceIndex].iDeviceType;
	m_lStartChan = g_struDeviceInfo[m_iDeviceIndex].iStartChan;
	
	//reinitialize the parameter when switching channel
	if (m_iChanIndex != iChanIndex)
	{
		m_iChanIndex = iChanIndex;
        m_iPlaybackChannel = g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[m_iChanIndex].iChannelNO;
        m_iChanShowNum = m_iPlaybackChannel;
		if (m_lPlayHandle>=0)
		{
			StopPlay();
		}
		
		m_bDownloading=FALSE;
		m_bSearching = FALSE;
		m_lPlayHandle = -1;
		m_bSound=TRUE;
		m_bPause=FALSE;
		m_bSetFrame = FALSE;
		m_bGetMaxTime = FALSE;
		m_bFullScreen = FALSE;
		m_bSaveFile = FALSE;
		//m_hPareDlgWnd = NULL;
		//m_hPareTabWnd = NULL;
		
		m_hFileThread = NULL;
		m_iFileNum = 0;
		m_lDownloadHandle = -1;
		m_nFileTime = 0;
		m_nTotalFrames = 0;
		m_nTotalSecond = 0;
		m_nTotalMinute = 0;
		m_nTotalHour = 0;
		m_listRemoteFile.DeleteAllItems();
        //memset(&m_struEventParamV40, 0, sizeof(NET_DVR_SEARCH_EVENT_PARAM_V40));
        //for (int i = 0; i < MAX_CHANNUM_V30; i++)
        //{
        //    m_struEventParamV40.uSeniorParam.struMotionParam.wMotDetChanNo[i] = 0xffff;
        //}
        memset(&m_struEventParamV50, 0, sizeof(NET_DVR_SEARCH_EVENT_PARAM_V50));
		
	}
	if (m_lLoginID < 0)
	{
		UpdateData(FALSE);
		return FALSE;
	}
	
	int iIndex = 0;
	m_comboMajorType.ResetContent();
	
	g_StringLanType(szLan, "移动侦测", "Motion Detect");
	m_comboMajorType.AddString(szLan);
	m_comboMajorType.SetItemData(iIndex, 0);
	iIndex++;
	
	g_StringLanType(szLan, "报警输入", "Alarm In");
	m_comboMajorType.AddString(szLan);
	m_comboMajorType.SetItemData(iIndex, 1);
	iIndex++;
	
	g_StringLanType(szLan, "行为分析", "Behavior Analysis");
	m_comboMajorType.AddString(szLan);
	m_comboMajorType.SetItemData(iIndex, 2);
	iIndex++;
	
	g_StringLanType(szLan, "智能侦测", "VCA Detect");
	m_comboMajorType.AddString(szLan);
	m_comboMajorType.SetItemData(iIndex, 4);
	iIndex++;

    g_StringLanType(szLan, "POS", "POS");
    m_comboMajorType.AddString(szLan);
    m_comboMajorType.SetItemData(iIndex, 5);
	iIndex++;	

    g_StringLanType(szLan, "门禁事件", "ACS Event");
    m_comboMajorType.AddString(szLan);
    m_comboMajorType.SetItemData(iIndex, 7);
    iIndex++;
	
    g_StringLanType(szLan, "非视频联动事件", "IOT Event");
    m_comboMajorType.AddString(szLan);
    m_comboMajorType.SetItemData(iIndex, 8);
    iIndex++;

	g_StringLanType(szLan, "通道关联", "Channel Related"); 
	m_comboMajorType.AddString(szLan);
	m_comboMajorType.SetItemData(iIndex, 100);
	iIndex++;
	
	m_iMajorType = 0;
	m_comboMajorType.SetCurSel(m_iMajorType);
	UpdateMinorEvent();
	UpdateChanStatus();


    iIndex = 0;
    m_comboDeviceType.ResetContent();

    g_StringLanType(szLan, "海康门禁主机", "Acs");
    m_comboDeviceType.InsertString(iIndex, szLan);
    m_comboDeviceType.SetItemData(iIndex, FILE_ACS);
    iIndex++;

    g_StringLanType(szLan, "海康可视对讲设备", "Video intercom");
    m_comboDeviceType.InsertString(iIndex, szLan);
    m_comboDeviceType.SetItemData(iIndex, FILE_VIDEO_INTERCOM);
    iIndex++;

    g_StringLanType(szLan, "GJD报警主机", "GJD");
    m_comboDeviceType.InsertString(iIndex, szLan);
    m_comboDeviceType.SetItemData(iIndex, FILE_GJD);
    iIndex++;

    g_StringLanType(szLan, "Luminite报警主机", "Luminite");
    m_comboDeviceType.InsertString(iIndex, szLan);
    m_comboDeviceType.SetItemData(iIndex, FILE_LUMINITE);
    iIndex++;

    g_StringLanType(szLan, "OPTEX报警主机", "OPTEX");
    m_comboDeviceType.InsertString(iIndex, szLan);
    m_comboDeviceType.SetItemData(iIndex, FILE_OPTEX);
    iIndex++;

    g_StringLanType(szLan, "模拟相机传感器设备", "camera detector");
    m_comboDeviceType.InsertString(iIndex, szLan);
    m_comboDeviceType.SetItemData(iIndex, FILE_CAMERA_DETECTOR);
    iIndex++;

    m_comboDeviceType.SetCurSel(0);
    UpdateData(FALSE);

    OnCbnSelchangeComboDeviceType();

	return TRUE;
}

/*********************************************************
Function:	InitUI
Desc:		Initial control of dialog
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::InitUI()
{
	// Initial button
	CButton *pButton;
	
	m_rcScreen=CRect(0,0,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_PLAY);
	pButton->SetIcon(m_hPlayDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_PLAY_BY_ID_AND_TIME);
	pButton->SetIcon(m_hPlayDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_STOP);
	pButton->SetIcon(m_hStopDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_FAST);
	pButton->SetIcon(m_hFastDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_SLOW);
	pButton->SetIcon(m_hSlowDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_STEP);
	pButton->SetIcon(m_hStepDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_SNATCH_PIC);
	pButton->SetIcon(m_hCaptureIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_SOUND);
	pButton->SetIcon(m_hSoundStopIcon);
	pButton->EnableWindow(FALSE);
}

/*********************************************************
Function:	SetStopState
Desc:		Change the control status when stop playback
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::SetStopState()
{
	CButton *pButton;
	
	m_sliderVolume.EnableWindow(FALSE);
	
	GetDlgItem(IDC_BTN_EVENT_FILE_PLAY_BY_ID_AND_TIME)->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_PLAY);
	pButton->SetIcon(m_hPlayEnableIcon);
	pButton->EnableWindow(TRUE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_STOP);
	pButton->SetIcon(m_hStopDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_FAST);
	pButton->SetIcon(m_hFastDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_SLOW);
	pButton->SetIcon(m_hSlowDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_STEP);
	pButton->SetIcon(m_hStepDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_SNATCH_PIC);
	pButton->SetIcon(m_hCaptureIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_SOUND);
	pButton->SetIcon(m_hSoundStopIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_STEP);
	pButton->SetIcon(m_hStepDisableIcon);
	pButton->EnableWindow(FALSE);	
}

/*********************************************************
Function:	SetStopStateIDTime
Desc:		Change the control status when stop playback
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::SetStopStateIDTime()
{
	CButton *pButton;
	
	m_sliderVolume.EnableWindow(FALSE);
	
	GetDlgItem(IDC_BTN_EVENT_FILE_PLAY)->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_PLAY_BY_ID_AND_TIME);
	pButton->SetIcon(m_hPlayEnableIcon);
	pButton->EnableWindow(TRUE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_STOP);
	pButton->SetIcon(m_hStopDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_FAST);
	pButton->SetIcon(m_hFastDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_SLOW);
	pButton->SetIcon(m_hSlowDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_STEP);
	pButton->SetIcon(m_hStepDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_SNATCH_PIC);
	pButton->SetIcon(m_hCaptureIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_SOUND);
	pButton->SetIcon(m_hSoundStopIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_STEP);
	pButton->SetIcon(m_hStepDisableIcon);
	pButton->EnableWindow(FALSE);	
}

/*********************************************************
Function:	ExitPlayBack
Desc:		Exit current diaglog and release resource
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::ExitPlayBack()
{
	if (m_hFileThread)
	{
		TerminateThread(m_hFileThread, 0);
		CloseHandle(m_hFileThread);
		m_hFileThread = NULL;
		NET_DVR_FindClose(m_lFileHandle);
	}	
	
	if (m_lPlayHandle!=-1)
	{
		NET_DVR_StopPlayBack(m_lPlayHandle);
		m_lPlayHandle = -1;
	}
	Sleep(100);
}
/*********************************************************
Function:	ConvertTime
Desc:		convert between time_t and NET_DVR_TIME
Input:	void
Output:	void
Return:	void
**********************************************************/
BOOL ConvertTime(time_t *lpInBuf, LPNET_DVR_TIME pOutBuf, BOOL bInToOut)
{
	if(pOutBuf == NULL || lpInBuf == NULL)
	{
		return FALSE;
	}
	
	if (bInToOut)
	{
		struct tm *newtime;
		newtime = localtime(lpInBuf);
		if (newtime == NULL)
		{
			return FALSE;
		}
		pOutBuf->dwYear = DWORD(newtime->tm_year+1900);
		pOutBuf->dwMonth = DWORD (newtime->tm_mon+1);
		pOutBuf->dwDay = DWORD(newtime->tm_mday);
		pOutBuf->dwHour = DWORD(newtime->tm_hour);
		pOutBuf->dwMinute = DWORD(newtime->tm_min);
		pOutBuf->dwSecond = DWORD(newtime->tm_sec);
	}
	else
	{
		struct tm newtime = {0};
		newtime.tm_year = pOutBuf->dwYear - 1900;
		newtime.tm_mon = pOutBuf->dwMonth - 1;
		newtime.tm_mday = pOutBuf->dwDay;
		newtime.tm_hour = pOutBuf->dwHour;
		newtime.tm_min = pOutBuf->dwMinute;
		newtime.tm_sec = pOutBuf->dwSecond;	
		//utc = local time + bias, local time = utc - bias;
		*lpInBuf = mktime(&newtime);
	}
	return TRUE;
}
/*********************************************************
Function:	PlayBack
Desc:		begin play back 
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::PlayBack()
{
	UpdateData(TRUE);
	
	int m_nVerifyret = -1;
	CString csFileName;
	int iFileSelPos = 0;
	HWND hPlayWnd=m_staticPlayWnd.GetSafeHwnd();
	POSITION  posItem = m_listRemoteFile.GetFirstSelectedItemPosition();
	NET_DVR_TIME struStartTime,struStopTime;
	char szLan[128] = {0};
	
	//	remoteplay_info.srcfilename=m_szFileName;
	if (m_lPlayHandle>=0)
	{
		if (NET_DVR_StopPlayBack(m_lPlayHandle))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopPlayBack");
		}
		m_lPlayHandle = -1;
		Sleep(400);
	}
	if (m_lPlayHandle == -1)
	{
		m_iChanShowNum = m_iPlaybackChannel;
		time_t tmp;
		ConvertTime(&tmp, &m_struStartTime, FALSE);
		tmp -= m_iTime;
		ConvertTime(&tmp, &m_struStartTime, TRUE);
		ConvertTime(&tmp, &m_struStopTime, FALSE);
		tmp += m_iTime;
		ConvertTime(&tmp, &m_struStopTime, TRUE);
		memcpy(&struStartTime, &m_struStartTime, sizeof(NET_DVR_TIME));
		memcpy(&struStopTime, &m_struStopTime, sizeof(NET_DVR_TIME));	
		
		if (m_strFileName.GetLength() > 0)
		{
            m_lPlayHandle = NET_DVR_PlayBackByName(m_lLoginID, m_strFileName.GetBuffer(0), hPlayWnd);

            if (m_lPlayHandle == -1)
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_PlayBackByName");
                g_StringLanType(szLan, "远程回放失败", "Fail to play back remote");
                AfxMessageBox(szLan);
                return;
            }
            else
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_PlayBackByName");
            }
		}
        else
        {
            m_lPlayHandle = NET_DVR_PlayBackByTime(m_lLoginID, m_iChanShowNum, &struStartTime, &struStopTime, hPlayWnd);//NULL

            if (m_lPlayHandle == -1)
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_PlayBackByTime ChanNum[%d]", m_iChanShowNum);
                g_StringLanType(szLan, "远程回放失败", "Fail to play back remote");
                AfxMessageBox(szLan);
                return;
            }
            g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_PlayBackByTime ChanNum[%d]", m_iChanShowNum);
        }

		int idx = NET_DVR_GetPlayBackPlayerIndex(m_lPlayHandle);

        if (m_bSaveByPlay)
        {
            char m_sFile[256] = { 0 };
            char sIPV6Addr[130] = { 0 };
            for (int i = 0; i < sizeof(g_struDeviceInfo[m_iDeviceIndex].chDeviceIP); i++)
            {
                if (g_struDeviceInfo[m_iDeviceIndex].chDeviceIP[i] == '\0')
                {
                    break;
                }
                else if (g_struDeviceInfo[m_iDeviceIndex].chDeviceIP[i] == ':')
                {
                    sIPV6Addr[i] = '-';
                }
                else
                {
                    sIPV6Addr[i] = g_struDeviceInfo[m_iDeviceIndex].chDeviceIP[i];
                }
            }
            CTime ctime = CTime::GetCurrentTime();

            sprintf(m_sFile, "%s\\%s_%d_%d_%d_%d_%d_%d_%d_savefile.mp4", g_struLocalParam.chDownLoadPath, sIPV6Addr, ctime.GetYear(),
                ctime.GetMonth(), ctime.GetDay(), ctime.GetHour(), ctime.GetMinute(), ctime.GetSecond(), ctime.GetTickCount);
            if (NET_DVR_PlayBackSaveData(m_lPlayHandle, m_sFile))
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_PlayBackSaveData[%s]", m_sFile);
                m_bSaveFile = TRUE;
            }
            else
            {
                char szLan[128] = { 0 };
                g_StringLanType(szLan, "文件保存失败", "Save the file failed");
                AfxMessageBox(szLan);
            }
        }
		
		NET_DVR_PlayBackControl(m_lPlayHandle, NET_DVR_PLAYSTART, 0, NULL);
		
		if (NET_DVR_PlayBackControl(m_lPlayHandle, NET_DVR_PLAYSTARTAUDIO, 0, NULL))
		{
			m_bSound=TRUE;
			NET_DVR_PlayBackControl(m_lPlayHandle, NET_DVR_PLAYAUDIOVOLUME, (0xffff)/2, NULL);
			m_sliderVolume.SetPos(50);
			((CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_SOUND))->SetIcon(m_hSoundStartIcon);
		}
		else
		{
			m_bSound=FALSE;
			((CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_SOUND))->SetIcon(m_hSoundStopIcon);
		}
		SetPlayState();
		SetTimer(PLAYBYTIME_TIMER, 5000, NULL);
	}
	else
	{
		if (m_bPause)
		{
			if (NET_DVR_PlayBackControl(m_lPlayHandle, NET_DVR_PLAYRESTART, 0, NULL))
			{
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_PLAYRESTART");
				m_bPause=FALSE;
				SetPlayState();
			}
            else
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_PLAYRESTART");
            }
		}
		else
		{
			if (NET_DVR_PlayBackControl(m_lPlayHandle, NET_DVR_PLAYPAUSE, 0, NULL))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_PLAYPAUSE");
				m_bPause=TRUE;
				CButton *pButton;	
				pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_PLAY);
				pButton->SetIcon(m_hPlayEnableIcon);
				pButton->EnableWindow(TRUE);
			}
            else
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_PLAYPAUSE");
            }
		}
	}
}

/*********************************************************
Function:	SetPlayState
Desc:		update the play state
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::SetPlayState() 
{
	m_sliderVolume.EnableWindow(TRUE);
	
	CButton *pButton;
	
	GetDlgItem(IDC_BTN_EVENT_FILE_PLAY_BY_ID_AND_TIME)->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_PLAY);
	pButton->SetIcon(m_hPauseEnableIcon);
	pButton->EnableWindow(TRUE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_STOP);
	pButton->SetIcon(m_hStopEnableIcon);
	pButton->EnableWindow(TRUE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_FAST);
	pButton->SetIcon(m_hFastEnableIcon);
	pButton->EnableWindow(TRUE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_SLOW);
	pButton->SetIcon(m_hSlowEnableIcon);
	pButton->EnableWindow(TRUE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_SNATCH_PIC);
	pButton->SetIcon(m_hCaptureIcon);
	pButton->EnableWindow(TRUE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_SOUND);
	if (m_bSound)
	{
		pButton->SetIcon(m_hSoundStartIcon);
	}
	else
	{
		pButton->SetIcon(m_hSoundStopIcon);
	}
	pButton->EnableWindow(TRUE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_STEP);
	pButton->SetIcon(m_hStepEnableIcon);
	pButton->EnableWindow(TRUE);
}

/*********************************************************
Function:	SetPauseState
Desc:		update the pause button state
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::SetPauseState()
{
	CButton *pButton;	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_PLAY);
	pButton->SetIcon(m_hPlayEnableIcon);
	pButton->EnableWindow(TRUE);
	
	GetDlgItem(IDC_BTN_EVENT_FILE_PLAY_BY_ID_AND_TIME)->EnableWindow(FALSE);
}

/*********************************************************
Function:	SetPlayStateIDTime
Desc:		update the play state
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::SetPlayStateIDTime() 
{
	m_sliderVolume.EnableWindow(TRUE);
	
	CButton *pButton;
	
	GetDlgItem(IDC_BTN_EVENT_FILE_PLAY)->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_PLAY_BY_ID_AND_TIME);
	pButton->SetIcon(m_hPauseEnableIcon);
	pButton->EnableWindow(TRUE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_STOP);
	pButton->SetIcon(m_hStopEnableIcon);
	pButton->EnableWindow(TRUE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_FAST);
	pButton->SetIcon(m_hFastEnableIcon);
	pButton->EnableWindow(TRUE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_SLOW);
	pButton->SetIcon(m_hSlowEnableIcon);
	pButton->EnableWindow(TRUE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_SNATCH_PIC);
	pButton->SetIcon(m_hCaptureIcon);
	pButton->EnableWindow(TRUE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_SOUND);
	if (m_bSound)
	{
		pButton->SetIcon(m_hSoundStartIcon);
	}
	else
	{
		pButton->SetIcon(m_hSoundStopIcon);
	}
	pButton->EnableWindow(TRUE);
	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_STEP);
	pButton->SetIcon(m_hStepEnableIcon);
	pButton->EnableWindow(TRUE);
}

/*********************************************************
Function:	SetPauseState
Desc:		update the pause button state
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::SetPauseStateIDTime()
{
	CButton *pButton;	
	pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_PLAY_BY_ID_AND_TIME);
	pButton->SetIcon(m_hPlayEnableIcon);
	pButton->EnableWindow(TRUE);
	
	GetDlgItem(IDC_BTN_EVENT_FILE_PLAY)->EnableWindow(FALSE);
}

/*********************************************************
Function:	StopPlay
Desc:		Stop playback
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::StopPlay()
{
	if (m_lPlayHandle >= 0)
	{
		if (m_bSaveFile)
		{
			if (!NET_DVR_StopPlayBackSave(m_lPlayHandle))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopPlayBackSave");
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopPlayBackSave");
				m_bSaveFile = FALSE;
			}
			
		}
		if (!NET_DVR_StopPlayBack(m_lPlayHandle))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopPlayBack");
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopPlayBack");
			m_bSaveFile = FALSE;
		}
		if (m_lPort >= 0)
		{
			PlayM4_FreePort(m_lPort);
			m_lPort = -1;
		}
		m_lPlayHandle = -1;
		KillTimer(REMOTE_PLAY_STATE_TIMER);
		UpdateData(FALSE);
		Invalidate(TRUE);
	}
	m_bPause = FALSE;
	m_bSetFrame = FALSE;
	
	if (EVENT_STREAM_INFO == m_comboMajorType.GetItemData(m_comboMajorType.GetCurSel()))
	{
		SetStopStateIDTime();
	}
	else
	{
		SetStopState();
	}
}

/*********************************************************
Function:	EnableFlashWnd
Desc:		refresh the state
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::EnableFlashWnd(BOOL bEnable)
{
	if (bEnable)
	{
		//THE same to multiplay
		GetDlgItem(IDC_BTN_EVENT_FILE_PLAY)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_BTN_EVENT_FILE_PLAY_BY_ID_AND_TIME)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_BTN_EVENT_FILE_STOP)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_BTN_EVENT_FILE_SLOW)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_BTN_EVENT_FILE_FAST)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_BTN_EVENT_FILE_SOUND)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_SLIDER_EVENT_FILE_VOLUME)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_COMBO_EVENT_DATE_START)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_COMBO_EVENT_DATE_STOP)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_COMBO_EVENT_TIME_STOP)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_COMBO_EVENT_TIME_START)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_COMBO_MAJOR_EVENT)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_BTN_EVENT_SEARCH_LIST)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_BTN_EVENT_FILE_SNATCH_PIC)->ModifyStyle(0,WS_VISIBLE,0);	
		//the only for single play
		GetDlgItem(IDC_BTN_EVENT_FILE_DOWNLOAD)->ModifyStyle(0,WS_VISIBLE,0);
		GetDlgItem(IDC_LIST_EVENT_FILE)->ModifyStyle(0,WS_VISIBLE,0);
		
		GetDlgItem(IDC_BTN_EVENT_FILE_STEP)->ModifyStyle(0,WS_VISIBLE,0);
	}
	else
	{
		//THE same to multiplay
		GetDlgItem(IDC_BTN_EVENT_FILE_PLAY)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_BTN_EVENT_FILE_PLAY_BY_ID_AND_TIME)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_BTN_EVENT_FILE_STOP)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_BTN_EVENT_FILE_SLOW)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_BTN_EVENT_FILE_FAST)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_BTN_EVENT_FILE_SOUND)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_SLIDER_EVENT_FILE_VOLUME)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_COMBO_EVENT_DATE_START)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_COMBO_EVENT_DATE_STOP)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_COMBO_EVENT_TIME_STOP)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_COMBO_EVENT_TIME_START)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_COMBO_MAJOR_EVENT)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_BTN_EVENT_SEARCH_LIST)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_BTN_EVENT_FILE_SNATCH_PIC)->ModifyStyle(WS_VISIBLE,0,0);
		//the only for single play
		GetDlgItem(IDC_LIST_EVENT_FILE)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_BTN_EVENT_FILE_STEP)->ModifyStyle(WS_VISIBLE,0,0);
		GetDlgItem(IDC_BTN_EVENT_FILE_DOWNLOAD)->ModifyStyle(WS_VISIBLE,0,0);
	}
}

/*********************************************************
Function:	IsInWnd
Desc:		make sure the mouse is on this window or not
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgPlayEvent::IsInWnd(CPoint point)
{
	CRect rc;
	GetDlgItem(IDC_STATIC_EVENT_FILE_WND)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	if (PtInRect(&rc,point))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*********************************************************
Function:	PlayBackFullScreen
Desc:		full screen
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::PlayBackFullScreen()
{
	EnableFlashWnd(FALSE);
	
	CRect rc,rcClient;
	::GetWindowRect(m_hPareDlgWnd,m_rcPareDlg);
	
	::GetWindowRect(m_hPareTabWnd,m_rcPareTab);
	
	::ScreenToClient(m_hPareDlgWnd,(POINT*)(&m_rcPareTab));
	::ScreenToClient(m_hPareDlgWnd,(POINT*)(&m_rcPareTab)+1);
	
	::GetWindowRect(m_hWnd,m_rcParent);
	::ScreenToClient(m_hPareTabWnd,(POINT*)(&m_rcParent));
	::ScreenToClient(m_hPareTabWnd,(POINT*)(&m_rcParent)+1);
	
	
	::SetWindowPos(m_hPareDlgWnd,NULL,m_rcScreen.left-SCREEN_EDGE,m_rcScreen.top-SCREEN_EDGE,m_rcScreen.Width()+2*SCREEN_EDGE,m_rcScreen.Height()+2*SCREEN_EDGE,SWP_SHOWWINDOW);
	
	::GetClientRect(m_hPareDlgWnd,rc);
	::SetWindowPos(m_hPareTabWnd,NULL,rc.left,rc.top,rc.Width(),rc.Height(),SWP_SHOWWINDOW);
	
	::GetClientRect(m_hPareTabWnd,rc);
	::SetWindowPos(m_hWnd,NULL,rc.left,rc.top,rc.Width(),rc.Height(),SWP_SHOWWINDOW);
	
	GetDlgItem(IDC_STATIC_EVENT_FILE_WND)->GetClientRect(rcClient);
	GetDlgItem(IDC_STATIC_EVENT_FILE_WND)->GetWindowRect(rc);
	int iEdge=(rc.Width()-rcClient.Width())/2;
	rc=m_rcScreen;
	rc.left-=iEdge;
	rc.right+=iEdge;
	rc.top-=iEdge;
	rc.bottom+=iEdge;
	this->ScreenToClient(rc);
	::SetWindowPos(GetDlgItem(IDC_STATIC_EVENT_FILE_WND)->m_hWnd,NULL,rc.left,rc.top,rc.Width(),rc.Height(),SWP_SHOWWINDOW);
	Invalidate(FALSE);
	UpdateWindow();
}

/*********************************************************
Function:	PlayBackShowNormal
Desc:		back to the normal show
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::PlayBackShowNormal()
{
	GetDlgItem(IDC_STATIC_EVENT_FILE_WND)->SetWindowPos(NULL,m_rcWnd.left,m_rcWnd.top,m_rcWnd.Width(),m_rcWnd.Height(),SWP_SHOWWINDOW);
	::SetWindowPos(m_hWnd,NULL,m_rcParent.left,m_rcParent.top,m_rcParent.Width(),m_rcParent.Height(),SWP_SHOWWINDOW);
	::SetWindowPos(m_hPareTabWnd,NULL,m_rcPareTab.left,m_rcPareTab.top,m_rcPareTab.Width(),m_rcPareTab.Height(),SWP_SHOWWINDOW);
	::SetWindowPos(m_hPareDlgWnd,NULL,m_rcPareDlg.left,m_rcPareDlg.top,m_rcPareDlg.Width(),m_rcPareDlg.Height(),SWP_SHOWWINDOW);
	EnableFlashWnd(TRUE);
	Invalidate(FALSE);
	UpdateWindow();
}

/*********************************************************
Function:	OnDestroy
Desc:		Destroy dialog when exiting
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::OnDestroy() 
{
	KillTimer(DOWNSTATE_TIMER);
	CDialog::OnDestroy();	
}

/*********************************************************
Function:	OnNMDblclkListRemoteFile
Desc:		play the selected file
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::OnNMDblclkListRemoteFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnBnClickedBtnRemoteFileStop();
	if (EVENT_STREAM_INFO == m_comboMajorType.GetItemData(m_comboMajorType.GetCurSel()))
	{
		OnBtnEventFilePlayByIdAndTime();
	}
	else
	{
		OnBnClickedBtnRemoteFilePlay();
	}
	
	*pResult = 0;
}
/*********************************************************
Function:	OnLButtonDblClk
Desc:		Enlarge image by double click
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if ((IsInWnd(point)) && (m_lPlayHandle>=0))
	{
		m_bFullScreen=!m_bFullScreen;
		g_pMainDlg->FullScreen(m_bFullScreen);//process of main frame
		if (m_bFullScreen)
		{
			PlayBackFullScreen();
		}
		else
		{
			PlayBackShowNormal();
		}
		
	}
	
	CDialog::OnLButtonDblClk(nFlags, point);
}

/*********************************************************
Function:	OnTimer
Desc:		Function for Timer, show the status of download and playback
Input:	
Output:	
Return:	
**********************************************************/
#if (_MSC_VER >= 1500)	//vs2008
void CDlgPlayEvent::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgPlayEvent::OnTimer(UINT nIDEvent) 
#endif
{
	DWORD nPos;
	char szLan[128] = {0};
	//	NET_DVR_TIME struOsdTime;
	if (nIDEvent == PLAYBYTIME_TIMER)
	{
		if (m_lPlayHandle >= 0)
		{
			if (NET_DVR_PlayBackControl(m_lPlayHandle, NET_DVR_PLAYGETPOS, 0, &nPos))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_PLAYGETPOS pos[%d]", nPos);
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_PLAYGETPOS");
			}
			
			// 			if (NET_DVR_GetPlayBackOsdTime(m_lPlayHandle, &struOsdTime))
			// 			{
			// 				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "OSDTime: %04d%02d%02d%02d%02d%02d", \
			// 					struOsdTime.dwYear, struOsdTime.dwMonth,struOsdTime.dwDay, struOsdTime.dwHour, struOsdTime.dwMinute, struOsdTime.dwSecond);
			// 			}
			// 			else
			// 			{
			// 				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetPlayBackOsdTime");
			// 			}
			
			if (nPos > 100)
			{
				StopPlay();
				g_StringLanType(szLan, "由于网络原因或DVR忙,回放异常终止!", " Due to network reasons or DVR is busy, playback abnormal termination");
				AfxMessageBox(szLan);
			}
			if (nPos == 100)
			{				
				StopPlay();
				g_StringLanType(szLan, "按时间回放结束", "playback by time over");
				AfxMessageBox(szLan);
			}		
		}
		
	}
	// 	else if (nIDEvent == DOWNBYTIME_TIMER)
	// 	{
	// 		if (m_bDown)
	// 		{
	// 			NET_DVR_PlayBackControl(m_lLoadHandle, NET_DVR_PLAYGETPOS, 0, &nPos);
	// 			if (nPos > 100)
	// 			{
	// 				m_bDown=FALSE;				
	// 				NET_DVR_StopGetFile(m_lLoadHandle);
	// 				g_StringLanType(szLan, "下载", "Download");
	// 				GetDlgItem(IDC_BTN_RT_DOWNLOAD)->SetWindowText(szLan);
	// 				g_StringLanType(szLan, "由于网络原因或DVR忙,下载异常终止!", " Due to network reasons or DVR is busy, download abnormal termination");
	// 				AfxMessageBox(szLan);
	// 			}
	// 			if (nPos == 100)
	// 			{
	// 				m_bDown=FALSE;				
	// 				NET_DVR_StopGetFile(m_lLoadHandle);
	// 				g_StringLanType(szLan, "下载", "Download");
	// 				GetDlgItem(IDC_BTN_RT_DOWNLOAD)->SetWindowText(szLan);
	// 				g_StringLanType(szLan, "按时间下载结束", "download by time over");
	// 				AfxMessageBox(szLan);
	// 			}		
	// 		}	
	// 	}	
	CDialog::OnTimer(nIDEvent);
}

/*********************************************************
Function:	OnBnClickedBtnRemoteSearchList
Desc:		function for search video by time or card NO.
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::OnBnClickedBtnRemoteSearchList()
{
	UpdateData(TRUE);
	char szLan[128] = {0};
	if (!m_bSearching)
	{
		m_IsQuit = TRUE;
		m_iMajorType = m_comboMajorType.GetItemData(m_comboMajorType.GetCurSel());
        m_struEventParamV50.wMajorType = m_iMajorType;
		
        int i = m_comboMinorEvent.GetCurSel();
        m_struEventParamV50.wMinorType = m_comboMinorEvent.GetItemData(i);
        m_struEventParamV50.struStartTime.wYear = (WORD)m_ctDateStart.GetYear();
        m_struEventParamV50.struStartTime.byMonth = (char)m_ctDateStart.GetMonth();
        m_struEventParamV50.struStartTime.byDay = (char)m_ctDateStart.GetDay();
        m_struEventParamV50.struStartTime.byHour = (char)m_ctTimeStart.GetHour();
        m_struEventParamV50.struStartTime.byMinute = (char)m_ctTimeStart.GetMinute();
        m_struEventParamV50.struStartTime.bySecond = (char)m_ctTimeStart.GetSecond();
        m_struEventParamV50.struStartTime.byLocalOrUTC = g_bISO8601;
        m_struEventParamV50.struStartTime.cTimeDifferenceH = g_iHourDiffWithUTC;
        m_struEventParamV50.struStartTime.cTimeDifferenceM = g_iMinDiffWithUTC;
        m_struEventParamV50.struEndTime.wYear = (WORD)m_ctDateStop.GetYear();
        m_struEventParamV50.struEndTime.byMonth = (char)m_ctDateStop.GetMonth();
        m_struEventParamV50.struEndTime.byDay = (char)m_ctDateStop.GetDay();
        m_struEventParamV50.struEndTime.byHour = (char)m_ctTimeStop.GetHour();
        m_struEventParamV50.struEndTime.byMinute = (char)m_ctTimeStop.GetMinute();
        m_struEventParamV50.struEndTime.bySecond = (char)m_ctTimeStop.GetSecond();
        m_struEventParamV50.struEndTime.byLocalOrUTC = g_bISO8601;
        m_struEventParamV50.struEndTime.cTimeDifferenceH = g_iHourDiffWithUTC;
        m_struEventParamV50.struEndTime.cTimeDifferenceM = g_iMinDiffWithUTC;
        m_struEventParamV50.byQuickSearch = m_bQuickSearch;
		
		//the state is signed in updateChanStatus
		m_lDeviceType = g_struDeviceInfo[m_iDeviceIndex].iDeviceType;
        char sMac[32] = { 0 };
        int iLen = m_sMacAddr.GetLength();
        memcpy(sMac, m_sMacAddr, iLen);
		switch(m_iMajorType)
		{
		case EVENT_ALARM_IN:
		case EVENT_MOT_DET:
			//		case EVENT_AUX_ALARM:
			break;
		case EVENT_VCA_BEHAVIOR:
			m_struEventParamV50.uSeniorParam.struVcaParam.byRuleID = m_comboRuleID.GetItemData(m_comboRuleID.GetCurSel());
			break;
		case EVENT_STREAM_INFO:
			m_struEventParamV50.uSeniorParam.struStreamIDParam.struIDInfo.dwSize = sizeof(NET_DVR_STREAM_INFO);
			strncpy((char*)m_struEventParamV50.uSeniorParam.struStreamIDParam.struIDInfo.byID, m_strStreamID.GetBuffer(0), STREAM_ID_LEN);
			m_struEventParamV50.uSeniorParam.struStreamIDParam.struIDInfo.dwChannel = m_iRelatedChannel;
			m_struEventParamV50.uSeniorParam.struStreamIDParam.byBackupVolumeNum = (BYTE)m_dwBackupVolume;
            strncpy((char*)m_struEventParamV50.uSeniorParam.struStreamIDParam.byArchiveLabel, m_strArchiveLabel.GetBuffer(0), 64);
			break;
        case EVENT_POS:
            m_struEventParamV50.uSeniorParam.struPosAlarm.byCaseSensitive = m_bCaseSensitive;
            m_struEventParamV50.uSeniorParam.struPosAlarm.byCombinateMode = m_bCombinateMode;
            strncpy((char*)m_struEventParamV50.uSeniorParam.struPosAlarm.sKeyWord[0], m_csKeyWord1.GetBuffer(0), STREAM_ID_LEN);
            strncpy((char*)m_struEventParamV50.uSeniorParam.struPosAlarm.sKeyWord[1], m_csKeyWord2.GetBuffer(0), STREAM_ID_LEN);
            strncpy((char*)m_struEventParamV50.uSeniorParam.struPosAlarm.sKeyWord[2], m_csKeyWord3.GetBuffer(0), STREAM_ID_LEN);
            //m_struEventParamV50.uSeniorParam.struPosAlarm.wChannel[0] = 10;
            //m_struEventParamV50.uSeniorParam.struPosAlarm.wChannel[1] = 11;
            //m_struEventParamV50.uSeniorParam.struPosAlarm.byAllChan = 1;
            break;
        case EVENT_ACS_CASE:
            m_struEventParamV50.uSeniorParam.struACSAlarm.dwMajor = m_cmbMajorType.GetItemData(m_cmbMajorType.GetCurSel());
            m_struEventParamV50.uSeniorParam.struACSAlarm.dwMinor = m_cmbMinorType.GetItemData(m_cmbMinorType.GetCurSel());
            strncpy((char*)m_struEventParamV50.uSeniorParam.struACSAlarm.byCardNo, m_csCardNo.GetBuffer(0), ACS_CARD_NO_LEN);
            strncpy((char*)m_struEventParamV50.uSeniorParam.struACSAlarm.byName, m_csName.GetBuffer(0), NAME_LEN);
            StrToMac(sMac, m_struEventParamV50.uSeniorParam.struACSAlarm.byMACAddr);
            break;
        case EVENT_IOT_CASE:
            m_struEventParamV50.uSeniorParam.struIOTAlarm.wDeviceType = m_comboDeviceType.GetItemData(m_comboDeviceType.GetCurSel());
            m_struEventParamV50.uSeniorParam.struIOTAlarm.wEventType = m_comboFindSubType.GetItemData(m_comboFindSubType.GetCurSel());
            m_struEventParamV50.uSeniorParam.struIOTAlarm.byCaseSensitive = m_bCaseSensitive;
            m_struEventParamV50.uSeniorParam.struIOTAlarm.byCombinateMode = m_bCombinateMode;
            m_struEventParamV50.uSeniorParam.struIOTAlarm.bySearchType = 0;//当前仅支持0，界面就不增加了
            strncpy((char*)m_struEventParamV50.uSeniorParam.struIOTAlarm.sKeyWord[0], m_csKeyWord1.GetBuffer(0), STREAM_ID_LEN);
            strncpy((char*)m_struEventParamV50.uSeniorParam.struIOTAlarm.sKeyWord[1], m_csKeyWord2.GetBuffer(0), STREAM_ID_LEN);
            strncpy((char*)m_struEventParamV50.uSeniorParam.struIOTAlarm.sKeyWord[2], m_csKeyWord3.GetBuffer(0), STREAM_ID_LEN);
            break;
		default:
			break;
		}
		
		
        m_lFileHandle = NET_DVR_FindFileByEvent_V50(m_lLoginID, &m_struEventParamV50);
		
		if (m_lFileHandle < 0)
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_FindFileByEvent_V50");
			g_StringLanType(szLan, "获取文件列表失败!", "Fail to get file list");
			AfxMessageBox(szLan);
			return;
		}
		m_listRemoteFile.DeleteAllItems();
		DWORD dwThreadId;
		if (m_hFileThread == NULL)
		{
			m_hFileThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetEventThread),this,0,&dwThreadId);	
		}
		if (m_hFileThread == NULL)
		{
			g_StringLanType(szLan, "打开查找线程失败!", "Fail to open finding thread!");
			AfxMessageBox(szLan);
			return;
		}
		g_StringLanType(szLan, "停止查找", "Stop Searching");
		GetDlgItem(IDC_BTN_EVENT_SEARCH_LIST)->SetWindowText(szLan);
		m_bSearching = TRUE;
		GetDlgItem(IDC_STATIC_EVENT_SEARCH_STATE)->ShowWindow(SW_SHOW);
	}
	else
	{
		if (m_hFileThread)
		{
			m_IsQuit = FALSE;
			//TerminateThread(m_hFileThread, 0);
		}
		CloseHandle(m_hFileThread);
		m_hFileThread = NULL;
		NET_DVR_FindClose(m_lFileHandle);
		g_StringLanType(szLan, "查找", "Search");
		GetDlgItem(IDC_BTN_EVENT_SEARCH_LIST)->SetWindowText(szLan);
		m_bSearching = FALSE;
		GetDlgItem(IDC_STATIC_EVENT_SEARCH_STATE)->ShowWindow(SW_HIDE);
		m_iFileNum = 0;
	}
}

/*********************************************************
Function:	OnBnClickedBtnRemoteFilePlay
Desc:		Function for start playback
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::OnBnClickedBtnRemoteFilePlay()
{
	if (m_lPlayHandle == -1)
	{
		PlayBack();
	}
	else
	{
		if (m_bPause)
		{
			if (NET_DVR_PlayBackControl(m_lPlayHandle, NET_DVR_PLAYRESTART, 0, NULL))
			{
				m_bPause=FALSE;
				SetPlayState();
			}
		}
		else
		{
			if (m_bSetFrame || m_bChangeSpeed)
			{
				if (NET_DVR_PlayBackControl(m_lPlayHandle, NET_DVR_PLAYNORMAL, 0, NULL))
				{
					g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_PLAYNORMAL");
					m_bSetFrame=FALSE;
					m_bChangeSpeed = FALSE;
					SetPlayState();
				}
			}
			else
			{
				if (NET_DVR_PlayBackControl(m_lPlayHandle, NET_DVR_PLAYPAUSE, 0, NULL))
				{
					g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_PLAYPAUSE");
					m_bPause=TRUE;
					SetPauseState();
				}
				if (!NET_DVR_RefreshPlay(m_lPlayHandle))
				{
					g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RefreshPlay");
				}
			}
			
		}
	}
}

/*********************************************************
Function:	OnBnClickedBtnRemoteFileStop
Desc:		stop playback
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::OnBnClickedBtnRemoteFileStop()
{
	StopPlay();
}

/*********************************************************
Function:	OnBnClickedBtnRemoteFileSave
Desc:		downlaod remote file
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::OnBnClickedBtnRemoteFileSave()
{
	static char szFilter[]="All File(*.mp4)|*.*||";
	char m_sFile[256] = "c:\\Savefile.mp4";
	CString csFile;
	CFileDialog dlg(FALSE,"*.mp4","Savefile.mp4",OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,
		szFilter);
	if (dlg.DoModal()==IDOK)
	{
		csFile = dlg.GetPathName();
		UpdateData(FALSE);
		sprintf(m_sFile, "%s", csFile);
	}
	
	if (NET_DVR_PlayBackSaveData(m_lPlayHandle, m_sFile))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_PlayBackSaveData[%s]", m_sFile);
		m_bSaveFile = TRUE;
	}
	else
	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "文件保存失败", "Save the file failed");
		AfxMessageBox(szLan);
	}
}

/*********************************************************
Function:	OnBnClickedBtnRemoteFileStopSave
Desc:		stop downlaod remote file
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::OnBnClickedBtnRemoteFileStopSave()
{
	
	if (m_bSaveFile)
	{
		NET_DVR_StopPlayBackSave(m_lPlayHandle);
		m_bSaveFile = FALSE;
		char szLan[128] = {0};
		g_StringLanType(szLan, "停止保存成功", "Save the file successfully");
		AfxMessageBox(szLan);
	}
}

/*********************************************************
Function:	OnBnClickedBtnRemoteFileGotoBeginning
Desc:		return to the begion of current file and play,
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::OnBnClickedBtnRemoteFileGotoBeginning()
{
	if (NET_DVR_PlayBackControl(m_lPlayHandle,NET_DVR_PLAYSETPOS, 0, NULL))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_PLAYSETPOS goto beginning");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_PLAYSETPOS goto beginning");
	}
}

/*********************************************************
Function:	OnBnClickedBtnRemoteFileFast
Desc:		 playback faster
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::OnBnClickedBtnRemoteFileFast()
{
	if (NET_DVR_PlayBackControl(m_lPlayHandle, NET_DVR_PLAYFAST, 0, NULL))
	{	
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_PLAYFAST");
		m_bChangeSpeed = TRUE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_PLAYFAST");
	}
}

/*********************************************************
Function:	OnBnClickedBtnRemoteFileSlow
Desc:		playback slower
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::OnBnClickedBtnRemoteFileSlow()
{
	if (NET_DVR_PlayBackControl(m_lPlayHandle, NET_DVR_PLAYSLOW, 0, NULL))
	{	
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_PLAYSLOW");
		m_bChangeSpeed = TRUE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_PLAYSLOW");
	}
}

/*********************************************************
Function:	OnBnClickedBtnRemoteFileSnatchPic
Desc:		Take snapshot of current palyback file
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::OnBnClickedBtnRemoteFileSnatchPic()
{
	char cFilename[256] = {0};
	
	sprintf(cFilename, "%s\\%d_%d.bmp",g_struLocalParam.chPictureSavePath,m_iChanShowNum, GetTickCount());
	if (NET_DVR_PlayBackCaptureFile(m_lPlayHandle,cFilename))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "%s NET_DVR_PlayBackCaptureFile",cFilename);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_PlayBackCaptureFile");
	}
}

/*********************************************************
Function:	OnBnClickedBtnRemoteFileStep
Desc:		playback single frame
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::OnBnClickedBtnRemoteFileStep()
{
	if (NET_DVR_PlayBackControl(m_lPlayHandle, NET_DVR_PLAYFRAME, 0, NULL))
	{
		CButton *pButton;	
		
		if (EVENT_STREAM_INFO == m_comboMajorType.GetItemData(m_comboMajorType.GetCurSel()))
		{
			pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_PLAY_BY_ID_AND_TIME);
			pButton->SetIcon(m_hPlayEnableIcon);
			pButton->EnableWindow(TRUE);
		}
		else
		{
			pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_PLAY);
			pButton->SetIcon(m_hPlayEnableIcon);
			pButton->EnableWindow(TRUE);
		}
		
		m_bSetFrame = TRUE;
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_PLAYFRAME");
	}
}

/*********************************************************
Function:	OnBnClickedBtnRemoteFileSound
Desc:		open/close audio
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::OnBnClickedBtnRemoteFileSound()
{
	CButton *pButton;
	
	if (m_bSound)
	{
		if (NET_DVR_PlayBackControl(m_lPlayHandle, NET_DVR_PLAYSTOPAUDIO, 0, NULL))
		{
			m_bSound=FALSE;
			pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_SOUND);
			pButton->SetIcon(m_hSoundStopIcon);
			GetDlgItem(IDC_SLIDER_EVENT_FILE_VOLUME)->EnableWindow(FALSE);
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_PLAYSTOPAUDIO %s", g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[m_iChanIndex].chChanName); 
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_PLAYSTOPAUDIO %s", g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[m_iChanIndex].chChanName); 
		}
	}
	else
	{		
		if (NET_DVR_PlayBackControl(m_lPlayHandle, NET_DVR_PLAYSTARTAUDIO, 0, NULL))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_PLAYSTOPAUDIO %s", g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[m_iChanIndex].chChanName); 
			pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_SOUND);
			GetDlgItem(IDC_SLIDER_EVENT_FILE_VOLUME)->EnableWindow(TRUE);
			pButton->SetIcon(m_hSoundStartIcon);
			m_bSound=TRUE;
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_PLAYSTOPAUDIO %s", g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[m_iChanIndex].chChanName); 
		}
	}
}

/*********************************************************
Function:	OnClickListRemoteFile
Desc:		resolve the time of the event
Input:	void
Output:	void
Return:	void
**********************************************************/
void CDlgPlayEvent::OnClickListRemoteFile(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	POSITION  iPos = m_listRemoteFile.GetFirstSelectedItemPosition();
	if (iPos == NULL)
	{
		return;
	}
	char szTime[32] = {0};
	char szTmp[8] = {0};
	int iOffset = 0;
	m_iItemSel = m_listRemoteFile.GetNextSelectedItem(iPos);
	sprintf(szTime, "%s", m_listRemoteFile.GetItemText(m_iItemSel, 1));//start
	memcpy(szTmp, szTime, 4);
	m_struStartTime.dwYear = atoi(szTmp);
	
	iOffset+=4;
	memset(szTmp, 0, 8);
	memcpy(szTmp, szTime+iOffset, 2);	
	m_struStartTime.dwMonth = atoi(szTmp);
	
	iOffset+=2;memset(szTmp, 0, 8);
	memcpy(szTmp, szTime+iOffset, 2);
	m_struStartTime.dwDay = atoi(szTmp);
	
	iOffset+=2;memset(szTmp, 0, 8);
	memcpy(szTmp, szTime+iOffset, 2);
	m_struStartTime.dwHour = atoi(szTmp);
	
	iOffset+=2;memset(szTmp, 0, 8);
	memcpy(szTmp, szTime+iOffset, 2);
	m_struStartTime.dwMinute = atoi(szTmp);
	
	iOffset+=2;memset(szTmp, 0, 8);
	memcpy(szTmp, szTime+iOffset, 2);
	m_struStartTime.dwSecond = atoi(szTmp);
	
	memset(szTime, 0, 32);
	sprintf(szTime, "%s", m_listRemoteFile.GetItemText(m_iItemSel, 2));//stop time
	iOffset=0;memset(szTmp, 0, 8);
	memcpy(szTmp, szTime+iOffset, 4);
	m_struStopTime.dwYear = atoi(szTmp);
	
	iOffset+=4;memset(szTmp, 0, 8);
	memcpy(szTmp, szTime+iOffset, 2);
	m_struStopTime.dwMonth = atoi(szTmp);
	
	iOffset+=2;memset(szTmp, 0, 8);
	memcpy(szTmp, szTime+iOffset, 2);
	m_struStopTime.dwDay = atoi(szTmp);
	
	iOffset+=2;memset(szTmp, 0, 8);
	memcpy(szTmp, szTime+iOffset, 2);
	m_struStopTime.dwHour = atoi(szTmp);
	
	iOffset+=2;memset(szTmp, 0, 8);
	memcpy(szTmp, szTime+iOffset, 2);
	m_struStopTime.dwMinute = atoi(szTmp);
	
	iOffset+=2;memset(szTmp, 0, 8);
	memcpy(szTmp, szTime+iOffset, 2);
	m_struStopTime.dwSecond = atoi(szTmp);

    m_strFileName = m_listRemoteFile.GetItemText(m_iItemSel, 8); //file name
	
	if (EVENT_STREAM_INFO == m_comboMajorType.GetItemData(m_comboMajorType.GetCurSel()))
	{
		CButton * pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_PLAY_BY_ID_AND_TIME);
		pButton->SetIcon(m_hPlayEnableIcon);
		pButton->EnableWindow(TRUE);
		
		GetDlgItem(IDC_BTN_EVENT_FILE_PLAY)->EnableWindow(FALSE);
	}
	else
	{
		CButton * pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_PLAY);
		pButton->SetIcon(m_hPlayEnableIcon);
		pButton->EnableWindow(TRUE);
		
		GetDlgItem(IDC_BTN_EVENT_FILE_PLAY_BY_ID_AND_TIME)->EnableWindow(FALSE);
	}
	
	
	
	UpdateData(FALSE);
	*pResult = 0;
}

/*********************************************************
Function:	OnCtlColor
Desc:		refresh the window
Input:	void
Output:	void
Return:	void
**********************************************************/
HBRUSH CDlgPlayEvent::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if (m_lPlayHandle < 0 || !m_bPause)
	{
		return hbr;
	}
	if (!NET_DVR_RefreshPlay(m_lPlayHandle))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RefreshPlay");
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

/*********************************************************
Function:	OnReleasedcaptureSliderRemoteFileVolume
Desc:		responding to mouse up message of volume progress
Input:	pNMHDR, point to NMHDR; 
pResult, point to LRESULT;
Output:	none
Return:	none
**********************************************************/
void CDlgPlayEvent::OnReleasedcaptureSliderRemoteFileVolume(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	WORD temp = (0xffff)/100;
	WORD dwVolume = 0;
	char chPos = 0;
	chPos =(char)m_sliderVolume.GetPos();
	dwVolume =(WORD) (chPos*temp);
	m_sliderVolume.SetPos(chPos);
	if (m_lPlayHandle >= 0)
	{
		if (NET_DVR_PlayBackControl(m_lPlayHandle, NET_DVR_PLAYAUDIOVOLUME, dwVolume, NULL))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_PLAYAUDIOVOLUME %s", g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[m_iChanIndex].chChanName); 
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_PLAYAUDIOVOLUME %s", g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[m_iChanIndex].chChanName); 
		}		
	}
	*pResult = 0;
}

/*********************************************************
Function:	OnClickListChan
Desc:		refresh the channels's selected state
Input:	void
Output:	void
Return:	void
**********************************************************/
void CDlgPlayEvent::OnClickListChan(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	static int iAlarmInNo = 0,iMotDetChanNo = 0,iVacChanNo = 0,iVcaDetectNo = 0, iPosChanNo = 0;

	//POSITION  iPos = m_listChan.GetFirstSelectedItemPosition();//is not useful for small icon list
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	DWORD dwPos = GetMessagePos();
	CPoint point( LOWORD(dwPos), HIWORD(dwPos));
	
	m_listChan.ScreenToClient(&point);
	
	UINT uFlag = 0;
	int iSel = m_listChan.HitTest(point, &uFlag);//
	if (iSel < 0)
	{
		return;
	}
	
	CString csTmp;

	int iData = m_listChan.GetItemData(iSel);

	BOOL bRet = m_listChan.GetCheck(iSel);
	if (iData == 0xffff)
	{
        iAlarmInNo = 0;
        iMotDetChanNo = 0;
        iVacChanNo = 0;
        iVcaDetectNo = 0;
        iPosChanNo = 0;
		OnChkAllChan(!bRet);
		TRACE("uFlag = %d, bRet = %d\n", uFlag, bRet);
		if (uFlag == LVHT_ONITEMLABEL)//uFlag | LVHT_ONITEM > 0
		{
			m_listChan.SetCheck(iSel, !bRet);			
		}
		return;
	}

    switch (m_struEventParamV50.wMajorType)
	{
	case 0:    
        if (iMotDetChanNo < MAX_CHANNUM_V30)
        {
            if (!bRet)
            {
                m_struEventParamV50.uSeniorParam.struMotionParam.wMotDetChanNo[iMotDetChanNo++] = iData;
            }
            else if (iMotDetChanNo > 0)
            {
                m_struEventParamV50.uSeniorParam.struMotionParam.wMotDetChanNo[--iMotDetChanNo] = -1;
            }
        }     
        if (uFlag == LVHT_ONITEMLABEL)
        {
            m_listChan.SetCheck(iSel, !bRet);
        }		
        break;
    case 1: 
        if (iAlarmInNo < MAX_CHANNUM_V30*2)
        {
            if (!bRet)
            {
                m_struEventParamV50.uSeniorParam.struAlarmParam.wAlarmInNo[iAlarmInNo++] = iData;
            }
            else if (iAlarmInNo > 0)
            {
                m_struEventParamV50.uSeniorParam.struAlarmParam.wAlarmInNo[--iAlarmInNo] = -1;
            }

        }

        if (uFlag == LVHT_ONITEMLABEL)
        {
            m_listChan.SetCheck(iSel, !bRet);
		}
		break;
    case 2:  
        if (iVacChanNo < MAX_CHANNUM_V30)
        {
            if (!bRet)
            {
                m_struEventParamV50.uSeniorParam.struVcaParam.wChanNo[iVacChanNo++] = iData;
            }
            else if (iVacChanNo > 0)
            {
                m_struEventParamV50.uSeniorParam.struVcaParam.wChanNo[--iVacChanNo] = -1;
            }
        }

        if (uFlag == LVHT_ONITEMLABEL)//
        {
            m_listChan.SetCheck(iSel, bRet);
        }
        break;
	case 4://智能侦测
        if (iVcaDetectNo < MAX_CHANNUM_V30)
        {
            if (!bRet)
            {
                m_struEventParamV50.uSeniorParam.struVCADetect.wChanNo[iVcaDetectNo++] = iData;
            }
            else if (iVcaDetectNo > 0)
            {
                m_struEventParamV50.uSeniorParam.struVCADetect.wChanNo[--iVcaDetectNo] = -1;
            }
        }
	 
        
        if (uFlag == LVHT_ONITEMLABEL)//
        {
            m_listChan.SetCheck(iSel, bRet);
        }
		break;
    case EVENT_POS:
        if (iPosChanNo < MAX_CHANNUM_V30)
        {
            if (!bRet)
            {
                m_struEventParamV50.uSeniorParam.struVCADetect.wChanNo[iPosChanNo++] = iData;
            }
            else if (iPosChanNo > 0)
            {
                m_struEventParamV50.uSeniorParam.struVCADetect.wChanNo[--iPosChanNo] = -1;
            }
        }
    case EVENT_IOT_CASE:
        if (iPosChanNo < MAX_CHANNUM_V30)
        {
            if (!bRet)
            {
                m_struEventParamV50.uSeniorParam.struIOTAlarm.wChannel[iPosChanNo++] = iData;
            }
            else if (iPosChanNo > 0)
            {
                m_struEventParamV50.uSeniorParam.struIOTAlarm.wChannel[--iPosChanNo] = -1;
            }
        }

	default:
		break;
	}
	
	UpdateData(FALSE);
	*pResult = 0;
}



/*********************************************************
Function:	UpdateChanStatus
Desc:		update the status of all channels
Input:	none
Output:	none
Return:	none
**********************************************************/
void CDlgPlayEvent::UpdateChanStatus()
{
	int iIndex = 0;
	int i = 0;
	CString csTemp;
	m_listChan.DeleteAllItems();
	//get the whole state of all channels
    switch (m_struEventParamV50.wMajorType)
	{
	case EVENT_MOT_DET:
	case EVENT_VCA_BEHAVIOR:
    case EVENT_POS:
    case EVENT_IOT_CASE:
		//	case EVENT_AUX_ALARM:
		//insert all channel node
		m_iIPChanNum = 0;
		m_listChan.InsertItem(iIndex, "All Chans");
		m_listChan.SetItemData(iIndex, 0xffff);
		iIndex ++;	
		for (i=0; i<g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum; i++)
		{
			if (i<g_struDeviceInfo[m_iDeviceIndex].iAnalogChanNum)
			{
				csTemp.Format(ANALOG_C_FORMAT, g_struDeviceInfo[m_iDeviceIndex].iStartChan+i);
				m_listChan.InsertItem(iIndex, csTemp);
				m_listChan.SetItemData(iIndex, i + g_struDeviceInfo[m_iDeviceIndex].iStartChan);
				iIndex ++;	
			}
			else 
			{
				csTemp.Format(DIGITAL_C_FORMAT, i+ 1 - g_struDeviceInfo[m_iDeviceIndex].iAnalogChanNum/*g_struDeviceInfo[m_iDeviceIndex].iStartChan-g_struDeviceInfo[m_iDeviceIndex].pStruIPParaCfgV40[0].dwStartDChan*/);
				m_listChan.InsertItem(iIndex, csTemp);
				m_listChan.SetItemData(iIndex, i- g_struDeviceInfo[m_iDeviceIndex].iAnalogChanNum + g_struDeviceInfo[m_iDeviceIndex].pStruIPParaCfgV40[0].dwStartDChan);
				m_iIPChanNum ++;
				iIndex ++;	
			}
		}
        for (int i = 0; i < MAX_CHANNUM_V30; i++)
        {
            m_struEventParamV50.uSeniorParam.struMotionParam.wMotDetChanNo[i] = 0xffff;
        }
		break;
	case EVENT_ALARM_IN:
		m_iIPAlarmIn = 0;
		m_listChan.InsertItem(iIndex, "All AlarmIn");
		m_listChan.SetItemData(iIndex, 0xffff);
		iIndex ++;	
		for (i=0; i<MAX_IP_ALARMIN_V40; i++)
		{
			if (i<g_struDeviceInfo[m_iDeviceIndex].iAlarmInNum)
			{
				csTemp.Format(ALARM_IN_NAME, 1+i);
				m_listChan.InsertItem(iIndex, csTemp);
				m_listChan.SetItemData(iIndex, i);
				iIndex ++;	
			}
			else if (i>=MAX_ANALOG_ALARMIN && g_struDeviceInfo[m_iDeviceIndex].pStruIPAlarmInCfgV40->struIPAlarmInInfo[i -MAX_ANALOG_ALARMIN].dwIPID != 0)
			{
				csTemp.Format(IP_ALARM_IN_NAME, 1+i-MAX_ANALOG_ALARMIN);
				m_listChan.InsertItem(iIndex, csTemp);
				m_listChan.SetItemData(iIndex, i);
				m_iIPAlarmIn ++;
				iIndex ++;				
			}
		}
        for (int i = 0; i < 2 * MAX_CHANNUM_V30; i++)
        {
            m_struEventParamV50.uSeniorParam.struAlarmParam.wAlarmInNo[i] = 0xffff;
        }

		break;
	case EVENT_VCA_DETECTION:
		m_iIPChanNum = 0;
		m_listChan.InsertItem(iIndex, "All Chans");
		m_listChan.SetItemData(iIndex, 0xffff);	
		iIndex ++;	
		for (i=0; i<g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum; i++)
		{
            m_listChan.InsertItem(iIndex, g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].chChanName);
            m_listChan.SetItemData(iIndex, g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChannelNO);
            iIndex ++;
		}
        for (int i = 0; i < MAX_CHANNUM_V30; i++)
        {
            m_struEventParamV50.uSeniorParam.struVCADetect.wChanNo[i] = 0xffff;
        }
		break;
	default:
		break;
	}
}

/*********************************************************
Function:	OnChkAllChan
Desc:		select all channels or not	
Input:	void
Output:	void
Return:	void
**********************************************************/
void CDlgPlayEvent::OnChkAllChan(BOOL bAll) 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    CString csTmp;
    int iSel = 0;
    int iChanIndex = 0;
    int i = 0;
    
    switch (m_struEventParamV50.wMajorType)
    {
    case EVENT_MOT_DET:
        for (i = 0; i<g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum; i++)//MAX_CHANNUM_V30
        {
            iSel++;
            m_listChan.SetCheck(iSel, bAll);
            iChanIndex = m_listChan.GetItemData(iSel);
            
            if (bAll)
            {
                m_struEventParamV50.uSeniorParam.struMotionParam.wMotDetChanNo[i] = iChanIndex;
            }
            else
            {
                m_struEventParamV50.uSeniorParam.struMotionParam.wMotDetChanNo[i] = 0xffff;
            }
            if (iChanIndex == MAX_CHANNUM_V30-1)
            {
                break;
            }
        }
        break;
        
    case EVENT_VCA_BEHAVIOR:
        for (i = 0; i<g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum; i++)//MAX_CHANNUM_V30
        {
            iSel++;
            m_listChan.SetCheck(iSel, bAll);
            iChanIndex = m_listChan.GetItemData(iSel);
            if (bAll)
            {
                m_struEventParamV50.uSeniorParam.struVcaParam.wChanNo[i] = iChanIndex;
            }
            else
            {
                m_struEventParamV50.uSeniorParam.struVcaParam.wChanNo[i] = 0xffff;
            }
            
            if (iChanIndex == MAX_CHANNUM_V30-1)
            {
                break;
            }
        }
        break;
    case EVENT_ALARM_IN:
        for (i = 0; i<g_struDeviceInfo[m_iDeviceIndex].iAlarmInNum+m_iIPAlarmIn; i++)
        {
            iSel++;
            m_listChan.SetCheck(iSel, bAll);
            iChanIndex = m_listChan.GetItemData(iSel);
            
            if (bAll)
            {
                m_struEventParamV50.uSeniorParam.struAlarmParam.wAlarmInNo[i] = iChanIndex;
            }
            else
            {
                m_struEventParamV50.uSeniorParam.struAlarmParam.wAlarmInNo[i] = 0xffff;
            }
            if (iChanIndex == 128 -1)
            {
                break;
            }
            
        }
        break;
    case EVENT_VCA_DETECTION:
        for (i = 0; i < g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum; i++)
        {
            iSel++;
            m_listChan.SetCheck(iSel, bAll);
            iChanIndex = m_listChan.GetItemData(iSel);
            
            if (bAll)
            {
                m_struEventParamV50.uSeniorParam.struVCADetect.byAll = 1;
                m_struEventParamV50.uSeniorParam.struVCADetect.wChanNo[i] = iChanIndex;
            }
            else
            {
                m_struEventParamV50.uSeniorParam.struVCADetect.byAll = 0;
                m_struEventParamV50.uSeniorParam.struVCADetect.wChanNo[i] = 0xffff;
            }
            if (iChanIndex == 64 -1)
            {
                break;
                
            }
        }
        break;
    case EVENT_POS:
        for (i = 0 ;i <g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum;i++)
        {
            iSel++;
            m_listChan.SetCheck(iSel, bAll);
            iChanIndex = m_listChan.GetItemData(iSel);
            
            if (bAll)
            {
                m_struEventParamV50.uSeniorParam.struPosAlarm.byAllChan = 1;
                m_struEventParamV50.uSeniorParam.struPosAlarm.wChannel[i] = iChanIndex;;
            }
            else
            {
                m_struEventParamV50.uSeniorParam.struPosAlarm.byAllChan = 0;
                m_struEventParamV50.uSeniorParam.struPosAlarm.wChannel[i] = 0xffff;
            }

            if (iChanIndex == MAX_CHANNUM_V30 -1)
            {
                break;
            }
        }
        break;
    case EVENT_IOT_CASE:
        for (i = 0; i < g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum; i++)
        {
            iSel++;
            m_listChan.SetCheck(iSel, bAll);
            iChanIndex = m_listChan.GetItemData(iSel);

            if (bAll)
            {
                m_struEventParamV50.uSeniorParam.struIOTAlarm.byAllChan = 1;
                m_struEventParamV50.uSeniorParam.struIOTAlarm.wChannel[i] = iChanIndex;;
            }
            else
            {
                m_struEventParamV50.uSeniorParam.struIOTAlarm.byAllChan = 0;
                m_struEventParamV50.uSeniorParam.struIOTAlarm.wChannel[i] = 0xffff;
            }

            if (iChanIndex == MAX_CHANNUM_V30 - 1)
            {
                break;
            }
        }
        break;
    default:
        break;
    }
    
    
    UpdateData(FALSE);	
}
    
    /*********************************************************
    Function:	OnSelchangeComboMajorEvent
    Desc:		select the major event
    Input:	void
    Output:	void
    Return:	void
**********************************************************/
void CDlgPlayEvent::OnSelchangeComboMajorEvent() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_iMajorType != m_comboMajorType.GetItemData(m_comboMajorType.GetCurSel()))
	{
		m_iMajorType = m_comboMajorType.GetItemData(m_comboMajorType.GetCurSel());
        m_struEventParamV50.wMajorType = m_iMajorType;
		UpdateMinorEvent();
		UpdateChanStatus();
	}
	
	UpdateData(FALSE);
}

void CDlgPlayEvent::OnSelchangeComboAcsMajorEvent()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);

    int iSel = 0;
    switch (m_cmbMajorType.GetCurSel())
    {
    case 0:
        m_cmbMinorType.ResetContent();
        iSel = 0;
        iSel = AddMinorAllString(iSel);
        iSel = AddMinorDeviceString(iSel);
        iSel = AddMinorAlarmString(iSel);
        iSel = AddMinorDoorString(iSel);
        iSel = AddMinorCardReaderString(iSel);
        m_cmbMinorType.SetCurSel(0);
        break;
    case 1:
        m_cmbMinorType.ResetContent();
        iSel = 0;
        iSel = AddMinorAllString(iSel);
        iSel = AddMinorDeviceString(iSel);
        m_cmbMinorType.SetCurSel(0);
        break;
    case 2:
        m_cmbMinorType.ResetContent();
        iSel = 0;
        iSel = AddMinorAllString(iSel);
        iSel = AddMinorAlarmString(iSel);
        m_cmbMinorType.SetCurSel(0);
        break;
    case 3:
        m_cmbMinorType.ResetContent();
        iSel = 0;
        iSel = AddMinorAllString(iSel);
        iSel = AddMinorDoorString(iSel);
        m_cmbMinorType.SetCurSel(0);
        break;
    case 4:
        m_cmbMinorType.ResetContent();
        iSel = 0;
        iSel = AddMinorAllString(iSel);
        iSel = AddMinorCardReaderString(iSel);
        m_cmbMinorType.SetCurSel(0);
        break;
    default:
        break;
    }
    UpdateData(FALSE);
}

/*********************************************************
Function: UpdateMinorEvent	
Desc:		update the minor event	
Input:	void
Output:	void
Return:	void
**********************************************************/
void CDlgPlayEvent::UpdateMinorEvent()
{
	int index = 0;
	m_iMinorType = 0xffff;
	m_comboMinorEvent.ResetContent();
	char szLan[128] = {0};
	switch(m_iMajorType)
	{
	case EVENT_MOT_DET:
	case EVENT_ALARM_IN:
        g_StringLanType(szLan, "全部", "All");
        m_comboMinorEvent.AddString(szLan);
        m_comboMinorEvent.SetItemData(index, 0xffff);
        index++;
        GetDlgItem(IDC_STATIC_ID)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_RULEID)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_KEYWORD1)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_KEYWORD1)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_KEYWORD4)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_KEYWORD5)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CHK_COMBINATEMODE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CHK_CASESENSITIVE)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_STATIC_STREAM_ID)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_STREAM_ID)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_RELATED_CHANNEL)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_RELATED_CHANNEL)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_STATIC_ACS_MAJOR_EVENT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_ACS_MINOR_EVENT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_ACS_MAJOR_EVENT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_ACS_MINOR_EVENT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_ACS_CARD_NO)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_ACS_NAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_ACS_CARD_NO)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_ACS_NAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_MAC1)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_MAC2)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_MAC_ADDR)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_VOLUME2)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_ARCHIVE_LABEL)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_STATIC_DEVICE_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_DEVICE_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_SUB_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_FIND_SUB_TYPE)->ShowWindow(SW_HIDE);

		break;
    case EVENT_POS:
		//	case EVENT_AUX_ALARM:
		g_StringLanType(szLan, "全部", "All");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, 0xffff);
		index++;
		GetDlgItem(IDC_STATIC_ID)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_RULEID)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_STATIC_KEYWORD1)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_KEYWORD1)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_KEYWORD4)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_KEYWORD5)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_CHK_COMBINATEMODE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_CHK_CASESENSITIVE)->ShowWindow(SW_SHOW);

        GetDlgItem(IDC_STATIC_STREAM_ID)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_STREAM_ID)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_RELATED_CHANNEL)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_RELATED_CHANNEL)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_STATIC_ACS_MAJOR_EVENT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_ACS_MINOR_EVENT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_ACS_MAJOR_EVENT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_ACS_MINOR_EVENT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_ACS_CARD_NO)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_ACS_NAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_ACS_CARD_NO)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_ACS_NAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_MAC1)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_MAC2)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_MAC_ADDR)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_VOLUME2)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_ARCHIVE_LABEL)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_STATIC_DEVICE_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_DEVICE_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_SUB_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_FIND_SUB_TYPE)->ShowWindow(SW_HIDE);

		break;
	case EVENT_VCA_BEHAVIOR:
		g_StringLanType(szLan, "全部", "All");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, 0xffff);
		index++;
		
		g_StringLanType(szLan, "穿越警戒面", "Traverse Plane");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, EVENT_TRAVERSE_PLANE);
		index++;
		
		g_StringLanType(szLan, "进入区域", "Enter Area");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index,  EVENT_ENTER_AREA);
		index++;
		
		g_StringLanType(szLan, "离开区域", "Exit Area");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index,  EVENT_EXIT_AREA);
		index++;
		
		g_StringLanType(szLan, "入侵", "Intrusion");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index,  EVENT_INTRUSION);
		index++;
		
		g_StringLanType(szLan, "徘徊", "Loiter");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index,  EVENT_LOITER);
		index++;
		
		g_StringLanType(szLan, "物品遗留拿取", "Left and Take");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index,  EVENT_LEFT_TAKE);
		index++;
		
		g_StringLanType(szLan, "停车", "Parking");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index,  EVENT_PARKING);
		index++;
		
		g_StringLanType(szLan, "快速移动", "Running");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index,  EVENT_RUN);
		index++;
		
		g_StringLanType(szLan, "人员聚集", "Staff Density");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index,  EVENT_HIGH_DENSITY);
        index++;
		
        g_StringLanType(szLan, "贴纸条", "Stick up");
        m_comboMinorEvent.AddString(szLan);
        m_comboMinorEvent.SetItemData(index,  EVENT_STICK_UP);
        index++;
		
        g_StringLanType(szLan, "安装读卡器", "Install Scanner");
        m_comboMinorEvent.AddString(szLan);
        m_comboMinorEvent.SetItemData(index,  EVENT_INSTALL_SCANNER);
        index++;
		
        g_StringLanType(szLan, "操作超时", "over time");
        m_comboMinorEvent.AddString(szLan);
        m_comboMinorEvent.SetItemData(index,  EVENT_OPERATE_OVER_TIME);
        index++;
		
        g_StringLanType(szLan, "异常人脸", "Face Detect");
        m_comboMinorEvent.AddString(szLan);
        m_comboMinorEvent.SetItemData(index,  EVENT_FACE_DETECT);
        index++;
		
        g_StringLanType(szLan, "物品遗留", "Left");
        m_comboMinorEvent.AddString(szLan);
        m_comboMinorEvent.SetItemData(index,  EVENT_LEFT);
        index++;
        
        g_StringLanType(szLan, "物品拿取", "Take");
        m_comboMinorEvent.AddString(szLan);
        m_comboMinorEvent.SetItemData(index,  EVENT_TAKE);
        index++;
		
		g_StringLanType(szLan, "离岗事件", "Leave Position");
        m_comboMinorEvent.AddString(szLan);
        m_comboMinorEvent.SetItemData(index,  EVENT_LEAVE_POSITION);
        index++;
		
		g_StringLanType(szLan, "尾随", "Trail");
        m_comboMinorEvent.AddString(szLan);
        m_comboMinorEvent.SetItemData(index,  EVENT_TRAIL_INFO);
        index++;
		
        g_StringLanType(szLan, "人员进入", "Human enter");
        m_comboMinorEvent.AddString(szLan);
        m_comboMinorEvent.SetItemData(index, EVENT_HUMAN_ENTER);
        index++;

		g_StringLanType(szLan, "倒地", "Fall Down");
        m_comboMinorEvent.AddString(szLan);
        m_comboMinorEvent.SetItemData(index,  EVENT_FALL_DOWN_INFO);
        index++;
		
		g_StringLanType(szLan, "正常人脸", "Normal");
        m_comboMinorEvent.AddString(szLan);
        m_comboMinorEvent.SetItemData(index,  EVENT_FACE_CAPTURE_INFO);
        index++;
		
		g_StringLanType(szLan, "多张人脸", "Multi");
        m_comboMinorEvent.AddString(szLan);
        m_comboMinorEvent.SetItemData(index,  EVENT_MULTI_FACES_INFO);
        index++;
		
		g_StringLanType(szLan, "声强突变", "Audio Abnormal");
        m_comboMinorEvent.AddString(szLan);
        m_comboMinorEvent.SetItemData(index,  EVENT_AUDIO_ABNORMAL_INFO);
        index++;

        g_StringLanType(szLan, "戴墨镜人脸", "Sunglasses Face");
        m_comboMinorEvent.AddString(szLan);
        m_comboMinorEvent.SetItemData(index, EVENT_SUNGLASSES_FACE_INFO);
        index++;

        g_StringLanType(szLan, "打电话人脸", "Calling Face");
        m_comboMinorEvent.AddString(szLan);
        m_comboMinorEvent.SetItemData(index, EVENT_CALLING_FACE_INFO);
        index++;

        g_StringLanType(szLan, "剧烈运动", "Violent motion");
        m_comboMinorEvent.AddString(szLan);
        m_comboMinorEvent.SetItemData(index, EVENT_VIOLENT_MOTION);
        index++;

        g_StringLanType(szLan, "安全帽检测", "Safety Helmet");
        m_comboMinorEvent.AddString(szLan);
        m_comboMinorEvent.SetItemData(index, EVENT_SAFETY_HELMET);
        index++;

        g_StringLanType(szLan, "人数变化", "People num change");
        m_comboMinorEvent.AddString(szLan);
        m_comboMinorEvent.SetItemData(index, EVENT_PEOPLE_NUM_CHANGE);
        index++;

        g_StringLanType(szLan, "起身", "Get up");
        m_comboMinorEvent.AddString(szLan);
        m_comboMinorEvent.SetItemData(index, EVENT_GET_UP);
        index++;

        g_StringLanType(szLan, "折线攀高", "Adv reach height");
        m_comboMinorEvent.AddString(szLan);
        m_comboMinorEvent.SetItemData(index, EVENT_ADV_REACH_HEIGHT);
        index++;

        g_StringLanType(szLan, "起立", "Stand up");
        m_comboMinorEvent.AddString(szLan);
        m_comboMinorEvent.SetItemData(index, EVENT_STOOD_UP);
        index++;
		
		//rule id
		GetDlgItem(IDC_STATIC_ID)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_RULEID)->ShowWindow(SW_SHOW);

        GetDlgItem(IDC_STATIC_KEYWORD1)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_KEYWORD1)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_KEYWORD4)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_KEYWORD4)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CHK_COMBINATEMODE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CHK_CASESENSITIVE)->ShowWindow(SW_HIDE);
        
        GetDlgItem(IDC_STATIC_STREAM_ID)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_STREAM_ID)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_RELATED_CHANNEL)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_RELATED_CHANNEL)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_STATIC_ACS_MAJOR_EVENT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_ACS_MINOR_EVENT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_ACS_MAJOR_EVENT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_ACS_MINOR_EVENT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_ACS_CARD_NO)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_ACS_NAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_ACS_CARD_NO)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_ACS_NAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_MAC1)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_MAC2)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_MAC_ADDR)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_VOLUME2)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_ARCHIVE_LABEL)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_STATIC_DEVICE_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_DEVICE_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_SUB_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_FIND_SUB_TYPE)->ShowWindow(SW_HIDE);

		m_comboRuleID.SetCurSel(0);
		break;
    case EVENT_ACS_CASE:
        g_StringLanType(szLan, "全部", "All");
        m_comboMinorEvent.AddString(szLan);
        m_comboMinorEvent.SetItemData(index, 0xffff);
        index++;
        GetDlgItem(IDC_STATIC_ID)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_RULEID)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_KEYWORD1)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_KEYWORD1)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_KEYWORD4)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_KEYWORD5)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CHK_COMBINATEMODE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CHK_CASESENSITIVE)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_STATIC_STREAM_ID)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_STREAM_ID)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_RELATED_CHANNEL)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_RELATED_CHANNEL)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_VOLUME2)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_ARCHIVE_LABEL)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_STATIC_ACS_MAJOR_EVENT)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_ACS_MINOR_EVENT)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_COMBO_ACS_MAJOR_EVENT)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_COMBO_ACS_MINOR_EVENT)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_ACS_CARD_NO)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_ACS_NAME)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_ACS_CARD_NO)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_ACS_NAME)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_MAC1)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_MAC2)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_MAC_ADDR)->ShowWindow(SW_SHOW);

        GetDlgItem(IDC_STATIC_DEVICE_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_DEVICE_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_SUB_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_FIND_SUB_TYPE)->ShowWindow(SW_HIDE);

        break;
	case EVENT_STREAM_INFO:
		g_StringLanType(szLan, "流ID", "Stream ID");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, 0);
		index++;
		
		g_StringLanType(szLan, "定时录像", "Timing Record");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, EVENT_TIMING);
		index++;
		
		g_StringLanType(szLan, "移动侦测", "Motion Detect");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, EVENT_MOTION_DETECT);
		index++;
		
		g_StringLanType(szLan, "报警录像", "Alarm");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, EVENT_ALARM);
		index++;
		
		g_StringLanType(szLan, "报警或移动录像", "Alarm or Motion Detect");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, EVENT_ALARM_OR_MOTION_DETECT);
		index++;
		
		g_StringLanType(szLan, "报警和移动录像", "Alarm and Motion Detect");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, EVENT_ALARM_AND_MOTION_DETECT);
		index++;
		
		g_StringLanType(szLan, "命令触发", "Command");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, EVENT_COMMAND_TRIGGER);
		index++;
		
		g_StringLanType(szLan, "手动录像", "Manual");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, EVENT_MANNUAL);
		index++;
		
		g_StringLanType(szLan, "存档卷录像", "Backup volume");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, EVENT_BACKUP_VOLUME);
		index++;

		g_StringLanType(szLan, "信号量", "Semaphore");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, STREAM_EVENT_SEMAPHORE);
		index++;

		g_StringLanType(szLan, "遮挡", "Hide");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, STREAM_EVENT_HIDE);
		index++;

		g_StringLanType(szLan, "逆行", "Inverse");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, STREAM_EVENT_INVERSE);
		index++;

		g_StringLanType(szLan, "视频丢失", "Video Lost");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, STREAM_EVENT_VIDEO_LOST);
		index++;

		g_StringLanType(szLan, "无线报警", "Wireless Alarm");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, STREAM_EVENT_WIRELESS_ALARM);
		index++;

		g_StringLanType(szLan, "PIR报警", "PIR Alarm");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, STREAM_EVENT_PIR_ALARM);
		index++;

		g_StringLanType(szLan, "呼救报警", "Call Help Alarm");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, STREAM_EVENT_CALLHELP_ALARM);
		index++;

		g_StringLanType(szLan, "人脸抓拍", "Face snap");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, STREAM_EVENT_FACESNAP);
		index++;

		g_StringLanType(szLan, "人脸侦测", "Face Detection");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, STREAM_EVENT_FACE_DETECTION);
		index++;

		g_StringLanType(szLan, "车辆检测", "ITS Plate");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, STREAM_EVENT_ITS_PLATE);
		index++;

		g_StringLanType(szLan, "客流量统计", "PDC");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, STREAM_EVENT_PDC);
		index++;
		
		g_StringLanType(szLan, "场景变更", "Scene Change Detection");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, STREAM_EVENT_SCENECHANGE_DETECTION);
		index++;
		
		g_StringLanType(szLan, "虚焦侦测", "Defocus Detection");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, STREAM_EVENT_DEFOCUS_DETECTION);
		index++;
		
		g_StringLanType(szLan, "音频异常", "Audio Exception");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, STREAM_EVENT_AUDIOEXCEPTION);
		index++;
		
		g_StringLanType(szLan, "穿越警戒面", "VCA Traverse Plane");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, VCA_EVENT_TRAVERSE_PLANE);
		index++;
		
		g_StringLanType(szLan, "周界入侵", "VCA Intrusion");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, VCA_EVENT_INTRUSION);
		index++;
		
		g_StringLanType(szLan, "进入区域", "VCA Enter Area");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, VCA_EVENT_ENTER_AREA);
		index++;
		
		g_StringLanType(szLan, "离开区域", "VCA Exit Area");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, VCA_EVENT_EXIT_AREA);
		index++;
		
		g_StringLanType(szLan, "徘徊侦测", "VCA Loiter");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, VCA_EVENT_LOITER);
		index++;
		
		g_StringLanType(szLan, "人员聚集", "VCA High Density");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, VCA_EVENT_HIGH_DENSITY);
		index++;

		g_StringLanType(szLan, "快速移动", "VCA Run");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, VCA_EVENT_RUN);
		index++;

		g_StringLanType(szLan, "非法停车", "VCA Parking");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, VCA_EVENT_PARKING);
		index++;

		g_StringLanType(szLan, "物品遗留", "VCA Left");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, VCA_EVENT_LEFT);
		index++;

		g_StringLanType(szLan, "物品拿取", "VCA Take");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, VCA_EVENT_TAKE);
		index++;

		GetDlgItem(IDC_STATIC_ID)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_RULEID)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_STATIC_KEYWORD1)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_KEYWORD1)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_KEYWORD4)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_KEYWORD5)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CHK_COMBINATEMODE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CHK_CASESENSITIVE)->ShowWindow(SW_HIDE);
        
        GetDlgItem(IDC_STATIC_STREAM_ID)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_STREAM_ID)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_RELATED_CHANNEL)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_RELATED_CHANNEL)->ShowWindow(SW_SHOW);

        GetDlgItem(IDC_STATIC_VOLUME2)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_ARCHIVE_LABEL)->ShowWindow(SW_SHOW);

        GetDlgItem(IDC_STATIC_ACS_MAJOR_EVENT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_ACS_MINOR_EVENT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_ACS_MAJOR_EVENT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_ACS_MINOR_EVENT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_ACS_CARD_NO)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_ACS_NAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_ACS_CARD_NO)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_ACS_NAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_MAC1)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_MAC2)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_MAC_ADDR)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_STATIC_DEVICE_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_DEVICE_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_SUB_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_FIND_SUB_TYPE)->ShowWindow(SW_HIDE);

		break;
	case EVENT_VCA_DETECTION:
		g_StringLanType(szLan, "全部", "All");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, EVENT_ALL);
		index++;
		g_StringLanType(szLan, "越警侦测", "Traverse Plane");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, EVENT_VCA_TRAVERSE_PLANE);
		index++;
		g_StringLanType(szLan, "区域入侵", "field detect");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, EVENT_FIELD_DETECTION);
		index++;
		g_StringLanType(szLan, "人脸识别", "face detect");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, EVENT_FACE_DETECTION);
		index++;
		g_StringLanType(szLan, "音频输入异常", "Audio Unnormal");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, EVENT_AUDIO_INPUT_ALARM);
		index++;
		g_StringLanType(szLan, "声强突变侦测", "Audio Detect");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, EVENT_SOUND_INTENSITY_ALARM);
		index++;
		g_StringLanType(szLan, "虚焦侦测", "virtual focus alarm");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, EVENT_VIRTUAL_FOCUS_ALARM);
		index++;
		g_StringLanType(szLan, "场景变更侦测", "scene change alarm");
		m_comboMinorEvent.AddString(szLan);
		m_comboMinorEvent.SetItemData(index, EVENT_SCENE_CHANGE_ALARM);
		index++;

        GetDlgItem(IDC_STATIC_KEYWORD1)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_KEYWORD1)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_KEYWORD4)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_KEYWORD5)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CHK_COMBINATEMODE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CHK_CASESENSITIVE)->ShowWindow(SW_HIDE);
        
        GetDlgItem(IDC_STATIC_STREAM_ID)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_STREAM_ID)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_RELATED_CHANNEL)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_RELATED_CHANNEL)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_VOLUME2)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_ARCHIVE_LABEL)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_STATIC_ACS_MAJOR_EVENT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_ACS_MINOR_EVENT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_ACS_MAJOR_EVENT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_ACS_MINOR_EVENT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_ACS_CARD_NO)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_ACS_NAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_ACS_CARD_NO)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_ACS_NAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_MAC1)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_MAC2)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_MAC_ADDR)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_STATIC_DEVICE_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_DEVICE_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_SUB_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_FIND_SUB_TYPE)->ShowWindow(SW_HIDE);

		break;
    case EVENT_IOT_CASE:
        g_StringLanType(szLan, "全部", "All");
        m_comboMinorEvent.AddString(szLan);
        m_comboMinorEvent.SetItemData(index, 0xffff);
        index++;
        GetDlgItem(IDC_STATIC_ID)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_RULEID)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_KEYWORD1)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_KEYWORD1)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_KEYWORD4)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_KEYWORD5)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_CHK_COMBINATEMODE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_CHK_CASESENSITIVE)->ShowWindow(SW_SHOW);

        GetDlgItem(IDC_STATIC_STREAM_ID)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_STREAM_ID)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_RELATED_CHANNEL)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_RELATED_CHANNEL)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_VOLUME2)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_ARCHIVE_LABEL)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_STATIC_ACS_MAJOR_EVENT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_ACS_MINOR_EVENT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_ACS_MAJOR_EVENT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_ACS_MINOR_EVENT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_ACS_CARD_NO)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_ACS_NAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_ACS_CARD_NO)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_ACS_NAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_MAC1)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_MAC2)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_MAC_ADDR)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_STATIC_DEVICE_TYPE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_COMBO_DEVICE_TYPE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_SUB_TYPE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_COMBO_FIND_SUB_TYPE)->ShowWindow(SW_SHOW);

        break;
	default:
		break;
	}
	m_comboMinorEvent.SetCurSel(0);
}

/*********************************************************
Function:	OnSelchangeComboMinorEvent
Desc:		
Input:	void
Output:	void
Return:	void
**********************************************************/
void CDlgPlayEvent::OnSelchangeComboMinorEvent() 
{
	// TODO: Add your control notification handler code here
	
}

/*********************************************************
Function:	PlayBack
Desc:		begin play back 
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayEvent::PlayBackByIDAndTime()
{
	UpdateData(TRUE);
	
	int m_nVerifyret = -1;
	int iFileSelPos = 0;
	HWND hPlayWnd=m_staticPlayWnd.GetSafeHwnd();
	POSITION  posItem = m_listRemoteFile.GetFirstSelectedItemPosition();
	char szLan[128] = {0};
	if (posItem == NULL)
	{
		g_StringLanType(szLan, "请选择要播放的文件!", "Please select the file to play");
		AfxMessageBox(szLan); 
		return;
	}
	
	iFileSelPos = m_listRemoteFile.GetNextSelectedItem(posItem);
	DWORD dwFileIndex = atoi(m_listRemoteFile.GetItemText(iFileSelPos,5));
	
	
	NET_DVR_TIME struStartTime,struStopTime;
	NET_DVR_VOD_PARA struVODPara;
	memset(&struVODPara, 0, sizeof(NET_DVR_VOD_PARA));
	
	//	remoteplay_info.srcfilename=m_szFileName;
	if (m_lPlayHandle>=0)
	{
		if (NET_DVR_StopPlayBack(m_lPlayHandle))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopPlayBack");
		}
		m_lPlayHandle = -1;
		Sleep(400);
	}
	if (m_lPlayHandle == -1)
	{
		m_iChanShowNum = m_iPlaybackChannel;
		time_t tmp;
		ConvertTime(&tmp, &m_struStartTime, FALSE);
		//tmp -= m_iTime;
		ConvertTime(&tmp, &m_struStartTime, TRUE);
		
		ConvertTime(&tmp, &m_struStopTime, FALSE);
		//tmp += m_iTime;
		ConvertTime(&tmp, &m_struStopTime, TRUE);
		memcpy(&struStartTime, &m_struStartTime, sizeof(NET_DVR_TIME));
		memcpy(&struStopTime, &m_struStopTime, sizeof(NET_DVR_TIME));	
		
		// 给struVODPara赋值
		struVODPara.dwSize = sizeof(NET_DVR_VOD_PARA);
		struVODPara.struIDInfo.dwSize = sizeof(NET_DVR_STREAM_INFO);
		strncpy((char*)struVODPara.struIDInfo.byID, m_strStreamID.GetBuffer(0), STREAM_ID_LEN);
		struVODPara.struIDInfo.dwChannel = m_iRelatedChannel;
		struVODPara.hWnd = hPlayWnd;
		memcpy(&struVODPara.struBeginTime, &struStartTime, sizeof(NET_DVR_TIME));
		memcpy(&struVODPara.struEndTime, &struStopTime, sizeof(NET_DVR_TIME));
		if (m_comboMinorEvent.GetItemData(m_comboMinorEvent.GetCurSel()) == EVENT_BACKUP_VOLUME)
		{
			struVODPara.byVolumeType = 1; //回放存档卷
		}
		else
		{
			struVODPara.byVolumeType = 0; //回放普通卷
		}
		
		struVODPara.byVolumeNum = m_dwBackupVolume;
		struVODPara.dwFileIndex = dwFileIndex;
		struVODPara.byDrawFrame = m_bDrawFrame;
		
        if (m_strFileName.GetLength() > 0)
        {
            m_lPlayHandle = NET_DVR_PlayBackByName(m_lLoginID, m_strFileName.GetBuffer(0), hPlayWnd);
            if (m_lPlayHandle == -1)
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_PlayBackByName");
                g_StringLanType(szLan, "通过文件名回放失败", "Fail to play back remote by name");
                AfxMessageBox(szLan);
                return;
            }
            else
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_PlayBackByName");
            }
        }
        else
        {
            m_lPlayHandle = NET_DVR_PlayBackByTime_V40(m_lLoginID, &struVODPara);
            if (m_lPlayHandle == -1)
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_PlayBackByTime_V40");
                g_StringLanType(szLan, "通过ID和时间远程回放失败", "Fail to play back remote by ID and time");
                AfxMessageBox(szLan);
                return;
            }
            else
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_PlayBackByTime_V40");
            }
        }
		
		int idx = NET_DVR_GetPlayBackPlayerIndex(m_lPlayHandle);

        if (m_bSaveByPlay)
        {
            char m_sFile[256] = {0};
            char sIPV6Addr[130] = { 0 };
            for (int i = 0; i < sizeof(g_struDeviceInfo[m_iDeviceIndex].chDeviceIP); i++)
            {
                if (g_struDeviceInfo[m_iDeviceIndex].chDeviceIP[i] == '\0')
                {
                    break;
                }
                else if (g_struDeviceInfo[m_iDeviceIndex].chDeviceIP[i] == ':')
                {
                    sIPV6Addr[i] = '-';
                }
                else
                {
                    sIPV6Addr[i] = g_struDeviceInfo[m_iDeviceIndex].chDeviceIP[i];
                }
            }
            CTime ctime = CTime::GetCurrentTime();

            sprintf(m_sFile, "%s\\%s_%d_%d_%d_%d_%d_%d_%d_savefile.mp4", g_struLocalParam.chDownLoadPath, sIPV6Addr, ctime.GetYear(),
                ctime.GetMonth(), ctime.GetDay(), ctime.GetHour(), ctime.GetMinute(), ctime.GetSecond(), ctime.GetTickCount);
            if (NET_DVR_PlayBackSaveData(m_lPlayHandle, m_sFile))
            {
                g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_PlayBackSaveData[%s]", m_sFile);
                m_bSaveFile = TRUE;
            }
            else
            {
                char szLan[128] = { 0 };
                g_StringLanType(szLan, "文件保存失败", "Save the file failed");
                AfxMessageBox(szLan);
            }
        }
		
		NET_DVR_PlayBackControl(m_lPlayHandle, NET_DVR_PLAYSTART, 0, NULL);
		
		if (NET_DVR_PlayBackControl(m_lPlayHandle, NET_DVR_PLAYSTARTAUDIO, 0, NULL))
		{
			m_bSound=TRUE;
			NET_DVR_PlayBackControl(m_lPlayHandle, NET_DVR_PLAYAUDIOVOLUME, (0xffff)/2, NULL);
			m_sliderVolume.SetPos(50);
			((CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_SOUND))->SetIcon(m_hSoundStartIcon);
		}
		else
		{
			m_bSound=FALSE;
			((CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_SOUND))->SetIcon(m_hSoundStopIcon);
		}
		SetPlayStateIDTime();
		SetTimer(PLAYBYTIME_TIMER, 5000, NULL);
	}
	else
	{
		if (m_bPause)
		{
			if (NET_DVR_PlayBackControl(m_lPlayHandle, NET_DVR_PLAYRESTART, 0, NULL))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_PLAYRESTART");
				m_bPause=FALSE;
				SetPlayStateIDTime();
			}
		}
		else
		{
			if (NET_DVR_PlayBackControl(m_lPlayHandle, NET_DVR_PLAYPAUSE, 0, NULL))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_PLAYPAUSE");
				m_bPause=TRUE;
				CButton *pButton;	
				pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_PLAY_BY_ID_AND_TIME);
				pButton->SetIcon(m_hPlayEnableIcon);
				pButton->EnableWindow(TRUE);
			}
		}
	}
}

void CDlgPlayEvent::OnBtnEventFilePlayByIdAndTime() 
{
	// TODO: Add your control notification handler code here
	if (m_lPlayHandle == -1)
	{
		PlayBackByIDAndTime();
	}
	else
	{
		if (m_bPause)
		{
			if (NET_DVR_PlayBackControl(m_lPlayHandle, NET_DVR_PLAYRESTART, 0, NULL))
			{
				m_bPause=FALSE;
				SetPlayStateIDTime();
			}
		}
		else
		{
			if (m_bSetFrame || m_bChangeSpeed)
			{
				if (NET_DVR_PlayBackControl(m_lPlayHandle, NET_DVR_PLAYNORMAL, 0, NULL))
				{
					g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_PLAYNORMAL");
					m_bSetFrame=FALSE;
					m_bChangeSpeed = FALSE;
					SetPlayStateIDTime();
				}
			}
			else
			{
				if (NET_DVR_PlayBackControl(m_lPlayHandle, NET_DVR_PLAYPAUSE, 0, NULL))
				{
					g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_PLAYPAUSE");
					m_bPause=TRUE;
					SetPauseStateIDTime();
				}
				if (!NET_DVR_RefreshPlay(m_lPlayHandle))
				{
					g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RefreshPlay");
				}
			}
			
		}
	}
}

int CDlgPlayEvent::AddMinorAllString(int iStartSel)
{
    int iSel = iStartSel;

    m_cmbMinorType.AddString("All");
    m_cmbMinorType.SetItemData(iSel, 0xffffffff);
    iSel++;

    return iSel;
}

int CDlgPlayEvent::AddMinorDeviceString(int iStartSel)
{
    CString szTemp;
    int iSel = iStartSel;

    szTemp.Format("HOST_ANTI_DISMANTLE");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_HOST_ANTI_DISMANTLE);
    iSel++;

    szTemp.Format("OFFLINE_ECENT_NEARLY_FULL");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_OFFLINE_ECENT_NEARLY_FULL);
    iSel++;

    szTemp.Format("NET_BROKEN");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_NET_BROKEN);
    iSel++;

    szTemp.Format("NET_RESUME");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_NET_RESUME);
    iSel++;

    szTemp.Format("LOW_BATTERY");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_LOW_BATTERY);
    iSel++;

    szTemp.Format("BATTERY_RESUME");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_BATTERY_RESUME);
    iSel++;

    szTemp.Format("AC_OFF");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_AC_OFF);
    iSel++;

    szTemp.Format("AC_RESUME");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_AC_RESUME);
    iSel++;

    szTemp.Format("SD_CARD_FULL");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_SD_CARD_FULL);
    iSel++;

    szTemp.Format("LINKAGE_CAPTURE_PIC");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_LINKAGE_CAPTURE_PIC);
    iSel++;

    szTemp.Format("IMAGE_QUALITY_LOW");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_IMAGE_QUALITY_LOW);
    iSel++;

    szTemp.Format("FINGER_PRINT_QUALITY_LOW");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FINGER_PRINT_QUALITY_LOW);
    iSel++;

    szTemp.Format("BATTERY_ELECTRIC_LOW");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_BATTERY_ELECTRIC_LOW);
    iSel++;

    szTemp.Format("BATTERY_ELECTRIC_RESUME");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_BATTERY_ELECTRIC_RESUME);
    iSel++;

    szTemp.Format("FIRE_IMPORT_SHORT_CIRCUIT");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FIRE_IMPORT_SHORT_CIRCUIT);
    iSel++;

    szTemp.Format("FIRE_IMPORT_BROKEN_CIRCUIT");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FIRE_IMPORT_BROKEN_CIRCUIT);
    iSel++;

    szTemp.Format("FIRE_IMPORT_RESUME");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FIRE_IMPORT_RESUME);
    iSel++;

    szTemp.Format("MASTER_RS485_LOOPNODE_BROKEN");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_MASTER_RS485_LOOPNODE_BROKEN);
    iSel++;

    szTemp.Format("MASTER_RS485_LOOPNODE_RESUME");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_MASTER_RS485_LOOPNODE_RESUME);
    iSel++;

    szTemp.Format("LOCAL_CONTROL_OFFLINE");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_LOCAL_CONTROL_OFFLINE);
    iSel++;

    szTemp.Format("LOCAL_CONTROL_RESUME");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_LOCAL_CONTROL_RESUME);
    iSel++;

    szTemp.Format("LOCAL_DOWNSIDE_RS485_LOOPNODE_BROKEN");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_LOCAL_DOWNSIDE_RS485_LOOPNODE_BROKEN);
    iSel++;

    szTemp.Format("LOCAL_DOWNSIDE_RS485_LOOPNODE_RESUME");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_LOCAL_DOWNSIDE_RS485_LOOPNODE_RESUME);
    iSel++;

    szTemp.Format("DISTRACT_CONTROLLER_ONLINE");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_DISTRACT_CONTROLLER_ONLINE);
    iSel++;

    szTemp.Format("DISTRACT_CONTROLLER_OFFLINE");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_DISTRACT_CONTROLLER_OFFLINE);
    iSel++;

    szTemp.Format("FIRE_BUTTON_TRIGGER");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FIRE_BUTTON_TRIGGER);
    iSel++;

    szTemp.Format("FIRE_BUTTON_RESUME");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FIRE_BUTTON_RESUME);
    iSel++;

    szTemp.Format("MAINTENANCE_BUTTON_TRIGGER");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_MAINTENANCE_BUTTON_TRIGGER);
    iSel++;

    szTemp.Format("MAINTENANCE_BUTTON_RESUME");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_MAINTENANCE_BUTTON_RESUME);
    iSel++;

    szTemp.Format("EMERGENCY_BUTTON_TRIGGER");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_EMERGENCY_BUTTON_TRIGGER);
    iSel++;

    szTemp.Format("EMERGENCY_BUTTON_RESUME");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_EMERGENCY_BUTTON_RESUME);
    iSel++;

    szTemp.Format("MAC_DETECT");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_MAC_DETECT);
    iSel++;

    return iSel;
}

int CDlgPlayEvent::AddMinorAlarmString(int iStartSel)
{
    CString szTemp;
    int iSel = iStartSel;

    szTemp.Format("ALARMIN_SHORT_CIRCUIT");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_ALARMIN_SHORT_CIRCUIT);
    iSel++;

    szTemp.Format("ALARMIN_BROKEN_CIRCUIT");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_ALARMIN_BROKEN_CIRCUIT);
    iSel++;

    szTemp.Format("ALARMIN_EXCEPTION");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_ALARMIN_EXCEPTION);
    iSel++;

    szTemp.Format("ALARMIN_RESUME");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_ALARMIN_RESUME);
    iSel++;

    szTemp.Format("CASE_SENSOR_ALARM");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_CASE_SENSOR_ALARM);
    iSel++;

    szTemp.Format("CASE_SENSOR_RESUME");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_CASE_SENSOR_RESUME);
    iSel++;

    return iSel;
}

int CDlgPlayEvent::AddMinorDoorString(int iStartSel)
{
    CString szTemp;
    int iSel = iStartSel;

    szTemp.Format("LEADER_CARD_OPEN_BEGIN");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_LEADER_CARD_OPEN_BEGIN);
    iSel++;

    szTemp.Format("LEADER_CARD_OPEN_END");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_LEADER_CARD_OPEN_END);
    iSel++;

    szTemp.Format("ALWAYS_OPEN_BEGIN");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_ALWAYS_OPEN_BEGIN);
    iSel++;

    szTemp.Format("ALWAYS_OPEN_END");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_ALWAYS_OPEN_END);
    iSel++;

    szTemp.Format("ALWAYS_CLOSE_BEGIN");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_ALWAYS_CLOSE_BEGIN);
    iSel++;

    szTemp.Format("ALWAYS_CLOSE_END");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_ALWAYS_CLOSE_END);
    iSel++;

    szTemp.Format("LOCK_OPEN");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_LOCK_OPEN);
    iSel++;

    szTemp.Format("LOCK_CLOSE");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_LOCK_CLOSE);
    iSel++;

    szTemp.Format("DOOR_BUTTON_PRESS");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_DOOR_BUTTON_PRESS);
    iSel++;

    szTemp.Format("DOOR_BUTTON_RELEASE");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_DOOR_BUTTON_RELEASE);
    iSel++;

    szTemp.Format("DOOR_OPEN_NORMAL");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_DOOR_OPEN_NORMAL);
    iSel++;

    szTemp.Format("DOOR_CLOSE_NORMAL");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_DOOR_CLOSE_NORMAL);
    iSel++;

    szTemp.Format("DOOR_OPEN_ABNORMAL");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_DOOR_OPEN_ABNORMAL);
    iSel++;

    szTemp.Format("DOOR_OPEN_TIMEOUT");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_DOOR_OPEN_TIMEOUT);
    iSel++;

    szTemp.Format("REMOTE_OPEN_DOOR");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_REMOTE_OPEN_DOOR);
    iSel++;

    szTemp.Format("REMOTE_CLOSE_DOOR");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_REMOTE_CLOSE_DOOR);
    iSel++;

    szTemp.Format("REMOTE_ALWAYS_OPEN");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_REMOTE_ALWAYS_OPEN);
    iSel++;

    szTemp.Format("REMOTE_ALWAYS_CLOSE");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_REMOTE_ALWAYS_CLOSE);
    iSel++;

    szTemp.Format("NOT_BELONG_MULTI_GROUP");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_NOT_BELONG_MULTI_GROUP);
    iSel++;

    szTemp.Format("INVALID_MULTI_VERIFY_PERIOD");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_INVALID_MULTI_VERIFY_PERIOD);
    iSel++;

    szTemp.Format("MULTI_VERIFY_SUPER_RIGHT_FAIL");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_MULTI_VERIFY_SUPER_RIGHT_FAIL);
    iSel++;

    szTemp.Format("MULTI_VERIFY_REMOTE_RIGHT_FAIL");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_MULTI_VERIFY_REMOTE_RIGHT_FAIL);
    iSel++;

    szTemp.Format("MULTI_VERIFY_SUCCESS");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_MULTI_VERIFY_SUCCESS);
    iSel++;

    szTemp.Format("MULTI_VERIFY_NEED_REMOTE_OPEN");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_MULTI_VERIFY_NEED_REMOTE_OPEN);
    iSel++;

    szTemp.Format("MULTI_VERIFY_SUPERPASSWD_VERIFY_SUCCESS");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_MULTI_VERIFY_SUPERPASSWD_VERIFY_SUCCESS);
    iSel++;

    szTemp.Format("MULTI_VERIFY_REPEAT_VERIFY_FAIL");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_MULTI_VERIFY_REPEAT_VERIFY_FAIL);
    iSel++;

    szTemp.Format("MULTI_VERIFY_TIMEOUT");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_MULTI_VERIFY_TIMEOUT);
    iSel++;

    szTemp.Format("REMOTE_CAPTURE_PIC");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_REMOTE_CAPTURE_PIC);
    iSel++;

    szTemp.Format("DOORBELL_RINGING");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_DOORBELL_RINGING);
    iSel++;

    szTemp.Format("SECURITY_MODULE_DESMANTLE_ALARM");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_SECURITY_MODULE_DESMANTLE_ALARM);
    iSel++;

    szTemp.Format("CALL_CENTER");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_CALL_CENTER);
    iSel++;

    szTemp.Format("FIRSTCARD_AUTHORIZE_BEGIN");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FIRSTCARD_AUTHORIZE_BEGIN);
    iSel++;

    szTemp.Format("FIRSTCARD_AUTHORIZE_END");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FIRSTCARD_AUTHORIZE_END);
    iSel++;

    szTemp.Format("DOORLOCK_INPUT_SHORT_CIRCUIT");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_DOORLOCK_INPUT_SHORT_CIRCUIT);
    iSel++;

    szTemp.Format("DOORLOCK_INPUT_BROKEN_CIRCUIT");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_DOORLOCK_INPUT_BROKEN_CIRCUIT);
    iSel++;

    szTemp.Format("DOORLOCK_INPUT_EXCEPTION");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_DOORLOCK_INPUT_EXCEPTION);
    iSel++;

    szTemp.Format("DOORCONTACT_INPUT_SHORT_CIRCUIT");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_DOORCONTACT_INPUT_SHORT_CIRCUIT);
    iSel++;

    szTemp.Format("DOORCONTACT_INPUT_BROKEN_CIRCUIT");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_DOORCONTACT_INPUT_BROKEN_CIRCUIT);
    iSel++;

    szTemp.Format("DOORCONTACT_INPUT_EXCEPTION");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_DOORCONTACT_INPUT_EXCEPTION);
    iSel++;

    szTemp.Format("OPENBUTTON_INPUT_SHORT_CIRCUIT");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_OPENBUTTON_INPUT_SHORT_CIRCUIT);
    iSel++;

    szTemp.Format("OPENBUTTON_INPUT_BROKEN_CIRCUIT");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_OPENBUTTON_INPUT_BROKEN_CIRCUIT);
    iSel++;

    szTemp.Format("OPENBUTTON_INPUT_EXCEPTION");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_OPENBUTTON_INPUT_EXCEPTION);
    iSel++;

    szTemp.Format("DOORLOCK_OPEN_EXCEPTION");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_DOORLOCK_OPEN_EXCEPTION);
    iSel++;

    szTemp.Format("DOORLOCK_OPEN_TIMEOUT");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_DOORLOCK_OPEN_TIMEOUT);
    iSel++;

    szTemp.Format("FIRSTCARD_OPEN_WITHOUT_AUTHORIZE");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FIRSTCARD_OPEN_WITHOUT_AUTHORIZE);
    iSel++;

    szTemp.Format("CALL_LADDER_RELAY_BREAK");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_CALL_LADDER_RELAY_BREAK);
    iSel++;

    szTemp.Format("CALL_LADDER_RELAY_CLOSE");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_CALL_LADDER_RELAY_CLOSE);
    iSel++;

    szTemp.Format("AUTO_KEY_RELAY_BREAK");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_AUTO_KEY_RELAY_BREAK);
    iSel++;

    szTemp.Format("AUTO_KEY_RELAY_CLOSE");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_AUTO_KEY_RELAY_CLOSE);
    iSel++;

    szTemp.Format("KEY_CONTROL_RELAY_BREAK");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_KEY_CONTROL_RELAY_BREAK);
    iSel++;

    szTemp.Format("KEY_CONTROL_RELAY_CLOSE");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_KEY_CONTROL_RELAY_CLOSE);
    iSel++;

    szTemp.Format("REMOTE_VISITOR_CALL_LADDER");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_REMOTE_VISITOR_CALL_LADDER);
    iSel++;

    szTemp.Format("REMOTE_HOUSEHOLD_CALL_LADDER");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_REMOTE_HOUSEHOLD_CALL_LADDER);
    iSel++;

    szTemp.Format("LEGAL_MESSAGE");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_LEGAL_MESSAGE);
    iSel++;

    szTemp.Format("ILLEGAL_MESSAGE");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_ILLEGAL_MESSAGE);
    iSel++;

    return iSel;
}

int CDlgPlayEvent::AddMinorCardReaderString(int iStartSel)
{
    CString szTemp;
    int iSel = iStartSel;

    szTemp.Format("STRESS_ALARM");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_STRESS_ALARM);
    iSel++;

    szTemp.Format("CARD_READER_DESMANTLE_ALARM");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_CARD_READER_DESMANTLE_ALARM);
    iSel++;

    szTemp.Format("LEGAL_CARD_PASS");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_LEGAL_CARD_PASS);
    iSel++;

    szTemp.Format("CARD_AND_PSW_PASS");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_CARD_AND_PSW_PASS);
    iSel++;

    szTemp.Format("CARD_AND_PSW_FAIL");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_CARD_AND_PSW_FAIL);
    iSel++;

    szTemp.Format("CARD_AND_PSW_TIMEOUT");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_CARD_AND_PSW_TIMEOUT);
    iSel++;

    szTemp.Format("CARD_MAX_AUTHENTICATE_FAIL");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_CARD_MAX_AUTHENTICATE_FAIL);
    iSel++;

    szTemp.Format("CARD_NO_RIGHT");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_CARD_NO_RIGHT);
    iSel++;

    szTemp.Format("CARD_INVALID_PERIOD");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_CARD_INVALID_PERIOD);
    iSel++;

    szTemp.Format("CARD_OUT_OF_DATE");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_CARD_OUT_OF_DATE);
    iSel++;

    szTemp.Format("INVALID_CARD");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_INVALID_CARD);
    iSel++;

    szTemp.Format("ANTI_SNEAK_FAIL");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_ANTI_SNEAK_FAIL);
    iSel++;

    szTemp.Format("INTERLOCK_DOOR_NOT_CLOSE");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_INTERLOCK_DOOR_NOT_CLOSE);
    iSel++;

    szTemp.Format("FINGERPRINT_COMPARE_PASS");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FINGERPRINT_COMPARE_PASS);
    iSel++;

    szTemp.Format("FINGERPRINT_COMPARE_FAIL");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FINGERPRINT_COMPARE_FAIL);
    iSel++;

    szTemp.Format("CARD_FINGERPRINT_VERIFY_PASS");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_CARD_FINGERPRINT_VERIFY_PASS);
    iSel++;

    szTemp.Format("CARD_FINGERPRINT_VERIFY_FAIL");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_CARD_FINGERPRINT_VERIFY_FAIL);
    iSel++;

    szTemp.Format("CARD_FINGERPRINT_VERIFY_TIMEOUT");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_CARD_FINGERPRINT_VERIFY_TIMEOUT);
    iSel++;

    szTemp.Format("CARD_FINGERPRINT_PASSWD_VERIFY_PASS");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_CARD_FINGERPRINT_PASSWD_VERIFY_PASS);
    iSel++;

    szTemp.Format("CARD_FINGERPRINT_PASSWD_VERIFY_FAIL");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_CARD_FINGERPRINT_PASSWD_VERIFY_FAIL);
    iSel++;

    szTemp.Format("CARD_FINGERPRINT_PASSWD_VERIFY_TIMEOUT");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_CARD_FINGERPRINT_PASSWD_VERIFY_TIMEOUT);
    iSel++;

    szTemp.Format("FINGERPRINT_PASSWD_VERIFY_PASS");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FINGERPRINT_PASSWD_VERIFY_PASS);
    iSel++;

    szTemp.Format("FINGERPRINT_PASSWD_VERIFY_FAIL");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FINGERPRINT_PASSWD_VERIFY_FAIL);
    iSel++;

    szTemp.Format("FINGERPRINT_PASSWD_VERIFY_TIMEOUT");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FINGERPRINT_PASSWD_VERIFY_TIMEOUT);
    iSel++;

    szTemp.Format("FINGERPRINT_INEXISTENCE");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FINGERPRINT_INEXISTENCE);
    iSel++;

    szTemp.Format("FACE_VERIFY_PASS");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FACE_VERIFY_PASS);
    iSel++;

    szTemp.Format("FACE_VERIFY_FAIL");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FACE_VERIFY_FAIL);
    iSel++;

    szTemp.Format("FACE_AND_FP_VERIFY_PASS");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FACE_AND_FP_VERIFY_PASS);
    iSel++;

    szTemp.Format("FACE_AND_FP_VERIFY_FAIL");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FACE_AND_FP_VERIFY_FAIL);
    iSel++;

    szTemp.Format("FACE_AND_FP_VERIFY_TIMEOUT");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FACE_AND_FP_VERIFY_TIMEOUT);
    iSel++;

    szTemp.Format("FACE_AND_PW_VERIFY_PASS");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FACE_AND_PW_VERIFY_PASS);
    iSel++;

    szTemp.Format("FACE_AND_PW_VERIFY_FAIL");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FACE_AND_PW_VERIFY_FAIL);
    iSel++;

    szTemp.Format("FACE_AND_PW_VERIFY_TIMEOUT");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FACE_AND_PW_VERIFY_TIMEOUT);
    iSel++;

    szTemp.Format("FACE_AND_CARD_VERIFY_PASS");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FACE_AND_CARD_VERIFY_PASS);
    iSel++;

    szTemp.Format("FACE_AND_CARD_VERIFY_FAIL");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FACE_AND_CARD_VERIFY_FAIL);
    iSel++;

    szTemp.Format("FACE_AND_CARD_VERIFY_TIMEOUT");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FACE_AND_CARD_VERIFY_TIMEOUT);
    iSel++;

    szTemp.Format("FACE_AND_PW_AND_FP_VERIFY_PASS");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FACE_AND_PW_AND_FP_VERIFY_PASS);
    iSel++;

    szTemp.Format("FACE_AND_PW_AND_FP_VERIFY_FAIL");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FACE_AND_PW_AND_FP_VERIFY_FAIL);
    iSel++;

    szTemp.Format("FACE_AND_PW_AND_FP_VERIFY_TIMEOUT");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FACE_AND_PW_AND_FP_VERIFY_TIMEOUT);
    iSel++;

    szTemp.Format("FACE_AND_CARD_AND_FP_VERIFY_PASS");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FACE_AND_CARD_AND_FP_VERIFY_PASS);
    iSel++;

    szTemp.Format("FACE_AND_CARD_AND_FP_VERIFY_FAIL");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FACE_AND_CARD_AND_FP_VERIFY_FAIL);
    iSel++;

    szTemp.Format("FACE_AND_CARD_AND_FP_VERIFY_TIMEOUT");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FACE_AND_CARD_AND_FP_VERIFY_TIMEOUT);
    iSel++;

    szTemp.Format("EMPLOYEENO_AND_FP_VERIFY_PASS");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_EMPLOYEENO_AND_FP_VERIFY_PASS);
    iSel++;

    szTemp.Format("EMPLOYEENO_AND_FP_VERIFY_FAIL");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_EMPLOYEENO_AND_FP_VERIFY_FAIL);
    iSel++;

    szTemp.Format("EMPLOYEENO_AND_FP_VERIFY_TIMEOUT");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_EMPLOYEENO_AND_FP_VERIFY_TIMEOUT);
    iSel++;

    szTemp.Format("EMPLOYEENO_AND_FP_AND_PW_VERIFY_PASS");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_EMPLOYEENO_AND_FP_AND_PW_VERIFY_PASS);
    iSel++;

    szTemp.Format("EMPLOYEENO_AND_FP_AND_PW_VERIFY_FAIL");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_EMPLOYEENO_AND_FP_AND_PW_VERIFY_FAIL);
    iSel++;

    szTemp.Format("EMPLOYEENO_AND_FP_AND_PW_VERIFY_TIMEOUT");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_EMPLOYEENO_AND_FP_AND_PW_VERIFY_TIMEOUT);
    iSel++;

    szTemp.Format("EMPLOYEENO_AND_FACE_VERIFY_PASS");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_EMPLOYEENO_AND_FACE_VERIFY_PASS);
    iSel++;

    szTemp.Format("EMPLOYEENO_AND_FACE_VERIFY_FAIL");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_EMPLOYEENO_AND_FACE_VERIFY_FAIL);
    iSel++;

    szTemp.Format("EMPLOYEENO_AND_FACE_VERIFY_TIMEOUT");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_EMPLOYEENO_AND_FACE_VERIFY_TIMEOUT);
    iSel++;

    szTemp.Format("FACE_RECOGNIZE_FAIL");
    m_cmbMinorType.AddString(szTemp);
    m_cmbMinorType.SetItemData(iSel, EVENT_ACS_FACE_RECOGNIZE_FAIL);
    iSel++;

    return iSel;
}

UINT8 CDlgPlayEvent::charToData(const char ch)
{
    switch (ch)
    {
    case '0':
        return 0;
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9;
    case 'a':
    case 'A':
        return 10;
    case 'b':
    case 'B':
        return 11;
    case 'c':
    case 'C':
        return 12;
    case 'd':
    case 'D':
        return 13;
    case 'e':
    case 'E':
        return 14;
    case 'f':
    case 'F':
        return 15;
    }
    return 0;
}

bool CDlgPlayEvent::StrToMac(const char * szMac, UINT8 * pMac)
{
    const char * pTemp = szMac;
    for (int i = 0; i < 6; ++i)
    {
        pMac[i] = charToData(*pTemp++) * 16;
        pMac[i] += charToData(*pTemp++);
        pTemp++;
    }
    return TRUE;
}


void CDlgPlayEvent::OnCbnSelchangeComboDeviceType()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    int iIndex = 0;
    m_comboFindSubType.ResetContent();
    const char* szAcs[] = { "authenticated", "authenticationFailed", "openingDoor", "closingDoor", "doorException",
        "remoteOperation", "timeSynchronization", "deviceException", "deviceRecovered", "alarmTriggered",
        "alarmRecovered", "callCenter" };
    const char* szVideoIntercom[] = { "tampering", "duressAlarm", "unlockingByPasswordFailed", "unlockingDoorFailed", "lockingDoorFailed",
        "intercom", "unlockingByPassword", "unlockingByDuress", "unlockingByCard", "unlockingByResident",
        "unlockingByCenter", "cardSwipingFailed" };
    const char* szGJD[] = { "pirDetection", "tampering", "lowlightDetection", "timer", "temperature" };
    const char* szLuminite[] = { "pirDetection", "pirTamper", "cloak", "shock", "failure",
        "move", "batteryLow", "codeViolation", "jamming", "mastheadTamper" };
    const char* szOPTEX[] = { "pcFn", "pcFr", "pcNr", "pcCr", "tcTa", "tcAm", "tcAr", "tcDq", "tcSo", "tcTr",
        "tcFa", "offline", "connect", "pcA1", "pcA2", "pcB1", "pcB2", "pcA11", "pcA12", "pcA22", "pcA21", "pcB11",
        "pcB12", "pcB22", "pcB21" };
    const char* szcameraDetector[] = { "wirelessTemperature", "wirelessMagneticContact", "wirelessSmoke", "wirelessPIR", "wirelessSiren", "wirelessKeyfob" };

    switch (m_comboDeviceType.GetItemData(m_comboDeviceType.GetCurSel()))
    {
    case FILE_ACS:
        for (iIndex = 0; iIndex < sizeof(szAcs) / sizeof(char*); iIndex++)
        {
            m_comboFindSubType.InsertString(iIndex, szAcs[iIndex]);
            m_comboFindSubType.SetItemData(iIndex, iIndex + 1);
        }
        m_comboFindSubType.InsertString(iIndex, "all");
        m_comboFindSubType.SetItemData(iIndex, 0xffff);
        break;
    case FILE_VIDEO_INTERCOM:
        for (iIndex = 0; iIndex < sizeof(szVideoIntercom) / sizeof(char*); iIndex++)
        {
            m_comboFindSubType.InsertString(iIndex, szVideoIntercom[iIndex]);
            m_comboFindSubType.SetItemData(iIndex, iIndex + 1);
        }
        m_comboFindSubType.InsertString(iIndex, "all");
        m_comboFindSubType.SetItemData(iIndex, 0xffff);
        break;
    case FILE_GJD:
        for (iIndex = 0; iIndex < sizeof(szGJD) / sizeof(char*); iIndex++)
        {
            m_comboFindSubType.InsertString(iIndex, szGJD[iIndex]);
            m_comboFindSubType.SetItemData(iIndex, iIndex + 1);
        }
        m_comboFindSubType.InsertString(iIndex, "all");
        m_comboFindSubType.SetItemData(iIndex, 0xffff);
        break;
    case FILE_LUMINITE:
        for (iIndex = 0; iIndex < sizeof(szLuminite) / sizeof(char*); iIndex++)
        {
            m_comboFindSubType.InsertString(iIndex, szLuminite[iIndex]);
            m_comboFindSubType.SetItemData(iIndex, iIndex + 1);
        }
        m_comboFindSubType.InsertString(iIndex, "all");
        m_comboFindSubType.SetItemData(iIndex, 0xffff);
        break;
    case FILE_OPTEX:
        for (iIndex = 0; iIndex < sizeof(szOPTEX) / sizeof(char*); iIndex++)
        {
            m_comboFindSubType.InsertString(iIndex, szOPTEX[iIndex]);
            m_comboFindSubType.SetItemData(iIndex, iIndex + 1);
        }
        m_comboFindSubType.InsertString(iIndex, "all");
        m_comboFindSubType.SetItemData(iIndex, 0xffff);
        break;
    case FILE_CAMERA_DETECTOR:
        for (iIndex = 0; iIndex < sizeof(szcameraDetector) / sizeof(char*); iIndex++)
        {
            m_comboFindSubType.InsertString(iIndex, szcameraDetector[iIndex]);
            m_comboFindSubType.SetItemData(iIndex, iIndex + 1);
        }
        m_comboFindSubType.InsertString(iIndex, "all");
        m_comboFindSubType.SetItemData(iIndex, 0xffff);
        break;
    default:
        m_comboFindSubType.ResetContent();
        break;
    }
    UpdateData(FALSE);
}

