// DlgAudioInVolumeCfg1.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAudioInVolumeCfg1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAudioInVolumeCfg dialog


CDlgAudioInVolumeCfg::CDlgAudioInVolumeCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAudioInVolumeCfg::IDD, pParent)
    , m_iAudioInIndex(1)
    , m_iAudioVolume(0)
{
	//{{AFX_DATA_INIT(CDlgAudioInVolumeCfg)
	m_bChkPhantomPower = FALSE;
	m_bEnableFBC = FALSE;
	m_bEnableAEC = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgAudioInVolumeCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgAudioInVolumeCfg)
    DDX_Check(pDX, IDC_CHK_PHANTOM_POWER, m_bChkPhantomPower);
    DDX_Check(pDX, IDC_CHK_ENABLE_FBC, m_bEnableFBC);
    DDX_Check(pDX, IDC_CHK_AEC, m_bEnableAEC);
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_AUDIO_IN_INDEX, m_iAudioInIndex);
    DDX_Control(pDX, IDC_COMBO_AUDIO_OUT_INDEX, m_comboAudioOutIndex);
    DDX_Text(pDX, IDC_EDIT_AUDIO_VOLUME, m_iAudioVolume);
}


BEGIN_MESSAGE_MAP(CDlgAudioInVolumeCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgAudioInVolumeCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
    ON_CBN_SELCHANGE(IDC_COMBO_AUDIO_OUT_INDEX, &CDlgAudioInVolumeCfg::OnCbnSelchangeComboAudioOutIndex)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAudioInVolumeCfg message handlers

void CDlgAudioInVolumeCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

	char szLan[128] = {0};
 
	memset(&m_struVolumeCfg, 0, sizeof(NET_DVR_VOLUME_CFG));

    DWORD dwReturnedBytes = 0;
	
    if (NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_AUDIOIN_VOLUME_CFG, m_iAudioInIndex, &m_struVolumeCfg, sizeof(NET_DVR_VOLUME_CFG), &dwReturnedBytes))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_AUDIOIN_VOLUME_CFG");
		g_StringLanType(szLan, "获取音频输入口音量调节参数成功!", "Success to get audio in volume parameter config");
		//	AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_AUDIOIN_VOLUME_CFG");
		g_StringLanType(szLan, "获取音频输入口音量调节参数失败!", "Fail to get audio in volume parameter config");
		AfxMessageBox(szLan);
		return;
	}
	
    m_comboAudioOutIndex.SetCurSel(m_dwLastIndex);
    if (0 <= m_dwLastIndex && m_dwLastIndex < 8)
    {
        m_iAudioVolume = m_struVolumeCfg.wVolume[m_dwLastIndex];
    }
    else if (8 <= m_dwLastIndex && m_dwLastIndex < 16)
    {
        m_iAudioVolume = m_struVolumeCfg.wVolumeEx[m_dwLastIndex - 8];
    }
    m_bChkPhantomPower = m_struVolumeCfg.byPhantomPowerSupply - 1;
	m_bEnableAEC = m_struVolumeCfg.byEnableAEC;
	m_bEnableFBC = m_struVolumeCfg.byEnableFBC[m_dwLastIndex];
	
	UpdateData(FALSE);
}

void CDlgAudioInVolumeCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);
	
	char szLan[128] = {0};
	m_struVolumeCfg.dwSize = sizeof(NET_DVR_VOLUME_CFG);
	
    DWORD dwIndex = 0;
    if (m_comboAudioOutIndex.GetCurSel() < 0)
    {
        dwIndex = 0;
    }
    else
    {
        dwIndex = m_comboAudioOutIndex.GetCurSel();
    }

    if (0 <= m_dwLastIndex && m_dwLastIndex < 8)
    {
        m_struVolumeCfg.wVolume[m_dwLastIndex] = m_iAudioVolume;
    }
    else if (8 <= m_dwLastIndex && m_dwLastIndex < 16)
    {
        m_struVolumeCfg.wVolumeEx[m_dwLastIndex - 8] = m_iAudioVolume;
    }

	m_struVolumeCfg.byPhantomPowerSupply = m_bChkPhantomPower+1;
	m_struVolumeCfg.byEnableAEC = m_bEnableAEC;
	m_struVolumeCfg.byEnableFBC[dwIndex] = m_bEnableFBC;


	
    if (NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_AUDIOIN_VOLUME_CFG, m_iAudioInIndex, &m_struVolumeCfg, sizeof(NET_DVR_VOLUME_CFG)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_AUDIOIN_VOLUME_CFG");
		g_StringLanType(szLan, "设置音频输入口音量调节参数成功!", "Success to set audio in volume parameter config");
		//	AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_AUDIOIN_VOLUME_CFG");
		g_StringLanType(szLan, "设置音频输入口音量调节参数失败!", "Fail to set audio in volume parameter config");
		AfxMessageBox(szLan);
		return;
	}
}

BOOL CDlgAudioInVolumeCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_dwLastIndex = 0;
	// TODO: Add extra initialization here

	char szLan[128] = {0};
    memset(&m_struVolumeCfg,0,sizeof(m_struVolumeCfg));

    for (int i = 0; i < 16; i++)
    {
        sprintf(szLan, "%d", i);
        m_comboAudioOutIndex.AddString(szLan);
    }

	OnBtnGet();

    m_comboAudioOutIndex.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgAudioInVolumeCfg::OnCbnSelchangeComboAudioOutIndex()
{
    // TODO:  在此添加控件通知处理程序代码
    m_dwLastIndex = m_comboAudioOutIndex.GetCurSel();
    if (0 <= m_dwLastIndex && m_dwLastIndex < 8)
    {
        m_iAudioVolume = m_struVolumeCfg.wVolume[m_dwLastIndex];
    }
    else if (8 <= m_dwLastIndex && m_dwLastIndex < 16)
    {
        m_iAudioVolume = m_struVolumeCfg.wVolumeEx[m_dwLastIndex - 8];
    }
    UpdateData(FALSE);
}
