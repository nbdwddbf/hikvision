// DlgInChanVideoLostCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInChanVideoLostCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInChanVideoLostCfg dialog


CDlgInChanVideoLostCfg::CDlgInChanVideoLostCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInChanVideoLostCfg::IDD, pParent)
    , m_bChkMonitorAlarm(FALSE)
    , m_bChkAudioAlarm(FALSE)
    , m_bChkReportCenter(FALSE)
    , m_bChkInvokeAlarmOut(FALSE)
    , m_bChkPicToFtp(FALSE)
    , m_bChkInvokeJpegCapture(FALSE)
    , m_bChkEmapAlarmOut(FALSE)
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
    , m_lLoginID(-1)
    , m_dwAlarmOutNum(0)
	, m_iDevIndex(-1)
{
	//{{AFX_DATA_INIT(CDlgInChanVideoLostCfg)
	m_bEnable = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgInChanVideoLostCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInChanVideoLostCfg)
    DDX_Control(pDX, IDC_TREE_ALARM_OUT, m_treeAlarmOut);
    DDX_Check(pDX, IDC_CHK_VILOST_MONITOR_ALARM, m_bChkMonitorAlarm);
    DDX_Check(pDX, IDC_CHK_VILOST_AUDIO_ALARM, m_bChkAudioAlarm);
    DDX_Check(pDX, IDC_CHK_VILOST_REPORT_CENTER, m_bChkReportCenter);
    DDX_Check(pDX, IDC_CHK_VILOST_INVOKE_ALARM_OUT, m_bChkInvokeAlarmOut);
    DDX_Check(pDX, IDC_CHK_ALARMOUT_EMAP, m_bChkEmapAlarmOut);
    DDX_Control(pDX, IDC_COMBO_VILOST_WEEKDAY, m_comboWeekday);
    DDX_Control(pDX, IDC_COMBO_VILOST_COPY_DAY, m_comboCopyDay);
    DDX_Check(pDX, IDC_CHK_INVOKE_JPEG_CAPTURE, m_bChkInvokeJpegCapture);
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
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cmbChannel);
    DDX_Check(pDX, IDC_CHK_PIC_FTP, m_bChkPicToFtp);
	DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInChanVideoLostCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgInChanVideoLostCfg)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
    ON_BN_CLICKED(IDC_CHK_VILOST_INVOKE_ALARM_OUT, OnBnClickedChkVilostInvokeAlarmOut)
    ON_BN_CLICKED(IDC_BTN_VILOST_DAY_OK, OnBnClickedBtnVilostDayOk)
    ON_BN_CLICKED(IDC_BTN_VILOST_DAY_COPY, OnBnClickedBtnVilostDayCopy)
    ON_CBN_SELCHANGE(IDC_COMBO_VILOST_WEEKDAY, OnCbnSelchangeComboVilostWeekday)
    ON_NOTIFY(NM_CLICK, IDC_TREE_ALARM_OUT, OnClickTreeAlarmOut)
    ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_ALARMOUT_SELECTALL, OnBtnAlarmoutSelectall)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInChanVideoLostCfg message handlers

void CDlgInChanVideoLostCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if (!TimeTest())
    {
        return;
    }
    
    int	i = m_comboWeekday.GetCurSel();	
    m_struPicCfg.struVILost.struAlarmTime[i][0].byStartHour = (BYTE)m_iHour11;
    m_struPicCfg.struVILost.struAlarmTime[i][0].byStartMin = (BYTE)m_iMin11;
    m_struPicCfg.struVILost.struAlarmTime[i][0].byStopHour = (BYTE)m_iHour12;
    m_struPicCfg.struVILost.struAlarmTime[i][0].byStopMin = (BYTE)m_iMin12;
    m_struPicCfg.struVILost.struAlarmTime[i][1].byStartHour = (BYTE)m_iHour21;
    m_struPicCfg.struVILost.struAlarmTime[i][1].byStartMin = (BYTE)m_iMin21;
    m_struPicCfg.struVILost.struAlarmTime[i][1].byStopHour = (BYTE)m_iHour22;
    m_struPicCfg.struVILost.struAlarmTime[i][1].byStopMin = (BYTE)m_iMin22;
    m_struPicCfg.struVILost.struAlarmTime[i][2].byStartHour = (BYTE)m_iHour31;
    m_struPicCfg.struVILost.struAlarmTime[i][2].byStartMin = (BYTE)m_iMin31;
    m_struPicCfg.struVILost.struAlarmTime[i][2].byStopHour = (BYTE)m_iHour32;
    m_struPicCfg.struVILost.struAlarmTime[i][2].byStopMin = (BYTE)m_iMin32;
    m_struPicCfg.struVILost.struAlarmTime[i][3].byStartHour = (BYTE)m_iHour41;
    m_struPicCfg.struVILost.struAlarmTime[i][3].byStartMin = (BYTE)m_iMin41;
    m_struPicCfg.struVILost.struAlarmTime[i][3].byStopHour = (BYTE)m_iHour42;
    m_struPicCfg.struVILost.struAlarmTime[i][3].byStopMin = (BYTE)m_iMin42;
    m_struPicCfg.struVILost.struAlarmTime[i][4].byStartHour = (BYTE)m_iHour51;
    m_struPicCfg.struVILost.struAlarmTime[i][4].byStartMin = (BYTE)m_iMin51;
    m_struPicCfg.struVILost.struAlarmTime[i][4].byStopHour = (BYTE)m_iHour52;
    m_struPicCfg.struVILost.struAlarmTime[i][4].byStopMin = (BYTE)m_iMin52;
    m_struPicCfg.struVILost.struAlarmTime[i][5].byStartHour = (BYTE)m_iHour61;
    m_struPicCfg.struVILost.struAlarmTime[i][5].byStartMin = (BYTE)m_iMin61;
    m_struPicCfg.struVILost.struAlarmTime[i][5].byStopHour = (BYTE)m_iHour62;
    m_struPicCfg.struVILost.struAlarmTime[i][5].byStopMin = (BYTE)m_iMin62;
    m_struPicCfg.struVILost.struAlarmTime[i][6].byStartHour = (BYTE)m_iHour71;
    m_struPicCfg.struVILost.struAlarmTime[i][6].byStartMin = (BYTE)m_iMin71;
    m_struPicCfg.struVILost.struAlarmTime[i][6].byStopHour = (BYTE)m_iHour72;
    m_struPicCfg.struVILost.struAlarmTime[i][6].byStopMin = (BYTE)m_iMin72;
    m_struPicCfg.struVILost.struAlarmTime[i][7].byStartHour = (BYTE)m_iHour81;
    m_struPicCfg.struVILost.struAlarmTime[i][7].byStartMin = (BYTE)m_iMin81;
    m_struPicCfg.struVILost.struAlarmTime[i][7].byStopHour = (BYTE)m_iHour82;
    m_struPicCfg.struVILost.struAlarmTime[i][7].byStopMin = (BYTE)m_iMin82;
    m_struPicCfg.struVILost.strVILostHandleType.dwHandleType= 0;
    m_struPicCfg.struVILost.strVILostHandleType.dwHandleType |= (m_bChkMonitorAlarm << 0);
    m_struPicCfg.struVILost.strVILostHandleType.dwHandleType |= (m_bChkAudioAlarm << 1);
    m_struPicCfg.struVILost.strVILostHandleType.dwHandleType |= (m_bChkReportCenter << 2);
    m_struPicCfg.struVILost.strVILostHandleType.dwHandleType |= (m_bChkInvokeAlarmOut << 3);
    m_struPicCfg.struVILost.strVILostHandleType.dwHandleType |= (m_bChkInvokeJpegCapture << 4);
    m_struPicCfg.struVILost.strVILostHandleType.dwHandleType |= (m_bChkEmapAlarmOut << 6);
    m_struPicCfg.struVILost.strVILostHandleType.dwHandleType |= (m_bChkPicToFtp << 9);
    m_struPicCfg.struVILost.byEnableHandleVILost = m_bEnable;
    m_struPicCfg.dwSize = sizeof(m_struPicCfg);
    
    for (i=0; i<MAX_ALARMOUT_V30; i++)
    {
	       m_struPicCfg.struVILost.strVILostHandleType.byRelAlarmOut[i] = (BYTE)m_pbAlarmOut[i];
    }
    
    DWORD dwChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    DWORD dwRet = 0;
    if (!NET_DVR_SetDVRConfig(m_lLoginID,NET_DVR_SET_INPUT_CHAN_CFG,dwChannel,&m_struPicCfg,sizeof(m_struPicCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_SET_INPUT_CHAN_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_SET_INPUT_CHAN_CFG");
    }

}


/*********************************************************
  Function:	OnBnClickedChkVilostInvokeAlarmOut
  Desc:		video loss alarm output status
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgInChanVideoLostCfg::OnBnClickedChkVilostInvokeAlarmOut()
{
	UpdateData(TRUE);
	m_treeAlarmOut.EnableWindow(m_bChkInvokeAlarmOut);
}

/*********************************************************
  Function:	CreateTree
  Desc:		create alarm output-channel conections
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgInChanVideoLostCfg::CreateTree(void)
{
	g_CreateAlarmOutTree(m_treeAlarmOut, m_iDevIndex,   m_pbAlarmOut);
}

void CDlgInChanVideoLostCfg::OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult) 
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
	  m_pbAlarmOut[dwIndex] = !bCheck;
	
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

void CDlgInChanVideoLostCfg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CreateTree();
	CDialog::OnPaint();
	// Do not call CDialog::OnPaint() for painting messages
}

BOOL CDlgInChanVideoLostCfg::GetVLHolidayHandle(NET_DVR_HOLIDAY_HANDLE &struHolidayHandle)
{
    DWORD dwRetrun = 0;
    if (NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_VILOST_HOLIDAY_HANDLE, m_iChanShowNum, &struHolidayHandle, sizeof(struHolidayHandle), &dwRetrun))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_VILOST_HOLIDAY_HANDLE");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VILOST_HOLIDAY_HANDLE");
        return FALSE;
    }
    
}

BOOL CDlgInChanVideoLostCfg::SetVLHolidayHandle(NET_DVR_HOLIDAY_HANDLE &struHolidayHandle)
{
    if (NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_VILOST_HOLIDAY_HANDLE, m_iChanShowNum, &struHolidayHandle, sizeof(struHolidayHandle)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VILOST_HOLIDAY_HANDLE");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VILOST_HOLIDAY_HANDLE");
        return FALSE;
    }

}


void CDlgInChanVideoLostCfg::OnBtnAlarmoutSelectall() 
{
	// TODO: Add your control notification handler code here
    CString struAlarmOutText = "";
    DWORD dwID = 0;
    GetDlgItem(IDC_BTN_ALARMOUT_SELECTALL)->GetWindowText(struAlarmOutText);
    if (struAlarmOutText.Find("全选") != -1)
    {
        GetDlgItem(IDC_BTN_ALARMOUT_SELECTALL)->SetWindowText("全不选");
		
        for (int i  = 0; i < MAX_ALARMOUT_V40 ; i++ )
        {
            if ((i <  g_struDeviceInfo[m_iDevIndex].iAlarmOutNum))
            {                
                m_pbAlarmOut[i] = 1;
            }
            else if (i >= MAX_ANALOG_ALARMOUT)
            {
                dwID = g_struDeviceInfo[m_iDevIndex].pStruIPAlarmOutCfgV40->struIPAlarmOutInfo[i-MAX_ANALOG_ALARMOUT].dwIPID;
                if (dwID != 0)
                {
                    m_pbAlarmOut[i] = 1;
                }
            }
        } 
    }
    else   
    {
        GetDlgItem(IDC_BTN_ALARMOUT_SELECTALL)->SetWindowText("全选");
        for (int i  = 0; i < MAX_ALARMOUT_V40 ; i++)
        {
            m_pbAlarmOut[i] = 0; 
        }
    }
    
    CreateTree();
}

/*********************************************************
Function:	TimeTest
Desc:		check time schedule
Input:	
Output:	
Return:	TRUE,correct schedule;FALSE,incorrect schedule;
**********************************************************/
BOOL CDlgInChanVideoLostCfg::TimeTest()
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

/*********************************************************
Function:	OnBnClickedBtnHideAlarmOk
Desc:		check and update time schedule settings
Input:	
Output:	
Return:	
**********************************************************/
void CDlgInChanVideoLostCfg::OnBnClickedBtnVilostDayOk()
{
	UpdateData(TRUE);
	if (!TimeTest())
	{
		return;
	}

	int	i = m_comboWeekday.GetCurSel();	
    if (7 == i)
    {
        m_struVLHolidayHandle.struAlarmTime[0].byStartHour = (BYTE)m_iHour11;
        m_struVLHolidayHandle.struAlarmTime[0].byStartMin = (BYTE)m_iMin11;
        m_struVLHolidayHandle.struAlarmTime[0].byStopHour = (BYTE)m_iHour12;
        m_struVLHolidayHandle.struAlarmTime[0].byStopMin = (BYTE)m_iMin12;
        m_struVLHolidayHandle.struAlarmTime[1].byStartHour = (BYTE)m_iHour21;
        m_struVLHolidayHandle.struAlarmTime[1].byStartMin = (BYTE)m_iMin21;
        m_struVLHolidayHandle.struAlarmTime[1].byStopHour = (BYTE)m_iHour22;
        m_struVLHolidayHandle.struAlarmTime[1].byStopMin = (BYTE)m_iMin22;
        m_struVLHolidayHandle.struAlarmTime[2].byStartHour = (BYTE)m_iHour31;
        m_struVLHolidayHandle.struAlarmTime[2].byStartMin = (BYTE)m_iMin31;
        m_struVLHolidayHandle.struAlarmTime[2].byStopHour = (BYTE)m_iHour32;
        m_struVLHolidayHandle.struAlarmTime[2].byStopMin = (BYTE)m_iMin32;
        m_struVLHolidayHandle.struAlarmTime[3].byStartHour = (BYTE)m_iHour41;
        m_struVLHolidayHandle.struAlarmTime[3].byStartMin = (BYTE)m_iMin41;
        m_struVLHolidayHandle.struAlarmTime[3].byStopHour = (BYTE)m_iHour42;
        m_struVLHolidayHandle.struAlarmTime[3].byStopMin = (BYTE)m_iMin42;
        m_struVLHolidayHandle.struAlarmTime[4].byStartHour = (BYTE)m_iHour51;
        m_struVLHolidayHandle.struAlarmTime[4].byStartMin = (BYTE)m_iMin51;
        m_struVLHolidayHandle.struAlarmTime[4].byStopHour = (BYTE)m_iHour52;
        m_struVLHolidayHandle.struAlarmTime[4].byStopMin = (BYTE)m_iMin52;
        m_struVLHolidayHandle.struAlarmTime[5].byStartHour = (BYTE)m_iHour61;
        m_struVLHolidayHandle.struAlarmTime[5].byStartMin = (BYTE)m_iMin61;
        m_struVLHolidayHandle.struAlarmTime[5].byStopHour = (BYTE)m_iHour62;
        m_struVLHolidayHandle.struAlarmTime[5].byStopMin = (BYTE)m_iMin62;
        m_struVLHolidayHandle.struAlarmTime[6].byStartHour = (BYTE)m_iHour71;
        m_struVLHolidayHandle.struAlarmTime[6].byStartMin = (BYTE)m_iMin71;
        m_struVLHolidayHandle.struAlarmTime[6].byStopHour = (BYTE)m_iHour72;
        m_struVLHolidayHandle.struAlarmTime[6].byStopMin = (BYTE)m_iMin72;
        m_struVLHolidayHandle.struAlarmTime[7].byStartHour = (BYTE)m_iHour81;
        m_struVLHolidayHandle.struAlarmTime[7].byStartMin = (BYTE)m_iMin81;
        m_struVLHolidayHandle.struAlarmTime[7].byStopHour = (BYTE)m_iHour82;
        m_struVLHolidayHandle.struAlarmTime[7].byStopMin = (BYTE)m_iMin82;
        if (!SetVLHolidayHandle(m_struVLHolidayHandle))
        {
            AfxMessageBox("Fail to set holiday handle");
        }
    }
    else
    {
        m_struPicCfg.struVILost.struAlarmTime[i][0].byStartHour = (BYTE)m_iHour11;
        m_struPicCfg.struVILost.struAlarmTime[i][0].byStartMin = (BYTE)m_iMin11;
        m_struPicCfg.struVILost.struAlarmTime[i][0].byStopHour = (BYTE)m_iHour12;
        m_struPicCfg.struVILost.struAlarmTime[i][0].byStopMin = (BYTE)m_iMin12;
        m_struPicCfg.struVILost.struAlarmTime[i][1].byStartHour = (BYTE)m_iHour21;
        m_struPicCfg.struVILost.struAlarmTime[i][1].byStartMin = (BYTE)m_iMin21;
        m_struPicCfg.struVILost.struAlarmTime[i][1].byStopHour = (BYTE)m_iHour22;
        m_struPicCfg.struVILost.struAlarmTime[i][1].byStopMin = (BYTE)m_iMin22;
        m_struPicCfg.struVILost.struAlarmTime[i][2].byStartHour = (BYTE)m_iHour31;
        m_struPicCfg.struVILost.struAlarmTime[i][2].byStartMin = (BYTE)m_iMin31;
        m_struPicCfg.struVILost.struAlarmTime[i][2].byStopHour = (BYTE)m_iHour32;
        m_struPicCfg.struVILost.struAlarmTime[i][2].byStopMin = (BYTE)m_iMin32;
        m_struPicCfg.struVILost.struAlarmTime[i][3].byStartHour = (BYTE)m_iHour41;
        m_struPicCfg.struVILost.struAlarmTime[i][3].byStartMin = (BYTE)m_iMin41;
        m_struPicCfg.struVILost.struAlarmTime[i][3].byStopHour = (BYTE)m_iHour42;
        m_struPicCfg.struVILost.struAlarmTime[i][3].byStopMin = (BYTE)m_iMin42;
        m_struPicCfg.struVILost.struAlarmTime[i][4].byStartHour = (BYTE)m_iHour51;
        m_struPicCfg.struVILost.struAlarmTime[i][4].byStartMin = (BYTE)m_iMin51;
        m_struPicCfg.struVILost.struAlarmTime[i][4].byStopHour = (BYTE)m_iHour52;
        m_struPicCfg.struVILost.struAlarmTime[i][4].byStopMin = (BYTE)m_iMin52;
        m_struPicCfg.struVILost.struAlarmTime[i][5].byStartHour = (BYTE)m_iHour61;
        m_struPicCfg.struVILost.struAlarmTime[i][5].byStartMin = (BYTE)m_iMin61;
        m_struPicCfg.struVILost.struAlarmTime[i][5].byStopHour = (BYTE)m_iHour62;
        m_struPicCfg.struVILost.struAlarmTime[i][5].byStopMin = (BYTE)m_iMin62;
        m_struPicCfg.struVILost.struAlarmTime[i][6].byStartHour = (BYTE)m_iHour71;
        m_struPicCfg.struVILost.struAlarmTime[i][6].byStartMin = (BYTE)m_iMin71;
        m_struPicCfg.struVILost.struAlarmTime[i][6].byStopHour = (BYTE)m_iHour72;
        m_struPicCfg.struVILost.struAlarmTime[i][6].byStopMin = (BYTE)m_iMin72;
        m_struPicCfg.struVILost.struAlarmTime[i][7].byStartHour = (BYTE)m_iHour81;
        m_struPicCfg.struVILost.struAlarmTime[i][7].byStartMin = (BYTE)m_iMin81;
        m_struPicCfg.struVILost.struAlarmTime[i][7].byStopHour = (BYTE)m_iHour82;
        m_struPicCfg.struVILost.struAlarmTime[i][7].byStopMin = (BYTE)m_iMin82;
    }
    GetDlgItem(IDC_BTN_VILOST_DAY_COPY)->EnableWindow(TRUE);
}

/*********************************************************
  Function:	OnBnClickedBtnVilostDayCopy
  Desc:		copy video loss alarm schedule
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgInChanVideoLostCfg::OnBnClickedBtnVilostDayCopy()
{
	UpdateData(TRUE);
	int j,k;
	int i = m_comboWeekday.GetCurSel();
	int m_nCopyTime = m_comboCopyDay.GetCurSel() - 1;

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
				memcpy(&(m_struPicCfg.struVILost.struAlarmTime[j][k]), &(m_struPicCfg.struVILost.struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
			}
		}
	}
    else if (7 == m_nCopyTime)
    {
        for (k = 0; k < MAX_TIMESEGMENT_V30; k++)
        {
            memcpy(&m_struVLHolidayHandle.struAlarmTime[k], &m_struPicCfg.struVILost.struAlarmTime[i][k], sizeof(NET_DVR_SCHEDTIME));
        }
        if (SetVLHolidayHandle(m_struVLHolidayHandle))
        {
            AfxMessageBox("Fail to set holiday handle");
        }
    }
	else
	{
		for (k=0; k<MAX_TIMESEGMENT_V30; k++)
		{
			memcpy(&(m_struPicCfg.struVILost.struAlarmTime[m_nCopyTime][k]), &(m_struPicCfg.struVILost.struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
		}
	}
}

/*********************************************************
  Function:	OnCbnSelchangeComboVilostWeekday
  Desc:		display video loss alarm schedule on selected date
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgInChanVideoLostCfg::OnCbnSelchangeComboVilostWeekday()
{
	UpdateData(TRUE);
	int	i = m_comboWeekday.GetCurSel();	
    if (7 == i) // 假日布防时间段 
    {
        m_iHour11 = m_struVLHolidayHandle.struAlarmTime[0].byStartHour;
        m_iMin11 = m_struVLHolidayHandle.struAlarmTime[0].byStartMin;
        m_iHour12 = m_struVLHolidayHandle.struAlarmTime[0].byStopHour;
        m_iMin12 = m_struVLHolidayHandle.struAlarmTime[0].byStopMin;
        m_iHour21 = m_struVLHolidayHandle.struAlarmTime[1].byStartHour;
        m_iMin21 = m_struVLHolidayHandle.struAlarmTime[1].byStartMin;
        m_iHour22 = m_struVLHolidayHandle.struAlarmTime[1].byStopHour;
        m_iMin22 = m_struVLHolidayHandle.struAlarmTime[1].byStopMin;
        m_iHour31 = m_struVLHolidayHandle.struAlarmTime[2].byStartHour;
        m_iMin31 = m_struVLHolidayHandle.struAlarmTime[2].byStartMin;
        m_iHour32 = m_struVLHolidayHandle.struAlarmTime[2].byStopHour;
        m_iMin32 = m_struVLHolidayHandle.struAlarmTime[2].byStopMin;
        m_iHour41 = m_struVLHolidayHandle.struAlarmTime[3].byStartHour;
        m_iMin41 = m_struVLHolidayHandle.struAlarmTime[3].byStartMin;
        m_iHour42 = m_struVLHolidayHandle.struAlarmTime[3].byStopHour;
        m_iMin42 = m_struVLHolidayHandle.struAlarmTime[3].byStopMin;
        m_iHour51 = m_struVLHolidayHandle.struAlarmTime[4].byStartHour;
        m_iMin51 = m_struVLHolidayHandle.struAlarmTime[4].byStartMin;
        m_iHour52 = m_struVLHolidayHandle.struAlarmTime[4].byStopHour;
        m_iMin52 = m_struVLHolidayHandle.struAlarmTime[4].byStopMin;
        m_iHour61 = m_struVLHolidayHandle.struAlarmTime[5].byStartHour;
        m_iMin61 = m_struVLHolidayHandle.struAlarmTime[5].byStartMin;
        m_iHour62 = m_struVLHolidayHandle.struAlarmTime[5].byStopHour;
        m_iMin62 = m_struVLHolidayHandle.struAlarmTime[5].byStopMin;
        m_iHour71 = m_struVLHolidayHandle.struAlarmTime[6].byStartHour;
        m_iMin71 = m_struVLHolidayHandle.struAlarmTime[6].byStartMin;
        m_iHour72 = m_struVLHolidayHandle.struAlarmTime[6].byStopHour;
        m_iMin72 = m_struVLHolidayHandle.struAlarmTime[6].byStopMin;
        m_iHour81 = m_struVLHolidayHandle.struAlarmTime[7].byStartHour;
        m_iMin81 = m_struVLHolidayHandle.struAlarmTime[7].byStartMin;
        m_iHour82 = m_struVLHolidayHandle.struAlarmTime[7].byStopHour;
        m_iMin82 = m_struVLHolidayHandle.struAlarmTime[7].byStopMin;
    }
    else
    {
	    m_iHour11 = m_struPicCfg.struVILost.struAlarmTime[i][0].byStartHour;
	    m_iMin11 = m_struPicCfg.struVILost.struAlarmTime[i][0].byStartMin;
	    m_iHour12 = m_struPicCfg.struVILost.struAlarmTime[i][0].byStopHour;
	    m_iMin12 = m_struPicCfg.struVILost.struAlarmTime[i][0].byStopMin;
	    m_iHour21 = m_struPicCfg.struVILost.struAlarmTime[i][1].byStartHour;
	    m_iMin21 = m_struPicCfg.struVILost.struAlarmTime[i][1].byStartMin;
	    m_iHour22 = m_struPicCfg.struVILost.struAlarmTime[i][1].byStopHour;
	    m_iMin22 = m_struPicCfg.struVILost.struAlarmTime[i][1].byStopMin;
	    m_iHour31 = m_struPicCfg.struVILost.struAlarmTime[i][2].byStartHour;
	    m_iMin31 = m_struPicCfg.struVILost.struAlarmTime[i][2].byStartMin;
	    m_iHour32 = m_struPicCfg.struVILost.struAlarmTime[i][2].byStopHour;
	    m_iMin32 = m_struPicCfg.struVILost.struAlarmTime[i][2].byStopMin;
	    m_iHour41 = m_struPicCfg.struVILost.struAlarmTime[i][3].byStartHour;
	    m_iMin41 = m_struPicCfg.struVILost.struAlarmTime[i][3].byStartMin;
	    m_iHour42 = m_struPicCfg.struVILost.struAlarmTime[i][3].byStopHour;
	    m_iMin42 = m_struPicCfg.struVILost.struAlarmTime[i][3].byStopMin;
	    m_iHour51 = m_struPicCfg.struVILost.struAlarmTime[i][4].byStartHour;
	    m_iMin51 = m_struPicCfg.struVILost.struAlarmTime[i][4].byStartMin;
	    m_iHour52 = m_struPicCfg.struVILost.struAlarmTime[i][4].byStopHour;
	    m_iMin52 = m_struPicCfg.struVILost.struAlarmTime[i][4].byStopMin;
	    m_iHour61 = m_struPicCfg.struVILost.struAlarmTime[i][5].byStartHour;
	    m_iMin61 = m_struPicCfg.struVILost.struAlarmTime[i][5].byStartMin;
	    m_iHour62 = m_struPicCfg.struVILost.struAlarmTime[i][5].byStopHour;
	    m_iMin62 = m_struPicCfg.struVILost.struAlarmTime[i][5].byStopMin;
	    m_iHour71 = m_struPicCfg.struVILost.struAlarmTime[i][6].byStartHour;
	    m_iMin71 = m_struPicCfg.struVILost.struAlarmTime[i][6].byStartMin;
	    m_iHour72 = m_struPicCfg.struVILost.struAlarmTime[i][6].byStopHour;
	    m_iMin72 = m_struPicCfg.struVILost.struAlarmTime[i][6].byStopMin;
	    m_iHour81 = m_struPicCfg.struVILost.struAlarmTime[i][7].byStartHour;
	    m_iMin81 = m_struPicCfg.struVILost.struAlarmTime[i][7].byStartMin;
	    m_iHour82 = m_struPicCfg.struVILost.struAlarmTime[i][7].byStopHour;
	    m_iMin82 = m_struPicCfg.struVILost.struAlarmTime[i][7].byStopMin;
    }
    UpdateData(FALSE);
}

BOOL CDlgInChanVideoLostCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
    m_pbAlarmOut = new BOOL[MAX_ALARMOUT_V40];
    if(m_pbAlarmOut != NULL)
    {
        memset(m_pbAlarmOut,0x0,sizeof(BOOL) * MAX_ALARMOUT_V40);
     }
	// TODO: Add extra initialization here
	
    memset(&m_struPicCfg,0,sizeof(m_struPicCfg));
    DWORD dwIndex = 0;
    char szLan[128] = {0};
    m_cmbChannel.ResetContent();
    dwIndex = 0;
    BOOL bBreak = FALSE;
    int i =0,j=0;
    for (i = 0; i< m_struSystemInfo.byVideoInTypeNum; i++)
    {         
        for ( j = 0; j < m_struSystemInfo.struVideoIn[i].wInNum; j++)
        {
            switch(m_struSystemInfo.struVideoIn[i].wInType)
            {
            case 0:
                sprintf(szLan,"SDI%02d",j+1); 
                break;
            case 1:
                sprintf(szLan,"VGA%02d",j+1); 
                break;
            case 2:
                sprintf(szLan,"HDMI%02d",j+1); 
                break;
            case 3:
                sprintf(szLan,"IP%02d",j+1); 
                break;
            case 4:
                sprintf(szLan,"PIP%02d",j+1); 
                break;
            default:
                sprintf(szLan,"Unkown%02d",j+1); 
                break;
            }           
            
            m_cmbChannel.AddString(szLan);
            m_cmbChannel.SetItemData(dwIndex,m_struSystemInfo.struVideoIn[i].wStartNo + j);
            dwIndex++;
        }
    }
    
    
    m_cmbChannel.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgInChanVideoLostCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    DWORD dwChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    DWORD dwRet = 0;
    memset(&m_struPicCfg,0,sizeof(m_struPicCfg));
    if (!NET_DVR_GetDVRConfig(m_lLoginID,NET_DVR_GET_INPUT_CHAN_CFG,dwChannel,&m_struPicCfg,sizeof(m_struPicCfg),&dwRet))
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_GET_INPUT_CHAN_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_GET_INPUT_CHAN_CFG");
    }
    if (!TimeTest())
    {
        return;
    }
    
    int	i = m_comboWeekday.GetCurSel();	
    m_iHour11 = m_struPicCfg.struVILost.struAlarmTime[i][0].byStartHour;
    m_iMin11 = m_struPicCfg.struVILost.struAlarmTime[i][0].byStartMin;
    m_iHour12 = m_struPicCfg.struVILost.struAlarmTime[i][0].byStopHour;
    m_iMin12 = m_struPicCfg.struVILost.struAlarmTime[i][0].byStopMin;
    m_iHour21 = m_struPicCfg.struVILost.struAlarmTime[i][1].byStartHour;
    m_iMin21 = m_struPicCfg.struVILost.struAlarmTime[i][1].byStartMin;
    m_iHour22 = m_struPicCfg.struVILost.struAlarmTime[i][1].byStopHour;
    m_iMin22 =  m_struPicCfg.struVILost.struAlarmTime[i][1].byStopMin;
    m_iHour31 = m_struPicCfg.struVILost.struAlarmTime[i][2].byStartHour;
    m_iMin31 = m_struPicCfg.struVILost.struAlarmTime[i][2].byStartMin;
    m_iHour32 = m_struPicCfg.struVILost.struAlarmTime[i][2].byStopHour;
    m_iMin32 = m_struPicCfg.struVILost.struAlarmTime[i][2].byStopMin;
    m_iHour41 = m_struPicCfg.struVILost.struAlarmTime[i][3].byStartHour;
    m_iMin41 = m_struPicCfg.struVILost.struAlarmTime[i][3].byStartMin;
    m_iHour42 = m_struPicCfg.struVILost.struAlarmTime[i][3].byStopHour;
    m_iMin42 = m_struPicCfg.struVILost.struAlarmTime[i][3].byStopMin;
    m_iHour51 = m_struPicCfg.struVILost.struAlarmTime[i][4].byStartHour;
    m_iMin51 = m_struPicCfg.struVILost.struAlarmTime[i][4].byStartMin;
    m_iHour52 = m_struPicCfg.struVILost.struAlarmTime[i][4].byStopHour;
    m_iHour61 = m_struPicCfg.struVILost.struAlarmTime[i][4].byStopMin;
    m_iMin61 = m_struPicCfg.struVILost.struAlarmTime[i][5].byStartHour;
    m_iHour62 = m_struPicCfg.struVILost.struAlarmTime[i][5].byStartMin;
    m_iMin62 = m_struPicCfg.struVILost.struAlarmTime[i][5].byStopHour;
    m_iHour71 = m_struPicCfg.struVILost.struAlarmTime[i][5].byStopMin;
    m_iMin71 = m_struPicCfg.struVILost.struAlarmTime[i][6].byStartHour;
    m_iHour72 = m_struPicCfg.struVILost.struAlarmTime[i][6].byStartMin;
    m_iHour72 = m_struPicCfg.struVILost.struAlarmTime[i][6].byStopHour;
    m_iMin72 = m_struPicCfg.struVILost.struAlarmTime[i][6].byStopMin;
    m_iHour81 = m_struPicCfg.struVILost.struAlarmTime[i][7].byStartHour;
    m_iMin81 = m_struPicCfg.struVILost.struAlarmTime[i][7].byStartMin;
    m_iHour82 = m_struPicCfg.struVILost.struAlarmTime[i][7].byStopHour;
    m_iMin82 = m_struPicCfg.struVILost.struAlarmTime[i][7].byStopMin;

    m_bChkMonitorAlarm = m_struPicCfg.struVILost.strVILostHandleType.dwHandleType  &0x01;
    m_bChkAudioAlarm = (m_struPicCfg.struVILost.strVILostHandleType.dwHandleType >>1)&0x01;
    m_bChkReportCenter = (m_struPicCfg.struVILost.strVILostHandleType.dwHandleType >>2)&0x01;
    m_bChkInvokeAlarmOut = (m_struPicCfg.struVILost.strVILostHandleType.dwHandleType >>3)&0x01;
    m_bChkInvokeJpegCapture = (m_struPicCfg.struVILost.strVILostHandleType.dwHandleType >>4)&0x01;
    m_bChkEmapAlarmOut = (m_struPicCfg.struVILost.strVILostHandleType.dwHandleType >>6)&0x01;
	m_bChkPicToFtp = (m_struPicCfg.struVILost.strVILostHandleType.dwHandleType >>9)&0x01;
   
    m_bEnable = m_struPicCfg.struVILost.byEnableHandleVILost ;
    for (i=0; i<MAX_ALARMOUT_V30; i++)
    {
	       m_pbAlarmOut[i] = m_struPicCfg.struVILost.strVILostHandleType.byRelAlarmOut[i];
    }

    CreateTree();
    UpdateData(FALSE);
}
