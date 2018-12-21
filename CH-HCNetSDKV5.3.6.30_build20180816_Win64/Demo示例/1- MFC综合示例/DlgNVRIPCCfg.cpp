// DlgNVRIPCCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgNVRIPCCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNVRIPCCfg dialog


CDlgNVRIPCCfg::CDlgNVRIPCCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNVRIPCCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNVRIPCCfg)
	m_bEnableCorridor = FALSE;
    m_iDevIndex = -1;
    m_lChannel = 0;
    m_lUserID = -1;
    memset(&m_struCorridorMode, 0,sizeof(m_struCorridorMode));
	//}}AFX_DATA_INIT
}


void CDlgNVRIPCCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNVRIPCCfg)
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cmbChannel);
	DDX_Control(pDX, IDC_COMBO_MIRROR_MODE, m_cmbMirrorMode);
	DDX_Check(pDX, IDC_CHECK_CORRIDOR_MODE, m_bEnableCorridor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNVRIPCCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgNVRIPCCfg)
	ON_BN_CLICKED(IDC_BTN_SET_CORRIDOR_MODE, OnBtnSetCorridorMode)
    ON_BN_CLICKED(IDC_BTN_GET_CORRIDOR_MODE, OnBtnGetCorridorMode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNVRIPCCfg message handlers

void CDlgNVRIPCCfg::OnBtnSetCorridorMode() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    m_struCorridorMode.dwSize = sizeof(m_struCorridorMode);
    m_struCorridorMode.byEnableCorridorMode = m_bEnableCorridor;
    m_struCorridorMode.byMirrorMode = m_cmbMirrorMode.GetCurSel();
    
    if (!NET_DVR_SetDVRConfig(g_struDeviceInfo[m_iDevIndex].lLoginID, NET_DVR_SET_CORRIDOR_MODE, m_lChannel, &m_struCorridorMode, sizeof(m_struCorridorMode)))
    {
        g_pMainDlg->AddLog(g_struDeviceInfo[m_iDevIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_SET_CORRIDOR_MODE");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(g_struDeviceInfo[m_iDevIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_SET_CORRIDOR_MODE");
	}
    
}

void CDlgNVRIPCCfg::OnBtnGetCorridorMode()
{
    UpdateData(TRUE);
    DWORD dwReturn = 0;
    memset(&m_struCorridorMode, 0, sizeof(m_struCorridorMode));
    m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_iDevIndex].lLoginID, NET_DVR_GET_CORRIDOR_MODE, m_lChannel, &m_struCorridorMode, sizeof(m_struCorridorMode), &dwReturn))
    {
        g_pMainDlg->AddLog(g_struDeviceInfo[m_iDevIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_GET_CORRIDOR_MODE");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(g_struDeviceInfo[m_iDevIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_GET_CORRIDOR_MODE");
    }
    m_bEnableCorridor = m_struCorridorMode.byEnableCorridorMode;
    m_cmbMirrorMode.SetCurSel(m_struCorridorMode.byMirrorMode);

	UpdateData(FALSE);
}

BOOL CDlgNVRIPCCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here



    g_AddChanInfoToComBox(m_cmbChannel, m_iDevIndex,TRUE);
    m_cmbMirrorMode.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
