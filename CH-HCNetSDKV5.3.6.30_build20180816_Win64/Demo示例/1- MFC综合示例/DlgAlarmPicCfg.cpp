// DlgAlarmPicCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmPicCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmPicCfg dialog


CDlgAlarmPicCfg::CDlgAlarmPicCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmPicCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAlarmPicCfg)
	m_nAlarmAfterPic = 0;
	m_nAlarmBeforePic = 0;
	m_nIntervalTime = 0;
	//}}AFX_DATA_INIT
}


void CDlgAlarmPicCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmPicCfg)
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_comboChannel);
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_comboResolution);
	DDX_Text(pDX, IDC_ALARM_AFTER_PIC, m_nAlarmAfterPic);
	DDX_Text(pDX, IDC_ALARM_BEFORE_PIC, m_nAlarmBeforePic);
	DDX_Text(pDX, IDC_INTERVAL_TIME, m_nIntervalTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmPicCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmPicCfg)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmPicCfg message handlers

void CDlgAlarmPicCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struAlarmCaptrueCfg.dwSize = sizeof(m_struAlarmCaptrueCfg);
	m_struAlarmCaptrueCfg.byAfterAlarmPic = m_nAlarmAfterPic;
	m_struAlarmCaptrueCfg.byBeforeAlarmPic = m_nAlarmBeforePic;
	m_struAlarmCaptrueCfg.byResolution = m_comboResolution.GetCurSel() + 1;
	m_struAlarmCaptrueCfg.wInterval = m_nIntervalTime;
	char szLan[128] = {0};
	if (NET_DVR_SetDVRConfig(m_lUserID,NET_DVR_SET_ALARM_CAPTRUE_CFG, m_comboChannel.GetItemData(m_comboChannel.GetCurSel()), &m_struAlarmCaptrueCfg,sizeof(m_struAlarmCaptrueCfg)))
	{
		g_pMainDlg->AddLog(m_lUserID, OPERATION_SUCC_T, "NET_DVR_SET_ALARM_CAPTRUE_CFG SUCC");
	}
	else
	{
		g_StringLanType(szLan, "ÉèÖÃ±¨¾¯×¥Í¼ÅäÖÃÊ§°Ü" , "NET_DVR_SET_ALARM_CAPTRUE_CFG FAILED");
		MessageBox(szLan);
		g_pMainDlg->AddLog(m_lUserID, OPERATION_FAIL_T, "NET_DVR_SET_ALARM_CAPTRUE_CFG FAILED");
		return;
	}
}

void CDlgAlarmPicCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struAlarmCaptrueCfg.dwSize = sizeof(m_struAlarmCaptrueCfg);
	
	char szLan[128] = {0};
	DWORD dwRet = 0;
	if (NET_DVR_GetDVRConfig(m_lUserID,NET_DVR_GET_ALARM_CAPTRUE_CFG, m_comboChannel.GetItemData(m_comboChannel.GetCurSel()),&m_struAlarmCaptrueCfg,sizeof(m_struAlarmCaptrueCfg),&dwRet))
	{
		g_pMainDlg->AddLog(m_lUserID, OPERATION_SUCC_T, "NET_DVR_GET_ALARM_CAPTRUE_CFG SUCC");
	}
	else
	{
		g_StringLanType(szLan, "»ñÈ¡±¨¾¯×¥Í¼ÅäÖÃÊ§°Ü" , "NET_DVR_GET_ALARM_CAPTRUE_CFG FAILED");
		MessageBox(szLan);
		g_pMainDlg->AddLog(m_lUserID, OPERATION_FAIL_T, "NET_DVR_GET_ALARM_CAPTRUE_CFG FAILED");
		return;
	}
	m_nAlarmAfterPic = m_struAlarmCaptrueCfg.byAfterAlarmPic;
	m_nAlarmBeforePic = m_struAlarmCaptrueCfg.byBeforeAlarmPic;
	m_comboResolution.SetCurSel(m_struAlarmCaptrueCfg.byResolution - 1);
	m_nIntervalTime = m_struAlarmCaptrueCfg.wInterval;
	UpdateData(FALSE);
}

BOOL CDlgAlarmPicCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char szLan[128] = {0};
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	memset(&m_struAlarmCaptrueCfg,0,sizeof(m_struAlarmCaptrueCfg));

	m_comboChannel.ResetContent();
	LONG i = -1;
	for (i = 0; i < g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum; i++)
	{
		sprintf(szLan, "%s", g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].chChanName);	
		m_comboChannel.AddString(szLan);
		m_comboChannel.SetItemData(i, g_struDeviceInfo[m_iDeviceIndex].pStruChanInfo[i].iChannelNO);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
