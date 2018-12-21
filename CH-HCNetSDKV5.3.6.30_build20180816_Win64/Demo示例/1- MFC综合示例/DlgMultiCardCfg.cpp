// DlgMultiCardCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgMultiCardCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMultiCardCfg dialog


CDlgMultiCardCfg::CDlgMultiCardCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMultiCardCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMultiCardCfg)
	m_bCombinationEnable = FALSE;
	m_bEnable = FALSE;
	m_bMultiCardEnable = FALSE;
	m_bOffLineVerify = FALSE;	
	m_dwGroupNo = 0;
	m_byMemberNum = 0;
	m_bySequenceNo = 0;
	m_bySwipeIntervalTimeout = 0;
	m_dwTemplateNo = 0;
	m_dwDoorNo = 1;
	//}}AFX_DATA_INIT
	m_lUserID = -1;
	m_lChannel = -1;
	m_iDevIndex = -1;

	memset(&m_struMultiCardCfg, 0, sizeof(m_struMultiCardCfg));
}


void CDlgMultiCardCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMultiCardCfg)
	DDX_Control(pDX, IDC_COMBO_MULTI_CARD_INDEX, m_comMultiCardIndex);
	DDX_Control(pDX, IDC_COMBO_GROUP_INDEX, m_comGroupIndex);
	DDX_Check(pDX, IDC_CHECK_COMBINATION_ENABLE, m_bCombinationEnable);
	DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
	DDX_Check(pDX, IDC_CHECK_MULTI_CARD_ENABLE, m_bMultiCardEnable);
	DDX_Check(pDX, IDC_CHECK_OFFLINE_VERIFY, m_bOffLineVerify);
	DDX_Text(pDX, IDC_EDIT_GROUP_NO, m_dwGroupNo);
	DDX_Text(pDX, IDC_EDIT_MEMBER_NUM, m_byMemberNum);
	DDX_Text(pDX, IDC_EDIT_SEQUENCE_NO, m_bySequenceNo);
	DDX_Text(pDX, IDC_EDIT_SWIPE_TIME_OUT, m_bySwipeIntervalTimeout);
	DDX_Text(pDX, IDC_EDIT_TEMPLATE_NO, m_dwTemplateNo);
	DDX_Text(pDX, IDC_EDIT_DOOR_NO, m_dwDoorNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMultiCardCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgMultiCardCfg)
	ON_BN_CLICKED(IDC_BTN_GET_MULTI_CARD, OnBtnGetMultiCard)
	ON_BN_CLICKED(IDC_BTN_SET_MULTI_CARD, OnBtnSetMultiCard)
	ON_CBN_SELCHANGE(IDC_COMBO_GROUP_INDEX, OnSelchangeComboGroupIndex)
	ON_BN_CLICKED(IDC_BTN_SAVE_MULTI_CARD, OnBtnSaveMultiCard)
	ON_CBN_SELCHANGE(IDC_COMBO_MULTI_CARD_INDEX, OnSelchangeComboMultiCardIndex)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMultiCardCfg message handlers

BOOL CDlgMultiCardCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_comGroupIndex.SetCurSel(0); 
    m_comMultiCardIndex.SetCurSel(0); 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMultiCardCfg::OnBtnGetMultiCard() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
	DWORD dwReturn = 0;
	
	memset(&m_struMultiCardCfg, 0, sizeof(m_struMultiCardCfg));
    if (NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_MULTI_CARD_CFG_V50, m_dwDoorNo, &m_struMultiCardCfg, sizeof(m_struMultiCardCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_MULTI_CARD_CFG_V50");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_MULTI_CARD_CFG_V50");
        return;
    }
	
	m_bEnable = m_struMultiCardCfg.byEnable;
	m_bySwipeIntervalTimeout = m_struMultiCardCfg.bySwipeIntervalTimeout;	
//	m_bOffLineVerify = m_struMultiCardCfg.byEnableOfflineVerifyMode;

	UpdateData(FALSE);

	m_comMultiCardIndex.SetCurSel(0);
	OnSelchangeComboMultiCardIndex();
}

void CDlgMultiCardCfg::OnBtnSetMultiCard() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    if (NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_MULTI_CARD_CFG_V50, m_dwDoorNo, &m_struMultiCardCfg, sizeof(m_struMultiCardCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_MULTI_CARD_CFG_V50");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_MULTI_CARD_CFG_V50");
        return;
    }

}

void CDlgMultiCardCfg::OnSelchangeComboGroupIndex() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
	int i = m_comMultiCardIndex.GetCurSel();
	int j = m_comGroupIndex.GetCurSel();
	m_bCombinationEnable = m_struMultiCardCfg.struGroupCfg[i].struGroupCombination[j].byEnable;
	m_byMemberNum = m_struMultiCardCfg.struGroupCfg[i].struGroupCombination[j].byMemberNum;
	m_bySequenceNo = m_struMultiCardCfg.struGroupCfg[i].struGroupCombination[j].bySequenceNo;
	m_dwGroupNo = m_struMultiCardCfg.struGroupCfg[i].struGroupCombination[j].dwGroupNo;

	UpdateData(FALSE);
}

void CDlgMultiCardCfg::OnBtnSaveMultiCard() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	m_struMultiCardCfg.dwSize = sizeof(m_struMultiCardCfg);
	m_struMultiCardCfg.byEnable = m_bEnable;
	m_struMultiCardCfg.bySwipeIntervalTimeout = m_bySwipeIntervalTimeout;	
//	m_struMultiCardCfg.byEnableOfflineVerifyMode = m_bOffLineVerify;
	
	int i = m_comMultiCardIndex.GetCurSel();
	int j = m_comGroupIndex.GetCurSel();
	
	m_struMultiCardCfg.struGroupCfg[i].byEnable = m_bMultiCardEnable;
    m_struMultiCardCfg.struGroupCfg[i].byEnableOfflineVerifyMode = m_bOffLineVerify;
	m_struMultiCardCfg.struGroupCfg[i].dwTemplateNo = m_dwTemplateNo;
	
	m_struMultiCardCfg.struGroupCfg[i].struGroupCombination[j].byEnable = m_bCombinationEnable;
	m_struMultiCardCfg.struGroupCfg[i].struGroupCombination[j].byMemberNum = m_byMemberNum;
	m_struMultiCardCfg.struGroupCfg[i].struGroupCombination[j].bySequenceNo = m_bySequenceNo;
	m_struMultiCardCfg.struGroupCfg[i].struGroupCombination[j].dwGroupNo = m_dwGroupNo;
}

void CDlgMultiCardCfg::OnSelchangeComboMultiCardIndex() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
	int i = m_comMultiCardIndex.GetCurSel();
	m_bMultiCardEnable = m_struMultiCardCfg.struGroupCfg[i].byEnable;
    m_bOffLineVerify = m_struMultiCardCfg.struGroupCfg[i].byEnableOfflineVerifyMode; 
	m_dwTemplateNo = m_struMultiCardCfg.struGroupCfg[i].dwTemplateNo;
    UpdateData(FALSE); 
	m_comGroupIndex.SetCurSel(0);
	OnSelchangeComboGroupIndex();
}
