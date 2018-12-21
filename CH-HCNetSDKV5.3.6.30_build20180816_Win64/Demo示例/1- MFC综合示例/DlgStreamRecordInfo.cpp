// DlgStreamRecordInfo.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgStreamRecordInfo.h"
#include "DlgRemoteStreamRecordSchedule.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgStreamRecordInfo dialog


CDlgStreamRecordInfo::CDlgStreamRecordInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStreamRecordInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgStreamRecordInfo)
	m_strStreamID = _T("");
	m_strRelatedChannel = _T("");
	m_bTimingRecord = TRUE;
	m_bRedundancyRecord = FALSE;
	m_strDurationTime = _T("");
	m_bRecordAudio = FALSE;
	m_strStatus = _T("");
	m_wLockDuration = 0;
	m_bBackup = FALSE;
	m_bPassback = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgStreamRecordInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgStreamRecordInfo)
	DDX_Control(pDX, IDC_CMB_STREAM_TYPE, m_cmbStreamType);
	DDX_Control(pDX, IDC_COMBO_RECORD_DELAY, m_cmbRecordDelay);
	DDX_Control(pDX, IDC_COMBO_PRE_RECORD_TIME, m_cmbPreRecordTime);
	DDX_Control(pDX, IDC_LIST_STREAM_RECORD_INFO, m_lstStreamRecordInfo);
	DDX_Text(pDX, IDC_EDIT_STREAM_ID, m_strStreamID);
	DDX_Text(pDX, IDC_EDIT_RELATEAD_CHANNLE, m_strRelatedChannel);
	DDX_Check(pDX, IDC_CHECK_TIMING_RECORD, m_bTimingRecord);
	DDX_Check(pDX, IDC_CHK_REDUNDANCY_REC, m_bRedundancyRecord);
	DDX_Text(pDX, IDC_EDIT_DURATION_TIME, m_strDurationTime);
	DDX_Check(pDX, IDC_CHECK_RECORD_AUDIO, m_bRecordAudio);
	DDX_Text(pDX, IDC_EDIT_STATUS, m_strStatus);
	DDX_Text(pDX, IDC_EDIT_LOCK_DURATION, m_wLockDuration);
	DDX_Check(pDX, IDC_CHECK_BACKUP, m_bBackup);
	DDX_Check(pDX, IDC_CHECK_CALLBACK, m_bPassback);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgStreamRecordInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgStreamRecordInfo)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAddStreamID)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDelStreamID)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_STREAM_RECORD_INFO, OnDblclkListStreamRecordInfo)
	ON_BN_CLICKED(IDC_BUTTON_TIMING_RECORD_SET, OnButtonTimingRecordSet)
	ON_BN_CLICKED(IDC_CHECK_TIMING_RECORD, OnCheckTimingRecord)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSetStreamRecordInfo)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGetStreamRecordInfo)
	ON_NOTIFY(NM_CLICK, IDC_LIST_STREAM_RECORD_INFO, OnClickListStreamRecordInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgStreamRecordInfo message handlers

BOOL CDlgStreamRecordInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);

	m_cmbPreRecordTime.SetCurSel(0);
	m_cmbRecordDelay.SetCurSel(0);
	m_cmbStreamType.SetCurSel(0);

	for (int i=0; i<64; i++)
	{
		memset(&m_struStreamRecordInfo[i], 0, sizeof(NET_DVR_STREAM_RECORD_INFO));
	}

	m_lstStreamRecordInfo.SetExtendedStyle(m_lstStreamRecordInfo.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	char szLan[128] = {0};
	g_StringLanType(szLan, "序号", "Serial No.");
	m_lstStreamRecordInfo.InsertColumn(0, szLan, LVCFMT_LEFT, 50, -1);
	
	g_StringLanType(szLan, "流ID", "Stream ID");
	m_lstStreamRecordInfo.InsertColumn(1, szLan, LVCFMT_LEFT, 100, -1);
	
	g_StringLanType(szLan, "关联通道", "Related channel");
	m_lstStreamRecordInfo.InsertColumn(2, szLan, LVCFMT_LEFT, 60, -1);
	
	g_StringLanType(szLan, "定时录像", "Timed record");
	m_lstStreamRecordInfo.InsertColumn(3, szLan, LVCFMT_LEFT, 60, -1);
	
	g_StringLanType(szLan, "记录音频", "Record audio");
	m_lstStreamRecordInfo.InsertColumn(4, szLan, LVCFMT_LEFT, 100, -1);
	
	g_StringLanType(szLan, "预录时间", "Pre record time");
	m_lstStreamRecordInfo.InsertColumn(5, szLan, LVCFMT_LEFT, 150, -1);

	g_StringLanType(szLan, "录像延时", "Record delay");
	m_lstStreamRecordInfo.InsertColumn(6, szLan, LVCFMT_LEFT, 100, -1);
	
	g_StringLanType(szLan, "保存天数", "Record duration");
	m_lstStreamRecordInfo.InsertColumn(7, szLan, LVCFMT_LEFT, 150, -1);

	g_StringLanType(szLan, "码流类型", "Stream Type");
	m_lstStreamRecordInfo.InsertColumn(8, szLan, LVCFMT_LEFT, 100, -1);
	
	g_StringLanType(szLan, "主码流抽帧", "Draw frame from main stream");
	m_lstStreamRecordInfo.InsertColumn(9, szLan, LVCFMT_LEFT, 150, -1);
	
	g_StringLanType(szLan, "子码流抽帧", "Draw frame from sub stream");
	m_lstStreamRecordInfo.InsertColumn(10, szLan, LVCFMT_LEFT, 100, -1);

	g_StringLanType(szLan, "冗余录像", "Redundancy record");
	m_lstStreamRecordInfo.InsertColumn(11, szLan, LVCFMT_LEFT, 100, -1);

	g_StringLanType(szLan, "状态", "status");
	m_lstStreamRecordInfo.InsertColumn(12, szLan, LVCFMT_LEFT, 50, -1);

	
	g_StringLanType(szLan, "存档", "Backup");
	m_lstStreamRecordInfo.InsertColumn(13, szLan, LVCFMT_LEFT, 50, -1);
	
	g_StringLanType(szLan, "回传", "Passback");
	m_lstStreamRecordInfo.InsertColumn(14, szLan, LVCFMT_LEFT, 50, -1);
	
	g_StringLanType(szLan, "锁定时长", "LockDuration");
	m_lstStreamRecordInfo.InsertColumn(15, szLan, LVCFMT_LEFT, 50, -1);

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgStreamRecordInfo::OnButtonAddStreamID() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	CString strTemp;

// 	if ("" == m_strStreamID)
// 	{
// 		g_StringLanType(szLan,"流ID为空","Stream ID is NULL");
// 		AfxMessageBox(szLan);
// 		return;
// 	}
		
	int iItemCount = m_lstStreamRecordInfo.GetItemCount();
	if (iItemCount > 64)
	{
		g_StringLanType(szLan,"流ID超过64个","Stream ID is more than 64");
		AfxMessageBox(szLan);
		return;
	}
	strTemp.Format("%02d", iItemCount+1);
	m_lstStreamRecordInfo.InsertItem(iItemCount, strTemp);
	m_lstStreamRecordInfo.SetItemText(iItemCount, 1, m_strStreamID);
	m_lstStreamRecordInfo.SetItemText(iItemCount, 2, m_strRelatedChannel);
	if (TRUE == m_bTimingRecord)
	{
		m_lstStreamRecordInfo.SetItemText(iItemCount, 3, "是");
	}
	else
	{
		m_lstStreamRecordInfo.SetItemText(iItemCount, 3, "否");
	}

	if (TRUE == m_bRecordAudio)
	{
		m_lstStreamRecordInfo.SetItemText(iItemCount, 4, "是");
	}
	else
	{
		m_lstStreamRecordInfo.SetItemText(iItemCount, 4, "否");
	}
	
	m_cmbPreRecordTime.GetWindowText(strTemp);
	m_lstStreamRecordInfo.SetItemText(iItemCount, 5, strTemp);
	m_cmbRecordDelay.GetWindowText(strTemp);
	m_lstStreamRecordInfo.SetItemText(iItemCount, 6, strTemp);
	m_lstStreamRecordInfo.SetItemText(iItemCount, 7, m_strDurationTime);
	
	strTemp.Format("%d", m_cmbStreamType.GetCurSel());
	m_lstStreamRecordInfo.SetItemText(iItemCount, 8, strTemp);

// 	if (TRUE == m_bDrawFrame)
// 	{
// 		m_lstStreamRecordInfo.SetItemText(iItemCount, 8, "是");
// 	}
// 	else
// 	{
// 		m_lstStreamRecordInfo.SetItemText(iItemCount, 8, "否");
// 	}
// 
// 	if (TRUE == m_bDrawFrameFromMain)
// 	{
// 		m_lstStreamRecordInfo.SetItemText(iItemCount, 9, "是");
// 	}
// 	else
// 	{
// 		m_lstStreamRecordInfo.SetItemText(iItemCount, 9, "否");
// 	}
// 
// 	if (TRUE == m_bDrawFrameFromSub)
// 	{
// 		m_lstStreamRecordInfo.SetItemText(iItemCount, 10, "是");
// 	}
// 	else
// 	{
// 		m_lstStreamRecordInfo.SetItemText(iItemCount, 10, "否");
// 	}

	if (TRUE == m_bRedundancyRecord)
	{
		m_lstStreamRecordInfo.SetItemText(iItemCount, 11, "是");
	}
	else
	{
		m_lstStreamRecordInfo.SetItemText(iItemCount, 11, "否");
	}

	strTemp.Format("%d", m_bBackup);
	m_lstStreamRecordInfo.SetItemText(iItemCount, 13, strTemp);

	strTemp.Format("%d", m_bPassback);
	m_lstStreamRecordInfo.SetItemText(iItemCount, 14, strTemp);

	strTemp.Format("%d", m_wLockDuration);
	m_lstStreamRecordInfo.SetItemText(iItemCount, 15, strTemp);




	// 添加了多个id,则用双击list来设置当前id的录像计划
	GetDlgItem(IDC_BUTTON_TIMING_RECORD_SET)->EnableWindow(FALSE);
}

