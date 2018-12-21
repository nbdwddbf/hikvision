// SubDlgVDCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "SubDlgVDCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubDlgVDCfg dialog


CSubDlgVDCfg::CSubDlgVDCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubDlgVDCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSubDlgVDCfg)
	m_dwDstLunID = 0;
	m_dwSrcLunID = 0;
	m_strLunNewName = _T("");
	m_strArrayIDGroup = _T("");
	m_dwCapacity = 0;
	m_strNewWarrantIP = _T("");
	m_strNewDVRName = _T("");
	m_strOldDVRName = _T("");
	//}}AFX_DATA_INIT
    m_iDevIndex = -1;
    m_lServerID = -1;
    memset(&m_struVDList, 0, sizeof(m_struVDList));
}


void CSubDlgVDCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubDlgVDCfg)
	DDX_Control(pDX, IDC_LIST_VD_INFO, m_ListVDInfo);
	DDX_Text(pDX, IDC_EDIT_DST_LUN_ID, m_dwDstLunID);
	DDX_Text(pDX, IDC_EDIT_SRT_LUN_ID, m_dwSrcLunID);
	DDX_Text(pDX, IDC_EDIT_LUN_NEW_NAME, m_strLunNewName);
	DDX_Text(pDX, IDC_EDIT_ARRAY_ID, m_strArrayIDGroup);
	DDX_Text(pDX, IDC_EDIT_VD_CAPACITY, m_dwCapacity);
	DDX_Text(pDX, IDC_EDIT_LUN_NEW_WRRANT_IP, m_strNewWarrantIP);
	DDX_Text(pDX, IDC_EDIT_NEW_DVR_NAME, m_strNewDVRName);
	DDX_Text(pDX, IDC_EDIT_OLD_DVR_NAME, m_strOldDVRName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubDlgVDCfg, CDialog)
	//{{AFX_MSG_MAP(CSubDlgVDCfg)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_BN_CLICKED(IDC_BTN_REPAIR, OnBtnRepair)
	ON_BN_CLICKED(IDC_BUTTON_CLONE_LUN, OnButtonCloneLun)
	ON_NOTIFY(NM_CLICK, IDC_LIST_VD_INFO, OnClickListVdInfo)
	ON_BN_CLICKED(IDC_BUTTON_EXPAND, OnButtonExpand)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, OnButtonModify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubDlgVDCfg message handlers

BOOL CSubDlgVDCfg::CheckInitParam()
{
    m_iDevIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lServerID = g_struDeviceInfo[m_iDevIndex].lLoginID;
    
    return TRUE;
}

inline BOOL CSubDlgVDCfg::ValidIPv6(BYTE *ip)
{
	if (strlen((char *)ip) > 2 && strchr((char *)ip, ':') != NULL)
	{
		return TRUE;
	}
	return FALSE;
}

