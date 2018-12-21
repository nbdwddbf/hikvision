// DlgMonitorInfo.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMonitorInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMonitorInfo dialog
void __stdcall cbRemoteConfigCallback(DWORD dwType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
	CDlgMonitorInfo *pThis = (CDlgMonitorInfo*)pUserData;
	LPNET_DVR_STREAM_INFO lpStreamInfo = NULL;
	CString strTemp;
	int iItemCount = 0;
	switch (dwType)
	{
	case NET_SDK_CALLBACK_TYPE_STATUS:
		g_pMainDlg->AddLog(g_pMainDlg->GetCurDeviceIndex(), OPERATION_SUCC_T, "Get stream id status[%d]", (DWORD)lpBuffer);
		break;
	case NET_SDK_CALLBACK_TYPE_DATA:
		lpStreamInfo = (LPNET_DVR_STREAM_INFO)lpBuffer;
		iItemCount = pThis->m_lstStreamSrc.GetItemCount();
		strTemp.Format("%02d", iItemCount+1);
		pThis->m_lstStreamSrc.InsertItem(iItemCount, strTemp);
		strTemp.Format("%d", lpStreamInfo->dwChannel);
        lpStreamInfo->byID[32] = 0;
		pThis->m_lstStreamSrc.SetItemText(iItemCount, 1, (const char*)lpStreamInfo->byID);
		//pThis->m_lstStreamSrc.SetItemText(iItemCount, 2, strTemp);
		break;
	default:
		break;
		
	}
	
}

CDlgMonitorInfo::CDlgMonitorInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMonitorInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMonitorInfo)
	m_bEnableChannel = FALSE;
	m_bEnableURL = FALSE;
	m_strChannel = _T("");
	m_strDomainName = _T("");
	m_strIPAddress = _T("");
	m_strPassword = _T("");
	m_strPort = _T("");
	m_strRelatedChannel = _T("");
	m_strStatus = _T("");
	m_strStreamID = _T("");
	m_strStreamURL = _T("");
	m_strUserName = _T("");
	m_bEnableCheck = FALSE;
	m_byBlurPoint = 0;
	m_byChromaPoint = 0;
	m_byFreezePoint = 0;
	m_byLumaPoint = 0;
	m_byPtzPoint = 0;
	m_bySignalPoint = 0;
	m_bySnowPoint = 0;
	m_byStreakPoint = 0;
	m_iCount = 0;
	m_csStreamIP = _T("");
	m_iStreamPort = 0;
	m_csDevIP = _T("");
	m_iDevPort = 0;
	m_iListNum = 0;
	m_bMonitorDel = FALSE;
	//}}AFX_DATA_INIT
	memset(&struStreamInfo, 0, sizeof(struStreamInfo));
	m_pStruStreamInfo = NULL;
}


void CDlgMonitorInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMonitorInfo)
	DDX_Control(pDX, IDC_COMBO_ll_PROTORL_DEV, m_cmbDevProtorl);
	DDX_Control(pDX, IDC_COMBO_ll_PROTORL, m_csCmbllProtorl);
	DDX_Control(pDX, IDC_COMBO_DEVTYPE, m_cmbDevType);
	DDX_Control(pDX, IDC_LIST_STREAM_SRC, m_lstStreamSrc);
	DDX_Control(pDX, IDC_COMBO_STREAM_TYPE, m_cmbStreamtype);
	DDX_Control(pDX, IDC_COMBO_SRC_TYPE, m_cmbSrcType);
	DDX_Control(pDX, IDC_COMBO_PROTOCOL_TYPE, m_cmbProtocolType);
	DDX_Check(pDX, IDC_CHECK_ENABLE_CHANNLE, m_bEnableChannel);
	DDX_Check(pDX, IDC_CHECK_ENABLE_URL, m_bEnableURL);
	DDX_Text(pDX, IDC_EDIT_CHANNLE, m_strChannel);
	DDX_Text(pDX, IDC_EDIT_DOMAIN_NAME, m_strDomainName);
	DDX_Text(pDX, IDC_EDIT_IP_ADDRESS, m_strIPAddress);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_PORT, m_strPort);
	DDX_Text(pDX, IDC_EDIT_RELATED_CHANNEL_, m_strRelatedChannel);
	DDX_Text(pDX, IDC_EDIT_STATUS, m_strStatus);
	DDX_Text(pDX, IDC_EDIT_STREAM_ID, m_strStreamID);
	DDX_Text(pDX, IDC_EDIT_STREAM_URL, m_strStreamURL);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_strUserName);
	DDX_Check(pDX, IDC_CHECK_START_CHECK, m_bEnableCheck);
	DDX_Text(pDX, IDC_EDIT_BLUR_POINT, m_byBlurPoint);
	DDX_Text(pDX, IDC_EDIT_CHROMA_POINT, m_byChromaPoint);
	DDX_Text(pDX, IDC_EDIT_FREEZE_POINT, m_byFreezePoint);
	DDX_Text(pDX, IDC_EDIT_LUMA_POINT, m_byLumaPoint);
	DDX_Text(pDX, IDC_EDIT_PTZ_POINT, m_byPtzPoint);
	DDX_Text(pDX, IDC_EDIT_SIGNALPOINT, m_bySignalPoint);
	DDX_Text(pDX, IDC_EDIT_SNOW_POINT, m_bySnowPoint);
	DDX_Text(pDX, IDC_EDIT_STREAK_POINT, m_byStreakPoint);
	DDX_Text(pDX, IDC_EDIT_COUNT, m_iCount);
	DDX_Text(pDX, IDC_EDIT_STREAMIP, m_csStreamIP);
	DDX_Text(pDX, IDC_EDIT_STREAMPORT, m_iStreamPort);
	DDX_Text(pDX, IDC_EDIT_DEVIP, m_csDevIP);
	DDX_Text(pDX, IDC_EDIT_DEVPORT, m_iDevPort);
	DDX_Check(pDX, IDC_CHECK_START_DEL, m_bMonitorDel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMonitorInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgMonitorInfo)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAddStreamID)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDelStreamID)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGetStreamSrc)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSetStreamSrc)
	ON_NOTIFY(NM_CLICK, IDC_LIST_STREAM_SRC, OnClickListStreamSrc)
	ON_CBN_SELCHANGE(IDC_COMBO_SRC_TYPE, OnSelchangeComboSrcType)
	ON_BN_CLICKED(IDC_BTN_GETINFO, OnBtnGetinfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMonitorInfo message handlers

BOOL CDlgMonitorInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
// 	CRect rc(0, 0, 0, 0);
// 	GetParent()->GetClientRect(&rc);
// 	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
// 	MoveWindow(&rc);
	
	m_pStruStreamInfo = new NET_DVR_STREAM_INFO[MAX_ALARMHOST_ALARMOUT_NUM];
	memset(m_pStruStreamInfo, 0, sizeof(NET_DVR_STREAM_INFO)*MAX_ALARMHOST_ALARMOUT_NUM);

	m_lstStreamSrc.SetExtendedStyle(m_lstStreamSrc.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	char szLan[128] = {0};
	g_StringLanType(szLan, "序号", "Serial No.");
	m_lstStreamSrc.InsertColumn(0, szLan, LVCFMT_LEFT, 50, -1);
	
	g_StringLanType(szLan, "流ID", "Stream ID");
	m_lstStreamSrc.InsertColumn(1, szLan, LVCFMT_LEFT, 100, -1);
	
	g_StringLanType(szLan, "关联通道", "Related channel");
	m_lstStreamSrc.InsertColumn(2, szLan, LVCFMT_LEFT, 0, -1);
	
	g_StringLanType(szLan, "来源方式", "Source type");
	m_lstStreamSrc.InsertColumn(3, szLan, LVCFMT_LEFT, 60, -1);
	
	g_StringLanType(szLan, "是否启用URL", "Enable URL");
	m_lstStreamSrc.InsertColumn(4, szLan, LVCFMT_LEFT, 100, -1);
	
	g_StringLanType(szLan, "URL", "URL");
	m_lstStreamSrc.InsertColumn(5, szLan, LVCFMT_LEFT, 0, -1);
	
	g_StringLanType(szLan, "是否启用直连通道", "Enable direct connect channel");
	m_lstStreamSrc.InsertColumn(6, szLan, LVCFMT_LEFT, 120, -1);
	
	g_StringLanType(szLan, "厂商", "Protocol type");
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
	
	g_StringLanType(szLan, "监控点设置状态", "Status");
	m_lstStreamSrc.InsertColumn(15, szLan, LVCFMT_LEFT, 150, -1);
	
	g_StringLanType(szLan, "设备类型", "Status");
	m_lstStreamSrc.InsertColumn(16, szLan, LVCFMT_LEFT, 80, -1);

	g_StringLanType(szLan, "信号丢失阀值", "Status");
	m_lstStreamSrc.InsertColumn(17, szLan, LVCFMT_LEFT, 150, -1);

	g_StringLanType(szLan, "图像模糊阀值", "Status");
	m_lstStreamSrc.InsertColumn(18, szLan, LVCFMT_LEFT, 150, -1);

	g_StringLanType(szLan, "亮度异常阀值", "Status");
	m_lstStreamSrc.InsertColumn(19, szLan, LVCFMT_LEFT, 150, -1);

	g_StringLanType(szLan, "图像偏色阀值", "Status");
	m_lstStreamSrc.InsertColumn(20, szLan, LVCFMT_LEFT, 150, -1);

	g_StringLanType(szLan, "雪花干扰阀值", "Status");
	m_lstStreamSrc.InsertColumn(21, szLan, LVCFMT_LEFT, 150, -1);

	g_StringLanType(szLan, "条纹干扰阀值", "Status");
	m_lstStreamSrc.InsertColumn(22, szLan, LVCFMT_LEFT, 150, -1);

	g_StringLanType(szLan, "画面冻结阀值", "Status");
	m_lstStreamSrc.InsertColumn(23, szLan, LVCFMT_LEFT, 150, -1);

	g_StringLanType(szLan, "云台失控阀值", "Status");
	m_lstStreamSrc.InsertColumn(24, szLan, LVCFMT_LEFT, 150, -1);

	g_StringLanType(szLan, "是否检测", "Status");
	m_lstStreamSrc.InsertColumn(25, szLan, LVCFMT_LEFT, 100, -1);

	g_StringLanType(szLan, "流媒体IP", "StreamIP");
	m_lstStreamSrc.InsertColumn(26, szLan, LVCFMT_LEFT, 100, -1);

	g_StringLanType(szLan, "流媒体端口", "StreamPort");
	m_lstStreamSrc.InsertColumn(27, szLan, LVCFMT_LEFT, 100, -1);

	g_StringLanType(szLan, "设备IP", "DevIP");
	m_lstStreamSrc.InsertColumn(28, szLan, LVCFMT_LEFT, 100, -1);

	g_StringLanType(szLan, "设备端口", "DevPort");
	m_lstStreamSrc.InsertColumn(29, szLan, LVCFMT_LEFT, 100, -1);

	g_StringLanType(szLan, "设备传输协议", "TranProtol");
	m_lstStreamSrc.InsertColumn(30, szLan, LVCFMT_LEFT, 100, -1);

	g_StringLanType(szLan, "流媒体传输协议", "TranProtol");
	m_lstStreamSrc.InsertColumn(31, szLan, LVCFMT_LEFT, 100, -1);

	g_StringLanType(szLan, "是否删除监控点", "TranProtol");
	m_lstStreamSrc.InsertColumn(32, szLan, LVCFMT_LEFT, 100, -1);

	m_cmbSrcType.SetCurSel(0);
	m_cmbSrcType.SetItemData(0, 0);
	m_cmbSrcType.SetItemData(1, 6);
	//m_cmbSrcType.SetItemData(2, 6);
	m_cmbStreamtype.SetCurSel(0);
	m_cmbProtocolType.SetCurSel(0);
	
	OnSelchangeComboSrcType();
	
	m_bEnableURL = FALSE;
	m_bEnableChannel = FALSE;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMonitorInfo::AddStreamInfoToDlg(LPNET_DVR_STREAM_INFO lpInter) 
{	
	CString strTemp;	
	int iItemCount = m_lstStreamSrc.GetItemCount();
	strTemp.Format("%02d", iItemCount+1);
	m_lstStreamSrc.InsertItem(iItemCount, strTemp);
	m_lstStreamSrc.SetItemText(iItemCount, 1, (char *)lpInter->byID);
	strTemp.Format("%02d", lpInter->dwChannel);
	m_lstStreamSrc.SetItemText(iItemCount, 2, strTemp);
}

void CDlgMonitorInfo::OnButtonAddStreamID() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	int iProtocolType = 0;
	int i = 0;
	CString strTemp;	
	int iItemCount = m_lstStreamSrc.GetItemCount();

	for (i = 0; i < iItemCount; i++)
	{
		if (0 == strcmp(m_lstStreamSrc.GetItemText(i, 1), m_strStreamID))
		{
			iItemCount = i;
			m_lstStreamSrc.DeleteItem(i);
		}
	}

	strTemp.Format("%02d", iItemCount+1);
	m_lstStreamSrc.InsertItem(iItemCount, strTemp);
	m_lstStreamSrc.SetItemText(iItemCount, 1, m_strStreamID);
	m_lstStreamSrc.SetItemText(iItemCount, 2, m_strRelatedChannel);
	m_cmbSrcType.GetWindowText(strTemp);
	m_lstStreamSrc.SetItemText(iItemCount, 3, strTemp);
	m_cmbStreamtype.GetWindowText(strTemp);
	m_lstStreamSrc.SetItemText(iItemCount, 13, strTemp);

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
		
		//m_cmbProtocolType.GetWindowText(strTemp);

		iProtocolType = m_cmbProtocolType.GetCurSel();
		if (iProtocolType == 0)
		{
			strTemp = "私有设备";
		}else if (iProtocolType == 1)
		{
			strTemp = "大华设备";
		}else if (iProtocolType == 2)
		{
			strTemp = "汉邦设备";
		}else if (iProtocolType == 3)
		{
			strTemp = "郎驰设备";
		}else if (iProtocolType == 4)
		{
			strTemp = "蓝色星际";
		}
// 		else if (iProtocolType == 5)
// 		{
// 			strTemp = "长虹一体化网络云台";
// 		}else if (iProtocolType == 6)
// 		{
// 			strTemp = "汉邦高科";
// 		}else if (iProtocolType == 7)
// 		{
// 			strTemp = "松下设备";
// 		}else if (iProtocolType == 8)
// 		{
// 			strTemp = "安讯士设备";
// 		}else if (iProtocolType == 9)
// 		{
// 			strTemp = "私有板卡";
// 		}else if (iProtocolType == 10)
// 		{
// 			strTemp = "华三平台设备";
// 		}else if (iProtocolType == 11)
// 		{
// 			strTemp = "蓝色星际";
// 		}else if (iProtocolType == 12)
// 		{
// 			strTemp = "郎驰设备";
// 		}else if (iProtocolType == 13)
// 		{
// 			strTemp = "恒忆设备";
// 		}

		m_lstStreamSrc.SetItemText(iItemCount, 7, strTemp);
		m_lstStreamSrc.SetItemText(iItemCount, 8, m_strUserName);
		m_lstStreamSrc.SetItemText(iItemCount, 9, m_strPassword);
		m_lstStreamSrc.SetItemText(iItemCount, 10, m_strDomainName);
		m_lstStreamSrc.SetItemText(iItemCount, 11, m_strIPAddress);
		m_lstStreamSrc.SetItemText(iItemCount, 12, m_strPort);
// 		m_cmbStreamtype.GetWindowText(strTemp);
// 		m_lstStreamSrc.SetItemText(iItemCount, 13, strTemp);
		m_lstStreamSrc.SetItemText(iItemCount, 14, m_strChannel);
	}
	else
	{
		if (TRUE == m_bEnableURL)
		{
			m_lstStreamSrc.SetItemText(iItemCount, 4, "是");
		}
		else
		{
			m_lstStreamSrc.SetItemText(iItemCount, 4, "否");
		}

		//m_cmbProtocolType.GetWindowText(strTemp);
		iProtocolType = m_cmbProtocolType.GetCurSel();
		if (iProtocolType == 0)
		{
			strTemp = "私有设备";
		}else if (iProtocolType == 1)
		{
			strTemp = "大华设备";
		}else if (iProtocolType == 2)
		{
			strTemp = "汉邦设备";
		}else if (iProtocolType == 3)
		{
			strTemp = "郎驰设备";
		}else if (iProtocolType == 4)
		{
			strTemp = "蓝色星际";
		}
// 		else if (iProtocolType == 5)
// 		{
// 			strTemp = "长虹一体化网络云台";
// 		}else if (iProtocolType == 6)
// 		{
// 			strTemp = "汉邦高科";
// 		}else if (iProtocolType == 7)
// 		{
// 			strTemp = "松下设备";
// 		}else if (iProtocolType == 8)
// 		{
// 			strTemp = "安讯士设备";
// 		}else if (iProtocolType == 9)
// 		{
// 			strTemp = "私有板卡";
// 		}else if (iProtocolType == 10)
// 		{
// 			strTemp = "华三平台设备";
// 		}else if (iProtocolType == 11)
// 		{
// 			strTemp = "蓝色星际";
// 		}else if (iProtocolType == 12)
// 		{
// 			strTemp = "郎驰设备";
// 		}else if (iProtocolType == 13)
// 		{
// 			strTemp = "恒忆设备";
// 		}

		m_lstStreamSrc.SetItemText(iItemCount, 7, strTemp);
		m_lstStreamSrc.SetItemText(iItemCount, 8, m_strUserName);
		m_lstStreamSrc.SetItemText(iItemCount, 9, m_strPassword);
// 		m_cmbStreamtype.GetWindowText(strTemp);
// 		m_lstStreamSrc.SetItemText(iItemCount, 13, strTemp);
		m_lstStreamSrc.SetItemText(iItemCount, 14, m_strChannel);
		m_lstStreamSrc.SetItemText(iItemCount, 26, m_csStreamIP);
		char sStreamPort[8] = {0};
		itoa(m_iStreamPort, sStreamPort, 10); 
		m_lstStreamSrc.SetItemText(iItemCount, 27, sStreamPort);
		m_lstStreamSrc.SetItemText(iItemCount, 28, m_csDevIP);

		char sDevPort[8] = {0};
		itoa(m_iDevPort, sDevPort, 10); 
		m_lstStreamSrc.SetItemText(iItemCount, 29, sDevPort);

		char sTranProtol[8] = {0};
		int jk = m_csCmbllProtorl.GetCurSel();  //流媒体传输协议
		itoa(jk, sTranProtol, 10);
		m_lstStreamSrc.SetItemText(iItemCount, 30, sTranProtol);

		char sTransmitType[8] = {0};
		int jk1 = m_cmbDevProtorl.GetCurSel();  //设备传输协议
		itoa(jk1, sTransmitType, 10);
		m_lstStreamSrc.SetItemText(iItemCount, 31, sTransmitType);

		
		// 将直连部分全设为空
		for (int i=10; i<13; i++)
		{
			m_lstStreamSrc.SetItemText(iItemCount, i, "");
		}
		
	}

	char* devType = "云台摄像机";
	char* devTypeTemp = "非云台摄像机";
	if (0 == m_cmbDevType.GetCurSel())
	{
		m_lstStreamSrc.SetItemText(iItemCount, 16, devTypeTemp);
	} 
	else
	{
		m_lstStreamSrc.SetItemText(iItemCount, 16, devType);
	}

	char* check = "检测";
	char* nocheck = "不检测";
	if (0 == m_bEnableCheck)
	{
		m_lstStreamSrc.SetItemText(iItemCount, 25, nocheck);
	} 
	else
	{
		m_lstStreamSrc.SetItemText(iItemCount, 25, check);
	}

	char* sDel = "删除";
	char* nosDel = "不删除";
	if (0 == m_bMonitorDel)
	{
		m_lstStreamSrc.SetItemText(iItemCount, 32, nosDel);
	} 
	else
	{
		m_lstStreamSrc.SetItemText(iItemCount, 32, sDel);
	}

	char sSignalPoint[8] = {0};
	itoa(m_bySignalPoint, sSignalPoint, 10); 
	m_lstStreamSrc.SetItemText(iItemCount, 17, sSignalPoint);
	
	char sBlurPoint[8] = {0};
	itoa(m_byBlurPoint, sBlurPoint, 10); 
	m_lstStreamSrc.SetItemText(iItemCount, 18, sBlurPoint);

	char sLumaPoint[8] = {0};
	itoa(m_byLumaPoint, sLumaPoint, 10); 
	m_lstStreamSrc.SetItemText(iItemCount, 19, sLumaPoint);

	char sChromaPoint[8] = {0};
	itoa(m_byChromaPoint, sChromaPoint, 10); 
	m_lstStreamSrc.SetItemText(iItemCount, 20, sChromaPoint);

	char sSnowPoint[8] = {0};
	itoa(m_bySnowPoint, sSnowPoint, 10); 
	m_lstStreamSrc.SetItemText(iItemCount, 21, sSnowPoint);

	char sStreakPoint[8] = {0};
	itoa(m_byStreakPoint, sStreakPoint, 10); 
	m_lstStreamSrc.SetItemText(iItemCount, 22, sStreakPoint);

	char sFreezePoint[8] = {0};
	itoa(m_byFreezePoint, sFreezePoint, 10); 
	m_lstStreamSrc.SetItemText(iItemCount, 23, sFreezePoint);

	char sPTZPoint[8] = {0};
	itoa(m_byPtzPoint, sPTZPoint, 10); 
	m_lstStreamSrc.SetItemText(iItemCount, 24, sPTZPoint);
}

