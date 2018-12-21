// DlgAcsCaseSensor.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAcsCaseSensor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAcsCaseSensor dialog


CDlgAcsCaseSensor::CDlgAcsCaseSensor(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAcsCaseSensor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAcsCaseSensor)
	m_bHostBuzzer = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgAcsCaseSensor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAcsCaseSensor)
	DDX_Control(pDX, IDC_TREE_CARD_DOOR_OPEN, m_treeDoorOpen);
	DDX_Control(pDX, IDC_TREE_CARD_DOOR_CLOSE, m_treeDoorClose);
	DDX_Control(pDX, IDC_TREE_CARD_READER_BUZZER, m_treeCardReaderBuzzer);
	DDX_Control(pDX, IDC_TREE_ALARM_OUT, m_treeAlarmOut);
	DDX_Control(pDX, IDC_COMBO_CASE_SENSOR_NO, m_comboCaseSensorNo);
	DDX_Check(pDX, IDC_CHK_HOST_BUZZER, m_bHostBuzzer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAcsCaseSensor, CDialog)
	//{{AFX_MSG_MAP(CDlgAcsCaseSensor)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_NOTIFY(NM_CLICK, IDC_TREE_CARD_READER_BUZZER, OnClickTreeCardReaderBuzzer)
	ON_NOTIFY(NM_CLICK, IDC_TREE_ALARM_OUT, OnClickTreeAlarmOut)
	ON_NOTIFY(NM_CLICK, IDC_TREE_CARD_DOOR_OPEN, OnClickTreeDoorOpen)
	ON_NOTIFY(NM_CLICK, IDC_TREE_CARD_DOOR_CLOSE, OnClickTreeDoorClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAcsCaseSensor message handlers

BOOL CDlgAcsCaseSensor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    memset(m_struCaseSensorCfg, 0, sizeof(m_struCaseSensorCfg));

    int i = 0;

    for (i = 0; i < MAX_CASE_SENSOR_NUM; i++)
    {
        m_struCaseSensorCfg[i].dwSize = sizeof(m_struCaseSensorCfg[i]);
    }
	
    m_comboCaseSensorNo.SetCurSel(0);

    CreateTree();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAcsCaseSensor::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetTreeSel(); 
    int iSel = m_comboCaseSensorNo.GetCurSel();
//     m_struCaseSensorCfg[iSel].byHostBuzzer = m_bHostBuzzer;

    if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_CASE_SENSOR_CFG, iSel + 1, &m_struCaseSensorCfg[iSel], sizeof(m_struCaseSensorCfg[iSel])))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_CASE_SENSOR_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_CASE_SENSOR_CFG");
    }
}

void CDlgAcsCaseSensor::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	int iSel = m_comboCaseSensorNo.GetCurSel();
    DWORD dwReturned = 0;
    
    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_CASE_SENSOR_CFG, iSel + 1, &m_struCaseSensorCfg[iSel], sizeof(m_struCaseSensorCfg[iSel]), &dwReturned))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_CASE_SENSOR_CFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_CASE_SENSOR_CFG");
        m_bHostBuzzer = m_struCaseSensorCfg[iSel].byHostBuzzer; 
        UpdateData(FALSE); 
        CreateTree();
    }
}

