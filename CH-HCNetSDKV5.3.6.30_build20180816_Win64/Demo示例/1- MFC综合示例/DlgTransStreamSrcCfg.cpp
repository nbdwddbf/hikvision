// DlgTransStreamSrcCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgTransStreamSrcCfg.h"
#include "DlgVideoIntercomStreamCfg.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTransStreamSrcCfg dialog


CDlgTransStreamSrcCfg::CDlgTransStreamSrcCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTransStreamSrcCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTransStreamSrcCfg)
	m_bEnableChannel = FALSE;
	m_bEnableURL = FALSE;
	m_strChannel = _T("1");
	m_strDomainName = _T("");
	m_strIPAddress = _T("172.9.3.97");
	m_strPassword = _T("12345");
	m_strPort = _T("8000");
	m_strRelatedChannel = _T("-1");
	m_strStreamID = _T("");
	m_strStreamURL = _T("");
	m_strUserName = _T("admin");
	m_strStatus = _T("");
	m_bOnline = FALSE;
	m_bZeroChanel = FALSE;
	m_bChannel = FALSE;
	m_csMediaServerIp = _T("");
	m_csMediaServerPort = _T("");
	//}}AFX_DATA_INIT

	memset(&m_struProtoList, 0, sizeof(NET_DVR_IPC_PROTO_LIST));
	m_hLongCfgHandle = -1;
	m_iCurSelItem = -1;
}


void CDlgTransStreamSrcCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTransStreamSrcCfg)
	DDX_Control(pDX, IDC_COMBO_MEDIA_PROTOCOL, m_comboMediaProtocol);
	DDX_Control(pDX, IDC_COMBO_TRANS_PROTOCOL, m_comboTransProtocol);
	DDX_Control(pDX, IDC_LIST_STREAM_SRC, m_lstStreamSrc);
	DDX_Control(pDX, IDC_COMBO_SRC_TYPE, m_cmbSrcType);
	DDX_Control(pDX, IDC_COMBO_STREAM_TYPE, m_cmbStreamtype);
	DDX_Control(pDX, IDC_COMBO_PROTOCOL_TYPE, m_cmbProtocolType);
	DDX_Check(pDX, IDC_CHECK_ENABLE_CHANNLE, m_bEnableChannel);
	DDX_Check(pDX, IDC_CHECK_ENABLE_URL, m_bEnableURL);
	DDX_Text(pDX, IDC_EDIT_CHANNLE, m_strChannel);
	DDX_Text(pDX, IDC_EDIT_DOMAIN_NAME, m_strDomainName);
	DDX_Text(pDX, IDC_EDIT_IP_ADDRESS, m_strIPAddress);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_PORT, m_strPort);
	DDX_Text(pDX, IDC_EDIT_RELATED_CHANNEL_, m_strRelatedChannel);
	DDX_Text(pDX, IDC_EDIT_STREAM_ID, m_strStreamID);
	DDX_Text(pDX, IDC_EDIT_STREAM_URL, m_strStreamURL);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_strUserName);
	DDX_Text(pDX, IDC_EDIT_STATUS, m_strStatus);
	DDX_Check(pDX, IDC_CHECK_ONLINE, m_bOnline);
	DDX_Check(pDX, IDC_CHK_ZEROCHANNEL, m_bZeroChanel);
	DDX_Check(pDX, IDC_CHK_CHANNEL, m_bChannel);
	DDX_Text(pDX, IDC_EDIT_MEDIA_SERVER_IP, m_csMediaServerIp);
	DDX_Text(pDX, IDC_EDIT_MEDIA_SERVER_PORT, m_csMediaServerPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTransStreamSrcCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgTransStreamSrcCfg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAddStreamID)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDelStreamID)
	ON_NOTIFY(NM_CLICK, IDC_LIST_STREAM_SRC, OnClickListStreamSrc)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGetStreamSrc)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSetStreamSrc)
	ON_CBN_SELCHANGE(IDC_COMBO_SRC_TYPE, OnSelchangeComboSrcType)
	ON_BN_CLICKED(IDC_BUTTON_GET_PROTO_LIST, OnButtonGetProtoList)
	ON_BN_CLICKED(IDC_BTN_GET_ALL, OnBtnGetAll)
	ON_BN_CLICKED(IDC_BTN_DELETE_ALL, OnBtnDeleteAll)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_CHK_CHANNEL, OnChkChannel)
	ON_BN_CLICKED(IDC_BTN_MOD, OnBtnMod)
	ON_BN_CLICKED(IDC_BTN_COPY_TO_ALL, OnBtnCopyToAll)
	ON_BN_CLICKED(IDC_BTN_APPLY_TRANS_CHAN, OnBtnApplyTransChan)
	ON_BN_CLICKED(IDC_BTN_VIDEO_INTERCOM_STREAM, OnBtnVideoIntercomStream)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTransStreamSrcCfg message handlers

BOOL CDlgTransStreamSrcCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);

	// TODO: Add extra initialization here
