// DlgUpStreamCfg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgUpStreamCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgUpStreamCfg dialog


CDlgUpStreamCfg::CDlgUpStreamCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUpStreamCfg::IDD, pParent)
	, m_lpProtoType(NULL)
{
	//{{AFX_DATA_INIT(CDlgUpStreamCfg)
    m_RemoteIP = _T("10.7.52.13");
    m_RemoteSurveillace = 1;
    m_RemoteUser = _T("test");
    m_RemotePass = _T("12345");
    m_strStreamMediaIp = _T("172.9.31.76");
    m_dwStreamMediaPort = 554;
    m_bUseStreamMedia = FALSE;
    m_RemotePort = 8000;
    m_csUrl = _T("");
    m_strDomainRemoteName = _T("admin");
    m_strDomainRemotePass = _T("12345");
    m_strDomainServerIp = _T("");
    m_uiDomainServerPort = 8000;
    m_strDomainStreamId = _T("");
    m_strDomainStreamMediaIp = _T("172.7.162.100");
    m_uiDomainStreamMediaPort = 554;
    m_strDomainName = _T("");
    m_uiDomainChannelNum = 0;
    m_bDomainUseStreamMedia = FALSE;
    m_strStreamId = _T("");
    m_wRemotePort = 8000;
    m_bDispChan = FALSE;
    m_bSubDispChan = FALSE;
    m_dwInputIndex = 1;
	//}}AFX_DATA_INIT
 //   memset(&m_struProtoList, 0, sizeof(m_struProtoList));
    memset(&m_struStreamCfgV41, 0, sizeof(m_struStreamCfgV41)); 
}

CDlgUpStreamCfg::~CDlgUpStreamCfg()
{
	if ( m_lpProtoType )
	{
		delete [] m_lpProtoType; 
		m_lpProtoType = NULL; 
	}
}

void CDlgUpStreamCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgUpStreamCfg)
    DDX_Control(pDX, IDC_COMBO_CHANNEL_TYPE2, m_comboChannelType);
    DDX_Control(pDX, IDC_COMB_MD_DEVCHAN_RESOLUTION, m_cmResolution);
    DDX_Control(pDX, IDC_COMB_MD_DEVCHAN_DEVICETYPE, m_combDeviceType);
    DDX_Control(pDX, IDC_COMBO_DOMAIN_TRANS_PRO, m_comboDomainTransPro);
    DDX_Control(pDX, IDC_COMBO_DOMAIN_TRANSMODE, m_comboDomainTransMode);
    DDX_Control(pDX, IDC_COMBO_DOMAIN_STREAMMEDIAPRO, m_comboDomainStreamMediaPro);
    DDX_Control(pDX, IDC_COMBO_DOMAIN_SERVER_TYPE, m_comboDomainServerType);
    DDX_Control(pDX, IDC_COMBO_DOMAIN_FACTYPE, m_comboDomainFacType);
    DDX_Control(pDX, IDC_COMBO_DOMAIN_CHANNEL_TYPE, m_comboDomainChannelType);
    DDX_Control(pDX, IDC_COMBO_STREAM_MODE, m_comboStreamMode);
    DDX_Control(pDX, IDC_COMBO_FACTYPE, m_FacTypeCtrl);
    DDX_Control(pDX, IDC_COMBOSTREAMMEDIAPRO, m_ComboStreamMediaPro);
