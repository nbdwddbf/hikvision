// DlgStreamID.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgStreamID.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgStreamID dialog


CDlgStreamID::CDlgStreamID(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStreamID::IDD, pParent)
    ,m_iTabIndex(0)
{
	//{{AFX_DATA_INIT(CDlgStreamID)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgStreamID::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgStreamID)
	DDX_Control(pDX, IDC_TAB_STREAM_ID, m_tabStreamID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgStreamID, CDialog)
	//{{AFX_MSG_MAP(CDlgStreamID)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_STREAM_ID, OnSelchangeTabStreamId)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgStreamID message handlers


BOOL CDlgStreamID::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char szLan[1024] = {0};
	m_iTabIndex = 0;
	g_StringLanType(szLan, "流来源", "Stream source");
	m_tabStreamID.InsertItem(0, szLan);
	m_dlgStreamSrc.Create(IDD_DLG_STREAM_SRC_CFG, &m_tabStreamID);
	m_dlgStreamSrc.ShowWindow(SW_HIDE);
	
	g_StringLanType(szLan, "流录像状态", "Stream record status");
	m_tabStreamID.InsertItem(1, szLan);
	m_dlgStreamRecordStatus.Create(IDD_DLG_STREAM_RECORD_STATUS, &m_tabStreamID);
	m_dlgStreamRecordStatus.ShowWindow(SW_HIDE);
	
	g_StringLanType(szLan, "流录像计划", "Stream record information");
	m_tabStreamID.InsertItem(2, szLan);
	m_dlgStreamRecordInfo.Create(IDD_DLG_STREAM_RECORD_INFO, &m_tabStreamID);
	m_dlgStreamRecordInfo.ShowWindow(SW_HIDE);

	g_StringLanType(szLan, "流手动录像和录像段加锁", "Stream manual record and lock");
	m_tabStreamID.InsertItem(3, szLan);
	m_dlgStreamManualRecordAndLock.Create(IDD_DLG_STREAM_MANUAL_RECORD_AND_LOCK, &m_tabStreamID);
	m_dlgStreamManualRecordAndLock.ShowWindow(SW_HIDE);

	g_StringLanType(szLan, "流录像检查和统计", "Stream record check");
	m_tabStreamID.InsertItem(4, szLan);
	m_dlgStreamRecordCheck.Create(IDD_DLG_STREAM_RECORD_CHECK, &m_tabStreamID);
	m_dlgStreamRecordCheck.ShowWindow(SW_HIDE);

    g_StringLanType(szLan, "流媒体参数配置", "Stream media config");
    m_tabStreamID.InsertItem(5, szLan);
    m_dlgStreamMediaCfg.Create(IDD_DLG_STREAM_MEDIA_CFG, &m_tabStreamID);
    m_dlgStreamMediaCfg.ShowWindow(SW_HIDE);

	WindowUpdate();
	
	
//	HWND hParentWnd[2] = {m_hWnd, m_tabStreamID.m_hWnd};
// 	m_dlgStreamSrc.SetParentWnd(hParentWnd, 2);
// 	m_dlgStreamRecordStatus.SetParentWnd(hParentWnd, 2);
// 	m_dlgStreamRecordInfo.SetParentWnd(hParentWnd, 2);

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgStreamID::WindowUpdate()
{
	switch (m_iTabIndex)
	{
	case 0:
		m_dlgStreamSrc.ShowWindow(SW_SHOW);
		m_dlgStreamRecordStatus.ShowWindow(SW_HIDE);
		m_dlgStreamRecordInfo.ShowWindow(SW_HIDE);
		m_dlgStreamManualRecordAndLock.ShowWindow(SW_HIDE);
		m_dlgStreamRecordCheck.ShowWindow(SW_HIDE);
        m_dlgStreamMediaCfg.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_dlgStreamSrc.ShowWindow(SW_HIDE);
		m_dlgStreamRecordStatus.ShowWindow(SW_SHOW);
		m_dlgStreamRecordInfo.ShowWindow(SW_HIDE);
		m_dlgStreamManualRecordAndLock.ShowWindow(SW_HIDE);
		m_dlgStreamRecordCheck.ShowWindow(SW_HIDE);
        m_dlgStreamMediaCfg.ShowWindow(SW_HIDE);
		break;
	case 2:
		m_dlgStreamSrc.ShowWindow(SW_HIDE);
		m_dlgStreamRecordStatus.ShowWindow(SW_HIDE);
		m_dlgStreamRecordInfo.ShowWindow(SW_SHOW);
		m_dlgStreamManualRecordAndLock.ShowWindow(SW_HIDE);
		m_dlgStreamRecordCheck.ShowWindow(SW_HIDE);
        m_dlgStreamMediaCfg.ShowWindow(SW_HIDE);
		break;
	case 3:
		m_dlgStreamSrc.ShowWindow(SW_HIDE);
		m_dlgStreamRecordStatus.ShowWindow(SW_HIDE);
		m_dlgStreamRecordInfo.ShowWindow(SW_HIDE);
		m_dlgStreamManualRecordAndLock.ShowWindow(SW_SHOW);
		m_dlgStreamRecordCheck.ShowWindow(SW_HIDE);
        m_dlgStreamMediaCfg.ShowWindow(SW_HIDE);
        m_dlgStreamManualRecordAndLock.InitWindows();
		break;
	case 4:
		m_dlgStreamSrc.ShowWindow(SW_HIDE);
		m_dlgStreamRecordStatus.ShowWindow(SW_HIDE);
		m_dlgStreamRecordInfo.ShowWindow(SW_HIDE);
		m_dlgStreamManualRecordAndLock.ShowWindow(SW_HIDE);
		m_dlgStreamRecordCheck.ShowWindow(SW_SHOW);
        m_dlgStreamMediaCfg.ShowWindow(SW_HIDE);
		break;
    case 5:
        m_dlgStreamSrc.ShowWindow(SW_HIDE);
        m_dlgStreamRecordStatus.ShowWindow(SW_HIDE);
        m_dlgStreamRecordInfo.ShowWindow(SW_HIDE);
        m_dlgStreamManualRecordAndLock.ShowWindow(SW_HIDE);
        m_dlgStreamRecordCheck.ShowWindow(SW_HIDE);
        m_dlgStreamMediaCfg.ShowWindow(SW_SHOW);
        break;
	default:
		m_dlgStreamSrc.ShowWindow(SW_SHOW);
		m_dlgStreamRecordStatus.ShowWindow(SW_HIDE);
		m_dlgStreamRecordInfo.ShowWindow(SW_HIDE);
		m_dlgStreamManualRecordAndLock.ShowWindow(SW_HIDE);
		m_dlgStreamRecordCheck.ShowWindow(SW_HIDE);
        m_dlgStreamMediaCfg.ShowWindow(SW_HIDE);
		break;

	}
}

void CDlgStreamID::OnSelchangeTabStreamId(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_iTabIndex = m_tabStreamID.GetCurSel();
	WindowUpdate();
	*pResult = 0;
}