// 	CRect rc(0, 0, 0, 0);
// 	GetParent()->GetClientRect(&rc);
// 	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
// 	MoveWindow(&rc);
// 
// 
 	m_lstStreamSrc.SetExtendedStyle(m_lstStreamSrc.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	char szLan[128] = {0};
	g_StringLanType(szLan, "序号", "Serial No.");
	m_lstStreamSrc.InsertColumn(0, szLan, LVCFMT_LEFT, 50, -1);

	g_StringLanType(szLan, "流ID", "Stream ID");
	m_lstStreamSrc.InsertColumn(1, szLan, LVCFMT_LEFT, 100, -1);
	
	g_StringLanType(szLan, "关联通道", "Related channel");
	m_lstStreamSrc.InsertColumn(2, szLan, LVCFMT_LEFT, 60, -1);

	g_StringLanType(szLan, "来源方式", "Source type");
	m_lstStreamSrc.InsertColumn(3, szLan, LVCFMT_LEFT, 60, -1);
	
	g_StringLanType(szLan, "是否启用URL", "Enable URL");
	m_lstStreamSrc.InsertColumn(4, szLan, LVCFMT_LEFT, 100, -1);
	
	g_StringLanType(szLan, "URL", "URL");
	m_lstStreamSrc.InsertColumn(5, szLan, LVCFMT_LEFT, 150, -1);

	g_StringLanType(szLan, "是否启用直连通道", "Enable direct connect channel");
	m_lstStreamSrc.InsertColumn(6, szLan, LVCFMT_LEFT, 120, -1);
	
	g_StringLanType(szLan, "厂家类型", "Factory type");
	m_lstStreamSrc.InsertColumn(7, szLan, LVCFMT_LEFT, 60, -1);
	
	g_StringLanType(szLan, "用户名", "User name");
	m_lstStreamSrc.InsertColumn(8, szLan, LVCFMT_LEFT, 50, -1);
	
	g_StringLanType(szLan, "密码", "Password");
	m_lstStreamSrc.InsertColumn(9, szLan, LVCFMT_LEFT, 50, -1);
	
	g_StringLanType(szLan, "域名", "Domain");
	m_lstStreamSrc.InsertColumn(10, szLan, LVCFMT_LEFT, 50, -1);
	
	g_StringLanType(szLan, "IP地址", "IP address");
	m_lstStreamSrc.InsertColumn(11, szLan, LVCFMT_LEFT, 80, -1);

	g_StringLanType(szLan, "端口", "Port");
	m_lstStreamSrc.InsertColumn(12, szLan, LVCFMT_LEFT, 50, -1);
	
	g_StringLanType(szLan, "传输类型", "Stream type");
	m_lstStreamSrc.InsertColumn(13, szLan, LVCFMT_LEFT, 60, -1);
	
	g_StringLanType(szLan, "通道号", "Channel");
	m_lstStreamSrc.InsertColumn(14, szLan, LVCFMT_LEFT, 50, -1);

	g_StringLanType(szLan, "状态", "Status");
	m_lstStreamSrc.InsertColumn(15, szLan, LVCFMT_LEFT, 50, -1);

	g_StringLanType(szLan, "在线", "Online");
	m_lstStreamSrc.InsertColumn(16, szLan, LVCFMT_LEFT, 50, -1);

	g_StringLanType(szLan, "零通道", "Zero Channel");
	m_lstStreamSrc.InsertColumn(17, szLan, LVCFMT_LEFT, 70, -1);

	g_StringLanType(szLan, "取流协议", "Protocol type");
	m_lstStreamSrc.InsertColumn(18, szLan, LVCFMT_LEFT, 80, -1);

	g_StringLanType(szLan, "流媒体IP", "Media server IP");
	m_lstStreamSrc.InsertColumn(19, szLan, LVCFMT_LEFT, 80, -1);

	g_StringLanType(szLan, "流媒体端口", "Media server port");
	m_lstStreamSrc.InsertColumn(20, szLan, LVCFMT_LEFT, 100, -1);

	g_StringLanType(szLan, "流媒体传输协议", "Media server protocol");
	m_lstStreamSrc.InsertColumn(21, szLan, LVCFMT_LEFT, 100, -1);

	m_cmbSrcType.SetCurSel(0);
	m_cmbSrcType.SetItemData(0, 0);
	m_cmbSrcType.SetItemData(1, 4);
	m_cmbStreamtype.SetCurSel(0);
	m_cmbProtocolType.SetCurSel(0);
	m_comboTransProtocol.SetCurSel(0);

	OnSelchangeComboSrcType();

	OnChkChannel();

	m_bEnableURL = FALSE;
	m_bEnableChannel = FALSE;

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTransStreamSrcCfg::OnButtonAddStreamID() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
// 	if ("" == m_strStreamID)
// 	{
// 		g_StringLanType(szLan,"流ID为空","Stream ID is NULL");
// 		AfxMessageBox(szLan);
// 		return;
// 	}

	CString strTemp;
	int iItemCount = m_lstStreamSrc.GetItemCount();
	if (iItemCount > 256)
	{
		g_StringLanType(szLan,"流ID超过256个","Stream ID is more than 256");
		AfxMessageBox(szLan);
		return;
	}
	strTemp.Format("%d", iItemCount+1);
	m_lstStreamSrc.InsertItem(iItemCount, strTemp);
	m_lstStreamSrc.SetItemText(iItemCount, 1, m_strStreamID);
	m_lstStreamSrc.SetItemText(iItemCount, 2, m_strRelatedChannel);
	m_cmbSrcType.GetWindowText(strTemp);
	m_lstStreamSrc.SetItemText(iItemCount, 3, strTemp);
	if (0 == m_cmbSrcType.GetCurSel())
	{
		// 将url部分设为空
		m_lstStreamSrc.SetItemText(iItemCount, 4, "");
		m_lstStreamSrc.SetItemText(iItemCount, 5, "");

		if (TRUE == m_bEnableChannel)
		{
			m_lstStreamSrc.SetItemText(iItemCount, 6, "是");
		}
		else
		{
			m_lstStreamSrc.SetItemText(iItemCount, 6, "否");
		}

		
		strTemp.Format("%d", m_cmbProtocolType.GetItemData(m_cmbProtocolType.GetCurSel()));
		m_lstStreamSrc.SetItemText(iItemCount, 7, strTemp);
		m_lstStreamSrc.SetItemText(iItemCount, 8, m_strUserName);
		m_lstStreamSrc.SetItemText(iItemCount, 9, m_strPassword);
		m_lstStreamSrc.SetItemText(iItemCount, 10, m_strDomainName);
		m_lstStreamSrc.SetItemText(iItemCount, 11, m_strIPAddress);
		m_lstStreamSrc.SetItemText(iItemCount, 12, m_strPort);
		m_cmbStreamtype.GetWindowText(strTemp);
		m_lstStreamSrc.SetItemText(iItemCount, 13, strTemp);
		m_lstStreamSrc.SetItemText(iItemCount, 14, m_strChannel);
		if (m_bZeroChanel)
		{
			g_StringLanType(szLan, "是", "Yes");
		}
		else
		{
			g_StringLanType(szLan, "否", "No");
		}
		m_lstStreamSrc.SetItemText(iItemCount, 17, szLan);
		switch (m_comboTransProtocol.GetCurSel())
		{
		case 0:
			m_lstStreamSrc.SetItemText(iItemCount, 18, "TCP");
			break;
		case 1:
			m_lstStreamSrc.SetItemText(iItemCount, 18, "UDP");
			break;
		case 2:
			g_StringLanType(szLan, "多播", "Multicast");
			m_lstStreamSrc.SetItemText(iItemCount, 18, szLan);
			break;
		default:
			m_lstStreamSrc.SetItemText(iItemCount, 18, "Unknown");
			break;
		}
		
		m_lstStreamSrc.SetItemText(iItemCount, 19, "");
		m_lstStreamSrc.SetItemText(iItemCount, 20, "");
		m_lstStreamSrc.SetItemText(iItemCount, 21, "");
	}
	else if (1 == m_cmbSrcType.GetCurSel())
	{
		if (TRUE == m_bEnableURL)
		{
			m_lstStreamSrc.SetItemText(iItemCount, 4, "是");
		}
		else
		{
			m_lstStreamSrc.SetItemText(iItemCount, 4, "否");
		}

		m_lstStreamSrc.SetItemText(iItemCount, 5, m_strStreamURL);

		// 将直连部分全设为空
		for (int i=6; i<15; i++)
		{
			m_lstStreamSrc.SetItemText(iItemCount, i, "");
		}

		m_lstStreamSrc.SetItemText(iItemCount, 19, "");
		m_lstStreamSrc.SetItemText(iItemCount, 20, "");
		m_lstStreamSrc.SetItemText(iItemCount, 21, "");
	}
	else
	{
		// 将url部分设为空
		m_lstStreamSrc.SetItemText(iItemCount, 4, "");
		m_lstStreamSrc.SetItemText(iItemCount, 5, "");
		
		if (TRUE == m_bEnableChannel)
		{
			m_lstStreamSrc.SetItemText(iItemCount, 6, "是");
		}
		else
		{
			m_lstStreamSrc.SetItemText(iItemCount, 6, "否");
		}
		
		
		strTemp.Format("%d", m_cmbProtocolType.GetItemData(m_cmbProtocolType.GetCurSel()));
		m_lstStreamSrc.SetItemText(iItemCount, 7, strTemp);
		m_lstStreamSrc.SetItemText(iItemCount, 8, m_strUserName);
		m_lstStreamSrc.SetItemText(iItemCount, 9, m_strPassword);
		m_lstStreamSrc.SetItemText(iItemCount, 10, m_strDomainName);
		m_lstStreamSrc.SetItemText(iItemCount, 11, m_strIPAddress);
		m_lstStreamSrc.SetItemText(iItemCount, 12, m_strPort);
		m_cmbStreamtype.GetWindowText(strTemp);
		m_lstStreamSrc.SetItemText(iItemCount, 13, strTemp);
		m_lstStreamSrc.SetItemText(iItemCount, 14, m_strChannel);
		m_lstStreamSrc.SetItemText(iItemCount, 17, "");
// 		if (m_bZeroChanel)
// 		{
// 			g_StringLanType(szLan, "是", "Yes");
// 		}
// 		else
// 		{
// 			g_StringLanType(szLan, "否", "No");
// 		}
// 		m_lstStreamSrc.SetItemText(iItemCount, 17, szLan);
		switch (m_comboTransProtocol.GetCurSel())
		{
		case 0:
			m_lstStreamSrc.SetItemText(iItemCount, 18, "TCP");
			break;
		case 1:
			m_lstStreamSrc.SetItemText(iItemCount, 18, "UDP");
			break;
		case 2:
			g_StringLanType(szLan, "多播", "Multicast");
			m_lstStreamSrc.SetItemText(iItemCount, 18, szLan);
			break;
		default:
			m_lstStreamSrc.SetItemText(iItemCount, 18, "Unknown");
			break;
		}

		m_lstStreamSrc.SetItemText(iItemCount, 19, m_csMediaServerIp);
		m_lstStreamSrc.SetItemText(iItemCount, 20, m_csMediaServerPort);
		if (m_comboMediaProtocol.GetCurSel() == 0)
		{
			m_lstStreamSrc.SetItemText(iItemCount, 21, "TCP");
		}
		else if (m_comboMediaProtocol.GetCurSel() == 1)
		{
			m_lstStreamSrc.SetItemText(iItemCount, 21, "UDP");
		}		
	}
}

void CDlgTransStreamSrcCfg::OnButtonDelStreamID() 
{
	// TODO: Add your control notification handler code here
	POSITION ps = NULL;

	ps = m_lstStreamSrc.GetFirstSelectedItemPosition();
	if (NULL == ps)
	{
		return;
	}

	NET_DVR_STREAM_INFO struStreamInfo = {0};
	NET_DVR_STREAM_SRC_INFO struDelete = {0};

	struStreamInfo.dwSize = sizeof(struStreamInfo);	
	struDelete.dwSize = sizeof(struDelete);
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	LONG lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	DWORD dwStatus = 0;
	int i = 0;
	CString csTemp = "";
	int nItem = -1;
	BOOL bAllSuccess = TRUE;

	while((nItem = m_lstStreamSrc.GetNextSelectedItem(ps)) != -1)
	{
		//int nItem = m_lstStreamSrc.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED);
		struStreamInfo.dwChannel = atoi(m_lstStreamSrc.GetItemText(nItem, 2));
		strncpy((char *)struStreamInfo.byID, m_lstStreamSrc.GetItemText(nItem, 1), STREAM_ID_LEN);

		if (!NET_DVR_SetDeviceConfig(lLoginID, NET_DVR_SET_STREAM_SRC_INFO, 1, &struStreamInfo, sizeof(struStreamInfo), \
			&dwStatus, &struDelete, sizeof(struDelete)))
		{
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_STREAM_SRC_INFO");
			//m_lstStreamSrc.DeleteItem(nItem);
		}
		else
		{
			if (dwStatus == 0 || dwStatus == NET_ERR_NO_STREAM_ID || dwStatus == NET_DVR_CHANNEL_ERROR)
			{
				m_lstStreamSrc.DeleteItem(nItem);
			    m_iCurSelItem = -1;
			}
			else
			{
				CString cs;
				cs.Format("%d", dwStatus);
				bAllSuccess = FALSE;
				m_lstStreamSrc.SetItemText(nItem, 15, cs);
				g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_STREAM_SRC_INFO");
			}
			
			ps = m_lstStreamSrc.GetFirstSelectedItemPosition();
		}		
	}

	for (i = 0; i < m_lstStreamSrc.GetItemCount(); i++)
	{
        csTemp.Format("%d", i + 1);
		m_lstStreamSrc.SetItemText(i, 0, csTemp);		
	}
	
	if (!bAllSuccess)
	{
		AfxMessageBox("Not all success");
	}
}

