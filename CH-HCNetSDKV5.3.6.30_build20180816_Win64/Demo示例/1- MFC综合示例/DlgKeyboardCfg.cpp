// DlgKeyboardCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgKeyboardCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgKeyboardCfg dialog


CDlgKeyboardCfg::CDlgKeyboardCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKeyboardCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgKeyboardCfg)
	m_bKeyBoardLock = FALSE;
	m_nLockTime = 0;
	m_nErrortimes = 0;
	//}}AFX_DATA_INIT
}


void CDlgKeyboardCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgKeyboardCfg)
	DDX_Control(pDX, IDC_CMB_KEYBOARD_ID, m_cmbKeyboardID);
	DDX_Check(pDX, IDC_CHK_KEYBOARD_LOCK, m_bKeyBoardLock);
	DDX_Text(pDX, IDC_EDIT_LOCK_TIME, m_nLockTime);
	DDX_Text(pDX, IDC_EDIT_PSW_ERROR_TIMES, m_nErrortimes);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgKeyboardCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgKeyboardCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgKeyboardCfg message handlers

void CDlgKeyboardCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

	NET_DVR_KEYBOARD_CFG struKeyboardAlarmCfg = {0};
	
	struKeyboardAlarmCfg.dwSize = sizeof(struKeyboardAlarmCfg);

	DWORD iKeyboardID = m_cmbKeyboardID.GetItemData(m_cmbKeyboardID.GetCurSel());

	DWORD returned = 0;
	char szLan[128] = {0};
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_KEYBOARD_CFG, iKeyboardID, &struKeyboardAlarmCfg, sizeof(struKeyboardAlarmCfg), &returned))
	{
		g_StringLanType(szLan, "»ñÈ¡¼üÅÌ²ÎÊýÅäÖÃÊ§°Ü" , "NET_DVR_GET_KEYBOARD_CFG FAILED");
		MessageBox(szLan);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_KEYBOARD_CFG FAILED");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_KEYBOARD_CFG SUCC");
	}

	m_bKeyBoardLock = struKeyboardAlarmCfg.byEnableLock;
	m_nLockTime = struKeyboardAlarmCfg.wLockTime;
	m_nErrortimes = struKeyboardAlarmCfg.byErrorTimes;

	UpdateData(FALSE);
}

void CDlgKeyboardCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	NET_DVR_KEYBOARD_CFG struKeyboardAlarmCfg = {0};

	struKeyboardAlarmCfg.dwSize = sizeof(struKeyboardAlarmCfg);

	struKeyboardAlarmCfg.byEnableLock = m_bKeyBoardLock;
	struKeyboardAlarmCfg.wLockTime = m_nLockTime;
	struKeyboardAlarmCfg.byErrorTimes = m_nErrortimes;

	DWORD iKeyboardID = m_cmbKeyboardID.GetItemData(m_cmbKeyboardID.GetCurSel());

	char szLan[128] = {0};
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_KEYBOARD_CFG, iKeyboardID, &struKeyboardAlarmCfg, sizeof(struKeyboardAlarmCfg)))
	{
		g_StringLanType(szLan, "ÉèÖÃ¼üÅÌ²ÎÊýÅäÖÃÊ§°Ü" , "NET_DVR_SET_KEYBOARD_CFG FAILED");
		MessageBox(szLan);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_KEYBOARD_CFG FAILED");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_KEYBOARD_CFG SUCC");
	}
}

BOOL CDlgKeyboardCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cmbKeyboardID.ResetContent();
	CString csTmp(_T(""));
	int i = 0;

	for (i = 0; i < 33; i++)
	{
		csTmp.Format(_T("%d"), i);
		m_cmbKeyboardID.AddString(csTmp);
        m_cmbKeyboardID.SetItemData( i+1, i);
	}

	m_cmbKeyboardID.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
