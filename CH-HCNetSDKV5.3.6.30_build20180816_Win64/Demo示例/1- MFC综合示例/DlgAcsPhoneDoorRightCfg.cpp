// DlgAcsPhoneDoorRightCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAcsPhoneDoorRightCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgAcsPhoneDoorRightCfg dialog


DlgAcsPhoneDoorRightCfg::DlgAcsPhoneDoorRightCfg(CWnd* pParent /*=NULL*/)
	: CDialog(DlgAcsPhoneDoorRightCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgAcsPhoneDoorRightCfg)
	
	//}}AFX_DATA_INIT
}


void DlgAcsPhoneDoorRightCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgAcsPhoneDoorRightCfg)
    DDX_Control(pDX, IDC_TREE_OPEN, m_treeOpen);
    DDX_Control(pDX, IDC_TREE_CLOSE, m_treeClose);
    DDX_Control(pDX, IDC_TREE_NORMAL_OPEN, m_treeNormalOpen);
    DDX_Control(pDX, IDC_TREE_NORMAL_CLOSE, m_treeNormalClose);
    DDX_Control(pDX, IDC_TREE_ARM, m_treeArm);
    DDX_Control(pDX, IDC_TREE_DISARM, m_treeDisArm);
    DDX_Control(pDX, IDC_COMBO_CHANNEL, m_comboChannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgAcsPhoneDoorRightCfg, CDialog)
	//{{AFX_MSG_MAP(DlgAcsPhoneDoorRightCfg)
    ON_BN_CLICKED(IDC_BUTTON_SET, OnBtnSet)
    ON_BN_CLICKED(IDC_BUTTON_GET, OnBtnGet)
    ON_NOTIFY(NM_CLICK, IDC_TREE_OPEN, OnClickTreeOpen)
    ON_NOTIFY(NM_CLICK, IDC_TREE_CLOSE, OnClickTreeClose)
    ON_NOTIFY(NM_CLICK, IDC_TREE_NORMAL_OPEN, OnClickTreeNormalOpen)
    ON_NOTIFY(NM_CLICK, IDC_TREE_NORMAL_CLOSE, OnClickTreeNormalClose)
    ON_NOTIFY(NM_CLICK, IDC_TREE_ARM, OnClickTreeArm)
	ON_NOTIFY(NM_CLICK, IDC_TREE_DISARM, OnClickTreeDisArm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgAcsPhoneDoorRightCfg message handlers

BOOL DlgAcsPhoneDoorRightCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;

    CString csStr;
    for (int i = 0; i < NET_SDK_MAX_WHITELIST_NUM_32; i++)
    {
        csStr.Format("%d",i+1);
        m_comboChannel.InsertString(i, csStr);
	}
    
    CreateTree();
    return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgAcsPhoneDoorRightCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetTreeSel(); 
    int iChannel = m_comboChannel.GetCurSel() + 1;
    char szLan[1024];

    if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_PHONE_DOOR_RIGHT_CFG, iChannel, &m_struPhoneDoorRightCfg, sizeof(m_struPhoneDoorRightCfg)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_PHONE_DOOR_RIGHT_CFG Failed");
        g_StringLanType(szLan, "设置手机关联门权限参数失败", "Set phone door right cfg Failed");
		MessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PHONE_DOOR_RIGHT_CFG SUCC");
    }
}

void DlgAcsPhoneDoorRightCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	int iChannel = m_comboChannel.GetCurSel() + 1;
    DWORD dwReturned = 0;
    char szLan[1024];
    
    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_PHONE_DOOR_RIGHT_CFG, iChannel, &m_struPhoneDoorRightCfg, sizeof(m_struPhoneDoorRightCfg), &dwReturned))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PHONE_DOOR_RIGHT_CFG Failed");
        g_StringLanType(szLan, "获取手机关联门权限参数失败", "Get phone door right cfg Failed");
		MessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_PHONE_DOOR_RIGHT_CFG SUCC");
        UpdateData(FALSE); 
        CreateTree();
    }
}