void CDlgTransStreamSrcCfg::OnClickListStreamSrc(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nItem = 0;
	CString strChannel;
	char szLan[128] = {0};
	
	POSITION pos = m_lstStreamSrc.GetFirstSelectedItemPosition();
	if (pos == NULL)
		TRACE0("No items were selected!\n");
	else
	{
		nItem = m_lstStreamSrc.GetNextSelectedItem(pos);
		m_iCurSelItem = nItem;
		
		//显示信息
		m_strStreamID = m_lstStreamSrc.GetItemText(nItem, 1);
		m_strRelatedChannel = m_lstStreamSrc.GetItemText(nItem, 2);
		if (0 == strcmp("直接取流", m_lstStreamSrc.GetItemText(nItem, 3)))
		{
			m_cmbSrcType.SetCurSel(0);
		}
		else if (0 == strcmp("URL", m_lstStreamSrc.GetItemText(nItem, 3)))
		{
			m_cmbSrcType.SetCurSel(1);
		}
		else if (0 == strcmp("流媒体取流", m_lstStreamSrc.GetItemText(nItem, 3)))
		{
			m_cmbSrcType.SetCurSel(2);
		}
		OnSelchangeComboSrcType();
		//m_cmbSrcType.SetWindowText(m_lstStreamSrc.GetItemText(nItem, 3));
		if (0 == strcmp("是", m_lstStreamSrc.GetItemText(nItem, 4)))
		{
			m_bEnableURL = TRUE;
		}
		else
		{
			m_bEnableURL = FALSE;
		}

		m_strStreamURL = m_lstStreamSrc.GetItemText(nItem, 5);

		if (0 == strcmp("是", m_lstStreamSrc.GetItemText(nItem, 6)))
		{
			m_bEnableChannel = TRUE;
		}
		else
		{
			m_bEnableChannel = FALSE;
		}

//		m_cmbProtocolType.SetWindowText(m_lstStreamSrc.GetItemText(nItem, 7));

		for (int k=0; k<m_struProtoList.dwProtoNum; k++)
		{
			if (m_cmbProtocolType.GetItemData(k) == atoi(m_lstStreamSrc.GetItemText(nItem, 7)))
			{
				m_cmbProtocolType.SetCurSel(k);
				break;				
			}
		}


		m_strUserName = m_lstStreamSrc.GetItemText(nItem, 8);
		m_strPassword = m_lstStreamSrc.GetItemText(nItem, 9);
		m_strDomainName = m_lstStreamSrc.GetItemText(nItem, 10);
		m_strIPAddress = m_lstStreamSrc.GetItemText(nItem, 11);
		m_strPort = m_lstStreamSrc.GetItemText(nItem, 12);
		m_cmbStreamtype.SetWindowText(m_lstStreamSrc.GetItemText(nItem, 13));
		m_strChannel = m_lstStreamSrc.GetItemText(nItem, 14);
		m_strStatus = m_lstStreamSrc.GetItemText(nItem, 15);

		if (0 == strcmp("是", m_lstStreamSrc.GetItemText(nItem, 16)))
		{
			m_bOnline = TRUE;
		}
		else
		{
			m_bOnline = FALSE;
		}
		

		g_StringLanType(szLan, "是", "Yes");
		if (0 == strcmp(szLan, m_lstStreamSrc.GetItemText(nItem, 17)))
		{
			m_bZeroChanel = TRUE;
		}
		else
		{
			m_bZeroChanel = FALSE;
		}

		if (0 == strcmp("TCP", m_lstStreamSrc.GetItemText(nItem, 18)))
		{
			m_comboTransProtocol.SetCurSel(0);			
		}
		else if (0 == strcmp("UDP", m_lstStreamSrc.GetItemText(nItem, 18)))
		{
			m_comboTransProtocol.SetCurSel(1);
		}
		else
		{
			m_comboTransProtocol.SetCurSel(2);
		}

		m_csMediaServerIp = m_lstStreamSrc.GetItemText(nItem, 19);
		m_csMediaServerPort = m_lstStreamSrc.GetItemText(nItem, 20);

		if (0 == strcmp("TCP", m_lstStreamSrc.GetItemText(nItem, 21)))
		{
			m_comboMediaProtocol.SetCurSel(0);			
		}
		else if (0 == strcmp("UDP", m_lstStreamSrc.GetItemText(nItem, 21)))
		{
			m_comboMediaProtocol.SetCurSel(1);
		}
		
		UpdateData(FALSE);
	}
	*pResult = 0;
}

