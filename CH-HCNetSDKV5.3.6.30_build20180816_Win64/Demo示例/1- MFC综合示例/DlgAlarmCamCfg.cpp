// DlgAlarmCamCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmCamCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmCamCfg dialog


CDlgAlarmCamCfg::CDlgAlarmCamCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmCamCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAlarmCamCfg)
	m_bPtzEnable = FALSE;
	m_bEnable = FALSE;
	m_iMonID = 0;
	m_iNum = 0;
	m_iPtzNo = 0;
	m_iRecordTime = 0;
	m_iResidentTime = 0;
	m_iCamID = 0;
	m_iAlarmOffCam = 0;
	m_iAlarmOffMonitor = 0;
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    memset(&m_struAlarmCamCfg, 0, sizeof(m_struAlarmCamCfg));
    m_lAlarmCamIndex = -1;
}


void CDlgAlarmCamCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmCamCfg)
	DDX_Control(pDX, IDC_COMBO_ALARMOFF_MODE, m_comboAlarmOffMode);
	DDX_Control(pDX, IDC_COMBO_ALARM_CHANNEL, m_comboAlarmChannel);
	DDX_Control(pDX, IDC_COMBO_PTZ_TYPE, m_comboPtzType);
	DDX_Control(pDX, IDC_COMBO_INDEX, m_comboIndex);
	DDX_Check(pDX, IDC_CHECK_PTZ_ENABLE, m_bPtzEnable);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	DDX_Text(pDX, IDC_EDIT_MON_ID, m_iMonID);
	DDX_Text(pDX, IDC_EDIT_NUM, m_iNum);
	DDX_Text(pDX, IDC_EDIT_PTZ_NO, m_iPtzNo);
	DDX_Text(pDX, IDC_EDIT_RECORD_TIME, m_iRecordTime);
	DDX_Text(pDX, IDC_EDIT_RESIDENT_TIME, m_iResidentTime);
	DDX_Text(pDX, IDC_EDIT_CAM_ID, m_iCamID);
	DDX_Text(pDX, IDC_EDIT_ALARMOFF_CAM, m_iAlarmOffCam);
	DDX_Text(pDX, IDC_EDIT_ALARMOFF_MONITOR, m_iAlarmOffMonitor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmCamCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmCamCfg)
	ON_CBN_SELCHANGE(IDC_COMBO_INDEX, OnSelchangeComboIndex)
	ON_BN_CLICKED(IDC_BTN_ALARMOFF_MON, OnBtnAlarmoffMon)
	ON_BN_CLICKED(IDC_BTN_CONFIRM, OnBtnConfirm)
	ON_BN_CLICKED(IDC_BTN_SET_UP, OnBtnSetUp)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_CHANNEL, OnSelchangeComboAlarmChannel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmCamCfg message handlers

BOOL CDlgAlarmCamCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
    
    InitComboIndex();
    InitAlarmChanCombo();
    InitPtzTypeCombo();
    InitAlarmOffCombo();
    m_comboAlarmChannel.SetCurSel(0);
    OnSelchangeComboAlarmChannel();
    UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlarmCamCfg::InitComboIndex()
{
    m_comboIndex.ResetContent();
    char szLan[128] = {0};
    for (int i = 0; i < MAX_ALARM_CAM_NUM; i++)
    {
        sprintf(szLan, "%d", i + 1);
        m_comboIndex.AddString(szLan);
    }
}

void CDlgAlarmCamCfg::InitAlarmChanCombo()
{
    m_comboAlarmChannel.ResetContent();
    char szLan[128] = {0};
    for (int i = 0; i < 32; i++)
    {
        sprintf(szLan, "Chan %d", i + 1);
        m_comboAlarmChannel.AddString(szLan);
    }
}

void CDlgAlarmCamCfg::InitPtzTypeCombo()
{
    char szLan[128] = {0};
    m_comboPtzType.ResetContent();
    int nIndex = 0;

    g_StringLanType(szLan, "预置点", "Preset");
    m_comboPtzType.InsertString(nIndex, szLan);
    m_comboPtzType.SetItemData(nIndex, 1);
    nIndex++;

    g_StringLanType(szLan, "巡航", "Cruise");
    m_comboPtzType.InsertString(nIndex, szLan);
    m_comboPtzType.SetItemData(nIndex, 2);
    nIndex++;
    
    g_StringLanType(szLan, "轨迹", "Track");
    m_comboPtzType.InsertString(nIndex, szLan);
    m_comboPtzType.SetItemData(nIndex, 3);
    nIndex++;
}

void CDlgAlarmCamCfg::InitAlarmOffCombo()
{
    char szLan[128] = {0};
    m_comboAlarmOffMode.ResetContent();
    g_StringLanType(szLan, "立即取消", "Immediately cancel");
    m_comboAlarmOffMode.AddString(szLan);
    g_StringLanType(szLan, "自动取消", "Canceled");
    m_comboAlarmOffMode.AddString(szLan);
    g_StringLanType(szLan, "手动取消", "Manually cancel");
    m_comboAlarmOffMode.AddString(szLan);
}

void CDlgAlarmCamCfg::SetAlarmCamCfgToWnd(NET_DVR_ALARM_CAM_CFG &struAlarmCamCfg)
{
    m_bEnable = struAlarmCamCfg.byEnable;
    m_iNum = struAlarmCamCfg.dwNum;
    m_lAlarmCamIndex = m_comboIndex.GetCurSel();
    SetAlarmCamInfoToWnd(struAlarmCamCfg.struAlarmCam[m_lAlarmCamIndex]);
}

