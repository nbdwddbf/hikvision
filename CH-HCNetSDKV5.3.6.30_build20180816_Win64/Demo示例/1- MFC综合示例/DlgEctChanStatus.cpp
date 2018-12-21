// DlgEctChanStatus.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgEctChanStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEctChanStatus dialog


CDlgEctChanStatus::CDlgEctChanStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEctChanStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEctChanStatus)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lFindHandle = -1;
	m_bGetNext = FALSE;
	m_hGetInfoThread = NULL;
}


void CDlgEctChanStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEctChanStatus)
	DDX_Control(pDX, IDC_LIST_ECT_CHAN_STATUS, m_listEctChanStatus);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEctChanStatus, CDialog)
	//{{AFX_MSG_MAP(CDlgEctChanStatus)
	ON_BN_CLICKED(IDC_BTN_GET_STATUS, OnBtnGetStatus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEctChanStatus message handlers

DWORD WINAPI CDlgEctChanStatus::GetEctChanStatusThread(LPVOID lpArg)
{
	CDlgEctChanStatus* pThis = reinterpret_cast<CDlgEctChanStatus*>(lpArg);
	int iRet =0;
	char szLan[128] = {0};
	while(pThis->m_bGetNext)
	{
		if (-1 == pThis->m_lFindHandle)
		{
			continue;
		}
		iRet = NET_DVR_GetNextRemoteConfig(pThis->m_lFindHandle, &pThis->lpITSEctChannelStatus[pThis->m_iEctStatusCount], sizeof(NET_ITS_ECT_CHANNELSTATE));
		if (iRet == NET_SDK_GET_NEXT_STATUS_SUCCESS)
		{
			pThis->AddEctChanStatusInfoToDlg(&(pThis->lpITSEctChannelStatus[pThis->m_iEctStatusCount]));
			pThis->m_iEctStatusCount++;
		} 
		else
		{
			if (iRet == NET_SDK_GET_NETX_STATUS_NEED_WAIT)
			{
				Sleep(5);
				continue;
			}
			if (iRet == NET_SDK_GET_NEXT_STATUS_FINISH)
			{
				g_StringLanType(szLan, "获取列表结束!", "Get route info Ending");
				AfxMessageBox(szLan);
				break;
			}
			else if(iRet == NET_SDK_GET_NEXT_STATUS_FAILED)
			{
				g_StringLanType(szLan, "获取列表失败!", "Get route info failed");
				AfxMessageBox(szLan);
				break;
			}
			else
			{
				g_StringLanType(szLan, "未知状态", "Unknown status");
				AfxMessageBox(szLan);
				break;
			}
		}
	}
	if (-1 != pThis->m_lFindHandle)
	{
		if (!NET_DVR_StopRemoteConfig(pThis->m_lFindHandle))
		{
			g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_FAIL_T, "Stop Remote Config Failed");
			pThis->m_bGetNext = FALSE;
		}
		else
		{
			g_pMainDlg->AddLog(pThis->m_iDeviceIndex, OPERATION_SUCC_T, "Stop Remote Config Successful");
			pThis->m_bGetNext = FALSE;
			pThis->m_lFindHandle = -1;
		}
	}
	return 0;
}


void CDlgEctChanStatus::OnBtnGetStatus() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	m_iEctStatusCount = 0;
	if (m_lFindHandle >= 0)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "It is getting data, wait for a moment");
	} 
	else
	{
		m_listEctChanStatus.DeleteAllItems();
		m_lFindHandle = NET_DVR_StartRemoteConfig(m_lLoginID, NET_ITS_GET_ECT_CHAN_INFO, NULL, 0, NULL, this);
		if (m_lFindHandle < 0)
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_ITS_GET_ECT_CHAN_INFO");
			return;
		} 
		else
		{
			m_bGetNext = TRUE;
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "Start Remote Config successfully");
			DWORD dwThreadId;
			m_hGetInfoThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetEctChanStatusThread),this,0,&dwThreadId);
		}
	}
}

