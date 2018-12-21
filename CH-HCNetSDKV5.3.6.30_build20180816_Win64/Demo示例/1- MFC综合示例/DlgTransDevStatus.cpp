// DlgTransDevStatus.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgTransDevStatus.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTransDevStatus dialog


CDlgTransDevStatus::CDlgTransDevStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTransDevStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTransDevStatus)
	m_dwLeftResource = 0;
	m_dwTotalResource = 0;
	m_iCount = 0;
	m_bGetAll = TRUE;
	m_pRecv = NULL;
	m_byCpuLoad = 0;
	//}}AFX_DATA_INIT
}


void CDlgTransDevStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTransDevStatus)
	DDX_Control(pDX, IDC_LIST_TRANS_CHAN, m_listTransChan);
	DDX_Control(pDX, IDC_LIST_DST_IP, m_listDstIp);
	DDX_Control(pDX, IDC_LIST_DST_ENCINFO, m_listDstEncInfo);
	DDX_Text(pDX, IDC_EDIT_LEFT_RESOURCE, m_dwLeftResource);
	DDX_Text(pDX, IDC_EDIT_TOTAL_RESOURCE, m_dwTotalResource);
	DDX_Text(pDX, IDC_EDIT_CPU_LD, m_byCpuLoad);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTransDevStatus, CDialog)
	//{{AFX_MSG_MAP(CDlgTransDevStatus)
	ON_BN_CLICKED(IDC_BTN_UPDATE, OnBtnUpdate)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_NOTIFY(NM_CLICK, IDC_LIST_TRANS_CHAN, OnClickListTransChan)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTransDevStatus message handlers