void CDlgStreamRecordInfo::OnButtonDelStreamID() 
{
	// TODO: Add your control notification handler code here
	while(m_lstStreamRecordInfo.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED) != -1)
	{
		int nItem = m_lstStreamRecordInfo.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED);
		m_lstStreamRecordInfo.DeleteItem(nItem);
	}

	int iItemCount = m_lstStreamRecordInfo.GetItemCount();
	if ((0 == iItemCount) && (TRUE == m_bTimingRecord))
	{
		GetDlgItem(IDC_BUTTON_TIMING_RECORD_SET)->EnableWindow(TRUE);
	}
}

void CDlgStreamRecordInfo::OnDblclkListStreamRecordInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iItemCount = m_lstStreamRecordInfo.GetItemCount();
	if (0 == iItemCount)
	{
		return;
	}

	int iRow = m_lstStreamRecordInfo.GetSelectionMark();
	if (0 == strcmp("否", m_lstStreamRecordInfo.GetItemText(iRow, 3)))
	{
		return;
	}

	CDlgRemoteStreamRecordSchedule dlg;
	dlg.m_iDevIndex = g_pMainDlg->GetCurDeviceIndex();
    dlg.m_lServerID = g_struDeviceInfo[dlg.m_iDevIndex].lLoginID;  
    
	
	
	//dlg.m_struRemoteRecSchedule = &(m_struStreamRecordInfo[iRow].struRecordInfo);
	dlg.m_pstruStreamRecordInfo = &m_struStreamRecordInfo[iRow];
	if (dlg.DoModal() == IDOK)
	{
// 		m_bSetChannelPara[m_iCurChanIndex] = TRUE;
// 		g_bMustReboot = g_pMainDlg->IsNeedRebootDevType();
	}
	*pResult = 0;
}

