// DlgAcsPersonnelChannelCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAcsPersonnelChannelCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgAcsPersonnelChannelCfg dialog


DlgAcsPersonnelChannelCfg::DlgAcsPersonnelChannelCfg(CWnd* pParent /*=NULL*/)
	: CDialog(DlgAcsPersonnelChannelCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgAcsPersonnelChannelCfg)
	m_dwDoorNo = 0;
	m_strScreenDisplay = _T("");
	m_dwRowSpacing = 0;
	m_dwColumnSpacing = 0;
	//}}AFX_DATA_INIT
}


void DlgAcsPersonnelChannelCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgAcsPersonnelChannelCfg)
	DDX_Control(pDX, IDC_COMBO_SCREEN_NO, m_byScreenNo);
	DDX_Control(pDX, IDC_COMBO_DEGREE, m_byDegree);
	DDX_Control(pDX, IDC_COMBO_FIRST_POSITION, m_dwFirstRowPosition);
	DDX_Control(pDX, IDC_COMBO_FRONT_SIZE, m_dwFontSize);
	DDX_Control(pDX, IDC_COMBO_SCREEN_TYPE, m_byScreenType);
	DDX_Control(pDX, IDC_COMBO_ENABLE_PERSON_STATISTICS, m_byEnableOfflineStatistics);
	DDX_Control(pDX, IDC_COMBO_PERSON_STATISTICS, m_byEnableStatistics);
	DDX_Control(pDX, IDC_COMBO_RESULT_TYPE, m_byResultType);
	DDX_Control(pDX, IDC_COMBO_WORK_MODE, m_byWorkMode);
	DDX_Control(pDX, IDC_COMBO_OUT_MODE, m_byOutMode);
	DDX_Control(pDX, IDC_COMBO_IN_MODE, m_byInMode);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_channel);
	DDX_Text(pDX, IDC_EDIT_DOOR_NO, m_dwDoorNo);
	DDX_Text(pDX, IDC_EDIT_USER_MESSAGE, m_strScreenDisplay);
	DDX_Text(pDX, IDC_EDIT_ROW_SPACING, m_dwRowSpacing);
	DDX_Text(pDX, IDC_EDIT_COLUMN_SPACING, m_dwColumnSpacing);
    DDX_Control(pDX, IDC_CMB_COUNT_SIGNAL_STATISTICAL_STANDARD, m_cmbCountSignalStatisticalStandard);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgAcsPersonnelChannelCfg, CDialog)
	//{{AFX_MSG_MAP(DlgAcsPersonnelChannelCfg)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_PLATFORM_VERIFY_GET, OnButtonPlatformVerifySet)
	ON_BN_CLICKED(IDC_BUTTON_PERSON_STATISTICS_GET, OnButtonPersonStatisticsGet)
	ON_BN_CLICKED(IDC_BUTTON_PERSON_STATISTICS_SET, OnButtonPersonStatisticsSet)
	ON_BN_CLICKED(IDC_BUTTON_SCREEN_DISPLAY_GET, OnButtonScreenDisplayGet)
	ON_BN_CLICKED(IDC_BUTTON_SCREEN_DISPLAY_SET, OnButtonScreenDisplaySet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgAcsPersonnelChannelCfg message handlers
BOOL DlgAcsPersonnelChannelCfg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
    
    CString csStr;
    char szLan[128] = {0};
    int i=0;
    m_channel.ResetContent();
    for (i=0; i<512; i++)
    {
        g_StringLanType(szLan, "", "");
        csStr.Format("%s%d", szLan, i);
        m_channel.InsertString(i, csStr);
    }
    m_channel.SetCurSel(0);
    
    m_byInMode.ResetContent();
    g_StringLanType(szLan, "受控", "controlled");
    m_byInMode.InsertString(0, szLan);
    g_StringLanType(szLan, "禁止", "forbid");
    m_byInMode.InsertString(1, szLan);
    g_StringLanType(szLan, "自由", "freedom");
    m_byInMode.InsertString(2, szLan);
    m_byInMode.SetCurSel(0);
    
    m_byOutMode.ResetContent();
    g_StringLanType(szLan, "受控", "controlled");
    m_byOutMode.InsertString(0, szLan);
    g_StringLanType(szLan, "禁止", "forbid");
    m_byOutMode.InsertString(1, szLan);
    g_StringLanType(szLan, "自由", "freedom");
    m_byOutMode.InsertString(2, szLan);
    m_byOutMode.SetCurSel(0);

    m_byWorkMode.ResetContent();
    g_StringLanType(szLan, "紧急", "urgent");
    m_byWorkMode.InsertString(0, szLan);
    g_StringLanType(szLan, "维护", "repair");
    m_byWorkMode.InsertString(1, szLan);
    g_StringLanType(szLan, "常闭", "normalClose");
    m_byWorkMode.InsertString(2, szLan);
    g_StringLanType(szLan, "常开", "normalOpen");
    m_byWorkMode.InsertString(3, szLan);
    m_byWorkMode.SetCurSel(0);


	m_dwFontSize.ResetContent();
    for (i=0; i<11; i++)
    {
        sprintf(szLan, "%d", i);
        m_dwFontSize.InsertString(i,szLan);
    }
    m_dwFontSize.SetCurSel(0);

	m_dwFirstRowPosition.ResetContent();
    for (i=0; i<8; i++)
    {
        sprintf(szLan, "%d/8", i);
        m_dwFirstRowPosition.InsertString(i,szLan);
    }
    m_dwFirstRowPosition.SetCurSel(0);

	m_byScreenType.ResetContent();
    g_StringLanType(szLan, "DC48270RS043_01T", "DC48270RS043_01T");
    m_byScreenType.InsertString(0, szLan);
    g_StringLanType(szLan, "DC80480B070_03T", "DC80480B070_03T");
    m_byScreenType.InsertString(1, szLan);
    m_byScreenType.SetCurSel(0);
    
	m_byScreenNo.ResetContent();
    for (i=0; i<16; i++)
    {
        sprintf(szLan, "%d", i);
        m_byScreenNo.InsertString(i,szLan);
    }
    m_byScreenNo.SetCurSel(0);


    m_byDegree.SetCurSel(0);
	m_byDegree.ResetContent();
    g_StringLanType(szLan, "正常", "normal");
    m_byDegree.InsertString(0, szLan);
    g_StringLanType(szLan, "侧着", "edge");
    m_byDegree.InsertString(1, szLan);
    m_byDegree.SetCurSel(0);

	m_byResultType.ResetContent();
    g_StringLanType(szLan, "非法", "legal");
    m_byResultType.InsertString(0, szLan);
    g_StringLanType(szLan, "合法", "illegal");
    m_byResultType.InsertString(1, szLan);
    m_byResultType.SetCurSel(0);

	m_byEnableStatistics.ResetContent();
    g_StringLanType(szLan, "不开启", "not open");
    m_byEnableStatistics.InsertString(0, szLan);
    g_StringLanType(szLan, "开启", "open");
    m_byEnableStatistics.InsertString(1, szLan);
    m_byEnableStatistics.SetCurSel(0);

	m_byEnableOfflineStatistics.ResetContent();
    g_StringLanType(szLan, "不开启", "not open");
    m_byEnableOfflineStatistics.InsertString(0, szLan);
    g_StringLanType(szLan, "开启", "open");
    m_byEnableOfflineStatistics.InsertString(1, szLan);
    m_byEnableOfflineStatistics.SetCurSel(0);
	
    m_cmbCountSignalStatisticalStandard.ResetContent();
    g_StringLanType(szLan, "无效", "invalid");
    m_cmbCountSignalStatisticalStandard.InsertString(0, szLan);
    g_StringLanType(szLan, "红外检测通行统计", "IR detect statistics");
    m_cmbCountSignalStatisticalStandard.InsertString(1, szLan);
    g_StringLanType(szLan, "认证数量统计", "certification number statistics");
    m_cmbCountSignalStatisticalStandard.InsertString(2, szLan);
    m_cmbCountSignalStatisticalStandard.SetCurSel(0);
	 
    //OnBtnGet();
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgAcsPersonnelChannelCfg::OnButtonGet() 
{
	// TODO: Add your control notification handler code here
    DWORD dwReturn = 0;
    NET_DVR_PERSONNEL_CHANNEL_CFG struChannelCfg = {0};
    struChannelCfg.dwSize = sizeof(struChannelCfg);
    //int i = m_channel.GetCurSel();
    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_PERSONNEL_CHANNEL_CFG, m_channel.GetCurSel(), &struChannelCfg, sizeof(struChannelCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PERSONNEL_CHANNEL_CFG Failed");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_PERSONNEL_CHANNEL_CFG SUCC");
        m_byInMode.SetCurSel(struChannelCfg.byInMode);
        m_byOutMode.SetCurSel(struChannelCfg.byOutMode);
        m_byWorkMode.SetCurSel(struChannelCfg.byWorkMode);
        
        UpdateData(FALSE);
	}
	
}

