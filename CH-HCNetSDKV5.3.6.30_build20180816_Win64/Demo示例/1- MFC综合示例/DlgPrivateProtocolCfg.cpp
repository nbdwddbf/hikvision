// DlgPrivateProtocolCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPrivateProtocolCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPrivateProtocolCfg dialog


CDlgPrivateProtocolCfg::CDlgPrivateProtocolCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPrivateProtocolCfg::IDD, pParent)
    , m_dwDistanceLimit(0)
{
	//{{AFX_DATA_INIT(CDlgPrivateProtocolCfg)
	m_bEcryptedSMSEnable = FALSE;
	m_csIndexCode = _T("");
	m_csIP = _T("");
	m_iPort = 0;
	m_csSecretKey = _T("");
	m_dwKeyLen = 0;
	m_dwInterVal = 0;
	//}}AFX_DATA_INIT

    memset(&m_struPrivateProtocol, 0, sizeof(m_struPrivateProtocol));
    
    m_lServerID = -1;
    m_iDevIndex = -1;
    m_lChannel = -1;
}


void CDlgPrivateProtocolCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgPrivateProtocolCfg)
    DDX_Control(pDX, IDC_COMBO_SERVERTYPE, m_comboServerType);
    DDX_Control(pDX, IDC_COMBO_ENABLE, m_comboEnable);
    DDX_Control(pDX, IDC_COMBO_ALGORITHM, m_comboAlgorithm);
    DDX_Check(pDX, IDC_CHK_ECRYTED_SMS_ENABLE, m_bEcryptedSMSEnable);
    DDX_Text(pDX, IDC_EDIT_INDEXCODE, m_csIndexCode);
    DDX_Text(pDX, IDC_EDIT_IP, m_csIP);
    DDX_Text(pDX, IDC_EDIT_PORT, m_iPort);
    DDX_Text(pDX, IDC_EDIT_SECRETKEY, m_csSecretKey);
    DDX_Text(pDX, IDC_EDIT_SECRETKEYLEN, m_dwKeyLen);
    DDX_Text(pDX, IDC_EDIT_INTERVAL, m_dwInterVal);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMBO_ACAUISITION_MODE, m_comboAcauisitionMode);
    DDX_Text(pDX, IDC_EDIT_DISTANCE_LIMIT, m_dwDistanceLimit);
    DDX_Control(pDX, IDC_COMBO_PK_MODE, m_combPKmode);
    DDX_Control(pDX, IDC_COMBO_MAC_ADDR_REDUCTION, m_combMACAddrReduction);
}


BEGIN_MESSAGE_MAP(CDlgPrivateProtocolCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgPrivateProtocolCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPrivateProtocolCfg message handlers

BOOL CDlgPrivateProtocolCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
    OnBtnGet();
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPrivateProtocolCfg::OnBtnGet() 
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
    m_dwInterVal = m_struPrivateProtocol.dwInterval;
    m_comboEnable.SetCurSel(m_struPrivateProtocol.byEnable);
    m_comboServerType.SetCurSel(m_struPrivateProtocol.byServerType);
    m_bEcryptedSMSEnable = m_struPrivateProtocol.byEcryptedSMSEnable;
    m_comboAlgorithm.SetCurSel(m_struPrivateProtocol.byAlgorithm);
    m_dwKeyLen = m_struPrivateProtocol.dwSecretKeyLen;
    m_comboAcauisitionMode.SetCurSel(m_struPrivateProtocol.byAcauisitionMode);
    m_dwDistanceLimit = m_struPrivateProtocol.dwDistanceLimit;
    m_combPKmode.SetCurSel(m_struPrivateProtocol.byPKModeEnable);
    m_combMACAddrReduction.SetCurSel(m_struPrivateProtocol.byMACAddrReductionEnable);
    m_csSecretKey.Format("%s", m_struPrivateProtocol.szSecretKey);
    m_csIndexCode.Format("%s", m_struPrivateProtocol.szIndexCode);
    UpdateData(FALSE);
}

void CDlgPrivateProtocolCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    strncpy(m_struPrivateProtocol.struIP.sIpV4, m_csIP, 16);
    
    m_struPrivateProtocol.wPort = m_iPort;
    m_struPrivateProtocol.dwInterval =  m_dwInterVal;
    m_struPrivateProtocol.byEnable = m_comboEnable.GetCurSel();
    m_struPrivateProtocol.byServerType = m_comboServerType.GetCurSel();
    m_struPrivateProtocol.byEcryptedSMSEnable = m_bEcryptedSMSEnable;
    m_struPrivateProtocol.byAlgorithm = m_comboAlgorithm.GetCurSel();
    m_struPrivateProtocol.dwSecretKeyLen = m_dwKeyLen;
    m_struPrivateProtocol.byAcauisitionMode = m_comboAcauisitionMode.GetCurSel();
    m_struPrivateProtocol.dwDistanceLimit = m_dwDistanceLimit;
    m_struPrivateProtocol.byPKModeEnable = m_combPKmode.GetCurSel();
    m_struPrivateProtocol.byMACAddrReductionEnable = m_combMACAddrReduction.GetCurSel();
    strncpy(m_struPrivateProtocol.szSecretKey, m_csSecretKey, 512);

	m_csIndexCode.Replace(_T('\n'), _T('\0'));
	strncpy(m_struPrivateProtocol.szIndexCode, m_csIndexCode, 64);
    m_struPrivateProtocol.dwSize = sizeof(m_struPrivateProtocol);
    
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_PRIVATE_PROTOCOL_CFG, m_lChannel, &m_struPrivateProtocol, sizeof(m_struPrivateProtocol)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_PRIVATE_PROTOCOL_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_PRIVATE_PROTOCOL_CFG");
    }
}
