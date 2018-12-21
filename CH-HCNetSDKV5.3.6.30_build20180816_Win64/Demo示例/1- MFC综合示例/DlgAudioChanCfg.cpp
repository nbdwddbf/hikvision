// DlgAudioChanCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAudioChanCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAudioChanCfg dialog

void TestAudioCfg (int iUserID)
{
	NET_DVR_AUDIO_CHAN_INFO struChanInfo  = {0};
	struChanInfo.dwSize = sizeof(NET_DVR_AUDIO_CHAN_INFO); 
	struChanInfo.dwChannel = 0xe0100; 
	NET_DVR_AUDIO_CHAN_CFG struChanCfg = {0}; 
	DWORD dwStatus; 

	if (!NET_DVR_GetDeviceConfig(iUserID, NET_DVR_GET_VW_AUDIO_CFG, 1, &struChanInfo, sizeof(struChanInfo), &dwStatus, &struChanCfg, sizeof(struChanCfg)))
	{
		return ; 
	}
	struChanCfg.byEnable = 1; 
	struChanCfg.byAudioSwitchType = 2; 
	struChanCfg.dwWindowNo = 0xff0101; 

	BOOL bRet = NET_DVR_SetDeviceConfig(iUserID, NET_DVR_SET_VW_AUDIO_CFG, 1, &struChanInfo, sizeof(struChanInfo), &dwStatus, &struChanCfg, sizeof(struChanCfg)); 
	return; 
}


CDlgAudioChanCfg::CDlgAudioChanCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAudioChanCfg::IDD, pParent)
	, m_dwTotalAudioChan( 0 )
{
	//{{AFX_DATA_INIT(CDlgAudioChanCfg)
	m_dwDeviceNO = 1;
	m_csChanName = _T("");
	m_BEanble = FALSE;
	m_dwSubWinNo = 0;
	m_dwWallNo = 1;
	m_dwWinNo = 1;
	//}}AFX_DATA_INIT
    memset(&m_struAllSystemInfo, 0, sizeof(m_struAllSystemInfo)); 
    
    memset(m_dwRecord, 0, sizeof(m_dwRecord));
	memset(m_dwAudioChan, 0, sizeof(m_dwAudioChan));

	m_lpChanCfgArray = NULL; 
    m_lpChanInfoArray = NULL; 
}

CDlgAudioChanCfg::~CDlgAudioChanCfg()
{
    if ( m_lpChanCfgArray )
    {
        delete []m_lpChanCfgArray; 
        m_lpChanCfgArray = NULL; 
    }
	
	if ( m_lpChanInfoArray )
	{
		delete []m_lpChanInfoArray; 
		m_lpChanInfoArray = NULL; 
	}


}

void CDlgAudioChanCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAudioChanCfg)
	DDX_Control(pDX, IDC_COMBO_VM_AUDIOCFG_SWITCH, m_cmbAudioCfgSwitch);
	DDX_Control(pDX, IDC_COMB_VM_AC_SUBBOARDNO, m_cmbSubBoardNo);
	DDX_Control(pDX, IDC_COMB_VW_AC_AUDIOCHANNO, m_cmbChanNo);
	DDX_Text(pDX, IDC_EDT_VM_AC_DEVICENO, m_dwDeviceNO);
	DDX_Text(pDX, IDC_EDT_VW_AC_CHANNAME, m_csChanName);
	DDX_Check(pDX, IDC_CHK_VM_AC_ENABLE, m_BEanble);
	DDX_Text(pDX, IDC_EDIT_VM_AUDIOCFG_SUBWINNO, m_dwSubWinNo);
	DDX_Text(pDX, IDC_EDIT_VM_AUDIOCFG_WALLNO, m_dwWallNo);
	DDX_Text(pDX, IDC_EDIT_VM_AUDIOCFG_WINNO, m_dwWinNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAudioChanCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgAudioChanCfg)
	ON_CBN_SELCHANGE(IDC_COMB_VM_AC_SUBBOARDNO, OnSelchangeSubboardNo)
	ON_BN_CLICKED(IDC_BUT_VM_AC_SAVE, OnButSave)
	ON_BN_CLICKED(IDC_BUT_VM_AC_SET, OnButSet)
	ON_BN_CLICKED(IDC_BUT_VW_AC_GETALL, OnButGetall)
	ON_BN_CLICKED(IDC_BUT_VM_AUDIO_STREAMCFG_SET, OnButStreamcfgSet)
	ON_CBN_SELCHANGE(IDC_COMBO_VM_AUDIOCFG_SWITCH, OnSelchangeAudiocfgSwitch)
	ON_CBN_SELCHANGE(IDC_COMB_VW_AC_AUDIOCHANNO, OnSelChannelChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAudioChanCfg message handlers

BOOL CDlgAudioChanCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
//	TestAudioCfg (m_lServerID); 
	// TODO: Add extra initialization here
    int i=0; 
    m_cmbAudioCfgSwitch.SetItemData(i, i+1); //前端源方式
    m_cmbAudioCfgSwitch.SetItemData(i+1, i+2); //窗口解码源方式
   
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex(); 
	m_lServerID = g_struDeviceInfo[m_iDeviceIndex].lLoginID; 
	GetAudioChanNum();
    m_cmbSubBoardNo.SetCurSel(0); 
    OnSelchangeSubboardNo(); 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgAudioChanCfg::GetAudioChanNum()
{
    CString csTemp; 
    //获取子系统信息
    if (!NET_DVR_MatrixGetSubSystemInfo_V40(m_lServerID, &m_struAllSystemInfo))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_MatrixGetSubSystemInfo_V40");
        MessageBox("NET_DVR_MatrixGetSubSystemInfo_V40 FAILED");
        return FALSE; 
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_MatrixGetSubSystemInfo_V40");
        m_cmbSubBoardNo.ResetContent(); 
//         for (int i=0; i<m_struAllSystemInfo.byBoardNum; i++)
//         {
//             csTemp.Format("%s", m_struAllSystemInfo.byBoardStartNum + i); 
//             m_cmbSubBoardNo.AddString(csTemp); 
//             m_cmbSubBoardNo.SetItemData(i, m_struAllSystemInfo.byBoardStartNum + i); 
//         }
		 
        for (int i=0, j=0; i<MAX_SUBSYSTEM_NUM_V40; i++)
        {
            if ( m_struAllSystemInfo.struSubSystemInfo[i].byBelongBoard != 0xff && m_struAllSystemInfo.struSubSystemInfo[i].byAudioChanNums != 0)
            {
                csTemp.Format("%d", m_struAllSystemInfo.struSubSystemInfo[i].byBelongBoard); 
                m_cmbSubBoardNo.AddString(csTemp); 
                m_cmbSubBoardNo.SetItemData(j++, i); 		
            }
        }
        return TRUE; 
	}
}

void CDlgAudioChanCfg::OnSelchangeSubboardNo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
    CString  csTemp ; 
    m_cmbChanNo.ResetContent(); 
    int  iSel = m_cmbSubBoardNo.GetItemData(m_cmbSubBoardNo.GetCurSel() );
    LPNET_DVR_SUBSYSTEMINFO_V40 lpSubSysInfo = &m_struAllSystemInfo.struSubSystemInfo[iSel]; 
    for (int i=0; i<lpSubSysInfo->byAudioChanNums; i++)
    {
        csTemp.Format("%d", i+lpSubSysInfo->byAudioChanStartNum); 
        m_cmbChanNo.AddString(csTemp); 
        m_cmbChanNo.SetItemData(i, i+lpSubSysInfo->byAudioChanStartNum); 
    }
    m_cmbChanNo.SetCurSel(0); 
    UpdateData(FALSE); 
	OnSelChannelChange();
}