void CDlgTransStreamSrcCfg::OnButtonGetStreamSrc() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    char szLan[128] = {0};
	DWORD dwReturn = 0;
	CString strTemp;
	BOOL bAllSuccess = TRUE;
	int i = 0;

	LPNET_DVR_STREAM_SRC_INFO pStreamSrcInfo = NULL;

	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	LONG lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	
	int iItemCount = m_lstStreamSrc.GetItemCount();
	
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

		pStreamSrcInfo = new(std::nothrow) NET_DVR_STREAM_SRC_INFO;
		if (NULL == pStreamSrcInfo)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pStreamSrcInfo, 0, sizeof(NET_DVR_STREAM_SRC_INFO));

		DWORD dwStatus = 0;

		BOOL bRet = NET_DVR_GetDeviceConfig(lLoginID, NET_DVR_GET_STREAM_SRC_INFO, iItemCount, pstruStreamID, sizeof(NET_DVR_STREAM_INFO), &dwStatus, pStreamSrcInfo, sizeof(NET_DVR_STREAM_SRC_INFO));
		
		if ( bRet && (0 == dwStatus) )
		{
			m_iCurSelItem = -1;
			//g_StringLanType(szLan,"获取流来源成功","Get source success");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "Get Stream Source success");
			//AfxMessageBox(szLan);
		}
		else
		{        
			g_StringLanType(szLan,"获取流来源失败","Fail to Get stream source");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Fail to set stream source");
			AfxMessageBox(szLan);
			return;
		}


		if (0 == pStreamSrcInfo->struStreamSrcInfo.byGetStreamType)
		{
			char szDomianName[MAX_DOMAIN_NAME] = {0};
			char szUserName[NAME_LEN] = {0};
			char szPassword[PASSWD_LEN] = {0};
			char szIP[16] = {0};

			m_cmbSrcType.SetCurSel(0);
			m_bEnableChannel = pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byEnable;
			m_bOnline = pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byOnline;
			for (int k=0; k<m_struProtoList.dwProtoNum; k++)
			{
				if (m_cmbProtocolType.GetItemData(k) == pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType)
				{
					m_cmbProtocolType.SetCurSel(k);
					break;				
				}
			}

			m_cmbStreamtype.SetCurSel(pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byStreamType);
			m_strChannel.Format("%d", pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.dwChannel);
			m_strPort.Format("%d", pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.wDVRPort);
			strncpy(szDomianName, (const char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byDomain, MAX_DOMAIN_NAME-1);
			m_strDomainName.Format("%s", szDomianName);
			strncpy(szUserName, (const char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.sUserName, NAME_LEN);
			m_strUserName.Format("%s", szUserName);
			strncpy(szPassword, (const char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.sPassword, PASSWD_LEN);
			m_strPassword.Format("%s", szPassword);
			strncpy(szIP, (const char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.struIP.sIpV4, 16);
			m_strIPAddress.Format("%s", szIP);
			m_bZeroChanel = pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byZeroChan;
			m_comboTransProtocol.SetCurSel(pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byTransProtocol);
		}
		else if (4 == pStreamSrcInfo->struStreamSrcInfo.byGetStreamType)
		{
			char szURL[256] = {0};
			m_cmbSrcType.SetCurSel(1);
			m_bEnableURL = pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrl.byEnable;
			strncpy(szURL, (const char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrl.strURL, 240);
			m_strStreamURL.Format("%s", szURL);
		}
		else if (6 == pStreamSrcInfo->struStreamSrcInfo.byGetStreamType)
		{
			//char szDomianName[MAX_DOMAIN_NAME] = {0};
			char szUserName[NAME_LEN] = {0};
			char szPassword[PASSWD_LEN] = {0};
			char szIP[64] = {0};
			
			m_cmbSrcType.SetCurSel(0);
			m_bEnableChannel = pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byEnable;
			//m_bOnline = pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byOnline;
			for (int k=0; k<m_struProtoList.dwProtoNum; k++)
			{
				if (m_cmbProtocolType.GetItemData(k) == pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byProType)
				{
					m_cmbProtocolType.SetCurSel(k);
					break;				
				}
			}
			
			m_cmbStreamtype.SetCurSel(pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransMode);
			m_strChannel.Format("%d", pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byChannel);
			m_strPort.Format("%d", pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.wDevPort);
			//strncpy(szDomianName, (const char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byDomain, MAX_DOMAIN_NAME-1);
			//m_strDomainName.Format("%s", szDomianName);
			strncpy(szUserName, (const char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.sUserName, NAME_LEN);
			m_strUserName.Format("%s", szUserName);
			strncpy(szPassword, (const char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.sPassWord, PASSWD_LEN);
			m_strPassword.Format("%s", szPassword);
			strncpy(szIP, (const char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byDevIP, 64);
			m_strIPAddress.Format("%s", szIP);
			//m_bZeroChanel = pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byZeroChan;
			m_comboTransProtocol.SetCurSel(pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransProtocol);

			strncpy(szIP, (const char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byStreamMediaIP, 64);
			m_csMediaServerIp.Format("%s", szIP);
			m_csMediaServerPort.Format("%d", pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.wStreamMediaPort);
			m_comboMediaProtocol.SetCurSel(pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransmitType);
		}
		else
		{
			g_StringLanType(szLan,"源模式暂不支持","Not support this stream source type");
			AfxMessageBox(szLan);
			return;
		}

		m_strStatus.Format("%d", dwStatus);

		delete pstruStreamID;
		pstruStreamID = NULL;
		delete pStreamSrcInfo;
		pStreamSrcInfo = NULL;
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

		// 申请iItemCount个NET_DVR_STREAM_SRC_INFO
		pStreamSrcInfo = new(std::nothrow) NET_DVR_STREAM_SRC_INFO[iItemCount];
		if (NULL == pStreamSrcInfo)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pStreamSrcInfo, 0, iItemCount*sizeof(NET_DVR_STREAM_SRC_INFO));


		for (i=0; i<iItemCount; i++)
		{
		 	pTempStreamID->dwSize = sizeof(NET_DVR_STREAM_INFO);
			strncpy((char*)pTempStreamID->byID, m_lstStreamSrc.GetItemText(i, 1), STREAM_ID_LEN);
		 	pTempStreamID->dwChannel = atoi(m_lstStreamSrc.GetItemText(i, 2));
			pTempStreamID++;
		}

		DWORD *pStatus = new DWORD[iItemCount];
		memset(pStatus, 0, sizeof(DWORD)*iItemCount);
		DWORD *pStatusKeep = pStatus;
		LPNET_DVR_STREAM_SRC_INFO pStreamSrcInfoKeep = pStreamSrcInfo;

		if (NET_DVR_GetDeviceConfig(lLoginID, NET_DVR_GET_STREAM_SRC_INFO, iItemCount, pstruStreamID, iItemCount*sizeof(NET_DVR_STREAM_INFO), pStatus, pStreamSrcInfo, iItemCount*sizeof(NET_DVR_STREAM_SRC_INFO)))
		{
			//g_StringLanType(szLan,"获取流来源成功","Get stream source success");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "Get Stream Source");
			//AfxMessageBox(szLan);
		}
		else
		{        
			g_StringLanType(szLan,"获取流来源失败","Fail to get stream source");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Fail to get stream source");
			AfxMessageBox(szLan);
			delete []pStreamSrcInfo;
			pStreamSrcInfo = NULL;
			delete []pstruStreamID;
			pstruStreamID = NULL;
			delete []pStatus;
			pStatus = NULL;
			return;
		}

		for (i=0; i<iItemCount; i++)
		{
			memcpy(szLan, (pstruStreamID + i)->byID, STREAM_ID_LEN);
			m_lstStreamSrc.SetItemText(i, 1, szLan);
			itoa((pstruStreamID + i)->dwChannel, szLan, 10);
			m_lstStreamSrc.SetItemText(i, 2, szLan);
			
			if (*pStatus == 0)
			{
				if (0 == pStreamSrcInfo->struStreamSrcInfo.byGetStreamType)
				{
					m_lstStreamSrc.SetItemText(i, 3, "直接取流");
					m_lstStreamSrc.SetItemText(i, 4, "");
					m_lstStreamSrc.SetItemText(i, 5, "");
					if (1 == pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byEnable)
					{
						m_lstStreamSrc.SetItemText(i, 6, "是");
					}
					else
					{
						m_lstStreamSrc.SetItemText(i, 6, "否");
					}
					
					CString strTemp;
					strTemp.Format("%d", pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType);
					m_lstStreamSrc.SetItemText(i, 7, strTemp); 
					m_lstStreamSrc.SetItemText(i, 8, (const char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.sUserName);
					m_lstStreamSrc.SetItemText(i, 9, (const char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.sPassword);
					m_lstStreamSrc.SetItemText(i, 10, (const char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byDomain);
					m_lstStreamSrc.SetItemText(i, 11, (const char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.struIP.sIpV4);
					strTemp.Format("%d", pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.wDVRPort);
					m_lstStreamSrc.SetItemText(i, 12, strTemp);
					
					if (0 == pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byStreamType)
					{
						m_lstStreamSrc.SetItemText(i, 13, "主码流");
					}
					else
					{
						m_lstStreamSrc.SetItemText(i, 13, "子码流");
					}
					
					strTemp.Format("%d", pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.dwChannel);
					m_lstStreamSrc.SetItemText(i, 14, strTemp);
					
					if (1 == pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byOnline)
					{
						m_lstStreamSrc.SetItemText(i, 16, "是");
					}
					else
					{
						m_lstStreamSrc.SetItemText(i, 16, "否");
					}
					
					if (1 == pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byZeroChan)
					{
						g_StringLanType(szLan, "是", "Yes");
					}
					else
					{
						g_StringLanType(szLan, "否", "No");
					}
					m_lstStreamSrc.SetItemText(i, 17, szLan);
					
					switch (pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byTransProtocol)
					{
					case 0:
						m_lstStreamSrc.SetItemText(i, 18, "TCP");
						break;
					case 1:
						m_lstStreamSrc.SetItemText(i, 18, "UDP");
						break;
					case 2:
						g_StringLanType(szLan, "多播", "Multicast");
						m_lstStreamSrc.SetItemText(i, 18, szLan);
						break;
						
					default:
						m_lstStreamSrc.SetItemText(i, 18, "Unknown");
						break;
					}
				}
				else if (4 == pStreamSrcInfo->struStreamSrcInfo.byGetStreamType)
				{
					m_lstStreamSrc.SetItemText(i, 3, "URL");
					if (1 == pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrl.byEnable)
					{
						m_lstStreamSrc.SetItemText(i, 4, "是");
					}
					else
					{
						m_lstStreamSrc.SetItemText(i, 4, "否");
					}
					m_lstStreamSrc.SetItemText(i, 5, (const char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrl.strURL);
					for (int j=6; j<19; j++)
					{
						m_lstStreamSrc.SetItemText(i, j, "");
					}
				}
				else if (6 == pStreamSrcInfo->struStreamSrcInfo.byGetStreamType)
				{
					m_lstStreamSrc.SetItemText(i, 3, "流媒体取流");
					m_lstStreamSrc.SetItemText(i, 4, "");
					m_lstStreamSrc.SetItemText(i, 5, "");
					if (1 == pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byEnable)
					{
						m_lstStreamSrc.SetItemText(i, 6, "是");
					}
					else
					{
						m_lstStreamSrc.SetItemText(i, 6, "否");
					}
					
					CString strTemp;
					strTemp.Format("%d", pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byProType);
					m_lstStreamSrc.SetItemText(i, 7, strTemp); 
					m_lstStreamSrc.SetItemText(i, 8, (const char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.sUserName);
					m_lstStreamSrc.SetItemText(i, 9, (const char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.sPassWord);
					//m_lstStreamSrc.SetItemText(i, 10, (const char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byDomain);
					m_lstStreamSrc.SetItemText(i, 11, (const char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byDevIP);
					strTemp.Format("%d", pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.wDevPort);
					m_lstStreamSrc.SetItemText(i, 12, strTemp);
					
					if (0 == pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransMode)
					{
						m_lstStreamSrc.SetItemText(i, 13, "主码流");
					}
					else
					{
						m_lstStreamSrc.SetItemText(i, 13, "子码流");
					}
					
					strTemp.Format("%d", pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byChannel);
					m_lstStreamSrc.SetItemText(i, 14, strTemp);

					m_lstStreamSrc.SetItemText(i, 16, "");				
					
					m_lstStreamSrc.SetItemText(i, 17, "");
					
					switch (pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransProtocol)
					{
					case 0:
						m_lstStreamSrc.SetItemText(i, 18, "TCP");
						break;
					case 1:
						m_lstStreamSrc.SetItemText(i, 18, "UDP");
						break;						
					default:
						m_lstStreamSrc.SetItemText(i, 18, "Unknown");
						break;
					}

					m_lstStreamSrc.SetItemText(i, 19, (const char *)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byStreamMediaIP);
					strTemp.Format("%d", pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.wStreamMediaPort);
					m_lstStreamSrc.SetItemText(i, 20, strTemp);
					switch (pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransmitType)
					{
					case 0:
						m_lstStreamSrc.SetItemText(i, 21, "TCP");
						break;
					case 1:
						m_lstStreamSrc.SetItemText(i, 21, "UDP");
						break;						
					default:
						m_lstStreamSrc.SetItemText(i, 21, "Unknown");
						break;
					}

				}
				else
				{
					g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, "not support this stream source type");
				}
			}
			else
			{
				strTemp.Empty();
				for (int j = 3; j < 22; j++)
				{
					m_lstStreamSrc.SetItemText(i, j, strTemp);
				}
				bAllSuccess = FALSE;
			}
			
			
			CString strStatus;
			strStatus.Format("%d", *pStatus);
			m_lstStreamSrc.SetItemText(i, 15, strStatus);
			
			pStatus++;
			pStreamSrcInfo++;
		}

		delete []pStreamSrcInfoKeep;
		pStreamSrcInfoKeep = NULL;
		delete []pstruStreamID;
		pstruStreamID = NULL;
		delete []pStatusKeep;
		pStatusKeep = NULL;
	}
	
	if (!bAllSuccess)
	{
		g_StringLanType(szLan, "未完全成功，请查看状态值", "Not all success, please check status");
		AfxMessageBox(szLan);
	}
	else
	{
		g_StringLanType(szLan,"获取流来源成功","Get stream source success");		
		AfxMessageBox(szLan);
	}

	UpdateData(FALSE);	
}

void CDlgTransStreamSrcCfg::OnButtonSetStreamSrc() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	BOOL bAllSuccess = TRUE;
    char szLan[128] = {0};
	int i = 0;

	LPNET_DVR_STREAM_SRC_INFO pStreamSrcInfo = NULL;
	LPNET_DVR_STREAM_SRC_INFO pTempSrcInfo = NULL;
	
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	LONG lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	
	int iItemCount = m_lstStreamSrc.GetItemCount();
	
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

		pStreamSrcInfo = new(std::nothrow) NET_DVR_STREAM_SRC_INFO;
		if (NULL == pStreamSrcInfo)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pStreamSrcInfo, 0, sizeof(NET_DVR_STREAM_SRC_INFO));
		pStreamSrcInfo->dwSize = sizeof(NET_DVR_STREAM_SRC_INFO);
		pStreamSrcInfo->struStreamSrcInfo.byGetStreamType = m_cmbSrcType.GetItemData(m_cmbSrcType.GetCurSel());
		if (0 == pStreamSrcInfo->struStreamSrcInfo.byGetStreamType)
		{
			pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byEnable = m_bEnableChannel;
			pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = m_cmbProtocolType.GetItemData(m_cmbProtocolType.GetCurSel());
			pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byStreamType = m_cmbStreamtype.GetCurSel();
			pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.dwChannel = atoi(m_strChannel);
			pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.wDVRPort = atoi(m_strPort);
			strncpy((char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byDomain, m_strDomainName, MAX_DOMAIN_NAME);
			strncpy((char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.sUserName, m_strUserName, NAME_LEN);
			strncpy((char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.sPassword, m_strPassword, PASSWD_LEN);
			strncpy(pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.struIP.sIpV4, m_strIPAddress, 16);
			pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byZeroChan = m_bZeroChanel;
			pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byTransProtocol = m_comboTransProtocol.GetCurSel();			
		}
		else if (4 == pStreamSrcInfo->struStreamSrcInfo.byGetStreamType)
		{
			pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrl.byEnable = m_bEnableURL;
			strncpy((char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrl.strURL, m_strStreamURL, 240);
		}
		else if (6 == pStreamSrcInfo->struStreamSrcInfo.byGetStreamType)
		{
			pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byEnable = m_bEnableChannel;
			pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byProType = m_cmbProtocolType.GetItemData(m_cmbProtocolType.GetCurSel());
			pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransMode = m_cmbStreamtype.GetCurSel();
			pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byChannel = atoi(m_strChannel);
			pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.wDevPort = atoi(m_strPort);
			//strncpy((char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byDomain, m_strDomainName, MAX_DOMAIN_NAME);
			strncpy((char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.sUserName, m_strUserName, NAME_LEN);
			strncpy((char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.sPassWord, m_strPassword, PASSWD_LEN);
			strncpy((char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byDevIP, m_strIPAddress, 64);
			//pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byZeroChan = m_bZeroChanel;
			pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransProtocol = m_comboTransProtocol.GetCurSel();
			
			strncpy((char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byStreamMediaIP, m_csMediaServerIp, 64);
			pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.wDevPort = atoi(m_csMediaServerPort);
			pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransmitType = m_comboMediaProtocol.GetCurSel();
		}
		else
		{
			g_StringLanType(szLan,"源模式暂不支持","Not support this stream source type");
			AfxMessageBox(szLan);
			return;
		}

		DWORD dwStatus = 0xffffffff; 

		BOOL bRet = NET_DVR_SetDeviceConfig(lLoginID, NET_DVR_SET_STREAM_SRC_INFO, iItemCount, pstruStreamID, sizeof(NET_DVR_STREAM_INFO), &dwStatus, pStreamSrcInfo, sizeof(NET_DVR_STREAM_SRC_INFO));
		
	
		if (bRet && (0 == dwStatus))
		{
			g_StringLanType(szLan,"设置流来源成功","Success");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "Set Stream Source");
			AfxMessageBox(szLan);
		}
		else
		{        
			g_StringLanType(szLan,"设置流来源失败","Fail to set stream source");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Fail to set stream source");
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

		// 申请iItemCount个NET_DVR_STREAM_SRC_INFO
		pStreamSrcInfo = new(std::nothrow) NET_DVR_STREAM_SRC_INFO[iItemCount];
		if (NULL == pStreamSrcInfo)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pStreamSrcInfo, 0, iItemCount*sizeof(NET_DVR_STREAM_SRC_INFO));
		pTempSrcInfo = pStreamSrcInfo;

		for (i=0; i<iItemCount; i++)
		{
		 	pTempStreamID->dwSize = sizeof(NET_DVR_STREAM_INFO);
			strncpy((char*)pTempStreamID->byID, m_lstStreamSrc.GetItemText(i, 1), STREAM_ID_LEN);
		 	pTempStreamID->dwChannel = atoi(m_lstStreamSrc.GetItemText(i, 2));
		 	
			pTempSrcInfo->dwSize = sizeof(NET_DVR_STREAM_SRC_INFO);
			if (0 == strcmp("直接取流", m_lstStreamSrc.GetItemText(i, 3)))
			{
				pTempSrcInfo->struStreamSrcInfo.byGetStreamType = 0;
				if (0 == strcmp("是", m_lstStreamSrc.GetItemText(i, 6)))
				{
					pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byEnable = 1;
				}
				else
				{
					pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byEnable = 0;
				}


				pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = atoi(m_lstStreamSrc.GetItemText(i, 7)); 
				strncpy((char*)pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.sUserName, m_lstStreamSrc.GetItemText(i, 8), NAME_LEN);
				strncpy((char*)pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.sPassword, m_lstStreamSrc.GetItemText(i, 9), PASSWD_LEN);
				strncpy((char*)pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byDomain, m_lstStreamSrc.GetItemText(i, 10), MAX_DOMAIN_NAME);
				strncpy((char*)pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.struIP.sIpV4, m_lstStreamSrc.GetItemText(i, 11), 16);
				pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.wDVRPort = atoi(m_lstStreamSrc.GetItemText(i, 12));
				if (0 == strcmp("主码流", m_lstStreamSrc.GetItemText(i, 13)))
				{
					pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byStreamType = 0;
				}
				else
				{
					pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byStreamType = 1;
				}
				pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.dwChannel = atoi(m_lstStreamSrc.GetItemText(i, 14));

				g_StringLanType(szLan, "是", "Yes");
				if (0 == strcmp(szLan, m_lstStreamSrc.GetItemText(i, 17)))
				{
					pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byZeroChan = 1;
				}
				else
				{
					pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byZeroChan = 0;
				}

				g_StringLanType(szLan, "多播", "Multicast");

				if (0 == strcmp("TCP", m_lstStreamSrc.GetItemText(i, 18)))
				{
					pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byTransProtocol = 0;
				}
				else if (0 == strcmp("UDP", m_lstStreamSrc.GetItemText(i, 18)))
				{
					pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byTransProtocol = 1;
				}
				else if (0 == strcmp(szLan, m_lstStreamSrc.GetItemText(i, 18)))
				{
					pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byTransProtocol = 2;
				}
				else
				{
					pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byTransProtocol = 0;					
				}

			}
			else if (0 == strcmp("URL", m_lstStreamSrc.GetItemText(i, 3)))
			{
				pTempSrcInfo->struStreamSrcInfo.byGetStreamType = 4;
				if (0 == strcmp("是", m_lstStreamSrc.GetItemText(i, 4)))
				{
					pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrl.byEnable = 1;
				}
				else
				{
					pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrl.byEnable = 0;
				}
				strncpy((char*)pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrl.strURL, m_lstStreamSrc.GetItemText(i, 5), 240);
			}
			else if (0 == strcmp("流媒体取流", m_lstStreamSrc.GetItemText(i, 3)))
			{
				pTempSrcInfo->struStreamSrcInfo.byGetStreamType = 6;
				if (0 == strcmp("是", m_lstStreamSrc.GetItemText(i, 6)))
				{
					pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byEnable = 1;
				}
				else
				{
					pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byEnable = 0;
				}
				
				
				pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byProType = atoi(m_lstStreamSrc.GetItemText(i, 7)); 
				strncpy((char*)pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.sUserName, m_lstStreamSrc.GetItemText(i, 8), NAME_LEN);
				strncpy((char*)pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.sPassWord, m_lstStreamSrc.GetItemText(i, 9), PASSWD_LEN);
				//strncpy((char*)pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byDomain, m_lstStreamSrc.GetItemText(i, 10), MAX_DOMAIN_NAME);
				strncpy((char*)pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byDevIP, m_lstStreamSrc.GetItemText(i, 11), 64);
				pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.wDevPort = atoi(m_lstStreamSrc.GetItemText(i, 12));
				if (0 == strcmp("主码流", m_lstStreamSrc.GetItemText(i, 13)))
				{
					pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransMode = 0;
				}
				else
				{
					pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransMode = 1;
				}
				pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byChannel = atoi(m_lstStreamSrc.GetItemText(i, 14));
				
				g_StringLanType(szLan, "多播", "Multicast");
				
				if (0 == strcmp("TCP", m_lstStreamSrc.GetItemText(i, 18)))
				{
					pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransProtocol = 0;
				}
				else if (0 == strcmp("UDP", m_lstStreamSrc.GetItemText(i, 18)))
				{
					pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransProtocol = 1;
				}
				else if (0 == strcmp(szLan, m_lstStreamSrc.GetItemText(i, 18)))
				{
					pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransProtocol = 2;
				}
				else
				{
					pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransProtocol = 0;					
				}

				strncpy((char *)pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byStreamMediaIP, m_lstStreamSrc.GetItemText(i, 19), 64);
				pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.wStreamMediaPort = atoi(m_lstStreamSrc.GetItemText(i, 20));
				if (0 == strcmp("TCP", m_lstStreamSrc.GetItemText(i, 21)))
				{
					pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransmitType = 0;
				}
				else if (0 == strcmp("UDP", m_lstStreamSrc.GetItemText(i, 21)))
				{
					pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransmitType = 1;
				}

			}
			else
			{
				g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, "not support this stream source type");
			}
			
			pTempStreamID++;
			pTempSrcInfo++;
		}

		DWORD *pStatus = new(std::nothrow) DWORD[iItemCount];
		memset(pStatus, 0, sizeof(DWORD)*iItemCount);

		if (NET_DVR_SetDeviceConfig(lLoginID, NET_DVR_SET_STREAM_SRC_INFO, iItemCount, pstruStreamID, iItemCount*sizeof(NET_DVR_STREAM_INFO), pStatus, pStreamSrcInfo, iItemCount*sizeof(NET_DVR_STREAM_SRC_INFO)))
		{
			//g_StringLanType(szLan,"设置流来源成功","Success");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "Set Stream Source");
			//AfxMessageBox(szLan);
		}
		else
		{        
			g_StringLanType(szLan,"设置流来源失败","Fail to set stream source");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Fail to set stream source");
			AfxMessageBox(szLan);
			delete []pstruStreamID;
			pstruStreamID = NULL;
			delete []pStreamSrcInfo;
			pStreamSrcInfo = NULL;
			delete []pStatus;
		    pStatus = NULL;
			return;
		}

		DWORD *pTemp = pStatus;
		for (i=0; i<iItemCount; i++)
		{
			if (*pTemp != 0)
			{
				bAllSuccess = FALSE;
			}
			CString strStatus;
			strStatus.Format("%d", *pTemp);
			m_lstStreamSrc.SetItemText(i, 15, strStatus);
			pTemp++;
		}

		delete [] pstruStreamID;
		pstruStreamID = NULL;
		delete [] pStreamSrcInfo;
		pStreamSrcInfo = NULL;
		delete [] pStatus;
		pStatus = NULL;
	}

	if (!bAllSuccess)
	{
		g_StringLanType(szLan, "未完全成功，请查看状态值", "Not all success, please check status");
		AfxMessageBox(szLan);
	}
	else
	{
		g_StringLanType(szLan,"设置流来源成功","Success");
		AfxMessageBox(szLan);
	}

	UpdateData(FALSE);
}

void CDlgTransStreamSrcCfg::OnSelchangeComboSrcType() 
{
	// TODO: Add your control notification handler code here
	if (0 == m_cmbSrcType.GetCurSel())
	{
		GetDlgItem(IDC_EDIT_STREAM_URL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK_ENABLE_URL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_STREAM_URL)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_COMBO_PROTOCOL_TYPE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PROTOCOL_TYPE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_USER_NAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_USER_NAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PASSWORD)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PASSWORD)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CHANNLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_CHANNLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_STREAM_TYPE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_STREAM_TYPE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_DOMAIN_NAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_DOMAIN_NAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_IP_ADDRESS)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_IP_ADDRESS)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PORT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK_ENABLE_CHANNLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHK_ZEROCHANNEL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_TRANS_PROTOCOL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_TRANS_PROTOCOL)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC_MEDIA)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_MEDIA_IP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_MEDIA_PORT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_MEDIA_PROTOCOL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_MEDIA_SERVER_IP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_MEDIA_SERVER_PORT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_MEDIA_PROTOCOL)->ShowWindow(SW_HIDE);
	}
	else if (1 == m_cmbSrcType.GetCurSel())
	{
		GetDlgItem(IDC_EDIT_STREAM_URL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK_ENABLE_URL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_STREAM_URL)->ShowWindow(SW_SHOW);
		
		GetDlgItem(IDC_COMBO_PROTOCOL_TYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PROTOCOL_TYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_USER_NAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_USER_NAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PASSWORD)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PASSWORD)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CHANNLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_CHANNLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_STREAM_TYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_STREAM_TYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_DOMAIN_NAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_DOMAIN_NAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_IP_ADDRESS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_IP_ADDRESS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PORT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK_ENABLE_CHANNLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHK_ZEROCHANNEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_TRANS_PROTOCOL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_TRANS_PROTOCOL)->ShowWindow(SW_HIDE);
		
		GetDlgItem(IDC_STATIC_MEDIA)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_MEDIA_IP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_MEDIA_PORT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_MEDIA_PROTOCOL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_MEDIA_SERVER_IP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_MEDIA_SERVER_PORT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_MEDIA_PROTOCOL)->ShowWindow(SW_HIDE);
		
		GetDlgItem(IDC_STATIC_MEDIA)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_MEDIA_IP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_MEDIA_PORT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_MEDIA_PROTOCOL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_MEDIA_SERVER_IP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_MEDIA_SERVER_PORT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_MEDIA_PROTOCOL)->ShowWindow(SW_HIDE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_STREAM_URL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK_ENABLE_URL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_STREAM_URL)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_COMBO_PROTOCOL_TYPE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PROTOCOL_TYPE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_USER_NAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_USER_NAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PASSWORD)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PASSWORD)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CHANNLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_CHANNLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_STREAM_TYPE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_STREAM_TYPE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_DOMAIN_NAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_DOMAIN_NAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_IP_ADDRESS)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_IP_ADDRESS)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PORT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK_ENABLE_CHANNLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHK_ZEROCHANNEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_TRANS_PROTOCOL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_TRANS_PROTOCOL)->ShowWindow(SW_SHOW);		

		GetDlgItem(IDC_STATIC_MEDIA)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_MEDIA_IP)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_MEDIA_PORT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_MEDIA_PROTOCOL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_MEDIA_SERVER_IP)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_MEDIA_SERVER_PORT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_MEDIA_PROTOCOL)->ShowWindow(SW_SHOW);
	}
}

