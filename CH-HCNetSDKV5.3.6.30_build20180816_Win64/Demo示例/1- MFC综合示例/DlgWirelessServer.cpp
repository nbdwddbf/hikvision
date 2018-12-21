// DlgWirelessServer.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgWirelessServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgWirelessServer dialog


DlgWirelessServer::DlgWirelessServer(CWnd* pParent /*=NULL*/)
	: CDialog(DlgWirelessServer::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgWirelessServer)
	m_byDefaultPassword = FALSE;
    m_szSsidInformation = _T("");
	m_szPassWd = _T("");
	//}}AFX_DATA_INIT
}


void DlgWirelessServer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgWirelessServer)
    DDX_Check(pDX, IDC_CHECK_DEFAULT_PWD, m_byDefaultPassword);
	DDX_Control(pDX, IDC_CTRL_BROADCAST_ENABLE, m_comBroadcastEnable);
	DDX_Control(pDX, IDC_CTRL_HOT_SPOT_ENABLE, m_comHotSpotEnable);
	DDX_Control(pDX, IDC_CTRL_ENCRYPTION_MODE, m_comEncryptionMode);
	DDX_Control(pDX, IDC_CTRL_SAFE_MODE, m_comSafeMode);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_comChannel);
    DDX_Text(pDX, IDC_SSID_INFORMATION, m_szSsidInformation);
	DDX_Text(pDX, IDC_PASSWORD, m_szPassWd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgWirelessServer, CDialog)
	//{{AFX_MSG_MAP(DlgWirelessServer)
	ON_BN_CLICKED(IDC_SET, OnSet)
	ON_BN_CLICKED(IDC_GET, OnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgWirelessServer message handlers

BOOL DlgWirelessServer::OnInitDialog() 
{
    CDialog::OnInitDialog();

    m_comChannel.ResetContent();
    m_comChannel.InsertString(0,"ÎÞÐ§");
    m_comChannel.InsertString(1,"Íø¿¨1");
    m_comChannel.InsertString(2,"Íø¿¨2");
    m_comChannel.SetCurSel(1);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgWirelessServer::OnSet()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char szLan[512] = {0};
    NET_DVR_WIRELESSSERVER struWirelessServer = {0};
    
    struWirelessServer.byWLanShare = m_comHotSpotEnable.GetCurSel();
    struWirelessServer.byBroadcastSSID = m_comBroadcastEnable.GetCurSel();;
    struWirelessServer.bySecurityMode = m_comSafeMode.GetCurSel();
    struWirelessServer.byAlgorithmType = m_comEncryptionMode.GetCurSel();
    sprintf(struWirelessServer.szSSID,"%s",m_szSsidInformation.GetBuffer(m_szSsidInformation.GetLength()));
    sprintf(struWirelessServer.szPassWord,"%s",m_szPassWd.GetBuffer(m_szPassWd.GetLength()));
    struWirelessServer.byDefaultPassword = m_byDefaultPassword;

    struWirelessServer.dwSize = sizeof(struWirelessServer);
    
    DWORD dwChannel = 0;
    dwChannel = m_comChannel.GetCurSel();
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &dwChannel;
    struCfg.dwCondSize = sizeof(dwChannel);
    struCfg.lpInBuffer = &struWirelessServer;
    struCfg.dwInSize = sizeof(struWirelessServer);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    
    if(!NET_DVR_SetSTDConfig(m_lUserID, NET_DVR_SET_WIRELESSSERVER, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_WIRELESSSERVER");
        sprintf(szLan, "Error Code:%d, Error Info:%s", NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_WIRELESSSERVER");
    }
}

void DlgWirelessServer::OnGet() 
{
    // TODO: Add your control notification handler code here
    NET_DVR_WIRELESSSERVER struWirelessServer = {0};

    DWORD dwChannel = 0;
    dwChannel = m_comChannel.GetCurSel();
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = &dwChannel;
    struCfg.dwCondSize = sizeof(dwChannel);
    struCfg.lpOutBuffer = &struWirelessServer;
    struCfg.dwOutSize = sizeof(struWirelessServer);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_WIRELESSSERVER, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_WIRELESSSERVER");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_WIRELESSSERVER");
    }

    m_comHotSpotEnable.SetCurSel(struWirelessServer.byWLanShare);
    m_comBroadcastEnable.SetCurSel(struWirelessServer.byBroadcastSSID);
    m_comSafeMode.SetCurSel(struWirelessServer.bySecurityMode);
    m_comEncryptionMode.SetCurSel(struWirelessServer.byAlgorithmType);
    m_szSsidInformation.Format("%s",struWirelessServer.szSSID);
    m_szPassWd.Format("%s",struWirelessServer.szPassWord);
    m_byDefaultPassword = struWirelessServer.byDefaultPassword;
    
    UpdateData(FALSE);
}
