// DlgIPAccessCfgIPServer.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgIPAccessCfgIPServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIPAccessCfgIPServer dialog


CDlgIPAccessCfgIPServer::CDlgIPAccessCfgIPServer(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIPAccessCfgIPServer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgIPAccessCfgIPServer)
	m_bEnable = FALSE;
	m_dwDVRChannelNO = 0;
	m_dwDVRPort = 0;
	m_csDVRSerial = _T("");
	m_csIPServerIP = _T("");
	m_dwIPServerPort = 0;
	m_csPasswd = _T("");
	m_csUsername = _T("");
	m_csDVRName = _T("");
	//}}AFX_DATA_INIT

	m_iChannelIndex = -1;
}


void CDlgIPAccessCfgIPServer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIPAccessCfgIPServer)
	DDX_Check(pDX, IDC_CHECK_STREAM_VALID, m_bEnable);
	DDX_Text(pDX, IDC_EDIT_DVR_CHANNEL, m_dwDVRChannelNO);
	DDX_Text(pDX, IDC_EDIT_DVR_PORT, m_dwDVRPort);
	DDX_Text(pDX, IDC_EDIT_DVR_SERIAL, m_csDVRSerial);
	DDX_Text(pDX, IDC_EDIT_IPSERVER_IP, m_csIPServerIP);
	DDX_Text(pDX, IDC_EDIT_IPSERVER_PORT, m_dwIPServerPort);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csPasswd);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_csUsername);
	DDX_Text(pDX, IDC_EDIT_DVR_NAME, m_csDVRName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIPAccessCfgIPServer, CDialog)
	//{{AFX_MSG_MAP(CDlgIPAccessCfgIPServer)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CDlgIPAccessCfgIPServer::UpdateParams()
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
	
	NET_DVR_IPSERVER_STREAM* pStreamCfg = &(pDlgRemoteIPAccess->m_struIPParaCfgV40.struStreamMode[m_iChannelIndex].uGetStream.struIPServerStream);
	
	//IP Server
	m_bEnable = pStreamCfg->byEnable;
	m_csIPServerIP.Format("%s", pStreamCfg->struIPServer.sIpV4);
	m_dwIPServerPort = pStreamCfg->wPort;
	
	//DVR
	m_csDVRName.Format("%s", (char *)pStreamCfg->byDVRName);
    m_csDVRSerial.Format("%s", (char *)pStreamCfg->byDVRSerialNumber);
	m_csUsername.Format("%s", (char *)pStreamCfg->byUserName);
	m_csPasswd.Format("%s", pStreamCfg->byPassWord);
	m_dwDVRChannelNO = pStreamCfg->byChannel;
	
	UpdateData(FALSE);
}

void CDlgIPAccessCfgIPServer::SetParams()
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
	pDlgRemoteIPAccess->m_struIPParaCfgV40.struStreamMode[m_iChannelIndex].byGetStreamType = NET_SDK_IPSERVER;
	NET_DVR_IPSERVER_STREAM* pStreamCfg = &(pDlgRemoteIPAccess->m_struIPParaCfgV40.struStreamMode[m_iChannelIndex].uGetStream.struIPServerStream);
	
	pStreamCfg->byEnable = m_bEnable;
	if (m_bEnable)
	{
		//stream server
		strncpy(pStreamCfg->struIPServer.sIpV4, m_csIPServerIP.GetBuffer(0), sizeof(pStreamCfg->struIPServer.sIpV4));
		pStreamCfg->wPort = m_dwIPServerPort;
		
		//DVR
		strncpy((char *)pStreamCfg->byDVRName, m_csDVRName.GetBuffer(0), sizeof(pStreamCfg->byDVRName));
		strncpy((char *)(pStreamCfg->byDVRSerialNumber), m_csDVRSerial.GetBuffer(0), sizeof(pStreamCfg->byDVRSerialNumber));
		strncpy((char *)(pStreamCfg->byUserName), m_csUsername.GetBuffer(0), sizeof(pStreamCfg->byUserName));
		strncpy((char *)(pStreamCfg->byPassWord), m_csPasswd.GetBuffer(0), sizeof(pStreamCfg->byPassWord));
	    pStreamCfg->byChannel = m_dwDVRChannelNO;
		
		pDlgRemoteIPAccess->SetChannelEnable(TRUE);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDlgIPAccessCfgIPServer message handlers

void CDlgIPAccessCfgIPServer::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	SetParams();
}