void CDlgStreamRecordInfo::OnButtonTimingRecordSet() 
{
	// TODO: Add your control notification handler code here
	int iItemCount = m_lstStreamRecordInfo.GetItemCount();
	if (0 == iItemCount)
	{
		CDlgRemoteStreamRecordSchedule dlg;
		dlg.m_iDevIndex = g_pMainDlg->GetCurDeviceIndex();
		dlg.m_lServerID = g_struDeviceInfo[dlg.m_iDevIndex].lLoginID;  
			
		dlg.m_pstruStreamRecordInfo = &m_struStreamRecordInfo[0];
		if (dlg.DoModal() == IDOK)
		{
			// 		m_bSetChannelPara[m_iCurChanIndex] = TRUE;
			// 		g_bMustReboot = g_pMainDlg->IsNeedRebootDevType();
		}
	}
}

void CDlgStreamRecordInfo::OnCheckTimingRecord() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (TRUE == m_bTimingRecord)
	{
		GetDlgItem(IDC_BUTTON_TIMING_RECORD_SET)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_TIMING_RECORD_SET)->EnableWindow(FALSE);
	}
	
}

void CDlgStreamRecordInfo::OnButtonSetStreamRecordInfo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    char szLan[128] = {0};

	LPNET_DVR_STREAM_RECORD_INFO pStreamRecordInfo = &m_struStreamRecordInfo[0];
	LPNET_DVR_STREAM_RECORD_INFO pTempRecordInfo = pStreamRecordInfo;
	
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	LONG lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	
	int iItemCount = m_lstStreamRecordInfo.GetItemCount();
	
	LPNET_DVR_STREAM_INFO pstruStreamID = NULL;
	LPNET_DVR_STREAM_INFO pTempStreamID = NULL;
	if (0 == iItemCount)
	{
// 		if ("" == m_strStreamID)
// 		{
// 			g_StringLanType(szLan,"流ID为空","Stream ID is NULL");
// 			AfxMessageBox(szLan);
// 			return;
// 		}
		pstruStreamID = new(std::nothrow) NET_DVR_STREAM_INFO;
		if (NULL == pstruStreamID)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pstruStreamID, 0, sizeof(NET_DVR_STREAM_INFO));
		pstruStreamID->dwSize = sizeof(NET_DVR_STREAM_INFO);
		pstruStreamID->dwChannel = atoi(m_strRelatedChannel);
		strncpy((char*)pstruStreamID->byID, m_strStreamID, STREAM_ID_LEN);

		pStreamRecordInfo->dwSize = sizeof(NET_DVR_STREAM_RECORD_INFO);
		pStreamRecordInfo->struRecordInfo.byAudioRec = m_bRecordAudio;
 		pStreamRecordInfo->struRecordInfo.byStreamType = m_cmbStreamType.GetCurSel();
		pStreamRecordInfo->struRecordInfo.byRedundancyRec = m_bRedundancyRecord;
		pStreamRecordInfo->struRecordInfo.dwPreRecordTime = m_cmbPreRecordTime.GetCurSel();
		pStreamRecordInfo->struRecordInfo.dwRecord = m_bTimingRecord;
		pStreamRecordInfo->struRecordInfo.dwRecorderDuration = atoi(m_strDurationTime);
		pStreamRecordInfo->struRecordInfo.dwRecordTime = m_cmbRecordDelay.GetCurSel();
		pStreamRecordInfo->struRecordInfo.byPassbackRecord = m_bPassback;
		pStreamRecordInfo->struRecordInfo.wLockDuration = m_wLockDuration;
		pStreamRecordInfo->struRecordInfo.byRecordBackup = m_bBackup;
		
		DWORD dwStatus = 0;
		BOOL bRet = NET_DVR_SetDeviceConfig(lLoginID, NET_DVR_SET_STREAM_RECORD_INFO, iItemCount, pstruStreamID, sizeof(NET_DVR_STREAM_INFO), &dwStatus, pStreamRecordInfo, sizeof(NET_DVR_STREAM_RECORD_INFO));	
	
		if (bRet && (0 == dwStatus))
		{
			g_StringLanType(szLan,"设置流录像信息成功","Success");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "succeed to set Stream record information");
			AfxMessageBox(szLan);
		}
		else
		{        
			g_StringLanType(szLan,"设置流录像信息失败","Fail to set stream record information");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Fail to set stream record information");
			AfxMessageBox(szLan);
		}

		m_strStatus.Format("%d", dwStatus);
	}
	else
	{
		// 申请iItemCount个NET_DVR_STREAM_INFO
		pstruStreamID = new(std::nothrow) NET_DVR_STREAM_INFO[iItemCount];
		if (NULL == pstruStreamID)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pstruStreamID, 0, iItemCount*sizeof(NET_DVR_STREAM_INFO));
		pTempStreamID = pstruStreamID;

		int i = 0; 
		for (i=0; i<iItemCount; i++)
		{
		 	pTempStreamID->dwSize = sizeof(NET_DVR_STREAM_INFO);
			strncpy((char*)pTempStreamID->byID, m_lstStreamRecordInfo.GetItemText(i, 1), STREAM_ID_LEN);
		 	pTempStreamID->dwChannel = atoi(m_lstStreamRecordInfo.GetItemText(i, 2));
		 	
			pTempRecordInfo->dwSize = sizeof(NET_DVR_STREAM_RECORD_INFO);
			if (0 == strcmp("是", m_lstStreamRecordInfo.GetItemText(i, 3)))
			{
				pTempRecordInfo->struRecordInfo.dwRecord = 1;
			}
			else
			{
				pTempRecordInfo->struRecordInfo.dwRecord = 0;
			}

			if (0 == strcmp("是", m_lstStreamRecordInfo.GetItemText(i, 4)))
			{
				pTempRecordInfo->struRecordInfo.byAudioRec = 1;
			}
			else
			{
				pTempRecordInfo->struRecordInfo.byAudioRec = 0;
			}

			if (0 == strcmp("不预录", m_lstStreamRecordInfo.GetItemText(i, 5)))
			{
				pTempRecordInfo->struRecordInfo.dwPreRecordTime = 0;
			}
			else if(0 == strcmp("5秒", m_lstStreamRecordInfo.GetItemText(i, 5)))
			{
				pTempRecordInfo->struRecordInfo.dwPreRecordTime = 1;
			}
			else if(0 == strcmp("10秒", m_lstStreamRecordInfo.GetItemText(i, 5)))
			{
				pTempRecordInfo->struRecordInfo.dwPreRecordTime = 2;
			}
			else if(0 == strcmp("15秒", m_lstStreamRecordInfo.GetItemText(i, 5)))
			{
				pTempRecordInfo->struRecordInfo.dwPreRecordTime = 3;
			}
			else if(0 == strcmp("20秒", m_lstStreamRecordInfo.GetItemText(i, 5)))
			{
				pTempRecordInfo->struRecordInfo.dwPreRecordTime = 4;
			}
			else if(0 == strcmp("25秒", m_lstStreamRecordInfo.GetItemText(i, 5)))
			{
				pTempRecordInfo->struRecordInfo.dwPreRecordTime = 5;
			}
			else if(0 == strcmp("30秒", m_lstStreamRecordInfo.GetItemText(i, 5)))
			{
				pTempRecordInfo->struRecordInfo.dwPreRecordTime = 6;
			}
			else
			{
				pTempRecordInfo->struRecordInfo.dwPreRecordTime = 7;
			}

			if (0 == strcmp("5秒", m_lstStreamRecordInfo.GetItemText(i, 6)))
			{
				pTempRecordInfo->struRecordInfo.dwRecordTime = 0;
			}
			else if(0 == strcmp("10秒", m_lstStreamRecordInfo.GetItemText(i, 6)))
			{
				pTempRecordInfo->struRecordInfo.dwRecordTime = 1;
			}
			else if(0 == strcmp("30秒", m_lstStreamRecordInfo.GetItemText(i, 6)))
			{
				pTempRecordInfo->struRecordInfo.dwRecordTime = 2;
			}
			else if(0 == strcmp("1分钟", m_lstStreamRecordInfo.GetItemText(i, 6)))
			{
				pTempRecordInfo->struRecordInfo.dwRecordTime = 3;
			}
			else if(0 == strcmp("2分钟", m_lstStreamRecordInfo.GetItemText(i, 6)))
			{
				pTempRecordInfo->struRecordInfo.dwRecordTime = 4;
			}
			else if(0 == strcmp("5分钟", m_lstStreamRecordInfo.GetItemText(i, 6)))
			{
				pTempRecordInfo->struRecordInfo.dwRecordTime = 5;
			}
			else
			{
				pTempRecordInfo->struRecordInfo.dwRecordTime = 6;
			}

			pTempRecordInfo->struRecordInfo.dwRecorderDuration = atoi(m_lstStreamRecordInfo.GetItemText(i, 7));

// 			if (0 == strcmp("是", m_lstStreamRecordInfo.GetItemText(i, 8)))
// 			{
// 				pTempRecordInfo->struRecordInfo.byRecDrawnFrame = 1;
// 			}
// 			else
// 			{
// 				pTempRecordInfo->struRecordInfo.byRecDrawnFrame = 0;
// 			}
// 
// 			if (0 == strcmp("是", m_lstStreamRecordInfo.GetItemText(i, 9)))
// 			{
// 				pTempRecordInfo->struRecordInfo.byNetMainDrawnFrame = 1;
// 			}
// 			else
// 			{
// 				pTempRecordInfo->struRecordInfo.byNetMainDrawnFrame = 0;
// 			}
// 
// 			if (0 == strcmp("是", m_lstStreamRecordInfo.GetItemText(i, 10)))
// 			{
// 				pTempRecordInfo->struRecordInfo.byNetSubDrawnFrame = 1;
// 			}
// 			else
// 			{
// 				pTempRecordInfo->struRecordInfo.byNetSubDrawnFrame = 0;
// 			}

			pTempRecordInfo->struRecordInfo.byStreamType = atoi(m_lstStreamRecordInfo.GetItemText(i, 8));

			if (0 == strcmp("是", m_lstStreamRecordInfo.GetItemText(i, 11)))
			{
				pTempRecordInfo->struRecordInfo.byRedundancyRec = 1;
			}
			else
			{
				pTempRecordInfo->struRecordInfo.byRedundancyRec = 0;
			}

			pTempRecordInfo->struRecordInfo.byRecordBackup = atoi(m_lstStreamRecordInfo.GetItemText(i, 13));
			pTempRecordInfo->struRecordInfo.byPassbackRecord = atoi(m_lstStreamRecordInfo.GetItemText(i, 14));
			pTempRecordInfo->struRecordInfo.wLockDuration = atoi(m_lstStreamRecordInfo.GetItemText(i, 15));
	
			pTempStreamID++;
			pTempRecordInfo++;
		}

		DWORD *pStatus = new DWORD[iItemCount];
		memset(pStatus, 0, sizeof(DWORD)*iItemCount);

		if (NET_DVR_SetDeviceConfig(lLoginID, NET_DVR_SET_STREAM_RECORD_INFO, iItemCount, pstruStreamID, iItemCount*sizeof(NET_DVR_STREAM_INFO), pStatus, pStreamRecordInfo, iItemCount*sizeof(NET_DVR_STREAM_RECORD_INFO)))
		{
			g_StringLanType(szLan,"批量设置流录像信息成功","Succeed to set stream record information");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "Set Stream record information");
			AfxMessageBox(szLan);
		}
		else
		{        
			g_StringLanType(szLan,"批量设置流录像信息失败","Fail to set stream record information");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Fail to set stream record information");
			AfxMessageBox(szLan);
		}

		for (i=0; i<iItemCount; i++)
		{
			CString strStatus;
			strStatus.Format("%d", *pStatus);
			m_lstStreamRecordInfo.SetItemText(i, 12, strStatus);
			pStatus++;
		}
	}

	UpdateData(FALSE);
}