void CSubDlgVDCfg::CurCfgUpdate()
{
    if (!CheckInitParam())
    {
        return;
    }

    if (!GetVDList())
    {
        return;
    }
    
    m_ListVDInfo.DeleteAllItems();
    int nIndex = 0;
    char szLan[128] = {0};
    char szLanEn[128] = {0};
    char szLanCn[128] = {0};
    for (int i = 0; i < m_struVDList.dwCount; i++)
    {
        nIndex = 0;
        sprintf(szLan, "%d", i+1);   
        m_ListVDInfo.InsertItem(i, szLan,nIndex);
        nIndex++;
        
        sprintf(szLan, "%d", m_struVDList.struVDInfo[i].wSlot);
        m_ListVDInfo.SetItemText(i, nIndex, szLan);
        nIndex++;

        m_ListVDInfo.SetItemText(i, nIndex, (char*)m_struVDList.struVDInfo[i].byName);
        nIndex++;

        unsigned __int64 dwCapacity = 0;
        *((DWORD*)&dwCapacity) = m_struVDList.struVDInfo[i].dwLCapacity;
        *((DWORD*)((char*)&dwCapacity + 4))  = m_struVDList.struVDInfo[i].dwHCapacity;
        dwCapacity >>= 20;

        unsigned __int64 dwFreeSpace = 0;
        *((DWORD*)&dwFreeSpace) = m_struVDList.struVDInfo[i].dwLFreeSpace;
        *((DWORD*)((char*)&dwFreeSpace + 4))  = m_struVDList.struVDInfo[i].dwHFreeSpace;
        dwFreeSpace >>= 20;
        sprintf(szLan, "%I64u/%I64u Gb", dwFreeSpace, dwCapacity);
        m_ListVDInfo.SetItemText(i, nIndex, szLan);
        nIndex++;

        m_ListVDInfo.SetItemText(i, nIndex, (char*)m_struVDList.struVDInfo[i].byArrayName);
        nIndex++;

        if (0 == m_struVDList.struVDInfo[i].byStatus)
        {
            g_StringLanType(szLan, "正常", "Functional");
        }
        else if (1 == m_struVDList.struVDInfo[i].byStatus)
        {
            g_StringLanType(szLan, "降级", "Degrade");
        }
        else if (2 == m_struVDList.struVDInfo[i].byStatus)
        {
            g_StringLanType(szLan, "已删除", "Delete");
        }
        else if (3 == m_struVDList.struVDInfo[i].byStatus)
        {
            g_StringLanType(szLan, "磁盘丢失", "Missing");
        }
        else if (4 == m_struVDList.struVDInfo[i].byStatus)
        {
            g_StringLanType(szLan, "下线", "Offline");
        }
        else if (5 == m_struVDList.struVDInfo[i].byStatus)
        {
            g_StringLanType(szLan, "次正常", "Psrtially optimal");
        }
        else if (6 == m_struVDList.struVDInfo[i].byStatus)
        {
            g_StringLanType(szLan, "外来", "Foreign");
        }
		else if (7 == m_struVDList.struVDInfo[i].byStatus)
        {
            g_StringLanType(szLan, "异常", "Exception");
        }
		else if (0xff == m_struVDList.struVDInfo[i].byStatus)
        {
            g_StringLanType(szLan, "不存在", "Not exist");
        }

        m_ListVDInfo.SetItemText(i, nIndex, szLan);
        nIndex++;

        switch (m_struVDList.struVDInfo[i].byRaidMode)
        {
        case RAID0:
            strcpy(szLan, "RAID0");
            break;
        case RAID1:
            strcpy(szLan, "RAID1");
            break;
        case RAID10:
            strcpy(szLan, "RAID10");
            break;
        case RAID1E:
            strcpy(szLan, "RAID1E");
            break;
        case RAID5:
            strcpy(szLan, "RAID5");
            break;
        case RAID6:
            strcpy(szLan, "RAID6");
            break;
        case RAID50:
            strcpy(szLan, "RAID50");
            break;
        case JBOD:
            strcpy(szLan, "JBOD");
            break;
        case RAID60:
            strcpy(szLan, "RAID60");
            break;
        default:
            break;
        }
        m_ListVDInfo.SetItemText(i, nIndex, szLan);
        nIndex++;

        if (0 == m_struVDList.struVDInfo[i].byRepair)
        {
            strcpy(szLan, "No");
        }
        else 
        {
            strcpy(szLan, "Yes");
        }
        m_ListVDInfo.SetItemText(i, nIndex, szLan);
        nIndex++;

        ProcessBgaInfo(szLan, m_struVDList.struVDInfo[i].struBgaInfo);
        m_ListVDInfo.SetItemText(i, nIndex, szLan);
        nIndex++;

		if (0 == m_struVDList.struVDInfo[i].byUsage)
        {
            g_StringLanType(szLan, "IP SAN", "IP SAN");
        }
        else if (1 == m_struVDList.struVDInfo[i].byUsage)
        {
            g_StringLanType(szLan, "光纤SAN", "FC SAN");
        }
        else if (2 == m_struVDList.struVDInfo[i].byUsage)
        {
            g_StringLanType(szLan, "DVR网盘", "DVR Net Disk");
        }
        else if (3 == m_struVDList.struVDInfo[i].byUsage)
        {
            g_StringLanType(szLan, "NAS", "NAS");
        }
        else if (4 == m_struVDList.struVDInfo[i].byUsage)
        {
            g_StringLanType(szLan, "录像卷", "Record");
        }
		m_ListVDInfo.SetItemText(i, nIndex, szLan);
        nIndex++;

		// Block size
		sprintf(szLan, "%d", m_struVDList.struVDInfo[i].dwBlockSize);
        m_ListVDInfo.SetItemText(i, nIndex, szLan);
        nIndex++;

		// 授权IP
		if (ValidIPv6(m_struVDList.struVDInfo[i].struWarrantIP.byIPv6))
		{
			sprintf(szLan, "%s", m_struVDList.struVDInfo[i].struWarrantIP.byIPv6);
		}
		else
		{
			sprintf(szLan, "%s", m_struVDList.struVDInfo[i].struWarrantIP.sIpV4);
		}
		m_ListVDInfo.SetItemText(i, nIndex, szLan);
        nIndex++;

		//阵列组
		sprintf(szLan, "%s", m_struVDList.struVDInfo[i].szArrayGroup);
		m_ListVDInfo.SetItemText(i, nIndex, szLan);

    }
}


