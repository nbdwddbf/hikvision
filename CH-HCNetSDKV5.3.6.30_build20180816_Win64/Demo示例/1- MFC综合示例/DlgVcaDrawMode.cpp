// DlgVcaDrawMode.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaDrawMode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaDrawMode dialog


CDlgVcaDrawMode::CDlgVcaDrawMode(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaDrawMode::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaDrawMode)
	m_bDSPAddRule = FALSE;
    m_bDSPAddTarget = FALSE;
    m_bPicAddRule = FALSE;
    m_bPicAddTarget = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgVcaDrawMode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaDrawMode)
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cmbChannel);
	DDX_Check(pDX, IDC_CHECK_DSP_ADD_RULE, m_bDSPAddRule);
    DDX_Check(pDX, IDC_CHECK_DSP_ADD_TARGET, m_bDSPAddTarget);
    DDX_Check(pDX, IDC_CHECK_PIC_ADD_RULE, m_bPicAddRule);
    DDX_Check(pDX, IDC_CHECK_PIC_ADD_TARGET, m_bPicAddTarget);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaDrawMode, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaDrawMode)
	ON_BN_CLICKED(IDC_BTN_SET_DRAW_MODE, OnBtnSetDrawMode)
	ON_BN_CLICKED(IDC_BTN_GET_DRAW_MODE, OnBtnGetDrawMode)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL, OnSelchangeComboChannel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaDrawMode message handlers

BOOL CDlgVcaDrawMode::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_AddChanInfoToComBox(m_cmbChannel, m_iDevIndex);
    m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
	
    if (!GetVcaDrawMode())
    {
        AfxMessageBox("Fail to get vca draw mode");
    }
    m_bDSPAddRule = m_struVCADrawMode.byDspAddRule;
    m_bDSPAddTarget = m_struVCADrawMode.byDspAddTarget;
    m_bPicAddRule = m_struVCADrawMode.byDspPicAddRule;
    m_bPicAddTarget = m_struVCADrawMode.byDspPicAddTarget;
    
    UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgVcaDrawMode::GetVcaDrawMode()
{
    UpdateData(TRUE);
    BOOL bRet = FALSE;
    m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());

    if(!NET_DVR_GetVCADrawMode(m_lServerID,  m_lChannel, &m_struVCADrawMode))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetVCADrawMode Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetVCADrawMode Chan[%d]", m_lChannel);
        bRet = TRUE;

        m_bDSPAddRule = m_struVCADrawMode.byDspAddRule;
        m_bDSPAddTarget = m_struVCADrawMode.byDspAddTarget;
        m_bPicAddRule = m_struVCADrawMode.byDspPicAddRule;
        m_bPicAddTarget = m_struVCADrawMode.byDspPicAddTarget;

    }
	UpdateData(FALSE);
    return bRet;    
}

BOOL CDlgVcaDrawMode::SetVcaDrawMode()
{
    BOOL bRet = FALSE;
	UpdateData(TRUE);
    m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    if(!NET_DVR_SetVCADrawMode(m_lServerID,  m_lChannel, &m_struVCADrawMode))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SetVCADrawMode Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SetVCADrawMode Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}

void CDlgVcaDrawMode::OnBtnSetDrawMode() 
{
    UpdateData(TRUE);
    m_struVCADrawMode.byDspAddRule = (unsigned char)m_bDSPAddRule;
    m_struVCADrawMode.byDspAddTarget = (unsigned char)m_bDSPAddTarget;
    m_struVCADrawMode.byDspPicAddRule = (unsigned char)m_bPicAddRule;
    m_struVCADrawMode.byDspPicAddTarget = (unsigned char)m_bPicAddTarget;

	if (!SetVcaDrawMode())
	{
        AfxMessageBox("Fail to set vca draw mode");
	}
    else
    {
        AfxMessageBox("Succ to set vca draw mode");
    }
}

void CDlgVcaDrawMode::OnBtnGetDrawMode() 
{
	// TODO: Add your control notification handler code here
	GetVcaDrawMode();
}

void CDlgVcaDrawMode::OnSelchangeComboChannel() 
{
	// TODO: Add your control notification handler code here
    GetVcaDrawMode();
}