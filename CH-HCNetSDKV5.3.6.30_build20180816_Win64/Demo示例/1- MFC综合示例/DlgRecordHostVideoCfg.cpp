// DlgRecordHostVideoCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRecordHostVideoCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordHostVideoCfg dialog


CDlgRecordHostVideoCfg::CDlgRecordHostVideoCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRecordHostVideoCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRecordHostVideoCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgRecordHostVideoCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRecordHostVideoCfg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_COM_EXPORT_TYPE, m_comExportType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRecordHostVideoCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgRecordHostVideoCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgRecordHostVideoCfg::OnInitDialog()
{
    CDialog::OnInitDialog();
	
    m_comExportType.InsertString(0, _T("0-MP4"));
	m_comExportType.InsertString(1, _T("1-AVI"));
	m_comExportType.SetCurSel(0);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordHostVideoCfg message handlers

void CDlgRecordHostVideoCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_RECORD_VIDEO_CFG struVideoCfg = {0};
    struVideoCfg.dwSize = sizeof(struVideoCfg);

    NET_DVR_STD_CONFIG struSTDConfig = {0};
    struSTDConfig.lpCondBuffer = NULL;
    struSTDConfig.dwCondSize = 0;
    struSTDConfig.lpOutBuffer = &struVideoCfg;
    struSTDConfig.dwOutSize = sizeof(struVideoCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struSTDConfig.lpStatusBuffer = m_szStatusBuf;
    struSTDConfig.dwStatusSize = ISAPI_STATUS_LEN;

    if (NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_RECORD_VIDEO_CFG, &struSTDConfig))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_RECORD_VIDEO_CFG");
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_RECORD_VIDEO_CFG");
    }

    m_comExportType.SetCurSel(struVideoCfg.byExportType);
}

void CDlgRecordHostVideoCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	
	NET_DVR_RECORD_VIDEO_CFG struVideoCfg = {0};
    struVideoCfg.dwSize = sizeof(struVideoCfg);
    struVideoCfg.byExportType = m_comExportType.GetCurSel();

    NET_DVR_STD_CONFIG struSTDConfig = {0};
    struSTDConfig.lpCondBuffer = NULL;
    struSTDConfig.dwCondSize = 0;
    struSTDConfig.lpInBuffer = &struVideoCfg;
    struSTDConfig.dwInSize = sizeof(struVideoCfg);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struSTDConfig.lpStatusBuffer = m_szStatusBuf;
    struSTDConfig.dwStatusSize = ISAPI_STATUS_LEN;

    if (NET_DVR_SetSTDConfig(m_lUserID, NET_DVR_SET_RECORD_VIDEO_CFG, &struSTDConfig))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_RECORD_VIDEO_CFG");
    }
    else
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_RECORD_VIDEO_CFG");
    }
}
