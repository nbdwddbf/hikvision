// DlgStreamSrcCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgStreamSrcCfg.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgStreamSrcCfg dialog


CDlgStreamSrcCfg::CDlgStreamSrcCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStreamSrcCfg::IDD, pParent)
    , m_strMonitorName(_T(""))
{
	//{{AFX_DATA_INIT(CDlgStreamSrcCfg)
	m_bEnableChannel = FALSE;
	m_bEnableURL = FALSE;
	m_strChannel = _T("");
	m_strDomainName = _T("");
	m_strPassword = _T("");
	m_strPort = _T("");
	m_strRelatedChannel = _T("");
	m_strStreamID = _T("");
	m_strStreamURL = _T("");
	m_strUserName = _T("");
	m_strStatus = _T("");
	m_bEnableRTSPPro = FALSE;
	m_bLocalBackUp = FALSE;
	m_strDeviceName = _T("");
	m_strRtspPasswd = _T("");
	m_strRtspUserName = _T("");
	m_strRtspStreamID = _T("");
	m_bChanStatus = FALSE;
	m_bEnableUrlMore = FALSE;
	m_bBackupUrlMore = FALSE;
	m_wPortUrlMore = 0;
	m_bRtspBackUp = FALSE;

    memset(&m_struStreamSrcInfo, 0,sizeof(m_struStreamSrcInfo));
    m_iCurSelectItem = -1;
    memset(&m_struProList, 0,sizeof(m_struProList));
	//}}AFX_DATA_INIT
}


void CDlgStreamSrcCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgStreamSrcCfg)

    DDX_Control(pDX, IDC_COMBO_STREAM_TYPE, m_cmbStreamType);
    DDX_Control(pDX, IDC_LIST_STREAM_SRC, m_lstStreamSrc);
    DDX_Control(pDX, IDC_COMBO_SRC_TYPE, m_cmbSrcType);
    DDX_Control(pDX, IDC_COMBO_STREAM_TYPE, m_cmbStreamType);
    DDX_Control(pDX, IDC_COMBO_PROTOCOL_TYPE, m_cmbProtocolType);
    DDX_Check(pDX, IDC_CHECK_ENABLE_CHANNLE, m_bEnableChannel);
    DDX_Check(pDX, IDC_CHECK_ENABLE_URL, m_bEnableURL);
    DDX_Text(pDX, IDC_EDIT_CHANNLE, m_strChannel);
    DDX_Text(pDX, IDC_EDIT_DOMAIN_NAME, m_strDomainName);
    DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
    DDX_Text(pDX, IDC_EDIT_PORT, m_strPort);
    DDX_Text(pDX, IDC_EDIT_RELATED_CHANNEL_, m_strRelatedChannel);
    DDX_Text(pDX, IDC_EDIT_STREAM_ID, m_strStreamID);
    DDX_Text(pDX, IDC_EDIT_STREAM_URL, m_strStreamURL);
    DDX_Text(pDX, IDC_EDIT_USER_NAME, m_strUserName);
    DDX_Check(pDX, IDC_CHK_ENABLE_RTSPPRO, m_bEnableRTSPPro);
    DDX_Check(pDX, IDC_CHK_LOCAL_BACKUP, m_bLocalBackUp);
    DDX_Text(pDX, IDC_EDIT_DEVICENAME, m_strDeviceName);
    DDX_Check(pDX, IDC_CHK_CHAN_STATUS, m_bChanStatus);
    DDX_Check(pDX, IDC_CHECK_ENABLE_URL_MORE, m_bEnableUrlMore);
    DDX_Check(pDX, IDC_CHK_LOCAL_BACKUP_URLMORE, m_bBackupUrlMore);
    DDX_Check(pDX, IDC_CHK_LOCAL_BACKUP_RTSP, m_bRtspBackUp);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_MONITOR_NAME, m_strMonitorName);
}