void CDlgMonitorInfo::OnButtonDelStreamID() 
{
	// TODO: Add your control notification handler code here
	while(m_lstStreamSrc.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED) != -1)
	{
		int nItem = m_lstStreamSrc.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED);
		m_lstStreamSrc.DeleteItem(nItem);
	}
}

void CDlgMonitorInfo::OnButtonGetStreamSrc() 
{
	// TODO: Add your control notification handler code here
//
	UpdateData(TRUE);
	char szLan[128] = {0};
	DWORD dwReturn = 0;
	CString strTemp;
	char szDomianName[MAX_DOMAIN_NAME] = {0};
	char szUserName[NAME_LEN] = {0};
	char szPassword[PASSWD_LEN] = {0};
	char szIP[16] = {0};
	int i = 0;

	m_lstStreamSrc.DeleteAllItems();
// 	if (m_hLongCfgHandle >= 0)
// 	{
// 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "It is getting data, wait for a moment");
// 	} 
// 	else
	{
		m_hLongCfgHandle = NET_DVR_StartRemoteConfig(m_lServerID, NET_DVR_GET_STREAM_INFO, NULL, 0, cbRemoteConfigCallback, this);
		if (-1 == m_hLongCfgHandle)
		{
			//g_StringLanType(szLan,"获取流信息失败","Fail to get stream info");
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Fail to get stream info");
			return;
		}
		else
		{
			//g_StringLanType(szLan,"获取流信息成功","Get stream info success");
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Get Stream info");
			UpdateData(FALSE);
		}
	}
}

void CDlgMonitorInfo::OnButtonSetStreamSrc() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    char szLan[128] = {0};

	LPNET_DVR_STREAM_SRC_INFO pStreamSrcInfo = NULL;
	LPNET_DVR_STREAM_SRC_INFO pTempSrcInfo = NULL;

	LPNET_DVR_MONITOR_VQDCFG pMonitorVqdCfg = NULL;
	LPNET_DVR_MONITOR_VQDCFG pTempMonitorVqdCfg = NULL;

	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	LONG lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	
	int iItemCount = m_lstStreamSrc.GetItemCount();
	
	LPNET_DVR_STREAM_INFO pstruStreamID = NULL;
	LPNET_DVR_STREAM_INFO pTempStreamID = NULL;

	if (iItemCount < 64)
	{
		// 申请iItemCount个NET_DVR_STREAM_INFO
		pstruStreamID = new NET_DVR_STREAM_INFO[iItemCount];
		if (NULL == pstruStreamID)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pstruStreamID, 0, iItemCount*sizeof(NET_DVR_STREAM_INFO));
		pTempStreamID = pstruStreamID;

		// 申请iItemCount个NET_DVR_STREAM_SRC_INFO
		pStreamSrcInfo = new NET_DVR_STREAM_SRC_INFO[iItemCount];
		if (NULL == pStreamSrcInfo)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pStreamSrcInfo, 0, iItemCount*sizeof(NET_DVR_STREAM_SRC_INFO));
		pTempSrcInfo = pStreamSrcInfo;

		// 申请iItemCount个NET_DVR_MONITOR_VQDCFG
		pMonitorVqdCfg = new NET_DVR_MONITOR_VQDCFG[iItemCount];
		if (NULL == pMonitorVqdCfg)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pMonitorVqdCfg, 0, iItemCount*sizeof(NET_DVR_MONITOR_VQDCFG));
		pTempMonitorVqdCfg = pMonitorVqdCfg;
			
			int i = 0; 
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

					//pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 0; // 目前只支持私有协议
					CString temp= m_lstStreamSrc.GetItemText(i, 7);

					if (0 == strcmp("私有设备", m_lstStreamSrc.GetItemText(i, 7)))
					{
						pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 0;
					}else if (0 == strcmp("大华设备", m_lstStreamSrc.GetItemText(i, 7)))
					{
						pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 1;
					}else if(0 == strcmp("汉邦设备", m_lstStreamSrc.GetItemText(i, 7)))
					{
						pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 2;
					}else if(0 == strcmp("郎驰设备", m_lstStreamSrc.GetItemText(i, 7)))
					{
						pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 3;
					}else if(0 == strcmp("蓝色星际", m_lstStreamSrc.GetItemText(i, 7)))
					{
						pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 4;
					}