LPNET_DVR_AUDIO_CHAN_CFG CDlgAudioChanCfg::GetChanCfg()
{
    if ( !m_lpChanCfgArray)
    {
        try
        {
            m_lpChanCfgArray = new NET_DVR_AUDIO_CHAN_CFG[MAX_ID_COUNT]; 
            memset(m_lpChanCfgArray, 0, sizeof(NET_DVR_AUDIO_CHAN_CFG)*MAX_ID_COUNT); 
        }
        catch (...)
        {
        	 MessageBox("CDlgAudioChanCfg::GetChanCfg Failed to malloc memory");
        }
    }
    return m_lpChanCfgArray; 
}
LPNET_DVR_AUDIO_CHAN_INFO CDlgAudioChanCfg::GetChanInfo()
{
    if ( !m_lpChanInfoArray)
    {
        try
        {
            m_lpChanInfoArray = new NET_DVR_AUDIO_CHAN_INFO[MAX_ID_COUNT]; 
        }
        catch (...)
        {
            MessageBox("CDlgAudioChanCfg::GetChanInfo Failed to malloc memory");
        }
    }
    return m_lpChanInfoArray; 
}
//获取所有子板的所有音频号 
LPNET_DVR_AUDIO_CHAN_INFO CDlgAudioChanCfg::GetInitChanInfo()
{   
    UpdateData(TRUE); 
    LPNET_DVR_AUDIO_CHAN_INFO lpInfo = GetChanInfo(); 
	DWORD dwCount = 0; 
	DWORD dwVaildSubCount = m_cmbSubBoardNo.GetCount(); 
	for (int i=0; i<dwVaildSubCount; i++)
	{
		DWORD dwSubIndexTemp = m_cmbSubBoardNo.GetItemData(i); 
		DWORD dwSubBoardNo = m_struAllSystemInfo.struSubSystemInfo[dwSubIndexTemp].byBelongBoard;
		LPNET_DVR_SUBSYSTEMINFO_V40 lpSubSysInfo = &m_struAllSystemInfo.struSubSystemInfo[dwSubIndexTemp]; 
		for (int j=0; j<lpSubSysInfo->byAudioChanNums; j++ )
		{
			lpInfo[dwCount].dwSize = sizeof(*lpInfo);
			lpInfo[dwCount].dwChannel = ((m_struAllSystemInfo.struSubSystemInfo[dwSubIndexTemp].byAudioChanStartNum+j) &0xffff) + (dwSubBoardNo<<16) + (1 << 24); 
			dwCount ++; 
		}	
	}
	m_dwTotalAudioChan = dwCount; 
    return lpInfo; 
}
//获取某个音频通道号
LPNET_DVR_AUDIO_CHAN_INFO CDlgAudioChanCfg::GetInitChanInfo(DWORD dwChanNo)
{
    UpdateData(TRUE); 
    LPNET_DVR_AUDIO_CHAN_INFO lpInfo = GetChanInfo();
    DWORD dwIndex = m_cmbSubBoardNo.GetCurSel(); 
    DWORD dwSubBoardNo = m_cmbSubBoardNo.GetItemData(dwIndex);
    lpInfo->dwSize = sizeof(*lpInfo);
    lpInfo->dwChannel = (dwChanNo&0xffff) + (dwSubBoardNo<<16) + (m_dwDeviceNO << 24); 
    return lpInfo; 
}  
//获取修改过的音频通道号
LPNET_DVR_AUDIO_CHAN_INFO CDlgAudioChanCfg::GetInitChanInfo(bool BMod)
{
    UpdateData(TRUE); 
    LPNET_DVR_AUDIO_CHAN_INFO lpInfo = GetChanInfo(); 
    DWORD iModCount = GetChangeItemNum();
    if ( ! iModCount )
    {
        return NULL; 
    }
//    DWORD dwIndex = m_cmbSubBoardNo.GetCurSel(); 
    DWORD dwIndex = m_cmbSubBoardNo.GetItemData(m_cmbSubBoardNo.GetCurSel() );
//    DWORD dwSubBoardNo = m_cmbSubBoardNo.GetItemData(dwIndex);
    DWORD dwSubBoardNo = m_struAllSystemInfo.struSubSystemInfo[dwIndex].byBelongBoard;
    DWORD dwChanNo = 0; 
    for (int i=0, j=0; i<MAX_ID_COUNT; i++)
    {
        if (m_dwRecord[i] == 1)
        {
            lpInfo[j].dwSize = sizeof(*lpInfo);
            dwChanNo = m_cmbChanNo.GetItemData(i); 
//            lpInfo[j].dwChannel =  (dwChanNo&0xffff) + (dwSubBoardNo<<16) + (m_dwDeviceNO << 24);
			lpInfo[j].dwChannel = m_dwAudioChan[i]; 
            j++;  
         }
    }
    return lpInfo; 
} 