BEGIN_MESSAGE_MAP(CDlgStreamSrcCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgStreamSrcCfg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAddStreamID)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDelStreamID)
	ON_NOTIFY(NM_CLICK, IDC_LIST_STREAM_SRC, OnClickListStreamSrc)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGetStreamSrc)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSetStreamSrc)
	ON_CBN_SELCHANGE(IDC_COMBO_SRC_TYPE, OnSelchangeComboSrcType)
	ON_BN_CLICKED(IDC_BTN_MODE, OnBtnMode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgStreamSrcCfg message handlers

BOOL CDlgStreamSrcCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);


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
    
    g_StringLanType(szLan, "启用", "Enable");
    m_lstStreamSrc.InsertColumn(4, szLan, LVCFMT_LEFT, 60, -1);
    
    g_StringLanType(szLan, "URL", "URL");
    m_lstStreamSrc.InsertColumn(5, szLan, LVCFMT_LEFT, 120, -1);
    
    g_StringLanType(szLan, "协议类型", "Protocol type");
    m_lstStreamSrc.InsertColumn(6, szLan, LVCFMT_LEFT, 60, -1);
    
    g_StringLanType(szLan, "码流类型", "Stream type");
    m_lstStreamSrc.InsertColumn(7, szLan, LVCFMT_LEFT, 60, -1);
    
    g_StringLanType(szLan, "用户名", "User name");
    m_lstStreamSrc.InsertColumn(8, szLan, LVCFMT_LEFT, 50, -1);
    
    g_StringLanType(szLan, "密码", "Password");
    m_lstStreamSrc.InsertColumn(9, szLan, LVCFMT_LEFT, 50, -1);
    
    g_StringLanType(szLan, "域名", "Domain");
    m_lstStreamSrc.InsertColumn(10, szLan, LVCFMT_LEFT, 50, -1);
    
    g_StringLanType(szLan, "端口", "Port");
    m_lstStreamSrc.InsertColumn(11, szLan, LVCFMT_LEFT, 50, -1);
    
    g_StringLanType(szLan, "通道号", "Channel");
    m_lstStreamSrc.InsertColumn(12, szLan, LVCFMT_LEFT, 50, -1);
    
    g_StringLanType(szLan, "通道编号", "Chan No");
    m_lstStreamSrc.InsertColumn(13, szLan, LVCFMT_LEFT, 80, -1);
    
    
    g_StringLanType(szLan, "状态", "Status");
    m_lstStreamSrc.InsertColumn(14, szLan, LVCFMT_LEFT, 50, -1);
    
    g_StringLanType(szLan, "本地备份", "Local BackUp");
	m_lstStreamSrc.InsertColumn(15, szLan, LVCFMT_LEFT,50, -1);

    g_StringLanType(szLan, "监控点名称", "Monitor Name");
    m_lstStreamSrc.InsertColumn(16, szLan, LVCFMT_LEFT, 120, -1);

    //Get Dev Support Protocol List
    AddProtocalList();   
	m_cmbSrcType.SetCurSel(0);
	m_cmbSrcType.SetItemData(0, 0);
	m_cmbSrcType.SetItemData(1, 4);
	m_cmbStreamType.SetCurSel(0);
	m_cmbProtocolType.SetCurSel(0);

   
	ShowUnionInfo(0);


    //IDC_COMBO_PROTOCOL_TYPE

	m_bEnableURL = FALSE;
	m_bEnableChannel = FALSE;

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgStreamSrcCfg::OnButtonAddStreamID() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    
	int iItemCount = m_lstStreamSrc.GetItemCount();
	AddStreamInfoToList(iItemCount);
}

void CDlgStreamSrcCfg::OnButtonDelStreamID() 
{
	// TODO: Add your control notification handler code here
	while(m_lstStreamSrc.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED) != -1)
	{
		int nItem = m_lstStreamSrc.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED);
		m_lstStreamSrc.DeleteItem(nItem);
	}
	
}