void DlgAcsPhoneDoorRightCfg::CreateTree()
{
    CString strTemp =_T("");
    CString strChanTmp = _T("");
    int i = 0;
    m_treeOpen.DeleteAllItems();
    m_treeClose.DeleteAllItems();
    
    HTREEITEM hChanItem = NULL;
    HTREEITEM hFirstItem = NULL;
       
    for (i = 0; i < sizeof(m_struPhoneDoorRightCfg.byOpenRight); i++)
    {
        strTemp.Format("Door %d", i + 1);
        hChanItem = m_treeOpen.InsertItem(strTemp, 0, 0, TVI_ROOT);
        if (hFirstItem == NULL)
        {
            hFirstItem = hChanItem;
        }

        m_treeOpen.SetItemData(hChanItem, i);

        if (m_struPhoneDoorRightCfg.byOpenRight[i])
        {
            m_treeOpen.SetCheck(hChanItem, TRUE);
        }
    }

    m_treeOpen.SelectItem(hFirstItem);
    m_treeOpen.Expand(m_treeOpen.GetRootItem(), TVE_EXPAND);

    hChanItem = NULL;
    hFirstItem = NULL;

    for (i = 0; i < sizeof(m_struPhoneDoorRightCfg.byCloseRight); i++)
    {
        strTemp.Format("Door %d", i + 1);
        hChanItem = m_treeClose.InsertItem(strTemp, 0, 0, TVI_ROOT);
        if (hFirstItem == NULL)
        {
            hFirstItem = hChanItem;
        }

        m_treeClose.SetItemData(hChanItem, i);

        if (m_struPhoneDoorRightCfg.byCloseRight[i])
        {
            m_treeClose.SetCheck(hChanItem, TRUE);
        }
    }

    m_treeClose.SelectItem(hFirstItem);
	m_treeClose.Expand(m_treeClose.GetRootItem(),TVE_EXPAND);

    hChanItem = NULL;
    hFirstItem = NULL;
    m_treeNormalOpen.DeleteAllItems();    
    for (i = 0; i < sizeof(m_struPhoneDoorRightCfg.byNormalOpenRight); i++)
    {
        strTemp.Format("Door %d", i + 1);
        hChanItem = m_treeNormalOpen.InsertItem(strTemp, 0, 0, TVI_ROOT);
        if (hFirstItem == NULL)
        {
            hFirstItem = hChanItem;
        }
        
        m_treeNormalOpen.SetItemData(hChanItem, i);
        
        if (m_struPhoneDoorRightCfg.byNormalOpenRight[i])
        {
            m_treeNormalOpen.SetCheck(hChanItem, TRUE);
        }
    }
    m_treeNormalOpen.SelectItem(hFirstItem);
	m_treeNormalOpen.Expand(m_treeNormalOpen.GetRootItem(),TVE_EXPAND);


    hChanItem = NULL;
    hFirstItem = NULL;
    m_treeNormalClose.DeleteAllItems();    
    for (i = 0; i < sizeof(m_struPhoneDoorRightCfg.byNormalCloseRight); i++)
    {
        strTemp.Format("Door %d", i + 1);
        hChanItem = m_treeNormalClose.InsertItem(strTemp, 0, 0, TVI_ROOT);
        if (hFirstItem == NULL)
        {
            hFirstItem = hChanItem;
        }
        
        m_treeNormalClose.SetItemData(hChanItem, i);
        
        if (m_struPhoneDoorRightCfg.byNormalCloseRight[i])
        {
            m_treeNormalClose.SetCheck(hChanItem, TRUE);
        }
    }
    m_treeNormalClose.SelectItem(hFirstItem);
	m_treeNormalClose.Expand(m_treeNormalClose.GetRootItem(),TVE_EXPAND);

    hChanItem = NULL;
    hFirstItem = NULL;
    m_treeArm.DeleteAllItems();    
    for (i = 0; i < sizeof(m_struPhoneDoorRightCfg.byArmRight); i++)
    {
        strTemp.Format("AlarmIn %d", i + 1);
        hChanItem = m_treeArm.InsertItem(strTemp, 0, 0, TVI_ROOT);
        if (hFirstItem == NULL)
        {
            hFirstItem = hChanItem;
        }
        
        m_treeArm.SetItemData(hChanItem, i);
        
        if (m_struPhoneDoorRightCfg.byArmRight[i])
        {
            m_treeArm.SetCheck(hChanItem, TRUE);
        }
    }
    m_treeArm.SelectItem(hFirstItem);
	m_treeArm.Expand(m_treeArm.GetRootItem(),TVE_EXPAND);

    hChanItem = NULL;
    hFirstItem = NULL;
    m_treeDisArm.DeleteAllItems();    
    for (i = 0; i < sizeof(m_struPhoneDoorRightCfg.byDisarmRight); i++)
    {
        strTemp.Format("AlarmIn %d", i + 1);
        hChanItem = m_treeDisArm.InsertItem(strTemp, 0, 0, TVI_ROOT);
        if (hFirstItem == NULL)
        {
            hFirstItem = hChanItem;
        }
        
        m_treeDisArm.SetItemData(hChanItem, i);
        
        if (m_struPhoneDoorRightCfg.byDisarmRight[i])
        {
            m_treeDisArm.SetCheck(hChanItem, TRUE);
        }
    }
    m_treeDisArm.SelectItem(hFirstItem);
	m_treeDisArm.Expand(m_treeDisArm.GetRootItem(),TVE_EXPAND);
}

