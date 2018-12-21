// DlgITSWorkState.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgITSWorkState.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgITSWorkState dialog


CDlgITSWorkState::CDlgITSWorkState(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgITSWorkState::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgITSWorkState)
	m_csHostIP = _T("");
	m_dwCpuUsage = 0;
	m_dwDataTotal = 0;
	m_dwDevTemp = 0;
	m_csDeviceName = _T("");
	m_dwEndDay = 0;
	m_dwEndHour = 0;
	m_dwEndMilliSec = 0;
	m_dwEndMinute = 0;
	m_dwEndMonth = 0;
	m_dwEndSec = 0;
	m_dwEndYear = 0;
	m_dwMemoryUsage = 0;
	m_dwNeedSendData = 0;
	m_dwRunTime = 0;
	m_dwStartDay = 0;
	m_dwStartHour = 0;
	m_dwStartMilliSec = 0;
	m_dwStartMinute = 0;
	m_dwStartMonth = 0;
	m_dwStartSec = 0;
	m_dwStartYear = 0;
	m_csDeviceState = _T("");
	//}}AFX_DATA_INIT
	m_iHostSel = 0;
}


void CDlgITSWorkState::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgITSWorkState)
	DDX_Control(pDX, IDC_COMBO_DEVICE_CHANNEL, m_comboDevChan);
	DDX_Control(pDX, IDC_LIST_ALARM_OUT_STATE, m_listAlarmOutState);
	DDX_Control(pDX, IDC_LIST_ALARM_IN_STATE, m_listAlarmInState);
	DDX_Control(pDX, IDC_COMBO_LOCAL_DISPLAY_STATE, m_comboLocalDisplay);
	DDX_Control(pDX, IDC_COMBO_HOST, m_comboHostIndex);
	DDX_Control(pDX, IDC_LIST_DISK_STATE, m_listDiskState);
	DDX_Control(pDX, IDC_LIST_CHAN_STATE, m_listChanState);
	DDX_Text(pDX, IDC_EDIT_HOST_IP, m_csHostIP);
	DDX_Text(pDX, IDC_EDIT_CPU_USAGE, m_dwCpuUsage);
	DDX_Text(pDX, IDC_EDIT_DATA_TOTAL, m_dwDataTotal);
	DDX_Text(pDX, IDC_EDIT_DEV_TEMP, m_dwDevTemp);
	DDX_Text(pDX, IDC_EDIT_DEVICE_NAME, m_csDeviceName);
	DDX_Text(pDX, IDC_EDIT_END_TIME_DAY, m_dwEndDay);
	DDX_Text(pDX, IDC_EDIT_END_TIME_HOUR, m_dwEndHour);
	DDX_Text(pDX, IDC_EDIT_END_TIME_MILLISEC, m_dwEndMilliSec);
	DDX_Text(pDX, IDC_EDIT_END_TIME_MINUTE, m_dwEndMinute);
	DDX_Text(pDX, IDC_EDIT_END_TIME_MONTH, m_dwEndMonth);
	DDX_Text(pDX, IDC_EDIT_END_TIME_SECOND, m_dwEndSec);
	DDX_Text(pDX, IDC_EDIT_END_TIME_YEAR, m_dwEndYear);
	DDX_Text(pDX, IDC_EDIT_MEMORY_USAGE, m_dwMemoryUsage);
	DDX_Text(pDX, IDC_EDIT_NEED_SEND_DATA, m_dwNeedSendData);
	DDX_Text(pDX, IDC_EDIT_RUNTIME, m_dwRunTime);
	DDX_Text(pDX, IDC_EDIT_START_TIME_DAY, m_dwStartDay);
	DDX_Text(pDX, IDC_EDIT_START_TIME_HOUR, m_dwStartHour);
	DDX_Text(pDX, IDC_EDIT_START_TIME_MILLISEC, m_dwStartMilliSec);
	DDX_Text(pDX, IDC_EDIT_START_TIME_MINUTE, m_dwStartMinute);
	DDX_Text(pDX, IDC_EDIT_START_TIME_MONTH, m_dwStartMonth);
	DDX_Text(pDX, IDC_EDIT_START_TIME_SECOND, m_dwStartSec);
	DDX_Text(pDX, IDC_EDIT_START_TIME_YEAR, m_dwStartYear);
	DDX_Text(pDX, IDC_STATIC_DEVSTATE, m_csDeviceState);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgITSWorkState, CDialog)
	//{{AFX_MSG_MAP(CDlgITSWorkState)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_CBN_SELCHANGE(IDC_COMBO_HOST, OnSelchangeComboHost)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgITSWorkState message handlers
