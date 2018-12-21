// DlgRaidConfig.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRaidConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRaidConfig dialog

typedef enum
{
    RAID_PD_CONFIG = 0,
    RAID_ARRAY_CONFIG,
    RAID_VD_CONFIG,
    RAID_ADAPTER_CONFIG,
	RAID_BTS_CONFIG
}RAID_CONFIG;

CDlgRaidConfig::CDlgRaidConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRaidConfig::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRaidConfig)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    m_iRaidConfigType = 0;
#if 1
    memset(&m_struAdapterInfo, 0, sizeof(m_struAdapterInfo));
    memset(&m_struPDList, 0, sizeof(m_struPDList));
    memset(&m_struArrayList, 0, sizeof(m_struArrayList));
    memset(&m_struVDList, 0, sizeof(m_struVDList));
    memset(&m_struSpareDisk, 0, sizeof(m_struSpareDisk));
    memset(&m_struArraySpaceAlloc, 0, sizeof(m_struArraySpaceAlloc));
    memset(&m_struOperateArray, 0, sizeof(m_struOperateArray));
    memset(&m_struOpeateVD, 0, sizeof(m_struOpeateVD));
#endif
}


void CDlgRaidConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRaidConfig)
	DDX_Control(pDX, IDC_TAB_RAID_CFG, m_tabRaidCfg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRaidConfig, CDialog)
	//{{AFX_MSG_MAP(CDlgRaidConfig)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_RAID_CFG, OnSelchangeTabRaidCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRaidConfig message handlers

void CDlgRaidConfig::OnOK() 
{
	
	//CDialog::OnOK();
}

BOOL CDlgRaidConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
    
    char szLan[128] = {0};
    int nIndex = 0;
    g_StringLanType(szLan, "ÎïÀí´ÅÅÌÅäÖÃ", "PD Config");
    m_tabRaidCfg.InsertItem(0, szLan);
    nIndex++;
    g_StringLanType(szLan, "ÕóÁÐÅäÖÃ", "ARRAY Config");
    m_tabRaidCfg.InsertItem(nIndex, szLan);
    nIndex++;
    g_StringLanType(szLan, "ÐéÄâ´ÅÅÌÅäÖÃ", "VD Config");
    m_tabRaidCfg.InsertItem(nIndex, szLan);
    nIndex++;
    g_StringLanType(szLan, "ÊÊÅäÆ÷ÅäÖÃ", "Adapter Config");
    m_tabRaidCfg.InsertItem(nIndex, szLan);
    nIndex++;
	g_StringLanType(szLan, "ºóÌ¨ÈÎÎñËÙ¶ÈÅäÖÃ", "BTS Config");
    m_tabRaidCfg.InsertItem(nIndex, szLan);
    nIndex++;

    m_subDlgPDCfg.Create(IDD_SUB_DLG_PD_CFG, &m_tabRaidCfg);
    m_subDlgArrayCfg.Create(IDD_SUB_DLG_ARRAY_CFG, &m_tabRaidCfg);
    m_subDlgVDCfg.Create(IDD_SUB_DLG_VD_CFG, &m_tabRaidCfg);
    m_subDlgAdapterCfg.Create(IDD_SUB_DLG_ADAPTER_CFG, &m_tabRaidCfg);
	m_subDlgBTSCfg.Create(IDD_SUB_DLG_BTS, &m_tabRaidCfg);

    CRect rect;
    m_tabRaidCfg.GetClientRect(&rect);
    rect.top+=20; 
    rect.bottom-=4; 
    rect.left+=4; 
    rect.right-=4; 
    
    m_subDlgPDCfg.MoveWindow(&rect);
    m_subDlgArrayCfg.MoveWindow(&rect);
    m_subDlgVDCfg.MoveWindow(&rect);
    m_subDlgAdapterCfg.MoveWindow(&rect);
	m_subDlgBTSCfg.MoveWindow(&rect);


    m_subDlgPDCfg.ShowWindow(SW_SHOW);
    m_subDlgArrayCfg.ShowWindow(SW_HIDE);
    m_subDlgVDCfg.ShowWindow(SW_HIDE);
    m_subDlgAdapterCfg.ShowWindow(SW_HIDE);
	m_subDlgBTSCfg.ShowWindow(SW_HIDE);
    