void CDlgStreamSrcCfg::OnClickListStreamSrc(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nItem = 0;
	CString strChannel;
    int iProtocalData = -1;
    CString strTemp = "";
	
	POSITION pos = m_lstStreamSrc.GetFirstSelectedItemPosition();
	if (pos == NULL)
    {
        TRACE0("No items were selected!\n");
        
        m_iCurSelectItem = -1;
    }
	else
	{
        nItem = m_lstStreamSrc.GetNextSelectedItem(pos);
        m_iCurSelectItem = nItem;

        //show relate Info
        m_strStreamID = m_lstStreamSrc.GetItemText(nItem, 1);
        m_strRelatedChannel = m_lstStreamSrc.GetItemText(nItem, 2);
        m_cmbSrcType.SetWindowText(m_lstStreamSrc.GetItemText(nItem, 3));
        
        if (0 ==  strcmp("直接取流",m_lstStreamSrc.GetItemText(nItem, 3)) )  //direct connect chan
        {
            ShowUnionInfo(0);
            ClearDirectChanInfo();
           	if (0 == strcmp("是", m_lstStreamSrc.GetItemText(nItem, 4)))
            {
                m_bEnableChannel = TRUE;
            }
            else
            {
                m_bEnableChannel = FALSE;
            }
  
            strTemp = m_lstStreamSrc.GetItemText(nItem, 6);            
            m_cmbProtocolType.SetCurSel(FindDataIndexInComboByStr(strTemp));

            m_cmbStreamType.SetCurSel(atoi(m_lstStreamSrc.GetItemText(nItem, 7)));
            m_strUserName = m_lstStreamSrc.GetItemText(nItem, 8);
            m_strPassword = m_lstStreamSrc.GetItemText(nItem, 9);
            m_strDomainName = m_lstStreamSrc.GetItemText(nItem, 10);
            m_strPort = m_lstStreamSrc.GetItemText(nItem, 11);
            m_strChannel = m_lstStreamSrc.GetItemText(nItem, 12);
             m_strDeviceName = m_lstStreamSrc.GetItemText(nItem, 13);
            m_strStatus = m_lstStreamSrc.GetItemText(nItem, 14);
            m_bLocalBackUp = atoi(m_lstStreamSrc.GetItemText(nItem, 15));
            if (m_strStatus.Find("在线") == 0 )
            {
                m_bChanStatus = TRUE;
            }
            else
            {
                m_bChanStatus = FALSE;
            } 
        }
        else if (0 == strcmp("URL",m_lstStreamSrc.GetItemText(nItem, 3)))
        {
             ShowUnionInfo(1);
            ClearUrlInfo();
            if (0 == strcmp("是", m_lstStreamSrc.GetItemText(nItem, 4)))
            {
                m_bEnableURL = TRUE;
            }
            else
            {
                m_bEnableURL = FALSE;
            }
            
            m_strStreamURL = m_lstStreamSrc.GetItemText(nItem, 5);       
        } 
        else if(0 == strcmp("RTSP",m_lstStreamSrc.GetItemText(nItem, 3)))
        {
             ShowUnionInfo(2);
            if (0 == strcmp("是", m_lstStreamSrc.GetItemText(nItem, 4)))
            {
                m_bEnableRTSPPro = TRUE;
            }
            else
            {
               m_bEnableRTSPPro = FALSE;
            }
            m_strStreamURL = m_lstStreamSrc.GetItemText(nItem,5);

            strTemp = m_lstStreamSrc.GetItemText(nItem, 6);            
            m_cmbProtocolType.SetCurSel(FindDataIndexInComboByStr(strTemp));
            
            m_strUserName = m_lstStreamSrc.GetItemText(nItem, 8);
            m_strPassword = m_lstStreamSrc.GetItemText(nItem, 9);
            m_strDomainName = m_lstStreamSrc.GetItemText(nItem, 10);
            m_strPort = m_lstStreamSrc.GetItemText(nItem, 11);
            m_bRtspBackUp = atoi(m_lstStreamSrc.GetItemText(nItem, 15));
        }
        else if (0 == strcmp("流媒体URL(级联)",m_lstStreamSrc.GetItemText(nItem, 3)))
        {
             ShowUnionInfo(3);
             if (0 == strcmp("是", m_lstStreamSrc.GetItemText(nItem, 4)))
             {
                 m_bEnableUrlMore = TRUE;
             }
             else
             {
                 m_bEnableUrlMore = FALSE;
             }
             m_strStreamURL = m_lstStreamSrc.GetItemText(nItem, 5);
             strTemp = m_lstStreamSrc.GetItemText(nItem, 6);
  
             m_cmbProtocolType.SetCurSel(FindDataIndexInComboByStr(strTemp));

             m_cmbStreamType.SetCurSel(atoi(m_lstStreamSrc.GetItemText(nItem, 7)));

             m_strUserName = m_lstStreamSrc.GetItemText(nItem, 8);
             m_strPassword = m_lstStreamSrc.GetItemText(nItem, 9);
             m_strDomainName = m_lstStreamSrc.GetItemText(nItem, 10);
             m_strPort = m_lstStreamSrc.GetItemText(nItem, 11);

             m_strChannel = m_lstStreamSrc.GetItemText(nItem, 12);
             m_strDeviceName = m_lstStreamSrc.GetItemText(nItem, 13);
                 
             m_bBackupUrlMore = atoi(m_lstStreamSrc.GetItemText(nItem, 15));
             
        }

        m_strMonitorName = m_lstStreamSrc.GetItemText(nItem, 16);
	}
    UpdateData(FALSE);
	*pResult = 0;
}

void CDlgStreamSrcCfg::OnButtonGetStreamSrc() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    char szLan[128] = {0};
	DWORD dwReturn = 0;
	CString strTemp;

   
    int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    LONG lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;
    
    //int iItemCount = m_lstStreamSrc.GetItemCount();
    
     
    memset(&m_struStreamID, 0, sizeof(NET_DVR_STREAM_INFO));
    m_struStreamID.dwSize = sizeof(NET_DVR_STREAM_INFO);
    m_struStreamID.dwChannel = atoi(m_strRelatedChannel);
    strncpy((char*)m_struStreamID.byID, m_strStreamID, STREAM_ID_LEN);
    
       
    DWORD dwStatus = 0;
    
    memset(&m_struStreamSrcInfo,0,sizeof(m_struStreamSrcInfo));
    BOOL bRet = NET_DVR_GetDeviceConfig(lLoginID, NET_DVR_GET_STREAM_SRC_INFO_V40, 0, &m_struStreamID, sizeof(m_struStreamID), &dwStatus, &m_struStreamSrcInfo, sizeof(m_struStreamSrcInfo));
    
    if ( bRet && (0 == dwStatus) )
    {
        g_StringLanType(szLan,"获取流来源成功","Get source success");
        g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "Get Stream Source success");
    }
    else
    {        
        g_StringLanType(szLan,"获取流来源失败","Fail to Get stream source");
        g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Fail to set stream source");
        AfxMessageBox(szLan);
        return;
    }
    
    

    if (m_iCurSelectItem == -1)
    {
        m_iCurSelectItem = 0; 
    }
  
 
    AssignmentStreamCfgV40(m_iCurSelectItem);
    AddStreamInfoToList(m_iCurSelectItem);
    m_lstStreamSrc.DeleteItem(m_iCurSelectItem +1);
    
    UpdateData(FALSE);
	
}

