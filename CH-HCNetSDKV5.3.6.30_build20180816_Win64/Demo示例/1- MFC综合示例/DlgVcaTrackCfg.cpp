// DlgVcaTrackCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaTrackCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaTrackCfg dialog

CDlgVcaTrackCfg::CDlgVcaTrackCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaTrackCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaTrackCfg)
	m_bEnableCalibration = FALSE;
	//}}AFX_DATA_INIT

    m_lServerID = -1;    
    m_iDevIndex = -1; 
    m_iChannel = -1;    
    m_lPlayHandle = -1;
    memset(&m_struTrackCfg, 0, sizeof(m_struTrackCfg));   
    memset(&m_struTrackMode, 0, sizeof(m_struTrackMode));    
}


void CDlgVcaTrackCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaTrackCfg)
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cmbChannel);
	DDX_Control(pDX, IDC_COMBO_CONF_MODE, m_comboConfMode);
	DDX_Check(pDX, IDC_CHECK_CALIBRATION, m_bEnableCalibration);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaTrackCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaTrackCfg)
	ON_BN_CLICKED(IDC_BTN_PREVIEW, OnBtnPreview)
	ON_BN_CLICKED(IDC_RADIO_ALARM_TRACK, OnRadioAlarmTrack)
	ON_BN_CLICKED(IDC_CHECK_CALIBRATION, OnCheckCalibration)
	ON_BN_CLICKED(IDC_BTN_SET_CALIBRATION, OnBtnSetCalibration)
	ON_BN_CLICKED(IDC_RADIO_TARGET_TRACK, OnRadioTargetTrack)
	ON_CBN_SELCHANGE(IDC_COMBO_CONF_MODE, OnSelchangeComboConfMode)
	ON_BN_CLICKED(IDC_RADIO_MANUAL_TRACK, OnRadioManualTrack)
	ON_BN_CLICKED(IDC_BTN_GET_CALIBRATION, OnBtnGetCalibration)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaTrackCfg message handlers

BOOL CDlgVcaTrackCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
    
    m_btnPtzUp.SubclassDlgItem(IDC_BTN_PTZ_UP,this);
    m_btnPtzDown.SubclassDlgItem(IDC_BTN_PTZ_DOWN,this);
    m_btnPtzLeft.SubclassDlgItem(IDC_BTN_PTZ_LEFT,this);
    m_btnPtzRight.SubclassDlgItem(IDC_BTN_PTZ_RIGHT,this);	
    m_btnZoomOut.SubclassDlgItem(IDC_BTN_ZOOM_OUT,this);
    m_btnZoomIn.SubclassDlgItem(IDC_BTN_ZOOM_IN,this);
    
    m_btnPtzUp.m_iPTZType = TILT_UP;
    m_btnPtzDown.m_iPTZType = TILT_DOWN;
    m_btnPtzLeft.m_iPTZType = PAN_LEFT;
    m_btnPtzRight.m_iPTZType = PAN_RIGHT;
    m_btnZoomOut.m_iPTZType = ZOOM_OUT;
    m_btnZoomIn.m_iPTZType = ZOOM_IN;
	g_AddChanInfoToComBox(m_cmbChannel, m_iDevIndex);
	m_iChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());(m_struTrackMode);

    GetTrackCfg();
     
    GetTrackMode();
	m_bEnableCalibration = m_struTrackCfg.byEnable;
    ShowTrackModeWnd(m_struTrackMode);
    m_bEnableCalibration = m_struTrackCfg.byEnable;
    EnableWnd(!m_struTrackCfg.byEnable);
    UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgVcaTrackCfg::GetTrackCfg()
{	
	UpdateData(TRUE);
    DWORD dwReturn = 0;
    BOOL bRet = FALSE;
    
    char szLan[128] = {0};
	 
    m_iChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    bRet = NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_TRACK_CFG, m_iChannel, &m_struTrackCfg, sizeof(m_struTrackCfg), &dwReturn);
    if (!bRet)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_TRACK_CFG");
        g_StringLanType(szLan, "获取标定配置失败", "Fail to get calibrate config");
        MessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_TRACK_CFG");
    }
    return bRet;
}

