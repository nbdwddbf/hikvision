// DlgTerminalConferenceStatus.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgTerminalConferenceStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTerminalConferenceStatus dialog


CDlgTerminalConferenceStatus::CDlgTerminalConferenceStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTerminalConferenceStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTerminalConferenceStatus)
	m_bDisabledAudioIn = FALSE;
	m_bMute = FALSE;
	m_csConferenceID = _T("");
	m_csConferenceName = _T("");
	m_csEndTime = _T("");
	m_csStartTime = _T("");
	m_csURL = _T("");
	m_byVolumeIn = 0;
	m_byVolumeOut = 0;
	//}}AFX_DATA_INIT
}


void CDlgTerminalConferenceStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTerminalConferenceStatus)
	DDX_Control(pDX, IDC_COMBO_CONFERENCE_TYPE, m_comboConferenceType);
	DDX_Control(pDX, IDC_COMBO_CONFERENCE_STATE, m_comboConferenceState);
	DDX_Check(pDX, IDC_CHK_DISABLED_AUDIO_IN, m_bDisabledAudioIn);
	DDX_Check(pDX, IDC_CHK_MUTE, m_bMute);
	DDX_Text(pDX, IDC_EDIT_CONFERENCE_ID, m_csConferenceID);
	DDX_Text(pDX, IDC_EDIT_CONFERENCE_NAME, m_csConferenceName);
	DDX_Text(pDX, IDC_EDIT_END_TIME, m_csEndTime);
	DDX_Text(pDX, IDC_EDIT_START_TIME, m_csStartTime);
	DDX_Text(pDX, IDC_EDIT_URL, m_csURL);
	DDX_Text(pDX, IDC_EDIT_VOLUME_IN, m_byVolumeIn);
	DDX_Text(pDX, IDC_EDIT_VOLUME_OUT, m_byVolumeOut);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTerminalConferenceStatus, CDialog)
	//{{AFX_MSG_MAP(CDlgTerminalConferenceStatus)
	ON_CBN_SELCHANGE(IDC_COMBO_CONFERENCE_TYPE, OnSelchangeComboConferenceType)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTerminalConferenceStatus message handlers

BOOL CDlgTerminalConferenceStatus::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;

    GetDlgItem(IDC_STATIC_URL)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_EDIT_URL)->ShowWindow(SW_HIDE);
    OnBtnGet();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTerminalConferenceStatus::OnSelchangeComboConferenceType() 
{
	// TODO: Add your control notification handler code here
    if (m_comboConferenceType.GetCurSel() < 0)
    {
        return;
    }

    if (m_comboConferenceType.GetCurSel() == 0)
    {
        GetDlgItem(IDC_STATIC_URL)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_URL)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_CONFERENCE_NAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_CONFERENCE_NAME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_CONFERENCE_ID)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_CONFERENCE_ID)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_START_TIME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_START_TIME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_END_TIME)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_END_TIME)->ShowWindow(SW_HIDE);
    }
    else if (m_comboConferenceType.GetCurSel() == 1)
    {
        GetDlgItem(IDC_STATIC_URL)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_URL)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_CONFERENCE_NAME)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_CONFERENCE_NAME)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_CONFERENCE_ID)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_CONFERENCE_ID)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_START_TIME)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_START_TIME)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_END_TIME)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_END_TIME)->ShowWindow(SW_SHOW);
    }	
}

void CDlgTerminalConferenceStatus::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    NET_DVR_STD_CONFIG struStdConfig = {0};
    NET_DVR_TERMINAL_CONFERENCE_STATUS struTerminalConferenceStatus = {0};
	struTerminalConferenceStatus.dwSize = sizeof(struTerminalConferenceStatus);

    struStdConfig.lpOutBuffer = &struTerminalConferenceStatus;
    struStdConfig.dwOutSize = sizeof(struTerminalConferenceStatus);

    if (!NET_DVR_GetSTDConfig(m_lUserID, NET_DVR_GET_TERMINAL_CONFERENCE_STATUS, &struStdConfig))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_TERMINAL_CONFERENCE_STATUS");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_TERMINAL_CONFERENCE_STATUS");
        m_comboConferenceState.SetCurSel(struTerminalConferenceStatus.byConferenceState);
        m_comboConferenceType.SetCurSel(struTerminalConferenceStatus.byConferenceType-1);
        
        if (struTerminalConferenceStatus.byConferenceType == 1)
        {
            m_csURL.Format("%s", struTerminalConferenceStatus.struCallInfo.struTerminalCallInfo.byTermianlURL);
			m_bMute = struTerminalConferenceStatus.struAudioStatus.byMute;
            m_byVolumeOut = struTerminalConferenceStatus.struAudioStatus.byVolume;
            m_bDisabledAudioIn = struTerminalConferenceStatus.struAudioStatus.byAudioInputDisabled;
            m_byVolumeIn = struTerminalConferenceStatus.struAudioStatus.byAudioInputVolume;
			OnSelchangeComboConferenceType();

			UpdateData(FALSE);
        }
        else if (struTerminalConferenceStatus.byConferenceType == 2)
        {
            m_csConferenceName.Format("%s", struTerminalConferenceStatus.struCallInfo.struConferenceCallInfo.byConferenceName);
            m_csConferenceID.Format("%s", struTerminalConferenceStatus.struCallInfo.struConferenceCallInfo.byConferenceID);
            m_csStartTime.Format("%4d-%02d-%02d %02d:%02d:%02d", \
                struTerminalConferenceStatus.struCallInfo.struConferenceCallInfo.struStartTime.dwYear,\
                struTerminalConferenceStatus.struCallInfo.struConferenceCallInfo.struStartTime.dwMonth,\
                struTerminalConferenceStatus.struCallInfo.struConferenceCallInfo.struStartTime.dwDay,\
                struTerminalConferenceStatus.struCallInfo.struConferenceCallInfo.struStartTime.dwHour,\
                struTerminalConferenceStatus.struCallInfo.struConferenceCallInfo.struStartTime.dwMinute,\
                struTerminalConferenceStatus.struCallInfo.struConferenceCallInfo.struStartTime.dwSecond);
            m_csEndTime.Format("%4d-%02d-%02d %02d:%02d:%02d", \
                struTerminalConferenceStatus.struCallInfo.struConferenceCallInfo.struEndTime.dwYear,\
                struTerminalConferenceStatus.struCallInfo.struConferenceCallInfo.struEndTime.dwMonth,\
                struTerminalConferenceStatus.struCallInfo.struConferenceCallInfo.struEndTime.dwDay,\
                struTerminalConferenceStatus.struCallInfo.struConferenceCallInfo.struEndTime.dwHour,\
                struTerminalConferenceStatus.struCallInfo.struConferenceCallInfo.struEndTime.dwMinute,\
                struTerminalConferenceStatus.struCallInfo.struConferenceCallInfo.struEndTime.dwSecond);
            m_bMute = struTerminalConferenceStatus.struAudioStatus.byMute;
            m_byVolumeOut = struTerminalConferenceStatus.struAudioStatus.byVolume;
            m_bDisabledAudioIn = struTerminalConferenceStatus.struAudioStatus.byAudioInputDisabled;
            m_byVolumeIn = struTerminalConferenceStatus.struAudioStatus.byAudioInputVolume;
			OnSelchangeComboConferenceType();

            UpdateData(FALSE);
        }
    }	
}

void CDlgTerminalConferenceStatus::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
    CDialog::OnCancel();
}