BOOL CDlgAudioChanCfg::GetAll()
{
    UpdateData(TRUE); 
    char szLan[128]; 
//   DWORD dwIndex = m_cmbSubBoardNo.GetCurSel(); 
//    DWORD dwCount = m_struAllSystemInfo.struSubSystemInfo[dwIndex].byAudioChanNums; 
    BOOL BGetAll = TRUE; 
    LPNET_DVR_AUDIO_CHAN_CFG lpGetAll = GetChanCfgSend(BGetAll);  
    LPNET_DVR_AUDIO_CHAN_INFO lpChanInfo = GetInitChanInfo(); 
	if ( ! m_dwTotalAudioChan )
	{
		MessageBox("没有音频通道号"); 
		return TRUE; 
	}
    if (!NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_VW_AUDIO_CFG, m_dwTotalAudioChan, lpChanInfo, m_dwTotalAudioChan*sizeof(*lpChanInfo), m_dwStatus, lpGetAll, m_dwTotalAudioChan*sizeof(*lpGetAll)))
    {
        sprintf(szLan, "获取所有失败, Error code %d",NET_DVR_GetLastError());
        AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_VW_AUDIO_CFG");	
        return FALSE; 
    }
    else
    {
		for (int i=0; i<m_dwTotalAudioChan; i++)
		{
			if ( m_dwStatus[i] != 0)
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "AudioChannel %d, status %d", lpChanInfo[i], m_dwStatus[i]);		
			}
		}
		g_pMainDlg->AddLog(m_iDeviceIndex,	OPERATION_SUCC_T, "NET_DVR_GET_VW_AUDIO_CFG");	
        //删除所哟修改记录
        memset(m_dwRecord, 0xff, sizeof(m_dwRecord)); 
        memcpy( GetChanCfg(), lpGetAll, m_dwTotalAudioChan*sizeof(*lpGetAll)); 
        UpdateCfg(); 
    }
    return TRUE; 
} 

BOOL CDlgAudioChanCfg::Save()
{
    UpdateData(TRUE); 
	DWORD dwSubData = m_cmbSubBoardNo.GetItemData(m_cmbSubBoardNo.GetCurSel());
	DWORD dwChanNo =  m_cmbChanNo.GetItemData( m_cmbChanNo.GetCurSel() );
	DWORD dwRecordIndex  = GetRecordIndex(dwSubData,  dwChanNo); 
	
//	DWORD dwIndex = m_cmbChanNo.GetCurSel(); 
	DWORD dwIndex = dwRecordIndex;
    LPNET_DVR_AUDIO_CHAN_CFG lpChanCfg = GetChanCfg();
    lpChanCfg[dwIndex].byEnable = m_BEanble; 
    strcpy((char *)lpChanCfg[dwIndex].sChanName, (LPCSTR)m_csChanName); 
    lpChanCfg[dwIndex].byAudioSwitchType = m_cmbAudioCfgSwitch.GetItemData(m_cmbAudioCfgSwitch.GetCurSel()); 
    if ( lpChanCfg[dwIndex].byAudioSwitchType == 2 )
    {
        lpChanCfg[dwIndex].dwWindowNo = (m_dwWallNo << 24) + ((m_dwSubWinNo&0xff)<<16) + (m_dwWinNo&0xffff); 
    }
// 	DWORD dwSubData = m_cmbSubBoardNo.GetItemData(m_cmbSubBoardNo.GetCurSel());
// 	DWORD dwChanNo =  m_cmbChanNo.GetItemData(dwIndex);
// 	DWORD dwRecordIndex  = GetRecordIndex(dwSubData,  dwChanNo); 
	DWORD dwSubBoardNo =  m_struAllSystemInfo.struSubSystemInfo[dwSubData].byBelongBoard;
	m_dwAudioChan[dwRecordIndex] = (dwChanNo&0xffff) + (dwSubBoardNo<<16) + ((m_dwDeviceNO&0xff) << 24);;
    m_dwRecord[dwRecordIndex] = 1; 
    return TRUE; 
}

