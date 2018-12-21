// DlgDelayPreviewCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgDelayPreviewCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDelayPreviewCfg dialog


CDlgDelayPreviewCfg::CDlgDelayPreviewCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDelayPreviewCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDelayPreviewCfg)
	m_iDelayTime = 0;
	//}}AFX_DATA_INIT
}


void CDlgDelayPreviewCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDelayPreviewCfg)
	DDX_Text(pDX, IDC_EDT_DELAY_TIME, m_iDelayTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDelayPreviewCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgDelayPreviewCfg)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDelayPreviewCfg message handlers

void CDlgDelayPreviewCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);
	
	char szLan[128] = {0};
	
	NET_DVR_PREVIEW_DELAY_CFG struDelayPreviewCfg = {0};
	struDelayPreviewCfg.dwSize = sizeof(NET_DVR_PREVIEW_DELAY_CFG);
	struDelayPreviewCfg.wdelayTime = (WORD)m_iDelayTime;
	
	if(!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_PREVIEW_DELAY_CFG, m_lChannel, &struDelayPreviewCfg, sizeof(NET_DVR_PREVIEW_DELAY_CFG)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_PREVIEW_DELAY_TIME_CFG");
		sprintf(szLan,"NET_DVR_SET_PREVIEW_DELAY_TIME_CFG failed[%d]", NET_DVR_GetLastError());
		AfxMessageBox(szLan);
	}
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PREVIEW_DELAY_TIME_CFG");
    }
}

BOOL CDlgDelayPreviewCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	OnBtnGet();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgDelayPreviewCfg::OnBtnGet()
{
	char szLan[128] = {0};
	DWORD dwBytesReturned = -1;
	
	NET_DVR_PREVIEW_DELAY_CFG struDelayPreviewCfg = {0};
	struDelayPreviewCfg.dwSize = sizeof(NET_DVR_PREVIEW_DELAY_CFG);
	
	if(!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_PREVIEW_DELAY_CFG, m_lChannel, &struDelayPreviewCfg, sizeof(NET_DVR_PREVIEW_DELAY_CFG), &dwBytesReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PREVIEW_DELAY_TIME_CFG");
		sprintf(szLan,"NET_DVR_GET_PREVIEW_DELAY_TIME_CFG failed[%d]", NET_DVR_GetLastError());
		AfxMessageBox(szLan);
		return;
	}
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_PREVIEW_DELAY_TIME_CFG");
    }
	
	m_iDelayTime = (DWORD)struDelayPreviewCfg.wdelayTime;
	
	UpdateData(FALSE);
}