void CDlgTransStreamSrcCfg::OnButtonGetProtoList() 
{
	// TODO: Add your control notification handler code here
	int i = 0;
	char szLan[1024] = {0};

	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	LONG lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	
	m_cmbProtocolType.ResetContent();
	if (NET_DVR_GetIPCProtoList(lLoginID, &m_struProtoList))
	{
		for (i = 0; i < (int)m_struProtoList.dwProtoNum; i++)
		{
			memset(szLan, 0, DESC_LEN);
			memcpy(szLan, m_struProtoList.struProto[i].byDescribe, DESC_LEN);
			m_cmbProtocolType.AddString(szLan);	
			m_cmbProtocolType.SetItemData(i, m_struProtoList.struProto[i].dwType);
		}
		m_cmbProtocolType.SetCurSel(0);
	}  
	else
	{
		//default	
		m_cmbProtocolType.AddString("0");
		m_cmbProtocolType.SetItemData(0, 0);
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetIPCProtoList");
		//GetDlgItem(IDC_COMBO_PROTYPE)->EnableWindow(TRUE);
	}
	
	m_cmbProtocolType.SetCurSel(0);
}

void CDlgTransStreamSrcCfg::OnBtnGetAll() 
{
	// TODO: Add your control notification handler code here
	int i = 0;
	char szLan[128] = {0};
	char *pRecv = new(std::nothrow) char[RECV_BUF_LEN];

	if (pRecv == NULL)
	{
		g_StringLanType(szLan, "分配接收缓冲区失败", "Alloc receive buffer fail");
		AfxMessageBox(szLan);
		return;
	}

	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	LONG lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;

	if (!NET_DVR_GetDeviceConfig(lLoginID, NET_DVR_GET_ALLSTREAM_SRC_INFO, 0xffffffff, NULL, 0, NULL, pRecv, RECV_BUF_LEN))
	{
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALLSTREAM_SRC_INFO");
		g_StringLanType(szLan, "获取失败", "Get fail");
		AfxMessageBox(szLan);
		return;
	}

	m_lstStreamSrc.DeleteAllItems();

	m_iCurSelItem = -1;
	DWORD dwTotalCount = *((DWORD *)pRecv);
	LPNET_DVR_STREAM_SRC_CFG lpTemp = (LPNET_DVR_STREAM_SRC_CFG)(pRecv + 4);
	CString csTemp;

	for (i = 0; i < dwTotalCount; i++)
	{
		csTemp.Format("%d", i + 1);
		m_lstStreamSrc.InsertItem(i, csTemp);
		m_lstStreamSrc.SetItemText(i, 1, (const char*)lpTemp->struStreamID.byID);
		itoa(lpTemp->struStreamID.dwChannel, (char *)csTemp.GetBuffer(0), 10);
		m_lstStreamSrc.SetItemText(i, 2, csTemp);
		
		if (0 == lpTemp->struStreamSrcInfo.struStreamSrcInfo.byGetStreamType)
		{
			g_StringLanType(szLan, "直接取流", "Direct");
			m_lstStreamSrc.SetItemText(i, 3, szLan);

			g_StringLanType(szLan, "否", "Disable");
			m_lstStreamSrc.SetItemText(i, 4, szLan);

			m_lstStreamSrc.SetItemText(i, 5, "");

			if (1 == lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struChanInfo.byEnable)
			{
				g_StringLanType(szLan, "是", "Enable");
			}
			else
			{
				g_StringLanType(szLan, "否", "Disable");
			}

			m_lstStreamSrc.SetItemText(i, 6, szLan);
			csTemp.Format("%d", lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struChanInfo.byProType);
			m_lstStreamSrc.SetItemText(i, 7, csTemp);
			m_lstStreamSrc.SetItemText(i, 8, (const char *)lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struChanInfo.sUserName);
			m_lstStreamSrc.SetItemText(i, 9, (const char *)lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struChanInfo.sPassword);
			m_lstStreamSrc.SetItemText(i, 10, (const char *)lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struChanInfo.byDomain);
			m_lstStreamSrc.SetItemText(i, 11, (const char *)lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struChanInfo.struIP.sIpV4);

			csTemp.Format("%d", lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struChanInfo.wDVRPort);
			m_lstStreamSrc.SetItemText(i, 12, csTemp);

			if (0 == lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struChanInfo.byStreamType)
			{
				g_StringLanType(szLan, "主码流", "Main stream");
			}
			else if (1 == lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struChanInfo.byStreamType)
			{
				g_StringLanType(szLan, "子码流", "Sub stream");
			}
			m_lstStreamSrc.SetItemText(i, 13, szLan);

			csTemp.Format("%d", lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struChanInfo.dwChannel);
			m_lstStreamSrc.SetItemText(i, 14, csTemp);

			if (1 == lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struChanInfo.byOnline)
			{
				g_StringLanType(szLan, "是", "Yes");
			}
			else
			{
				g_StringLanType(szLan, "否", "No");
			}
			m_lstStreamSrc.SetItemText(i, 16, szLan);

			if (1 == lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struChanInfo.byZeroChan)
			{
				g_StringLanType(szLan, "是", "Yes");
			}
			else
			{
				g_StringLanType(szLan, "否", "No");
			}
			m_lstStreamSrc.SetItemText(i, 17, szLan);

			switch (lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struChanInfo.byTransProtocol)
			{
			case 0:
				m_lstStreamSrc.SetItemText(i, 18, "TCP");
				break;
			case 1:
				m_lstStreamSrc.SetItemText(i, 18, "UDP");
				break;
			case 2:
				g_StringLanType(szLan, "多播", "Multicast");
				m_lstStreamSrc.SetItemText(i, 18, szLan);
				break;
			default:
				m_lstStreamSrc.SetItemText(i, 18, "Unknown");
				break;
			}
		}
		else if (4 == lpTemp->struStreamSrcInfo.struStreamSrcInfo.byGetStreamType)
		{
			m_lstStreamSrc.SetItemText(i, 3, "URL");
			if (1 == lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struStreamUrl.byEnable)
			{
				g_StringLanType(szLan, "是", "Enable");				
			}
			else
			{
				g_StringLanType(szLan, "否", "Disable");
			}
			m_lstStreamSrc.SetItemText(i, 4, szLan);
			m_lstStreamSrc.SetItemText(i, 5, (const char*)lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struStreamUrl.strURL);
			for (int j=6; j<19; j++)
			{
				m_lstStreamSrc.SetItemText(i, j, "");
			}
		}
		else if (6 == lpTemp->struStreamSrcInfo.struStreamSrcInfo.byGetStreamType)
		{
			g_StringLanType(szLan, "流媒体取流", "Media server");
			m_lstStreamSrc.SetItemText(i, 3, szLan);

			g_StringLanType(szLan, "否", "Disable");
			m_lstStreamSrc.SetItemText(i, 4, szLan);
			
			m_lstStreamSrc.SetItemText(i, 5, "");
			
			if (1 == lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struStreamUrlCfg.byEnable)
			{
				g_StringLanType(szLan, "是", "Enable");
			}
			else
			{
				g_StringLanType(szLan, "否", "Disable");
			}
			
			m_lstStreamSrc.SetItemText(i, 6, szLan);
			csTemp.Format("%d", lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struStreamUrlCfg.byProType);
			m_lstStreamSrc.SetItemText(i, 7, csTemp);
			m_lstStreamSrc.SetItemText(i, 8, (const char *)lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struStreamUrlCfg.sUserName);
			m_lstStreamSrc.SetItemText(i, 9, (const char *)lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struStreamUrlCfg.sPassWord);
			//m_lstStreamSrc.SetItemText(i, 10, (const char *)lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struStreamUrlCfg.byDomain);
			m_lstStreamSrc.SetItemText(i, 11, (const char *)lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struStreamUrlCfg.byDevIP);
			
			csTemp.Format("%d", lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struStreamUrlCfg.wDevPort);
			m_lstStreamSrc.SetItemText(i, 12, csTemp);
			
			if (0 == lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransMode)
			{
				g_StringLanType(szLan, "主码流", "Main stream");
			}
			else if (1 == lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransMode)
			{
				g_StringLanType(szLan, "子码流", "Sub stream");
			}
			m_lstStreamSrc.SetItemText(i, 13, szLan);
			
			csTemp.Format("%d", lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struStreamUrlCfg.byChannel);
			m_lstStreamSrc.SetItemText(i, 14, csTemp);
			
// 			if (1 == lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struChanInfo.byOnline)
// 			{
// 				g_StringLanType(szLan, "是", "Yes");
// 			}
// 			else
// 			{
// 				g_StringLanType(szLan, "否", "No");
// 			}
// 			m_lstStreamSrc.SetItemText(i, 16, szLan);
			
// 			if (1 == lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struChanInfo.byZeroChan)
// 			{
// 				g_StringLanType(szLan, "是", "Yes");
// 			}
// 			else
// 			{
// 				g_StringLanType(szLan, "否", "No");
// 			}
// 			m_lstStreamSrc.SetItemText(i, 17, szLan);
			
			switch (lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransProtocol)
			{
			case 0:
				m_lstStreamSrc.SetItemText(i, 18, "TCP");
				break;
			case 1:
				m_lstStreamSrc.SetItemText(i, 18, "UDP");
				break;
			case 2:
				g_StringLanType(szLan, "多播", "Multicast");
				m_lstStreamSrc.SetItemText(i, 18, szLan);
				break;
			default:
				m_lstStreamSrc.SetItemText(i, 18, "Unknown");
				break;
			}

			m_lstStreamSrc.SetItemText(i, 19, (const char*)lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struStreamUrlCfg.byStreamMediaIP);
			csTemp.Format("%d", lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struStreamUrlCfg.wStreamMediaPort);
			m_lstStreamSrc.SetItemText(i, 20, csTemp);
			switch (lpTemp->struStreamSrcInfo.struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransmitType)
			{
			case 0:
				m_lstStreamSrc.SetItemText(i, 21, "TCP");
				break;
			case 1:
				m_lstStreamSrc.SetItemText(i, 21, "UDP");
				break;			
			default:
				m_lstStreamSrc.SetItemText(i, 21, "Unknown");
				break;
			}
		}		
		else
		{
			g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, "not support this stream source type");
		}
		
		csTemp.Format("%d", NET_DVR_NOERROR);
		m_lstStreamSrc.SetItemText(i, 15, csTemp);

		lpTemp++;
	}

	delete []pRecv;
	pRecv = NULL;

	UpdateData(FALSE);
}

