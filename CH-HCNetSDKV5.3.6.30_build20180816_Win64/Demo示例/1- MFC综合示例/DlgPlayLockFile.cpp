// DlgPlayLockFile.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgPlayLockFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPlayLockFile dialog


CDlgPlayLockFile::CDlgPlayLockFile(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPlayLockFile::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPlayLockFile)
	m_dwDuration = 0;
	m_ctLockBeginDate = 0;
	m_ctLockBeginTime = 0;
	m_ctLockEndDate = 0;
	m_ctLockEndTime = 0;
	m_dwDiskNO = 0;
	m_ctLockBeginDate2 = 0;
	m_ctLockBeginTime2 = 0;
	m_ctLockEndDate2 = 0;
	m_ctLockEndTime2 = 0;
	m_ctUnlockTimePointDate = 0;
	m_ctUnlockTimePointTime = 0;
	m_bOfflineRecord = FALSE;
	//}}AFX_DATA_INIT

	m_iCurSelectedRow = -1;
}

CDlgPlayLockFile::~CDlgPlayLockFile()
{

}


void CDlgPlayLockFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPlayLockFile)
	DDX_Control(pDX, IDC_LIST_IP_CHAN, m_listChannelRecordStatus);
	DDX_Control(pDX, IDC_COMBO_GROUPNO, m_comboGroupNO);
	DDX_Control(pDX, IDC_COMBO_RECORD_TYPE, m_comboRecordType);
	DDX_Text(pDX, IDC_EDIT_DURATION, m_dwDuration);
	DDX_DateTimeCtrl(pDX, IDC_LOCK_BEGIN_DATE, m_ctLockBeginDate);
	DDX_DateTimeCtrl(pDX, IDC_LOCK_BEGIN_TIME, m_ctLockBeginTime);
	DDX_DateTimeCtrl(pDX, IDC_LOCK_END_DATE, m_ctLockEndDate);
	DDX_DateTimeCtrl(pDX, IDC_LOCK_END_TIME, m_ctLockEndTime);
	DDX_Text(pDX, IDC_EDIT_DISK_NO, m_dwDiskNO);
	DDX_DateTimeCtrl(pDX, IDC_LOCK_BEGIN_DATE2, m_ctLockBeginDate2);
	DDX_DateTimeCtrl(pDX, IDC_LOCK_BEGIN_TIME2, m_ctLockBeginTime2);
	DDX_DateTimeCtrl(pDX, IDC_LOCK_END_DATE2, m_ctLockEndDate2);
	DDX_DateTimeCtrl(pDX, IDC_LOCK_END_TIME2, m_ctLockEndTime2);
	DDX_DateTimeCtrl(pDX, IDC_UNLOCK_TIME_POINT_DATE, m_ctUnlockTimePointDate);
	DDX_DateTimeCtrl(pDX, IDC_UNLOCK_TIME_POINT_TIME, m_ctUnlockTimePointTime);
	DDX_Check(pDX, IDC_CHECK_OFFLINE_RECORD, m_bOfflineRecord);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPlayLockFile, CDialog)
	//{{AFX_MSG_MAP(CDlgPlayLockFile)
	ON_BN_CLICKED(IDC_BTN_FILE_LOCK, OnBtnFileLock)
	ON_BN_CLICKED(IDC_BTN_FILE_UNLOCK, OnBtnFileUnlock)
	ON_BN_CLICKED(IDC_BTN_UPDATE_RECORD_INFO, OnBtnUpdateRecordInfo)
	ON_CBN_SELCHANGE(IDC_COMBO_GROUPNO, OnSelchangeComboGroupno)
	ON_NOTIFY(NM_CLICK, IDC_LIST_IP_CHAN, OnClickListIpChan)
	ON_BN_CLICKED(IDC_BTN_MODIFY_INFO, OnBtnModifyInfo)
	ON_BN_CLICKED(IDC_BTN_SET_RECORD_DISK, OnBtnSetRecordDisk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPlayLockFile message handlers
/*********************************************************
  Function:	SetParentWnd
  Desc:		transmit the handle of parent dialog box
  Input:	hhWnd, pointer to handle array
  Output:	
  Return:	
**********************************************************/
void CDlgPlayLockFile::SetParentWnd(HWND *hhWnd, int iParentNum)
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
BOOL CDlgPlayLockFile::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);
	CTime timeCur = CTime::GetCurrentTime();
	CTime timeStart(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),0,0,0);
	CTime timeStop(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),23,59,59);
	m_ctLockBeginDate  = timeStart;
	m_ctLockEndDate    = timeStop;
	m_ctLockBeginTime  = timeStart;
	m_ctLockEndTime    = timeStop;
    m_ctLockBeginDate2 = timeCur;
	m_ctLockBeginTime2 = timeCur;
	m_ctLockEndDate2   = timeCur;
	m_ctLockEndTime2   = timeCur;
	m_ctUnlockTimePointTime = timeCur;
	m_ctUnlockTimePointDate = timeCur;
	//CheckInitParam();
	memset(&m_struLockPara,0,sizeof(NET_DVR_TIME_LOCK));
	memset(&m_struLockReturn,0,sizeof(NET_DVR_LOCK_RETURN));

	m_listChannelRecordStatus.SetExtendedStyle(m_listChannelRecordStatus.GetExtendedStyle()|LVS_EX_FULLROWSELECT);
	char szLan[128] = {0};
	g_StringLanType(szLan, "ÐòºÅ", "Serial No.");
	m_listChannelRecordStatus.InsertColumn(0, szLan,LVCFMT_LEFT,40,-1);
	g_StringLanType(szLan, "Í¨µÀºÅ", "Channel");
	m_listChannelRecordStatus.InsertColumn(1,szLan,LVCFMT_LEFT,80,-1);
	
	g_StringLanType(szLan, "ÊÇ·ñ¿ÉÓÃ", "Whether enable");
	m_listChannelRecordStatus.InsertColumn(2, szLan,LVCFMT_LEFT,80,-1);
	g_StringLanType(szLan, "Â¼Ïñ×´Ì¬", "Record status");
	m_listChannelRecordStatus.InsertColumn(3, szLan,LVCFMT_LEFT,100,-1);

	g_StringLanType(szLan, "´ÅÅÌºÅ", "Disk NO.");
	m_listChannelRecordStatus.InsertColumn(4, szLan,LVCFMT_LEFT,100,-1);

	g_StringLanType(szLan, "¶ÏÍøÁª¶¯Â¼Ïñ", "Off Line Record");
	m_listChannelRecordStatus.InsertColumn(5, szLan, LVCFMT_LEFT,100,-1);

	return TRUE;
}

