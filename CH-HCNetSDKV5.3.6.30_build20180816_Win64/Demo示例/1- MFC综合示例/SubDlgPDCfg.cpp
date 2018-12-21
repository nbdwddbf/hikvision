// SubDlgPDCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "SubDlgPDCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define  FASTCONFIG_TIMER 100
#define  WM_PHY_DISK_INFO_FINISH 1001
/////////////////////////////////////////////////////////////////////////////
// CSubDlgPDCfg dialog
#define WM_PROC_PHY_DISK_INFO_SHOW		WM_USER + 1

CSubDlgPDCfg::CSubDlgPDCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubDlgPDCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSubDlgPDCfg)
	m_csArrayName = _T("");
	m_iArrayID = 0;
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    memset(&m_struPDList, 0, sizeof(m_struPDList));
    memset(&m_struAdapterInfo, 0, sizeof(m_struAdapterInfo));
    memset(&m_struOperateArray, 0, sizeof(m_struOperateArray));
    memset(&m_struSpareDisk, 0, sizeof(m_struSpareDisk));
    m_lFastConfigHandle = -1;
    m_dwArraySize = 0;
    m_dwPhyDiskNum = 0;
    m_pStruPhyDiskInfo = new NET_DVR_PHY_DISK_INFO[64];
    if (m_pStruPhyDiskInfo != NULL)
    {
        memset(m_pStruPhyDiskInfo,0, sizeof(NET_DVR_PHY_DISK_INFO)* 64);
    }
}


void CSubDlgPDCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubDlgPDCfg)
	DDX_Control(pDX, IDC_COMBO_RAID_INIT_MODE, m_comboRaidInitMode);
	DDX_Control(pDX, IDC_COMBO_SPARE_TYPE, m_comboSpareType);
	DDX_Control(pDX, IDC_LIST_PD_SLOT, m_listPDSlot);
	DDX_Control(pDX, IDC_COMBO_RAID_MODE, m_comboRaidMode);
	DDX_Control(pDX, IDC_LIST_PD_INFO, m_ListPDInfo);
	DDX_Text(pDX, IDC_EDIT_ARRAY_NAME, m_csArrayName);
	DDX_Text(pDX, IDC_EDIT_ARRAY_ID, m_iArrayID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubDlgPDCfg, CDialog)
	//{{AFX_MSG_MAP(CSubDlgPDCfg)
	ON_BN_CLICKED(IDC_BTN_FAST_CONFIG, OnBtnFastConfig)
	ON_BN_CLICKED(IDC_BTN_CREATE_ARRAY, OnBtnCreateArray)
	ON_BN_CLICKED(IDC_BTN_SET_SPARE_DISK, OnBtnSetSpareDisk)
	ON_BN_CLICKED(IDC_BTN_DEL_SPARE_DISK, OnBtnDelSpareDisk)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_CALC_ARRAY_SIZE, OnBtnCalcArraySize)
    ON_MESSAGE(WM_PROC_PHY_DISK_INFO_SHOW, OnShowPhyDiskInfo)
    ON_MESSAGE(WM_PHY_DISK_INFO_FINISH, OnMsgPhyDiskInfoFinish)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

LRESULT CSubDlgPDCfg::OnMsgPhyDiskInfoFinish(WPARAM wParam, LPARAM lParam)
{
    NET_DVR_StopRemoteConfig(m_lGetPhyDiskHanle);
    m_lGetPhyDiskHanle = -1;
    g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PHY_DISK_INFO Finish!");
    return 0;
}

