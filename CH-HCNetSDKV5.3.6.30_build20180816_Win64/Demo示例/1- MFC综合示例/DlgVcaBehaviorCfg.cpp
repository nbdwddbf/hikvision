// DlgVcaBehaviorCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaBehaviorCfg.h"
#include "DlgVcaDrawMode.h"
#include "DlgVcaLF.h"
#include "DlgVcaRuleCfg.h"
#include "DlgVcaBehaviorCalibrate.h"
#include "DlgvcaMaskRegion.h"
#include "DlgVcaEnterRegion.h"
#include "DlgSizeFilter.h"
#include "DlgVcaFaceDetect.h"
#include "DlgVcaWorkStatus.h"
#include "DlgVcaFaceSnapCfg.h"
#include "DlgVcaObjectColor.h"
#include "DlgVcaAuxAreaList.h"
#include "DlgVcaChannelWorkMode.h"
#include "DlgVcaBaselineScene.h"
#include "DlgVcaVQDEventRule.h"
#include "DlgVcaVQDAlarmPic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaBehaviorCfg dialog


CDlgVcaBehaviorCfg::CDlgVcaBehaviorCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaBehaviorCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaBehaviorCfg)
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    m_iChannelNum = -1;
    m_iVcaChannel = -1;
}


void CDlgVcaBehaviorCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaBehaviorCfg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaBehaviorCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaBehaviorCfg)
	ON_BN_CLICKED(IDC_BTN_MASK_REGION, OnBtnMaskRegion)
	ON_BN_CLICKED(IDC_BTN_ENTER_REGION2, OnBtnEnterRegion2)
	ON_BN_CLICKED(IDC_BTN_LF_CFG, OnBtnLfCfg)
	ON_BN_CLICKED(IDC_BTN_SET_RULECFG, OnBtnSetRulecfg)
	ON_BN_CLICKED(IDC_BTN_BEHAVIOR_CALIBRATE, OnBtnBehaviorCalibrate)
	ON_BN_CLICKED(IDC_BTN_SIZE_FILTER, OnBtnSizeFilter)
	ON_BN_CLICKED(IDC_BTN_FACE_DETECT, OnBtnFaceDetect)
	ON_BN_CLICKED(IDC_BTN_VCA_WORK_STATUS, OnBtnVcaWorkStatus)
	ON_BN_CLICKED(IDC_BTN_OBJECT_COLOR, OnBtnObjectColor)
	ON_BN_CLICKED(IDC_BTN_AUXAREA, OnBtnAuxArea)
	ON_BN_CLICKED(IDC_BTN_CHANNEL_WORKMODE, OnBtnChannelWorkMode)
	ON_BN_CLICKED(IDC_BTN_BASELINE_SCENE, OnBtnBaselineScene)
	ON_BN_CLICKED(IDC_BTN_VQD_EVENT_RULE, OnBtnVQDEventRule)
	ON_BN_CLICKED(IDC_BTN_GET_VQD_ALRM_PIC, OnBtnGetVQDAlarmPic)
	ON_BN_CLICKED(IDC_BTN_FACESNAP, OnBtnFacesnap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaBehaviorCfg message handlers

BOOL CDlgVcaBehaviorCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	return TRUE;
}


void CDlgVcaBehaviorCfg::OnBtnMaskRegion() 
{
	CDlgVcaMaskRegion dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVcaBehaviorCfg::OnBtnEnterRegion2() 
{
    CDlgVcaEnterRegion dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVcaBehaviorCfg::OnBtnLfCfg() 
{
    CDlgVcaLF dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVcaBehaviorCfg::OnBtnSetRulecfg() 
{
	UpdateData(TRUE);
    CDlgVcaRuleCfg dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iVcaChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
	dlg.m_byVCAType = m_byVcaType;
	dlg.m_byMode = m_byVcaChanMode;
    dlg.DoModal();
}

void CDlgVcaBehaviorCfg::OnBtnBehaviorCalibrate() 
{
    CDlgVcaBehaviorCalibrate dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.DoModal();
}

void CDlgVcaBehaviorCfg::OnBtnSizeFilter() 
{
    CDlgSizeFilter dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}   

void CDlgVcaBehaviorCfg::OnBtnFaceDetect() 
{
    CDlgVcaFaceDetect dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
	dlg.m_iChannelNum = m_iChannelNum;
    dlg.DoModal();

}

void CDlgVcaBehaviorCfg::OnBtnVcaWorkStatus() 
{
    CDlgVcaWorkStatus dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChanNum = m_iChannelNum;
    dlg.DoModal();
}

void CDlgVcaBehaviorCfg::OnBtnObjectColor() 
{
	CDlgVcaObjectColor dlg;
	dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel  = m_iVcaChannel;
    dlg.m_lServerID = m_lServerID;
	dlg.DoModal();
}

void CDlgVcaBehaviorCfg::OnBtnAuxArea() 
{
 	CDlgVcaAuxAreaList dlg;
 	dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel  = m_iVcaChannel;
    dlg.m_lServerID = m_lServerID;
 	dlg.DoModal();	
}

void CDlgVcaBehaviorCfg::OnBtnChannelWorkMode() 
{
 	CDlgVcaChannelWorkMode dlg;
 	dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel  = m_iVcaChannel;
    dlg.m_lServerID = m_lServerID;
 	dlg.DoModal();
}

void CDlgVcaBehaviorCfg::OnBtnBaselineScene() 
{
 	CDlgVcaBaselineScene dlg;
 	dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel  = m_iVcaChannel;
    dlg.m_lServerID = m_lServerID;
 	dlg.DoModal();
}

void CDlgVcaBehaviorCfg::OnBtnVQDEventRule() 
{
 	CDlgVcaVQDEventRule dlg;
	dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel  = m_iVcaChannel;
    dlg.m_lServerID = m_lServerID;
    dlg.DoModal();
}

void CDlgVcaBehaviorCfg::OnBtnGetVQDAlarmPic() 
{
 	CDlgVcaVQDAlarmPic dlg;
 	dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel  = m_iVcaChannel;
    dlg.m_lServerID = m_lServerID;
 	dlg.DoModal();
}

void CDlgVcaBehaviorCfg::OnBtnFacesnap() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaFaceSnapCfg dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.m_lChannel = m_iVcaChannel;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}