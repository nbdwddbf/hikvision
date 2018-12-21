// DlgTrialAudioActivation.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgTrialAudioActivation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTrialAudioActivation dialog


CDlgTrialAudioActivation::CDlgTrialAudioActivation(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTrialAudioActivation::IDD, pParent)
    ,m_lUserID(-1)
    ,m_iDevIndex(-1)
{
	//{{AFX_DATA_INIT(CDlgTrialAudioActivation)
	m_bEnable = FALSE;
	m_wDelayTime = 0;
	m_bySensitivity = 0;
	m_byPriority = 0;
	m_bPreset = FALSE;
	m_bChkVGA1 = FALSE;
	m_bChkVGA2 = FALSE;
	m_bChkVGA3 = FALSE;
	m_bChkVGA4 = FALSE;
	m_bChkVGA5_10 = FALSE;
	m_bChkHDMI1 = FALSE;
	m_bChkHDMI2 = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgTrialAudioActivation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTrialAudioActivation)
	DDX_Control(pDX, IDC_CMB_BASE_NO, m_cmbBaseNo);
	DDX_Control(pDX, IDC_CMB_PRESET_NO, m_cmbPresetNO);
	DDX_Control(pDX, IDC_CMB_CHAN, m_cmbChan);
	DDX_Control(pDX, IDC_CMB_AUDIO_INPUT_NO, m_cmbAudioActivation);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	DDX_Text(pDX, IDC_EDIT_SWITCH_DELAY_TIME, m_wDelayTime);
	DDX_Text(pDX, IDC_EDIT_SENSITIVITY, m_bySensitivity);
	DDX_Text(pDX, IDC_EDIT_PRIORITY, m_byPriority);
	DDX_Check(pDX, IDC_CHK_PRESET, m_bPreset);
	DDX_Check(pDX, IDC_CHK_VGA1, m_bChkVGA1);
	DDX_Check(pDX, IDC_CHK_VGA2, m_bChkVGA2);
	DDX_Check(pDX, IDC_CHK_VGA3, m_bChkVGA3);
	DDX_Check(pDX, IDC_CHK_VGA4, m_bChkVGA4);
	DDX_Check(pDX, IDC_CHK_VGA5_10, m_bChkVGA5_10);
	DDX_Check(pDX, IDC_CHK_HDMI1, m_bChkHDMI1);
	DDX_Check(pDX, IDC_CHK_HDMI3, m_bChkHDMI2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTrialAudioActivation, CDialog)
	//{{AFX_MSG_MAP(CDlgTrialAudioActivation)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_CBN_SELCHANGE(IDC_CMB_AUDIO_INPUT_NO, OnSelchangeCmbAudioInputNo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTrialAudioActivation message handlers