void CDlgAcsCaseSensor::CreateTree()
{    
    int iSel = m_comboCaseSensorNo.GetCurSel();

    if (iSel == -1)
    {
        return;
    }

    CString strTemp =_T("");
    CString strChanTmp = _T("");
    int i = 0;
    m_treeCardReaderBuzzer.DeleteAllItems();
    m_treeAlarmOut.DeleteAllItems();
    
    HTREEITEM hChanItem = NULL;
    HTREEITEM hFirstItem = NULL;
       
    for (i = 0; i < MAX_CARD_READER_NUM; i++)
    {
        strTemp.Format("CardReaderBuzzer %d", i + 1);
        hChanItem = m_treeCardReaderBuzzer.InsertItem(strTemp, 0, 0, TVI_ROOT);
        if (hFirstItem == NULL)
        {
            hFirstItem = hChanItem;
        }

        m_treeCardReaderBuzzer.SetItemData(hChanItem, i);

        if (m_struCaseSensorCfg[iSel].byCardReaderBuzzer[i])
        {
            m_treeCardReaderBuzzer.SetCheck(hChanItem, TRUE);
        }
    }

    m_treeCardReaderBuzzer.SelectItem(hFirstItem);
    m_treeCardReaderBuzzer.Expand(m_treeCardReaderBuzzer.GetRootItem(), TVE_EXPAND);

    hChanItem = NULL;
    hFirstItem = NULL;

    for (i = 0; i < MAX_ALARMHOST_ALARMOUT_NUM; i++)
    {
        strTemp.Format("AlarmOut %d", i + 1);
        hChanItem = m_treeAlarmOut.InsertItem(strTemp, 0, 0, TVI_ROOT);
        if (hFirstItem == NULL)
        {
            hFirstItem = hChanItem;
        }

        m_treeAlarmOut.SetItemData(hChanItem, i);

        if (m_struCaseSensorCfg[iSel].byAssociateAlarmOut[i])
        {
            m_treeAlarmOut.SetCheck(hChanItem, TRUE);
        }
    }

    m_treeAlarmOut.SelectItem(hFirstItem);
	m_treeAlarmOut.Expand(m_treeAlarmOut.GetRootItem(),TVE_EXPAND);

    hChanItem = NULL;
    hFirstItem = NULL;
    m_treeDoorOpen.DeleteAllItems();    
    for (i = 0; i < MAX_DOOR_NUM; i++)
    {
        strTemp.Format("Open Door %d", i + 1);
        hChanItem = m_treeDoorOpen.InsertItem(strTemp, 0, 0, TVI_ROOT);
        if (hFirstItem == NULL)
        {
            hFirstItem = hChanItem;
        }
        
        m_treeDoorOpen.SetItemData(hChanItem, i);
        
        if (m_struCaseSensorCfg[iSel].byDoorOpen[i])
        {
            m_treeDoorOpen.SetCheck(hChanItem, TRUE);
        }
    }
    m_treeDoorOpen.SelectItem(hFirstItem);
	m_treeDoorOpen.Expand(m_treeDoorOpen.GetRootItem(),TVE_EXPAND);


    hChanItem = NULL;
    hFirstItem = NULL;
    m_treeDoorClose.DeleteAllItems();
    for (i = 0; i < MAX_DOOR_NUM; i++)
    {
        strTemp.Format("Close Door %d", i + 1);
        hChanItem = m_treeDoorClose.InsertItem(strTemp, 0, 0, TVI_ROOT);
        if (hFirstItem == NULL)
        {
            hFirstItem = hChanItem;
        }      
        m_treeDoorClose.SetItemData(hChanItem, i);
        
        if (m_struCaseSensorCfg[iSel].byDoorClose[i])
        {
            m_treeDoorClose.SetCheck(hChanItem, TRUE);
        }
    }
    m_treeDoorClose.SelectItem(hFirstItem);
	m_treeDoorClose.Expand(m_treeDoorClose.GetRootItem(),TVE_EXPAND);
}

