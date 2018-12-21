// DlgStreamAttachInfoCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgStreamAttachInfoCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgStreamAttachInfoCfg dialog


CDlgStreamAttachInfoCfg::CDlgStreamAttachInfoCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStreamAttachInfoCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgStreamAttachInfoCfg)
	m_bStreamWithVca = FALSE;
	//}}AFX_DATA_INIT
	m_lServerID = -1;
	m_lChannel = -1;
	m_iDeviceIndex = -1;
}


void CDlgStreamAttachInfoCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgStreamAttachInfoCfg)
	DDX_Check(pDX, IDC_CHECK_STREAM_WITH_VCA, m_bStreamWithVca);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgStreamAttachInfoCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgStreamAttachInfoCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgStreamAttachInfoCfg message handlers
BOOL CDlgStreamAttachInfoCfg::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;
}

void CDlgStreamAttachInfoCfg::OnBtnGet() 
{  
	char szError[32] = "\0";
	if (!GetStreamAttachInfoCfg())
	{
        g_StringLanType(szError, "获取失败","Get failed");
		AfxMessageBox(szError);
	}
	else
	{
		UpdateData(FALSE);
	}
}

void CDlgStreamAttachInfoCfg::OnBtnSet() 
{   
	UpdateData(TRUE);

	char szError[32] = "\0";
	if (SetStreamAttachInfoCfg())
	{
        g_StringLanType(szError, "保存成功","Saved successfully");
	}
	else
	{
		g_StringLanType(szError, "保存失败","Save failed");
	}
	AfxMessageBox(szError);
}

BOOL CDlgStreamAttachInfoCfg::GetStreamAttachInfoCfg()
{   
	BOOL bRet      = FALSE;
	DWORD dwReturn = 0;
	
	NET_DVR_STREAM_ATTACHINFO_CFG struStreamAttachInfoCfg = {0};
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_STREAM_ATTACHINFO_CFG,m_lChannel,&struStreamAttachInfoCfg,
		sizeof(struStreamAttachInfoCfg),&dwReturn))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_STREAM_ATTACHINFO_CFG Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_STREAM_ATTACHINFO_CFG Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
	m_bStreamWithVca = struStreamAttachInfoCfg.byStreamWithVca;

	return bRet;
}

BOOL CDlgStreamAttachInfoCfg::SetStreamAttachInfoCfg()
{
	BOOL bRet      = FALSE;
	
	NET_DVR_STREAM_ATTACHINFO_CFG struStreamAttachInfoCfg = {0};
	struStreamAttachInfoCfg.dwSize = sizeof(struStreamAttachInfoCfg);
	struStreamAttachInfoCfg.byStreamWithVca = m_bStreamWithVca;

    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_STREAM_ATTACHINFO_CFG,m_lChannel,&struStreamAttachInfoCfg,
		sizeof(struStreamAttachInfoCfg)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_STREAM_ATTACHINFO_CFG Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_STREAM_ATTACHINFO_CFG Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
	return bRet;
}