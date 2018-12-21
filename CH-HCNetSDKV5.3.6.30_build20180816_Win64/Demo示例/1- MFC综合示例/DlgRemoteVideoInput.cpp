// DlgRemoteVideoInput.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRemoteVideoInput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteVideoInput dialog


CDlgRemoteVideoInput::CDlgRemoteVideoInput(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteVideoInput::IDD, pParent)
	,m_lUserID(-1)
	,m_lChannel(-1)
	,m_dwDevIndex(0)
	,m_lRealHandle(-1)
{
	//{{AFX_DATA_INIT(CDlgRemoteVideoInput)
	//}}AFX_DATA_INIT
	ZeroMemory(&m_struVidowInEffect, sizeof(m_struVidowInEffect));
}


void CDlgRemoteVideoInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteVideoInput)
	DDX_Control(pDX, IDC_SLIDER_SHARPNESS, m_sliderSharpness);
	DDX_Control(pDX, IDC_SLIDER_DENOISING, m_sliderDenoising);
	DDX_Control(pDX, IDC_SLIDER_SATURATION, m_sliderSaturation);
	DDX_Control(pDX, IDC_SLIDER_HUE, m_sliderHue);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST, m_sliderContrast);
	DDX_Control(pDX, IDC_SLIDER_BRIGHT, m_sliderBrightness);
	DDX_Control(pDX, IDC_COMBO_INPUT_MODE, m_comboMode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRemoteVideoInput, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteVideoInput)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_SETUP, OnButtonSetup)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_CBN_SELCHANGE(IDC_COMBO_INPUT_MODE, OnSelchangeComboInputMode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteVideoInput message handlers

BOOL CDlgRemoteVideoInput::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	char szLan[128] = {0};
	
	g_StringLanType(szLan, "标准", "Standard");
	m_comboMode.AddString(szLan);
	g_StringLanType(szLan, "室内", "Indoor");
	m_comboMode.AddString(szLan);
	g_StringLanType(szLan, "弱光", "Dim light");
	m_comboMode.AddString(szLan);
	g_StringLanType(szLan, "室外", "Outdoor");
	m_comboMode.AddString(szLan);
	g_StringLanType(szLan, "自定义", "Customize");
	m_comboMode.AddString(szLan);
	m_comboMode.SetCurSel(0);

	m_sliderBrightness.SetRange(1, MAX_RANGE, TRUE);
	m_sliderHue.SetRange(1, MAX_RANGE, TRUE);
	m_sliderSaturation.SetRange(1, MAX_RANGE, TRUE);
	m_sliderContrast.SetRange(1, MAX_RANGE, TRUE);
	m_sliderSharpness.SetRange(1, MAX_RANGE, TRUE);
	m_sliderDenoising.SetRange(1,MAX_RANGE, TRUE);

	NET_DVR_CLIENTINFO strClientInfo = {0};
	strClientInfo.lChannel = m_lChannel;
	strClientInfo.lLinkMode = 0;
	strClientInfo.hPlayWnd = GetDlgItem(IDC_STATIC_REALPLAY)->GetSafeHwnd();
	m_lRealHandle = NET_DVR_RealPlay(m_lUserID, &strClientInfo);

	OnButtonUpdate();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRemoteVideoInput::OnButtonUpdate() 
{
	DWORD dwBytesReturned = 0;
	if(!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_VIDEO_INPUT_EFFECT, m_lChannel, &m_struVidowInEffect, sizeof(m_struVidowInEffect), &dwBytesReturned))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_GET_VIDEO_INPUT_EFFECT", m_lChannel);	
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "chan[%d] NET_DVR_GET_VIDEO_INPUT_EFFECT", m_lChannel);	

		if (255 == m_struVidowInEffect.wEffectMode)
		{
			m_comboMode.SetCurSel(4);
		}
		else
		{
			m_comboMode.SetCurSel(m_struVidowInEffect.wEffectMode);
		}
		

		m_sliderBrightness.SetPos(m_struVidowInEffect.struVideoEffect.dwBrightValue);
		m_sliderSaturation.SetPos(m_struVidowInEffect.struVideoEffect.dwSaturationValue);
		m_sliderContrast.SetPos(m_struVidowInEffect.struVideoEffect.dwContrastValue);
		m_sliderHue.SetPos(m_struVidowInEffect.struVideoEffect.dwHueValue);
		m_sliderSharpness.SetPos(m_struVidowInEffect.struVideoEffect.dwSharpness);
		m_sliderDenoising.SetPos(m_struVidowInEffect.struVideoEffect.dwDenoising);

		UpdateData(FALSE);
	}
}