void CDlgAlarmCamCfg::GetAlarmCamCfgFromWnd(NET_DVR_ALARM_CAM_CFG &struAlarmCamCfg)
{
    struAlarmCamCfg.byEnable = m_bEnable;
    struAlarmCamCfg.dwNum = m_iNum;    
    GetAlarmCamInfoFromWnd(struAlarmCamCfg.struAlarmCam[m_comboIndex.GetCurSel()]);
}

void CDlgAlarmCamCfg::SetAlarmCamInfoToWnd(NET_DVR_ALARM_CAM_INFO &struAlarmCamInfo)
{
    m_iCamID = struAlarmCamInfo.dwCamID;
    m_iMonID = struAlarmCamInfo.dwMonID;
    m_iRecordTime = struAlarmCamInfo.dwRecordTime;
    m_iResidentTime = struAlarmCamInfo.dwResidentTime;
    m_bPtzEnable = struAlarmCamInfo.struPtzCtrl.byEnable;
    m_iPtzNo = struAlarmCamInfo.struPtzCtrl.byPtzNo;
    for (int i = 0; i < m_comboPtzType.GetCount(); i++)
    {
        if (struAlarmCamInfo.struPtzCtrl.byType == m_comboPtzType.GetItemData(i))
        {
            m_comboPtzType.SetCurSel(i);
            break;
        }
    }
    m_comboAlarmOffMode.SetCurSel(struAlarmCamInfo.byAlarmOffMode);
}

void CDlgAlarmCamCfg::GetAlarmCamInfoFromWnd(NET_DVR_ALARM_CAM_INFO &struAlarmCamInfo)
{
    struAlarmCamInfo.dwCamID = m_iCamID;
    struAlarmCamInfo.dwMonID = m_iMonID;
    struAlarmCamInfo.dwRecordTime = m_iRecordTime;
    struAlarmCamInfo.dwResidentTime = m_iResidentTime;
    struAlarmCamInfo.struPtzCtrl.byEnable = m_bPtzEnable;
    struAlarmCamInfo.struPtzCtrl.byPtzNo = m_iPtzNo;
    struAlarmCamInfo.struPtzCtrl.byType = m_comboPtzType.GetItemData(m_comboPtzType.GetCurSel());
    struAlarmCamInfo.byAlarmOffMode = m_comboAlarmOffMode.GetCurSel();
}

BOOL CDlgAlarmCamCfg::SetAlarmCamCfg(NET_DVR_ALARM_CAM_CFG &sturAlarmCamCfg)
{
    if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_ALARM_CAMCFG, m_comboAlarmChannel.GetCurSel() + 1, &sturAlarmCamCfg, sizeof(sturAlarmCamCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_ALARM_CAMCFG");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_ALARM_CAMCFG");
        return FALSE;
    }
}

BOOL CDlgAlarmCamCfg::GetAlarmCamCfg(NET_DVR_ALARM_CAM_CFG &sturAlarmCamCfg)
{
    DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_ALARM_CAMCFG, m_comboAlarmChannel.GetCurSel() + 1, &sturAlarmCamCfg, sizeof(sturAlarmCamCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARM_CAMCFG");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARM_CAMCFG");
        return FALSE;
    }
}

void CDlgAlarmCamCfg::OnSelchangeComboIndex() 
{
    m_lAlarmCamIndex = m_comboIndex.GetCurSel();
    SetAlarmCamInfoToWnd(m_struAlarmCamCfg.struAlarmCam[m_lAlarmCamIndex]);
    UpdateData(FALSE);
}

void CDlgAlarmCamCfg::OnBtnAlarmoffMon() 
{
	UpdateData(TRUE);
    if (!AlarmOffMonitor())
    {
        AfxMessageBox("Fail to alarm off monitor");
    }
}

BOOL CDlgAlarmCamCfg::AlarmOffMonitor()
{
    if (NET_DVR_MatrixAlarmOffMonitor(m_lServerID, m_iAlarmOffMonitor, m_iAlarmOffCam))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_MatrixAlarmOffMonitor");
        return TRUE;
    } 
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_MatrixAlarmOffMonitor");
        return FALSE;
    }
}

void CDlgAlarmCamCfg::OnBtnConfirm() 
{
    UpdateData(TRUE);
    GetAlarmCamInfoFromWnd(m_struAlarmCamCfg.struAlarmCam[m_comboIndex.GetCurSel()]);  

//    GetAlarmCamInfoFromWnd()
}

void CDlgAlarmCamCfg::OnBtnSetUp() 
{
    UpdateData(TRUE);
    GetAlarmCamCfgFromWnd(m_struAlarmCamCfg);
    if (!SetAlarmCamCfg(m_struAlarmCamCfg))
    {
        AfxMessageBox("Fail to set  Alarm Cam config");
    }
}

void CDlgAlarmCamCfg::OnSelchangeComboAlarmChannel() 
{
    m_comboIndex.SetCurSel(0);
    GetAlarmCamCfg(m_struAlarmCamCfg);
    SetAlarmCamCfgToWnd(m_struAlarmCamCfg);
    UpdateData(FALSE);
}
