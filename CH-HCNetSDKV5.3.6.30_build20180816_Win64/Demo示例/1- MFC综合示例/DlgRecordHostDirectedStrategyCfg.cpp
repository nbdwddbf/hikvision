// DlgRecordHostDirectedStrategyCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRecordHostDirectedStrategyCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordHostDirectedStrategyCfg dialog


CDlgRecordHostDirectedStrategyCfg::CDlgRecordHostDirectedStrategyCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRecordHostDirectedStrategyCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRecordHostDirectedStrategyCfg)
		// NOTE: the ClassWizard will add member initialization here
    memset(&m_struDirectedStrategy, 0, sizeof(m_struDirectedStrategy));
	//}}AFX_DATA_INIT
}


void CDlgRecordHostDirectedStrategyCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRecordHostDirectedStrategyCfg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
    DDX_Control(pDX, IDC_COMB_DIRECTED_STRATEGY, m_comStrategy);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRecordHostDirectedStrategyCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgRecordHostDirectedStrategyCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
    ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CDlgRecordHostDirectedStrategyCfg::OnInitDialog()
{
    CDialog::OnInitDialog();
    m_comStrategy.InsertString(0, _T("0-常态导播策略"));
    m_comStrategy.InsertString(1, _T("1-精品导播策略"));
    m_comStrategy.SetCurSel(0);
    
    //GetDlgItem(IDC_BTN_GET)->EnableWindow(TRUE);
    //GetDlgItem(IDC_BTN_SET)->EnableWindow(FALSE);

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordHostDirectedStrategyCfg message handlers

void CDlgRecordHostDirectedStrategyCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    
    NET_DVR_STD_CONFIG struSTDConfig = {0};
    struSTDConfig.lpCondBuffer = &m_lChannel;
    struSTDConfig.dwCondSize = sizeof(m_lChannel);
    struSTDConfig.lpOutBuffer = &m_struDirectedStrategy;
    struSTDConfig.dwOutSize = sizeof(m_struDirectedStrategy);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struSTDConfig.lpStatusBuffer = m_szStatusBuf;
    struSTDConfig.dwStatusSize = ISAPI_STATUS_LEN;


    if (NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_DIRECTED_STRATEGY_CFG, &struSTDConfig))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_DIRECTED_STRATEGY_CFG");
        
        m_comStrategy.SetCurSel(m_struDirectedStrategy.byDirectedStrategyType);
        //GetDlgItem(IDC_BTN_SET)->EnableWindow(TRUE);
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_DIRECTED_STRATEGY_CFG");
        //GetDlgItem(IDC_BTN_SET)->EnableWindow(FALSE);
    }
}

void CDlgRecordHostDirectedStrategyCfg::OnBtnSet()
{
	UpdateData(TRUE);

    m_struDirectedStrategy.byDirectedStrategyType = m_comStrategy.GetCurSel();
	m_struDirectedStrategy.dwSize = sizeof(m_struDirectedStrategy);

    NET_DVR_STD_CONFIG struSTDConfig = {0};
    struSTDConfig.lpCondBuffer = &m_lChannel;
    struSTDConfig.dwCondSize = sizeof(m_lChannel);
    struSTDConfig.lpInBuffer = &m_struDirectedStrategy;
    struSTDConfig.dwInSize = sizeof(m_struDirectedStrategy);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struSTDConfig.lpStatusBuffer = m_szStatusBuf;
    struSTDConfig.dwStatusSize = ISAPI_STATUS_LEN;

  
    if (NET_DVR_SetSTDConfig(m_lUserID, NET_DVR_SET_DIRECTED_STRATEGY_CFG, &struSTDConfig))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_DIRECTED_STRATEGY_CFG");
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_DIRECTED_STRATEGY_CFG");
    }    
}