BOOL CDlgITSWorkState::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow();
	char szLan[128] = {0};
	g_StringLanType(szLan, "通道号", "Chan No.");
	m_listChanState.InsertColumn(0, szLan, LVCFMT_LEFT, 90, -1);
	g_StringLanType(szLan, "录像状态", "Record Status");
	m_listChanState.InsertColumn(1, szLan, LVCFMT_LEFT, 100, -1);
	g_StringLanType(szLan, "信号状态", "Signal Status");
	m_listChanState.InsertColumn(2, szLan, LVCFMT_LEFT, 100, -1);
	g_StringLanType(szLan, "硬件状态", "Hardware Status");
	m_listChanState.InsertColumn(3, szLan, LVCFMT_LEFT, 100, -1);
	g_StringLanType(szLan, "连接数", "Link Nums");
	m_listChanState.InsertColumn(4, szLan, LVCFMT_LEFT, 100, -1);
	g_StringLanType(szLan, "当前码率(bps)", "Current Bitrate(bps)");
	m_listChanState.InsertColumn(5, szLan,LVCFMT_LEFT,110, -1);
	g_StringLanType(szLan, "客户端", "Client IP");
	m_listChanState.InsertColumn(6, szLan,LVCFMT_LEFT,80, -1);
	g_StringLanType(szLan, "IPC链接数", "IPC link No.");
	m_listChanState.InsertColumn(7, szLan,LVCFMT_LEFT,80, -1);
	
	g_StringLanType(szLan, "硬盘号", "HD No.");
	m_listDiskState.InsertColumn(0, szLan, LVCFMT_LEFT, 90, -1);
	g_StringLanType(szLan, "硬盘容量(MB)", "HD Capacity");
	m_listDiskState.InsertColumn(1, szLan, LVCFMT_LEFT, 130, -1);
	g_StringLanType(szLan, "剩余空间(MB)", "Last Capacity");
	m_listDiskState.InsertColumn(2, szLan, LVCFMT_LEFT, 130, -1);
	g_StringLanType(szLan, "硬盘状态", "HD Status");
	m_listDiskState.InsertColumn(3, szLan, LVCFMT_LEFT,250,-1);
	
	m_listChanState.SetExtendedStyle(m_listChanState.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_listDiskState.SetExtendedStyle(m_listDiskState.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	m_comboDevChan.SetCurSel(0);
	CheckInitParam();


	return TRUE;
}

void CDlgITSWorkState::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int i = 0;
	int iIndex = 0;
	int iTotalLen = 0;
	CString strDiskNum = _T("");
	CString strChanNum = _T("");
	CString strTemp = _T("");
	char szLan[1024] = {0};
	DWORD dwStatus = 0;
	DWORD dwChannel;
	char szTemp[17] = {0};

	m_listChanState.DeleteAllItems();
	m_listDiskState.DeleteAllItems();

	if (m_comboDevChan.GetCurSel() == 0)
	{
		dwChannel = 0xffffffff;
	}
	else
	{
		dwChannel = m_comboDevChan.GetCurSel();
	}
	
	memset(&m_struWorkState, 0, sizeof(NET_ITS_WORKSTATE));
	if (!NET_DVR_GetDeviceStatus(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_ITS_GET_WORKSTATE, 1, &dwChannel,4,&dwStatus,&m_struWorkState,sizeof(m_struWorkState)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetDeviceStatus");
		g_StringLanType(szLan, "获取ITS设备状态失败!", "Get ITS Device Status Err!");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetDeviceStatus");
		g_StringLanType(szLan, "获取ITS设备状态成功!", "Get ITS Device Status Succ!");
		AfxMessageBox(szLan);
	}

	m_iHostSel = 0;
	m_comboHostIndex.SetCurSel(0);
	memcpy(szLan,m_struWorkState.byDevName, 32);
	m_csDeviceName.Format(szLan);
	m_dwRunTime = m_struWorkState.dwRunTime;
	m_dwMemoryUsage = m_struWorkState.dwMemoryUsage;
	m_dwCpuUsage = m_struWorkState.dwCpuUsage;
	m_dwDevTemp = m_struWorkState.dwDevTemperature;
	m_comboLocalDisplay.SetCurSel(m_struWorkState.dwLocalDisplay);

	m_dwDataTotal = m_struWorkState.struTrafficDataInfo[m_iHostSel].dwDataQuantity;
	m_dwNeedSendData = m_struWorkState.struTrafficDataInfo[m_iHostSel].dwDataRsendQuantity;
	memcpy(szTemp,m_struWorkState.struTrafficDataInfo[m_iHostSel].struDataHost.sIpV4,16);
	m_csHostIP.Format(szTemp);
	m_dwStartYear = m_struWorkState.struTrafficDataInfo[m_iHostSel].struStartTime.wYear;
	m_dwStartMonth = m_struWorkState.struTrafficDataInfo[m_iHostSel].struStartTime.wMonth;
	m_dwStartDay = m_struWorkState.struTrafficDataInfo[m_iHostSel].struStartTime.wDay;
	m_dwStartHour = m_struWorkState.struTrafficDataInfo[m_iHostSel].struStartTime.wHour;
	m_dwStartMinute = m_struWorkState.struTrafficDataInfo[m_iHostSel].struStartTime.wMinute;
	m_dwStartSec = m_struWorkState.struTrafficDataInfo[m_iHostSel].struStartTime.wSecond;
	m_dwEndYear = m_struWorkState.struTrafficDataInfo[m_iHostSel].struEndTime.wYear;
	m_dwEndMonth = m_struWorkState.struTrafficDataInfo[m_iHostSel].struEndTime.wMonth;
	m_dwEndDay = m_struWorkState.struTrafficDataInfo[m_iHostSel].struEndTime.wDay;
	m_dwEndHour = m_struWorkState.struTrafficDataInfo[m_iHostSel].struEndTime.wHour;
	m_dwEndMinute = m_struWorkState.struTrafficDataInfo[m_iHostSel].struEndTime.wMinute;
	m_dwEndSec = m_struWorkState.struTrafficDataInfo[m_iHostSel].struEndTime.wSecond;

	switch (m_struWorkState.dwDeviceStatic) 
	{
	case 0:
		g_StringLanType(szLan, "正常", "Normal");
		m_csDeviceState.Format(szLan);
		break;
	case 1:
		g_StringLanType(szLan, "CPU占用率太高,超过85%", "CPU occupancy rate is too high");
		m_csDeviceState.Format(szLan);
		break;
	case 2:
		g_StringLanType(szLan, "硬件错误", "Hardware error");
		m_csDeviceState.Format(szLan);
		break;
	default:
		//ASSERT(m_struWorkState.dwDeviceStatic < 3);
		break;
	}

	GetDlgItem(IDC_STATIC_DEVSTATE)->SetWindowText(m_csDeviceState);

// 	if (0 == m_struWorkState.byAudioChanStatus[0])
// 	{
// 	}
// 	else if (1 == m_struWorkState.byAudioChanStatus[0])
// 	{
// 	}

	//monitoring point state
	for (i = 0; i < MAX_CHANNUM_V40; i++)  //
	{
		if (!g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].bEnable)
		{
			continue;
		}

		strChanNum.Format("%s", g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].chChanName);	

		if (0 == m_struWorkState.struChanStatic[i].byRecordStatic)
		{
			g_StringLanType(szLan, "不录像", "Not Record");
			m_csRecState.Format(szLan);
		}
		else if (1 == m_struWorkState.struChanStatic[i].byRecordStatic)
		{
			g_StringLanType(szLan, "录像", "Record");
			m_csRecState.Format(szLan);
		}

		if (0 == m_struWorkState.struChanStatic[i].bySignalStatic)
		{
			g_StringLanType(szLan, "正常", "Normal");
			m_csSignalState.Format(szLan);
		}
		else if (1 == m_struWorkState.struChanStatic[i].bySignalStatic)
		{
			g_StringLanType(szLan, "信号丢失", "Signal loss");
			m_csSignalState.Format(szLan);
		}

		if ( 0 == m_struWorkState.struChanStatic[i].byHardwareStatic)
		{
			g_StringLanType(szLan, "正常", "Normal");
			m_csHardWareState.Format(szLan);
		}
		else if (1 == m_struWorkState.struChanStatic[i].byHardwareStatic)
		{
			g_StringLanType(szLan, "异常", "Abnormal");
			m_csHardWareState.Format(szLan);
		}

		m_csLinkCount.Format("%d", m_struWorkState.struChanStatic[i].dwLinkNum);
		iTotalLen+=m_struWorkState.struChanStatic[i].dwLinkNum;
		m_csBitrate.Format("%ld", m_struWorkState.struChanStatic[i].dwBitRate);
		//strTemp.Format("%d", );
		m_listChanState.InsertItem(iIndex, strChanNum, 0);
		m_listChanState.SetItemText(iIndex, 1, m_csRecState);
		m_listChanState.SetItemText(iIndex, 2, m_csSignalState);
		m_listChanState.SetItemText(iIndex, 3, m_csHardWareState);
		m_listChanState.SetItemText(iIndex, 4, m_csLinkCount);
		m_listChanState.SetItemText(iIndex, 5, m_csBitrate);
		m_listChanState.SetItemText(iIndex, 6, m_struWorkState.struChanStatic[i].struClientIP[0].sIpV4);
		strTemp.Format("%d", m_struWorkState.struChanStatic[i].dwIPLinkNum);
		m_listChanState.SetItemText(iIndex, 7, strTemp);
		iIndex++;
	}

	//disk state
	for (i = 0; i < MAX_DISKNUM_V30; i++)
	{
		g_StringLanType(szLan, "硬盘", "HD");
		strDiskNum.Format("%s%02d", szLan, i+1);

		m_csDiskVolume.Format("%ld", m_struWorkState.struHardDiskStatic[i].dwVolume);
		m_csDiskFreeSpace.Format("%ld", m_struWorkState.struHardDiskStatic[i].dwFreeSpace);

		if (m_struWorkState.struHardDiskStatic[i].dwVolume != 0)
		{
			switch (m_struWorkState.struHardDiskStatic[i].dwHardDiskStatic) 
			{
			case 0:
				g_StringLanType(szLan, "活动", "Active");
				m_csDiskState.Format(szLan);
				break;
			case 1:
				g_StringLanType(szLan, "休眠", "Dormancy");
				m_csDiskState.Format(szLan);
				break;
			case 2:
				g_StringLanType(szLan, "不正常", "Abnormal");
				m_csDiskState.Format(szLan);
				m_csDiskState.Format("%s", "不正常");
				break;
 			case 3:		
 				g_StringLanType(szLan, "休眠且不正常", "Dormancy and Abnormal");
 				m_csDiskState.Format(szLan);
 				break;
			case 4:
				g_StringLanType(szLan, "未格式化", "Not Format");
				m_csDiskState.Format(szLan);
 				break;
			case 5:
				g_StringLanType(szLan, "未连接(网络硬盘)", "Not Connect(Net Disk)");
				m_csDiskState.Format(szLan);
 				break;
			case 6:
				g_StringLanType(szLan, "正在格式化", "Being Formating");
				m_csDiskState.Format(szLan);
 				break;
			default:
// 				ASSERT(m_struWorkState.struHardDiskStatic[i].dwHardDiskStatic >= 0 &&\
// 					m_struWorkState.struHardDiskStatic[i].dwHardDiskStatic < 4);
				break;
			}
		}else
		{
			m_csDiskState.Format("");
		}

		strTemp.Format("%d",i);
		m_listDiskState.InsertItem(i,strDiskNum,0);
		m_listDiskState.SetItemText(i,1,m_csDiskVolume);
		m_listDiskState.SetItemText(i,2,m_csDiskFreeSpace);
		m_listDiskState.SetItemText(i,3,m_csDiskState);
	}

	UpdateData(FALSE);
}

