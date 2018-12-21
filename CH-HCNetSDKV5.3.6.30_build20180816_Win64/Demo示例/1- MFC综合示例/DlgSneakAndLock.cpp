// DlgSneakAndLock.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgSneakAndLock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSneakAndLock dialog


CDlgSneakAndLock::CDlgSneakAndLock(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSneakAndLock::IDD, pParent)
    ,m_dwLastCardIndex(0)
    ,m_dwLastDoorIndex(0)
{
	//{{AFX_DATA_INIT(CDlgSneakAndLock)
	m_bLockEnable = FALSE;
	m_bSneakEnable = FALSE;
	m_dwMultiDoorGroup = 0;
	m_dwCardReaderSequence = 1;
	m_dwStartCardReaderNo = 1;
	m_bCardReader = FALSE;
	m_dwReaderCardNo = 1;
	//}}AFX_DATA_INIT

	m_lUserID = -1;
	m_lChannel = -1;
	m_iDevIndex= -1;

	memset(&m_struSneakCfg, 0, sizeof(m_struSneakCfg));
	memset(&m_struMultiDoorLockCfg,0,sizeof(m_struMultiDoorLockCfg));
}


void CDlgSneakAndLock::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSneakAndLock)
	DDX_Control(pDX, IDC_LST_DOOR_INTERLOCK, m_lstDoorInterLock);
	DDX_Control(pDX, IDC_LST_FOLLOWUP_CARDREADER, m_lstFollowCardRead);
	DDX_Control(pDX, IDC_COMBO_CARD_READER_SEQ_INDEX, m_comCardReaderSeqIndex);
	DDX_Control(pDX, IDC_COMBO_CARD_READER_INDEX, m_comCardReaderIndex);
	DDX_Control(pDX, IDC_COMBO_LOCK_GROUP_INDEX, m_comLockGroupIndex);
	DDX_Control(pDX, IDC_COMBO_LOCK_DOOR_INDEX, m_comLockDoorIndex);
	DDX_Check(pDX, IDC_CHECK_LOCK_ENABLE, m_bLockEnable);
	DDX_Check(pDX, IDC_CHECK_SNEAK_ENABLE, m_bSneakEnable);
	DDX_Text(pDX, IDC_EDIT_LOCK_DOOR_NO, m_dwMultiDoorGroup);
	DDX_Text(pDX, IDC_EDIT_SEQ_READER_NO, m_dwCardReaderSequence);
	DDX_Text(pDX, IDC_EDIT_START_READER_NO, m_dwStartCardReaderNo);
	DDX_Check(pDX, IDC_CHK_CRAD_READER, m_bCardReader);
	DDX_Text(pDX, IDC_EDIT_READER_NO, m_dwReaderCardNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSneakAndLock, CDialog)
	//{{AFX_MSG_MAP(CDlgSneakAndLock)
	ON_BN_CLICKED(IDC_BTN_SAVE_LOCK, OnBtnSaveLock)
	ON_BN_CLICKED(IDC_BTN_SET_LOCK, OnBtnSetLock)
	ON_BN_CLICKED(IDC_BTN_GET_LOCK, OnBtnGetLock)
	ON_CBN_SELCHANGE(IDC_COMBO_LOCK_GROUP_INDEX, OnSelchangeComboLockGroupIndex)
	ON_CBN_SELCHANGE(IDC_COMBO_LOCK_DOOR_INDEX, OnSelchangeComboLockDoorIndex)
	ON_BN_CLICKED(IDC_BTN_SAVE_SNEAK, OnBtnSaveSneak)
	ON_BN_CLICKED(IDC_BTN_SET_SNEAK, OnBtnSetSneak)
	ON_BN_CLICKED(IDC_BTN_GET_SNEAK, OnBtnGetSneak)
	ON_CBN_SELCHANGE(IDC_COMBO_CARD_READER_INDEX, OnSelchangeComboCardReaderIndex)
	ON_CBN_SELCHANGE(IDC_COMBO_CARD_READER_SEQ_INDEX, OnSelchangeComboCardReaderSeqIndex)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_GET_SNEAK_READCARD, OnBtnGetSneakReadcard)
	ON_BN_CLICKED(IDC_BTN_SET_SNEAK_READCARD, OnBtnSetSneakReadcard)
	ON_NOTIFY(NM_CLICK, IDC_LST_FOLLOWUP_CARDREADER, OnClickLstFollowupCardReader)
	ON_EN_KILLFOCUS(IDC_EDIT_SEQ_READER_NO, OnKillfocusEditSeqReaderNo)
	ON_NOTIFY(NM_CLICK, IDC_LST_DOOR_INTERLOCK, OnClickLstDoorInterlock)
	ON_EN_KILLFOCUS(IDC_EDIT_LOCK_DOOR_NO, OnKillfocusLockDoorNo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSneakAndLock message handlers

void CDlgSneakAndLock::OnBtnSaveLock() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int i = m_comLockGroupIndex.GetCurSel();
	int j = m_comLockDoorIndex.GetCurSel();

	m_struMultiDoorLockCfg.dwSize = sizeof(m_struMultiDoorLockCfg);
	m_struMultiDoorLockCfg.byEnable = m_bLockEnable;
	m_struMultiDoorLockCfg.dwMultiDoorGroup[i][j] = m_dwMultiDoorGroup;

}

