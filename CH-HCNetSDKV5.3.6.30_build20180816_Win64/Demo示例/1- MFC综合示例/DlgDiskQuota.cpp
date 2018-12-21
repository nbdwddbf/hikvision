// DlgDiskQuota.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgDiskQuota.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDiskQuota dialog


CDlgDiskQuota::CDlgDiskQuota(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDiskQuota::IDD, pParent)
    , m_dwPicPeriod(0)
    , m_dwReocrdPeriod(0)
{
	//{{AFX_DATA_INIT(CDlgDiskQuota)
	m_iPicCapacity = 0;
	m_iRecordCapacity = 0;
	m_iPicUsed = 0;
	m_iRecordUsed = 0;
	m_byDrawPer = 0;
	m_byPicPer = 0;
	m_byRecordPer = 0;
	m_byRecordQuotaRatio = 0;
	m_byPicQuotaRatio = 0;
	m_iAddInfoCapacity = 0;
	m_byAddInfoQuotaRatio = 0;
	m_iAddInfoUsed = 0;
	m_bAllChann = FALSE;
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_lChannel = -1;
    m_iDevIndex = -1;
    m_lChannelNum = -1;
    memset(&m_struDiskQuotaCfg, 0, sizeof(m_struDiskQuotaCfg));
}


void CDlgDiskQuota::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgDiskQuota)
    DDX_Control(pDX, IDC_COMBO_ADDINFO_TYPE, m_comboAddInfoType);
    DDX_Control(pDX, IDC_COMBO_RECORD_TYPE, m_comboRecordType);
    DDX_Control(pDX, IDC_COMBO_PIC_TYPE, m_comboPicType);
    DDX_Text(pDX, IDC_EDIT_PIC_CAPACITY, m_iPicCapacity);
    DDX_Text(pDX, IDC_EDIT_RECORD_CAPACITY, m_iRecordCapacity);
    DDX_Text(pDX, IDC_EDIT_USED_PIC, m_iPicUsed);
    DDX_Text(pDX, IDC_EDIT_USED_RECORD, m_iRecordUsed);
    DDX_Text(pDX, IDC_EDIT_DRAW_P, m_byDrawPer);
    DDX_Text(pDX, IDC_EDIT_PICCTURE_P, m_byPicPer);
    DDX_Text(pDX, IDC_EDIT_RECORD_P, m_byRecordPer);
    DDX_Text(pDX, IDC_EDIT_RECORD_QUOTA_RATIO, m_byRecordQuotaRatio);
    DDX_Text(pDX, IDC_EDIT_PIC_QUOTA_RATIO, m_byPicQuotaRatio);
    DDX_Text(pDX, IDC_EDIT_ADDINFO_CAPACITY, m_iAddInfoCapacity);
    DDX_Text(pDX, IDC_EDIT_ADDINFO_QUOTA_RATIO, m_byAddInfoQuotaRatio);
    DDX_Text(pDX, IDC_EDIT_USED_ADDINFO, m_iAddInfoUsed);
    DDX_Check(pDX, IDC_CHECK_ALL_CHANN, m_bAllChann);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_STORAGE_PERIOD_PIC, m_dwPicPeriod);
    DDX_Text(pDX, IDC_EDIT_STORAGE_PERIOD_RECORD, m_dwReocrdPeriod);
}


