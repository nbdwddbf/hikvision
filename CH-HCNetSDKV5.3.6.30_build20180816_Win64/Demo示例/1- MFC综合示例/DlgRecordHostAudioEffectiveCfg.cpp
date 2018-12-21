// DlgRecordHostAudioEffectiveCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRecordHostAudioEffectiveCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordHostAudioEffectiveCfg dialog


CDlgRecordHostAudioEffectiveCfg::CDlgRecordHostAudioEffectiveCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRecordHostAudioEffectiveCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRecordHostAudioEffectiveCfg)
		// NOTE: the ClassWizard will add member initialization here

    m_lAudioChan = 1;
	m_dwCheckDelay = 0;
	m_byThreshold = 0;
	m_byVolumePercent = 0;
	m_byPriority = 0;
	memset(&m_struAudioEffectiveCfg, 0, sizeof(m_struAudioEffectiveCfg));
	//}}AFX_DATA_INIT
}


void CDlgRecordHostAudioEffectiveCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRecordHostAudioEffectiveCfg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
    DDX_Control(pDX, IDC_COM_AUDIO_CHAN, m_comAudioChan);
    DDX_Text(pDX, IDC_COM_AUDIO_CHAN, m_lAudioChan);
	DDX_Text(pDX, IDC_EDT_CHECKDELAY, m_dwCheckDelay);
    DDX_Text(pDX, IDC_EDT_THRESHOLD, m_byThreshold);
    DDX_Text(pDX, IDC_EDT_VOLUME, m_byVolumePercent);
    DDX_Text(pDX, IDC_EDT_PRIORITY, m_byPriority);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRecordHostAudioEffectiveCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgRecordHostAudioEffectiveCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CDlgRecordHostAudioEffectiveCfg::OnInitDialog()
{
    CDialog::OnInitDialog();

    //m_comAudioChan.InsertString(0, _T("0"));
	m_comAudioChan.InsertString(0, _T("1"));
    m_comAudioChan.InsertString(1, _T("2"));
    m_comAudioChan.InsertString(2, _T("3"));
    m_comAudioChan.InsertString(3, _T("4"));
    m_comAudioChan.InsertString(4, _T("5"));
    m_comAudioChan.InsertString(5, _T("6"));
    m_comAudioChan.InsertString(6, _T("7"));
    m_comAudioChan.InsertString(7, _T("8"));

	m_comAudioChan.SetCurSel(0);

    m_lAudioChan = 1;

    UpdateData(FALSE);

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordHostAudioEffectiveCfg message handlers

void CDlgRecordHostAudioEffectiveCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    
    NET_DVR_STD_CONFIG struSTDConfig = {0};
    struSTDConfig.lpCondBuffer = &m_lAudioChan;
    struSTDConfig.dwCondSize = sizeof(m_lAudioChan);
    struSTDConfig.lpOutBuffer = &m_struAudioEffectiveCfg;
    struSTDConfig.dwOutSize = sizeof(m_struAudioEffectiveCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struSTDConfig.lpStatusBuffer = m_szStatusBuf;
    struSTDConfig.dwStatusSize = ISAPI_STATUS_LEN;


    if (NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_AUDIO_EFFECTIVE_CFG, &struSTDConfig))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_AUDIO_EFFECTIVE_CFG");
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_AUDIO_EFFECTIVE_CFG");
    }

    m_dwCheckDelay = m_struAudioEffectiveCfg.dwCheckDelay;
    m_byThreshold  = m_struAudioEffectiveCfg.byThreshold;
    m_byVolumePercent = m_struAudioEffectiveCfg.byVolumePercent;
    m_byPriority = m_struAudioEffectiveCfg.byPriority;

    UpdateData(FALSE);
}

void CDlgRecordHostAudioEffectiveCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_struAudioEffectiveCfg.dwSize = sizeof(m_struAudioEffectiveCfg);

    m_struAudioEffectiveCfg.dwCheckDelay = m_dwCheckDelay;
    m_struAudioEffectiveCfg.byThreshold = m_byThreshold;
    m_struAudioEffectiveCfg.byVolumePercent = m_byVolumePercent;
    m_struAudioEffectiveCfg.byPriority = m_byPriority;

    NET_DVR_STD_CONFIG struSTDConfig = {0};
    struSTDConfig.lpCondBuffer = &m_lAudioChan;
    struSTDConfig.dwCondSize = sizeof(m_lAudioChan);
    struSTDConfig.lpInBuffer = &m_struAudioEffectiveCfg;
    struSTDConfig.dwInSize = sizeof(m_struAudioEffectiveCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struSTDConfig.lpStatusBuffer = m_szStatusBuf;
    struSTDConfig.dwStatusSize = ISAPI_STATUS_LEN;

    if (NET_DVR_SetSTDConfig(m_lUserID, NET_DVR_SET_AUDIO_EFFECTIVE_CFG, &struSTDConfig))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_AUDIO_EFFECTIVE_CFG");
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_AUDIO_EFFECTIVE_CFG");
    }
	
}
