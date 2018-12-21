// DlgNetraHttps.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgNetraHttps.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNetraHttps dialog


CDlgNetraHttps::CDlgNetraHttps(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNetraHttps::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNetraHttps)
	m_wHttpsPort = 0;
	m_bHttps = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgNetraHttps::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNetraHttps)
	DDX_Text(pDX, IDC_EDIT_HTTPSPORT, m_wHttpsPort);
	DDX_Check(pDX, IDC_CHECK_HTTPS, m_bHttps);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNetraHttps, CDialog)
	//{{AFX_MSG_MAP(CDlgNetraHttps)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNetraHttps message handlers

void CDlgNetraHttps::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_HTTPS_CFG struHttpsInfo;
	memset(&struHttpsInfo, 0, sizeof(NET_DVR_HTTPS_CFG));

	struHttpsInfo.dwSize = sizeof(NET_DVR_HTTPS_CFG);
	struHttpsInfo.byEnable = m_bHttps;
	struHttpsInfo.wHttpsPort = m_wHttpsPort;

	if (!NET_DVR_SetDVRConfig(m_lUserId, NET_DVR_SET_HTTPS_CFG, 0, &(struHttpsInfo), sizeof(NET_DVR_HTTPS_CFG)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_HTTPS_CFG");
		AfxMessageBox("NET_DVR_SET_HTTPS_CFG failed");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_HTTPS_CFG");
	}
}

void CDlgNetraHttps::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturned = 0;
	NET_DVR_HTTPS_CFG struHttpsInfo;
	memset(&struHttpsInfo, 0, sizeof(NET_DVR_HTTPS_CFG));

	if (!NET_DVR_GetDVRConfig(m_lUserId, NET_DVR_GET_HTTPS_CFG, 0, &struHttpsInfo, sizeof(NET_DVR_HTTPS_CFG), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_HTTPS_CFG");
		AfxMessageBox("NET_DVR_GET_HTTPS_CFG failed");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_HTTPS_CFG");
	}

	m_bHttps = struHttpsInfo.byEnable;
	m_wHttpsPort = struHttpsInfo.wHttpsPort;
	UpdateData(FALSE);
	
}
