// DlgStreamRecordStatus.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgStreamRecordStatus.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgStreamRecordStatus dialog


CDlgStreamRecordStatus::CDlgStreamRecordStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStreamRecordStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgStreamRecordStatus)
	m_strRelatedChannel = _T("");
	m_strRelatedDisc = _T("");
	m_strStreamID = _T("");
	m_strStatus = _T("");
	m_bOffLineRecord = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgStreamRecordStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgStreamRecordStatus)
	DDX_Control(pDX, IDC_LIST_RECORD_STATUS, m_lstStreamRecordStatus);
	DDX_Control(pDX, IDC_COMBO_RECORD_TYPE, m_cmbRecordType);
	DDX_Text(pDX, IDC_EDIT_RELATED_CHANNEL, m_strRelatedChannel);
	DDX_Text(pDX, IDC_EDIT_RELATED_DISC, m_strRelatedDisc);
	DDX_Text(pDX, IDC_EDIT_STREAM_ID, m_strStreamID);
	DDX_Text(pDX, IDC_EDIT_STATUS, m_strStatus);
	DDX_Check(pDX, IDC_CHECK_OFFLINE_RECORD, m_bOffLineRecord);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgStreamRecordStatus, CDialog)
	//{{AFX_MSG_MAP(CDlgStreamRecordStatus)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAddStreamID)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDelStreamID)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGetStreamRecordStatus)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSetStreamRecordStatus)
	ON_NOTIFY(NM_CLICK, IDC_LIST_RECORD_STATUS, OnClickListRecordStatus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgStreamRecordStatus message handlers

BOOL CDlgStreamRecordStatus::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);

	m_cmbRecordType.SetCurSel(0);

	m_lstStreamRecordStatus.SetExtendedStyle(m_lstStreamRecordStatus.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	char szLan[128] = {0};
	g_StringLanType(szLan, "序号", "Serial No.");
	m_lstStreamRecordStatus.InsertColumn(0, szLan, LVCFMT_LEFT, 50, -1);
	
	g_StringLanType(szLan, "流ID", "Stream ID");
	m_lstStreamRecordStatus.InsertColumn(1, szLan, LVCFMT_LEFT, 100, -1);
	
	g_StringLanType(szLan, "关联通道", "Related channel");
	m_lstStreamRecordStatus.InsertColumn(2, szLan, LVCFMT_LEFT, 60, -1);
	
	g_StringLanType(szLan, "编码器状态", "Encode status");
	m_lstStreamRecordStatus.InsertColumn(3, szLan, LVCFMT_LEFT, 100, -1);

	g_StringLanType(szLan, "关联磁盘", "Related disc");
	m_lstStreamRecordStatus.InsertColumn(4, szLan, LVCFMT_LEFT, 60, -1);

	g_StringLanType(szLan, "状态", "Status");
	m_lstStreamRecordStatus.InsertColumn(5, szLan, LVCFMT_LEFT, 60, -1);
	
	g_StringLanType(szLan, "断网联动录像", "Off Line Record");
	m_lstStreamRecordStatus.InsertColumn(6, szLan, LVCFMT_LEFT, 60, -1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgStreamRecordStatus::OnButtonAddStreamID() 
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
	
	int iItemCount = m_lstStreamRecordStatus.GetItemCount();
	if (iItemCount > 64)
	{
		g_StringLanType(szLan,"流ID超过64个","Stream ID is more than 64");
		AfxMessageBox(szLan);
		return;
	}
	strTemp.Format("%02d", iItemCount+1);
	m_lstStreamRecordStatus.InsertItem(iItemCount, strTemp);
	m_lstStreamRecordStatus.SetItemText(iItemCount, 1, m_strStreamID);
	m_lstStreamRecordStatus.SetItemText(iItemCount, 2, m_strRelatedChannel);

	m_cmbRecordType.GetWindowText(strTemp);
	m_lstStreamRecordStatus.SetItemText(iItemCount, 3, strTemp);
	m_lstStreamRecordStatus.SetItemText(iItemCount, 4, m_strRelatedDisc);

	strTemp.Format("%d", m_bOffLineRecord);
	m_lstStreamRecordStatus.SetItemText(iItemCount, 6, strTemp);
}

void CDlgStreamRecordStatus::OnButtonDelStreamID() 
{
	// TODO: Add your control notification handler code here
	while(m_lstStreamRecordStatus.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED) != -1)
	{
		int nItem = m_lstStreamRecordStatus.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED);
		m_lstStreamRecordStatus.DeleteItem(nItem);
	}
	
}