/*********************************************************
  Function:	CheckDate
  Desc:		check start and stop time
  Input:	tFrom,start time; tTo,stop time;
  Output:	
  Return:	TRUE,correct time;FALSE,timing error;
**********************************************************/
BOOL CDlgPlayLockFile::CheckDate(CTime tFrom, CTime tTo)
{
	if (tFrom.GetYear() > tTo.GetYear())
	{
		return FALSE;
	}
	else
	{
		if (tFrom.GetYear() == tTo.GetYear())
		{
			if (tFrom.GetMonth() > tTo.GetMonth())
			{
				return FALSE;
			}
			else
			{
				if (tFrom.GetMonth() == tTo.GetMonth())
				{
					if (tFrom.GetDay() > tTo.GetDay())
					{
						return FALSE;
					}
					else
					{
						if (tFrom.GetDay() == tTo.GetDay())
						{
							if (tFrom.GetHour() > tTo.GetHour())
							{
								return FALSE;
							}
							else
							{
								if (tFrom.GetHour() == tTo.GetHour())
								{
									if (tFrom.GetMinute() > tTo.GetMinute())
									{
										return FALSE;
									}
									else
									{
										if (tFrom.GetMinute() == tTo.GetMinute())
										{
											if (tFrom.GetSecond() > tTo.GetSecond())
											{
												return FALSE;
											}
										}//end sec
									}//end min
								}
							}//end hour
						}
					}//end day
				}
			}//end month
		}
	}//end year
	return TRUE;
}


