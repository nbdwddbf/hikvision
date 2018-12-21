// MatDynamicTest.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "MatDynamicTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMatDynamicTest dialog


CMatDynamicTest::CMatDynamicTest(CWnd* pParent /*=NULL*/)
	: CDialog(CMatDynamicTest::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMatDynamicTest)
	m_RemoteIP = _T("172.10.33.10");
	m_RemoteSurveillace = 1;
	m_RemoteUser = _T("admin");
	m_RemotePass = _T("12345");
	m_strStreamMediaIp = _T("172.10.33.10");
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
	m_csDecodeChanTitle = _T("");
	m_dwSubWinNo = 0;
	m_dwWallNo = 0;
	m_dwWinNo = 0;
	//}}AFX_DATA_INIT
    memset(&m_struProtoList, 0, sizeof(m_struProtoList));
}


void CMatDynamicTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMatDynamicTest)
	DDX_Control(pDX, IDC_COMBO_CHANNEL_TYPE2, m_comboChannelType);
	DDX_Control(pDX, IDC_COMBO_DOMAIN_TRANS_PRO, m_comboDomainTransPro);
	DDX_Control(pDX, IDC_COMBO_DOMAIN_TRANSMODE, m_comboDomainTransMode);
	DDX_Control(pDX, IDC_COMBO_DOMAIN_STREAMMEDIAPRO, m_comboDomainStreamMediaPro);
	DDX_Control(pDX, IDC_COMBO_DOMAIN_SERVER_TYPE, m_comboDomainServerType);
	DDX_Control(pDX, IDC_COMBO_DOMAIN_FACTYPE, m_comboDomainFacType);
	DDX_Control(pDX, IDC_COMBO_DOMAIN_CHANNEL_TYPE, m_comboDomainChannelType);
	DDX_Control(pDX, IDC_COMBO_STREAM_MODE, m_comboStreamMode);
	DDX_Control(pDX, IDC_COMBO_FACTYPE, m_FacTypeCtrl);
	DDX_Control(pDX, IDC_COMBOSTREAMMEDIAPRO, m_ComboStreamMediaPro);
	DDX_Control(pDX, IDC_COMBODECCHANNUM, m_DecChanCombo);
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
	DDX_Text(pDX, IDC_STATIC_DECODEORWINNO, m_csDecodeChanTitle);
	DDX_Text(pDX, IDC_EDIT_DYNAMIC_SUBWINNO, m_dwSubWinNo);
	DDX_Text(pDX, IDC_EDIT_DYNAMIC_WALLNO, m_dwWallNo);
	DDX_Text(pDX, IDC_EDIT_DYNAMIC_WINNO, m_dwWinNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMatDynamicTest, CDialog)
	//{{AFX_MSG_MAP(CMatDynamicTest)
	ON_BN_CLICKED(IDC_STARTDYNAMIC, OnStartdynamic)
	ON_BN_CLICKED(IDC_STOPDYNAMIC, OnStopdynamic)
	ON_BN_CLICKED(IDC_USESTREAMMEDIA, OnUsestreammedia)
	ON_CBN_SELCHANGE(IDC_COMBO_STREAM_MODE, OnSelchangeComboStreamMode)
	ON_BN_CLICKED(IDC_CHK_DOMAIN_USESTREAMMEDIA, OnChkDomainUsestreammedia)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL_TYPE2, OnSelchangeComboChannelType2)
	ON_CBN_SELCHANGE(IDC_COMBO_DOMAIN_CHANNEL_TYPE, OnSelchangeComboDomainChannelType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatDynamicTest message handlers

void CMatDynamicTest::OnStartdynamic() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	NET_DVR_PU_STREAM_CFG_V41 dt;
	ZeroMemory(&dt, sizeof(dt));
	dt.dwSize = sizeof(NET_DVR_PU_STREAM_CFG_V41);
	dt.byStreamMode = m_comboStreamMode.GetCurSel() + 1;
	//dt.byStreamMode = 1;
	int i = 0;
	char temp[20] = {0};
	switch (dt.byStreamMode)
	{
	case 1:		/*IP或域名取流*/
		dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.byChanType = m_comboChannelType.GetCurSel();
		sprintf((char *)dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.byStreamId, "%s", m_strStreamId);
		sprintf((char *)dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.byAddress, "%s", m_RemoteIP);
		dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.wDVRPort = m_RemotePort;
		dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.byChannel = 0;
		dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.byTransProtocol = m_TransProtocolCombo.GetCurSel();
		dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.byTransMode = m_TransModeCombo.GetCurSel();
        dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.dwChannel = (DWORD)m_RemoteSurveillace;
       
		m_FacTypeCtrl.GetLBText(m_FacTypeCtrl.GetCurSel(), temp);
		for (i = 0; i < m_struProtoList.dwProtoNum; i++)
		{
			if (strcmp(temp, (const char *)m_struProtoList.struProto[i].byDescribe) == 0)
			{
				dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.byFactoryType = m_struProtoList.struProto[i].dwType;
				break;
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
		for (i = 0; i < m_struProtoList.dwProtoNum; i++)
		{
			if (strcmp(temp, (const char *)m_struProtoList.struProto[i].byDescribe) == 0)
			{
				dt.uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byFactoryType = m_struProtoList.struProto[i].dwType;
				break;
			}
		}

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
	DWORD dwDecChanNum =  m_DecChanCombo.GetCurSel()+m_lStartChan;
	if ( m_BUseWinNo )
	{
		dwDecChanNum = m_dwWinNo + ((m_dwSubWinNo&0xff) << 16) + ((m_dwWallNo&0xff) << 24); 
	}
	if (!NET_DVR_MatrixStartDynamic_V41(m_lServerID, dwDecChanNum, &dt))
	{
		CString tmp;
		tmp.Format("Error: NET_DVR_MatrixStartDynamic = %d\n", NET_DVR_GetLastError());
		AfxMessageBox(tmp);
		return;
	}

	MessageBox("Start successfully!");
}

void CMatDynamicTest::OnStopdynamic() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwDecChanNum =  m_DecChanCombo.GetCurSel()+m_lStartChan;
	if ( m_BUseWinNo )
	{
		dwDecChanNum = m_dwWinNo + ((m_dwSubWinNo&0xff) << 16) + ((m_dwWallNo&0xff) << 24); 
	}
	if (!NET_DVR_MatrixStopDynamic(m_lServerID, dwDecChanNum))
	{
		TRACE("\nError: NET_DVR_MatrixStopDynamic = %d\n", NET_DVR_GetLastError());
        CString str;
        str.Format("Error Code : %d", NET_DVR_GetLastError());
        AfxMessageBox(str);
		return;
	}
	char szLan[128] = {0};
	g_StringLanType(szLan, "成功停止", "Stop successfully");
	AfxMessageBox(szLan);
}

BOOL CMatDynamicTest::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_lDeviceID = g_pMainDlg->GetCurDeviceIndex(); 
	// TODO: Add extra initialization here
	CString tmp;
	char szLan[128] = {0};
	g_StringLanType(szLan, "通道", "Channel");
	for (int i=0; i<m_iChannelnumber;i++)
	{
		tmp.Format("%s%d", szLan, i + m_lStartChan);
		m_DecChanCombo.AddString(tmp);
	}

    if (NET_DVR_GetIPCProtoList(m_lServerID, &m_struProtoList))
    {
        for (int i = 0; i < (int)m_struProtoList.dwProtoNum; i++)
        {
            memset(szLan, 0, DESC_LEN);
            memcpy(szLan, m_struProtoList.struProto[i].byDescribe, DESC_LEN);
            m_FacTypeCtrl.AddString(szLan);
			m_comboDomainFacType.AddString(szLan);
		}
        m_FacTypeCtrl.SetCurSel(0);
		m_comboDomainFacType.SetCurSel(0);
    } 
	else
	{
		MessageBox(NET_DVR_GetErrorMsg());
	}

	m_DecChanCombo.SetCurSel(0);
	m_TransProtocolCombo.SetCurSel(0);
	m_TransModeCombo.SetCurSel(0);
    m_bUseStreamMedia = 0;
	m_comboChannelType.SetCurSel(0);
	m_ComboStreamMediaPro.SetCurSel(0);
	
	m_comboDomainServerType.SetCurSel(0);
	m_comboDomainFacType.SetCurSel(0);
	m_comboDomainTransPro.SetCurSel(0);
	m_comboDomainTransMode.SetCurSel(0);
	m_comboDomainChannelType.SetCurSel(0);
	m_comboDomainStreamMediaPro.SetCurSel(0);
	m_BUseWinNo = IsDevWinControl(m_lDeviceID); 
	if (m_BUseWinNo)
	{
		m_csDecodeChanTitle = "墙号.子窗口.窗口"; 
		GetDlgItem(IDC_COMBODECCHANNUM)->ShowWindow(SW_HIDE); 
		GetDlgItem(IDC_EDIT_DYNAMIC_WALLNO)->ShowWindow(SW_SHOW); 
		GetDlgItem(IDC_EDIT_DYNAMIC_SUBWINNO)->ShowWindow(SW_SHOW); 
		GetDlgItem(IDC_EDIT_DYNAMIC_WINNO)->ShowWindow(SW_SHOW); 
	}
	UpdateData(FALSE);
    //OnUsestreammedia();
	//OnSelchangeComboDomainChannelType();
	m_comboStreamMode.SetCurSel(0);
	OnSelchangeComboStreamMode();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMatDynamicTest::OnUsestreammedia() 
{
	// TODO: Add your control notification handler code here
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

void CMatDynamicTest::EnableIpOrDomainGroup(BOOL IsEnable)
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
		OnUsestreammedia();
		OnSelchangeComboChannelType2(); 
	}
}

void CMatDynamicTest::EnableURLGroup(BOOL IsEnable)
{
	GetDlgItem(IDC_EDIT_URL)->EnableWindow(IsEnable);
}
	
void CMatDynamicTest::EnableDynamicDDNSGroup(BOOL IsEnable)
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
		OnChkDomainUsestreammedia();
		OnSelchangeComboDomainChannelType();
	}
}


void CMatDynamicTest::OnSelchangeComboStreamMode() 
{
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


void CMatDynamicTest::OnChkDomainUsestreammedia() 
{
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

void CMatDynamicTest::OnSelchangeComboChannelType2() 
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

void CMatDynamicTest::OnSelchangeComboDomainChannelType() 
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