//    DDX_Control(pDX, IDC_COMBODECCHANNUM, m_DecChanCombo);
    DDX_Control(pDX, IDC_COMBOTRANSMODE, m_TransModeCombo);
    DDX_Control(pDX, IDC_COMBOPROTOCOL, m_TransProtocolCombo);
    DDX_Text(pDX, IDC_EDITREMOTEIP, m_RemoteIP);
    DDX_Text(pDX, IDC_EDITREMOTESURVE, m_RemoteSurveillace);
    DDX_Text(pDX, IDC_EDITREMOTENAME, m_RemoteUser);
    DDX_Text(pDX, IDC_EDITREMOTEPASS, m_RemotePass);
    DDX_Text(pDX, IDC_STREAMMEDIAIP, m_strStreamMediaIp);
    DDX_Text(pDX, IDC_STREAMMEDIAPORT, m_dwStreamMediaPort);
    DDX_Check(pDX, IDC_USESTREAMMEDIA, m_bUseStreamMedia);
    DDX_Text(pDX, IDC_EDITREMOTEPORT, m_RemotePort);
    DDV_MinMaxDWord(pDX, m_RemotePort, 0, 65535);
    DDX_Text(pDX, IDC_EDIT_URL, m_csUrl);
    DDX_Text(pDX, IDC_EDIT_DOMAIN_REMOTENAME, m_strDomainRemoteName);
    DDX_Text(pDX, IDC_EDIT_DOMAIN_REMOTEPASS, m_strDomainRemotePass);
    DDX_Text(pDX, IDC_EDIT_DOMAIN_SERVER_IP, m_strDomainServerIp);
    DDX_Text(pDX, IDC_EDIT_DOMAIN_SERVER_PORT, m_uiDomainServerPort);
    DDX_Text(pDX, IDC_EDIT_DOMAIN_STREAMID, m_strDomainStreamId);
    DDX_Text(pDX, IDC_EDIT_DOMAIN_STREAMMEDIAIP, m_strDomainStreamMediaIp);
    DDX_Text(pDX, IDC_EDIT_DOMAIN_STREAMMEDIAPORT, m_uiDomainStreamMediaPort);
    DDX_Text(pDX, IDC_EDIT_DOMAIN_NAME, m_strDomainName);
    DDX_Text(pDX, IDC_EDIT_DOMAIN_CHANNEL_NUMBER, m_uiDomainChannelNum);
    DDX_Check(pDX, IDC_CHK_DOMAIN_USESTREAMMEDIA, m_bDomainUseStreamMedia);
    DDX_Text(pDX, IDC_EDIT_STREAMID, m_strStreamId);
    DDX_Text(pDX, IDC_EDIT_DOMAIN_REMOTE_PORT, m_wRemotePort);
    DDX_Check(pDX, IDC_CHK_MD_DEVCHAN_DISPCHAN, m_bDispChan);
    DDX_Check(pDX, IDC_CHK_MD_DEVCHAN_SUBDISPCHAN, m_bSubDispChan);
    DDX_Text(pDX, IDC_EDIT_MD_DEVCHAN_INPUTINDEX, m_dwInputIndex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgUpStreamCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgUpStreamCfg)
	ON_BN_CLICKED(IDC_OK, OnOk)
	ON_CBN_SELCHANGE(IDC_COMBO_STREAM_MODE, oncbnChangeStreamMode)
	ON_BN_CLICKED(IDC_USESTREAMMEDIA, OnBnClickedUsestreammedia)
	ON_BN_CLICKED(IDC_CHK_DOMAIN_USESTREAMMEDIA, OnBnClickedChkDomainUsestreammedia)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgUpStreamCfg message handlers

BOOL CDlgUpStreamCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    char szLan[128]; 
	m_lDeviceID =  g_pMainDlg->GetCurDeviceIndex(); 
	m_lServerID = g_struDeviceInfo[m_lDeviceID].lLoginID; 

    int i=0; 
	if ( ! m_lpProtoType )
	{
		m_lpProtoType = new NET_DVR_PROTO_TYPE[1024];
	}
	memset(&m_struProtocolListV41, 0, sizeof(m_struProtocolListV41));
	m_struProtocolListV41.dwSize = sizeof(m_struProtocolListV41);
	if(!NET_DVR_GetIPCProtoList_V41(m_lServerID, &m_struProtocolListV41))
	{
		g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_GetIPCProtoList_V41 Get Num");
	}
	else
	{
		g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_GetIPCProtoList_V41 Get Num");
	}
	DWORD dwVaildProtoNum = m_struProtocolListV41.dwProtoNum;
	m_struProtocolListV41.pBuffer = (BYTE *)m_lpProtoType; 
	m_struProtocolListV41.dwBufferLen = sizeof(NET_DVR_PROTO_TYPE) * dwVaildProtoNum; 
	if(!NET_DVR_GetIPCProtoList_V41(m_lServerID, &m_struProtocolListV41))
	{
		g_pMainDlg->AddLog(m_lDeviceID, OPERATION_FAIL_T, "NET_DVR_GetIPCProtoList_V41 Get List");
	
	}
	else
	{
		g_pMainDlg->AddLog(m_lDeviceID, OPERATION_SUCC_T, "NET_DVR_GetIPCProtoList_V41 Get List");
	}
	LPNET_DVR_PROTO_TYPE lpProtoType = (LPNET_DVR_PROTO_TYPE)m_struProtocolListV41.pBuffer; 
	for (i = 0; i < (int)m_struProtocolListV41.dwProtoNum; i++)
	{
		memset(szLan, 0, DESC_LEN);
		memcpy(szLan, lpProtoType->byDescribe, DESC_LEN);
		m_FacTypeCtrl.AddString(szLan);
		m_FacTypeCtrl.SetItemData(i, lpProtoType->dwType); 
		m_comboDomainFacType.AddString(szLan);
		m_comboDomainFacType.SetItemData(i, lpProtoType->dwType); 
		++ lpProtoType; 
	}	
	m_FacTypeCtrl.SetCurSel(0);
	m_comboDomainFacType.SetCurSel(0);