//     if (-1 == NET_DVR_RaidFastConfig(m_lServerID, "Raid1"))
//     {
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RaidFastConfig");
//     }
//     else
//     {
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RaidFastConfig");
//     }
// 
//     if (-1 == NET_DVR_ExpandDisk(m_lServerID, 0))
//     {
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_ExpandDisk");
//     }
//     else
//     {
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, " NET_DVR_ExpandDisk");
//     }
//     GetPDList();
//    GetArrayList();
//GetArraySpaceAlloc(0);
    //CreateVD();
    // 
   //  GetVDList();

 //   SetSpareDisk();
//  CreateArray();
//DelArray(0);
    RaidConfigUpdate(RAID_PD_CONFIG);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgRaidConfig::RaidConfigUpdate(int iConfigType)
{
    switch (iConfigType)
    {
    case RAID_PD_CONFIG:
        m_subDlgPDCfg.CurCfgUpdate();
        break;
    case RAID_ARRAY_CONFIG:
        m_subDlgArrayCfg.CurCfgUpdate();
        break;
    case RAID_VD_CONFIG:
        m_subDlgVDCfg.CurCfgUpdate();
        break;
    case RAID_ADAPTER_CONFIG:
        m_subDlgAdapterCfg.CurCfgUpdate();
        break;
	case RAID_BTS_CONFIG:
        m_subDlgBTSCfg.CheckInitParam();
        break;
    default:
        m_iRaidConfigType = RAID_PD_CONFIG;
        m_subDlgPDCfg.CurCfgUpdate();
        break;
    }
    ChangeCurConfigWnd(iConfigType);
}

void CDlgRaidConfig::ChangeCurConfigWnd(int iConfigType)
{
    m_subDlgPDCfg.ShowWindow(SW_HIDE);
    m_subDlgArrayCfg.ShowWindow(SW_HIDE);
    m_subDlgVDCfg.ShowWindow(SW_HIDE);
    m_subDlgAdapterCfg.ShowWindow(SW_HIDE);
	m_subDlgBTSCfg.ShowWindow(SW_HIDE);

    switch (iConfigType)
    {
    case RAID_PD_CONFIG:
        m_subDlgPDCfg.ShowWindow(SW_SHOW);
        break;
    case RAID_ARRAY_CONFIG:
        m_subDlgArrayCfg.ShowWindow(SW_SHOW);
        break;
    case RAID_VD_CONFIG:
        m_subDlgVDCfg.ShowWindow(SW_SHOW);
        break;
    case RAID_ADAPTER_CONFIG:
        m_subDlgAdapterCfg.ShowWindow(SW_SHOW);
        break;
	case RAID_BTS_CONFIG:
        m_subDlgBTSCfg.ShowWindow(SW_SHOW);
        break;
    default:
        m_subDlgPDCfg.ShowWindow(SW_SHOW);
        break;
    }
}

BOOL CDlgRaidConfig::GetAdapterInfo()
{
    DWORD dwReturn = 0;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_RAID_ADAPTER_INFO, 0, &m_struAdapterInfo, sizeof(m_struAdapterInfo), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_RAID_ADAPTER_INFO");
        return FALSE;
    }   
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_RAID_ADAPTER_INFO");
        return TRUE;
    }
}

BOOL CDlgRaidConfig::SetAdapterInfo()
{
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_RAID_ADAPTER_INFO, 0, &m_struAdapterInfo, sizeof(m_struAdapterInfo)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_RAID_ADAPTER_INFO");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_RAID_ADAPTER_INFO");
        return TRUE;
    }
}