BOOL CDlgAudioChanCfg::Refresh()
{
    return TRUE; 
}

BOOL CDlgAudioChanCfg::Set()
{
    UpdateData(TRUE); 
    char szLan[128]; 
    //如果给库传零或怎么样
    DWORD dwCount = GetChangeItemNum(); 
    LPNET_DVR_AUDIO_CHAN_CFG lpChanCfg = GetChanCfgSend();
    bool bMod = TRUE; 
    LPNET_DVR_AUDIO_CHAN_INFO lpChanInfo = GetInitChanInfo(bMod); 
	if ( dwCount == 0 )
	{
		MessageBox("没有修改部分发送"); 
		return FALSE; 
	}
    if (!NET_DVR_SetDeviceConfig(m_lServerID, NET_DVR_SET_VW_AUDIO_CFG, dwCount, lpChanInfo, dwCount*sizeof(*lpChanInfo), m_dwStatus, lpChanCfg, dwCount*sizeof(*lpChanCfg)))
    {
        sprintf(szLan, "设置修失败, Error code %d",NET_DVR_GetLastError());
        AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_VW_AUDIO_CFG");		
    }
    else
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_VW_AUDIO_CFG");
		BOOL BError = FALSE; 
		CString csShow ; 
		for (int i=0; i<dwCount; i++)
		{

			LPNET_DVR_AUDIO_CHAN_INFO lpChanInfoTemp = lpChanInfo  + i; 
			if ( m_dwStatus[i] != 0 )
			{
				CString csTemp ; 
				csTemp.Format("DeviceNo[%d] boardNo[%d] AudioChan[%d] dwStatus[%d]\r\n",(lpChanInfoTemp->dwChannel>>24),\
					(lpChanInfoTemp->dwChannel>>16)&0xff, (lpChanInfoTemp->dwChannel&0xffff),  m_dwStatus[i]);
				csShow += csTemp; 
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "DeviceNo[%d] boardNo[%d] AudioChan[%d] dwStatus[%d]",(lpChanInfoTemp->dwChannel>>24),\
					(lpChanInfoTemp->dwChannel>>16)&0xff, (lpChanInfoTemp->dwChannel&0xffff),  m_dwStatus[i]);	
				BError = TRUE; 
			}
		}
		if ( BError)
		{
			MessageBox(csShow); 
		}
        memset(m_dwRecord, 0, sizeof(m_dwRecord));     
    }
    delete [] lpChanCfg;  
    return TRUE; 
}