void CDlgTrialAudioActivation::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    int i = 0;
	memset(&m_struAudioActCfg,0,sizeof(m_struAudioActCfg));
    DWORD dwAudioInputNo = m_cmbAudioActivation.GetItemData(m_cmbAudioActivation.GetCurSel());
    DWORD dwRet = 0;

    if (NET_DVR_GetDVRConfig(m_lUserID,NET_DVR_GET_AUDIO_ACTIVATION_CFG,dwAudioInputNo,&m_struAudioActCfg,sizeof(m_struAudioActCfg),&dwRet))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_AUDIO_ACTIVATION_CFG Audio Input Chan[%d]", NET_DVR_GET_AUDIO_ACTIVATION_CFG,dwAudioInputNo);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_AUDIO_ACTIVATION_CFG Audio Input Chan[%d]", NET_DVR_GET_AUDIO_ACTIVATION_CFG,dwAudioInputNo);
        return;
    }

    //change Get Info

    m_bEnable = m_struAudioActCfg.byEnable;
    for ( i = 0; i < m_cmbChan.GetCount(); i++)
    {
        if (m_cmbChan.GetItemData(i) == m_struAudioActCfg.dwChanNo)
        {
            m_cmbChan.SetCurSel(i);
            break;
        }
    }

    //
    m_wDelayTime    = m_struAudioActCfg.wDelayTime;
    m_bPreset       = m_struAudioActCfg.byEnablePreset;
    m_byPriority    = m_struAudioActCfg.byPriority;
    m_bySensitivity = m_struAudioActCfg.bySensitivity;
	m_bChkVGA1 = m_struAudioActCfg.byVoChanNo[0];
	m_bChkVGA2 = m_struAudioActCfg.byVoChanNo[1];
	m_bChkVGA3 = m_struAudioActCfg.byVoChanNo[2];
	m_bChkVGA4 = m_struAudioActCfg.byVoChanNo[3];
	m_bChkVGA5_10 = m_struAudioActCfg.byVoChanNo[4];
	m_bChkHDMI1 = m_struAudioActCfg.byVoChanNo[5];
	m_bChkHDMI2 = m_struAudioActCfg.byVoChanNo[6];
    for ( i = 0; i < m_cmbPresetNO.GetCount();i++)
    {
        if (m_cmbPresetNO.GetItemData(i) == m_struAudioActCfg.wPreset)
        {
            m_cmbPresetNO.SetCurSel(i);
            break;
        }
    }

	for ( i = 0; i < m_cmbBaseNo.GetCount();i++)
    {
        if (m_cmbBaseNo.GetItemData(i) == m_struAudioActCfg.wBase)
        {
            m_cmbBaseNo.SetCurSel(i);
            break;
        }
    }
    UpdateData(FALSE);

}