// 	if (NET_DVR_GetIPCProtoList(m_lServerID, &m_struProtoList))
//     {
//         for (i = 0; i < (int)m_struProtoList.dwProtoNum; i++)
//         {
//             memset(szLan, 0, DESC_LEN);
//             memcpy(szLan, m_struProtoList.struProto[i].byDescribe, DESC_LEN);
//             m_FacTypeCtrl.AddString(szLan);
//             m_FacTypeCtrl.SetItemData(i, m_struProtoList.struProto[i].dwType); 
// 			m_comboDomainFacType.AddString(szLan);
//             m_comboDomainFacType.SetItemData(i, m_struProtoList.struProto[i].dwType); 
// 		}
//         m_FacTypeCtrl.SetCurSel(0);
// 		m_comboDomainFacType.SetCurSel(0);
//     } 
// 	else
// 	{
// 		g_pMainDlg->AddLog( m_lDeviceID , OPERATION_FAIL_T, "NET_DVR_MatrixStopDynamic");
//     }
    UpdateStreamCfg(); 
	oncbnChangeStreamMode();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CDlgUpStreamCfg::EnableDynamicDDNSGroup(BOOL IsEnable)
{
    
    UINT id[]={IDC_EDIT_DOMAIN_NAME, IDC_EDIT_DOMAIN_REMOTE_PORT, IDC_COMBO_DOMAIN_SERVER_TYPE, IDC_EDIT_DOMAIN_SERVER_IP, IDC_EDIT_DOMAIN_SERVER_PORT, IDC_COMBO_DOMAIN_TRANS_PRO,\
        IDC_EDIT_DOMAIN_STREAMID, IDC_COMBO_DOMAIN_TRANSMODE, IDC_EDIT_DOMAIN_REMOTENAME, IDC_EDIT_DOMAIN_REMOTEPASS, IDC_COMBO_DOMAIN_CHANNEL_TYPE, IDC_COMBO_DOMAIN_FACTYPE,\
        IDC_EDIT_DOMAIN_CHANNEL_NUMBER, IDC_CHK_DOMAIN_USESTREAMMEDIA, IDC_EDIT_DOMAIN_STREAMMEDIAIP, IDC_EDIT_DOMAIN_STREAMMEDIAPORT, IDC_COMBO_DOMAIN_STREAMMEDIAPRO};
    for (int i = 0; i < sizeof(id)/sizeof(UINT); i++)
    {
        GetDlgItem(id[i])->EnableWindow(IsEnable);
    }
    if (IsEnable)
    {
        OnBnClickedChkDomainUsestreammedia();
        OnSelchangeComboDomainChannelType();
    }
}






void CDlgUpStreamCfg::OnSelchangeComboChannelType2() 
{
	
	UpdateData(TRUE);
	
	GetDlgItem(IDC_EDITREMOTESURVE)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_STREAMID)->EnableWindow(FALSE);
	switch (m_comboChannelType.GetCurSel())
	{
	case 0:
	case 1:
		break;
	case 2:
		GetDlgItem(IDC_EDIT_STREAMID)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDITREMOTESURVE)->EnableWindow(FALSE);
		break;
	default:
		break;
	}
	UpdateData(FALSE);
	
}

