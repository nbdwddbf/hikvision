// DlgMatUnitedSystem.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMatUnitedSystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMatUnitedSystem dialog


CDlgMatUnitedSystem::CDlgMatUnitedSystem(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMatUnitedSystem::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMatUnitedSystem)
	m_csAdress = _T("");
	m_csPassWord = _T("");
	m_wPort = 0;
	m_dwSeq = 0;
	m_csUserName = _T("");
	//}}AFX_DATA_INIT
}


void CDlgMatUnitedSystem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMatUnitedSystem)
	DDX_Control(pDX, IDC_COMBO_SYSTEM_NUM, m_comboSystemNum);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_csAdress);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csPassWord);
	DDX_Text(pDX, IDC_EDIT_PORT, m_wPort);
	DDX_Text(pDX, IDC_EDIT_SEQ, m_dwSeq);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_csUserName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMatUnitedSystem, CDialog)
	//{{AFX_MSG_MAP(CDlgMatUnitedSystem)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_CBN_SELCHANGE(IDC_COMBO_SYSTEM_NUM, OnSelchangeComboSystemNum)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMatUnitedSystem message handlers

void CDlgMatUnitedSystem::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturned = 0;
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_UNITEDMATRIXSYSTEM, 0, &m_struInfo, sizeof(m_struInfo), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_UNITEDMATRIXSYSTEM");
		AfxMessageBox("获取失败");
		return;
	}
	
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_UNITEDMATRIXSYSTEM");
	AfxMessageBox("获取成功");
}

BOOL CDlgMatUnitedSystem::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	memset(&m_struInfo, 0, sizeof(m_struInfo));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMatUnitedSystem::OnSelchangeComboSystemNum() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iSel = m_comboSystemNum.GetCurSel();
	m_dwSeq = m_struInfo.struMatrixInfo[iSel].dwSequence;
	m_wPort = m_struInfo.struMatrixInfo[iSel].wSubMatrixPort;
	m_csAdress.Format("%s", m_struInfo.struMatrixInfo[iSel].sAddress);
	m_csPassWord.Format("%s", m_struInfo.struMatrixInfo[iSel].sPassword);
	m_csUserName.Format("%s", m_struInfo.struMatrixInfo[iSel].sUserName);

	UpdateData(FALSE);
}

void CDlgMatUnitedSystem::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
