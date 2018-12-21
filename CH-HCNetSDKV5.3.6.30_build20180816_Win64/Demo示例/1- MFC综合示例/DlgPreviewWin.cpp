// DlgPreviewWin.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPreviewWin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPreviewWin dialog


CDlgPreviewWin::CDlgPreviewWin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreviewWin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPreviewWin)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lPreviewHandle = -1;
}


void CDlgPreviewWin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPreviewWin)
	DDX_Control(pDX, IDC_COMBO_STREAM_TYPE, m_comboStreamType);
	DDX_Control(pDX, IDC_COMBO_PROTOCOL, m_comboProtocol);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPreviewWin, CDialog)
	//{{AFX_MSG_MAP(CDlgPreviewWin)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_START, OnBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPreviewWin message handlers

void CDlgPreviewWin::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	OnBtnStop();
	CDialog::OnCancel();
}

BOOL CDlgPreviewWin::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	memset(&m_struPara, 0, sizeof(m_struPara));
	m_struPara.lChannel = m_struStreamInfo.dwChannel;	
	m_struPara.bBlocked = 0;
	m_struPara.hPlayWnd = GetDlgItem(IDC_STATIC_PREVIEW)->m_hWnd;
	memcpy(m_struPara.byStreamID, m_struStreamInfo.byID, STREAM_ID_LEN);

	m_comboProtocol.SetCurSel(0);
	m_comboStreamType.SetCurSel(0);
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPreviewWin::OnBtnStart() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};

	if (m_lPreviewHandle != -1)
	{
		g_StringLanType(szLan, "ÇëÏÈÍ£Ö¹Ô¤ÀÀ", "Please stop preview first");
		AfxMessageBox(szLan);
		return;
	}

	m_struPara.dwStreamType = m_comboStreamType.GetCurSel();
	m_struPara.dwLinkMode = m_comboProtocol.GetCurSel();

	if (-1 != (m_lPreviewHandle = NET_DVR_RealPlay_V40(m_lUserID, &m_struPara, NULL, NULL)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_RealPlay_V40");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RealPlay_V40");
	}
}

void CDlgPreviewWin::OnBtnStop() 
{
	// TODO: Add your control notification handler code here
	if (m_lPreviewHandle != -1)
	{
		NET_DVR_StopRealPlay(m_lPreviewHandle);	
		Invalidate();
		m_lPreviewHandle = -1;
	}
}

void CDlgPreviewWin::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if (m_lPreviewHandle != -1)
	{
		NET_DVR_StopRealPlay(m_lPreviewHandle);	
		Invalidate();
		m_lPreviewHandle = -1;
	}
	CDialog::OnClose();
}