/*********************************************************
Function:	CheckInitParam
Desc:		check current selected device, and initialize parameters in the dialog
Input:	
Output:	
Return:	TRUE,checked and got state info;FALSE,failed;
**********************************************************/
BOOL CDlgITSWorkState::CheckInitParam(void)
{
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	
	if (iDeviceIndex == -1)
	{
		m_lLoginID = -1;
		GetDlgItem(IDC_BTN_GET)->EnableWindow(FALSE);
		return FALSE;
	}
	
	if (m_iDeviceIndex == iDeviceIndex)
	{
		return TRUE;
	}
	else
	{
		m_iDeviceIndex = iDeviceIndex;
		m_listChanState.DeleteAllItems();
		m_listDiskState.DeleteAllItems();
	}
	
	m_lLoginID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	
	if (m_lLoginID < 0)
	{
		GetDlgItem(IDC_BTN_GET)->EnableWindow(FALSE);
		return FALSE;
	}
	
	OnBtnGet();
	EnableWindow(TRUE);
	return TRUE;
}

void CDlgITSWorkState::OnSelchangeComboHost() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_iHostSel = m_comboHostIndex.GetCurSel();
	m_dwDataTotal = m_struWorkState.struTrafficDataInfo[m_iHostSel].dwDataQuantity;
	m_dwNeedSendData = m_struWorkState.struTrafficDataInfo[m_iHostSel].dwDataRsendQuantity;
	m_csHostIP.Format(m_struWorkState.struTrafficDataInfo[m_iHostSel].struDataHost.sIpV4);
	m_dwStartYear = m_struWorkState.struTrafficDataInfo[m_iHostSel].struStartTime.wYear;
	m_dwStartMonth = m_struWorkState.struTrafficDataInfo[m_iHostSel].struStartTime.wMonth;
	m_dwStartDay = m_struWorkState.struTrafficDataInfo[m_iHostSel].struStartTime.wDay;
	m_dwStartHour = m_struWorkState.struTrafficDataInfo[m_iHostSel].struStartTime.wHour;
	m_dwStartMinute = m_struWorkState.struTrafficDataInfo[m_iHostSel].struStartTime.wMinute;
	m_dwStartSec = m_struWorkState.struTrafficDataInfo[m_iHostSel].struStartTime.wSecond;
	m_dwEndYear = m_struWorkState.struTrafficDataInfo[m_iHostSel].struEndTime.wYear;
	m_dwEndMonth = m_struWorkState.struTrafficDataInfo[m_iHostSel].struEndTime.wMonth;
	m_dwEndDay = m_struWorkState.struTrafficDataInfo[m_iHostSel].struEndTime.wDay;
	m_dwEndHour = m_struWorkState.struTrafficDataInfo[m_iHostSel].struEndTime.wHour;
	m_dwEndMinute = m_struWorkState.struTrafficDataInfo[m_iHostSel].struEndTime.wMinute;
	m_dwEndSec = m_struWorkState.struTrafficDataInfo[m_iHostSel].struEndTime.wSecond;
}
