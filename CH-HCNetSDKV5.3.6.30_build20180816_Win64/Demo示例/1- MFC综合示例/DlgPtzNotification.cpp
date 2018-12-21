// DlgPtzNotification.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgPtzNotification.h"
#include "afxdialogex.h"


// CDlgPtzNotification 对话框

IMPLEMENT_DYNAMIC(CDlgPtzNotification, CDialogEx)

CDlgPtzNotification::CDlgPtzNotification(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgPtzNotification::IDD, pParent)
    , m_dwPresetChan(0)
    , m_dwCruiseChan(0)
    , m_dwTrackChan(0)
    , m_dwCruisePointNo(0)
    , m_dwPresetPointNo(0)
    , m_dwTrackPointNo(0)
    , m_dwPresetNum(0)
    , m_dwCruiseNum(0)
    , m_dwTrackNum(0)
    , m_bPattern(FALSE)
    , m_bPatrol(FALSE)
    , m_bPreset(FALSE)
{

}

CDlgPtzNotification::~CDlgPtzNotification()
{
}

void CDlgPtzNotification::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CMB_CHAN, m_cmbChan);
    DDX_Text(pDX, IDC_EDIT_PRESET_CHAN, m_dwPresetChan);
    DDX_Text(pDX, IDC_EDIT_CRUISE_CHAN, m_dwCruiseChan);
    DDX_Text(pDX, IDC_EDIT_TRACK_CHAN, m_dwTrackChan);
    DDX_Text(pDX, IDC_EDIT_CRUISE_POINT_NO, m_dwCruisePointNo);
    DDX_Text(pDX, IDC_EDIT_PRESET_POINT_NO, m_dwPresetPointNo);
    DDX_Text(pDX, IDC_EDIT_TRACK_POINT_NO, m_dwTrackPointNo);
    DDX_Text(pDX, IDC_EDIT_PRESET_NUM, m_dwPresetNum);
    DDX_Text(pDX, IDC_EDIT_CRUISE_NUM, m_dwCruiseNum);
    DDX_Text(pDX, IDC_EDIT_TRACK_NUM, m_dwTrackNum);
    DDX_Control(pDX, IDC_CMB_EVNET_TYPE, m_cmbType);
    DDX_Check(pDX, IDC_PATTERN, m_bPattern);
    DDX_Check(pDX, IDC_POTROL, m_bPatrol);
    DDX_Check(pDX, IDC_PRESET, m_bPreset);
}


BEGIN_MESSAGE_MAP(CDlgPtzNotification, CDialogEx)
    ON_BN_CLICKED(IDC_BTN_SET, &CDlgPtzNotification::OnBnClickedBtnSet)
    ON_BN_CLICKED(IDC_BTN_GET, &CDlgPtzNotification::OnBnClickedBtnGet)
    ON_CBN_SELCHANGE(IDC_CMB_CHAN, &CDlgPtzNotification::OnCbnSelchangeCmbChan)
    ON_BN_CLICKED(IDC_BTN_SAVE, &CDlgPtzNotification::OnBnClickedBtnSave)
    ON_BN_CLICKED(IDCANCEL, &CDlgPtzNotification::OnBnClickedCancel)
    ON_BN_CLICKED(IDC_POTROL, &CDlgPtzNotification::OnBnClickedPotrol)
    ON_BN_CLICKED(IDC_PATTERN, &CDlgPtzNotification::OnBnClickedPattern)
    ON_BN_CLICKED(IDC_PRESET, &CDlgPtzNotification::OnBnClickedPreset)
END_MESSAGE_MAP()