void DlgAcsPersonnelChannelCfg::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_PERSONNEL_CHANNEL_CFG struChannelCfg = {0};
    struChannelCfg.dwSize = sizeof(struChannelCfg);
    
    struChannelCfg.byInMode = m_byInMode.GetCurSel();
    struChannelCfg.byOutMode = m_byOutMode.GetCurSel();
    struChannelCfg.byWorkMode = m_byWorkMode.GetCurSel();
	int i = m_channel.GetCurSel();
    if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_PERSONNEL_CHANNEL_CFG, m_channel.GetCurSel(), &struChannelCfg, sizeof(struChannelCfg)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_PERSONNEL_CHANNEL_CFG Failed");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PERSONNEL_CHANNEL_CFG SUCC");
	}
	
}

void DlgAcsPersonnelChannelCfg::OnButtonPlatformVerifySet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    NET_DVR_PLATFORM_VERIFY_CFG struPlatformCfg = {0};
    struPlatformCfg.dwSize = sizeof(struPlatformCfg);
    
    struPlatformCfg.dwDoorNo = m_dwDoorNo;
    struPlatformCfg.byResultType = m_byResultType.GetCurSel();
    memcpy(struPlatformCfg.byScreenDisplay, m_strScreenDisplay, sizeof(struPlatformCfg.byScreenDisplay));
    if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_PLATFORM_VERIFY_CFG, 0, &struPlatformCfg, sizeof(struPlatformCfg)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_PLATFORM_VERIFY_CFG Failed");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PLATFORM_VERIFY_CFG SUCC");
	}
}

