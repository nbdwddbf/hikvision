// DlgVcaForensicsModeCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaForensicsModeCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaForensicsModeCfg dialog


CDlgVcaForensicsModeCfg::CDlgVcaForensicsModeCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaForensicsModeCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaForensicsModeCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nCurForensicsMode = TFS_FORENSICS_MODE_AUTO;
	memset(&m_struForenciscMode,0, sizeof(m_struForenciscMode));
	m_struForenciscMode.dwSize = sizeof(m_struForenciscMode);
}


void CDlgVcaForensicsModeCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaForensicsModeCfg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaForensicsModeCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaForensicsModeCfg)
	ON_BN_CLICKED(IDC_BTN_SAVE,     OnBtnSave)
	ON_BN_CLICKED(IDC_RADIO_AUTO,   OnRadioAuto)
	ON_BN_CLICKED(IDC_RADIO_MANUAL, OnRadioManual)
    ON_BN_CLICKED(IDC_RADIO_SEMIAUTO, OnRadioSemiAuto)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaForensicsModeCfg message handlers

BOOL CDlgVcaForensicsModeCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
    GetTfsForensicsMode();
	InitWndCtrlState();
	return TRUE;
}

void CDlgVcaForensicsModeCfg::OnBtnSave() 
{   
	char szError[32] = "\0";
	if (SetTfsForensicsMode())
	{
        g_StringLanType(szError, "保存成功","Saved successfully");
	}
	else
	{
		g_StringLanType(szError, "保存失败","Save failed");
	}
	AfxMessageBox(szError);
}

void CDlgVcaForensicsModeCfg::OnRadioAuto() 
{
	CheckDlgButton(IDC_RADIO_MANUAL,BST_UNCHECKED);
	CheckDlgButton(IDC_RADIO_AUTO,  BST_CHECKED);
    CheckDlgButton(IDC_RADIO_SEMIAUTO,  BST_UNCHECKED);
	m_nCurForensicsMode = TFS_FORENSICS_MODE_AUTO;
}

void CDlgVcaForensicsModeCfg::OnRadioManual() 
{
	CheckDlgButton(IDC_RADIO_MANUAL,BST_CHECKED);
	CheckDlgButton(IDC_RADIO_AUTO,  BST_UNCHECKED);
    CheckDlgButton(IDC_RADIO_SEMIAUTO,  BST_UNCHECKED);
	m_nCurForensicsMode = TFS_FORENSICS_MODE_MANUAL;
}

void CDlgVcaForensicsModeCfg::OnRadioSemiAuto() 
{
    CheckDlgButton(IDC_RADIO_MANUAL,BST_UNCHECKED);
    CheckDlgButton(IDC_RADIO_AUTO,  BST_UNCHECKED);
    CheckDlgButton(IDC_RADIO_SEMIAUTO,  BST_CHECKED);
    m_nCurForensicsMode = TFS_FORENSICS_MODE_SEMIAUTO;
}

void CDlgVcaForensicsModeCfg::InitWndCtrlState()
{
	if (m_nCurForensicsMode == TFS_FORENSICS_MODE_AUTO)
	{
		OnRadioAuto();
	}
	else if (m_nCurForensicsMode == TFS_FORENSICS_MODE_MANUAL)
	{
		OnRadioManual();
	}
    else if (m_nCurForensicsMode == TFS_FORENSICS_MODE_SEMIAUTO)
    {
        OnRadioSemiAuto();
    }
}

BOOL CDlgVcaForensicsModeCfg::GetTfsForensicsMode()
{
	DWORD dwStatus = 0;
	BOOL bRet      = FALSE;
	
    if (!NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_FORENSICS_MODE, 1,(LPVOID)&m_lChannel, sizeof(m_lChannel),
		&dwStatus,&m_struForenciscMode, sizeof(m_struForenciscMode)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_FORENSICS_MODE Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_FORENSICS_MODE Chan[%d]", m_lChannel);
        bRet = TRUE;
    }

	m_nCurForensicsMode = m_struForenciscMode.byMode;
    return bRet;
}

BOOL CDlgVcaForensicsModeCfg::SetTfsForensicsMode()
{  
	m_struForenciscMode.byMode = m_nCurForensicsMode;

	DWORD dwStatus = 0;
	BOOL bRet      = FALSE;
	
    if (!NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_FORENSICS_MODE,1,(LPVOID)&m_lChannel, sizeof(m_lChannel),
		&dwStatus,&m_struForenciscMode, sizeof(m_struForenciscMode)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_FORENSICS_MODE Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_FORENSICS_MODE Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}
