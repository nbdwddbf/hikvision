// DlgVcaSceneTrafficCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaSceneTrafficCfg.h"
#include "DlgVcaSceneCfg.h"
#include "DlgSceneTimeCfg.h"
#include "DlgVcaSceneLaneCfg.h"
#include "DlgVcaSceneITSCalibrate.h"
#include "DlgVcaSceneAidRuleCfg.h"
#include "DlgVcaSceneTpsRuleCfg.h"
#include "DlgVcaForensicsModeCfg.h"
#include "DlgVcaSceneRegionList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSceneTrafficCfg dialog


CDlgVcaSceneTrafficCfg::CDlgVcaSceneTrafficCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaSceneTrafficCfg::IDD, pParent)
{
	m_iDevIndex      = -1;
    m_lServerID      = -1;
    m_iStartChannel  = -1;
    m_iChannelnumber = -1;
    m_iVcaChannel    = -1;
}


void CDlgVcaSceneTrafficCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgVcaSceneTrafficCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaSceneTrafficCfg)
	ON_BN_CLICKED(IDC_BTN_SCENE_CFG,       OnBtnSceneCfg)
	ON_BN_CLICKED(IDC_BTN_SCENE_TIME_CFG,  OnBtnSceneTimeCfg)
	ON_BN_CLICKED(IDC_BTN_MASK_REGION, OnBtnMaskRegion)
	ON_BN_CLICKED(IDC_BTN_REFERENCE_REGION, OnBtnReferenceRegion)
	ON_BN_CLICKED(IDC_BTN_LANECFG,OnBtnLanecfg)
	ON_BN_CLICKED(IDC_BTN_ITS_CALIBRATE,OnBtnItsCalibrate)
	ON_BN_CLICKED(IDC_BTN_AID_RULECFG, OnBtnAidRulecfg)
	ON_BN_CLICKED(IDC_BTN_TPS_RULECFG, OnBtnTpsRulecfg)
	ON_BN_CLICKED(IDC_BTN_FORENSICS_MODE, OnBtnForensicsMode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSceneTrafficCfg message handlers

BOOL CDlgVcaSceneTrafficCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;
}





void CDlgVcaSceneTrafficCfg::OnBtnSceneCfg() 
{
	CDlgVcaSceneCfg dlgVcaSceneCfg;
	dlgVcaSceneCfg.m_lServerID = m_lServerID;
    dlgVcaSceneCfg.m_iDevIndex = m_iDevIndex;
    dlgVcaSceneCfg.m_lChannel  = m_iVcaChannel;
	dlgVcaSceneCfg.DoModal();
	
}

void CDlgVcaSceneTrafficCfg::OnBtnSceneTimeCfg()
{
	CDlgSceneTimeCfg dlgSceneTimeCfg;
	dlgSceneTimeCfg.m_lServerID = m_lServerID;
	dlgSceneTimeCfg.m_iDevIndex = m_iDevIndex;
    dlgSceneTimeCfg.m_lChannel  = m_iVcaChannel;
	dlgSceneTimeCfg.DoModal();
}



void CDlgVcaSceneTrafficCfg::OnBtnMaskRegion() 
{
	CDlgVcaSceneRegionList dlg(CDlgVcaSceneRegionList::REGIONLIST_TYPE_MASK);
	dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.m_lServerID = m_lServerID;
    dlg.DoModal();
}

void CDlgVcaSceneTrafficCfg::OnBtnReferenceRegion() 
{
	CDlgVcaSceneRegionList dlg(CDlgVcaSceneRegionList::REGIONLIST_TYPE_REFERENCE);
	dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.m_lServerID = m_lServerID;
    dlg.DoModal();
}



void CDlgVcaSceneTrafficCfg::OnBtnLanecfg()
{
	CDlgVcaSceneLaneCfg dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel  = m_iVcaChannel;
    dlg.DoModal();
}

void CDlgVcaSceneTrafficCfg::OnBtnItsCalibrate()
{
	CDlgVcaSceneITSCalibrate dlg;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel   = m_iVcaChannel;
    dlg.m_lServerID = m_lServerID;
    dlg.DoModal();
}

void CDlgVcaSceneTrafficCfg::OnBtnAidRulecfg() 
{
	CDlgVcaSceneAidRuleCfg dlg;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel   = m_iVcaChannel;
    dlg.m_lServerID = m_lServerID;
    dlg.DoModal();
}

void CDlgVcaSceneTrafficCfg::OnBtnTpsRulecfg() 
{
	CDlgVcaSceneTpsRuleCfg dlg;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel  = m_iVcaChannel;
    dlg.m_lServerID = m_lServerID;
    dlg.DoModal();
}

void CDlgVcaSceneTrafficCfg::OnBtnForensicsMode() 
{
	CDlgVcaForensicsModeCfg dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.DoModal();
}