void DlgAcsPhoneDoorRightCfg::GetTreeSel()
{
	UpdateData(TRUE); 
	memset(&m_struPhoneDoorRightCfg, 0 , sizeof(m_struPhoneDoorRightCfg));
	m_struPhoneDoorRightCfg.dwSize = sizeof(m_struPhoneDoorRightCfg);

    int i = 0; 
	HTREEITEM hTreeItem;

	BOOL bCheck;
	DWORD dwIndex;
	DWORD dwCount = 0; 
	CTreeCtrl *treeCtr = &m_treeOpen; 
    dwCount = m_treeOpen.GetCount(); 
	hTreeItem = m_treeOpen.GetRootItem();

    for ( i=0; i<dwCount; i++)
    {
		bCheck = treeCtr->GetCheck(hTreeItem);
		dwIndex = treeCtr->GetItemData(hTreeItem);
		m_struPhoneDoorRightCfg.byOpenRight[dwIndex] = bCheck;
		hTreeItem = treeCtr->GetNextSiblingItem(hTreeItem); 
    }

	treeCtr = &m_treeClose;
	hTreeItem = m_treeClose.GetRootItem();
	dwCount = m_treeClose.GetCount(); 
    for ( i=0; i<dwCount; i++)
    {
		bCheck = treeCtr->GetCheck(hTreeItem);
		dwIndex = treeCtr->GetItemData(hTreeItem);
		m_struPhoneDoorRightCfg.byCloseRight[dwIndex] = bCheck;
		hTreeItem = treeCtr->GetNextSiblingItem(hTreeItem); 
    }

	treeCtr = &m_treeNormalOpen;
	hTreeItem = m_treeNormalOpen.GetRootItem();
	dwCount = m_treeNormalOpen.GetCount(); 
    for ( i=0; i<dwCount; i++)
    {
		bCheck = treeCtr->GetCheck(hTreeItem);
		dwIndex = treeCtr->GetItemData(hTreeItem);
		m_struPhoneDoorRightCfg.byNormalOpenRight[dwIndex] = bCheck;
		hTreeItem = treeCtr->GetNextSiblingItem(hTreeItem); 
    }

	treeCtr = &m_treeNormalClose;
	hTreeItem = m_treeNormalClose.GetRootItem();
	dwCount = m_treeNormalClose.GetCount(); 
    for ( i=0; i<dwCount; i++)
    {
		bCheck = treeCtr->GetCheck(hTreeItem);
		dwIndex = treeCtr->GetItemData(hTreeItem);
		m_struPhoneDoorRightCfg.byNormalCloseRight[dwIndex] = bCheck;
		hTreeItem = treeCtr->GetNextSiblingItem(hTreeItem); 
    }

    treeCtr = &m_treeArm;
    hTreeItem = m_treeArm.GetRootItem();
    dwCount = m_treeArm.GetCount(); 
    for ( i=0; i<dwCount; i++)
    {
        bCheck = treeCtr->GetCheck(hTreeItem);
        dwIndex = treeCtr->GetItemData(hTreeItem);
        m_struPhoneDoorRightCfg.byArmRight[dwIndex] = bCheck;
        hTreeItem = treeCtr->GetNextSiblingItem(hTreeItem); 
    }

    treeCtr = &m_treeDisArm;
    hTreeItem = m_treeDisArm.GetRootItem();
    dwCount = m_treeDisArm.GetCount(); 
    for ( i=0; i<dwCount; i++)
    {
        bCheck = treeCtr->GetCheck(hTreeItem);
        dwIndex = treeCtr->GetItemData(hTreeItem);
        m_struPhoneDoorRightCfg.byDisarmRight[dwIndex] = bCheck;
        hTreeItem = treeCtr->GetNextSiblingItem(hTreeItem); 
    }
} 