void CDlgStreamRecordStatus::OnButtonGetStreamRecordStatus() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    char szLan[128] = {0};
	DWORD dwReturn = 0;
	CString strTemp;

	LPNET_DVR_STREAM_RECORD_STATUS pStreamRecordStatus = NULL;

	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	LONG lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	
	int iItemCount = m_lstStreamRecordStatus.GetItemCount();
	
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

		pStreamRecordStatus = new(std::nothrow) NET_DVR_STREAM_RECORD_STATUS;
		if (NULL == pStreamRecordStatus)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pStreamRecordStatus, 0, sizeof(NET_DVR_STREAM_RECORD_STATUS));

		// 返回的状态
		DWORD dwStatus = 0;
		BOOL bRet = NET_DVR_GetDeviceConfig(lLoginID, NET_DVR_GET_STREAM_RECORD_STATUS, iItemCount, pstruStreamID, sizeof(NET_DVR_STREAM_INFO), &dwStatus, pStreamRecordStatus, sizeof(NET_DVR_STREAM_RECORD_STATUS));
		if (bRet && (0 == dwStatus))
		{
			g_StringLanType(szLan,"获取流录像状态成功","Get source success");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "Get Stream record status success");
			AfxMessageBox(szLan);
		}
		else
		{        
			g_StringLanType(szLan,"获取流录像状态失败","Fail to Get stream record status");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Fail to set stream record status");
			AfxMessageBox(szLan);
			return;
		}

		m_cmbRecordType.SetCurSel(pStreamRecordStatus->byRecord);
		m_strRelatedDisc.Format("%d", pStreamRecordStatus->dwRelatedHD);

		m_bOffLineRecord = pStreamRecordStatus->byOffLineRecord;
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

		// 申请iItemCount个NET_DVR_STREAM_RECORD_STATUS
		pStreamRecordStatus = new(std::nothrow) NET_DVR_STREAM_RECORD_STATUS[iItemCount];
		if (NULL == pStreamRecordStatus)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pStreamRecordStatus, 0, iItemCount*sizeof(NET_DVR_STREAM_RECORD_STATUS));

		DWORD *pStatus = new DWORD[iItemCount];
		memset(pStatus, 0, sizeof(DWORD)*iItemCount);

		int i = 0; 
		for (i=0; i<iItemCount; i++)
		{
		 	pTempStreamID->dwSize = sizeof(NET_DVR_STREAM_INFO);
			strncpy((char*)pTempStreamID->byID, m_lstStreamRecordStatus.GetItemText(i, 1), STREAM_ID_LEN);
		 	pTempStreamID->dwChannel = atoi(m_lstStreamRecordStatus.GetItemText(i, 2));
			pTempStreamID++;
		}

		if (NET_DVR_GetDeviceConfig(lLoginID, NET_DVR_GET_STREAM_RECORD_STATUS, iItemCount, pstruStreamID, iItemCount*sizeof(NET_DVR_STREAM_INFO), pStatus, pStreamRecordStatus, iItemCount*sizeof(NET_DVR_STREAM_RECORD_STATUS)))
		{
			g_StringLanType(szLan,"批量获取流录像状态成功","Get source success");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "Get Stream record status success");
			AfxMessageBox(szLan);
		}
		else
		{        
			g_StringLanType(szLan,"批量获取流录像状态失败","Fail to Get stream record status");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Fail to set stream record status");
			AfxMessageBox(szLan);
			return;
		}

		for (i=0; i<iItemCount; i++)
		{
			m_cmbRecordType.GetLBText(pStreamRecordStatus->byRecord, strTemp);
			m_lstStreamRecordStatus.SetItemText(i, 3, strTemp);
			strTemp.Format("%d", pStreamRecordStatus->dwRelatedHD);
			m_lstStreamRecordStatus.SetItemText(i, 4, strTemp);
			
			CString strStatus;
			strStatus.Format("%d", *pStatus);
			m_lstStreamRecordStatus.SetItemText(i, 5, strStatus);

			strTemp.Format("%d", pStreamRecordStatus->byOffLineRecord);
			m_lstStreamRecordStatus.SetItemText(i, 6, strTemp);

			pStatus++;
			pStreamRecordStatus++;
		}

	}

	UpdateData(FALSE);
}

