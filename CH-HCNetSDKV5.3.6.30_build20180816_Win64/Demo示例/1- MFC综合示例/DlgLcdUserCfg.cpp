// DlgLcdUserCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgLcdUserCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLcdUserCfg dialog


CDlgLcdUserCfg::CDlgLcdUserCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLcdUserCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLcdUserCfg)
	m_csMacAddr = _T("");
	m_csPassword = _T("");
	m_csPasswordSure = _T("");
	m_csUserName = _T("");
	//}}AFX_DATA_INIT
}


void CDlgLcdUserCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLcdUserCfg)
	DDX_Control(pDX, IDC_IPADDRESS, m_cIp);
	DDX_Control(pDX, IDC_COMBO_USER_INDEX, m_comboUserIndex);
	DDX_Control(pDX, IDC_COMBO_PRIORITY, m_comboPriority);
	DDX_Text(pDX, IDC_EDIT_MAC_ADDR, m_csMacAddr);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csPassword);
	DDX_Text(pDX, IDC_EDIT_PASSWORD_SURE, m_csPasswordSure);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_csUserName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLcdUserCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgLcdUserCfg)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLcdUserCfg message handlers

BOOL CDlgLcdUserCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    memset(&m_struUserCfg, 0, sizeof(m_struUserCfg));
    memset(m_szLan, 0, sizeof(m_szLan));

    int i = 0;

    g_StringLanType(m_szLan, "当前用户", "Current user");
    m_comboUserIndex.AddString(m_szLan);

    for (i = 0; i < 16; i++)
    {
        sprintf(m_szLan, "User%d", i+1);
        m_comboUserIndex.AddString(m_szLan);
    }
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLcdUserCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if (m_csPassword != m_csPasswordSure)
    {
        g_StringLanType(m_szLan, "密码与确认密码不一致", "password and confirm password are not same");
        AfxMessageBox(m_szLan);
        return;
    }

    DWORD dwIp = 0;
    m_struUserCfg.dwSize = sizeof(m_struUserCfg);
    memcpy(m_struUserCfg.sUserName, m_csUserName, min(sizeof(m_struUserCfg.sUserName), m_csUserName.GetLength()));
    memcpy(m_struUserCfg.sPassWord, m_csPassword, min(sizeof(m_struUserCfg.sPassWord), m_csPassword.GetLength()));
    m_cIp.GetAddress(dwIp);
    sprintf((char*)m_struUserCfg.struUserIP.sIpV4,  "%s", IPToStr(dwIp));
    memcpy(m_struUserCfg.byMacAddr, m_csMacAddr, min(sizeof(m_struUserCfg.byMacAddr), m_csMacAddr.GetLength()));
    m_struUserCfg.byPriority = m_comboPriority.GetCurSel() + 1;

    DWORD dwUserIndex = m_comboUserIndex.GetCurSel();
    if (dwUserIndex == 0)
    {
        dwUserIndex = 0xffffffff;
    }

    if (!NET_DVR_SetDVRConfig(m_lUserId, NET_DVR_SET_VCS_USER_CFG, dwUserIndex, &m_struUserCfg, sizeof(m_struUserCfg)))
    {
        g_StringLanType(m_szLan, "设置用户配置失败", "Set User Config failed");
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, m_szLan);
        return;
    }
    else
    {
        g_StringLanType(m_szLan, "设置用户配置成功", "Set User Config successful");
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, m_szLan);
	}	
}

void CDlgLcdUserCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwUserIndex = m_comboUserIndex.GetCurSel();
    DWORD dwReturn = 0;

    if (dwUserIndex == 0)
    {
        dwUserIndex = 0xffffffff;
    }

    if (!NET_DVR_GetDVRConfig(m_lUserId, NET_DVR_GET_VCS_USER_CFG, dwUserIndex, &m_struUserCfg, sizeof(m_struUserCfg), &dwReturn))
    {
        g_StringLanType(m_szLan, "获取用户配置失败", "Get User Config failed");
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, m_szLan);
        return;
    }
    else
    {
        g_StringLanType(m_szLan, "获取用户配置成功", "Get User Config successful");
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, m_szLan);
        m_csUserName = m_struUserCfg.sUserName;
        m_csPassword = m_struUserCfg.sPassWord;
        m_csPasswordSure = m_struUserCfg.sPassWord;
        m_csMacAddr = m_struUserCfg.byMacAddr;
        UpdateData(FALSE); 
        m_comboPriority.SetCurSel(m_struUserCfg.byPriority - 1);
        DWORD dwIpAddr = ntohl(inet_addr(m_struUserCfg.struUserIP.sIpV4));
        m_cIp.SetAddress(dwIpAddr);
        
	}    
}

void CDlgLcdUserCfg::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
    CDialog::OnCancel();
}