void CDlgSneakAndLock::OnBtnSetLock() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    m_struMultiDoorLockCfg.dwSize = sizeof(m_struMultiDoorLockCfg);
	m_struMultiDoorLockCfg.byEnable = m_bLockEnable;
//     int i = m_comLockGroupIndex.GetCurSel();
//     int j = m_comLockDoorIndex.GetCurSel();
//     m_struMultiDoorLockCfg.dwMultiDoorGroup[i][j] = m_dwMultiDoorGroup;
	if (NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_MULTI_DOOR_INTERLOCK_CFG, m_lChannel, &m_struMultiDoorLockCfg, sizeof(m_struMultiDoorLockCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_MULTI_DOOR_INTERLOCK_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_MULTI_DOOR_INTERLOCK_CFG");
        return;
    }
}

void CDlgSneakAndLock::OnBtnGetLock() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
	if (NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_MULTI_DOOR_INTERLOCK_CFG, m_lChannel, &m_struMultiDoorLockCfg, sizeof(m_struMultiDoorLockCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_MULTI_DOOR_INTERLOCK_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_MULTI_DOOR_INTERLOCK_CFG");
        return;
    }

	m_bLockEnable = m_struMultiDoorLockCfg.byEnable;
	UpdateData(FALSE);
    UpdateDoorInterlockList();

}

BOOL CDlgSneakAndLock::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_comLockGroupIndex.SetCurSel(0);
	m_comLockDoorIndex.SetCurSel(0);

	m_comCardReaderIndex.SetCurSel(0);
	m_comCardReaderSeqIndex.SetCurSel(0);

    memset(m_bySet, 0, sizeof(m_bySet));
    memset(m_struCardReadAntiSneak, 0, sizeof(m_struCardReadAntiSneak));
    memset(&m_struCardAntiSneak, 0, sizeof(m_struCardAntiSneak));
    m_struCardAntiSneak.dwSize = sizeof(m_struCardAntiSneak); 

    char csTmp[128];
    m_lstFollowCardRead.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES); 
    g_StringLanType(csTmp, "ÐòºÅ", "number");
    m_lstFollowCardRead.InsertColumn(0, csTmp, LVCFMT_LEFT, 60, -1);
    g_StringLanType(csTmp, "ºóÐø¶Á¿¨Æ÷±àºÅ", "follow reader number");
    m_lstFollowCardRead.InsertColumn(1, csTmp, LVCFMT_LEFT, 100, -1);

    m_lstDoorInterLock.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES); 
    g_StringLanType(csTmp, "¶àÃÅ»¥Ëø×éºÅ", "group number");
    m_lstDoorInterLock.InsertColumn(0, csTmp, LVCFMT_LEFT, 80, -1);
     g_StringLanType(csTmp, "»¥ËøÃÅºÅ", "lock door number");
    m_lstDoorInterLock.InsertColumn(1, csTmp, LVCFMT_LEFT, 80, -1);
    g_StringLanType(csTmp, "ÃÅ±àºÅ", "door number");
    m_lstDoorInterLock.InsertColumn(2, csTmp, LVCFMT_LEFT, 80, -1);
    UpdateFollowUpList(); 
    UpdateDoorInterlockList(); 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSneakAndLock::OnSelchangeComboLockGroupIndex() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
	int i = m_comLockGroupIndex.GetCurSel();

	m_comLockDoorIndex.SetCurSel(0);
	OnSelchangeComboLockDoorIndex();
}

void CDlgSneakAndLock::OnSelchangeComboLockDoorIndex() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
	int i = m_comLockGroupIndex.GetCurSel();
	int j = m_comLockDoorIndex.GetCurSel();
    m_struCardAntiSneak.dwFollowUpCardReader[m_dwLastCardIndex] = m_dwCardReaderSequence; 
    m_dwLastCardIndex = m_comCardReaderSeqIndex.GetCurSel(); 
    m_struMultiDoorLockCfg.dwMultiDoorGroup[(m_dwLastDoorIndex>>16)][(m_dwLastDoorIndex&0xffff)] = m_dwMultiDoorGroup;
    m_dwLastDoorIndex = (i<<16) + (j&0xffff); 
	m_dwMultiDoorGroup = m_struMultiDoorLockCfg.dwMultiDoorGroup[i][j];
	UpdateData(FALSE);
}

