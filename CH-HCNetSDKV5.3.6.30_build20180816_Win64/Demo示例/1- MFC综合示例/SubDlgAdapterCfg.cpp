// SubDlgAdapterCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "SubDlgAdapterCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubDlgAdapterCfg dialog


CSubDlgAdapterCfg::CSubDlgAdapterCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubDlgAdapterCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSubDlgAdapterCfg)
	m_csVersion = _T("");
	m_csPortNum = _T("");
	m_csPortType = _T("");
	m_csRaidType = _T("");
	m_csSupportExpand = _T("");
	m_csSupportMigrate = _T("");
	m_bAutoRebuild = FALSE;
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    memset(&m_struAdapterInfo, 0, sizeof(m_struAdapterInfo));
}


void CSubDlgAdapterCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubDlgAdapterCfg)
	DDX_Text(pDX, IDC_STATIC_VERSION, m_csVersion);
	DDX_Text(pDX, IDC_STATIC_PORT_NUM, m_csPortNum);
	DDX_Text(pDX, IDC_STATIC_PORT_TYPE, m_csPortType);
	DDX_Text(pDX, IDC_STATIC_RAID_TYPE, m_csRaidType);
	DDX_Text(pDX, IDC_STATIC_SUPPORT_EXPAND, m_csSupportExpand);
	DDX_Text(pDX, IDC_STATIC_SUPPORT_MIGRATE, m_csSupportMigrate);
	DDX_Check(pDX, IDC_CHECK_AUTO_REBUILD, m_bAutoRebuild);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubDlgAdapterCfg, CDialog)
	//{{AFX_MSG_MAP(CSubDlgAdapterCfg)
	ON_BN_CLICKED(IDC_BTN_SET_ADAPTER, OnBtnSetAdapter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubDlgAdapterCfg message handlers
BOOL CSubDlgAdapterCfg::CheckInitParam()
{
    m_iDevIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lServerID = g_struDeviceInfo[m_iDevIndex].lLoginID;

    m_csVersion.Empty();
    m_csPortNum.Empty();
    m_csPortType.Empty();
    m_csRaidType.Empty();
    m_csSupportExpand.Empty();
	m_csSupportMigrate.Empty();
    return TRUE;
}
void CSubDlgAdapterCfg::CurCfgUpdate()
{
    if (!CheckInitParam())
    {
        return;
    }

    if (!GetAdapterInfo())
    {
        return;
    }
    
    char szLan[128] = {0};

    sprintf(szLan, "%d.%d.%d.%d", m_struAdapterInfo.struVersion.wMajorVersion,
        m_struAdapterInfo.struVersion.wMinorVersion, m_struAdapterInfo.struVersion.wRevisionNumber,
        m_struAdapterInfo.struVersion.wBuildNumber);
    m_csVersion = szLan;

    sprintf(szLan, "%d", m_struAdapterInfo.bySlotCount);
    m_csPortNum = szLan;

    if (1 == m_struAdapterInfo.bySupportExpand)
    {
        g_StringLanType(szLan, "ÊÇ", "yes");   
    }
    else
    {
        g_StringLanType(szLan, "·ñ", "No");   
    }
    m_csSupportExpand = szLan;

    if (1 == m_struAdapterInfo.bySupportMigrate)
    {
        g_StringLanType(szLan, "ÊÇ", "yes");   
    }
    else
    {
        g_StringLanType(szLan, "·ñ", "No");   
    }
    m_csSupportMigrate = szLan;


//     RAID0_ABILITY   = 0x0001,
//         RAID1_ABILITY   = 0x0002,
//         RAID10_ABILITY  = 0x0004,
//         RAID1E_ABILITY  = 0x0008,
//         RAID5_ABILITY   = 0x0010,
//         RAID6_ABILITY   = 0x0020,
//         RAID50_ABILITY  = 0x0040,
//         JBOD_ABILITY    = 0x0080,
//         RAID60_ABILITY  = 0x0100

    if (1 == ((m_struAdapterInfo.wSupportRaidType >> 0) & 0x01))
    {
        m_csRaidType += "0 ";
    }
    if (1 == ((m_struAdapterInfo.wSupportRaidType >> 1) & 0x01))
    {
        m_csRaidType += "1 ";
    }
    if (1 == ((m_struAdapterInfo.wSupportRaidType >> 2) & 0x01))
    {
        m_csRaidType += "10 ";
    }
    if (1 == ((m_struAdapterInfo.wSupportRaidType >> 3) & 0x01))
    {
        m_csRaidType += "1E ";
    }
    if (1 == ((m_struAdapterInfo.wSupportRaidType >> 4) & 0x01))
    {
        m_csRaidType += "5 ";
    }
    if (1 == ((m_struAdapterInfo.wSupportRaidType >> 5) & 0x01))
    {
        m_csRaidType += "6 ";
    }
    if (1 == ((m_struAdapterInfo.wSupportRaidType >> 6) & 0x01))
    {
        m_csRaidType += "50 ";
    }
    if (1 == ((m_struAdapterInfo.wSupportRaidType >> 7) & 0x01))
    {
        m_csRaidType += "JBOD ";
    }
    if (1 == ((m_struAdapterInfo.wSupportRaidType >> 8) & 0x01))
    {
        m_csRaidType += "60 ";
    }
//     HD_TYPE_SATA    = 0x01,
//         HD_TYPE_PATA    = 0x02,
//         HD_TYPE_SAS     = 0x04,
//         HD_TYPE_ATAPI   = 0x08,
//         HD_TYPE_TAPE    = 0x10,
//         HD_TYPE_SES     = 0x20

    if (1 == (m_struAdapterInfo.wSlotSupportType & 0x01))
    {
        m_csPortType += "SATA ";
    }
    if (1 == ((m_struAdapterInfo.wSlotSupportType >> 1)& 0x01))
    {
        m_csPortType += "PATA ";
    }

    if (1 == ((m_struAdapterInfo.wSlotSupportType >> 2)& 0x01))
    {
        m_csPortType += "SAS ";
    }

    if (1 == ((m_struAdapterInfo.wSlotSupportType >> 3)& 0x01))
    {
        m_csPortType += "ATAPI ";
    }

    if (1 == ((m_struAdapterInfo.wSlotSupportType >> 4)& 0x01))
    {
        m_csPortType += "TAPE ";
    }

    if (1 == ((m_struAdapterInfo.wSlotSupportType >> 5)& 0x01))
    {
        m_csPortType += "SES ";
    }

    if (1 == m_struAdapterInfo.bySupportRebuild)
    {
        GetDlgItem(IDC_CHECK_AUTO_REBUILD)->EnableWindow(TRUE);
        m_bAutoRebuild = m_struAdapterInfo.byAutoRebuild;
    }
    else
    {
        GetDlgItem(IDC_CHECK_AUTO_REBUILD)->EnableWindow(FALSE);
    }
    UpdateData(FALSE);
}
void CSubDlgAdapterCfg::OnBtnSetAdapter() 
{
    UpdateData(TRUE);
    m_struAdapterInfo.byAutoRebuild = m_bAutoRebuild;
    SetAdapterInfo();
}

BOOL CSubDlgAdapterCfg::GetAdapterInfo()
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

BOOL CSubDlgAdapterCfg::SetAdapterInfo()
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

BOOL CSubDlgAdapterCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    m_csVersion.Empty();
    m_csVersion.Empty();
    m_csPortNum.Empty();
    m_csPortType.Empty();
    m_csRaidType.Empty();
    m_csSupportExpand.Empty();
    m_csSupportMigrate.Empty();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
