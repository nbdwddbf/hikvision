// DlgGB28181ServerCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgGB28181ServerCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGB28181ServerCfg dialog


CDlgGB28181ServerCfg::CDlgGB28181ServerCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGB28181ServerCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGB28181ServerCfg)
	m_csPasswd = _T("");
	m_dwTimes = 0;
	m_wPort = 0;
	m_dwRegisterValid = 0;
	m_csServerID = _T("");
    m_lUserID = -1;
    m_iDevIndex = -1;
    m_bAutoAddIpc = FALSE;

	//}}AFX_DATA_INIT
}


void CDlgGB28181ServerCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGB28181ServerCfg)
	DDX_Text(pDX, IDC_EDIT_AUTHPASSWD, m_csPasswd);
	DDX_Text(pDX, IDC_EDIT_MAX_HEARTBEAT_TIME, m_dwTimes);
	DDX_Text(pDX, IDC_EDIT_PORT, m_wPort);
	DDX_Text(pDX, IDC_EDIT_REGISTER_VALID, m_dwRegisterValid);
	DDX_Text(pDX, IDC_EDIT_SERVER_ID, m_csServerID);
    DDX_Check(pDX, IDC_CHK_AUTOADDIPC, m_bAutoAddIpc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGB28181ServerCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgGB28181ServerCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGB28181ServerCfg message handlers

void CDlgGB28181ServerCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_STD_CONFIG struStdCfg = {0};
    struStdCfg.lpOutBuffer = &m_struServerCfg;
    struStdCfg.dwOutSize = sizeof(m_struServerCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struStdCfg.lpStatusBuffer = m_szStatusBuf;
    struStdCfg.dwStatusSize = ISAPI_STATUS_LEN;
	if (!NET_DVR_GetSTDConfig(m_lUserID,NET_DVR_GET_GBT28181_SERVICE_CFG,&struStdCfg))
	{
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_GET_GBT28181_SERVICE_CFG");
        return;
	}
    else
    {
         g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_GET_GBT28181_SERVICE_CFG");
    }

    m_csServerID = m_struServerCfg.byServerID;
    m_csPasswd = m_struServerCfg.byAuthPasswd;
    m_wPort = m_struServerCfg.wPort;
    m_dwRegisterValid = m_struServerCfg.dwRegisterValid;
    m_dwTimes = m_struServerCfg.byMaxHeartbeatTimeOut;
    m_bAutoAddIpc = m_struServerCfg.byAutoAddIpc;
    UpdateData(FALSE);

}

BOOL CDlgGB28181ServerCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here

    memset(&m_struServerCfg,0,sizeof(m_struServerCfg));
	OnBtnGet();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgGB28181ServerCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    memset(&m_struServerCfg,0,sizeof(m_struServerCfg));
    m_struServerCfg.dwSize = sizeof(m_struServerCfg);
    strncpy((char*)m_struServerCfg.byServerID, m_csServerID.GetBuffer(0),DEV_ID_LEN);
    strncpy((char*)m_struServerCfg.byAuthPasswd, m_csPasswd.GetBuffer(0),PASSWD_LEN);
    m_struServerCfg.wPort = m_wPort;
    m_struServerCfg.dwRegisterValid = m_dwRegisterValid;
    m_struServerCfg.byMaxHeartbeatTimeOut = m_dwTimes;
    m_struServerCfg.byAutoAddIpc = m_bAutoAddIpc;
    NET_DVR_STD_CONFIG struStdCfg = {0};
    struStdCfg.lpInBuffer = &m_struServerCfg;
    struStdCfg.dwInSize = sizeof(m_struServerCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struStdCfg.lpStatusBuffer = m_szStatusBuf;
    struStdCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if (!NET_DVR_SetSTDConfig(m_lUserID,NET_DVR_SET_GBT28181_SERVICE_CFG,&struStdCfg))
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_SET_GBT28181_SERVICE_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_SET_GBT28181_SERVICE_CFG");
    }
    
}