void CDlgSneakAndLock::OnBtnSaveSneak() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int i = m_comCardReaderIndex.GetCurSel();
	int j = m_comCardReaderSeqIndex.GetCurSel();
	
// 	m_struSneakCfg.dwSize = sizeof(m_struSneakCfg);
// 	m_struSneakCfg.byEnable = m_bSneakEnable;
// 	m_struSneakCfg.dwStartCardReaderNo = m_dwStartCardReaderNo;
    m_struCardReadAntiSneak[i].dwSize = sizeof(m_struCardReadAntiSneak[i]);
	m_struCardReadAntiSneak[i].byEnable = m_bCardReader;
    m_struCardReadAntiSneak[i].dwFollowUpCardReader[j] = m_dwCardReaderSequence;

    m_bySet[i] = 1;
    //m_struSneakCfg.dwCardReaderSequence[i][j] = m_dwCardReaderSequence;
}

void CDlgSneakAndLock::OnBtnSetSneak() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    m_struSneakCfg.dwSize = sizeof(m_struSneakCfg);
    m_struSneakCfg.byEnable = m_bSneakEnable;
    m_struSneakCfg.dwStartCardReaderNo = m_dwStartCardReaderNo;
	if (NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_SNEAK_CFG, m_lChannel, &m_struSneakCfg, sizeof(m_struSneakCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SNEAK_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SNEAK_CFG");
        return;
    }

//     int i = 0;
// 
//     for (i = 0; i < MAX_CARD_READER_NUM; i++)
//     {
//         if (m_bySet[i] == 1)
//         {
//             if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_CARD_READER_ANTI_SNEAK_CFG, i + 1, &m_struCardReadAntiSneak[i], sizeof(m_struCardReadAntiSneak[i])))
//             {
//                 g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_CARD_READER_ANTI_SNEAK_CFG");
//             }
//             else
//             {
//                 g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_CARD_READER_ANTI_SNEAK_CFG");
//                 m_bySet[i] = 0;
//             }
//         }        
//     }
}

void CDlgSneakAndLock::OnBtnGetSneak() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
	if (NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_SNEAK_CFG, m_lChannel, &m_struSneakCfg, sizeof(m_struSneakCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SNEAK_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SNEAK_CFG");
        return;
    }
	
	m_bSneakEnable = m_struSneakCfg.byEnable;
	m_dwStartCardReaderNo = m_struSneakCfg.dwStartCardReaderNo;
	UpdateData(FALSE);

}

void CDlgSneakAndLock::OnSelchangeComboCardReaderIndex() 
{
	// TODO: Add your control notification handler code here
	int i = m_comCardReaderIndex.GetCurSel();
	
	m_comCardReaderSeqIndex.SetCurSel(0);
	OnSelchangeComboCardReaderSeqIndex();
}

void CDlgSneakAndLock::OnSelchangeComboCardReaderSeqIndex() 
{
	// TODO: Add your control notification handler code here// 
// 	
// 	int i = m_comCardReaderIndex.GetCurSel();
// 	int j = m_comCardReaderSeqIndex.GetCurSel();
// 
// 	m_dwCardReaderSequence = m_struCardReadAntiSneak[i].dwFollowUpCardReader[j];
    UpdateData(TRUE); 
    m_struCardAntiSneak.dwFollowUpCardReader[m_dwLastCardIndex] = m_dwCardReaderSequence; 
    m_dwLastCardIndex = m_comCardReaderSeqIndex.GetCurSel(); 
    m_dwCardReaderSequence = m_struCardAntiSneak.dwFollowUpCardReader[m_dwLastCardIndex]; 
	UpdateData(FALSE);
}

void CDlgSneakAndLock::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
    CDialog::OnCancel();
}

void CDlgSneakAndLock::OnBtnGetSneakReadcard() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    memset(&m_struCardAntiSneak, 0, sizeof(m_struCardAntiSneak)); 
    DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_CARD_READER_ANTI_SNEAK_CFG, m_dwReaderCardNo, &m_struCardAntiSneak, sizeof(m_struCardAntiSneak), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_CARD_READER_ANTI_SNEAK_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_CARD_READER_ANTI_SNEAK_CFG");
        return;
    }
    m_bCardReader = m_struCardAntiSneak.byEnable; 