void CDlgUpStreamCfg::OnSelchangeComboDomainChannelType() 
{
	UpdateData(TRUE);
	
	GetDlgItem(IDC_EDIT_DOMAIN_CHANNEL_NUMBER)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DOMAIN_STREAMID)->EnableWindow(FALSE);
	switch (m_comboDomainChannelType.GetCurSel())
	{
	case 0:
	case 1:
		break;
	case 2:
		GetDlgItem(IDC_EDIT_DOMAIN_STREAMID)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DOMAIN_CHANNEL_NUMBER)->EnableWindow(FALSE);
		
		break;
	default:
		break;
	}
	UpdateData(FALSE);
	
}


NET_DVR_PU_STREAM_CFG_V41& CDlgUpStreamCfg::GetStreamCfg()
{
	return m_struStreamCfgV41; 
}

//更新结构体 
BOOL CDlgUpStreamCfg::UpdateStreamCfg(BOOL bUpdateStructure)
{
    UpdateData(TRUE); 
    NET_DVR_PU_STREAM_CFG_V41 & dt = m_struStreamCfgV41; 
    ZeroMemory(&dt, sizeof(dt));
    dt.dwSize = sizeof(NET_DVR_PU_STREAM_CFG_V41);
    dt.byStreamMode = m_comboStreamMode.GetCurSel() + 1;
    int i = 0;
    char temp[20] = {0};
    switch (dt.byStreamMode)
    {
        case 1:		/*IP或域名取流*/
            dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.byChanType = m_comboChannelType.GetCurSel();
            sprintf((char *)dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.byStreamId, "%s", m_strStreamId);
            sprintf((char *)dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.byAddress, "%s", m_RemoteIP);
            dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.wDVRPort = m_RemotePort;
            //dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.byChannel = (BYTE)m_RemoteSurveillace;
            dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.byTransProtocol = m_TransProtocolCombo.GetCurSel();
            dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.byTransMode = m_TransModeCombo.GetCurSel();
            dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.byResolution = m_cmResolution.GetCurSel()+1; 
            dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.byDeviceType = m_combDeviceType.GetCurSel()+1; 
            dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.byDispChan = m_bDispChan; 
            dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.bySubDispChan = m_bSubDispChan; 
            dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.dwChannel = m_RemoteSurveillace; 
            m_FacTypeCtrl.GetLBText(m_FacTypeCtrl.GetCurSel(), temp);
//             for (i = 0; i < m_struProtoList.dwProtoNum; i++)
//             {
//                 if (strcmp(temp, (const char *)m_struProtoList.struProto[i].byDescribe) == 0)
//                 {
//                     dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.byFactoryType = m_struProtoList.struProto[i].dwType;
//                     break;
//                 }
//             }
			{
				LPNET_DVR_PROTO_TYPE lpProtoType = (LPNET_DVR_PROTO_TYPE)m_struProtocolListV41.pBuffer; 
				for (i = 0; i < (int)m_struProtocolListV41.dwProtoNum; i++)
				{
					if (strcmp(temp, (const char *)lpProtoType->byDescribe) == 0)
					{
						dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.byFactoryType = lpProtoType->dwType;
						break;
					}
					++ lpProtoType; 
				}
			}
            sprintf((char *)dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.sPassword, "%s", m_RemotePass);
            sprintf((char *)dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.sUserName, "%s", m_RemoteUser);
            
            if (m_bUseStreamMedia)
            {
                dt.uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byValid = 1;
                dt.uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.wDevPort = m_dwStreamMediaPort;
                dt.uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byTransmitType = m_ComboStreamMediaPro.GetCurSel();
                sprintf((char *)dt.uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byAddress, "%s", m_strStreamMediaIp);		
            }
            break;
        case 2:		/*URL取流*/
            dt.uDecStreamMode.struUrlInfo.byEnable = 1;
            sprintf((char *)dt.uDecStreamMode.struUrlInfo.strURL, "%s", m_csUrl);
            dt.byStreamMode = 2;
            break;
        case 3:		/*动态域名取流*/
            sprintf((char *)dt.uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byDevAddress, "%s", m_strDomainName);
            dt.uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byTransProtocol = m_comboDomainTransPro.GetCurSel();
            dt.uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byTransMode = m_comboDomainTransMode.GetCurSel();
            dt.uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byDdnsType = m_comboDomainServerType.GetCurSel();
            sprintf((char *)dt.uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byDdnsAddress, "%s", m_strDomainServerIp);
            dt.uDecStreamMode.struDdnsDecInfo.struDdnsInfo.wDdnsPort = m_uiDomainServerPort;
            dt.uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byChanType = m_comboDomainChannelType.GetCurSel();
            
            m_comboDomainFacType.GetLBText(m_comboDomainFacType.GetCurSel(), temp);
			{
				LPNET_DVR_PROTO_TYPE lpProtoType = (LPNET_DVR_PROTO_TYPE)m_struProtocolListV41.pBuffer; 
				for (i = 0; i < (int)m_struProtocolListV41.dwProtoNum; i++)
				{
					if (strcmp(temp, (const char *)lpProtoType->byDescribe) == 0)
					{
						dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.byFactoryType = lpProtoType->dwType;
						break;
					}
					++ lpProtoType; 
				}
			}
		
//             for (i = 0; i < m_struProtoList.dwProtoNum; i++)
//             {
//                 if (strcmp(temp, (const char *)m_struProtoList.struProto[i].byDescribe) == 0)
//                 {
//                     dt.uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byFactoryType = m_struProtoList.struProto[i].dwType;
//                     break;
//                 }
//             }
            
            dt.uDecStreamMode.struDdnsDecInfo.struDdnsInfo.dwChannel = m_uiDomainChannelNum;
            sprintf((char *)dt.uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byStreamId, "%s", m_strDomainStreamId);
            
            sprintf((char *)dt.uDecStreamMode.struDdnsDecInfo.struDdnsInfo.sUserName, "%s", m_strDomainRemoteName);
            sprintf((char *)dt.uDecStreamMode.struDdnsDecInfo.struDdnsInfo.sPassword, "%s", m_strDomainRemotePass);
            dt.uDecStreamMode.struDdnsDecInfo.struDdnsInfo.wDevPort = m_wRemotePort;

            if (m_bDomainUseStreamMedia)
            {
                dt.uDecStreamMode.struDdnsDecInfo.struMediaServer.byValid = 1;
                dt.uDecStreamMode.struDdnsDecInfo.struMediaServer.wDevPort = m_uiDomainStreamMediaPort;
                dt.uDecStreamMode.struDdnsDecInfo.struMediaServer.byTransmitType = m_comboDomainStreamMediaPro.GetCurSel();
                sprintf((char *)dt.uDecStreamMode.struDdnsDecInfo.struMediaServer.byAddress, "%s", m_strDomainStreamMediaIp);		
            }
            break;
        default:
            break;
	}
	return TRUE; 
}

