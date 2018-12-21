// DlgVcaRemoteChannel.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaRemoteChannel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaRemoteChannel dialog


CDlgVcaRemoteChannel::CDlgVcaRemoteChannel(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaRemoteChannel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaRemoteChannel)
	m_strAddress = _T("");
	m_nChannelNo = 0;
	m_strPassword = _T("12345");
	m_nPort = 8000;
	m_strUserName = _T("admin");
	//}}AFX_DATA_INIT
}


void CDlgVcaRemoteChannel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaRemoteChannel)
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_strAddress);
	DDX_Text(pDX, IDC_EDIT_CHANNEL, m_nChannelNo);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUserName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaRemoteChannel, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaRemoteChannel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaRemoteChannel message handlers

void CDlgVcaRemoteChannel::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	CDialog::OnOK();
}

void CDlgVcaRemoteChannel::SetRemoteChannelParam(CString strAddress,DWORD dwPort,CString strUserName,CString strPwd,DWORD dwChannel)
{
	m_strAddress  = strAddress;
	m_nPort       = dwPort;
	m_strUserName = strUserName;
	m_strPassword = strPwd;
	m_nChannelNo  = dwChannel;
}

void CDlgVcaRemoteChannel::GetRemoteChannelParam(CString& strAddress,DWORD& dwPort,CString& strUserName,CString& strPwd,DWORD& dwChannel)
{
	strAddress  = m_strAddress;
	dwPort      = m_nPort;
	strUserName = m_strUserName;
	strPwd      = m_strPassword;
	dwChannel   = m_nChannelNo;
}