/*********************************************************
  Function:	CheckInitParam
  Desc:		check current device parameters, and initialize dialog box parameters
  Input:	
  Output:	
  Return:	TRUE,check and initialize correctly;FALSE,check failed,not initialized;
**********************************************************/
BOOL CDlgPlayLockFile::CheckInitParam()
{
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	if (iDeviceIndex == -1)
	{
		UpdateData(FALSE);
		return FALSE;
	}

// 	if (iDeviceIndex != m_iDeviceIndex)
// 	{
		m_iDeviceIndex = iDeviceIndex;
		m_lLoginID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
		m_iChanCount = g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum;		
		m_lStartChan = g_struDeviceInfo[m_iDeviceIndex].iStartChan;
//	}
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	
	if (iChanIndex != m_iChanIndex)//-1 all channel
	{
		m_iChanIndex = iChanIndex;
	}

	UpdateData(FALSE); 
	return TRUE;
}
/*********************************************************
Function:	OnBtnFileLock
Desc:		lock file by time
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPlayLockFile::OnBtnFileLock() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
    CTime ctLockBegin(m_ctLockBeginDate.GetYear(),m_ctLockBeginDate.GetMonth(),m_ctLockBeginDate.GetDay(),
		m_ctLockBeginTime.GetHour(),m_ctLockBeginTime.GetMinute(),m_ctLockBeginTime.GetSecond());
	CTime ctLockEnd(m_ctLockEndDate.GetYear(),m_ctLockEndDate.GetMonth(),m_ctLockEndDate.GetDay(),
		m_ctLockEndTime.GetHour(),m_ctLockEndTime.GetMinute(),m_ctLockEndTime.GetSecond());
	if (!CheckDate(ctLockBegin,ctLockEnd))
	{
		return;
	}

	m_struLockPara.dwSize = sizeof(NET_DVR_TIME_LOCK);
	m_struLockPara.strBeginTime.dwYear   = (DWORD)m_ctLockBeginDate.GetYear();
	m_struLockPara.strBeginTime.dwMonth  = (DWORD)m_ctLockBeginDate.GetMonth();
	m_struLockPara.strBeginTime.dwDay    = (DWORD)m_ctLockBeginDate.GetDay();
	m_struLockPara.strBeginTime.dwHour   = (DWORD)m_ctLockBeginTime.GetHour();
	m_struLockPara.strBeginTime.dwMinute = (DWORD)m_ctLockBeginTime.GetMinute();
	m_struLockPara.strBeginTime.dwSecond = (DWORD)m_ctLockBeginTime.GetSecond();
	
	m_struLockPara.strEndTime.dwYear   = (DWORD)m_ctLockEndDate.GetYear();
	m_struLockPara.strEndTime.dwMonth  = (DWORD)m_ctLockEndDate.GetMonth();
	m_struLockPara.strEndTime.dwDay    = (DWORD)m_ctLockEndDate.GetDay();
	m_struLockPara.strEndTime.dwHour   = (DWORD)m_ctLockEndTime.GetHour();
	m_struLockPara.strEndTime.dwMinute = (DWORD)m_ctLockEndTime.GetMinute();
	m_struLockPara.strEndTime.dwSecond = (DWORD)m_ctLockEndTime.GetSecond();

	m_struLockPara.strUnlockTimePoint.wYear = (WORD)m_ctUnlockTimePointDate.GetYear();
	m_struLockPara.strUnlockTimePoint.byMonth = (BYTE)m_ctUnlockTimePointDate.GetMonth();
	m_struLockPara.strUnlockTimePoint.byDay = (BYTE)m_ctUnlockTimePointDate.GetDay();
	m_struLockPara.strUnlockTimePoint.byHour = (BYTE)m_ctUnlockTimePointTime.GetHour();
	m_struLockPara.strUnlockTimePoint.byMinute = (BYTE)m_ctUnlockTimePointTime.GetMinute();
	m_struLockPara.strUnlockTimePoint.bySecond = (BYTE)m_ctUnlockTimePointTime.GetSecond();

	
	m_struLockPara.dwChannel      = (DWORD)(m_iChanIndex + m_lStartChan);
	CString strDebug;
	strDebug.Format("m_iChanIndex = %d, m_lStartChan = %d\n", m_iChanIndex, m_lStartChan);
	OutputDebugString(strDebug);
	m_struLockPara.dwLockDuration = m_dwDuration;
    m_struLockPara.dwRecordType   = (DWORD)m_comboRecordType.GetCurSel();
	if (0x00000008 == m_struLockPara.dwRecordType)
	{
		m_struLockPara.dwRecordType = 0xffffffff;
	}
	
	m_struLockReturn.dwSize = sizeof(NET_DVR_LOCK_RETURN);	
	

 	if (NET_DVR_LockFileByTime(m_lLoginID, &m_struLockPara, &m_struLockReturn))
    {
		g_StringLanType(szLan,"Â¼Ïñ¶Î¼ÓËø³É¹¦","Success");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "File locked");
		AfxMessageBox(szLan);
        
		CTime ctReturnBegin((int)m_struLockReturn.strBeginTime.dwYear,(int)m_struLockReturn.strBeginTime.dwMonth,\
		    (int)m_struLockReturn.strBeginTime.dwDay,(int)m_struLockReturn.strBeginTime.dwHour,\
		    (int)m_struLockReturn.strBeginTime.dwMinute,(int)m_struLockReturn.strBeginTime.dwSecond);
		CTime ctReturnEnd((int)m_struLockReturn.strEndTime.dwYear,(int)m_struLockReturn.strEndTime.dwMonth,\
		    (int)m_struLockReturn.strEndTime.dwDay,(int)m_struLockReturn.strEndTime.dwHour,\
		    (int)m_struLockReturn.strEndTime.dwMinute,(int)m_struLockReturn.strEndTime.dwSecond);
		m_ctLockBeginDate2 = ctReturnBegin;
		m_ctLockBeginTime2 = ctReturnBegin;
		m_ctLockEndDate2   = ctReturnEnd;
		m_ctLockEndTime2   = ctReturnEnd;
		
		UpdateData(FALSE);
		return;
    }
    else
	{        
		g_StringLanType(szLan,"Â¼Ïñ¶Î¼ÓËøÊ§°Ü","Fail to lock");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Lock file err");
		AfxMessageBox(szLan);
		return;
	}	

}

void CDlgPlayLockFile::OnBtnFileUnlock() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	CTime ctLockBegin(m_ctLockBeginDate.GetYear(),m_ctLockBeginDate.GetMonth(),m_ctLockBeginDate.GetDay(),
		m_ctLockBeginTime.GetHour(),m_ctLockBeginTime.GetMinute(),m_ctLockBeginTime.GetSecond());
	CTime ctLockEnd(m_ctLockEndDate.GetYear(),m_ctLockEndDate.GetMonth(),m_ctLockEndDate.GetDay(),
		m_ctLockEndTime.GetHour(),m_ctLockEndTime.GetMinute(),m_ctLockEndTime.GetSecond());
	if (!CheckDate(m_ctLockBeginDate,m_ctLockEndDate))
	{
		return;
	}
	
	m_struLockPara.dwSize = sizeof(NET_DVR_TIME_LOCK);
	m_struLockPara.strBeginTime.dwYear   = (DWORD)m_ctLockBeginDate.GetYear();
	m_struLockPara.strBeginTime.dwMonth  = (DWORD)m_ctLockBeginDate.GetMonth();
	m_struLockPara.strBeginTime.dwDay    = (DWORD)m_ctLockBeginDate.GetDay();
	m_struLockPara.strBeginTime.dwHour   = (DWORD)m_ctLockBeginTime.GetHour();
	m_struLockPara.strBeginTime.dwMinute = (DWORD)m_ctLockBeginTime.GetMinute();
	m_struLockPara.strBeginTime.dwSecond = (DWORD)m_ctLockBeginTime.GetSecond();
	
	m_struLockPara.strEndTime.dwYear   = (DWORD)m_ctLockEndDate.GetYear();
	m_struLockPara.strEndTime.dwMonth  = (DWORD)m_ctLockEndDate.GetMonth();
	m_struLockPara.strEndTime.dwDay    = (DWORD)m_ctLockEndDate.GetDay();
	m_struLockPara.strEndTime.dwHour   = (DWORD)m_ctLockEndTime.GetHour();
	m_struLockPara.strEndTime.dwMinute = (DWORD)m_ctLockEndTime.GetMinute();
	m_struLockPara.strEndTime.dwSecond = (DWORD)m_ctLockEndTime.GetSecond();
	
	m_struLockPara.dwChannel      = (DWORD)(m_iChanIndex + m_lStartChan);
	m_struLockPara.dwLockDuration = m_dwDuration;
    m_struLockPara.dwRecordType   = (DWORD)m_comboRecordType.GetCurSel();
	if (0x00000008 == m_struLockPara.dwRecordType)
	{
		m_struLockPara.dwRecordType = 0xffffffff;
	}
	
	m_struLockReturn.dwSize = sizeof(NET_DVR_LOCK_RETURN);
		
	
	if (NET_DVR_UnlockFileByTime(m_lLoginID, &m_struLockPara, &m_struLockReturn))
    {
		g_StringLanType(szLan,"Â¼Ïñ¶Î½âËø³É¹¦","Success");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "File unlocked");
		AfxMessageBox(szLan);
        
		CTime ctReturnBegin((int)m_struLockReturn.strBeginTime.dwYear,(int)m_struLockReturn.strBeginTime.dwMonth,
			(int)m_struLockReturn.strBeginTime.dwDay,(int)m_struLockReturn.strBeginTime.dwHour,
			(int)m_struLockReturn.strBeginTime.dwMinute,(int)m_struLockReturn.strBeginTime.dwSecond);
		CTime ctReturnEnd((int)m_struLockReturn.strEndTime.dwYear,(int)m_struLockReturn.strEndTime.dwMonth,
			(int)m_struLockReturn.strEndTime.dwDay,(int)m_struLockReturn.strEndTime.dwHour,
			(int)m_struLockReturn.strEndTime.dwMinute,(int)m_struLockReturn.strEndTime.dwSecond);
		m_ctLockBeginDate2 = ctReturnBegin;
		m_ctLockBeginTime2 = ctReturnBegin;
		m_ctLockEndDate2   = ctReturnEnd;
		m_ctLockEndTime2   = ctReturnEnd;
		
		UpdateData(FALSE);
		return;
    }
    else
	{        
		g_StringLanType(szLan,"Â¼Ïñ¶Î½âËøÊ§°Ü","Fail to unlock");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Unlock file err");
		AfxMessageBox(szLan);
		return;
	}
}

void CDlgPlayLockFile::OnBtnUpdateRecordInfo() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_IPPARACFG_V40 struIPAccessCfgV40;
	DWORD dwReturned = 0;
	memset(&struIPAccessCfgV40, 0, sizeof(NET_DVR_IPPARACFG_V40));
	BOOL bRet = NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_IPPARACFG_V40, 0, &struIPAccessCfgV40, sizeof(NET_DVR_IPPARACFG_V40), &dwReturned);
	if (!bRet)
	{	
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_IPPARACFG_V40");
		return;
	}
	
	int i = 0;
	char szLan[128] = {0};
	m_comboGroupNO.ResetContent();
	for (i = 0; i < (int)struIPAccessCfgV40.dwGroupNum; i++)
	{
		memset(szLan, 0, 128);
		sprintf(szLan, "%d", i);
		m_comboGroupNO.AddString(szLan);
	}
	
	m_comboGroupNO.SetCurSel(0);
	//get group[0]
	memset(&m_struGroupRecordStatus, 0, sizeof(m_struGroupRecordStatus));
	m_struGroupRecordStatus.dwSize = sizeof(m_struGroupRecordStatus);
	bRet = NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_RECORD_CHANNEL_INFO, 0, &m_struGroupRecordStatus, sizeof(NET_DVR_CHAN_GROUP_RECORD_STATUS), &dwReturned);
	if (!bRet)
	{	
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_RECORD_CHANNEL_INFO");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_RECORD_CHANNEL_INFO");
	}

	CString strTemp =_T("");
	m_listChannelRecordStatus.DeleteAllItems();
	for (i = 0; i < 64; i++)
	{
		//NO.
		strTemp.Format("%02d", i + 1);
		m_listChannelRecordStatus.InsertItem(i, strTemp, 0);
		
		//channel NO.
		strTemp.Format("%06d", m_struGroupRecordStatus.struChanStatus[i].wChannelNO);
		m_listChannelRecordStatus.SetItemText(i, 1, strTemp);

		//Is enable
		strTemp.Format("%d", m_struGroupRecordStatus.struChanStatus[i].byValid);
		m_listChannelRecordStatus.SetItemText(i, 2, strTemp);
		
		//Is record
		strTemp.Format("%d", m_struGroupRecordStatus.struChanStatus[i].byRecord);
		m_listChannelRecordStatus.SetItemText(i, 3, strTemp);
		
		//Disk NO.
		strTemp.Format("%06d", m_struGroupRecordStatus.struChanStatus[i].dwRelatedHD);
		m_listChannelRecordStatus.SetItemText(i, 4, strTemp);

		//offline record.
		strTemp.Format("%d", m_struGroupRecordStatus.struChanStatus[i].byOffLineRecord);
		m_listChannelRecordStatus.SetItemText(i, 5, strTemp);
	}

	UpdateData(FALSE);
}

void CDlgPlayLockFile::OnSelchangeComboGroupno() 
{
	// TODO: Add your control notification handler code here
	int iGroupNO = m_comboGroupNO.GetCurSel();
	DWORD dwReturned = 0;

	memset(&m_struGroupRecordStatus, 0, sizeof(m_struGroupRecordStatus));
	BOOL bRet = NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_RECORD_CHANNEL_INFO, iGroupNO, &m_struGroupRecordStatus, sizeof(NET_DVR_CHAN_GROUP_RECORD_STATUS), &dwReturned);
	if (!bRet)
	{	
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_RECORD_CHANNEL_INFO");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_RECORD_CHANNEL_INFO");
	}
	
	int i = 0;
	CString strTemp =_T("");
	m_listChannelRecordStatus.DeleteAllItems();
	for (i = 0; i < 64; i++)
	{
		//NO.
		strTemp.Format("%02d", i + 1);
		m_listChannelRecordStatus.InsertItem(i, strTemp, 0);
		
		//channel NO.
		strTemp.Format("%06d", m_struGroupRecordStatus.struChanStatus[i].wChannelNO);
		m_listChannelRecordStatus.SetItemText(i, 1, strTemp);
		
		//Is enable
		strTemp.Format("%d", m_struGroupRecordStatus.struChanStatus[i].byValid);
		m_listChannelRecordStatus.SetItemText(i, 2, strTemp);
		
		//Is record
		strTemp.Format("%d", m_struGroupRecordStatus.struChanStatus[i].byRecord);
		m_listChannelRecordStatus.SetItemText(i, 3, strTemp);
		
		//Disk NO.
		strTemp.Format("%06d", m_struGroupRecordStatus.struChanStatus[i].dwRelatedHD);
		m_listChannelRecordStatus.SetItemText(i, 4, strTemp);

		//OffLine.
		strTemp.Format("%d", m_struGroupRecordStatus.struChanStatus[i].byOffLineRecord);
		m_listChannelRecordStatus.SetItemText(i, 5, strTemp);

		//m_listChannelRecordStatus.SetItemData(i, i);
	}
	
	UpdateData(FALSE);
}

void CDlgPlayLockFile::OnClickListIpChan(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION  iPos = m_listChannelRecordStatus.GetFirstSelectedItemPosition();
	if (iPos == NULL)
	{
		return;
	}
 	m_iCurSelectedRow = m_listChannelRecordStatus.GetNextSelectedItem(iPos);
	m_dwDiskNO = m_struGroupRecordStatus.struChanStatus[m_iCurSelectedRow].dwRelatedHD;
	m_bOfflineRecord = m_struGroupRecordStatus.struChanStatus[m_iCurSelectedRow].byOffLineRecord;

	UpdateData(FALSE);
}

void CDlgPlayLockFile::OnBtnModifyInfo() 
{
	UpdateData(TRUE);
	// TODO: Add your control notification handler code here
	if (m_iCurSelectedRow < 0)
	{
		return;
	}

	CString strTemp =_T("");
	m_struGroupRecordStatus.struChanStatus[m_iCurSelectedRow].dwRelatedHD = m_dwDiskNO;
	m_struGroupRecordStatus.struChanStatus[m_iCurSelectedRow].byOffLineRecord = m_bOfflineRecord;
	strTemp.Format("%06d", m_dwDiskNO);
	m_listChannelRecordStatus.SetItemText(m_iCurSelectedRow, 4, strTemp);

	strTemp.Format("%d", m_bOfflineRecord);
	m_listChannelRecordStatus.SetItemText(m_iCurSelectedRow, 5, strTemp);

	UpdateData(FALSE);
}

void CDlgPlayLockFile::OnBtnSetRecordDisk() 
{
	// TODO: Add your control notification handler code here
	BOOL bRet = NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_RECORD_CHANNEL_INFO, 0, &m_struGroupRecordStatus, sizeof(NET_DVR_CHAN_GROUP_RECORD_STATUS));
	if (!bRet)
	{	
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_RECORD_CHANNEL_INFO");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_RECORD_CHANNEL_INFO");
	}
}
