// DlgCloudCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgCloudCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCloudCfg dialog


CDlgCloudCfg::CDlgCloudCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCloudCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCloudCfg)
	m_csAuthCode = _T("");
    m_csAlias = _T("");
    m_i64TotalCapability = 0;
    m_i64UsedSpace = 0;
    memset(&m_struCloudCfg, 0, sizeof(m_struCloudCfg));
    memset(&m_struStdConfig, 0, sizeof(m_struStdConfig));
	//}}AFX_DATA_INIT
}

BOOL CDlgCloudCfg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    m_comboEnable.SetCurSel(0);
    m_comboCloudType.SetCurSel(0);
    m_comboStatus.SetCurSel(0);
    GetDlgItem(IDC_EDIT_ALIAS)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_TOTAL_CAPABILITY)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_USED_SPACE)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_STATUS)->EnableWindow(FALSE);
    return TRUE;
}

void CDlgCloudCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCloudCfg)
    DDX_Control(pDX, IDC_COMBO_ENABLE, m_comboEnable);
    DDX_Control(pDX, IDC_COMBO_CLOUD_TYPE, m_comboCloudType);
    DDX_Control(pDX, IDC_COMBO_STATUS, m_comboStatus);
    DDX_Text(pDX, IDC_EDIT_AUTH_CODE, m_csAuthCode);
    DDX_Text(pDX, IDC_EDIT_ALIAS, m_csAlias);
    DDX_Text(pDX, IDC_EDIT_TOTAL_CAPABILITY, m_i64TotalCapability);
    DDX_Text(pDX, IDC_EDIT_USED_SPACE, m_i64UsedSpace);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCloudCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgCloudCfg)
	ON_BN_CLICKED(IDC_BTN_GET_CLOUD_CFG, OnBtnGetCloudCfg)
	ON_BN_CLICKED(IDC_BTN_SET_CLOUD_CFG, OnBtnSetCloudCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCloudCfg message handlers

void CDlgCloudCfg::OnBtnGetCloudCfg() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    
    m_struCloudCfg.dwSize = sizeof(m_struCloudCfg);
    m_struStdConfig.lpInBuffer = NULL;
    m_struStdConfig.dwInSize = 0;
    m_struStdConfig.lpOutBuffer = (LPVOID)&m_struCloudCfg;
    m_struStdConfig.dwOutSize = sizeof(m_struCloudCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    m_struStdConfig.lpStatusBuffer = m_szStatusBuf;
    m_struStdConfig.dwStatusSize = ISAPI_STATUS_LEN;
    
    if (!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_CLOUD_CFG, &m_struStdConfig))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_CLOUD_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_CLOUD_CFG");
    }
    m_comboEnable.SetCurSel(m_struCloudCfg.byEnable);
    m_comboCloudType.SetCurSel(m_struCloudCfg.byType - 1);
    m_comboStatus.SetCurSel(m_struCloudCfg.byStatus-1);
    m_csAuthCode = m_struCloudCfg.szAuthCode;
    m_csAlias = m_struCloudCfg.szAlias;
    m_i64TotalCapability = m_struCloudCfg.i64TotalCapability;
    m_i64UsedSpace = m_struCloudCfg.i64UsedSpace;

    UpdateData(FALSE);
}

void CDlgCloudCfg::OnBtnSetCloudCfg() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    
    m_struCloudCfg.dwSize = sizeof(m_struCloudCfg);
    m_struCloudCfg.byEnable = m_comboEnable.GetCurSel();
    m_struCloudCfg.byType = m_comboCloudType.GetCurSel() + 1;
    //m_struCloudCfg.byStatus = m_comboStatus.GetCurSel() + 1;  //只读
    strcpy(m_struCloudCfg.szAuthCode, m_csAuthCode);
    //strcpy(m_struCloudCfg.szAlias, m_csAlias);    //只读
    //m_struCloudCfg.i64TotalCapability = m_i64TotalCapability; //只读
    //m_struCloudCfg.i64UsedSpace = m_i64UsedSpace; //只读

    m_struStdConfig.lpInBuffer = (LPVOID)&m_struCloudCfg;
    m_struStdConfig.dwInSize = sizeof(m_struCloudCfg);
    m_struStdConfig.lpOutBuffer = NULL;
    m_struStdConfig.dwOutSize = 0;
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    m_struStdConfig.lpStatusBuffer = m_szStatusBuf;
    m_struStdConfig.dwStatusSize = ISAPI_STATUS_LEN;
    
    if (!NET_DVR_SetSTDConfig(m_lUserID, NET_DVR_SET_CLOUD_CFG, &m_struStdConfig))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_CLOUD_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_CLOUD_CFG");
    }
    
    UpdateData(FALSE);
}
