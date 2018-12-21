// DlgRecordHostFilmModeCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRecordHostFilmModeCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordHostFilmModeCfg dialog


CDlgRecordHostFilmModeCfg::CDlgRecordHostFilmModeCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRecordHostFilmModeCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRecordHostFilmModeCfg)
		// NOTE: the ClassWizard will add member initialization here
    memset(&m_struFilmModeCfg, 0, sizeof(m_struFilmModeCfg));
	//}}AFX_DATA_INIT
}


void CDlgRecordHostFilmModeCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRecordHostFilmModeCfg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
    DDX_Control(pDX, IDC_COMB_TYPE, m_comType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRecordHostFilmModeCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgRecordHostFilmModeCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordHostFilmModeCfg message handlers


BOOL CDlgRecordHostFilmModeCfg::OnInitDialog()
{
    CDialog::OnInitDialog();
    //m_comType.AddString(_T("0-单画面"));
    //m_comType.AddString(_T("1-两画面"));
    //m_comType.AddString(_T("2-画中画"));
    m_comType.SetCurSel(0);
    

    return TRUE;
}

void CDlgRecordHostFilmModeCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    
    NET_DVR_STD_CONFIG struSTDConfig = {0};
    struSTDConfig.lpCondBuffer = &m_dwChannel;
    struSTDConfig.dwCondSize = sizeof(m_dwChannel);
    struSTDConfig.lpOutBuffer = &m_struFilmModeCfg;
    struSTDConfig.dwOutSize = sizeof(m_struFilmModeCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struSTDConfig.lpStatusBuffer = m_szStatusBuf;
    struSTDConfig.dwStatusSize = ISAPI_STATUS_LEN;


    if (NET_DVR_GetSTDConfig(m_lLoginID, NET_DVR_GET_FILM_MODE_CFG, &struSTDConfig))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_FILM_MODE_CFG");
        
        m_comType.SetCurSel(m_struFilmModeCfg.byScreenType);
        GetDlgItem(IDC_BTN_SET)->EnableWindow(TRUE);
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_FILM_MODE_CFG");
    }	
}

void CDlgRecordHostFilmModeCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_struFilmModeCfg.dwSize = sizeof(m_struFilmModeCfg);

    m_struFilmModeCfg.byScreenType = m_comType.GetCurSel();

    NET_DVR_STD_CONFIG struSTDConfig = {0};
    struSTDConfig.lpCondBuffer = &m_dwChannel;
    struSTDConfig.dwCondSize = sizeof(m_dwChannel);
    struSTDConfig.lpInBuffer = &m_struFilmModeCfg;
    struSTDConfig.dwInSize = sizeof(m_struFilmModeCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struSTDConfig.lpStatusBuffer = m_szStatusBuf;
    struSTDConfig.dwStatusSize = ISAPI_STATUS_LEN;


    if (NET_DVR_SetSTDConfig(m_lLoginID, NET_DVR_SET_FILM_MODE_CFG, &struSTDConfig))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_FILM_MODE_CFG");
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_FILM_MODE_CFG");
    }
}