void CDlgStreamSrcCfg::OnButtonSetStreamSrc() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char szLan[1024] = {0};
    char szLanCn[1024] = {0};
    char szLanEn[1024] = {0};

     
    int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    LONG lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;
    POSITION pos = m_lstStreamSrc.GetFirstSelectedItemPosition();
    
    int nItem = 0;
    if (pos == NULL)
    {
        //TRACE0("No items were selected!\n");
        memcpy(szLanCn,"请先选择一条要配置的信息", sizeof("请先选择一条要配置的信息"));
        memcpy(szLanEn, "Please Select One Stream Info first!", sizeof("Please Select One Stream Info first!"));
        g_StringLanType(szLan,szLanCn, szLanEn);
        AfxMessageBox(szLan);
        return;
    }
    nItem = m_lstStreamSrc.GetNextSelectedItem(pos);   
     
     
    memset(&m_struStreamID, 0, sizeof(m_struStreamID));
    m_struStreamID.dwSize = sizeof(NET_DVR_STREAM_INFO);
    m_strStreamID = m_lstStreamSrc.GetItemText(nItem, 1);
    strncpy((char*)m_struStreamID.byID,m_strStreamID, STREAM_ID_LEN);   
    m_strRelatedChannel = m_lstStreamSrc.GetItemText(nItem, 2);
    m_struStreamID.dwChannel = atoi(m_strRelatedChannel);  
   
    m_cmbSrcType.SetWindowText(m_lstStreamSrc.GetItemText(nItem, 3));

    memset(&m_struStreamSrcInfo, 0,sizeof(m_struStreamSrcInfo));
    m_struStreamSrcInfo.dwSize = sizeof(m_struStreamSrcInfo);
   
    
    if (0 ==  strcmp("直接取流",m_lstStreamSrc.GetItemText(nItem, 3)) )  //direct connect chan
    {
        m_struStreamSrcInfo.byGetStreamType = 0;
    }
    else if (0 ==  strcmp("URL",m_lstStreamSrc.GetItemText(nItem, 3)) )  //direct connect chan
    {
      m_struStreamSrcInfo.byGetStreamType = 4;  
    }
    else if (0 ==  strcmp("RTSP",m_lstStreamSrc.GetItemText(nItem, 3)) )  //direct connect chan
    {
        m_struStreamSrcInfo.byGetStreamType = 7; 
   
    }
    else if (0 ==  strcmp("流媒体URL(级联)",m_lstStreamSrc.GetItemText(nItem, 3)) )  //direct connect chan
    {
        m_struStreamSrcInfo.byGetStreamType = 8;  

    }

    strncpy((char*)m_struStreamSrcInfo.byMonitorName, m_strMonitorName, 128);
  
    if (!ReadStreamCfgV40(nItem))
    {
       return;
    }


    DWORD dwStatus = 0; 
    
    BOOL bRet = NET_DVR_SetDeviceConfig(lLoginID, NET_DVR_SET_STREAM_SRC_INFO_V40, 0, &m_struStreamID, sizeof(m_struStreamID), &dwStatus, &m_struStreamSrcInfo, sizeof(m_struStreamSrcInfo));
    
    if (bRet && (0 == dwStatus))
    {
        g_StringLanType(szLan,"设置流来源成功","Success");
        g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "Set Stream Source");
    }
    else
    {        
        g_StringLanType(szLan,"设置流来源失败","Fail to set stream source");
        g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "Fail to set stream source");
    }
    
	UpdateData(FALSE);
}

void CDlgStreamSrcCfg::OnSelchangeComboSrcType() 
{
	// TODO: Add your control notification handler code here
    ShowUnionInfo(m_cmbSrcType.GetCurSel());
}

void CDlgStreamSrcCfg::ClearDirectChanInfo()
{
    
    m_bEnableChannel = FALSE;
    m_strUserName = "";
    m_strPassword = "";
    m_strChannel = "";
    m_strDomainName = "";
    m_strPort = "";    
    m_bChanStatus = FALSE;
}
void CDlgStreamSrcCfg::ClearUrlInfo()
{
    m_bEnableURL = FALSE;
    m_strStreamURL = "";
}

void CDlgStreamSrcCfg::ClearRtspInfo()
{
    m_bEnableRTSPPro = FALSE;
    m_strRtspUserName = "";
    m_strRtspPasswd = "";
}

