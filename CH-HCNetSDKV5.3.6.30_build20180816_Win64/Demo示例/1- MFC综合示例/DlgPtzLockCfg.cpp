// DlgPtzLockCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPtzLockCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPtzLockCfg dialog


CDlgPtzLockCfg::CDlgPtzLockCfg(CWnd* pParent /*=NULL*/)
: CDialog(CDlgPtzLockCfg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgPtzLockCfg)
    m_lUserID = -1;
    m_iDevIndex  = -1;
    m_lChannel= -1;
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


void CDlgPtzLockCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPtzLockCfg)
	DDX_Control(pDX, IDC_COMBO_WORKMODE, m_cmbWorkMode);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cmbChannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPtzLockCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgPtzLockCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPtzLockCfg message handlers

BOOL CDlgPtzLockCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	memset(&m_struPtzLockCfg,0,sizeof(m_struPtzLockCfg));

    g_AddChanInfoToComBox(m_cmbChannel,m_iDevIndex);

    for (int i = 0; i< m_cmbChannel.GetCount();i++)
    {
        if (m_lChannel == m_cmbChannel.GetItemData(i))
        {
            m_cmbChannel.SetCurSel(i);
            break;
        }
    }
    OnBtnGet();
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPtzLockCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    DWORD dwReturn = 0;
    if (!NET_DVR_GetDVRConfig(m_lUserID,NET_DVR_GET_PTZLOCKCFG,m_lChannel, &m_struPtzLockCfg,sizeof(m_struPtzLockCfg),&dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_GET_PTZLOCKCFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_GET_PTZLOCKCFG");
    }

    m_cmbWorkMode.SetCurSel(m_struPtzLockCfg.byWorkMode);
    UpdateData(FALSE);

}

void CDlgPtzLockCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_lChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    m_struPtzLockCfg.byWorkMode = m_cmbWorkMode.GetCurSel();

    if (!NET_DVR_SetDVRConfig(m_lUserID,NET_DVR_SET_PTZLOCKCFG,m_lChannel, &m_struPtzLockCfg,sizeof(m_struPtzLockCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_FAIL_T,"NET_DVR_SET_PTZLOCKCFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex,OPERATION_SUCC_T,"NET_DVR_SET_PTZLOCKCFG");
    }
    UpdateData(FALSE);
}
