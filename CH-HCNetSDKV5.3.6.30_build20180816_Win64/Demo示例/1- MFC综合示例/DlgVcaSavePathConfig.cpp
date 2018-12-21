// DlgVcaSavePathConfig.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaSavePathConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSavePathConfig dialog


CDlgVcaSavePathConfig::CDlgVcaSavePathConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaSavePathConfig::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaSavePathConfig)
	m_dwDiskNo = 0;
	m_dwLeftSpace = 0;
	m_bChkEnableSave = FALSE;
	m_bChkSaveAlarmPic = FALSE;
	//}}AFX_DATA_INIT
	m_lServerID = -1;
    m_lChannel = -1;
    m_iDevIndex = -1;
	m_lDiskNum = 0;
	memset(&m_struSavePathCfg, 0, sizeof(m_struSavePathCfg));
}


void CDlgVcaSavePathConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaSavePathConfig)
	DDX_Control(pDX, IDC_COMBO_SAVE_TYPE, m_comboSaveType);
	DDX_Control(pDX, IDC_COMBO_DISK_NUM, m_comboDiskNum);
	DDX_Text(pDX, IDC_EDIT_DISK_NO, m_dwDiskNo);
	DDX_Text(pDX, IDC_EDIT_LEFT_SPACE, m_dwLeftSpace);
	DDX_Check(pDX, IDC_CHK_ENABLE_SAVE, m_bChkEnableSave);
	DDX_Check(pDX, IDC_CHK_SAVE_ALARM_PIC, m_bChkSaveAlarmPic);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaSavePathConfig, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaSavePathConfig)
	ON_BN_CLICKED(IDC_BTN_SURE, OnBtnSure)
	ON_BN_CLICKED(IDC_BTN_GET_SAVE_PATH, OnBtnGetSavePath)
	ON_BN_CLICKED(IDC_BTN_SET_SAVE_PATH, OnBtnSetSavePath)
	ON_CBN_SELCHANGE(IDC_COMBO_DISK_NUM, OnSelchangeComboDiskNum)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaSavePathConfig message handlers
BOOL CDlgVcaSavePathConfig::OnInitDialog()
{
	CDialog::OnInitDialog();
	OnBtnGetSavePath();
	return TRUE;
}

void CDlgVcaSavePathConfig::OnBtnSure() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    m_struSavePathCfg.struPathInfo[m_lDiskNum].byActive = m_bChkEnableSave;
	if (m_comboSaveType.GetCurSel() == 3)
	{
		m_struSavePathCfg.struPathInfo[m_lDiskNum].byType = 255;
	}
	else
	{
        m_struSavePathCfg.struPathInfo[m_lDiskNum].byType = m_comboSaveType.GetCurSel();
	}
	
	m_struSavePathCfg.struPathInfo[m_lDiskNum].bySaveAlarmPic = m_bChkSaveAlarmPic;
	m_struSavePathCfg.struPathInfo[m_lDiskNum].dwDiskDriver = m_dwDiskNo;
	m_struSavePathCfg.struPathInfo[m_lDiskNum].dwLeftSpace = m_dwLeftSpace;
}

void CDlgVcaSavePathConfig::OnBtnGetSavePath() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
	m_lDiskNum = 0;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_SAVE_PATH_CFG, 0, &m_struSavePathCfg, sizeof(m_struSavePathCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SAVE_PATH_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SAVE_PATH_CFG");
    }
	
	m_lDiskNum = m_comboDiskNum.GetCurSel();
    m_dwDiskNo = m_struSavePathCfg.struPathInfo[m_lDiskNum].dwDiskDriver;
	m_dwLeftSpace = m_struSavePathCfg.struPathInfo[m_lDiskNum].dwLeftSpace;
	if (m_struSavePathCfg.struPathInfo[m_lDiskNum].byType == 255)
	{
		m_comboSaveType.SetCurSel(3);
	}
	else
	{
		m_comboSaveType.SetCurSel(m_struSavePathCfg.struPathInfo[m_lDiskNum].byType);
	}
	
	m_bChkSaveAlarmPic = m_struSavePathCfg.struPathInfo[m_lDiskNum].bySaveAlarmPic;
	m_bChkEnableSave = m_struSavePathCfg.struPathInfo[m_lDiskNum].byActive;
	UpdateData(FALSE);
}

void CDlgVcaSavePathConfig::OnBtnSetSavePath() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struSavePathCfg.dwSize = sizeof(m_struSavePathCfg);
	
	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_SAVE_PATH_CFG, 0, &m_struSavePathCfg, sizeof(m_struSavePathCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SAVE_PATH_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SAVE_PATH_CFG");
    }
}

void CDlgVcaSavePathConfig::OnSelchangeComboDiskNum() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    m_lDiskNum = m_comboDiskNum.GetCurSel();
    m_dwDiskNo = m_struSavePathCfg.struPathInfo[m_lDiskNum].dwDiskDriver;
	m_dwLeftSpace = m_struSavePathCfg.struPathInfo[m_lDiskNum].dwLeftSpace;
	if (m_struSavePathCfg.struPathInfo[m_lDiskNum].byType == 255)
	{
		m_comboSaveType.SetCurSel(3);
	}
	else
	{
		m_comboSaveType.SetCurSel(m_struSavePathCfg.struPathInfo[m_lDiskNum].byType);
	}

	m_bChkSaveAlarmPic = m_struSavePathCfg.struPathInfo[m_lDiskNum].bySaveAlarmPic;
	m_bChkEnableSave = m_struSavePathCfg.struPathInfo[m_lDiskNum].byActive;
	UpdateData(FALSE);
}