BOOL CDlgVcaTrackCfg::SetTrackCfg()
{
	UpdateData(TRUE);
	m_iChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());
    BOOL bRet = FALSE;
    char szLan[128] = {0};
    bRet = NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_TRACK_CFG, m_iChannel, &m_struTrackCfg, sizeof(m_struTrackCfg));
    if (!bRet)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_TRACK_CFG");
        g_StringLanType(szLan, "设置标定配置失败", "Fail to set calibrate config");
        MessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_TRACK_CFG");
    }
    return bRet;
}

BOOL CDlgVcaTrackCfg::GetTrackMode()
{
	UpdateData(TRUE);
	m_iChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());

    BOOL bRet = FALSE;

    char szLan[128] = {0};
    bRet = NET_DVR_GetTrackMode(m_lServerID, m_iChannel, &m_struTrackMode);
    if (!bRet)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetTrackMode");
        g_StringLanType(szLan, "获取球机跟踪模式失败", "Fail to get track mode");
        MessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetTrackMode");
    }
    return bRet;
}

BOOL CDlgVcaTrackCfg::SetTrackMode()
{
	UpdateData(TRUE);
	m_iChannel = m_cmbChannel.GetItemData(m_cmbChannel.GetCurSel());

    BOOL bRet = FALSE;
    char szLan[128] = {0};
    bRet = NET_DVR_SetTrackMode(m_lServerID, m_iChannel, &m_struTrackMode);
    if (!bRet)
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SetTrackMode");
        g_StringLanType(szLan, "设置球机跟踪模式失败", "Fail to set track mode");
        MessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SetTrackMode");
    }
    return bRet;
}

void CDlgVcaTrackCfg::OnBtnPreview() 
{
    if (m_lPlayHandle >=0 )
    {
        if (StopRealPlay())
        {
            m_lPlayHandle = -1;
            ((CButton*)GetDlgItem(IDC_BTN_PREVIEW))->SetWindowText("Start play");
            Invalidate(TRUE);
        }
    }
    else
    {
        StartRealPlay();
        if (m_lPlayHandle >= 0)
        {
            ((CButton*)GetDlgItem(IDC_BTN_PREVIEW))->SetWindowText("Stop play");
            m_btnPtzUp.m_lPlayHandle = m_lPlayHandle;
            m_btnPtzDown.m_lPlayHandle = m_lPlayHandle;
            m_btnPtzLeft.m_lPlayHandle = m_lPlayHandle;
            m_btnPtzRight.m_lPlayHandle = m_lPlayHandle;
            m_btnZoomOut.m_lPlayHandle = m_lPlayHandle;
            m_btnZoomIn.m_lPlayHandle = m_lPlayHandle;	
        }
    }
}

void CDlgVcaTrackCfg::ShowTrackModeWnd(NET_DVR_TRACK_MODE struTrackMode)
{
    m_comboConfMode.SetCurSel(m_struTrackMode.byRuleConfMode);
    ((CButton *)GetDlgItem(IDC_RADIO_ALARM_TRACK))->SetCheck(FALSE);
    ((CButton *)GetDlgItem(IDC_RADIO_TARGET_TRACK))->SetCheck(FALSE);
    ((CButton *)GetDlgItem(IDC_RADIO_MANUAL_TRACK))->SetCheck(FALSE);
    switch(struTrackMode.byTrackMode)
    {
    case ALARM_TRACK:
        ((CButton *)GetDlgItem(IDC_RADIO_ALARM_TRACK))->SetCheck(TRUE);
        break;
//     case TARGET_TRACK:
//         ((CButton *)GetDlgItem(IDC_RADIO_TARGET_TRACK))->SetCheck(TRUE);
//         break;
    case MANUAL_CTRL:
        ((CButton *)GetDlgItem(IDC_RADIO_MANUAL_TRACK))->SetCheck(TRUE);
        break;
    default:
        break;
    }
    
}