void CDlgAcsCaseSensor::GetTreeSel()
{
	UpdateData(TRUE); 
	int iSel = m_comboCaseSensorNo.GetCurSel();
	memset(&m_struCaseSensorCfg[iSel], 0 , sizeof(m_struCaseSensorCfg[iSel]));
	m_struCaseSensorCfg[iSel].dwSize = sizeof(m_struCaseSensorCfg[iSel]);
	m_struCaseSensorCfg[iSel].byHostBuzzer = m_bHostBuzzer; 
    int i = 0; 
	HTREEITEM hTreeItem;

	BOOL bCheck;
	DWORD dwIndex;
	DWORD dwCount = 0; 
	CTreeCtrl *treeCtr = &m_treeAlarmOut; 
    dwCount = m_treeAlarmOut.GetCount(); 
	hTreeItem = m_treeAlarmOut.GetRootItem();

    for ( i=0; i<dwCount; i++)
    {
		bCheck = treeCtr->GetCheck(hTreeItem);
		dwIndex = treeCtr->GetItemData(hTreeItem);
		m_struCaseSensorCfg[iSel].byAssociateAlarmOut[dwIndex] = bCheck;
		hTreeItem = treeCtr->GetNextSiblingItem(hTreeItem); 
    }

	treeCtr = &m_treeCardReaderBuzzer;
	hTreeItem = m_treeCardReaderBuzzer.GetRootItem();
	dwCount = m_treeCardReaderBuzzer.GetCount(); 
    for ( i=0; i<dwCount; i++)
    {
		bCheck = treeCtr->GetCheck(hTreeItem);
		dwIndex = treeCtr->GetItemData(hTreeItem);
		m_struCaseSensorCfg[iSel].byCardReaderBuzzer[dwIndex] = bCheck;
		hTreeItem = treeCtr->GetNextSiblingItem(hTreeItem); 
    }

	treeCtr = &m_treeDoorOpen;
	hTreeItem = m_treeDoorOpen.GetRootItem();
	dwCount = m_treeDoorOpen.GetCount(); 
    for ( i=0; i<dwCount; i++)
    {
		bCheck = treeCtr->GetCheck(hTreeItem);
		dwIndex = treeCtr->GetItemData(hTreeItem);
		m_struCaseSensorCfg[iSel].byDoorOpen[dwIndex] = bCheck;
		hTreeItem = treeCtr->GetNextSiblingItem(hTreeItem); 
    }

	treeCtr = &m_treeDoorClose;
	hTreeItem = m_treeDoorClose.GetRootItem();
	dwCount = m_treeDoorClose.GetCount(); 
    for ( i=0; i<dwCount; i++)
    {
		bCheck = treeCtr->GetCheck(hTreeItem);
		dwIndex = treeCtr->GetItemData(hTreeItem);
		m_struCaseSensorCfg[iSel].byDoorClose[dwIndex] = bCheck;
		hTreeItem = treeCtr->GetNextSiblingItem(hTreeItem); 
    }

} 

void CDlgAcsCaseSensor::OnClickTreeCardReaderBuzzer(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int iSel = m_comboCaseSensorNo.GetCurSel();
    if (iSel == -1)
    {
        return;
    }

    CPoint pt(0,0);
    CRect rc(0,0,0,0);
    GetCursorPos(&pt);
    m_treeCardReaderBuzzer.ScreenToClient(&pt);
    GetDlgItem(IDC_TREE_CARD_READER_BUZZER)->GetWindowRect(&rc);
    m_treeCardReaderBuzzer.ScreenToClient(&rc);
    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;
    
    UINT uFlag = 0;
    HTREEITEM hSelect = m_treeCardReaderBuzzer.HitTest(pt, &uFlag);
    
    if (NULL == hSelect) 
    {
        return;
    }
    m_treeCardReaderBuzzer.SelectItem(hSelect);
    DWORD dwIndex = m_treeCardReaderBuzzer.GetItemData(hSelect);
    BOOL bCheck = m_treeCardReaderBuzzer.GetCheck(hSelect);
    m_treeCardReaderBuzzer.SetCheck(hSelect, !bCheck);
    m_struCaseSensorCfg[iSel].byCardReaderBuzzer[dwIndex] = !bCheck;
    //switch checkbox status on click
    if (uFlag & LVHT_ONITEM ||uFlag & LVHT_TOLEFT || uFlag & LVHT_ONITEMLABEL)//LVHT_TOLEFT)
    {
        m_treeCardReaderBuzzer.SetCheck(hSelect, !bCheck);
        m_struCaseSensorCfg[iSel].byCardReaderBuzzer[dwIndex] = !bCheck;
    }
    else
    {
        m_treeCardReaderBuzzer.SetCheck(hSelect, bCheck);
        m_struCaseSensorCfg[iSel].byCardReaderBuzzer[dwIndex] = bCheck;
	}
    UpdateData(FALSE); 
	*pResult = 0;
}