// 					else if(0 == strcmp("长虹一体化网络云台", m_lstStreamSrc.GetItemText(i, 7)))
// 					{
// 						pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 5;
// 					}else if(0 == strcmp("汉邦高科", m_lstStreamSrc.GetItemText(i, 7)))
// 					{
// 						pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 6;
// 					}else if(0 == strcmp("松下设备", m_lstStreamSrc.GetItemText(i, 7)))
// 					{
// 						pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 7;
// 					}else if(0 == strcmp("安讯士设备", m_lstStreamSrc.GetItemText(i, 7)))
// 					{
// 						pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 8;
// 					}else if(0 == strcmp("私有板卡", m_lstStreamSrc.GetItemText(i, 7)))
// 					{
// 						pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 9;
// 					}else if(0 == strcmp("华三平台设备", m_lstStreamSrc.GetItemText(i, 7)))
// 					{
// 						pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 10;
// 					}else if(0 == strcmp("蓝色星际", m_lstStreamSrc.GetItemText(i, 7)))
// 					{
// 						pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 11;
// 					}else if(0 == strcmp("郎驰设备", m_lstStreamSrc.GetItemText(i, 7)))
// 					{
// 						pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 12;
// 					}else if(0 == strcmp("恒忆设备", m_lstStreamSrc.GetItemText(i, 7)))
// 					{
// 						pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 13;
// 					}

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

				}
				else if (0 == strcmp("URL", m_lstStreamSrc.GetItemText(i, 3)))
				{
					pTempSrcInfo->struStreamSrcInfo.byGetStreamType = 6;
					if (0 == strcmp("是", m_lstStreamSrc.GetItemText(i, 4)))
					{
						pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byEnable = 1;
					}
					else
					{
						pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byEnable = 0;
					}
					//strncpy((char*)pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrl.strURL, m_lstStreamSrc.GetItemText(i, 5), 240);
					
					if (0 == strcmp("私有设备", m_lstStreamSrc.GetItemText(i, 7)))
					{
						pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byProType = 0;
					}else if (0 == strcmp("大华设备", m_lstStreamSrc.GetItemText(i, 7)))
					{
						pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byProType = 1;
					}else if(0 == strcmp("汉邦设备", m_lstStreamSrc.GetItemText(i, 7)))
					{
						pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byProType = 2;
					}else if(0 == strcmp("郎驰设备", m_lstStreamSrc.GetItemText(i, 7)))
					{
						pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byProType = 3;
					}else if(0 == strcmp("蓝色星际", m_lstStreamSrc.GetItemText(i, 7)))
					{
						pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byProType = 4;
					}
// 					else if(0 == strcmp("长虹一体化网络云台", m_lstStreamSrc.GetItemText(i, 7)))
// 					{
// 						pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlInfo.byProType = 5;
// 					}else if(0 == strcmp("汉邦高科", m_lstStreamSrc.GetItemText(i, 7)))
// 					{
// 						pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlInfo.byProType = 6;
// 					}else if(0 == strcmp("松下设备", m_lstStreamSrc.GetItemText(i, 7)))
// 					{
// 						pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlInfo.byProType = 7;
// 					}else if(0 == strcmp("安讯士设备", m_lstStreamSrc.GetItemText(i, 7)))
// 					{
// 						pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlInfo.byProType = 8;
// 					}else if(0 == strcmp("私有板卡", m_lstStreamSrc.GetItemText(i, 7)))
// 					{
// 						pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlInfo.byProType = 9;
// 					}else if(0 == strcmp("华三平台设备", m_lstStreamSrc.GetItemText(i, 7)))
// 					{
// 						pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlInfo.byProType = 10;
// 					}else if(0 == strcmp("蓝色星际", m_lstStreamSrc.GetItemText(i, 7)))
// 					{
// 						pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlInfo.byProType = 11;
// 					}else if(0 == strcmp("郎驰设备", m_lstStreamSrc.GetItemText(i, 7)))
// 					{
// 						pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlInfo.byProType = 12;
// 					}else if(0 == strcmp("恒忆设备", m_lstStreamSrc.GetItemText(i, 7)))
// 					{
// 						pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlInfo.byProType = 13;
// 					}

					if (0 == strcmp("主码流", m_lstStreamSrc.GetItemText(i, 13)))
					{
						pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransMode = 0;
					}
					else
					{
						pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransMode = 1;
					}

					pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byChannel = atoi(m_lstStreamSrc.GetItemText(i, 14));
					strncpy((char*)pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byDevIP, m_lstStreamSrc.GetItemText(i, 28), 64);
					strncpy((char*)pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byStreamMediaIP, m_lstStreamSrc.GetItemText(i, 26), 64);
					strncpy((char*)pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.sUserName, m_lstStreamSrc.GetItemText(i, 8), NAME_LEN);
					strncpy((char*)pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.sPassWord, m_lstStreamSrc.GetItemText(i, 9), PASSWD_LEN);
					pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.wStreamMediaPort = atoi(m_lstStreamSrc.GetItemText(i, 27));
					pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.wDevPort = atoi(m_lstStreamSrc.GetItemText(i, 29));
					pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransProtocol = atoi(m_lstStreamSrc.GetItemText(i, 30));
					pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransmitType = atoi(m_lstStreamSrc.GetItemText(i, 31));
				}
				else
				{
					g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, "not support this stream source type");
				}
				
				//监控点信息
				pTempMonitorVqdCfg->dwSize = sizeof(NET_DVR_MONITOR_VQDCFG);

				if (0 == strcmp("检测", m_lstStreamSrc.GetItemText(i, 25)))
				{
					pTempMonitorVqdCfg->byEnable = TRUE;
				} 
				else
				{
					pTempMonitorVqdCfg->byEnable = FALSE;
				}
				

				if (0 == strcmp("非云台摄像机", m_lstStreamSrc.GetItemText(i, 16)))
				{
					pTempMonitorVqdCfg->byDevType = 0;
				} 
				else
				{
					pTempMonitorVqdCfg->byDevType = 1;
				}

				BYTE bySignalPoint = atoi(m_lstStreamSrc.GetItemText(i, 17));
				pTempMonitorVqdCfg->bySignalPoint = bySignalPoint;

				BYTE byBlurPoint = atoi(m_lstStreamSrc.GetItemText(i, 18));
				pTempMonitorVqdCfg->byBlurPoint = byBlurPoint;

				BYTE byLumaPoint = atoi(m_lstStreamSrc.GetItemText(i, 19));
				pTempMonitorVqdCfg->byLumaPoint = byLumaPoint;

				BYTE byChromaPoint = atoi(m_lstStreamSrc.GetItemText(i, 20));
				pTempMonitorVqdCfg->byChromaPoint = byChromaPoint;

				BYTE bySnowPoint = atoi(m_lstStreamSrc.GetItemText(i, 21));
				pTempMonitorVqdCfg->bySnowPoint = bySnowPoint;

				BYTE byStreakPoint = atoi(m_lstStreamSrc.GetItemText(i, 22));
				pTempMonitorVqdCfg->byStreakPoint = byStreakPoint;

				BYTE byFreezePoint = atoi(m_lstStreamSrc.GetItemText(i, 23));
				pTempMonitorVqdCfg->byFreezePoint = byFreezePoint;

				BYTE byPTZPoint = atoi(m_lstStreamSrc.GetItemText(i, 24));
				pTempMonitorVqdCfg->byPTZPoint = byPTZPoint;

