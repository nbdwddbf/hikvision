// DlgVideoOutResolutionCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVideoOutResolutionCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoOutResolutionCfg dialog


CDlgVideoOutResolutionCfg::CDlgVideoOutResolutionCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVideoOutResolutionCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVideoOutResolutionCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgVideoOutResolutionCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVideoOutResolutionCfg)
	DDX_Control(pDX, IDC_CMB_VIDEO_OUT_NO, m_cmbVideoOutNo);
	DDX_Control(pDX, IDC_CMB_RESOLUTION, m_cmbResulotion);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVideoOutResolutionCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVideoOutResolutionCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVideoOutResolutionCfg message handlers

void CDlgVideoOutResolutionCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

	LONG lChannel = m_cmbVideoOutNo.GetCurSel() + 1;
	
	char szLan[128] = {0};
	NET_DVR_VIDEOOUT_RESOLUTION_CFG struVideoOutResolutionCfg = {0};
	memset(&struVideoOutResolutionCfg, 0, sizeof(NET_DVR_VIDEOOUT_RESOLUTION_CFG));
	
	DWORD dwReturnedBytes = 0;
	
	if(NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_VIDEOOUT_RESOLUTION_CFG, lChannel, &struVideoOutResolutionCfg, sizeof(NET_DVR_VIDEOOUT_RESOLUTION_CFG), &dwReturnedBytes))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_VIDEOOUT_RESOLUTION_CFG");
		g_StringLanType(szLan, "获取设备本地视频输出口分辨率成功!", "Success to get device video out resolution");
		//	AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VIDEOOUT_RESOLUTION_CFG");
		g_StringLanType(szLan, "获取设备本地视频输出口分辨率失败!", "Fail to get device video out resolution");
		AfxMessageBox(szLan);
		return;
	}
	
	m_cmbResulotion.SetCurSel(struVideoOutResolutionCfg.byResolution);
	
	UpdateData(FALSE);
}

void CDlgVideoOutResolutionCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);

	LONG lChannel = m_cmbVideoOutNo.GetCurSel() + 1;
	
	char szLan[128] = {0};
	NET_DVR_VIDEOOUT_RESOLUTION_CFG struVideoOutResolutionCfg = {0};
	memset(&struVideoOutResolutionCfg, 0, sizeof(NET_DVR_VIDEOOUT_RESOLUTION_CFG));
	
	struVideoOutResolutionCfg.dwSize = sizeof(NET_DVR_VIDEOOUT_RESOLUTION_CFG);
	struVideoOutResolutionCfg.byResolution = m_cmbResulotion.GetCurSel();
	
	if(NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_VIDEOOUT_RESOLUTION_CFG, lChannel, &struVideoOutResolutionCfg, sizeof(NET_DVR_VIDEOOUT_RESOLUTION_CFG)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VIDEOOUT_RESOLUTION_CFG");
		g_StringLanType(szLan, "设置设备本地视频输出口分辨率成功!", "Success to set device video out resolution");
		//	AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VIDEOOUT_RESOLUTION_CFG");
		g_StringLanType(szLan, "设置设备本地视频输出口分辨率失败!", "Fail to set device video out resolution");
		AfxMessageBox(szLan);
		return;
	}
}

BOOL CDlgVideoOutResolutionCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_cmbVideoOutNo.SetCurSel(0);
	
	OnBtnGet();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
