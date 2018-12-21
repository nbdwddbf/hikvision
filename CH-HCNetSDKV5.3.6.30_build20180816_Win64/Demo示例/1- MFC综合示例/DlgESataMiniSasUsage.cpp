// DlgESataMiniSasUsage.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgESataMiniSasUsage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgESataMiniSasUsage dialog


CDlgESataMiniSasUsage::CDlgESataMiniSasUsage(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgESataMiniSasUsage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgESataMiniSasUsage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(&m_struESataMiniSasUsage, 0, sizeof(m_struESataMiniSasUsage));
}


void CDlgESataMiniSasUsage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgESataMiniSasUsage)
	DDX_Control(pDX, IDC_COMBO_ESATA, m_cmbESata);
	DDX_Control(pDX, IDC_COMBO_ESATA_USAGE, m_cmbESataUsage);
	DDX_Control(pDX, IDC_COMBO_MINISAS, m_cmbMiniSas);
	DDX_Control(pDX, IDC_COMBO_MINISAS_USAGE, m_cmbMiniSasUsage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgESataMiniSasUsage, CDialog)
	//{{AFX_MSG_MAP(CDlgESataMiniSasUsage)
	ON_CBN_SELCHANGE(IDC_COMBO_MINISAS, OnSelchangeComboMinisas)
	ON_CBN_SELCHANGE(IDC_COMBO_ESATA, OnSelchangeComboEsata)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_ESATA_SAVE, OnButtonEsataSave)
	ON_BN_CLICKED(IDC_BUTTON_MINISAS_SAVE, OnButtonMinisasSave)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgESataMiniSasUsage message handlers

void CDlgESataMiniSasUsage::OnSelchangeComboMinisas() 
{
	// TODO: Add your control notification handler code here
	int iIndex = m_cmbMiniSas.GetCurSel();
	m_cmbMiniSasUsage.SetCurSel(m_struESataMiniSasUsage.byMiniSASUsage[iIndex]);

	UpdateData(FALSE);
	
}

void CDlgESataMiniSasUsage::OnSelchangeComboEsata() 
{
	// TODO: Add your control notification handler code here
	int iIndex = m_cmbESata.GetCurSel();
	m_cmbESataUsage.SetCurSel(m_struESataMiniSasUsage.byESATAUsage[iIndex]);

	UpdateData(FALSE);
}

BOOL CDlgESataMiniSasUsage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int i = 0;
	CString strTemp;
	for (i=1; i<=MAX_ESATA_NUM; i++)
	{
		strTemp.Format("%d", i);
		m_cmbESata.AddString(strTemp);
	}

	for (i=1; i<=MAX_MINISAS_NUM; i++)
	{
		strTemp.Format("%d", i);
		m_cmbMiniSas.AddString(strTemp);
	}

	OnButtonGet();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgESataMiniSasUsage::OnButtonGet() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};

	memset(&m_struESataMiniSasUsage, 0, sizeof(m_struESataMiniSasUsage));

	DWORD dwReturnedBytes = 0;
	if(TRUE == NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_ESATA_MINISAS_USAGE_CFG, -1, &m_struESataMiniSasUsage, sizeof(m_struESataMiniSasUsage), &dwReturnedBytes))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ESATA_MINISAS_USAGE_CFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ESATA_MINISAS_USAGE_CFG");
		g_StringLanType(szLan, "获取ESATA和miniSAS用途失败", "Fail to get ESATA & miniSAS usage");
		AfxMessageBox(szLan);
	}

	m_cmbESata.SetCurSel(0);
	m_cmbESataUsage.SetCurSel(m_struESataMiniSasUsage.byESATAUsage[0]);
	m_cmbMiniSas.SetCurSel(0);
	m_cmbMiniSasUsage.SetCurSel(m_struESataMiniSasUsage.byMiniSASUsage[0]);
	
	UpdateData(FALSE);
}

void CDlgESataMiniSasUsage::OnButtonEsataSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iIndex = m_cmbESata.GetCurSel();
	m_struESataMiniSasUsage.byESATAUsage[iIndex] = m_cmbESataUsage.GetCurSel();
}

void CDlgESataMiniSasUsage::OnButtonMinisasSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iIndex = m_cmbMiniSas.GetCurSel();
	m_struESataMiniSasUsage.byMiniSASUsage[iIndex] = m_cmbMiniSasUsage.GetCurSel();
}

void CDlgESataMiniSasUsage::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};

    m_struESataMiniSasUsage.dwSize = sizeof(m_struESataMiniSasUsage);
    if (NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_ESATA_MINISAS_USAGE_CFG, -1, &m_struESataMiniSasUsage, sizeof(m_struESataMiniSasUsage)))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_ESATA_MINISAS_USAGE_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_ESATA_MINISAS_USAGE_CFG");
		g_StringLanType(szLan, "设置ESATA和miniSAS用途失败", "Fail to set ESATA & miniSAS usage");
		AfxMessageBox(szLan);
    }
}