BEGIN_MESSAGE_MAP(CDlgDiskQuota, CDialog)
	//{{AFX_MSG_MAP(CDlgDiskQuota)
	ON_BN_CLICKED(IDC_BTN_QUOTA_CFG, OnBtnQuotaCfg)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnBtnQuotaUpgrade)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnBtnQuotaExit)
	ON_BN_CLICKED(IDC_BTN_QUOTA_CFG2, OnBtnDrawFrameQuotaCfg)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE2, OnButtonDrawFrameUpdate)
	ON_BN_CLICKED(IDC_BTN_DRAW_FRAME_QUOTA_CFG, OnBtnDrawFrameQuotaCfg)
	ON_BN_CLICKED(IDC_BUTTON_DRAW_FRAME_UPDATE, OnButtonDrawFrameUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDiskQuota message handlers

BOOL CDlgDiskQuota::OnInitDialog() 
{
	CDialog::OnInitDialog();
    char szLan[128] = {0};
	  
    InitWnd();

    if (!GetDiskQuotaCfg(m_lChannel, m_struDiskQuotaCfg))
    {
		g_StringLanType(szLan, "ªÒ»°¥≈≈Ã≈‰∂Ó≈‰÷√ ß∞‹", "Fail to get disk quota configure");  
        AfxMessageBox(szLan);
    }

	SetDiskQuotaCfgToWnd(m_struDiskQuotaCfg);

	OnButtonDrawFrameUpdate();

    UpdateData(FALSE);	
    return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgDiskQuota::InitWnd()
{
    char szLan[128] = {0};
    int nIndex = 0;
    m_comboPicType.ResetContent();
	g_StringLanType(szLan, "∞¥»›¡ø", " By Capacity");
    m_comboPicType.InsertString(nIndex, szLan);
    m_comboPicType.SetItemData(nIndex, 1);

	nIndex++;
	g_StringLanType(szLan, "∞¥±»¿˝", " By proportion");
    m_comboPicType.InsertString(nIndex, szLan);
    m_comboPicType.SetItemData(nIndex, 2);

	nIndex++;
	g_StringLanType(szLan, "∞¥ ±º‰", " By Time");
    m_comboPicType.InsertString(nIndex, szLan);
    m_comboPicType.SetItemData(nIndex, 3);
	
    nIndex= 0;
    m_comboRecordType.ResetContent();
	g_StringLanType(szLan, "∞¥»›¡ø", " By Capacity");
    m_comboRecordType.InsertString(nIndex, szLan);
    m_comboRecordType.SetItemData(nIndex, 1);

	nIndex++;
	g_StringLanType(szLan, "∞¥±»¿˝", " By proportion");
    m_comboRecordType.InsertString(nIndex, szLan);
    m_comboRecordType.SetItemData(nIndex, 2);

    nIndex++;
    g_StringLanType(szLan, "∞¥ ±º‰", " By Time");
    m_comboRecordType.InsertString(nIndex, szLan);
    m_comboRecordType.SetItemData(nIndex, 3);

    nIndex= 0;
    m_comboAddInfoType.ResetContent();
    g_StringLanType(szLan, "∞¥»›¡ø", " By Capacity");
    m_comboAddInfoType.InsertString(nIndex, szLan);
    m_comboAddInfoType.SetItemData(nIndex, 1);
    
    nIndex++;
    g_StringLanType(szLan, "∞¥±»¿˝", " By proportion");
    m_comboAddInfoType.InsertString(nIndex, szLan);
    m_comboAddInfoType.SetItemData(nIndex, 2);

}

BOOL CDlgDiskQuota::GetDiskQuotaCfg(LONG lChannel, NET_DVR_DISK_QUOTA_CFG &struDiskQuotaCfg)
{
    DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_DISK_QUOTA_CFG, lChannel, &struDiskQuotaCfg, sizeof(struDiskQuotaCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_DISK_QUOTA_CFG");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_DISK_QUOTA_CFG");
        return FALSE;
    }
    return TRUE;
}

BOOL CDlgDiskQuota::SetDiskQuotaCfg(LONG lChannel, NET_DVR_DISK_QUOTA_CFG &struDiskQuotaCfg)
{
    if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_DISK_QUOTA_CFG, lChannel, &struDiskQuotaCfg, sizeof(struDiskQuotaCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_DISK_QUOTA_CFG");
        return TRUE;
    } 
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_DISK_QUOTA_CFG");
        return FALSE;
    }
}