void CDlgStreamRecordStatus::OnButtonSetStreamRecordStatus() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    char szLan[128] = {0};

	LPNET_DVR_STREAM_RECORD_STATUS pStreamRecordStatus = NULL;
	LPNET_DVR_STREAM_RECORD_STATUS pTempRecordStatus = NULL;
	
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	LONG lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	
	int iItemCount = m_lstStreamRecordStatus.GetItemCount();
	
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

		pStreamRecordStatus = new(std::nothrow) NET_DVR_STREAM_RECORD_STATUS;
		if (NULL == pStreamRecordStatus)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pStreamRecordStatus, 0, sizeof(NET_DVR_STREAM_RECORD_STATUS));
		pStreamRecordStatus->dwSize = sizeof(NET_DVR_STREAM_RECORD_STATUS);
		//pStreamRecordStatus->byRecord = m_cmbRecordType.GetCurSel(); //只读
		pStreamRecordStatus->dwRelatedHD = atoi(m_strRelatedDisc);
		pStreamRecordStatus->byOffLineRecord = m_bOffLineRecord;

		DWORD dwStatus = 0;
		BOOL bRet = NET_DVR_SetDeviceConfig(lLoginID, NET_DVR_SET_STREAM_RECORD_STATUS, iItemCount, pstruStreamID, sizeof(NET_DVR_STREAM_INFO), &dwStatus, pStreamRecordStatus, sizeof(NET_DVR_STREAM_RECORD_STATUS));
		if (bRet && (0 == dwStatus))
		{
			g_StringLanType(szLan,"设置流录像状态成功","Succeed to set stream record status");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "Set Stream record status");
			AfxMessageBox(szLan);
		}
		else
		{        
			g_StringLanType(szLan,"设置流录像状态失败","Fail to set stream record status");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Fail to set stream record status");
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

		// 申请iItemCount个NET_DVR_STREAM_RECORD_STATUS
		pStreamRecordStatus = new(std::nothrow) NET_DVR_STREAM_RECORD_STATUS[iItemCount];
		if (NULL == pStreamRecordStatus)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pStreamRecordStatus, 0, iItemCount*sizeof(NET_DVR_STREAM_RECORD_STATUS));
		pTempRecordStatus = pStreamRecordStatus;

		int i = 0; 
		for (i=0; i<iItemCount; i++)
		{
		 	pTempStreamID->dwSize = sizeof(NET_DVR_STREAM_INFO);
			strncpy((char*)pTempStreamID->byID, m_lstStreamRecordStatus.GetItemText(i, 1), STREAM_ID_LEN);
		 	pTempStreamID->dwChannel = atoi(m_lstStreamRecordStatus.GetItemText(i, 2));
		 	
			pTempRecordStatus->dwSize = sizeof(NET_DVR_STREAM_RECORD_STATUS);

			//只读不能设置
// 			if (0 == strcmp("不在录像", m_lstStreamRecordStatus.GetItemText(i, 3)))
// 			{
// 				pTempRecordStatus->byRecord = 0;
// 			}
// 			else  if (0 == strcmp("在录像", m_lstStreamRecordStatus.GetItemText(i, 3)))
// 			{
// 				pTempRecordStatus->byRecord = 1;
// 			}
// 			else  if (0 == strcmp("空闲", m_lstStreamRecordStatus.GetItemText(i, 3)))
// 			{
// 				pTempRecordStatus->byRecord = 2;
// 			}
// 			else  if (0 == strcmp("无连接", m_lstStreamRecordStatus.GetItemText(i, 3)))
// 			{
// 				pTempRecordStatus->byRecord = 3;
// 			}
// 			else  if (0 == strcmp("无输入视频", m_lstStreamRecordStatus.GetItemText(i, 3)))
// 			{
// 				pTempRecordStatus->byRecord = 4;
// 			}
// 			else  if (0 == strcmp("未加载", m_lstStreamRecordStatus.GetItemText(i, 3)))
// 			{
// 				pTempRecordStatus->byRecord = 5;
// 			}
// 			else  if (0 == strcmp("存档中", m_lstStreamRecordStatus.GetItemText(i, 3)))
// 			{
// 				pTempRecordStatus->byRecord = 6;
// 			}
// 			else  if (0 == strcmp("回传中", m_lstStreamRecordStatus.GetItemText(i, 3)))
// 			{
// 				pTempRecordStatus->byRecord = 7;
// 			}
// 			else  if (0 == strcmp("用户名或密码错", m_lstStreamRecordStatus.GetItemText(i, 3)))
// 			{
// 				pTempRecordStatus->byRecord = 8;
// 			}
// 			else  if (0 == strcmp("设备不兼容", m_lstStreamRecordStatus.GetItemText(i, 3)))
// 			{
// 				pTempRecordStatus->byRecord = 9;
// 			}


			pTempRecordStatus->dwRelatedHD = atoi(m_lstStreamRecordStatus.GetItemText(i, 4)); 

			pTempRecordStatus->byOffLineRecord = m_bOffLineRecord/*atoi(m_lstStreamRecordStatus.GetItemText(i, 6))*/; 

			pTempStreamID++;
			pTempRecordStatus++;
		}

		DWORD *pStatus = new DWORD[iItemCount];
		memset(pStatus, 0, sizeof(DWORD)*iItemCount);


		if (NET_DVR_SetDeviceConfig(lLoginID, NET_DVR_SET_STREAM_RECORD_STATUS, iItemCount, pstruStreamID, iItemCount*sizeof(NET_DVR_STREAM_INFO), pStatus, pStreamRecordStatus, iItemCount*sizeof(NET_DVR_STREAM_RECORD_STATUS)))
		{
			g_StringLanType(szLan,"设置流录像状态成功","Succeed to set stream record status");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "Set Stream record status");
			AfxMessageBox(szLan);
		}
		else
		{        
			g_StringLanType(szLan,"设置流录像状态失败","Fail to set stream record status");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Fail to set stream record status");
			AfxMessageBox(szLan);
		}

		for (i=0; i<iItemCount; i++)
		{
			CString strStatus;
			strStatus.Format("%d", *pStatus);
			m_lstStreamRecordStatus.SetItemText(i, 5, strStatus);
			pStatus++;
		}
	}

	UpdateData(FALSE);
}

void CDlgStreamRecordStatus::OnClickListRecordStatus(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nItem = 0;
	CString strChannel;
	
	POSITION pos = m_lstStreamRecordStatus.GetFirstSelectedItemPosition();
	if (pos == NULL)
		TRACE0("No items were selected!\n");
	else
	{
		nItem = m_lstStreamRecordStatus.GetNextSelectedItem(pos);
		
		//显示信息
		m_strStreamID = m_lstStreamRecordStatus.GetItemText(nItem, 1);
		m_strRelatedChannel = m_lstStreamRecordStatus.GetItemText(nItem, 2);
		m_cmbRecordType.SetWindowText(m_lstStreamRecordStatus.GetItemText(nItem, 3));
		m_strRelatedDisc = m_lstStreamRecordStatus.GetItemText(nItem, 4);
		m_strStatus = m_lstStreamRecordStatus.GetItemText(nItem, 5);
		m_bOffLineRecord = atoi(m_lstStreamRecordStatus.GetItemText(nItem, 6));
	
		UpdateData(FALSE);
	}
	*pResult = 0;
}