void CDlgTransStreamSrcCfg::OnBtnDeleteAll() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	LONG lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;

	if (!NET_DVR_SetDeviceConfig(lLoginID, NET_DVR_SET_STREAM_SRC_INFO, 0xffffffff, NULL, 0, NULL, NULL, 0))
	{
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_STREAM_SRC_INFO");
		g_StringLanType(szLan, "操作失败", "Operate fail");
		AfxMessageBox(szLan);				
	}
	else
	{
		m_iCurSelItem = -1;
		m_lstStreamSrc.DeleteAllItems();
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_STREAM_SRC_INFO");
		UpdateData(FALSE);
		AfxMessageBox("Success");
	}
}

void CDlgTransStreamSrcCfg::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CDlgTransStreamSrcCfg::OnChkChannel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	if (m_bChannel)
	{
		GetDlgItem(IDC_EDIT_STREAM_ID)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_RELATED_CHANNEL_)->EnableWindow(TRUE);
		m_strStreamID.Empty();
	}
	else
	{
		GetDlgItem(IDC_EDIT_STREAM_ID)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_RELATED_CHANNEL_)->EnableWindow(FALSE);
		m_strRelatedChannel = "-1";
	}
	
	UpdateData(FALSE);
}

void CDlgTransStreamSrcCfg::OnBtnMod() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	POSITION ps = m_lstStreamSrc.GetFirstSelectedItemPosition();

	if (ps == NULL)
	{
		return;
	}

	CString strTemp;
	char szLan[128] = {0};
	int iSelItem = -1;
	while((iSelItem = m_lstStreamSrc.GetNextSelectedItem(ps)) != -1)
	{
		if (m_lstStreamSrc.GetSelectedCount() == 1)
		{
			m_lstStreamSrc.SetItemText(iSelItem, 1, m_strStreamID);
		    m_lstStreamSrc.SetItemText(iSelItem, 2, m_strRelatedChannel);
		}
		
		m_cmbSrcType.GetWindowText(strTemp);
		m_lstStreamSrc.SetItemText(iSelItem, 3, strTemp);
		if (0 == m_cmbSrcType.GetCurSel())
		{
			// 将url部分设为空
			m_lstStreamSrc.SetItemText(iSelItem, 4, "");
			m_lstStreamSrc.SetItemText(iSelItem, 5, "");
			//流媒体部分清空
			m_lstStreamSrc.SetItemText(iSelItem, 19, "");
			m_lstStreamSrc.SetItemText(iSelItem, 20, "");
			m_lstStreamSrc.SetItemText(iSelItem, 21, "");
			
			
			if (TRUE == m_bEnableChannel)
			{
				m_lstStreamSrc.SetItemText(iSelItem, 6, "是");
			}
			else
			{
				m_lstStreamSrc.SetItemText(iSelItem, 6, "否");
			}
			
			
			strTemp.Format("%d", m_cmbProtocolType.GetItemData(m_cmbProtocolType.GetCurSel()));
			m_lstStreamSrc.SetItemText(iSelItem, 7, strTemp);
			m_lstStreamSrc.SetItemText(iSelItem, 8, m_strUserName);
			m_lstStreamSrc.SetItemText(iSelItem, 9, m_strPassword);
			m_lstStreamSrc.SetItemText(iSelItem, 10, m_strDomainName);
			m_lstStreamSrc.SetItemText(iSelItem, 11, m_strIPAddress);
			m_lstStreamSrc.SetItemText(iSelItem, 12, m_strPort);
			m_cmbStreamtype.GetWindowText(strTemp);
			m_lstStreamSrc.SetItemText(iSelItem, 13, strTemp);
			m_lstStreamSrc.SetItemText(iSelItem, 14, m_strChannel);
			if (m_bZeroChanel)
			{
				g_StringLanType(szLan, "是", "Yes");
			}
			else
			{
				g_StringLanType(szLan, "否", "No");
			}
			m_lstStreamSrc.SetItemText(iSelItem, 17, szLan);
			switch (m_comboTransProtocol.GetCurSel())
			{
			case 0:
				m_lstStreamSrc.SetItemText(iSelItem, 18, "TCP");
				break;
			case 1:
				m_lstStreamSrc.SetItemText(iSelItem, 18, "UDP");
				break;
			case 2:
				g_StringLanType(szLan, "多播", "Multicast");
				m_lstStreamSrc.SetItemText(iSelItem, 18, szLan);
				break;
			default:
				m_lstStreamSrc.SetItemText(iSelItem, 18, "Unknown");
				break;
			}		
		}
		else if (1 == m_cmbSrcType.GetCurSel())	
		{
			if (TRUE == m_bEnableURL)
			{
				m_lstStreamSrc.SetItemText(iSelItem, 4, "是");
			}
			else
			{
				m_lstStreamSrc.SetItemText(iSelItem, 4, "否");
			}
			
			m_lstStreamSrc.SetItemText(iSelItem, 5, m_strStreamURL);
			
			// 将直连部分全设为空
			for (int i=6; i<15; i++)
			{
				m_lstStreamSrc.SetItemText(iSelItem, i, "");
			}
			//流媒体部分清空
			m_lstStreamSrc.SetItemText(iSelItem, 19, "");
			m_lstStreamSrc.SetItemText(iSelItem, 20, "");
			m_lstStreamSrc.SetItemText(iSelItem, 21, "");
			
		}
		else if (2 == m_cmbSrcType.GetCurSel())
		{
			// 将url部分设为空
			m_lstStreamSrc.SetItemText(iSelItem, 4, "");
			m_lstStreamSrc.SetItemText(iSelItem, 5, "");
			
			if (TRUE == m_bEnableChannel)
			{
				m_lstStreamSrc.SetItemText(iSelItem, 6, "是");
			}
			else
			{
				m_lstStreamSrc.SetItemText(iSelItem, 6, "否");
			}
			
			
			strTemp.Format("%d", m_cmbProtocolType.GetItemData(m_cmbProtocolType.GetCurSel()));
			m_lstStreamSrc.SetItemText(iSelItem, 7, strTemp);
			m_lstStreamSrc.SetItemText(iSelItem, 8, m_strUserName);
			m_lstStreamSrc.SetItemText(iSelItem, 9, m_strPassword);
			//m_lstStreamSrc.SetItemText(iSelItem, 10, m_strDomainName);
			m_lstStreamSrc.SetItemText(iSelItem, 11, m_strIPAddress);
			m_lstStreamSrc.SetItemText(iSelItem, 12, m_strPort);
			m_cmbStreamtype.GetWindowText(strTemp);
			m_lstStreamSrc.SetItemText(iSelItem, 13, strTemp);
			m_lstStreamSrc.SetItemText(iSelItem, 14, m_strChannel);
			// 		if (m_bZeroChanel)
			// 		{
			// 			g_StringLanType(szLan, "是", "Yes");
			// 		}
			// 		else
			// 		{
			// 			g_StringLanType(szLan, "否", "No");
			// 		}
			// 		m_lstStreamSrc.SetItemText(iSelItem, 17, szLan);
			switch (m_comboTransProtocol.GetCurSel())
			{
			case 0:
				m_lstStreamSrc.SetItemText(iSelItem, 18, "TCP");
				break;
			case 1:
				m_lstStreamSrc.SetItemText(iSelItem, 18, "UDP");
				break;
			case 2:
				g_StringLanType(szLan, "多播", "Multicast");
				m_lstStreamSrc.SetItemText(iSelItem, 18, szLan);
				break;
			default:
				m_lstStreamSrc.SetItemText(iSelItem, 18, "Unknown");
				break;
			}
			
			m_lstStreamSrc.SetItemText(iSelItem, 19, m_csMediaServerIp);
			m_lstStreamSrc.SetItemText(iSelItem, 20, m_csMediaServerPort);
			
			switch (m_comboMediaProtocol.GetCurSel())
			{
			case 0:
				m_lstStreamSrc.SetItemText(iSelItem, 21, "TCP");
				break;
			case 1:
				m_lstStreamSrc.SetItemText(iSelItem, 21, "UDP");
				break;		
			default:
				m_lstStreamSrc.SetItemText(iSelItem, 21, "Unknown");
				break;
			}
			
		}		
	}
	//int iSelItem = m_lstStreamSrc.GetNextSelectedItem(ps);	
	
	UpdateData(FALSE);
}