BOOL CDlgEctChanStatus::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_listEctChanStatus.SetExtendedStyle(m_listEctChanStatus.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);

	m_listEctChanStatus.InsertColumn(0, "序号", LVCFMT_LEFT, 60, -1);
	m_listEctChanStatus.InsertColumn(1, "通道号", LVCFMT_LEFT, 80, -1);
	m_listEctChanStatus.InsertColumn(2, "录像状态", LVCFMT_LEFT, 80, -1);
	m_listEctChanStatus.InsertColumn(3, "信号状态", LVCFMT_LEFT, 80, -1);
	m_listEctChanStatus.InsertColumn(4, "硬件状态", LVCFMT_LEFT, 80, -1);
	m_listEctChanStatus.InsertColumn(5, "IPC布防状态", LVCFMT_LEFT, 100, -1);
	m_listEctChanStatus.InsertColumn(6, "实际码率", LVCFMT_LEFT, 80, -1);
	m_listEctChanStatus.InsertColumn(7, "客户端连接数", LVCFMT_LEFT, 80, -1);
	m_listEctChanStatus.InsertColumn(8, "客户端IP", LVCFMT_LEFT, 150, -1);
	m_listEctChanStatus.InsertColumn(9, "通道IP连接数", LVCFMT_LEFT, 80, -1);
	m_listEctChanStatus.InsertColumn(10, "连接是否超出", LVCFMT_LEFT, 80, -1);

	lpITSEctChannelStatus = new NET_ITS_ECT_CHANNELSTATE[64];
	memset(lpITSEctChannelStatus, 0, sizeof(NET_ITS_ECT_CHANNELSTATE)*64);
	m_iEctStatusCount = 0;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgEctChanStatus::AddEctChanStatusInfoToDlg(LPNET_ITS_ECT_CHANNELSTATE lpInter)
{
	char szStr[128] = {0};
	CString strtemp;
	int iCount = m_listEctChanStatus.GetItemCount();
	//序号
	sprintf(szStr, "%3d", iCount);
	m_listEctChanStatus.InsertItem(iCount, szStr);
	//通道号
	strtemp.Format("%d", lpInter->dwChannel);
	m_listEctChanStatus.SetItemText(iCount, 1, strtemp);
	//录像状态
	if (lpInter->byRecordStatic == 0) //0-不录像,1-录像
	{
		m_listEctChanStatus.SetItemText(iCount, 2, "不录像");
	} 
	else
	{
		m_listEctChanStatus.SetItemText(iCount, 2, "录像");
	}
	//信号状态
	if (lpInter->bySignalStatic == 0)//0-正常,1-信号丢失
	{
		m_listEctChanStatus.SetItemText(iCount, 3, "正常");
	} 
	else
	{
		m_listEctChanStatus.SetItemText(iCount, 3, "信号丢失");
	}
	//通道硬件状态
	if (lpInter->byHardwareStatic == 0)//0-正常,1-异常
	{
		m_listEctChanStatus.SetItemText(iCount, 4, "正常");
	} 
	else
	{
		m_listEctChanStatus.SetItemText(iCount, 4, "异常");
	}
	//IPC布防状态
	if (lpInter->byChannelArmState == 0)//0-不布防,1-布防
	{
		m_listEctChanStatus.SetItemText(iCount, 5, "不布防");
	} 
	else
	{
		m_listEctChanStatus.SetItemText(iCount, 5, "布防");
	}
	//实际码率
	strtemp.Format("%d", lpInter->dwBitRate);
	m_listEctChanStatus.SetItemText(iCount, 6, strtemp);
	//客户端连接数
	strtemp.Format("%d", lpInter->dwLinkNum);
	m_listEctChanStatus.SetItemText(iCount, 7, strtemp);
	//客户端IP
	memset(szStr, 0, sizeof(szStr));
	memcpy(szStr, lpInter->struClientIP->sIpV4, 16);
	m_listEctChanStatus.SetItemText(iCount, 8, szStr);
	//通道IP连接数
	strtemp.Format("%d", lpInter->dwIPLinkNum);
	m_listEctChanStatus.SetItemText(iCount, 9, strtemp);
	//连接数是否超出
	strtemp.Format("%d", lpInter->byExceedMaxLink);
	m_listEctChanStatus.SetItemText(iCount, 10, strtemp);
	
	return;
}
