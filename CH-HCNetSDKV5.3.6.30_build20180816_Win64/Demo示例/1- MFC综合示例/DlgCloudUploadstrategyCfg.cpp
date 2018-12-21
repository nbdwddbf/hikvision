// DlgCloudUploadstrategyCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgCloudUploadstrategyCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCloudUploadstrategyCfg dialog


CDlgCloudUploadstrategyCfg::CDlgCloudUploadstrategyCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCloudUploadstrategyCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCloudUploadstrategyCfg)
    memset(&m_struCloudUploadStrategyCond, 0, sizeof(m_struCloudUploadStrategyCond));
    memset(&m_struCloudUploadStrategy, 0, sizeof(m_struCloudUploadStrategy));
    memset(&m_struStdConfig, 0, sizeof(m_struStdConfig));
    m_bAllEvent = FALSE;
    m_bMotion = FALSE;
    m_bAlarm = FALSE;
    m_bVCA = FALSE;
	//}}AFX_DATA_INIT
}

BOOL CDlgCloudUploadstrategyCfg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    m_comboStrategyType.SetCurSel(0);
    m_comboRecordType.SetCurSel(0);
    return TRUE;
}

void CDlgCloudUploadstrategyCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCloudUploadstrategyCfg)
    DDX_Control(pDX, IDC_COMBO_STRATEGY_TYPE, m_comboStrategyType);
    DDX_Control(pDX, IDC_COMBO_RECORD_TYPE, m_comboRecordType);
    DDX_Check(pDX, IDC_CHK_ALLEVENT, m_bAllEvent);
    DDX_Check(pDX, IDC_CHK_MOTION, m_bMotion);
    DDX_Check(pDX, IDC_CHK_ALARM, m_bAlarm);
    DDX_Check(pDX, IDC_CHK_VCA, m_bVCA);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCloudUploadstrategyCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgCloudUploadstrategyCfg)
	ON_BN_CLICKED(IDC_BTN_GET_CLOUD_UPLOADSTRATEGY, OnBtnGetCloudUploadstrategy)
	ON_BN_CLICKED(IDC_BTN_SET_CLOUD_STRATEGY, OnBtnSetCloudStrategy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCloudUploadstrategyCfg message handlers

void CDlgCloudUploadstrategyCfg::OnBtnGetCloudUploadstrategy() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    
    m_struCloudUploadStrategyCond.dwSize = sizeof(m_struCloudUploadStrategyCond);
    m_struCloudUploadStrategyCond.dwChannel = 1;
    m_struCloudUploadStrategy.dwSize = sizeof(m_struCloudUploadStrategy);
    m_struStdConfig.lpInBuffer = NULL;
    m_struStdConfig.dwInSize = 0;
    m_struStdConfig.lpCondBuffer = (LPVOID)&m_struCloudUploadStrategyCond;
    m_struStdConfig.dwCondSize = sizeof(m_struCloudUploadStrategyCond);
    m_struStdConfig.lpOutBuffer = (LPVOID)&m_struCloudUploadStrategy;
    m_struStdConfig.dwOutSize = sizeof(m_struCloudUploadStrategy);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    m_struStdConfig.lpStatusBuffer = m_szStatusBuf;
    m_struStdConfig.dwStatusSize = ISAPI_STATUS_LEN;
    
    if (!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_CLOUD_UPLOADSTRATEGY, &m_struStdConfig))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_CLOUD_UPLOADSTRATEGY");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_CLOUD_UPLOADSTRATEGY");
    }
    m_comboStrategyType.SetCurSel(m_struCloudUploadStrategy.byStrategyType-1);
    //m_comboRecordType.SetCurSel(m_struCloudUploadStrategy.byRecordType);
    m_bAllEvent = m_struCloudUploadStrategy.dwRecordType & 0x01;
    m_bMotion = m_struCloudUploadStrategy.dwRecordType & 0x02;
    m_bAlarm = m_struCloudUploadStrategy.dwRecordType & 0x04;
    m_bVCA = m_struCloudUploadStrategy.dwRecordType & 0x08;
    
    UpdateData(FALSE);
}

void CDlgCloudUploadstrategyCfg::OnBtnSetCloudStrategy() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    memset(&m_struCloudUploadStrategy, 0, sizeof(m_struCloudUploadStrategy));
    m_struCloudUploadStrategyCond.dwSize = sizeof(m_struCloudUploadStrategyCond);
    m_struCloudUploadStrategyCond.dwChannel = 1;
    m_struCloudUploadStrategy.dwSize = sizeof(m_struCloudUploadStrategy);
    m_struCloudUploadStrategy.byStrategyType = m_comboStrategyType.GetCurSel()+1;
    //m_struCloudUploadStrategy.byRecordType = m_comboRecordType.GetCurSel();
    m_struCloudUploadStrategy.dwRecordType = m_struCloudUploadStrategy.dwRecordType | m_bAllEvent;
    m_struCloudUploadStrategy.dwRecordType = m_struCloudUploadStrategy.dwRecordType | (m_bMotion << 1);
    m_struCloudUploadStrategy.dwRecordType = m_struCloudUploadStrategy.dwRecordType | (m_bAlarm << 2);
    m_struCloudUploadStrategy.dwRecordType = m_struCloudUploadStrategy.dwRecordType | (m_bVCA << 3);
    m_struStdConfig.lpCondBuffer = (LPVOID)&m_struCloudUploadStrategyCond;
    m_struStdConfig.dwCondSize = sizeof(m_struCloudUploadStrategyCond);
    m_struStdConfig.lpInBuffer = (LPVOID)&m_struCloudUploadStrategy;
    m_struStdConfig.dwInSize = sizeof(m_struCloudUploadStrategy);
    m_struStdConfig.lpOutBuffer = NULL;
    m_struStdConfig.dwOutSize = 0;
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    m_struStdConfig.lpStatusBuffer = m_szStatusBuf;
    m_struStdConfig.dwStatusSize = ISAPI_STATUS_LEN;
    //m_struCloudUploadStrategy.dwRecordType = 0;
    if (!NET_DVR_SetSTDConfig(m_lUserID, NET_DVR_SET_CLOUD_UPLOADSTRATEGY, &m_struStdConfig))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_CLOUD_UPLOADSTRATEGY");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_CLOUD_UPLOADSTRATEGY");
    }
    
    UpdateData(FALSE);
}
