// DlgVcaFace.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaFace.h"
#include "DlgvcaMaskRegion.h"
#include "DlgSizeFilter.h"
#include "DlgVcaFaceSnapCfg.h"
#include "DlgVcaFindBackgroundPic.h"
#include "DlgVcaSingleProcImg.h"
#include "DlgVcaBlackList.h"
#include "DlgVcaFindSnapData.h"
#include "DlgVcaFaceMatchLogSearch.h"
#include "DlgVcaDataBase.h"
#include "DlgVcaSnapDatabase.h"
#include "DlgVcaFaceDataBase.h"
#include "DlgVcaSavePathConfig.h"
#include "DlgVcaDevAccessCfg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaFace dialog


CDlgVcaFace::CDlgVcaFace(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaFace::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaFace)
	//}}AFX_DATA_INIT
}


void CDlgVcaFace::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaFace)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaFace, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaFace)
	ON_BN_CLICKED(IDC_BTN_MASK_REGION, OnBtnMaskRegion)
	ON_BN_CLICKED(IDC_BTN_FACESNAP, OnBtnFacesnap)
	ON_BN_CLICKED(IDC_BTN_FIND_BACKGROUNDPIC, OnBtnFindBackgroundpic)
	ON_BN_CLICKED(IDC_BTN_FD_PROCIMG, OnBtnFdProcimg)
	ON_BN_CLICKED(IDC_BTN_BLACKLIST, OnBtnBlacklist)
	ON_BN_CLICKED(IDC_BTN_FIND_SNAP_PIC, OnBtnFindSnapPic)
	ON_BN_CLICKED(IDC_BTN_FACEMATCH_LOG, OnBtnFacematchLog)
	ON_BN_CLICKED(IDC_BTN_VCA_DATABASE, OnBtnVcaDatabase)
	ON_BN_CLICKED(IDC_BTN_SNAP_DATABASE, OnBtnSnapDatabase)
	ON_BN_CLICKED(IDC_BTN_FACE_DATABASE, OnBtnFaceDatabase)
	ON_BN_CLICKED(IDC_BTN_SAVE_PATH, OnBtnSavePath)
	ON_BN_CLICKED(IDC_BTN_DEV_ACCESS_CFG, OnBtnDevAccessCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaFace message handlers
BOOL CDlgVcaFace::OnInitDialog() 
{
	CDialog::OnInitDialog();
	return TRUE;  
}


void CDlgVcaFace::OnBtnMaskRegion() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaMaskRegion dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVcaFace::OnBtnFacesnap() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaFaceSnapCfg dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVcaFace::OnBtnFindBackgroundpic() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaFindBackgroundPic dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVcaFace::OnBtnFdProcimg() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaSingleProcImg dlg;
    dlg.m_lServerID = m_lServerID;
	dlg.m_lChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVcaFace::OnBtnBlacklist() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaBlackList dlg;
    dlg.m_lServerID = m_lServerID;
	dlg.m_lChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVcaFace::OnBtnFindSnapPic() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaFindSnapData dlg;
    dlg.m_lServerID = m_lServerID;
	dlg.m_lChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVcaFace::OnBtnFacematchLog() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaFaceMatchLogSearch dlg;
    dlg.m_lServerID = m_lServerID;
	dlg.m_lChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVcaFace::OnBtnVcaDatabase() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaDataBase dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CDlgVcaFace::OnBtnSnapDatabase() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaSnapDatabase dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CDlgVcaFace::OnBtnFaceDatabase() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaFaceDataBase dlg;
	dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CDlgVcaFace::OnBtnSavePath() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaSavePathConfig dlg;
    dlg.m_lServerID = m_lServerID;
	dlg.m_lChannel = m_iVcaChannel;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CDlgVcaFace::OnBtnDevAccessCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaDevAccessCfg dlg;
    dlg.m_lServerID = m_lServerID;
	dlg.m_lChannel = m_iVcaChannel;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}
