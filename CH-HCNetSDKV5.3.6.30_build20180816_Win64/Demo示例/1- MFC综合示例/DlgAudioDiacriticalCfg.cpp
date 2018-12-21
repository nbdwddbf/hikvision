// DlgAudioDiacriticalCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAudioDiacriticalCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAudioDiacriticalCfg dialog


CDlgAudioDiacriticalCfg::CDlgAudioDiacriticalCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAudioDiacriticalCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAudioDiacriticalCfg)
	m_bEnable = FALSE;
	m_csBassValue = _T("");
	//}}AFX_DATA_INIT
}


void CDlgAudioDiacriticalCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAudioDiacriticalCfg)
	DDX_Control(pDX, IDC_CMB_CHAN, m_cmbChan);
	DDX_Control(pDX, IDC_SLIDER_BASS_VALUE, m_sliderBassValue);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	DDX_Text(pDX, IDC_STATIC_BASS_VALUE, m_csBassValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAudioDiacriticalCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgAudioDiacriticalCfg)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_BASS_VALUE, OnCustomdrawSliderBassValue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAudioDiacriticalCfg message handlers

void CDlgAudioDiacriticalCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	NET_DVR_AUDIO_DIACRITICAL_CFG struAudioDiacriticalCfg = {0};
	memset(&struAudioDiacriticalCfg, 0, sizeof(NET_DVR_AUDIO_DIACRITICAL_CFG));
	
	DWORD dwReturnedBytes = 0;

	int iChannel = m_cmbChan.GetItemData(m_cmbChan.GetCurSel());
	
	if(NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_AUDIO_DIACRITICAL_CFG, iChannel, &struAudioDiacriticalCfg, sizeof(NET_DVR_AUDIO_DIACRITICAL_CFG), &dwReturnedBytes))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_AUDIO_DIACRITICAL_CFG");
		g_StringLanType(szLan, "ªÒ»°“Ù∆µ±‰“Ù≈‰÷√≥…π¶!", "Success to get audio diacritical config");
		//	AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_AUDIO_DIACRITICAL_CFG");
		g_StringLanType(szLan, "ªÒ»°“Ù∆µ±‰“Ù≈‰÷√ ß∞‹!", "Fail to get audio diacritical config");
		AfxMessageBox(szLan);
		return;
	}
	m_sliderBassValue.SetPos(struAudioDiacriticalCfg.byBassValue);
	m_bEnable = struAudioDiacriticalCfg.byEnable;
	UpdateData(FALSE);
}

void CDlgAudioDiacriticalCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);

	int iChannel = m_cmbChan.GetItemData(m_cmbChan.GetCurSel());
	
	char szLan[128] = {0};
	NET_DVR_AUDIO_DIACRITICAL_CFG struAudioDiacriticalCfg = {0};
	memset(&struAudioDiacriticalCfg, 0, sizeof(NET_DVR_AUDIO_DIACRITICAL_CFG));
	
	struAudioDiacriticalCfg.dwSize = sizeof(NET_DVR_AUDIO_DIACRITICAL_CFG);

	struAudioDiacriticalCfg.byEnable = m_bEnable;
	struAudioDiacriticalCfg.byBassValue = m_sliderBassValue.GetPos();
	
	if(NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_AUDIO_DIACRITICAL_CFG, iChannel, &struAudioDiacriticalCfg, sizeof(NET_DVR_AUDIO_DIACRITICAL_CFG)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_AUDIO_DIACRITICAL_CFG");
		g_StringLanType(szLan, "…Ë÷√“Ù∆µ±‰“Ù≈‰÷√≥…π¶!", "Success to set audio diacritical config");
		//	AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_AUDIO_DIACRITICAL_CFG");
		g_StringLanType(szLan, "…Ë÷√“Ù∆µ±‰“Ù≈‰÷√ ß∞‹!", "Fail to set audio diacritical config");
		AfxMessageBox(szLan);
		return;
	}
}

BOOL CDlgAudioDiacriticalCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	
	char szLan[128] = {0};
    m_cmbChan.ResetContent();
	
	int i;
	for ( i = 0; i < g_struDeviceInfo[m_dwDevIndex].iDeviceChanNum; i++ )
	{	
		m_cmbChan.AddString(g_struDeviceInfo[m_dwDevIndex].pStruChanInfo[i].chChanName);
		m_cmbChan.SetItemData(i, g_struDeviceInfo[m_dwDevIndex].pStruChanInfo[i].iChannelNO);
	}
	
    m_cmbChan.AddString("Error Chan");
    m_cmbChan.SetItemData(g_struDeviceInfo[m_dwDevIndex].iDeviceChanNum, 0xffff);

	m_cmbChan.SetCurSel(0);

	m_sliderBassValue.SetRange(-12, 12);
	m_sliderBassValue.SetPos(0);

	OnBtnGet();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAudioDiacriticalCfg::OnCustomdrawSliderBassValue(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE); 
    m_csBassValue.Format("%d", m_sliderBassValue.GetPos()); 
    UpdateData(FALSE);

	*pResult = 0;
}