void CDlgTransStreamSrcCfg::GetStreamInfoFromList(LPNET_DVR_STREAM_INFO lpStreamInfo, DWORD *pNum)
{
	if (NULL == lpStreamInfo || NULL == pNum)
	{
		return;
	}

	*pNum = m_lstStreamSrc.GetItemCount() > 256 ? 256 : m_lstStreamSrc.GetItemCount();
	LPNET_DVR_STREAM_INFO lpTemp = lpStreamInfo;
	
	for (int i = 0; i < *pNum; i++)
	{
		lpTemp->dwSize = sizeof(NET_DVR_STREAM_INFO);
		lpTemp->dwChannel = atoi(m_lstStreamSrc.GetItemText(i, 2));
		strncpy((char*)lpTemp->byID, m_lstStreamSrc.GetItemText(i, 1), STREAM_ID_LEN);
		lpTemp++;
	}
}

void CDlgTransStreamSrcCfg::OnBtnCopyToAll() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	POSITION ps = m_lstStreamSrc.GetFirstSelectedItemPosition();
	
	char szLan[128] = {0};	

	if (ps == NULL)
	{
		g_StringLanType(szLan, "请选择一个条目", "Please select a item");
		AfxMessageBox(szLan);
		return;
	}

	int iSelItem = m_lstStreamSrc.GetNextSelectedItem(ps);

	int i,j = 0;

	for (i = 0; i < m_lstStreamSrc.GetItemCount(); i++)
	{
		for (j = 3; j < m_lstStreamSrc.GetHeaderCtrl()->GetItemCount(); j++)
		{
			m_lstStreamSrc.SetItemText(i, j, m_lstStreamSrc.GetItemText(iSelItem, j));
		}
	}	
}