void CALLBACK g_PhyDiskInfoCallback(DWORD dwDataType, void* lpBuffer, DWORD dwBufLen, void* pUserData)
{
    CSubDlgPDCfg *pThis = static_cast<CSubDlgPDCfg*>(pUserData);
  
	HWND hWnd = pThis->GetSafeHwnd();
    if (NULL == hWnd)
    {
        return;
	}
    if (dwDataType == NET_SDK_CALLBACK_TYPE_STATUS)
    {       
        g_pMainDlg->AddLog(g_pMainDlg->GetCurDeviceIndex(), OPERATION_SUCC_T, "Get Physical Disk Info status[%d]", *(DWORD*)lpBuffer);
        if (*((DWORD*) lpBuffer) == NET_SDK_CALLBACK_STATUS_SUCCESS)
        {
            pThis->PostMessage(WM_PHY_DISK_INFO_FINISH, 0, 0);
        }
    }
    else if (dwDataType == NET_SDK_CALLBACK_TYPE_DATA)
    {
        NET_DVR_PHY_DISK_INFO struPhyDiskInfo = {0};
        
        
        memcpy(&struPhyDiskInfo,lpBuffer,dwBufLen);
        char *pSzTemp = new char[dwBufLen];
        if (pSzTemp == NULL)
        {
            return;
        }
        memset(pSzTemp,0, dwBufLen);

        memcpy(pSzTemp,&struPhyDiskInfo,dwBufLen);
        ::PostMessage(hWnd,WM_PROC_PHY_DISK_INFO_SHOW, (WPARAM)pSzTemp,dwBufLen);
        
    }
}
BOOL CSubDlgPDCfg::CheckInitParam()
{
    m_iDevIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lServerID = g_struDeviceInfo[m_iDevIndex].lLoginID;
    
    if (!GetAdapterInfo())
    {
        AfxMessageBox("Fail to get adapter info");
       // return FALSE;
    }
    
    m_comboRaidMode.ResetContent();
    int nIndex = 0;
    if (1 == ((m_struAdapterInfo.wSupportRaidType >> 0) & 0x01))
    {
        m_comboRaidMode.AddString("RAID0");
        m_comboRaidMode.SetItemData(nIndex, RAID0);
        nIndex++;
    }
    if (1 == ((m_struAdapterInfo.wSupportRaidType >> 1) & 0x01))
    {
        m_comboRaidMode.AddString("RAID1");
        m_comboRaidMode.SetItemData(nIndex, RAID1);
        nIndex++;
    }
    if (1 == ((m_struAdapterInfo.wSupportRaidType >> 2) & 0x01))
    {
        m_comboRaidMode.AddString("RAID10");
        m_comboRaidMode.SetItemData(nIndex, RAID10);
        nIndex++;
    }
    if (1 == ((m_struAdapterInfo.wSupportRaidType >> 3) & 0x01))
    {
        m_comboRaidMode.AddString("RAID1E");
        m_comboRaidMode.SetItemData(nIndex, RAID1E);
        nIndex++;
    }
    if (1 == ((m_struAdapterInfo.wSupportRaidType >> 4) & 0x01))
    {
        m_comboRaidMode.AddString("RAID5");
        m_comboRaidMode.SetItemData(nIndex, RAID5);
        nIndex++;
    }
    if (1 == ((m_struAdapterInfo.wSupportRaidType >> 5) & 0x01))
    {
        m_comboRaidMode.AddString("RAID6");
        m_comboRaidMode.SetItemData(nIndex, RAID6);
        nIndex++;
    }
    if (1 == ((m_struAdapterInfo.wSupportRaidType >> 6) & 0x01))
    {
        m_comboRaidMode.AddString("RAID50");
        m_comboRaidMode.SetItemData(nIndex, RAID50);
        nIndex++;
    }
    if (1 == ((m_struAdapterInfo.wSupportRaidType >> 7) & 0x01))
    {
        m_comboRaidMode.AddString("JBOD");
        m_comboRaidMode.SetItemData(nIndex, JBOD);
        nIndex++;
    }
    if (1 == ((m_struAdapterInfo.wSupportRaidType >> 8) & 0x01))
    {
        m_comboRaidMode.AddString("RAID60");
        m_comboRaidMode.SetItemData(nIndex, RAID60);
        nIndex++;
    }
    
    return TRUE;
}

