// DlgInfoDiffusionTernimalPreview.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInfoDiffusionTernimalPreview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionTernimalPreview dialog


CDlgInfoDiffusionTernimalPreview::CDlgInfoDiffusionTernimalPreview(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInfoDiffusionTernimalPreview::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInfoDiffusionTernimalPreview)
	m_dwChannelNo = 0;
	m_dwTerminalNo = 0;
	//}}AFX_DATA_INIT
	m_iDevIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDevIndex].lLoginID;
	memset(&m_struPreview, 0, sizeof(m_struPreview));
	m_lPreviewHandle = -1;
}


void CDlgInfoDiffusionTernimalPreview::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInfoDiffusionTernimalPreview)
	DDX_Text(pDX, IDC_EDIT_CHANNEL_NO, m_dwChannelNo);
	DDX_Text(pDX, IDC_EDIT_TERMINAL_NO, m_dwTerminalNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInfoDiffusionTernimalPreview, CDialog)
	//{{AFX_MSG_MAP(CDlgInfoDiffusionTernimalPreview)
	ON_BN_CLICKED(IDC_BTN_START_PREVIEW, OnBtnStartPreview)
	ON_BN_CLICKED(IDC_BTN_STOP_PREVIEW, OnBtnStopPreview)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionTernimalPreview message handlers

void CDlgInfoDiffusionTernimalPreview::OnBtnStartPreview() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	if (m_lPreviewHandle >= 0)
	{
		StopPreview();
		m_lPreviewHandle = -1;
	}
	m_lPreviewHandle = StartPreview();
}

void CDlgInfoDiffusionTernimalPreview::OnBtnStopPreview() 
{
	// TODO: Add your control notification handler code here
	if (m_lPreviewHandle >= 0)
	{
		StopPreview();
		m_lPreviewHandle = -1;
	}
}

BOOL CDlgInfoDiffusionTernimalPreview::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgInfoDiffusionTernimalPreview::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	OnBtnStopPreview();
}

LONG CDlgInfoDiffusionTernimalPreview::StartPreview()
{
	memset(&m_struPreview, 0, sizeof(m_struPreview));
	m_struPreview.byProtoType = g_struDeviceInfo[m_iDevIndex].pStruChanInfo->nPreviewProtocolType;
	m_struPreview.hPlayWnd = GetDlgItem(IDC_STAT_PLAY_WND)->m_hWnd;
	m_struPreview.lChannel = m_dwTerminalNo<<16 | m_dwChannelNo;
	m_struPreview.lLinkMode = g_struDeviceInfo[m_iDevIndex].pStruChanInfo->dwStreamType<<31 | g_struDeviceInfo[m_iDevIndex].pStruChanInfo->dwLinkMode;
	
	LONG lHandle = -1;
	lHandle = NET_DVR_RealPlay_V30(m_lUserID, &m_struPreview, NULL, NULL, TRUE);
	if (lHandle < 0)
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RealPlay_V30");
		char sLan[256] = {0};
		g_StringLanType(sLan, "Ô¤ÀÀÊ§°Ü£¡", "Preview failed!");
		AfxMessageBox(sLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RealPlay_V30");
	}

	return lHandle;
}

BOOL CDlgInfoDiffusionTernimalPreview::StopPreview()
{
	if (!NET_DVR_StopRealPlay(m_lPreviewHandle))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopRealPlay");
		return FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopRealPlay");
		return TRUE;
	}
}
