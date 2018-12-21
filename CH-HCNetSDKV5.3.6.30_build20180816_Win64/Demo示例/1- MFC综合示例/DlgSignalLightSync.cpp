// DlgSignalLightSync.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgSignalLightSync.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSignalLightSync dialog


CDlgSignalLightSync::CDlgSignalLightSync(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSignalLightSync::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSignalLightSync)
	m_wPhase = 0;
	//}}AFX_DATA_INIT
}


void CDlgSignalLightSync::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSignalLightSync)
	DDX_Control(pDX, IDC_COMBO_LINKLOCK, m_cbLinkLock);
	DDX_Text(pDX, IDC_EDIT_PHASE, m_wPhase);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSignalLightSync, CDialog)
	//{{AFX_MSG_MAP(CDlgSignalLightSync)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSignalLightSync message handlers

void CDlgSignalLightSync::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	char szLan[64]={0};
	if (m_iCurChanNO<0 || m_iCurChanNO>1024)
	{
		g_StringLanType(szLan,"通道非法","channel invalid");
		MessageBox(szLan);
		return;
	}

	DWORD dwRet=0;
	NET_DVR_SIGNAL_SYNCCFG struSignalSyncCfg={0};
	struSignalSyncCfg.dwSize = sizeof(struSignalSyncCfg);
	CString strErr;
	if (!NET_DVR_GetDVRConfig(m_lUserID,NET_DVR_GET_SIGNAL_SYNC,m_iCurChanNO,&struSignalSyncCfg,sizeof(struSignalSyncCfg),&dwRet))
	{
		strErr.Format("NET_DVR_GET_SIGNAL_SYNC chan[%d] failed! error code[%d]", m_iCurChanNO, NET_DVR_GetLastError());
		MessageBox(strErr);
		return;
	}

	MessageBox("NET_DVR_GET_SIGNAL_SYNC suss!");

	m_wPhase = struSignalSyncCfg.wPhase;
	m_cbLinkLock.SetCurSel(struSignalSyncCfg.byLineLock);

	UpdateData(FALSE);

}

void CDlgSignalLightSync::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	char szLan[64]={0};
	if (m_iCurChanNO<0 || m_iCurChanNO>1024)
	{
		g_StringLanType(szLan,"通道非法","channel invalid");
		MessageBox(szLan);
		return;
	}

	NET_DVR_SIGNAL_SYNCCFG struSignalSyncCfg={0};
	struSignalSyncCfg.dwSize = sizeof(struSignalSyncCfg);
	struSignalSyncCfg.wPhase = m_wPhase;
	struSignalSyncCfg.byLineLock = m_cbLinkLock.GetCurSel();
	CString strErr;
	if (!NET_DVR_SetDVRConfig(m_lUserID,NET_DVR_SET_SIGNAL_SYNC,m_iCurChanNO,&struSignalSyncCfg,sizeof(struSignalSyncCfg)))
	{
		strErr.Format("NET_DVR_SET_SIGNAL_SYNC chan[%d] failed! error code[%d]", m_iCurChanNO, NET_DVR_GetLastError());
		MessageBox(strErr);
		return;
	}
	
	MessageBox("NET_DVR_SET_SIGNAL_SYNC suss!");
}

BOOL CDlgSignalLightSync::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	int iCurChanIndex = g_pMainDlg->GetCurChanIndex();
	m_iCurChanNO = g_struDeviceInfo[iDeviceIndex].pStruChanInfo[iCurChanIndex].iChannelNO; 

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