void DlgAcsPersonnelChannelCfg::OnButtonPersonStatisticsGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
    NET_DVR_PERSON_STATISTICS_CFG struPersonStatisticsCfg = {0};
    struPersonStatisticsCfg.dwSize = sizeof(struPersonStatisticsCfg);
    
    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_PERSON_STATISTICS_CFG, 0, &struPersonStatisticsCfg, sizeof(struPersonStatisticsCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PERSON_STATISTICS_CFG Failed");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_PERSON_STATISTICS_CFG SUCC");
        m_byEnableStatistics.SetCurSel(struPersonStatisticsCfg.byEnableStatistics);
        m_byEnableOfflineStatistics.SetCurSel(struPersonStatisticsCfg.byEnableOfflineStatistics);
        m_cmbCountSignalStatisticalStandard.SetCurSel(struPersonStatisticsCfg.byCountSignalStatisticalStandard);
        UpdateData(FALSE);
	}
}

void DlgAcsPersonnelChannelCfg::OnButtonPersonStatisticsSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    NET_DVR_PERSON_STATISTICS_CFG struPersonStatisticsCfg = {0};
    struPersonStatisticsCfg.dwSize = sizeof(struPersonStatisticsCfg);
    
    struPersonStatisticsCfg.byEnableStatistics = m_byEnableStatistics.GetCurSel();
    struPersonStatisticsCfg.byEnableOfflineStatistics = m_byEnableOfflineStatistics.GetCurSel();
    struPersonStatisticsCfg.byCountSignalStatisticalStandard = m_cmbCountSignalStatisticalStandard.GetCurSel();

    if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_PERSON_STATISTICS_CFG, 0, &struPersonStatisticsCfg, sizeof(struPersonStatisticsCfg)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_PERSON_STATISTICS_CFG Failed");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PERSON_STATISTICS_CFG SUCC");
	}
}

void DlgAcsPersonnelChannelCfg::OnButtonScreenDisplayGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
    NET_DVR_ACS_SCREEN_DISPLAY_CFG struScreenDisplayCfg = {0};
    struScreenDisplayCfg.dwSize = sizeof(struScreenDisplayCfg);
    
    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_ACS_SCREEN_DISPLAY_CFG, m_byScreenNo.GetCurSel(), &struScreenDisplayCfg, sizeof(struScreenDisplayCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ACS_SCREEN_DISPLAY_CFG Failed");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ACS_SCREEN_DISPLAY_CFG SUCC");
        m_dwFontSize.SetCurSel(struScreenDisplayCfg.dwFontSize);
        m_dwFirstRowPosition.SetCurSel(struScreenDisplayCfg.dwFirstRowPosition);
        m_byDegree.SetCurSel(struScreenDisplayCfg.byDegree);
		m_byScreenType.SetCurSel(struScreenDisplayCfg.byScreenType);

        m_dwRowSpacing= struScreenDisplayCfg.dwRowSpacing;
        m_dwColumnSpacing = struScreenDisplayCfg.dwColumnSpacing;      
        UpdateData(FALSE);
	}	
}

void DlgAcsPersonnelChannelCfg::OnButtonScreenDisplaySet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    NET_DVR_ACS_SCREEN_DISPLAY_CFG struScreenDisplayCfg = {0};
    struScreenDisplayCfg.dwSize = sizeof(struScreenDisplayCfg);
    
    struScreenDisplayCfg.dwFontSize = m_dwFontSize.GetCurSel();
    struScreenDisplayCfg.dwFirstRowPosition = m_dwFirstRowPosition.GetCurSel();
    struScreenDisplayCfg.byDegree = m_byDegree.GetCurSel();
	struScreenDisplayCfg.byScreenType = m_byScreenType.GetCurSel();

    struScreenDisplayCfg.dwRowSpacing = m_dwRowSpacing;
    struScreenDisplayCfg.dwColumnSpacing = m_dwColumnSpacing;

    if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_ACS_SCREEN_DISPLAY_CFG, m_byScreenNo.GetCurSel(), &struScreenDisplayCfg, sizeof(struScreenDisplayCfg)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_ACS_SCREEN_DISPLAY_CFG Failed");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_ACS_SCREEN_DISPLAY_CFG SUCC");
	}
}