void CDlgDiskQuota::GetDiskQuotaCfgFromWnd(NET_DVR_DISK_QUOTA_CFG &struDiskQuotaCfg)
{
    GetPicQuotaFromWnd(struDiskQuotaCfg.struPicQuota);
    GetRecordQuotaFromWnd(struDiskQuotaCfg.struRecordQuota);
    GetAddInfoQuotaFromWnd(struDiskQuotaCfg.struAddInfoQuota);
}

void CDlgDiskQuota::GetPicQuotaFromWnd(NET_DVR_DISK_QUOTA &struPicQuota)
{
    struPicQuota.byQuotaType = m_comboPicType.GetItemData(m_comboPicType.GetCurSel());
    struPicQuota.wStoragePeriod = m_dwPicPeriod;
    struPicQuota.dwLCapacity = m_iPicCapacity;
	struPicQuota.byQuotaRatio = m_byPicQuotaRatio;
}
void CDlgDiskQuota::GetRecordQuotaFromWnd(NET_DVR_DISK_QUOTA &struRecordQuota)
{
    struRecordQuota.byQuotaType = m_comboRecordType.GetItemData(m_comboRecordType.GetCurSel());
    struRecordQuota.wStoragePeriod = m_dwReocrdPeriod;
    struRecordQuota.dwLCapacity = m_iRecordCapacity;
	struRecordQuota.byQuotaRatio = m_byRecordQuotaRatio;
}
void CDlgDiskQuota::GetAddInfoQuotaFromWnd(NET_DVR_DISK_QUOTA &struAddInfoQuota)
{
    struAddInfoQuota.byQuotaType = m_comboAddInfoType.GetItemData(m_comboPicType.GetCurSel());
    struAddInfoQuota.dwLCapacity = m_iAddInfoCapacity;
    struAddInfoQuota.byQuotaRatio = m_byAddInfoQuotaRatio;
}

void CDlgDiskQuota::SetDiskQuotaCfgToWnd(NET_DVR_DISK_QUOTA_CFG &struDiskQuotaCfg)
{
    SetPicQuotaToWnd(struDiskQuotaCfg.struPicQuota);
    SetRecordQuotaToWnd(struDiskQuotaCfg.struRecordQuota);
    SetAddInfoQuotaFromWnd(struDiskQuotaCfg.struAddInfoQuota);
}

void CDlgDiskQuota::SetPicQuotaToWnd(NET_DVR_DISK_QUOTA &struPicQuota)
{
    int i = 0;
    for (i = 0; i < m_comboPicType.GetCount(); i++)
    {
        if (struPicQuota.byQuotaType == m_comboPicType.GetItemData(i))
        {
            m_comboPicType.SetCurSel(i);
			break;
        }
    }

    m_iPicCapacity = struPicQuota.dwLCapacity;
	m_iPicUsed = struPicQuota.dwLUsedSpace;
	m_byPicQuotaRatio = struPicQuota.byQuotaRatio;
    m_dwPicPeriod = struPicQuota.wStoragePeriod;
}
void CDlgDiskQuota::SetRecordQuotaToWnd(NET_DVR_DISK_QUOTA &struRecordQuota)
{
    int i = 0;
    for (i = 0; i < m_comboRecordType.GetCount(); i++)
    {
        if (struRecordQuota.byQuotaType == m_comboRecordType.GetItemData(i))
        {
            m_comboRecordType.SetCurSel(i);
			break;
        }
    }
    
    m_iRecordCapacity = struRecordQuota.dwLCapacity;
	m_iRecordUsed = struRecordQuota.dwLUsedSpace;
	m_byRecordQuotaRatio = struRecordQuota.byQuotaRatio;
    m_dwReocrdPeriod = struRecordQuota.wStoragePeriod;
}

