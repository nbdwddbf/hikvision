// DlgSlaveCameraInfo.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgSlaveCameraInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSlaveCameraInfo dialog

CDlgSlaveCameraInfo::CDlgSlaveCameraInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSlaveCameraInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSlaveCameraInfo)
	m_csSlaveIP = _T("");
	m_csPassWD = _T("");
	m_iPort = 0;
	m_csSlaveUserName = _T("");
	m_bChkSlaveLoginEnable = FALSE;
	//}}AFX_DATA_INIT
	memset(&m_struSlaveCameraCond, 0, sizeof(m_struSlaveCameraCond));
	memset(&m_struSlaveCameraCfg, 0, sizeof(m_struSlaveCameraCfg));
	memset(&m_struSTDCfg, 0, sizeof(m_struSTDCfg));
	memset(m_szStatusBuf, 0, 1024);
}


void CDlgSlaveCameraInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSlaveCameraInfo)
	DDX_Text(pDX, IDC_EDIT_SLAVE_IP, m_csSlaveIP);
	DDX_Text(pDX, IDC_EDIT_SLAVE_PASSWD, m_csPassWD);
	DDX_Text(pDX, IDC_EDIT_SLAVE_PORT, m_iPort);
	DDX_Text(pDX, IDC_EDIT_SLAVE_USERNAME, m_csSlaveUserName);
	DDX_Check(pDX, IDC_CHK_LOGINSTATUS, m_bChkSlaveLoginEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSlaveCameraInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgSlaveCameraInfo)
	ON_BN_CLICKED(IDC_BTN_LOGIN, OnBtnLogin)
	ON_BN_CLICKED(IDC_BTN_LOGOUT, OnBtnLogout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSlaveCameraInfo message handlers

void CDlgSlaveCameraInfo::OnBtnLogin() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_struSlaveCameraCfg.dwSize = sizeof(m_struSlaveCameraCfg);
	m_struSlaveCameraCfg.byAddressType = 0;
	m_struSlaveCameraCfg.wPort = m_iPort;
	memcpy(m_struSlaveCameraCfg.unionServer.struAddrIP.struIp.sIpV4, m_csSlaveIP, 16);
	memcpy(m_struSlaveCameraCfg.szUserName, m_csSlaveUserName, 32);
	memcpy(m_struSlaveCameraCfg.szPassWord, m_csPassWD, 16);
	m_struSlaveCameraCfg.byLoginStatus = m_bChkSlaveLoginEnable;

	m_struSTDCfg.lpCondBuffer = &m_struSlaveCameraCond;
	m_struSTDCfg.dwCondSize = sizeof(m_struSlaveCameraCond);
	m_struSTDCfg.lpInBuffer = &m_struSlaveCameraCfg;
	m_struSTDCfg.dwInSize = sizeof(NET_DVR_SLAVECAMERA_CFG);

    m_struSTDCfg.lpStatusBuffer = m_szStatusBuf;
    m_struSTDCfg.dwStatusSize = 1024;

	memcpy(&g_struLocalParam.struSlaveCameraCfg[m_struSlaveCameraCond.byID], &m_struSlaveCameraCfg, sizeof(m_struSlaveCameraCfg));

    if(!NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_SLAVECAMERA, &m_struSTDCfg))
    {
       g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SLAVECAMERA ");
    }
    else
    {
       g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_SLAVECAMERA");
    }
}

void CDlgSlaveCameraInfo::OnBtnLogout() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &m_struSlaveCameraCond;
    struCfg.dwCondSize = sizeof(m_struSlaveCameraCond);

    struCfg.lpOutBuffer = &m_struSlaveCameraCfg;
    struCfg.dwOutSize = sizeof(m_struSlaveCameraCfg);

    memset(m_szStatusBuf, 0, 1024);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = 1024;
    
    if(!NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_SLAVECAMERA, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SLAVECAMERA");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SLAVECAMERA");        
    }
	char cTemp[100] = {0};
    memcpy(cTemp, m_struSlaveCameraCfg.unionServer.struAddrIP.struIp.sIpV4, 16);
    m_csSlaveIP.Format("%s",cTemp);
	ZeroMemory(cTemp, 100);
	memcpy(cTemp, m_struSlaveCameraCfg.szUserName, 32);
	m_csSlaveUserName.Format("%s",cTemp);
	ZeroMemory(cTemp, 100);
	memcpy(cTemp, m_struSlaveCameraCfg.szPassWord, 16);
	m_csPassWD.Format("%s",cTemp);

	m_iPort = m_struSlaveCameraCfg.wPort;
	m_bChkSlaveLoginEnable = m_struSlaveCameraCfg.byLoginStatus;
	UpdateData(FALSE);
}