void CSubDlgVDCfg::ProcessBgaInfo(char *str, const NET_DVR_BGA_INFO &struBgaInfo)
{
    char szLan[128] = {0};
    char szLanCn[128] = {0};
    char szLanEn[128] = {0};
    if (struBgaInfo.byBgaState  == BGA_STATE_NONE)
    {
        strcpy(str, "No task");
    }
    else if (struBgaInfo.byBgaState == BGA_STATE_RUNNING)
    { 
        switch (struBgaInfo.byBga)
        {
        case BGA_REBUILD:
            sprintf(szLanCn, "重建:%d%", struBgaInfo.wBgaPercentage);
            sprintf(szLanEn, "Rebuild:%d%", struBgaInfo.wBgaPercentage);
            sprintf(szLan, szLanCn, szLanEn);
            break;
        case BGA_CONSISTENCY_FIX:
            sprintf(szLanCn, "一致性检查并修复:%d%", struBgaInfo.wBgaPercentage);
            sprintf(szLanEn, "consistency check and fix:%d%", struBgaInfo.wBgaPercentage);
            sprintf(szLan, szLanCn, szLanEn);
            break;
        case BGA_CONSISTENCY_CHECK:
            sprintf(szLanCn, "一致性检查:%d%", struBgaInfo.wBgaPercentage);
            sprintf(szLanEn, "consistency check:%d%", struBgaInfo.wBgaPercentage);
            sprintf(szLan, szLanCn, szLanEn);
            break;
        case BGA_INIT_QUICK:
            sprintf(szLanCn, "快速初始化:%d%", struBgaInfo.wBgaPercentage);
            sprintf(szLanEn, "Quick Init:%d%", struBgaInfo.wBgaPercentage);
            sprintf(szLan, szLanCn, szLanEn);
            break;
        case BGA_INIT_BACK:
            sprintf(szLanCn, "初始化:%d%", struBgaInfo.wBgaPercentage);
            sprintf(szLanEn, "Init:%d%", struBgaInfo.wBgaPercentage);
            sprintf(szLan, szLanCn, szLanEn);
            break;
        case BGA_MIGRATION:
            sprintf(szLanCn, "迁移:%d%", struBgaInfo.wBgaPercentage);
            sprintf(szLanEn, "Migration:%d%", struBgaInfo.wBgaPercentage);
            sprintf(szLan, szLanCn, szLanEn);
            break;
        case BGA_INIT_FORE:
            sprintf(szLan, "Init Fore:%d%", struBgaInfo.wBgaPercentage);
            break;
        case BGA_COPYBACK:
            sprintf(szLan, "CopyBack %d%",struBgaInfo.wBgaPercentage);
            break;
        default:
            sprintf(szLan, "bga[%d]bgaState[%d]wPercentage[%d]", struBgaInfo.byBga, struBgaInfo.byBgaState, struBgaInfo.wBgaPercentage);
            break;
        }
        strncpy(str, szLan, sizeof(szLan));
    }
    else if (struBgaInfo.byBgaState == BGA_STATE_ABORTED)
    {
        strcpy(str, "Task Aboted");
    }
    else if (struBgaInfo.byBgaState  == BGA_STATE_PAUSED)
    {
        strcpy(str, "Task pause");
}

}
BOOL CSubDlgVDCfg::GetVDList()
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