// 				BYTE byMonitorDel = atoi(m_lstStreamSrc.GetItemText(i, 32));
// 				pTempMonitorVqdCfg->byMonitorDel = byMonitorDel;

				if (0 == strcmp("删除", m_lstStreamSrc.GetItemText(i, 32)))
				{
					pTempMonitorVqdCfg->byMonitorDel = 1;
				} 
				else
				{
					pTempMonitorVqdCfg->byMonitorDel = 0;
				}

				pTempMonitorVqdCfg++;
				pTempStreamID++;
				pTempSrcInfo++;
			}

			DWORD *pStatusStream = new DWORD[iItemCount];
			memset(pStatusStream, 0, sizeof(DWORD)*iItemCount);

			DWORD *pStatus = new DWORD[iItemCount];
			memset(pStatus, 0, sizeof(DWORD)*iItemCount);

			if (NET_DVR_SetDeviceConfig(lLoginID, NET_DVR_SET_STREAM_SRC_INFO, iItemCount, pstruStreamID, iItemCount*sizeof(NET_DVR_STREAM_INFO), pStatusStream, pStreamSrcInfo, iItemCount*sizeof(NET_DVR_STREAM_SRC_INFO)))
			{
				if (NET_DVR_SetDeviceConfig(lLoginID, NET_DVR_SET_MONITOR_VQDCFG, iItemCount, pstruStreamID, iItemCount*sizeof(NET_DVR_STREAM_INFO), pStatus, pMonitorVqdCfg, iItemCount*sizeof(NET_DVR_MONITOR_VQDCFG)))
				{
					g_StringLanType(szLan,"设置监控点信息成功","Success");
					g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "Set Monitor info Success");
					AfxMessageBox(szLan);
				}
			}
			else
			{        
				g_StringLanType(szLan,"设置监控点信息失败","Fail to set Monitor info");
				g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Fail to set Monitor info");
				AfxMessageBox(szLan);
			}
			
			for (i=0; i<iItemCount; i++)
			{
				CString strStatus;
				strStatus.Format("%d", *pStatusStream);
				m_lstStreamSrc.SetItemText(i, 15, strStatus);
				pStatusStream++;
			}

		}
		else
		{
			int iGetCount = 0;
			int iLastCount = 0;
			int iForCount = 0;
			
			if (iItemCount%64 == 0)
			{
				iGetCount = iItemCount/64;
				iForCount = iGetCount;
			} 
			else
			{
				iLastCount = iItemCount%64;
				iGetCount = iItemCount/64;
				iForCount = iGetCount + 1;
			}
			for (int z = 0; z < iForCount; z++)
			{
				if ((z == iGetCount) && iLastCount != 0)
				{
					iItemCount = iLastCount;
				} 
				else
				{
					iItemCount = 64;
				}
				
				// 申请iItemCount个NET_DVR_STREAM_INFO
				pstruStreamID = new NET_DVR_STREAM_INFO[iItemCount];
				if (NULL == pstruStreamID)
				{
					g_StringLanType(szLan,"申请内存失败","new memory failed");
					AfxMessageBox(szLan);
					return;
				}
				memset(pstruStreamID, 0, iItemCount*sizeof(NET_DVR_STREAM_INFO));
				pTempStreamID = pstruStreamID;

				// 申请iItemCount个NET_DVR_STREAM_SRC_INFO
				pStreamSrcInfo = new NET_DVR_STREAM_SRC_INFO[iItemCount];
				if (NULL == pStreamSrcInfo)
				{
					g_StringLanType(szLan,"申请内存失败","new memory failed");
					AfxMessageBox(szLan);
					return;
				}
				memset(pStreamSrcInfo, 0, iItemCount*sizeof(NET_DVR_STREAM_SRC_INFO));
				pTempSrcInfo = pStreamSrcInfo;

				// 申请iItemCount个NET_DVR_MONITOR_VQDCFG
				pMonitorVqdCfg = new NET_DVR_MONITOR_VQDCFG[iItemCount];
				if (NULL == pMonitorVqdCfg)
				{
					g_StringLanType(szLan,"申请内存失败","new memory failed");
					AfxMessageBox(szLan);
					return;
				}
				memset(pMonitorVqdCfg, 0, iItemCount*sizeof(NET_DVR_MONITOR_VQDCFG));
				pTempMonitorVqdCfg = pMonitorVqdCfg;
				
				int i = 0; 
				for (i = 64*z; i < (iItemCount + 64*z); i++)
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

					//	pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 0; // 目前只支持海康协议
						if (0 == strcmp("私有设备", m_lstStreamSrc.GetItemText(i, 7)))
						{
							pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 0;
						}else if (0 == strcmp("大华设备", m_lstStreamSrc.GetItemText(i, 7)))
						{
							pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 1;
						}else if(0 == strcmp("汉邦设备", m_lstStreamSrc.GetItemText(i, 7)))
						{
							pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 2;
						}else if(0 == strcmp("郎驰设备", m_lstStreamSrc.GetItemText(i, 7)))
						{
							pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 3;
						}else if(0 == strcmp("蓝色星际", m_lstStreamSrc.GetItemText(i, 7)))
						{
							pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 4;
						}
// 						else if(0 == strcmp("长虹一体化网络云台", m_lstStreamSrc.GetItemText(i, 7)))
// 						{
// 							pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 5;
// 						}else if(0 == strcmp("汉邦高科", m_lstStreamSrc.GetItemText(i, 7)))
// 						{
// 							pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 6;
// 						}else if(0 == strcmp("松下设备", m_lstStreamSrc.GetItemText(i, 7)))
// 						{
// 							pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 7;
// 						}else if(0 == strcmp("安讯士设备", m_lstStreamSrc.GetItemText(i, 7)))
// 						{
// 							pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 8;
// 						}else if(0 == strcmp("私有板卡", m_lstStreamSrc.GetItemText(i, 7)))
// 						{
// 							pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 9;
// 						}else if(0 == strcmp("华三平台设备", m_lstStreamSrc.GetItemText(i, 7)))
// 						{
// 							pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 10;
// 						}else if(0 == strcmp("蓝色星际", m_lstStreamSrc.GetItemText(i, 7)))
// 						{
// 							pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 11;
// 						}else if(0 == strcmp("郎驰设备", m_lstStreamSrc.GetItemText(i, 7)))
// 						{
// 							pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 12;
// 						}else if(0 == strcmp("恒忆设备", m_lstStreamSrc.GetItemText(i, 7)))
// 						{
// 							pTempSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType = 13;
// 						}

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

					}
					else if (0 == strcmp("URL", m_lstStreamSrc.GetItemText(i, 3)))
					{
						pTempSrcInfo->struStreamSrcInfo.byGetStreamType = 6;
						if (0 == strcmp("是", m_lstStreamSrc.GetItemText(i, 4)))
						{
							pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byEnable = 1;
						}
						else
						{
							pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byEnable = 0;
						}
						//strncpy((char*)pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrl.strURL, m_lstStreamSrc.GetItemText(i, 5), 240);
						
						if (0 == strcmp("私有设备", m_lstStreamSrc.GetItemText(i, 7)))
						{
							pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byProType = 0;
						}else if (0 == strcmp("大华设备", m_lstStreamSrc.GetItemText(i, 7)))
						{
							pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byProType = 1;
						}else if(0 == strcmp("汉邦设备", m_lstStreamSrc.GetItemText(i, 7)))
						{
							pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byProType = 2;
						}else if(0 == strcmp("郎驰设备", m_lstStreamSrc.GetItemText(i, 7)))
						{
							pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byProType = 3;
						}else if(0 == strcmp("蓝色星际", m_lstStreamSrc.GetItemText(i, 7)))
						{
							pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byProType = 4;
						}
// 						else if(0 == strcmp("长虹一体化网络云台", m_lstStreamSrc.GetItemText(i, 7)))
// 						{
// 							pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlInfo.byProType = 5;
// 						}
// 						else if(0 == strcmp("汉邦高科", m_lstStreamSrc.GetItemText(i, 7)))
// 						{
// 							pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlInfo.byProType = 6;
// 						}else if(0 == strcmp("松下设备", m_lstStreamSrc.GetItemText(i, 7)))
// 						{
// 							pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlInfo.byProType = 7;
// 						}else if(0 == strcmp("安讯士设备", m_lstStreamSrc.GetItemText(i, 7)))
// 						{
// 							pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlInfo.byProType = 8;
// 						}else if(0 == strcmp("私有板卡", m_lstStreamSrc.GetItemText(i, 7)))
// 						{
// 							pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlInfo.byProType = 9;
// 						}else if(0 == strcmp("华三平台设备", m_lstStreamSrc.GetItemText(i, 7)))
// 						{
// 							pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlInfo.byProType = 10;
// 						}else if(0 == strcmp("蓝色星际", m_lstStreamSrc.GetItemText(i, 7)))
// 						{
// 							pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlInfo.byProType = 11;
// 						}else if(0 == strcmp("郎驰设备", m_lstStreamSrc.GetItemText(i, 7)))
// 						{
// 							pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlInfo.byProType = 12;
// 						}else if(0 == strcmp("恒忆设备", m_lstStreamSrc.GetItemText(i, 7)))
// 						{
// 							pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlInfo.byProType = 13;
// 						}

						pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byChannel = atoi(m_lstStreamSrc.GetItemText(i, 14));
						strncpy((char*)pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byDevIP, m_lstStreamSrc.GetItemText(i, 28), 64);
						strncpy((char*)pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byStreamMediaIP, m_lstStreamSrc.GetItemText(i, 26), 64);
						strncpy((char*)pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.sUserName, m_lstStreamSrc.GetItemText(i, 8), NAME_LEN);
						strncpy((char*)pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.sPassWord, m_lstStreamSrc.GetItemText(i, 9), PASSWD_LEN);
						pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.wStreamMediaPort = atoi(m_lstStreamSrc.GetItemText(i, 27));
						pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.wDevPort = atoi(m_lstStreamSrc.GetItemText(i, 29));
						pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransProtocol = atoi(m_lstStreamSrc.GetItemText(i, 30));
						pTempSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransmitType = atoi(m_lstStreamSrc.GetItemText(i, 31));
						
					}
					else
					{
						g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, "not support this stream source type");
					}
					
					//监控点信息
					pTempMonitorVqdCfg->dwSize = sizeof(NET_DVR_MONITOR_VQDCFG);

					if (0 == strcmp("检测", m_lstStreamSrc.GetItemText(i, 25)))
					{
						pTempMonitorVqdCfg->byEnable = TRUE;
					} 
					else
					{
						pTempMonitorVqdCfg->byEnable = FALSE;
					}
					

					if (0 == strcmp("非云台摄像机", m_lstStreamSrc.GetItemText(i, 16)))
					{
						pTempMonitorVqdCfg->byDevType = 0;
					} 
					else
					{
						pTempMonitorVqdCfg->byDevType = 1;
					}

					BYTE bySignalPoint = atoi(m_lstStreamSrc.GetItemText(i, 17));
					pTempMonitorVqdCfg->bySignalPoint = bySignalPoint;

					BYTE byBlurPoint = atoi(m_lstStreamSrc.GetItemText(i, 18));
					pTempMonitorVqdCfg->byBlurPoint = byBlurPoint;

					BYTE byLumaPoint = atoi(m_lstStreamSrc.GetItemText(i, 19));
					pTempMonitorVqdCfg->byLumaPoint = byLumaPoint;

					BYTE byChromaPoint = atoi(m_lstStreamSrc.GetItemText(i, 20));
					pTempMonitorVqdCfg->byChromaPoint = byChromaPoint;

					BYTE bySnowPoint = atoi(m_lstStreamSrc.GetItemText(i, 21));
					pTempMonitorVqdCfg->bySnowPoint = bySnowPoint;

					BYTE byStreakPoint = atoi(m_lstStreamSrc.GetItemText(i, 22));
					pTempMonitorVqdCfg->byStreakPoint = byStreakPoint;

					BYTE byFreezePoint = atoi(m_lstStreamSrc.GetItemText(i, 23));
					pTempMonitorVqdCfg->byFreezePoint = byFreezePoint;

					BYTE byPTZPoint = atoi(m_lstStreamSrc.GetItemText(i, 24));
					pTempMonitorVqdCfg->byPTZPoint = byPTZPoint;

					if (0 == strcmp("删除", m_lstStreamSrc.GetItemText(i, 32)))
					{
						pTempMonitorVqdCfg->byMonitorDel = 1;
					} 
					else
					{
						pTempMonitorVqdCfg->byMonitorDel = 0;
					}

					pTempMonitorVqdCfg++;
					pTempStreamID++;
					pTempSrcInfo++;
				}

				DWORD *pStatus = new DWORD[iItemCount];
				memset(pStatus, 0, sizeof(DWORD)*iItemCount);

				DWORD *pStatusStream = new DWORD[iItemCount];
				memset(pStatusStream, 0, sizeof(DWORD)*iItemCount);

				if (NET_DVR_SetDeviceConfig(lLoginID, NET_DVR_SET_STREAM_SRC_INFO, iItemCount, pstruStreamID, iItemCount*sizeof(NET_DVR_STREAM_INFO), pStatusStream, pStreamSrcInfo, iItemCount*sizeof(NET_DVR_STREAM_SRC_INFO)))
				{
					if (NET_DVR_SetDeviceConfig(lLoginID, NET_DVR_SET_MONITOR_VQDCFG, iItemCount, pstruStreamID, iItemCount*sizeof(NET_DVR_STREAM_INFO), pStatus, pMonitorVqdCfg, iItemCount*sizeof(NET_DVR_MONITOR_VQDCFG)))
					{
						g_StringLanType(szLan,"设置监控点信息成功","Success to set Monitor info");
						g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "Success to Monitor info Success");
						AfxMessageBox(szLan);
					}
				}
				else
				{        
					g_StringLanType(szLan,"设置监控点信息失败","Fail to set Monitor info");
					g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Fail to set Monitor info");
					AfxMessageBox(szLan);
				}
				
				for (i=0; i<iItemCount; i++)
				{
					CString strStatus;
					strStatus.Format("%d", *pStatusStream);
					m_lstStreamSrc.SetItemText(i, 15, strStatus);
					pStatusStream++;
				}
			}
		}

	UpdateData(FALSE);
}

