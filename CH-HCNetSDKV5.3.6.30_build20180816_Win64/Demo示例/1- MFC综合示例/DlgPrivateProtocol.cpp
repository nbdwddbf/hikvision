// DlgPrivateProtocol.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPrivateProtocol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPrivateProtocol dialog


CDlgPrivateProtocol::CDlgPrivateProtocol(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPrivateProtocol::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPrivateProtocol)
	m_bEcryptedSMSEnable = FALSE;
	m_interval = 0;
	m_csIP = _T("");
	m_iPort = 0;
	m_iKeyLen = 0;
	m_csSecretKey = _T("");
	//}}AFX_DATA_INIT
    memset(&m_struPrivateProtocol, 0, sizeof(m_struPrivateProtocol));

    m_lServerID = -1;
    m_iDevIndex = -1;
    m_lChannel = -1;
}


void CDlgPrivateProtocol::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPrivateProtocol)
	DDX_Control(pDX, IDC_COMBO_SERVERTYPE2, m_comboAlgorithm);
	DDX_Control(pDX, IDC_COMBO_SERVERTYPE, m_comboServerType);
	DDX_Check(pDX, IDC_CHECK1, m_bEcryptedSMSEnable);
	DDX_Text(pDX, IDC_EDIT_INTERVAL, m_interval);
	DDX_Text(pDX, IDC_EDIT_IP, m_csIP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_iPort);
	DDX_Text(pDX, IDC_EDIT_SECRETKEY_LEN1, m_iKeyLen);
	DDX_Text(pDX, IDC_EDIT2, m_csSecretKey);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPrivateProtocol, CDialog)
	//{{AFX_MSG_MAP(CDlgPrivateProtocol)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON51, OnButton5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPrivateProtocol message handlers

void CDlgPrivateProtocol::OnButton1() 
{
	// TODO: Add your control notification handler code here
    DWORD dwReturn = 0;
    //memset(&m_NetCfg, 0, sizeof(m_NetCfg));
    m_struPrivateProtocol.dwSize = sizeof(m_struPrivateProtocol);
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_PRIVATE_PROTOCOL_CFG, m_lChannel, &m_struPrivateProtocol, sizeof(m_struPrivateProtocol), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PRIVATE_PROTOCOL_CFG");
        MessageBox(NET_DVR_GetErrorMsg());
        return ;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PRIVATE_PROTOCOL_CFG");
    }
    
    m_csIP.Format("%s", m_struPrivateProtocol.struIP.sIpV4);
    m_iPort = m_struPrivateProtocol.wPort;
    m_interval = m_struPrivateProtocol.dwInterval;
    m_comboServerType.SetCurSel(m_struPrivateProtocol.byServerType);
    m_bEcryptedSMSEnable = m_struPrivateProtocol.byEcryptedSMSEnable;
    m_comboAlgorithm.SetCurSel(m_struPrivateProtocol.byAlgorithm);
    m_iKeyLen = m_struPrivateProtocol.dwSecretKeyLen;
    m_csSecretKey.Format("%s", m_struPrivateProtocol.szSecretKey);

    UpdateData(FALSE);

}

void CDlgPrivateProtocol::OnButton5() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    strncpy(m_struPrivateProtocol.struIP.sIpV4, m_csIP, 16);

    m_struPrivateProtocol.wPort = m_iPort;
    m_struPrivateProtocol.dwInterval =  m_interval;
    m_struPrivateProtocol.byServerType = m_comboServerType.GetCurSel();
    m_struPrivateProtocol.byEcryptedSMSEnable = m_bEcryptedSMSEnable;
    m_struPrivateProtocol.byAlgorithm = m_comboAlgorithm.GetCurSel();
    m_struPrivateProtocol.dwSecretKeyLen = m_iKeyLen;
    strncpy(m_struPrivateProtocol.szSecretKey, m_csSecretKey, 512);

    m_struPrivateProtocol.dwSize = sizeof(m_struPrivateProtocol);
    
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_PRIVATE_PROTOCOL_CFG, 0, &m_struPrivateProtocol, sizeof(m_struPrivateProtocol)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_PRIVATE_PROTOCOL_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_PRIVATE_PROTOCOL_CFG");
    }
}
