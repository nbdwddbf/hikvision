// DlgIPAccessCfgStreamServer.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgIPAccessCfgStreamServer.h"
#include "DlgRemoteIPAccess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIPAccessCfgStreamServer dialog


CDlgIPAccessCfgStreamServer::CDlgIPAccessCfgStreamServer(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIPAccessCfgStreamServer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgIPAccessCfgStreamServer)
	m_bEnable = FALSE;
	m_dwChannelNO = 0;
	m_csDVRIP = _T("");
	m_dwDVRPort = 0;
	m_csPasswd = _T("");
	m_csStreamServerIP = _T("");
	m_csUserName = _T("");
	m_dwStreamPort = 0;
	//}}AFX_DATA_INIT

	m_iChannelIndex = 0;
}


void CDlgIPAccessCfgStreamServer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIPAccessCfgStreamServer)
	DDX_Control(pDX, IDC_COMBO_STREAM_TRANSTYPE, m_comboStreamTransType);
	DDX_Control(pDX, IDC_COMBO_DVR_TRANS_TYPE, m_comboDVRTransType);
	DDX_Control(pDX, IDC_COMBO_DVR_TRANS_PROTOCOL, m_comboDVRTransProtocol);
	DDX_Check(pDX, IDC_CHECK_STREAM_VALID, m_bEnable);
	DDX_Text(pDX, IDC_EDIT_DVR_CHANNEL, m_dwChannelNO);
	DDV_MinMaxDWord(pDX, m_dwChannelNO, 0, 256);
	DDX_Text(pDX, IDC_EDIT_DVR_IP, m_csDVRIP);
	DDV_MaxChars(pDX, m_csDVRIP, 16);
	DDX_Text(pDX, IDC_EDIT_DVR_PORT, m_dwDVRPort);
	DDV_MinMaxDWord(pDX, m_dwDVRPort, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csPasswd);
	DDV_MaxChars(pDX, m_csPasswd, 32);
	DDX_Text(pDX, IDC_EDIT_STREAM_SERVER_IP, m_csStreamServerIP);
	DDV_MaxChars(pDX, m_csStreamServerIP, 16);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_csUserName);
	DDV_MaxChars(pDX, m_csUserName, 32);
	DDX_Text(pDX, IDC_EDIT_STREAM_SERVER_PORT, m_dwStreamPort);
	DDV_MinMaxDWord(pDX, m_dwStreamPort, 0, 65535);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIPAccessCfgStreamServer, CDialog)
	//{{AFX_MSG_MAP(CDlgIPAccessCfgStreamServer)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CDlgIPAccessCfgStreamServer::UpdateParams(int iMode)
{
    CDlgRemoteIPAccess *pDlgRemoteIPAccess = (CDlgRemoteIPAccess *)GetParent();
	if (NULL == pDlgRemoteIPAccess)
	{
		return;
	}
	m_iChannelIndex = pDlgRemoteIPAccess->m_iCurChanIndex;
	if (m_iChannelIndex < 0 || m_iChannelIndex >= MAX_CHANNUM_V30)
	{
		return;
	}

	NET_DVR_PU_STREAM_CFG* pStreamCfg = &(pDlgRemoteIPAccess->m_struIPParaCfgV40.struStreamMode[m_iChannelIndex].uGetStream.struPUStream);
	
	//stream server
	m_iMode = iMode;
	m_bEnable = pStreamCfg->struStreamMediaSvrCfg.byValid;
	m_csStreamServerIP.Format("%s", pStreamCfg->struStreamMediaSvrCfg.struDevIP.sIpV4);
	m_dwStreamPort = pStreamCfg->struStreamMediaSvrCfg.wDevPort;
	m_comboStreamTransType.SetCurSel(pStreamCfg->struStreamMediaSvrCfg.byTransmitType);

	//DVR
    m_csDVRIP.Format("%s", pStreamCfg->struDevChanInfo.struIP.sIpV4);
	m_dwDVRPort = pStreamCfg->struDevChanInfo.wDVRPort;
	m_csUserName.Format("%s", pStreamCfg->struDevChanInfo.sUserName);
	m_csPasswd.Format("%s", pStreamCfg->struDevChanInfo.sPassword);
	m_dwChannelNO = pStreamCfg->struDevChanInfo.byChannel;
	m_comboDVRTransProtocol.SetCurSel(pStreamCfg->struDevChanInfo.byTransProtocol);
	m_comboDVRTransType.SetCurSel(pStreamCfg->struDevChanInfo.byTransMode);

	UpdateData(FALSE);
}

void CDlgIPAccessCfgStreamServer::SetParams()
{
	UpdateData(TRUE);
	CDlgRemoteIPAccess *pDlgRemoteIPAccess = (CDlgRemoteIPAccess *)GetParent();
	if (NULL == pDlgRemoteIPAccess)
	{
		return;
	}
	m_iChannelIndex = pDlgRemoteIPAccess->m_iCurChanIndex;
	if ( m_iChannelIndex < 0 || m_iChannelIndex >= MAX_CHANNUM_V30)
	{
		return;
	}


	//stream type
	pDlgRemoteIPAccess->m_struIPParaCfgV40.struStreamMode[m_iChannelIndex].byGetStreamType = pDlgRemoteIPAccess->m_dwMode/*NET_SDK_STREAM_MEDIA*/;
	NET_DVR_PU_STREAM_CFG* pStreamCfg = &(pDlgRemoteIPAccess->m_struIPParaCfgV40.struStreamMode[m_iChannelIndex].uGetStream.struPUStream);
	
	pStreamCfg->struStreamMediaSvrCfg.byValid = m_bEnable;
//	if (m_bEnable)
	{
		//stream server
		strncpy(pStreamCfg->struStreamMediaSvrCfg.struDevIP.sIpV4, m_csStreamServerIP.GetBuffer(0), sizeof(pStreamCfg->struStreamMediaSvrCfg.struDevIP.sIpV4));
		pStreamCfg->struStreamMediaSvrCfg.wDevPort = m_dwStreamPort;
		pStreamCfg->struStreamMediaSvrCfg.byTransmitType = m_comboStreamTransType.GetCurSel();

		//DVR
		strncpy(pStreamCfg->struDevChanInfo.struIP.sIpV4, m_csDVRIP.GetBuffer(0), sizeof(pStreamCfg->struDevChanInfo.struIP.sIpV4));
		pStreamCfg->struDevChanInfo.wDVRPort = m_dwDVRPort;
		strncpy((char *)(pStreamCfg->struDevChanInfo.sUserName), m_csUserName.GetBuffer(0), sizeof(pStreamCfg->struDevChanInfo.sUserName));
		strncpy((char *)(pStreamCfg->struDevChanInfo.sPassword), m_csPasswd.GetBuffer(0), sizeof(pStreamCfg->struDevChanInfo.sPassword));
		pStreamCfg->struDevChanInfo.byChannel = m_dwChannelNO;
		pStreamCfg->struDevChanInfo.byTransProtocol = m_comboDVRTransProtocol.GetCurSel();
		pStreamCfg->struDevChanInfo.byTransMode = m_comboDVRTransType.GetCurSel();

		pDlgRemoteIPAccess->SetChannelEnable(TRUE);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDlgIPAccessCfgStreamServer message handlers

void CDlgIPAccessCfgStreamServer::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	SetParams();
}

BOOL CDlgIPAccessCfgStreamServer::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_comboDVRTransProtocol.SetCurSel(0);
	m_comboDVRTransType.SetCurSel(0);
	m_comboStreamTransType.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