void CDlgStreamRecordInfo::OnButtonGetStreamRecordInfo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    char szLan[128] = {0};
	DWORD dwReturn = 0;
	CString strTemp;

	LPNET_DVR_STREAM_RECORD_INFO pStreamRecordInfo = &m_struStreamRecordInfo[0];

	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	LONG lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	
	int iItemCount = m_lstStreamRecordInfo.GetItemCount();
	
	LPNET_DVR_STREAM_INFO pstruStreamID = NULL;
	LPNET_DVR_STREAM_INFO pTempStreamID = NULL;
	if (0 == iItemCount)
	{
// 		if ("" == m_strStreamID)
// 		{
// 			g_StringLanType(szLan,"流ID为空","Stream ID is NULL");
// 			AfxMessageBox(szLan);
// 			return;
// 		}
		pstruStreamID = new(std::nothrow) NET_DVR_STREAM_INFO;
		if (NULL == pstruStreamID)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pstruStreamID, 0, sizeof(NET_DVR_STREAM_INFO));
		pstruStreamID->dwSize = sizeof(NET_DVR_STREAM_INFO);
		pstruStreamID->dwChannel = atoi(m_strRelatedChannel);
		strncpy((char*)pstruStreamID->byID, m_strStreamID, STREAM_ID_LEN);

		// 返回的状态
		DWORD dwStatus = 0;

		BOOL bRet = NET_DVR_GetDeviceConfig(lLoginID, NET_DVR_GET_STREAM_RECORD_INFO, iItemCount, pstruStreamID, sizeof(NET_DVR_STREAM_INFO), &dwStatus, pStreamRecordInfo, sizeof(NET_DVR_STREAM_RECORD_INFO));


		if (bRet && (0 == dwStatus))
		{
			g_StringLanType(szLan,"获取流录像信息成功","Get stream record information success");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "Get stream record information success");
			AfxMessageBox(szLan);
		}
		else
		{        
			g_StringLanType(szLan,"获取流录像信息失败","Fail to Get stream record information");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Fail to set stream record information");
			AfxMessageBox(szLan);
			return;
		}

		m_bTimingRecord = pStreamRecordInfo->struRecordInfo.dwRecord;
		m_bRecordAudio = pStreamRecordInfo->struRecordInfo.byAudioRec;
		m_cmbPreRecordTime.SetCurSel(pStreamRecordInfo->struRecordInfo.dwPreRecordTime);
		m_cmbRecordDelay.SetCurSel(pStreamRecordInfo->struRecordInfo.dwRecordTime);
		m_strDurationTime.Format("%d", pStreamRecordInfo->struRecordInfo.dwRecorderDuration);
		m_cmbStreamType.SetCurSel(pStreamRecordInfo->struRecordInfo.byStreamType);
