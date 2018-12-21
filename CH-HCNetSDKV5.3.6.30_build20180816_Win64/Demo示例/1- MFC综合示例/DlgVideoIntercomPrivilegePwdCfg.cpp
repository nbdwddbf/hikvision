// DlgVideoIntercomPrivilegePwdCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVideoIntercomPrivilegePwdCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomPrivilegePwdCfg dialog


CDlgVideoIntercomPrivilegePwdCfg::CDlgVideoIntercomPrivilegePwdCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVideoIntercomPrivilegePwdCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVideoIntercomPrivilegePwdCfg)
	m_strNewPwd = _T("");
	m_strOldPwd = _T("");
	m_strConfirmNewPwd = _T("");
	//}}AFX_DATA_INIT
	m_lServerID = -1;
	m_iDevIndex = -1;
}


void CDlgVideoIntercomPrivilegePwdCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVideoIntercomPrivilegePwdCfg)
	DDX_Control(pDX, IDC_COMBO_PWD_TYPE, m_comboPwdType);
	DDX_Text(pDX, IDC_EDIT_NEW_PWD, m_strNewPwd);
	DDX_Text(pDX, IDC_EDIT_OLD_PWD, m_strOldPwd);
	DDX_Text(pDX, IDC_EDIT_NEW_PWD_CONFIRM, m_strConfirmNewPwd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVideoIntercomPrivilegePwdCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVideoIntercomPrivilegePwdCfg)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomPrivilegePwdCfg message handlers

BOOL CDlgVideoIntercomPrivilegePwdCfg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitCtrlState();

	return TRUE;
}

void CDlgVideoIntercomPrivilegePwdCfg::OnBtnSet() 
{
	UpdateData(TRUE);

	char szError[64] = "\0";

	if (m_strConfirmNewPwd != m_strNewPwd)
	{
		g_StringLanType(szError, "两次输入的新密码不一致","Please confirm the new password again");
		AfxMessageBox(szError);
		return;
	}

	if (SetPrivilegePwdCfg())
	{   
		g_StringLanType(szError, "保存成功","Saved successfully");
	}
	else
	{
		g_StringLanType(szError, "保存失败","Save failed");
	}
	AfxMessageBox(szError);
}

void CDlgVideoIntercomPrivilegePwdCfg::InitCtrlState()
{
	char szItem[64] = "\0";
	g_StringLanType(szItem, "工程密码","Engineering");
	m_comboPwdType.InsertString(0,szItem);
	m_comboPwdType.SetItemData(0,ENUM_PRIVILEGE_PASSWORD_ENGINEERING);

	g_StringLanType(szItem, "布/撤防密码","Setup Alarm");
	m_comboPwdType.InsertString(1,szItem);
	m_comboPwdType.SetItemData(1,ENUM_PRIVILEGE_PASSWORD_SETUPALARM);

	g_StringLanType(szItem, "户主开锁密码","Householder Unlock");
	m_comboPwdType.InsertString(2,szItem);
	m_comboPwdType.SetItemData(2,ENUM_PRIVILEGE_PASSWORD_HOUSEHOLDER_UNLOCK);

	g_StringLanType(szItem, "防劫持密码","Anti Hijacking");
	m_comboPwdType.InsertString(3,szItem);
	m_comboPwdType.SetItemData(3,ENUM_PRIVILEGE_PASSWORD_ANTI_HIJACKING);

    g_StringLanType(szItem, "公共密码1", "Password Public 1");
    m_comboPwdType.InsertString(4, szItem);
    m_comboPwdType.SetItemData(4, ENUM_PRIVILEGE_PASSWORD_PUBLIC1);

    g_StringLanType(szItem, "公共密码2", "Password Public 2");
    m_comboPwdType.InsertString(5, szItem);
    m_comboPwdType.SetItemData(5, ENUM_PRIVILEGE_PASSWORD_PUBLIC2);

    g_StringLanType(szItem, "公共密码3", "Password Public 3");
    m_comboPwdType.InsertString(6, szItem);
    m_comboPwdType.SetItemData(6, ENUM_PRIVILEGE_PASSWORD_PUBLIC3);

    g_StringLanType(szItem, "发卡密码", "send card password");
    m_comboPwdType.InsertString(7, szItem);
    m_comboPwdType.SetItemData(7, ENUM_PRIVILEGE_PASSWORD_SENDCARD);

	m_comboPwdType.SetCurSel(0);
}


BOOL CDlgVideoIntercomPrivilegePwdCfg::SetPrivilegePwdCfg()
{
	NET_DVR_PRIVILEGE_PASSWORD_CFG struPwdCfg;
	struPwdCfg.dwSize = sizeof(struPwdCfg);

	int nPwdTypeIndex = m_comboPwdType.GetCurSel();
	if (nPwdTypeIndex == CB_ERR)
	{
		return FALSE;
	}
	struPwdCfg.byPwdType = m_comboPwdType.GetItemData(nPwdTypeIndex);
	strncpy((char*)struPwdCfg.byNewPassword,m_strNewPwd,PASSWD_LEN);
	strncpy((char*)struPwdCfg.byOldPassword,m_strOldPwd,PASSWD_LEN);

	BOOL  bRst = FALSE;

	
	if (NET_DVR_SetDVRConfig(m_lServerID,NET_DVR_SET_PRIVILEGE_PASSWORD,0,&struPwdCfg,sizeof(struPwdCfg)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_PRIVILEGE_PASSWORD");;
		bRst = TRUE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_PRIVILEGE_PASSWORD");
		bRst = FALSE;
	}
	
	return bRst;
}