BOOL CDlgPtzNotification::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    int i = 0;
    char sbuf[128] = { 0 };
    for (i = 0; i < 512; i++)
    {
        sprintf(sbuf, "chan-%d", i + 1);
        m_cmbChan.InsertString(i, sbuf);
    }
    m_cmbChan.SetCurSel(0);

    m_cmbType.ResetContent();
    m_cmbType.InsertString(0, "facedetection");
    m_cmbType.InsertString(1, "vehicledetection");
    m_cmbType.InsertString(2, "scenechangedetection");
    m_cmbType.InsertString(3, "linedetection");
    m_cmbType.InsertString(4, "regionEntrance");
    m_cmbType.InsertString(5, "regionExiting");
    m_cmbType.InsertString(6, "loitering");
    m_cmbType.InsertString(7, "group");
    m_cmbType.InsertString(8, "rapidMove");
    m_cmbType.InsertString(9, "parking");
    m_cmbType.InsertString(10, "unattendedBaggage");
    m_cmbType.InsertString(11, "attendedBaggage");
    m_cmbType.InsertString(12, "audioexception");
    m_cmbType.InsertString(13, "PIR");
    m_cmbType.InsertString(14, "defocus");
    m_cmbType.InsertString(15, "temperature");
    m_cmbType.InsertString(16, "fireDetection");
    m_cmbType.InsertString(17, "thermometry");
    m_cmbType.InsertString(18, "shipsDetection");
    m_cmbType.InsertString(19, "fieldDetection");
    m_cmbType.InsertString(20, "blackListFaceContrast");
    m_cmbType.InsertString(21, "whiteListFaceContrast");
    m_cmbType.InsertString(22, "humanRecognition");
    m_cmbType.InsertString(23, "faceContrast");
    m_cmbType.SetCurSel(0);
    memset(&m_struPtzNotificationCond, 0, sizeof(m_struPtzNotificationCond));
    memset(&m_struPtzNotificationCfg, 0, sizeof(m_struPtzNotificationCfg));
    GetDlgItem(IDC_PATTERN)->EnableWindow(FALSE);
    GetDlgItem(IDC_POTROL)->EnableWindow(FALSE);
    GetDlgItem(IDC_PRESET)->EnableWindow(TRUE);
    m_bPreset = TRUE;

    GetDlgItem(IDC_EDIT_PRESET_CHAN)->EnableWindow(TRUE);
    GetDlgItem(IDC_EDIT_PRESET_POINT_NO)->EnableWindow(TRUE);
    GetDlgItem(IDC_EDIT_TRACK_CHAN)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_TRACK_POINT_NO)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_CRUISE_CHAN)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_CRUISE_POINT_NO)->EnableWindow(FALSE);
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常:  OCX 属性页应返回 FALSE
}
// CDlgPtzNotification 消息处理程序


void CDlgPtzNotification::OnBnClickedBtnSet()
{
    // TODO:  在此添加控件通知处理程序代码
    UpdateData(TRUE);
    m_struPtzNotificationCond.dwSize = sizeof(m_struPtzNotificationCond);
    m_struPtzNotificationCond.byEventType = m_cmbType.GetCurSel();
    m_struPtzNotificationCond.dwChannel = m_lChannel;

    m_struPtzNotificationCfg.dwSize = sizeof(m_struPtzNotificationCfg);

    NET_DVR_STD_CONFIG struCfg = { 0 };
    struCfg.lpCondBuffer = &m_struPtzNotificationCond;
    struCfg.dwCondSize = sizeof(m_struPtzNotificationCond);
    struCfg.lpInBuffer = &m_struPtzNotificationCfg;
    struCfg.dwInSize = sizeof(m_struPtzNotificationCfg);

    memset(m_szStatusBuf, 0, ISAPI_STATUS_LEN);
    struCfg.lpStatusBuffer = m_szStatusBuf;
    struCfg.dwStatusSize = ISAPI_STATUS_LEN;

    if (!NET_DVR_SetSTDConfig(m_lUserID, NET_DVR_SET_PTZ_NOTIFICATION, &struCfg))
    {
        OutputDebugString(m_szStatusBuf);
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_PTZ_NOTIFICATION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PTZ_NOTIFICATION");
    }
}


