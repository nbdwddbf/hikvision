// DlgInqMixAudioInCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInqMixAudioInCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInqMixAudioInCfg dialog


CDlgInqMixAudioInCfg::CDlgInqMixAudioInCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInqMixAudioInCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInqMixAudioInCfg)
	m_bEnableMixAudioIn = FALSE;
	m_nMixAudioDelay = 0;
	//}}AFX_DATA_INIT
	m_iCurChanType = -1;
	memset(&m_struInqMixAudioInCfg, 0, sizeof(NET_DVR_INQUEST_MIX_AUDIOIN_CFG));
}


void CDlgInqMixAudioInCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInqMixAudioInCfg)
	DDX_Control(pDX, IDC_CMB_MIX_CHAN_NUM, m_cmbMixChanNum);
	DDX_Control(pDX, IDC_CMB_INQ_ROOM_NO, m_cmbInqRoomNo);
	DDX_Control(pDX, IDC_LIST_CHAN, m_listCtrlChan);
	DDX_Control(pDX, IDC_CMB_CHAN_TYPE, m_cmbChanType);
	DDX_Check(pDX, IDC_CHK_ENABLE_MIX_AUDIO, m_bEnableMixAudioIn);
	DDX_Text(pDX, IDC_EDIT_MIX_AUDIO_DELAY, m_nMixAudioDelay);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInqMixAudioInCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgInqMixAudioInCfg)
	ON_CBN_SELCHANGE(IDC_CMB_CHAN_TYPE, OnSelchangeCmbChanType)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_REFRESH_CHAN_NUM, OnBtnRefreshChanNum)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInqMixAudioInCfg message handlers

void CDlgInqMixAudioInCfg::OnSelchangeCmbChanType() 
{
	// TODO: Add your control notification handler code here
	GetChanInfoFromWnd();
	InitChanList();
	SetChanInfoToDlg();
}

void CDlgInqMixAudioInCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);
	GetChanInfoFromWnd();
	
	char szLan[128] = {0};
	
	m_struInqMixAudioInCfg.dwSize = sizeof(NET_DVR_INQUEST_MIX_AUDIOIN_CFG);
	m_struInqMixAudioInCfg.byEnable = m_bEnableMixAudioIn;
	m_struInqMixAudioInCfg.dwMixCnt = m_cmbMixChanNum.GetCurSel();
	m_struInqMixAudioInCfg.byMixAudioDelay = (BYTE)m_nMixAudioDelay;

	LONG lInqRoomNo = m_cmbInqRoomNo.GetCurSel() + 1;
	
	if(!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_INQUEST_MIX_AUDIOIN_CFG, lInqRoomNo, &m_struInqMixAudioInCfg, sizeof(NET_DVR_INQUEST_MIX_AUDIOIN_CFG)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_INQUEST_MIX_AUDIOIN_CFG");
		sprintf(szLan,"NET_DVR_SET_INQUEST_MIX_AUDIOIN_CFG failed[%d]", NET_DVR_GetLastError());
		AfxMessageBox(szLan);
	}
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_INQUEST_MIX_AUDIOIN_CFG");
    }
}

BOOL CDlgInqMixAudioInCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cmbInqRoomNo.SetCurSel(0);
	m_cmbChanType.SetCurSel(0);

	InitMixChanNumCombo();
	m_cmbMixChanNum.SetCurSel(0);
	InitChanList();
	OnBtnGet();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgInqMixAudioInCfg::InitMixChanNumCombo()
{
	char szLan[128] = {0};
    m_cmbMixChanNum.ResetContent();

	LONG lChanNum = g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum;
	int i = -1;
    for (i = 0; i < lChanNum + 3; i ++)
    {
        sprintf(szLan, "%d", i);
        m_cmbMixChanNum.AddString(szLan);
    }
}

void CDlgInqMixAudioInCfg::InitChanList()
{
	LONG lChanNum = g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum;
	
	char szLan[128] = {0};
	
	m_listCtrlChan.DeleteAllItems();
	m_listCtrlChan.SetExtendedStyle(LVS_EX_CHECKBOXES);
	int iChanType = m_cmbChanType.GetCurSel();
	int i = -1;

	if (iChanType == 0)	//模拟/数字通道
	{
		for (i = 0; i < lChanNum; i++)
		{
			g_StringLanType(szLan, "通道", "Chan");
			sprintf(szLan, "%s%d", szLan, i+1);
			m_listCtrlChan.InsertItem(i, szLan);
		}
	}
	if (iChanType == 1)	//Mic
	{
		for (i = 0; i < 1; i++)
		{
			g_StringLanType(szLan, "Mic", "Mic");
			sprintf(szLan, "%s%d", szLan, i+1);
			m_listCtrlChan.InsertItem(i, szLan);
		}
	}
	if (iChanType == 2)	//Line In
	{
		for (i = 0; i < 1; i++)
		{
			g_StringLanType(szLan, "Line In", "Chan");
			sprintf(szLan, "%s%d", szLan, i+1);
			m_listCtrlChan.InsertItem(i, szLan);
		}
	}
	
	UpdateData(FALSE);
}

