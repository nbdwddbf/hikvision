// DlgCuntomProtocal.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgCuntomProtocal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCuntomProtocal dialog


CDlgCuntomProtocal::CDlgCuntomProtocal(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCuntomProtocal::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCuntomProtocal)
	m_dwSubPort = 0;
	m_dwMainPort = 0;
	m_csSubPath = _T("");
	m_csProName = _T("");
	m_csMainPath = _T("");
	m_bEnableSub = FALSE;
	m_bEnable = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgCuntomProtocal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCuntomProtocal)
	DDX_Control(pDX, IDC_COMBO_SUB_TRANS_TYPE, m_cmbSubTransType);
	DDX_Control(pDX, IDC_COMBO_MAIN_TRANS_TYPE, m_cmbMainTransType);
	DDX_Control(pDX, IDC_COMBO_PRO_INDEX, m_comboIndex);
	DDX_Control(pDX, IDC_COMBO_MAIN_PRO_TYPE, m_comboMainType);
	DDX_Control(pDX, IDC_COMBO_SUB_PRO_TYPE, m_comboSubType);
	DDX_Text(pDX, IDC_EDIT_SUB_PORT, m_dwSubPort);
	DDX_Text(pDX, IDC_EDIT_MAIN_PORT, m_dwMainPort);
	DDX_Text(pDX, IDC_EDIT_SUB_PATH, m_csSubPath);
	DDX_Text(pDX, IDC_EDIT_NAME, m_csProName);
	DDX_Text(pDX, IDC_EDIT_MAIN_PATH, m_csMainPath);
	DDX_Check(pDX, IDC_CHK_ENABLE_SUB, m_bEnableSub);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCuntomProtocal, CDialog)
	//{{AFX_MSG_MAP(CDlgCuntomProtocal)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_CBN_SELCHANGE(IDC_COMBO_PRO_INDEX, OnSelchangeComboProIndex)
	ON_BN_CLICKED(IDC_BUTTON_SETUP, OnButtonSetup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCuntomProtocal message handlers

BOOL CDlgCuntomProtocal::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_comboIndex.SetCurSel(0);
	m_comboMainType.SetCurSel(0);
	m_comboSubType.SetCurSel(0);
	m_cmbMainTransType.SetCurSel(0);
	m_cmbSubTransType.SetCurSel(0);

    m_comboIndex.ResetContent();

    CString strProtocol;

    for (int i = 1; i <= 128; i++)
    {
        strProtocol.Format("Protocal %d", i);
        m_comboIndex.AddString(strProtocol);
    }

    m_comboIndex.SetCurSel(0);

	OnButtonUpdate();
	
	return TRUE;
}

void CDlgCuntomProtocal::OnButtonExit() 
{
	CDialog::OnCancel();
}

void CDlgCuntomProtocal::OnButtonUpdate() 
{
	int iIndex = m_comboIndex.GetCurSel() + 1;
	
	ZeroMemory(&m_strProtocal, sizeof(m_strProtocal));
	DWORD dwReturned = 0;
	if(!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_CUSTOM_PRO_CFG, iIndex, &m_strProtocal, sizeof(m_strProtocal), &dwReturned))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_CUSTOM_PRO_CFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_CUSTOM_PRO_CFG");
	
		m_bEnable = m_strProtocal.dwEnabled;
		m_csProName.Format("%s", m_strProtocal.sProtocalName);
		m_bEnableSub = m_strProtocal.dwEnableSubStream;

		m_comboMainType.SetCurSel(m_strProtocal.byMainProType);
		m_cmbMainTransType.SetCurSel(m_strProtocal.byMainTransType);
		m_dwMainPort = m_strProtocal.wMainPort;
		m_csMainPath.Format("%s", m_strProtocal.sMainPath);

		m_comboSubType.SetCurSel(m_strProtocal.bySubProType);
		m_cmbSubTransType.SetCurSel(m_strProtocal.bySubTransType);
		m_dwSubPort = m_strProtocal.wSubPort;
		m_csSubPath.Format("%s", m_strProtocal.sSubPath);
		
		UpdateData(FALSE);
	}
}

void CDlgCuntomProtocal::OnSelchangeComboProIndex() 
{
	OnButtonUpdate();
}

void CDlgCuntomProtocal::OnButtonSetup() 
{
	UpdateData(TRUE);
	
	int iIndex = m_comboIndex.GetCurSel() + 1;

	m_strProtocal.dwSize = sizeof(m_strProtocal);

	m_strProtocal.dwEnabled = m_bEnable;
	sprintf(m_strProtocal.sProtocalName, "%s", m_csProName);
	m_strProtocal.dwEnableSubStream = m_bEnableSub;
	
	m_strProtocal.byMainProType = m_comboMainType.GetCurSel();
	m_strProtocal.byMainTransType = m_cmbMainTransType.GetCurSel();
	m_strProtocal.wMainPort = m_dwMainPort;
	sprintf(m_strProtocal.sMainPath, "%s", m_csMainPath);
	
	m_strProtocal.bySubProType = m_comboSubType.GetCurSel();
	m_strProtocal.bySubTransType = m_cmbSubTransType.GetCurSel();
	m_strProtocal.wSubPort = m_dwSubPort;
	sprintf(m_strProtocal.sSubPath, "%s", m_csSubPath);
	
	if(!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_CUSTOM_PRO_CFG, iIndex, &m_strProtocal, sizeof(m_strProtocal)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_CUSTON_PRO_CFG");
		CString cs;
		cs.Format("NET_DVR_SET_CUSTOM_PRO_CFG failed!Error[%d]", NET_DVR_GetLastError());
		AfxMessageBox(cs);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_CUSTOM_PRO_CFG");
	}	
}