void DlgAcsPhoneDoorRightCfg::OnClickTreeOpen(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    CPoint pt(0,0);
    CRect rc(0,0,0,0);
    GetCursorPos(&pt);
    m_treeOpen.ScreenToClient(&pt);
    m_treeOpen.GetWindowRect(&rc);
    m_treeOpen.ScreenToClient(&rc);
    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;
    
    UINT uFlag = 0;
    HTREEITEM hSelect = m_treeOpen.HitTest(pt, &uFlag);
    
    if (NULL == hSelect) 
    {
        return;
    }
    m_treeOpen.SelectItem(hSelect);
    DWORD dwIndex = m_treeOpen.GetItemData(hSelect);
    BOOL bCheck = m_treeOpen.GetCheck(hSelect);
    m_treeOpen.SetCheck(hSelect, !bCheck);
    m_struPhoneDoorRightCfg.byOpenRight[dwIndex] = !bCheck;
    //switch checkbox status on click
    if (uFlag & LVHT_ONITEM ||uFlag & LVHT_TOLEFT || uFlag & LVHT_ONITEMLABEL)//LVHT_TOLEFT)
    {
        m_treeOpen.SetCheck(hSelect, !bCheck);
        m_struPhoneDoorRightCfg.byOpenRight[dwIndex] = !bCheck;
    }
    else
    {
        m_treeOpen.SetCheck(hSelect, bCheck);
        m_struPhoneDoorRightCfg.byOpenRight[dwIndex] = bCheck;
	}
    UpdateData(FALSE); 
	*pResult = 0;
}

void DlgAcsPhoneDoorRightCfg::OnClickTreeClose(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    CPoint pt(0,0);
    CRect rc(0,0,0,0);
    GetCursorPos(&pt);
    m_treeClose.ScreenToClient(&pt);
    m_treeClose.GetWindowRect(&rc);
    m_treeClose.ScreenToClient(&rc);
    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;
    
    UINT uFlag = 0;
    HTREEITEM hSelect = m_treeClose.HitTest(pt, &uFlag);
    
    if (NULL == hSelect) 
    {
        return;
    }
    m_treeClose.SelectItem(hSelect);
    DWORD dwIndex = m_treeClose.GetItemData(hSelect);
    BOOL bCheck = m_treeClose.GetCheck(hSelect);
    m_treeClose.SetCheck(hSelect, !bCheck);
    m_struPhoneDoorRightCfg.byCloseRight[dwIndex] = !bCheck;
    //switch checkbox status on click
    if (uFlag & LVHT_ONITEM ||uFlag & LVHT_TOLEFT || uFlag & LVHT_ONITEMLABEL)
    {
        m_treeClose.SetCheck(hSelect, !bCheck);
        m_struPhoneDoorRightCfg.byCloseRight[dwIndex] = !bCheck;
    }
    else
    {
        m_treeClose.SetCheck(hSelect, bCheck);
        m_struPhoneDoorRightCfg.byCloseRight[dwIndex] = bCheck;
	}
    UpdateData(FALSE);
	*pResult = 0;
}

void DlgAcsPhoneDoorRightCfg::OnClickTreeNormalOpen(NMHDR* pNMHDR, LRESULT* pResult) 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    CPoint pt(0,0);
    CRect rc(0,0,0,0);
    GetCursorPos(&pt);
    m_treeNormalOpen.ScreenToClient(&pt);   
    m_treeNormalOpen.GetWindowRect(&rc);
    m_treeNormalOpen.ScreenToClient(&rc);
    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;
    
    UINT uFlag = 0;
    HTREEITEM hSelect = m_treeNormalOpen.HitTest(pt, &uFlag);
    
    if (NULL == hSelect) 
    {
        return;
    }
    m_treeNormalOpen.SelectItem(hSelect);
    DWORD dwIndex = m_treeNormalOpen.GetItemData(hSelect);
    BOOL bCheck = m_treeNormalOpen.GetCheck(hSelect);
    m_treeNormalOpen.SetCheck(hSelect, !bCheck);
    m_struPhoneDoorRightCfg.byNormalOpenRight[dwIndex] = !bCheck;
    //switch checkbox status on click
    if (uFlag & LVHT_ONITEM ||uFlag & LVHT_TOLEFT || uFlag & LVHT_ONITEMLABEL)
    {
        m_treeNormalOpen.SetCheck(hSelect, !bCheck);
        m_struPhoneDoorRightCfg.byNormalOpenRight[dwIndex] = !bCheck;
    }
    else
    {
        m_treeNormalOpen.SetCheck(hSelect, bCheck);
        m_struPhoneDoorRightCfg.byNormalOpenRight[dwIndex] = bCheck;
    }
    UpdateData(FALSE);
    *pResult = 0;
}

