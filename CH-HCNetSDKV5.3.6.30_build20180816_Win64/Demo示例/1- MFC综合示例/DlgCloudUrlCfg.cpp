// DlgCloudUrlCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgCloudUrlCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCloudUrlCfg dialog


CDlgCloudUrlCfg::CDlgCloudUrlCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCloudUrlCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCloudUrlCfg)
	m_csCloudUrl = _T("");
	//}}AFX_DATA_INIT
}

BOOL CDlgCloudUrlCfg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    // TODO: Add extra initialization here
    m_comboCloudType.SetCurSel(0);
    //GetDlgItem(IDC_EDIT_CLOUD_URL)->EnableWindow(FALSE);
    return TRUE;
}

void CDlgCloudUrlCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCloudUrlCfg)
    DDX_Control(pDX, IDC_COMBO_CLOUD_TYPE, m_comboCloudType);
    DDX_Text(pDX, IDC_EDIT_CLOUD_URL, m_csCloudUrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCloudUrlCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgCloudUrlCfg)
	ON_BN_CLICKED(IDC_BTN_GET_CLOUD_URL, OnBtnGetCloudUrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCloudUrlCfg message handlers

void CDlgCloudUrlCfg::OnBtnGetCloudUrl() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    NET_DVR_CLOUD_URL_COND struCloudUrlCond = {0};
    struCloudUrlCond.dwSize = sizeof(struCloudUrlCond);
    struCloudUrlCond.byType = m_comboCloudType.GetCurSel()+1;
    NET_DVR_CLOUD_URL struCloudUrl = {0};
    struCloudUrl.dwSize = sizeof(struCloudUrl);
    
    NET_DVR_STD_CONFIG struStdConfig = {0};
    struStdConfig.lpCondBuffer = (LPVOID)&struCloudUrlCond;
    struStdConfig.dwCondSize = sizeof(struCloudUrlCond);
    struStdConfig.lpOutBuffer = (LPVOID)&struCloudUrl;
    struStdConfig.dwOutSize = sizeof(struCloudUrl);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struStdConfig.lpStatusBuffer = m_szStatusBuf;
    struStdConfig.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_CLOUD_URL, &struStdConfig))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_CLOUD_URL");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_CLOUD_URL");
	}
    m_csCloudUrl = struCloudUrl.szURL;
    UpdateData(FALSE);
}