BOOL CDlgTransDevStatus::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);

	char szLan[128] = {0};
	m_iCurSelItem = -1;

	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();

	memset(&m_struTransDevStatus, 0, sizeof(m_struTransDevStatus));
	memset(m_struStreamInfo, 0, sizeof(m_struStreamInfo));
	memset(m_dwStatusList, 0, sizeof(m_dwStatusList));
	m_pRecv = new(std::nothrow) char[MAX_TRANS_CHAN_NUM * sizeof(NET_DVR_TRANSSTATUS) + 4];
	if (m_pRecv == NULL)
	{
		g_StringLanType(szLan, "分配内存失败", "New memory fail");
		AfxMessageBox(szLan);
	}

	g_StringLanType(szLan, "序号", "Serial No.");
	m_listTransChan.InsertColumn(0, szLan, LVCFMT_LEFT, 50, -1);

	g_StringLanType(szLan, "流ID", "Stream ID");
	m_listTransChan.InsertColumn(1, szLan, LVCFMT_LEFT, 100, -1);

	g_StringLanType(szLan, "关联通道", "Channel No.");
	m_listTransChan.InsertColumn(2, szLan, LVCFMT_LEFT, 60, -1);	

	g_StringLanType(szLan, "转码模式", "Trans mode");
	m_listTransChan.InsertColumn(3, szLan, LVCFMT_LEFT, 70, -1);

	g_StringLanType(szLan, "连接数", "Link number");
	m_listTransChan.InsertColumn(4, szLan, LVCFMT_LEFT, 60, -1);

	g_StringLanType(szLan, "使用资源数", "Trans resource");
	m_listTransChan.InsertColumn(5, szLan, LVCFMT_LEFT, 80, -1);

	g_StringLanType(szLan, "源封装类型", "Source Format type");
	m_listTransChan.InsertColumn(6, szLan, LVCFMT_LEFT, 90, -1);

	g_StringLanType(szLan, "源视频编码类型", "Source Video encode type");
	m_listTransChan.InsertColumn(7, szLan, LVCFMT_LEFT, 100, -1);

	g_StringLanType(szLan, "源图像宽", "Source Image width");
	m_listTransChan.InsertColumn(8, szLan, LVCFMT_LEFT, 70, -1);

	g_StringLanType(szLan, "源图像高", "Source Image height");
	m_listTransChan.InsertColumn(9, szLan, LVCFMT_LEFT, 70, -1);	

	g_StringLanType(szLan, "源视频码率", "Source Video bitrate");
	m_listTransChan.InsertColumn(10, szLan, LVCFMT_LEFT, 90, -1);

	g_StringLanType(szLan, "源帧率", "Source Frame rate");
	m_listTransChan.InsertColumn(11, szLan, LVCFMT_LEFT, 50, -1);

	g_StringLanType(szLan, "源音频编码类型", "Source Audio encode type");
	m_listTransChan.InsertColumn(12, szLan, LVCFMT_LEFT, 100, -1);

	g_StringLanType(szLan, "状态", "Status");
	m_listTransChan.InsertColumn(13, szLan, LVCFMT_LEFT, 50, -1);

	//目标转码表
	g_StringLanType(szLan, "序号", "No.");
	m_listDstEncInfo.InsertColumn(0, szLan, LVCFMT_LEFT, 40);

	g_StringLanType(szLan, "目标封装类型", "Target Format type");
	m_listDstEncInfo.InsertColumn(1, szLan, LVCFMT_LEFT, 90, -1);
	
	g_StringLanType(szLan, "目标视频编码类型", "Target encode type");
	m_listDstEncInfo.InsertColumn(2, szLan, LVCFMT_LEFT, 100, -1);
	
	g_StringLanType(szLan, "目标图像宽", "Target Image width");
	m_listDstEncInfo.InsertColumn(3, szLan, LVCFMT_LEFT, 90, -1);
	
	g_StringLanType(szLan, "目标图像高", "Target Image height");
	m_listDstEncInfo.InsertColumn(4, szLan, LVCFMT_LEFT, 90, -1);
	
	g_StringLanType(szLan, "目标视频码率", "Target Video bit rate");
	m_listDstEncInfo.InsertColumn(5, szLan, LVCFMT_LEFT, 90, -1);
	
	g_StringLanType(szLan, "目标帧率", "Target Frame rate");
	m_listDstEncInfo.InsertColumn(6, szLan, LVCFMT_LEFT, 60, -1);
	
	g_StringLanType(szLan, "目标音频编码类型", "Target Audio encode type");
	m_listDstEncInfo.InsertColumn(7, szLan, LVCFMT_LEFT, 100, -1);

	//连接IP表
	g_StringLanType(szLan, "序号", "No.");
	m_listDstIp.InsertColumn(0, szLan, LVCFMT_LEFT, 40);

	g_StringLanType(szLan, "IP地址", "IP Address");
	m_listDstIp.InsertColumn(1, szLan, LVCFMT_LEFT, 100, -1);

	g_StringLanType(szLan, "端口", "Port");
	m_listDstIp.InsertColumn(2, szLan, LVCFMT_LEFT, 50, -1);

	m_listDstEncInfo.SetExtendedStyle(m_listDstEncInfo.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listDstIp.SetExtendedStyle(m_listDstIp.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listTransChan.SetExtendedStyle(m_listTransChan.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	
	GetDeviceStatus();
	//SetTimer(TRANS_DEVICE_TIMER, 3000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTransDevStatus::OnBtnUpdate() 
{
	// TODO: Add your control notification handler code here
	m_bGetAll = FALSE;
	GetDeviceStatus();
	m_bGetAll = TRUE;	
}

void CDlgTransDevStatus::InsertDataToList(DWORD dwList)
{
	if (m_pRecv == NULL)
	{
		return;
	}

	int i = 0;
	int j = 0;
	char szLan[128] = {0};
	CString csTemp;
	DWORD dwItemCount = 0;
	LPNET_DVR_TRANSSTATUS lpTemp = NULL;
	
	switch (dwList)
	{
	case 0:
		dwItemCount = m_iCount;
		lpTemp = (LPNET_DVR_TRANSSTATUS)(m_pRecv + 4);
		for (i = 0; i < dwItemCount; i++)
		{		
			m_listTransChan.InsertItem(i, itoa(i + 1, szLan, 10));
			m_listTransChan.SetItemText(i, 1, (const char *)lpTemp->struStreamInfo.byID);
			m_listTransChan.SetItemText(i ,2, ltoa(lpTemp->struStreamInfo.dwChannel, szLan, 10));
			
			if (m_dwStatusList[i] != 0)
			{
				for (j = 3; j < dwItemCount; j++)
				{
					m_listTransChan.SetItemText(i, j, "");
				}				
			}
			else
			{
				if (lpTemp->byMode == 1)
				{
					g_StringLanType(szLan, "主动", "Active");
				}
				else if (lpTemp->byMode == 2)
				{
					g_StringLanType(szLan, "被动", "Passive");
				}
				m_listTransChan.SetItemText(i, 3, szLan);			
				
				m_listTransChan.SetItemText(i, 4, itoa(lpTemp->byLinkNums, szLan, 10));
				
				m_listTransChan.SetItemText(i, 5, itoa(lpTemp->byTransResource, szLan, 10));
				
				csTemp = GetFormatType(lpTemp->struSrcEncodeInfo.byFormatType);
				m_listTransChan.SetItemText(i, 6, csTemp);
				
				csTemp = GetVideoEncType(lpTemp->struSrcEncodeInfo.byVideoEncType);
				m_listTransChan.SetItemText(i, 7, csTemp);
				
				m_listTransChan.SetItemText(i, 8, itoa(lpTemp->struSrcEncodeInfo.wWidth, szLan, 10));
				
				m_listTransChan.SetItemText(i, 9, itoa(lpTemp->struSrcEncodeInfo.wHeight, szLan, 10));			
				
				itoa(lpTemp->struSrcEncodeInfo.dwVideoBitrate, szLan, 10);
				csTemp.Format("%sKbps", szLan);
				m_listTransChan.SetItemText(i, 10, csTemp);			
				
				if (lpTemp->struSrcEncodeInfo.dwVideoFrameRate < 200)
				{
					m_listTransChan.SetItemText(i, 11, itoa(lpTemp->struSrcEncodeInfo.dwVideoFrameRate, szLan, 10));
				}
				else
				{
					csTemp = GetFrameRate(lpTemp->struSrcEncodeInfo.dwVideoFrameRate);
					m_listTransChan.SetItemText(i, 11, csTemp);
				}			
				
				csTemp = GetAudioEncType(lpTemp->struSrcEncodeInfo.byAudioEncType);
			    m_listTransChan.SetItemText(i, 12, csTemp);
			}

			m_listTransChan.SetItemText(i, 13, itoa(m_dwStatusList[i], szLan, 10));			
			
			lpTemp++;
		}
	    break;
	case 1:
		lpTemp = (LPNET_DVR_TRANSSTATUS)(m_pRecv + 4 + m_iCurSelItem * sizeof(NET_DVR_TRANSSTATUS));
		for (i = 0; i < lpTemp->byLinkNums; i++)
		{
			m_listDstIp.InsertItem(i, itoa(i + 1, szLan, 10));
			m_listDstIp.SetItemText(i, 1, lpTemp->struDstIPInfo[i].struIP.sIpV4);
			m_listDstIp.SetItemText(i, 2, itoa(lpTemp->struDstIPInfo[i].wPort, szLan, 10));
		}
		break;
	case 2:
		lpTemp = (LPNET_DVR_TRANSSTATUS)(m_pRecv + 4 + m_iCurSelItem * sizeof(NET_DVR_TRANSSTATUS));
		for (i = 0; i < lpTemp->byLinkNums; i++)
		{
			m_listDstEncInfo.InsertItem(i, itoa(i + 1, szLan, 10));
			csTemp = GetFormatType(lpTemp->struDstEncodeInfo[i].byFormatType);
			m_listDstEncInfo.SetItemText(i, 1, csTemp);
			
			csTemp = GetVideoEncType(lpTemp->struDstEncodeInfo[i].byVideoEncType);
			m_listDstEncInfo.SetItemText(i, 2, csTemp);
			
			m_listDstEncInfo.SetItemText(i, 3, itoa(lpTemp->struDstEncodeInfo[i].wWidth, szLan, 10));
			
			m_listDstEncInfo.SetItemText(i, 4, itoa(lpTemp->struDstEncodeInfo[i].wHeight, szLan, 10));
			
			itoa(lpTemp->struDstEncodeInfo[i].dwVideoBitrate, szLan, 10);
			csTemp.Format("%sKbps", szLan);
			m_listDstEncInfo.SetItemText(i, 5, csTemp);			
			
			if (lpTemp->struDstEncodeInfo[i].dwVideoFrameRate < 200)
			{
				m_listDstEncInfo.SetItemText(i, 6, itoa(lpTemp->struDstEncodeInfo[i].dwVideoFrameRate, szLan, 10));
			}
			else
			{
				csTemp = GetFrameRate(lpTemp->struDstEncodeInfo[i].dwVideoFrameRate);
			    m_listDstEncInfo.SetItemText(i, 6, csTemp);
			}	
			
			csTemp = GetAudioEncType(lpTemp->struDstEncodeInfo[i].byAudioEncType);
			m_listDstEncInfo.SetItemText(i, 7, csTemp);
		}
		break;
	default:
		break;
	}	
}

CString CDlgTransDevStatus::GetFormatType(BYTE byIndex)
{
	CString csTemp = "";
	char szLan[64] = {0};

	switch (byIndex)
	{
	case 1:
		csTemp = "Original";
		break;
	case 2:
		csTemp = "RTP";
		break;
	case 3:
		csTemp = "PS";
		break;
	case 4:
		csTemp = "TS";
		break;
	case 5:
		csTemp = "Private";
		break;
	case 6:
		csTemp = "FLV";
		break;
	case 7:
		csTemp = "ASF";
		break;
	case 8:
		csTemp = "3GP";
		break;
	case 9:
		csTemp= "GB28281";
		break;
	case 0xff:
		g_StringLanType(szLan, "无效", "Invalid");
		csTemp.Format("%s", szLan);
		break;
	default:
		break;
	}

	return csTemp;
}
	
CString CDlgTransDevStatus::GetVideoEncType(BYTE byIndex)
{
	CString csTemp = "";
	char szLan[64] = {0};

	switch (byIndex)
	{
	case 0:
		csTemp = "Private264";
		break;
	case 1:
		csTemp = "H264";
		break;
	case 2:
		csTemp = "mpeg4";
		break;
	case 5:
		csTemp = "MPEG2";
		break;
	case 7:
		csTemp = "M-JPEG";
		break;
	case 0xff:
		g_StringLanType(szLan, "无效", "Invalid");
		csTemp.Format("%s", szLan);
		break;
	default:
		break;
	}

	return csTemp;
}

CString CDlgTransDevStatus::GetResolutionName(BYTE byIndex)
{
	CString csTemp = "";
	switch (byIndex)
	{
	case 0:
		csTemp = "DCIF";
		break;
	case 1:
		csTemp = "CIF";
		break;
	case 2:
		csTemp = "QCIF";
		break;
	case 3:
		csTemp = "4CIF";
		break;
	case 4:
		csTemp = "2CIF";
		break;
	case 16:
		csTemp = "VGA";
		break;
	case 17:
		csTemp = "UXGA";
		break;
	case 18:
		csTemp = "SVGA";
		break;
	case 19:
		csTemp = "HD720p";
		break;
	case 20:
		csTemp = "XVGA";
		break;
	case 21:
		csTemp = "HD900p";
		break;
	case 22:
		csTemp = "SXGAp";
		break;
	case 27:
		csTemp = "1920*1080";
		break;
	case 28:
		csTemp = "2560*1920";
		break;
	case 29:
		csTemp = "1600*304";
		break;
	case 30:
		csTemp = "2048*1536";
		break;
	case 31:
		csTemp = "2448*2048";
		break;
	case 32:
		csTemp = "2448*1200";
		break;
	case 33:
		csTemp = "2448*800";
		break;
	case 34:
		csTemp = "XGA";
		break;
	case 35:
		csTemp = "SXGA";
		break;
	case 36:
		csTemp = "WD1";
		break;
	case 37:
		csTemp = "1080i";
		break;
	case 38:
		csTemp = "WXGA";
		break;
	default:
		break;
	}

	return csTemp;
}

// CString CDlgTransDevStatus::GetVideoBitrate(DWORD dwIndex)
// {
// 	CString csTemp = "";
// 
// 	switch (dwIndex)
// 	{
// 	case 2:
// 		csTemp = "32Kbps";
// 		break;
// 	case 3:
// 		csTemp = "48Kbps";
// 		break;
// 	case 4:
// 		csTemp = "64Kbps";
// 		break;
// 	case 5:
// 		csTemp = "80Kbps";
// 		break;
// 	case 6:
// 		csTemp = "96Kbps";
// 		break;
// 	case 7:
// 		csTemp = "128Kbps";
// 		break;
// 	case 8:
// 		csTemp = "160Kbps";
// 		break;
// 	case 9:
// 		csTemp = "192Kbps";
// 		break;
// 	case 10:
// 		csTemp = "224Kbps";
// 		break;
// 	case 11:
// 		csTemp = "256Kbps";
// 		break;
// 	case 12:
// 		csTemp = "320Kbps";
// 		break;
// 	case 13:
// 		csTemp = "384Kbps";
// 		break;
// 	case 14:
// 		csTemp = "448Kbps";
// 		break;
// 	case 15:
// 		csTemp = "512Kbps";
// 		break;
// 	case 16:
// 		csTemp = "640Kbps";
// 		break;
// 	case 17:
// 		csTemp = "768Kbps";
// 		break;
// 	case 18:
// 		csTemp = "896Kbps";
// 		break;
// 	case 19:
// 		csTemp = "1024Kbps";
// 		break;
// 	case 20:
// 		csTemp = "1280Kbps";
// 		break;
// 	case 21:
// 		csTemp = "1536Kbps";
// 		break;
// 	case 22:
// 		csTemp = "1792Kbps";
// 		break;
// 	case 23:
// 		csTemp = "2048Kbps";
// 		break;
// 	case 24:
// 		csTemp = "3072Kbps";
// 		break;
// 	case 25:
// 		csTemp = "4096Kbps";
// 		break;
// 	case 26:
// 		csTemp = "8192Kbps";
// 		break;
// 	case 27:
// 		csTemp = "16384Kbps";
// 		break;
// 	default:
// 		if ((dwIndex & 0x80000000) != 0)
// 		{
// 			csTemp.Format("%dKbps", dwIndex & 0x70000000);
// 		}
// 		break;		
// 	}
// 
// 	return csTemp;
// 
// }

CString CDlgTransDevStatus::GetFrameRate(DWORD dwIndex)
{
	CString csTemp = "";

	switch (dwIndex)
	{
	case 200:
		csTemp = "1/2";
		break;
	case 201:
		csTemp = "1/4";
		break;
	case 202:
		csTemp = "1/8";
		break;
	case 203:
		csTemp = "1/16";
		break;	
	default:
		break;
	}

	return csTemp;
}

CString CDlgTransDevStatus::GetAudioEncType(BYTE dwIndex)
{
	CString csTemp = "";

	switch (dwIndex)
	{
	case 0:
		csTemp = "G722";
		break;
	case 1:
		csTemp = "G711_U";
		break;
	case 2:
		csTemp = "G711_A";
		break;
	case 5:
		csTemp = "MPEG2";
		break;
	case 6:
		csTemp = "G726";
		break;
	case 7:
		csTemp = "AAC";
		break;	
	default:
		break;
	}

	return csTemp;
}

void CDlgTransDevStatus::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	if (m_pRecv != NULL)
	{
		delete []m_pRecv;
		m_pRecv = NULL;
	}

	CDialog::OnCancel();
}

void CDlgTransDevStatus::OnClickListTransChan(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION  iPos = m_listTransChan.GetFirstSelectedItemPosition();
	if (iPos == NULL)
	{
		return;
	}
	m_iCurSelItem = m_listTransChan.GetNextSelectedItem(iPos);
	
	m_listDstIp.DeleteAllItems();
	m_listDstEncInfo.DeleteAllItems();
	InsertDataToList(1);
	InsertDataToList(2);
	//OnBtnUpdate();
	*pResult = 0;
}

#if (_MSC_VER >= 1500)	//vs2008
void CDlgTransDevStatus::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgTransDevStatus::OnTimer(UINT nIDEvent) 
#endif
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == TRANS_DEVICE_TIMER && m_bGetAll)
	{
		GetDeviceStatus();
	}
	CDialog::OnTimer(nIDEvent);
}