void CDlgStreamSrcCfg::ClearUrlMoreInfo()
{
    m_bEnableRTSPPro = FALSE;
    m_strRtspUserName = "";
    m_strRtspPasswd = "";
}
void CDlgStreamSrcCfg::ShowUnionInfo(int iCurIndex)
{
    if (iCurIndex < 0)
    {
        return;
    }
    switch (iCurIndex)
    {
    case 0:
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
        GetDlgItem(IDC_STATIC_IP_ADDRESS)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_PORT)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_CHECK_ENABLE_CHANNLE)->ShowWindow(SW_SHOW);        
        GetDlgItem(IDC_CHK_ENABLE_RTSPPRO)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CHK_LOCAL_BACKUP)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_DEVICENAME)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_DEVICENAME)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_CHK_CHAN_STATUS)->ShowWindow(SW_SHOW);


        GetDlgItem(IDC_CHK_LOCAL_BACKUP_RTSP)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CHK_LOCAL_BACKUP_URLMORE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CHECK_ENABLE_URL_MORE)->ShowWindow(SW_HIDE);
        break;
    case 1:
        GetDlgItem(IDC_EDIT_STREAM_URL)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_CHECK_ENABLE_URL)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_STREAM_URL)->ShowWindow(SW_SHOW);
        
        GetDlgItem(IDC_STATIC_CHANNLE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_CHANNLE)->ShowWindow(SW_HIDE);
        
        GetDlgItem(IDC_COMBO_PROTOCOL_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_PROTOCOL_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_USER_NAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_USER_NAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_PASSWORD)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_PASSWORD)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_STATUS)->ShowWindow(SW_HIDE);
        
        GetDlgItem(IDC_STATIC_STREAM_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_STREAM_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_DOMAIN_NAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_IP_ADDRESS)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_PORT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CHECK_ENABLE_CHANNLE)->ShowWindow(SW_HIDE);
        
        GetDlgItem(IDC_CHK_LOCAL_BACKUP_RTSP)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CHK_ENABLE_RTSPPRO)->ShowWindow(SW_HIDE);
         GetDlgItem(IDC_CHK_LOCAL_BACKUP)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_DEVICENAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_DEVICENAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CHK_CHAN_STATUS)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_CHK_LOCAL_BACKUP_URLMORE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CHECK_ENABLE_URL_MORE)->ShowWindow(SW_HIDE);
        break;
    case 2:
        GetDlgItem(IDC_EDIT_STREAM_URL)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_CHECK_ENABLE_URL)->ShowWindow(SW_HIDE);
        
        
        GetDlgItem(IDC_COMBO_PROTOCOL_TYPE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_PROTOCOL_TYPE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_USER_NAME)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_USER_NAME)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_PASSWORD)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_PASSWORD)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_CHANNLE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_CHANNLE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_STREAM_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_STREAM_TYPE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_DOMAIN_NAME)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_IP_ADDRESS)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_PORT)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_CHECK_ENABLE_CHANNLE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_STATUS)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_CHK_LOCAL_BACKUP_RTSP)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_STREAM_URL)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_CHK_ENABLE_RTSPPRO)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_CHK_LOCAL_BACKUP)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_DEVICENAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_DEVICENAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CHK_CHAN_STATUS)->ShowWindow(SW_HIDE);

 
        GetDlgItem(IDC_CHK_LOCAL_BACKUP_URLMORE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CHECK_ENABLE_URL_MORE)->ShowWindow(SW_HIDE);
        
        break;
    case 3:
        GetDlgItem(IDC_STATIC_STREAM_URL)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_STREAM_URL)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_CHECK_ENABLE_URL)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_CHECK_ENABLE_URL_MORE)->ShowWindow(SW_SHOW);
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
        GetDlgItem(IDC_EDIT_DOMAIN_NAME)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_IP_ADDRESS)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_PORT)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_PORT)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_CHECK_ENABLE_CHANNLE)->ShowWindow(SW_HIDE);
        
        GetDlgItem(IDC_STATIC_DEVICENAME)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_DEVICENAME)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_CHK_LOCAL_BACKUP)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_STATUS)->ShowWindow(SW_HIDE);
        
        GetDlgItem(IDC_CHK_ENABLE_RTSPPRO)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CHK_CHAN_STATUS)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CHK_LOCAL_BACKUP_RTSP)->ShowWindow(SW_HIDE);

        GetDlgItem(IDC_CHK_LOCAL_BACKUP_URLMORE)->ShowWindow(SW_SHOW);
        break;
    default:
        break;
   }
       
}

