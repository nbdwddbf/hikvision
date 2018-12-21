// DlgRecordStatus.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRecordStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordStatus dialog


CDlgRecordStatus::CDlgRecordStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRecordStatus::IDD, pParent)
    , m_iRecordingTime(0)
{
	//{{AFX_DATA_INIT(CDlgRecordStatus)
	m_dwChannel = 0;
	m_byRecUUID = _T("");
	//}}AFX_DATA_INIT
	m_lUserID = 0;
	m_iDeviceIndex = 0;
	m_iStartChannel = 0;
}


void CDlgRecordStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRecordStatus)
	DDX_Control(pDX, IDC_COM_RECORD_STATUS, m_comRecordStatus);
	DDX_Text(pDX, IDC_EDIT_UUID, m_byRecUUID);
	//}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_RECORDING_TIME, m_iRecordingTime);
}


BEGIN_MESSAGE_MAP(CDlgRecordStatus, CDialog)
	//{{AFX_MSG_MAP(CDlgRecordStatus)
	ON_BN_CLICKED(IDC_BTN_QUERY, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRecordStatus message handlers

void CDlgRecordStatus::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_RECORD_STATUS struRecordStatus = {0};

    DWORD dwChannel = 0;
 //   dwChannel = m_dwChannel;
    NET_DVR_STD_CONFIG struCfg = {0};
    struCfg.lpCondBuffer = NULL;
    struCfg.dwCondSize = 0;
    struCfg.lpOutBuffer = &struRecordStatus;
    struCfg.dwOutSize = sizeof(struRecordStatus);
    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;
    if(!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_RECORD_STATUS, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_RECORD_STATUS");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_RECORD_STATUS");
    }

	m_comRecordStatus.SetCurSel(struRecordStatus.byRecordStatus);
    m_byRecUUID.Format("%s",struRecordStatus.byRecUUID);
    m_iRecordingTime = struRecordStatus.dwRecordingTime;
    
    UpdateData(FALSE);
}
