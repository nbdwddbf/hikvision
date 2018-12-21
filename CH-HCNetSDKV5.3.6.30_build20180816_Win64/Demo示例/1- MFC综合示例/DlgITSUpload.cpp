// DlgITSUpload.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgITSUpload.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgITSUpload dialog


CDlgITSUpload::CDlgITSUpload(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgITSUpload::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgITSUpload)
	m_iHostIndex = -1;
	m_strHostIP = _T("");
	m_iHostPort = 0;
	m_bStopUpload = FALSE;
	m_iUploadStrategy = -1;
	m_dwUploadInterval = 0;
	m_dwUploadTimeout = 0;
	m_bPostData = FALSE;
	//}}AFX_DATA_INIT
	m_lServerID = -1;
    m_iDevIndex = -1;
	m_lChannel = -1;
}


void CDlgITSUpload::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgITSUpload)
	DDX_CBIndex(pDX, IDC_CMB_HOST_INDEX, m_iHostIndex);
	DDX_Text(pDX, IDC_EDT_HOST_IP, m_strHostIP);
	DDX_Text(pDX, IDC_EDT_HOST_PORT, m_iHostPort);
	DDX_Check(pDX, IDC_CK_STOP_UPLOAD, m_bStopUpload);
	DDX_CBIndex(pDX, IDC_CMB_UPLOAD_STRATEGY, m_iUploadStrategy);
	DDX_Text(pDX, IDC_EDT_UPLOAD_INTERVAL, m_dwUploadInterval);
	DDX_Text(pDX, IDC_EDT_UPLOAD_TIMEOUT, m_dwUploadTimeout);
	DDX_Check(pDX, IDC_CK_POST, m_bPostData);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgITSUpload, CDialog)
	//{{AFX_MSG_MAP(CDlgITSUpload)
	ON_BN_CLICKED(IDC_ENSURE, OnEnsure)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_CBN_SELCHANGE(IDC_CMB_HOST_INDEX, OnSelchangeCmbHostIndex)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgITSUpload message handlers

void CDlgITSUpload::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

BOOL CDlgITSUpload::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	OnBtnGet();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgITSUpload::OnEnsure() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_iHostIndex == 0)
	{
		memcpy(m_struUploadCfg.struRemoteDataHost1.struHostAddr.sIpV4, m_strHostIP.GetBuffer(0), 16);
		m_struUploadCfg.struRemoteDataHost1.wHostPort = m_iHostPort;
		m_struUploadCfg.struRemoteDataHost1.bySuspendUpload = m_bStopUpload;
		m_struUploadCfg.struRemoteDataHost1.byUploadStrategy = m_iUploadStrategy;
		m_struUploadCfg.struRemoteDataHost1.wUploadInterval = m_dwUploadInterval;
		m_struUploadCfg.struRemoteDataHost1.dwUploadTimeOut = m_dwUploadTimeout;
		m_struUploadCfg.struRemoteDataHost1.dwDataType |= m_bPostData;
	}
	else if (m_iHostIndex == 1)
	{
		memcpy(m_struUploadCfg.struRemoteDataHost2.struHostAddr.sIpV4, m_strHostIP.GetBuffer(0), 16);
		m_struUploadCfg.struRemoteDataHost2.wHostPort = m_iHostPort;
		m_struUploadCfg.struRemoteDataHost2.bySuspendUpload = m_bStopUpload;
		m_struUploadCfg.struRemoteDataHost2.byUploadStrategy = m_iUploadStrategy;
		m_struUploadCfg.struRemoteDataHost2.wUploadInterval = m_dwUploadInterval;
		m_struUploadCfg.struRemoteDataHost2.dwUploadTimeOut = m_dwUploadTimeout;
		m_struUploadCfg.struRemoteDataHost2.dwDataType |= m_bPostData;
	}
}

void CDlgITSUpload::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	memset(&m_struUploadCfg, 0, sizeof(m_struUploadCfg));
	DWORD dwReturn = 0;
	if (NET_DVR_GetDVRConfig(m_lServerID, NET_ITS_GET_UPLOAD_CFG, m_lChannel, &m_struUploadCfg,
		sizeof(m_struUploadCfg), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_ITS_GET_UPLOAD_CFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_ITS_GET_UPLOAD_CFG");
	}
	m_iHostIndex = 0;
	m_strHostIP = m_struUploadCfg.struRemoteDataHost1.struHostAddr.sIpV4;
	m_iHostPort = m_struUploadCfg.struRemoteDataHost1.wHostPort;
	m_bStopUpload = m_struUploadCfg.struRemoteDataHost1.bySuspendUpload;
	m_iUploadStrategy = m_struUploadCfg.struRemoteDataHost1.byUploadStrategy;
	m_dwUploadInterval = m_struUploadCfg.struRemoteDataHost1.wUploadInterval;
	m_dwUploadTimeout = m_struUploadCfg.struRemoteDataHost1.dwUploadTimeOut;
	m_bPostData = m_struUploadCfg.struRemoteDataHost1.dwDataType & 0x01;
	UpdateData(FALSE);
}

void CDlgITSUpload::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	if (NET_DVR_SetDVRConfig(m_lServerID, NET_ITS_SET_UPLOAD_CFG, m_lChannel, &m_struUploadCfg, sizeof(m_struUploadCfg)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_ITS_SET_UPLOAD_CFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_ITS_SET_UPLOAD_CFG");
	}
}

void CDlgITSUpload::OnSelchangeCmbHostIndex() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_iHostIndex == 0)
	{
		//m_iHostIndex = 0;
		m_strHostIP = m_struUploadCfg.struRemoteDataHost1.struHostAddr.sIpV4;
		m_iHostPort = m_struUploadCfg.struRemoteDataHost1.wHostPort;
		m_bStopUpload = m_struUploadCfg.struRemoteDataHost1.bySuspendUpload;
		m_iUploadStrategy = m_struUploadCfg.struRemoteDataHost1.byUploadStrategy;
		m_dwUploadInterval = m_struUploadCfg.struRemoteDataHost1.wUploadInterval;
		m_dwUploadTimeout = m_struUploadCfg.struRemoteDataHost1.dwUploadTimeOut;
		m_bPostData = m_struUploadCfg.struRemoteDataHost1.dwDataType & 0x01;
	}
	else if (m_iHostIndex == 1)
	{
		//m_iHostIndex = 0;
		m_strHostIP = m_struUploadCfg.struRemoteDataHost2.struHostAddr.sIpV4;
		m_iHostPort = m_struUploadCfg.struRemoteDataHost2.wHostPort;
		m_bStopUpload = m_struUploadCfg.struRemoteDataHost2.bySuspendUpload;
		m_iUploadStrategy = m_struUploadCfg.struRemoteDataHost2.byUploadStrategy;
		m_dwUploadInterval = m_struUploadCfg.struRemoteDataHost2.wUploadInterval;
		m_dwUploadTimeout = m_struUploadCfg.struRemoteDataHost2.dwUploadTimeOut;
		m_bPostData = m_struUploadCfg.struRemoteDataHost2.dwDataType & 0x01;
	}
	UpdateData(FALSE);
}
