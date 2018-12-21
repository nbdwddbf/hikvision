// UserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "UserDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserDlg dialog


CUserDlg::CUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserDlg)
	m_strVerifyPwd = _T("");
	m_strPwd = _T("");
	m_strUser = _T("");
	m_bRemoteParam = FALSE;
	m_bRemotePtz = FALSE;
	m_bRemoteOperation = FALSE;
	m_bRemoteReboot = FALSE;
	//}}AFX_DATA_INIT
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
}


void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserDlg)
	DDX_Control(pDX, IDC_COMBO_USER_SEL, m_UserCtrl);
	DDX_Text(pDX, IDC_EDIT_USER_VERIFY_PWD, m_strVerifyPwd);
	DDX_Text(pDX, IDC_EDIT_USER_PWD, m_strPwd);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_strUser);
	DDV_MaxChars(pDX, m_strUser, 16);
	DDX_Check(pDX, IDC_CHK_REMOTE_SET_PARAM, m_bRemoteParam);
	DDX_Check(pDX, IDC_CHK_REMOTE_PTZ_CTRL, m_bRemotePtz);
	DDX_Check(pDX, IDC_CHK_REMOTE_HIGH_OPERATION, m_bRemoteOperation);
	DDX_Check(pDX, IDC_CHK_REMOTE_REBOOT, m_bRemoteReboot);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserDlg, CDialog)
	//{{AFX_MSG_MAP(CUserDlg)
	ON_BN_CLICKED(ID_BTN_USER_OK, OnBtnUserOk)
	ON_CBN_SELCHANGE(IDC_COMBO_USER_SEL, OnSelchangeComboUserSel)	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserDlg message handlers
/*************************************************
函数名:    	OnBtnUserOk
函数描述:	设置密码
输入参数:   无
输出参数:   			
返回值:		
*************************************************/
void CUserDlg::OnBtnUserOk() 
{
	// TODO: Add your control notification handler code here	
	UpdateData(TRUE);
	char szLan[128] = {0};
	int sel = m_UserCtrl.GetCurSel();
	
	if (m_strPwd.GetLength() > 16)
	{
		g_StringLanType(szLan, "密码长度不能大于16字节", "The length of password can not be longer than 16 bytes");
		AfxMessageBox(szLan);
		return;
	}
	if (strcmp(m_strPwd, m_strVerifyPwd) != 0)
    {
		g_StringLanType(szLan, "密码与确认密码不一致", "Password is different from confirm password");
        AfxMessageBox(szLan);
        return;
    }

	memset(&m_User, 0, sizeof(m_User));
	int iSel = m_UserCtrl.GetCurSel() + 1;
    m_User.dwSize = sizeof(m_User);
	memcpy(m_User.sPassword, m_strPwd, m_strPwd.GetLength());
	
	m_User.byOtherRight[6] = m_bRemotePtz;
	m_User.byOtherRight[2] = m_bRemoteParam;
	m_User.byOtherRight[7] = m_bRemoteOperation;
	m_User.byOtherRight[1] = m_bRemoteReboot;

    if (!NET_DVR_SetAlarmDeviceUser(m_lServerID, iSel, &m_User))
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SetAlarmDeviceUser");
        MessageBox(NET_DVR_GetErrorMsg());
        return;
    }
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SetAlarmDeviceUser");
	}
}
/*************************************************
函数名:    	GetUserCfg
函数描述:	获取用户名密码
输入参数:   无
输出参数:   			
返回值:		
*************************************************/
BOOL CUserDlg::GetUserCfg()
{
    memset(&m_User, 0, sizeof(NET_DVR_ALARM_DEVICE_USER));
    m_User.dwSize = sizeof(m_User);
    DWORD dwReturn = 0;
	int iIndex = m_UserCtrl.GetCurSel() + 1;
    if (!NET_DVR_GetAlarmDeviceUser(m_lServerID, iIndex, &m_User))
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetAlarmDeviceUser");
        MessageBox(NET_DVR_GetErrorMsg());
        return FALSE;
    }
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetAlarmDeviceUser");
	}

	//m_UserCtrl.SetCurSel(0);
    //OnSelchangeComboUserSel();
    return TRUE;
}

void CUserDlg::OnSelchangeComboUserSel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_UserCtrl.GetCurSel() == 0)
	{
		GetDlgItem(IDC_EDIT_USER_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_REMOTE_SET_PARAM)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_REMOTE_PTZ_CTRL)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_REMOTE_HIGH_OPERATION)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_REMOTE_REBOOT)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_USER_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_REMOTE_SET_PARAM)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_REMOTE_PTZ_CTRL)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_REMOTE_HIGH_OPERATION)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_REMOTE_REBOOT)->EnableWindow(TRUE);
	}

	if (m_lServerID < 0)
	{
		return;
	}

	if (GetUserCfg() != TRUE)
	{
		return;
	}	
	
	m_bRemotePtz = m_User.byOtherRight[6];
	m_bRemoteParam = m_User.byOtherRight[2];
	m_bRemoteOperation = m_User.byOtherRight[7];
	m_bRemoteReboot = m_User.byOtherRight[1];
	
	m_strUser = m_User.sUserName;
	m_strPwd = m_User.sPassword;

	UpdateData(FALSE);
}

