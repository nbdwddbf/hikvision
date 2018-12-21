// DlgIPCSpeclalEx.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgIPCSpeclalEx.h"
#include "DlgPdcRuleCfgEx.h"
#include "DlgHeatMapCfg.h"
#ifdef _DEBUG
#define new DEBUG_NEW 
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIPCSpeclalEx dialog


CDlgIPCSpeclalEx::CDlgIPCSpeclalEx(CWnd* pParent /*=NULL*/)
: CDialog(CDlgIPCSpeclalEx::IDD, pParent),
m_lLoginID(-1),
m_iDeviceIndex(-1),
m_lChannel(-1),
m_lPlayHandle(-1),
m_iChanCount(0),
m_iAnaChanCount(0),
m_iDStartChannel(-1),
m_lStartChannel(-1)
{
	//{{AFX_DATA_INIT(CDlgIPCSpeclalEx)
	m_iAudioVol = 0;
	m_dwTerminalNo = 0;
	//}}AFX_DATA_INIT
}


void CDlgIPCSpeclalEx::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIPCSpeclalEx)
	DDX_Text(pDX, IDC_EDIT_AUDIO_VOL, m_iAudioVol);
	DDX_Text(pDX, IDC_EDIT_TERMINAL_NO, m_dwTerminalNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIPCSpeclalEx, CDialog)
//{{AFX_MSG_MAP(CDlgIPCSpeclalEx)
ON_BN_CLICKED(IDC_BTN_GET_AUDIO_VOL, OnBtnGetAudioVol)
ON_BN_CLICKED(IDC_BTN_SET_AUDIO_VOL, OnBtnSetAudioVol)
	ON_BN_CLICKED(IDC_BTN_PDC, OnBtnPdc)
	ON_BN_CLICKED(IDC_BTN_HEATMAP, OnBtnHeatmap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgIPCSpeclalEx message handlers

void CDlgIPCSpeclalEx::OnBtnGetAudioVol() 
{
	DWORD dwReturn = 0;
	m_iAudioVol = 0;
	CString str;
	str.Format(_T("%d"),m_iAudioVol);
	GetDlgItem(IDC_EDIT_AUDIO_VOL)->SetWindowText(str);
	if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_AUDIOOUT_VOLUME, m_lChannel, &m_struAudioVol, sizeof(m_struAudioVol), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_AUDIOOUT_VOLUME");
		return;
    }
	
	m_iAudioVol = m_struAudioVol.byAudioOutVolume;
	str.Format(_T("%d"),m_iAudioVol);
	GetDlgItem(IDC_EDIT_AUDIO_VOL)->SetWindowText(str);
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_AUDIOOUT_VOLUME");
	
}

void CDlgIPCSpeclalEx::OnBtnSetAudioVol() 
{
	m_iAudioVol = 0;
	CString str;
	GetDlgItem(IDC_EDIT_AUDIO_VOL)->GetWindowText(str);
	char *ch = str.GetBuffer(str.GetLength());
	int m_iAudioVol = atoi(ch);
	char szLan[128] = {0};
	if (m_iAudioVol < 0 || m_iAudioVol > 100)
	{
		g_StringLanType(szLan, "音频范围在0 -- 100之间", "AudioVol between 0 - 100 ");
		AfxMessageBox(szLan);
		return;
	}
	m_struAudioVol.dwSize = sizeof(m_struAudioVol);
	m_struAudioVol.byAudioOutVolume = m_iAudioVol;
	if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_AUDIOOUT_VOLUME, m_lChannel, &m_struAudioVol, sizeof(m_struAudioVol)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_AUDIOOUT_VOLUME");
        return;
	}
	
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_AUDIOOUT_VOLUME");
}

void CDlgIPCSpeclalEx::OnBtnPdc() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CDlgPdcRuleCfgEx dlg;
	dlg.m_lServerID = m_lLoginID;
	dlg.m_lChannel = LONG(m_dwTerminalNo<<16 | (DWORD)m_lChannel);
	dlg.m_iDevIndex = m_iDeviceIndex;
	dlg.m_lChanNum = m_iChanCount;
	dlg.DoModal();
}

void CDlgIPCSpeclalEx::OnBtnHeatmap() 
{
	// TODO: Add your control notification handler code here
	CDlgHeatMapCfg dlg;
	dlg.m_lServerID = m_lLoginID;
	dlg.m_lChannel = m_lChannel;
	dlg.m_iDevIndex = m_iDeviceIndex;
	dlg.DoModal();
}

BOOL CDlgIPCSpeclalEx::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (g_struDeviceInfo[m_iDeviceIndex].iDeviceType == DS_D60S) //信息发布服务器
	{
		GetDlgItem(IDC_EDIT_TERMINAL_NO)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_TERMINAL_NO)->EnableWindow(FALSE);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