void CSubDlgPDCfg::CurCfgUpdate()
{
    if (!CheckInitParam())
    {
        return;
    }
    
    if (!GetPDList())
    {
         return;      
    }

   // m_listPDSlot.DeleteAllItems();            
    m_listPDSlot.SetExtendedStyle(LVS_EX_CHECKBOXES);
   /* char szLan[128] = {0};
    char szLanCn[128] = {0};
    char szLanEn[128] = {0};

	int i = 0;
    for (i = 0; i < m_struPDList.dwCount; i++)
    {
        sprintf(szLan, "%d", m_struPDList.struPhyDiskInfo[i].wPhySlot);
        m_listPDSlot.InsertItem(i, szLan);
    }

    m_ListPDInfo.DeleteAllItems();
    int nIndex = 0;
    memset(szLan, 0, sizeof(szLan));
    memset(szLanCn, 0, sizeof(szLanCn));
    memset(szLanEn, 0, sizeof(szLanEn));
    for (i = 0; i < m_struPDList.dwCount; i++)
    {
        nIndex = 0;
        sprintf(szLan, "%d",m_struPDList.struPhyDiskInfo[i].wPhySlot);   
        m_ListPDInfo.InsertItem(i, szLan,nIndex);
        nIndex++;
        
        unsigned __int64 dwCapacity = 0;
        *((DWORD*)&dwCapacity) = m_struPDList.struPhyDiskInfo[i].dwLCapacity;
        *((DWORD*)((char*)&dwCapacity + 4))  = m_struPDList.struPhyDiskInfo[i].dwHCapacity;
        dwCapacity >>= 20;
        sprintf(szLan, "%I64u Gb", dwCapacity);
        m_ListPDInfo.SetItemText(i, nIndex, szLan);
        nIndex++;

         m_ListPDInfo.SetItemText(i, nIndex, LPCTSTR(m_struPDList.struPhyDiskInfo[i].byArrrayName));
        nIndex++;

       if (0 == m_struPDList.struPhyDiskInfo[i].byType)
       {
           //普通，1全局热备，2-阵列热备
           strncpy(szLanCn, "普通", sizeof(szLanCn));
           strncpy(szLanEn, "Normal", sizeof(szLanEn));
           g_StringLanType(szLan, szLanCn, szLanEn);
       }
       else if (1 == m_struPDList.struPhyDiskInfo[i].byType)
       {
            strncpy(szLanCn, "全局热备", sizeof(szLanCn));
            strncpy(szLanEn, "Global spare disk", sizeof(szLanEn));
            g_StringLanType(szLan, szLanCn, szLanEn);
       }
       else if (2 == m_struPDList.struPhyDiskInfo[i].byType)
       {
           strncpy(szLanCn, "阵列热备", sizeof(szLanCn));
           strncpy(szLanEn, "Global spare disk", sizeof(szLanEn));
           g_StringLanType(szLan, szLanCn, szLanEn);    
       }
	   else if (3 == m_struPDList.struPhyDiskInfo[i].byType)
       {
           strncpy(szLanCn, "阵列盘", sizeof(szLanCn));
           strncpy(szLanEn, "raid array disk", sizeof(szLanEn));
           g_StringLanType(szLan, szLanCn, szLanEn);    
       }
       m_ListPDInfo.SetItemText(i, nIndex, szLan);
       nIndex++;

    
       if (1 == m_struPDList.struPhyDiskInfo[i].byStatus)
       {
           strncpy(szLanCn, "正常", sizeof(szLanCn));
           strncpy(szLanEn, "Functional", sizeof(szLanEn));
           g_StringLanType(szLan, szLanCn, szLanEn);
       }
       m_ListPDInfo.SetItemText(i, nIndex, szLan);
       nIndex++;

       strncpy(szLan, (char*)m_struPDList.struPhyDiskInfo[i].byMode, sizeof(m_struPDList.struPhyDiskInfo[i].byMode));
       m_ListPDInfo.SetItemText(i, nIndex, szLan);
       nIndex++;


    }
*/
}