void CDlgMonitorInfo::OnClickListStreamSrc(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nItem = 0;
	CString strChannel;
	
	POSITION pos = m_lstStreamSrc.GetFirstSelectedItemPosition();
	if (pos == NULL)
		TRACE0("No items were selected!\n");
	else
	{
		nItem = m_lstStreamSrc.GetNextSelectedItem(pos);
		
		//显示信息
		m_strStreamID = m_lstStreamSrc.GetItemText(nItem, 1);
		m_strRelatedChannel = m_lstStreamSrc.GetItemText(nItem, 2);
		m_cmbSrcType.SetWindowText(m_lstStreamSrc.GetItemText(nItem, 3));
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
		
		m_cmbProtocolType.SetWindowText(m_lstStreamSrc.GetItemText(nItem, 7));
		m_strUserName = m_lstStreamSrc.GetItemText(nItem, 8);
		m_strPassword = m_lstStreamSrc.GetItemText(nItem, 9);
		m_strDomainName = m_lstStreamSrc.GetItemText(nItem, 10);
		m_strIPAddress = m_lstStreamSrc.GetItemText(nItem, 11);
		m_strPort = m_lstStreamSrc.GetItemText(nItem, 12);
		m_cmbStreamtype.SetWindowText(m_lstStreamSrc.GetItemText(nItem, 13));
		m_strChannel = m_lstStreamSrc.GetItemText(nItem, 14);
		m_strStatus = m_lstStreamSrc.GetItemText(nItem, 15);
		
		char* devType = "云台摄像机";
		char* devTypeTemp = "非云台摄像机";
		if (!strcmp(devType, m_lstStreamSrc.GetItemText(nItem, 16)))
		{
			m_cmbDevType.SetCurSel(1);
		}
		else
		{
			m_cmbDevType.SetCurSel(0);
		}
		
		char* check = "检测";
		char* nocheck = "不检测";
		if (!strcmp(check, m_lstStreamSrc.GetItemText(nItem, 25)))
		{
			m_bEnableCheck = TRUE;
		} 
		else
		{
			m_bEnableCheck = FALSE;
		}

		char* sDel = "删除";
		char* nosDel = "不删除";
		if (!strcmp(check, m_lstStreamSrc.GetItemText(nItem, 32)))
		{
			m_bMonitorDel = TRUE;
		} 
		else
		{
			m_bMonitorDel = FALSE;
		}

		CString m_csSignalPoint;
		m_csSignalPoint = m_lstStreamSrc.GetItemText(nItem, 17);
		m_bySignalPoint = _ttoi(m_csSignalPoint);
		
		CString m_csBlurPoint;
		m_csBlurPoint = m_lstStreamSrc.GetItemText(nItem, 18);
		m_byBlurPoint = _ttoi(m_csBlurPoint);

		CString m_csLumaPoint;
		m_csLumaPoint = m_lstStreamSrc.GetItemText(nItem, 19);
		m_byLumaPoint = _ttoi(m_csLumaPoint);

		CString m_csChromaPoint;
		m_csChromaPoint = m_lstStreamSrc.GetItemText(nItem, 20);
		m_byChromaPoint = _ttoi(m_csChromaPoint);

		CString m_csSnowPoint;
		m_csSnowPoint = m_lstStreamSrc.GetItemText(nItem, 21);
		m_bySnowPoint = _ttoi(m_csSnowPoint);

		CString m_csStreakPoint;
		m_csStreakPoint = m_lstStreamSrc.GetItemText(nItem, 22);
		m_byStreakPoint = _ttoi(m_csStreakPoint);

		CString m_csFreezePoint;
		m_csFreezePoint = m_lstStreamSrc.GetItemText(nItem, 23);
		m_byFreezePoint = _ttoi(m_csFreezePoint);

		CString m_csPtzPoint;
		m_csPtzPoint = m_lstStreamSrc.GetItemText(nItem, 24);
		m_byPtzPoint = _ttoi(m_csPtzPoint);

		
		m_csStreamIP = m_lstStreamSrc.GetItemText(nItem, 26);
		m_csDevIP = m_lstStreamSrc.GetItemText(nItem, 28);

		CString m_csStreamPort;
		m_csStreamPort = m_lstStreamSrc.GetItemText(nItem, 27);
		m_iStreamPort = _ttoi(m_csStreamPort);

		CString m_csDevPort;
		m_csDevPort = m_lstStreamSrc.GetItemText(nItem, 27);
		m_iDevPort = _ttoi(m_csDevPort);

		CString m_csTranProto;
		m_csTranProto = m_lstStreamSrc.GetItemText(nItem, 30);
		int kl = _ttoi(m_csTranProto);
		m_csCmbllProtorl.SetCurSel(kl);

		CString m_csTransmitType;
		m_csTransmitType = m_lstStreamSrc.GetItemText(nItem, 31);
		int kl1 = _ttoi(m_csTransmitType);
		m_cmbDevProtorl.SetCurSel(kl1);

		UpdateData(FALSE);
	}
	*pResult = 0;
}

void CDlgMonitorInfo::OnSelchangeComboSrcType() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	if (0 == m_cmbSrcType.GetCurSel())
	{
		GetDlgItem(IDC_EDIT_STREAM_URL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK_ENABLE_URL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_STREAM_URL)->ShowWindow(SW_HIDE);
		
		GetDlgItem(IDC_STATIC_DEVIP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_DEVIP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_DEVPORT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_DEVPORT)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_STREAMIP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_STREAMIP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_STREAMPORT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_STREAMPORT)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_CHALL_POTROL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_ll_PROTORL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_CHALL_POTROL_DEV)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_ll_PROTORL_DEV)->ShowWindow(SW_HIDE);

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
//		GetDlgItem(IDC_STATIC_DOMAIN_NAME)->ShowWindow(SW_SHOW);
//		GetDlgItem(IDC_EDIT_DOMAIN_NAME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_IP_ADDRESS)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_IP_ADDRESS)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PORT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK_ENABLE_CHANNLE)->ShowWindow(SW_SHOW);

		m_cmbProtocolType.ResetContent();
		int iIndex = 0;
		g_StringLanType(szLan, "私有设备", "PRIVATE DEV");
		m_cmbProtocolType.InsertString(iIndex, szLan);
		iIndex++;

		g_StringLanType(szLan, "大华设备", "DAHUA DEV");
		m_cmbProtocolType.InsertString(iIndex, szLan);
		iIndex++;

		g_StringLanType(szLan, "汉邦设备", "HANBANG DEV");
		m_cmbProtocolType.InsertString(iIndex, szLan);
		iIndex++;

		g_StringLanType(szLan, "郎驰设备", "LANGCHI DEV");
		m_cmbProtocolType.InsertString(iIndex, szLan);
		iIndex++;

		g_StringLanType(szLan, "蓝色星际", "BLUE STAR");
		m_cmbProtocolType.InsertString(iIndex, szLan);

	}
	else
	{
		GetDlgItem(IDC_EDIT_STREAM_URL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK_ENABLE_URL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_STREAM_URL)->ShowWindow(SW_HIDE);
		
		GetDlgItem(IDC_STATIC_DEVIP)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_DEVIP)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_DEVPORT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_DEVPORT)->ShowWindow(SW_SHOW);
		
		GetDlgItem(IDC_STATIC_STREAMIP)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_STREAMIP)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_STREAMPORT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_STREAMPORT)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC_CHALL_POTROL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_ll_PROTORL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_CHALL_POTROL_DEV)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_ll_PROTORL_DEV)->ShowWindow(SW_SHOW);

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
//		GetDlgItem(IDC_STATIC_DOMAIN_NAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_DOMAIN_NAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_IP_ADDRESS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_IP_ADDRESS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PORT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CHECK_ENABLE_CHANNLE)->ShowWindow(SW_HIDE);

		m_cmbProtocolType.ResetContent();
		int iIndex = 0;
		g_StringLanType(szLan, "私有设备", "PRIVATE DEV");
		m_cmbProtocolType.InsertString(iIndex, szLan);
		iIndex++;
		
		g_StringLanType(szLan, "大华设备", "DAHUA DEV");
		m_cmbProtocolType.InsertString(iIndex, szLan);
		iIndex++;

	}
}

void CDlgMonitorInfo::OnBtnMonitorInfoAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	CString strTemp;
	int iItemCount = m_lstStreamSrc.GetItemCount();
	if (iItemCount > 64)
	{
		g_StringLanType(szLan,"流ID超过64个","Stream ID is more than 64");
		AfxMessageBox(szLan);
		return;
	}
	strTemp.Format("%s", m_cmbDevType.GetCurSel());
	m_lstStreamSrc.SetItemText(iItemCount, 15, strTemp);
}

void CDlgMonitorInfo::OnBtnMonitorInfoDel() 
{
	// TODO: Add your control notification handler code here
	OnButtonDelStreamID();
}

