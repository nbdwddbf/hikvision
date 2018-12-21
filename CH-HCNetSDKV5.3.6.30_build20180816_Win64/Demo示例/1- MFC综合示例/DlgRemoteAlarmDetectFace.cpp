// DlgRemoteAlarmDetectFace.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRemoteAlarmDetectFace.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteAlarmDetectFace dialog


CDlgRemoteAlarmDetectFace::CDlgRemoteAlarmDetectFace(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteAlarmDetectFace::IDD, pParent)
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
{
	//{{AFX_DATA_INIT(CDlgRemoteAlarmDetectFace)
	m_bChkEmapAlarmOut = FALSE;
	m_bChkInvokeAlarmOut = FALSE;
	m_bChkMonitorAlarm = FALSE;
	m_bChkUploadCenter = FALSE;
	m_bChkVoiceAlarm = FALSE;
	m_bChkInvokeJpegCapture = FALSE;
	m_bChkPicToFtp = FALSE;
    m_bChkPicToCloud = FALSE;
	m_bChkFaceDetect = FALSE;
	m_bChkEnableDisPlay = FALSE;
	m_nDuration = 0;
	//}}AFX_DATA_INIT

	memset(&m_struDetectFaceCfg, 0, sizeof(m_struDetectFaceCfg));
	//memset(&m_struChannelGroup, 0, sizeof(m_struChannelGroup));

	memset(&m_bAlarmOut[0], 0, sizeof(BOOL)*MAX_CHANNUM_V30);
	memset(&m_bRecordChan[0], 0, sizeof(BOOL)*MAX_CHANNUM_V30);
	memset(&m_struHolidayTime[0], 0 ,MAX_TIMESEGMENT_V30 * sizeof(NET_DVR_SCHEDTIME));

	for (int i = 0; i < MAX_CHANNUM_V30; i++)
	{
		m_struDetectFaceCfg.struAlarmHandleType.dwRelAlarmOut[i] = 0xffffffff;
		m_struDetectFaceCfg.dwRelRecordChan[i] = 0xffffffff;
	}
	
	m_dwMaxRelAlarmOutNum = 0;
	m_dwMaxRelRecordChanNum = 0;
}


void CDlgRemoteAlarmDetectFace::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteAlarmDetectFace)
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_comboChannel);
	DDX_Control(pDX, IDC_COM_DETECT_SENSITIVE, m_comDetectSensitive);
	DDX_Control(pDX, IDC_TREE_ALARM_OUT, m_treeAlarmOut);
	DDX_Control(pDX, IDC_TREE_CHAN, m_treeChan);
	DDX_Check(pDX, IDC_CHK_ALARM_EMAP, m_bChkEmapAlarmOut);
	DDX_Check(pDX, IDC_CHK_ALARMIN_INVOKE_ALARMOUT, m_bChkInvokeAlarmOut);
	DDX_Check(pDX, IDC_CHK_ALARMIN_MONITOR, m_bChkMonitorAlarm);
	DDX_Check(pDX, IDC_CHK_ALARMIN_UPLOAD_CENTER, m_bChkUploadCenter);
	DDX_Check(pDX, IDC_CHK_ALARMIN_VOICE, m_bChkVoiceAlarm);
	DDX_Check(pDX, IDC_CHK_INVOKE_JPEG_CAPTURE, m_bChkInvokeJpegCapture);
	DDX_Check(pDX, IDC_CHK_PIC_FTP, m_bChkPicToFtp);
    DDX_Check(pDX, IDC_CHK_PIC_CLOUD, m_bChkPicToCloud);
	DDX_Check(pDX, IDC_CHK_ENABLE_FACE_DETECT, m_bChkFaceDetect);
	DDX_Check(pDX, IDC_CHK_ENABLE_DISPLAY, m_bChkEnableDisPlay);
	DDX_Control(pDX, IDC_COMBO_ALARMIN_WEEKDAY, m_comboWeekday);
	DDX_Control(pDX, IDC_COMBO_ALARMIN_COPY_TIME, m_comboCopyTime);
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
	DDX_Text(pDX, IDC_DURATION, m_nDuration);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRemoteAlarmDetectFace, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteAlarmDetectFace)
	ON_BN_CLICKED(IDC_BTN_ALARM_IN_TIME_OK, OnBtnAlarmInTimeOk)
	ON_NOTIFY(NM_CLICK, IDC_TREE_ALARM_OUT, OnClickTreeAlarmOut)
	ON_BN_CLICKED(IDC_BTN_ALARMIN_OK, OnBtnAlarminOk)
	ON_WM_CANCELMODE()
	ON_NOTIFY(NM_CLICK, IDC_TREE_CHAN, OnClickTreeChan)
	ON_BN_CLICKED(IDC_BTN_ALARMIN_TIME_COPY, OnBtnAlarminTimeCopy)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARMIN_WEEKDAY, OnSelchangeComboAlarminWeekday)
	ON_BN_CLICKED(IDC_CHK_ALARMIN_INVOKE_ALARMOUT, OnChkAlarminInvokeAlarmout)
	ON_BN_CLICKED(IDC_BTN_ALARMIN_UPLOAD, OnBtnAlarminUpload)
	ON_BN_CLICKED(IDC_BTN_ALARMIN_EXIT, OnBtnAlarminExit)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL, OnSelchangeComboChannel)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteAlarmDetectFace message handlers

