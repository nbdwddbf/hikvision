// DlgCloudStorageCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgCloudStorageCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCloudStorageCfg dialog


CDlgCloudStorageCfg::CDlgCloudStorageCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCloudStorageCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCloudStorageCfg)
		// NOTE: the ClassWizard will add member initialization here
	m_bEnable = FALSE;
	m_csIP = _T("");
	m_csIPV6 = _T("");
	m_wPort = 0;
	m_csPasswd = _T("");
	m_csUserName = _T("");
	m_dwPoolID = 0;
	//}}AFX_DATA_INIT
	m_lServerID = -1;
	memset(&m_struCloudStorageCfg, 0, sizeof(m_struCloudStorageCfg));
	memset(&m_struCloudStorageCond, 0, sizeof(m_struCloudStorageCond));
}


void CDlgCloudStorageCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCloudStorageCfg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_COMBO_POOLPARAM, m_comboPoolParam);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	DDX_Text(pDX, IDC_EDIT_IP, m_csIP);
	DDX_Text(pDX, IDC_EDIT_IPV6, m_csIPV6);
	DDX_Text(pDX, IDC_EDIT_PORT, m_wPort);
	DDX_Text(pDX, IDC_EDIT_PASSWD, m_csPasswd);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_csUserName);
	DDX_Text(pDX, IDC_EDIT_POOL_ID, m_dwPoolID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCloudStorageCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgCloudStorageCfg)
		// NOTE: the ClassWizard will add message map macros here
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_WM_CANCELMODE()
	ON_CBN_SELCHANGE(IDC_COMBO_POOLPARAM, OnSelchangeComboPoolparam)
	ON_BN_CLICKED(IDC_BTN_SURE, OnBtnSure)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
//	ON_EN_CHANGE(IDC_EDIT_PORT, OnChangeEditPort)
//	ON_EN_ERRSPACE(IDC_EDIT_PORT, OnErrspaceEditPort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCloudStorageCfg message handlers
/////////////////////////////////////////////////////////////////////////////
// CDlgCloudStorageCfg message handlers
BOOL CDlgCloudStorageCfg::SaveDataFromUI()
{
	UpdateData(TRUE);
	m_struCloudStorageCfg.dwSize = sizeof(m_struCloudStorageCfg);
	memcpy(m_struCloudStorageCfg.struIP.sIpV4, m_csIP, 16);
	memcpy(m_struCloudStorageCfg.struIP.byIPv6, m_csIPV6, 128);
	memcpy(m_struCloudStorageCfg.szPassword, m_csPasswd, 48);
	memcpy(m_struCloudStorageCfg.szUser, m_csUserName, 48);
	if (m_wPort > 65535 || m_wPort < 2000)
	{
		AfxMessageBox("云存储端口号值应小于65535，大于2000!");
		return FALSE;
	}
	m_struCloudStorageCfg.wPort = m_wPort;
	m_struCloudStorageCfg.byEnable = m_bEnable; 

	return TRUE;
}

BOOL CDlgCloudStorageCfg::UpdataDataToUI()
{	
	char szPasswdLan[49] = {0};
	char szUserNameLan[49] = {0};
	memcpy(szPasswdLan, m_struCloudStorageCfg.szPassword, 48);
	memcpy(szUserNameLan, m_struCloudStorageCfg.szUser, 48);
	m_csIP = m_struCloudStorageCfg.struIP.sIpV4;
	m_csIPV6 = m_struCloudStorageCfg.struIP.byIPv6;
	m_csPasswd.Format("%s",szPasswdLan);
	m_csUserName.Format("%s",szUserNameLan);
	m_wPort = m_struCloudStorageCfg.wPort;
	m_bEnable = m_struCloudStorageCfg.byEnable;
	UpdateData(FALSE);
	return TRUE;
}

void CDlgCloudStorageCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struCloudStorageCond.dwChannel = 1;
	m_struCloudStorageCond.dwSize = sizeof(m_struCloudStorageCond);

	SaveDataFromUI();

	char szLan[128] = {0};
	char szTemp[256] = {0};
	
	DWORD *pStatus = new DWORD;
	memset(pStatus, 0, 4);
	if (!NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_CLOUDSTORAGE_CFG, 1, &m_struCloudStorageCond, sizeof(m_struCloudStorageCond), \
		pStatus, &m_struCloudStorageCfg, sizeof(m_struCloudStorageCfg)))
	{
		g_StringLanType(szLan, "设置云存储参数失败", "Set Cloud Storage Param configuration failed");
		sprintf(szTemp, "%s %s %d", szLan, NET_DVR_GetErrorMsg(),NET_DVR_GetLastError());
		AfxMessageBox(szTemp);
		delete [] pStatus;
		return;
	}
	else
	{
		if (*pStatus != 0)
		{
			g_StringLanType(szLan, "设置云存储参数失败", "Set Cloud Storage Param configuration failed");
			sprintf(szTemp, "%s %d %s ", szLan, NET_DVR_GetLastError(), NET_DVR_GetErrorMsg());
			AfxMessageBox(szTemp);
			delete [] pStatus;
			return;
		}
	}
	delete [] pStatus;
}

BOOL CDlgCloudStorageCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();

// 	CRect rc(0, 0, 0, 0);
// 	GetParent()->GetClientRect(&rc);
// 	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
// 	MoveWindow(&rc);
	// TODO: Add extra initialization here
// 	m_struCloudStorageCond.dwChannel = 1;
// 	m_struCloudStorageCond.dwSize = sizeof(m_struCloudStorageCond);
// 	OnBtnGet();
	m_comboPoolParam.SetCurSel(2);
	OnSelchangeComboPoolparam();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCloudStorageCfg::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CDlgCloudStorageCfg::OnSelchangeComboPoolparam() 
{
	// TODO: Add your control notification handler code here
	
	m_dwPoolID = m_struCloudStorageCfg.struPoolInfo[m_comboPoolParam.GetCurSel()].dwPoolID;
	UpdateData(FALSE);
}

void CDlgCloudStorageCfg::OnBtnSure() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struCloudStorageCfg.struPoolInfo[m_comboPoolParam.GetCurSel()].dwPoolID = m_dwPoolID;
}

void CDlgCloudStorageCfg::CurCfgUpdate()
{
	m_struCloudStorageCond.dwChannel = 1;
	m_struCloudStorageCond.dwSize = sizeof(m_struCloudStorageCond);
	OnBtnGet();
}

void CDlgCloudStorageCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	char szTemp[256] = {0};
	
	m_struCloudStorageCond.dwChannel = 1;
	m_struCloudStorageCond.dwSize = sizeof(m_struCloudStorageCond);

	DWORD *pStatus = new DWORD;
	memset(pStatus, 0, sizeof(DWORD));
	
	if (NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_CLOUDSTORAGE_CFG, 1, &m_struCloudStorageCond, \
		sizeof(m_struCloudStorageCond), pStatus, &m_struCloudStorageCfg, sizeof(m_struCloudStorageCfg)))
	{
		if (*pStatus != 0)
		{
			g_StringLanType(szLan, "获取云存储参数失败", "Get Cloud Storage Param configuration failed");
			sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
			AfxMessageBox(szTemp);
			delete [] pStatus;
			return;
		}
	}
	else
	{
		delete [] pStatus;
		g_StringLanType(szLan, "获取云存储参数失败", "Get Cloud Storage Param configuration failed");
		sprintf(szTemp, "%s %s %d", szLan, NET_DVR_GetErrorMsg(), NET_DVR_GetLastError());
		AfxMessageBox(szTemp);
		return;	
	}
	delete [] pStatus;

	m_comboPoolParam.SetCurSel(2);
	OnSelchangeComboPoolparam();
	UpdataDataToUI();
	UpdateData(FALSE);
}

//void CDlgCloudStorageCfg::OnChangeEditPort() 
//{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
// 	UpdateData(TRUE);
// 	if (m_wPort > 65535 || m_wPort < 2000)
// 	{
// 		AfxMessageBox("云存储端口号值应小于65535，大于2000!");
// 		return;
// 	}
//}

