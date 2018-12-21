// DlgIPAccessCfgDDNS.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgIPAccessCfgDDNS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIPAccessCfgDDNS dialog


CDlgIPAccessCfgDDNS::CDlgIPAccessCfgDDNS(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIPAccessCfgDDNS::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgIPAccessCfgDDNS)
	m_bEnable = FALSE;
	m_dwChannel = 0;
	m_csDVRName = _T("");
	m_dwDVRPort = 0;
	m_csDVRSerial = _T("");
	m_csIPServerIP = _T("");
	m_csDVRPasswd = _T("");
	m_csStreamIP = _T("");
	m_dwStreamPort = 0;
	m_csUserName = _T("");
	m_dwIPServerPort = 0;
	//}}AFX_DATA_INIT
}


void CDlgIPAccessCfgDDNS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIPAccessCfgDDNS)
	DDX_Control(pDX, IDC_COMBO_STREAM_TRANSTYPE, m_comboStreamTransType);
	DDX_Control(pDX, IDC_COMBO_DVR_TRANS_TYPE, m_comboDVRTransType);
	DDX_Control(pDX, IDC_COMBO_DVR_TRANS_PROTOCOL, m_comboDVRTransProtocol);
	DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
	DDX_Text(pDX, IDC_EDIT_DVR_CHANNEL, m_dwChannel);
	DDX_Text(pDX, IDC_EDIT_DVR_NAME, m_csDVRName);
	DDX_Text(pDX, IDC_EDIT_DVR_PORT, m_dwDVRPort);
	DDX_Text(pDX, IDC_EDIT_DVR_SERIAL, m_csDVRSerial);
	DDX_Text(pDX, IDC_EDIT_IPSERVER_IP, m_csIPServerIP);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csDVRPasswd);
	DDX_Text(pDX, IDC_EDIT_STREAM_IP, m_csStreamIP);
	DDX_Text(pDX, IDC_EDIT_STREAM_PORT, m_dwStreamPort);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_csUserName);
	DDX_Text(pDX, IDC_EDIT_IPSERVER_PORT, m_dwIPServerPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIPAccessCfgDDNS, CDialog)
	//{{AFX_MSG_MAP(CDlgIPAccessCfgDDNS)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CDlgIPAccessCfgDDNS::UpdateParams()
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
	
	NET_DVR_DDNS_STREAM_CFG* pStreamCfg = &(pDlgRemoteIPAccess->m_struIPParaCfgV40.struStreamMode[m_iChannelIndex].uGetStream.struDDNSStream);
	
	//stream server
	m_bEnable = pStreamCfg->byEnable;
	m_csStreamIP.Format("%s", pStreamCfg->struStreamServer.sIpV4);
	m_dwStreamPort = pStreamCfg->wStreamServerPort;
	m_comboStreamTransType.SetCurSel(pStreamCfg->byStreamServerTransmitType);
	
	//DVR
    m_csDVRName.Format("%s", pStreamCfg->sDVRName);
	m_dwDVRPort = pStreamCfg->wDVRPort;
	m_csDVRSerial.Format("%s", pStreamCfg->sDVRSerialNumber);
	m_csUserName.Format("%s", pStreamCfg->sUserName);
	m_csDVRPasswd.Format("%s", pStreamCfg->sPassWord);
	m_dwChannel = pStreamCfg->byChannel;
	m_comboDVRTransProtocol.SetCurSel(pStreamCfg->byTransProtocol);
	m_comboDVRTransType.SetCurSel(pStreamCfg->byTransMode);

	//IPserver
	m_csIPServerIP.Format("%s", pStreamCfg->struIPServer.sIpV4);
	m_dwIPServerPort = pStreamCfg->wIPServerPort;
	
	UpdateData(FALSE);
}

void CDlgIPAccessCfgDDNS::SetParams()
{
	UpdateData(TRUE);
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

	//stream type
	pDlgRemoteIPAccess->m_struIPParaCfgV40.struStreamMode[m_iChannelIndex].byGetStreamType = NET_SDK_DDNS_STREAM_CFG;
	NET_DVR_DDNS_STREAM_CFG* pStreamCfg = &(pDlgRemoteIPAccess->m_struIPParaCfgV40.struStreamMode[m_iChannelIndex].uGetStream.struDDNSStream);
	
	pStreamCfg->byEnable = m_bEnable;
	if (m_bEnable)
	{
		//stream server
		strncpy(pStreamCfg->struStreamServer.sIpV4, m_csStreamIP.GetBuffer(0), sizeof(pStreamCfg->struStreamServer.sIpV4));
		pStreamCfg->wStreamServerPort = m_dwStreamPort;
		pStreamCfg->byStreamServerTransmitType = m_comboStreamTransType.GetCurSel();
		
		//DVR
		strncpy((char *)(pStreamCfg->sDVRName), m_csDVRName.GetBuffer(0), sizeof(pStreamCfg->sDVRName));
		pStreamCfg->wDVRPort = m_dwDVRPort;
		strncpy((char *)(pStreamCfg->sDVRSerialNumber), m_csDVRSerial.GetBuffer(0), sizeof(pStreamCfg->sDVRSerialNumber));
		strncpy((char *)(pStreamCfg->sUserName), m_csUserName.GetBuffer(0), sizeof(pStreamCfg->sUserName));
		strncpy((char *)(pStreamCfg->sPassWord), m_csDVRPasswd.GetBuffer(0), sizeof(pStreamCfg->sPassWord));
		pStreamCfg->byChannel = m_dwChannel;
		pStreamCfg->byTransProtocol = m_comboDVRTransProtocol.GetCurSel();
		pStreamCfg->byTransMode = m_comboDVRTransType.GetCurSel();

		strncpy((char *)(pStreamCfg->struIPServer.sIpV4), m_csIPServerIP.GetBuffer(0), sizeof(pStreamCfg->struIPServer.sIpV4));
	    pStreamCfg->wIPServerPort = m_dwIPServerPort;
		
		pDlgRemoteIPAccess->SetChannelEnable(TRUE);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDlgIPAccessCfgDDNS message handlers

void CDlgIPAccessCfgDDNS::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	SetParams();
}