void CDlgRemoteAlarmDetectFace::OnBtnAlarmInTimeOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    if (!TimeTest())
    {
        return;
    }
    int	i = m_comboWeekday.GetCurSel();	
	if (i == 8)
	{
		m_struHolidayTime[0].byStartHour = (BYTE)m_iHour11;
		m_struHolidayTime[0].byStartMin = (BYTE)m_iMin11;
		m_struHolidayTime[0].byStopHour = (BYTE)m_iHour12;
		m_struHolidayTime[0].byStopMin = (BYTE)m_iMin12;
		m_struHolidayTime[1].byStartHour = (BYTE)m_iHour21;
		m_struHolidayTime[1].byStartMin = (BYTE)m_iMin21;
		m_struHolidayTime[1].byStopHour = (BYTE)m_iHour22;
		m_struHolidayTime[1].byStopMin = (BYTE)m_iMin22;
		m_struHolidayTime[2].byStartHour = (BYTE)m_iHour31;
		m_struHolidayTime[2].byStartMin = (BYTE)m_iMin31;
		m_struHolidayTime[2].byStopHour = (BYTE)m_iHour32;
		m_struHolidayTime[2].byStopMin = (BYTE)m_iMin32;
		m_struHolidayTime[3].byStartHour = (BYTE)m_iHour41;
		m_struHolidayTime[3].byStartMin = (BYTE)m_iMin41;
		m_struHolidayTime[3].byStopHour = (BYTE)m_iHour42;
		m_struHolidayTime[3].byStopMin = (BYTE)m_iMin42;
		m_struHolidayTime[4].byStartHour = (BYTE)m_iHour51;
		m_struHolidayTime[4].byStartMin = (BYTE)m_iMin51;
		m_struHolidayTime[4].byStopHour = (BYTE)m_iHour52;
		m_struHolidayTime[4].byStopMin = (BYTE)m_iMin52;
		m_struHolidayTime[5].byStartHour = (BYTE)m_iHour61;
		m_struHolidayTime[5].byStartMin = (BYTE)m_iMin61;
		m_struHolidayTime[5].byStopHour = (BYTE)m_iHour62;
		m_struHolidayTime[5].byStopMin = (BYTE)m_iMin62;
		m_struHolidayTime[6].byStartHour = (BYTE)m_iHour71;
		m_struHolidayTime[6].byStartMin = (BYTE)m_iMin71;
		m_struHolidayTime[6].byStopHour = (BYTE)m_iHour72;
		m_struHolidayTime[6].byStopMin = (BYTE)m_iMin72;
		m_struHolidayTime[7].byStartHour = (BYTE)m_iHour81;
		m_struHolidayTime[7].byStartMin = (BYTE)m_iMin81;
		m_struHolidayTime[7].byStopHour = (BYTE)m_iHour82;
		m_struHolidayTime[7].byStopMin = (BYTE)m_iMin82;
	}
	else
	{
		m_struAlarmTime[i][0].byStartHour = (BYTE)m_iHour11;
		m_struAlarmTime[i][0].byStartMin = (BYTE)m_iMin11;
		m_struAlarmTime[i][0].byStopHour = (BYTE)m_iHour12;
		m_struAlarmTime[i][0].byStopMin = (BYTE)m_iMin12;
		m_struAlarmTime[i][1].byStartHour = (BYTE)m_iHour21;
		m_struAlarmTime[i][1].byStartMin = (BYTE)m_iMin21;
		m_struAlarmTime[i][1].byStopHour = (BYTE)m_iHour22;
		m_struAlarmTime[i][1].byStopMin = (BYTE)m_iMin22;
		m_struAlarmTime[i][2].byStartHour = (BYTE)m_iHour31;
		m_struAlarmTime[i][2].byStartMin = (BYTE)m_iMin31;
		m_struAlarmTime[i][2].byStopHour = (BYTE)m_iHour32;
		m_struAlarmTime[i][2].byStopMin = (BYTE)m_iMin32;
		m_struAlarmTime[i][3].byStartHour = (BYTE)m_iHour41;
		m_struAlarmTime[i][3].byStartMin = (BYTE)m_iMin41;
		m_struAlarmTime[i][3].byStopHour = (BYTE)m_iHour42;
		m_struAlarmTime[i][3].byStopMin = (BYTE)m_iMin42;
		m_struAlarmTime[i][4].byStartHour = (BYTE)m_iHour51;
		m_struAlarmTime[i][4].byStartMin = (BYTE)m_iMin51;
		m_struAlarmTime[i][4].byStopHour = (BYTE)m_iHour52;
		m_struAlarmTime[i][4].byStopMin = (BYTE)m_iMin52;
		m_struAlarmTime[i][5].byStartHour = (BYTE)m_iHour61;
		m_struAlarmTime[i][5].byStartMin = (BYTE)m_iMin61;
		m_struAlarmTime[i][5].byStopHour = (BYTE)m_iHour62;
		m_struAlarmTime[i][5].byStopMin = (BYTE)m_iMin62;
		m_struAlarmTime[i][6].byStartHour = (BYTE)m_iHour71;
		m_struAlarmTime[i][6].byStartMin = (BYTE)m_iMin71;
		m_struAlarmTime[i][6].byStopHour = (BYTE)m_iHour72;
		m_struAlarmTime[i][6].byStopMin = (BYTE)m_iMin72;
		m_struAlarmTime[i][7].byStartHour = (BYTE)m_iHour81;
		m_struAlarmTime[i][7].byStartMin = (BYTE)m_iMin81;
		m_struAlarmTime[i][7].byStopHour = (BYTE)m_iHour82;
		m_struAlarmTime[i][7].byStopMin = (BYTE)m_iMin82;
	}	
	GetDlgItem(IDC_BTN_ALARMIN_TIME_COPY)->EnableWindow(TRUE);	
}

