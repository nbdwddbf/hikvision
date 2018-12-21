// DlgAudioInVolumeCfg1.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAudioInVolumeCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAudioInVolumeCfg dialog


CDlgAudioInVolumeCfg::CDlgAudioInVolumeCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAudioInVolumeCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAudioInVolumeCfg)
	m_csVolume = _T("");
	m_bEnableFBC = FALSE;
	m_bEnableAEC = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgAudioInVolumeCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAudioInVolumeCfg)
	DDX_Control(pDX, IDC_CMB_AUDIOOUT_TYPE, m_cmbAudioOutType);
	DDX_Control(pDX, IDC_CMB_AUDIOIN_CHAN_NO, m_cmbAudioInChan);
	DDX_Control(pDX, IDC_SLIDER_VOLUME, m_sliderVolume);
	DDX_Text(pDX, IDC_STATIC_VOLUME, m_csVolume);
	DDX_Check(pDX, IDC_CHK_ENABLE_FBC, m_bEnableFBC);
	DDX_Check(pDX, IDC_CHK_AEC, m_bEnableAEC);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAudioInVolumeCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgAudioInVolumeCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_VOLUME, OnCustomdrawSliderVolume)
	ON_CBN_SELCHANGE(IDC_CMB_AUDIOOUT_TYPE, OnSelchangeCmbAudiooutType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAudioInVolumeCfg message handlers

void CDlgAudioInVolumeCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	
	char szLan[128] = {0};
 
	memset(&m_struVolumeCfg, 0, sizeof(NET_DVR_VOLUME_CFG));
	
	DWORD dwReturnedBytes = 0;

	LONG lChannel = m_cmbAudioInChan.GetCurSel() + 1;
	
	if(NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_AUDIOIN_VOLUME_CFG, lChannel, &m_struVolumeCfg, sizeof(NET_DVR_VOLUME_CFG), &dwReturnedBytes))
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
	
    m_cmbAudioOutType.SetCurSel(m_dwLastIndex);
	m_sliderVolume.SetPos(m_struVolumeCfg.wVolume[m_dwLastIndex]);
	
	UpdateData(FALSE);
}

void CDlgAudioInVolumeCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);
	
	char szLan[128] = {0};
	m_struVolumeCfg.dwSize = sizeof(NET_DVR_VOLUME_CFG);
	
    DWORD dwIndex = 0;
    if (m_cmbAudioOutType.GetCurSel() < 0)
    {
        dwIndex = 0;
    }
    else
    {
        dwIndex = m_cmbAudioOutType.GetCurSel();
    }
	m_struVolumeCfg.wVolume[dwIndex] = m_sliderVolume.GetPos();

	LONG lChannel = m_cmbAudioInChan.GetCurSel() + 1;
	
	if(NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_AUDIOIN_VOLUME_CFG, lChannel, &m_struVolumeCfg, sizeof(NET_DVR_VOLUME_CFG)))
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
// 	m_cmbAudioInChan.ResetContent();
// 
// 	int i = 0;
// 
// 	for (i = 0; i < 16; i++)
// 	{
// 		sprintf(szLan, "MIC%d", i+1);
// 		m_cmbAudioInChan.InsertString(0, szLan);
// 		m_cmbAudioInChan.SetItemData(0, i+1);
// 	}
// 
// 	for (i = 0; i < 4; i++)
// 	{
// 	}
// 	
// 	m_cmbAudioInChan.InsertString(0, "VGA in4");
// 	m_cmbAudioInChan.SetItemData(0, 12);
// 
// 	m_cmbAudioInChan.InsertString(0, "VGA in4");
// 	m_cmbAudioInChan.SetItemData(0, 12);
// 
// 	m_cmbAudioInChan.InsertString(0, "VGA in4");
// 	m_cmbAudioInChan.SetItemData(0, 12);
// 
// 	m_cmbAudioInChan.InsertString(0, "VGA in4");
// 	m_cmbAudioInChan.SetItemData(0, 12);
// 
// 	m_cmbAudioInChan.InsertString(0, "VGA in4");
// 	m_cmbAudioInChan.SetItemData(0, 12);

	m_cmbAudioInChan.SetCurSel(0);	

	m_sliderVolume.SetRange(0, 127);
	m_sliderVolume.SetPos(0);

	sprintf(szLan, "%d", 0);
	SetDlgItemText(IDC_STATIC_VOLUME, szLan);

    m_cmbAudioOutType.SetCurSel(0);

	OnBtnGet();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAudioInVolumeCfg::OnCustomdrawSliderVolume(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE); 
    m_csVolume.Format("%d", m_sliderVolume.GetPos()); 
    UpdateData(FALSE);

	*pResult = 0;
}

void CDlgAudioInVolumeCfg::OnSelchangeCmbAudiooutType() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
	m_struVolumeCfg.wVolume[m_dwLastIndex] = m_sliderVolume.GetPos();

    m_dwLastIndex = m_cmbAudioOutType.GetCurSel();
    m_sliderVolume.SetPos(m_struVolumeCfg.wVolume[m_dwLastIndex]);
    UpdateData(FALSE);

}