void CDlgMonitorInfo::OnBtnMonitorInfoSet() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgMonitorInfo::OnBtnMonitorInfoGet() 
{
	// TODO: Add your control notification handler code here
	
}
void CDlgMonitorInfo::ShowVQDList(int iNum,LONG lCount, DWORD *pStatus, LPNET_DVR_STREAM_INFO pstruStreamID,LPNET_DVR_STREAM_SRC_INFO pInputStreamSrcInfo, LPNET_DVR_MONITOR_VQDCFG pInputMonitorInfo)
{
	int iItemNum = lCount;
	int iDelNum = lCount;
	m_iListNum = iNum*64/* + lCount*/;
	int i = 0;
	CString strTemp;
	char szDomianName[MAX_DOMAIN_NAME] = {0};
	char szUserName[NAME_LEN+1] = {0};
	char szPassword[PASSWD_LEN+1] = {0};
	char szIP[16] = {0};

	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	LONG lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	LPNET_DVR_STREAM_SRC_INFO pStreamSrcInfo = pInputStreamSrcInfo;
	LPNET_DVR_MONITOR_VQDCFG pTempMonitorVqdCfg = pInputMonitorInfo;
//	LPNET_DVR_STREAM_INFO pstruStreamID = pstruStreamID;
//  	if (iNum == 0)
//  	{
//		m_lstStreamSrc.DeleteAllItems();
// 	}

	for (int z=0; z<iItemNum; z++)
	{
		//int iItemCount = m_lstStreamSrc.GetItemCount();
		int iItemCount = m_iListNum++;
		m_lstStreamSrc.DeleteItem(iItemCount);
		strTemp.Format("%02d", iItemCount+1);
		m_lstStreamSrc.InsertItem(iItemCount, strTemp);

    	m_lstStreamSrc.SetItemText(iItemCount, 1, (char*)pstruStreamID->byID);
 		m_lstStreamSrc.SetItemText(iItemCount, 2, /*pstruStreamID->dwChannel*/"0");
		m_cmbSrcType.GetWindowText(strTemp);
		m_lstStreamSrc.SetItemText(iItemCount, 3, strTemp);
		i = iItemCount;
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

			if (pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType == 0)
			{
				m_lstStreamSrc.SetItemText(i, 7, "私有设备"); // 目前只支持海康协议
			}else if(pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType == 1)
			{
				m_lstStreamSrc.SetItemText(i, 7, "大华设备");
			}else if(pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType == 2)
			{
				m_lstStreamSrc.SetItemText(i, 7, "汉邦设备");
			}else if (pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType == 3)
			{
				m_lstStreamSrc.SetItemText(i, 7, "郎驰设备");
			}else if(pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType == 4)
			{
				m_lstStreamSrc.SetItemText(i, 7, "蓝色星际");
			}
// 			else if(pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType == 5)
// 			{
// 				m_lstStreamSrc.SetItemText(i, 7, "长虹一体化网络云台");
// 			}else if (pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType == 6)
// 			{
// 				m_lstStreamSrc.SetItemText(i, 7, "汉邦高科");
// 			}else if(pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType == 7)
// 			{
// 				m_lstStreamSrc.SetItemText(i, 7, "安讯士设备");
// 			}else if(pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType == 8)
// 			{
// 				m_lstStreamSrc.SetItemText(i, 7, "私有板卡");
// 			}else if (pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType == 9)
// 			{
// 				m_lstStreamSrc.SetItemText(i, 7, "华三平台设备");
// 			}else if(pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType == 10)
// 			{
// 				m_lstStreamSrc.SetItemText(i, 7, "松下协议");
// 			}else if(pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType == 11)
// 			{
// 				m_lstStreamSrc.SetItemText(i, 7, "蓝色星际");
// 			}else if (pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType == 12)
// 			{
// 				m_lstStreamSrc.SetItemText(i, 7, "郎驰设备");
// 			}else if (pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byProType == 13)
// 			{
// 				m_lstStreamSrc.SetItemText(i, 7, "恒忆设备");
// 			}

			memcpy(szDomianName, (const char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.byDomain, MAX_DOMAIN_NAME-1);
			m_strDomainName.Format("%s", szDomianName);
			memcpy(szUserName, (const char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.sUserName, NAME_LEN);
			m_strUserName.Format("%s", szUserName);
			memcpy(szPassword, (const char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.sPassword, PASSWD_LEN);
			m_strPassword.Format("%s", szPassword);
			memcpy(szIP, (const char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struChanInfo.struIP.sIpV4, 16);
			m_strIPAddress.Format("%s", szIP);

			m_lstStreamSrc.SetItemText(i, 8, m_strUserName);
			m_lstStreamSrc.SetItemText(i, 9, m_strPassword);
			m_lstStreamSrc.SetItemText(i, 10, m_strDomainName);
			m_lstStreamSrc.SetItemText(i, 11, m_strIPAddress);

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
		}
		else if (6 == pStreamSrcInfo->struStreamSrcInfo.byGetStreamType)
		{
			m_lstStreamSrc.SetItemText(i, 3, "URL");
			if (1 == pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byEnable)
			{
				m_lstStreamSrc.SetItemText(i, 4, "是");
			}
			else
			{
				m_lstStreamSrc.SetItemText(i, 4, "否");
			}

			if (pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byProType == 0)
			{
				m_lstStreamSrc.SetItemText(i, 7, "私有设备"); // 目前只支持海康协议
			}else if(pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byProType == 1)
			{
				m_lstStreamSrc.SetItemText(i, 7, "大华设备");
			}else if(pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byProType == 2)
			{
				m_lstStreamSrc.SetItemText(i, 7, "汉邦设备");
			}else if (pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byProType == 3)
			{
				m_lstStreamSrc.SetItemText(i, 7, "郎驰设备");
			}else if(pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byProType == 4)
			{
				m_lstStreamSrc.SetItemText(i, 7, "蓝色星际");
			}
// 			else if(pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlInfo.byProType == 5)
// 			{
// 				m_lstStreamSrc.SetItemText(i, 7, "长虹一体化网络云台");
// 			}
// 			else if (pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlInfo.byProType == 6)
// 			{
// 				m_lstStreamSrc.SetItemText(i, 7, "汉邦高科");
// 			}else if(pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlInfo.byProType == 7)
// 			{
// 				m_lstStreamSrc.SetItemText(i, 7, "安讯士设备");
// 			}else if(pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlInfo.byProType == 8)
// 			{
// 				m_lstStreamSrc.SetItemText(i, 7, "私有板卡");
// 			}else if (pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlInfo.byProType == 9)
// 			{
// 				m_lstStreamSrc.SetItemText(i, 7, "华三平台设备");
// 			}else if(pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlInfo.byProType == 10)
// 			{
// 				m_lstStreamSrc.SetItemText(i, 7, "松下协议");
// 			}else if(pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlInfo.byProType == 11)
// 			{
// 				m_lstStreamSrc.SetItemText(i, 7, "蓝色星际");
// 			}else if (pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlInfo.byProType == 12)
// 			{
// 				m_lstStreamSrc.SetItemText(i, 7, "郎驰设备");
// 			}else if (pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlInfo.byProType == 13)
// 			{
// 				m_lstStreamSrc.SetItemText(i, 7, "恒忆设备");
// 			}

			memcpy(szUserName, (const char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.sUserName, NAME_LEN);
			m_strUserName.Format("%s", szUserName);
			memcpy(szPassword, (const char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.sPassWord, PASSWD_LEN);
			m_strPassword.Format("%s", szPassword);

			m_lstStreamSrc.SetItemText(i, 8, m_strUserName);
			m_lstStreamSrc.SetItemText(i, 9, m_strPassword);

			if (0 == pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransMode)
			{
				m_lstStreamSrc.SetItemText(i, 13, "主码流");
			}
			else
			{
				m_lstStreamSrc.SetItemText(i, 13, "子码流");
			}

			char szChannel[8] = {0};
			itoa(pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byChannel, szChannel, 10); 
			m_lstStreamSrc.SetItemText(iItemCount, 14, szChannel);
			
			char szStreamIP[128] = {0};
			memcpy(szStreamIP, (const char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byStreamMediaIP, 64);
			m_csStreamIP.Format("%s", szStreamIP);
			m_lstStreamSrc.SetItemText(iItemCount, 26, m_csStreamIP);

			char szDevIP[128] = {0};
			memcpy(szDevIP, (const char*)pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byDevIP, 64);
			m_csDevIP.Format("%s", szDevIP);
			m_lstStreamSrc.SetItemText(iItemCount, 28, m_csDevIP);

			char sStreamPort[128] = {0};
			itoa(pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.wStreamMediaPort, sStreamPort, 10);
			m_lstStreamSrc.SetItemText(iItemCount, 27, sStreamPort);			
			
			char sDevPort[128] = {0};
			itoa(pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.wDevPort, sDevPort, 10); 
			m_lstStreamSrc.SetItemText(iItemCount, 29, sDevPort);
			
			char sTranProtol[8] = {0};
			itoa(pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransProtocol, sTranProtol, 10);
			m_lstStreamSrc.SetItemText(iItemCount, 30, sTranProtol);
	
			char sTransmitType[8] = {0};
			itoa(pStreamSrcInfo->struStreamSrcInfo.uGetStream.struStreamUrlCfg.byTransmitType, sTransmitType, 10);
			m_lstStreamSrc.SetItemText(iItemCount, 31, sTransmitType);

			// 将直连部分全设为空
			for (int i=10; i<14; i++)
			{
				m_lstStreamSrc.SetItemText(iItemCount, i, "");
			}

		}

		else
		{
			g_pMainDlg->AddLog(iDeviceIndex, ALARM_INFO_T, "not support this stream source type");
		}
		
		CString strStatus;
		strStatus.Format("%d", *pStatus);
		m_lstStreamSrc.SetItemText(i, 15, strStatus);
		
		char* devType = "云台摄像机";
		char* devTypeTemp = "非云台摄像机";
		if (0 == pTempMonitorVqdCfg->byDevType)
		{
			m_lstStreamSrc.SetItemText(iItemCount, 16, devTypeTemp);
		} 
		else
		{
			m_lstStreamSrc.SetItemText(iItemCount, 16, devType);
		}

		char* check = "检测";
		char* nocheck = "不检测";
		if (0 == pTempMonitorVqdCfg->byEnable)
		{
			m_lstStreamSrc.SetItemText(iItemCount, 25, nocheck);
		} 
		else
		{
			m_lstStreamSrc.SetItemText(iItemCount, 25, check);
		}

		char sSignalPoint[8] = {0};
		itoa(pTempMonitorVqdCfg->bySignalPoint, sSignalPoint, 10); 
		m_lstStreamSrc.SetItemText(iItemCount, 17, sSignalPoint);
		
		char sBlurPoint[8] = {0};
		itoa(pTempMonitorVqdCfg->byBlurPoint, sBlurPoint, 10); 
		m_lstStreamSrc.SetItemText(iItemCount, 18, sBlurPoint);
		
		char sLumaPoint[8] = {0};
		itoa(pTempMonitorVqdCfg->byLumaPoint, sLumaPoint, 10); 
		m_lstStreamSrc.SetItemText(iItemCount, 19, sLumaPoint);
		
		char sChromaPoint[8] = {0};
		itoa(pTempMonitorVqdCfg->byChromaPoint, sChromaPoint, 10); 
		m_lstStreamSrc.SetItemText(iItemCount, 20, sChromaPoint);
		
		char sSnowPoint[8] = {0};
		itoa(pTempMonitorVqdCfg->bySnowPoint, sSnowPoint, 10); 
		m_lstStreamSrc.SetItemText(iItemCount, 21, sSnowPoint);
		
		char sStreakPoint[8] = {0};
		itoa(pTempMonitorVqdCfg->byStreakPoint, sStreakPoint, 10); 
		m_lstStreamSrc.SetItemText(iItemCount, 22, sStreakPoint);
		
		char sFreezePoint[8] = {0};
		itoa(pTempMonitorVqdCfg->byFreezePoint, sFreezePoint, 10); 
		m_lstStreamSrc.SetItemText(iItemCount, 23, sFreezePoint);
		
		char sPTZPoint[8] = {0};
		itoa(pTempMonitorVqdCfg->byPTZPoint, sPTZPoint, 10); 
		m_lstStreamSrc.SetItemText(iItemCount, 24, sPTZPoint);

		pTempMonitorVqdCfg++;
		pStatus++;
		pStreamSrcInfo++;
		pstruStreamID++;
	}
	return;
}

void CDlgMonitorInfo::OnBtnGetinfo() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	int i = 0;
	UpdateData(TRUE);
	LPNET_DVR_STREAM_SRC_INFO pStreamSrcInfo = NULL;

	LPNET_DVR_MONITOR_VQDCFG pMonitorVqdCfg = NULL;
	LPNET_DVR_MONITOR_VQDCFG pTempMonitorVqdCfg = NULL;

	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	LONG lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;
	
	int iItemCount = m_lstStreamSrc.GetItemCount();
	LPNET_DVR_STREAM_INFO pstruStreamID = NULL;
	LPNET_DVR_STREAM_INFO pstruStreamIDTemp = NULL;
	int iCountNum = iItemCount;
	if (iItemCount < 64)
	{
		// 申请iItemCount个NET_DVR_STREAM_INFO
		pstruStreamID = new NET_DVR_STREAM_INFO[iItemCount];
		if (NULL == pstruStreamID)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		pstruStreamIDTemp = pstruStreamID;
		memset(pstruStreamIDTemp, 0, iItemCount*sizeof(NET_DVR_STREAM_INFO));
		for (i=0; i<iItemCount; i++)
		{
			pstruStreamIDTemp->dwSize = sizeof(NET_DVR_STREAM_INFO);
			strncpy((char*)pstruStreamIDTemp->byID, m_lstStreamSrc.GetItemText(i, 1), STREAM_ID_LEN);
			pstruStreamIDTemp->dwChannel = atoi(m_lstStreamSrc.GetItemText(i, 2));
			pstruStreamIDTemp++;
		}
		
		// 申请iItemCount个NET_DVR_STREAM_SRC_INFO
		pStreamSrcInfo = new NET_DVR_STREAM_SRC_INFO[iItemCount];
		if (NULL == pStreamSrcInfo)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pStreamSrcInfo, 0, iItemCount*sizeof(NET_DVR_STREAM_SRC_INFO));
		
		//获取监控点信息 申请iItemCount个NET_DVR_MONITOR_VQDCFG
		pTempMonitorVqdCfg = new NET_DVR_MONITOR_VQDCFG[iItemCount];
		if (NULL == pTempMonitorVqdCfg)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pTempMonitorVqdCfg, 0, iItemCount*sizeof(NET_DVR_MONITOR_VQDCFG));
		
		DWORD *pStatus = new DWORD[iItemCount];
		memset(pStatus, 0, sizeof(DWORD)*iItemCount);

		if (NET_DVR_GetDeviceConfig(lLoginID, NET_DVR_GET_STREAM_SRC_INFO, iItemCount, pstruStreamID, iItemCount*sizeof(NET_DVR_STREAM_INFO), pStatus, pStreamSrcInfo, iItemCount*sizeof(NET_DVR_STREAM_SRC_INFO)))
		{
			if (NET_DVR_GetDeviceConfig(lLoginID, NET_DVR_GET_MONITOR_VQDCFG, iItemCount, pstruStreamID, iItemCount*sizeof(NET_DVR_STREAM_INFO), pStatus, pTempMonitorVqdCfg, iItemCount*sizeof(NET_DVR_MONITOR_VQDCFG)))
			{
				//g_StringLanType(szLan,"获取监控点信息成功","Get Monitor Info success");
				g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "Get Monitor Info success");
				//AfxMessageBox(szLan);
			}
		}
		else
		{        
			g_StringLanType(szLan,"获取监控点信息失败","Fail to Get Monitor Info");
			g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Fail to Get Monitor Info");
			AfxMessageBox(szLan);
			return;
		}

		ShowVQDList(0,iItemCount, pStatus, pstruStreamID, pStreamSrcInfo, pTempMonitorVqdCfg);
		UpdateData(FALSE);
		return;

	}
	else
	{
		int iGetCount = 0;
		int iLastCount = 0;
		int iForCount = 0;

		if (iItemCount%64 == 0)
		{
			iGetCount = iItemCount/64;
			iForCount = iGetCount;
		} 
		else
		{
			iLastCount = iItemCount%64;
			iGetCount = iItemCount/64;
			iForCount = iGetCount + 1;
		}

		for (int z = 0; z < iForCount; z++)
		{
			int j = 0;
			if ((z == iGetCount) && iLastCount != 0)
			{
				iItemCount = iLastCount;
			} 
			else
			{
				iItemCount = 64;
			}
			
			pstruStreamID = new NET_DVR_STREAM_INFO[iItemCount];
			if (NULL == pstruStreamID)
			{
				g_StringLanType(szLan,"申请内存失败","new memory failed");
				AfxMessageBox(szLan);
				return;
			}
			memset(pstruStreamID, 0, iItemCount*sizeof(NET_DVR_STREAM_INFO));
			pstruStreamIDTemp = pstruStreamID;
			for (i = 64*z; i < (iItemCount + 64*z) ; i++)
			{
				pstruStreamIDTemp->dwSize = sizeof(NET_DVR_STREAM_INFO);
				strncpy((char*)pstruStreamIDTemp->byID, m_lstStreamSrc.GetItemText(/*64*z +*/ i, 1), STREAM_ID_LEN);
				pstruStreamIDTemp->dwChannel = atoi(m_lstStreamSrc.GetItemText(/*64*z + */i, 2));
				pstruStreamIDTemp++;
			}

			// 申请iItemCount个NET_DVR_STREAM_SRC_INFO
			pStreamSrcInfo = new NET_DVR_STREAM_SRC_INFO[iItemCount];
			if (NULL == pStreamSrcInfo)
			{
				g_StringLanType(szLan,"申请内存失败","new memory failed");
				AfxMessageBox(szLan);
				return;
			}
			memset(pStreamSrcInfo, 0, iItemCount*sizeof(NET_DVR_STREAM_SRC_INFO));
			
			//获取监控点信息 申请iItemCount个NET_DVR_MONITOR_VQDCFG
			pTempMonitorVqdCfg = new NET_DVR_MONITOR_VQDCFG[iItemCount];
			if (NULL == pTempMonitorVqdCfg)
			{
				g_StringLanType(szLan,"申请内存失败","new memory failed");
				AfxMessageBox(szLan);
				return;
			}
			memset(pTempMonitorVqdCfg, 0, iItemCount*sizeof(NET_DVR_MONITOR_VQDCFG));
			
			DWORD *pStatus = new DWORD[iItemCount];
			memset(pStatus, 0, sizeof(DWORD)*iItemCount);
			
			if (NET_DVR_GetDeviceConfig(lLoginID, NET_DVR_GET_STREAM_SRC_INFO, iItemCount, pstruStreamID, iItemCount*sizeof(NET_DVR_STREAM_INFO), pStatus, pStreamSrcInfo, iItemCount*sizeof(NET_DVR_STREAM_SRC_INFO)))
			{
				if (NET_DVR_GetDeviceConfig(lLoginID, NET_DVR_GET_MONITOR_VQDCFG, iItemCount, pstruStreamID, iItemCount*sizeof(NET_DVR_STREAM_INFO), pStatus, pTempMonitorVqdCfg, iItemCount*sizeof(NET_DVR_MONITOR_VQDCFG)))
				{
					//g_StringLanType(szLan,"获取监控点信息成功","Get Monitor Info success");
					g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "Get Monitor Info success");
					//AfxMessageBox(szLan);
				}
			}
			else
			{        
				g_StringLanType(szLan,"获取监控点信息失败","Fail to Get Monitor Info");
				g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Fail to Get Monitor Info");
				AfxMessageBox(szLan);
				return;
			}		

			ShowVQDList(z,iItemCount, pStatus, pstruStreamID, pStreamSrcInfo, pTempMonitorVqdCfg);
			
			//return;
		}
		UpdateData(FALSE);
	}
}