/*********************************************************
  Function:	CreateTree
  Desc:		establish alarm out - video connection
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteAlarmDetectFace::CreateTree(void)
{
	g_CreateChannelTree(m_treeChan, m_dwDevIndex, m_bRecordChan);
	g_CreateAlarmOutTree(m_treeAlarmOut, m_dwDevIndex, m_bAlarmOut);
	
}


void CDlgRemoteAlarmDetectFace::OnClickTreeChan(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	CPoint pt(0,0);
	CRect rc(0,0,0,0);
	GetCursorPos(&pt);
	GetDlgItem(IDC_TREE_CHAN)->GetWindowRect(&rc);
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
	m_bRecordChan[dwIndex] = !bCheck;

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

void CDlgRemoteAlarmDetectFace::OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	CPoint pt(0,0);
	CRect rc(0,0,0,0);
	GetCursorPos(&pt);
	GetDlgItem(IDC_TREE_ALARM_OUT)->GetWindowRect(&rc);
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
	m_bAlarmOut[dwIndex] = !bCheck;;
	
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




void CDlgRemoteAlarmDetectFace::OnBtnAlarminOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int i = 0;
	char szLan[128] = {0};
	m_struDetectFaceCfg.dwSize = sizeof(m_struDetectFaceCfg);
	m_struDetectFaceCfg.dwRelRecordChanNum = 0;
	memset(&m_struDetectFaceCfg.dwRelRecordChan[0],0xffffffff,sizeof(DWORD)*MAX_CHANNUM_V30);
	int j = 0;
	for (i = 0; i < MAX_CHANNUM_V30; i++)
	{
		if (m_bRecordChan[i])
		{
			m_struDetectFaceCfg.dwRelRecordChan[j] = i+1;
			m_struDetectFaceCfg.dwRelRecordChanNum++;
			j++;
		}
	}

	m_struDetectFaceCfg.struAlarmHandleType.dwRelAlarmOutChanNum = 0;
	memset(&m_struDetectFaceCfg.struAlarmHandleType.dwRelAlarmOut[0],0xffffffff,sizeof(DWORD)*MAX_CHANNUM_V30);
	j = 0;
	for (i=0; i < MAX_CHANNUM_V30; i++)
	{
		if (m_bAlarmOut[i])
		{
			m_struDetectFaceCfg.struAlarmHandleType.dwRelAlarmOut[j] = i+1;
			m_struDetectFaceCfg.struAlarmHandleType.dwRelAlarmOutChanNum++;
			j++;
		}	
	}
	
	memcpy(m_struDetectFaceCfg.struAlarmTime, m_struAlarmTime, sizeof(NET_DVR_SCHEDTIME) * MAX_DAYS * MAX_TIMESEGMENT_V30);
	m_struDetectFaceCfg.struAlarmHandleType.dwHandleType = 0;
	m_struDetectFaceCfg.struAlarmHandleType.dwHandleType |= (m_bChkMonitorAlarm << 0);
	m_struDetectFaceCfg.struAlarmHandleType.dwHandleType |= (m_bChkVoiceAlarm << 1);
	m_struDetectFaceCfg.struAlarmHandleType.dwHandleType |= (m_bChkUploadCenter << 2);
	m_struDetectFaceCfg.struAlarmHandleType.dwHandleType |= (m_bChkInvokeAlarmOut << 3);
	m_struDetectFaceCfg.struAlarmHandleType.dwHandleType |= (m_bChkInvokeJpegCapture << 4);
	m_struDetectFaceCfg.struAlarmHandleType.dwHandleType |= (m_bChkEmapAlarmOut<<6);
	m_struDetectFaceCfg.struAlarmHandleType.dwHandleType |= (m_bChkPicToFtp << 9);	
    m_struDetectFaceCfg.struAlarmHandleType.dwHandleType |= (m_bChkPicToCloud << 12);
	
	m_struDetectFaceCfg.byEnableDetectFace = m_bChkFaceDetect;
	m_struDetectFaceCfg.byEnableDisplay = m_bChkEnableDisPlay;
	m_struDetectFaceCfg.byDetectSensitive = m_comDetectSensitive.GetCurSel() + 1;
	m_struDetectFaceCfg.wDuration = m_nDuration;
	m_struChannelGroup.dwSize = sizeof(m_struChannelGroup);
	int iCurChanIndex = m_comboChannel.GetCurSel();
	int iChannel = m_comboChannel.GetItemData(iCurChanIndex);
	
	m_struChannelGroup.dwSize = sizeof(m_struChannelGroup);
    if (iChannel > 63 + g_struDeviceInfo[m_dwDevIndex].iAnalogChanNum + 1)
	{
		m_struChannelGroup.dwGroup = 1;
		m_struChannelGroup.dwChannel = iChannel - 63;
	}
	else
	{
		m_struChannelGroup.dwGroup = 0;
		m_struChannelGroup.dwChannel = iChannel;
	}
	memcpy(m_struDetectFaceCfg.struHolidayTime, m_struHolidayTime, sizeof(NET_DVR_SCHEDTIME) * MAX_TIMESEGMENT_V30);
	int iItemCount = 1;
	DWORD *pStatus = new DWORD[iItemCount];
	memset(pStatus, 0, sizeof(DWORD)*iItemCount);

	BOOL bRet = NET_DVR_SetDeviceConfig(m_lServerID,NET_DVR_SET_FACE_DETECT, iItemCount,&m_struChannelGroup, sizeof(m_struChannelGroup), pStatus, \
		&m_struDetectFaceCfg, sizeof(m_struDetectFaceCfg));
	if (!bRet)
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_FAIL_T, "NET_DVR_SET_FACE_DETECT");
		if (pStatus != NULL)
		{
			delete [] pStatus;
			pStatus = NULL;
		}
		return;
	}
	else
	{
		if (*pStatus != NET_DVR_NOERROR)
		{
			g_pMainDlg->AddLog(m_lServerID, OPERATION_FAIL_T, "NET_DVR_SET_FACE_DETECT");
			sprintf(szLan,"NET_DVR_SET_FACE_DETECT  Error[%d], chanNum[%d]", *pStatus, m_struChannelGroup.dwChannel);
			AfxMessageBox(szLan);
			if (pStatus != NULL)
			{
				delete [] pStatus;
				pStatus = NULL;
			}
			return;
		}
		else
		{
			g_pMainDlg->AddLog(m_lServerID, OPERATION_SUCC_T, "NET_DVR_SET_FACE_DETECT");
		}
	}

	if (pStatus != NULL)
	{
		delete [] pStatus;
		pStatus = NULL;
	}
}

BOOL CDlgRemoteAlarmDetectFace::OnInitDialog() 
{
	CDialog::OnInitDialog();
	char sTemp[32] = {0};
	// TODO: Add extra initialization here
	int i = 0;
	int index = 0;
	for (i = 0; i < g_struDeviceInfo[m_dwDevIndex].iAnalogChanNum; i++)
	{
		sprintf(sTemp,"camera%d",g_struDeviceInfo[m_dwDevIndex].iStartChan + i);
		m_comboChannel.AddString(sTemp);
		m_comboChannel.SetItemData(index,g_struDeviceInfo[m_dwDevIndex].iStartChan + i);
		index++;
	}
	for (i = 0; i < g_struDeviceInfo[m_dwDevIndex].iIPChanNum; i++)
	{
		sprintf(sTemp,"Ipcamera%d",g_struDeviceInfo[m_dwDevIndex].pStruIPParaCfgV40->dwStartDChan + i);
		m_comboChannel.AddString(sTemp);
		m_comboChannel.SetItemData(index,g_struDeviceInfo[m_dwDevIndex].pStruIPParaCfgV40->dwStartDChan + i);
		index++;
	}
 	m_comboWeekday.SetCurSel(0);
	m_comboChannel.SetCurSel(0);
	ShowData();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRemoteAlarmDetectFace::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CDlgRemoteAlarmDetectFace::OnBtnAlarminUpload() 
{
	// TODO: Add your control notification handler code here
	ShowData();
}

void CDlgRemoteAlarmDetectFace::OnBtnAlarminExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CDlgRemoteAlarmDetectFace::OnBtnAlarminTimeCopy() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int j,k;
	int i = m_comboWeekday.GetCurSel();
	int m_nCopyTime = m_comboCopyTime.GetCurSel() - 1;
	
	if (m_nCopyTime == -1)
	{
		for (j=0; j<MAX_DAYS; j++)
		{
			if (j == i)
			{
				continue;
			}
			for (k=0; k<MAX_TIMESEGMENT_V30; k++)
			{
				memcpy(&(m_struAlarmTime[j][k]), &(m_struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
			}
		}
	}
	else
	{
		for (k=0; k<MAX_TIMESEGMENT_V30; k++)
		{
			memcpy(&(m_struAlarmTime[m_nCopyTime][k]), &(m_struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
		}
	}
}

BOOL CDlgRemoteAlarmDetectFace::TimeTest()
{
	int i = 0;
	int j = 0;
	WORD wStartTime[MAX_TIMESEGMENT_V30], wStopTime[MAX_TIMESEGMENT_V30];
	char szLan[1024] = {0};
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

void CDlgRemoteAlarmDetectFace::OnSelchangeComboAlarminWeekday() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int	i = m_comboWeekday.GetCurSel();	
/*    {*/
	if (i == 7)
	{
		m_iHour11 = m_struHolidayTime[0].byStartHour;
        m_iMin11 = m_struHolidayTime[0].byStartMin;
        m_iHour12 =m_struHolidayTime[0].byStopHour;
        m_iMin12 = m_struHolidayTime[0].byStopMin;
        m_iHour21 = m_struHolidayTime[1].byStartHour;
        m_iMin21 = m_struHolidayTime[1].byStartMin;
        m_iHour22 = m_struHolidayTime[1].byStopHour;
        m_iMin22 = m_struHolidayTime[1].byStopMin;
        m_iHour31 = m_struHolidayTime[2].byStartHour;
        m_iMin31 = m_struHolidayTime[2].byStartMin;
        m_iHour32 = m_struHolidayTime[2].byStopHour;
        m_iMin32 = m_struHolidayTime[2].byStopMin;
        m_iHour41 = m_struHolidayTime[3].byStartHour;
        m_iMin41 = m_struHolidayTime[3].byStartMin;
        m_iHour42 = m_struHolidayTime[3].byStopHour;
        m_iMin42 = m_struHolidayTime[3].byStopMin;
        m_iHour51 = m_struHolidayTime[4].byStartHour;
        m_iMin51 = m_struHolidayTime[4].byStartMin;
        m_iHour52 = m_struHolidayTime[4].byStopHour;
        m_iMin52 = m_struHolidayTime[4].byStopMin;
        m_iHour61 = m_struHolidayTime[5].byStartHour;
        m_iMin61 = m_struHolidayTime[5].byStartMin;
        m_iHour62 = m_struHolidayTime[5].byStopHour;
        m_iMin62 = m_struHolidayTime[5].byStopMin;
        m_iHour71 = m_struHolidayTime[6].byStartHour;
        m_iMin71 = m_struHolidayTime[6].byStartMin;
        m_iHour72 = m_struHolidayTime[6].byStopHour;
        m_iMin72 = m_struHolidayTime[6].byStopMin;
        m_iHour81 = m_struHolidayTime[7].byStartHour;
        m_iMin81 = m_struHolidayTime[7].byStartMin;
        m_iHour82 = m_struHolidayTime[7].byStopHour;
		m_iMin82 = m_struHolidayTime[7].byStopMin;
	}
	else
	{
        m_iHour11 = m_struAlarmTime[i][0].byStartHour;
        m_iMin11 = m_struAlarmTime[i][0].byStartMin;
        m_iHour12 =m_struAlarmTime[i][0].byStopHour;
        m_iMin12 = m_struAlarmTime[i][0].byStopMin;
        m_iHour21 = m_struAlarmTime[i][1].byStartHour;
        m_iMin21 = m_struAlarmTime[i][1].byStartMin;
        m_iHour22 = m_struAlarmTime[i][1].byStopHour;
        m_iMin22 = m_struAlarmTime[i][1].byStopMin;
        m_iHour31 = m_struAlarmTime[i][2].byStartHour;
        m_iMin31 = m_struAlarmTime[i][2].byStartMin;
        m_iHour32 = m_struAlarmTime[i][2].byStopHour;
        m_iMin32 = m_struAlarmTime[i][2].byStopMin;
        m_iHour41 = m_struAlarmTime[i][3].byStartHour;
        m_iMin41 = m_struAlarmTime[i][3].byStartMin;
        m_iHour42 = m_struAlarmTime[i][3].byStopHour;
        m_iMin42 = m_struAlarmTime[i][3].byStopMin;
        m_iHour51 = m_struAlarmTime[i][4].byStartHour;
        m_iMin51 = m_struAlarmTime[i][4].byStartMin;
        m_iHour52 = m_struAlarmTime[i][4].byStopHour;
        m_iMin52 = m_struAlarmTime[i][4].byStopMin;
        m_iHour61 = m_struAlarmTime[i][5].byStartHour;
        m_iMin61 = m_struAlarmTime[i][5].byStartMin;
        m_iHour62 = m_struAlarmTime[i][5].byStopHour;
        m_iMin62 = m_struAlarmTime[i][5].byStopMin;
        m_iHour71 = m_struAlarmTime[i][6].byStartHour;
        m_iMin71 = m_struAlarmTime[i][6].byStartMin;
        m_iHour72 = m_struAlarmTime[i][6].byStopHour;
        m_iMin72 = m_struAlarmTime[i][6].byStopMin;
        m_iHour81 = m_struAlarmTime[i][7].byStartHour;
        m_iMin81 = m_struAlarmTime[i][7].byStartMin;
        m_iHour82 = m_struAlarmTime[i][7].byStopHour;
		m_iMin82 = m_struAlarmTime[i][7].byStopMin;
	}
