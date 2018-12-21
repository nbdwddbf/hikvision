// MatCycLink.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "MatCycLink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMatCycLink dialog


CMatCycLink::CMatCycLink(CWnd* pParent /*=NULL*/)
	: CDialog(CMatCycLink::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMatCycLink)
	m_DVRIP = _T("172.9.3.11");
	m_DVRPasswd = _T("12345");
	m_DVRPort = 80;
	m_DVRUser = _T("admin");
	m_PoolTime = 0;
	m_bCheckConnectChan = FALSE;
	m_bUseStreamMedia = FALSE;
	m_strStreamMediaIp = _T("");
	m_dwStreamMediaPort = 0;
	m_bUseUrl = FALSE;
	m_csUrl = _T("");
	m_bDomainUseStreamMedia = FALSE;
	m_dwDomainChannelNum = 0;
	m_strDomainIp = _T("");
	m_strDomainRemoteName = _T("admin");
	m_strDomainRemotePass = _T("12345");
	m_strDomainServerIp = _T("172.9.3.11");
	m_wDomainServerPort = 80;
	m_strDomainStreamId = _T("");
	m_strDomainStreamIdIP = _T("");
	m_wDomainStreamMediaPort = 0;
	m_strStreamID = _T("");
	m_byChannelNum = 0;
	m_wDomainDevPort = 8000;
	m_csDecodeChanTitle = _T("");
	m_dwSubWinNo = 0;
	m_dwWallNo = 0;
	m_dwWinNo = 0;
	//}}AFX_DATA_INIT
	m_iChanSel = -1;
	for (int i=0; i<32; i++)
	{
		m_CycLink[i] = FALSE;
	}
    memset(&m_struProtoList, 0, sizeof(m_struProtoList));
	memset(&m_MatLoopDec, 0, sizeof(NET_DVR_MATRIX_LOOP_DECINFO_V41));
	memset(m_iWin, 0xffffffff, sizeof(m_iWin)); 
}