BOOL CDlgStreamSrcCfg::ReadStreamCfgV40(int dwItem)
{
    char szLan[1024] = {0}; 

    if (0 == m_struStreamSrcInfo.byGetStreamType)
    {
        m_struStreamSrcInfo.uGetStream.struChanInfo.byEnable = m_bEnableChannel;
        m_struStreamSrcInfo.uGetStream.struChanInfo.byProType = m_cmbProtocolType.GetItemData(m_cmbProtocolType.GetCurSel());
        m_struStreamSrcInfo.uGetStream.struChanInfo.byStreamType = m_cmbStreamType.GetCurSel();
        m_struStreamSrcInfo.uGetStream.struChanInfo.dwChannel = atoi(m_strChannel);
        m_struStreamSrcInfo.uGetStream.struChanInfo.wDVRPort = atoi(m_strPort);
        strncpy((char*)m_struStreamSrcInfo.uGetStream.struChanInfo.byAddress, m_strDomainName, MAX_DOMAIN_NAME);
        strncpy((char*)m_struStreamSrcInfo.uGetStream.struChanInfo.sUserName, m_strUserName, NAME_LEN);
        strncpy((char*)m_struStreamSrcInfo.uGetStream.struChanInfo.sPassword, m_strPassword, PASSWD_LEN);
        m_struStreamSrcInfo.uGetStream.struChanInfo.byLocalBackUp = m_bLocalBackUp;
        strncpy((char*)m_struStreamSrcInfo.uGetStream.struChanInfo.byVAGChanNo, m_strDeviceName, MAX_VAG_CHANNO_LEN);

    }
    else if (4 == m_struStreamSrcInfo.byGetStreamType)
    {
        m_struStreamSrcInfo.uGetStream.struPuStreamUrl.byEnable = m_bEnableURL;
        strncpy((char*)m_struStreamSrcInfo.uGetStream.struPuStreamUrl.strURL, m_strStreamURL, URL_LEN);
    }
    else if (7 == m_struStreamSrcInfo.byGetStreamType)
    {
        m_struStreamSrcInfo.uGetStream.struRtspCfg.byEnable = m_bEnableRTSPPro;
       strncpy((char*)m_struStreamSrcInfo.uGetStream.struRtspCfg.strURL, m_strStreamURL, URL_LEN_V40);
        strncpy((char*)m_struStreamSrcInfo.uGetStream.struRtspCfg.sUserName, m_strUserName, NAME_LEN);
        strncpy((char*)m_struStreamSrcInfo.uGetStream.struRtspCfg.sPassWord,m_strPassword, PASSWD_LEN);
        m_struStreamSrcInfo.uGetStream.struRtspCfg.dwProtocalType = m_cmbProtocolType.GetItemData(m_cmbProtocolType.GetCurSel());
        m_struStreamSrcInfo.uGetStream.struRtspCfg.wPort = atoi(m_strPort);
        strncpy((char*)m_struStreamSrcInfo.uGetStream.struRtspCfg.byAddress, m_strDomainName, MAX_DOMAIN_NAME);
        m_struStreamSrcInfo.uGetStream.struRtspCfg.byLocalBackUp = m_bRtspBackUp;
 
    }
    else if (8 == m_struStreamSrcInfo.byGetStreamType)
    {
        // 将url部分设为空
        m_struStreamSrcInfo.uGetStream.struStreamUrlV40.byEnable = m_bEnableUrlMore;
        m_struStreamSrcInfo.uGetStream.struStreamUrlV40.byLocalBackUp = m_bBackupUrlMore;    
        m_struStreamSrcInfo.uGetStream.struStreamUrlV40.byStreamType = m_cmbStreamType.GetCurSel();
        strncpy((char*)m_struStreamSrcInfo.uGetStream.struStreamUrlV40.strURL, m_strStreamURL, URL_LEN_V40);
        m_struStreamSrcInfo.uGetStream.struStreamUrlV40.dwProtocalType = m_cmbProtocolType.GetItemData(m_cmbProtocolType.GetCurSel());
        strncpy((char*)m_struStreamSrcInfo.uGetStream.struStreamUrlV40.sUserName, m_strUserName, NAME_LEN);
        strncpy((char*)m_struStreamSrcInfo.uGetStream.struStreamUrlV40.sPassWord,m_strPassword, PASSWD_LEN);
        m_struStreamSrcInfo.uGetStream.struStreamUrlV40.wIPPort = atoi(m_strPort);
        strncpy((char*)m_struStreamSrcInfo.uGetStream.struStreamUrlV40.byAddress, m_strDomainName, MAX_DOMAIN_NAME);
        
        m_struStreamSrcInfo.uGetStream.struStreamUrlV40.wChanNo = atoi(m_strChannel);
        strncpy((char*)m_struStreamSrcInfo.uGetStream.struStreamUrlV40.byVAGChanNo, m_strDeviceName, MAX_VAG_CHANNO_LEN);
    }
    else
    {
        g_StringLanType(szLan,"源模式暂不支持","Not support this stream source type");
        AfxMessageBox(szLan);
        return FALSE;
    }

    return TRUE;
}