void CDlgInqMixAudioInCfg::OnBtnGet()
{
	char szLan[128] = {0};
	DWORD dwBytesReturned = -1;
	
	m_struInqMixAudioInCfg.dwSize = sizeof(NET_DVR_INQUEST_MIX_AUDIOIN_CFG);
	LONG lInqRoomIndex = m_cmbInqRoomNo.GetCurSel() + 1;
	
	if(!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_INQUEST_MIX_AUDIOIN_CFG, lInqRoomIndex, &m_struInqMixAudioInCfg, sizeof(NET_DVR_INQUEST_MIX_AUDIOIN_CFG), &dwBytesReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_INQUEST_MIX_AUDIOIN_CFG");
		sprintf(szLan,"NET_DVR_GET_INQUEST_MIX_AUDIOIN_CFG failed[%d]", NET_DVR_GetLastError());
		AfxMessageBox(szLan);
		return;
	}
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_INQUEST_MIX_AUDIOIN_CFG");
    }
	
	m_bEnableMixAudioIn = m_struInqMixAudioInCfg.byEnable;
	m_cmbMixChanNum.SetCurSel(m_struInqMixAudioInCfg.dwMixCnt);
	m_nMixAudioDelay = m_struInqMixAudioInCfg.byMixAudioDelay;
	
	//m_cmbChanType.SetCurSel(0);

	SetChanInfoToDlg();
	//OnSelchangeCmbChanType();
	
	UpdateData(FALSE);
}

void CDlgInqMixAudioInCfg::SetChanInfoToDlg()
{
	LONG lChanNum = g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum;

	int iChanType = m_cmbChanType.GetCurSel();
	int i = -1;
	if (iChanType == 0)	//模拟/数字通道
	{
		for ( i = 0 ; i < m_listCtrlChan.GetItemCount(); i++ )
		{
			m_listCtrlChan.SetCheck( i, m_struInqMixAudioInCfg.bySrcChan[i]);
		}
	}
	if (iChanType == 1)//Mic
	{
		for ( i = 0 ; i < m_listCtrlChan.GetItemCount(); i++ )
		{
			m_listCtrlChan.SetCheck( i, m_struInqMixAudioInCfg.byMic[i]);
		}
	}
	if (iChanType == 2)//Line In
	{
		for ( i = 0 ; i < m_listCtrlChan.GetItemCount(); i++ )
		{
			m_listCtrlChan.SetCheck( i, m_struInqMixAudioInCfg.byLineIn[i]);
		}
	}

	m_iCurChanType = iChanType;
	
	UpdateData(FALSE);
}

void CDlgInqMixAudioInCfg::GetChanInfoFromWnd()
{
	UpdateData(TRUE);
	int i = -1;

	if (m_iCurChanType == 0)
	{
		memset(m_struInqMixAudioInCfg.bySrcChan, 0, MAX_MIX_CHAN_NUM);
		for (i=0; i<m_listCtrlChan.GetItemCount(); i++)
		{
			m_struInqMixAudioInCfg.bySrcChan[i] = m_listCtrlChan.GetCheck(i);
		}
	}
	else if(m_iCurChanType == 1)
	{
		memset(m_struInqMixAudioInCfg.byMic, 0, 16);
		for (i=0; i<m_listCtrlChan.GetItemCount(); i++)
		{
			m_struInqMixAudioInCfg.byMic[i] = m_listCtrlChan.GetCheck(i);
		}
	}
	else if (m_iCurChanType == 2)
	{
		memset(m_struInqMixAudioInCfg.byLineIn, 0, 16);
		for (i=0; i<m_listCtrlChan.GetItemCount(); i++)
		{
			m_struInqMixAudioInCfg.byLineIn[i] = m_listCtrlChan.GetCheck(i);
		}
	}
}



void CDlgInqMixAudioInCfg::OnBtnRefreshChanNum() 
{
	// TODO: Add your control notification handler code here
	int i = -1;
	m_struInqMixAudioInCfg.dwMixCnt = 0;
	GetChanInfoFromWnd();

	for (i=0; i< MAX_MIX_CHAN_NUM; i++)
	{
		if (m_struInqMixAudioInCfg.bySrcChan[i] == 1)
		{
			m_struInqMixAudioInCfg.dwMixCnt += 1;
		}
	}
	for (i=0; i< MAX_LINE_IN_CHAN_NUM; i++)
	{
		if (m_struInqMixAudioInCfg.byLineIn[i] == 1)
		{
			m_struInqMixAudioInCfg.dwMixCnt += 1;
		}
	}
	for (i=0; i< MAX_MIC_CHAN_NUM; i++)
	{
		if (m_struInqMixAudioInCfg.byMic[i] == 1)
		{
			m_struInqMixAudioInCfg.dwMixCnt += 1;
		}
	}
	m_cmbMixChanNum.SetCurSel(m_struInqMixAudioInCfg.dwMixCnt);

	UpdateData(FALSE);
}