BOOL CSubDlgPDCfg::GetPDList()
{
//     if (!NET_DVR_GetPDList(m_lServerID, &m_struPDList))
//     {
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetPDList");
//         return FALSE;
//     }
//     else
//     {   
//         g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetPDList");
//         return TRUE;
//     }

    m_ListPDInfo.DeleteAllItems();
    m_listPDSlot.DeleteAllItems();
    m_dwPhyDiskNum = 0;
    memset(m_pStruPhyDiskInfo,0, sizeof(NET_DVR_PHY_DISK_INFO)* 64);
    m_lGetPhyDiskHanle = NET_DVR_StartRemoteConfig(m_lServerID,NET_DVR_GET_PHY_DISK_INFO,NULL,0,g_PhyDiskInfoCallback,this);
    if (m_lGetPhyDiskHanle < 0)
    {
          g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PHY_DISK_INFO Failed!");
          return FALSE;
    }
   
    g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PHY_DISK_INFO Success!");
    return TRUE;

}


BOOL CSubDlgPDCfg::GetAdapterInfo()
{
    DWORD dwReturn = 0;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_RAID_ADAPTER_INFO, 0, &m_struAdapterInfo, sizeof(m_struAdapterInfo), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_RAID_ADAPTER_INFO");
        return FALSE;
    }   
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_RAID_ADAPTER_INFO");
        return TRUE;
    }
}

void CSubDlgPDCfg::OnBtnFastConfig() 
{
    UpdateData(TRUE);
    if (m_csArrayName == "")
    {
        AfxMessageBox("Please input Array name");
    }
    m_lFastConfigHandle = NET_DVR_RaidFastConfig(m_lServerID, m_csArrayName.GetBuffer(0));
    if (-1 == m_lFastConfigHandle)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Fail to fast config");
        AfxMessageBox("Fail to Fast Config");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Succ to fast config");
        SetTimer(FASTCONFIG_TIMER, 1000, NULL);
    }
    
}