void CDlgAcsCaseSensor::OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int iSel = m_comboCaseSensorNo.GetCurSel();
    if (iSel == -1)
    {
        return;
    }
    CPoint pt(0,0);
    CRect rc(0,0,0,0);
    GetCursorPos(&pt);
    m_treeAlarmOut.ScreenToClient(&pt);
    GetDlgItem(IDC_TREE_ALARM_OUT)->GetWindowRect(&rc);
    m_treeAlarmOut.ScreenToClient(&rc);
    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;
    
    UINT uFlag = 0;
    HTREEITEM hSelect = m_treeAlarmOut.HitTest(pt, &uFlag);
    
    if (NULL == hSelect) 
    {
        return;
    }
    m_treeAlarmOut.SelectItem(hSelect);
    DWORD dwIndex = m_treeAlarmOut.GetItemData(hSelect);
    BOOL bCheck = m_treeAlarmOut.GetCheck(hSelect);
    m_treeAlarmOut.SetCheck(hSelect, !bCheck);
    m_struCaseSensorCfg[iSel].byAssociateAlarmOut[dwIndex] = !bCheck;
    //switch checkbox status on click
    if (uFlag & LVHT_ONITEM ||uFlag & LVHT_TOLEFT || uFlag & LVHT_ONITEMLABEL)
    {
        m_treeAlarmOut.SetCheck(hSelect, !bCheck);
        m_struCaseSensorCfg[iSel].byAssociateAlarmOut[dwIndex] = !bCheck;
    }
    else
    {
        m_treeAlarmOut.SetCheck(hSelect, bCheck);
        m_struCaseSensorCfg[iSel].byAssociateAlarmOut[dwIndex] = bCheck;
	}
    UpdateData(FALSE);
	*pResult = 0;
}

void CDlgAcsCaseSensor::OnClickTreeDoorOpen(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    int iSel = m_comboCaseSensorNo.GetCurSel();
    if (iSel == -1)
    {
        return;
    }
    CPoint pt(0,0);
    CRect rc(0,0,0,0);
    GetCursorPos(&pt);
    m_treeDoorOpen.ScreenToClient(&pt);   
    m_treeDoorOpen.GetWindowRect(&rc);
    m_treeDoorOpen.ScreenToClient(&rc);
    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;
    
    UINT uFlag = 0;
    HTREEITEM hSelect = m_treeDoorOpen.HitTest(pt, &uFlag);
    
    if (NULL == hSelect) 
    {
        return;
    }
    m_treeDoorOpen.SelectItem(hSelect);
    DWORD dwIndex = m_treeDoorOpen.GetItemData(hSelect);
    BOOL bCheck = m_treeDoorOpen.GetCheck(hSelect);
    m_treeDoorOpen.SetCheck(hSelect, !bCheck);
    m_struCaseSensorCfg[iSel].byDoorOpen[dwIndex] = !bCheck;
    //switch checkbox status on click
    if (uFlag & LVHT_ONITEM ||uFlag & LVHT_TOLEFT || uFlag & LVHT_ONITEMLABEL)
    {
		m_treeDoorOpen.SetCheck(hSelect, !bCheck);
        m_struCaseSensorCfg[iSel].byDoorOpen[dwIndex] = !bCheck;
    }
    else
    {
        m_treeDoorOpen.SetCheck(hSelect, bCheck);
        m_struCaseSensorCfg[iSel].byDoorOpen[dwIndex] = bCheck;
	}
    UpdateData(FALSE);
	*pResult = 0;
}

void CDlgAcsCaseSensor::OnClickTreeDoorClose(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int iSel = m_comboCaseSensorNo.GetCurSel();
    if (iSel == -1)
    {
        return;
    }
    CPoint pt(0,0);
    CRect rc(0,0,0,0);
    GetCursorPos(&pt);
    m_treeDoorClose.ScreenToClient(&pt);
    m_treeDoorClose.GetWindowRect(&rc);
    m_treeDoorClose.ScreenToClient(&rc);
    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;

    UINT uFlag = 0;
    HTREEITEM hSelect = m_treeDoorClose.HitTest(pt, &uFlag);

    if (NULL == hSelect) 
    {
        return;
    }
    m_treeDoorClose.SelectItem(hSelect);
    DWORD dwIndex = m_treeDoorClose.GetItemData(hSelect);
    BOOL bCheck = m_treeDoorClose.GetCheck(hSelect);
    m_treeDoorClose.SetCheck(hSelect, !bCheck);
    m_struCaseSensorCfg[iSel].byDoorClose[dwIndex] = !bCheck;

    //switch checkbox status on click
    if (uFlag & LVHT_ONITEM ||uFlag & LVHT_TOLEFT || uFlag & LVHT_ONITEMLABEL )
    {
        m_treeDoorClose.SetCheck(hSelect, !bCheck);
        m_struCaseSensorCfg[iSel].byDoorClose[dwIndex] = !bCheck;
    }
    else
    {
        m_treeDoorClose.SetCheck(hSelect, bCheck);
        m_struCaseSensorCfg[iSel].byDoorClose[dwIndex] = bCheck;
    }	
    UpdateData(FALSE);
	*pResult = 0;
}