void CDlgPtzNotification::OnBnClickedBtnGet()
{
    memset(&m_struPtzNotificationCond, 0, sizeof(m_struPtzNotificationCond));
    memset(&m_struPtzNotificationCfg, 0, sizeof(m_struPtzNotificationCfg));

    m_struPtzNotificationCond.dwSize = sizeof(m_struPtzNotificationCond);
    m_struPtzNotificationCond.byEventType = m_cmbType.GetCurSel();
    m_struPtzNotificationCond.dwChannel = m_lChannel;

    NET_DVR_STD_CONFIG  struConfig = { 0 };
    struConfig.lpCondBuffer = &m_struPtzNotificationCond;
    struConfig.dwCondSize = sizeof(m_struPtzNotificationCond);

    struConfig.lpOutBuffer = &m_struPtzNotificationCfg;
    struConfig.dwOutSize = sizeof(m_struPtzNotificationCfg);
    if (!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_PTZ_NOTIFICATION, &struConfig))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_PTZ_NOTIFICATION");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_PTZ_NOTIFICATION");
        m_dwPresetPointNo = m_struPtzNotificationCfg.struPresetChanInfo[0].dwPresetPointNo;
        m_dwCruisePointNo = m_struPtzNotificationCfg.struCruiseChanInfo[0].dwCruiseNo;
        m_dwTrackPointNo = m_struPtzNotificationCfg.struPtzTrackInfo[0].dwPtzTrackNo;

        m_dwPresetChan = m_struPtzNotificationCfg.struPresetChanInfo[0].dwEnablePresetChan;
        m_dwCruiseChan = m_struPtzNotificationCfg.struCruiseChanInfo[0].dwEnableCruiseChan;
        m_dwTrackChan = m_struPtzNotificationCfg.struPtzTrackInfo[0].dwEnablePtzTrackChan;

        m_dwPresetNum = m_struPtzNotificationCfg.dwEnablePresetChanNum;
        m_dwCruiseNum = m_struPtzNotificationCfg.dwEnableCruiseChanNum;
        m_dwTrackNum = m_struPtzNotificationCfg.dwEnablePtzTrackChanNum;

        //m_cmbType.SetCurSel(m_struPtzNotification.byEventType);
    }
    UpdateData(FALSE);
}


void CDlgPtzNotification::OnCbnSelchangeCmbChan()
{
    // TODO:  
    UpdateData(TRUE);
    int iTemp = m_cmbChan.GetCurSel();
    m_dwPresetPointNo = m_struPtzNotificationCfg.struPresetChanInfo[iTemp].dwPresetPointNo;
    m_dwCruisePointNo = m_struPtzNotificationCfg.struCruiseChanInfo[iTemp].dwCruiseNo;
    m_dwTrackPointNo = m_struPtzNotificationCfg.struPtzTrackInfo[iTemp].dwPtzTrackNo;

    m_dwPresetChan = m_struPtzNotificationCfg.struPresetChanInfo[iTemp].dwEnablePresetChan;
    m_dwCruiseChan = m_struPtzNotificationCfg.struCruiseChanInfo[iTemp].dwEnableCruiseChan;
    m_dwTrackChan = m_struPtzNotificationCfg.struPtzTrackInfo[iTemp].dwEnablePtzTrackChan;

    m_dwPresetNum = m_struPtzNotificationCfg.dwEnablePresetChanNum;
    m_dwCruiseNum = m_struPtzNotificationCfg.dwEnableCruiseChanNum;
    m_dwTrackNum = m_struPtzNotificationCfg.dwEnablePtzTrackChanNum;
    UpdateData(FALSE);
}


void CDlgPtzNotification::OnBnClickedBtnSave()
{
    // TODO:  
    UpdateData(TRUE);
    int iTemp = m_cmbChan.GetCurSel();
    m_struPtzNotificationCfg.struPresetChanInfo[iTemp].dwPresetPointNo = m_dwPresetPointNo;
    m_struPtzNotificationCfg.struCruiseChanInfo[iTemp].dwCruiseNo = m_dwCruisePointNo;
    m_struPtzNotificationCfg.struPtzTrackInfo[iTemp].dwPtzTrackNo = m_dwTrackPointNo;

    m_struPtzNotificationCfg.struPresetChanInfo[iTemp].dwEnablePresetChan = m_dwPresetChan;
    m_struPtzNotificationCfg.struCruiseChanInfo[iTemp].dwEnableCruiseChan = m_dwCruiseChan;
    m_struPtzNotificationCfg.struPtzTrackInfo[iTemp].dwEnablePtzTrackChan = m_dwTrackChan;

    m_struPtzNotificationCfg.dwEnablePresetChanNum = m_dwPresetNum;
    m_struPtzNotificationCfg.dwEnableCruiseChanNum = m_dwCruiseNum;
    m_struPtzNotificationCfg.dwEnablePtzTrackChanNum = m_dwTrackNum;
    UpdateData(FALSE);
}


void CDlgPtzNotification::OnBnClickedCancel()
{
    CDialogEx::OnCancel();
}