void CDlgUpStreamCfg::SetStreamCfg(const NET_DVR_PU_STREAM_CFG_V41& Cfg)
{
    memcpy(&m_struStreamCfgV41, &Cfg, sizeof(Cfg)); 
}

BOOL CDlgUpStreamCfg::UpdateStreamCfg()
{
    LPNET_DVR_PU_STREAM_CFG_V41 lpCfg = &m_struStreamCfgV41; 
    m_comboStreamMode.SetCurSel(lpCfg->byStreamMode-1);
    LPNET_DVR_DEV_CHAN_INFO_EX lpChanInfo = NULL; 
    LPNET_DVR_STREAM_MEDIA_SERVER lpMediaServer = NULL; 
    LPNET_DVR_PU_STREAM_URL lpURL  =NULL; 
    LPNET_DVR_DEV_DDNS_INFO lpDDNSInfo = NULL; 
    DWORD dwTemp; 
    int i = 0; 
    switch (lpCfg->byStreamMode)
        {
        case 1:		/*IP或域名取流*/
            lpChanInfo = &lpCfg->uDecStreamMode.struDecStreamDev.struDevChanInfo; 
            
            m_comboChannelType.SetCurSel(lpChanInfo->byChanType); 
            m_strStreamId.Format("%s", lpChanInfo->byStreamId);
            m_RemoteIP.Format("%s", lpChanInfo->byAddress); 
            m_RemotePort = lpChanInfo->wDVRPort; 
            m_TransProtocolCombo.SetCurSel(lpChanInfo->byTransProtocol); 
            m_TransModeCombo.SetCurSel(lpChanInfo->byTransMode); 
            m_cmResolution.SetCurSel(lpChanInfo->byResolution-1); 
            m_combDeviceType.SetCurSel(lpChanInfo->byDeviceType-1); 
            m_bDispChan = lpChanInfo->byDispChan; 
            m_bSubDispChan = lpChanInfo->bySubDispChan; 
            m_RemoteSurveillace = lpChanInfo->dwChannel; 
//            dwTemp = m_FacTypeCtrl.GetItemData(m_FacTypeCtrl.GetCurSel()); 
			{
				LPNET_DVR_PROTO_TYPE lpProtoType = (LPNET_DVR_PROTO_TYPE)m_struProtocolListV41.pBuffer; 
// 				for (i = 0; i < m_struProtocolListV41.dwProtoNum; i++)
// 				{
// 					if (dwTemp == lpChanInfo->byFactoryType)
// 					{
// 						m_FacTypeCtrl.SetCurSel(i); 
// 					}
// 				}
				DWORD dwCount = m_FacTypeCtrl.GetCount(); 
				for (i = 0; i < dwCount; i++)
				{
					dwTemp = m_FacTypeCtrl.GetItemData(i); 
					if (dwTemp == lpChanInfo->byFactoryType)
					{
						m_FacTypeCtrl.SetCurSel(i); 
						break; 
					}
				}
			}
		
            m_RemotePass.Format("%s", (char *)lpChanInfo->sPassword);
            m_RemoteUser.Format("%s", (char *)lpChanInfo->sUserName);

            lpMediaServer = &lpCfg->uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg; 
            m_bUseStreamMedia = lpMediaServer->byValid; 
            if (lpMediaServer->byValid)
            {
                m_dwStreamMediaPort = lpMediaServer->wDevPort; 
                m_ComboStreamMediaPro.SetCurSel(lpMediaServer->byTransmitType); 
                m_strStreamMediaIp.Format("%s", (char *)lpMediaServer->byAddress); 
            }
            break;
        case 2:		/*URL取流*/
            lpURL = &lpCfg->uDecStreamMode.struUrlInfo; 
            if (lpURL->byEnable )
            {
                m_csUrl.Format("%s", (char *)lpURL->strURL); 
            }
            break;
        case 3:		/*动态域名取流*/
            lpDDNSInfo = &lpCfg->uDecStreamMode.struDdnsDecInfo.struDdnsInfo; 
            m_strDomainName.Format("%s", (char *)lpDDNSInfo->byDevAddress); 
            m_comboDomainTransMode.SetCurSel(lpDDNSInfo->byTransProtocol); 
            m_comboDomainServerType.SetCurSel(lpDDNSInfo->byTransMode); 
            m_comboDomainServerType.SetCurSel(lpDDNSInfo->byDdnsType); 
            m_strDomainServerIp.Format("%s", lpDDNSInfo->byDdnsAddress);
            m_uiDomainServerPort = lpDDNSInfo->wDdnsPort; 
            m_comboDomainChannelType.SetCurSel(lpDDNSInfo->byChanType); 
            dwTemp = m_comboDomainFacType.GetItemData(m_comboDomainFacType.GetCurSel()); 
            for (i = 0; i < m_struProtocolListV41.dwProtoNum; i++)
            {
                if (dwTemp == lpDDNSInfo->byFactoryType)
                {
                    m_comboDomainFacType.SetCurSel(i); 
                }
            }
            m_uiDomainChannelNum = lpDDNSInfo->dwChannel; 
            m_strDomainStreamId.Format("%s", (char *)lpDDNSInfo->byStreamId); 
            m_strDomainRemoteName.Format("%s", (char *)lpDDNSInfo->sUserName); 
            m_strDomainRemotePass.Format("%s", (char *)lpDDNSInfo->sPassword); 
            m_wRemotePort = lpDDNSInfo->wDevPort;
            
            lpMediaServer = &lpCfg->uDecStreamMode.struDdnsDecInfo.struMediaServer; 
            m_bDomainUseStreamMedia = lpMediaServer->byValid; 
            if (lpMediaServer->byValid)
            {
                m_uiDomainStreamMediaPort = lpMediaServer->wDevPort; 
                m_comboDomainStreamMediaPro.SetCurSel(lpMediaServer->byTransmitType); 
                m_strDomainStreamMediaIp.Format("%s", (char *)lpMediaServer->byAddress); 
            }                
            break;
        default:
            break;
	}
    UpdateData(FALSE); 
    return TRUE; 
}