// 		m_bDrawFrame = pStreamRecordInfo->struRecordInfo.byRecDrawnFrame;
// 		m_bDrawFrameFromMain = pStreamRecordInfo->struRecordInfo.byNetMainDrawnFrame;
// 		m_bDrawFrameFromSub = pStreamRecordInfo->struRecordInfo.byNetSubDrawnFrame;
		m_bRedundancyRecord = pStreamRecordInfo->struRecordInfo.byRedundancyRec;
		m_bBackup = pStreamRecordInfo->struRecordInfo.byRecordBackup;
		m_bPassback = pStreamRecordInfo->struRecordInfo.byPassbackRecord;
		m_wLockDuration = pStreamRecordInfo->struRecordInfo.wLockDuration;

		GetDlgItem(IDC_BUTTON_TIMING_RECORD_SET)->EnableWindow(m_bTimingRecord);

		m_strStatus.Format("%d", dwStatus);
	}
	else
	{
		// 申请iItemCount个NET_DVR_STREAM_INFO
		pstruStreamID = new(std::nothrow) NET_DVR_STREAM_INFO[iItemCount];
		if (NULL == pstruStreamID)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pstruStreamID, 0, iItemCount*sizeof(NET_DVR_STREAM_INFO));
		pTempStreamID = pstruStreamID;

		DWORD *pStatus = new DWORD[iItemCount];
		memset(pStatus, 0, sizeof(DWORD)*iItemCount);

		int i = 0; 
		for (i=0; i<iItemCount; i++)
		{
		 	pTempStreamID->dwSize = sizeof(NET_DVR_STREAM_INFO);
			strncpy((char*)pTempStreamID->byID, m_lstStreamRecordInfo.GetItemText(i, 1), STREAM_ID_LEN);
		 	pTempStreamID->dwChannel = atoi(m_lstStreamRecordInfo.GetItemText(i, 2));
			pTempStreamID++;
		}

		
		if (NET_DVR_GetDeviceConfig(lLoginID, NET_DVR_GET_STREAM_RECORD_INFO, iItemCount, pstruStreamID, iItemCount*sizeof(NET_DVR_STREAM_INFO), pStatus, pStreamRecordInfo, iItemCount*sizeof(NET_DVR_STREAM_RECORD_INFO)))
		{
			g_StringLanType(szLan,"批量获取流录像信息成功","Get stream record information success");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "Get Stream record information");
			AfxMessageBox(szLan);
		}
		else
		{
			delete pStatus;
			g_StringLanType(szLan,"批量获取流录像信息失败","Fail to get stream record information");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Fail to get stream record information");
			AfxMessageBox(szLan);
			return;
		}

		for (i=0; i<iItemCount; i++)
		{
// 			m_bTimingRecord = pStreamRecordInfo->struRecordInfo.dwRecord;
// 			m_bRecordAudio = pStreamRecordInfo->struRecordInfo.byAudioRec;
// 			m_cmbPreRecordTime.SetCurSel(pStreamRecordInfo->struRecordInfo.dwPreRecordTime);
// 			m_cmbRecordDelay.SetCurSel(pStreamRecordInfo->struRecordInfo.dwRecordTime);
// 			m_strDurationTime.Format("%d", pStreamRecordInfo->struRecordInfo.dwRecorderDuration);
//  		m_bRedundancyRecord = pStreamRecordInfo->struRecordInfo.byRedundancyRec;


			if (1 == pStreamRecordInfo->struRecordInfo.dwRecord)
			{
				m_lstStreamRecordInfo.SetItemText(i, 3, "是");
			}
			else
			{
				m_lstStreamRecordInfo.SetItemText(i, 3, "否");
			}

			if (1 == pStreamRecordInfo->struRecordInfo.byAudioRec)
			{
				m_lstStreamRecordInfo.SetItemText(i, 4, "是");
			}
			else
			{
				m_lstStreamRecordInfo.SetItemText(i, 4, "否");
			}

			m_cmbPreRecordTime.GetLBText(pStreamRecordInfo->struRecordInfo.dwPreRecordTime, strTemp);
			m_lstStreamRecordInfo.SetItemText(i, 5, strTemp);

			m_cmbRecordDelay.GetLBText(pStreamRecordInfo->struRecordInfo.dwRecordTime, strTemp);
			m_lstStreamRecordInfo.SetItemText(i, 6, strTemp);

			strTemp.Format("%d", pStreamRecordInfo->struRecordInfo.dwRecorderDuration);
			m_lstStreamRecordInfo.SetItemText(i, 7, strTemp);

			strTemp.Format("%d", pStreamRecordInfo->struRecordInfo.byStreamType);
			m_lstStreamRecordInfo.SetItemText(i, 8, strTemp);

// 			if (1 == pStreamRecordInfo->struRecordInfo.byRecDrawnFrame)
// 			{
// 				m_lstStreamRecordInfo.SetItemText(i, 8, "是");
// 			}
// 			else
// 			{
// 				m_lstStreamRecordInfo.SetItemText(i, 8, "否");
// 			}
// 
// 			if (1 == pStreamRecordInfo->struRecordInfo.byNetMainDrawnFrame)
// 			{
// 				m_lstStreamRecordInfo.SetItemText(i, 9, "是");
// 			}
// 			else
// 			{
// 				m_lstStreamRecordInfo.SetItemText(i, 9, "否");
// 			}
// 
// 			if (1 == pStreamRecordInfo->struRecordInfo.byNetSubDrawnFrame)
// 			{
// 				m_lstStreamRecordInfo.SetItemText(i, 10, "是");
// 			}
// 			else
// 			{
// 				m_lstStreamRecordInfo.SetItemText(i, 10, "否");
// 			}
			
			if (1 == pStreamRecordInfo->struRecordInfo.byRedundancyRec)
			{
				m_lstStreamRecordInfo.SetItemText(i, 11, "是");
			}
			else
			{
				m_lstStreamRecordInfo.SetItemText(i, 11, "否");
			}

			CString strStatus;
			strStatus.Format("%d", *pStatus);
			m_lstStreamRecordInfo.SetItemText(i, 12, strStatus);

			CString strTemp;
			strTemp.Format("%d", pStreamRecordInfo->struRecordInfo.byRecordBackup);
			m_lstStreamRecordInfo.SetItemText(i, 13, strTemp);
			
			strTemp.Format("%d", pStreamRecordInfo->struRecordInfo.byPassbackRecord);
			m_lstStreamRecordInfo.SetItemText(i, 14, strTemp);
			
			strTemp.Format("%d", pStreamRecordInfo->struRecordInfo.wLockDuration);
			m_lstStreamRecordInfo.SetItemText(i, 15, strTemp);
			
			pStatus++;
			pStreamRecordInfo++;
		}
	}

	UpdateData(FALSE);
}

