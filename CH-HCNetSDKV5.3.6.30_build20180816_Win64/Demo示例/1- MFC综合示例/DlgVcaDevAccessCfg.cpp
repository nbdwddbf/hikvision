// DlgVcaDevAccessCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaDevAccessCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaDevAccessCfg dialog


CDlgVcaDevAccessCfg::CDlgVcaDevAccessCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaDevAccessCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaDevAccessCfg)
	m_bChkAccessEn = FALSE;
	m_csIP = _T("");
	m_dwPort = 0;
	m_csPassword = _T("");
	m_csUserName = _T("");
	//}}AFX_DATA_INIT
	m_lServerID = -1;
    m_lChannel = -1;
    m_iDevIndex = -1;
	memset(&m_struDevAccessCfg, 0, sizeof(m_struDevAccessCfg));
}


void CDlgVcaDevAccessCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaDevAccessCfg)
	DDX_Check(pDX, IDC_CHK_ACCESS_ENABLE, m_bChkAccessEn);
	DDX_Text(pDX, IDC_EDIT_IP, m_csIP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_dwPort);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csPassword);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_csUserName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaDevAccessCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaDevAccessCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaDevAccessCfg message handlers
BOOL CDlgVcaDevAccessCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
	OnBtnGet();
	return TRUE;
}

void CDlgVcaDevAccessCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
	char szLan[33] = {0};
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_DEVACCESS_CFG, m_lChannel, &m_struDevAccessCfg, sizeof(m_struDevAccessCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_DEVACCESS_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_DEVACCESS_CFG");
    }

	m_bChkAccessEn = m_struDevAccessCfg.byEnable;
	m_dwPort = m_struDevAccessCfg.wDevicePort;
	memcpy(szLan,m_struDevAccessCfg.struIP.sIpV4, 16);
	m_csIP.Format(szLan);
	memset(szLan,0,33);
	memcpy(szLan,m_struDevAccessCfg.sUserName,32);
	m_csUserName.Format(szLan);
	memset(szLan,0,33);
	memcpy(szLan,m_struDevAccessCfg.sPassword,16);
	m_csPassword.Format(szLan);
	UpdateData(FALSE);
}

void CDlgVcaDevAccessCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struDevAccessCfg.dwSize = sizeof(m_struDevAccessCfg);
	m_struDevAccessCfg.byEnable = m_bChkAccessEn;
	m_struDevAccessCfg.wDevicePort = m_dwPort;
	memcpy(m_struDevAccessCfg.struIP.sIpV4,m_csIP,16);
	memcpy(m_struDevAccessCfg.sUserName,m_csUserName,32);
	memcpy(m_struDevAccessCfg.sPassword,m_csPassword,16);
	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_DEVACCESS_CFG, m_lChannel, &m_struDevAccessCfg, sizeof(m_struDevAccessCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_DEVACCESS_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_DEVACCESS_CFG");
    }
}