void CDlgUpStreamCfg::OnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
	UpdateStreamCfg(FALSE); 
    CDialog::OnOK(); 
}

void CDlgUpStreamCfg::EnableURLGroup(BOOL IsEnable)
{
    GetDlgItem(IDC_EDIT_URL)->EnableWindow(IsEnable);
}

void CDlgUpStreamCfg::EnableIpOrDomainGroup(BOOL IsEnable)
{
    
    UINT id[]={IDC_EDITREMOTEIP, IDC_EDITREMOTESURVE, IDC_EDITREMOTEPORT, IDC_EDITREMOTENAME, IDC_EDITREMOTEPASS,\
        IDC_COMBOPROTOCOL, IDC_COMBOTRANSMODE, IDC_COMBO_FACTYPE, IDC_USESTREAMMEDIA, IDC_STREAMMEDIAIP, IDC_STREAMMEDIAPORT, IDC_COMBOSTREAMMEDIAPRO, \
        IDC_EDIT_STREAMID, IDC_COMBO_CHANNEL_TYPE2};
    for (int i = 0; i < sizeof(id)/sizeof(UINT); i++)
    {
        GetDlgItem(id[i])->EnableWindow(IsEnable);
    }
    
    if (IsEnable)
    {
		OnBnClickedUsestreammedia(); 
        OnSelchangeComboChannelType2(); 
    }
}