BOOL CDlgStreamSrcCfg::AssignmentStreamCfgV40(int iSelectItem)
{
    if (iSelectItem < 0)
    {
        return FALSE;
    } 
    
    char szLan[128] = {0};

    m_strMonitorName.Format("%s", m_struStreamSrcInfo.byMonitorName);

    if (0 == m_struStreamSrcInfo.byGetStreamType)
    {
        m_cmbSrcType.SetCurSel(0);
        m_bEnableChannel = m_struStreamSrcInfo.uGetStream.struChanInfo.byEnable;
       m_cmbProtocolType.SetCurSel(FindDataIndexInCombo(m_struStreamSrcInfo.uGetStream.struChanInfo.byProType));
       m_strUserName  = m_struStreamSrcInfo.uGetStream.struChanInfo.sUserName;
       m_strPassword  = m_struStreamSrcInfo.uGetStream.struChanInfo.sPassword;
       m_strDomainName = m_struStreamSrcInfo.uGetStream.struChanInfo.byAddress;
        m_strPort.Format("%d", m_struStreamSrcInfo.uGetStream.struChanInfo.wDVRPort);
        m_cmbStreamType.SetCurSel(m_struStreamSrcInfo.uGetStream.struChanInfo.byStreamType);
        m_bChanStatus = m_struStreamSrcInfo.uGetStream.struChanInfo.byOnline;
        m_strChannel.Format("%d", m_struStreamSrcInfo.uGetStream.struChanInfo.dwChannel);
        m_bLocalBackUp = m_struStreamSrcInfo.uGetStream.struChanInfo.byLocalBackUp;  
        m_strDeviceName = m_struStreamSrcInfo.uGetStream.struChanInfo.byVAGChanNo;
        m_bChanStatus = m_struStreamSrcInfo.uGetStream.struChanInfo.byOnline;
    }
    else if (4 == m_struStreamSrcInfo.byGetStreamType)
    {
        m_cmbSrcType.SetCurSel(1);
        m_bEnableURL = m_struStreamSrcInfo.uGetStream.struPuStreamUrl.byEnable;
         m_strStreamURL = m_struStreamSrcInfo.uGetStream.struPuStreamUrl.strURL;
    }
    else if (7 ==m_struStreamSrcInfo.byGetStreamType)
    {
        m_cmbSrcType.SetCurSel(2);
        m_bEnableRTSPPro = m_struStreamSrcInfo.uGetStream.struRtspCfg.byEnable;
        m_bLocalBackUp = m_struStreamSrcInfo.uGetStream.struRtspCfg.byLocalBackUp;
        //差协议类型
         m_strUserName = m_struStreamSrcInfo.uGetStream.struRtspCfg.sUserName;
         m_strPassword = m_struStreamSrcInfo.uGetStream.struRtspCfg.sPassWord;
         m_strStreamURL = m_struStreamSrcInfo.uGetStream.struRtspCfg.strURL;
        //域名
        m_strDomainName = m_struStreamSrcInfo.uGetStream.struRtspCfg.byAddress ;
        m_strPort.Format("%d", m_struStreamSrcInfo.uGetStream.struRtspCfg.wPort);
        m_cmbProtocolType.SetCurSel(FindDataIndexInCombo(m_struStreamSrcInfo.uGetStream.struRtspCfg.dwProtocalType));
    }
    else if (8 == m_struStreamSrcInfo.byGetStreamType)
    {
        m_cmbSrcType.SetCurSel(3);
        
        // 将url部分设为空
        m_bEnableUrlMore = m_struStreamSrcInfo.uGetStream.struStreamUrlV40.byEnable;
        m_cmbStreamType.SetCurSel(m_struStreamSrcInfo.uGetStream.struStreamUrlV40.byStreamType);
        m_bBackupUrlMore = m_struStreamSrcInfo.uGetStream.struStreamUrlV40.byLocalBackUp;
         m_strStreamURL = m_struStreamSrcInfo.uGetStream.struRtspCfg.strURL;
        m_cmbProtocolType.SetCurSel(FindDataIndexInCombo(m_struStreamSrcInfo.uGetStream.struStreamUrlV40.dwProtocalType));  
        m_strUserName = m_struStreamSrcInfo.uGetStream.struStreamUrlV40.sUserName;
        m_strPassword = m_struStreamSrcInfo.uGetStream.struStreamUrlV40.sPassWord;         
       m_strDomainName = m_struStreamSrcInfo.uGetStream.struChanInfo.byAddress;
        m_strPort.Format("%d",m_struStreamSrcInfo.uGetStream.struStreamUrlV40.wIPPort); 
        m_strChannel.Format("%d", m_struStreamSrcInfo.uGetStream.struStreamUrlV40.wChanNo);
        m_strDeviceName = m_struStreamSrcInfo.uGetStream.struStreamUrlV40.byVAGChanNo;
    }
    else
    {
        g_StringLanType(szLan,"源模式暂不支持","Not support this stream source type");
        AfxMessageBox(szLan);
        return FALSE;
    }

    UpdateData(FALSE);
    return TRUE;
}