BOOL CDlgAudioChanCfg::UpdateCfg()
{
    UpdateData(TRUE); 
    LPNET_DVR_AUDIO_CHAN_CFG lpChanCfg = GetChanCfg();
	DWORD dwSubData = m_cmbSubBoardNo.GetItemData(m_cmbSubBoardNo.GetCurSel());
	DWORD dwChanNo =  m_cmbChanNo.GetItemData( m_cmbChanNo.GetCurSel() );
	DWORD dwIndex  = GetRecordIndex(dwSubData,  dwChanNo); 
//    DWORD dwIndex = m_cmbChanNo.GetCurSel(); 

    m_csChanName.Format("%s", (char *)lpChanCfg[dwIndex].sChanName); 
    m_BEanble = lpChanCfg[dwIndex].byEnable; 
    m_cmbAudioCfgSwitch.SetCurSel(lpChanCfg[dwIndex].byAudioSwitchType-1); 
    m_dwWallNo = lpChanCfg[dwIndex].dwWindowNo >> 24; 
    m_dwSubWinNo = (lpChanCfg[dwIndex].dwWindowNo >> 16) &0xff; 
    m_dwWinNo = lpChanCfg[dwIndex].dwWindowNo &0xffff; 
    UpdateData(FALSE); 
    return TRUE; 
}

DWORD CDlgAudioChanCfg::GetChangeItemNum()
{
    int iModCount = 0; 
    for (int i=0; i<MAX_ID_COUNT; i++)
    {
        if (m_dwRecord[i] == 1)
        {
            iModCount ++; 
        }
    }
    return iModCount; 
} 

LPNET_DVR_AUDIO_CHAN_CFG CDlgAudioChanCfg::GetChanCfgSend(BOOL BAll)
{
    LPNET_DVR_AUDIO_CHAN_CFG  lpChanCfg = GetChanCfg(); 
    LPNET_DVR_AUDIO_CHAN_CFG lpChanCfgSend = NULL;
    if ( BAll)
    {
        lpChanCfgSend =  new NET_DVR_AUDIO_CHAN_CFG[MAX_ID_COUNT]; 
        memcpy(lpChanCfgSend, lpChanCfg, MAX_ID_COUNT*sizeof(*lpChanCfg)); 
        return lpChanCfgSend; 
    }

    int iModCount = GetChangeItemNum(); 
    if ( ! iModCount )
    {
        return NULL; 
    }

    lpChanCfgSend = new NET_DVR_AUDIO_CHAN_CFG[iModCount]; 
    for (int i=0,  j=0; i<MAX_ID_COUNT; i++)
    {
        if (m_dwRecord[i] == 1)
        {
            memcpy(lpChanCfgSend+j, lpChanCfg+i, sizeof(*lpChanCfgSend));
            lpChanCfgSend[j].dwSize = sizeof(*lpChanCfgSend); 
            j++;  
        }
    }
    return lpChanCfgSend; 
}

void CDlgAudioChanCfg::OnButSave() 
{
	// TODO: Add your control notification handler code here
	Save(); 
}

void CDlgAudioChanCfg::OnButSet() 
{
	// TODO: Add your control notification handler code here
	Set(); 
}

void CDlgAudioChanCfg::OnButGetall() 
{
	// TODO: Add your control notification handler code here
	GetAll(); 
}

void CDlgAudioChanCfg::OnButStreamcfgSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE); 
	DWORD dwSubBoardNo = m_cmbSubBoardNo.GetItemData(m_cmbSubBoardNo.GetCurSel()); 
	DWORD dwChanNo = m_cmbChanNo.GetItemData(m_cmbChanNo.GetCurSel() );
	int dwIndex = GetRecordIndex(dwSubBoardNo, dwChanNo);
	if ( dwIndex == -1)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "dwSubBoardNo = %d,dwChanNo = %d , No Record Index", dwSubBoardNo, dwChanNo);	
		return ; 
	}
//    DWORD dwIndex = m_cmbChanNo.GetCurSel(); 
    LPNET_DVR_AUDIO_CHAN_CFG lpChanCfg = GetChanCfg();
	m_DlgUpStreamCfg.SetStreamCfg(lpChanCfg[dwIndex].struAudioSrcInfo);
    if ( m_DlgUpStreamCfg.DoModal() == IDOK )
    {
        memcpy(&lpChanCfg[dwIndex].struAudioSrcInfo, &m_DlgUpStreamCfg.GetStreamCfg(), sizeof(lpChanCfg[dwIndex].struAudioSrcInfo)); 
    }

}

