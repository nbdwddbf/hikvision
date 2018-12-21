// DlgVcaITSCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaITSCfg.h"
#include "DlgVcaLaneCfg.h"
#include "DlgRegionList.h"
#include "DlgTPSRuleCfg.h"
#include "DlgVcaAidRuleCfg.h"
#include "DlgVcaITSCalibrate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "DlgVcaDrawMode.h"
#include "DlgVcaITCTriggerCfg.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaITSCfg dialog


CDlgVcaITSCfg::CDlgVcaITSCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaITSCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaITSCfg)
	//}}AFX_DATA_INIT
    m_iDevIndex = -1;
    m_lServerID = -1;
    m_iVcaChannel = -1;
    m_dwSceneMode = 0;
}


void CDlgVcaITSCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaITSCfg)
	DDX_Control(pDX, IDC_COMBO_SCENE_MODE, m_comboSceneMode);
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CDlgVcaITSCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaITSCfg)
	ON_BN_CLICKED(IDC_BTN_MASK_REGION, OnBtnMaskRegion)
	ON_BN_CLICKED(IDC_BTN_REFERENCE_REGION, OnBtnReferenceRegion)
	ON_BN_CLICKED(IDC_BTN_LANECFG, OnBtnLanecfg)
	ON_BN_CLICKED(IDC_BTN_AID_RULECFG, OnBtnAidRulecfg)
	ON_BN_CLICKED(IDC_BTN_TPS_RULECFG, OnBtnTpsRulecfg)
	ON_BN_CLICKED(IDC_BTN_ITS_CALIBRATE, OnBtnItsCalibrate)
	ON_BN_CLICKED(IDC_BTN_SET_SCENE_MODE, OnBtnSetSceneMode)
	ON_BN_CLICKED(IDC_BTN_ITC_TRIGGERCFG, OnBtnItcTriggerCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaITSCfg message handlers

BOOL CDlgVcaITSCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
    InitWnd();
    
    GetSceneMode();
    SetSceneModeToWnd();
    UpdateData(FALSE);
	
	return TRUE; 
}

void CDlgVcaITSCfg::InitWnd()
{
    char szLan[128] = {0};
    m_comboSceneMode.ResetContent();
    g_StringLanType(szLan, "普通高速公路", "Freeway");
    m_comboSceneMode.AddString(szLan);
    
    g_StringLanType(szLan, "高速隧道场景", "Tunnel");
    m_comboSceneMode.AddString(szLan);

    g_StringLanType(szLan, "高速桥梁场景", "Bridge");
    m_comboSceneMode.AddString(szLan);
}

BOOL CDlgVcaITSCfg::GetSceneMode()
{
    if (!NET_DVR_GetSceneMode(m_lServerID, m_iVcaChannel, &m_dwSceneMode))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetSceneMode Chan[%d]", m_iVcaChannel);
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetSceneMode Chan[%d]", m_iVcaChannel);
        return TRUE;
    }
}

BOOL CDlgVcaITSCfg::SetSceneMode()
{
    if (!NET_DVR_SetSceneMode(m_lServerID, m_iVcaChannel, m_dwSceneMode))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SetSceneMode Chan[%d]", m_iVcaChannel);
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SetSceneMode Chan[%d]", m_iVcaChannel);
        return TRUE;
    }
}

void CDlgVcaITSCfg::SetSceneModeToWnd()
{
    m_comboSceneMode.SetCurSel(m_dwSceneMode);
}

void CDlgVcaITSCfg::GetSceneModeFromWnd()
{
    m_dwSceneMode = m_comboSceneMode.GetCurSel();
}


void CDlgVcaITSCfg::OnBtnMaskRegion() 
{
    CDlgRegionList dlg;
    dlg.m_dwRegionType = MASK_REGION;
    dlg.m_lServerID = m_lServerID;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVcaITSCfg::OnBtnReferenceRegion() 
{
    CDlgRegionList dlg;
    dlg.m_dwRegionType = REFERENCE_REGION;
    dlg.m_lServerID = m_lServerID;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVcaITSCfg::OnBtnLanecfg() 
{
    CDlgVcaLaneCfg dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.DoModal();
}
void CDlgVcaITSCfg::OnBtnAidRulecfg() 
{
    CDlgVcaAidRuleCfg dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.DoModal();
}

void CDlgVcaITSCfg::OnBtnTpsRulecfg() 
{
    CDlgTPSRuleCfg dlg;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lServerID = m_lServerID;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.DoModal();
}

void CDlgVcaITSCfg::OnBtnItsCalibrate() 
{
    CDlgVcaITSCalibrate dlg;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.m_lServerID = m_lServerID;
    dlg.DoModal();

}

void CDlgVcaITSCfg::OnBtnSetSceneMode() 
{
    GetSceneModeFromWnd();
    if (SetSceneMode())
    {
        AfxMessageBox("Succ set scene mode") ;       
    }
    else
    {
        AfxMessageBox("Fail to set scene mode");
    }
}


void CDlgVcaITSCfg::OnBtnItcTriggerCfg() 
{
	CDlgVcaITCTriggerCfg dlg;
	dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.DoModal();
}