void CDlgTransDevStatus::GetDeviceStatus()
{
	if (m_iDeviceIndex == -1 || m_pRecv == NULL)
	{
		return;
	}

	if (m_bGetAll)
	{
		if (!NET_DVR_GetDeviceStatus(m_lUserID, NET_DVR_GET_STREAM_TRANS_STATUS, 0xffffffff, NULL, 0, NULL, m_pRecv, 4 + sizeof(NET_DVR_TRANSSTATUS) * MAX_TRANS_CHAN_NUM))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_STREAM_TRANS_STATUS");
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_STREAM_TRANS_STATUS");
			memset(m_dwStatusList, 0, sizeof(m_dwStatusList));
			m_listTransChan.DeleteAllItems();
			m_listDstEncInfo.DeleteAllItems();
			m_listDstIp.DeleteAllItems();
			
			m_iCount = *((int*)m_pRecv);

			InsertDataToList(0);
			if (m_iCurSelItem != -1)
			{
				InsertDataToList(1);
				InsertDataToList(2);
			}

			//保存流ID参数，以供按条件获取状态测试
			SaveStreamInfo();
		}
	}
	else
	{
		if (m_iCount != 0)
		{
			memset(m_dwStatusList, 0, sizeof(m_dwStatusList));
			memset(m_pRecv, 0, MAX_TRANS_CHAN_NUM * sizeof(NET_DVR_TRANSSTATUS) + 4);
			if (!NET_DVR_GetDeviceStatus(m_lUserID, NET_DVR_GET_STREAM_TRANS_STATUS, m_iCount, m_struStreamInfo, m_iCount * sizeof(m_struStreamInfo[0]), m_dwStatusList, m_pRecv + 4, sizeof(NET_DVR_TRANSSTATUS) * MAX_TRANS_CHAN_NUM))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_STREAM_TRANS_STATUS");
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_STREAM_TRANS_STATUS");
				m_listTransChan.DeleteAllItems();
				m_listDstEncInfo.DeleteAllItems();
				m_listDstIp.DeleteAllItems();
				
				m_iCount = *((int*)m_pRecv);
				
				InsertDataToList(0);
				if (m_iCurSelItem != -1)
				{
					InsertDataToList(1);
					InsertDataToList(2);
				}
			}
		}
		
	}
	
	
	if (!NET_DVR_GetDeviceStatus(m_lUserID, NET_DVR_GET_DEVICE_TRANS_STATUS, 0, NULL, 0, NULL, &m_struTransDevStatus, sizeof(m_struTransDevStatus)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_DEVICE_TRANS_STATUS");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_DEVICE_TRANS_STATUS");
		m_dwTotalResource = m_struTransDevStatus.dwTotalResource;
		m_dwLeftResource = m_struTransDevStatus.dwIdleResource;
		m_byCpuLoad = m_struTransDevStatus.byCpuLoad;
	}
	
	UpdateData(FALSE);
}

void CDlgTransDevStatus::SaveStreamInfo()
{
	int i = 0;
	m_iCount = *((int*)m_pRecv);

	LPNET_DVR_TRANSSTATUS lpTemp = (LPNET_DVR_TRANSSTATUS)(m_pRecv + 4);

	for (i = 0; i < m_iCount; i++)
	{
		memcpy(&m_struStreamInfo[i], &lpTemp->struStreamInfo, sizeof(m_struStreamInfo[0]));
		lpTemp++;
	}
}