void CDlgStreamSrcCfg::AddStreamInfoToList(int iItem)
{
    UpdateData(TRUE);
    char szLan[128] = {0};
	CString strTemp;
    if (iItem > m_lstStreamSrc.GetItemCount() )
    {
        return;
    }    
	strTemp.Format("%02d", iItem+1);
	m_lstStreamSrc.InsertItem(iItem, strTemp);
	m_lstStreamSrc.SetItemText(iItem, 1, m_strStreamID);
	m_lstStreamSrc.SetItemText(iItem, 2, m_strRelatedChannel);
	m_cmbSrcType.GetWindowText(strTemp);
	m_lstStreamSrc.SetItemText(iItem, 3, strTemp);
	if (0 == m_cmbSrcType.GetCurSel())
	{
		// 将url部分设为空
		if (TRUE == m_bEnableChannel)
		{
			m_lstStreamSrc.SetItemText(iItem, 4, "是");
		}
		else
		{
			m_lstStreamSrc.SetItemText(iItem, 4, "否");
		}
        
        m_lstStreamSrc.SetItemText(iItem, 5, "");      
        
        m_cmbProtocolType.GetWindowText(strTemp);
        m_lstStreamSrc.SetItemText(iItem, 6, strTemp);

        strTemp.Format("%2d", m_cmbStreamType.GetCurSel());
        m_lstStreamSrc.SetItemText(iItem, 7, strTemp);

		m_lstStreamSrc.SetItemText(iItem, 8, m_strUserName);
		m_lstStreamSrc.SetItemText(iItem, 9, m_strPassword);
		m_lstStreamSrc.SetItemText(iItem, 10, m_strDomainName);
		m_lstStreamSrc.SetItemText(iItem, 11, m_strPort);
        m_lstStreamSrc.SetItemText(iItem, 12, m_strChannel);
		m_lstStreamSrc.SetItemText(iItem, 13, m_strDeviceName);
        if (m_bChanStatus)
        {
            m_lstStreamSrc.SetItemText(iItem, 14, "在线");
        }
        else
        {
            m_lstStreamSrc.SetItemText(iItem, 14, "不在线");
        }
       
        strTemp.Format("%d", m_bLocalBackUp);
        m_lstStreamSrc.SetItemText(iItem, 15, strTemp);
	}
	else if (1 == m_cmbSrcType.GetCurSel())
	{
        if (TRUE == m_bEnableURL)
        {
            m_lstStreamSrc.SetItemText(iItem, 4, "是");
        }
        else
        {
            m_lstStreamSrc.SetItemText(iItem, 4, "否");
        }
        
        m_lstStreamSrc.SetItemText(iItem, 5, m_strStreamURL);
        
        // 将直连部分全设为空
        for (int i=6; i<15; i++)
        {
            m_lstStreamSrc.SetItemText(iItem, i, "");
		}

	} 
	else if (2 == m_cmbSrcType.GetCurSel())
	{
        // 将url部分设为空
        if (m_bEnableRTSPPro)
        {
            m_lstStreamSrc.SetItemText(iItem, 4, "是");
        }
        else
        {
            m_lstStreamSrc.SetItemText(iItem, 4, "否");
        }

          m_lstStreamSrc.SetItemText(iItem, 5, m_strStreamURL);
        //协议类型
        m_cmbProtocolType.GetWindowText(strTemp);
        m_lstStreamSrc.SetItemText(iItem, 6, strTemp);

        m_lstStreamSrc.SetItemText(iItem, 7, "");
        m_lstStreamSrc.SetItemText(iItem, 8, m_strUserName);
        m_lstStreamSrc.SetItemText(iItem, 9, m_strPassword);
        m_lstStreamSrc.SetItemText(iItem, 10, m_strDomainName);
        m_lstStreamSrc.SetItemText(iItem, 11, m_strPort);
        m_lstStreamSrc.SetItemText(iItem, 12, "");         
        m_lstStreamSrc.SetItemText(iItem, 13, "");
        m_lstStreamSrc.SetItemText(iItem, 14, "");      
        strTemp.Format("%d", m_bRtspBackUp);
        m_lstStreamSrc.SetItemText(iItem, 15, strTemp);
	}
    else if (3 == m_cmbSrcType.GetCurSel())
    {
        // 将url部分设为空
        if (m_bEnableUrlMore)
        {
            m_lstStreamSrc.SetItemText(iItem, 4, "是");
        }
        else
        {
            m_lstStreamSrc.SetItemText(iItem, 4, "否");
        }
        m_lstStreamSrc.SetItemText(iItem, 5, m_strStreamURL);
        
        
        m_cmbProtocolType.GetWindowText(strTemp);
        m_lstStreamSrc.SetItemText(iItem, 6,strTemp);
        
        strTemp.Format("%d",m_cmbStreamType.GetCurSel());
        m_lstStreamSrc.SetItemText(iItem, 7, strTemp);
        m_lstStreamSrc.SetItemText(iItem, 8, m_strUserName);
        m_lstStreamSrc.SetItemText(iItem, 9, m_strPassword);
        m_lstStreamSrc.SetItemText(iItem, 10, m_strDomainName);
        m_lstStreamSrc.SetItemText(iItem, 11, m_strPort);
        m_lstStreamSrc.SetItemText(iItem, 12, m_strChannel);
        m_lstStreamSrc.SetItemText(iItem, 13, m_strDeviceName);
        m_lstStreamSrc.SetItemText(iItem, 14, "");
        strTemp.Format("%d", m_bBackupUrlMore);
        m_lstStreamSrc.SetItemText(iItem, 15, strTemp);
    }

    m_lstStreamSrc.SetItemText(iItem, 16, m_strMonitorName);
}

void CDlgStreamSrcCfg::OnBtnMode() 
{
	// TODO: Add your control notification handler code here
	AddStreamInfoToList(m_iCurSelectItem);
    m_lstStreamSrc.DeleteItem(m_iCurSelectItem +1);
    
}

void CDlgStreamSrcCfg::AddProtocalList()
{
    int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    if (iDeviceIndex < 0)
    {
        return;
    }
    LONG lLoginID = g_struDeviceInfo[iDeviceIndex].lLoginID;
    
    memset(&m_struProList,0 , sizeof(m_struProList));

    if (!NET_DVR_GetIPCProtoList(lLoginID,&m_struProList))
    {
       g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetIPCProtoList");
       return;
    }

    g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetIPCProtoList");

    //add protocal Info to List

    m_cmbProtocolType.ResetContent();
    int iIndex = 0;
    
    for (int i = 0; i < m_struProList.dwProtoNum; i++)
    {
        m_cmbProtocolType.AddString((char*)m_struProList.struProto[i].byDescribe);
       
        m_cmbProtocolType.SetItemData(iIndex, m_struProList.struProto[i].dwType);
        iIndex++;
    }

    m_cmbProtocolType.SetCurSel(0);


}

BOOL CDlgStreamSrcCfg::CheckInitParam()
{
     AddProtocalList();    
    return TRUE;
}

int CDlgStreamSrcCfg::FindDataIndexInCombo(byte byProtocalType)
{
    int iRet = -1;
    for (int i = 0; i < m_cmbProtocolType.GetCount(); i++)
    {
        if (m_cmbProtocolType.GetItemData( m_cmbProtocolType.SetCurSel(i)) == byProtocalType)
        {
            iRet =  i;
            break;
        }       
    }
    return iRet;
}

int CDlgStreamSrcCfg::FindDataIndexInComboByStr(CString strFind)
{
    int iRet = -1;
    CString strTemp = "";

    for (int i = 0; i < m_cmbProtocolType.GetCount(); i++)
    {
        strTemp = m_struProList.struProto[i].byDescribe;
        if (strTemp == strFind)
        {
            iRet = i;
            break;
        }

    }
    return iRet;
}