void CDlgAudioChanCfg::OnSelchangeAudiocfgSwitch() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
    int iSel = m_cmbAudioCfgSwitch.GetCurSel(); 
    GetDlgItem(IDC_BUT_VM_AUDIO_STREAMCFG_SET)->EnableWindow(FALSE); 
    GetDlgItem(IDC_EDIT_VM_AUDIOCFG_WALLNO)->EnableWindow(FALSE); 
    GetDlgItem(IDC_EDIT_VM_AUDIOCFG_SUBWINNO)->EnableWindow(FALSE); 
    GetDlgItem(IDC_EDIT_VM_AUDIOCFG_WINNO)->EnableWindow(FALSE); 
    if (iSel == 0)
    {
        GetDlgItem(IDC_BUT_VM_AUDIO_STREAMCFG_SET)->EnableWindow(TRUE); 
    }
    else if ( iSel == 1)
    {
        GetDlgItem(IDC_EDIT_VM_AUDIOCFG_WALLNO)->EnableWindow(TRUE); 
        GetDlgItem(IDC_EDIT_VM_AUDIOCFG_SUBWINNO)->EnableWindow(TRUE); 
        GetDlgItem(IDC_EDIT_VM_AUDIOCFG_WINNO)->EnableWindow(TRUE); 
    }
}

void TestAudioCfg ()
{
	
}

int  CDlgAudioChanCfg::GetRecordIndex(DWORD dwSubIndex, DWORD dwChan)
{
	int iIndex = 0; 
	int  iSel = m_cmbSubBoardNo.GetItemData(m_cmbSubBoardNo.GetCurSel() );
	CString csTemp; 
	DWORD dwVaildSubCount = m_cmbSubBoardNo.GetCount(); 
	for (int i=0; i<dwVaildSubCount; i++)
	{
		DWORD dwSubIndexTemp = m_cmbSubBoardNo.GetItemData(i); 
		LPNET_DVR_SUBSYSTEMINFO_V40 lpSubSysInfo = &m_struAllSystemInfo.struSubSystemInfo[dwSubIndexTemp]; 
		if ( dwSubIndexTemp == dwSubIndex )
		{		
			for (int i=0; i<lpSubSysInfo->byAudioChanNums; i++ , iIndex++)
			{
				if ( i+lpSubSysInfo->byAudioChanStartNum == dwChan )
				{
					return iIndex; 
				}
			}
		}
		else
		{
			iIndex += lpSubSysInfo->byAudioChanNums;
		}
	}
	return -1; 
}



void CDlgAudioChanCfg::OnSelChannelChange()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE); 
	DWORD dwSubBoardNo = m_cmbSubBoardNo.GetItemData(m_cmbSubBoardNo.GetCurSel()); 
	DWORD dwChanNo = m_cmbChanNo.GetItemData(m_cmbChanNo.GetCurSel() );
	int iRecordIndex = GetRecordIndex(dwSubBoardNo, dwChanNo);
	if ( iRecordIndex == -1)
	{
		 g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "dwSubBoardNo = %d,dwChanNo = %d , No Record Index", dwSubBoardNo, dwChanNo);	
		 return ; 
	}
	LPNET_DVR_AUDIO_CHAN_CFG lpChanCfg = GetChanCfg();
	m_csChanName.Format("%s", (char *)lpChanCfg[iRecordIndex].sChanName); 
	m_BEanble = lpChanCfg[iRecordIndex].byEnable; 
	m_cmbAudioCfgSwitch.SetCurSel(lpChanCfg[iRecordIndex].byAudioSwitchType-1); 
	m_dwWallNo = lpChanCfg[iRecordIndex].dwWindowNo >> 24; 
	m_dwSubWinNo = (lpChanCfg[iRecordIndex].dwWindowNo >> 16) &0xff; 
	m_dwWinNo = lpChanCfg[iRecordIndex].dwWindowNo &0xffff; 
	UpdateData(FALSE); 
}
