void CDlgPtzNotification::OnBnClickedPotrol()
{
    UpdateData(TRUE);
    if (m_bPatrol == TRUE)
    {
        GetDlgItem(IDC_PATTERN)->EnableWindow(!m_bPatrol);
        GetDlgItem(IDC_PRESET)->EnableWindow(!m_bPatrol);

        GetDlgItem(IDC_EDIT_TRACK_CHAN)->EnableWindow(!m_bPatrol);
        GetDlgItem(IDC_EDIT_TRACK_POINT_NO)->EnableWindow(!m_bPatrol);
        GetDlgItem(IDC_EDIT_PRESET_CHAN)->EnableWindow(!m_bPatrol);
        GetDlgItem(IDC_EDIT_PRESET_POINT_NO)->EnableWindow(!m_bPatrol);



    }
    else
    {
        GetDlgItem(IDC_PATTERN)->EnableWindow(!m_bPatrol);
        GetDlgItem(IDC_PRESET)->EnableWindow(!m_bPatrol);
        GetDlgItem(IDC_EDIT_PRESET_CHAN)->EnableWindow(!m_bPatrol);
        GetDlgItem(IDC_EDIT_PRESET_POINT_NO)->EnableWindow(!m_bPatrol);

        GetDlgItem(IDC_EDIT_TRACK_CHAN)->EnableWindow(!m_bPatrol);
        GetDlgItem(IDC_EDIT_TRACK_POINT_NO)->EnableWindow(!m_bPatrol);
    }
    UpdateData(FALSE);
}


void CDlgPtzNotification::OnBnClickedPattern()
{
    UpdateData(TRUE);
    if (m_bPattern == TRUE)
    {
        GetDlgItem(IDC_POTROL)->EnableWindow(!m_bPattern);
        GetDlgItem(IDC_PRESET)->EnableWindow(!m_bPattern);
        GetDlgItem(IDC_EDIT_CRUISE_CHAN)->EnableWindow(!m_bPattern);
        GetDlgItem(IDC_EDIT_CRUISE_POINT_NO)->EnableWindow(!m_bPattern);
        GetDlgItem(IDC_EDIT_PRESET_CHAN)->EnableWindow(!m_bPattern);
        GetDlgItem(IDC_EDIT_PRESET_POINT_NO)->EnableWindow(!m_bPattern);
    }
    else
    {
        GetDlgItem(IDC_POTROL)->EnableWindow(!m_bPattern);
        GetDlgItem(IDC_PRESET)->EnableWindow(!m_bPattern);
        GetDlgItem(IDC_EDIT_PRESET_CHAN)->EnableWindow(!m_bPattern);
        GetDlgItem(IDC_EDIT_PRESET_POINT_NO)->EnableWindow(!m_bPattern);
        GetDlgItem(IDC_EDIT_CRUISE_CHAN)->EnableWindow(!m_bPattern);
        GetDlgItem(IDC_EDIT_CRUISE_POINT_NO)->EnableWindow(!m_bPattern);
    }
    UpdateData(FALSE);
}


void CDlgPtzNotification::OnBnClickedPreset()
{
    UpdateData(TRUE);
    if (m_bPreset == TRUE)
    {
        GetDlgItem(IDC_POTROL)->EnableWindow(!m_bPreset);
        GetDlgItem(IDC_PATTERN)->EnableWindow(!m_bPreset);
        GetDlgItem(IDC_EDIT_CRUISE_CHAN)->EnableWindow(!m_bPreset);
        GetDlgItem(IDC_EDIT_CRUISE_POINT_NO)->EnableWindow(!m_bPreset);
        GetDlgItem(IDC_EDIT_TRACK_CHAN)->EnableWindow(!m_bPreset);
        GetDlgItem(IDC_EDIT_TRACK_POINT_NO)->EnableWindow(!m_bPreset);

    }
    else
    {
        GetDlgItem(IDC_POTROL)->EnableWindow(!m_bPreset);
        GetDlgItem(IDC_PATTERN)->EnableWindow(!m_bPreset);


        GetDlgItem(IDC_EDIT_CRUISE_CHAN)->EnableWindow(!m_bPreset);
        GetDlgItem(IDC_EDIT_CRUISE_POINT_NO)->EnableWindow(!m_bPreset);
        GetDlgItem(IDC_EDIT_TRACK_CHAN)->EnableWindow(!m_bPreset);
        GetDlgItem(IDC_EDIT_TRACK_POINT_NO)->EnableWindow(!m_bPreset);
    }
    UpdateData(FALSE);
}