BOOL CDlgTrialAudioActivation::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    // TODO: Add extra initialization here
    int i = 0,j;
    char szLan[1024] = {0};
    DWORD dwIndex = 0;
    //add audio Input chan Info
    m_cmbAudioActivation.ResetContent();
    for (i = 0; i < 16; i++)
    {
        sprintf(szLan, "MacIn%d", i+1);
        m_cmbAudioActivation.AddString(szLan);
        m_cmbAudioActivation.SetItemData(dwIndex,i+ g_struDeviceInfo[m_iDevIndex].byStartAudioInputChanNo);
        dwIndex++;
    }
    
    for (i = 0; i < 4; i++)
    {
        sprintf(szLan, "Stereo LineIn%d", i+1);
        m_cmbAudioActivation.AddString(szLan);
        m_cmbAudioActivation.SetItemData(dwIndex,i+ g_struDeviceInfo[m_iDevIndex].byStartAudioInputChanNo+ 16);
        dwIndex++;
    }
    
    for (i = 0; i < 2; i++)
    {
        sprintf(szLan, "ineIn%d", i+1);
        m_cmbAudioActivation.AddString(szLan);
        m_cmbAudioActivation.SetItemData(dwIndex,i+ g_struDeviceInfo[m_iDevIndex].byStartAudioInputChanNo+ 16+4);
        dwIndex++;
    }
    
    for (i = 0; i< m_struSystemInfo.byVideoInTypeNum;i++)
    {
        if (m_struSystemInfo.struVideoIn[i].wInType == 3)
        {
            for (int j =0; j < m_struSystemInfo.struVideoIn[i].wInNum;j++)
            {
                sprintf(szLan,"IPChannel%02d",j+1);
                m_cmbAudioActivation.AddString(szLan);
                m_cmbAudioActivation.SetItemData(dwIndex++,j+16+4+2 +1);
            }
            break;
        }
    }

    m_cmbAudioActivation.SetCurSel(0);

    //add vedio In channel info
    m_cmbChan.ResetContent();
    dwIndex = 0;
    BOOL bBreak = FALSE;
    for (i = 0; i< m_struSystemInfo.byVideoInTypeNum; i++)
    {         
        for ( j = 0; j < m_struSystemInfo.struVideoIn[i].wInNum; j++)
        {
            switch(m_struSystemInfo.struVideoIn[i].wInType)
            {
            case 0:
                sprintf(szLan,"SDI%02d",j+1); 
                break;
            case 1:
                sprintf(szLan,"VGA%02d",j+1); 
                break;
            case 2:
                sprintf(szLan,"HDMI%02d",j+1); 
                break;
            case 3:
                sprintf(szLan,"IP%02d",j+1); 
                break;
            case 4:
                sprintf(szLan,"PIP%02d",j+1); 
                break;
            default:
                sprintf(szLan,"Unkown%02d",j+1); 
                break;
            }           
            
            m_cmbChan.AddString(szLan);
            m_cmbChan.SetItemData(dwIndex,m_struSystemInfo.struVideoIn[i].wStartNo + j);
            dwIndex++;
        }
    }
    
 
    m_cmbChan.SetCurSel(0);
    //add Preset
	dwIndex = 0;
    m_cmbPresetNO.ResetContent();
    for( i = 0; i < 256; i++)
    {
       sprintf(szLan,"Preset %d",i+1);
       m_cmbPresetNO.AddString(szLan);
       m_cmbPresetNO.SetItemData(dwIndex,i+1);
       dwIndex++;
    }
    
    m_cmbBaseNo.SetCurSel(0);
	dwIndex = 0;
    m_cmbBaseNo.ResetContent();
    for( i = 0; i < 256; i++)
    {
		sprintf(szLan,"Preset %d",i+1);
		m_cmbBaseNo.AddString(szLan);
		m_cmbBaseNo.SetItemData(dwIndex,i+1);
		dwIndex++;
    }
    
    m_cmbBaseNo.SetCurSel(0);

    OnBtnGet();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTrialAudioActivation::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    DWORD dwAudioInputNo = m_cmbAudioActivation.GetItemData(m_cmbAudioActivation.GetCurSel());
    DWORD dwRet = 0;
    memset(&m_struAudioActCfg,0,sizeof(m_struAudioActCfg));
    m_struAudioActCfg.dwSize = sizeof(m_struAudioActCfg);
    m_struAudioActCfg.byEnable = m_bEnable;
    m_struAudioActCfg.dwChanNo = m_cmbChan.GetItemData(m_cmbChan.GetCurSel());
    m_struAudioActCfg.wDelayTime = m_wDelayTime;
    m_struAudioActCfg.byPriority = m_byPriority;
    m_struAudioActCfg.bySensitivity = m_bySensitivity;
    m_struAudioActCfg.byEnablePreset = m_bPreset;

	m_struAudioActCfg.byVoChanNo[0]  = m_bChkVGA1;
	m_struAudioActCfg.byVoChanNo[1] = m_bChkVGA2;
	m_struAudioActCfg.byVoChanNo[2] = m_bChkVGA3;
	m_struAudioActCfg.byVoChanNo[3] = m_bChkVGA4;
	m_struAudioActCfg.byVoChanNo[4] = m_bChkVGA5_10;
	m_struAudioActCfg.byVoChanNo[5] = m_bChkHDMI1;
	m_struAudioActCfg.byVoChanNo[6] = m_bChkHDMI2;
    if (m_bPreset)
    {
        m_struAudioActCfg.wPreset = /*m_cmbPresetNO.GetItemData(*/m_cmbPresetNO.GetCurSel()+1/*)*/;
		m_struAudioActCfg.wBase = m_cmbBaseNo.GetCurSel()+1;
    }

    if (NET_DVR_SetDVRConfig(m_lUserID,NET_DVR_SET_AUDIO_ACTIVATION_CFG,dwAudioInputNo,&m_struAudioActCfg,sizeof(m_struAudioActCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_AUDIO_ACTIVATION_CFG Audio Input Chan[%d]", NET_DVR_GET_AUDIO_ACTIVATION_CFG,dwAudioInputNo);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_AUDIO_ACTIVATION_CFG Audio Input Chan[%d]", NET_DVR_GET_AUDIO_ACTIVATION_CFG,dwAudioInputNo);
        return;
    }
}

void CDlgTrialAudioActivation::OnSelchangeCmbAudioInputNo() 
{
	// TODO: Add your control notification handler code here
	OnBtnGet();
}