//    m_comCardReaderSeqIndex.SetCurSel(0);
    m_dwCardReaderSequence = m_struCardAntiSneak.dwFollowUpCardReader[0]; 
    UpdateData(FALSE); 
    UpdateFollowUpList(); 
}

void CDlgSneakAndLock::OnBtnSetSneakReadcard() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

    m_struCardAntiSneak.dwSize = sizeof(m_struCardAntiSneak); 
    m_struCardAntiSneak.byEnable = m_bCardReader; 
//    int iSelIndex = m_comCardReaderSeqIndex.GetCurSel();
//    m_struCardAntiSneak.dwFollowUpCardReader[iSelIndex] = m_dwCardReaderSequence; 

    if (NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_CARD_READER_ANTI_SNEAK_CFG, m_dwReaderCardNo, &m_struCardAntiSneak, sizeof(m_struCardAntiSneak)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_CARD_READER_ANTI_SNEAK_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_CARD_READER_ANTI_SNEAK_CFG");
        return;
    }
}

void CDlgSneakAndLock::OnClickLstFollowupCardReader(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    POSITION  iPos = m_lstFollowCardRead.GetFirstSelectedItemPosition();
    if (iPos == NULL)
    {
        return;
    }
    m_dwLastCardIndex  = m_lstFollowCardRead.GetNextSelectedItem(iPos);
    m_dwCardReaderSequence = m_lstFollowCardRead.GetItemData(m_dwLastCardIndex);  
    UpdateData(FALSE); 
	*pResult = 0;
}

void CDlgSneakAndLock::UpdateFollowUpList()
{
    CString csTmp; 
    int iIndex; 
    m_lstFollowCardRead.DeleteAllItems(); 
    for (int i=0; i<MAX_SNEAK_PATH_NODE; i++)
    {
        csTmp.Format("%d", i+1); 
        iIndex = m_lstFollowCardRead.InsertItem(i, csTmp); 
        m_lstFollowCardRead.SetItemData(iIndex, m_struCardAntiSneak.dwFollowUpCardReader[i]);
        csTmp.Format("%d", m_struCardAntiSneak.dwFollowUpCardReader[i]); 
        m_lstFollowCardRead.SetItemText(iIndex, 1, csTmp); 
    }
    UpdateData(FALSE); 
} 

void CDlgSneakAndLock::OnKillfocusEditSeqReaderNo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
    m_struCardAntiSneak.dwFollowUpCardReader[m_dwLastCardIndex] = m_dwCardReaderSequence; 
    UpdateFollowUpList(); 
//    UpdateData(FALSE); 
}

void CDlgSneakAndLock::UpdateDoorInterlockList()
{
    CString csTmp; 
    int iIndex; 
    m_lstDoorInterLock.DeleteAllItems(); 
    for (int i=0; i<MAX_MULTI_DOOR_INTERLOCK_GROUP; i++)
    {
        for (int j=0; j<MAX_INTER_LOCK_DOOR_NUM; j++)
        {
            csTmp.Format("%d", i+1); 
            iIndex = m_lstDoorInterLock.InsertItem(i*MAX_INTER_LOCK_DOOR_NUM+j, csTmp); 
            m_lstDoorInterLock.SetItemData(iIndex, (i<<16)+j );
            csTmp.Format("%d", j+1); 
            m_lstDoorInterLock.SetItemText(iIndex, 1, csTmp); 
            csTmp.Format("%d", m_struMultiDoorLockCfg.dwMultiDoorGroup[i][j] ); 
            m_lstDoorInterLock.SetItemText(iIndex, 2, csTmp); 
        }         
    }
    UpdateData(FALSE); 
}

void CDlgSneakAndLock::OnClickLstDoorInterlock(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
    POSITION  iPos = m_lstDoorInterLock.GetFirstSelectedItemPosition();
    if (iPos == NULL)
    {
        return;
    }
    int iCurSel  = m_lstDoorInterLock.GetNextSelectedItem(iPos);
    m_dwLastDoorIndex = m_lstDoorInterLock.GetItemData(iCurSel);  
    int i, j; 
    i = m_dwLastDoorIndex >> 16;
    j = m_dwLastDoorIndex & 0xffff; 
    m_dwMultiDoorGroup = m_struMultiDoorLockCfg.dwMultiDoorGroup[i][j]; 
    UpdateData(FALSE); 
	*pResult = 0;
}

void CDlgSneakAndLock::OnKillfocusLockDoorNo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
    int i, j; 
    i = m_dwLastDoorIndex >> 16;
    j = m_dwLastDoorIndex & 0xffff;
    m_struMultiDoorLockCfg.dwMultiDoorGroup[i][j] = m_dwMultiDoorGroup; 
    UpdateDoorInterlockList();
}