BOOL CSubDlgPDCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();

    m_ListPDInfo.SetExtendedStyle(m_ListPDInfo.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
    
    int nIndex = 0;
    char szLan[128] = {0};
    g_StringLanType(szLan, "硬盘槽位", "PD Slot");
    m_ListPDInfo.InsertColumn(nIndex, szLan,LVCFMT_LEFT,60,-1);
    nIndex++;
    
    g_StringLanType(szLan, "容量", "Capacity");
    m_ListPDInfo.InsertColumn(nIndex,szLan, LVCFMT_LEFT, 80, -1);
    nIndex++;
    
    g_StringLanType(szLan, "阵列",  "Array");
    m_ListPDInfo.InsertColumn(nIndex,szLan, LVCFMT_LEFT, 80, -1);
    nIndex++;

    g_StringLanType(szLan, "硬盘信息", "Info");
    m_ListPDInfo.InsertColumn(nIndex, szLan, LVCFMT_LEFT, 100, -1);
    nIndex++;
    
    g_StringLanType(szLan, "硬盘状态", "Disk status");
    m_ListPDInfo.InsertColumn(nIndex, szLan, LVCFMT_LEFT, 100, -1);
    nIndex++;
    
    g_StringLanType(szLan, "硬盘类型", "Mode");
    m_ListPDInfo.InsertColumn(nIndex, szLan, LVCFMT_LEFT, 100, -1);
    nIndex++;
    
    if (m_pStruPhyDiskInfo == NULL)
    {
        m_pStruPhyDiskInfo = new NET_DVR_PHY_DISK_INFO[64];
        if (m_pStruPhyDiskInfo == NULL)
        {
            return FALSE;
        }
        memset(m_pStruPhyDiskInfo,0, sizeof(NET_DVR_PHY_DISK_INFO)* 64);
    }
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSubDlgPDCfg::OnBtnCreateArray() 
{
    UpdateData(TRUE);
    if (m_csArrayName == "")
    {
        AfxMessageBox("Please input Array name");
    }
    memset(&m_struOperateArray, 0, sizeof(m_struOperateArray));
    strncpy((char*)m_struOperateArray.byName, m_csArrayName.GetBuffer(0), sizeof(m_struOperateArray.byName));
    m_struOperateArray.byRaidMode = m_comboRaidMode.GetItemData(m_comboRaidMode.GetCurSel());
 	m_struOperateArray.byInitMode = m_comboRaidInitMode.GetCurSel();

    int nSlotIndex = 0;
    for (DWORD i = 0; i < m_dwPhyDiskNum; i++)
    {
        if (m_listPDSlot.GetCheck(i))
        {
            if (m_struOperateArray.byPDCount < SUPPORT_PD_NUM)
            {
                m_struOperateArray.wPDSlots[m_struOperateArray.byPDCount] = m_pStruPhyDiskInfo[i].wPhySlot;
            }
            else
            {
                m_struOperateArray.wPDSlotsPartTwo[m_struOperateArray.byPDCount - SUPPORT_PD_NUM] = m_pStruPhyDiskInfo[i].wPhySlot;
            }
            m_struOperateArray.byPDCount++;
        }
    }

    
    if (!CreateArray())
	{
        AfxMessageBox("Fail to create array");
        return;
	}
    else
    {
        CurCfgUpdate();
    }
    
}

BOOL CSubDlgPDCfg::CreateArray()
{
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

BOOL CSubDlgPDCfg::CalcArraySize()
{
    unsigned __int64 dwSize = 0;
    if (!NET_DVR_CalcArraySize(m_lServerID, &m_struOperateArray, &dwSize))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_CalcArraySize");
        m_dwArraySize = (DWORD)(dwSize >> 20);
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_CalcArraySize");
        m_dwArraySize = (DWORD)(dwSize >> 20);
        return TRUE;
    }
}

BOOL CSubDlgPDCfg::SetSpareDisk()
{
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

void CSubDlgPDCfg::OnBtnSetSpareDisk() 
{
    UpdateData(TRUE);
    POSITION posPD = m_ListPDInfo.GetFirstSelectedItemPosition();
    
    char szLan[128] = {0};
    if (posPD == 0)
    {
        g_StringLanType(szLan, "请选择物理磁盘", "please select PD");
        AfxMessageBox(szLan);
        return;
    }
    int iCurSel = m_ListPDInfo.GetNextSelectedItem(posPD);

    if (iCurSel < 0 || iCurSel > m_dwPhyDiskNum) 
    {
        return;
    }
    m_struSpareDisk.wPDSlot = m_pStruPhyDiskInfo[iCurSel].wPhySlot;
    m_struSpareDisk.bySpareType = m_comboSpareType.GetCurSel() + 1;
    m_struSpareDisk.wArrayID = m_iArrayID;
    
    if (!SetSpareDisk())
    {
        AfxMessageBox("Fail to set spare disk");
        return;
    }
    else
    {
        CurCfgUpdate();
    }
}

void CSubDlgPDCfg::OnBtnDelSpareDisk() 
{
    POSITION posPD = m_ListPDInfo.GetFirstSelectedItemPosition();
    
    char szLan[128] = {0};
    if (posPD == 0)
    {
        g_StringLanType(szLan, "请选择物理磁盘", "please select PD");
        AfxMessageBox(szLan);
        return;
    }
    int iCurSel = m_ListPDInfo.GetNextSelectedItem(posPD);
    if (iCurSel < 0 || iCurSel > m_dwPhyDiskNum)
    {
        return;
    }
    m_struSpareDisk.wPDSlot = m_pStruPhyDiskInfo[iCurSel].wPhySlot;
    m_struSpareDisk.bySpareType = 0;
    if (!SetSpareDisk())
    {
        AfxMessageBox("Fail to set spare disk");
        return;
    }
    else
    {
        CurCfgUpdate();
    }

}

#if (_MSC_VER >= 1500)	//vs2008
void CSubDlgPDCfg::OnTimer(UINT_PTR nIDEvent)
#else
void CSubDlgPDCfg::OnTimer(UINT nIDEvent)
#endif
{
	// TODO: Add your message handler code here and/or call default
    if (nIDEvent == FASTCONFIG_TIMER)
    {
        DWORD dwState = 0;
        char szLan[128] = {0};
        NET_DVR_FastConfigProcess(m_lFastConfigHandle, &dwState);
        

        if (dwState >= 0 && dwState < 100)
        {
            //TRACE("dwState = %d", dwState); 
            sprintf(szLan, "Process:%d%", dwState);
            GetDlgItem(IDC_STATIC_PROCESS)->SetWindowText(szLan);
        }
        else if (dwState == PROCESS_SUCCESS)
        {
            TRACE("Fastconfig succ");
            GetDlgItem(IDC_STATIC_PROCESS)->SetWindowText("Success");
            NET_DVR_CloseFastConfig(m_lFastConfigHandle); 
            KillTimer(FASTCONFIG_TIMER);
            CurCfgUpdate();
        }
        else if (dwState == PROCESS_EXCEPTION)
        {
            GetDlgItem(IDC_STATIC_PROCESS)->SetWindowText("Fastconfig exception");
            NET_DVR_CloseFastConfig(m_lFastConfigHandle);
            KillTimer(FASTCONFIG_TIMER);
        }
        else if (dwState == PROCESS_FAILED)
        {
            GetDlgItem(IDC_STATIC_PROCESS)->SetWindowText("Fastconfig Failed");
            NET_DVR_CloseFastConfig(m_lFastConfigHandle);
            KillTimer(FASTCONFIG_TIMER);
        }
        else
        {
            GetDlgItem(IDC_STATIC_PROCESS)->SetWindowText("Fastconfig Failed");
            NET_DVR_CloseFastConfig(m_lFastConfigHandle);
            KillTimer(FASTCONFIG_TIMER);
        }
        //UpdateData(FALSE);
    }
    
    CDialog::OnTimer(nIDEvent);
}

void CSubDlgPDCfg::OnBtnCalcArraySize() 
{
    memset(&m_struOperateArray, 0, sizeof(m_struOperateArray));
    strncpy((char*)m_struOperateArray.byName, m_csArrayName.GetBuffer(0), sizeof(m_struOperateArray.byName));
    m_struOperateArray.byRaidMode = m_comboRaidMode.GetItemData(m_comboRaidMode.GetCurSel());
    
    int nSlotIndex = 0;
    for (DWORD i = 0; i < m_dwPhyDiskNum; i++)
    {
        if (m_listPDSlot.GetCheck(i))
        {
            if (m_struOperateArray.byPDCount < SUPPORT_PD_NUM)
            {
                m_struOperateArray.wPDSlots[m_struOperateArray.byPDCount] = m_pStruPhyDiskInfo[i].wPhySlot;
            }
            else
            {
                m_struOperateArray.wPDSlotsPartTwo[m_struOperateArray.byPDCount - SUPPORT_PD_NUM] = m_pStruPhyDiskInfo[i].wPhySlot;
            }
            m_struOperateArray.byPDCount++;
        }
    }
    
    if (!CalcArraySize())
    {
        AfxMessageBox("Fail to calc array size");
        return;
    }
    else
    {
        char szLan[128] = {0};
        sprintf(szLan, "Array size is %dG", m_dwArraySize);
        AfxMessageBox(szLan);
    }

}

void CSubDlgPDCfg::OnCancel()
{
    return;
}

LRESULT CSubDlgPDCfg::OnShowPhyDiskInfo(WPARAM wParam, LPARAM lParam)
{
    char szLan[1024] = {0};
    char szLanCn[1024] = {0};
    char szLanEn[1024] = {0};

    LPNET_DVR_PHY_DISK_INFO pStruPhyDiskInfo = (LPNET_DVR_PHY_DISK_INFO)wParam;

    DWORD dwListPDCount = m_ListPDInfo.GetItemCount();
    int nIndex = 0;
    DWORD dwListPDSlotCoun = m_listPDSlot.GetItemCount();
    
   
     m_pStruPhyDiskInfo[m_dwPhyDiskNum].wPhySlot = pStruPhyDiskInfo->wPhySlot;
     m_pStruPhyDiskInfo[m_dwPhyDiskNum].byType = pStruPhyDiskInfo->byType;
     m_pStruPhyDiskInfo[m_dwPhyDiskNum].byStatus = pStruPhyDiskInfo->byStatus;
     memcpy(m_pStruPhyDiskInfo[m_dwPhyDiskNum].byMode, pStruPhyDiskInfo->byMode, 40);
     m_pStruPhyDiskInfo[m_dwPhyDiskNum].dwHCapacity = pStruPhyDiskInfo->dwHCapacity;
     m_pStruPhyDiskInfo[m_dwPhyDiskNum].dwLCapacity = pStruPhyDiskInfo->dwLCapacity;
     m_pStruPhyDiskInfo[m_dwPhyDiskNum].wArrayID = pStruPhyDiskInfo->wArrayID;
     memcpy(m_pStruPhyDiskInfo[m_dwPhyDiskNum].byArrrayName, pStruPhyDiskInfo->byArrrayName, MAX_NAMELEN);
     m_dwPhyDiskNum++;
    sprintf(szLan, "%d", pStruPhyDiskInfo->wPhySlot);
    m_listPDSlot.InsertItem(dwListPDSlotCoun, szLan);

    sprintf(szLan, "%d",pStruPhyDiskInfo->wPhySlot);   
    m_ListPDInfo.InsertItem(dwListPDCount, szLan,nIndex);
    nIndex++;
    
    unsigned __int64 dwCapacity = 0;
    *((DWORD*)&dwCapacity) = pStruPhyDiskInfo->dwLCapacity;
    *((DWORD*)((char*)&dwCapacity + 4))  = pStruPhyDiskInfo->dwHCapacity;
    dwCapacity >>= 20;
    sprintf(szLan, "%I64u Gb", dwCapacity);
    m_ListPDInfo.SetItemText(dwListPDCount, nIndex, szLan);
    nIndex++;
    
    m_ListPDInfo.SetItemText(dwListPDCount, nIndex, LPCTSTR(pStruPhyDiskInfo->byArrrayName));
    nIndex++;
    
    if (0 == pStruPhyDiskInfo->byType)
    {
        //普通，1全局热备，2-阵列热备
        strncpy(szLanCn, "普通", sizeof(szLanCn));
        strncpy(szLanEn, "Normal", sizeof(szLanEn));
        g_StringLanType(szLan, szLanCn, szLanEn);
    }
    else if (1 == pStruPhyDiskInfo->byType)
    {
        strncpy(szLanCn, "全局热备", sizeof(szLanCn));
        strncpy(szLanEn, "Global spare disk", sizeof(szLanEn));
        g_StringLanType(szLan, szLanCn, szLanEn);
    }
    else if (2 == pStruPhyDiskInfo->byType)
    {
        strncpy(szLanCn, "阵列热备", sizeof(szLanCn));
        strncpy(szLanEn, "Global spare disk", sizeof(szLanEn));
        g_StringLanType(szLan, szLanCn, szLanEn);    
    }
    else if (3 == pStruPhyDiskInfo->byType)
    {
        strncpy(szLanCn, "阵列盘", sizeof(szLanCn));
        strncpy(szLanEn, "raid array disk", sizeof(szLanEn));
        g_StringLanType(szLan, szLanCn, szLanEn);    
    }
    m_ListPDInfo.SetItemText(dwListPDCount, nIndex, szLan);
    nIndex++;
    
    
    if (1 == pStruPhyDiskInfo->byStatus)
    {
        strncpy(szLanCn, "正常", sizeof(szLanCn));
        strncpy(szLanEn, "Functional", sizeof(szLanEn));
        g_StringLanType(szLan, szLanCn, szLanEn);
    }
    m_ListPDInfo.SetItemText(dwListPDCount, nIndex, szLan);
    nIndex++;
    
    strncpy(szLan, (char*)pStruPhyDiskInfo->byMode, sizeof(pStruPhyDiskInfo->byMode));
    m_ListPDInfo.SetItemText(dwListPDCount, nIndex, szLan);
    nIndex++;
    if (pStruPhyDiskInfo != NULL)
    {
        delete pStruPhyDiskInfo;
        pStruPhyDiskInfo = NULL;
    }
        
   
	return NULL;
}