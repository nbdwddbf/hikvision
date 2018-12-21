// DlgVideoIntercomGateway.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVideoIntercomGateway.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomGateway dialog


CDlgVideoIntercomGateway::CDlgVideoIntercomGateway(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVideoIntercomGateway::IDD, pParent)
    , m_iLockID(1)
{
	//{{AFX_DATA_INIT(CDlgVideoIntercomGateway)
	m_strControlSrcInfo = _T("");
	m_dwGatewayIndex = 1;
	m_strLockPassword = _T("");
	//}}AFX_DATA_INIT
	m_lServerID = -1;
	m_iDevIndex = -1;
}


void CDlgVideoIntercomGateway::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgVideoIntercomGateway)
    DDX_Control(pDX, IDC_COMBO_OPENLOCKTYPE, m_comboOpenLockType);
    DDX_Control(pDX, IDC_COMBO_LOCKTYPE, m_comboLockType);
    DDX_Control(pDX, IDC_COMBO_COMMAND, m_comboCommand);
    DDX_Text(pDX, IDC_EDIT_CONTROL_SRC_INFO, m_strControlSrcInfo);
    DDX_Text(pDX, IDC_EDIT_GATEWAY_INDEX, m_dwGatewayIndex);
    DDX_Text(pDX, IDC_EDIT_LOCK_PASSWORD, m_strLockPassword);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_LOCK_ID, m_iLockID);
}


BEGIN_MESSAGE_MAP(CDlgVideoIntercomGateway, CDialog)
	//{{AFX_MSG_MAP(CDlgVideoIntercomGateway)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_CBN_SELCHANGE(IDC_COMBO_LOCKTYPE, OnSelchangeComboLocktype)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoIntercomGateway message handlers

BOOL CDlgVideoIntercomGateway::OnInitDialog()
{
	CDialog::OnInitDialog();

	char szLan[32] ="\0";
	g_StringLanType(szLan,"关闭","Close");
    m_comboCommand.InsertString(0,szLan);
	g_StringLanType(szLan,"打开", "Open");
	m_comboCommand.InsertString(1,szLan);
    g_StringLanType(szLan,"常开", "Always Open");
    m_comboCommand.InsertString(2, szLan);
    g_StringLanType(szLan,"恢复", "Resume");
    m_comboCommand.InsertString(3, szLan);
	m_comboCommand.SetCurSel(1);
	m_comboLockType.SetCurSel(0);
	GetDlgItem(IDC_EDIT_LOCK_PASSWORD)->EnableWindow(FALSE);
	m_comboOpenLockType.SetCurSel(0);
	return TRUE;
}

void CDlgVideoIntercomGateway::OnBtnSet() 
{
	char szError[32] = "\0";
	if (!ControlGateway())
	{   
		g_StringLanType(szError, "设置失败","Set param failed");
		AfxMessageBox(szError);
	}
}

BOOL CDlgVideoIntercomGateway::ControlGateway()
{   
	UpdateData(TRUE);

	NET_DVR_CONTROL_GATEWAY struControlGateway = {0};
	struControlGateway.dwSize = sizeof(struControlGateway);
	struControlGateway.byCommand = m_comboCommand.GetCurSel();
	struControlGateway.dwGatewayIndex = m_dwGatewayIndex;
	struControlGateway.byLockType = m_comboLockType.GetCurSel();
    struControlGateway.wLockID = m_iLockID;
	strncpy((char*)struControlGateway.byControlSrc,m_strControlSrcInfo,NAME_LEN);
	struControlGateway.byControlType = m_comboOpenLockType.GetCurSel();
	strncpy((char*)struControlGateway.byPassword, m_strLockPassword, PASSWD_LEN);
    
	BOOL bRst = FALSE;
	
	if (NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_GATEWAY,&struControlGateway,sizeof(struControlGateway)))
	{   
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_REMOTECONTROL_GATEWAY");
		bRst = TRUE;
	}
	else
	{   
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_REMOTECONTROL_GATEWAY");
		bRst = FALSE;
	}

	return bRst;
}

void CDlgVideoIntercomGateway::OnSelchangeComboLocktype() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (0 == m_comboLockType.GetCurSel())
	{
		GetDlgItem(IDC_EDIT_LOCK_PASSWORD)->EnableWindow(FALSE);
	}
	else if(1 == m_comboLockType.GetCurSel())
	{
		GetDlgItem(IDC_EDIT_LOCK_PASSWORD)->EnableWindow(TRUE);
	}
}