void CDlgRemoteVideoInput::OnButtonSetup() 
{
	UpdateData(TRUE);

	m_struVidowInEffect.struVideoEffect.dwBrightValue = m_sliderBrightness.GetPos();
	m_struVidowInEffect.struVideoEffect.dwSaturationValue = m_sliderSaturation.GetPos();
	m_struVidowInEffect.struVideoEffect.dwContrastValue = m_sliderContrast.GetPos();
	m_struVidowInEffect.struVideoEffect.dwHueValue = m_sliderHue.GetPos();
	m_struVidowInEffect.struVideoEffect.dwSharpness = m_sliderSharpness.GetPos();
	m_struVidowInEffect.struVideoEffect.dwDenoising = m_sliderDenoising.GetPos();

	if(m_comboMode.GetCurSel() == 4)
	{
		m_struVidowInEffect.wEffectMode = 255;
	}
	else
	{
		m_struVidowInEffect.wEffectMode = m_comboMode.GetCurSel();
	}

	if(!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_VIDEO_INPUT_EFFECT, m_lChannel, &m_struVidowInEffect, sizeof(m_struVidowInEffect)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_SET_VIDEO_INPUT_EFFECT", m_lChannel);	
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "chan[%d] NET_DVR_SET_VIDEO_INPUT_EFFECT", m_lChannel);	
	}
}

void CDlgRemoteVideoInput::OnButtonExit() 
{
	NET_DVR_StopRealPlay(m_lRealHandle);
	CDialog::OnOK();
}

void CDlgRemoteVideoInput::OnSelchangeComboInputMode() 
{
	NET_DVR_DEFAULT_VIDEO_COND struDefaultVideoCond;
	memset(&struDefaultVideoCond, 0, sizeof(NET_DVR_DEFAULT_VIDEO_COND));
	struDefaultVideoCond.dwSize = sizeof(NET_DVR_DEFAULT_VIDEO_COND);
	struDefaultVideoCond.dwChannel = m_lChannel;
	if(m_comboMode.GetCurSel() == 4)
	{
		struDefaultVideoCond.dwVideoMode = 255;
	}
	else
	{
		struDefaultVideoCond.dwVideoMode = m_comboMode.GetCurSel();
	}
	

	NET_DVR_VIDEO_EFFECT struVideoEffect;
	memset(&struVideoEffect, 0, sizeof(NET_DVR_VIDEO_EFFECT));
	DWORD dwStatus = 0;

	BOOL bRet = NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_DEFAULT_VIDEO_EFFECT, 1, &struDefaultVideoCond,sizeof(struDefaultVideoCond),&dwStatus, &struVideoEffect, sizeof(struVideoEffect));
	
	if (!(bRet && (0 == dwStatus)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_DEFAULT_VIDEO_EFFECT");
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_DEFAULT_VIDEO_EFFECT");
	}

	m_sliderBrightness.SetPos(struVideoEffect.dwBrightValue);
	m_sliderSaturation.SetPos(struVideoEffect.dwSaturationValue);
	m_sliderContrast.SetPos(struVideoEffect.dwContrastValue);
 	m_sliderHue.SetPos(struVideoEffect.dwHueValue);
	m_sliderSharpness.SetPos(struVideoEffect.dwSharpness);
 	m_sliderDenoising.SetPos(struVideoEffect.dwDenoising);

	UpdateData(FALSE);
}