BOOL CDlgRaidConfig::GetPDList()
{
    if (!NET_DVR_GetPDList(m_lServerID, &m_struPDList))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetPDList");
        return FALSE;
    }
    else
    {   
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetPDList");
        return TRUE;
    }
}


BOOL CDlgRaidConfig::GetArrayList()
{
    if (!NET_DVR_GetArrayList(m_lServerID, &m_struArrayList))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetArrayList");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetArrayList");
        return TRUE;
    }
}

BOOL CDlgRaidConfig::GetVDList()
{
    if (!NET_DVR_GetVDList(m_lServerID, &m_struVDList))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetVDList");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetVDList");
        return TRUE;
    }
}

BOOL CDlgRaidConfig::SetSpareDisk()
{

    m_struSpareDisk.bySpareType = 1;
    m_struSpareDisk.wPDSlot = 3;
    if (!NET_DVR_SetSpareDisk(m_lServerID, &m_struSpareDisk))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SetSpareDisk");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SetSpareDisk");
        return TRUE;
    }
}

BOOL CDlgRaidConfig::GetArraySpaceAlloc(DWORD dwArraySlot)
{

    if (!NET_DVR_GetArraySpaceAlloc(m_lServerID, dwArraySlot, &m_struArraySpaceAlloc))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetArraySpaceAlloc");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetArraySpaceAlloc");
        return TRUE;
    }
}

BOOL CDlgRaidConfig::DelArray(DWORD dwArrayID)
{
    if (!NET_DVR_DelArray(m_lServerID, dwArrayID))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_DelArray ArrayID[%d]", dwArrayID);
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DelArray ArrayID[%d]", dwArrayID);
        return TRUE;
    }
}

BOOL CDlgRaidConfig::CreateArray()
{

    strncpy((char*)m_struOperateArray.byName, "raid1", MAX_NAMELEN);
        
    if (!NET_DVR_CreateArray(m_lServerID, &m_struOperateArray))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_CreateArray");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_CreateArray");
        return TRUE;
    }
}

BOOL CDlgRaidConfig::MigrateArray()
{
    if (!NET_DVR_MigrateArray(m_lServerID, &m_struOperateArray))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_MigrateArray");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_MigrateArray");
        return TRUE;
    }
}

BOOL CDlgRaidConfig::RebuildArray()
{
    if (!NET_DVR_RebuildArray(m_lServerID, &m_struOperateArray))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RebuildArray");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RebuildArray");
        return TRUE;
    }
}

BOOL CDlgRaidConfig::CreateVD()
{
//     m_struOpeateVD.bySlot = 0;
//     m_struOpeateVD.wArrayID = 0;
//     m_struOpeateVD.dwLCapacity = 1024*1024*100;
//     strncpy((char*)m_struOpeateVD.byName, "VD1", sizeof(m_struOpeateVD.byName));

    if (!NET_DVR_CreateVD(m_lServerID, &m_struOpeateVD))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_CreateVD");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_CreateVD");
        return TRUE;
    }
}
BOOL CDlgRaidConfig::DelVD(DWORD dwID)
{
    if (!NET_DVR_DelVD(m_lServerID, dwID))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_DelVD VD[%d]", dwID);
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_DelVD VD[%d]", dwID);
        return TRUE;
    }
}

BOOL CDlgRaidConfig::RepairVD(DWORD dwID)
{
    if (!NET_DVR_RepairVD(m_lServerID, dwID))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RepairVD VD[%d]", dwID);
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RepairVD VD[%d]", dwID);
        return TRUE;
    }
}

void CDlgRaidConfig::OnSelchangeTabRaidCfg(NMHDR* pNMHDR, LRESULT* pResult) 
{
    m_iRaidConfigType = m_tabRaidCfg.GetCurSel();
 
	RaidConfigUpdate(m_iRaidConfigType);

	*pResult = 0;
}

void CDlgRaidConfig::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