BOOL CSubDlgVDCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    m_ListVDInfo.SetExtendedStyle(m_ListVDInfo.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);
    
    int nIndex = 0;
    char szLan[128] = {0};

    g_StringLanType(szLan, "序号", "Index");
    m_ListVDInfo.InsertColumn(nIndex, szLan,LVCFMT_LEFT,60,-1);
    nIndex++;

    g_StringLanType(szLan, "槽位", "VD Slot");
    m_ListVDInfo.InsertColumn(nIndex, szLan,LVCFMT_LEFT,60,-1);
    nIndex++;

    g_StringLanType(szLan, "名称", "Name");
    m_ListVDInfo.InsertColumn(nIndex, szLan,LVCFMT_LEFT,60,-1);
    nIndex++;

    g_StringLanType(szLan, "容量", "Capacity");
    m_ListVDInfo.InsertColumn(nIndex, szLan,LVCFMT_LEFT,60,-1);
    nIndex++;

    g_StringLanType(szLan, "阵列", "Array");
    m_ListVDInfo.InsertColumn(nIndex, szLan,LVCFMT_LEFT,60,-1);
    nIndex++;

    g_StringLanType(szLan, "状态", "Status");
    m_ListVDInfo.InsertColumn(nIndex, szLan,LVCFMT_LEFT,60,-1);
    nIndex++;

    g_StringLanType(szLan, "类型", "Raid type");
    m_ListVDInfo.InsertColumn(nIndex, szLan,LVCFMT_LEFT,60,-1);
    nIndex++;

    g_StringLanType(szLan, "修复", "Repair");
    m_ListVDInfo.InsertColumn(nIndex, szLan,LVCFMT_LEFT,60,-1);
    nIndex++;

    g_StringLanType(szLan, "任务", "Task");
    m_ListVDInfo.InsertColumn(nIndex, szLan,LVCFMT_LEFT,60,-1);
    nIndex++;

	g_StringLanType(szLan, "用途", "Usage");
    m_ListVDInfo.InsertColumn(nIndex, szLan,LVCFMT_LEFT,60,-1);
    nIndex++;

	g_StringLanType(szLan, "块大小", "Block size");
    m_ListVDInfo.InsertColumn(nIndex, szLan,LVCFMT_LEFT,70,-1);
    nIndex++;

	g_StringLanType(szLan, "授权IP", "Warrant IP");
    m_ListVDInfo.InsertColumn(nIndex, szLan,LVCFMT_LEFT,80,-1);
    nIndex++;

	g_StringLanType(szLan, "阵列组", "Array Group");
    m_ListVDInfo.InsertColumn(nIndex, szLan,LVCFMT_LEFT,120,-1);
    nIndex++;
    
    return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSubDlgVDCfg::OnBtnDel() 
{
	POSITION posVD = m_ListVDInfo.GetFirstSelectedItemPosition();
    
    char szLan[128] = {0};
    if (posVD == 0)
    {
        g_StringLanType(szLan, "请选择虚拟磁盘", "please select VD");
        AfxMessageBox(szLan);
        return;
    }
    int iVDCurSel = m_ListVDInfo.GetNextSelectedItem(posVD);

    if (!DelVD(m_struVDList.struVDInfo[iVDCurSel].wSlot))
    {
        AfxMessageBox("Fail to  del VD");
        return;
    }
    else
    {
        CurCfgUpdate();
    }
}

void CSubDlgVDCfg::OnBtnRepair() 
{
    POSITION posVD = m_ListVDInfo.GetFirstSelectedItemPosition();
    
    char szLan[128] = {0};
    if (posVD == 0)
    {
        g_StringLanType(szLan, "请选择虚拟磁盘", "please select VD");
        AfxMessageBox(szLan);
        return;
    }
    int iVDCurSel = m_ListVDInfo.GetNextSelectedItem(posVD);
    
    if (!RepairVD(m_struVDList.struVDInfo[iVDCurSel].wSlot))
    {
        AfxMessageBox("Fail to  Rapair VD");
        return;
    }
    else
    {
        CurCfgUpdate();
    }
}

