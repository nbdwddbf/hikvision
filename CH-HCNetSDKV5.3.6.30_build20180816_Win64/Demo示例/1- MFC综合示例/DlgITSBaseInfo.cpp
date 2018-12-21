// DlgITSBaseInfo.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgITSBaseInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgITSBaseInfo dialog


CDlgITSBaseInfo::CDlgITSBaseInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgITSBaseInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgITSBaseInfo)
	m_csMainVersion = _T("");
	m_csBvtVersion = _T("");
	m_csLptVersion = _T("");
	m_csMprVersion = _T("");
	m_csTldVersion = _T("");
	m_csTvdVersion = _T("");
	//}}AFX_DATA_INIT
	m_lServerID = -1;
    m_iDevIndex = -1;
	m_lChannel = -1;
	memset(&m_struBaseInfo, 0, sizeof(m_struBaseInfo));
}


void CDlgITSBaseInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgITSBaseInfo)
	DDX_Text(pDX, IDC_EDIT_MAIN_VERSION, m_csMainVersion);
	DDX_Text(pDX, IDC_EDIT_BVT_VERSION, m_csBvtVersion);
	DDX_Text(pDX, IDC_EDIT_LPT_VERSION, m_csLptVersion);
	DDX_Text(pDX, IDC_EDIT_MPR_VERSION, m_csMprVersion);
	DDX_Text(pDX, IDC_EDIT_TLD_VERSION, m_csTldVersion);
	DDX_Text(pDX, IDC_EDIT_TVD_VERSION, m_csTvdVersion);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgITSBaseInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgITSBaseInfo)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgITSBaseInfo message handlers

void CDlgITSBaseInfo::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	memset(&m_struBaseInfo, 0, sizeof(m_struBaseInfo));
	DWORD dwReturn = 0;
	char szLan[33] = {0};
	if (NET_DVR_GetDVRConfig(m_lServerID, NET_ITS_GET_BASE_INFO, m_lChannel, &m_struBaseInfo, sizeof(m_struBaseInfo), &dwReturn))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_ITS_GET_BASE_INFO");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_ITS_GET_BASE_INFO");
	}
	memcpy(szLan,m_struBaseInfo.byMainVer,VERSION_LEN);
	m_csMainVersion.Format("%s", szLan);
	memset(szLan,0,VERSION_LEN);
	memcpy(szLan,m_struBaseInfo.byMprVer,VERSION_LEN);
	m_csMprVersion.Format("%s", szLan);
	memset(szLan,0,VERSION_LEN);
	memcpy(szLan,m_struBaseInfo.byBvtVer,VERSION_LEN);
	m_csBvtVersion.Format("%s", szLan);
	memset(szLan,0,VERSION_LEN);
	memcpy(szLan,m_struBaseInfo.byLptVer,VERSION_LEN);
	m_csLptVersion.Format("%s", szLan);
	memset(szLan,0,VERSION_LEN);
	memcpy(szLan,m_struBaseInfo.byTvdVer,VERSION_LEN);
	m_csTvdVersion.Format("%s", szLan);
	memset(szLan,0,VERSION_LEN);
	memcpy(szLan,m_struBaseInfo.byTldVer,VERSION_LEN);
	m_csTldVersion.Format("%s", szLan);
	UpdateData(FALSE);
}