void DlgAcsPhoneDoorRightCfg::OnClickTreeNormalClose(NMHDR* pNMHDR, LRESULT* pResult) 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    CPoint pt(0,0);
    CRect rc(0,0,0,0);
    GetCursorPos(&pt);
    m_treeNormalClose.ScreenToClient(&pt);   
    m_treeNormalClose.GetWindowRect(&rc);
    m_treeNormalClose.ScreenToClient(&rc);
    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;
    
    UINT uFlag = 0;
    HTREEITEM hSelect = m_treeNormalClose.HitTest(pt, &uFlag);
    
    if (NULL == hSelect) 
    {
        return;
    }
    m_treeNormalClose.SelectItem(hSelect);
    DWORD dwIndex = m_treeNormalClose.GetItemData(hSelect);
    BOOL bCheck = m_treeNormalClose.GetCheck(hSelect);
    m_treeNormalClose.SetCheck(hSelect, !bCheck);
    m_struPhoneDoorRightCfg.byNormalCloseRight[dwIndex] = !bCheck;
    //switch checkbox status on click
    if (uFlag & LVHT_ONITEM ||uFlag & LVHT_TOLEFT || uFlag & LVHT_ONITEMLABEL)
    {
        m_treeNormalClose.SetCheck(hSelect, !bCheck);
        m_struPhoneDoorRightCfg.byNormalCloseRight[dwIndex] = !bCheck;
    }
    else
    {
        m_treeNormalClose.SetCheck(hSelect, bCheck);
        m_struPhoneDoorRightCfg.byNormalCloseRight[dwIndex] = bCheck;
    }
    UpdateData(FALSE);
    *pResult = 0;
}

void DlgAcsPhoneDoorRightCfg::OnClickTreeArm(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    CPoint pt(0,0);
    CRect rc(0,0,0,0);
    GetCursorPos(&pt);
    m_treeArm.ScreenToClient(&pt);   
    m_treeArm.GetWindowRect(&rc);
    m_treeArm.ScreenToClient(&rc);
    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;
    
    UINT uFlag = 0;
    HTREEITEM hSelect = m_treeArm.HitTest(pt, &uFlag);
    
    if (NULL == hSelect) 
    {
        return;
    }
    m_treeArm.SelectItem(hSelect);
    DWORD dwIndex = m_treeArm.GetItemData(hSelect);
    BOOL bCheck = m_treeArm.GetCheck(hSelect);
    m_treeArm.SetCheck(hSelect, !bCheck);
    m_struPhoneDoorRightCfg.byArmRight[dwIndex] = !bCheck;
    //switch checkbox status on click
    if (uFlag & LVHT_ONITEM ||uFlag & LVHT_TOLEFT || uFlag & LVHT_ONITEMLABEL)
    {
		m_treeArm.SetCheck(hSelect, !bCheck);
        m_struPhoneDoorRightCfg.byArmRight[dwIndex] = !bCheck;
    }
    else
    {
        m_treeArm.SetCheck(hSelect, bCheck);
        m_struPhoneDoorRightCfg.byArmRight[dwIndex] = bCheck;
	}
    UpdateData(FALSE);
	*pResult = 0;
}

void DlgAcsPhoneDoorRightCfg::OnClickTreeDisArm(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    CPoint pt(0,0);
    CRect rc(0,0,0,0);
    GetCursorPos(&pt);
    m_treeDisArm.ScreenToClient(&pt);
    m_treeDisArm.GetWindowRect(&rc);
    m_treeDisArm.ScreenToClient(&rc);
    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;

    UINT uFlag = 0;
    HTREEITEM hSelect = m_treeDisArm.HitTest(pt, &uFlag);

    if (NULL == hSelect) 
    {
        return;
    }
    m_treeDisArm.SelectItem(hSelect);
    DWORD dwIndex = m_treeDisArm.GetItemData(hSelect);
    BOOL bCheck = m_treeDisArm.GetCheck(hSelect);
    m_treeDisArm.SetCheck(hSelect, !bCheck);
    m_struPhoneDoorRightCfg.byDisarmRight[dwIndex] = !bCheck;

    //switch checkbox status on click
    if (uFlag & LVHT_ONITEM ||uFlag & LVHT_TOLEFT || uFlag & LVHT_ONITEMLABEL )
    {
        m_treeDisArm.SetCheck(hSelect, !bCheck);
        m_struPhoneDoorRightCfg.byDisarmRight[dwIndex] = !bCheck;
    }
    else
    {
        m_treeDisArm.SetCheck(hSelect, bCheck);
        m_struPhoneDoorRightCfg.byDisarmRight[dwIndex] = bCheck;
    }	
    UpdateData(FALSE);
	*pResult = 0;
}