void CMatCycLink::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMatCycLink)
	DDX_Control(pDX, IDC_COMBO_IP_CHANNEL_TYPE, m_comboChannelType);
	DDX_Control(pDX, IDC_COMBOSWITCH, m_comboSwitch);
	DDX_Control(pDX, IDC_COMBO_DOMAIN_TRANSMODE, m_comboDomainTransMode);
	DDX_Control(pDX, IDC_COMBO_DOMAIN_STREAMMEDIAPRO, m_comboDomainStreamMediaPro);
	DDX_Control(pDX, IDC_COMBO_DOMAIN_TRANS_PRO, m_comboDomainTransPro);
	DDX_Control(pDX, IDC_COMBO_DOMAIN_SERVER_TYPE, m_comboDomainServerType);
	DDX_Control(pDX, IDC_COMBO_DOMAIN_FACTYPE, m_comboDomainFacType);
	DDX_Control(pDX, IDC_COMBO_DOMAIN_CHANNEL_TYPE, m_comboDomainChanneType);
	DDX_Control(pDX, IDC_COMBO_STREAM_MODE, m_comboStreamMode);
	DDX_Control(pDX, IDC_COMBO_FACTYPE, m_FacTypeCtrl);
	DDX_Control(pDX, IDC_COMBOSTREAMMEDIAPRO, m_ComboStreamMediaPro);
	DDX_Control(pDX, IDC_COMBOTRANSTYPE, m_TransModesCombo);
	DDX_Control(pDX, IDC_COMBOTRANSMODE, m_TransProtocolCombo);
	DDX_Control(pDX, IDC_COMBODECCHAN, m_DecChanCombo);
	DDX_Control(pDX, IDC_COMBO_CONNECT_CHANNEL, m_ConnectChanCombo);
	DDX_Text(pDX, IDC_EDITDVRIP, m_DVRIP);
	DDX_Text(pDX, IDC_EDITDVRPASSWD, m_DVRPasswd);
	DDX_Text(pDX, IDC_EDITDVRPORT, m_DVRPort);
	DDX_Text(pDX, IDC_EDITDVRUSER, m_DVRUser);
	DDX_Text(pDX, IDC_EDIT_POOLTIME, m_PoolTime);
	DDX_Check(pDX, IDC_CHECKCONCHAN, m_bCheckConnectChan);
	DDX_Check(pDX, IDC_USESTREAMMEDIA, m_bUseStreamMedia);
	DDX_Text(pDX, IDC_STREAMMEDIAIP, m_strStreamMediaIp);
	DDX_Text(pDX, IDC_STREAMMEDIAPORT, m_dwStreamMediaPort);
	DDX_Text(pDX, IDC_EDIT_URL, m_csUrl);
	DDX_Check(pDX, IDC_CHK_DOMAIN_USESTREAMMEDIA, m_bDomainUseStreamMedia);
	DDX_Text(pDX, IDC_EDIT_DOMAIN_CHANNEL_NUMBER, m_dwDomainChannelNum);
	DDX_Text(pDX, IDC_EDIT_DOMAIN_NAME, m_strDomainIp);
	DDX_Text(pDX, IDC_EDIT_DOMAIN_REMOTENAME, m_strDomainRemoteName);
	DDX_Text(pDX, IDC_EDIT_DOMAIN_REMOTEPASS, m_strDomainRemotePass);
	DDX_Text(pDX, IDC_EDIT_DOMAIN_SERVER_IP, m_strDomainServerIp);
	DDX_Text(pDX, IDC_EDIT_DOMAIN_SERVER_PORT, m_wDomainServerPort);
	DDX_Text(pDX, IDC_EDIT_DOMAIN_STREAMID, m_strDomainStreamId);
	DDX_Text(pDX, IDC_EDIT_DOMAIN_STREAMMEDIAIP, m_strDomainStreamIdIP);
	DDX_Text(pDX, IDC_EDIT_DOMAIN_STREAMMEDIAPORT, m_wDomainStreamMediaPort);
	DDX_Text(pDX, IDC_EDIT_IP_STREAM_ID, m_strStreamID);
	DDX_Text(pDX, IDC_EDIT_CHANNEL_NUM, m_byChannelNum);
	DDX_Text(pDX, IDC_EDIT_DOMAIN_DEV_PORT, m_wDomainDevPort);
	DDX_Text(pDX, IDC_STATIC_CYCLE_DECODECHAN, m_csDecodeChanTitle);
	DDX_Text(pDX, IDC_EDIT_CYCLE_SUBWINNO, m_dwSubWinNo);
	DDX_Text(pDX, IDC_EDIT_CYCLE_WALLNO, m_dwWallNo);
	DDX_Text(pDX, IDC_EDIT_CYCLE_WINNO, m_dwWinNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMatCycLink, CDialog)
	//{{AFX_MSG_MAP(CMatCycLink)
	ON_CBN_SELCHANGE(IDC_COMBODECCHAN, OnSelchangeCombodecchan)
	ON_CBN_SELCHANGE(IDC_COMBO_CONNECT_CHANNEL, OnSelchangeComboconchan)
	ON_BN_CLICKED(IDC_SINGLEGET, OnSingleget)
	ON_BN_CLICKED(IDC_WHOLEGET, OnWholeget)
	ON_BN_CLICKED(IDC_SINGLESET, OnSingleset)
	ON_BN_CLICKED(IDC_USESTREAMMEDIA, OnUsestreammedia)
	ON_CBN_SELCHANGE(IDC_COMBO_STREAM_MODE, OnSelchangeComboStreamMode)
	ON_BN_CLICKED(IDC_CHK_DOMAIN_USESTREAMMEDIA, OnChkDomainUsestreammedia)
	ON_BN_CLICKED(IDC_URL_SAVEPARA, OnUrlSavepara)
	ON_BN_CLICKED(IDC_DOMAIN_SAVEPARA, OnDomainSavepara)
	ON_BN_CLICKED(IDC_IP_SAVEPARA, OnIpSavepara)
	ON_BN_CLICKED(IDC_BTN_SET_DEC_CYCLE_PARM, OnBtnSetDecCycleParm)
	ON_CBN_SELCHANGE(IDC_COMBO_IP_CHANNEL_TYPE, OnSelchangeComboIpChannelType)
	ON_CBN_SELCHANGE(IDC_COMBO_DOMAIN_CHANNEL_TYPE, OnSelchangeComboDomainChannelType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatCycLink message handlers

BOOL CMatCycLink::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int i = 0;

	ZeroMemory(&m_MatLoopDec, sizeof(NET_DVR_MATRIX_LOOP_DECINFO_V41));
	// TODO: Add extra initialization here
	char szLan [128] = {0};
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
	DWORD chanNum = 0;
	CString tmp;
	for (i=0; i<m_iChannelnumber; i++)
	{
		chanNum = i + m_lStartChan;
		tmp.Format("%d", chanNum);
		m_DecChanCombo.AddString(tmp);
	}
// 	m_DecChanCombo.SetCurSel(0);
// 	OnSelchangeCombodecchan();	
// 	if (!NET_DVR_MatrixGetLoopDecChanInfo_V41(m_lServerID, m_lStartChan, &m_MatLoopDec))
// 	{
// 		TRACE("\nError: NET_DVR_MatrixGetLoopDecChanInfo[%d] = %d\n", i, NET_DVR_GetLastError());
// 	}
// 	else
// 	{
// 		TRACE("NET_DVR_MatrixGetLoopDecChanInfo_V41 succ");
//     }
// 
// 	if (!NET_DVR_MatrixGetLoopDecChanEnable(m_lServerID, m_lStartChan, &chanNum))
// 	{
// 		TRACE("\nError: NET_DVR_MatrixGetLoopDecChanEnable = %d\n", NET_DVR_GetLastError());
// 	}
// 	else
// 	{
// 		m_comboSwitch.SetCurSel(chanNum);
// 	}

	for (i=0; i<MAX_CYCLE_CHAN_V30; i++)
	{
		tmp.Format("%d", i + m_lStartChan);
		m_ConnectChanCombo.AddString(tmp);
	}	
	m_PoolTime = m_MatLoopDec.dwPoolTime;
	m_bCheckConnectChan = m_MatLoopDec.struchanConInfo[0].byEnable;
	m_ConnectChanCombo.SetCurSel(0);
	m_lDeviceID = g_pMainDlg->GetCurDeviceIndex(); 
	m_BUseWinNo = IsDevWinControl(m_lDeviceID); 
	if (m_BUseWinNo)
	{
		m_csDecodeChanTitle = "墙号.子窗口.窗口"; 
		GetDlgItem(IDC_COMBODECCHAN)->ShowWindow(SW_HIDE); 
		GetDlgItem(IDC_WHOLEGET)->ShowWindow(SW_HIDE); 	
		GetDlgItem(IDC_EDIT_CYCLE_WALLNO)->ShowWindow(SW_SHOW); 
		GetDlgItem(IDC_EDIT_CYCLE_SUBWINNO)->ShowWindow(SW_SHOW); 
		GetDlgItem(IDC_EDIT_CYCLE_WINNO)->ShowWindow(SW_SHOW); 
	}
	UpdateData(FALSE);
	OnSelchangeComboconchan();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CMatCycLink::OnSelchangeCombodecchan() 
{
	// TODO: Add your control notification handler code here
	int sel = m_DecChanCombo.GetCurSel();
	if (sel == m_iChanSel)
	{
		return;
	}
	m_iChanSel = sel;
	
	m_comboSwitch.SetCurSel(m_CycLink[sel]);
	UpdateData(FALSE);

	if (!NET_DVR_MatrixGetLoopDecChanInfo_V41(m_lServerID, m_iChanSel + m_lStartChan, &m_MatLoopDec))
	{
		g_pMainDlg->AddLog(g_struDeviceInfo[m_lServerID].iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_MatrixGetLoopDecChanInfo_V41");
		TRACE("\nError: NET_DVR_MatrixGetLoopDecChanInfo[%d] = %d\n", m_iChanSel + m_lStartChan, NET_DVR_GetLastError());
    }
	else
	{
		g_pMainDlg->AddLog(g_struDeviceInfo[m_lStartChan].iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_MatrixGetLoopDecChanInfo_V41");
	}

	m_PoolTime = m_MatLoopDec.dwPoolTime;
	m_ConnectChanCombo.SetCurSel(0);
	m_bCheckConnectChan = m_MatLoopDec.struchanConInfo[0].byEnable;
	if (m_MatLoopDec.struchanConInfo[0].byEnable)
	{
		int i = 0;
		m_comboStreamMode.SetCurSel(m_MatLoopDec.struchanConInfo[m_iChanSel].byStreamMode);
		switch (m_MatLoopDec.struchanConInfo[m_iChanSel].byStreamMode)
		{
		case 0:
			break;
		case 1:		/*IP或域名取流*/
			m_ConnectChanCombo.SetCurSel(0);
			OnSelchangeComboconchan();
			break;
		case 2:		/*URL取流*/
			m_csUrl.Format("%s", m_MatLoopDec.struchanConInfo[m_iChanSel].uDecStreamMode.struUrlInfo.strURL);
			break;
		case 3:		/*DDNS动态取流*/
			m_strDomainIp.Format("%s", m_MatLoopDec.struchanConInfo[m_iChanSel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byDevAddress);
			m_comboDomainServerType.SetCurSel(m_MatLoopDec.struchanConInfo[m_iChanSel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byDdnsType);
			m_strDomainServerIp.Format("%s", m_MatLoopDec.struchanConInfo[m_iChanSel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byDdnsAddress);
			m_wDomainServerPort = m_MatLoopDec.struchanConInfo[m_iChanSel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.wDdnsPort;
			m_comboDomainTransPro.SetCurSel(m_MatLoopDec.struchanConInfo[m_iChanSel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byTransProtocol);
			m_comboDomainTransMode.SetCurSel(m_MatLoopDec.struchanConInfo[m_iChanSel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byTransMode);
			m_strDomainRemoteName.Format("%s", m_MatLoopDec.struchanConInfo[m_iChanSel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.sUserName);
			m_strDomainRemotePass.Format("%s", m_MatLoopDec.struchanConInfo[m_iChanSel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.sPassword);
			m_comboDomainChanneType.SetCurSel(m_MatLoopDec.struchanConInfo[m_iChanSel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byChanType);
			m_comboDomainFacType.SetCurSel(m_MatLoopDec.struchanConInfo[m_iChanSel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byFactoryType);
			m_strDomainStreamId.Format("%s", m_MatLoopDec.struchanConInfo[m_iChanSel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byStreamId);
			m_dwDomainChannelNum = m_MatLoopDec.struchanConInfo[m_iChanSel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.dwChannel;
			m_wDomainDevPort = m_MatLoopDec.struchanConInfo[m_iChanSel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.wDevPort;

			m_bDomainUseStreamMedia = m_MatLoopDec.struchanConInfo[m_iChanSel].uDecStreamMode.struDdnsDecInfo.struMediaServer.byValid;
			if (m_bDomainUseStreamMedia)
			{
				m_strDomainStreamIdIP.Format("%s", m_MatLoopDec.struchanConInfo[m_iChanSel].uDecStreamMode.struDdnsDecInfo.struMediaServer.byAddress);
				m_wDomainStreamMediaPort = m_MatLoopDec.struchanConInfo[m_iChanSel].uDecStreamMode.struDdnsDecInfo.struMediaServer.wDevPort;
				m_comboDomainStreamMediaPro.SetCurSel(m_MatLoopDec.struchanConInfo[m_iChanSel].uDecStreamMode.struDdnsDecInfo.struMediaServer.byTransmitType);
			}
			break;
		default:
			break;
		}
		OnSelchangeComboStreamMode();
	}
	UpdateData(FALSE);
}

void CMatCycLink::OnSelchangeComboconchan() 
{
	// TODO: Add your control notification handler code here
	int sel = m_ConnectChanCombo.GetCurSel();
	int i = 0;
	m_comboStreamMode.SetCurSel(m_MatLoopDec.struchanConInfo[sel].byStreamMode);
	OnSelchangeComboStreamMode();
	m_bCheckConnectChan = m_MatLoopDec.struchanConInfo[sel].byEnable;
	TRACE("\n### m_bCheckConnectChan = 0x%x\n", m_bCheckConnectChan);

	switch (m_MatLoopDec.struchanConInfo[sel].byStreamMode)
	{
	case 0:
		m_comboChannelType.SetCurSel(0);
		OnSelchangeComboIpChannelType(); 
		m_DVRPort = 8000;
		m_byChannelNum = 0;
		m_DVRUser = _T("admin");
		m_DVRPasswd = "12345";
		m_TransModesCombo.SetCurSel(0);
		m_TransProtocolCombo.SetCurSel(0);
		m_FacTypeCtrl.SetCurSel(0);
		m_bUseStreamMedia = FALSE;
		m_ComboStreamMediaPro.SetCurSel(0);
		m_dwStreamMediaPort = 554;
		m_strStreamMediaIp = "172.9.10.10";
		
		m_comboDomainTransPro.SetCurSel(0);
		m_comboDomainTransMode.SetCurSel(0);
		m_comboDomainServerType.SetCurSel(0);
		m_wDomainServerPort = 8000;
		m_comboDomainChanneType.SetCurSel(0);
		m_comboDomainFacType.SetCurSel(0);
		m_dwDomainChannelNum= 0;
		m_strDomainRemoteName = _T("admin");
		m_strDomainRemotePass = "12345";
		m_bDomainUseStreamMedia = FALSE;
		m_comboDomainStreamMediaPro.SetCurSel(0);
		m_wDomainStreamMediaPort = 554;
		m_strDomainStreamIdIP = "172.9.10.10";
		m_wDomainDevPort = 8000;
		break;
	case 1:
		
		m_comboChannelType.SetCurSel(m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byChanType);
		UpdateData(FALSE);
		OnSelchangeComboIpChannelType(); 
		m_strStreamID.Format("%s", m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byStreamId);
		m_DVRIP.Format("%s", m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byAddress);
		m_DVRPort = m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.wDVRPort;
		if (m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.dwChannel == 0)
		{
			m_byChannelNum = m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byChannel;
		}
		else
		{
			m_byChannelNum = m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.dwChannel;
		}

		m_DVRUser.Format("%s", m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.sUserName);
		m_DVRPasswd.Format("%s", m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.sPassword);
		m_TransModesCombo.SetCurSel(m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byTransMode);
		m_TransProtocolCombo.SetCurSel(m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byTransProtocol);
		//m_FacTypeCtrl.SetCurSel(m_MatLoopDec.struchanConInfo[sel].struDevChanInfo.byFactoryType);
		
		for(i = 0; i < m_struProtoList.dwProtoNum; i++)
		{
			if (m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byFactoryType == m_struProtoList.struProto[i].dwType) 
			{
				m_FacTypeCtrl.SetCurSel(i);
				break;
			}
		}
		if (i >= m_struProtoList.dwProtoNum) 
		{
			m_FacTypeCtrl.SetCurSel(-1);
		}

		m_bUseStreamMedia = m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byValid;
		if (m_bUseStreamMedia)
		{
			m_dwStreamMediaPort = m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.wDevPort;
			m_strStreamMediaIp.Format("%s", m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byAddress);
			m_ComboStreamMediaPro.SetCurSel(m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byTransmitType);
		}

		m_comboDomainTransPro.SetCurSel(0);
		m_comboDomainTransMode.SetCurSel(0);
		m_comboDomainServerType.SetCurSel(0);
		m_wDomainServerPort = 8000;
		m_comboDomainChanneType.SetCurSel(0);
		m_comboDomainFacType.SetCurSel(0);
		m_dwDomainChannelNum= 0;
		m_strDomainRemoteName = _T("admin");
		m_strDomainRemotePass = "12345";
		m_bDomainUseStreamMedia = FALSE;
		break;
	case 2:
		m_csUrl.Format("%s", m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struUrlInfo.strURL);
		break;
	case 3:

		m_comboChannelType.SetCurSel(0);
		m_DVRPort = 8000;
		m_byChannelNum = 0;
		m_DVRUser = _T("admin");
		m_DVRPasswd = "12345";
		m_TransModesCombo.SetCurSel(0);
		m_TransProtocolCombo.SetCurSel(0);
		m_FacTypeCtrl.SetCurSel(0);
		m_bUseStreamMedia = FALSE;

		m_strDomainIp.Format("%s", m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byDevAddress);
		m_comboDomainTransPro.SetCurSel(m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byTransProtocol);
		m_comboDomainTransMode.SetCurSel(m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byTransMode);
		m_comboDomainServerType.SetCurSel(m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byDdnsType);
		m_strDomainServerIp.Format("%s", m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byDdnsAddress);
		m_wDomainServerPort = m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.wDdnsPort;
		m_comboDomainChanneType.SetCurSel(m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byChanType);
		UpdateData(FALSE);
		OnSelchangeComboDomainChannelType(); 
		m_comboDomainFacType.SetCurSel(m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byFactoryType);
		m_dwDomainChannelNum = m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.dwChannel;
		m_strDomainStreamId.Format("%s", m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byStreamId);
		m_strDomainRemoteName.Format("%s", m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.sUserName);
		m_strDomainRemotePass.Format("%s", m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.sPassword);
		m_wDomainDevPort = m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.wDevPort;

		m_bDomainUseStreamMedia = m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struMediaServer.byValid;
		if (m_bDomainUseStreamMedia)
		{
			m_strDomainStreamIdIP.Format("%s", m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struMediaServer.byAddress);
			m_comboDomainStreamMediaPro.SetCurSel(m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struMediaServer.byTransmitType);
			m_wDomainStreamMediaPort = m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struMediaServer.wDevPort;
		}
		break;
	default:
		break;
	}

	UpdateData(FALSE);
	OnUsestreammedia();
	OnChkDomainUsestreammedia(); 
	OnSelchangeComboIpChannelType();
	OnSelchangeComboDomainChannelType();
		

}

void CMatCycLink::OnIpSavepara() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	m_MatLoopDec.dwPoolTime = m_PoolTime;
	int sel = m_ConnectChanCombo.GetCurSel();
	ZeroMemory(&m_MatLoopDec.struchanConInfo[sel], sizeof(m_MatLoopDec.struchanConInfo[sel]));	
	m_MatLoopDec.struchanConInfo[sel].byEnable = m_bCheckConnectChan;

	m_MatLoopDec.struchanConInfo[sel].byStreamMode = m_comboStreamMode.GetCurSel();
	m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byChanType = m_comboChannelType.GetCurSel();
	sprintf((char *)m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byStreamId, "%s", m_strStreamID);
	sprintf((char *)m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byAddress, "%s", m_DVRIP);
	m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.wDVRPort = m_DVRPort;

	//byChannel字段不使用了（赋0表示无效），使用兼容的新字段dwChannel
	m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byChannel = 0;
	m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.dwChannel = m_byChannelNum;
	m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byTransProtocol = m_TransProtocolCombo.GetCurSel();
	m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byTransMode = m_TransModesCombo.GetCurSel();

	char temp[20] = {0};
    m_FacTypeCtrl.GetLBText(m_FacTypeCtrl.GetCurSel(), temp); 
    for (int i = 0; i < m_struProtoList.dwProtoNum; i++)
    {
        if (strcmp(temp, (const char *)m_struProtoList.struProto[i].byDescribe) == 0)
        {
            m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byFactoryType = m_struProtoList.struProto[i].dwType;
            break;
        }
    }

    sprintf((char *)m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.sUserName, "%s", m_DVRUser);
	sprintf((char *)m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.sPassword, "%s", m_DVRPasswd);
    //TRACE("m_bUseStreamMedia ==== %d", m_bUseStreamMedia);
    if (m_bUseStreamMedia)
    {
		m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byValid = m_bUseStreamMedia;
        m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.wDevPort = m_dwStreamMediaPort;
        m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byTransmitType = m_ComboStreamMediaPro.GetCurSel();
        sprintf((char *)m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byAddress, "%s", m_strStreamMediaIp);
        //TRACE(m_MatLoopDec.struchanConInfo[sel].streamMediaServerCfg.byAddress);
    }		
		
}

void CMatCycLink::OnUrlSavepara() 
{
	UpdateData(TRUE);

	m_MatLoopDec.dwPoolTime = m_PoolTime;
	int sel = m_ConnectChanCombo.GetCurSel();
	ZeroMemory(&m_MatLoopDec.struchanConInfo[sel], sizeof(m_MatLoopDec.struchanConInfo[sel]));	
	m_MatLoopDec.struchanConInfo[sel].byEnable = m_bCheckConnectChan;
	
	m_MatLoopDec.struchanConInfo[sel].byStreamMode = m_comboStreamMode.GetCurSel();
	m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struUrlInfo.byEnable = TRUE;
	sprintf((char *)m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struUrlInfo.strURL, "%s", m_csUrl);
	
}


void CMatCycLink::OnDomainSavepara() 
{
	UpdateData(TRUE);
	
	m_MatLoopDec.dwPoolTime = m_PoolTime;
	int sel = m_ConnectChanCombo.GetCurSel();
	ZeroMemory(&m_MatLoopDec.struchanConInfo[sel], sizeof(m_MatLoopDec.struchanConInfo[sel]));	
	m_MatLoopDec.struchanConInfo[sel].byEnable = m_bCheckConnectChan;

	m_MatLoopDec.struchanConInfo[sel].byStreamMode = m_comboStreamMode.GetCurSel();
	sprintf((char *)m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byDevAddress, "%s", m_strDomainIp);
	m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byTransProtocol = m_comboDomainTransPro.GetCurSel();
	m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byTransMode = m_comboDomainTransMode.GetCurSel();
	m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byDdnsType = m_comboDomainServerType.GetCurSel();
	sprintf((char *)m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byDdnsAddress, "%s", m_strDomainServerIp);
	m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.wDdnsPort = m_wDomainServerPort;
	m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byChanType = m_comboDomainChanneType.GetCurSel();
	
	char temp[20] = {0};
    m_comboDomainFacType.GetLBText(m_comboDomainFacType.GetCurSel(), temp); 
    for (int i = 0; i < m_struProtoList.dwProtoNum; i++)
    {
        if (strcmp(temp, (const char *)m_struProtoList.struProto[i].byDescribe) == 0)
        {
            m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byFactoryType = m_struProtoList.struProto[i].dwType;
            break;
        }
    }

	m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.dwChannel = m_dwDomainChannelNum;
	sprintf((char *)m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.byStreamId, "%s", m_strDomainStreamId);
	sprintf((char *)m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.sUserName, "%s", m_strDomainRemoteName);
	sprintf((char *)m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.sPassword, "%s", m_strDomainRemotePass);
	m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struDdnsInfo.wDevPort = m_wDomainDevPort;

	if (m_bDomainUseStreamMedia)
	{
		m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struMediaServer.byValid = TRUE;
		sprintf((char *)m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struMediaServer.byAddress, "%s", m_strDomainStreamIdIP);
		m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struMediaServer.byTransmitType = m_comboDomainStreamMediaPro.GetCurSel();
		m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDdnsDecInfo.struMediaServer.wDevPort =m_wDomainStreamMediaPort;
	}
		
	
	
}


void CMatCycLink::OnSingleget() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int sel = m_DecChanCombo.GetCurSel();
	DWORD flg = 0;
	DWORD dwDecChanNum =  sel+m_lStartChan;
	if ( m_BUseWinNo )
	{
		dwDecChanNum = m_dwWinNo + ((m_dwSubWinNo&0xff) << 16) + ((m_dwWallNo&0xff) << 24); 
	}
	if (!NET_DVR_MatrixGetLoopDecChanEnable(m_lServerID, dwDecChanNum, &flg))
	{
		TRACE("\nError: NET_DVR_MatrixGetLoopDecChanEnable[%d] = %d\n", sel+m_lStartChan, NET_DVR_GetLastError());
		return;
	}
	if ( m_BUseWinNo )
	{
		m_comboSwitch.SetCurSel(flg);
	}
	else
	{
		m_CycLink[sel] = flg ? TRUE : FALSE; 
		m_comboSwitch.SetCurSel(m_CycLink[sel]);
	}
	UpdateData(FALSE);
	char szLan[128] = {0};
	g_StringLanType(szLan, "获取成功", "Get successfully");
	AfxMessageBox(szLan);
}

void CMatCycLink::OnWholeget() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD flg = 0;
	if (!NET_DVR_MatrixGetLoopDecEnable(m_lServerID, &flg))
	{
		TRACE("\nError: NET_DVR_MatrixGetLoopDecEnable = %d\n", NET_DVR_GetLastError());
		return;
	}
	TRACE("\n### 0x%x\n", flg);
	for (int i=0; i<m_iChannelnumber; i++)
	{
		if (flg&0x1)
		{
			m_CycLink[i] = TRUE;
		}
		else
		{
			m_CycLink[i] = FALSE;
		}
		flg = flg>>1;
		TRACE("\n### %d\n", m_CycLink[i]);
	}
	int sel = m_DecChanCombo.GetCurSel();
	m_comboSwitch.SetCurSel(m_CycLink[sel]);
	UpdateData(FALSE);
	char szLan[128] = {0};
	g_StringLanType(szLan, "获取成功", "Get successfully");
	AfxMessageBox(szLan);
}

void CMatCycLink::OnSingleset() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int sel = m_DecChanCombo.GetCurSel();
	BOOL flg = FALSE;
	if (m_comboSwitch.GetCurSel())
	{
		flg = TRUE;
	}
	DWORD dwDecChanNum =  sel+m_lStartChan;
	if ( m_BUseWinNo )
	{
		dwDecChanNum = m_dwWinNo + ((m_dwSubWinNo&0xff) << 16) + ((m_dwWallNo&0xff) << 24); 
	}

	if (!NET_DVR_MatrixSetLoopDecChanEnable(m_lServerID, dwDecChanNum, flg))
	{
		TRACE("\nError: NET_DVR_MatrixSetLoopDecChanEnable[%d] = %d\n", sel+m_lStartChan, NET_DVR_GetLastError());
		return;
	}
	MessageBox("Set successfully!");
}


void CMatCycLink::OnUsestreammedia() 
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

void CMatCycLink::OnChkDomainUsestreammedia() 
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

void CMatCycLink::EnableIpOrDomainGroup(BOOL IsEnable)
{
	
	UINT id[]={IDC_EDITDVRIP, IDC_EDITDVRPORT, IDC_EDITDVRUSER, IDC_EDITDVRPASSWD, IDC_COMBOTRANSMODE, IDC_COMBOTRANSTYPE, IDC_EDIT_CHANNEL_NUM,\
				IDC_EDIT_IP_STREAM_ID, IDC_COMBO_FACTYPE, IDC_USESTREAMMEDIA, IDC_STREAMMEDIAIP, IDC_STREAMMEDIAPORT, IDC_COMBOSTREAMMEDIAPRO, IDC_IP_SAVEPARA, IDC_COMBO_IP_CHANNEL_TYPE};
	for (int i = 0; i < sizeof(id)/sizeof(UINT); i++)
	{
		GetDlgItem(id[i])->EnableWindow(IsEnable);
	}
	
	if (IsEnable)
	{
		OnUsestreammedia();
		OnSelchangeComboIpChannelType();
	}
}

void CMatCycLink::EnableURLGroup(BOOL IsEnable)
{
	GetDlgItem(IDC_EDIT_URL)->EnableWindow(IsEnable);
	GetDlgItem(IDC_URL_SAVEPARA)->EnableWindow(IsEnable);
}

void CMatCycLink::EnableDynamicDDNSGroup(BOOL IsEnable)
{
	
	UINT id[]={IDC_EDIT_DOMAIN_NAME, IDC_EDIT_DOMAIN_DEV_PORT, IDC_COMBO_DOMAIN_SERVER_TYPE, IDC_EDIT_DOMAIN_SERVER_IP, IDC_EDIT_DOMAIN_SERVER_PORT, IDC_COMBO_DOMAIN_TRANS_PRO,\
		IDC_EDIT_DOMAIN_STREAMID, IDC_COMBO_DOMAIN_TRANSMODE, IDC_EDIT_DOMAIN_REMOTENAME, IDC_EDIT_DOMAIN_REMOTEPASS, IDC_COMBO_DOMAIN_CHANNEL_TYPE, IDC_COMBO_DOMAIN_FACTYPE,\
		IDC_EDIT_DOMAIN_CHANNEL_NUMBER,  IDC_CHK_DOMAIN_USESTREAMMEDIA, IDC_EDIT_DOMAIN_STREAMMEDIAIP, IDC_EDIT_DOMAIN_STREAMMEDIAPORT, IDC_COMBO_DOMAIN_STREAMMEDIAPRO,\
		IDC_DOMAIN_SAVEPARA};
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

void CMatCycLink::OnSelchangeComboStreamMode() 
{
	switch (m_comboStreamMode.GetCurSel())
	{
	case 0: /*无效*/
		EnableIpOrDomainGroup(FALSE);
		EnableURLGroup(FALSE);
		EnableDynamicDDNSGroup(FALSE);
		break;
	case 1:	/*IP或域名取流*/
		EnableIpOrDomainGroup(TRUE);
		EnableURLGroup(FALSE);
		EnableDynamicDDNSGroup(FALSE);
		break;
	case 2:	/*URL取流*/
		EnableIpOrDomainGroup(FALSE);
		EnableURLGroup(TRUE);
		EnableDynamicDDNSGroup(FALSE);
		break;
	case 3:	/*动态域名解析取流*/
		EnableIpOrDomainGroup(FALSE);
		EnableURLGroup(FALSE);
		EnableDynamicDDNSGroup(TRUE);
		break;
	default:
		break;
	}	
}

void CMatCycLink::OnBtnSetDecCycleParm() 
{
	m_MatLoopDec.dwSize = sizeof(NET_DVR_MATRIX_LOOP_DECINFO_V41);
	m_MatLoopDec.dwPoolTime = m_PoolTime;
	DWORD dwDecChanNum =  m_iChanSel + m_lStartChan;
	if ( m_BUseWinNo )
	{
		dwDecChanNum = m_dwWinNo + ((m_dwSubWinNo&0xff) << 16) + ((m_dwWallNo&0xff) << 24); 
	}
    if (!NET_DVR_MatrixSetLoopDecChanInfo_V41(m_lServerID, dwDecChanNum, &m_MatLoopDec))
    {
        CString stmp;
        stmp.Format("\nError: NET_DVR_MatrixSetLoopDecChanInfo = %d\n", NET_DVR_GetLastError());
        AfxMessageBox(stmp);
    }
    else
    {
		char szLan[128] = {0};
		g_StringLanType(szLan, "保存成功", "save successfully");
		AfxMessageBox(szLan);
	}	
}

void CMatCycLink::OnSelchangeComboIpChannelType() 
{

	UpdateData(TRUE);

	GetDlgItem(IDC_EDIT_CHANNEL_NUM)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_IP_STREAM_ID)->EnableWindow(FALSE);
	switch (m_comboChannelType.GetCurSel())
	{
	case 0:
	case 1:
		break;
	case 2:
		GetDlgItem(IDC_EDIT_IP_STREAM_ID)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_CHANNEL_NUM)->EnableWindow(FALSE);
		break;
	default:
		break;
	}
	UpdateData(FALSE);
	
}

void CMatCycLink::OnSelchangeComboDomainChannelType() 
{
	UpdateData(TRUE);
	
	GetDlgItem(IDC_EDIT_DOMAIN_CHANNEL_NUMBER)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DOMAIN_STREAMID)->EnableWindow(FALSE);
	switch (m_comboDomainChanneType.GetCurSel())
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

int  CMatCycLink::WinInIndex(DWORD dwWinNo)
{
	for (int i=0; i<MAX_CYCLE_CHAN_V30 ; i ++)
	{
		if ( m_iWin[i] == dwWinNo )
		{
			return i; 
		}
	}
	return -1; 
}