void CDlgDiskQuota::SetAddInfoQuotaFromWnd(NET_DVR_DISK_QUOTA &struAddInfoQuota)
{
    int i = 0;
    for (i = 0; i < m_comboAddInfoType.GetCount(); i++)
    {
        if (struAddInfoQuota.byQuotaType == m_comboAddInfoType.GetItemData(i))
        {
            m_comboAddInfoType.SetCurSel(i);
            break;
        }
    }
    
    m_iAddInfoCapacity = struAddInfoQuota.dwLCapacity;
    m_iAddInfoUsed = struAddInfoQuota.dwLUsedSpace;
    m_byAddInfoQuotaRatio = struAddInfoQuota.byQuotaRatio;
}

void CDlgDiskQuota::OnBtnQuotaCfg() 
{
    UpdateData(TRUE);

    LONG lChannel = m_lChannel;
    //if (m_bAllChann)
    //{
    //    lChannel = -1;
    //}

	char szLan[128] = {0};
    GetDiskQuotaCfgFromWnd(m_struDiskQuotaCfg);
	if (!SetDiskQuotaCfg(lChannel, m_struDiskQuotaCfg))
	{
		g_StringLanType(szLan, "≈‰÷√¥≈≈Ã≈‰∂Ó ß∞‹", "Fail to set disk quota");    
        AfxMessageBox(szLan);
	}
}

void CDlgDiskQuota::OnBtnQuotaUpgrade()
{   
    UpdateData(TRUE);
    LONG lChannel = m_lChannel;
    if (m_bAllChann)
    {
        lChannel = 0xff;
    }
    
	char szLan[128] = {0};
	if (!GetDiskQuotaCfg(lChannel, m_struDiskQuotaCfg))
    {
		g_StringLanType(szLan, "ªÒ»°¥≈≈Ã≈‰∂Ó≈‰÷√ ß∞‹", "Fail to get disk quota configure");  
        AfxMessageBox(szLan);
    }
	
	SetDiskQuotaCfgToWnd(m_struDiskQuotaCfg);
    UpdateData(FALSE);	
}

void CDlgDiskQuota::OnBtnQuotaExit()
{
	CDialog::OnCancel();
}

void CDlgDiskQuota::OnBtnDrawFrameQuotaCfg() 
{
	UpdateData(TRUE);
	char szLan[128] = {0};
	
	m_struDrawFrame.dwSize = sizeof(m_struDrawFrame);
	m_struDrawFrame.byDrawFrameRecordQuota = m_byDrawPer;
	m_struDrawFrame.byPicQuota = m_byPicPer;
	m_struDrawFrame.byRecordQuota = m_byRecordPer;

    if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_DRAWFRAME_DISK_QUOTA_CFG, m_lChannel, &m_struDrawFrame, sizeof(m_struDrawFrame)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_DRAWFRAME_DISK_QUOTA_CFG");
        return;
    } 
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_DRAWFRAME_DISK_QUOTA_CFG");
		g_StringLanType(szLan, "…Ë÷√¥≈≈Ã≈‰∂Ó≈‰÷√ ß∞‹", "Fail to setup disk quota configure");  
        AfxMessageBox(szLan);
        return;
    }	
}

void CDlgDiskQuota::OnButtonDrawFrameUpdate() 
{
	char szLan[128] = {0};

    DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_DRAWFRAME_DISK_QUOTA_CFG, m_lChannel, &m_struDrawFrame, sizeof(m_struDrawFrame), &dwReturn))
    {
		m_byDrawPer = m_struDrawFrame.byDrawFrameRecordQuota;
		m_byPicPer = m_struDrawFrame.byPicQuota;
		m_byRecordPer = m_struDrawFrame.byRecordQuota;		

        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_DRAWFRAME_DISK_QUOTA_CFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_DRAWFRAME_DISK_QUOTA_CFG");
		g_StringLanType(szLan, "ªÒ»°≥È÷°Õ®µ¿¥≈≈Ã≈‰∂Ó≈‰÷√ ß∞‹", "Fail to get disk quota configure");  
        AfxMessageBox(szLan);
        return;
    }
}