BOOL CSubDlgVDCfg::DelVD(DWORD dwID)
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

BOOL CSubDlgVDCfg::RepairVD(DWORD dwID)
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

void CSubDlgVDCfg::OnButtonCloneLun() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	NET_DVR_LUN_CLONE struLunClone;
	memset(&struLunClone, 0, sizeof(NET_DVR_LUN_CLONE));
	struLunClone.dwSize = sizeof(NET_DVR_LUN_CLONE);
	struLunClone.dwSrcLunID = m_dwSrcLunID;
	struLunClone.dwDstLunID = m_dwDstLunID;

	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_CLONE_LUN, &struLunClone, sizeof(NET_DVR_LUN_CLONE)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_CLONE_LUN ");
		g_StringLanType(szLan, "操作失败", "control failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_CLONE_LUN");
	}

	 
}

void CSubDlgVDCfg::OnClickListVdInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nItem = 0;
	CString strTemp;
	
	POSITION pos = m_ListVDInfo.GetFirstSelectedItemPosition();
	if (pos == NULL)
		TRACE0("No items were selected!\n");
	else
	{
		nItem = m_ListVDInfo.GetNextSelectedItem(pos);
		
		//显示信息
		strTemp = m_ListVDInfo.GetItemText(nItem, 1);
		m_dwSrcLunID = atoi(strTemp);

		m_strOldDVRName = m_ListVDInfo.GetItemText(nItem, 2);

		UpdateData(FALSE);
	}

	*pResult = 0;
}

void CSubDlgVDCfg::OnButtonExpand() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};

	unsigned __int64 dwCapacity =  ((unsigned __int64)m_dwCapacity) * 1024 *1024;

	NET_DVR_LUN_EXPAND struLunExpand;
	memset(&struLunExpand, 0, sizeof(NET_DVR_LUN_EXPAND));
	struLunExpand.dwSize = sizeof(NET_DVR_LUN_EXPAND);
	struLunExpand.dwLSize = *((DWORD*)&dwCapacity);
	struLunExpand.dwHSize = *((DWORD*)((char*)&dwCapacity + 4));
	struLunExpand.dwLunID = m_dwSrcLunID;
	memcpy(struLunExpand.szNewLunName, m_strLunNewName, MAX_NAMELEN);
	memcpy(struLunExpand.szArrayIDGroup, m_strArrayIDGroup, NAME_LEN);

	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_EXPAND_LUN, &struLunExpand, sizeof(NET_DVR_LUN_CLONE)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_EXPAND_LUN ");
		g_StringLanType(szLan, "操作失败", "control failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_EXPAND_LUN");
	}
}

void CSubDlgVDCfg::OnButtonModify() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	NET_DVR_DVR_NET_DISK_MODIFY struDVRModify;
	memset(&struDVRModify, 0, sizeof(NET_DVR_DVR_NET_DISK_MODIFY));
	struDVRModify.dwSize = sizeof(NET_DVR_DVR_NET_DISK_MODIFY);
	memcpy(struDVRModify.szOldDvrNetDiskName, m_strOldDVRName, MAX_NAMELEN);
	memcpy(struDVRModify.szNewDvrNetDiskName, m_strNewDVRName, MAX_NAMELEN);

	if (ValidIPv6((unsigned char*)m_strNewWarrantIP.GetBuffer(0)))
	{
		strncpy((char*)struDVRModify.struWarrantIP.byIPv6, m_strNewWarrantIP, 127);
	}
	else
	{
		strncpy(struDVRModify.struWarrantIP.sIpV4, m_strNewWarrantIP, 15);
	}
	
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_MODIFY_DVR_NET_DISK, &struDVRModify, sizeof(NET_DVR_DVR_NET_DISK_MODIFY)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_MODIFY_DVR_NET_DISK ");
		g_StringLanType(szLan, "操作失败", "control failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_MODIFY_DVR_NET_DISK");
	}
}