void CDlgVcaTrackCfg::OnRadioAlarmTrack() 
{
    m_struTrackMode.byTrackMode = ALARM_TRACK;
    SetTrackMode();
}

void CDlgVcaTrackCfg::OnRadioTargetTrack() 
{
    // TODO: Add your control notification handler code here
//     m_struTrackMode.byTrackMode = TARGET_TRACK;
//     SetTrackMode();
}

long CDlgVcaTrackCfg::StartRealPlay()
{
    NET_DVR_CLIENTINFO struClientInfo;
    memset(&struClientInfo, 0, sizeof(NET_DVR_CLIENTINFO));
    struClientInfo.lChannel = m_iChannel;
    struClientInfo.hPlayWnd = GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
    m_lPlayHandle = NET_DVR_RealPlay_V30(m_lServerID, &struClientInfo, NULL, NULL, TRUE); 
    if (m_lPlayHandle == -1) 
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RealPlay_V30");
        MessageBox("Fail to Realplay");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RealPlay_V30");
    }
    return m_lPlayHandle;
}

BOOL CDlgVcaTrackCfg::StopRealPlay()
{
    if (m_lPlayHandle >= 0)
    {
        return NET_DVR_StopRealPlay(m_lPlayHandle);
    }

    return TRUE;
}

void CDlgVcaTrackCfg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
    StopRealPlay();
    CDialog::PostNcDestroy();
}

void CDlgVcaTrackCfg::OnCheckCalibration() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
	m_struTrackCfg.byEnable = m_bEnableCalibration;
    m_struTrackCfg.byDomeCalibrate = FALSE;
    
    if (TRUE == m_struTrackCfg.byEnable)
    {
        EnableWnd(!m_struTrackCfg.byEnable);
    }
    else
    {
        EnableWnd(!m_struTrackCfg.byEnable);
    }
    SetTrackCfg();
}

void CDlgVcaTrackCfg::EnableWnd(BOOL bEnable)
{
    GetDlgItem(IDC_BTN_SET_CALIBRATION)->EnableWindow(bEnable);
    GetDlgItem(IDC_COMBO_CONF_MODE)->EnableWindow(bEnable);
    GetDlgItem(IDC_RADIO_ALARM_TRACK)->EnableWindow(bEnable);
    GetDlgItem(IDC_RADIO_TARGET_TRACK)->EnableWindow(bEnable);
    GetDlgItem(IDC_RADIO_MANUAL_TRACK)->EnableWindow(bEnable);
}
void CDlgVcaTrackCfg::OnBtnSetCalibration() 
{
	// TODO: Add your control notification handler code here
	m_struTrackCfg.byDomeCalibrate = TRUE;
    SetTrackCfg();
}


void CDlgVcaTrackCfg::OnSelchangeComboConfMode() 
{
    m_struTrackMode.byRuleConfMode = m_comboConfMode.GetCurSel();
    SetTrackMode();
}

void CDlgVcaTrackCfg::OnRadioManualTrack() 
{
    m_struTrackMode.byTrackMode = MANUAL_CTRL;	
    SetTrackMode();
}

BOOL CDlgVcaTrackCfg::PreTranslateMessage(MSG* pMsg) 
{
    CRect rcWnd;
    memset(&rcWnd, 0, sizeof(rcWnd));
    GetDlgItem(IDC_PLAYWND)->GetWindowRect(&rcWnd);
    
    CPoint pt(0,0);
    GetCursorPos(&pt);
    switch (pMsg->message)
    {
    case WM_LBUTTONDOWN:
        if (PtInRect(rcWnd, pt) && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) 
            && (MANUAL_CTRL == m_struTrackMode.byTrackMode || ALARM_TRACK == m_struTrackMode.byTrackMode))
        {
            m_struTrackMode.uModeParam.struManualCtrl.struCtrlPoint.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
            m_struTrackMode.uModeParam.struManualCtrl.struCtrlPoint.fY= (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
            SetTrackMode();
        }
        break;
    default:
        break;
    }
    
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgVcaTrackCfg::OnBtnGetCalibration() 
{
	// TODO: Add your control notification handler code here
	GetTrackCfg();
}