void CDlgTransStreamSrcCfg::OnBtnApplyTransChan() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	char sStreamID[32] = {0};
	DWORD dwChannel = -1;
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	LONG lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;

	if (m_iCurSelItem == -1)
	{
		g_StringLanType(szLan, "请选择一个流ID", "Please select one stream ID");
		AfxMessageBox(szLan);
		return;
	}

	m_lstStreamSrc.GetItemText(m_iCurSelItem, 1, sStreamID, STREAM_ID_LEN);

	if (!NET_DVR_GetDeviceConfig(lLoginID, NET_DVR_APPLY_TRANS_CHAN, 1, sStreamID, STREAM_ID_LEN, NULL, &dwChannel, sizeof(DWORD)))
	{
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_APPLY_TRANS_CHAN");
		g_StringLanType(szLan, "申请失败", "Apply fail");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_APPLY_TRANS_CHAN");
		sprintf(szLan, "Trans channel Num = %d", dwChannel);
		AfxMessageBox(szLan);
	}
}

void CDlgTransStreamSrcCfg::OnBtnVideoIntercomStream() 
{
	// TODO: Add your control notification handler code here
	CDlgVideoIntercomStreamCfg dlg;
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	LONG lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	dlg.m_lServerID = lLoginID;
	dlg.m_iDevIndex = iDeviceIndex;
	dlg.DoModal();
}