void CDlgUpStreamCfg::oncbnChangeStreamMode()
{
	// TODO: 在此添加控件通知处理程序代码
	switch (m_comboStreamMode.GetCurSel())
	{
	case 0:	/*IP或域名取流*/
		EnableIpOrDomainGroup(TRUE);
		EnableURLGroup(FALSE);
		EnableDynamicDDNSGroup(FALSE);
		break;
	case 1:	/*URL取流*/
		EnableIpOrDomainGroup(FALSE);
		EnableURLGroup(TRUE);
		EnableDynamicDDNSGroup(FALSE);
		break;
	case 2:	/*动态域名解析取流*/
		EnableIpOrDomainGroup(FALSE);
		EnableURLGroup(FALSE);
		EnableDynamicDDNSGroup(TRUE);
		break;
	default:
		break;
	}   
}

void CDlgUpStreamCfg::OnBnClickedUsestreammedia()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_bUseStreamMedia)
	{
		GetDlgItem(IDC_STREAMMEDIAIP)->EnableWindow(TRUE);
		GetDlgItem(IDC_STREAMMEDIAPORT)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBOSTREAMMEDIAPRO)->EnableWindow(TRUE);
		UpdateData(FALSE);
	}
	else
	{
		GetDlgItem(IDC_STREAMMEDIAIP)->EnableWindow(FALSE);
		GetDlgItem(IDC_STREAMMEDIAPORT)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBOSTREAMMEDIAPRO)->EnableWindow(FALSE);
	}	
	UpdateData(FALSE);	
}

void CDlgUpStreamCfg::OnBnClickedChkDomainUsestreammedia()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_bDomainUseStreamMedia)
	{
		GetDlgItem(IDC_EDIT_DOMAIN_STREAMMEDIAIP)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DOMAIN_STREAMMEDIAPORT)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_DOMAIN_STREAMMEDIAPRO)->EnableWindow(TRUE);
		UpdateData(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_DOMAIN_STREAMMEDIAIP)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DOMAIN_STREAMMEDIAPORT)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_DOMAIN_STREAMMEDIAPRO)->EnableWindow(FALSE);
	}	
	UpdateData(FALSE);	
}