void CDlgStreamRecordInfo::OnClickListStreamRecordInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nItem = 0;
	CString strChannel;
	
	POSITION pos = m_lstStreamRecordInfo.GetFirstSelectedItemPosition();
	if (pos == NULL)
		TRACE0("No items were selected!\n");
	else
	{
		nItem = m_lstStreamRecordInfo.GetNextSelectedItem(pos);
		
		//显示信息
		m_strStreamID = m_lstStreamRecordInfo.GetItemText(nItem, 1);
		m_strRelatedChannel = m_lstStreamRecordInfo.GetItemText(nItem, 2);
		if (0 == strcmp("是", m_lstStreamRecordInfo.GetItemText(nItem, 3)))
		{
			m_bTimingRecord = TRUE;
		}
		else
		{
			m_bTimingRecord = FALSE;
		}

		if (0 == strcmp("是", m_lstStreamRecordInfo.GetItemText(nItem, 4)))
		{
			m_bRecordAudio = TRUE;
		}
		else
		{
			m_bRecordAudio = FALSE;
		}
		
		m_cmbPreRecordTime.SetWindowText(m_lstStreamRecordInfo.GetItemText(nItem, 5));
		
		m_cmbRecordDelay.SetWindowText(m_lstStreamRecordInfo.GetItemText(nItem, 6));

		m_strDurationTime = m_lstStreamRecordInfo.GetItemText(nItem, 7);
	
		m_cmbStreamType.SetCurSel(atoi(m_lstStreamRecordInfo.GetItemText(nItem, 8)));

// 		if (0 == strcmp("是", m_lstStreamRecordInfo.GetItemText(nItem, 8)))
// 		{
// 			m_bDrawFrame = TRUE;
// 		}
// 		else
// 		{
// 			m_bDrawFrame = FALSE;
// 		}
// 		
// 		if (0 == strcmp("是", m_lstStreamRecordInfo.GetItemText(nItem, 9)))
// 		{
// 			m_bDrawFrameFromMain = TRUE;
// 		}
// 		else
// 		{
// 			m_bDrawFrameFromMain = FALSE;
// 		}
// 
// 		if (0 == strcmp("是", m_lstStreamRecordInfo.GetItemText(nItem, 10)))
// 		{
// 			m_bDrawFrameFromSub = TRUE;
// 		}
// 		else
// 		{
// 			m_bDrawFrameFromSub = FALSE;
// 		}
		
		if (0 == strcmp("是", m_lstStreamRecordInfo.GetItemText(nItem, 11)))
		{
			m_bRedundancyRecord = TRUE;
		}
		else
		{
			m_bRedundancyRecord = FALSE;
		}

		m_strStatus = m_lstStreamRecordInfo.GetItemText(nItem, 12);

		m_bBackup = atoi(m_lstStreamRecordInfo.GetItemText(nItem, 13));
		m_bPassback = atoi(m_lstStreamRecordInfo.GetItemText(nItem, 14));
		m_wLockDuration = atoi(m_lstStreamRecordInfo.GetItemText(nItem, 15));

		UpdateData(FALSE);
	}
	*pResult = 0;
}
