// DlgScaleOutCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgScaleOutCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgScaleOutCfg dialog


CDlgScaleOutCfg::CDlgScaleOutCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgScaleOutCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgScaleOutCfg)
	//}}AFX_DATA_INIT
}


void CDlgScaleOutCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgScaleOutCfg)
	DDX_Control(pDX, IDC_COMBO_OUT_SCALE8, m_comboOutScale8);
	DDX_Control(pDX, IDC_COMBO_OUT_SCALE7, m_comboOutScale7);
	DDX_Control(pDX, IDC_COMBO_OUT_SCALE6, m_comboOutScale6);
	DDX_Control(pDX, IDC_COMBO_OUT_SCALE5, m_comboOutScale5);
	DDX_Control(pDX, IDC_COMBO_OUT_SCALE4, m_comboOutScale4);
	DDX_Control(pDX, IDC_COMBO_OUT_SCALE3, m_comboOutScale3);
	DDX_Control(pDX, IDC_COMBO_OUT_SCALE2, m_comboOutScale2);
	DDX_Control(pDX, IDC_COMBO_OUT_SCALE, m_comboOutScale);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgScaleOutCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgScaleOutCfg)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgScaleOutCfg message handlers

void CDlgScaleOutCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_OUT_SCALE_CFG struOutScaleCfg = {0};
	struOutScaleCfg.dwSize = sizeof(NET_DVR_OUT_SCALE_CFG);
	struOutScaleCfg.byOutScale[0] = m_comboOutScale.GetCurSel();
	struOutScaleCfg.byOutScale[1] = m_comboOutScale2.GetCurSel();
	struOutScaleCfg.byOutScale[2] = m_comboOutScale3.GetCurSel();
	struOutScaleCfg.byOutScale[3] = m_comboOutScale4.GetCurSel();
	struOutScaleCfg.byOutScale[4] = m_comboOutScale5.GetCurSel();
	struOutScaleCfg.byOutScale[5] = m_comboOutScale6.GetCurSel();
	struOutScaleCfg.byOutScale[6] = m_comboOutScale7.GetCurSel();
	struOutScaleCfg.byOutScale[7] = m_comboOutScale8.GetCurSel();
	if (NET_DVR_SetDVRConfig(m_lUserID,NET_DVR_SET_OUT_SCALE_CFG,0,&struOutScaleCfg,sizeof(struOutScaleCfg)))
	{
		g_pMainDlg->AddLog(m_lUserID, OPERATION_SUCC_T, "NET_DVR_SET_OUT_SCALE_CFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_lUserID, OPERATION_FAIL_T, "NET_DVR_SET_OUT_SCALE_CFG");
	}
}

void CDlgScaleOutCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_OUT_SCALE_CFG struOutScaleCfg = {0};
	struOutScaleCfg.dwSize = sizeof(NET_DVR_OUT_SCALE_CFG);
	DWORD dwRet = 0;
	if (NET_DVR_GetDVRConfig(m_lUserID,NET_DVR_GET_OUT_SCALE_CFG,0,&struOutScaleCfg,sizeof(struOutScaleCfg),&dwRet))
	{
		g_pMainDlg->AddLog(m_lUserID, OPERATION_SUCC_T, "NET_DVR_GET_OUT_SCALE_CFG");
	}
	else
	{
		AfxMessageBox("»ñÈ¡Ê§°Ü");
		g_pMainDlg->AddLog(m_lUserID, OPERATION_FAIL_T, "NET_DVR_GET_OUT_SCALE_CFG");
		return;
	}
	m_comboOutScale.SetCurSel(struOutScaleCfg.byOutScale[0]);
	m_comboOutScale2.SetCurSel(struOutScaleCfg.byOutScale[1]);
	m_comboOutScale3.SetCurSel(struOutScaleCfg.byOutScale[2]);
	m_comboOutScale4.SetCurSel(struOutScaleCfg.byOutScale[3]);
	m_comboOutScale5.SetCurSel(struOutScaleCfg.byOutScale[4]);
	m_comboOutScale6.SetCurSel(struOutScaleCfg.byOutScale[5]);
	m_comboOutScale7.SetCurSel(struOutScaleCfg.byOutScale[6]);
	m_comboOutScale8.SetCurSel(struOutScaleCfg.byOutScale[7]);
	UpdateData(FALSE);
}

BOOL CDlgScaleOutCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	OnBtnGet();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