/*    }*/
	
	UpdateData(FALSE);	
}

void CDlgRemoteAlarmDetectFace::OnChkAlarminInvokeAlarmout() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_treeAlarmOut.EnableWindow(m_bChkInvokeAlarmOut);
}

void CDlgRemoteAlarmDetectFace::ShowData()
{
	UpdateData(TRUE);
	int iCurChanIndex = m_comboChannel.GetCurSel();
	int iChannel = m_comboChannel.GetItemData(iCurChanIndex);
	m_struChannelGroup.dwSize = sizeof(m_struChannelGroup);
    if (iChannel > 63 + g_struDeviceInfo[m_dwDevIndex].iAnalogChanNum + 1)
    {
        m_struChannelGroup.dwGroup = 1;
        m_struChannelGroup.dwChannel = iChannel - 63;
    }
    else
    {
        m_struChannelGroup.dwGroup = 0;
        m_struChannelGroup.dwChannel = iChannel;
    }
	
    int i = 0;
	int iItemCount = 1;
	char szLan[128] = {0};

	DWORD *pStatus = new DWORD[iItemCount];
	memset(pStatus, 0, sizeof(DWORD)*iItemCount);
 
// 	NET_DVR_DETECT_FACE  struDetectFaceCfg[2];
// 	NET_DVR_CHANNEL_GROUP struChannelGroup[2];
// 
// 	memset(&struDetectFaceCfg, 0 ,sizeof(struDetectFaceCfg));
// 	memset(&struChannelGroup, 0, sizeof(struChannelGroup));
// 
// 	for (i = 0; i < 2; i++)
// 	{
// 		struChannelGroup[i].dwSize = sizeof(NET_DVR_CHANNEL_GROUP);
// 		struChannelGroup[i].dwGroup = i;
// 		struChannelGroup[i].dwChannel = i + 1;
// 	}
// 
// 	if (NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_FACE_DETECT, iItemCount, &struChannelGroup, \
// 		iItemCount*sizeof(NET_DVR_CHANNEL_GROUP), pStatus, &struDetectFaceCfg, iItemCount*sizeof(NET_DVR_DETECT_FACE)))
// 	{
// 		g_pMainDlg->AddLog(m_lServerID, OPERATION_SUCC_T, "NET_DVR_GET_FACE_DETECT");
// 	}
// 	else
// 	{
// 		g_pMainDlg->AddLog(m_lServerID, OPERATION_FAIL_T, "NET_DVR_GET_FACE_DETECT");
// 		return;
// 	}
// 
// 	for (i=0; i<iItemCount; i++)
// 	{
// 		if (*pStatus != 0)
// 		{
// 			sprintf(szLan,"错误状态返回值:%d",*pStatus);
// 			AfxMessageBox(szLan);
// 		}
// 		sprintf(szLan,"正确状态返回值:%d",*pStatus);
// 		AfxMessageBox(szLan);
// 		pStatus++;
// 	}
	
	memset(&m_struDetectFaceCfg,0,sizeof(m_struDetectFaceCfg));
	m_struDetectFaceCfg.dwSize = sizeof(m_struDetectFaceCfg);
	if (NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_FACE_DETECT, iItemCount, &m_struChannelGroup, \
		iItemCount*sizeof(m_struChannelGroup), pStatus, &m_struDetectFaceCfg, iItemCount*sizeof(m_struDetectFaceCfg)))
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_SUCC_T, "NET_DVR_GET_FACE_DETECT");
	}
	else
	{
		g_pMainDlg->AddLog(m_lServerID, OPERATION_FAIL_T, "NET_DVR_GET_FACE_DETECT");
		return;
	}

	for (i=0; i<iItemCount; i++)
	{
		if (*pStatus != 0)
		{
			sprintf(szLan,"错误状态返回值:%d",*pStatus);
		//	AfxMessageBox(szLan);
		}
		sprintf(szLan,"正确状态返回值:%d",*pStatus);
	//	AfxMessageBox(szLan);
		pStatus++;
	}

	memcpy(m_struAlarmTime, m_struDetectFaceCfg.struAlarmTime, sizeof(NET_DVR_SCHEDTIME) * MAX_DAYS * MAX_TIMESEGMENT_V30);

	m_bChkMonitorAlarm = m_struDetectFaceCfg.struAlarmHandleType.dwHandleType &0x01;
	m_bChkVoiceAlarm = (m_struDetectFaceCfg.struAlarmHandleType.dwHandleType>>1)&0x01;
	m_bChkUploadCenter = (m_struDetectFaceCfg.struAlarmHandleType.dwHandleType>>2)&0x01;
	m_bChkInvokeAlarmOut = (m_struDetectFaceCfg.struAlarmHandleType.dwHandleType>>3)&0x01;
	m_bChkInvokeJpegCapture = (m_struDetectFaceCfg.struAlarmHandleType.dwHandleType>>4)&0x01;
	m_bChkEmapAlarmOut = (m_struDetectFaceCfg.struAlarmHandleType.dwHandleType>>6)&0x01;
	m_bChkPicToFtp = (m_struDetectFaceCfg.struAlarmHandleType.dwHandleType>>9)&0x01;
    m_bChkPicToCloud = (m_struDetectFaceCfg.struAlarmHandleType.dwHandleType >> 12) & 0x01;

	m_treeAlarmOut.EnableWindow(m_bChkInvokeAlarmOut);
	memset(&m_bAlarmOut[0],0,sizeof(BOOL)*MAX_CHANNUM_V30);
	memset(&m_bRecordChan[0],0,sizeof(BOOL)*MAX_CHANNUM_V30);
	for (i=0;i<MAX_CHANNUM_V30;i++)
	{
		if (m_struDetectFaceCfg.struAlarmHandleType.dwRelAlarmOut[i] != 0xffffffff )
		{
			if ( m_struDetectFaceCfg.struAlarmHandleType.dwRelAlarmOut[i]> 0 && m_struDetectFaceCfg.struAlarmHandleType.dwRelAlarmOut[i] <= MAX_CHANNUM_V30)
			{
				m_bAlarmOut[m_struDetectFaceCfg.struAlarmHandleType.dwRelAlarmOut[i] -1] = TRUE;
			}
		}
		else
		{
			break;
		}
	}
	for (i=0; i< MAX_CHANNUM_V30; i++)
	{
		if (m_struDetectFaceCfg.dwRelRecordChan[i] != 0xffffffff)
		{
			if (m_struDetectFaceCfg.dwRelRecordChan[i] >0 && m_struDetectFaceCfg.dwRelRecordChan[i] <= MAX_CHANNUM_V30)
			{
			}
			m_bRecordChan[m_struDetectFaceCfg.dwRelRecordChan[i] - 1] = TRUE;
		}
		else
		{
			break;
		}
	}

	m_bChkFaceDetect = m_struDetectFaceCfg.byEnableDetectFace;
	m_bChkEnableDisPlay = m_struDetectFaceCfg.byEnableDisplay;
	m_comDetectSensitive.SetCurSel(m_struDetectFaceCfg.byDetectSensitive - 1);

	m_dwMaxRelAlarmOutNum = m_struDetectFaceCfg.struAlarmHandleType.dwMaxRelAlarmOutChanNum;
	m_dwMaxRelRecordChanNum = m_struDetectFaceCfg.dwMaxRelRecordChanNum;
	m_nDuration = m_struDetectFaceCfg.wDuration;
	memcpy(m_struHolidayTime, m_struDetectFaceCfg.struHolidayTime, sizeof(NET_DVR_SCHEDTIME) * MAX_TIMESEGMENT_V30);
	UpdateData(FALSE);
	CreateTree();

	OnSelchangeComboAlarminWeekday();
	UpdateData(FALSE);
}

void CDlgRemoteAlarmDetectFace::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CreateTree();
	// Do not call CDialog::OnPaint() for painting messages
}

void CDlgRemoteAlarmDetectFace::OnSelchangeComboChannel() 
{
	// TODO: Add your control notification handler code here
	ShowData();
}
