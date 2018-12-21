// DlgRecordHostRTMPCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRecordHostRTMPCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordHostRTMPCfg dialog


CDlgRecordHostRTMPCfg::CDlgRecordHostRTMPCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRecordHostRTMPCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRecordHostRTMPCfg)
		// NOTE: the ClassWizard will add member initialization here
	m_bEnRTMP = FALSE;
    m_dwPacketLen = 0;
    m_lChannel    = 0L;
    memset(&m_struRTMPCfg, 0, sizeof(m_struRTMPCfg));
	//}}AFX_DATA_INIT
}


void CDlgRecordHostRTMPCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRecordHostRTMPCfg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_COM_CHANNEL, m_comChannel);
    DDX_Control(pDX, IDC_COM_STREAM_TYPE, m_comStreamType);
    DDX_Check(pDX, IDC_CHK_ENRTMP, m_bEnRTMP);
    DDX_Text(pDX, IDC_EDT_RTMP_PACK_LEN, m_dwPacketLen);
    DDX_Text(pDX, IDC_EDT_RTMP_URL, m_strRTMPURL);
    DDX_Text(pDX, IDC_COM_CHANNEL, m_lChannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRecordHostRTMPCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgRecordHostRTMPCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CDlgRecordHostRTMPCfg::OnInitDialog()
{
    CDialog::OnInitDialog();

    //m_comChannel.InsertStream(0, _T(""));
    //m_comChannel.SetCurSel(0);

    m_comStreamType.InsertString(0, _T("1-主码流"));
    m_comStreamType.InsertString(1, _T("2-子码流"));
    m_comStreamType.InsertString(2, _T("3-码流三"));
    m_comStreamType.SetCurSel(0);

    UpdateData(FALSE);
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordHostRTMPCfg message handlers

void CDlgRecordHostRTMPCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    NET_DVR_RTMP_COND struRTMPCond = {0};
    struRTMPCond.dwChannel = m_lChannel;//FIXME
    struRTMPCond.byStreamType = m_comStreamType.GetCurSel()+1;

    NET_DVR_STD_CONFIG struSTDConfig = {0};
    
    struSTDConfig.lpCondBuffer = &struRTMPCond;
    struSTDConfig.dwCondSize = sizeof(struRTMPCond);
    struSTDConfig.lpOutBuffer = &m_struRTMPCfg;
    struSTDConfig.dwOutSize = sizeof(m_struRTMPCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struSTDConfig.lpStatusBuffer = m_szStatusBuf;
    struSTDConfig.dwStatusSize = ISAPI_STATUS_LEN; 


    if (NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_RTMP_CFG, &struSTDConfig))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_RTMP_CFG");
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_RTMP_CFG");
    }

    m_bEnRTMP = (BOOL)m_struRTMPCfg.byEnable;
    m_dwPacketLen = m_struRTMPCfg.dwPacketLen;
    m_strRTMPURL  = m_struRTMPCfg.szURL;

    UpdateData(FALSE);
}

void CDlgRecordHostRTMPCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_struRTMPCfg.dwSize = sizeof(m_struRTMPCfg);
    m_struRTMPCfg.byEnable = m_bEnRTMP;
    m_struRTMPCfg.dwPacketLen = m_dwPacketLen;
    strncpy(m_struRTMPCfg.szURL, m_strRTMPURL.GetBuffer(m_strRTMPURL.GetLength()), RTMP_URL_LEN);

    NET_DVR_RTMP_COND struRTMPCond = {0};
    struRTMPCond.dwChannel = m_lChannel;
    struRTMPCond.byStreamType = m_comStreamType.GetCurSel()+1;

    NET_DVR_STD_CONFIG struSTDConfig = {0};
    struSTDConfig.lpCondBuffer = &struRTMPCond;
    struSTDConfig.dwCondSize = sizeof(struRTMPCond);
    struSTDConfig.lpInBuffer = &m_struRTMPCfg;
    struSTDConfig.dwInSize = sizeof(m_struRTMPCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struSTDConfig.lpStatusBuffer = m_szStatusBuf;
    struSTDConfig.dwStatusSize = ISAPI_STATUS_LEN;

    if (NET_DVR_SetSTDConfig(m_lUserID, NET_DVR_SET_RTMP_CFG, &struSTDConfig))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_RTMP_CFG");
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_RTMP_CFG");
    }
}
